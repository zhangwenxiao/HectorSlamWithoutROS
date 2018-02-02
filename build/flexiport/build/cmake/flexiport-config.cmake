# Flexiport CMake config file
#
# This file sets the following variables:
# Flexiport_FOUND - Always TRUE.
# Flexiport_INCLUDE_DIRS - Directories containing the Flexiport include files.
# Flexiport_LIBRARIES - Libraries needed to use Flexiport.
# Flexiport_DEFINITIONS - Compiler flags for Flexiport.
# Flexiport_VERSION - The version of Flexiport found.
# Flexiport_VERSION_MAJOR - The major version of Flexiport found.
# Flexiport_VERSION_MINOR - The minor version of Flexiport found.
# Flexiport_VERSION_REVISION - The revision version of Flexiport found.
# Flexiport_VERSION_CANDIDATE - The candidate version of Flexiport found.

message(STATUS "Found Flexiport-2.0.0")
set(Flexiport_FOUND TRUE)

set(Flexiport_INCLUDE_DIRS
    "/usr/local/include/flexiport-2")

if(WIN32)
    set(Flexiport_LIBRARIES
        "/usr/local/lib/libflexiport.a")
else(WIN32)
    set(Flexiport_LIBRARIES
        "/usr/local/lib/libflexiport.so")
endif(WIN32)

set(Flexiport_DEFINITIONS )

set(Flexiport_VERSION 2.0.0)
set(Flexiport_VERSION_MAJOR 2)
set(Flexiport_VERSION_MINOR 0)
set(Flexiport_VERSION_REVISION 0)
set(Flexiport_VERSION_CANDIDATE )

