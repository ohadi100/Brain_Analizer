/**
 * @file
 * @brief     code for the generic EngineDispatcher
 */
#include <EngineDispatcher.hpp>
#include "PeriodicStatisticsEngine.hpp"
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "brain/engines/qlah/EthEngine.hpp"
#include "brain/engines/qlah/HostEngine.hpp"
#include "brain/engines/security_events/IntelligentSensorEngine.hpp"
#include "brain/engines/security_events/SacidEventsEngine.hpp"
#include "brain/engines/security_events/SecurityEventsEngine.hpp"
#include "brain/engines/swpac/KernelLogEngine.hpp"
#include "brain/engines/swpac/ProcessPerformanceEngine.hpp"
#include "brain/engines/swpac/TLSErrorReportEngine.hpp"
#include "brain/engines/swpac/UnknownConstraintEngine.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/thread_handler/ThreadHandler.hpp"
#include "common/thread_handler/ThreadNamesConstants.hpp"
#include "persistent_map/PersistentMap.h"
#include "security_events/SecurityEventIdsManager.hpp"
#include "brain/sender/publishers/utils/message_size_check/ExceededMessageSizeCheck.hpp"
#include "brain/engines/qlah/EthUnknownProtocolAlert.hpp"
#include "brain/engines/qlah/EthIllegalVlanFramesAlert.hpp"
#include "brain/engines/serializer/IDSPeriodicReportSerializer.hpp"

#if defined(tests) || defined(SIMULATION)
#include "NullEngine.hpp"
#endif

using brain::engines::EngineDispatcher;
using brain::engines::EngineId;
using common::notification_handler::DataArrivedEvent;
using common::sensor_data::SensorData;
using common::thread_handler::EThreadStatus;
using common::thread_handler::ThreadHandler;

using brain::engines::security_events::SecurityEventIdsManager;
namespace brain
{
namespace engines
{
    using EventNoiseFilterPtr = std::shared_ptr<brain::brain_noise_filter::EventNoiseFilter>;
}
}  // namespace brain

EngineDispatcher::EngineDispatcher(SensorDataQueuesManagerPtr       queuesManager,
                                   MessageRepositoryPtr             msgRepository,
                                   CounterManagerPtr const          debugCounters,
                                   ConfigurationPtr const           config,
                                   TimerPtr const                   timer,
                                   PersistentMemoryFactoryPtr const persistentMemoryFactory,
                                   DiagnosticsManagerPtr            diagnosticsManager,
                                   SPExceededMessageSizeCheck       exceededMessageSizeCheck)
  : EngineDispatcherBase(
      queuesManager, static_cast<uint32_t>(SensorDataTag::SD_NUMBER_OF_TAGS), brain::events::EventPriorityMap)
  , m_msgRepository(msgRepository)
  , m_debugCounters(debugCounters)
  , m_config(config)
  , m_timer(timer)
  , m_persistentMemoryFactory(persistentMemoryFactory)
  , m_diagnosticsManager(diagnosticsManager)
  , m_exceededMessageSizeCheck(exceededMessageSizeCheck)
#ifdef HTTPS_PUBLISHER
  , m_sensorsMap(static_cast<uint32_t>(SensorDataTag::SD_NUMBER_OF_TAGS))
#endif
{
    static const std::unordered_map<EngineId, config_keys::ConfigKeyType> s_eventPriorityConfigKey{
        {EngineId::PERIODIC_STATISTICS, brain::config_keys::EVENT_PRIORITY_PERIODIC_STATISTICS},
        {EngineId::SWPAC_TLS_ERROR_REPORT, brain::config_keys::EVENT_PRIORITY_DHM},
        {EngineId::SWPAC_KERNEL_LOG, brain::config_keys::EVENT_PRIORITY_DHM},
        {EngineId::SWPAC_PROCESS_PERFORMANCE, brain::config_keys::EVENT_PRIORITY_DHM},
        {EngineId::SWPAC_UNKNOWN_CONSTRAINT_ID, brain::config_keys::EVENT_PRIORITY_DHM},
        {EngineId::QLAH_ETH, brain::config_keys::EVENT_PRIORITY_QLAH_ETH},
        {EngineId::QLAH_HOST, brain::config_keys::EVENT_PRIORITY_QLAH_HOST},
        {EngineId::SECURITY_EVENT, brain::config_keys::EVENT_PRIORITY_SECURITY_EVENT},
        {EngineId::INTELLIGENT_SENSOR, brain::config_keys::EVENT_PRIORITY_INTELLIGENT_SENSOR},
        {EngineId::SACID_EVENT, brain::config_keys::EVENT_PRIORITY_SACID_CAN_EVENT}};

    EngineDispatcherBase::Set(s_eventPriorityConfigKey);

    if (m_config)
    {
        std::string const osLog = "usbcore: registered new device driver usb";
        m_config->SetValue("osLog", osLog);

        loadEventPriorities(m_config);
    }

    Init();
}

void
EngineDispatcher::Init()
{
    auto eventNoiseFilter = std::make_shared<brain::brain_noise_filter::EventNoiseFilter>(m_debugCounters, m_config);
#if defined(SIMULATION)
    // For testing
    auto const nullEngine = std::make_shared<brain::engines::NullEngine>(m_debugCounters);
    m_engines[static_cast<uint32_t>(SensorDataTag::SD_NULL_TAG)] = nullEngine;
#endif

    auto reportSerializer = std::make_shared<brain::engines::IDSPeriodicReportSerializer>(m_config);

    // SW-PAC
    auto dhmIncidentTable = std::make_shared<brain::engines::swpac::IncidentCounterTable>();

    auto const kernelLogEngine = std::make_shared<brain::engines::swpac::KernelLogEngine>(
        m_debugCounters, m_msgRepository, reportSerializer, eventNoiseFilter, m_priorityMap[EngineId::SWPAC_KERNEL_LOG]);
    kernelLogEngine->SetIncidentCounterTable(dhmIncidentTable);
    m_engines[static_cast<uint32_t>(SensorDataTag::SD_SWPAC_KERNEL_LOG)] = kernelLogEngine;

    auto const tlsErrorReportEngine = std::make_shared<brain::engines::swpac::TLSErrorReportEngine>(
        m_debugCounters, m_msgRepository, reportSerializer, eventNoiseFilter, m_priorityMap[EngineId::SWPAC_TLS_ERROR_REPORT]);
    tlsErrorReportEngine->SetIncidentCounterTable(dhmIncidentTable);
    m_engines[static_cast<uint32_t>(SensorDataTag::SD_SWPAC_TLS_ERROR_REPORT)] = tlsErrorReportEngine;

    auto const processPerformanceEngine = std::make_shared<brain::engines::swpac::ProcessPerformanceEngine>(
        m_debugCounters,
        m_msgRepository,
        m_config,
        reportSerializer,
        eventNoiseFilter,
        m_priorityMap[EngineId::SWPAC_PROCESS_PERFORMANCE]);
    processPerformanceEngine->SetIncidentCounterTable(dhmIncidentTable);
    m_engines[static_cast<uint32_t>(SensorDataTag::SD_SWPAC_PROCESS_PERFORMANCE_REPORT)] = processPerformanceEngine;

    m_unknownConstraintEngine = std::make_shared<brain::engines::swpac::UnknownConstraintEngine>(
        m_debugCounters, m_msgRepository, reportSerializer, eventNoiseFilter, m_priorityMap[EngineId::SWPAC_PROCESS_PERFORMANCE]);

    // QLAH
    auto ethUnknownProtocolAlert = brain::engines::qlah::EthUnknownProtocolAlert::CreateAlert(
        m_debugCounters, m_msgRepository, reportSerializer, eventNoiseFilter, m_priorityMap[EngineId::QLAH_ETH]);
    auto illegalVlangAlert = brain::engines::qlah::EthIllegalVlanFramesAlert::CreateAlert(
        m_debugCounters, m_msgRepository, reportSerializer, eventNoiseFilter, m_priorityMap[EngineId::QLAH_ETH]);
    auto const ethStats
        = std::make_shared<brain::engines::EthernetStatistics>(m_debugCounters, m_diagnosticsManager, m_config);
    ethStats->SetEthUnknownProtocolAlert(std::move(ethUnknownProtocolAlert));
    ethStats->SetEthIllegalVlanFramesAlert(std::move(illegalVlangAlert));

    auto const ethEngine = std::make_shared<brain::engines::qlah::EthEngine>(
        m_debugCounters, m_msgRepository, ethStats, reportSerializer, eventNoiseFilter, m_priorityMap[EngineId::QLAH_ETH]);
    m_engines[static_cast<uint32_t>(SensorDataTag::SD_QLAH_ETH)] = ethEngine;

    auto const hostEngine = std::make_shared<brain::engines::qlah::HostEngine>(
        m_debugCounters, m_msgRepository, reportSerializer, eventNoiseFilter, m_priorityMap[EngineId::QLAH_HOST]);
    m_engines[static_cast<uint32_t>(SensorDataTag::SD_QLAH_HOST)] = hostEngine;

    // SecurityEvents
    const brain::engines::security_events::SecurityEventsEngine::SecurityEventsEngineConfig securityEngineConfig{
        m_debugCounters,
        m_msgRepository,
        m_config,
        m_timer,
        ethStats,
        reportSerializer,
        eventNoiseFilter,
        m_priorityMap[EngineId::SECURITY_EVENT]};

    m_securityEventsEngine = std::make_shared<brain::engines::security_events::SecurityEventsEngine>(securityEngineConfig);
    m_engines[static_cast<uint32_t>(SensorDataTag::SD_SECURITY_EVENT)] = m_securityEventsEngine;

    auto const intelligentSensorEngine = std::make_shared<brain::engines::security_events::IntelligentSensorEngine>(
        m_debugCounters, m_msgRepository, reportSerializer, eventNoiseFilter, m_priorityMap[EngineId::INTELLIGENT_SENSOR]);
    m_engines[static_cast<uint32_t>(SensorDataTag::SD_INTELLIGENT_SENSOR)] = intelligentSensorEngine;

    // periodic
    std::unordered_map<uint32_t, std::shared_ptr<Engine>> periodicEnginesStatisticsMap;
    periodicEnginesStatisticsMap[static_cast<uint32_t>(SensorDataTag::SD_SWPAC_PROCESS_PERFORMANCE_REPORT)]
        = processPerformanceEngine;
    periodicEnginesStatisticsMap[static_cast<uint32_t>(SensorDataTag::SD_QLAH_ETH)]       = ethEngine;
    periodicEnginesStatisticsMap[static_cast<uint32_t>(SensorDataTag::SD_QLAH_HOST)]      = hostEngine;
    periodicEnginesStatisticsMap[static_cast<uint32_t>(SensorDataTag::SD_SECURITY_EVENT)] = m_securityEventsEngine;

    const brain::engines::PeriodicStatisticsEngine::PeriodicStatisticsEngineConfig config{
        m_debugCounters,
        m_msgRepository,
        periodicEnginesStatisticsMap,
        m_diagnosticsManager,
        reportSerializer,
        eventNoiseFilter,
        m_exceededMessageSizeCheck,
        m_priorityMap[EngineId::PERIODIC_STATISTICS]};

    auto const periodicStaticEngine
        = std::make_shared<brain::engines::PeriodicStatisticsEngine>(config);
        
    periodicStaticEngine->SetIncidentCounterTable(dhmIncidentTable);
    m_engines[static_cast<uint32_t>(SensorDataTag::SD_PERIODIC_STATISTICS)] = periodicStaticEngine;

    // Sacid communicator
    bool isSacidCommunicatorstatusEnabled{true};
    bool ok = m_config->GetValue(brain::config_keys::SACID_COMMUNICATOR_STATUS, isSacidCommunicatorstatusEnabled);
    // double check that the function GetValue has not alltered the value of isSacidCommunicatorstatusEnabled in case it
    // was not found in the configuration file
    if (!ok)
    {
        isSacidCommunicatorstatusEnabled = true;
    }

    if (isSacidCommunicatorstatusEnabled)
    {
        // SACID CAN Events
        m_engines[static_cast<uint32_t>(SensorDataTag::SD_SACID_CAN_EVENT)]
            = std::make_shared<brain::engines::security_events::SacidEventsEngine>(
                m_debugCounters,
                m_msgRepository,
                m_securityEventsEngine,
                reportSerializer,
                eventNoiseFilter,
                m_priorityMap[EngineId::SACID_EVENT]);
    }

    if (m_debugCounters)
    {
        m_failedProcessSDCounter = m_debugCounters->CreateCounter(
            common::counters::warning::ENGINE_DISPATCHER_FAILED_PROCESS_SD_COUNTER_NAME,
            EventCounterLevelType::COUNTER_WARNING);
        m_counterArrivedEventWithSignal
            = m_debugCounters->CreateCounter(common::counters::debug::BRAIN_DATA_ARRIVED_EVENT_SIGNAL_COUNTER_NAME,
                                             EventCounter::EventCounterLevelType::COUNTER_DEBUG);
    }

#ifdef HTTPS_PUBLISHER
    m_sensorsMap[static_cast<uint32_t>(SensorDataTag::SD_SECURITY_EVENT)] = m_securityEventsEngine;
    m_sensorsMap[static_cast<uint32_t>(SensorDataTag::SD_PERIODIC_STATISTICS)]
        = m_engines[static_cast<uint32_t>(SensorDataTag::SD_PERIODIC_STATISTICS)];
    m_sensorsMap[static_cast<uint32_t>(SensorDataTag::SD_SWPAC_KERNEL_LOG)]                 = kernelLogEngine;
    m_sensorsMap[static_cast<uint32_t>(SensorDataTag::SD_SWPAC_TLS_ERROR_REPORT)]           = tlsErrorReportEngine;
    m_sensorsMap[static_cast<uint32_t>(SensorDataTag::SD_SWPAC_PROCESS_PERFORMANCE_REPORT)] = processPerformanceEngine;

    m_fileSystemComm
        = std::make_shared<communicator::fileSystemComm::FileSystemCommunicator>(m_sensorsMap, m_diagnosticsManager);
    m_fileSystemComm->InitService();
#endif
}
