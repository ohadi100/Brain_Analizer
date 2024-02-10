/**
 * @file
 * @brief     This file contains the functionality of the DiagFeatureFlags class
 */
#include "DiagFeatureFlags.hpp"
#include <cstring>

using brain::adaptation_values_names::AdaptationId;
using brain::diagnostics::diag_accessor::DiagFeatureFlags;
using vwg::dal::Enablinganddisablingspecificfeatures;
using vwg::dal::IntrusionDetectionSystem;
using vwg::dal::Intrusiondetectionsystemactivationstate;


// Diag Adaptations - 0x7704
std::array<DiagFeatureFlags::CallbackFunc, DiagFeatureFlags::SPECIFIC_FEATURE_COUNT>
    DiagFeatureFlags::m_specificFeatureHandlers = {
        createUpdateFeatureCallback(
            &vwg::dal::GeneratedDiagnosticAccessor::getEnablinganddisablingspecificfeaturesLinkutilizationmonitoringOn,
            AdaptationId::LINK_UTILIZATION_MONITORING_ON),
        createUpdateFeatureCallback(&vwg::dal::GeneratedDiagnosticAccessor::
                                        getEnablinganddisablingspecificfeaturesBroadcastmulticastratesmonitoringOn,
                                    AdaptationId::BROADCAST_MULTICAST_RATES_MONITORING_ON),
        createUpdateFeatureCallback(
            &vwg::dal::GeneratedDiagnosticAccessor::getEnablinganddisablingspecificfeaturesDiscardedframesmonitoringOn,
            AdaptationId::DISCARDED_FRAMES_MONITORING_ON),
        createUpdateFeatureCallback(
            &vwg::dal::GeneratedDiagnosticAccessor::getEnablinganddisablingspecificfeaturesIPtrafficmonitoringOn,
            AdaptationId::IP_TRAFFIC_MONITORING_ON),
        createUpdateFeatureCallback(
            &vwg::dal::GeneratedDiagnosticAccessor::getEnablinganddisablingspecificfeaturesTLSsessionsmonitoringOn,
            AdaptationId::TLS_SESSIONS_MONITORING_ON),
        createUpdateFeatureCallback(
            &vwg::dal::GeneratedDiagnosticAccessor::getEnablinganddisablingspecificfeaturesMonitoringofprocessesOn,
            AdaptationId::MONITORING_OF_PROCESSES_ON),
        createUpdateFeatureCallback(
            &vwg::dal::GeneratedDiagnosticAccessor::getEnablinganddisablingspecificfeaturesOSmonitoringOn,
            AdaptationId::OS_MONITORING_ON),
        createUpdateFeatureCallback(
            &vwg::dal::GeneratedDiagnosticAccessor::getEnablinganddisablingspecificfeaturesFilemonitoringOn,
            AdaptationId::FILE_MONITORING_ON),
        createUpdateFeatureCallback(
            &vwg::dal::GeneratedDiagnosticAccessor::getEnablinganddisablingspecificfeaturesHosterrormonitoringOn,
            AdaptationId::HOST_ERROR_MONITORING_ON),
        createUpdateFeatureCallback(
            &vwg::dal::GeneratedDiagnosticAccessor::getEnablinganddisablingspecificfeaturesServicelevelmonitoringOn,
            AdaptationId::SERVICE_LEVEL_MONITORING_ON),
};

DiagFeatureFlags::DiagFeatureFlags(IdsEnablerPtr idsEnabler)
  : m_dalState(vwg::dal::State::kNotReady)
  , m_idsEnabler(idsEnabler)
  , m_dataImplausibleDtc(ids_evt_DataSet0x7231)
{
    // Sets all features to true by default
    for (uint8_t featureId = 0U; featureId < AdaptationId::ADAPTATIONS_COUNT; featureId++)
    {
        m_featureFlags[featureId] = true;
    }
#ifndef SSP_PLATFORM
    RegisterDiagAccessor(); // Casue 2.0 to be stack, will be handle when we use the real diag library of 2.0
#endif    
}

DiagFeatureFlags::~DiagFeatureFlags()
{
    try
    {
        m_diagnosticAccessor.removeErrorCallback();
        m_diagnosticAccessor.removeStateChangedCallback();
        std::ignore = m_diagnosticAccessor.removeHashChangedCallback();
        LOG_DEBUG << "DiagFeatureFlags destructor end" << LOG_NOOP;
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "destruction of the DiagFeatureFlags failed and got exception." << LOG_NOOP;
    }  // only for parasoft violations
}

void
DiagFeatureFlags::RegisterDiagAccessor()
{
    m_diagnosticAccessor.setErrorCallback([](vwg::dal::Error const& err) {
        LOG_WARNING << "DiagnosticAccessor error callback: " << static_cast<uint8_t>(err.getResultCode()) << " - "
                    << err.getDescription().c_str() << LOG_NOOP;
    });

    static constexpr uint32_t WAIT_FOR_DSA_TIMEOUT{5U * 1000U};

    auto const initResult = m_diagnosticAccessor.init(vwg::dal::CacheEnable{true}, WAIT_FOR_DSA_TIMEOUT);

    if (vwg::dal::ResultCode::kNoError != initResult.getResultCode())
    {
        LOG_WARNING << "Could not initialize GeneratedDiagnosticAccessor: " << initResult.getDescription().c_str()
                    << LOG_NOOP;
        return;
    }

    m_dalState = m_diagnosticAccessor.getState();

    LOG_INFO << "GeneratedDiagnosticAccessor has been initialized and connected to DSA with status "
             << static_cast<int>(initResult.getResultCode()) << " - " << initResult.getDescription().c_str()
             << " and state " << static_cast<int>(m_diagnosticAccessor.getState()) << LOG_NOOP;

    static_cast<void>(m_diagnosticAccessor.setHashChangedCallback(std::bind(&DiagFeatureFlags::hashChangedCallback,
                                                                            this,
                                                                            std::placeholders::_1,
                                                                            std::placeholders::_2,
                                                                            std::placeholders::_3)));

    m_diagnosticAccessor.setStateChangedCallback([this](vwg::dal::State state) {
        LOG_INFO << "DAL Connection Status Change: " << static_cast<int>(state) << LOG_NOOP;
        m_dalState = state;
        LoadDiagnosticData();
    });
}

void
DiagFeatureFlags::hashChangedCallback(vwg::dal::HashType const&,
                                      vwg::dal::DiagnosticDataNamespace diagDataNamespace,
                                      vwg::dal::DataIds const&          changedDids)
{
    if (m_dalState != vwg::dal::State::kReadyAndSynchronized)
    {
        LOG_WARNING << "DAL state is not kReadyAndSynchronized" << LOG_NOOP;
        return;
    }

    switch (diagDataNamespace)
    {
    case vwg::dal::DiagnosticDataNamespace::kAdaption:
        this->adaptationHashChangedCallback(changedDids);
        break;
    case vwg::dal::DiagnosticDataNamespace::kDataSet:
        this->dataSetHashChangedCallback(changedDids);
        break;
    default:
        break;
    }
}

void
DiagFeatureFlags::adaptationHashChangedCallback(vwg::dal::DataIds const& changedDids)
{
    for (auto const& changedDid : changedDids)
    {
        switch (changedDid)
        {
        case Enablinganddisablingspecificfeatures::getDid():
            // Diag - 0x7704
            LOG_INFO << "Doing EnablinganddisablingSpecificfeatures adaptation action" << LOG_NOOP;
            handleEnablingSpecificFeaturesAdaption();
            break;
        case Intrusiondetectionsystemactivationstate::getDid():
            // Diag - 0x032e
            LOG_INFO << "Doing Intrusiondetectionsystemactivationstate adaptation action" << LOG_NOOP;
            handleIntrusionDetectionSystemAdaptation();
            break;
        default:
            break;
        }
    }
}

void
DiagFeatureFlags::dataSetHashChangedCallback(vwg::dal::DataIds const& changedDids)
{
    for (auto const& changedDid : changedDids)
    {
        if (changedDid == IntrusionDetectionSystem::getDid())
        {
            // Diag - 0x7231
            LOG_INFO << "Doing IntrusionDetectionSystem dataSet action" << LOG_NOOP;
            handleIntrusionDetectionSystemDataSet();
        }
    }
}

void
DiagFeatureFlags::handleEnablingSpecificFeaturesAdaption()
{
    for (auto const& featureHandler : m_specificFeatureHandlers)
    {
        featureHandler(*this);
    }
}

void
DiagFeatureFlags::updateSpecificFeature(vwg::dal::Either<vwg::dal::Error, bool> specificFeatureResult,
                                        AdaptationId const                      adaptationId)
{
    static std::array<std::string, AdaptationId::ADAPTATIONS_COUNT> const adaptationNames
        = {"link_utilization_monitoring_on",
           "broadcast_multicast_rates_monitoring_on",
           "discarded_frames_monitoring_on",
           "ip_traffic_monitoring_on",
           "tls_sessions_monitoring_on",
           "monitoring_of_processes_on",
           "os_monitoring_on",
           "file_monitoring_on",
           "host_error_monitoring_on",
           "service_level_monitoring_on",
           "diagnostics_enable_disable_status"};

    std::string const& adaptationName = adaptationNames[adaptationId];

    auto onErrorHandler = [&adaptationName](vwg::dal::Error const& error) -> bool {
        LOG_ERROR << "Couldn't get getEnablinganddisablingSpecificfeatures " << adaptationName.c_str()
                  << " output. Error code: " << static_cast<uint8_t>(error.getResultCode()) << ", Using default value"
                  << LOG_NOOP;
        return false;
    };

    auto onValueHandler = [this, &adaptationName, adaptationId](bool const& featureEnabledStatus) -> bool {
        bool const featureEnabledCurrentStatus = m_featureFlags[adaptationId];

        // Updates adaptation state value
        if ((featureEnabledStatus != featureEnabledCurrentStatus))
        {
            LOG_INFO << "Adaptation Specific feature " << adaptationName.c_str() << " is set to "
                     << (featureEnabledStatus ? "enabled" : "disabled") << LOG_NOOP;
            m_featureFlags[adaptationId] = featureEnabledStatus;
        }

        return true;
    };

    std::ignore = specificFeatureResult.onError(onErrorHandler).onValue(onValueHandler).join();
}

void
DiagFeatureFlags::handleIntrusionDetectionSystemAdaptation()
{
    auto onErrorHandler = [](vwg::dal::Error const& error) -> bool {
        LOG_ERROR
            << "Couldn't get getIntrusiondetectionsystemactivationstateEnablinganddisablingIDSOn output. Error code: "
            << static_cast<uint8_t>(error.getResultCode()) << ", Using default value" << LOG_NOOP;
        return false;
    };
    auto onValueHandler = [this](bool const& idsMode) -> bool {
        updateIdsMode(idsMode);
        return true;
    };

    auto adaptionResult = m_diagnosticAccessor.getIntrusiondetectionsystemactivationstateEnablinganddisablingIDSOn();
    std::ignore         = adaptionResult.onError(onErrorHandler).onValue(onValueHandler).join();
}

void
DiagFeatureFlags::handleIntrusionDetectionSystemDataSet()
{
    auto onErrorHandler = [](const vwg::dal::Error& error) -> bool {
        LOG_ERROR << "Could not get IntrusionDetectionSystem diagnostic data. Error code: "
                  << static_cast<uint8_t>(error.getResultCode()) << ", Using default value" << LOG_NOOP;
        return false;
    };

    auto onValueHandler
        = std::bind(&DiagFeatureFlags::parseIntrusionDetectionSystemDataSet, this, std::placeholders::_1);

    auto diagnosticsData       = m_diagnosticAccessor.getDiagnosticData(vwg::dal::DiagnosticDataNamespace::kDataSet,
                                                                  {IntrusionDetectionSystem::getDid()});
    bool dataSetHandlerSuccess = diagnosticsData.onError(onErrorHandler).onValue(onValueHandler).join();

    // Diag DTC - 0x600500 - data_implausible
    m_dataImplausibleDtc.SetEvent(!dataSetHandlerSuccess);
}

bool
DiagFeatureFlags::parseIntrusionDetectionSystemDataSet(vwg::dal::DiagnosticData const& value)
{
    static constexpr size_t DATASET_TOTAL_SIZE{128U};

    if (DATASET_TOTAL_SIZE != value.size())
    {
        LOG_WARNING << "DataSet invalid size: " << value.size() << ", expected: " << DATASET_TOTAL_SIZE << LOG_NOOP;
        return false;
    }

    uint32_t                  version{0U};
    static constexpr size_t   DATASET_VERSION_OFFSET{0U};
    static constexpr uint32_t DATASET_VERSION{0x58303031U};

    std::ignore = std::memcpy(&version, &value[DATASET_VERSION_OFFSET], sizeof(uint32_t));
    if (DATASET_VERSION != version)
    {
        LOG_WARNING << "DataSet data has invalid version: " << version << " expected: " << DATASET_VERSION << LOG_NOOP;
        return false;
    }

    static constexpr size_t DATASET_DATA_OFFSET{16U};

    updateIdsMode(static_cast<bool>(value[DATASET_DATA_OFFSET]));

    return true;
}

void
DiagFeatureFlags::updateIdsMode(bool const idsMode)
{
    m_featureFlags[AdaptationId::DIAGNOSTICS_IDS_ENABLED] = idsMode;

    if (nullptr == m_idsEnabler)
    {
        LOG_WARNING << "Can't update ids mode, idsEnabler is nullptr" << LOG_NOOP;
        return;
    }

    LOG_INFO << "update ids mode " << idsMode << LOG_NOOP;
    m_idsEnabler->ChangeMode(idsMode);
}

void
DiagFeatureFlags::LoadDiagnosticData()
{
    if (vwg::dal::State::kReadyAndSynchronized == m_dalState)
    {
        LOG_DEBUG << "Loading diagnositc data" << LOG_NOOP;
        handleEnablingSpecificFeaturesAdaption();
        handleIntrusionDetectionSystemAdaptation();
    }
}