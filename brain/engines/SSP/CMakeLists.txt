# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/EngineDispatcher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PeriodicStatisticsEngine.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/EngineDispatcher.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PeriodicStatisticsEngine.hpp
)    

# Project Name and definition:
project("EngineDispatcher"
        VERSION 1.0.0
        DESCRIPTION "EngineDispatcher functionality")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${BRAIN_FOLDER}/engines ${BRAIN_FOLDER}/communicator ${BRAIN_FOLDER}/histograms )
target_link_libraries(${PROJECT_NAME} common_ids engines EventNoiseFilter NanoPB FileSystemCommunicator)
