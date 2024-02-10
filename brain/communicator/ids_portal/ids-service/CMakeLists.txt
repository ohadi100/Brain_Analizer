find_package(portal REQUIRED)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/ids_service.hpp
)

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/ids_service.cpp
)

add_library(ids-service
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(ids-service
    PUBLIC
        portal::libportal
        idspubsub-api::idspubsub-api
)

set_target_properties(ids-service PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
)

add_library(ids-service::ids-service ALIAS ids-service)
