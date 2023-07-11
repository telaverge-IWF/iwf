#!/bin/bash

flock -n /var/run/iwf_logrotate.lock -c "/opt/diametriq/iwf/scripts/logrotate.sh /opt/diametriq/iwf/config/iwf_logrotate"
