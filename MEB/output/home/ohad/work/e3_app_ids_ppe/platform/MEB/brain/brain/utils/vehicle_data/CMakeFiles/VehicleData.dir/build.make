# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/ohad/icas-1-sdk/sysroot/usr/bin/cmake

# The command to remove a file.
RM = /home/ohad/icas-1-sdk/sysroot/usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain

# Include any dependencies generated for this target.
include output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/depend.make

# Include the progress variables for this target.
include output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/progress.make

# Include the compile flags for this target's objects.
include output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/flags.make

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.o: output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/flags.make
output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.o: brain/utils/vehicle_data/VehicleData.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.o"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/VehicleData.dir/VehicleData.cpp.o -c /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/VehicleData.cpp

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VehicleData.dir/VehicleData.cpp.i"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/VehicleData.cpp > CMakeFiles/VehicleData.dir/VehicleData.cpp.i

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VehicleData.dir/VehicleData.cpp.s"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/VehicleData.cpp -o CMakeFiles/VehicleData.dir/VehicleData.cpp.s

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.o.requires:

.PHONY : output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.o.requires

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.o.provides: output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.o.requires
	$(MAKE) -f output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/build.make output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.o.provides.build
.PHONY : output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.o.provides

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.o.provides.build: output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.o


# Object files for target VehicleData
VehicleData_OBJECTS = \
"CMakeFiles/VehicleData.dir/VehicleData.cpp.o"

# External object files for target VehicleData
VehicleData_EXTERNAL_OBJECTS =

output/libs/libVehicleData.a: output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.o
output/libs/libVehicleData.a: output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/build.make
output/libs/libVehicleData.a: output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../../../../../../../../libs/libVehicleData.a"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data && $(CMAKE_COMMAND) -P CMakeFiles/VehicleData.dir/cmake_clean_target.cmake
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VehicleData.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/build: output/libs/libVehicleData.a

.PHONY : output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/build

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/requires: output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/VehicleData.cpp.o.requires

.PHONY : output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/requires

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/clean:
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data && $(CMAKE_COMMAND) -P CMakeFiles/VehicleData.dir/cmake_clean.cmake
.PHONY : output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/clean

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/depend:
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data/CMakeFiles/VehicleData.dir/depend

