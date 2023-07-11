const char* mysql_fix_privilege_tables[]={
"-- Copyright (c) 2007, 2011, Oracle and/or its affiliates. All rights reserved.\n "
"",
"--\n "
"",
"-- This program is free software; you can redistribute it and/or modify\n "
"",
"-- it under the terms of the GNU General Public License as published by\n "
"",
"-- the Free Software Foundation; version 2 of the License.\n "
"",
"--\n "
"",
"-- This program is distributed in the hope that it will be useful,\n "
"",
"-- but WITHOUT ANY WARRANTY; without even the implied warranty of\n "
"",
"-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n "
"",
"-- GNU General Public License for more details.\n "
"",
"--\n "
"",
"-- You should have received a copy of the GNU General Public License\n "
"",
"-- along with this program; if not, write to the Free Software\n "
"",
"-- Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA\n "
"",
"\n "
"",
"--\n "
"",
"-- The system tables of MySQL Server\n "
"",
"--\n "
"",
"\n "
"",
"set sql_mode='';\n "
"",
"set storage_engine=myisam;\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS db (   Host char(60) binary DEFAULT '' NOT NULL, Db char(64) binary DEFAULT '' NOT NULL, User char(16) binary DEFAULT '' NOT NULL, Select_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Insert_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Update_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Delete_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Create_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT"
"",
" NULL, Drop_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Grant_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, References_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Index_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Alter_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Create_tmp_table_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Lock_tables_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT "
"",
"'N' NOT NULL, Create_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Show_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Create_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Alter_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Execute_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Event_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Trigger_priv enum('N','Y') COLLATE utf8_ge"
"",
"neral_ci DEFAULT 'N' NOT NULL, PRIMARY KEY Host (Host,Db,User), KEY User (User) ) engine=MyISAM CHARACTER SET utf8 COLLATE utf8_bin comment='Database privileges';\n "
"",
"\n "
"",
"-- Remember for later if db table already existed\n "
"",
"set @had_db_table= @@warning_count != 0;\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS host (  Host char(60) binary DEFAULT '' NOT NULL, Db char(64) binary DEFAULT '' NOT NULL, Select_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Insert_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Update_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Delete_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Create_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Drop_priv enum('N','Y') COLLATE ut"
"",
"f8_general_ci DEFAULT 'N' NOT NULL, Grant_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, References_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Index_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Alter_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Create_tmp_table_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Lock_tables_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Create_view_priv enum('N','"
"",
"Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Show_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Create_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Alter_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Execute_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Trigger_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, PRIMARY KEY Host (Host,Db) ) engine=MyISAM CHARACTER SET utf8 COLLATE utf8_bin co"
"",
"mment='Host privileges;  Merged with database privileges';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS user (   Host char(60) binary DEFAULT '' NOT NULL, User char(16) binary DEFAULT '' NOT NULL, Password char(41) character set latin1 collate latin1_bin DEFAULT '' NOT NULL, Select_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Insert_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Update_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Delete_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Create_priv enum('N','Y'"
"",
") COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Drop_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Reload_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Shutdown_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Process_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, File_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Grant_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, References_priv enum('N','Y') COL"
"",
"LATE utf8_general_ci DEFAULT 'N' NOT NULL, Index_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Alter_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Show_db_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Super_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Create_tmp_table_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Lock_tables_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Execute_priv enum('N','"
"",
"Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Repl_slave_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Repl_client_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Create_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Show_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Create_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Alter_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NUL"
"",
"L, Create_user_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Event_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Trigger_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, Create_tablespace_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, ssl_type enum('','ANY','X509', 'SPECIFIED') COLLATE utf8_general_ci DEFAULT '' NOT NULL, ssl_cipher BLOB NOT NULL, x509_issuer BLOB NOT NULL, x509_subject BLOB NOT NULL, max_questions int(11) unsigned DEF"
"",
"AULT 0  NOT NULL, max_updates int(11) unsigned DEFAULT 0  NOT NULL, max_connections int(11) unsigned DEFAULT 0  NOT NULL, max_user_connections int(11) unsigned DEFAULT 0  NOT NULL, plugin char(64) DEFAULT '', authentication_string TEXT, PRIMARY KEY Host (Host,User) ) engine=MyISAM CHARACTER SET utf8 COLLATE utf8_bin comment='Users and global privileges';\n "
"",
"\n "
"",
"-- Remember for later if user table already existed\n "
"",
"set @had_user_table= @@warning_count != 0;\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS func (  name char(64) binary DEFAULT '' NOT NULL, ret tinyint(1) DEFAULT '0' NOT NULL, dl char(128) DEFAULT '' NOT NULL, type enum ('function','aggregate') COLLATE utf8_general_ci NOT NULL, PRIMARY KEY (name) ) engine=MyISAM CHARACTER SET utf8 COLLATE utf8_bin   comment='User defined functions';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS plugin ( name varchar(64) DEFAULT '' NOT NULL, dl varchar(128) DEFAULT '' NOT NULL, PRIMARY KEY (name) ) engine=MyISAM CHARACTER SET utf8 COLLATE utf8_general_ci comment='MySQL plugins';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS servers ( Server_name char(64) NOT NULL DEFAULT '', Host char(64) NOT NULL DEFAULT '', Db char(64) NOT NULL DEFAULT '', Username char(64) NOT NULL DEFAULT '', Password char(64) NOT NULL DEFAULT '', Port INT(4) NOT NULL DEFAULT '0', Socket char(64) NOT NULL DEFAULT '', Wrapper char(64) NOT NULL DEFAULT '', Owner char(64) NOT NULL DEFAULT '', PRIMARY KEY (Server_name)) CHARACTER SET utf8 comment='MySQL Foreign Servers table';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS tables_priv ( Host char(60) binary DEFAULT '' NOT NULL, Db char(64) binary DEFAULT '' NOT NULL, User char(16) binary DEFAULT '' NOT NULL, Table_name char(64) binary DEFAULT '' NOT NULL, Grantor char(77) DEFAULT '' NOT NULL, Timestamp timestamp, Table_priv set('Select','Insert','Update','Delete','Create','Drop','Grant','References','Index','Alter','Create View','Show view','Trigger') COLLATE utf8_general_ci DEFAULT '' NOT NULL, Column_priv set('Select','Insert','Update','Reference"
"",
"s') COLLATE utf8_general_ci DEFAULT '' NOT NULL, PRIMARY KEY (Host,Db,User,Table_name), KEY Grantor (Grantor) ) engine=MyISAM CHARACTER SET utf8 COLLATE utf8_bin   comment='Table privileges';\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS columns_priv ( Host char(60) binary DEFAULT '' NOT NULL, Db char(64) binary DEFAULT '' NOT NULL, User char(16) binary DEFAULT '' NOT NULL, Table_name char(64) binary DEFAULT '' NOT NULL, Column_name char(64) binary DEFAULT '' NOT NULL, Timestamp timestamp, Column_priv set('Select','Insert','Update','References') COLLATE utf8_general_ci DEFAULT '' NOT NULL, PRIMARY KEY (Host,Db,User,Table_name,Column_name) ) engine=MyISAM CHARACTER SET utf8 COLLATE utf8_bin   comment='Column privi"
"",
"leges';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS help_topic ( help_topic_id int unsigned not null, name char(64) not null, help_category_id smallint unsigned not null, description text not null, example  text not null, url char(128) not null, primary key (help_topic_id), unique index (name) ) engine=MyISAM CHARACTER SET utf8   comment='help topics';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS help_category ( help_category_id smallint unsigned not null, name  char(64) not null, parent_category_id smallint unsigned null, url char(128) not null, primary key (help_category_id), unique index (name) ) engine=MyISAM CHARACTER SET utf8   comment='help categories';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS help_relation ( help_topic_id int unsigned not null references help_topic, help_keyword_id  int unsigned not null references help_keyword, primary key (help_keyword_id, help_topic_id) ) engine=MyISAM CHARACTER SET utf8 comment='keyword-topic relation';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS help_keyword (   help_keyword_id  int unsigned not null, name char(64) not null, primary key (help_keyword_id), unique index (name) ) engine=MyISAM CHARACTER SET utf8 comment='help keywords';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS time_zone_name (   Name char(64) NOT NULL, Time_zone_id int unsigned NOT NULL, PRIMARY KEY Name (Name) ) engine=MyISAM CHARACTER SET utf8   comment='Time zone names';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS time_zone (   Time_zone_id int unsigned NOT NULL auto_increment, Use_leap_seconds enum('Y','N') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL, PRIMARY KEY TzId (Time_zone_id) ) engine=MyISAM CHARACTER SET utf8   comment='Time zones';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS time_zone_transition (   Time_zone_id int unsigned NOT NULL, Transition_time bigint signed NOT NULL, Transition_type_id int unsigned NOT NULL, PRIMARY KEY TzIdTranTime (Time_zone_id, Transition_time) ) engine=MyISAM CHARACTER SET utf8   comment='Time zone transitions';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS time_zone_transition_type (   Time_zone_id int unsigned NOT NULL, Transition_type_id int unsigned NOT NULL, Offset int signed DEFAULT 0 NOT NULL, Is_DST tinyint unsigned DEFAULT 0 NOT NULL, Abbreviation char(8) DEFAULT '' NOT NULL, PRIMARY KEY TzIdTrTId (Time_zone_id, Transition_type_id) ) engine=MyISAM CHARACTER SET utf8   comment='Time zone transition types';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS time_zone_leap_second (   Transition_time bigint signed NOT NULL, Correction int signed NOT NULL, PRIMARY KEY TranTime (Transition_time) ) engine=MyISAM CHARACTER SET utf8   comment='Leap seconds information for time zones';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS proc (db char(64) collate utf8_bin DEFAULT '' NOT NULL, name char(64) DEFAULT '' NOT NULL, type enum('FUNCTION','PROCEDURE') NOT NULL, specific_name char(64) DEFAULT '' NOT NULL, language enum('SQL') DEFAULT 'SQL' NOT NULL, sql_data_access enum( 'CONTAINS_SQL', 'NO_SQL', 'READS_SQL_DATA', 'MODIFIES_SQL_DATA') DEFAULT 'CONTAINS_SQL' NOT NULL, is_deterministic enum('YES','NO') DEFAULT 'NO' NOT NULL, security_type enum('INVOKER','DEFINER') DEFAULT 'DEFINER' NOT NULL, param_list blob"
"",
" NOT NULL, returns longblob DEFAULT '' NOT NULL, body longblob NOT NULL, definer char(77) collate utf8_bin DEFAULT '' NOT NULL, created timestamp, modified timestamp, sql_mode set( 'REAL_AS_FLOAT', 'PIPES_AS_CONCAT', 'ANSI_QUOTES', 'IGNORE_SPACE', 'NOT_USED', 'ONLY_FULL_GROUP_BY', 'NO_UNSIGNED_SUBTRACTION', 'NO_DIR_IN_CREATE', 'POSTGRESQL', 'ORACLE', 'MSSQL', 'DB2', 'MAXDB', 'NO_KEY_OPTIONS', 'NO_TABLE_OPTIONS', 'NO_FIELD_OPTIONS', 'MYSQL323', 'MYSQL40', 'ANSI', 'NO_AUTO_VALUE_ON_ZERO', 'NO_BACKSLASH_ESCAP"
"",
"ES', 'STRICT_TRANS_TABLES', 'STRICT_ALL_TABLES', 'NO_ZERO_IN_DATE', 'NO_ZERO_DATE', 'INVALID_DATES', 'ERROR_FOR_DIVISION_BY_ZERO', 'TRADITIONAL', 'NO_AUTO_CREATE_USER', 'HIGH_NOT_PRECEDENCE', 'NO_ENGINE_SUBSTITUTION', 'PAD_CHAR_TO_FULL_LENGTH') DEFAULT '' NOT NULL, comment text collate utf8_bin NOT NULL, character_set_client char(32) collate utf8_bin, collation_connection char(32) collate utf8_bin, db_collation char(32) collate utf8_bin, body_utf8 longblob, PRIMARY KEY (db,name,type)) engine=MyISAM charact"
"",
"er set utf8 comment='Stored Procedures';\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS procs_priv ( Host char(60) binary DEFAULT '' NOT NULL, Db char(64) binary DEFAULT '' NOT NULL, User char(16) binary DEFAULT '' NOT NULL, Routine_name char(64) COLLATE utf8_general_ci DEFAULT '' NOT NULL, Routine_type enum('FUNCTION','PROCEDURE') NOT NULL, Grantor char(77) DEFAULT '' NOT NULL, Proc_priv set('Execute','Alter Routine','Grant') COLLATE utf8_general_ci DEFAULT '' NOT NULL, Timestamp timestamp, PRIMARY KEY (Host,Db,User,Routine_name,Routine_type), KEY Grantor (Grantor)"
"",
" ) engine=MyISAM CHARACTER SET utf8 COLLATE utf8_bin   comment='Procedure privileges';\n "
"",
"\n "
"",
"-- Create general_log if CSV is enabled.\n "
"",
"\n "
"",
"SET @str = IF (@@have_csv = 'YES', 'CREATE TABLE IF NOT EXISTS general_log (event_time TIMESTAMP NOT NULL, user_host MEDIUMTEXT NOT NULL, thread_id INTEGER NOT NULL, server_id INTEGER UNSIGNED NOT NULL, command_type VARCHAR(64) NOT NULL, argument MEDIUMTEXT NOT NULL) engine=CSV CHARACTER SET utf8 comment=\"General log\"', 'SET @dummy = 0');\n "
"",
"\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"-- Create slow_log if CSV is enabled.\n "
"",
"\n "
"",
"SET @str = IF (@@have_csv = 'YES', 'CREATE TABLE IF NOT EXISTS slow_log (start_time TIMESTAMP NOT NULL, user_host MEDIUMTEXT NOT NULL, query_time TIME NOT NULL, lock_time TIME NOT NULL, rows_sent INTEGER NOT NULL, rows_examined INTEGER NOT NULL, db VARCHAR(512) NOT NULL, last_insert_id INTEGER NOT NULL, insert_id INTEGER NOT NULL, server_id INTEGER UNSIGNED NOT NULL, sql_text MEDIUMTEXT NOT NULL) engine=CSV CHARACTER SET utf8 comment=\"Slow log\"', 'SET @dummy = 0');\n "
"",
"\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS event ( db char(64) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL default '', name char(64) CHARACTER SET utf8 NOT NULL default '', body longblob NOT NULL, definer char(77) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL default '', execute_at DATETIME default NULL, interval_value int(11) default NULL, interval_field ENUM('YEAR','QUARTER','MONTH','DAY','HOUR','MINUTE','WEEK','SECOND','MICROSECOND','YEAR_MONTH','DAY_HOUR','DAY_MINUTE','DAY_SECOND','HOUR_MINUTE','HOUR_SECOND','MINUTE_S"
"",
"ECOND','DAY_MICROSECOND','HOUR_MICROSECOND','MINUTE_MICROSECOND','SECOND_MICROSECOND') default NULL, created TIMESTAMP NOT NULL, modified TIMESTAMP NOT NULL, last_executed DATETIME default NULL, starts DATETIME default NULL, ends DATETIME default NULL, status ENUM('ENABLED','DISABLED','SLAVESIDE_DISABLED') NOT NULL default 'ENABLED', on_completion ENUM('DROP','PRESERVE') NOT NULL default 'DROP', sql_mode  set('REAL_AS_FLOAT','PIPES_AS_CONCAT','ANSI_QUOTES','IGNORE_SPACE','NOT_USED','ONLY_FULL_GROUP_BY','NO"
"",
"_UNSIGNED_SUBTRACTION','NO_DIR_IN_CREATE','POSTGRESQL','ORACLE','MSSQL','DB2','MAXDB','NO_KEY_OPTIONS','NO_TABLE_OPTIONS','NO_FIELD_OPTIONS','MYSQL323','MYSQL40','ANSI','NO_AUTO_VALUE_ON_ZERO','NO_BACKSLASH_ESCAPES','STRICT_TRANS_TABLES','STRICT_ALL_TABLES','NO_ZERO_IN_DATE','NO_ZERO_DATE','INVALID_DATES','ERROR_FOR_DIVISION_BY_ZERO','TRADITIONAL','NO_AUTO_CREATE_USER','HIGH_NOT_PRECEDENCE','NO_ENGINE_SUBSTITUTION','PAD_CHAR_TO_FULL_LENGTH') DEFAULT '' NOT NULL, comment char(64) CHARACTER SET utf8 COLLATE "
"",
"utf8_bin NOT NULL default '', originator INTEGER UNSIGNED NOT NULL, time_zone char(64) CHARACTER SET latin1 NOT NULL DEFAULT 'SYSTEM', character_set_client char(32) collate utf8_bin, collation_connection char(32) collate utf8_bin, db_collation char(32) collate utf8_bin, body_utf8 longblob, PRIMARY KEY (db, name) ) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT 'Events';\n "
"",
"\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS ndb_binlog_index (Position BIGINT UNSIGNED NOT NULL, File VARCHAR(255) NOT NULL, epoch BIGINT UNSIGNED NOT NULL, inserts INT UNSIGNED NOT NULL, updates INT UNSIGNED NOT NULL, deletes INT UNSIGNED NOT NULL, schemaops INT UNSIGNED NOT NULL, orig_server_id INT UNSIGNED NOT NULL, orig_epoch BIGINT UNSIGNED NOT NULL, gci INT UNSIGNED NOT NULL, next_position BIGINT UNSIGNED NOT NULL, next_file VARCHAR(255) NOT NULL, PRIMARY KEY(epoch, orig_server_id, orig_epoch)) ENGINE=MYISAM;\n "
"",
"\n "
"",
"--\n "
"",
"-- PERFORMANCE SCHEMA INSTALLATION\n "
"",
"-- Note that this script is also reused by mysql_upgrade,\n "
"",
"-- so we have to be very careful here to not destroy any\n "
"",
"-- existing database named 'performance_schema' if it\n "
"",
"-- can contain user data.\n "
"",
"-- In case of downgrade, it's ok to drop unknown tables\n "
"",
"-- from a future version, as long as they belong to the\n "
"",
"-- performance schema engine.\n "
"",
"--\n "
"",
"\n "
"",
"set @have_old_pfs= (select count(*) from information_schema.schemata where schema_name='performance_schema');\n "
"",
"\n "
"",
"SET @l1=\"SET @broken_tables = (select count(*) from information_schema.tables\";\n "
"",
"SET @l2=\" where engine != \'PERFORMANCE_SCHEMA\' and table_schema=\'performance_schema\')\";\n "
"",
"SET @cmd=concat(@l1,@l2);\n "
"",
"\n "
"",
"-- Work around for bug#49542\n "
"",
"SET @str = IF(@have_old_pfs = 1, @cmd, 'SET @broken_tables = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @l1=\"SET @broken_views = (select count(*) from information_schema.views\";\n "
"",
"SET @l2=\" where table_schema='performance_schema')\";\n "
"",
"SET @cmd=concat(@l1,@l2);\n "
"",
"\n "
"",
"-- Work around for bug#49542\n "
"",
"SET @str = IF(@have_old_pfs = 1, @cmd, 'SET @broken_views = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @broken_routines = (select count(*) from mysql.proc where db='performance_schema');\n "
"",
"\n "
"",
"SET @broken_events = (select count(*) from mysql.event where db='performance_schema');\n "
"",
"\n "
"",
"SET @broken_pfs= (select @broken_tables + @broken_views + @broken_routines + @broken_events);\n "
"",
"\n "
"",
"--\n "
"",
"-- The performance schema database.\n "
"",
"-- Only drop and create the database if this is safe (no broken_pfs).\n "
"",
"-- This database is created, even in --without-perfschema builds,\n "
"",
"-- so that the database name is always reserved by the MySQL implementation.\n "
"",
"--\n "
"",
"\n "
"",
"SET @cmd= \"DROP DATABASE IF EXISTS performance_schema\";\n "
"",
"\n "
"",
"SET @str = IF(@broken_pfs = 0, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @cmd= \"CREATE DATABASE performance_schema character set utf8\";\n "
"",
"\n "
"",
"SET @str = IF(@broken_pfs = 0, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- From this point, only create the performance schema tables\n "
"",
"-- if the server is build with performance schema\n "
"",
"--\n "
"",
"\n "
"",
"set @have_pfs= (select count(engine) from information_schema.engines where engine='PERFORMANCE_SCHEMA' and support != 'NO');\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE COND_INSTANCES\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.cond_instances(\";\n "
"",
"SET @l2=\"NAME VARCHAR(128) not null,\";\n "
"",
"SET @l3=\"OBJECT_INSTANCE_BEGIN BIGINT not null\";\n "
"",
"SET @l4=\")ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE EVENTS_WAITS_CURRENT\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.events_waits_current(\";\n "
"",
"SET @l2=\"THREAD_ID INTEGER not null,\";\n "
"",
"SET @l3=\"EVENT_ID BIGINT unsigned not null,\";\n "
"",
"SET @l4=\"EVENT_NAME VARCHAR(128) not null,\";\n "
"",
"SET @l5=\"SOURCE VARCHAR(64),\";\n "
"",
"SET @l6=\"TIMER_START BIGINT unsigned,\";\n "
"",
"SET @l7=\"TIMER_END BIGINT unsigned,\";\n "
"",
"SET @l8=\"TIMER_WAIT BIGINT unsigned,\";\n "
"",
"SET @l9=\"SPINS INTEGER unsigned,\";\n "
"",
"SET @l10=\"OBJECT_SCHEMA VARCHAR(64),\";\n "
"",
"SET @l11=\"OBJECT_NAME VARCHAR(512),\";\n "
"",
"SET @l12=\"OBJECT_TYPE VARCHAR(64),\";\n "
"",
"SET @l13=\"OBJECT_INSTANCE_BEGIN BIGINT not null,\";\n "
"",
"SET @l14=\"NESTING_EVENT_ID BIGINT unsigned,\";\n "
"",
"SET @l15=\"OPERATION VARCHAR(16) not null,\";\n "
"",
"SET @l16=\"NUMBER_OF_BYTES BIGINT unsigned,\";\n "
"",
"SET @l17=\"FLAGS INTEGER unsigned\";\n "
"",
"SET @l18=\")ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4,@l5,@l6,@l7,@l8,@l9,@l10,@l11,@l12,@l13,@l14,@l15,@l16,@l17,@l18);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE EVENTS_WAITS_HISTORY\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.events_waits_history(\";\n "
"",
"-- lines 2 to 18 are unchanged from EVENTS_WAITS_CURRENT\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4,@l5,@l6,@l7,@l8,@l9,@l10,@l11,@l12,@l13,@l14,@l15,@l16,@l17,@l18);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE EVENTS_WAITS_HISTORY_LONG\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.events_waits_history_long(\";\n "
"",
"-- lines 2 to 18 are unchanged from EVENTS_WAITS_CURRENT\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4,@l5,@l6,@l7,@l8,@l9,@l10,@l11,@l12,@l13,@l14,@l15,@l16,@l17,@l18);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE EVENTS_WAITS_SUMMARY_BY_INSTANCE\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.events_waits_summary_by_instance(\";\n "
"",
"SET @l2=\"EVENT_NAME VARCHAR(128) not null,\";\n "
"",
"SET @l3=\"OBJECT_INSTANCE_BEGIN BIGINT not null,\";\n "
"",
"SET @l4=\"COUNT_STAR BIGINT unsigned not null,\";\n "
"",
"SET @l5=\"SUM_TIMER_WAIT BIGINT unsigned not null,\";\n "
"",
"SET @l6=\"MIN_TIMER_WAIT BIGINT unsigned not null,\";\n "
"",
"SET @l7=\"AVG_TIMER_WAIT BIGINT unsigned not null,\";\n "
"",
"SET @l8=\"MAX_TIMER_WAIT BIGINT unsigned not null\";\n "
"",
"SET @l9=\")ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4,@l5,@l6,@l7,@l8,@l9);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE EVENTS_WAITS_SUMMARY_BY_THREAD_BY_EVENT_NAME\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.events_waits_summary_by_thread_by_event_name(\";\n "
"",
"SET @l2=\"THREAD_ID INTEGER not null,\";\n "
"",
"SET @l3=\"EVENT_NAME VARCHAR(128) not null,\";\n "
"",
"SET @l4=\"COUNT_STAR BIGINT unsigned not null,\";\n "
"",
"SET @l5=\"SUM_TIMER_WAIT BIGINT unsigned not null,\";\n "
"",
"SET @l6=\"MIN_TIMER_WAIT BIGINT unsigned not null,\";\n "
"",
"SET @l7=\"AVG_TIMER_WAIT BIGINT unsigned not null,\";\n "
"",
"SET @l8=\"MAX_TIMER_WAIT BIGINT unsigned not null\";\n "
"",
"SET @l9=\")ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4,@l5,@l6,@l7,@l8,@l9);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE EVENTS_WAITS_SUMMARY_GLOBAL_BY_EVENT_NAME\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.events_waits_summary_global_by_event_name(\";\n "
"",
"SET @l2=\"EVENT_NAME VARCHAR(128) not null,\";\n "
"",
"SET @l3=\"COUNT_STAR BIGINT unsigned not null,\";\n "
"",
"SET @l4=\"SUM_TIMER_WAIT BIGINT unsigned not null,\";\n "
"",
"SET @l5=\"MIN_TIMER_WAIT BIGINT unsigned not null,\";\n "
"",
"SET @l6=\"AVG_TIMER_WAIT BIGINT unsigned not null,\";\n "
"",
"SET @l7=\"MAX_TIMER_WAIT BIGINT unsigned not null\";\n "
"",
"SET @l8=\")ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4,@l5,@l6,@l7,@l8);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE FILE_INSTANCES\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.file_instances(\";\n "
"",
"SET @l2=\"FILE_NAME VARCHAR(512) not null,\";\n "
"",
"SET @l3=\"EVENT_NAME VARCHAR(128) not null,\";\n "
"",
"SET @l4=\"OPEN_COUNT INTEGER unsigned not null\";\n "
"",
"SET @l5=\")ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4,@l5);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE FILE_SUMMARY_BY_EVENT_NAME\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.file_summary_by_event_name(\";\n "
"",
"SET @l2=\"EVENT_NAME VARCHAR(128) not null,\";\n "
"",
"SET @l3=\"COUNT_READ BIGINT unsigned not null,\";\n "
"",
"SET @l4=\"COUNT_WRITE BIGINT unsigned not null,\";\n "
"",
"SET @l5=\"SUM_NUMBER_OF_BYTES_READ BIGINT unsigned not null,\";\n "
"",
"SET @l6=\"SUM_NUMBER_OF_BYTES_WRITE BIGINT unsigned not null\";\n "
"",
"SET @l7=\")ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4,@l5,@l6,@l7);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE FILE_SUMMARY_BY_INSTANCE\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.file_summary_by_instance(\";\n "
"",
"SET @l2=\"FILE_NAME VARCHAR(512) not null,\";\n "
"",
"SET @l3=\"EVENT_NAME VARCHAR(128) not null,\";\n "
"",
"SET @l4=\"COUNT_READ BIGINT unsigned not null,\";\n "
"",
"SET @l5=\"COUNT_WRITE BIGINT unsigned not null,\";\n "
"",
"SET @l6=\"SUM_NUMBER_OF_BYTES_READ BIGINT unsigned not null,\";\n "
"",
"SET @l7=\"SUM_NUMBER_OF_BYTES_WRITE BIGINT unsigned not null\";\n "
"",
"SET @l8=\")ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4,@l5,@l6,@l7,@l8);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE MUTEX_INSTANCES\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.mutex_instances(\";\n "
"",
"SET @l2=\"NAME VARCHAR(128) not null,\";\n "
"",
"SET @l3=\"OBJECT_INSTANCE_BEGIN BIGINT not null,\";\n "
"",
"SET @l4=\"LOCKED_BY_THREAD_ID INTEGER\";\n "
"",
"SET @l5=\")ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4,@l5);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE PERFORMANCE_TIMERS\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.performance_timers(\";\n "
"",
"SET @l2=\"TIMER_NAME ENUM ('CYCLE', 'NANOSECOND', 'MICROSECOND', 'MILLISECOND', 'TICK') not null,\";\n "
"",
"SET @l3=\"TIMER_FREQUENCY BIGINT,\";\n "
"",
"SET @l4=\"TIMER_RESOLUTION BIGINT,\";\n "
"",
"SET @l5=\"TIMER_OVERHEAD BIGINT\";\n "
"",
"SET @l6=\") ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4,@l5,@l6);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE RWLOCK_INSTANCES\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.rwlock_instances(\";\n "
"",
"SET @l2=\"NAME VARCHAR(128) not null,\";\n "
"",
"SET @l3=\"OBJECT_INSTANCE_BEGIN BIGINT not null,\";\n "
"",
"SET @l4=\"WRITE_LOCKED_BY_THREAD_ID INTEGER,\";\n "
"",
"SET @l5=\"READ_LOCKED_BY_COUNT INTEGER unsigned not null\";\n "
"",
"SET @l6=\")ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4,@l5,@l6);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE SETUP_CONSUMERS\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.setup_consumers(\";\n "
"",
"SET @l2=\"NAME VARCHAR(64) not null,\";\n "
"",
"SET @l3=\"ENABLED ENUM ('YES', 'NO') not null\";\n "
"",
"SET @l4=\")ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE SETUP_INSTRUMENTS\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.setup_instruments(\";\n "
"",
"SET @l2=\"NAME VARCHAR(128) not null,\";\n "
"",
"SET @l3=\"ENABLED ENUM ('YES', 'NO') not null,\";\n "
"",
"SET @l4=\"TIMED ENUM ('YES', 'NO') not null\";\n "
"",
"SET @l5=\")ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4,@l5);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE SETUP_TIMERS\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.setup_timers(\";\n "
"",
"SET @l2=\"NAME VARCHAR(64) not null,\";\n "
"",
"SET @l3=\"TIMER_NAME ENUM ('CYCLE', 'NANOSECOND', 'MICROSECOND', 'MILLISECOND', 'TICK') not null\";\n "
"",
"SET @l4=\")ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"--\n "
"",
"-- TABLE THREADS\n "
"",
"--\n "
"",
"\n "
"",
"SET @l1=\"CREATE TABLE performance_schema.threads(\";\n "
"",
"SET @l2=\"THREAD_ID INTEGER not null,\";\n "
"",
"SET @l3=\"PROCESSLIST_ID INTEGER,\";\n "
"",
"SET @l4=\"NAME VARCHAR(128) not null\";\n "
"",
"SET @l5=\")ENGINE=PERFORMANCE_SCHEMA;\";\n "
"",
"\n "
"",
"SET @cmd=concat(@l1,@l2,@l3,@l4,@l5);\n "
"",
"\n "
"",
"SET @str = IF(@have_pfs = 1, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"CREATE TABLE IF NOT EXISTS proxies_priv (Host char(60) binary DEFAULT '' NOT NULL, User char(16) binary DEFAULT '' NOT NULL, Proxied_host char(60) binary DEFAULT '' NOT NULL, Proxied_user char(16) binary DEFAULT '' NOT NULL, With_grant BOOL DEFAULT 0 NOT NULL, Grantor char(77) DEFAULT '' NOT NULL, Timestamp timestamp, PRIMARY KEY Host (Host,User,Proxied_host,Proxied_user), KEY Grantor (Grantor) ) engine=MyISAM CHARACTER SET utf8 COLLATE utf8_bin comment='User proxy privileges';\n "
"",
"\n "
"",
"-- Remember for later if proxies_priv table already existed\n "
"",
"set @had_proxies_priv_table= @@warning_count != 0;\n "
"",
"\n "
"",
"#\n "
"",
"# SQL commands for creating the tables in MySQL Server which\n "
"",
"# are used by the NDBINFO storage engine to access system\n "
"",
"# information and statistics from MySQL Cluster\n "
"",
"#\n "
"",
"# Only create objects if NDBINFO is supported\n "
"",
"SELECT @have_ndbinfo:= COUNT(*) FROM information_schema.engines WHERE engine='NDBINFO' AND support IN ('YES', 'DEFAULT');\n "
"",
"\n "
"",
"# Only create objects if version >= 7.1\n "
"",
"SET @str=IF(@have_ndbinfo,'SELECT @have_ndbinfo:= (@@ndbinfo_version >= (7 << 16) | (1 << 8)) || @ndbinfo_skip_version_check','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# Only create objects if ndbinfo namespace is free\n "
"",
"SET @str=IF(@have_ndbinfo,'SET @@ndbinfo_show_hidden=TRUE','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'SELECT @have_ndbinfo:= COUNT(*) = 0 FROM information_schema.tables WHERE table_schema = @@ndbinfo_database AND LEFT(table_name, LENGTH(@@ndbinfo_table_prefix)) = @@ndbinfo_table_prefix AND engine != \"ndbinfo\"','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'SET @@ndbinfo_show_hidden=default','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE DATABASE IF NOT EXISTS `ndbinfo`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# Set NDBINFO in offline mode during (re)create of tables\n "
"",
"# and views to avoid errors caused by no such table or\n "
"",
"# different table definition in NDB\n "
"",
"SET @str=IF(@have_ndbinfo,'SET @@global.ndbinfo_offline=TRUE','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# Drop any old views in ndbinfo\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`transporters`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`logspaces`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`logbuffers`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`resources`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`counters`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`nodes`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`memoryusage`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`diskpagebuffer`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`diskpagebuffer`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`threadblocks`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`threadstat`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`cluster_transactions`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`server_transactions`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`cluster_operations`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`server_operations`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# Drop any old lookup tables in ndbinfo\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`blocks`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`config_params`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$dbtc_apiconnect_state`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$dblqh_tcconnect_state`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$tables\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$tables`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$tables` (`table_id` INT UNSIGNED,`table_name` VARCHAR(512),`comment` VARCHAR(512)) COMMENT=\"metadata for tables available through ndbinfo\" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$columns\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$columns`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$columns` (`table_id` INT UNSIGNED,`column_id` INT UNSIGNED,`column_name` VARCHAR(512),`column_type` INT UNSIGNED,`comment` VARCHAR(512)) COMMENT=\"metadata for columns available through ndbinfo \" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$test\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$test`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$test` (`node_id` INT UNSIGNED,`block_number` INT UNSIGNED,`block_instance` INT UNSIGNED,`counter` INT UNSIGNED,`counter2` BIGINT UNSIGNED) COMMENT=\"for testing\" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$pools\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$pools`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$pools` (`node_id` INT UNSIGNED,`block_number` INT UNSIGNED,`block_instance` INT UNSIGNED,`pool_name` VARCHAR(512),`used` BIGINT UNSIGNED COMMENT \"currently in use\",`total` BIGINT UNSIGNED COMMENT \"total allocated\",`high` BIGINT UNSIGNED COMMENT \"in use high water mark\",`entry_size` BIGINT UNSIGNED COMMENT \"size in bytes of each object\",`config_param1` INT UNSIGNED COMMENT \"config param 1 affecting pool\",`config_param2` INT UNSIGNED COMMENT \"config para"
"",
"m 2 affecting pool\",`config_param3` INT UNSIGNED COMMENT \"config param 3 affecting pool\",`config_param4` INT UNSIGNED COMMENT \"config param 4 affecting pool\") COMMENT=\"pool usage\" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$transporters\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$transporters`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$transporters` (`node_id` INT UNSIGNED,`remote_node_id` INT UNSIGNED,`connection_status` INT UNSIGNED) COMMENT=\"transporter status\" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$logspaces\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$logspaces`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$logspaces` (`node_id` INT UNSIGNED,`log_type` INT UNSIGNED COMMENT \"0 = REDO, 1 = DD-UNDO\",`log_id` INT UNSIGNED,`log_part` INT UNSIGNED,`total` BIGINT UNSIGNED COMMENT \"total allocated\",`used` BIGINT UNSIGNED COMMENT \"currently in use\",`high` BIGINT UNSIGNED COMMENT \"in use high water mark\") COMMENT=\"logspace usage\" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$logbuffers\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$logbuffers`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$logbuffers` (`node_id` INT UNSIGNED,`log_type` INT UNSIGNED COMMENT \"0 = REDO, 1 = DD-UNDO\",`log_id` INT UNSIGNED,`log_part` INT UNSIGNED,`total` BIGINT UNSIGNED COMMENT \"total allocated\",`used` BIGINT UNSIGNED COMMENT \"currently in use\",`high` BIGINT UNSIGNED COMMENT \"in use high water mark\") COMMENT=\"logbuffer usage\" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$resources\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$resources`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$resources` (`node_id` INT UNSIGNED,`resource_id` INT UNSIGNED,`reserved` INT UNSIGNED COMMENT \"reserved for this resource\",`used` INT UNSIGNED COMMENT \"currently in use\",`max` INT UNSIGNED COMMENT \"max available\",`high` INT UNSIGNED COMMENT \"in use high water mark\") COMMENT=\"resources usage (a.k.a superpool)\" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$counters\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$counters`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$counters` (`node_id` INT UNSIGNED,`block_number` INT UNSIGNED,`block_instance` INT UNSIGNED,`counter_id` INT UNSIGNED,`val` BIGINT UNSIGNED COMMENT \"monotonically increasing since process start\") COMMENT=\"monotonic counters\" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$nodes\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$nodes`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$nodes` (`node_id` INT UNSIGNED,`uptime` BIGINT UNSIGNED COMMENT \"time in seconds that node has been running\",`status` INT UNSIGNED COMMENT \"starting/started/stopped etc.\",`start_phase` INT UNSIGNED COMMENT \"start phase if node is starting\",`config_generation` INT UNSIGNED COMMENT \"configuration generation number\") COMMENT=\"node status\" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$diskpagebuffer\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$diskpagebuffer`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$diskpagebuffer` (`node_id` INT UNSIGNED,`block_instance` INT UNSIGNED,`pages_written` BIGINT UNSIGNED COMMENT \"Pages written to disk\",`pages_written_lcp` BIGINT UNSIGNED COMMENT \"Pages written by local checkpoint\",`pages_read` BIGINT UNSIGNED COMMENT \"Pages read from disk\",`log_waits` BIGINT UNSIGNED COMMENT \"Page writes waiting for log to be written to disk\",`page_requests_direct_return` BIGINT UNSIGNED COMMENT \"Page in buffer and no requests waiting "
"",
"for it\",`page_requests_wait_queue` BIGINT UNSIGNED COMMENT \"Page in buffer, but some requests are already waiting for it\",`page_requests_wait_io` BIGINT UNSIGNED COMMENT \"Page not in buffer, waiting to be read from disk\") COMMENT=\"disk page buffer info\" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$threadblocks\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$threadblocks`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$threadblocks` (`node_id` INT UNSIGNED COMMENT \"node id\",`thr_no` INT UNSIGNED COMMENT \"thread number\",`block_number` INT UNSIGNED COMMENT \"block number\",`block_instance` INT UNSIGNED COMMENT \"block instance\") COMMENT=\"which blocks are run in which threads\" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$threadstat\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$threadstat`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$threadstat` (`node_id` INT UNSIGNED COMMENT \"node id\",`thr_no` INT UNSIGNED COMMENT \"thread number\",`thr_nm` VARCHAR(512) COMMENT \"thread name\",`c_loop` BIGINT UNSIGNED COMMENT \"No of loops in main loop\",`c_exec` BIGINT UNSIGNED COMMENT \"No of signals executed\",`c_wait` BIGINT UNSIGNED COMMENT \"No of times waited for more input\",`c_l_sent_prioa` BIGINT UNSIGNED COMMENT \"No of prio A signals sent to own node\",`c_l_sent_priob` BIGINT UNSIGNED COMMENT \"No"
"",
" of prio B signals sent to own node\",`c_r_sent_prioa` BIGINT UNSIGNED COMMENT \"No of prio A signals sent to remote node\",`c_r_sent_priob` BIGINT UNSIGNED COMMENT \"No of prio B signals sent to remote node\",`os_tid` BIGINT UNSIGNED COMMENT \"OS thread id\",`os_now` BIGINT UNSIGNED COMMENT \"OS gettimeofday (millis)\",`os_ru_utime` BIGINT UNSIGNED COMMENT \"OS user CPU time (micros)\",`os_ru_stime` BIGINT UNSIGNED COMMENT \"OS system CPU time (micros)\",`os_ru_minflt` BIGINT UNSIGNED COMMENT \"OS page reclaims (soft p"
"",
"age faults\",`os_ru_majflt` BIGINT UNSIGNED COMMENT \"OS page faults (hard page faults)\",`os_ru_nvcsw` BIGINT UNSIGNED COMMENT \"OS voluntary context switches\",`os_ru_nivcsw` BIGINT UNSIGNED COMMENT \"OS involuntary context switches\") COMMENT=\"Statistics on execution threads\" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$transactions\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$transactions`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$transactions` (`node_id` INT UNSIGNED COMMENT \"node id\",`block_instance` INT UNSIGNED COMMENT \"TC instance no\",`objid` INT UNSIGNED COMMENT \"Object id of transaction object\",`apiref` INT UNSIGNED COMMENT \"API reference\",`transid0` INT UNSIGNED COMMENT \"Transaction id\",`transid1` INT UNSIGNED COMMENT \"Transaction id\",`state` INT UNSIGNED COMMENT \"Transaction state\",`flags` INT UNSIGNED COMMENT \"Transaction flags\",`c_ops` INT UNSIGNED COMMENT \"No of oper"
"",
"ations in transaction\",`outstanding` INT UNSIGNED COMMENT \"Currently outstanding request\",`timer` INT UNSIGNED COMMENT \"Timer (seconds)\") COMMENT=\"transactions\" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$operations\n "
"",
"SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$operations`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$operations` (`node_id` INT UNSIGNED COMMENT \"node id\",`block_instance` INT UNSIGNED COMMENT \"LQH instance no\",`objid` INT UNSIGNED COMMENT \"Object id of operation object\",`tcref` INT UNSIGNED COMMENT \"TC reference\",`apiref` INT UNSIGNED COMMENT \"API reference\",`transid0` INT UNSIGNED COMMENT \"Transaction id\",`transid1` INT UNSIGNED COMMENT \"Transaction id\",`tableid` INT UNSIGNED COMMENT \"Table id\",`fragmentid` INT UNSIGNED COMMENT \"Fragment id\",`op` IN"
"",
"T UNSIGNED COMMENT \"Operation type\",`state` INT UNSIGNED COMMENT \"Operation state\",`flags` INT UNSIGNED COMMENT \"Operation flags\") COMMENT=\"operations\" ENGINE=NDBINFO','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.blocks\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`blocks` (block_number INT UNSIGNED PRIMARY KEY, block_name VARCHAR(512))','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'INSERT INTO `ndbinfo`.`blocks` VALUES (254, \"CMVMI\"), (248, \"DBACC\"), (250, \"DBDICT\"), (246, \"DBDIH\"), (247, \"DBLQH\"), (245, \"DBTC\"), (249, \"DBTUP\"), (253, \"NDBFS\"), (251, \"NDBCNTR\"), (252, \"QMGR\"), (255, \"TRIX\"), (244, \"BACKUP\"), (256, \"DBUTIL\"), (257, \"SUMA\"), (258, \"DBTUX\"), (259, \"TSMAN\"), (260, \"LGMAN\"), (261, \"PGMAN\"), (262, \"RESTORE\"), (263, \"DBINFO\"), (264, \"DBSPJ\"), (265, \"THRMAN\"), (266, \"TRPMAN\")','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.config_params\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`config_params` (param_number INT UNSIGNED PRIMARY KEY, param_name VARCHAR(512))','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'INSERT INTO `ndbinfo`.`config_params` VALUES (179, \"MaxNoOfSubscriptions\"), (180, \"MaxNoOfSubscribers\"), (181, \"MaxNoOfConcurrentSubOperations\"), (5, \"HostName\"), (3, \"NodeId\"), (101, \"NoOfReplicas\"), (103, \"MaxNoOfAttributes\"), (102, \"MaxNoOfTables\"), (149, \"MaxNoOfOrderedIndexes\"), (150, \"MaxNoOfUniqueHashIndexes\"), (110, \"MaxNoOfConcurrentIndexOperations\"), (105, \"MaxNoOfTriggers\"), (109, \"MaxNoOfFiredTriggers\"), (100, \"MaxNoOfSavedMessages\"), (177, \"LockExecuteThreadToCPU\"), "
"",
"(178, \"LockMaintThreadsToCPU\"), (176, \"RealtimeScheduler\"), (114, \"LockPagesInMainMemory\"), (123, \"TimeBetweenWatchDogCheck\"), (174, \"SchedulerExecutionTimer\"), (175, \"SchedulerSpinTimer\"), (141, \"TimeBetweenWatchDogCheckInitial\"), (124, \"StopOnError\"), (107, \"MaxNoOfConcurrentOperations\"), (627, \"MaxDMLOperationsPerTransaction\"), (151, \"MaxNoOfLocalOperations\"), (152, \"MaxNoOfLocalScans\"), (153, \"BatchSizePerLocalScan\"), (106, \"MaxNoOfConcurrentTransactions\"), (108, \"MaxNoOfConcurrentScans\"), (111, \"Trans"
"",
"actionBufferMemory\"), (113, \"IndexMemory\"), (112, \"DataMemory\"), (154, \"UndoIndexBuffer\"), (155, \"UndoDataBuffer\"), (156, \"RedoBuffer\"), (157, \"LongMessageBuffer\"), (160, \"DiskPageBufferMemory\"), (198, \"SharedGlobalMemory\"), (115, \"StartPartialTimeout\"), (116, \"StartPartitionedTimeout\"), (117, \"StartFailureTimeout\"), (619, \"StartNoNodegroupTimeout\"), (118, \"HeartbeatIntervalDbDb\"), (618, \"ConnectCheckIntervalDelay\"), (119, \"HeartbeatIntervalDbApi\"), (120, \"TimeBetweenLocalCheckpoints\"), (121, \"TimeBetweenG"
"",
"lobalCheckpoints\"), (170, \"TimeBetweenEpochs\"), (171, \"TimeBetweenEpochsTimeout\"), (182, \"MaxBufferedEpochs\"), (126, \"NoOfFragmentLogFiles\"), (140, \"FragmentLogFileSize\"), (189, \"InitFragmentLogFiles\"), (190, \"DiskIOThreadPool\"), (159, \"MaxNoOfOpenFiles\"), (162, \"InitialNoOfOpenFiles\"), (129, \"TimeBetweenInactiveTransactionAbortCheck\"), (130, \"TransactionInactiveTimeout\"), (131, \"TransactionDeadlockDetectionTimeout\"), (148, \"Diskless\"), (122, \"ArbitrationTimeout\"), (142, \"Arbitration\"), (7, \"DataDir\"), (12"
"",
"5, \"FileSystemPath\"), (250, \"LogLevelStartup\"), (251, \"LogLevelShutdown\"), (252, \"LogLevelStatistic\"), (253, \"LogLevelCheckpoint\"), (254, \"LogLevelNodeRestart\"), (255, \"LogLevelConnection\"), (259, \"LogLevelCongestion\"), (258, \"LogLevelError\"), (256, \"LogLevelInfo\"), (158, \"BackupDataDir\"), (163, \"DiskSyncSize\"), (164, \"DiskCheckpointSpeed\"), (165, \"DiskCheckpointSpeedInRestart\"), (133, \"BackupMemory\"), (134, \"BackupDataBufferSize\"), (135, \"BackupLogBufferSize\"), (136, \"BackupWriteSize\"), (139, \"BackupMaxWr"
"",
"iteSize\"), (161, \"StringMemory\"), (169, \"MaxAllocate\"), (166, \"MemReportFrequency\"), (167, \"BackupReportFrequency\"), (184, \"StartupStatusReportFrequency\"), (168, \"ODirect\"), (172, \"CompressedBackup\"), (173, \"CompressedLCP\"), (9, \"TotalSendBufferMemory\"), (202, \"ReservedSendBufferMemory\"), (185, \"Nodegroup\"), (186, \"MaxNoOfExecutionThreads\"), (188, \"__ndbmt_lqh_workers\"), (187, \"__ndbmt_lqh_threads\"), (191, \"__ndbmt_classic\"), (628, \"ThreadConfig\"), (193, \"FileSystemPathDD\"), (194, \"FileSystemPathDataFiles\""
"",
"), (195, \"FileSystemPathUndoFiles\"), (196, \"InitialLogfileGroup\"), (197, \"InitialTablespace\"), (605, \"MaxLCPStartDelay\"), (606, \"BuildIndexThreads\"), (607, \"HeartbeatOrder\"), (608, \"DictTrace\"), (609, \"MaxStartFailRetries\"), (610, \"StartFailRetryDelay\"), (613, \"EventLogBufferSize\"), (614, \"Numa\"), (611, \"RedoOverCommitLimit\"), (612, \"RedoOverCommitCounter\"), (615, \"LateAlloc\"), (616, \"TwoPassInitialNodeRestartCopy\"), (617, \"MaxParallelScansPerFragment\"), (620, \"IndexStatAutoCreate\"), (621, \"IndexStatAutoUp"
"",
"date\"), (622, \"IndexStatSaveSize\"), (623, \"IndexStatSaveScale\"), (624, \"IndexStatTriggerPct\"), (625, \"IndexStatTriggerScale\"), (626, \"IndexStatUpdateDelay\"), (629, \"CrashOnCorruptedTuple\"), (630, \"MinFreePct\")','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$dbtc_apiconnect_state\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$dbtc_apiconnect_state` (state_int_value  INT UNSIGNED PRIMARY KEY, state_name VARCHAR(256), state_friendly_name VARCHAR(256), state_description VARCHAR(256))','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'INSERT INTO `ndbinfo`.`ndb$dbtc_apiconnect_state` VALUES (0, \"CS_CONNECTED\", \"Connected\", \"An allocated idle transaction object\"), (1, \"CS_DISCONNECTED\", \"Disconnected\", \"An unallocated connection object\"), (2, \"CS_STARTED\", \"Started\", \"A started transaction\"), (3, \"CS_RECEIVING\", \"Receiving\", \"A transaction receiving operations\"), (7, \"CS_RESTART\", \"\", \"\"), (8, \"CS_ABORTING\", \"Aborting\", \"A transaction aborting\"), (9, \"CS_COMPLETING\", \"Completing\", \"A transaction completing\"), ("
"",
"10, \"CS_COMPLETE_SENT\", \"Completing\", \"A transaction completing\"), (11, \"CS_PREPARE_TO_COMMIT\", \"\", \"\"), (12, \"CS_COMMIT_SENT\", \"Committing\", \"A transaction committing\"), (13, \"CS_START_COMMITTING\", \"\", \"\"), (14, \"CS_COMMITTING\", \"Committing\", \"A transaction committing\"), (15, \"CS_REC_COMMITTING\", \"\", \"\"), (16, \"CS_WAIT_ABORT_CONF\", \"Aborting\", \"\"), (17, \"CS_WAIT_COMPLETE_CONF\", \"Completing\", \"\"), (18, \"CS_WAIT_COMMIT_CONF\", \"Committing\", \"\"), (19, \"CS_FAIL_ABORTING\", \"TakeOverAborting\", \"\"), (20, \"CS_FAIL"
"",
"_ABORTED\", \"TakeOverAborting\", \"\"), (21, \"CS_FAIL_PREPARED\", \"\", \"\"), (22, \"CS_FAIL_COMMITTING\", \"TakeOverCommitting\", \"\"), (23, \"CS_FAIL_COMMITTED\", \"TakeOverCommitting\", \"\"), (24, \"CS_FAIL_COMPLETED\", \"TakeOverCompleting\", \"\"), (25, \"CS_START_SCAN\", \"Scanning\", \"\"), (26, \"CS_SEND_FIRE_TRIG_REQ\", \"Precomitting\", \"\"), (27, \"CS_WAIT_FIRE_TRIG_REQ\", \"Precomitting\", \"\")','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.ndb$dblqh_tcconnect_state\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$dblqh_tcconnect_state` (state_int_value  INT UNSIGNED PRIMARY KEY, state_name VARCHAR(256), state_friendly_name VARCHAR(256), state_description VARCHAR(256))','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"SET @str=IF(@have_ndbinfo,'INSERT INTO `ndbinfo`.`ndb$dblqh_tcconnect_state` VALUES (0, \"IDLE\", \"Idle\", \"\"), (1, \"WAIT_ACC\", \"WaitLock\", \"\"), (2, \"WAIT_TUPKEYINFO\", \"\", \"\"), (3, \"WAIT_ATTR\", \"WaitData\", \"\"), (4, \"WAIT_TUP\", \"WaitTup\", \"\"), (5, \"STOPPED\", \"Stopped\", \"\"), (6, \"LOG_QUEUED\", \"LogPrepare\", \"\"), (7, \"PREPARED\", \"Prepared\", \"\"), (8, \"LOG_COMMIT_WRITTEN_WAIT_SIGNAL\", \"\", \"\"), (9, \"LOG_COMMIT_QUEUED_WAIT_SIGNAL\", \"\", \"\"), (10, \"COMMIT_STOPPED\", \"CommittingStopped\", \"\"), (11, \"LOG_COMMIT_QUEUED\", \"C"
"",
"ommitting\", \"\"), (12, \"COMMIT_QUEUED\", \"Committing\", \"\"), (13, \"COMMITTED\", \"Committed\", \"\"), (35, \"WAIT_TUP_COMMIT\", \"Committing\", \"\"), (14, \"WAIT_ACC_ABORT\", \"Aborting\", \"\"), (15, \"ABORT_QUEUED\", \"Aborting\", \"\"), (16, \"ABORT_STOPPED\", \"AbortingStopped\", \"\"), (17, \"WAIT_AI_AFTER_ABORT\", \"Aborting\", \"\"), (18, \"LOG_ABORT_QUEUED\", \"Aborting\", \"\"), (19, \"WAIT_TUP_TO_ABORT\", \"Aborting\", \"\"), (20, \"WAIT_SCAN_AI\", \"Scanning\", \"\"), (21, \"SCAN_STATE_USED\", \"Scanning\", \"\"), (22, \"SCAN_FIRST_STOPPED\", \"Scanning\", \"\""
"",
"), (23, \"SCAN_CHECK_STOPPED\", \"Scanning\", \"\"), (24, \"SCAN_STOPPED\", \"ScanningStopped\", \"\"), (25, \"SCAN_RELEASE_STOPPED\", \"ScanningStopped\", \"\"), (26, \"SCAN_CLOSE_STOPPED\", \"ScanningStopped\", \"\"), (27, \"COPY_CLOSE_STOPPED\", \"ScanningStopped\", \"\"), (28, \"COPY_FIRST_STOPPED\", \"ScanningStopped\", \"\"), (29, \"COPY_STOPPED\", \"ScanningStopped\", \"\"), (30, \"SCAN_TUPKEY\", \"Scanning\", \"\"), (31, \"COPY_TUPKEY\", \"NodeRecoveryScanning\", \"\"), (32, \"TC_NOT_CONNECTED\", \"Idle\", \"\"), (33, \"PREPARED_RECEIVED_COMMIT\", \"Committing"
"",
"\", \"\"), (34, \"LOG_COMMIT_WRITTEN\", \"Committing\", \"\")','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.transporters\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`transporters` AS SELECT node_id, remote_node_id,  CASE connection_status  WHEN 0 THEN \"CONNECTED\"  WHEN 1 THEN \"CONNECTING\"  WHEN 2 THEN \"DISCONNECTED\"  WHEN 3 THEN \"DISCONNECTING\"  ELSE NULL  END AS status FROM `ndbinfo`.`ndb$transporters`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.logspaces\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`logspaces` AS SELECT node_id,  CASE log_type  WHEN 0 THEN \"REDO\"  WHEN 1 THEN \"DD-UNDO\"  ELSE NULL  END AS log_type, log_id, log_part, total, used FROM `ndbinfo`.`ndb$logspaces`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.logbuffers\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`logbuffers` AS SELECT node_id,  CASE log_type  WHEN 0 THEN \"REDO\"  WHEN 1 THEN \"DD-UNDO\"  ELSE \"<unknown>\"  END AS log_type, log_id, log_part, total, used FROM `ndbinfo`.`ndb$logbuffers`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.resources\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`resources` AS SELECT node_id,  CASE resource_id  WHEN 0 THEN \"RESERVED\"  WHEN 1 THEN \"DISK_OPERATIONS\"  WHEN 2 THEN \"DISK_RECORDS\"  WHEN 3 THEN \"DATA_MEMORY\"  WHEN 4 THEN \"JOBBUFFER\"  WHEN 5 THEN \"FILE_BUFFERS\"  WHEN 6 THEN \"TRANSPORTER_BUFFERS\"  WHEN 7 THEN \"DISK_PAGE_BUFFER\"  WHEN 8 THEN \"QUERY_MEMORY\"  WHEN 9 THEN \"SCHEMA_TRANS_MEMORY\"  ELSE \"<unknown>\"  END AS resource_name, reserved, used, max FR"
"",
"OM `ndbinfo`.`ndb$resources`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.counters\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`counters` AS SELECT node_id, b.block_name, block_instance, counter_id, CASE counter_id  WHEN 1 THEN \"ATTRINFO\"  WHEN 2 THEN \"TRANSACTIONS\"  WHEN 3 THEN \"COMMITS\"  WHEN 4 THEN \"READS\"  WHEN 5 THEN \"SIMPLE_READS\"  WHEN 6 THEN \"WRITES\"  WHEN 7 THEN \"ABORTS\"  WHEN 8 THEN \"TABLE_SCANS\"  WHEN 9 THEN \"RANGE_SCANS\"  WHEN 10 THEN \"OPERATIONS\"  WHEN 11 THEN \"READS_RECEIVED\"  WHEN 12 THEN \"LOCAL_READS_SENT\"  WHE"
"",
"N 13 THEN \"REMOTE_READS_SENT\"  WHEN 14 THEN \"READS_NOT_FOUND\"  WHEN 15 THEN \"TABLE_SCANS_RECEIVED\"  WHEN 16 THEN \"LOCAL_TABLE_SCANS_SENT\"  WHEN 17 THEN \"RANGE_SCANS_RECEIVED\"  WHEN 18 THEN \"LOCAL_RANGE_SCANS_SENT\"  WHEN 19 THEN \"REMOTE_RANGE_SCANS_SENT\"  WHEN 20 THEN \"SCAN_BATCHES_RETURNED\"  WHEN 21 THEN \"SCAN_ROWS_RETURNED\"  WHEN 22 THEN \"PRUNED_RANGE_SCANS_RECEIVED\"  WHEN 23 THEN \"CONST_PRUNED_RANGE_SCANS_RECEIVED\"  WHEN 24 THEN \"LOCAL_READS\"  WHEN 25 THEN \"LOCAL_WRITES\"  ELSE \"<unknown>\"  END AS counter"
"",
"_name, val FROM `ndbinfo`.`ndb$counters` c LEFT JOIN `ndbinfo`.blocks b ON c.block_number = b.block_number','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.nodes\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`nodes` AS SELECT node_id, uptime, CASE status  WHEN 0 THEN \"NOTHING\"  WHEN 1 THEN \"CMVMI\"  WHEN 2 THEN \"STARTING\"  WHEN 3 THEN \"STARTED\"  WHEN 4 THEN \"SINGLEUSER\"  WHEN 5 THEN \"STOPPING_1\"  WHEN 6 THEN \"STOPPING_2\"  WHEN 7 THEN \"STOPPING_3\"  WHEN 8 THEN \"STOPPING_4\"  ELSE \"<unknown>\"  END AS status, start_phase, config_generation FROM `ndbinfo`.`ndb$nodes`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.memoryusage\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`memoryusage` AS SELECT node_id,  pool_name AS memory_type,  SUM(used*entry_size) AS used,  SUM(used) AS used_pages,  SUM(total*entry_size) AS total,  SUM(total) AS total_pages FROM `ndbinfo`.`ndb$pools` WHERE block_number IN (248, 254) AND   (pool_name = \"Index memory\" OR pool_name = \"Data memory\") GROUP BY node_id, memory_type','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.diskpagebuffer\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`diskpagebuffer` AS SELECT node_id, block_instance, pages_written, pages_written_lcp, pages_read, log_waits, page_requests_direct_return, page_requests_wait_queue, page_requests_wait_io FROM `ndbinfo`.`ndb$diskpagebuffer`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.diskpagebuffer\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`diskpagebuffer` AS SELECT node_id, block_instance, pages_written, pages_written_lcp, pages_read, log_waits, page_requests_direct_return, page_requests_wait_queue, page_requests_wait_io FROM `ndbinfo`.`ndb$diskpagebuffer`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.threadblocks\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`threadblocks` AS SELECT t.node_id, t.thr_no, b.block_name, t.block_instance FROM `ndbinfo`.`ndb$threadblocks` t LEFT JOIN `ndbinfo`.blocks b ON t.block_number = b.block_number','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.threadstat\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`threadstat` AS SELECT * from `ndbinfo`.`ndb$threadstat`','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.cluster_transactions\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`cluster_transactions` AS SELECT t.node_id, t.block_instance, t.transid0 + (t.transid1 << 32) as transid, s.state_friendly_name as state,  t.c_ops as count_operations,  t.outstanding as outstanding_operations,  t.timer as inactive_seconds,  (t.apiref & 65535) as client_node_id,  (t.apiref >> 16) as client_block_ref FROM `ndbinfo`.`ndb$transactions` t LEFT JOIN `ndbinfo`.`ndb$dbtc_apiconnect_state` s   "
"",
"     ON s.state_int_value = t.state','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.server_transactions\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`server_transactions` AS SELECT map.mysql_connection_id, t.*FROM information_schema.ndb_transid_mysql_connection_map map JOIN `ndbinfo`.cluster_transactions t   ON (map.ndb_transid >> 32) = (t.transid >> 32)','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.cluster_operations\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`cluster_operations` AS SELECT o.node_id, o.block_instance, o.transid0 + (o.transid1 << 32) as transid, case o.op  when 1 then \"READ\" when 2 then \"READ-SH\" when 3 then \"READ-EX\" when 4 then \"INSERT\" when 5 then \"UPDATE\" when 6 then \"DELETE\" when 7 then \"WRITE\" when 8 then \"UNLOCK\" when 9 then \"REFRESH\" when 257 then \"SCAN\" when 258 then \"SCAN-SH\" when 259 then \"SCAN-EX\" ELSE \"<unknown>\" END as operatio"
"",
"n_type,  s.state_friendly_name as state,  o.tableid,  o.fragmentid,  (o.apiref & 65535) as client_node_id,  (o.apiref >> 16) as client_block_ref,  (o.tcref & 65535) as tc_node_id,  ((o.tcref >> 16) & 511) as tc_block_no,  ((o.tcref >> (16 + 9)) & 127) as tc_block_instance FROM `ndbinfo`.`ndb$operations` o LEFT JOIN `ndbinfo`.`ndb$dblqh_tcconnect_state` s        ON s.state_int_value = o.state','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# ndbinfo.server_operations\n "
"",
"SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`server_operations` AS SELECT map.mysql_connection_id, o.* FROM `ndbinfo`.cluster_operations o JOIN information_schema.ndb_transid_mysql_connection_map map  ON (map.ndb_transid >> 32) = (o.transid >> 32)','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"# Finally turn off offline mode\n "
"",
"SET @str=IF(@have_ndbinfo,'SET @@global.ndbinfo_offline=FALSE','SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"-- Copyright (c) 2003, 2011, Oracle and/or its affiliates. All rights reserved.\n "
"",
"--\n "
"",
"-- This program is free software; you can redistribute it and/or modify\n "
"",
"-- it under the terms of the GNU General Public License as published by\n "
"",
"-- the Free Software Foundation; version 2 of the License.\n "
"",
"--\n "
"",
"-- This program is distributed in the hope that it will be useful,\n "
"",
"-- but WITHOUT ANY WARRANTY; without even the implied warranty of\n "
"",
"-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n "
"",
"-- GNU General Public License for more details.\n "
"",
"--\n "
"",
"-- You should have received a copy of the GNU General Public License\n "
"",
"-- along with this program; if not, write to the Free Software\n "
"",
"-- Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA\n "
"",
"\n "
"",
"# This part converts any old privilege tables to privilege tables suitable\n "
"",
"# for current version of MySQL\n "
"",
"\n "
"",
"# You can safely ignore all 'Duplicate column' and 'Unknown column' errors\n "
"",
"# because these just mean that your tables are already up to date.\n "
"",
"# This script is safe to run even if your tables are already up to date!\n "
"",
"\n "
"",
"set sql_mode='';\n "
"",
"set storage_engine=MyISAM;\n "
"",
"\n "
"",
"ALTER TABLE user add File_priv enum('N','Y') COLLATE utf8_general_ci NOT NULL;\n "
"",
"\n "
"",
"# Detect whether or not we had the Grant_priv column\n "
"",
"SET @hadGrantPriv:=0;\n "
"",
"SELECT @hadGrantPriv:=1 FROM user WHERE Grant_priv LIKE '%';\n "
"",
"\n "
"",
"ALTER TABLE user add Grant_priv enum('N','Y') COLLATE utf8_general_ci NOT NULL,add References_priv enum('N','Y') COLLATE utf8_general_ci NOT NULL,add Index_priv enum('N','Y') COLLATE utf8_general_ci NOT NULL,add Alter_priv enum('N','Y') COLLATE utf8_general_ci NOT NULL;\n "
"",
"ALTER TABLE host add Grant_priv enum('N','Y') NOT NULL,add References_priv enum('N','Y') COLLATE utf8_general_ci NOT NULL,add Index_priv enum('N','Y') COLLATE utf8_general_ci NOT NULL,add Alter_priv enum('N','Y') COLLATE utf8_general_ci NOT NULL;\n "
"",
"ALTER TABLE db add Grant_priv enum('N','Y') COLLATE utf8_general_ci NOT NULL,add References_priv enum('N','Y') COLLATE utf8_general_ci NOT NULL,add Index_priv enum('N','Y') COLLATE utf8_general_ci NOT NULL,add Alter_priv enum('N','Y') COLLATE utf8_general_ci NOT NULL;\n "
"",
"\n "
"",
"# Fix privileges for old tables\n "
"",
"UPDATE user SET Grant_priv=File_priv,References_priv=Create_priv,Index_priv=Create_priv,Alter_priv=Create_priv WHERE @hadGrantPriv = 0;\n "
"",
"UPDATE db SET References_priv=Create_priv,Index_priv=Create_priv,Alter_priv=Create_priv WHERE @hadGrantPriv = 0;\n "
"",
"UPDATE host SET References_priv=Create_priv,Index_priv=Create_priv,Alter_priv=Create_priv WHERE @hadGrantPriv = 0;\n "
"",
"\n "
"",
"#\n "
"",
"# The second alter changes ssl_type to new 4.0.2 format\n "
"",
"# Adding columns needed by GRANT .. REQUIRE (openssl)\n "
"",
"\n "
"",
"ALTER TABLE user\n "
"",
"ADD ssl_type enum('','ANY','X509', 'SPECIFIED') COLLATE utf8_general_ci NOT NULL,\n "
"",
"ADD ssl_cipher BLOB NOT NULL,\n "
"",
"ADD x509_issuer BLOB NOT NULL,\n "
"",
"ADD x509_subject BLOB NOT NULL;\n "
"",
"ALTER TABLE user MODIFY ssl_type enum('','ANY','X509', 'SPECIFIED') NOT NULL;\n "
"",
"\n "
"",
"#\n "
"",
"# tables_priv\n "
"",
"#\n "
"",
"ALTER TABLE tables_priv\n "
"",
"  ADD KEY Grantor (Grantor);\n "
"",
"\n "
"",
"ALTER TABLE tables_priv\n "
"",
"  MODIFY Host char(60) NOT NULL default '',\n "
"",
"  MODIFY Db char(64) NOT NULL default '',\n "
"",
"  MODIFY User char(16) NOT NULL default '',\n "
"",
"  MODIFY Table_name char(64) NOT NULL default '',\n "
"",
"  MODIFY Grantor char(77) NOT NULL default '',\n "
"",
"  ENGINE=MyISAM,\n "
"",
"  CONVERT TO CHARACTER SET utf8 COLLATE utf8_bin;\n "
"",
"\n "
"",
"ALTER TABLE tables_priv\n "
"",
"  MODIFY Column_priv set('Select','Insert','Update','References')\n "
"",
"    COLLATE utf8_general_ci DEFAULT '' NOT NULL,\n "
"",
"  MODIFY Table_priv set('Select','Insert','Update','Delete','Create',\n "
"",
"                        'Drop','Grant','References','Index','Alter',\n "
"",
"                        'Create View','Show view','Trigger')\n "
"",
"    COLLATE utf8_general_ci DEFAULT '' NOT NULL,\n "
"",
"  COMMENT='Table privileges';\n "
"",
"\n "
"",
"#\n "
"",
"# columns_priv\n "
"",
"#\n "
"",
"#\n "
"",
"# Name change of Type -> Column_priv from MySQL 3.22.12\n "
"",
"#\n "
"",
"ALTER TABLE columns_priv\n "
"",
"  CHANGE Type Column_priv set('Select','Insert','Update','References')\n "
"",
"    COLLATE utf8_general_ci DEFAULT '' NOT NULL;\n "
"",
"\n "
"",
"ALTER TABLE columns_priv\n "
"",
"  MODIFY Host char(60) NOT NULL default '',\n "
"",
"  MODIFY Db char(64) NOT NULL default '',\n "
"",
"  MODIFY User char(16) NOT NULL default '',\n "
"",
"  MODIFY Table_name char(64) NOT NULL default '',\n "
"",
"  MODIFY Column_name char(64) NOT NULL default '',\n "
"",
"  ENGINE=MyISAM,\n "
"",
"  CONVERT TO CHARACTER SET utf8 COLLATE utf8_bin,\n "
"",
"  COMMENT='Column privileges';\n "
"",
"\n "
"",
"ALTER TABLE columns_priv\n "
"",
"  MODIFY Column_priv set('Select','Insert','Update','References')\n "
"",
"    COLLATE utf8_general_ci DEFAULT '' NOT NULL;\n "
"",
"\n "
"",
"#\n "
"",
"#  Add the new 'type' column to the func table.\n "
"",
"#\n "
"",
"\n "
"",
"ALTER TABLE func add type enum ('function','aggregate') COLLATE utf8_general_ci NOT NULL;\n "
"",
"\n "
"",
"#\n "
"",
"#  Change the user,db and host tables to current format\n "
"",
"#\n "
"",
"\n "
"",
"# Detect whether we had Show_db_priv\n "
"",
"SET @hadShowDbPriv:=0;\n "
"",
"SELECT @hadShowDbPriv:=1 FROM user WHERE Show_db_priv LIKE '%';\n "
"",
"\n "
"",
"ALTER TABLE user\n "
"",
"ADD Show_db_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Alter_priv,\n "
"",
"ADD Super_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Show_db_priv,\n "
"",
"ADD Create_tmp_table_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Super_priv,\n "
"",
"ADD Lock_tables_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Create_tmp_table_priv,\n "
"",
"ADD Execute_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Lock_tables_priv,\n "
"",
"ADD Repl_slave_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Execute_priv,\n "
"",
"ADD Repl_client_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Repl_slave_priv;\n "
"",
"\n "
"",
"# Convert privileges so that users have similar privileges as before\n "
"",
"\n "
"",
"UPDATE user SET Show_db_priv= Select_priv, Super_priv=Process_priv, Execute_priv=Process_priv, Create_tmp_table_priv='Y', Lock_tables_priv='Y', Repl_slave_priv=file_priv, Repl_client_priv=File_priv where user<>\"\" AND @hadShowDbPriv = 0;\n "
"",
"\n "
"",
"\n "
"",
"#  Add fields that can be used to limit number of questions and connections\n "
"",
"#  for some users.\n "
"",
"\n "
"",
"ALTER TABLE user\n "
"",
"ADD max_questions int(11) NOT NULL DEFAULT 0 AFTER x509_subject,\n "
"",
"ADD max_updates   int(11) unsigned NOT NULL DEFAULT 0 AFTER max_questions,\n "
"",
"ADD max_connections int(11) unsigned NOT NULL DEFAULT 0 AFTER max_updates;\n "
"",
"\n "
"",
"\n "
"",
"#\n "
"",
"#  Add Create_tmp_table_priv and Lock_tables_priv to db and host\n "
"",
"#\n "
"",
"\n "
"",
"ALTER TABLE db\n "
"",
"ADD Create_tmp_table_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"ADD Lock_tables_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL;\n "
"",
"ALTER TABLE host\n "
"",
"ADD Create_tmp_table_priv enum('N','Y') DEFAULT 'N' NOT NULL,\n "
"",
"ADD Lock_tables_priv enum('N','Y') DEFAULT 'N' NOT NULL;\n "
"",
"\n "
"",
"alter table user change max_questions max_questions int(11) unsigned DEFAULT 0  NOT NULL;\n "
"",
"\n "
"",
"\n "
"",
"alter table db comment='Database privileges';\n "
"",
"alter table host comment='Host privileges;  Merged with database privileges';\n "
"",
"alter table user comment='Users and global privileges';\n "
"",
"alter table func comment='User defined functions';\n "
"",
"\n "
"",
"# Convert all tables to UTF-8 with binary collation\n "
"",
"# and reset all char columns to correct width\n "
"",
"ALTER TABLE user\n "
"",
"  MODIFY Host char(60) NOT NULL default '',\n "
"",
"  MODIFY User char(16) NOT NULL default '',\n "
"",
"  ENGINE=MyISAM, CONVERT TO CHARACTER SET utf8 COLLATE utf8_bin;\n "
"",
"ALTER TABLE user\n "
"",
"  MODIFY Password char(41) character set latin1 collate latin1_bin NOT NULL default '',\n "
"",
"  MODIFY Select_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Insert_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Update_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Delete_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Create_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Drop_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Reload_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Shutdown_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Process_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY File_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Grant_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY References_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Index_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Alter_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Show_db_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Super_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Create_tmp_table_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Lock_tables_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Execute_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Repl_slave_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Repl_client_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY ssl_type enum('','ANY','X509', 'SPECIFIED') COLLATE utf8_general_ci DEFAULT '' NOT NULL;\n "
"",
"\n "
"",
"ALTER TABLE db\n "
"",
"  MODIFY Host char(60) NOT NULL default '',\n "
"",
"  MODIFY Db char(64) NOT NULL default '',\n "
"",
"  MODIFY User char(16) NOT NULL default '',\n "
"",
"  ENGINE=MyISAM, CONVERT TO CHARACTER SET utf8 COLLATE utf8_bin;\n "
"",
"ALTER TABLE db\n "
"",
"  MODIFY  Select_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY  Insert_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY  Update_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY  Delete_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY  Create_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY  Drop_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY  Grant_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY  References_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY  Index_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY  Alter_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY  Create_tmp_table_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY  Lock_tables_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL;\n "
"",
"\n "
"",
"ALTER TABLE host\n "
"",
"  MODIFY Host char(60) NOT NULL default '',\n "
"",
"  MODIFY Db char(64) NOT NULL default '',\n "
"",
"  ENGINE=MyISAM, CONVERT TO CHARACTER SET utf8 COLLATE utf8_bin;\n "
"",
"ALTER TABLE host\n "
"",
"  MODIFY Select_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Insert_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Update_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Delete_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Create_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Drop_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Grant_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY References_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Index_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Alter_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Create_tmp_table_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL,\n "
"",
"  MODIFY Lock_tables_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL;\n "
"",
"\n "
"",
"ALTER TABLE func\n "
"",
"  ENGINE=MyISAM, CONVERT TO CHARACTER SET utf8 COLLATE utf8_bin;\n "
"",
"ALTER TABLE func\n "
"",
"  MODIFY type enum ('function','aggregate') COLLATE utf8_general_ci NOT NULL;\n "
"",
"\n "
"",
"#\n "
"",
"# Modify log tables.\n "
"",
"#\n "
"",
"\n "
"",
"SET @old_log_state = @@global.general_log;\n "
"",
"SET GLOBAL general_log = 'OFF';\n "
"",
"ALTER TABLE general_log\n "
"",
"  MODIFY event_time TIMESTAMP NOT NULL,\n "
"",
"  MODIFY user_host MEDIUMTEXT NOT NULL,\n "
"",
"  MODIFY thread_id INTEGER NOT NULL,\n "
"",
"  MODIFY server_id INTEGER UNSIGNED NOT NULL,\n "
"",
"  MODIFY command_type VARCHAR(64) NOT NULL,\n "
"",
"  MODIFY argument MEDIUMTEXT NOT NULL;\n "
"",
"SET GLOBAL general_log = @old_log_state;\n "
"",
"\n "
"",
"SET @old_log_state = @@global.slow_query_log;\n "
"",
"SET GLOBAL slow_query_log = 'OFF';\n "
"",
"ALTER TABLE slow_log\n "
"",
"  MODIFY start_time TIMESTAMP NOT NULL,\n "
"",
"  MODIFY user_host MEDIUMTEXT NOT NULL,\n "
"",
"  MODIFY query_time TIME NOT NULL,\n "
"",
"  MODIFY lock_time TIME NOT NULL,\n "
"",
"  MODIFY rows_sent INTEGER NOT NULL,\n "
"",
"  MODIFY rows_examined INTEGER NOT NULL,\n "
"",
"  MODIFY db VARCHAR(512) NOT NULL,\n "
"",
"  MODIFY last_insert_id INTEGER NOT NULL,\n "
"",
"  MODIFY insert_id INTEGER NOT NULL,\n "
"",
"  MODIFY server_id INTEGER UNSIGNED NOT NULL,\n "
"",
"  MODIFY sql_text MEDIUMTEXT NOT NULL;\n "
"",
"SET GLOBAL slow_query_log = @old_log_state;\n "
"",
"\n "
"",
"ALTER TABLE plugin\n "
"",
"  MODIFY name varchar(64) COLLATE utf8_general_ci NOT NULL DEFAULT '',\n "
"",
"  MODIFY dl varchar(128) COLLATE utf8_general_ci NOT NULL DEFAULT '',\n "
"",
"  CONVERT TO CHARACTER SET utf8 COLLATE utf8_general_ci;\n "
"",
"\n "
"",
"#\n "
"",
"# Detect whether we had Create_view_priv\n "
"",
"#\n "
"",
"SET @hadCreateViewPriv:=0;\n "
"",
"SELECT @hadCreateViewPriv:=1 FROM user WHERE Create_view_priv LIKE '%';\n "
"",
"\n "
"",
"#\n "
"",
"# Create VIEWs privileges (v5.0)\n "
"",
"#\n "
"",
"ALTER TABLE db ADD Create_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Lock_tables_priv;\n "
"",
"ALTER TABLE db MODIFY Create_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Lock_tables_priv;\n "
"",
"\n "
"",
"ALTER TABLE host ADD Create_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Lock_tables_priv;\n "
"",
"ALTER TABLE host MODIFY Create_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Lock_tables_priv;\n "
"",
"\n "
"",
"ALTER TABLE user ADD Create_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Repl_client_priv;\n "
"",
"ALTER TABLE user MODIFY Create_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Repl_client_priv;\n "
"",
"\n "
"",
"#\n "
"",
"# Show VIEWs privileges (v5.0)\n "
"",
"#\n "
"",
"ALTER TABLE db ADD Show_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Create_view_priv;\n "
"",
"ALTER TABLE db MODIFY Show_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Create_view_priv;\n "
"",
"\n "
"",
"ALTER TABLE host ADD Show_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Create_view_priv;\n "
"",
"ALTER TABLE host MODIFY Show_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Create_view_priv;\n "
"",
"\n "
"",
"ALTER TABLE user ADD Show_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Create_view_priv;\n "
"",
"ALTER TABLE user MODIFY Show_view_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Create_view_priv;\n "
"",
"\n "
"",
"#\n "
"",
"# Assign create/show view privileges to people who have create provileges\n "
"",
"#\n "
"",
"UPDATE user SET Create_view_priv=Create_priv, Show_view_priv=Create_priv where user<>\"\" AND @hadCreateViewPriv = 0;\n "
"",
"\n "
"",
"#\n "
"",
"#\n "
"",
"#\n "
"",
"SET @hadCreateRoutinePriv:=0;\n "
"",
"SELECT @hadCreateRoutinePriv:=1 FROM user WHERE Create_routine_priv LIKE '%';\n "
"",
"\n "
"",
"#\n "
"",
"# Create PROCEDUREs privileges (v5.0)\n "
"",
"#\n "
"",
"ALTER TABLE db ADD Create_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Show_view_priv;\n "
"",
"ALTER TABLE db MODIFY Create_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Show_view_priv;\n "
"",
"\n "
"",
"ALTER TABLE host ADD Create_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Show_view_priv;\n "
"",
"ALTER TABLE host MODIFY Create_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Show_view_priv;\n "
"",
"\n "
"",
"ALTER TABLE user ADD Create_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Show_view_priv;\n "
"",
"ALTER TABLE user MODIFY Create_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Show_view_priv;\n "
"",
"\n "
"",
"#\n "
"",
"# Alter PROCEDUREs privileges (v5.0)\n "
"",
"#\n "
"",
"ALTER TABLE db ADD Alter_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Create_routine_priv;\n "
"",
"ALTER TABLE db MODIFY Alter_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Create_routine_priv;\n "
"",
"\n "
"",
"ALTER TABLE host ADD Alter_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Create_routine_priv;\n "
"",
"ALTER TABLE host MODIFY Alter_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Create_routine_priv;\n "
"",
"\n "
"",
"ALTER TABLE user ADD Alter_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Create_routine_priv;\n "
"",
"ALTER TABLE user MODIFY Alter_routine_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Create_routine_priv;\n "
"",
"\n "
"",
"ALTER TABLE db ADD Execute_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Alter_routine_priv;\n "
"",
"ALTER TABLE db MODIFY Execute_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Alter_routine_priv;\n "
"",
"\n "
"",
"ALTER TABLE host ADD Execute_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Alter_routine_priv;\n "
"",
"ALTER TABLE host MODIFY Execute_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Alter_routine_priv;\n "
"",
"\n "
"",
"#\n "
"",
"# Assign create/alter routine privileges to people who have create privileges\n "
"",
"#\n "
"",
"UPDATE user SET Create_routine_priv=Create_priv, Alter_routine_priv=Alter_priv where user<>\"\" AND @hadCreateRoutinePriv = 0;\n "
"",
"UPDATE db SET Create_routine_priv=Create_priv, Alter_routine_priv=Alter_priv, Execute_priv=Select_priv where user<>\"\" AND @hadCreateRoutinePriv = 0;\n "
"",
"UPDATE host SET Create_routine_priv=Create_priv, Alter_routine_priv=Alter_priv, Execute_priv=Select_priv where @hadCreateRoutinePriv = 0;\n "
"",
"\n "
"",
"#\n "
"",
"# Add max_user_connections resource limit\n "
"",
"#\n "
"",
"ALTER TABLE user ADD max_user_connections int(11) unsigned DEFAULT '0' NOT NULL AFTER max_connections;\n "
"",
"\n "
"",
"#\n "
"",
"# user.Create_user_priv\n "
"",
"#\n "
"",
"\n "
"",
"SET @hadCreateUserPriv:=0;\n "
"",
"SELECT @hadCreateUserPriv:=1 FROM user WHERE Create_user_priv LIKE '%';\n "
"",
"\n "
"",
"ALTER TABLE user ADD Create_user_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Alter_routine_priv;\n "
"",
"ALTER TABLE user MODIFY Create_user_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Alter_routine_priv;\n "
"",
"UPDATE user LEFT JOIN db USING (Host,User) SET Create_user_priv='Y'\n "
"",
"  WHERE @hadCreateUserPriv = 0 AND\n "
"",
"        (user.Grant_priv = 'Y' OR db.Grant_priv = 'Y');\n "
"",
"\n "
"",
"#\n "
"",
"# procs_priv\n "
"",
"#\n "
"",
"\n "
"",
"ALTER TABLE procs_priv\n "
"",
"  ENGINE=MyISAM,\n "
"",
"  CONVERT TO CHARACTER SET utf8 COLLATE utf8_bin;\n "
"",
"\n "
"",
"ALTER TABLE procs_priv\n "
"",
"  MODIFY Proc_priv set('Execute','Alter Routine','Grant')\n "
"",
"    COLLATE utf8_general_ci DEFAULT '' NOT NULL;\n "
"",
"\n "
"",
"ALTER IGNORE TABLE procs_priv\n "
"",
"  MODIFY Routine_name char(64)\n "
"",
"    COLLATE utf8_general_ci DEFAULT '' NOT NULL;\n "
"",
"\n "
"",
"ALTER TABLE procs_priv\n "
"",
"  ADD Routine_type enum('FUNCTION','PROCEDURE')\n "
"",
"    COLLATE utf8_general_ci NOT NULL AFTER Routine_name;\n "
"",
"\n "
"",
"ALTER TABLE procs_priv\n "
"",
"  MODIFY Timestamp timestamp AFTER Proc_priv;\n "
"",
"\n "
"",
"#\n "
"",
"# proc\n "
"",
"#\n "
"",
"\n "
"",
"# Correct the name fields to not binary, and expand sql_data_access\n "
"",
"ALTER TABLE proc MODIFY name char(64) DEFAULT '' NOT NULL,\n "
"",
"                 MODIFY specific_name char(64) DEFAULT '' NOT NULL,\n "
"",
"                 MODIFY sql_data_access\n "
"",
"                        enum('CONTAINS_SQL',\n "
"",
"                             'NO_SQL',\n "
"",
"                             'READS_SQL_DATA',\n "
"",
"                             'MODIFIES_SQL_DATA'\n "
"",
"                            ) DEFAULT 'CONTAINS_SQL' NOT NULL,\n "
"",
"                 MODIFY body longblob NOT NULL,\n "
"",
"                 MODIFY returns longblob NOT NULL,\n "
"",
"                 MODIFY sql_mode\n "
"",
"                        set('REAL_AS_FLOAT',\n "
"",
"                            'PIPES_AS_CONCAT',\n "
"",
"                            'ANSI_QUOTES',\n "
"",
"                            'IGNORE_SPACE',\n "
"",
"                            'NOT_USED',\n "
"",
"                            'ONLY_FULL_GROUP_BY',\n "
"",
"                            'NO_UNSIGNED_SUBTRACTION',\n "
"",
"                            'NO_DIR_IN_CREATE',\n "
"",
"                            'POSTGRESQL',\n "
"",
"                            'ORACLE',\n "
"",
"                            'MSSQL',\n "
"",
"                            'DB2',\n "
"",
"                            'MAXDB',\n "
"",
"                            'NO_KEY_OPTIONS',\n "
"",
"                            'NO_TABLE_OPTIONS',\n "
"",
"                            'NO_FIELD_OPTIONS',\n "
"",
"                            'MYSQL323',\n "
"",
"                            'MYSQL40',\n "
"",
"                            'ANSI',\n "
"",
"                            'NO_AUTO_VALUE_ON_ZERO',\n "
"",
"                            'NO_BACKSLASH_ESCAPES',\n "
"",
"                            'STRICT_TRANS_TABLES',\n "
"",
"                            'STRICT_ALL_TABLES',\n "
"",
"                            'NO_ZERO_IN_DATE',\n "
"",
"                            'NO_ZERO_DATE',\n "
"",
"                            'INVALID_DATES',\n "
"",
"                            'ERROR_FOR_DIVISION_BY_ZERO',\n "
"",
"                            'TRADITIONAL',\n "
"",
"                            'NO_AUTO_CREATE_USER',\n "
"",
"                            'HIGH_NOT_PRECEDENCE',\n "
"",
"                            'NO_ENGINE_SUBSTITUTION',\n "
"",
"                            'PAD_CHAR_TO_FULL_LENGTH'\n "
"",
"                            ) DEFAULT '' NOT NULL,\n "
"",
"                 DEFAULT CHARACTER SET utf8;\n "
"",
"\n "
"",
"# Correct the character set and collation\n "
"",
"ALTER TABLE proc CONVERT TO CHARACTER SET utf8;\n "
"",
"# Reset some fields after the conversion\n "
"",
"ALTER TABLE proc  MODIFY db\n "
"",
"                         char(64) collate utf8_bin DEFAULT '' NOT NULL,\n "
"",
"                  MODIFY definer\n "
"",
"                         char(77) collate utf8_bin DEFAULT '' NOT NULL,\n "
"",
"                  MODIFY comment\n "
"",
"                         char(64) collate utf8_bin DEFAULT '' NOT NULL;\n "
"",
"\n "
"",
"ALTER TABLE proc ADD character_set_client\n "
"",
"                     char(32) collate utf8_bin DEFAULT NULL\n "
"",
"                     AFTER comment;\n "
"",
"ALTER TABLE proc MODIFY character_set_client\n "
"",
"                        char(32) collate utf8_bin DEFAULT NULL;\n "
"",
"\n "
"",
"SELECT CASE WHEN COUNT(*) > 0 THEN \n "
"",
"CONCAT (\"WARNING: NULL values of the 'character_set_client' column ('mysql.proc' table) have been updated with a default value (\", @@character_set_client, \"). Please verify if necessary.\")\n "
"",
"ELSE NULL \n "
"",
"END \n "
"",
"AS value FROM proc WHERE character_set_client IS NULL;\n "
"",
"\n "
"",
"UPDATE proc SET character_set_client = @@character_set_client \n "
"",
"                     WHERE character_set_client IS NULL;\n "
"",
"\n "
"",
"ALTER TABLE proc ADD collation_connection\n "
"",
"                     char(32) collate utf8_bin DEFAULT NULL\n "
"",
"                     AFTER character_set_client;\n "
"",
"ALTER TABLE proc MODIFY collation_connection\n "
"",
"                        char(32) collate utf8_bin DEFAULT NULL;\n "
"",
"\n "
"",
"SELECT CASE WHEN COUNT(*) > 0 THEN \n "
"",
"CONCAT (\"WARNING: NULL values of the 'collation_connection' column ('mysql.proc' table) have been updated with a default value (\", @@collation_connection, \"). Please verify if necessary.\")\n "
"",
"ELSE NULL \n "
"",
"END \n "
"",
"AS value FROM proc WHERE collation_connection IS NULL;\n "
"",
"\n "
"",
"UPDATE proc SET collation_connection = @@collation_connection\n "
"",
"                     WHERE collation_connection IS NULL;\n "
"",
"\n "
"",
"ALTER TABLE proc ADD db_collation\n "
"",
"                     char(32) collate utf8_bin DEFAULT NULL\n "
"",
"                     AFTER collation_connection;\n "
"",
"ALTER TABLE proc MODIFY db_collation\n "
"",
"                        char(32) collate utf8_bin DEFAULT NULL;\n "
"",
"\n "
"",
"SELECT CASE WHEN COUNT(*) > 0 THEN \n "
"",
"CONCAT (\"WARNING: NULL values of the 'db_collation' column ('mysql.proc' table) have been updated with default values. Please verify if necessary.\")\n "
"",
"ELSE NULL\n "
"",
"END\n "
"",
"AS value FROM proc WHERE db_collation IS NULL;\n "
"",
"\n "
"",
"UPDATE proc AS p SET db_collation  = \n "
"",
"                     ( SELECT DEFAULT_COLLATION_NAME \n "
"",
"                       FROM INFORMATION_SCHEMA.SCHEMATA \n "
"",
"                       WHERE SCHEMA_NAME = p.db)\n "
"",
"                     WHERE db_collation IS NULL;\n "
"",
"\n "
"",
"ALTER TABLE proc ADD body_utf8 longblob DEFAULT NULL\n "
"",
"                     AFTER db_collation;\n "
"",
"ALTER TABLE proc MODIFY body_utf8 longblob DEFAULT NULL;\n "
"",
"\n "
"",
"# Change comment from char(64) to text\n "
"",
"ALTER TABLE proc MODIFY comment\n "
"",
"                        text collate utf8_bin NOT NULL;\n "
"",
"\n "
"",
"#\n "
"",
"# EVENT privilege\n "
"",
"#\n "
"",
"SET @hadEventPriv := 0;\n "
"",
"SELECT @hadEventPriv :=1 FROM user WHERE Event_priv LIKE '%';\n "
"",
"\n "
"",
"ALTER TABLE user add Event_priv enum('N','Y') character set utf8 DEFAULT 'N' NOT NULL AFTER Create_user_priv;\n "
"",
"ALTER TABLE user MODIFY Event_priv enum('N','Y') character set utf8 DEFAULT 'N' NOT NULL AFTER Create_user_priv;\n "
"",
"\n "
"",
"UPDATE user SET Event_priv=Super_priv WHERE @hadEventPriv = 0;\n "
"",
"\n "
"",
"ALTER TABLE db add Event_priv enum('N','Y') character set utf8 DEFAULT 'N' NOT NULL;\n "
"",
"ALTER TABLE db MODIFY Event_priv enum('N','Y') character set utf8 DEFAULT 'N' NOT NULL;\n "
"",
"\n "
"",
"#\n "
"",
"# EVENT table\n "
"",
"#\n "
"",
"ALTER TABLE event DROP PRIMARY KEY;\n "
"",
"ALTER TABLE event ADD PRIMARY KEY(db, name);\n "
"",
"# Add sql_mode column just in case.\n "
"",
"ALTER TABLE event ADD sql_mode set ('NOT_USED') AFTER on_completion;\n "
"",
"# Update list of sql_mode values.\n "
"",
"ALTER TABLE event MODIFY sql_mode\n "
"",
"                        set('REAL_AS_FLOAT',\n "
"",
"                            'PIPES_AS_CONCAT',\n "
"",
"                            'ANSI_QUOTES',\n "
"",
"                            'IGNORE_SPACE',\n "
"",
"                            'NOT_USED',\n "
"",
"                            'ONLY_FULL_GROUP_BY',\n "
"",
"                            'NO_UNSIGNED_SUBTRACTION',\n "
"",
"                            'NO_DIR_IN_CREATE',\n "
"",
"                            'POSTGRESQL',\n "
"",
"                            'ORACLE',\n "
"",
"                            'MSSQL',\n "
"",
"                            'DB2',\n "
"",
"                            'MAXDB',\n "
"",
"                            'NO_KEY_OPTIONS',\n "
"",
"                            'NO_TABLE_OPTIONS',\n "
"",
"                            'NO_FIELD_OPTIONS',\n "
"",
"                            'MYSQL323',\n "
"",
"                            'MYSQL40',\n "
"",
"                            'ANSI',\n "
"",
"                            'NO_AUTO_VALUE_ON_ZERO',\n "
"",
"                            'NO_BACKSLASH_ESCAPES',\n "
"",
"                            'STRICT_TRANS_TABLES',\n "
"",
"                            'STRICT_ALL_TABLES',\n "
"",
"                            'NO_ZERO_IN_DATE',\n "
"",
"                            'NO_ZERO_DATE',\n "
"",
"                            'INVALID_DATES',\n "
"",
"                            'ERROR_FOR_DIVISION_BY_ZERO',\n "
"",
"                            'TRADITIONAL',\n "
"",
"                            'NO_AUTO_CREATE_USER',\n "
"",
"                            'HIGH_NOT_PRECEDENCE',\n "
"",
"                            'NO_ENGINE_SUBSTITUTION',\n "
"",
"                            'PAD_CHAR_TO_FULL_LENGTH'\n "
"",
"                            ) DEFAULT '' NOT NULL AFTER on_completion;\n "
"",
"ALTER TABLE event MODIFY name char(64) CHARACTER SET utf8 NOT NULL default '';\n "
"",
"\n "
"",
"ALTER TABLE event MODIFY COLUMN originator INT UNSIGNED NOT NULL;\n "
"",
"ALTER TABLE event ADD COLUMN originator INT UNSIGNED NOT NULL AFTER comment;\n "
"",
"\n "
"",
"ALTER TABLE event MODIFY COLUMN status ENUM('ENABLED','DISABLED','SLAVESIDE_DISABLED') NOT NULL default 'ENABLED';\n "
"",
"\n "
"",
"ALTER TABLE event ADD COLUMN time_zone char(64) CHARACTER SET latin1\n "
"",
"        NOT NULL DEFAULT 'SYSTEM' AFTER originator;\n "
"",
"\n "
"",
"ALTER TABLE event ADD character_set_client\n "
"",
"                      char(32) collate utf8_bin DEFAULT NULL\n "
"",
"                      AFTER time_zone;\n "
"",
"ALTER TABLE event MODIFY character_set_client\n "
"",
"                         char(32) collate utf8_bin DEFAULT NULL;\n "
"",
"\n "
"",
"ALTER TABLE event ADD collation_connection\n "
"",
"                      char(32) collate utf8_bin DEFAULT NULL\n "
"",
"                      AFTER character_set_client;\n "
"",
"ALTER TABLE event MODIFY collation_connection\n "
"",
"                         char(32) collate utf8_bin DEFAULT NULL;\n "
"",
"\n "
"",
"ALTER TABLE event ADD db_collation\n "
"",
"                      char(32) collate utf8_bin DEFAULT NULL\n "
"",
"                      AFTER collation_connection;\n "
"",
"ALTER TABLE event MODIFY db_collation\n "
"",
"                         char(32) collate utf8_bin DEFAULT NULL;\n "
"",
"\n "
"",
"ALTER TABLE event ADD body_utf8 longblob DEFAULT NULL\n "
"",
"                      AFTER db_collation;\n "
"",
"ALTER TABLE event MODIFY body_utf8 longblob DEFAULT NULL;\n "
"",
"\n "
"",
"\n "
"",
"#\n "
"",
"# TRIGGER privilege\n "
"",
"#\n "
"",
"\n "
"",
"SET @hadTriggerPriv := 0;\n "
"",
"SELECT @hadTriggerPriv :=1 FROM user WHERE Trigger_priv LIKE '%';\n "
"",
"\n "
"",
"ALTER TABLE user ADD Trigger_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Event_priv;\n "
"",
"ALTER TABLE user MODIFY Trigger_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Event_priv;\n "
"",
"\n "
"",
"ALTER TABLE host ADD Trigger_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL;\n "
"",
"ALTER TABLE host MODIFY Trigger_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL;\n "
"",
"\n "
"",
"ALTER TABLE db ADD Trigger_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL;\n "
"",
"ALTER TABLE db MODIFY Trigger_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL;\n "
"",
"\n "
"",
"UPDATE user SET Trigger_priv=Super_priv WHERE @hadTriggerPriv = 0;\n "
"",
"\n "
"",
"#\n "
"",
"# user.Create_tablespace_priv\n "
"",
"#\n "
"",
"\n "
"",
"SET @hadCreateTablespacePriv := 0;\n "
"",
"SELECT @hadCreateTablespacePriv :=1 FROM user WHERE Create_tablespace_priv LIKE '%';\n "
"",
"\n "
"",
"ALTER TABLE user ADD Create_tablespace_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Trigger_priv;\n "
"",
"ALTER TABLE user MODIFY Create_tablespace_priv enum('N','Y') COLLATE utf8_general_ci DEFAULT 'N' NOT NULL AFTER Trigger_priv;\n "
"",
"\n "
"",
"UPDATE user SET Create_tablespace_priv = Super_priv WHERE @hadCreateTablespacePriv = 0;\n "
"",
"\n "
"",
"--\n "
"",
"-- Unlike 'performance_schema', the 'mysql' database is reserved already,\n "
"",
"-- so no user procedure is supposed to be there.\n "
"",
"--\n "
"",
"-- NOTE: until upgrade is finished, stored routines are not available,\n "
"",
"-- because system tables (e.g. mysql.proc) might be not usable.\n "
"",
"--\n "
"",
"drop procedure if exists mysql.die;\n "
"",
"create procedure mysql.die() signal sqlstate 'HY000' set message_text='Unexpected content found in the performance_schema database.';\n "
"",
"\n "
"",
"--\n "
"",
"-- For broken upgrades, SIGNAL the error\n "
"",
"--\n "
"",
"\n "
"",
"SET @cmd=\"call mysql.die()\";\n "
"",
"\n "
"",
"SET @str = IF(@broken_pfs > 0, @cmd, 'SET @dummy = 0');\n "
"",
"PREPARE stmt FROM @str;\n "
"",
"EXECUTE stmt;\n "
"",
"DROP PREPARE stmt;\n "
"",
"\n "
"",
"drop procedure mysql.die;\n "
"",
"\n "
"",
"ALTER TABLE user ADD plugin char(64) DEFAULT '',  ADD authentication_string TEXT;\n "
"",
"ALTER TABLE user MODIFY plugin char(64) DEFAULT '';\n "
"",
"ALTER TABLE user MODIFY authentication_string TEXT;\n "
"",
"\n "
"",
"-- Need to pre-fill mysql.proxies_priv with access for root even when upgrading from\n "
"",
"-- older versions\n "
"",
"\n "
"",
"CREATE TEMPORARY TABLE tmp_proxies_priv LIKE proxies_priv;\n "
"",
"INSERT INTO tmp_proxies_priv VALUES ('localhost', 'root', '', '', TRUE, '', now());\n "
"",
"INSERT INTO proxies_priv SELECT * FROM tmp_proxies_priv WHERE @had_proxies_priv_table=0;\n "
"",
"DROP TABLE tmp_proxies_priv;\n "
"",
"\n "
"",
"\n "
"",
"#\n "
"",
"# mysql.ndb_binlog_index\n "
"",
"#\n "
"",
"# Change type from BIGINT to INT\n "
"",
"ALTER TABLE ndb_binlog_index\n "
"",
"  MODIFY inserts INT UNSIGNED NOT NULL,\n "
"",
"  MODIFY updates INT UNSIGNED NOT NULL,\n "
"",
"  MODIFY deletes INT UNSIGNED NOT NULL,\n "
"",
"  MODIFY schemaops INT UNSIGNED NOT NULL;\n "
"",
"# Add new columns\n "
"",
"ALTER TABLE ndb_binlog_index\n "
"",
"  ADD orig_server_id INT UNSIGNED NOT NULL,\n "
"",
"  ADD orig_epoch BIGINT UNSIGNED NOT NULL,\n "
"",
"  ADD gci INT UNSIGNED NOT NULL;\n "
"",
"# New primary key\n "
"",
"ALTER TABLE ndb_binlog_index\n "
"",
"  DROP PRIMARY KEY,\n "
"",
"  ADD PRIMARY KEY(epoch, orig_server_id, orig_epoch);\n "
"",
"\n "
"",
"# Activate the new, possible modified privilege tables\n "
"",
"# This should not be needed, but gives us some extra testing that the above\n "
"",
"# changes was correct\n "
"",
"\n "
"",
"flush privileges;\n "
"",
"\n "
"",
"#\n "
"",
"# ndb_binlog_index table\n "
"",
"#\n "
"",
"ALTER TABLE ndb_binlog_index\n "
"",
"  ADD COLUMN next_position BIGINT UNSIGNED NOT NULL;\n "
"",
"ALTER TABLE ndb_binlog_index\n "
"",
"  ADD COLUMN next_file VARCHAR(255) NOT NULL;"
"",
"",
NULL
};
