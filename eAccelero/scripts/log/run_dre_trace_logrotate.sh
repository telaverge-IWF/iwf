#!/bin/bash

flock -n /var/run/dre_trace_logrotate.lock -c "/opt/diametriq/dre/scripts/logrotate.sh /opt/diametriq/dre/config/dre_trace_logrotate"
