#include "BrainApp.hpp" // Implemented

#include "brain/utils/UtilsConstants.hpp"
#include "sender/publishers/utils/message_size_check/ExceededMessageSizeCheck.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include <DBNames.hpp>
#include <interface/PersistentMemoryManagerBuilder.hpp>
#include <factory/PersistentMemoryFactory.hpp>
#include "watchdog/PersistentMemoryWatchdog.hpp"
#include "common/notification_handler/DataArrivedEvent.hpp"
#include "common/thread_handler/ThreadNamesConstants.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/counter_manager/CounterLogger.hpp"
#include "common/utils/GUID/GUID.hpp"
#include "brain/engines/CriticalAlertFilter.hpp"
#include <sys/prctl.h>
#include <tuple>

#if defined (SIMULATION)
#include "brain/internal_player/InternalPlayer.hpp"
#endif //defined (SIMULATION)

#ifdef TESTS
#include "unit/brain/sensor_data/swpac/SWPACTestConstants.hpp"
#endif //TESTS

// TODO remove compilation flags IDSPPE-2779
#if !defined(HTTPS_PUBLISHER)
    #include <ac/com/runtime.hpp> // Required for GDCAgent's CommonLarge skeleton initialization
#endif

#if !defined(HTTPS_PUBLISHER) || (defined(TESTS) && !defined(SSP_PLATFORM_TEST))
#include "brain/sender/publishers/GDC_12/GDCPublisher.hpp"
#else //!defined(HTTPS_PUBLISHER) || (defined(TESTS) && !defined(SSP_PLATFORM_TEST))
#include "brain/sender/publishers/https_publisher/HTTPSPublisher.hpp"
#endif //!defined(HTTPS_PUBLISHER) || (defined(TESTS) && !defined(SSP_PLATFORM_TEST))

#if defined(SSP_PLATFORM) || defined(SSP_PLATFORM_TEST) || defined(SSP_SIMULATION)
#include "brain/communicator/SSP/CommunicatorManager.hpp"
#include "diagnostics/SSP/DiagnosticsManager.hpp"
#include "brain/engines/SSP/EngineDispatcher.hpp"
#else //defined(SSP_PLATFORM) || defined(SSP_PLATFORM_TEST) || defined(SSP_SIMULATION)
#include "brain/engines/PPE/EngineDispatcher.hpp"
#include "brain/communicator/PPE/CommunicatorManager.hpp"
#include "diagnostics/PPE/DiagnosticsManager.hpp"

#include "brain/sender/EventsStorage.hpp"
#include "brain/events/Event.hpp"
#include "brain/events/EventPriority.hpp"
#include "brain/messageRepository/MessageRepositoryPriorityQueue.hpp"
#include "brain/sender/BELogicSM.hpp"
#include "brain/sender/Creditor.hpp"
#include "brain/sender/publishers/interface/PublisherInterface.hpp"
#include "brain/utils/vehicle_data/VehicleData.hpp"
#include "common/thread_handler/Reactor.hpp"

using vwg::e3p::sm::PowerManagement;
#endif //defined(SSP_PLATFORM) || defined(SSP_PLATFORM_TEST)

using common::configuration::Configuration;
using common::memory::PersistentMemoryWatchdog;
using common::memory::PersistentMemoryFactory;
using common::notification_handler::DataArrivedEvent;
using common::thread_handler::EThreadStatus;
using common::thread_handler::ThreadHandler;
using namespace common::memory;

using brain::app_mng::BrainApp;
namespace brain
{
namespace app_mng
{
using MessageRepositoryInterface = brain::messageRepository::MessageRepositoryInterface;
}
}  // namespace brain

BrainApp * BrainApp::m_instance = nullptr;

BrainApp::BrainApp() :
    m_communicatorManager(nullptr)
    ,m_engineDispatcher(nullptr)
    ,m_configuration(nullptr)
    ,m_timer(nullptr)
    ,m_player(nullptr)
    ,m_shutDown(true)
    ,m_threadHandler(ThreadHandler::GetInstance())
{
#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))   
m_powerManagement = std::make_unique<PowerManagement>(common::IDS_APPLICATION_NAME);
#endif // defined(TESTS) || defined(HCP5_PLATFORM)
    m_instance = this;
}

BrainApp* BrainApp::GetInstance()
{
    if (nullptr == m_instance)
    {
        LOG_ERROR << "BrainApp was not initialized" << LOG_NOOP;
    }

    return m_instance;
}

#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))   
void BrainApp::PowerManagementHandler(PowerManagement::RequestType const request) noexcept
{
    m_currentPowerRequest = request;
    m_powerStateChange.notify_one();
}

PowerManagement::ReturnType BrainApp::updatePowerState(PowerManagement::PowerState state) noexcept
{
    m_currentPowerState = state;
    auto rc{PowerManagement::ReturnType::kSuccess};
#if defined(TESTS) || defined(HCP5_PLATFORM)
    try
    {
        rc = m_powerManagement->reportPowerState(state);
    }
    catch (std::exception const& e)
    {
        LOG_WARNING << "Exception when reporting the power state " << static_cast<int>(state) << ": " << e.what()
                    << LOG_NOOP;
    }
#endif // defined(TESTS) || defined(HCP5_PLATFORM)
    return rc;
}
#endif // !defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST)


EThreadStatus BrainApp::powerStateChangeHandler()
{
    std::unique_lock<std::mutex> lk(m_powerStateChangeMutex);
#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))   
    while (nullptr != m_instance) {

        m_powerStateChange.wait(lk);

        if (nullptr == m_instance )
        {
            break;
        }

        LOG_INFO << "Received " << PowerManagement::RequestTypeToString(m_currentPowerRequest) << " request"
                 << LOG_NOOP;
        if (IsValidRequest())
        {
            switch (m_currentPowerRequest)
            {
                case PowerManagement::RequestType::kPrepareStandby:
                    disableSender();
                    m_retReport = updatePowerState(PowerManagement::PowerState::kStandby);
                    break;

                case PowerManagement::RequestType::kPrepareSuspend:
                    ChangeIdsMode(false, false);// the sender is disabled when preparing to standby (only then the persistent memory can be written)
                    m_idsEnableDisable->SetMode(false);
                    m_retReport = updatePowerState(PowerManagement::PowerState::kSuspended);
                    break;
                
                case PowerManagement::RequestType::kResume:
                // falls through
                case PowerManagement::RequestType::kCancelSuspend:
                    ChangeIdsMode(true, false);// the sender is enabled after sending the Running notification to the state manager
                    m_idsEnableDisable->SetMode(true);
                    m_retReport = updatePowerState(PowerManagement::PowerState::kRunning);
                    enableSender();
                    break;

                default:
                    LOG_WARNING << "Received unknown request" << LOG_NOOP;
                    break;
            }
        }
        else
        {
            LOG_WARNING << "Not a valid request " << PowerManagement::RequestTypeToString(m_currentPowerRequest)
                        << " with state " << PowerManagement::PowerStateToString(m_currentPowerState) << LOG_NOOP;
        }

        if(PowerManagement::ReturnType::kGeneralError == m_retReport)
        {
            LOG_WARNING << "Report Power State Failed" << LOG_NOOP;
        }  
    }
#else
    ChangeIdsMode(true);
#endif
    return EThreadStatus::eSuccess;
}

bool BrainApp::Init(ConfigurationPtr config, PersistentMemoryFactoryPtr perMemFactory, CounterManagerPtr debugCounters)
{
    if ((nullptr == config) || (nullptr == perMemFactory))
    {
        return false;
    }

    // set the configuration member to the given config
    m_shutDown = false;
    m_configuration = config;
    m_debugCounters = debugCounters;
    m_persistentMemoryFactory = perMemFactory;
    m_timer = std::make_shared<common::Timer>();

    if (nullptr != m_debugCounters)
    {
        // init counters
        m_startMeasurementInterval = m_debugCounters->CreateCounter(common::counters::debug::BRAIN_MEASUREMENT_INTERVALS_STARTED_COUNTER_NAME, EventCounter::EventCounterLevelType::COUNTER_DEBUG);
        m_endMeasurementInterval = m_debugCounters->CreateCounter(common::counters::debug::BRAIN_MEASUREMENT_INTERVALS_ENDED_COUNTER_NAME, EventCounter::EventCounterLevelType::COUNTER_DEBUG);
        m_resetBrain = m_debugCounters->CreateCounter(common::counters::errors::BRAIN_CRASH_FREEZE_RESET_COUNTER_NAME, EventCounter::EventCounterLevelType::COUNTER_ERROR);
    }

    std::string logLevelStr = "0x1F"; 
    std::ignore = m_configuration->GetValue(config_keys::LOG_LEVEL_BM, logLevelStr);
    auto const logLevel = static_cast<uint8_t>(std::stoul(logLevelStr, nullptr, 16));
    common::utils::Logger::GetInstance().SetLogLevelBitMask(logLevel);

    bool enableQueueLogDebugLevel = true;
    std::ignore = m_configuration->GetValue(config_keys::ENABLE_QUEUE_LOG_IN_DEBUG_LEVEL_STATUS, enableQueueLogDebugLevel);
    common::utils::Logger::GetInstance().SetQueueLogInDebugLevelStatus(enableQueueLogDebugLevel);

    uint32_t suppressionIntervalMs{};
    auto rc = m_configuration->GetValue(config_keys::REPEATED_LOG_SUPRESSION_INTERVAL_MS, suppressionIntervalMs);
    if (rc)
    {
        common::utils::Logger::GetInstance().SetLogSupressionIntervalMs(suppressionIntervalMs);
    }

    size_t logRateHz{};
    size_t logBurst{};
    size_t logTokenRefillPeriodMs{};
    rc = m_configuration->GetValue(config_keys::LOG_PRINT_RATE_HZ, logRateHz);
    rc = rc && m_configuration->GetValue(config_keys::LOG_PRINT_BURST, logBurst);
    rc = rc && m_configuration->GetValue(config_keys::LOG_TOKEN_REFILL_PERIOD_MS, logTokenRefillPeriodMs);
    if (rc)
    {
        common::utils::Logger::GetInstance().SetLogRateLimiterParameters(logRateHz, logBurst, logTokenRefillPeriodMs);
    }

#if defined (DEBUG_COUNTER) && !defined(TESTS)

    bool areCountersEnabled = true;
    std::ignore = m_configuration->GetValue(config_keys::COUNTER_LOGGER_STATUS, areCountersEnabled);

    if (areCountersEnabled)
    {
        LOG_INFO << "Enable Counters" << LOG_NOOP;
        auto const debugCountersVec = std::vector<std::shared_ptr<common::counters::CounterManager>>{m_debugCounters};
        m_counterLogger = std::make_unique<common::counters::CounterLogger>(debugCountersVec, m_configuration);
        if (m_counterLogger)
        {
            // Start counter logger
            if (!m_counterLogger->RunThread())
            {
                LOG_ERROR << "Can't start CounterLogger thread!" << LOG_NOOP;
            }
        }
        else
        {
            LOG_ERROR << "failed to allocate memory for CounterLogger" << LOG_NOOP;
        }
    }
#endif // (DEBUG_COUNTER) && !(TESTS)

    updateGuidNumber();

    m_queuesManager = std::make_shared<common::notification_handler::SensorDataQueuesManager>(m_configuration, m_debugCounters);

    PersistentMemoryFactoryPtr persistentMemoryFactory = m_persistentMemoryFactory;

#if !defined(HCP5_PLATFORM)
    bool unlimitedCredit = false;
    std::ignore = m_configuration->GetValue(config_keys::UNLIMITED_CREDIT_FOR_REPORT, unlimitedCredit);

    if (unlimitedCredit)
    {
        LOG_INFO << "Initializing brain - Unlimited credit specified - using persistent memory mock for sender only!"
                 << LOG_NOOP;
        persistentMemoryFactory = m_persistentMemoryFactoryMock;
    }
#endif //HCP5_PLATFORM
#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))   
    brain::engines::CriticalAlertFilter::GetInstance().Init(m_configuration);
#endif
    // Reactor initialization
    m_reactor = std::make_shared<Reactor>(std::vector<std::pair<uint32_t, uint32_t>>({std::make_pair(10U, 1U)}));

    // Message repository initialization
    m_msgRepository = std::make_shared<MessageRepositoryPriorityQueue>(debugCounters);
    const std::vector<MessageRepositoryInterface::MessageRepositoryParameters> repoParameters = {{5U, 400U}, {1U, 200U}, {1U, 80U}, {1U, 40U}};
    m_msgRepository->Init(repoParameters);

    std::unique_ptr<Creditor> creditor = std::make_unique<Creditor>(m_persistentMemoryFactory, m_debugCounters, m_configuration);
#if !defined(HTTPS_PUBLISHER)
    // Initialize runtime for the GDCAgent's CommonLarge skeleton
    static ac::com::Runtime runtime{};
    std::unique_ptr<brain::publishers::gdc_publisher::GDCPublisher> publisher = std::make_unique<brain::publishers::gdc_publisher::GDCPublisher>(persistentMemoryFactory, debugCounters,m_configuration);
#else 
    std::unique_ptr<brain::publishers::https::Publisher> publisher = std::make_unique<brain::publishers::https::Publisher>(persistentMemoryFactory, debugCounters,m_configuration);
#endif

    SPExceededMessageSizeCheck exceededMessageSizeCheck = std::make_shared<brain::publishers::utils::ExceededMessageSizeCheck>(m_configuration);

    m_senderManager = std::make_unique<SenderManager>(
        m_persistentMemoryFactory, m_debugCounters, m_configuration, m_reactor, m_msgRepository, std::move(creditor), std::move(publisher), exceededMessageSizeCheck);

    LOG_INFO << "Sender Manager was created" << LOG_NOOP;

    m_idsEnableDisable = std::make_shared<common::shutdown_and_enabler::IDSEnabler>([this](bool newMode){ChangeIdsMode(newMode);});

    m_diagnosticsManager = std::make_shared<brain::diagnostics::DiagnosticsManager>(m_debugCounters, m_idsEnableDisable, m_persistentMemoryFactory, m_timer);

    m_engineDispatcher = std::make_shared<brain::engines::EngineDispatcher>(
        m_queuesManager, m_msgRepository, m_debugCounters, m_configuration, m_timer, m_persistentMemoryFactory, m_diagnosticsManager, exceededMessageSizeCheck);

    m_communicatorManager = std::make_shared<brain::brain_communicator::CommunicatorManager>(m_queuesManager, m_configuration, m_debugCounters, m_timer, m_diagnosticsManager);
    m_idsEnableDisable->ChangeMode(m_diagnosticsManager->GetFeatureFlag(brain::adaptation_values_names::AdaptationId::DIAGNOSTICS_IDS_ENABLED));

    m_diagnosticsManager->Init();

    LOG_INFO << "Initializing brain - Running component client service" << LOG_NOOP;

    brain::engines::EngineDispatcher::CreateRulesEngineThread(m_engineDispatcher);

    m_threadHandler->StartThread([this]()->EThreadStatus
    {
        return this->powerStateChangeHandler();
    }, std::string(threads_names::ids::POWER_STATE));
#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
#if defined(TESTS) || defined(HCP5_PLATFORM)
    m_powerManagement->setPowerStateRequestHandler(std::bind(&BrainApp::PowerManagementHandler, this, std::placeholders::_1));
#endif // defined(TESTS) || defined(HCP5_PLATFORM)
#endif
    LOG_INFO << "Initializing brain - Brain initialization complete" << LOG_NOOP;
    return true;
}

bool BrainApp::Init()
{
    LOG_INFO << "Brain initialization started" << LOG_NOOP;

    std::unique_lock<std::recursive_mutex> const lk(m_brainStateMutex);
    m_configFilePaths = getConfigPaths();

    m_debugCounters = std::make_shared<common::counters::CounterManager>();
    if (!m_debugCounters)
    {
        LOG_ERROR << "Initializing brain - failed to allocate memory for CounterManager" << LOG_NOOP;
    }

    PersistentMemoryWatchdogPtr persistentMemoryWatchdog = std::make_shared<PersistentMemoryWatchdog>();
    
    common::memory::PersistentMemoryManagerBuilder persistanceBuilder{persistentMemoryWatchdog, m_debugCounters};
    PersistentMemoryFactoryPtr persistentMemoryFactory = std::make_shared<PersistentMemoryFactory>(false, persistanceBuilder); 
    m_persistentMemoryFactoryMock = std::make_shared<PersistentMemoryFactory>(true, persistanceBuilder);

    auto config = Configuration::CreateConfig(m_configFilePaths, persistentMemoryFactory, PER_MEM_IDS_BRAIN_CONFIGURATION_DATA);
    
    return Init(config, persistentMemoryFactory, m_debugCounters);
}

void BrainApp::StartPlayer()
{
    std::string playerFileName;
    bool const isSettingPresent =
        m_configuration->GetValue(config_keys::BRAIN_NOTIFICATIONS_PLAYER_FILE, playerFileName);

    if (isSettingPresent && !playerFileName.empty())
    {
        LOG_INFO << "Creating internal Player for file: " << playerFileName << LOG_NOOP;
#if defined (EEE_PLATFORM)
        LOG_ERROR << "not supported in release platform" << LOG_NOOP;
#else
        m_player = std::make_shared<brain::internal_player::InternalPlayer>(m_queuesManager, m_debugCounters, m_diagnosticsManager);
        if (m_player) 
        {
            std::ignore = m_player->StartPlayerFromFile(m_configuration);
        }

#endif // EEE_PLATFORM
    }
    else
    {
        LOG_ERROR << "Starting player - Notifications player is enabled but no file provided" << LOG_NOOP;
    }
}

BrainApp::~BrainApp()
{
    try
    {
        m_shutdownSleeper.WakeUp();

#ifdef DEBUG_COUNTER
        if (m_counterLogger)
        {
            m_counterLogger->Disable();
        }
#endif  // DEBUG_COUNTER

        if (m_persistentMemoryWatchdog)
        {
            m_persistentMemoryWatchdog->Stop();
        }

        m_instance = nullptr;

        // close power state listner
        m_powerStateChange.notify_one();

        if (!m_shutDown)
        {
            PrepareToShutdown();
            // close all the threads
            m_threadHandler->Stop();
        }
        LOG_INFO << "BrainApp Destructor end" << LOG_NOOP;
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "destruction of the BrainApp failed and got exception." << LOG_NOOP;
    }  // only for parasoft violations
}

void BrainApp::Run()
{
    LOG_INFO << "Running brain - SELF_TEST: brain starting his main loop" << LOG_NOOP;

    std::ignore = prctl(PR_SET_NAME, threads_names::ids::BRAIN_APP_RUN, 0, 0, 0);

    while (!ShouldStop())
    {
        LOG_VERBOSE << "Brain loop start" << LOG_NOOP;

        static constexpr auto WAIT_TIMEOUT_MS = 500U;
        uint64_t waitTime = WAIT_TIMEOUT_MS;
        if (m_shutDown)
        {
            LOG_VERBOSE << "m_shutdown is on, sleeping" << LOG_NOOP;
            std::ignore = m_shutdownSleeper.SleepMilliseconds(waitTime);
        }
        else
        {
            if (m_idsEnableDisable->GetMode())
            {
                LOG_VERBOSE << "IDS enabled" << LOG_NOOP;
                waitTime =  m_timer->ProcessTimerEntries();
            }

            bool const returnByEvent = m_threadHandler->TryWait(std::chrono::milliseconds(waitTime));
            LOG_DEBUG << "Brain main loop triggered by " << (returnByEvent ? "EVENT" : "TIMEOUT TIMER") << LOG_NOOP;
        }
        LOG_VERBOSE << "Brain Loop done" << LOG_NOOP;
    }

    updateDiagnosticsOnCrash();

    LOG_INFO << "Running brain - brain stopping main loop" << LOG_NOOP;
} 

void BrainApp::updateDiagnosticsOnCrash()
{
    // If Run loop stops, it means that a signal was received
    if (nullptr != m_debugCounters)
    {
        // Diag MV - 0x032d
        common::counters::IncreaseCounter(m_resetBrain);
    }
    m_diagnosticsManager->updateDiagnosticsOnCrash();
}

void BrainApp::ChangeIdsMode(bool nextMode, bool toggleSender)
{
    std::unique_lock<std::recursive_mutex> const lk(m_brainStateMutex);

    auto const currentMode = m_idsEnableDisable->GetMode();

    LOG_INFO << "Current Brain State is:" << (m_shutDown ? "KprepSD" : "Kon")
             << ", Current Ids brain Mode is :" << (currentMode ? "Enable" : "Disable") << " --> Changing to "
             << (nextMode ? "Enable" : "Disable") << LOG_NOOP;

    if (currentMode == nextMode)
    {
        LOG_DEBUG << "Ids mode is already " << (currentMode ? "Enabled" : "Disabled")
                  << " trying to change to the same state" << LOG_NOOP;
    }
    else
    {
        if (nextMode)
        {
            //if changing to ON
            changeIdsModeToEnabled(toggleSender);
            LOG_INFO << "Switched mode to Enabled" << LOG_NOOP;
        }
        else
        {
            //if changing to OFF
            changeIdsModeToDisabled(toggleSender);
            LOG_INFO << "Switched mode to Disabled" << LOG_NOOP;
        }
    }
}

void BrainApp::changeIdsModeToEnabled(bool toggleSender)
{
    LOG_INFO << "IDS state changed to enabled" << LOG_NOOP;

    if (!m_shutDown)
    {
        m_communicatorManager->RegisterAllNotificationHandlers();

        if (toggleSender)
        {
            enableSender();
        }

        common::counters::IncreaseCounter(m_startMeasurementInterval);
    }
}

void BrainApp::changeIdsModeToDisabled(bool toggleSender)
{
    LOG_INFO << "IDS state changed to disabled" << LOG_NOOP;

    // Close all SOME/IP connections and stop UDPTunnelHandler thread
    // Improves the transition time to suspended state to stay below 5 seconds
    m_communicatorManager->DeregisterSensorsNotifications();
    m_queuesManager->ClearAllQueues();

    if (toggleSender)
    {
        disableSender();
    }

    common::counters::IncreaseCounter(m_endMeasurementInterval);
}

bool BrainApp::PrepareToShutdown()
{
    LOG_INFO << "Preparing to shutdown Brain" << LOG_NOOP;
    std::unique_lock<std::recursive_mutex> const lk(m_brainStateMutex);
    LOG_INFO << "Current Brain State is:" << (m_shutDown ? "KprepSD" : "Kon")
             << "--> Changing to {KprepSD}, Current Ids brain Mode is :"
             << (m_idsEnableDisable->GetMode() ? "Enable" : "Disable") << LOG_NOOP;

    if (nullptr != m_senderManager)
    {
        m_senderManager->PrepareToShutDown();
    }

    if (nullptr != m_configuration)
    {
       std::ignore = m_configuration->PrepareToShutdown();
    }

    #ifndef SSP_PLATFORM
    m_communicatorManager->PrepareToShutdown();
    #endif
    
    m_shutDown = true;
    return true;
}


bool BrainApp::CancelPrepareToShutdown()
{
    LOG_INFO << "Canceling preparations to shutdown Brain" << LOG_NOOP;
    std::unique_lock<std::recursive_mutex> const lk(m_brainStateMutex);
    LOG_INFO << "Current Brain State is:" << (m_shutDown ? "KprepSD" : "Kon")
             << "--> Changing to {Kon}, Current Ids brain Mode is :"
             << (m_idsEnableDisable->GetMode() ? "Enable" : "Disable") << LOG_NOOP;

    if (m_idsEnableDisable->GetMode())
    {
    #ifndef SSP_PLATFORM
        m_communicatorManager->CancelPrepareToShutdown();
    #endif
    }

    if (nullptr != m_senderManager)
    {
        m_senderManager->CancelPrepareToShutDown();
    }

    if (nullptr != m_configuration)
    {
        std::ignore = m_configuration->CancelPrepareToShutdown();
    }

    m_shutDown = false;
    return true;
}

void BrainApp::updateGuidNumber()
{
    std::string guidNumber;
    if (!m_configuration->GetValue(config_keys::VEHICLE_GUID, guidNumber) || guidNumber.empty())// !already set
    {
        static constexpr uint8_t GUID_GENERATION_VERSION = 1U;       //time-based version. see RFC 4122 for more information
        guidNumber = common::GUID::CreateGUID(GUID_GENERATION_VERSION);
        if (!guidNumber.empty())
        {
            LOG_INFO << "m_configuration set GuidNumber" << LOG_NOOP;
            std::ignore = m_configuration->SetPersistentValue(config_keys::VEHICLE_GUID, guidNumber);
            m_configuration->SavePersistent();
        }
    }
    
    if (!m_configuration->GetValue(config_keys::VEHICLE_GUID, guidNumber) || guidNumber.empty())// !already set
    {
        LOG_ERROR << "get GUID failed" << LOG_NOOP;
    }
    LOG_DEBUG << "GuidNumber: " << guidNumber.c_str() << LOG_NOOP;
}

std::vector<std::string> BrainApp::getConfigPaths() const
{
    std::vector<std::string> configFilePaths;

#ifdef SIMULATION
#ifdef TESTS
    configFilePaths = {CONFIG_BRAIN_SIMULATION_CONFIG, BRAIN_TEST_PATH};
#else //TESTS
    configFilePaths = {"/config/brain_simulation_config.json"};
#endif  // TESTS
#elif defined EEE_PLATFORM
#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
#ifdef TESTS
    configFilePaths = {"/system/e3/etc/e3_ids/brain_eee_config.json", BRAIN_TEST_PATH};
#else //TESTS
    configFilePaths = {"/system/e3/etc/e3_ids/brain_eee_config.json"};
#endif //TESTS
#else  // !defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST)
    configFilePaths = {"/config/brain_ssp_config.json",
                       "/usr/local/brain_eee_config.json",
                       "/opt/e3_ids/config/brain_eee_config.json",
                       "/system/e3/etc/e3_ids/brain_eee_config.json"};
#endif  //! defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST)
#endif  // SIMULATION and EEE_PLATFORM

    return configFilePaths;
}