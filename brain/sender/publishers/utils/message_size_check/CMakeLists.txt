message(STATUS "CMake process for ExceededMessageSizeCheck start")

# Project Name and definition:
project("ExceededMessageSizeCheck"
        VERSION 1.0.0
        DESCRIPTION "GDC_1.2 publisher functionality")

set(PUBLISHER_SOURCES ExceededMessageSizeCheck.cpp)

add_library(${PROJECT_NAME} ${PUBLISHER_SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids NanoPB)

message(STATUS "End of CMake process for ExceededMessageSizeCheck")