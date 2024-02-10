/**
 * @file
 * @brief     This file contains the definition of the EventsStorage class and its functionality
 */
#ifndef EVENTS_STORAGE_HPP
#define EVENTS_STORAGE_HPP

#include <array>
#include <functional>
#include <map>
#include <mutex>

#include "brain/config/BrainConfigConstants.hpp"
#include "brain/events/Event.hpp"
#include "common/counter_manager/CounterManager.hpp"
#include "common/utils/singleQueue/SmartPtrSingleQueue.hpp"
#include "common/utils/types/ConfigurationTypes.hpp"
#include "common/utils/types/string.hpp"
namespace common
{
namespace memory
{
class PersistentMemoryManagerInterface;
class PersistentMemoryFactory;
} // namespace memory
} // namespace common

using brain::events::EventPriority;
namespace brain
{
namespace sender
{
	constexpr size_t KBYTE = 1 << 10;
	constexpr size_t MBYTE = 1 << 20;
    typedef uint32_t MetadataKey;  

    struct EventsQueueParameters
    {
        size_t weight;
        size_t maxElements;
        size_t maxSize;
    };

    enum EventsQueueConfigParamIndexes : uint8_t
	{
        WEIGHT = 0U,
        MAX_ELEMENTS = 1U,
		MAX_SIZE = 2U,

        QUEUE_PARAMETERS_COUNT
	};

#pragma pack(push)
#pragma pack(1)
struct PersistentManagementParameters {
        MetadataKey headIndex{0U};
        MetadataKey tailIndex{0U};
        MetadataKey totalSize{0U};
    }; 
#pragma pack(pop)

	
  	constexpr EventsQueueParameters QueuePriorityCriticalDefaultParameters   {5U, 400U, MBYTE * 128U};    // EventPriority::Critical
	constexpr EventsQueueParameters QueuePriorityImportantDefaultParameters  {1U, 200U, MBYTE * 32U};     // EventPriority::Important
	constexpr EventsQueueParameters QueuePriorityNormalDefaultParameters     {1U, 80U,  MBYTE * 16U};     // EventPriority::Normal
	constexpr EventsQueueParameters QueuePriorityLowDefaultParameters        {1U, 40U,  KBYTE * 800U};    // EventPriority::Low

    constexpr char PersistentManagementKeyCritical[] = "perManagementKeyCritical";
    constexpr char PersistentManagementKeyImportant[] = "perManagementKeyImportant";
    constexpr char PersistentManagementKeyNormal[] = "perManagementKeyNormal";
    constexpr char PersistentManagementKeyLow[] = "perManagementKeyLow";

    constexpr MetadataKey PerManagementParamDefaultHeadIndex = 0U;
    constexpr MetadataKey PerManagementParamDefaultTailIndex = 0U;
    constexpr MetadataKey PerManagementParamDefaultTotalSize = 0U;

using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;

/**
 * @class   EventsStorage
 * @brief   The EventsStorage class defines the events persistent storage behivior in the system.
 */
class EventsStorage
{

public:
    using PersistentMemoryFactoryPtr          = std::shared_ptr<common::memory::PersistentMemoryFactory>;
    using PersistentMemoryManagerInterfacePtr = std::shared_ptr<common::memory::PersistentMemoryManagerInterface>;

    using Event             = brain::events::Event;
    using EventQueueType    = common::SmartPtrSingleQueue<Event>;
    using EventQueuePtrType = std::unique_ptr<EventQueueType>;
    using EventCounter      = common::counters::EventCounter;
    using CounterManagerPtr = std::shared_ptr<common::counters::CounterManager>;
    using ConfigurationPtr  = common::configuration::Pointer;

    /**
     * @brief   Constructor
     * @param   persistentMemoryFactory - factory for creating persistent memory objects
     * @param   CounterManagerPtr const debugCounters
     */
    EventsStorage(
        PersistentMemoryFactoryPtr persistentMemoryFactory,
        CounterManagerPtr const debugCounters,
        ConfigurationPtr config);

    /**
     * @brief   Constructor
     * @param   std::vector<PersistentMemoryManagerInterfacePtr>& vecOfStoragePtr
     * @param   CounterManagerPtr const debugCounters
     * @param   ConfigurationPtr config
     */
    EventsStorage(
        std::vector<PersistentMemoryManagerInterfacePtr>& vecOfStoragePtr,
        CounterManagerPtr const debugCounters,
        ConfigurationPtr config);

    /**
	 * @brief   Destructor
	 */
    virtual ~EventsStorage();

    /**
     * @brief    default copy constructor
     */
    EventsStorage(const EventsStorage& other) = delete;

    /**
     * @brief    default move constructor
     */
    EventsStorage(EventsStorage&& other) = delete;

    /**
    * @brief    default copy assignment operator
    */
    EventsStorage& operator=(EventsStorage const&) = delete;

    /**
    * @brief   default move assignment operator
    */
    EventsStorage& operator=(EventsStorage&&) = delete;

    /**
	 * @brief   init the counters
     * @param   CounterManagerPtr
	 */
    void InitCounters(CounterManagerPtr const debugCounters);

    /**
    * @brief   Check if the Ram Queue is full,
    * @param   EventPriority
    * @return  bool - true iff the Priority Ram queue is full.
    */
    inline bool IsRamQueuePriorityFull(EventPriority const Priority) const
	{
	    return m_ramQueues[Priority]->IsFull();
	}
	
    /**
     * @brief   Store event in storage
     * @param   std::unique_ptr<Event> eventToStore
     * @return  bool - true iff event stored successfully
     */
    bool StoreEvent(std::unique_ptr<Event> eventToStore);

    /**
     * @brief   Flushes the RAM event queue to the storage
     */
    void FlushRAMEvents();

    /**
     * @brief   Delete all events from storage
     */
    void DeleteAllEvents();

    /**
     * @brief   Enable persistent storage
     */
    void Enable();

    /**
     * @brief   Disable persistent storage
     */
    void Disable();

    /**
     * @brief   Check if the storage is empty
     * @return  bool - true if event storage is empty
     */
    inline bool IsStorageEmpty() const noexcept
    {
        if(!m_isPmEnable)
        {
            return IsRamStorageEmpty();
        }
        return IsPersistentStorageEmpty();
    }

    /**
     * @brief   Check if the persistent storage is empty
     * @return  bool - true iff storage is empty
     */
    inline bool IsPersistentStorageEmpty() const noexcept
    {
        uint32_t totalSize = 0U;
        for (int32_t priority = 0; priority < EventPriority::NUM_OF_EVENT_PRIORITIES; priority++)
        {
            totalSize += m_persistentManagementParameters[static_cast<EventPriority>(priority)].totalSize;
        }

        return (0 == totalSize);
    }

        /**
     * @brief   Check if the ram_queues are empty
     * @return  bool - true if ram queue is empty
     */
    inline bool IsRamStorageEmpty() const noexcept
    {
        bool isEmpty = true;
        for (int32_t priority = 0; priority < EventPriority::NUM_OF_EVENT_PRIORITIES; priority++)
        {
            isEmpty = isEmpty && m_ramQueues[static_cast<EventPriority>(priority)]->IsEmpty();
        }
        return isEmpty;
    }

    /**
     * @brief   Check if the storage is empty, by checking if head == tail
     *          Wrapp around problem of the indexes will not give wrong result, since there is no situation that tail index was wrapped
     *          and reached to head, while the whole contect is full, since the index value is 2^32 and the capacity of the PM is much smaller.
     * @return  bool - true iff storage is empty
     */
    inline bool IsStorageEmptyByPriority(EventPriority priority) const noexcept
    {
        auto& parameters = m_persistentManagementParameters[priority];
        auto isEmpty = parameters.headIndex == parameters.tailIndex;

        // Just for debug check
        if( (isEmpty && (parameters.totalSize > PerManagementParamDefaultTotalSize) ) ||
            (!isEmpty && (PerManagementParamDefaultTotalSize == parameters.totalSize) ) )
        {
            storageEmptyByPriorityLog(parameters);
            common::counters::IncreaseCounter(m_fatal_error_empty_mismatch);
        }
        
        return isEmpty;
    }

    /**
     * @brief   Check if a given priority's queue is empty (including RAM)
     * @param   EventPriority priority
     * @return  bool - true iff storage is empty
     */
    inline bool IsRamQueuePriorityEmpty(EventPriority priority) const
    {
        return ((nullptr != m_ramQueues[priority]) && m_ramQueues[priority]->IsEmpty()
                && (0UL != m_numberOfPriorityEventsInPersistentStorage[priority]));
    }

    /**
    * @brief    Get the number of event in the storage
    * @return   uint64_t number of events
    */
    inline uint64_t GetNumberOfEvents() const noexcept
    {
        uint64_t totalEvents = 0U;

        for (uint32_t priority = 0U; priority < EventPriority::NUM_OF_EVENT_PRIORITIES; priority++)
        {
            auto tail = m_persistentManagementParameters[static_cast<EventPriority>(priority)].tailIndex;
            auto head = m_persistentManagementParameters[static_cast<EventPriority>(priority)].headIndex;

            if(tail >= head)
            {
                totalEvents+=(tail-head)/2; //devide by 2 since each event has 2 records
            }
            else // for wrapp around scenario
            {
                totalEvents+=(head-tail)/2; //devide by 2 since each event has 2 records
            }
        }
        return totalEvents;
    }

    /**
     * @brief   verify that there is enough storage in priority queue and ram queue
     *          in order to save useless event creation (which may raise the CPU)
     * @param   EventPriority const priority (default normal)
     * @return  true if there is enough storage for creating an event, false otherwise.
     */
    inline bool HasStorageAvailableForEvent(EventPriority const priority, size_t const sizeOfEvent) const
    {
        if(!m_isPmEnable)
        {
            return true;
        }
        return ((GetPriorityQueueAvailableStorage(priority) >= sizeOfEvent) && (!IsRamQueuePriorityFull(priority)));        
    }

    /**
     * @brief   Get the next event
     * @param   outEvent - output
     * @return  true iff event has been popped
     */
    bool GetNextEvent(std::unique_ptr<Event>& outEvent);

    /**
     * @brief   Gets the available storage size for the given  priority.
     * @param   EventPriority priority - the given priority
     * @return  size_t - available storage
     */
    inline size_t GetPriorityQueueAvailableStorage(EventPriority priority) const noexcept
    {
        if(!m_isPmEnable)
        {
            return m_queuePriorityParameters[priority].maxSize;
        }

        size_t sizeLeft = 0U;

        if( m_queuePriorityParameters[priority].maxSize  > m_persistentManagementParameters[priority].totalSize)
        {
            sizeLeft = m_queuePriorityParameters[priority].maxSize - m_persistentManagementParameters[priority].totalSize;
        }

        return sizeLeft;
    }


#ifndef TESTS
protected:
#endif
    /**
     * @brief   Persistency manager wrapper for reading
     * @param   Event::BufferType& returnBuffer
     * @param   PersistentMemoryManagerInterfacePtr perMngr
     * @param   common::types::string const& entryKey
     * @param   MetadataKey entrySize
     * @return  bool -  true for successe otherwise false.
     */
    bool getEventDataFromPersistencyManager(Event::BufferType&                      returnBuffer,
                                            PersistentMemoryManagerInterfacePtr perMngr,
                                            common::types::string const&            entryKey,
                                            MetadataKey                             entrySize) const;

    /**
     * @brief   Get event from storage
     * @param   EventPriority const priority - Event priority
     * @param   std::unique_ptr<Event>& outEvent - output value for the popped event
     * @return  true iff event is successfully popped
     */
    bool getEventFromPerMem(EventPriority const priority, std::unique_ptr<Event>& outEvent);

    /**
     * @brief   Get event from RAM Queue
     * @param   EventPriority const priority - the event priority
     * @param   std::unique_ptr<Event>& outEvent - buffer for the event
     * @return  isSucceed
     */
    bool getEventFromRam(EventPriority const priority, std::unique_ptr<Event>& outEvent);

#ifndef TESTS
private:
#endif
    void storageEmptyByPriorityLog(brain::sender::PersistentManagementParameters const& parameters) const;

    void init(CounterManagerPtr const debugCounters, ConfigurationPtr config);

    void loadQueueParams(ConfigurationPtr config);

    /**
	 * @brief   init the management parameters of the persistent event
	 */
    void InitPersistentMananagementParameters();

    inline void ResetPersistentManagementParameters(uint8_t priority) noexcept;

    bool storeEventInPersistentStorage(std::unique_ptr<Event> eventToStore);

    inline bool StoreManagementKeys(EventPriority priority, MetadataKey head, MetadataKey tail, MetadataKey totalSize);

    void setNumberOfEvents();

    /**
	 * @brief   Set the Weights counters to the initial values
	 */
    void setPriorityQueueWeightsRemained() noexcept;

    /**
	 * @brief   Delete all events for priority and initialize the relevant data
	 */
    void DeleteAllEventsByPriority(uint8_t priority) noexcept;

    /**
     * @var     std::vector<PersistentMemoryManagerInterfacePtr> m_priorityQueuePerMemPtrVec
     * @brief   vector of all priority DB's
     */
    std::vector<PersistentMemoryManagerInterfacePtr> m_perMemQueues;
   
    /**
     * @var     std::array<PersistentManagementParameters, EventPriority::NUM_OF_EVENT_PRIORITIES> m_persistentManagementParameters
     * @brief   Array of the management values (head,tail and total size) per priority
     */
    std::array<PersistentManagementParameters, EventPriority::NUM_OF_EVENT_PRIORITIES> m_persistentManagementParameters;

    /**
     * @var     m_numberOfPriorityEventsInPersistentStorage
     * @brief   Number of events in the persistent storage in each queue
     */
    std::array<size_t, EventPriority::NUM_OF_EVENT_PRIORITIES> m_numberOfPriorityEventsInPersistentStorage;

    /**
     * @var     std::mutex m_storageMutex
     * @brief   Mutex for storage operations
     */
    std::mutex m_storageMutex;

    /**
     * @var     std::array<std::atomic<size_t>, EventPriority::NUM_OF_EVENT_PRIORITIES> m_queuesAvailableStorage
     * @brief   queues for available storage
     */
    std::array<std::atomic<size_t>, EventPriority::NUM_OF_EVENT_PRIORITIES> m_queuesAvailableStorage;
    
    /**
     * @var     EventQueuePtrType m_ramQueues[EventPriority::NUM_OF_EVENT_PRIORITIES]
     * @brief   ram queues between the analyzing thread and the storing thread
     */
    EventQueuePtrType m_ramQueues[EventPriority::NUM_OF_EVENT_PRIORITIES];

    /**
     * @var     std::array<size_t, EventPriority::NUM_OF_EVENT_PRIORITIES> m_priorityQueueWeights
     * @brief   Runtime array for the priority queue weight calculation
     */
    std::array<size_t, EventPriority::NUM_OF_EVENT_PRIORITIES> m_weightsRemainedQueues;

    std::shared_ptr<EventCounter> m_enqueueRAMCounter;
    std::shared_ptr<EventCounter> m_dequeuedRAMCounter;
    std::shared_ptr<EventCounter> m_failedFlushCounter;
    std::shared_ptr<EventCounter> m_pushCounter;
    std::shared_ptr<EventCounter> m_popCounter;
    std::shared_ptr<EventCounter>  m_amountOfFlashedEventsCounter;
    std::shared_ptr<EventCounter>  m_fatal_error_delete_pm;
    std::shared_ptr<EventCounter>  m_fatal_error_empty_mismatch;
    std::shared_ptr<EventCounter> m_failEnqueueRAMErrCounter;

    std::array<std::shared_ptr<EventCounter>, EventPriority::NUM_OF_EVENT_PRIORITIES> m_persistentMemorySize;
    std::array<std::shared_ptr<EventCounter>, EventPriority::NUM_OF_EVENT_PRIORITIES> m_enqueueSuccessCounters;
    std::array<std::shared_ptr<EventCounter>, EventPriority::NUM_OF_EVENT_PRIORITIES> m_enqueueFailCounters;
    std::array<size_t, EventPriority::NUM_OF_EVENT_PRIORITIES> m_ramQueuesEventSize = { 0 };

    std::array<EventsQueueParameters, EventPriority::NUM_OF_EVENT_PRIORITIES>     m_queuePriorityParameters;
    std::array<std::string, EventPriority::NUM_OF_EVENT_PRIORITIES>               m_persistentManagementKeys;
    static std::map<EventPriority, brain::config_keys::ConfigKeyType const> const s_eventQueueParamsCofigKeys;

    std::function<bool(EventPriority const,std::unique_ptr<Event>&)> m_getEventFunc;
    bool m_isPmEnable{false};
};
} //namespace sender
} //namespace brain

#endif // EVENTS_STORAGE_HPP
