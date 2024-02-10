/**
 * @file
 * @brief     The IdsProxyCommunicator is a class that contains code of brain recieving data from the IDS Proxy
 */
#ifndef IDS_PROXY_COMMUNICATOR
#define IDS_PROXY_COMMUNICATOR

// Includes from "generated" folder that is placed under 'brain' during environmentr preparation
#include "vwg/services/idsbrainproxyrelay/idsbrainproxyrelay_common.h"
#include "vwg/services/idsbrainproxyrelay/idsbrainproxyrelay_proxy.h"

#include "legacySomeIPCommunicator.hpp"


namespace brain
{
namespace brain_communicator
{
namespace someip
{
namespace ids_proxy_communicator
{

// Naming colition - first Proxy is the Ids service, second Proxy means a data recieving interface
using IdsProxyRelayProxy        = vwg::services::idsbrainproxyrelay::proxy::IDSBrainProxyRelayProxy;
using IdsProxyRelayNotification = vwg::services::idsbrainproxyrelay::proxy::fields::relayFeedbackPDU;
using IdsProxyRelayData         = vwg::services::idsbrainproxyrelay::datatypes::DT_relayFeedbackPDU_struct;

class IdsProxyRelayCommunicator : public legacySomeIPCommunicator<IdsProxyRelayProxy>
{
public:
public:
    /**
     * @fn      CoreDumpCommunicator()
     * @brief   Ctor
     * @return  none
     */
    IdsProxyRelayCommunicator(Communicator::SensorDataQueuesManagerPtr queuesManager,
                              Communicator::NoiseFilterPtr             noiseFilters,
                              uint32_t const                           flushThreshold)
      : legacySomeIPCommunicator(
          "IdsProxyRelayCommunicator", queuesManager, noiseFilters, flushThreshold, CommunicatorId::PROXY_RELAY)
    {
    }


    /**
     * @fn      virtual ~CoreDumpCommunicator()
     * @brief   Dtor
     * @return  none
     */
    virtual ~IdsProxyRelayCommunicator(){};

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

}  // namespace ids_proxy_communicator
}  // namespace someip
}  // namespace brain_communicator
}  // namespace brain

#endif  // IDS_PROXY_COMMUNICATOR
