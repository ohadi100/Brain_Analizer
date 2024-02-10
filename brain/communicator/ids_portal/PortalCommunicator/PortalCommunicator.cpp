#include "PortalCommunicator.hpp"

using brain::brain_communicator::portal::PortalCommunicator;

PortalCommunicator::PortalCommunicator(SensorDataQueuesManagerPtr queuesManager,
                                       CounterManagerPtr          debugCounters,
                                       uint32_t                   flushThreshold,
                                       NoiseFilterPtr             sensorNoiseFilter)
  : Communicator(queuesManager, flushThreshold, CommunicatorId::SECURITY_EVENT, sensorNoiseFilter)
  , m_debugCounters(debugCounters)
{
    m_subscriber = std::make_shared<brain::brain_communicator::portal::PortalSubscriber>("127.0.0.1", 44444);
    LOG_INFO << "IDS PortalCommunicator" << LOG_NOOP;
}

PortalCommunicator::~PortalCommunicator()
{
    LOG_INFO << "IDS ~PortalCommunicator" << LOG_NOOP;
    Stop();
}

void PortalCommunicator::Start()
{
    LOG_INFO << "IDS Subscribing to portal IDSM" << LOG_NOOP;
    m_subscriber->Subscribe();
}

void PortalCommunicator::Stop()
{
    LOG_INFO << "IDS Unsubscribing from portal IDSM" << LOG_NOOP;
    m_subscriber->UnSubscribe();
}
