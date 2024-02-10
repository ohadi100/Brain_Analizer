/**
 * @file
 * @brief       A rule engine for the Intelligent sensor.
 *              Forwards all intelligent sensor events.
 */
#include "IntelligentSensorEngine.hpp"
#include "NanoPB.hpp"
#include "SecurityEventsEngine.hpp"
#include "brain/noise_filter/event_noise_filter/GroupNoiseFilter.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "brain/utils/nanopb/Decoders.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "brain/config/AlertEventsNames.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"

using brain::engines::security_events::IntelligentSensorEngine;
using brain::engines::security_events::SecurityEventsEngine;
using brain::engines::ReturnCode;
using namespace brain::sender_events;

namespace brain
{
namespace engines
{
namespace security_events
{
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;
using Message = brain::messageRepository::MessageRepositoryInterface::Message;
}
}  // namespace engines
}  // namespace brain

IntelligentSensorEngine::IntelligentSensorEngine(CounterManagerPtr                                 debugCounters,
                                                 MessageRepositoryPtr                              msgRepository,
                                                 EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                                                 EventNoiseFilterPtr                               eventNoiseFilter,
                                                 events::EventPriority                             priority)
  : EngineEventSender(priority, msgRepository, reportSerializer, eventNoiseFilter)
{
    if (debugCounters)
    {
        m_failedCounter = debugCounters->CreateCounter(
            common::counters::warning::INTELLIGENT_SENSOR_ENGINE_FAILED_PROCESS_COUNTER_NAME, EventCounterLevelType::COUNTER_WARNING);
        m_filteredEventCounter = debugCounters->CreateCounter(
            common::counters::warning::FILTERED_OUT_INTELLIGENT_SENSOR_EVENT_BY_EVENT_NOISE_FILTER_COUNTER_NAME, EventCounterLevelType::COUNTER_WARNING);
    }
}

ReturnCode
IntelligentSensorEngine::processInternal(UPSensorData sd)
{
    try
    {
        LOG_VERBOSE << "Processing IntelligentSensorEngine - began processing SecurityEventSensorData" << LOG_NOOP;

        auto& securityEventSD = dynamic_cast<SecurityEventSensorData&>(*sd);
        forwardIntelligentEvent(securityEventSD);
    }
    catch (std::bad_cast const& /*e*/)
    {
        LOG_ERROR << "Processing IntelligentSensorEngine - sd cannot be casted to SecurityEventSensorData" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCounter);
        SecurityEventsEngine::HandleDroppedSecurityEventExt(std::move(sd),
                                                            DropReason::IntelligentSensorEngine);
        return ReturnCode::CastError;
    }

    return ReturnCode::Success;
}

void
IntelligentSensorEngine::forwardIntelligentEvent(SecurityEventSensorData& securityEventSD)
{
    // Handle rule evaluation
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
    createIntelligentEvent(ruleEval, securityEventSD);
    
    auto const rc = addEventAlert(ruleEval, CriticalEventAlert::IntelligentEventName);
    if (AddEventReturnCode::SerializationError == rc)
    {
        SecurityEventsEngine::HandleDroppedSecurityEventExt(securityEventSD,
                                                            DropReason::IntelligentSensorEngine);
    }
}

IntelligentSensorEngine::AddEventReturnCode
IntelligentSensorEngine::addEventAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval,
                                       brain::sender_events::CriticalEventAlert                       event)
{
    auto const status = SendEvent(ruleEval, SensorDataTag::SD_INTELLIGENT_SENSOR, event);

    if (EngineEventSender::SendStatus::Success != status)
    {
        common::counters::IncreaseCounter(
            (EngineEventSender::SendStatus::NoiseFilterError == status) ? m_filteredEventCounter : m_failedCounter);
    }

    return (EngineEventSender::SendStatus::Success == status) ? AddEventReturnCode::Success
                                                          : AddEventReturnCode::StorageError;
}

void
IntelligentSensorEngine::createIntelligentEvent(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                                                SecurityEventSensorData&                                 sd)
{
    com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData securityEventAlert
        = com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_init_default;
    std::ignore = SecurityEventsEngine::CreateSecurityEventData(securityEventAlert, sd);

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;

    ruleEval.which_RuleData
        = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_intelligentSensorEvent_tag);
    ruleEval.RuleData.intelligentSensorEvent = securityEventAlert;

    auto eventFrame = sd.GetEventFrame();
    LOG_DEBUG << "create intelligentSensorEvent:"
                << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
                << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
                << ",eventDefinitionId=" << static_cast<uint32_t>(eventFrame.eventDefinitionId) << LOG_NOOP;
}
