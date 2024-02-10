#include "IdsImmobilizerCommunicator.hpp"

namespace brain
{
namespace brain_communicator
{
namespace someip
{
namespace ids_Immobilizer_communicator
{

void IdsImmobilizerCommunicator::RegisterService()
{
    RegisterSomeIP(m_proxy->info, m_communicatorName);
}

void IdsImmobilizerCommunicator::DeregisterService()
{
    DeregisterSomeIp(m_proxy->info);
}


} // namespace ids_Immobilizer_communicator
} // namespace someip
} // namespace brain_communicator
} // namespace brain
