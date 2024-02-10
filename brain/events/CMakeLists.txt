# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/Event.cpp
    ${CMAKE_CURRENT_LIST_DIR}/EventUtils.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/Event.hpp
    ${CMAKE_CURRENT_LIST_DIR}/EventUtils.cpp
)    

# Project Name and definition:
project("events"
        VERSION 1.0.0
        DESCRIPTION "Definitions and implementations of events")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids)
