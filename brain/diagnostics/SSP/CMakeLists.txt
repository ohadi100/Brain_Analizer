# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/DiagnosticsManager.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/DiagnosticsManager.hpp
)    

# Project Name and definition:
project("DiagnosticsManager"
        VERSION 1.0.0
        DESCRIPTION "DiagnosticsManager functionality")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids)
