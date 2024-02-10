/**
 * @file
 * @brief     This file contains the definition of the DisallowedLayer3ProtocolEntry class and its functionality.
 *            DisallowedLayer3ProtocolEntry contains IDSm instance ID, Sensor instance ID, busId, sourceIpAddress,
 *            destinationIpAddress, protocolId, sourcePort, destinationPort.
 */
#ifndef DISALLOWED_LAYER3_PROTOCOL_ENTRY_HPP
#define DISALLOWED_LAYER3_PROTOCOL_ENTRY_HPP

#include "IpAnomaliesCountersEntry.hpp"
#include "common/utils/CPP/optional/Optional.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using brain::utils::IpType;

/**
 * @class               DisallowedLayer3ProtocolEntry
 * @brief               The DisallowedLayer3ProtocolEntry class
 * @internalInterfaces  The DisallowedLayer3ProtocolEntry provides a type representation and hash function, so it can be
 * used as unordered map key.
 */
class DisallowedLayer3ProtocolEntry final : public IpAnomaliesCountersEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId - ids instance id
     * @param   uint8_t  sensorInstanceId - sensor instance id
     * @param   uint16_t  busId - ID of the CAN bus
     * @param   IpType&  sourceIpAddress - source ip address
     * @param   IpType&  destinationIpAddress - destination ip address
     * @param   uint8_t protocolId - protocol id
     * @param   uint32_t sourcePort - source port
     * @param   uint32_t destinationPort - destination port
    */
    DisallowedLayer3ProtocolEntry(uint16_t      idsMInstanceId,
                                  uint8_t       sensorInstanceId,
                                  uint16_t      busId,
                                  IpType const& sourceIpAddress,
                                  IpType const& destinationIpAddress,
                                  uint8_t       protocolId,
                                  uint32_t      sourcePort,
                                  uint32_t      destinationPort)
      : IpAnomaliesCountersEntry{idsMInstanceId,
                                 sensorInstanceId,
                                 busId,
                                 sourceIpAddress,
                                 destinationIpAddress,
                                 sourcePort,
                                 destinationPort}
      , m_protocolId{protocolId}
    {
    }

    /**
     * @brief   Default constructor
     */
    DisallowedLayer3ProtocolEntry() = default;

    /**
     * @brief   Compare two DisallowedLayer3ProtocolEntry objects
     * @param   DisallowedLayer3ProtocolEntry const& other - the DisallowedLayer3ProtocolEntry object to compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    bool
    operator==(DisallowedLayer3ProtocolEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two DisallowedLayer3ProtocolEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   DisallowedLayer3ProtocolEntry const& other - the DisallowedLayer3ProtocolEntry object to compare to
     * @return  bool - true any field is different. false otherwise
     */
    bool
    operator!=(DisallowedLayer3ProtocolEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   set Protocol Id
     * @param   uint8_t
     * @return  void
     */
    inline void
    SetProtocolId(uint8_t protocolId)
    {
        m_protocolId = protocolId;
    }

    /**
     * @brief   get protocol Id
     * @return  cm::optional<uint8_t> const&
     */
    inline cm::optional<uint8_t> const&
    GetProtocolId() const
    {
        return m_protocolId;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   DisallowedLayer3ProtocolEntry const& other - the DisallowedLayer3ProtocolEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(DisallowedLayer3ProtocolEntry const& other) const
    {
        return IpAnomaliesCountersEntry::isEqual(other) && (other.m_protocolId == m_protocolId);
    }

private:
    cm::optional<uint8_t> m_protocolId;
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
template <>
class hash<brain::engines::security_events::DisallowedLayer3ProtocolEntry>
{
public:
    /**
     * @brief   hash function of DisallowedLayer3ProtocolEntry object
     *          Must be implemented so DisallowedLayer3ProtocolEntry can be used as map key.
     * @param   DisallowedLayer3ProtocolEntry entry - the DisallowedLayer3ProtocolEntry object to get hash for
     * @return  size_t - The hash value of the given DisallowedLayer3ProtocolEntry.
     */
    size_t
    operator()(brain::engines::security_events::DisallowedLayer3ProtocolEntry const& entry) const
    {
        std::array<size_t, 2> hashes;
        hashes[0U] = hash<brain::engines::security_events::IpAnomaliesCountersEntry>()(entry);
        auto const& optProtocolId{entry.GetProtocolId()};
        hashes[1U] = optProtocolId ? hash<uint8_t>()(*optProtocolId) : std::numeric_limits<size_t>::min();

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

using brain::utils::IpType;

#endif  // DISALLOWED_LAYER3_PROTOCOL_ENTRY_HPP
