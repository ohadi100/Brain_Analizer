/**
* @file
* @brief       An Engine class that does no special operations

*/
#ifndef NULL_ENGINE_HPP
#define NULL_ENGINE_HPP

#include "Engine.hpp"
#include "common/counter_manager/CounterManager.hpp"

namespace brain
{
namespace engines
{

using common::sensor_data::UPSensorData;

/**
 * @class   NullEngine
 * @brief   The NullEngine class defines the rule engine of the Special Frame Report analysis logic
 *          The class defines and runs the process of the rule engines of the Special Frame Report analysis
 */
class NullEngine : public Engine
{
public:

    using EventCounter = common::counters::EventCounter;
    using Counterptr = std::shared_ptr<EventCounter>;
    using CounterManagerPtr = common::counters::CounterManagerPtr;

public:

    /**
     * @brief   Constructor
     * @param   CounterManagerPtr & countersManager - counters manager
     */
    NullEngine(CounterManagerPtr countersManager);

    /**
     * @brief   Logs but does nothing else
     * @param   UPSensorData& sd - the notification dequeued from the WRR
     * @return  ReturnCode - always ReturnCode::Success
     */
    ReturnCode processInternal(UPSensorData sd) override;
    
private:
    Counterptr m_nullCounter;
};

} // namespace engines
} // namespace brain

#endif // NULL_ENGINE_HPP