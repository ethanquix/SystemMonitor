# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wyzlic_a/blih/cpp/jason

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wyzlic_a/blih/cpp/jason

# Include any dependencies generated for this target.
include CMakeFiles/FlyModule.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FlyModule.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FlyModule.dir/flags.make

CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o: CMakeFiles/FlyModule.dir/flags.make
CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o: src_sensor/FlyModule.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wyzlic_a/blih/cpp/jason/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o -c /home/wyzlic_a/blih/cpp/jason/src_sensor/FlyModule.cpp

CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wyzlic_a/blih/cpp/jason/src_sensor/FlyModule.cpp > CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.i

CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wyzlic_a/blih/cpp/jason/src_sensor/FlyModule.cpp -o CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.s

CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o.requires:

.PHONY : CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o.requires

CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o.provides: CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o.requires
	$(MAKE) -f CMakeFiles/FlyModule.dir/build.make CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o.provides.build
.PHONY : CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o.provides

CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o.provides.build: CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o


# Object files for target FlyModule
FlyModule_OBJECTS = \
"CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o"

# External object files for target FlyModule
FlyModule_EXTERNAL_OBJECTS =

/home/wyzlic_a/.sensor/libFlyModule.so: CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o
/home/wyzlic_a/.sensor/libFlyModule.so: CMakeFiles/FlyModule.dir/build.make
/home/wyzlic_a/.sensor/libFlyModule.so: CMakeFiles/FlyModule.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wyzlic_a/blih/cpp/jason/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library /home/wyzlic_a/.sensor/libFlyModule.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FlyModule.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FlyModule.dir/build: /home/wyzlic_a/.sensor/libFlyModule.so

.PHONY : CMakeFiles/FlyModule.dir/build

CMakeFiles/FlyModule.dir/requires: CMakeFiles/FlyModule.dir/src_sensor/FlyModule.cpp.o.requires

.PHONY : CMakeFiles/FlyModule.dir/requires

CMakeFiles/FlyModule.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FlyModule.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FlyModule.dir/clean

CMakeFiles/FlyModule.dir/depend:
	cd /home/wyzlic_a/blih/cpp/jason && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wyzlic_a/blih/cpp/jason /home/wyzlic_a/blih/cpp/jason /home/wyzlic_a/blih/cpp/jason /home/wyzlic_a/blih/cpp/jason /home/wyzlic_a/blih/cpp/jason/CMakeFiles/FlyModule.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FlyModule.dir/depend
