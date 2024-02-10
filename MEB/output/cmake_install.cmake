# Install script for directory: /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common

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
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/alive_supervision/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/persistent_memory/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/configuration/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/counter_manager/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/mocks/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/notification_handler/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/sensor_data/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/shutdown_and_enabler/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/thread_handler/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/cmake_install.cmake")
  include("/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/version/cmake_install.cmake")

endif()

