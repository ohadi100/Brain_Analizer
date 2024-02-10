/**
 * @file
 * @brief     This file contains the functionality of the IpDroppedConnectionsEntry class and its functionality
 */
#include "IpDroppedConnectionsEntry.hpp"

using brain::engines::security_events::IpDroppedConnectionsEntry;
using brain::utils::IpType;

IpDroppedConnectionsEntry::IpDroppedConnectionsEntry(IpType const&      sourceIp,
                                                     std::string const& transportProtocol,
                                                     uint32_t           sourcePort)
  : m_sourceIp(sourceIp)
  , m_transportProtocol(transportProtocol)
  , m_sourcePort(sourcePort)
{
}

bool
IpDroppedConnectionsEntry::operator==(IpDroppedConnectionsEntry const& other) const
{
    return isEqual(other);
}

bool
IpDroppedConnectionsEntry::operator!=(IpDroppedConnectionsEntry const& other) const
{
    return !isEqual(other);
}

bool
IpDroppedConnectionsEntry::isEqual(IpDroppedConnectionsEntry const& other) const
{
    if (m_sourceIp != other.m_sourceIp)
    {
        return false;
    }

    if (m_transportProtocol != other.m_transportProtocol)
    {
        return false;
    }

    if (m_sourcePort != other.m_sourcePort)
    {
        return false;
    }

    return true;
}
