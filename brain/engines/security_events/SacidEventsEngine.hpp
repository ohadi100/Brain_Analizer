/**
 * @file
 * @brief     A rule engine for SACID CAN events.
 */
#ifndef SACID_EVENTS_ENGINE_HPP
#define SACID_EVENTS_ENGINE_HPP

#include <mutex>

#include "brain/config/BrainConfigConstants.hpp"
#include "brain/engines/Engine.hpp"
#include "brain/engines/EngineEventSender.hpp"
#include "SecurityEventsEngine.hpp"
#include "brain/sensor_data/security_events/SecurityEventSensorData.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/utils/timer/Timer.hpp"
#include "common/utils/types/MultipleKeysMap.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using IDSMInstanceID   = uint16_t;
using SensorInstanceID = uint8_t;
using EventID          = uint16_t;
using Count            = uint16_t;
using BusID            = uint16_t;
using CANID            = uint32_t;
using ControllerID     = uint8_t;
using ErrorType        = uint8_t;
using CountValue       = uint32_t;

using brain::sensor_data::SecurityEventSensorData;
using common::sensor_data::UPSensorData;

/**
 * @class   SacidEventsEngine
 * @brief   The SacidEventsEngine analyzes SecurityEvents.
 */
class SacidEventsEngine
  : public Engine
  , public EngineEventSender
{
public:
    using CounterManagerPtr = common::counters::CounterManagerPtr;
    using EventCounter = common::counters::EventCounter;
    using EventCounterWithTs = common::counters::EventCounterWithTs;
    using TimerPtr = common::TimerPtr;
    using ConfigurationPtr = common::configuration::Pointer;
    using PersistentMemoryFactoryPtr = common::utils::PersistentMap::PersistentMemoryFactoryPtr;
    using PersistentMemory = common::utils::PersistentMap;
    using SecurityEventsEnginePtr = std::shared_ptr<SecurityEventsEngine>;
    using EventNoiseFilterPtr = std::shared_ptr<brain::brain_noise_filter::EventNoiseFilter>;

    /**
     * @brief   Constructor
     * @param   CounterManagerPtr debugCounters
     * @param   msgRepository for communicate with sender manager sender
     * @param   SecurityEventsEnginePtr securityEventsEngine - instance of general SE engine
     * @param   reportSerializer - class to serialize idsperiodicreport proto object
     * @param   EventNoiseFilterPtr eventNoiseFilter
     * @param   EventPriority priority
     */
    SacidEventsEngine(CounterManagerPtr                                 debugCounters,
                      MessageRepositoryPtr                              msgRepository,
                      SecurityEventsEnginePtr                           securityEventsEngine,
                      EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                      EventNoiseFilterPtr                               eventNoiseFilter,
                      events::EventPriority                             priority = events::EventPriority::Important);

    /**
     * @brief   Destructor
     */
    ~SacidEventsEngine() = default;

    /**
     * @brief    default copy constructor
     */
    SacidEventsEngine(const SacidEventsEngine& other) = delete;

    /**
     * @brief    default move constructor
     */
    SacidEventsEngine(SacidEventsEngine&& other) = delete;

    /**
    * @brief    default copy assignment operator
    */
    SacidEventsEngine& operator=(SacidEventsEngine const&) = delete;

    /**
    * @brief   default move assignment operator
    */
    SacidEventsEngine& operator=(SacidEventsEngine&&) = delete;

private:
    ReturnCode processInternal(UPSensorData sd) override;

    void handleSacidSecurityEvents(SecurityEventSensorData& sacidSD);
    void forwardSacidEvent(SecurityEventSensorData& securityEventSD, bool isCriticalEvent = false);

    EventCounterPtr    m_invalidCtxDataLenCounter;
    EventCounterPtr    m_failedCounter;
    CounterManagerPtr  m_debugCounters;

protected:
    
    /**
     * @brief   Create the alert to be ready to be sent
     * @param   com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval - input/output variable, rule evaluation protobuf structure that include the alert
     * @param   SecurityEventSensorData& sd - sendor data used in the alert
     * @return  bool - true is alert was created, false otherwise
     */
    virtual bool createEventAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval, SecurityEventSensorData& sd);
    
    //used to access code from SecurityEventsEngine
    SecurityEventsEnginePtr   m_securityEventsEngine;
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

#endif  // SACID_EVENTS_ENGINE_HPP
