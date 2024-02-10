/**
 * @file
 * @brief     This file contains the functionality of the DiagDataCommunicator class
 */
#include "DiagDataCommunicator.hpp"
#include <chrono>
#include "brain/config/BrainConfigConstants.hpp"
#include "brain/sensor_data/security_events/SecurityEventSensorData.hpp"
#include "common/utils/logger/Logger.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "brain/config/BrainConfigConstants.hpp"

#include <chrono>

#define WMI_POSITION 0
#define WMI_LENGTH 3
#define VIN_CLASS_LENGTH 2
#define VIN_CLASS_POSITION 6
#define MODEL_YEAR_POSITION 9

using brain::brain_communicator::diagdata_communicator::DiagDataCommunicator;

DiagDataCommunicator::DiagDataCommunicator(SensorDataQueuesManagerPtr queuesManager,
                                           uint32_t                   flushThreshold,
                                           ConfigurationPtr           config,
                                           NoiseFilterPtr             sensorNoiseFilter)
  : Communicator(queuesManager, flushThreshold, CommunicatorId::DIAG_DATA, sensorNoiseFilter)
  , m_configuration(config)
{
}

DiagDataCommunicator::~DiagDataCommunicator()
{
    try
    {
        Stop();
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "destruction of the DiagDataCommunicator failed and got exception." << LOG_NOOP;
    }  // only for parasoft violations
}

void DiagDataCommunicator::Stop()
{
    LOG_INFO << "Deregistering DiagData handling" << LOG_NOOP;
    m_diagDataProxy.reset();
}

void DiagDataCommunicator::findServiceCallback(ara::com::ServiceHandleContainer<typename DiagDataProxy::HandleType> handles, ara::com::FindServiceHandle /*handle*/)
{
    if (handles.empty())
    {
        LOG_INFO << "Service callback found 0 handles communicator Id is : " << static_cast<uint32_t>(m_communicatorId)
                 << LOG_NOOP;  // The log means the IDS didn't find the service (ECU with some IP communication)
        return;
    }

    for (auto & handleCopy : handles)
    {
        LOG_INFO << "FindServiceHandle callback identified new handle: instance_id ["
                 << handleCopy.GetInstanceId().toString().data() << "]" << LOG_NOOP;
        m_diagDataProxy = std::make_unique<DiagDataProxy>(handleCopy);
        try
        {
            if (!getDiagDataByKeysOnDD(*m_diagDataProxy))
            {
                LOG_INFO << "invalid VIN vehicle Type is empty, mock VT will created before sending to BE" << LOG_NOOP;
            }
        }
        // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
        catch (const std::exception& e)
        // parasoft-end-suppress AUTOSAR-A15_3_4-a
        {
            LOG_ERROR << "FindServiceHandle callback failed at proxy initialization: " << e.what() << LOG_NOOP;
        }

        LOG_INFO << "findServiceCallback registering instanceId = " << handleCopy.GetInstanceId().toString()
                 << LOG_NOOP;
    }
}


bool DiagDataCommunicator::getDiagDataByKeysOnDD(
    vwg::services::diagnostic::diagdata::diagdata::proxy::DiagDataProxy const& proxyDiagDataService)
{
    ara::stdtypes::String accessID{"Access1"};
    vwg::services::diagnostic::diagdata::diagdata::getDiagDataByKeys_diagDataKeys diagDataKeys;
        diagDataKeys.push_back("LL_GatewUDS/"
                                "DiagnServi_ReadDataByIdentECUIdent."
                                "Param_RecorDataIdent."
                                "Vehicle Identification Number");

    ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions resultOptionsInterpretedValue;
    resultOptionsInterpretedValue.resultFormat = vwg::services::diagnostic::diagdata::diagdata::ResultFormat::
        interpretedValue;

    resultOptionsInterpretedValue.content = vwg::services::diagnostic::diagdata::diagdata::Content::valueInformation; 

    using namespace std::chrono_literals;
    constexpr ara::stdtypes::UInt32 kTimeoutInMs{500U};
    LOG_DEBUG << "call getDiagDataByKeys API" << LOG_NOOP;
    ac::core::Future<vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagDataByKeys::Output,
                     ac::core::Error_code>
        out{proxyDiagDataService.getDiagDataByKeys(
            accessID, diagDataKeys, resultOptionsInterpretedValue, kTimeoutInMs)};   

    constexpr std::size_t kTotalMillisecondsToTimeout{5000U};
    constexpr std::size_t kTimeoutPeriodMs{100U};
    std::uint32_t         timeoutCtr = 0U;

    while (ac::core::future_status::ready != out.wait_for(std::chrono::milliseconds(kTimeoutPeriodMs))) 
    {
        timeoutCtr++;
        if ((timeoutCtr * kTimeoutPeriodMs) >= kTotalMillisecondsToTimeout) 
        {
            LOG_DEBUG << " DiagMaster status not ready, reached timeout. Activation failed" << LOG_NOOP;
            return false;
        }
    }

    ac::core::Result<vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagDataByKeys::Output,
                     ac::core::Error_code> const res{out.GetResult()};                                                              

    if (res.HasValue()) 
    {
        vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagDataByKeys::Output value{res.Value()};

        if (vwg::services::diagnostic::diagdata::diagdata::ReturnStatus::success == value.returnStatus) 
        {
            LOG_DEBUG << "Received DiagDataItems successful!" << LOG_NOOP;
            std::string const diagDataItems{std::string(value.diagDataItems.begin(), value.diagDataItems.end())};

            if(!parseDiagDataItems(diagDataItems))
            {
                return false;           
            }
        }
        else 
        {
            LOG_DEBUG << "DiagMaster returned with negative status." << LOG_NOOP;
            return false; 
        }
    }
    else 
    {
        LOG_DEBUG << "Result has no valid data. -> No activation" << LOG_NOOP;
        return false; 
    }
    return true;
}

bool DiagDataCommunicator::parseDiagDataItems(std::string const& responseJson)
{
    LOG_DEBUG << "Parse diagdata items and extract VIN." << LOG_NOOP;

    rapidjson::Document jsonDocument{};
    std::ignore = jsonDocument.Parse(responseJson.c_str());
    if (!jsonDocument.IsObject()) 
    {
        LOG_DEBUG << "Error not a valid json object" << LOG_NOOP;
        return false;
    }

    if (!jsonDocument.HasMember("DiagnosticData")) 
    {
        LOG_DEBUG << "Error no Member DiagnosticData" << LOG_NOOP;
        return false;
    }

    rapidjson::Value const& diagnosticData{jsonDocument["DiagnosticData"]};
    if (!diagnosticData.IsArray()) 
    {
        LOG_DEBUG << "Error diagnosticData is not an array" << LOG_NOOP;
        return false;
    }

    if (!diagnosticData[0U].HasMember("DataObjects")) 
    {
        LOG_DEBUG << "Error no Member DataObjects" << LOG_NOOP;
        return false;
    }

    rapidjson::Value const& dataObjects{diagnosticData[0U]["DataObjects"]};
    if (!dataObjects.IsArray()) 
    {
        LOG_DEBUG << "Error DataObjects is not an array" << LOG_NOOP;
        return false;
    }

    if (!dataObjects[0U].HasMember("Values")) 
    {
        LOG_DEBUG << "Error no Member Values" << LOG_NOOP;
        return false;
    }

    rapidjson::Value const& values{dataObjects[0U]["Values"]};
    return parseValuesArray(values);
}

bool DiagDataCommunicator::parseValuesArray(rapidjson::Value const& values)
{
    if (!values.IsArray()) 
    {
        LOG_DEBUG << "Error Values is not an array" << LOG_NOOP;
        return false;
    }
    rapidjson::SizeType const indexOfDataRecord{getIndex(values, "Param_DataRecor")};

    if (indexOfDataRecord == values.Size()) 
    {
        LOG_DEBUG << "Param_DataRecor not found" << LOG_NOOP;
        return false;
    }

    if (!values[indexOfDataRecord].HasMember("Structure"))
    {
        return false;
    }

    return parseStructureArray(values[indexOfDataRecord]["Structure"]);
}

bool
DiagDataCommunicator::parseStructureArray(rapidjson::Value const& structure)
{
    if (!structure.IsArray()) 
    {
        LOG_DEBUG << "Error Values are not an array" << LOG_NOOP;
        return false;
    }

    rapidjson::SizeType const indexOfSfdToken{getIndex(structure, "Param_VehicIdentNumbe")};

    if (structure.Size() == indexOfSfdToken) 
    {
        LOG_DEBUG << "Could not find Param_VehicIdentNumbe in Structure." << LOG_NOOP;
        return false;
    }

    if (!structure[indexOfSfdToken].HasMember("Value")) 
    {
        LOG_DEBUG << "Could not find Value." << LOG_NOOP;
        return false;
    }
    if (!structure[indexOfSfdToken]["Value"].IsString()) 
    {
        return false;
    }
    std::string const value{structure[indexOfSfdToken]["Value"].GetString()};
    return setVehicleType(value);
}

rapidjson::SizeType
DiagDataCommunicator::getIndex(rapidjson::Value const& element, std::string const& searchParamShortName)
{
    rapidjson::SizeType const sizeOfArray{element.Size()};
    for (rapidjson::SizeType i{0U}; i < sizeOfArray; i++) 
    {
        if (element[i].HasMember("ParamShortName") && 
        element[i]["ParamShortName"].IsString() && 
        (searchParamShortName == element[i]["ParamShortName"].GetString())) 
        {
            return i;
        }
    }

    return sizeOfArray;
}


//create vehicle type based on system req
bool DiagDataCommunicator::setVehicleType(std::string const& vehicleID)
{

    
    if(MODEL_YEAR_POSITION <= vehicleID.size())
    {
        auto vehicleType = vehicleID.substr(WMI_POSITION, WMI_LENGTH); // adding WMI
        vehicleType += vehicleID.substr(VIN_CLASS_POSITION, VIN_CLASS_LENGTH); // adding VIN class
        vehicleType += vehicleID[MODEL_YEAR_POSITION]; // adding model year
        m_vehicleType = vehicleType;
    }
    else
    {
        LOG_DEBUG << "The vehicle ID is too short Vehicle Type not created!" << LOG_NOOP;
        return false;
    }

    #ifndef TESTS
    if(!m_configuration->SetPersistentValue(brain::config_keys::VEHICLE_TYPE,m_vehicleType))
    {
        LOG_DEBUG << "PersistentValue failed Vehicle Type not created!" << LOG_NOOP;
        return false;
    }
    m_configuration->SavePersistent();

    #endif  // TESTS

    LOG_INFO << "m_configuration set Vehicle Type" << LOG_NOOP;
    LOG_DEBUG << "m_configuration set Vehicle Type is: " << m_vehicleType << LOG_NOOP;
    return true;
}


void
DiagDataCommunicator::Start()
{
    LOG_DEBUG << "Start DiagDataCommunicator" << LOG_NOOP;
    if (!(m_findServiceHandles.empty()))
    {
        LOG_ERROR << "Proxies/handlers still exist, has DiagDataCommunicator already started?" << LOG_NOOP;
        return;
    }

    m_findServiceHandles.emplace_back(std::make_unique<ara::com::FindServiceHandle>(DiagDataProxy::StartFindService(
        std::bind(&DiagDataCommunicator::findServiceCallback, this, std::placeholders::_1, std::placeholders::_2))));
}
