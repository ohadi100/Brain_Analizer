/**
 * @file
 * @brief     This file contains the definition of the HostOsLogEntry class and its functionality.
 */
#ifndef HOST_OS_LOG_ENTRY_HPP
#define HOST_OS_LOG_ENTRY_HPP

#include "SecurityEventInstanceIdEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

/**
 * @class       HostOsLogEntry
 */
class HostOsLogEntry : public SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId
     * @param   uint8_t sensorInstanceId
     * @param   uint8_t vmIdentifier
     * @return	none
     */
    HostOsLogEntry(uint16_t idsMInstanceId, uint8_t sensorInstanceId, uint8_t vmIdentifier)
      : SecurityEventInstanceIdEntry(idsMInstanceId, sensorInstanceId)
      , m_vmIdentifier(vmIdentifier)
    {
    }

    /**
     * @brief   Compare two IpDroppedConnectionsEntry objects
     * @param   HostOsLogEntry const& other - the HostOsLogEntry object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(HostOsLogEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two IpDroppedConnectionsEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   HostOsLogEntry const& other - the HostOsLogEntry object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(HostOsLogEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get vmIdentifier
     * @return  uint8_t
     */
    inline uint8_t
    GetVmIdentifier() const
    {
        return m_vmIdentifier;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   HostOsLogEntry const& other - the HostOsLogEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    inline bool
    isEqual(HostOsLogEntry const& other) const
    {
        return SecurityEventInstanceIdEntry::isEqual(other) && (m_vmIdentifier == other.m_vmIdentifier);
    }

private:
    uint8_t m_vmIdentifier{};
};

using SPHostOsLogEntry = std::shared_ptr<HostOsLogEntry>;

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::HostOsLogEntry;
template <>
class hash<HostOsLogEntry>
{
public:
    /**
     * @brief   hash function of HostOsLogEntry object
     *          Must be implemented so HostOsLogEntry can be used as map key.
     * @param   HostOsLogEntry entry - the HostOsLogEntry object to get hash for
     * @return  size_t - The hash value of the given HostOsLogEntry.
     */
    size_t
    operator()(HostOsLogEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = std::hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<uint8_t>()(entry.GetVmIdentifier());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // HOST_OS_LOG_ENTRY_HPP
