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
CMAKE_SOURCE_DIR = /home/esadev/projects/MIC/ILI9341

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/esadev/projects/MIC/ILI9341/build

# Include any dependencies generated for this target.
include CMakeFiles/ILI9341.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ILI9341.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ILI9341.dir/flags.make

CMakeFiles/ILI9341.dir/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp.obj: CMakeFiles/ILI9341.dir/flags.make
CMakeFiles/ILI9341.dir/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp.obj: ../src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/esadev/projects/MIC/ILI9341/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ILI9341.dir/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp.obj"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ILI9341.dir/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp.obj -c /home/esadev/projects/MIC/ILI9341/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp

CMakeFiles/ILI9341.dir/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ILI9341.dir/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp.i"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/esadev/projects/MIC/ILI9341/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp > CMakeFiles/ILI9341.dir/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp.i

CMakeFiles/ILI9341.dir/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ILI9341.dir/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp.s"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/esadev/projects/MIC/ILI9341/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp -o CMakeFiles/ILI9341.dir/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp.s

# Object files for target ILI9341
ILI9341_OBJECTS = \
"CMakeFiles/ILI9341.dir/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp.obj"

# External object files for target ILI9341
ILI9341_EXTERNAL_OBJECTS =

libILI9341.a: CMakeFiles/ILI9341.dir/src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp.obj
libILI9341.a: CMakeFiles/ILI9341.dir/build.make
libILI9341.a: CMakeFiles/ILI9341.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/esadev/projects/MIC/ILI9341/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libILI9341.a"
	$(CMAKE_COMMAND) -P CMakeFiles/ILI9341.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ILI9341.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ILI9341.dir/build: libILI9341.a

.PHONY : CMakeFiles/ILI9341.dir/build

CMakeFiles/ILI9341.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ILI9341.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ILI9341.dir/clean

CMakeFiles/ILI9341.dir/depend:
	cd /home/esadev/projects/MIC/ILI9341/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/esadev/projects/MIC/ILI9341 /home/esadev/projects/MIC/ILI9341 /home/esadev/projects/MIC/ILI9341/build /home/esadev/projects/MIC/ILI9341/build /home/esadev/projects/MIC/ILI9341/build/CMakeFiles/ILI9341.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ILI9341.dir/depend

