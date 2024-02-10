set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/FsPersistentMemoryManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PersistentMemoryManagerBuilder.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/FsPersistentMemoryManager.hpp
)

# ToDo - remove in IDSPPE-1456 as root CMakes are separated
if(DEFINED EEE_PLATFORM)
    add_definitions(-DDIDS_DIRECTORY="/data/e3/ids")
    add_definitions(-DDPM_DIRECTORY="/data/e3/ids/pm")
else()
    add_definitions(-DDIDS_DIRECTORY="")
    add_definitions(-DDPM_DIRECTORY="")
endif()

# Project Name and definition:
project("FsPersistentMemoryManager"
        VERSION 1.0.0
        DESCRIPTION "The Alive Supervision part of the commons library")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids)

