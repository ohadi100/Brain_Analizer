#include "PassedDroppedAlertsNanoPB.hpp"
#include "NanoPbMacros.hpp"

#include "brain/utils/nanopb/Decoders.hpp"
#include "brain/utils/nanopb/Encoders.hpp"

using namespace brain::engines::security_events::nanopb;

SecEventAlertPassedDroppedCounters::SecEventAlertPassedDroppedCounters()
  : SecEventAlertPassedDroppedCountersNPB{0U, 0U, 0U, true, {0U, 0U}}
{
    has_passedDroppedCounters = true;
}

SecEventAlertPassedDroppedCounters::SecEventAlertPassedDroppedCounters(
    SecEventAlertPassedDroppedCounters&& rhs) noexcept
  : SecEventAlertPassedDroppedCountersNPB{rhs}
{
    has_passedDroppedCounters = true;
}

DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters::
    DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters()
  : DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCountersNPB{
      common::nanopb::CreateDecodingCallback(ConstraintId), true, {0U, 0U}}
{
}

DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters::
    DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters(
        DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters&& rhs) noexcept
  : DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCountersNPB(rhs)
  , MOVE_DM(ConstraintId)
{
    constraintId.arg = &ConstraintId;
    has_passedDroppedCounters = true;
}

void
DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters::PrepareForSerialization()
{
    constraintId = common::nanopb::CreateEncodingCallback(ConstraintId);
}

PassedDroppedCounters::PassedDroppedCounters()
  : PassedDroppedCountersNPB{0U, 0U}
{
}

PassedDroppedCounters::PassedDroppedCounters(PassedDroppedCounters&& rhs) noexcept
  : PassedDroppedCountersNPB(rhs)
{
}

PassedDroppedAlertsData::PassedDroppedAlertsData()
  : PassedDroppedAlertsDataNPB com_vwg_connect_ids_idsperiodicreport_v1_PassedDroppedAlertsData_init_default
{
    criticalSecurityEventAlertPassedDroppedCounters = common::nanopb::CreateDecodingCallback<
        SecEventAlertPassedDroppedCountersNPB,
        com_vwg_connect_ids_idsperiodicreport_v1_SecEventAlertPassedDroppedCounters_fields>(
        CriticalSecurityEventAlertPassedDroppedCounters);
    unknownEventIdAlertPassedDroppedCounters = common::nanopb::CreateDecodingCallback<
        SecEventAlertPassedDroppedCountersNPB,
        com_vwg_connect_ids_idsperiodicreport_v1_SecEventAlertPassedDroppedCounters_fields>(
        UnknownEventIdAlertPassedDroppedCounters);
    dhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters = common::nanopb::CreateDecodingCallback<
        DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCountersNPB,
        com_vwg_connect_ids_idsperiodicreport_v1_DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters_fields>(
        DhmIncidentWithUnknownConstraintIdAlertCounters);

    has_hostErrorMonitoringReportPassedDroppedCounters                    = true;
    has_dosDetectorReportPassedDroppedCounters                            = true;
    has_erroneousServiceRegistrationAlertPassedDroppedCounters            = true;
    has_doubledMacToIpAlertPassedDroppedCounters                          = true;
    has_suspiciousEcuUnlockSuccessfulAlertPassedDroppedCounters           = true;
    has_natTableAlertPassedDroppedCounters                                = true;
    has_processMemoryUsageAlertPassedDroppedCounters = true;
    has_processCpuUsageAlertPassedDroppedCounters    = true;
    has_suspiciousProcessCrashRateAlertPassedDroppedCounters              = true;
    has_suspiciousAggregateCrashRateAlertPassedDroppedCounters            = true;
    has_linkUtilizationAlertPassedDroppedCounters                         = true;
    has_intelligentSensorEventPassedDroppedCounters                       = true;
    has_serviceIntegrationKeepaliveTimeoutAlertPassedDroppedCounters      = true;
    has_canControllerErroStateAlertPassedDroppedCounters                  = true;
    has_secEventKeepAliveTimeoutAlertPassedDroppedCounters                = true;
    has_dhmOsLogRegexKernelPanicAlertPassedDroppedCounters                = true;
    has_dhmTerIncidentAlertPassedDroppedCounters                          = true;
    has_dhmIncidentStringSizeAlertPassedDroppedCounters                   = true;
    has_unknownProtocolDroppedFramesCounterAlertPassedDroppedCounters     = true;
    has_illegalVlanDropValueAlertPassedDroppedCounters                    = true;
}

PassedDroppedAlertsData::PassedDroppedAlertsData(PassedDroppedAlertsData&& rhs) noexcept
  : PassedDroppedAlertsDataNPB(rhs)
  , MOVE_DM(CriticalSecurityEventAlertPassedDroppedCounters)
  , MOVE_DM(UnknownEventIdAlertPassedDroppedCounters)
  , MOVE_DM(DhmIncidentWithUnknownConstraintIdAlertCounters)
{
    criticalSecurityEventAlertPassedDroppedCounters.arg              = &CriticalSecurityEventAlertPassedDroppedCounters;
    unknownEventIdAlertPassedDroppedCounters.arg                     = &UnknownEventIdAlertPassedDroppedCounters;
    dhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters.arg = &DhmIncidentWithUnknownConstraintIdAlertCounters;

    has_hostErrorMonitoringReportPassedDroppedCounters                    = true;
    has_dosDetectorReportPassedDroppedCounters                            = true;
    has_erroneousServiceRegistrationAlertPassedDroppedCounters            = true;
    has_doubledMacToIpAlertPassedDroppedCounters                          = true;
    has_suspiciousEcuUnlockSuccessfulAlertPassedDroppedCounters           = true;
    has_natTableAlertPassedDroppedCounters                                = true;
    has_processMemoryUsageAlertPassedDroppedCounters                      = true;
    has_processCpuUsageAlertPassedDroppedCounters    = true;
    has_suspiciousProcessCrashRateAlertPassedDroppedCounters              = true;
    has_suspiciousAggregateCrashRateAlertPassedDroppedCounters            = true;
    has_linkUtilizationAlertPassedDroppedCounters                         = true;
    has_intelligentSensorEventPassedDroppedCounters                       = true;
    has_serviceIntegrationKeepaliveTimeoutAlertPassedDroppedCounters      = true;
    has_canControllerErroStateAlertPassedDroppedCounters                  = true;
    has_secEventKeepAliveTimeoutAlertPassedDroppedCounters                = true;
    has_dhmOsLogRegexKernelPanicAlertPassedDroppedCounters                = true;
    has_dhmTerIncidentAlertPassedDroppedCounters                          = true;
    has_dhmIncidentStringSizeAlertPassedDroppedCounters                   = true;
    has_unknownProtocolDroppedFramesCounterAlertPassedDroppedCounters     = true;
    has_illegalVlanDropValueAlertPassedDroppedCounters                    = true;
}

void
PassedDroppedAlertsData::PrepareForSerialization()
{
    criticalSecurityEventAlertPassedDroppedCounters = common::nanopb::CreateEncodingCallback<
        SecEventAlertPassedDroppedCountersNPB,
        com_vwg_connect_ids_idsperiodicreport_v1_SecEventAlertPassedDroppedCounters_fields>(
        CriticalSecurityEventAlertPassedDroppedCounters);
    unknownEventIdAlertPassedDroppedCounters = common::nanopb::CreateEncodingCallback<
        SecEventAlertPassedDroppedCountersNPB,
        com_vwg_connect_ids_idsperiodicreport_v1_SecEventAlertPassedDroppedCounters_fields>(
        UnknownEventIdAlertPassedDroppedCounters);
    
    for (auto& entry: DhmIncidentWithUnknownConstraintIdAlertCounters) entry.PrepareForSerialization();
    dhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters = common::nanopb::CreateEncodingCallback<
        DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCountersNPB,
        com_vwg_connect_ids_idsperiodicreport_v1_DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters_fields>(
        DhmIncidentWithUnknownConstraintIdAlertCounters);
}