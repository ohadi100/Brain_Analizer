#pragma once

#include "brain/engines/EngineEventSender.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "common/utils/os/time/TimeWrapper.hpp"
namespace brain
{
namespace engines
{
namespace qlah
{

class EventAlertBase : public brain::engines::EngineEventSender
{
public:
    using ConfigurationPtr   = common::configuration::Pointer;
    using EventCounter       = common::counters::EventCounter;
    using CriticalEventAlert = brain::sender_events::CriticalEventAlert;
    using Message            = brain::messageRepository::MessageRepositoryInterface::Message;
    using EventCounterPtr    = std::shared_ptr<common::counters::EventCounter>;

    EventAlertBase(MessageRepositoryPtr                              messageRepository,
                   EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                   EventNoiseFilterPtr                               eventNoiseFilter,
                   events::EventPriority priority = events::EventPriority::Important)
      : EngineEventSender(priority, messageRepository, reportSerializer, eventNoiseFilter)
    {
    }

protected:
    void
    sendRuleAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                  SensorDataTag                                            SDtag,
                  CriticalEventAlert                                       event)
    {
        auto const currentTime    = common::Time::GetCurrentTimeMilliSec();
        ruleEval.ruleEvaluationId = currentTime;
        ruleEval.timestamp        = currentTime;

        auto const status = SendEvent(ruleEval, SDtag, event);

        common::counters::IncreaseCounter((EngineEventSender::SendStatus::Success != status) ? m_failedCounter
                                                                                             : m_alertSendCounter);
    }

    EventCounterPtr m_failedCounter;
    EventCounterPtr m_alertSendCounter;
};

}  // namespace qlah
}  // namespace engines
}  // namespace brain
