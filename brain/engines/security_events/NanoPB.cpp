/**
 * @file
 * @brief     This file contains the functionality of statistical nanopb encoding/decoding for Security events
*/
#include "NanoPB.hpp"

#include "brain/utils/nanopb/Decoders.hpp"
#include "brain/utils/nanopb/Encoders.hpp"

using namespace brain::engines::security_events::nanopb;

DEFINE_NPB_TABLE(IpConnectionCounters, ipConnectionCounters)

//_______________________Ip Dropped Connections_______________________

IpDroppedConnectionsEntry::IpDroppedConnectionsEntry():
IpDroppedConnectionsEntryNPB
{
    common::nanopb::CreateDecodingCallback(SourceIP),
    common::nanopb::CreateDecodingCallback(TransportProtocol),
    0,
    0
}
{}

IpDroppedConnectionsEntry::IpDroppedConnectionsEntry(IpDroppedConnectionsEntry&& rhs) noexcept :
IpDroppedConnectionsEntryNPB{rhs},
MOVE_DM(SourceIP),
MOVE_DM(TransportProtocol)
{
    sourceIp.arg = &SourceIP;
    transportProtocol.arg = &TransportProtocol;
}

void IpDroppedConnectionsEntry::PrepareForSerialization()
{
    sourceIp = common::nanopb::CreateEncodingCallback(SourceIP);
    transportProtocol = common::nanopb::CreateEncodingCallback(TransportProtocol);
}

DEFINE_NPB_ENTRY_TABLE(IpDroppedConnections, ipDroppedConnections)

//_______________________Host Os Log Rate_______________________

HostOsLogRateEntry::HostOsLogRateEntry():
HostOsLogRateEntryNPB
{
    0U,
    0U,
    0U,
    true,
    {
        0U,
        0U,
        common::nanopb::CreateDecodingCallback<HistogramFloatBucket, com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket_fields>(Buckets)
    }
}
{}

HostOsLogRateEntry::HostOsLogRateEntry(HostOsLogRateEntry&& rhs) noexcept :
HostOsLogRateEntryNPB{rhs},
MOVE_DM(Buckets)
{
    has_rateHistogram = !Buckets.empty();
    rateHistogram.buckets.arg = &Buckets;
}

void HostOsLogRateEntry::PrepareForSerialization()
{
    rateHistogram.buckets = common::nanopb::CreateEncodingCallback<HistogramFloatBucket, com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket_fields>(Buckets);
}

DEFINE_NPB_ENTRY_TABLE(HostOsLogRate, hostOsLogRate)

//_______________________External Unsuccessful Connections_______________________

ExternalUnsuccessfulConnectionsEntry::ExternalUnsuccessfulConnectionsEntry():
ExternalUnsuccessfulConnectionsEntryNPB
{
    0U,
    0U,
    0U,
    9U,
    0U,
    common::nanopb::CreateDecodingCallback(ConnectionUnitDeviceName),
    0U
}
{}

ExternalUnsuccessfulConnectionsEntry::ExternalUnsuccessfulConnectionsEntry(ExternalUnsuccessfulConnectionsEntry&& rhs) noexcept :
ExternalUnsuccessfulConnectionsEntryNPB{rhs},
MOVE_DM(ConnectionUnitDeviceName)
{
    connectionUnitDeviceName.arg = &ConnectionUnitDeviceName;
}

void ExternalUnsuccessfulConnectionsEntry::PrepareForSerialization()
{
    connectionUnitDeviceName = common::nanopb::CreateEncodingCallback(ConnectionUnitDeviceName);
}

DEFINE_NPB_ENTRY_TABLE(ExternalUnsuccessfulConnections, externalUnsuccessfulConnections)

//_______________________External Interfaces Usage Statistics_______________________

DEFINE_NPB_TABLE(ExternalInterfacesUsageStatistics, externalInterfacesUsageStatistics)

//_______________________Process Performance_______________________

ProcessPerformanceEntry::ProcessPerformanceEntry() :
ProcessPerformanceEntryNPB
{
    {
        common::nanopb::CreateDecodingCallback(ProcessName),
    },
    0,
    {0},
    0,
    {0},
    true,
    {
        0,
        0,
        common::nanopb::CreateDecodingCallback<HistogramFloatBucket, com_vwg_connect_ids_idsperiodicreport_v1_Bucket_fields>(PriviledgedModeCpuUsageBuckets)
    },
    true,
    {
        0,
        0,
        common::nanopb::CreateDecodingCallback<HistogramFloatBucket, com_vwg_connect_ids_idsperiodicreport_v1_Bucket_fields>(NonPriviledgedModeCpuUsageBuckets)
    },
    true,
    {
        0,
        0,
        common::nanopb::CreateDecodingCallback<HistogramFloatBucket, com_vwg_connect_ids_idsperiodicreport_v1_Bucket_fields>(MemoryUsageBuckets)
    }
}
{}

ProcessPerformanceEntry::ProcessPerformanceEntry(ProcessPerformanceEntry&& rhs) noexcept :
ProcessPerformanceEntryNPB{rhs},
MOVE_DM(PriviledgedModeCpuUsageBuckets),
MOVE_DM(NonPriviledgedModeCpuUsageBuckets),
MOVE_DM(MemoryUsageBuckets),
MOVE_DM(ProcessName)
{
    if(rhs.which_sensor == com_vwg_connect_ids_idsperiodicreport_v1_ProcessPerformanceEntry_sensorIdentifier_tag)
    {
        SensorIdentifier = std::move(rhs.SensorIdentifier);
    }
    has_priviledgedModeCpuUsageHistogram = !PriviledgedModeCpuUsageBuckets.empty();
    priviledgedModeCpuUsageHistogram.buckets.arg = &PriviledgedModeCpuUsageBuckets;
    has_nonPriviledgedModeCpuUsageHistogram = !NonPriviledgedModeCpuUsageBuckets.empty();
    nonPriviledgedModeCpuUsageHistogram.buckets.arg = &NonPriviledgedModeCpuUsageBuckets;
    has_memoryUsageHistogram = !MemoryUsageBuckets.empty();
    memoryUsageHistogram.buckets.arg = &MemoryUsageBuckets;
}

void ProcessPerformanceEntry::PrepareForSerialization()
{
    processName = common::nanopb::CreateEncodingCallback(ProcessName);
    if(which_sensor == com_vwg_connect_ids_idsperiodicreport_v1_ProcessPerformanceEntry_sensorIdentifier_tag)
    {
        sensor.sensorIdentifier = common::nanopb::CreateEncodingCallback(SensorIdentifier);
    }
    priviledgedModeCpuUsageHistogram.buckets = common::nanopb::CreateEncodingCallback<HistogramFloatBucket, com_vwg_connect_ids_idsperiodicreport_v1_Bucket_fields>(PriviledgedModeCpuUsageBuckets);
    nonPriviledgedModeCpuUsageHistogram.buckets = common::nanopb::CreateEncodingCallback<HistogramFloatBucket, com_vwg_connect_ids_idsperiodicreport_v1_Bucket_fields>(NonPriviledgedModeCpuUsageBuckets);
    memoryUsageHistogram.buckets = common::nanopb::CreateEncodingCallback<HistogramFloatBucket, com_vwg_connect_ids_idsperiodicreport_v1_Bucket_fields>(MemoryUsageBuckets);
}

DEFINE_NPB_ENTRY_TABLE(ProcessPerformance, processPerformance)

//_______________________ProcessStartStopCounters_______________________

ProcessStartStopCountersEntry::ProcessStartStopCountersEntry() :
ProcessStartStopCountersEntryNPB
{
    0,
    0,
    0,
    0,
    {
        common::nanopb::CreateDecodingCallback(AdaptiveAutosarAppName),
    },
    {
        common::nanopb::CreateDecodingCallback(ProcessCommandLine),
    },
    0,
    0
}
{}

ProcessStartStopCountersEntry::ProcessStartStopCountersEntry(ProcessStartStopCountersEntry&& rhs) noexcept :
ProcessStartStopCountersEntryNPB(rhs),
MOVE_DM(AdaptiveAutosarAppName),
MOVE_DM(ProcessCommandLine)
{

}

void ProcessStartStopCountersEntry::PrepareForSerialization()
{
    adaptiveAutosarAppName = common::nanopb::CreateEncodingCallback(AdaptiveAutosarAppName);
    processCommandLine = common::nanopb::CreateEncodingCallback(ProcessCommandLine);
}

DEFINE_NPB_ENTRY_TABLE(ProcessStartStopCounters, processStartStopCounters)

//_______________________IpAnomaliesCounters_______________________

IpAnomaliesCountersEntry::IpAnomaliesCountersEntry() :
IpAnomaliesCountersEntryNPB
{
    0U,
    0U,
    0U,
    common::nanopb::CreateDecodingCallback(SourceIpAddress),
    common::nanopb::CreateDecodingCallback(DestinationIpAddress),
    0U,
    0U,
    0U,
    0U,
    common::nanopb::CreateDecodingCallback(TransportProtocol),
    0U
}
{}

IpAnomaliesCountersEntry::IpAnomaliesCountersEntry(IpAnomaliesCountersEntry&& rhs) noexcept
  : IpAnomaliesCountersEntryNPB{rhs}
  , MOVE_DM(SourceIpAddress)
  , MOVE_DM(DestinationIpAddress)
  , MOVE_DM(TransportProtocol)
{
    sourceIpAddress.arg = &SourceIpAddress;
    destinationIpAddress.arg = &DestinationIpAddress;
    transportProtocol.arg = &TransportProtocol;
}

void IpAnomaliesCountersEntry::PrepareForSerialization()
{
    sourceIpAddress = common::nanopb::CreateEncodingCallback(SourceIpAddress);
    destinationIpAddress = common::nanopb::CreateEncodingCallback(DestinationIpAddress);
    transportProtocol = common::nanopb::CreateEncodingCallback(TransportProtocol);
}

DEFINE_NPB_ENTRY_TABLE(IpAnomaliesCounters, ipAnomaliesCounters)

//_______________________Service Registry_______________________

ServiceRegistryEntry::ServiceRegistryEntry():
ServiceRegistryEntryNPB
{
    0,
    0,
    0,
    common::nanopb::CreateDecodingCallback(RegisteredService),
    common::nanopb::CreateDecodingCallback(RegisteringApplicationId),
    common::nanopb::CreateDecodingCallback(RegisteringServerIP),
    false,
    0
}
{}

ServiceRegistryEntry::ServiceRegistryEntry(ServiceRegistryEntry&& rhs) noexcept :
ServiceRegistryEntryNPB{rhs},
MOVE_DM(RegisteredService),
MOVE_DM(RegisteringApplicationId),
MOVE_DM(RegisteringServerIP)
{
    registeredService.arg = &RegisteredService;
    registeringApplicationId.arg = &RegisteringApplicationId;
    registeringServerIP.arg = &RegisteringServerIP;
}

void ServiceRegistryEntry::PrepareForSerialization()
{
    registeredService = common::nanopb::CreateEncodingCallback(RegisteredService);
    registeringApplicationId = common::nanopb::CreateEncodingCallback(RegisteringApplicationId);
    registeringServerIP = common::nanopb::CreateEncodingCallback(RegisteringServerIP);
}

DEFINE_NPB_ENTRY_TABLE(ServiceRegistry, serviceRegistry)

//_______________________Process Crash Rate_______________________

ProcessCrashRateEntry::ProcessCrashRateEntry()
  : ProcessCrashRateEntryNPB{
      0,
      0,
      0,
      common::nanopb::CreateDecodingCallback(ProcessName),
      0,
      0,
      true,
      {0,
       0,
       common::nanopb::CreateDecodingCallback<HistogramFloatBucket,
                                              com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket_fields>(Buckets)},
      common::nanopb::CreateDecodingCallback(CrashReasonStr)}
{}

ProcessCrashRateEntry::ProcessCrashRateEntry(ProcessCrashRateEntry&& rhs) noexcept
  : ProcessCrashRateEntryNPB{rhs}
  , MOVE_DM(ProcessName)
  , MOVE_DM(Buckets)
  , MOVE_DM(CrashReasonStr)
{
    processName.arg = &ProcessName;
    crashReasonStr.arg                    = &CrashReasonStr;
    has_processCrashRateHistogram         = !Buckets.empty();
    processCrashRateHistogram.buckets.arg = &Buckets;
}

void ProcessCrashRateEntry::PrepareForSerialization()
{
    processName = common::nanopb::CreateEncodingCallback(ProcessName);
    crashReasonStr = common::nanopb::CreateEncodingCallback(CrashReasonStr);
    processCrashRateHistogram.buckets = common::nanopb::CreateEncodingCallback<HistogramFloatBucket, com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket_fields>(Buckets);
}

DEFINE_NPB_ENTRY_TABLE(ProcessCrashRate, processCrashRate)

//_______________________External New HW Connection_______________________

ExternalNewHWConnectionEntry::ExternalNewHWConnectionEntry():
ExternalNewHWConnectionEntryNPB
{   
    0,
    0,
    0,
    common::nanopb::CreateDecodingCallback(HardwareIdSerial),
    common::nanopb::CreateDecodingCallback(DeviceSubClasses),
    common::nanopb::CreateDecodingCallback(CalledLriverLibrary),
    common::nanopb::CreateDecodingCallback(HandlingConnectionDriverLibrary),
    0
}
{}

ExternalNewHWConnectionEntry::ExternalNewHWConnectionEntry(ExternalNewHWConnectionEntry&& rhs) noexcept :
ExternalNewHWConnectionEntryNPB{rhs},
MOVE_DM(HardwareIdSerial),
MOVE_DM(DeviceSubClasses),
MOVE_DM(CalledLriverLibrary),
MOVE_DM(HandlingConnectionDriverLibrary)
{
    ExternalNewHWConnectionEntryNPB::hardwareIdSerial.arg = &HardwareIdSerial;
    ExternalNewHWConnectionEntryNPB::deviceSubClasses.arg = &DeviceSubClasses;
    ExternalNewHWConnectionEntryNPB::calledLriverLibrary.arg = &CalledLriverLibrary;
    ExternalNewHWConnectionEntryNPB::handlingConnectionDriverLibrary.arg = &HandlingConnectionDriverLibrary;
}

void ExternalNewHWConnectionEntry::PrepareForSerialization()
{
    hardwareIdSerial = common::nanopb::CreateEncodingCallback(HardwareIdSerial);
    deviceSubClasses = common::nanopb::CreateEncodingCallback(DeviceSubClasses);
    calledLriverLibrary = common::nanopb::CreateEncodingCallback(CalledLriverLibrary);
    handlingConnectionDriverLibrary = common::nanopb::CreateEncodingCallback(HandlingConnectionDriverLibrary);
}

DEFINE_NPB_ENTRY_TABLE(ExternalNewHWConnection, externalNewHWConnection)

//_______________________External Data Storage_______________________

ExternalDataStorageEntry::ExternalDataStorageEntry():
ExternalDataStorageEntryNPB
{   
    0,
    0,
    0,
    common::nanopb::CreateDecodingCallback(HardwareIdSerialNumber),
    0,
    0
}
{}

ExternalDataStorageEntry::ExternalDataStorageEntry(ExternalDataStorageEntry&& rhs) noexcept :
ExternalDataStorageEntryNPB{rhs},
MOVE_DM(HardwareIdSerialNumber)
{
    ExternalDataStorageEntryNPB::hardwareIdSerialNumber.arg = &HardwareIdSerialNumber;
}

void ExternalDataStorageEntry::PrepareForSerialization()
{
    hardwareIdSerialNumber = common::nanopb::CreateEncodingCallback(HardwareIdSerialNumber);
  
}

DEFINE_NPB_ENTRY_TABLE(ExternalDataStorage, externalDataStorage)

//_______________________Ethernet Service Interruption_______________________

DEFINE_NPB_TABLE(EthernetServiceInterruption, ethernetServiceInterruption)

//_______________________Link Utilization_______________________

LinkUtilizationEntry::LinkUtilizationEntry() : LinkUtilizationEntryNPB{}
{}

LinkUtilizationEntry::LinkUtilizationEntry(LinkUtilizationEntry&& rhs) noexcept :
    LinkUtilizationEntryNPB{rhs},
    MOVE_DM(BucketsOut),
    MOVE_DM(BucketsIn)
{}

void LinkUtilizationEntry::PrepareForSerialization()
{
    linkUtilizationHistogramOut.buckets = common::nanopb::CreateEncodingCallback<HistogramFloatBucket, com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket_fields>(BucketsOut);
    linkUtilizationHistogramIn.buckets = common::nanopb::CreateEncodingCallback<HistogramFloatBucket, com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket_fields>(BucketsIn);
}

DEFINE_NPB_ENTRY_TABLE(LinkUtilization, linkUtilization)

//_______________________Ethernet Switches Counters_______________________

DEFINE_NPB_TABLE(EthernetSwitchesCounters, ethernetSwitchesCounters)

//_______________________Diagnostic Event Sequence_______________________

DEFINE_NPB_TABLE(DiagnosticEventSequence, diagnosticEventSequence)

//_______________________FreshnessValueFailedCounters_______________________

DEFINE_NPB_TABLE(FreshnessValueFailedCounters, freshnessValueFailedCounters)

//_______________________SecurityEventsCounters_______________________

DEFINE_NPB_TABLE(SecurityEventsCounters, securityEventsCounters)

//_______________________OversizedPacketsHistogram_______________________

OversizedPacketsHistogramEntry::OversizedPacketsHistogramEntry() :
OversizedPacketsHistogramEntryNPB
{
    0U,
    0U,
    0U,
    common::nanopb::CreateDecodingCallback(SourceIpAddress),
    common::nanopb::CreateDecodingCallback(DestinationIpAddress),
    0U,
    0U,
    common::nanopb::CreateDecodingCallback(TransportProtocol),
    true,
    {
        0,
        0,
        common::nanopb::CreateDecodingCallback<HistogramFloatBucket, com_vwg_connect_ids_idsperiodicreport_v1_Bucket_fields>(OversizedPacketsHistogram)
    }
}
{}

OversizedPacketsHistogramEntry::OversizedPacketsHistogramEntry(OversizedPacketsHistogramEntry&& rhs) noexcept
  : OversizedPacketsHistogramEntryNPB{rhs}
  , MOVE_DM(OversizedPacketsHistogram)
  , MOVE_DM(SourceIpAddress)
  , MOVE_DM(DestinationIpAddress)
  , MOVE_DM(TransportProtocol)
{
    has_oversizedPacketsHistogram = !OversizedPacketsHistogram.empty();
    oversizedPacketsHistogram.buckets.arg = &OversizedPacketsHistogram;
    
    sourceIpAddress.arg = &SourceIpAddress;
    destinationIpAddress.arg = &DestinationIpAddress;
    transportProtocol.arg = &TransportProtocol;
}

void OversizedPacketsHistogramEntry::PrepareForSerialization()
{
    sourceIpAddress = common::nanopb::CreateEncodingCallback(SourceIpAddress);
    destinationIpAddress = common::nanopb::CreateEncodingCallback(DestinationIpAddress);
    transportProtocol = common::nanopb::CreateEncodingCallback(TransportProtocol);
    oversizedPacketsHistogram.buckets = common::nanopb::CreateEncodingCallback<HistogramFloatBucket, com_vwg_connect_ids_idsperiodicreport_v1_Bucket_fields>(OversizedPacketsHistogram);
}

DEFINE_NPB_ENTRY_TABLE(OversizedPacketsHistogram, oversizedPacketsHistogram)

//_______________________DroppedSecurityEventsCounters_______________________

DroppedSecurityEventsCountersEntry::DroppedSecurityEventsCountersEntry() :
DroppedSecurityEventsCountersEntryNPB
{
    0U,
    0U,
    0U,
    common::nanopb::CreateDecodingCallback(DropReason),
    0U,
    common::nanopb::CreateDecodingCallback(ConstraintId)
}
{}

DroppedSecurityEventsCountersEntry::DroppedSecurityEventsCountersEntry(DroppedSecurityEventsCountersEntry&& rhs) noexcept
  : DroppedSecurityEventsCountersEntryNPB{rhs}
  , MOVE_DM(DropReason)
  , MOVE_DM(ConstraintId)
{
    dropReason.arg = &DropReason;
    constraintId.arg = &ConstraintId;
}

void DroppedSecurityEventsCountersEntry::PrepareForSerialization()
{
    dropReason = common::nanopb::CreateEncodingCallback(DropReason);
    constraintId = common::nanopb::CreateEncodingCallback(ConstraintId);
}

DEFINE_NPB_ENTRY_TABLE(DroppedSecurityEventsCounters, droppedSecurityEventsCounters)

//_______________________CriticalSecurityEventsAlertsCounters_______________________

DEFINE_NPB_TABLE(CriticalSecurityEventsAlertsCounters, criticalSecurityEventsAlertsCounters)

//_______________________MacToIpAssociationCounters_______________________

MacToIpAssociationCountersEntry::MacToIpAssociationCountersEntry()
  : MacToIpAssociationCountersEntryNPB{0U, common::nanopb::CreateDecodingCallback(IpAddress), 0U, 0U, 0U}
{
}

MacToIpAssociationCountersEntry::MacToIpAssociationCountersEntry(MacToIpAssociationCountersEntry&& rhs) noexcept
  : MacToIpAssociationCountersEntryNPB{rhs}
  , MOVE_DM(IpAddress)
{
    ipAddress.arg = &IpAddress;
}

void
MacToIpAssociationCountersEntry::PrepareForSerialization()
{
    ipAddress = common::nanopb::CreateEncodingCallback(IpAddress);
}

DEFINE_NPB_ENTRY_TABLE(MacToIpAssociationCounters, macToIpAssociationCounters)

//_______________________IpAnomaliesConnectionsCounters_______________________

IpAnomaliesConnectionsCountersEntry::IpAnomaliesConnectionsCountersEntry():
IpAnomaliesConnectionsCountersEntryNPB
{   
    0U,
    0U,
    0U,
    0U,
    0U,
    common::nanopb::CreateDecodingCallback(FilterRule),
    common::nanopb::CreateDecodingCallback(IncomingPackageInterface),
    common::nanopb::CreateDecodingCallback(OutgoingPackageInterface),
    common::nanopb::CreateDecodingCallback(SourceIpAddress),
    common::nanopb::CreateDecodingCallback(DestinationIpAddress),
    common::nanopb::CreateDecodingCallback(TmProtocol),
    0U,
    0U,
    0U,
    0U,
    0U,
    common::nanopb::CreateDecodingCallback(PayloadLength),
    0U,
    0U,
    0U
}
{}

IpAnomaliesConnectionsCountersEntry::IpAnomaliesConnectionsCountersEntry(IpAnomaliesConnectionsCountersEntry&& rhs) noexcept
  : IpAnomaliesConnectionsCountersEntryNPB{rhs}
  , MOVE_DM(FilterRule)
  , MOVE_DM(IncomingPackageInterface)
  , MOVE_DM(OutgoingPackageInterface)
  , MOVE_DM(SourceIpAddress)
  , MOVE_DM(DestinationIpAddress)
  , MOVE_DM(TmProtocol)
  , MOVE_DM(PayloadLength)
{
    filterRule.arg               = &FilterRule;
    incomingPackageInterface.arg = &IncomingPackageInterface;
    outgoingPackageInterface.arg = &OutgoingPackageInterface;
    sourceIpAddress.arg          = &SourceIpAddress;
    destinationIpAddress.arg     = &DestinationIpAddress;
    tmProtocol.arg               = &TmProtocol;
    payloadLength.arg            = &PayloadLength;
}

void IpAnomaliesConnectionsCountersEntry::PrepareForSerialization()
{
    filterRule = common::nanopb::CreateEncodingCallback(FilterRule);
    incomingPackageInterface = common::nanopb::CreateEncodingCallback(IncomingPackageInterface);
    outgoingPackageInterface = common::nanopb::CreateEncodingCallback(OutgoingPackageInterface);
    sourceIpAddress = common::nanopb::CreateEncodingCallback(SourceIpAddress);
    destinationIpAddress = common::nanopb::CreateEncodingCallback(DestinationIpAddress);
    tmProtocol = common::nanopb::CreateEncodingCallback(TmProtocol);
    payloadLength = common::nanopb::CreateEncodingCallback(PayloadLength);
}

DEFINE_NPB_ENTRY_TABLE(IpAnomaliesConnectionsCounters, ipAnomaliesConnectionsCounters)

//_______________________DroppedBlockedConnectionCounter_______________________

DroppedConnectionCountersEntry::DroppedConnectionCountersEntry():
DroppedConnectionCountersEntryNPB
{   
    0U,
    0U,
    0U,
    0U,
    0U,
    common::nanopb::CreateDecodingCallback(FilterRule),
    common::nanopb::CreateDecodingCallback(IncomingPackageInterface),
    common::nanopb::CreateDecodingCallback(OutgoingPackageInterface),
    common::nanopb::CreateDecodingCallback(SourceIpAddress),
    common::nanopb::CreateDecodingCallback(DestinationIpAddress),
    common::nanopb::CreateDecodingCallback(TransportProtocol),
    0U,
    0U,
    common::nanopb::CreateDecodingCallback(UserName),
    common::nanopb::CreateDecodingCallback(ProcessName),
    0U,
    0U
}
{}

DroppedConnectionCountersEntry::DroppedConnectionCountersEntry(DroppedConnectionCountersEntry&& rhs) noexcept
  : DroppedConnectionCountersEntryNPB{rhs}
  , MOVE_DM(FilterRule)
  , MOVE_DM(IncomingPackageInterface)
  , MOVE_DM(OutgoingPackageInterface)
  , MOVE_DM(SourceIpAddress)
  , MOVE_DM(DestinationIpAddress)
  , MOVE_DM(TransportProtocol)
  , MOVE_DM(UserName)
  , MOVE_DM(ProcessName)
{
    filterRule.arg               = &FilterRule;
    incomingPackageInterface.arg = &IncomingPackageInterface;
    outgoingPackageInterface.arg = &OutgoingPackageInterface;
    sourceIpAddress.arg          = &SourceIpAddress;
    destinationIpAddress.arg     = &DestinationIpAddress;
    transportProtocol.arg        = &TransportProtocol;
    userName.arg                 = &UserName;
    processName.arg              = &ProcessName;
}

void DroppedConnectionCountersEntry::PrepareForSerialization()
{
    filterRule = common::nanopb::CreateEncodingCallback(FilterRule);
    incomingPackageInterface = common::nanopb::CreateEncodingCallback(IncomingPackageInterface);
    outgoingPackageInterface = common::nanopb::CreateEncodingCallback(OutgoingPackageInterface);
    sourceIpAddress = common::nanopb::CreateEncodingCallback(SourceIpAddress);
    destinationIpAddress = common::nanopb::CreateEncodingCallback(DestinationIpAddress);
    transportProtocol = common::nanopb::CreateEncodingCallback(TransportProtocol);
    userName = common::nanopb::CreateEncodingCallback(UserName);
    processName = common::nanopb::CreateEncodingCallback(ProcessName);
}

DEFINE_NPB_ENTRY_TABLE(DroppedConnectionCounters, droppedConnectionCounters)

//_______________________RxTxErrors Counters_______________________

DEFINE_NPB_TABLE(RxTxErrors, rxTxErrors)

//_______________________BusOffStatistics Counters_______________________

DEFINE_NPB_TABLE(BusOffStatistics, busOffStatistics)

//_____________________________________________________________________

SecurityEventMonitoringData::SecurityEventMonitoringData():
SecurityEventMonitoringDataNPB com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventMonitoringData_init_default
{
    INIT_DM_TABLE(IpConnectionCounters, ipConnectionCounters)
    INIT_DM_TABLE(IpDroppedConnections, ipDroppedConnections)
    INIT_DM_TABLE(HostOsLogRate, hostOsLogRate)
    INIT_DM_TABLE(ExternalUnsuccessfulConnections, externalUnsuccessfulConnections)
    INIT_DM_TABLE(ExternalInterfacesUsageStatistics, externalInterfacesUsageStatistics)
    INIT_DM_TABLE(ProcessPerformance, processPerformance)
    INIT_DM_TABLE(ProcessStartStopCounters, processStartStopCounters)
    INIT_DM_TABLE(DroppedBlockedConnections, droppedBlockedConnections)
    INIT_DM_TABLE(DisallowedLayer3ProtocolCounters, disallowedLayer3ProtocolCounters)
    INIT_DM_TABLE(OversizedPacketsHistogram, oversizedPacketsHistogram)
    INIT_DM_TABLE(ServiceRegistry, serviceRegistry)
    INIT_DM_TABLE(ProcessCrashRate, processCrashRate)

    has_aggregatedCrashRateHistogram = false;
    aggregatedCrashRateHistogram = com_vwg_connect_ids_idsperiodicreport_v1_FloatHistogramData{
        0,
        0,
        common::nanopb::CreateDecodingCallback<HistogramFloatBucket, com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket_fields>(AggregatedCrashRateHistogramBuckets)
    };    

    INIT_DM_TABLE(EthernetServiceInterruption, ethernetServiceInterruption)
    INIT_DM_TABLE(LinkUtilization, linkUtilization)
    INIT_DM_TABLE(EthernetSwitchesCounters, ethernetSwitchesCounters)
    INIT_DM_TABLE(InvalidTcpDestinationPortCounter, invalidTcpDestinationPortCounter)
    INIT_DM_TABLE(InvalidUdpDestinationPortCounter, invalidUdpDestinationPortCounter)
    INIT_DM_TABLE(InvalidIpv4AddressCounter, invalidIpv4AddressCounter)
    INIT_DM_TABLE(InvalidIpv6AddressCounter, invalidIpv6AddressCounter)
    INIT_DM_TABLE(DiagnosticEventSequence, diagnosticEventSequence)
    INIT_DM_TABLE(DisallowedLayer4ProtocolCounters, disallowedLayer4ProtocolCounters)
    INIT_DM_TABLE(UnusedPortConnectionAttempts, unusedPortConnectionAttempts)
    INIT_DM_TABLE(ExternalNewHWConnection, externalNewHWConnection)
    INIT_DM_TABLE(ExternalDataStorage, externalDataStorage)
    INIT_DM_TABLE(FreshnessValueFailedCounters, freshnessValueFailedCounters)
    INIT_DM_TABLE(SecurityEventsCounters, securityEventsCounters)
    INIT_DM_TABLE(DroppedSecurityEventsCounters, droppedSecurityEventsCounters)
    INIT_DM_TABLE(CriticalSecurityEventsAlertsCounters, criticalSecurityEventsAlertsCounters)
    INIT_DM_TABLE(MacToIpAssociationCounters, macToIpAssociationCounters)
    INIT_DM_TABLE(IpAnomaliesConnectionsCounters, ipAnomaliesConnectionsCounters)
    INIT_DM_TABLE(DroppedConnectionCounters, droppedConnectionCounters)
    INIT_DM_TABLE(RxTxErrors, rxTxErrors)
    INIT_DM_TABLE(BusOffStatistics, busOffStatistics)
}

SecurityEventMonitoringData::SecurityEventMonitoringData(SecurityEventMonitoringData&& rhs) noexcept :
SecurityEventMonitoringDataNPB{rhs},
MOVE_DM(IpConnectionCounters),
MOVE_DM(IpDroppedConnections),
MOVE_DM(HostOsLogRate),
MOVE_DM(ExternalUnsuccessfulConnections),
MOVE_DM(ExternalInterfacesUsageStatistics),
//ConMod EU
MOVE_DM(ProcessPerformance),
MOVE_DM(ProcessStartStopCounters),
MOVE_DM(DroppedBlockedConnections),
MOVE_DM(DisallowedLayer3ProtocolCounters),
MOVE_DM(DiagnosticEventSequence),
// Ethernet Anomalies Monitoring
MOVE_DM(EthernetServiceInterruption),
MOVE_DM(LinkUtilization),
MOVE_DM(EthernetSwitchesCounters),

MOVE_DM(InvalidTcpDestinationPortCounter),
MOVE_DM(InvalidUdpDestinationPortCounter),
MOVE_DM(InvalidIpv4AddressCounter),
MOVE_DM(InvalidIpv6AddressCounter),
MOVE_DM(DisallowedLayer4ProtocolCounters),
MOVE_DM(UnusedPortConnectionAttempts),
MOVE_DM(OversizedPacketsHistogram),
MOVE_DM(FreshnessValueFailedCounters),
MOVE_DM(MacToIpAssociationCounters),
MOVE_DM(IpAnomaliesConnectionsCounters),
MOVE_DM(DroppedConnectionCounters),
// HCP3
MOVE_DM(ServiceRegistry),
MOVE_DM(ProcessCrashRate),
MOVE_DM(AggregatedCrashRateHistogramBuckets),
MOVE_DM(ExternalNewHWConnection),
MOVE_DM(ExternalDataStorage),
// Security Events Digesting
MOVE_DM(SecurityEventsCounters),
MOVE_DM(DroppedSecurityEventsCounters),
MOVE_DM(CriticalSecurityEventsAlertsCounters),
//HCP1 and SACID
MOVE_DM(RxTxErrors),
MOVE_DM(BusOffStatistics)
{
    COPY_DM_TABLE(IpConnectionCounters, ipConnectionCounters)
    COPY_DM_TABLE(HostOsLogRate, hostOsLogRate)
    COPY_DM_TABLE(ExternalUnsuccessfulConnections, externalUnsuccessfulConnections)
    COPY_DM_TABLE(ExternalInterfacesUsageStatistics, externalInterfacesUsageStatistics)
    COPY_DM_TABLE(ProcessPerformance, processPerformance)
    COPY_DM_TABLE(ProcessStartStopCounters, processStartStopCounters)
    COPY_DM_TABLE(DroppedBlockedConnections, droppedBlockedConnections)
    COPY_DM_TABLE(ServiceRegistry, serviceRegistry)
    COPY_DM_TABLE(ProcessCrashRate, processCrashRate)
    has_aggregatedCrashRateHistogram = !AggregatedCrashRateHistogramBuckets.empty();
    aggregatedCrashRateHistogram.buckets.arg = &AggregatedCrashRateHistogramBuckets;
    COPY_DM_TABLE(ExternalNewHWConnection, externalNewHWConnection)
    COPY_DM_TABLE(ExternalDataStorage, externalDataStorage)
    COPY_DM_TABLE(EthernetServiceInterruption, ethernetServiceInterruption)
    COPY_DM_TABLE(LinkUtilization, linkUtilization)
    COPY_DM_TABLE(EthernetSwitchesCounters, ethernetSwitchesCounters)
    COPY_DM_TABLE(DisallowedLayer3ProtocolCounters, disallowedLayer3ProtocolCounters)
    COPY_DM_TABLE(InvalidTcpDestinationPortCounter, invalidTcpDestinationPortCounter)
    COPY_DM_TABLE(InvalidUdpDestinationPortCounter, invalidUdpDestinationPortCounter)
    COPY_DM_TABLE(InvalidIpv4AddressCounter, invalidIpv4AddressCounter)
    COPY_DM_TABLE(InvalidIpv6AddressCounter, invalidIpv6AddressCounter)
    COPY_DM_TABLE(DiagnosticEventSequence, diagnosticEventSequence)
    COPY_DM_TABLE(FreshnessValueFailedCounters, freshnessValueFailedCounters)
    COPY_DM_TABLE(DisallowedLayer4ProtocolCounters, disallowedLayer4ProtocolCounters)
    COPY_DM_TABLE(UnusedPortConnectionAttempts, unusedPortConnectionAttempts)
    COPY_DM_TABLE(OversizedPacketsHistogram, oversizedPacketsHistogram)
    COPY_DM_TABLE(SecurityEventsCounters, securityEventsCounters)
    COPY_DM_TABLE(DroppedSecurityEventsCounters, droppedSecurityEventsCounters)
    COPY_DM_TABLE(CriticalSecurityEventsAlertsCounters, criticalSecurityEventsAlertsCounters)
    COPY_DM_TABLE(MacToIpAssociationCounters, macToIpAssociationCounters)
    COPY_DM_TABLE(IpAnomaliesConnectionsCounters, ipAnomaliesConnectionsCounters)
    COPY_DM_TABLE(DroppedConnectionCounters, droppedConnectionCounters)
    COPY_DM_TABLE(RxTxErrors, rxTxErrors)
    COPY_DM_TABLE(BusOffStatistics, busOffStatistics)
}

void SecurityEventMonitoringData::PrepareForSerialization()
{
    PREPARE_DM_TABLE(IpConnectionCounters, ipConnectionCounters)
    PREPARE_DM_TABLE(IpDroppedConnections, ipDroppedConnections)
    PREPARE_DM_TABLE(HostOsLogRate, hostOsLogRate)
    PREPARE_DM_TABLE(ExternalUnsuccessfulConnections, externalUnsuccessfulConnections)
    PREPARE_DM_TABLE(ExternalInterfacesUsageStatistics, externalInterfacesUsageStatistics)
    PREPARE_DM_TABLE(ProcessPerformance, processPerformance)
    PREPARE_DM_TABLE(ProcessStartStopCounters, processStartStopCounters)
    PREPARE_DM_TABLE(DroppedBlockedConnections, droppedBlockedConnections)
    PREPARE_DM_TABLE(ServiceRegistry, serviceRegistry)
    PREPARE_DM_TABLE(ProcessCrashRate, processCrashRate)
    PREPARE_DM_TABLE(ExternalNewHWConnection, externalNewHWConnection)
    PREPARE_DM_TABLE(ExternalDataStorage, externalDataStorage)
    PREPARE_DM_TABLE(EthernetServiceInterruption, ethernetServiceInterruption)
    PREPARE_DM_TABLE(LinkUtilization, linkUtilization)
    PREPARE_DM_TABLE(EthernetSwitchesCounters, ethernetSwitchesCounters)
    PREPARE_DM_TABLE(DiagnosticEventSequence, diagnosticEventSequence)
    PREPARE_DM_TABLE(InvalidTcpDestinationPortCounter, invalidTcpDestinationPortCounter)
    PREPARE_DM_TABLE(InvalidUdpDestinationPortCounter, invalidUdpDestinationPortCounter)
    PREPARE_DM_TABLE(InvalidIpv4AddressCounter, invalidIpv4AddressCounter)
    PREPARE_DM_TABLE(InvalidIpv6AddressCounter, invalidIpv6AddressCounter)
    PREPARE_DM_TABLE(DisallowedLayer3ProtocolCounters, disallowedLayer3ProtocolCounters)
    PREPARE_DM_TABLE(DisallowedLayer4ProtocolCounters, disallowedLayer4ProtocolCounters)
    PREPARE_DM_TABLE(UnusedPortConnectionAttempts, unusedPortConnectionAttempts)
    PREPARE_DM_TABLE(FreshnessValueFailedCounters, freshnessValueFailedCounters)
    PREPARE_DM_TABLE(OversizedPacketsHistogram, oversizedPacketsHistogram)
    PREPARE_DM_TABLE(SecurityEventsCounters, securityEventsCounters)
    PREPARE_DM_TABLE(DroppedSecurityEventsCounters, droppedSecurityEventsCounters)
    PREPARE_DM_TABLE(CriticalSecurityEventsAlertsCounters, criticalSecurityEventsAlertsCounters)
    PREPARE_DM_TABLE(MacToIpAssociationCounters, macToIpAssociationCounters)
    PREPARE_DM_TABLE(IpAnomaliesConnectionsCounters, ipAnomaliesConnectionsCounters)
    PREPARE_DM_TABLE(DroppedConnectionCounters, droppedConnectionCounters)
    PREPARE_DM_TABLE(RxTxErrors, rxTxErrors)
    PREPARE_DM_TABLE(BusOffStatistics, busOffStatistics)

    has_aggregatedCrashRateHistogram = !AggregatedCrashRateHistogramBuckets.empty();
    aggregatedCrashRateHistogram.buckets
        = common::nanopb::CreateEncodingCallback<HistogramFloatBucket,
                                                 com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket_fields>(
            AggregatedCrashRateHistogramBuckets);
}

SecurityEventsPeriodicMonitoringData::SecurityEventsPeriodicMonitoringData():
SecurityEventsPeriodicMonitoringDataNPB
{
    common::nanopb::CreateDecodingCallback<SecurityEventMonitoringDataNPB, com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventMonitoringData_fields>(Entries)
}
{}

void SecurityEventsPeriodicMonitoringData::PrepareForSerialization()
{
    securityEventMonitoringData = common::nanopb::CreateEncodingCallback<SecurityEventMonitoringDataNPB, com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventMonitoringData_fields>(Entries);
    for (auto& entry: Entries)
    {
        entry.PrepareForSerialization();
    }
}
