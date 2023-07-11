#!/bin/bash
source /opt/diametriq/dre/scripts/package_functions.sh

DEST=/var/log/archive/
mkdir -p $DEST

function take_mysql_dump()
{

	local ip=`GetMysqlIpAddress`
	local username=`GetMysqlUsername`
	local password=`GetMysqlPassword`
	local port=`GetMysqlPort`
	mysqldump --host=$ip --user=$username --password=$password --port=$port --databases DIAMETRIQ >> /tmp/$1 2>/dev/null

}

makedirstruct()
{

    local DIR1=`echo $DEST``date | tr -s ':' ' ' | cut -d ' ' -f 8`
    local DIR2=`echo $DIR1`/`date | tr -s ':' ' ' | cut -d ' ' -f 2`
    local DIR3=`echo $DIR2`/`date | tr -s ':' ' ' | cut -d ' ' -f 3`
    if [ "$1" = "HOUR" ]
    then
        TARGET=`echo $DIR3`/`date | tr -s ':' ' ' | cut -d ' ' -f 4`
    else
        TARGET=$DIR3
    fi

    mkdir -p $TARGET/mysql
    mv -f /tmp/$2 $TARGET/mysql/.
}

MYSQL_DUMP_FILE="mysql_dump_"
DATE=`date | tr -s " " | tr " " "_"`
MYSQL_DUMP_FILE=$MYSQL_DUMP_FILE$DATE".sql"

take_mysql_dump $MYSQL_DUMP_FILE
makedirstruct " " $MYSQL_DUMP_FILE
