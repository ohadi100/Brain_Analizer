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
include output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/depend.make

# Include the progress variables for this target.
include output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/progress.make

# Include the compile flags for this target's objects.
include output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/flags.make

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o: output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/flags.make
output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o: brain/communicator/CanCommunicator/CanCommunicator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o -c /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/communicator/CanCommunicator/CanCommunicator.cpp

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.i"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/communicator/CanCommunicator/CanCommunicator.cpp > CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.i

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.s"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/communicator/CanCommunicator/CanCommunicator.cpp -o CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.s

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o.requires:

.PHONY : output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o.requires

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o.provides: output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o.requires
	$(MAKE) -f output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/build.make output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o.provides.build
.PHONY : output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o.provides

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o.provides.build: output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o


# Object files for target CanCommunicator
CanCommunicator_OBJECTS = \
"CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o"

# External object files for target CanCommunicator
CanCommunicator_EXTERNAL_OBJECTS =

output/libs/libCanCommunicator.a: output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o
output/libs/libCanCommunicator.a: output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/build.make
output/libs/libCanCommunicator.a: output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../../../../../../../libs/libCanCommunicator.a"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator && $(CMAKE_COMMAND) -P CMakeFiles/CanCommunicator.dir/cmake_clean_target.cmake
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CanCommunicator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/build: output/libs/libCanCommunicator.a

.PHONY : output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/build

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/requires: output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/CanCommunicator.cpp.o.requires

.PHONY : output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/requires

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/clean:
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator && $(CMAKE_COMMAND) -P CMakeFiles/CanCommunicator.dir/cmake_clean.cmake
.PHONY : output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/clean

output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/depend:
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/communicator/CanCommunicator /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : output/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/canCommunicator/CMakeFiles/CanCommunicator.dir/depend

