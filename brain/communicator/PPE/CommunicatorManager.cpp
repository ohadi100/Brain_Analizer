/**
 * @file
 * @brief     This file contains the functionality of the CommunicatorManager class
*/
#if defined (EEE_PLATFORM) || defined (LINUX)
#include <tuple>
#endif // defined (EEE_PLATFORM) || defined (LINUX)

#include <tuple>
#include "CommunicatorManager.hpp"
#include "communicator/periodic/PeriodicReportCommunicator.hpp"
#include "brain/brain_app/BrainApp.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "brain/diagnostics/PPE/AdaptationValuesConstants.hpp"
#include "brain/noise_filter/sensor_noise_filter/SensorNoiseFilter.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/counter_manager/CounterManager.hpp"

#ifdef EEE_PLATFORM
#include "someip/GSDPCommunicator.hpp"
using brain::brain_communicator::someip::gsdp::GSDPCommunicator;
#include "someip/SecurityEventSmall.hpp"
using brain::brain_communicator::someip::idssecurityeventsmall::IDSSecurityEventSmallCommunicator;
#include "someip/SecurityEventNormal.hpp"
using brain::brain_communicator::someip::idssecurityeventnormal::IDSSecurityEventNormalCommunicator;
#include "brain/communicator/diagdata/DiagDataCommunicator.hpp"
using brain::brain_communicator::diagdata_communicator::DiagDataCommunicator;
#endif // EEE_PLATFORM

#include "uds/UDSCommunicator.hpp"
#include "brain/communicator/sci/SciCommunicator.hpp"
#include "brain/sensor_data/swpac/SwpacSensorDataBase.hpp"

using brain::brain_communicator::uds::UDSCommunicator;
using brain::brain_communicator::sci_communicator::SciCommunicator;
using brain::app_mng::BrainApp;
using brain::brain_communicator::CommunicatorManager;
using common::configuration::Configuration;
using brain::brain_communicator::periodic::PeriodicReportCommunicator;
using brain::brain_noise_filter::NoiseFilter;
using brain::brain_noise_filter::SensorNoiseFilter;


CommunicatorManager::CommunicatorManager(SensorDataQueuesManagerPtr queuesManager,
                                         ConfigurationPtr           config,
                                         CounterManagerPtr          debugCounters,
                                         TimerPtr                   timer,
                                         DiagnosticsManagerPtr      diagnosticsManager)
  : m_queuesManager(queuesManager)
  , m_configuration(config)
  , m_debugCounters(debugCounters)
  , m_diagManager(diagnosticsManager)
  , m_timer(timer)
  , m_someipTimerKey(0U)
{
}

void CommunicatorManager::RegisterAllNotificationHandlers()
{
    LOG_INFO << "Registering all notifications" << LOG_NOOP;

    if (!m_comms.empty())
    {
        LOG_ERROR << "Deregistering dangling communicators: " << m_comms.size() << LOG_NOOP;
        auto it = m_comms.begin();
        while (m_comms.end() != it)
        {
            auto& comm = *it;
            comm->Stop();
            it = m_comms.erase(it);  // call the dtor
        }
        LOG_ERROR << "Done: " << m_comms.size() << LOG_NOOP;
    }

    auto periodicComm = std::make_unique<PeriodicReportCommunicator>(
        m_queuesManager, m_debugCounters, m_configuration, m_timer);
    periodicComm->Start();
    m_comms.emplace_back(std::move(periodicComm));

    auto sensorNoiseFilter = std::make_shared<SensorNoiseFilter>(m_debugCounters, m_configuration);
    static constexpr uint32_t defaultPeriodicReportFlushThreshold = 1U;
    uint32_t flushThreshold = defaultPeriodicReportFlushThreshold;

#ifdef EEE_PLATFORM
    // incidence registration

    std::string vehicleType;
    if (!m_configuration->GetValue(brain::config_keys::VEHICLE_TYPE, vehicleType) || vehicleType.empty())// !already set
     {
        // Diag Data communicator
        LOG_INFO << "Creating DiagData Service" << LOG_NOOP;
        auto DiagDataProvider = std::make_unique<DiagDataCommunicator>(m_queuesManager, flushThreshold,m_configuration, sensorNoiseFilter);
        DiagDataProvider->Start();
        m_comms.emplace_back(std::move(DiagDataProvider));
    }
    else
    {
        LOG_DEBUG << "Vehicle Type exist " << vehicleType << LOG_NOOP;
    }
    // GSDP communicator
    bool isGSDPCommunicatorstatusEnabled = true;
    std::ignore = m_configuration->GetValue(brain::config_keys::GSDP_COMMUNICATOR_STATUS, isGSDPCommunicatorstatusEnabled);

    if (isGSDPCommunicatorstatusEnabled)
    {
        static constexpr uint32_t defaultGSDPFlushThreshold = 1U;
        flushThreshold = defaultGSDPFlushThreshold;
        std::ignore = m_configuration->GetValue(brain::config_keys::GSDP_FLUSH_THRESHOLD, flushThreshold);

        LOG_INFO << "Creating GSDP Incidence Service" << LOG_NOOP;
        auto GSDPIncidentProvider = std::make_unique<GSDPCommunicator>(
            m_queuesManager, m_debugCounters, flushThreshold, m_diagManager ,sensorNoiseFilter);
        GSDPIncidentProvider->Start();
        m_comms.emplace_back(std::move(GSDPIncidentProvider));

        std::ignore = m_configuration->GetValue(brain::config_keys::MAXIMUM_SIZE_STRING_TYPE, brain::sensor_data::SwpacSensorDataBase::MaximumSizeStringType);
    }
    else
    {
        LOG_INFO << "GSDP Communicator Disabled" << LOG_NOOP;
    }

    // SecurityEventSmall communicator
    std::vector<uint32_t> enabledInstances;
    
    bool isSESmallCommunicatorstatusEnabled = true;
    std::ignore = m_configuration->GetValue(brain::config_keys::SE_SMALL_COMMUNICATOR_STATUS, isSESmallCommunicatorstatusEnabled);

    if (isSESmallCommunicatorstatusEnabled)
    {
        LOG_INFO << "Creating IDSSecurityEventSmall service" << LOG_NOOP;
        static constexpr uint32_t defaultSecurityEventSmallFlushThreshold = 1U;
        flushThreshold = defaultSecurityEventSmallFlushThreshold;
        std::ignore = m_configuration->GetValue(brain::config_keys::SECURITY_EVENT_SMALL_FLUSH_THRESHOLD, flushThreshold);
        enabledInstances.clear();
        std::ignore = m_configuration->GetValue(brain::config_keys::COMM_SE_SMALL_INSTANCES, enabledInstances);

        LOG_INFO << "Creating IDSSecurityEventSmall Incidence Service" << LOG_NOOP;
        auto SecurityEventSmallIncidentProvider = std::make_unique<IDSSecurityEventSmallCommunicator>(
            m_queuesManager, m_debugCounters, flushThreshold, m_diagManager, enabledInstances,
            sensorNoiseFilter);
        SecurityEventSmallIncidentProvider->Start();
        m_comms.emplace_back(std::move(SecurityEventSmallIncidentProvider));
    }
    else
    {
        LOG_INFO << "IDSSecurityEventSmall Communicator Disabled" << LOG_NOOP;
    }

    // SecurityEvent communicator
    bool isSENormalCommunicatorstatusEnabled = true;
    std::ignore = m_configuration->GetValue(brain::config_keys::SE_NORMAL_COMMUNICATOR_STATUS, isSENormalCommunicatorstatusEnabled);
    
    if (isSENormalCommunicatorstatusEnabled)
    {
        enabledInstances.clear();
        std::ignore = m_configuration->GetValue(brain::config_keys::COMM_SE_NORMAL_INSTANCES, enabledInstances);
        LOG_INFO << "Creating IDSSecurityEventNormal service" << LOG_NOOP;
        static constexpr uint32_t defaultSecurityEventNormalFlushThreshold = 1U;
        flushThreshold = defaultSecurityEventNormalFlushThreshold;
        std::ignore = m_configuration->GetValue(brain::config_keys::SECURITY_EVENT_NORMAL_FLUSH_THRESHOLD, flushThreshold);

        LOG_INFO << "Creating IDSSecurityEventNormal Incidence Service" << LOG_NOOP;
        auto SecurityEventNormalIncidentProvider = std::make_unique<IDSSecurityEventNormalCommunicator>(
            m_queuesManager, m_debugCounters, flushThreshold, m_diagManager , enabledInstances, sensorNoiseFilter);
        SecurityEventNormalIncidentProvider->Start();
        m_comms.emplace_back(std::move(SecurityEventNormalIncidentProvider));
    }
    else
    {
        LOG_INFO << "IDSSecurityEventNormal Communicator Disabled" << LOG_NOOP;
    }

    // Sacid communicator
    bool isSacidCommunicatorstatusEnabled = true;
    std::ignore = m_configuration->GetValue(brain::config_keys::SACID_COMMUNICATOR_STATUS, isSacidCommunicatorstatusEnabled);
    
    if (isSacidCommunicatorstatusEnabled)
    {
        LOG_INFO << "Creating SCI Service" << LOG_NOOP;
        auto SCIProvider = std::make_unique<SciCommunicator>(m_queuesManager, m_debugCounters, flushThreshold, sensorNoiseFilter);
        SCIProvider->Start();
        m_comms.emplace_back(std::move(SCIProvider));
    }
    else
    {
        LOG_INFO << "Sacid Communicator Disabled" << LOG_NOOP;
    }


    static constexpr uint64_t defaultSomeIPSamplingInterval = 1U;
    uint64_t sampleInterval = defaultSomeIPSamplingInterval;
    std::ignore = m_configuration->GetValue(brain::config_keys::SOMEIP_SAMPLE_HANDLING_INTERVAL, sampleInterval);
    setPeriodicSomeIPHandling(sampleInterval);

#endif // EEE_PLATFORM

    LOG_INFO << "Checking should create UDS Incidence Service" << LOG_NOOP;
    bool isUDSCommunicatorEnabled = true;
    std::ignore = m_configuration->GetValue(brain::config_keys::UDS_COMMUNICATOR_STATUS, isUDSCommunicatorEnabled);

    if (isUDSCommunicatorEnabled)
    {
        LOG_INFO << "Creating UDS Incidence Service" << LOG_NOOP;
        std::string       udsPathName;
        std::string const udsPathString =
#ifdef SIMULATION
            brain::config_keys::UDS_PATH_SIMULATION;
#else
            brain::config_keys::UDS_PATH;
#endif
        if (m_configuration->GetValue(udsPathString, udsPathName))
        {
            LOG_INFO << "Reading uds path name [" << udsPathName << "] from configuration succeeded" << LOG_NOOP;

            auto UDSIncidentProvider = std::make_unique<UDSCommunicator>(m_queuesManager,
                                                                             udsPathName,
                                                                             m_debugCounters,
                                                                             flushThreshold,
                                                                             m_diagManager,
                                                                             sensorNoiseFilter);
            LOG_VERBOSE << "UDSIncidentProvider is starting" << LOG_NOOP;
            UDSIncidentProvider->Start();
            LOG_INFO << "UDSIncidentProvider started successfully" << LOG_NOOP;
            m_comms.emplace_back(std::move(UDSIncidentProvider));
        }
        else
        {
            LOG_INFO << "UDS Communicator Disabled" << LOG_NOOP;
        }
    }
    else
    {
        LOG_INFO << "UDS Communicator already created" << LOG_NOOP;
    }
}

#ifdef EEE_PLATFORM
void CommunicatorManager::setPeriodicSomeIPHandling(uint64_t const interval)
{
    if (nullptr == m_timer)
    {
        LOG_WARNING << "Timer is null, can't set periodic someip sample handling" << LOG_NOOP;
        return;
    }

    // Deregister previous periodic function
    if (0U != m_someipTimerKey)
    {
        m_timer->Deregister(m_someipTimerKey);
    }

    m_someipTimerKey = m_timer->Register(
    common::S_TO_MS(interval),
    [this]() {
        getNewSomeipSamples();
    }, 
    true);
}

void CommunicatorManager::getNewSomeipSamples()
{
    for(auto const& communicator : m_comms)
    {
        communicator->HandleNewSamples();
    }
}
#endif // EEE_PLATFORM