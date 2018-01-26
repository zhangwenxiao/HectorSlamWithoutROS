# HokuyoAIST CMake config file
#
# This file sets the following variables:
# HokuyoAIST_FOUND - Always TRUE.
# HokuyoAIST_INCLUDE_DIRS - Directories containing the HokuyoAIST include files.
# HokuyoAIST_LIBRARIES - Libraries needed to use HokuyoAIST.
# HokuyoAIST_DEFINITIONS - Compiler flags for HokuyoAIST.
# HokuyoAIST_VERSION - The version of HokuyoAIST found.
# HokuyoAIST_VERSION_MAJOR - The major version of HokuyoAIST found.
# HokuyoAIST_VERSION_MINOR - The minor version of HokuyoAIST found.
# HokuyoAIST_VERSION_PATCH - The revision version of HokuyoAIST found.
# HokuyoAIST_VERSION_TWEAK - The candidate version of HokuyoAIST found.

message(STATUS "Found HokuyoAIST-3.0.2")
set(HokuyoAIST_FOUND TRUE)

find_package(Flexiport REQUIRED)

set(HokuyoAIST_INCLUDE_DIRS
    "/usr/local/include/hokuyoaist-3"
    ${Flexiport_INCLUDE_DIRS})

if(WIN32)
    set(HokuyoAIST_LIBRARIES
        "/usr/local/lib/libhokuyoaist.a"
        ${Flexiport_LIBRARIES}
        )
else(WIN32)
    set(HokuyoAIST_LIBRARIES
        "/usr/local/lib/libhokuyoaist.so"
        ${Flexiport_LIBRARIES}
        )
endif(WIN32)

set(HokuyoAIST_DEFINITIONS ${Flexiport_DEFINITIONS})

set(HokuyoAIST_VERSION 3.0.2)
set(HokuyoAIST_VERSION_MAJOR 3)
set(HokuyoAIST_VERSION_MINOR 0)
set(HokuyoAIST_VERSION_PATCH 2)
set(HokuyoAIST_VERSION_TWEAK )
