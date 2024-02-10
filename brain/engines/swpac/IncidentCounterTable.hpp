/**
 * @file
 * @brief Implementation for counting dhm incidents that are processed
 */

#ifndef INCIDENT_COUNTER_TABLE
#define INCIDENT_COUNTER_TABLE

#include <string>
#include <unordered_map>
#include <memory>
#include "IncidentHelper.hpp"
#include "autogen/nanopb/NanoPbInclude.hpp"

namespace brain
{
namespace engines
{
namespace swpac
{

class IncidentCounterTable final
{

public:
    IncidentCounterTable()  = default;
   
    /**
     * @brief incement the incident counter for specific dhm incident key
     * @param sensor_data::swpac::ConstraintId incident - incident constraint id
     * @return none
     */
    void Increment(sensor_data::swpac::ConstraintId incident);

    /**
     * @brief serialize the proto DhmIncidentsCountersTable
     * @param com_vwg_connect_ids_idsperiodicreport_v1_DhmIncidentsCountersTable& table - proto dhm incident counter
     * table
     * @return none
     */
    bool Serialize(com_vwg_connect_ids_idsperiodicreport_v1_DhmIncidentsCountersTable& table);

    /**
     * @brief clear the incident counter values
     * @param none
     * @return none
     */
    inline void clear()
    {
        m_incidents.clear();
    }

private:
    static bool encodeDhmIncidentsCountersTable(pb_ostream_t* stream, pb_field_t const* fields, void* const* arg);

    std::unordered_map<brain::sensor_data::swpac::ConstraintId, uint32_t> m_incidents;
};

using SPIncidentCounterTable = std::shared_ptr<brain::engines::swpac::IncidentCounterTable>;

}  // namespace swpac
}  // namespace engines
}  // namespace brain

#endif  // INCIDENT_COUNTER_TABLE