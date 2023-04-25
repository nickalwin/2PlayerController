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
CMAKE_SOURCE_DIR = /home/esadev/projects/MIC/graphicstest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/esadev/projects/MIC/graphicstest/build

# Utility rule file for fuses.

# Include the progress variables for this target.
include CMakeFiles/fuses.dir/progress.make

CMakeFiles/fuses:
	/usr/bin/avrdude -P /dev/ttyACM0 -c arduino -p atmega328p -U lfuse:w::m -U hfuse:w::m -U efuse:w::m -U lock:w::m

fuses: CMakeFiles/fuses
fuses: CMakeFiles/fuses.dir/build.make

.PHONY : fuses

# Rule to build all files generated by this target.
CMakeFiles/fuses.dir/build: fuses

.PHONY : CMakeFiles/fuses.dir/build

CMakeFiles/fuses.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fuses.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fuses.dir/clean

CMakeFiles/fuses.dir/depend:
	cd /home/esadev/projects/MIC/graphicstest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/esadev/projects/MIC/graphicstest /home/esadev/projects/MIC/graphicstest /home/esadev/projects/MIC/graphicstest/build /home/esadev/projects/MIC/graphicstest/build /home/esadev/projects/MIC/graphicstest/build/CMakeFiles/fuses.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fuses.dir/depend

