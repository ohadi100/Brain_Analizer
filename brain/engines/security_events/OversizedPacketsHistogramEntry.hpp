/**
 * @file
 * @brief     This file contains the definition of the OversizedPacketsHistogramEntry class and its functionality.
 *            OversizedPacketsHistogramEntry contains IDSm instance ID, Sensor instance ID, busId, sourceIpAddress,
 *            destinationIpAddress, sourcePort, transportProtocol, destinationPortRequest.
 */
#ifndef OVERSIZED_PACKETS_HISTOGRAM_ENTRY_HPP
#define OVERSIZED_PACKETS_HISTOGRAM_ENTRY_HPP

#include <string>
#include "IpAnomaliesCountersEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using brain::utils::IpType;

/**
 * @class               OversizedPacketsHistogramEntry
 * @brief               The OversizedPacketsHistogramEntry class
 * @internalInterfaces  The OversizedPacketsHistogramEntry provides a type representation and hash function, so it can
 * be used as unordered map key.
 */
class OversizedPacketsHistogramEntry final : public IpAnomaliesCountersEntry
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
     * @param   std::string transportProtocol - transport protocol
    */
    OversizedPacketsHistogramEntry(uint16_t           idsMInstanceId,
                                   uint8_t            sensorInstanceId,
                                   uint16_t           busId,
                                   IpType const&      sourceIpAddress,
                                   IpType const&      destinationIpAddress,
                                   uint32_t           sourcePort,
                                   uint32_t           destinationPort,
                                   std::string const& transportProtocol)
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
    OversizedPacketsHistogramEntry() = default;

    /**
     * @brief   Compare two OversizedPacketsHistogramEntry objects
     * @param   OversizedPacketsHistogramEntry const& other - the OversizedPacketsHistogramEntry object to compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    bool
    operator==(OversizedPacketsHistogramEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two OversizedPacketsHistogramEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   OversizedPacketsHistogramEntry const& other - the OversizedPacketsHistogramEntry object to compare to
     * @return  bool - true any field is different. false otherwise
     */
    bool
    operator!=(OversizedPacketsHistogramEntry const& other) const
    {
        return !isEqual(other);
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
     * @param   OversizedPacketsHistogramEntry const& other - the OversizedPacketsHistogramEntry object to check if
     * equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(OversizedPacketsHistogramEntry const& other) const
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
class hash<brain::engines::security_events::OversizedPacketsHistogramEntry>
{
public:
    /**
     * @brief   hash function of OversizedPacketsHistogramEntry object
     *          Must be implemented so OversizedPacketsHistogramEntry can be used as map key.
     * @param   OversizedPacketsHistogramEntry entry - the OversizedPacketsHistogramEntry object to get hash for
     * @return  size_t - The hash value of the given OversizedPacketsHistogramEntry.
     */
    size_t
    operator()(brain::engines::security_events::OversizedPacketsHistogramEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = hash<brain::engines::security_events::IpAnomaliesCountersEntry>()(entry);
        hashes[1U] = hash<std::string>()(entry.GetTransportProtocol());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // OVERSIZED_PACKETS_HISTOGRAM_ENTRY_HPP