# Project Name and definition:
project("GDCAgentAraUtils"
        VERSION 1.0.0
        DESCRIPTION "General utilities for the brain library")
add_library(GDCAgentAraUtils)

# Project include and link definitions:
target_include_directories(GDCAgentAraUtils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
