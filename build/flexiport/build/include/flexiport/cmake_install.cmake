# Install script for directory: /home/zwx/mycode/hokuyoaist/build/flexiport/include/flexiport

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "library" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/flexiport-2/flexiport" TYPE FILE FILES
    "/home/zwx/mycode/hokuyoaist/build/flexiport/include/flexiport/flexiport.h"
    "/home/zwx/mycode/hokuyoaist/build/flexiport/include/flexiport/flexiport_types.h"
    "/home/zwx/mycode/hokuyoaist/build/flexiport/include/flexiport/logfile.h"
    "/home/zwx/mycode/hokuyoaist/build/flexiport/include/flexiport/logreaderport.h"
    "/home/zwx/mycode/hokuyoaist/build/flexiport/include/flexiport/logwriterport.h"
    "/home/zwx/mycode/hokuyoaist/build/flexiport/include/flexiport/port.h"
    "/home/zwx/mycode/hokuyoaist/build/flexiport/include/flexiport/serialport.h"
    "/home/zwx/mycode/hokuyoaist/build/flexiport/include/flexiport/tcpport.h"
    "/home/zwx/mycode/hokuyoaist/build/flexiport/include/flexiport/timeout.h"
    "/home/zwx/mycode/hokuyoaist/build/flexiport/include/flexiport/udpport.h"
    )
endif()

