/**
 * @file
 * @brief     This file contains helper structs and functions for serializing security events data
 .
 */
#ifndef SECURITY_EVENTS_NANOPB_HPP
#define SECURITY_EVENTS_NANOPB_HPP

#include <vector>
#include <string>

#include "autogen/nanopb/NanoPbInclude.hpp"
#include "brain/utils/IpUtils.hpp"
#include "NanoPbMacros.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{
namespace nanopb
{
    
using brain::utils::IpType;

using HistogramBucket = com_vwg_connect_ids_idsperiodicreport_v1_Bucket;
using HistogramFloatBucket = com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket;

using SecurityEventMonitoringDataNPB = com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventMonitoringData;
using SecurityEventsPeriodicMonitoringDataNPB = com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventsMonitoringData;

DECLARE_NPB_TABLE(IpConnectionCounters)

BEGIN_DECLARE_NPB_ENTRY_TABLE(IpDroppedConnections)
    std::vector<uint8_t> SourceIP;
    std::string TransportProtocol;
END_DECLARE_NPB_ENTRY_TABLE(IpDroppedConnections)

BEGIN_DECLARE_NPB_ENTRY_TABLE(HostOsLogRate)
    std::vector<HistogramFloatBucket> Buckets;
END_DECLARE_NPB_ENTRY_TABLE(HostOsLogRate)

BEGIN_DECLARE_NPB_ENTRY_TABLE(ExternalUnsuccessfulConnections)
    std::string ConnectionUnitDeviceName;
END_DECLARE_NPB_ENTRY_TABLE(ExternalUnsuccessfulConnections)

DECLARE_NPB_TABLE(ExternalInterfacesUsageStatistics)

BEGIN_DECLARE_NPB_ENTRY_TABLE(ProcessPerformance)
    std::vector<HistogramBucket> PriviledgedModeCpuUsageBuckets;
    std::vector<HistogramBucket> NonPriviledgedModeCpuUsageBuckets;
    std::vector<HistogramBucket> MemoryUsageBuckets;
    std::string ProcessName;
    std::string SensorIdentifier;
END_DECLARE_NPB_ENTRY_TABLE(ProcessPerformance)

BEGIN_DECLARE_NPB_ENTRY_TABLE(ProcessStartStopCounters)
    std::string AdaptiveAutosarAppName;
    std::string ProcessCommandLine;
END_DECLARE_NPB_ENTRY_TABLE(ProcessStartStopCounters)

BEGIN_DECLARE_NPB_ENTRY_TABLE(IpAnomaliesCounters)
    std::vector<uint8_t> SourceIpAddress;
    std::vector<uint8_t> DestinationIpAddress;
    std::string TransportProtocol;
END_DECLARE_NPB_ENTRY_TABLE(IpAnomaliesCounters)

BEGIN_DECLARE_NPB_ENTRY_TABLE(ServiceRegistry)
    std::string RegisteredService;
    std::string RegisteringApplicationId;
    IpType RegisteringServerIP;
END_DECLARE_NPB_ENTRY_TABLE(ServiceRegistry)

BEGIN_DECLARE_NPB_ENTRY_TABLE(ProcessCrashRate)
    std::string ProcessName;
    std::vector<HistogramFloatBucket> Buckets;
    std::string                       CrashReasonStr;
END_DECLARE_NPB_ENTRY_TABLE(ProcessCrashRate)

BEGIN_DECLARE_NPB_ENTRY_TABLE(ExternalNewHWConnection)
    std::string HardwareIdSerial;
    std::string DeviceSubClasses;
    std::string CalledLriverLibrary;
    std::string HandlingConnectionDriverLibrary;
END_DECLARE_NPB_ENTRY_TABLE(ExternalNewHWConnection)

BEGIN_DECLARE_NPB_ENTRY_TABLE(ExternalDataStorage)
    std::string HardwareIdSerialNumber;
END_DECLARE_NPB_ENTRY_TABLE(ExternalDataStorage)

DECLARE_NPB_TABLE(EthernetServiceInterruption)

BEGIN_DECLARE_NPB_ENTRY_TABLE(LinkUtilization)
    std::vector<HistogramFloatBucket> BucketsOut;
    std::vector<HistogramFloatBucket> BucketsIn;
END_DECLARE_NPB_ENTRY_TABLE(LinkUtilization)

DECLARE_NPB_TABLE(EthernetSwitchesCounters)

DECLARE_NPB_TABLE(DiagnosticEventSequence)

DECLARE_NPB_TABLE(FreshnessValueFailedCounters)

BEGIN_DECLARE_NPB_ENTRY_TABLE(OversizedPacketsHistogram)
    std::vector<HistogramBucket> OversizedPacketsHistogram;
    std::vector<uint8_t> SourceIpAddress;
    std::vector<uint8_t> DestinationIpAddress;
    std::string TransportProtocol;
END_DECLARE_NPB_ENTRY_TABLE(OversizedPacketsHistogram)

DECLARE_NPB_TABLE(SecurityEventsCounters)

BEGIN_DECLARE_NPB_ENTRY_TABLE(DroppedSecurityEventsCounters)
    std::string DropReason;
    std::string ConstraintId;
END_DECLARE_NPB_ENTRY_TABLE(DroppedSecurityEventsCounters)

DECLARE_NPB_TABLE(CriticalSecurityEventsAlertsCounters)

BEGIN_DECLARE_NPB_ENTRY_TABLE(MacToIpAssociationCounters)
    std::vector<uint8_t> IpAddress;
END_DECLARE_NPB_ENTRY_TABLE(MacToIpAssociationCounters)

BEGIN_DECLARE_NPB_ENTRY_TABLE(IpAnomaliesConnectionsCounters)
    std::string          FilterRule;
    std::string          IncomingPackageInterface;
    std::string          OutgoingPackageInterface;
    std::vector<uint8_t> SourceIpAddress;
    std::vector<uint8_t> DestinationIpAddress;
    std::string          TmProtocol;
    std::string          PayloadLength;
END_DECLARE_NPB_ENTRY_TABLE(IpAnomaliesConnectionsCounters)

BEGIN_DECLARE_NPB_ENTRY_TABLE(DroppedConnectionCounters)
    std::string          FilterRule;
    std::string          IncomingPackageInterface;
    std::string          OutgoingPackageInterface;
    std::vector<uint8_t> SourceIpAddress;
    std::vector<uint8_t> DestinationIpAddress;
    std::string          TransportProtocol;
    std::string          UserName;
    std::string          ProcessName;
END_DECLARE_NPB_ENTRY_TABLE(DroppedConnectionCounters)

//HCP1 and SACID
DECLARE_NPB_TABLE(RxTxErrors)
DECLARE_NPB_TABLE(BusOffStatistics)

/**
 * @class   SecurityEventMonitoringData
 * @brief   utility class for nanoPB serialization.
 */
class SecurityEventMonitoringData: public SecurityEventMonitoringDataNPB
{
public:
    SecurityEventMonitoringData();
    ~SecurityEventMonitoringData() = default;

    SecurityEventMonitoringData(SecurityEventMonitoringData const& rhs) = delete;
    SecurityEventMonitoringData(SecurityEventMonitoringData&& rhs) noexcept;

    /**
    * @brief    default copy assignment operator
    */
    SecurityEventMonitoringData& operator=(SecurityEventMonitoringData const&) = delete;

    /**
    * @brief   default move assignment operator
    */
    SecurityEventMonitoringData& operator=(SecurityEventMonitoringData&&) = delete;

    void PrepareForSerialization();

    DECLARE_DM_TABLE(IpConnectionCounters)
    DECLARE_DM_TABLE(IpDroppedConnections)
    DECLARE_DM_TABLE(HostOsLogRate)
    DECLARE_DM_TABLE(ExternalUnsuccessfulConnections)
    DECLARE_DM_TABLE(ExternalInterfacesUsageStatistics)

    // ConMod EU
    DECLARE_DM_TABLE(ProcessPerformance)
    DECLARE_DM_TABLE(ProcessStartStopCounters)
    IpAnomaliesCountersTable DroppedBlockedConnections;
    IpAnomaliesCountersTable DisallowedLayer3ProtocolCounters;
    DECLARE_DM_TABLE(DiagnosticEventSequence)

    // Ethernet Anomalies Monitoring
    DECLARE_DM_TABLE(EthernetServiceInterruption)
    DECLARE_DM_TABLE(LinkUtilization)
    DECLARE_DM_TABLE(EthernetSwitchesCounters)

    IpAnomaliesCountersTable InvalidTcpDestinationPortCounter;
    IpAnomaliesCountersTable InvalidUdpDestinationPortCounter;
    IpAnomaliesCountersTable InvalidIpv4AddressCounter;
    IpAnomaliesCountersTable InvalidIpv6AddressCounter;
    IpAnomaliesCountersTable DisallowedLayer4ProtocolCounters;
    IpAnomaliesCountersTable UnusedPortConnectionAttempts;
    DECLARE_DM_TABLE(OversizedPacketsHistogram)
    DECLARE_DM_TABLE(FreshnessValueFailedCounters)
    DECLARE_DM_TABLE(MacToIpAssociationCounters)
    DECLARE_DM_TABLE(IpAnomaliesConnectionsCounters)
    DECLARE_DM_TABLE(DroppedConnectionCounters)

    // HCP3
    DECLARE_DM_TABLE(ServiceRegistry)
    DECLARE_DM_TABLE(ProcessCrashRate)
    std::vector<HistogramFloatBucket> AggregatedCrashRateHistogramBuckets;
    DECLARE_DM_TABLE(ExternalNewHWConnection)
    DECLARE_DM_TABLE(ExternalDataStorage)

    // Security Events Digesting
    DECLARE_DM_TABLE(SecurityEventsCounters)
    DECLARE_DM_TABLE(DroppedSecurityEventsCounters)
    DECLARE_DM_TABLE(CriticalSecurityEventsAlertsCounters)

    //HCP1 and SACID
    DECLARE_DM_TABLE(RxTxErrors)
    DECLARE_DM_TABLE(BusOffStatistics)
};

/**
 * @class   SecurityEventsPeriodicMonitoringData
 * @brief   utility class for nanoPB serialization.
 */
class SecurityEventsPeriodicMonitoringData: public SecurityEventsPeriodicMonitoringDataNPB
{
public:
    SecurityEventsPeriodicMonitoringData();
    
    /**
     * @brief destructor default
     */
    ~SecurityEventsPeriodicMonitoringData() = default;

    SecurityEventsPeriodicMonitoringData(SecurityEventsPeriodicMonitoringData const& rhs) = delete;
    
    /**
     * @brief    default move constructor
     */
    SecurityEventsPeriodicMonitoringData(SecurityEventsPeriodicMonitoringData&& other) = delete;

    /**
    * @brief    default copy assignment operator
    */
    SecurityEventsPeriodicMonitoringData& operator=(SecurityEventsPeriodicMonitoringData const&) = delete;

    /**
    * @brief   default move assignment operator
    */
    SecurityEventsPeriodicMonitoringData& operator=(SecurityEventsPeriodicMonitoringData&&) = delete;

    void PrepareForSerialization();

    inline void Clear()
    {
        Entries.clear();
    }

    using Entry = SecurityEventMonitoringData;
    std::vector<Entry> Entries;
};

}}}} // namespace brain::engines::security_events::nanopb

#endif // SECURITY_EVENTS_NANOPB_HPP
