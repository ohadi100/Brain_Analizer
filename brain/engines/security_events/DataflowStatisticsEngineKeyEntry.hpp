/**
 * @file
 * @brief     This file contains the definition of the DataflowStatisticsEngineKeyEntry class and its functionality.
 *            DataflowStatisticsEngineKeyEntry contains the uniqe parameters which identifies the keys in the
 *            DataflowStatisticsEngine. The key consist of IDSm instance ID, Sensor instance ID and Uid (used as port
 *            number)
 */
#ifndef DATAFLOW_STATISTICS_ENGINE_KEY_ENTRY_HPP
#define DATAFLOW_STATISTICS_ENGINE_KEY_ENTRY_HPP
#include <stdint.h>
#include <memory>
#include "SecurityEventInstanceIdEntry.hpp"


namespace brain
{
namespace engines
{
namespace security_events
{


/**
 * @class               DataflowStatisticsEngineKeyEntry
 * @brief               The DataflowStatisticsEngineKeyEntry with keys EventId, idsMInstanceId & sensorInstanceId
 * @internalInterfaces  The DataflowStatisticsEngineKeyEntry provides a type representation and hash function, so it
 * can be used as unordered map key.
 */
class DataflowStatisticsEngineKeyEntry final : public SecurityEventInstanceIdEntry
{
public:
    /**
     * @brief   Constructor
     * @param   uint16_t idsMInstanceId
     * @param   uint8_t sensorInstanceId
     * @param   uint32_t uId
     */
    DataflowStatisticsEngineKeyEntry(uint16_t idsMInstanceId, uint8_t sensorInstanceId, uint32_t uId)
      : SecurityEventInstanceIdEntry{idsMInstanceId, sensorInstanceId}
      , m_uid{uId}
    {
    }

    /**
     * @brief   Compare two DataflowStatisticsEngineKeyEntry objects
     * @param   DataflowStatisticsEngineKeyEntry const& other - the DataflowStatisticsEngineKeyEntry object to compare
     * to
     * @return  bool - true all fields are equal. false otherwise
     */
    bool
    operator==(DataflowStatisticsEngineKeyEntry const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two DataflowStatisticsEngineKeyEntry objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   DataflowStatisticsEngineKeyEntry const& other - the DataflowStatisticsEngineKeyEntry object to compare
     * to
     * @return  bool - true any field is different. false otherwise
     */
    bool
    operator!=(DataflowStatisticsEngineKeyEntry const& other) const
    {
        return !isEqual(other);
    }

    /**
     * @brief   get the m_uid (port nuber)
     * @return  uint32_t
     */
    inline uint32_t
    GetUId() const
    {
        return m_uid;
    }

    inline void
    SetUid(uint32_t uid)
    {
        m_uid = uid;
    }

protected:
    /**
     * @brief   copy the internal data
     * @param   DataflowStatisticsEngineKeyEntry const& other - the DataflowStatisticsEngineKeyEntry object to check
     * if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(DataflowStatisticsEngineKeyEntry const& other) const
    {
        return (SecurityEventInstanceIdEntry::isEqual(other) && (m_uid == other.m_uid));
    }


private:
    uint32_t m_uid{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

namespace std
{
using brain::engines::security_events::DataflowStatisticsEngineKeyEntry;
// using common::utils::CombineHash;

template <>
class hash<DataflowStatisticsEngineKeyEntry>
{
public:
    /**
     * @brief   hash function of DataflowStatisticsEngineKeyEntry object
     *          Must be implemented so DataflowStatisticsEngineKeyEntry can be used as map key.
     * @param   DataflowStatisticsEngineKeyEntry entry - the DataflowStatisticsEngineKeyEntry object to get hash for
     * @return  size_t - The hash value of the given DataflowStatisticsEngineKeyEntry.
     */
    size_t
    operator()(DataflowStatisticsEngineKeyEntry const& entry) const
    {
        std::array<size_t, 2U> hashes;
        hashes[0U] = hash<SecurityEventInstanceIdEntry>()(entry);
        hashes[1U] = hash<uint32_t>()(entry.GetUId());
        return common::utils::CombineHash(hashes);
    }
};
}  // namespace std

#endif  // DATAFLOW_STATISTICS_ENGINE_KEY_ENTRY_HPP