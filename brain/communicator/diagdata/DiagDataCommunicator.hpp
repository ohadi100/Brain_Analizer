/**
 * @file
 * @brief    This file contains the definition of DiagDataCommunicator.
 */
#ifndef DIAGDATA_COMMUNICATOR_HPP
#define DIAGDATA_COMMUNICATOR_HPP

#include <map>
#include <memory>

#include <rapidjson/document.h>

#include "brain/communicator/Communicator.hpp"
#include "common/utils/types/ConfigurationTypes.hpp"
#include "generated/vwg/services/diagnostic/diagdata/diagdata/diagdata_proxy.h"
#include "generated/vwg/services/diagnostic/diagdata/diagdata/impl_type_resultoptions.h"

namespace brain
{
namespace brain_communicator
{
namespace diagdata_communicator
{

using DiagDataProxy = vwg::services::diagnostic::diagdata::diagdata::proxy::DiagDataProxy;
class DiagDataCommunicator : public Communicator
{
public:
    using ConfigurationPtr = common::configuration::Pointer;
    using NoiseFilterPtr    = std::shared_ptr<brain::brain_noise_filter::SensorNoiseFilter>;

    /**
     * @brief   Ctor. Creates the signal handler, and initializes ara log with a mock logger required for scilib
     * internal usage.
     * @param   queuesManager - queue that manages all sensors, input for Communicator ctor
     * @param   debugCounters - link to debug counters that are used in IDS, input for Communicator ctor
     * @param   flushThreshold - input for Communicator ctor
     * @param   sensorNoiseFilter - noise filter link
     */
    DiagDataCommunicator(SensorDataQueuesManagerPtr queuesManager,
                         uint32_t                   flushThreshold,
                         ConfigurationPtr           config,
                         NoiseFilterPtr             sensorNoiseFilter = nullptr);

    /**
     * @brief   Dtor. Deregisters signal handlers.
     */
    virtual ~DiagDataCommunicator() override;

    /**
     * @brief    default copy constructor
     */
    DiagDataCommunicator(const DiagDataCommunicator& other) = delete;

    /**
     * @brief    default move constructor
     */
    DiagDataCommunicator(DiagDataCommunicator&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    DiagDataCommunicator& operator=(DiagDataCommunicator const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    DiagDataCommunicator& operator=(DiagDataCommunicator&&) = delete;

    /**
     * @brief   Starts the signal handling logic, which parses the configuration and registers m_signalHanlder to handle
     * each signal.
     */
    virtual void Start() override;

    /**
     * @brief   Deregisters the signal handling and resets the parsed signals objects.
     */
    virtual void Stop() override;

#ifndef TESTS
private:
#endif  // TESTS

    /**
     * @brief   find Service and create proxy.
     * @param   DiagDataProxy::HandleType> DiagDataProxy handles 
     * @param   ara::com::FindServiceHandle handles
     */
    void findServiceCallback(ara::com::ServiceHandleContainer<typename DiagDataProxy::HandleType> handles, ara::com::FindServiceHandle /*handle*/);
    /**
     * @brief   sends SOME/IP msg to DiagMaster.
     * @param   DiagDataProxy const& proxyDiagDataService : diagData proxy 
     * @return  bool - true for success otherwise false.
     */
    bool getDiagDataByKeysOnDD(vwg::services::diagnostic::diagdata::diagdata::proxy::DiagDataProxy const& proxyDiagDataService);
    /**
     * @brief   function to parse DiagDataItems json comming from DiagMaster.
     * @param   string const& responseJson : parse diag data items 
     * @return  bool - true for success otherwise false.
     */
    bool parseDiagDataItems(std::string const& responseJson);
    /**
     * @brief   parses Values array in json.
     * @param   rapidjson::Value values: The "Values" array.
     * @return  bool - true for success otherwise false.
     */
    bool parseValuesArray(rapidjson::Value const& values);
    /**
     * @brief   parses Structure array in json.
     * @param   rapidjson::Value structure: The "Structure" array.
     * @return  bool - true for success otherwise false.
     */
    bool parseStructureArray(rapidjson::Value const& structure);

    /**
    * @brief looks for element with specified ParamShortName
    * @param rapidjson::Value element         : rapidjson element that needs to be an array.
    * @param std::string searchParamShortName : ParamShortName that has to be searched for.
    * @return index where the element was found. If nothing was found the size of the array will be returned.
    */
    rapidjson::SizeType getIndex(rapidjson::Value const& element, std::string const& searchParamShortName);
    
    /**
    * @brief genarte Vehicle Type and save it in PM
    * @param std::string const& vehicleID     : vehicle ID from diag data
    * @return bool - true for success otherwise false.
    */
    bool setVehicleType(std::string const& vehicleID);
      
    std::string m_vehicleType;
    std::unique_ptr<ara::com::FindServiceHandle> m_findDiagData;
    std::vector<std::unique_ptr<ara::com::FindServiceHandle>> m_findServiceHandles;
    std::unique_ptr<DiagDataProxy> m_diagDataProxy;
    ConfigurationPtr m_configuration;
};

} /* namespace diagdata_communicator */
} /* namespace brain_communicator */
} /* namespace brain */

#endif /* DIAGDATA_COMMUNICATOR_HPP */
