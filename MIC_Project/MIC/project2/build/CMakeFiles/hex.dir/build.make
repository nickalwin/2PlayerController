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
CMAKE_SOURCE_DIR = /home/esadev/projects/MIC/project2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/esadev/projects/MIC/project2/build

# Utility rule file for hex.

# Include the progress variables for this target.
include CMakeFiles/hex.dir/progress.make

CMakeFiles/hex:
	avr-objcopy -R .eeprom -O ihex project2.elf project2.hex

hex: CMakeFiles/hex
hex: CMakeFiles/hex.dir/build.make

.PHONY : hex

# Rule to build all files generated by this target.
CMakeFiles/hex.dir/build: hex

.PHONY : CMakeFiles/hex.dir/build

CMakeFiles/hex.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hex.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hex.dir/clean

CMakeFiles/hex.dir/depend:
	cd /home/esadev/projects/MIC/project2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/esadev/projects/MIC/project2 /home/esadev/projects/MIC/project2 /home/esadev/projects/MIC/project2/build /home/esadev/projects/MIC/project2/build /home/esadev/projects/MIC/project2/build/CMakeFiles/hex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hex.dir/depend

