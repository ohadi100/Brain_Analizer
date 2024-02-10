#ifndef ALERT_EVENTS_NAMES_HPP
#define ALERT_EVENTS_NAMES_HPP

#include <string>
#include <unordered_map>

namespace brain
{
namespace sender_events
{

enum class CriticalEventAlert : uint16_t
{
    CriticalEventName = 0U,
    SuspiciousAlertEventName,
    HCP3HostSensorTimeoutAlert,
    DenialOfServiceAlert,
    HostErrorMonitoring,
    IntelligentEventName,
    SacidEventsEngine,
    ExcessiveProcessMemoryUsage,
    ExcessiveProcessCpuUsage,
    LinkUtilizationOutTraffic,
    LinkUtilizationInTraffic,
    TLSErrorReport,
    UnknownEventIdEventName,
    SecevKeepaliveTimeoutAlert,
    ErroneousServiceRegistration,
    SuspiciousAlertText,
    NatFloodingAlertText,
    NatEntryNotFountAlertText,
    NatDuplicateEntryText,
    DoubleIpToMacEventName,
    DoubleMacToIpEventName,
    SuspiciousProcessCrashRate,
    SuspiciousAggregateCrashRate,
    PeriodicStatistics, 
    SACIDPeriodicStatistics,
    DroppedUnknownEventIdAlertThatExceededMaxNumber,
    OSLogKernelPanic,
    DhmStringSizeLimit,
    DhmUnkownConstrainId,
    DhmUnkownConstrainIdMaxNumber,
    MaxEventName,
    QlahUnknownProtocolFramesValue,
    QlahIllegalVlanFrame,
};

std::string const& GetCriticalEventString(CriticalEventAlert event);


}  // namespace sender_events
}  // namespace brain

#endif