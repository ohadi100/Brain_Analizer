#pragma once
/**
 * @file
 * @brief     The EngineDispatcherBase class that dequeues sensor data objects and sends them to the correct engine
 */

#include <memory>
#include <unordered_set>

#include "brain/engines/Engine.hpp"
#include "brain/engines/EngineId.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/notification_handler/SensorDataQueuesManager.hpp"
#include "brain/events/EventPriority.hpp"

using common::sensor_data::SensorDataTag;

namespace brain
{
namespace engines
{
using brain::engines::Engine;
using brain::engines::EngineId;
using brain::events::EventPriorityMapType;
using common::sensor_data::UPSensorData;
/**
 * @class   EngineDispatcherBase
 * @brief   The EngineDispatcherBase class that dequeues sensor data objects and sends them to the correct engine
 */
class EngineDispatcherBase
{
public:
    using SensorDataQueuesManager    = common::notification_handler::SensorDataQueuesManager;
    using SensorData                 = common::sensor_data::SensorData;
    using ConfigurationPtr           = common::configuration::Pointer;
    using EventCounter               = common::counters::EventCounter;
    using SensorDataQueuesManagerPtr = SensorDataQueuesManager::SensorDataQueuesManagerPtr;
    using EventPriorityConfigKeys    = std::unordered_map<EngineId, std::string const>;
    using EngineDispatcherBasePtr = std::shared_ptr<brain::engines::EngineDispatcherBase>;

    EngineDispatcherBase(SensorDataQueuesManagerPtr queuesManager,
                         uint32_t const             sensorDataSize,
                         EventPriorityMapType const priorityMap)
      : m_engines(sensorDataSize)
      , m_queuesManager(queuesManager)
      , m_priorityMap(priorityMap)
    {}

    virtual ~EngineDispatcherBase() = default;

    /**
     * @brief    default copy constructor
     */
    EngineDispatcherBase(const EngineDispatcherBase& other) = delete;

    /**
     * @brief    default move constructor
     */
    EngineDispatcherBase(EngineDispatcherBase&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    EngineDispatcherBase& operator=(EngineDispatcherBase const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    EngineDispatcherBase& operator=(EngineDispatcherBase&&) = delete;

    virtual void Init() = 0;

    /**
     * @brief   Dequeues SDs and handles them
     * @param   stopAfterSingleFail - should handleData finished chunk processing after failing to process one of the
     * SDs
     * @return  bool - True iff any data was processed
     */
    bool HandleData(bool const stopAfterSingleFail = false);

    /**
     * @brief   Create RuleEngine thread
     * @param   EngineDispatcherBasePtr - shared pointer of EngineDispatcherBase
     * @return  void
     */
    static void CreateRulesEngineThread(EngineDispatcherBasePtr engineDispatcherBasePtr);
#ifndef TESTS
protected:
#endif
    void loadEventPriorities(ConfigurationPtr config);
    void
    Set(EventPriorityConfigKeys PriorityConfigKeys)
    {
        m_eventPriorityConfigKeys.insert(PriorityConfigKeys.begin(), PriorityConfigKeys.end());
    }
    std::vector<std::shared_ptr<Engine>> m_engines;
    SensorDataQueuesManagerPtr           m_queuesManager;
    std::shared_ptr<EventCounter>        m_failedProcessSDCounter;
    std::shared_ptr<EventCounter>        m_counterArrivedEventWithSignal;
    EventPriorityMapType                 m_priorityMap;
    EventPriorityConfigKeys              m_eventPriorityConfigKeys;

#ifndef TESTS 
private:
#endif //TESTS 

    bool handleSD(UPSensorData sd);

    void              StartDispatcher();
    void              StopDispatcher();
    std::atomic<bool> m_runningFlag{false};
};
}  // namespace engines
}  // namespace brain
