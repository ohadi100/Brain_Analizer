/**
 * @file
 * @brief     This file contains the definition of the EthernetServiceInterruptionEntry class and its functionality.
 *            EthernetServiceInterruptionEntry contains the ID of the CAN bus and the communication server ID.
 */
#ifndef ETHERNET_SERVICE_INTERRUPTION_ENTRY_HPP
#define ETHERNET_SERVICE_INTERRUPTION_ENTRY_HPP

#include "EthernetBaseEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

/**
 * @class               EthernetServiceInterruptionEntry
 * @brief               The EthernetServiceInterruptionEntry class
 * @internalInterfaces  The EthernetServiceInterruptionEntry provides a type representation and hash function, so it can
 * be used as unordered map key.
 */
class EthernetServiceInterruptionEntry final : public EthernetBaseEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId - IDSm instance ID
     * @param   uint8_t  sensorInstanceId - sensor instance id
     * @param   uint32_t busId - ID of the CAN bus
     * @param   uint32_t comServerIdentifier - Communication server identifier
     */
    EthernetServiceInterruptionEntry(uint16_t idsMInstanceId,
                                     uint8_t  sensorInstanceId,
                                     uint32_t busId,
                                     uint32_t comServerIdentifier)
      : EthernetBaseEntry(idsMInstanceId, sensorInstanceId, busId)
      , m_comServerIdentifier{comServerIdentifier}
    {
    }

    /**
     * @brief   Compare two EthernetServiceInterruptionEntry objects
     * @param   EthernetServiceInterruptionEntry const& other - the EthernetServiceInterruptionEntry object to compare
     * to
     * @return  bool - true all fields are equal. false otherwise
     */
    inline bool
    operator==(EthernetServiceInterruptionEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two EthernetServiceInterruptionEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   EthernetServiceInterruptionEntry const& other - the EthernetServiceInterruptionEntry object to compare
     * to
     * @return  bool - true any field is different. false otherwise
     */
    inline bool
    operator!=(EthernetServiceInterruptionEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get communication server identifier
     * @return  uint32_t
     */
    inline uint32_t
    GetComServerIdentifier() const
    {
        return m_comServerIdentifier;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   EthernetServiceInterruptionEntry const& other - the EthernetServiceInterruptionEntry object to check if
     * equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    inline bool
    isEqual(EthernetServiceInterruptionEntry const& other) const
    {
        return (EthernetBaseEntry::isEqual(other)) && (other.m_comServerIdentifier == m_comServerIdentifier);
    }

private:
    uint32_t m_comServerIdentifier{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::EthernetServiceInterruptionEntry;

template <>
class hash<EthernetServiceInterruptionEntry>
{
public:
    /**
     * @brief   hash function of EthernetServiceInterruptionEntry object
     *          Must be implemented so EthernetServiceInterruptionEntry can be used as map key.
     * @param   EthernetServiceInterruptionEntry entry - the EthernetServiceInterruptionEntry object to get hash for
     * @return  size_t - The hash value of the given EthernetServiceInterruptionEntry.
     */
    size_t
    operator()(EthernetServiceInterruptionEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = std::hash<EthernetBaseEntry>()(entry);
        hashes[1U] = hash<uint32_t>()(entry.GetComServerIdentifier());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // ETHERNET_SERVICE_INTERRUPTION_ENTRY_HPP
