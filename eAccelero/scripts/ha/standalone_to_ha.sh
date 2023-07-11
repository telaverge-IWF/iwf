#!/bin/sh

PRODUCT=iwf
source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh

MYSQL_CONFIG_FILE=/etc/my.cnf

if [ "$PRODUCT" == "dre" ];then
    SYSCONFIG_DRE=/etc/sysconfig/dre
    DRE_ROOT=/opt/diametriq/dre
elif [ "$PRODUCT" == "iwf" ];then
    SYSCONFIG_DRE=/etc/sysconfig/iwf
    DRE_ROOT=/opt/diametriq/iwf
fi



CONFIG_FILE=/opt/diametriq/${PRODUCT}/config/install_${PRODUCT}.cnf

function check_already_dre_isactive()
{
    if [ ! -e $SYSCONFIG_DRE ];then
        #PLOG_ERROR "$SYSCONFIG_DRE does not exist" $LINENO
        return 1
    fi

    MODE=`cat $SYSCONFIG_DRE  | grep BASICOPTS | tr -s " " | tr "\"" " "|cut -d " " -f 8`

    if [ "$MODE" == "3" ];then
        PLOG_INFO "$SYSCONFIG_DRE ${PRODUCT} is configured as cold-standby" $LINENO
	return 1
    elif [ "$MODE" == "1" ];then
        PLOG_INFO "$SYSCONFIG_DRE ${PRODUCT} is not configured as standlone" $LINENO
	return 0
    fi
		
}

function configure_heartbeat_mysql_replication()
{

	if [ "`GetDreInstallMode`" == 2 ] || [ "`GetDreInstallMode`" == 3 ] || [ "`GetDreInstallMode`" == 4 ];then
	    LOG_DEBUG "Calling heartbeat scripts" $LINENO
	    $DRE_ROOT/scripts/heartbeat_ha.sh  
            if [ $? != 0 ];then
                #in case of error ,setting state of installation in tmp file since post script always returns 0
	        LOG_ERROR "Setting \"failure\" in /tmp/.${PRODUCT}_install_state" $LINENO
                echo "failure" >/tmp/.${PRODUCT}_install_state
                PLOG_ERROR "Invalid heartbeat configuration!" $LINE
                exit 1
            fi

	    $DRE_ROOT/scripts/mysql_ha.sh  
	fi
}

check_env
log_heading "STANDALONE_TO_HA"
check_already_dre_isactive

if [ $? -eq 1 ];then
	echo "Dre is already configured as cold-standby"
	exit 1
fi
if [ `check_if_cnf_modified` == "no" ];then
    PLOG_INFO "-------------------------------------------------------------------------------------" $LINENO
    PLOG_INFO "$CONFIG_FILE is not modified!" $LINENO
    PLOG_INFO "Configure the following sections in $CONFIG_FILE and retry!" $LINENO
    PLOG_INFO "1) install_mode (supported mode:3)" $LINENO
    PLOG_INFO "2) [bonding] section" $LINENO
    PLOG_INFO "3) [tipc] section" $LINENO
    PLOG_INFO "4) [local_host] section" $LINENO
    PLOG_INFO "5) [mysql_heartbeat] section" $LINENO

    PLOG_INFO "-------------------------------------------------------------------------------------" $LINENO
    exit
fi

PLOG_INFO "Configure the following sections in $CONFIG_FILE " $LINENO
PLOG_INFO "1) install_mode (supported mode:3)" $LINENO
PLOG_INFO "2) [bonding] section" $LINENO
PLOG_INFO "3) [tipc] section" $LINENO
PLOG_INFO "4) [local_host] section" $LINENO
PLOG_INFO "5) [mysql_heartbeat] section" $LINENO
PLOG_INFO "Note: configure and save the file $CONFIG_FILE before proceeding" $LINENO  

echo "This action will upgrade ${PRODUCT} from standlone mode to ha mode "
read -p "Due you want to continue [y/n] [y] " choice
choice=${choice:-y}
echo $choice

if [ "$choice" = "n" ];then
	exit 0
fi

#backup_cnf_file
echo "config=$CONFIG_FILE"
if [ -e /etc/${PRODUCT}.cfg ];then
    cp -f /etc/${PRODUCT}.cfg /etc/${PRODUCT}.cfg`date +%s`
fi

#parse install_mode
#parse bonding configurations
#parse tipc configurations 
#parse localhost configurations 
#parse mysql heartbeat configurations

parse_validate_cnf_for_HA  $CONFIG_FILE
# set the DRE_CNF_FILE which will avoid asking console input for configurations
# and take it from /etc/dre.cfg which is parsed and set in the prev line
DRE_CNF_FILE="$CONFIG_FILE"

pgrep ^avamgr > /dev/null
if [ $? -eq 0 ];then
   LOG_DEBUG "Stopping dre..." $LINENO
   service dre stop
fi

#set dre mode to 2 in dre.cfg
set_dre_cfg "DreInstallMode" "3"
uncommand_my_cnf_for_activestandby
cp -f $MYSQL_CONFIG_FILE $DRE_ROOT/.syscfg


configure_ethernet_bonding
configure_tipc_bearer
configure_localhost
$DRE_ROOT/scripts/install.sh --reinstall
$DRE_ROOT/scripts/configCmgr.sh "TCP" `GetMysqlUsername` `GetMysqlPassword` `GetMysqlIpAddress` `GetMysqlPort`
cp $DRE_MYSQL_SERVER_CONFDIR/mysql.cfg $DRE_ROOT/.syscfg
cp -f $DRE_CONFIG $DRE_ROOT/.syscfg

configure_heartbeat
configure_heartbeat_mysql_replication #local function
configure_rsync
set_dre_mode
$DRE_ROOT/scripts/configCmgr.sh "TCP" `GetMysqlUsername` `GetMysqlPassword` `GetMysqlIpAddress` `GetMysqlPort`
cp -f $DRE_MYSQL_SERVER_CONFDIR/mysql.cfg $DRE_ROOT/.syscfg
cp -f $DRE_CONFIG $DRE_ROOT/.syscfg
copy_dre_cnf
PLOG_INFO "SUCCESSFULLY UPGRADED TO COLD-STANDBY" $LINENO
update_cnf_timestamp
backup_cnf_file
