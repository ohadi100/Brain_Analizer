/**
 * @file
 * @brief     This file contains the definition of the ErrorEventLoggingUserLoginCountersEntry.
 */
#ifndef ERROR_EVENT_LOGGING_USER_LOGIN_COUNTERS_ENTRY_HPP
#define ERROR_EVENT_LOGGING_USER_LOGIN_COUNTERS_ENTRY_HPP

#include "SecurityEventInstanceIdEntry.hpp"
#include "brain/utils/IpUtils.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using brain::utils::IpType;

class ErrorEventLoggingUserLoginCountersEntry final : public SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief   Default Constructor (needed for UT)
     */
    ErrorEventLoggingUserLoginCountersEntry() = default;

    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId - IDSm instance ID
     * @param   uint8_t sensorInstanceId - sensor instance ID
     * @param   std::string const& userName - user Name
     * @param   uint32_t failReason - error code (if relevant)
     * @param   IpType const& sourceIpAddress - source IP address
     * @param   uint16_t destinationPort - destination port
     * @param   std::string const& protocol - protocol
     * @param   uint32_t partitionId - partition ID
     * @param   std::string const& processName - process name
     */
    ErrorEventLoggingUserLoginCountersEntry(uint16_t           idsMInstanceId,
                                            uint8_t            sensorInstanceId,
                                            std::string const& userName,
                                            uint32_t           failReason,
                                            IpType const&      sourceIpAddress,
                                            uint16_t           destinationPort,
                                            std::string const& protocol,
                                            uint32_t           partitionId,
                                            std::string const& processName)
      : SecurityEventInstanceIdEntry(idsMInstanceId, sensorInstanceId)
      , m_userName(userName)
      , m_failReason(failReason)
      , m_sourceIpAddress(sourceIpAddress)
      , m_destinationPort(destinationPort)
      , m_protocol(protocol)
      , m_partitionId(partitionId)
      , m_processName(processName)
    {
    }

    /**
     * @brief   Compare two ErrorEventLoggingUserLoginCountersEntry objects
     * @param   ErrorEventLoggingUserLoginCountersEntry const& other - the ErrorEventLoggingUserLoginCountersEntry
     * object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(ErrorEventLoggingUserLoginCountersEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two ErrorEventLoggingUserLoginCountersEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   ErrorEventLoggingUserLoginCountersEntry const& other - the ErrorEventLoggingUserLoginCountersEntry
     * object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(ErrorEventLoggingUserLoginCountersEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get user name
     * @return  std::string
     */
    inline std::string const&
    GetUserName() const
    {
        return m_userName;
    }

    /**
     * @brief   get error code (if relevant)
     * @return  uint32_t
     */
    inline uint32_t
    GetFailReason() const
    {
        return m_failReason;
    }

    /**
     * @brief   get source IP address
     * @return  IpType
     */
    inline IpType const&
    GetSourceIpAddress() const
    {
        return m_sourceIpAddress;
    }

    /**
     * @brief   get destination port
     * @return  uint16_t
     */
    inline uint16_t
    GetDestinationPort() const
    {
        return m_destinationPort;
    }

    /**
     * @brief   get protocol
     * @return  std::string
     */
    inline std::string const&
    GetProtocol() const
    {
        return m_protocol;
    }

    /**
     * @brief   get partition ID
     * @return  uint32_t
     */
    inline uint32_t
    GetPartitionId() const
    {
        return m_partitionId;
    }

    /**
     * @brief   get process name
     * @return  std::string
     */
    inline std::string const&
    GetProcessName() const
    {
        return m_processName;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   ErrorEventLoggingUserLoginCountersEntry const& other - the ErrorEventLoggingUserLoginCountersEntry
     * object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(ErrorEventLoggingUserLoginCountersEntry const& other) const
    {
        return (SecurityEventInstanceIdEntry::isEqual(other)) && (other.m_userName == m_userName)
               && (other.m_failReason == m_failReason) && (other.m_sourceIpAddress == m_sourceIpAddress)
               && (other.m_destinationPort == m_destinationPort) && (other.m_protocol == m_protocol)
               && (other.m_partitionId == m_partitionId) && (other.m_processName == m_processName);
    }

private:
    std::string m_userName;
    uint32_t    m_failReason{};
    IpType      m_sourceIpAddress{};
    uint16_t    m_destinationPort{};
    std::string m_protocol;
    uint32_t    m_partitionId{};
    std::string m_processName;
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::ErrorEventLoggingUserLoginCountersEntry;

template <>
class hash<ErrorEventLoggingUserLoginCountersEntry>
{
public:
    /**
     * @brief   hash function of ErrorEventLoggingUserLoginCountersEntry object
     *          Must be implemented so ErrorEventLoggingUserLoginCountersEntry can be used as map key.
     * @param   ErrorEventLoggingUserLoginCountersEntry entry - the ErrorEventLoggingUserLoginCountersEntry object to
     * get hash for
     * @return  size_t - The hash value of the given ErrorEventLoggingUserLoginCountersEntry.
     */
    size_t
    operator()(ErrorEventLoggingUserLoginCountersEntry const& entry) const
    {
        std::array<size_t, 8U> hashes;
        hashes[0U] = std::hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<std::string>()(entry.GetUserName());
        hashes[2U] = hash<uint32_t>()(entry.GetFailReason());
        hashes[3U] = hash<IpType>()(entry.GetSourceIpAddress());
        hashes[4U] = hash<uint16_t>()(entry.GetDestinationPort());
        hashes[5U] = hash<std::string>()(entry.GetProtocol());
        hashes[6U] = hash<uint32_t>()(entry.GetPartitionId());
        hashes[7U] = hash<std::string>()(entry.GetProcessName());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif
