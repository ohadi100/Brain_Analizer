#include "SwpacEngineBase.hpp"
#include "autogen/nanopb/NanoPbInclude.hpp"
#include "brain/config/AlertEventsNames.hpp"
#include "brain/engines/security_events/NanoPbMacros.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/counter_manager/counters/EventCounter.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"

using brain::engines::swpac::SwpacEngineBase;
using namespace brain::sensor_data;
using namespace brain::sender_events;
using namespace common::counters;
namespace brain
{
namespace engines
{
namespace swpac
{
using Message = brain::messageRepository::MessageRepositoryInterface::Message;
}
}  // namespace engines
}  // namespace brain

SwpacEngineBase::SwpacEngineBase(CounterManagerPtr                                 debugCounters,
                                 events::EventPriority                             priority,
                                 MessageRepositoryPtr                              msgRepository,
                                 EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                                 EventNoiseFilterPtr                               eventNoiseFilter)
  : EngineEventSender(priority, msgRepository, reportSerializer, eventNoiseFilter)
{
    if (debugCounters)
    {
        m_failedCounter    = debugCounters->CreateCounter(STRING_SIZE_LIMIT_ALERT_FAILED_COUNTER_NAME,
                                                       EventCounter::EventCounterLevelType::COUNTER_WARNING);
        m_alertSendCounter = debugCounters->CreateCounter(STRING_SIZE_LIMIT_ALERT_SENT_COUNTER_NAME,
                                                          EventCounter::EventCounterLevelType::COUNTER_DEBUG);
    }
}

bool
SwpacEngineBase::sendStringSizeAlert(common::sensor_data::SensorDataTag      sdTag,
                                     brain::sensor_data::swpac::ConstraintId constrainId,
                                     SwpacSensorDataBase::AlertData const&   ad)
{
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;

    com_vwg_connect_ids_idsperiodicreport_v1_DhmIncidentStringSizeAlert dhmIncidentStringSizeAlert
        = com_vwg_connect_ids_idsperiodicreport_v1_DhmIncidentStringSizeAlert_init_default;

    LOG_DEBUG << "Sending " << ad.stringDetails.size() << " size limit alerts" << LOG_NOOP;
    auto const& constraintId = brain::sensor_data::swpac::GetConstraintIdString(constrainId);
    for (auto const& stringDetail : ad.stringDetails)
    {
        dhmIncidentStringSizeAlert.timestamp
            = (0U == ad.timestampSecondsSinceEpoch) ? common::MS_TO_S(m_currentTime) : ad.timestampSecondsSinceEpoch;
        dhmIncidentStringSizeAlert.constraintId = common::nanopb::CreateEncodingCallback(constraintId);
        dhmIncidentStringSizeAlert.reference    = common::nanopb::CreateEncodingCallback(ad.reference);
        INIT_NPB_FIELD(dhmIncidentStringSizeAlert, id, stringDetail.id);
        dhmIncidentStringSizeAlert.stringSizeLimit    = SwpacSensorDataBase::MaximumSizeStringType;
        dhmIncidentStringSizeAlert.receivedStringSize = stringDetail.receivedStringSize;

        ruleEval.ruleEvaluationId = m_currentTime;
        ruleEval.timestamp        = m_currentTime;
        ruleEval.which_RuleData   = static_cast<pb_size_t>(
            com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_dhmIncidentStringSizeAlert_tag);
        ruleEval.RuleData.dhmIncidentStringSizeAlert = dhmIncidentStringSizeAlert;

        auto const status = SendEvent(ruleEval, sdTag, CriticalEventAlert::DhmStringSizeLimit);
        if (EngineEventSender::SendStatus::Success != status)
        {
            common::counters::IncreaseCounter(m_failedCounter);
            return false;
        }

        common::counters::IncreaseCounter(m_alertSendCounter);
        LOG_DEBUG << "String size limit alert sent" << LOG_NOOP;
    }  // stringDetails

    return true;
}
