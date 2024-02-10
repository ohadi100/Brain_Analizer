# Project Name and definition:
set(CANCOMM
    CanCommunicator.cpp
)

project(CanCommunicator
        VERSION 1.0.0
        DESCRIPTION "CAN communicator functionality with legacy libraries")

add_library(${PROJECT_NAME} ${CANCOMM})
target_link_libraries(${PROJECT_NAME} BaseCommunicator common_ids)
