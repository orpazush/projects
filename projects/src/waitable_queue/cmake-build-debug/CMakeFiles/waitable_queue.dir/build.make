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
CMAKE_SOURCE_DIR = /home/orpaz/orpaz-houta/projects/src/waitable_queue

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orpaz/orpaz-houta/projects/src/waitable_queue/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/waitable_queue.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/waitable_queue.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/waitable_queue.dir/flags.make

CMakeFiles/waitable_queue.dir/proj_utils.cpp.o: CMakeFiles/waitable_queue.dir/flags.make
CMakeFiles/waitable_queue.dir/proj_utils.cpp.o: ../proj_utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orpaz/orpaz-houta/projects/src/waitable_queue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/waitable_queue.dir/proj_utils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/waitable_queue.dir/proj_utils.cpp.o -c /home/orpaz/orpaz-houta/projects/src/waitable_queue/proj_utils.cpp

CMakeFiles/waitable_queue.dir/proj_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/waitable_queue.dir/proj_utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orpaz/orpaz-houta/projects/src/waitable_queue/proj_utils.cpp > CMakeFiles/waitable_queue.dir/proj_utils.cpp.i

CMakeFiles/waitable_queue.dir/proj_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/waitable_queue.dir/proj_utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orpaz/orpaz-houta/projects/src/waitable_queue/proj_utils.cpp -o CMakeFiles/waitable_queue.dir/proj_utils.cpp.s

CMakeFiles/waitable_queue.dir/waitable_queue_test.cpp.o: CMakeFiles/waitable_queue.dir/flags.make
CMakeFiles/waitable_queue.dir/waitable_queue_test.cpp.o: ../waitable_queue_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orpaz/orpaz-houta/projects/src/waitable_queue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/waitable_queue.dir/waitable_queue_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/waitable_queue.dir/waitable_queue_test.cpp.o -c /home/orpaz/orpaz-houta/projects/src/waitable_queue/waitable_queue_test.cpp

CMakeFiles/waitable_queue.dir/waitable_queue_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/waitable_queue.dir/waitable_queue_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orpaz/orpaz-houta/projects/src/waitable_queue/waitable_queue_test.cpp > CMakeFiles/waitable_queue.dir/waitable_queue_test.cpp.i

CMakeFiles/waitable_queue.dir/waitable_queue_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/waitable_queue.dir/waitable_queue_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orpaz/orpaz-houta/projects/src/waitable_queue/waitable_queue_test.cpp -o CMakeFiles/waitable_queue.dir/waitable_queue_test.cpp.s

# Object files for target waitable_queue
waitable_queue_OBJECTS = \
"CMakeFiles/waitable_queue.dir/proj_utils.cpp.o" \
"CMakeFiles/waitable_queue.dir/waitable_queue_test.cpp.o"

# External object files for target waitable_queue
waitable_queue_EXTERNAL_OBJECTS =

waitable_queue: CMakeFiles/waitable_queue.dir/proj_utils.cpp.o
waitable_queue: CMakeFiles/waitable_queue.dir/waitable_queue_test.cpp.o
waitable_queue: CMakeFiles/waitable_queue.dir/build.make
waitable_queue: CMakeFiles/waitable_queue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orpaz/orpaz-houta/projects/src/waitable_queue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable waitable_queue"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/waitable_queue.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/waitable_queue.dir/build: waitable_queue

.PHONY : CMakeFiles/waitable_queue.dir/build

CMakeFiles/waitable_queue.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/waitable_queue.dir/cmake_clean.cmake
.PHONY : CMakeFiles/waitable_queue.dir/clean

CMakeFiles/waitable_queue.dir/depend:
	cd /home/orpaz/orpaz-houta/projects/src/waitable_queue/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orpaz/orpaz-houta/projects/src/waitable_queue /home/orpaz/orpaz-houta/projects/src/waitable_queue /home/orpaz/orpaz-houta/projects/src/waitable_queue/cmake-build-debug /home/orpaz/orpaz-houta/projects/src/waitable_queue/cmake-build-debug /home/orpaz/orpaz-houta/projects/src/waitable_queue/cmake-build-debug/CMakeFiles/waitable_queue.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/waitable_queue.dir/depend
