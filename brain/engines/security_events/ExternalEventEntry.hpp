/**
 * @file
 * @brief     This file contains the definition of the ExternalEventEntry class and its functionality.
 */
#ifndef EXTERNAL_EVENT_ENTRY_HPP
#define EXTERNAL_EVENT_ENTRY_HPP

#include "SecurityEventInstanceIdEntry.hpp"
#include "brain/utils/IpUtils.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using IpType = brain::utils::IpType;

/**
 * @class       ExternalEventEntry
 */
class ExternalEventEntry : public SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceID
     * @param   uint8_t  sensorInstanceID
     * @param   uint8_t  connectionType
     * @return	none
     */
    ExternalEventEntry(uint16_t idsMInstanceId, uint8_t sensorInstanceId, uint8_t connectionType)
      : SecurityEventInstanceIdEntry(idsMInstanceId, sensorInstanceId)
      , m_connectionType(connectionType)
    {
    }

    /**
     * @brief   Compare two ExternalEventEntry objects
     * @param   ExternalEventEntry const& other - the ExternalEventEntry object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(ExternalEventEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two ExternalEventEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   ExternalEventEntry const& other - the ExternalEventEntry object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(ExternalEventEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get connectionType
     * @return  uint8_t
     */
    inline uint8_t
    GetConnectionType() const
    {
        return m_connectionType;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   ExternalEventEntry const& other - the ExternalEventEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(ExternalEventEntry const& other) const
    {
        return ((SecurityEventInstanceIdEntry::isEqual(other)) && (m_connectionType == other.m_connectionType));
    }

private:
    uint8_t m_connectionType{};
};


}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::ExternalEventEntry;
using IpType = brain::utils::IpType;
template <>
class hash<ExternalEventEntry>
{
public:
    /**
     * @brief   hash function of ExternalEventEntry object
     *          Must be implemented so ExternalEventEntry can be used as map key.
     * @param   ExternalEventEntry entry - the ExternalEventEntry object to get hash for
     * @return  size_t - The hash value of the given ExternalEventEntry.
     */
    size_t
    operator()(ExternalEventEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = std::hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<uint8_t>()(entry.GetConnectionType());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // EXTERNAL_EVENT_ENTRY_HPP
