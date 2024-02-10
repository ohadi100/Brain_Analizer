#include "MessageRepositoryPriorityQueue.hpp"
#include "brain/sender/EventsStorage.hpp"
#include "common/counter_manager/CounterNames.hpp"

using brain::messageRepository::MessageRepositoryPriorityQueue;
using brain::sender::EventsStorage;


MessageRepositoryPriorityQueue::MessageRepositoryPriorityQueue(CounterManagerPtr debugCounters,
                                                               EventStorageUPtr  eventStorageUPtr)
  : m_counters(debugCounters)
  , m_eventStorage(std::move(eventStorageUPtr))
{
}

bool
MessageRepositoryPriorityQueue::Init(const std::vector<MessageRepositoryParameters>& MessageRepositoryParams)
{
    m_ramQueues.clear();
    m_weightsQueuesConfigured.clear();
    m_weightsQueuesRemained.clear();
    m_maxPriorities = MessageRepositoryParams.size();

    uint32_t priority = 0U;
    for (auto const& vec : MessageRepositoryParams)
    {
        m_ramQueues.emplace_back(std::make_unique<Queue>(vec.maxElements));
        m_weightsQueuesConfigured.emplace_back(vec.weight);

        m_enqueueSuccessCounters.emplace_back(
            m_counters->CreateCounter(common::counters::debug::SUCCESS_ENQUEUE_EVENT_TO_WRR_QUEUE(priority),
                                      EventCounterLevelType::COUNTER_DEBUG));

        m_enqueueFailCounters.emplace_back(
            m_counters->CreateCounter(common::counters::debug::FAIL_ENQUEUE_EVENT_TO_WRR_QUEUE(priority), 
                                      EventCounterLevelType::COUNTER_DEBUG));

        priority++;
    }

    m_dequeueCounter = m_counters->CreateCounter(common::counters::debug::DEQUEUED_RAM_EVENTS_COUNTER_NAME, 
                                     EventCounterLevelType::COUNTER_DEBUG);

    m_weightsQueuesRemained = m_weightsQueuesConfigured;
    return !MessageRepositoryParams.empty();  // if the supplied vector is empty return false
}

bool
MessageRepositoryPriorityQueue::Push(MessagePtr&& message, uint8_t priority)
{
    bool result{false};

    if (priority >= m_maxPriorities)
    {
        return result;
    }

    if (m_ramQueues[priority]->Enqueue(std::move(message)))
    {
        common::counters::IncreaseCounter(m_enqueueSuccessCounters[priority]);
        result = true;
    }
    else
    {
        common::counters::IncreaseCounter(m_enqueueFailCounters[priority]);
    }

    return result;
}

// Implemented with WWR logic
bool
MessageRepositoryPriorityQueue::Pop(MessagePtr& message)
{
    size_t priority{0};

    for (; priority < m_ramQueues.size(); ++priority)
    {
        if ((0U != m_weightsQueuesRemained[priority]) && m_ramQueues[priority]->Dequeue(message))
        {
            common::counters::IncreaseCounter(m_dequeueCounter);
            --m_weightsQueuesRemained[priority];
            return true;
        }
    }

    // At this point, no message found, either because weight is equal to 0, or no message exist in the m_ramQueues.
    // Need to reset the weights and if there is message in the RAM Q, run again the pop method.

    m_weightsQueuesRemained = m_weightsQueuesConfigured;

    return areAllRamQueueEmpty() ? false : Pop(message);
}

bool
MessageRepositoryPriorityQueue::areAllRamQueueEmpty()
{
    for (auto const& loop : m_ramQueues)
    {
        if (!loop->IsEmpty())
        {
            return false;
        }
    }

    return true;
}