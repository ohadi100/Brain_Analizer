/**
 * @file
 * @brief The implementation of the skeleton of the GdcAgentCommonLarge & GenericLarge interfaces.
 */
#ifndef GDC_AGENT_HPP
#define GDC_AGENT_HPP

#include <ara/com/types.h>
#include <ara/core/future.h>
#include <atomic>
#include <factory/PersistentMemoryFactory.hpp>
#include "CampaignConfiguration/CampaignConfiguration.pb.h"
#include "Utils/araUtils.hpp"
#include "ara/stdtypes/impl_type_string.h"
#include "ara/stdtypes/impl_type_uint32.h"
#include "ara/stdtypes/impl_type_uint8.h"
#include "brain/diagnostics/dtc/DtcEvent.hpp"
#include "brain/generated/vwg/services/connect/datacollector/odcagentcommonlarge/odcagentcommonlarge_skeleton.h"
#include "brain/generated/vwg/services/connect/datacollector/odcagentgenerichuge/odcagentgenerichuge_skeleton.h"  // Located in our codebase (taken from DRM)
#include "common/notification_handler/DataArrivedEvent.hpp"
#include "interface/PersistentMemoryManagerInterface.hpp"
#include "sender/publishers/interface/PublisherInterface.hpp"


namespace gdccommonlargeskeleton  = ::vwg::services::connect::datacollector::odcagentcommonlarge::skeleton;
namespace gdccommonlargedatatypes = ::vwg::services::connect::datacollector::odcagentcommonlarge;
namespace gdcgenerichugeskeleton  = ::vwg::services::connect::datacollector::odcagentgenerichuge::skeleton;
namespace gdcgenerichugedatatypes = ::vwg::services::connect::datacollector::odcagentgenerichuge;


namespace brain
{
namespace publishers
{
namespace agents
{

static constexpr char kGdcCommonLargeInstance[] = "OdcAgentCommonLarge5";
static constexpr char kGdcGenericHugeInstance[] = "OdcAgentGenericHuge5";
static int const      kAgentID                  = 0x2140;  // Our agent Id
static size_t const   kMaxChunkSize             = (1024 * 1024);
static constexpr char PM_DB[]                   = "ids_ppe_gdc";
static constexpr char kCampaignKey[]            = "CAMPAIGNS";
static constexpr char kStorageSizeKey[]         = "CAMPAIGNS_STORAGE_SIZE";
static constexpr char kUuidKey[]                = "UUID";
static constexpr char kConfigsKey[]             = "ConfigString";
static constexpr char kKeyID[]                  = "KeyID";
// Campaigns JSON is storage is around 75 bytes in size. A single byte is enough to represent a size of up to 255 bytes.
// For example, { "CAMPAIGNS": [ { "UUID": "78e484e6-f638-52ec-ada5-d865b08814ce", "KeyID": 13579 } ] } is 77 bytes.
// Campaigns Protobuf in storage is around 43 bytes in size.
static constexpr uint8_t NUM_OF_BYTES_TO_REPRESENT_CAMPAIGN_SIZE = 1;

using PersistentMemoryFactory             = std::shared_ptr<common::memory::PersistentMemoryFactory>;
using PersistentMemoryManagerInterfacePtr = std::shared_ptr<common::memory::PersistentMemoryManagerInterface>;
using ByteVector                          = std::vector<std::uint8_t>;

/**
 * @brief The implementation of the skeleton of the GDCAgentCommonLarge & GenericLarge interfaces.
 */
class GDCAgent
  : public gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton
  , public gdcgenerichugeskeleton::OdcAgentGenericHugeSkeleton
{

public:
    using EventType = PublisherInterface::EventType;
    using ChangeModeCallback = std::function<void(EventType)>;

    /**
     * @brief Construct the GDC Agent Common Large Skeleton Impl object.
     */
    GDCAgent(std::shared_ptr<common::memory::PersistentMemoryFactory> memoryFactory);

    void InitCallback(ChangeModeCallback changeBEMode);
    /**
     * @brief Destroy the GDC Agent Common Large Skeleton Impl object.
     */
    ~GDCAgent();

    /**
     * @brief    default copy constructor
     */
    GDCAgent(const GDCAgent& other) = delete;

    /**
     * @brief    default move constructor
     */
    GDCAgent(GDCAgent&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    GDCAgent& operator=(GDCAgent const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    GDCAgent& operator=(GDCAgent&&) = delete;

    /**
     * @brief Start offering the SOME/IP services.
     *        Called from PublisherBase::Init().
     */
    void OfferService();

    /**
     * @brief Stop offering the SOME/IP services.
     *        Called from PublisherBase destructor.
     */
    void StopOfferService();

    /**
     * @brief Estimate the GDC campaigns resources
     */
    virtual ::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::estimateCampaignOutput> estimateCampaign(
        gdccommonlargedatatypes::Campaign const& campaign) override;

    /**
     * @brief Get campaigns and resource consumption
     */
    virtual ::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::getCampaignsOutput> getCampaigns()
        override;

    /**
     * @brief
     *
     * @param resource
     * @return ::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::getDataOutput>
     */
    virtual ::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::getDataOutput> getData(
        ::ara::stdtypes::String const& resource) override;

    /**
     * @brief Handle remove campaign the persistent storage request
     *
     * @param uuid
     * @return ::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::removeCampaignOutput>
     */
    virtual ::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::removeCampaignOutput> removeCampaign(
        ::ara::stdtypes::String const& uuid) override;

    /**
     * @brief Set the data request
     *
     * @param request
     * @return ::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::setDataOutput>
     */
    virtual ::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::setDataOutput> setData(
        gdccommonlargedatatypes::SetDataRequest const& request) override;

    /**
     * @brief SOME/IP interface function.
     *
     * Add the campaign to the agent's configuration.
     * If another campaign already exists, it is replaced with the new campaign.
     * @param request (AddCampaignRequest) is Request data with campaigns UUID, signature, and payload
     * @return ::ara::core::Future<addCampaignOutput>
     */
    virtual ::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::addCampaignOutput> addCampaign(
        gdccommonlargedatatypes::AddCampaignRequest const& request) override;

    /**
     * @brief GetInfo output
     *
     * @return ::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::getInfoOutput>
     */
    virtual ::ara::core::Future<gdccommonlargeskeleton::OdcAgentCommonLargeSkeleton::getInfoOutput> getInfo() override;

    /**
     * @brief Enables GDCMaster to modify flow control behavior. Defined in GenericHuge's interface.
     *
     * @param controlInformation - struct contanining flow control flags
     */
    virtual void control(gdcgenerichugedatatypes::ControlInfo const& controlInformation) override;

    /**
     * @brief resets GenericHuge data sending status
     *
     * @param none
     * @return none
     */
    inline void
    ResetStatusFlags()
    {
        m_transmissionStatus    = false;
        m_acknowledgementStatus = false;
    }

    /**
     * @brief m_acknowledgementStatus getter
     * @param none
     * @return bool
     */
    inline bool
    GetAcknowledgementStatus() const noexcept
    {
        return m_acknowledgementStatus;
    }

    /**
     * @brief m_transmissionStatus getter

     * @param none
     * @return bool
     */
    inline bool
    GetTransmissionStatus() const noexcept
    {
        return m_transmissionStatus;
    }

    /**
     * @brief   set GDCMaster send permission
     * @param   bool
     * @return  void
     */
    inline void
    SetGDCMasterPermitsSend(bool gdcMasterPermitsSend)
    {
        m_gdcMasterPermitsSend = gdcMasterPermitsSend;
    }

    /**
     * @brief   get GDCMaster send permission
     * @return  bool
     */
    inline bool
    GetGDCMasterPermitsSend()
    {
        return m_gdcMasterPermitsSend;
    }

    /**
     * @brief   get keyId
     * @return  uint32_t
     */
    inline uint32_t
    GetKeyId()
    {
        return m_keyId;
    }

    /**
     * @brief   get flow control status arrived ptr
     * @return  bool
     */
    inline std::shared_ptr<common::notification_handler::DataArrivedEvent>
    GetFlowControlStatusArrived()
    {
        return m_flowControlStatusArrived;
    }

private:
    ChangeModeCallback m_changeBEMode;
    std::shared_ptr<common::notification_handler::DataArrivedEvent> m_flowControlStatusArrived;
    bool     m_transmissionStatus{false};     // enable or disable the posibility to send data
    bool     m_acknowledgementStatus{false};  // status of the last command sent
    bool     m_receivedCampaign{false};       // flag to show the if a campaign was received
    uint32_t m_keyId{0U};
    bool m_gdcMasterPermitsSend{false};  // Agent is only allowed to send data between addCampaign() and removeCampaign()
    bool m_isIDSCoreEnabled{true};      // if there are no campaign available the IDS must be disable
    bool m_isFeatureDisabled{false};    // feature is disabled in case is specified in the config file
    brain::diagnostics::dtc::DtcEvent
                m_backendCommunicationDtc;  // Diag DTC - 0x600507 - ids_backend_communication_unavailable
    std::string m_uuid;
    PersistentMemoryManagerInterfacePtr m_persistentMemoryManager;

    /**
     * @brief Enable/Disable IDS
     *
     * @param status if set to true, the IDS Core will be enabled, if set to false IDS Core will be disabled
     */
    void enableIDSCore(bool status);

    CampaignConfiguration configurationDeserializer(ByteVector gdcCampaignData, std::string const& uuid) const;

    /**
     * @brief Read the campaign configurations value from the persistent storage
     *
     * @param persistentCampaign OUT parameter for the campaigns
     * @return true if successfully read from storage and stored in `campaigns` else false
     */
    bool readCampaignFromStorage(CampaignConfiguration& persistentCampaign);

    /**
     * @brief Read the campaign configurations size from the persistent storage
     *
     * @param storedCampaignSize OUT parameter for the campaigns protobuf size
     * @return true if successfully read from storage and stored in `storedCampaignsize` else false
     */
    bool readCampaignStorageSize(uint8_t& storedCampaignSize);

    /**
     * @brief Write the campaign configuration in the persistent storage
     *
     * @param campaignConfig - The data of the campaign configuration to store.
     *                     Can be empty to represent that no campaign currently exists.
     * @return true if successfully written to storage else false
     */
    bool writePersistentCampaign(CampaignConfiguration const& campaignConfig);

    /**
     * @brief Checks if the given UUID is equal to the UUID in persistence.
     *
     * @param uuid The uuid to check if exists in storage.
     * @return true if uuid matches to persistance, else false.
     */
    bool isPersistedUUID(std::string const& uuid) const;

    /**
     * @brief Initializes campaign data from the storage.
     */
    void initializeFromStorage();

    /**
     * @brief resets Campaign persistency with an empty buffer.
     *
     * @return true if success, else false.
     */
    bool resetCampaignPersistency();
};

} /* namespace agents */
} /* namespace publishers */
} /* namespace brain */

#endif /* GDC_AGENT_HPP */
