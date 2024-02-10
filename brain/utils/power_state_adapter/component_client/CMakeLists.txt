set(DOMAIN_LIBS
    ara_exec
    state_notification
)

project(PowerStateAdapter
        VERSION 1.0.0
        DESCRIPTION "Implementation of Power State Adapter for ICAS1")

add_library(${PROJECT_NAME} STATIC PowerStateAdapter.cpp)
target_link_libraries(${PROJECT_NAME} ${DOMAIN_LIBS})
