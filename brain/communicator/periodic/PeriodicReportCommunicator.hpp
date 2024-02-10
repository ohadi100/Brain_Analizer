/**
 * @file
 * @brief     This file contains the definition of the PeriodicReportCommunicator class and its functionality
 */
#ifndef PERIODIC_REPORT_COMMUNICATOR_HPP
#define PERIODIC_REPORT_COMMUNICATOR_HPP

#include "brain/communicator/Communicator.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "common/sensor_data/SensorDataTags.hpp"
#include "common/utils/timer/Timer.hpp"
#include "common/utils/types/ConfigurationTypes.hpp"

using brain::config_keys::ConfigKeyType;
using common::sensor_data::SensorDataTag;

namespace brain
{
namespace brain_communicator
{
namespace periodic
{

/**
 * @class   PeriodicReportCommunicator
 * @brief   Class that implements communicator that is using timer to execute periodic callbacks.
 */
class PeriodicReportCommunicator : public brain::brain_communicator::Communicator
{
public:
    static constexpr uint32_t DEFAULT_REPORT_SEND_INTERVAL_SECS  = 43200;  // 12 hours
    static constexpr uint32_t DEFAULT_STATISTICS_INTERVAL_SECS   = 3600;   // 1 hour
    static constexpr uint32_t MIN_PERIODIC_REPORT_CHECK_INTERVAL = 120;    // 2 minutes

    using ConfigurationPtr          = common::configuration::Pointer;
    using MiliSecondsSinceEpochType = uint64_t;
    using CounterManagerPtr         = std::shared_ptr<common::counters::CounterManager>;
    using EventCounterLevelType     = common::counters::EventCounter::EventCounterLevelType;

    /**
     * @brief   Constructor
     * @param   SensorDataQueuesManagerPtr  queuesManager
     * @param   CounterManagerPtr debugCounters,
     * @param   ConfigurationPtr config - config
     * @param   TimerPtr timer for communicator activation
     */
    PeriodicReportCommunicator(SensorDataQueuesManagerPtr queuesManager,
                               CounterManagerPtr          debugCounters,
                               ConfigurationPtr           config,
                               common::TimerPtr           timer);

    /**
     * @brief   Destructor
     */
    virtual ~PeriodicReportCommunicator() = default;

    /**
     * @brief    default copy constructor
     */
    PeriodicReportCommunicator(const PeriodicReportCommunicator& other) = delete;

    /**
     * @brief    default move constructor
     */
    PeriodicReportCommunicator(PeriodicReportCommunicator&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    PeriodicReportCommunicator& operator=(PeriodicReportCommunicator const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    PeriodicReportCommunicator& operator=(PeriodicReportCommunicator&&) = delete;

    /**
     * @brief   Start sending periodic SDs continuously. The communicator will continue to run till Stop() is called
     */
    virtual void Start() override;

    /**
     * @brief   Stops the communicator and stops sending periodic SDs. Call Start to rerun the communicator after Stop
     * was called
     */
    virtual void Stop() override;

    /**
     * @brief   Create periodic SD and send it.
     */
    void SendPeriodicSD();

#ifdef TESTS
    void ForceSendPeriodicSD();
    bool IgnoreTimer = false;
#endif

    void SetTimer(common::TimerPtr timer);

protected:
    uint32_t getPeriodicIntervalConfiguration(ConfigKeyType const& key);

    MiliSecondsSinceEpochType getPreviousCreationTime(ConfigurationPtr config, ConfigKeyType const& key);

    uint32_t getPeriodicGracePeriod();

    bool storePreviousCreationTime(MiliSecondsSinceEpochType reportCreationTime,
                                   ConfigurationPtr          config,
                                   ConfigKeyType const&      key);

    bool isPeriodicSDCreationNeeded(MiliSecondsSinceEpochType currentTime,
                                    MiliSecondsSinceEpochType generationInterval,
                                    ConfigKeyType const&      key);

    void createPeriodicSD(SensorDataTag             tag,
                          std::string const&        sdTimerName,
                          MiliSecondsSinceEpochType currentTime,
                          ConfigKeyType const&      key);

    // counters
    CounterManagerPtr             m_debugCounters;
    std::shared_ptr<EventCounter> m_failedCreatingSDCounter;

    ConfigurationPtr                m_config;
    common::Timer::TimerRegisterKey m_registrationKey;
    size_t                          m_statisticsInterval;
    common::TimerPtr                        m_timer;
};

}  // namespace periodic
}  // namespace brain_communicator
}  // namespace brain

#endif  // PERIODIC_REPORT_COMMUNICATOR_HPP
