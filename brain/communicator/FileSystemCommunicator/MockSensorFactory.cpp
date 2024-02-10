#include "MockSensorFactory.hpp"
#include "autogen/gsep/ParsedEventIds.hpp"
#include "brain/engines/PPE/PeriodicStatisticsEngine.hpp"
#include "brain/engines/security_events/SecurityEventsEngine.hpp"
#include "brain/engines/swpac/KernelLogEngine.hpp"
#include "brain/engines/swpac/ProcessPerformanceEngine.hpp"
#include "brain/engines/swpac/TLSErrorReportEngine.hpp"
#include "brain/sensor_data/security_events/SecurityEventSensorData.hpp"
#include "brain/sensor_data/swpac/SWPACSensorDataFactory.hpp"
#include "brain/utils/UtilsConstants.hpp"
#include "common/sensor_data/SensorDataTypes.hpp"
#include "common/utils/logger/Logger.hpp"
#include "common/utils/timer/Timer.hpp"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/impl_type_securityeventevent.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/impl_type_securityeventtype.h"

using namespace brain::engines::security_events;
using brain::sensor_data::SecurityEventSensorData;
using common::sensor_data::SensorDataTag;
using SecurityEventDataType = vwg::services::security::idssecurityevent::idssecurityevent::SecurityEventEvent;
using brain::sensor_data::swpac::ConstraintId;


namespace common
{

template <typename T>
T
optionalGetUInt(rapidjson::Document const& data,
                const char*                fieldName,
                T                          defaultValue = {})
{
    return (data.HasMember(fieldName) ? static_cast<T>(data[fieldName].GetUint()) : defaultValue);
}

template <typename T>
T
optionalGetUInt(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>> const& data,
                const char*                                                                       fieldName,
                T defaultValue = {})
{
    return (data.HasMember(fieldName) ? static_cast<T>(data[fieldName].GetUint()) : defaultValue);
}

SecurityEventTimestamp
uintToSecurityEventTimestamp(uint64_t timestamp)
{
    SecurityEventTimestamp eventTimestamp;
    eventTimestamp.inspection.source = eventTimestamp.source_AutoSAR;
    eventTimestamp.autosar.seconds   = static_cast<uint32_t>(common::MS_TO_S(timestamp));
    eventTimestamp.autosar.nano
        = static_cast<uint32_t>((timestamp % common::MILLISECONDS_IN_SECOND) * common::NANOSECONDS_IN_MILLISECOND)
          & 0x3FFFFFFF;

    return eventTimestamp;
}

void
jsonArrayToByteArray(rapidjson::GenericValue<rapidjson::UTF8<>> const& data, uint8_t* byteArray, size_t length)
{
    size_t currentLength{0U};
    for (auto& var : data.GetArray())
    {
        if (++currentLength < length)
        {
            byteArray[currentLength - 1] = static_cast<uint8_t>(var.GetUint());
        }
        else
        {
            break;
        }
    }
}

void
ipAddressToByteArray(rapidjson::GenericValue<rapidjson::UTF8<>> const&    data,
                     union brain::engines::security_events::SECEV_ipaddr& input)
{
    size_t currentCnt{0U};
    auto   inputPtr = reinterpret_cast<uint8_t*>(&input);

    for (auto& var : data.GetArray())
    {
        uint8_t val{static_cast<uint8_t>(var.GetUint())};
        memcpy(reinterpret_cast<void*>(inputPtr + currentCnt), reinterpret_cast<void*>(&val), sizeof(uint8_t));
        currentCnt++;
    }
}


template <typename EVENT_STRUCT>
static std::vector<uint8_t>
ConvertToContextData(EVENT_STRUCT* event)
{
    brain::engines::security_events::SECEV_Convert(event);
    auto it = reinterpret_cast<uint8_t const*>(event);
    return std::vector<uint8_t>(it, it + sizeof(*event));
}

SecurityEventFrame
CreateSecurityEventFrame(uint16_t const eventId,
                         bool const     enabledTimestamp,
                         bool const     enabledContextData,
                         uint8_t        sensorInstanceID,
                         uint16_t       idsMInstanceID,
                         uint16_t       count)
{
    SecurityEventFrame securityEventFrame{};
    securityEventFrame.eventDefinitionId = eventId;

    securityEventFrame.sensorInstanceID = (sensorInstanceID & 0x3F);
    securityEventFrame.idsMInstanceID   = (idsMInstanceID & 0x3FF);

    securityEventFrame.protocolHeaderTimestamp   = enabledTimestamp ? 1U : 0U;
    securityEventFrame.protocolHeaderContextData = enabledContextData ? 1U : 0U;

    securityEventFrame.count = count;

    SECEV_Convert(&securityEventFrame);

    return securityEventFrame;
}

SecurityEventTimestamp
CreateSecurityEventTimestamp(uint64_t timestamp)
{
    auto eventTimestamp = uintToSecurityEventTimestamp(timestamp);

    SECEV_Convert(&eventTimestamp);

    return eventTimestamp;
}

SecurityEventDataType
CreateSecurityEventSomeIpStruct(uint16_t const              eventId,
                                std::vector<uint8_t> const& contextData,
                                uint8_t                     sensorInstanceID = 0U,
                                uint16_t                    idsMInstanceID   = 0U)
{
    static uint16_t       eventFrameCount{0U};
    SecurityEventDataType securityEvent{};
    uint64_t const        timestamp{common::Time::GetCurrentTimeMilliSec()};

    // Set event id
    SecurityEventFrame eventFrame
        = CreateSecurityEventFrame(eventId, true, true, sensorInstanceID, idsMInstanceID, eventFrameCount++);
    std::array<uint8_t, sizeof(SecurityEventFrame)> eventFrameArray
        = *reinterpret_cast<std::array<uint8_t, sizeof(SecurityEventFrame)>*>(&eventFrame);
    securityEvent.element.eventFrame = eventFrameArray;

    // Set timestamp
    SecurityEventTimestamp                              eventTimestamp = CreateSecurityEventTimestamp(timestamp);
    std::array<uint8_t, sizeof(SecurityEventTimestamp)> eventTimestampArray
        = *reinterpret_cast<std::array<uint8_t, sizeof(SecurityEventTimestamp)>*>(&eventTimestamp);
    securityEvent.element.timestamp = eventTimestampArray;

    securityEvent.element.contextData = contextData;

    return securityEvent;
}

MockSensorFactory::MockSensorFactory(std::vector<std::shared_ptr<brain::engines::Engine>> const& sensorsMap,
                                     DiagnosticsManagerPtr                                       diagManager)
  : m_sensorsMap(sensorsMap)
  , m_diagnosticsManager{diagManager}
{
}

bool
MockSensorFactory::CreateAndSendSensorData(rapidjson::Document const& jsonObj)
{
    const std::string& tag = jsonObj.HasMember("tag") ? jsonObj["tag"].GetString() : "";
    bool               rc{false};

    LOG_INFO << "sensor data of type: " << tag << " created from json and send to queue" << LOG_NOOP;

    if ("SD_SECURITY_EVENT" == tag)
    {
        common::sensor_data::UPSensorData sd = CreateSecurityEventSensoData(jsonObj);
        if (nullptr == sd)
        {
            LOG_ERROR << "No sensor data created from json" << LOG_NOOP;
        }
        else
        {
            if (static_cast<size_t>(SensorDataTag::SD_SECURITY_EVENT) < m_sensorsMap.size())
            {
                const auto sensor = std::dynamic_pointer_cast<brain::engines::security_events::SecurityEventsEngine>(
                    m_sensorsMap[static_cast<uint32_t>(SensorDataTag::SD_SECURITY_EVENT)]);
                if (nullptr != sensor)
                {
                    sensor->Process(std::move(sd));
                    rc = true;
                }
            }
        }
    }
    else if ("SD_PERIODIC_STATISTICS" == tag)
    {
        if (static_cast<size_t>(SensorDataTag::SD_PERIODIC_STATISTICS) < m_sensorsMap.size())
        {
            const auto sensor = std::dynamic_pointer_cast<brain::engines::PeriodicStatisticsEngine>(
                m_sensorsMap[static_cast<uint32_t>(SensorDataTag::SD_PERIODIC_STATISTICS)]);
            if (nullptr != sensor)
            {
                std::string timerName{jsonObj.HasMember("timerName") ? jsonObj["timerName"].GetString() : ""};

                auto sd = std::make_unique<common::sensor_data::PeriodicStatisticsSensorData>(timerName.c_str());
                sd->SetTag(SensorDataTag::SD_PERIODIC_STATISTICS);

                sensor->Process(std::move(sd));
                rc = true;
            }
        }
    }
    else if ("SD_SWPAC_KERNEL_LOG" == tag)
    {
        if (static_cast<size_t>(SensorDataTag::SD_SWPAC_KERNEL_LOG) < m_sensorsMap.size())
        {
            const auto sensor = std::dynamic_pointer_cast<brain::engines::swpac::KernelLogEngine>(
                m_sensorsMap[static_cast<uint32_t>(SensorDataTag::SD_SWPAC_KERNEL_LOG)]);

            if (nullptr != sensor)
            {
                auto const& dataIt = jsonObj.FindMember("data");
                if (jsonObj.MemberEnd() != dataIt)
                {
                    auto sd = std::make_unique<brain::sensor_data::KernelLogSensorData>(rc, dataIt->value);
                    sd->SetTag(SensorDataTag::SD_SWPAC_KERNEL_LOG);
                    sensor->Process(std::move(sd));
                }
            }
        }
    }
    else if ("SD_SWPAC_TLS_ERROR_REPORT" == tag)
    {
        if (static_cast<size_t>(SensorDataTag::SD_SWPAC_TLS_ERROR_REPORT) < m_sensorsMap.size())
        {
            const auto sensor = std::dynamic_pointer_cast<brain::engines::swpac::TLSErrorReportEngine>(
                m_sensorsMap[static_cast<uint32_t>(SensorDataTag::SD_SWPAC_TLS_ERROR_REPORT)]);

            if (nullptr != sensor)
            {
                auto const& dataIt = jsonObj.FindMember("data");
                if (jsonObj.MemberEnd() != dataIt)
                {
                    auto sd = std::make_unique<brain::sensor_data::TLSErrorReportSensorData>(rc, dataIt->value);
                    sd->SetTag(SensorDataTag::SD_SWPAC_TLS_ERROR_REPORT);
                    sensor->Process(std::move(sd));
                }
            }
        }
    }
    else if ("SD_SWPAC_PROCESS_PERFORMANCE_REPORT" == tag)
    {
        if (static_cast<size_t>(SensorDataTag::SD_SWPAC_PROCESS_PERFORMANCE_REPORT) < m_sensorsMap.size())
        {
            const auto sensor = std::dynamic_pointer_cast<brain::engines::swpac::ProcessPerformanceEngine>(
                m_sensorsMap[static_cast<uint32_t>(SensorDataTag::SD_SWPAC_PROCESS_PERFORMANCE_REPORT)]);

            if (nullptr != sensor)
            {
                auto const& dataIt = jsonObj.FindMember("data");
                if (jsonObj.MemberEnd() != dataIt)
                {
                    auto sd = std::make_unique<brain::sensor_data::ProcessPerformanceSensorData>(rc, dataIt->value);
                    sd->SetTag(SensorDataTag::SD_SWPAC_PROCESS_PERFORMANCE_REPORT);
                    sensor->Process(std::move(sd));
                }
            }
        }
    }
    else if ("SD_DHM" == tag)
    {
        auto const& dataIt = jsonObj.FindMember("data");
        if (jsonObj.MemberEnd() != dataIt && dataIt->value.IsObject())
        {
            const rapidjson::Value& dataObject = dataIt->value;

            rapidjson::StringBuffer                    buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            dataObject.Accept(writer);

            ConstraintId constrainId{ConstraintId::UNDEFINED_CONSTRAINTID};
            brain::sensor_data::SWPACSensorDataFactory::CreateSD(constrainId, buffer.GetString(), m_diagnosticsManager);
        }
    }

    return rc;
}

common::sensor_data::UPSensorData
MockSensorFactory::CreateSecurityEventSensoData(rapidjson::Document const& jsonObj)
{
    common::sensor_data::UPSensorData sensorData;
    std::stringstream                 idString;
    uint16_t                          eventId{};

    idString << std::hex << jsonObj["eventId"].GetString();
    idString >> eventId;

    LOG_INFO << "CreateSecurityEventSensoData: received security events " << eventId << LOG_NOOP;


    uint8_t  sensorInstanceID = optionalGetUInt<uint8_t>(jsonObj, "sensorInstanceID");
    uint16_t idsMInstanceID   = optionalGetUInt<uint16_t>(jsonObj, "idsMInstanceID");

    switch (eventId)
    {
    case EventIds::MESSAGE_BURST: {
        SECEV_MESSAGE_BURST event{};

        if (jsonObj.HasMember("data"))
        {
            auto data                          = jsonObj["data"].GetObject();
            event.length.normal.dataLength     = sizeof(event) - sizeof(event.length);
            event.uid                          = optionalGetUInt<uint32_t>(data, "uid") & 0xFFFFFFU;
            event.successBit                   = optionalGetUInt<uint8_t>(data, "successBit");
            event.busId                        = optionalGetUInt<uint8_t>(data, "busId");
            event.burstMonitoringTime          = optionalGetUInt<uint16_t>(data, "burstMonitoringTime");
            event.messagePerTimeUnitThreshold  = optionalGetUInt<uint16_t>(data, "messagePerTimeUnitThreshold");
            event.communicationAttemptedsCount = optionalGetUInt<uint32_t>(data, "communicationAttemptedsCount") & 0xFFFFFFU;
            event.busType                      = optionalGetUInt<uint8_t>(data, "busType");
            if (data.HasMember("sourceIpAddress"))
            {
                ipAddressToByteArray(data["sourceIpAddress"], event.sourceIpAddress);
            }

            if (data.HasMember("destinationIpAddress"))
            {
                ipAddressToByteArray(data["destinationIpAddress"], event.destinationIpAddress);
            }

            strcpy(event.transportProtocol,
                   data.HasMember("transportProtocol") ? data["transportProtocol"].GetString() : "");
            event.sourcePortRequest      = optionalGetUInt<uint32_t>(data, "sourcePortRequest");
            event.destinationPortRequest = optionalGetUInt<uint32_t>(data, "destinationPortRequest");
            event.messagesPerReferenceIntervalCount
                = optionalGetUInt<uint16_t>(data, "messagesPerReferenceIntervalCount");
            event.timeReferenceInterval = optionalGetUInt<uint16_t>(data, "timeReferenceInterval");

            if (data.HasMember("messagePayloadSize"))
            {
                jsonArrayToByteArray(data["messagePayloadSize"], event.messagePayloadSize, 64);
            }
        }

        bool sdCreateSuccess{};
        auto contextData = ConvertToContextData(&event);

        sensorData = std::make_unique<SecurityEventSensorData>(
            CreateSecurityEventSomeIpStruct(eventId, contextData, sensorInstanceID, idsMInstanceID), sdCreateSuccess);
        break;
    }
    case EventIds::EXTERNAL_CONNECTION_INTERFACE_UNSUCCESSFUL: {
        SECEV_EXTERNAL_CONNECTION_INTERFACE_UNSUCCESSFUL event{};

        if (jsonObj.HasMember("data"))
        {
            auto data                        = jsonObj["data"].GetObject();
            event.length.normal.dataLength   = sizeof(event) - sizeof(event.length);
            event.uid                        = optionalGetUInt<uint32_t>(data, "uid") & 0xFFFFFFU;
            event.successBit                 = optionalGetUInt<uint8_t>(data, "successBit");
            event.connectionType             = optionalGetUInt<uint8_t>(data, "connectionType");
            event.connectingUnitAddress      = optionalGetUInt<uint64_t>(data, "connectingUnitAddress") & 0xFFFFFFFFFFFF;
            event.reasonForConnectionRefusal = optionalGetUInt<uint32_t>(data, "reasonForConnectionRefusal");
            strcpy(event.connectionUnitDeviceName,
                   data.HasMember("connectionUnitDeviceName") ? data["connectionUnitDeviceName"].GetString() : "");
        }

        bool sdCreateSuccess{};
        auto contextData = ConvertToContextData(&event);

        sensorData = std::make_unique<SecurityEventSensorData>(
            CreateSecurityEventSomeIpStruct(eventId, contextData, sensorInstanceID, idsMInstanceID), sdCreateSuccess);
        break;
    }
    case EventIds::PROCESS_CRASH_NOTIFICATION: {
        SECEV_PROCESS_CRASH_NOTIFICATION event{};

        if (jsonObj.HasMember("data"))
        {
            auto data                      = jsonObj["data"].GetObject();
            event.length.normal.dataLength = sizeof(event) - sizeof(event.length);
            event.uid                      = optionalGetUInt<uint32_t>(data, "uid") & 0xFFFFFFU;
            ;
            event.successBit   = optionalGetUInt<uint8_t>(data, "successBit");
            event.dtcDfcc      = optionalGetUInt<uint32_t>(data, "dtcDfcc") & 0xFFFFFFU;
            event.dtcTi        = optionalGetUInt<uint32_t>(data, "dtcTi") & 0xFFFFFFU;
            event.vmIdentifier = optionalGetUInt<uint8_t>(data, "vmIdentifier");
            event.processDriverApplicationLibraryId
                = optionalGetUInt<uint32_t>(data, "processDriverApplicationLibraryId") & 0xFFFFFFU;
            strcpy(event.processDriverApplicationLibrary,
                   data.HasMember("processDriverApplicationLibrary")
                       ? data["processDriverApplicationLibrary"].GetString()
                       : "");
            event.processState                  = optionalGetUInt<uint8_t>(data, "processState");
            event.typeOfError                   = optionalGetUInt<uint16_t>(data, "typeOfError");
            event.crashReason                   = optionalGetUInt<uint8_t>(data, "crashReason");
            event.additionalInformationLength   = optionalGetUInt<uint32_t>(data, "additionalInformationLength");
            event.additionalInformationPerError = optionalGetUInt<uint16_t>(data, "additionalInformationPerError");
        }

        bool sdCreateSuccess{};
        auto contextData = ConvertToContextData(&event);

        sensorData = std::make_unique<SecurityEventSensorData>(
            CreateSecurityEventSomeIpStruct(eventId, contextData, sensorInstanceID, idsMInstanceID), sdCreateSuccess);
        break;
    }
    default:
        sensorData = std::unique_ptr<common::sensor_data::SensorData>(nullptr);
    }

    return sensorData;
}

}  // namespace common