/**
 * @file
 * @brief     The EventNoiseFilter is implementation for noise filtering of events.
 */
#include "EventNoiseFilter.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "common/counter_manager/CounterNames.hpp"

using namespace brain::brain_noise_filter;

EventNoiseFilter::EventNoiseFilter(CounterManagerPtr debugCounters, ConfigurationPtr config)
  : m_groupNoiseFilter(debugCounters, config)
{
    if (debugCounters)
    {
        m_filteredGroupCounter = debugCounters->CreateCounter(
            common::counters::warning::FILTERED_OUT_EVENT_BY_GROUP_NF_COUNTER, EventCounterLevelType::COUNTER_WARNING);
        m_notFilteredGroupCounter = debugCounters->CreateCounter(
            common::counters::debug::NOT_FILTERED_OUT_EVENT_BY_GROUP_NF_COUNTER, EventCounterLevelType::COUNTER_DEBUG);
    }
}

bool
EventNoiseFilter::IsDoubleFilteredOut(uint32_t const eventTag, size_t const eventSize)
{
    return m_groupNoiseFilter.IsFilteredOutBySDTag(
        eventTag, m_filteredGroupCounter, m_notFilteredGroupCounter, static_cast<uint32_t>(eventSize));
}
