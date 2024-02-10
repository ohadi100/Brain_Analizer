message(STATUS "CMake process for GDC agent start")

add_subdirectory(CampaignConfiguration)

# Project Name and definition:
project("GDCAgent"
        VERSION 1.0.0
        DESCRIPTION "General utilities for the brain library")

set(PUBLISHER_SOURCES GDCAgent.cpp)
add_library(${PROJECT_NAME} ${PUBLISHER_SOURCES})
# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} arxml_ext_sources_lib common_ids CampaignConfiguration)

message(STATUS "End of CMake process for GDC agent")
