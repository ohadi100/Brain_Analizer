/**
 * @file
 * @brief     This file contains the definitiond of the ResourceConsumptionEntry.
 */
#pragma once

#include "brain/engines/security_events/SecurityEventInstanceIdEntry.hpp"
#include "brain/sensor_data/security_events/SecurityEventSensorData.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{
using brain::sensor_data::SecurityEventSensorData;

/**
 * @struct              ResourceConsumptionEntry
 * @brief               The ResourceConsumptionEntry holds the table keys of ResourceConsumption table
 */
class ResourceConsumptionEntry final : public SecurityEventInstanceIdEntry
{
public:
    bool
    operator==(ResourceConsumptionEntry const& rhs) const
    {
        return SecurityEventInstanceIdEntry::isEqual(rhs) && (m_processName == rhs.m_processName)
               && (m_sensorIdentifier == rhs.m_sensorIdentifier);
    }

    bool
    operator!=(ResourceConsumptionEntry const& rhs) const
    {
        return !(*this == rhs);
    }

    ResourceConsumptionEntry() = default;

    ResourceConsumptionEntry(std::string const& processName,
                             uint16_t           idsMInstanceId,
                             uint8_t            sensorInstanceId)
      : SecurityEventInstanceIdEntry(idsMInstanceId, sensorInstanceId)
      , m_processName(processName)
    {
    }

    ResourceConsumptionEntry(std::string const& processName, std::string const& sensorIdentifier)
      : SecurityEventInstanceIdEntry()
      , m_processName(processName)
      , m_sensorIdentifier(sensorIdentifier)
    {
    }

    ResourceConsumptionEntry(std::string const& processName,
                             uint16_t           idsMInstanceId,
                             uint8_t            sensorInstanceId,
                             std::string const& sensorIdentifier)
      : SecurityEventInstanceIdEntry(idsMInstanceId, sensorInstanceId)
      , m_processName(processName)
      , m_sensorIdentifier(sensorIdentifier)
    {
    }

    ResourceConsumptionEntry(const SecurityEventSensorData& sd, const SECEV_RESOURCE_CONSUMPTION_NOTIFICATION* event)
    {
        static const std::string DEFAULT_SENSOR_IDENTIFIER;

        m_processName = event->processName;
        switch (sd.GetTag())
        {
        case common::sensor_data::SensorDataTag::SD_SECURITY_EVENT:
            m_sensorInstanceId = sd.GetEventFrame().sensorInstanceID;
            m_idsMInstanceId   = sd.GetEventFrame().idsMInstanceID;
            m_sensorIdentifier = DEFAULT_SENSOR_IDENTIFIER;
            break;
        default:
            m_processName = "ILLEGAL_TAG";
            LOG_DEBUG << "Illegal TAG" << LOG_NOOP;
        }
    }

    std::string m_processName;
    std::string m_sensorIdentifier;
};

/**
 * Disable the use of the == and != operators in the base class by
 * implicit conversion from ResourceConsumptionEntry to SecurityEventInstanceIdEntry
 */
bool operator==(ResourceConsumptionEntry const& lhs, SecurityEventInstanceIdEntry const& rhs) = delete;
bool operator==(SecurityEventInstanceIdEntry const& lhs, ResourceConsumptionEntry const& rhs) = delete;
bool operator!=(ResourceConsumptionEntry const& lhs, SecurityEventInstanceIdEntry const& rhs) = delete;
bool operator!=(SecurityEventInstanceIdEntry const& lhs, ResourceConsumptionEntry const& rhs) = delete;

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::ResourceConsumptionEntry;

template <>
class hash<ResourceConsumptionEntry>
{
public:
    /**
     * @brief   hash function of ResourceConsumptionEntry object
     *          Must be implemented so ResourceConsumptionEntry can be used as map key.
     * @param   ResourceConsumptionEntry entry - the ResourceConsumptionEntry object to get hash for
     * @return  size_t - The hash value of the given ResourceConsumptionEntry.
     */
    size_t
    operator()(ResourceConsumptionEntry const& entry) const
    {
        std::array<size_t, 3U> hashes;
        hashes[0U] = std::hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<std::string>()(entry.m_processName);
        hashes[2U] = hash<std::string>()(entry.m_sensorIdentifier);
      
        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std