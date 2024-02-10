/**
 * @file
 * @brief This file contains the definition of the PeriodicStatisticsEngine class and its functionality
 */
#ifndef PERIODIC_STATISTICS_ENGINE_HPP
#define PERIODIC_STATISTICS_ENGINE_HPP


#include "brain/engines/Engine.hpp"
#include "brain/engines/EngineEventSender.hpp"
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "brain/histograms/RateHistogram.hpp"
#include "brain/histograms/ScalarHistogram.hpp"
#include "security_events/NanoPB.hpp"

using ScalarHistogram    = brain::histogram::ScalarHistogram;
using ScalarHistogramPtr = std::shared_ptr<brain::histogram::ScalarHistogram>;

namespace brain
{

namespace engines
{

using common::sensor_data::UPSensorData;

/**
 * @class   PeriodicStatisticsEngine
 * @brief   The PeriodicStatisticsEngine class defines the rule engine of the OS log Report analysis logic.
 *          The class defines and runs the process of the rule engines of the OS log Report analysis.
 */
class PeriodicStatisticsEngine final
  : public Engine
  , public EngineEventSender
{
public:
    using BinDataVector         = histogram::RateHistogram::BinDataVector;
    using CounterManagerPtr     = common::counters::CounterManagerPtr;
    using EventCounter          = common::counters::EventCounter;
    using DiagnosticsManagerPtr = brain::diagnostics::DiagnosticsManagerInterface::Pointer;
    using EventNoiseFilterPtr    = std::shared_ptr<brain::brain_noise_filter::EventNoiseFilter>;

    /**
     * @brief   Constructor
     * @param   CounterManagerPtr & debugCounters - counter Manager
     * @param   msgRepository for communicate with sender manager sender
     * @param   std::unordered_map<uint32_t, std::shared_ptr<Engine>>& periodicEngines
     * @param   DiagnosticsManagerPtr diagnosticsManager
     * @param   reportSerializer - class to serialize idsperiodicreport proto object
     * @param   EventNoiseFilterPtr eventNoiseFilter
     * @param   EventPriority priority
     */
    PeriodicStatisticsEngine(CounterManagerPtr                                      debugCounters,
                             MessageRepositoryPtr                                   msgRepository,
                             std::unordered_map<uint32_t, std::shared_ptr<Engine>>& periodicEngines,
                             DiagnosticsManagerPtr                                  diagnosticsManager,
                             EngineEventSender::IDSPeriodicReportSerializerPtr      reportSerializer,
                             EventNoiseFilterPtr                                    eventNoiseFilter,
                             EventPriority                                          priority = EventPriority::Critical);

protected:
    ReturnCode processInternal(UPSensorData sd) override;
    bool createRuleEvaluation(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval);

private:
    // void createIdsStatisticsPeriodicReport(com_vwg_connect_ids_idsperiodicreport_v1_IdsStatisticsPeriodicReport&
    // statisticsPeriodicReport);

#if defined(DEBUG_COUNTER) || !defined(HCP5_PLATFORM)
    void printEvent(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval);
#endif  // defined(DEBUG_COUNTER) || !defined(HCP5_PLATFORM)
    void printEventToLog(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval);

    CounterManagerPtr m_debugCounters;

    BinDataVector m_hfmHistogram;

    // counters
    EventCounterPtr                                                     m_noAvailableStorageCounter;
    EventCounterPtr                                                     m_failedProcessCounter;
    EventCounterPtr                                                     m_measurementIntervalStartedCounter;
    EventCounterPtr                                                     m_measurementIntervalEndedCounter;
    std::array<EventCounterPtr, common::sensor_data::PRIORITY_COUNT>    m_queueManagerEnqueueSuccessCounters;
    std::array<EventCounterPtr, common::sensor_data::PRIORITY_COUNT>    m_queueManagerEnqueueFailCounters;
    std::array<EventCounterPtr, EventPriority::NUM_OF_EVENT_PRIORITIES> m_eventsStorageEnqueueSuccessCounters;
    std::array<EventCounterPtr, EventPriority::NUM_OF_EVENT_PRIORITIES> m_eventsStorageEnqueueFailCounters;
};
}  // namespace engines
}  // namespace brain

#endif  // PERIODIC_STATISTICS_ENGINE_HPP
