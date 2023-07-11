# Install script for directory: /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn

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
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cppconn" TYPE FILE FILES
    "/opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn/build_config.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn/config.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn/connection.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn/datatype.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn/driver.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn/exception.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn/metadata.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn/parameter_metadata.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn/prepared_statement.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn/resultset.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn/resultset_metadata.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn/statement.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn/sqlstring.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/cppconn/warning.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

