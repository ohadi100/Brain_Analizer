/**
 * @file
 * @brief     This file contains the definition of the SwpacSensorDataBase class and its functionality.
 */

#ifndef SWPAC_SENSOR_DATA_BASE_HPP
#define SWPAC_SENSOR_DATA_BASE_HPP

#include <list>
#include <string>
#include "IncidentHelper.hpp"
#include "common/utils/CPP/Nonassignable.hpp"
#include "common/utils/CPP/optional/Optional.hpp"

namespace brain
{
namespace sensor_data
{

/**
 * @class   SwpacSensorDataBase
 * @brief   base class for SWPAC sensor data
 */
class SwpacSensorDataBase : public common::utils::Nonassignable
{
public:
    using ConstraintId = brain::sensor_data::swpac::ConstraintId;

    struct AlertData
    {
        uint64_t    timestampSecondsSinceEpoch{};
        // std::string constraintId;
        std::string reference;
        // each large string should be reported in a separate alert
        class StringDetail
        {
        public:
            StringDetail(uint32_t inSize, cm::optional<uint32_t> const& inId)
              : receivedStringSize(inSize)
              , id(inId)
            {
            }
            uint32_t               receivedStringSize{};
            cm::optional<uint32_t> id;
        };
        std::list<StringDetail> stringDetails;
    };

    /**
     * @brief   Constant for limiting the maximum size if the string type in a JSON object
     */
    static uint32_t MaximumSizeStringType;

    /**
     * @brief   Ctor
     * @param   constraintId - constraint ID, used in the alert data
     */
    explicit SwpacSensorDataBase(ConstraintId constraintId = ConstraintId::UNDEFINED_CONSTRAINTID)
    {
        m_constraintId = constraintId;
    }

    /**
     * @brief   Dtor
     */
    virtual ~SwpacSensorDataBase() = default;

    /**
     * @brief    default copy constructor
     */
    SwpacSensorDataBase(const SwpacSensorDataBase& other) = delete;

    /**
     * @brief    default move constructor
     */
    SwpacSensorDataBase(SwpacSensorDataBase&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    SwpacSensorDataBase& operator=(SwpacSensorDataBase const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    SwpacSensorDataBase& operator=(SwpacSensorDataBase&&) = delete;

    /**
     * @brief   Get the string size alert data
     * @return  AlertData const& - alert data
     */
    AlertData const&
    GetStringSizeAlertData() const
    {
        return m_alertData;
    }

    /**
     * @brief   Get the alert flag
     * @return  true iff an alert must be send
     */
    bool
    IsAlert() const
    {
        return !m_alertData.stringDetails.empty();
    }

    /**
     * @brief   Get the constraint id
     * @return  the dhm constraint id
     */
    constexpr swpac::ConstraintId
    GetConstraintId() const
    {
        return m_constraintId;
    }

    /**
     * @brief  Set the constraint id
     * @param  the dhm constraint id
     */
    void SetConstraintId(swpac::ConstraintId constraintId)
    {
        m_constraintId = constraintId;
    }

#ifndef TESTS
protected:
#endif
    /**
     * @brief   Truncates the input string and sets the alert flag if needed
     * @param   std::string const& value - input string to be truncated
     * @param   std::string const& reference - the "reference" value within the "dataItems" of the incident (used to
     * generate the alert)
     * @param   cm::optional<uint32_t> const& id - optional ID associated to the input string (used to generate the
     * alert)
     * @return  truncated string if needed, otherwise the unchanged string
     */
    std::string
    truncateStringSize(std::string const& value, std::string const& reference, cm::optional<uint32_t> const& id = {})
    {
        std::string out{value};
        if (value.size() > MaximumSizeStringType)
        {
            if (m_alertData.stringDetails.empty())
            {
                m_alertData.reference = reference;
            }
            m_alertData.stringDetails.emplace_back(static_cast<uint32_t>(value.size()), id);

            out.resize(MaximumSizeStringType);
        }
        return out;
    }

    /**
     * @brief    Set the alert timestamp expressed in seconds since epoch
     * @param    uint64_t timestamp
     * @return   none
     */
    void
    setAlertDataTimestamp(uint64_t timestamp)
    {
        m_alertData.timestampSecondsSinceEpoch = timestamp;
    }

    swpac::ConstraintId m_constraintId;

private:
    AlertData m_alertData{};
};

}  // namespace sensor_data
}  // namespace brain

#endif  // SWPAC_SENSOR_DATA_BASE_HPP
