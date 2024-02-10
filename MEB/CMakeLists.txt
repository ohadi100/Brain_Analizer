cmake_minimum_required(VERSION 3.9)

###############################################
#             Brain definitions               #
###############################################

project(brain
        VERSION 0.1.0
        LANGUAGES CXX)

set(BASE_PATH_MEB ${CMAKE_CURRENT_LIST_DIR})

# Using old flag that implies a release environment - we will be able to change it after - IDSPPE-2798 
add_definitions(-DRELEASE=1)
add_definitions(-DMEB_PLATFORM=1)

set(BRAIN_DIR ${BASE_PATH_MEB}/brain)

message(STATUS "MEB base path: ${BASE_PATH_MEB}")

set(CMAKE_BINARY_DIR ${BASE_PATH_MEB}/output)
message(STATUS "MEB Output folder path: ${CMAKE_BINARY_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)

set(BASE_PATH ${CMAKE_CURRENT_LIST_DIR}/brain)

set(JSONCPP_MAIN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ext/jsoncpp/linux/jsoncpp)
set(JSONCPP_LIBRARY_PATH ${JSONCPP_MAIN_PATH}/lib)
set(JSONCPP_INCLUDE_PATH ${JSONCPP_MAIN_PATH}/include)

set(HISTOGRAM_LIB_SUBMODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ext/histogram-lib)
set(HISTOGRAM_LIB_BUILD_PATH ${HISTOGRAM_LIB_SUBMODULE_PATH}/build)
set(HISTOGRAM_LIB_INCLUDE_PATH ${HISTOGRAM_LIB_SUBMODULE_PATH}/include)

set(CAN_ALGO_PLATFORM_NAME UNECE CACHE INTERNAL "the default platform for compilation")

###################################################
#      Include CMake scripts                      #
###################################################

include(common/include_paths.cmake)
include(brain/include_paths.cmake)
include(brain/main/linked_libs.cmake)
include(../../../cmake/toolchains/meb_toolchain.cmake)
include(../../../cmake/modules/utils.cmake)
include(../../../cmake/modules/corbos_plugets.cmake) 

###################################################
#      IDS Version                                #
###################################################

# CMake variables use by CMakeLists.txt at common/utils/verison 
set(IDS_VERSION)
set(IDS_COMMIT_HASH)

extract_git_branch(IDS_VERSION)
extract_git_hash(IDS_COMMIT_HASH)

###################################################
#      Specify includes                           #
###################################################

set(MEB_INCLUDES 
    ${BRAIN_DIR}/main/MEB
    ${BRAIN_DIR}/engines/MEB
    ${BRAIN_DIR}/utils/log_handlers/aralog_legacy
    ${BASE_PATH_MEB}/generated 
    ${BRAIN_DIR}/communicator/legacySomeip
    ${BRAIN_DIR}/communicator/CanCommunicator
    )

include_directories(
    ${COMMON_INCLUDE_PATHS}         # Coming from common/include_paths 
    ${BRAIN_INCLUDE_PATHS}          # Coming from brain/include_paths
    ${MEB_INCLUDES}                
    ${HISTOGRAM_LIB_INCLUDE_PATH}   # ToDo - put histogram lib in common IDSMEB-603
    ${JSONCPP_INCLUDE_PATH}
    ${BASE_PATH_MEB}                # Support for legacy includes
)

#######################################################
#                 Add modules                         #
#######################################################

# Q&D Workaround - Compile only Communicator.cpp and avoid looking at all the CMakeLists.txt files in the subdirectories
# ToDo - IDSPPE-1456 take to Communicator CMake as part of fixing Communicator CMake
add_library(BaseCommunicator ${BRAIN_DIR}/communicator/Communicator.cpp)

add_subdirectory(common ${CMAKE_BINARY_DIR}/${COMMON_DIR})
add_subdirectory(${HISTOGRAM_LIB_SUBMODULE_PATH} ${HISTOGRAM_LIB_BUILD_PATH}) # ToDo - put histogram lib in common IDSMEB-603 
add_subdirectory(${BRAIN_DIR}/histograms ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/histograms)
add_subdirectory(autogen/nanopb  ${CMAKE_BINARY_DIR}/autogen/nanopb)
add_subdirectory(${BRAIN_DIR}/main/MEB ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/main)  
add_subdirectory(${BRAIN_DIR}/utils/log_handlers/aralog_legacy ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/aralog)
add_subdirectory(${BRAIN_DIR}/utils/supervision_adapter/supervision_icas1 ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/supervision_icas1)
add_subdirectory(${BRAIN_DIR}/utils/power_state_adapter/component_client ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/component_client)
add_subdirectory(${BRAIN_DIR}/persistence/ara_per_legacy ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/ara_per)
add_subdirectory(${BRAIN_DIR}/communicator/legacySomeip ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/legacySomeip)
add_subdirectory(${BRAIN_DIR}/canPdu ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/canPdu)
add_subdirectory(${BRAIN_DIR}/utils/execution_reporter/application_client ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/execution_reporter)
add_subdirectory(${BRAIN_DIR}/utils ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/utils)
add_subdirectory(${BRAIN_DIR}/events ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/events)
add_subdirectory(${BRAIN_DIR}/messageRepository ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/messageRepository)
add_subdirectory(${BRAIN_DIR}/sender ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/sender)
add_subdirectory(${BRAIN_DIR}/sender/publishers/ids_proxy_someip ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/ids_proxy_publisher)
add_subdirectory(${BRAIN_DIR}/communicator/CanCommunicator ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/canCommunicator)
add_subdirectory(${BRAIN_DIR}/noise_filter ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/noise_filter)
add_subdirectory(${BRAIN_DIR}/engines/serializer ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/serializer)
add_subdirectory(${BRAIN_DIR}/engines/dispatcher ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/dispatcher)
add_subdirectory(${BRAIN_DIR}/engines/MEB ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/MebEngines)
add_subdirectory(${BRAIN_DIR}/engines/can ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/canEngines)
add_subdirectory(${BASE_PATH_MEB}/ext/can_algorithm ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/can_algorithm)
add_subdirectory(${BRAIN_DIR}/communicator/periodic ${CMAKE_BINARY_DIR}/${BRAIN_DIR}/periodic)

# ToDo - IDSPPE-1456 take to Communicator CMake as part of fixing Communicator CMake
target_link_libraries(BaseCommunicator common_ids noise_filter)

######################################
#       Main compilation             #   
######################################

icas_add_executable(
        BINARY ${PROJECT_NAME}
        EXE_SRCS brain/main/main.cpp
        MAKE_TARGET_PREFIX ${PROJECT_NAME}
)

target_link_libraries(${PROJECT_NAME}
                      ${LINK_TO_MAIN} # Coming from main/linked_libs
                      
)

##############################################################
#               Definition of compilation                   #   
##############################################################

set(BRAIN_COMPILE_DEFINITIONS _GLIBCXX_USE_NANOSLEEP BRAIN ${OS_PLATFORM})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${BRAIN_COMPILE_DEFINITIONS})