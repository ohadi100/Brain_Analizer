/**
 * @file
 * @brief     The SensorNoiseFilter is derived from NoiseFilter, and implement noise filter for sensors.
 */
#ifndef SENSOR_NOISE_FILTER_HPP
#define SENSOR_NOISE_FILTER_HPP

#include "brain/noise_filter/NoiseFilter.hpp"

namespace brain
{
namespace brain_noise_filter
{
constexpr bool SHOULD_COUNT_FILTERED_INCIDENTS = true;
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;

class SensorNoiseFilter final : public NoiseFilter
{
public:
    using CounterManagerPtr = common::counters::CounterManagerPtr;

    /**
      * @brief   Constructor
      * @param   CounterManagerPtr debugCounters, ConfigurationPtr config
      */
    SensorNoiseFilter(CounterManagerPtr debugCounters, ConfigurationPtr config);

    /**
      * @brief   Destructor
      */
    virtual ~SensorNoiseFilter() = default;

    /**
     * @brief    default copy constructor
     */
    SensorNoiseFilter(const SensorNoiseFilter& other) = delete;

    /**
     * @brief    default move constructor
     */
    SensorNoiseFilter(SensorNoiseFilter&& other) = delete;

    /**
    * @brief    default copy assignment operator
    */
    SensorNoiseFilter& operator=(SensorNoiseFilter const&) = delete;

    /**
    * @brief   default move assignment operator
    */
    SensorNoiseFilter& operator=(SensorNoiseFilter&&) = delete;
    
    /**
    * @brief   Getter for the filtered SDs counter
    * @return  The filtered counter
    */
    std::shared_ptr<EventCounter> GetSDFilteredCounter() const
    {
        return m_sdFilteredCounter;
    }

    /**
      * @brief   Getter for the not filtered counter
      * @return  The not filtered SDs counter
      */
    std::shared_ptr<EventCounter> GetSDNotFilteredCounter() const
    {
        return m_sdNotFilteredCounter;
    }

private:
    std::shared_ptr<EventCounter> m_sdFilteredCounter;
    std::shared_ptr<EventCounter> m_sdNotFilteredCounter;

}; //class SensorNoiseFilter

} //namespace brain_noise_filter
} //namespace brain

#endif // SENSOR_NOISE_FILTER_HPP
