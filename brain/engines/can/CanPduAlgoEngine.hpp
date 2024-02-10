/**
 * @file      CanPduAlgoEngine.hpp
 * @brief     Definition of the CanPduAlgoEngine class
 */
#pragma once

#include "brain/canPdu/CanPDU.hpp"
#include "brain/canPdu/CanPduData.hpp"
#include "brain/canPdu/CanPduParser.hpp"
#include "brain/engines/Engine.hpp"

#include "brain/config/BrainConfigConstants.hpp"
#include "brain/events/EventPriority.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/sensor_data/SensorData.hpp"
#include "common/sensor_data/SensorDataTags.hpp"
#include "common/utils/types/ConfigurationTypes.hpp"
#include "brain/engines/serializer/IDSPeriodicReportSerializer.hpp"



#include "CanPduEventEngine.hpp"

// TODO uncomment when the MEB counter manager is ready

// #include "common/counter_manager/MebCounterManager.h"
// #include "brain/counter_manager/CanCounterManager.h"

#include <set>

namespace brain
{
namespace engines
{
using common::sensor_data::SensorData;
using SdTag            = common::sensor_data::SensorDataTag;
using CommonSDPtr      = common::sensor_data::UPSensorData;
using ConfigurationPtr = common::configuration::Pointer;
// using MebCountersmanagerptr = std::shared_ptr<common::counters::MebCounterManager>;
// using CanCounterManagerPtr = std::shared_ptr<brain::counters::CanCounterManager>;
using SPCanPduState = std::shared_ptr<brain::can_pdu::CanPduState>;
using PduPtr        = brain::can_pdu::CanPDU*;
using ReturnCode    = brain::engines::ReturnCode;
using EventPriority = brain::events::EventPriority;


class CanPduAlgoEngine : public brain::engines::Engine
{
public:
    /**
     * @brief Constructor for the CanPduAlgoEngine class.
     *
     * @param[in] config
     */
    CanPduAlgoEngine(ConfigurationPtr                                                      config,
                     std::shared_ptr<brain::messageRepository::MessageRepositoryInterface> msgRepository,
                     IDSPeriodicReportSerializerPtr                                        reportSerializer,
                     EventPriority                                                         priority);

    /**
     * @brief Handles incoming sensor data.
     *
     * @param[in] sd Sensor data pointer
     *
     * @return ReturnCode with the processed SensorData
     */
    ReturnCode processInternal(common::sensor_data::UPSensorData sd) override;

    /**
     * @brief Destructor for the CanPduAlgoEngine class.
     */
    virtual ~CanPduAlgoEngine()
    {
    }

private:
    static constexpr uint32_t KLEMMEN_STATUS_01_ID     = 960U;         ///< Klemmen_Status_01 can id in decimal
    static constexpr uint32_t KLEMMEN_STATUS_MOCKED_ID = 316495106U;   ///< IM-4862
    static constexpr uint32_t INDEX_TO_DETECT_ERROR    = 0xFFFFFFFFU;  ///< IM-4962
    static constexpr uint8_t  KLEMME_15_BYTE           = 2U;           ///< The byte of Klemme 15 in Klemmen_Status_01
    static constexpr uint8_t  KLEMME_15_BIT            = 1U;  ///< The bit of Klemme 15 in its Byte in Klemmen_Status_01
    static constexpr char     pduPopFromQueue[]        = "CAN pdu - pop from queue";

    bool InitCanAnalyzer();
    bool RunCanAnalyzer(PduPtr pdu, IDS_Result& algoRes, brain::can_pdu::CanEventEngineData& eventData);

    ReturnCode HandlePeriodicCanSensorData(CommonSDPtr sd);
    ReturnCode HandleCanPduSensorData(CommonSDPtr sd);

    // void countEventForSpecificRule(brain::can_pdu::CanPDU &pdu, IDS_Result const canAlgoRes, IDS_Result const mask,
    // std::shared_ptr<common::counters::MebEventCounter> counter); void updateCounters(brain::data_unit::CanPDU &pdu,
    // IDS_Result const canAlgoRes);

    brain::engines::CanPduEventEngine m_canPduEventEngine;
    ConfigurationPtr                  m_idsConfig;
    std::set<uint32_t>                m_mutedCanIds;
    SPCanPduState                     m_state;
    bool                              m_kl15SignalOn = false;
    // MebEventCounterptr m_popPduFromQueueCounter;
    brain::can_pdu::CanPduParser m_parser;

    IDS_Result m_isCanAttackOccured = RESULT_OK;  // IM-5211 - this variable is to verify that we update previous
                                                  // attack.
    // MebCountersmanagerptr m_mebCounters;
    // CanCounterManagerPtr m_canCounters;
    // std::unordered_map<uint32_t, std::shared_ptr<brain::counters::CanMessageCounter>> m_canIdToCounter;

    // std::shared_ptr<common::counters::MebEventCounter> m_counterNewEvent;
    // std::shared_ptr<common::counters::MebEventCounter> m_eventRateCounter;
    // std::shared_ptr<common::counters::MebEventCounter> m_eventTimeCounter;
    // std::shared_ptr<common::counters::MebEventCounter> m_eventDropCounter;
    // std::shared_ptr<common::counters::MebEventCounter> m_eventCreateFailed;

    // // diagnostics counters
    // std::shared_ptr<common::counters::MebEventCounter> m_ruleACounter;
    // std::shared_ptr<common::counters::MebEventCounter> m_ruleBCounter;
    // std::shared_ptr<common::counters::MebEventCounter> m_ruleCCounter;
    // std::shared_ptr<common::counters::MebEventCounter> m_ruleECounter;
    // std::shared_ptr<common::counters::MebEventCounter> m_ruleFCounter;
    // std::shared_ptr<common::counters::MebEventCounter> m_ruleGCounter;

    // // Event rate
    // uint64_t m_eventCounter = 0;
    uint64_t m_lastUpdateTime = 0;
};
}  // namespace engines
}  // namespace brain