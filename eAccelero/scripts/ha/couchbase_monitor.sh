#!/bin/bash

PRODUCT=iwf
source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh
CB_CRON_LOCK=/etc/.${PRODUCT}/couchbase_cron_lock
list="epmd beam.smp memsup cpu_sup ssl_esock  moxi /opt/couchbase/bin/memcached  inet_gethost"
flag=0

function check_if_user_stopped_or_started_couchbase()
{
    if [ -e /etc/.${PRODUCT}/couchbase_state ];then
        if [ "`cat /etc/.${PRODUCT}/couchbase_state`" == "0" ] || [ "`cat /etc/.${PRODUCT}/couchbase_state`" == "2" ];then
            echo "couchbase state changed" >>$CB_LOGS
	    return 0
	else
	    return 1
        fi
    fi
}

while [ 1 ]
do
    sleep 1
    
    check_if_user_stopped_or_started_couchbase
    if [ $? -eq 0 ];then
	continue
    fi


    for i in $list
    do
        ps -eaf|grep $i|grep -v grep > /dev/null
        if [ $? -ne 0 ];then
            echo "`date`:$i is not running." >>$CB_LOGS
	    flag=1
        fi

    done
    check_if_user_stopped_or_started_couchbase
    if [ $? -eq 0 ];then
	continue
    fi

    if [ $flag -eq 1 ];then
        echo "one of the process has stopped!" >>$CB_LOGS
        service couchbase-server stop
        for i in $list
        do
            pkill -9 $i
        done

        check_and_start_couchbase
 	#make sure all the processes have come up
	#wait until then
	while [ $flag -eq 1 ]
	do
            check_if_user_stopped_or_started_couchbase
            if [ $? -eq 0 ];then
		flag=0
	        break
            fi


	    sleep 1
	    flag=0
	    for i in $list
	    do 
		ps -eaf|grep $i|grep -v grep > /dev/null
        	if [ $? -ne 0 ];then
           	     echo "`date`$i is not running." >>$CB_LOGS
	    	    flag=1
        	fi

	    done
  	    
	done
    else
	flag=0
    fi
done

