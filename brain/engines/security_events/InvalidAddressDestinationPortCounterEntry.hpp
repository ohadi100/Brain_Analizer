/**
 * @file
 * @brief     This file contains the definition of the InvalidAddressDestinationPortCounterEntry class and its
 * functionality. InvalidAddressDestinationPortCounterEntry contains IDSm instance ID, Sensor instance ID, busEthId,
 * sourceIpAddress, sourcePort, destinationIpAddress, destinationPortRequest.
 */
#ifndef INVALID_ADDRESS_DESTINATION_PORT_COUNTER_ENTRY_HPP
#define INVALID_ADDRESS_DESTINATION_PORT_COUNTER_ENTRY_HPP

#include "IpAnomaliesCountersEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using brain::utils::IpType;

/**
 * @class               InvalidAddressDestinationPortCounterEntry
 * @brief               The InvalidAddressDestinationPortCounterEntry class
 * @internalInterfaces  The InvalidAddressDestinationPortCounterEntry provides a type representation and hash function,
 * so it can be used as unordered map key.
 */
class InvalidAddressDestinationPortCounterEntry final : public IpAnomaliesCountersEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId - ids instance id
     * @param   uint8_t  sensorInstanceId - sensor instance id
     * @param   uint16_t  busId - ID of the CAN bus
     * @param   IpType&  sourceIpAddress - source ip address
     * @param   uint32_t sourcePort - source port
     * @param   IpType&  destinationIpAddress - destination ip address
     * @param   uint32_t destinationPort - destination port
     * @param   uint32_t fwRuleId - firmware
     */
    InvalidAddressDestinationPortCounterEntry(uint16_t      idsMInstanceId,
                                              uint8_t       sensorInstanceId,
                                              uint16_t      busId,
                                              IpType const& sourceIpAddress,
                                              uint32_t      sourcePort,
                                              IpType const& destinationIpAddress,
                                              uint32_t      destinationPort,
                                              uint32_t      fwRuleId)
      : IpAnomaliesCountersEntry{idsMInstanceId,
                                 sensorInstanceId,
                                 busId,
                                 sourceIpAddress,
                                 destinationIpAddress,
                                 sourcePort,
                                 destinationPort}
      , m_fwRuleId{fwRuleId}
    {
    }

    /**
     * @brief   Default constructor
     */
    InvalidAddressDestinationPortCounterEntry() = default;

    /**
     * @brief   Compare two InvalidAddressDestinationPortCounterEntry objects
     * @param   InvalidAddressDestinationPortCounterEntry const& other - the InvalidAddressDestinationPortCounterEntry
     * object to compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    bool
    operator==(InvalidAddressDestinationPortCounterEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two InvalidAddressDestinationPortCounterEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   InvalidAddressDestinationPortCounterEntry const& other - the InvalidAddressDestinationPortCounterEntry
     * object to compare to
     * @return  bool - true any field is different. false otherwise
     */
    bool
    operator!=(InvalidAddressDestinationPortCounterEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   set firmware rule id
     * @param   uint32_t
     * @return  void
     */
    inline void
    SetFwRuleId(uint32_t fwRuleId)
    {
        m_fwRuleId = fwRuleId;
    }

    /**
     * @brief   get firmware rule id
     * @return  uint32_t
     */
    inline uint32_t
    GetFwRuleId() const
    {
        return m_fwRuleId;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   InvalidAddressDestinationPortCounterEntry const& other - the InvalidAddressDestinationPortCounterEntry
     * object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(InvalidAddressDestinationPortCounterEntry const& other) const
    {
        return ((IpAnomaliesCountersEntry::isEqual(other)) && (other.m_fwRuleId == m_fwRuleId));
    }

private:
    uint32_t m_fwRuleId{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
template <>
class hash<brain::engines::security_events::InvalidAddressDestinationPortCounterEntry>
{
public:
    /**
     * @brief   hash function of InvalidAddressDestinationPortCounterEntry object
     *          Must be implemented so InvalidAddressDestinationPortCounterEntry can be used as map key.
     * @param   InvalidAddressDestinationPortCounterEntry entry - the InvalidAddressDestinationPortCounterEntry object
     * to get hash for
     * @return  size_t - The hash value of the given InvalidAddressDestinationPortCounterEntry.
     */
    size_t
    operator()(brain::engines::security_events::InvalidAddressDestinationPortCounterEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = hash<brain::engines::security_events::IpAnomaliesCountersEntry>()(entry);
        hashes[1U] = hash<uint32_t>()(entry.GetFwRuleId());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // INVALID_ADDRESS_DESTINATION_PORT_COUNTER_ENTRY_HPP
