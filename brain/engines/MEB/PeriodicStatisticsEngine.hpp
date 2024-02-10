#pragma once

/**
 * @file
 * @brief This file contains the definition of the PeriodicStatisticsEngine class and its functionality
 */


#include "IDSPeriodicReportSerializer.hpp"
#include "MessageRepository.hpp"
#include "autogen/nanopb/NanoPbInclude.hpp"
#include "brain/engines/Engine.hpp"
#include "brain/events/EventPriority.hpp"

namespace brain
{

namespace engines
{

/**
 * @class   PeriodicStatisticsEngine
 * @brief   The PeriodicStatisticsEngine class defines the rule engine of the OS log Report analysis logic.
 *          The class defines and runs the process of the rule engines of the OS log Report analysis.
 */
class PeriodicStatisticsEngine final : public Engine
{
public:
    PeriodicStatisticsEngine(std::shared_ptr<brain::messageRepository::MessageRepositoryInterface> msgRepository,
                             IDSPeriodicReportSerializerPtr                                        reportSerializer,
                             events::EventPriority                                          priority);

protected:
    ReturnCode processInternal(common::sensor_data::UPSensorData) override;
    void       createRuleEvaluation(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval);

private:
    std::shared_ptr<brain::messageRepository::MessageRepositoryInterface> m_msgRepository;
    IDSPeriodicReportSerializerPtr m_serializer;
    events::EventPriority m_priority;

};
}  // namespace engines
}  // namespace brain
