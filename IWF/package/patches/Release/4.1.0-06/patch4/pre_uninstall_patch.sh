#!/bin/bash
echo ">>> pre uninstall script execution >>>"

ps -eaf|grep ^avamgr|grep -v grep >/dev/null
if [ $? -eq 0 ];then
    echo "Stop DRE..."
    service dre stop
fi



