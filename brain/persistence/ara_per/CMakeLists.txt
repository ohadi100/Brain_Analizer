set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/AraPersistentMemoryManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PersistentMemoryManagerBuilder.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/AraPersistentMemoryManager.hpp
)

# Project Name and definition:
project("AraPersistentMemory"
        VERSION 1.0.0
        DESCRIPTION "The Ara-Persistent Memory manager and repository")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
add_subdirectory(AraPersistentDB)
target_link_libraries(${PROJECT_NAME} common_ids AraPersistentDB)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
