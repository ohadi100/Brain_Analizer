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
include output/alive_supervision/CMakeFiles/AliveSupervision.dir/depend.make

# Include the progress variables for this target.
include output/alive_supervision/CMakeFiles/AliveSupervision.dir/progress.make

# Include the compile flags for this target's objects.
include output/alive_supervision/CMakeFiles/AliveSupervision.dir/flags.make

output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o: output/alive_supervision/CMakeFiles/AliveSupervision.dir/flags.make
output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o: common/alive_supervision/AliveSupervision.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/alive_supervision && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o -c /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/alive_supervision/AliveSupervision.cpp

output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.i"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/alive_supervision && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/alive_supervision/AliveSupervision.cpp > CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.i

output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.s"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/alive_supervision && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/alive_supervision/AliveSupervision.cpp -o CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.s

output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o.requires:

.PHONY : output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o.requires

output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o.provides: output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o.requires
	$(MAKE) -f output/alive_supervision/CMakeFiles/AliveSupervision.dir/build.make output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o.provides.build
.PHONY : output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o.provides

output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o.provides.build: output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o


# Object files for target AliveSupervision
AliveSupervision_OBJECTS = \
"CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o"

# External object files for target AliveSupervision
AliveSupervision_EXTERNAL_OBJECTS =

output/libs/libAliveSupervision.a: output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o
output/libs/libAliveSupervision.a: output/alive_supervision/CMakeFiles/AliveSupervision.dir/build.make
output/libs/libAliveSupervision.a: output/alive_supervision/CMakeFiles/AliveSupervision.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../libs/libAliveSupervision.a"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/alive_supervision && $(CMAKE_COMMAND) -P CMakeFiles/AliveSupervision.dir/cmake_clean_target.cmake
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/alive_supervision && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AliveSupervision.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
output/alive_supervision/CMakeFiles/AliveSupervision.dir/build: output/libs/libAliveSupervision.a

.PHONY : output/alive_supervision/CMakeFiles/AliveSupervision.dir/build

output/alive_supervision/CMakeFiles/AliveSupervision.dir/requires: output/alive_supervision/CMakeFiles/AliveSupervision.dir/AliveSupervision.cpp.o.requires

.PHONY : output/alive_supervision/CMakeFiles/AliveSupervision.dir/requires

output/alive_supervision/CMakeFiles/AliveSupervision.dir/clean:
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/alive_supervision && $(CMAKE_COMMAND) -P CMakeFiles/AliveSupervision.dir/cmake_clean.cmake
.PHONY : output/alive_supervision/CMakeFiles/AliveSupervision.dir/clean

output/alive_supervision/CMakeFiles/AliveSupervision.dir/depend:
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/alive_supervision /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/alive_supervision /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/alive_supervision/CMakeFiles/AliveSupervision.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : output/alive_supervision/CMakeFiles/AliveSupervision.dir/depend

