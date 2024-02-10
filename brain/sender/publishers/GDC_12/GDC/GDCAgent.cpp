#include "GDCAgent.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "common/utils/logger/Logger.hpp"
#include "brain/brain_app/BrainApp.hpp"

#include <algorithm>
#include <climits>
#include <fstream>
#include <functional>
#include <limits>
#include <random>
#include <vector>

using brain::publishers::agents::GDCAgent;
using namespace vwg::e3p::drm;
using brain::publishers::agents::CampaignConfiguration;


GDCAgent::GDCAgent(std::shared_ptr<common::memory::PersistentMemoryFactory> memoryFactory)
  : gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton(ara::com::InstanceIdentifier(kGdcCommonLargeInstance))
  , gdcgenerichugeskeleton::OdcAgentGenericHugeSkeleton(ara::com::InstanceIdentifier(kGdcGenericHugeInstance))
  , m_flowControlStatusArrived(std::make_shared<common::notification_handler::DataArrivedEvent>())
  , m_backendCommunicationDtc(ids_evt_EventIdsBackendCommunicationUnavailable)
{
    m_persistentMemoryManager = memoryFactory->CreatePersistentMemory(PM_DB);
    auto* app = brain::app_mng::BrainApp::GetInstance();
    if (nullptr != app)
    {
        auto config = app->GetConfigurationClass();
        if (nullptr != config)
        {
            std::ignore = config->GetValue(brain::config_keys::DISABLE_FEATURE_IDSENABLEDISABLE_ON_CAMPAIGN_AVAILABILITY,
                                           m_isFeatureDisabled);
        }
    }

    initializeFromStorage();
}

void
GDCAgent::InitCallback(ChangeModeCallback changeBEMode)
{
    m_changeBEMode = changeBEMode;
}
GDCAgent::~GDCAgent()
{
    try
    {
        // Sets idsBackendCommunicationUnavailable state if no GDC campaign arrived during current driving cycle (Diag
        // DTC - 0x600507 - ids_backend_communication_unavailable)
        m_backendCommunicationDtc.SetEvent(m_receivedCampaign);
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "destruction of the GDCAgent failed and got exception." << LOG_NOOP;
    }  // only for parasoft violations
}

void
GDCAgent::OfferService()
{
    gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::OfferService();
    LOG_INFO << "GDCAgent/" << kGdcCommonLargeInstance << ":Service offered" << LOG_NOOP;
    gdcgenerichugeskeleton::OdcAgentGenericHugeSkeleton::OfferService();
    LOG_INFO << "GDCAgent/" << kGdcGenericHugeInstance << ":Service offered" << LOG_NOOP;
}

void
GDCAgent::StopOfferService()
{
    gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::StopOfferService();
    LOG_INFO << "GDCAgent/" << kGdcCommonLargeInstance << ":Service stopped" << LOG_NOOP;
    gdcgenerichugeskeleton::OdcAgentGenericHugeSkeleton::StopOfferService();
    LOG_INFO << "GDCAgent/" << kGdcGenericHugeInstance << ":Service stopped" << LOG_NOOP;
}

::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::addCampaignOutput>
GDCAgent::addCampaign(gdccommonlargedatatypes::AddCampaignRequest const& request)
{
    LOG_INFO << "GDCAgent::addCampaign" << LOG_NOOP;
    addCampaignOutput output;

    // Diag - 0x600507 - Ids_backend_communication_unavailable
    m_receivedCampaign = true;

    if (request.signature.data.empty() && request.campaign.data.empty())
    {
        /*Activate the campaign*/
        LOG_INFO << "Empty signature & campaign data received. UUID '" << request.uuid
                 << "' is targeted for activation." << LOG_NOOP;

        if (isPersistedUUID(request.uuid.c_str()))
        {
            LOG_INFO << "Order will be activated." << LOG_NOOP;
            m_changeBEMode(EventType::CONNECTED);
            output.response.status = gdccommonlargedatatypes::Status::success;
        }
        else
        {
            LOG_INFO << "UUID not found in persistence. Setting 'response.status to: unknownUuid" << LOG_NOOP;
            output.response.status = gdccommonlargedatatypes::Status::unknownUuid;
        }
    }
    else
    {
        /*New order: Add & activate*/
        LOG_INFO << "Campaign Signature: " << request.signature.data << ", uuid: " << request.uuid << LOG_NOOP;
        CampaignConfiguration campaignConfiguration
            = configurationDeserializer(request.campaign.data, std::string(request.uuid.c_str()));

        m_changeBEMode(EventType::CONNECTED);
        m_keyId = campaignConfiguration.keyid();
        m_uuid  = campaignConfiguration.uuid();

        if (writePersistentCampaign(campaignConfiguration))
        {
            output.response.status = gdccommonlargedatatypes::Status::success;
            LOG_INFO << "valid campaign configuration" << LOG_NOOP;
        }
        else
        {
            // Storing in persistance wasnt successful.
            // TODO: Verify if 'unknownUuid' error is right
            LOG_INFO << "Setting 'response.status to: unknownUuid" << LOG_NOOP;
            output.response.status = gdccommonlargedatatypes::Status::unknownUuid;
        }
    }

    gdccommonlargedatatypes::Resource resource;
    resource.key   = 1;
    resource.value = 1;

    ::ara::core::Vector<gdccommonlargedatatypes::Resource> vecData;
    vecData.push_back(resource);
    gdccommonlargedatatypes::ResourceVector resourceVector;
    resourceVector.data      = vecData;
    output.response.response = resourceVector;

    bool const isResponseStatusSuccess{gdccommonlargedatatypes::Status::success == output.response.status};
    enableIDSCore(isResponseStatusSuccess);  // if add campaign is sucessfull we enable IDSCore, else disable IDSCore

    return createFutureOutput<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::addCampaignOutput>(
        std::move(output));
}

::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::estimateCampaignOutput>
GDCAgent::estimateCampaign(gdccommonlargedatatypes::Campaign const& campaign)
{
    LOG_INFO << "GDCAgent::estimateCampaign" << LOG_NOOP;
    (void)campaign;
    gdccommonlargedatatypes::CampaignOpResponse response{};

    // Set status
    response.status = gdccommonlargedatatypes::Status::success;

    // Set resource
    // TODO: resource values are temporary require definition
    gdccommonlargedatatypes::Resource resource;
    resource.key   = 1U;
    resource.value = 1U;

    gdccommonlargedatatypes::ResourceVector resVec;
    resVec.data.emplace_back(resource);

    response.response = resVec;

    return createFutureOutput<estimateCampaignOutput>({std::move(response)});
}


::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::getCampaignsOutput>
GDCAgent::getCampaigns()
{
    LOG_INFO << "GDCAgent::getCampaigns" << LOG_NOOP;

    getCampaignsOutput                                     output;
    gdccommonlargedatatypes::ResourceVector                resourceVector;
    ::ara::core::Vector<gdccommonlargedatatypes::Resource> vecData;

    ::ara::core::Vector<::ara::stdtypes::String> uuids;
    if (!m_uuid.empty())
    {
        uuids.push_back(m_uuid);
        LOG_INFO << "Found UUID: " << m_uuid << LOG_NOOP;
    }

    gdccommonlargedatatypes::Resource resource;
    resource.key   = 1;
    resource.value = 1;
    vecData.push_back(resource);

    resourceVector.data               = vecData;
    output.response.uuids             = uuids;
    output.response.consumedResources = resourceVector;

    return createFutureOutput<getCampaignsOutput>(std::move(output));
}

::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::getDataOutput>
GDCAgent::getData(::ara::stdtypes::String const&)
{
    LOG_INFO << "GDCAgent::getData" << LOG_NOOP;
    return createFutureOutput<getDataOutput>();
}

::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::getInfoOutput>
GDCAgent::getInfo()
{
    LOG_INFO << "GDCAgent::getInfo" << LOG_NOOP;
    getInfoOutput output;
    output.response.id = kAgentID;
    gdccommonlargedatatypes::Resource resource;

    // TODO: Decide what to send here exactly!
    resource.key   = 1;
    resource.value = 5;
    output.response.totalResources.data.push_back(resource);

    output.response.version = {
        1,
        0,
        0};  // For internal agent's usage, in order to track the agent versions. {major version, minor version, bugfix}
    output.response.abilities = gdccommonlargedatatypes::Abilities::supportsPersistentCampaigns;
    return createFutureOutput<getInfoOutput>(std::move(output));
}


::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::removeCampaignOutput>
GDCAgent::removeCampaign(::ara::stdtypes::String const& uuid)
{
    LOG_INFO << "GDCAgent::removeCampaign()" << LOG_NOOP;
    removeCampaignOutput output;

    static constexpr char DC_MASTER_SHUTDOWN_UUID[]
        = "00000000-0000-0000-0000-000000000000";  // this is a specific UUID sent by GDC to annouces agents to prepare

    if (uuid.compare(std::string(DC_MASTER_SHUTDOWN_UUID)) == 0)
    {
        LOG_DEBUG "DC Master Shutdown" << LOG_NOOP;
        output.response.status = gdccommonlargedatatypes::Status::success;
    }
    else
    {
        if (resetCampaignPersistency())
        {
            LOG_INFO << "Removed campaign configuration" << LOG_NOOP;
            output.response.status = gdccommonlargedatatypes::Status::success;
        }
        else
        {
            LOG_ERROR << "Error removing campaign configuration: " << uuid << LOG_NOOP;
            output.response.status = gdccommonlargedatatypes::Status::unknownUuid;
        }
    }


    gdccommonlargedatatypes::Resource resource;
    resource.key   = 1;
    resource.value = 1;

    ::ara::core::Vector<gdccommonlargedatatypes::Resource> vecData;
    vecData.push_back(resource);
    gdccommonlargedatatypes::ResourceVector resourceVector;
    resourceVector.data      = vecData;
    output.response.response = resourceVector;

    bool const isResponseStatusSuccess{gdccommonlargedatatypes::Status::success == output.response.status};
    enableIDSCore(!isResponseStatusSuccess);  // if remove campaign is sucessfull we disable IDSCore, else enable IDSCore

    return createFutureOutput<removeCampaignOutput>(std::move(output));
}

::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::setDataOutput>
GDCAgent::setData(gdccommonlargedatatypes::SetDataRequest const&)
{
    LOG_INFO << "GDCAgent::setData" << LOG_NOOP;
    return createFutureOutput<setDataOutput>();
}

void
GDCAgent::control(gdcgenerichugedatatypes::ControlInfo const& controlInformation)
{
    // TODO change to debug level
    LOG_INFO << "GDCAgent::control: "
             << "Ackknowledge: " << controlInformation.acknowledge
             << ", ContinueTransmission: " << controlInformation.continueTransmission << LOG_NOOP;

    m_transmissionStatus    = controlInformation.continueTransmission;
    m_acknowledgementStatus = controlInformation.acknowledge;

    switch ((m_acknowledgementStatus << 1) | m_transmissionStatus)
    {
    case 0:
        m_changeBEMode(EventType::RETRY_WITH_TIMEOUT);
        break; 
    case 1:
        m_changeBEMode(EventType::RETRY);
        break; 
    case 2:
        m_changeBEMode(EventType::ACK_OK_WITH_TIMEOUT);
        break; 
    case 3:
        m_changeBEMode(EventType::ACK_OK);
        break; 
    default:
        break;
    }

}


void
GDCAgent::initializeFromStorage()
{
    // If the storage keys doesn't exist, create them empty.
    std::vector<std::string> dbKeys;
    m_persistentMemoryManager->GetAllKeys(dbKeys);
    bool const isCampaignKeyMissing = (std::find(dbKeys.begin(), dbKeys.end(), kCampaignKey) == dbKeys.end());
    bool const isSizeKeyMissing     = (std::find(dbKeys.begin(), dbKeys.end(), kStorageSizeKey) == dbKeys.end());

    if (isCampaignKeyMissing || isSizeKeyMissing)
    {
        std::ignore = resetCampaignPersistency();
        return;
    }

    CampaignConfiguration persistentCampaign;
    if (!readCampaignFromStorage(persistentCampaign))
    {
        LOG_ERROR << "Failed to read campaign from storage" << LOG_NOOP;
        enableIDSCore(false);  // no campaign found in persistance
        return;
    }

    // If a campaign exists in persistent storage, update the key and uuid.
    if (!persistentCampaign.uuid().empty())
    {
        m_keyId = persistentCampaign.keyid();
        m_uuid  = persistentCampaign.uuid();
        enableIDSCore(true);  // there is a campaign available so IDS must be enabled
    }
}

bool
GDCAgent::readCampaignStorageSize(uint8_t& storedCampaignSize)
{
    if (!m_persistentMemoryManager->GetEntry(
            kStorageSizeKey, &storedCampaignSize, NUM_OF_BYTES_TO_REPRESENT_CAMPAIGN_SIZE))
    {
        LOG_ERROR << "Failed to read stored campaign size from storage" << LOG_NOOP;
        return false;
    }

    return true;
}

bool
GDCAgent::readCampaignFromStorage(CampaignConfiguration& persistentCampaign)
{
    uint8_t campaignSize{};
    if (!(readCampaignStorageSize(campaignSize)))
    {
        LOG_ERROR << "Can't read campaign storage size, not reading campaign" << LOG_NOOP;
        return false;
    }

    ByteVector readBuffer = ByteVector(campaignSize);
    if (!m_persistentMemoryManager->GetEntry(kCampaignKey, readBuffer.data(), campaignSize))
    {
        LOG_WARNING << "Failed to read campaign from storage" << LOG_NOOP;
    }
    else if (!persistentCampaign.ParseFromArray(readBuffer.data(), campaignSize))
    {
        LOG_ERROR << "Parsing the protocol buffer has failed" << LOG_NOOP;
        return false;
    }

    if (!persistentCampaign.uuid().empty())
    {
        LOG_INFO << "Read persistent Campaign: " << persistentCampaign.keyid() << " uuid: " << persistentCampaign.uuid()
                 << LOG_NOOP;
    }
    else
    {
        LOG_WARNING << "No campaign was found in the persistent storage" << LOG_NOOP;
    }

    return true;
}

bool
GDCAgent::writePersistentCampaign(CampaignConfiguration const& campaignConfig)
{
    const std::string campaignData{campaignConfig.SerializePartialAsString()};
    const ByteVector  valueVector(campaignData.begin(), campaignData.end());
    const uint8_t     campaignSize = static_cast<uint8_t>(valueVector.size());

    // Store Campaign's size in the persistent memory - single byte representing campaign Protobuf's size (limited to
    // 255 bytes)
    const ByteVector sizeVector{campaignSize};
    if (!(m_persistentMemoryManager->StoreEntry(kStorageSizeKey, sizeVector)))
    {
        LOG_ERROR << "Failed to store persistent campaigns size to the persistent memory" << LOG_NOOP;
        return false;
    }

    LOG_DEBUG << "Persistent campaign Protobuf's size is " << campaignSize << " bytes" << LOG_NOOP;

    if (!m_persistentMemoryManager->StoreEntry(kCampaignKey, valueVector))
    {
        LOG_ERROR << "Failed to store the campaign in the persistent memory" << LOG_NOOP;
        return false;
    }

    LOG_INFO << "Successfully stored the campaign in the persistent memory" << LOG_NOOP;

    return true;
}

bool
GDCAgent::isPersistedUUID(std::string const& uuid) const
{
    LOG_INFO << "GDCAgentBase::isPersistedUUID()" << LOG_NOOP;

    if (uuid != m_uuid)
    {
        LOG_WARNING << "UUID doesn't match, given: " << uuid << ", persistent: " << m_uuid << LOG_NOOP;
        return false;
    }

    return true;
}

CampaignConfiguration
GDCAgent::configurationDeserializer(ByteVector gdcCampaignData, std::string const& uuid) const
{
    CampaignConfiguration result;
    /*Parse a protocol buffer contained in an array of bytes*/
    if (!result.ParseFromArray(gdcCampaignData.data(), static_cast<int>(gdcCampaignData.size())))
    {
        LOG_WARNING << "Parsing the protocol buffer has failed" << LOG_NOOP;
    }
    result.set_uuid(uuid);
    LOG_DEBUG << "Parsed new campaign key_id: " << result.keyid() << ", uuid: " << result.uuid() << LOG_NOOP;

    return result;
}

void
GDCAgent::enableIDSCore(bool status)
{
    if (!m_isFeatureDisabled)
    {
        if (status != m_isIDSCoreEnabled)
        {
            auto* app = brain::app_mng::BrainApp::GetInstance();
            if ((nullptr != app) && app->GetIdsEnableDisableClass())
            {
                app->GetIdsEnableDisableClass()->SetMode(status);
                m_isIDSCoreEnabled = status;
            }
            else
            {
                LOG_WARNING << "Unable to change the IDS mode, BrainApp is not initialized" << LOG_NOOP;
            }
        }
        else
        {
            LOG_INFO << "IDS is already in the status " << (m_isIDSCoreEnabled ? "enabled" : "disabled") << LOG_NOOP;
        }
    }
}


bool
GDCAgent::resetCampaignPersistency()
{
    m_keyId = 0U;
    m_uuid  = "";

    if (!writePersistentCampaign(CampaignConfiguration()))
    {
        LOG_ERROR << "Could not reset campaigns in the storage" << LOG_NOOP;
        return false;
    }

    return true;
}