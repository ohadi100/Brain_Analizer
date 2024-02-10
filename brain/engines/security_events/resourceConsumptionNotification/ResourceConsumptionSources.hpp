/**
 * @file
 * @brief      This file define class that handle ResourceConsumption events.
 */
#pragma once

#include <unordered_map>
#include "ResourceConsumptionEntry.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "common/configuration/Configuration.hpp"

using brain::config_keys::ConfigKeyType;

namespace brain
{
namespace engines
{
namespace security_events
{

static constexpr uint32_t DEFAULT_MEM_TOTAL                          = 256U;
static constexpr uint32_t MEMORY_USAGE_ALERT_THRESHOLD_PER_PROCESS   = 50U;
static constexpr uint32_t MEMORY_USAGE_ALERT_THRESHOLD_PER_CORE      = 90U;
static constexpr uint32_t MEMORY_USAGE_ALERT_THRESHOLD_PER_PARTITION = 90U;
static constexpr uint32_t CPU_USAGE_ALERT_THRESHOLD                  = 70U;

enum ResourceConsumptionSource : uint8_t
{
    RESOURCE_CONSUMPTION_HCP3_SE_SYS = 0U,
    RESOURCE_CONSUMPTION_HCP3_SE_IVI,
    RESOURCE_CONSUMPTION_HCP4_SE_M1_C0,
    RESOURCE_CONSUMPTION_HCP4_SE_M1_C1,
    RESOURCE_CONSUMPTION_HCP4_SE_M1_C2,
    RESOURCE_CONSUMPTION_HCP4_SE_M1_C3,
    RESOURCE_CONSUMPTION_HCP4_SE_M1_C4,
    RESOURCE_CONSUMPTION_HCP4_SE_M1_C5,
    RESOURCE_CONSUMPTION_HCP4_SE_M2_1_C0,
    RESOURCE_CONSUMPTION_HCP4_SE_M2_1_C1,
    RESOURCE_CONSUMPTION_HCP4_SE_M2_2_C2,
    RESOURCE_CONSUMPTION_HCP4_SE_M2_2_C3,
    RESOURCE_CONSUMPTION_CONMOD_SE,
    NUM_SOURCES_RESOURCE_CONSUMPTION
};

#define RESOURCE_CONSUMPTION_HCP4(source)                                                                       \
    ((brain::engines::security_events::ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M1_C0 <= source) \
     && (brain::engines::security_events::ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M2_2_C3 >= source))

#define RESOURCE_CONSUMPTION_HCP3_SE_SENSOR(source)                                                           \
    ((brain::engines::security_events::ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP3_SE_SYS == source) \
     || (brain::engines::security_events::ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP3_SE_IVI == source))

#define RESOURCE_CONSUMPTION_CONMOD(source) \
    (brain::engines::security_events::ResourceConsumptionSource::RESOURCE_CONSUMPTION_CONMOD_SE == source)

#define RESOURCE_CONSUMPTION_CALCULATE_CPU_PERCENTAGE_NEEDED(source) \
    RESOURCE_CONSUMPTION_CONMOD(source)

#define RESOURCE_CONSUMPTION_CALCULATE_MEMORY_PERCENTAGE_NEEDED(source) \
    (RESOURCE_CONSUMPTION_CONMOD(source) || RESOURCE_CONSUMPTION_HCP4(source))

#define CPU_USAGE_FIELD_FIILED_WITH_TOTAL_CPU(source)\
    (RESOURCE_CONSUMPTION_HCP4(source) || \
    RESOURCE_CONSUMPTION_CONMOD(source))

class ResourceConsumptionHistoryData
{
public:
    uint32_t m_timestamp{};
    uint32_t m_kernelCpuConsumption{};
    uint32_t m_userCpuConsumption{};
    uint32_t m_ramUtilization{};
    bool
    operator==(ResourceConsumptionHistoryData const& other) const
    {
        return (m_timestamp == other.m_timestamp) && (m_kernelCpuConsumption == other.m_kernelCpuConsumption)
               && (m_userCpuConsumption == other.m_userCpuConsumption) && (m_ramUtilization == other.m_ramUtilization);
    }
};

class ResourceConsumptionSources
{
public:
    using ConfigurationPtr          = std::shared_ptr<common::configuration::Configuration>;
    using ResourceConsumptionSource = brain::engines::security_events::ResourceConsumptionSource;

    static constexpr uint32_t MAX_USAGE_THRESHOLD = 100U; // if there is no threshold for creating alert, effectivly threshold = 100%
    static constexpr uint32_t SYSTEM_PAGE_SIZE = 4U; // system page size in KB for both: HCP3 SYS & IVI partitions.
    static constexpr uint32_t RATE_TO_PERCENTAGE_FACTOR = 100U;
    
    ResourceConsumptionSources() = default;

    /**
     * @brief Constructor for the ResourceConsumptionSources with support for configuration read-out for MEM_TOTAL
     * parameter
     * @param config - pointer to the configuration object.
     * @return ResourceConsumptionSources object with a map that maping to each configured source the memory total size,
     * either the default size 256 (fail to read out the config data or when the configuration pointer is null), the
     * configuration specified size (successfully read out the config data) and in addition memory + cpu alerts
     * thresholds.
     */
    explicit ResourceConsumptionSources(ConfigurationPtr config);

    /**
     * @brief build ResourceConsumptionSource from ResourceConsumptionEntry
     * @param const ResourceConsumptionEntry& key
     * @return ResourceConsumptionSource
     */
    ResourceConsumptionSource GetResourceConsumptionSource(const ResourceConsumptionEntry& key);

    /**
     * @brief return total memory configured to specific source
     * @param const ResourceConsumptionSource& source
     * @return uint8_t - total memory configured to specific source
     */
    uint32_t GetTotalMemorySpace(ResourceConsumptionSource source);

    /**
     * @brief return memory used multiplied by system page size if needed
     * @param const ResourceConsumptionSource& source
     * @param uint32_t ramUtilizationReceived
     * @return uint8_t - memory used multiplied by system page size if needed
     */
    uint32_t GetTotalMemoryUsed(const ResourceConsumptionSource&, uint32_t ramUtilizationReceived);

    /**
    * @brief Emplaces resource use percentages from given entries into given variables.
    *
    * @param[in]  prevProcessPerformanceDataEntry Previous resource consumption data
    * @param[in]  curProcessPerformanceDataEntry  Current resource consumption data
    * @param[in]  key                             Key for resource consumption source data
    * @param[out] userCpuConsumptionPercentage    Emplacement variable for user-space CPU consumption percent
    * @param[out] kernelCpuConsumptionPercentage  Emplacement variable for kernel-space CPU consumption percent
    * @param[out] memConsumptionPercentage        Emplacement variable for memory consumption percent
    */
    void CalculateResourceConsumptionPercentage(const ResourceConsumptionHistoryData& prevProcessPerformanceDataEntry,
                                                const ResourceConsumptionHistoryData& curProcessPerformanceDataEntry, 
                                                const ResourceConsumptionEntry& key,
                                                uint32_t& userCpuConsumptionPercentage, 
                                                uint32_t& kernelCpuConsumptionPercentage, 
                                                uint32_t& memConsumptionPercentage);

    /**
     * @brief return the percentage (0-100) of the memory alert threshold
     * @param const ResourceConsumptionEntry& key - to get configured thresholt per source
     * @return uint8_t - percentage (0-100) of the memory alert threshold
     */
    uint32_t GetMemoryUsageThreshold(const ResourceConsumptionEntry& key);

    /**
     * @brief return the percentage (0-100) of the cpu alert threshold
     * @param const ResourceConsumptionEntry& key - to get configured thresholt per source
     * @return uint8_t - percentage (0-100) of the cpu alert threshold
     */
    uint32_t GetCpuUsageThreshold(const ResourceConsumptionEntry& key);

private:
    std::unordered_map<ResourceConsumptionSource, uint32_t> m_memTotalPerSource;

    uint32_t m_memoryUsageAlertThresholdPerProcess{};
    uint32_t m_memoryUsageAlertThresholdPerCore{};
    uint32_t m_memoryUsageAlertThresholdPerPartition{};

    uint32_t m_cpuUsageAlertThresholdPerProcess{};
    uint32_t m_cpuUsageAlertThresholdPerCore{};
    uint32_t m_cpuUsageAlertThresholdPerPartition{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain