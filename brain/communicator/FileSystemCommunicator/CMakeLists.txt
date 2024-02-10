if((DEFINED EEE_PLATFORM AND DEFINED HTTPS_PUBLISHER) OR ("${BUILD_MODE}" STREQUAL "tests") )
    if( (DEFINED PPE_PLATFORM) OR (DEFINED ENV{PPE_PLATFORM_TEST}) OR ("${BUILD_MODE}" STREQUAL "normal" AND DEFINED ENV{SIMULATION} AND NOT DEFINED ENV{SSP_SIMULATION}) )
        set(SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/MockSensorFactory.cpp
        )

        set(HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/MockSensorFactory.hpp
        )
        set_source_files_properties(${CMAKE_CURRENT_LIST_DIR}/MockSensorFactory.cpp PROPERTIES COMPILE_FLAGS -Wno-missing-declarations)
    endif()
endif()

set(HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_LIST_DIR}/FileSystemCommunicator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FolderMonitor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SensorGenerator.cpp
)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/FileAction.hpp
    ${CMAKE_CURRENT_LIST_DIR}/FolderMonitor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/FileSystemCommunicator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SensorGenerator.hpp
)

if("${BUILD_MODE}" STREQUAL "tests")
    if(NOT DEFINED ENV{SSP_PLATFORM_TEST})
        set(SOURCES ${SOURCES} ${AUTOGEN_GSEP_DIRECTORY}/SecurityEvents.cpp)
    endif()
endif()

# Project Name and definition:
project("FileSystemCommunicator"
        VERSION 1.0.0
        DESCRIPTION "The file system communicator part of the commons library")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids engines)
