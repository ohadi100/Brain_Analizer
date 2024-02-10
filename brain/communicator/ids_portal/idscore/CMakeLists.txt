find_package(portal REQUIRED)

set(HEADERS
)

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/idscore.cpp
)

add_executable(idscore
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(idscore
    PUBLIC
        idspubsub-api::idspubsub-api
        portal::libportal
        portal::libportal-rsocket
)

set_target_properties(idscore
    PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS ON
)