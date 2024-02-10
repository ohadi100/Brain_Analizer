/**
 * @file
 * @brief      This file declare the functionality of class that handle ResourceConsumption notification events.
 */
#pragma once

#include "ResourceConsumptionEntry.hpp"
#include "ResourceConsumptionSources.hpp"
#include "brain/engines/security_events/IStatisticsDataHolder.hpp"
#include "brain/engines/security_events/SecurityEventEngineCreateEvent.hpp"
#include "brain/histograms/ScalarHistogram.hpp"
#include "common/utils/types/BoundedUnorderedMap.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

/**
 * @class   ResourceConsumptionNotificationEngine
 * @brief   The ResourceConsumptionNotificationEngine analyzes ResourceConsumptionNotification Events.
 */
class ResourceConsumptionNotificationEngine
  : public SecurityEventEngineCreateEvent
  , public IStatisticsDataHolder
{
public:
    using ProcessPerformanceTable        = common::types::BoundedUnorderedMap<ResourceConsumptionEntry,
                                                                       std::tuple<brain::histogram::ScalarHistogram,
                                                                                  brain::histogram::ScalarHistogram,
                                                                                  brain::histogram::ScalarHistogram>>;
    using ProcessPerformanceTableElement = std::pair<brain::engines::security_events::ResourceConsumptionEntry,
                                                     std::tuple<brain::histogram::ScalarHistogram,
                                                                brain::histogram::ScalarHistogram,
                                                                brain::histogram::ScalarHistogram>>;
    using ProcessPerformanceDataMap
        = common::types::BoundedUnorderedMap<ResourceConsumptionEntry, ResourceConsumptionHistoryData>;
    using CounterManagerPtr = std::shared_ptr<common::counters::CounterManager>;
    using ConfigurationPtr  = common::configuration::Pointer;

    /**
     * @brief Construct a new Resource Consumption Notification Engine object
     *
     * @param debugCounters debug counter object
     * @param config configuration object
     * @param sender
     * @param msgRepository for communicate with sender manager sender
     * @param reportSerializer - class to serialize idsperiodicreport proto object
     * @param eventNoiseFilter noise filter
     * @param priority priority of the event
     */
    ResourceConsumptionNotificationEngine(CounterManagerPtr                                 debugCounters,
                                          ConfigurationPtr                                  config,
                                          MessageRepositoryPtr                              msgRepository,
                                          EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                                          EventNoiseFilterPtr                               eventNoiseFilter = nullptr,
                                          events::EventPriority priority = events::EventPriority::Important);

    /**
     * @brief Fill Statistics Data
     * @param securityEventMonitoringData - The structure to fill
     * @return bool - true for success, otherwise false.
     */
    bool FillStatisticData(SecurityEventMonitoringData& securityEventMonitoringData) override;

    /**
     * @brief reset Statistics Data
     *
     */
    void ResetStatisticData() override;

#ifdef TESTS
    inline size_t
    GetProcessPerformanceTableSize() const
    {
        return m_processPerformanceTable.size();
    }

    inline size_t
    GetProcessPerformanceDataSize() const
    {
        return m_processPerformanceData.size();
    }
#endif  // TESTS

protected:
    ReturnCode processInternal(UPSensorData sd) override;

    bool createExcessiveProcessMemoryUsageAlert(ResourceConsumptionEntry const&          key,
                                                brain::histogram::ScalarHistogram const& hist,
                                                SecurityEventSensorData const&           sd);
    bool createExcessiveProcessCpuUsageAlert(ResourceConsumptionEntry const&          key,
                                             brain::histogram::ScalarHistogram const& privHist,
                                             brain::histogram::ScalarHistogram const& userHist,
                                             uint32_t                                 userCpuPercentage,
                                             uint32_t                                 kernelCpuPercentage,
                                             uint32_t                                 alertThreshold,
                                             SecurityEventSensorData const&           sd);

    bool fillHistogramsData(SecurityEventMonitoringData&          securityEventMonitoringData,
                            ProcessPerformanceTableElement const& entry);
    bool fillPriviledgedModeCpuUsageHistogram(SecurityEventMonitoringData&          securityEventMonitoringData,
                                              ProcessPerformanceTableElement const& entry);
    bool fillNonPriviledgedModeCpuUsageHistogram(SecurityEventMonitoringData&          securityEventMonitoringData,
                                                 ProcessPerformanceTableElement const& entry);
    bool fillMemoryUsageHistogram(SecurityEventMonitoringData&          securityEventMonitoringData,
                                  ProcessPerformanceTableElement const& entry);

    ProcessPerformanceTable                                            m_processPerformanceTable;
    ProcessPerformanceDataMap                                          m_processPerformanceData;
    ResourceConsumptionSources                                         m_resourceConsumptionSources;
    uint32_t                                                           m_userCpuConsumptionPercentage{};
    uint32_t                                                           m_kernelCpuConsumptionPercentage{};
    uint32_t                                                           m_memConsumptionPercentage{};
    static brain::histogram::ScalarHistogram::BinIntervalsVector const m_memoryUsageBins;
    static brain::histogram::ScalarHistogram::BinIntervalsVector const m_cpuUsageBins;
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain