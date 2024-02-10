/**
 * @file
 * @brief     This file contains the definition of the EthernetBaseEntry class and its functionality.
 *            EthernetBaseEntry contains the ID of the CAN bus and the communication server ID.
 */
#ifndef ETHERNET_BASE_ENTRY_HPP
#define ETHERNET_BASE_ENTRY_HPP

#include "SecurityEventInstanceIdEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

/**
 * @class               EthernetBaseEntry
 * @brief               The EthernetBaseEntry class
 * @internalInterfaces  The EthernetBaseEntry provides a type representation and hash function, so it can be used as
 * unordered map key.
 */
class EthernetBaseEntry : public SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId - IDSm instance ID
     * @param   uint8_t sensorInstanceId - sensor instance ID
     * @param   uint32_t busId - ID of the CAN bus
     */
    EthernetBaseEntry(uint16_t idsMInstanceId, uint8_t sensorInstanceId, uint32_t busId)
      : SecurityEventInstanceIdEntry(idsMInstanceId, sensorInstanceId)
      , m_busId{busId}
    {
    }

    /**
     * @brief   Default constructor
     */
    EthernetBaseEntry() = default;

    /**
     * @brief   Default destructor
     */
    virtual ~EthernetBaseEntry() = default;

    /**
     * @brief   Copy constructor from another EthernetBaseEntry object
     *          Copies the internal data to the new object
     * @param   EthernetBaseEntry const& other - the EthernetBaseEntry object to copy from
     */
    EthernetBaseEntry(EthernetBaseEntry const& other) = default;

    /**
     * @brief    default move constructor
     */
    EthernetBaseEntry(EthernetBaseEntry&& other) = delete;

    /**
     * @brief   Assignment operator from another EthernetBaseEntry object
     *          Copies the internal data to the current object
     * @param   EthernetBaseEntry const& other - the EthernetBaseEntry object to copy from
     * @return  EthernetBaseEntry& - Reference to the updated EthernetBaseEntry object
     */
    EthernetBaseEntry& operator=(EthernetBaseEntry const& other) = delete;

    /**
     * @brief   default move assignment operator
     */
    EthernetBaseEntry& operator=(EthernetBaseEntry&&) = default;

    /**
     * @brief   Compare two EthernetBaseEntry objects
     * @param   EthernetBaseEntry const& other - the EthernetBaseEntry object to compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    inline bool
    operator==(EthernetBaseEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two EthernetBaseEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   EthernetBaseEntry const& other - the EthernetBaseEntry object to compare to
     * @return  bool - true any field is different. false otherwise
     */
    inline bool
    operator!=(EthernetBaseEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get CAN bus ID
     * @return  uint32_t
     */
    inline uint32_t
    GetBusId() const
    {
        return m_busId;
    }

    /**
     * @brief   set ID of the CAN bus
     * @param   uint16_t
     */
    inline void
    SetBusId(uint16_t busId)
    {
        m_busId = busId;
    }


protected:
    /**
     * @brief   copy the internal data
     * @param   EthernetBaseEntry const& other - the EthernetBaseEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    inline bool
    isEqual(EthernetBaseEntry const& other) const
    {
        return (SecurityEventInstanceIdEntry::isEqual(other)) && (other.m_busId == m_busId);
    }

private:
    uint32_t m_busId{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::EthernetBaseEntry;

template <>
class hash<EthernetBaseEntry>
{
public:
    /**
     * @brief   hash function of EthernetBaseEntry object
     *          Must be implemented so EthernetBaseEntry can be used as map key.
     * @param   EthernetBaseEntry entry - the EthernetBaseEntry object to get hash for
     * @return  size_t - The hash value of the given EthernetBaseEntry.
     */
    size_t
    operator()(EthernetBaseEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = std::hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<uint32_t>()(entry.GetBusId());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // ETHERNET_BASE_ENTRY_HPP
