/**
 * @file
 * @brief     A rule engine for the Host QLAH Sensor
 */
#include "HostEngine.hpp"
#include "autogen/nanopb/NanoPbInclude.hpp"
#include "brain/config/AlertEventsNames.hpp"
#include "brain/engines/security_events/NanoPbMacros.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"
#include "brain/noise_filter/event_noise_filter/GroupNoiseFilter.hpp"
#include "brain/sensor_data/qlah/HostSensorData.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/utils/os/time/Time.hpp"

using brain::engines::ReturnCode;
using brain::engines::qlah::HostEngine;
using brain::sensor_data::HostSensorData;
using common::utils::Logger;
using namespace brain::sender_events;

namespace brain
{
namespace engines
{
namespace qlah
{
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;
using Message = brain::messageRepository::MessageRepositoryInterface::Message;
}
}  // namespace engines
}  // namespace brain

#define SHIFT_AND_SET_PROTO_FIELD(value, field) \
    value = static_cast<uint16_t>(value >> 1U); \
    if (0U == value)                            \
    {                                           \
        return;                                 \
    }                                           \
    buffer.field = (value & 1U)


HostEngine::HostEngine(CounterManagerPtr                                 debugCounters,
                       MessageRepositoryPtr                              msgRepository,
                       EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                       EventNoiseFilterPtr                               eventNoiseFilter,
                       events::EventPriority                             priority)
  : EngineEventSender(priority, msgRepository, reportSerializer, eventNoiseFilter)
{
    if (debugCounters)
    {
        m_failedCounter = debugCounters->CreateCounter(common::counters::warning::HOST_ENGINE_FAILED_PROCESS_COUNTER_NAME, EventCounterLevelType::COUNTER_WARNING);

        m_uartAliveSignalMissingCounter = debugCounters->CreateCounterWithTs(
            common::counters::errors::UART_ALIVE_SIGNAL_MISSING_COUNTER_NAME, EventCounterLevelType::COUNTER_ERROR);
        m_authenticationErrorCounter = debugCounters->CreateCounterWithTs(
            common::counters::errors::AUTHENTICATION_ERROR_COUNTER_NAME, EventCounterLevelType::COUNTER_ERROR);

        m_microProcessorSignatureFailureCounter
            = debugCounters->CreateCounter(common::counters::warning::MICRO_PROCESSOR_SIGNATURE_FAILURE_COUNTER_NAME,
                                           EventCounterLevelType::COUNTER_WARNING);
        m_microControllerSignatureFailureCounter
            = debugCounters->CreateCounter(common::counters::warning::MICRO_CONTROLLER_SIGNATURE_FAILURE_COUNTER_NAME,
                                           EventCounterLevelType::COUNTER_WARNING);
        m_microControllerHardwareFailureCounter
            = debugCounters->CreateCounter(common::counters::warning::MICRO_CONTROLLER_HARDWARE_FAILURE_COUNTER_NAME,
                                           EventCounterLevelType::COUNTER_WARNING);
    }
}

void
HostEngine::parseFailedSgn1(com_vwg_connect_ids_idsperiodicreport_v1_UPFirewallSignatureFailureAlert& buffer,
                            uint16_t failedSgn1) noexcept
{
    LOG_DEBUG << "SD-failedSgn1: " << failedSgn1 << LOG_NOOP;

    buffer.timestamp          = m_timeStamp;
    buffer.vkmsKeyListFailure = ((failedSgn1 & 1U) != 0U);          // bit 0
    SHIFT_AND_SET_PROTO_FIELD(failedSgn1, sfdAccessProtectionError);          // bit 1
    SHIFT_AND_SET_PROTO_FIELD(failedSgn1, ivdIntegrityValidationError);       // bit 2
    SHIFT_AND_SET_PROTO_FIELD(failedSgn1, moseContainerAuthenticityFailure);  // bit 3
    SHIFT_AND_SET_PROTO_FIELD(failedSgn1, sokMessageAuthenticityFailure);     // bit 4
}

void
HostEngine::parseFailedSgn2(com_vwg_connect_ids_idsperiodicreport_v1_UCFirewallSignatureFailureAlert& buffer,
                            uint16_t failedSgn2) noexcept
{
    LOG_DEBUG << "SD-failedSgn2: " << failedSgn2 << LOG_NOOP;

    buffer.timestamp            = m_timeStamp;
    buffer.authenticBootFailure = ((failedSgn2 & 1U) != 0U);         // bit 0
    SHIFT_AND_SET_PROTO_FIELD(failedSgn2, runTimeManipulationFailure);         // bit 1
    SHIFT_AND_SET_PROTO_FIELD(failedSgn2, secureBootSwtFailure);               // bit 2
    SHIFT_AND_SET_PROTO_FIELD(failedSgn2, obdCvnNumberCalculationUcFailure);   // bit 3
    SHIFT_AND_SET_PROTO_FIELD(failedSgn2, obdCvnNumberCalculationSwtFailure);  // bit 4
    SHIFT_AND_SET_PROTO_FIELD(failedSgn2, vkmsKeyListFailure);                 // bit 5
    SHIFT_AND_SET_PROTO_FIELD(failedSgn2, rxSwinListFailure);                  // bit 6
    SHIFT_AND_SET_PROTO_FIELD(failedSgn2, sfdAccessProtectionError);           // bit 7
    SHIFT_AND_SET_PROTO_FIELD(failedSgn2, ivdIntegrityValidationError);        // bit 8
    SHIFT_AND_SET_PROTO_FIELD(failedSgn2, sokMessageAuthenticityFailure);      // bit 9
}

void
HostEngine::parseCpuErrors(com_vwg_connect_ids_idsperiodicreport_v1_UCHWFailureAlert& buffer,
                           uint16_t                                                   cpuErrors) noexcept
{
    LOG_DEBUG << "SD-cpuErrors:" << cpuErrors << LOG_NOOP;

    buffer.timestamp    = m_timeStamp;
    buffer.cpu0Watchdog = ((cpuErrors & 1U) != 0U);   // bit 0
    SHIFT_AND_SET_PROTO_FIELD(cpuErrors, cpu1Watchdog);         // bit 1
    SHIFT_AND_SET_PROTO_FIELD(cpuErrors, cpu2Watchdog);         // bit 2
    SHIFT_AND_SET_PROTO_FIELD(cpuErrors, cpu3Watchdog);         // bit 3
    SHIFT_AND_SET_PROTO_FIELD(cpuErrors, hsmWatchdogAsserted);  // bit 4
    SHIFT_AND_SET_PROTO_FIELD(cpuErrors, phmHwIntegrityError);  // bit 5
    SHIFT_AND_SET_PROTO_FIELD(cpuErrors, mpuWrongAccess);       // bit 6
    SHIFT_AND_SET_PROTO_FIELD(cpuErrors, lbistError);           // bit 7
    SHIFT_AND_SET_PROTO_FIELD(cpuErrors, mbistError);           // bit 8
    SHIFT_AND_SET_PROTO_FIELD(cpuErrors, eccError);             // bit 9
}

void
HostEngine::createHostErrorMonitoringReport(
    com_vwg_connect_ids_idsperiodicreport_v1_HostErrorMonitoringReport& hostErrorMonitoringReport)
{
    hostErrorMonitoringReport.creationTimeStamp = m_currentTime;

    if (0U != m_failedSgn1)
    {
        common::counters::IncreaseCounter(m_microProcessorSignatureFailureCounter);
        com_vwg_connect_ids_idsperiodicreport_v1_UPFirewallSignatureFailureAlert uPFirewallSignatureFailureAlertBuffer
            = com_vwg_connect_ids_idsperiodicreport_v1_UPFirewallSignatureFailureAlert_init_default;
        parseFailedSgn1(uPFirewallSignatureFailureAlertBuffer, m_failedSgn1);
        SET_NPB_OPTIONAL_FIELD(
            hostErrorMonitoringReport, uPFirewallSignatureFailureAlert, uPFirewallSignatureFailureAlertBuffer);
    }
    else
    {
        hostErrorMonitoringReport.has_uPFirewallSignatureFailureAlert = false;
    }

    if (0U != m_failedSgn2)
    {
        common::counters::IncreaseCounter(m_microControllerSignatureFailureCounter);
        com_vwg_connect_ids_idsperiodicreport_v1_UCFirewallSignatureFailureAlert uCFirewallSignatureFailureAlertBuffer
            = com_vwg_connect_ids_idsperiodicreport_v1_UCFirewallSignatureFailureAlert_init_default;
        parseFailedSgn2(uCFirewallSignatureFailureAlertBuffer, m_failedSgn2);
        SET_NPB_OPTIONAL_FIELD(
            hostErrorMonitoringReport, uCFirewallSignatureFailureAlert, uCFirewallSignatureFailureAlertBuffer);
    }
    else
    {
        hostErrorMonitoringReport.has_uCFirewallSignatureFailureAlert = false;
    }

    if (0U != m_cpuErrors)
    {
        common::counters::IncreaseCounter(m_microControllerHardwareFailureCounter);
        com_vwg_connect_ids_idsperiodicreport_v1_UCHWFailureAlert uCHWFailureAlertBuffer
            = com_vwg_connect_ids_idsperiodicreport_v1_UCHWFailureAlert_init_default;
        parseCpuErrors(uCHWFailureAlertBuffer, m_cpuErrors);
        SET_NPB_OPTIONAL_FIELD(hostErrorMonitoringReport, uCHWFailureAlert, uCHWFailureAlertBuffer);
    }
    else
    {
        hostErrorMonitoringReport.has_uCHWFailureAlert = false;
    }
}

bool
HostEngine::createRuleEvaluation(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval)
{
    com_vwg_connect_ids_idsperiodicreport_v1_HostErrorMonitoringReport hostErrorMonitoringReport
        = com_vwg_connect_ids_idsperiodicreport_v1_HostErrorMonitoringReport_init_default;
    createHostErrorMonitoringReport(hostErrorMonitoringReport);

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    ruleEval.which_RuleData
        = static_cast<pb_size_t>(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_hostErrorMonitoringReport_tag);
    ruleEval.RuleData.hostErrorMonitoringReport = hostErrorMonitoringReport;

#ifndef HCP5_PLATFORM
    printEvent(ruleEval);
#endif  //! HCP5_PLATFORM

    return true;
}

ReturnCode
HostEngine::processInternal(UPSensorData sd)
{
    auto returnCode{ReturnCode::FailedError};
    try
    {
        LOG_VERBOSE << "Processing QLAH Host engine - began processing HostSensorData" << LOG_NOOP;
        auto const& hostSD = dynamic_cast<HostSensorData const&>(*sd);
        

        // For periodic statistics report
        m_timeStamp                                             = hostSD.GetTimestamp();
        cm::optional<bool> const& uartAliveSignalMissingCounter = hostSD.GetMissingAliveSig();
        cm::optional<bool> const& authenticationErrorCounter    = hostSD.GetAuthError();
        if (uartAliveSignalMissingCounter.has_value() && (true == *uartAliveSignalMissingCounter))
        {
            if (nullptr != m_uartAliveSignalMissingCounter)
            {
                m_uartAliveSignalMissingCounter->CountEvent(m_timeStamp);
            }
        }
        if (authenticationErrorCounter.has_value() && (true == *authenticationErrorCounter))
        {
            if (nullptr != m_authenticationErrorCounter)
            {
                m_authenticationErrorCounter->CountEvent(m_timeStamp);
            }
        }

        cm::optional<uint16_t> const& failedSgn1     = hostSD.GetFailedSgn1();
        uint16_t const                failedSgn1Bits = (failedSgn1.has_value()) ? (*failedSgn1) : 0;

        cm::optional<uint16_t> const& failedSgn2     = hostSD.GetFailedSgn2();
        uint16_t const                failedSgn2Bits = (failedSgn2.has_value()) ? (*failedSgn2) : 0;

        cm::optional<uint16_t> const& cpuErrors     = hostSD.GetCpuErrors();
        uint16_t const                cpuErrorsBits = (cpuErrors.has_value()) ? (*cpuErrors) : 0;

        if ((0U != failedSgn1Bits) || (0U != failedSgn2Bits) || (0U != cpuErrorsBits))
        {
            m_failedSgn1 = failedSgn1Bits;
            m_failedSgn2 = failedSgn2Bits;
            m_cpuErrors  = cpuErrorsBits;
            com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
                = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
            std::ignore = createRuleEvaluation(ruleEval);

            auto const status = SendEvent(ruleEval, SensorDataTag::SD_QLAH_HOST, CriticalEventAlert::HostErrorMonitoring);
            if (EngineEventSender::SendStatus::Success != status)
            {
                common::counters::IncreaseCounter(m_failedCounter);
            }
            else
            {
                returnCode = ReturnCode::Success;
            }
        }

    }
    catch (std::bad_cast const&)
    {
        LOG_ERROR << "Processing QLAH Host engine - sd cannot be casted to HostSensorData" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCounter);
        returnCode = ReturnCode::CastError;
    }

    return returnCode;
}

void
HostEngine::ClearContents() noexcept
{
    m_uartAliveSignalMissingCounter->ResetCounter();
    m_authenticationErrorCounter->ResetCounter();
}

#ifndef HCP5_PLATFORM
void
HostEngine::printEvent(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval)
{
    auto& eventLogger = Logger::GetInstance();
#ifdef TESTS
    eventLogger.InitRuleEvaluationFile();
#endif  // TESTS

    eventLogger.LogDebugAndToFile<std::string>(
        "HostEngine::printEvent - Creating HostErrorMonitoring alert event", 0, Logger::valueType::NO_TYPE);
    eventLogger.LogDebugAndToFile<uint64_t>(
        "HostEngine::printEvent - ruleEvaluationId", ruleEval.ruleEvaluationId, Logger::valueType::UINT_TYPE);
    eventLogger.LogDebugAndToFile<uint64_t>(
        "HostEngine::printEvent - timestamp", ruleEval.timestamp, Logger::valueType::UINT_TYPE);
    eventLogger.LogDebugAndToFile<pb_size_t>(
        "HostEngine::printEvent - which_RuleData", ruleEval.which_RuleData, Logger::valueType::UINT_TYPE);

    if (ruleEval.RuleData.hostErrorMonitoringReport.has_uPFirewallSignatureFailureAlert)
    {
        com_vwg_connect_ids_idsperiodicreport_v1_UPFirewallSignatureFailureAlert const uPFirewallSignatureFailureAlert
            = ruleEval.RuleData.hostErrorMonitoringReport.uPFirewallSignatureFailureAlert;
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uPFirewallSignatureFailureAlert.vkmsKeyListFailure",
            uPFirewallSignatureFailureAlert.vkmsKeyListFailure,
            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uPFirewallSignatureFailureAlert.sfdAccessProtectionError",
            uPFirewallSignatureFailureAlert.sfdAccessProtectionError,
            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uPFirewallSignatureFailureAlert.ivdIntegrityValidationError",
            uPFirewallSignatureFailureAlert.ivdIntegrityValidationError,
            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uPFirewallSignatureFailureAlert.moseContainerAuthenticityFailure",
            uPFirewallSignatureFailureAlert.moseContainerAuthenticityFailure,
            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uPFirewallSignatureFailureAlert.sokMessageAuthenticityFailure",
            uPFirewallSignatureFailureAlert.sokMessageAuthenticityFailure,
            Logger::valueType::UINT_TYPE);
    }

    if (ruleEval.RuleData.hostErrorMonitoringReport.has_uCFirewallSignatureFailureAlert)
    {
        com_vwg_connect_ids_idsperiodicreport_v1_UCFirewallSignatureFailureAlert const uCFirewallSignatureFailureAlert
            = ruleEval.RuleData.hostErrorMonitoringReport.uCFirewallSignatureFailureAlert;
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uCFirewallSignatureFailureAlert.authenticBootFailure",
            uCFirewallSignatureFailureAlert.authenticBootFailure,
            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uCFirewallSignatureFailureAlert.runTimeManipulationFailure",
            uCFirewallSignatureFailureAlert.runTimeManipulationFailure,
            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uCFirewallSignatureFailureAlert.secureBootSwtFailure",
            uCFirewallSignatureFailureAlert.secureBootSwtFailure,
            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uCFirewallSignatureFailureAlert.obdCvnNumberCalculationUcFailure",
            uCFirewallSignatureFailureAlert.obdCvnNumberCalculationUcFailure,
            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uCFirewallSignatureFailureAlert.obdCvnNumberCalculationSwtFailure",
            uCFirewallSignatureFailureAlert.obdCvnNumberCalculationSwtFailure,
            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uCFirewallSignatureFailureAlert.vkmsKeyListFailure",
            uCFirewallSignatureFailureAlert.vkmsKeyListFailure,
            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uCFirewallSignatureFailureAlert.rxSwinListFailure",
            uCFirewallSignatureFailureAlert.rxSwinListFailure,
            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uCFirewallSignatureFailureAlert.sfdAccessProtectionError",
            uCFirewallSignatureFailureAlert.sfdAccessProtectionError,
            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uCFirewallSignatureFailureAlert.ivdIntegrityValidationError",
            uCFirewallSignatureFailureAlert.ivdIntegrityValidationError,
            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>(
            "HostEngine::printEvent - uCFirewallSignatureFailureAlert.sokMessageAuthenticityFailure",
            uCFirewallSignatureFailureAlert.sokMessageAuthenticityFailure,
            Logger::valueType::UINT_TYPE);
    }

    if (ruleEval.RuleData.hostErrorMonitoringReport.has_uCHWFailureAlert)
    {
        com_vwg_connect_ids_idsperiodicreport_v1_UCHWFailureAlert const uCHWFailureAlert
            = ruleEval.RuleData.hostErrorMonitoringReport.uCHWFailureAlert;
        eventLogger.LogDebugAndToFile<bool>("HostEngine::printEvent - uCHWFailureAlert.cpuWatchdog",
                                            uCHWFailureAlert.cpu0Watchdog,
                                            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>("HostEngine::printEvent - uCHWFailureAlert.cpuWatchdog",
                                            uCHWFailureAlert.cpu1Watchdog,
                                            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>("HostEngine::printEvent - uCHWFailureAlert.cpuWatchdog",
                                            uCHWFailureAlert.cpu2Watchdog,
                                            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>("HostEngine::printEvent - uCHWFailureAlert.cpuWatchdog",
                                            uCHWFailureAlert.cpu3Watchdog,
                                            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>("HostEngine::printEvent - uCHWFailureAlert.cpuWatchdog",
                                            uCHWFailureAlert.cpuWatchdog,
                                            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>("HostEngine::printEvent - uCHWFailureAlert.hsmWatchdogAsserted",
                                            uCHWFailureAlert.hsmWatchdogAsserted,
                                            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>("HostEngine::printEvent - uCHWFailureAlert.phmHwIntegrityError",
                                            uCHWFailureAlert.phmHwIntegrityError,
                                            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>("HostEngine::printEvent - uCHWFailureAlert.mpuWrongAccess",
                                            uCHWFailureAlert.mpuWrongAccess,
                                            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>("HostEngine::printEvent - uCHWFailureAlert.lbistError",
                                            uCHWFailureAlert.lbistError,
                                            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>("HostEngine::printEvent - uCHWFailureAlert.mbistError",
                                            uCHWFailureAlert.mbistError,
                                            Logger::valueType::UINT_TYPE);
        eventLogger.LogDebugAndToFile<bool>("HostEngine::printEvent - uCHWFailureAlert.eccError",
                                            uCHWFailureAlert.eccError,
                                            Logger::valueType::UINT_TYPE);
    }

#ifdef TESTS
    eventLogger.LogDebugAndToFile<std::string>("", "", Logger::valueType::CLOSE);
#endif  // TESTS
}
#endif  //! HCP5_PLATFORM
