#pragma once
/**
 * @file
 * @brief     The EngineDispatcher class that dequeues sensor data objects and sends them to the correct engine
 */
#include <memory>
#include <unordered_set>

#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "brain/engines/Engine.hpp"
#include "brain/engines/dispatcher/EngineDispatcherBase.hpp"
#include "common/notification_handler/SensorDataQueuesManager.hpp"
#include "common/sensor_data/SensorDataTags.hpp"
#include "common/utils/timer/Timer.hpp"
#include "common/utils/types/ConfigurationTypes.hpp"
#include "common/utils/types/MessageRepositoryTypes.hpp"

#ifdef HTTPS_PUBLISHER
#include "brain/communicator/FileSystemCommunicator/FileSystemCommunicator.hpp"
#endif

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
namespace security_events
{
class SecurityEventsEngine;
}  // namespace security_events

namespace swpac
{
class UnknownConstraintEngine;
}

using brain::engines::Engine;
using brain::engines::EngineId;
using brain::events::EventPriorityMapType;
using brain::messageRepository::MessageRepositoryPtr;
using common::sensor_data::UPSensorData;
using common::sensor_data::SensorDataTag;
/**
 * @class   EngineDispatcher
 * @brief   The EngineDispatcher class that dequeues sensor data objects and sends them to the correct engine
 */
class EngineDispatcher : public EngineDispatcherBase
{
public:
    using SensorDataQueuesManager    = common::notification_handler::SensorDataQueuesManager;
    using PersistentMemoryFactoryPtr = std::shared_ptr<common::memory::PersistentMemoryFactory>;
    using DiagnosticsManagerPtr      = brain::diagnostics::DiagnosticsManagerInterface::Pointer;
    using SensorData                 = common::sensor_data::SensorData;
    using SensorDataChunk            = common::notification_handler::SDChunk;
    using CounterManagerPtr          = common::counters::CounterManagerPtr;
    using ConfigurationPtr           = common::configuration::Pointer;
    using EventCounterLevelType      = common::counters::EventCounter::EventCounterLevelType;
    using EventCounter               = common::counters::EventCounter;
    using SensorDataQueuesManagerPtr = SensorDataQueuesManager::SensorDataQueuesManagerPtr;
    using TimerPtr                   = common::TimerPtr;
    using SPExceededMessageSizeCheck = std::shared_ptr<brain::publishers::utils::ExceededMessageSizeCheck>;
    /**
     * @brief   Constructor
     * @param   queuesManager - queuesManager to request queue from
     * @param   msgRepository for communicate with sender manager
     * @param   debugCounters - counters manager
     * @param   config - configuration pointer
     * @param   timer - timer pointer
     * @param   persistentMemoryFactory - persiste memory factory
     * @param   diagnosticsManager - diagnostic manager
     * @param   exceededMessageSizeCheck check exceeded message size
     */
    EngineDispatcher(SensorDataQueuesManagerPtr       queuesManager,
                     MessageRepositoryPtr             msgRepository,
                     CounterManagerPtr const          debugCounters,
                     ConfigurationPtr const           config,
                     TimerPtr const                   timer,
                     PersistentMemoryFactoryPtr const persistentMemoryFactory,
                     DiagnosticsManagerPtr            diagnosticsManager,
                     SPExceededMessageSizeCheck       exceededMessageSizeCheck);
    EngineDispatcher() = delete;

    /**
     * @brief   destructor
     */
    virtual ~EngineDispatcher() = default;

    /**
     * @brief    default copy constructor
     */
    EngineDispatcher(const EngineDispatcher& other) = delete;

    /**
     * @brief    default move constructor
     */
    EngineDispatcher(EngineDispatcher&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    EngineDispatcher& operator=(EngineDispatcher const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    EngineDispatcher& operator=(EngineDispatcher&&) = delete;

    /**
     * @brief   initialize the system with all the relevant engines
     */
    void Init() override;

    /**
     * @brief   Get a pointer to the SE engine. Needed in order to handle dropped SE.
     * @return  shared smart pointer to the SE engine
     */
    std::shared_ptr<security_events::SecurityEventsEngine>
    GetSecurityEventsEngine() const
    {
        return m_securityEventsEngine;
    }

    /**
     * @brief   Get a pointer to the swpack unknown constraint engine.
     * @return  shared smart pointer to the Unknown constraint
     */
    std::shared_ptr<brain::engines::swpac::UnknownConstraintEngine>
    GetUnkownConstraintEngine() const
    {
        return m_unknownConstraintEngine;
    }

private:
    std::shared_ptr<security_events::SecurityEventsEngine>          m_securityEventsEngine;
    std::shared_ptr<brain::engines::swpac::UnknownConstraintEngine> m_unknownConstraintEngine;
    MessageRepositoryPtr                                            m_msgRepository;
    CounterManagerPtr                                               m_debugCounters;
    ConfigurationPtr                                                m_config;
    TimerPtr                                                        m_timer;
    PersistentMemoryFactoryPtr                                      m_persistentMemoryFactory;
    DiagnosticsManagerPtr                                           m_diagnosticsManager;
    SPExceededMessageSizeCheck                                      m_exceededMessageSizeCheck;
#ifdef HTTPS_PUBLISHER
    std::vector<std::shared_ptr<Engine>>                                  m_sensorsMap;
    std::shared_ptr<communicator::fileSystemComm::FileSystemCommunicator> m_fileSystemComm;
#endif
};
}  // namespace engines
}  // namespace brain
