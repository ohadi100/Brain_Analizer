/**
 * @file
 * @brief     This file contains the definition of the DhmDroppedSecurityEventsCountersEntry class and its
 * functionality. DhmDroppedSecurityEventsCountersEntry contains dhm constraint id drop reason used as table key.
 */
#ifndef DHM_DROPPED_SECURITY_EVENTS_COUNTERS_ENTRY_HPP
#define DHM_DROPPED_SECURITY_EVENTS_COUNTERS_ENTRY_HPP

#include "SecurityEventsHelper.hpp"
#include "brain/sensor_data/swpac/IncidentHelper.hpp"
#include "common/utils/HashUtils.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

class DhmDroppedSecurityEventsCountersEntry final
{
public:
    using ConstraintId = brain::sensor_data::swpac::ConstraintId;
    using DropReason   = brain::engines::security_events::DropReason;
    /**
     * @brief   Constructor
     * @param   cpnstraintId - dhm constraint id
     * @param   dropReason - drop reason
     */
    DhmDroppedSecurityEventsCountersEntry(ConstraintId constraintId, DropReason dropReason)
      : m_constraintId{constraintId}
      , m_dropReason{dropReason}
    {
    }

    /**
     * @brief   Compare two DhmDroppedSecurityEventsCountersEntry objects
     * @param   DhmDroppedSecurityEventsCountersEntry other - the DhmDroppedSecurityEventsCountersEntry object to
     * compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    bool
    operator==(DhmDroppedSecurityEventsCountersEntry other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two DhmDroppedSecurityEventsCountersEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   DhmDroppedSecurityEventsCountersEntry other - the DhmDroppedSecurityEventsCountersEntry object to
     * compare to
     * @return  bool - true any field is different. false otherwise
     */
    bool
    operator!=(DhmDroppedSecurityEventsCountersEntry other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get dhm constraint id
     * @return  brain::sensor_data::swpac::ConstraintId
     */
    inline constexpr brain::sensor_data::swpac::ConstraintId
    GetConstraintId() const
    {
        return m_constraintId;
    }

    /**
     * @brief   get drop reason
     * @return  SecurityEventsEngine::DropReason
     */
    inline constexpr DropReason
    GetDropReason() const
    {
        return m_dropReason;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   DhmDroppedSecurityEventsCountersEntry other - the DhmDroppedSecurityEventsCountersEntry object to
     * check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(DhmDroppedSecurityEventsCountersEntry other) const
    {
        return (other.m_constraintId == m_constraintId) && (other.m_dropReason == m_dropReason);
    }

private:
    brain::sensor_data::swpac::ConstraintId m_constraintId;
    DropReason                              m_dropReason;
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::DhmDroppedSecurityEventsCountersEntry;

template <>
class hash<DhmDroppedSecurityEventsCountersEntry>
{
public:
    /**
     * @brief   hash function of DhmDroppedSecurityEventsCountersEntry object
     *          Must be implemented so DhmDroppedSecurityEventsCountersEntry can be used as map key.
     * @param   DhmDroppedSecurityEventsCountersEntry entry - the DhmDroppedSecurityEventsCountersEntry object to get
     * hash for
     * @return  size_t - The hash value of the given DhmDroppedSecurityEventsCountersEntry.
     */
    size_t
    operator()(DhmDroppedSecurityEventsCountersEntry entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = hash<brain::sensor_data::swpac::ConstraintId>()(entry.GetConstraintId());
        hashes[1U] = hash<brain::engines::security_events::DropReason>()(entry.GetDropReason());
        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // DHM_DROPPED_SECURITY_EVENTS_COUNTERS_ENTRY_HPP