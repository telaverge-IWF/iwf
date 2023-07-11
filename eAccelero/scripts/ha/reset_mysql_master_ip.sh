#!/bin/bash
PRODUCT=iwf
source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh

if [ $# != 1 ]
then
    echo "Enter the Master IP as Parameter" 
    echo "Usage:- $0 MasterMysqlIP"
    exit 1
fi

/bin/ipcalc -cs $1
if [ $? -ne 0 ];then
	PLOG_INFO "Mysql ipaddress is not valid" $LINENO 
	exit 1
fi


USERNAME=`GetMysqlUsername`
PASSWORD=`GetMysqlPassword`
IP=`GetMysqlIpAddress`
PORT=`GetMysqlPort`
LOCAL_IP=`GetMysqlLocalIP`
MATE_IP=$1
LOCAL_HOSTNAME=`GetMysqlLocalHostname`
MATE_HOSTNAME=`GetMysqlMateHostname`

my="mysql  --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT -se"
unset_sess_repl="set @@session.sql_log_bin=0;"

${my} "${unset_sess_repl} STOP SLAVE;"
${my} "${unset_sess_repl} RESET MASTER"
${my} "${unset_sess_repl} GRANT REPLICATION SLAVE ON *.* TO replica@\"%\" IDENTIFIED BY 'replica_passwd';"

ALREADY_CONFIGERED_IP=`${my} "${unset_sess_repl} show slave status \G;" | grep Master_Host | tr -s " " | cut -d " " -f 3`

if [ "$ALREADY_CONFIGERED_IP" == "$MATE_IP" ]; then

    	LOG_INFO "Mysql Replication is already configured for ip \"$MATE_IP\" " $LINENO
    	${my} "${unset_sess_repl} RESET SLAVE;"
	${my} "${unset_sess_repl} CHANGE MASTER TO MASTER_HOST='$MATE_IP', MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';"
	${my} "${unset_sess_repl} START SLAVE;"

elif [ "$ALREADY_CONFIGERED_IP" = "" ]; then
    	LOG_INFO "Mysql Replication is not configured  " $LINENO
	${my} "${unset_sess_repl} CHANGE MASTER TO MASTER_HOST='$MATE_IP', MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';"

	if [ $? -ne 0 ];then
    		# There is some error in the replication 
    		# resetting the slave
    		#
    		${my} "${unset_sess_repl} RESET SLAVE;"
    		${my} "${unset_sess_repl} CHANGE MASTER TO MASTER_HOST='$MATE_IP', MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';"
    		if [ $? -ne 0 ];then
    			PLOG_ERROR "Mysql Replication configuration failed!" $LINENO

			exit 1
    		fi
	fi

	${my} "${unset_sess_repl} START SLAVE;"
	if [ $? -ne 0 ];then
    		# There is some error in the replication 
    		# resetting the value
		#
    		${my} "${unset_sess_repl} RESET SLAVE;"
    		${my} "${unset_sess_repl} CHANGE MASTER TO MASTER_HOST='$MATE_IP', MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';"
		
		${my} "${unset_sess_repl} START SLAVE;"
    		if [ $? -ne 0 ];then
    			PLOG_ERROR "Mysql Replication configuration failed!" $LINENO
			exit 1
    		fi
	fi

elif [ "$ALREADY_CONFIGERED_IP" != "$MATE_IP" ]; then

    	LOG_INFO "Mysql Replication ip change from \"$ALREADY_CONFIGERED_IP\" to  \"$MATE_IP\" " $LINENO

	${my} "${unset_sess_repl} CHANGE MASTER TO MASTER_HOST='$MATE_IP', MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';"

	if [ $? -ne 0 ];then
    		# There is some error in the replication 
    		# resetting the slave
    		#
    		${my} "${unset_sess_repl} RESET SLAVE;"
		${my} "${unset_sess_repl} CHANGE MASTER TO MASTER_HOST='$MATE_IP', MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';"
    		if [ $? -ne 0 ];then
    			PLOG_ERROR "Mysql Replication configuration failed!" $LINENO
			exit 1
    		fi
	fi

	${my} "${unset_sess_repl} START SLAVE;"
	if [ $? -ne 0 ];then
    		# There is some error in the replication 
    		# resetting the value
		#
    		${my} "${unset_sess_repl} RESET SLAVE;"
		${my} "${unset_sess_repl} CHANGE MASTER TO MASTER_HOST='$MATE_IP', MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';"
		${my} "${unset_sess_repl} START SLAVE;"
    		if [ $? -ne 0 ];then
    			PLOG_ERROR "Mysql Replication configuration failed!" $LINENO
			exit 1
    		fi
	fi

fi
