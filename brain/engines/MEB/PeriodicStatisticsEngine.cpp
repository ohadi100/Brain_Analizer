/**
 * @file
 * @brief     This file contains the functionality of the PeriodicStatisticsEngine class
 */
#include "PeriodicStatisticsEngine.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "brain/events/Event.hpp"

namespace brain
{

namespace engines
{

PeriodicStatisticsEngine::PeriodicStatisticsEngine(
    std::shared_ptr<brain::messageRepository::MessageRepositoryInterface> msgRepository,
    IDSPeriodicReportSerializerPtr                                        reportSerializer,
    brain::events::EventPriority                                          priority)
  : m_msgRepository(msgRepository)
  , m_serializer(reportSerializer)
  , m_priority(priority)
{
}

void
PeriodicStatisticsEngine::createRuleEvaluation(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval)
{
    com_vwg_connect_ids_idsperiodicreport_v1_IdsStatisticsPeriodicReport statisticsPeriodicReport
        = com_vwg_connect_ids_idsperiodicreport_v1_IdsStatisticsPeriodicReport_init_default;

    ruleEval.ruleEvaluationId = m_currentTime;
    ruleEval.timestamp        = m_currentTime;
    ruleEval.which_RuleData   = static_cast<pb_size_t>(
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_idsStatisticsPeriodicReport_tag);
    ruleEval.RuleData.idsStatisticsPeriodicReport = statisticsPeriodicReport;
}

ReturnCode
PeriodicStatisticsEngine::processInternal(common::sensor_data::UPSensorData)
{
    com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation statisticReport
        = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;
    createRuleEvaluation(statisticReport);

    auto idsReport = m_serializer->Serialize(statisticReport);

    auto const& serializedIdsReport
        = common::nanopb::EncodeNanoPb<com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_fields>(idsReport);

    m_msgRepository->Push(std::make_unique<std::vector<uint8_t>>(*serializedIdsReport), m_priority);

    LOG_INFO << "Periodic event passed to send mechanism, report size: " << serializedIdsReport->size() << LOG_NOOP;

    return ReturnCode::Success;
}

}  // namespace engines
}  // namespace brain
