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
CMAKE_SOURCE_DIR = /home/bram/Projects/MIC/IRsender

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bram/Projects/MIC/IRsender/build

# Include any dependencies generated for this target.
include CMakeFiles/IRsender.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/IRsender.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IRsender.dir/flags.make

CMakeFiles/IRsender.dir/src/IRsender.cpp.obj: CMakeFiles/IRsender.dir/flags.make
CMakeFiles/IRsender.dir/src/IRsender.cpp.obj: ../src/IRsender.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bram/Projects/MIC/IRsender/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/IRsender.dir/src/IRsender.cpp.obj"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IRsender.dir/src/IRsender.cpp.obj -c /home/bram/Projects/MIC/IRsender/src/IRsender.cpp

CMakeFiles/IRsender.dir/src/IRsender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IRsender.dir/src/IRsender.cpp.i"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bram/Projects/MIC/IRsender/src/IRsender.cpp > CMakeFiles/IRsender.dir/src/IRsender.cpp.i

CMakeFiles/IRsender.dir/src/IRsender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IRsender.dir/src/IRsender.cpp.s"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bram/Projects/MIC/IRsender/src/IRsender.cpp -o CMakeFiles/IRsender.dir/src/IRsender.cpp.s

# Object files for target IRsender
IRsender_OBJECTS = \
"CMakeFiles/IRsender.dir/src/IRsender.cpp.obj"

# External object files for target IRsender
IRsender_EXTERNAL_OBJECTS =

IRsender.elf: CMakeFiles/IRsender.dir/src/IRsender.cpp.obj
IRsender.elf: CMakeFiles/IRsender.dir/build.make
IRsender.elf: CMakeFiles/IRsender.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bram/Projects/MIC/IRsender/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable IRsender.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IRsender.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IRsender.dir/build: IRsender.elf

.PHONY : CMakeFiles/IRsender.dir/build

CMakeFiles/IRsender.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IRsender.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IRsender.dir/clean

CMakeFiles/IRsender.dir/depend:
	cd /home/bram/Projects/MIC/IRsender/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bram/Projects/MIC/IRsender /home/bram/Projects/MIC/IRsender /home/bram/Projects/MIC/IRsender/build /home/bram/Projects/MIC/IRsender/build /home/bram/Projects/MIC/IRsender/build/CMakeFiles/IRsender.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IRsender.dir/depend

