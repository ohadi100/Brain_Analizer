set(DOMAIN_LIBS
    keyvaluestorage
)

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/AraPersistentMemoryManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PersistentMemoryManagerBuilder.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/AraPersistentMemoryManager.hpp
)

# Project Name and definition:
project(AraPersistentMemory
        VERSION 1.0.0
        DESCRIPTION "The Ara-Persistent Memory manager for legacy library")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_link_libraries(${PROJECT_NAME} ${DOMAIN_LIBS} common_ids)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
