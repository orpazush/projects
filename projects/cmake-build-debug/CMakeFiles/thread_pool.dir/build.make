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
include CMakeFiles/thread_pool.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/thread_pool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/thread_pool.dir/flags.make

CMakeFiles/thread_pool.dir/src/thread_pool/thread_pool_test.cpp.o: CMakeFiles/thread_pool.dir/flags.make
CMakeFiles/thread_pool.dir/src/thread_pool/thread_pool_test.cpp.o: ../src/thread_pool/thread_pool_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orpaz/orpaz-houta/projects/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/thread_pool.dir/src/thread_pool/thread_pool_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/thread_pool.dir/src/thread_pool/thread_pool_test.cpp.o -c /home/orpaz/orpaz-houta/projects/src/thread_pool/thread_pool_test.cpp

CMakeFiles/thread_pool.dir/src/thread_pool/thread_pool_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/thread_pool.dir/src/thread_pool/thread_pool_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orpaz/orpaz-houta/projects/src/thread_pool/thread_pool_test.cpp > CMakeFiles/thread_pool.dir/src/thread_pool/thread_pool_test.cpp.i

CMakeFiles/thread_pool.dir/src/thread_pool/thread_pool_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/thread_pool.dir/src/thread_pool/thread_pool_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orpaz/orpaz-houta/projects/src/thread_pool/thread_pool_test.cpp -o CMakeFiles/thread_pool.dir/src/thread_pool/thread_pool_test.cpp.s

# Object files for target thread_pool
thread_pool_OBJECTS = \
"CMakeFiles/thread_pool.dir/src/thread_pool/thread_pool_test.cpp.o"

# External object files for target thread_pool
thread_pool_EXTERNAL_OBJECTS =

thread_pool: CMakeFiles/thread_pool.dir/src/thread_pool/thread_pool_test.cpp.o
thread_pool: CMakeFiles/thread_pool.dir/build.make
thread_pool: libprojects.so
thread_pool: CMakeFiles/thread_pool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orpaz/orpaz-houta/projects/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable thread_pool"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/thread_pool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/thread_pool.dir/build: thread_pool

.PHONY : CMakeFiles/thread_pool.dir/build

CMakeFiles/thread_pool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/thread_pool.dir/cmake_clean.cmake
.PHONY : CMakeFiles/thread_pool.dir/clean

CMakeFiles/thread_pool.dir/depend:
	cd /home/orpaz/orpaz-houta/projects/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orpaz/orpaz-houta/projects /home/orpaz/orpaz-houta/projects /home/orpaz/orpaz-houta/projects/cmake-build-debug /home/orpaz/orpaz-houta/projects/cmake-build-debug /home/orpaz/orpaz-houta/projects/cmake-build-debug/CMakeFiles/thread_pool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/thread_pool.dir/depend
