message(STATUS "CMake process for publisher utilities start")

# Project Name and definition:
project("PublisherUtils"
        VERSION 1.0.0
        DESCRIPTION "General utilities for the publisher library")

add_subdirectory(message_size_check)

message(STATUS "End of CMake process for publisher utilities")