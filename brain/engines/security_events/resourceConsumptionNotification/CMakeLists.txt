# Define parts of project:

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/ResourceConsumptionSources.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceConsumptionNotificationEngine.cpp)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/ResourceConsumptionEntry.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceConsumptionSources.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceConsumptionNotificationEngine.hpp)

# Project Name and definition:
project("ResourceConsumptionNotification_engine"
        VERSION 1.0.0
        DESCRIPTION "The various brain ResourceConsumptionNotification engine")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} common_ids)