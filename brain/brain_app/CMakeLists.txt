# Define parts of project:
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/BrainApp.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/BrainApp.hpp
)    

# Project Name and definition:
project("BrainApp"
        VERSION 1.0.0
        DESCRIPTION "The brain application object")
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${TEST_FOLDER})

target_link_directories(${PROJECT_NAME} PUBLIC ${CONAN_LIB_DIRS})
target_link_libraries(${PROJECT_NAME} common_ids ${CONAN_LIBS})

if((DEFINED ENV{SSP_PLATFORM}) OR (DEFINED ENV{SSP_SIMULATION}) OR (DEFINED ENV{SSP_PLATFORM_TEST}))
    target_link_libraries(${PROJECT_NAME} Brain::Publishers::SSP_Publisher)
endif()
