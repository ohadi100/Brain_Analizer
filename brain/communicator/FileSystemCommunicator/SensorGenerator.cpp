#include "SensorGenerator.hpp"
#include "common/utils/logger/Logger.hpp"

#include <unistd.h>
#include <iostream>

namespace common
{
namespace sensor_genarotor
{
#if !(defined(SSP_PLATFORM) || defined(SSP_PLATFORM_TEST) || defined(SSP_SIMULATION))
SensorGenerator::SensorGenerator(std::vector<std::shared_ptr<brain::engines::Engine>> const& sensorsMap,
                                 DiagnosticsManagerPtr                                       diagManager)
  : m_sensorFactory(sensorsMap, diagManager)
{
}
#else   //! defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST)
SensorGenerator::SensorGenerator(std::vector<std::shared_ptr<brain::engines::Engine>> const& /*sensorsMap*/,
                                 DiagnosticsManagerPtr                                       /*diagManager*/)
{}
#endif  //! defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST)

bool
SensorGenerator::ParseAndGenerateSensor(const std::string& fileContent)
{
    rapidjson::Document json;

    if (json.Parse(fileContent.c_str()).HasParseError())
    {
        LOG_ERROR << "Failed to create rapid json document" << LOG_NOOP;
        return false;
    }
#if !(defined(SSP_PLATFORM) || defined(SSP_PLATFORM_TEST) || defined(SSP_SIMULATION))

    if (!m_sensorFactory.CreateAndSendSensorData(json))
    {
        LOG_ERROR << "Sensor factory failed to create mock sensor" << LOG_NOOP;
        return false;
    }
#endif  //! defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST)

    return true;
}

}  // namespace sensor_genarotor
}  // namespace common