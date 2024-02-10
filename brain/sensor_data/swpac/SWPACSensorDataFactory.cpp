/**
 * @file
 * @brief     code for SWPACSensorDataFactory
 */
#include "SWPACSensorDataFactory.hpp"
#include "ProcessPerformanceSensorData.hpp"
#include "brain/diagnostics/PPE/AdaptationValuesConstants.hpp"
#include "brain/engines/swpac/UnknownConstraintEngine.hpp"
#include "brain/sensor_data/swpac/KernelLogSensorData.hpp"
#include "brain/sensor_data/swpac/TLSErrorReportSensorData.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/sensor_data/SensorDataTags.hpp"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using brain::engines::swpac::UnknownConstraintEngine;
using brain::sensor_data::SWPACSensorDataFactory;
using common::sensor_data::SensorDataTag;
using namespace common::sensor_data;
using brain::sensor_data::swpac::ConstraintIdMap;
using brain::sensor_data::swpac::ConstraintId;
using brain::sensor_data::swpac::EventsTypes;
using brain::sensor_data::swpac::IncidentType;

std::shared_ptr<common::counters::EventCounter> SWPACSensorDataFactory::m_tLSErrorReportSdCreatedCounter;
std::shared_ptr<common::counters::EventCounter> SWPACSensorDataFactory::m_kernelLogKernelPanicSdCreatedCounter;
std::shared_ptr<common::counters::EventCounter> SWPACSensorDataFactory::m_processPerformanceSdCreatedCounter;

void
SWPACSensorDataFactory::getCoreMetaId(std::string const& reference, std::string& metaId)
{
    // for example for reference: "dacq/92d58a6e-4860-409c-9566-31cdb52a80e6/0f6ef590-4395-49c8-8a8e-317ca3976e31"
    // the metaid will equal "92d58a6e-4860-409c-9566-31cdb52a80e6"
    constexpr uint8_t META_ID_LENGTH              = 36U;
    constexpr uint8_t PREFIX_CORE_META_ID_END_POS = 5U;
    if (reference.size() > PREFIX_CORE_META_ID_END_POS)
    {
        metaId = reference.substr(PREFIX_CORE_META_ID_END_POS, META_ID_LENGTH);
    }
    else
    {
        LOG_WARNING << "Size of the reference = " << reference << " is smaller than " << PREFIX_CORE_META_ID_END_POS
                    << LOG_NOOP;
    }
}

void
SWPACSensorDataFactory::getMetaId(std::string& metaId)
{
    // for example for reference: "dacq/92d58a6e-4860-409c-9566-31cdb52a80e6/0f6ef590-4395-49c8-8a8e-317ca3976e31"
    // the metaid will equal "0f6ef590-4395-49c8-8a8e-317ca3976e31"
    constexpr uint8_t PREFIX_META_ID_END_POS = 42U;
    if (metaId.size() > PREFIX_META_ID_END_POS)
    {
        std::ignore = metaId.erase(0U, PREFIX_META_ID_END_POS);
    }
    else
    {
        LOG_WARNING << "Size of the metaId = " << metaId << " is smaller than " << PREFIX_META_ID_END_POS << LOG_NOOP;
    }
}
void
SWPACSensorDataFactory::InitCounters(CounterManagerPtr debugCounters)
{
    if (debugCounters)
    {
        m_tLSErrorReportSdCreatedCounter = debugCounters->CreateCounter(
            common::counters::debug::TLS_ERROR_REPORT_SD_WAS_CREATED, EventCounterLevelType::COUNTER_DEBUG);
        m_kernelLogKernelPanicSdCreatedCounter = debugCounters->CreateCounter(
            common::counters::debug::KERNEL_LOG_KERNEL_PANIC_SD_WAS_CREATED, EventCounterLevelType::COUNTER_DEBUG);
        m_processPerformanceSdCreatedCounter = debugCounters->CreateCounter(
            common::counters::debug::PROCESS_PERFORMANCE_SD_WAS_CREATED, EventCounterLevelType::COUNTER_DEBUG);
    }
}

SWPACSensorDataFactory::UPSensorDataVectorPtr
SWPACSensorDataFactory::CreateSD(ConstraintId&         constraintId,
                                 char const*           incident,
                                 DiagnosticsManagerPtr diagnosticsManager)
{
    rapidjson::Document incidentJson;

    if (incidentJson.Parse(incident).HasParseError())
    {
        LOG_WARNING << "Creating SD for SWPAC sensors - rapidjson failed to parse the incident - [" << incident << "]"
                    << LOG_NOOP;
        return std::shared_ptr<UPSensorDataVector>();
    }

    // The following data is taken from examples of real incidents
    if ((!incidentJson.HasMember("additional info")) || (!incidentJson["additional info"].HasMember("dataSets"))
        || (incidentJson["additional info"]["dataSets"].Size() == 0U)
        || !incidentJson["additional info"]["dataSets"].IsArray())
    {
        LOG_WARNING << "Creating SD for SWPAC sensors - Received an incident in an unacceptable form - [" << incident
                    << "]" << LOG_NOOP;
        return std::shared_ptr<UPSensorDataVector>();
    }

    UPSensorData sd = defineEventType(incidentJson, constraintId, diagnosticsManager);
    if (!sd)
    {
        LOG_WARNING << "Creating SD for SWPAC sensors - SD was not created successfully - [" << incident << "]"
                    << LOG_NOOP;
        return std::shared_ptr<UPSensorDataVector>();
    }

    UPSensorDataVectorPtr sdVector = std::make_shared<UPSensorDataVector>();
    sdVector->emplace_back(std::move(sd));

    return sdVector;
}

UPSensorData
SWPACSensorDataFactory::defineEventType(rapidjson::Document&  incidentJson,
                                        ConstraintId&         constraintId,
                                        DiagnosticsManagerPtr diagnosticsManager)
{
    ConstraintId typeConstraintId = ConstraintId::UNDEFINED_CONSTRAINTID;

    auto const& constraintIdIt = incidentJson.FindMember("constraintId");
    std::string constraintIdString;
    
    if (incidentJson.MemberEnd() != constraintIdIt && constraintIdIt->value.IsString())
    {
        constraintIdString = constraintIdIt->value.GetString();
        auto const& idItr = ConstraintIdMap.find(constraintIdString);
        if (idItr != ConstraintIdMap.end())
        {
            typeConstraintId = idItr->second;
        }
    }

    if (ConstraintId::UNDEFINED_CONSTRAINTID == typeConstraintId)
    {
        rapidjson::StringBuffer                    buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        incidentJson.Accept(writer);

        UnknownConstraintEngine::sendAlertExt(constraintIdString, buffer.GetString());
        return {};
    }

    constraintId = typeConstraintId;

    std::string                          coreMeta;
    auto const&                          dataSets = incidentJson["additional info"]["dataSets"];
    rapidjson::Value::ConstValueIterator setItr   = dataSets.Begin();
    for (; setItr != dataSets.End(); ++setItr)
    {
        auto const& dataItemsIt = setItr->FindMember("dataItems");
        if ((setItr->MemberEnd() != dataItemsIt) && dataItemsIt->value.IsArray() && (dataItemsIt->value.Size() > 0U))
        {
            auto const& dataItemsValue = dataItemsIt->value[0U];
            auto const& referenceIt    = dataItemsValue.FindMember("reference");
            if (dataItemsValue.MemberEnd() != referenceIt && referenceIt->value.IsString())
            {
                std::string const& reference = (*setItr)["dataItems"][0U]["reference"].GetString();
                getCoreMetaId(reference, coreMeta);

                auto const& typeItr = EventsTypes.find(coreMeta);
                if (typeItr != EventsTypes.end())
                {
                    IncidentType const& type = typeItr->second;
                    return sdByType(type, typeConstraintId, dataItemsIt->value, diagnosticsManager);
                }
            }
        }
    }

    LOG_WARNING << "Creating SD for SWPAC sensors - Failed to create SD from incident - unknown type coreMetaId - "
                << coreMeta << LOG_NOOP;
    return {};
}

UPSensorData
SWPACSensorDataFactory::sdByType(IncidentType            type,
                                 ConstraintId            constraintId,
                                 rapidjson::Value const& dataItemsJson,
                                 DiagnosticsManagerPtr   diagnosticsManager)
{
    UPSensorData sd;
    bool         success{false};

    LOG_DEBUG << "Parsing incident " << static_cast<uint16_t>(type) << " and constraint "
              << static_cast<uint16_t>(constraintId) << LOG_NOOP;

    switch (type)
    {
    case IncidentType::KERNEL_LOG:
        // Diag Adaptations - 0x7704 - OSmonitoringOn
        if (!diagnosticsManager
            || !diagnosticsManager->GetFeatureFlag(brain::adaptation_values_names::AdaptationId::OS_MONITORING_ON))
        {
            break;
        }

        sd = std::make_unique<brain::sensor_data::KernelLogSensorData>(success, dataItemsJson, constraintId);
        if (!success)
        {
            sd.reset();
            break;
        }

        LOG_DEBUG << "Created KernelLogSensorData" << LOG_NOOP;
        sd->SetTag(SensorDataTag::SD_SWPAC_KERNEL_LOG);
        
        common::counters::IncreaseCounter(m_kernelLogKernelPanicSdCreatedCounter);
        break;

    case IncidentType::TLS_ERROR_REPORTING:
        // Diag Adaptations - 0x7704 - TLSsessionsmonitoringOn
        if (!diagnosticsManager
            && !diagnosticsManager->GetFeatureFlag(
                brain::adaptation_values_names::AdaptationId::TLS_SESSIONS_MONITORING_ON))
        {
            break;
        }

        sd = std::make_unique<brain::sensor_data::TLSErrorReportSensorData>(success, dataItemsJson, constraintId);
        if (!success)
        {
            sd.reset();
            break;
        }

        LOG_DEBUG << "Created TLSErrorReportSensorData" << LOG_NOOP;
        sd->SetTag(SensorDataTag::SD_SWPAC_TLS_ERROR_REPORT);
        common::counters::IncreaseCounter(m_tLSErrorReportSdCreatedCounter);
        break;
    case IncidentType::PROCESS_PERFORMANCE:
        if (ConstraintId::PROCESS_PERFORMANCE != constraintId)
        {
            LOG_WARNING << "Unsupported Process Performance constraintId" << LOG_NOOP;
            break;
        }

        sd = std::make_unique<brain::sensor_data::ProcessPerformanceSensorData>(success, dataItemsJson, constraintId);
        if (!success)
        {
            sd.reset();
            break;
        }

        LOG_DEBUG << "Created Process Performance Monitoring Data" << LOG_NOOP;
        sd->SetTag(SensorDataTag::SD_SWPAC_PROCESS_PERFORMANCE_REPORT);
        common::counters::IncreaseCounter(m_processPerformanceSdCreatedCounter);
        break;
    default:
        LOG_WARNING << "Currently we do not support event of type - " << static_cast<int>(type) << LOG_NOOP;
    }

    return sd;
}
