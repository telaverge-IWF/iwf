#!/bin/bash
ps -eaf|grep ^avamgr|grep -v grep >/dev/null
if [ $? -ne 0 ];then
    echo "Start DRE..."
    service dre start
fi



