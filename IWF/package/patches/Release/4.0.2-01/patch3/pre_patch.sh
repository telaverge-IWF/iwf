#!/bin/bash
#adding rocommunity public in the begining of /etc/snmp/snmpd.conf

ps -eaf|grep ^avamgr|grep -v grep >/dev/null
if [ $? -eq 0 ];then
    echo "Stop DRE..."
    service dre stop
fi


