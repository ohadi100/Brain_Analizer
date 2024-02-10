/**
 * @file
 * @brief     This file contains the definition of the SecurityEventInstanceIdEntry class and its functionality.
 *            SecurityEventInstanceIdEntry contains IDSm instance ID and Sensor instance ID used as table key.
 */
#ifndef SECURITY_EVENT_INSTANCE_ID_ENTRY_HPP
#define SECURITY_EVENT_INSTANCE_ID_ENTRY_HPP

#include <stdint.h>
#include <memory>
#include "common/utils/HashUtils.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

/**
 * @class               SecurityEventInstanceIdEntry
 * @brief               The SecurityEventInstanceIdEntry class
 * @internalInterfaces  The SecurityEventInstanceIdEntry provides a type representation and hash function, so it can be
 * used as unordered map key.
 */
class SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief   Default Constructor (needed for UT)
     */
    SecurityEventInstanceIdEntry() = default;

    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId
     * @param   uint8_t sensorInstanceId
     */
    SecurityEventInstanceIdEntry(uint16_t idsMInstanceId, uint8_t sensorInstanceId)
      : m_idsMInstanceId(idsMInstanceId)
      , m_sensorInstanceId(sensorInstanceId)
    {
    }

    /**
     * @brief   Default destructor
     */
    virtual ~SecurityEventInstanceIdEntry() = default;

    /**
     * @brief   Copy constructor from another SecurityEventInstanceIdEntry object
     *          Copies the internal data to the new object
     * @param   SecurityEventInstanceIdEntry const& other - the SecurityEventInstanceIdEntry object to copy from
     */
    SecurityEventInstanceIdEntry(SecurityEventInstanceIdEntry const& other) = default;

    /**
     * @brief    default move constructor
     */
    SecurityEventInstanceIdEntry(SecurityEventInstanceIdEntry&& other) = default;

    /**
     * @brief   Assignment operator from another SecurityEventInstanceIdEntry object
     *          Copies the internal data to the current object
     * @param   SecurityEventInstanceIdEntry const& other - the SecurityEventInstanceIdEntry object to copy from
     * @return  SecurityEventInstanceIdEntry& - Reference to the updated SecurityEventInstanceIdEntry object
     */
    SecurityEventInstanceIdEntry& operator=(SecurityEventInstanceIdEntry const& other) = default;

    /**
    * @brief   default move assignment operator
    */
    SecurityEventInstanceIdEntry& operator=(SecurityEventInstanceIdEntry&&) = default;

    /**
     * @brief   Compare two SecurityEventInstanceIdEntry objects
     * @param   SecurityEventInstanceIdEntry const& other - the SecurityEventInstanceIdEntry object to compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    bool
    operator==(SecurityEventInstanceIdEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two SecurityEventInstanceIdEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   SecurityEventInstanceIdEntry const& other - the SecurityEventInstanceIdEntry object to compare to
     * @return  bool - true any field is different. false otherwise
     */
    bool
    operator!=(SecurityEventInstanceIdEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get IDSm instance ID
     * @return  uint16_t
     */
    inline uint16_t
    GetIdsMInstanceId() const
    {
        return m_idsMInstanceId;
    }

    /**
     * @brief   get sensor instance ID
     * @return  uint8_t
     */
    inline uint8_t
    GetSensorInstanceId() const
    {
        return m_sensorInstanceId;
    }

    /**
     * @brief   set Ids Instance Id
     * @param   uint32_t
     */
    inline void
    SetIdsMInstanceId(uint16_t idsMInstanceId)
    {
        m_idsMInstanceId = idsMInstanceId;
    }

    /**
     * @brief   set sensor instance id
     * @param   uint8_t
     */
    inline void
    SetSensorInstanceId(uint8_t sensorInstanceId)
    {
        m_sensorInstanceId = sensorInstanceId;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   SecurityEventInstanceIdEntry const& other - the SecurityEventInstanceIdEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(SecurityEventInstanceIdEntry const& other) const
    {
        return (other.m_idsMInstanceId == m_idsMInstanceId) && (other.m_sensorInstanceId == m_sensorInstanceId);
    }

    uint16_t m_idsMInstanceId{};
    uint8_t  m_sensorInstanceId{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::SecurityEventInstanceIdEntry;

template <>
class hash<SecurityEventInstanceIdEntry>
{
public:
    /**
     * @brief   hash function of ExternalUnsuccessfulConnectionsEntry object
     *          Must be implemented so ExternalUnsuccessfulConnectionsEntry can be used as map key.
     * @param   ExternalUnsuccessfulConnectionsEntry entry - the ExternalUnsuccessfulConnectionsEntry object to get hash
     * for
     * @return  size_t - The hash value of the given ExternalUnsuccessfulConnectionsEntry.
     */
    size_t
    operator()(SecurityEventInstanceIdEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = hash<uint16_t>()(entry.GetIdsMInstanceId());
        hashes[1U] = hash<uint8_t>()(entry.GetSensorInstanceId());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // SECURITY_EVENT_INSTANCE_ID_ENTRY_HPP
