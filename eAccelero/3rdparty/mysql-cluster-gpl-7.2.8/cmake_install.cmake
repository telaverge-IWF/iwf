# Install script for directory: /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Info")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/docs" TYPE FILE OPTIONAL FILES "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/Docs/mysql.info")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Info")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Readme")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE OPTIONAL FILES
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/COPYING"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/LICENSE.mysql"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Readme")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Readme")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/README")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Readme")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/docs" TYPE FILE FILES
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/Docs/INFO_SRC"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/Docs/INFO_BIN"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Readme")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/Docs/INSTALL-BINARY")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Readme")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Documentation")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/docs" TYPE DIRECTORY FILES "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/Docs/" REGEX "/INSTALL\\-BINARY$" EXCLUDE REGEX "/Makefile\\.[^/]*$" EXCLUDE REGEX "/glibc[^/]*$" EXCLUDE REGEX "/linuxthreads\\.txt$" EXCLUDE REGEX "/myisam\\.txt$" EXCLUDE REGEX "/mysql\\.info$" EXCLUDE REGEX "/sp\\-imp\\-spec\\.txt$" EXCLUDE)
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Documentation")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/cmd-line-utils/libedit/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/archive/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/blackhole/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/csv/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/example/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/federated/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/heap/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/innobase/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/myisam/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/myisammrg/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/perfschema/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/audit_null/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/auth/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/daemon_example/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/fulltext/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/semisync/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/include/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/dbug/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/strings/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/vio/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/regex/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/mysys/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/libmysql/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/unittest/mytap/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/unittest/mysys/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/extra/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/tests/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/client/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql/share/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/libservices/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/mysql-test/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/mysql-test/lib/My/SafeProcess/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/support-files/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/scripts/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql-bench/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/cmake_install.cmake")
  INCLUDE("/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/packaging/WiX/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
