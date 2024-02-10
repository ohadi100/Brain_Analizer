# Install script for directory: /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils

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
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/conditionalSleep/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/CPP/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/diagnostics/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/GUID/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/jsonUtils/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/logger/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/os/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/random/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/singleQueue/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/socket/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/timer/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/typeCasting/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/types/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/wrr/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/stateMachine/cmake_install.cmake")

endif()

