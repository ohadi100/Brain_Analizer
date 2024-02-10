/**
 * @file
 * @brief     A calss that injects incidents to the brain
 */
#ifndef INTERNAL_PLAYER_HPP
#define INTERNAL_PLAYER_HPP

#include <thread>

#include "brain/sensor_data/swpac/SWPACSensorDataFactory.hpp"
#include "common/counter_manager/CounterManager.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/notification_handler/SensorDataQueuesManager.hpp"
#include "common/player/PlayerBase.hpp"
#include "common/sensor_data/SensorData.hpp"
#include "common/utils/conditionalSleep/ConditionalSleep.hpp"
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"

using brain::sensor_data::SWPACSensorDataFactory;

namespace brain
{
namespace internal_player
{

/**
 * @class   InternalPlayer
 * @brief   The player is a powerful tool which reads a JSON file and sends the notifications it reads through SomeIP, 
 *          or bypasses the SomeIP communication and just pushes the notifications into the queue
 *          (in case SIMULATION compilation flag is used).
 *          if the player is initialized, all it does is parsing the json file and send the notifications
 *          one by one.
 */
class InternalPlayer : public common::player_base::PlayerBase
{
    using ConfigurationPtr = common::configuration::Pointer;
    using CounterManagerPtr = std::shared_ptr<common::counters::CounterManager>;
    using SensorDataQueuesManagerPtr = std::shared_ptr<common::notification_handler::SensorDataQueuesManager>;
    using DiagnosticsManagerPtr = brain::diagnostics::DiagnosticsManagerInterface::Pointer;
    using SensorDataTag = common::sensor_data::SensorDataTag;

public:
    
    /**
     * @brief   constructor - initialize the publishers and filling a map with the notifications types and relevant functions.
     * @param   DiagnosticsManagerPtr diagnosticsManager.
     */
    InternalPlayer(DiagnosticsManagerPtr diagnosticsManager) :
        InternalPlayer(nullptr, nullptr, diagnosticsManager)
    {}

    /**
     * @brief   constructor with an initialization built in.
     * @param   SensorDataQueuesManagerPtr queuesManager
     * @param   CounterManagerPtr debugCounters
     * @param   DiagnosticsManagerPtr diagnosticsManager
     */
    InternalPlayer(SensorDataQueuesManagerPtr queuesManager, CounterManagerPtr debugCounters, DiagnosticsManagerPtr diagnosticsManager) : 
        m_queuesManager(queuesManager),
        m_playerThread(nullptr),
        m_debugCounters(debugCounters),
        m_diagManager(diagnosticsManager)
    {
        #if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
        brain::sensor_data::SWPACSensorDataFactory::InitCounters(m_debugCounters);
        #endif //(!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
    }

    /**
     * @brief   Destructor.
     */
    virtual ~InternalPlayer();

    /**
     * @brief    default copy constructor
     */
    InternalPlayer(const InternalPlayer& other) = delete;

    /**
     * @brief    default move constructor
     */
    InternalPlayer(InternalPlayer&& other) = delete;

    /**
    * @brief    default copy assignment operator
    */
    InternalPlayer& operator=(InternalPlayer const&) = delete;

    /**
    * @brief   default move assignment operator
    */
    InternalPlayer& operator=(InternalPlayer&&) = delete;

    /**
     * @brief  Playing all the notifications from the object m_JsonRoot that was parsed from the config file.
    */
    void Play() override;

    /**
    * @brief   playing all the notifications from the object jsonToPlay.
    * @param   jsonToPlay.
    */
    void virtual Play(const Json::Value & jsonToPlay);

    /**
     * @brief   create and start the player thread.
     * @return  bool true if succeed, false otherwise 
     */
    bool StartThread();
    
    /**
     * @brief   wait for player thread finished
     */
    void WaitForPlayer() const;

    /**
     * @brief   running the internalPlayer thread with a file.
     *          Will work only if the player is enabled in the configuration and there is a file there also.
     * @param   Configuration
     * @return  bool true if succeed, false otherwise.
     */
    bool StartPlayerFromFile(ConfigurationPtr configuration);

    /**
     * @brief   initialize the Player with a file name,
     * @param   Configuration& configuration
     * @return  true, if initialization succeeded, false otherwise.
     */
    bool LoadPlayerFile(ConfigurationPtr configuration);
	
	/**
     * @brief   check if the Player is already initialized.
     * @param   none.
     * @return  true, if already initialized, false otherwise.
     */
    bool InitializePlayer(common::configuration::Configuration& configuration) override;
protected:

    void sendData(UPSensorData sd) override;

private:

    SensorDataQueuesManagerPtr m_queuesManager;
    common::ConditionalSleep m_sleeper;
    std::mutex m_playMutex;

    /**
    * @thread: m_playerThread
    * @brief:  This thread mainly generate events from JSON file.
    *
    *          After it finish to read the JSON file the thread is terminate.
    */
    std::shared_ptr<std::thread> m_playerThread;

    CounterManagerPtr m_debugCounters;

    std::shared_ptr<brain::diagnostics::DiagnosticsManagerInterface> m_diagManager;
};

} // namespace internal_player
} // namespace brain
#endif //INTERNAL_PLAYER_HPP
