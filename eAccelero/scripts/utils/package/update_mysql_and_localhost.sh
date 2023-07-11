#this script is allow the user to update the mysql authentication details
#and local host configuration details after an upgrde
PRODUCT=iwf
source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh
LOG_INFO "Updating mysql authentication and localhost details" $LINENO
enter_configuration
if [ $PRODUCT = "dre" ];then
    $DRE_ROOT/${PRODUCT}/scripts/install.sh --reinstall
fi

if [ $PRODUCT = "iwf" ];then
    $IWF_ROOT/${PRODUCT}/scripts/install.sh --reinstall
fi

if [ $? -eq 0 ];then
    PLOG_INFO "Update successful!" $LINENO
    #update the mysql.cfg as well
    $DRE_ROOT/scripts/configCmgr.sh "TCP" `GetMysqlUsername` `GetMysqlPassword` `GetMysqlIpAddress` `GetMysqlPort`
    cp $DRE_MYSQL_SERVER_CONFDIR/mysql.cfg $DRE_ROOT/.syscfg
    cp -f $DRE_CONFIG $DRE_ROOT/.syscfg
else
    PLOG_ERROR "Update failed!" $LINENO
fi
