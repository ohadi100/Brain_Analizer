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
include output/utils/typeCasting/CMakeFiles/TypeCasting.dir/depend.make

# Include the progress variables for this target.
include output/utils/typeCasting/CMakeFiles/TypeCasting.dir/progress.make

# Include the compile flags for this target's objects.
include output/utils/typeCasting/CMakeFiles/TypeCasting.dir/flags.make

output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o: output/utils/typeCasting/CMakeFiles/TypeCasting.dir/flags.make
output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o: common/utils/typeCasting/TypeCasting.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/typeCasting && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o -c /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/typeCasting/TypeCasting.cpp

output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TypeCasting.dir/TypeCasting.cpp.i"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/typeCasting && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/typeCasting/TypeCasting.cpp > CMakeFiles/TypeCasting.dir/TypeCasting.cpp.i

output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TypeCasting.dir/TypeCasting.cpp.s"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/typeCasting && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/typeCasting/TypeCasting.cpp -o CMakeFiles/TypeCasting.dir/TypeCasting.cpp.s

output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o.requires:

.PHONY : output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o.requires

output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o.provides: output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o.requires
	$(MAKE) -f output/utils/typeCasting/CMakeFiles/TypeCasting.dir/build.make output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o.provides.build
.PHONY : output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o.provides

output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o.provides.build: output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o


# Object files for target TypeCasting
TypeCasting_OBJECTS = \
"CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o"

# External object files for target TypeCasting
TypeCasting_EXTERNAL_OBJECTS =

output/libs/libTypeCasting.a: output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o
output/libs/libTypeCasting.a: output/utils/typeCasting/CMakeFiles/TypeCasting.dir/build.make
output/libs/libTypeCasting.a: output/utils/typeCasting/CMakeFiles/TypeCasting.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../libs/libTypeCasting.a"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/typeCasting && $(CMAKE_COMMAND) -P CMakeFiles/TypeCasting.dir/cmake_clean_target.cmake
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/typeCasting && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TypeCasting.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
output/utils/typeCasting/CMakeFiles/TypeCasting.dir/build: output/libs/libTypeCasting.a

.PHONY : output/utils/typeCasting/CMakeFiles/TypeCasting.dir/build

output/utils/typeCasting/CMakeFiles/TypeCasting.dir/requires: output/utils/typeCasting/CMakeFiles/TypeCasting.dir/TypeCasting.cpp.o.requires

.PHONY : output/utils/typeCasting/CMakeFiles/TypeCasting.dir/requires

output/utils/typeCasting/CMakeFiles/TypeCasting.dir/clean:
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/typeCasting && $(CMAKE_COMMAND) -P CMakeFiles/TypeCasting.dir/cmake_clean.cmake
.PHONY : output/utils/typeCasting/CMakeFiles/TypeCasting.dir/clean

output/utils/typeCasting/CMakeFiles/TypeCasting.dir/depend:
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/typeCasting /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/typeCasting /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/utils/typeCasting/CMakeFiles/TypeCasting.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : output/utils/typeCasting/CMakeFiles/TypeCasting.dir/depend

