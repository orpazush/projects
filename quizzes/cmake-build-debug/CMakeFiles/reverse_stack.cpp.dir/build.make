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
CMAKE_COMMAND = /snap/clion/137/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/137/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/orpaz/orpaz-houta/quizzes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orpaz/orpaz-houta/quizzes/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/reverse_stack.cpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/reverse_stack.cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/reverse_stack.cpp.dir/flags.make

CMakeFiles/reverse_stack.cpp.dir/reverse_stack.cpp.o: CMakeFiles/reverse_stack.cpp.dir/flags.make
CMakeFiles/reverse_stack.cpp.dir/reverse_stack.cpp.o: ../reverse_stack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orpaz/orpaz-houta/quizzes/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/reverse_stack.cpp.dir/reverse_stack.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/reverse_stack.cpp.dir/reverse_stack.cpp.o -c /home/orpaz/orpaz-houta/quizzes/reverse_stack.cpp

CMakeFiles/reverse_stack.cpp.dir/reverse_stack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reverse_stack.cpp.dir/reverse_stack.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orpaz/orpaz-houta/quizzes/reverse_stack.cpp > CMakeFiles/reverse_stack.cpp.dir/reverse_stack.cpp.i

CMakeFiles/reverse_stack.cpp.dir/reverse_stack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reverse_stack.cpp.dir/reverse_stack.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orpaz/orpaz-houta/quizzes/reverse_stack.cpp -o CMakeFiles/reverse_stack.cpp.dir/reverse_stack.cpp.s

# Object files for target reverse_stack.cpp
reverse_stack_cpp_OBJECTS = \
"CMakeFiles/reverse_stack.cpp.dir/reverse_stack.cpp.o"

# External object files for target reverse_stack.cpp
reverse_stack_cpp_EXTERNAL_OBJECTS =

reverse_stack.cpp: CMakeFiles/reverse_stack.cpp.dir/reverse_stack.cpp.o
reverse_stack.cpp: CMakeFiles/reverse_stack.cpp.dir/build.make
reverse_stack.cpp: CMakeFiles/reverse_stack.cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orpaz/orpaz-houta/quizzes/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable reverse_stack.cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reverse_stack.cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/reverse_stack.cpp.dir/build: reverse_stack.cpp

.PHONY : CMakeFiles/reverse_stack.cpp.dir/build

CMakeFiles/reverse_stack.cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/reverse_stack.cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/reverse_stack.cpp.dir/clean

CMakeFiles/reverse_stack.cpp.dir/depend:
	cd /home/orpaz/orpaz-houta/quizzes/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orpaz/orpaz-houta/quizzes /home/orpaz/orpaz-houta/quizzes /home/orpaz/orpaz-houta/quizzes/cmake-build-debug /home/orpaz/orpaz-houta/quizzes/cmake-build-debug /home/orpaz/orpaz-houta/quizzes/cmake-build-debug/CMakeFiles/reverse_stack.cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/reverse_stack.cpp.dir/depend

