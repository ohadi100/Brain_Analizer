# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/InternalPlayer.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/InternalPlayer.hpp
)    

# Project Name and definition:
project("internal_player"
        VERSION 1.0.0
        DESCRIPTION "Definitions and implementations of internal player")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids BrainConfiguration noise_filter events)
