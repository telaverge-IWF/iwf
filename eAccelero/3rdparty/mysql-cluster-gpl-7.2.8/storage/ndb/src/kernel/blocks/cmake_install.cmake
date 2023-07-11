# Install script for directory: /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/opt/checkout/eAccelero/3rdparty/mysql")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
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
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ClusterTools")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ndb_print_file" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ndb_print_file")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ndb_print_file"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/ndb_print_file")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ndb_print_file" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ndb_print_file")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ndb_print_file")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ClusterTools")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/backup/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dbdict/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dbdih/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dbtup/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

