/**
 * @file
 * @brief     This file contains the definition of the ExternalDataStorageEntry class and its functionality.
 *            ExternalDataStorageEntry contains connection type, address of connecting unit and reason for connection
 * refusal.
 */
#ifndef EXTERNAL_DATA_STORAGE_ENTRY_HPP
#define EXTERNAL_DATA_STORAGE_ENTRY_HPP

#include "ExternalHwEventEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{


/**
 * @class               ExternalDataStorageEntry
 * @brief               The ExternalDataStorageEntry class connectionType, connectionAddress & refusalReason
 * @internalInterfaces  The ExternalDataStorageEntry provides a type representation and hash function, so it can be used
 * as unordered map key.
 */
class ExternalDataStorageEntry final : public ExternalHwEventEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId - IDSm instance ID
     * @param   uint8_t sensorInstanceId - sensor instance ID
     * @param   uint8_t const connectionType - WIFI 0x00, BT 0x01, BLE 0x02, NFC 0x03, 3G 4G 5G 0x04
     * @param   std::string const& hardwareIdSerialNumber - Hardware ID or Serial Number
     * @param   uint8_t fileSystem - enum according to the file system - 0x0: No File System, 0x1: NTFS=0x1,
     * FAT32=0x2, etc
     */
    ExternalDataStorageEntry(uint16_t           idsMInstanceId,
                             uint8_t            sensorInstanceId,
                             uint8_t            connectionType,
                             std::string const& hardwareIdSerialNumber,
                             uint8_t            fileSystem)
      : ExternalHwEventEntry(idsMInstanceId, sensorInstanceId, connectionType, hardwareIdSerialNumber)
      , m_fileSystem(fileSystem)
    {
    }

    /**
     * @brief   Compare two ExternalDataStorageEntry objects
     * @param   ExternalDataStorageEntry const& other - the ExternalDataStorageEntry object to compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    bool
    operator==(ExternalDataStorageEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two ExternalDataStorageEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   ExternalDataStorageEntry const& other - the ExternalDataStorageEntry object to compare to
     * @return  bool - true any field is different. false otherwise
     */
    bool
    operator!=(ExternalDataStorageEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get file system 0x0: No File System, 0x1: NTFS=0x1, FAT32=0x2, etc
     * @return  uint8_t
     */
    inline uint8_t
    GetFileSystem() const
    {
        return m_fileSystem;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   ExternalDataStorageEntry const& other - the ExternalDataStorageEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(ExternalDataStorageEntry const& other) const
    {
        return ExternalHwEventEntry::isEqual(other) && (m_fileSystem == other.m_fileSystem);
    }

private:
    uint8_t m_fileSystem{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::ExternalDataStorageEntry;
using AddressType = brain::utils::AddressType;

template <>
class hash<ExternalDataStorageEntry>
{
public:
    /**
     * @brief   hash function of ExternalDataStorageEntry object
     *          Must be implemented so ExternalDataStorageEntry can be used as map key.
     * @param   ExternalDataStorageEntry entry - the ExternalDataStorageEntry object to get hash for
     * @return  size_t - The hash value of the given ExternalDataStorageEntry.
     */
    size_t
    operator()(ExternalDataStorageEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = std::hash<ExternalHwEventEntry>()(entry);
        hashes[1U] = hash<uint8_t>()(entry.GetFileSystem());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // EXTERNAL_DATA_STORAGE_ENTRY_HPP