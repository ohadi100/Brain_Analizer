/**
* @file
* @brief The EventNoiseFilter is derived from NoiseFilter, and implement noise filter for events.
*/

#ifndef EVENT_NOISE_FILTER_HPP
#define EVENT_NOISE_FILTER_HPP

#include "common/utils/CPP/optional/Optional.hpp"
#include "common/configuration/Configuration.hpp"
#include "GroupNoiseFilter.hpp"
#include "brain/events/Event.hpp"

namespace brain
{
namespace brain_noise_filter
{

using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;
class EventNoiseFilter
{
public:
    using CounterManagerPtr = common::counters::CounterManagerPtr;
    using EventCounter = common::counters::EventCounter;
    using ConfigurationPtr = common::configuration::Pointer;

    /**
      * @brief   Constructor
      * @param   CounterManagerPtr debugCounters, ConfigurationPtr config
      */
    EventNoiseFilter(CounterManagerPtr debugCounters, ConfigurationPtr config);

    /**
      * @brief   Destructor
      */
    virtual ~EventNoiseFilter() = default;

    /**
     * @brief    default copy constructor
     */
    EventNoiseFilter(const EventNoiseFilter& other) = delete;

    /**
     * @brief    default move constructor
     */
    EventNoiseFilter(EventNoiseFilter&& other) = delete;

    /**
    * @brief    default copy assignment operator
    */
    EventNoiseFilter& operator=(EventNoiseFilter const&) = delete;

    /**
    * @brief   default move assignment operator
    */
    EventNoiseFilter& operator=(EventNoiseFilter&&) = delete;

    /**
    * @brief   Filter the event first in group noise filter according to its group,
    *          and if it passes than in global noise filter as they're cascaded.
    * @param   uint32_t const eventTag - the event tag.
    * @param   event
    * @return  true if filtered. false if not.
    */
    virtual bool IsDoubleFilteredOut(uint32_t const eventTag, size_t const eventSize);

#ifndef TESTS
private:
#endif

    GroupNoiseFilter m_groupNoiseFilter;
    std::shared_ptr<EventCounter> m_filteredGroupCounter;
    std::shared_ptr<EventCounter> m_notFilteredGroupCounter;

}; //class EventNoiseFilter

} //namespace brain_noise_filter
} //namespace brain

#endif /* EVENT_NOISE_FILTER_HPP */
