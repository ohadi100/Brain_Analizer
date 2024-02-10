/**
 * @file
 * @brief     A rule engine for the Security Events
 */
#include "SecurityEventsEngine.hpp"
#include <DBNames.hpp>
#include "NanoPB.hpp"
#include "brain_app/BrainApp.hpp"
#include "brain/config/AlertEventsNames.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "brain/noise_filter/event_noise_filter/GroupNoiseFilter.hpp"
#include "brain/utils/nanopb/Decoders.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "common/utils/typeCasting/TypeCasting.hpp"
#include "resourceConsumptionNotification/ResourceConsumptionNotificationEngine.hpp"
#include "brain/sensor_data/swpac/IncidentHelper.hpp"
#include "brain/sensor_data/swpac/SwpacSensorDataBase.hpp"

#if defined(SSP_PLATFORM) || defined(SSP_PLATFORM_TEST) || defined(SSP_SIMULATION)
#include "brain/engines/SSP/EngineDispatcher.hpp"
#else //defined(SSP_PLATFORM) || defined(SSP_PLATFORM_TEST) || defined(SSP_SIMULATION)
#include "brain/engines/PPE/EngineDispatcher.hpp"
#endif

using brain::engines::ReturnCode;
using brain::engines::security_events::EventIds;
using brain::engines::security_events::IpAnomaliesCountersEntry;
using brain::engines::security_events::OversizedPacketsHistogramEntry;
using brain::engines::security_events::SecurityEventFrame;
using brain::engines::security_events::SecurityEventIdsManager;
using brain::engines::security_events::SecurityEventsEngine;
using brain::engines::security_events::ServiceRegistryEntry;
using brain::utils::AddressType;
using brain::utils::ConvertIpAddress;
using brain::utils::FormatIpType;
using namespace brain::sender_events;
using brain::engines::security_events::DropReason;
using brain::sensor_data::swpac::ConstraintId;
using brain::app_mng::BrainApp;
using namespace brain::histogram;

namespace brain
{
namespace engines
{
namespace security_events
{
using FloatHistogramData = com_vwg_connect_ids_idsperiodicreport_v1_FloatHistogramData;
static std::string const  SerializedEventsPersistentMemoryKey{"SerializedMonitorEvents"};
static constexpr uint32_t DefaultKeepAliveTimeoutPeriod{600U};

static constexpr size_t ipConnectionCountersTableLimit{200U};
static constexpr size_t hostOsLogRateTableLimit{10U};
static constexpr size_t externalUnsuccessfulConnectionsTableLimit{50U};
static constexpr size_t externalInterfacesUsageStatisticsTableLimit{50U};
static constexpr size_t processStartStopCountersTableLimit{800U};
static constexpr size_t keepAliveTimersTableLimit{10U};
static constexpr size_t processCrashRateTableLimit{400U};
static constexpr size_t serviceRegistryTableLimit{50U};
static constexpr size_t externalNewHWConnectionTableLimit{50U};
static constexpr size_t externalDataStorageTableLimit{50U};
static constexpr size_t droppedBlockedConnectionsTableLimit{100U};
static constexpr size_t ethernetServiceInterruptionTableLimit{50U};
static constexpr size_t oversizedPacketsHistogramTableLimit{100U};
static constexpr size_t invalidAddressDestinationPortCounterTableLimit{400U};
static constexpr size_t freshnessValueFailedCountersTableLimit{100U};
static constexpr size_t disallowedLayer3ProtocolCountersTableLimit{50U};
static constexpr size_t disallowedLayer4ProtocolCountersTableLimit{100U};
static constexpr size_t unusedPortConnectionAttemptsTableLimit{100U};
static constexpr size_t ipAnomaliesConnectionsCountersTableLimit{400U};
static constexpr size_t macToIpAssociationTableLimit{200U};
static constexpr size_t doubledIpToMacAssociationTableLimit{200U};
static constexpr size_t doubledMacToIpAssociationTableLimit{200U};
static constexpr size_t droppedConnectionsCountersTableLimit{400U};
static constexpr size_t securityEventsCountersTableLimit{300U};
static constexpr size_t droppedSecurityEventsCountersTableLimit{1000U};
static constexpr size_t criticalSecurityEventsAlertsCountersTableLimit{200U};
static constexpr size_t rxTxErrorsCountersTableLimit{100U};
static constexpr size_t canIfSevErrorStateTableLimit{100U};

void initIpAnomaliesCountersEntry(IpAnomaliesCountersEntry&                                                    entry,
                                  SecurityEventFrame                                                           frame,
                                  brain::engines::security_events::SECEV_DETECTED_UNALLOWED_L4_PROTOCOL const* event);
bool isIpAnomaliesEntryValid(brain::engines::security_events::SECEV_DETECTED_UNALLOWED_L4_PROTOCOL const* event);
}  // namespace security_events
}  // namespace engines
}  // namespace brain

static std::unordered_set<common::sensor_data::SensorDataTag>&&
initSecurityEventsEngineValidTags() noexcept
{
    static std::unordered_set<common::sensor_data::SensorDataTag> newSet{
        common::sensor_data::SensorDataTag::SD_SECURITY_EVENT};
    return std::move(newSet);
}
std::unordered_set<common::sensor_data::SensorDataTag> const SecurityEventsEngine::validTags
    = initSecurityEventsEngineValidTags();

static brain::histogram::RateHistogram::BinIntervalsVector&&
initSecurityEventsEngineRatesBins() noexcept
{
    static brain::histogram::RateHistogram::BinIntervalsVector newVector{
        1.0 / common::S_TO_MS(100.), 1.0 / common::S_TO_MS(10.), 1.0 / common::S_TO_MS(1.), 10.0 / common::S_TO_MS(1.)};
    return std::move(newVector);
}
// OS Log Rate Histogram (requirement 3.2) - timestamps (ms)
brain::histogram::RateHistogram::BinIntervalsVector const SecurityEventsEngine::m_ratesBins
    = initSecurityEventsEngineRatesBins();

static brain::histogram::RateHistogram::BinIntervalsVector&&
initSecurityEventsEngineProcessCrashRateBins() noexcept
{
    static brain::histogram::RateHistogram::BinIntervalsVector newVector{
        1.0 / common::S_TO_MS(1000), 1.0 / common::S_TO_MS(100), 1.0 / common::S_TO_MS(10), 1.0 / common::S_TO_MS(1)};
    return std::move(newVector);
}
// Process Crash Rate Histogram (requirement 3.8 HCP3 GBT) - timestamps (ms)
brain::histogram::RateHistogram::BinIntervalsVector const SecurityEventsEngine::m_processCrashRateBins
    = initSecurityEventsEngineProcessCrashRateBins();

static brain::histogram::RateHistogram::BinIntervalsVector&&
initSecurityEventsEnginePackageSizeBins() noexcept
{
    static brain::histogram::RateHistogram::BinIntervalsVector newVector{
        2048, 4096, std::numeric_limits<uint32_t>::max()};
    return std::move(newVector);
}
// Process Oversized Packets Histogram using the packageSize field in the context data
brain::histogram::RateHistogram::BinIntervalsVector const SecurityEventsEngine::m_packageSizeBins
    = initSecurityEventsEnginePackageSizeBins();

// parasoft-begin-suppress AUTOSAR-M15_3_1-a "Keep the vector as itavoid using init function for map and createDecodeContextDataHandler"
// parasoft-begin-suppress AUTOSAR-A15_5_3-f "Keep the vector as itavoid using init function for map and createDecodeContextDataHandler"
std::map<uint16_t, SecurityEventsEngine::CallbackVector> SecurityEventsEngine::m_eventHandlers = {
    // IDS-08
    {EventIds::ETHERNET_COMMUNICATION_INTERRUPTION,
     CallbackVector{createDecodeContextDataHandler<SECEV_ETHERNET_COMMUNICATION_INTERRUPTION>(
         &SecurityEventsEngine::handleEthernetCommunicationInterruptionEvent)}},
    // IDS-09
    {EventIds::DATA_DEFINITION_L3_CHECK_FAILED,
     CallbackVector{createDecodeContextDataHandler<SECEV_DATA_DEFINITION_L3_CHECK_FAILED>(
         &SecurityEventsEngine::handleDataDefinitionL3CheckFailedEvent)}},
    // IDS-10
    {EventIds::SWITCH_DATAFLOW_STATISTICS,
     CallbackVector{createDecodeContextDataHandler<SECEV_SWITCH_DATAFLOW_STATISTICS>(
         &SecurityEventsEngine::handleSwitchDataflowStatisticsEvent)}},
    // IDS-11
    {EventIds::DETECTED_UNALLOWED_L3_PROTOCOL,
     CallbackVector{createDecodeContextDataHandler<SECEV_DETECTED_UNALLOWED_L3_PROTOCOL>(
         &SecurityEventsEngine::handleDisallowedLayer3ProtocolEvent)}},
    // IDS - 12
    {EventIds::DETECTED_UNALLOWED_L4_PROTOCOL,
     CallbackVector{createDecodeContextDataHandler<SECEV_DETECTED_UNALLOWED_L4_PROTOCOL>(
         &SecurityEventsEngine::handleDisallowedLayer4ProtocolEvent)}},
    // IDS-15
    {EventIds::UNUSED_PORT_CONNECTION_REQUEST,
     CallbackVector{createDecodeContextDataHandler<SECEV_UNUSED_PORT_CONNECTION_REQUEST>(
                        &SecurityEventsEngine::handleUnusedPortConnectionRequestEvent),
                    &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_UNUSED_PORT_CONNECTION_REQUEST>}},
    {EventIds::MESSAGE_MAX_SIZE_EXCEEDED,
     CallbackVector{createDecodeContextDataHandler<SECEV_MESSAGE_MAX_SIZE_EXCEEDED>(
         &SecurityEventsEngine::handleOversizedPacketsHistogram)}},
    // IDS-23
    {EventIds::MESSAGE_BURST, CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_MESSAGE_BURST>}},
    // IDS-25
    {EventIds::SECOC_SEV_MAC_VERIFICATION_FAILED,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_SECOC_SEV_MAC_VERIFICATION_FAILED>}},
    // IDS-26
    {EventIds::SECOC_SEV_FRESHNESS_NOT_AVAILABLE,
     CallbackVector{createDecodeContextDataHandler<SECEV_SECOC_SEV_FRESHNESS_NOT_AVAILABLE>(
         &SecurityEventsEngine::HandleFreshnessValueFailedEvent)}},
    // IDS-28
    {EventIds::TCPIP_SEV_ARP_IP_ADDR_CONFLICT,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_TCPIP_SEV_ARP_IP_ADDR_CONFLICT>}},
    // IDS-29
    {EventIds::TCPIP_SEV_DROP_INV_PORT_TCP,
     CallbackVector{createDecodeContextDataHandler<SECEV_TCPIP_SEV_DROP_INV_PORT_TCP>(
         &SecurityEventsEngine::handleDroppedTcpPacketsEvent)}},
    // IDS-30
    {EventIds::TCPIP_SEV_DROP_INV_PORT_UDP,
     CallbackVector{createDecodeContextDataHandler<SECEV_TCPIP_SEV_DROP_INV_PORT_UDP>(
         &SecurityEventsEngine::handleDroppedUdpPacketsEvent)}},
    // IDS-31
    {EventIds::TCPIP_SEV_DROP_INV_IPV4_ADDR,
     CallbackVector{createDecodeContextDataHandler<SECEV_TCPIP_SEV_DROP_INV_IPV4_ADDR>(
         &SecurityEventsEngine::handleDroppedIpv4AddressEvent)}},
    // IDS-32
    {EventIds::TCPIP_SEV_DROP_INV_IPV6_ADDR,
     CallbackVector{createDecodeContextDataHandler<SECEV_TCPIP_SEV_DROP_INV_IPV6_ADDR>(
         &SecurityEventsEngine::handleDroppedIpv6AddressEvent)}},
    // IDS-33
    {EventIds::SOAD_SEV_DROP_PDU_RX_TCP,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_SOAD_SEV_DROP_PDU_RX_TCP>}},
    // IDS-34
    {EventIds::SOAD_SEV_DROP_PDU_RX_UDP,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_SOAD_SEV_DROP_PDU_RX_UDP>}},
    // IDS-35
    {EventIds::SOAD_SEV_DROP_MSG_RX_UDP_LENGTH,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_SOAD_SEV_DROP_MSG_RX_UDP_LENGTH>}},
    // IDS-36
    {EventIds::SOAD_SEV_DROP_MSG_RX_UDP_SOCKET,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_SOAD_SEV_DROP_MSG_RX_UDP_SOCKET>}},
    // IDS-37
    {EventIds::SOAD_SEV_REJECTED_TCP_CONNECTION,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_SOAD_SEV_REJECTED_TCP_CONNECTION>}},
    // IDS-38
    {EventIds::ETHIF_SEV_DROP_UNKNOWN_ETHERTYPE,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_ETHIF_SEV_DROP_UNKNOWN_ETHERTYPE>}},
    // IDS-39
    {EventIds::ETHIF_SEV_DROP_VLAN_DOUBLE_TAG,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_ETHIF_SEV_DROP_VLAN_DOUBLE_TAG>}},
    // IDS-40
    {EventIds::ETHIF_SEV_DROP_INV_VLAN,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_ETHIF_SEV_DROP_INV_VLAN>}},
    // IDS-41
    {EventIds::ETHIF_SEV_DROP_ETH_MAC_COLLISIONN,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_ETHIF_SEV_DROP_ETH_MAC_COLLISIONN>}},
    // IDS-42
    {EventIds::LOCAL_FW_LOGS_FORWARDED_PACKAGE_STATISTICS,
     CallbackVector{createDecodeContextDataHandler<SECEV_LOCAL_FW_LOGS_FORWARDED_PACKAGE_STATISTICS>(
         &SecurityEventsEngine::handleLogsForwardedPackageStatisticsEvent)}},
    // IDS-43
    {EventIds::LOCAL_FW_BLOCKED_CONNECTIONS_DETECTED,
     CallbackVector{createDecodeContextDataHandler<SECEV_LOCAL_FW_BLOCKED_CONNECTIONS_DETECTED>(
         &SecurityEventsEngine::handleBlockedConnectionsDetectedEvent)}},
    // IDS-45
    {EventIds::UNEXPECTED_SERVICE_REGISTRY_DETECTED,
     CallbackVector{createDecodeContextDataHandler<SECEV_UNEXPECTED_SERVICE_REGISTRY_DETECTED>(
                        &SecurityEventsEngine::handleUnexpectedServiceRegistryEvent)}},
    // IDS-47
    {EventIds::SERVICE_LIST_CHANGE, CallbackVector{&SecurityEventsEngine::forwardCriticalSecurityEvent}},
    // IDS-48
    {EventIds::AUTHENTICATION_ERRORS_REPORTS,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_AUTHENTICATION_ERRORS_REPORTS>}},
    // IDS-49
    {EventIds::FAILED_SERVICE_REQUEST_DETECTED,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_FAILED_SERVICE_REQUEST_DETECTED>}},
    // IDS-50
    {EventIds::PROCESS_CRASH_NOTIFICATION,
     CallbackVector{createDecodeContextDataHandler<SECEV_PROCESS_CRASH_NOTIFICATION>(
         &SecurityEventsEngine::handleProcessCrashNotificationEvent)}},
    // IDS-51
    {EventIds::SMS_LOG_REPORTS,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_SMS_LOG_REPORTS>}},
    // IDS-52
    {EventIds::NAT_UPDATE_REPORTS,
     CallbackVector{
         createDecodeContextDataHandler<SECEV_NAT_UPDATE_REPORTS>(&SecurityEventsEngine::handleNatTableEvents)}},
    // IDS-59
    {EventIds::PROCESS_START_STOP_NOTIFICATION,
     CallbackVector{createDecodeContextDataHandler<SECEV_PROCESS_START_STOP_NOTIFICATION>(
         &SecurityEventsEngine::handleProcessStartStopNotificationEvent)}},
    // IDS-61
    {EventIds::SECURE_BOOT_FAILED,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_SECURE_BOOT_FAILED>}},
    // IDS-63
    {EventIds::SW_VERSION_UPDATE_MECHANISM_CHANGES,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_SW_VERSION_UPDATE_MECHANISM_CHANGES>}},
    // IDS-64
    {EventIds::VM_CRITICAL_ERROR,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_VM_CRITICAL_ERROR>}},
    // IDS-65
    {EventIds::ECU_MODE_CHANGE,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_ECU_MODE_CHANGE>}},
    // IDS-66
    {EventIds::APN_CONFIGURATION_CHANGE_REPORTS,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_APN_CONFIGURATION_CHANGE_REPORTS>}},
    // IDS-67
    {EventIds::OS_LOG_REPORTS,
     CallbackVector{
         createDecodeContextDataHandler<SECEV_OS_LOG_REPORTS>(&SecurityEventsEngine::handleOsLogReportsEvent),
         &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_OS_LOG_REPORTS>}},
    // IDS-68
    {EventIds::MAC_AUDIT_REPORTS,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_MAC_AUDIT_REPORTS>}},
    // IDS-69
    {EventIds::IDSM_INTERNAL_EVENT_NO_EVENT_BUFFER_AVAILABLE,
     CallbackVector{
         &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_IDSM_INTERNAL_EVENT_NO_EVENT_BUFFER_AVAILABLE>}},
    // IDS-70
    {EventIds::IDSM_INTERNAL_EVENT_NO_CONTEXT_DATA_BUFFER_AVAILABLE,
     CallbackVector{
         &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_IDSM_INTERNAL_EVENT_NO_CONTEXT_DATA_BUFFER_AVAILABLE>}},
    // IDS-71
    {EventIds::IDSM_INTERNAL_EVENT_TRAFFIC_LIMITATION_EXCEEDED,
     CallbackVector{
         &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_IDSM_INTERNAL_EVENT_TRAFFIC_LIMITATION_EXCEEDED>}},
    // IDS-72
    {EventIds::ERROR_EVENT_LOGGING_MONITORING,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_ERROR_EVENT_LOGGING_MONITORING>}},
    // IDS-73
    {EventIds::SECURITY_ERROR_EVENT_LOGGING_MONITORING,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_SECURITY_ERROR_EVENT_LOGGING_MONITORING>}},
    // IDS-74
    {EventIds::ERROR_EVENT_LOGGING_USER_LOGIN,
     CallbackVector{createDecodeContextDataHandler<SECEV_ERROR_EVENT_LOGGING_USER_LOGIN>(
         &SecurityEventsEngine::handleErrorEventLoggingUserLoginEvent)}},
    // IDS-75
    {EventIds::ACCESS_CONTROL_CONFIGURATION_CHANGE,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_ACCESS_CONTROL_CONFIGURATION_CHANGE>}},
    // IDS-76
    {EventIds::VKMS_NO_KEYS_AVAILABLE,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_VKMS_NO_KEYS_AVAILABLE>}},
    // IDS-77
    {EventIds::VKMS_DLC_VERIFICATION_FAILED,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_VKMS_DLC_VERIFICATION_FAILED>}},
    // IDS-78
    {EventIds::VKMS_UNKNOWN_KEY_REQUESTED,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_VKMS_UNKNOWN_KEY_REQUESTED>}},
    // IDS-79
    {EventIds::VKMS_VIN_VALIDATION_FAILED,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_VKMS_VIN_VALIDATION_FAILED>}},
    // IDS-88
    {EventIds::DIAG_SEV_WRITE_INVALID_DATA,
     CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence,
                    &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_DIAG_SEV_WRITE_INVALID_DATA>}},
    // IDS-89
    {EventIds::DIAG_SEV_SECURITY_ACCESS_DENIED,
     CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence,
                    &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_DIAG_SEV_SECURITY_ACCESS_DENIED>}},
    // IDS-90
    {EventIds::DIAG_SEV_COMMUNICATION_CONTROL_SWITCHED_OFF,
     CallbackVector{
         &SecurityEventsEngine::HandleDiagnosticEventSequence,
         &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_DIAG_SEV_COMMUNICATION_CONTROL_SWITCHED_OFF>}},
    // IDS-91
    {EventIds::DIAG_SEV_SERVICE_NOT_SUPPORTED,
     CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence,
                    &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_DIAG_SEV_SERVICE_NOT_SUPPORTED>}},
    // IDS-92
    {EventIds::DIAG_SEV_SUBFUNCTION_NOT_SUPPORTED,
     CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence,
                    &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_DIAG_SEV_SUBFUNCTION_NOT_SUPPORTED>}},
    // IDS-93
    {EventIds::DIAG_SEV_INCORRECT_MESSAGE_LENGTH_OR_FORMAT,
     CallbackVector{
         &SecurityEventsEngine::HandleDiagnosticEventSequence,
         &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_DIAG_SEV_INCORRECT_MESSAGE_LENGTH_OR_FORMAT>}},
    // IDS-94
    {EventIds::DIAG_SEV_REQUEST_SEQUENCE_ERROR,
     CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence,
                    &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_DIAG_SEV_REQUEST_SEQUENCE_ERROR>}},
    // IDS-95
    {EventIds::DIAG_SEV_REQUEST_OUT_OF_RANGE,
     CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence,
                    &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_DIAG_SEV_REQUEST_OUT_OF_RANGE>}},
    // IDS-96
    {EventIds::DIAG_SEV_REQUESTED_ACTIONS_REQUIRES_AUTHENTICATION,
     CallbackVector{
         &SecurityEventsEngine::HandleDiagnosticEventSequence,
         &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_DIAG_SEV_REQUESTED_ACTIONS_REQUIRES_AUTHENTICATION>}},
    // IDS-97
    {EventIds::DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED,
     CallbackVector{
         &SecurityEventsEngine::HandleDiagnosticEventSequence,
         &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED>}},
    // IDS-98
    {EventIds::DIAG_SEV_SECURITY_ACCESS_INVALID_KEY,
     CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence,
                    &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_DIAG_SEV_SECURITY_ACCESS_INVALID_KEY>}},
    // IDS-99
    {EventIds::DIAG_SEV_SECURITY_ACCESS_REQUIRED_TIME_DELAY_NOT_EXPIRED,
     CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence,
                    &SecurityEventsEngine::decodeHandleCriticalEvent<
                        SECEV_DIAG_SEV_SECURITY_ACCESS_REQUIRED_TIME_DELAY_NOT_EXPIRED>}},
    // IDS-100
    {EventIds::DIAG_SEV_NUMBER_OF_FAILED_AUTHENTICATION_ATTEMPTS_EXCEEDED,
     CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence,
                    &SecurityEventsEngine::decodeHandleCriticalEvent<
                        SECEV_DIAG_SEV_NUMBER_OF_FAILED_AUTHENTICATION_ATTEMPTS_EXCEEDED>}},
    // IDS-101
    {EventIds::DIAG_SEV_CERTIFICATE_FAILURE,
     CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence,
                    &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_DIAG_SEV_CERTIFICATE_FAILURE>}},
    // IDS-102
    {EventIds::DIAG_SEV_ECU_UNLOCK_SUCCESSFUL, CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence}},
    // IDS-103
    {EventIds::DIAG_SEV_AUTHENTICATION_SUCCESSFUL,
     CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence}},
    // IDS-104
    {EventIds::DIAG_SEV_CLEAR_DTC_SUCCESSFUL, CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence}},
    // IDS-105
    {EventIds::DIAG_SEV_ECU_RESET, CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence}},
    // IDS-106
    {EventIds::DIAG_SEV_WRITE_DATA, CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence}},
    // IDS-107
    {EventIds::DIAG_SEV_REQUEST_DOWNLOAD, CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence}},
    // IDS-108
    {EventIds::DIAG_SEV_DTC_SETTING_SWITCHED_OFF, CallbackVector{&SecurityEventsEngine::HandleDiagnosticEventSequence}},
    // IDS-109
    {EventIds::CRYPTOGRAPHIC_LIB_FAILURES_NOTIFICATION,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_CRYPTOGRAPHIC_LIB_FAILURES_NOTIFICATION>}},
    // IDS-110
    {EventIds::CONFIGURATION_FILE_DISCREPANCY_NOTIFICATION,
     CallbackVector{
         &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_CONFIGURATION_FILE_DISCREPANCY_NOTIFICATION>}},
    // IDS-112
    {EventIds::TRUSTED_APPLICATION_INVOCATION,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_TRUSTED_APPLICATION_INVOCATION>}},
    // IDS-113
    {EventIds::EXTERNAL_CONNECTION_INTERFACE_SUCCESSFUL,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_EXTERNAL_CONNECTION_INTERFACE_SUCCESSFUL>}},
    // IDS-114
    {EventIds::EXTERNAL_CONNECTION_INTERFACE_UNSUCCESSFUL,
     CallbackVector{
         createDecodeContextDataHandler<SECEV_EXTERNAL_CONNECTION_INTERFACE_UNSUCCESSFUL>(
             &SecurityEventsEngine::handleExternalConnectionInterfaceUnsuccessfulEvent),
         &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_EXTERNAL_CONNECTION_INTERFACE_UNSUCCESSFUL>}},
    // IDS-115
    {EventIds::NEW_BINDING_INTERFACE_NOTIFICATION,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_NEW_BINDING_INTERFACE_NOTIFICATION>}},
    // IDS-116
    {EventIds::EXTERNAL_INTERFACES_USAGE_STATISTICS,
     CallbackVector{createDecodeContextDataHandler<SECEV_EXTERNAL_INTERFACES_USAGE_STATISTICS>(
         &SecurityEventsEngine::handleExternalInterfacesUsageStatisticsEvent)}},
    // IDS-118
    {EventIds::EXTERNAL_DATA_STORAGE_CONNECTION,
     CallbackVector{createDecodeContextDataHandler<SECEV_EXTERNAL_DATA_STORAGE_CONNECTION>(
         &SecurityEventsEngine::handleExternalDataStorageEvent)}},
    // IDS-120
    {EventIds::EXTERNAL_NEW_HW_CONNECTION,
     CallbackVector{createDecodeContextDataHandler<SECEV_EXTERNAL_NEW_HW_CONNECTION>(
         &SecurityEventsEngine::handleExternalNewHWConnection)}},
    // IDS-121
    {EventIds::EXTERNAL_SOURCES_FILE_DATA_STREAM,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_EXTERNAL_SOURCES_FILE_DATA_STREAM>}},
    // IDS-122
    {EventIds::DIAGNOSTIC_DATA_SET_DOWNLOAD,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_DIAGNOSTIC_DATA_SET_DOWNLOAD>}},
    // IDS-125
    {EventIds::SW_VERIFICATION_FAILURE,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_SW_VERIFICATION_FAILURE>}},
    // IDS-126
    {EventIds::VKMS_KEY_CHANGE,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_VKMS_KEY_CHANGE>}},
    // IDS-127
    {EventIds::VTTL_REGISTRY_CHANGE_REPORTS,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_VTTL_REGISTRY_CHANGE_REPORTS>}},
    // IDS-130
    {EventIds::CONTROL_MODULE_ERROR,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_CONTROL_MODULE_ERROR>}},
    // IDS-131
    {EventIds::KEEP_ALIVE_MESSAGE,
     CallbackVector{
         createDecodeContextDataHandler<SECEV_KEEP_ALIVE_MESSAGE>(&SecurityEventsEngine::handleKeepAliveEvent)}},
    {EventIds::CAN_TIMING_ANOMALY_DETECTED,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_CAN_TIMING_ANOMALY_DETECTED>}},
    {EventIds::UNKNOWN_MESSAGE_DETECTED,
     CallbackVector{&SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_UNKNOWN_MESSAGE_DETECTED>}},
    {EventIds::CANIF_SEV_ERRORSTATE_PASSIVE,
     CallbackVector{&SecurityEventsEngine::HandleCanIfErrorStatus,
                    &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_CANIF_SEV_ERRORSTATE_PASSIVE>}},
    {EventIds::CANIF_SEV_ERRORSTATE_BUSOFF,
     CallbackVector{&SecurityEventsEngine::HandleCanIfErrorStatus,
                    &SecurityEventsEngine::decodeHandleCriticalEvent<SECEV_CANIF_SEV_ERRORSTATE_BUSOFF>}},
    {EventIds::CANIF_SEV_TX_ERROR_DETECTED,
     CallbackVector{&SecurityEventsEngine::HandleRXandTXErrorDetected<SECEV_CANIF_SEV_TX_ERROR_DETECTED>}},
    {EventIds::CANIF_SEV_RX_ERROR_DETECTED,
     CallbackVector{&SecurityEventsEngine::HandleRXandTXErrorDetected<SECEV_CANIF_SEV_RX_ERROR_DETECTED>}}};
// parasoft-end-suppress AUTOSAR-A15_5_3-f
// parasoft-end-suppress AUTOSAR-M15_3_1-a

SecurityEventsEngine::SecurityEventsEngine(SecurityEventsEngineConfig const& engineConfig)
  : SecurityEventEngineCreateEvent(engineConfig.debugCounters,
                                   engineConfig.priority,
                                   engineConfig.msgRepository,
                                   engineConfig.reportSerializer,
                                   engineConfig.eventNoiseFilter)
  , m_debugCounters(engineConfig.debugCounters)
  , m_ipConnectionCountersTable{ipConnectionCountersTableLimit}
  , m_ipDroppedConnectionsTable{ipConnectionCountersTableLimit}
  , m_hostOsLogRateTable{hostOsLogRateTableLimit}
  , m_externalUnsuccessfulConnectionsTable{externalUnsuccessfulConnectionsTableLimit}
  , m_externalInterfacesUsageStatisticsTable{externalInterfacesUsageStatisticsTableLimit}
  , m_processStartStopCountersTable{processStartStopCountersTableLimit}
  , m_keepAliveTimersTable{keepAliveTimersTableLimit}
  , m_keepAliveTimer(engineConfig.timer)
  , m_processCrashRateTable{processCrashRateTableLimit}
  , m_aggregateCrashRateHistogram{m_ratesBins, MAX_BURST}
  , m_serviceRegistryTable{serviceRegistryTableLimit}
  , m_externalNewHWConnectionTable{externalNewHWConnectionTableLimit}
  , m_externalDataStorageTable{externalDataStorageTableLimit}
  , m_droppedBlockedConnectionsTable{droppedBlockedConnectionsTableLimit}
  , m_ethernetServiceInterruptionTable{ethernetServiceInterruptionTableLimit}
  , m_oversizedPacketsHistogramTable{oversizedPacketsHistogramTableLimit}
  , m_invalidTcpDestinationPortCounterTable{invalidAddressDestinationPortCounterTableLimit}
  , m_invalidUdpDestinationPortCounterTable{invalidAddressDestinationPortCounterTableLimit}
  , m_invalidIpv4AddressCounterTable{invalidAddressDestinationPortCounterTableLimit}
  , m_invalidIpv6AddressCounterTable{invalidAddressDestinationPortCounterTableLimit}
  , m_freshnessValueFailedCountersTable{freshnessValueFailedCountersTableLimit}
  , m_disallowedLayer3ProtocolCountersTable{disallowedLayer3ProtocolCountersTableLimit}
  , m_disallowedLayer4ProtocolCountersTable{disallowedLayer4ProtocolCountersTableLimit}
  , m_unusedPortConnectionAttemptsTable{unusedPortConnectionAttemptsTableLimit}
  , m_ipAnomaliesConnectionsCountersTable{ipAnomaliesConnectionsCountersTableLimit}
  , m_macToIpAssociationTable{macToIpAssociationTableLimit}
  , m_doubledIpToMacAssociationTable{doubledIpToMacAssociationTableLimit}
  , m_doubledMacToIpAssociationTable{doubledMacToIpAssociationTableLimit}
  , m_droppedConnectionsCountersTable{droppedConnectionsCountersTableLimit}
  , m_securityEventsCountersTable{securityEventsCountersTableLimit}
  , m_droppedSecurityEventsCountersTable{droppedSecurityEventsCountersTableLimit}
  , m_dhmDroppedSecurityEventsCountersTable{droppedSecurityEventsCountersTableLimit}
  , m_criticalSecurityEventsAlertsCountersTable{criticalSecurityEventsAlertsCountersTableLimit}
  , m_rxtxErrorsCountersTable{rxTxErrorsCountersTableLimit}
  , m_canIfSevErrorStateTable{canIfSevErrorStateTableLimit}
  , m_ethStats(engineConfig.ethStats)
{
    if (m_debugCounters)
    {
        m_failedCounter = m_debugCounters->CreateCounter(
            common::counters::warning::SECURITY_EVENTS_ENGINE_FAILED_PROCESS_COUNTER_NAME,
            EventCounterLevelType::COUNTER_WARNING);
        m_invalidCtxDataLenCounter
            = m_debugCounters->CreateCounter(common::counters::errors::SECURITY_EVENT_SD_INVALID_CONTEXT_DATA_LENGTH,
                                             EventCounterLevelType::COUNTER_ERROR);
        // Wrapper SecurityEventsEngine debug counters
        m_UnknownEventIdAlertCounter = m_debugCounters->CreateCounter(
            common::counters::debug::UNKNOWN_EVENT_ID_ALERT_COUNTER_NAME, EventCounterLevelType::COUNTER_DEBUG);
        m_freshnessValueFailedTableCounter = m_debugCounters->CreateCounter(
            common::counters::debug::FRESHNESS_VALUE_FAILED_COUNTERS_TABLE_UPDATED_COUNTER_NAME,
            EventCounterLevelType::COUNTER_DEBUG);
        m_diagnosticEventSequenceTableCounter = m_debugCounters->CreateCounter(
            common::counters::debug::DIAGNOSTIC_EVENT_SEQUENCE_TABLE_UPDATED_COUNTER_NAME,
            EventCounterLevelType::COUNTER_DEBUG);
        m_SETableCounter
            = m_debugCounters->CreateCounter(common::counters::debug::SECURITY_EVENT__COUNTERS_TABLE_UPDATED_COUNTER_NAME,
                                           EventCounterLevelType::COUNTER_DEBUG);
        m_droppedSETableCounter
            = m_debugCounters->CreateCounter(common::counters::debug::DROPPED_SECURITY_EVENT_TABLE_UPDATED_COUNTER_NAME,
                                           EventCounterLevelType::COUNTER_DEBUG);
        m_criticalSETableCounter
            = m_debugCounters->CreateCounter(common::counters::debug::CRITICAL_SECURITY_EVENT_TABLE_UPDATED_COUNTER_NAME,
                                           EventCounterLevelType::COUNTER_DEBUG);
    }

    auto getConfigParam
        = [engineConfig](auto& param, auto defaultParam, brain::config_keys::ConfigKeyType& key, char const* logPrefix) {
              if (!engineConfig.config || !engineConfig.config->GetValue(key, param))
              {
                  LOG_WARNING << logPrefix << " couldn't be parsed from configuration file" << LOG_NOOP;
                  param = defaultParam;
              }
              LOG_DEBUG << logPrefix << " configured: " << param << LOG_NOOP;
          };

    static constexpr double DEFAULT_SUSPICIOUS_CRASH_THRESHOLD_RATE{0.1};
    static constexpr double DEFAULT_SUSPICIOUS_CRASH_RATE_MAX_BURST{5.0};
    static constexpr double DEFAULT_AGGREGATE_CRASH_THRESHOLD_RATE{1.0};
    static constexpr double DEFAULT_AGGREGATE_CRASH_RATE_MAX_BURST{5.0};

    getConfigParam(m_keepAliveTimeoutPeriod,
                   DefaultKeepAliveTimeoutPeriod,
                   brain::config_keys::KEEP_ALIVE_TIMEOUT_PERIOD,
                   "Keep alive timeout period");
    getConfigParam(m_suspiciousCrashThresholdRate,
                   DEFAULT_SUSPICIOUS_CRASH_THRESHOLD_RATE,
                   brain::config_keys::PROCESS_CRASH_RATE_ALERT_TOKEN_BUCKET_THRESHOLD,
                   "Suspicious crash threshold rate");
    getConfigParam(m_suspiciousCrashRateMaxBurst,
                   DEFAULT_SUSPICIOUS_CRASH_RATE_MAX_BURST,
                   brain::config_keys::PROCESS_CRASH_RATE_ALERT_TOKEN_BUCKET_BURST,
                   "Suspicious crash rate max. burst");
    getConfigParam(m_aggregateCrashThresholdRate,
                   DEFAULT_AGGREGATE_CRASH_THRESHOLD_RATE,
                   brain::config_keys::AGGREGATE_CRASH_RATE_ALERT_TOKEN_BUCKET_THRESHOLD,
                   "Aggregate crash threshold rate");
    getConfigParam(m_aggregateCrashRateMaxBurst,
                   DEFAULT_AGGREGATE_CRASH_RATE_MAX_BURST,
                   brain::config_keys::AGGREGATE_CRASH_RATE_ALERT_TOKEN_BUCKET_BURST,
                   "Aggregate crash rate max. burst");

    m_aggregateCrashRateTokenBucket
        = std::make_unique<PolicerTokenBucket>(m_aggregateCrashThresholdRate, m_aggregateCrashRateMaxBurst);

    LOG_VERBOSE << "Created stats tables" << LOG_NOOP;

    m_natCountersTable = NatCountersTable(engineConfig.config);

    // refactor members - todel rinat comment
    auto const resourceConsumptionNotificationEngine
        = std::make_shared<brain::engines::security_events::ResourceConsumptionNotificationEngine>(
            engineConfig.debugCounters,
            engineConfig.config,
            engineConfig.msgRepository,
            engineConfig.reportSerializer,
            engineConfig.eventNoiseFilter,
            engineConfig.priority);

    m_securityEventEngines[EventIds::RESOURCE_CONSUMPTION_NOTIFICATION].push_back(
        resourceConsumptionNotificationEngine);

    m_statisticsDataHolders.push_back(resourceConsumptionNotificationEngine);
}

namespace brain
{
namespace engines
{
namespace security_events
{
static void
initProtoIpAnomaliesCountersEntry(SecurityEventsEngine::ProtoIpAnomaliesCounters& entry,
                                  const IpAnomaliesCountersEntry&                 value)
{
    entry.idsMInstanceId       = value.GetIdsMInstanceId();
    entry.sensorInstanceId     = value.GetSensorInstanceId();
    entry.busId                = value.GetBusId();
    entry.SourceIpAddress      = value.GetSourceIpAddress();
    entry.sourcePort           = value.GetSourcePort();
    entry.DestinationIpAddress = value.GetDestinationIpAddress();
    entry.destinationPort      = value.GetDestinationPort();
}

static void
initProtoIpOversizedPacketsHistogramEntry(SecurityEventsEngine::ProtoOversizePacketsHistogramEntry& entry,
                                          const OversizedPacketsHistogramEntry&                     value)
{
    entry.idsMInstanceId       = value.GetIdsMInstanceId();
    entry.sensorInstanceId     = value.GetSensorInstanceId();
    entry.busId                = value.GetBusId();
    entry.SourceIpAddress      = value.GetSourceIpAddress();
    entry.sourcePort           = value.GetSourcePort();
    entry.DestinationIpAddress = value.GetDestinationIpAddress();
    entry.destinationPort      = value.GetDestinationPort();
    entry.TransportProtocol    = value.GetTransportProtocol();
}

template <typename T>
bool
isIpAnomaliesEntryValid(T const* event)
{
    return event->hasBusEthIdField() && event->hasSourceIpAddressField() && event->hasDestinationIpAddressField()
           && event->hasSourcePortField() && event->hasDestinationPortRequestField();
}

bool
isIpAnomaliesEntryValid(brain::engines::security_events::SECEV_DETECTED_UNALLOWED_L4_PROTOCOL const* event)
{
    return event->hasBusIdField() && event->hasSourceIpAddressField() && event->hasDestinationIpAddressField()
           && event->hasSourcePortField() && event->hasDestinationPortField();
}

template <typename T>
void
initIpAnomaliesCountersEntry(IpAnomaliesCountersEntry& entry, SecurityEventFrame frame, T const* event)
{
    IpType sourceIp{ConvertIpAddress(event->sourceIpAddress)};
    IpType destinationIp{ConvertIpAddress(event->destinationIpAddress)};

    entry.SetIdsMInstanceId(frame.idsMInstanceID);
    entry.SetSensorInstanceId(frame.sensorInstanceID);
    entry.SetBusId(static_cast<uint16_t>(event->busEthId));
    entry.SetSourceIpAddress(sourceIp);
    entry.SetDestinationIpAddress(destinationIp);
    entry.SetSourcePort(static_cast<uint32_t>(event->sourcePort));
    entry.SetDestinationPort(static_cast<uint32_t>(event->destinationPortRequest));
}

void
initIpAnomaliesCountersEntry(IpAnomaliesCountersEntry&                                                    entry,
                             SecurityEventFrame                                                           frame,
                             brain::engines::security_events::SECEV_DETECTED_UNALLOWED_L4_PROTOCOL const* event)
{
    IpType sourceIp{ConvertIpAddress(event->sourceIpAddress)};
    IpType destinationIp{ConvertIpAddress(event->destinationIpAddress)};

    entry.SetIdsMInstanceId(frame.idsMInstanceID);
    entry.SetSensorInstanceId(frame.sensorInstanceID);
    entry.SetBusId(static_cast<uint16_t>(event->busId));
    entry.SetSourceIpAddress(sourceIp);
    entry.SetDestinationIpAddress(destinationIp);
    entry.SetSourcePort(static_cast<uint32_t>(event->sourcePort));
    entry.SetDestinationPort(static_cast<uint32_t>(event->destinationPort));
}

}  // namespace security_events
}  // namespace engines
}  // namespace brain

void
SecurityEventsEngine::stopKeepAliveTimers()
{
    for (auto& it : m_keepAliveTimersTable)
    {
        common::Timer::TimerRegisterKey registrationKey = it.second;

        if ((common::Timer::TIMER_REGISTRATION_KEY_ERROR != registrationKey)
            && (common::Timer::INVALID_TIMER_REGISTRATION_KEY != registrationKey))
        {
            std::ignore = m_keepAliveTimer->Deregister(registrationKey);
        }
    }
    m_keepAliveTimersTable.clear();
}

SecurityEventsEngine::~SecurityEventsEngine()
{
    try
    {
        stopKeepAliveTimers();
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "destruction of the SecurityEventsEngine failed and got exception." << LOG_NOOP;
    }  // only for parasoft violations
}

bool
SecurityEventsEngine::appendTables(SecurityEventsPeriodicMonitoringData& securityEventsMonitoring, uint64_t startPeriodicReportTimestamp, uint64_t endPeriodicReportTimestamp)
{
    // Add new  element
    if (securityEventsMonitoring.Entries.empty())
    {
        securityEventsMonitoring.Entries.emplace_back();
    }
    auto& newSecurityEventMonitoringData = securityEventsMonitoring.Entries.back();

    newSecurityEventMonitoringData.periodStartTime = startPeriodicReportTimestamp;
    newSecurityEventMonitoringData.periodEndTime   = endPeriodicReportTimestamp;

    // for the refactor - todel rinat comment
    for (auto const& eventHandler : m_statisticsDataHolders)
    {
        if (!eventHandler->FillStatisticData(newSecurityEventMonitoringData))
        {
            return false;
        }
    }

    // Fetch aggregated Connections Counters Table (requirement 2.1)
    for (auto const& entry : m_ipConnectionCountersTable)
    {
        newSecurityEventMonitoringData.IpConnectionCounters.Entries.emplace_back(
            com_vwg_connect_ids_idsperiodicreport_v1_IpConnectionCountersEntry{entry.first.ethIdType,
                                                                               entry.first.vlanTag,
                                                                               entry.second.droppedBlockedConnections,
                                                                               entry.second.successfulConnections});
    }

    // Fetch aggregated Dropped Connections Flows Table	(requirement 2.2)
    for (auto const& entry : m_ipDroppedConnectionsTable)
    {
        newSecurityEventMonitoringData.IpDroppedConnections.Entries.emplace_back();
        auto& newEntry             = newSecurityEventMonitoringData.IpDroppedConnections.Entries.back();
        newEntry.SourceIP          = entry.first.GetSourceIp();
        newEntry.TransportProtocol = entry.first.GetTransportProtocol();
        newEntry.sourcePort        = entry.first.GetSourcePort();
        newEntry.count             = entry.second;
    };

    // Fetch OS Log Rate Histogram Table (requirement 3.1)
    for (auto const& entry : m_hostOsLogRateTable)
    {
        // Traverse entry
        newSecurityEventMonitoringData.HostOsLogRate.Entries.emplace_back();
        auto& newEntry          = newSecurityEventMonitoringData.HostOsLogRate.Entries.back();
        newEntry.idsMInstanceId = entry.first.GetIdsMInstanceId();
        SET_NPB_FIELD(newEntry, sensorInstanceId, entry.first.GetSensorInstanceId());
        newEntry.vmIdentifier      = entry.first.GetVmIdentifier();
        newEntry.has_rateHistogram = true;

        brain::histogram::RateHistogram::BinDataVector histogramData;
        auto                                           getHistogramSucceeded = entry.second.GetHistogramValues(
            histogramData, newEntry.rateHistogram.firstSeenTimeStamp, newEntry.rateHistogram.lastSeenTimeStamp);
        if (!getHistogramSucceeded)
        {
            return false;
        }

        // Traverse histogram
        for (auto const& record : histogramData)
        {
            newEntry.Buckets.emplace_back(
                com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket{static_cast<uint32_t>(record.GetHeight()), static_cast<float>(record.GetInterval())});
        }
    }

    // Fetch Unsuccessful Connections Table (requirement 4.1)
    for (auto const& entry : m_externalUnsuccessfulConnectionsTable)
    {
        newSecurityEventMonitoringData.ExternalUnsuccessfulConnections.Entries.emplace_back();
        auto& newEntry          = newSecurityEventMonitoringData.ExternalUnsuccessfulConnections.Entries.back();
        newEntry.idsMInstanceId = entry.first.GetIdsMInstanceId();
        SET_NPB_FIELD(newEntry, sensorInstanceId, entry.first.GetSensorInstanceId());
        newEntry.connectionType           = entry.first.GetConnectionType();
        newEntry.connectingUnitAddress    = entry.first.GetAddressOfConnectingUnit();
        newEntry.refusalReason            = entry.first.GetRefusalReason();
        newEntry.ConnectionUnitDeviceName = entry.first.GetConnectionUnitDeviceName();
        newEntry.count                    = entry.second;
    }

    // Fetch External Interface Usage Statistics Table
    for (auto const& entry : m_externalInterfacesUsageStatisticsTable)
    {
        newSecurityEventMonitoringData.ExternalInterfacesUsageStatistics.Entries.emplace_back();
        auto& newEntry          = newSecurityEventMonitoringData.ExternalInterfacesUsageStatistics.Entries.back();
        newEntry.idsMInstanceId = entry.first.GetIdsMInstanceId();
        SET_NPB_FIELD(newEntry, sensorInstanceId, entry.first.GetSensorInstanceId());
        newEntry.connectionType          = entry.first.GetConnectionType();
        newEntry.layerType               = entry.first.GetLayerType();
        newEntry.newSessionsInLayerCount = entry.second.newSessionsInLayerCount;
        newEntry.totalPacketsPassed      = entry.second.totalPacketsPassed;
        newEntry.totalBytesPassed        = entry.second.totalBytesPassed;
    }

    // Fetch Process Start Stop Counters Table
    for (auto const& entry : m_processStartStopCountersTable)
    {
        newSecurityEventMonitoringData.ProcessStartStopCounters.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.ProcessStartStopCounters.Entries.back();

        newEntry.sensorInstanceId       = entry.first.GetSensorInstanceId();
        newEntry.idsMInstanceId         = entry.first.GetIdsMInstanceId();
        newEntry.vmIdentifier           = entry.first.GetVmIdentifier();
        newEntry.groupId                = entry.first.GetGroupId();
        newEntry.AdaptiveAutosarAppName = entry.first.GetAdaptiveAutosarAppName();
        newEntry.ProcessCommandLine     = entry.first.GetProcessCommandLine();
        newEntry.startCount             = std::get<PROCESS_START_COUNTER>(entry.second);
        newEntry.stopCount              = std::get<PROCESS_STOP_COUNTER>(entry.second);
    }

    // Fetch Service Registry Table	(requirement 4.1 HCP3 GBT)
    for (auto const& entry : m_serviceRegistryTable)
    {
        newSecurityEventMonitoringData.ServiceRegistry.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.ServiceRegistry.Entries.back();

        newEntry.idsMInstanceID = entry.first.GetIdsMInstanceId();
        SET_NPB_FIELD(newEntry, sensorInstanceID, entry.first.GetSensorInstanceId());
        newEntry.serviceRegistryId        = entry.first.GetServiceRegistryId();
        newEntry.RegisteredService        = entry.first.GetRegisteredService();
        newEntry.RegisteringApplicationId = entry.first.GetRegisteringApplicationId();
        newEntry.RegisteringServerIP      = entry.first.GetRegisteringServerIP();
        newEntry.indicator                = entry.first.GetIndicator();

        newEntry.count = entry.second;
    }

    // Process Crash Rate Table	(requirement 3.7 HCP3 GBT)
    for (auto const& entry : m_processCrashRateTable)
    {
        // Traverse entry
        newSecurityEventMonitoringData.ProcessCrashRate.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.ProcessCrashRate.Entries.back();

        newEntry.idsMInstanceID                = entry.first.GetIdsMInstanceId();
        newEntry.sensorInstanceID              = entry.first.GetSensorInstanceId();
        newEntry.vmIdentifier                  = entry.first.GetVmIdentifier();
        newEntry.ProcessName                   = entry.first.GetProcessName();
        newEntry.typeOfError                   = entry.first.GetTypeOfError();
        newEntry.crashReason                   = entry.first.GetCrashReason();
        newEntry.has_processCrashRateHistogram = true;

        brain::histogram::RateHistogram::BinDataVector histogramData;
        auto                                           getHistogramSucceeded = std::get<0>(entry.second)
                                         .GetHistogramValues(histogramData,
                                                             newEntry.processCrashRateHistogram.firstSeenTimeStamp,
                                                             newEntry.processCrashRateHistogram.lastSeenTimeStamp);
        if (!getHistogramSucceeded)
        {
            return false;
        }

        // Traverse histogram
        for (auto const& record : histogramData)
        {
            newEntry.Buckets.emplace_back(com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket{
                static_cast<uint32_t>(record.GetHeight()), static_cast<float>(record.GetInterval())});
        }
    }

    // Fetch External new HW connection storage Table (requirement 6.1 HCP3 GBT)
    for (auto const& entry : m_externalNewHWConnectionTable)
    {
        newSecurityEventMonitoringData.ExternalNewHWConnection.Entries.emplace_back();
        auto& newEntry          = newSecurityEventMonitoringData.ExternalNewHWConnection.Entries.back();
        newEntry.idsMInstanceID = entry.first.GetIdsMInstanceId();
        SET_NPB_FIELD(newEntry, sensorInstanceID, entry.first.GetSensorInstanceId());
        newEntry.connectionType                  = entry.first.GetConnectionType();
        newEntry.HardwareIdSerial                = entry.first.GetHardwareIdSerialNumber();
        newEntry.DeviceSubClasses                = entry.first.GetDeviceSubClasses();
        newEntry.CalledLriverLibrary             = entry.first.GetCalledDriverLibrary();
        newEntry.HandlingConnectionDriverLibrary = entry.first.GetHandlingConnectionDriverLibrary();
        newEntry.count                           = entry.second;
    };

    // Fetch External Data Storage Table (requirement 5.1 HCP3 GBT)
    for (auto const& entry : m_externalDataStorageTable)
    {
        newSecurityEventMonitoringData.ExternalDataStorage.Entries.emplace_back();
        auto& newEntry          = newSecurityEventMonitoringData.ExternalDataStorage.Entries.back();
        newEntry.idsMInstanceID = entry.first.GetIdsMInstanceId();
        SET_NPB_FIELD(newEntry, sensorInstanceID, entry.first.GetSensorInstanceId());
        newEntry.connectionType         = entry.first.GetConnectionType();
        newEntry.fileSystem             = entry.first.GetFileSystem();
        newEntry.HardwareIdSerialNumber = entry.first.GetHardwareIdSerialNumber();
        newEntry.count                  = entry.second;
    };

    // Fetch Dropped/Blocked Connections Table (requirement 59)
    for (auto const& entry : m_droppedBlockedConnectionsTable)
    {
        newSecurityEventMonitoringData.DroppedBlockedConnections.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.DroppedBlockedConnections.Entries.back();

        initProtoIpAnomaliesCountersEntry(newEntry, entry.first);

        newEntry.count = entry.second;
    }

    // Fetch Disallowed Layer 3 Protocol Counters Table (requirement 71)
    for (auto const& entry : m_disallowedLayer3ProtocolCountersTable)
    {
        newSecurityEventMonitoringData.DisallowedLayer3ProtocolCounters.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.DisallowedLayer3ProtocolCounters.Entries.back();

        initProtoIpAnomaliesCountersEntry(newEntry, entry.first);

        auto const& optProtocolId{entry.first.GetProtocolId()};
        INIT_NPB_FIELD(newEntry, protocolId, optProtocolId);
        newEntry.count = entry.second;
    }

    // Fetch Ethernet Service Interruption Table (Ethernet Anomalies Monitoring)
    for (auto const& entry : m_ethernetServiceInterruptionTable)
    {
        newSecurityEventMonitoringData.EthernetServiceInterruption.Entries.emplace_back();
        auto& newEntry          = newSecurityEventMonitoringData.EthernetServiceInterruption.Entries.back();
        newEntry.idsMInstanceID = entry.first.GetIdsMInstanceId();
        SET_NPB_FIELD(newEntry, sensorInstanceID, entry.first.GetSensorInstanceId());
        newEntry.busId               = entry.first.GetBusId();
        newEntry.comServerIdentifier = entry.first.GetComServerIdentifier();
        newEntry.count               = entry.second;
    }

    // Dropped TCP packet because of invalid destination TCP-Port
    for (auto const& entry : m_invalidTcpDestinationPortCounterTable)
    {
        newSecurityEventMonitoringData.InvalidTcpDestinationPortCounter.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.InvalidTcpDestinationPortCounter.Entries.back();

        initProtoIpAnomaliesCountersEntry(newEntry, entry.first);

        SET_NPB_FIELD(newEntry, fwRuleId, entry.first.GetFwRuleId());
        newEntry.count = entry.second;
    }

    for (auto const& entry : m_invalidUdpDestinationPortCounterTable)
    {
        newSecurityEventMonitoringData.InvalidUdpDestinationPortCounter.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.InvalidUdpDestinationPortCounter.Entries.back();

        initProtoIpAnomaliesCountersEntry(newEntry, entry.first);

        SET_NPB_FIELD(newEntry, fwRuleId, entry.first.GetFwRuleId());
        newEntry.count = entry.second;
    }

    for (auto const& entry : m_invalidIpv4AddressCounterTable)
    {
        newSecurityEventMonitoringData.InvalidIpv4AddressCounter.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.InvalidIpv4AddressCounter.Entries.back();

        initProtoIpAnomaliesCountersEntry(newEntry, entry.first);

        SET_NPB_FIELD(newEntry, fwRuleId, entry.first.GetFwRuleId());
        newEntry.count = entry.second;
    }

    for (auto const& entry : m_invalidIpv6AddressCounterTable)
    {
        newSecurityEventMonitoringData.InvalidIpv6AddressCounter.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.InvalidIpv6AddressCounter.Entries.back();

        initProtoIpAnomaliesCountersEntry(newEntry, entry.first);

        SET_NPB_FIELD(newEntry, fwRuleId, entry.first.GetFwRuleId());
        newEntry.count = entry.second;
    }

    for (auto const& entry : m_disallowedLayer4ProtocolCountersTable)
    {
        newSecurityEventMonitoringData.DisallowedLayer4ProtocolCounters.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.DisallowedLayer4ProtocolCounters.Entries.back();

        initProtoIpAnomaliesCountersEntry(newEntry, entry.first);

        SET_NPB_FIELD(newEntry, fwRuleId, entry.first.GetFwRuleId());
        newEntry.count = entry.second;
    }

    for (auto const& entry : m_unusedPortConnectionAttemptsTable)
    {
        newSecurityEventMonitoringData.UnusedPortConnectionAttempts.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.UnusedPortConnectionAttempts.Entries.back();

        initProtoIpAnomaliesCountersEntry(newEntry, entry.first);

        newEntry.TransportProtocol = entry.first.GetTransportProtocol();
        newEntry.count             = entry.second;
    }

    for (auto const& entry : m_oversizedPacketsHistogramTable)
    {
        newSecurityEventMonitoringData.OversizedPacketsHistogram.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.OversizedPacketsHistogram.Entries.back();

        initProtoIpOversizedPacketsHistogramEntry(newEntry, entry.first);

        newEntry.has_oversizedPacketsHistogram = true;
        brain::histogram::ScalarHistogram::BinDataVector histogramData;
        uint64_t                                         firstHistogramTs{};
        uint64_t                                         lastHistogramTs{};
        auto getHistogramSucceeded = entry.second.GetHistogramValues(histogramData, firstHistogramTs, lastHistogramTs);
        if (!getHistogramSucceeded)
        {
            return false;
        }
        newEntry.has_oversizedPacketsHistogram                = true;
        newEntry.oversizedPacketsHistogram.firstSeenTimeStamp = firstHistogramTs;
        newEntry.oversizedPacketsHistogram.lastSeenTimeStamp  = lastHistogramTs;
        for (auto const& record : histogramData)
        {
            newEntry.OversizedPacketsHistogram.emplace_back(com_vwg_connect_ids_idsperiodicreport_v1_Bucket{
                static_cast<uint32_t>(record.GetHeight()), static_cast<uint32_t>(record.GetInterval())});
        }
    }

    // IDS shall monitor the security events related to diagnostics and record the timestamp and eventID of each one
    for (auto const& entry : m_diagnosticEventSequenceTable)
    {
        newSecurityEventMonitoringData.DiagnosticEventSequence.Entries.emplace_back();
        auto& newEntry           = newSecurityEventMonitoringData.DiagnosticEventSequence.Entries.back();
        newEntry.securityEventID = entry.GetSecurityEventID();
        newEntry.timestamp       = entry.GetTimestamp();
    }


    for (auto const& entry : m_freshnessValueFailedCountersTable)
    {
        newSecurityEventMonitoringData.FreshnessValueFailedCounters.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.FreshnessValueFailedCounters.Entries.back();

        newEntry.idsMInstanceID = entry.first.GetIdsMInstanceId();
        SET_NPB_FIELD(newEntry, sensorInstanceID, entry.first.GetSensorInstanceId());
        newEntry.fvmErrorCode = entry.first.GetFvmErrorCode();
        newEntry.pduId        = entry.first.GetPduId();

        newEntry.count = entry.second;
    }

    // Connections Counters Table
    for (auto const& entry : m_ipAnomaliesConnectionsCountersTable)
    {
        newSecurityEventMonitoringData.IpAnomaliesConnectionsCounters.Entries.emplace_back();
        auto& protoEntry = newSecurityEventMonitoringData.IpAnomaliesConnectionsCounters.Entries.back();

        protoEntry.idsMInstanceId                        = entry.first.GetIdsMInstanceId();
        protoEntry.sensorInstanceId                      = entry.first.GetSensorInstanceId();
        protoEntry.ethIdType                             = entry.first.GetEthIdType();
        protoEntry.firewallId                            = entry.first.GetFirewallId();
        protoEntry.filterRuleId                          = entry.first.GetFilterRuleId();
        protoEntry.FilterRule                            = entry.first.GetFilterRule();
        protoEntry.IncomingPackageInterface              = entry.first.GetIncomingPackageInterface();
        protoEntry.OutgoingPackageInterface              = entry.first.GetOutgoingPackageInterface();
        protoEntry.SourceIpAddress                       = entry.first.GetSourceIpAddress();
        protoEntry.DestinationIpAddress                  = entry.first.GetDestinationIpAddress();
        protoEntry.TmProtocol                            = entry.first.GetTmProtocol();
        protoEntry.sourcePort                            = entry.first.GetSourcePort();
        protoEntry.destinationPort                       = entry.first.GetDestinationPort();
        protoEntry.sourceMacAddress                      = entry.first.GetSourceMacAddress();
        protoEntry.destinationMacAddress                 = entry.first.GetDestinationMacAddress();
        protoEntry.vlanTag                               = entry.first.GetVlanTag();
        protoEntry.PayloadLength                         = entry.second.PayloadLength;
        protoEntry.droppedBlockedConnectionAttemptsCount = entry.second.DroppedBlockedConnectionAttemptsCount;
        protoEntry.successfullConnectionAttemptsCount    = entry.second.SuccessfullConnectionAttemptsCount;
        protoEntry.droppedNotificationsCount             = entry.second.DroppedNotificationsCount;
    }

    // MAC to IP Association Table
    for (auto const& entry : m_macToIpAssociationTable)
    {
        newSecurityEventMonitoringData.MacToIpAssociationCounters.Entries.emplace_back();
        auto& protoEntry = newSecurityEventMonitoringData.MacToIpAssociationCounters.Entries.back();

        protoEntry.IpAddress        = entry.first.GetIpAddress();
        protoEntry.macAddress       = entry.first.GetMacAddress();
        protoEntry.createdTimestamp = entry.second.CreatedTimestamp;
        protoEntry.updatedTimestamp = entry.second.UpdatedTimestamp;
        protoEntry.counter          = entry.second.Counter;
    }

    for (auto const& entry : m_droppedConnectionsCountersTable)
    {
        newSecurityEventMonitoringData.DroppedConnectionCounters.Entries.emplace_back();
        auto& protoEntry = newSecurityEventMonitoringData.DroppedConnectionCounters.Entries.back();

        protoEntry.idsMInstanceId            = entry.first.GetIdsMInstanceId();
        protoEntry.sensorInstanceId          = entry.first.GetSensorInstanceId();
        protoEntry.serviceVersion            = entry.first.GetServiceVersion();
        protoEntry.firewallId                = entry.first.GetFirewallId();
        protoEntry.filterRuleId              = entry.first.GetFilterRuleId();
        protoEntry.FilterRule                = entry.first.GetFilterRule();
        protoEntry.IncomingPackageInterface  = entry.first.GetIncomingPackageInterface();
        protoEntry.OutgoingPackageInterface  = entry.first.GetOutgoingPackageInterface();
        protoEntry.SourceIpAddress           = entry.first.GetSourceIpAddress();
        protoEntry.DestinationIpAddress      = entry.first.GetDestinationIpAddress();
        protoEntry.TransportProtocol         = entry.first.GetTransportProtocol();
        protoEntry.sourcePort                = entry.first.GetSourcePort();
        protoEntry.destinationPort           = entry.first.GetDestinationPort();
        protoEntry.UserName                  = entry.first.GetUserName();
        protoEntry.ProcessName               = entry.first.GetProcessName();
        protoEntry.droppedNotificationsCount = entry.second.DroppedNotificationsCount;
        protoEntry.droppedPackagesCount      = entry.second.DroppedPackagesCount;
    }

    // Fetch Link Utilization Histogram & Ethernet Switches Counters Tables (Ethernet Anomalies Monitoring)
    if (!fetchEthStats(newSecurityEventMonitoringData))
    {
        return false;
    }

    // Fetch Security Events Counters Table
    for (auto const& entry : m_securityEventsCountersTable)
    {
        newSecurityEventMonitoringData.SecurityEventsCounters.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.SecurityEventsCounters.Entries.back();

        newEntry.idsMInstanceId = entry.first.GetIdsMInstanceId();
        SET_NPB_FIELD(newEntry, sensorInstanceId, entry.first.GetSensorInstanceId());
        newEntry.securityEventId = entry.first.GetSecurityEventId();

        newEntry.count = entry.second;
    }

    // Fetch Dropped Security Events Counters Table
    for (auto const& entry : m_droppedSecurityEventsCountersTable)
    {
        newSecurityEventMonitoringData.DroppedSecurityEventsCounters.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.DroppedSecurityEventsCounters.Entries.back();

        newEntry.idsMInstanceID = entry.first.GetIdsMInstanceId();
        SET_NPB_FIELD(newEntry, sensorInstanceID, entry.first.GetSensorInstanceId());
        newEntry.eventId    = entry.first.GetSecurityEventId();
        newEntry.DropReason = entry.first.GetDropReason();
        newEntry.count      = entry.second;
    }

    for (auto const& entry : m_dhmDroppedSecurityEventsCountersTable)
    {
        newSecurityEventMonitoringData.DroppedSecurityEventsCounters.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.DroppedSecurityEventsCounters.Entries.back();

        newEntry.ConstraintId = brain::sensor_data::swpac::GetConstraintIdString(entry.first.GetConstraintId());
        newEntry.DropReason = DropReasonMap.at(entry.first.GetDropReason());
        newEntry.count = entry.second;
    }

    // Fetch Critical Security Events Alerts Counters Table
    for (auto const& entry : m_criticalSecurityEventsAlertsCountersTable)
    {
        newSecurityEventMonitoringData.CriticalSecurityEventsAlertsCounters.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.CriticalSecurityEventsAlertsCounters.Entries.back();

        newEntry.securityEventId = static_cast<uint32_t>(entry.first);
        newEntry.count           = entry.second;
    }

    for (auto const& entry : m_rxtxErrorsCountersTable)
    {
        newSecurityEventMonitoringData.RxTxErrors.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.RxTxErrors.Entries.back();

        newEntry.busId            = entry.first.GetBusId();
        newEntry.canId            = entry.first.GetCanId();
        newEntry.controllerId     = entry.first.GetControllerId();
        newEntry.errorType        = entry.first.GetErrorType();
        newEntry.idsMInstanceID   = entry.first.GetIdsMInstanceId();
        newEntry.sensorInstanceID = entry.first.GetSensorInstanceId();
        newEntry.count            = entry.second;
    }

    for (auto const& entry : m_canIfSevErrorStateTable)
    {
        newSecurityEventMonitoringData.BusOffStatistics.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.BusOffStatistics.Entries.back();

        newEntry.idsMInstanceID   = entry.first.GetIdsMInstanceId();
        newEntry.sensorInstanceID = entry.first.GetSensorInstanceId();
        newEntry.state            = entry.first.GetState();
        newEntry.count            = entry.second;
    }

    // Reset tables at end of monitoring period
    resetTables();

    return true;
}

void
SecurityEventsEngine::resetTables()
{
    // for the refactor - todel rinat comment
    for (auto const& eventHandler : m_statisticsDataHolders)
    {
        eventHandler->ResetStatisticData();
    }
    // ConMod
    m_ipConnectionCountersTable.clear();
    m_ipDroppedConnectionsTable.clear();
    m_hostOsLogRateTable.clear();
    m_externalUnsuccessfulConnectionsTable.clear();
    m_externalInterfacesUsageStatisticsTable.clear();
    m_processStartStopCountersTable.clear();
    m_droppedBlockedConnectionsTable.clear();
    m_ethernetServiceInterruptionTable.clear();
    m_ethStats->ClearSomeIpStats();
    m_invalidTcpDestinationPortCounterTable.clear();
    m_invalidUdpDestinationPortCounterTable.clear();
    m_invalidIpv4AddressCounterTable.clear();
    m_invalidIpv6AddressCounterTable.clear();
    m_diagnosticEventSequenceTable.clear();
    m_disallowedLayer3ProtocolCountersTable.clear();
    m_disallowedLayer4ProtocolCountersTable.clear();
    m_unusedPortConnectionAttemptsTable.clear();
    m_freshnessValueFailedCountersTable.clear();
    m_securityEventsCountersTable.clear();
    m_oversizedPacketsHistogramTable.clear();
    m_ipAnomaliesConnectionsCountersTable.clear();
    m_macToIpAssociationTable.clear();
    m_droppedConnectionsCountersTable.clear();
    // HCP3
    m_serviceRegistryTable.clear();
    m_processCrashRateTable.clear();
    m_externalDataStorageTable.clear();
    m_externalNewHWConnectionTable.clear();
    // Security Events Digesting
    m_droppedSecurityEventsCountersTable.clear();
    m_dhmDroppedSecurityEventsCountersTable.clear();
    m_criticalSecurityEventsAlertsCountersTable.clear();
    //HCP1 or SACID
    m_rxtxErrorsCountersTable.clear();
    m_canIfSevErrorStateTable.clear();

    // ConMod
    m_ipConnectionCountersTable.ResetFailedAllocations();
    m_ipDroppedConnectionsTable.ResetFailedAllocations();
    m_hostOsLogRateTable.ResetFailedAllocations();
    m_externalUnsuccessfulConnectionsTable.ResetFailedAllocations();
    m_externalInterfacesUsageStatisticsTable.ResetFailedAllocations();
    m_processStartStopCountersTable.ResetFailedAllocations();
    m_droppedBlockedConnectionsTable.ResetFailedAllocations();
    m_ethernetServiceInterruptionTable.ResetFailedAllocations();
    m_invalidTcpDestinationPortCounterTable.ResetFailedAllocations();
    m_invalidUdpDestinationPortCounterTable.ResetFailedAllocations();
    m_invalidIpv4AddressCounterTable.ResetFailedAllocations();
    m_invalidIpv6AddressCounterTable.ResetFailedAllocations();
    m_disallowedLayer3ProtocolCountersTable.ResetFailedAllocations();
    m_disallowedLayer4ProtocolCountersTable.ResetFailedAllocations();
    m_unusedPortConnectionAttemptsTable.ResetFailedAllocations();
    m_freshnessValueFailedCountersTable.ResetFailedAllocations();
    m_securityEventsCountersTable.ResetFailedAllocations();
    m_oversizedPacketsHistogramTable.ResetFailedAllocations();
    m_ipAnomaliesConnectionsCountersTable.ResetFailedAllocations();
    m_macToIpAssociationTable.ResetFailedAllocations();
    m_droppedConnectionsCountersTable.ResetFailedAllocations();
    // HCP3
    m_serviceRegistryTable.ResetFailedAllocations();
    m_processCrashRateTable.ResetFailedAllocations();
    m_externalDataStorageTable.ResetFailedAllocations();
    m_externalNewHWConnectionTable.ResetFailedAllocations();
    // Security Events Digesting
    m_droppedSecurityEventsCountersTable.ResetFailedAllocations();
    m_dhmDroppedSecurityEventsCountersTable.ResetFailedAllocations();
    m_criticalSecurityEventsAlertsCountersTable.ResetFailedAllocations();
        //HCP1 or SACID
    m_rxtxErrorsCountersTable.ResetFailedAllocations();
    m_canIfSevErrorStateTable.ResetFailedAllocations();
}

bool
SecurityEventsEngine::appendHistograms(SecurityEventsPeriodicMonitoringData& securityEventsMonitoring)
{
    if (securityEventsMonitoring.Entries.empty())
    {
        return false;
    }
    auto& newEntry = securityEventsMonitoring.Entries.back();

    // HCP3
    if (!m_aggregateCrashRateHistogram.Empty())
    {
        newEntry.has_aggregatedCrashRateHistogram = true;

        brain::histogram::RateHistogram::BinDataVector histogramData;
        auto                                           getHistogramSucceeded
            = m_aggregateCrashRateHistogram.GetHistogramValues(histogramData,
                                                               newEntry.aggregatedCrashRateHistogram.firstSeenTimeStamp,
                                                               newEntry.aggregatedCrashRateHistogram.lastSeenTimeStamp);
        if (!getHistogramSucceeded)
        {
            return false;
        }

        // Traverse histogram
        for (auto const& record : histogramData)
        {
            newEntry.AggregatedCrashRateHistogramBuckets.emplace_back(
                com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket{static_cast<uint32_t>(record.GetHeight()),
                                                                     static_cast<float>(record.GetInterval())});
        }
    }

    // Reset histograms at end of monitoring period
    // HCP3
    m_aggregateCrashRateHistogram.ClearHistogramContents();

    return true;
}

void
SecurityEventsEngine::HandleCanIfErrorStatus(SecurityEventSensorData& sd)
{
    auto const eventFrame = sd.GetEventFrame();

    CanIfSevErrorStateEntry entry{
        eventFrame.idsMInstanceID,
        eventFrame.sensorInstanceID,
        static_cast<uint8_t>(sd.GetEventId() == EventIds::CANIF_SEV_ERRORSTATE_PASSIVE ? 0U : 1U)};
    m_canIfSevErrorStateTable[entry] += eventFrame.count;
}

void
SecurityEventsEngine::HandleDiagnosticEventSequence(SecurityEventSensorData& sd)
{
    auto createEntry = [this](uint64_t timestamp, uint16_t idSE) {
        LOG_DEBUG << "Diagnostic Security Event: timestamp=" << timestamp << "l, idSE=" << idSE << LOG_NOOP;
        m_diagnosticEventSequenceTable.push_back({timestamp, idSE});
        common::counters::IncreaseCounter(m_diagnosticEventSequenceTableCounter);
    };

    auto const idSE      = sd.GetEventId();
    auto const timestamp = sd.GetTimestamp();
    switch (idSE)
    {
    case DIAG_SEV_WRITE_INVALID_DATA:
    case DIAG_SEV_SECURITY_ACCESS_DENIED:
    case DIAG_SEV_COMMUNICATION_CONTROL_SWITCHED_OFF:
    case DIAG_SEV_SERVICE_NOT_SUPPORTED:
    case DIAG_SEV_SUBFUNCTION_NOT_SUPPORTED:
    case DIAG_SEV_INCORRECT_MESSAGE_LENGTH_OR_FORMAT:
    case DIAG_SEV_REQUEST_SEQUENCE_ERROR:
    case DIAG_SEV_REQUEST_OUT_OF_RANGE:
    case DIAG_SEV_REQUESTED_ACTIONS_REQUIRES_AUTHENTICATION:
    case DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED:
    case DIAG_SEV_SECURITY_ACCESS_INVALID_KEY:
    case DIAG_SEV_SECURITY_ACCESS_REQUIRED_TIME_DELAY_NOT_EXPIRED:
    case DIAG_SEV_NUMBER_OF_FAILED_AUTHENTICATION_ATTEMPTS_EXCEEDED:
    case DIAG_SEV_CERTIFICATE_FAILURE:
        m_diagnosticFailureIndication = true;
        createEntry(timestamp, idSE);
        break;
    case DIAG_SEV_ECU_UNLOCK_SUCCESSFUL:
        createDiagSevEcuUnlockSuccessfulAlert(sd);
        // falls through
    case DIAG_SEV_AUTHENTICATION_SUCCESSFUL:
    case DIAG_SEV_CLEAR_DTC_SUCCESSFUL:
    case DIAG_SEV_ECU_RESET:
    case DIAG_SEV_WRITE_DATA:
    case DIAG_SEV_REQUEST_DOWNLOAD:
    case DIAG_SEV_DTC_SETTING_SWITCHED_OFF:
        createEntry(timestamp, idSE);
        break;
    default:
        // should not happen because this callback must be added only on the above SE, but just in case
        common::counters::IncreaseCounter(m_failedCounter);
        LOG_ERROR << idSE << " is not a diagnostics SE that must be checked" << LOG_NOOP;
    }
}

void
SecurityEventsEngine::createDiagSevEcuUnlockSuccessfulAlert(SecurityEventSensorData& sd)
{
    if (m_diagnosticFailureIndication)
    {
        m_diagnosticFailureIndication = false;

        // send the event
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
            = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
        createSecurityEventAlert(ruleEval, sd, SecurityEventType::Normal, EventIds::DIAG_SEV_ECU_UNLOCK_SUCCESSFUL);
        if (!addEventAlert(ruleEval, CriticalEventAlert::SuspiciousAlertEventName, sd))
        {
            common::counters::IncreaseCounter(m_failedCounter);
            HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        }
    }
    else
    {
        LOG_DEBUG << "DIAG_SEV_ECU_UNLOCK_SUCCESSFUL event without diagnostic failure indication" << LOG_NOOP;
    }
}

void
SecurityEventsEngine::createErroneousServiceRegistrationAlert(
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval, SecurityEventSensorData& sd)
{
    com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData securityEventAlert
        = com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_init_default;
    std::ignore = CreateSecurityEventData(securityEventAlert, sd);

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    
    ruleEval.which_RuleData = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_erroneousServiceRegistrationAlert_tag);
    ruleEval.RuleData.erroneousServiceRegistrationAlert = securityEventAlert;

    auto eventFrame = sd.GetEventFrame();
    LOG_DEBUG << "create ErroneousServiceRegistrationAlert:"
              << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
              << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
              << ",eventDefinitionId=" << static_cast<uint32_t>(eventFrame.eventDefinitionId) << LOG_NOOP;
}

void
SecurityEventsEngine::handleErroneousServiceRegistrationAlert(SecurityEventSensorData& securityEventSD)
{
    // Handle rule evaluation
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
    createErroneousServiceRegistrationAlert(ruleEval, securityEventSD);
    if (!addEventAlert(ruleEval, CriticalEventAlert::ErroneousServiceRegistration, securityEventSD))
    {
        common::counters::IncreaseCounter(m_failedCounter);
        HandleDroppedSecurityEvent(securityEventSD, DropReason::SecurityEventsEngine);
    }
}

bool
SecurityEventsEngine::encodeShadowNatTableData(pb_ostream_t* stream, pb_field_t const* fields, void* const* arg)
{
    auto const& natEntries = **reinterpret_cast<std::list<NatCountersEntriesStruct>* const*>(arg);
    for (auto const& entry : natEntries)
    {
        com_vwg_connect_ids_idsperiodicreport_v1_ShadowNatEntry sntr
            = com_vwg_connect_ids_idsperiodicreport_v1_ShadowNatEntry_init_default;
        sntr.externalServerIpAddress     = entry.m_externalServerIpAddress;
        sntr.externalTransportSourcePort = entry.m_externalTransportSourcePort;
        sntr.internalIpAddress           = common::nanopb::CreateEncodingCallback(entry.m_internalIpAddress);
        sntr.internalTransportSourcePort = entry.m_internalTransportSourcePort;
        sntr.transportProtocol           = entry.m_transportProtocol;

        if ((!pb_encode_tag_for_field(stream, fields))
            || (!pb_encode_submessage(stream, com_vwg_connect_ids_idsperiodicreport_v1_ShadowNatEntry_fields, &sntr)))
        {
            return false;
        }
    }

    return true;
}

void
SecurityEventsEngine::createNatTableAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                                          SecurityEventSensorData const&                           sd,
                                          NatCountersTableValue const&                             natTable,
                                          NatTableEvent                                            natTableEvent,
                                          SECEV_NAT_UPDATE_REPORTS const*                          event)
{
    com_vwg_connect_ids_idsperiodicreport_v1_NatUpdateReportAlert natEventAlert
        = com_vwg_connect_ids_idsperiodicreport_v1_NatUpdateReportAlert_init_default;

    ruleEval.ruleEvaluationId               = m_currentTime;
    ruleEval.timestamp                      = m_currentTime;
    natEventAlert.configurableMaxTableSize  = m_natCountersTable.GetMaxNatTableSize();
    auto const eventFrame                   = sd.GetEventFrame();
    natEventAlert.has_eventFrame            = true;
    auto& natEventFrame                     = natEventAlert.eventFrame;
    natEventFrame.protocolHeaderContextData = eventFrame.protocolHeaderContextData;
    natEventFrame.protocolHeaderSignature   = eventFrame.protocolHeaderSignature;
    natEventFrame.protocolHeaderTimestamp   = eventFrame.protocolHeaderTimestamp;
    natEventFrame.protocolHeaderReserved    = eventFrame.protocolHeaderReserved;
    natEventFrame.protocolVersion           = eventFrame.protocolVersion;
    natEventFrame.sensorInstanceID          = eventFrame.sensorInstanceID;
    natEventFrame.idsMInstanceID            = eventFrame.idsMInstanceID;
    natEventFrame.eventDefinitionId         = eventFrame.eventDefinitionId;
    natEventFrame.count                     = eventFrame.count;
    natEventFrame.reserved                  = eventFrame.reserved;

    natEventAlert.has_securityEventTimestamp = true;
    natEventAlert.securityEventTimestamp.timestampNano     = sd.GetAutosarTimestampNano();
    natEventAlert.securityEventTimestamp.timestampSource   = sd.GetAutosarTimestampSource();
    natEventAlert.securityEventTimestamp.timestampReserved = sd.GetAutosarTimestampReserved();
    natEventAlert.securityEventTimestamp.timestampSeconds  = sd.GetAutosarTimestampSeconds();

    natEventAlert.uid           = event->uid;
    natEventAlert.successBit    = event->successBit;
    natEventAlert.natIdentifier = event->natIdentifier;
    natEventAlert.operationType = event->operationType;

    m_eventDataToSerialize.resize(1);
    m_eventDataToSerialize[0]
        = {reinterpret_cast<uint8_t const*>(&event->internalIpAddress), sizeof(event->internalIpAddress)};
    natEventAlert.internalIpAddress           = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0]);
    natEventAlert.externalServerIpAddress     = event->externalServerIpAddress;
    natEventAlert.transportProtocol           = event->transportProtocol;
    natEventAlert.internalTransportSourcePort = event->internalTransportSourcePort;
    natEventAlert.externalTransportSourcePort = event->externalTransportSourcePort;

    natEventAlert.has_natTable                           = true;
    natEventAlert.natTable.shadowNatEntries.arg          = const_cast<NatCountersTableValue*>(&natTable);
    natEventAlert.natTable.shadowNatEntries.funcs.encode = &encodeShadowNatTableData;

    ruleEval.which_RuleData
        = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_natTableAlert_tag);

    switch (natTableEvent)
    {
    case NatTableEvent::NAT_FLOODING_ALERT:
        natEventAlert.alertString = common::nanopb::CreateEncodingLiteralStringCallback(
            GetCriticalEventString(CriticalEventAlert::NatFloodingAlertText).c_str());
        break;
    case NatTableEvent::NAT_ENTRY_NOT_FOUND_ALERT:
        natEventAlert.alertString = common::nanopb::CreateEncodingLiteralStringCallback(
            GetCriticalEventString(CriticalEventAlert::NatEntryNotFountAlertText).c_str());
        break;
    case NatTableEvent::NAT_DUPLICATE_ENTRY_ALERT:
        natEventAlert.alertString = common::nanopb::CreateEncodingLiteralStringCallback(
            GetCriticalEventString(CriticalEventAlert::NatDuplicateEntryText).c_str());
        break;
    default:
        break;
    }
    ruleEval.RuleData.natTableAlert = natEventAlert;
}

void
SecurityEventsEngine::handleNatTableEvents(SecurityEventSensorData& sd, SECEV_NAT_UPDATE_REPORTS const* event)
{
    if (!event->hasFields()
        && (!event->hasNatIdentifierField() || !event->hasOperationTypeField() || !event->hasInternalIpAddressField()
            || !event->hasExternalServerIpAddressField() || !event->hasTransportProtocolField()
            || !event->hasInternalTransportSourcePortField() || !event->hasExternalTransportSourcePortField()))
    {
        LOG_ERROR << "Invalid event NAT_UPDATE_REPORTS received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    NatCountersTableEntry entry{sd.GetIdsMId(), sd.GetSensorId(), event->natIdentifier};

    brain::engines::security_events::NatCountersEntriesStruct newNatTableRow;
    newNatTableRow.m_internalIpAddress           = ConvertIpAddress(event->internalIpAddress);
    newNatTableRow.m_externalServerIpAddress     = event->externalServerIpAddress;
    newNatTableRow.m_transportProtocol           = event->transportProtocol;
    newNatTableRow.m_internalTransportSourcePort = event->internalTransportSourcePort;
    newNatTableRow.m_externalTransportSourcePort = event->externalTransportSourcePort;

    auto& entryTable = m_natCountersTable.GetEntryList(entry);

    if (event->operationType == Field_OperationType::ADD)
    {
        if (!m_natCountersTable.Append(entry, newNatTableRow))
        {
            if (m_natCountersTable.IsMaxReached(entry))
            {
                com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
                    = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
                createNatTableAlert(ruleEval, sd, entryTable, NatTableEvent::NAT_FLOODING_ALERT, event);
                if (!addEventAlert(ruleEval, CriticalEventAlert::NatFloodingAlertText, sd))
                {
                    common::counters::IncreaseCounter(m_failedCounter);
                    HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
                }
                LOG_DEBUG << "Nat table maximum size exceeded." << LOG_NOOP;
            }
            else
            {
                com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
                    = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
                createNatTableAlert(ruleEval, sd, entryTable, NatTableEvent::NAT_DUPLICATE_ENTRY_ALERT, event);
                if (!addEventAlert(ruleEval, CriticalEventAlert::NatDuplicateEntryText, sd))
                {
                    common::counters::IncreaseCounter(m_failedCounter);
                    HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
                }
                LOG_DEBUG << "The entry is already in the Nat table." << LOG_NOOP;
            }
        }
    }
    else if (event->operationType == Field_OperationType::DELETE_LOG)
    {
        if (!m_natCountersTable.Delete(entry, newNatTableRow))
        {
            com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
                = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
            createNatTableAlert(ruleEval, sd, entryTable, NatTableEvent::NAT_ENTRY_NOT_FOUND_ALERT, event);
            if (!addEventAlert(ruleEval, CriticalEventAlert::NatEntryNotFountAlertText, sd))
            {
                common::counters::IncreaseCounter(m_failedCounter);
                HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
            }
            LOG_DEBUG << "Element not found in Nat table." << LOG_NOOP;
        }
    }
    else
    {
        // invalid operation type
        LOG_WARNING << "Invalid operation type on Nat table!" << LOG_NOOP;
    }
    LOG_DEBUG << "Keys: "
              << "(SensorId/IdsMId/natId) (" << entry.GetSensorInstanceId() << "/" << entry.GetIdsMInstanceId() << "/"
              << entry.GetNatIdentifier() << "). "
              << "Operation " << event->operationType << ". Data: "
              << "internalIp " << FormatIpType(newNatTableRow.m_internalIpAddress) << " externalIp "
              << newNatTableRow.m_externalServerIpAddress << " transportProtocol " << newNatTableRow.m_transportProtocol
              << " internalTransportSourcePort " << newNatTableRow.m_internalTransportSourcePort
              << " externalTransportSourcePort " << newNatTableRow.m_externalTransportSourcePort << LOG_NOOP;
}

bool
SecurityEventsEngine::fetchEthStats(
    brain::engines::security_events::nanopb::SecurityEventMonitoringData& newSecurityEventMonitoringData)
{
    if (!m_ethStats)
    {
        LOG_ERROR << "Ethernet stats processor is NULL" << LOG_NOOP;
        return false;
    }
    auto const& linkUtilizationHistogramTable = m_ethStats->GetLinkUtilizationHistogramTable();
    for (auto const& entry : linkUtilizationHistogramTable)
    {
        newSecurityEventMonitoringData.LinkUtilization.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.LinkUtilization.Entries.back();
        // key
        newEntry.idsMInstanceId = entry.first.GetIdsMInstanceId();
        SET_NPB_FIELD(newEntry, sensorInstanceId, entry.first.GetSensorInstanceId());
        newEntry.uid = entry.first.GetUId();
        // value
        ScalarHistogram const* hist                                                         = nullptr;
        FloatHistogramData*    pbLinkUtilizationHistogram                                   = nullptr;
        std::vector<brain::engines::security_events::nanopb::HistogramFloatBucket>* buckets = nullptr;
        for (int dir = 0; dir < EthernetStatistics::LINK_DIRECTION_COUNT; ++dir)
        {
            switch (dir)
            {
            case EthernetStatistics::LINK_OUT_DIRECTION:
                hist = &std::get<EthernetStatistics::LINK_OUT_DIRECTION>(entry.second);
                newEntry.has_linkUtilizationHistogramOut = true;
                pbLinkUtilizationHistogram               = &newEntry.linkUtilizationHistogramOut;
                buckets                                  = &newEntry.BucketsOut;
                break;
            case EthernetStatistics::LINK_IN_DIRECTION:
                hist = &std::get<EthernetStatistics::LINK_IN_DIRECTION>(entry.second);
                newEntry.has_linkUtilizationHistogramIn = true;
                pbLinkUtilizationHistogram              = &newEntry.linkUtilizationHistogramIn;
                buckets                                 = &newEntry.BucketsIn;
                break;
            default:
                LOG_WARNING << "Unknown traffic direction " << dir << LOG_NOOP;
                return false;
            }

            brain::histogram::ScalarHistogram::BinDataVector histogramData;
            uint64_t                                         firstHistogramTs{};
            uint64_t                                         lastHistogramTs{};
            auto const ok = hist->GetHistogramValues(histogramData, firstHistogramTs, lastHistogramTs);
            if (!ok)
            {
                return false;
            }
            pbLinkUtilizationHistogram->firstSeenTimeStamp = firstHistogramTs;
            pbLinkUtilizationHistogram->lastSeenTimeStamp  = lastHistogramTs;
            for (auto const& record : histogramData)
            {
                buckets->emplace_back(com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket{
                    static_cast<uint32_t>(record.GetHeight()), static_cast<float>(record.GetInterval())});
            }
        }
    }

    auto const ethernetSwitchesCountersTable = m_ethStats->GetEthernetSwitchesCountersTable();
    for (auto const& entry : ethernetSwitchesCountersTable)
    {
        newSecurityEventMonitoringData.EthernetSwitchesCounters.Entries.emplace_back();
        auto& newEntry = newSecurityEventMonitoringData.EthernetSwitchesCounters.Entries.back();
        // key
        newEntry.idsMInstanceId = entry.first.GetIdsMInstanceId();
        SET_NPB_FIELD(newEntry, sensorInstanceId, entry.first.GetSensorInstanceId());
        newEntry.uid = entry.first.GetUId();
        // value
        newEntry.dropPktBufOverrung = entry.second.dropPktBufOverrung;
        newEntry.dropPktCrC         = entry.second.dropPktCrC;
        newEntry.oversizePkt        = entry.second.oversizePkt;
        newEntry.undersizePkt       = entry.second.undersizePkt;
        newEntry.algnmtErr          = entry.second.algnmtErr;
    }

    return true;
}

bool
SecurityEventsEngine::createLinkUtilizationAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                                                 DataflowStatisticsEngineKeyEntry const&                  entry,
                                                 int /*dir*/)
{
    auto const linkUtilizationHistogramTable = m_ethStats->GetLinkUtilizationHistogramTable();
    auto       it                            = linkUtilizationHistogramTable.find(entry);
    if (linkUtilizationHistogramTable.end() == it)
    {
        LOG_ERROR << "Cannot find key in link utilization histogram table" << LOG_NOOP;
        return false;
    }

    _com_vwg_connect_ids_idsperiodicreport_v1_LinkUtilizationEntry linkUtilizationAlert
        = com_vwg_connect_ids_idsperiodicreport_v1_LinkUtilizationEntry_init_default;

    linkUtilizationAlert.idsMInstanceId = entry.GetIdsMInstanceId();
    SET_NPB_FIELD(linkUtilizationAlert, sensorInstanceId, entry.GetSensorInstanceId());
    linkUtilizationAlert.uid = entry.GetUId();

    m_ethStatsBinDataVectorOut.clear();
    uint64_t firstHistogramTs{};
    uint64_t lastHistogramTs{};
    auto     ok = std::get<EthernetStatistics::LINK_OUT_DIRECTION>(it->second)
                  .GetHistogramValues(m_ethStatsBinDataVectorOut, firstHistogramTs, lastHistogramTs);
    if (ok)
    {
        linkUtilizationAlert.has_linkUtilizationHistogramOut                = true;
        linkUtilizationAlert.linkUtilizationHistogramOut.firstSeenTimeStamp = firstHistogramTs;
        linkUtilizationAlert.linkUtilizationHistogramOut.lastSeenTimeStamp  = lastHistogramTs;
        linkUtilizationAlert.linkUtilizationHistogramOut.buckets.funcs.encode
            = &common::nanopb::encoders::EncodeScalarFloatingHistogram;
        linkUtilizationAlert.linkUtilizationHistogramOut.buckets.arg = &m_ethStatsBinDataVectorOut;
    }
    m_ethStatsBinDataVectorIn.clear();
    ok = std::get<EthernetStatistics::LINK_IN_DIRECTION>(it->second)
             .GetHistogramValues(m_ethStatsBinDataVectorIn, firstHistogramTs, lastHistogramTs);
    if (ok)
    {
        linkUtilizationAlert.has_linkUtilizationHistogramIn                = true;
        linkUtilizationAlert.linkUtilizationHistogramIn.firstSeenTimeStamp = firstHistogramTs;
        linkUtilizationAlert.linkUtilizationHistogramIn.lastSeenTimeStamp  = lastHistogramTs;
        linkUtilizationAlert.linkUtilizationHistogramIn.buckets.funcs.encode
            = &common::nanopb::encoders::EncodeScalarFloatingHistogram;
        linkUtilizationAlert.linkUtilizationHistogramIn.buckets.arg = &m_ethStatsBinDataVectorIn;
    }

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    ruleEval.which_RuleData
        = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_linkUtilizationAlert_tag);
    ruleEval.RuleData.linkUtilizationAlert = linkUtilizationAlert;
    return true;
}

void
SecurityEventsEngine::handleUnexpectedServiceRegistryEvent(SecurityEventSensorData&                          sd,
                                                           SECEV_UNEXPECTED_SERVICE_REGISTRY_DETECTED const* event)
{
    if (event->hasErrorInformationField())
    {
        bool       successIndicator = (0U == event->errorInformation);
        auto const eventFrame       = sd.GetEventFrame();

        if (event->hasServiceRegistryIdField() && event->hasRegisteredServiceField()
            && event->hasRegisteringApplicationIdField() && event->hasRegisteringServerAddressIpField())
        {
            if (0x00 != event->registeringServerAddressIp[0U])
            {
                LOG_ERROR << "Invalid registeringServerAddressIp for event UNEXPECTED_SERVICE_REGISTRY_DETECTED"
                          << LOG_NOOP;
                HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
                return;
            }

            auto serverIp{brain::utils::ConvertSecevIpAddress(&event->registeringServerAddressIp[1U])};

            ServiceRegistryEntry entry{eventFrame.idsMInstanceID,
                                       eventFrame.sensorInstanceID,
                                       event->serviceRegistryId,
                                       event->registeredService,
                                       reinterpret_cast<const char*>(event->registeringApplicationId),
                                       ConvertIpAddress(serverIp),
                                       successIndicator};

            ++m_serviceRegistryTable[entry];
            LOG_DEBUG << "Updated ServicRegistryTable: "
                      << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
                      << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
                      << ",serviceRegistryId=" << event->serviceRegistryId
                      << ",registeredService=" << entry.GetRegisteredService()
                      << ",registeringApplicationId=" << entry.GetRegisteringApplicationId()
                      << ",registeringServerAddressIp=" << FormatIpType(entry.GetRegisteringServerIP())
                      << ",errorInformation=" << event->errorInformation << LOG_NOOP;
        }

        // Requirement 4.2 HCP3 GBT
        if (!successIndicator)
        {
            handleErroneousServiceRegistrationAlert(sd);
        }
    }
    else
    {
        LOG_ERROR << "Invalid event UNEXPECTED_SERVICE_REGISTRY_DETECTED received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }
}


bool
SecurityEventsEngine::CreateSecurityEventsMonitoringData(SecurityEventsPeriodicMonitoringData& securityEventsMonitoring,
                                                         uint64_t startPeriodicReportTimestamp,
                                                         uint64_t endPeriodicReportTimestamp)
{
    auto ok = appendTables(securityEventsMonitoring, startPeriodicReportTimestamp, endPeriodicReportTimestamp);
    if (!ok)
    {
        LOG_WARNING << "Failed to append data from current monitoring period" << LOG_NOOP;
        return false;
    }

    ok = appendHistograms(securityEventsMonitoring);
    if (!ok)
    {
        LOG_WARNING << "Failed to append histograms from current monitoring period" << LOG_NOOP;
        return false;
    }

    securityEventsMonitoring.PrepareForSerialization();
    for (auto const& entry : securityEventsMonitoring.Entries)
    {
        if (entry.has_processCrashRateTable)
        {
            LOG_VERBOSE << "PeriodicStatistics has Process crash rate table" << LOG_NOOP;
        }
        if (entry.has_aggregatedCrashRateHistogram)
        {
            LOG_VERBOSE << "PeriodicStatistics has aggregate crash rate histogram" << LOG_NOOP;
        }
        if (entry.has_serviceRegistryTable)
        {
            LOG_VERBOSE << "PeriodicStatistics has service registry table" << LOG_NOOP;
        }
        if (entry.has_externalDataStorageTable)
        {
            LOG_VERBOSE << "PeriodicStatistics has external data storage table" << LOG_NOOP;
        }
        if (entry.has_externalNewHWConnectionTable)
        {
            LOG_VERBOSE << "PeriodicStatistics has external HW devices table" << LOG_NOOP;
        }
        if (entry.has_droppedBlockedConnectionsTable)
        {
            LOG_VERBOSE << "PeriodicStatistics has dropped/blocked connections table" << LOG_NOOP;
        }
        if (entry.has_ethernetSwitchesCountersTable)
        {
            LOG_VERBOSE << "PeriodicStatistics has ethernet switches counters table" << LOG_NOOP;
        }
        if (entry.has_securityEventsCountersTable)
        {
            LOG_VERBOSE << "PeriodicStatistics has security events counters table" << LOG_NOOP;
        }
        if (entry.has_criticalSecurityEventsAlertsCountersTable)
        {
            LOG_VERBOSE << "PeriodicStatistics has critical security events alerts counters table" << LOG_NOOP;
        }
        if (entry.has_droppedSecurityEventsCountersTable)
        {
            LOG_VERBOSE << "PeriodicStatistics has dropped security events counters table" << LOG_NOOP;
        }
    }

    return true;
}

ReturnCode
SecurityEventsEngine::processInternal(UPSensorData sd)
{
    // Check valid tags
    auto findTag = validTags.find(sd->GetTag());
    auto res     = ReturnCode::Success;
    if (findTag != validTags.end())
    {
        try
        {
            LOG_VERBOSE << "Processing SecurityEventsEngine - began processing SecurityEventSensorData" << LOG_NOOP;

            auto&      securityEventSD  = dynamic_cast<SecurityEventSensorData&>(*sd);
            auto&      secEvIdsMgr      = SecurityEventIdsManager::GetInstance();
            auto const eventId          = securityEventSD.GetEventId();
            auto       idsMInstanceID   = securityEventSD.GetEventFrame().idsMInstanceID;
            auto       sensorInstanceID = securityEventSD.GetEventFrame().sensorInstanceID;
            auto       count            = securityEventSD.GetEventFrame().count;

            if (secEvIdsMgr.IsInSecurityEventsIdsWhiteList(eventId))
            {
                auto handlerById = m_eventHandlers.find(eventId);
                if (handlerById == m_eventHandlers.end())
                {
                    if (0 == m_securityEventEngines.count(eventId))
                    {
                        // Couldn't found received event ID in the event handler keys - meaning it's not supported.
                        HandleUnknownEventIdAlert(securityEventSD);
                    }
                    else
                    {
                        // event ID found in the event handler keys - execute all it's handlers
                        for (auto const& eventHandler : m_securityEventEngines[eventId])
                        {
                            res = eventHandler->Process(std::move(sd));
                            if (ReturnCode::Success != res)
                            {
                                handleDroppedSecurityEvent(idsMInstanceID, sensorInstanceID, eventId, DropReason::SecurityEventsEngine);
                            }
                        }

                        updateSecurityEventsCountersTable(idsMInstanceID, sensorInstanceID, eventId, count);
                    }
                }
                else
                {
                    // event ID found in the event handler keys - execute all it's handlers
                    for (auto const& eventHandler : m_eventHandlers[eventId])
                    {
                        eventHandler(this, securityEventSD);
                    }
                    UpdateSecurityEventsCountersTable(securityEventSD.GetEventFrame());
                }
            }
            else
            {
                // If the event is in the blacklist then just disregard it.
                if (secEvIdsMgr.IsInSecurityEventsIdsBlackList(eventId))
                {
                    LOG_DEBUG << "SE " << static_cast<int>(eventId) << " is blacklisted, will not be processed"
                              << LOG_NOOP;
                }
                // Couldn't found received event ID in white list or blacklist
                HandleUnknownEventIdAlert(securityEventSD);
            }
        }
        catch (std::bad_cast const& /*e*/)
        {
            LOG_ERROR << "Processing SecurityEventsEngine - sd cannot be casted to SecurityEventSensorData" << LOG_NOOP;
            res = ReturnCode::CastError;
        }
    }
    else
    {
        LOG_ERROR << "Processing SecurityEventsEngine - the SD is tagged: " << static_cast<uint32_t>(sd->GetTag())
                  << " is not supported" << LOG_NOOP;
        res = ReturnCode::TagError;
    }

    if (ReturnCode::Success != res)
    {
        if (ReturnCode::LengthError == res)
        {
            common::counters::IncreaseCounter(m_invalidCtxDataLenCounter);
        }
        common::counters::IncreaseCounter(m_failedCounter);
    }
    return res;
}

bool
SecurityEventsEngine::SendLinkUtilizationAlert(DataflowStatisticsEngineKeyEntry const&            entry,
                                               brain::sensor_data::SecurityEventSensorData const& sd,
                                               int                                                dir)
{
    auto const eventName = (EthernetStatistics::LINK_OUT_DIRECTION == dir)
                               ? CriticalEventAlert::LinkUtilizationOutTraffic
                               : CriticalEventAlert::LinkUtilizationInTraffic;

    // Handle rule evaluation
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
    auto ok = createLinkUtilizationAlert(ruleEval, entry, dir);
    if (!ok)
    {
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return false;
    }

    return addEventAlert(ruleEval, eventName, sd);
}

void
SecurityEventsEngine::createSecurityEventAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                                               SecurityEventSensorData&                                 sd,
                                               SecurityEventType                                        eventType,
                                               EventIds                                                 eventId)
{
    com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData securityEventAlert
        = com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_init_default;
    std::ignore     = CreateSecurityEventData(securityEventAlert, sd);
    auto eventFrame = sd.GetEventFrame();

    switch (eventId)
    {
    case EventIds::DIAG_SEV_ECU_UNLOCK_SUCCESSFUL:
        securityEventAlert.has_unlockedData       = true;
        securityEventAlert.unlockedData.alertText = common::nanopb::CreateEncodingLiteralStringCallback(
            GetCriticalEventString(CriticalEventAlert::SuspiciousAlertText).c_str());
        securityEventAlert.unlockedData.timestamp = m_currentTime;
        ruleEval.which_RuleData                   = static_cast<pb_size_t>(
            com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_suspiciousEcuUnlockSuccessfulAlert_tag);
        ruleEval.RuleData.suspiciousEcuUnlockSuccessfulAlert = securityEventAlert;
        eventType                                            = SecurityEventType::Normal;
        LOG_DEBUG << "create suspiciousEcuUnlockSuccessfulAlert:"
                  << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
                  << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
                  << ",eventDefinitionId=" << static_cast<uint32_t>(eventFrame.eventDefinitionId) << LOG_NOOP;
        break;
    default:;
    }

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    
    switch (eventType)
    {
    case SecurityEventType::Critical:
        ruleEval.which_RuleData = static_cast<pb_size_t>(
            com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_criticalSecurityEventAlert_tag);
        ruleEval.RuleData.criticalSecurityEventAlert = securityEventAlert;
        LOG_DEBUG << "create criticalSecurityEventAlert:"
                  << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
                  << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
                  << ",eventDefinitionId=" << static_cast<uint32_t>(eventFrame.eventDefinitionId) << LOG_NOOP;
        break;
    case SecurityEventType::Unknown:
        securityEventAlert.contextData            = common::nanopb::CreateEncodingCallback(sd.GetContextData());
        securityEventAlert.has_unlockedData       = true;
        securityEventAlert.unlockedData.alertText = common::nanopb::CreateEncodingLiteralStringCallback(
            GetCriticalEventString(CriticalEventAlert::UnknownEventIdEventName).c_str());
        securityEventAlert.unlockedData.timestamp = m_currentTime;
        ruleEval.which_RuleData
            = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_unknownEventIdAlert_tag);
        ruleEval.RuleData.unknownEventIdAlert = securityEventAlert;
        LOG_DEBUG << "create unknownEventIdAlert:"
                  << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
                  << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
                  << ",eventDefinitionId=" << static_cast<uint32_t>(eventFrame.eventDefinitionId)
                  << ",contextData size=" << sd.GetContextData().size() << LOG_NOOP;
        break;
    case SecurityEventType::Normal:
        // falls through
    default:;
    }
}

void
SecurityEventsEngine::forwardCriticalSecurityEvent(SecurityEventSensorData& securityEventSD)
{
    UpdateCriticalSecurityEventsAlertsCountersTable(securityEventSD.GetEventId());

    // Handle rule evaluation
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
    createSecurityEventAlert(ruleEval, securityEventSD, SecurityEventType::Critical, {});
    
    if (!addEventAlert(ruleEval, CriticalEventAlert::CriticalEventName, securityEventSD))
    {
        common::counters::IncreaseCounter(m_failedCounter);
        HandleDroppedSecurityEvent(securityEventSD, DropReason::SecurityEventsEngine);
    }
}

void
SecurityEventsEngine::detectDoubleIpToMacAssociation(IpType const&                  ipAddress,
                                                     uint64_t                       mac)
{
    m_doubledIpToMacAssociationTable[mac] = ipAddress;
    LOG_DEBUG << "Create  IP address to MAC address association: "
              << "timestamp=" << m_currentTime << ",new mac=" << mac << ",new ip=" << FormatIpType(ipAddress)
              << LOG_NOOP;
}

void
SecurityEventsEngine::createDoubleMacToIpaddressAlert(uint64_t                       mac,
                                                      uint64_t                       currentMac,
                                                      IpType const&                  ipAddress,
                                                      SecurityEventSensorData const& sd)
{
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;

    com_vwg_connect_ids_idsperiodicreport_v1_DoubledIpOrMacAssociation doubleMacToIpAssociationAlert
        = com_vwg_connect_ids_idsperiodicreport_v1_DoubledIpOrMacAssociation_init_default;

    doubleMacToIpAssociationAlert.timestamp   = m_currentTime;
    doubleMacToIpAssociationAlert.newMac      = mac;
    doubleMacToIpAssociationAlert.newIpAddres = common::nanopb::CreateEncodingCallback(ipAddress);
    SET_NPB_FIELD(doubleMacToIpAssociationAlert, currentMac, currentMac);
    doubleMacToIpAssociationAlert.currentIp = common::nanopb::CreateEncodingCallback(ipAddress);

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    ruleEval.which_RuleData
        = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_doubledMacToIpAlert_tag);
    ruleEval.RuleData.doubledMacToIpAlert = doubleMacToIpAssociationAlert;

    if (!addEventAlert(ruleEval, CriticalEventAlert::DoubleMacToIpEventName, sd))
    {
        common::counters::IncreaseCounter(m_failedCounter);
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
    }

    LOG_DEBUG << "Create double MAC address to IP address association: "
              << "timestamp=" << m_currentTime << ",new mac=" << mac << ",new ip=" << FormatIpType(ipAddress)
              << ",current mac=" << currentMac << LOG_NOOP;
}

void
SecurityEventsEngine::detectDoubleMacToIpAssociation(uint64_t                       mac,
                                                     IpType const&                  ipAddress,
                                                     SecurityEventSensorData const& sd)
{
    if (1U == m_doubledMacToIpAssociationTable.count(ipAddress))
    {
        auto const currentMac{m_doubledMacToIpAssociationTable[ipAddress]};
        if (currentMac != mac)
        {
            createDoubleMacToIpaddressAlert(mac, currentMac, ipAddress, sd);
        }
    }
    else
    {
        m_doubledMacToIpAssociationTable[ipAddress] = mac;
    }
}

void
SecurityEventsEngine::handleLogsForwardedPackageStatisticsEvent(
    SecurityEventSensorData& sd, SECEV_LOCAL_FW_LOGS_FORWARDED_PACKAGE_STATISTICS const* event)
{
    IpType const  sourceIp{ConvertIpAddress(event->sourceIpAddress)};
    IpType const  destinationIp(ConvertIpAddress(event->destinationIpAddress));
    uint8_t const ethIdType = static_cast<uint8_t>(event->ethIdType_filterType << 4 | event->ethIdType_networkType);

    if (event->hasDroppedBlockedConnectionAttemptsCountField())
    {
        if (event->hasVlanTagField() && event->hasSuccessfullConnectionAttemptsCountField())
        {
            brain::engines::security_events::IpConnectionCountersEntry entry{ethIdType, event->vlanTag};
            brain::engines::security_events::IpConnectionCountersValue value{
                event->droppedBlockedConnectionAttemptsCount, event->successfullConnectionAttemptsCount};

            m_ipConnectionCountersTable[entry] = value;
        }
    }

    if (event->hasFields()
        || (event->hasIncomingPackageInterfaceField() && event->hasOutgoingPackageInterfaceField()
            && event->hasSourceIpAddressField() && event->hasDestinationIpAddressField() && event->hasSourcePortField()
            && event->hasDestinationPortField() && event->hasSourceMacAddressField()
            && event->hasDestinationMacAddressField() && event->hasFirewallIdField() && event->hasFilterRuleIdField()
            && event->hasFilterRuleField() && event->hasTmProtocolField() && event->hasVlanTagField()
            && event->hasDroppedBlockedConnectionAttemptsCountField()
            && event->hasSuccessfullConnectionAttemptsCountField()))
    {
        // Connections Counters Table
        auto const        eventFrame{sd.GetEventFrame()};
        std::string const packageInterface[]{common::CharArrayToString(event->incomingPackageInterface),
                                             common::CharArrayToString(event->outgoingPackageInterface)};
        IpType const      ipAddress[]{sourceIp, destinationIp};
        uint32_t const    ports[]{event->sourcePort, event->destinationPort};
        uint64_t const    macAddresses[]{event->sourceMacAddress, event->destinationMacAddress};

        brain::engines::security_events::ConnectionsCountersEntry connectionCounterEntry{
            eventFrame.idsMInstanceID,
            eventFrame.sensorInstanceID,
            ethIdType,
            event->firewallId,
            event->filterRuleId,
            common::CharArrayToString(event->filterRule),
            packageInterface,
            ipAddress,
            common::CharArrayToString(event->tmProtocol),
            ports,
            macAddresses,
            event->vlanTag};

        brain::engines::security_events::ConnectionsCountersValue connectionValue{
            common::CharArrayToString(event->framePayload), 0U, 0U, 0U};

        auto const connectionsCountersIt
            = m_ipAnomaliesConnectionsCountersTable.emplace(std::piecewise_construct,
                                                            std::forward_as_tuple(connectionCounterEntry),
                                                            std::forward_as_tuple(connectionValue));
        if (!common::types::IsMapSizeExceeded(m_ipAnomaliesConnectionsCountersTable, connectionsCountersIt))
        {
            auto& connectionsCountersValue = connectionsCountersIt.first->second;
            connectionsCountersValue.DroppedBlockedConnectionAttemptsCount
                += event->droppedBlockedConnectionAttemptsCount;
            connectionsCountersValue.SuccessfullConnectionAttemptsCount += event->successfullConnectionAttemptsCount;
            ++connectionsCountersValue.DroppedNotificationsCount;

            LOG_DEBUG << "Updated connection counter table: "
                      << "IDSm inst. ID=" << connectionCounterEntry.GetIdsMInstanceId()
                      << ", sensor inst. ID=" << connectionCounterEntry.GetSensorInstanceId()
                      << ", ethidType=" << connectionCounterEntry.GetEthIdType()
                      << ",firewall id=" << connectionCounterEntry.GetFirewallId()
                      << "filter rule id=" << connectionCounterEntry.GetFilterRuleId()
                      << ", filter rule=" << connectionCounterEntry.GetFilterRule()
                      << ", incoming package interface=" << connectionCounterEntry.GetIncomingPackageInterface()
                      << ", outgoing package interface=" << connectionCounterEntry.GetOutgoingPackageInterface()
                      << "source ip address=" << FormatIpType(connectionCounterEntry.GetSourceIpAddress())
                      << ", destination ip address=" << FormatIpType(connectionCounterEntry.GetDestinationIpAddress())
                      << ", tm protocol=" << connectionCounterEntry.GetTmProtocol()
                      << ", source port=" << connectionCounterEntry.GetSourcePort()
                      << ", destination port=" << connectionCounterEntry.GetDestinationPort()
                      << "source mac address=" << connectionCounterEntry.GetSourceMacAddress()
                      << ", destination mac address=" << connectionCounterEntry.GetDestinationMacAddress()
                      << ", vlan tag=" << connectionCounterEntry.GetVlanTag()
                      << ", dropped blocked connection attempts count="
                      << connectionsCountersValue.DroppedBlockedConnectionAttemptsCount
                      << ", successfull connection attemptsCount="
                      << connectionsCountersValue.SuccessfullConnectionAttemptsCount
                      << ", dropped notifications count=" << connectionsCountersValue.DroppedNotificationsCount
                      << LOG_NOOP;
        }
    }
    else
    {
        LOG_ERROR << "Invalid event LOCAL_FW_LOGS_FORWARDED_PACKAGE_STATISTICS received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    if (event->hasSourceIpAddressField() && event->hasDestinationIpAddressField() && event->hasSourceMacAddressField()
        && event->hasDestinationMacAddressField())
    {
        // source and destination MAC to IP Association Table
        brain::engines::security_events::MacToIpAssociationEntry sourceMactoIpEntry{sourceIp, event->sourceMacAddress};
        brain::engines::security_events::MacToIpAssociationEntry destinationMactoIpEntry{destinationIp,
                                                                                         event->destinationMacAddress};
        brain::engines::security_events::MacToIpAssociationValue macValue{0u, m_currentTime, m_currentTime};

        auto macToIpAssociationIt = m_macToIpAssociationTable.emplace(
            std::piecewise_construct, std::forward_as_tuple(sourceMactoIpEntry), std::forward_as_tuple(macValue));

        if (!common::types::IsMapSizeExceeded(m_macToIpAssociationTable, macToIpAssociationIt))
        {
            auto& sourceMacToIpAssociationValue = macToIpAssociationIt.first->second;

            ++sourceMacToIpAssociationValue.Counter;
            sourceMacToIpAssociationValue.UpdatedTimestamp = m_currentTime;

            LOG_DEBUG << "Updated source mac to ip association value table: "
                      << "mac address " << sourceMactoIpEntry.GetMacAddress()
                      << ", ip address=" << FormatIpType(sourceMactoIpEntry.GetIpAddress()) << ", created timestamp "
                      << sourceMacToIpAssociationValue.CreatedTimestamp << ", updated timestamp "
                      << sourceMacToIpAssociationValue.UpdatedTimestamp << ", events count "
                      << sourceMacToIpAssociationValue.Counter << LOG_NOOP;
        }

        macToIpAssociationIt = m_macToIpAssociationTable.emplace(
            std::piecewise_construct, std::forward_as_tuple(destinationMactoIpEntry), std::forward_as_tuple(macValue));

        if (!common::types::IsMapSizeExceeded(m_macToIpAssociationTable, macToIpAssociationIt))
        {
            auto& destinationMacToIpAssociationValue = macToIpAssociationIt.first->second;

            ++destinationMacToIpAssociationValue.Counter;
            destinationMacToIpAssociationValue.UpdatedTimestamp = m_currentTime;

            LOG_DEBUG << "Updated destination mac to ip association value table: "
                      << "mac address " << destinationMactoIpEntry.GetMacAddress()
                      << ", ip address=" << FormatIpType(destinationMactoIpEntry.GetIpAddress())
                      << ", created timestamp " << destinationMacToIpAssociationValue.CreatedTimestamp
                      << ", updated timestamp " << destinationMacToIpAssociationValue.UpdatedTimestamp
                      << ", events count " << destinationMacToIpAssociationValue.Counter << LOG_NOOP;
        }
    }

    if (event->hasSourceIpAddressField() && event->hasSourceMacAddressField())
    {
        detectDoubleIpToMacAssociation(sourceIp, event->sourceMacAddress);
        detectDoubleMacToIpAssociation(event->sourceMacAddress, sourceIp, sd);
    }

    if (event->hasDestinationIpAddressField() && event->hasDestinationMacAddressField())
    {
        detectDoubleIpToMacAssociation(destinationIp, event->destinationMacAddress);
        detectDoubleMacToIpAssociation(event->destinationMacAddress, destinationIp, sd);
    }
}

void
SecurityEventsEngine::handleBlockedConnectionsDetectedEvent(SecurityEventSensorData&                           sd,
                                                            SECEV_LOCAL_FW_BLOCKED_CONNECTIONS_DETECTED const* event)
{
    // discard calculation becuase source,destination,sourcePort and transportProtocol is used for both table
    // calculations
    if (!event->hasFields()
        && (!event->hasSourceIpAddressField() || !event->hasDestinationIpAddressField() || !event->hasSourcePortField()
            || !event->hasTransportProtocolField()))
    {
        LOG_ERROR << "Invalid event LOCAL_FW_BLOCKED_CONNECTIONS_DETECTED received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    IpType const      sourceIp{ConvertIpAddress(event->sourceIpAddress)};
    IpType const      destinationIp{ConvertIpAddress(event->destinationIpAddress)};
    std::string const transportProtocol{common::CharArrayToString(event->transportProtocol)};

    // Requirement 2.2
    brain::engines::security_events::IpDroppedConnectionsEntry entry(sourceIp, transportProtocol, event->sourcePort);

    ++m_ipDroppedConnectionsTable[entry];

    LOG_VERBOSE << "Updated IpDroppedConnections table" << LOG_NOOP;

    if (event->hasFields()
        || (event->hasIncomingPackageInterfaceField() && event->hasOutgoingPackageInterfaceField()
            && event->hasServiceVersionField() && event->hasFirewallIdField() && event->hasFilterRuleIdField()
            && event->hasFilterRuleField() && event->hasUserNameField() && event->hasProcessNameField()
            && event->hasDroppedNotificationsCountField() && event->hasDroppedPackagesCountField()))
    {
        // Dropped Connections Counters Table
        auto const        eventFrame{sd.GetEventFrame()};
        std::string const packageInterface[2]{common::CharArrayToString(event->incomingPackageInterface),
                                              common::CharArrayToString(event->outgoingPackageInterface)};
        IpType const      ipAddress[2]{sourceIp, destinationIp};
        uint32_t const    ports[2]{event->sourcePort, event->destinationPort};

        brain::engines::security_events::DroppedConnectionsCountersEntry droppedConnectionEntry{
            eventFrame.idsMInstanceID,
            eventFrame.sensorInstanceID,
            event->serviceVersion,
            event->firewallId,
            event->filterRuleId,
            common::CharArrayToString(event->filterRule),
            packageInterface,
            ipAddress,
            transportProtocol,
            ports,
            common::CharArrayToString(event->userName),
            common::CharArrayToString(event->processName)};
        brain::engines::security_events::DroppedConnectionsCountersValue connectionValue{0U, 0U};

        auto const droppedConnectionCounterEntryIt
            = m_droppedConnectionsCountersTable.emplace(std::piecewise_construct,
                                                        std::forward_as_tuple(droppedConnectionEntry),
                                                        std::forward_as_tuple(connectionValue));
        if (!common::types::IsMapSizeExceeded(m_droppedConnectionsCountersTable, droppedConnectionCounterEntryIt))
        {
            auto& currentDroppedConnectionCounter = droppedConnectionCounterEntryIt.first->second;

            currentDroppedConnectionCounter.DroppedNotificationsCount += event->droppedNotificationsCount;
            currentDroppedConnectionCounter.DroppedPackagesCount += event->droppedPackagesCount;

            LOG_DEBUG << "Updated dropped connection counter table: "
                      << "IDSm inst. ID=" << droppedConnectionEntry.GetIdsMInstanceId()
                      << ", sensor inst. ID=" << droppedConnectionEntry.GetSensorInstanceId()
                      << ", serviceVersion=" << droppedConnectionEntry.GetServiceVersion()
                      << ", firewall id=" << droppedConnectionEntry.GetFirewallId()
                      << ", filter rule id=" << droppedConnectionEntry.GetFilterRuleId()
                      << ", filter rule=" << droppedConnectionEntry.GetFilterRule()
                      << ", incoming package interface=" << droppedConnectionEntry.GetIncomingPackageInterface()
                      << ", outgoing package interface=" << droppedConnectionEntry.GetOutgoingPackageInterface()
                      << ", source ip address=" << FormatIpType(droppedConnectionEntry.GetSourceIpAddress())
                      << ", destination ip address=" << FormatIpType(droppedConnectionEntry.GetDestinationIpAddress())
                      << ", transport protocol=" << droppedConnectionEntry.GetTransportProtocol()
                      << ", source port=" << droppedConnectionEntry.GetSourcePort()
                      << ", destination port=" << droppedConnectionEntry.GetDestinationPort()
                      << ", user name=" << droppedConnectionEntry.GetUserName()
                      << ", process name=" << droppedConnectionEntry.GetProcessName()
                      << ", droppped notification count=" << currentDroppedConnectionCounter.DroppedNotificationsCount
                      << ", dropped package count=" << currentDroppedConnectionCounter.DroppedPackagesCount << LOG_NOOP;
        }
    }
}

void
SecurityEventsEngine::handleSuspiciousProcessCrashRateAlert(brain::histogram::RateHistogram const& hist,
                                                            SecurityEventSensorData&               securityEventSD)
{
    // Handle rule evaluation
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
    brain::histogram::RateHistogram::BinDataVector processHistogramData;
    brain::histogram::RateHistogram::BinDataVector aggregatedHistogramData;
    std::string                                    processName
        = securityEventSD.decodeContextData<SECEV_PROCESS_CRASH_NOTIFICATION>()->processDriverApplicationLibrary;

    auto const ok = createSuspiciousProcessCrashRateAlert(
        ruleEval, securityEventSD, hist, processHistogramData, aggregatedHistogramData, processName);
    if (!ok)
    {
        HandleDroppedSecurityEvent(securityEventSD, DropReason::SecurityEventsEngine);
        return;
    }

    if (!addEventAlert(ruleEval, CriticalEventAlert::SuspiciousProcessCrashRate, securityEventSD))
    {
        common::counters::IncreaseCounter(m_failedCounter);
        HandleDroppedSecurityEvent(securityEventSD, DropReason::SecurityEventsEngine);
    }
}

bool
SecurityEventsEngine::createSuspiciousProcessCrashRateAlert(
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
    SecurityEventSensorData&                                 securityEventSD,
    brain::histogram::RateHistogram                          hist,
    BinDataVector&                                           processHistogramData,
    BinDataVector&                                           aggregatedHistogramData,
    std::string&                                             processName)
{
    LOG_VERBOSE << "Suspicious process crash rate alert" << LOG_NOOP;

    uint64_t processFirstTimeStamp{};
    uint64_t processLastTimeStamp{};
    if (!hist.GetHistogramValues(processHistogramData, processFirstTimeStamp, processLastTimeStamp))
    {
        LOG_ERROR << "Cannot get process crash rate histogram values" << LOG_NOOP;
        return false;
    }

    com_vwg_connect_ids_idsperiodicreport_v1_SuspiciousProcessCrashRateAlert crashRateAlert
        = com_vwg_connect_ids_idsperiodicreport_v1_SuspiciousProcessCrashRateAlert_init_default;
    // fill process ID
    auto const eventFrame         = securityEventSD.GetEventFrame();
    auto const event              = securityEventSD.decodeContextData<SECEV_PROCESS_CRASH_NOTIFICATION>();
    crashRateAlert.idsMInstanceID = eventFrame.idsMInstanceID;
    SET_NPB_FIELD(crashRateAlert, sensorInstanceID, eventFrame.sensorInstanceID);
    crashRateAlert.processName.funcs.encode = &common::nanopb::encoders::EncodeStr;
    if (nullptr != event)
    {
        crashRateAlert.typeOfError  = event->typeOfError;
        crashRateAlert.crashReason  = event->crashReason;
        crashRateAlert.vmIdentifier = event->vmIdentifier;
    }
    crashRateAlert.processName.arg = &processName;

    // fill process crash rate histogram
    crashRateAlert.has_processCrashRateHistogram                  = true;
    crashRateAlert.processCrashRateHistogram.firstSeenTimeStamp   = processFirstTimeStamp;
    crashRateAlert.processCrashRateHistogram.lastSeenTimeStamp    = processLastTimeStamp;
    crashRateAlert.processCrashRateHistogram.buckets.funcs.encode = &common::nanopb::encoders::EncodeRateHistogram;
    crashRateAlert.processCrashRateHistogram.buckets.arg          = &processHistogramData;

    fillAggregatedCrashRateHistogramForAlert<com_vwg_connect_ids_idsperiodicreport_v1_SuspiciousProcessCrashRateAlert>(
        crashRateAlert, aggregatedHistogramData);

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    ruleEval.which_RuleData = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_suspiciousProcessCrashRateAlert_tag);
    ruleEval.RuleData.suspiciousProcessCrashRateAlert = crashRateAlert;

    return true;
}

void
SecurityEventsEngine::handleSuspiciousAggregateCrashRateAlert(SecurityEventSensorData const& securityEventSD)
{
    // Handle rule evaluation
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
    brain::histogram::RateHistogram::BinDataVector aggregatedHistogramData;

    createSuspiciousAggregateCrashRateAlert(ruleEval, aggregatedHistogramData);

    if (!addEventAlert(ruleEval, CriticalEventAlert::SuspiciousAggregateCrashRate, securityEventSD))
    {
        common::counters::IncreaseCounter(m_failedCounter);
        HandleDroppedSecurityEvent(securityEventSD, DropReason::SecurityEventsEngine);
    }
}

void
SecurityEventsEngine::createSuspiciousAggregateCrashRateAlert(
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval, BinDataVector& aggregatedHistogramData)
{
    com_vwg_connect_ids_idsperiodicreport_v1_SuspiciousAggregateCrashRateAlert crashRateAlert
        = com_vwg_connect_ids_idsperiodicreport_v1_SuspiciousAggregateCrashRateAlert_init_default;

    fillAggregatedCrashRateHistogramForAlert<
        com_vwg_connect_ids_idsperiodicreport_v1_SuspiciousAggregateCrashRateAlert>(crashRateAlert,
                                                                                    aggregatedHistogramData);

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    ruleEval.which_RuleData = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_suspiciousAggregateCrashRateAlert_tag);
    ruleEval.RuleData.suspiciousAggregateCrashRateAlert = crashRateAlert;
}

void
SecurityEventsEngine::handleProcessCrashNotificationEvent(SecurityEventSensorData&                sd,
                                                          SECEV_PROCESS_CRASH_NOTIFICATION const* event)
{
    if (!event->hasFields()
        && (!event->hasProcessStateField() || !event->hasVmIdentifierField()
            || !event->hasProcessDriverApplicationLibraryField() || !event->hasTypeOfErrorField()
            || !event->hasCrashReasonField()))
    {
        LOG_ERROR << "Invalid event PROCESS_CRASH_NOTIFICATION received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    LOG_VERBOSE << "Watchdog - Process Crash Rate" << LOG_NOOP;
    auto const eventFrame = sd.GetEventFrame();

    if (event->processState == PROCESS_STATE_STOP)
    {
        // Requirement 3.7 HCP3 GBT
        brain::engines::security_events::ProcessCrashRateEntry entry{eventFrame.idsMInstanceID,
                                                                     eventFrame.sensorInstanceID,
                                                                     event->vmIdentifier,
                                                                     event->processDriverApplicationLibrary,
                                                                     event->typeOfError,
                                                                     event->crashReason};
        auto const                                             insertion = m_processCrashRateTable.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(entry),
            std::forward_as_tuple(
                std::make_tuple(brain::histogram::RateHistogram{m_processCrashRateBins, MAX_BURST},
                                PolicerTokenBucket{m_suspiciousCrashThresholdRate, m_suspiciousCrashRateMaxBurst})));

        if (!common::types::IsMapSizeExceeded(m_processCrashRateTable, insertion))
        {
            auto& processCrashRateHistogram = std::get<0>(insertion.first->second);
            auto& tokenBucket               = std::get<1>(insertion.first->second);

            // Requirement 3.8 HCP3 GBT
            std::ignore = processCrashRateHistogram.AddData(sd.GetTimestamp(), EventWeight);
            LOG_DEBUG << "Updated ProcessCrashRateTable:"
                      << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
                      << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
                      << ",vmIdentifier=" << event->vmIdentifier << ",processName=" << entry.GetProcessName()
                      << ",typeOfError=" << event->typeOfError << ",crashReason=" << event->crashReason
                      << ",processState=PROCESS_STATE_STOP" << LOG_NOOP;

            // Requirement 3.9 HCP3 GBT - step 1 (update histogram)
            std::ignore = m_aggregateCrashRateHistogram.AddData(sd.GetTimestamp(), EventWeight);
            LOG_VERBOSE << "Updated AggregateCrashRate histogram" << LOG_NOOP;

            // Requirement 3.9 HCP3 GBT - step 2 (create an alert)
            bool isEventInBucketsLimit
                = m_aggregateCrashRateTokenBucket->Update(common::MS_TO_S(sd.GetTimestamp()), EventWeight);
            if (!isEventInBucketsLimit)
            {
                handleSuspiciousAggregateCrashRateAlert(sd);
                m_aggregateCrashRateTokenBucket->Reset();

                LOG_DEBUG << "Created aggregateCrashRate alert and reset the token bucket for security event: "
                          << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
                          << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
                          << ",vmIdentifier=" << event->vmIdentifier << ",processName=" << entry.GetProcessName()
                          << ",typeOfError=" << event->typeOfError << ",crashReason=" << event->crashReason
                          << ",processState=stop." << LOG_NOOP;
            }

            // Requirement 3.10 HCP3 GBT
            isEventInBucketsLimit = tokenBucket.Update(common::MS_TO_S(sd.GetTimestamp()), EventWeight);
            if (!isEventInBucketsLimit)
            {
                handleSuspiciousProcessCrashRateAlert(processCrashRateHistogram, sd);
                tokenBucket.Reset();

                LOG_DEBUG << "Created suspiciousProcessCrashRate alert and reset the token bucket for security event: "
                          << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
                          << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
                          << ",vmIdentifier=" << event->vmIdentifier << ",processName=" << entry.GetProcessName()
                          << ",typeOfError=" << event->typeOfError << ",crashReason=" << event->crashReason << LOG_NOOP;
            }
        }
    }
}

void
SecurityEventsEngine::handleProcessStartStopNotificationEvent(SecurityEventSensorData&                     sd,
                                                              SECEV_PROCESS_START_STOP_NOTIFICATION const* event)
{
    if (!event->hasFields()
        && (!event->hasVmIdentifierField() || !event->hasGroupIdField() || !event->hasProcessCommandLineField()
            || !event->hasProcessCommandLineLengthField() || !event->hasProcessStateField()
            || !event->hasAdaptiveAutosarAppNameLengthField() || !event->hasAdaptiveAutosarAppNameField()))
    {
        LOG_ERROR << "Invalid event PROCESS_START_STOP_NOTIFICATION received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    auto const        eventFrame = sd.GetEventFrame();
    std::string const adaptiveAutosarAppName(event->adaptiveAutosarAppName, event->adaptiveAutosarAppNameLength);
    std::string const processCommandLine(event->processCommandLine, event->processCommandLineLength);
    ProcessStartStopCountersEntry entry{eventFrame.idsMInstanceID,
                                        eventFrame.sensorInstanceID,
                                        event->vmIdentifier,
                                        event->groupId,
                                        adaptiveAutosarAppName,
                                        processCommandLine};

    auto const it = m_processStartStopCountersTable.emplace(
        std::piecewise_construct, std::forward_as_tuple(entry), std::forward_as_tuple(std::make_pair(0U, 0U)));

    if (!common::types::IsMapSizeExceeded(m_processStartStopCountersTable, it))
    {
        // a combination of flags might be received
        if (PROCESS_STATE_START == (PROCESS_STATE_START & event->processState))
        {
            std::get<PROCESS_START_COUNTER>(it.first->second) += 1U;
        }
        if (PROCESS_STATE_STOP == (PROCESS_STATE_STOP & event->processState))
        {
            std::get<PROCESS_STOP_COUNTER>(it.first->second) += 1U;
        }

        LOG_DEBUG << "Updated ProcessStartStopCountersTable:"
                  << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
                  << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
                  << ",vmIdentifier=" << event->vmIdentifier << ",groupId=" << event->groupId
                  << ",adaptiveAutosarAppName=" << adaptiveAutosarAppName
                  << ",processCommandLine=" << processCommandLine << ",processState=" << event->processState
                  << LOG_NOOP;
    }
}

void
SecurityEventsEngine::handleOsLogReportsEvent(SecurityEventSensorData& sd, SECEV_OS_LOG_REPORTS const* event)
{
    if (!event->hasVmIdentifierField())
    {
        LOG_ERROR << "Invalid event OS_LOG_REPORTS received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }
    // Requirement 3.1
    auto const     eventFrame = sd.GetEventFrame();
    HostOsLogEntry entry(static_cast<uint16_t>(eventFrame.idsMInstanceID),
                         static_cast<uint8_t>(eventFrame.sensorInstanceID),
                         event->vmIdentifier);

    const auto insertion = m_hostOsLogRateTable.emplace(
        std::piecewise_construct, std::forward_as_tuple(entry), std::forward_as_tuple(m_ratesBins, MAX_BURST));

    if (!common::types::IsMapSizeExceeded(m_hostOsLogRateTable, insertion))
    {
        // Requirement 3.2
        std::ignore = insertion.first->second.AddData(sd.GetTimestamp(), EventWeight);
        LOG_DEBUG << "Updated HostOsLogRateTable:"
                  << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
                  << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
                  << ",vmIdentifier=" << event->vmIdentifier << ",timestamp=" << sd.GetTimestamp() << LOG_NOOP;
    }
}

void
SecurityEventsEngine::handleExternalConnectionInterfaceUnsuccessfulEvent(
    SecurityEventSensorData& sd, SECEV_EXTERNAL_CONNECTION_INTERFACE_UNSUCCESSFUL const* event)
{
    if (!event->hasFields()
        && (!event->hasConnectingUnitAddressField() || !event->hasConnectionTypeField()
            || !event->hasReasonForConnectionRefusalField() || !event->hasConnectionUnitDeviceNameField()))
    {
        LOG_ERROR << "Invalid event EXTERNAL_CONNECTION_INTERFACE_UNSUCCESSFUL received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    // Requirement 4.1
    auto const eventFrame = sd.GetEventFrame();

    brain::engines::security_events::ExternalUnsuccessfulConnectionsEntry entry(
        static_cast<uint16_t>(eventFrame.idsMInstanceID),
        static_cast<uint8_t>(eventFrame.sensorInstanceID),
        static_cast<uint8_t>(event->connectionType),
        event->connectingUnitAddress,
        event->reasonForConnectionRefusal,
        common::CharArrayToString(event->connectionUnitDeviceName));

    ++m_externalUnsuccessfulConnectionsTable[entry];

    LOG_DEBUG << "Updated ExternalUnsuccessfulConnectionsTable:"
              << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
              << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
              << ",connectionType=" << event->connectionType
              << ",connectionAddress=" << entry.GetAddressOfConnectingUnit()
              << ",reasonForConnectionRefusal=" << event->reasonForConnectionRefusal
              << ",connectionUnitDeviceName=" << entry.GetConnectionUnitDeviceName() << LOG_NOOP;
}

void
SecurityEventsEngine::handleErrorEventLoggingUserLoginEvent(SecurityEventSensorData&                    sd,
                                                            SECEV_ERROR_EVENT_LOGGING_USER_LOGIN const* event)
{
    if (!event->hasFields()
        && (!event->hasSourceIpAddressField() || !event->hasUserNameField() || !event->hasFailReasonField()
            || !event->hasDestinationPortField() || !event->hasProtocolField() || !event->hasPartitionIdField()
            || !event->hasProcessNameField()))
    {
        LOG_ERROR << "Invalid event ERROR_EVENT_LOGGING_USER_LOGIN received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    auto const  eventFrame = sd.GetEventFrame();
    auto const& ipType     = ConvertIpAddress(event->sourceIpAddress);
    brain::engines::security_events::ErrorEventLoggingUserLoginCountersEntry entry{eventFrame.idsMInstanceID,
                                                                                   eventFrame.sensorInstanceID,
                                                                                   event->userName,
                                                                                   event->failReason,
                                                                                   ipType,
                                                                                   event->destinationPort,
                                                                                   event->protocol,
                                                                                   event->partitionId,
                                                                                   event->processName};

    LOG_DEBUG << "Updated ErrorEventLoggingUserLoginCounters:"
              << "idsMInstanceID=" << entry.GetIdsMInstanceId() << ",sensorInstanceID=" << entry.GetSensorInstanceId()
              << ",user name=" << entry.GetUserName() << ",fail reason=" << entry.GetFailReason()
              << ",src. IP addr.=" << FormatIpType(entry.GetSourceIpAddress())
              << ",dest. port=" << entry.GetDestinationPort() << ",protocol=" << entry.GetProtocol()
              << ",partition ID=" << entry.GetPartitionId() << ",processName=" << entry.GetProcessName() << LOG_NOOP;
}

void
SecurityEventsEngine::handleExternalDataStorageEvent(SecurityEventSensorData&                      sd,
                                                     SECEV_EXTERNAL_DATA_STORAGE_CONNECTION const* event)
{
    if (!event->hasFields()
        && (!event->hasConnectionTypeField() || !event->hasHardwareIdSerialNumberField()
            || !event->hasFileSystemField()))
    {
        LOG_ERROR << "Invalid event EXTERNAL_DATA_STORAGE_CONNECTION received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    LOG_VERBOSE << "External Data Storage" << LOG_NOOP;
    // Requirement 5.1 HCP3
    auto const                                                eventFrame = sd.GetEventFrame();
    brain::engines::security_events::ExternalDataStorageEntry entry(eventFrame.idsMInstanceID,
                                                                    eventFrame.sensorInstanceID,
                                                                    event->connectionType,
                                                                    std::string(event->hardwareIdSerialNumber),
                                                                    event->fileSystem);

    ++m_externalDataStorageTable[entry];

    LOG_VERBOSE << "Updated Data Storage table" << LOG_NOOP;
}

void
SecurityEventsEngine::handleExternalNewHWConnection(SecurityEventSensorData&                sd,
                                                    SECEV_EXTERNAL_NEW_HW_CONNECTION const* event)
{
    if (!event->hasFields()
        && (!event->hasConnectedHardwareTypeField() || !event->hasHardwareIdSerialField()
            || !event->hasDeviceSubClassesField() || !event->hasCalledLriverLibraryField()
            || !event->hasHandlingConnectionDriverLibraryField()))
    {
        LOG_ERROR << "Invalid event EXTERNAL_NEW_HW_CONNECTION received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    // Requirement 6.1 HCP3
    LOG_VERBOSE << "Additional External Hardware Connectivity" << LOG_NOOP;
    brain::engines::security_events::ExternalNewHWConnectionEntry entry(
        sd.GetEventFrame().idsMInstanceID,
        sd.GetEventFrame().sensorInstanceID,
        static_cast<uint8_t>(event->connectedHardwareType),
        std::string(event->hardwareIdSerial),
        std::string(event->deviceSubClasses),
        std::string(event->calledLriverLibrary),
        std::string(event->handlingConnectionDriverLibrary));

    ++m_externalNewHWConnectionTable[entry];

    LOG_VERBOSE << "Updated New HW Connection table" << LOG_NOOP;
}

void
SecurityEventsEngine::fillKeepAliveRuleEval(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                                            SecurityEventSensorData const&                           sd)
{
    com_vwg_connect_ids_idsperiodicreport_v1_SecEventKeepAliveTimeoutAlert secEventKeepAliveTimeoutAlert
        = com_vwg_connect_ids_idsperiodicreport_v1_SecEventKeepAliveTimeoutAlert_init_default;
    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    ruleEval.which_RuleData = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_secEventKeepAliveTimeoutAlert_tag);
    secEventKeepAliveTimeoutAlert.timestamp             = ruleEval.timestamp;
    secEventKeepAliveTimeoutAlert.exceededTimeoutPeriod = m_keepAliveTimeoutPeriod;
    secEventKeepAliveTimeoutAlert.eventDefinitionId     = sd.GetEventFrame().eventDefinitionId;
    secEventKeepAliveTimeoutAlert.IdsMSensorInstID      = sd.GetEventFrame().idsMInstanceID;
    SET_NPB_FIELD(secEventKeepAliveTimeoutAlert, sensorInstanceID, sd.GetEventFrame().sensorInstanceID);
    ruleEval.RuleData.secEventKeepAliveTimeoutAlert = secEventKeepAliveTimeoutAlert;
}

void
SecurityEventsEngine::createKeepaliveTimeoutAlert(SensorDataPtr sdPtr)
{
    // Noise filter
    auto sd = *sdPtr.get();

    // Handle rule evaluation
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
    fillKeepAliveRuleEval(ruleEval, sd);

    // Create event
    auto const eventFrame = sd.GetEventFrame();
    LOG_DEBUG << "Create KeepaliveTimeout Alert for "
              << "eventId: " << static_cast<uint32_t>(eventFrame.eventDefinitionId)
              << ",idsMInstanceId:" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
              << ",sensorInstanceId:" << static_cast<uint8_t>(eventFrame.sensorInstanceID) << LOG_NOOP;

    if (!addEventAlert(ruleEval, CriticalEventAlert::SecevKeepaliveTimeoutAlert, sd))
    {
        common::counters::IncreaseCounter(m_failedCounter);
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
    }
}

void
SecurityEventsEngine::handleKeepAliveEvent(SecurityEventSensorData const& sd, SECEV_KEEP_ALIVE_MESSAGE const* /*event*/)
{
    LOG_VERBOSE << "handle SecurityEvent KeepAlive event..." << LOG_NOOP;

    uint16_t eventDefinitionId = sd.GetEventFrame().eventDefinitionId;
    uint16_t idsMInstanceID    = sd.GetEventFrame().idsMInstanceID;
    uint8_t  sensorInstanceID  = sd.GetEventFrame().sensorInstanceID;

    LOG_DEBUG << "Process KeepAliveSecev,"
              << " eventId: " << eventDefinitionId << ", idsMInstanceId:" << idsMInstanceID
              << ", sensorInstanceId:" << static_cast<int>(sensorInstanceID) << LOG_NOOP;

    SensorDataPtr sharedSd = std::make_shared<SecurityEventSensorData>(sd);

    SecurityEventUniqeIdentifierEntry entry{idsMInstanceID, sensorInstanceID, eventDefinitionId};
    auto                              entryIdx = m_keepAliveTimersTable.find(entry);
    if (entryIdx == m_keepAliveTimersTable.end())
    {
        auto newTimerRegistrationKey = m_keepAliveTimer->Register(
            common::S_TO_MS(m_keepAliveTimeoutPeriod),
            [this, sharedSd]() {
                createKeepaliveTimeoutAlert(sharedSd);
            },
            true);
        m_keepAliveTimersTable[entry] = newTimerRegistrationKey;
        return;
    }

    // entry found
    auto& timerRegistrationKey = m_keepAliveTimersTable.at(entry);

    if (nullptr == m_keepAliveTimer)
    {
        LOG_ERROR << "Timer is null, can't set data arrived event" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCounter);
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    // Reset timer
    if (0U != timerRegistrationKey)
    {
        std::ignore          = m_keepAliveTimer->Deregister(timerRegistrationKey);
        timerRegistrationKey = common::Timer::INVALID_TIMER_REGISTRATION_KEY;
    }
    // Re-arm timer, cyclic ensure timer will be re-armed
    timerRegistrationKey = m_keepAliveTimer->Register(
        common::S_TO_MS(m_keepAliveTimeoutPeriod),
        [this, sharedSd]() {
            createKeepaliveTimeoutAlert(sharedSd);
        },
        true);

    if (common::Timer::TIMER_REGISTRATION_KEY_ERROR == timerRegistrationKey)
    {
        timerRegistrationKey = 0;
        common::counters::IncreaseCounter(m_failedCounter);
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }
}

void
SecurityEventsEngine::handleDataDefinitionL3CheckFailedEvent(SecurityEventSensorData&                     sd,
                                                             SECEV_DATA_DEFINITION_L3_CHECK_FAILED const* event)
{
    if (!event->hasFields() && (!event->hasDroppedBlockedConnectionCountField() || !isIpAnomaliesEntryValid(event)))
    {
        LOG_ERROR << "Invalid event DATA_DEFINITION_L3_CHECK_FAILED received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    brain::engines::security_events::IpAnomaliesCountersEntry entry{};
    auto const                                                eventFrame = sd.GetEventFrame();

    initIpAnomaliesCountersEntry(entry, eventFrame, event);

    m_droppedBlockedConnectionsTable[entry] += event->droppedBlockedConnectionCount;

    LOG_DEBUG << "Updated BlockedConnectionsTable: "
              << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
              << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
              << ",busId=" << entry.GetBusId() << ",sourceIpAddress=" << FormatIpType(entry.GetSourceIpAddress())
              << ",sourcePort=" << entry.GetSourcePort()
              << ",destinationIpAddress=" << FormatIpType(entry.GetDestinationIpAddress())
              << ",destinationPort=" << entry.GetDestinationPort()
              << ",droppedBlockedConnectionCount=" << event->droppedBlockedConnectionCount << LOG_NOOP;
}

void
SecurityEventsEngine::handleEthernetCommunicationInterruptionEvent(
    SecurityEventSensorData& sd, SECEV_ETHERNET_COMMUNICATION_INTERRUPTION const* event)
{
    if (!event->hasFields()
        && (!event->hasBusIdField() || !event->hasCommunicationServerIdField() || !event->hasTimeoutDtcCounterField()))
    {
        LOG_ERROR << "Invalid event ETHERNET_COMMUNICATION_INTERRUPTION received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    // Ethernet Anomalies Monitoring
    auto const                                                        eventFrame = sd.GetEventFrame();
    brain::engines::security_events::EthernetServiceInterruptionEntry entry{
        eventFrame.idsMInstanceID, eventFrame.sensorInstanceID, event->busId, event->communicationServerId};
    m_ethernetServiceInterruptionTable[entry] += event->timeoutDtcCounter;

    LOG_DEBUG << "Updated EthernetServiceInterruptionTable: "
              << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
              << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID) << ",busId=" << event->busId
              << ",communicationServerId=" << event->communicationServerId
              << ",timeoutDtcCounter=" << event->timeoutDtcCounter << LOG_NOOP;
}

void
SecurityEventsEngine::handleExternalInterfacesUsageStatisticsEvent(
    SecurityEventSensorData& sd, SECEV_EXTERNAL_INTERFACES_USAGE_STATISTICS const* event)
{
    if (!event->hasFields()
        && (!event->hasNewSessionsInLayerCountField() || !event->hasTotalPacketsPassedField()
            || !event->hasTotalBytesPassedField() || !event->hasConnectionTypeField() || !event->hasLayerTypeField()))
    {
        LOG_ERROR << "Invalid event EXTERNAL_INTERFACES_USAGE_STATISTICS received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    auto const                                                              eventFrame = sd.GetEventFrame();
    brain::engines::security_events::ExternalInterfacesUsageStatisticsEntry entry(
        static_cast<uint16_t>(eventFrame.idsMInstanceID),
        static_cast<uint8_t>(eventFrame.sensorInstanceID),
        static_cast<uint8_t>(event->connectionType),
        static_cast<uint16_t>(event->layerType));

    uint32_t newSessionsInLayerCount{};
    uint32_t totalPacketsPassed{};
    uint64_t totalBytesPassed{};

    if (!IsEmptyUint32(event->newSessionsInLayerCount))
    {
        newSessionsInLayerCount = event->newSessionsInLayerCount;
    }
    
    if (!IsEmptyUint32(event->totalPacketsPassed))
    {
        totalPacketsPassed = event->totalPacketsPassed;
    }
    
    if (!IsEmptyArray(event->totalBytesPassed, sizeof(event->totalBytesPassed)))
    {
        totalBytesPassed = *(reinterpret_cast<const uint64_t*>(event->totalBytesPassed));
    }

    if (m_externalInterfacesUsageStatisticsTable.find(entry) == m_externalInterfacesUsageStatisticsTable.end())
    {
        m_externalInterfacesUsageStatisticsTable[entry]
            = {newSessionsInLayerCount, totalPacketsPassed, totalBytesPassed};
    }
    else
    {
        auto& data = m_externalInterfacesUsageStatisticsTable[entry];
        data.newSessionsInLayerCount += newSessionsInLayerCount;
        data.totalPacketsPassed += totalPacketsPassed;
        data.totalBytesPassed += totalBytesPassed;
    }

    LOG_DEBUG << "Updated ExternalInterfacesUsageStatisticsTable: "
              << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
              << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
              << ",connectionType=" << event->connectionType << ",layerType=" << event->layerType
              << ",newSessionsInLayerCount=" << newSessionsInLayerCount << ",totalPacketsPassed=" << totalPacketsPassed
              << ",totalBytesPassed=" << totalBytesPassed << LOG_NOOP;
}

void
SecurityEventsEngine::handleSwitchDataflowStatisticsEvent(SecurityEventSensorData&                sd,
                                                          SECEV_SWITCH_DATAFLOW_STATISTICS const* event)
{
    if (!event->hasFields()
        && (!event->hasDropPktBufOverrungField() || !event->hasDropPktCrCField() || !event->hasOversizePktField()
            || !event->hasUndersizePktField() || !event->hasAlgnmtErrField() || !event->hasIfOutOctets1Field()
            || !event->hasIfOutOctets2Field() || !event->hasIfInOctets1Field() || !event->hasIfInOctets2Field()))
    {
        LOG_ERROR << "Invalid event SWITCH_DATAFLOW_STATISTICS received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    if (m_ethStats && !m_ethStats->HandleEvent(this, sd, event))
    {
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
    }
}

void
SecurityEventsEngine::handleDisallowedLayer3ProtocolEvent(SecurityEventSensorData&                    sd,
                                                          SECEV_DETECTED_UNALLOWED_L3_PROTOCOL const* event)
{
    if (!event->hasFields() && (!event->hasProtocolIdField() || !isIpAnomaliesEntryValid(event)))
    {
        LOG_ERROR << "Invalid event DETECTED_UNALLOWED_L3_PROTOCOL received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    brain::engines::security_events::DisallowedLayer3ProtocolEntry entry{};
    auto                                                           eventFrame = sd.GetEventFrame();

    initIpAnomaliesCountersEntry(entry, eventFrame, event);
    entry.SetProtocolId(event->protocolId);

    ++m_disallowedLayer3ProtocolCountersTable[entry];

    LOG_DEBUG << "Updated DisallowedLayer3ProtocolCountersTable: "
              << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
              << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
              << ",busId=" << entry.GetBusId() << ",sourceIpAddress=" << FormatIpType(entry.GetSourceIpAddress())
              << ",sourcePort=" << entry.GetSourcePort()
              << ",destinationIpAddress=" << FormatIpType(entry.GetDestinationIpAddress())
              << ",destinationPort=" << entry.GetDestinationPort() << ",protocolId=" << *entry.GetProtocolId()
              << LOG_NOOP;
}

void
SecurityEventsEngine::handleDroppedTcpPacketsEvent(SecurityEventSensorData&                 sd,
                                                   SECEV_TCPIP_SEV_DROP_INV_PORT_TCP const* event)
{
    if (!event->hasFields() && (!event->hasFwRuleIdField() || !isIpAnomaliesEntryValid(event)))
    {
        LOG_ERROR << "Invalid event TCPIP_SEV_DROP_INV_PORT_TCP received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    InvalidAddressDestinationPortCounterEntry entry{};
    auto const                                eventFrame = sd.GetEventFrame();

    initIpAnomaliesCountersEntry(entry, eventFrame, event);
    entry.SetFwRuleId(event->fwRuleId);

    ++m_invalidTcpDestinationPortCounterTable[entry];

    LOG_DEBUG << "Updated InvalidTcpDestinationPortCounterTable: "
              << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
              << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
              << ",busId=" << entry.GetBusId() << ",sourceIpAddress=" << FormatIpType(entry.GetSourceIpAddress())
              << ",sourcePort=" << entry.GetSourcePort()
              << ",destinationIpAddress=" << FormatIpType(entry.GetDestinationIpAddress())
              << ",destinationPort=" << entry.GetDestinationPort() << ",firewallRuleId=" << entry.GetFwRuleId()
              << LOG_NOOP;
}

void
SecurityEventsEngine::handleDroppedUdpPacketsEvent(SecurityEventSensorData&                 sd,
                                                   SECEV_TCPIP_SEV_DROP_INV_PORT_UDP const* event)
{
    if (!event->hasFields() && (!event->hasFwRuleIdField() || !isIpAnomaliesEntryValid(event)))
    {
        LOG_ERROR << "Invalid event TCPIP_SEV_DROP_INV_PORT_UDP received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    InvalidAddressDestinationPortCounterEntry entry{};
    auto const                                eventFrame = sd.GetEventFrame();

    initIpAnomaliesCountersEntry(entry, eventFrame, event);
    entry.SetFwRuleId(event->fwRuleId);

    ++m_invalidUdpDestinationPortCounterTable[entry];

    LOG_DEBUG << "Updated InvalidUdpDestinationPortCounterTable: "
              << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
              << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
              << ",busId=" << entry.GetBusId() << ",sourceIpAddress=" << FormatIpType(entry.GetSourceIpAddress())
              << ",sourcePort=" << entry.GetSourcePort()
              << ",destinationIpAddress=" << FormatIpType(entry.GetDestinationIpAddress())
              << ",destinationPort=" << entry.GetDestinationPort() << ",firewallRuleId=" << entry.GetFwRuleId()
              << LOG_NOOP;
}

void
SecurityEventsEngine::handleDroppedIpv4AddressEvent(SecurityEventSensorData&                  sd,
                                                    SECEV_TCPIP_SEV_DROP_INV_IPV4_ADDR const* event)
{
    if (!event->hasFields() && (!event->hasFwRuleIdField() || !isIpAnomaliesEntryValid(event)))
    {
        LOG_ERROR << "Invalid event TCPIP_SEV_DROP_INV_IPV4_ADDR received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    InvalidAddressDestinationPortCounterEntry entry{};
    auto                                      eventFrame = sd.GetEventFrame();

    initIpAnomaliesCountersEntry(entry, eventFrame, event);
    entry.SetFwRuleId(event->fwRuleId);

    ++m_invalidIpv4AddressCounterTable[entry];

    LOG_DEBUG << "Updated InvalidIpv4AddressCounterTable: "
              << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
              << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
              << ",busId=" << entry.GetBusId() << ",sourceIpAddress=" << FormatIpType(entry.GetSourceIpAddress())
              << ",sourcePort=" << entry.GetSourcePort()
              << ",destinationIpAddress=" << FormatIpType(entry.GetDestinationIpAddress())
              << ",destinationPort=" << entry.GetDestinationPort() << ",firewallRuleId=" << entry.GetFwRuleId()
              << LOG_NOOP;
}

void
SecurityEventsEngine::handleDroppedIpv6AddressEvent(SecurityEventSensorData&                  sd,
                                                    SECEV_TCPIP_SEV_DROP_INV_IPV6_ADDR const* event)
{
    if (!event->hasFields() && (!event->hasFwRuleIdField() || !isIpAnomaliesEntryValid(event)))
    {
        LOG_ERROR << "Invalid event TCPIP_SEV_DROP_INV_IPV6_ADDR received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    InvalidAddressDestinationPortCounterEntry entry{};
    auto                                      eventFrame = sd.GetEventFrame();

    initIpAnomaliesCountersEntry(entry, eventFrame, event);
    entry.SetFwRuleId(event->fwRuleId);

    ++m_invalidIpv6AddressCounterTable[entry];

    LOG_DEBUG << "Updated InvalidIpv6AddressCounterTable: "
              << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
              << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
              << ",busId=" << entry.GetBusId() << ",sourceIpAddress=" << FormatIpType(entry.GetSourceIpAddress())
              << ",sourcePort=" << entry.GetSourcePort()
              << ",destinationIpAddress=" << FormatIpType(entry.GetDestinationIpAddress())
              << ",destinationPort=" << entry.GetDestinationPort() << ",firewallRuleId=" << entry.GetFwRuleId()
              << LOG_NOOP;
}

void
SecurityEventsEngine::HandleFreshnessValueFailedEvent(SecurityEventSensorData&                       sd,
                                                      SECEV_SECOC_SEV_FRESHNESS_NOT_AVAILABLE const* event)
{
    if (!event->hasFields() && (!event->hasPduIdField() || !event->hasFvmErrorCodeField()))
    {
        LOG_ERROR << "Invalid event SECOC_SEV_FRESHNESS_NOT_AVAILABLE received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    auto const                eventFrame = sd.GetEventFrame();
    FreshnessValueFailedEntry entry{
        eventFrame.idsMInstanceID, eventFrame.sensorInstanceID, event->fvmErrorCode, event->pduId};

    ++m_freshnessValueFailedCountersTable[entry];

    LOG_DEBUG << "Updated FreshnessValueFailedCountersTable: "
              << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
              << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
              << ",fvmErrorCode=" << event->fvmErrorCode << ",pduId=" << event->pduId << LOG_NOOP;
    common::counters::IncreaseCounter(m_freshnessValueFailedTableCounter);
}

void
SecurityEventsEngine::handleDisallowedLayer4ProtocolEvent(SecurityEventSensorData&                    sd,
                                                          SECEV_DETECTED_UNALLOWED_L4_PROTOCOL const* event)
{
    if (!event->hasFields() && (!event->hasFirewallIdField() || !isIpAnomaliesEntryValid(event)))
    {
        LOG_ERROR << "Invalid event DETECTED_UNALLOWED_L4_PROTOCOL received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    DisallowedLayer4ProtocolEntry entry{};
    auto const                    eventFrame = sd.GetEventFrame();

    initIpAnomaliesCountersEntry(entry, eventFrame, event);
    entry.SetFwRuleId(event->firewallId);

    ++m_disallowedLayer4ProtocolCountersTable[entry];

    LOG_DEBUG << "Updated DisallowedLayer4ProtocolCountersTable: "
              << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
              << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
              << ",busId=" << entry.GetBusId() << ",sourceIpAddress=" << FormatIpType(entry.GetSourceIpAddress())
              << ",sourcePort=" << entry.GetSourcePort()
              << ",destinationIpAddress=" << FormatIpType(entry.GetDestinationIpAddress())
              << ",destinationPort=" << entry.GetDestinationPort() << ",firewallRuleId=" << entry.GetFwRuleId()
              << LOG_NOOP;
}

void
SecurityEventsEngine::handleUnusedPortConnectionRequestEvent(SecurityEventSensorData&                    sd,
                                                             SECEV_UNUSED_PORT_CONNECTION_REQUEST const* event)
{
    if (!event->hasFields() && (!event->hasTransportProtocolField() || !isIpAnomaliesEntryValid(event)))
    {
        LOG_ERROR << "Invalid event UNUSED_PORT_CONNECTION_REQUEST received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    UnusedPortConnectionRequestEntry entry{};
    auto                             eventFrame = sd.GetEventFrame();

    initIpAnomaliesCountersEntry(entry, eventFrame, event);
    entry.SetTransportProtocol(common::CharArrayToString(event->transportProtocol));

    ++m_unusedPortConnectionAttemptsTable[entry];

    LOG_DEBUG << "Updated UnusedPortConnectionAttemptsTable: "
              << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
              << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
              << ",busId=" << entry.GetBusId() << ",sourceIpAddress=" << FormatIpType(entry.GetSourceIpAddress())
              << ",sourcePort=" << event->sourcePort
              << ",destinationIpAddress=" << FormatIpType(entry.GetDestinationIpAddress())
              << ",destinationPort=" << event->destinationPortRequest
              << ",transportProtocol=" << entry.GetTransportProtocol() << LOG_NOOP;
}

void
SecurityEventsEngine::updateSecurityEventsCountersTable(uint16_t idsMInstanceID,
                                                        uint8_t  sensorInstanceID,
                                                        uint16_t eventID,
                                                        uint16_t count)
{
    SecurityEventsCountersEntry entry{idsMInstanceID, sensorInstanceID, eventID};
    m_securityEventsCountersTable[entry] += count;

    LOG_DEBUG << "Updated security events counters table: "
              << "idsMInstanceID=" << idsMInstanceID << ",sensorInstanceID=" << sensorInstanceID
              << ",event ID=" << eventID << ",count=" << m_securityEventsCountersTable[entry] << LOG_NOOP;
    common::counters::IncreaseCounter(m_SETableCounter);
}

void
SecurityEventsEngine::UpdateSecurityEventsCountersTable(SecurityEventFrame eventFrame)
{
    updateSecurityEventsCountersTable(eventFrame.idsMInstanceID, eventFrame.sensorInstanceID, eventFrame.eventDefinitionId, eventFrame.count);
}

void
SecurityEventsEngine::handleOversizedPacketsHistogram(SecurityEventSensorData&               sd,
                                                      SECEV_MESSAGE_MAX_SIZE_EXCEEDED const* event)
{
    if (!event->hasFields()
        && (!event->hasPackageSizeField() || !event->hasDestinationPortField() || !event->hasSourcePortField()
            || !event->hasTransportProtocolField() || !event->hasSourceIpAddressField()
            || !event->hasDestinationIpAddressField() || !event->hasBusIdField()))
    {
        LOG_ERROR << "Invalid event MESSAGE_MAX_SIZE_EXCEEDED received" << LOG_NOOP;
        HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
        return;
    }

    auto eventFrame = sd.GetEventFrame();

    IpType sourceIp{ConvertIpAddress(event->sourceIpAddress)};
    IpType destinationIp{ConvertIpAddress(event->destinationIpAddress)};

    OversizedPacketsHistogramEntry entry{eventFrame.idsMInstanceID,
                                         eventFrame.sensorInstanceID,
                                         static_cast<uint16_t>(event->busId),
                                         sourceIp,
                                         destinationIp,
                                         static_cast<uint32_t>(event->sourcePort),
                                         static_cast<uint32_t>(event->destinationPort),
                                         event->transportProtocol};

    auto const it = m_oversizedPacketsHistogramTable.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(entry),
        std::forward_as_tuple(brain::histogram::ScalarHistogram{m_packageSizeBins}));

    if (!common::types::IsMapSizeExceeded(m_oversizedPacketsHistogramTable, it))
    {
        double interval{};
        std::ignore = it.first->second.Update(sd.GetTimestamp(), event->packageSize, EventWeight, interval);

        LOG_DEBUG << "Updated Oversized Packets Histogram for SECEV_MESSAGE_MAX_SIZE_EXCEEDED event:: "
                  << "idsMInstanceID=" << static_cast<uint16_t>(eventFrame.idsMInstanceID)
                  << ",sensorInstanceID=" << static_cast<uint8_t>(eventFrame.sensorInstanceID)
                  << ",busId=" << event->busId << ",sourceIpAddress=" << FormatIpType(sourceIp)
                  << ",sourcePort=" << event->sourcePort << ",destinationIpAddress=" << FormatIpType(destinationIp)
                  << ",destinationPort=" << event->destinationPort
                  << ",transportProtocol=" << entry.GetTransportProtocol() << ",packageSize=" << event->packageSize
                  << LOG_NOOP;
    }
}

void
SecurityEventsEngine::HandleUnknownEventIdAlert(SecurityEventSensorData& securityEventSD)
{
    common::counters::IncreaseCounter(m_UnknownEventIdAlertCounter);
    // Handle rule evaluation
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
    createSecurityEventAlert(ruleEval, securityEventSD, SecurityEventType::Unknown, {});

    if (!addEventAlert(ruleEval, CriticalEventAlert::UnknownEventIdEventName, securityEventSD))
    {
        common::counters::IncreaseCounter(m_failedCounter);
        HandleDroppedSecurityEvent(securityEventSD, DropReason::SecurityEventsEngine);
    }
}

void SecurityEventsEngine::handleDroppedSecurityEvent(uint16_t   idsMInstanceID,
                                                      uint8_t    sensorInstanceID,
                                                      uint16_t   eventID,
                                                      DropReason dropReason)
{
    auto const&                              dropReasonStr = DropReasonMap.at(dropReason);
    DroppedSecurityEventsCountersEntry const entry{idsMInstanceID, sensorInstanceID, eventID, dropReasonStr};
    ++m_droppedSecurityEventsCountersTable[entry];

    LOG_DEBUG << "Update dropped security events counters table: "
              << "IDSm inst. ID=" << idsMInstanceID << ", sensor inst. ID=" << sensorInstanceID
              << ", event ID=" << eventID << ", dropReason = " << dropReasonStr
              << ", count=" << m_droppedSecurityEventsCountersTable[entry] << LOG_NOOP;
    common::counters::IncreaseCounter(m_droppedSETableCounter);
}

void
SecurityEventsEngine::HandleDhmDroppedSecurityEvent(ConstraintId constraintId, DropReason dropReason)
{
    auto const&                                 dropReasonStr = DropReasonMap.at(dropReason);
    DhmDroppedSecurityEventsCountersEntry const entry{constraintId, dropReason};

    ++m_dhmDroppedSecurityEventsCountersTable[entry];

    LOG_DEBUG << "Update dhm dropped security events counters table: "
              << " constraintId " << static_cast<uint8_t>(constraintId) << ", dropReason " << dropReasonStr
              << ", count=" << m_dhmDroppedSecurityEventsCountersTable[entry] << LOG_NOOP;
    common::counters::IncreaseCounter(m_droppedSETableCounter);
}

void
SecurityEventsEngine::HandleDroppedSecurityEvent(SecurityEventSensorData const& sd, DropReason dropReason)
{
    handleDroppedSecurityEvent(sd.GetEventFrame().idsMInstanceID, sd.GetEventFrame().sensorInstanceID, sd.GetEventId(), dropReason);
}

void
SecurityEventsEngine::HandleDroppedSecurityEventExt(UPSensorData sd, DropReason dropReason)
{
    if (!sd)
    {
        LOG_ERROR << "Handling dropped Security Events - no sensor data" << LOG_NOOP;
        return;
    }
    try
    {
        auto const& securityEventSD = dynamic_cast<brain::sensor_data::SecurityEventSensorData const&>(*sd);
        SecurityEventsEngine::HandleDroppedSecurityEventExt(securityEventSD, dropReason);
    }
    catch (std::bad_cast const& /*e*/)
    {
        LOG_ERROR << "Handling dropped Security Events - sd cannot be casted to SecurityEventSensorData" << LOG_NOOP;
    }
}


void
SecurityEventsEngine::HandleDroppedSecurityEventExt(SecurityEventSensorData const& sd, DropReason dropReason)
{
    auto* app = BrainApp::GetInstance();
    if (nullptr == app)
    {
        LOG_ERROR << "Handling dropped Security Events - brain app not initialized" << LOG_NOOP;
        return;
    }
    auto engDispatcher = std::static_pointer_cast<EngineDispatcher>(app->GetEngineDispatcher());
    if (!engDispatcher)
    {
        LOG_ERROR << "Handling dropped Security Events - cannot get brain app instance" << LOG_NOOP;
        return;
    }
    auto seEng = engDispatcher->GetSecurityEventsEngine();
    if (!seEng)
    {
        LOG_ERROR << "Handling dropped Security Events - SE engine is null" << LOG_NOOP;
        return;
    }
    
    seEng->HandleDroppedSecurityEvent(sd, dropReason);
}

void
SecurityEventsEngine::HandleDhmDroppedSecurityEventExt(ConstraintId constraintId, DropReason dropReason)
{
    auto* app = BrainApp::GetInstance();
    if (nullptr == app)
    {
        LOG_ERROR << "Handling dropped Security Events - brain app not initialized" << LOG_NOOP;
        return;
    }
    auto engDispatcher = std::static_pointer_cast<EngineDispatcher>(app->GetEngineDispatcher());
    if (!engDispatcher)
    {
        LOG_ERROR << "Handling dropped Security Events - cannot get brain app instance" << LOG_NOOP;
        return;
    }
    auto seEng = engDispatcher->GetSecurityEventsEngine();
    if (!seEng)
    {
        LOG_ERROR << "Handling dropped Security Events - SE engine is null" << LOG_NOOP;
        return;
    }

    seEng->HandleDhmDroppedSecurityEvent(constraintId, dropReason);
}

void
SecurityEventsEngine::UpdateCriticalSecurityEventsAlertsCountersTable(uint16_t eventId)
{
    auto const eventIdEnum = static_cast<EventIds>(eventId);
    ++m_criticalSecurityEventsAlertsCountersTable[eventIdEnum];

    LOG_DEBUG << "Update critical security events alerts counters table: "
              << "event ID=" << eventId << ", count=" << m_criticalSecurityEventsAlertsCountersTable[eventIdEnum]
              << LOG_NOOP;
    common::counters::IncreaseCounter(m_criticalSETableCounter);
}
