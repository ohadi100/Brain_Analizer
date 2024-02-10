set(DOMAIN_LIBS
    phm_client_lib
)

project(SupervisionAdapter
        VERSION 1.0.0
        DESCRIPTION "General utilities for the brain library")

add_library(${PROJECT_NAME} SupervisionAdapter.cpp)

target_link_libraries(${PROJECT_NAME} ${DOMAIN_LIBS})
