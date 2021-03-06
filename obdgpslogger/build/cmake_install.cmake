# Install script for directory: /home/anthony/ClemsonVibrationResearch/obdgpslogger

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/libs/sqlite3/cmake_install.cmake")
  INCLUDE("/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/src/obdcomm/cmake_install.cmake")
  INCLUDE("/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/src/logger/cmake_install.cmake")
  INCLUDE("/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/src/gui/cmake_install.cmake")
  INCLUDE("/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/src/obdinfo/cmake_install.cmake")
  INCLUDE("/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/src/conf/cmake_install.cmake")
  INCLUDE("/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/src/analysis/cmake_install.cmake")
  INCLUDE("/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/src/kml/cmake_install.cmake")
  INCLUDE("/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/src/csv/cmake_install.cmake")
  INCLUDE("/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/src/gpx/cmake_install.cmake")
  INCLUDE("/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/src/sim/cmake_install.cmake")
  INCLUDE("/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/src/repair/cmake_install.cmake")
  INCLUDE("/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/src/ftdipty/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/anthony/ClemsonVibrationResearch/obdgpslogger/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
