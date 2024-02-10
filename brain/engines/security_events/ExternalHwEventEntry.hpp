/**
 * @file
 * @brief     This file contains the definition of the ExternalHwEventEntry class and its functionality.
 *            ExternalHwEventEntry contains connection type, address of connecting unit and reason for connection
 * refusal.
 */
#ifndef EXTERNAL_HW_EVENT_ENTRY_HPP
#define EXTERNAL_HW_EVENT_ENTRY_HPP

#include "ExternalEventEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{
/**
 * @class               ExternalHwEventEntry
 * @brief               The ExternalHwEventEntry class connectionType, connectionAddress & refusalReason
 * @internalInterfaces  The ExternalHwEventEntry provides a type representation and hash function, so it can be used as
 * unordered map key.
 */
class ExternalHwEventEntry : public ExternalEventEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId - IDSm instance ID
     * @param   uint8_t sensorInstanceId - sensor instance ID
     * @param   uint8_t connectionType - Type of connected hardware (1 Byte enumerator) [0x1: Ethernet, 0x2:
     * Keyboard, 0x3: Mouse, 0x4: Storage, 0x5: Other]
     * @param   std::string const& hardwareIdSerial - Hardware ID/Serial (16 Bytes UTF8)
     */
    ExternalHwEventEntry(uint16_t           idsMInstanceId,
                         uint8_t            sensorInstanceId,
                         uint8_t            connectionType,
                         std::string const& hardwareIdSerial)
      : ExternalEventEntry(idsMInstanceId, sensorInstanceId, connectionType)
      , m_hardwareIdSerial(hardwareIdSerial)
    {
    }

    /**
     * @brief   Compare two ExternalHwEventEntry objects
     * @param   ExternalHwEventEntry const& other - the ExternalHwEventEntry object to compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    inline bool
    operator==(ExternalHwEventEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two ExternalHwEventEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   ExternalHwEventEntry const& other - the ExternalHwEventEntry object to compare to
     * @return  bool - true any field is different. false otherwise
     */
    inline bool
    operator!=(ExternalHwEventEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get hardware serial address
     * @return  std::string
     */
    inline std::string const&
    GetHardwareIdSerialNumber() const
    {
        return m_hardwareIdSerial;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   ExternalHwEventEntry const& other - the ExternalHwEventEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    inline bool
    isEqual(ExternalHwEventEntry const& other) const
    {
        return (ExternalEventEntry::isEqual(other) && m_hardwareIdSerial == other.m_hardwareIdSerial);
    }

private:
    std::string m_hardwareIdSerial;
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::ExternalHwEventEntry;


template <>
class hash<ExternalHwEventEntry>
{
public:
    /**
     * @brief   hash function of ExternalHwEventEntry object
     *          Must be implemented so ExternalHwEventEntry can be used as map key.
     * @param   ExternalHwEventEntry entry - the ExternalHwEventEntry object to get hash for
     * @return  size_t - The hash value of the given ExternalHwEventEntry.
     */
    size_t
    operator()(ExternalHwEventEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = std::hash<ExternalEventEntry>()(entry);
        hashes[1U] = hash<std::string>()(entry.GetHardwareIdSerialNumber());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // EXTERNAL_HW_EVENT_ENTRY_HPP