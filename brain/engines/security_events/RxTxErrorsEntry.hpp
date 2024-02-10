/**
 * @file
 * @brief     This file contains the definitiond of the RxTxErrorsEntry.
 */
#pragma once

#include "SecurityEventInstanceIdEntry.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{
/**
 * @class RxTxErrorsEntry
 * @brief The RxTxErrorsEntry holds the table keys of RxTxErrors table
 */
class RxTxErrorsEntry final : public SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief Constructs a RXErrors or TXErrors Entry  from given IDs/state.
     * @param[in] idsMInstanceId   IDSm instance ID
     * @param[in] sensorInstanceId sensor instance ID
     * @param[in] errorType        error type from context data
     * @param[in] busId            bus ID from context data
     * @param[in] canId            can ID from context data
     * @param[in] controllerId     controller ID from context data
     */
    RxTxErrorsEntry(uint16_t idsMInstanceId,
                    uint8_t  sensorInstanceId,
                    uint8_t  errorType,
                    uint16_t busId,
                    uint32_t canId,
                    uint8_t  controllerId)
      : SecurityEventInstanceIdEntry(idsMInstanceId, sensorInstanceId)
      , m_errorType{errorType}
      , m_busId{busId}
      , m_canId{canId}
      , m_controllerId{controllerId}
    {
    }

    /**
     * @brief Compare two RxTxErrorsEntry objects
     * @param[in] other - the RxTxErrorsEntry object to compare to
     * @return true all fields are equal. false otherwise
     */
    inline bool
    operator==(RxTxErrorsEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief Compare two RxTxErrorsEntry objects, checks if different
     *        Objects are not equal, if any of the fields aren't equal
     * @param[in]  other - the RxTxErrorsEntry object to compare to
     * @return true any field is different. false otherwise
     */
    inline bool
    operator!=(RxTxErrorsEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get error type
     * @return  uint8_t
     */
    inline constexpr uint8_t
    GetErrorType() const
    {
        return m_errorType;
    }

    /**
     * @brief   get CAN ID
     * @return  uint32_t
     */
    inline constexpr uint32_t
    GetCanId() const
    {
        return m_canId;
    }

    /**
     * @brief   get CAN bus ID
     * @return  uint16_t
     */
    inline constexpr uint16_t
    GetBusId() const
    {
        return m_busId;
    }

    /**
     * @brief   get controller ID
     * @return  uint8_t
     */
    inline constexpr uint8_t
    GetControllerId() const
    {
        return m_controllerId;
    }

protected:
    /**
     * @brief Copy the internal data
     * @param[in]  other the RxTxErrorsEntry object to check if equal
     * @return true if all fields are equal, false otherwise
     */
    inline bool
    isEqual(RxTxErrorsEntry const& other) const
    {
        return SecurityEventInstanceIdEntry::isEqual(other) && (m_errorType == other.m_errorType)
               && (m_busId == other.m_busId) && (m_canId == other.m_canId) && (m_controllerId == other.m_controllerId);
    }

private:
    uint8_t  m_errorType{};     // RX/TX CAN Error Details
    uint16_t m_busId{};         // Bus ID
    uint32_t m_canId{};         // CAN ID
    uint8_t  m_controllerId{};  // CAN Controler ID reported the error
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::RxTxErrorsEntry;

template <>
class hash<RxTxErrorsEntry>
{
public:
    /**
     * @brief hash function of RxTxErrorsEntry object
     *        Must be implemented so RxTxErrorsEntry can be used as map key.
     * @param entry - the RxTxErrorsEntry object to get hash for
     * @return size_t - The hash value of the given RxTxErrorsEntry.
     */
    size_t
    operator()(RxTxErrorsEntry const& entry) const
    {
        std::array<size_t, 5U> hashes;
        hashes[0U] = std::hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<uint8_t>()(entry.GetErrorType());
        hashes[2U] = hash<uint16_t>()(entry.GetBusId());
        hashes[3U] = hash<uint32_t>()(entry.GetCanId());
        hashes[4U] = hash<uint8_t>()(entry.GetControllerId());

        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std