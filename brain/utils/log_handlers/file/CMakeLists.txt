# Project Name and definition:
project("FileLogHandler"
        VERSION 1.0.0
        DESCRIPTION "File log handler interface")

add_library(${PROJECT_NAME} ${PROJECT_NAME}.cpp ${PROJECT_NAME}.hpp)
target_link_libraries(${PROJECT_NAME} Logger)
