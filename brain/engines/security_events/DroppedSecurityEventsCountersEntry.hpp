/**
 * @file
 * @brief     This file contains the definition of the DroppedSecurityEventsCountersEntry class and its functionality.
 *            DroppedSecurityEventsCountersEntry contains IDSm instance ID, sensor instance ID, security event ID and
 * drop reason used as table key.
 */
#ifndef DROPPED_SECURITY_EVENTS_COUNTERS_ENTRY_HPP
#define DROPPED_SECURITY_EVENTS_COUNTERS_ENTRY_HPP

#include "SecurityEventInstanceIdEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

class DroppedSecurityEventsCountersEntry final : public SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId
     * @param   uint8_t sensorInstanceId
     * @param   uint16_t securityEventId
     * @param   std::string const& dropReason
     */
    DroppedSecurityEventsCountersEntry(uint16_t           idsMInstanceId,
                                       uint8_t            sensorInstanceId,
                                       uint16_t           securityEventId,
                                       std::string const& dropReason)
      : SecurityEventInstanceIdEntry(idsMInstanceId, sensorInstanceId)
      , m_securityEventId{securityEventId}
      , m_dropReason{dropReason}
    {
    }

    /**
     * @brief   Compare two DroppedSecurityEventsCountersEntry objects
     * @param   DroppedSecurityEventsCountersEntry const& other - the DroppedSecurityEventsCountersEntry object to
     * compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    bool
    operator==(DroppedSecurityEventsCountersEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two DroppedSecurityEventsCountersEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   DroppedSecurityEventsCountersEntry const& other - the DroppedSecurityEventsCountersEntry object to
     * compare to
     * @return  bool - true any field is different. false otherwise
     */
    bool
    operator!=(DroppedSecurityEventsCountersEntry const& other) const
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

    /**
     * @brief   get drop reason
     * @return  std::string const&
     */
    inline std::string const& GetDropReason() const
    {
        return m_dropReason;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   DroppedSecurityEventsCountersEntry const& other - the DroppedSecurityEventsCountersEntry object to check
     * if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(DroppedSecurityEventsCountersEntry const& other) const
    {
        return SecurityEventInstanceIdEntry::isEqual(other) && (other.m_securityEventId == m_securityEventId)
               && (other.m_dropReason == m_dropReason);
    }

private:
    uint16_t m_securityEventId{};
    std::string m_dropReason;
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::DroppedSecurityEventsCountersEntry;

template <>
class hash<DroppedSecurityEventsCountersEntry>
{
public:
    /**
     * @brief   hash function of DroppedSecurityEventsCountersEntry object
     *          Must be implemented so DroppedSecurityEventsCountersEntry can be used as map key.
     * @param   DroppedSecurityEventsCountersEntry entry - the DroppedSecurityEventsCountersEntry object to get hash for
     * @return  size_t - The hash value of the given DroppedSecurityEventsCountersEntry.
     */
    size_t
    operator()(DroppedSecurityEventsCountersEntry const& entry) const
    {
        std::array<size_t, 3U> hashes;
        hashes[0U] = hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<uint16_t>()(entry.GetSecurityEventId());
        hashes[2U] = hash<std::string>()(entry.GetDropReason());
        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // DROPPED_SECURITY_EVENTS_COUNTERS_ENTRY_HPP
