/**
 * @file
 * @brief     This file contains the functionality of the InternalPlayer class
 */
#include "InternalPlayer.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/utils/jsonUtils/JsonUtils.cpp"
#include "brain/sensor_data/swpac/IncidentHelper.hpp"

using brain::internal_player::InternalPlayer;
using brain::sensor_data::swpac::ConstraintId;
using common::utils::JsonUtils;
using std::string;

InternalPlayer::~InternalPlayer()
{
    try
    {
        m_sleeper.WakeUp();
        if (m_playerThread != nullptr)
        {
            if (m_playerThread->joinable())
            {
                m_playerThread->join();
            }
        }
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "destruction of the InternalPlayer failed and got exception." << LOG_NOOP;
    }  // only for parasoft violations
}

bool InternalPlayer::InitializePlayer(common::configuration::Configuration& configuration)
{
    bool res = PlayerBase::InitializePlayer(configuration);
    if (res) 
    {
        setMaxNumMsgInterval(0);
    }
    return res;
}

void InternalPlayer::Play()
{
    Play(getJsonRoot());
}

void InternalPlayer::Play(const Json::Value & jsonToPlay)
{
    #if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
    // Lock since we can reach this section from both the tests and the Http server.
    std::lock_guard<std::mutex> lock(m_playMutex);
    if (IsInitialized())
    {
        uint64_t prevTime = 0U;   

        for (Json::Value currJsonObj : jsonToPlay)
        {
            ConstraintId constrainId{ConstraintId::UNDEFINED_CONSTRAINTID};
            SWPACSensorDataFactory::UPSensorDataVectorPtr sdVector =
                brain::sensor_data::SWPACSensorDataFactory::CreateSD(constrainId, currJsonObj.toStyledString().c_str(), m_diagManager);
            if (!sdVector || nullptr == sdVector->front())
            {
                LOG_DEBUG << "Invalid sensor data was read from JSON" << LOG_NOOP;
                continue;
            }

            uint64_t currTime = currJsonObj["timestamp"].asUInt();
            uint64_t timeDiff = currTime - prevTime;

            if ((0U < timeDiff) && (0U != prevTime))
            {
                std::ignore = m_sleeper.SleepMilliseconds(timeDiff);
            }
          
            //moved name acquisition to be before move to avoid losing ownership over up before fetching name
            for (auto& sd : *sdVector)
            {
                sendData(std::move(sd));
            }

            prevTime = currTime;
            
        }
    }
    #else //(!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
        std::ignore = jsonToPlay;
    #endif //(!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
}

void InternalPlayer::sendData(UPSensorData sd)
{
    LOG_DEBUG << "sending notification of tag: " << static_cast<uint32_t>(sd->GetTag()) << LOG_NOOP;

    if (nullptr == m_queuesManager)
    {
        LOG_ERROR << "invalid notificationHandler" << LOG_NOOP;
        return;
    }

    std::ignore = m_queuesManager->AddNotificationToQueue(std::move(sd));
}

bool InternalPlayer::StartThread()
{
    m_playerThread = std::make_shared<std::thread>([this]() {Play(); });

    if (nullptr == m_playerThread)
    {
        LOG_ERROR << "InternalPlayer::StartPlayer - Failed to allocate memory for player thread" << LOG_NOOP;
        return false;
    }
    if (!(m_playerThread->joinable()))
    {
        LOG_ERROR << "InternalPlayer::StartPlayer - Failed create player thread" << LOG_NOOP;
        return false;
    }
    return true;
}

void InternalPlayer::WaitForPlayer() const
{
    if (nullptr != m_playerThread)
    {
        if (m_playerThread->joinable())
        {
            m_playerThread->join();
        }
    }
}

bool InternalPlayer::StartPlayerFromFile(ConfigurationPtr Configuration)
{
    if (LoadPlayerFile(Configuration))
    {
        return StartThread();
    }
    return false;
}

bool InternalPlayer::LoadPlayerFile(ConfigurationPtr configuration)
{
    bool isPlayerEnabled = false;
    bool isSettingPresent = configuration->GetValue(brain::config_keys::BRAIN_NOTIFICATIONS_PLAYER_ENABLED, isPlayerEnabled);

    if ((false == isPlayerEnabled) || (false == isSettingPresent))
    {
        LOG_ERROR << "Notifications player is disabled" << LOG_NOOP;
        return false;
    }

    std::string playerFileName;
    isSettingPresent = configuration->GetValue(brain::config_keys::BRAIN_NOTIFICATIONS_PLAYER_FILE, playerFileName);
    
    if (!isSettingPresent)
    {
        LOG_ERROR << "Initialize Player without a file" << LOG_NOOP;
        return false;
    }

    if (playerFileName.empty())
    {
        LOG_ERROR << "Notifications player is enabled but no file provided" << LOG_NOOP;
        return false;
    }

    auto jsonRoot = getJsonRoot();
    if (false == JsonUtils::ParseJson(playerFileName, jsonRoot))
    {
        LOG_ERROR << "Failed to parse json file " << playerFileName << LOG_NOOP;
        return false;
    }

    setIsInitialized(true);
    return true;
}
