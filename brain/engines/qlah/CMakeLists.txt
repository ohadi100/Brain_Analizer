# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/EthUnknownProtocolAlert.cpp
    ${CMAKE_CURRENT_LIST_DIR}/EthIllegalVlanFramesAlert.cpp
    ${CMAKE_CURRENT_LIST_DIR}/EthEngine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/HostEngine.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/EventAlertBase.hpp
    ${CMAKE_CURRENT_LIST_DIR}/EthUnknownProtocolAlert.hpp
    ${CMAKE_CURRENT_LIST_DIR}/EthIllegalVlanFramesAlert.hpp
    ${CMAKE_CURRENT_LIST_DIR}/EthEngine.hpp
    ${CMAKE_CURRENT_LIST_DIR}/HostEngine.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PortData.hpp
)    

# Project Name and definition:
project("qlah_engines"
        VERSION 1.0.0
        DESCRIPTION "The various brain qlah engines")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids BrainUtils Histograms histogram-lib engines BrainConfiguration QlahSensorData EventNoiseFilter Sender)
