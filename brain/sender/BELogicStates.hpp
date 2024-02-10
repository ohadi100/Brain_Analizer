/**
 * @file
 * @brief BE logic states definitions.
 *
 * This module is common state machine logic with all the BE types.
 */
#pragma once

namespace common
{
namespace utils
{
class StateMachine;
}  // namespace utils
}  // namespace common
namespace brain
{
namespace sender
{

// class StateMachine;
using StateMachineBase = common::utils::StateMachine;

enum BE_STATES
{
    STATE_INIT = 0,
    STATE_CONNECTING,
    STATE_READY_TO_SEND,
    STATE_WAIT_ACK,
    STATE_RETRY,
    STATE_DISABLED,
    STATE_MAX
};

enum BE_EVENTS
{
    EVENT_CONNECT = 0,
    EVENT_CONNECTING,
    EVENT_CONNECTED,
    EVENT_SEND_DATA,
    EVENT_SEND_OLD_DATA,
    EVENT_DATA_SENT_TIMEOUT,
    EVENT_ACK_OK,
    EVENT_ACK_OK_WITH_TO,
    EVENT_ACK_OK_WITH_TO_EXPIRED,
    EVENT_ACK_RETRY,
    EVENT_ACK_RETRY_WITH_TO,
    EVENT_MAX_RETRY,
    EVENT_DISABLE,
    EVENT_ENABLE,
    EVENT_DISCONNECT,
    EVENT_CONNECTION_TIMEOUT,
    EVENT_MAX
};

class BaseState
{
public:
    BaseState()  = default;
    ~BaseState() = default;

    /**
     * @brief    default copy constructor
     */
    BaseState(const BaseState& other) = delete;

    /**
     * @brief    default move constructor
     */
    BaseState(BaseState&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    BaseState& operator=(BaseState const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    BaseState& operator=(BaseState&&) = delete;

    static void DebugStateEventNotification(unsigned int& oldState,
                                            unsigned int& newState,
                                            unsigned int& event,
                                            bool          transition);
    static void UseCredit(StateMachineBase* sm);

    static bool OnConnected(StateMachineBase* sm, void* data);
    static bool OnDisable(StateMachineBase* sm, void* data);
    static bool OnDisconnected(StateMachineBase* sm, void* data);
};

class StateInit : public BaseState
{
public:
    StateInit()  = default;
    ~StateInit() = default;

    /**
     * @brief    default copy constructor
     */
    StateInit(const StateInit& other) = default;

    /**
     * @brief    default move constructor
     */
    StateInit(StateInit&& other) = default;

    /**
    * @brief    default copy assignment operator
    */
    StateInit& operator=(StateInit const&) = default;

    /**
    * @brief   default move assignment operator
    */
    StateInit& operator=(StateInit&&) = default;

    static bool OnConnect(StateMachineBase* sm, void* data);
};

class StateConnecting : public BaseState
{
public:
    StateConnecting()  = default;
    ~StateConnecting() = default;

    /**
     * @brief    default copy constructor
     */
    StateConnecting(const StateConnecting& other) = default;

    /**
     * @brief    default move constructor
     */
    StateConnecting(StateConnecting&& other) = default;

    /**
    * @brief    default copy assignment operator
    */
    StateConnecting& operator=(StateConnecting const&) = default;

    /**
    * @brief   default move assignment operator
    */
    StateConnecting& operator=(StateConnecting&&) = default;
};

class StateReadyToSend : public BaseState
{
public:
    StateReadyToSend()  = default;
    ~StateReadyToSend() = default;
    
    /**
     * @brief    default copy constructor
     */
    StateReadyToSend(const StateReadyToSend& other) = default;

    /**
     * @brief    default move constructor
     */
    StateReadyToSend(StateReadyToSend&& other) = default;

    /**
    * @brief    default copy assignment operator
    */
    StateReadyToSend& operator=(StateReadyToSend const&) = default;

    /**
    * @brief   default move assignment operator
    */
    StateReadyToSend& operator=(StateReadyToSend&&) = default;

    static bool OnSendData(StateMachineBase* sm, void* data);
};

class StateWaitAck : public BaseState
{
public:
    StateWaitAck()  = default;
    ~StateWaitAck() = default;

    /**
     * @brief    default copy constructor
     */
    StateWaitAck(const StateWaitAck& other) = default;

    /**
     * @brief    default move constructor
     */
    StateWaitAck(StateWaitAck&& other) = default;

    /**
    * @brief    default copy assignment operator
    */
    StateWaitAck& operator=(StateWaitAck const&) = default;

    /**
    * @brief   default move assignment operator
    */
    StateWaitAck& operator=(StateWaitAck&&) = default;

    static bool OnAckOk(StateMachineBase* sm, void* data);
    static bool OnAckOkWithTO(StateMachineBase* sm, void* data);
    static bool OnAckOkWithTOExpired(StateMachineBase* sm, void* data);
    static bool OnAckRetry(StateMachineBase* sm, void* data);
    static bool OnAckRetryWithTO(StateMachineBase* sm, void* data);
};

class StateRetry : public BaseState
{
public:
    StateRetry()  = default;
    ~StateRetry() = default;

    /**
     * @brief    default copy constructor
     */
    StateRetry(const StateRetry& other) = default;

    /**
     * @brief    default move constructor
     */
    StateRetry(StateRetry&& other) = default;

    /**
     * @brief    default copy assignment operator
     */
    StateRetry& operator=(StateRetry const&) = default;

    /**
     * @brief   default move assignment operator
     */
    StateRetry& operator=(StateRetry&&) = default;

    static bool OnReSendData(StateMachineBase* sm, void* data);

    static bool OnMaxRetry(StateMachineBase* sm, void* data);
};

class StateDisabled
{
public:
    /**
     * @brief    default constructor
     */
    StateDisabled()  = default;

    /**
     * @brief    default destructor
     */
    ~StateDisabled() = default;

    /**
     * @brief    default copy constructor
     */
    StateDisabled(const StateDisabled& other) = default;

    /**
     * @brief    default move constructor
     */
    StateDisabled(StateDisabled&& other) = default;

    /**
    * @brief    default copy assignment operator
    */
    StateDisabled& operator=(StateDisabled const&) = default;

    /**
    * @brief   default move assignment operator
    */
    StateDisabled& operator=(StateDisabled&&) = default;

    static bool OnEnable(StateMachineBase* sm, void* data);
};
}  // namespace sender
}  // namespace brain
