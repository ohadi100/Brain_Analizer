#include "brain/communicator/periodic/PeriodicReportCommunicator.hpp"
#include "common/sensor_data/SensorDataTypes.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/counter_manager/CounterNames.hpp"

using brain::brain_communicator::periodic::PeriodicReportCommunicator;
using common::sensor_data::PeriodicStatisticsSensorData;
using common::Time;
namespace brain
{
namespace brain_communicator
{
namespace periodic
{
// parasoft-begin-suppress AUTOSAR-M3_4_1-b "This is false positive, this is used in UT, in the same file"
static constexpr char PERIODIC_STATISTICS_SD_TIMER_NAME[]                           = "Periodic Statistics Sensor Data";
// parasoft-end-suppress AUTOSAR-M3_4_1-b
static constexpr PeriodicReportCommunicator::MiliSecondsSinceEpochType INVALID_TIME = 0U;
}  // namespace periodic
}  // namespace brain_communicator
}  // namespace brain


PeriodicReportCommunicator::PeriodicReportCommunicator(SensorDataQueuesManagerPtr queuesManager,
                                                       CounterManagerPtr          debugCounters,
                                                       ConfigurationPtr           config, 
                                                       common::TimerPtr           timer)
  : Communicator(queuesManager, 0U, CommunicatorId::PERIODIC)
  , m_debugCounters(debugCounters)
  , m_config(config)
  , m_registrationKey(common::Timer::INVALID_TIMER_REGISTRATION_KEY)
  , m_statisticsInterval(
        getPeriodicIntervalConfiguration(brain::config_keys::IDS_PERIODIC_STATISTICS_SEND_INTERVAL_SECS))
  , m_timer(timer)
{

    #ifdef TESTS
        m_statisticsInterval = 0U;
    #else
        if(m_statisticsInterval <= MIN_PERIODIC_REPORT_CHECK_INTERVAL)
        {
            m_statisticsInterval = MIN_PERIODIC_REPORT_CHECK_INTERVAL;
        }
    #endif //TESTS

    if (debugCounters)
    {
        m_failedCreatingSDCounter = debugCounters->CreateCounter(common::counters::errors::PERIODIC_REPORT_SD_WAS_NOT_CREATED, EventCounterLevelType::COUNTER_ERROR);
    }
}

void PeriodicReportCommunicator::Start()
{
    if (nullptr == m_timer)
    {
        LOG_ERROR << "[PeriodicReportFlow] Starting periodic report communicator - m_timer is nullptr" << LOG_NOOP;
        return;
    }

    if (0U == m_registrationKey)
    {
        LOG_INFO << "[PeriodicReportFlow] Starting periodic report communicator -  Interval: [" << m_statisticsInterval
                 << "] seconds" << LOG_NOOP;
        m_registrationKey = m_timer->Register(
            common::S_TO_MS(m_statisticsInterval),
            [this]() {
                SendPeriodicSD();
            },
            true);

        if(common::Timer::TIMER_REGISTRATION_KEY_ERROR == m_registrationKey)
        {
            m_registrationKey = 0U;
            LOG_ERROR << "[PeriodicReportFlow] Error - couldn't register timer for periodic report action" << LOG_NOOP;
        }
    }
}

void PeriodicReportCommunicator::Stop()
{
    LOG_INFO << "[PeriodicReportFlow] Stopping periodic report communicator - Deregistering from timer" << LOG_NOOP;

    if (nullptr == m_timer)
    {
        LOG_ERROR << "[PeriodicReportFlow] Stopping periodic report communicator - m_timer is nullptr" << LOG_NOOP;
        return;
    }

    if (0U == m_registrationKey)
    {
        return;
    }

    // TODO - deregister refactor (thread unsafe)
    std::ignore       = m_timer->Deregister(m_registrationKey);
    m_registrationKey = 0U;
}

uint32_t PeriodicReportCommunicator::getPeriodicIntervalConfiguration(ConfigKeyType const& key)
{
    const uint32_t defaultInterval = (key == brain::config_keys::IDS_PERIODIC_STATISTICS_SEND_INTERVAL_SECS) ? DEFAULT_REPORT_SEND_INTERVAL_SECS : DEFAULT_STATISTICS_INTERVAL_SECS;

    if (nullptr == m_config)
    {
        return defaultInterval;
    }

    uint32_t intervalFromConfig = 0U;
    if (!m_config->GetValue(key, intervalFromConfig))
    {
        return defaultInterval;
    }

    return intervalFromConfig;
}


void PeriodicReportCommunicator::SendPeriodicSD()
{
    LOG_DEBUG << "[PeriodicReportFlow] Sending periodic SD - started" << LOG_NOOP;

    if (!Time::IsCurrentTimeValid())
    {
        LOG_ERROR << "[PeriodicReportFlow] Sending periodic SD - No real time is present, can't save statistics"
                  << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedCreatingSDCounter);
        return;
    }

    MiliSecondsSinceEpochType currentTime = Time::GetCurrentTimeMilliSec();
    if (isPeriodicSDCreationNeeded(currentTime, m_statisticsInterval, brain::config_keys::PERIODIC_STATISTICS_PREVIOUS_TS))
    {
        LOG_DEBUG << "[PeriodicReportFlow] Sending periodic SD - Creating periodic statistics SD, current time: ["
                  << currentTime << "]" << LOG_NOOP;
        createPeriodicSD(SensorDataTag::SD_PERIODIC_STATISTICS, PERIODIC_STATISTICS_SD_TIMER_NAME, currentTime, brain::config_keys::PERIODIC_STATISTICS_PREVIOUS_TS);
    }
    else
    {
        common::counters::IncreaseCounter(m_failedCreatingSDCounter);
    }

    LOG_DEBUG << "[PeriodicReportFlow] Sending periodic SD - ended" << LOG_NOOP;
}

#ifdef TESTS
void PeriodicReportCommunicator::ForceSendPeriodicSD()
{
    MiliSecondsSinceEpochType currentTime = Time::GetCurrentTimeMilliSec();
    LOG_DEBUG << "[PeriodicReportFlow] Sending periodic SD - Creating periodic statistics SD, current time: ["
              << currentTime << "]" << LOG_NOOP;
    createPeriodicSD(SensorDataTag::SD_PERIODIC_STATISTICS, PERIODIC_STATISTICS_SD_TIMER_NAME, currentTime, brain::config_keys::PERIODIC_STATISTICS_PREVIOUS_TS);
}
#endif

void
PeriodicReportCommunicator::createPeriodicSD(SensorDataTag             tag,
                                             std::string const&        sdTimerName,
                                             MiliSecondsSinceEpochType currentTime,
                                             ConfigKeyType const&      key)
{
    auto sd = std::make_unique<PeriodicStatisticsSensorData>(sdTimerName.c_str());
    sd->SetTag(tag);

    handle(std::move(sd), 0U);

    if (!storePreviousCreationTime(currentTime, m_config, key))
    {
        LOG_ERROR << "[PeriodicReportFlow] Creating periodic SD - Failed to store periodic time stamp" << LOG_NOOP;
    }
}

PeriodicReportCommunicator::MiliSecondsSinceEpochType
    PeriodicReportCommunicator::getPreviousCreationTime(ConfigurationPtr config, ConfigKeyType const& key)
{
    if (nullptr == config)
    {
        LOG_ERROR
            << "[PeriodicReportFlow] Getting previous creation time of periodic report communicator - config is nullptr"
            << LOG_NOOP;
        return INVALID_TIME;
    }

    MiliSecondsSinceEpochType previousIntervalTime = 0U;
    if (!config->GetValue(key, previousIntervalTime))
    {
        return INVALID_TIME;
    }

    return previousIntervalTime;
}

bool
PeriodicReportCommunicator::storePreviousCreationTime(MiliSecondsSinceEpochType reportCreationTime,
                                                      ConfigurationPtr          config,
                                                      ConfigKeyType const&      key)
{
    if (nullptr == config)
    {
        LOG_ERROR
            << "[PeriodicReportFlow] Storing previous creation time of periodic report communicator - config is nullptr"
            << LOG_NOOP;
        return false;
    }

    return config->SetPersistentValue(key, reportCreationTime, true);
}

bool
PeriodicReportCommunicator::isPeriodicSDCreationNeeded(MiliSecondsSinceEpochType currentTime,
                                                       MiliSecondsSinceEpochType generationInterval,
                                                       ConfigKeyType const&      key)
{
#ifdef TESTS
    if (IgnoreTimer)
        return false;
#endif

    MiliSecondsSinceEpochType previousTs = getPreviousCreationTime(m_config, key);
    if (INVALID_TIME == previousTs)
    {
        LOG_DEBUG << "[PeriodicReportFlow] Checking if periodic SD creation is needed - Previous periodic time stamp "
                     "is not present"
                  << LOG_NOOP;
    }

    LOG_DEBUG << "[PeriodicReportFlow] Checking if periodic SD creation is needed - Creating " << key << " : ["
              << previousTs << "]" << LOG_NOOP;

    if (currentTime <= previousTs)
    {
        return false;
    }

    return (generationInterval <= (currentTime - previousTs));
}

void PeriodicReportCommunicator::SetTimer(common::TimerPtr timer)
{
    if ((nullptr != m_timer) && (0U != m_registrationKey))
    {
        std::ignore       = m_timer->Deregister(m_registrationKey);
        m_registrationKey = 0U;
    }

    m_timer = timer;
}