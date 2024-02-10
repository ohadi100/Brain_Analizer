/**
 * @file
 * @brief    This file contains the implementation of DtcServiceDiscoveryEvent.
 */
#include "DtcServiceDiscoveryEvent.hpp"


using brain::diagnostics::dtc::DtcServiceDiscoveryEvent;

namespace brain
{
namespace diagnostics
{
namespace dtc
{
static constexpr uint64_t NO_SERVICE_DISCOVERY_QUALIFICATION_TIME_SEC{60UL};
static constexpr uint64_t NO_SERVICE_DISCOVERY_SUSPENSION_TIME_SEC{120UL};
}  // namespace dtc
}  // namespace diagnostics
}  // namespace brain

DtcServiceDiscoveryEvent::DtcServiceDiscoveryEvent(TimerPtr timer):
    DtcTimedEvent(
        ids_evt_EventIdsServiceDiscoveryUnavailable,
        timer,
        NO_SERVICE_DISCOVERY_QUALIFICATION_TIME_SEC,
        NO_SERVICE_DISCOVERY_SUSPENSION_TIME_SEC),
    m_discoveredServicesCount(0U),
    m_serviceDiscoveryStatuses{false}
{
    // At startup, no services discovered yet, which should cause set of DtcEvent if no change is made for qualification
    // time
    updateConditionStatus(true);
}

void
DtcServiceDiscoveryEvent::UpdateServiceDiscoveryStatus(uint8_t const communicatorId, bool const serviceDiscoveryStatus)
{
    // Prevents parallel access from different communicators
    std::lock_guard<std::mutex> const lock(m_updateMutex);

    if (communicatorId < m_serviceDiscoveryStatuses.size())
    {
        // If communicator discovery status didn't change, nothing to do
        if (serviceDiscoveryStatus == m_serviceDiscoveryStatuses[communicatorId])
        {
            return;
        }

        // Status changed to true, when no services were discovered
        if (serviceDiscoveryStatus && (0U == m_discoveredServicesCount++))
        {
            updateConditionStatus(false);
        }

        // Status changed to false, resulting in no discovered services
        if (!serviceDiscoveryStatus && (0U == --m_discoveredServicesCount))
        {
            updateConditionStatus(true);
        }

        m_serviceDiscoveryStatuses[communicatorId] = serviceDiscoveryStatus;
    }
    else
    {
        LOG_ERROR << "DtcServiceDiscoveryEvent::UpdateServiceDiscoveryStatus Index out of bound" << LOG_NOOP;
    }
}