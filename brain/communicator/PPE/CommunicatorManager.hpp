#pragma once
/**
 * @file
 * @brief     code for Brain's Communicator Manager
*/

#include "brain/communicator/Communicator.hpp"
#include "brain/communicator/CommunicatorManagerBase.hpp"
#include "common/configuration/Configuration.hpp"
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"

namespace common
{
    namespace counters
    {
        class CounterManager;
    }
    
    namespace notification_handler
    {
        class SensorDataQueuesManager;
    }
}

namespace brain
{
namespace brain_communicator
{
       
/**
 * @class   CommunicatorManager for PPE platform
 * @brief   Responsible for all the sensor communicators
 */
class CommunicatorManager : public CommunicatorManagerBase, public common::utils::Nonassignable
{
    using SensorDataQueuesManagerPtr = std::shared_ptr<common::notification_handler::SensorDataQueuesManager>;
    using NoiseFilterPtr             = std::shared_ptr<brain::brain_noise_filter::NoiseFilter>;
    using ConfigurationPtr           = common::configuration::Pointer;
    using CounterManagerPtr          = std::shared_ptr<common::counters::CounterManager>;
    using UPCommunicator             = std::unique_ptr<brain::brain_communicator::Communicator>;
    using TimerPtr                   = std::shared_ptr<common::Timer>;
    using DiagnosticsManagerPtr      = std::shared_ptr<brain::diagnostics::DiagnosticsManagerInterface>;

public:
    /**
     * @brief Constructs a CommunicatorManager from given queues manager, configuration, debug counters, timer, and diagnostics manager.
     *
     * @param queuesManager      Queues manager for sensor data
     * @param config             General configuration
     * @param debugCounters      Counters used for debug purposes
     * @param timer              A timer
     * @param diagnosticsManager Manager object for diagnostics data
     */
    CommunicatorManager(
        SensorDataQueuesManagerPtr queuesManager,
        ConfigurationPtr config,
        CounterManagerPtr debugCounters,
        TimerPtr timer,
        DiagnosticsManagerPtr diagnosticsManager);

    void RegisterAllNotificationHandlers() override;

#ifndef TESTS
private:
#endif //TESTS
    SensorDataQueuesManagerPtr m_queuesManager;
	
    ConfigurationPtr m_configuration;

    CounterManagerPtr m_debugCounters;

    DiagnosticsManagerPtr m_diagManager;

    TimerPtr m_timer;
    common::Timer::TimerRegisterKey m_someipTimerKey;

#ifdef EEE_PLATFORM
    void setPeriodicSomeIPHandling(uint64_t const interval);
    void getNewSomeipSamples();

#endif // EEE_PLATFORM
};

} // namespace brain_communicator
} // namespace brain

