/**
 * @file
 * @brief     Processes ethernet statistics for multiple sensors.
 *            Implements the visitor pattern by visiting the engines processing
 *            Ethernet related events.
 */
#ifndef ETHERNET_STATISTICS_HPP
#define ETHERNET_STATISTICS_HPP

#include <unordered_map>
#include "common/counter_manager/CounterManager.hpp"
#include "brain/histograms/ScalarHistogram.hpp"
#include "brain/histograms/RateHistogram.hpp"
#include "security_events/SecurityEventInstanceIdEntry.hpp"
#include "qlah/PortData.hpp"
#include "brain/sensor_data/qlah/EthSensorData.hpp"
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "brain/engines/qlah/PortData.hpp"
#include "brain/engines/security_events/DataflowStatisticsEngineKeyEntry.hpp"
#include "brain/histograms/ScalarHistogram.hpp"
#include "brain/sensor_data/qlah/EthSensorData.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/utils/types/BoundedUnorderedMap.hpp"
#include "brain/engines/qlah/EthUnknownProtocolAlert.hpp"
#include "brain/engines/qlah/EthIllegalVlanFramesAlert.hpp"

namespace brain
{
namespace sensor_data
{
class SecurityEventSensorData;
} // sensor_data
namespace engines
{
namespace security_events
{
class SecurityEventsEngine;
struct SECEV_SWITCH_DATAFLOW_STATISTICS;
} // security_events
namespace qlah
{
class EthEngine;
}  // namespace qlah

class EthernetStatistics
{
public:
    using CounterManagerPtr                = common::counters::CounterManagerPtr;
    using DiagnosticsManagerPtr = brain::diagnostics::DiagnosticsManagerInterface::Pointer;
    using SecurityEventsEngine             = brain::engines::security_events::SecurityEventsEngine;
    using EthEngine                        = brain::engines::qlah::EthEngine;
    using SecurityEventSensorData          = brain::sensor_data::SecurityEventSensorData;
    using PortData                         = brain::data_unit::PortData;
    using ScalarHistogram                  = histogram::ScalarHistogram;
    using EventCounter                     = common::counters::EventCounter;
    using ConfigurationPtr                 = common::configuration::Pointer;
    using DataflowStatisticsEngineKeyEntry = brain::engines::security_events::DataflowStatisticsEngineKeyEntry;
    using EventCounterWithTs               = common::counters::EventCounterWithTs;
    using HistogramsMap
        = common::types::BoundedUnorderedMap<std::string,
                                             std::pair<uint64_t, std::unique_ptr<histogram::RateHistogram>>>;
    using EthSensorData                    = brain::sensor_data::EthSensorData;
    using SECEV_SWITCH_DATAFLOW_STATISTICS = brain::engines::security_events::SECEV_SWITCH_DATAFLOW_STATISTICS;
    using EthUnknownProtocolAlertPtr       = brain::engines::qlah::EthUnknownProtocolAlert::EthUnknownProtocolAlertPtr;
    using EthIllegalVlanFramesAlertPtr     = brain::engines::qlah::EthIllegalVlanFramesAlert::EthIllegalVlanFramesAlertPtr;

    // ConMod CD is identified by IDSm instance ID 0x032.
    // HCP4 M2_1 is identified by IDSm instance ID 0x019.
    static constexpr uint16_t CONMOD_IDSM = 0x032;
    static constexpr uint16_t HCP4_IDSM = 0x019;

    static constexpr uint32_t DEFAULT_BUCKET_THRESHOLD_RATE = 100000000U;
    static constexpr uint32_t DEFAULT_BUCKET_MAX_BURST      = 20000U;

    enum { LINK_OUT_DIRECTION = 0, LINK_IN_DIRECTION, LINK_DIRECTION_COUNT };
    using LinkUtilizationHistogramTable
        = common::types::BoundedUnorderedMap<DataflowStatisticsEngineKeyEntry, std::tuple<ScalarHistogram, ScalarHistogram>>;
    class EthernetSwitchesCountersData
    {
    public:
        uint32_t dropPktBufOverrung{};
        uint32_t dropPktCrC{};
        uint32_t oversizePkt{};
        uint32_t undersizePkt{};
        uint32_t algnmtErr{};

        bool operator==(EthernetSwitchesCountersData const& other) const
        {
            return (other.dropPktBufOverrung == dropPktBufOverrung) &&
                   (other.dropPktCrC == dropPktCrC) &&
                   (other.oversizePkt == oversizePkt) &&
                   (other.undersizePkt == undersizePkt) &&
                   (other.algnmtErr == algnmtErr);
        }
    };
    using EthernetSwitchesCountersTable
        = common::types::BoundedUnorderedMap<DataflowStatisticsEngineKeyEntry, EthernetSwitchesCountersData>;

    struct HistogramValues
    {
        uint64_t                                firstTimestamp{};
        uint64_t                                lastTimestamp{};
        histogram::RateHistogram::BinDataVector histogramsData;
    };

    /**
     * @brief   Constructor
     * @param   CounterManagerPtr debugCounters
     * @param   DiagnosticsManagerPtr diagnosticsManager
     * @param   ConfigurationPtr config
     */
    EthernetStatistics(CounterManagerPtr debugCounters, DiagnosticsManagerPtr diagnosticsManager, ConfigurationPtr config);

    /**
     * @brief   Handle received SomeIp Ethernet events
     * @param   SecurityEventsEngine* engine (visited component in visitor pattern)
     * @param   SecurityEventSensorData const& sd
     * @param   SECEV_SWITCH_DATAFLOW_STATISTICS const* event
     * @return  true if no error, false otherwise (a generated event is dropped)
     */
    bool HandleEvent(SecurityEventsEngine*                   engine,
                     SecurityEventSensorData const&          sd,
                     SECEV_SWITCH_DATAFLOW_STATISTICS const* event);

    /**
     * @brief   Reset all tables after sending their content with proto buffer
     */
    void ClearSomeIpStats();

    /**
     * @brief   Handle received QLAH Ethernet events
     * @param   EthEngine* engine (visited component in visitor pattern)
     * @param   EthSensorData const& ethSD
     * @return  true if no error, false otherwise (a generated event is dropped)
     */
    bool HandleEvent(EthEngine* engine, EthSensorData const& ethSD);

    /**
     * @brief   Clear QLAH related stats
     */
    void ClearQlahStats();

    common::types::BoundedUnorderedMap<std::string, PortData> const* GetPortsData() const
    {
        return &m_qlahStats.portsData;
    }

    bool GetInOctetsHistogramsValues(std::unordered_map<std::string, std::shared_ptr<HistogramValues>>& histogramsData) const;
    HistogramsMap const& GetBroadcastMulticastHistograms() const
    {
        return m_qlahStats.broadcastMulticastHistograms;
    }

    HistogramsMap const& GetInOctetsHistograms() const
    {
        return m_qlahStats.inOctetsHistograms;
    }

    std::string const& GetAlertPortId() const
    {
        return m_qlahStats.alertPortId;
    }

    LinkUtilizationHistogramTable const& GetLinkUtilizationHistogramTable() const
    {
        return m_someIpStats.linkUtilizationHistogramTable;
    }
    EthernetSwitchesCountersTable const& GetEthernetSwitchesCountersTable() const
    {
        return m_someIpStats.ethernetSwitchesCountersTable;
    }
    static ScalarHistogram::BinIntervalsVector const& GetOctetsRatesBins(bool isHighSpeedRateBin)
    {
        return isHighSpeedRateBin ? SomeIpStats::highSpeedOctetsRatesBins : SomeIpStats::octetsRatesBins;
    }

    void ClearLinkUtilization();
    void ClearBroadcastMulticast();

    /**
     * @brief Set the Eth Unknown Protocol Alert object
     * 
     * @param ethUnknownProtocolAlert - eth unknown protocol alert object 
     */
    void SetEthUnknownProtocolAlert(EthUnknownProtocolAlertPtr ethUnknownProtocolAlert)
    {
        m_ethUnknownProtocolAlert = std::move(ethUnknownProtocolAlert);
    }

    /**
     * @brief Set the Illegal Vlan Frames Alert object
     * 
     * @param EthIllegalVlanFramesAlert - set eth illegal vlan frames alert
     */
    void SetEthIllegalVlanFramesAlert(EthIllegalVlanFramesAlertPtr  ethIllegalVlanFramesAlert)
    {
        m_ethIllegalVlanFramesAlert = std::move(ethIllegalVlanFramesAlert);
    }

#ifdef TESTS
    std::shared_ptr<EventCounter> GetDenialOfServiceAlertCounter() const
    {
        return m_qlahStats.denialOfServiceAlertCounter;
    }
#endif

private:
    void initCounters(CounterManagerPtr debugCounters);
    void updateEthernetSwitchesCountersTable(DataflowStatisticsEngineKeyEntry const& entry,
                                             SECEV_SWITCH_DATAFLOW_STATISTICS const* event);
    bool updateLinkUtilizationHistogramTable(SecurityEventsEngine*                              engine,
                                             DataflowStatisticsEngineKeyEntry const&            entry,
                                             brain::sensor_data::SecurityEventSensorData const& sd,
                                             SECEV_SWITCH_DATAFLOW_STATISTICS const*            event);
    void updateDiscardedFrameValues(EthSensorData const& ethSD, PortData& portData);
    void updateInOctetsHistograms(uint64_t const timeStamp, uint64_t const inOctetsCounter, std::string const& id);
    bool isThresholdExceeded(uint64_t const timeStamp, uint64_t const byteDiff, PortData& portData);
    void updateBroadcastMulticastHistograms(uint64_t timeStamp,
                                            uint64_t broadcastMulticastCounter,
                                            std::string const& id);
    struct SomeIpStats
    {
        std::shared_ptr<EventCounter> linkUtilizationAlertCounter;

        LinkUtilizationHistogramTable linkUtilizationHistogramTable{30U};
        EthernetSwitchesCountersTable ethernetSwitchesCountersTable{30U};

        static ScalarHistogram::BinIntervalsVector const octetsRatesBins;
        static ScalarHistogram::BinIntervalsVector const highSpeedOctetsRatesBins;
    } m_someIpStats;

    //

    struct QlahStats
    {
        std::shared_ptr<EventCounter> failedCounter;
        std::shared_ptr<EventCounter> successCounter;
        std::shared_ptr<EventCounter> inOctetsHistogramFailedAddDataCounter;
        std::shared_ptr<EventCounter> outBroadcastHistogramFailedAddDataCounter;
        std::shared_ptr<EventCounter> denialOfServiceAlertCounter;
        std::shared_ptr<EventCounter> ethMonitorTableEntriesCounter;

        std::shared_ptr<EventCounterWithTs> unknownProtocolFramesCounter;
        std::shared_ptr<EventCounterWithTs> illegalVlanDropCounter;
        std::shared_ptr<EventCounterWithTs> illegalIpDropCounter;

        std::string alertPortId;

        HistogramsMap inOctetsHistograms{30U};
        HistogramsMap broadcastMulticastHistograms{30U};

        static histogram::RateHistogram::BinIntervalsVector const octetsRatesBins;
        static histogram::RateHistogram::BinIntervalsVector const broadcastMulticastRatesBins;

        common::types::BoundedUnorderedMap<std::string, PortData> portsData{30U};
    } m_qlahStats;

    std::atomic<bool>& m_linkUtilizationMonitoringOn;  // Diag Adaptations - 0x7704 - LinkUtilizationMonitoringOn
    std::atomic<bool>&
        m_broadcastMulticastRatesMonitoringOn;  // Diag Adaptations - 0x7704 - BroadcastMulticastRatesMonitoringOn
    std::atomic<bool>& m_discardedFramesMonitoringOn;  // Diag Adaptations - 0x7704 - DiscardedRatesMonitoringOn

    uint32_t m_bucketThresholdRate{DEFAULT_BUCKET_THRESHOLD_RATE};
    uint32_t m_bucketMaxBurst{DEFAULT_BUCKET_MAX_BURST};

    EthUnknownProtocolAlertPtr   m_ethUnknownProtocolAlert;
    EthIllegalVlanFramesAlertPtr m_ethIllegalVlanFramesAlert;
};

using EthernetStatisticsPtr = std::shared_ptr<EthernetStatistics>;

} // engines
} // brain

#endif // ETHERNET_STATISTICS_HPP
