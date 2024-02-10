/**
 * @file
 * @brief     This file contains the definition of the Sender manager class and its functionality
 */
#pragma once

#include <atomic>
#include <memory>
#include <unordered_map>
#include <vector>
#include "brain/utils/TestsAdapters.hpp"
#include "common/utils/timer/Timer.hpp"  // needed to static values from Timer
#include "common/utils/types/ConfigurationTypes.hpp"
#include "common/utils/types/MessageRepositoryTypes.hpp"

class PublisherInterface;

namespace common
{
namespace thread_handler
{
class Reactor;
}  // namespace thread_handler
namespace counters
{
class CounterManager;
class EventCounter;
}  // namespace counters
namespace memory
{
class PersistentMemoryFactory;
}  // namespace memory
}  // namespace common

namespace brain
{
namespace publishers
{
namespace utils
{
class ExceededMessageSizeCheck;
}  // namespace utils
}  // namespace publishers
namespace sender
{
class BELogicSM;
class BaseState;
class StateInit;
class Creditor;
class EventsStorage;
class BufferType;
}  // namespace sender

namespace message_serialize
{
class MessageSerialize;
}
namespace sender_manager
{
class SenderManager
{
public:
    using ExceededMessageSizeCheck = brain::publishers::utils::ExceededMessageSizeCheck;

    using BELogicSM     = brain::sender::BELogicSM;
    using BufferType    = brain::sender::BufferType;
    using Creditor      = brain::sender::Creditor;
    using EventsStorage = brain::sender::EventsStorage;

    using MessageSerialize = brain::message_serialize::MessageSerialize;

    using CounterManager          = common::counters::CounterManager;
    using EventCounter            = common::counters::EventCounter;
    using PersistentMemoryFactory = common::memory::PersistentMemoryFactory;
    using Reactor                 = common::thread_handler::Reactor;

    using TimerRegisterKey = common::Timer::TimerRegisterKey;

    using PersistentMemoryFactoryPtr  = std::shared_ptr<PersistentMemoryFactory>;
    using CounterManagerPtr           = std::shared_ptr<CounterManager>;
    using ReactorPtr                  = std::shared_ptr<Reactor>;
    using CreditorUPtr                = std::unique_ptr<Creditor>;
    using MessageSerializePtr         = std::unique_ptr<MessageSerialize>;
    using ExceededMessageSizeCheckPtr = std::shared_ptr<ExceededMessageSizeCheck>;

    using ConfigurationPtr = common::configuration::Pointer;
    using EventCounterePtr = std::shared_ptr<EventCounter>;

    using PublisherUPtr        = std::unique_ptr<PublisherInterface>;
    using MessageRepositoryPtr = brain::messageRepository::MessageRepositoryPtr;

    enum class TimerTypes : uint8_t
    {
        WAIT_FOR_CONNECTION_UP,  // Timeout for waiting to connection establishment with the BE
        DATA_SENT,               // Timeout to wait for respond after sending data to BE
        ACK_OK_TIMEOT,           // Timeout before sending the next new data
        RETRY_TIMEOT,            // Timeout before sending the previous data
        PERIODIC_SEND_EVENT      // Timer interval of periodic send event
    };

    using TimersVectorPairs = std::vector<std::pair<TimerTypes, uint16_t>>;

    /**
     * @brief        SenderManager Constructor
     * @param[in]    persistentMemoryFactory persistent factory pointer
     * @param[in]    debugCounters debug counter pointer
     * @param[in]    configuration configuration pointer
     * @param[in]    reactor reactor pointer with ability to trigger on tasks with it own thread context
     * @param[in]    msgRepository to communicate with engines
     * @param[in]    creditor for manage credit
     * @param[in]    publisher for send data to the BE
     * @param[in]    exceededMessageSizeCheck to manage limit size of the BE
     * @param[in]    timersVector configurations for SM timeouts
     */
    SenderManager(PersistentMemoryFactoryPtr       persistentMemoryFactory,
                  CounterManagerPtr                debugCounters,
                  ConfigurationPtr                 configuration,
                  ReactorPtr                       reactor,
                  MessageRepositoryPtr             msgRepository,
                  CreditorUPtr                     creditor,
                  PublisherUPtr                    publisher,
                  ExceededMessageSizeCheckPtr      exceededMessageSizeCheck,
                  TimersVectorPairs                timersVector    = {});
    virtual ~SenderManager();

    /**
     * @brief    default copy constructor
     */
    SenderManager(const SenderManager& other) = delete;

    /**
     * @brief    default move constructor
     */
    SenderManager(SenderManager&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    SenderManager& operator=(SenderManager const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    SenderManager& operator=(SenderManager&&) = delete;

    /**
     * @brief   Send new message (event)
     *
     * @return  true on success, else false
     */
    bool SendMessage();

    /**
     * @brief   Re-send the last message that was sent
     *
     * @return  true on success, else false
     */
    bool ReSendMessage();

    /**
     * @brief   Prepare component for shutdown
     * TODORan analyze what need to be implement here
     */
    void PrepareToShutDown();

    /**
     * @brief   Cancel preparations for shutdown
     * TODORan analyze what need to be implement here
     */
    void CancelPrepareToShutDown();

    /**
     * @brief   Change sender mode to enable
     */
    void Enable();

    /**
     * @brief   Change sender mode to disable
     */
    void Disable();

    /**
     * @brief       Callback function that will handle the event that sent by the publisher
     *
     * @param[in]   event The event that need to be handle.
     */
    void PublisherCallback(uint8_t event);

    /**
     * @brief   Indicate the enable state of the module
     *
     * @return  true on success, else false
     */
    inline bool
    IsEnabled() const
    {
        return m_isEnabled;
    };

    PRIVATE_NOT_FOR_TESTS
    friend class brain::sender::BELogicSM;
    friend class brain::sender::BaseState;  // need access to m_publisher and m_creditor
    friend class brain::sender::StateInit;  // need access to m_publisher

    enum class MessageSendState : uint8_t
    {
        POP_DATA,
        EXCEED_MSG_SIZE,
        CREDIT_VALIDATION,
        SEND_TO_PUBLISHER
    };

    inline void      initializePublisherEventTranslator(void);
    bool             cancelLastTimer();
    bool             cancelPeriodicTimer();
    void             setReactorTask(uint8_t event) const;
    TimerRegisterKey setReactorTimerTask(uint8_t event, uint16_t time);
    void             setPeriodicSendEventTask();
    inline bool      checkCreditAvailableToSendMsg(size_t reportSizeBytes) const;

    std::unique_ptr<BELogicSM>     m_beLogicSM;
    std::unique_ptr<EventsStorage> m_eventsStorage;
    ReactorPtr                     m_reactor;
    MessageRepositoryPtr           m_msgRepository;
    CreditorUPtr                   m_creditor;
    PublisherUPtr                  m_publisher;
    ExceededMessageSizeCheckPtr    m_exceededMessageSizeCheck;
    
    std::unique_ptr<std::vector<uint8_t>> m_poppedData;
    std::shared_ptr<std::vector<uint8_t>> m_msgToBeSend;
    MessageSendState                      m_sendState{MessageSendState::POP_DATA};
    std::atomic<TimerRegisterKey>         m_lastTimer{common::Timer::INVALID_TIMER_REGISTRATION_KEY};
    TimerRegisterKey                      m_periodicTimer{common::Timer::INVALID_TIMER_REGISTRATION_KEY};
    std::unordered_map<uint8_t, uint8_t>  m_publisherEventTranslator;
    EventCounterePtr                      m_reportCounter;

    bool              m_shouldSerialize{false};
    uint16_t          m_periodicSendEventIntervalSec{5U};
    std::atomic<bool> m_isEnabled{false};
};

}  // namespace sender_manager
}  // namespace brain