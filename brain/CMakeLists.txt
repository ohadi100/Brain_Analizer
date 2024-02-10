# allows the use of target_link_libraries() with targets defined in other directories (cmake 3.13+)
if(POLICY CMP0079 )
  cmake_policy(SET CMP0079 NEW)
endif()

# setting bash path
set(BASE_PATH ${CMAKE_CURRENT_LIST_DIR})

###########################
# Start flags settings    #
###########################
if(DEFINED ENV{BUILD_MONITOR})
    message("BUILDING WITH COVERAGE")
    set(BRAIN_COMPILE_OPTIONS ${BRAIN_COMPILE_OPTIONS} -ftest-coverage -fprofile-arcs)
    set(CMAKE_EXE_LINKER_FLAGS "-ftest-coverage -fprofile-arcs --coverage -lgcov")
endif()

if(DEFINED ENV{MONITOR_MEMORY})
    if($ENV{MONITOR_MEMORY})
        add_definitions(-fsanitize=leak -g -fno-omit-frame-pointer)
        set(BRAIN_LINK_FLAGS "${BRAIN_LINK_FLAGS} -fsanitize=leak -g -fno-omit-frame-pointer")
    endif()
endif()

if(DEFINED EEE_PLATFORM)
    message("BUILDING FOR EEE")
    add_definitions(-DARA_COM_SIMPLE_UTF8_STRING_SERIALIZATION=1)
    add_definitions(-DEXCEPTIONS_ENABLED=1)
endif()

if(DEFINED ENV{SIMULATION})
    message("BUILDING FOR SIMULATION")
    add_definitions(-DSIMULATION=1)

    include_directories(${TEST_FOLDER})
endif()

if (DEFINED HTTPS_PUBLISHER)
    message("HTTPS_PUBLISHER")
    add_definitions(-DHTTPS_PUBLISHER=1)
endif()

if(DEFINED ENV{SSP_PLATFORM})
    add_link_options("-Wl,--no-fatal-warnings")
endif()

set(BRAIN_LINK_FLAGS "${BRAIN_LINK_FLAGS} -rdynamic")

# Strip symbol and relocation information in release versions in order to remove symbols and debug sections which enlarge the binary size
if("${CMAKE_BUILD_TYPE}" STREQUAL "release")
    set(BRAIN_LINK_FLAGS "${BRAIN_LINK_FLAGS} -s")
endif()

###########################
# End flags settings      #
###########################

if("${BUILD_MODE}" STREQUAL "tests")
MESSAGE( STATUS " BuildMode=tests")
project(e3_ids_gtest
        VERSION 0.1.0
        LANGUAGES CXX)
else()
MESSAGE( STATUS " BuildMode=normal")
project(e3_ids
        VERSION 0.1.0
        LANGUAGES CXX)
endif()

get_directory_property(HAS_PARENT PARENT_DIRECTORY)

message(STATUS "e3_ids project cmake begin")

set(CONTAINER_NAME "${PROJECT_NAME}")

####################################
# Start compile the common library #
####################################
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${COMMON_FOLDER})
FOREACH(subdir ${SUBDIRS})
    include_directories(${COMMON_FOLDER}/${subdir})
ENDFOREACH()
SUBDIRLIST(SUBDIRS ${COMMON_FOLDER}/utils)
FOREACH(subdir ${SUBDIRS})
    include_directories(${COMMON_FOLDER}/utils/${subdir})
ENDFOREACH()
SUBDIRLIST(SUBDIRS ${COMMON_FOLDER}/utils/os)
FOREACH(subdir ${SUBDIRS})
    include_directories(${COMMON_FOLDER}/utils/os/${subdir})
ENDFOREACH()
SUBDIRLIST(SUBDIRS ${COMMON_FOLDER}/mocks)
FOREACH(subdir ${SUBDIRS})
    include_directories(${COMMON_FOLDER}/mocks/${subdir})
ENDFOREACH()
SUBDIRLIST(SUBDIRS ${COMMON_FOLDER}/persistent_memory)
FOREACH(subdir ${SUBDIRS})
    include_directories(${COMMON_FOLDER}/persistent_memory/${subdir})
ENDFOREACH()

include_directories(${BRAIN_FOLDER})
##################################
# End compile the common library #
##################################

# Handle diagnostic files and library
if( (DEFINED PPE_PLATFORM) OR (DEFINED ENV{PPE_PLATFORM_TEST}) OR ("${BUILD_MODE}" STREQUAL "normal" AND DEFINED ENV{SIMULATION} AND NOT DEFINED ENV{SSP_SIMULATION}))
    FILE (GLOB_RECURSE arxml_sources  ${BASE_PATH}/generated/**/*.cpp)
    set(diagnostic_external_sources
        ${CONAN_INCLUDE_DIRS_ADG2_DM_CONFIGURATION}/sourcecode/DiagAPI/ids/src/ac/dm/diag_api/ids_id.cpp
        ${CONAN_INCLUDE_DIRS_ADG2_DM_CONFIGURATION}/sourcecode/DiagAPI/ids/src/ara/diag/app_ids.cpp
        ${CONAN_INCLUDE_DIRS_ADG2_DM_CONFIGURATION}/sourcecode/DiagAPI/ids/src/ara/diag/intrusion_detection_system_error_counter.cpp
        ${CONAN_INCLUDE_DIRS_ADG2_DM_CONFIGURATION}/sourcecode/DiagAPI/ids/src/ara/diag/intrusion_detection_system_reset_life_cycle_data.cpp
        ${CONAN_INCLUDE_DIRS_ADG2_DM_CONFIGURATION}/sourcecode/DiagAPI/ids/src/ara/diag/intrusion_detection_system_warning_counter.cpp
    )

    if(NOT "${BUILD_MODE}" STREQUAL "tests")
        set(diagnostic_external_sources
            ${diagnostic_external_sources}
            ${CONAN_INCLUDE_DIRS_ADG2_DM_CONFIGURATION}/sourcecode/dal/ids/GeneratedDiagnosticAccessor.cpp
            ${CONAN_INCLUDE_DIRS_ADG2_DM_CONFIGURATION}/sourcecode/dal/ids/GeneratedDataTypes.cpp
            ${CONAN_INCLUDE_DIRS_ADG2_DM_CONFIGURATION}/sourcecode/dal/ids/GeneratedDiagnosticAccessorInitDelegate.cpp
        )
    endif()

    set(DIAGNOSTICS_COMPILATION_FLAGS "-Wno-inconsistent-missing-override")
    set(DIAGNOSTICS_COMPILATION_FLAGS "${DIAGNOSTICS_COMPILATION_FLAGS};-Wno-sign-compare")
    set(DIAGNOSTICS_COMPILATION_FLAGS "${DIAGNOSTICS_COMPILATION_FLAGS};-Wno-shadow")
    # -Wno-int-in-bool-context is not supported in the HCP5 compiler
    if(DEFINED ENV{SIMULATION})
        set(DIAGNOSTICS_COMPILATION_FLAGS "${DIAGNOSTICS_COMPILATION_FLAGS};-Wno-int-in-bool-context")
    endif()

    set_source_files_properties(
        ${diagnostic_external_sources}
        PROPERTIES
        COMPILE_OPTIONS "${DIAGNOSTICS_COMPILATION_FLAGS}"
    )

    add_library(diagnostic_ext_sources_lib ${diagnostic_external_sources})
    target_link_libraries(diagnostic_ext_sources_lib dal)
endif()

###############################
# Include directories         #
###############################
set(BRAIN_INCLUDE_DIRS
    ..
    ${BASE_PATH}
    ${BASE_PATH}/generated
    ${BASE_PATH}/utils/nanopb
    ${RSI_ACCESS_INCLUDE_PATH}
    ${RSI_GENERATED_INCLUDE_PATH}
    ${VEHICLE_DATA_INC}
    ${HISTOGRAM_LIB_INCLUDE_PATH}
    )

if((DEFINED ENV{SSP_PLATFORM}) OR (DEFINED ENV{SSP_PLATFORM_TEST}) OR (DEFINED ENV{SSP_SIMULATION}))
    set(PORTAL_LIB_BUILD_PATH ${CMAKE_CURRENT_BINARY_DIR}/communicator/ids_portal/ids-service)
    set(PORTAL_LIB_BUILD_PATH ${PORTAL_LIB_BUILD_PATH} ${CMAKE_CURRENT_BINARY_DIR}/communicator/ids_portal/proto)
    set(PORTAL_LIB_INCLUDE_PATH ${CMAKE_CURRENT_BINARY_DIR}/communicator/ids_portal)
    set(PORTAL_LIB_INCLUDE_PATH ${PORTAL_LIB_INCLUDE_PATH} ${BASE_PATH}/communicator/ids_portal)

    set(BRAIN_INCLUDE_DIRS ${BRAIN_INCLUDE_DIRS} ${PORTAL_LIB_INCLUDE_PATH})
endif()

if((DEFINED PPE_PLATFORM) OR (DEFINED ENV{PPE_PLATFORM_TEST}) OR ("${BUILD_MODE}" STREQUAL "normal" AND DEFINED ENV{SIMULATION} AND NOT DEFINED ENV{SSP_SIMULATION}))
    set(BRAIN_INCLUDE_DIRS ${BRAIN_INCLUDE_DIRS} ${CONAN_INCLUDE_DIRS_ADG2_DM_CONFIGURATION}/sourcecode/DiagAPI/ids/inc)
endif()

if(NOT DEFINED EEE_PLATFORM)
	set(BRAIN_INCLUDE_DIRS
        ${BRAIN_INCLUDE_DIRS}
        )
endif()

###############################
# Compile options             #
###############################
include(${CMAKE_FOLDER}/toolchains/ppe_toolchain.cmake)

###############################
# Start unit test files       #
###############################
if("${BUILD_MODE}" STREQUAL "tests")
FILE (GLOB internal_player internal_player/*.cpp)
    if(NOT DEFINED ENV{SSP_PLATFORM_TEST})
        message(STATUS "BUILD EEE TEST")

        set(GDC_PUBLISHER_TEST_SOURCES
            ${TEST_FOLDER}/unit/brain/sender/BELogicSM_utest.cpp
            ${TEST_FOLDER}/unit/brain/sender/BELogicSM_utest.hpp
            ${TEST_FOLDER}/unit/brain/sender/SenderManager_utest.cpp
            ${TEST_FOLDER}/unit/brain/sender/SenderManager_utest.hpp
            ${TEST_FOLDER}/unit/brain/sender/Creditor_utest.cpp
            ${TEST_FOLDER}/unit/brain/sender/Creditor_utest.hpp
            ${TEST_FOLDER}/unit/brain/sender/EventsStorage_utest.cpp
            ${TEST_FOLDER}/unit/brain/sender/EventsStorage_utest.hpp
            ${TEST_FOLDER}/unit/brain/sender/publishers/GDCPublisher_utest.cpp
            ${TEST_FOLDER}/unit/brain/sender/publishers/GDCPublisher_utest.hpp
            ${TEST_FOLDER}/unit/brain/sender/publishers/ExceededMessageSizeCheck_utest.cpp
            ${TEST_FOLDER}/unit/brain/sender/publishers/GDC/GDCAgent_utest.cpp
            ${TEST_FOLDER}/unit/brain/sender/publishers/GDC/GDCAgent_utest.hpp
            ${TEST_FOLDER}/unit/brain/sender/publishers/GDC/GDCMasterMock.cpp
            ${TEST_FOLDER}/unit/brain/sender/publishers/GDC/GDCMasterMock.hpp
        )
        FILE (GLOB autogen_sources 
                                ${TEST_FOLDER}/unit/autogen/proto/*.cc
                                ${TEST_FOLDER}/unit/brain/sensor_data/idshostsensor/SomeIPHostSensorDataTest.cpp
                                ${TEST_FOLDER}/unit/sourcecode/dal/ids/*.cpp)

        FILE (GLOB_RECURSE tests_sources  
                                ${TEST_FOLDER}/unit/brain/brain_app/*.cpp
                                ${TEST_FOLDER}/unit/brain/communicator/*.cpp
                                ${TEST_FOLDER}/unit/brain/diagnostics/*.cpp
                                ${TEST_FOLDER}/unit/brain/engines/idshostsensor/*.cpp
                                ${TEST_FOLDER}/unit/brain/engines/PPE/*.cpp
                                ${TEST_FOLDER}/unit/brain/engines/qlah/*.cpp
                                ${TEST_FOLDER}/unit/brain/engines/security_events/*.cpp
                                ${TEST_FOLDER}/unit/brain/engines/swpac/*.cpp
                                ${TEST_FOLDER}/unit/brain/events/*.cpp
                                ${TEST_FOLDER}/unit/brain/histogram/*.cpp
                                ${TEST_FOLDER}/unit/brain/integration/*.cpp
                                ${TEST_FOLDER}/unit/brain/noise_filter/*.cpp
                                ${TEST_FOLDER}/unit/brain/messageRepository/*.cpp
                                ${TEST_FOLDER}/unit/brain/sensor_data/*.cpp
                                ${TEST_FOLDER}/unit/brain/suspendToRamTest/*.cpp
                                ${TEST_FOLDER}/unit/brain/utils/*.cpp
                                ${TEST_FOLDER}/unit/common/**/*.cpp
                                ${TEST_FOLDER}/unit/resources/*.cpp
                                ${TEST_FOLDER}/unit/sourcecode/*.cpp
                                ${TEST_FOLDER}/unit/test_utils/*.cpp
                                ${TEST_FOLDER}/unit/resources/*.cpp
                                ${TEST_FOLDER}/unit/brain/persistence/**/*.cpp
                                )
        
        set(TEST_SOURCES ${TEST_SOURCES} ${autogen_sources} ${tests_sources} ${GDC_PUBLISHER_TEST_SOURCES})
    #SSP Platform tests
    else()
        message(STATUS "BUILD SSP TEST")

        set(SSP_PUBLISHER_TEST_SOURCES
            ${TEST_FOLDER}/unit/brain/sender/publishers/SSP/SSPPublisher_utest.cpp
            ${TEST_FOLDER}/unit/brain/sender/publishers/SSP/PnOrchLibAdapter_utest.cpp
        )
        FILE (GLOB autogen_sources 
                                ${TEST_FOLDER}/unit/brain/communicator/periodic/*.cpp
                                ${TEST_FOLDER}/unit/brain/communicator/CommunicatorManager_utest.cpp
                                ${TEST_FOLDER}/unit/brain/communicator/Communicator_utest.cpp
                                ${TEST_FOLDER}/unit/brain/engines/SSP/*.cpp
                                ${TEST_FOLDER}/unit/brain/counter_manager/*.cpp
                                ${TEST_FOLDER}/unit/brain/events/*.cpp
                                ${TEST_FOLDER}/unit/brain/histogram/*.cpp
                                ${TEST_FOLDER}/unit/brain/infra/*.cpp
                                ${TEST_FOLDER}/unit/brain/utils/**/*.cpp
                                ${TEST_FOLDER}/unit/common/**/*.cpp
                                ${TEST_FOLDER}/unit/brain/sensor_data/swpac/SWPACTestConstants.cpp)

        FILE (GLOB_RECURSE tests_sources  
                ${TEST_FOLDER}/resources/json_utils
                sender/publishers/HTTPSPublisher.cpp
                ${BASE_PATH}/communicator/FileSystemCommunicator/SensorGenerator.cpp
                ${BASE_PATH}/communicator/FileSystemCommunicator/FileSystemCommunicator.cpp
                ${BASE_PATH}/communicator/FileSystemCommunicator/FolderMonitor.cpp
        )
        set(TEST_SOURCES ${TEST_SOURCES} ${tests_sources} ${autogen_sources} ${SSP_PUBLISHER_TEST_SOURCES})
    endif()

    set(TEST_LIB_TARGET_NAME test_lib)
    add_library(${TEST_LIB_TARGET_NAME} STATIC ${TEST_SOURCES})
    target_link_libraries(${TEST_LIB_TARGET_NAME}
                            engines
                            EngineDispatcherBase
                            AraPersistentMemory
                            FsPersistentMemoryManager
                            FileLogHandler
                            $<$<BOOL:$ENV{SSP_PLATFORM_TEST}>:Brain::Publishers::SSP_Publisher>
                            )
    target_compile_options(${TEST_LIB_TARGET_NAME} PUBLIC ${TEST_COMPILATION_FLAGS})

    set(TEST_INCLUDES
        ${TEST_FOLDER}/unit/brain
        ${TEST_FOLDER}/unit/
        ${TEST_FOLDER}
        ${BRAIN_FOLDER}
        ${BRAIN_FOLDER}/utils
        )
        target_include_directories(${TEST_LIB_TARGET_NAME} PUBLIC ${TEST_INCLUDES})
endif()

include_directories(${BRAIN_INCLUDE_DIRS})

message(STATUS "container name: ${CONTAINER_NAME}")

# Linker directories (must come before the target definition)
link_directories(${RSI_ACCESS_LIBS_PATH}
                 ${CONAN_LIB_DIRS}
                 ${HISTOGRAM_LIB_BUILD_PATH})


if(DEFINED ENV{SSP_PLATFORM} OR DEFINED ENV{SSP_PLATFORM_TEST} OR DEFINED ENV{SSP_SIMULATION})
    link_directories(${PORTAL_LIB_BUILD_PATH})
endif()

if(DEFINED ENV{SSP_PLATFORM})
    vwos_add_executable(
        ${CONTAINER_NAME}
        app/main.cpp
        )
elseif (DEFINED HCP5_PLATFORM)
    vwos_add_executable(
        ${CONTAINER_NAME}
        main.cpp
        )
elseif ("${BUILD_MODE}" STREQUAL "normal") # simulator
    if(DEFINED ENV{SSP_SIMULATION})
        add_executable(
            ${CONTAINER_NAME}
            app/main.cpp
            )
    else()
        vwos_add_executable(
            ${CONTAINER_NAME}
            main.cpp
            )
    endif()
elseif (DEFINED ENV{SSP_PLATFORM_TEST})
    add_executable(
        ${CONTAINER_NAME}
        ${TEST_FOLDER}/platform/SSP_main/main.cpp
        )
else()
    set_source_files_properties(${TEST_FOLDER}/platform/PPE_main/main.cpp PROPERTIES COMPILE_FLAGS "-Wno-ctor-dtor-privacy")
    vwos_add_executable(
        ${CONTAINER_NAME}
        ${TEST_FOLDER}/platform/PPE_main/main.cpp
        )
endif()

add_subdirectory(${AUTOGEN_NANOPB_DIRECTORY} ${BASE_PATH}/../build/lib)
add_subdirectory(${HISTOGRAM_LIB_SUBMODULE_PATH} ${HISTOGRAM_LIB_BUILD_PATH})  # ToDo - put histogram lib in common IDSMEB-603 

if(DEFINED HCP5_PLATFORM)
    set(BUILD_STATIC_LIBS 1)
    unset(BUILD_STATIC_LIBS)
endif()

target_compile_options(${CONTAINER_NAME} PUBLIC ${BRAIN_COMPILE_OPTIONS})

set(BRAIN_COMPILE_DEFINITIONS _GLIBCXX_USE_NANOSLEEP LINUX BRAIN)

# Following definitions are needed for libsci's e3-asio dependency.
set(BRAIN_COMPILE_DEFINITIONS ${BRAIN_COMPILE_DEFINITIONS} ASIO_STANDALONE ASIO_HEADER_ONLY ASIO_SEPARATE_COMPILATION ASIO_NO_TYPEID)

target_compile_definitions(${CONTAINER_NAME} PUBLIC ${BRAIN_COMPILE_DEFINITIONS})

set(BRAIN_INCLUDES
    ${CONAN_INCLUDE_DIRS}
    "${BASE_PATH}/utils/nanopb/"
    )

if("${BUILD_MODE}" STREQUAL "tests")
    set(BRAIN_INCLUDES
        ${BRAIN_INCLUDES}
        ${TEST_FOLDER}/unit/brain
        ${TEST_FOLDER}/unit
        )
endif()

if(NOT DEFINED HCP5_PLATFORM)
    set(PTHREAD_LIB pthread)
endif()

set(BRAIN_LIBS
    common_ids
    ${PTHREAD_LIB}
    gen_nanopb
    histogram-lib
    )

if(NOT DEFINED EEE_PLATFORM)
    set(BRAIN_LIBS
        ${BRAIN_LIBS}
        )
endif()

if("${BUILD_MODE}" STREQUAL "tests")
    set(BRAIN_LIBS -Wl,--whole-archive test_lib -Wl,--no-whole-archive ${BRAIN_LIBS})
elseif(DEFINED ENV{SIMULATION})
    target_sources(${CONTAINER_NAME} PUBLIC ${TEST_FOLDER}/unit/brain/sensor_data/swpac/SWPACTestConstants.cpp)
    set(BRAIN_LIBS -Wl,--whole-archive -Wl,--no-whole-archive ${BRAIN_LIBS})
endif()

# When linking, dependent library should come on the left
# Circular dependency caused by the requirement to compile code from adg2_DM_configuration forces brain libraries
# to be both on the left & right side of adg2_DM_configuration lib
# Therefore, BRAIN_LIBS is added twice
if(DEFINED EEE_PLATFORM) 
    set(BRAIN_LIBS
        ${BRAIN_LIBS}
        ${CONAN_LIBS}
        )
    if((NOT DEFINED ENV{SSP_PLATFORM}) AND (NOT DEFINED ENV{SSP_PLATFORM_TEST}) AND (NOT DEFINED ENV{SSP_SIMULATION}))
        set(BRAIN_LIBS
            ${BRAIN_LIBS}
        )
    endif()
else()
    if((NOT DEFINED ENV{SSP_PLATFORM_TEST}) AND (NOT DEFINED ENV{SSP_SIMULATION}))
        set(BRAIN_LIBS
        ${BRAIN_LIBS}
        ${CONAN_LIBS}
        -Wl,--no-as-needed libconfig_loader.so
        )
    else()
        set(BRAIN_LIBS
        ${BRAIN_LIBS}
        ${CONAN_LIBS}
        #-Wl,--no-as-needed libconfig_loader.so
        )
endif()

endif()

if( (DEFINED PPE_PLATFORM) OR (DEFINED ENV{PPE_PLATFORM_TEST}) OR ("${BUILD_MODE}" STREQUAL "normal" AND DEFINED ENV{SIMULATION} AND NOT DEFINED ENV{SSP_SIMULATION}) )
    add_library(arxml_ext_sources_lib ${arxml_sources})
    add_subdirectory(sensor_data)
endif()

##############################################
# Add the subdirectory sources to be compile #
##############################################
add_subdirectory(brain_app)
add_subdirectory(communicator)
add_subdirectory(config)
add_subdirectory(diagnostics)
add_subdirectory(engines)
add_subdirectory(events)
add_subdirectory(histograms)
add_subdirectory(noise_filter)
add_subdirectory(sender)
add_subdirectory(utils)
add_subdirectory(messageRepository)

if(NOT DEFINED EEE_PLATFORM)
    add_subdirectory(internal_player)
endif()

#####################################################
# Start define the libraries to be linked with main #
#####################################################
target_link_libraries(${CONTAINER_NAME} 
    ${BRAIN_LIBS} 
    BrainApp
    PeriodicCommunicator
    communicator
    BrainConfiguration
    engines
    events
    Histograms
    EventNoiseFilter
    SensorNoiseFilter
    noise_filter
    Sender
    Ipv6Address
    NanoPB
    VehicleData
    BrainUtils
    FileSystemCommunicator
    DiagnosticsManager
    security_events
    MessageRepository)

if(DEFINED PPE_PLATFORM)
    target_link_libraries(${CONTAINER_NAME} 
        UDSCommunicator    
        QlahSensorData
        SecurityEventSensorData
        SWPAC
        diagdata
        SCICommunicator
        someip
        diag_accessor
        dtc
        measurement_values
        diagnostic_routines
        qlah_engines
        ResourceConsumptionNotification_engine
        SWPAC_engines)
elseif(DEFINED ENV{SSP_PLATFORM})
    target_link_libraries(${CONTAINER_NAME} idspubsub-api ids-service PortalCommunicator)
else()
    target_link_libraries(${CONTAINER_NAME} internal_player)
endif()

if (DEFINED HTTPS_PUBLISHER)
    target_link_libraries(${CONTAINER_NAME} HTTPS_Publisher)
else()
    target_link_libraries(${CONTAINER_NAME} GDC_1.2_Publisher)
endif()
if("${BUILD_MODE}" STREQUAL "tests")
    add_subdirectory(utils/log_handlers/simulation)
    add_subdirectory(utils/log_handlers/file)
    add_subdirectory(persistence/ara_per)
    add_subdirectory(persistence/fs_per)
    target_link_libraries(${TEST_LIB_TARGET_NAME} AraPersistentMemory FsPersistentMemoryManager FileLogHandler SimulationLogHandler SecurityEventSensorData)
    target_link_libraries(${CONTAINER_NAME} FsPersistentMemoryManager SimulationLogHandler)
elseif(DEFINED ENV{EEE_PLATFORM} AND (NOT DEFINED ENV{SSP_PLATFORM}))
    add_subdirectory(persistence/ara_per)
    add_subdirectory(utils/log_handlers/aralog)
    target_link_libraries(${CONTAINER_NAME} AraPersistentMemory IcasLogHandler)
else()
    add_subdirectory(persistence/fs_per)
    add_subdirectory(utils/log_handlers/simulation)
    target_link_libraries(${CONTAINER_NAME} FsPersistentMemoryManager SimulationLogHandler)
endif()

get_target_property(includePath ${CONTAINER_NAME} INCLUDE_DIRECTORIES)

###################################################
# End define the libraries to be linked with main #
###################################################

set_target_properties(${CONTAINER_NAME} PROPERTIES LINK_FLAGS ${BRAIN_LINK_FLAGS})

add_custom_target(brain_create_version_info_file COMMAND ${BASE_PATH}/../scripts/create_version_info_file.sh "${BUILD_OPTS}" COMMENT "Creating ${VERSION_FILE} ${BUILD_OPTS}")

add_dependencies(${CONTAINER_NAME} brain_create_version_info_file)

if(HAS_PARENT)
    set(BRAIN_COMPILE_OPTIONS ${BRAIN_COMPILE_OPTIONS} PARENT_SCOPE)
    set(BRAIN_COMPILE_DEFINITIONS ${BRAIN_COMPILE_DEFINITIONS} PARENT_SCOPE)
    set(BRAIN_LIBS  ${BRAIN_LIBS} PARENT_SCOPE)
endif()


install(TARGETS ${CONTAINER_NAME} DESTINATION bin) #TODO once ${CONTAINER_NAME}.debug will be available, need to change this line if the comment out bellow

message(STATUS "e3_ids project CMake end")