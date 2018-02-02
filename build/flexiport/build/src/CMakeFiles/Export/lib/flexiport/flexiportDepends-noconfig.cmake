#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "flexiport" for configuration ""
set_property(TARGET flexiport APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(flexiport PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libflexiport.so.2.0.0"
  IMPORTED_SONAME_NOCONFIG "libflexiport.so.2"
  )

list(APPEND _IMPORT_CHECK_TARGETS flexiport )
list(APPEND _IMPORT_CHECK_FILES_FOR_flexiport "${_IMPORT_PREFIX}/lib/libflexiport.so.2.0.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
