/**
 * @file
 * @brief     This file contains the definition of the ConnectionsCountersBaseEntry.
 */
#ifndef CONNECTIONS_COUNTERS_BASE_ENTRY_HPP
#define CONNECTIONS_COUNTERS_BASE_ENTRY_HPP

#include <string>
#include "SecurityEventInstanceIdEntry.hpp"
#include "brain/utils/IpUtils.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using brain::utils::IpType;

class ConnectionsCountersBaseEntry : public SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId - IDSm instance ID
     * @param   uint8_t sensorInstanceId - sensor instance ID
     * @param   uint16_t firewallId - firewall id
     * @param   uint16_t filterRuleId - filter rule id
     * @param   string const& filterRule - filter rule
     * @param   std::string const packageInterface[2] - incoming and outgoing package interface
     * @param   IpType const ipAddress[2U] - source and destination IP address
     * @param   uint32_t const port[2U] - source and destination Port ID
     */
    ConnectionsCountersBaseEntry(uint16_t           idsMInstanceId,
                                 uint8_t            sensorInstanceId,
                                 uint16_t           firewallId,
                                 uint16_t           filterRuleId,
                                 std::string const& filterRule,
                                 std::string const  packageInterface[2U],
                                 IpType const       ipAddress[2U],
                                 uint32_t const     port[2U])
      : SecurityEventInstanceIdEntry{idsMInstanceId, sensorInstanceId}
      , m_firewallId{firewallId}
      , m_filterRuleId{filterRuleId}
      , m_filterRule{filterRule}
      , m_incomingPackageInterface{packageInterface[0U]}
      , m_outgoingPackageInterface{packageInterface[1U]}
      , m_sourceIpAddress{ipAddress[0U]}
      , m_destinationIpAddress{ipAddress[1U]}
      , m_sourcePort{port[0U]}
      , m_destinationPort{port[1U]}
    {
    }

    /**
     * @brief   Default destructor
     */
    virtual ~ConnectionsCountersBaseEntry() = default;

    /**
     * @brief   Copy constructor from another ConnectionsCountersBaseEntry object
     *          Copies the internal data to the new object
     * @param   ConnectionsCountersBaseEntry const& other - the ConnectionsCountersBaseEntry object to copy from
     */
    ConnectionsCountersBaseEntry(ConnectionsCountersBaseEntry const& other) = default;

    /**
     * @brief    default move constructor
     */
    ConnectionsCountersBaseEntry(ConnectionsCountersBaseEntry&& other) = delete;

    /**
     * @brief   Assignment operator from another ConnectionsCountersBaseEntry object
     *          Copies the internal data to the current object
     * @param   ConnectionsCountersBaseEntry const& other - the ConnectionsCountersBaseEntry object to copy from
     * @return  ConnectionsCountersBaseEntry& - Reference to the updated ConnectionsCountersBaseEntry object
     */
    ConnectionsCountersBaseEntry& operator=(const ConnectionsCountersBaseEntry& other) = delete;

    /**
     * @brief   default move assignment operator
     */
    ConnectionsCountersBaseEntry& operator=(ConnectionsCountersBaseEntry&&) = default;

    /**
     * @brief   Compare two ConnectionsCountersBaseEntry objects
     * @param   ConnectionsCountersBaseEntry const& other - the ConnectionsCountersBaseEntry
     * object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(ConnectionsCountersBaseEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two ConnectionsCountersBaseEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   ConnectionsCountersBaseEntry const& other - the ConnectionsCountersBaseEntry
     * object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(ConnectionsCountersBaseEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get firewall id
     * @return  uint16_t
     */
    inline uint16_t
    GetFirewallId() const
    {
        return m_firewallId;
    }

    /**
     * @brief   get Incoming package interface
     * @return  std::string
     */
    inline std::string const&
    GetIncomingPackageInterface() const
    {
        return m_incomingPackageInterface;
    }

    /**
     * @brief   get Outgoing package interface
     * @return  std::string
     */
    inline std::string const&
    GetOutgoingPackageInterface() const
    {
        return m_outgoingPackageInterface;
    }

    /**
     * @brief   get filter rule id
     * @return  uint16_t
     */
    inline uint16_t
    GetFilterRuleId() const
    {
        return m_filterRuleId;
    }

    /**
     * @brief   get filter rule
     * @return  std::string
     */
    inline std::string const&
    GetFilterRule() const
    {
        return m_filterRule;
    }

    /**
     * @brief   get source ip address
     * @return  IpType
     */
    inline IpType const&
    GetSourceIpAddress() const
    {
        return m_sourceIpAddress;
    }

    /**
     * @brief   get destination ip address
     * @return  IpType
     */
    inline IpType const&
    GetDestinationIpAddress() const
    {
        return m_destinationIpAddress;
    }

    /**
     * @brief   get Source Port ID
     * @return  uint32_t
     */
    inline uint32_t
    GetSourcePort() const
    {
        return m_sourcePort;
    }

    /**
     * @brief   get Destination Port ID
     * @return  uint32_t
     */
    inline uint32_t
    GetDestinationPort() const
    {
        return m_destinationPort;
    }


protected:
    /**
     * @brief   copy the internal data
     * @param   ConnectionsCountersBaseEntry const& other - the ConnectionsCountersBaseEntry
     * object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(ConnectionsCountersBaseEntry const& other) const
    {
        return SecurityEventInstanceIdEntry::isEqual(other) && (other.m_firewallId == m_firewallId)
               && (other.m_filterRuleId == m_filterRuleId) && (other.m_filterRule == m_filterRule)
               && (other.m_incomingPackageInterface == m_incomingPackageInterface)
               && (other.m_outgoingPackageInterface == m_outgoingPackageInterface)
               && (other.m_sourceIpAddress == m_sourceIpAddress)
               && (other.m_destinationIpAddress == m_destinationIpAddress) && (other.m_sourcePort == m_sourcePort)
               && (other.m_destinationPort == m_destinationPort);
    }

private:
    uint16_t    m_firewallId{};
    uint16_t    m_filterRuleId{};
    std::string m_filterRule;
    std::string m_incomingPackageInterface;
    std::string m_outgoingPackageInterface;
    IpType      m_sourceIpAddress;
    IpType      m_destinationIpAddress;
    uint32_t    m_sourcePort{};
    uint32_t    m_destinationPort{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{

using brain::engines::security_events::ConnectionsCountersBaseEntry;

template <>
class hash<ConnectionsCountersBaseEntry>
{
public:
    /**
     * @brief   hash function of ConnectionsCountersBaseEntry object
     *          Must be implemented so ConnectionsCountersBaseEntry can be used as map key.
     * @param   ConnectionsCountersBaseEntry entry - the ConnectionsCountersBaseEntry object to get hash for
     * @return  size_t - The hash value of the given ConnectionsCountersBaseEntry.
     */
    size_t
    operator()(ConnectionsCountersBaseEntry const& entry) const
    {
        std::array<size_t, 10U> hashes;

        hashes[0U] = hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<uint16_t>()(entry.GetFirewallId());
        hashes[2U] = hash<uint16_t>()(entry.GetFilterRuleId());
        hashes[3U] = hash<string>()(entry.GetFilterRule());
        hashes[4U] = hash<string>()(entry.GetIncomingPackageInterface());
        hashes[5U] = hash<string>()(entry.GetOutgoingPackageInterface());
        hashes[6U] = hash<IpType>()(entry.GetSourceIpAddress());
        hashes[7U] = hash<IpType>()(entry.GetDestinationIpAddress());
        hashes[8U] = hash<uint32_t>()(entry.GetSourcePort());
        hashes[9U] = hash<uint32_t>()(entry.GetDestinationPort());

        return common::utils::CombineHash(hashes);
    }
};

}  // namespace std

#endif  // CONNECTIONS_COUNTERS_BASE_ENTRY_HPP