/**
 * @file
 * @brief     This file contains the definition of the IpAnomaliesCountersEntry class and its functionality.
 *            IpAnomaliesCountersEntry contains IDSm instance ID, Sensor instance ID, busId, sourceIpAddress,
 *            destinationIpAddress, sourcePort, destinationPort.
 */
#ifndef IP_ANOMALIES_COUNTERS_ENTRY_HPP
#define IP_ANOMALIES_COUNTERS_ENTRY_HPP

#include "EthernetBaseEntry.hpp"
#include "brain/utils/IpUtils.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using brain::utils::IpType;

/**
 * @class               IpAnomaliesCountersEntry
 * @brief               The IpAnomaliesCountersEntry class
 * @internalInterfaces  The IpAnomaliesCountersEntry provides a type representation and hash function, so it can be used
 * as unordered map key.
 */
class IpAnomaliesCountersEntry : public EthernetBaseEntry
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
    */
    IpAnomaliesCountersEntry(uint16_t      idsMInstanceId,
                             uint8_t       sensorInstanceId,
                             uint16_t      busId,
                             IpType const& sourceIpAddress,
                             IpType const& destinationIpAddress,
                             uint32_t      sourcePort,
                             uint32_t      destinationPort)
      : EthernetBaseEntry(idsMInstanceId, sensorInstanceId, busId)
      , m_sourceIpAddress{sourceIpAddress}
      , m_destinationIpAddress{destinationIpAddress}
      , m_sourcePort{sourcePort}
      , m_destinationPort{destinationPort}
    {
    }

    /**
     * @brief   Default constructor
     */
    IpAnomaliesCountersEntry() = default;

    /**
     * @brief   Default destructor
     */
    virtual ~IpAnomaliesCountersEntry() = default;

    /**
     * @brief   Copy constructor from another IpAnomaliesCountersEntry object
     *          Copies the internal data to the new object
     * @param   IpAnomaliesCountersEntry const& other - the IpAnomaliesCountersEntry object to copy from
     */
    IpAnomaliesCountersEntry(IpAnomaliesCountersEntry const& other) = default;

    /**
     * @brief    default move constructor
     */
    IpAnomaliesCountersEntry(IpAnomaliesCountersEntry&& other) = default;

    /**
     * @brief   Assignment operator from another IpAnomaliesCountersEntry object
     *          Copies the internal data to the current object
     * @param   IpAnomaliesCountersEntry const& other - the IpAnomaliesCountersEntry object to copy from
     * @return  IpAnomaliesCountersEntry& - Reference to the updated IpAnomaliesCountersEntry object
     */
    IpAnomaliesCountersEntry& operator=(IpAnomaliesCountersEntry const& other) = default;

    /**
     * @brief   default move assignment operator
     */
    IpAnomaliesCountersEntry& operator=(IpAnomaliesCountersEntry&&) = default;

    /**
     * @brief   Compare two IpAnomaliesCountersEntry objects
     * @param   IpAnomaliesCountersEntry const& other - the IpAnomaliesCountersEntry object to compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    bool
    operator==(IpAnomaliesCountersEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two IpAnomaliesCountersEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   IpAnomaliesCountersEntry const& other - the IpAnomaliesCountersEntry object to compare to
     * @return  bool - true any field is different. false otherwise
     */
    bool
    operator!=(IpAnomaliesCountersEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   set source Ip address
     * @param   IpType
     */
    inline void
    SetSourceIpAddress(IpType const& sourceIpAddress)
    {
        m_sourceIpAddress = sourceIpAddress;
    }

    /**
     * @brief   get source Ip address
     * @return  IpType
     */
    inline IpType const&
    GetSourceIpAddress() const
    {
        return m_sourceIpAddress;
    }

    /**
     * @brief   set destination ip address
     * @param   IpType
     */
    inline void
    SetDestinationIpAddress(IpType const& destinationIpAddress)
    {
        m_destinationIpAddress = destinationIpAddress;
    }

    /**
     * @brief   get destination ip address
     * @return  IpType
     */
    inline IpType const&
    GetDestinationIpAddress() const
    {
        return m_destinationIpAddress;
    }

    /**
     * @brief   set source port
     * @param   uint32_t
     */
    inline void
    SetSourcePort(uint32_t sourcePort)
    {
        m_sourcePort = sourcePort;
    }

    /**
     * @brief   get source port
     * @return  uint32_t
     */
    inline uint32_t
    GetSourcePort() const
    {
        return m_sourcePort;
    }

    /**
     * @brief   set destination port
     * @param   uint32_t
     */
    inline void
    SetDestinationPort(uint32_t destinationPort)
    {
        m_destinationPort = destinationPort;
    }

    /**
     * @brief   get destination port
     * @return  uint32_t
     */
    inline uint32_t
    GetDestinationPort() const
    {
        return m_destinationPort;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   IpAnomaliesCountersEntry const& other - the IpAnomaliesCountersEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(IpAnomaliesCountersEntry const& other) const
    {
        return (EthernetBaseEntry::isEqual(other) && (other.m_sourceIpAddress == m_sourceIpAddress)
                && (other.m_destinationIpAddress == m_destinationIpAddress) && (other.m_sourcePort == m_sourcePort)
                && (other.m_destinationPort == m_destinationPort));
    }

private:
    IpType   m_sourceIpAddress{};
    IpType   m_destinationIpAddress{};
    uint32_t m_sourcePort{};
    uint32_t m_destinationPort{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
template <>
class hash<brain::engines::security_events::IpAnomaliesCountersEntry>
{
public:
    /**
     * @brief   hash function of IpAnomaliesCountersEntry object
     *          Must be implemented so IpAnomaliesCountersEntry can be used as map key.
     * @param   IpAnomaliesCountersEntry entry - the IpAnomaliesCountersEntry object to get hash for
     * @return  size_t - The hash value of the given IpAnomaliesCountersEntry.
     */
    size_t
    operator()(brain::engines::security_events::IpAnomaliesCountersEntry const& entry) const
    {
        std::array<size_t, 5U> hashes;
        hashes[0U] = std::hash<EthernetBaseEntry>()(entry);
        hashes[1U] = hash<IpType>()(entry.GetSourceIpAddress());
        hashes[2U] = hash<uint32_t>()(entry.GetSourcePort());
        hashes[3U] = hash<IpType>()(entry.GetDestinationIpAddress());
        hashes[4U] = hash<uint32_t>()(entry.GetDestinationPort());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // IP_ANOMALIES_COUNTERS_ENTRY_HPP