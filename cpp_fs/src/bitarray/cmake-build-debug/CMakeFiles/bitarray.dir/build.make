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
CMAKE_COMMAND = /snap/clion/124/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/124/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/orpaz/orpaz-houta/cpp_fs/src/bitarray

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orpaz/orpaz-houta/cpp_fs/src/bitarray/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bitarray.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bitarray.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bitarray.dir/flags.make

CMakeFiles/bitarray.dir/bitarray.cpp.o: CMakeFiles/bitarray.dir/flags.make
CMakeFiles/bitarray.dir/bitarray.cpp.o: ../bitarray.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orpaz/orpaz-houta/cpp_fs/src/bitarray/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bitarray.dir/bitarray.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bitarray.dir/bitarray.cpp.o -c /home/orpaz/orpaz-houta/cpp_fs/src/bitarray/bitarray.cpp

CMakeFiles/bitarray.dir/bitarray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bitarray.dir/bitarray.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orpaz/orpaz-houta/cpp_fs/src/bitarray/bitarray.cpp > CMakeFiles/bitarray.dir/bitarray.cpp.i

CMakeFiles/bitarray.dir/bitarray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bitarray.dir/bitarray.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orpaz/orpaz-houta/cpp_fs/src/bitarray/bitarray.cpp -o CMakeFiles/bitarray.dir/bitarray.cpp.s

# Object files for target bitarray
bitarray_OBJECTS = \
"CMakeFiles/bitarray.dir/bitarray.cpp.o"

# External object files for target bitarray
bitarray_EXTERNAL_OBJECTS =

bitarray: CMakeFiles/bitarray.dir/bitarray.cpp.o
bitarray: CMakeFiles/bitarray.dir/build.make
bitarray: CMakeFiles/bitarray.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orpaz/orpaz-houta/cpp_fs/src/bitarray/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bitarray"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bitarray.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bitarray.dir/build: bitarray

.PHONY : CMakeFiles/bitarray.dir/build

CMakeFiles/bitarray.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bitarray.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bitarray.dir/clean

CMakeFiles/bitarray.dir/depend:
	cd /home/orpaz/orpaz-houta/cpp_fs/src/bitarray/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orpaz/orpaz-houta/cpp_fs/src/bitarray /home/orpaz/orpaz-houta/cpp_fs/src/bitarray /home/orpaz/orpaz-houta/cpp_fs/src/bitarray/cmake-build-debug /home/orpaz/orpaz-houta/cpp_fs/src/bitarray/cmake-build-debug /home/orpaz/orpaz-houta/cpp_fs/src/bitarray/cmake-build-debug/CMakeFiles/bitarray.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bitarray.dir/depend

