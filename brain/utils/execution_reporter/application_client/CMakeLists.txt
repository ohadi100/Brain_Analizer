set(DOMAIN_LIBS
    ara_exec
)    

project(ExecutionReporter
        VERSION 1.0.0
        DESCRIPTION "General utilities for the brain library")

add_library(${PROJECT_NAME} STATIC ExecutionReporter.cpp)

target_link_libraries(${PROJECT_NAME} ${DOMAIN_LIBS})
