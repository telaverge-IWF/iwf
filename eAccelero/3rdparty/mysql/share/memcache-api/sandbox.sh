#!/bin/sh

prefix=/opt/checkout/eAccelero/3rdparty/mysql
bindir=bin
libexecdir=bin
libdir=lib
scriptsdir=scripts
memcachedir=/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/extra/memcached
sourcetree=/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache
installtree=/opt/checkout/eAccelero/3rdparty/mysql/memcache-api
memcached_binary=/opt/checkout/eAccelero/3rdparty/mysql/bin/memcached

MYSELF=`who am i | awk '{print $1}'`
MYSQL_PREFIX=$prefix
MYSQL_BIN=$prefix/$bindir
MYSQL_LIBEXEC=$prefix/$libexecdir
MYSQL_SCRIPTS=$prefix/$scriptsdir
MYSQL_LIB=$prefix/$libdir
MEMCACHE_BASE=$memcachedir
SOURCE_TREE=$sourcetree
HOME_BASE=$sourcetree   # fallback to source tree 

if test `pwd` = $SOURCE_TREE
 then
   # If we are in the source tree, use the memcached and engine there
   memcached_binary=$MEMCACHE_BASE/memcached
   NDB_ENGINE_SO=$SOURCE_TREE/ndb_engine.so
 else
   test -d $installtree && HOME_BASE=$installtree
   NDB_ENGINE_SO=$MYSQL_LIB/ndb_engine.so
fi

test_paths() {
  test_path $MYSQL_BIN ndb_mgm
  test_path $MYSQL_BIN mysql
  test_path $MYSQL_BIN mysqladmin
  test_path $MYSQL_LIBEXEC ndb_mgmd
  test_path $MYSQL_LIBEXEC ndbd
  test_path $MYSQL_LIBEXEC mysqld_safe
  test_path $MYSQL_SCRIPTS mysql_install_db
  if [ ! -x $memcached_binary ] 
    then 
      echo "Cannot execute $memcached_binary"
      exit
  fi
}

test_path() {
  if [ ! -x $1/$2 ] 
   then
    echo "Fatal error: cannot execute $2 at $1"
    exit
  fi
}

build_dirs() {
  echo Creating sandbox
  mkdir $HOME_BASE/sandbox
  mkdir $HOME_BASE/sandbox/data
  mkdir $HOME_BASE/sandbox/ndb 
  mkdir $HOME_BASE/sandbox/ndb-config
}

write_my_cnf() {
  ( echo "[mysqld]"
    echo "ndbcluster"
    echo "datadir=$HOME_BASE/sandbox/data"
    echo "pid-file=$HOME_BASE/sandbox/mysqld.pid"
    echo "user=$MYSELF"
    echo "innodb_log_file_size=1M"
    echo
  ) > $HOME_BASE/sandbox/my.cnf
 }

write_cluster_ini() {
  ( echo "[MGM]"
    echo "NodeId=1"
    echo "datadir=$HOME_BASE/sandbox/ndb"
    echo "hostname=localhost"
    echo 
    echo "[DB DEFAULT]"
    echo "NoOfReplicas=1"
    echo "TimeBetweenGlobalCheckpoints=12000"
    echo "DataMemory=180M"
    echo "IndexMemory=60M"
    echo "HeartbeatIntervalDbApi=15000"
    echo
    echo "[NDBD]"
    echo "NodeId=2"
    echo "datadir=$HOME_BASE/sandbox/ndb"
    echo 
    echo "[API]"
    echo "[API]"
    echo "[API]"
    echo "[API]"
    echo "[API]"
    echo "[API]"
    echo "[API]"
  ) > $HOME_BASE/sandbox/cluster.ini
}

do_install_db() {
  $MYSQL_SCRIPTS/mysql_install_db \
    --basedir=$MYSQL_PREFIX --datadir=$HOME_BASE/sandbox/data \
    --skip-name-resolve --user=$MYSELF > /dev/null
  if test ! -d sandbox/data/mysql 
    then echo "Failed: mysql_install_db did not work." && exit
    else echo "Created MySQL System Tables"
  fi
}

start_mgm_server() {
  INITIAL="--initial"
  test -f sandbox/ndb-config/ndb_1_config.bin.1 && INITIAL=""

  $MYSQL_LIBEXEC/ndb_mgmd -f $HOME_BASE/sandbox/cluster.ini \
    --config-dir=$HOME_BASE/sandbox/ndb-config $INITIAL
    
  sleep 5
}

start_ndbd() {
  $MYSQL_LIBEXEC/ndbd 
  sleep 5
}

start_mysql_server() {
  $MYSQL_LIBEXEC/mysqld_safe --defaults-file=$HOME_BASE/sandbox/my.cnf &
  sleep 5
}

mysqld_is_running() {  
   test_pid mysqld.pid
}

mgm_server_is_running() {  
   test_pid ndb/ndb_1.pid
}

ndbd_is_running()  {  
   test_pid ndb/ndb_2.pid
}

memcached_is_running() {
   test_pid memcached.pid
}

test_pid() {
  test -f sandbox/$1  || return 1
  SERVERPID=`cat $HOME_BASE/sandbox/$1`
  ps -p "$SERVERPID" > /dev/null || return 1
  return 0
}

load_metadata() {
  echo Loading NDB Memcache configuration data
  DDL_SCRIPT=$SOURCE_TREE/scripts/ndb_memcache_metadata.sql
  $MYSQL_BIN/mysql --connect-timeout=10 -u root < $DDL_SCRIPT || TRY_AGAIN=1
  test "$TRY_AGAIN" = "1" && $MYSQL_BIN/mysql --connect-timeout=10 \
    -u root < $DDL_SCRIPT
}

start_memcached() {
    $memcached_binary -d -v \
    -P $HOME_BASE/sandbox/memcached.pid \
    -E $NDB_ENGINE_SO $1 $2
}

stop_memcached() {
  SERVERPID=`cat $HOME_BASE/sandbox/memcached.pid`
  test -n "$SERVERPID" && kill $SERVERPID
}

stop_mysqld() {
  $MYSQL_BIN/mysqladmin -u root shutdown
}

stop_mgm_server() {
  $MYSQL_BIN/ndb_mgm -e shutdown
}

final_message() {
  sleep 2
  echo
  echo "Sandbox directory is $HOME_BASE/sandbox"
  echo "Memcached is $memcached_binary"
  echo 
  echo "Use \"sh sandbox.sh stop\" to stop memcached & MySQL Cluster"
  echo 
}

usage() {
  echo "sandbox.sh start [ndb_mgmd | ndbd | mysql | memcached]"
  echo "           stop  [ndb_mgmd | mysql | memcached]"
  echo "           status"
  echo
  exit
}

cmd_status() {
  if mgm_server_is_running 
    then echo "[ndb_mgmd]   running"
    else echo "[ndb_mgmd]   stopped"
  fi
  if ndbd_is_running 
    then echo "[ndbd]       running"
    else echo "[ndbd]       stopped"
  fi
  if mysqld_is_running
    then echo "[mysqld]     running"
    else echo "[mysqld]     stopped"
  fi
  if memcached_is_running
    then echo "[memcached]  running"
    else echo "[memcached]  stopped"
  fi
}

cmd_stop() {
  test "$1" = "memcached"  &&   stop_memcached   &&  exit
  test "$1" = "mysqld"     &&   stop_mysqld      &&  exit
  test "$1" = "ndb_mgmd"   &&   stop_mgm_server  &&  exit

  test "$1" = ""  ||   usage

  # stop all
  mysqld_is_running        &&   stop_mysqld
  memcached_is_running     &&   stop_memcached
  mgm_server_is_running    &&   stop_mgm_server
}  

cmd_start() {
  test "$1" = "memcached"  &&  start_memcached    && exit
  test "$1" = "mysqld"     &&  start_mysql_server && exit
  test "$1" = "ndbd"       &&  start_ndbd         && exit
  test "$1" = "ndb_mgmd"   &&  start_mgm_server   && exit

  test "$1" = ""  ||   usage
  
  # start all
  test -d sandbox                     ||  build_dirs
  test -f sandbox/my.cnf              ||  write_my_cnf
  test -f sandbox/cluster.ini         ||  write_cluster_ini
  test -d sandbox/data/mysql          ||  do_install_db
  mgm_server_is_running               ||  start_mgm_server
  ndbd_is_running                     ||  start_ndbd 
  mysqld_is_running                   ||  start_mysql_server  
  test -d sandbox/data/ndbmemcache    ||  load_metadata  
  memcached_is_running                ||  start_memcached

  final_message
}  


# ------------------------------ main script --------------------------

( cd $HOME_BASE 
  test_paths
  if test "$1" = "stop" 
   then 
     cmd_stop "$2"
  elif test "$1" = "start"  
   then
     cmd_start "$2"
  elif test "$1" = "status" 
    then
     cmd_status
  else 
     usage
  fi
)
