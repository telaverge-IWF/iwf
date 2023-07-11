#!/bin/bash
PRODUCT=iwf

source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh
USERNAME=`GetMysqlUsername`
PASSWORD=`GetMysqlPassword`
IP=`GetMysqlIpAddress`
PORT=`GetMysqlPort`
LOCAL_IP=`GetMysqlLocalIP`
MATE_IP=`GetMysqlMateIP`

my="mysql  --user=$USERNAME --password=$PASSWORD --port=$PORT "
mydump="mysqldump  --host=$MATE_IP --user=$USERNAME --password=$PASSWORD --port=$PORT --databases DIAMETRIQ "

${mydump} > /tmp/diametriq_dump.sql
if [ $? -ne 0 ];then
	
    PLOG_ERROR "Failed to dump mysql data from mate!" $LINENO
    PLOG_ERROR "Possible issues can be..." $LINENO
    PLOG_ERROR "1) mysql is not running..." $LINENO
    PLOG_ERROR "2) Previlage is not created for user/ip" $LINENO
  
    exit 1

fi
${my} DIAMETRIQ < /tmp/diametriq_dump.sql
if [ $? -ne 0 ];then
	
    PLOG_ERROR "Failed to import mysql dump from mate!" $LINENO
    exit 1

fi
LOG_INFO "Successfully dumped the data into the mysql " $LINENO
echo "Done !!!"
