/**
 * @file
 * @brief    This file contains the definition of DtcServiceDiscoveryEvent.
 */
#ifndef DTC_SERVICE_DISCOVERY_EVENT_HPP
#define DTC_SERVICE_DISCOVERY_EVENT_HPP

#include "DtcTimedEvent.hpp"
#include "brain/communicator/Communicator.hpp"

#include <ara/diag/app_ids.h>
#include <mutex>
#include <array>


namespace brain
{
namespace diagnostics
{
namespace dtc
{

/**
 * @class   DtcServiceDiscoveryEvent
 * @brief   Dtc should be true if at least one service discovered.
 *          Dtc status is updated after qualification/suspension time.
 */
class DtcServiceDiscoveryEvent : public DtcTimedEvent
{
public:

    /**
      * @brief    Constructor
      * @param    instanceId
      */
    DtcServiceDiscoveryEvent(TimerPtr timer);
    
    /**
     * @brief   Updates communicator service discovery status
     * @param   uint8_t const communicatorId - communicator to update sevice discovery status for
     * @param   bool const serviceDiscoveryStatus
     */
    void UpdateServiceDiscoveryStatus(uint8_t const communicatorId, bool const serviceDiscoveryStatus);

private:
    
    std::mutex m_updateMutex;

    uint32_t m_discoveredServicesCount;
    std::array<bool, brain::brain_communicator::COMMUNICATORS_COUNT> m_serviceDiscoveryStatuses;
};
} // namespace dtc
} // namespace diagnostics
} // namespace brain

#endif // DTC_SERVICE_DISCOVERY_EVENT_HPP
