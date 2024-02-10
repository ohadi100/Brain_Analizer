/**
 * @file
 * @brief     This file contains the definition of the TLSErrorReportSensorData class and its functionality.
 */
#ifndef PROCESS_PERFORMANCE_SENSOR_DATA_HPP
#define PROCESS_PERFORMANCE_SENSOR_DATA_HPP

#include "common/sensor_data/SensorData.hpp"
#include "SwpacSensorDataBase.hpp"
#include "rapidjson/document.h"

namespace brain
{
namespace sensor_data
{

class ProcessPerformanceSensorData final
  : public common::sensor_data::SensorData
  , public SwpacSensorDataBase
{
public:
    using ConstraintId = brain::sensor_data::swpac::ConstraintId;

    /**
     * @brief   Ctor
     * @param   bool& success - true for success, otherwise false.
     * @param   rapidjson::Value const& parsedJson - json to build sd from
     * @param   constraintId - constraint ID, used by the alert for limiting the string size
     */
    ProcessPerformanceSensorData(bool&                   success,
                                 rapidjson::Value const& parsedJson,
                                 ConstraintId            constraintId = ConstraintId::PROCESS_PERFORMANCE);

    /**
     * @brief   Ctor
     */
    ProcessPerformanceSensorData() = default;

    /**
     * @brief   Get Process Name
     * @return  std::string - get the process name
     */
    inline std::string const&
    GetProcessName() const noexcept
    {
        return m_processName;
    };

    /**
     * @brief   Get Process Id value
     * @return  int32_t - process id value
     */
    inline constexpr int32_t
    GetPid() const noexcept
    {
        return m_pid;
    }

    /**
     * @brief   Get CPU value
     * @return  int32_t - cpu value
     */
    inline constexpr uint32_t
    GetCpu() const noexcept
    {
        return m_cpu;
    }

    /**
     * @brief   Get Ram utilization value
     * @return  int32_t - ram utilization value
     */
    inline constexpr uint32_t
    GetRam() const noexcept
    {
        return m_ram;
    }

private:
    /**
     * @brief   Fill SD data from json
     * @param   rapidjson::Value const& dataItems - dataItems is a part from the entire json incident
     * @return  bool - true for success otherwise false
     */
    bool FillFromJson(rapidjson::Value const& dataItems);

    std::string                                  m_processName;
    int32_t                                      m_pid{};
    uint32_t                                     m_cpu{};
    uint32_t                                     m_ram{};
};

}  // namespace sensor_data
}  // namespace brain

#endif  // PROCESS_PERFORMANCE_SENSOR_DATA_HPP