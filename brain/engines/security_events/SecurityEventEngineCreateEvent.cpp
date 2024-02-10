/**
 * @file
 * @brief      This file implements the functionality of SE engines that create events
 */

#include "SecurityEventEngineCreateEvent.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"

using brain::engines::security_events::SecurityEventEngineCreateEvent;
namespace brain
{
namespace engines
{
namespace security_events
{
using Message = brain::messageRepository::MessageRepositoryInterface::Message;
}
}  // namespace engines
}  // namespace brain

static std::vector<common::nanopb::Array>
initEventDataToSerialize() noexcept
{
    return std::vector<common::nanopb::Array>{};
}
std::vector<common::nanopb::Array> SecurityEventEngineCreateEvent::m_eventDataToSerialize = initEventDataToSerialize();

bool
SecurityEventEngineCreateEvent::addEventAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval,
                                              brain::sender_events::CriticalEventAlert                       event,
                                              SecurityEventSensorData const&                                 sd)
{
    auto status
        = SendEvent(ruleEval, SensorDataTag::SD_SECURITY_EVENT, event, sd.GetEventFrame(), sd.GetContextData().size());

    if (EngineEventSender::SendStatus::Success != status)
    {
        if (EngineEventSender::SendStatus::EmptyRuleEval == status)
        {
            clearEventDataToSerialize();
        }
        common::counters::IncreaseCounter(m_failedCounter);
    }
    else
    {
        clearEventDataToSerialize();
    }

    return EngineEventSender::SendStatus::Success
           == status;  // the process succeded, lack of storage in the sender is not related to the engine success.
}