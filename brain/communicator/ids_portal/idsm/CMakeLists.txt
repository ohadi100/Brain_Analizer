find_package(portal REQUIRED)

set(HEADERS
)

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/idsm.cpp
)

add_executable(idsm
    ${SOURCES}
)

target_link_libraries(idsm
    PUBLIC
        portal::libportal
        portal::libportal-rsocket
        idspubsub-api::idspubsub-api
        ids-service::ids-service
)

set_target_properties(idsm
    PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
)