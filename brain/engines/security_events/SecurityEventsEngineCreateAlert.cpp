/**
 * @file
 * @brief     A rule engine for the Security Events.
 *            Contains the implementation for critical security event alert serialization.
 */
#include "SecurityEventsEngine.hpp"

using brain::engines::security_events::SecurityEventsEngine;
using brain::engines::security_events::EventIds;

#define CHECK_EVENT(event, eventId)                                                                \
    do                                                                                             \
    {                                                                                              \
        if (nullptr == event)                                                                      \
        {                                                                                          \
            LOG_ERROR << "Decoding of the SE 0x" << std::hex << eventId                            \
                      << " failed, the serialization of context data is not possible" << LOG_NOOP; \
            return false;                                                                          \
        }                                                                                          \
    } while (false)

namespace brain
{
namespace engines
{
namespace security_events
{
static inline common::nanopb::Array
convertIpAddressToArray(brain::engines::security_events::SECEV_ipaddr const& addr)
{
    return {reinterpret_cast<uint8_t const*>(&addr), sizeof(addr)};
}

}  // namespace security_events
}  // namespace engines
}  // namespace brain

bool SecurityEventsEngine::CreateSecurityEventData(
    com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData& securityEventAlert, SecurityEventSensorData& sd)
{
    auto const eventFrame                                   = sd.GetEventFrame();
    securityEventAlert.has_eventFrame                       = true;
    securityEventAlert.eventFrame.protocolHeaderContextData = eventFrame.protocolHeaderContextData;
    securityEventAlert.eventFrame.protocolHeaderSignature   = eventFrame.protocolHeaderSignature;
    securityEventAlert.eventFrame.protocolHeaderTimestamp   = eventFrame.protocolHeaderTimestamp;
    securityEventAlert.eventFrame.protocolHeaderReserved    = eventFrame.protocolHeaderReserved;
    securityEventAlert.eventFrame.protocolVersion           = eventFrame.protocolVersion;
    securityEventAlert.eventFrame.sensorInstanceID          = eventFrame.sensorInstanceID;
    securityEventAlert.eventFrame.idsMInstanceID            = eventFrame.idsMInstanceID;
    securityEventAlert.eventFrame.eventDefinitionId         = eventFrame.eventDefinitionId;
    securityEventAlert.eventFrame.count                     = eventFrame.count;
    securityEventAlert.eventFrame.reserved                  = eventFrame.reserved;

    securityEventAlert.has_timestamp               = true;
    securityEventAlert.timestamp.timestampNano     = sd.GetAutosarTimestampNano();
    securityEventAlert.timestamp.timestampSource   = sd.GetAutosarTimestampSource();
    securityEventAlert.timestamp.timestampReserved = sd.GetAutosarTimestampReserved();
    securityEventAlert.timestamp.timestampSeconds  = sd.GetAutosarTimestampSeconds();


    auto eventId = eventFrame.eventDefinitionId;
    switch (eventId)
    {
    case EventIds::AUDI_IDS_INTELLIGENT_SENSOR:
    {
        securityEventAlert.contextData = common::nanopb::CreateEncodingCallback(sd.GetContextData());
    }
    break;
    case EventIds::ETHIF_SEV_DROP_VLAN_DOUBLE_TAG: {
        auto const* event = sd.decodeContextData<SECEV_ETHIF_SEV_DROP_VLAN_DOUBLE_TAG>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_ethifSevDropVlanDoubleTag_tag);
        securityEventAlert.protoContextData.ethifSevDropVlanDoubleTag.uid = event->uid;
        securityEventAlert.protoContextData.ethifSevDropVlanDoubleTag.successBit = event->successBit;
        m_eventDataToSerialize.resize(3U);
        m_eventDataToSerialize[0U] = {event->sourceMac, sizeof(event->sourceMac)};
        securityEventAlert.protoContextData.ethifSevDropVlanDoubleTag.sourceMac = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {event->destinationMac, sizeof(event->destinationMac)};
        securityEventAlert.protoContextData.ethifSevDropVlanDoubleTag.destinationMac = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        securityEventAlert.protoContextData.ethifSevDropVlanDoubleTag.payloadSize = event->payloadSize;
        m_eventDataToSerialize[2U] = {event->payload, sizeof(event->payload)};
        securityEventAlert.protoContextData.ethifSevDropVlanDoubleTag.payload = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[2U]);
    }
    break;
    case EventIds::MESSAGE_BURST:
    {
        auto const* event = sd.decodeContextData<SECEV_MESSAGE_BURST>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_messageBurst_tag);
        securityEventAlert.protoContextData.messageBurst.uid = event->uid;
        securityEventAlert.protoContextData.messageBurst.successBit = event->successBit;
        securityEventAlert.protoContextData.messageBurst.busId = event->busId;
        securityEventAlert.protoContextData.messageBurst.burstMonitoringTime = event->burstMonitoringTime;
        securityEventAlert.protoContextData.messageBurst.messagePerTimeUnitThreshold = event->messagePerTimeUnitThreshold;
        securityEventAlert.protoContextData.messageBurst.communicationAttemptedsCount = event->communicationAttemptedsCount;
        securityEventAlert.protoContextData.messageBurst.busType = event->busType;
        m_eventDataToSerialize.resize(4U);
        m_eventDataToSerialize[0U] = convertIpAddressToArray(event->sourceIpAddress);
        securityEventAlert.protoContextData.messageBurst.sourceIpAddress = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = convertIpAddressToArray(event->destinationIpAddress);
        securityEventAlert.protoContextData.messageBurst.destinationIpAddress = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        m_eventDataToSerialize[2U] = {reinterpret_cast<uint8_t const*>(event->transportProtocol), sizeof(event->transportProtocol)};
        securityEventAlert.protoContextData.messageBurst.transportProtocol = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[2U]);
        securityEventAlert.protoContextData.messageBurst.sourcePortRequest = event->sourcePortRequest;
        securityEventAlert.protoContextData.messageBurst.destinationPortRequest = event->destinationPortRequest;
        securityEventAlert.protoContextData.messageBurst.messagesPerReferenceIntervalCount = event->messagesPerReferenceIntervalCount;
        securityEventAlert.protoContextData.messageBurst.timeReferenceInterval = event->timeReferenceInterval;
        m_eventDataToSerialize[3U] = {event->messagePayloadSize, sizeof(event->messagePayloadSize)};
        securityEventAlert.protoContextData.messageBurst.messagePayloadSize = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[3U]);
    }
    break;
    case EventIds::ETHIF_SEV_DROP_UNKNOWN_ETHERTYPE:
    {
        auto const* event = sd.decodeContextData<SECEV_ETHIF_SEV_DROP_UNKNOWN_ETHERTYPE>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_ethifSevDropUnknownEthertype_tag);
        securityEventAlert.protoContextData.ethifSevDropUnknownEthertype.uid = event->uid;
        securityEventAlert.protoContextData.ethifSevDropUnknownEthertype.successBit = event->successBit;
        m_eventDataToSerialize.resize(3U);
        m_eventDataToSerialize[0U] = {event->sourceMac, sizeof(event->sourceMac)};
        securityEventAlert.protoContextData.ethifSevDropUnknownEthertype.sourceMac = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {event->destinationMac, sizeof(event->destinationMac)};
        securityEventAlert.protoContextData.ethifSevDropUnknownEthertype.destinationMac = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        securityEventAlert.protoContextData.ethifSevDropUnknownEthertype.payloadSizeInBits = event->payloadSizeInBits;
        m_eventDataToSerialize[2U] = {event->payload, sizeof(event->payload)};
        securityEventAlert.protoContextData.ethifSevDropUnknownEthertype.payload = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[2U]);
        securityEventAlert.protoContextData.ethifSevDropUnknownEthertype.ethertype = event->ethertype;
    }
    break;
    case EventIds::TRUSTED_APPLICATION_INVOCATION:
    {
        auto const* event = sd.decodeContextData<SECEV_TRUSTED_APPLICATION_INVOCATION>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_trustedApplicationInvocation_tag);
        securityEventAlert.protoContextData.trustedApplicationInvocation.uid = event->uid;
        securityEventAlert.protoContextData.trustedApplicationInvocation.successBit = event->successBit;
        securityEventAlert.protoContextData.trustedApplicationInvocation.trustedApplicationNameLength = event->trustedApplicationNameLength;
        m_eventDataToSerialize.resize(3U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->trustedApplicationName), sizeof(event->trustedApplicationName)};
        securityEventAlert.protoContextData.trustedApplicationInvocation.trustedApplicationName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        securityEventAlert.protoContextData.trustedApplicationInvocation.invokingAppProcessNameLength = event->invokingAppProcessNameLength;
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->invokingAppProcessName), sizeof(event->invokingAppProcessName)};
        securityEventAlert.protoContextData.trustedApplicationInvocation.invokingAppProcessName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        securityEventAlert.protoContextData.trustedApplicationInvocation.originId = event->originId;
        m_eventDataToSerialize[2U] = {reinterpret_cast<uint8_t const*>(event->originName), sizeof(event->originName)};
        securityEventAlert.protoContextData.trustedApplicationInvocation.originName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[2U]);
    }
    break;
    case EventIds::ETHIF_SEV_DROP_ETH_MAC_COLLISIONN:
    {
        auto const* event = sd.decodeContextData<SECEV_ETHIF_SEV_DROP_ETH_MAC_COLLISIONN>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_ethifSevDropEthMacCollisionn_tag);
        securityEventAlert.protoContextData.ethifSevDropEthMacCollisionn.uid = event->uid;
        securityEventAlert.protoContextData.ethifSevDropEthMacCollisionn.successBit = event->successBit;
        m_eventDataToSerialize.resize(3U);
        m_eventDataToSerialize[0U] = {event->sourceMac, sizeof(event->sourceMac)};
        securityEventAlert.protoContextData.ethifSevDropEthMacCollisionn.sourceMac = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {event->destinationMac, sizeof(event->destinationMac)};
        securityEventAlert.protoContextData.ethifSevDropEthMacCollisionn.destinationMac = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        securityEventAlert.protoContextData.ethifSevDropEthMacCollisionn.payloadSize = event->payloadSize;
        m_eventDataToSerialize[2U] = {event->payload, sizeof(event->payload)};
        securityEventAlert.protoContextData.ethifSevDropEthMacCollisionn.payload = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[2U]);
    }
    break;
    case EventIds::AUTHENTICATION_ERRORS_REPORTS:
    {
        auto const* event = sd.decodeContextData<SECEV_AUTHENTICATION_ERRORS_REPORTS>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_authenticationErrorsReports_tag);
        securityEventAlert.protoContextData.authenticationErrorsReports.uid = event->uid;
        securityEventAlert.protoContextData.authenticationErrorsReports.successBit = event->successBit;
        securityEventAlert.protoContextData.authenticationErrorsReports.resourceId = event->resourceId;
        m_eventDataToSerialize.resize(4U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->resourceName), sizeof(event->resourceName)};
        securityEventAlert.protoContextData.authenticationErrorsReports.resourceName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        securityEventAlert.protoContextData.authenticationErrorsReports.applicationId = event->applicationId;
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->applicationName), sizeof(event->applicationName)};
        securityEventAlert.protoContextData.authenticationErrorsReports.applicationName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        securityEventAlert.protoContextData.authenticationErrorsReports.serviceId = event->serviceId;
        m_eventDataToSerialize[2U] = {reinterpret_cast<uint8_t const*>(event->serviceName), sizeof(event->serviceName)};
        securityEventAlert.protoContextData.authenticationErrorsReports.serviceName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[2U]);
        securityEventAlert.protoContextData.authenticationErrorsReports.userId = event->userId;
        m_eventDataToSerialize[3U] = {reinterpret_cast<uint8_t const*>(event->userName), sizeof(event->userName)};
        securityEventAlert.protoContextData.authenticationErrorsReports.userName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[3U]);
        securityEventAlert.protoContextData.authenticationErrorsReports.typeOfError = event->typeOfError;
        securityEventAlert.protoContextData.authenticationErrorsReports.tokenUsedInAuthentification = event->tokenUsedInAuthentification;
        securityEventAlert.protoContextData.authenticationErrorsReports.credentialsInserted = event->credentialsInserted;
    }
    break;
    case EventIds::DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevSecurityAccessNumberOfAttemptsExceeded_tag);
        securityEventAlert.protoContextData.diagSevSecurityAccessNumberOfAttemptsExceeded.uid = event->uid;
        securityEventAlert.protoContextData.diagSevSecurityAccessNumberOfAttemptsExceeded.successBit = event->successBit;
        securityEventAlert.protoContextData.diagSevSecurityAccessNumberOfAttemptsExceeded.nrc = event->nrc;
        securityEventAlert.protoContextData.diagSevSecurityAccessNumberOfAttemptsExceeded.consecutiveAttemptsCount = event->consecutiveAttemptsCount;
        securityEventAlert.protoContextData.diagSevSecurityAccessNumberOfAttemptsExceeded.maxAttemptsCount = event->maxAttemptsCount;
    }
    break;
    case EventIds::SOAD_SEV_DROP_MSG_RX_UDP_SOCKET:
    {
        auto const* event = sd.decodeContextData<SECEV_SOAD_SEV_DROP_MSG_RX_UDP_SOCKET>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_soadSevDropMsgRxUdpSocket_tag);
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpSocket.uid = event->uid;
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpSocket.successBit = event->successBit;
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpSocket.soadErrorCode = event->soadErrorCode;
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpSocket.payloadsNumber = event->payloadsNumber;
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpSocket.reconstructedPayloadSize = event->recontructedPayloadSize;
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {event->reconstructedPayload, sizeof(event->reconstructedPayload)};
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpSocket.reconstructedPayload = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpSocket.keyId = event->keyId;
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpSocket.pduId = event->pduId;
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpSocket.freshnessCounter = event->freshnessCounter;
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->computedMac), sizeof(event->computedMac)};
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpSocket.computedMac = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpSocket.availableSocketConnectionCount = event->availableSocketConnectionCount;
    }
    break;
    case EventIds::TCPIP_SEV_ARP_IP_ADDR_CONFLICT:
    {
        auto const* event = sd.decodeContextData<SECEV_TCPIP_SEV_ARP_IP_ADDR_CONFLICT>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_tcpipSevArpIpAddrConflict_tag);
        securityEventAlert.protoContextData.tcpipSevArpIpAddrConflict.uid = event->uid;
        securityEventAlert.protoContextData.tcpipSevArpIpAddrConflict.successBit = event->successBit;
        securityEventAlert.protoContextData.tcpipSevArpIpAddrConflict.busEthId = event->busEthId;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = convertIpAddressToArray(event->arpReplyIpAddress);
        securityEventAlert.protoContextData.tcpipSevArpIpAddrConflict.arpReplyIpAddress = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        securityEventAlert.protoContextData.tcpipSevArpIpAddrConflict.macAddress = event->macAddress;
    }
    break;
    case EventIds::SOAD_SEV_DROP_MSG_RX_UDP_LENGTH:
    {
        auto const* event = sd.decodeContextData<SECEV_SOAD_SEV_DROP_MSG_RX_UDP_LENGTH>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_soadSevDropMsgRxUdpLength_tag);
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpLength.uid = event->uid;
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpLength.successBit = event->successBit;
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpLength.soadErrorCode = event->soadErrorCode;
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpLength.payloadsNumber = event->payloadsNumber;
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpLength.reconstructedPayloadSize = event->recontructedPayloadSize;
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {event->reconstructedPayload, sizeof(event->reconstructedPayload)};
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpLength.reconstructedPayload = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpLength.keyId = event->keyId;
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpLength.pduId = event->pduId;
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpLength.freshnessCounter = event->freshnessCounter;
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->computedMac), sizeof(event->computedMac)};
        securityEventAlert.protoContextData.soadSevDropMsgRxUdpLength.computedMac = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
    }
    break;
    case EventIds::SECURE_BOOT_FAILED:
    {
        auto const* event = sd.decodeContextData<SECEV_SECURE_BOOT_FAILED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_secureBootFailed_tag);
        securityEventAlert.protoContextData.secureBootFailed.uid = event->uid;
        securityEventAlert.protoContextData.secureBootFailed.successBit = event->successBit;
        securityEventAlert.protoContextData.secureBootFailed.secureBootFailedStep = event->secureBootFailedStep;
        securityEventAlert.protoContextData.secureBootFailed.secureBootAttemptsCount = event->secureBootAttemptsCount;
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->failReason), sizeof(event->failReason)};
        securityEventAlert.protoContextData.secureBootFailed.failReason = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->securityCredentialsUsed), sizeof(event->securityCredentialsUsed)};
        securityEventAlert.protoContextData.secureBootFailed.securityCredentialsUsed = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
    }
    break;
    case EventIds::IDSM_INTERNAL_EVENT_TRAFFIC_LIMITATION_EXCEEDED:
    {
        auto const* event = sd.decodeContextData<SECEV_IDSM_INTERNAL_EVENT_TRAFFIC_LIMITATION_EXCEEDED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_idsmInternalEventTrafficLimitationExceeded_tag);
        securityEventAlert.protoContextData.idsmInternalEventTrafficLimitationExceeded.uid = event->uid;
        securityEventAlert.protoContextData.idsmInternalEventTrafficLimitationExceeded.successBit = event->successBit;
        securityEventAlert.protoContextData.idsmInternalEventTrafficLimitationExceeded.busType = event->busType;
        securityEventAlert.protoContextData.idsmInternalEventTrafficLimitationExceeded.busId = event->busId;
        securityEventAlert.protoContextData.idsmInternalEventTrafficLimitationExceeded.droppedEventCount = event->droppedEventCount;
        securityEventAlert.protoContextData.idsmInternalEventTrafficLimitationExceeded.trafficLimit = event->trafficLimit;
    }
    break;
    case EventIds::APN_CONFIGURATION_CHANGE_REPORTS:
    {
        auto const* event = sd.decodeContextData<SECEV_APN_CONFIGURATION_CHANGE_REPORTS>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_apnConfigurationChangeReports_tag);
        securityEventAlert.protoContextData.apnConfigurationChangeReports.uid = event->uid;
        securityEventAlert.protoContextData.apnConfigurationChangeReports.successBit = event->successBit;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->processName), sizeof(event->processName)};
        securityEventAlert.protoContextData.apnConfigurationChangeReports.processName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        securityEventAlert.protoContextData.apnConfigurationChangeReports.processId = event->processId;
    }
    break;
    case EventIds::DIAG_SEV_SECURITY_ACCESS_INVALID_KEY:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_SECURITY_ACCESS_INVALID_KEY>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevSecurityAccessInvalidKey_tag);
        securityEventAlert.protoContextData.diagSevSecurityAccessInvalidKey.uid = event->uid;
        securityEventAlert.protoContextData.diagSevSecurityAccessInvalidKey.successBit = event->successBit;
        securityEventAlert.protoContextData.diagSevSecurityAccessInvalidKey.nrc = event->nrc;
        securityEventAlert.protoContextData.diagSevSecurityAccessInvalidKey.invalidKey = event->invalidKey;
    }
    break;
    case EventIds::VKMS_UNKNOWN_KEY_REQUESTED:
    {
        auto const* event = sd.decodeContextData<SECEV_VKMS_UNKNOWN_KEY_REQUESTED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_vkmsUnknownKeyRequested_tag);
        securityEventAlert.protoContextData.vkmsUnknownKeyRequested.uid = event->uid;
        securityEventAlert.protoContextData.vkmsUnknownKeyRequested.successBit = event->successBit;
        securityEventAlert.protoContextData.vkmsUnknownKeyRequested.dtcDfcc = event->dtcDfcc;
        securityEventAlert.protoContextData.vkmsUnknownKeyRequested.dtcTi = event->dtcTi;
        securityEventAlert.protoContextData.vkmsUnknownKeyRequested.keyIdentifier = event->keyIdentifier;
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->executingServiceApp), sizeof(event->executingServiceApp)};
        securityEventAlert.protoContextData.vkmsUnknownKeyRequested.executingServiceApp = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        securityEventAlert.protoContextData.vkmsUnknownKeyRequested.originId = event->originId;
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->originName), sizeof(event->originName)};
        securityEventAlert.protoContextData.vkmsUnknownKeyRequested.originName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
    }
    break;
    case EventIds::SMS_LOG_REPORTS:
    {
        auto const* event = sd.decodeContextData<SECEV_SMS_LOG_REPORTS>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_smsLogReports_tag);
        securityEventAlert.protoContextData.smsLogReports.uid = event->uid;
        securityEventAlert.protoContextData.smsLogReports.successBit = event->successBit;
        securityEventAlert.protoContextData.smsLogReports.directionOfTheSms = event->directionOfTheSms;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {event->pduFrame, sizeof(event->pduFrame)};
        securityEventAlert.protoContextData.smsLogReports.pduFrame = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::OS_LOG_REPORTS:
    {
        auto const* event = sd.decodeContextData<SECEV_OS_LOG_REPORTS>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_osLogReports_tag);
        securityEventAlert.protoContextData.osLogReports.uid = event->uid;
        securityEventAlert.protoContextData.osLogReports.successBit = event->successBit;
        securityEventAlert.protoContextData.osLogReports.vmIdentifier = event->vmIdentifier;
        securityEventAlert.protoContextData.osLogReports.logFileSize = event->logFileSize;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->logReport), sizeof(event->logReport)};
        securityEventAlert.protoContextData.osLogReports.logReport = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::SOAD_SEV_REJECTED_TCP_CONNECTION:
    {
        auto const* event = sd.decodeContextData<SECEV_SOAD_SEV_REJECTED_TCP_CONNECTION>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_soadSevRejectedTcpConnection_tag);
        securityEventAlert.protoContextData.soadSevRejectedTcpConnection.uid = event->uid;
        securityEventAlert.protoContextData.soadSevRejectedTcpConnection.successBit = event->successBit;
        securityEventAlert.protoContextData.soadSevRejectedTcpConnection.soadErrorCode = event->soadErrorCode;
        securityEventAlert.protoContextData.soadSevRejectedTcpConnection.payloadsNumber = event->payloadsNumber;
        securityEventAlert.protoContextData.soadSevRejectedTcpConnection.reconstructedPayloadSize = event->recontructedPayloadSize;
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {event->reconstructedPayload, sizeof(event->reconstructedPayload)};
        securityEventAlert.protoContextData.soadSevRejectedTcpConnection.reconstructedPayload = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        securityEventAlert.protoContextData.soadSevRejectedTcpConnection.keyId = event->keyId;
        securityEventAlert.protoContextData.soadSevRejectedTcpConnection.pduId = event->pduId;
        securityEventAlert.protoContextData.soadSevRejectedTcpConnection.freshnessCounter = event->freshnessCounter;
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->computedMac), sizeof(event->computedMac)};
        securityEventAlert.protoContextData.soadSevRejectedTcpConnection.computedMac = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
    }
    break;
    case EventIds::VKMS_NO_KEYS_AVAILABLE:
    {
        auto const* event = sd.decodeContextData<SECEV_VKMS_NO_KEYS_AVAILABLE>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_vkmsNoKeysAvailable_tag);
        securityEventAlert.protoContextData.vkmsNoKeysAvailable.uid = event->uid;
        securityEventAlert.protoContextData.vkmsNoKeysAvailable.successBit = event->successBit;
        securityEventAlert.protoContextData.vkmsNoKeysAvailable.dtcDfcc = event->dtcDfcc;
        securityEventAlert.protoContextData.vkmsNoKeysAvailable.dtcTi = event->dtcTi;
        securityEventAlert.protoContextData.vkmsNoKeysAvailable.timeSinceEcuStartup = event->timeSinceEcuStartup;
    }
    break;
    case EventIds::IDSM_INTERNAL_EVENT_NO_EVENT_BUFFER_AVAILABLE:
    {
        auto const* event = sd.decodeContextData<SECEV_IDSM_INTERNAL_EVENT_NO_EVENT_BUFFER_AVAILABLE>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_idsmInternalEventNoEventBufferAvailable_tag);
        securityEventAlert.protoContextData.idsmInternalEventNoEventBufferAvailable.uid = event->uid;
        securityEventAlert.protoContextData.idsmInternalEventNoEventBufferAvailable.successBit = event->successBit;
        securityEventAlert.protoContextData.idsmInternalEventNoEventBufferAvailable.idsmBufferSize = event->idsmBufferSize;
        securityEventAlert.protoContextData.idsmInternalEventNoEventBufferAvailable.roppedEventCounter = event->roppedEventCounter;
    }
    break;
    case EventIds::IDSM_INTERNAL_EVENT_NO_CONTEXT_DATA_BUFFER_AVAILABLE:
    {
        auto const* event = sd.decodeContextData<SECEV_IDSM_INTERNAL_EVENT_NO_CONTEXT_DATA_BUFFER_AVAILABLE>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_idsmInternalEventNoContextDataBufferAvailable_tag);
        securityEventAlert.protoContextData.idsmInternalEventNoContextDataBufferAvailable.uid = event->uid;
        securityEventAlert.protoContextData.idsmInternalEventNoContextDataBufferAvailable.successBit = event->successBit;
        securityEventAlert.protoContextData.idsmInternalEventNoContextDataBufferAvailable.idsmBufferSize = event->idsmBufferSize;
        securityEventAlert.protoContextData.idsmInternalEventNoContextDataBufferAvailable.droppedEventCounter = event->droppedEventCounter;
    }
    break;
    case EventIds::EXTERNAL_CONNECTION_INTERFACE_UNSUCCESSFUL:
    {
        auto const* event = sd.decodeContextData<SECEV_EXTERNAL_CONNECTION_INTERFACE_UNSUCCESSFUL>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_externalConnectionInterfaceUnsuccessful_tag);
        securityEventAlert.protoContextData.externalConnectionInterfaceUnsuccessful.uid = event->uid;
        securityEventAlert.protoContextData.externalConnectionInterfaceUnsuccessful.successBit = event->successBit;
        securityEventAlert.protoContextData.externalConnectionInterfaceUnsuccessful.connectionType = event->connectionType;
        securityEventAlert.protoContextData.externalConnectionInterfaceUnsuccessful.connectingUnitAddress
            = event->connectingUnitAddress;
        securityEventAlert.protoContextData.externalConnectionInterfaceUnsuccessful.reasonForConnectionRefusal
            = event->reasonForConnectionRefusal;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->connectionUnitDeviceName),
                                      sizeof(event->connectionUnitDeviceName)};
        securityEventAlert.protoContextData.externalConnectionInterfaceUnsuccessful.connectionUnitDeviceName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::DIAG_SEV_REQUESTED_ACTIONS_REQUIRES_AUTHENTICATION:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_REQUESTED_ACTIONS_REQUIRES_AUTHENTICATION>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevRequestedActionsRequiresAuthentication_tag);
        securityEventAlert.protoContextData.diagSevRequestedActionsRequiresAuthentication.uid = event->uid;
        securityEventAlert.protoContextData.diagSevRequestedActionsRequiresAuthentication.successBit = event->successBit;
        securityEventAlert.protoContextData.diagSevRequestedActionsRequiresAuthentication.nrc = event->nrc;
        securityEventAlert.protoContextData.diagSevRequestedActionsRequiresAuthentication.diagnosticService = event->diagnosticService;
    }
    break;
    case EventIds::DIAG_SEV_SERVICE_NOT_SUPPORTED:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_SERVICE_NOT_SUPPORTED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevServiceNotSupported_tag);
        securityEventAlert.protoContextData.diagSevServiceNotSupported.uid = event->uid;
        securityEventAlert.protoContextData.diagSevServiceNotSupported.successBit = event->successBit;
        securityEventAlert.protoContextData.diagSevServiceNotSupported.nrc = event->nrc;
        securityEventAlert.protoContextData.diagSevServiceNotSupported.diagnosticService = event->diagnosticService;
    }
    break;
    case EventIds::DIAG_SEV_CERTIFICATE_FAILURE:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_CERTIFICATE_FAILURE>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevCertificateFailure_tag);
        securityEventAlert.protoContextData.diagSevCertificateFailure.uid = event->uid;
        securityEventAlert.protoContextData.diagSevCertificateFailure.successBit = event->successBit;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {event->certificate, sizeof(event->certificate)};
        securityEventAlert.protoContextData.diagSevCertificateFailure.certificate = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::ACCESS_CONTROL_CONFIGURATION_CHANGE:
    {
        auto const* event = sd.decodeContextData<SECEV_ACCESS_CONTROL_CONFIGURATION_CHANGE>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_accessControlConfigurationChange_tag);
        securityEventAlert.protoContextData.accessControlConfigurationChange.uid = event->uid;
        securityEventAlert.protoContextData.accessControlConfigurationChange.successBit = event->successBit;
        securityEventAlert.protoContextData.accessControlConfigurationChange.configurationLength = event->configurationLength;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->configuration), sizeof(event->configuration)};
        securityEventAlert.protoContextData.accessControlConfigurationChange.configuration = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::NEW_BINDING_INTERFACE_NOTIFICATION:
    {
        auto const* event = sd.decodeContextData<SECEV_NEW_BINDING_INTERFACE_NOTIFICATION>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_newBindingInterfaceNotification_tag);
        securityEventAlert.protoContextData.newBindingInterfaceNotification.uid = event->uid;
        securityEventAlert.protoContextData.newBindingInterfaceNotification.successBit = event->successBit;
        securityEventAlert.protoContextData.newBindingInterfaceNotification.connectionType = event->connectionType;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->applicationProcessName), sizeof(event->applicationProcessName)};
        securityEventAlert.protoContextData.newBindingInterfaceNotification.applicationProcessName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::CONFIGURATION_FILE_DISCREPANCY_NOTIFICATION:
    {
        auto const* event = sd.decodeContextData<SECEV_CONFIGURATION_FILE_DISCREPANCY_NOTIFICATION>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_configurationFileDiscrepancyNotification_tag);
        securityEventAlert.protoContextData.configurationFileDiscrepancyNotification.uid = event->uid;
        securityEventAlert.protoContextData.configurationFileDiscrepancyNotification.successBit = event->successBit;
        securityEventAlert.protoContextData.configurationFileDiscrepancyNotification.dtcDfcc = event->dtcDfcc;
        securityEventAlert.protoContextData.configurationFileDiscrepancyNotification.dtcTi = event->dtcTi;
    }
    break;
    case EventIds::DIAGNOSTIC_DATA_SET_DOWNLOAD:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAGNOSTIC_DATA_SET_DOWNLOAD>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagnosticDataSetDownload_tag);
        securityEventAlert.protoContextData.diagnosticDataSetDownload.uid = event->uid;
        securityEventAlert.protoContextData.diagnosticDataSetDownload.successBit = event->successBit;
        securityEventAlert.protoContextData.diagnosticDataSetDownload.updatedDid = event->updatedDid;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->didValue), sizeof(event->didValue)};
        securityEventAlert.protoContextData.diagnosticDataSetDownload.didValue = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::SOAD_SEV_DROP_PDU_RX_TCP:
    {
        auto const* event = sd.decodeContextData<SECEV_SOAD_SEV_DROP_PDU_RX_TCP>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_soadSevDropPduRxTcp_tag);
        securityEventAlert.protoContextData.soadSevDropPduRxTcp.uid = event->uid;
        securityEventAlert.protoContextData.soadSevDropPduRxTcp.successBit = event->successBit;
        securityEventAlert.protoContextData.soadSevDropPduRxTcp.soadErrorCode = event->soadErrorCode;
        securityEventAlert.protoContextData.soadSevDropPduRxTcp.payloadsNumber = event->payloadsNumber;
        securityEventAlert.protoContextData.soadSevDropPduRxTcp.reconstructedPayloadSize = event->recontructedPayloadSize;
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {event->reconstructedPayload, sizeof(event->reconstructedPayload)};
        securityEventAlert.protoContextData.soadSevDropPduRxTcp.reconstructedPayload = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        securityEventAlert.protoContextData.soadSevDropPduRxTcp.keyId = event->keyId;
        securityEventAlert.protoContextData.soadSevDropPduRxTcp.pduId = event->pduId;
        securityEventAlert.protoContextData.soadSevDropPduRxTcp.freshnessCounter = event->freshnessCounter;
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->computedMac), sizeof(event->computedMac)};
        securityEventAlert.protoContextData.soadSevDropPduRxTcp.computedMac = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
    }
    break;
    case EventIds::UNUSED_PORT_CONNECTION_REQUEST:
    {
        auto const* event = sd.decodeContextData<SECEV_UNUSED_PORT_CONNECTION_REQUEST>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_unusedPortConnectionRequest_tag);
        securityEventAlert.protoContextData.unusedPortConnectionRequest.uid = event->uid;
        securityEventAlert.protoContextData.unusedPortConnectionRequest.successBit = event->successBit;
        securityEventAlert.protoContextData.unusedPortConnectionRequest.busId = event->busEthId;
        m_eventDataToSerialize.resize(4U);
        m_eventDataToSerialize[0U] = convertIpAddressToArray(event->sourceIpAddress);
        securityEventAlert.protoContextData.unusedPortConnectionRequest.sourceIpAddress = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = convertIpAddressToArray(event->destinationIpAddress);
        securityEventAlert.protoContextData.unusedPortConnectionRequest.destinationIpAddress = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        securityEventAlert.protoContextData.unusedPortConnectionRequest.sourcePort = event->sourcePort;
        m_eventDataToSerialize[2U] = {reinterpret_cast<uint8_t const*>(event->transportProtocol), sizeof(event->transportProtocol)};
        securityEventAlert.protoContextData.unusedPortConnectionRequest.transportProtocol = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[2U]);
        securityEventAlert.protoContextData.unusedPortConnectionRequest.destinationPortRequest = event->destinationPortRequest;
        securityEventAlert.protoContextData.unusedPortConnectionRequest.messagePayloadLength = event->messagePayloadLength;
        m_eventDataToSerialize[3U] = {event->messagePayload, sizeof(event->messagePayload)};
        securityEventAlert.protoContextData.unusedPortConnectionRequest.messagePayload = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[3U]);
    }
    break;
    case EventIds::SECURITY_ERROR_EVENT_LOGGING_MONITORING:
    {
        auto const* event = sd.decodeContextData<SECEV_SECURITY_ERROR_EVENT_LOGGING_MONITORING>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_securityErrorEventLoggingMonitoring_tag);
        securityEventAlert.protoContextData.securityErrorEventLoggingMonitoring.uid = event->uid;
        securityEventAlert.protoContextData.securityErrorEventLoggingMonitoring.successBit = event->successBit;
        securityEventAlert.protoContextData.securityErrorEventLoggingMonitoring.dtcDfcc = event->dtcDfcc;
        securityEventAlert.protoContextData.securityErrorEventLoggingMonitoring.dtcTi = event->dtcTi;
        securityEventAlert.protoContextData.securityErrorEventLoggingMonitoring.vmIdentifier = event->vmIdentifier;
        securityEventAlert.protoContextData.securityErrorEventLoggingMonitoring.securityEventId = event->securityEventId;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->securityLogging), sizeof(event->securityLogging)};
        securityEventAlert.protoContextData.securityErrorEventLoggingMonitoring.securityLogging = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::DIAG_SEV_NUMBER_OF_FAILED_AUTHENTICATION_ATTEMPTS_EXCEEDED:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_NUMBER_OF_FAILED_AUTHENTICATION_ATTEMPTS_EXCEEDED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevNumberOfFailedAuthenticationAttemptsExceeded_tag);
        securityEventAlert.protoContextData.diagSevNumberOfFailedAuthenticationAttemptsExceeded.uid = event->uid;
        securityEventAlert.protoContextData.diagSevNumberOfFailedAuthenticationAttemptsExceeded.successBit = event->successBit;
        securityEventAlert.protoContextData.diagSevNumberOfFailedAuthenticationAttemptsExceeded.failedAuthenticationAttemptsCount = event->failedAuthenticationAttemptsCount;
    }
    break;
    case EventIds::DIAG_SEV_SUBFUNCTION_NOT_SUPPORTED:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_SUBFUNCTION_NOT_SUPPORTED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevSubfunctionNotSupported_tag);
        securityEventAlert.protoContextData.diagSevSubfunctionNotSupported.uid = event->uid;
        securityEventAlert.protoContextData.diagSevSubfunctionNotSupported.successBit = event->successBit;
        securityEventAlert.protoContextData.diagSevSubfunctionNotSupported.nrc = event->nrc;
        securityEventAlert.protoContextData.diagSevSubfunctionNotSupported.diagnosticSubfuncton = event->diagnosticSubfuncton;
    }
    break;
    case EventIds::DIAG_SEV_SECURITY_ACCESS_DENIED:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_SECURITY_ACCESS_DENIED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevSecurityAccessDenied_tag);
        securityEventAlert.protoContextData.diagSevSecurityAccessDenied.uid = event->uid;
        securityEventAlert.protoContextData.diagSevSecurityAccessDenied.successBit = event->successBit;
        securityEventAlert.protoContextData.diagSevSecurityAccessDenied.nrc = event->nrc;
        securityEventAlert.protoContextData.diagSevSecurityAccessDenied.diagnosticService = event->diagnosticService;
    }
    break;
    case EventIds::SECOC_SEV_MAC_VERIFICATION_FAILED:
    {
        auto const* event = sd.decodeContextData<SECEV_SECOC_SEV_MAC_VERIFICATION_FAILED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_secocSevMacVerificationFailed_tag);
        securityEventAlert.protoContextData.secocSevMacVerificationFailed.uid = event->uid;
        securityEventAlert.protoContextData.secocSevMacVerificationFailed.successBit = event->successBit;
        securityEventAlert.protoContextData.secocSevMacVerificationFailed.payloadsBeforCount = event->payloadsBeforCount;
        securityEventAlert.protoContextData.secocSevMacVerificationFailed.reconstructedPayloadSize = event->recontructedPayloadSize;
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {event->reconstructedPayload, sizeof(event->reconstructedPayload)};
        securityEventAlert.protoContextData.secocSevMacVerificationFailed.reconstructedPayload = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        securityEventAlert.protoContextData.secocSevMacVerificationFailed.keyId = event->keyId;
        securityEventAlert.protoContextData.secocSevMacVerificationFailed.pduId = event->pduId;
        securityEventAlert.protoContextData.secocSevMacVerificationFailed.freshnessCounter = event->freshnessCounter;
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->computedMac), sizeof(event->computedMac)};
        securityEventAlert.protoContextData.secocSevMacVerificationFailed.computedMac = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
    }
    break;
    case EventIds::SOAD_SEV_DROP_PDU_RX_UDP:
    {
        auto const* event = sd.decodeContextData<SECEV_SOAD_SEV_DROP_PDU_RX_UDP>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_soadSevDropPduRxUdp_tag);
        securityEventAlert.protoContextData.soadSevDropPduRxUdp.uid = event->uid;
        securityEventAlert.protoContextData.soadSevDropPduRxUdp.successBit = event->successBit;
        securityEventAlert.protoContextData.soadSevDropPduRxUdp.soadErrorCode = event->soadErrorCode;
        securityEventAlert.protoContextData.soadSevDropPduRxUdp.payloadsNumber = event->payloadsNumber;
        securityEventAlert.protoContextData.soadSevDropPduRxUdp.reconstructedPayloadSize = event->recontructedPayloadSize;
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {event->reconstructedPayload, sizeof(event->reconstructedPayload)};
        securityEventAlert.protoContextData.soadSevDropPduRxUdp.reconstructedPayload = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        securityEventAlert.protoContextData.soadSevDropPduRxUdp.keyId = event->keyId;
        securityEventAlert.protoContextData.soadSevDropPduRxUdp.pduId = event->pduId;
        securityEventAlert.protoContextData.soadSevDropPduRxUdp.freshnessCounter = event->freshnessCounter;
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->computedMac), sizeof(event->computedMac)};
        securityEventAlert.protoContextData.soadSevDropPduRxUdp.computedMac = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
    }
    break;
    case EventIds::SW_VERSION_UPDATE_MECHANISM_CHANGES:
    {
        auto const* event = sd.decodeContextData<SECEV_SW_VERSION_UPDATE_MECHANISM_CHANGES>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_swVersionUpdateMechanismChanges_tag);
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.uid = event->uid;
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.successBit = event->successBit;
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.updateMechanism = event->updateMechanism;
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.testerId = event->testerId;
        m_eventDataToSerialize.resize(5U);
        m_eventDataToSerialize[0U] = convertIpAddressToArray(event->sourceIp);
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.sourceIp = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->processTaskName), sizeof(event->processTaskName)};
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.processTaskName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.processTaskId = event->processTaskId;
        m_eventDataToSerialize[2U] = {reinterpret_cast<uint8_t const*>(event->serviceName), sizeof(event->serviceName)};
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.serviceName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[2U]);
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.updatedFileHash = event->updatedFileHash;
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.updateFileSize = event->updateFileSize;
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.signatureAlgo = event->signatureAlgo;
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.failReason = event->failReason;
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.totalBlocksCount = event->totalBlocksCount;
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.updatedBlocksCount = event->updatedBlocksCount;
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.blockId = event->blockId;
        m_eventDataToSerialize[3U] = {reinterpret_cast<uint8_t const*>(event->blockVersion), sizeof(event->blockVersion)};
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.blockVersion = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[3U]);
        m_eventDataToSerialize[4U] = {reinterpret_cast<uint8_t const*>(event->blockSignature), sizeof(event->blockSignature)};
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.blockSignature = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[4U]);
        securityEventAlert.protoContextData.swVersionUpdateMechanismChanges.blockLength = event->blockLength;
    }
    break;
    case EventIds::DIAG_SEV_REQUEST_OUT_OF_RANGE:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_REQUEST_OUT_OF_RANGE>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevRequestOutOfRange_tag);
        securityEventAlert.protoContextData.diagSevRequestOutOfRange.uid = event->uid;
        securityEventAlert.protoContextData.diagSevRequestOutOfRange.successBit = event->successBit;
        securityEventAlert.protoContextData.diagSevRequestOutOfRange.nrc = event->nrc;
        securityEventAlert.protoContextData.diagSevRequestOutOfRange.diagnosticService = event->diagnosticService;
        securityEventAlert.protoContextData.diagSevRequestOutOfRange.did = event->did;
        securityEventAlert.protoContextData.diagSevRequestOutOfRange.diagRequestLength = event->diagRequestLength;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {event->diagRequestTrace, sizeof(event->diagRequestTrace)};
        securityEventAlert.protoContextData.diagSevRequestOutOfRange.diagRequestTrace = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::CRYPTOGRAPHIC_LIB_FAILURES_NOTIFICATION:
    {
        auto const* event = sd.decodeContextData<SECEV_CRYPTOGRAPHIC_LIB_FAILURES_NOTIFICATION>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_cryptographicLibFailuresNotification_tag);
        securityEventAlert.protoContextData.cryptographicLibFailuresNotification.uid = event->uid;
        securityEventAlert.protoContextData.cryptographicLibFailuresNotification.successBit = event->successBit;
        securityEventAlert.protoContextData.cryptographicLibFailuresNotification.dtcDfcc = event->dtcDfcc;
        securityEventAlert.protoContextData.cryptographicLibFailuresNotification.dtcTi = event->dtcTi;
        m_eventDataToSerialize.resize(4U);
        m_eventDataToSerialize[0U] = convertIpAddressToArray(event->clientIp);
        securityEventAlert.protoContextData.cryptographicLibFailuresNotification.clientIp = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = convertIpAddressToArray(event->serverIp);
        securityEventAlert.protoContextData.cryptographicLibFailuresNotification.serverIp = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        m_eventDataToSerialize[2U] = {reinterpret_cast<uint8_t const*>(event->protocol), sizeof(event->protocol)};
        securityEventAlert.protoContextData.cryptographicLibFailuresNotification.protocol = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[2U]);
        securityEventAlert.protoContextData.cryptographicLibFailuresNotification.clientSourcePort = event->clientSourcePort;
        securityEventAlert.protoContextData.cryptographicLibFailuresNotification.clientDestinationPort = event->clientDestinationPort;
        m_eventDataToSerialize[3U] = {reinterpret_cast<uint8_t const*>(event->tlsIdentity), sizeof(event->tlsIdentity)};
        securityEventAlert.protoContextData.cryptographicLibFailuresNotification.tlsIdentity = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[3U]);
        securityEventAlert.protoContextData.cryptographicLibFailuresNotification.failReason = event->failReason;
        securityEventAlert.protoContextData.cryptographicLibFailuresNotification.cryptographicFunction = event->cryptographicFunction;
    }
    break;
    case EventIds::DIAG_SEV_ECU_UNLOCK_SUCCESSFUL:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_ECU_UNLOCK_SUCCESSFUL>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevEcuUnlockSuccessful_tag);
        securityEventAlert.protoContextData.diagSevEcuUnlockSuccessful.uid = event->uid;
        securityEventAlert.protoContextData.diagSevEcuUnlockSuccessful.successBit = event->successBit;
        securityEventAlert.protoContextData.diagSevEcuUnlockSuccessful.sessionUsedDuringTheActivationOfTheService = event->sessionUsedDuringTheActivationOfTheService;
        securityEventAlert.protoContextData.diagSevEcuUnlockSuccessful.seed = event->seed;
        securityEventAlert.protoContextData.diagSevEcuUnlockSuccessful.key = event->key;
        securityEventAlert.protoContextData.diagSevEcuUnlockSuccessful.keyCounterValue = event->keyCounterValue;
    }
    break;
    case EventIds::ETHIF_SEV_DROP_INV_VLAN:
    {
        auto const* event = sd.decodeContextData<SECEV_ETHIF_SEV_DROP_INV_VLAN>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_ethifSevDropInvVlan_tag);
        securityEventAlert.protoContextData.ethifSevDropInvVlan.uid = event->uid;
        securityEventAlert.protoContextData.ethifSevDropInvVlan.successBit = event->successBit;
        m_eventDataToSerialize.resize(3U);
        m_eventDataToSerialize[0U] = {event->sourceMac, sizeof(event->sourceMac)};
        securityEventAlert.protoContextData.ethifSevDropInvVlan.sourceMac = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {event->destinationMac, sizeof(event->destinationMac)};
        securityEventAlert.protoContextData.ethifSevDropInvVlan.destinationMac = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        securityEventAlert.protoContextData.ethifSevDropInvVlan.payloadSize = event->payloadSize;
        m_eventDataToSerialize[2U] = {event->payload, sizeof(event->payload)};
        securityEventAlert.protoContextData.ethifSevDropInvVlan.payload = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[2U]);
    }
    break;
    case EventIds::CONTROL_MODULE_ERROR:
    {
        auto const* event = sd.decodeContextData<SECEV_CONTROL_MODULE_ERROR>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_controlModuleError_tag);
        securityEventAlert.protoContextData.controlModuleError.uid = event->uid;
        securityEventAlert.protoContextData.controlModuleError.successBit = event->successBit;
        securityEventAlert.protoContextData.controlModuleError.dtcDfcc = event->dtcDfcc;
        securityEventAlert.protoContextData.controlModuleError.dtcTi = event->dtcTi;
    }
    break;
    case EventIds::EXTERNAL_SOURCES_FILE_DATA_STREAM:
    {
        auto const* event = sd.decodeContextData<SECEV_EXTERNAL_SOURCES_FILE_DATA_STREAM>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_externalSourcesFileDataStream_tag);
        securityEventAlert.protoContextData.externalSourcesFileDataStream.uid = event->uid;
        securityEventAlert.protoContextData.externalSourcesFileDataStream.successBit = event->successBit;
        securityEventAlert.protoContextData.externalSourcesFileDataStream.typeOfDataTransmittedFileOrDataStream = event->typeOfDataTransmittedFileOrDataStream;
        securityEventAlert.protoContextData.externalSourcesFileDataStream.dataOriginLength = event->dataOriginLength;
        securityEventAlert.protoContextData.externalSourcesFileDataStream.dataOrigin = event->dataOrigin;
        securityEventAlert.protoContextData.externalSourcesFileDataStream.destinationApplicationLength = event->destinationApplicationLength;
        securityEventAlert.protoContextData.externalSourcesFileDataStream.destinationApplication = event->destinationApplication;
        securityEventAlert.protoContextData.externalSourcesFileDataStream.dataSize = event->dataSize;
        securityEventAlert.protoContextData.externalSourcesFileDataStream.streamFileNameLength = event->streamFileNameLength;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->streamFileName), sizeof(event->streamFileName)};
        securityEventAlert.protoContextData.externalSourcesFileDataStream.streamFileName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::SW_VERIFICATION_FAILURE:
    {
        auto const* event = sd.decodeContextData<SECEV_SW_VERIFICATION_FAILURE>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_swVerificationFailure_tag);
        securityEventAlert.protoContextData.swVerificationFailure.uid = event->uid;
        securityEventAlert.protoContextData.swVerificationFailure.successBit = event->successBit;
        securityEventAlert.protoContextData.swVerificationFailure.updateMechanism = event->updateMechanism;
        securityEventAlert.protoContextData.swVerificationFailure.testerId = event->testerId;
        m_eventDataToSerialize.resize(5U);
        m_eventDataToSerialize[0U] = convertIpAddressToArray(event->sourceIpAddress);
        securityEventAlert.protoContextData.swVerificationFailure.sourceIpAddress = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->serviceName), sizeof(event->serviceName)};
        securityEventAlert.protoContextData.swVerificationFailure.processNameExecutingUpdate = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        securityEventAlert.protoContextData.swVerificationFailure.processId = event->processId;
        m_eventDataToSerialize[2U] = {reinterpret_cast<uint8_t const*>(event->serviceName), sizeof(event->serviceName)};
        securityEventAlert.protoContextData.swVerificationFailure.serviceName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[2U]);
        securityEventAlert.protoContextData.swVerificationFailure.packageManifestHash = event->packageManifestHash;
        securityEventAlert.protoContextData.swVerificationFailure.packageManifestFileSize = event->packageManifestFileSize;
        m_eventDataToSerialize[3U] = {reinterpret_cast<uint8_t const*>(event->packageManifestSignatureAlgo), sizeof(event->packageManifestSignatureAlgo)};
        securityEventAlert.protoContextData.swVerificationFailure.packageManifestSignatureAlgo = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[3U]);
        securityEventAlert.protoContextData.swVerificationFailure.failureCode = event->failureCode;
        m_eventDataToSerialize[4U] = {reinterpret_cast<uint8_t const*>(event->failureReason), sizeof(event->failureReason)};
        securityEventAlert.protoContextData.swVerificationFailure.failureReason = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[4U]);
    }
    break;
    case EventIds::DIAG_SEV_INCORRECT_MESSAGE_LENGTH_OR_FORMAT:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_INCORRECT_MESSAGE_LENGTH_OR_FORMAT>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevIncorrectMessageLengthOrFormat_tag);
        securityEventAlert.protoContextData.diagSevIncorrectMessageLengthOrFormat.uid = event->uid;
        securityEventAlert.protoContextData.diagSevIncorrectMessageLengthOrFormat.successBit = event->successBit;
        securityEventAlert.protoContextData.diagSevIncorrectMessageLengthOrFormat.nrc = event->nrc;
        securityEventAlert.protoContextData.diagSevIncorrectMessageLengthOrFormat.diagnosticService = event->diagnosticService;
        securityEventAlert.protoContextData.diagSevIncorrectMessageLengthOrFormat.nrcType = event->nrcType;
        securityEventAlert.protoContextData.diagSevIncorrectMessageLengthOrFormat.length = event->length_1;
        securityEventAlert.protoContextData.diagSevIncorrectMessageLengthOrFormat.format = event->format;
    }
    break;
    case EventIds::DIAG_SEV_COMMUNICATION_CONTROL_SWITCHED_OFF:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_COMMUNICATION_CONTROL_SWITCHED_OFF>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevCommunicationControlSwitchedOff_tag);
        securityEventAlert.protoContextData.diagSevCommunicationControlSwitchedOff.uid = event->uid;
        securityEventAlert.protoContextData.diagSevCommunicationControlSwitchedOff.successBit = event->successBit;
        securityEventAlert.protoContextData.diagSevCommunicationControlSwitchedOff.statusRxTx = event->statusRxTx;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->messagesId), sizeof(event->messagesId)};
        securityEventAlert.protoContextData.diagSevCommunicationControlSwitchedOff.messagesId = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::DIAG_SEV_WRITE_INVALID_DATA:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_WRITE_INVALID_DATA>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevWriteInvalidData_tag);
        securityEventAlert.protoContextData.diagSevWriteInvalidData.uid = event->uid;
        securityEventAlert.protoContextData.diagSevWriteInvalidData.successBit = event->successBit;
        securityEventAlert.protoContextData.diagSevWriteInvalidData.nrc = event->nrc;
        securityEventAlert.protoContextData.diagSevWriteInvalidData.rdid = event->rdid;
        securityEventAlert.protoContextData.diagSevWriteInvalidData.dataLength = event->dataLength;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {event->dataTriedToBeWritten, sizeof(event->dataTriedToBeWritten)};
        securityEventAlert.protoContextData.diagSevWriteInvalidData.dataTriedToBeWritten = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::EXTERNAL_CONNECTION_INTERFACE_SUCCESSFUL:
    {
        auto const* event = sd.decodeContextData<SECEV_EXTERNAL_CONNECTION_INTERFACE_SUCCESSFUL>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_externalConnectionInterfaceSuccessful_tag);
        securityEventAlert.protoContextData.externalConnectionInterfaceSuccessful.uid = event->uid;
        securityEventAlert.protoContextData.externalConnectionInterfaceSuccessful.successBit = event->successBit;
        securityEventAlert.protoContextData.externalConnectionInterfaceSuccessful.connectionType = event->connectionType;
        securityEventAlert.protoContextData.externalConnectionInterfaceSuccessful.connectingUnitAddress = event->connectingUnitAddress;
        securityEventAlert.protoContextData.externalConnectionInterfaceSuccessful.suppliedIpv4AddressForNewConnection = event->suppliedIpv4AddressForNewConnection;
        m_eventDataToSerialize.resize(3U);
        m_eventDataToSerialize[0U] = convertIpAddressToArray(event->suppliedIpv6AddressForNewConnection);
        securityEventAlert.protoContextData.externalConnectionInterfaceSuccessful.suppliedIpv6AddressForNewConnection = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        securityEventAlert.protoContextData.externalConnectionInterfaceSuccessful.connectingUnitDeviceNameLength = event->connectingUnitDeviceNameLength;
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->connectingUnitDeviceName), sizeof(event->connectingUnitDeviceName)};
        securityEventAlert.protoContextData.externalConnectionInterfaceSuccessful.connectingUnitDeviceName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        securityEventAlert.protoContextData.externalConnectionInterfaceSuccessful.transmittedDataType = event->transmittedDataType;
        securityEventAlert.protoContextData.externalConnectionInterfaceSuccessful.streamFileNameLength = event->streamFileNameLength;
        m_eventDataToSerialize[2U] = {reinterpret_cast<uint8_t const*>(event->apnConfigurationFile), sizeof(event->apnConfigurationFile)};
        securityEventAlert.protoContextData.externalConnectionInterfaceSuccessful.apnConfigurationFile = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[2U]);
    }
    break;
    case EventIds::VKMS_KEY_CHANGE:
    {
        auto const* event = sd.decodeContextData<SECEV_VKMS_KEY_CHANGE>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_vkmsKeyChange_tag);
        securityEventAlert.protoContextData.vkmsKeyChange.uid = event->uid;
        securityEventAlert.protoContextData.vkmsKeyChange.successBit = event->successBit;
        securityEventAlert.protoContextData.vkmsKeyChange.keyId = event->keyId;
        m_eventDataToSerialize.resize(5U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->processTaskName), sizeof(event->processTaskName)};
        securityEventAlert.protoContextData.vkmsKeyChange.processTaskName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        securityEventAlert.protoContextData.vkmsKeyChange.processTaskId = event->processTaskId;
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(&event->creationDateOfNewKey.autosar), sizeof(event->creationDateOfNewKey)};
        securityEventAlert.protoContextData.vkmsKeyChange.creationDateOfNewKey = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        m_eventDataToSerialize[2U] = {reinterpret_cast<uint8_t const*>(&event->expirationDateOfNewKey.autosar), sizeof(event->expirationDateOfNewKey)};
        securityEventAlert.protoContextData.vkmsKeyChange.expirationDateOfNewKey = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[2U]);
        m_eventDataToSerialize[3U] = {reinterpret_cast<uint8_t const*>(&event->originIpAddress.ipv6), sizeof(event->originIpAddress)};
        securityEventAlert.protoContextData.vkmsKeyChange.originIpAddress = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[3U]);
        m_eventDataToSerialize[4U] = {reinterpret_cast<uint8_t const*>(event->originalServiceName), sizeof(event->originalServiceName)};
        securityEventAlert.protoContextData.vkmsKeyChange.originalServiceName = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[4U]);
    }
    break;
    case EventIds::ERROR_EVENT_LOGGING_MONITORING:
    {
        auto const* event = sd.decodeContextData<SECEV_ERROR_EVENT_LOGGING_MONITORING>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_errorEventLoggingMonitoring_tag);
        securityEventAlert.protoContextData.errorEventLoggingMonitoring.uid = event->uid;
        securityEventAlert.protoContextData.errorEventLoggingMonitoring.successBit = event->successBit;
        securityEventAlert.protoContextData.errorEventLoggingMonitoring.dtcDfcc = event->dtcDfcc;
        securityEventAlert.protoContextData.errorEventLoggingMonitoring.dtcTi = event->dtcTi;
        securityEventAlert.protoContextData.errorEventLoggingMonitoring.vmIdentifier = event->vmIdentifier;
        securityEventAlert.protoContextData.errorEventLoggingMonitoring.errorId = event->errorId;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->errorLogging), sizeof(event->errorLogging)};
        securityEventAlert.protoContextData.errorEventLoggingMonitoring.errorLogging = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::VM_CRITICAL_ERROR:
    {
        auto const* event = sd.decodeContextData<SECEV_VM_CRITICAL_ERROR>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_vmCriticalError_tag);
        securityEventAlert.protoContextData.vmCriticalError.uid = event->uid;
        securityEventAlert.protoContextData.vmCriticalError.successBit = event->successBit;
        securityEventAlert.protoContextData.vmCriticalError.dtcDfcc = event->dtcDfcc;
        securityEventAlert.protoContextData.vmCriticalError.dtcTi = event->dtcTi;
        securityEventAlert.protoContextData.vmCriticalError.vmIdentifier = event->vmIdentifier;
        securityEventAlert.protoContextData.vmCriticalError.typeOfError = event->typeOfError;
        securityEventAlert.protoContextData.vmCriticalError.additionalInformationLength = event->additionalInformationLength;
    }
    break;
    case EventIds::DIAG_SEV_SECURITY_ACCESS_REQUIRED_TIME_DELAY_NOT_EXPIRED:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_SECURITY_ACCESS_REQUIRED_TIME_DELAY_NOT_EXPIRED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevSecurityAccessRequiredTimeDelayNotExpired_tag);
        securityEventAlert.protoContextData.diagSevSecurityAccessRequiredTimeDelayNotExpired.uid = event->uid;
        securityEventAlert.protoContextData.diagSevSecurityAccessRequiredTimeDelayNotExpired.successBit = event->successBit;
        securityEventAlert.protoContextData.diagSevSecurityAccessRequiredTimeDelayNotExpired.nrc = event->nrc;
        securityEventAlert.protoContextData.diagSevSecurityAccessRequiredTimeDelayNotExpired.delayTime = event->delayTime;
    }
    break;
    case EventIds::DIAG_SEV_REQUEST_SEQUENCE_ERROR:
    {
        auto const* event = sd.decodeContextData<SECEV_DIAG_SEV_REQUEST_SEQUENCE_ERROR>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_diagSevRequestSequenceError_tag);
        securityEventAlert.protoContextData.diagSevRequestSequenceError.uid = event->uid;
        securityEventAlert.protoContextData.diagSevRequestSequenceError.successBit = event->successBit;
        securityEventAlert.protoContextData.diagSevRequestSequenceError.nrc = event->nrc;
        securityEventAlert.protoContextData.diagSevRequestSequenceError.diagnosticService = event->diagnosticService;
        securityEventAlert.protoContextData.diagSevRequestSequenceError.diagnosticSubfunction = event->diagnosticSubfunction;
    }
    break;
    case EventIds::VKMS_DLC_VERIFICATION_FAILED:
    {
        auto const* event = sd.decodeContextData<SECEV_VKMS_DLC_VERIFICATION_FAILED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_vkmsDlcVerificationFailed_tag);
        securityEventAlert.protoContextData.vkmsDlcVerificationFailed.uid = event->uid;
        securityEventAlert.protoContextData.vkmsDlcVerificationFailed.successBit = event->successBit;
        securityEventAlert.protoContextData.vkmsDlcVerificationFailed.dtcDfcc = event->dtcDfcc;
        securityEventAlert.protoContextData.vkmsDlcVerificationFailed.dtcTi = event->dtcTi;
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->publicKeyId), sizeof(event->publicKeyId)};
        securityEventAlert.protoContextData.vkmsDlcVerificationFailed.publicKeyId = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->expectedHash), sizeof(event->expectedHash)};
        securityEventAlert.protoContextData.vkmsDlcVerificationFailed.expectedHash = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        securityEventAlert.protoContextData.vkmsDlcVerificationFailed.contentError = event->contentError;
    }
    break;
    case EventIds::MAC_AUDIT_REPORTS:
    {
        auto const* event = sd.decodeContextData<SECEV_MAC_AUDIT_REPORTS>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_macAuditReports_tag);
        securityEventAlert.protoContextData.macAuditReports.uid = event->uid;
        securityEventAlert.protoContextData.macAuditReports.successBit = event->successBit;
        securityEventAlert.protoContextData.macAuditReports.vmIdentifier = event->vmIdentifier;
        securityEventAlert.protoContextData.macAuditReports.lengthOfAuditRecordFile = event->lengthOfAuditRecordFile;
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->smackAuditRecords), sizeof(event->smackAuditRecords)};
        securityEventAlert.protoContextData.macAuditReports.smackAuditRecords = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->newSmackConfiguration), sizeof(event->newSmackConfiguration)};
        securityEventAlert.protoContextData.macAuditReports.newSmackConfiguration = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
    }
    break;
    case EventIds::FAILED_SERVICE_REQUEST_DETECTED:
    {
        auto const* event = sd.decodeContextData<SECEV_FAILED_SERVICE_REQUEST_DETECTED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_failedServiceRequestDetected_tag);
        securityEventAlert.protoContextData.failedServiceRequestDetected.uid = event->uid;
        securityEventAlert.protoContextData.failedServiceRequestDetected.successBit = event->successBit;
        securityEventAlert.protoContextData.failedServiceRequestDetected.serviceRegistryId = event->serviceRegistryId;
        m_eventDataToSerialize.resize(4U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->registeredService), sizeof(event->registeredService)};
        securityEventAlert.protoContextData.failedServiceRequestDetected.registeredService = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->queryingApplicationId), sizeof(event->queryingApplicationId)};
        securityEventAlert.protoContextData.failedServiceRequestDetected.queryingApplicationId = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
        m_eventDataToSerialize[2U] = convertIpAddressToArray(event->queryingServerIpAddress);
        securityEventAlert.protoContextData.failedServiceRequestDetected.queryingServerIpAddress = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[2U]);
        m_eventDataToSerialize[3U] = {event->errorInformationOnFailure, sizeof(event->errorInformationOnFailure)};
        securityEventAlert.protoContextData.failedServiceRequestDetected.errorInformationOnFailure = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[3U]);
    }
    break;
    case EventIds::VKMS_VIN_VALIDATION_FAILED:
    {
        auto const* event = sd.decodeContextData<SECEV_VKMS_VIN_VALIDATION_FAILED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_vkmsVinValidationFailed_tag);
        securityEventAlert.protoContextData.vkmsVinValidationFailed.uid = event->uid;
        securityEventAlert.protoContextData.vkmsVinValidationFailed.successBit = event->successBit;
        securityEventAlert.protoContextData.vkmsVinValidationFailed.dtcDfcc = event->dtcDfcc;
        securityEventAlert.protoContextData.vkmsVinValidationFailed.dtcTi = event->dtcTi;
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->currentVin), sizeof(event->currentVin)};
        securityEventAlert.protoContextData.vkmsVinValidationFailed.currentVin = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->receivedVin), sizeof(event->receivedVin)};
        securityEventAlert.protoContextData.vkmsVinValidationFailed.receivedVin = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
    }
    break;
    case EventIds::ECU_MODE_CHANGE:
    {
        auto const* event = sd.decodeContextData<SECEV_ECU_MODE_CHANGE>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_ecuModeChange_tag);
        securityEventAlert.protoContextData.ecuModeChange.uid = event->uid;
        securityEventAlert.protoContextData.ecuModeChange.successBit = event->successBit;
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->oldEcuMode), sizeof(event->oldEcuMode)};
        securityEventAlert.protoContextData.ecuModeChange.oldEcuMode = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->newEcuMode), sizeof(event->newEcuMode)};
        securityEventAlert.protoContextData.ecuModeChange.newEcuMode = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
    }
    break;
    case EventIds::CHAR_COM_MESSAGE_OUT_OF_SEQUENCE:
    {
        auto const* event = sd.decodeContextData<SECEV_CHAR_COM_MESSAGE_OUT_OF_SEQUENCE>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_charComMessageOutOfSequence_tag);
        securityEventAlert.protoContextData.charComMessageOutOfSequence.expectedMsgSeqNumber  = event->expectedMsgSeqNumber ;
        securityEventAlert.protoContextData.charComMessageOutOfSequence.receivedMsgSeqNumber  = event->receivedMsgSeqNumber ;
    }
    break;
    case EventIds::CHAR_CONTRACT_CERTIFICATE_INSTALLATION_FAILED:
    {
        auto const* event = sd.decodeContextData<SECEV_CHAR_CONTRACT_CERTIFICATE_INSTALLATION_FAILED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_charContractCertificateInstallationFailed_tag);
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->leafCertificateCn), sizeof(event->leafCertificateCn)};
        securityEventAlert.protoContextData.charContractCertificateInstallationFailed.leafCertificateCn  = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->errorReason), sizeof(event->errorReason)};
        securityEventAlert.protoContextData.charContractCertificateInstallationFailed.errorReason  = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
    }
    break;
    case EventIds::CHAR_EXI_MESSAGE_INVALID:
    {
        auto const* event = sd.decodeContextData<SECEV_CHAR_EXI_MESSAGE_INVALID>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_charExiMessageInvalid_tag);
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {event->exiMessagePayload, sizeof(event->exiMessagePayload)};
        securityEventAlert.protoContextData.charExiMessageInvalid.exiMessagePayload  = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->reaon), sizeof(event->reaon)};
        securityEventAlert.protoContextData.charExiMessageInvalid.reaon = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
    }
    break;
    case EventIds::CHAR_EXI_SIGNATURE_INVALID:
    {
        auto const* event = sd.decodeContextData<SECEV_CHAR_EXI_SIGNATURE_INVALID>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_charExiSignatureInvalid_tag);
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->signaturePayload), sizeof(event->signaturePayload)};
        securityEventAlert.protoContextData.charExiSignatureInvalid.signaturePayload  = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::CHAR_EXI_SIGNATURE_MISSING:
    {
        auto const* event = sd.decodeContextData<SECEV_CHAR_EXI_SIGNATURE_MISSING>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_charExiSignatureMissing_tag);
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->messagePayload), sizeof(event->messagePayload)};
        securityEventAlert.protoContextData.charExiSignatureMissing.messagePayload  = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::CHAR_SECC_DISCOVERY_PROTOCOL_INVALID:
    {
        auto const* event = sd.decodeContextData<SECEV_CHAR_SECC_DISCOVERY_PROTOCOL_INVALID>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_charSeccDiscoveryProtocolInvalid_tag);
        m_eventDataToSerialize.resize(2U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->requestPayload), sizeof(event->requestPayload)};
        securityEventAlert.protoContextData.charSeccDiscoveryProtocolInvalid.requestPayload  = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
        m_eventDataToSerialize[1U] = {reinterpret_cast<uint8_t const*>(event->responsePayload), sizeof(event->responsePayload)};
        securityEventAlert.protoContextData.charSeccDiscoveryProtocolInvalid.responsePayload  = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[1U]);
    }
    break;
    case EventIds::CHAR_SERVER_TLS_CERTIFICATE_INVALID:
    {
        auto const* event = sd.decodeContextData<SECEV_CHAR_SERVER_TLS_CERTIFICATE_INVALID>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_charServerTlsCertificateInvalid_tag);
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->certificateCn), sizeof(event->certificateCn)};
        securityEventAlert.protoContextData.charServerTlsCertificateInvalid.certificateCn  = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::CAN_TIMING_ANOMALY_DETECTED: {
        auto const* event = sd.decodeContextData<SECEV_CAN_TIMING_ANOMALY_DETECTED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_canTimingAnomalyDetected_tag);
        securityEventAlert.protoContextData.canTimingAnomalyDetected.uid = event->uid;
        securityEventAlert.protoContextData.canTimingAnomalyDetected.successBit = event->successBit;
        securityEventAlert.protoContextData.canTimingAnomalyDetected.busId = event->busId;
        securityEventAlert.protoContextData.canTimingAnomalyDetected.canId = event->canId;
        securityEventAlert.protoContextData.canTimingAnomalyDetected.ruleACounter = event->ruleACounter;
        securityEventAlert.protoContextData.canTimingAnomalyDetected.ruleBCounter = event->ruleBCounter;
        securityEventAlert.protoContextData.canTimingAnomalyDetected.ruleCCounter = event->ruleCCounter;
        securityEventAlert.protoContextData.canTimingAnomalyDetected.ruleECounter = event->ruleECounter;
        securityEventAlert.protoContextData.canTimingAnomalyDetected.ruleFCounter = event->ruleFCounter;
        securityEventAlert.protoContextData.canTimingAnomalyDetected.ruleGCounter = event->ruleGCounter;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U] = {reinterpret_cast<uint8_t const*>(event->canMatrixId), sizeof(event->canMatrixId)};
        securityEventAlert.protoContextData.canTimingAnomalyDetected.canMatrixId  = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::UNKNOWN_MESSAGE_DETECTED: {
        auto const* event = sd.decodeContextData<SECEV_UNKNOWN_MESSAGE_DETECTED>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData = static_cast<pb_size_t>(
            com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_unknownMessageDetected_tag);
        securityEventAlert.protoContextData.unknownMessageDetected.uid        = event->uid;
        securityEventAlert.protoContextData.unknownMessageDetected.successBit = event->successBit;
        securityEventAlert.protoContextData.unknownMessageDetected.busId      = event->busId;
        securityEventAlert.protoContextData.unknownMessageDetected.lengthOfMessagePayload
            = event->lengthOfMessagePayload;
        // 0-4 bits:  1 = whitelist, 2 = blacklist, 5-8 bits: 0 = CAN-ID standard, 1 = CAN-ID extended, 2 = CAN-FD-ID
        uint8_t const canIdType{static_cast<uint8_t>(event->canIdType_filterType | event->canIdType_canIdType << 4)};
        securityEventAlert.protoContextData.unknownMessageDetected.canIdType = canIdType;
        // bit 0: CAN REMOTE flag, bit 1: CAN ERROR flag, bit 2: CAN EXTENDED flag, bit 3: CAN
        // FD flag, bit 4: CAN BRS flag, bit 5: CAN ESI flag
        uint8_t const canFlags{static_cast<uint8_t>(event->canFlags_remote | event->canFlags_error << 1
                                                    | event->canFlags_extended << 2 | event->canFlags_fd << 3
                                                    | event->canFlags_brs << 4 | event->canFlags_esi << 5)};
        securityEventAlert.protoContextData.unknownMessageDetected.canFlags = canFlags;
        m_eventDataToSerialize.resize(1U);
        m_eventDataToSerialize[0U]
            = {reinterpret_cast<uint8_t const*>(event->canMessageFullPayload), sizeof(event->canMessageFullPayload)};
        securityEventAlert.protoContextData.unknownMessageDetected.canMessageFullPayload
            = common::nanopb::CreateEncodingCallback(m_eventDataToSerialize[0U]);
    }
    break;
    case EventIds::CANIF_SEV_ERRORSTATE_PASSIVE: {
        auto const* event = sd.decodeContextData<SECEV_CANIF_SEV_ERRORSTATE_PASSIVE>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData
            = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_canifSevErrorstatePassive_tag);
        securityEventAlert.protoContextData.canifSevErrorstatePassive.uid = event->uid;
        securityEventAlert.protoContextData.canifSevErrorstatePassive.successBit = event->successBit;
    }
    break;
    case EventIds::CANIF_SEV_ERRORSTATE_BUSOFF: {
        auto const* event = sd.decodeContextData<SECEV_CANIF_SEV_ERRORSTATE_BUSOFF>();
        CHECK_EVENT(event, eventId);
        securityEventAlert.which_protoContextData
            = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_canifSevErrorstateBusoff_tag);
        securityEventAlert.protoContextData.canifSevErrorstateBusoff.uid = event->uid;
        securityEventAlert.protoContextData.canifSevErrorstateBusoff.successBit = event->successBit;
    }
    break;
    default:;
    }
    return true;
}
