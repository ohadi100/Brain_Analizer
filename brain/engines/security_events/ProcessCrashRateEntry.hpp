/**
 * @file
 * @brief     This file contains the definition of the ProcessCrashRateEntry class and its functionality.
 *            ProcessCrashRateEntry contains idsMInstanceId, sensorInstanceId, vmIdentifier, processName, typeOfError
 * and crashReason.
 */
#ifndef PROCESS_CRASH_RATE_ENTRY_HPP
#define PROCESS_CRASH_RATE_ENTRY_HPP

#include "HostOsLogEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

/**
 * @class               ProcessCrashRateEntry
 * @brief               The ProcessCrashRateEntry contains idsMInstanceId, sensorInstanceId, vmIdentifier, processName,
 * typeOfError and crashReason
 * @internalInterfaces  The ProcessCrashRateEntry provides a type representation and hash function, so it can be used as
 * unordered map key.
 */
class ProcessCrashRateEntry final : public HostOsLogEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t  idsMInstanceId
     * @param   uint8_t  sensorInstanceId
     * @param   uint8_t  vmIdentifier
     * @param   std::string  processName
     * @param   uint16_t  typeOfError
     * @param   uint8_t  crashReason
     */
    ProcessCrashRateEntry(uint16_t    idsMInstanceId,
                          uint8_t     sensorInstanceId,
                          uint8_t     vmIdentifier,
                          std::string processName,
                          uint16_t    typeOfError,
                          uint8_t     crashReason)
      : HostOsLogEntry(idsMInstanceId, sensorInstanceId, vmIdentifier)
      , m_processName(processName)
      , m_typeOfError(typeOfError)
      , m_crashReason(crashReason)
    {
    }

    /**
     * @brief   Compare two ProcessCrashRateEntry objects
     * @param   ProcessCrashRateEntry const& other - the ProcessCrashRateEntry object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    inline bool
    operator==(ProcessCrashRateEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two ProcessCrashRateEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   ProcessCrashRateEntry const& other - the ProcessCrashRateEntry object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    inline bool
    operator!=(ProcessCrashRateEntry const& other) const
    {
        return !isEqual(other);
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

    /**
     * @brief   get type of error
     * @return  uint16_t
     */
    inline uint16_t
    GetTypeOfError() const
    {
        return m_typeOfError;
    }

    /**
     * @brief   get crash reason
     * @return  uint8_t
     */
    inline uint8_t
    GetCrashReason() const
    {
        return m_crashReason;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   ProcessCrashRateEntry const& other - the ProcessCrashRateEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    inline bool
    isEqual(ProcessCrashRateEntry const& other) const
    {
        return ((HostOsLogEntry::isEqual(other)) && (m_processName == other.GetProcessName())
                && (m_typeOfError == other.GetTypeOfError()) && (m_crashReason == other.GetCrashReason()));
    }

private:
    std::string m_processName;
    uint16_t    m_typeOfError{};
    uint8_t     m_crashReason{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::ProcessCrashRateEntry;

template <>
class hash<ProcessCrashRateEntry>
{
public:
    /**
     * @brief   hash function of ProcessCrashRateEntry object
     *          Must be implemented so ProcessCrashRateEntry can be used as map key.
     * @param   ProcessCrashRateEntry entry - the ProcessCrashRateEntry object to get hash for
     * @return  size_t - The hash value of the given ProcessCrashRateEntry.
     */
    size_t
    operator()(ProcessCrashRateEntry const& entry) const
    {
        std::array<size_t, 4U> hashes;
        hashes[0U] = std::hash<HostOsLogEntry>()(entry);
        hashes[1U] = hash<std::string>()(entry.GetProcessName());
        hashes[2U] = hash<uint16_t>()(entry.GetTypeOfError());
        hashes[3U] = hash<uint8_t>()(entry.GetCrashReason());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // PROCESS_CRASH_RATE_ENTRY_HPP