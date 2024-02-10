/**
 * @file
 * @brief     This file contains the definition of the NatCountersTableEntry class and its functionality.
 *            Basically this class represents the key entries in the Nat table.
 */
#ifndef NAT_COUNTERS_TABLE_ENTRY_HPP
#define NAT_COUNTERS_TABLE_ENTRY_HPP

#include "SecurityEventInstanceIdEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

/**
 * @class       NatCountersTableEntry
 */
class NatCountersTableEntry : public SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId
     * @param   uint8_t sensorInstanceId
     * @param   uint8_t natIdentifier
     * @return	none
     */
    NatCountersTableEntry(uint16_t idsMInstanceId, uint8_t sensorInstanceId, uint16_t natIdentifier)
      : SecurityEventInstanceIdEntry(idsMInstanceId, sensorInstanceId)
      , m_natIdentifier(natIdentifier)
    {
    }

    /**
     * @brief   Compare two NatCountersTableEntry objects
     * @param   NatCountersTableEntry const& other - the NatCountersTableEntry object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(NatCountersTableEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two NatCountersTableEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   NatCountersTableEntry const& other - the NatCountersTableEntry object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(NatCountersTableEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get the Nat identifier
     * @return  uint8_t
     */
    inline uint16_t
    GetNatIdentifier() const
    {
        return m_natIdentifier;
    }

protected:
    /**
     * @brief   compare data and return the result
     * @param   NatCountersTableEntry const& other - the NatCountersTableEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(NatCountersTableEntry const& other) const
    {
        return SecurityEventInstanceIdEntry::isEqual(other) && (other.m_natIdentifier == m_natIdentifier);
    }

private:
    uint16_t m_natIdentifier{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::NatCountersTableEntry;
template <>
class hash<NatCountersTableEntry>
{
public:
    /**
     * @brief   hash function of NatCountersTableEntry object
     *          Must be implemented so NatCountersTableEntry can be used as map key.
     * @param   NatCountersTableEntry entry - the NatCountersTableEntry object to get hash for
     * @return  size_t - The hash value of the given NatCountersTableEntry.
     */
    size_t
    operator()(NatCountersTableEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = std::hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<uint16_t>()(entry.GetNatIdentifier());
        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // NAT_COUNTERS_TABLE_ENTRY_HPP
