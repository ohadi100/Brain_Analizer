# Project Name and definition:
project("Ipv6Address"
        VERSION 1.0.0
        DESCRIPTION "General utilities for IPv6 address support")
add_library(Ipv6Address Ipv6Address.cpp)

# Project include and link definitions:
target_include_directories(Ipv6Address PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Ipv6Address common_ids)
