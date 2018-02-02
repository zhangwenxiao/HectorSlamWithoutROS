# Install script for directory: /home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/hokuyoaist-3/hokuyoaist" TYPE FILE FILES
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/hokuyoaist.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/hokuyo_errors.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/scan_data.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/sensor.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/sensor_info.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/utils.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/GridMap.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/DataPointContainer.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/GridMapBase.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/GridMapCacheArray.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/GridMapLogOdds.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/GridMapReflectanceCount.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/GridMapSimpleCount.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/HectorMapMutex.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/HectorMappingRos.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/HectorSlamProcessor.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/MapDimensionProperties.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/MapLockerInterface.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/MapProContainer.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/MapRepMultiMap.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/MapRepresentationInterface.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/MapReqSingleMap.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/OccGridMapBase.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/OccGridMapUtil.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/OccGridMapUtilConfig.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/ScanMatcher.h"
    "/home/zwx/mycode/lion_code/lion_slam/lion_slam/include/hokuyoaist/UtilFunctions.h"
    )
endif()

