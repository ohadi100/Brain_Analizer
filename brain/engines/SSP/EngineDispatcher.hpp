/**
 * @file
 * @brief     The EngineDispatcher class that dequeues sensor data objects and sends them to the correct engine
 */
#ifndef ENGINE_DISPATCHER_HPP
#define ENGINE_DISPATCHER_HPP

#include <memory>
#include <unordered_set>

#include "brain/engines/dispatcher/EngineDispatcherBase.hpp"

#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "brain/engines/Engine.hpp"
#include "brain/engines/EngineId.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/notification_handler/SensorDataQueuesManager.hpp"
#include "common/sensor_data/SensorDataTags.hpp"
#include "common/utils/timer/Timer.hpp"
#include "common/utils/types/MessageRepositoryTypes.hpp"

#ifdef HTTPS_PUBLISHER
#include "brain/communicator/FileSystemCommunicator/FileSystemCommunicator.hpp"
#endif

using common::sensor_data::SensorDataTag;

namespace brain
{
namespace publishers
{
namespace utils
{
class ExceededMessageSizeCheck;
} //namespace utils
} //namespace publishers
namespace engines
{

using brain::engines::Engine;
using brain::engines::EngineId;
using brain::events::EventPriorityMapType;
using common::sensor_data::UPSensorData;
using brain::messageRepository::MessageRepositoryPtr;
/**
 * @class   EngineDispatcher
 * @brief   The EngineDispatcher class that dequeues sensor data objects and sends them to the correct engine
 */
class EngineDispatcher final : public EngineDispatcherBase
{
public:
    using DataArrivedEventPtr        = std::shared_ptr<common::notification_handler::DataArrivedEvent>;
    using SensorDataQueuesManager    = common::notification_handler::SensorDataQueuesManager;
    using PersistentMemoryFactoryPtr = std::shared_ptr<common::memory::PersistentMemoryFactory>;
    using DiagnosticsManagerPtr      = brain::diagnostics::DiagnosticsManagerInterface::Pointer;
    using SensorData                 = common::sensor_data::SensorData;
    using SensorDataChunk            = common::notification_handler::SDChunk;
    using SensorDataChunkPtr         = common::notification_handler::SDChunkPtr;
    using CounterManagerPtr          = common::counters::CounterManagerPtr;
    using ConfigurationPtr           = common::configuration::Pointer;
    using EventCounterLevelType      = common::counters::EventCounter::EventCounterLevelType;
    using EventCounter               = common::counters::EventCounter;
    using SensorDataQueuesManagerPtr = SensorDataQueuesManager::SensorDataQueuesManagerPtr;
    using TimerPtr                   = common::TimerPtr;
    using SPExceededMessageSizeCheck = std::shared_ptr<brain::publishers::utils::ExceededMessageSizeCheck>;
    /**
     * @brief   Constructor
     * @param   SensorDataQueuesManagerPtr queuesManager - queuesManager to request queue from
     * @param   msgRepository for communicate with sender manager
     * @param   CounterManagerPtr & debugCounters - counters manager
     * @param   ConfigurationPtr & config
     * @param   TimerPtr & timer
     * @param   PersistentMemoryFactoryPtr & persistentMemoryFactory
     * @param   DiagnosticsManagerPtr diagnosticsManager
     * @param   exceededMessageSizeCheck check exceeded message size
     * @return  none
     */
    EngineDispatcher(SensorDataQueuesManagerPtr        queuesManager,
                     MessageRepositoryPtr              msgRepository,
                     CounterManagerPtr const           debugCounters,
                     ConfigurationPtr const            config,
                     TimerPtr const                    timer,
                     PersistentMemoryFactoryPtr const& persistentMemoryFactory,
                     DiagnosticsManagerPtr             diagnosticsManager,
                     SPExceededMessageSizeCheck        exceededMessageSizeCheck);
    EngineDispatcher()                        = delete;

    /**
     * @brief   initialize the system with all the relevant engines 
     */
    void Init() override;

private:
    MessageRepositoryPtr      m_msgRepository;
    CounterManagerPtr          m_debugCounters;
    ConfigurationPtr           m_config;
    TimerPtr                   m_timer;
    PersistentMemoryFactoryPtr m_persistentMemoryFactory;
    DiagnosticsManagerPtr      m_diagnosticsManager;
    SPExceededMessageSizeCheck m_exceededMessageSizeCheck;
#ifdef HTTPS_PUBLISHER
    std::vector<std::shared_ptr<Engine>>                                  m_sensorsMap;
    std::shared_ptr<communicator::fileSystemComm::FileSystemCommunicator> m_fileSystemComm;
#endif
};
}  // namespace engines
}  // namespace brain

#endif  // ENGINE_DISPATCHER_HPP
