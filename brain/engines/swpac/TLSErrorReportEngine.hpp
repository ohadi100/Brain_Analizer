/**
 * @file
 * @brief     A rule engine for the TLS Error Sensor
 */
#ifndef TLS_ERROR_REPORT_ENGINE_HPP
#define TLS_ERROR_REPORT_ENGINE_HPP

#include "TLSErrorReportSensorData.hpp"
#include "SwpacEngineBase.hpp"

namespace brain
{
namespace engines
{
namespace swpac
{

class IncidentCounterTable;

using common::sensor_data::UPSensorData;

/**
 * @class   TLSErrorReportEngine
 * @brief   The TLSErrorReportEngine analyzes a TlsErrorReporting sensor data.
 */
class TLSErrorReportEngine : public SwpacEngineBase
{
public:
    using EventCounter       = common::counters::EventCounter;

    /**
     * @brief   Constructor
     * @param   CounterManagerPtr debugCounters
     * @param   msgRepository for communicate with sender manager sender.
     * @param   EventNoiseFilterPtr eventNoiseFilter
     * @param   reportSerializer - class to serialize idsperiodicreport proto object
     * @param   EventPriority priority
     */
    TLSErrorReportEngine(CounterManagerPtr                                 debugCounters,
                         MessageRepositoryPtr                              msgRepository,
                         EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                         EventNoiseFilterPtr                               eventNoiseFilter,
                         events::EventPriority                             priority = events::EventPriority::Important);

private:
    bool       sendAlert(brain::sensor_data::TLSErrorReportSensorData const& sd);
    ReturnCode processInternal(UPSensorData sd) override;

    EventCounterPtr m_failedCounter;
    EventCounterPtr m_alertSendCounter;
};

}  // namespace swpac
}  // namespace engines
}  // namespace brain

#endif  // TLS_ERROR_REPORT_ENGINE_HPP
