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
CMAKE_COMMAND = /snap/clion/126/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/126/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/orpaz/orpaz-houta/projects/src/storage

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orpaz/orpaz-houta/projects/src/storage/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/heap_storage.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/heap_storage.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/heap_storage.dir/flags.make

CMakeFiles/heap_storage.dir/heap_storage.cpp.o: CMakeFiles/heap_storage.dir/flags.make
CMakeFiles/heap_storage.dir/heap_storage.cpp.o: ../heap_storage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orpaz/orpaz-houta/projects/src/storage/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/heap_storage.dir/heap_storage.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/heap_storage.dir/heap_storage.cpp.o -c /home/orpaz/orpaz-houta/projects/src/storage/heap_storage.cpp

CMakeFiles/heap_storage.dir/heap_storage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/heap_storage.dir/heap_storage.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orpaz/orpaz-houta/projects/src/storage/heap_storage.cpp > CMakeFiles/heap_storage.dir/heap_storage.cpp.i

CMakeFiles/heap_storage.dir/heap_storage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/heap_storage.dir/heap_storage.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orpaz/orpaz-houta/projects/src/storage/heap_storage.cpp -o CMakeFiles/heap_storage.dir/heap_storage.cpp.s

# Object files for target heap_storage
heap_storage_OBJECTS = \
"CMakeFiles/heap_storage.dir/heap_storage.cpp.o"

# External object files for target heap_storage
heap_storage_EXTERNAL_OBJECTS =

heap_storage: CMakeFiles/heap_storage.dir/heap_storage.cpp.o
heap_storage: CMakeFiles/heap_storage.dir/build.make
heap_storage: CMakeFiles/heap_storage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orpaz/orpaz-houta/projects/src/storage/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable heap_storage"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/heap_storage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/heap_storage.dir/build: heap_storage

.PHONY : CMakeFiles/heap_storage.dir/build

CMakeFiles/heap_storage.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/heap_storage.dir/cmake_clean.cmake
.PHONY : CMakeFiles/heap_storage.dir/clean

CMakeFiles/heap_storage.dir/depend:
	cd /home/orpaz/orpaz-houta/projects/src/storage/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orpaz/orpaz-houta/projects/src/storage /home/orpaz/orpaz-houta/projects/src/storage /home/orpaz/orpaz-houta/projects/src/storage/cmake-build-debug /home/orpaz/orpaz-houta/projects/src/storage/cmake-build-debug /home/orpaz/orpaz-houta/projects/src/storage/cmake-build-debug/CMakeFiles/heap_storage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/heap_storage.dir/depend

