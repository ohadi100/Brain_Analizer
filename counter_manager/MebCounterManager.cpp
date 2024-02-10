/**
 * @file      MebCounterManager.h
 * @brief     Debug counter manager for MEB events
  
 */

#include "common/counter_manager/MebCounterManager.h"
#include "common/counter_manager/BaseCounterManager.h"

using namespace common::counters;
using common::counters::MebEventCounter;


MebCounterManager::MebCounterManager() : BaseCounterManager()
{
    mIsMarkedForReset.store(false);
}

void MebCounterManager::CountNotification(std::string const& eventName)
{
    if (IsMarkedForReset())
    {
        ClearAll();
    }

    static_cast<void>(GetCounter(eventName)->CountEvent());
}

std::shared_ptr<MebEventCounter> MebCounterManager::GetCounter(std::string const & eventName)
{
    auto notificationCounter = m_counterManager.GetCounter(eventName);

    if (notificationCounter == m_counterManager.End())
    {
        notificationCounter = m_counterManager.AddCounter(eventName);
    }

    return notificationCounter->second;
}

Json::Value MebCounterManager::GetCountersAsJson()
{
    if (IsMarkedForReset())
    {
        ClearAll();
    }

    return m_counterManager.GetCountersAsJson();
}

std::string MebCounterManager::GetCountersAsJsonString()
{
    if (IsMarkedForReset())
    {
        ClearAll();
    }

    auto const json = GetCountersAsJson();

    Json::StreamWriterBuilder const builder;

    return  Json::writeString(builder, json);
}

void MebCounterManager::ClearAll()
{
    m_counterManager.Clear();
    mIsMarkedForReset.store(false);
}

bool MebCounterManager::IsMarkedForReset() noexcept
{
    return mIsMarkedForReset.load();
}

std::string MebCounterManager::GetSerializedCounters()
{
    return GetCountersAsJsonString();
}

Json::Value MebCounterManager::GetCountersJson()
{
    return GetCountersAsJson();
}

void MebCounterManager::MarkForReset() noexcept
{
    mIsMarkedForReset.store(true);
}