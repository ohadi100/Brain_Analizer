/**
 * @file
 * @brief     This file contains the definition of the DiagMeasurementValuesManager class
 */
#ifndef DIAG_MEASUREMENT_VALUES_MANAGER_HPP
#define DIAG_MEASUREMENT_VALUES_MANAGER_HPP

#include <memory>

#include "brain/diagnostics/measurement_values/IntrusionDetectionSystemErrorCounterPublisher.hpp"
#include "brain/diagnostics/measurement_values/IntrusionDetectionSystemWarningCounterPublisher.hpp"

namespace common
{
    namespace counters
    {
        class CounterManager;
    } // namespace counters
} // namespace common


namespace brain
{
namespace diagnostics
{
namespace measurement_values
{
/**
 * @class   DiagMeasurementValuesManager
 * @brief   Initializes and stops all measurement values
 */
class DiagMeasurementValuesManager
{
public:

    using CounterManagerPtr = std::shared_ptr<common::counters::CounterManager>;

    using IntrusionDetectionSystemErrorCounterPublisher = brain::diagnostics::measurement_values::IntrusionDetectionSystemErrorCounterPublisher;
    using IntrusionDetectionSystemWarningCounterPublisher = brain::diagnostics::measurement_values::IntrusionDetectionSystemWarningCounterPublisher;

    /**
     * @brief   Constructor
     * @param   CounterManagerPtr countersManager
     */
    DiagMeasurementValuesManager(CounterManagerPtr countersManager);

    /**
     * @brief   set up counters for diagnostics
     * @param   PersistentMapPtr persistentMemory - persistent memory for saving measurement values
     */
    void SetUpCounterPublishers(PersistentMapPtr persistentMemory);
    
    /**
     * @brief   Resets all measurement values
     * @return  true if successfull, false otherwise
     */
    bool ResetMeasurementValues();

#ifndef TESTS
private:
#endif // TESTS

    CounterManagerPtr m_countersManager;

    std::shared_ptr<IntrusionDetectionSystemWarningCounterPublisher> m_diagIntrusionDetectionSystemWarningCounterPublisher; // 0x032c
    std::shared_ptr<IntrusionDetectionSystemErrorCounterPublisher> m_diagIntrusionDetectionSystemErrorCounterPublisher; // 0x032d
};

} // namespace measurement_values
} // namespace diagnostics
} // namespace brain

#endif // DIAG_MEASUREMENT_VALUES_MANAGER_HPP
