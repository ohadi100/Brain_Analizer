# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/SocketCommunicator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UDSCommunicator.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/SocketCommunicator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/UDSCommunicator.hpp
)    

# Project Name and definition:
project("UDSCommunicator"
        VERSION 1.0.0
        DESCRIPTION "UDS communicator functionality")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids communicator noise_filter diagnostics QlahSensorData)
