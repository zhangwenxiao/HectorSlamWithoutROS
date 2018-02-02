# Find the Python libraries and headers
SET (TARGET_PYTHON_VERSION 3)
FIND_PACKAGE (PythonLibs ${TARGET_PYTHON_VERSION})
if (NOT PYTHON_LIBRARIES)
  MESSAGE (STATUS "Python libaries not found. Cannot build Python bindings for HokuyoAIST.")
endif (NOT PYTHON_LIBRARIES)
STRING (REGEX MATCH "^[23]\.[0-9]" PYTHON_MAJORMINOR_VERSION "${PYTHONLIBS_VERSION_STRING}")

# Find Boost::Python
OPTION (Boost_USE_STATIC_LIBS "Use the static versions of the Boost libraries" OFF)
MARK_AS_ADVANCED (Boost_USE_STATIC_LIBS)

STRING (REGEX REPLACE "[^0-9]" "" BOOST_PY_VERSION ${PYTHON_MAJORMINOR_VERSION})
FIND_PACKAGE (Boost COMPONENTS python-py${BOOST_PY_VERSION})
if(Boost_FOUND)
  if(NOT Boost_PYTHON-PY${BOOST_PY_VERSION}_FOUND)
    MESSAGE (STATUS
      "Boost::Python library was not found. Cannot build Python bindings for HokuyoAIST.")
  endif(NOT Boost_PYTHON-PY${BOOST_PY_VERSION}_FOUND)
else(Boost_FOUND)
  MESSAGE (STATUS
      "Boost libraries were not found. Cannot build Python bindings for HokuyoAIST.")
endif(Boost_FOUND)

if(PYTHON_LIBRARIES AND Boost_PYTHON-PY${BOOST_PY_VERSION}_FOUND AND LIB_TYPE STREQUAL SHARED)
  MESSAGE (STATUS "HokuyoAIST Python bindings will be built.")

  SET (pyModuleTarget hokuyoaist_py)
  INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIRS})
  INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/include/hokuyoaist ${PYTHON_INCLUDE_PATH})
  add_library(${pyModuleTarget} MODULE hokuyo_aist.cpp)
  TARGET_LINK_LIBRARIES (${pyModuleTarget} hokuyoaist Boost::python-py${BOOST_PY_VERSION} ${PYTHON_LIBRARIES})
  SET_TARGET_PROPERTIES (${pyModuleTarget} PROPERTIES PREFIX "" OUTPUT_NAME "hokuyoaist")
  install(TARGETS ${pyModuleTarget} LIBRARY DESTINATION
    lib/python${PYTHON_MAJORMINOR_VERSION}/site-packages)

  ADD_SUBDIRECTORY (test)
ELSEIF(NOT LIB_TYPE STREQUAL SHARED)
  MESSAGE (STATUS "HokuyoAIST Python bindings will not be built - must build hokuyoaist as a shared library.")
endif(PYTHON_LIBRARIES AND Boost_PYTHON-PY${BOOST_PY_VERSION}_FOUND AND LIB_TYPE STREQUAL SHARED)
