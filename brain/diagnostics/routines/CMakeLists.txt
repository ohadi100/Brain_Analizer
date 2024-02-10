# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/IDSResetLifeCycleRoutine.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/IDSResetLifeCycleRoutine.hpp
)    

# Project Name and definition:
project("diagnostic_routines"
        VERSION 1.0.0
        DESCRIPTION "Diagnostic routines functionality")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} 
common_ids 
diagnostic_ext_sources_lib
)
