set(SOURCES
${CMAKE_CURRENT_LIST_DIR}/EngineEventSender.cpp)

set(HEADERS
${CMAKE_CURRENT_LIST_DIR}/EngineEventSender.hpp
)

if( (DEFINED PPE_PLATFORM) OR (DEFINED ENV{PPE_PLATFORM_TEST}) OR ("${BUILD_MODE}" STREQUAL "normal" AND DEFINED ENV{SIMULATION} AND NOT DEFINED ENV{SSP_SIMULATION}))
    set(SOURCES
        ${SOURCES}
        ${CMAKE_CURRENT_LIST_DIR}/CriticalAlertFilter.cpp
        ${CMAKE_CURRENT_LIST_DIR}/EthernetStatistics.cpp)

    set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_LIST_DIR}/CriticalAlertFilter.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Engine.hpp
        ${CMAKE_CURRENT_LIST_DIR}/EngineId.hpp
        ${CMAKE_CURRENT_LIST_DIR}/EthernetStatistics.hpp)
endif()


if(NOT DEFINED EEE_PLATFORM)
    set(SOURCES ${SOURCES} ${CMAKE_CURRENT_LIST_DIR}/NullEngine.cpp)
    set(HEADERS ${HEADERS} ${CMAKE_CURRENT_LIST_DIR}/NullEngine.hpp)
endif()

# Project Name and definition:
project("engines"
        VERSION 1.0.0
        DESCRIPTION "The various brain engines")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

add_subdirectory(security_events)
add_subdirectory(dispatcher)
add_subdirectory(serializer)

if(DEFINED ENV{SSP_PLATFORM} OR DEFINED ENV{SSP_PLATFORM_TEST} OR DEFINED ENV{SSP_SIMULATION})
    add_subdirectory(SSP)
else()
    add_subdirectory(PPE)
    add_subdirectory(qlah)
    add_subdirectory(swpac)
endif()


if(NOT DEFINED ENV{SSP_PLATFORM} AND NOT DEFINED ENV{SSP_PLATFORM_TEST} AND NOT DEFINED ENV{SSP_SIMULATION})
    target_link_libraries(${CONTAINER_NAME} 
    qlah_engines
    security_events
    SWPAC_engines)
    target_link_libraries(${PROJECT_NAME}  SWPAC_engines  qlah_engines)
else()
    target_link_libraries(
    ${CONTAINER_NAME} 
    EngineDispatcher 
    security_events)
endif()

target_link_libraries(${PROJECT_NAME} common_ids security_events  gen_nanopb  EngineDispatcher EngineDispatcherBase)

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})