/**
 * @file
 * @brief     This file contains the definition of the DisallowedLayer4ProtocolEntry class and its functionality.
 *            DisallowedLayer4ProtocolEntry contains IDSm instance ID, Sensor instance ID, busId, sourceIpAddress,
 *            destinationIpAddress, transportProtocol, sourcePort, destinationPort, fwRuleId.
 */
#ifndef DISALLOWED_LAYER4_PROTOCOL_ENTRY_HPP
#define DISALLOWED_LAYER4_PROTOCOL_ENTRY_HPP

#include "DisallowedLayer3ProtocolEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using brain::utils::IpType;

/**
 * @class               DisallowedLayer4ProtocolEntry
 * @brief               The DisallowedLayer4ProtocolEntry class
 * @internalInterfaces  The DisallowedLayer4ProtocolEntry provides a type representation and hash function, so it can be
 * used as unordered map key.
 */
class DisallowedLayer4ProtocolEntry final : public IpAnomaliesCountersEntry
{
public:

    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId - ids instance id
     * @param   uint8_t  sensorInstanceId - sensor instance id
     * @param   uint16_t  busId - ID of the CAN bus
     * @param   IpType&  sourceIpAddress - source ip address
     * @param   IpType&  destinationIpAddress - destination ip address
     * @param   uint32_t sourcePort - source port
     * @param   uint32_t destinationPort - destination port
     * @param   uint16_t firewallId - Firewall ID
    */
    DisallowedLayer4ProtocolEntry(uint16_t      idsMInstanceId,
                                  uint8_t       sensorInstanceId,
                                  uint16_t      busId,
                                  IpType const& sourceIpAddress,
                                  IpType const& destinationIpAddress,
                                  uint32_t      sourcePort,
                                  uint32_t      destinationPort,
                                  uint16_t      firewallId)
      : IpAnomaliesCountersEntry{idsMInstanceId,
                                 sensorInstanceId,
                                 busId,
                                 sourceIpAddress,
                                 destinationIpAddress,
                                 sourcePort,
                                 destinationPort}
      , m_fwRuleId{firewallId}
    {
    }

    /**
     * @brief   Default constructor
     */
    DisallowedLayer4ProtocolEntry() = default;

    /**
     * @brief   Compare two DisallowedLayer4ProtocolEntry objects
     * @param   DisallowedLayer4ProtocolEntry const& other - the DisallowedLayer4ProtocolEntry object to compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    bool
    operator==(DisallowedLayer4ProtocolEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two DisallowedLayer4ProtocolEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   DisallowedLayer4ProtocolEntry const& other - the DisallowedLayer4ProtocolEntry object to compare to
     * @return  bool - true any field is different. false otherwise
     */
    bool
    operator!=(DisallowedLayer4ProtocolEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   set Firewall ID
     * @param   uint16_t
     * @return  void
     */
    inline void
    SetFwRuleId(uint16_t fwRuleId)
    {
        m_fwRuleId = fwRuleId;
    }

    /**
     * @brief   get Firewall ID
     * @return  uint16_t
     */
    inline uint16_t
    GetFwRuleId() const
    {
        return m_fwRuleId;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   DisallowedLayer4ProtocolEntry const& other - the DisallowedLayer4ProtocolEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(DisallowedLayer4ProtocolEntry const& other) const
    {
        return IpAnomaliesCountersEntry::isEqual(other) && (other.m_fwRuleId == m_fwRuleId);
    }

private:
    uint16_t m_fwRuleId{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
template <>
class hash<brain::engines::security_events::DisallowedLayer4ProtocolEntry>
{
public:
    /**
     * @brief   hash function of DisallowedLayer4ProtocolEntry object
     *          Must be implemented so DisallowedLayer4ProtocolEntry can be used as map key.
     * @param   DisallowedLayer4ProtocolEntry entry - the DisallowedLayer4ProtocolEntry object to get hash for
     * @return  size_t - The hash value of the given DisallowedLayer4ProtocolEntry.
     */
    size_t
    operator()(brain::engines::security_events::DisallowedLayer4ProtocolEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = hash<brain::engines::security_events::IpAnomaliesCountersEntry>()(entry);
        hashes[1U] = hash<uint16_t>()(entry.GetFwRuleId());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // DISALLOWED_LAYER4_PROTOCOL_ENTRY_HPP