# Install script for directory: /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/mysql.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/mysql_com.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/mysql_time.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/my_list.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/my_alloc.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/typelib.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/mysql/plugin.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/mysql/plugin_audit.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/mysql/plugin_ftparser.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/my_dbug.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/m_string.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/my_sys.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/my_xml.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/mysql_embed.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/my_pthread.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/decimal.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/errmsg.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/my_global.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/my_net.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/my_getopt.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/sslopt-longopts.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/my_dir.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/sslopt-vars.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/sslopt-case.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/sql_common.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/keycache.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/m_ctype.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/my_attribute.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/my_compiler.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/mysql_version.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/my_config.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/mysqld_ername.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/mysqld_error.h"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/sql_state.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mysql" TYPE DIRECTORY FILES "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/mysql/" FILES_MATCHING REGEX "/[^/]*\\.h$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")

