/**
 * @file
 * @brief     Definition of the SensorGenerator class
 */
#ifndef MOCK_SENSOR_FACTORY_HPP
#define MOCK_SENSOR_FACTORY_HPP

#include <string.h>
#include <memory>
#include <vector>
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "brain/engines/Engine.hpp"
#include "rapidjson/document.h"

namespace common
{
class MockSensorFactory final
{
public:
    using DiagnosticsManagerPtr = brain::diagnostics::DiagnosticsManagerInterface::Pointer;

    explicit MockSensorFactory(std::vector<std::shared_ptr<brain::engines::Engine>> const& sensorsMap,
                               DiagnosticsManagerPtr                                       diagManager);
    
    bool CreateAndSendSensorData(rapidjson::Document const& jsonObj);

private:
    std::vector<std::shared_ptr<brain::engines::Engine>> m_sensorsMap;
    common::sensor_data::UPSensorData                    CreateSecurityEventSensoData(rapidjson::Document const& jsonObj);
    DiagnosticsManagerPtr                                m_diagnosticsManager;
};

}  // namespace common


#endif  // SENSOR_GENERATOR_HPP