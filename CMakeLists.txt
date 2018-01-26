cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(HokuyoAIST VERSION 3.0.2)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)
include(${PROJECT_SOURCE_DIR}/cmake/hokuyoaist_utils.cmake)
set(PROJECT_DESCRIPTION "Hokuyo range sensor driver.")
set(PROJECT_VENDOR "Geoffrey Biggs, AIST")

# Add an "uninstall" target
configure_file("${PROJECT_SOURCE_DIR}/cmake/uninstall_target.cmake.in"
    "${PROJECT_BINARY_DIR}/uninstall_target.cmake" IMMEDIATE @ONLY)
add_custom_target(uninstall "${CMAKE_COMMAND}" -P
    "${PROJECT_BINARY_DIR}/uninstall_target.cmake")

option(BUILD_EXAMPLES "Build and install examples" ON)
option(BUILD_PYTHON_BINDINGS "Build Python bindings" ON)
option(BUILD_DOCUMENTATION "Build the documentation" ON)

option(HOKUYOAIST_STATIC_LIBS "Build static libraries" OFF)
if(HOKUYOAIST_STATIC_LIBS)
    set(LIB_TYPE STATIC)
else(HOKUYOAIST_STATIC_LIBS)
    set(LIB_TYPE SHARED)
endif(HOKUYOAIST_STATIC_LIBS)

# Set up installation directories
set(BIN_INSTALL_DIR "bin")
set(LIB_INSTALL_DIR "lib")
set(INC_INSTALL_DIR
    "include/${PROJECT_NAME_LOWER}-${PROJECT_VERSION_MAJOR}")
set(SHARE_INSTALL_DIR
    "share/${PROJECT_NAME_LOWER}-${PROJECT_VERSION_MAJOR}")

# Dependencies
find_package(Flexiport)
# May need to link to the rt library
include(CheckFunctionExists)
set(CMAKE_REQUIRED_INCLUDES time.h)
set(CMAKE_REQUIRED_LIBRARIES rt)
CHECK_FUNCTION_EXISTS(clock_gettime HAVE_CLOCK_GETTIME)
set(CMAKE_REQUIRED_INCLUDES)
set(CMAKE_REQUIRED_LIBRARIES)

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

