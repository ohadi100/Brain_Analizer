/**
 * @file
 * @brief    This file contains the definition of PortalCommunicator.
 */

#ifndef PORTALCOMMUNICATOR_HPP
#define PORTALCOMMUNICATOR_HPP

#include "brain/communicator/Communicator.hpp"
#include "PortalSubscriber.hpp"

namespace brain
{
namespace brain_communicator
{
namespace portal
{
class PortalCommunicator : public Communicator
{
    using CounterManagerPtr    = std::shared_ptr<common::counters::CounterManager>;
    using PortalSubscriberPtr  = std::shared_ptr<brain::brain_communicator::portal::PortalSubscriber>;

public:
    PortalCommunicator(SensorDataQueuesManagerPtr queuesManager,
                       CounterManagerPtr          debugCounters,
                       uint32_t                   flushThreshold,
                       NoiseFilterPtr             sensorNoiseFilter = nullptr);

    ~PortalCommunicator() override;

    virtual void Start() override;

    virtual void Stop() override;

#ifndef TESTS
private:
#endif  // TESTS
    CounterManagerPtr    m_debugCounters;
    PortalSubscriberPtr  m_subscriber;
};

} /* namespace portal */
} /* namespace brain_communicator */
} /* namespace brain */

#endif /* PORTALCOMMUNICATOR_HPP */


