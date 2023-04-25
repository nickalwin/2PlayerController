# Install script for directory: /home/esadev/projects/MIC/ArduinoCoreLib

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/esadev/projects/MIC/ArduinoCoreLib/build/libArduinoCore.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/arduino" TYPE FILE FILES
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/variants/standard/pins_arduino.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/Arduino.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/binary.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/Client.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/HardwareSerial.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/HardwareSerial_private.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/IPAddress.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/new.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/PluggableUSB.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/Printable.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/Print.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/Server.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/Stream.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/Udp.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/USBAPI.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/USBCore.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/USBDesc.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/WCharacter.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/wiring_private.h"
    "/home/esadev/projects/MIC/ArduinoCoreLib/src/cores/arduino/WString.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/esadev/projects/MIC/ArduinoCoreLib/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
