/**
 * @file
 * @brief     This file contains the functionality of the EthernetStatistics class
 */
#include "EthernetStatistics.hpp"
#include <cmath>
#include "autogen/gsep/SecurityEvents.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "brain/sensor_data/security_events/SecurityEventSensorData.hpp"
#include "brain/utils/UtilsConstants.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "qlah/EthEngine.hpp"
#include "security_events/SecurityEventsEngine.hpp"

using namespace brain::engines;
using namespace brain;

// For compatibility with prior C++ International Standards
constexpr uint32_t EthernetStatistics::DEFAULT_BUCKET_THRESHOLD_RATE;
constexpr uint32_t EthernetStatistics::DEFAULT_BUCKET_MAX_BURST;

using brain::histogram::RateHistogram;
using brain::histogram::ScalarHistogram;

namespace brain
{
namespace engines
{
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;

static ScalarHistogram::BinIntervalsVector&&
initEthernetStatisticsSomeIpStatsOctetsRatesBins() noexcept
{
    static ScalarHistogram::BinIntervalsVector newVector{
        0,
        1.0,
        10.0,
        20.0,
        30.0,
        40.0,
        50.0,
        60.0,
        70.0,
        80.0,
        90.0,
        100.0,
        std::numeric_limits<int32_t>::max()  // bins are represented with protobuf using float type
    };
    return std::move(newVector);
}
ScalarHistogram::BinIntervalsVector const EthernetStatistics::SomeIpStats::octetsRatesBins
    = initEthernetStatisticsSomeIpStatsOctetsRatesBins();


static ScalarHistogram::BinIntervalsVector&&
initEthernetStatisticsSomeIpStatsHighSpeedOctetsRatesBins() noexcept
{
    static ScalarHistogram::BinIntervalsVector newVector{
        0,
        100.0,
        200.0,
        300.0,
        400.0,
        500.0,
        600.0,
        700.0,
        800.0,
        900.0,
        1000.0,
        std::numeric_limits<int32_t>::max()  // bins are represented with protobuf using float type
    };
    return std::move(newVector);
}
ScalarHistogram::BinIntervalsVector const EthernetStatistics::SomeIpStats::highSpeedOctetsRatesBins
    = initEthernetStatisticsSomeIpStatsHighSpeedOctetsRatesBins();

static RateHistogram::BinIntervalsVector&&
initEthernetStatisticsQlahStatsOctetsRatesBins() noexcept
{
    static RateHistogram::BinIntervalsVector newVector{MEGA_D,
                                                       2.0 * MEGA_D,
                                                       3.0 * MEGA_D,
                                                       4.0 * MEGA_D,
                                                       5.0 * MEGA_D,
                                                       6.0 * MEGA_D,
                                                       7.0 * MEGA_D,
                                                       8.0 * MEGA_D,
                                                       9.0 * MEGA_D,
                                                       10.0 * MEGA_D};
    return std::move(newVector);
}
RateHistogram::BinIntervalsVector const EthernetStatistics::QlahStats::octetsRatesBins
    = initEthernetStatisticsQlahStatsOctetsRatesBins();

static RateHistogram::BinIntervalsVector&&
initEthernetStatisticsQlahStatsBroadcastMulticastRatesBins() noexcept
{
    static RateHistogram::BinIntervalsVector newVector{1.0, 10.0, 20.0, 50.0, 100.0, 200.0, 500.0, 1000.0};
    return std::move(newVector);
}
RateHistogram::BinIntervalsVector const EthernetStatistics::QlahStats::broadcastMulticastRatesBins
    = initEthernetStatisticsQlahStatsBroadcastMulticastRatesBins();

enum BurstConfigParamIndexes : uint8_t
{
    RATE  = 0U,
    BURST = 1U,

    NF_PARAMETERS_COUNT
};

}  // namespace engines
}  // namespace brain

EthernetStatistics::EthernetStatistics(CounterManagerPtr     debugCounters,
                                       DiagnosticsManagerPtr diagnosticsManager,
                                       ConfigurationPtr      config)
  : m_linkUtilizationMonitoringOn{diagnosticsManager->GetFeatureFlag(
      brain::adaptation_values_names::AdaptationId::LINK_UTILIZATION_MONITORING_ON)}
  , m_broadcastMulticastRatesMonitoringOn{diagnosticsManager->GetFeatureFlag(
        brain::adaptation_values_names::AdaptationId::BROADCAST_MULTICAST_RATES_MONITORING_ON)}
  , m_discardedFramesMonitoringOn{diagnosticsManager->GetFeatureFlag(
        brain::adaptation_values_names::AdaptationId::DISCARDED_FRAMES_MONITORING_ON)}
{
    initCounters(debugCounters);
    std::vector<uint32_t> portDataBucketParams;
    if (config
        && config->GetValue(brain::config_keys::HCP5_SWITCH_TRAFIC_MONITORING_TOKEN_BUCKET_PARAMS,
                            portDataBucketParams))
    {
        if (portDataBucketParams.size() == NF_PARAMETERS_COUNT)
        {
            m_bucketThresholdRate = portDataBucketParams[BurstConfigParamIndexes::RATE];
            m_bucketMaxBurst      = portDataBucketParams[BurstConfigParamIndexes::BURST];
        }
        else
        {
            LOG_ERROR << "Invalid number of variables in hcp5_switch_traffic_monitoring_token_bucket_params config key "
                      << LOG_NOOP;
        }
    }
}

void
EthernetStatistics::initCounters(CounterManagerPtr debugCounters)
{
    if (debugCounters)
    {
        m_someIpStats.linkUtilizationAlertCounter
            = debugCounters->CreateCounter(common::counters::warning::LINK_UTILIZATION_THRESHOLD_EXCEEDED_COUNTER_NAME,
                                           EventCounterLevelType::COUNTER_WARNING);

        m_qlahStats.successCounter = debugCounters->CreateCounter(
            common::counters::debug::ETH_ENGINE_PROCESS_SUCCESS_COUNTER_NAME, EventCounterLevelType::COUNTER_DEBUG);
        m_qlahStats.denialOfServiceAlertCounter = debugCounters->CreateCounter(
            common::counters::warning::DENIAL_OF_SERVICE_ALERT_COUNTER_NAME, EventCounterLevelType::COUNTER_WARNING);

        m_qlahStats.unknownProtocolFramesCounter = debugCounters->CreateCounterWithTs(
            common::counters::errors::UNKNOWN_PROTOCOL_FRAMES_COUNTER, EventCounterLevelType::COUNTER_ERROR);
        m_qlahStats.illegalVlanDropCounter = debugCounters->CreateCounterWithTs(
            common::counters::errors::ILLEGAL_VLAN_DROP_COUNTER, EventCounterLevelType::COUNTER_ERROR);
        m_qlahStats.illegalIpDropCounter = debugCounters->CreateCounterWithTs(
            common::counters::errors::ILLEGAL_IP_DROP_COUNTER, EventCounterLevelType::COUNTER_ERROR);
        m_qlahStats.ethMonitorTableEntriesCounter
            = debugCounters->CreateCounter(common::counters::ETH_MONITORING_TABLE_ENTRIES_COUNTER_NAME);
    }
}

bool
EthernetStatistics::HandleEvent(SecurityEventsEngine*                   engine,
                                SecurityEventSensorData const&          sd,
                                SECEV_SWITCH_DATAFLOW_STATISTICS const* event)
{
    auto const                             eventFrame       = sd.GetEventFrame();
    auto const                             idsMInstanceId   = eventFrame.idsMInstanceID;
    auto const                             sensorInstanceId = eventFrame.sensorInstanceID;
    DataflowStatisticsEngineKeyEntry const entry{idsMInstanceId, sensorInstanceId, event->uid};
    updateEthernetSwitchesCountersTable(entry, event);
    return updateLinkUtilizationHistogramTable(engine, entry, sd, event);
}

void
EthernetStatistics::updateEthernetSwitchesCountersTable(DataflowStatisticsEngineKeyEntry const& entry,
                                                        SECEV_SWITCH_DATAFLOW_STATISTICS const* event)
{
    static uint32_t constexpr EMPTY_FIELD = 0xFFFFFFFF;

    if (0U == m_someIpStats.ethernetSwitchesCountersTable.count(entry))
    {
        m_someIpStats.ethernetSwitchesCountersTable[entry] = {};
    }

    auto updateField = [](uint32_t& tableField, uint32_t field) {
        if (field != EMPTY_FIELD)
        {
            if (tableField + field < std::numeric_limits<uint32_t>::max())
            {
                tableField += field;
            }
            else
            {
                LOG_WARNING << "Possible overflow when adding the value of field to the table" << LOG_NOOP;
            }
        }
        else
        {
            tableField = field;
        }
    };

    auto& tableData = m_someIpStats.ethernetSwitchesCountersTable[entry];
    updateField(tableData.dropPktBufOverrung, event->dropPktBufOverrung);
    updateField(tableData.dropPktCrC, event->dropPktCrC);
    updateField(tableData.oversizePkt, event->oversizePkt);
    updateField(tableData.undersizePkt, event->undersizePkt);
    updateField(tableData.algnmtErr, event->algnmtErr);
    LOG_DEBUG << "Updated EthernetSwitchesCountersTable:idsMInstanceId=" << entry.GetIdsMInstanceId()
              << ",sensorInstanceId=" << entry.GetSensorInstanceId()
              << ",dropPktBufOverrung=" << event->dropPktBufOverrung << ",dropPktCrC=" << event->dropPktCrC
              << ",oversizePkt=" << event->oversizePkt << ",undersizePkt=" << event->undersizePkt
              << ",algnmtErr=" << event->algnmtErr << LOG_NOOP;
}

bool
EthernetStatistics::updateLinkUtilizationHistogramTable(SecurityEventsEngine*                              engine,
                                                        DataflowStatisticsEngineKeyEntry const&            entry,
                                                        brain::sensor_data::SecurityEventSensorData const& sd,
                                                        SECEV_SWITCH_DATAFLOW_STATISTICS const*            event)
{
    auto dataRateMbps = [](uint64_t bytes) {
        // use floor in order to make sure the input value stays in the correct bin in ScalarHistogram
        return static_cast<int64_t>(std::floor(BytesToBits(bytes) / MEGA));
    };
    auto convertToUint64 = [](uint32_t lowerHalf, uint32_t upperHalf) {
        return (static_cast<uint64_t>(upperHalf) << 32) | lowerHalf;
    };

    auto const ifOutOctets = convertToUint64(event->ifOutOctets1, event->ifOutOctets2);
    auto const ifInOctets  = convertToUint64(event->ifInOctets1, event->ifInOctets2);

    double                              thresholdRate{};
    ScalarHistogram::BinIntervalsVector temporaryRatesBins;
    static constexpr double             DATA_RATE_THRESHOLD_MB{50.0};
    static constexpr double             HIGH_SPEED_DATA_RATE_THRESHOLD_MB{500.0};

    if (CONMOD_IDSM == entry.GetIdsMInstanceId())
    {
        temporaryRatesBins = SomeIpStats::highSpeedOctetsRatesBins;
        thresholdRate      = HIGH_SPEED_DATA_RATE_THRESHOLD_MB;
    }
    else
    {
        thresholdRate      = DATA_RATE_THRESHOLD_MB;
        temporaryRatesBins = SomeIpStats::octetsRatesBins;
    }

    auto const it = m_someIpStats.linkUtilizationHistogramTable.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(entry),
        std::forward_as_tuple(
            std::make_tuple(ScalarHistogram(temporaryRatesBins), ScalarHistogram(temporaryRatesBins))));

    if (!common::types::IsMapSizeExceeded(m_someIpStats.linkUtilizationHistogramTable, it))
    {
        LOG_DEBUG << "Updated LinkUtilizationHistogramTable:idsMInstanceId=" << entry.GetIdsMInstanceId()
                  << ",sensorInstanceId=" << entry.GetSensorInstanceId() << ",ifOutOctets1=" << event->ifOutOctets1
                  << ",ifOutOctets2=" << event->ifOutOctets2 << ",ifInOctets1=" << event->ifInOctets1
                  << ",ifInOctets2=" << event->ifInOctets2 << LOG_NOOP;

        double matchedInterval{};
        for (int dir = 0; dir < LINK_DIRECTION_COUNT; ++dir)
        {
            uint64_t         ifOctets = 0U;
            ScalarHistogram* hist     = nullptr;
            switch (dir)
            {
            case LINK_OUT_DIRECTION:
                ifOctets = ifOutOctets;
                hist     = &std::get<LINK_OUT_DIRECTION>(it.first->second);
                break;
            case LINK_IN_DIRECTION:
                ifOctets = ifInOctets;
                hist     = &std::get<LINK_IN_DIRECTION>(it.first->second);
                break;
            default:
                LOG_WARNING << "Unknown traffic direction " << dir << LOG_NOOP;
                return false;
            }
            auto const ok
                = hist->Update(sd.GetTimestamp(), static_cast<double>(dataRateMbps(ifOctets)), 1U, matchedInterval);
            if (!ok)
            {
                LOG_WARNING << "Link utilization histogram for " << dir << " traffic cannot be updated" << LOG_NOOP;
                continue;
            }

            if (matchedInterval > thresholdRate)
            {
                auto const rc = engine->SendLinkUtilizationAlert(entry, sd, dir);
                if (rc)
                {
                    common::counters::IncreaseCounter(m_someIpStats.linkUtilizationAlertCounter);
                }
            }
        }
    }

    return true;
}

void
EthernetStatistics::ClearSomeIpStats()
{
    m_someIpStats.linkUtilizationHistogramTable.clear();
    m_someIpStats.ethernetSwitchesCountersTable.clear();

    m_someIpStats.linkUtilizationHistogramTable.ResetFailedAllocations();
    m_someIpStats.ethernetSwitchesCountersTable.ResetFailedAllocations();

    m_qlahStats.portsData.ResetFailedAllocations();
}

bool
EthernetStatistics::HandleEvent(EthEngine* engine, EthSensorData const& ethSD)
{
    std::string const& portId = ethSD.GetID();

    const auto insertion
        = m_qlahStats.portsData.emplace(std::piecewise_construct,
                                        std::forward_as_tuple(portId),
                                        std::forward_as_tuple(m_bucketThresholdRate, m_bucketMaxBurst));
    if (common::types::IsMapSizeExceeded(m_qlahStats.portsData, insertion))
    {
        return false;
    }

    auto& portData = insertion.first->second;

    // Diag Adaptations - 0x7704 - DiscardedFramesMonitoringOn
    if (m_discardedFramesMonitoringOn)
    {
        updateDiscardedFrameValues(ethSD, portData);
    }

    uint64_t const timeStamp = ethSD.GetTimestamp();

    cm::optional<uint64_t> const& ifInOctetsValue                     = ethSD.GetIfInOctetsCounter();
    cm::optional<uint64_t> const& etherStatsUndersizePktsValue        = ethSD.GetEtherStatsUndersizePkts();
    cm::optional<uint64_t> const& etherStatsPkts64OctetsValue         = ethSD.GetEtherStatsPkts64Octets();
    cm::optional<uint64_t> const& etherStatsPkts65to127OctetsValue    = ethSD.GetEtherStatsPkts65to127Octets();
    cm::optional<uint64_t> const& etherStatsPkts128to255OctetsValue   = ethSD.GetEtherStatsPkts128to255Octets();
    cm::optional<uint64_t> const& etherStatsPkts256to511OctetsValue   = ethSD.GetEtherStatsPkts256to511Octets();
    cm::optional<uint64_t> const& etherStatsPkts512to1023OctetsValue  = ethSD.GetEtherStatsPkts512to1023Octets();
    cm::optional<uint64_t> const& etherStatsPkts1024to1518OctetsValue = ethSD.GetEtherStatsPkts1024to1518Octets();
    cm::optional<uint64_t> const& etherStatsOversizePktsValue         = ethSD.GetEtherStatsOversizePkts();
    cm::optional<uint32_t> const& ifOutMulticastPktsValue             = ethSD.GetIfOutMulticastPktsCounter();
    cm::optional<uint32_t> const& ifOutBroadcastPktsValue             = ethSD.GetIfOutBroadcastPktsCounter();
    cm::optional<bool> const&     diagFilter                          = ethSD.GetDiagFilter();

    portData.addTimeStamp(timeStamp);

    if (diagFilter.has_value())
    {
        portData.m_isMonitoringDoS = !*diagFilter;
    }

    if (ifInOctetsValue.has_value() && (*ifInOctetsValue > 0))
    {
        LOG_DEBUG << "ifInOctetsValue value: " << *ifInOctetsValue << LOG_NOOP;
        if (*ifInOctetsValue < *portData.m_ifInOctetsValue)
        {
            LOG_WARNING << "ifInOctetsValue difference is negative" << LOG_NOOP;
        }
        else
        {
            uint64_t const byteDiff = *ifInOctetsValue - *portData.m_ifInOctetsValue;
            updateInOctetsHistograms(timeStamp, *ifInOctetsValue, portId);
            portData.m_ifInOctetsValue = *ifInOctetsValue;

            static const uint64_t DEFAULT_LINK_CAPACITY{1000U * MEGA};
            uint64_t linkCapacity{DEFAULT_LINK_CAPACITY};
            static const std::unordered_map<std::string, uint64_t> SWITCH_PORT_LINK_CAPACITY_MAPPING{
                {"switch_0_port_0", 100U * MEGA},   {"switch_0_port_1", 100U * MEGA},
                {"switch_0_port_2", 1000U * MEGA},  {"switch_0_port_3", 1000U * MEGA},
                {"switch_0_port_4", 1000U * MEGA},  {"switch_0_port_5", 1000U * MEGA},
                {"switch_0_port_6", 1000U * MEGA},  {"switch_0_port_7", 1000U * MEGA},
                {"switch_1_port_0", 100U * MEGA},   {"switch_1_port_1", 100U * MEGA},
                {"switch_1_port_2", 100U * MEGA},   {"switch_1_port_3", 100U * MEGA},
                {"switch_1_port_4", 100U * MEGA},   {"switch_1_port_5", 100U * MEGA},
                {"switch_1_port_6", 1000U * MEGA},  {"switch_1_port_7", 1000U * MEGA},
                {"switch_1_port_8", 1000U * MEGA},  {"switch_1_port_9", 1000U * MEGA},
                {"switch_1_port_10", 1000U * MEGA}, {"switch_1_port_11", 5000U * MEGA},
                {"switch_1_port_12", 100U * MEGA},  {"switch_1_port_13", 100U * MEGA},
                {"switch_1_port_14", 100U * MEGA},  {"switch_1_port_15", 1000U * MEGA}};


            auto     linkCapacityIt = SWITCH_PORT_LINK_CAPACITY_MAPPING.find(ethSD.GetID());
            if (SWITCH_PORT_LINK_CAPACITY_MAPPING.end() != linkCapacityIt)
            {
                linkCapacity = linkCapacityIt->second;
            }
            else
            {
                LOG_DEBUG << "missing link capacity key for " << ethSD.GetID() << LOG_NOOP;
            }

            const auto   dataRateInBits = BytesToBits(byteDiff);
            const double linkUtilizationRatePercentage
                = round((static_cast<double>(dataRateInBits) / static_cast<double>(linkCapacity)) * 100.0);

            // Diag Adaptations - 0x7704 - LinkUtilizationMonitoringOn
            if (m_linkUtilizationMonitoringOn)
            {
                double matchedInterval{};
                bool   isUpdateSucceed = portData.m_linkUtilizationInHistogram.Update(
                    timeStamp, linkUtilizationRatePercentage, 1U, matchedInterval);
                if (!isUpdateSucceed)
                {
                    LOG_WARNING << "Link utilization in histogram update problem for port: " << portId.c_str()
                                << LOG_NOOP;
                }
            }
            if (isThresholdExceeded(timeStamp, byteDiff, portData) && portData.m_isMonitoringDoS)
            {
                common::counters::IncreaseCounter(m_qlahStats.denialOfServiceAlertCounter);
                m_qlahStats.alertPortId = portId;
                engine->CreateDosAlert();
                portData.m_tokenBucket.Reset();
            }
        }
    }

    if (etherStatsUndersizePktsValue.has_value() && (*etherStatsUndersizePktsValue > 0U))
    {
        LOG_DEBUG << "etherStatsUndersizePktsValue value: " << *etherStatsUndersizePktsValue << LOG_NOOP;
        portData.m_etherStatsUndersizePktsValue = *etherStatsUndersizePktsValue;
    }

    if (etherStatsPkts64OctetsValue.has_value() && (*etherStatsPkts64OctetsValue > 0U))
    {
        LOG_DEBUG << "etherStatsPkts64OctetsValue value: " << *etherStatsPkts64OctetsValue << LOG_NOOP;
        portData.m_etherStatsPkts64OctetsValue = *etherStatsPkts64OctetsValue;
    }

    if (etherStatsPkts65to127OctetsValue.has_value() && (*etherStatsPkts65to127OctetsValue > 0U))
    {
        LOG_DEBUG << "etherStatsPkts65to127OctetsValue value: " << *etherStatsPkts65to127OctetsValue << LOG_NOOP;
        portData.m_etherStatsPkts65to127OctetsValue = *etherStatsPkts65to127OctetsValue;
    }

    if (etherStatsPkts128to255OctetsValue.has_value() && (*etherStatsPkts128to255OctetsValue > 0U))
    {
        LOG_DEBUG << "etherStatsPkts128to255OctetsValue value: " << *etherStatsPkts128to255OctetsValue << LOG_NOOP;
        portData.m_etherStatsPkts128to255OctetsValue = *etherStatsPkts128to255OctetsValue;
    }

    if (etherStatsPkts256to511OctetsValue.has_value() && (*etherStatsPkts256to511OctetsValue > 0U))
    {
        LOG_DEBUG << "etherStatsPkts256to511OctetsValue value: " << *etherStatsPkts256to511OctetsValue << LOG_NOOP;
        portData.m_etherStatsPkts256to511OctetsValue = *etherStatsPkts256to511OctetsValue;
    }

    if (etherStatsPkts512to1023OctetsValue.has_value() && (*etherStatsPkts512to1023OctetsValue > 0U))
    {
        LOG_DEBUG << "etherStatsPkts512to1023OctetsValue value: " << *etherStatsPkts512to1023OctetsValue << LOG_NOOP;
        portData.m_etherStatsPkts512to1023OctetsValue = *etherStatsPkts512to1023OctetsValue;
    }

    if (etherStatsPkts1024to1518OctetsValue.has_value() && (*etherStatsPkts1024to1518OctetsValue > 0U))
    {
        LOG_DEBUG << "etherStatsPkts1024to1518OctetsValue value: " << *etherStatsPkts1024to1518OctetsValue << LOG_NOOP;
        portData.m_etherStatsPkts1024to1518OctetsValue = *etherStatsPkts1024to1518OctetsValue;
    }

    if (etherStatsOversizePktsValue.has_value() && (*etherStatsOversizePktsValue > 0U))
    {
        LOG_DEBUG << "etherStatsOversizePktsValue value: " << *etherStatsOversizePktsValue << LOG_NOOP;
        portData.m_etherStatsOversizePktsValue = *etherStatsOversizePktsValue;
    }

    uint64_t broadcastMulticastCounter{};
    if ((ifOutMulticastPktsValue.has_value()) && (*ifOutMulticastPktsValue > 0U))
    {
        LOG_DEBUG << "ifOutMulticastPktsValue value: " << *ifOutMulticastPktsValue << LOG_NOOP;
        broadcastMulticastCounter += (*ifOutMulticastPktsValue);
    }

    if ((ifOutBroadcastPktsValue.has_value()) && (*ifOutBroadcastPktsValue > 0U))
    {
        LOG_DEBUG << "ifOutBroadcastPktsValue value: " << *ifOutBroadcastPktsValue << LOG_NOOP;
        broadcastMulticastCounter += (*ifOutBroadcastPktsValue);
    }

    if (0U < broadcastMulticastCounter)
    {
        LOG_DEBUG << "Counter broadcastMulticastCounter value: " << broadcastMulticastCounter << LOG_NOOP;

        // Diag Adaptations - 0x7704 - BroadcastMulticastRatesMonitoringOn
        if (m_broadcastMulticastRatesMonitoringOn)
        {
            updateBroadcastMulticastHistograms(timeStamp, broadcastMulticastCounter, portId);
        }
    }
    return true;
}

void
EthernetStatistics::ClearQlahStats()
{
    for (auto& portData : m_qlahStats.portsData)
    {
        portData.second.m_discardedFramesValue       = 0;
        portData.second.m_unknownProtocolFramesValue = 0;
        portData.second.m_illegalVlanDropValue       = 0;
        portData.second.m_illegalIpDropValue         = 0;
        portData.second.m_vlanEgressDropValue        = 0;
        portData.second.m_vlanIngressDropValue       = 0;
        portData.second.m_vlanLookupMissDropValue    = 0;
        portData.second.m_aclLookupMissDropValue     = 0;
        portData.second.m_firstSeenTimeStamp         = 0;
        portData.second.m_lastSeenTimeStamp          = 0;
    }

    m_qlahStats.portsData.ResetFailedAllocations();

    m_qlahStats.inOctetsHistograms.clear();
}

void
EthernetStatistics::updateDiscardedFrameValues(EthSensorData const& ethSD, PortData& portData)
{
    uint64_t const timeStamp = ethSD.GetTimestamp();

    cm::optional<uint64_t> const& discardedFramesValue              = ethSD.GetDiscardedFramesCounter();
    cm::optional<uint64_t> const& unknownProtocolDroppedFramesValue = ethSD.GetUnknownProtocolDroppedFramesCounter();
    cm::optional<uint64_t> const& illegalVLANDroppedFramesValue     = ethSD.GetIllegalVLANDroppedFramesCounter();
    cm::optional<uint64_t> const& illegalIPDroppedFramesValue       = ethSD.GetIllegalIPDroppedFramesCounter();
    cm::optional<uint64_t> const& vlanIngressDroppedFramesValue     = ethSD.GetVLANIngressDroppedFramesCounter();
    cm::optional<uint64_t> const& vlanEgressDroppedFramesValue      = ethSD.GetVLANEgressDroppedFramesCounter();
    cm::optional<uint64_t> const& vlanLookupDroppedFramesValue      = ethSD.GetVLANLookupDroppedFramesCounter();
    cm::optional<uint64_t> const& aclLookupDroppedFramesValue       = ethSD.GetACLLookupDroppedFramesCounter();

    if (discardedFramesValue.has_value() && (*discardedFramesValue > 0U))
    {
        LOG_DEBUG << "discardedFramesValue value: " << *discardedFramesValue << LOG_NOOP;
        portData.m_discardedFramesValue = *discardedFramesValue;
    }

    if (unknownProtocolDroppedFramesValue.has_value() && (*unknownProtocolDroppedFramesValue > 0U))
    {
        LOG_DEBUG << "unknownProtocolDroppedFramesValue value: " << *unknownProtocolDroppedFramesValue << LOG_NOOP;
        portData.m_unknownProtocolFramesValue = *unknownProtocolDroppedFramesValue;
        m_qlahStats.unknownProtocolFramesCounter->CountEvent(timeStamp, *unknownProtocolDroppedFramesValue);
        
        if (m_ethUnknownProtocolAlert)
        {
            m_ethUnknownProtocolAlert->Update(ethSD.GetID(), *unknownProtocolDroppedFramesValue);
        }
    }

    if (illegalVLANDroppedFramesValue.has_value() && (*illegalVLANDroppedFramesValue > 0U))
    {
        LOG_DEBUG << "illegalVLANDroppedFramesValue value: " << *illegalVLANDroppedFramesValue << LOG_NOOP;
        portData.m_illegalVlanDropValue = *illegalVLANDroppedFramesValue;
        m_qlahStats.illegalVlanDropCounter->CountEvent(timeStamp, *illegalVLANDroppedFramesValue);

        if (m_ethIllegalVlanFramesAlert)
        {
            m_ethIllegalVlanFramesAlert->Update(ethSD.GetID(), *illegalVLANDroppedFramesValue);
        }
    }

    if (illegalIPDroppedFramesValue.has_value() && (*illegalIPDroppedFramesValue > 0U))
    {
        LOG_DEBUG << "illegalIPDroppedFramesValue value: " << *illegalIPDroppedFramesValue << LOG_NOOP;
        portData.m_illegalIpDropValue = *illegalIPDroppedFramesValue;
        m_qlahStats.illegalIpDropCounter->CountEvent(timeStamp, *illegalIPDroppedFramesValue);
    }

    if (vlanIngressDroppedFramesValue.has_value() && (*vlanIngressDroppedFramesValue > 0U))
    {
        LOG_DEBUG << "vlanIngressDroppedFramesValue value: " << *vlanIngressDroppedFramesValue << LOG_NOOP;
        portData.m_vlanIngressDropValue = *vlanIngressDroppedFramesValue;
    }

    if (vlanEgressDroppedFramesValue.has_value() && (*vlanEgressDroppedFramesValue > 0U))
    {
        LOG_DEBUG << "vlanEgressDroppedFramesValue value: " << *vlanEgressDroppedFramesValue << LOG_NOOP;
        portData.m_vlanEgressDropValue = *vlanEgressDroppedFramesValue;
    }

    if (vlanLookupDroppedFramesValue.has_value() && (*vlanLookupDroppedFramesValue > 0U))
    {
        LOG_DEBUG << "vlanLookupDroppedFramesValue value: " << *vlanLookupDroppedFramesValue << LOG_NOOP;
        portData.m_vlanLookupMissDropValue = *vlanLookupDroppedFramesValue;
    }

    if (aclLookupDroppedFramesValue.has_value() && (*aclLookupDroppedFramesValue > 0U))
    {
        LOG_DEBUG << "aclLookupDroppedFramesValue value: " << *aclLookupDroppedFramesValue << LOG_NOOP;
        portData.m_aclLookupMissDropValue = *aclLookupDroppedFramesValue;
    }
}

void
EthernetStatistics::updateInOctetsHistograms(uint64_t const     timeStamp,
                                             uint64_t const     inOctetsCounter,
                                             std::string const& id)
{
    uint64_t ifInOctetsCurrentCounter;

    auto const it = m_qlahStats.inOctetsHistograms.find(id);
    if (m_qlahStats.inOctetsHistograms.end() == it)
    {
        m_qlahStats.inOctetsHistograms[id]
            = {inOctetsCounter, std::make_unique<RateHistogram>(m_qlahStats.octetsRatesBins, brain::histogram::MAX_BURST)};
        ifInOctetsCurrentCounter = inOctetsCounter;
        common::counters::IncreaseCounter(m_qlahStats.ethMonitorTableEntriesCounter);
    }
    else
    {
        if (inOctetsCounter >= it->second.first)
        {
            ifInOctetsCurrentCounter = (inOctetsCounter - it->second.first);
        }
        else
        {
            ifInOctetsCurrentCounter = inOctetsCounter;
            LOG_WARNING << "The current InOctets counter is smaller than the previous one" << LOG_NOOP;
        }
    }

    if (ifInOctetsCurrentCounter > (std::numeric_limits<uint64_t>::max() / CHAR_BIT))
    {
        ifInOctetsCurrentCounter = std::numeric_limits<uint64_t>::max();
        LOG_WARNING << "The value of the current InOctets in bits, exceeds the max value of uint64_t" << LOG_NOOP;
    }
    else
    {
        ifInOctetsCurrentCounter *= CHAR_BIT;
    }
    if (!m_qlahStats.inOctetsHistograms[id].second->AddData(common::MS_TO_S(timeStamp), ifInOctetsCurrentCounter))
    {
        common::counters::IncreaseCounter(m_qlahStats.inOctetsHistogramFailedAddDataCounter);
        LOG_ERROR << "Failed adding to in octets histogram with id = " << id << LOG_NOOP;
    }
    else
    {
        LOG_DEBUG << "in octets histogram with id=" << id << " was updated" << LOG_NOOP;
        m_qlahStats.inOctetsHistograms[id].first = inOctetsCounter;
    }
}

bool
EthernetStatistics::isThresholdExceeded(uint64_t const timeStamp, uint64_t const byteDiff, PortData& portData)
{
    return !portData.m_tokenBucket.Update(common::MS_TO_S(timeStamp), byteDiff);
}

void
EthernetStatistics::updateBroadcastMulticastHistograms(uint64_t           timeStamp,
                                                       uint64_t           broadcastMulticastCounter,
                                                       std::string const& id)
{
    uint64_t   broadcastMulticastCurrentCounter;
    auto const it = m_qlahStats.broadcastMulticastHistograms.find(id);
    if (m_qlahStats.broadcastMulticastHistograms.end() == it)
    {
        m_qlahStats.broadcastMulticastHistograms[id]
            = {broadcastMulticastCounter,
               std::make_unique<RateHistogram>(m_qlahStats.broadcastMulticastRatesBins, brain::histogram::MAX_BURST)};
        broadcastMulticastCurrentCounter = broadcastMulticastCounter;
        common::counters::IncreaseCounter(m_qlahStats.ethMonitorTableEntriesCounter);
    }
    else
    {
        if (broadcastMulticastCounter >= it->second.first)
        {
            broadcastMulticastCurrentCounter = (broadcastMulticastCounter - it->second.first);
        }
        else
        {
            LOG_WARNING << "The current out Broadcast-Multicast counter is smaller than the previous one" << LOG_NOOP;
            broadcastMulticastCurrentCounter = broadcastMulticastCounter;
        }
    }

    if (!m_qlahStats.broadcastMulticastHistograms[id].second->AddData(common::MS_TO_S(timeStamp),
                                                                      broadcastMulticastCurrentCounter))
    {
        common::counters::IncreaseCounter(m_qlahStats.outBroadcastHistogramFailedAddDataCounter);
        LOG_ERROR << "Failed adding to out broadcast-multicast histogram with id = " << id << LOG_NOOP;
    }
    else
    {
        LOG_DEBUG << "Out broadcast-multicast histogram with id=" << id << " was updated" << LOG_NOOP;
        m_qlahStats.broadcastMulticastHistograms[id].first = broadcastMulticastCounter;
    }
}

bool
EthernetStatistics::GetInOctetsHistogramsValues(
    std::unordered_map<std::string, std::shared_ptr<HistogramValues>>& histogramsData) const
{
    histogramsData.clear();

    for (auto const& histogram : m_qlahStats.inOctetsHistograms)
    {
        RateHistogram::BinDataVector histogramData;
        uint64_t                     firstHistogramTs{};
        uint64_t                     lastHistogramTs{};

        if (!histogram.second.second->GetHistogramValues(histogramData, firstHistogramTs, lastHistogramTs))
        {
            LOG_ERROR << "Failed to get data of histogram with id = " << histogram.first << LOG_NOOP;
            return false;
        }

        HistogramValues const data{firstHistogramTs, lastHistogramTs, histogramData};
        histogramsData[histogram.first] = std::make_shared<HistogramValues>(data);
    }
    return true;
}

void
EthernetStatistics::ClearLinkUtilization()
{
    m_qlahStats.alertPortId.clear();
}

void
EthernetStatistics::ClearBroadcastMulticast()
{
    m_qlahStats.broadcastMulticastHistograms.clear();
}
