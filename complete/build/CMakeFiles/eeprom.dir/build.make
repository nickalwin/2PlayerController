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
CMAKE_SOURCE_DIR = /home/esadev/Documents/GitHub/2PlayerController/complete

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/esadev/Documents/GitHub/2PlayerController/complete/build

# Utility rule file for eeprom.

# Include the progress variables for this target.
include CMakeFiles/eeprom.dir/progress.make

CMakeFiles/eeprom:
	avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma.eeprom=0 -O ihex IR_Reciever.elf IR_Reciever.eep

eeprom: CMakeFiles/eeprom
eeprom: CMakeFiles/eeprom.dir/build.make

.PHONY : eeprom

# Rule to build all files generated by this target.
CMakeFiles/eeprom.dir/build: eeprom

.PHONY : CMakeFiles/eeprom.dir/build

CMakeFiles/eeprom.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/eeprom.dir/cmake_clean.cmake
.PHONY : CMakeFiles/eeprom.dir/clean

CMakeFiles/eeprom.dir/depend:
	cd /home/esadev/Documents/GitHub/2PlayerController/complete/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/esadev/Documents/GitHub/2PlayerController/complete /home/esadev/Documents/GitHub/2PlayerController/complete /home/esadev/Documents/GitHub/2PlayerController/complete/build /home/esadev/Documents/GitHub/2PlayerController/complete/build /home/esadev/Documents/GitHub/2PlayerController/complete/build/CMakeFiles/eeprom.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/eeprom.dir/depend

