/**
 * @file
 * @brief     The IdsIpSecurityCommunicator is a class that contains code of brain recieving data from the IDS Proxy
 */
#ifndef IDS_IP_SECURITY_COMMUNICATOR
#define IDS_IP_SECURITY_COMMUNICATOR

// Includes from "generated" folder that is placed under 'brain' during environmentr preparation
#include "vwg/services/idsipsecuritysensor/idsipsecuritysensor_common.h"
#include "vwg/services/idsipsecuritysensor/idsipsecuritysensor_proxy.h"

#include "legacySomeIPCommunicator.hpp"


namespace brain
{
namespace brain_communicator
{
namespace someip
{
namespace ids_ipsecurity_communicator
{

// Naming colition - first Proxy is the Ids service, second Proxy means a data recieving interface
using IdsIpSecurityProxy = vwg::services::idsipsecuritysensor::proxy::IDSIpSecuritySensorProxy;

class IdsIpSecurityCommunicator : public legacySomeIPCommunicator<IdsIpSecurityProxy>
{
public:
public:
    /**
     * @fn      CoreDumpCommunicator()
     * @brief   Ctor
     * @return  none
     */
    IdsIpSecurityCommunicator(Communicator::SensorDataQueuesManagerPtr queuesManager,
                              Communicator::NoiseFilterPtr             noiseFilters,
                              uint32_t const                           flushThreshold)
      : legacySomeIPCommunicator(
          "IdsIpSecurityCommunicator", queuesManager, noiseFilters, flushThreshold, CommunicatorId::IP_SECURITY)
    {
    }

    /**
     * @fn      virtual ~CoreDumpCommunicator()
     * @brief   Dtor
     * @return  none
     */
    virtual ~IdsIpSecurityCommunicator(){};

    /**
     * @fn      RegisterService
     * @brief   Regsiter some ip service with specific hanle for getting core dump data
     */
    void RegisterService() override;

    /**
     * @fn      DeregisterService
     * @brief   Deregsiter some ip service with specific hanle for getting core dump data
     */
    void DeregisterService() override;
};

}  // namespace ids_ipsecurity_communicator
}  // namespace someip
}  // namespace brain_communicator
}  // namespace brain

#endif  // IDS_IP_SECURITY_COMMUNICATOR
