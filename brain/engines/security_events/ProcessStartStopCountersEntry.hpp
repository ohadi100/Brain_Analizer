/**
 * @file
 * @brief     This file contains the definitiond of the ProcessStartStopEntry.
 */
#ifndef PROCESS_START_STOP_ENTRY_HPP
#define PROCESS_START_STOP_ENTRY_HPP

#include "HostOsLogEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

class ProcessStartStopCountersEntry final : public HostOsLogEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId - IDSm instance ID
     * @param   uint8_t sensorInstanceId - sensor instance ID
     * @param   uint8_t vmIdentifier - VM identifier
     * @param   uint16_t groupId - Group ID
     * @param   std::string const& adaptiveAutosarAppName - Adaptive AUTOSAR Application Name
     * @param   std::string const& processCommandLine - Process command line
     */
    ProcessStartStopCountersEntry(uint16_t           idsMInstanceId,
                                  uint8_t            sensorInstanceId,
                                  uint8_t            vmIdentifier,
                                  uint16_t           groupId,
                                  std::string const& adaptiveAutosarAppName,
                                  std::string const& processCommandLine)
      : HostOsLogEntry(idsMInstanceId, sensorInstanceId, vmIdentifier)
      , m_groupId(groupId)
      , m_adaptiveAutosarAppName(adaptiveAutosarAppName)
      , m_processCommandLine(processCommandLine)
    {
    }

    /**
     * @brief   Compare two ProcessStartStopCountersEntry objects
     * @param   ProcessStartStopCountersEntry const& other - the ProcessStartStopCountersEntry object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(ProcessStartStopCountersEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two ProcessStartStopCountersEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   ProcessStartStopCountersEntry const& other - the ProcessStartStopCountersEntry object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(ProcessStartStopCountersEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get VM group ID
     * @return  uint16_t
     */
    inline uint16_t
    GetGroupId() const
    {
        return m_groupId;
    }

    /**
     * @brief   get adaptive AUTOSAR application name
     * @return  std::string
     */
    inline std::string const&
    GetAdaptiveAutosarAppName() const
    {
        return m_adaptiveAutosarAppName;
    }

    /**
     * @brief   get process command line
     * @return  std::string
     */
    inline std::string const&
    GetProcessCommandLine() const
    {
        return m_processCommandLine;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   ProcessStartStopCountersEntry const& other - the ProcessStartStopCountersEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(ProcessStartStopCountersEntry const& other) const
    {
        return ((HostOsLogEntry::isEqual(other)) && (other.m_groupId == m_groupId)
                && (other.m_adaptiveAutosarAppName == m_adaptiveAutosarAppName)
                && (other.m_processCommandLine == m_processCommandLine));
    }

private:
    uint16_t    m_groupId{};
    std::string m_adaptiveAutosarAppName;
    std::string m_processCommandLine;
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::ProcessStartStopCountersEntry;

template <>
class hash<ProcessStartStopCountersEntry>
{
public:
    /**
     * @brief   hash function of ProcessStartStopCountersEntry object
     *          Must be implemented so ProcessStartStopCountersEntry can be used as map key.
     * @param   ProcessStartStopCountersEntry entry - the ProcessStartStopCountersEntry object to get hash for
     * @return  size_t - The hash value of the given ProcessStartStopCountersEntry.
     */
    size_t
    operator()(ProcessStartStopCountersEntry const& entry) const
    {
        std::array<size_t, 4U> hashes;
        hashes[0U] = std::hash<HostOsLogEntry>()(entry);
        hashes[1U] = hash<uint16_t>()(entry.GetGroupId());
        hashes[2U] = hash<std::string>()(entry.GetAdaptiveAutosarAppName());
        hashes[3U] = hash<std::string>()(entry.GetProcessCommandLine());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif
