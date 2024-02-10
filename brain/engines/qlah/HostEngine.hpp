/**
 * @file
 * @brief     A rule engine for the Host QLAH Sensor
*/
#ifndef HOST_ENGINE_HPP
#define HOST_ENGINE_HPP

#include "brain/noise_filter/event_noise_filter/EventNoiseFilter.hpp"
#include "brain/engines/Engine.hpp"
#include "brain/engines/EngineEventSender.hpp"
#include "common/counter_manager/CounterManager.hpp"

namespace brain
{
namespace engines
{
namespace qlah
{

using common::sensor_data::UPSensorData;

/**
 * @class   HostEngine
 * @brief   The HostEngine analyzes a host sensor data of qlah sensors.
 */
class HostEngine
  : public Engine
  , public EngineEventSender
{
public:
    using CounterManagerPtr = common::counters::CounterManagerPtr;
    using EventCounter = common::counters::EventCounter;
    using EventCounterWithTs = common::counters::EventCounterWithTs;
    using EventNoiseFilterPtr = std::shared_ptr<brain::brain_noise_filter::EventNoiseFilter>;
    using EventCounterPtr = std::shared_ptr<common::counters::EventCounter>;

    /**
     * @brief   Constructor
     * @param   CounterManagerPtr debugCounters
     * @param   msgRepository for communication with sender manager sender
     * @param   reportSerializer - class to serialize idsperiodicreport proto object
     * @param   EventNoiseFilterPtr eventNoiseFilter
     * @param   EventPriority priority
     */
    HostEngine(CounterManagerPtr                                 debugCounters,
               MessageRepositoryPtr                              msgRepository,
               EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
               EventNoiseFilterPtr                               eventNoiseFilter,
               events::EventPriority                             priority = events::EventPriority::Important);

    /**
     * @brief   Get the counter's value.
     * @return  uint64_t - counter's value.
     */
    inline uint64_t GetUartAliveSignalMissingCounter() const noexcept
    {
        return m_uartAliveSignalMissingCounter->GetEventCounter();
    }

    /**
     * @brief   Get the uart alive signal missing first seen timestamp.
     * @return  uint64_t - the timestamp's value.
     */
    inline uint64_t GetUartAliveSignalMissingFirstSeenTimestamp() const noexcept
    {
        return m_uartAliveSignalMissingCounter->GetFirstSeenTimeStamp();
    }

    /**
     * @brief   Get the uart alive signal missing last seen timestamp.
     * @return  uint64_t - the timestamp's value.
     */
    inline uint64_t GetUartAliveSignalMissingLastSeenTimestamp() const noexcept
    {
        return m_uartAliveSignalMissingCounter->GetLastSeenTimeStamp();
    }

    /**
     * @brief   Get the counter's value.
     * @return  uint64_t - counter's value.
     */
    inline uint64_t GetAuthenticationErrorCounter() const noexcept
    {
        return m_authenticationErrorCounter->GetEventCounter();
    }

    /**
     * @brief   Get the authentication error first seen timestamp.
     * @return  uint64_t - the timestamp's value.
     */
    inline uint64_t GetAuthenticationErrorFirstSeenTimestamp() const noexcept
    {
        return m_authenticationErrorCounter->GetFirstSeenTimeStamp();
    }

    /**
     * @brief   Get the authentication error last seen timestamp.
     * @return  uint64_t - the timestamp's value.
     */
    inline uint64_t GetAuthenticationErrorLastSeenTimestamp() const noexcept
    {
        return m_authenticationErrorCounter->GetLastSeenTimeStamp();
    }

    /**
     * @brief   Clears the histogram and the counters contents.
     */
    void ClearContents() noexcept;

protected:

    ReturnCode processInternal(UPSensorData sd) override;
    bool createRuleEvaluation(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval);

private:
    void parseFailedSgn1(com_vwg_connect_ids_idsperiodicreport_v1_UPFirewallSignatureFailureAlert& buffer, uint16_t failedSgn1) noexcept;
    void parseFailedSgn2(com_vwg_connect_ids_idsperiodicreport_v1_UCFirewallSignatureFailureAlert& buffer, uint16_t failedSgn2) noexcept;
    void parseCpuErrors(com_vwg_connect_ids_idsperiodicreport_v1_UCHWFailureAlert& buffer, uint16_t cpuErrors) noexcept;
    void createHostErrorMonitoringReport(com_vwg_connect_ids_idsperiodicreport_v1_HostErrorMonitoringReport& hostErrorMonitoringReport);

#ifndef HCP5_PLATFORM
    static void printEvent(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval);
#endif //!HCP5_PLATFORM

    EventCounterPtr m_failedCounter;
    EventCounterPtr m_createdEventCounter;
    EventCounterPtr m_beganProcessingCounter;

    std::shared_ptr<EventCounterWithTs> m_uartAliveSignalMissingCounter;
    std::shared_ptr<EventCounterWithTs> m_authenticationErrorCounter;
    
    EventCounterPtr m_microProcessorSignatureFailureCounter;
    EventCounterPtr m_microControllerSignatureFailureCounter;
    EventCounterPtr m_microControllerHardwareFailureCounter;

    //errors bits
    uint16_t m_failedSgn1{};
    uint16_t m_failedSgn2{};
    uint16_t m_cpuErrors{};
    uint64_t m_timeStamp{0UL};
};

} // namespace qlah
} // namespace engines
} // namespace brain

#endif // HOST_ENGINE_HPP
