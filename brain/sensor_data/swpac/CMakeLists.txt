# Project Name and definition:
project("SWPAC"
        VERSION 1.0.0
        DESCRIPTION "General utilities for IPv6 address support")
add_library(SWPAC
            IncidentHelper.cpp
            KernelLogSensorData.cpp
            SWPACSensorDataFactory.cpp
            TLSErrorReportSensorData.cpp
            ProcessPerformanceSensorData.cpp
            SwpacSensorDataBase.cpp)
       
# Project include and link definitions:
target_include_directories(SWPAC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SWPAC common_ids)
