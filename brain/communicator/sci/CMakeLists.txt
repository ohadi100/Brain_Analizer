# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/SciCommunicator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SciSignalGroupHandler.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/SciCommunicator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SciSignalGroupHandler.hpp
)    

# Project Name and definition:
project("SCICommunicator"
        VERSION 1.0.0
        DESCRIPTION "SCI communicator functionality")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})
set_source_files_properties(${CMAKE_CURRENT_LIST_DIR}/SciCommunicator.cpp PROPERTIES COMPILE_FLAGS -Wno-shadow)

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids communicator engines BrainUtils BrainConfiguration SecurityEventSensorData)
