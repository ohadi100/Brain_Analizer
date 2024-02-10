/**
 * @file
 * @brief     This file contains the definition of the IntrusionDetectionSystemErrorCounterPublisher class
 */
#ifndef COUNTER_MEASUREMENT_VALUE_HPP
#define COUNTER_MEASUREMENT_VALUE_HPP

#include <map>
#include <memory>


namespace common
{
    namespace counters
    {
        class EventCounter;
    } // namespace counters

    namespace utils
    {
        class PersistentMap;
    } // namespace utils
} // namespace common

namespace brain
{
namespace diagnostics
{
namespace measurement_values
{
using EventCounterPtr = std::shared_ptr<common::counters::EventCounter>;
using PersistentMapPtr = std::shared_ptr<common::utils::PersistentMap>;

class CounterMeasurementValue
{
public:

    /**
     * @brief   Constructor
     * @param   PersistentMapPtr persistentMemory
     */
    CounterMeasurementValue(PersistentMapPtr persistentMemory) :
        m_persistentMemory(persistentMemory)
    {}

    virtual ~CounterMeasurementValue() = default;

    /**
     * @brief    default copy constructor
     */
    CounterMeasurementValue(const CounterMeasurementValue& other) = delete;

    /**
     * @brief    default move constructor
     */
    CounterMeasurementValue(CounterMeasurementValue&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    CounterMeasurementValue& operator=(CounterMeasurementValue const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    CounterMeasurementValue& operator=(CounterMeasurementValue&&) = delete;    
    
    /**
     * @brief   Resets all measurement value counters.
     * @returns true if successfully reseted all counters, false otherwise.
     */
    bool ResetCounters();

protected:

    void addCounter(EventCounterPtr counter);

    uint64_t getCount(std::string const& counterName) const;

    void loadFromPersistentMemory();

    void saveToPersistentMemory();

    PersistentMapPtr m_persistentMemory;

    std::map<std::string, EventCounterPtr> m_counters;
};

} // namespace measurement_values
} // namespace diagnostics
} // namespace brain


#endif  // COUNTER_MEASUREMENT_VALUE_HPP
