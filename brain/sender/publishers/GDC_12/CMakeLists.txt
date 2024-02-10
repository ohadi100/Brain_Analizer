message(STATUS "CMake process for GDC_1.2 publisher start")

include_directories(${BRAIN_FOLDER}/sender/publishers/interface)
add_subdirectory(GDC)

# Project Name and definition:
project("GDC_1.2_Publisher"
        VERSION 1.0.0
        DESCRIPTION "GDC_1.2 publisher functionality")

set(PUBLISHER_SOURCES GDCPublisher.cpp)

add_library(${PROJECT_NAME} ${PUBLISHER_SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} arxml_ext_sources_lib common_ids GDCAgent ExceededMessageSizeCheck)

message(STATUS "End of CMake process for PPE publisher")