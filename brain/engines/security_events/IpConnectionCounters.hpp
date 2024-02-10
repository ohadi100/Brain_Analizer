/**
 * @file
 * @brief     This file contains the definition of the IpConnectionCountersEntry and IpConnectionCountersValue.
 *            IpConnectionCountersEntry contains EthIdType and VlanTag.
 *            IpConnectionCountersValue contains dropped/blocked connections & successful connections counters.
 */
#ifndef IP_CONNECTION_COUNTERS_HPP
#define IP_CONNECTION_COUNTERS_HPP

#include <stdint.h>
#include <memory>
#include "brain/utils/IpUtils.hpp"
#include "common/utils/HashUtils.hpp"


namespace brain
{
namespace engines
{
namespace security_events
{

/**
 * @struct              IpConnectionCountersEntry
 * @brief               The IpConnectionCountersEntry holds EthIdType and VlanTag
 * @internalInterfaces  The IpConnectionCountersEntry provides a type representation and hash function, so it can be used as unordered map key.
 */
class IpConnectionCountersEntry
{
public:
    bool operator==(IpConnectionCountersEntry rhs) const
    {
        return ((ethIdType == rhs.ethIdType) && (vlanTag == rhs.vlanTag));
    }

    uint8_t ethIdType = 0U;
    uint16_t vlanTag = 0U;
};


/**
 * @struct              IpConnectionCountersValue
 * @brief               The IpConnectionCountersValue holds dropped/blocked connections & successful connections counters
 */
class IpConnectionCountersValue
{
public:
    bool operator==(IpConnectionCountersValue rhs) const
    {
        return ((droppedBlockedConnections == rhs.droppedBlockedConnections) 
                && (successfulConnections == rhs.successfulConnections));
    }

    uint32_t droppedBlockedConnections = 0U;
    uint32_t successfulConnections = 0U;
};

} // namespace security_events
} // namespace engines
} // namespace brain

namespace std
{
using brain::engines::security_events::IpConnectionCountersEntry;

template <>
class hash<IpConnectionCountersEntry>
{
public:
    /**
     * @brief   hash function of IpConnectionCountersEntry object
     *          Must be implemented so IpConnectionCountersEntry can be used as map key.
     * @param   IpConnectionCountersEntry entry - the IpConnectionCountersEntry object to get hash for
     * @return  size_t - The hash value of the given IpConnectionCountersEntry.
     */
    size_t
    operator()(IpConnectionCountersEntry entry) const
    {
        std::array<size_t, 2U> hashes;

        hashes[0U] = hash<uint8_t>()(entry.ethIdType);
        hashes[1U] = hash<uint16_t>()(entry.vlanTag);

        return common::utils::CombineHash(hashes);
    }
};
}

#endif // IP_CONNECTION_COUNTERS_HPP