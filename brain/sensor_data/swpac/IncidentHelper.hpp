#ifndef INCIDENT_HELPER_HPP
#define INCIDENT_HELPER_HPP

#include <unordered_map>
#include <string>

namespace brain
{
namespace sensor_data
{
namespace swpac
{

enum class IncidentType : uint8_t
{
    KERNEL_LOG = 1U,
    TLS_ERROR_REPORTING,
    PROCESS_PERFORMANCE
};

enum class ConstraintId : uint8_t
{
    KERNEL_LOG_KERNEL_PANIC = 1U,
    TLS_ERROR_REPORT,
    PROCESS_PERFORMANCE,
    UNDEFINED_CONSTRAINTID
};

extern std::unordered_map<std::string, IncidentType> const EventsTypes;
extern std::unordered_map<std::string, ConstraintId> const ConstraintIdMap;
std::string const& GetConstraintIdString(ConstraintId type);

}  // namespace swpac
}  // namespace sensor_data
}  // namespace brain

#endif //INCIDENT_HELPERS_HPP