# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/AlertEventsNames.cpp
)

set(HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/AlertEventsNames.hpp
        ${CMAKE_CURRENT_LIST_DIR}/BrainConfigConstants.hpp
)    

# Project Name and definition:
project("BrainConfiguration"
        VERSION 1.0.0
        DESCRIPTION "General configuration and constants for brain use")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids)
