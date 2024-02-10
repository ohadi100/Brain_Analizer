/**
 * @file
 * @brief     code for the generic EngineDispatcher
 */
#include "brain/engines/SSP/EngineDispatcher.hpp"
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "brain/engines/SSP/PeriodicStatisticsEngine.hpp"
#include "brain/noise_filter/event_noise_filter/EventNoiseFilter.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/thread_handler/ThreadHandler.hpp"
#include "common/thread_handler/ThreadNamesConstants.hpp"
#include "persistent_map/PersistentMap.h"
#include "brain/sender/publishers/utils/message_size_check/ExceededMessageSizeCheck.hpp"
#include "brain/engines/serializer/IDSPeriodicReportSerializer.hpp"

#if defined(tests) || defined(SIMULATION)
#include "brain/engines/NullEngine.hpp"
#endif  // defined(tests) || defined(SIMULATION)

using brain::engines::EngineDispatcher;
using brain::engines::EngineDispatcherBase;
using brain::engines::EngineId;
using common::notification_handler::DataArrivedEvent;
using common::sensor_data::SensorData;
using common::thread_handler::ThreadHandler;

namespace brain
{
namspace engines
{
    using EventNoiseFilterPtr = std::shared_ptr<brain::brain_noise_filter::EventNoiseFilter>;
}
}  // namespace brain


EngineDispatcher::EngineDispatcher(SensorDataQueuesManagerPtr        queuesManager,
                                   MessageRepositoryPtr              msgRepository,
                                   CounterManagerPtr const           debugCounters,
                                   ConfigurationPtr const            config,
                                   TimerPtr const                    timer,
                                   PersistentMemoryFactoryPtr const& persistentMemoryFactory,
                                   DiagnosticsManagerPtr             diagnosticsManager,
                                   SPExceededMessageSizeCheck        exceededMessageSizeCheck)
  : EngineDispatcherBase(
      queuesManager, static_cast<uint32_t>(SensorDataTag::SD_NUMBER_OF_TAGS), brain::events::EventPriorityMap)
  , m_msgRepository(msgRepository)
  , m_debugCounters(debugCounters)
  , m_config(config)
  , m_timer(timer)
  , m_persistentMemoryFactory(persistentMemoryFactory)
  , m_diagnosticsManager(diagnosticsManager)
  , m_exceededMessageSizeCheck(exceededMessageSizeCheck)
#ifdef HTTPS_PUBLISHER  // Https publisher
  , m_sensorsMap(static_cast<uint32_t>(
        SensorDataTag::SD_NUMBER_OF_TAGS))  // m_sensorsMap(static_cast<uint32_t>(SensorDataTag::SD_NUMBER_OF_TAGS))
#endif
{
    std::unordered_map<EngineId, config_keys::ConfigKeyType> s_eventPriorityConfigKey{
        {EngineId::PERIODIC_STATISTICS, brain::config_keys::EVENT_PRIORITY_PERIODIC_STATISTICS},
    };

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
#endif  // defined(tests) || defined(SIMULATION)

    auto reportSerializer = std::make_shared<brain::engines::IDSPeriodicReportSerializer>(m_config);

    std::unordered_map<uint32_t, std::shared_ptr<Engine>> periodicEnginesStatisticsMap;

    brain::engines::security_events::SecurityEventsEngine::SecurityEventsEngineConfig securityEngineConfig{
        m_debugCounters,
        m_msgRepository,
        periodicEnginesStatisticsMap,
        m_diagnosticsManager,
        reportSerializer,
        eventNoiseFilter,
        m_exceededMessageSizeCheck,
        m_priorityMap[EngineId::PERIODIC_STATISTICS]};

    m_engines[static_cast<uint32_t>(SensorDataTag::SD_PERIODIC_STATISTICS)]
        = std::make_shared<brain::engines::PeriodicStatisticsEngine>(securityEngineConfig);

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
    m_sensorsMap[static_cast<uint32_t>(SensorDataTag::SD_PERIODIC_STATISTICS)]
        = m_engines[static_cast<uint32_t>(SensorDataTag::SD_PERIODIC_STATISTICS)];
    m_fileSystemComm = std::make_shared<communicator::fileSystemComm::FileSystemCommunicator>(m_sensorsMap,m_diagnosticsManager);
    m_fileSystemComm->InitService();
#endif
}