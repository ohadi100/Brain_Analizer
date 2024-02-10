/**
 * @file
 * @brief     A rule engine for the Kernel Log Sensor
 */
#ifndef KERNEL_LOG_ENGINE_HPP
#define KERNEL_LOG_ENGINE_HPP

#include "SwpacEngineBase.hpp"
#include "brain/sensor_data/swpac/KernelLogSensorData.hpp"
#include "common/counter_manager/CounterManager.hpp"

namespace brain
{
namespace engines
{
namespace swpac
{

class IncidentCounterTable;

using common::sensor_data::UPSensorData;

/**
 * @class   KernelLogEngine
 * @brief   The KernelLogEngine analyzes a KernelLog sensor data.
 */
class KernelLogEngine : public SwpacEngineBase
{
public:
    using EventCounter = common::counters::EventCounter;

    /**
     * @brief   Constructor
     * @param   debugCounters debug counter object
     * @param   msgRepository for communicate with sender manager sender
     * @param   reportSerializer - class to serialize idsperiodicreport proto object
     * @param   eventNoiseFilter noise filter
     */
    KernelLogEngine(CounterManagerPtr                                 debugCounters,
                    MessageRepositoryPtr                              msgRepository,
                    EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                    EventNoiseFilterPtr                               eventNoiseFilter,
                    events::EventPriority                             priority = events::EventPriority::Important);

private:
    bool       sendAlert(brain::sensor_data::KernelLogSensorData const& sd);
    ReturnCode processInternal(UPSensorData sd) override;

    EventCounterPtr m_failedCounter;
    EventCounterPtr m_alertSendCounter;
};

}  // namespace swpac
}  // namespace engines
}  // namespace brain

#endif  // KERNEL_LOG_ENGINE_HPP
