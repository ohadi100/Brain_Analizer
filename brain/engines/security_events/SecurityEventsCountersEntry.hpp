/**
 * @file
 * @brief     This file contains the definition of the SecurityEventsCountersEntry class and its functionality.
 *            SecurityEventsCountersEntry contains IDSm instance ID, sensor instance ID and security event ID used as
 * table key.
 */
#ifndef SECURITY_EVENTS_COUNTERS_ENTRY_HPP
#define SECURITY_EVENTS_COUNTERS_ENTRY_HPP

#include "SecurityEventInstanceIdEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

class SecurityEventsCountersEntry final : public SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId
     * @param   uint8_t sensorInstanceId
     * @param   uint16_t securityEventId
     */
    SecurityEventsCountersEntry(uint16_t idsMInstanceId, uint8_t sensorInstanceId, uint16_t securityEventId)
      : SecurityEventInstanceIdEntry(idsMInstanceId, sensorInstanceId)
      , m_securityEventId(securityEventId)
    {
    }

    /**
     * @brief   Compare two SecurityEventsCountersEntry objects
     * @param   SecurityEventsCountersEntry const& other - the SecurityEventsCountersEntry object to compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    bool
    operator==(SecurityEventsCountersEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two SecurityEventsCountersEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   SecurityEventsCountersEntry const& other - the SecurityEventsCountersEntry object to compare to
     * @return  bool - true any field is different. false otherwise
     */
    bool
    operator!=(SecurityEventsCountersEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get security event ID
     * @return  uint16_t
     */
    inline uint16_t
    GetSecurityEventId() const
    {
        return m_securityEventId;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   SecurityEventsCountersEntry const& other - the SecurityEventsCountersEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(SecurityEventsCountersEntry const& other) const
    {
        return (other.m_securityEventId == m_securityEventId) && SecurityEventInstanceIdEntry::isEqual(other);
    }

private:
    uint16_t m_securityEventId{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::SecurityEventsCountersEntry;

template <>
class hash<SecurityEventsCountersEntry>
{
public:
    /**
     * @brief   hash function of SecurityEventsCountersEntry object
     *          Must be implemented so SecurityEventsCountersEntry can be used as map key.
     * @param   SecurityEventsCountersEntry entry - the SecurityEventsCountersEntry object to get hash for
     * @return  size_t - The hash value of the given SecurityEventsCountersEntry.
     */
    size_t
    operator()(SecurityEventsCountersEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<uint16_t>()(entry.GetSecurityEventId());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // SECURITY_EVENTS_COUNTERS_ENTRY_HPP