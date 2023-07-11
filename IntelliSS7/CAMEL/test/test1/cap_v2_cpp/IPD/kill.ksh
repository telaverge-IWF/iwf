#!/bin/ksh
pID=$(ps -ef | grep test | grep -v grep | nawk '{print $2}')
if [[ $pID != "" ]]; then
echo $pID
kill -9 $pID
fi
