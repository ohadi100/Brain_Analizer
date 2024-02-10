# Project Name and definition:
project("MEB Engines"
        VERSION 1.0.0
        DESCRIPTION "PeriodicReportEngine for MEB")
add_library(PeriodicReportEngine ${CMAKE_CURRENT_LIST_DIR}/PeriodicStatisticsEngine.hpp   ${CMAKE_CURRENT_LIST_DIR}/PeriodicStatisticsEngine.cpp)
target_link_libraries(PeriodicReportEngine NanoPB ReportSerializer)

add_library(EngineDispatcher ${CMAKE_CURRENT_LIST_DIR}/EngineDispatcher.hpp ${CMAKE_CURRENT_LIST_DIR}/EngineDispatcher.cpp)
target_link_libraries(EngineDispatcher ReportSerializer PeriodicReportEngine EngineDispatcherBase)
