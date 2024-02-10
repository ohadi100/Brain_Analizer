/**
 * @file
 * @brief This file contains the definition of the PeriodicStatisticsEngine class and its functionality
 */
#ifndef PERIODIC_STATISTICS_ENGINE_HPP
#define PERIODIC_STATISTICS_ENGINE_HPP

#include "swpac/KernelLogEngine.hpp"
#include "qlah/EthEngine.hpp"
#include "qlah/HostEngine.hpp"
#include "security_events/SecurityEventsEngine.hpp"
#include "brain/engines/swpac/ProcessPerformanceEngine.hpp"
#include "security_events/NanoPB.hpp"
#include "Engine.hpp"
#include "EngineEventSender.hpp"
#include "security_events/PassedDroppedAlertsNanoPB.hpp"
#include "common/utils/types/BoundedUnorderedMap.hpp"
#include "brain/histograms/RateHistogram.hpp"

using brain::events::EventPriority;
namespace brain
{

namespace publishers
{
namespace utils
{
class ExceededMessageSizeCheck;
} //namespace utils
} //namespace publishers

namespace engines
{
namespace swpac
{
class IncidentCounterTable;
}
}

namespace diagnostics
{
    namespace diag_accessor
    {
        class DiagFeatureFlags;
    } // namespace diag_accessor
} // namespace diagnostics

namespace engines
{

using common::sensor_data::UPSensorData;
using ScalarHistogram    = brain::histogram::ScalarHistogram;
using ScalarHistogramPtr = std::shared_ptr<brain::histogram::ScalarHistogram>;

/**
 * @class   PeriodicStatisticsEngine
 * @brief   The PeriodicStatisticsEngine class defines the rule engine of the OS log Report analysis logic.
 *          The class defines and runs the process of the rule engines of the OS log Report analysis.
 */
class PeriodicStatisticsEngine
  : public Engine
  , public EngineEventSender
{
public:
    using BinDataVector              = brain::histogram::RateHistogram::BinDataVector;
    using CounterManagerPtr          = common::counters::CounterManagerPtr;
    using EventCounter               = common::counters::EventCounter;
    using DiagnosticsManagerPtr      = brain::diagnostics::DiagnosticsManagerInterface::Pointer;
    using PortData                   = brain::data_unit::PortData;
    using EventNoiseFilterPtr        = std::shared_ptr<brain::brain_noise_filter::EventNoiseFilter>;
    using SPExceededMessageSizeCheck = std::shared_ptr<brain::publishers::utils::ExceededMessageSizeCheck>;
    using EventCounterPtr            = std::shared_ptr<common::counters::EventCounter>;

    struct PeriodicStatisticsEngineConfig
    {
        CounterManagerPtr                                      debugCounters;
        MessageRepositoryPtr                                   msgRepository;
        std::unordered_map<uint32_t, std::shared_ptr<Engine>>& periodicEngines;
        DiagnosticsManagerPtr                                  diagnosticsManager;
        EngineEventSender::IDSPeriodicReportSerializerPtr      reportSerializer;
        EventNoiseFilterPtr                                    eventNoiseFilter;
        SPExceededMessageSizeCheck                             exceededMessageSizeCheck;
        EventPriority                                          priority{EventPriority::Critical};
    };

     /**
     * @brief   Constructor
     * @param   PeriodicStatisticsEngineConfig constructor parameters
     */
    explicit PeriodicStatisticsEngine(const PeriodicStatisticsEngineConfig &config);

    virtual ~PeriodicStatisticsEngine() = default;

    /**
     * @brief    default copy constructor
     */
    PeriodicStatisticsEngine(const PeriodicStatisticsEngine& other) = delete;

    /**
     * @brief    default move constructor
     */
    PeriodicStatisticsEngine(PeriodicStatisticsEngine&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    PeriodicStatisticsEngine& operator=(PeriodicStatisticsEngine const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    PeriodicStatisticsEngine& operator=(PeriodicStatisticsEngine&&) = delete;


    /**
     * @brief   Serialize FilteredIncidentsByNoiseFilterData.
     * @param   com_vwg_connect_ids_idsperiodicreport_v1_PassedDroppedIncidentsData& passedDroppedIncidentsBuffer - the serialize FilteredIncidentsByNoiseFilterData.
     * @return  bool - true for success, otherwise false.
     */
    bool SerializePassedDroppedIncidentsData(com_vwg_connect_ids_idsperiodicreport_v1_PassedDroppedIncidentsData& passedDroppedIncidentsBuffer) const noexcept;

    /**
     * @brief   Serialize EthMonitoringTable.
     * @param   com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringTable& ethMonitoringTableBuffe - the serialize EthMonitoringTable.
     * @return  bool - true for success, otherwise false.
     */
    bool SerializeEthMonitoringTable(com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringTable& ethMonitoringTableBuffer);

    /**
     * @brief   Serialize HostErrorMonitoringData.
     * @param   com_vwg_connect_ids_idsperiodicreport_v1_HostErrorMonitoringData& hostErrorMonitoringBuffer - the serialize HostErrorMonitoringData.
     * @return  bool - true for success, otherwise false.
     */
    bool SerializeHostErrorMonitoringData(com_vwg_connect_ids_idsperiodicreport_v1_HostErrorMonitoringCountersData& hostErrorMonitoringCountersBuffer);

    /**
     * @brief Set the Incident Counter Table object
     * @param std::shared_ptr<IncidentCounterTable> incidentCounter - incident counter table
     * @return none
     */
    inline void
    SetIncidentCounterTable(brain::engines::swpac::SPIncidentCounterTable incidentCounter)
    {
        m_dhmIncidentTable = incidentCounter;
    }

protected:

    ReturnCode processInternal(UPSensorData sd) override;
    bool createRuleEvaluation(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval);
    SPExceededMessageSizeCheck m_exceededMessageSizeCheck;
    void clearEngines();
    
private:

    void createIdsStatisticsPeriodicReport(com_vwg_connect_ids_idsperiodicreport_v1_IdsStatisticsPeriodicReport& statisticsPeriodicReport);

#if defined(DEBUG_COUNTER) || !defined(HCP5_PLATFORM)
    void printEvent(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval);
#endif //defined(DEBUG_COUNTER) || !defined(HCP5_PLATFORM)
    void printEventToLog(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval);

    CounterManagerPtr m_debugCounters;
    std::shared_ptr<qlah::EthEngine> m_ethEngine;
    std::shared_ptr<qlah::HostEngine> m_hostEngine;
    std::shared_ptr<security_events::SecurityEventsEngine> m_securityEventsEngine;
    std::shared_ptr<brain::engines::swpac::ProcessPerformanceEngine> m_processPerformanceEngine;
    brain::engines::swpac::SPIncidentCounterTable m_dhmIncidentTable;

    security_events::nanopb::SecurityEventsPeriodicMonitoringData m_securityEventsStorage;
    brain::engines::security_events::nanopb::PassedDroppedAlertsData m_passedDroppedAlertData;
    
    // counters
    EventCounterPtr m_secEveMonitorDataExistCounter;
    EventCounterPtr m_passedDroppedMonitoringDataExistCounter;
    EventCounterPtr m_ethMonitoringTableExistCounter;
    EventCounterPtr m_hostErrorMonitoringDataExistCounter;
    EventCounterPtr m_processPerformanceDataExistsCounter;
    EventCounterPtr m_failedProcessCounter;
    EventCounterPtr m_measurementIntervalStartedCounter;
    EventCounterPtr m_measurementIntervalEndedCounter;
    EventCounterPtr m_dhmIncidentCounterCounter;
    EventCounterPtr m_hcp1StatisticsPeriodcReportCounter;
    EventCounterPtr m_exceededMessageSizeCounter;
    EventCounterPtr m_failedCounter;

    std::array<EventCounterPtr, common::sensor_data::PRIORITY_COUNT> m_queueManagerEnqueueSuccessCounters;
    std::array<EventCounterPtr, common::sensor_data::PRIORITY_COUNT> m_queueManagerEnqueueFailCounters;
    std::array<EventCounterPtr, EventPriority::NUM_OF_EVENT_PRIORITIES> m_eventsStorageEnqueueSuccessCounters;
    std::array<EventCounterPtr, EventPriority::NUM_OF_EVENT_PRIORITIES> m_eventsStorageEnqueueFailCounters;    

    std::atomic<bool>& m_hostErrorMonitoringOn;               // Diag Adaptations - 0x7704 - HostErrorMonitoringOn
    uint64_t           m_monitoringPeriodStartTimestampMs{};  // used to store the start time of the monitoring for PR
};
} // namespace engines
} // namespace brain

#endif // PERIODIC_STATISTICS_ENGINE_HPP
