/**
 * @file
 * @brief     A rule engine for the Security Events
 */
#include "SacidEventsEngine.hpp"
#include <DBNames.hpp>
#include "SecurityEventsEngine.hpp"
#include "common/counter_manager/CounterNames.hpp"
// used from SecurityEventsEngine
#include "brain/config/AlertEventsNames.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"

using brain::engines::ReturnCode;
using brain::engines::security_events::EventIds;
using brain::engines::security_events::SacidEventsEngine;
using brain::engines::security_events::SecurityEventsEngine;
using namespace brain::sender_events;
namespace brain
{
namespace engines
{
namespace security_events
{
using CriticalSecurityEventsAlertsCountersTable = std::unordered_map<EventIds, uint32_t>;
using EventCounterLevelType                     = common::counters::EventCounter::EventCounterLevelType;
using Message                                   = brain::messageRepository::MessageRepositoryInterface::Message;
}
}  // namespace engines
}  // namespace brain

SacidEventsEngine::SacidEventsEngine(CounterManagerPtr                                 debugCounters,
                                     MessageRepositoryPtr                              msgRepository,
                                     SecurityEventsEnginePtr                           securityEventsEngine,
                                     EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                                     EventNoiseFilterPtr                               eventNoiseFilter,
                                     events::EventPriority                             priority)
  : EngineEventSender(priority, msgRepository, reportSerializer, eventNoiseFilter)
  , m_debugCounters(debugCounters)
  , m_securityEventsEngine(securityEventsEngine)
{
    if (m_debugCounters)
    {
        m_failedCounter
            = m_debugCounters->CreateCounter(common::counters::warning::SACID_ENGINE_FAILED_PROCESS_COUNTER_NAME,
                                             EventCounterLevelType::COUNTER_WARNING);
        m_invalidCtxDataLenCounter = m_debugCounters->CreateCounter(
            common::counters::errors::SACID_SD_INVALID_CONTEXT_DATA_LENGTH, EventCounterLevelType::COUNTER_ERROR);
    }
}

using brain::engines::security_events::SecurityEventIdsManager;
ReturnCode
SacidEventsEngine::processInternal(UPSensorData sd)
{
    try
    {
        LOG_VERBOSE << "Processing SacidEventsEngine - began processing SecurityEventSensorData" << LOG_NOOP;

        auto& sacidSD      = dynamic_cast<SecurityEventSensorData&>(*sd);
        auto& secEvIdsMgr  = SecurityEventIdsManager::GetInstance();
        auto  sacidEventId = sacidSD.GetEventId();
        if (secEvIdsMgr.IsInSecurityEventsIdsWhiteList(sacidEventId))
        {
            m_securityEventsEngine->UpdateSecurityEventsCountersTable(sacidSD.GetEventFrame());
            handleSacidSecurityEvents(sacidSD);
        }
        else
        {
            // If the event is in the blacklist then just disregard it.
            if (secEvIdsMgr.IsInSecurityEventsIdsBlackList(sacidEventId))
            {
                LOG_DEBUG << "SE " << static_cast<int>(sacidEventId) << " is blacklisted, will not be processed"
                          << LOG_NOOP;
                return ReturnCode::Success;
            }
            m_securityEventsEngine->HandleUnknownEventIdAlert(sacidSD);
        }
    }
    catch (std::bad_cast const& /*e*/)
    {
        LOG_ERROR << "Processing SacidEventsEngine - sd cannot be casted to SecurityEventSensorData" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCounter);
        return ReturnCode::CastError;
    }

    return ReturnCode::Success;
}


void
SacidEventsEngine::handleSacidSecurityEvents(SecurityEventSensorData& sacidSD)
{
    auto const eventId = sacidSD.GetEventId();

    switch (eventId)
    {
    case EventIds::CANIF_SEV_RX_ERROR_DETECTED:
        m_securityEventsEngine->HandleRXandTXErrorDetected<SECEV_CANIF_SEV_RX_ERROR_DETECTED>(sacidSD);
        break;
    case EventIds::CANIF_SEV_TX_ERROR_DETECTED:
        m_securityEventsEngine->HandleRXandTXErrorDetected<SECEV_CANIF_SEV_TX_ERROR_DETECTED>(sacidSD);
        break;
    case EventIds::CANIF_SEV_ERRORSTATE_PASSIVE:
        [[fallthrough]];  // done accordingly to the requirements, for 2 SE we need to do same thing
    case EventIds::CANIF_SEV_ERRORSTATE_BUSOFF:
        m_securityEventsEngine->HandleCanIfErrorStatus(sacidSD);
        break;
    case EventIds::SECOC_SEV_MAC_VERIFICATION_FAILED:
    case EventIds::SOAD_SEV_DROP_PDU_RX_TCP:
    case EventIds::SOAD_SEV_DROP_PDU_RX_UDP:
    case EventIds::SOAD_SEV_DROP_MSG_RX_UDP_LENGTH:
    case EventIds::SOAD_SEV_DROP_MSG_RX_UDP_SOCKET:
    case EventIds::SOAD_SEV_REJECTED_TCP_CONNECTION:
    case EventIds::ETHIF_SEV_DROP_UNKNOWN_ETHERTYPE:
    case EventIds::ETHIF_SEV_DROP_VLAN_DOUBLE_TAG:
    case EventIds::ETHIF_SEV_DROP_INV_VLAN:
    case EventIds::ETHIF_SEV_DROP_ETH_MAC_COLLISIONN:
    case EventIds::SECURE_BOOT_FAILED:
    case EventIds::SW_VERSION_UPDATE_MECHANISM_CHANGES:
    case EventIds::ECU_MODE_CHANGE:
    case EventIds::VKMS_NO_KEYS_AVAILABLE:
    case EventIds::VKMS_DLC_VERIFICATION_FAILED:
    case EventIds::VKMS_UNKNOWN_KEY_REQUESTED:
    case EventIds::VKMS_VIN_VALIDATION_FAILED:
    case EventIds::CHAR_SECC_DISCOVERY_PROTOCOL_INVALID:
    case EventIds::CHAR_EXI_MESSAGE_INVALID:
    case EventIds::CHAR_EXI_SIGNATURE_INVALID:
    case EventIds::CHAR_EXI_SIGNATURE_MISSING:
    case EventIds::CHAR_SERVER_TLS_CERTIFICATE_INVALID:
    case EventIds::CHAR_CONTRACT_CERTIFICATE_INSTALLATION_FAILED:
    case EventIds::CHAR_COM_MESSAGE_OUT_OF_SEQUENCE:
    case EventIds::FLOW_INTEGRITY_FAILURE:
        forwardSacidEvent(sacidSD, true);
        break;
    case EventIds::SECOC_SEV_FRESHNESS_NOT_AVAILABLE: {
        auto event = sacidSD.decodeContextData<SECEV_SECOC_SEV_FRESHNESS_NOT_AVAILABLE>();
        if (nullptr == event)
        {
            LOG_ERROR << "Cannot decode context data for SECOC_SEV_FRESHNESS_NOT_AVAILABLE" << LOG_NOOP;
            common::counters::IncreaseCounter(m_invalidCtxDataLenCounter);
            common::counters::IncreaseCounter(m_failedCounter);
            m_securityEventsEngine->HandleDroppedSecurityEvent(sacidSD, DropReason::SacidEventsEngine);
            return;
        }

        m_securityEventsEngine->HandleFreshnessValueFailedEvent(sacidSD, event);
    }
    break;
    case EventIds::DIAG_SEV_WRITE_INVALID_DATA:
    case EventIds::DIAG_SEV_SECURITY_ACCESS_DENIED:
    case EventIds::DIAG_SEV_COMMUNICATION_CONTROL_SWITCHED_OFF:
    case EventIds::DIAG_SEV_SERVICE_NOT_SUPPORTED:
    case EventIds::DIAG_SEV_SUBFUNCTION_NOT_SUPPORTED:
    case EventIds::DIAG_SEV_INCORRECT_MESSAGE_LENGTH_OR_FORMAT:
    case EventIds::DIAG_SEV_REQUEST_SEQUENCE_ERROR:
    case EventIds::DIAG_SEV_REQUEST_OUT_OF_RANGE:
    case EventIds::DIAG_SEV_REQUESTED_ACTIONS_REQUIRES_AUTHENTICATION:
    case EventIds::DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED:
    case EventIds::DIAG_SEV_SECURITY_ACCESS_INVALID_KEY:
    case EventIds::DIAG_SEV_SECURITY_ACCESS_REQUIRED_TIME_DELAY_NOT_EXPIRED:
    case EventIds::DIAG_SEV_NUMBER_OF_FAILED_AUTHENTICATION_ATTEMPTS_EXCEEDED:
    case EventIds::DIAG_SEV_CERTIFICATE_FAILURE:
        m_securityEventsEngine->HandleDiagnosticEventSequence(sacidSD);
        forwardSacidEvent(sacidSD, true);
        break;
    case EventIds::DIAG_SEV_ECU_UNLOCK_SUCCESSFUL:
    case EventIds::DIAG_SEV_AUTHENTICATION_SUCCESSFUL:
    case EventIds::DIAG_SEV_CLEAR_DTC_SUCCESSFUL:
    case EventIds::DIAG_SEV_ECU_RESET:
    case EventIds::DIAG_SEV_WRITE_DATA:
    case EventIds::DIAG_SEV_REQUEST_DOWNLOAD:
    case EventIds::DIAG_SEV_DTC_SETTING_SWITCHED_OFF:
        m_securityEventsEngine->HandleDiagnosticEventSequence(sacidSD);
        break;
    default:
        LOG_WARNING << "handleSacidSecurityEvents received wrong eventID" << LOG_NOOP;
        m_securityEventsEngine->HandleUnknownEventIdAlert(sacidSD);
        break;
    }
}

bool
SacidEventsEngine::createEventAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                                    SecurityEventSensorData&                                 sd)
{
    com_vwg_connect_ids_idsperiodicreport_v1_CanControllerErrorStateAlert canControllerErrorStateAlert
        = com_vwg_connect_ids_idsperiodicreport_v1_CanControllerErrorStateAlert_init_default;

    canControllerErrorStateAlert.idsMInstanceID   = sd.GetIdsMId();
    canControllerErrorStateAlert.sensorInstanceID = sd.GetSensorId();
    canControllerErrorStateAlert.state            = (sd.GetEventId() == EventIds::CANIF_SEV_ERRORSTATE_PASSIVE) ? 0 : 1;

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    ruleEval.which_RuleData   = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_canControllerErroStateAlert_tag);
    ruleEval.RuleData.canControllerErroStateAlert = canControllerErrorStateAlert;

    return true;
}

void
SacidEventsEngine::forwardSacidEvent(SecurityEventSensorData& securityEventSD, bool isCriticalEvent)
{
    auto const& eventName
        = isCriticalEvent ? CriticalEventAlert::CriticalEventName : CriticalEventAlert::SacidEventsEngine;
    
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;

    bool canSendAlert{true};
    if (!isCriticalEvent)
    {
        std::ignore = createEventAlert(ruleEval, securityEventSD);
    }
    else
    {
        m_securityEventsEngine->UpdateCriticalSecurityEventsAlertsCountersTable(securityEventSD.GetEventId());

        com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData securityEventAlert
            = com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData_init_default;
        canSendAlert = SecurityEventsEngine::CreateSecurityEventData(securityEventAlert, securityEventSD);

        ruleEval.ruleEvaluationId = m_currentTime;
        ruleEval.timestamp        = m_currentTime;
        
        ruleEval.which_RuleData = static_cast<pb_size_t>(
            com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_criticalSecurityEventAlert_tag);
        ruleEval.RuleData.criticalSecurityEventAlert = securityEventAlert;
    }

    if (canSendAlert)
    {
        auto const status
            = SendEvent(ruleEval, SensorDataTag::SD_SACID_CAN_EVENT, eventName, securityEventSD.GetEventFrame());

        if (EngineEventSender::SendStatus::Success != status)
        {
            common::counters::IncreaseCounter(m_failedCounter);

            m_securityEventsEngine->HandleDroppedSecurityEvent(securityEventSD, DropReason::SacidEventsEngine);
        }
    }
    else
    {
        LOG_ERROR << "Cannot send alert" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCounter);
        m_securityEventsEngine->HandleDroppedSecurityEvent(securityEventSD, DropReason::SacidEventsEngine);
    }
}
