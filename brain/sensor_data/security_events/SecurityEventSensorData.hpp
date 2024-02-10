/**
 * @file
 * @brief     This file contains the definition of the SecurityEventSensorData class and its functionality.
 */
#ifndef SECURITY_EVENT_SENSOR_DATA_HPP
#define SECURITY_EVENT_SENSOR_DATA_HPP
#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
    #include <sci/frontend/api/IEventHandlers.hpp>
    #include <sci/frontend/common/ReceivedSignal.hpp>
    #include <sci/frontend/common/ReceivedSignalGroup.hpp>
#endif
#include "autogen/gsep/SecurityEvents.hpp"
#include "vwg/services/security/idssecurityevent/idssecurityeventsmall/impl_type_securityeventstruct.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/impl_type_securityeventevent.h"
#include "common/sensor_data/SensorData.hpp"
#include "common/utils/logger/Logger.hpp"
#include "common/utils/CPP/optional/Optional.hpp"

namespace brain
{
namespace sensor_data
{

using brain::engines::security_events::SecurityEventTimestamp;
using brain::engines::security_events::SecurityEventFrame;

/**
 * @class   SomeIPSecurityEventSensorData
 * @brief   class which holds the data of security event
 */
class SecurityEventSensorData : public common::sensor_data::SensorData
{
public:
    using SecurityEventNormalDataType = ::vwg::services::security::idssecurityevent::idssecurityevent::SecurityEventEvent;
    using SecurityEventSmallDataType = ::vwg::services::security::idssecurityevent::idssecurityeventsmall::SecurityEventStruct;
    using SecurityEventStruct_eventFrame = vwg::services::security::idssecurityevent::idssecurityeventsmall::SecurityEventStruct_eventFrame;
    using SecurityEventStruct_timestamp = vwg::services::security::idssecurityevent::idssecurityeventsmall::SecurityEventStruct_timestamp;
    using SecurityEventStruct_contextData = vwg::services::security::idssecurityevent::idssecurityeventsmall::SecurityEventStruct_contextData;
	using SCISensorDataType = std::vector<uint64_t>;

    /**
     * @brief   Ctor
     * @param   SomeIPSecurityEventSensorData(SecurityEventNormalDataType const& securityEventData
     * @param   bool& success - true for success, otherwise false.
     */
    SecurityEventSensorData(SecurityEventNormalDataType const& securityEventData, bool& success);

    /**
     * @brief   Ctor
     * @param   SomeIPSecurityEventSensorData(SecurityEventSmallDataType const& securityEventData
     * @param   bool& success - true for success, otherwise false.
     */
    SecurityEventSensorData(SecurityEventSmallDataType const& securityEventData, bool& success);

#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
    /**
     * @brief   Ctor
     * @param   SomeIPSecurityEventSensorData(SCISensorDataType const& securityEventData
     * @param   bool& success - true for success, otherwise false.
     */
    SecurityEventSensorData(SCISensorDataType const& securityEventData, bool& success);
#endif
    /**
     * @brief   Ctor
     */
    SecurityEventSensorData() = default;

    /**
     * @brief   Get the timestamp in milliseconds.
     * @return  uint64_t - The timestamp.
     */
    inline uint64_t
    GetTimestamp() const noexcept
    {
        return m_timestamp;
    };

    /**
     * @brief   Get the autosar timestamp seconds.
     * @return  uint32_t - The timestamp seconds or 0 if the format is not Autosar.
     */
    inline uint32_t GetAutosarTimestampSeconds() const {
        return isAutosarTimestamp() ? m_securityEventTimestamp.autosar.seconds : 0U;
    }

    /**
     * @brief   Get the autosar timestamp nanoseconds.
     * @return  uint32_t - The timestamp nanoseconds or 0 if the format is not Autosar.
     */
    inline uint32_t GetAutosarTimestampNano() const {
        return isAutosarTimestamp() ? m_securityEventTimestamp.autosar.nano : 0U;
    }

    /**
     * @brief   Get the autosar timestamp source.
     * @return  uint32_t - The timestamp source or 0 if the format is not Autosar.
     */
    inline uint32_t GetAutosarTimestampSource() const {
        return isAutosarTimestamp() ? m_securityEventTimestamp.autosar.source : 0U;
    }

    /**
     * @brief   Get the autosar timestamp reserved.
     * @return  uint32_t - The timestamp reserved or 0 if the format is not Autosar.
     */
    inline uint32_t GetAutosarTimestampReserved() const {
        return isAutosarTimestamp() ? m_securityEventTimestamp.autosar.reserved : 0U;
    }

    /**
     * @brief   Get the security event identifier.
     * @return  uint16_t - the security event identifier
     */
    inline uint16_t
    GetEventId() const noexcept
    {
        return m_eventFrame.eventDefinitionId;
    }

    /**
     * @brief   Get the contextData.
     * @return  std::vector<uint8_t> const&
     */
    inline std::vector<uint8_t> const&
    GetContextData() const noexcept
    {
        return m_contextData;
    };

    /**
     * @brief   Get the event frame data.
     * @return  secutiry event frame - 64 bits containing event frame data
     */
    inline SecurityEventFrame
    GetEventFrame() const noexcept
    {
        return m_eventFrame;
    };

    /**
     * @brief   Get the sensor identifier.
     * @return  uint8_t - the security event identifier
     */
    inline uint8_t
    GetSensorId() const noexcept
    {
        return  m_eventFrame.sensorInstanceID;
    }

    /**
     * @brief   Get the IdsM instance identifier.
     * @return  uint16_t - the IdsM instance identifier
     */
    inline uint16_t
    GetIdsMId() const noexcept
    {
        return m_eventFrame.idsMInstanceID;
    }

    /**
     * @brief   Get the Count value.
     * @return  uint16_t - the Count value
     */
    inline uint16_t
    GetCount() const noexcept
    {
        return  m_eventFrame.count;
    }

    /**
     * @brief   Deferred processing of ContextData
     * @return  bool - true for success, otherwise false.
     */
    template <typename EVENT_STRUCT>
    EVENT_STRUCT const*
    decodeContextData()
    {
        const bool isSacidTag{common::sensor_data::SensorDataTag::SD_SACID_CAN_EVENT == m_tag};
        // sacid events have larger context data
        if (!isSacidTag && (m_contextData.size() > sizeof(EVENT_STRUCT)))
        {
            LOG_ERROR << "SomeIPSecurityEventSensorData - Event ID " << std::hex
                      << static_cast<uint32_t>(m_eventFrame.eventDefinitionId) << std::dec << ", idsMInstanceID "
                      << static_cast<uint32_t>(m_eventFrame.idsMInstanceID) << ", tag " << static_cast<uint32_t>(m_tag)
                      << " has an invalid contextData length " << m_contextData.size()
                      << ", expected: " << sizeof(EVENT_STRUCT) << LOG_NOOP;
            return nullptr;
        }
        else if (m_contextData.size() < sizeof(EVENT_STRUCT))
        {
            EVENT_STRUCT* event = reinterpret_cast<EVENT_STRUCT*>(const_cast<uint8_t*>(m_contextData.data()));
            if (!SECEV_hasValidSize(event, m_contextData.size()))
            {
                LOG_ERROR << "SomeIPSecurityEventSensorData - "
                          << "Event ID " << std::hex << static_cast<uint32_t>(m_eventFrame.eventDefinitionId)
                          << std::dec << ", idsMInstanceID " << static_cast<uint32_t>(m_eventFrame.idsMInstanceID)
                          << ", tag " << static_cast<uint32_t>(m_tag) << " has an invalid data length "
                          << m_contextData.size() << ", expected " << sizeof(EVENT_STRUCT) << LOG_NOOP;
                return nullptr;
            }

            LOG_DEBUG << "SomeIPSecurityEventSensorData resize "
                      << "event ID " << std::hex << static_cast<uint32_t>(m_eventFrame.eventDefinitionId) << std::dec
                      << ", idsMInstanceID " << static_cast<uint32_t>(m_eventFrame.idsMInstanceID) << ", tag "
                      << static_cast<uint32_t>(m_tag) << " context data from " << m_contextData.size() << " to "
                      << sizeof(EVENT_STRUCT) << LOG_NOOP;

            m_contextData.resize(sizeof(EVENT_STRUCT), 0U);
        }

        // Cast ContextData to auto-generated struct
        EVENT_STRUCT* event = reinterpret_cast<EVENT_STRUCT*>(const_cast<uint8_t*>(m_contextData.data()));

        // Verifies that contextData isn't already decoded
        if (!m_isContextDataDecoded)
        {
            // Deserialize using byte and bit swapping
            SECEV_Convert(event, m_useBitSwap);
            m_isContextDataDecoded = true;
        }

        return event;
    }

private:
    inline bool isAutosarTimestamp() const {
        return m_securityEventTimestamp.source_AutoSAR == m_securityEventTimestamp.inspection.source;
    }
    bool decodeEvent(SecurityEventStruct_eventFrame         eventFrame,
                     SecurityEventStruct_timestamp          timestamp,
                     SecurityEventStruct_contextData const& contextData);
    bool extractEventFrame(SecurityEventStruct_eventFrame eventFrame);
    void extractTimestamp(SecurityEventStruct_timestamp timestamp);

    bool extractEventFrame(SCISensorDataType const& securityEventData);
    bool extractTimestamp(SCISensorDataType const& securityEventData);
    bool extractContextData(SCISensorDataType const& securityEventData);
    void printConModLog(bool success);

    SecurityEventFrame                      m_eventFrame{};
    uint64_t                                m_timestamp{};
    SecurityEventTimestamp                  m_securityEventTimestamp{};
    std::vector<uint8_t>                    m_contextData;
    bool                                    m_isContextDataDecoded{};
    bool                                    m_useBitSwap = true;
};

}  // namespace sensor_data
}  // namespace brain

#endif  // SECURITY_EVENT_SENSOR_DATA_HPP
