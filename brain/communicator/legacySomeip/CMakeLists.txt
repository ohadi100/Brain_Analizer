# Project Name and definition:
set(COMMUNICATORS
    IdsProxyRelayCommunicator.cpp
    IdsEthCommunicator.cpp
    IdsImmobilizerCommunicator.cpp
    IdsIpSecurityCommunicator.cpp
    IdsSecurityEventCommunicator.cpp
)

set(DOMAIN_LIBS
    ara_com
)

project(SomeIpLegacy
        VERSION 1.0.0
        DESCRIPTION "SOME/IP communicator functionality with legacy libraries")

add_library(${PROJECT_NAME} ${COMMUNICATORS})
target_link_libraries(${PROJECT_NAME} common_ids ${DOMAIN_LIBS})
