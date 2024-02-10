#pragma once
/**
 * @file
 * @brief     This file contains the definition of the VehicleData class and its functionality
 */
#include <memory>
#include <string>

#include "common/utils/types/ConfigurationTypes.hpp" // for ConfigurationPtr

namespace brain
{
namespace brain_vehicle_data
{
class VehicleData
{
public:
    using ConfigurationPtr = common::configuration::Pointer;

    /**
     * @brief  returns the IDS Version
     * @return the IDS Version
     */
    static std::string GetIdsVersion();

    /**
     * @brief   constructor
     * @param   ConfigurationPtr configuration
     */
    VehicleData(ConfigurationPtr configuration);

    /**
     * @brief   return serialize vehicle data (comma separated)
     * @param   std::string& serializeVehicleData - the serialize vehicle data.
     * @return  bool - true for success otherwise false.
     */
    bool GetSerializeVehicleData(std::string& serializeVehicleData);

    /**
     * @brief   return vehicle GUID
     * @param   std::string& vehicleGuid - the vehicle GUID.
     * @return  bool
     *            true - if the vehicle GUID is found in configuration and it's length is >= MAX_VEHICLE_ID_LEN
     *            true - if the vehicle GUID is generated and it's length is >= MAX_VEHICLE_ID_LEN
     *            false - if the configuration is null
     *            false - if the vehicle GUID is < MAX_VEHICLE_ID_LEN
     */
    bool GetVehicleGuid(std::string& vehicleGuid);

    /**
     * @brief   return vehicle type
     * @param   std::string& vehicleType -  the vehicle type.
     * @return  bool - true for success otherwise false.
     */
    bool GetVehicleType(std::string& vehicleType);

private:
    ConfigurationPtr m_configuration;
};

} //brain_vehicle_data
} //brain
