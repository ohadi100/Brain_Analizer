/**
 * @file       ResourceConsumptionSources.cpp
 * @brief      This file define class that handle ResourceConsumption events.
 */

#include "ResourceConsumptionSources.hpp"
#include "common/utils/logger/Logger.hpp"

using brain::engines::security_events::ResourceConsumptionSource;
using brain::engines::security_events::ResourceConsumptionSources;

ResourceConsumptionSources::ResourceConsumptionSources(ConfigurationPtr config)
{
    static std::unordered_map<brain::engines::security_events::ResourceConsumptionSource, ConfigKeyType> const
        memTotalConfigKeys
        = {
            {ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M1_C0, brain::config_keys::HCP4_M1_C0_MEM_TOTAL},
            {ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M1_C1, brain::config_keys::HCP4_M1_C1_MEM_TOTAL},
            {ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M1_C2, brain::config_keys::HCP4_M1_C2_MEM_TOTAL},
            {ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M1_C3, brain::config_keys::HCP4_M1_C3_MEM_TOTAL},
            {ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M1_C4, brain::config_keys::HCP4_M1_C4_MEM_TOTAL},
            {ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M1_C5, brain::config_keys::HCP4_M1_C5_MEM_TOTAL},
            {ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M2_1_C0,
             brain::config_keys::HCP4_M2_1_C0_MEM_TOTAL},
            {ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M2_1_C1,
             brain::config_keys::HCP4_M2_1_C1_MEM_TOTAL},
            {ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M2_2_C2,
             brain::config_keys::HCP4_M2_2_C2_MEM_TOTAL},
            {ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M2_2_C3,
             brain::config_keys::HCP4_M2_2_C3_MEM_TOTAL},
            {ResourceConsumptionSource::RESOURCE_CONSUMPTION_CONMOD_SE, brain::config_keys::CONMOD_MEM_TOTAL},
        };


    for (auto const& configKey : memTotalConfigKeys)
    {
        if (config)
        {
            auto memTotal = DEFAULT_MEM_TOTAL;
            if (!config->GetValue(configKey.second, memTotal))
            {
                LOG_DEBUG << "error while get " << configKey.second << " value from persistent" << LOG_NOOP;
            }

            std::ignore = m_memTotalPerSource.emplace(configKey.first, memTotal);
        }
        else
        {
            std::ignore = m_memTotalPerSource.emplace(configKey.first, DEFAULT_MEM_TOTAL);
        }
    }

    m_memoryUsageAlertThresholdPerProcess   = MEMORY_USAGE_ALERT_THRESHOLD_PER_PROCESS;
    m_memoryUsageAlertThresholdPerCore      = MEMORY_USAGE_ALERT_THRESHOLD_PER_CORE;
    m_memoryUsageAlertThresholdPerPartition = MEMORY_USAGE_ALERT_THRESHOLD_PER_PARTITION;

    m_cpuUsageAlertThresholdPerProcess   = CPU_USAGE_ALERT_THRESHOLD;
    m_cpuUsageAlertThresholdPerCore      = CPU_USAGE_ALERT_THRESHOLD;
    m_cpuUsageAlertThresholdPerPartition = CPU_USAGE_ALERT_THRESHOLD;

    if (config)
    {
        std::ignore = config->GetValue(brain::config_keys::MEMORY_USAGE_ALERT_THRESHOLD_PER_PROCESS,
                                       m_memoryUsageAlertThresholdPerProcess);
        std::ignore = config->GetValue(brain::config_keys::MEMORY_USAGE_ALERT_THRESHOLD_PER_CORE,
                                       m_memoryUsageAlertThresholdPerCore);
        std::ignore = config->GetValue(brain::config_keys::MEMORY_USAGE_ALERT_THRESHOLD_PER_PARTITION,
                                       m_memoryUsageAlertThresholdPerPartition);
        std::ignore = config->GetValue(brain::config_keys::CPU_USAGE_ALERT_THRESHOLD_PER_PROCESS,
                                       m_cpuUsageAlertThresholdPerProcess);
        std::ignore
            = config->GetValue(brain::config_keys::CPU_USAGE_ALERT_THRESHOLD_PER_CORE, m_cpuUsageAlertThresholdPerCore);
        std::ignore = config->GetValue(brain::config_keys::CPU_USAGE_ALERT_THRESHOLD_PER_PARTITION,
                                       m_cpuUsageAlertThresholdPerPartition);
    }
}

ResourceConsumptionSource
ResourceConsumptionSources::GetResourceConsumptionSource(const ResourceConsumptionEntry& key)
{
    // constants used for SecurityEvents data
    // instance ID numbers define by Autosar by 10bits
    static constexpr uint16_t SENSOR_INSTANCE_ID_0{0x0U};
    static constexpr uint16_t SENSOR_INSTANCE_ID_1{0x01U};

    static constexpr uint16_t SENSOR_INSTANCE_ID_HCP4_CORE0          = 0x0U;
    static constexpr uint16_t SENSOR_INSTANCE_ID_HCP4_CORE1          = 0x1U;
    static constexpr uint16_t SENSOR_INSTANCE_ID_HCP4_CORE2          = 0x2U;
    static constexpr uint16_t SENSOR_INSTANCE_ID_HCP4_CORE3          = 0x3U;
    static constexpr uint16_t SENSOR_INSTANCE_ID_HCP4_CORE4          = 0x4U;
    static constexpr uint16_t SENSOR_INSTANCE_ID_HCP4_CORE5          = 0x5U;

    static constexpr uint16_t IDSM_INSTANCE_ID_IVI        = 0x10U;
    static constexpr uint16_t IDSM_INSTANCE_ID_SYS        = 0x11U;

    static constexpr uint16_t IDSM_INSTANCE_ID_HCP4_M1    = 0x18U;
    static constexpr uint16_t IDSM_INSTANCE_ID_HCP4_M2_1  = 0x19U;
    static constexpr uint16_t IDSM_INSTANCE_ID_HCP4_M2_2  = 0x1AU;
    static constexpr uint16_t IDSM_INSTANCE_ID_CONMOD_NAD = 0x31U;

    uint16_t    idsmInstanceId   = key.GetIdsMInstanceId();
    uint16_t    sensorInstanceId = key.GetSensorInstanceId();

    ResourceConsumptionSource source = ResourceConsumptionSource::NUM_SOURCES_RESOURCE_CONSUMPTION;  // default

    switch (idsmInstanceId)
    {
    case IDSM_INSTANCE_ID_IVI:
        if ((SENSOR_INSTANCE_ID_0 == sensorInstanceId) || (SENSOR_INSTANCE_ID_1 == sensorInstanceId))
        {
            source = ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP3_SE_IVI;
        }
        break;
    case IDSM_INSTANCE_ID_SYS:
        if ((SENSOR_INSTANCE_ID_0 == sensorInstanceId) || (SENSOR_INSTANCE_ID_1 == sensorInstanceId))
        {
            source = ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP3_SE_SYS;
        }
        break;
    case IDSM_INSTANCE_ID_HCP4_M1:
        switch (sensorInstanceId)
        {
        case SENSOR_INSTANCE_ID_HCP4_CORE0:
            source = ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M1_C0;
            break;
        case SENSOR_INSTANCE_ID_HCP4_CORE1:
            source = ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M1_C1;
            break;
        case SENSOR_INSTANCE_ID_HCP4_CORE2:
            source = ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M1_C2;
            break;
        case SENSOR_INSTANCE_ID_HCP4_CORE3:
            source = ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M1_C3;
            break;
        case SENSOR_INSTANCE_ID_HCP4_CORE4:
            source = ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M1_C4;
            break;
        case SENSOR_INSTANCE_ID_HCP4_CORE5:
            source = ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M1_C5;
            break;
        default:
            break;
        }
        break;
    case IDSM_INSTANCE_ID_HCP4_M2_1:
        switch (sensorInstanceId)
        {
        case SENSOR_INSTANCE_ID_HCP4_CORE0:
            source = ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M2_1_C0;
            break;
        case SENSOR_INSTANCE_ID_HCP4_CORE1:
            source = ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M2_1_C1;
            break;
        default:
            break;
        }
        break;
    case IDSM_INSTANCE_ID_HCP4_M2_2:
        switch (sensorInstanceId)
        {
        case SENSOR_INSTANCE_ID_HCP4_CORE2:
            source = ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M2_2_C2;
            break;
        case SENSOR_INSTANCE_ID_HCP4_CORE3:
            source = ResourceConsumptionSource::RESOURCE_CONSUMPTION_HCP4_SE_M2_2_C3;
            break;
        default:
            break;
        }
        break;
    case IDSM_INSTANCE_ID_CONMOD_NAD:
        if (SENSOR_INSTANCE_ID_0 == sensorInstanceId)
        {
            source = ResourceConsumptionSource::RESOURCE_CONSUMPTION_CONMOD_SE;
        }
        break;
    default:
        break;
    }

    return source;
}

uint32_t
ResourceConsumptionSources::GetTotalMemorySpace(ResourceConsumptionSource source)
{
    auto memTotalPerSourceIter = m_memTotalPerSource.find(source);
    if (m_memTotalPerSource.end() != memTotalPerSourceIter)
    {
        return memTotalPerSourceIter->second;
    }
    LOG_DEBUG << "memory total configuration for source " << static_cast<uint32_t>(source) << "does't exist"
              << LOG_NOOP;
    return 0U;
}

uint32_t
ResourceConsumptionSources::GetTotalMemoryUsed(const ResourceConsumptionSource&, uint32_t ramUtilizationReceived)
{
    return ramUtilizationReceived;
}

void
ResourceConsumptionSources::CalculateResourceConsumptionPercentage(
    const ResourceConsumptionHistoryData& prevProcessPerformanceDataEntry,
    const ResourceConsumptionHistoryData& curProcessPerformanceDataEntry,
    const ResourceConsumptionEntry&       key,
    uint32_t&                             userCpuConsumptionPercentage,
    uint32_t&                             kernelCpuConsumptionPercentage,
    uint32_t&                             memConsumptionPercentage)
{
    userCpuConsumptionPercentage   = 0U;
    kernelCpuConsumptionPercentage = 0U;
    memConsumptionPercentage       = 0U;

    ResourceConsumptionSource source = GetResourceConsumptionSource(key);

    if (brain::engines::security_events::NUM_SOURCES_RESOURCE_CONSUMPTION <= source)
    {
        // check for invalid source, output values should be kept 0 to avoid false alerts
        return;
    }

    if (RESOURCE_CONSUMPTION_CALCULATE_CPU_PERCENTAGE_NEEDED(source))
    {
        uint32_t deltaTime = curProcessPerformanceDataEntry.m_timestamp - prevProcessPerformanceDataEntry.m_timestamp;

        if ((0U < prevProcessPerformanceDataEntry.m_timestamp)
            && (0U != deltaTime))  // not the first event arrived and valid variables for percentage calculation
        {
            // calculate percentage
            static constexpr uint32_t SYSTEM_CLK_TCK
                = 100U;  // system clk ticks same for all: HCP3 SYS partition, HCP3 IVI partition and ConMod
            static constexpr uint32_t SYSTEM_CLK_TO_MS_FACTOR = (1000U / SYSTEM_CLK_TCK);

            auto const deltaUserProcessingTime = (curProcessPerformanceDataEntry.m_userCpuConsumption
                                                  - prevProcessPerformanceDataEntry.m_userCpuConsumption)
                                                 * SYSTEM_CLK_TO_MS_FACTOR;
            auto const deltaKernelProcessingTime = (curProcessPerformanceDataEntry.m_kernelCpuConsumption
                                                    - prevProcessPerformanceDataEntry.m_kernelCpuConsumption)
                                                   * SYSTEM_CLK_TO_MS_FACTOR;

            userCpuConsumptionPercentage
                = deltaUserProcessingTime * ResourceConsumptionSources::RATE_TO_PERCENTAGE_FACTOR / deltaTime;
            kernelCpuConsumptionPercentage
                = deltaKernelProcessingTime * ResourceConsumptionSources::RATE_TO_PERCENTAGE_FACTOR / deltaTime;
        }
    }
    else
    {
        // for SecurityEvent HCP3 the values already in percentage
        userCpuConsumptionPercentage   = curProcessPerformanceDataEntry.m_userCpuConsumption;
        kernelCpuConsumptionPercentage = curProcessPerformanceDataEntry.m_kernelCpuConsumption;
    }

    if (RESOURCE_CONSUMPTION_CALCULATE_MEMORY_PERCENTAGE_NEEDED(source))
    {
        uint32_t memTotal = GetTotalMemorySpace(source);
        if (0U != memTotal)
        {
            // calculate percentage
            auto const memConsumption = GetTotalMemoryUsed(source, curProcessPerformanceDataEntry.m_ramUtilization);
            memConsumptionPercentage
                = memConsumption * ResourceConsumptionSources::RATE_TO_PERCENTAGE_FACTOR / memTotal;
        }
        else
        {
            LOG_WARNING << " total memory for source " << static_cast<uint32_t>(source) << "has not been configured"
                        << LOG_NOOP;
        }
    }
    else
    {
        memConsumptionPercentage = curProcessPerformanceDataEntry.m_ramUtilization;
    }
}

uint32_t
ResourceConsumptionSources::GetMemoryUsageThreshold(const ResourceConsumptionEntry& key)
{
    ResourceConsumptionSource source = GetResourceConsumptionSource(key);

    return RESOURCE_CONSUMPTION_HCP4(source)
               ? m_memoryUsageAlertThresholdPerCore
               : RESOURCE_CONSUMPTION_CONMOD(source)
                     ? m_memoryUsageAlertThresholdPerProcess
                     : RESOURCE_CONSUMPTION_HCP3_SE_SENSOR(source) ? m_memoryUsageAlertThresholdPerPartition
                                                                   : ResourceConsumptionSources::MAX_USAGE_THRESHOLD;
}

uint32_t
ResourceConsumptionSources::GetCpuUsageThreshold(const ResourceConsumptionEntry& key)
{
    ResourceConsumptionSource source = GetResourceConsumptionSource(key);

    uint32_t cpuUsageThreshold = ResourceConsumptionSources::MAX_USAGE_THRESHOLD;  // default
    if (RESOURCE_CONSUMPTION_HCP4(source))
    {
        cpuUsageThreshold = m_cpuUsageAlertThresholdPerCore;
    }
    else if (RESOURCE_CONSUMPTION_CONMOD(source))
    {
        cpuUsageThreshold = m_cpuUsageAlertThresholdPerProcess;
    }
    else if (RESOURCE_CONSUMPTION_HCP3_SE_SENSOR(source))
    {
        cpuUsageThreshold = m_cpuUsageAlertThresholdPerPartition;
    }

    return cpuUsageThreshold;
}