/**
 * @file
 * @brief     This file contains the functionality of the PeriodicStatisticsEngine class
 */
#include "PeriodicStatisticsEngine.hpp"
#include "CriticalAlertFilter.hpp"
#include "brain/config/AlertEventsNames.hpp"
#include "brain/diagnostics/PPE/AdaptationValuesConstants.hpp"
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "brain/engines/swpac/IncidentCounterTable.hpp"
#include "brain/events/EventPriority.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/sensor_data/SensorDataTypes.hpp"
#include "common/utils/os/time/Time.hpp"
#include "brain/sender/publishers/utils/message_size_check/ExceededMessageSizeCheck.hpp"

using namespace common::counters;
using namespace brain::sender_events;
using brain::engines::PeriodicStatisticsEngine;
using brain::engines::ReturnCode;
using brain::engines::qlah::EthEngine;
using brain::engines::qlah::HostEngine;
using brain::engines::security_events::SecurityEventsEngine;
using brain::engines::swpac::KernelLogEngine;
using brain::engines::swpac::ProcessPerformanceEngine;
using common::sensor_data::PeriodicStatisticsSensorData;
using common::sensor_data::SDPriority;
using common::sensor_data::SensorDataTag;
using common::utils::Logger;
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;
using brain::engines::security_events::nanopb::PassedDroppedAlertsData;


PeriodicStatisticsEngine::PeriodicStatisticsEngine(const PeriodicStatisticsEngineConfig& config)
  : EngineEventSender(config.priority, config.msgRepository, config.reportSerializer, config.eventNoiseFilter)
  , m_exceededMessageSizeCheck(config.exceededMessageSizeCheck)
  , m_debugCounters(config.debugCounters)
  , m_ethEngine(
        std::dynamic_pointer_cast<EthEngine>(config.periodicEngines[static_cast<uint32_t>(SensorDataTag::SD_QLAH_ETH)]))
  , m_hostEngine(std::dynamic_pointer_cast<HostEngine>(
        config.periodicEngines[static_cast<uint32_t>(SensorDataTag::SD_QLAH_HOST)]))
  , m_securityEventsEngine(std::dynamic_pointer_cast<SecurityEventsEngine>(
        config.periodicEngines[static_cast<uint32_t>(SensorDataTag::SD_SECURITY_EVENT)]))
  , m_processPerformanceEngine(std::dynamic_pointer_cast<ProcessPerformanceEngine>(
        config.periodicEngines[static_cast<uint32_t>(SensorDataTag::SD_SWPAC_PROCESS_PERFORMANCE_REPORT)]))
  , m_hostErrorMonitoringOn(config.diagnosticsManager->GetFeatureFlag(
        brain::adaptation_values_names::AdaptationId::HOST_ERROR_MONITORING_ON))
  , m_monitoringPeriodStartTimestampMs(
        common::Time::GetCurrentTimeMilliSec())  // first report start timestamp is creation of the class, next report
                                                 // start timestamp is created in createIdsStatisticsPeriodicReport
{
    if (m_debugCounters)
    {
        m_secEveMonitorDataExistCounter = m_debugCounters->CreateCounter(
            debug::PERIODIC_STATISTICS_HAS_SECURITY_EVENTS_MONITORING_DATA, EventCounterLevelType::COUNTER_DEBUG);
        m_passedDroppedMonitoringDataExistCounter = m_debugCounters->CreateCounter(
            debug::PERIODIC_STATISTICS_HAS_PASSED_DROPPED_INCIDENTS_DATA, EventCounterLevelType::COUNTER_DEBUG);
        m_ethMonitoringTableExistCounter = m_debugCounters->CreateCounter(
            debug::PERIODIC_STATISTICS_HAS_ETH_MONITORING_TABLE, EventCounterLevelType::COUNTER_DEBUG);
        m_hostErrorMonitoringDataExistCounter = m_debugCounters->CreateCounter(
            debug::PERIODIC_STATISTICS_HAS_HOST_ERROR_MONITORING_COUNTERS_DATA, EventCounterLevelType::COUNTER_DEBUG);
        m_processPerformanceDataExistsCounter = m_debugCounters->CreateCounter(
            debug::PERIODIC_STATISTICS_HAS_PROCESS_PERFORMANCE_MONITORING_DATA, EventCounterLevelType::COUNTER_DEBUG);

        m_failedCounter = m_debugCounters->CreateCounter(
            warning::PERIODIC_STATISTICS_ENGINE_FAILED_PROCESS_COUNTER_NAME, EventCounterLevelType::COUNTER_WARNING);
        m_measurementIntervalStartedCounter = m_debugCounters->CreateCounter(
            debug::MEASUREMENT_INTERVALS_STARTED_COUNTER_NAME, EventCounterLevelType::COUNTER_DEBUG);
        m_measurementIntervalEndedCounter = m_debugCounters->CreateCounter(
            debug::MEASUREMENT_INTERVALS_ENDED_COUNTER_NAME, EventCounterLevelType::COUNTER_DEBUG);
        m_dhmIncidentCounterCounter
            = m_debugCounters->CreateCounter(debug::DHM_INCIDENT_COUNTER_NAME, EventCounterLevelType::COUNTER_DEBUG);
        m_hcp1StatisticsPeriodcReportCounter = m_debugCounters->CreateCounter(
            debug::HCP1_STATISTICS_PERIODIC_REPORT_COUNTER_NAME, EventCounterLevelType::COUNTER_DEBUG);
        m_exceededMessageSizeCounter = m_debugCounters->CreateCounter(debug::EXCEEDED_MESSAGE_SIZE_COUNTER_NAME,
                                                                      EventCounterLevelType::COUNTER_DEBUG);

        for (uint8_t priorityIndex = 0U; priorityIndex < static_cast<uint8_t>(SDPriority::NUM_OF_SD_PRIORITIES); ++priorityIndex)
        {
            m_queueManagerEnqueueSuccessCounters[priorityIndex]
                = config.debugCounters->GetCounter(debug::SUCCESS_ENQUEUE_SD_TO_WRR_QUEUE(priorityIndex));
            m_queueManagerEnqueueFailCounters[priorityIndex]
                = config.debugCounters->GetCounter(errors::FAIL_ENQUEUE_SD_TO_WRR_QUEUE(priorityIndex));
        }

        for (uint32_t priorityIndex = 0U; priorityIndex < static_cast<uint32_t>(EventPriority::NUM_OF_EVENT_PRIORITIES);
             ++priorityIndex)
        {
            m_eventsStorageEnqueueSuccessCounters[priorityIndex]
                = config.debugCounters->GetCounter(debug::SUCCESS_ENQUEUE_EVENT_TO_WRR_QUEUE(priorityIndex));
            m_eventsStorageEnqueueFailCounters[priorityIndex]
                = config.debugCounters->GetCounter(debug::FAIL_ENQUEUE_EVENT_TO_WRR_QUEUE(priorityIndex));
        }
    }
    LOG_INFO << "[PeriodicReportFlow] Starting new monitoring period on startup" << m_monitoringPeriodStartTimestampMs
             << LOG_NOOP;
}

bool
PeriodicStatisticsEngine::SerializePassedDroppedIncidentsData(
    com_vwg_connect_ids_idsperiodicreport_v1_PassedDroppedIncidentsData& passedDroppedIncidentsBuffer) const noexcept
{
    LOG_DEBUG << "[PeriodicReportFlow] SerializePassedDroppedIncidentsData" << LOG_NOOP;

    // If there debugCounters isn't available, can't generate alert
    if (!m_debugCounters)
    {
        LOG_WARNING
            << "[PeriodicReportFlow] Couldn't serialize PassedDroppedIncidentsData because debugCounters is nullptr"
            << LOG_NOOP;
        return false;
    }

    passedDroppedIncidentsBuffer.creationTimeStamp = m_currentTime;

// Noise filter counters
#define SERIALIZE_NF_COUNTERS(MEMBER, COUNTER)                                                                \
    do                                                                                                        \
    {                                                                                                         \
        if ((m_debugCounters->GetCounter(common::counters::warning::COUNTER)->GetEventCounter() > 0U)         \
            || (m_debugCounters->GetCounter(common::counters::debug::NOT_##COUNTER)->GetEventCounter() > 0U)) \
        {                                                                                                     \
            passedDroppedIncidentsBuffer.has_##MEMBER = true;                                                 \
            passedDroppedIncidentsBuffer.MEMBER.filteredCounter                                               \
                = m_debugCounters->GetCounter(common::counters::warning::COUNTER)->GetAndResetCounter();      \
            passedDroppedIncidentsBuffer.MEMBER.passedCounter                                                 \
                = m_debugCounters->GetCounter(common::counters::debug::NOT_##COUNTER)->GetAndResetCounter();  \
        }                                                                                                     \
    } while (false)

    // Cumulative noise filter
    SERIALIZE_NF_COUNTERS(sensorNFCounters, FILTERED_OUT_BY_SENSOR_NF_COUNTER);
    SERIALIZE_NF_COUNTERS(groupNFCounters, FILTERED_OUT_EVENT_BY_GROUP_NF_COUNTER);

    // Sensor noise filter counters
    SERIALIZE_NF_COUNTERS(qlahEthSensorNFCounters, FILTERED_QLAH_ETH_SENSOR_SD_SENSOR_NF_COUNTER);
    SERIALIZE_NF_COUNTERS(qlahHostSensorNFCounters, FILTERED_QLAH_HOST_SENSOR_SD_SENSOR_NF_COUNTER);
    SERIALIZE_NF_COUNTERS(swpacKernelLogSensorNFCounters, FILTERED_SWPAC_KERNEL_LOG_SD_SENSOR_NF_COUNTER);
    SERIALIZE_NF_COUNTERS(swpacTlsErrorSensorNFCounters, FILTERED_SWPAC_TLS_ERROR_REPORT_SD_SENSOR_NF_COUNTER);
    SERIALIZE_NF_COUNTERS(swpacProcessMonitoringSensorNFCounters,
                          FILTERED_SWPAC_PROCESS_PERFORMANCE_SD_SENSOR_NF_COUNTER);
    SERIALIZE_NF_COUNTERS(securityEventSensorNFCounters, FILTERED_SECURITY_EVENT_SD_SENSOR_NF_COUNTER);
    SERIALIZE_NF_COUNTERS(intelligentSensorNFCounters, FILTERED_INTELLIGENT_SD_SENSOR_NF_COUNTER);
    SERIALIZE_NF_COUNTERS(sacidSensorNFCounters, FILTERED_SACID_SD_SENSOR_NF_COUNTER);

    // Group noise filters
    SERIALIZE_NF_COUNTERS(periodicGroupNFCounters, FILTERED_PERIODIC_GROUP_NF_COUNTER);
    SERIALIZE_NF_COUNTERS(ethSensorGroupNFCounters, FILTERED_ETH_SENSOR_GROUP_NF_COUNTER);
    SERIALIZE_NF_COUNTERS(ethHostGroupNFCounters, FILTERED_HOST_SENSOR_GROUP_NF_COUNTER);
    SERIALIZE_NF_COUNTERS(tlsErrorGroupNFCounters, FILTERED_TLS_ERROR_REPORT_GROUP_NF_COUNTER);
    SERIALIZE_NF_COUNTERS(securityEventGroupNFCounters, FILTERED_SECURITY_EVENT_GROUP_NF_COUNTER);
    SERIALIZE_NF_COUNTERS(intelligentGroupNFCounters, FILTERED_INTELLIGENT_GROUP_NF_COUNTER);
#undef SERIALIZE_NF_COUNTERS

// QueueManager queue counters
#define SERIALIZE_QM_QUEUE_COUNTERS(MEMBER, PRIORITY)                                   \
    do                                                                                  \
    {                                                                                   \
        if (m_queueManagerEnqueueFailCounters[PRIORITY]->GetEventCounter() > 0U         \
            || m_queueManagerEnqueueSuccessCounters[PRIORITY]->GetEventCounter() > 0U)  \
        {                                                                               \
            passedDroppedIncidentsBuffer.has_##MEMBER = true;                           \
            passedDroppedIncidentsBuffer.MEMBER.filteredCounter                         \
                = m_queueManagerEnqueueFailCounters[PRIORITY]->GetAndResetCounter();    \
            passedDroppedIncidentsBuffer.MEMBER.passedCounter                           \
                = m_queueManagerEnqueueSuccessCounters[PRIORITY]->GetAndResetCounter(); \
        }                                                                               \
    } while (false)

    SERIALIZE_QM_QUEUE_COUNTERS(queueManagerCriticalQueueCounters, SDPriority::Critical);
    SERIALIZE_QM_QUEUE_COUNTERS(queueManagerImportantQueueCounters, SDPriority::Important);
    SERIALIZE_QM_QUEUE_COUNTERS(queueManagerNormalQueueCounters, SDPriority::Normal);
    SERIALIZE_QM_QUEUE_COUNTERS(queueManagerLowQueueCounters, SDPriority::Low);
#undef SERIALIZE_QM_QUEUE_COUNTERS

// EventsStorage queue counters
#define SERIALIZE_ES_QUEUE_COUNTERS(member, priority)                                    \
    do                                                                                   \
    {                                                                                    \
        if (m_eventsStorageEnqueueFailCounters[priority]->GetEventCounter() > 0U         \
            || m_eventsStorageEnqueueSuccessCounters[priority]->GetEventCounter() > 0U)  \
        {                                                                                \
            passedDroppedIncidentsBuffer.has_##member = true;                            \
            passedDroppedIncidentsBuffer.member.filteredCounter                          \
                = m_eventsStorageEnqueueFailCounters[priority]->GetAndResetCounter();    \
            passedDroppedIncidentsBuffer.member.passedCounter                            \
                = m_eventsStorageEnqueueSuccessCounters[priority]->GetAndResetCounter(); \
        }                                                                                \
    } while (false)

    SERIALIZE_ES_QUEUE_COUNTERS(eventsStorageCriticalQueueCounters, EventPriority::Critical);
    SERIALIZE_ES_QUEUE_COUNTERS(eventsStorageImportantQueueCounters, EventPriority::Important);
    SERIALIZE_ES_QUEUE_COUNTERS(eventsStorageNormalQueueCounters, EventPriority::Normal);
    SERIALIZE_ES_QUEUE_COUNTERS(eventsStorageLowQueueCounters, EventPriority::Low);
#undef SERIALIZE_ES_QUEUE_COUNTERS

    return true;
}

bool
PeriodicStatisticsEngine::SerializeEthMonitoringTable(
    com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringTable& ethMonitoringTableBuffer)
{
    if (nullptr == m_ethEngine)
    {
        LOG_ERROR << "[PeriodicReportFlow] PeriodicStatistics Engine - Failed to serialize EthMonitoringTable because "
                     "Eth Engine is nullptr"
                  << LOG_NOOP;
        return false;
    }

    return m_ethEngine->FetchContents(ethMonitoringTableBuffer);
}

bool
PeriodicStatisticsEngine::SerializeHostErrorMonitoringData(
    com_vwg_connect_ids_idsperiodicreport_v1_HostErrorMonitoringCountersData& hostErrorMonitoringCountersBuffer)
{
    bool retVal = false;
    if (nullptr == m_hostEngine)
    {
        LOG_ERROR
            << "PeriodicStatistics Engine - Failed to serialize HostErrorMonitoringData because Host Engine is nullptr"
            << LOG_NOOP;
        return retVal;
    }

    hostErrorMonitoringCountersBuffer.creationTimeStamp = m_currentTime;

    uint64_t const uartAliveSignalMissingCounter = m_hostEngine->GetUartAliveSignalMissingCounter();
    if (0U != uartAliveSignalMissingCounter)
    {
        hostErrorMonitoringCountersBuffer.has_uartAliveSignalMissingCounter = true;
        hostErrorMonitoringCountersBuffer.uartAliveSignalMissingCounter.firstSeenTimeStamp
            = m_hostEngine->GetUartAliveSignalMissingFirstSeenTimestamp();
        hostErrorMonitoringCountersBuffer.uartAliveSignalMissingCounter.lastSeenTimeStamp
            = m_hostEngine->GetUartAliveSignalMissingLastSeenTimestamp();
        hostErrorMonitoringCountersBuffer.uartAliveSignalMissingCounter.counter = uartAliveSignalMissingCounter;
        retVal                                                                  = true;
    }
    else
    {
        hostErrorMonitoringCountersBuffer.has_uartAliveSignalMissingCounter = false;
    }

    uint64_t const authenticationErrorCounter = m_hostEngine->GetAuthenticationErrorCounter();
    if (0U != authenticationErrorCounter)
    {
        hostErrorMonitoringCountersBuffer.has_authenticationErrorCounter = true;
        hostErrorMonitoringCountersBuffer.authenticationErrorCounter.firstSeenTimeStamp
            = m_hostEngine->GetAuthenticationErrorFirstSeenTimestamp();
        hostErrorMonitoringCountersBuffer.authenticationErrorCounter.lastSeenTimeStamp
            = m_hostEngine->GetAuthenticationErrorLastSeenTimestamp();
        hostErrorMonitoringCountersBuffer.authenticationErrorCounter.counter = authenticationErrorCounter;
        retVal                                                               = true;
    }
    else
    {
        hostErrorMonitoringCountersBuffer.has_authenticationErrorCounter = false;
    }

    if (retVal)
    {
        m_hostEngine->ClearContents();
    }
    return retVal;
}

void
PeriodicStatisticsEngine::createIdsStatisticsPeriodicReport(
    com_vwg_connect_ids_idsperiodicreport_v1_IdsStatisticsPeriodicReport& statisticsPeriodicReport)
{
    com_vwg_connect_ids_idsperiodicreport_v1_PassedDroppedIncidentsData passedDroppedIncidentsBuffer
        = com_vwg_connect_ids_idsperiodicreport_v1_PassedDroppedIncidentsData_init_default;
    com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringTable ethMonitoringTableBuffer
        = com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringTable_init_default;
    com_vwg_connect_ids_idsperiodicreport_v1_HostErrorMonitoringCountersData hostErrorMonitoringCountersBuffer
        = com_vwg_connect_ids_idsperiodicreport_v1_HostErrorMonitoringCountersData_init_default;
    com_vwg_connect_ids_idsperiodicreport_v1_DhmIncidentsCountersTable dhmIncidentCounterTable;
    com_vwg_connect_ids_idsperiodicreport_v1_ExceededMaxMessageSizeToIepDropEntryList exceededMaxMessageSizeEntry
        = com_vwg_connect_ids_idsperiodicreport_v1_ExceededMaxMessageSizeToIepDropEntryList_init_default;

    statisticsPeriodicReport.periodStartTime = m_monitoringPeriodStartTimestampMs;
    uint64_t monitoringPeriodEndTimestampMs  = common::Time::GetCurrentTimeMilliSec();
    statisticsPeriodicReport.periodEndTime   = monitoringPeriodEndTimestampMs;

    if (SerializePassedDroppedIncidentsData(passedDroppedIncidentsBuffer))
    {
        SET_NPB_OPTIONAL_FIELD(statisticsPeriodicReport, passedDroppedIncidentsData, passedDroppedIncidentsBuffer);
        common::counters::IncreaseCounter(m_passedDroppedMonitoringDataExistCounter);
    }
    else
    {
        statisticsPeriodicReport.has_passedDroppedIncidentsData = false;
    }

    if (SerializeEthMonitoringTable(ethMonitoringTableBuffer))
    {
        SET_NPB_OPTIONAL_FIELD(statisticsPeriodicReport, ethMonitoringTable, ethMonitoringTableBuffer);
        common::counters::IncreaseCounter(m_ethMonitoringTableExistCounter);
    }
    else
    {
        statisticsPeriodicReport.has_ethMonitoringTable = false;
    }

    // Diag Adaptations - 0x7704 - HostErrorMonitoringOn
    if (m_hostErrorMonitoringOn && SerializeHostErrorMonitoringData(hostErrorMonitoringCountersBuffer))
    {
        SET_NPB_OPTIONAL_FIELD(
            statisticsPeriodicReport, hostErrorMonitoringCountersData, hostErrorMonitoringCountersBuffer);
        common::counters::IncreaseCounter(m_hostErrorMonitoringDataExistCounter);
    }
    else
    {
        statisticsPeriodicReport.has_hostErrorMonitoringCountersData = false;
    }

    if (nullptr == m_processPerformanceEngine
        || m_processPerformanceEngine->CreateSecurityEventsMonitoringData(
            m_securityEventsStorage, m_monitoringPeriodStartTimestampMs, monitoringPeriodEndTimestampMs))
    {
        statisticsPeriodicReport.has_securityEventsMonitoringData = false;
    }
    else
    {
        SET_NPB_OPTIONAL_FIELD(statisticsPeriodicReport, securityEventsMonitoringData, m_securityEventsStorage);
        common::counters::IncreaseCounter(m_processPerformanceDataExistsCounter);
    }

    // SecurityEvents measurement interval condition 2 (requirement 1.3 ConMod)
    if ((nullptr == m_securityEventsEngine)
        || !m_securityEventsEngine->CreateSecurityEventsMonitoringData(
            m_securityEventsStorage, m_monitoringPeriodStartTimestampMs, monitoringPeriodEndTimestampMs))
    {
        statisticsPeriodicReport.has_securityEventsMonitoringData = false;
    }
    else
    {
        SET_NPB_OPTIONAL_FIELD(statisticsPeriodicReport, securityEventsMonitoringData, m_securityEventsStorage);
        common::counters::IncreaseCounter(m_secEveMonitorDataExistCounter);
    }

    if (!brain::engines::CriticalAlertFilter::GetInstance().Serialize(m_passedDroppedAlertData, m_currentTime))
    {
        statisticsPeriodicReport.has_passedDroppedAlertsData = false;
    }
    else
    {
        statisticsPeriodicReport.has_passedDroppedAlertsData = true;
        statisticsPeriodicReport.passedDroppedAlertsData     = m_passedDroppedAlertData;
    }

    if (!m_dhmIncidentTable || !m_dhmIncidentTable->Serialize(dhmIncidentCounterTable))
    {
        statisticsPeriodicReport.has_dhmIncidentsCountersTable = false;
    }
    else
    {
        SET_NPB_OPTIONAL_FIELD(statisticsPeriodicReport, dhmIncidentsCountersTable, dhmIncidentCounterTable);
        common::counters::IncreaseCounter(m_dhmIncidentCounterCounter);
    }

    if (m_exceededMessageSizeCheck && m_exceededMessageSizeCheck->Serialize(exceededMaxMessageSizeEntry))
    {
        SET_NPB_OPTIONAL_FIELD(statisticsPeriodicReport, exceededMaxMessageSizeDropEntry, exceededMaxMessageSizeEntry);
        common::counters::IncreaseCounter(m_exceededMessageSizeCounter);
    }
    else
    {
        statisticsPeriodicReport.has_exceededMaxMessageSizeDropEntry = false;
    }
    LOG_INFO << "[PeriodicReportFlow] Ending monitoring period, timestamp: " << monitoringPeriodEndTimestampMs
             << LOG_NOOP;
    //get ready for a next PR
    m_monitoringPeriodStartTimestampMs = common::Time::GetCurrentTimeMilliSec();
    LOG_INFO << "[PeriodicReportFlow] Starting new monitoring period " << m_monitoringPeriodStartTimestampMs
             << LOG_NOOP;
}

bool
PeriodicStatisticsEngine::createRuleEvaluation(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval)
{
    com_vwg_connect_ids_idsperiodicreport_v1_IdsStatisticsPeriodicReport statisticsPeriodicReport
        = com_vwg_connect_ids_idsperiodicreport_v1_IdsStatisticsPeriodicReport_init_default;
    createIdsStatisticsPeriodicReport(statisticsPeriodicReport);

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    ruleEval.which_RuleData   = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_idsStatisticsPeriodicReport_tag);
    ruleEval.RuleData.idsStatisticsPeriodicReport = statisticsPeriodicReport;

#if defined(DEBUG_COUNTER) || !defined(HCP5_PLATFORM)
    printEvent(ruleEval);
#endif  //(DEBUG_COUNTER) || !(HCP5_PLATFORM)
    // printEventToLog(ruleEval);

    return true;
}

void
PeriodicStatisticsEngine::clearEngines()
{
    if (nullptr != m_ethEngine)
    {
        m_ethEngine->ClearContents();
    }

    m_securityEventsStorage.Clear();  // clear securityEvents periodic data

    brain::engines::CriticalAlertFilter::GetInstance().ResetCounters();
    m_passedDroppedAlertData.Clear();
    
    if (m_dhmIncidentTable)
    {
        m_dhmIncidentTable->clear();
    }

    if (m_exceededMessageSizeCheck)
    {
        m_exceededMessageSizeCheck->clear();
    }
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

        const auto status = SendEvent(ruleEval, SensorDataTag::SD_PERIODIC_STATISTICS, CriticalEventAlert::PeriodicStatistics);

        if (EngineEventSender::SendStatus::Success != status)
        {
            common::counters::IncreaseCounter(m_failedCounter);
        }

        LOG_INFO << "[PeriodicReportFlow] Periodic report sent " << static_cast<uint8_t>(status) << LOG_NOOP;

        clearEngines();

        common::counters::IncreaseCounter(m_measurementIntervalEndedCounter);
        common::counters::IncreaseCounter(m_measurementIntervalStartedCounter);
        return ReturnCode::Success;
    }
    catch (std::bad_cast const& /*e*/)
    {
        LOG_ERROR << "[PeriodicReportFlow] SD cannot be cast to PeriodicStatisticsSensorData!" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCounter);
        return ReturnCode::CastError;
    }
}

#if defined(DEBUG_COUNTER) || !defined(HCP5_PLATFORM)
void
PeriodicStatisticsEngine::printEvent(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval)
{
    auto& eventLogger = Logger::GetInstance();
#ifdef TESTS
    eventLogger.InitRuleEvaluationFile();
#endif  // TESTS

    eventLogger.LogDebugAndToFile<std::string>(
        "PeriodicStatistics Engine - Event printed: Creating periodic statistics event", 0, Logger::valueType::NO_TYPE);
    eventLogger.LogDebugAndToFile<uint64_t>("PeriodicStatistics Engine - Event printed: ruleEvaluationId",
                                            ruleEval.ruleEvaluationId,
                                            Logger::valueType::UINT_TYPE);
    eventLogger.LogDebugAndToFile<uint64_t>(
        "PeriodicStatistics Engine - Event printed: timestamp", ruleEval.timestamp, Logger::valueType::UINT_TYPE);
    eventLogger.LogDebugAndToFile<pb_size_t>("PeriodicStatistics Engine - Event printed: which_RuleData",
                                             ruleEval.which_RuleData,
                                             Logger::valueType::UINT_TYPE);

    com_vwg_connect_ids_idsperiodicreport_v1_IdsStatisticsPeriodicReport statisticsPeriodicReport
        = ruleEval.RuleData.idsStatisticsPeriodicReport;

    if (statisticsPeriodicReport.has_passedDroppedIncidentsData)
    {
        eventLogger.LogDebugAndToFile<uint64_t>(
            "PeriodicStatistics Engine - Event printed: passedDroppedIncidentsData.creationTimeStamp",
            statisticsPeriodicReport.passedDroppedIncidentsData.creationTimeStamp,
            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<uint64_t>(
            "PeriodicStatistics Engine - Event printed: "
            "passedDroppedIncidentsData.sensorNFCounters.filteredIncidentsCounter",
            statisticsPeriodicReport.passedDroppedIncidentsData.sensorNFCounters.filteredCounter,
            Logger::valueType::UINT_TYPE);
    }

    if (statisticsPeriodicReport.has_hostErrorMonitoringCountersData)
    {
        eventLogger.LogDebugAndToFile<uint64_t>(
            "PeriodicStatistics Engine - Event printed: hostErrorMonitoringCountersData.creationTimeStamp",
            statisticsPeriodicReport.hostErrorMonitoringCountersData.creationTimeStamp,
            Logger::valueType::UINT_TYPE);

        if (statisticsPeriodicReport.hostErrorMonitoringCountersData.has_uartAliveSignalMissingCounter)
        {
            eventLogger.LogDebugAndToFile<uint64_t>(
                "PeriodicStatistics Engine - Event printed: "
                "hostErrorMonitoringCountersData.uartAliveSignalMissingCounter.firstSeenTimestamp",
                statisticsPeriodicReport.hostErrorMonitoringCountersData.uartAliveSignalMissingCounter
                    .firstSeenTimeStamp,
                Logger::valueType::UINT_TYPE);
            eventLogger.LogDebugAndToFile<uint64_t>(
                "PeriodicStatistics Engine - Event printed: "
                "hostErrorMonitoringCountersData.uartAliveSignalMissingCounter.lastSeenTimeStamp",
                statisticsPeriodicReport.hostErrorMonitoringCountersData.uartAliveSignalMissingCounter
                    .lastSeenTimeStamp,
                Logger::valueType::UINT_TYPE);
            eventLogger.LogDebugAndToFile<uint64_t>(
                "PeriodicStatistics Engine - Event printed: "
                "hostErrorMonitoringCountersData.uartAliveSignalMissingCounter.Counter",
                statisticsPeriodicReport.hostErrorMonitoringCountersData.uartAliveSignalMissingCounter.counter,
                Logger::valueType::UINT_TYPE);
        }
        if (statisticsPeriodicReport.hostErrorMonitoringCountersData.has_authenticationErrorCounter)
        {
            eventLogger.LogDebugAndToFile<uint64_t>(
                "PeriodicStatistics Engine - Event printed: "
                "hostErrorMonitoringCountersData.authenticationErrorCounter.firstSeenTimestamp",
                statisticsPeriodicReport.hostErrorMonitoringCountersData.authenticationErrorCounter.firstSeenTimeStamp,
                Logger::valueType::UINT_TYPE);
            eventLogger.LogDebugAndToFile<uint64_t>(
                "PeriodicStatistics Engine - Event printed: "
                "hostErrorMonitoringCountersData.authenticationErrorCounter.lastSeenTimeStamp",
                statisticsPeriodicReport.hostErrorMonitoringCountersData.authenticationErrorCounter.lastSeenTimeStamp,
                Logger::valueType::UINT_TYPE);
            eventLogger.LogDebugAndToFile<uint64_t>(
                "PeriodicStatistics Engine - Event printed: "
                "hostErrorMonitoringCountersData.authenticationErrorCounter.Counter",
                statisticsPeriodicReport.hostErrorMonitoringCountersData.authenticationErrorCounter.counter,
                Logger::valueType::UINT_TYPE);
        }
    }

#ifdef TESTS
    eventLogger.LogDebugAndToFile<std::string>("", "", Logger::valueType::CLOSE);
#endif  // TESTS
}
#endif  // defined(DEBUG_COUNTER) || !defined(HCP5_PLATFORM)

void
PeriodicStatisticsEngine::printEventToLog(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval)
{
    LOG_INFO << "PeriodicStatistics Engine - Event printed: Creating periodic statistics event" << LOG_NOOP;
    LOG_INFO << "PeriodicStatistics Engine - Event printed: ruleEvaluationId " << ruleEval.ruleEvaluationId << LOG_NOOP;
    LOG_INFO << "PeriodicStatistics Engine - Event printed: timestamp " << ruleEval.timestamp << LOG_NOOP;
    LOG_INFO << "PeriodicStatistics Engine - Event printed: which_RuleData " << ruleEval.which_RuleData << LOG_NOOP;

    com_vwg_connect_ids_idsperiodicreport_v1_IdsStatisticsPeriodicReport statisticsPeriodicReport
        = ruleEval.RuleData.idsStatisticsPeriodicReport;

    if (statisticsPeriodicReport.has_passedDroppedIncidentsData)
    {
        LOG_INFO << "PeriodicStatistics Engine - Event printed: passedDroppedIncidentsData.creationTimeStamp "
                 << statisticsPeriodicReport.passedDroppedIncidentsData.creationTimeStamp << LOG_NOOP;
        LOG_INFO << "PeriodicStatistics Engine - Event printed: "
                    "passedDroppedIncidentsData.sensorNFCounters.filteredIncidentsCounter "
                 << statisticsPeriodicReport.passedDroppedIncidentsData.sensorNFCounters.filteredCounter << LOG_NOOP;
    }

    if (statisticsPeriodicReport.has_hostErrorMonitoringCountersData)
    {
        LOG_INFO << "PeriodicStatistics Engine - Event printed: hostErrorMonitoringCountersData.creationTimeStamp "
                 << statisticsPeriodicReport.hostErrorMonitoringCountersData.creationTimeStamp << LOG_NOOP;

        if (statisticsPeriodicReport.hostErrorMonitoringCountersData.has_uartAliveSignalMissingCounter)
        {
            LOG_INFO << "PeriodicStatistics Engine - Event printed: "
                        "hostErrorMonitoringCountersData.uartAliveSignalMissingCounter.firstSeenTimestamp "
                     << statisticsPeriodicReport.hostErrorMonitoringCountersData.uartAliveSignalMissingCounter
                            .firstSeenTimeStamp
                     << LOG_NOOP;
            LOG_INFO << "PeriodicStatistics Engine - Event printed: "
                        "hostErrorMonitoringCountersData.uartAliveSignalMissingCounter.lastSeenTimeStamp "
                     << statisticsPeriodicReport.hostErrorMonitoringCountersData.uartAliveSignalMissingCounter
                            .lastSeenTimeStamp
                     << LOG_NOOP;
            LOG_INFO << "PeriodicStatistics Engine - Event printed: "
                        "hostErrorMonitoringCountersData.uartAliveSignalMissingCounter.Counter "
                     << statisticsPeriodicReport.hostErrorMonitoringCountersData.uartAliveSignalMissingCounter.counter
                     << LOG_NOOP;
        }
        if (statisticsPeriodicReport.hostErrorMonitoringCountersData.has_authenticationErrorCounter)
        {
            LOG_INFO << "PeriodicStatistics Engine - Event printed: "
                        "hostErrorMonitoringCountersData.authenticationErrorCounter.firstSeenTimestamp "
                     << statisticsPeriodicReport.hostErrorMonitoringCountersData.authenticationErrorCounter
                            .firstSeenTimeStamp
                     << LOG_NOOP;
            LOG_INFO
                << "PeriodicStatistics Engine - Event printed: "
                   "hostErrorMonitoringCountersData.authenticationErrorCounter.lastSeenTimeStamp "
                << statisticsPeriodicReport.hostErrorMonitoringCountersData.authenticationErrorCounter.lastSeenTimeStamp
                << LOG_NOOP;
            LOG_INFO << "PeriodicStatistics Engine - Event printed: "
                        "hostErrorMonitoringCountersData.authenticationErrorCounter.Counter "
                     << statisticsPeriodicReport.hostErrorMonitoringCountersData.authenticationErrorCounter.counter
                     << LOG_NOOP;
        }
    }
}