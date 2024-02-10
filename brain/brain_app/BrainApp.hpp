#pragma once
/**
 * @file
 * @brief This file contains the definition of the BrainApp class and its functionality.
 */
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>


#include "engines/dispatcher/EngineDispatcherBase.hpp"
#include "diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "communicator/CommunicatorManagerBase.hpp"
#include "common/utils/stateMachine/StateMachine.hpp"
#include "sender/BELogicStates.hpp"
#include "sender/SenderManager.hpp"
#include "sender/publishers/interface/PublisherInterface.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/shutdown_and_enabler/ids_enabler/IDSEnabler.hpp"
#include "common/thread_handler/ThreadHandler.hpp"
#include "common/utils/CPP/optional/Optional.hpp"
#include "common/utils/CPP/SafeCall.hpp"
#include "common/utils/conditionalSleep/ConditionalSleep.hpp"
#include "common/utils/os/signal_handlers.hpp"
#include "diagnostics/dtc/DtcEvent.hpp"

#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
#ifdef HTTPS_PUBLISHER
#include "brain/diagnostics/dtc/DtcEvent.hpp"
#endif  // HTTPS_PUBLISHER
#include "ext/PowerStateManager/PowerManagement.hpp"
#endif  //(!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST))


using common::thread_handler::ThreadHandler;

// Forward declarations
namespace brain
{
namespace messageRepository
{
class MessageRepositoryPriorityQueue;
} // namespace message_repository
namespace internal_player
{
class InternalPlayer;
}  // namespace internal_player

namespace brain_communicator
{
class CommunicatorManagerBase;
}  // namespace brain_communicator

namespace brain_communicator
{
class CommunicatorManager;
}  // namespace brain_communicator


namespace sender_manager
{
class SenderManager;
}  // namespace sender

}  // namespace brain

namespace common
{
class Timer;

namespace memory
{
class PersistentMemoryWatchdog;
class PersistentMemoryFactory;
}  // namespace memory

namespace counters
{
class CounterManager;
class CounterLogger;
class EventCounter;
}  // namespace counters

namespace notification_handler
{
class SensorDataQueuesManager;
}  // namespace notification_handler

namespace thread_handler
{
class Reactor;
} // namespace thread_handler
}  // namespace common

//
// Class Definition
//

namespace brain
{
namespace app_mng
{

/**
 * @class       BrainApp
 * @brief       This class manage the Brain. its holding most of the features inside and handles
 *              them to other classes who needs them. its checks the parameters that the main.cpp
 *              gets from the user and initialize the relevant classes according to those parameters
 *              then, its initialize all the controllers and running the timer to process his entries
 *              in addition, this class is in charge of switching the state of the brain to on and off
 *
 *              Static variable: m_instance.
 *              The m_instance variable is containing BrainApp instance in a form of static variable.
 *              This variable manage the all the IDS application.
 *              This class is a singleton.
 *              The initial value is nullptr, and it initiate at the BrainApp constructor to be the BrainApp.
 *              This variable is accessible to any module that import the BrainApp header via the following methods:
 *              GetInstance() - Getter for the instance.
 *              IsInstanceInitiated() - Check if the BrainApp is initiated or not.
 */
class BrainApp
{
public:
    using PersistentMemoryWatchdogPtr = std::shared_ptr<common::memory::PersistentMemoryWatchdog>;
    using PersistentMemoryFactoryPtr  = std::shared_ptr<common::memory::PersistentMemoryFactory>;
    using InternalPlayerPtr           = std::shared_ptr<brain::internal_player::InternalPlayer>;
    using CounterManagerPtr           = std::shared_ptr<common::counters::CounterManager>;
    using EventCounterPtr             = std::shared_ptr<common::counters::EventCounter>;

    using TimerPtr = std::shared_ptr<common::Timer>;

    using SensorDataQueuesManagerPtr = std::shared_ptr<common::notification_handler::SensorDataQueuesManager>;

    using EngineDispatcherBasePtr = brain::engines::EngineDispatcherBase::EngineDispatcherBasePtr;

    using CommunicatorManagerPtr = std::shared_ptr<brain::brain_communicator::CommunicatorManagerBase>;

    using IdsEnableDisablePtr = std::shared_ptr<common::shutdown_and_enabler::IDSEnabler>;
    using ConfigurationPtr = common::configuration::Pointer;

    using DiagnosticsManagerInterface = std::shared_ptr<brain::diagnostics::DiagnosticsManagerInterface>;

    using EventCounter = common::counters::EventCounter;

    using EThreadStatus = common::thread_handler::EThreadStatus;

    using SenderManager = brain::sender_manager::SenderManager;
    using Reactor       = common::thread_handler::Reactor;
    using Creditor      = brain::sender::Creditor;
    using MessageRepositoryPriorityQueue = brain::messageRepository::MessageRepositoryPriorityQueue;
    using PublisherPtr  = std::shared_ptr<PublisherInterface>;
    using SPExceededMessageSizeCheck = std::shared_ptr<brain::publishers::utils::ExceededMessageSizeCheck>;

    /**
     * @brief   Constructor
     */
    BrainApp();

    /**
     * @brief    default copy constructor
     */
    BrainApp(const BrainApp& other) = delete;

    /**
     * @brief    default move constructor
     */
    BrainApp(BrainApp&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    BrainApp& operator=(BrainApp const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    BrainApp& operator=(BrainApp&&) = delete;

    /**
     * @brief   Destructor
     */
    virtual ~BrainApp();

    /**
     * @brief   there should be only one BrainApp in the program. this function grant access to the single instance of
     * this class
     * @return  BrainApp* - a pointer to the instance
     */
    static BrainApp* GetInstance();

    /**
     * @brief   initialize the system with all the relevant controllers and major classes such as the brainNH. also,
     *          checks the arguments passed and insert the strings into the configuration class if they exist
     * @return  bool - true if init succeeded, false otherwise
     */
    bool Init();

    /**
     * @brief   initialize the system with all the relevant controllers and major classes by initiated config object and
     * perMemFactory object.
     * @param   config - pointer to a well created config object by Configuration::CreateConfig.
     * @param   perMemFactory - pointer to persistent memory factory object for BrainApp persistent storage
     * @param   debugCounters - pointer to Counter Manager which hold the application logging counters
     * @return  bool - true if init succeeded, false otherwise
     */
    bool Init(ConfigurationPtr config, PersistentMemoryFactoryPtr perMemFactory, CounterManagerPtr debugCounters);

    /**
     * @brief   running the internalPlayer
     */
    void StartPlayer();

    /**
     * @brief   running the ProcessTimerEntries
     * @dynamic_behavior:
     *          This function run in infinity loop till the stop() flag is set.
     *
     *          In every iteration, this function activate the brainControllersManager to look for
     *          notification from outside sensor, increase the PHM counter, and increase the eventCounter.
     *
     *          This loop run every 500 milliseconds.
     */
    void Run();

    /**
     * @brief   retrieving access to the CommunicatorManager
     * @return  CommunicatorManagerPtr
     */
    inline CommunicatorManagerPtr
    GetCommunicatorManager() const  // make return value const
    {
        return m_communicatorManager;
    }

    /**
     * @brief   retrieving access to the queuesManager
     * @return  SensorDataQueuesManagerPtr
     */
    inline SensorDataQueuesManagerPtr
    GetQueuesManager() const
    {
        return m_queuesManager;
    }

    /**
     * @brief   retrieving access to the engineDispatcher
     * @return  EngineDispatcherBasePtr
     */
    inline EngineDispatcherBasePtr
    GetEngineDispatcher() const
    {
        return m_engineDispatcher;
    }

    /**
     * @brief   retrieving access to the Configuration class
     * @return  ConfigurationPtr
     */
    inline ConfigurationPtr
    GetConfigurationClass() const
    {
        return m_configuration;
    }

    /**
     * @brief   retrieving access to the Timer class
     * @param   none
     * @return  TimerPtr
     */
    inline TimerPtr
    GetTimerClass() const
    {
        return m_timer;
    }


    /**
     * @brief   Getter for counters class
     * @return  CounterManagerPtr
     */
    inline CounterManagerPtr
    GetCounterManagerClass() const
    {
        return m_debugCounters;
    }

    /**
     * @brief   Getter for IDSEnabler class
     * @return  IdsEnableDisablePtr
     */
    inline IdsEnableDisablePtr
    GetIdsEnableDisableClass() const
    {
        return m_idsEnableDisable;
    }

    /**
     * @brief   Check if BrainApp instance has been initiated
     * @return  bool - true iff BrainApp instance has been initiated, false otherwise
     */
    inline static bool
    IsInstanceInitiated() noexcept
    {
        return (nullptr != m_instance);
    }

    /**
     * @brief   Run all the subscribed callbacks for pre shutdown
     * @return  bool - true iff all operations done successfully, false otherwise
     */
    bool PrepareToShutdown();

    /**
     * @brief   Run all the subscribed callbacks for pre shutdown
     * @return  bool - true iff all operations done successfully, false otherwise
     */
    bool CancelPrepareToShutdown();

    /**
     * @brief   Get diagnostic manger class instance
     * @param   none
     * @return  DiagnosticsManagerInterface
     */
    inline DiagnosticsManagerInterface
    GetDiagManager() const
    {
        return m_diagnosticsManager;
    }

    /**
     * @brief   return a pointer to the Internal player. this method is only for debug since the player isn't part of
     * our release.
     * @return  return a pointer to the Internal player.
     */
    inline InternalPlayerPtr
    GetPlayerClass() const noexcept
    {
        return m_player;
    }
#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
    /**
     * @brief   Used as a callback function for power management mehcanism.
     * @param   request, set system according to this power state request.
     */
    void PowerManagementHandler(vwg::e3p::sm::PowerManagement::RequestType const request) noexcept;
    /**
     * @brief   Validates the power management state machine (SM)
     * @return  true iff the SM next state is valid
     * Valid requests:
     * If the PowerManagement::RequestType is kResume && the PowerManagement::PowerState is kSuspend
     * If the PowerManagement::RequestType is kPrepStandby && the PowerManagement::PowerState is kRunning
     * If the PowerManagement::RequestType is kPrepSuspend && the PowerManagement::PowerState is kStandby
     * If the PowerManagement::RequestType is kCancelSuspend && the PowerManagement::PowerState is kStandby
     * If no PowerManagement::PowerState is set yet - every PowerManagement::RequestType is valid
     *
     */
    constexpr bool
    IsValidRequest() const noexcept
    {
        return ((m_currentPowerState == vwg::e3p::sm::PowerManagement::PowerState::kUnknown)
                || ((m_currentPowerRequest == vwg::e3p::sm::PowerManagement::RequestType::kResume)
                    && (m_currentPowerState == vwg::e3p::sm::PowerManagement::PowerState::kSuspended))
                || ((m_currentPowerRequest == vwg::e3p::sm::PowerManagement::RequestType::kPrepareStandby)
                    && (m_currentPowerState == vwg::e3p::sm::PowerManagement::PowerState::kRunning))
                || ((m_currentPowerRequest == vwg::e3p::sm::PowerManagement::RequestType::kPrepareSuspend)
                    && (m_currentPowerState == vwg::e3p::sm::PowerManagement::PowerState::kStandby))
                || ((m_currentPowerRequest == vwg::e3p::sm::PowerManagement::RequestType::kCancelSuspend)
                    && (m_currentPowerState == vwg::e3p::sm::PowerManagement::PowerState::kStandby)));
    }

    vwg::e3p::sm::PowerManagement::ReturnType updatePowerState(
        vwg::e3p::sm::PowerManagement::PowerState state) noexcept;
#endif  //(!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST))
    /**
     * @brief   Chenges IdsMode to enabled/disabled
     * @param   nextMode - true: enable IDS, false: disable IDS
     * @param   toggleSender - true: change the sender state according to nextMode, false: do nothing
     */
    void ChangeIdsMode(bool nextMode, bool toggleSender = true);

#ifndef TESTS
protected:
#endif  // TESTS

    bool createSenderThread();
    void updateGuidNumber();

    void changeIdsModeToDisabled(bool toggleSender);
    void changeIdsModeToEnabled(bool toggleSender);
    void updateDiagnosticsOnCrash();
    bool removeSenderManager();

    inline void
    enableSender()
    {
        common::utils::SafeCall(m_senderManager.get(), &SenderManager::Enable);
    }

    inline void
    disableSender()
    {
        common::utils::SafeCall(m_senderManager.get(), &SenderManager::Disable);
    }

#ifdef TESTS
    inline bool
    getShutDownStatus() const noexcept
    {
        return m_shutDown;
    }
#endif  // TESTS

#ifndef TESTS
private:
#endif  // TESTS

    inline bool
    ShouldStop() const
    {
        return (common::should_stop() || m_threadHandler->ShouldStop());
    }

    EThreadStatus powerStateChangeHandler();

    std::vector<std::string> getConfigPaths() const;

    static BrainApp* m_instance;

    CommunicatorManagerPtr m_communicatorManager;

    SensorDataQueuesManagerPtr m_queuesManager;

    EngineDispatcherBasePtr m_engineDispatcher;

    std::mutex m_senderThreadMutex;

    ConfigurationPtr m_configuration;

    TimerPtr m_timer;

    DiagnosticsManagerInterface m_diagnosticsManager;

    InternalPlayerPtr m_player;

    PublisherPtr m_publisher;

#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
    vwg::e3p::sm::PowerManagement::RequestType m_currentPowerRequest{
        vwg::e3p::sm::PowerManagement::RequestType::kUnknown};
    vwg::e3p::sm::PowerManagement::PowerState m_currentPowerState{vwg::e3p::sm::PowerManagement::PowerState::kUnknown};
    std::unique_ptr<vwg::e3p::sm::PowerManagement> m_powerManagement;
    vwg::e3p::sm::PowerManagement::ReturnType      m_retReport;
    // Diag DTC - 0x600508 - ids_function_stopped_working
    brain::diagnostics::dtc::DtcEvent m_idsFunctionStoppedDtc{ids_evt_EventIdsFunctionStoppedWorking};
#endif  //(!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST))
    // Counters
    CounterManagerPtr                                m_debugCounters;
    std::shared_ptr<EventCounter>                    m_startMeasurementInterval;
    std::shared_ptr<EventCounter>                    m_endMeasurementInterval;
    std::shared_ptr<EventCounter>                    m_resetBrain;

    PersistentMemoryWatchdogPtr                      m_persistentMemoryWatchdog;
    PersistentMemoryFactoryPtr                       m_persistentMemoryFactory;
    PersistentMemoryFactoryPtr                       m_persistentMemoryFactoryMock;
    
    std::recursive_mutex                             m_brainStateMutex;
    bool                                             m_shutDown{true};
    IdsEnableDisablePtr                              m_idsEnableDisable;

#ifdef DEBUG_COUNTER
    std::shared_ptr<common::counters::CounterLogger> m_counterLogger;
#endif  // DEBUG_COUNTER
    std::vector<std::string>                         m_configFilePaths;
    common::ConditionalSleep                         m_senderSleeper;
    common::ConditionalSleep                         m_shutdownSleeper;
    std::condition_variable                          m_powerStateChange;
    std::mutex                                       m_powerStateChangeMutex;
    std::shared_ptr<ThreadHandler>                   m_threadHandler{ThreadHandler::GetInstance()};

    std::unique_ptr<SenderManager>                   m_senderManager;
    std::shared_ptr<Reactor>                         m_reactor;
    std::shared_ptr<MessageRepositoryPriorityQueue>  m_msgRepository;
};

}  // namespace app_mng
}  // namespace brain
