#include "CanPduAlgoEngine.hpp"
#include "CanStatisticFillInfo.hpp"
#include "common/utils/os/time/Time.hpp"
#include "ext/can_algorithm/resources/generated_resources/UNECE/matrix_defs.h"
#include "ext/can_algorithm/src/include/ids_results.h"
#include "ext/can_algorithm/src/include/ids_timing_analyzer.h"
// #include "PeriodicSensorData.hpp"


#define COUNTER_NAME_UNK_MSG      ("UNK_MSG_CONST")
#define COUNTER_NAME_NEW_EVENT    ("CAN Event created")
#define PDU_EVENT_RATE_COUNTER    ("PDU analyzer - event rate")
#define PDU_EVENT_TIME_SPENT      ("PDU analyzer - time spent")
#define PDU_EVENT_CREATION_FAILED ("PDU analyzer - shaper add failed")
// using PeriodicSd = sensor_data::PeriodicSensorData;

namespace brain
{
namespace engines
{
constexpr char CanPduAlgoEngine::pduPopFromQueue[];
CanPduAlgoEngine::CanPduAlgoEngine(ConfigurationPtr                                        config,
                     std::shared_ptr<brain::messageRepository::MessageRepositoryInterface> msgRepository,
                     IDSPeriodicReportSerializerPtr                                        reportSerializer,
                     EventPriority                                                         priority)
  : m_canPduEventEngine(msgRepository,reportSerializer,priority), m_idsConfig(config)
{
    // m_canIdToCounter.clear();
    // Initialize counters for tracking events related to CAN PDU handling
    // m_popPduFromQueueCounter = mebCounters->GetCounter(CanPduAlgoEngine::pduPopFromQueue);
    // if (nullptr == m_popPduFromQueueCounter)
    // {
    //     LOG(CommonLogerLevel::kError) << "Invalid pduPopFromQueueCounter pointer";
    // }

    if (false == InitCanAnalyzer())
    {
        LOG_ERROR << "Failed to InitCanAnalyzer" << LOG_NOOP;
    }

    m_parser.ParserInit();

    m_state = std::make_shared<brain::can_pdu::CanPduState>(config);
}

bool
CanPduAlgoEngine::InitCanAnalyzer()
{
    /*|TODO retrive CAN ID's counters code here after add counters support*/


    // m_counterNewEvent = m_mebCounters->GetCounter(COUNTER_NAME_NEW_EVENT);
    // m_eventRateCounter = m_mebCounters->GetCounter(PDU_EVENT_RATE_COUNTER);
    // m_eventTimeCounter = m_mebCounters->GetCounter(PDU_EVENT_TIME_SPENT);
    // m_eventCreateFailed = m_mebCounters->GetCounter(PDU_EVENT_CREATION_FAILED);
    // m_eventDropCounter = m_mebCounters->GetCounter(brain::config_keys::DROPPED_PDU_EVENTS_COUNTER);

    // // for diagnostics purposes
    // m_ruleACounter = m_mebCounters->GetCounter(brain::config_keys::RULE_A_COUNTER);
    // m_ruleBCounter = m_mebCounters->GetCounter(brain::config_keys::RULE_B_COUNTER);
    // m_ruleCCounter = m_mebCounters->GetCounter(brain::config_keys::RULE_C_COUNTER);
    // m_ruleECounter = m_mebCounters->GetCounter(brain::config_keys::RULE_E_COUNTER);
    // m_ruleFCounter = m_mebCounters->GetCounter(brain::config_keys::RULE_F_COUNTER);
    // m_ruleGCounter = m_mebCounters->GetCounter(brain::config_keys::RULE_G_COUNTER);

    // Getting the IDs of CAN messages that are muted and not supposed to be processed
    std::vector<uint32_t> mutedCanIdsVec;
    static_cast<void>(m_idsConfig->GetValue(brain::config_keys::CAN_ALGORITHM_MUTED_CAN_IDS, mutedCanIdsVec));

    // Insert muted CAN IDs into a set for faster search operations during analysis
    for (uint32_t canId : mutedCanIdsVec)
    {
        m_mutedCanIds.insert(canId);
    }

    // Load the CAN matrix that contains the mapping between CAN IDs and corresponding data
    load_can_matrix();

    return true;
}

ReturnCode
CanPduAlgoEngine::processInternal(common::sensor_data::UPSensorData sd)
{
    if (sd->GetTag() == SdTag::SD_CAN_PDU_PERIODIC_EVENT)
    {
        return HandlePeriodicCanSensorData(std::move(sd));
    }
    else if (sd->GetTag() == SdTag::SD_CAN_PDU_EVENT)
    {
        return HandleCanPduSensorData(std::move(sd));
    }
    else
    {
        LOG_ERROR << "Invalid tag: " << unsigned(sd->GetTag()) << " recived by CanPduAlgoEngine" << LOG_NOOP;
        return ReturnCode::FailedError;
    }

    // If no issues were detected, return success
    return ReturnCode::Success;
    ;
}

bool
CanPduAlgoEngine::RunCanAnalyzer(PduPtr pdu, IDS_Result& algoRes, brain::can_pdu::CanEventEngineData& eventData)
{
    // Ensuring the 'doEvent' flag is initially set to false
    algoRes = RESULT_OK;

    // Extracting the message ID and timestamp from the PDU
    uint32_t const msgId        = pdu->GetMsgId();
    uint32_t const msgTimestamp = pdu->GetTimestamp();

    // Check if the current CAN ID is muted. If it's muted, it should not be checked for any issues.
    if (m_mutedCanIds.find(msgId) != m_mutedCanIds.end())
    {
        LOG_DEBUG << "CanID: " << m_mutedCanIds.size() << " is muted and won't be checked for attacks." << LOG_NOOP;
        return true;
    }

    // Running the CAN algorithm on the PDU payload and handle the result
    working_context_t working_context;
    algoRes = check_types_and_context(
        &working_context, msgTimestamp, (uint8_t*)pdu->GetPayload(), pdu->GetMsgIndex(), pdu->GetMsgType());

    // If an event was detected, the 'doEvent' flag will be set
    if (RESULT_OK != algoRes)
    {
        m_state->SetPeriodicStateDataFlag(false);
        eventData.m_pdu       = pdu;
        eventData.m_state     = m_state;
        eventData.m_result    = algoRes;
        eventData.m_timeStamp = msgTimestamp;
        eventData.m_canId     = msgId;
    }

    return true;
}

ReturnCode
CanPduAlgoEngine::HandlePeriodicCanSensorData(CommonSDPtr sd)
{
    if (nullptr == sd)
    {
        LOG_ERROR << "Invalid PeriodicSensorData pointer" << LOG_NOOP;
        return ReturnCode::FailedError;
    }
    // std::unique_ptr<PeriodicSd> periodicSd(static_cast<PeriodicSd *>(sd.release()));
    // LOG_INFO << "Can PDU Engine called to send CAN PDU Snapshot" << LOG_NOOP;

    // /* After the casting we can look at whether the SD came at shutdown - and in shutdown we should
    //  not send CAN state */
    // if (periodicSd->IsSentAtInterrupt())
    // {
    //     LOG_INFO << "CAN PDU Engine called at shutdown, skipping CAN State sending" << LOG_NOOP;
    //     return ReturnCode::FailedError;
    // }

    // m_state->SetPeriodicStateDataFlag(true);

    // CanEventEngineData eventData;
    // eventData.SetTag(SdTag::SD_CAN_ALGO_PDU);
    // eventData.m_state = m_state;
    // eventData.m_timeStamp = periodicSd->GetTimeMiliSeconds();
    // eventData.m_pdu = nullptr;
    // eventData.m_result = RESULT_OK;
    // eventData.m_canId = 0;

    // LOG_DEBUG << "creating CAN periodic event" << LOG_NOOP;

    // // Pass the algorithmic data to the successor for further processing
    // auto result = m_successor->HandleData(std::make_unique<CanEventEngineData>(eventData));

    // // Log error if passing the algorithmic data to the successor failed
    // if (CommonErrors::SUCCESS != result.GetResultCode())
    // {
    //     LOG_ERROR << "Failed to pass CAN periodic data to successor" << LOG_NOOP;
    //     return ReturnCode::FailedError;
    // }

    // return ReturnCode::Success;
}

ReturnCode
CanPduAlgoEngine::HandleCanPduSensorData(CommonSDPtr sd)
{
    std::unique_ptr<brain::can_pdu::CanPduData> canSensorData(static_cast<brain::can_pdu::CanPduData*>(sd.release()));

    brain::can_pdu::IdsFrame* frame = reinterpret_cast<brain::can_pdu::IdsFrame*>(canSensorData->m_buffer);

    std::vector<brain::can_pdu::CanPDU*> pduVec;

    // Parse the raw data and populate the algorithmic data
    bool res = m_parser.ParseAndCreatePdu(frame, pduVec);
    if (false == res)
    {
        // Parsing failed, log error and return an error result
        LOG_ERROR << "Failed to parse CanPduData" << LOG_NOOP;
    }

    if (!pduVec.empty())
    {

        LOG_DEBUG << "CanPduAlgoEngine recived: " << pduVec.size() << " PDU's" << LOG_NOOP;

        // For each PDU in the pduVec, add it to the state and then run the CAN analyzer
        for (auto& pdu : pduVec)
        {
            PduPtr const statedPdu = m_state->AddPdustream(pdu);

            // remove the PDU from the vector, in case of failure the sensor dada distructor will free the PDU
            // canSensorData->m_pduVec.erase(canSensorData->m_pduVec.begin());

            // If a PDU was successfully added to the state
            if (statedPdu != nullptr)
            {
                // Count the event of popping a PDU from the queue
                // static_cast<void>(m_popPduFromQueueCounter->CountEvent());

                IDS_Result                         canAlgoRes = RESULT_OK;
                brain::can_pdu::CanEventEngineData eventData;
                // Run the CAN analyzer on the PDU. If it fails, log an error and return.
                if (false == RunCanAnalyzer(statedPdu, canAlgoRes, eventData))
                {
                    LOG_ERROR << "Failed to run CanAnalyzer" << LOG_NOOP;
                }

                // updateCounters(*statedPdu, canAlgoRes);

                // IM-5211 - IDS_RESULT is a byte, so we do logic OR to check if CAN attack occured.
                m_isCanAttackOccured |= canAlgoRes;

                uint64_t const curTime = common::Time::GetCurrentTimeMilliSec();
                if ((curTime - m_lastUpdateTime) >= 1000U)
                {
                    if (RESULT_OK != m_isCanAttackOccured)
                    {
                        m_isCanAttackOccured = RESULT_OK;
                    }

                    // ASF - Bad casting
                    // m_eventRateCounter->SetEvent(((m_eventCounter * 1000U) / (curTime - m_lastUpdateTime)));
                    // m_eventTimeCounter->SetEvent(curTime - m_lastUpdateTime);
                    // m_eventCounter = 0U;
                    // m_lastUpdateTime = curTime;
                }

                // If an event was detected by the CAN analyzer, handle it
                if (canAlgoRes != RESULT_OK)
                {
                    m_state->CheckAndAddContext(statedPdu->GetMsgId());

                    LOG_DEBUG << "CAN anomaly detected, creating event" << LOG_NOOP;

                    // Pass the algorithmic data to the successor for further processing
                    auto result = m_canPduEventEngine.HandleData(std::make_unique<brain::can_pdu::CanEventEngineData>(eventData));

                    // Log error if passing the algorithmic data to the successor failed
                    if (ReturnCode::Success != result)
                    {
                        LOG_ERROR << "Failed to pass CAN event engine data to successor" << LOG_NOOP;
                        // static_cast<void>(m_eventDropCounter->CountEvent());
                        // static_cast<void>(m_eventCreateFailed->CountEvent());
                    }
                    else
                    {
                        // Count the event of creating a new event
                        // static_cast<void>(m_counterNewEvent->CountEvent());
                        // m_eventCounter++;
                    }

                    m_state->CheckAndRemoveContext(statedPdu->GetMsgId());
                }
            }
        }
    }
    return ReturnCode::Success;
}

// void CanPduAlgoEngine::countEventForSpecificRule(brain::data_unit::CanPDU &pdu, IDS_Result const canAlgoRes,
// IDS_Result const mask, std::shared_ptr<common::counters::MebEventCounter> counter)
// {
//     if (RESULT_OK != (canAlgoRes & mask))
//     {
//         counter->CountEvent();
//         // Leave counter here for attack monitoring
//         m_canCounters->CountEvent(
//             m_canIdToCounter[pdu.GetMsgId()],
//             mask,
//             pdu.GetMsgType(),
//             pdu.GetBusId(),
//             pdu.GetMsgId());
//     }
// }

// void CanPduAlgoEngine::updateCounters(brain::data_unit::CanPDU &pdu, IDS_Result const canAlgoRes)
// {
//     if (RESULT_OK == canAlgoRes)
//     {
//         m_canCounters->CountEvent(
//             m_canIdToCounter[pdu.GetMsgId()],
//             RESULT_OK,
//             pdu.GetMsgType(),
//             pdu.GetBusId(),
//             pdu.GetMsgId());
//         return;
//     }
//     countEventForSpecificRule(pdu, canAlgoRes, RESULT_MSG_EARLY_CYCLE, m_ruleACounter);
//     countEventForSpecificRule(pdu, canAlgoRes, RESULT_MSG_EARLY_INHIBIT, m_ruleBCounter);
//     countEventForSpecificRule(pdu, canAlgoRes, RESULT_SUSPICIOUS_BEHAVIOR, m_ruleCCounter);
//     countEventForSpecificRule(pdu, canAlgoRes, RESULT_ON_CHANGE_UNCHANGED, m_ruleECounter);
//     countEventForSpecificRule(pdu, canAlgoRes, RESULT_MSG_EARLY_CYCLE_FAST, m_ruleFCounter);
//     countEventForSpecificRule(pdu, canAlgoRes, RESULT_TOO_FEW_REPETITIONS, m_ruleGCounter);
// }
}  // namespace engines
}  // namespace brain