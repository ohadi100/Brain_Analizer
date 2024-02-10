/**
 * @file
 * @brief     This file contains the functionality of the IntrusionDetectionSystemWarningCounterPublisher class
 *            Implementing diagnostics requirement 0x032c
 */
#include "IntrusionDetectionSystemWarningCounterPublisher.hpp"
#include <ara/diag/app_ids.h>
#include "common/utils/logger/Logger.hpp"
#include "common/counter_manager/CounterManager.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/utils/diagnostics/DiagnosticsUtils.hpp"


using brain::diagnostics::measurement_values::IntrusionDetectionSystemWarningCounterPublisher;
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;


IntrusionDetectionSystemWarningCounterPublisher::IntrusionDetectionSystemWarningCounterPublisher(CounterManagerPtr countersManager, PersistentMapPtr persistentMemory) : 
    CounterMeasurementValue(persistentMemory),
    IntrusionDetectionSystemWarningCounter(GENERATE_INSTANCE_SPECIFIER(ids_did_IntrusionDetectionSystemWarningCounter))
{
    if (nullptr != countersManager)
    {
        addCounter(countersManager->GetCounter(common::counters::warning::LINK_UTILIZATION_THRESHOLD_EXCEEDED_COUNTER_NAME));
        addCounter(countersManager->GetCounter(common::counters::warning::TLS_ERROR_REPORT_CREATED_EVENT_COUNTER_NAME));
        addCounter(countersManager->GetCounter(common::counters::warning::MICRO_PROCESSOR_SIGNATURE_FAILURE_COUNTER_NAME));
        addCounter(countersManager->GetCounter(common::counters::warning::MICRO_CONTROLLER_SIGNATURE_FAILURE_COUNTER_NAME));
        addCounter(countersManager->GetCounter(common::counters::warning::MICRO_CONTROLLER_HARDWARE_FAILURE_COUNTER_NAME));
    }
    else
    {
        LOG_WARNING << "CounterManager is nullptr, can't get counter values" << LOG_NOOP;
    }

    loadFromPersistentMemory();

    LOG_INFO << "Initiating IntrusionDetectionSystemWarningCounter measurement value publisher" << LOG_NOOP;
    std::ignore = IntrusionDetectionSystemWarningCounter::Offer();
}

IntrusionDetectionSystemWarningCounterPublisher::~IntrusionDetectionSystemWarningCounterPublisher()
{
    try
    {
        LOG_INFO << "Stopping IntrusionDetectionSystemWarningCounter measurement value publisher" << LOG_NOOP;
        IntrusionDetectionSystemWarningCounter::StopOffer();

        saveToPersistentMemory();
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "destruction of the IntrusionDetectionSystemWarningCounterPublisher failed and got exception."
                  << LOG_NOOP;
    }  // only for parasoft violations
}

ara::core::Future<IntrusionDetectionSystemWarningCounterPublisher::OperationOutput>
IntrusionDetectionSystemWarningCounterPublisher::Read(
        ara::diag::MetaInfo metaInfo, ara::diag::CancellationHandler cancellationHandler)
{
    static_cast<void>(metaInfo);
    static_cast<void>(cancellationHandler);

    ::ara::core::Promise<IntrusionDetectionSystemWarningOutput> promise;
    IntrusionDetectionSystemWarningOutput out;

    updateMeasurementValue(out);

    promise.set_value(out);

    return promise.get_future();
}

void IntrusionDetectionSystemWarningCounterPublisher::updateMeasurementValue(IntrusionDetectionSystemWarningOutput& output)
{
    output.MeasurementValue_0x032c_Intrusion_detection_system_warning_counter_Link_utilization_threshold_exceeded = static_cast<uint16_t>(getCount(common::counters::warning::LINK_UTILIZATION_THRESHOLD_EXCEEDED_COUNTER_NAME));
    output.MeasurementValue_0x032c_Intrusion_detection_system_warning_counter_Suspected_brute_force_attack_tls = static_cast<uint16_t>(getCount(common::counters::warning::TLS_ERROR_REPORT_CREATED_EVENT_COUNTER_NAME));
    output.MeasurementValue_0x032c_Intrusion_detection_system_warning_counter_Micro_prozessor_signature_failure = static_cast<uint16_t>(getCount(common::counters::warning::MICRO_PROCESSOR_SIGNATURE_FAILURE_COUNTER_NAME));
    output.MeasurementValue_0x032c_Intrusion_detection_system_warning_counter_Micro_controller_signature_failure = static_cast<uint16_t>(getCount(common::counters::warning::MICRO_CONTROLLER_SIGNATURE_FAILURE_COUNTER_NAME));
    output.MeasurementValue_0x032c_Intrusion_detection_system_warning_counter_Microcontroller_hardware_failure = static_cast<uint16_t>(getCount(common::counters::warning::MICRO_CONTROLLER_HARDWARE_FAILURE_COUNTER_NAME));
    output.MeasurementValue_0x032c_Intrusion_detection_system_warning_counter_Protocol_signature_failure = 6U;
}