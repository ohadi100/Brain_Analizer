# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/DiagnosticsManager.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/DiagnosticsManager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/AdaptationValuesConstants.hpp
)    

# Project Name and definition:
project("DiagnosticsManager"
        VERSION 1.0.0
        DESCRIPTION "DiagnosticsManager functionality")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${BRAIN_FOLDER}/diagnostics)
target_link_libraries(${PROJECT_NAME} common_ids dtc measurement_values diag_accessor diagnostic_routines)
