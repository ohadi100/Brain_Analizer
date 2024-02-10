# Project Name and definition:
set(CANPDU
    CanPDU.cpp
    CanPduState.cpp
    CanPduParser.cpp
)

project(CanPdu
        VERSION 1.0.0
        DESCRIPTION "CanPdu Library for CAN communication")

add_library(${PROJECT_NAME} ${CANPDU})
target_link_libraries(${PROJECT_NAME} common_ids)
