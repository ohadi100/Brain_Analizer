#include "IdsSecurityEventCommunicator.hpp"

namespace brain
{
namespace brain_communicator
{
namespace someip
{
namespace ids_security_event_communicator
{

void IdsSecurityEventCommunicator::RegisterService()
{
    RegisterSomeIP(m_proxy->securityEvent, m_communicatorName);
}

void IdsSecurityEventCommunicator::DeregisterService()
{
    DeregisterSomeIp(m_proxy->securityEvent);
}


} // namespace ids_security_event_communicator
} // namespace someip
} // namespace brain_communicator
} // namespace brain
