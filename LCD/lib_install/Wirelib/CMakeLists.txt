# Just a recent number
cmake_minimum_required(VERSION 3.18)

# Determine the Arduino path, with all Arduino related libraries and generic cmake stuff
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(ARDUINO_PATH $ENV{HOME}/Arduino)
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(ARDUINO_PATH "$ENV{HOMEDRIVE}$ENV{HOMEPATH}/Arduino")
endif()

# the toolchain to use
set(CMAKE_TOOLCHAIN_FILE ${ARDUINO_PATH}/etc/toolchain-avr.cmake)

# sometimes we need the assembler
enable_language(ASM)

# Project name
project("Wire")

# Where to install
set(CMAKE_INSTALL_PREFIX ${ARDUINO_PATH})

# Target: the Arduino Wire library with all library source files to compile
# 	Latest release from github extracted in src/
#	https://github.com/arduino/ArduinoCore-avr/releases/tag/1.8.5
# To generate a list of .c and cpp files in Linux:
#       cd <project directory>
#       find src/libraries/Wire -name \*.[cSs]\*
add_library(${PROJECT_NAME} STATIC
	src/libraries/Wire/src/utility/twi.c
	src/libraries/Wire/src/Wire.cpp
)

# Here the compiler finds include files (-I flags)
target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/Wire/src/utility
	${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/Wire/src
	${ARDUINO_PATH}/include/arduino
)

# All .h files of Wire
# To get a list of .h files (in Linux):
#       cd <project directory>
#       find src/libraries/Wire -name \*.h
set(INCLUDES
	src/libraries/Wire/src/utility/twi.h
	src/libraries/Wire/src/Wire.h
)

# Install the library here (INSTALL_PREFIX_PATH is prepended)
install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION lib)
install(FILES ${INCLUDES} DESTINATION include/arduino)

