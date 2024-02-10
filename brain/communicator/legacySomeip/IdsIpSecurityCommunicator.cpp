#include "IdsIpSecurityCommunicator.hpp"

namespace brain
{
namespace brain_communicator
{
namespace someip
{
namespace ids_ipsecurity_communicator
{

void IdsIpSecurityCommunicator::RegisterService()
{
    RegisterSomeIP(m_proxy->firewallFilterReports, m_communicatorName);
}

void IdsIpSecurityCommunicator::DeregisterService()
{
    DeregisterSomeIp(m_proxy->firewallFilterReports);
}


} // namespace ids_ipsecurity_communicator
} // namespace someip
} // namespace brain_communicator
} // namespace brain
