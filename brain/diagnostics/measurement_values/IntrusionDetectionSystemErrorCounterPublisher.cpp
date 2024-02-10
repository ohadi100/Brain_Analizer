/**
 * @file
 * @brief This file contains the functionality of the IntrusionDetectionSystemErrorCounterPublisher class
 *        Implementing diagnostics requirement 0x032d
 */
#include "IntrusionDetectionSystemErrorCounterPublisher.hpp"
#include <ara/diag/app_ids.h>
#include "common/utils/logger/Logger.hpp"
#include "common/counter_manager/CounterManager.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/utils/diagnostics/DiagnosticsUtils.hpp"


using brain::diagnostics::measurement_values::IntrusionDetectionSystemErrorCounterPublisher;
namespace brain
{
namespace diagnostics
{
namespace measurement_values
{
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;
}  // namespace measurement_values
}  // namespace diagnostics
}  // namespace brain

IntrusionDetectionSystemErrorCounterPublisher::IntrusionDetectionSystemErrorCounterPublisher(CounterManagerPtr countersManager, PersistentMapPtr persistentMemory) : 
    CounterMeasurementValue(persistentMemory),
    IntrusionDetectionSystemErrorCounter(GENERATE_INSTANCE_SPECIFIER(ids_did_IntrusionDetectionSystemErrorCounter))
{
    if (nullptr != countersManager)
    {
        addCounter(countersManager->GetCounterWithTs(common::counters::errors::UNKNOWN_PROTOCOL_FRAMES_COUNTER));
        addCounter(countersManager->GetCounterWithTs(common::counters::errors::ILLEGAL_VLAN_DROP_COUNTER));
        addCounter(countersManager->GetCounterWithTs(common::counters::errors::ILLEGAL_IP_DROP_COUNTER));
        addCounter(countersManager->GetCounterWithTs(common::counters::errors::UART_ALIVE_SIGNAL_MISSING_COUNTER_NAME));
        addCounter(countersManager->GetCounterWithTs(common::counters::errors::AUTHENTICATION_ERROR_COUNTER_NAME));
        addCounter(countersManager->GetCounter(common::counters::errors::BRAIN_CRASH_FREEZE_RESET_COUNTER_NAME));
    }
    else
    {
        LOG_WARNING << "CounterManager is nullptr, can't get counter values" << LOG_NOOP;
    }

    loadFromPersistentMemory();

    LOG_INFO << ("Initiating IntrusionDetectionSystemErrorCounter measurement value publisher") << LOG_NOOP;
    std::ignore = IntrusionDetectionSystemErrorCounter::Offer();
}

IntrusionDetectionSystemErrorCounterPublisher::~IntrusionDetectionSystemErrorCounterPublisher()
{
    try
    {
        LOG_INFO << "Stopping IntrusionDetectionSystemErrorCounter measurement value publisher" << LOG_NOOP;
        IntrusionDetectionSystemErrorCounter::StopOffer();

        saveToPersistentMemory();
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "destruction of the IntrusionDetectionSystemErrorCounterPublisher failed and got exception."
                  << LOG_NOOP;
    }  // only for parasoft violations
}

ara::core::Future<IntrusionDetectionSystemErrorCounterPublisher::OperationOutput>
IntrusionDetectionSystemErrorCounterPublisher::Read(
        ara::diag::MetaInfo metaInfo, ara::diag::CancellationHandler cancellationHandler)
{
    static_cast<void>(metaInfo);
    static_cast<void>(cancellationHandler);

    ::ara::core::Promise<IntrusionDetectionSystemErrorOutput> promise;
    IntrusionDetectionSystemErrorOutput out;

    updateMeasurementValue(out);

    promise.set_value(out);

    return promise.get_future();
}

void IntrusionDetectionSystemErrorCounterPublisher::updateMeasurementValue(IntrusionDetectionSystemErrorOutput& output)
{
    output.MeasurementValue_0x032d_Intrusion_detection_system_error_counter_Unknown_protocol_frames = static_cast<uint16_t>(getCount(common::counters::errors::UNKNOWN_PROTOCOL_FRAMES_COUNTER));
    output.MeasurementValue_0x032d_Intrusion_detection_system_error_counter_Illegal_vlan_drop_counter = static_cast<uint16_t>(getCount(common::counters::errors::ILLEGAL_VLAN_DROP_COUNTER));
    output.MeasurementValue_0x032d_Intrusion_detection_system_error_counter_Illegal_ip_drop_counter = static_cast<uint16_t>(getCount(common::counters::errors::ILLEGAL_IP_DROP_COUNTER));
    output.MeasurementValue_0x032d_Intrusion_detection_system_error_counter_UART_alive_signal_missing_counter = static_cast<uint16_t>(getCount(common::counters::errors::UART_ALIVE_SIGNAL_MISSING_COUNTER_NAME));
    output.MeasurementValue_0x032d_Intrusion_detection_system_error_counter_Authentication_error_counter = static_cast<uint16_t>(getCount(common::counters::errors::AUTHENTICATION_ERROR_COUNTER_NAME));
    output.MeasurementValue_0x032d_Intrusion_detection_system_error_counter_Reset_counter = static_cast<uint16_t>(getCount(common::counters::errors::BRAIN_CRASH_FREEZE_RESET_COUNTER_NAME));
}
