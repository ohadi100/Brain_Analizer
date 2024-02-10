/**
 * @file      CanPduEventEngine.hpp
 * @brief     Definition of the CanPduEventEngine class
 */

#pragma once

// #include "common/counter_manager/MebCounterManager.h"
#include "autogen/nanopb/NanoPbInclude.hpp"
#include "brain/canPdu/CanPDU.hpp"
#include "brain/canPdu/CanPduData.hpp"
#include "ext/can_algorithm/src/include/ids_results.h"
#include "brain/engines/Engine.hpp"
#include "brain/events/EventPriority.hpp"
#include "brain/messageRepository/interface/MessageRepository.hpp"
#include "common/sensor_data/SensorData.hpp"
#include "brain/engines/serializer/IDSPeriodicReportSerializer.hpp"


namespace brain
{
namespace engines
{
using CommonSDPtr = common::sensor_data::UPSensorData;
// using MebCountersmanagerptr = std::shared_ptr<common::counters::MebCounterManager>;
// using MebEventCounterptr = std::shared_ptr<common::counters::MebEventCounter>;
using RuleData       = com_vwg_connect_ids_idsperiodicreport_v1_BusTimingAnomalyRuleData;
using RuleEvaluation = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation;
using EventPriority  = brain::events::EventPriority;
using ReturnCode     = brain::engines::ReturnCode;

/**
 * @class CanPduEventEngine
 * @brief This class is used for handling and managing CAN Protocol Data Unit (PDU) events.
 *
 * CanPduEventEngine is a part of engine plugin, which handles data passed through it and manages events related to CAN
 * PDU.
 */
class CanPduEventEngine
{
public:
    /**
     * @brief Constructor for CanPduEventEngine
     * @param successor A shared pointer to the successor in the chain of responsibility.
     * @param mebCounters A shared pointer to a MebCounterManager instance.
     */
    CanPduEventEngine(std::shared_ptr<brain::messageRepository::MessageRepositoryInterface> msgRepository,
                      IDSPeriodicReportSerializerPtr                                        reportSerializer,
                      EventPriority                                                         priority);

    /**
     * @brief Destructor for CanPduEventEngine
     */
    ~CanPduEventEngine();

    /**
     * @brief  function for handling data.
     * @param sd A shared pointer to SensorData.
     * @return A ReturnCode that contains the SensorData.
     */
    ReturnCode HandleData(CommonSDPtr sd);

private:
    /// Event related attributes are added based on the message type.
    void AddEventAttribut(const uint32_t msgType, const uint32_t index, RuleData& ruleData);

    ReturnCode handlePeriodicCanSensorData(std::unique_ptr<brain::can_pdu::CanEventEngineData> eventEngineData);
    ReturnCode handleCanPduSensorData(std::unique_ptr<brain::can_pdu::CanEventEngineData> eventEngineData);
    ReturnCode serializeAndPassCanEvent(RuleEvaluation ruleEval);

    std::shared_ptr<brain::messageRepository::MessageRepositoryInterface> m_msgRepository;
    IDSPeriodicReportSerializerPtr m_serializer;
    EventPriority m_priority;
};
}  // namespace engines
}  // namespace brain