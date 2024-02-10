include(${BASE_PATH_MEB}/brain/main/linked_libs.cmake)

# Library 
project(IdsMainFlow
        VERSION 1.0.0
        DESCRIPTION "MEB main flow")

# Deliderately build one library out of both the IdsMainFlowBase and IdsMainFlow to have clear linkage to one library  
add_library(${PROJECT_NAME} STATIC IdsMainFlow.cpp ${BASE_PATH_MEB}/brain/main/Base/IdsMainFlowBase.cpp)

target_link_libraries(${PROJECT_NAME} 
                      ${LINK_TO_MAIN_FLOW}  # from linked_libs.cmake
                      IdsProxyPublisher
)
