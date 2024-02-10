/**
 * @file
 * @brief     This file contains the definition of the ExternalUnsuccessfulConnectionsEntry class and its functionality.
 */
#ifndef EXTERNAL_UNSUCCESSFUL_CONNECTIONS_ENTRY_ENTRY_HPP
#define EXTERNAL_UNSUCCESSFUL_CONNECTIONS_ENTRY_ENTRY_HPP

#include "ExternalEventEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using IpType = brain::utils::IpType;

/**
 * @class       ExternalUnsuccessfulConnectionsEntry
 */
class ExternalUnsuccessfulConnectionsEntry final : public ExternalEventEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceID
     * @param   uint8_t sensorInstanceID
     * @param   uint8_t connectionType
     * @param   unit64_t addressOfConnectingUnit
     * @param   uint32_t refusalReason
     * @param   std::string const& connectionUnitDeviceName
     */
    ExternalUnsuccessfulConnectionsEntry(uint16_t           idsMInstanceId,
                                         uint8_t            sensorInstanceId,
                                         uint8_t            connectionType,
                                         uint64_t           addressOfConnectingUnit,
                                         uint32_t           refusalReason,
                                         std::string const& connectionUnitDeviceName)
      : ExternalEventEntry(idsMInstanceId, sensorInstanceId, connectionType)
      , m_addressOfConnectingUnit(addressOfConnectingUnit)
      , m_refusalReason(refusalReason)
      , m_connectionUnitDeviceName(connectionUnitDeviceName)
    {
    }

    /**
     * @brief   Compare two IpDroppedConnectionsEntry objects
     * @param   ExternalUnsuccessfulConnectionsEntry const& other - the ExternalUnsuccessfulConnectionsEntry object to
     * compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(ExternalUnsuccessfulConnectionsEntry const& other) const
    {
        return ExternalEventEntry::isEqual(other) && (m_addressOfConnectingUnit == other.m_addressOfConnectingUnit)
               && (m_refusalReason == other.m_refusalReason)
               && (m_connectionUnitDeviceName == other.m_connectionUnitDeviceName);
    }

    /**
     * @brief   Compare two IpDroppedConnectionsEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   ExternalUnsuccessfulConnectionsEntry const& other - the ExternalUnsuccessfulConnectionsEntry object to
     * compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(ExternalUnsuccessfulConnectionsEntry const& other) const
    {
        return !(*this == other);
    }

    /**
     * @brief   get addressOfConnectingUnit
     * @param   none
     * @return  uint64_t
     */
    inline uint64_t
    GetAddressOfConnectingUnit() const
    {
        return m_addressOfConnectingUnit;
    }

    /**
     * @brief   get refusalReason
     * @return  uint32_t
     */
    inline uint32_t
    GetRefusalReason() const
    {
        return m_refusalReason;
    }

    /**
     * @brief   get connectionUnitDeviceName
     * @return  std::string
     */
    inline std::string const&
    GetConnectionUnitDeviceName() const
    {
        return m_connectionUnitDeviceName;
    }

private:
    uint64_t    m_addressOfConnectingUnit{};
    uint32_t    m_refusalReason{};
    std::string m_connectionUnitDeviceNameLength;
    std::string m_connectionUnitDeviceName;
};

using SPExternalUnsuccessfulConnectionsEntry = std::shared_ptr<ExternalUnsuccessfulConnectionsEntry>;

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::ExternalUnsuccessfulConnectionsEntry;
using IpType = brain::utils::IpType;
template <>
class hash<ExternalUnsuccessfulConnectionsEntry>
{
public:
    /**
     * @brief   hash function of ExternalUnsuccessfulConnectionsEntry object
     *          Must be implemented so ExternalUnsuccessfulConnectionsEntry can be used as map key.
     * @param   ExternalUnsuccessfulConnectionsEntry entry - the ExternalUnsuccessfulConnectionsEntry object to get hash
     * for
     * @return  size_t - The hash value of the given ExternalUnsuccessfulConnectionsEntry.
     */
    size_t
    operator()(ExternalUnsuccessfulConnectionsEntry const& entry) const
    {
        std::array<size_t, 4U> hashes;
        hashes[0U] = std::hash<ExternalEventEntry>()(entry);
        hashes[1U] = hash<uint64_t>()(entry.GetAddressOfConnectingUnit());
        hashes[2U] = hash<uint32_t>()(entry.GetRefusalReason());
        hashes[3U] = hash<std::string>()(entry.GetConnectionUnitDeviceName());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // EXTERNAL_UNSUCCESSFUL_CONNECTIONS_ENTRY_ENTRY_HPP
