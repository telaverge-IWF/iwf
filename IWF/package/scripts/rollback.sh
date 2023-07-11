#this script is used to rollback to older ${PRODUCT} and restoring the state of older${PRODUCT} 
PRODUCT=iwf
source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh
SYS_CFG=/opt/diametriq/${PRODUCT}/.syscfg
DRE_CONFIG=/etc/${PRODUCT}.cfg

function GetMysqlUsername()
{
    sed -n s/MysqlUsername=//p $DRE_CONFIG
}

function GetMysqlPassword()
{
    sed -n s/MysqlPassword=//p $DRE_CONFIG
}

function GetMysqlIpAddress()
{
    sed -n s/MysqlIpAddress=//p $DRE_CONFIG
}

function GetMysqlPort()
{
    sed -n s/MysqlPort=//p $DRE_CONFIG
}
LOG_DEBUG "rollback.sh beggining" $LINENO
PLOG_INFO "Restoring system configuration..." $LINENO

cp -f $SYS_CFG/${PRODUCT}.sh /etc/profile.d
cp -f $SYS_CFG/${PRODUCT}.env /etc/sysconfig/${PRODUCT}
cp -f $SYS_CFG/${PRODUCT}-x86_64.conf /etc/ld.so.conf.d
cp -f $SYS_CFG/dre /etc/rc.d/init.d
ldconfig
chkconfig --add dre


restore_iptable_rules $SYS_CFG
restore_bonding_cfg $SYS_CFG/bonding
check_and_reconfig_tipc
#restore_heartbeat_cfg $SYS_CFG/heartbeat
restore_mysqlreplication_cfg

service crond stop
LOG_INFO "Restoring logrotate and trace rotate configurations..." $LINENO

#deleting the previous crontab configuration
sed -i /${PRODUCT}_logrotate/d /etc/crontab >/dev/null
sed -i /run_${PRODUCT}_logrotate.sh/d /etc/crontab >/dev/null
sed -i /run_${PRODUCT}_console_logrotate.sh/d /etc/crontab >/dev/null
sed -i /database_dump.sh/d /etc/crontab >/dev/null
sed -i /tracer.sh/d /etc/crontab >/dev/null
sed -i /archive_purge.sh/d /etc/crontab >/dev/null

#add logrotate to crontab
grep "^0 \* \* \* \* root /opt/diametriq/${PRODUCT}/scripts/run_${PRODUCT}_console_logrotate.sh" /etc/crontab  >/dev/null
if [ $? != 0 ];then
    echo "0 * * * * root /opt/diametriq/${PRODUCT}/scripts/run_${PRODUCT}_console_logrotate.sh" >> /etc/crontab
fi
grep "^0 \* \* \* \* root /opt/diametriq/${PRODUCT}/scripts/run_${PRODUCT}_logrotate.sh" /etc/crontab  >/dev/null
if [ $? != 0 ];then
    echo "0 * * * * root /opt/diametriq/${PRODUCT}/scripts/run_${PRODUCT}_logrotate.sh" >> /etc/crontab
fi


grep "^30 \* \* \* \* root /opt/diametriq/${PRODUCT}/scripts/database_dump.sh" /etc/crontab  >/dev/null
if [ $? != 0 ];then
    echo "30 * * * * root /opt/diametriq/${PRODUCT}/scripts/database_dump.sh" >> /etc/crontab
fi

grep "\* \* \* \* \* root /opt/diametriq/${PRODUCT}/scripts/tracer.sh" /etc/crontab >/dev/null
if [ $? -ne 0 ];then
    echo "* * * * * root /opt/diametriq/${PRODUCT}/scripts/tracer.sh" >> /etc/crontab
fi

#add archive and purge script of stats to crontab
grep "^30 0 \* \* \* root /opt/diametriq/${PRODUCT}/scripts/archive_purge.sh" /etc/crontab >/dev/null
if [ $? != 0 ];then
    echo "30 0 * * * root /opt/diametriq/${PRODUCT}/scripts/archive_purge.sh" >> /etc/crontab
fi


ps -eaf|grep " crond"|grep -v "grep" >/dev/null
if [ $? -eq 0 ];then
    service crond restart
else
    service crond start
fi

pgrep apache-tomcat 1>/dev/null
if [ $? -eq 0 ];then
    stop apache-tomcat
fi
#/opt/apache-tomcat/bin/shutdown.sh
if [ $PRODUCT = "dre" ];then
    rm -rf /opt/apache-tomcat/webapps/DRE
    rm -f /opt/apache-tomcat/webapps/DRE.war
    PLOG_INFO "Copying WEB Application to Tomcat folder.." $LINENO
    cp -f /opt/diametriq/${PRODUCT}/WEB-GUI/DRE.war   /opt/apache-tomcat/webapps/
    PLOG_INFO "Copied WEB Application to Tomcat folder successfully" $LINENO
fi
#/opt/apache-tomcat/bin/startup.sh
start apache-tomcat

LOG_DEBUG "pgrep memcached = `pgrep memcached`" $LINENO
pgrep memcached
if [ $? == 0 ]
then
    PLOG_INFO "Memcached is up and running..." $LINENO
else
    PLOG_INFO "Starting Memcached..." $LINENO
    #/usr/bin/memcached -p 11211 -m 1024 -u root &
    start memcached
    if [ $? != 0 ]
    then
        PLOG_ERROR "Starting memcached failed!" $LINENO
        exit 1
    fi
 
fi

MysqlUsername=$( GetMysqlUsername )
LOG_INFO "MysqlUsername=$MysqlUsername" $LINENO
MysqlPassword=$( GetMysqlPassword )
LOG_INFO "MysqlPassword=$MysqlPassword" $LINENO
MysqlIpAddress=$( GetMysqlIpAddress )
LOG_INFO "MysqlIpAddress=$MysqlIpAddress" $LINENO
MysqlPort=$( GetMysqlPort )
LOG_INFO "MysqlPort=$MysqlPort" $LINENO
cd $SYS_CFG
DUMP=`ls -rt *.sql | grep "dump" |tail -1`
LOG_DEBUG "DUMP = $DUMP" $LINENO

my="mysql  --host=$MysqlIpAddress --user=$MysqlUsername --password=$MysqlPassword --port=$MysqlPort -se"
${my} "set @@global.sql_log_bin=0"
${my} "set @@session.sql_log_bin=0"

${my} "drop database DIAMETRIQ"
if [ $? -ne 0 ];then
    PLOG_ERROR "Mysql error! exiting..." $LINENO
    ${my} "set @@global.sql_log_bin=1"
    ${my} "set @@session.sql_log_bin=1"
    exit 1
fi

${my} "create database DIAMETRIQ"
if [ $? -ne 0 ];then
    PLOG_ERROR "Mysql error! exiting..." $LINENO
    ${my} "set @@global.sql_log_bin=1"
    ${my} "set @@session.sql_log_bin=1"
    exit 1
fi

mysql -u $MysqlUsername -p$MysqlPassword  DIAMETRIQ < $DUMP
if [ $? -ne 0 ];then
    PLOG_ERROR "Mysql error! exiting..." $LINENO
    ${my} "set @@global.sql_log_bin=1"
    ${my} "set @@session.sql_log_bin=1"
    exit 1
fi


my1="mysql  --host=$MysqlIpAddress --user=$MysqlUsername --password=$MysqlPassword --port=$MysqlPort "
if [ $? -ne 0 ];then
    PLOG_ERROR "Mysql error! exiting..." $LINENO
    exit 1
fi

if [ "${PRODUCT}" == "dre" ];then
    ${my1} < /opt/diametriq/${PRODUCT}/scripts/install_functions.sql
    if [ $? -ne 0 ];then
        PLOG_ERROR "Mysql error! exiting..." $LINENO
        ${my} "set @@global.sql_log_bin=1"
        ${my} "set @@session.sql_log_bin=1"
        exit 1
    fi
    ${my1} < /opt/diametriq/${PRODUCT}/scripts/trigger_fun.sql
    if [ $? -ne 0 ];then
        PLOG_ERROR "Mysql error! exiting..." $LINENO
        ${my} "set @@global.sql_log_bin=1"
        ${my} "set @@session.sql_log_bin=1"
        exit 1
    fi
fi

${my} "set @@global.sql_log_bin=1"
${my} "set @@session.sql_log_bin=1"
