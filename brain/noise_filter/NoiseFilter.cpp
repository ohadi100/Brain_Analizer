/**
* @file
* @brief     The SensorNoiseFilter is a definitions for noise filter.
*/
#include "NoiseFilter.hpp"
#include "common/utils/HashUtils.hpp"
#include "common/configuration/Configuration.hpp"

using namespace brain::brain_noise_filter;
namespace brain
{

namespace brain_noise_filter
{
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;
}  // namespace brain_noise_filter
}  // namespace brain

NoiseFilter::NoiseFilter(std::unordered_map<uint32_t, NoiseFilterParameters>&& FiltersToRegister, CounterManagerPtr debugCounters, bool const shouldCountFiltered) :
    m_noiseFilters(std::move(FiltersToRegister)), m_shouldCountFiltered(shouldCountFiltered), m_debugCounters(debugCounters)
{
}

NoiseFilter::NoiseFilter(std::unordered_map<uint32_t, NoiseFilterParameters>& FiltersToRegister, CounterManagerPtr debugCounters, bool const shouldCountFiltered) :
    m_noiseFilters(std::move(FiltersToRegister)), m_shouldCountFiltered(shouldCountFiltered), m_debugCounters(debugCounters)
{
}

double NoiseFilter::tokenInit(NoiseFilterParameters& filterParameters, uint32_t sizeOfData, int64_t time) const
{
    int64_t const lastTime = filterParameters.lastTime;

    if ((time < 0) && (lastTime > 0) && (time < (std::numeric_limits<int64_t>::min() + lastTime)))
    {
        // underflow check
        LOG_WARNING << "dt underflow, thus token will get min value of double" << LOG_NOOP;
        return std::numeric_limits<double>::min();
    }
    else if ((time > 0) && (lastTime < 0) && (time > (std::numeric_limits<int64_t>::max() + lastTime)))
    {
        // overflow check
        LOG_WARNING << "dt overflow, thus token will get max value of double" << LOG_NOOP;
        return std::numeric_limits<double>::max();
    }
    else
    {
        int64_t const dt = time - lastTime;
        double const rate = filterParameters.rate;
        double const addToToken = (rate * static_cast<double>(dt)) - static_cast<double>(sizeOfData);
        double token = filterParameters.token;

        if (token > (std::numeric_limits<double>::max() - addToToken))
        {
            LOG_WARNING << "Token overflow, thus token will get max value of double" << LOG_NOOP;
            return std::numeric_limits<double>::max();
        }
        else
        {
            token += addToToken;
            return token;
        }
    }
}

bool NoiseFilter::IsFilteredOutBySDTag(uint32_t SDTag, EventCounterPtr filteredCounter, EventCounterPtr notFilteredCounter, uint32_t const sizeOfData)
{
    std::unordered_map<uint32_t, NoiseFilterParameters>::iterator filterItr = m_noiseFilters.find(SDTag);
    if (m_noiseFilters.end() == filterItr)
    {
        // sensorType is not registered
        return false;
    }	
	auto& filterParameters = filterItr->second;
	return IsFilteredOutByParams(filterParameters, filteredCounter, notFilteredCounter, sizeOfData);
}

bool NoiseFilter::IsFilteredOutByParams(NoiseFilterParameters& filterParameters, EventCounterPtr filteredCounter, EventCounterPtr notFilteredCounter, uint32_t const sizeOfData)
{
    auto const time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    double token = tokenInit(filterParameters, sizeOfData, time);

    uint32_t const burst = filterParameters.burst;
    if (token > static_cast<double>(burst))
    {
        token = static_cast<double>(burst);
    }

    if (token >= 0.0)
    {
        filterParameters.lastTime = time;
        filterParameters.token = token;
        common::counters::IncreaseCounter(notFilteredCounter);
        if (m_debugCounters)
        {
            common::counters::IncreaseCounter(filterParameters.notFilteredCounter);
        }
        return DATA_IS_NOT_FILTERED_OUT_AND_WILL_BE_PROCESSED; //Allowed to pass
    }

    filterParameters.token = 0.0;

    if (m_shouldCountFiltered)
    {
        common::counters::IncreaseCounter(filteredCounter);
        if (m_debugCounters)
        {
            common::counters::IncreaseCounter(filterParameters.filteredCounter);
        }
    }
    return DATA_IS_FILTERED_OUT_AND_WILL_NOT_BE_PROCESSED; //Not allowed to pass
}

bool NoiseFilter::IsFilterRegistered(uint32_t SDTag) const
{
    return (m_noiseFilters.end() != m_noiseFilters.find(SDTag));
}

#ifdef TESTS
bool NoiseFilter::GetFilterParameters(uint32_t SDTag, NoiseFilterParameters& noiseFilterParams)
{
    auto const filterItr = m_noiseFilters.find(SDTag);
    if (m_noiseFilters.end() == filterItr)
    {
        // sensorType is not registered
        return false;
    }
    noiseFilterParams = filterItr->second;
    return true;
}

bool NoiseFilter::RegisterFilter(
    uint32_t SDTag,
    double eventRate,
    uint32_t maxBurst,
    std::string const& filteredCounterName,
    std::string const& notFilteredCounterName)
{

    if (common::utils::IsEqual<double>(0.0, eventRate))
    {
        // illegal rate
        return false;
    }

    // if the filterType already registered - return false
    auto const filterIndexItr = m_noiseFilters.find(SDTag);
    if (m_noiseFilters.end() == filterIndexItr)
    {
        //int64_t const time = static_cast<int64_t>(-1.0/eventRate);
        static_cast<void>(m_noiseFilters.insert({SDTag, {eventRate, maxBurst, m_debugCounters, filteredCounterName, notFilteredCounterName}}));
        return true;
    }
    return false;
}

bool NoiseFilter::DeregisterFilter(uint32_t SDTag)
{
    return (m_noiseFilters.erase(SDTag) > 0U);
}

bool NoiseFilter::EditFilter(uint32_t SDTag, double eventRate, uint32_t maxBurst)
{
    if (common::utils::IsEqual<double>(0.0, eventRate))
    {
        // illegal rate
        return false;
    }
    std::unordered_map<uint32_t, NoiseFilterParameters>::iterator filterIndexItr = m_noiseFilters.find(SDTag);
    if (m_noiseFilters.end() == filterIndexItr)
    {
        return false;
    }
    int64_t const time = static_cast<int64_t>(-1.0/ eventRate);
    filterIndexItr->second.lastTime = time;
    filterIndexItr->second.rate = eventRate;
    filterIndexItr->second.burst = maxBurst;
    
    return true;    
}

void NoiseFilter::DisableNoiseFilter()
{
    m_noiseFilters.clear();
}
#endif //TESTS

NoiseFilterParameters::NoiseFilterParameters(
    ConfigurationPtr config,
    double defaultRate,
    uint32_t defaultBurst,
    std::string const& configKey,
    CounterManagerPtr counters,
    std::string const& filteredCounterName,
    std::string const& notFilteredCounterName) :
    rate(defaultRate),
    burst(defaultBurst)
{
    if (counters)
    {
        filteredCounter = counters->CreateCounter(filteredCounterName, EventCounterLevelType::COUNTER_WARNING);
        notFilteredCounter = counters->CreateCounter(notFilteredCounterName, EventCounterLevelType::COUNTER_DEBUG);
    }

    std::vector<uint32_t> configParams;
    if (config && config->GetValue(configKey, configParams))
    {
        static const uint64_t EXPECTED_VECTOR_SIZE = 2U;
        if (configParams.size() == EXPECTED_VECTOR_SIZE)
        {
            rate = configParams[NFConfigParamIndexes::RATE];
            burst = configParams[NFConfigParamIndexes::BURST];
        }
        else
        {
            LOG_ERROR << "Invalid number of variables in noise filter config key " << configKey << LOG_NOOP;
        }
    }

    token = static_cast<double>(burst);
    lastTime = common::utils::IsEqual<double>(0.0, rate) ? 0 : static_cast<int64_t>(-1.0/rate);
}

#ifdef TESTS
NoiseFilterParameters::NoiseFilterParameters(
    double defaultRate,
    uint32_t defaultBurst,
    CounterManagerPtr counters,
    std::string const& filteredCounterName,
    std::string const& notFilteredCounterName) :
    rate(defaultRate),
    burst(defaultBurst),
    lastTime(common::utils::IsEqual<double>(0.0, defaultRate) ? 0 : static_cast<int64_t>(-1.0/defaultRate)),
    token(static_cast<double>(defaultBurst))
{
    if (counters)
    {
        filteredCounter = counters->CreateCounter(filteredCounterName, EventCounterLevelType::COUNTER_WARNING);
        notFilteredCounter = counters->CreateCounter(notFilteredCounterName, EventCounterLevelType::COUNTER_DEBUG);
    }
}
#endif // TESTS