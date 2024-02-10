#pragma once
/**
 * @file
 * @brief     This file contains the definition of the HostSensorData class and its functionality.
 */
#include "common/sensor_data/SensorData.hpp"
#include "common/utils/CPP/optional/Optional.hpp"
#include <unordered_map>
#include "rapidjson/document.h"

namespace brain
{
namespace sensor_data
{
/**
 * @class   HostSensorData
 * @brief   class which holds the data of Host event
 */
class HostSensorData : public common::sensor_data::SensorData
{
public:

    enum class HostSensorProperties : uint8_t
    {
        TIMESTAMP = 0,   
        ID,
        DOMAIN_TYPE,
        SENSOR_TYPE,
        MISSING_ALIVE_SIG,
        APP_UNEXP,
        AUTH_ERROR,
        FAILED_SGN1,
        CPU_ERRORS,
        FAILED_SGN2
    };

    /**
     * @brief   Ctor
     * @param   rapidjson::Value const& parsedJson - json to build sd from
     * @param   bool& success - true for success, otherwise false.
     */
    HostSensorData(rapidjson::Value const& parsedJson, bool& success);

    /**
     * @brief   Ctor
     */
    HostSensorData() = default;

    /**
     * @brief   Fill SD data from json.
     * @param   rapidjson::Value const& parsedJson - json to fill sd from
     * @return  bool - true for success otherwise false.
     */
    bool FillFromJson(rapidjson::Value const& incidentJson);

    /**
    * @brief   Get the timestamp.
    * @return  const uint64_t& - The timestamp.
    */
    inline uint64_t const & GetTimestamp() const noexcept
    {
        return m_timestamp;
    };

    /**
    * @brief   Set the timestamp.
    * @param   uint64_t time - The time stamp to be set.
    */
    inline void SetTimestamp(uint64_t time) noexcept
    {
        m_timestamp = time;
    };

    /**
    * @brief   Get the sensor ID.
    * @return  const std::string& - The sensor ID.
    */
    inline std::string const & GetID() const noexcept
    {
        return m_id;
    };

    /**
    * @brief   Set the sensor ID.
    * @param   std::string const& sensorID - the sensor ID to be set.
    */
    inline void SetID(std::string const& sensorID)
    {
        m_id = sensorID;
    };

    /**
    * @brief   Get the domain type.
    * @return  const cm::optional<std::string>& - The domain type.
    */
    inline cm::optional<std::string> const & GetDomainType() const noexcept
    {
        return m_domainType;
    };

    /**
    * @brief   Set the domain type.
    * @param   std::string const& domainType - the domain type to be set.
    */
    inline void SetDomainType(std::string const& domainType)
    {
        m_domainType = domainType;
    };

    /**
    * @brief   Get the sensor type.
    * @return  const cm::optional<std::string>& - The sensor type.
    */
    inline cm::optional<std::string> const & GetSensorType() const noexcept
    {
        return m_sensorType;
    };

    /**
    * @brief   Set the sensor type.
    * @param   std::string const& sensorType - the sensor type to be set.
    */
    inline void SetSensorType(std::string const& sensorType)
    {
        m_sensorType = sensorType;
    };

    /**
    * @brief   true if the UART Alive Signal is missing.
    * @return  const cm::optional<bool>& - true if the UART Alive Signal is missing.
    */
    inline cm::optional<bool> const & GetMissingAliveSig() const noexcept
    {
        return m_missingAliveSig;
    };

    /**
    * @brief   Set true if the UART Alive Signal is missing.
    * @param   bool missingAliveSig - true if the UART Alive Signal is missing.
    */
    inline void SetMissingAliveSig(bool missingAliveSig) noexcept
    {
        m_missingAliveSig = missingAliveSig;
    };

    /**
    * @brief   Get an unexpected application event.
    * @return  const cm::optional<std::string>& - the unexpected application event.
    */
    inline cm::optional<std::string> const & GetAppUnexp() const noexcept
    {
        return m_appUnexp;
    };

    /**
    * @brief   Set an unexpected application event.
    * @param   std::string const& inAppUnexp - the unexpected application event to be set.
    */
    inline void SetAppUnexp(std::string const& inAppUnexp)
    {
        m_appUnexp = inAppUnexp;
    };

    /**
    * @brief   true if an authentication error has been detected.
    * @return  const cm::optional<bool>& - true if an authentication error has been detected.
    */
    inline cm::optional<bool> const & GetAuthError() const noexcept
    {
        return m_authError;
    };

    /**
    * @brief   Set true if an authentication error has been detected.
    * @param   bool authError - true if an authentication error has been detected.
    */
    inline void SetAuthError(bool authError) noexcept
    {
        m_authError = authError;
    };

    /**
    * @brief   Get the failed Sgn1.
    * @return  const cm::optional<uint16_t>& - The failed Sgn1.
    */
    inline cm::optional<uint16_t> const & GetFailedSgn1() const noexcept
    {
        return m_failedSgn1;
    };

    /**
    * @brief   Set the failed Sgn1.
    * @param   uint16_t failedSgn1 - The failed Sgn1 to be set.
    */
    inline void SetFailedSgn1(uint16_t failedSgn1) noexcept
    {
        m_failedSgn1 = failedSgn1;
    };

    /**
    * @brief   Get the CPU Errors.
    * @return  const cm::optional<uint16_t>& - The CPU Errors.
    */
    inline cm::optional<uint16_t> const & GetCpuErrors() const noexcept
    {
        return m_cpuErrors;
    };

    /**
    * @brief   Set the CPU Errors.
    * @param   uint16_t cpuErrors - The CPU Errors to be set.
    */
    inline void SetCpuErrors(uint16_t cpuErrors) noexcept
    {
        m_cpuErrors = cpuErrors;
    };

    /**
    * @brief   Get the failed Sgn2.
    * @return  const cm::optional<uint16_t>& - The failed Sgn2.
    */
    inline cm::optional<uint16_t> const & GetFailedSgn2() const noexcept
    {
        return m_failedSgn2;
    };

    /**
    * @brief   Set the failed Sgn2.
    * @param   uint16_t failedSgn2 - The failed Sgn2 to be set.
    */
    inline void SetFailedSgn2(uint16_t failedSgn2) noexcept
    {
        m_failedSgn2 = failedSgn2;
    };

private:

    uint64_t                  m_timestamp;
    std::string               m_id;
    cm::optional<std::string> m_domainType;
    cm::optional<std::string> m_sensorType;
    cm::optional<bool>        m_missingAliveSig;
    cm::optional<std::string> m_appUnexp;
    cm::optional<bool>        m_authError;
    cm::optional<uint16_t>    m_failedSgn1;
    cm::optional<uint16_t>    m_cpuErrors;
    cm::optional<uint16_t>    m_failedSgn2;
    static std::unordered_map<std::string, HostSensorProperties> const s_properties;
};
} // namespace sensor_data
} // namespace brain
