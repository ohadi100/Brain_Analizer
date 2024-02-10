# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/GSDPCommunicator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SecurityEventNormal.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SecurityEventSmall.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/GSDPCommunicator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SecurityEventNormal.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SecurityEventSmall.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SomeIPCommunicator.hpp
)    

# Project Name and definition:
project("someip"
        VERSION 1.0.0
        DESCRIPTION "SOME/IP communicator functionality")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids communicator noise_filter diagnostics)
