/**
 * @file
 * @brief     This file contains the definition of the ExternalInterfacesUsageStatisticsEntry class and its
 * functionality.
 */
#ifndef EXTERNAL_INTERFACES_USAGE_STATISTICS_ENTRY_HPP
#define EXTERNAL_INTERFACES_USAGE_STATISTICS_ENTRY_HPP

#include "SecurityEventInstanceIdEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

/**
 * @class       ExternalInterfacesUsageStatisticsEntry
 */
class ExternalInterfacesUsageStatisticsEntry : public SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief   Default Constructor (needed for UT)
     */
    ExternalInterfacesUsageStatisticsEntry() = default;

    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceID
     * @param   uint8_t sensorInstanceID
     * @param   uint8_t connectionType
     * @param   uint16_t layerType
     * @return	none
     */
    ExternalInterfacesUsageStatisticsEntry(uint16_t idsMInstanceID,
                                           uint8_t  sensorInstanceID,
                                           uint8_t  connectionType,
                                           uint16_t layerType)
      : SecurityEventInstanceIdEntry(idsMInstanceID, sensorInstanceID)
      , m_connectionType(connectionType)
      , m_layerType(layerType)
    {
    }

    /**
     * @brief   Compare two ExternalInterfacesUsageStatisticsEntry objects
     * @param   ExternalInterfacesUsageStatisticsEntry const& other - the ExternalInterfacesUsageStatisticsEntry object
     * to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(ExternalInterfacesUsageStatisticsEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two IpDroppedConnectionsEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   ExternalInterfacesUsageStatisticsEntry const& other - the ExternalInterfacesUsageStatisticsEntry object
     * to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(ExternalInterfacesUsageStatisticsEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get connectionType
     * @return  uint8_t
     */
    inline uint8_t
    GetConnectionType() const
    {
        return m_connectionType;
    }

    /**
     * @brief   get layerType
     * @return  uint16_t
     */
    inline uint16_t
    GetLayerType() const
    {
        return m_layerType;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   ExternalInterfacesUsageStatisticsEntry const& other - the ExternalInterfacesUsageStatisticsEntry object
     * to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    inline bool
    isEqual(ExternalInterfacesUsageStatisticsEntry const& other) const
    {
        return SecurityEventInstanceIdEntry::isEqual(other) && (m_connectionType == other.m_connectionType)
               && (m_layerType == other.m_layerType);
    }

private:
    uint8_t  m_connectionType{};
    uint16_t m_layerType{};
};

using SPExternalInterfacesUsageStatisticsEntry = std::shared_ptr<ExternalInterfacesUsageStatisticsEntry>;

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::ExternalInterfacesUsageStatisticsEntry;
template <>
class hash<ExternalInterfacesUsageStatisticsEntry>
{
public:
    /**
     * @brief   hash function of ExternalInterfacesUsageStatisticsEntry object
     *          Must be implemented so ExternalInterfacesUsageStatisticsEntry can be used as map key.
     * @param   ExternalInterfacesUsageStatisticsEntry entry - the ExternalInterfacesUsageStatisticsEntry object to get
     * hash for
     * @return  size_t - The hash value of the given ExternalInterfacesUsageStatisticsEntry.
     */
    size_t
    operator()(ExternalInterfacesUsageStatisticsEntry const& entry) const
    {
        std::array<size_t, 3U> hashes;
        hashes[0U] = std::hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<uint8_t>()(entry.GetConnectionType());
        hashes[2U] = hash<uint16_t>()(entry.GetLayerType());
        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // EXTERNAL_INTERFACES_USAGE_STATISTICS_ENTRY_HPP
