# Project Name and definition:
project("Histograms"
        VERSION 1.0.0
        DESCRIPTION "Definitions and implementations of histograms for brain use")
add_library(${PROJECT_NAME} RateHistogram.cpp ScalarHistogram.cpp)

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} histogram-lib common_ids)
