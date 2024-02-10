#pragma once
/**
 * @file MessageRepositoryPriorityQueue
 * @brief Implements a message repository via priority queue, using weighted round robin logic in the Pop operation.
 *
 * This class implements the message repository interface, using a weighted round robin (WRR) algorithm to define the
 * dequeuing / pop order. Can also use persistent memory to save events for both preparation to shutdown flow and
 * steady state work.
 *
 * @extends MessageRepositoryInterface
 */
#include <array>
#include "common/utils/singleQueue/SmartPtrSingleQueue.hpp"
#include "interface/MessageRepository.hpp"
#include "common/counter_manager/CounterManager.hpp"
#include "brain/events/EventPriority.hpp"
namespace brain
{
namespace sender
{
class EventsStorage;
}  // namespace sender

using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;
namespace messageRepository
{
class MessageRepositoryPriorityQueue final : public MessageRepositoryInterface
{
public:
    using EventStorageUPtr = std::unique_ptr<brain::sender::EventsStorage>;
    using Queue            = common::SmartPtrSingleQueue<MessageRepositoryInterface::Message>;  // Message defined at MessageRepositoryInterface                                                             // MessageRepositoryInterface
    using MessageQueueUptr = std::unique_ptr<Queue>;
    using CounterManagerPtr = std::shared_ptr<common::counters::CounterManager>;
    using EventCounter               = common::counters::EventCounter;
    
    /**
     * @brief Constructor of MessageRepositoryPriorityQueue.
     */
    explicit MessageRepositoryPriorityQueue(CounterManagerPtr  debugCounters , EventStorageUPtr eventStorageUPtr = nullptr );  // TODO need to add support to persist option

    /**
     * @brief Initialize the message repo class with maximun number of priorities.
     *
     * @param[in] MessageRepositoryParams Configure parameters for each priority level.
     * @note      Index 0 of the vector refers to the highest priority and the last index refers to the lowest priority.
     * @return    true on success, else false.
     */
    bool Init(const std::vector<MessageRepositoryParameters>& MessageRepositoryParams) override;

    /**
     * @brief Pushes given message data into the repository.
     *
     * @note message should not be used after push.
     *
     * @param[in] message  Message to be inserted into the repository
     * @param[in] priority Priority of the message
     * @return    true on success, else false.
     */
    bool Push(MessagePtr&& message, uint8_t priority) override;

    /**
     * @brief Pops a contained message and emplaces it into a given location.
     *
     * @note should use std::unique_ptr::swap to make sure emplacement is in O(1).
     *
     * @param[out] message The given location for a loaded message.
     * @return     true on success means there is a message from any priority, else false.
     */
    bool Pop(MessagePtr& message) override;

private:
    bool areAllRamQueueEmpty();

    uint64_t                      m_maxPriorities{0};
    std::vector<MessageQueueUptr> m_ramQueues;
    std::vector<size_t>           m_weightsQueuesConfigured;
    std::vector<size_t>           m_weightsQueuesRemained;
    std::shared_ptr<common::counters::CounterManager>                m_counters;
    EventStorageUPtr              m_eventStorage;  // TODO need to add support to persist option
    std::vector<std::shared_ptr<EventCounter>> m_enqueueSuccessCounters;
    std::vector<std::shared_ptr<EventCounter>> m_enqueueFailCounters;
    std::shared_ptr<EventCounter>              m_dequeueCounter;
};
}  // namespace messageRepository
}  // namespace brain