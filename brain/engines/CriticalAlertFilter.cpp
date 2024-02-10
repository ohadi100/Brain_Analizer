/**
 * @file
 * @brief This file contains the functionality of the Critical Alert Filter class
 */
#include "CriticalAlertFilter.hpp"

#include "autogen/gsep/SecurityEvents.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/utils/logger/Logger.hpp"

using namespace brain::engines;
using namespace brain::sender_events;
using namespace brain::engines::security_events;
using brain::engines::security_events::nanopb::PassedDroppedAlertsData;
using brain::engines::security_events::nanopb::PassedDroppedCountersNPB;

namespace brain
{
namespace engines
{

static constexpr uint32_t DEFAULT_AGGREGATE_ALERT_LIMIT{100U};

static void
SerializePassedDroppedCounters(PassedDroppedCountersNPB&               passedDroppedCounters,
                               CriticalAlertFilter::PassedDropCounters entry)
{
    passedDroppedCounters.passedCounter   = entry.passedCounter;
    passedDroppedCounters.filteredCounter = entry.filteredCounter;
}

static void
SerializeAlertDataEntry(brain::engines::security_events::nanopb::PassedDroppedAlertsData&             data,
                        std::pair<CriticalEventAlert, CriticalAlertFilter::PassedDropCounters> const& entry)
{
    switch (entry.first)
    {
    case CriticalEventAlert::DroppedUnknownEventIdAlertThatExceededMaxNumber:
        data.droppedUnknownEventIdAlertThatExceededMaxNumber = entry.second.filteredCounter;
        break;
    case CriticalEventAlert::ExcessiveProcessMemoryUsage:
        SerializePassedDroppedCounters(data.processMemoryUsageAlertPassedDroppedCounters,
                                       entry.second);
        break;
    case CriticalEventAlert::SuspiciousAlertEventName:
        SerializePassedDroppedCounters(data.suspiciousEcuUnlockSuccessfulAlertPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::HCP3HostSensorTimeoutAlert:
        SerializePassedDroppedCounters(data.serviceIntegrationKeepaliveTimeoutAlertPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::DenialOfServiceAlert:
        SerializePassedDroppedCounters(data.dosDetectorReportPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::HostErrorMonitoring:
        SerializePassedDroppedCounters(data.hostErrorMonitoringReportPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::IntelligentEventName:
        SerializePassedDroppedCounters(data.intelligentSensorEventPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::ExcessiveProcessCpuUsage:
        SerializePassedDroppedCounters(data.processCpuUsageAlertPassedDroppedCounters,
                                       entry.second);
        break;
    // both LinkUtilization alerts are seriezlied in linkUtilizationAlertPassedDroppedCounters entry
    case CriticalEventAlert::LinkUtilizationOutTraffic:
    // [[fallthrough]];
    case CriticalEventAlert::LinkUtilizationInTraffic:
        SerializePassedDroppedCounters(data.linkUtilizationAlertPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::SecevKeepaliveTimeoutAlert:
        SerializePassedDroppedCounters(data.secEventKeepAliveTimeoutAlertPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::ErroneousServiceRegistration:
        SerializePassedDroppedCounters(data.erroneousServiceRegistrationAlertPassedDroppedCounters, entry.second);
        break;
    // all Nat alerts are seriezlied in natTableAlertPassedDroppedCounters entry
    case CriticalEventAlert::NatFloodingAlertText:
    // [[fallthrough]];
    case CriticalEventAlert::NatEntryNotFountAlertText:
    // [[fallthrough]];
    case CriticalEventAlert::NatDuplicateEntryText:
        SerializePassedDroppedCounters(data.natTableAlertPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::DoubleMacToIpEventName:
        SerializePassedDroppedCounters(data.doubledMacToIpAlertPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::SuspiciousProcessCrashRate:
        SerializePassedDroppedCounters(data.suspiciousProcessCrashRateAlertPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::SuspiciousAggregateCrashRate:
        SerializePassedDroppedCounters(data.suspiciousAggregateCrashRateAlertPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::SacidEventsEngine:
        SerializePassedDroppedCounters(data.canControllerErroStateAlertPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::OSLogKernelPanic:
        SerializePassedDroppedCounters(data.dhmOsLogRegexKernelPanicAlertPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::TLSErrorReport:
        SerializePassedDroppedCounters(data.dhmTerIncidentAlertPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::DhmStringSizeLimit:
        SerializePassedDroppedCounters(data.dhmIncidentStringSizeAlertPassedDroppedCounters, entry.second);
        break;
    case CriticalEventAlert::DhmUnkownConstrainIdMaxNumber:
        data.droppedDhmIncidentWithUnknownConstraintIdAlertThatExceededMaxNumber = entry.second.filteredCounter;
        break;
    case CriticalEventAlert::QlahUnknownProtocolFramesValue:
        SerializePassedDroppedCounters(data.unknownProtocolDroppedFramesCounterAlertPassedDroppedCounters,
                                       entry.second);
        break;
    case CriticalEventAlert::QlahIllegalVlanFrame:
        SerializePassedDroppedCounters(data.illegalVlanDropValueAlertPassedDroppedCounters, entry.second);
        break;
    default:
        LOG_WARNING << "Missing serialize function for alert " << static_cast<uint16_t>(entry.first) << LOG_NOOP;
    }
}

static void
SerializeSecEventAlertPassedDroppedCounters(
    brain::engines::security_events::nanopb::SecEventAlertPassedDroppedCounters&           passedDroppedCounter,
    std::pair<SecurityEventsCountersEntry, CriticalAlertFilter::PassedDropCounters> const& entry)
{
    passedDroppedCounter.eventDefinitionId                     = entry.first.GetSecurityEventId();
    passedDroppedCounter.idsMInstanceID                        = entry.first.GetIdsMInstanceId();
    passedDroppedCounter.sensorInstanceID                      = entry.first.GetSensorInstanceId();
    passedDroppedCounter.passedDroppedCounters.passedCounter   = entry.second.passedCounter;
    passedDroppedCounter.passedDroppedCounters.filteredCounter = entry.second.filteredCounter;
}

static void
SerializeDhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters(
    brain::engines::security_events::nanopb::DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters&
                                                                           passedDroppedCounter,
    std::pair<std::string, CriticalAlertFilter::PassedDropCounters> const& entry)
{
    passedDroppedCounter.ConstraintId                          = entry.first;
    passedDroppedCounter.passedDroppedCounters.passedCounter   = entry.second.passedCounter;
    passedDroppedCounter.passedDroppedCounters.filteredCounter = entry.second.filteredCounter;
}
}  // namespace engines
}  // namespace brain


void CriticalAlertFilter::resetLimits()
{
    m_defaultAltertLimit = DEFAULT_AGGREGATE_ALERT_LIMIT;
    m_criticalSecurityEventAlertDefaultLimit = 0U;
    m_unknownEventIdAlertLimit = 0U;
    m_unknownEventIdAlertMaxNumber = 0U;
    m_dhmUnknownConstraintIdAlertLimit = 0U;
    m_dhmUnknownConstraintIdMaxNumber = 0U;
    m_criticalEventsLimits.clear();
    m_criticalSecurityEventAlertLimitsPerKey.clear();
}

void
CriticalAlertFilter::Init(ConfigurationPtr const config)
{
    auto getConfigParam = [config](brain::config_keys::ConfigKeyType& key, auto& param, auto defaultParam) {
        if (!config || !config->GetValue(key, param))
        {
            LOG_WARNING << key << " couldn't be parsed from configuration file" << LOG_NOOP;
            param = defaultParam;
        }
        LOG_DEBUG << key << " configured: " << param << LOG_NOOP;
    };

    resetLimits();

    getConfigParam(brain::config_keys::DEFAULT_ALERT_LIMIT, m_defaultAltertLimit, DEFAULT_AGGREGATE_ALERT_LIMIT);
    
    getConfigParam(brain::config_keys::CRITICAL_SECURITY_EVENT_ALERT_DEFAULT_LIMIT,
                   m_criticalSecurityEventAlertDefaultLimit,
                   m_defaultAltertLimit);
    getConfigParam(brain::config_keys::UNKNOWN_EVENT_ID_ALERT_LIMIT, m_unknownEventIdAlertLimit, m_defaultAltertLimit);
    getConfigParam(brain::config_keys::UNKNOWN_EVENT_ID_ALERT_MAX_NUMBER,
                   m_unknownEventIdAlertMaxNumber,
                   m_unknownEventIdAlertLimit);

    std::vector<std::vector<uint32_t>> eventLimitPerKey;
    std::ignore = config->GetValue(brain::config_keys::CRITICAL_SECURITY_EVENT_ALERT_LIMITS_PER_KEY, eventLimitPerKey);

    static constexpr size_t CRITICAL_SECURITY_EVENT_ALERT_LIMITS_KEY_SIZE{4U};

    for (auto const& limitValues : eventLimitPerKey)
    {
        if (limitValues.size() == CRITICAL_SECURITY_EVENT_ALERT_LIMITS_KEY_SIZE)
        {
            SecurityEventsCountersEntry entry{static_cast<uint16_t>(limitValues[0U]),
                                              static_cast<uint8_t>(limitValues[1U]),
                                              static_cast<uint16_t>(limitValues[2U])};
            m_criticalSecurityEventAlertLimitsPerKey[entry] = limitValues[3U];
        }
        else
        {
            LOG_INFO << "Invalid key size " << limitValues.size()
                     << " found in CRITICAL_SECURITY_EVENT_ALERT_LIMITS_PER_KEY" << LOG_NOOP;
        }
    }

    getConfigParam(brain::config_keys::DHM_OS_LOG_REGEX_KERNEL_PANIC_ALERT_LIMIT,
                   m_criticalEventsLimits[CriticalEventAlert::OSLogKernelPanic],
                   m_defaultAltertLimit);
    getConfigParam(brain::config_keys::DHM_TER_INCIDENT_ALERT_LIMIT,
                   m_criticalEventsLimits[CriticalEventAlert::TLSErrorReport],
                   m_defaultAltertLimit);
    getConfigParam(brain::config_keys::DHM_INCIDENT_STRING_SIZE_ALERT_LIMIT,
                   m_criticalEventsLimits[CriticalEventAlert::DhmStringSizeLimit],
                   m_defaultAltertLimit);
    getConfigParam(brain::config_keys::DHM_Incident_With_Unknown_Constraint_Id_Alert_Limit,
                   m_dhmUnknownConstraintIdAlertLimit,
                   m_defaultAltertLimit);
    getConfigParam(brain::config_keys::DHM_Incident_With_Unknown_Constraint_Id_Alert_Max_Number,
                   m_dhmUnknownConstraintIdMaxNumber,
                   m_dhmUnknownConstraintIdAlertLimit);
    getConfigParam(brain::config_keys::QLAH_Unknown_Protocol_Dropped_Frames_Counter_Alert_Limit,
                   m_criticalEventsLimits[CriticalEventAlert::QlahUnknownProtocolFramesValue],
                   m_defaultAltertLimit);
    getConfigParam(brain::config_keys::QLAH_ILLEGAL_VLAN_DROP_VALUE_Alert_limit,
                   m_criticalEventsLimits[CriticalEventAlert::QlahIllegalVlanFrame],
                   m_defaultAltertLimit);

    ResetCounters();
}

uint32_t
CriticalAlertFilter::getCriticalAlertlimit(SecurityEventFrame frame)
{
    uint32_t                    rc{m_criticalSecurityEventAlertDefaultLimit};
    SecurityEventsCountersEntry entry{frame.idsMInstanceID, frame.sensorInstanceID, frame.eventDefinitionId};
    if (m_criticalSecurityEventAlertLimitsPerKey.find(entry) != m_criticalSecurityEventAlertLimitsPerKey.end())
    {
        rc = m_criticalSecurityEventAlertLimitsPerKey[entry];
    }

    return rc;
}

bool
CriticalAlertFilter::CanSend(CriticalEventAlert event, SecurityEventFrame frame)
{
    bool isLimitNotReached{false};

    if (CriticalEventAlert::CriticalEventName == event)
    {
        SecurityEventsCountersEntry entry{frame.idsMInstanceID, frame.sensorInstanceID, frame.eventDefinitionId};
        auto const                  it = m_criticalAlertCounter.emplace(
            std::piecewise_construct, std::forward_as_tuple(entry), std::forward_as_tuple(PassedDropCounters{}));

        if (getCriticalAlertlimit(frame) > it.first->second.passedCounter)
        {
            it.first->second.passedCounter += 1U;
            isLimitNotReached = true;
        }
        else
        {
            it.first->second.filteredCounter += 1U;
        }
    }
    else if (CriticalEventAlert::UnknownEventIdEventName == event)
    {
        SecurityEventsCountersEntry entry{frame.idsMInstanceID, frame.sensorInstanceID, frame.eventDefinitionId};

        if ((m_unknownEventIdAlertCounter.size() >= m_unknownEventIdAlertMaxNumber)
            && (m_unknownEventIdAlertCounter.find(entry) == m_unknownEventIdAlertCounter.end()))
        {
            auto const it = m_otherAlertsCounter.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(CriticalEventAlert::DroppedUnknownEventIdAlertThatExceededMaxNumber),
                std::forward_as_tuple(PassedDropCounters{}));
            it.first->second.filteredCounter += 1U;
        }
        else
        {
            auto const it = m_unknownEventIdAlertCounter.emplace(
                std::piecewise_construct, std::forward_as_tuple(entry), std::forward_as_tuple(PassedDropCounters{}));

            if (m_unknownEventIdAlertLimit > it.first->second.passedCounter)
            {
                it.first->second.passedCounter += 1U;
                isLimitNotReached = true;
            }
            else
            {
                it.first->second.filteredCounter += 1U;
            }
        }
    }
    else
    {
        if (!GetCriticalEventString(event).empty())
        {
            auto const it = m_otherAlertsCounter.emplace(
                std::piecewise_construct, std::forward_as_tuple(event), std::forward_as_tuple(PassedDropCounters{}));

            auto alertLimit   = m_defaultAltertLimit;
            auto eventLimitIt = m_criticalEventsLimits.find(event);

            if (m_criticalEventsLimits.cend() != eventLimitIt)
            {
                alertLimit = eventLimitIt->second;
            }

            if (alertLimit > it.first->second.passedCounter)
            {
                it.first->second.passedCounter += 1U;
                isLimitNotReached = true;
            }
            else
            {
                it.first->second.filteredCounter += 1U;
            }
        }
        else
        {
            LOG_ERROR << "Critical events " << static_cast<uint16_t>(event) << " not implemented" << LOG_NOOP;
        }
    }

    return isLimitNotReached;
}

bool
CriticalAlertFilter::CanSend(brain::sender_events::CriticalEventAlert event, std::string const& id)
{
    bool isLimitReached{true};

    if (CriticalEventAlert::DhmUnkownConstrainId == event)
    {
        if ((m_dhmUnkownConstrainIdCounter.size() >= m_dhmUnknownConstraintIdMaxNumber)
            && (m_dhmUnkownConstrainIdCounter.cend() == m_dhmUnkownConstrainIdCounter.find(id)))
        {
            auto const maxNumberit
                = m_otherAlertsCounter.emplace(std::piecewise_construct,
                                               std::forward_as_tuple(CriticalEventAlert::DhmUnkownConstrainIdMaxNumber),
                                               std::forward_as_tuple(PassedDropCounters{}));
            maxNumberit.first->second.filteredCounter += 1U;
        }
        else
        {
            auto const it = m_dhmUnkownConstrainIdCounter.emplace(
                std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple(PassedDropCounters{}));

            if (m_dhmUnknownConstraintIdAlertLimit > it.first->second.passedCounter)
            {
                it.first->second.passedCounter += 1U;
                isLimitReached = false;
            }
            else
            {
                it.first->second.filteredCounter += 1U;
            }
        }
    }

    return !isLimitReached;
}

void
CriticalAlertFilter::ResetCounters()
{
    m_criticalAlertCounter.clear();
    m_unknownEventIdAlertCounter.clear();
    m_otherAlertsCounter.clear();
    m_dhmUnkownConstrainIdCounter.clear();
}

bool
CriticalAlertFilter::Serialize(brain::engines::security_events::nanopb::PassedDroppedAlertsData& data,
                               uint64_t                                                          timestamp)
{
    if (m_criticalAlertCounter.empty() && m_unknownEventIdAlertCounter.empty() && m_otherAlertsCounter.empty()
        && m_dhmUnkownConstrainIdCounter.empty())
    {
        LOG_DEBUG << "All critical alerts are empty" << LOG_NOOP;
        return false;
    }

    data.creationTimeStamp = timestamp;

    for (auto const& entry : m_criticalAlertCounter)
    {
        data.CriticalSecurityEventAlertPassedDroppedCounters.emplace_back();
        auto& passedDroppedCounter = data.CriticalSecurityEventAlertPassedDroppedCounters.back();

        SerializeSecEventAlertPassedDroppedCounters(passedDroppedCounter, entry);
    }

    for (auto const& entry : m_dhmUnkownConstrainIdCounter)
    {
        data.DhmIncidentWithUnknownConstraintIdAlertCounters.emplace_back();
        auto& passedDroppedCounter = data.DhmIncidentWithUnknownConstraintIdAlertCounters.back();

        SerializeDhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters(passedDroppedCounter, entry);
    }

    for (auto const& entry : m_unknownEventIdAlertCounter)
    {
        data.UnknownEventIdAlertPassedDroppedCounters.emplace_back();
        auto& passedDroppedCounter = data.UnknownEventIdAlertPassedDroppedCounters.back();

        SerializeSecEventAlertPassedDroppedCounters(passedDroppedCounter, entry);
    }

    for (auto const& entry : m_otherAlertsCounter)
    {
        SerializeAlertDataEntry(data, entry);
    }

    data.PrepareForSerialization();

    return true;
}
