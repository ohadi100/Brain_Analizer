/**
 * @file
 * @brief     This file contains the functionality of the DiagnosticEventPublisher class
 */
#include "brain/diagnostics/dtc/DtcEvent.hpp"
#include "common/utils/logger/Logger.hpp"
#include "common/utils/diagnostics/DiagnosticsUtils.hpp"


using brain::diagnostics::dtc::DtcEvent;


DtcEvent::DtcEvent(
    ara::core::InstanceSpecifier const& instanceId,
    bool const resetEnabled/*=true*/) :
m_resetEnabled(resetEnabled),
m_currentDtcStatus(false)
{
    LOG_DEBUG << "Offering publish service" << LOG_NOOP;

    auto getFaultDetectionCounter = [](void) -> std::int8_t {
        LOG_DEBUG << "getFaultDetectionCounter()" << LOG_NOOP;
        return 1;
    };

    std::ignore = m_monitor.emplace(GENERATE_INSTANCE_SPECIFIER(instanceId),
                                    std::bind(&DtcEvent::monitorInitCallback, this, std::placeholders::_1),
                                    getFaultDetectionCounter);
}

void DtcEvent::SetEvent(bool const status)
{
    if (status != m_currentDtcStatus)
    {
        m_currentDtcStatus = status;
        publishMonitorEventToDM();
    }
}

void DtcEvent::publishMonitorEventToDM()
{
    LOG_VERBOSE << "Publishing monitor events to the DM" << LOG_NOOP;

    MonitorActionType dtcValue = m_currentDtcStatus ? MonitorActionType::kFailed : MonitorActionType::kPassed;
    auto const res = m_monitor->ReportMonitorAction(dtcValue);
    if (!res.HasValue())
    {
        LOG_ERROR << "ara::diag::Monitor::ReportMonitorAction() failed" << LOG_NOOP;
    }
}

void DtcEvent::monitorInitCallback(ara::diag::Monitor::InitMonitorReason reason)
{
    if ((ara::diag::Monitor::InitMonitorReason::kClear == reason) && m_resetEnabled)
    {
        SetEvent(false);
    }
}