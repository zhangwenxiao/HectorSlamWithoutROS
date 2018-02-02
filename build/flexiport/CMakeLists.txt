cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(Flexiport)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)
include(${PROJECT_SOURCE_DIR}/cmake/flexiport_utils.cmake)
set(PROJECT_VERSION 2.0.0 CACHE STRING "Flexiport version")
DISSECT_VERSION()
set(PROJECT_DESCRIPTION "Flexible communications library.")
set(PROJECT_VENDOR "AIST")

# Add an "uninstall" target
configure_file("${PROJECT_SOURCE_DIR}/cmake/uninstall_target.cmake.in"
    "${PROJECT_BINARY_DIR}/uninstall_target.cmake" IMMEDIATE @ONLY)
add_custom_target(uninstall "${CMAKE_COMMAND}" -P
    "${PROJECT_BINARY_DIR}/uninstall_target.cmake")

option(FLEXIPORT_INCLUDE_SERIAL "Build serial port support" ON)
option(FLEXIPORT_INCLUDE_TCP "Build TCP network port support" ON)
option(FLEXIPORT_INCLUDE_UDP "Build UDP network port support" ON)
option(FLEXIPORT_INCLUDE_BT "Build Bluetooth RFCOMM port support" ON)
option(FLEXIPORT_INCLUDE_LOGGING "Build log reader/writer port support" ON)
mark_as_advanced(FLEXIPORT_INCLUDE_SERIAL FLEXIPORT_INCLUDE_TCP FLEXIPORT_INCLUDE_UDP FLEXIPORT_INCLUDE_BT)
option(BUILD_EXAMPLES "Build and install examples" ON)
option(BUILD_PYTHON_BINDINGS "Build Python bindings" OFF)
option(BUILD_DOCUMENTATION "Build the documentation" ON)

option(FLEXIPORT_STATIC_LIBS "Build static libraries" OFF)
if(FLEXIPORT_STATIC_LIBS)
    set(LIB_TYPE STATIC)
else(FLEXIPORT_STATIC_LIBS)
    set(LIB_TYPE SHARED)
endif(FLEXIPORT_STATIC_LIBS)

# Check for function alternatives
if(QNXNTO)
    set(CMAKE_REQUIRED_LIBRARIES socket)
endif(QNXNTO)
include(CheckFunctionExists)
CHECK_FUNCTION_EXISTS(getaddrinfo FLEXIPORT_HAVE_GETADDRINFO)
set(CMAKE_REQUIRED_LIBRARIES)

# Check for bluetooth (bluez) support using pkg-config
if(FLEXIPORT_INCLUDE_BT)
    include(FindPkgConfig)
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(BLUETOOTH bluez)
        if(NOT BLUETOOTH_FOUND)
            message(WARNING "bluez not found, bluetooth support disabled")
            set(FLEXIPORT_INCLUDE_BT OFF)
        endif(NOT BLUETOOTH_FOUND)
    else(PKG_CONFIG_FOUND)
        message(WARNING "Could not find pkg-config, bluetooth support disabled")
        set(FLEXIPORT_INCLUDE_BT OFF)
    endif(PKG_CONFIG_FOUND)
endif(FLEXIPORT_INCLUDE_BT)

# Set up installation directories
set(BIN_INSTALL_DIR "bin")
set(LIB_INSTALL_DIR "lib")
set(INC_INSTALL_DIR
    "include/${PROJECT_NAME_LOWER}-${PROJECT_VERSION_MAJOR}")
set(SHARE_INSTALL_DIR
    "share/${PROJECT_NAME_LOWER}-${PROJECT_VERSION_MAJOR}")

# Make the config header
set(config_h_in ${PROJECT_SOURCE_DIR}/include/flexiport/config.h.in)
set(config_h ${PROJECT_BINARY_DIR}/include/flexiport/config.h)
configure_file(${config_h_in} ${config_h})
install(FILES ${config_h} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

# Subdirectories
add_subdirectory(cmake)
#if(BUILD_DOCUMENTATION)
#    add_subdirectory(doc)
#endif(BUILD_DOCUMENTATION)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif(BUILD_EXAMPLES)
add_subdirectory(include)
add_subdirectory(src)
if(BUILD_PYTHON_BINDINGS)
    add_subdirectory(python)
endif(BUILD_PYTHON_BINDINGS)

# Package creation
include(InstallRequiredSystemLibraries)
set(PROJECT_EXECUTABLES ${EXAMPLE_EXECUTABLES})
set(cpack_options "${PROJECT_BINARY_DIR}/cpack_options.cmake")
configure_file("${PROJECT_SOURCE_DIR}/cmake/cpack_options.cmake.in"
    ${cpack_options} @ONLY)
set(CPACK_PROJECT_CONFIG_FILE ${cpack_options})
include(CPack)

