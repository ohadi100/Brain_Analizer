/**
 * @file
 * @brief     A rule engine for the Unkown Constrain Id events
 */
#ifndef UNKNOWN_CONSTRAIN_ENGINE_HPP
#define UNKNOWN_CONSTRAIN_ENGINE_HPP

#include "brain/engines/EngineEventSender.hpp"

namespace brain
{
namespace engines
{
namespace swpac
{

class UnknownConstraintEngine : public EngineEventSender
{
public:
    using CounterManagerPtr   = common::counters::CounterManagerPtr;
    using ConfigurationPtr    = common::configuration::Pointer;
    using EventCounter        = common::counters::EventCounter;
    using EventNoiseFilterPtr = std::shared_ptr<brain::brain_noise_filter::EventNoiseFilter>;
    using EventCounterPtr     = std::shared_ptr<common::counters::EventCounter>;

    /**
     * @brief   Constructor
     * @param   CounterManagerPtr debugCounters
     * @param   msgRepository for communicate with sender manager sender.
     * @param   reportSerializer - class to serialize idsperiodicreport proto object
     * @param   SPEventNoiseFilter eventNoiseFilter
     * @param   EventPriority priority
     */
    UnknownConstraintEngine(CounterManagerPtr                                 debugCounters,
                            MessageRepositoryPtr                              msgRepository,
                            EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                            EventNoiseFilterPtr                               eventNoiseFilter,
                            events::EventPriority priority = events::EventPriority::Important);

    /**
     * @brief used to send unknown constraint id to backend
     * @param constraintId - unknown constraint id
     * @param incident - incident json as string
     * @return true - if alert is sent successfully
     * @return false - if could not send alert
     */
    static bool sendAlertExt(std::string const& constraintId, std::string const& incident);

    /**
     * @brief used to send unknown constraint id to backend
     * @param constraintId - unknown constraint id
     * @param incident - incident json as string
     * @return true - if alert is sent successfully
     * @return false - if could not send alert
     */
    bool sendAlert(std::string const& constraintId, std::string const& incidentt);

private:
    EventCounterPtr m_failedCounter;
    EventCounterPtr m_alertSendCounter;
};

}  // namespace swpac
}  // namespace engines
}  // namespace brain

#endif