# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /snap/clion/138/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/138/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/orpaz/orpaz-houta/projects

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orpaz/orpaz-houta/projects/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/master.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/master.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/master.dir/flags.make

CMakeFiles/master.dir/src/master/master_test.cpp.o: CMakeFiles/master.dir/flags.make
CMakeFiles/master.dir/src/master/master_test.cpp.o: ../src/master/master_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orpaz/orpaz-houta/projects/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/master.dir/src/master/master_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/master.dir/src/master/master_test.cpp.o -c /home/orpaz/orpaz-houta/projects/src/master/master_test.cpp

CMakeFiles/master.dir/src/master/master_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/master.dir/src/master/master_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orpaz/orpaz-houta/projects/src/master/master_test.cpp > CMakeFiles/master.dir/src/master/master_test.cpp.i

CMakeFiles/master.dir/src/master/master_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/master.dir/src/master/master_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orpaz/orpaz-houta/projects/src/master/master_test.cpp -o CMakeFiles/master.dir/src/master/master_test.cpp.s

# Object files for target master
master_OBJECTS = \
"CMakeFiles/master.dir/src/master/master_test.cpp.o"

# External object files for target master
master_EXTERNAL_OBJECTS =

master: CMakeFiles/master.dir/src/master/master_test.cpp.o
master: CMakeFiles/master.dir/build.make
master: libprojects.so
master: CMakeFiles/master.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orpaz/orpaz-houta/projects/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable master"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/master.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/master.dir/build: master

.PHONY : CMakeFiles/master.dir/build

CMakeFiles/master.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/master.dir/cmake_clean.cmake
.PHONY : CMakeFiles/master.dir/clean

CMakeFiles/master.dir/depend:
	cd /home/orpaz/orpaz-houta/projects/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orpaz/orpaz-houta/projects /home/orpaz/orpaz-houta/projects /home/orpaz/orpaz-houta/projects/cmake-build-debug /home/orpaz/orpaz-houta/projects/cmake-build-debug /home/orpaz/orpaz-houta/projects/cmake-build-debug/CMakeFiles/master.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/master.dir/depend

