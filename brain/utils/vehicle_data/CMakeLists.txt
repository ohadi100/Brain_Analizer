# Project Name and definition:
project("VehicleData"
        VERSION 1.0.0
        DESCRIPTION "General utilities for vehicle data")
add_library(VehicleData VehicleData.cpp)

# Project include and link definitions:
target_include_directories(VehicleData PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(VehicleData common_ids)
