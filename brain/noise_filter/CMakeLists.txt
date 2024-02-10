# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/NoiseFilter.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/NoiseFilter.hpp
)    

# Project Name and definition:
project("noise_filter"
        VERSION 1.0.0
        DESCRIPTION "Definitions and implementations of histograms for brain use")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

add_subdirectory(event_noise_filter)
add_subdirectory(sensor_noise_filter)

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids)
