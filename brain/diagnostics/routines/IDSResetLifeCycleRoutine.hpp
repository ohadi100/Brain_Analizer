/**
 * @file
 * @brief     This file contains the definition of the IDSResetLifeCycleRoutine class
 */
#ifndef IDS_RESET_LIFE_CYCLE_ROUTINE_HPP
#define IDS_RESET_LIFE_CYCLE_ROUTINE_HPP

#include <ara/diag/intrusion_detection_system_reset_life_cycle_data.h>
#include <ara/diag/app_ids.h>
#include <mutex>
#include <atomic>


namespace brain
{
    namespace diagnostics
    {
        namespace measurement_values
        {
            class DiagMeasurementValuesManager;
        }
    }
}

namespace brain 
{
namespace diagnostics 
{
namespace routines 
{

// Contains all valid combinations of routine result & status
enum RoutineResultStatus : uint8_t
{
    ROUTINESTATUS_NOT_ACTIVE = 0x00U,
    ROUTINESTATUS_ACTIVE = 0x01U,
    ROUTINESTATUS_COMPLETED_FALSE_RESULTS = 0x14U,
    ROUTINESTATUS_COMPLETED_CORRECT_RESULTS = 0x24U
};

using IntrusionDetectionSystemResetLifeCycleData = vwg::e3p::diag::ids::IntrusionDetectionSystemResetLifeCycleData;
using DiagMeasurementValuesManagerPtr = std::shared_ptr<brain::diagnostics::measurement_values::DiagMeasurementValuesManager>;

class IDSResetLifeCycleRoutine : public IntrusionDetectionSystemResetLifeCycleData
{
public:

    using FutureRequestResultsOutput = ara::core::Future<IntrusionDetectionSystemResetLifeCycleData::RequestResultsOutput>;
    using FutureStartOutput = ara::core::Future<IntrusionDetectionSystemResetLifeCycleData::StartOutput>;

    /**
     * @brief   constructor
     */
    IDSResetLifeCycleRoutine(DiagMeasurementValuesManagerPtr measurementValuesManager);

    /**
     * @brief   destructor
     */
    ~IDSResetLifeCycleRoutine();

    /**
     * @brief    default copy constructor
     */
    IDSResetLifeCycleRoutine(const IDSResetLifeCycleRoutine& other) = delete;

    /**
     * @brief    default move constructor
     */
    IDSResetLifeCycleRoutine(IDSResetLifeCycleRoutine&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    IDSResetLifeCycleRoutine& operator=(IDSResetLifeCycleRoutine const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    IDSResetLifeCycleRoutine& operator=(IDSResetLifeCycleRoutine&&) = delete;

    /**
     * @brief   RequestResults method implementation.
     * @return  future The Routine Results status.
     */
    FutureRequestResultsOutput RequestResults(ara::diag::MetaInfo, ara::diag::CancellationHandler) override;

    /**
     * @brief   Start method implementation.
     * @return  future The result of Start method
     */
    FutureStartOutput Start(ara::core::Array<uint8_t, 3U> const&, ara::diag::MetaInfo, ara::diag::CancellationHandler) override;

private:

    std::atomic<RoutineResultStatus> m_routineResultStatus;

    DiagMeasurementValuesManagerPtr m_measurementValuesManager;
};

} // routines
} // namespace diagnostics
} // namespace brain

#endif // IDS_RESET_LIFE_CYCLE_ROUTINE_HPP
