# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/tmp.i7tGOf6Z4C

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.i7tGOf6Z4C/cmake-build-release-raspi

# Include any dependencies generated for this target.
include CMakeFiles/bitarray_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bitarray_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bitarray_test.dir/flags.make

CMakeFiles/bitarray_test.dir/bitarray.cpp.o: CMakeFiles/bitarray_test.dir/flags.make
CMakeFiles/bitarray_test.dir/bitarray.cpp.o: ../bitarray.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.i7tGOf6Z4C/cmake-build-release-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bitarray_test.dir/bitarray.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bitarray_test.dir/bitarray.cpp.o -c /tmp/tmp.i7tGOf6Z4C/bitarray.cpp

CMakeFiles/bitarray_test.dir/bitarray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bitarray_test.dir/bitarray.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.i7tGOf6Z4C/bitarray.cpp > CMakeFiles/bitarray_test.dir/bitarray.cpp.i

CMakeFiles/bitarray_test.dir/bitarray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bitarray_test.dir/bitarray.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.i7tGOf6Z4C/bitarray.cpp -o CMakeFiles/bitarray_test.dir/bitarray.cpp.s

CMakeFiles/bitarray_test.dir/bitarray_test.cpp.o: CMakeFiles/bitarray_test.dir/flags.make
CMakeFiles/bitarray_test.dir/bitarray_test.cpp.o: ../bitarray_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.i7tGOf6Z4C/cmake-build-release-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bitarray_test.dir/bitarray_test.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bitarray_test.dir/bitarray_test.cpp.o -c /tmp/tmp.i7tGOf6Z4C/bitarray_test.cpp

CMakeFiles/bitarray_test.dir/bitarray_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bitarray_test.dir/bitarray_test.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.i7tGOf6Z4C/bitarray_test.cpp > CMakeFiles/bitarray_test.dir/bitarray_test.cpp.i

CMakeFiles/bitarray_test.dir/bitarray_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bitarray_test.dir/bitarray_test.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.i7tGOf6Z4C/bitarray_test.cpp -o CMakeFiles/bitarray_test.dir/bitarray_test.cpp.s

# Object files for target bitarray_test
bitarray_test_OBJECTS = \
"CMakeFiles/bitarray_test.dir/bitarray.cpp.o" \
"CMakeFiles/bitarray_test.dir/bitarray_test.cpp.o"

# External object files for target bitarray_test
bitarray_test_EXTERNAL_OBJECTS =

bitarray_test: CMakeFiles/bitarray_test.dir/bitarray.cpp.o
bitarray_test: CMakeFiles/bitarray_test.dir/bitarray_test.cpp.o
bitarray_test: CMakeFiles/bitarray_test.dir/build.make
bitarray_test: CMakeFiles/bitarray_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.i7tGOf6Z4C/cmake-build-release-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bitarray_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bitarray_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bitarray_test.dir/build: bitarray_test

.PHONY : CMakeFiles/bitarray_test.dir/build

CMakeFiles/bitarray_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bitarray_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bitarray_test.dir/clean

CMakeFiles/bitarray_test.dir/depend:
	cd /tmp/tmp.i7tGOf6Z4C/cmake-build-release-raspi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.i7tGOf6Z4C /tmp/tmp.i7tGOf6Z4C /tmp/tmp.i7tGOf6Z4C/cmake-build-release-raspi /tmp/tmp.i7tGOf6Z4C/cmake-build-release-raspi /tmp/tmp.i7tGOf6Z4C/cmake-build-release-raspi/CMakeFiles/bitarray_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bitarray_test.dir/depend
