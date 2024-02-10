#pragma once
/**
 * @file
 * @brief This file contains the definition of the Critical Alert Filter class and its functionality
 */
#include <unordered_map>

#include "autogen/gsep/SecurityEvents.hpp"
#include "brain/config/AlertEventsNames.hpp"
#include "common/utils/CPP/Singleton.hpp"
#include "common/utils/HashUtils.hpp"
#include "common/utils/types/ConfigurationTypes.hpp"
#include "security_events/SecurityEventsCountersEntry.hpp"
#include "security_events/PassedDroppedAlertsNanoPB.hpp"

namespace brain
{
namespace engines
{

using brain::engines::security_events::SecurityEventsCountersEntry;

class CriticalAlertFilter : public common::utils::Singleton<CriticalAlertFilter>
{
public:
    using ConfigurationPtr = common::configuration::Pointer;

    struct PassedDropCounters
    {
        uint32_t passedCounter{};
        uint32_t filteredCounter{};
    };

    void Init(ConfigurationPtr const config);

    bool CanSend(brain::sender_events::CriticalEventAlert            event,
                 brain::engines::security_events::SecurityEventFrame frame = {});
    bool CanSend(brain::sender_events::CriticalEventAlert event, std::string const& id);

    bool Serialize(brain::engines::security_events::nanopb::PassedDroppedAlertsData& data, uint64_t timestamp);
    void ResetCounters();

private:
    void resetLimits();

    uint32_t getCriticalAlertlimit(brain::engines::security_events::SecurityEventFrame frame);

    uint32_t                                                               m_defaultAltertLimit{};
    uint32_t                                                               m_criticalSecurityEventAlertDefaultLimit{};
    uint32_t                                                               m_unknownEventIdAlertLimit{};
    uint32_t                                                               m_unknownEventIdAlertMaxNumber{};
    uint32_t                                                               m_dhmUnknownConstraintIdAlertLimit{};
    uint32_t                                                               m_dhmUnknownConstraintIdMaxNumber{};
    std::unordered_map<brain::sender_events::CriticalEventAlert, uint32_t> m_criticalEventsLimits{};
    std::unordered_map<SecurityEventsCountersEntry, uint32_t>              m_criticalSecurityEventAlertLimitsPerKey{};

    std::unordered_map<SecurityEventsCountersEntry, PassedDropCounters> m_criticalAlertCounter;
    std::unordered_map<SecurityEventsCountersEntry, PassedDropCounters> m_unknownEventIdAlertCounter;
    std::unordered_map<std::string, PassedDropCounters>                 m_dhmUnkownConstrainIdCounter;

    std::unordered_map<brain::sender_events::CriticalEventAlert, PassedDropCounters> m_otherAlertsCounter;
};

}  // namespace engines
}  // namespace brain
