/**
 * @file
 * @brief     Definition of the SensorGenerator class
 */
#ifndef SENSOR_GENERATOR_HPP
#define SENSOR_GENERATOR_HPP
#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
#include "MockSensorFactory.hpp"
#endif  //! defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST)
#include <string.h>
#include <vector>
#include "brain/engines/Engine.hpp"
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
namespace common
{
namespace sensor_genarotor
{
class SensorGenerator final
{
public:
    using DiagnosticsManagerPtr = brain::diagnostics::DiagnosticsManagerInterface::Pointer;

    explicit SensorGenerator(std::vector<std::shared_ptr<brain::engines::Engine>> const& sensorsMap,
                             DiagnosticsManagerPtr                                       diagManager);
    bool ParseAndGenerateSensor(const std::string& fileContent);

    enum class SensorType : uint8_t
    {
        coredump = 0
    };

private:
    SensorType GetSensorType();
#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
    MockSensorFactory m_sensorFactory;
#endif  //! defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST)
};

}  // namespace sensor_genarotor
}  // namespace common

#endif  // SENSOR_GENERATOR_HPP