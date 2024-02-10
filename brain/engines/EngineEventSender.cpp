#include "EngineEventSender.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"

using brain::engines::CriticalAlertFilter;
using brain::engines::EngineEventSender;
using brain::engines::security_events::SecurityEventFrame;
using brain::sender_events::CriticalEventAlert;

EngineEventSender::EngineEventSender(brain::events::EventPriority   priority,
                                     MessageRepositoryPtr           msgRepository,
                                     IDSPeriodicReportSerializerPtr reportSerializer,
                                     EventNoiseFilterPtr            eventNoiseFilter)
  : m_reportSerializer{reportSerializer}
  , m_priority{priority}
  , m_messageRepository{msgRepository}
  , m_eventNoiseFilter{eventNoiseFilter}
{
}

EngineEventSender::SendStatus
EngineEventSender::CanSendNoiseFilter(SensorDataTag sdTag, size_t eventSize) const
{
    if ((nullptr != m_eventNoiseFilter)
        && m_eventNoiseFilter->IsDoubleFilteredOut(static_cast<uint32_t>(sdTag), eventSize))
    {
        LOG_WARNING << "Event of SD with tag " << static_cast<uint32_t>(sdTag)
                    << " was filtered out by the event noise filter" << LOG_NOOP;
        return SendStatus::NoiseFilterError;
    }

    return SendStatus::Success;
}

EngineEventSender::SendStatus
EngineEventSender::SendUnfilteredEvent(cm::optional<std::vector<uint8_t>> const& serializedRuleEval,
                                       SensorDataTag                             sdTag,
                                       size_t                                    eventSize)
{
    if (!serializedRuleEval.has_value())
    {
        LOG_ERROR << "Failed to serialize null values" << LOG_NOOP;
        return SendStatus::EmptyRuleEval;
    }

    SendStatus status = CanSendNoiseFilter(sdTag, eventSize);
    if (status != SendStatus::Success)
    {
        LOG_ERROR << "Event noise filtered" << LOG_NOOP;
        return status;
    }

    if ((m_messageRepository != nullptr)
        && !m_messageRepository->Push(std::make_unique<std::vector<uint8_t>>(*serializedRuleEval), m_priority))
    {
        LOG_ERROR << "Failed to add event" << LOG_NOOP;
        return SendStatus::Failed;
    }

    LOG_DEBUG << "Event successfully sent" << LOG_NOOP;

    return SendStatus::Success;
}

EngineEventSender::SendStatus
EngineEventSender::SendEvent(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval,
                             SensorDataTag                                                  sdTag,
                             brain::sender_events::CriticalEventAlert                       event,
                             SecurityEventFrame                                             frame,
                             size_t                                                         eventSize)
{
    if (nullptr == m_reportSerializer)
    {
        LOG_ERROR << "Report serializer is null" << LOG_NOOP;
        return SendStatus::Failed;
    }
    
    if (0U == ruleEval.which_RuleData)
    {
        LOG_ERROR << "Empty rule evaluation" << LOG_NOOP;
        return SendStatus::EmptyRuleEval;
    }

    auto serializedRuleEval = m_reportSerializer->Serialize(ruleEval);

#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
    if ((CriticalEventAlert::MaxEventName != event) && !CriticalAlertFilter::GetInstance().CanSend(event, frame))
    {
        LOG_ERROR << "Processing engine of SD with tag " << static_cast<uint32_t>(sdTag)
                  << " - stopped due to reaching the send limit" << LOG_NOOP;
        return SendStatus::Failed;
    }
#endif

    auto sentSize = (EngineEventSender::EVENT_MAX_SIZE <= eventSize)
                        ? (serializedRuleEval.has_value() ? serializedRuleEval->size() : 0U)
                        : eventSize;

    return SendUnfilteredEvent(serializedRuleEval, sdTag, sentSize);
}