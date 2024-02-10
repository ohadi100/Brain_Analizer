/**
 * @file
 * @brief     This file contains the definition of the ConnectionsCountersEntry.
 */
#ifndef CONNECTIONS_COUNTERS_ENTRY_HPP
#define CONNECTIONS_COUNTERS_ENTRY_HPP

#include "ConnectionsCountersBaseEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using brain::utils::IpType;

class ConnectionsCountersEntry final : public ConnectionsCountersBaseEntry
{
public:
    /**
     * @brief   Default Constructor (needed for UT)
     */
    ConnectionsCountersEntry() = default;

    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId - IDSm instance ID
     * @param   uint8_t sensorInstanceId - sensor instance ID
     * @param   uint8_t ethIdType - ETH-ID standard whitelist
     * @param   uint16_t firewallId - firewall id
     * @param   uint16_t filterRuleId - filter rule id
     * @param   string const& filterRule - filter rule
     * @param   std::string const packageInterface[2] - incoming and outgoing package interface
     * @param   IpType const ipAddress[2U] - source and destination IP address
     * @param   string const& tmProtocol - tm Protocol
     * @param   uint32_t const port[2U] - source and destination Port ID
     * @param   uint64_t const mac[2] - source and destination MAC Address
     * @param   uint16_t vlanTag - VLAN TAG
     */
    ConnectionsCountersEntry(uint16_t           idsMInstanceId,
                             uint8_t            sensorInstanceId,
                             uint8_t            ethIdType,
                             uint16_t           firewallId,
                             uint16_t           filterRuleId,
                             std::string const& filterRule,
                             std::string const  packageInterface[2],
                             IpType const       ipAddress[2],
                             std::string        tmProtocol,
                             uint32_t const     port[2],
                             uint64_t const     mac[2],
                             uint16_t           vlanTag)
      : ConnectionsCountersBaseEntry(
          idsMInstanceId, sensorInstanceId, firewallId, filterRuleId, filterRule, packageInterface, ipAddress, port)
      , m_ethIdType{ethIdType}
      , m_tmProtocol{tmProtocol}
      , m_sourceMacAddress{mac[0U]}
      , m_destinationMacAddress{mac[1U]}
      , m_vlanTag{vlanTag}
    {
    }

    /**
     * @brief   Compare two ConnectionsCountersEntry objects
     * @param   ConnectionsCountersEntry const& other - the ConnectionsCountersEntry
     * object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(ConnectionsCountersEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two ConnectionsCountersEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   ConnectionsCountersEntry const& other - the ConnectionsCountersEntry
     * object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(ConnectionsCountersEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get ETH-ID standard whitelist
     * @return  uint8_t
     */
    inline uint8_t
    GetEthIdType() const
    {
        return m_ethIdType;
    }

    /**
     * @brief   get tm protocol
     * @return  std::string
     */
    inline std::string const&
    GetTmProtocol() const
    {
        return m_tmProtocol;
    }

    /**
     * @brief   get VLAN TAG
     * @return  uint16_t
     */
    inline uint16_t
    GetVlanTag() const
    {
        return m_vlanTag;
    }

    /**
     * @brief   get source mac address
     * @return  uint64
     */
    inline uint64_t
    GetSourceMacAddress() const
    {
        return m_sourceMacAddress;
    }

    /**
     * @brief   get destination mac address
     * @return  uint64
     */
    inline uint64_t
    GetDestinationMacAddress() const
    {
        return m_destinationMacAddress;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   ConnectionsCountersEntry const& other - the ConnectionsCountersEntry
     * object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(ConnectionsCountersEntry const& other) const
    {
        return ConnectionsCountersBaseEntry::isEqual(other) && (other.m_ethIdType == m_ethIdType)
               && (other.m_tmProtocol == m_tmProtocol) && (other.m_sourceMacAddress == m_sourceMacAddress)
               && (other.m_destinationMacAddress == m_destinationMacAddress) && (other.m_vlanTag == m_vlanTag);
    }

private:
    uint8_t                 m_ethIdType{};
    std::string             m_tmProtocol;
    uint64_t                m_sourceMacAddress{};
    uint64_t                m_destinationMacAddress{};
    uint16_t                m_vlanTag{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{

using brain::engines::security_events::ConnectionsCountersEntry;

template <>
class hash<ConnectionsCountersEntry>
{
public:
    /**
     * @brief   hash function of ConnectionsCountersEntry object
     *          Must be implemented so ConnectionsCountersEntry can be used as map key.
     * @param   ConnectionsCountersEntry entry - the ConnectionsCountersEntry object to get hash for
     * @return  size_t - The hash value of the given ConnectionsCountersEntry.
     */
    size_t
    operator()(ConnectionsCountersEntry const& entry) const
    {
        std::array<size_t, 6U> hashes;

        hashes[0U]  = hash<ConnectionsCountersBaseEntry>()(entry);
        hashes[1U]  = hash<uint8_t>()(entry.GetEthIdType());
        hashes[2U]  = hash<string>()(entry.GetTmProtocol());
        hashes[3U]  = hash<uint64_t>()(entry.GetSourceMacAddress());
        hashes[4U]  = hash<uint64_t>()(entry.GetDestinationMacAddress());
        hashes[5U]  = hash<uint16_t>()(entry.GetVlanTag());

        return common::utils::CombineHash(hashes);
    }
};

}  // namespace std

#endif  // CONNECTIONS_COUNTERS_ENTRY_HPP