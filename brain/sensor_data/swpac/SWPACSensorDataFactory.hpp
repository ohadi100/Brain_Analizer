/**
 * @file
 * @brief     A factory for SW-PAC SensorData
*/
#ifndef SWPAC_SENSOR_DATA_FACTORY_HPP
#define SWPAC_SENSOR_DATA_FACTORY_HPP

#include "common/counter_manager/CounterManager.hpp"
#include "common/utils/CPP/optional/Optional.hpp"
#include "common/sensor_data/SensorData.hpp"
#include "common/utils/logger/Logger.hpp"
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "IncidentHelper.hpp"

#include "rapidjson/document.h"
#include <unordered_map>

namespace brain
{
namespace sensor_data
{

using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;

/**
 * @class   SWPACSensorDataFactory
 * @brief   A factory for SensorData
 */
class SWPACSensorDataFactory
{
public:
    using CoreMetaId = std::string;
    using CounterManagerPtr = std::shared_ptr<common::counters::CounterManager>;
    using EventCounterPtr = std::shared_ptr<common::counters::EventCounter>;
    using UPSensorData = common::sensor_data::UPSensorData;
    using UPSensorDataVector = std::vector<UPSensorData>;
    using UPSensorDataVectorPtr = std::shared_ptr<UPSensorDataVector>;
    using DiagnosticsManagerPtr = brain::diagnostics::DiagnosticsManagerInterface::Pointer;
    using ConstraintId = brain::sensor_data::swpac::ConstraintId;

    static void InitCounters(CounterManagerPtr debugCounters);

    /**
     * @brief   Create appropriate SD according to the incident type
     * @param   constrainId = cdhm incident constraint id
     * @param   const char* incident -  the given incident
     * @param   CounterManagerPtr debugCounters
     * @return  UPSensorDataVectorPtr - SD
     */
    static UPSensorDataVectorPtr CreateSD(ConstraintId& constraintId,
                                          char const*           incident,
                                          DiagnosticsManagerPtr diagnosticsManager);

private:
    
    SWPACSensorDataFactory() = delete;

    static void getCoreMetaId(std::string const& reference, std::string& metaId);
    static void getMetaId(std::string& metaId);
    
    static UPSensorData defineEventType(rapidjson::Document&  incidentJson,
                                        ConstraintId&         constraintId,
                                        DiagnosticsManagerPtr diagnosticsManager);
    static UPSensorData sdByType(sensor_data::swpac::IncidentType type,
                                 sensor_data::swpac::ConstraintId constraintId,
                                 rapidjson::Value const&          dataItemsJson,
                                 DiagnosticsManagerPtr            diagnosticsManager);

    static EventCounterPtr m_tLSErrorReportSdCreatedCounter;
    static EventCounterPtr m_kernelLogKernelPanicSdCreatedCounter;
    static EventCounterPtr m_processPerformanceSdCreatedCounter;
};

} // namespace sensor_data
} // namespace brain

#endif // SWPAC_SENSOR_DATA_FACTORY_HPP
