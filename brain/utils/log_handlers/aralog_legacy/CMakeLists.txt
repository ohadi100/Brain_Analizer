set(DOMAIN_LIBS
    ara_com
)

project(LogAdapter
        VERSION 1.0.0
        DESCRIPTION "Inferface to the legacy ara log library")

add_library(${PROJECT_NAME} AraLogHandler.cpp LoggerInit.cpp)
target_link_libraries(${PROJECT_NAME} Logger ${DOMAIN_LIBS})
