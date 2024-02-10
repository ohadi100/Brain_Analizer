# Project Name and definition:
project("Sender"
        VERSION 1.0.0
        DESCRIPTION "General utilities for the brain library")
add_library(${PROJECT_NAME} Creditor.cpp EventsStorage.cpp BELogicStates.cpp BELogicSM.cpp SenderManager.cpp)

# ToDo - remove after IDSPPE-1456 - each project will define its publisher
add_subdirectory(publishers)

# Project include and link definitions:
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} common_ids ExceededMessageSizeCheck events) 
