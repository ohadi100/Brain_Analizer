#pragma once
/**
 * @file
 * @brief     Serialize the proto IDS periodic report
 */

#include <memory>
#include "autogen/nanopb/NanoPbInclude.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "brain/utils/vehicle_data/VehicleData.hpp"
#include "common/utils/types/ConfigurationTypes.hpp"

namespace brain
{

namespace engines
{

class IDSPeriodicReportSerializer
{
public:
    using VehicleData       = brain::brain_vehicle_data::VehicleData;
    using ConfigurationPtr  = common::configuration::Pointer;
    using IDSPeriodicReport = com_vwg_connect_ids_idsperiodicreport_v1_IDSPeriodicReport;

    explicit IDSPeriodicReportSerializer(ConfigurationPtr configuration)
      : m_vehicleData{configuration}
    {
    }

    /**
     * @brief proto serialize ids periodic report
     * @param com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation - proto rule evaluation
     * @return cm::optional<std::vector<uint8_t>> - serialized proto ids periodic report
     */
    cm::optional<std::vector<uint8_t>> Serialize(
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval);

private:
    static bool encodeIdsPeriodicReport(pb_ostream_t* stream, pb_field_t const* fields, void* const* arg);

    VehicleData                                                            m_vehicleData;
    std::array<com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation, 1U> m_ruleEvaluations;
};

using IDSPeriodicReportSerializerPtr = std::shared_ptr<brain::engines::IDSPeriodicReportSerializer>;

};  // namespace engines

};  // namespace brain