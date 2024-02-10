/**
 * @file
 * @brief     This file contains the functionality of the CounterMeasurementValue class
 */
#include "CounterMeasurementValue.hpp"
#include "common/utils/logger/Logger.hpp"
#include "common/counter_manager/CounterManager.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "persistent_map/PersistentMap.h"


using brain::diagnostics::measurement_values::CounterMeasurementValue;
using common::utils::PersistentMap;


void CounterMeasurementValue::addCounter(EventCounterPtr counter)
{
    std::string counterName;
    counter->GetEventName(counterName);

    std::ignore = m_counters.insert(std::make_pair(counterName, counter));
}

uint64_t CounterMeasurementValue::getCount(std::string const& counterName) const
{
    EventCounterPtr const counter = m_counters.at(counterName);
    return counter ? counter->GetEventCounter() : 0UL;
}

bool CounterMeasurementValue::ResetCounters()
{
    bool result = true;

    for (auto const& counter: m_counters)
    {
        if (nullptr != counter.second)
        {
            counter.second->ResetCounter();
        }
        else
        {
            result = false;
        }
    }

    return result;
}

void CounterMeasurementValue::loadFromPersistentMemory()
{
    if (nullptr == m_persistentMemory)
    {
        LOG_WARNING
            << "Can't load diagnostics measurement values from persistency because m_persistentMemory is nullptr"
            << LOG_NOOP;
        return;
    }

    for (auto const& counter: m_counters)
    {
        if (nullptr != counter.second)
        {
            uint64_t counterValue = 0U;
            if (PersistentMap::OperationStatus::eSuccess == m_persistentMemory->GetValue(counter.first, counterValue))
            {
                counter.second->SetEventCounter(counterValue);
            }
            else
            {
                LOG_WARNING << "Value for '" << counter.first
                            << "' measurement value counter wasn't found in persistent memory" << LOG_NOOP;
            }
        }
    }
}

void CounterMeasurementValue::saveToPersistentMemory()
{
    if (nullptr == m_persistentMemory)
    {
        LOG_WARNING << "Can't save diagnostics measurement values to persistency because m_persistentMemory is nullptr"
                    << LOG_NOOP;
        return;
    }

    for (auto const& counter: m_counters)
    {
        if (nullptr != counter.second)
        {
            if (PersistentMap::OperationStatus::eSuccess != m_persistentMemory->StoreValue(counter.first, counter.second->GetEventCounter()))
            {
                LOG_WARNING << "Failed to save '" << counter.first
                            << "' counter, used by measurement values to persistency" << LOG_NOOP;
                return;
            }
        }
    }
}
