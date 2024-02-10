#include "IdsProxyRelayCommunicator.hpp"

namespace brain
{
namespace brain_communicator
{
namespace someip
{
namespace ids_proxy_communicator
{

void IdsProxyRelayCommunicator::RegisterService()
{
    RegisterSomeIP(m_proxy->relayFeedbackPDU, m_communicatorName);
}

void IdsProxyRelayCommunicator::DeregisterService()
{
    DeregisterSomeIp(m_proxy->relayFeedbackPDU);
}


} // namespace ids_proxy_communicator
} // namespace someip
} // namespace brain_communicator
} // namespace brain
