#script for tracer log rotation
#!/bin/bash

PRODUCT=iwf
if [ -z $PRODUCT ];then
    S_PRODUCT_NAME=dre
    PRODUCT_NAME=DRE
elif [ $PRODUCT = "dre" ];then
    S_PRODUCT_NAME=dre
    PRODUCT_NAME=DRE
elif [ $PRODUCT = "iwf" ];then
    S_PRODUCT_NAME=iwf
    PRODUCT_NAME=IWF
fi

seconds=58
while [ 1 ]
do
    logrotate  /opt/diametriq/${S_PRODUCT_NAME}/config/${S_PRODUCT_NAME}_trace_logrotate
    sleep 1
    ((seconds--))
    if [ $seconds -le 0 ];then
        exit
    fi
    echo $seconds
done


