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
CMAKE_SOURCE_DIR = /home/orpaz/orpaz-houta/system_programming/tcp_udp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orpaz/orpaz-houta/system_programming/tcp_udp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/utils.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/utils.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/utils.dir/flags.make

CMakeFiles/utils.dir/tcp_udp_utils.cpp.o: CMakeFiles/utils.dir/flags.make
CMakeFiles/utils.dir/tcp_udp_utils.cpp.o: ../tcp_udp_utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orpaz/orpaz-houta/system_programming/tcp_udp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/utils.dir/tcp_udp_utils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utils.dir/tcp_udp_utils.cpp.o -c /home/orpaz/orpaz-houta/system_programming/tcp_udp/tcp_udp_utils.cpp

CMakeFiles/utils.dir/tcp_udp_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils.dir/tcp_udp_utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orpaz/orpaz-houta/system_programming/tcp_udp/tcp_udp_utils.cpp > CMakeFiles/utils.dir/tcp_udp_utils.cpp.i

CMakeFiles/utils.dir/tcp_udp_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils.dir/tcp_udp_utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orpaz/orpaz-houta/system_programming/tcp_udp/tcp_udp_utils.cpp -o CMakeFiles/utils.dir/tcp_udp_utils.cpp.s

# Object files for target utils
utils_OBJECTS = \
"CMakeFiles/utils.dir/tcp_udp_utils.cpp.o"

# External object files for target utils
utils_EXTERNAL_OBJECTS =

libutils.a: CMakeFiles/utils.dir/tcp_udp_utils.cpp.o
libutils.a: CMakeFiles/utils.dir/build.make
libutils.a: CMakeFiles/utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orpaz/orpaz-houta/system_programming/tcp_udp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libutils.a"
	$(CMAKE_COMMAND) -P CMakeFiles/utils.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/utils.dir/build: libutils.a

.PHONY : CMakeFiles/utils.dir/build

CMakeFiles/utils.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/utils.dir/cmake_clean.cmake
.PHONY : CMakeFiles/utils.dir/clean

CMakeFiles/utils.dir/depend:
	cd /home/orpaz/orpaz-houta/system_programming/tcp_udp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orpaz/orpaz-houta/system_programming/tcp_udp /home/orpaz/orpaz-houta/system_programming/tcp_udp /home/orpaz/orpaz-houta/system_programming/tcp_udp/cmake-build-debug /home/orpaz/orpaz-houta/system_programming/tcp_udp/cmake-build-debug /home/orpaz/orpaz-houta/system_programming/tcp_udp/cmake-build-debug/CMakeFiles/utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/utils.dir/depend
