/**
 * @file
 * @brief     This file contains the definitiond of the CanIfSevErrorStateEntry.
 */
#pragma once

#include "SecurityEventInstanceIdEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

/**
 * @class CanIfSevErrorStateEntry
 * @brief The CanIfSevErrorStateEntry holds the table keys of canIfErrorStateCounters table
 */
class CanIfSevErrorStateEntry final : public SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief Constructs a CAN Interface Security Event Error State Entry from given IDs/state.
     * @param[in] idsMInstanceId   IDSm instance ID
     * @param[in] sensorInstanceId sensor instance ID
     * @param[in] state            given error state (0-PassiveMode, 1-Busoff)
     */
    CanIfSevErrorStateEntry(uint16_t idsMInstanceId, uint8_t sensorInstanceId, uint8_t state)
      : SecurityEventInstanceIdEntry(idsMInstanceId, sensorInstanceId)
      , m_state{state}
    {
    }

    /**
     * @brief Compare two CanIfSevErrorStateEntry objects
     * @param[in] other - the CanIfSevErrorStateEntry object to compare to
     * @return true all fields are equal. false otherwise
     */
    inline bool
    operator==(CanIfSevErrorStateEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief Compare two CanIfSevErrorStateEntry objects, checks if different
     *        Objects are not equal, if any of the fields aren't equal
     * @param[in] other - the CanIfSevErrorStateEntry object to compare to
     * @return true any field is different. false otherwise
     */
    inline bool
    operator!=(CanIfSevErrorStateEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get state
     * @return  uint8_t
     */
    inline constexpr uint8_t
    GetState() const
    {
        return m_state;
    }

protected:
    /**
     * @brief copy the internal data
     * @param[in] other the CanIfSevErrorStateEntry object to check if equal
     * @return true if all fields are equal, false otherwise
     */
    inline bool
    isEqual(CanIfSevErrorStateEntry const& other) const
    {
        return SecurityEventInstanceIdEntry::isEqual(other) && (m_state == other.m_state);
    }

private:
    uint8_t m_state{};  // State (0-PassiveMode, 1-Busoff)
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::CanIfSevErrorStateEntry;

template <>
class hash<CanIfSevErrorStateEntry>
{
public:
    /**
     * @brief hash function of CanIfSevErrorStateEntry object
     *        Must be implemented so CanIfSevErrorStateEntry can be used as map key.
     * @param[in] entry the CanIfSevErrorStateEntry object to get hash for
     * @return the hash value of the given CanIfSevErrorStateEntry.
     */
    size_t
    operator()(CanIfSevErrorStateEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = std::hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<uint8_t>()(entry.GetState());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std