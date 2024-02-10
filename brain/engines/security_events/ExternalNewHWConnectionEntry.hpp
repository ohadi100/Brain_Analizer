/**
 * @file
 * @brief     This file contains the definition of the ExternalNewHWConnectionEntry class and its functionality.
 *            ExternalNewHWConnectionEntry contains connection type, address of connecting unit and reason for
 * connection refusal.
 */
#ifndef EXTERNAL_NEW_HW_CONNECTION_ENTRY_HPP
#define EXTERNAL_NEW_HW_CONNECTION_ENTRY_HPP

#include "ExternalHwEventEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{
/**
 * @class               ExternalNewHWConnectionEntry
 * @brief               The ExternalNewHWConnectionEntry class connectionType, connectionAddress & refusalReason
 * @internalInterfaces  The ExternalNewHWConnectionEntry provides a type representation and hash function, so it can be
 * used as unordered map key.
 */
class ExternalNewHWConnectionEntry final : public ExternalHwEventEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId - IDSm instance ID
     * @param   uint8_t sensorInstanceId - sensor instance ID
     * @param   uint8_t connectionType - Type of connected hardware (1 Byte enumerator) [0x1: Ethernet, 0x2:
     * Keyboard, 0x3: Mouse, 0x4: Storage, 0x5: Other]
     * @param   std::string const& hardwareIdSerial - Hardware ID/Serial (16 Bytes UTF8)
     * @param   std::string const& deviceSubClasses - Device classes and sub classes (24 Byte String UTF8)
     * @param   std::string const& calledDriverLibrary - Driver Library called for handling connection (24 Bytes String
     * UTF8)
     * @param   std::string const& handlingConnectionDriverLibrary - Handling connection driver/library (24 Bytes String 
     * UTF8)
     */
    ExternalNewHWConnectionEntry(uint16_t           idsMInstanceId,
                                 uint8_t            sensorInstanceId,
                                 uint8_t            connectionType,
                                 std::string const& hardwareIdSerial,
                                 std::string const& deviceSubClasses,
                                 std::string const& calledDriverLibrary,
                                 std::string const& handlingConnectionDriverLibrary)
      : ExternalHwEventEntry(idsMInstanceId, sensorInstanceId, connectionType, hardwareIdSerial)
      , m_deviceSubClasses(deviceSubClasses)
      , m_calledDriverLibrary(calledDriverLibrary)
      , m_handlingConnectionDriverLibrary(handlingConnectionDriverLibrary)
    {
    }

    /**
     * @brief   Compare two ExternalNewHWConnectionEntry objects
     * @param   ExternalNewHWConnectionEntry const& other - the ExternalNewHWConnectionEntry object to compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    inline bool
    operator==(ExternalNewHWConnectionEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two ExternalNewHWConnectionEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   ExternalNewHWConnectionEntry const& other - the ExternalNewHWConnectionEntry object to compare to
     * @return  bool - true any field is different. false otherwise
     */
    inline bool
    operator!=(ExternalNewHWConnectionEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get device Sub Classes
     * @return  std::string
     */
    inline std::string const&
    GetDeviceSubClasses() const
    {
        return m_deviceSubClasses;
    }

    /**
     * @brief   get called Driver Library
     * @return  std::string
     */
    inline std::string const&
    GetCalledDriverLibrary() const
    {
        return m_calledDriverLibrary;
    }

    /**
     * @brief   get connection Driver Library
     * @return  std::string
     */
    inline std::string const&
    GetHandlingConnectionDriverLibrary() const
    {
        return m_handlingConnectionDriverLibrary;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   ExternalNewHWConnectionEntry const& other - the ExternalNewHWConnectionEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    inline bool
    isEqual(ExternalNewHWConnectionEntry const& other) const
    {
        return (ExternalHwEventEntry::isEqual(other) && m_deviceSubClasses == other.m_deviceSubClasses
                && m_calledDriverLibrary == other.m_calledDriverLibrary
                && m_handlingConnectionDriverLibrary == other.m_handlingConnectionDriverLibrary);
    }

private:
    std::string m_deviceSubClasses;
    std::string m_calledDriverLibrary;
    std::string m_handlingConnectionDriverLibrary;
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::ExternalNewHWConnectionEntry;


template <>
class hash<ExternalNewHWConnectionEntry>
{
public:
    /**
     * @brief   hash function of ExternalNewHWConnectionEntry object
     *          Must be implemented so ExternalNewHWConnectionEntry can be used as map key.
     * @param   ExternalNewHWConnectionEntry entry - the ExternalNewHWConnectionEntry object to get hash for
     * @return  size_t - The hash value of the given ExternalNewHWConnectionEntry.
     */
    size_t
    operator()(ExternalNewHWConnectionEntry const& entry) const
    {
        std::array<size_t, 4U> hashes;
        hashes[0U] = std::hash<ExternalHwEventEntry>()(entry);
        hashes[1U] = hash<std::string>()(entry.GetDeviceSubClasses());
        hashes[2U] = hash<std::string>()(entry.GetCalledDriverLibrary());
        hashes[3U] = hash<std::string>()(entry.GetHandlingConnectionDriverLibrary());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // EXTERNAL_NEW_HW_CONNECTION_ENTRY_HPP