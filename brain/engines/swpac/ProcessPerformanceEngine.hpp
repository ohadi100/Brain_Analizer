/**
 * @file
 * @brief     A rule engine for the Process Performance sensor data
 */
#ifndef PROCESS_PERFORMANCE_ENGINE_HPP
#define PROCESS_PERFORMANCE_ENGINE_HPP

#include "brain/engines/security_events/NanoPB.hpp"
#include "brain/engines/security_events/resourceConsumptionNotification/ResourceConsumptionEntry.hpp"
#include "brain/histograms/ScalarHistogram.hpp"
#include "brain/sensor_data/swpac/ProcessPerformanceSensorData.hpp"
#include "common/utils/types/BoundedUnorderedMap.hpp"
#include "SwpacEngineBase.hpp"

namespace brain
{
namespace engines
{
namespace swpac
{

class IncidentCounterTable;
using ProcessPerformanceSensorData = brain::sensor_data::ProcessPerformanceSensorData;

class ProcessPerformanceEngine : public SwpacEngineBase
{
public:
    using ResourceConsumptionEntry = brain::engines::security_events::ResourceConsumptionEntry;
    using ConfigurationPtr         = common::configuration::Pointer;
    using EventCounter             = common::counters::EventCounter;
    using SecurityEventsPeriodicMonitoringData
        = brain::engines::security_events::nanopb::SecurityEventsPeriodicMonitoringData;

    using ProcessPerformanceTable = common::types::BoundedUnorderedMap<
        std::string,
        std::tuple<brain::histogram::ScalarHistogram, brain::histogram::ScalarHistogram>>;
    /**
     * @brief   Constructor
     * @param   CounterManagerPtr debugCounters
     * @param   msgRepository for communicate with sender manager sender.
     * @param   reportSerializer - class to serialize idsperiodicreport proto object
     * @param   EventNoiseFilterPtr eventNoiseFilter
     * @param   EventPriority priority
     */
    ProcessPerformanceEngine(CounterManagerPtr                                 debugCounters,
                             MessageRepositoryPtr                              msgRepository,
                             ConfigurationPtr                                  config,
                             EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                             EventNoiseFilterPtr                               eventNoiseFilter,
                             events::EventPriority priority = events::EventPriority::Important);

    /**
     * @brief   Serializes SecurityEventsMonitoringData (requirement 1.3)
     * @param   securityEventsMonitoring - Output for serialized SecurityEventsMonitoringData.
     * @param   startTime - start timestap in miliseconds for the periodic report creation
     * @param   endTime - end timestap in miliseconds for the periodic report creation
     * @return  bool - true for success, otherwise false.
     */
    bool CreateSecurityEventsMonitoringData(SecurityEventsPeriodicMonitoringData& securityEventsMonitoring,
                                            uint64_t                              startTime,
                                            uint64_t                              endTime);

private:
    ReturnCode processInternal(UPSensorData sd) override;

    void resetTable();

    bool addEventAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval,
                       brain::sender_events::CriticalEventAlert                       event);

    bool createExcessiveProcessMemoryUsageAlert(brain::histogram::ScalarHistogram const& hist,
                                                ProcessPerformanceSensorData const&      sd);

    bool createExcessiveProcessCpuUsageAlert(brain::histogram::ScalarHistogram const& total,
                                             ProcessPerformanceSensorData const&      sd);

    ProcessPerformanceTable                                            m_processPerformanceTable;
    static brain::histogram::ScalarHistogram::BinIntervalsVector const m_memoryUsageBins;
    static brain::histogram::ScalarHistogram::BinIntervalsVector const m_cpuUsageBins;

    EventCounterPtr m_excessiveProcessMemoryAlertCounter;
    EventCounterPtr m_excessiveProcessCpuAlertCounter;
    EventCounterPtr m_failedCounter;

    uint32_t m_memoryUsageAlertThresholdPerProcess{50U};
    uint32_t m_cpuUsageAlertThresholdPerProcess{70U};
};

}  // namespace swpac
}  // namespace engines
}  // namespace brain

#endif  // PROCESS_PERFORMANCE_ENGINE_HPP