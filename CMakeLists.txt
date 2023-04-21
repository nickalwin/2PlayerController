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
project("2PlayerController")

# Where to install
set(CMAKE_INSTALL_PREFIX ${ARDUINO_PATH})

# defines: use Arduino.h i.s.o. WProgram.h
add_compile_definitions(ARDUINO=101)

# Target: the Arduino core library with all core source files to compile
# To get a list of .c and cpp files in Linux:
#       cd <project directory>
#       find src/cores/arduino -name \*.[cSs]\*
add_library(${PROJECT_NAME} STATIC
	src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.cpp
	src/Adafruit-GFX-Library-1.11.3/Adafruit_GrayOLED.cpp
	src/Adafruit-GFX-Library-1.11.3/Adafruit_SPITFT.cpp
	src/Adafruit-GFX-Library-1.11.3/fontconvert/fontconvert.c
	src/Adafruit-GFX-Library-1.11.3/Adafruit_GFX.cpp
	src/Adafruit-GFX-Library-1.11.3/glcdfont.c
)

# Here the compiler finds include files (-I flags)
target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src/Adafruit_ILI9341-1.5.12
	${CMAKE_CURRENT_SOURCE_DIR}/src/Adafruit-GFX-Library-1.11.3
	${ARDUINO_PATH}/include/arduino
)

# All .h files of Arduino core
# To get a list of .h files (in Linux):
#       cd <project directory>
#       find src/cores/arduino -name \*.h
set(INCLUDES
	src/Adafruit_ILI9341-1.5.12/Adafruit_ILI9341.h
	src/Adafruit-GFX-Library-1.11.3/Adafruit_SPITFT.h
	src/Adafruit-GFX-Library-1.11.3/Adafruit_GrayOLED.h
	src/Adafruit-GFX-Library-1.11.3/gfxfont.h
	src/Adafruit-GFX-Library-1.11.3/Adafruit_GFX.h
	src/Adafruit-GFX-Library-1.11.3/Adafruit_SPITFT_Macros.h
)
set(INCLUDES_FONTS
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMono12pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBold18pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBoldOblique12pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBoldItalic9pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifItalic24pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMono9pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBoldOblique18pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansOblique18pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansOblique12pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBold12pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSans9pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifItalic18pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBold9pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifItalic12pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBold18pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBoldOblique9pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerif12pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBoldOblique18pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifItalic9pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/Tiny3x3a2pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBold12pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerif24pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBold9pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoOblique18pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBold18pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoOblique12pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerif18pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSans24pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMono18pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSans12pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBoldItalic12pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoOblique9pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBold24pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMono24pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansOblique9pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerif9pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/Org_01.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBoldOblique24pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBoldOblique12pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBold24pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoOblique24pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBold12pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBold24pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBoldItalic24pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBoldOblique24pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSans18pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBoldOblique9pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/TomThumb.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/Picopixel.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBold9pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansOblique24pt7b.h
	src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBoldItalic18pt7b.h
)

# Install the library here (INSTALL_PREFIX_PATH is prepended)
install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION lib)
install(FILES ${INCLUDES} DESTINATION include/arduino)
install(FILES ${INCLUDES_FONTS} DESTINATION include/arduino/Fonts)
