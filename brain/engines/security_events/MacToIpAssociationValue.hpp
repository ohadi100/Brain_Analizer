/**
 * @file
 * @brief     This file contains the definition of the MacToIpAssociationValue.
 */
#ifndef MAC_TO_IP_ASSOCIATION_VALUE_HPP
#define MAC_TO_IP_ASSOCIATION_VALUE_HPP

#include <stdint.h>

namespace brain
{
namespace engines
{
namespace security_events
{

class MacToIpAssociationValue final
{
public:
    /**
     * @brief Construct
    */
    MacToIpAssociationValue() = default;

    /**
     * @brief Constructs ConnectionsCountersValue strucutre
     */
    MacToIpAssociationValue(uint32_t counter, uint64_t createdTimestamp, uint64_t updatedTimestamp)
      : Counter{counter}
      , CreatedTimestamp{createdTimestamp}
      , UpdatedTimestamp{updatedTimestamp} {};

    /**
     * @brief   Compare two MacToIpAssociationValue objects
     * @param   MacToIpAssociationValue const& other - the MacToIpAssociationValue
     * object to compare to
     * @return  bool - true if all fields are equal. false otherwise
     */
    bool
    operator==(MacToIpAssociationValue const& other) const
    {
        return isEqual(other);
    }

    /**
     * @brief   Compare two MacToIpAssociationValue objects, checks if different
     *          Objects are not equal, if any of the fields aren't equal
     * @param   MacToIpAssociationValue const& other - the MacToIpAssociationValue
     * object to compare to
     * @return  bool - true if any field is different. false otherwise
     */
    bool
    operator!=(MacToIpAssociationValue const& other) const
    {
        return !isEqual(other);
    }

    uint32_t Counter{};
    uint64_t CreatedTimestamp{};
    uint64_t UpdatedTimestamp{};

protected:
    /**
     * @brief   copy the internal data
     * @param   MacToIpAssociationValue const& other - the MacToIpAssociationValue
     * object to check if equal
     * @return  bool - true if all fields are equal, false otherwise
     */
    bool
    isEqual(MacToIpAssociationValue const& other) const
    {
        return (other.Counter == Counter) && (other.CreatedTimestamp == CreatedTimestamp)
               && (other.UpdatedTimestamp == UpdatedTimestamp);
    }
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain
#endif  // MAC_TO_IP_ASSOCIATION_VALUE_HPP