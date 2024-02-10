/**
 * @file
 * @brief     This file contains the definition of the heper functions needed for Security Events.
 */

#ifndef SECURITY_EVENTS_HELPER_HPP
#define SECURITY_EVENTS_HELPER_HPP

#include <cstdint>
#include <string>
#include <unordered_map>
#include "common/utils/HashUtils.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

/// @brief Drop reason enumeration
enum class DropReason : uint8_t
{
    SecurityEventSmallCommunicator,
    SecurityEventNormalCommunicator,
    SacidCanEventCommunicator,
    IntelligentSecurityEventCommunicator,
    SecurityEventsEngine,
    SacidEventsEngine,
    IntelligentSensorEngine,
    SecurityEventSmallNoiseFilter,
    SecurityEventNormalNoiseFilter,
    SacidCanEventNoiseFilter,
    IntelligentSensorNoiseFilter,
    PriorityQueueInvalid,
    PriorityQueueCritical,
    PriorityQueueImportant,
    PriorityQueueNormal,
    PriorityQueueLow,
    DhmKernelLogNoiseFilter,
    DhmTlsErrorNoiseFilter,
    DhmProcessPerformanceNoiseFilter,
    GSDPCommunicator,
};

extern std::unordered_map<DropReason, std::string> const DropReasonMap;

}  // namespace security_events
}  // namespace engines
}  // namespace brain

#endif  // SECURITY_EVENTS_HELPER_HPP