#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "hokuyoaist" for configuration ""
set_property(TARGET hokuyoaist APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(hokuyoaist PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libhokuyoaist.so.3.0.2"
  IMPORTED_SONAME_NOCONFIG "libhokuyoaist.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS hokuyoaist )
list(APPEND _IMPORT_CHECK_FILES_FOR_hokuyoaist "${_IMPORT_PREFIX}/lib/libhokuyoaist.so.3.0.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
