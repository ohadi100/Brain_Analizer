#include "EventsStorage.hpp"

#include "brain/config/BrainConfigConstants.hpp"

#include <DBNames.hpp>
#include <factory/PersistentMemoryFactory.hpp>
#include "common/configuration/Configuration.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/utils/logger/Logger.hpp"

#include <cstdlib>

using brain::sender::EventsStorage;
using brain::events::Event;
using namespace common::memory;
using brain::events::EventPriority;


static std::map<EventPriority, brain::config_keys::ConfigKeyType const>&&
initEventsStorageEventQueueParamsCofigKeys() noexcept
{
    static std::map<EventPriority, brain::config_keys::ConfigKeyType const> newMap{
        {EventPriority::Critical, brain::config_keys::SENDER_QUEUE_CRITICAL_PARAMS},
        {EventPriority::Important, brain::config_keys::SENDER_QUEUE_IMPORTANT_PARAMS},
        {EventPriority::Normal, brain::config_keys::SENDER_QUEUE_NORMAL_PARAMS},
        {EventPriority::Low, brain::config_keys::SENDER_QUEUE_LOW_PARAMS}};
    return std::move(newMap);
}
std::map<EventPriority, brain::config_keys::ConfigKeyType const> const EventsStorage::s_eventQueueParamsCofigKeys
    = initEventsStorageEventQueueParamsCofigKeys();

EventsStorage::EventsStorage(
    PersistentMemoryFactoryPtr persistentMemoryFactory,
    CounterManagerPtr const debugCounters,
    ConfigurationPtr config) :
    m_perMemQueues{persistentMemoryFactory->CreatePersistentMemory(PER_MEM_IDS_BRAIN_PRIORITY0_EVENTS),
                   persistentMemoryFactory->CreatePersistentMemory(PER_MEM_IDS_BRAIN_PRIORITY1_EVENTS),
                   persistentMemoryFactory->CreatePersistentMemory(PER_MEM_IDS_BRAIN_PRIORITY2_EVENTS),
                   persistentMemoryFactory->CreatePersistentMemory(PER_MEM_IDS_BRAIN_PRIORITY3_EVENTS)},
    m_queuePriorityParameters{
        brain::sender::QueuePriorityCriticalDefaultParameters,
        brain::sender::QueuePriorityImportantDefaultParameters,
        brain::sender::QueuePriorityNormalDefaultParameters,
        brain::sender::QueuePriorityLowDefaultParameters}
{
    init(debugCounters, config);
}

EventsStorage::EventsStorage(
    std::vector<PersistentMemoryManagerInterfacePtr>& vecOfStoragePtr,
    CounterManagerPtr const debugCounters,
    ConfigurationPtr config) :
    m_perMemQueues(vecOfStoragePtr),
    m_queuePriorityParameters{
        brain::sender::QueuePriorityCriticalDefaultParameters,
        brain::sender::QueuePriorityImportantDefaultParameters,
        brain::sender::QueuePriorityNormalDefaultParameters,
        brain::sender::QueuePriorityLowDefaultParameters}
{
    init(debugCounters, config);
}

void EventsStorage::init(CounterManagerPtr const debugCounters, ConfigurationPtr config)
{
    if (config)
    {
        loadQueueParams(config);
        std::ignore = config->GetValue(brain::config_keys::EVENT_STORAGE_PM_STATUS, m_isPmEnable);
        LOG_INFO << "Event Storage PM state: " << (true == m_isPmEnable ? "Enabled" : "Disabled") << LOG_NOOP;
    }

    if(m_isPmEnable)
    {
        m_getEventFunc = std::bind(&EventsStorage::getEventFromPerMem,this, std::placeholders::_1,std::placeholders::_2); 
    }
    else
    {
        m_getEventFunc = std::bind(&EventsStorage::getEventFromRam,this, std::placeholders::_1,std::placeholders::_2); 
    }

    m_ramQueues[EventPriority::Critical] = std::make_unique<EventQueueType>(m_queuePriorityParameters[EventPriority::Critical].maxElements);
    m_ramQueues[EventPriority::Important] = std::make_unique<EventQueueType>(m_queuePriorityParameters[EventPriority::Important].maxElements);
    m_ramQueues[EventPriority::Normal] = std::make_unique<EventQueueType>(m_queuePriorityParameters[EventPriority::Normal].maxElements);
    m_ramQueues[EventPriority::Low] = std::make_unique<EventQueueType>(m_queuePriorityParameters[EventPriority::Low].maxElements);

    m_weightsRemainedQueues[EventPriority::Critical] = m_queuePriorityParameters[EventPriority::Critical].weight;
    m_weightsRemainedQueues[EventPriority::Important] = m_queuePriorityParameters[EventPriority::Important].weight;
    m_weightsRemainedQueues[EventPriority::Normal] = m_queuePriorityParameters[EventPriority::Normal].weight;
    m_weightsRemainedQueues[EventPriority::Low] = m_queuePriorityParameters[EventPriority::Low].weight;

    m_persistentManagementKeys[EventPriority::Critical] = PersistentManagementKeyCritical;
    m_persistentManagementKeys[EventPriority::Important] = PersistentManagementKeyImportant;
    m_persistentManagementKeys[EventPriority::Normal] = PersistentManagementKeyNormal;
    m_persistentManagementKeys[EventPriority::Low] = PersistentManagementKeyLow;

    if(m_isPmEnable)
    {
        InitPersistentMananagementParameters();
    }
    

    if (debugCounters)
    {
        InitCounters(debugCounters);
    }
}

EventsStorage::~EventsStorage()
{
    try
    {
        FlushRAMEvents();
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "flush RAM events failed and got exception." << LOG_NOOP;
    }
}

void EventsStorage::InitCounters(CounterManagerPtr const debugCounters)
{
   
    m_failEnqueueRAMErrCounter = debugCounters->CreateCounter(common::counters::errors::FAILED_ENQUEUE_RAM_EVENTS_ERR_COUNTER_NAME,EventCounterLevelType::COUNTER_ERROR);
    m_fatal_error_delete_pm = debugCounters->CreateCounter(common::counters::errors::FATAL_ERROR_DELETE_PM,EventCounterLevelType::COUNTER_ERROR);
    m_fatal_error_empty_mismatch = debugCounters->CreateCounter(common::counters::errors::FATAL_ERROR_EMPTY_MISMATCH,EventCounterLevelType::COUNTER_ERROR);
    m_enqueueRAMCounter = debugCounters->CreateCounter(common::counters::debug::ENQUEUE_RAM_EVENTS_COUNTER_NAME, EventCounterLevelType::COUNTER_DEBUG);
    m_dequeuedRAMCounter = debugCounters->CreateCounter(common::counters::debug::DEQUEUED_RAM_EVENTS_COUNTER_NAME, EventCounterLevelType::COUNTER_DEBUG);
    m_failedFlushCounter = debugCounters->CreateCounter(common::counters::errors::FAILED_FLUSH_RAM_EVENTS_COUNTER_NAME, EventCounterLevelType::COUNTER_ERROR);
    m_pushCounter = debugCounters->CreateCounter(common::counters::debug::PUSH_COUNTER_NAME, EventCounterLevelType::COUNTER_DEBUG);
    m_popCounter = debugCounters->CreateCounter(common::counters::debug::POP_COUNTER_NAME, EventCounterLevelType::COUNTER_DEBUG);
    m_amountOfFlashedEventsCounter = debugCounters->CreateCounter(common::counters::info::AMOUNT_OF_FLUSHED_EVENTS_FROM_RAM_TO_PM, EventCounterLevelType::COUNTER_INFO);

    for (uint32_t priority = 0U; priority < static_cast<uint32_t>(EventPriority::NUM_OF_EVENT_PRIORITIES); ++priority)
    {
        m_persistentMemorySize[priority] = debugCounters->CreateCounter(common::counters::info::PM_SIZE(priority),
                                                                        EventCounterLevelType::COUNTER_INFO);
        m_enqueueSuccessCounters[priority]
            = debugCounters->CreateCounter(common::counters::debug::SUCCESS_ENQUEUE_EVENT_TO_WRR_QUEUE(priority),
                                           EventCounterLevelType::COUNTER_DEBUG);
        m_enqueueFailCounters[priority] = debugCounters->CreateCounter(
            common::counters::debug::FAIL_ENQUEUE_EVENT_TO_WRR_QUEUE(priority), EventCounterLevelType::COUNTER_DEBUG);
    }
}

void EventsStorage::loadQueueParams(ConfigurationPtr config)
{
    for (size_t priority = 0U; priority < EventPriority::NUM_OF_EVENT_PRIORITIES; priority++)
    {
        std::vector<uint32_t> queueParams;
        if (config->GetValue(s_eventQueueParamsCofigKeys.at(static_cast<EventPriority>(priority)), queueParams))
        {
            if (EventsQueueConfigParamIndexes::QUEUE_PARAMETERS_COUNT != queueParams.size())
            {
                LOG_WARNING << "Invalid number of parameters for key "
                            << s_eventQueueParamsCofigKeys.at(static_cast<EventPriority>(priority)) << LOG_NOOP;
                return;
            }

            m_queuePriorityParameters[priority] = {
                queueParams[EventsQueueConfigParamIndexes::WEIGHT],
                queueParams[EventsQueueConfigParamIndexes::MAX_ELEMENTS],
                queueParams[EventsQueueConfigParamIndexes::MAX_SIZE]};
        }
    }
}

bool EventsStorage::StoreEvent(std::unique_ptr<Event> eventToStore)
{
    LOG_VERBOSE << "Storing event" << LOG_NOOP;

    EventPriority const& priority = eventToStore->GetPriority();
    auto const& eventSize = eventToStore->GetSize();

    std::lock_guard<std::mutex> const lock(m_storageMutex);
    
    if (EventPriority::NUM_OF_EVENT_PRIORITIES <= priority)
    {
        LOG_WARNING << "StoreEvent: priority " << static_cast<int>(priority) << " is out of boundaries" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failEnqueueRAMErrCounter);
        return false;
    }

    //Check twice to prevent race (next time is in storeEventInPersistentStorage)
    //First time check before storing in the RAM storage the second check before storing in the persistent storage - maybe something changed in between
    if(m_isPmEnable)
    {
        if (!m_perMemQueues[priority]->IsEnabled())
        {
            LOG_WARNING << "Failed to store event in RAM storage because priority " << static_cast<int>(priority)
                        << " queue is disabled!" << LOG_NOOP;
            common::counters::IncreaseCounter(m_enqueueFailCounters[priority]);
            return false;
        }
    }

    if ((0U >= eventSize) || ((eventSize + m_ramQueuesEventSize[priority]) > GetPriorityQueueAvailableStorage(priority)))
    {
        static constexpr uint32_t MAX_EVENT_SIZE = KBYTE * 200U;
        if ((0U >= eventSize) || (MAX_EVENT_SIZE < eventSize))
        {

            LOG_WARNING << "Failed to store event in RAM storage because event size of buffer is 0 or less or higher "
                           "than max event size"
                        << LOG_NOOP;
        }
        else
        {
            LOG_WARNING << "Failed to store event in RAM storage because priority " << static_cast<int>(priority)
                        << " queue does not have enough storage!" << LOG_NOOP;
        }
        common::counters::IncreaseCounter(m_enqueueFailCounters[priority]);
        return false;
    }


    if (m_ramQueues[priority]->IsFull())
    {
        LOG_WARNING << "Failed to store event in RAM storage because priority " << static_cast<int>(priority)
                    << " RAM queue is full!" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failEnqueueRAMErrCounter);
        common::counters::IncreaseCounter(m_enqueueFailCounters[priority]);
        return false;
    }

    if (!m_ramQueues[priority]->Enqueue(std::move(eventToStore)))
    {
        LOG_WARNING << "Failed to store event in RAM storage because priority " << static_cast<int>(priority)
                    << " RAM queue Enqueue failed!" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failEnqueueRAMErrCounter);
        common::counters::IncreaseCounter(m_enqueueFailCounters[priority]);
        return false;
    }

    LOG_DEBUG << "PM_DBG:RAM StoreEvent with priority " << static_cast<int>(priority) << " and size " << eventSize
              << " was stored successfully in the RAM storage" << LOG_NOOP;

    m_ramQueuesEventSize[priority]+=eventSize;
   
    common::counters::IncreaseCounter(m_enqueueRAMCounter);
    common::counters::IncreaseCounter(m_enqueueSuccessCounters[priority]);
    return true;
}


inline bool EventsStorage::StoreManagementKeys(EventPriority priority, MetadataKey head, MetadataKey tail, MetadataKey totalSize)
{
    PersistentManagementParameters managementParameters{head, tail, totalSize};

    auto stroeResult = m_perMemQueues[priority]->StoreEntry(m_persistentManagementKeys[priority],
                                                reinterpret_cast<uint8_t*>(&managementParameters),
                                                sizeof(managementParameters));

    LOG_DEBUG << "PM_DBG: Stored management keys[" << stroeResult << "]: priority " << static_cast<int>(priority)
              << " head " << head << " tail " << tail << " total size " << totalSize << LOG_NOOP;

    return stroeResult;
}

bool EventsStorage::storeEventInPersistentStorage(std::unique_ptr<Event> eventToStore)
{
    EventPriority const& priority = eventToStore->GetPriority();
    MetadataKey eventSize = static_cast<MetadataKey>(eventToStore->GetSize());
    if (!m_perMemQueues[priority]->IsEnabled())
    {
        LOG_WARNING << "ERROR: Failed to store event in persistent storage because priority "
                    << static_cast<int>(priority) << " queue is disabled!" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedFlushCounter);
        return false;
    }
       
    // Check there is available space for the new event
    const auto availableSpace = GetPriorityQueueAvailableStorage(priority);
    if(eventSize > availableSpace)
    {
        LOG_WARNING << "ERROR: Failed to store event in PM since there is no enough space for"
                    << " priority " << static_cast<int>(priority) << " evnetSize " << eventSize << " availableSpace "
                    << availableSpace << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedFlushCounter);
        return false;
    }

    // Handle the store of the event's size record
    common::types::string const sizeKey(std::to_string(m_persistentManagementParameters[priority].tailIndex));

    if (!m_perMemQueues[priority]->StoreEntry(sizeKey, reinterpret_cast<uint8_t*>(&eventSize), sizeof(eventSize)))
    {
        LOG_WARNING << "PM_DBG: Failed to store event's size for key " << sizeKey << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedFlushCounter);
        return false;
    }

    // Handle the store of the event's data record
    common::types::string const dataKey(std::to_string(m_persistentManagementParameters[priority].tailIndex+1));

    auto const& eventBuffer = eventToStore->GetBuffer();

    if (!m_perMemQueues[priority]->StoreEntry(dataKey, eventBuffer))
    {
        m_perMemQueues[priority]->RemoveEntry(sizeKey);
        LOG_WARNING << "PM_DBG: Failed to store event data with key [" << dataKey << "]" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedFlushCounter);
        return false;
    }

    // Handle the store of the managment key record
    if(!StoreManagementKeys(static_cast<EventPriority>(priority), 
                                            m_persistentManagementParameters[priority].headIndex,
                                            (m_persistentManagementParameters[priority].tailIndex+2U),
                                            (m_persistentManagementParameters[priority].totalSize + eventSize)))
    {
        LOG_WARNING << "PM_DBG: Failed to store management parameters with key ["
                    << m_persistentManagementKeys[priority] << "]" << LOG_NOOP;
        m_perMemQueues[priority]->RemoveEntry(sizeKey);
        m_perMemQueues[priority]->RemoveEntry(dataKey);
        common::counters::IncreaseCounter(m_failedFlushCounter);
        return false;
    }

    // Update the RAM data only after successful update of the 3 PM records
    m_persistentManagementParameters[priority].tailIndex+=2U;
    m_persistentManagementParameters[priority].totalSize += eventSize;
    
    m_persistentMemorySize[priority]->SetEventCounter(m_persistentManagementParameters[priority].totalSize);
    common::counters::IncreaseCounter(m_pushCounter); //This counters count the number of event stored (meaning the number of pairs)

    LOG_DEBUG << "PM_DBG: Persist StoreEvent with "
              << "priority " << static_cast<int>(priority) << " and size " << eventSize << " was stored successfully:"
              << "head " << m_persistentManagementParameters[priority].headIndex << " tail "
              << m_persistentManagementParameters[priority].tailIndex - 2U << " totalSize "
              << m_persistentManagementParameters[priority].totalSize << LOG_NOOP;

    return true;
}

void EventsStorage::FlushRAMEvents()
{
    if(m_isPmEnable)
    {
        LOG_VERBOSE << "Flush RAM events" << LOG_NOOP;
        std::lock_guard<std::mutex> const lock(m_storageMutex);

        uint32_t eventsFlushed = 0U;
        std::unique_ptr<Event> eventToStore;
        for (uint32_t priority = 0U; priority < EventPriority::NUM_OF_EVENT_PRIORITIES; ++priority)
        {
            while (m_ramQueues[priority]->Dequeue(eventToStore))
            {
                m_ramQueuesEventSize[priority]-=eventToStore->GetSize();
                common::counters::IncreaseCounter(m_dequeuedRAMCounter);
                if (storeEventInPersistentStorage(std::move(eventToStore)))
                {
                    eventsFlushed++; //No need to check overflow since not only it's used for logging solely but also the type of ramQueue is int of which the max size isn't bigger than for uint32
                }
            }
        }

        if (0U < eventsFlushed)
        {
            m_amountOfFlashedEventsCounter->IncrementEventCounter(eventsFlushed);
            LOG_DEBUG << "Flushed " << eventsFlushed << " events from the RAM to persistent memory" << LOG_NOOP;
        }
        LOG_DEBUG << "Finished flush RAM to persistent memory" << LOG_NOOP;
    }
}

void EventsStorage::DeleteAllEventsByPriority(uint8_t priority) noexcept
{
    LOG_DEBUG << "PM_DBG: Delete all events for priority " << static_cast<int>(priority) << LOG_NOOP;

    // Remove the current persist data
    m_perMemQueues[priority]->RemoveAllKeys();

    // Reset the management parameters
    ResetPersistentManagementParameters(priority);

    // Set default settings into the persist data
    std::ignore = StoreManagementKeys(static_cast<EventPriority>(priority),
                                      PerManagementParamDefaultHeadIndex,
                                      PerManagementParamDefaultTailIndex,
                                      PerManagementParamDefaultTotalSize);
}

void EventsStorage::DeleteAllEvents()
{
    LOG_INFO << "Delete all events" << LOG_NOOP;

    for (uint8_t priority = 0U; priority < EventPriority::NUM_OF_EVENT_PRIORITIES; priority++)
    {
        DeleteAllEventsByPriority(priority);
    }
}

bool
EventsStorage::getEventDataFromPersistencyManager(Event::BufferType&                  returnBuffer,
                                                  PersistentMemoryManagerInterfacePtr perMngr,
                                                  common::types::string const&        entryKey,
                                                  MetadataKey                         entrySize) const
{
    if (!perMngr)
    {
        return false;
    }

    uint8_t* const buffer = new uint8_t[entrySize];
    if (nullptr == buffer)
    {
        LOG_ERROR << "Failed to get entry from persistence manager due to failure to allocate memory for buffer"
                  << LOG_NOOP;
        return false;
    }

    if (!(perMngr->GetEntry(entryKey, buffer, entrySize)))
    {
        LOG_ERROR << "Failed to get entry from persistence manager because GetEntry failed" << LOG_NOOP;

        delete[] buffer;
        return false;
    }

    static_cast<void>(std::copy(buffer, buffer + entrySize , std::back_inserter(returnBuffer)));

    delete[] buffer;
    return true;
}

void EventsStorage::Enable()
{
    if(m_isPmEnable)
    {
        LOG_INFO << "Enable" << LOG_NOOP;
        std::lock_guard<std::mutex> const lock(m_storageMutex);

        for (auto storagePtr : m_perMemQueues)
        {
            storagePtr->Enable();
        }
    }
}

void EventsStorage::Disable()
{
    if(m_isPmEnable)
    {
        LOG_INFO << "Disable" << LOG_NOOP;
        std::lock_guard<std::mutex> const lock(m_storageMutex);

        for (auto const& storagePtr : m_perMemQueues)
        {
            storagePtr->Disable();
        }

    }
}

bool EventsStorage::GetNextEvent(std::unique_ptr<Event>& outEvent)
{
    LOG_DEBUG << "Get next event" << LOG_NOOP;
    std::vector<common::types::string> keys;
    Event::BufferType eventBuffer;
    int32_t priority = 0;
    outEvent = std::make_unique<Event>();

    // Check if there is event with weight > 0
    for (; priority < EventPriority::NUM_OF_EVENT_PRIORITIES; priority++)
    {
        if (0U < m_weightsRemainedQueues[static_cast<size_t>(priority)])
        {       
            if(m_getEventFunc(static_cast<EventPriority>(priority), outEvent))
            {
                m_weightsRemainedQueues[static_cast<size_t>(priority)]--;
                return true;
            }
        }
    }

    // If there is no event with weight > 0, run over the priority with weight 0 to check if there is event and reset the weights
    for (priority = 0; priority < EventPriority::NUM_OF_EVENT_PRIORITIES; priority++)
    {
        if (0U == m_weightsRemainedQueues[static_cast<size_t>(priority)])
        {       
            if(m_getEventFunc(static_cast<EventPriority>(priority), outEvent))
            {
                setPriorityQueueWeightsRemained();
                return true;
            }
        }
    }

    return false;
}

void EventsStorage::storageEmptyByPriorityLog(brain::sender::PersistentManagementParameters const& parameters) const
{
    LOG_DEBUG << "PM_DBG: DB mismatch: head=" << parameters.headIndex << ", tail=" << parameters.tailIndex
              << ", totalSize=" << parameters.totalSize << LOG_NOOP;
}

bool EventsStorage::getEventFromRam(EventPriority const priority, std::unique_ptr<Event>& outEvent)
{
    bool isSucceed = false;
    if(m_ramQueues[priority]->Dequeue(outEvent))
    {
        common::counters::IncreaseCounter(m_dequeuedRAMCounter);
        LOG_DEBUG << "Got event from m_ramQueues priority " << static_cast<int>(priority) << LOG_NOOP;
        isSucceed = true;
        m_ramQueuesEventSize[priority]-=outEvent->GetSize();
    }
    return isSucceed;

}

bool EventsStorage::getEventFromPerMem(EventPriority const priority, std::unique_ptr<Event>& outEvent)
{
    MetadataKey eventSize = 0;
    Event::BufferType eventBuffer;

    // Check if there are events
    if(!IsStorageEmptyByPriority(static_cast<EventPriority>(priority)))
    {
        // Handle the retrieve of the event's size record
        common::types::string const sizeKey(std::to_string(m_persistentManagementParameters[priority].headIndex));

        if (!(m_perMemQueues[priority]->GetEntry(sizeKey,
                                    reinterpret_cast<uint8_t*>(&eventSize), sizeof(eventSize))))
        {
            LOG_DEBUG
                << "PM_DBG: FATAL error, didn't success to retrieve event's size, while storage isn't empty, priority="
                << static_cast<int>(priority) << ", sizeKey=" << sizeKey << LOG_NOOP;
            common::counters::IncreaseCounter(m_fatal_error_delete_pm);
            DeleteAllEventsByPriority(static_cast<uint8_t>(priority));
            return false;
        }

        // Handle the retrieve of the event's data record
        common::types::string const dataKey(std::to_string(m_persistentManagementParameters[priority].headIndex+1));

        if(!(getEventDataFromPersistencyManager(eventBuffer, m_perMemQueues[priority], dataKey, eventSize)))
        {
            LOG_DEBUG
                << "PM_DBG: FATAL error, didn't success to retrieve event's data, while storage isn't empty, priority="
                << static_cast<int>(priority) << ", dataKey=" << dataKey << LOG_NOOP;
            common::counters::IncreaseCounter(m_fatal_error_delete_pm);
            DeleteAllEventsByPriority(static_cast<uint8_t>(priority));
            return false;
        }

        // Handle the store of the managment key record
        if (!StoreManagementKeys(static_cast<EventPriority>(priority), 
                                m_persistentManagementParameters[priority].headIndex+2U,
                                m_persistentManagementParameters[priority].tailIndex,
                                m_persistentManagementParameters[priority].totalSize - eventSize))
        {
            LOG_DEBUG << "PM_DBG: GetNextEvent, failed to store the ManagementParameters"
                      << ", priority=" << static_cast<int>(priority)
                      << ",head=" << m_persistentManagementParameters[priority].headIndex + 2U
                      << ", tail=" << m_persistentManagementParameters[priority].tailIndex
                      << ", totalSize=" << m_persistentManagementParameters[priority].totalSize - eventSize << LOG_NOOP;
            return false;
        }
            
        //Remove the entry
        //We will remove the entry only after we updated the new head in the persistent memory 
        //because otherwise, it will try to read not exist value over and over again
        m_perMemQueues[priority]->RemoveEntry(sizeKey);
        m_perMemQueues[priority]->RemoveEntry(dataKey);
            
        // Store of the management parameters
        m_persistentManagementParameters[priority].headIndex+=2;
        m_persistentManagementParameters[priority].totalSize -= eventSize;

        // Update the returned outEvent
        outEvent->Set(eventBuffer,static_cast<EventPriority>(priority));

        LOG_DEBUG << "GetNextEvent succeed for "
                  << "priority=" << static_cast<int>(priority)
                  << " from head=" << m_persistentManagementParameters[priority].headIndex - 2U
                  << " tail=" << m_persistentManagementParameters[priority].tailIndex
                  << " totalSize=" << m_persistentManagementParameters[priority].totalSize << LOG_NOOP;

        m_persistentMemorySize[priority]->SetEventCounter(m_persistentManagementParameters[priority].totalSize);
        common::counters::IncreaseCounter(m_popCounter);
        return true;
    }
    return false;
}


inline void EventsStorage::ResetPersistentManagementParameters(uint8_t priority) noexcept
{
    m_persistentManagementParameters[priority] = {PerManagementParamDefaultHeadIndex,
                                                PerManagementParamDefaultTailIndex,
                                                PerManagementParamDefaultTotalSize};
}

void EventsStorage::InitPersistentMananagementParameters()
{
    if(m_isPmEnable)
    {
        
    
        for (uint8_t priority = 0U; priority < EventPriority::NUM_OF_EVENT_PRIORITIES; ++priority)
        {
            LOG_DEBUG << "PM_DBG: init pesistentManagmentParameters priority: " << static_cast<int>(priority)
                      << LOG_NOOP;

            // If the management key exist, initialize the RAM parameters with the stored data, otherwise remove the exist data and start from scratch
            bool result = m_perMemQueues[priority]->GetEntry(m_persistentManagementKeys[priority], 
                                                    reinterpret_cast<uint8_t*>(&m_persistentManagementParameters[priority]),
                                                    sizeof(m_persistentManagementParameters[priority]));
            if(!result)
            {
                DeleteAllEventsByPriority(priority);
                LOG_DEBUG << "PM_DBG: MNG parameters NOT FOUND - RemoveAllKeys() for priority="
                          << static_cast<int>(priority) << LOG_NOOP;
            }
            else
            {
                LOG_DEBUG << "PM_DBG: MNG parameters FOUND: for "
                          << " priority=" << static_cast<int>(priority)
                          << " head=" << m_persistentManagementParameters[priority].headIndex
                          << " tail=" << m_persistentManagementParameters[priority].tailIndex
                          << " size=" << m_persistentManagementParameters[priority].totalSize << LOG_NOOP;
            }
        }
    }
}

void EventsStorage::setPriorityQueueWeightsRemained() noexcept
{
    LOG_DEBUG << "set priority queue weights remained" << LOG_NOOP;
    for (size_t priority = 0U; priority < EventPriority::NUM_OF_EVENT_PRIORITIES; ++priority)
    {
        m_weightsRemainedQueues[priority] = m_queuePriorityParameters[priority].weight;
	}
}
