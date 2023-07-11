#!/bin/bash
#This script is a wrapper script which Handles  log rotate error 
#which will corrupt the logrotate file
#

if [ $# != 1 ]; then
    echo "Enter the path to the log-rotation configuration file"
    exit 1
fi

FILE_PATH="$1"

logrotate $FILE_PATH
if [ $? -ne 0 ]; then
    echo "logrotate state -- version 2" > /var/lib/logrotate.status
    logrotate $FILE_PATH
    if [ $? -ne 0 ]; then
        echo "logrotation failing... " >> /var/log/dre/package_critical.log 
    fi
fi
