# Project Name and definition:
set(CANENGINE
    CanPduAlgoEngine.cpp
    CanPduEventEngine.cpp
)

set(DOMAIN_LIBS
    ara_com
)

project(CanEngine
        VERSION 1.0.0
        DESCRIPTION "CanEngine Library for CAN events")

add_library(${PROJECT_NAME} ${CANENGINE})
target_link_libraries(${PROJECT_NAME} common_ids)
