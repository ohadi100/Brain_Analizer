# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/KernelLogEngine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TLSErrorReportEngine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ProcessPerformanceEngine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SwpacEngineBase.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UnknownConstraintEngine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/IncidentCounterTable.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/KernelLogEngine.hpp
    ${CMAKE_CURRENT_LIST_DIR}/TLSErrorReportEngine.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ProcessPerformanceEngine.hpp
    ${CMAKE_CURRENT_LIST_DIR}/UnknownConstraintEngine.hpp
    ${CMAKE_CURRENT_LIST_DIR}/IncidentCounterTable.hpp
)

# Project Name and definition:
project("SWPAC_engines"
        VERSION 1.0.0
        DESCRIPTION "The various brain SWPAC engines")
add_library(SWPAC_engines ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(SWPAC_engines PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SWPAC_engines common_ids BrainUtils Histograms histogram-lib engines BrainConfiguration SWPAC EventNoiseFilter Sender ReportSerializer)
