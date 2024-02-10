include_directories(${AUTOGEN_NANOPB_DIRECTORY})

# Define parts of project:
set(IDS_NANO_UTILS
    ${CMAKE_CURRENT_LIST_DIR}/Encoders.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Decoders.cpp
)

# ToDo - Move it to ext folder / get via Conan and compile standalone
set(OPEN_SRC_NANO_UTILS
    ${CMAKE_CURRENT_LIST_DIR}/pb_common.c
    ${CMAKE_CURRENT_LIST_DIR}/pb_decode.c
    ${CMAKE_CURRENT_LIST_DIR}/pb_encode.c    
)

# Project Name and definition:
project(NanoPB
        VERSION 1.0.0
        DESCRIPTION "Wrapper for the nanopb Protobuf coding/decoding")
add_library(NanoPB ${IDS_NANO_UTILS} ${OPEN_SRC_NANO_UTILS})

# Project include and link definitions:
link_directories({AUTOGEN_NANOPB_DIRECTORY})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(NanoPB Histograms BrainUtils common_ids gen_nanopb)
