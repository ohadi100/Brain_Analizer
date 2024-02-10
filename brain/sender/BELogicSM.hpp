/**
 * @file
 * @brief BE logic state-machine core.
 *
 * This module is common state machine logic with all the BE types.
 */
#pragma once

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>
#include "BELogicStates.hpp"
#include "SenderManager.hpp"  // need to definition types inside SenderManager class
#include "StateMachine.hpp"   // needed to inheritance from StateMachine

namespace brain
{
namespace sender
{

class BELogicSM final : public StateMachineBase
{
public:
    using StateMachineBase  = common::utils::StateMachine;
    using SenderManager     = brain::sender_manager::SenderManager;
    using TimerTypes        = SenderManager::TimerTypes;
    using TimersVectorPairs = SenderManager::TimersVectorPairs;
    using TimerData         = std::pair<uint16_t, BE_EVENTS>;

    /**
     * @brief        Constructor
     * @param[in]    senderManager - reference to senderManager object
     * @param[in]    timersVector - timers vector
     */
    BELogicSM(SenderManager& senderManager, const SenderManager::TimersVectorPairs& timersVector);

    PRIVATE_NOT_FOR_TESTS
    friend class brain::sender_manager::SenderManager;
    friend class BaseState;         // needed to access m_senderManager
    friend class StateInit;         // needed to access m_senderManager
    friend class StateConnecting;   // needed to access m_senderManager
    friend class StateReadyToSend;  // needed to access m_senderManager
    friend class StateWaitAck;      // needed to access m_senderManager
    friend class StateRetry;        // needed to access m_senderManager
    friend class StateDisabled;     // needed to access m_senderManager

    bool setSMEvent(BE_EVENTS event);
    bool reloadTimerTask(TimerTypes timerTimeout);

    static constexpr uint8_t MAX_RETRY_LIMIT = 3U;

    static constexpr uint16_t TIMER_WAIT_CONNECTION_UP_IN_SEC = 10U * 60U;
    static constexpr uint16_t TIMER_DATA_SENT_IN_SEC          = 10U;
    static constexpr uint16_t TIMER_ACK_WAIT_IN_SEC           = 2U;
    static constexpr uint16_t TIMER_RETRY_WAIT_IN_SEC         = 2U;
    static constexpr uint16_t TIMER_PERIODIC_SEND_EVET        = 5U;

    std::unordered_map<TimerTypes, TimerData> m_timers
        = {{TimerTypes::WAIT_FOR_CONNECTION_UP,
            {static_cast<uint16_t>(BELogicSM::TIMER_WAIT_CONNECTION_UP_IN_SEC), EVENT_CONNECTION_TIMEOUT}},
           {TimerTypes::DATA_SENT,
            {static_cast<uint16_t>(BELogicSM::TIMER_DATA_SENT_IN_SEC), EVENT_DATA_SENT_TIMEOUT}},
           {TimerTypes::ACK_OK_TIMEOT,
            {static_cast<uint16_t>(BELogicSM::TIMER_ACK_WAIT_IN_SEC), EVENT_ACK_OK_WITH_TO_EXPIRED}},
           {TimerTypes::RETRY_TIMEOT,
            {static_cast<uint16_t>(BELogicSM::TIMER_RETRY_WAIT_IN_SEC), EVENT_SEND_OLD_DATA}},
           {TimerTypes::PERIODIC_SEND_EVENT,
            {static_cast<uint16_t>(BELogicSM::TIMER_PERIODIC_SEND_EVET),
             EVENT_MAX /* Dummy event, not relevant for this timer type*/}}};

    uint8_t        m_maxRetryCounter{0U};
    SenderManager& m_senderManager;
};

}  // namespace sender
}  // namespace brain
