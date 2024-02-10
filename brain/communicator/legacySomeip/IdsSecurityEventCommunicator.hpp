/**
 * @file
 * @brief     The IdsSecurityEventCommunicator is a class that contains code of brain recieving data from the IDS
 * SecurityEvent sensor
 */
#ifndef IDS_SECURITY_EVENT_COMMUNICATOR
#define IDS_SECURITY_EVENT_COMMUNICATOR

// Includes from "generated" folder that is placed under 'brain' during environmentr preparation
#include "vwg/services/idssecurityevent/idssecurityevent_common.h"
#include "vwg/services/idssecurityevent/idssecurityevent_proxy.h"

#include "legacySomeIPCommunicator.hpp"


namespace brain
{
namespace brain_communicator
{
namespace someip
{
namespace ids_security_event_communicator
{

// Naming colition - first Proxy is the Ids service, second Proxy means a data recieving interface
using IdsSecurityEventProxy = vwg::services::idssecurityevent::proxy::IDSSecurityEventProxy;


class IdsSecurityEventCommunicator : public legacySomeIPCommunicator<IdsSecurityEventProxy>
{
public:
public:
    /**
     * @fn      CoreDumpCommunicator()
     * @brief   Ctor
     * @return  none
     */
    IdsSecurityEventCommunicator(Communicator::SensorDataQueuesManagerPtr queuesManager,
                                 Communicator::NoiseFilterPtr             noiseFilters,
                                 uint32_t const                           flushThreshold)
      : legacySomeIPCommunicator(
          "IdsSecurityEventCommunicator", queuesManager, noiseFilters, flushThreshold, CommunicatorId::SECURITY_EVENT)
    {
    }

    /**
     * @fn      virtual ~CoreDumpCommunicator()
     * @brief   Dtor
     * @return  none
     */
    virtual ~IdsSecurityEventCommunicator(){};

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

}  // namespace ids_security_event_communicator
}  // namespace someip
}  // namespace brain_communicator
}  // namespace brain

#endif  // IDS_SECURITY_EVENT_COMMUNICATOR
