# Just a recent number
cmake_minimum_required(VERSION 3.18)

# Use AVR GCC toolchain definition in your HOME/Arduino directory
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(ARDUINO_PATH $ENV{HOME}/Arduino)
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    cmake_path(CONVERT "$ENV{HOMEDRIVE}$ENV{HOMEPATH}/Arduino" TO_CMAKE_PATH_LIST ARDUINO_PATH NORMALIZE)
endif()
set(CMAKE_TOOLCHAIN_FILE ${ARDUINO_PATH}/etc/toolchain-avr.cmake)

# we need the assembler this time
enable_language(ASM)

# Project name
project("BusIO")

# Where to install
set(CMAKE_INSTALL_PREFIX ${ARDUINO_PATH})

# defines: use Arduino.h i.s.o. WProgram.h
add_compile_definitions(ARDUINO=101)

# Target: the Arduino core library with all core source files to compile
# To get a list of .c and cpp files in Linux:
#       cd <project directory>
#       find src -name \*.[cSs]\*
add_library(${PROJECT_NAME} STATIC
	src/Adafruit_BusIO-1.14.1/Adafruit_SPIDevice.cpp
	src/Adafruit_BusIO-1.14.1/Adafruit_I2CDevice.cpp
	src/Adafruit_BusIO-1.14.1/Adafruit_BusIO_Register.cpp
)

# Here the compiler finds include files (-I flags)
target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src/Adafruit_BusIO-1.14.1
	${ARDUINO_PATH}/include/arduino
)

# All .h files of Arduino core
# To get a list of .h files (in Linux):
#       cd <project directory>
#       find src -name \*.h
set(INCLUDES
	src/Adafruit_BusIO-1.14.1/Adafruit_I2CDevice.h
	src/Adafruit_BusIO-1.14.1/Adafruit_I2CRegister.h
	src/Adafruit_BusIO-1.14.1/Adafruit_BusIO_Register.h
	src/Adafruit_BusIO-1.14.1/Adafruit_SPIDevice.h
)

# Install the library here (INSTALL_PREFIX_PATH is prepended)
install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION lib)
install(FILES ${INCLUDES} DESTINATION include/arduino)
