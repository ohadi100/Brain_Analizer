/**
 * @file
 * @brief    This file contains the definition of DtcServiceRegistryEvent.
 */
#ifndef DTC_SERVICE_REGISTRY_EVENT_HPP
#define DTC_SERVICE_REGISTRY_EVENT_HPP

#include "DtcTimedEvent.hpp"

#include <ara/diag/app_ids.h>
#include <mutex>


namespace brain
{
namespace diagnostics
{
namespace dtc
{

/**
 * @class   DtcServiceRegistryEvent
 * @brief   Dtc should be true if at least one service registered.
 *          Dtc status is updated after qualification/suspension time.
 */
class DtcServiceRegistryEvent : public DtcTimedEvent
{
public:

    /**
      * @brief    Constructor
      * @param    instanceId
      */
    DtcServiceRegistryEvent(TimerPtr timer);

    /**
     * @brief   Updates the number of registered services.
     * @param   bool const serviceRegistryStatus - true for service registered, false for service disconnected
     */
    void UpdateServiceRegistyStatus(bool const serviceRegistryStatus);

private:
    
    std::mutex m_updateMutex;

    uint32_t m_registeredServicesCount;
};
} // namespace dtc
} // namespace diagnostics
} // namespace brain

#endif // DTC_SERVICE_REGISTRY_EVENT_HPP
