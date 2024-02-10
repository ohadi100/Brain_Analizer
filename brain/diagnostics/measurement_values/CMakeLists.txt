# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/CounterMeasurementValue.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DiagMeasurementValuesManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/IntrusionDetectionSystemErrorCounterPublisher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/IntrusionDetectionSystemWarningCounterPublisher.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/CounterMeasurementValue.hpp
    ${CMAKE_CURRENT_LIST_DIR}/DiagMeasurementValuesManager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/IntrusionDetectionSystemErrorCounterPublisher.hpp
    ${CMAKE_CURRENT_LIST_DIR}/IntrusionDetectionSystemWarningCounterPublisher.hpp
)    

# Project Name and definition:
project("measurement_values"
        VERSION 1.0.0
        DESCRIPTION "DTC functionality")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids)
