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
include output/utils/GUID/CMakeFiles/GUID.dir/depend.make

# Include the progress variables for this target.
include output/utils/GUID/CMakeFiles/GUID.dir/progress.make

# Include the compile flags for this target's objects.
include output/utils/GUID/CMakeFiles/GUID.dir/flags.make

output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.o: output/utils/GUID/CMakeFiles/GUID.dir/flags.make
output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.o: common/utils/GUID/GUID.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.o"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/GUID && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GUID.dir/GUID.cpp.o -c /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/GUID/GUID.cpp

output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GUID.dir/GUID.cpp.i"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/GUID && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/GUID/GUID.cpp > CMakeFiles/GUID.dir/GUID.cpp.i

output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GUID.dir/GUID.cpp.s"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/GUID && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/GUID/GUID.cpp -o CMakeFiles/GUID.dir/GUID.cpp.s

output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.o.requires:

.PHONY : output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.o.requires

output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.o.provides: output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.o.requires
	$(MAKE) -f output/utils/GUID/CMakeFiles/GUID.dir/build.make output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.o.provides.build
.PHONY : output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.o.provides

output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.o.provides.build: output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.o


# Object files for target GUID
GUID_OBJECTS = \
"CMakeFiles/GUID.dir/GUID.cpp.o"

# External object files for target GUID
GUID_EXTERNAL_OBJECTS =

output/libs/libGUID.a: output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.o
output/libs/libGUID.a: output/utils/GUID/CMakeFiles/GUID.dir/build.make
output/libs/libGUID.a: output/utils/GUID/CMakeFiles/GUID.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../libs/libGUID.a"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/GUID && $(CMAKE_COMMAND) -P CMakeFiles/GUID.dir/cmake_clean_target.cmake
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/GUID && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GUID.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
output/utils/GUID/CMakeFiles/GUID.dir/build: output/libs/libGUID.a

.PHONY : output/utils/GUID/CMakeFiles/GUID.dir/build

output/utils/GUID/CMakeFiles/GUID.dir/requires: output/utils/GUID/CMakeFiles/GUID.dir/GUID.cpp.o.requires

.PHONY : output/utils/GUID/CMakeFiles/GUID.dir/requires

output/utils/GUID/CMakeFiles/GUID.dir/clean:
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/GUID && $(CMAKE_COMMAND) -P CMakeFiles/GUID.dir/cmake_clean.cmake
.PHONY : output/utils/GUID/CMakeFiles/GUID.dir/clean

output/utils/GUID/CMakeFiles/GUID.dir/depend:
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/GUID /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/GUID /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/GUID/CMakeFiles/GUID.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : output/utils/GUID/CMakeFiles/GUID.dir/depend

