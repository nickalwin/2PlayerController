# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/esadev/projects/MIC/Rot13

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/esadev/projects/MIC/Rot13/build

# Utility rule file for strip.

# Include the progress variables for this target.
include CMakeFiles/strip.dir/progress.make

CMakeFiles/strip: Rot13.elf
	avr-strip Rot13.elf

strip: CMakeFiles/strip
strip: CMakeFiles/strip.dir/build.make

.PHONY : strip

# Rule to build all files generated by this target.
CMakeFiles/strip.dir/build: strip

.PHONY : CMakeFiles/strip.dir/build

CMakeFiles/strip.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/strip.dir/cmake_clean.cmake
.PHONY : CMakeFiles/strip.dir/clean

CMakeFiles/strip.dir/depend:
	cd /home/esadev/projects/MIC/Rot13/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/esadev/projects/MIC/Rot13 /home/esadev/projects/MIC/Rot13 /home/esadev/projects/MIC/Rot13/build /home/esadev/projects/MIC/Rot13/build /home/esadev/projects/MIC/Rot13/build/CMakeFiles/strip.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/strip.dir/depend

