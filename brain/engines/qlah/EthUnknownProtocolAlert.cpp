#include "EthUnknownProtocolAlert.hpp"
#include "brain/config/AlertEventsNames.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "common/counter_manager/CounterNames.hpp"

using brain::engines::qlah::EthUnknownProtocolAlert;
using brain::engines::qlah::EventAlertBase;
using brain::sender_events::CriticalEventAlert;

namespace brain
{
namespace engines
{
namespace qlah
{
static constexpr size_t UnknownProtocolCounterTableLimit{30U};
}
}  // namespace engines
}  // namespace brain

EthUnknownProtocolAlert::EthUnknownProtocolAlert(CounterManagerPtr                                 debugCounters,
                                                 MessageRepositoryPtr                              messageRepository,
                                                 EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                                                 EventNoiseFilterPtr                               eventNoiseFilter,
                                                 events::EventPriority                             priority)
  : EventAlertBase(messageRepository, reportSerializer, eventNoiseFilter, priority)
  , m_unknownProtocolTable{UnknownProtocolCounterTableLimit}
{
    if (debugCounters)
    {
        m_failedCounter = debugCounters->CreateCounter(
            common::counters::warning::QLAH_UNKNOWN_PROTOCOL_FRAME_ALERT_FAILED_COUNTER_NAME,
            EventCounter::EventCounterLevelType::COUNTER_WARNING);
        m_alertSendCounter
            = debugCounters->CreateCounter(common::counters::debug::QLAH_UNKNOWN_PROTOCOL_FRAME_ALERT_SENT_COUNTER_NAME,
                                           EventCounter::EventCounterLevelType::COUNTER_DEBUG);
    }
    else
    {
        LOG_WARNING << "null debug counter passed" << LOG_NOOP;
    }
}

void
EthUnknownProtocolAlert::Update(std::string const& id, uint64_t count)
{
    auto it = m_unknownProtocolTable.emplace(
        std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple(0ULL));

    if (!common::types::IsMapSizeExceeded(m_unknownProtocolTable, it) && (count > it.first->second))
    {
        sendAlert(id, (count - it.first->second));

        it.first->second = count;
    }
}

void
EthUnknownProtocolAlert::sendAlert(std::string const& id, uint64_t count)
{
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;

    com_vwg_connect_ids_idsperiodicreport_v1_UnknownProtocolDroppedFramesCounterAlert alert
        = com_vwg_connect_ids_idsperiodicreport_v1_UnknownProtocolDroppedFramesCounterAlert_init_default;

    alert.id                                       = common::nanopb::CreateEncodingCallback(id);
    
    uint32_t unknownProtocolDroppedFramesCounterValue = static_cast<uint32_t>(count);
    if (count >= std::numeric_limits<uint32_t>::max())
    {
        LOG_WARNING << "alert count overflow " << count << LOG_NOOP;
        unknownProtocolDroppedFramesCounterValue = std::numeric_limits<uint32_t>::max();
    }
    alert.unknownProtocolDroppedFramesCounterValue = unknownProtocolDroppedFramesCounterValue;

    ruleEval.which_RuleData = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_unknownProtocolDroppedFramesCounterAlert_tag);
    ruleEval.RuleData.unknownProtocolDroppedFramesCounterAlert = alert;

    sendRuleAlert(ruleEval, SensorDataTag::SD_QLAH_ETH, CriticalEventAlert::QlahUnknownProtocolFramesValue);
}