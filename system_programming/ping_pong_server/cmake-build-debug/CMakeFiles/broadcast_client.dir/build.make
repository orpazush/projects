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
CMAKE_SOURCE_DIR = /home/orpaz/orpaz-houta/system_programming/ping_pong_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orpaz/orpaz-houta/system_programming/ping_pong_server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/broadcast_client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/broadcast_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/broadcast_client.dir/flags.make

CMakeFiles/broadcast_client.dir/broadcast_client.cpp.o: CMakeFiles/broadcast_client.dir/flags.make
CMakeFiles/broadcast_client.dir/broadcast_client.cpp.o: ../broadcast_client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orpaz/orpaz-houta/system_programming/ping_pong_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/broadcast_client.dir/broadcast_client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/broadcast_client.dir/broadcast_client.cpp.o -c /home/orpaz/orpaz-houta/system_programming/ping_pong_server/broadcast_client.cpp

CMakeFiles/broadcast_client.dir/broadcast_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/broadcast_client.dir/broadcast_client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orpaz/orpaz-houta/system_programming/ping_pong_server/broadcast_client.cpp > CMakeFiles/broadcast_client.dir/broadcast_client.cpp.i

CMakeFiles/broadcast_client.dir/broadcast_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/broadcast_client.dir/broadcast_client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orpaz/orpaz-houta/system_programming/ping_pong_server/broadcast_client.cpp -o CMakeFiles/broadcast_client.dir/broadcast_client.cpp.s

# Object files for target broadcast_client
broadcast_client_OBJECTS = \
"CMakeFiles/broadcast_client.dir/broadcast_client.cpp.o"

# External object files for target broadcast_client
broadcast_client_EXTERNAL_OBJECTS =

broadcast_client: CMakeFiles/broadcast_client.dir/broadcast_client.cpp.o
broadcast_client: CMakeFiles/broadcast_client.dir/build.make
broadcast_client: libutils.so
broadcast_client: CMakeFiles/broadcast_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orpaz/orpaz-houta/system_programming/ping_pong_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable broadcast_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/broadcast_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/broadcast_client.dir/build: broadcast_client

.PHONY : CMakeFiles/broadcast_client.dir/build

CMakeFiles/broadcast_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/broadcast_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/broadcast_client.dir/clean

CMakeFiles/broadcast_client.dir/depend:
	cd /home/orpaz/orpaz-houta/system_programming/ping_pong_server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orpaz/orpaz-houta/system_programming/ping_pong_server /home/orpaz/orpaz-houta/system_programming/ping_pong_server /home/orpaz/orpaz-houta/system_programming/ping_pong_server/cmake-build-debug /home/orpaz/orpaz-houta/system_programming/ping_pong_server/cmake-build-debug /home/orpaz/orpaz-houta/system_programming/ping_pong_server/cmake-build-debug/CMakeFiles/broadcast_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/broadcast_client.dir/depend
