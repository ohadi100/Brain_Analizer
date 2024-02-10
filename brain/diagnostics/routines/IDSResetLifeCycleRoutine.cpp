/**
 * @file
 * @brief     This file contains the functionality of the IDSResetLifeCycleRoutine class
 *            Implements diagnostics requirement 0x030a
 */
#include "IDSResetLifeCycleRoutine.hpp"
#include "brain/diagnostics/measurement_values/DiagMeasurementValuesManager.hpp"
#include "common/utils/diagnostics/DiagnosticsUtils.hpp"
#include "common/utils/logger/Logger.hpp"


using brain::diagnostics::routines::IDSResetLifeCycleRoutine;


IDSResetLifeCycleRoutine::IDSResetLifeCycleRoutine(DiagMeasurementValuesManagerPtr measurementValuesManager)  :
    IntrusionDetectionSystemResetLifeCycleData(GENERATE_INSTANCE_SPECIFIER(ids_rid_IntrusionDetectionSystemResetLifeCycleData)),
    m_routineResultStatus(RoutineResultStatus::ROUTINESTATUS_NOT_ACTIVE),
    m_measurementValuesManager(measurementValuesManager)
{
    std::ignore = Offer();
}

IDSResetLifeCycleRoutine::~IDSResetLifeCycleRoutine()
{
    try
    {
        StopOffer();
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "destruction of the IDSResetLifeCycleRoutine failed and got exception." << LOG_NOOP;
    }  // only for parasoft violations
}

IDSResetLifeCycleRoutine::FutureRequestResultsOutput
IDSResetLifeCycleRoutine::RequestResults(ara::diag::MetaInfo, ara::diag::CancellationHandler)
{
    LOG_INFO << "IDSResetLifeCycleRoutine routine RequestResultsStatus: "
             << static_cast<uint8_t>(m_routineResultStatus.load()) << LOG_NOOP;

    ara::core::Promise<RequestResultsOutput> promiseOutput;
    RequestResultsOutput output;

    output.Routine_Request_Routine_Results_Response_Intrusion_detection_system_reset_life_cycle_data_Routine_Status_Routine_Result = m_routineResultStatus;

    promiseOutput.set_value(std::move(output));

    return promiseOutput.get_future();
}

IDSResetLifeCycleRoutine::FutureStartOutput
IDSResetLifeCycleRoutine::Start(
    ara::core::Array<uint8_t, 3U> const&,
    ara::diag::MetaInfo,
    ara::diag::CancellationHandler)
{
    auto const previousStatus = m_routineResultStatus.exchange(RoutineResultStatus::ROUTINESTATUS_ACTIVE);
    if (previousStatus != RoutineResultStatus::ROUTINESTATUS_ACTIVE)
    {
        LOG_INFO << ("Starting IDSResetLifeCycleRoutine routine") << LOG_NOOP;

        if ((nullptr != m_measurementValuesManager) && m_measurementValuesManager->ResetMeasurementValues())
        {
            m_routineResultStatus = RoutineResultStatus::ROUTINESTATUS_COMPLETED_CORRECT_RESULTS;
        }
        else
        {
            m_routineResultStatus = RoutineResultStatus::ROUTINESTATUS_COMPLETED_FALSE_RESULTS;
        }

        LOG_INFO << ("Finished IDSResetLifeCycleRoutine routine") << LOG_NOOP;
    }

    ara::core::Promise<StartOutput> promiseOutput;
    promiseOutput.set_value();

    return promiseOutput.get_future();
}
