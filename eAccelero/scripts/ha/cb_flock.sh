#!/bin/bash
PRODUCT=iwf
CB_LOCK=/etc/.${PRODUCT}/couchbase_monitor.lock 

flock -n $CB_LOCK -c "/opt/diametriq/${PRODUCT}/scripts/couchbase_monitor.sh"
