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
CMAKE_COMMAND = /snap/clion/123/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/123/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/orpaz/orpaz-houta/cpp_fs/src/ood

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orpaz/orpaz-houta/cpp_fs/src/ood/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ood.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ood.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ood.dir/flags.make

CMakeFiles/ood.dir/ood.cpp.o: CMakeFiles/ood.dir/flags.make
CMakeFiles/ood.dir/ood.cpp.o: ../ood.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orpaz/orpaz-houta/cpp_fs/src/ood/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ood.dir/ood.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ood.dir/ood.cpp.o -c /home/orpaz/orpaz-houta/cpp_fs/src/ood/ood.cpp

CMakeFiles/ood.dir/ood.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ood.dir/ood.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orpaz/orpaz-houta/cpp_fs/src/ood/ood.cpp > CMakeFiles/ood.dir/ood.cpp.i

CMakeFiles/ood.dir/ood.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ood.dir/ood.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orpaz/orpaz-houta/cpp_fs/src/ood/ood.cpp -o CMakeFiles/ood.dir/ood.cpp.s

CMakeFiles/ood.dir/ood_test.cpp.o: CMakeFiles/ood.dir/flags.make
CMakeFiles/ood.dir/ood_test.cpp.o: ../ood_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orpaz/orpaz-houta/cpp_fs/src/ood/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ood.dir/ood_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ood.dir/ood_test.cpp.o -c /home/orpaz/orpaz-houta/cpp_fs/src/ood/ood_test.cpp

CMakeFiles/ood.dir/ood_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ood.dir/ood_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orpaz/orpaz-houta/cpp_fs/src/ood/ood_test.cpp > CMakeFiles/ood.dir/ood_test.cpp.i

CMakeFiles/ood.dir/ood_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ood.dir/ood_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orpaz/orpaz-houta/cpp_fs/src/ood/ood_test.cpp -o CMakeFiles/ood.dir/ood_test.cpp.s

# Object files for target ood
ood_OBJECTS = \
"CMakeFiles/ood.dir/ood.cpp.o" \
"CMakeFiles/ood.dir/ood_test.cpp.o"

# External object files for target ood
ood_EXTERNAL_OBJECTS =

ood: CMakeFiles/ood.dir/ood.cpp.o
ood: CMakeFiles/ood.dir/ood_test.cpp.o
ood: CMakeFiles/ood.dir/build.make
ood: CMakeFiles/ood.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orpaz/orpaz-houta/cpp_fs/src/ood/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ood"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ood.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ood.dir/build: ood

.PHONY : CMakeFiles/ood.dir/build

CMakeFiles/ood.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ood.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ood.dir/clean

CMakeFiles/ood.dir/depend:
	cd /home/orpaz/orpaz-houta/cpp_fs/src/ood/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orpaz/orpaz-houta/cpp_fs/src/ood /home/orpaz/orpaz-houta/cpp_fs/src/ood /home/orpaz/orpaz-houta/cpp_fs/src/ood/cmake-build-debug /home/orpaz/orpaz-houta/cpp_fs/src/ood/cmake-build-debug /home/orpaz/orpaz-houta/cpp_fs/src/ood/cmake-build-debug/CMakeFiles/ood.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ood.dir/depend
