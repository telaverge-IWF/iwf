#!/bin/bash

PRODUCT=iwf
source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh
USERNAME=`GetMysqlUsername`
PASSWORD=`GetMysqlPassword`
IP=`GetMysqlIpAddress`
PORT=`GetMysqlPort`
LOCAL_IP=`GetMysqlLocalIP`
MATE_IP=`GetMysqlMateIP`

MESSAGE=[`date`][$0]"Message From database monitor script. "

mylocaldump="mysqldump --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT --databases DIAMETRIQ "
mymatedump="mysqldump  --host=$MATE_IP --user=$USERNAME --password=$PASSWORD --port=$PORT --databases DIAMETRIQ "

${mymatedump} > /tmp/diametriq_mate_dump.sql
if [ $? -ne 0 ];then
    PLOG_ERROR "Failed to dump mysql data from mate mysql!" $LINENO
    PLOG_ERROR "Possible issues can be..." $LINENO
    PLOG_ERROR "1) mysql is not running..." $LINENO
    PLOG_ERROR "2) Previlage is not created for user/ip" $LINENO
    exit 1
fi
${mylocaldump} > /tmp/diametriq_local_dump.sql
if [ $? -ne 0 ];then
    PLOG_ERROR "Failed to dump mysql data from local mysql!" $LINENO
    PLOG_ERROR "Possible issues can be..." $LINENO
    PLOG_ERROR "1) mysql is not running..." $LINENO
    PLOG_ERROR "2) Previlage is not created for user/ip" $LINENO
    exit 1
fi

if [ -e /tmp/diametriq_mate_dump.sql ];then
	sed -i /"Dump completed"/d /tmp/diametriq_mate_dump.sql
	sed -i /"Database: DIAMETRIQ"/d /tmp/diametriq_mate_dump.sql
fi

if [ -e /tmp/diametriq_local_dump.sql ];then
	sed -i /"Dump completed"/d /tmp/diametriq_local_dump.sql
	sed -i /"Database: DIAMETRIQ"/d /tmp/diametriq_local_dump.sql
fi

MYSQL_DIFF=`diff /tmp/diametriq_mate_dump.sql /tmp/diametriq_local_dump.sql`
if [ -z "$MYSQL_DIFF" ];then
	echo $MESSAGE"Databases are in sync......"
	echo $MESSAGE"Databases are in sync......" >>/var/log/${PRODUCT}/cmgr.log
	#wall $MESSAGE"Databases are in sync....."
else
	echo $MESSAGE"Databases are not in sync....."
	echo $MESSAGE"diff:-"$MYSQL_DIFF >>/var/log/${PRODUCT}/cmgr.log
	wall $MESSAGE"Databases are not in sync..... diff:-" "$MYSQL_DIFF"
fi

