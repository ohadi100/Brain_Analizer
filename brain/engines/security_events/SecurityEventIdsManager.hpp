/**
 * @file
 *
 * @brief     This class manages the security events white and black lists.
 *
 * The SecurityEventIds are contained in two separate lists. One WHITE list, which means that
 * the SecurityEvent is allowed to be processed/sent/etc; ant one BLACK list, which means that
 * those SecurityEventIds are disabled, not processed.
 * Initially the Black list is empty, while the White list is pre-populated in the class.
 */
#ifndef SECURITY_EVENT_IDS_MANAGER_HPP
#define SECURITY_EVENT_IDS_MANAGER_HPP

#include <stdint.h>
#include <set>
#include "autogen/gsep/ParsedEventIds.hpp"
#include "common/utils/CPP/Singleton.hpp"
#include "common/utils/logger/Logger.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

/**
 * @brief This class implements the 2 list (black & white) management of the SecurityEventIds.
*/
class SecurityEventIdsManager : public common::utils::Singleton<SecurityEventIdsManager>
{
private:
    SecurityEventIdsManager() = default;
    friend class common::utils::Singleton<SecurityEventIdsManager>;

    std::set<uint16_t> m_securityEventsBlacklist;

    std::set<uint16_t> m_securityEventsWhitelist{
        EventIds::ETHERNET_COMMUNICATION_INTERRUPTION,  // IDS-08 - Ethernet Service Interruption Counters Table
        EventIds::DATA_DEFINITION_L3_CHECK_FAILED,      // IDS-09 - OSI Layer 3 check failed
        EventIds::SWITCH_DATAFLOW_STATISTICS,           // IDS-10 - See statistics table on tab "ETH_Switch_Statistics"
        EventIds::DETECTED_UNALLOWED_L3_PROTOCOL,  // IDS-11 - Unallowed layer 3 protocol (e.g.IPv4) detected. On OSI
                                                   // layer 3 only IPv6 shall be used.
        EventIds::DETECTED_UNALLOWED_L4_PROTOCOL,  // IDS-12 - Unallowed layer 4 protocols detected. On OSI layer 4 only
                                                   // TCP, UDP and ICMPv6 shall be used.
        EventIds::UNUSED_PORT_CONNECTION_REQUEST,  // IDS-15 - Connection Request to an Unused Port
        EventIds::MESSAGE_MAX_SIZE_EXCEEDED,  // IDS-17 - Detect message exceeding maximum ECU packet size, including
                                              // size after reassembled fragment
        EventIds::MESSAGE_BURST,              // IDS-23 - Detect message bursts of messages in a defined period of time.
        EventIds::SECOC_SEV_MAC_VERIFICATION_FAILED,  // IDS-25 - MAC verification of a received PDU failed
        EventIds::SECOC_SEV_FRESHNESS_NOT_AVAILABLE,  // IDS-26 - Failed to get freshness value from FvM.  Freshnes
                                                      // Value Manager. The Software Component Freshness Value Manager
                                                      // (FVM) shall provide the  Freshness Value (FV) to SecOC.
        EventIds::TCPIP_SEV_ARP_IP_ADDR_CONFLICT,  // IDS-28 - Received local IP address in ARP reply for different MAC.
        EventIds::TCPIP_SEV_DROP_INV_PORT_TCP,     // IDS-29 - Invalid TCP Destination Port Counters Table
        EventIds::TCPIP_SEV_DROP_INV_PORT_UDP,   // IDS-30 - Dropped UDP packet because of invalid destination UDP-Port
        EventIds::TCPIP_SEV_DROP_INV_IPV4_ADDR,  // IDS-31 - Dropped datagram because of invalid IPV4 address
        EventIds::TCPIP_SEV_DROP_INV_IPV6_ADDR,  // IDS-32 - Dropped datagram because of invalid IPV6 address
        EventIds::SOAD_SEV_DROP_PDU_RX_TCP,  // IDS-33 - SoAd dropped a PDU. The PDU violates stack configuration and
                                             // was received via a TCP socket.
        EventIds::SOAD_SEV_DROP_PDU_RX_UDP,  // IDS-34 - SoAd dropped a PDU. The PDU violates stack configuration and
                                             // was received via a UDP socket.
        EventIds::SOAD_SEV_DROP_MSG_RX_UDP_LENGTH,   // IDS-35 - SoAd dropped a message rx via UDP socket. The violation
                                                     // relates to the length of the PDUs compared to the overall length
                                                     // of the message.
        EventIds::SOAD_SEV_DROP_MSG_RX_UDP_SOCKET,   // IDS-36 - SoAd received a UDP message which violates stack
                                                     // configuration and was dropped. No suitable socket connection
                                                     // matching to configuration was found.
        EventIds::SOAD_SEV_REJECTED_TCP_CONNECTION,  // IDS-37 - SoAd rejected a TCP connection. The connection request
                                                     // violates stack configuration.
        EventIds::ETHIF_SEV_DROP_UNKNOWN_ETHERTYPE,  // IDS-38 - An ethernet datagram was dropped because the Ethertype
                                                     // in not known.
        EventIds::ETHIF_SEV_DROP_VLAN_DOUBLE_TAG,  // IDS-39 - An ethernet datagram was dropped due to double VLAN tag.
        EventIds::ETHIF_SEV_DROP_INV_VLAN,  // IDS-40 - An ethernet datagram was dropped due to an invalid CrtlIdx/VLAN.
        EventIds::ETHIF_SEV_DROP_ETH_MAC_COLLISIONN,  // IDS-41 - Ethernet datagram was dropped because local MAC was
                                                      // same as source MAC in an incoming frame.
        EventIds::LOCAL_FW_LOGS_FORWARDED_PACKAGE_STATISTICS,  // IDS-42 - Local FW Forwarded Package Statistics
        EventIds::LOCAL_FW_BLOCKED_CONNECTIONS_DETECTED,       // IDS-43 - Local FW Blocked Connections Detected
        EventIds::UNEXPECTED_SERVICE_REGISTRY_DETECTED,  // IDS-45 - Every service registry in the SE must notify the
                                                         // IDS Core of every unexpected registration request.
        EventIds::SERVICE_LIST_CHANGE,  // IDS-47 - Online ECU's have a specific set of services they may connect to in
                                        // the backend.
        EventIds::AUTHENTICATION_ERRORS_REPORTS,  // IDS-48 - The IDS sensor must report each event where a car-internal
                                                  // client attempted to connect to sSOA protected ressource without
                                                  // providing valid credentials/token (authentication failure).
        EventIds::FAILED_SERVICE_REQUEST_DETECTED,  // IDS-49 - Every service registry in the SE must notifiy the IDS
                                                    // Core of every failed service discovery request.
        EventIds::PROCESS_CRASH_NOTIFICATION,       // IDS-50 - Process Crash Notification
        EventIds::SMS_LOG_REPORTS,     // IDS-51 - The IDS sensor must log all SMS sent to/from the vehicle.
        EventIds::NAT_UPDATE_REPORTS,  // IDS-52 - The IDS shall maintain a shadow NAT table which shall be updated with
                                       // every arrival of 0xD700 (NAT_UPDATE_REPORTS) Security Event.
        EventIds::RESOURCE_CONSUMPTION_NOTIFICATION,  // IDS-58 - Resource Consumption Notification
        EventIds::PROCESS_START_STOP_NOTIFICATION,    // IDS-59 - Every virtual machine operating system or operating
                                                      // system in the SE must send process start/stop notifications to
                                                      // the IDS Core every time an unknown process starts or stops.
        EventIds::SECURE_BOOT_FAILED,  // IDS-61 - Secure boot failed (signature verification) Once you do a secure
                                       // boot, there is an indication if it failed.
        EventIds::SW_VERSION_UPDATE_MECHANISM_CHANGES,  // IDS-63 - SW Version Update Mechanism Change
        EventIds::VM_CRITICAL_ERROR,  // IDS-64 - The SE VM/Hypervisor must send a notification of any critical errors
                                      // encountered (guest OS boot failure, image validation failure, virtual machine
                                      // reset, etc.) to the IDS Core.
        EventIds::ECU_MODE_CHANGE,  // IDS-65 - If a ECU changes ist state from "normal operation mode" to another state
                                    // (e.g. Safe State, Recovery mode etc), the IDS Core should be notified.
        EventIds::APN_CONFIGURATION_CHANGE_REPORTS,  // IDS-66 - APN Configuration Change Report
        EventIds::OS_LOG_REPORTS,                    // IDS-67 - OS Log Reports
        EventIds::MAC_AUDIT_REPORTS,  // IDS-68 - SMACK (Simplified Mandatory Access Control Kernel) audit records (if
                                      // available) must be reported. There is also SE LINUX ->Mandatory Access Control
                                      // mechanism All mechanisms are meant here. What we want to see here are the error
                                      // logs from the security mechanism.
        EventIds::IDSM_INTERNAL_EVENT_NO_EVENT_BUFFER_AVAILABLE,  // IDS-69 - A SEv cannot be handled because there are
                                                                  // no more event buffers available to process the
                                                                  // event.
        EventIds::IDSM_INTERNAL_EVENT_NO_CONTEXT_DATA_BUFFER_AVAILABLE,  // IDS-70 - The context data of an incoming
                                                                         // event cannot be stored because there are no
                                                                         // more context data buffers available.
        EventIds::IDSM_INTERNAL_EVENT_TRAFFIC_LIMITATION_EXCEEDED,  // IDS-71 - The current traffic exceeds a configured
                                                                    // traffic limitation.
        EventIds::ERROR_EVENT_LOGGING_MONITORING,  // IDS-72 - Error and event logging Monitoring (critical errors,
                                                   // application crashes, memory access denials etc).
        EventIds::SECURITY_ERROR_EVENT_LOGGING_MONITORING,  // IDS-73 - Error and event logging Monitoring (security
                                                            // related events, file access).
        EventIds::ERROR_EVENT_LOGGING_USER_LOGIN,  // IDS-74 - Relevant log files and error logging created by virtual
                                                   // machine logging mechanisms must be sent to the IDS Core
                                                   // frequently.
        EventIds::ACCESS_CONTROL_CONFIGURATION_CHANGE,  // IDS-75 - Access control configuration change.
        EventIds::VKMS_NO_KEYS_AVAILABLE,               // IDS-76 - VKMS key storage is empty.
        EventIds::VKMS_DLC_VERIFICATION_FAILED,         // IDS-77 - DLC signature is not valid, or invalid content.
        EventIds::VKMS_UNKNOWN_KEY_REQUESTED,       // IDS-78 - An application requested a key not available in VKMS.
        EventIds::VKMS_VIN_VALIDATION_FAILED,       // IDS-79 - The VIN in DLC does not match to the vehicle VIN.
        EventIds::DIAG_SEV_WRITE_INVALID_DATA,      // IDS-88 - Tester writes invalid data with service WriteDataBy
                                                    // Identifier.
        EventIds::DIAG_SEV_SECURITY_ACCESS_DENIED,  // IDS-89 - Tester has send an diagnostic request without meeting
                                                    // the servers security level requirements for that service. NRC
                                                    // 0x33 (securityAccessDenied) was returned.
        EventIds::DIAG_SEV_COMMUNICATION_CONTROL_SWITCHED_OFF,  // IDS-90 - ECU communication was switched off with
                                                                // service CommunicationControl.
        EventIds::DIAG_SEV_SERVICE_NOT_SUPPORTED,  // IDS-91 - A diagnostic service was requested that is not supported
                                                   // ornot supported in the active session. NRC 0x11 (serviceNot
                                                   // Supported) or NRC 0x7F (serviceNotSupportedInActive Session) was
                                                   // returned.
        EventIds::DIAG_SEV_SUBFUNCTION_NOT_SUPPORTED,  // IDS-92 - A subfunction of a diagnostic service was requested
                                                       // that is not supported for the requested service.
        EventIds::DIAG_SEV_INCORRECT_MESSAGE_LENGTH_OR_FORMAT,  // IDS-93 - Received request message does not match the
                                                                // specified length or the format of the parameters is
                                                                // different from the specified ones for that service.
                                                                // NRC 0x13 (incorrect MessageLengthOrInvalidFormat) was
                                                                // returned.
        EventIds::DIAG_SEV_REQUEST_SEQUENCE_ERROR,  // IDS-94 - A diagnostic service was received in the wrong sequence
                                                    // order. NRC 0x24 (requestSequenceError) was returned.
        EventIds::DIAG_SEV_REQUEST_OUT_OF_RANGE,  // IDS-95 - A diagnsotic request with a parameter that is our range of
                                                  // the allowed bounds was received. A NRC 0x31 (requestOut OfRange)
                                                  // was returned.
        EventIds::DIAG_SEV_REQUESTED_ACTIONS_REQUIRES_AUTHENTICATION,  // IDS-96 - A diagnostic request was received
                                                                       // while the required authentication to executie
                                                                       // this service is not given. NRC 0x34
                                                                       // (authenticationRequired) was returned.
        EventIds::DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED,  // IDS-97 - Security Access failed and the
                                                                         // number of invalid attempts has been
                                                                         // exceeded. NRC 0x36 (exceedNumberOf Attempts)
                                                                         // was returned. Here the counters should be
                                                                         // for consecuritve attempts and reset after
                                                                         // driving cycle. Not a global counter.
        EventIds::DIAG_SEV_SECURITY_ACCESS_INVALID_KEY,  // IDS-98 - Security Access failed because the tester has send
                                                         // aninvalid key to the server. An NRC 0x35 (invalidKey) was
                                                         // returned.
        EventIds::DIAG_SEV_SECURITY_ACCESS_REQUIRED_TIME_DELAY_NOT_EXPIRED,  // IDS-99 - A further attempt to unlock the
                                                                             // ECU was taken before the delay time had
                                                                             // expired. NRC 0x37 (requiredTimeDelayNot
                                                                             // Expired) was sent.
        EventIds::DIAG_SEV_NUMBER_OF_FAILED_AUTHENTICATION_ATTEMPTS_EXCEEDED,  // IDS-100 - Number of failed
                                                                               // authentification attempts - OEM
                                                                               // specific.
        EventIds::DIAG_SEV_CERTIFICATE_FAILURE,    // IDS-101 - The tester tried an authentication with an invalid
                                                   // certficate.
        EventIds::DIAG_SEV_ECU_UNLOCK_SUCCESSFUL,  // IDS-102 - Successful unlocked the ECU (via Security Access $27),
                                                   // per Level.
        EventIds::DIAG_SEV_AUTHENTICATION_SUCCESSFUL,  // IDS-103 - Succesfully authenticated (via Authentication $29)
        EventIds::DIAG_SEV_CLEAR_DTC_SUCCESSFUL,       // IDS-104 - DTC information has been cleared by SID 0x14 Clear
                                                       // DTCInformation
        EventIds::DIAG_SEV_ECU_RESET,                  // IDS-105 - ECU had been reset by SID 0x11 ResetECU
        EventIds::DIAG_SEV_WRITE_DATA,  // IDS-106 - Diagnostic data identifier have been written by SID 0x2E.   Only
                                        // for sucessfull written data- Not for NRC 0x31
        EventIds::DIAG_SEV_REQUEST_DOWNLOAD,          // IDS-107 - DTC setting switched off with service 0x85 (Control
                                                      // DTCSetting).
        EventIds::DIAG_SEV_DTC_SETTING_SWITCHED_OFF,  // IDS-108 - A diagnsotic data download sequence was requested
                                                      // with SID 0x34.
        EventIds::CRYPTOGRAPHIC_LIB_FAILURES_NOTIFICATION,      // IDS-109 - Cryptographic Lib Failures Notification
        EventIds::CONFIGURATION_FILE_DISCREPANCY_NOTIFICATION,  // IDS-110 - Periodic check of the 'configuration files"
                                                                // (instructions, directives, commands) must be included
                                                                // in the host-based sensor setup.
        EventIds::TRUSTED_APPLICATION_INVOCATION,  // IDS-112 - The SE must inform the IDS Core of any of any invocation
                                                   // of a Trusted Application (TEE Domain).
        EventIds::EXTERNAL_CONNECTION_INTERFACE_SUCCESSFUL,    // IDS-113 - Successful wireless connections.
        EventIds::EXTERNAL_CONNECTION_INTERFACE_UNSUCCESSFUL,  // IDS-114 - External Connection Interface Unsuccessful
        EventIds::NEW_BINDING_INTERFACE_NOTIFICATION,  // IDS-115 - New bindings of applications/processes to any
                                                       // wireless interface, including bindings performed during system
                                                       // start-up.
        EventIds::EXTERNAL_INTERFACES_USAGE_STATISTICS,  // IDS-116 - External interfaces usage statistics
        EventIds::EXTERNAL_DATA_STORAGE_CONNECTION,      // IDS-118 - External Data Storage Connection
        EventIds::EXTERNAL_NEW_HW_CONNECTION,            // IDS-120 - external new HW connection
        EventIds::EXTERNAL_SOURCES_FILE_DATA_STREAM,  // IDS-121 - File or data stream received from external sources.
        EventIds::DIAGNOSTIC_DATA_SET_DOWNLOAD,       // IDS-122 - Diagnostic Data Set Download
        EventIds::SW_VERIFICATION_FAILURE,       // IDS-125 - Failure in the method used to verify the authenticity of a
                                                 // piece of SW.
        EventIds::VKMS_KEY_CHANGE,               // IDS-126 - VKMS Key Change
        EventIds::VTTL_REGISTRY_CHANGE_REPORTS,  // IDS-127 - VTTL Registry Change Reports
        EventIds::CONTROL_MODULE_ERROR,  // IDS-130 - This Security Event will trigger when one Contorl Module error is
                                         // activated. If an ECU has access to the DEM or the DTC Setting logic, it will
                                         // be triggered once a Control module related DTC is set to \"active\".
                                         // Normally use for RAM Errors
        EventIds::KEEP_ALIVE_MESSAGE,    // IDS-131 - Keep-alive notification in order to validate sensor functionality

        // Intelligent event id
        EventIds::AUDI_IDS_INTELLIGENT_SENSOR,

        //HCP1
        EventIds::CAN_TIMING_ANOMALY_DETECTED,
        EventIds::UNKNOWN_MESSAGE_DETECTED,

        // SACID
        EventIds::CANIF_SEV_TX_ERROR_DETECTED,
        EventIds::CANIF_SEV_RX_ERROR_DETECTED,
        EventIds::CANIF_SEV_ERRORSTATE_PASSIVE,
        EventIds::CANIF_SEV_ERRORSTATE_BUSOFF,
        EventIds::CHAR_EXI_SIGNATURE_INVALID,
        EventIds::CHAR_COM_MESSAGE_OUT_OF_SEQUENCE,
        EventIds::CHAR_EXI_MESSAGE_INVALID,
        EventIds::CHAR_SERVER_TLS_CERTIFICATE_INVALID,
        EventIds::CHAR_EXI_SIGNATURE_MISSING,
        EventIds::CHAR_CONTRACT_CERTIFICATE_INSTALLATION_FAILED,
        EventIds::FLOW_INTEGRITY_FAILURE,
        EventIds::CHAR_SECC_DISCOVERY_PROTOCOL_INVALID};
#ifdef TESTS
    std::set<uint16_t> m_copySecurityEventsWhitelist;
#endif

public:
    /**
     * @brief   Updates the internal Blacklist, and whitelist (subtract the blacklist content from the initial
     * whitelist)
     * @param   std::vector<uint32_t> blacklistedSecurityEventsArray - a vector of blacklisted event ids.
     * @return  none.
     */
    void
    UpdateSecurityEventsLists(std::vector<uint16_t> const& blacklistedSecurityEventsArray)
    {
        std::set<uint16_t> result;
        // convert from std::vector to std::set
        m_securityEventsBlacklist = std::set<uint16_t>(std::make_move_iterator(blacklistedSecurityEventsArray.begin()),
                                                       std::make_move_iterator(blacklistedSecurityEventsArray.end()));
        // substract the blacklist from the whitelist
        std::ignore = std::set_difference(m_securityEventsWhitelist.begin(),
                                          m_securityEventsWhitelist.end(),
                                          m_securityEventsBlacklist.begin(),
                                          m_securityEventsBlacklist.end(),
                                          std::inserter(result, result.end()));

#ifdef TESTS
        m_copySecurityEventsWhitelist.insert(m_securityEventsWhitelist.begin(), m_securityEventsWhitelist.end());
#endif
        // update the whitelist with the (INITIAL_WHITELIST - BLACKLIST)
        m_securityEventsWhitelist = std::move(result);

        LOG_INFO << "Currently there are " << m_securityEventsWhitelist.size() << " SE in WHITE list and "
                 << m_securityEventsBlacklist.size() << " in BLACK list" << LOG_NOOP;
    }

    /**
     * @brief   Returns the security event ids White list.
     * @return  Returns the security event ids White list.
     */
    inline std::set<uint16_t> const&
    GetSecurityEventsIdsWhiteList() const
    {
        return m_securityEventsWhitelist;
    }

    /**
     * @brief   Returns the security event ids Black list.
     * @return  Returns the security event ids Black list.
     */
    inline std::set<uint16_t> const&
    GetSecurityEventsIdsBlackList() const
    {
        return m_securityEventsBlacklist;
    }

    /**
     * @brief   Checks if the specified parameter is in the White list.
     * @param   uint16_t elem - the element to check if it is in the Whitelist
     * @return  Returns true if the specified element is in the White list; false otherwise.
     */
    inline bool
    IsInSecurityEventsIdsWhiteList(uint16_t elem) const
    {
        return std::find(m_securityEventsWhitelist.begin(), m_securityEventsWhitelist.end(), elem)
               != m_securityEventsWhitelist.end();
    }

    /**
     * @brief   Checks if the specified elem parameter is in the Black list.
     * @param   uint16_t elem - the element to be checked in the Black list.
     * @return  Returns true, if the element is in the Black list; otherwise false.
     */
    inline bool
    IsInSecurityEventsIdsBlackList(uint16_t elem) const
    {
        return std::find(m_securityEventsBlacklist.begin(), m_securityEventsBlacklist.end(), elem)
               != m_securityEventsBlacklist.end();
    }

#ifdef TESTS
    inline void
    resetWhiteAndBlackLists()
    {
        m_securityEventsWhitelist.clear();
        m_securityEventsWhitelist.insert(m_copySecurityEventsWhitelist.begin(), m_copySecurityEventsWhitelist.end());
        m_securityEventsBlacklist.clear();
    }
#endif
};


}  // namespace security_events
}  // namespace engines
}  // namespace brain

#endif  // SECURITY_EVENT_IDS_MANAGER_HPP