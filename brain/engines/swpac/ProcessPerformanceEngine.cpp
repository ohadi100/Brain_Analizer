/**
 * @file
 * @brief     A rule engine for the Process Performance sensor data
 */
#include "ProcessPerformanceEngine.hpp"
#include "IncidentCounterTable.hpp"
#include "brain/config/AlertEventsNames.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "IncidentCounterTable.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"
#include "brain/config/BrainConfigConstants.hpp"
using namespace brain::engines::swpac;
using brain::engines::ReturnCode;
using brain::sender_events::CriticalEventAlert;
namespace brain
{
namespace engines
{
namespace swpac
{
using Message = brain::messageRepository::MessageRepositoryInterface::Message;
static constexpr size_t   dhmProcessPerformanceTableLimit{1800U};
}  // namespace swpac
}  // namespace engines
}  // namespace brain
static brain::histogram::ScalarHistogram::BinIntervalsVector&&
initProcessPerformanceEngineMemoryUsageBins() noexcept
{
    static brain::histogram::ScalarHistogram::BinIntervalsVector newVector{
        10U, 20U, 30U, 40U, 50U, 60U, 70U, 80U, 90U, 100U};
    return std::move(newVector);
}
brain::histogram::ScalarHistogram::BinIntervalsVector const
    brain::engines::swpac::ProcessPerformanceEngine::m_memoryUsageBins
    = initProcessPerformanceEngineMemoryUsageBins();

static brain::histogram::ScalarHistogram::BinIntervalsVector&&
initProcessPerformanceEngineCpuUsageBins() noexcept
{
    static brain::histogram::ScalarHistogram::BinIntervalsVector newVector{
        10U, 20U, 30U, 40U, 50U, 60U, 70U, 80U, 90U, 100U};
    return std::move(newVector);
}
brain::histogram::ScalarHistogram::BinIntervalsVector const
    brain::engines::swpac::ProcessPerformanceEngine::m_cpuUsageBins
    = initProcessPerformanceEngineCpuUsageBins();

constexpr uint8_t SensorInstanceId{0x040};

ProcessPerformanceEngine::ProcessPerformanceEngine(CounterManagerPtr                                 debugCounters,
                                                   MessageRepositoryPtr                              msgRepository,
                                                   ConfigurationPtr                                  config,
                                                   EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                                                   EventNoiseFilterPtr                               eventNoiseFilter,
                                                   events::EventPriority                             priority)
  : SwpacEngineBase(debugCounters, priority, msgRepository, reportSerializer, eventNoiseFilter)
  , m_processPerformanceTable{dhmProcessPerformanceTableLimit}
{
    if (config)
    {
        std::ignore = config->GetValue(brain::config_keys::MEMORY_USAGE_ALERT_THRESHOLD_PER_PROCESS,
                                       m_memoryUsageAlertThresholdPerProcess);
        std::ignore = config->GetValue(brain::config_keys::CPU_USAGE_ALERT_THRESHOLD_PER_PROCESS,
                                       m_cpuUsageAlertThresholdPerProcess);
    }

    if (debugCounters)
    {
        m_failedCounter
            = debugCounters->CreateCounter(common::counters::PROCESS_PERFORMANCE_FAILED_PROCESS_COUNTER_NAME,
                                           EventCounter::EventCounterLevelType::COUNTER_WARNING);
        m_excessiveProcessMemoryAlertCounter = debugCounters->CreateCounter(
            common::counters::PROCESS_PERFORMANCE_EXCESSIVE_PROCESS_MEMORY_ALERT_COUNTER_NAME,
            EventCounter::EventCounterLevelType::COUNTER_DEBUG);
        m_excessiveProcessCpuAlertCounter = debugCounters->CreateCounter(
            common::counters::PROCESS_PERFORMANCE_EXCESSIVE_PROCESS_CPU_ALERT_COUNTER_NAME,
            EventCounter::EventCounterLevelType::COUNTER_DEBUG);
    }
}

bool
ProcessPerformanceEngine::CreateSecurityEventsMonitoringData(
    SecurityEventsPeriodicMonitoringData& securityEventsMonitoring,
    uint64_t                              startPeriodicReportTimestamp,
    uint64_t                              endPeriodicReportTimestamp)
{
    if (m_processPerformanceTable.empty())
    {
        LOG_DEBUG << "Process Performance table is empty" << LOG_NOOP;
        return false;
    }

    if (securityEventsMonitoring.Entries.empty())
    {
        securityEventsMonitoring.Entries.emplace_back();
    }
    auto& newSecurityEventMonitoringData = securityEventsMonitoring.Entries.back();

    newSecurityEventMonitoringData.periodStartTime = startPeriodicReportTimestamp;
    newSecurityEventMonitoringData.periodEndTime   = endPeriodicReportTimestamp;

    for (auto const& entry : m_processPerformanceTable)
    {
        newSecurityEventMonitoringData.ProcessPerformance.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.ProcessPerformance.Entries.back();

        newEntry.ProcessName = entry.first;

        newEntry.which_partition = com_vwg_connect_ids_idsperiodicreport_v1_ProcessPerformanceEntry_idsMInstanceID_tag;
        newEntry.partition.idsMInstanceID = SensorInstanceId;

        brain::histogram::ScalarHistogram::BinDataVector histogramData;
        uint64_t                                         firstHistogramTs{};
        uint64_t                                         lastHistogramTs{};

        newEntry.has_priviledgedModeCpuUsageHistogram = false;

        histogramData.clear();
        auto hasValue = std::get<0>(entry.second).GetHistogramValues(histogramData, firstHistogramTs, lastHistogramTs);
        if (!hasValue)
        {
            return false;
        }
        newEntry.has_nonPriviledgedModeCpuUsageHistogram                = true;
        newEntry.nonPriviledgedModeCpuUsageHistogram.firstSeenTimeStamp = firstHistogramTs;
        newEntry.nonPriviledgedModeCpuUsageHistogram.lastSeenTimeStamp  = lastHistogramTs;
        for (auto const& record : histogramData)
        {
            newEntry.NonPriviledgedModeCpuUsageBuckets.emplace_back(com_vwg_connect_ids_idsperiodicreport_v1_Bucket{
                static_cast<uint32_t>(record.GetHeight()), static_cast<uint32_t>(record.GetInterval())});
        }

        histogramData.clear();
        hasValue = std::get<1>(entry.second).GetHistogramValues(histogramData, firstHistogramTs, lastHistogramTs);
        if (!hasValue)
        {
            return false;
        }
        newEntry.has_memoryUsageHistogram                = true;
        newEntry.memoryUsageHistogram.firstSeenTimeStamp = firstHistogramTs;
        newEntry.memoryUsageHistogram.lastSeenTimeStamp  = lastHistogramTs;
        for (auto const& record : histogramData)
        {
            newEntry.MemoryUsageBuckets.emplace_back(com_vwg_connect_ids_idsperiodicreport_v1_Bucket{
                static_cast<uint32_t>(record.GetHeight()), static_cast<uint32_t>(record.GetInterval())});
        }
    }

    resetTable();

    return true;
}

void
ProcessPerformanceEngine::resetTable()
{
    m_processPerformanceTable.clear();
    m_processPerformanceTable.ResetFailedAllocations();
}

bool
ProcessPerformanceEngine::addEventAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval,
                                        brain::sender_events::CriticalEventAlert                       event)
{
    auto const status
        = SendEvent(ruleEval, common::sensor_data::SensorDataTag::SD_SWPAC_PROCESS_PERFORMANCE_REPORT, event);

    if (EngineEventSender::SendStatus::Success != status)
    {
        common::counters::IncreaseCounter(m_failedCounter);
    }

    return EngineEventSender::SendStatus::Success == status;
}

bool
ProcessPerformanceEngine::createExcessiveProcessMemoryUsageAlert(brain::histogram::ScalarHistogram const& hist,
                                                                 ProcessPerformanceSensorData const&      sd)
{
    brain::histogram::ScalarHistogram::BinDataVector binDataVector;
    uint64_t                                         firstHistogramTs{};
    uint64_t                                         lastHistogramTs{};
    if (!hist.GetHistogramValues(binDataVector, firstHistogramTs, lastHistogramTs))
    {
        LOG_ERROR << "Cannot get process memory usage histogram values" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCounter);
        return false;
    }

    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
    com_vwg_connect_ids_idsperiodicreport_v1_ExcessiveProcessMemoryCpuUsageAlert memUsage
        = com_vwg_connect_ids_idsperiodicreport_v1_ExcessiveProcessMemoryCpuUsageAlert_init_default;

    memUsage.processName = common::nanopb::CreateEncodingCallback(sd.GetProcessName());

    memUsage.which_partition = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_ExcessiveProcessMemoryCpuUsageAlert_idsMInstanceID_tag);
    memUsage.partition.idsMInstanceID = SensorInstanceId;
    

    memUsage.has_memoryUserCpuUsageHistogram                  = true;
    memUsage.memoryUserCpuUsageHistogram.firstSeenTimeStamp   = firstHistogramTs;
    memUsage.memoryUserCpuUsageHistogram.lastSeenTimeStamp    = lastHistogramTs;
    memUsage.memoryUserCpuUsageHistogram.buckets.funcs.encode = &common::nanopb::encoders::EncodeScalarHistogram;
    memUsage.memoryUserCpuUsageHistogram.buckets.arg          = &binDataVector;

    memUsage.cpuUsageTotal  = sd.GetCpu();
    memUsage.memoryUsage    = sd.GetRam();
    memUsage.alertThreshold = m_memoryUsageAlertThresholdPerProcess;

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    
    ruleEval.which_RuleData
        = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_processMemoryUsageAlert_tag);
    ruleEval.RuleData.processMemoryUsageAlert = memUsage;

    auto const ok = addEventAlert(ruleEval, CriticalEventAlert::ExcessiveProcessMemoryUsage);
    if (ok)
    {
        common::counters::IncreaseCounter(m_excessiveProcessMemoryAlertCounter);
        LOG_DEBUG << "Excessive process memory usage alert updated: "
                  << "processName=" << sd.GetProcessName() << ",idsMInstanceId =" << SensorInstanceId
                  << ",idsMInstanceID=" << sd.GetPid() << LOG_NOOP;
    }
    return ok;
}
bool
ProcessPerformanceEngine::createExcessiveProcessCpuUsageAlert(brain::histogram::ScalarHistogram const& total,
                                                              ProcessPerformanceSensorData const&      sd)
{
    brain::histogram::ScalarHistogram::BinDataVector totalVector;
    uint64_t                                         firstHistogramTs{};
    uint64_t                                         lastHistogramTs{};
    if (!total.GetHistogramValues(totalVector, firstHistogramTs, lastHistogramTs))
    {
        LOG_ERROR << "Cannot get process priv CPU usage histogram values" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCounter);
        return false;
    }

    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
    com_vwg_connect_ids_idsperiodicreport_v1_ExcessiveProcessMemoryCpuUsageAlert cpuUsage
        = com_vwg_connect_ids_idsperiodicreport_v1_ExcessiveProcessMemoryCpuUsageAlert_init_default;

    cpuUsage.processName = common::nanopb::CreateEncodingCallback(sd.GetProcessName());

    cpuUsage.which_partition = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_ExcessiveProcessMemoryCpuUsageAlert_idsMInstanceID_tag);
    cpuUsage.partition.idsMInstanceID = SensorInstanceId;

    cpuUsage.has_memoryUserCpuUsageHistogram                  = true;
    cpuUsage.memoryUserCpuUsageHistogram.firstSeenTimeStamp   = firstHistogramTs;
    cpuUsage.memoryUserCpuUsageHistogram.lastSeenTimeStamp    = lastHistogramTs;
    cpuUsage.memoryUserCpuUsageHistogram.buckets.funcs.encode = &common::nanopb::encoders::EncodeScalarHistogram;
    cpuUsage.memoryUserCpuUsageHistogram.buckets.arg          = &totalVector;

    cpuUsage.cpuUsageTotal  = sd.GetCpu();
    cpuUsage.memoryUsage    = sd.GetRam();
    cpuUsage.alertThreshold = m_cpuUsageAlertThresholdPerProcess;

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    
    ruleEval.which_RuleData
        = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_processCpuUsageAlert_tag);
    ruleEval.RuleData.processCpuUsageAlert = cpuUsage;

    auto const ok = addEventAlert(ruleEval, CriticalEventAlert::ExcessiveProcessCpuUsage);

    if (ok)
    {
        common::counters::IncreaseCounter(m_excessiveProcessCpuAlertCounter);
        LOG_DEBUG << "Excessive process CPU usage alert updated: "
                  << "processName=" << sd.GetProcessName() << ",idsMInstanceId=" << SensorInstanceId
                  << ",idsMInstanceID=" << sd.GetPid() << LOG_NOOP;
    }

    return ok;
}

ReturnCode
ProcessPerformanceEngine::processInternal(UPSensorData const sd)
{
    try
    {
        LOG_VERBOSE << "Began processing ProcessPerformanceSensorData" << LOG_NOOP;
        auto const& processPerformanceSD = dynamic_cast<ProcessPerformanceSensorData const&>(*sd);

        auto const insertion = m_processPerformanceTable.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(processPerformanceSD.GetProcessName()),
            std::forward_as_tuple(std::make_tuple(brain::histogram::ScalarHistogram{m_cpuUsageBins},
                                                  brain::histogram::ScalarHistogram{m_memoryUsageBins})));

        if (common::types::IsMapSizeExceeded(m_processPerformanceTable, insertion))
        {
            common::counters::IncreaseCounter(m_failedCounter);
            return ReturnCode::MaxTableSizeError;
        }

        LOG_VERBOSE << "processing " << processPerformanceSD.GetProcessName() << " pid "
                    << processPerformanceSD.GetPid() << " ram " << processPerformanceSD.GetRam() << " cpu "
                    << processPerformanceSD.GetCpu() << LOG_NOOP;

        auto& valueTuple = insertion.first->second;

        auto& nonPrivCpuUsageHistogram = std::get<0>(valueTuple);
        auto& memUsageHistogram        = std::get<1>(valueTuple);

        double interval{};
        static constexpr uint64_t EVENT_WEIGHT{1U};
        auto   timeStamp = processPerformanceSD.GetCreatedTimestamp();
        std::ignore      = nonPrivCpuUsageHistogram.Update(
            timeStamp, static_cast<uint16_t>(processPerformanceSD.GetCpu()), EVENT_WEIGHT, interval);
        std::ignore = memUsageHistogram.Update(
            timeStamp, static_cast<uint16_t>(processPerformanceSD.GetRam()), EVENT_WEIGHT, interval);

        bool memoryAlertStatus{true};
        bool cpuAlertStatus{true};

        if (processPerformanceSD.GetRam() > m_memoryUsageAlertThresholdPerProcess)
        {
            memoryAlertStatus = createExcessiveProcessMemoryUsageAlert(memUsageHistogram, processPerformanceSD);
        }

        if (processPerformanceSD.GetCpu() > m_cpuUsageAlertThresholdPerProcess)
        {
            cpuAlertStatus = createExcessiveProcessCpuUsageAlert(nonPrivCpuUsageHistogram, processPerformanceSD);
        }

        // send string size alert only if the SD is valid
        if (processPerformanceSD.IsAlert())
        {
            LOG_DEBUG << "ProcessPerformance Engine - string size alert" << LOG_NOOP;
            sendStringSizeAlert(processPerformanceSD.GetTag(),
                                processPerformanceSD.GetConstraintId(),
                                processPerformanceSD.GetStringSizeAlertData());
        }

        if (m_incidentCounter)
        {
            m_incidentCounter->Increment(brain::sensor_data::swpac::ConstraintId::PROCESS_PERFORMANCE);
        }

        return ((memoryAlertStatus && cpuAlertStatus) ? ReturnCode::Success : ReturnCode::FailedError);
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::bad_cast const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "SD cannot be casted to ProcessPerformanceSensorData" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCounter);
        return ReturnCode::CastError;
    }
}