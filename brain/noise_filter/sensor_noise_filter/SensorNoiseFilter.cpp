/**
* @file
* @brief     The SensorNoiseFilter is implementation for noise filter.
*/
#include "SensorNoiseFilter.hpp"
#include "common/sensor_data/SensorDataTags.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "common/counter_manager/CounterNames.hpp"

using namespace brain::brain_noise_filter;
using common::sensor_data::SensorDataTag;

SensorNoiseFilter::SensorNoiseFilter(CounterManagerPtr debugCounters, ConfigurationPtr config) : NoiseFilter(std::unordered_map<uint32_t, NoiseFilterParameters>
    ({
#define DEFINE_FILTER_PARAMETERS(TAG,RATE,BURST,KEY,COUNTER) {static_cast<uint32_t>(SensorDataTag::TAG), NoiseFilterParameters(config, RATE, BURST, brain::config_keys::KEY, debugCounters, common::counters::warning::COUNTER, common::counters::debug::NOT_ ## COUNTER)}
        DEFINE_FILTER_PARAMETERS(SD_QLAH_ETH, 256, 25600, QLAH_ETH_SENSOR_NOISE_FILTER_PARAMS, FILTERED_QLAH_ETH_SENSOR_SD_SENSOR_NF_COUNTER),
        DEFINE_FILTER_PARAMETERS(SD_QLAH_HOST, 256, 25600, QLAH_HOST_SENSOR_NOISE_FILTER_PARAMS, FILTERED_QLAH_HOST_SENSOR_SD_SENSOR_NF_COUNTER),
        DEFINE_FILTER_PARAMETERS(SD_SWPAC_KERNEL_LOG, 10000, 100000, SWPAC_KERNEL_LOG_SENSOR_NOISE_FILTER_PARAMS, FILTERED_SWPAC_KERNEL_LOG_SD_SENSOR_NF_COUNTER),
        DEFINE_FILTER_PARAMETERS(SD_SWPAC_TLS_ERROR_REPORT, 22000, 220000, SWPAC_TLS_ERROR_REPORT_SENSOR_NOISE_FILTER_PARAMS, FILTERED_SWPAC_TLS_ERROR_REPORT_SD_SENSOR_NF_COUNTER),
        DEFINE_FILTER_PARAMETERS(SD_SWPAC_PROCESS_PERFORMANCE_REPORT, 10000, 20000, SWPAC_PROCESS_PERFORMANCE_SENSOR_NOISE_FILTER_PARAMS, FILTERED_SWPAC_PROCESS_PERFORMANCE_SD_SENSOR_NF_COUNTER),
        DEFINE_FILTER_PARAMETERS(SD_SECURITY_EVENT, 9728, 204800, SECURITY_EVENT_SENSOR_NOISE_FILTER_PARAMS, FILTERED_SECURITY_EVENT_SD_SENSOR_NF_COUNTER),
        DEFINE_FILTER_PARAMETERS(SD_INTELLIGENT_SENSOR, 128, 512000, INTELLIGENT_SENSOR_NOISE_FILTER_PARAMS, FILTERED_INTELLIGENT_SD_SENSOR_NF_COUNTER),
        DEFINE_FILTER_PARAMETERS(SD_SACID_CAN_EVENT, 87, 900, SACID_SENSOR_NOISE_FILTER_PARAMS, FILTERED_SACID_SD_SENSOR_NF_COUNTER)
#undef DEFINE_FILTER_PARAMETERS
    }),
    debugCounters,
    SHOULD_COUNT_FILTERED_INCIDENTS)
{
    m_sdFilteredCounter = debugCounters->CreateCounter(common::counters::warning::FILTERED_OUT_BY_SENSOR_NF_COUNTER, EventCounterLevelType::COUNTER_WARNING);
    m_sdNotFilteredCounter = debugCounters->CreateCounter(common::counters::debug::NOT_FILTERED_OUT_BY_SENSOR_NF_COUNTER, EventCounterLevelType::COUNTER_DEBUG);
}
