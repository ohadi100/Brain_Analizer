/**
 * @file
 * @brief     This file contains the definition of the DiagnosticEventSequenceEntry class and its functionality.
 */
#ifndef DIAGNOSTIC_EVENT_SEQUENCE_ENTRY_HPP
#define DIAGNOSTIC_EVENT_SEQUENCE_ENTRY_HPP

#include <stdint.h>
#include <memory>


namespace brain
{
namespace engines
{
namespace security_events
{

/**
 * @class       DiagnosticEventSequenceEntry
 */
class DiagnosticEventSequenceEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint64_t const timestamp
     * @param   uint32_t const securityEventID
     * @return	none
     */
    DiagnosticEventSequenceEntry(uint64_t timestamp, uint32_t securityEventID)
      : m_timestamp(timestamp)
      , m_securityEventID(securityEventID)
    {
    }

    /**
     * @brief   Compare two DiagnosticEventSequenceEntry objects
     * @param   DiagnosticEventSequenceEntry const& other - the DiagnosticEventSequenceEntry object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(DiagnosticEventSequenceEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two DiagnosticEventSequenceEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   DiagnosticEventSequenceEntry const& other - the DiagnosticEventSequenceEntry object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(DiagnosticEventSequenceEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get securityevent ID
     * @return  uint32_t
     */
    inline uint32_t
    GetSecurityEventID() const
    {
        return m_securityEventID;
    }

    /**
     * @brief   get vmIdentifier
     * @return  uint64_t
     */
    inline uint64_t
    GetTimestamp() const
    {
        return m_timestamp;
    }

protected:
    /**
     * @brief   compare data and return the result
     * @param   DiagnosticEventSequenceEntry const& other - the DiagnosticEventSequenceEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(DiagnosticEventSequenceEntry const& other) const
    {
        return (other.m_timestamp == m_timestamp) && (other.m_securityEventID == m_securityEventID);
    }

private:
    uint64_t m_timestamp{};
    uint32_t m_securityEventID{};
};

using SPDiagnosticEventSequenceEntry = std::shared_ptr<DiagnosticEventSequenceEntry>;

}  // namespace security_events
}  // namespace engines
}  // namespace brain

#endif  // DIAGNOSTIC_EVENT_SEQUENCE_ENTRY_HPP
