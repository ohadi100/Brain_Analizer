/**
 * @file
 * @brief     The IdsEthCommunicator is a class that contains code of brain recieving data from the IDS ETH sensors
 */
#ifndef IDS_ETH_COMMUNICATOR
#define IDS_ETH_COMMUNICATOR

// Includes from "generated" folder that is placed under 'brain' during environmentr preparation
#include "vwg/services/idsethernetsensor/idsethernetsensor_common.h"
#include "vwg/services/idsethernetsensor/idsethernetsensor_proxy.h"

#include "legacySomeIPCommunicator.hpp"


namespace brain
{
namespace brain_communicator
{
namespace someip
{
namespace ids_eth_communicator
{

// Naming colition - first Proxy is the Ids service, second Proxy means a data recieving interface
using IdsEthProxy                = vwg::services::idsethernetsensor::proxy::IDSEthernetSensorProxy;
using IdsEthPortStatisticsData   = vwg::services::idsethernetsensor::datatypes::DT_portStatistics_struct;
using IdsEthSpecialFrameData     = vwg::services::idsethernetsensor::datatypes::DT_specialFrameReports_struct;
using IdsEthServiceDiscoveryData = vwg::services::idsethernetsensor::datatypes::DT_serviceDiscoveryReports_struct;
using IdsEthTrafficFlowData      = vwg::services::idsethernetsensor::datatypes::DT_trafficFlowSamples_struct;

class IdsEthCommunicator : public legacySomeIPCommunicator<IdsEthProxy>
{
public:
public:
    /**
     * @fn      CoreDumpCommunicator()
     * @brief   Ctor
     * @return  none
     */
    IdsEthCommunicator(Communicator::SensorDataQueuesManagerPtr queuesManager,
                       Communicator::NoiseFilterPtr             noiseFilters,
                       uint32_t const                           flushThreshold)
      : legacySomeIPCommunicator("IdsEthCommunicator", queuesManager, noiseFilters, flushThreshold, CommunicatorId::ETH)
    {
    }

    /**
     * @fn      virtual ~CoreDumpCommunicator()
     * @brief   Dtor
     * @return  none
     */
    virtual ~IdsEthCommunicator(){};

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

}  // namespace ids_eth_communicator
}  // namespace someip
}  // namespace brain_communicator
}  // namespace brain

#endif  // IDS_ETH_COMMUNICATOR
