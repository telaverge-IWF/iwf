
--disable_query_log
--disable_result_log

--source suite/ndb_memcache/include/memcached_wait_for_ready.inc

use ndbmemcache;
let $done = query_get_value (select key_prefix k from key_prefixes where container = 'tt001', k, 1);
if ($done != "tt001:") 
{
                
set default_storage_engine = ndbcluster;

CREATE TABLE tt001 (mkey char(20) not null primary key, sval char(20));
CREATE TABLE tt002 (mkey varchar(32) not null primary key, sval varchar(32));
CREATE TABLE tt003 (mkey year not null primary key, sval year);
CREATE TABLE tt004 (mkey timestamp not null primary key, sval timestamp);
CREATE TABLE tt005 (mkey binary(20) not null primary key, sval binary(20));
CREATE TABLE tt006 (mkey varbinary(32) not null primary key, sval varbinary(32));
CREATE TABLE tt007 (mkey float not null primary key, sval float);
CREATE TABLE tt008 (mkey double not null primary key, sval double);
CREATE TABLE tt009 (mkey decimal(8,2) not null primary key, sval decimal(8,2));
CREATE TABLE tt010 (mkey date not null primary key, sval date);
CREATE TABLE tt011 (mkey datetime not null primary key, sval datetime);
CREATE TABLE tt012 (mkey time not null primary key, sval time);
CREATE TABLE tt013 (mkey tinyint unsigned not null primary key, sval tinyint unsigned);
CREATE TABLE tt014 (mkey smallint unsigned not null primary key, sval smallint unsigned);
CREATE TABLE tt015 (mkey mediumint unsigned not null primary key, sval mediumint unsigned);
CREATE TABLE tt016 (mkey int unsigned not null primary key, sval int unsigned);
CREATE TABLE tt017 (mkey bigint unsigned not null primary key, sval bigint unsigned);
CREATE TABLE tt018 (mkey tinyint not null primary key, sval tinyint);
CREATE TABLE tt019 (mkey smallint not null primary key, sval smallint);
CREATE TABLE tt020 (mkey mediumint not null primary key, sval mediumint);
CREATE TABLE tt021 (mkey int not null primary key, sval int);
CREATE TABLE tt022 (mkey bigint not null primary key, sval bigint);

CREATE VIEW tv_tablist AS SELECT TABLE_NAME 
  FROM INFORMATION_SCHEMA.TABLES 
  WHERE TABLE_NAME LIKE 'tt0%' and table_schema = 'ndbmemcache';

INSERT INTO containers (name, db_schema, db_table, key_columns, value_columns) 
 SELECT table_name, "ndbmemcache", table_name, "mkey", "sval" from tv_tablist;
 
INSERT INTO key_prefixes (key_prefix, policy, container) 
 SELECT concat(table_name,":"), "ndb-only", table_name
 FROM tv_tablist;

UPDATE memcache_server_roles set update_timestamp = now() 
  WHERE role_id = 0;
  
DROP VIEW tv_tablist;

--source suite/ndb_memcache/include/wait_for_reconf.inc
}

--enable_query_log
--enable_result_log

