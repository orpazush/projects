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
CMAKE_SOURCE_DIR = /home/orpaz/orpaz-houta/system_programming/ping_pong_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orpaz/orpaz-houta/system_programming/ping_pong_server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bst.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bst.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bst.dir/flags.make

CMakeFiles/bst.dir/home/orpaz/orpaz-houta/ds/src/bst/bst.c.o: CMakeFiles/bst.dir/flags.make
CMakeFiles/bst.dir/home/orpaz/orpaz-houta/ds/src/bst/bst.c.o: /home/orpaz/orpaz-houta/ds/src/bst/bst.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orpaz/orpaz-houta/system_programming/ping_pong_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/bst.dir/home/orpaz/orpaz-houta/ds/src/bst/bst.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bst.dir/home/orpaz/orpaz-houta/ds/src/bst/bst.c.o   -c /home/orpaz/orpaz-houta/ds/src/bst/bst.c

CMakeFiles/bst.dir/home/orpaz/orpaz-houta/ds/src/bst/bst.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bst.dir/home/orpaz/orpaz-houta/ds/src/bst/bst.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/orpaz/orpaz-houta/ds/src/bst/bst.c > CMakeFiles/bst.dir/home/orpaz/orpaz-houta/ds/src/bst/bst.c.i

CMakeFiles/bst.dir/home/orpaz/orpaz-houta/ds/src/bst/bst.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bst.dir/home/orpaz/orpaz-houta/ds/src/bst/bst.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/orpaz/orpaz-houta/ds/src/bst/bst.c -o CMakeFiles/bst.dir/home/orpaz/orpaz-houta/ds/src/bst/bst.c.s

# Object files for target bst
bst_OBJECTS = \
"CMakeFiles/bst.dir/home/orpaz/orpaz-houta/ds/src/bst/bst.c.o"

# External object files for target bst
bst_EXTERNAL_OBJECTS =

libbst.a: CMakeFiles/bst.dir/home/orpaz/orpaz-houta/ds/src/bst/bst.c.o
libbst.a: CMakeFiles/bst.dir/build.make
libbst.a: CMakeFiles/bst.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orpaz/orpaz-houta/system_programming/ping_pong_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libbst.a"
	$(CMAKE_COMMAND) -P CMakeFiles/bst.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bst.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bst.dir/build: libbst.a

.PHONY : CMakeFiles/bst.dir/build

CMakeFiles/bst.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bst.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bst.dir/clean

CMakeFiles/bst.dir/depend:
	cd /home/orpaz/orpaz-houta/system_programming/ping_pong_server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orpaz/orpaz-houta/system_programming/ping_pong_server /home/orpaz/orpaz-houta/system_programming/ping_pong_server /home/orpaz/orpaz-houta/system_programming/ping_pong_server/cmake-build-debug /home/orpaz/orpaz-houta/system_programming/ping_pong_server/cmake-build-debug /home/orpaz/orpaz-houta/system_programming/ping_pong_server/cmake-build-debug/CMakeFiles/bst.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bst.dir/depend
