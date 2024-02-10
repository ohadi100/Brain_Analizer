/**
 * @file
 * @brief     This file contains the definition of the FreshnessValueFailedEntry class and its functionality.
 *            FreshnessValueFailedEntry contains IDSm instance ID, Sensor instance ID, fvmErrorCode, pduId.
 */
#ifndef FRESHNESS_VALUE_FAILED_ENTRY_HPP
#define FRESHNESS_VALUE_FAILED_ENTRY_HPP

#include "SecurityEventInstanceIdEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

/**
 * @class               FreshnessValueFailedEntry
 * @brief               The FreshnessValueFailedEntry class
 * @internalInterfaces  The FreshnessValueFailedEntry provides a type representation and hash function, so it can be
 * used as unordered map key.
 */
class FreshnessValueFailedEntry final : public SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId - ids instance id
     * @param   uint8_t  sensorInstanceId - sensor instance id
     * @param   uint16_t fvmErrorCode - FVM error code
     * @param   uint16_t pduId - PDU-ID
    */
    FreshnessValueFailedEntry(uint16_t idsMInstanceId, uint8_t sensorInstanceId, uint16_t fvmErrorCode, uint16_t pduId)
      : SecurityEventInstanceIdEntry(idsMInstanceId, sensorInstanceId)
      , m_fvmErrorCode{fvmErrorCode}
      , m_pduId{pduId}
    {
    }

    /**
     * @brief   Compare two FreshnessValueFailedEntry objects
     * @param   FreshnessValueFailedEntry const& other - the FreshnessValueFailedEntry object to compare to
     * @return  bool - true all fields are equal. false otherwise
     */
    bool
    operator==(FreshnessValueFailedEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two FreshnessValueFailedEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   FreshnessValueFailedEntry const& other - the FreshnessValueFailedEntry object to compare to
     * @return  bool - true any field is different. false otherwise
     */
    bool
    operator!=(FreshnessValueFailedEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get FVM error code
     * @return  uint16_t
     */
    inline uint16_t
    GetFvmErrorCode() const
    {
        return m_fvmErrorCode;
    }

    /**
     * @brief   get PDU-ID
     * @return  uint16_t
     */
    inline uint16_t
    GetPduId() const
    {
        return m_pduId;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   FreshnessValueFailedEntry const& other - the FreshnessValueFailedEntry object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(FreshnessValueFailedEntry const& other) const
    {
        return SecurityEventInstanceIdEntry::isEqual(other) && (other.m_fvmErrorCode == m_fvmErrorCode)
               && (other.m_pduId == m_pduId);
    };

private:
    uint16_t m_fvmErrorCode{};
    uint16_t m_pduId{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{

template <>
class hash<brain::engines::security_events::FreshnessValueFailedEntry>
{
public:
    /**
     * @brief   hash function of FreshnessValueFailedEntry object
     *          Must be implemented so FreshnessValueFailedEntry can be used as map key.
     * @param   FreshnessValueFailedEntry entry - the FreshnessValueFailedEntry object to get hash for
     * @return  size_t - The hash value of the given FreshnessValueFailedEntry.
     */
    size_t
    operator()(brain::engines::security_events::FreshnessValueFailedEntry const& entry) const
    {
        std::array<size_t, 3U> hashes;
        hashes[0U] = std::hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<uint16_t>()(entry.GetFvmErrorCode());
        hashes[2U] = hash<uint16_t>()(entry.GetPduId());

        return common::utils::CombineHash(hashes);
    }
};

}  // namespace std

#endif  // FRESHNESS_VALUE_FAILED_ENTRY_HPP