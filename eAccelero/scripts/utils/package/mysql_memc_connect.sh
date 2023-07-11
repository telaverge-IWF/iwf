#!/bin/bash

PRODUCT=iwf
function check_mysql()
{
    count=58
    echo -n "checking for mysql "
    echo "check_mysql">> /var/log/dre/package.log
    while [ 1 ];do
    sleep 1
        netstat -nap | grep mysql | grep "LISTEN" > /dev/null
    if [ $? -eq 0 ]; then
        echo "."
        echo "Mysql started Listening" >> /var/log/dre/package.log
        return 0
        else
        echo "Mysql is Listening" >> /var/log/dre/package.log
    fi

    echo -n "."
    ((count--))
    if [ $count -le 0 ];then
            exit
        fi
        echo $count
    done
}

function check_and_start_mysql()
{
    echo "pgrep mysqld = `pgrep mysqld`" >> /var/log/dre/package.log
    echo "check_and_start_mysql" >> /var/log/dre/package.log
    pgrep mysqld >/dev/null 
    if [ $? -ne 0 ];then
        echo "starting mysql..." >> /var/log/dre/package.log
        echo "starting mysql..." >> /var/log/dre/package.log
        start mysqld
        echo "pgrep mysqld = `pgrep mysqld`" >> /var/log/dre/package.log
        pgrep mysqld >/dev/null
        if [ $? -eq 0 ];then
            echo "Myql up and running..." >> /var/log/dre/package.log
        check_mysql
        else
            echo "Could not start mysql" >> /var/log/dre/package.log
            exit 1
        fi
    fi
    echo "no need to start mysql.... already running!" >> /var/log/dre/package.log
}

DRE_CONFIG=/etc/dre.cfg
function GetMysqlUsername()
{
    sed -n s/^MysqlUsername=//p $DRE_CONFIG
}

function GetMysqlPassword()
{
    sed -n s/^MysqlPassword=//p $DRE_CONFIG
}

function GetMysqlIpAddress()
{
    sed -n s/^MysqlIpAddress=//p $DRE_CONFIG
}

function GetMysqlPort()
{
    sed -n s/^MysqlPort=//p $DRE_CONFIG
}

ip=`GetMysqlIpAddress`
username=`GetMysqlUsername`
password=`GetMysqlPassword`
port=`GetMysqlPort`
flag=0
my="mysql  --user=$username --password=$password --port=$port -se"
my1="mysql  --host=$ip --user=$username --password=$password --port=$port "

if [ "$PRODUCT" == "iwf" ];then
    exit 0
fi

netstat -anp|grep "50000"|grep "mysqld"|grep "ESTABLISHED"  >/dev/null
if [ $? -ne 0 ];then
        echo "connecting mysql to memcached..." >> /var/log/dre/package.log
        check_mysql
    check_and_start_mysql
    ${my1} < /opt/diametriq/dre/scripts/install_functions.sql
    ${my1} < /opt/diametriq/dre/scripts/trigger_fun.sql
fi






