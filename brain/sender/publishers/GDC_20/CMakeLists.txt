find_package(gdc-2.0-onboard-pn-orch)

add_library(SSPPublisher STATIC
    SSPPublisher.cpp
    PnOrchLibAdapter.cpp
)

add_library(Brain::Publishers::SSP_Publisher ALIAS SSPPublisher)

target_link_libraries(SSPPublisher
    PUBLIC
    gdc-2.0-onboard-pn-orch::PnOrch
    PublisherInterface
)

target_include_directories(SSPPublisher
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Prevent target from being built unless depended upon
set_target_properties(SSPPublisher PROPERTIES EXCLUDE_FROM_ALL TRUE)