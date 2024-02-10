/**
 * @file
 * @brief     A rule engine for the Unkown Constrain Id events
 */
#include "UnknownConstraintEngine.hpp"
#include "brain/brain_app/BrainApp.hpp"
#include "brain/engines/CriticalAlertFilter.hpp"
#include "brain/engines/PPE/EngineDispatcher.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"

using brain::engines::CriticalAlertFilter;
using brain::engines::swpac::UnknownConstraintEngine;
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

UnknownConstraintEngine::UnknownConstraintEngine(CounterManagerPtr                                 debugCounters,
                                                 MessageRepositoryPtr                              msgRepository,
                                                 EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                                                 EventNoiseFilterPtr                               eventNoiseFilter,
                                                 events::EventPriority                             priority)
  : EngineEventSender(priority, msgRepository, reportSerializer, eventNoiseFilter)
{
    if (debugCounters)
    {
        m_failedCounter
            = debugCounters->CreateCounter(common::counters::warning::UNKNOWN_CONSTRAIN_ID_ALERT_FAILED_COUNTER_NAME,
                                           EventCounter::EventCounterLevelType::COUNTER_WARNING);
        m_alertSendCounter
            = debugCounters->CreateCounter(common::counters::debug::UNKNOWN_CONSTRAIN_ID_ALERT_COUNTER_NAME,
                                           EventCounter::EventCounterLevelType::COUNTER_DEBUG);
    }
}

bool
UnknownConstraintEngine::sendAlertExt(std::string const& constraintId, std::string const& incident)
{
    auto* app = brain::app_mng::BrainApp::GetInstance();
    if (nullptr == app)
    {
        LOG_ERROR << "Handling Unknown Constraint id Events - brain app not initialized" << LOG_NOOP;
        return false;
    }

    auto engDispacher = std::static_pointer_cast<brain::engines::EngineDispatcher>(app->GetEngineDispatcher());

    if (!engDispacher)
    {
        LOG_ERROR << "Handling Unknown Constraint id Events - cannot get brain app instance" << LOG_NOOP;
        return false;
    }

    auto engine = engDispacher->GetUnkownConstraintEngine();
    if (!engine)
    {
        LOG_ERROR << "Handling Unknown Constraint id Events - cannot get SE engine" << LOG_NOOP;
        return false;
    }

    engine->sendAlert(constraintId, incident);

    return true;
}

bool
UnknownConstraintEngine::sendAlert(std::string const& constraintId, std::string const& incident)
{
    if (!CriticalAlertFilter::GetInstance().CanSend(brain::sender_events::CriticalEventAlert::DhmUnkownConstrainId,
                                                    incident))
    {
        LOG_ERROR << "Processing engine of SD with tag "
                  << static_cast<uint32_t>(SensorDataTag::SD_SWPAC_UNKNOWN_CONSTRAINT_ID)
                  << " - stopped due to reaching the send limit" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCounter);
        return false;
    }

    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;

    com_vwg_connect_ids_idsperiodicreport_v1_DhmIncidentWithUnknownConstraintIdAlert alert
        = com_vwg_connect_ids_idsperiodicreport_v1_DhmIncidentWithUnknownConstraintIdAlert_init_default;

    alert.constraintId = common::nanopb::CreateEncodingCallback(constraintId);
    alert.incident     = common::nanopb::CreateEncodingCallback(incident);

    auto const currentTime = common::Time::GetCurrentTimeMilliSec();
    ruleEval.ruleEvaluationId = currentTime;
    ruleEval.timestamp        = currentTime;
    ruleEval.which_RuleData   = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_dhmIncidentWithUnknownConstraintIdAlert_tag);
    ruleEval.RuleData.dhmIncidentWithUnknownConstraintIdAlert = alert;
    
    auto serializedRuleEval = m_reportSerializer->Serialize(ruleEval);
    auto const status = SendUnfilteredEvent(serializedRuleEval,
                                            SensorDataTag::SD_SWPAC_UNKNOWN_CONSTRAINT_ID,
                                            serializedRuleEval->size());

    if (EngineEventSender::SendStatus::Success == status)
    {
        LOG_DEBUG << "Kernel Panic event sent" << LOG_NOOP;
        common::counters::IncreaseCounter(m_alertSendCounter);
    }
    else
    {
        LOG_ERROR << "Failed to add kernel panic event" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCounter);
    }
    
    return EngineEventSender::SendStatus::Success == status;
}