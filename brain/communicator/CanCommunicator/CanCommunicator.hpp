/**
 * @file      CanCommunicator.hpp
 * @brief     The CanCommunicator is a communicator class for CAN
 */
#pragma once

#include "brain/communicator/Communicator.hpp"
#include "Logger.hpp"

#include "RawSocket.hpp"

#include <atomic>

using common::ids_socket::RawSocket;

namespace brain
{
namespace brain_communicator
{
namespace can_communicator
{
class CanCommunicator : public brain::brain_communicator::Communicator
{
public:
    /**
     * @fn      CanCommunicator()
     * @brief   Ctor
     * @return  none
     */
    CanCommunicator(Communicator::SensorDataQueuesManagerPtr queuesManager);

    /**
     * @fn      ~CanCommunicator()
     * @brief   Dtor
     * @param   none
     * @return  none
     */
    virtual ~CanCommunicator();

    /**
     * @brief API method to implement functionality of starting the communicator, ussually litsening to data from
     * outside
     * @return true - Init service succeeded, communicator is active
     * @return false - Communicator is inactive
     */
    virtual void Start() override;

    /**
     * @brief API Method to implement functionality of stopping the listening to outside data from the communicator
     * A Communicator must guarantee that after this function call it will no longer be active
     * @return true - Service was stopped during the method calling, communicator is inactive
     * @return false - Service was not stopped during the method execution, but still communicator is inactive
     */
    virtual void Stop() override;

private:
    static constexpr char      INTERFACE_NAME[] = "eth0.2066";
    static constexpr u_int32_t TIME_INTERVAL    = 5U;

    void CanThreadhandler();
    void StopCanThread() noexcept;
    void KillCommunication() noexcept;

    std::string       m_communicatorName;
    std::atomic<bool> m_activatedOnce;
    std::atomic<bool> m_terminationFlag;

    common::ids_socket::IBaseSocket* m_socket;
    std::thread*                     m_thread;

    Communicator::SensorDataQueuesManagerPtr m_queuesManager;
};
}  // namespace can_communicator
}  // namespace brain_communicator
}  // namespace brain