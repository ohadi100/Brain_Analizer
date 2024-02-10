/**
 * @file
 * @brief     This file contains the functionality of the CommunicatorManagerBase class
 */


#include "brain/communicator/CommunicatorManagerBase.hpp"

#include <tuple>
#include "utils/UtilsConstants.hpp"

using brain::brain_communicator::CommunicatorManagerBase;

CommunicatorManagerBase::~CommunicatorManagerBase()
{
    LOG_VERBOSE << "Destructor start" << LOG_NOOP;

    PrepareToShutdown();

    LOG_DEBUG << "Destructor end" << LOG_NOOP;
}

void
CommunicatorManagerBase::PrepareToShutdown()
{
    LOG_INFO << "Preparing to shutdown" << LOG_NOOP;
    DeregisterSensorsNotifications();
}

void
CommunicatorManagerBase::CancelPrepareToShutdown()
{
    LOG_INFO << "Cancelling prepare to shutdown" << LOG_NOOP;
    RegisterAllNotificationHandlers();
}


void
CommunicatorManagerBase::DeregisterSensorsNotifications()
{
    LOG_VERBOSE << "Deregistering from all Sensors notifications" << LOG_NOOP;

    auto it = m_comms.begin();
    while (m_comms.end() != it)
    {
        auto& comm = *it;
        comm->Stop();
        it = m_comms.erase(it);  // call the dtor
    }

#ifdef EEE_PLATFORM
    DeregisterTimer();
#endif  // EEE_PLATFORM
}
