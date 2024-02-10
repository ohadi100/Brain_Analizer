#ifndef EVENT_PRIORITY_HPP
#define EVENT_PRIORITY_HPP

#include <stdint.h>
#include <unordered_map>
#include "brain/engines/EngineId.hpp"


namespace brain
{
namespace events
{
using brain::engines::EngineId;

enum EventPriority : uint8_t
{
    Critical  = 0U,  // P0
    Important = 1U,  // P1
    Normal    = 2U,  // P2
    Low       = 3U,  // P3

    NUM_OF_EVENT_PRIORITIES
};

using EventPriorityMapType = std::unordered_map<EngineId, EventPriority>;

static EventPriorityMapType&&
initEventPriorityMap() noexcept
{
    static EventPriorityMapType newMap{{EngineId::PERIODIC_STATISTICS, EventPriority::Critical},
                                       {EngineId::SWPAC_TLS_ERROR_REPORT, EventPriority::Important},
                                       {EngineId::SWPAC_KERNEL_LOG, EventPriority::Important},
                                       {EngineId::SWPAC_PROCESS_PERFORMANCE, EventPriority::Important},
                                       {EngineId::SWPAC_UNKNOWN_CONSTRAINT_ID, EventPriority::Important},
                                       {EngineId::QLAH_ETH, EventPriority::Important},
                                       {EngineId::QLAH_HOST, EventPriority::Important},
                                       {EngineId::SECURITY_EVENT, EventPriority::Important},
                                       {EngineId::INTELLIGENT_SENSOR, EventPriority::Critical},
                                       {EngineId::SACID_EVENT, EventPriority::Important}};
    return std::move(newMap);
}

static EventPriorityMapType const EventPriorityMap = initEventPriorityMap();

}  // namespace events
}  // namespace brain

#endif  // EVENT_PRIORITY_HPP
