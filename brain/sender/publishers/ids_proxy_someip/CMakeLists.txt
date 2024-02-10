set(DOMAIN_LIBS
    ara_com
)        

# Project Name and definition:
project(IdsProxyPublisher
        VERSION 1.0.0
        DESCRIPTION "Ids Proxy connection library from Brain, on ICAS1")

add_library(${PROJECT_NAME} IdsProxyPublisher.cpp brain_to_proxy_server/BrainToProxyServer.cpp)

target_link_libraries(${PROJECT_NAME} common_ids ${DOMAIN_LIBS})
