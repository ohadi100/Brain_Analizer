# Project name, definition, linkage, and include settings:

project("AraPersistentDB"
        VERSION 1.0.0
        DESCRIPTION "Ara persistent DB functionality")

if(DEFINED EEE_PLATFORM)
    add_library(${PROJECT_NAME} AraPersistentDBEEE.cpp)
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CONAN_INCLUDE_DIRS_ADG2_DM_CONFIGURATION})
    target_link_libraries(${PROJECT_NAME} CounterManager CPP Logger Types ${CONAN_LIBS_ADG2_DM_CONFIGURATION})
else()
    add_library(${PROJECT_NAME} INTERFACE)
    target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
endif()
