# Project Name and definition:
project("QlahSensorData"
        VERSION 1.0.0
        DESCRIPTION "General utilities for the brain library")
add_library(QlahSensorData EthSensorData.cpp HostSensorData.cpp)

# Project include and link definitions:
target_include_directories(QlahSensorData PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(QlahSensorData common_ids)

