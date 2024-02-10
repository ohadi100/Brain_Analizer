#include "IdsEthCommunicator.hpp"

namespace brain
{
namespace brain_communicator
{
namespace someip
{
namespace ids_eth_communicator
{

void IdsEthCommunicator::RegisterService()
{
    RegisterSomeIP(m_proxy->specialFrameReports, m_communicatorName);
    RegisterSomeIP(m_proxy->portStatistics, m_communicatorName);
    RegisterSomeIP(m_proxy->serviceDiscoveryReports, m_communicatorName);
    RegisterSomeIP(m_proxy->trafficFlowSamples, m_communicatorName);
}

void IdsEthCommunicator::DeregisterService()
{
    DeregisterSomeIp(m_proxy->specialFrameReports);
    DeregisterSomeIp(m_proxy->portStatistics);
    DeregisterSomeIp(m_proxy->serviceDiscoveryReports);
    DeregisterSomeIp(m_proxy->trafficFlowSamples);
}

} // namespace ids_eth_communicator
} // namespace someip
} // namespace brain_communicator
} // namespace brain
