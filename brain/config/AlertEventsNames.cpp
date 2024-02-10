#include "AlertEventsNames.hpp"
#include "common/utils/logger/Logger.hpp"

using namespace brain::sender_events;

std::string const&
brain::sender_events::GetCriticalEventString(CriticalEventAlert event)
{
    static const std::unordered_map<CriticalEventAlert, std::string> criticalEventAlert2String{
        {CriticalEventAlert::CriticalEventName, "CriticalSecurityEventAlert"},
        {CriticalEventAlert::SuspiciousAlertEventName, "SuspiciousSecurityEventAlert"},
        {CriticalEventAlert::HCP3HostSensorTimeoutAlert, "HCP3 HostSensor Keepalive timeout alert"},
        {CriticalEventAlert::DenialOfServiceAlert, "Denial of Service Alert"},
        {CriticalEventAlert::HostErrorMonitoring, "HostErrorMonitoring"},
        {CriticalEventAlert::IntelligentEventName, "IntelligentSensorEvent"},
        {CriticalEventAlert::SacidEventsEngine, "canControllerErroStateAlert"},
        {CriticalEventAlert::ExcessiveProcessMemoryUsage, "ExcessiveProcessMemoryUsage"},
        {CriticalEventAlert::ExcessiveProcessCpuUsage, "ExcessiveProcessCpuUsage"},
        {CriticalEventAlert::LinkUtilizationOutTraffic, "Link utilization alert for out traffic"},
        {CriticalEventAlert::LinkUtilizationInTraffic, "Link utilization alert for in traffic"},
        {CriticalEventAlert::TLSErrorReport, "TLSErrorReport"},
        {CriticalEventAlert::UnknownEventIdEventName, "Unknown eventID"},
        {CriticalEventAlert::SecevKeepaliveTimeoutAlert, "Secev Keepalive timeout alert"},
        {CriticalEventAlert::ErroneousServiceRegistration, "ErroneousServiceRegistration"},
        {CriticalEventAlert::SuspiciousAlertText, "suspicious DIAG_SEV_ECU_UNLOCK_SUCCESSFUL"},
        {CriticalEventAlert::NatFloodingAlertText, "NAT flooding"},
        {CriticalEventAlert::NatEntryNotFountAlertText, "can't locate NAT entry"},
        {CriticalEventAlert::NatDuplicateEntryText, "Duplicate NAT entry"},
        {CriticalEventAlert::DoubleIpToMacEventName, "double IP address to MAC address association"},
        {CriticalEventAlert::DoubleMacToIpEventName, "double MAC address to IP address association"},
        {CriticalEventAlert::SuspiciousProcessCrashRate, "SuspiciousProcessCrashRate"},
        {CriticalEventAlert::SuspiciousAggregateCrashRate, "SuspiciousAggregateCrashRate"},
        {CriticalEventAlert::PeriodicStatistics, "PeriodicStatistics"},
        {CriticalEventAlert::SACIDPeriodicStatistics, "SACIDPeriodicStatistics"},
        {CriticalEventAlert::DroppedUnknownEventIdAlertThatExceededMaxNumber,
         "DroppedUnknownEventIdAlertThatExceededMaxNumber"},
        {CriticalEventAlert::OSLogKernelPanic, "OSLogKernelPanic"},
        {CriticalEventAlert::DhmStringSizeLimit, "DhmStringSizeLimit"},
        {CriticalEventAlert::DhmUnkownConstrainId, "DhmUnkownConstrainId"},
        {CriticalEventAlert::DhmUnkownConstrainIdMaxNumber, "DhmUnkownConstrainIdMaxNumber"},
        {CriticalEventAlert::QlahUnknownProtocolFramesValue, "QlahUnknownProtocolFramesValue"},
        {CriticalEventAlert::QlahIllegalVlanFrame, "QlahEthIllegalVlanFrameAlert"}};

    if (CriticalEventAlert::MaxEventName == event)
    {
        static std::string const emptyValue;

        LOG_ERROR << "Invalid Event supplied" << LOG_NOOP;

        return emptyValue;
    }

    return criticalEventAlert2String.at(event);
}