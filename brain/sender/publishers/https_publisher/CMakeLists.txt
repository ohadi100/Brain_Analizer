message(STATUS "CMake process for https publisher start")

# Project Name and definition:
project("HTTPS_Publisher"
        VERSION 1.0.0
        DESCRIPTION "General utilities for the brain library")

set(PUBLISHER_SOURCES HTTPSPublisher.cpp)

add_library(${PROJECT_NAME} ${PUBLISHER_SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids ExceededMessageSizeCheck)

message(STATUS "End of CMake process for https publisher")