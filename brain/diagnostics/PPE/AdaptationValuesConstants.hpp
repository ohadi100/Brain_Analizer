#pragma once

#include <array>
#include <string>

namespace brain
{

namespace adaptation_values_names
{

using AdaptationNameType = std::string;

enum AdaptationId : uint8_t
{
    // Diag Adaptations -  0x7704
    LINK_UTILIZATION_MONITORING_ON = 0U,
    BROADCAST_MULTICAST_RATES_MONITORING_ON,
    DISCARDED_FRAMES_MONITORING_ON,
    IP_TRAFFIC_MONITORING_ON,
    TLS_SESSIONS_MONITORING_ON,
    MONITORING_OF_PROCESSES_ON,
    OS_MONITORING_ON,
    FILE_MONITORING_ON,
    HOST_ERROR_MONITORING_ON,
    SERVICE_LEVEL_MONITORING_ON,

    // Diag Adaptations, DataSet - 0x032e, 0x7231
    DIAGNOSTICS_IDS_ENABLED,

    ADAPTATIONS_COUNT
};

}  // namespace adaptation_values_names
}  // namespace brain