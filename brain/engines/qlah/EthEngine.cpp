/**
 * @file
 * @brief     A rule engine for the Ethernet QLAH Sensor
 */
#include "EthEngine.hpp"
#include "brain/sensor_data/qlah/EthSensorData.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "brain/utils/UtilsConstants.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "autogen/nanopb/NanoPbInclude.hpp"
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "brain/config/AlertEventsNames.hpp"
#include "brain/engines/security_events/NanoPbMacros.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"

#ifndef SSP_PLATFORM
#include "brain/diagnostics/PPE/AdaptationValuesConstants.hpp"
#endif

#include <cmath>

using brain::engines::qlah::EthEngine;
using brain::engines::ReturnCode;
using brain::sensor_data::EthSensorData;
using brain::histogram::RateHistogram;
using brain::histogram::ScalarHistogram;
using namespace brain::sender_events;

namespace brain
{
namespace engines
{
namespace qlah
{
using EventStatus           = histogram_lib::IRatePolicer::EventStatus;
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;
using Message               = brain::messageRepository::MessageRepositoryInterface::Message;
}  // namespace qlah
}  // namespace engines
}  // namespace brain

static ScalarHistogram::BinDataVector
initLinkUtilizationInBinDataVector() noexcept
{
    return ScalarHistogram::BinDataVector{};
}
ScalarHistogram::BinDataVector EthEngine::m_linkUtilizationInBinDataVector = initLinkUtilizationInBinDataVector();

EthEngine::EthEngine(CounterManagerPtr                                 debugCounters,
                     MessageRepositoryPtr                              msgRepository,
                     EthernetStatisticsPtr                             ethStats,
                     EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                     EventNoiseFilterPtr                               eventNoiseFilter,
                     events::EventPriority                             priority)
  : EngineEventSender(priority, msgRepository, reportSerializer, eventNoiseFilter)
  , m_ethStats(ethStats)
{
    if (debugCounters)
    {
        m_processSuccessCounter = debugCounters->GetCounter(common::counters::debug::ETH_ENGINE_PROCESS_SUCCESS_COUNTER_NAME);
        m_failedCounter = debugCounters->CreateCounter(common::counters::warning::ETH_ENGINE_FAILED_PROCESS_COUNTER_NAME, EventCounterLevelType::COUNTER_WARNING);
        m_filteredEventCounter = debugCounters->CreateCounter(common::counters::warning::FILTERED_OUT_DOS_ALERT_BY_EVENT_NOISE_FILTER_COUNTER_NAME, EventCounterLevelType::COUNTER_WARNING);
    }
}

ReturnCode EthEngine::processInternal(UPSensorData sd)
{
    try
    {
        auto const& ethSD = dynamic_cast<EthSensorData const&>(*sd);
        LOG_VERBOSE << "Processing QLAH Eth engine - began processing EthSensorData" << LOG_NOOP;
        auto res = m_ethStats->HandleEvent(this, ethSD);
        common::counters::IncreaseCounter(m_processSuccessCounter);
        return (res ? ReturnCode::Success : ReturnCode::FailedError);
    }
    catch(std::bad_cast const& /*e*/)
    {
        LOG_ERROR << "Processing QLAH Eth engine - sd cannot be casted to EthSensorData" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCounter);
        return ReturnCode::CastError;
    }
}

bool EthEngine::FetchContents(com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringTable& ethMonitoringTableBuffer)
{
    ethDiscardedFramesMonitoringHistogramsHandler(ethMonitoringTableBuffer);
    ethMonitoringTableBuffer.ethMonitoringData.funcs.encode = &serializeEthMonitoringData;
    ethMonitoringTableBuffer.ethMonitoringData.arg = const_cast<common::types::BoundedUnorderedMap<std::string, PortData>*>(m_ethStats->GetPortsData());
    ethMonitoringTableBuffer.creationTimeStamp = common::Time::GetCurrentTimeSec();

    return true;
}

void
EthEngine::ethDiscardedFramesMonitoringHistogramsHandler(
    com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringTable& ethMonitoringTableBuffer)
{
    if (m_ethStats->GetInOctetsHistogramsValues(m_inOctetHistogramsMap))
    {
        ethMonitoringTableBuffer.inOctetsHistogramsTable.funcs.encode = &encodeHistogramsTable;
        ethMonitoringTableBuffer.inOctetsHistogramsTable.arg          = static_cast<void*>(&m_inOctetHistogramsMap);
    }
}

bool EthEngine::encodeHistogramsTable(pb_ostream_t* stream, pb_field_t const* fields, void* const* arg)
{
    auto const& histogramsMap
        = **reinterpret_cast<std::unordered_map<std::string, std::shared_ptr<EthEngine::HistogramValues>>* const*>(arg);

    for (auto const& histogramData : histogramsMap)
    {
        if (nullptr == histogramData.second)
        {
            return false;
        }
        com_vwg_connect_ids_idsperiodicreport_v1_FloatHistogramsTable floatHistogramsTable
            = com_vwg_connect_ids_idsperiodicreport_v1_FloatHistogramsTable_init_default;
        floatHistogramsTable.id                     = common::nanopb::CreateEncodingCallback(histogramData.first);
        floatHistogramsTable.has_floatHistogramData = true;
        floatHistogramsTable.floatHistogramData.firstSeenTimeStamp   = histogramData.second->firstTimestamp;
        floatHistogramsTable.floatHistogramData.lastSeenTimeStamp    = histogramData.second->lastTimestamp;
        floatHistogramsTable.floatHistogramData.buckets.funcs.encode = &common::nanopb::encoders::EncodeRateHistogram;
        floatHistogramsTable.floatHistogramData.buckets.arg          = static_cast<void*>(&histogramData.second->histogramsData);

        if ((!pb_encode_tag_for_field(stream, fields))
            || (!pb_encode_submessage(
                stream, com_vwg_connect_ids_idsperiodicreport_v1_FloatHistogramsTable_fields, &floatHistogramsTable)))
        {
            return false;
        }
    }

    return true;
}

bool EthEngine::serializeEthMonitoringData(pb_ostream_t* const stream, pb_field_t const* const fields, void* const* arg)
{
    auto* const* portsDataPtr
        = reinterpret_cast<common::types::BoundedUnorderedMap<std::string, PortData>* const*>(arg);
    if ((nullptr == portsDataPtr) || (nullptr == portsDataPtr[0]))
    {
        return false;
    }

    auto& portDataTable = **portsDataPtr;
    for (auto const& portData : portDataTable)
    {
        com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringData ethMonitoringData = com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringData_init_default;
        auto const& data = portData.second;
        createEthMonitoringDataRuleEvaluation(ethMonitoringData, portData.first, data);
        createLinkUtilizationInRuleEvaluation(ethMonitoringData, data.m_linkUtilizationInHistogram);
        if (!pb_encode_tag_for_field(stream, fields)
            || !pb_encode_submessage(
                stream, com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringData_fields, &ethMonitoringData))
        {
            return false;
        }
    }

    return true;
}

void EthEngine::createEthMonitoringDataRuleEvaluation(com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringData& ethMonitoringData,
        std::string const& id,
        PortData const& portData)
{
    ethMonitoringData.id = common::nanopb::CreateEncodingCallback(id);
    ethMonitoringData.firstSeenTimeStamp = portData.m_firstSeenTimeStamp;
    ethMonitoringData.lastSeenTimeStamp = portData.m_lastSeenTimeStamp;
    INIT_NPB_FIELD(ethMonitoringData, discardedFramesValue, portData.m_discardedFramesValue);
    INIT_NPB_FIELD(ethMonitoringData, unknownProtocolFramesValue, portData.m_unknownProtocolFramesValue);
    INIT_NPB_FIELD(ethMonitoringData, illegalVlanDropValue, portData.m_illegalVlanDropValue);
    INIT_NPB_FIELD(ethMonitoringData, illegalIpDropValue, portData.m_illegalIpDropValue);
    INIT_NPB_FIELD(ethMonitoringData, vlanEgressDropValue, portData.m_vlanEgressDropValue);
    INIT_NPB_FIELD(ethMonitoringData, vlanIngressDropValue, portData.m_vlanIngressDropValue);
    INIT_NPB_FIELD(ethMonitoringData, vlanLookupMissDropValue, portData.m_vlanLookupMissDropValue);
    INIT_NPB_FIELD(ethMonitoringData, aclLookupMissDropValue, portData.m_aclLookupMissDropValue);
    INIT_NPB_FIELD(ethMonitoringData, etherStatsUndersizePktsValue, portData.m_etherStatsUndersizePktsValue);
    INIT_NPB_FIELD(ethMonitoringData, etherStatsPkts64OctetsValue, portData.m_etherStatsPkts64OctetsValue);
    INIT_NPB_FIELD(ethMonitoringData, etherStatsPkts65to127OctetsValue, portData.m_etherStatsPkts65to127OctetsValue);
    INIT_NPB_FIELD(ethMonitoringData, etherStatsPkts128to255OctetsValue, portData.m_etherStatsPkts128to255OctetsValue);
    INIT_NPB_FIELD(ethMonitoringData, etherStatsPkts256to511OctetsValue, portData.m_etherStatsPkts256to511OctetsValue);
    INIT_NPB_FIELD(ethMonitoringData, etherStatsPkts512to1023OctetsValue, portData.m_etherStatsPkts512to1023OctetsValue);
    INIT_NPB_FIELD(ethMonitoringData, etherStatsPkts1024to1518OctetsValue, portData.m_etherStatsPkts1024to1518OctetsValue);
    INIT_NPB_FIELD(ethMonitoringData, etherStatsOversizePktsValue, portData.m_etherStatsOversizePktsValue);
}

void EthEngine::createLinkUtilizationInRuleEvaluation(com_vwg_connect_ids_idsperiodicreport_v1_EthMonitoringData& ethMonitoringData, ScalarHistogram const& histogram)
{
    m_linkUtilizationInBinDataVector.clear();
    uint64_t firstHistogramTs{};
    uint64_t lastHistogramTs{};
    if (histogram.GetHistogramValues(m_linkUtilizationInBinDataVector, firstHistogramTs, lastHistogramTs))
    {
        ethMonitoringData.has_linkUtilizationInHistogram = true;
        ethMonitoringData.linkUtilizationInHistogram.firstSeenTimeStamp = firstHistogramTs;
        ethMonitoringData.linkUtilizationInHistogram.lastSeenTimeStamp = lastHistogramTs;
        ethMonitoringData.linkUtilizationInHistogram.buckets.funcs.encode = &common::nanopb::encoders::EncodeScalarFloatingHistogram;
        ethMonitoringData.linkUtilizationInHistogram.buckets.arg = &m_linkUtilizationInBinDataVector;
    }
}

void EthEngine::ClearContents() noexcept
{
    m_ethStats->ClearQlahStats();
}

void EthEngine::CreateDosAlert()
{
    // Handle rule evaluation
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
    std::ignore = createRuleEvaluation(ruleEval);
    auto const status = SendEvent(ruleEval, SensorDataTag::SD_QLAH_ETH, CriticalEventAlert::DenialOfServiceAlert);

    if (EngineEventSender::SendStatus::Success != status)
    {
        common::counters::IncreaseCounter(
            (EngineEventSender::SendStatus::NoiseFilterError == status) ? m_filteredEventCounter : m_failedCounter);
    }

    // Reset histograms after serialization in EncodeNanoPb
    m_ethStats->ClearLinkUtilization();
    m_linkUtilizationInBinDataVector.clear();
}

bool EthEngine::createRuleEvaluation(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval)
{
    com_vwg_connect_ids_idsperiodicreport_v1_DosDetectorReport dosDetectorReport = com_vwg_connect_ids_idsperiodicreport_v1_DosDetectorReport_init_default;
    auto const& alertPortId = m_ethStats->GetAlertPortId();
    dosDetectorReport.id = common::nanopb::CreateEncodingCallback(alertPortId);
    auto const& portData = m_ethStats->GetPortsData()->at(alertPortId);
    dosDetectorReport.has_linkUtilizationHistogram = false;
    uint64_t firstHistogramTs{};
    uint64_t lastHistogramTs{};
    if(portData.m_linkUtilizationInHistogram.GetHistogramValues(m_linkUtilizationInBinDataVector, firstHistogramTs, lastHistogramTs))
    {
        dosDetectorReport.has_linkUtilizationHistogram = true;
        dosDetectorReport.linkUtilizationHistogram.firstSeenTimeStamp = firstHistogramTs;
        dosDetectorReport.linkUtilizationHistogram.lastSeenTimeStamp = lastHistogramTs;
        dosDetectorReport.linkUtilizationHistogram.buckets.funcs.encode = &common::nanopb::encoders::EncodeScalarFloatingHistogram;
        dosDetectorReport.linkUtilizationHistogram.buckets.arg = &m_linkUtilizationInBinDataVector;
    }

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    ruleEval.which_RuleData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_dosDetectorReport_tag);
    ruleEval.RuleData.dosDetectorReport = dosDetectorReport;

    return true;
}
