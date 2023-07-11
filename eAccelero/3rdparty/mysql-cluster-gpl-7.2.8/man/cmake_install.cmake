# Install script for directory: /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ManPages")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/man/man1" TYPE FILE FILES
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/comp_err.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndbinfo_select_all.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/innochecksum.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/perror.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/msql2mysql.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/replace.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/my_print_defaults.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/resolve_stack_dump.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/myisam_ftdump.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/resolveip.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/myisamchk.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/myisamlog.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/myisampack.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql-stress-test.pl.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql-test-run.pl.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql.server.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql_client_test.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql_client_test_embedded.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql_config.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql_convert_table_format.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql_find_rows.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql_fix_extensions.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql_install_db.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql_plugin.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql_secure_installation.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql_setpermission.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql_tzinfo_to_sql.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql_upgrade.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql_waitpid.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysql_zap.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqlaccess.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqladmin.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqlbinlog.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqlbug.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqlcheck.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqld_multi.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqld_safe.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqldump.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqldumpslow.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqlhotcopy.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqlimport.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqlman.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqlshow.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqlslap.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqltest.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqltest_embedded.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb-common-options.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_config.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_cpcd.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_delete_all.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_desc.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_drop_index.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_drop_table.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_error_reporter.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_index_stat.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_mgm.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_print_backup_file.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_print_schema_file.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_print_sys_file.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_restore.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_select_all.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_select_count.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_show_tables.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_size.pl.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_waiter.1"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndbd_redo_log_reader.1"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ManPages")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ManPages")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/man/man8" TYPE FILE FILES
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndbmtd.8"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndbd.8"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/mysqld.8"
    "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/man/ndb_mgmd.8"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ManPages")

