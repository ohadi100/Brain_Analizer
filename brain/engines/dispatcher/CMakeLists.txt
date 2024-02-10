set(SOURCES
${CMAKE_CURRENT_LIST_DIR}/EngineDispatcherBase.cpp)

set(HEADERS
${CMAKE_CURRENT_LIST_DIR}/EngineDispatcherBase.hpp)

# Project Name and definition:
project(EngineDispatcherBase
        VERSION 1.0.0
        DESCRIPTION "EngineDispatcher for running engines")

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} common_ids)
