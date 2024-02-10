# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/PortalCommunicator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PortalSubscriber.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/PortalCommunicator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PortalSubscriber.hpp
)    

# Project Name and definition:
project("PortalCommunicator"
        VERSION 1.0.0
        DESCRIPTION "UDS communicator functionality")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids communicator ids-service)
