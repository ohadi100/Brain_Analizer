/**
* @file
* @brief     The GroupNoiseFilter is derived from NoiseFilter, and implement noise filter for event group.
*/
#include "GroupNoiseFilter.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "common/counter_manager/CounterNames.hpp"

using namespace brain::brain_noise_filter;
using common::sensor_data::SensorDataTag;

GroupNoiseFilter::GroupNoiseFilter(CounterManagerPtr debugCounters, ConfigurationPtr config) : NoiseFilter(std::unordered_map<uint32_t, NoiseFilterParameters>
    ({
#define DEFINE_FILTER_PARAMETERS(TAG,RATE,BURST,KEY,COUNTER) {static_cast<uint32_t>(SensorDataTag::TAG), NoiseFilterParameters(config, RATE, BURST, brain::config_keys::KEY, debugCounters, common::counters::warning::COUNTER, common::counters::debug::NOT_ ## COUNTER)}

        DEFINE_FILTER_PARAMETERS(SD_PERIODIC_STATISTICS, 345, 409600, PERIODIC_GROUP_NOISE_FILTER_PARAMS, FILTERED_PERIODIC_GROUP_NF_COUNTER),
        DEFINE_FILTER_PARAMETERS(SD_QLAH_ETH, 256, 51200, QLAH_ETH_GROUP_NOISE_FILTER_PARAMS, FILTERED_ETH_SENSOR_GROUP_NF_COUNTER),
        DEFINE_FILTER_PARAMETERS(SD_QLAH_HOST, 256, 51200, QLAH_HOST_GROUP_NOISE_FILTER_PARAMS, FILTERED_HOST_SENSOR_GROUP_NF_COUNTER),
        DEFINE_FILTER_PARAMETERS(SD_SWPAC_TLS_ERROR_REPORT, 10000, 100000, SWPAC_TLS_ERROR_GROUP_NOISE_FILTER_PARAMS, FILTERED_TLS_ERROR_REPORT_GROUP_NF_COUNTER),
        DEFINE_FILTER_PARAMETERS(SD_SECURITY_EVENT, 8064, 204800, SECURITY_EVENT_GROUP_NOISE_FILTER_PARAMS, FILTERED_SECURITY_EVENT_GROUP_NF_COUNTER),
        DEFINE_FILTER_PARAMETERS(SD_INTELLIGENT_SENSOR, 128, 512000, INTELLIGENT_GROUP_NOISE_FILTER_PARAMS, FILTERED_INTELLIGENT_GROUP_NF_COUNTER)
#undef DEFINE_FILTER_PARAMETERS
    }),
    debugCounters,
    true)
{}
