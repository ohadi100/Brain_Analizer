/**
 * @file
 * @brief     This file contains the functionality of the PeriodicStatisticsEngine class
 */
#include "PeriodicStatisticsEngine.hpp"

#include "brain/config/AlertEventsNames.hpp"
#include "brain/events/EventPriority.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/sensor_data/SensorDataTypes.hpp"
#include "common/utils/os/time/Time.hpp"


using namespace common::counters;
using namespace brain::sender_events;
using brain::engines::PeriodicStatisticsEngine;
using brain::engines::ReturnCode;
using common::sensor_data::PeriodicStatisticsSensorData;
using common::sensor_data::SDPriority;
using common::sensor_data::SensorDataTag;
using common::utils::Logger;
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;
using Message               = brain::messageRepository::MessageRepositoryInterface::Message;

PeriodicStatisticsEngine::PeriodicStatisticsEngine(
    CounterManagerPtr                                      debugCounters,
    MessageRepositoryPtr                                   msgRepository,
    std::unordered_map<uint32_t, std::shared_ptr<Engine>>& periodicEngines,
    DiagnosticsManagerPtr                                  diagnosticsManager,
    EngineEventSender::IDSPeriodicReportSerializerPtr      reportSerializer,
    EventNoiseFilterPtr                                    eventNoiseFilter,
    EventPriority                                          priority)
  : EngineEventSender(priority, msgRepository, reportSerializer, eventNoiseFilter)
  , m_debugCounters(debugCounters)
{
    if (m_debugCounters)
    {

        m_failedProcessCounter = m_debugCounters->CreateCounter(
            warning::PERIODIC_STATISTICS_ENGINE_FAILED_PROCESS_COUNTER_NAME, EventCounterLevelType::COUNTER_WARNING);
        m_noAvailableStorageCounter = m_debugCounters->CreateCounter(
            errors::LACK_OF_AVAILABLE_STORAGE(
                static_cast<uint8_t>(common::sensor_data::SensorDataTag::SD_PERIODIC_STATISTICS)),
            EventCounterLevelType::COUNTER_ERROR);
        m_measurementIntervalStartedCounter = m_debugCounters->CreateCounter(
            debug::MEASUREMENT_INTERVALS_STARTED_COUNTER_NAME, EventCounterLevelType::COUNTER_DEBUG);
        m_measurementIntervalEndedCounter = m_debugCounters->CreateCounter(
            debug::MEASUREMENT_INTERVALS_ENDED_COUNTER_NAME, EventCounterLevelType::COUNTER_DEBUG);

        for (uint8_t priorityIndex = 0U; priorityIndex < static_cast<uint8_t>(SDPriority::NUM_OF_SD_PRIORITIES); ++priorityIndex)
        {
            m_queueManagerEnqueueSuccessCounters[priorityIndex]
                = debugCounters->GetCounter(debug::SUCCESS_ENQUEUE_SD_TO_WRR_QUEUE(priorityIndex));
            m_queueManagerEnqueueFailCounters[priorityIndex]
                = debugCounters->GetCounter(errors::FAIL_ENQUEUE_SD_TO_WRR_QUEUE(priorityIndex));
        }

        for (uint8_t priorityIndex = 0U; priorityIndex < static_cast<uint8_t>(EventPriority::NUM_OF_EVENT_PRIORITIES);
             ++priorityIndex)
        {
            m_eventsStorageEnqueueSuccessCounters[priorityIndex]
                = debugCounters->GetCounter(debug::SUCCESS_ENQUEUE_EVENT_TO_WRR_QUEUE(priorityIndex));
            m_eventsStorageEnqueueFailCounters[priorityIndex]
                = debugCounters->GetCounter(debug::FAIL_ENQUEUE_EVENT_TO_WRR_QUEUE(priorityIndex));
        }
    }
}


bool
PeriodicStatisticsEngine::createRuleEvaluation(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval)
{
    com_vwg_connect_ids_idsperiodicreport_v1_IdsStatisticsPeriodicReport statisticsPeriodicReport
        = com_vwg_connect_ids_idsperiodicreport_v1_IdsStatisticsPeriodicReport_init_default;

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    ruleEval.which_RuleData   = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_idsStatisticsPeriodicReport_tag);
    ruleEval.RuleData.idsStatisticsPeriodicReport = statisticsPeriodicReport;

    return true;
}


ReturnCode
PeriodicStatisticsEngine::processInternal(UPSensorData sd)
{
    try
    {
        LOG_INFO << "[PeriodicReportFlow] Generating periodic report" << LOG_NOOP;

        // make sure the input SD can be processed by this engine (will throw on error)
        std::ignore = dynamic_cast<PeriodicStatisticsSensorData&>(*sd);

        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
            = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
        std::ignore = createRuleEvaluation(ruleEval);

        auto const& serializedRuleEval
            = common::nanopb::EncodeNanoPb<com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_fields>(ruleEval);

        bool status = SendEvent(
                      serializedRuleEval, SensorDataTag::SD_PERIODIC_STATISTICS, CriticalEventAlert::PeriodicStatistics)
                  == EngineEventSender::SendStatus::Success;
        LOG_INFO << "[PeriodicReportFlow] Periodic report sent " << (EngineEventSender::SendStatus::Success == status)
                 << ", report size " << serializedRuleEval->size() << LOG_NOOP;


        common::counters::IncreaseCounter(m_measurementIntervalEndedCounter);
        common::counters::IncreaseCounter(m_measurementIntervalStartedCounter);
        return ReturnCode::Success;
    }
    catch (std::bad_cast const& /*e*/)
    {
        LOG_ERROR << "[PeriodicReportFlow] SD cannot be cast to PeriodicStatisticsSensorData!" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedProcessCounter);
        return ReturnCode::CastError;
    }
}
