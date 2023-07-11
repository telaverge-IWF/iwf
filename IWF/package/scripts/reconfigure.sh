#!/bin/bash
#this script allows the user to configure/reconfigure the below listed configurations
#1)Ethernet Bonding TODO
#2)TIPC
#3)DRE/DEA Local Host
#4)Alarms
#5)Heartbeat and Mysql Replication
#6)NTP server 
#7)File sync(Rsync)

PRODUCT=iwf
DRE_BASE_PATH=/opt/diametriq/${PRODUCT}

source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh
CONFIG_FILE=""
CONFIG_FLG=0
DRE_CNF_FILE=/opt/diametriq/${PRODUCT}/config/install_${PRODUCT}.cnf

if [ "$PRODUCT" == "iwf" ];then
    DRE_ROOT=$IWF_ROOT
fi

LOCAL_HOST=1
ALARM=2
NTP=3
BONDING=4
MYSQL_HEARTBEAT=5
SIGTRAN=6

# $1 = number
function parse_validate()
{
    case $1 in
	1) parse_localhost_cnf
	   validate_localhost_cnf
	   update_localhost_in_dre_cfg
	    ;;
	2) parse_alarm_cnf $DRE_CNF_FILE 
	   update_alarm_in_dre_cfg

	    ;;
	3) parse_ntp_cnf
	   validate_ntp_cnf
	   update_ntp_in_dre_cfg
	
	    ;;
	4) parse_bonding_from_user_cnf
	   validate_bonding
	   parse_tipc_cnf
	   validate_tipc_cnf 
	   if [ `GetDreInstallMode` != "1" ];then
		parse_mysql_heartbeat_cnf
		validate_mysql_heartbeat_cnf
		update_mysql_heartbeat_in_dre_cfg
 	   fi
	   update_bonding_in_dre_cfg
	   update_tipc_in_dre_cfg
		
	    ;;
	5) parse_mysql_heartbeat_cnf
	   validate_mysql_heartbeat_cnf
	   update_mysql_heartbeat_in_dre_cfg
	
	    ;;
	6)
	   parse_sigtran_config
	   validate_sigtran_config
	   update_sigtrancfg_in_iwfcfg
	
    esac

}

function reconfigure_menu()
{
    PLOG_INFO "Reconfiguration/Configuration menu" $LINENO
    heading "Reconfiguration/Configuration Menu"
    while [ 1 ]
    do
	if [ `check_if_cnf_modified` == "no" ];then
	    PLOG_INFO "-------------------------------------------------------------------------------------" $LINENO
	    PLOG_INFO "Note: Edit the appropriate sections in \"$DRE_CNF_FILE\" and retry." $LINENO
	    PLOG_INFO "-------------------------------------------------------------------------------------" $LINENO
	    exit

	fi
        if [ `GetDreInstallMode` == "1" ];then
	    PLOG_INFO "-------------------------------------------------------------------------------------" $LINENO
	    PLOG_INFO "Note: Edit the appropriate sections in \"$DRE_CNF_FILE\" before selecting any option." $LINENO
	    PLOG_INFO "Note: Save the file \"$DRE_CNF_FILE\"(if edited) before proceeding" $LINENO
	    PLOG_INFO "-------------------------------------------------------------------------------------" $LINENO

	    PLOG_INFO "1.Alarms"	 $LINENO
	    PLOG_INFO "2.NTP Server" $LINENO
	    PLOG_INFO "3.Ethernet Bonding" $LINENO
	    PLOG_INFO "4.Exit" $LINENO
	    CHOICE=`spl_num_check $'Enter choice(number)\t\t:' $'Wrong Choice! Enter valid choice:' "1" "4"`
            case $CHOICE in
                1)  #parse_validate $ALARM
		    #configure_alarms
                    
                    ;;
	        2) parse_validate $NTP  
		   configure_NTP
		    ;;
		3)  parse_validate $BONDING
		    configure_ethernet_bonding
		    configure_tipc_bearer
		    ;;
	   	4)  
		   #/opt/diametriq/${PRODUCT}/scripts/create_user_config.sh
		   exit
            esac
            cp -f $DRE_CONFIG $DRE_ROOT/.syscfg

        
        elif [ `GetDreInstallMode` == "2" ] || [ `GetDreInstallMode` == "3" ] || [ `GetDreInstallMode` == "4" ];then
		PLOG_INFO "-------------------------------------------------------------------------------------" $LINENO
		PLOG_INFO "Note: Edit the appropriate sections in \"$DRE_CNF_FILE\" before selecting any option." $LINENO
		PLOG_INFO "Note: Save the file \"$DRE_CNF_FILE\"(if edited) before proceeding" $LINENO
		PLOG_INFO "-------------------------------------------------------------------------------------" $LINENO

	        PLOG_INFO "1.Alarms"	$LINENO
	        PLOG_INFO "2.Heartbeat and MySQL replication" $LINENO
	        PLOG_INFO "3.NTP Server" $LINENO
	        PLOG_INFO "4.File Sync" $LINENO
		PLOG_INFO "5.Ethernet Bonding" $LINENO
	        PLOG_INFO "6.Exit" $LINENO
            CHOICE=`spl_num_check $'Enter choice(number)\t\t:' $'Wrong Choice! Enter valid choice:' "1" "6"`
            case $CHOICE in
                1)  #parse_validate $ALARM
		    #configure_alarms
                    ;;
                2)  parse_validate $MYSQL_HEARTBEAT
	            configure_heartbeat
                    #call the heartbeat and replication scripts
                    LOG_DEBUG "Calling heartbeat scripts" $LINENO
                    $DRE_BASE_PATH/scripts/heartbeat_ha.sh  
                    if [ $? != 0 ];then
                       LOG_ERROR "Heartbeat configurations failed due to unknown reasons!" $LINENO
	                   exit 1
                    fi


                    $DRE_BASE_PATH/scripts/mysql_ha.sh  
                    $DRE_BASE_PATH/scripts/configCmgr.sh "TCP" `GetMysqlUsername` `GetMysqlPassword` `GetMysqlIpAddress` `GetMysqlPort`

                    ;;
                3)  parse_validate $NTP
		    configure_NTP
                    ;;
                4)  configure_rsync
                    ;;
                5)  parse_validate $BONDING
		    configure_ethernet_bonding
		    configure_tipc_bearer
		    configure_heartbeat
                    #call the heartbeat and replication scripts
                    LOG_DEBUG "Calling heartbeat scripts" $LINENO
                    $DRE_BASE_PATH/scripts/heartbeat_ha.sh  
                    if [ $? != 0 ];then
                       LOG_ERROR "Heartbeat configurations failed due to unknown reasons!" $LINENO
	                   exit 1
                    fi


                    $DRE_BASE_PATH/scripts/mysql_ha.sh  
                    $DRE_BASE_PATH/scripts/configCmgr.sh "TCP" `GetMysqlUsername` `GetMysqlPassword` `GetMysqlIpAddress` `GetMysqlPort`
		    
                    ;;

		6)  
	            #/opt/diametriq/${PRODUCT}/scripts/create_user_config.sh
		    exit
                    ;;
            esac
            cp -f $DRE_CONFIG $DRE_ROOT/.syscfg
        fi
	update_cnf_timestamp	
	#/opt/diametriq/${PRODUCT}/scripts/create_user_config.sh
        exit
    done
    


}


while [ $# -gt 0 ]
do
    case "$1" in
        "--configFile")
                        shift
                        CONFIG_FILE="$1"
			parse_user_dre_cnf_file "$CONFIG_FILE"
                        PLOG_INFO "ConfigFile passed=$CONFIG_FILE" $LINENO
			CONFIG_FLG=1
                    ;;
	"--tipc")
			pgrep ^avamgr >/dev/null
			if [ $? -eq 0 ];then
			    service dre stop
			fi
			check_env
			backup_cnf_file
			log_heading "RECONFIGURATION SCRIPT"
			DRE_CNF_FILE=""
			
			configure_tipc --reconfigure
		    	cd $DRE_BASE_PATH/lib/tipc1* && ./install.sh
		        /opt/diametriq/${PRODUCT}/scripts/create_user_config.sh
			update_cnf_timestamp
			exit                    
    esac
    shift
done

check_env
log_heading "RECONFIGURATION SCRIPT"
backup_cnf_file
reconfigure_menu
backup_cnf_file
#/opt/diametriq/${PRODUCT}/scripts/create_user_config.sh






