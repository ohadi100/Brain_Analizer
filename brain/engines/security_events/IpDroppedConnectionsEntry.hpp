/**
 * @file
 * @brief     This file contains the definition of the IpDroppedConnectionsEntry class and its functionality.
 *            IpDroppedConnectionsEntry Ip address, transport protocol and source port.
 */
#ifndef IP_DROPPED_CONNECTIONS_ENTRY_HPP
#define IP_DROPPED_CONNECTIONS_ENTRY_HPP

#include <memory>
#include "brain/utils/IpUtils.hpp"
#include "common/utils/HashUtils.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using brain::utils::IpType;

/**
 * @class               IpDroppedConnectionsEntry
 * @brief               The IpDroppedConnectionsEntry class Ip address, transport protocol and source port
 * @internalInterfaces  The IpDroppedConnectionsEntry provides a type representation and hash function, so it can be
 * used as unordered map key.
 */
class IpDroppedConnectionsEntry final
{
public:
    /**
     * @brief   Constructor
     * @param   IpType const& sourceIp - source ip address
     * @param   std::string const& transportProtocol
     * @param   uint32_t sourcePort
     */
    IpDroppedConnectionsEntry(IpType const& sourceIp, std::string const& transportProtocol, uint32_t sourcePort);

    /**
     * @brief   Compare two IpDroppedConnectionsEntry objects
     * @param   IpDroppedConnectionsEntry const& other - the IpDroppedConnectionsEntry object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool operator==(IpDroppedConnectionsEntry const& other) const;

    /**
     * @brief   Compare two IpDroppedConnectionsEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   IpDroppedConnectionsEntry const& other - the IpDroppedConnectionsEntry object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool operator!=(IpDroppedConnectionsEntry const& other) const;

    /**
     * @brief   get source IP address
     * @return  IpType
     */
    inline IpType const&
    GetSourceIp() const
    {
        return m_sourceIp;
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
     * @brief   get source port
     * @return  uint32_t
     */
    inline uint32_t
    GetSourcePort() const
    {
        return m_sourcePort;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   IpDroppedConnectionsEntry const& other - the IpDroppedConnectionsEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool isEqual(IpDroppedConnectionsEntry const& other) const;

private:
    IpType      m_sourceIp{};
    std::string m_transportProtocol;
    uint32_t    m_sourcePort{};
};

using SPIpDroppedConnectionsEntry = std::shared_ptr<IpDroppedConnectionsEntry>;

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::IpDroppedConnectionsEntry;
using IpType = brain::utils::IpType;

template <>
class hash<IpDroppedConnectionsEntry>
{
public:
    /**
     * @brief   hash function of IpDroppedConnectionsEntry object
     *          Must be implemented so IpDroppedConnectionsEntry can be used as map key.
     * @param   IpDroppedConnectionsEntry entry - the IpDroppedConnectionsEntry object to get hash for
     * @return  size_t - The hash value of the given IpDroppedConnectionsEntry.
     */
    size_t
    operator()(IpDroppedConnectionsEntry const& entry) const
    {
        std::array<size_t, 3U> hashes;
        hashes[0U] = hash<IpType>()(entry.GetSourceIp());
        hashes[1U] = hash<std::string>()(entry.GetTransportProtocol());
        hashes[2U] = hash<uint32_t>()(entry.GetSourcePort());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // IP_DROPPED_CONNECTIONS_ENTRY_HPP