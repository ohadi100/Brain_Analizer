#include "IncidentHelper.hpp"

using namespace brain::sensor_data::swpac;

static std::unordered_map<std::string, IncidentType>&&
initEventsTypes() noexcept
{
    static std::unordered_map<std::string, IncidentType> newMap{
        {"7ed8bdd6-0ebc-4a2c-bc0a-57b314310329", IncidentType::KERNEL_LOG},
        {"9446b4d9-6998-43ee-9f10-08a9ecd45535", IncidentType::TLS_ERROR_REPORTING},
        {"393cc2c6-e412-4414-9d72-65df787487ef", IncidentType::PROCESS_PERFORMANCE}};
    return std::move(newMap);
}
std::unordered_map<std::string, IncidentType> const brain::sensor_data::swpac::EventsTypes = initEventsTypes();

static std::unordered_map<std::string, ConstraintId>&&
initConstraintIdMap() noexcept
{
    static std::unordered_map<std::string, ConstraintId> newMap{
        {"75b9b0cf-ce50-4f7b-8b9f-154ca60b4a13", ConstraintId::KERNEL_LOG_KERNEL_PANIC},
        {"4ee61796-79fc-454b-8dc1-d5e09b04f316", ConstraintId::TLS_ERROR_REPORT},
        {"51c8b12d-c62f-4a7c-872f-70aa9d17184e", ConstraintId::PROCESS_PERFORMANCE}};
    return std::move(newMap);
}
std::unordered_map<std::string, ConstraintId> const brain::sensor_data::swpac::ConstraintIdMap = initConstraintIdMap();

std::string const&
brain::sensor_data::swpac::GetConstraintIdString(ConstraintId type)
{
    static std::string const unknownId{"Unknown"};

    for (const auto& pair : brain::sensor_data::swpac::ConstraintIdMap)
    {
        if (pair.second == type)
        {
            return pair.first;
        }
    }

    return unknownId;
}