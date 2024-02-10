/**
 * @file
 * @brief Implementation of the back-end state machine logic
 *
 */
#include "BELogicStates.hpp"
#include "BELogicSM.hpp"
#include "Creditor.hpp"
#include "StateMachine.hpp"
#include "brain/sender/publishers/interface/PublisherInterface.hpp"
#include "common/thread_handler/Reactor.hpp"
#include "common/utils/logger/Logger.hpp"
#include "common/utils/stateMachine/StateMachine.hpp"

// Use to ignore unused varialbe in compile time
#define IGNORE_UNUSED __attribute__((unused))
#define CHECK_NULLPTR(pointer) \
    if (nullptr == pointer)         \
    {                          \
        LOG_ERROR << "Pointer " << #pointer << " is null" << LOG_NOOP; \
        return false;          \
    }

using namespace brain::sender;

namespace brain
{
namespace sender
{

const char* BE_STATES_STR[BE_STATES::STATE_MAX]
    = {"STATE_INIT", "STATE_CONNECTING", "STATE_READY_TO_SEND", "STATE_WAIT_ACK", "STATE_RETRY", "STATE_DISABLED"};

const char* BE_EVENTS_STR[BE_EVENTS::EVENT_MAX] = {"EVENT_CONNECT",
                                                   "EVENT_CONNECTING",
                                                   "EVENT_CONNECTED",
                                                   "EVENT_SEND_DATA",
                                                   "EVENT_SEND_OLD_DATA",
                                                   "EVENT_DATA_SENT_TIMEOUT",
                                                   "EVENT_ACK_OK",
                                                   "EVENT_ACK_OK_WITH_TO",
                                                   "EVENT_ACK_OK_WITH_TO_EXPIRED",
                                                   "EVENT_ACK_RETRY",
                                                   "EVENT_ACK_RETRY_WITH_TO",
                                                   "EVENT_MAX_RETRY",
                                                   "EVENT_DISABLE",
                                                   "EVENT_ENABLE",
                                                   "EVENT_DISCONNECT",
                                                   "EVENT_CONNECTION_TIMEOUT"};

using TimerTypes = brain::sender::BELogicSM::TimerTypes;
}  // namespace sender
}  // namespace brain

using brain::sender_manager::SenderManager;

void
BaseState::DebugStateEventNotification(unsigned int& oldState,
                                       unsigned int& newState,
                                       unsigned int& event,
                                       bool          transition)
{
    if ((oldState < STATE_MAX) && (newState < STATE_MAX) && (event < EVENT_MAX))
    {
        if (transition)
        {
            LOG_DEBUG << "BELOGICSM: Transition from " << BE_STATES_STR[oldState] << " to " << BE_STATES_STR[newState]
                      << "(" << BE_EVENTS_STR[event] << ")" << LOG_NOOP;
        }
        else
        {
            LOG_DEBUG << "BELOGICSM: New event " << BE_EVENTS_STR[event]
                      << "posted at State=" << BE_STATES_STR[oldState] << LOG_NOOP;
        }
    }
    else
    {
        LOG_DEBUG << "Wrong oldState=" << oldState << " or newState=" << newState << " or event=" << event << LOG_NOOP;
    }
}

bool
BaseState::OnConnected(IGNORE_UNUSED StateMachineBase* sm, IGNORE_UNUSED void* data)
{
    return true;
}

bool
BaseState::OnDisable(IGNORE_UNUSED StateMachineBase* sm, IGNORE_UNUSED void* data)
{
    CHECK_NULLPTR(sm);

    SenderManager& senderManager = static_cast<BELogicSM*>(sm)->m_senderManager;
   
    if(!senderManager.cancelPeriodicTimer())
    {
        LOG_ERROR << "cancelPeriodicTimer function was failed" << LOG_NOOP;
        return false;
    }

    if(!senderManager.cancelLastTimer())
    {
        LOG_ERROR << "cancelLastTimer function was failed" << LOG_NOOP;
        return false;
    }

    return senderManager.m_publisher->Disconnect();
}

bool
BaseState::OnDisconnected(IGNORE_UNUSED StateMachineBase* sm, IGNORE_UNUSED void* data)
{
    CHECK_NULLPTR(sm);

    // Disable the connection and roll again to init state
    SenderManager& senderManager = static_cast<BELogicSM*>(sm)->m_senderManager;

    if(!senderManager.m_publisher->Disconnect())
    {
        LOG_ERROR << "m_publisher->Disconnect() function was failed" << LOG_NOOP;
        return false;
    }

    return static_cast<BELogicSM*>(sm)->setSMEvent(EVENT_CONNECT);
}

void
BaseState::UseCredit(StateMachineBase* sm)
{
    SenderManager& senderManager = static_cast<BELogicSM*>(sm)->m_senderManager;
    senderManager.m_creditor->UseCredit(senderManager.m_msgToBeSend->size());
}

bool
StateInit::OnConnect(IGNORE_UNUSED StateMachineBase* sm, IGNORE_UNUSED void* data)
{
    CHECK_NULLPTR(sm);

    SenderManager& senderManager = static_cast<BELogicSM*>(sm)->m_senderManager;

    bool result = senderManager.m_publisher->Connect([&senderManager](PublisherInterface::EventType eventType) {
        senderManager.PublisherCallback(static_cast<uint8_t>(eventType));
    });

    LOG_DEBUG << "PublisherDBG: OnConnect, result=" << (result ? "OK" : "ERROR") << LOG_NOOP;
    if (result)
    {
        return static_cast<BELogicSM*>(sm)->reloadTimerTask(TimerTypes::WAIT_FOR_CONNECTION_UP);
    }
    else
    {
        return false;
    }
}

bool
StateReadyToSend::OnSendData(IGNORE_UNUSED StateMachineBase* sm, IGNORE_UNUSED void* data)
{
    CHECK_NULLPTR(sm);

    auto* beLogicSm = static_cast<BELogicSM*>(sm);

    // Reset the retry counter when new message is being send
    beLogicSm->m_maxRetryCounter = 0U;

    if (beLogicSm->m_senderManager.SendMessage())
    {
        return beLogicSm->reloadTimerTask(TimerTypes::DATA_SENT);
    }

    return false;
}

bool
StateWaitAck::OnAckOk(IGNORE_UNUSED StateMachineBase* sm, IGNORE_UNUSED void* data)
{
    CHECK_NULLPTR(sm);

    UseCredit(sm);
    return true;
}

bool
StateWaitAck::OnAckOkWithTO(IGNORE_UNUSED StateMachineBase* sm, IGNORE_UNUSED void* data)
{
    CHECK_NULLPTR(sm);

    return static_cast<BELogicSM*>(sm)->reloadTimerTask(TimerTypes::ACK_OK_TIMEOT);
}

bool
StateWaitAck::OnAckOkWithTOExpired(IGNORE_UNUSED StateMachineBase* sm, IGNORE_UNUSED void* data)
{
    CHECK_NULLPTR(sm);
    
    UseCredit(sm);
    return true;
}

bool
StateWaitAck::OnAckRetry(IGNORE_UNUSED StateMachineBase* sm, IGNORE_UNUSED void* data)
{
    CHECK_NULLPTR(sm);

    return static_cast<BELogicSM*>(sm)->setSMEvent(EVENT_SEND_OLD_DATA);
}

bool
StateWaitAck::OnAckRetryWithTO(IGNORE_UNUSED StateMachineBase* sm, IGNORE_UNUSED void* data)
{
    CHECK_NULLPTR(sm);

    return static_cast<BELogicSM*>(sm)->reloadTimerTask(TimerTypes::RETRY_TIMEOT);
}

bool
StateRetry::OnReSendData(IGNORE_UNUSED StateMachineBase* sm, IGNORE_UNUSED void* data)
{
    CHECK_NULLPTR(sm);

    if (static_cast<BELogicSM*>(sm)->m_maxRetryCounter++ < BELogicSM::MAX_RETRY_LIMIT)
    {
        if (static_cast<BELogicSM*>(sm)->m_senderManager.ReSendMessage())
        {
            return static_cast<BELogicSM*>(sm)->reloadTimerTask(TimerTypes::DATA_SENT);
        }
    }
    else
    {
        static_cast<BELogicSM*>(sm)->setSMEvent(EVENT_MAX_RETRY);
    }

    return false;  // For stay in the same state
}

bool
StateRetry::OnMaxRetry(IGNORE_UNUSED StateMachineBase* sm, IGNORE_UNUSED void* data)
{
    CHECK_NULLPTR(sm);

    return static_cast<BELogicSM*>(sm)->setSMEvent(EVENT_DISABLE);
}

bool
StateDisabled::OnEnable(IGNORE_UNUSED StateMachineBase* sm, IGNORE_UNUSED void* data)
{
    // TBD
    return true;
}
