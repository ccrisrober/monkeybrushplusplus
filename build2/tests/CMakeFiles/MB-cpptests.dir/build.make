# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/crodriguez/Desktop/monkeybrushplusplus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/crodriguez/Desktop/monkeybrushplusplus/build2

# Utility rule file for MB-cpptests.

# Include the progress variables for this target.
include tests/CMakeFiles/MB-cpptests.dir/progress.make

tests/CMakeFiles/MB-cpptests:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/crodriguez/Desktop/monkeybrushplusplus/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running MB unit tests"
	/usr/bin/ctest -T test --no-compress-output --output-on-failure -L MB-unit -C Release ${ARGS}

MB-cpptests: tests/CMakeFiles/MB-cpptests
MB-cpptests: tests/CMakeFiles/MB-cpptests.dir/build.make

.PHONY : MB-cpptests

# Rule to build all files generated by this target.
tests/CMakeFiles/MB-cpptests.dir/build: MB-cpptests

.PHONY : tests/CMakeFiles/MB-cpptests.dir/build

tests/CMakeFiles/MB-cpptests.dir/clean:
	cd /home/crodriguez/Desktop/monkeybrushplusplus/build2/tests && $(CMAKE_COMMAND) -P CMakeFiles/MB-cpptests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/MB-cpptests.dir/clean

tests/CMakeFiles/MB-cpptests.dir/depend:
	cd /home/crodriguez/Desktop/monkeybrushplusplus/build2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/crodriguez/Desktop/monkeybrushplusplus /home/crodriguez/Desktop/monkeybrushplusplus/tests /home/crodriguez/Desktop/monkeybrushplusplus/build2 /home/crodriguez/Desktop/monkeybrushplusplus/build2/tests /home/crodriguez/Desktop/monkeybrushplusplus/build2/tests/CMakeFiles/MB-cpptests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/MB-cpptests.dir/depend
