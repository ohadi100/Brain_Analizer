/**
 * @file
 * @brief     This file contains the definition of the ServiceRegistryEntry class and its functionality.
 *            ServiceRegistryEntry contains IdsM instance ID, sensor instance ID, service registry ID, registered
 * service, registering application ID, registering server IP address and success/failure indicator.
 */
#ifndef SERVICE_REGISTRY_ENTRY_HPP
#define SERVICE_REGISTRY_ENTRY_HPP

#include "SecurityEventInstanceIdEntry.hpp"
#include "brain/utils/IpUtils.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using brain::utils::IpType;

/**
 * @class               ServiceRegistryEntry
 * @brief               The ServiceRegistryEntry class contains IdsM instance ID, sensor instance ID, service registry
 * ID, registered service, registering application ID, registering server IP address and success/failure indicator
 * @internalInterfaces  The ServiceRegistryEntry provides a type representation and hash function, so it can be used as
 * unordered map key.
 */
class ServiceRegistryEntry final : public SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t  idsMInstanceId - idsM instance Id
     * @param   uint8_t  sensorInstanceId - sensor instance Id
     * @param   uint32_t  serviceRegistryId - service registry Id
     * @param   std::string const& registeredService - registered service
     * @param   std::string const& registeringApplicationId - registering application Id
     * @param   IpType const& registeringServerIP - registering server IP address
     * @param   bool  successIndicator -  indicator. true for success, false for failure
     */
    ServiceRegistryEntry(uint16_t           idsMInstanceId,
                         uint8_t            sensorInstanceId,
                         uint32_t           serviceRegistryId,
                         std::string const& registeredService,
                         std::string const& registeringApplicationId,
                         IpType const&      registeringServerIP,
                         bool               successIndicator)
      : SecurityEventInstanceIdEntry(idsMInstanceId, sensorInstanceId)
      , m_serviceRegistryId(serviceRegistryId)
      , m_registeredService(registeredService)
      , m_registeringApplicationId(registeringApplicationId)
      , m_registeringServerIP(registeringServerIP)
      , m_indicator(successIndicator)
    {
    }

    /**
     * @brief   Compare two ServiceRegistryEntry objects
     * @param   ServiceRegistryEntry const& other - the ServiceRegistryEntry object to compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    inline bool
    operator==(ServiceRegistryEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two ServiceRegistryEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   ServiceRegistryEntry const& other - the ServiceRegistryEntry object to compare to
     * @return  bool - true any field is different. false otherwise
     */
    inline bool
    operator!=(ServiceRegistryEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get service registry Id
     * @return  uint32_t
     */
    inline uint32_t
    GetServiceRegistryId() const
    {
        return m_serviceRegistryId;
    }

    /**
     * @brief   get registered service
     * @return  std::string
     */
    inline std::string const&
    GetRegisteredService() const
    {
        return m_registeredService;
    }

    /**
     * @brief   get registering application Id
     * @return  std::string
     */
    inline std::string const&
    GetRegisteringApplicationId() const
    {
        return m_registeringApplicationId;
    }

    /**
     * @brief   get registering server IP
     * @return  IpType
     */
    inline IpType const&
    GetRegisteringServerIP() const
    {
        return m_registeringServerIP;
    }

    /**
     * @brief   get success/failure indicator
     * @return  bool - true for success, otherwise false
     */
    inline bool
    GetIndicator() const
    {
        return m_indicator;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   ServiceRegistryEntry const& other - the ServiceRegistryEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    inline bool
    isEqual(ServiceRegistryEntry const& other) const
    {
        return (SecurityEventInstanceIdEntry::isEqual(other)) && (m_serviceRegistryId == other.m_serviceRegistryId)
                && (m_registeredService == other.m_registeredService)
                && (m_registeringApplicationId == other.m_registeringApplicationId)
                && (m_registeringServerIP == other.m_registeringServerIP) && (m_indicator == other.m_indicator);
    }

private:
    uint32_t    m_serviceRegistryId{};
    std::string m_registeredService;
    std::string m_registeringApplicationId;
    IpType      m_registeringServerIP;
    bool        m_indicator;  // true for success, otherwise false
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain


namespace std
{
using brain::engines::security_events::ServiceRegistryEntry;
using IpType = brain::utils::IpType;

template <>
class hash<ServiceRegistryEntry>
{
public:
    /**
     * @brief   hash function of ServiceRegistryEntry object
     *          Must be implemented so ServiceRegistryEntry can be used as map key.
     * @param   ServiceRegistryEntry entry - the ServiceRegistryEntry object to get hash for
     * @return  size_t - The hash value of the given ServiceRegistryEntry.
     */
    size_t
    operator()(ServiceRegistryEntry const& entry) const
    {
        std::array<size_t, 6U> hashes;
        hashes[0U] = std::hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<uint32_t>()(entry.GetServiceRegistryId());
        hashes[2U] = hash<std::string>()(entry.GetRegisteredService());
        hashes[3U] = hash<std::string>()(entry.GetRegisteringApplicationId());
        hashes[4U] = hash<IpType>()(entry.GetRegisteringServerIP());
        hashes[5U] = hash<bool>()(entry.GetIndicator());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // SERVICE_REGISTRY_ENTRY_HPP