#include "IncidentCounterTable.hpp"
#include "brain/utils/nanopb/Encoders.hpp"

using brain::engines::swpac::IncidentCounterTable;
using brain::sensor_data::swpac::ConstraintId;

void
IncidentCounterTable::Increment(ConstraintId incident)
{
    const auto& it = m_incidents.emplace(std::piecewise_construct, std::forward_as_tuple(incident), std::forward_as_tuple(0U));

    it.first->second += 1U;
}

bool
IncidentCounterTable::Serialize(com_vwg_connect_ids_idsperiodicreport_v1_DhmIncidentsCountersTable& table)
{
    if (!m_incidents.empty())
    {
        table.dhmIncidentsCountersEntry.funcs.encode = &encodeDhmIncidentsCountersTable;
        table.dhmIncidentsCountersEntry.arg          = static_cast<void*>(&m_incidents);

        return true;
    }

    return false;
}

bool
IncidentCounterTable::encodeDhmIncidentsCountersTable(pb_ostream_t* stream, pb_field_t const* fields, void* const* arg)
{
    auto const& incidents
        = **reinterpret_cast<std::unordered_map<ConstraintId, uint32_t>* const*>(arg);

    for (auto const& incident : incidents)
    {
        com_vwg_connect_ids_idsperiodicreport_v1_DhmIncidentsCountersEntry entry
            = com_vwg_connect_ids_idsperiodicreport_v1_DhmIncidentsCountersEntry_init_default;

        entry.constraintId
            = common::nanopb::CreateEncodingCallback(brain::sensor_data::swpac::GetConstraintIdString(incident.first));
        entry.count = incident.second;

        if ((!pb_encode_tag_for_field(stream, fields))
            || (!pb_encode_submessage(
                stream, com_vwg_connect_ids_idsperiodicreport_v1_DhmIncidentsCountersEntry_fields, &entry)))
        {
            return false;
        }
    }

    return true;
}
