/**
 * @file
 * @brief     This file contains the definition of the DroppedConnectionsCountersEntry.
 */
#ifndef DROPPED_CONNECTIONS_COUNTERS_ENTRY_HPP
#define DROPPED_CONNECTIONS_COUNTERS_ENTRY_HPP

#include "ConnectionsCountersBaseEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using brain::utils::IpType;

class DroppedConnectionsCountersEntry final : public ConnectionsCountersBaseEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId - IDSm instance ID
     * @param   uint8_t sensorInstanceId - sensor instance ID
     * @param   uint32_t serviceVersion - service version
     * @param   uint16_t firewallId - firewall id
     * @param   uint16_t filterRuleId - filter rule id
     * @param   string const& filterRule - filter rule
     * @param   std::string const packageInterface[2] - incoming and outgoing package interface
     * @param   IpType const ipAddress[2U] - source and destination IP address
     * @param   string const& transportProtocol - transport protocol
     * @param   uint32_t const port[2U] - source and destination Port ID
     * @param   string const& userName - user name
     * @param   string const& processName - process name
     */
    DroppedConnectionsCountersEntry(uint16_t           idsMInstanceId,
                                    uint8_t            sensorInstanceId,
                                    uint32_t           serviceVersion,
                                    uint16_t           firewallId,
                                    uint16_t           filterRuleId,
                                    std::string const& filterRule,
                                    std::string const  packageInterface[2],
                                    IpType const       ipAddress[2],
                                    std::string const& transportProtocol,
                                    uint32_t const     port[2],
                                    std::string const& userName,
                                    std::string const& processName)
      : ConnectionsCountersBaseEntry(
          idsMInstanceId, sensorInstanceId, firewallId, filterRuleId, filterRule, packageInterface, ipAddress, port)
      , m_serviceVersion{serviceVersion}
      , m_transportProtocol{transportProtocol}
      , m_userName{userName}
      , m_processName{processName}
    {
    }

    /**
     * @brief   Compare two DroppedConnectionsCountersEntry objects
     * @param   DroppedConnectionsCountersEntry const& other - the DroppedConnectionsCountersEntry
     * object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(DroppedConnectionsCountersEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two DroppedConnectionsCountersEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   DroppedConnectionsCountersEntry const& other - the DroppedConnectionsCountersEntry
     * object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(DroppedConnectionsCountersEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get service version
     * @return  uint32_t
     */
    inline uint32_t
    GetServiceVersion() const
    {
        return m_serviceVersion;
    }

    /**
     * @brief   get transport protocol
     * @return  std::string
     */
    inline std::string const&
    GetTransportProtocol() const
    {
        return m_transportProtocol;
    }

    /**
     * @brief   get user name
     * @return  std::string
     */
    inline std::string const&
    GetUserName() const
    {
        return m_userName;
    }

    /**
     * @brief   get process name
     * @return  std::string
     */
    inline std::string const&
    GetProcessName() const
    {
        return m_processName;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   DroppedConnectionsCountersEntry const& other - the DroppedConnectionsCountersEntry
     * object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(DroppedConnectionsCountersEntry const& other) const
    {
        return ConnectionsCountersBaseEntry::isEqual(other) && (other.m_serviceVersion == m_serviceVersion)
               && (other.m_transportProtocol == m_transportProtocol) && (other.m_userName == m_userName)
               && (other.m_processName == m_processName);
    }

private:
    uint32_t    m_serviceVersion{};
    std::string m_transportProtocol;
    std::string m_userName;
    std::string m_processName;
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{

using brain::engines::security_events::DroppedConnectionsCountersEntry;

template <>
class hash<DroppedConnectionsCountersEntry>
{
public:
    /**
     * @brief   hash function of DroppedConnectionsCountersEntry object
     *          Must be implemented so DroppedConnectionsCountersEntry can be used as map key.
     * @param   DroppedConnectionsCountersEntry entry - the DroppedConnectionsCountersEntry object to get hash for
     * @return  size_t - The hash value of the given DroppedConnectionsCountersEntry.
     */
    size_t
    operator()(DroppedConnectionsCountersEntry const& entry) const
    {
        std::array<size_t, 5U> hashes;
        hashes[0U] = hash<ConnectionsCountersBaseEntry>()(entry);
        hashes[1U] = hash<uint32_t>()(entry.GetServiceVersion());
        hashes[2U] = hash<std::string>()(entry.GetTransportProtocol());
        hashes[3U] = hash<std::string>()(entry.GetUserName());
        hashes[4U] = hash<std::string>()(entry.GetProcessName());

        return common::utils::CombineHash(hashes);
    }
};

}  // namespace std

#endif  // DROPPED_CONNECTIONS_COUNTERS_ENTRY_HPP