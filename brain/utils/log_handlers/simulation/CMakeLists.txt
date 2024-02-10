# Project Name and definition:
project("SimulationLogHandler"
        VERSION 1.0.0
        DESCRIPTION "Simulation Log Handler interface")

add_library(${PROJECT_NAME} ${PROJECT_NAME}.cpp ${PROJECT_NAME}.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} Logger)
