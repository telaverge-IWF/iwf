#!/bin/bash

PRODUCT=iwf
source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh
USERNAME=`GetMysqlUsername`
PASSWORD=`GetMysqlPassword`
IP=`GetMysqlIpAddress`
PORT=`GetMysqlPort`
LOCAL_IP=`GetMysqlLocalIP`
MATE_IP=`GetMysqlMateIP`
VIRTUAL_CIDR=`GetVirtualIP`
VIRTUAL_IP=`echo "$VIRTUAL_CIDR"|cut -d'/' -f1`

my="mysql  --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT -se"
unset_sess_repl="set @@session.sql_log_bin=0;"

${my} "${unset_sess_repl} GRANT REPLICATION SLAVE ON *.* TO replica@\"%\" IDENTIFIED BY 'replica_passwd';"
sed -i "s/^relay-log=.*/relay-log=diametriq-relay-bin/g" /etc/my.cnf
LOG_INFO "-- " $LINENO
serverId=`date +%s`
if [ $# -eq 1 ];then
    if [ "$1" == "--rollback" ];then
        LOG_DEBUG "Not updating server id as its rollback" $LINENO
    fi
else
    LOG_DEBUG "Updating server-id=$serverId in my.cnf" $LINENO
    sed -i "s/^server-id.*/server-id=$serverId/g" /etc/my.cnf
fi
LOG_DEBUG "--1--" $LINENO
LOG_DEBUG "--2--" $LINENO
stop mysqld
start mysqld
check_mysql
LOG_DEBUG "--3--" $LINENO
LOG_DEBUG "--4--" $LINENO
LOG_DEBUG "--5--" $LINENO
${my} "${unset_sess_repl} STOP SLAVE;"
LOG_DEBUG "--6--" $LINENO

${my} "${unset_sess_repl} GRANT CREATE,EXECUTE,GRANT OPTION,LOCK TABLES,DROP,REFERENCES,ALTER,DELETE,INDEX,INSERT,SELECT,UPDATE,TRIGGER,ALTER ROUTINE,CREATE ROUTINE,CREATE USER,REPLICATION CLIENT,REPLICATION SLAVE,REFERENCES,SUPER ON *.* TO replica@'$MATE_IP' IDENTIFIED BY 'replica_passwd' with GRANT option;"
if [ "$USERNAME" = "root" ]; then
	${my} "${unset_sess_repl} GRANT ALL ON *.* to $USERNAME@'$LOCAL_IP' IDENTIFIED BY '$PASSWORD';"
	${my} "${unset_sess_repl} GRANT ALL ON *.* to $USERNAME@'$MATE_IP' IDENTIFIED BY '$PASSWORD';"
	${my} "${unset_sess_repl} GRANT ALL ON *.* to $USERNAME@'$VIRTUAL_IP' IDENTIFIED BY '$PASSWORD';"	
else
	${my} "${unset_sess_repl} GRANT CREATE,EXECUTE,GRANT OPTION,LOCK TABLES,DROP,REFERENCES,ALTER,DELETE,INDEX,INSERT,SELECT,UPDATE,TRIGGER,ALTER ROUTINE,CREATE ROUTINE,CREATE USER,REPLICATION CLIENT,REPLICATION SLAVE,REFERENCES,SUPER ON *.* TO $USERNAME@'$LOCAL_IP' IDENTIFIED BY '$PASSWORD' with GRANT option;"
	${my} "${unset_sess_repl} GRANT CREATE,EXECUTE,GRANT OPTION,LOCK TABLES,DROP,REFERENCES,ALTER,DELETE,INDEX,INSERT,SELECT,UPDATE,TRIGGER,ALTER ROUTINE,CREATE ROUTINE,CREATE USER,REPLICATION CLIENT,REPLICATION SLAVE,REFERENCES,SUPER ON *.* TO $USERNAME@'$MATE_IP' IDENTIFIED BY '$PASSWORD' with GRANT option;"
	${my} "${unset_sess_repl} GRANT CREATE,EXECUTE,GRANT OPTION,LOCK TABLES,DROP,REFERENCES,ALTER,DELETE,INDEX,INSERT,SELECT,UPDATE,TRIGGER,ALTER ROUTINE,CREATE ROUTINE,CREATE USER,REPLICATION CLIENT,REPLICATION SLAVE,REFERENCES,SUPER ON *.* TO $USERNAME@'$VIRTUAL_IP' IDENTIFIED BY '$PASSWORD' with GRANT option;"
fi

ALREADY_CONFIGERED_IP=`${my} "${unset_sess_repl} show slave status \G;" | grep Master_Host | tr -s " " | cut -d " " -f 3`

if [ "$ALREADY_CONFIGERED_IP" = $MATE_IP ]; then

    	LOG_INFO "Mysql Replication is already configured for ip \"$MATE_IP\" " $LINENO
        LOG_DEBUG "--7--" $LINENO
	${my} "${unset_sess_repl} START SLAVE;"
	if [ $? -ne 0 ];then

		LOG_DEBUG "start slave failed... we are reseting slave configuration  " $LINENO
		RELAY_LOG_NAME=`${my} "${unset_sess_repl} show slave status \G;" | grep Relay_Log_File | tr -s " " | cut -d " " -f 3`	
		LOG_DEBUG "Taking old configuration, Realylogname =  "$RELAY_LOG_NAME $LINENO
		RELAY_LOG_POS=`${my} "${unset_sess_repl} show slave status \G;" | grep Relay_Log_Pos | tr -s " " | cut -d " " -f 3`
		LOG_DEBUG "Taking old configuration, Realylogpos =  "$RELAY_LOG_POS $LINENO
		LOG_DEBUG "--8--" $LINENO
    		${my} "${unset_sess_repl} RESET SLAVE;"
		LOG_DEBUG "--9--" $LINENO
		${my} "${unset_sess_repl} CHANGE MASTER TO MASTER_HOST='$MATE_IP',RELAY_LOG_FILE='$RELAY_LOG_NAME',RELAY_LOG_POS=$RELAY_LOG_POS, MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';" 2>>/var/log/${PRODUCT}/package_critical.log
		LOG_DEBUG "--10--" $LIENNO
		${my} "${unset_sess_repl} START SLAVE;"
    		if [ $? -ne 0 ];then
    			LOG_ERROR "Mysql Replication configuration failed!" $LINENO
			exit 1
    		fi
	fi

elif [ "$ALREADY_CONFIGERED_IP" = "" ]; then
    	LOG_INFO "Mysql Replication is not configured  " $LINENO
	${my} "${unset_sess_repl} CHANGE MASTER TO MASTER_HOST='$MATE_IP', MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';"

	if [ $? -ne 0 ];then
    		# There is some error in the replication 
    		# resetting the slave
    		#
		LOG_DEBUG "changing master ip failed... we are reseting slave " $LINENO
		LOG_DEBUG "--11--" $LIENNO
    		${my} "${unset_sess_repl} RESET SLAVE;"
   		LOG_DEBUG "--12--" $LIENNO
 		${my} "${unset_sess_repl} CHANGE MASTER TO MASTER_HOST='$MATE_IP', MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';"
    		if [ $? -ne 0 ];then
    			LOG_ERROR "Mysql Replication configuration failed!" $LINENO
			exit 1
    		fi
	fi

        LOG_DEBUG "--13--" $LIENNO
	${my} "${unset_sess_repl} START SLAVE;"
	if [ $? -ne 0 ];then
    		# There is some error in the replication 
    		# resetting the value
	        LOG_DEBUG "--14--" $LIENNO
		LOG_DEBUG "start slave failed... we are reseting slave " $LINENO
	#
    		${my} "${unset_sess_repl} RESET SLAVE;"
    		${my} "${unset_sess_repl} CHANGE MASTER TO MASTER_HOST='$MATE_IP', MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';"
	        LOG_DEBUG "--15--" $LIENNO
	        ${my} "${unset_sess_repl} START SLAVE;"
    		if [ $? -ne 0 ];then
    			LOG_ERROR "Mysql Replication configuration failed!" $LINENO
			exit 1
    		fi
	fi

elif [ "$ALREADY_CONFIGERED_IP" != "$MATE_IP" ]; then

    	LOG_INFO "Mysql Replication ip change from \"$ALREADY_CONFIGERED_IP\" to  \"$MATE_IP\" " $LINENO
	RELAY_LOG_NAME=`${my} "${unset_sess_repl} show slave status \G;" | grep Relay_Log_File | tr -s " " | cut -d " " -f 3`	
	RELAY_LOG_POS=`${my} "${unset_sess_repl} show slave status \G;" | grep Relay_Log_Pos | tr -s " " | cut -d " " -f 3`

	${my} "${unset_sess_repl} CHANGE MASTER TO MASTER_HOST='$MATE_IP',RELAY_LOG_FILE='$RELAY_LOG_NAME',RELAY_LOG_POS=$RELAY_LOG_POS, MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';"

	if [ $? -ne 0 ];then
    		# There is some error in the replication 
    		# resetting the slave
    		LOG_DEBUG "--16--" $LIENNO

		LOG_DEBUG "start slave failed... we are reseting slave " $LINENO
    		${my} "${unset_sess_repl} RESET SLAVE;"
		${my} "${unset_sess_repl} CHANGE MASTER TO MASTER_HOST='$MATE_IP',RELAY_LOG_FILE='$RELAY_LOG_NAME',RELAY_LOG_POS=$RELAY_LOG_POS, MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';"
    		if [ $? -ne 0 ];then
    			PLOG_ERROR "Mysql Replication configuration failed!" $LINENO
			exit 1
    		fi
	fi
        LOG_DEBUG "--17--" $LIENNO

	${my} "${unset_sess_repl} START SLAVE;"
	if [ $? -ne 0 ];then
    		# There is some error in the replication 
    		# resetting the value
		LOG_DEBUG "--18--" $LIENNO

		LOG_DEBUG "start slave failed... we are reseting slave " $LINENO
    		${my} "${unset_sess_repl} RESET SLAVE;"
		${my} "${unset_sess_repl} CHANGE MASTER TO MASTER_HOST='$MATE_IP',RELAY_LOG_FILE='$RELAY_LOG_NAME',RELAY_LOG_POS=$RELAY_LOG_POS, MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';"
                LOG_DEBUG "--19--" $LIENNO
		${my} "${unset_sess_repl} START SLAVE;"
    		if [ $? -ne 0 ];then
    			PLOG_ERROR "Mysql Replication configuration failed!" $LINENO
			exit 1
    		fi
	fi

fi

LOG_DEBUG "--20--" $LIENNO
