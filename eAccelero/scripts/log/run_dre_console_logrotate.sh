#!/bin/bash

flock -n /var/run/dre_console_logrotate.lock -c "/opt/diametriq/dre/scripts/logrotate.sh /opt/diametriq/dre/config/dre_console_logrotate"
