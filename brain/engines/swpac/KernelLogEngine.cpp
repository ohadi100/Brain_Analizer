/**
 * @file
 * @brief     A rule engine for the Kernel Log sensor data
 */
#include "KernelLogEngine.hpp"
#include "autogen/nanopb/NanoPbInclude.hpp"
#include "brain/config/AlertEventsNames.cpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"

using brain::engines::ReturnCode;
using brain::engines::swpac::KernelLogEngine;
using brain::sender_events::CriticalEventAlert;
using brain::sender_events::GetCriticalEventString;
using brain::sensor_data::KernelLogSensorData;
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

KernelLogEngine::KernelLogEngine(CounterManagerPtr                                 debugCounters,
                                 MessageRepositoryPtr                              msgRepository,
                                 EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                                 EventNoiseFilterPtr                               eventNoiseFilter,
                                 events::EventPriority                             priority)
  : SwpacEngineBase(debugCounters, priority, msgRepository, reportSerializer, eventNoiseFilter)
{
    if (debugCounters)
    {
        m_failedCounter    = debugCounters->CreateCounter(common::counters::KERNEL_LOG_FAILED_PROCESS_COUNTER_NAME,
                                                       EventCounter::EventCounterLevelType::COUNTER_WARNING);
        m_alertSendCounter = debugCounters->CreateCounter(common::counters::KERNEL_LOG_DHM_ALERT_SENT_COUNTER_NAME,
                                                          EventCounter::EventCounterLevelType::COUNTER_WARNING);
    }
}

bool
KernelLogEngine::sendAlert(KernelLogSensorData const& sd)
{
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;

    com_vwg_connect_ids_idsperiodicreport_v1_DhmOsLogIncident dhmOsLogIncident
        = com_vwg_connect_ids_idsperiodicreport_v1_DhmOsLogIncident_init_default;

    dhmOsLogIncident.timestamp = sd.GetLogMessageTimestamp().value();
    if (sd.GetLogMessageMessage().has_value())
    {
        dhmOsLogIncident.logMessage = common::nanopb::CreateEncodingCallback(sd.GetLogMessageMessage().value());
    }
    dhmOsLogIncident.logLevel = sd.GetLogMessageLoglevel().value();
    dhmOsLogIncident.facility = sd.GetLogMessageFacility().value();

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    ruleEval.which_RuleData   = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_dhmOsLogRegexKernelPanicAlert_tag);
    ruleEval.RuleData.dhmOsLogRegexKernelPanicAlert = dhmOsLogIncident;

    auto const status
        = SendEvent(ruleEval, SensorDataTag::SD_SWPAC_KERNEL_LOG, CriticalEventAlert::OSLogKernelPanic);

    common::counters::IncreaseCounter((EngineEventSender::SendStatus::Success != status) ? m_failedCounter
                                                                                         : m_alertSendCounter);

    return (EngineEventSender::SendStatus::Success == status);
}

ReturnCode
KernelLogEngine::processInternal(UPSensorData const sd)
{
    try
    {
        LOG_VERBOSE << "Began processing KernelLogSensorData" << LOG_NOOP;
        auto const& kernelLogSD = dynamic_cast<KernelLogSensorData const&>(*sd);

        if (!kernelLogSD.GetLogMessageTimestamp().has_value())
        {
            LOG_ERROR << "KernelLog Engine - 'timestamp' value is missing" << LOG_NOOP;
            common::counters::IncreaseCounter(m_failedCounter);
            return ReturnCode::InvalidError;
        }

        if (!kernelLogSD.GetLogMessageLoglevel().has_value())
        {
            LOG_ERROR << "KernelLog Engine - 'loglevel' value is missing" << LOG_NOOP;
            common::counters::IncreaseCounter(m_failedCounter);
            return ReturnCode::InvalidError;
        }

        if (!kernelLogSD.GetLogMessageFacility().has_value())
        {
            LOG_ERROR << "KernelLog Engine - 'facility' value is missing" << LOG_NOOP;
            common::counters::IncreaseCounter(m_failedCounter);
            return ReturnCode::InvalidError;
        }

        // send string size alert only if the SD is valid
        if (kernelLogSD.IsAlert())
        {
            LOG_DEBUG << "KernelLog Engine - string size alert" << LOG_NOOP;
            sendStringSizeAlert(
                kernelLogSD.GetTag(), kernelLogSD.GetConstraintId(), kernelLogSD.GetStringSizeAlertData());
        }

        if (m_incidentCounter)
        {
            m_incidentCounter->Increment(brain::sensor_data::swpac::ConstraintId::KERNEL_LOG_KERNEL_PANIC);
        }

        return (sendAlert(kernelLogSD) ? ReturnCode::Success : ReturnCode::FailedError);
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::bad_cast const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "SD cannot be casted to KernelLogSensorData" << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCounter);
        return ReturnCode::CastError;
    }
}
