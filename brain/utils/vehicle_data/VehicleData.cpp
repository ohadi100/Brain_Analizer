/**
 * @file
 * @brief     This file contains the functionality of the VehicleData class
 */
#include "brain/config/BrainConfigConstants.hpp"
#include "common/utils/GUID/GUID.hpp"
#include "common/utils/typeCasting/TypeCasting.cpp"
#include "common/version/version.hpp"
#include "common/configuration/Configuration.hpp"

#include <tuple>

#include "VehicleData.hpp"

#include <tuple>

#include "VehicleData.hpp"

#include <tuple>

#include "VehicleData.hpp"

using brain::brain_vehicle_data::VehicleData;

namespace brain
{
namespace brain_vehicle_data
{
// maximum number of characters of the VIN
static constexpr uint8_t MAX_VEHICLE_ID_LEN{9U};
}  // namespace brain_vehicle_data
}  // namespace brain


VehicleData::VehicleData(ConfigurationPtr configuration)
  : m_configuration(configuration)
{
    if (!configuration)
    {
        LOG_ERROR << "Configuration is null in VehicleData" << LOG_NOOP;
    }
}

bool
VehicleData::GetSerializeVehicleData(std::string& serializeVehicleData)
{
    std::string vehicleGuid;
    serializeVehicleData.clear();
    if (!GetVehicleGuid(vehicleGuid))
    {
        LOG_ERROR << "BackendManager failed to get vehicleGuid" << LOG_NOOP;
        return false;
    }

    std::string vehicleType;
    if (!GetVehicleType(vehicleType))
    {
        LOG_ERROR << "BackendManager failed to get vehicleType" << LOG_NOOP;
        return false;
    }

    serializeVehicleData = common::SimpleSerialized({vehicleType, vehicleGuid, GetIdsVersion()});
    return true;
}

bool
VehicleData::GetVehicleGuid(std::string& vehicleGuid)
{
    if (!m_configuration)
    {
        LOG_ERROR << "Failed to get vehicle GUID because m_configuration is null" << LOG_NOOP;
        return false;
    }

    if (!m_configuration->GetValue(brain::config_keys::VEHICLE_GUID, vehicleGuid))
    {
        // generating a new vehicle ID, and save it to persistence
        vehicleGuid = common::GUID::CreateGUID(1);
        std::ignore = m_configuration->SetPersistentValue(brain::config_keys::VEHICLE_GUID, vehicleGuid);
        LOG_DEBUG << "Failed to get vehicle GUID because VEHICLE_GUID not found. Generating vehicleGuid {"
                  << vehicleGuid << "}." << LOG_NOOP;
    }

    if (MAX_VEHICLE_ID_LEN > vehicleGuid.length())
    {
        LOG_INFO << "Vehicle GUID length is less then 9." << LOG_NOOP;
        return false;
    }
    return true;
}

std::string
VehicleData::GetIdsVersion()
{
    return common::version::Version::GetVersion();
}

bool
VehicleData::GetVehicleType(std::string& vehicleType)
{
    if (!m_configuration)
    {
        LOG_ERROR << "Failed to get vehicle type because  m_configuration == nullptr" << LOG_NOOP;
        return false;
    }
    static const std::string INVALID_VEHICLE_TYPE_NAME{"InvalidGUID"};

    vehicleType = INVALID_VEHICLE_TYPE_NAME;
    if (m_configuration->GetValue(brain::config_keys::VEHICLE_TYPE, vehicleType))
    {
        LOG_DEBUG << "Vehicle type was obtained from the configuration" << LOG_NOOP;
    }
    else
    {
        std::string vehicleGuid;
        if (GetVehicleGuid(vehicleGuid))
        {
            vehicleType = vehicleGuid.substr(0, MAX_VEHICLE_ID_LEN);
            std::ignore = m_configuration->SetPersistentValue(brain::config_keys::VEHICLE_TYPE, vehicleType);
            LOG_DEBUG << "Cannot find VEHICLE_TYPE. Generating vehicleType {" << vehicleType.c_str() << "}" << LOG_NOOP;
        }
        else
        {
            LOG_DEBUG << "Cannot get the vehicle GUID, or it's length is less then MAX_VEHICLE_ID_LEN. Vehicle type is "
                      << vehicleType << LOG_NOOP;
        }
    }

    return true;
}