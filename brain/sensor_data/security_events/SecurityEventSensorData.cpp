#include "ara/stdtypes/impl_type_string.h"
#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
#include "brain/communicator/sci/SciCommunicator.hpp"
#endif
#include "autogen/gsep/ParsedEventIds.hpp"
#include "brain/utils/UtilsConstants.hpp"
#include "common/utils/logger/Logger.hpp"
#include "common/utils/os/time/Time.hpp"
#include "common/utils/typeCasting/TypeCasting.hpp"

#include "SecurityEventSensorData.hpp" // implemented

using brain::sensor_data::SecurityEventSensorData;
using brain::engines::security_events::EventIds;
#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
using namespace brain::brain_communicator::sci_communicator;
#endif
using namespace brain::engines::security_events;


SecurityEventSensorData::SecurityEventSensorData(SecurityEventNormalDataType const& securityEventData, bool& success)
  : SensorData()
{
    success = false;
    SetTag(common::sensor_data::SensorDataTag::SD_SECURITY_EVENT);

    if (!securityEventData.element.eventFrame.has_value())
    {
        LOG_ERROR << "eventFrame does not exist in the Security Event, can't extract event id" << LOG_NOOP;
        return;
    }

    if (!securityEventData.element.timestamp.has_value())
    {
        LOG_ERROR << "timestamp does not exist in the Security Event" << LOG_NOOP;
        m_timestamp = common::Time::GetCurrentTimeMilliSec();
    }

    if (!securityEventData.element.contextData.has_value())
    {
        LOG_ERROR << "contextData does not exist in the Security Event" << LOG_NOOP;
        return;
    }

    success = decodeEvent(*(securityEventData.element.eventFrame),
                          *(securityEventData.element.timestamp),
                          *(securityEventData.element.contextData));

    static constexpr uint16_t INTELLIGENT_EVENT_ID = 0xEA00;
    if (INTELLIGENT_EVENT_ID == m_eventFrame.eventDefinitionId)
    {
        SetTag(common::sensor_data::SensorDataTag::SD_INTELLIGENT_SENSOR);
    }

    printConModLog(success);

    success = true;
}

SecurityEventSensorData::SecurityEventSensorData(SecurityEventSmallDataType const& securityEventData, bool& success)
  : SensorData(),
    m_useBitSwap(false)
{
    success = false;
    SetTag(common::sensor_data::SensorDataTag::SD_SECURITY_EVENT);

    if (!securityEventData.timestamp.has_value())
    {
        LOG_DEBUG << "timestamp does not exist in the Security Event Small" << LOG_NOOP;
        m_timestamp = common::Time::GetCurrentTimeMilliSec();
    }

    if (!securityEventData.contextData.has_value())
    {
        LOG_ERROR << "contextData does not exist in the Security Event" << LOG_NOOP;
        return;
    }

    success
        = decodeEvent(securityEventData.eventFrame, *(securityEventData.timestamp), *(securityEventData.contextData));

    printConModLog(success);
}

#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
SecurityEventSensorData::SecurityEventSensorData(SCISensorDataType const& securityEventData, bool& success)
{
    SetTag(common::sensor_data::SensorDataTag::SD_SACID_CAN_EVENT);

    // make sure the event data contains all the signals
    success = securityEventData.size() > SignalIndexes::kContextData6;
    if (success)
    {
        success = extractTimestamp(securityEventData);
        success = success && extractEventFrame(securityEventData);
        success = success && extractContextData(securityEventData);
        printConModLog(success);
    }
}
#endif
bool
SecurityEventSensorData::decodeEvent(SecurityEventStruct_eventFrame         eventFrame,
                                     SecurityEventStruct_timestamp          timestamp,
                                     SecurityEventStruct_contextData const& contextData)
{
    // Extract EventFrame
    if (!extractEventFrame(eventFrame))
    {
        LOG_ERROR << "Could not extract event frame" << LOG_NOOP;
        return false;
    }

    // Extract Timestamp
    extractTimestamp(timestamp);

    // Extract ContextData
    m_contextData.clear();
    copy(contextData.begin(), contextData.end(), back_inserter(m_contextData));
    LOG_DEBUG << "extractEventFrame: contextData has size " << m_contextData.size() << LOG_NOOP;

    return true;
}

bool SecurityEventSensorData::extractEventFrame(SecurityEventStruct_eventFrame eventFrame)
{
    LOG_VERBOSE << "extractEventFrame: Event Frame has value" << LOG_NOOP;
    if (eventFrame.size() != sizeof(SecurityEventFrame))
    {
        LOG_WARNING << "IDSSecurityEvent eventFrame has invalid size: " << eventFrame.size() << LOG_NOOP;
        return false;
    }
    LOG_DEBUG << "extractEventFrame: Event Frame has size " << eventFrame.size() << LOG_NOOP;

    // Deserializing eventFrame
    m_eventFrame = *reinterpret_cast<SecurityEventFrame const*>(eventFrame.data());
    if (!m_useBitSwap)
    {
        uint8_t       val  = *(reinterpret_cast<uint8_t*>(&m_eventFrame));
        const uint8_t data = static_cast<uint8_t>(
            (val & 0xF0) | static_cast<uint8_t>((val & 0x08) >> 3) | static_cast<uint8_t>((val & 0x04) >> 1)
            | static_cast<uint8_t>((val & 0x02) << 1) | static_cast<uint8_t>((val & 0x01) << 3));
        *(reinterpret_cast<uint8_t*>(&m_eventFrame)) = data;
    }
    brain::engines::security_events::SECEV_Convert(&m_eventFrame, m_useBitSwap);

    return true;
}

void SecurityEventSensorData::extractTimestamp(SecurityEventStruct_timestamp timestamp)
{
    if (0U == m_eventFrame.protocolHeaderTimestamp)
    {
        LOG_DEBUG << "No timestamp detected, skipping extractTimestamp" << LOG_NOOP;
        m_timestamp = common::Time::GetCurrentTimeMilliSec();
        return;
    }
    LOG_VERBOSE << "extractEventFrame: Timestamp has value" << LOG_NOOP;

    // Deserializes timestamp
    std::vector<uint8_t>    timestampData(timestamp.begin(), timestamp.end());
    m_securityEventTimestamp = *reinterpret_cast<union SecurityEventTimestamp*>(timestampData.data());
    SECEV_Convert(&m_securityEventTimestamp, m_useBitSwap);
    LOG_DEBUG << "After SECEV_Convert Timestamp source: "
              << static_cast<uint8_t>(m_securityEventTimestamp.inspection.source) << LOG_NOOP;

    if (isAutosarTimestamp())
    {
        LOG_DEBUG << "After SECEV_Convert Timestamp(AutoSAR) "
                  << "nano: " << static_cast<uint32_t>(m_securityEventTimestamp.autosar.nano)
                  << ", second: " << static_cast<uint64_t>(m_securityEventTimestamp.autosar.seconds) << LOG_NOOP;

        m_timestamp = (common::S_TO_MS(static_cast<uint64_t>(m_securityEventTimestamp.autosar.seconds)))
                      + (static_cast<uint64_t>(m_securityEventTimestamp.autosar.nano) / common::NANOSECONDS_IN_MILLISECOND);
    }
    else
    {
        LOG_DEBUG << "After SECEV_Convert Timestamp(OEM) milis: "
                  << static_cast<uint64_t>(m_securityEventTimestamp.oem.milis) << LOG_NOOP;
        m_timestamp = m_securityEventTimestamp.oem.milis;
    }
}
#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
bool SecurityEventSensorData::extractEventFrame(SCISensorDataType const& securityEventData)
{

    m_eventFrame = *reinterpret_cast<struct SecurityEventFrame const*>(&securityEventData[SignalIndexes::kEventFrame]);
    return true;
}

bool SecurityEventSensorData::extractTimestamp(SCISensorDataType const& securityEventData)
{
    m_timestamp = securityEventData[SignalIndexes::kTimestamp];
    return true;
}

bool SecurityEventSensorData::extractContextData(SCISensorDataType const& securityEventData)
{
    m_contextData = common::VectorOfUint64ToUint8({securityEventData[SignalIndexes::kContextData1],
                                                   securityEventData[SignalIndexes::kContextData2],
                                                   securityEventData[SignalIndexes::kContextData3],
                                                   securityEventData[SignalIndexes::kContextData4],
                                                   securityEventData[SignalIndexes::kContextData5],
                                                   securityEventData[SignalIndexes::kContextData6]});
    return true;
}
#endif

void
SecurityEventSensorData::printConModLog(bool success)
{
    // this is used to create the requested logs containing the eventId and the event name
    static std::unordered_map<int, std::string> const EventIdToString{
        {0x9700, "ETHERNET_COMMUNICATION_INTERRUPTION"},  // IDS-08 - Ethernet Service Interruption Counters Table
        {0x9701, "DATA_DEFINITION_L3_CHECK_FAILED"},      // IDS-09 - OSI Layer 3 check failed
        {0x9702, "SWITCH_DATAFLOW_STATISTICS"},           // IDS-10 - See statistics table on tab"ETH_Switch_Statistics"
        {0x9703, "DETECTED_UNALLOWED_L3_PROTOCOL"},  // IDS-11 - Unallowed layer 3 protocol (e.g.IPv4) detected. On OSI
                                                     // layer 3 only IPv6 shall be used.
        {0x9704, "DETECTED_UNALLOWED_L4_PROTOCOL"},  // IDS-12 - Unallowed layer 4 protocols detected. On OSI layer 4
                                                     // only TCP, UDP and ICMPv6 shall be used.
        {0x9707, "UNUSED_PORT_CONNECTION_REQUEST"},  // IDS-15 - Connection Request to an Unused Port
        {0x9709, "MESSAGE_MAX_SIZE_EXCEEDED"},  // IDS-17 - Detect message exceeding maximum ECU packet size, including
                                                // size after reassembled fragment
        {0x970F, "MESSAGE_BURST"},  // IDS-23 - Detect message bursts of messages in a defined period of time.
        {0x002C, "SECOC_SEV_MAC_VERIFICATION_FAILED"},  // IDS-25 - MAC verification of a received PDU failed
        {0x002D, "SECOC_SEV_FRESHNESS_NOT_AVAILABLE"},  // IDS-26 - Failed to get freshness value from FvM.  Freshnes
                                                        // Value Manager. The Software Component Freshness Value Manager
                                                        // (FVM) shall provide the  Freshness Value (FV) to SecOC.
        {0x000B, "TCPIP_SEV_DROP_INV_PORT_TCP"},        // IDS-29 - Invalid TCP Destination Port Counters Table
        {0x000C, "TCPIP_SEV_DROP_INV_PORT_UDP"},  // IDS-30 - Dropped UDP packet because of invalid destination UDP-Port
        {0x000D, "TCPIP_SEV_DROP_INV_IPV4_ADDR"},  // IDS-31 - Dropped datagram because of invalid IPV4 address
        {0x000E, "TCPIP_SEV_DROP_INV_IPV6_ADDR"},  // IDS-32 - Dropped datagram because of invalid IPV6 address
        {0x000A,
         "TCPIP_SEV_ARP_IP_ADDR_CONFLICT"},    // IDS-28 - Received local IP address in ARP reply for different MAC.
        {0x0005, "SOAD_SEV_DROP_PDU_RX_TCP"},  // IDS-33 - SoAd dropped a PDU. The PDU violates stack configuration and
                                               // was received via a TCP socket.
        {0x0006, "SOAD_SEV_DROP_PDU_RX_UDP"},  // IDS-34 - SoAd dropped a PDU. The PDU violates stack configuration and
                                               // was received via a UDP socket.
        {0x0007, "SOAD_SEV_DROP_MSG_RX_UDP_LENGTH"},   // IDS-35 - SoAd dropped a message rx via UDP socket. The
                                                       // violation relates to the length of the PDUs compared to the
                                                       // overall length of the message.
        {0x0008, "SOAD_SEV_DROP_MSG_RX_UDP_SOCKET"},   // IDS-36 - SoAd received a UDP message which violates stack
                                                       // configuration and was dropped. No suitable socket connection
                                                       // matching to configuration was found.
        {0x0009, "SOAD_SEV_REJECTED_TCP_CONNECTION"},  // IDS-37 - SoAd rejected a TCP connection. The connection
                                                       // request violates stack configuration.
        {0x000F, "ETHIF_SEV_DROP_UNKNOWN_ETHERTYPE"},  // IDS-38 - An ethernet datagram was dropped because the
                                                       // Ethertype in not known.
        {0x0010,
         "ETHIF_SEV_DROP_VLAN_DOUBLE_TAG"},  // IDS-39 - An ethernet datagram was dropped due to double VLAN tag.
        {0x0011,
         "ETHIF_SEV_DROP_INV_VLAN"},  // IDS-40 - An ethernet datagram was dropped due to an invalid CrtlIdx/VLAN.
        {0x0012, "ETHIF_SEV_DROP_ETH_MAC_COLLISIONN"},  // IDS-41 - Ethernet datagram was dropped because local MAC was
                                                        // same as source MAC in an incoming frame.
        {0x9711, "LOCAL_FW_LOGS_FORWARDED_PACKAGE_STATISTICS"},  // IDS-42 - Local FW Forwarded Package Statistics
        {0x9712, "LOCAL_FW_BLOCKED_CONNECTIONS_DETECTED"},       // IDS-43 - Local FW Blocked Connections Detected
        {0xD002, "UNEXPECTED_SERVICE_REGISTRY_DETECTED"},  // IDS-45 - Every service registry in the SE must notify the
                                                           // IDS Core of every unexpected registration request.
        {0xD004, "SERVICE_LIST_CHANGE"},  // IDS-47 - Online ECU's have a specific set of services they may connect to
                                          // in the backend.
        {0xD005,
         "AUTHENTICATION_ERRORS_REPORTS"},  // IDS-48 - The IDS sensor must report each event where a car-internal
                                            // client attempted to connect to sSOA protected ressource without providing
                                            // valid credentials/token (authentication failure).
        {0xD006, "FAILED_SERVICE_REQUEST_DETECTED"},  // IDS-49 - Every service registry in the SE must notifiy the IDS
                                                      // Core of every failed service discovery request.
        {0xD007, "PROCESS_CRASH_NOTIFICATION"},       // IDS-50 - Process Crash Notification
        {0xD008, "SMS_LOG_REPORTS"},     // IDS-51 - The IDS sensor must log all SMS sent to/from the vehicle.
        {0xD700, "NAT_UPDATE_REPORTS"},  // IDS-52 - The IDS shall maintain a shadow NAT table which shall be updated
                                         // with every arrival of 0xD700 (NAT_UPDATE_REPORTS) Security Event.
        {0xD701, "RESOURCE_CONSUMPTION_NOTIFICATION"},  // IDS-58 - Resource Consumption Notification
        {0xD702, "PROCESS_START_STOP_NOTIFICATION"},    // IDS-59 - Every virtual machine operating system or operating
                                                      // system in the SE must send process start/stop notifications to
                                                      // the IDS Core every time an unknown process starts or stops.
        {0xD009, "SECURE_BOOT_FAILED"},  // IDS-61 - Secure boot failed (signature verification) Once you do a secure
                                         // boot, there is an indication if it failed.
        {0xD00B, "SW_VERSION_UPDATE_MECHANISM_CHANGES"},  // IDS-63 - SW Version Update Mechanism Change
        {0xD703, "VM_CRITICAL_ERROR"},  // IDS-64 - The SE VM/Hypervisor must send a notification of any critical errors
                                        // encountered (guest OS boot failure, image validation failure, virtual machine
                                        // reset, etc.) to the IDS Core.
        {0xD704, "ECU_MODE_CHANGE"},    // IDS-65 - If a ECU changes ist state from"normal operation mode" to another
                                        // state (e.g. Safe State, Recovery mode etc), the IDS Core should be notified.
        {0xD705, "APN_CONFIGURATION_CHANGE_REPORTS"},  // IDS-66 - APN Configuration Change Report
        {0xD706, "OS_LOG_REPORTS"},                    // IDS-67 - OS Log Reports
        {0xD707, "MAC_AUDIT_REPORTS"},  // IDS-68 - SMACK (Simplified Mandatory Access Control Kernel) audit records (if
                                        // available) must be reported. There is also SE LINUX ->Mandatory Access
                                        // Control mechanism All mechanisms are meant here. What we want to see here are
                                        // the error logs from the security mechanism.
        {0x002E,
         "IDSM_INTERNAL_EVENT_NO_EVENT_BUFFER_AVAILABLE"},  // IDS-69 - A SEv cannot be handled because there are no
                                                            // more event buffers available to process the event.
        {0x002F, "IDSM_INTERNAL_EVENT_NO_CONTEXT_DATA_BUFFER_AVAILABLE"},  // IDS-70 - The context data of an incoming
                                                                           // event cannot be stored because there are
                                                                           // no more context data buffers available.
        {0x0030, "IDSM_INTERNAL_EVENT_TRAFFIC_LIMITATION_EXCEEDED"},       // IDS-71 - The current traffic exceeds a
                                                                           // configured traffic limitation.
        {0xD708, "ERROR_EVENT_LOGGING_MONITORING"},  // IDS-72 - Error and event logging Monitoring (critical errors,
                                                     // application crashes, memory access denials etc).
        {0xD709, "SECURITY_ERROR_EVENT_LOGGING_MONITORING"},  // IDS-73 - Error and event logging Monitoring (security
                                                              // related events, file access).
        {0xD70A,
         "ERROR_EVENT_LOGGING_USER_LOGIN"},  // IDS-74 - Relevant log files and error logging created by virtual machine
                                             // logging mechanisms must be sent to the IDS Core frequently.
        {0xD00D, "ACCESS_CONTROL_CONFIGURATION_CHANGE"},  // IDS-75 - Access control configuration change.
        {0xD00E, "VKMS_NO_KEYS_AVAILABLE"},               // IDS-76 - VKMS key storage is empty.
        {0xD00F, "VKMS_DLC_VERIFICATION_FAILED"},         // IDS-77 - DLC signature is not valid, or invalid content.
        {0xD010, "VKMS_UNKNOWN_KEY_REQUESTED"},  // IDS-78 - An application requested a key not available in VKMS.
        {0xD011, "VKMS_VIN_VALIDATION_FAILED"},  // IDS-79 - The VIN in DLC does not match to the vehicle VIN.
        {0x0017,
         "DIAG_SEV_WRITE_INVALID_DATA"},  // IDS-88 - Tester writes invalid data with service WriteDataBy Identifier.
        {0x0018, "DIAG_SEV_SECURITY_ACCESS_DENIED"},  // IDS-89 - Tester has send an diagnostic request without meeting
                                                      // the servers security level requirements for that service. NRC
                                                      // 0x33 (securityAccessDenied) was returned.
        {0x0019, "DIAG_SEV_COMMUNICATION_CONTROL_SWITCHED_OFF"},  // IDS-90 - ECU communication was switched off with
                                                                  // service CommunicationControl.
        {0x001A,
         "DIAG_SEV_SERVICE_NOT_SUPPORTED"},  // IDS-91 - A diagnostic service was requested that is not supported ornot
                                             // supported in the active session. NRC 0x11 (serviceNot Supported) or NRC
                                             // 0x7F (serviceNotSupportedInActive Session) was returned.
        {0x001B, "DIAG_SEV_SUBFUNCTION_NOT_SUPPORTED"},  // IDS-92 - A subfunction of a diagnostic service was requested
                                                         // that is not supported for the requested service.
        {0x001C,
         "DIAG_SEV_INCORRECT_MESSAGE_LENGTH_OR_FORMAT"},  // IDS-93 - Received request message does not match the
                                                          // specified length or the format of the parameters is
                                                          // different from the specified ones for that service. NRC
                                                          // 0x13 (incorrect MessageLengthOrInvalidFormat) was returned.
        {0x001D, "DIAG_SEV_REQUEST_SEQUENCE_ERROR"},      // IDS-94 - A diagnostic service was received in the wrong
                                                      // sequence order. NRC 0x24 (requestSequenceError) was returned.
        {0x001E, "DIAG_SEV_REQUEST_OUT_OF_RANGE"},  // IDS-95 - A diagnsotic request with a parameter that is our range
                                                    // of the allowed bounds was received. A NRC 0x31 (requestOut
                                                    // OfRange) was returned.
        {0x001F, "DIAG_SEV_REQUESTED_ACTIONS_REQUIRES_AUTHENTICATION"},  // IDS-96 - A diagnostic request was received
                                                                         // while the required authentication to
                                                                         // executie this service is not given. NRC 0x34
                                                                         // (authenticationRequired) was returned.
        {0x0020,
         "DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED"},  // IDS-97 - Security Access failed and the number of
                                                                   // invalid attempts has been exceeded. NRC 0x36
                                                                   // (exceedNumberOf Attempts) was returned. Here the
                                                                   // counters should be for consecuritve attempts and
                                                                   // reset after driving cycle. Not a global counter.
        {0x0021, "DIAG_SEV_SECURITY_ACCESS_INVALID_KEY"},  // IDS-98 - Security Access failed because the tester has
                                                           // send aninvalid key to the server. An NRC 0x35 (invalidKey)
                                                           // was returned.
        {0x0022,
         "DIAG_SEV_SECURITY_ACCESS_REQUIRED_TIME_DELAY_NOT_EXPIRED"},  // IDS-99 - A further attempt to unlock the ECU
                                                                       // was taken before the delay time had expired.
                                                                       // NRC 0x37 (requiredTimeDelayNot Expired) was
                                                                       // sent.
        {0x0023,
         "DIAG_SEV_NUMBER_OF_FAILED_AUTHENTICATION_ATTEMPTS_EXCEEDED"},  // IDS-100 - Number of failed authentification
                                                                         // attempts - OEM specific.
        {0x0024,
         "DIAG_SEV_CERTIFICATE_FAILURE"},  // IDS-101 - The tester tried an authentication with an invalid certficate.
        {0x0025, "DIAG_SEV_ECU_UNLOCK_SUCCESSFUL"},  // IDS-102 - Successful unlocked the ECU (via Security Access $27),
                                                     // per Level.
        {0x0026, "DIAG_SEV_AUTHENTICATION_SUCCESSFUL"},  // IDS-103 - Succesfully authenticated (via Authentication $29)
        {0x0027, "DIAG_SEV_CLEAR_DTC_SUCCESSFUL"},       // IDS-104 - DTC information has been cleared by SID 0x14 Clear
                                                         // DTCInformation
        {0x0028, "DIAG_SEV_ECU_RESET"},                  // IDS-105 - ECU had been reset by SID 0x11 ResetECU
        {0x0029, "DIAG_SEV_WRITE_DATA"},  // IDS-106 - Diagnostic data identifier have been written by SID 0x2E.   Only
                                          // for sucessfull written data- Not for NRC 0x31
        {0x002A,
         "DIAG_SEV_REQUEST_DOWNLOAD"},  // IDS-107 - DTC setting switched off with service 0x85 (Control DTCSetting).
        {0x002B, "DIAG_SEV_DTC_SETTING_SWITCHED_OFF"},  // IDS-108 - A diagnsotic data download sequence was requested
                                                        // with SID 0x34.
        {0xD012, "CRYPTOGRAPHIC_LIB_FAILURES_NOTIFICATION"},      // IDS-109 - Cryptographic Lib Failures Notification
        {0xD013, "CONFIGURATION_FILE_DISCREPANCY_NOTIFICATION"},  // IDS-110 - Periodic check of the 'configuration
                                                                  // files" (instructions, directives, commands) must be
                                                                  // included in the host-based sensor setup.
        {0xD015, "TRUSTED_APPLICATION_INVOCATION"},  // IDS-112 - The SE must inform the IDS Core of any of any
                                                     // invocation of a Trusted Application (TEE Domain).
        {0xE900, "EXTERNAL_CONNECTION_INTERFACE_SUCCESSFUL"},    // IDS-113 - Successful wireless connections.
        {0xE901, "EXTERNAL_CONNECTION_INTERFACE_UNSUCCESSFUL"},  // IDS-114 - External Connection Interface Unsuccessful
        {0xE902,
         "NEW_BINDING_INTERFACE_NOTIFICATION"},  // IDS-115 - New bindings of applications/processes to any wireless
                                                 // interface, including bindings performed during system start-up.
        {0xE903, "EXTERNAL_INTERFACES_USAGE_STATISTICS"},  // IDS-116 - External interfaces usage statistics
        {0xE905, "EXTERNAL_DATA_STORAGE_CONNECTION"},      // IDS-118 - External Data Storage Connection
        {0xE907, "EXTERNAL_NEW_HW_CONNECTION"},            // IDS-120 - external new HW connection
        {0xE908, "EXTERNAL_SOURCES_FILE_DATA_STREAM"},  // IDS-121 - File or data stream received from external sources.
        {0xE701, "DIAGNOSTIC_DATA_SET_DOWNLOAD"},       // IDS-122 - Diagnostic Data Set Download
        {0xD70D, "SW_VERIFICATION_FAILURE"},  // IDS-125 - Failure in the method used to verify the authenticity of a
                                              // piece of SW.
        {0xD017, "VKMS_KEY_CHANGE"},          // IDS-126 - VKMS Key Change
        {0xD016, "VTTL_REGISTRY_CHANGE_REPORTS"},  // IDS-127 - VTTL Registry Change Reports
        {0xD70E, "CONTROL_MODULE_ERROR"},  // IDS-130 - This Security Event will trigger when one Contorl Module error
                                           // is activated. If an ECU has access to the DEM or the DTC Setting logic, it
                                           // will be triggered once a Control module related DTC is set to "active".
                                           // Normally use for RAM Errors
        {0x8000, "KEEP_ALIVE_MESSAGE"},  // IDS-131 - Keep-alive notification in order to validate sensor functionality

        // Intelligent event id
        {0xEA00, "INTELLIGENT_EVENT_ID"}};

    if (success)
    {
        std::string const& eventName{(0 < EventIdToString.count(m_eventFrame.eventDefinitionId))
                                         ? EventIdToString.at(m_eventFrame.eventDefinitionId)
                                         : "unknown"};
        LOG_DEBUG << static_cast<uint32_t>(m_eventFrame.idsMInstanceID) << ": " << eventName << " " << std::hex
                  << static_cast<uint32_t>(m_eventFrame.eventDefinitionId) << LOG_NOOP;
    }
}