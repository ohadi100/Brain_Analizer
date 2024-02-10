# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/Communicator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/CommunicatorManagerBase.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/Communicator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/CommunicatorManagerBase.hpp
)    

# Project Name and definition:
project("communicator"
        VERSION 1.0.0
        DESCRIPTION "General configuration and constants for brain use")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

add_subdirectory(periodic)

# ToDo - delete the CMake as part of IDSPPE-1456
if(DEFINED ENV{SSP_PLATFORM} OR DEFINED ENV{SSP_PLATFORM_TEST} OR DEFINED ENV{SSP_SIMULATION})
    add_subdirectory(SSP)
    add_subdirectory(ids_portal)
else()
    add_subdirectory(PPE)
    add_subdirectory(uds)
    add_subdirectory(diagdata)
    add_subdirectory(sci)
    add_subdirectory(someip)
endif()

add_subdirectory(FileSystemCommunicator)

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids PeriodicCommunicator   CommunicatorManager)
if(NOT DEFINED ENV{SSP_PLATFORM} AND NOT DEFINED ENV{SSP_PLATFORM_TEST} AND NOT DEFINED ENV{SSP_SIMULATION})
    target_link_libraries(${PROJECT_NAME} diagdata SCICommunicator someip arxml_ext_sources_lib UDSCommunicator)
endif()
