/**
 * @file
 * @brief     The NoiseFilter is a definitions for noise filter.
 */
#ifndef NOISE_FILTER_HPP
#define NOISE_FILTER_HPP

#include <tuple>
#include <chrono>
#include <atomic>  
#include <unordered_map>

#include "common/utils/logger/Logger.hpp"
#include "common/counter_manager/CounterManager.hpp"
#include "common/utils/types/ConfigurationTypes.hpp"

namespace brain
{

namespace brain_noise_filter
{

using ConfigurationPtr = common::configuration::Pointer;
using EventCounter = common::counters::EventCounter;
using EventCounterPtr = std::shared_ptr<EventCounter>;
using CounterManagerPtr = common::counters::CounterManagerPtr;

class NoiseFilterParameters final
{
public:
    NoiseFilterParameters(
        ConfigurationPtr config,
        double defaultRate,
        uint32_t defaultBurst,
        std::string const& configKey,
        CounterManagerPtr counters,
        std::string const& filteredCounterName,
        std::string const& notFilteredCounterName);

#ifdef TESTS
    NoiseFilterParameters() = default;
    NoiseFilterParameters(
        double defaultRate,
        uint32_t defaultBurst,
        CounterManagerPtr counters,
        std::string const& filteredCounterName,
        std::string const& notFilteredCounterName);
#endif // TESTS

    double rate;
    uint32_t burst;
    int64_t lastTime;
    double token;
    EventCounterPtr filteredCounter;
    EventCounterPtr notFilteredCounter;
};

enum NFConfigParamIndexes : uint8_t
{
    RATE = 0U,
    BURST = 1U,

    NF_PARAMETERS_COUNT
};

constexpr bool DATA_IS_FILTERED_OUT_AND_WILL_NOT_BE_PROCESSED = true;
constexpr bool DATA_IS_NOT_FILTERED_OUT_AND_WILL_BE_PROCESSED = false;


class NoiseFilter
{
public:
    /**
     * @brief   update the last time the event examined
     * @param   NoiseFilterParameters& filterParameters - reference to the tuple - some of the fields are output parameters.
     * @param   EventCounterPtr filteredCounter - the filtered counter.
     * @param   EventCounterPtr notFilteredCounter - the not filtered counter.
     * @param   uint32_t const sizeOfData - Size of data in bytes that examined at once.
     * @return  true if filtered. false if not.
     */
    virtual bool IsFilteredOutByParams(NoiseFilterParameters& filterParameters, EventCounterPtr filteredCounter, EventCounterPtr notFilteredCounter, uint32_t const sizeOfData);

	/**
     * @brief   update the last time the event examined
     * @param   uint32_t SDTag - The sensor data tag to filter by.
     * @param   EventCounterPtr filteredCounter - the filtered counter.
     * @param   EventCounterPtr notFilteredCounter - the not filtered counter.
     * @param   uint32_t const sizeOfData - Size of data in bytes that examined at once.
     * @return  true if filtered. false if not.
     */
    virtual bool IsFilteredOutBySDTag(uint32_t SDTag, EventCounterPtr filteredCounter, EventCounterPtr notFilteredCounter, uint32_t const sizeOfData);
    
    /**
     * @brief   return true if given filerKey is registered.
     * @param   uint32_t SDTag - The sensor data tag
     * @return  false if the filterIndex not registered.
     */
    virtual bool IsFilterRegistered(uint32_t SDTag) const;

#ifdef TESTS 
	/**
     * @brief   Get the filter parameters
     * @param   uint32_t SDTag - The sensor data tag
     * @param   NoiseFilterParameters& noiseFilterParams - Output parameter. the event full parameters.
     * @return  false if the filterIndex not registered.
     */
    virtual bool GetFilterParameters(uint32_t SDTag, NoiseFilterParameters& noiseFilterParams);

    /**
     * @brief   Register filter for rate monitoring.
     * @param   uint32_t SDTag - the sensor type
     * @param   double eventRate - The rate in which the event is allowed to happen.
     *
     *          For example:
     *          rate=0.1: 1 event per 10 seconds
     *          rate=10 : 10 events per 1 second
     *
     * @param   uint32_t maxBurst - The max burst that we allow to the events rate.
     * @param   std::string const& filteredCounterName
     * @param   std::string const& notFilteredCounterName
     * @return  true if operation succeed, false otherwise.
     */
    virtual bool RegisterFilter(
        uint32_t SDTag,
        double eventRate,
        uint32_t maxBurst,
        std::string const& filteredCounterName,
        std::string const& notFilteredCounterName);
    /**
     * @brief   Deregister filter from noise filter.
     * @param   uint32_t const SDTag - the filter type.
     * @return  true if operation succeed, false otherwise.
     */
    virtual bool DeregisterFilter(uint32_t SDTag);

    /**
     * @brief   Edit filter parameters of given filter index for rate monitoring.
     * @param   uint32_t const SDTag - the sensor type
     * @param   double const eventRate - The rate in which the event is allowed to happen.
     *
     *          For example:
     *          rate=0.1: 1 event per 10 seconds
     *          rate=10 : 10 events per 1 second
     *
     * @param   uint32_t const maxBurst - The max burst that we allow to the events rate.
     * @return  true if filter params were edited, false if filter index was not found.
     */
    virtual bool EditFilter(uint32_t SDTag, double eventRate, uint32_t maxBurst);

    virtual void DisableNoiseFilter();
#endif //TESTS

protected:
    /**
      * @brief   deleted the default constructor.
      */
    NoiseFilter() = delete;

    /**
      * @brief   Destructor
      */
    virtual ~NoiseFilter() = default;

    /**
     * @brief    default copy constructor
     */
    NoiseFilter(const NoiseFilter& other) = delete;

    /**
     * @brief    default move constructor
     */
    NoiseFilter(NoiseFilter&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    NoiseFilter& operator=(NoiseFilter const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    NoiseFilter& operator=(NoiseFilter&&) = delete;

    /**
      * @brief   constructor
      *          This constructor is protected because we don't want to create an instance of NoiseFilter(), only instances of the derived classes.
      * @param   std::unordered_map<uint32_t, NoiseFilterParameters> FiltersToRegister - ref to noise filters parameters map
      * @param   CounterManagerPtr debugCounters
      * @param   bool const shouldCountFiltered - reflects whether to count cases filtered out by noise filter in order to improve performance
      */
    NoiseFilter(std::unordered_map<uint32_t, NoiseFilterParameters>&& FiltersToRegister, CounterManagerPtr debugCounters, bool const shouldCountFiltered=false);

    /**
     * @brief   constructor
     *          This constructor is protected because we don't want to create an instance of NoiseFilter(), only instances of the derived classes.
     * @param   std::unordered_map<uint32_t, NoiseFilterParameters> FiltersToRegister - ref to noise filters parameters map
     * @param   CounterManagerPtr debugCounters
     * @param   bool const shouldCountFiltered - reflects whether to count cases filtered out by noise filter in order to improve performance
     */
    NoiseFilter(std::unordered_map<uint32_t, NoiseFilterParameters>& FiltersToRegister, CounterManagerPtr debugCounters, bool const shouldCountFiltered = false);

    /**
      * @brief   Initialize the token
      * @param   NoiseFilterParameters& filterParameters - filter Parameters
      * @param   uint32_t const sizeOfData - the size of the data
      * @param   __time64_t const time - The current time
      * @return  double - tokens
      */
    double tokenInit(NoiseFilterParameters& filterParameters, uint32_t sizeOfData, int64_t time) const;

private:
    std::unordered_map<uint32_t, NoiseFilterParameters> m_noiseFilters;
    bool const m_shouldCountFiltered;
    CounterManagerPtr m_debugCounters;

}; //class NoiseFilter

} //namespace brain_noise_filter
} //namespace brain

#endif /* NOISE_FILTER_HPP */
