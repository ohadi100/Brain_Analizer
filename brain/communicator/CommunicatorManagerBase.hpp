#pragma once
/**
 * @file
 * @brief     code for Brain's Communicator Manager Base
 */

#include "brain/communicator/Communicator.hpp"

namespace brain
{
namespace brain_communicator
{

/**
 * @class   CommunicatorManagerBase
 * @brief   Responsible for all the sensor communicators
 */
class CommunicatorManagerBase
{
    using UPCommunicator        = std::unique_ptr<brain::brain_communicator::Communicator>;
    using TimerPtr              = std::shared_ptr<common::Timer>;

public:
    /**
     * @brief   Constructor
     */
    CommunicatorManagerBase() = default;

    /**
     * @brief   Destructor
     */
    virtual ~CommunicatorManagerBase();

    /**
     * @brief    default copy constructor
     */
    CommunicatorManagerBase(const CommunicatorManagerBase& other) = delete;

    /**
     * @brief    default move constructor
     */
    CommunicatorManagerBase(CommunicatorManagerBase&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    CommunicatorManagerBase& operator=(CommunicatorManagerBase const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    CommunicatorManagerBase& operator=(CommunicatorManagerBase&&) = delete;

    /**
     * @brief   Prep all notification handlers for shutdown
     */
    void PrepareToShutdown();

    /**
     * @brief   Cancel all notification handlers shutdown prep
     */
    void CancelPrepareToShutdown();

    /**
     * @brief   Register all the default Notification Handlers (can gw, ethernet sensor, ...)
     */
    virtual void RegisterAllNotificationHandlers() = 0;

    /**
     * @brief   Un-register from all the sensors Notification Handlers
     */
    void DeregisterSensorsNotifications();

    /**
     * @brief   Un-register Timer
     */

#ifndef TESTS
protected:
#endif
    std::vector<UPCommunicator> m_comms;

    virtual void
    DeregisterTimer()
    {
    }
};


}  // namespace brain_communicator
}  // namespace brain
