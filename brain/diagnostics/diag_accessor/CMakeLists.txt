# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/DiagFeatureFlags.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/DiagFeatureFlags.hpp
)    

# Project Name and definition:
project("diag_accessor"
        VERSION 1.0.0
        DESCRIPTION "Diagnostics accessor functionality")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_link_libraries(${PROJECT_NAME} common_ids )
if("${BUILD_MODE}" STREQUAL "tests")
    target_link_libraries(${PROJECT_NAME} test_lib)
endif()
