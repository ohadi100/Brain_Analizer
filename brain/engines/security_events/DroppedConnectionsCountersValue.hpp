/**
 * @file
 * @brief     This file contains the definition of the DroppedConnectionsCountersValue.
 */
#ifndef DROPPED_CONNECTIONS_COUNTERS_VALUE_HPP
#define DROPPED_CONNECTIONS_COUNTERS_VALUE_HPP

#include <stdint.h>

namespace brain
{
namespace engines
{
namespace security_events
{

class DroppedConnectionsCountersValue final
{
public:
    /**
     * @brief Construct
     */
    DroppedConnectionsCountersValue() = default;

    /**
     * @brief Constructs ConnectionsCountersValue strucutre
     */
    DroppedConnectionsCountersValue(uint32_t droppedNotificationsCount, uint32_t droppedPackagesCount)
      : DroppedNotificationsCount{droppedNotificationsCount}
      , DroppedPackagesCount{droppedPackagesCount} {};

    /**
     * @brief   Compare two DroppedConnectionsCountersValue objects
     * @param   DroppedConnectionsCountersValue other - the DroppedConnectionsCountersValue
     * object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(DroppedConnectionsCountersValue other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two DroppedConnectionsCountersValue objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   DroppedConnectionsCountersValue other - the DroppedConnectionsCountersValue
     * object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(DroppedConnectionsCountersValue other) const
    {
        return !isEqual(other);
    }

    uint32_t DroppedNotificationsCount{};
    uint32_t DroppedPackagesCount{};

protected:
    /**
     * @brief   copy the internal data
     * @param   DroppedConnectionsCountersValue other - the DroppedConnectionsCountersValue
     * object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(DroppedConnectionsCountersValue other) const
    {
        return (other.DroppedNotificationsCount == DroppedNotificationsCount)
               && (other.DroppedPackagesCount == DroppedPackagesCount);
    }
};


}  // namespace security_events
}  // namespace engines
}  // namespace brain

#endif  // DROPPED_CONNECTIONS_COUNTERS_VALUE_HPP