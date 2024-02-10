/**
 * @file
 * @brief     This file contains the definition of the ConnectionsCountersValue.
 */
#ifndef CONNECTIONS_COUNTERS_VALUE_HPP
#define CONNECTIONS_COUNTERS_VALUE_HPP

#include <string>

namespace brain
{
namespace engines
{
namespace security_events
{

class ConnectionsCountersValue final
{
public:
    /**
     * @brief constructor
     */
    ConnectionsCountersValue() = default;

    /**
     * @brief Constructs ConnectionsCountersValue strucutre
     */
    ConnectionsCountersValue(std::string const& payloadLength,
                             uint32_t           droppedBlockedConnectionAttemptsCount,
                             uint32_t           successfullConnectionAttemptsCount,
                             uint32_t           droppedNotificationsCount)
      : PayloadLength{payloadLength}
      , DroppedBlockedConnectionAttemptsCount{droppedBlockedConnectionAttemptsCount}
      , SuccessfullConnectionAttemptsCount{successfullConnectionAttemptsCount}
      , DroppedNotificationsCount{droppedNotificationsCount} {};

    /**
     * @brief   Compare two ConnectionsCountersValue objects
     * @param   ConnectionsCountersValue const& other - the ConnectionsCountersValue
     * object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(ConnectionsCountersValue const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two ConnectionsCountersValue objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   ConnectionsCountersValue const& other - the ConnectionsCountersValue
     * object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(ConnectionsCountersValue const& other) const
    {
        return !isEqual(other);
    }

    std::string PayloadLength;
    uint32_t    DroppedBlockedConnectionAttemptsCount{};
    uint32_t    SuccessfullConnectionAttemptsCount{};
    uint32_t    DroppedNotificationsCount{};

protected:
    /**
     * @brief   copy the internal data
     * @param   ConnectionsCountersValue const& other - the ConnectionsCountersValue
     * object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(ConnectionsCountersValue const& other) const
    {
        return (other.PayloadLength == PayloadLength)
               && (other.DroppedBlockedConnectionAttemptsCount == DroppedBlockedConnectionAttemptsCount)
               && (other.SuccessfullConnectionAttemptsCount == SuccessfullConnectionAttemptsCount)
               && (other.DroppedNotificationsCount == DroppedNotificationsCount);
    };
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain

#endif  // CONNECTIONS_COUNTERS_VALUE_HPP