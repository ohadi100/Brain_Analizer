/**
 * @file
 * @brief     The IdsProxyCommunicator is a class that contains code of brain recieving data from the IDS Proxy
 */
#ifndef IDS_IMMOBILIZER_COMMUNICATOR
#define IDS_IMMOBILIZER_COMMUNICATOR

// Includes from "generated" folder that is placed under 'brain' during environmentr preparation
#include "vwg/services/immobilizer/immobilizer_common.h"
#include "vwg/services/immobilizer/immobilizer_proxy.h"

#include "legacySomeIPCommunicator.hpp"


namespace brain
{
namespace brain_communicator
{
namespace someip
{
namespace ids_Immobilizer_communicator
{

// Naming colition - first Proxy is the Ids service, second Proxy means a data recieving interface
using IdsimmobilizerProxy = vwg::services::immobilizer::proxy::ImmobilizerProxy;

class IdsImmobilizerCommunicator : public legacySomeIPCommunicator<IdsimmobilizerProxy>
{
public:
public:
    /**
     * @fn      CoreDumpCommunicator()
     * @brief   Ctor
     * @return  none
     */
    IdsImmobilizerCommunicator(Communicator::SensorDataQueuesManagerPtr queuesManager,
                               Communicator::NoiseFilterPtr             noiseFilters,
                               uint32_t const                           flushThreshold)
      : legacySomeIPCommunicator(
          "IDS_Immobilizer", queuesManager, noiseFilters, flushThreshold, CommunicatorId::IMMOBILIZER)
    {
    }

    /**
     * @fn      virtual ~CoreDumpCommunicator()
     * @brief   Dtor
     * @return  none
     */
    virtual ~IdsImmobilizerCommunicator(){};

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

}  // namespace ids_Immobilizer_communicator
}  // namespace someip
}  // namespace brain_communicator
}  // namespace brain

#endif  // IDS_IMMOBILIZER_COMMUNICATOR
