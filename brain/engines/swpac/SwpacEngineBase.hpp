/**
 * @file
 * @brief     This file contains the definition of the SwpacEngineBase class and its functionality.
 */

#ifndef SWPAC_ENGINE_BASE_HPP
#define SWPAC_ENGINE_BASE_HPP

#include "brain/engines/EngineEventSender.hpp"
#include "brain/engines/Engine.hpp"
#include "IncidentCounterTable.hpp"
#include "brain/sensor_data/swpac/SwpacSensorDataBase.hpp"
#include "common/counter_manager/CounterManager.hpp"

namespace brain
{
namespace engines
{
namespace swpac
{

/**
 * @class   SwpacEngineBase
 * @brief   Class which manages the string size alert for all engines that might trigger this alarm
 */
class SwpacEngineBase
  : public Engine
  , public EngineEventSender
{
public:
    using CounterManagerPtr   = common::counters::CounterManagerPtr;
    using EventNoiseFilterPtr = std::shared_ptr<brain::brain_noise_filter::EventNoiseFilter>;
    using EventCounterPtr     = std::shared_ptr<common::counters::EventCounter>;
    
    /**
     * @brief   Ctor
     * @param   CounterManagerPtr   debugCounters - debug counters manager
     * @param   EventPriority       priority      - event priority
     * @param   msgRepository       for communicate with sender manager sender
     * @param reportSerializer - class to serialize idsperiodicreport proto object
     * @param   EventNoiseFilterPtr  eventNoiseFilter - noise filter
     */
    SwpacEngineBase(CounterManagerPtr                                 debugCounters,
                    events::EventPriority                             priority,
                    MessageRepositoryPtr                              msgRepository,
                    EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                    EventNoiseFilterPtr                               eventNoiseFilter);

    /**
     * @brief Set the Incident Counter Table object
     * @param incidentCounter - incident counter table
     * @return none
     */
    inline void
    SetIncidentCounterTable(SPIncidentCounterTable incidentCounter)
    {
        m_incidentCounter = incidentCounter;
    }

protected:
    bool                   sendStringSizeAlert(SensorDataTag                                             sdTag,
                                               brain::sensor_data::swpac::ConstraintId                   constrainId,
                                               brain::sensor_data::SwpacSensorDataBase::AlertData const& ad);
    SPIncidentCounterTable m_incidentCounter;
    EventCounterPtr         m_failedCounter;
    EventCounterPtr         m_alertSendCounter;
};

}  // namespace swpac
}  // namespace engines
}  // namespace brain

#endif  // SWPAC_ENGINE_BASE_HPP
