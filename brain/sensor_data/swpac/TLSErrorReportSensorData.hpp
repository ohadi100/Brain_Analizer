#pragma once
/**
 * @file
 * @brief     This file contains the definition of the TLSErrorReportSensorData class and its functionality.
 */
#include "common/sensor_data/SensorData.hpp"
#include "SwpacSensorDataBase.hpp"
#include "rapidjson/document.h"

namespace brain
{
namespace sensor_data
{
/**
 * @class   TLSErrorReportSensorData
 * @brief   class which holds the data of TLS Error Reporting event
 */
class TLSErrorReportSensorData : public common::sensor_data::SensorData,
                                 public SwpacSensorDataBase
{
public:
    using ConstraintId = brain::sensor_data::swpac::ConstraintId;

    enum class valueId : uint8_t
    {
        COMPONENTID_ID = 0,
        TIME_STAMP_ID,
        CLIENT_IP_ID,
        SERVER_IP_ID,
        CLIENT_PORT_ID,
        SERVER_PORT_ID,
        PROTOCOL_ID,
        FAILURE_REASON_ID,
        TLS_IDENTITY_ID,
    };

    enum class protocolId : uint16_t
    {
        UDP_ID = 0,
        TCP_ID = 1
    };

    /**
     * @brief   Ctor
     * @param   success - true for success, otherwise false.
     * @param   rapidjson::Value const& parsedJson - json to build sd from
     * @param   constraintId - constraint ID, used by the alert for limiting the string size
     */
    TLSErrorReportSensorData(bool& success,
                             rapidjson::Value const& parsedJson,
                             ConstraintId            constraintId = ConstraintId::TLS_ERROR_REPORT);

    /**
     * @brief   Ctor
     */
    TLSErrorReportSensorData() = default;

   /**
    * @brief   Fill SD data from json
    * @param   rapidjson::Value const& dataItems - dataItems is a part from the entire json incident
    * @return  bool - true for success otherwise false
    */
    bool FillFromJson(rapidjson::Value const& dataItems);


    /**
    * @brief   Get the component id
    * @return  const cm::optional<std::string>& - The component id.
    */
    inline cm::optional<std::string> const & GetComponentId() const noexcept
    {
        return m_componentId;
    };

   /**
    * @brief   Set the component id
    * @param   std::string const& componentId - The component id to be set.
    */
    inline void SetComponentId(std::string const& componentId)
    {
        m_componentId = componentId;
    };

     /**
     * @brief   Get the client ip
     * @return  const cm::optional<std::string>& - The client ip.
     */
    inline cm::optional<std::string> const & GetClientIp() const noexcept
    {
        return m_clientIp;
    };

    /**
     * @brief   Set the client ip
     * @param   std::string const& clientIp - The client ip to be set.
     */
    inline void SetClientIp(std::string const& clientIp)
    {
        m_clientIp = clientIp;
    };

    /**
     * @brief   Get the server ip
     * @return  const cm::optional<std::string>& - The server ip.
     */
    inline cm::optional<std::string> const & GetServerIp() const noexcept
    {
        return m_serverIp;
    };

    /**
     * @brief   Set the server ip
     * @param   std::string const& serverIp - The server ip to be set.
     */
    inline void SetServerIp(std::string const& serverIp)
    {
        m_serverIp = serverIp;
    };

    /**
     * @brief   Get the time stamp
     * @return  cm::optional<uint64_t> - The time stamp.
     */
    inline cm::optional<uint64_t> const & GetTimeStamp() const noexcept
    {
        return m_timeStamp;
    };

    /**
     * @brief   Set time stamp
     * @param   uint64_t timeStamp - The time stamp to be set.
     */
    inline void SetTimeStamp(uint64_t timeStamp) noexcept
    {
        m_timeStamp = timeStamp;
    };

    /**
	 * @brief   Get the client port
	 * @return  cm::optional<uint16_t> - The client port.
	 */
    inline cm::optional<uint16_t> const & GetClientPort() const noexcept
    {
        return m_clientPort;
    };

    /**
     * @brief   Set client port
     * @param   uint16_t clientPort - The client port to be set.
     */
    inline void SetClientPort(uint16_t clientPort) noexcept
    {
        m_clientPort = clientPort;
    };

    /**
	 * @brief   Get the server port
	 * @return  cm::optional<uint16_t> - The server port.
	 */
    inline cm::optional<uint16_t> const & GetServerPort() const noexcept
    {
        return m_serverPort;
    };

    /**
     * @brief   Set server port
     * @param   uint16_t serverPort - The server port to be set.
     */
    inline void SetServerPort(uint16_t serverPort) noexcept
    {
        m_serverPort = serverPort;
    };
    
    /**
     * @brief   Get the protocol
     * @return  cm::optional<uint16_t> - The protocol.
     */
    inline cm::optional<uint16_t> const & GetProtocol() const noexcept
    {
        return m_protocol;
    };

    /**
	 * @brief   Set protocol
	 * @param   uint16_t protocol - The protocol to be set.
	 */
    inline void SetProtocol(uint16_t protocol) noexcept
    {
        m_protocol = protocol;
    };

    /**
	 * @brief   Get the failure reason
	 * @return  cm::optional<int32_t> - The failure reason.
	 */
    inline cm::optional<int32_t> const & GetFailureReason() const noexcept
    {
        return m_failureReason;
    };

    /**
     * @brief   Set failure reason
     * @param   int32_t failureReason - The failure reason to be set.
     */
    inline void SetFailureReason(int32_t failureReason) noexcept
    {
        m_failureReason = failureReason;
    };


    /**
    * @brief   Get the tls identity
    * @return  const cm::optional<std::string>& - The tls identity.
    */
    inline cm::optional<std::string> const & GetTlsIdentity() const noexcept
    {
        return m_tlsIdentity;
    };

    /**
     * @brief   Set the tls identity
     * @param   std::string const& tlsIdentity - The tls identity to be set.
     */
    inline void SetTlsIdentity(std::string const& tlsIdentity)
    {
        m_tlsIdentity = tlsIdentity;
    }

private:
    cm::optional<std::string>                    m_componentId;
    cm::optional<uint64_t>                       m_timeStamp;
    cm::optional<std::string>                    m_clientIp;
    cm::optional<std::string>                    m_serverIp;
    cm::optional<uint16_t>                       m_clientPort;
    cm::optional<uint16_t>                       m_serverPort;
    cm::optional<uint16_t>                       m_protocol;
    cm::optional<int32_t>                        m_failureReason;
    cm::optional<std::string>                    m_tlsIdentity;
};

} // namespace sensor_data
} // namespace brain
