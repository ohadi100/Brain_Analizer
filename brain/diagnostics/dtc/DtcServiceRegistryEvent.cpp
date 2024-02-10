/**
 * @file
 * @brief    This file contains the implementation of DtcServiceRegistryEvent.
 */
#include "DtcServiceRegistryEvent.hpp"
#include "common/utils/logger/Logger.hpp"


using brain::diagnostics::dtc::DtcServiceRegistryEvent;

namespace brain
{
namespace diagnostics
{
namespace dtc
{
static constexpr uint64_t NO_SERVICE_REGISTRY_QUALIFICATION_TIME_SEC{60UL};
static constexpr uint64_t NO_SERVICE_REGISTRY_SUSPENSION_TIME_SEC{120UL};
}  // namespace dtc
}  // namespace diagnostics
}  // namespace brain

DtcServiceRegistryEvent::DtcServiceRegistryEvent(TimerPtr timer):
    DtcTimedEvent(
        ids_evt_EventIdsServiceRegistryUnavailable,
        timer,
        NO_SERVICE_REGISTRY_QUALIFICATION_TIME_SEC,
        NO_SERVICE_REGISTRY_SUSPENSION_TIME_SEC),
    m_registeredServicesCount(0U)
{
    // At startup, no services registered yet, which should cause set of DtcEvent if no change is made for qualification time
    updateConditionStatus(true);
}

void DtcServiceRegistryEvent::UpdateServiceRegistyStatus(bool const serviceRegistryStatus)
{
    // Prevents parallel access from different communicators
    std::lock_guard<std::mutex> const lock(m_updateMutex);
    
    if (serviceRegistryStatus && (0U == m_registeredServicesCount++))
    {
        updateConditionStatus(false);
    }

    if (!serviceRegistryStatus)
    {
        if (0U == m_registeredServicesCount)
        {
            LOG_ERROR << "ServiceDeregistered called when there isn't any registered services" << LOG_NOOP;
            return;
        }

        if (0U == --m_registeredServicesCount)
        {
            updateConditionStatus(true);
        }
    }
}
