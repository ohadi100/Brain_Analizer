/**
 * @file
 * @brief     A rule engine for the TLS Error Sensor.
 */
#include "TLSErrorReportEngine.hpp"
#include "autogen/nanopb/NanoPbInclude.hpp"
#include "brain/config/AlertEventsNames.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/utils/logger/Logger.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"

using brain::engines::swpac::TLSErrorReportEngine;
using brain::engines::ReturnCode;
using brain::sensor_data::TLSErrorReportSensorData;
using common::utils::Logger;
using namespace brain::sender_events;
namespace brain
{
namespace engines
{
namespace swpac
{
using Message = brain::messageRepository::MessageRepositoryInterface::Message;
}
}  // namespace engines
}  // namespace brain

TLSErrorReportEngine::TLSErrorReportEngine(CounterManagerPtr                                 debugCounters,
                                           MessageRepositoryPtr                              msgRepository,
                                           EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                                           EventNoiseFilterPtr                               eventNoiseFilter,
                                           events::EventPriority                             priority)
  : SwpacEngineBase(debugCounters, priority, msgRepository, reportSerializer, eventNoiseFilter)
{
    if (debugCounters)
    {
        m_failedCounter = debugCounters->CreateCounter(common::counters::TLS_ERROR_REPORT_FAILED_PROCESS_COUNTER_NAME,
                                                       EventCounter::EventCounterLevelType::COUNTER_WARNING);
        m_alertSendCounter
            = debugCounters->CreateCounter(common::counters::warning::TLS_ERROR_REPORT_CREATED_EVENT_COUNTER_NAME,
                                           EventCounter::EventCounterLevelType::COUNTER_DEBUG);
    }
}

bool
TLSErrorReportEngine::sendAlert(TLSErrorReportSensorData const& sd)
{
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;

    com_vwg_connect_ids_idsperiodicreport_v1_DhmTerIncident dhmTerIncident
        = com_vwg_connect_ids_idsperiodicreport_v1_DhmTerIncident_init_default;

    dhmTerIncident.componentId       = common::nanopb::CreateEncodingCallback(sd.GetComponentId().value());
    dhmTerIncident.timestamp         = sd.GetTimeStamp().value();
    dhmTerIncident.clientIp          = common::nanopb::CreateEncodingCallback(sd.GetClientIp().value());
    dhmTerIncident.serverIp          = common::nanopb::CreateEncodingCallback(sd.GetServerIp().value());
    dhmTerIncident.clientPort        = sd.GetClientPort().value();
    dhmTerIncident.serverPort        = sd.GetServerPort().value();
    dhmTerIncident.protocol          = sd.GetProtocol().value();
    dhmTerIncident.failureReasonCode = sd.GetFailureReason().value();
    dhmTerIncident.tlsIdentity       = common::nanopb::CreateEncodingCallback(sd.GetTlsIdentity().value());

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    ruleEval.which_RuleData
        = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_dhmTerIncidentAlert_tag);
    ruleEval.RuleData.dhmTerIncidentAlert = dhmTerIncident;

    auto const status
        = SendEvent(ruleEval, SensorDataTag::SD_SWPAC_TLS_ERROR_REPORT, CriticalEventAlert::TLSErrorReport);

    if (EngineEventSender::SendStatus::Success != status)
    {
        common::counters::IncreaseCounter(m_failedCounter);
        return false;
    }

    common::counters::IncreaseCounter(m_alertSendCounter);
    return true;
}

ReturnCode
TLSErrorReportEngine::processInternal(UPSensorData const sd)
{
    try
    {
        LOG_VERBOSE << "TLSErrorReport Engine - Began processing TLSErrorReportSensorData" << LOG_NOOP;
        auto const& tlsSD = dynamic_cast<TLSErrorReportSensorData const&>(*sd);

        cm::optional<uint64_t> const& timeStamp = tlsSD.GetTimeStamp();
        if (!timeStamp.has_value())
        {
            LOG_ERROR << "TLSErrorReport Engine - 'timeStamp' value is missing" << LOG_NOOP;
            common::counters::IncreaseCounter(m_failedCounter);
            return ReturnCode::InvalidError;
        }

        cm::optional<std::string> const& TLSClientIPv6Address = tlsSD.GetClientIp();
        if (!TLSClientIPv6Address.has_value())
        {
            LOG_ERROR << "TLSErrorReport Engine - 'TLSClientIPv6Address' value is missing" << LOG_NOOP;
            common::counters::IncreaseCounter(m_failedCounter);
            return ReturnCode::InvalidError;
        }

        cm::optional<std::string> const& TLSServerIPv6Address = tlsSD.GetServerIp();
        if (!TLSServerIPv6Address.has_value())
        {
            LOG_ERROR << "TLSErrorReport Engine - 'TLSServerIPv6Address' value is missing" << LOG_NOOP;
            common::counters::IncreaseCounter(m_failedCounter);
            return ReturnCode::InvalidError;
        }

        cm::optional<uint16_t> const& transportProtocol = tlsSD.GetProtocol();
        if (!transportProtocol.has_value())
        {
            LOG_ERROR << "TLSErrorReport Engine - 'transportProtocol' value is missing" << LOG_NOOP;
            common::counters::IncreaseCounter(m_failedCounter);
            return ReturnCode::InvalidError;
        }

        cm::optional<uint16_t> const& clientPort = tlsSD.GetClientPort();
        if (!clientPort.has_value())
        {
            LOG_ERROR << "TLSErrorReport Engine - 'clientPort' value is missing" << LOG_NOOP;
            common::counters::IncreaseCounter(m_failedCounter);
            return ReturnCode::InvalidError;
        }

        cm::optional<uint16_t> const& serverPort = tlsSD.GetServerPort();
        if (!serverPort.has_value())
        {
            LOG_ERROR << "TLSErrorReport Engine - 'serverPort' value is missing" << LOG_NOOP;
            common::counters::IncreaseCounter(m_failedCounter);
            return ReturnCode::InvalidError;
        }

        cm::optional<int32_t> const& failureReasonCode = tlsSD.GetFailureReason();
        if (!failureReasonCode.has_value())
        {
            LOG_ERROR << "TLSErrorReport Engine - 'failureReasonCode' value is missing" << LOG_NOOP;
            common::counters::IncreaseCounter(m_failedCounter);
            return ReturnCode::InvalidError;
        }

        cm::optional<std::string> const& componentId = tlsSD.GetComponentId();
        if (!componentId.has_value())
        {
            LOG_ERROR << "TLSErrorReport Engine - 'componentId' value is missing" << LOG_NOOP;
            common::counters::IncreaseCounter(m_failedCounter);
            return ReturnCode::InvalidError;
        }

        cm::optional<std::string> const& tlsIdentity = tlsSD.GetTlsIdentity();
        if (!tlsIdentity.has_value())
        {
            LOG_ERROR << "TLSErrorReport Engine - 'tlsIdentity' value is missing" << LOG_NOOP;
            common::counters::IncreaseCounter(m_failedCounter);
            return ReturnCode::InvalidError;
        }

        // send string size alert only if the SD is valid
        if (tlsSD.IsAlert())
        {
            LOG_DEBUG << "TLSErrorReport Engine - string size alert" << LOG_NOOP;
            sendStringSizeAlert(tlsSD.GetTag(), tlsSD.GetConstraintId(), tlsSD.GetStringSizeAlertData());
        }

        if (m_incidentCounter)
        {
            m_incidentCounter->Increment(brain::sensor_data::swpac::ConstraintId::TLS_ERROR_REPORT);
        }

        return (sendAlert(tlsSD) ? ReturnCode::Success : ReturnCode::FailedError);
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::bad_cast const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "TLSErrorReport Engine - SD cannot be casted to TlsErrorReportingSensorData" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCounter);
        return ReturnCode::CastError;
    }
}
