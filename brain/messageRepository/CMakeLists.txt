message(STATUS "CMake process for MessageRepository object")

# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/MessageRepositoryPriorityQueue.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/interface/MessageRepository.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MessageRepositoryPriorityQueue.hpp
)    

# Project Name and definition:
project("MessageRepository"
        VERSION 1.0.0
        DESCRIPTION "The MessageRepository object")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "End of CMake process for MessageRepository object")