/**
 * @file
 * @brief     A rule engine for Intelligent sensor.
 */
#ifndef INTELLIGENT_SENSOR_ENGINE_HPP
#define INTELLIGENT_SENSOR_ENGINE_HPP

#include "brain/engines/Engine.hpp"
#include "brain/engines/EngineEventSender.hpp"
#include "brain/sensor_data/security_events/SecurityEventSensorData.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using brain::sensor_data::SecurityEventSensorData;
using common::sensor_data::UPSensorData;

/**
 * @class   IntelligentSensorEngine
 * @brief   The SecurityEventsEngine analyzes SecurityEvents.
 */
class IntelligentSensorEngine
  : public Engine
  , public EngineEventSender
{
public:
    using CounterManagerPtr   = common::counters::CounterManagerPtr;
    using EventCounter        = common::counters::EventCounter;
    using EventNoiseFilterPtr = std::shared_ptr<brain::brain_noise_filter::EventNoiseFilter>;
    using EventCounterPtr     = std::shared_ptr<common::counters::EventCounter>;

    /**
     * @brief   Constructor
     * @param   CounterManagerPtr debugCounters
     * @param   msgRepository for communicate with sender manager sender
     * @param   reportSerializer - class to serialize idsperiodicreport proto object
     * @param   EventNoiseFilterPtr eventNoiseFilter
     * @param   EventPriority priority
     */
    IntelligentSensorEngine(CounterManagerPtr                                 debugCounters,
                            MessageRepositoryPtr                              msgRepository,
                            EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                            EventNoiseFilterPtr                               eventNoiseFilter,
                            events::EventPriority priority = events::EventPriority::Critical);

protected:
    ReturnCode processInternal(UPSensorData sd) override;
    enum class AddEventReturnCode : uint8_t
    {
        Success,
        SerializationError,
        StorageError,
        NoiseFilterError
    };
    virtual AddEventReturnCode addEventAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval,
                                             brain::sender_events::CriticalEventAlert                       event);

private:
    void createIntelligentEvent(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                                SecurityEventSensorData&                                 sd);
    void forwardIntelligentEvent(SecurityEventSensorData& securityEventSD);

    EventCounterPtr m_failedCounter;
    EventCounterPtr m_filteredEventCounter;
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

#endif  // INTELLIGENT_SENSOR_ENGINE_HPP
