#include "CanPduEventEngine.hpp"
#include "Time.hpp"
#include "Encoders.hpp"

#include "ext/can_algorithm/src/include/mqb_can_types.h"
#include "ext/can_algorithm/src/include/mqb_lib_interface.h"
#include "Event.hpp"

using EventAsSensorData = brain::events::Event;
using EventAsSensorDataPtr = std::unique_ptr<EventAsSensorData>;

// using EventFactory = brain::events::EventFactory;

namespace brain
{
    namespace engines
    {
        CanPduEventEngine::CanPduEventEngine(std::shared_ptr<brain::messageRepository::MessageRepositoryInterface> msgRepository,
                                            IDSPeriodicReportSerializerPtr                                        reportSerializer,
                                            EventPriority                                                        priority) : 
                                            m_msgRepository(msgRepository), m_serializer(reportSerializer) ,m_priority(priority)
        {
        }

        CanPduEventEngine::~CanPduEventEngine()
        {
        }

        ReturnCode CanPduEventEngine::HandleData(CommonSDPtr sd)
        {

            LOG_DEBUG << "CanPduEventEngine Creating CAN event" <<LOG_NOOP;

            std::unique_ptr<brain::can_pdu::CanEventEngineData> canEventData(static_cast<brain::can_pdu::CanEventEngineData *>(sd.release()));

            // if pdu is null then it is periodic data
            if (nullptr == canEventData->m_pdu)
            {
                return handlePeriodicCanSensorData(std::move(canEventData));
            }
            else
            {
                return handleCanPduSensorData(std::move(canEventData));
            }

            // If no issues were detected, return success.
            return ReturnCode::Success;
        }

        ReturnCode CanPduEventEngine::handlePeriodicCanSensorData(std::unique_ptr<brain::can_pdu::CanEventEngineData> eventEngineData)
        {
            auto timestamp = eventEngineData->m_timeStamp;

            com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation ruleEval = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;

            ruleEval.ruleEvaluationId = timestamp;
            ruleEval.timestamp = timestamp;

            ruleEval.which_RuleData = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_stateCaptureRuleData_tag;
            ruleEval.RuleData.stateCaptureRuleData.isExists = true;
            ruleEval.state = eventEngineData->m_state->GetAllStateData();

            auto result = serializeAndPassCanEvent(ruleEval);
            if (ReturnCode::Success != result)
            {
                LOG_ERROR << "Failed to serialize CAN event to successor" << LOG_NOOP; 
                return result;
            }

            // If no issues were detected, return success.
            return ReturnCode::Success;
        }

        ReturnCode CanPduEventEngine::handleCanPduSensorData(std::unique_ptr<brain::can_pdu::CanEventEngineData> eventEngineData)
        {
            // Initialize the RuleEvaluation data structure.
            RuleEvaluation ruleEvaluation = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;

            // Set the RuleData field in the RuleEvaluation structure.
            ruleEvaluation.which_RuleData = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_busTimingAnomalyRuleData_tag;
            auto &timingAnomalyEvent = ruleEvaluation.RuleData.busTimingAnomalyRuleData;

            // Initialize the BusTimingAnomalyRuleData structure.
            timingAnomalyEvent = com_vwg_connect_ids_idsperiodicreport_v1_BusTimingAnomalyRuleData_init_default;

            // Get the PDU from the CanEventEngineData.
            brain::can_pdu::CanPDU *pdu = eventEngineData->m_pdu;

            // Set the fields in the BusTimingAnomalyRuleData structure.
            timingAnomalyEvent.canId = eventEngineData->m_canId;
            timingAnomalyEvent.timestamp = eventEngineData->m_timeStamp;
            timingAnomalyEvent.rule = eventEngineData->m_result;
            timingAnomalyEvent.busId = pdu->GetBusId();
            timingAnomalyEvent.msgType = pdu->GetMsgType();

            // Add the event attribute based on the PDU's MsgType and CanIndex.
            AddEventAttribut(pdu->GetMsgType(), pdu->GetCanIndex(), timingAnomalyEvent);

            // Update the RuleData field in the RuleEvaluation structure.
            ruleEvaluation.RuleData.busTimingAnomalyRuleData = timingAnomalyEvent;

            ruleEvaluation.state = eventEngineData->m_state->GetAllStateData();

            auto result = serializeAndPassCanEvent(ruleEvaluation);
            if (ReturnCode::Success != result)
            {
                LOG_ERROR << "Failed to serialize CAN event to successor" << LOG_NOOP;
                return result;
            }

            // If no issues were detected, return success.
            return ReturnCode::Success;
        }

        ReturnCode CanPduEventEngine::serializeAndPassCanEvent(RuleEvaluation ruleEval)
        {

            // Set the state fields in the RuleEvaluation structure.
            ruleEval.has_state = true;

            // Encode the RuleEvaluation data structure into a binary format.
            // Create a new Event object with the serialized data and priority using the event factory.

            auto idsReport = m_serializer->Serialize(ruleEval);

            auto const& serializedIdsReport
                = common::nanopb::EncodeNanoPb<com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_fields>(idsReport);


            LOG_DEBUG << "Created CAN event" << LOG_NOOP;

            // Send the Event to the next link in the chain.
            //auto result = m_successor->HandleData(std::move(event));
            bool result =m_msgRepository->Push(std::make_unique<std::vector<uint8_t>>(*serializedIdsReport), m_priority);

            if (true != result)
            {
                LOG_ERROR << "Failed to pass CAN event to successor" << LOG_NOOP;
                return ReturnCode::FailedError;
            }

            // If no issues were detected, return success.
            return ReturnCode::Success;
        }

        void CanPduEventEngine::AddEventAttribut(const uint32_t msgType, const uint32_t index, RuleData &ruleData)
        {
            // Depending on the message type, extract the correct data structure and set the fields in the RuleData structure.
            switch (msgType)
            {
            case MSG_TYPE_1:
            {
                type_1_ct const data = get_data_type1(index);
                ruleData.cycleTime = data.cycle_time;
                ruleData.bzByteOffset = data.bz_byte_offset;
            }
            break;
            case MSG_TYPE_2or3:
            {
                type_2and3_ct const data = get_data_type2and3(index);
                ruleData.cycleTime = data.cycle_time;
                ruleData.bzByteOffset = data.bz_byte_offset;
                ruleData.inhibitTime = data.inhibit_time;
            }
            break;
            case MSG_TYPE_4or5:
            {
                type_4and5_ct const data = get_data_type4and5(index);
                ruleData.cycleTime = data.cycle_time;
                ruleData.bzByteOffset = data.bz_byte_offset;
                ruleData.inhibitTime = data.inhibit_time;
                ruleData.fastCycle = data.fast_cycle;
                ruleData.numOfRepetitions = data.num_of_repetitions;
            }
            break;
            case MSG_TYPE_6:
            {
                type_6_ct const data = get_data_type6(index);
                ruleData.cycleTime = data.cycle_time;
                ruleData.bzByteOffset = data.bz_byte_offset;
                ruleData.fastCycle = data.fast_cycle;
            }
            break;
#ifdef NUM_OF_TYPE_7_MESSAGES
            case MSG_TYPE_7:
            {
                type_7_ct const data = get_data_type7(index);
                ruleData.cycleTime = data.cycle_time;
                ruleData.bzByteOffset = data.bz_byte_offset;
                ruleData.fastCycle = data.fast_cycle;
                ruleData.numOfRepetitions = data.num_of_repetitions;
            }
            break;
#endif
            default:
            {
                ruleData.cycleTime = 0;
                ruleData.bzByteOffset = 0;
                ruleData.inhibitTime = 0;
                ruleData.fastCycle = 0;
                ruleData.numOfRepetitions = 0;
            }
            break;
            }
        }
    } // namespace engine
} // namespace plugins