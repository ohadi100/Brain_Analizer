#include "SenderManager.hpp"
#include "EventsStorage.hpp"
#include "brain/events/Event.hpp"
#include "brain/events/EventPriority.hpp"
#include "brain/messageRepository/MessageRepositoryPriorityQueue.hpp"
#include "brain/sender/BELogicSM.hpp"
#include "brain/sender/Creditor.hpp"
#include "brain/sender/publishers/interface/PublisherInterface.hpp"
#include "brain/utils/vehicle_data/VehicleData.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/counter_manager/counters/EventCounter.hpp"
#include "common/thread_handler/Reactor.hpp"
#include "common/utils/logger/Logger.hpp"
#include "common/utils/stateMachine/StateMachine.hpp"
#include "publishers/utils/message_size_check/ExceededMessageSizeCheck.hpp"
#include "sender/BELogicStates.hpp"

using brain::brain_vehicle_data::VehicleData;
using brain::message_serialize::MessageSerialize;

using brain::sender_manager::SenderManager;
namespace brain
{
namespace sender_manager
{
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;
}  // namespace sender_manager
}  // namespace brain


SenderManager::SenderManager(PersistentMemoryFactoryPtr       persistentMemoryFactory,
                             CounterManagerPtr                debugCounters,
                             ConfigurationPtr                 configuration,
                             ReactorPtr                       reactor,
                             MessageRepositoryPtr             msgRepository,
                             CreditorUPtr                     creditor,
                             PublisherUPtr                    publisher,
                             ExceededMessageSizeCheckPtr      exceededMessageSizeCheck,
                             TimersVectorPairs                timersVector)
  : m_beLogicSM(std::make_unique<BELogicSM>((*this), timersVector))
  , m_eventsStorage(std::make_unique<EventsStorage>(persistentMemoryFactory, debugCounters, configuration))
  , m_reactor(reactor)
  , m_msgRepository(msgRepository)
  , m_creditor(std::move(creditor))
  , m_publisher(std::move(publisher))
  , m_exceededMessageSizeCheck(exceededMessageSizeCheck)
  , m_periodicSendEventIntervalSec(m_beLogicSM->m_timers[TimerTypes::PERIODIC_SEND_EVENT].first)
{
    initializePublisherEventTranslator();

    m_msgToBeSend.reset();

    m_reportCounter
        = debugCounters->CreateCounter(common::counters::debug::REPORTS_COUNTER, EventCounterLevelType::COUNTER_DEBUG);

    // Reactor will be active as long as Sender object exists (Both in Enable and Disable mode)
    if (!m_reactor->Start())
    {
        LOG_WARNING << "The Sender reactor thread may not be running" << LOG_NOOP;
    }
}

SenderManager::~SenderManager()
{
    m_reactor->Stop();
}

void
SenderManager::PublisherCallback(uint8_t event)
{
    auto findResult = m_publisherEventTranslator.find(event);

    LOG_DEBUG << "SENDER_DBG: Received event=" << std::to_string(static_cast<uint32_t>(event)) << " from Publisher"
              << ", find result=" << (findResult != m_publisherEventTranslator.end() ? "OK" : "ERROR") << LOG_NOOP;

    if (findResult != m_publisherEventTranslator.end())
    {
        LOG_DEBUG << "SENDER_DBG: Received event=" << std::to_string(static_cast<uint32_t>(event)) << " from Publisher"
                  << LOG_NOOP;
        setReactorTask(findResult->second);
    }

    LOG_ERROR << "SENDER_DBG: Received unknown event= " << std::to_string(static_cast<uint32_t>(event))
              << "from Publisher" << LOG_NOOP;
}

void
SenderManager::setReactorTask(uint8_t event) const
{
    auto func = [this, event]() {
        m_beLogicSM->setSMEvent(static_cast<brain::sender::BE_EVENTS>(event));
    };
    m_reactor->Exec(func);
}

common::thread_handler::Reactor::TimerRegisterKey
SenderManager::setReactorTimerTask(uint8_t event, uint16_t time)
{
    auto func = [this, event, time]() {
        LOG_DEBUG << "SENDER_DBG: timer expired for event=" << std::to_string(static_cast<uint32_t>(event))
                  << ",time=" << time << LOG_NOOP;
        m_beLogicSM->setSMEvent(static_cast<brain::sender::BE_EVENTS>(event));
        m_lastTimer = 0;
    };
    m_lastTimer = m_reactor->ExecTimeout(func, time * 1000U, false);
    LOG_DEBUG << "SENDER_DBG: timer registered=" << std::to_string(static_cast<uint32_t>(event)) << ",time=" << time
              << ", m_lastTimer=" << m_lastTimer << LOG_NOOP;
    return m_lastTimer;
}

void
SenderManager::setPeriodicSendEventTask()
{
    auto func = [this]() {
        LOG_DEBUG << "SENDER_DBG: Chaning state to EVENT_SEND_DATA" << LOG_NOOP;
        m_beLogicSM->setSMEvent(brain::sender::BE_EVENTS::EVENT_SEND_DATA);
    };
    m_periodicTimer = m_reactor->ExecTimeout(func, m_periodicSendEventIntervalSec * 1000U, true);
    LOG_DEBUG << "SENDER_DBG: setPeriodicSendEventTask registered" << LOG_NOOP;
}

bool
SenderManager::cancelLastTimer()
{
    bool result{true};

    if (m_lastTimer)
    {
        LOG_DEBUG << "SENDER_DBG: timer cancelled=" << m_lastTimer << LOG_NOOP;
        result      = m_reactor->CancelTimeout(m_lastTimer);
        m_lastTimer = 0;
    }

    return result;
}

bool
SenderManager::cancelPeriodicTimer()
{
    bool result{true};

    if (m_periodicTimer)
    {
        LOG_DEBUG << "SENDER_DBG: periodic timer cancelled=" << m_lastTimer << LOG_NOOP;
        result      = m_reactor->CancelTimeout(m_periodicTimer);
        m_periodicTimer = 0;
    }

    return result;
}

bool
SenderManager::SendMessage()
{
    LOG_DEBUG << "SENDER_DBG: m_sendState =" << std::to_string(static_cast<uint32_t>(m_sendState)) << LOG_NOOP;

    // TODORan consider to implement it by StateMachine class
    if (MessageSendState::POP_DATA == m_sendState)
    {
        if (m_msgRepository->Pop(m_poppedData))
        {
            LOG_DEBUG << "SENDER_DBG: SendMessage Pop" << LOG_NOOP;
            
            m_msgToBeSend.reset();
            m_msgToBeSend = std::move(m_poppedData);

            m_sendState = MessageSendState::EXCEED_MSG_SIZE;
        }
    }

    if (MessageSendState::EXCEED_MSG_SIZE == m_sendState)
    {
        if (m_exceededMessageSizeCheck->IsValid(m_msgToBeSend->size()))
        {
            LOG_DEBUG << "SENDER_DBG: SendMessage m_exceededMessageSizeCheck->IsValid" << LOG_NOOP;
            m_sendState = MessageSendState::CREDIT_VALIDATION;
        }
        else
        {
            m_sendState = MessageSendState::POP_DATA;
        }
    }

    if (MessageSendState::CREDIT_VALIDATION == m_sendState)
    {
        if (checkCreditAvailableToSendMsg(m_msgToBeSend->size()))
        {
            LOG_DEBUG << "SENDER_DBG: SendMessage checkCreditAvailableToSendMsg" << LOG_NOOP;
            m_sendState = MessageSendState::SEND_TO_PUBLISHER;
        }
    }

    if (MessageSendState::SEND_TO_PUBLISHER == m_sendState)
    {
        if (m_publisher->SendMessage(m_msgToBeSend))
        {
            LOG_DEBUG << "SENDER_DBG: SendMessage SendMessage" << LOG_NOOP;
            common::counters::IncreaseCounter(m_reportCounter);
            m_sendState = MessageSendState::POP_DATA;
            return true;
        }
    }

    return false;
}

bool
SenderManager::ReSendMessage()
{
    m_sendState = MessageSendState::SEND_TO_PUBLISHER;
    return SendMessage();
}

bool
SenderManager::checkCreditAvailableToSendMsg(size_t reportSizeBytes) const
{
    uint64_t const availableCredits = m_creditor->GetByteCredit();
    if (reportSizeBytes <= availableCredits)
    {
        LOG_DEBUG << "Sufficient credits (Report size: " << reportSizeBytes
                  << " Available credits: " << availableCredits << ")" << LOG_NOOP;
        return true;
    }

    LOG_DEBUG << "Insufficient credits (Report size: " << reportSizeBytes << " Available credits: " << availableCredits
              << ")" << LOG_NOOP;
    return false;
}

void
SenderManager::initializePublisherEventTranslator(void)
{
    m_publisherEventTranslator = {{static_cast<uint8_t>(PublisherInterface::EventType::CONNECTED),
                                   static_cast<uint8_t>(brain::sender::BE_EVENTS::EVENT_CONNECTED)},
                                  {static_cast<uint8_t>(PublisherInterface::EventType::ACK_OK),
                                   static_cast<uint8_t>(brain::sender::BE_EVENTS::EVENT_ACK_OK)},
                                  {static_cast<uint8_t>(PublisherInterface::EventType::ACK_OK_WITH_TIMEOUT),
                                   static_cast<uint8_t>(brain::sender::BE_EVENTS::EVENT_ACK_OK_WITH_TO)},
                                  {static_cast<uint8_t>(PublisherInterface::EventType::RETRY),
                                   static_cast<uint8_t>(brain::sender::BE_EVENTS::EVENT_ACK_RETRY)},
                                  {static_cast<uint8_t>(PublisherInterface::EventType::RETRY_WITH_TIMEOUT),
                                   static_cast<uint8_t>(brain::sender::BE_EVENTS::EVENT_ACK_RETRY_WITH_TO)}};
}

void
SenderManager::Enable()
{
    m_isEnabled = true;

    // Start the periodic event of send message task
    setPeriodicSendEventTask();

    setReactorTask(brain::sender::BE_EVENTS::EVENT_CONNECT);
}

void
SenderManager::Disable()
{
    m_isEnabled = false;

    setReactorTask(brain::sender::BE_EVENTS::EVENT_DISABLE);
}

void
SenderManager::PrepareToShutDown()
{
    // TODORan what need to implement here?
}

void
SenderManager::CancelPrepareToShutDown()
{
    // TODORan what need to implement here?
}
