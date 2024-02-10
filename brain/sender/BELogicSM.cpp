/**
 * @file
 * @brief Implementation of the back-end state machine logic
 *
 */
#include "BELogicSM.hpp"
#include "common/utils/logger/Logger.hpp"

using brain::sender::BELogicSM;

BELogicSM::BELogicSM(SenderManager& senderManager, const TimersVectorPairs& timersVector)
  : StateMachineBase("BELogicSM", STATE_MAX, EVENT_MAX, STATE_INIT, BaseState::DebugStateEventNotification)
  , m_senderManager(senderManager)
{
    // If the vector isn't empty, override the default values
    for (auto& element : timersVector)
    {
        m_timers[element.first].first = element.second;
    }

    // Initialize the state machine matrix
    INIT_TRANSITION(m_smRepo, STATE_INIT, EVENT_CONNECT, STATE_CONNECTING, StateInit, OnConnect);
    INIT_TRANSITION(m_smRepo, STATE_INIT, EVENT_DISABLE, STATE_DISABLED, StateInit, OnDisable);

    INIT_TRANSITION(m_smRepo, STATE_CONNECTING, EVENT_CONNECTED, STATE_READY_TO_SEND, StateConnecting, OnConnected);
    INIT_TRANSITION(m_smRepo, STATE_CONNECTING, EVENT_CONNECTION_TIMEOUT, STATE_INIT, StateConnecting, OnDisconnected);
    INIT_TRANSITION(m_smRepo, STATE_CONNECTING, EVENT_DISABLE, STATE_DISABLED, StateConnecting, OnDisable);

    INIT_TRANSITION(m_smRepo, STATE_READY_TO_SEND, EVENT_SEND_DATA, STATE_WAIT_ACK, StateReadyToSend, OnSendData);
    INIT_TRANSITION(m_smRepo, STATE_READY_TO_SEND, EVENT_DISCONNECT, STATE_INIT, StateReadyToSend, OnDisconnected);
    INIT_TRANSITION(m_smRepo, STATE_READY_TO_SEND, EVENT_DISABLE, STATE_DISABLED, StateReadyToSend, OnDisable);

    INIT_TRANSITION(m_smRepo, STATE_WAIT_ACK, EVENT_DATA_SENT_TIMEOUT, STATE_RETRY, StateWaitAck, OnAckRetry);
    INIT_TRANSITION(m_smRepo, STATE_WAIT_ACK, EVENT_ACK_OK, STATE_READY_TO_SEND, StateWaitAck, OnAckOk);
    INIT_TRANSITION(m_smRepo, STATE_WAIT_ACK, EVENT_ACK_OK_WITH_TO, STATE_WAIT_ACK, StateWaitAck, OnAckOkWithTO);
    INIT_TRANSITION(m_smRepo,
                    STATE_WAIT_ACK,
                    EVENT_ACK_OK_WITH_TO_EXPIRED,
                    STATE_READY_TO_SEND,
                    StateWaitAck,
                    OnAckOkWithTOExpired);
    INIT_TRANSITION(m_smRepo, STATE_WAIT_ACK, EVENT_ACK_RETRY, STATE_RETRY, StateWaitAck, OnAckRetry);
    INIT_TRANSITION(m_smRepo, STATE_WAIT_ACK, EVENT_ACK_RETRY_WITH_TO, STATE_RETRY, StateWaitAck, OnAckRetryWithTO);
    INIT_TRANSITION(m_smRepo, STATE_WAIT_ACK, EVENT_DISABLE, STATE_DISABLED, StateWaitAck, OnDisable);
    INIT_TRANSITION(m_smRepo, STATE_WAIT_ACK, EVENT_DISCONNECT, STATE_INIT, StateWaitAck, OnDisconnected);

    INIT_TRANSITION(m_smRepo, STATE_RETRY, EVENT_SEND_OLD_DATA, STATE_WAIT_ACK, StateRetry, OnReSendData);
    INIT_TRANSITION(m_smRepo, STATE_RETRY, EVENT_MAX_RETRY, STATE_INIT, StateRetry, OnDisconnected);
    INIT_TRANSITION(m_smRepo, STATE_RETRY, EVENT_DISCONNECT, STATE_INIT, StateRetry, OnDisconnected);

    INIT_TRANSITION(m_smRepo, STATE_DISABLED, EVENT_ENABLE, STATE_INIT, StateDisabled, OnEnable);
}

bool
BELogicSM::setSMEvent(BE_EVENTS event)
{
    return postEvent(event);
}

bool
BELogicSM::reloadTimerTask(TimerTypes timerType)
{
    m_senderManager.cancelLastTimer();
    auto timerId = m_senderManager.setReactorTimerTask(m_timers[timerType].second, m_timers[timerType].first);
    LOG_DEBUG << "reloadTimerTask, timerType = " << std::to_string(static_cast<uint32_t>(timerType))
              << ",timer=" << m_timers[timerType].first << ",timerId=" << timerId << LOG_NOOP;
    return true;
}