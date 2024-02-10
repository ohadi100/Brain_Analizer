#include "ResourceConsumptionNotificationEngine.hpp"
#include "brain/config/AlertEventsNames.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"
#include "brain/utils/nanopb/Encoders.hpp"

using brain::engines::ReturnCode;
using brain::engines::security_events::ResourceConsumptionEntry;
using brain::engines::security_events::ResourceConsumptionHistoryData;
using brain::engines::security_events::ResourceConsumptionNotificationEngine;

static brain::histogram::ScalarHistogram::BinIntervalsVector&&
initResourceConsumptionNotificationEngineMemoryUsageBins() noexcept
{
    static brain::histogram::ScalarHistogram::BinIntervalsVector newVector{10, 20, 30, 40, 50, 60, 70, 80, 90};
    return std::move(newVector);
}
// Memory Usage Histogram - bins (MB)
brain::histogram::ScalarHistogram::BinIntervalsVector const ResourceConsumptionNotificationEngine::m_memoryUsageBins
    = initResourceConsumptionNotificationEngineMemoryUsageBins();


static brain::histogram::ScalarHistogram::BinIntervalsVector&&
initResourceConsumptionNotificationEngineCpuUsageBins() noexcept
{
    static brain::histogram::ScalarHistogram::BinIntervalsVector newVector{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    return std::move(newVector);
}
// CPU Usage Histogram - bins (%)
brain::histogram::ScalarHistogram::BinIntervalsVector const ResourceConsumptionNotificationEngine::m_cpuUsageBins
    = initResourceConsumptionNotificationEngineCpuUsageBins();

namespace brain
{
namespace engines
{
namespace security_events
{
static constexpr size_t processPerformanceDataMapLimit{1600U};
static constexpr size_t processPerformanceTableLimit{1600U};
}  // namespace security_events
}  // namespace engines
}  // namespace brain

ResourceConsumptionNotificationEngine::ResourceConsumptionNotificationEngine(
    CounterManagerPtr                                 debugCounters,
    ConfigurationPtr                                  config,
    MessageRepositoryPtr                              msgRepository,
    EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
    EventNoiseFilterPtr                               eventNoiseFilter,
    events::EventPriority                             priority)
  : SecurityEventEngineCreateEvent(debugCounters, priority, msgRepository, reportSerializer, eventNoiseFilter)
  , m_processPerformanceTable{processPerformanceTableLimit}
  , m_processPerformanceData{processPerformanceDataMapLimit}
{
    m_resourceConsumptionSources = ResourceConsumptionSources(config);
}

bool
ResourceConsumptionNotificationEngine::FillStatisticData(SecurityEventMonitoringData& securityEventMonitoringData)
{
    for (auto const& entry : m_processPerformanceTable)
    {
        securityEventMonitoringData.ProcessPerformance.Entries.emplace_back();
        auto& newEntry = securityEventMonitoringData.ProcessPerformance.Entries.back();

        newEntry.ProcessName = entry.first.m_processName;
        // Initialize the relevant fields depends if it's data of host or security type
        newEntry.which_sensor = com_vwg_connect_ids_idsperiodicreport_v1_ProcessPerformanceEntry_sensorInstanceID_tag;
        newEntry.sensor.sensorInstanceID = entry.first.GetSensorInstanceId();
        newEntry.which_partition = com_vwg_connect_ids_idsperiodicreport_v1_ProcessPerformanceEntry_idsMInstanceID_tag;
        newEntry.partition.idsMInstanceID = entry.first.GetIdsMInstanceId();

        if (!fillHistogramsData(securityEventMonitoringData, entry))
        {
            LOG_ERROR << "failed to append histograms data from current entry" << LOG_NOOP;
            return false;
        }
    }

    if (securityEventMonitoringData.has_processPerformanceTable)
    {
        LOG_VERBOSE << "PeriodicStatistics has process performance table" << LOG_NOOP;
    }

    return true;
}

void
ResourceConsumptionNotificationEngine::ResetStatisticData()
{
    m_processPerformanceTable.clear();
    m_processPerformanceTable.ResetFailedAllocations();
}

ReturnCode
ResourceConsumptionNotificationEngine::processInternal(UPSensorData sd)
{
    try
    {
        auto&                                          securityEventSD = dynamic_cast<SecurityEventSensorData&>(*sd);
        SECEV_RESOURCE_CONSUMPTION_NOTIFICATION const* event
            = securityEventSD.decodeContextData<SECEV_RESOURCE_CONSUMPTION_NOTIFICATION>();

        if (nullptr == event)
        {
            LOG_ERROR << "received event RESOURCE_CONSUMPTION_NOTIFICATION with invalid length" << LOG_NOOP;
            return ReturnCode::LengthError;
        }

        if (!event->hasFields()
            && (!event->hasProcessNameField() || !event->hasCpuUsageKernelSpaceField()
                || !event->hasCpuUsageUserSpaceField() || !event->hasMemoryUsageField()))
        {
            LOG_ERROR << "Invalid event RESOURCE_CONSUMPTION_NOTIFICATION received" << LOG_NOOP;
            return ReturnCode::InvalidError;
        }

        ResourceConsumptionEntry       key(securityEventSD, event);
        ResourceConsumptionHistoryData prevProcessPerformanceDataEntry{};
        auto cpuUsageKernelSpace = (std::numeric_limits<uint16_t>::max() == event->cpuUsageKernelSpace)
                                       ? 0U
                                       : event->cpuUsageKernelSpace;  // HCP4 sensors send default value in cpuUsage_1
                                                                      // field (0xFFFF), reset cpuUsageKernelSpace.

        auto const cpuUsageUserSpace = event->cpuUsageUserSpace;
        auto const ramMemoryUsage    = event->memoryUsage;
        auto const sdTimeStamp       = securityEventSD.GetTimestamp();

        ResourceConsumptionHistoryData curProcessPerformanceDataEntry{
            static_cast<uint32_t>(sdTimeStamp), cpuUsageKernelSpace, cpuUsageUserSpace, ramMemoryUsage};

        auto const prevProcessPerformanceDataEntryIterator = m_processPerformanceData.find(key);
        if (m_processPerformanceData.end() != prevProcessPerformanceDataEntryIterator)
        {
            LOG_DEBUG << "[handleResourceConsumptionNotificationEvent] found process entry in m_processPerformanceData"
                      << LOG_NOOP;
            prevProcessPerformanceDataEntry = prevProcessPerformanceDataEntryIterator->second;
        }

        std::ignore          = m_processPerformanceData.emplace(key, curProcessPerformanceDataEntry);
        auto const insertion = m_processPerformanceTable.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(key),
            std::forward_as_tuple(std::make_tuple(brain::histogram::ScalarHistogram{m_cpuUsageBins},
                                                  brain::histogram::ScalarHistogram{m_cpuUsageBins},
                                                  brain::histogram::ScalarHistogram{m_memoryUsageBins})));

        if (common::types::IsMapSizeExceeded(m_processPerformanceTable, insertion))
        {
            return ReturnCode::MaxTableSizeError;
        }

        auto& valueTuple               = insertion.first->second;
        auto& privCpuUsageHistogram    = std::get<0>(valueTuple);
        auto& nonPrivCpuUsageHistogram = std::get<1>(valueTuple);
        auto& memUsageHistogram        = std::get<2>(valueTuple);

        m_userCpuConsumptionPercentage   = 0U;
        m_kernelCpuConsumptionPercentage = 0U;
        m_memConsumptionPercentage       = 0U;

        m_resourceConsumptionSources.CalculateResourceConsumptionPercentage(prevProcessPerformanceDataEntry,
                                                                            curProcessPerformanceDataEntry,
                                                                            key,
                                                                            m_userCpuConsumptionPercentage,
                                                                            m_kernelCpuConsumptionPercentage,
                                                                            m_memConsumptionPercentage);

        /* Update Histogram tables*/
        double interval{};
        // in HCP4 and Conmod Only the cpuUsage field is filled with a value for both user and kernel. no need to
        // update kernel cpu usage histogram
        uint64_t privCpuUsageWeight
            = CPU_USAGE_FIELD_FIILED_WITH_TOTAL_CPU(m_resourceConsumptionSources.GetResourceConsumptionSource(key))
                  ? 0U
                  : EventWeight;

        std::ignore
            = privCpuUsageHistogram.Update(sdTimeStamp, m_kernelCpuConsumptionPercentage, privCpuUsageWeight, interval);
        std::ignore
            = nonPrivCpuUsageHistogram.Update(sdTimeStamp, m_userCpuConsumptionPercentage, EventWeight, interval);
        std::ignore = memUsageHistogram.Update(sdTimeStamp, m_memConsumptionPercentage, EventWeight, interval);

        LOG_DEBUG << "Updated ProcessPerformanceTable for Security event: processName=" << key.m_processName
                  << ",sensorId=" << key.GetSensorInstanceId() << ",vimId/idsmId=" << key.GetIdsMInstanceId()
                  << ",memU=" << ramMemoryUsage << ",cpuK=" << cpuUsageKernelSpace << ",cpuU=" << cpuUsageUserSpace
                  << LOG_NOOP;

        /* Handle alerts */
        // Excessive process memory usage alert
        uint32_t memUsageThreshold = m_resourceConsumptionSources.GetMemoryUsageThreshold(key);
        if (m_memConsumptionPercentage > memUsageThreshold)
        {
            if (createExcessiveProcessMemoryUsageAlert(key, memUsageHistogram, securityEventSD))
            {
                LOG_DEBUG << "Set Memory alert for Security event: processName=" << key.m_processName
                          << " ,sensorId=" << key.GetSensorInstanceId() << " ,vimId/idsmId=" << key.GetIdsMInstanceId()
                          << LOG_NOOP;
            }
            else
            {
                return ReturnCode::FailedError;
            }
        }

        // Excessive process cpu usage alert
        uint32_t cpuUsageThreshold = m_resourceConsumptionSources.GetCpuUsageThreshold(key);
        if ((m_kernelCpuConsumptionPercentage + m_userCpuConsumptionPercentage) > cpuUsageThreshold)
        {
            if (createExcessiveProcessCpuUsageAlert(key,
                                                    privCpuUsageHistogram,
                                                    nonPrivCpuUsageHistogram,
                                                    m_userCpuConsumptionPercentage,
                                                    m_kernelCpuConsumptionPercentage,
                                                    cpuUsageThreshold,
                                                    securityEventSD))
            {
                LOG_DEBUG << "Set cpu usage alert for Security event: processName=" << key.m_processName
                          << " ,sensorId=" << key.GetSensorInstanceId() << " ,vimId/idsmId=" << key.GetIdsMInstanceId()
                          << LOG_NOOP;
            }
            else
            {
                return ReturnCode::FailedError;
            }
        }
    }
    catch (std::bad_cast const& /*e*/)
    {
        LOG_ERROR << "Processing SecurityEventsEngine - sd cannot be casted to SecurityEventSensorData" << LOG_NOOP;
        return ReturnCode::CastError;
    }

    return ReturnCode::Success;
}
bool
ResourceConsumptionNotificationEngine::createExcessiveProcessMemoryUsageAlert(
    ResourceConsumptionEntry const&          key,
    brain::histogram::ScalarHistogram const& hist,
    SecurityEventSensorData const&           sd)
{
    LOG_VERBOSE << "Excessive process memory usage alert" << LOG_NOOP;

    brain::histogram::ScalarHistogram::BinDataVector binDataVector;
    uint64_t                                         firstHistogramTs{};
    uint64_t                                         lastHistogramTs{};
    if (!hist.GetHistogramValues(binDataVector, firstHistogramTs, lastHistogramTs))
    {
        LOG_ERROR << "Cannot get process memory usage histogram values" << LOG_NOOP;
        return false;
    }

    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
    com_vwg_connect_ids_idsperiodicreport_v1_ExcessiveProcessMemoryCpuUsageAlert memUsage
        = com_vwg_connect_ids_idsperiodicreport_v1_ExcessiveProcessMemoryCpuUsageAlert_init_default;

    memUsage.processName = common::nanopb::CreateEncodingCallback(key.m_processName);

    // Initialize the relevant fields depends if it's data of host or security type
    memUsage.which_sensor = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_ExcessiveProcessMemoryCpuUsageAlert_sensorInstanceID_tag);
    memUsage.sensor.sensorInstanceID = key.GetSensorInstanceId();
    memUsage.which_partition         = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_ExcessiveProcessMemoryCpuUsageAlert_idsMInstanceID_tag);
    memUsage.partition.idsMInstanceID = key.GetIdsMInstanceId();

    memUsage.has_memoryUserCpuUsageHistogram                  = true;
    memUsage.memoryUserCpuUsageHistogram.firstSeenTimeStamp   = firstHistogramTs;
    memUsage.memoryUserCpuUsageHistogram.lastSeenTimeStamp    = lastHistogramTs;
    memUsage.memoryUserCpuUsageHistogram.buckets.funcs.encode = &common::nanopb::encoders::EncodeScalarHistogram;
    memUsage.memoryUserCpuUsageHistogram.buckets.arg          = &binDataVector;
    memUsage.has_privCpuUsageHistogram                        = false;
    ruleEval.ruleEvaluationId                                 = m_currentTime;
    ruleEval.timestamp                                        = m_currentTime;

    ruleEval.which_RuleData
        = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_processMemoryUsageAlert_tag);
    ruleEval.RuleData.processMemoryUsageAlert = memUsage;

    auto const ok = addEventAlert(ruleEval, sender_events::CriticalEventAlert::ExcessiveProcessMemoryUsage, sd);

    if (ok)
    {
        LOG_DEBUG << "Excessive process memory usage alert updated: "
                  << "processName=" << key.m_processName << ",sensorInstanceID=" << key.GetSensorInstanceId()
                  << ",idsMInstanceID=" << key.GetIdsMInstanceId() << LOG_NOOP;
    }

    return ok;
}

bool
ResourceConsumptionNotificationEngine::createExcessiveProcessCpuUsageAlert(
    ResourceConsumptionEntry const&          key,
    brain::histogram::ScalarHistogram const& privHist,
    brain::histogram::ScalarHistogram const& userHist,
    uint32_t                                 userCpuPercentage,
    uint32_t                                 kernelCpuPercentage,
    uint32_t                                 alertThreshold,
    SecurityEventSensorData const&           sd)
{
    LOG_VERBOSE << "Excessive process CPU usage alert" << LOG_NOOP;

    brain::histogram::ScalarHistogram::BinDataVector privBinDataVector;
    uint64_t                                         firstPrivHistogramTs{};
    uint64_t                                         lastPrivHistogramTs{};
    if (!privHist.GetHistogramValues(privBinDataVector, firstPrivHistogramTs, lastPrivHistogramTs))
    {
        LOG_ERROR << "Cannot get process priv CPU usage histogram values" << LOG_NOOP;
        return false;
    }

    brain::histogram::ScalarHistogram::BinDataVector userBinDataVector;
    uint64_t                                         firstUsrHistogramTs{};
    uint64_t                                         lastUsrHistogramTs{};
    if (!userHist.GetHistogramValues(userBinDataVector, firstUsrHistogramTs, lastUsrHistogramTs))
    {
        LOG_ERROR << "Cannot get process user CPU usage histogram values" << LOG_NOOP;
        return false;
    }

    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
    com_vwg_connect_ids_idsperiodicreport_v1_ExcessiveProcessMemoryCpuUsageAlert cpuUsage
        = com_vwg_connect_ids_idsperiodicreport_v1_ExcessiveProcessMemoryCpuUsageAlert_init_default;

    cpuUsage.processName = common::nanopb::CreateEncodingCallback(key.m_processName);

    // Initialize the relevant fields depends if it's data of host or security type
    cpuUsage.which_sensor = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_ExcessiveProcessMemoryCpuUsageAlert_sensorInstanceID_tag);
    cpuUsage.sensor.sensorInstanceID = key.GetSensorInstanceId();
    cpuUsage.which_partition         = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_ExcessiveProcessMemoryCpuUsageAlert_idsMInstanceID_tag);
    cpuUsage.partition.idsMInstanceID = key.GetIdsMInstanceId();

    SET_NPB_FIELD(cpuUsage, alertThreshold, alertThreshold);
    SET_NPB_FIELD(cpuUsage, cpuUsageUserSpace, userCpuPercentage);
    SET_NPB_FIELD(cpuUsage, cpuUsageKernelSpace, kernelCpuPercentage);

    if (!CPU_USAGE_FIELD_FIILED_WITH_TOTAL_CPU(m_resourceConsumptionSources.GetResourceConsumptionSource(key)))
    {
        cpuUsage.has_privCpuUsageHistogram                  = true;
        cpuUsage.privCpuUsageHistogram.firstSeenTimeStamp   = firstPrivHistogramTs;
        cpuUsage.privCpuUsageHistogram.lastSeenTimeStamp    = lastPrivHistogramTs;
        cpuUsage.privCpuUsageHistogram.buckets.funcs.encode = &common::nanopb::encoders::EncodeScalarHistogram;
        cpuUsage.privCpuUsageHistogram.buckets.arg          = &privBinDataVector;
    }
    else
    {
        cpuUsage.has_privCpuUsageHistogram = false;
    }

    cpuUsage.has_memoryUserCpuUsageHistogram                  = true;
    cpuUsage.memoryUserCpuUsageHistogram.firstSeenTimeStamp   = firstUsrHistogramTs;
    cpuUsage.memoryUserCpuUsageHistogram.lastSeenTimeStamp    = lastUsrHistogramTs;
    cpuUsage.memoryUserCpuUsageHistogram.buckets.funcs.encode = &common::nanopb::encoders::EncodeScalarHistogram;
    cpuUsage.memoryUserCpuUsageHistogram.buckets.arg          = &userBinDataVector;
    ruleEval.ruleEvaluationId                                 = m_currentTime;
    ruleEval.timestamp                                        = m_currentTime;
    
    ruleEval.which_RuleData
        = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_processCpuUsageAlert_tag);
    ruleEval.RuleData.processCpuUsageAlert = cpuUsage;

    auto const ok = addEventAlert(ruleEval, sender_events::CriticalEventAlert::ExcessiveProcessCpuUsage, sd);

    if (ok)
    {
        LOG_DEBUG << "Excessive process CPU usage alert updated: "
                  << "processName=" << key.m_processName << ",sensorInstanceID=" << key.GetSensorInstanceId()
                  << ",idsMInstanceID=" << key.GetIdsMInstanceId() << LOG_NOOP;
    }

    return ok;
}

bool
ResourceConsumptionNotificationEngine::fillPriviledgedModeCpuUsageHistogram(
    SecurityEventMonitoringData& securityEventMonitoringData, ProcessPerformanceTableElement const& entry)
{
    auto& newEntry = securityEventMonitoringData.ProcessPerformance.Entries.back();

    brain::histogram::ScalarHistogram::BinDataVector histogramData;
    uint64_t                                         firstHistogramTs{};
    uint64_t                                         lastHistogramTs{};
    auto                                             getHistogramSucceeded
        = std::get<0>(entry.second).GetHistogramValues(histogramData, firstHistogramTs, lastHistogramTs);
    if (!getHistogramSucceeded)
    {
        return false;
    }

    newEntry.priviledgedModeCpuUsageHistogram.firstSeenTimeStamp = firstHistogramTs;
    newEntry.priviledgedModeCpuUsageHistogram.lastSeenTimeStamp  = lastHistogramTs;
    if (!histogramData.empty())
    {
        newEntry.has_priviledgedModeCpuUsageHistogram = true;
        for (auto const& record : histogramData)
        {
            newEntry.PriviledgedModeCpuUsageBuckets.emplace_back(com_vwg_connect_ids_idsperiodicreport_v1_Bucket{
                static_cast<uint32_t>(record.GetHeight()), static_cast<uint32_t>(record.GetInterval())});
        }
    }
    else
    {
        newEntry.has_priviledgedModeCpuUsageHistogram = false;
    }

    return true;
}

bool
ResourceConsumptionNotificationEngine::fillNonPriviledgedModeCpuUsageHistogram(
    SecurityEventMonitoringData& securityEventMonitoringData, ProcessPerformanceTableElement const& entry)
{
    auto& newEntry = securityEventMonitoringData.ProcessPerformance.Entries.back();

    brain::histogram::ScalarHistogram::BinDataVector histogramData;
    uint64_t                                         firstHistogramTs{};
    uint64_t                                         lastHistogramTs{};

    if (!std::get<1>(entry.second).GetHistogramValues(histogramData, firstHistogramTs, lastHistogramTs))
    {
        return false;
    }

    newEntry.nonPriviledgedModeCpuUsageHistogram.firstSeenTimeStamp = firstHistogramTs;
    newEntry.nonPriviledgedModeCpuUsageHistogram.lastSeenTimeStamp  = lastHistogramTs;
    if (!histogramData.empty())
    {
        newEntry.has_nonPriviledgedModeCpuUsageHistogram = true;
        for (auto const& record : histogramData)
        {
            newEntry.NonPriviledgedModeCpuUsageBuckets.emplace_back(com_vwg_connect_ids_idsperiodicreport_v1_Bucket{
                static_cast<uint32_t>(record.GetHeight()), static_cast<uint32_t>(record.GetInterval())});
        }
    }
    else
    {
        newEntry.has_nonPriviledgedModeCpuUsageHistogram = false;
    }

    return true;
}

bool
ResourceConsumptionNotificationEngine::fillMemoryUsageHistogram(
    SecurityEventMonitoringData& securityEventMonitoringData, ProcessPerformanceTableElement const& entry)
{
    auto& newEntry = securityEventMonitoringData.ProcessPerformance.Entries.back();

    brain::histogram::ScalarHistogram::BinDataVector histogramData;
    uint64_t                                         firstHistogramTs{};
    uint64_t                                         lastHistogramTs{};
    auto                                             getHistogramSucceeded
        = std::get<2>(entry.second).GetHistogramValues(histogramData, firstHistogramTs, lastHistogramTs);
    if (!getHistogramSucceeded)
    {
        return false;
    }

    newEntry.memoryUsageHistogram.firstSeenTimeStamp = firstHistogramTs;
    newEntry.memoryUsageHistogram.lastSeenTimeStamp  = lastHistogramTs;
    if (!histogramData.empty())
    {
        newEntry.has_memoryUsageHistogram = true;
        for (auto const& record : histogramData)
        {
            newEntry.MemoryUsageBuckets.emplace_back(com_vwg_connect_ids_idsperiodicreport_v1_Bucket{
                static_cast<uint32_t>(record.GetHeight()), static_cast<uint32_t>(record.GetInterval())});
        }
    }
    else
    {
        newEntry.has_memoryUsageHistogram = false;
    }

    return true;
}

bool
ResourceConsumptionNotificationEngine::fillHistogramsData(SecurityEventMonitoringData& securityEventMonitoringData,
                                                          ProcessPerformanceTableElement const& entry)
{
    return fillPriviledgedModeCpuUsageHistogram(securityEventMonitoringData, entry)
           && fillNonPriviledgedModeCpuUsageHistogram(securityEventMonitoringData, entry)
           && fillMemoryUsageHistogram(securityEventMonitoringData, entry);
}