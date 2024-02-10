set(PROTO_FILES
    IdsPubSub.proto
)

set(PORTAL_PROTOC_PATH  "/home/e3-user/.portal/protoc-3.19.1-linux-x86_64.exe")
set(PACKAGE_PATH "/home/e3-user/.conan/data/portal/0.5.11/e3swp/testing/package")
if(DEFINED ENV{SSP_PLATFORM})
    find_package(portal REQUIRED)
    set(PORTAL_PATH "${PACKAGE_PATH}/6e721a5ab0e10e28b8a767bcb7aaf60e6480716d/lib/cmake/portal")
    include("${PORTAL_PATH}/portalConfig.cmake")
else()
    find_package(portal CONFIG REQUIRED HINTS "${PACKAGE_PATH}/29e5f37a5f991cbf11148a7f747177de74fd1e96/lib/cmake/portal")
endif()

# protobuf source files go into the lib just like any other CPP source file
add_library(idspubsub-api ${PROTO_FILES})

# TODO: Get rid of the version here.
portal_generate(idspubsub-api VERSION 0.5.11)

add_library(idspubsub-api::idspubsub-api ALIAS idspubsub-api)
