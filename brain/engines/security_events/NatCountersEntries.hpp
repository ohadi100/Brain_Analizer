/**
 * @file
 * @brief     This file contains the definition of the NatCountersEntries struct, which represents a record in a Nat
 * table.
 */
#ifndef NAT_COUNTERS_ENTRIES_HPP
#define NAT_COUNTERS_ENTRIES_HPP

#include <stdint.h>
#include "brain/utils/IpUtils.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

class NatCountersEntriesStruct
{
public:    
    brain::utils::IpType m_internalIpAddress{};
    uint32_t             m_externalServerIpAddress{};
    uint8_t              m_transportProtocol{};
    uint16_t             m_internalTransportSourcePort{};
    uint16_t             m_externalTransportSourcePort{};

    bool
    operator==(NatCountersEntriesStruct const& rhs) const
    {
        return (m_internalIpAddress == rhs.m_internalIpAddress)
               && (m_externalServerIpAddress == rhs.m_externalServerIpAddress)
               && (m_transportProtocol == rhs.m_transportProtocol)
               && (m_internalTransportSourcePort == rhs.m_internalTransportSourcePort)
               && (m_externalTransportSourcePort == rhs.m_externalTransportSourcePort);
    }
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

#endif  // NAT_COUNTERS_ENTRIES_HPP
