/**
 * @file
 * @brief     The GroupNoiseFilter is derived from NoiseFilter, and implement noise filter for sensor group.
 */
#ifndef GROUP_NOISE_FILTER_HPP
#define GROUP_NOISE_FILTER_HPP

#include "brain/noise_filter/NoiseFilter.hpp"
#include "common/sensor_data/SensorDataTags.hpp"
#include "common/configuration/Configuration.hpp"

namespace brain
{

namespace brain_noise_filter
{

class GroupNoiseFilter final : public NoiseFilter
{
public:
    using ConfigurationPtr = common::configuration::Pointer;

    /**
      * @brief   Constructor
      * @param   CounterManagerPtr debugCounters
      * @param   ConfigurationPtr config
      */
    GroupNoiseFilter(CounterManagerPtr debugCounters, ConfigurationPtr config);

    /**
      * @brief   Destructor
      */
    virtual ~GroupNoiseFilter() = default;

    /**
     * @brief    default copy constructor
     */
    GroupNoiseFilter(const GroupNoiseFilter& other) = delete;

    /**
     * @brief    default move constructor
     */
    GroupNoiseFilter(GroupNoiseFilter&& other) = delete;

    /**
    * @brief    default copy assignment operator
    */
    GroupNoiseFilter& operator=(GroupNoiseFilter const&) = delete;

    /**
    * @brief   default move assignment operator
    */
    GroupNoiseFilter& operator=(GroupNoiseFilter&&) = delete;
}; //class GroupNoiseFilter

} //namespace brain_noise_filter
} //namespace brain

#endif /* GROUP_NOISE_FILTER_HPP */
