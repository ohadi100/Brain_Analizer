# Install script for directory: /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/ext/histogram-lib/build/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/histograms/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/autogen/nanopb/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/main/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/aralog/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/supervision_icas1/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/component_client/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/ara_per/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/legacySomeip/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canPdu/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/execution_reporter/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/events/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/messageRepository/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/sender/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/ids_proxy_publisher/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/noise_filter/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/serializer/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/dispatcher/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/MebEngines/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canEngines/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/can_algorithm/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/periodic/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
