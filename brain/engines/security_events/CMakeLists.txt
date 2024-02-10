# Define parts of project:
if(DEFINED ENV{SSP_PLATFORM} OR DEFINED ENV{SSP_PLATFORM_TEST} OR DEFINED ENV{SSP_SIMULATION})
    set(SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/NanoPB.cpp
        ${CMAKE_CURRENT_LIST_DIR}/NatCountersTable.cpp)

        set(HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/NanoPB.hpp
        ${CMAKE_CURRENT_LIST_DIR}/NanoPbMacros.hpp)
        
else()
    set(SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/SecurityEventsHelper.cpp
        ${CMAKE_CURRENT_LIST_DIR}/IntelligentSensorEngine.cpp
        ${CMAKE_CURRENT_LIST_DIR}/IpDroppedConnectionsEntry.cpp
        ${CMAKE_CURRENT_LIST_DIR}/NanoPB.cpp
        ${CMAKE_CURRENT_LIST_DIR}/NatCountersTable.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PassedDroppedAlertsNanoPB.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SacidEventsEngine.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SecurityEventsEngine.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SecurityEventsEngineCreateAlert.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SecurityEventEngineCreateEvent.cpp
        ${AUTOGEN_GSEP_DIRECTORY}/SecurityEvents.cpp)

    set(HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/SecurityEventsHelper.hpp
        ${CMAKE_CURRENT_LIST_DIR}/CanIfSevErrorStateEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ConnectionsCountersBaseEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ConnectionsCountersEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ConnectionsCountersValue.hpp
        ${CMAKE_CURRENT_LIST_DIR}/DataflowStatisticsEngineKeyEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/DiagnosticEventSequenceEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/DisallowedLayer3ProtocolEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/DisallowedLayer4ProtocolEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/DroppedConnectionsCountersEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/DroppedConnectionsCountersValue.hpp
        ${CMAKE_CURRENT_LIST_DIR}/DroppedSecurityEventsCountersEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/DhmDroppedSecurityEventsCountersEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ErrorEventLoggingUserLoginCountersEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/EthernetBaseEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/EthernetServiceInterruptionEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ExternalDataStorageEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ExternalEventEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ExternalHwEventEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ExternalInterfacesUsageStatisticsEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ExternalNewHWConnectionEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ExternalUnsuccessfulConnectionsEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/FreshnessValueFailedEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/HostOsLogEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/IntelligentSensorEngine.hpp
        ${CMAKE_CURRENT_LIST_DIR}/InvalidAddressDestinationPortCounterEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/IStatisticsDataHolder.hpp
        ${CMAKE_CURRENT_LIST_DIR}/IpAnomaliesCountersEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/IpConnectionCounters.hpp
        ${CMAKE_CURRENT_LIST_DIR}/IpDroppedConnectionsEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/MacToIpAssociationEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/MacToIpAssociationValue.hpp
        ${CMAKE_CURRENT_LIST_DIR}/NanoPB.hpp
        ${CMAKE_CURRENT_LIST_DIR}/NanoPbMacros.hpp
        ${CMAKE_CURRENT_LIST_DIR}/NatCountersEntries.hpp
        ${CMAKE_CURRENT_LIST_DIR}/NatCountersTableEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/NatCountersTable.hpp
        ${CMAKE_CURRENT_LIST_DIR}/OversizedPacketsHistogramEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/PassedDroppedAlertsNanoPB.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ProcessCrashRateEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ProcessStartStopCountersEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/RxTxErrorsEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/SacidEventsEngine.hpp
        ${CMAKE_CURRENT_LIST_DIR}/SecurityEventIdsManager.hpp
        ${CMAKE_CURRENT_LIST_DIR}/SecurityEventInstanceIdEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/SecurityEventsCountersEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/SecurityEventsEngine.hpp
        ${CMAKE_CURRENT_LIST_DIR}/SecurityEventEngineCreateEvent.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ServiceRegistryEntry.hpp
        ${CMAKE_CURRENT_LIST_DIR}/UnusedPortConnectionRequestEntry.hpp)

    add_subdirectory(resourceConsumptionNotification)
endif()
# Project Name and definition:
project("security_events"
        VERSION 1.0.0
        DESCRIPTION "The various brain security_events engines")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} 
    common_ids
    BrainUtils
    Histograms
    histogram-lib
    engines
    BrainConfiguration
    EventNoiseFilter
    gen_nanopb
    NanoPB
)
if(NOT DEFINED ENV{SSP_PLATFORM} AND NOT DEFINED ENV{SSP_PLATFORM_TEST} AND NOT DEFINED ENV{SSP_SIMULATION})
target_link_libraries(${PROJECT_NAME} ResourceConsumptionNotification_engine)
endif()
