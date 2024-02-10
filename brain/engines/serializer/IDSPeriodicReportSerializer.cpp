#include "IDSPeriodicReportSerializer.hpp"

using namespace brain::engines;

cm::optional<std::vector<uint8_t>>
    IDSPeriodicReportSerializer::Serialize(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval)
{
        std::string vehicleGuid;
        std::string vehicleType;
        auto const idsVersion{m_vehicleData.GetIdsVersion()};

        m_vehicleData.GetVehicleGuid(vehicleGuid);
        m_vehicleData.GetVehicleType(vehicleType);

        IDSPeriodicReport report = com_vwg_connect_ids_idsperiodicreport_v1_IDSPeriodicReport_init_default;

        report.vehicleId           = common::nanopb::CreateEncodingCallback(vehicleGuid);
        report.vehicleType         = common::nanopb::CreateEncodingCallback(vehicleType);
        report.idsVersion          = common::nanopb::CreateEncodingCallback(idsVersion);
        
        m_ruleEvaluations = {ruleEval};
        report.ruleEvaluations.funcs.encode = &encodeIdsPeriodicReport;
        report.ruleEvaluations.arg          = static_cast<void*>(&m_ruleEvaluations);

        return common::nanopb::EncodeNanoPb<com_vwg_connect_ids_idsperiodicreport_v1_IDSPeriodicReport_fields>(report);
}

bool IDSPeriodicReportSerializer::encodeIdsPeriodicReport(pb_ostream_t* stream, pb_field_t const* fields, void* const* arg)
{
    auto const& ruleEvaluations
        = **reinterpret_cast<std::array<com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation, 1U>* const*>(arg);

    for (auto const& ruleEvaluation : ruleEvaluations)
    {
        com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation entry
            = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_init_default;

        entry = ruleEvaluation;

        if ((!pb_encode_tag_for_field(stream, fields))
            || (!pb_encode_submessage(
                stream, com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation_fields, &entry)))
        {
            return false;
        }
    }

    return true;
}
