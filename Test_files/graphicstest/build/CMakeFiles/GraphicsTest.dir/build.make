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

# Include any dependencies generated for this target.
include CMakeFiles/GraphicsTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GraphicsTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GraphicsTest.dir/flags.make

CMakeFiles/GraphicsTest.dir/src/graphicstest.cpp.obj: CMakeFiles/GraphicsTest.dir/flags.make
CMakeFiles/GraphicsTest.dir/src/graphicstest.cpp.obj: ../src/graphicstest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/esadev/projects/MIC/graphicstest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GraphicsTest.dir/src/graphicstest.cpp.obj"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GraphicsTest.dir/src/graphicstest.cpp.obj -c /home/esadev/projects/MIC/graphicstest/src/graphicstest.cpp

CMakeFiles/GraphicsTest.dir/src/graphicstest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GraphicsTest.dir/src/graphicstest.cpp.i"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/esadev/projects/MIC/graphicstest/src/graphicstest.cpp > CMakeFiles/GraphicsTest.dir/src/graphicstest.cpp.i

CMakeFiles/GraphicsTest.dir/src/graphicstest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GraphicsTest.dir/src/graphicstest.cpp.s"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/esadev/projects/MIC/graphicstest/src/graphicstest.cpp -o CMakeFiles/GraphicsTest.dir/src/graphicstest.cpp.s

# Object files for target GraphicsTest
GraphicsTest_OBJECTS = \
"CMakeFiles/GraphicsTest.dir/src/graphicstest.cpp.obj"

# External object files for target GraphicsTest
GraphicsTest_EXTERNAL_OBJECTS =

GraphicsTest.elf: CMakeFiles/GraphicsTest.dir/src/graphicstest.cpp.obj
GraphicsTest.elf: CMakeFiles/GraphicsTest.dir/build.make
GraphicsTest.elf: CMakeFiles/GraphicsTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/esadev/projects/MIC/graphicstest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable GraphicsTest.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GraphicsTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GraphicsTest.dir/build: GraphicsTest.elf

.PHONY : CMakeFiles/GraphicsTest.dir/build

CMakeFiles/GraphicsTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GraphicsTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GraphicsTest.dir/clean

CMakeFiles/GraphicsTest.dir/depend:
	cd /home/esadev/projects/MIC/graphicstest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/esadev/projects/MIC/graphicstest /home/esadev/projects/MIC/graphicstest /home/esadev/projects/MIC/graphicstest/build /home/esadev/projects/MIC/graphicstest/build /home/esadev/projects/MIC/graphicstest/build/CMakeFiles/GraphicsTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GraphicsTest.dir/depend

