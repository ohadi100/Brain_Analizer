# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/IDSPeriodicReportSerializer.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/IDSPeriodicReportSerializer.hpp
)    

# Project Name and definition:
project(ReportSerializer
        VERSION 1.0.0
        DESCRIPTION "Final generic serializer for the IDS Protobuf reports")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} common_ids NanoPB gen_nanopb VehicleData)
