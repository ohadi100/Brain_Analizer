/**
 * @file
 * @brief     This file contains the definition of the KernelLogSensorData (Kernel Log Messages) class and its functionality.
 */
#ifndef KERNEL_LOG_SENSOR_DATA_HPP
#define KERNEL_LOG_SENSOR_DATA_HPP

#include "common/sensor_data/SensorData.hpp"
#include "SwpacSensorDataBase.hpp"
#include "rapidjson/document.h"

namespace brain
{
namespace sensor_data
{
/**
 * @class   KernelLogSensorData
 * @brief   class which holds the data of OS event of type KernelLog
 */
class KernelLogSensorData : public common::sensor_data::SensorData,
                            public SwpacSensorDataBase
{
public:
    using ConstraintId = brain::sensor_data::swpac::ConstraintId;

    enum class LogLevelValues : uint8_t
    {
        KERN_EMERG = 0,
        KERN_ALERT,
        KERN_CRIT,
        KERN_ERR,
        KERN_WARNING,
        KERN_NOTICE,
        KERN_INFO,
        KERN_DEBUG
    };

    enum class valueId : uint8_t
    {
        TIMESTAMP_ID = 0,
        MESSAGE_ID,
        LOG_LEVEL_ID,
        FACILITY_ID
    };

    /**
     * @brief   Ctor
     * @param   bool& success - true for success, otherwise false.
     * @param   rapidjson::Value const& parsedJson - json to build sd from
     * @param   std::string const& constraintId - constraint ID, used by the alert for limiting the string size
     */
    KernelLogSensorData(bool&                   success,
                        rapidjson::Value const& parsedJson,
                        ConstraintId            constraintId = ConstraintId::KERNEL_LOG_KERNEL_PANIC);

    /**
     * @brief   Ctor
     */
    KernelLogSensorData() = default;

    /**
     * @brief   Fill SD data from json
     * @param   rapidjson::Value const& dataItems - dataItems is a part from the entire json incident
     * @return  bool - true for success otherwise false
     */
    bool FillFromJson(rapidjson::Value const& dataItems);

    /**
    * @brief   Get the log message timestamp
    * @return  cm::optional<uint64_t> - The log message timestamp.
    */
    inline cm::optional<uint64_t> const & GetLogMessageTimestamp() const noexcept
    {
        return m_logMessageTimestamp;
    }

    /**
    * @brief   Set the log message timestamp
    * @param   uint64_t logMessageTimestamp - The log message timestamp to be set.
    */
    inline void SetLogMessageTimestamp(uint64_t logMessageTimestamp) noexcept
    {
        m_logMessageTimestamp = logMessageTimestamp;
    }

    /**
    * @brief   Get the log message message
    * @return  cm::optional<std::string> - The log message message.
    */
    inline cm::optional<std::string> const & GetLogMessageMessage() const noexcept
    {
        return m_logMessageMessage;
    }

    /**
    * @brief   Set the log message message
    * @param   std::string const& logMessageTimestamp - The log message message to be set.
    */
    inline void SetLogMessageMessage(std::string const& logMessageMessage)
    {
        m_logMessageMessage = logMessageMessage;
    }

    /**
    * @brief   Get the log message log level
    * @return  cm::optional<uint32_t> - The log message log level.
    */
    inline cm::optional<uint32_t> const & GetLogMessageLoglevel() const noexcept
    {
        return m_logMessageLoglevel;
    }

    /**
    * @brief   Set the log message log level
    * @param   uint32_t logMessageLoglevel - The log message log level to be set.
    */
    inline void SetLogMessageLoglevel(uint32_t logMessageLoglevel) noexcept
    {
        m_logMessageLoglevel = logMessageLoglevel;
    }

    /**
    * @brief   Get the log message facility
    * @return  cm::optional<uint32_t> - The log message facility.
    */
    inline cm::optional<uint32_t> const & GetLogMessageFacility() const noexcept
    {
        return m_logMessageFacility;
    }

    /**
    * @brief   Set the log message facility
    * @param   uint32_t logMessageFacility - The log message facility to be set.
    */
    inline void SetLogMessageFacility(uint32_t logMessageFacility) noexcept
    {
        m_logMessageFacility = logMessageFacility;
    }

private:
    bool fillLogMessageFromJson(rapidjson::Value const& incidentJson, std::string const& reference);

    cm::optional<uint64_t>                       m_logMessageTimestamp;
    cm::optional<std::string>                    m_logMessageMessage;
    cm::optional<uint32_t>                       m_logMessageLoglevel;
    cm::optional<uint32_t>                       m_logMessageFacility;
};

} // namespace sensor_data
} // namespace brain

#endif // KERNEL_LOG_SENSOR_DATA_HPP
