/**
 * @file
 * @brief       This file describes the functionality of SE engines that create events
 */
#pragma once

#include "brain/engines/Engine.hpp"
#include "brain/engines/EngineEventSender.hpp"
#include "brain/sensor_data/security_events/SecurityEventSensorData.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "common/counter_manager/CounterNames.hpp"

using brain::engines::EngineEventSender;

namespace brain
{
namespace engines
{
namespace security_events
{

using SecurityEventSensorData = brain::sensor_data::SecurityEventSensorData;
using CounterManagerPtr       = std::shared_ptr<common::counters::CounterManager>;
using EventCounterLevelType   = common::counters::EventCounter::EventCounterLevelType;
using EventCounterPtr         = std::shared_ptr<common::counters::EventCounter>;
/**
 * @class SecurityEventEngineCreateEvent
 * @brief Derived class for Security Events engines that create events
 */
class SecurityEventEngineCreateEvent
  : public Engine
  , public EngineEventSender
{
public:
    /**
     * @brief Construct a new Security Event Engine Create Event object
     *
     * @param debugCounters debug counter object
     * @param priority priority of the securitry event
     * @param sender
     * @param msgRepository for communicate with sender manager sender
     * @param reportSerializer - class to serialize idsperiodicreport proto object
     * @param eventNoiseFilter noise filter
     */
    SecurityEventEngineCreateEvent(CounterManagerPtr                                 debugCounters,
                                   events::EventPriority                             priority,
                                   MessageRepositoryPtr                              msgRepository,
                                   EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                                   EventNoiseFilterPtr                               eventNoiseFilter = nullptr)
      : EngineEventSender(priority, msgRepository, reportSerializer, eventNoiseFilter)
    {
        if (debugCounters)
        {
            m_failedCounter = debugCounters->CreateCounter(
                common::counters::warning::FILTERED_OUT_SECURITY_EVENT_BY_EVENT_NOISE_FILTER_COUNTER_NAME,
                EventCounterLevelType::COUNTER_WARNING);
        }
    }

    /**
     * @brief Destroy the Security Event Engine Create Event object
     *
     */
    virtual ~SecurityEventEngineCreateEvent() = default;

    /**
     * @brief    default copy constructor
     */
    SecurityEventEngineCreateEvent(const SecurityEventEngineCreateEvent& other) = delete;

    /**
     * @brief    default move constructor
     */
    SecurityEventEngineCreateEvent(SecurityEventEngineCreateEvent&& other) = delete;

    /**
    * @brief    default copy assignment operator
    */
    SecurityEventEngineCreateEvent& operator=(SecurityEventEngineCreateEvent const&) = delete;

    /**
    * @brief   default move assignment operator
    */
    SecurityEventEngineCreateEvent& operator=(SecurityEventEngineCreateEvent&&) = delete;

    static constexpr uint64_t EventWeight{1U};

protected:
    virtual bool addEventAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval,
                               brain::sender_events::CriticalEventAlert                       event,
                               SecurityEventSensorData const&                                 sd);

    inline void
    clearEventDataToSerialize()
    {
        m_eventDataToSerialize.clear();
    }

    // temporary buffers to store event data to serialize
    static std::vector<common::nanopb::Array> m_eventDataToSerialize;
    EventCounterPtr                           m_failedCounter;
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain