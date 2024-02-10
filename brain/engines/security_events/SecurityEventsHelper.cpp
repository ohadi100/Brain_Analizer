#include "SecurityEventsHelper.hpp"

using brain::engines::security_events::DropReason;

static std::unordered_map<DropReason, std::string>&&
initMap() noexcept
{
    static std::unordered_map<DropReason, std::string> newMap{
        {DropReason::SecurityEventSmallCommunicator, "SecurityEventSmallCommunicator"},
        {DropReason::SecurityEventNormalCommunicator, "SecurityEventNormalCommunicator"},
        {DropReason::SacidCanEventCommunicator, "SacidCanEventCommunicator"},
        {DropReason::SecurityEventsEngine, "SecurityEventsEngine"},
        {DropReason::SacidEventsEngine, "SacidEventsEngine"},
        {DropReason::IntelligentSensorEngine, "IntelligentSensorEngine"},
        {DropReason::SecurityEventSmallNoiseFilter, "SecurityEventSmallNoiseFilter"},
        {DropReason::SecurityEventNormalNoiseFilter, "SecurityEventNormalNoiseFilter"},
        {DropReason::SacidCanEventNoiseFilter, "SacidCanEventNoiseFilter"},
        {DropReason::IntelligentSensorNoiseFilter, "IntelligentSensorNoiseFilter"},
        {DropReason::PriorityQueueInvalid, "PriorityQueueInvalid"},
        {DropReason::PriorityQueueCritical, "PriorityQueueCritical"},
        {DropReason::PriorityQueueImportant, "PriorityQueueImportant"},
        {DropReason::PriorityQueueNormal, "PriorityQueueNormal"},
        {DropReason::PriorityQueueLow, "PriorityQueueLow"},
        {DropReason::DhmKernelLogNoiseFilter, "DhmKernelLogNoiseFilter"},
        {DropReason::DhmTlsErrorNoiseFilter, "DhmTlsErrorNoiseFilter"},
        {DropReason::DhmProcessPerformanceNoiseFilter, "DhmProcessPerformanceNoiseFilter"},
        {DropReason::GSDPCommunicator, "GSDPCommunicator"}};

    return std::move(newMap);
}

std::unordered_map<DropReason, std::string> const brain::engines::security_events::DropReasonMap = initMap();