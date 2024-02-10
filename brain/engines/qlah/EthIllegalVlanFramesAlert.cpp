#include "EthIllegalVlanFramesAlert.hpp"
#include "brain/config/AlertEventsNames.hpp"
#include "common/counter_manager/CounterNames.hpp"

using brain::engines::qlah::EventAlertBase;
using brain::engines::qlah::EthIllegalVlanFramesAlert;
using brain::sender_events::CriticalEventAlert;

EthIllegalVlanFramesAlert::EthIllegalVlanFramesAlert(CounterManagerPtr    debugCounters,
                                                     MessageRepositoryPtr messageRepository,
                                                     EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                                                     EventNoiseFilterPtr                               eventNoiseFilter,
                                                     events::EventPriority                             priority)
  : EventAlertBase(messageRepository, reportSerializer, eventNoiseFilter, priority)
  , m_illegalVlangTable{30U}
{
    if (debugCounters)
    {
        m_failedCounter = debugCounters->CreateCounter(
            common::counters::warning::QLAH_ILLEGAL_VLANG_FRAME_ALERT_FAILED_COUNTER_NAME,
            EventCounter::EventCounterLevelType::COUNTER_WARNING);
        m_alertSendCounter
            = debugCounters->CreateCounter(common::counters::debug::QLAH_ILLEGAL_VLANG_FRAME_ALERT_SENT_COUNTER_NAME,
                                           EventCounter::EventCounterLevelType::COUNTER_DEBUG);
    }
    else
    {
        LOG_WARNING << "null debug counter passed" << LOG_NOOP;
    }
}

void
EthIllegalVlanFramesAlert::sendAlert(std::string const& id, uint64_t count)
{
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;

    com_vwg_connect_ids_idsperiodicreport_v1_IllegalVlanDropValueAlert alert
        = com_vwg_connect_ids_idsperiodicreport_v1_IllegalVlanDropValueAlert_init_default;

    alert.id                   = common::nanopb::CreateEncodingCallback(id);
    
    uint32_t illegalVlanDropValue = static_cast<uint32_t>(count);
    if (count >= std::numeric_limits<uint32_t>::max())
    {
        LOG_WARNING << "alert count overflow " << count << LOG_NOOP;
        illegalVlanDropValue = std::numeric_limits<uint32_t>::max();
    }
    alert.illegalVlanDropValue = illegalVlanDropValue;
    
    ruleEval.which_RuleData = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_illegalVlanDropValueAlert_tag);
    ruleEval.RuleData.illegalVlanDropValueAlert = alert;

    sendRuleAlert(ruleEval, SensorDataTag::SD_QLAH_ETH, CriticalEventAlert::QlahIllegalVlanFrame);
}

void
EthIllegalVlanFramesAlert::Update(std::string const& id, uint64_t count)
{
    auto it
        = m_illegalVlangTable.emplace(std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple(0ULL));

    if (!common::types::IsMapSizeExceeded(m_illegalVlangTable, it) && (count > it.first->second))
    {
        sendAlert(id, (count - it.first->second));

        it.first->second = count;
    }
}