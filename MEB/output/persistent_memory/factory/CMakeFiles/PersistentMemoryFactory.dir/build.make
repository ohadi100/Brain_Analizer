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
include output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/depend.make

# Include the progress variables for this target.
include output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/progress.make

# Include the compile flags for this target's objects.
include output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/flags.make

output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o: output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/flags.make
output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o: common/persistent_memory/factory/PersistentMemoryFactory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/persistent_memory/factory && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o -c /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/persistent_memory/factory/PersistentMemoryFactory.cpp

output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.i"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/persistent_memory/factory && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/persistent_memory/factory/PersistentMemoryFactory.cpp > CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.i

output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.s"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/persistent_memory/factory && /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/persistent_memory/factory/PersistentMemoryFactory.cpp -o CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.s

output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o.requires:

.PHONY : output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o.requires

output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o.provides: output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o.requires
	$(MAKE) -f output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/build.make output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o.provides.build
.PHONY : output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o.provides

output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o.provides.build: output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o


# Object files for target PersistentMemoryFactory
PersistentMemoryFactory_OBJECTS = \
"CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o"

# External object files for target PersistentMemoryFactory
PersistentMemoryFactory_EXTERNAL_OBJECTS =

output/libs/libPersistentMemoryFactory.a: output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o
output/libs/libPersistentMemoryFactory.a: output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/build.make
output/libs/libPersistentMemoryFactory.a: output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../libs/libPersistentMemoryFactory.a"
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/persistent_memory/factory && $(CMAKE_COMMAND) -P CMakeFiles/PersistentMemoryFactory.dir/cmake_clean_target.cmake
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/persistent_memory/factory && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PersistentMemoryFactory.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/build: output/libs/libPersistentMemoryFactory.a

.PHONY : output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/build

output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/requires: output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/PersistentMemoryFactory.cpp.o.requires

.PHONY : output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/requires

output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/clean:
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/persistent_memory/factory && $(CMAKE_COMMAND) -P CMakeFiles/PersistentMemoryFactory.dir/cmake_clean.cmake
.PHONY : output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/clean

output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/depend:
	cd /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/persistent_memory/factory /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/persistent_memory/factory /home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : output/persistent_memory/factory/CMakeFiles/PersistentMemoryFactory.dir/depend

