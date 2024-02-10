/**
 * @file
 * @brief       This file declares interfaces for Security Events engines classes
 */
#pragma once

#include "NanoPB.hpp"


namespace brain
{
namespace engines
{
namespace security_events
{
/**
 * @interface   IStatisticsDataHolder
 * @brief       An interface to entities containing statistical data
 */
class IStatisticsDataHolder
{
public:
    using SecurityEventMonitoringData = brain::engines::security_events::nanopb::SecurityEventMonitoringData;

    /**
     * @brief    default constructor
     */
    IStatisticsDataHolder() = default;

    /**
     * @fn      virtual ~IStatisticsDataHolder()
     * @brief   Destructor
     */
    virtual ~IStatisticsDataHolder() = default;

    /**
     * @brief    default copy constructor
     */
    IStatisticsDataHolder(const IStatisticsDataHolder& other) = default;

    /**
     * @brief    default move constructor
     */
    IStatisticsDataHolder(IStatisticsDataHolder&& other) = default;

    /**
    * @brief    default copy assignment operator
    */
    IStatisticsDataHolder& operator=(IStatisticsDataHolder const&) = default;

    /**
    * @brief   default move assignment operator
    */
    IStatisticsDataHolder& operator=(IStatisticsDataHolder&&) = default;
    
    /**
     * @brief   Fill Statistic Data
     * @param   SecurityEventMonitoringData& securityEventMonitoringData - The structure to fill
     * @return  bool - true for success, otherwise false.
     */
    virtual bool FillStatisticData(SecurityEventMonitoringData& securityEventMonitoringData) = 0;

    /**
     * @brief   Reset Statistic Data.
     */
    virtual void ResetStatisticData() = 0;
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain