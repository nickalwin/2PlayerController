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
CMAKE_SOURCE_DIR = /home/esadev/projects/Project/Nun_LCD

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/esadev/projects/Project/Nun_LCD/build

# Include any dependencies generated for this target.
include CMakeFiles/Nun_LCD.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Nun_LCD.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Nun_LCD.dir/flags.make

CMakeFiles/Nun_LCD.dir/src/main.cpp.obj: CMakeFiles/Nun_LCD.dir/flags.make
CMakeFiles/Nun_LCD.dir/src/main.cpp.obj: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/esadev/projects/Project/Nun_LCD/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Nun_LCD.dir/src/main.cpp.obj"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Nun_LCD.dir/src/main.cpp.obj -c /home/esadev/projects/Project/Nun_LCD/src/main.cpp

CMakeFiles/Nun_LCD.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Nun_LCD.dir/src/main.cpp.i"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/esadev/projects/Project/Nun_LCD/src/main.cpp > CMakeFiles/Nun_LCD.dir/src/main.cpp.i

CMakeFiles/Nun_LCD.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Nun_LCD.dir/src/main.cpp.s"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/esadev/projects/Project/Nun_LCD/src/main.cpp -o CMakeFiles/Nun_LCD.dir/src/main.cpp.s

# Object files for target Nun_LCD
Nun_LCD_OBJECTS = \
"CMakeFiles/Nun_LCD.dir/src/main.cpp.obj"

# External object files for target Nun_LCD
Nun_LCD_EXTERNAL_OBJECTS =

Nun_LCD.elf: CMakeFiles/Nun_LCD.dir/src/main.cpp.obj
Nun_LCD.elf: CMakeFiles/Nun_LCD.dir/build.make
Nun_LCD.elf: CMakeFiles/Nun_LCD.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/esadev/projects/Project/Nun_LCD/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Nun_LCD.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Nun_LCD.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Nun_LCD.dir/build: Nun_LCD.elf

.PHONY : CMakeFiles/Nun_LCD.dir/build

CMakeFiles/Nun_LCD.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Nun_LCD.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Nun_LCD.dir/clean

CMakeFiles/Nun_LCD.dir/depend:
	cd /home/esadev/projects/Project/Nun_LCD/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/esadev/projects/Project/Nun_LCD /home/esadev/projects/Project/Nun_LCD /home/esadev/projects/Project/Nun_LCD/build /home/esadev/projects/Project/Nun_LCD/build /home/esadev/projects/Project/Nun_LCD/build/CMakeFiles/Nun_LCD.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Nun_LCD.dir/depend
