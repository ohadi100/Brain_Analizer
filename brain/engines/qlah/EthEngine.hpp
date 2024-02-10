/**
 * @file
 * @brief     A rule engine for the Ethernet QLAH Sensor
 */
#ifndef ETH_ENGINE_HPP
#define ETH_ENGINE_HPP

#include "brain/engines/Engine.hpp"
#include "brain/engines/EngineEventSender.hpp"
#include "brain/engines/EthernetStatistics.hpp"

namespace brain
{

namespace diagnostics
{
namespace diag_accessor
{
class DiagFeatureFlags;
}  // namespace diag_accessor
}  // namespace diagnostics

namespace data_unit
{
class PortData;
} // data_unit

namespace engines
{
namespace qlah
{

using common::sensor_data::UPSensorData;

/**
 * @class   EthEngine
 * @brief   The EthEngine analyzes the ethernet sensor data of qlah sensors.
 */
class EthEngine final
  : public Engine
  , public EngineEventSender
{
public:
    using CounterManagerPtr   = common::counters::CounterManagerPtr;
    using EventCounter        = common::counters::EventCounter;
    using ScalarHistogram     = brain::histogram::ScalarHistogram;
    using EthSensorProperties = brain::sensor_data::EthSensorData::EthSensorProperties;
    using HistogramValues     = brain::engines::EthernetStatistics::HistogramValues;
    using PortData            = brain::data_unit::PortData;
    using EventNoiseFilterPtr = std::shared_ptr<brain::brain_noise_filter::EventNoiseFilter>;
    using EventCounterPtr     = std::shared_ptr<common::counters::EventCounter>;

    /**
     * @brief   Constructor
     * @param   debugCounters debugCounters
     * @param   msgRepository for communicate with sender manager
     * @param   ethStats ethStats
     * @param   reportSerializer - class to serialize idsperiodicreport proto object
     * @param   eventNoiseFilter eventNoiseFilter
     * @param   priority priority
     */
    EthEngine(CounterManagerPtr                                 debugCounters,
              MessageRepositoryPtr                              msgRepository,
              EthernetStatisticsPtr                             ethStats,
              EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
              EventNoiseFilterPtr                               eventNoiseFilter,
              events::EventPriority                             priority = events::EventPriority::Important);

    /**
     * @brief   Prepare for serialization eth stats using nanopb
     * @param   com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringTable& ethMonitoringTableBuffer
     * @return  true if all stats are successfully prepared for serialization, false otherwise
     */
    bool FetchContents(com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringTable& ethMonitoringTableBuffer);

    /**
     * @brief   Clears the counters contents.
     */
    void ClearContents() noexcept;

    /**
     * @brief   Create DOS alert.
     */
    void CreateDosAlert();

#ifndef TESTS
private:
#endif

    ReturnCode processInternal(UPSensorData sd) override;
    bool createRuleEvaluation(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval);

    void ethDiscardedFramesMonitoringHistogramsHandler(
        com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringTable& ethMonitoringTableBuffer);
    static bool encodeHistogramsTable(pb_ostream_t* stream, pb_field_t const* fields, void* const* arg);
    static bool serializeEthMonitoringData(pb_ostream_t* const stream, pb_field_t const* const fields, void* const* arg);
    static void createLinkUtilizationInRuleEvaluation(
        com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringData& ethMonitoringData,
        ScalarHistogram const& histogram);
    static void createEthMonitoringDataRuleEvaluation(
        com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringData& ethMonitoringData,
        std::string const& id,
        PortData const& portData);

    EventCounterPtr m_processSuccessCounter;
    EventCounterPtr m_failedCounter;
    EventCounterPtr m_beganProcessingCounter;

    std::unordered_map<std::string, std::shared_ptr<HistogramValues>> m_inOctetHistogramsMap;
    static brain::histogram::ScalarHistogram::BinDataVector m_linkUtilizationInBinDataVector;
    std::shared_ptr<EventCounter> m_filteredEventCounter;

    EthernetStatisticsPtr m_ethStats;
};

}  // namespace qlah
}  // namespace engines
}  // namespace brain

#endif  // ETH_ENGINE_HPP
