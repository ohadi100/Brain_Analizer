# Project Name and definition:
project("SecurityEventSensorData"
        VERSION 1.0.0
        DESCRIPTION "General utilities for the brain library")
add_library(SecurityEventSensorData SecurityEventSensorData.cpp)

# Project include and link definitions:
target_include_directories(SecurityEventSensorData PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SecurityEventSensorData common_ids)

