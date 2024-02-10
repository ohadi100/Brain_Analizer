/**
 * @file
 * @brief     This file contains the definition of the UnusedPortConnectionRequestEntry class and its functionality.
 *            UnusedPortConnectionRequestEntry contains IDSm instance ID, Sensor instance ID, busId, sourceIpAddress,
 *            destinationIpAddress, sourcePort, transportProtocol, destinationPortRequest.
 */
#ifndef UNUSED_PORT_CONNECTION_REQUEST_ENTRY_HPP
#define UNUSED_PORT_CONNECTION_REQUEST_ENTRY_HPP

#include "IpAnomaliesCountersEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using brain::utils::IpType;

/**
 * @class               UnusedPortConnectionRequestEntry
 * @brief               The UnusedPortConnectionRequestEntry class
 * @internalInterfaces  The UnusedPortConnectionRequestEntry provides a type representation and hash function, so it can
 * be used as unordered map key.
 */
class UnusedPortConnectionRequestEntry final : public IpAnomaliesCountersEntry
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
     * @param   std::string transportProtocol - transport protocol
     * @param   uint32_t destinationPort - destination port
    */
    UnusedPortConnectionRequestEntry(uint16_t           idsMInstanceId,
                                     uint8_t            sensorInstanceId,
                                     uint16_t           busId,
                                     IpType const&      sourceIpAddress,
                                     IpType const&      destinationIpAddress,
                                     uint32_t           sourcePort,
                                     std::string const& transportProtocol,
                                     uint32_t           destinationPort)
      : IpAnomaliesCountersEntry{idsMInstanceId,
                                 sensorInstanceId,
                                 busId,
                                 sourceIpAddress,
                                 destinationIpAddress,
                                 sourcePort,
                                 destinationPort}
      , m_transportProtocol{transportProtocol}
    {
    }

    /**
     * @brief   Default constructor
     */
    UnusedPortConnectionRequestEntry() = default;

    /**
     * @brief   Compare two UnusedPortConnectionRequestEntry objects
     * @param   UnusedPortConnectionRequestEntry const& other - the UnusedPortConnectionRequestEntry object to compare
     * to
     * @return  bool - true all fields are equal. false otherwise
     */
    bool
    operator==(UnusedPortConnectionRequestEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two UnusedPortConnectionRequestEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   UnusedPortConnectionRequestEntry const& other - the UnusedPortConnectionRequestEntry object to compare
     * to
     * @return  bool - true any field is different. false otherwise
     */
    bool
    operator!=(UnusedPortConnectionRequestEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   set transport protocol
     * @param   std::string
     */
    inline void
    SetTransportProtocol(std::string const& transportProtocol)
    {
        m_transportProtocol = transportProtocol;
    }

    /**
     * @brief   get transport protocol
     * @return  std::string
     */
    inline std::string const&
    GetTransportProtocol() const
    {
        return m_transportProtocol;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   UnusedPortConnectionRequestEntry const& other - the UnusedPortConnectionRequestEntry object to check if
     * equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(UnusedPortConnectionRequestEntry const& other) const
    {
        return IpAnomaliesCountersEntry::isEqual(other) && (other.m_transportProtocol == m_transportProtocol);
    }

private:
    std::string m_transportProtocol;
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
template <>
class hash<brain::engines::security_events::UnusedPortConnectionRequestEntry>
{
public:
    /**
     * @brief   hash function of UnusedPortConnectionRequestEntry object
     *          Must be implemented so UnusedPortConnectionRequestEntry can be used as map key.
     * @param   UnusedPortConnectionRequestEntry entry - the UnusedPortConnectionRequestEntry object to get hash for
     * @return  size_t - The hash value of the given UnusedPortConnectionRequestEntry.
     */
    size_t
    operator()(brain::engines::security_events::UnusedPortConnectionRequestEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = hash<brain::engines::security_events::IpAnomaliesCountersEntry>()(entry);
        hashes[1U] = hash<std::string>()(entry.GetTransportProtocol());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // UNUSED_PORT_CONNECTION_REQUEST_ENTRY_HPP