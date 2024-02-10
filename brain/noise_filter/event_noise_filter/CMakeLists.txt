# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/EventNoiseFilter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GroupNoiseFilter.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/EventNoiseFilter.hpp
    ${CMAKE_CURRENT_LIST_DIR}/GroupNoiseFilter.hpp
)    

# Project Name and definition:
project("EventNoiseFilter"
        VERSION 1.0.0
        DESCRIPTION "Definitions and implementations of event noise filter")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids BrainConfiguration noise_filter events)
