# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/DtcEvent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DtcServiceDiscoveryEvent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DtcServiceRegistryEvent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DtcTimedEvent.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/DtcEvent.hpp
    ${CMAKE_CURRENT_LIST_DIR}/DtcServiceDiscoveryEvent.hpp
    ${CMAKE_CURRENT_LIST_DIR}/DtcServiceRegistryEvent.hpp
    ${CMAKE_CURRENT_LIST_DIR}/DtcTimedEvent.hpp
)    

# Project Name and definition:
project("dtc"
        VERSION 1.0.0
        DESCRIPTION "DTC functionality")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

set_source_files_properties(${CMAKE_CURRENT_LIST_DIR}/DtcEvent.cpp PROPERTIES COMPILE_FLAGS -Wno-unused-parameter) # for testing mode
# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids)
