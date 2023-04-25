# Install script for directory: /home/esadev/projects/MIC/GFX

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/esadev/Arduino")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "avr-objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/esadev/projects/MIC/GFX/build/libGFX.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/arduino" TYPE FILE FILES
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Adafruit_SPITFT.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Adafruit_GrayOLED.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/gfxfont.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Adafruit_GFX.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Adafruit_SPITFT_Macros.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/arduino/Fonts" TYPE FILE FILES
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMono12pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBold18pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBoldOblique12pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBoldItalic9pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifItalic24pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMono9pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBoldOblique18pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansOblique18pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansOblique12pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBold12pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSans9pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifItalic18pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBold9pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifItalic12pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBold18pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBoldOblique9pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerif12pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBoldOblique18pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifItalic9pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/Tiny3x3a2pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBold12pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerif24pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBold9pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoOblique18pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBold18pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoOblique12pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerif18pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSans24pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMono18pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSans12pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBoldItalic12pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoOblique9pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBold24pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMono24pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansOblique9pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerif9pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/Org_01.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBoldOblique24pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBoldOblique12pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBold24pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoOblique24pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBold12pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBold24pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBoldItalic24pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeMonoBoldOblique24pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSans18pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansBoldOblique9pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/TomThumb.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/Picopixel.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBold9pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSansOblique24pt7b.h"
    "/home/esadev/projects/MIC/GFX/src/Adafruit-GFX-Library-1.11.3/Fonts/FreeSerifBoldItalic18pt7b.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/esadev/projects/MIC/GFX/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
