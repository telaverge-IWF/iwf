#!/bin/bash
#script to configura/reconfigure couchbase
#Same script is used by avamgr process to configure couchbase
PRODUCT=iwf

source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh
calculate_ram_for_couchbase
configure_couchbase
RET=$?
if [ $RET -ne 0 ];then
    exit $RET
else
    exit 0
fi
