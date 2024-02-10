# Project Name and definition:
project("BrainUtils"
        VERSION 1.0.0
        DESCRIPTION "General utilities for the brain library")
add_library(${PROJECT_NAME} CounterWithTs.cpp IpUtils.cpp)

add_subdirectory(ipv6Address)
add_subdirectory(nanopb)
add_subdirectory(vehicle_data)

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}  common_ids)
