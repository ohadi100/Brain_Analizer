/**
 * @file
 * @brief     This file contains the definition of the MacToIpAssociationEntry.
 */
#ifndef MAC_TO_IP_ASSOCIATION_ENTRY_HPP
#define MAC_TO_IP_ASSOCIATION_ENTRY_HPP

#include <array>
#include "brain/utils/IpUtils.hpp"
#include "common/utils/HashUtils.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using brain::utils::IpType;

class MacToIpAssociationEntry final
{
public:
    /**
     * @brief   Constructor
     * @param   IpType const& ipAddress - IP address
     * @param   uint64_t macAddress - MAC Address
     */
    MacToIpAssociationEntry(IpType const& ipAddress, uint64_t macAddress)
      : m_ipAddress{ipAddress}
      , m_macAddress{macAddress}
    {
    }

    /**
     * @brief   Compare two MacToIpAssociationEntry objects
     * @param   MacToIpAssociationEntry const& other - the MacToIpAssociationEntry
     * object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(MacToIpAssociationEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two MacToIpAssociationEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   MacToIpAssociationEntry const& other - the MacToIpAssociationEntry
     * object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(MacToIpAssociationEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get IP address
     * @return  IpType
     */
    inline IpType const&
    GetIpAddress() const
    {
        return m_ipAddress;
    }

    /**
     * @brief   get MAC Address
     * @return  uint64_t
     */
    inline uint64_t
    GetMacAddress() const
    {
        return m_macAddress;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   MacToIpAssociationEntry const& other - the MacToIpAssociationEntry
     * object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(MacToIpAssociationEntry const& other) const
    {
        return (other.m_ipAddress == m_ipAddress) && (other.m_macAddress == m_macAddress);
    }

private:
    IpType   m_ipAddress;
    uint64_t m_macAddress{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::MacToIpAssociationEntry;

template <>
class hash<MacToIpAssociationEntry>
{
public:
    /**
     * @brief   hash function of MacToIpAssociationEntry object
     *          Must be implemented so MacToIpAssociationEntry can be used as map key.
     * @param   MacToIpAssociationEntry entry - the MacToIpAssociationEntry object to get hash for
     * @return  size_t - The hash value of the given MacToIpAssociationEntry.
     */
    size_t
    operator()(MacToIpAssociationEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = hash<IpType>()(entry.GetIpAddress());
        hashes[1U] = hash<uint64_t>()(entry.GetMacAddress());

        return common::utils::CombineHash(hashes);
    }
};

}  // namespace std

#endif  // MAC_TO_IP_ASSOCIATION_ENTRY_HPP