/**
 * @file
 * @brief     This file contains the definition of the IntrusionDetectionSystemErrorCounterPublisher class
 */
#ifndef INTRUSION_DETECTION_SYSTEM_ERROR_COUNTER_PUBLISHER_HPP
#define INTRUSION_DETECTION_SYSTEM_ERROR_COUNTER_PUBLISHER_HPP

#include "CounterMeasurementValue.hpp"
#include <ara/diag/intrusion_detection_system_error_counter.h>


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
using IntrusionDetectionSystemErrorCounter = vwg::e3p::diag::ids::IntrusionDetectionSystemErrorCounter;

class IntrusionDetectionSystemErrorCounterPublisher : public CounterMeasurementValue, IntrusionDetectionSystemErrorCounter
{
public:

    using IntrusionDetectionSystemErrorOutput = IntrusionDetectionSystemErrorCounter::OperationOutput;
    
    /**
     * @brief   Constructor
     * @param   CounterManagerPtr counters
     * @param   PersistentMapPtr persistentMemory
     */
    IntrusionDetectionSystemErrorCounterPublisher(CounterManagerPtr countersManager, PersistentMapPtr persistentMemory);

    /**
     * @brief   Destructor - saves measurement values to persistency
     */
    ~IntrusionDetectionSystemErrorCounterPublisher();

    /**
     * @brief    default copy constructor
     */
    IntrusionDetectionSystemErrorCounterPublisher(const IntrusionDetectionSystemErrorCounterPublisher& other) = delete;

    /**
     * @brief    default move constructor
     */
    IntrusionDetectionSystemErrorCounterPublisher(IntrusionDetectionSystemErrorCounterPublisher&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    IntrusionDetectionSystemErrorCounterPublisher& operator=(IntrusionDetectionSystemErrorCounterPublisher const&)
        = delete;

    /**
     * @brief   default move assignment operator
     */
    IntrusionDetectionSystemErrorCounterPublisher& operator=(IntrusionDetectionSystemErrorCounterPublisher&&) = delete;

    /**
     * @brief   Provides this data identifier.
     * @param   metaInfo meta information - currently ignored 
     * @param   cancellationHandler informs if the current conversation is canceled - currently ignored
     * @returns the data identifier.
     */
    ara::core::Future<IntrusionDetectionSystemErrorOutput> Read(
        ara::diag::MetaInfo metaInfo, ara::diag::CancellationHandler cancellationHandler) override;

private:

    /**
     * @brief   Updates Measurement value output with relevant data
     * @param   IntrusionDetectionSystemErrorOutput& output - the output to update
     */
    void updateMeasurementValue(IntrusionDetectionSystemErrorOutput& output);
};

} // namespace measurement_values
} // namespace diagnostics
} // namespace brain


#endif  // INTRUSION_DETECTION_SYSTEM_ERROR_COUNTER_PUBLISHER_HPP
