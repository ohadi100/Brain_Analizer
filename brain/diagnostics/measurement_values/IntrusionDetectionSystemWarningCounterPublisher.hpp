/**
 * @file
 * @brief     This file contains the definition of the IntrusionDetectionSystemWarningCounterPublisher class
 */
#ifndef INTRUSION_DETECTION_SYSTEM_WARNING_COUNTER_PUBLISHER_HPP
#define INTRUSION_DETECTION_SYSTEM_WARNING_COUNTER_PUBLISHER_HPP

#include "CounterMeasurementValue.hpp"
#include <ara/diag/intrusion_detection_system_warning_counter.h>


namespace common
{
    namespace counters
    {
        class CounterManager;
        class EventCounter;
    } // namespace counters
} // namespace common

namespace brain
{
namespace diagnostics
{
namespace measurement_values
{
using CounterManagerPtr = std::shared_ptr<common::counters::CounterManager>;
using EventCounterPtr = std::shared_ptr<common::counters::EventCounter>;
using CounterMeasurementValue = brain::diagnostics::measurement_values::CounterMeasurementValue;
using IntrusionDetectionSystemWarningCounter = vwg::e3p::diag::ids::IntrusionDetectionSystemWarningCounter;

class IntrusionDetectionSystemWarningCounterPublisher : public CounterMeasurementValue, IntrusionDetectionSystemWarningCounter
{
public:

    using IntrusionDetectionSystemWarningOutput = IntrusionDetectionSystemWarningCounter::OperationOutput;
    
    /**
     * @brief   Constructor
     * @param   CounterManagerPtr counters
     * @param   PersistentMapPtr persistentMemory
     */
    IntrusionDetectionSystemWarningCounterPublisher(CounterManagerPtr counters, PersistentMapPtr persistentMemory);
    
    /**
     * @brief   Destructor - saves measurement values to persistency
     */
    ~IntrusionDetectionSystemWarningCounterPublisher();

    /**
     * @brief    default copy constructor
     */
    IntrusionDetectionSystemWarningCounterPublisher(const IntrusionDetectionSystemWarningCounterPublisher& other)
        = delete;

    /**
     * @brief    default move constructor
     */
    IntrusionDetectionSystemWarningCounterPublisher(IntrusionDetectionSystemWarningCounterPublisher&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    IntrusionDetectionSystemWarningCounterPublisher& operator=(IntrusionDetectionSystemWarningCounterPublisher const&)
        = delete;

    /**
     * @brief   default move assignment operator
     */
    IntrusionDetectionSystemWarningCounterPublisher& operator=(IntrusionDetectionSystemWarningCounterPublisher&&)
        = delete;

    /**
     * @brief   Provides this data identifier.
     * @param   metaInfo meta information - currently ignored 
     * @param   cancellationHandler informs if the current conversation is canceled - currently ignored
     * @returns the data identifier.
     */
    ara::core::Future<IntrusionDetectionSystemWarningOutput> Read(
        ara::diag::MetaInfo metaInfo, ara::diag::CancellationHandler cancellationHandler) override;

private:

    /**
     * @brief   Updates Measurement value output with relevant data
     * @param   IntrusionDetectionSystemWarningOutput& output - the output to update
     */
    void updateMeasurementValue(IntrusionDetectionSystemWarningOutput& output);
};
} // namespace measurement_values
} // namespace diagnostics
} // namespace brain


#endif  // INTRUSION_DETECTION_SYSTEM_WARNING_COUNTER_PUBLISHER_HPP
