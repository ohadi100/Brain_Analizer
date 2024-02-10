/**
 * @file
 * @brief     A rule engine for SecurityEvents.
 */
#ifndef SECURITY_EVENTS_ENGINE_HPP
#define SECURITY_EVENTS_ENGINE_HPP

#include <unordered_map>
#include <unordered_set>
#include "CanIfSevErrorStateEntry.hpp"
#include "ConnectionsCountersEntry.hpp"
#include "ConnectionsCountersValue.hpp"
#include "DhmDroppedSecurityEventsCountersEntry.hpp"
#include "DiagnosticEventSequenceEntry.hpp"
#include "DisallowedLayer3ProtocolEntry.hpp"
#include "DisallowedLayer4ProtocolEntry.hpp"
#include "DroppedConnectionsCountersEntry.hpp"
#include "DroppedConnectionsCountersValue.hpp"
#include "DroppedSecurityEventsCountersEntry.hpp"
#include "ErrorEventLoggingUserLoginCountersEntry.hpp"
#include "EthernetServiceInterruptionEntry.hpp"
#include "ExternalDataStorageEntry.hpp"
#include "ExternalInterfacesUsageStatisticsEntry.hpp"
#include "ExternalNewHWConnectionEntry.hpp"
#include "ExternalUnsuccessfulConnectionsEntry.hpp"
#include "FreshnessValueFailedEntry.hpp"
#include "HostOsLogEntry.hpp"
#include "IStatisticsDataHolder.hpp"
#include "InvalidAddressDestinationPortCounterEntry.hpp"
#include "IpAnomaliesCountersEntry.hpp"
#include "IpConnectionCounters.hpp"
#include "IpDroppedConnectionsEntry.hpp"
#include "MacToIpAssociationEntry.hpp"
#include "MacToIpAssociationValue.hpp"
#include "NanoPB.hpp"
#include "NatCountersTable.hpp"
#include "OversizedPacketsHistogramEntry.hpp"
#include "ProcessCrashRateEntry.hpp"
#include "ProcessStartStopCountersEntry.hpp"
#include "RxTxErrorsEntry.hpp"
#include "SecurityEventEngineCreateEvent.hpp"
#include "SecurityEventIdsManager.hpp"
#include "SecurityEventsCountersEntry.hpp"
#include "ServiceRegistryEntry.hpp"
#include "UnusedPortConnectionRequestEntry.hpp"
#include "brain/engines/EthernetStatistics.hpp"
#include "brain/histograms/RateHistogram.hpp"
#include "brain/histograms/ScalarHistogram.hpp"
#include "brain/sensor_data/security_events/SecurityEventSensorData.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/utils/CPP/optional/Optional.hpp"
#include "common/utils/types/BoundedUnorderedMap.hpp"
#include "policer/PolicerTokenBucket.hpp"
#include "common/utils/timer/Timer.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{
using brain::sensor_data::SecurityEventSensorData;
using common::sensor_data::UPSensorData;

/**
 * @class   SecurityEventsEngine
 * @brief   The SecurityEventsEngine analyzes SecurityEvents.
 */
class SecurityEventsEngine : public SecurityEventEngineCreateEvent
{
public:
    using CounterManagerPtr     = common::counters::CounterManagerPtr;
    using EventCounter          = common::counters::EventCounter;
    using EventCounterWithTs    = common::counters::EventCounterWithTs;
    using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;
    using ConfigurationPtr      = common::configuration::Pointer;
    using PolicerTokenBucket    = histogram_lib::PolicerTokenBucket;
    using ScalarHistogram       = histogram::ScalarHistogram;
    using BinDataVector         = brain::histogram::RateHistogram::BinDataVector;
    using TimerPtr              = common::TimerPtr;
    using IpConnectionCountersTable
        = common::types::BoundedUnorderedMap<IpConnectionCountersEntry, IpConnectionCountersValue>;
    using IpDroppedConnectionsTable = common::types::BoundedUnorderedMap<IpDroppedConnectionsEntry, uint32_t>;
    using HostOsLogRateTable = common::types::BoundedUnorderedMap<HostOsLogEntry, brain::histogram::RateHistogram>;
    using ErrorEventLoggingUserLoginCountersTable
        = common::types::BoundedUnorderedMap<ErrorEventLoggingUserLoginCountersEntry, uint32_t>;
    using ExternalUnsuccessfulConnectionsTable
        = common::types::BoundedUnorderedMap<ExternalUnsuccessfulConnectionsEntry, uint32_t>;
    using SensorDataPtr      = std::shared_ptr<SecurityEventSensorData>;
    using EventNoiseFilterPtr = std::shared_ptr<brain::brain_noise_filter::EventNoiseFilter>;
    using ConstraintId       = brain::sensor_data::swpac::ConstraintId;

    /**
     * @struct   ExternalInterfaceUsageStatisticsValue
     * @brief   The ExternalInterfaceUsageStatisticsValue represents the value field in the
     * ExternalInterfacesUsageStatisticsTable unordered map.
     */
    class ExternalInterfaceUsageStatisticsValue
    {
    public:
        uint32_t newSessionsInLayerCount{};
        uint32_t totalPacketsPassed{};
        uint64_t totalBytesPassed{};

        bool
        operator==(ExternalInterfaceUsageStatisticsValue const& other) const
        {
            return ((newSessionsInLayerCount == other.newSessionsInLayerCount)
                    && (totalPacketsPassed == other.totalPacketsPassed)
                    && (totalBytesPassed == other.totalBytesPassed));
        }
    };
    using ExternalInterfacesUsageStatisticsTable
        = common::types::BoundedUnorderedMap<ExternalInterfacesUsageStatisticsEntry,
                                             ExternalInterfaceUsageStatisticsValue>;

    using ProcessStartStopCountersEntry = brain::engines::security_events::ProcessStartStopCountersEntry;
    enum
    {
        PROCESS_START_COUNTER = 0,
        PROCESS_STOP_COUNTER
    };  // used to access pair items in ProcessStartStopCountersTable
    enum
    {
        PROCESS_STATE_START = 0x01,
        PROCESS_STATE_STOP  = 0x10
    };
    using ProcessStartStopCountersTable
        = common::types::BoundedUnorderedMap<ProcessStartStopCountersEntry, std::pair<uint32_t, uint32_t>>;
    using DroppedBlockedConnectionsTable = common::types::BoundedUnorderedMap<IpAnomaliesCountersEntry, uint32_t>;
    using DiagnosticEventSequenceTable   = std::vector<brain::engines::security_events::DiagnosticEventSequenceEntry>;
    using DisallowedLayer3ProtocolCountersTable
        = common::types::BoundedUnorderedMap<DisallowedLayer3ProtocolEntry, uint32_t>;

    // keepAlive timers manager table
    using SecurityEventUniqeIdentifierEntry = brain::engines::security_events::SecurityEventsCountersEntry;
    using KeepAliveTimersTable
        = common::types::BoundedUnorderedMap<SecurityEventUniqeIdentifierEntry, common::Timer::TimerRegisterKey>;

    using DisallowedLayer4ProtocolCountersTable
        = common::types::BoundedUnorderedMap<DisallowedLayer4ProtocolEntry, uint32_t>;
    using UnusedPortConnectionAttemptsTable
        = common::types::BoundedUnorderedMap<UnusedPortConnectionRequestEntry, uint32_t>;
    using OversizedPacketsHistogramTable
        = common::types::BoundedUnorderedMap<OversizedPacketsHistogramEntry, brain::histogram::ScalarHistogram>;
    using ProtoOversizePacketsHistogramEntry = brain::engines::security_events::nanopb::OversizedPacketsHistogramEntry;

    // HCP3 GBT Tables
    using ProcessCrashRateTable
        = common::types::BoundedUnorderedMap<ProcessCrashRateEntry,
                                             std::tuple<brain::histogram::RateHistogram, PolicerTokenBucket>>;
    using ServiceRegistryTable         = common::types::BoundedUnorderedMap<ServiceRegistryEntry, uint32_t>;
    using ExternalDataStorageTable     = common::types::BoundedUnorderedMap<ExternalDataStorageEntry, uint32_t>;
    using ExternalNewHWConnectionTable = common::types::BoundedUnorderedMap<ExternalNewHWConnectionEntry, uint32_t>;
    using ProtoIpAnomaliesCounters     = brain::engines::security_events::nanopb::IpAnomaliesCountersEntry;

    using SecurityEventMonitoringData = brain::engines::security_events::nanopb::SecurityEventMonitoringData;
    using SecurityEventsPeriodicMonitoringData
        = brain::engines::security_events::nanopb::SecurityEventsPeriodicMonitoringData;

    using PersistentMemoryFactoryPtr = common::utils::PersistentMap::PersistentMemoryFactoryPtr;
    using PersistentMemory           = common::utils::PersistentMap;
    using CallbackVector
        = std::vector<std::function<void(SecurityEventsEngine*, brain::sensor_data::SecurityEventSensorData&)>>;

    // Ethernet Anomalies Monitoring
    using EthernetServiceInterruptionTable
        = common::types::BoundedUnorderedMap<EthernetServiceInterruptionEntry, uint32_t>;
    using InvalidAddressDestinationPortCounterTable
        = common::types::BoundedUnorderedMap<InvalidAddressDestinationPortCounterEntry, uint32_t>;
    using FreshnessValueFailedCountersTable = common::types::BoundedUnorderedMap<FreshnessValueFailedEntry, uint32_t>;
    using IpAnomaliesConnectionsCountersTable
        = common::types::BoundedUnorderedMap<ConnectionsCountersEntry, ConnectionsCountersValue>;
    using MacToIpAssociationTable
        = common::types::BoundedUnorderedMap<MacToIpAssociationEntry, MacToIpAssociationValue>;
    using DoubledIpToMacAssociationTable = common::types::BoundedUnorderedMap<uint64_t, IpType>;
    using DoubledMacToIpAssociationTable = common::types::BoundedUnorderedMap<IpType, uint64_t>;
    using DroppedConnectionsCountersTable
        = common::types::BoundedUnorderedMap<DroppedConnectionsCountersEntry, DroppedConnectionsCountersValue>;

    // Security Events Digesting
    using SecurityEventsCountersTable = common::types::BoundedUnorderedMap<SecurityEventsCountersEntry, uint32_t>;
    using DroppedSecurityEventsCountersTable
        = common::types::BoundedUnorderedMap<DroppedSecurityEventsCountersEntry, uint32_t>;
    using DhmDroppedSecurityEventsCountersTable = common::types::BoundedUnorderedMap<DhmDroppedSecurityEventsCountersEntry, uint32_t>; 
    using CriticalSecurityEventsAlertsCountersTable = common::types::BoundedUnorderedMap<EventIds, uint32_t>;
    using RxTxErrorsTable = common::types::BoundedUnorderedMap<RxTxErrorsEntry, uint32_t>;
    using CanIfSevErrorStateTable = common::types::BoundedUnorderedMap<CanIfSevErrorStateEntry, uint32_t>;

    // refactor usings
    using EnginePtr               = std::shared_ptr<Engine>;
    using StatisticsDataHolderPtr = std::shared_ptr<IStatisticsDataHolder>;

    // External interfaces monitoring
    enum class NatTableEvent
    {
        NAT_FLOODING_ALERT = 0x0,
        NAT_ENTRY_NOT_FOUND_ALERT,
        NAT_DUPLICATE_ENTRY_ALERT
    };
    using NatCountersTableValue = std::list<NatCountersEntriesStruct>;

    struct SecurityEventsEngineConfig
    {
        CounterManagerPtr                                 debugCounters;
        MessageRepositoryPtr                              msgRepository;
        ConfigurationPtr                                  config;
        TimerPtr                                          timer;
        EthernetStatisticsPtr                             ethStats;
        EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer;
        EventNoiseFilterPtr                               eventNoiseFilter;
        events::EventPriority                             priority{events::EventPriority::Important};
    };

    /**
     * @brief   Constructor
     * @param   config - security events engine config structure
     */
    explicit SecurityEventsEngine(SecurityEventsEngineConfig const& engineConfig);

    /**
     * @brief   Destructor
     */
    ~SecurityEventsEngine();

    /**
     * @brief    default copy constructor
     */
    SecurityEventsEngine(const SecurityEventsEngine& other) = delete;

    /**
     * @brief    default move constructor
     */
    SecurityEventsEngine(SecurityEventsEngine&& other) = delete;

    /**
    * @brief    default copy assignment operator
    */
    SecurityEventsEngine& operator=(SecurityEventsEngine const&) = delete;

    /**
    * @brief   default move assignment operator
    */
    SecurityEventsEngine& operator=(SecurityEventsEngine&&) = delete;

    /**
     * @brief   Serializes SecurityEventsMonitoringData (requirement 1.3)
     * @param   securityEventsMonitoring - Output for serialized SecurityEventsMonitoringData.
     * @param   startTime - start timestap in miliseconds for the periodic report creation
     * @param   endTime - end timestap in miliseconds for the periodic report creation
     * @return  bool - true for success, otherwise false.
     */
    bool CreateSecurityEventsMonitoringData(SecurityEventsPeriodicMonitoringData& securityEventsMonitoring,
                                            uint64_t                              startTime,
                                            uint64_t                              endTime);

    /**
     * @brief   Creates a SecurityEventAlert
     * @param   com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData& securityEventAlert - Rule evaluation
     * @param   SecurityEventSensorData const& securityEventSD - SecurityEvent SD
     * @return  true if the decode and security event alert protobuf was filled correctly, false otherwise
     */
    static bool CreateSecurityEventData(com_vwg_connect_ids_idsperiodicreport_v1_SecurityEventData& securityEventAlert,
                                        SecurityEventSensorData&                                    sd);

    /**
     * @brief   Process a SecurityEvent sensor data
     * @param   SecurityEventInstanceIdEntry const& entry
     * @param   brain::sensor_data::SecurityEventSensorData const& sd
     * @param   int dir - data flow direction
     * @return  bool - true for success, otherwise false.
     */
    bool SendLinkUtilizationAlert(DataflowStatisticsEngineKeyEntry const&            entry,
                                  brain::sensor_data::SecurityEventSensorData const& sd,
                                  int                                                dir);

    /**
     * @brief   Updates the table that stores the SE counting
     * @param   SecurityEventFrame eventFrame - SE frame
     */
    void UpdateSecurityEventsCountersTable(SecurityEventFrame eventFrame);

    /**
     * @brief   Updates the table that stores the SE counting
     * @param   uint16_t eventId - event ID
     */
    void UpdateCriticalSecurityEventsAlertsCountersTable(uint16_t eventId);

    /**
     * @brief   Handle the SE that are not known
     * @param   SecurityEventSensorData const& sd - sensor data
     */
    void HandleUnknownEventIdAlert(SecurityEventSensorData& sd);

    /**
     * @brief   Handle the SE SECOC_SEV_FRESHNESS_NOT_AVAILABLE
     * @param   SecurityEventSensorData& sd - sensor data
     * @param   SECEV_SECOC_SEV_FRESHNESS_NOT_AVAILABLE const* event - SE data deserialized
     */
    void HandleFreshnessValueFailedEvent(SecurityEventSensorData&                       sd,
                                         SECEV_SECOC_SEV_FRESHNESS_NOT_AVAILABLE const* event);

    /**
     * @fn      void HandleDroppedSecurityEvent(SecurityEventSensorData const& sd, DropReason dropReason);
     * @brief   Handle the SE that are dropped (not sent, unable to send, etc...)
     * @param   SecurityEventSensorData const& sd - SE sensor data
     * @param   DropReason dropReason
     * @return  none
     */
    void HandleDroppedSecurityEvent(SecurityEventSensorData const& sd, DropReason dropReason);

    /**
     * @fn      void HandleDhmDroppedSecurityEvent(ConstraintId constraintId, DropReason dropReason);
     * @brief   Handle the SE that are dropped (not sent, unable to send, etc...)
     * @param   constraintId - dhm constraint id
     * @param   dropReason - drop reason
     * @return  none
     */
    void HandleDhmDroppedSecurityEvent(ConstraintId constraintId, DropReason dropReason);

    /**
     * @fn      void HandleDroppedSecurityEvent(UPSensorData sd)
     * @brief   Handle the SE that are dropped outside the SE engine (not sent, unable to send, etc...)
     * @param   UPSensorData sd - sensor data
     * @param   DropReason dropReason
     * @return  none
     */
    static void HandleDroppedSecurityEventExt(UPSensorData sd, DropReason dropReason);
    
    /**
     * @fn      void HandleDroppedSecurityEvent(SecurityEventSensorData const& sd, DropReason dropReason);
     * @brief   Handle the SE that are dropped outside the SE engine (not sent, unable to send, etc...)
     * @param   SecurityEventSensorData const& sd - SE sensor data
     * @param   DropReason dropReason
     * @return  none
     */
    static void HandleDroppedSecurityEventExt(SecurityEventSensorData const& sd, DropReason dropReason);

    /**
     * @fn      void HandleDhmDroppedSecurityEventExt(brain::sensor_data::swpac::ConstraintId constraintId, DropReason dropReason);
     * @brief   Handle the SE that are dhm dropped outside the SE engine (not sent, unable to send, etc...)
     * @param   constraintId - dhm constraint id
     * @param   dropReason - drop reason
     */
    static void HandleDhmDroppedSecurityEventExt(ConstraintId constraintId, DropReason dropReason);

    /**
     * @brief   Handle the SE from Diagnostics
     * @param   SecurityEventSensorData& sd - sensor data
     */
    void HandleDiagnosticEventSequence(SecurityEventSensorData& sd);

    /**
     * @brief   Returns the table with the computed statistics
     * @return  FreshnessValueFailedCountersTable - table that contains the computed statistics
     */
    inline const FreshnessValueFailedCountersTable&
    GetFreshnessValueFailedCountersTable() const
    {
        return m_freshnessValueFailedCountersTable;
    }

    /**
     * @brief   Returns the table with the computed statistics
     * @return  DiagnosticEventSequenceTable - table that contains the computed statistics
     */
    inline const DiagnosticEventSequenceTable&
    GetDiagnosticEventSequenceTable() const
    {
        return m_diagnosticEventSequenceTable;
    }

    /**
     * @brief   Returns the table with the computed statistics
     * @return  SecurityEventsCountersTable - table that contains the computed statistics
     */
    inline const SecurityEventsCountersTable&
    GetSecurityEventsCountersTable() const
    {
        return m_securityEventsCountersTable;
    }

    /**
     * @brief   Returns the table with the computed statistics
     * @return  DroppedSecurityEventsCountersTable - table that contains the computed statistics
     */
    inline const DroppedSecurityEventsCountersTable&
    GetDroppedSecurityEventsCountersTable() const
    {
        return m_droppedSecurityEventsCountersTable;
    }

    /**
     * @brief   Returns the table with the computed statistics
     * @return  DhmDroppedSecurityEventsCountersTable - table that contains the computed statistics
     */
    inline const DhmDroppedSecurityEventsCountersTable&
    GetDhmDroppedSecurityEventsCountersTable() const
    {
        return m_dhmDroppedSecurityEventsCountersTable;
    }

    /**
     * @brief   Returns the table with the computed statistics
     * @return  CriticalSecurityEventsAlertsCountersTable - table that contains the computed statistics
     */
    inline const CriticalSecurityEventsAlertsCountersTable&
    GetCriticalSecurityEventsAlertsCountersTable() const
    {
        return m_criticalSecurityEventsAlertsCountersTable;
    }

    /**
     * @brief   Returns the table with the computed statistics
     * @return  RxTxErrorsTable - table that contains the computed statistics
     */
    inline const RxTxErrorsTable&
    GetRxTxErrorsCountersTable() const
    {
        return m_rxtxErrorsCountersTable;
    }

    /**
     * @brief   Returns the table with the computed statistics
     * @return  CanIfSevErrorStateTable - table that contains the computed statistics
     */
    inline const CanIfSevErrorStateTable&
    GetCanIfSevErrorStateTable() const
    {
        return m_canIfSevErrorStateTable;
    }

    
    /**
     * @brief   Handle the SE from HCP1 or SACID (CANIF_SEV_TX_ERROR_DETECTED or CANIF_SEV_RX_ERROR_DETECTED)
     * @param   SecurityEventSensorData& sd - sensor data
     */
    template <typename T>
    void
    HandleRXandTXErrorDetected(SecurityEventSensorData& sd)
    {
        auto event = sd.decodeContextData<T>();
        if (nullptr == event)
        {
            HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
            common::counters::IncreaseCounter(m_invalidCtxDataLenCounter);
            return;
        }
        if (!event->hasFields()
            && (!event->hasErrorTypeField() || !event->hasBusIdField() || !event->hasCanIdField()
                || !event->hasControllerIdField()))
        {
            LOG_ERROR << "Invalid event CANIF_SEV_TX_ERROR_DETECTED or CANIF_SEV_RX_ERROR_DETECTED received"
                      << LOG_NOOP;
            HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
            return;
        }

        auto const      eventFrame = sd.GetEventFrame();
        RxTxErrorsEntry entry{eventFrame.idsMInstanceID,
                              eventFrame.sensorInstanceID,
                              event->errorType,
                              event->busId,
                              event->canId,
                              event->controllerId};
        m_rxtxErrorsCountersTable[entry] += eventFrame.count;
    }


    /**
     * @brief   Handle the SE from HCP1 or SACID (CANIF_SEV_ERRORSTATE_PASSIVE or  CANIF_SEV_ERRORSTATE_BUSOFF)
     * @param   SecurityEventSensorData& sd - sensor data
     */
    void HandleCanIfErrorStatus(SecurityEventSensorData& sd);

protected:
    enum class SecurityEventType : uint8_t
    {
        Normal,
        Critical,
        Unknown
    };

    ReturnCode   processInternal(UPSensorData sd) override;
    virtual void handleKeepAliveEvent(SecurityEventSensorData const& sd, SECEV_KEEP_ALIVE_MESSAGE const* event);
    virtual void createKeepaliveTimeoutAlert(SensorDataPtr sdPtr);

    virtual void fillKeepAliveRuleEval(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                                       SecurityEventSensorData const&                           sd);
    virtual void createNatTableAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                                     SecurityEventSensorData const&                           sd,
                                     NatCountersTableValue const&                             natTable,
                                     NatTableEvent                                            natTableEvent,
                                     SECEV_NAT_UPDATE_REPORTS const*                          event);
    virtual void createDoubleMacToIpaddressAlert(uint64_t                       mac,
                                                 uint64_t                       currentMac,
                                                 IpType const&                  ipAddress,
                                                 SecurityEventSensorData const& sd);

private:
    static std::unordered_set<common::sensor_data::SensorDataTag> const validTags;

    void handleDroppedSecurityEvent(uint16_t   idsMInstanceID,
                                    uint8_t    sensorInstanceID,
                                    uint16_t   eventID,
                                    DropReason dropReason);
    void updateSecurityEventsCountersTable(uint16_t idsMInstanceID,
                                           uint8_t  sensorInstanceID,
                                           uint16_t eventID,
                                           uint16_t count);
    void createSuspiciousAggregateCrashRateAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                                                 BinDataVector& aggregatedHistogramData);
    void createErroneousServiceRegistrationAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                                                 SecurityEventSensorData&                                 sd);
    bool createSuspiciousProcessCrashRateAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                                               SecurityEventSensorData&                                 securityEventSD,
                                               brain::histogram::RateHistogram                          hist,
                                               BinDataVector& processHistogramData,
                                               BinDataVector& aggregatedHistogramData,
                                               std::string&   processName);
    void createSecurityEventAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                                  SecurityEventSensorData&                                 sd,
                                  SecurityEventType                                        eventType,
                                  EventIds                                                 eventId);

    void forwardCriticalSecurityEvent(SecurityEventSensorData& securityEventSD);

    // ConMod EU & China
    void handleDataDefinitionL3CheckFailedEvent(SecurityEventSensorData&                     sd,
                                                SECEV_DATA_DEFINITION_L3_CHECK_FAILED const* event);
    void handleEthernetCommunicationInterruptionEvent(SecurityEventSensorData&                         sd,
                                                      SECEV_ETHERNET_COMMUNICATION_INTERRUPTION const* event);

    // ConMod China
    void handleLogsForwardedPackageStatisticsEvent(SecurityEventSensorData&                                sd,
                                                   SECEV_LOCAL_FW_LOGS_FORWARDED_PACKAGE_STATISTICS const* event);
    void handleBlockedConnectionsDetectedEvent(SecurityEventSensorData&                           sd,
                                               SECEV_LOCAL_FW_BLOCKED_CONNECTIONS_DETECTED const* event);
    void handleOsLogReportsEvent(SecurityEventSensorData& sd, SECEV_OS_LOG_REPORTS const* event);
    void handleExternalConnectionInterfaceUnsuccessfulEvent(
        SecurityEventSensorData& sd, SECEV_EXTERNAL_CONNECTION_INTERFACE_UNSUCCESSFUL const* event);
    void handleExternalInterfacesUsageStatisticsEvent(SecurityEventSensorData&                          sd,
                                                      SECEV_EXTERNAL_INTERFACES_USAGE_STATISTICS const* event);

    void handleErrorEventLoggingUserLoginEvent(SecurityEventSensorData&                    sd,
                                               SECEV_ERROR_EVENT_LOGGING_USER_LOGIN const* event);

    // ConMod EU
    void handleProcessStartStopNotificationEvent(SecurityEventSensorData&                     sd,
                                                 SECEV_PROCESS_START_STOP_NOTIFICATION const* event);
    
    void createDiagSevEcuUnlockSuccessfulAlert(SecurityEventSensorData& sd);

    void handleDroppedTcpPacketsEvent(SecurityEventSensorData& sd, SECEV_TCPIP_SEV_DROP_INV_PORT_TCP const* event);
    void handleDroppedUdpPacketsEvent(SecurityEventSensorData& sd, SECEV_TCPIP_SEV_DROP_INV_PORT_UDP const* event);
    void handleDroppedIpv4AddressEvent(SecurityEventSensorData& sd, SECEV_TCPIP_SEV_DROP_INV_IPV4_ADDR const* event);
    void handleDroppedIpv6AddressEvent(SecurityEventSensorData& sd, SECEV_TCPIP_SEV_DROP_INV_IPV6_ADDR const* event);
    void handleDisallowedLayer3ProtocolEvent(SecurityEventSensorData&                    sd,
                                             SECEV_DETECTED_UNALLOWED_L3_PROTOCOL const* event);
    void handleDisallowedLayer4ProtocolEvent(SecurityEventSensorData&                    sd,
                                             SECEV_DETECTED_UNALLOWED_L4_PROTOCOL const* event);
    void handleUnusedPortConnectionRequestEvent(SecurityEventSensorData&                    sd,
                                                SECEV_UNUSED_PORT_CONNECTION_REQUEST const* event);
    void handleOversizedPacketsHistogram(SecurityEventSensorData& sd, SECEV_MESSAGE_MAX_SIZE_EXCEEDED const* event);

    // HCP3 GBT
    void handleProcessCrashNotificationEvent(SecurityEventSensorData&                sd,
                                             SECEV_PROCESS_CRASH_NOTIFICATION const* event);
    void handleErroneousServiceRegistrationAlert(SecurityEventSensorData& securityEventSD);
    void handleUnexpectedServiceRegistryEvent(SecurityEventSensorData&                          sd,
                                              SECEV_UNEXPECTED_SERVICE_REGISTRY_DETECTED const* event);
    void handleExternalNewHWConnection(SecurityEventSensorData& sd, SECEV_EXTERNAL_NEW_HW_CONNECTION const* event);
    void handleExternalDataStorageEvent(SecurityEventSensorData&                      sd,
                                        SECEV_EXTERNAL_DATA_STORAGE_CONNECTION const* event);
    void handleSuspiciousAggregateCrashRateAlert(SecurityEventSensorData const& securityEventSD);
    void handleSuspiciousProcessCrashRateAlert(brain::histogram::RateHistogram const& hist,
                                               SecurityEventSensorData&               securityEventSD);

    // Ethernet Anomalies Monitoring
    void handleSwitchDataflowStatisticsEvent(SecurityEventSensorData&                sd,
                                             SECEV_SWITCH_DATAFLOW_STATISTICS const* event);

    // External interfaces monitoring
    static bool encodeShadowNatTableData(pb_ostream_t* stream, pb_field_t const* fields, void* const* arg);
    void        handleNatTableEvents(SecurityEventSensorData& sd, SECEV_NAT_UPDATE_REPORTS const* event);

    // Dataflow Statistics
    bool fetchEthStats(
        brain::engines::security_events::nanopb::SecurityEventMonitoringData& newSecurityEventMonitoringData);
    bool createLinkUtilizationAlert(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation& ruleEval,
                                    DataflowStatisticsEngineKeyEntry const&                  entry,
                                    int                                                      dir);

    /**
     * @brief   Clears the persistent storage
     * @return  bool - true for success, otherwise false.
     */
    bool clearPersistentSerializedInfo();

    /**
     * @brief   Appends current events to `securityEventsMonitoring`
     * @param   SecurityEventsPeriodicMonitoringData& securityEventsMonitoring
     * @param   startPeriodicReportTimestamp - start timestap for the periodic report creation
     * @param   endPeriodicReportTimestamp - end timestap for the periodic report creation
     * @return  bool - true for success, otherwise false.
     */
    bool appendTables(SecurityEventsPeriodicMonitoringData& securityEventsMonitoring,
                      uint64_t                              startPeriodicReportTimestamp,
                      uint64_t                              endPeriodicReportTimestamp);

    /**
     * @brief   Reset all tables after sending their content with proto buffer
     */
    void resetTables();

    /**
     * @brief   Appends histograms to `securityEventsMonitoring`
     * @param   SecurityEventsPeriodicMonitoringData& securityEventsMonitoring
     * @return  bool - true for success, otherwise false.
     */
    bool appendHistograms(SecurityEventsPeriodicMonitoringData& securityEventsMonitoring);

    template <typename T, typename OpT>
    static std::function<void(SecurityEventsEngine* self, SecurityEventSensorData& sd)>
    createDecodeContextDataHandler(OpT op)
    {
        return [op](SecurityEventsEngine* self, SecurityEventSensorData& sd) {
            // Translate ContextData
            T const* event = sd.decodeContextData<T>();
            if (nullptr == event)
            {
                common::counters::IncreaseCounter(self->m_invalidCtxDataLenCounter);
                self->HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
                return;
            }

            return (self->*op)(sd, event);
        };
    }

    template <typename T>
    void
    decodeHandleCriticalEvent(SecurityEventSensorData& sd)
    {
        // Decodes contextData inside the sd
        if (nullptr == sd.decodeContextData<T>())
        {
            HandleDroppedSecurityEvent(sd, DropReason::SecurityEventsEngine);
            common::counters::IncreaseCounter(m_invalidCtxDataLenCounter);
            return;
        }

        forwardCriticalSecurityEvent(sd);
    }

    template <typename T>
    void
    fillAggregatedCrashRateHistogramForAlert(T& alert, brain::histogram::RateHistogram::BinDataVector& histogramData)
    {
        uint64_t aggregatedFirstTimeStamp{};
        uint64_t aggregatedLastTimeStamp{};
        if (!m_aggregateCrashRateHistogram.GetHistogramValues(
                histogramData, aggregatedFirstTimeStamp, aggregatedLastTimeStamp))
        {
            LOG_ERROR << "Cannot get aggregated crash rate histogram values" << LOG_NOOP;
            return;
        }

        alert.has_aggregatedCrashRateHistogram                  = true;
        alert.aggregatedCrashRateHistogram.firstSeenTimeStamp   = aggregatedFirstTimeStamp;
        alert.aggregatedCrashRateHistogram.lastSeenTimeStamp    = aggregatedLastTimeStamp;
        alert.aggregatedCrashRateHistogram.buckets.funcs.encode = &common::nanopb::encoders::EncodeRateHistogram;
        alert.aggregatedCrashRateHistogram.buckets.arg          = &histogramData;
    }

    void detectDoubleIpToMacAssociation(IpType const& ipAddress, uint64_t mac);
    void detectDoubleMacToIpAssociation(uint64_t mac, IpType const& ipAddress, SecurityEventSensorData const& sd);

    // keepAlive
    void stopKeepAliveTimers();

protected:
    // common variables
    CounterManagerPtr             m_debugCounters;
    std::shared_ptr<EventCounter> m_failedCounter;
    std::shared_ptr<EventCounter> m_invalidCtxDataLenCounter;
    std::shared_ptr<EventCounter> m_droppedSETableCounter;
    std::shared_ptr<EventCounter> m_UnknownEventIdAlertCounter;
    std::shared_ptr<EventCounter> m_freshnessValueFailedTableCounter;
    std::shared_ptr<EventCounter> m_diagnosticEventSequenceTableCounter;
    std::shared_ptr<EventCounter> m_SETableCounter;
    std::shared_ptr<EventCounter> m_criticalSETableCounter;

    // Requirement 2.1
    IpConnectionCountersTable m_ipConnectionCountersTable;

    // Requirement 2.2
    IpDroppedConnectionsTable m_ipDroppedConnectionsTable;

    // Requirement 3.1
    HostOsLogRateTable m_hostOsLogRateTable;

    // Requirement 4.1
    ExternalUnsuccessfulConnectionsTable m_externalUnsuccessfulConnectionsTable;

    ExternalInterfacesUsageStatisticsTable m_externalInterfacesUsageStatisticsTable;

    ProcessStartStopCountersTable m_processStartStopCountersTable;

    // Requirement 1.1 HCP3 GBT
    KeepAliveTimersTable m_keepAliveTimersTable;
    TimerPtr             m_keepAliveTimer;
    uint32_t             m_keepAliveTimeoutPeriod{};

    // Requirement 3.7 HCP3 GBT
    ProcessCrashRateTable m_processCrashRateTable;
    double m_suspiciousCrashThresholdRate{};
    double m_suspiciousCrashRateMaxBurst{};

    // Requirement 3.9 HCP3 GBT
    brain::histogram::RateHistogram m_aggregateCrashRateHistogram;
    std::unique_ptr<PolicerTokenBucket> m_aggregateCrashRateTokenBucket;
    double m_aggregateCrashThresholdRate{};
    double m_aggregateCrashRateMaxBurst{};

    // Requirement 4.1 HCP3 GBT
    ServiceRegistryTable m_serviceRegistryTable;

    // Requirement 6.1 HCP3
    ExternalNewHWConnectionTable m_externalNewHWConnectionTable;

    // Requirement 5.1 HCP3
    ExternalDataStorageTable m_externalDataStorageTable;

    // Requirement 59 - Dropped/Blocked Connections Table
    DroppedBlockedConnectionsTable m_droppedBlockedConnectionsTable;

    // Requirement 105 - Diagnostic Event Sequence
    DiagnosticEventSequenceTable m_diagnosticEventSequenceTable;
    bool                         m_diagnosticFailureIndication = false;

    // Ethernet Anomalies Monitoring
    EthernetServiceInterruptionTable m_ethernetServiceInterruptionTable;
    // Requirement 65 - Oversized Packets Histogram Table
    OversizedPacketsHistogramTable m_oversizedPacketsHistogramTable;
    // Requirement 67 - Invalid TCP Destination Port Counters Table
    InvalidAddressDestinationPortCounterTable m_invalidTcpDestinationPortCounterTable;
    // Requirement 68 - Invalid UDP Destination Port Counters Table
    InvalidAddressDestinationPortCounterTable m_invalidUdpDestinationPortCounterTable;
    // Requirement 69 - Invalid IPv4 Address Counters Table
    InvalidAddressDestinationPortCounterTable m_invalidIpv4AddressCounterTable;
    // Requirement 70 - Invalid IPv6 Address Counters Table
    InvalidAddressDestinationPortCounterTable m_invalidIpv6AddressCounterTable;
    // Failed to get FV from FM Counters Table
    FreshnessValueFailedCountersTable m_freshnessValueFailedCountersTable;
    // Requirement 71 - Disallowed Layer 3 Protocol Counters Table
    DisallowedLayer3ProtocolCountersTable m_disallowedLayer3ProtocolCountersTable;
    // Requirement 72 - Disallowed Layer 4 Protocol Counters Table
    DisallowedLayer4ProtocolCountersTable m_disallowedLayer4ProtocolCountersTable;
    // Requirement 73 - Connection Attempts to an Unused Port Counters Table
    UnusedPortConnectionAttemptsTable m_unusedPortConnectionAttemptsTable;
    // Connections Counters Table
    IpAnomaliesConnectionsCountersTable m_ipAnomaliesConnectionsCountersTable;
    // Source and Destination MAC to IP Association Table
    MacToIpAssociationTable m_macToIpAssociationTable;
    // Double IP to MAC Association
    DoubledIpToMacAssociationTable m_doubledIpToMacAssociationTable;
    // Double MAC to IP Association
    DoubledMacToIpAssociationTable m_doubledMacToIpAssociationTable;
    // Dropped Connections Counters Table
    DroppedConnectionsCountersTable m_droppedConnectionsCountersTable;

    // Security Events Digesting
    SecurityEventsCountersTable               m_securityEventsCountersTable;
    DroppedSecurityEventsCountersTable        m_droppedSecurityEventsCountersTable;
    DhmDroppedSecurityEventsCountersTable     m_dhmDroppedSecurityEventsCountersTable;
    CriticalSecurityEventsAlertsCountersTable m_criticalSecurityEventsAlertsCountersTable;
    //HCP1 statistics for periodic report
    RxTxErrorsTable                           m_rxtxErrorsCountersTable;
    CanIfSevErrorStateTable                   m_canIfSevErrorStateTable;

    // External interfaces monitoring - NatCounterTable class to handle nat related events
    NatCountersTable m_natCountersTable;

    static brain::histogram::RateHistogram::BinIntervalsVector const   m_processCrashRateBins;
    static brain::histogram::RateHistogram::BinIntervalsVector const   m_ratesBins;
    static brain::histogram::ScalarHistogram::BinIntervalsVector const m_packageSizeBins;

    static std::map<uint16_t, CallbackVector> m_eventHandlers;

    EthernetStatisticsPtr          m_ethStats;
    ScalarHistogram::BinDataVector m_ethStatsBinDataVectorOut;
    ScalarHistogram::BinDataVector m_ethStatsBinDataVectorIn;

    // functions and members for the refactor - todel rinat comment
protected:
    std::map<uint16_t, std::vector<EnginePtr>> m_securityEventEngines;
    std::vector<StatisticsDataHolderPtr>       m_statisticsDataHolders{};
};

using SecurityEventsEnginePtr = std::shared_ptr<SecurityEventsEngine>;

}  // namespace security_events
}  // namespace engines
}  // namespace brain

#endif  // SECURITY_EVENTS_ENGINE_HPP
