#!/bin/bash
source /etc/package_functions.sh

DRE_VER=
IWF_VER=
DRE_BASE=/opt/diametriq
DRE_UNINST_INFO=/etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_uninstall_info
DB_UPGRADE_INFO=/etc/.${S_PRODUCT_NAME}/db_upgrade_info
#source /opt/diametriq/${S_PRODUCT_NAME}/scripts/package_functions.sh

#function to execute the command memc_servers_set while uninstalling
function memc_servers_set_uninstall()
{
    local ip=`GetMysqlIpAddress`
    local username=`GetMysqlUsername`
    local password=`GetMysqlPassword`
    local port=`GetMysqlPort`
    local flag=0

    check_and_start_mysql
    my="mysql  --host=$ip --user=$username --password=$password --port=$port -se"
    ${my} "select memc_servers_set('localhost:11211')"

}

#function to check incompatibility between the current version uninstall script and previous rollback script.
#Previous version script may not be aware of few extra configurations that are done by current version, so this
#function will take care of reverting those changes in case of a rollback
function check_and_revert_cur_version_specific_changes()
{
    local SYS_CFG=/opt/diametriq/${S_PRODUCT_NAME}/.syscfg
    revert_crontab_cfg
    LOG_INFO "Reverting current version specific configurations" $LINENO
    #if previous version does not have mysql upstart then revert back to service script
    if [ -e $DRE_BASE/${S_PRODUCT_NAME}/scripts/.rollback.sh ];then
	  
	 grep "^restore_bonding_cfg" $DRE_BASE/${S_PRODUCT_NAME}/scripts/.rollback.sh >/dev/null
	 if [ $? -ne 0 ];then
	     LOG_DEBUG "Restoring bonding which prev ver is not aware of " $LINENO
	     restore_bonding_cfg $SYS_CFG/bonding
 	 fi

	 grep "^check_and_reconfig_tipc" $DRE_BASE/${S_PRODUCT_NAME}/scripts/.rollback.sh >/dev/null
         if [ $? -ne 0 ];then
	     LOG_DEBUG "Restoring tipc configuration which prev ver is not aware of" $LINENO
	     check_and_reconfig_tipc
	 fi
	if [ "$PRODUCT" == "iwf" ];then
            grep "^restore_heartbeat_cfg" $DRE_BASE/${S_PRODUCT_NAME}/scripts/.rollback.sh >/dev/null
	    if [ $? -ne 0 ];then
	        LOG_DEBUG "Restoring heartbeat which prev ver is not aware of" $LINENO
	        restore_heartbeat_cfg $SYS_CFG/heartbeat
 	    fi
	fi

 	
         grep "^restore_mysqlreplication_cfg" $DRE_BASE/${S_PRODUCT_NAME}/scripts/.rollback.sh >/dev/null
	 if [ $? -ne 0 ];then
	    LOG_DEBUG "Restoring mysql replication which prev version is not aware of" $LINENO
	    restore_mysqlreplication_cfg
	 fi
         grep " service mysql start" $DRE_BASE/${S_PRODUCT_NAME}/scripts/.rollback.sh >/dev/null
	    if [ $? -eq 0 ];then
	        LOG_WARNING "previous version ${S_PRODUCT_NAME} does not have upstart for mysql" $LINENO
	        LOG_DEBUG "Reverting upstart configuration for mysql" $LINENO
	        pgrep mysqld >/dev/null
	        if [ $? -eq 0 ];then
		    PLOG_INFO "Stopping mysqld" $LINENO
		    stop mysqld
	        fi
	        rm -f /etc/init/mysqld.conf
	        chkconfig mysql on
	    fi

    fi
   
    
}



#This function will set the value for a particular field in dre_uninstall_info
#Argument 1 : Field/name in dre_uninstall_info
#Argument 2 : Value to be set 
function Set_dre_uninstall_info()
{
    LOG_DEBUG "function Set_dre_uninstall_info start" $LINENO
    LOG_DEBUG "\$#=$#, \$1=$1 , \$2=$2 " $LINENO
    if [ $# != 2 ];then
	echo "Usage: Set_dre_uninstall_info <field_name> <value>"
        return 1
    fi

    if [ ! -e $DRE_UNINST_INFO ];then
        touch $DRE_UNINST_INFO
    fi
    FIELD_NAME=$1
    VALUE=$2
    RET=0

    if [ "$FIELD_NAME" == "ver" ] || \
       [ "$FIELD_NAME" == "rollbk" ] || \
       [ "$FIELD_NAME" == "cur_ver_dbupgrade_flg" ] || \
       [ "$FIELD_NAME" == "rollbk_ver" ] || \
       [ "$FIELD_NAME" == "rollbk_ver_dbupgrade_flg" ] || \
       [ "$FIELD_NAME" == "db_flush" ];then

        if [ -z `grep $FIELD_NAME $DRE_UNINST_INFO` ];then
            echo "$FIELD_NAME=$VALUE" >> $DRE_UNINST_INFO
	    LOG_DEBUG "Appending $FIELD_NAME=$VALUE to $DRE_UNINST_INFO" $LINENO
        else
            sed -i "s/$FIELD_NAME=.*/$FIELD_NAME=$VALUE/g" $DRE_UNINST_INFO
	    LOG_DEBUG "Replacing $FIELD_NAME=$VALUE in $DRE_UNINST_INFO" $LINENO
        fi

    else
 	LOG_ERROR "Invalid field name $FIELD_NAME" $LINENO
        RET=1
    fi
    LOG_DEBUG "function Set_dre_uninstall_info ending" $LINENO
    return $RET
}

#This function returns the db_upgrade_flg of a particular PRODUCT version .
#Argument : PRODUCT version
#Returns db_upgrade_flg for the PRODUCT version passed
function Get_db_upgrade_info()
{
    LOG_DEBUG "function Get_db_upgrade_info starting" $LINENO
    if [ $# != 1 ];then
	echo "Usage: Get_db_upgrade_info <ver>"
	LOG_ERROR " \$#=$# : Usage: Get_db_upgrade_info <ver>" $LINENO
	return 1
    fi
    LOG_DEBUG "\$#=$#, \$1=$1" $LINENO
    
    sed -n s/^$1=//p $DB_UPGRADE_INFO
}

function stop_dre_service()
{
    pgrep ^avamgr > /dev/null
    if [ $? == 0 ];then
#LOG_INFO "Stopping ${S_PRODUCT_NAME} service before uninstall/rollback..." $LINENO
#service ${S_PRODUCT_NAME} stop
        LOG_INFO "Stopping dre service before uninstall/rollback..." $LINENO
        service dre stop
    fi

}

function save_mysql_dump()
{
    check_and_start_mysql  
    LOG_DEBUG "function save_mysql_dump start" $LINENO
    MysqlUsername=$( GetMysqlUsername )
    LOG_INFO "MysqlUsername=$MysqlUsername"  $LINENO
    MysqlPassword=$( GetMysqlPassword )
    LOG_INFO "MysqlPassword=$MysqlPassword" $LINENO
    MysqlIpAddress=$( GetMysqlIpAddress )
    LOG_INFO "MysqlIpAddress=$MysqlIpAddress" $LINENO
    MysqlPort=$( GetMysqlPort )
    LOG_INFO "MysqlPort=$MysqlPort" $LINENO


    MYSQL_DUMP_FILE="mysql_dump_"
    DATE=`date | tr -s " " | tr " " "_"`
    MYSQL_DUMP_FILE=$MYSQL_DUMP_FILE$DATE".sql"
    PLOG_INFO "Mysql dump file= $MYSQL_DUMP_FILE" $LINENO
    #take mysql dump for rollback procedure
    PLOG_INFO "Creating mysql dump..." $LINENO
    mysqldump --host=$MysqlIpAddress --user=$MysqlUsername --password=$MysqlPassword --port=$MysqlPort --databases DIAMETRIQ >> $MYSQL_DUMP_FILE
    if [ $? -ne 0 ];then
        PLOG_ERROR "Mysql dump failed" $LINENO
	return 1 
    fi
    PLOG_INFO "Saving mysql dump in $1..." $LINENO
    mv $MYSQL_DUMP_FILE $1

    LOG_DEBUG "function save_mysql_dump end" $LINENO
    check_and_stop_mysql
}


if [ `id -u` -ne 0 ]; then
    echo "Run as root"
    exit 1
fi

if [ "$PWD" == "/opt/diametriq/${S_PRODUCT_NAME}" ] || [ "$PWD" == "/opt/diametriq/${S_PRODUCT_NAME}/bin" ];then
    LOG_WARNING "User executing uninstall inside /opt/diametriq/${S_PRODUCT_NAME}" $LINENO
    PLOG_INFO "Cannot execute \"uninstall_${S_PRODUCT_NAME}.sh\" script inside \"/opt/diametriq/${S_PRODUCT_NAME}\"" $LINENO
    PLOG_INFO "Move out of \"/opt/diametriq/${S_PRODUCT_NAME}\" directory and retry!" $LINENO
    exit 1
fi
if [ "$PRODUCT" == "iwf" ];then
    #if heartbeat is running stop it
    #this step is because ,in standby machine if active mysql is running we have to switch 
    #active mysql to active machine 
    pgrep heartbeat >/dev/null
    if [ $? -eq 0 ];then
        kill_heartbeat &
        service heartbeat stop
    fi
fi



if [ $# == 1 ];then
    #this if block is for the rollback in case of post script installation failure
    PLOG_INFO " Rolling back..." $LINENO
    LOG_DEBUG "Rollback is due to failure while installing" $LINENO
    #find out if previous version of PRODUCT is present for rollback
    if [ `rpm -q ${S_PRODUCT_NAME}|wc -l` -gt 1 ];then
        ROLLBACK_VERSION=`rpm -q ${S_PRODUCT_NAME}|tail -2|head -1`
	LOG_DEBUG "Rollback version = $ROLLBACK_VERSION" $LINENO
        ROLLBACK_VERSION=${ROLLBACK_VERSION%*.*}
        LOG_DEBUG "Rollback version directory= $ROLLBACK_VERSION" $LINENO
        ROLLBK_DEP_LIST=/opt/diametriq/$ROLLBACK_VERSION/.syscfg/$ROLLBACK_VERSION"_dep.txt"
    else
	ROLLBACK_VERSION=""
    fi

    if [ $S_PRODUCT_NAME = "dre" ];then
        rpm -e $DRE_VER
    fi

    if [ $S_PRODUCT_NAME = "iwf" ];then
        rpm -e $IWF_VER
    fi

    cd $DRE_BASE

    if [ $S_PRODUCT_NAME = "dre" ];then
        rm -rf $DRE_VER
    fi

    if [ $S_PRODUCT_NAME = "iwf" ];then
        rm -rf $IWF_VER
    fi

    #if a previous version is available rollback to it
    cd $DRE_BASE
    rm -f ${S_PRODUCT_NAME} 
    LOG_DEBUG "Rollback version = $ROLLBACK_VERSION" $LINENO
    if [ -n "$ROLLBACK_VERSION" ];then
        PLOG_INFO "Rolling back to $ROLLBACK_VERSION" $LINENO
        ln -s $ROLLBACK_VERSION $DRE_BASE${S_PRODUCT_NAME}/
	 cp $DRE_BASE/${S_PRODUCT_NAME}/.syscfg/${S_PRODUCT_NAME}.cfg /etc/ 1>/dev/null
	 LOG_DEBUG "Before copy: `cat /etc/my.cnf`" $LINENO
   	check_and_stop_mysql
         mv /etc/my.cnf /etc/my.cnfbk

        cp -f $DRE_BASE/${S_PRODUCT_NAME}/.syscfg/my.cnf /etc
        /opt/diametriq/${S_PRODUCT_NAME}/scripts/validate_my_cnf_file.sh
        check_and_start_mysql
        cp $DRE_BASE/${S_PRODUCT_NAME}/.syscfg/${S_PRODUCT_NAME}.cfg /etc/ 1>/dev/null
 	#call the function which takes care of version specific change	
        check_and_revert_cur_version_specific_changes	

	    cd $DRE_BASE/${S_PRODUCT_NAME}/scripts && if [ -e .rollback.sh ];then ./.rollback.sh; 
        else PLOG_INFO "No rollback support in $ROLLBACK_VERSION, rollback failed!" $LINENO ;
	    exit 1
        fi
	    check_and_start_3rdparty_proccesses
	    if [ "`GetDreInstallMode`" == "2" ] || [ `GetDreInstallMode` == "3" ] || [ `GetDreInstallMode` == "4" ];then
	        LOG_INFO "restarting network service..." $LINENO
	        restart_network	
	    fi
   	    PLOG_INFO "Successfully rolledback to $ROLLBACK_VERSION !" $LINENO
    else
        PLOG_INFO "Uninstall Successful" $LINENO
    fi
 


else
    begin_uninstall

    if [ $S_PRODUCT_NAME = "dre" ];then
        LOG_DEBUG "DRE_VER=$DRE_VER" $LINENO
    fi

    if [ $S_PRODUCT_NAME = "iwf" ];then
        LOG_DEBUG "IWF_VER=$IWF_VER" $LINENO
    fi

    #Empty the dre_uninstall_info file if found
    if [ -e $DRE_UNINST_INFO ];then
        >$DRE_UNINST_INFO
    fi
    #find out if previous version of PRODUCT is present for rollback
    if [ `rpm -q ${S_PRODUCT_NAME}|wc -l` -gt 1 ];then
        ROLLBACK_VERSION=`rpm -q ${S_PRODUCT_NAME}|tail -2|head -1`
	    LOG_DEBUG "Rollback version = $ROLLBACK_VERSION" $LINENO
        ROLLBACK_VERSION=${ROLLBACK_VERSION%*.*}
        LOG_DEBUG "Rollback version directory= $ROLLBACK_VERSION" $LINENO
        ROLLBK_DEP_LIST=/opt/diametriq/$ROLLBACK_VERSION/.syscfg/$ROLLBACK_VERSION"_dep.txt"
	    if [ -e $ROLLBK_DEP_LIST ];then
            LOG_DEBUG "Dependency list for $ROLLBACK_VERSION: `cat $ROLLBK_DEP_LIST`" $LINENO
            #check the dependecies for Rollback version, if all dependencies are not installed, Halt the uninstall/rollback
            PLOG_INFO "checking dependencies for $ROLLBACK_VERSION..." $LINENO
            check_dependencies $ROLLBK_DEP_LIST
	    fi
    else
	    ROLLBACK_VERSION=""
        #disable backup and recovery if its enabled
	    if [ "$PRODUCT" == "dre" ];then
                disable_backup_recovery
 	    fi
	    #clean couchbase configuration during uninstall
	    #delete the buckets and stop couchbase-server
	    if [ "`GetDreInstallMode`" == "4" ];then
		    stop_dre_service
	        clean_couchbase
        fi
    fi

    if [ $S_PRODUCT_NAME = "dre" ];then
        CFG_BKP=`echo "$DRE_VER"`
    fi

    if [ $S_PRODUCT_NAME = "iwf" ];then
        CFG_BKP=`echo "$IWF_VER"`
    fi


    mkdir -p $DRE_BASE/${S_PRODUCT_NAME}_config_bkp/$CFG_BKP
    cp -rf $DRE_BASE/${S_PRODUCT_NAME}/config $DRE_BASE/${S_PRODUCT_NAME}_config_bkp/$CFG_BKP
    cp -rf $DRE_BASE/${S_PRODUCT_NAME}/.syscfg $DRE_BASE/${S_PRODUCT_NAME}_config_bkp/$CFG_BKP
    save_mysql_dump $DRE_BASE/${S_PRODUCT_NAME}_config_bkp/$CFG_BKP
    PLOG_INFO "Config backup created at $DRE_BASE/${S_PRODUCT_NAME}_config_bkp/$CFG_BKP" $LINENO
    stop_dre_service

    if [ $S_PRODUCT_NAME = "dre" ];then
        rpm -e $DRE_VER
    fi

    if [ $S_PRODUCT_NAME = "iwf" ];then
        rpm -e $IWF_VER
    fi


    cd $DRE_BASE

    if [ $S_PRODUCT_NAME = "dre" ];then
        rpm -e $DRE_VER
        rm -rf $DRE_VER
    fi

    if [ $S_PRODUCT_NAME = "iwf" ];then
        rm -rf $IWF_VER
    fi



    #if a previous version is available rollback to it
    cd $DRE_BASE
    if [ $S_PRODUCT_NAME == "dre" ];then
        rm -f dre
    fi
    
    if [ $S_PRODUCT_NAME == "iwf" ];then
        rm -f iwf
    fi
    LOG_DEBUG "Rollback version = $ROLLBACK_VERSION" $LINENO
    if [ -n "$ROLLBACK_VERSION" ];then
        PLOG_INFO "Rolling back to $ROLLBACK_VERSION" $LINENO
        ln -s $ROLLBACK_VERSION $DRE_BASE/${S_PRODUCT_NAME}
        cp $DRE_BASE/${S_PRODUCT_NAME}/.syscfg/${S_PRODUCT_NAME}.cfg /etc/ 1>/dev/null
        check_and_stop_mysql
	LOG_DEBUG "Before copy: `cat /etc/my.cnf`" $LINENO
        mv /etc/my.cnf /etc/my.cnfbk

        cp -f $DRE_BASE/${S_PRODUCT_NAME}/.syscfg/my.cnf /etc
        /opt/diametriq/${S_PRODUCT_NAME}/scripts/validate_my_cnf_file.sh
        check_and_start_mysql
 	#call the function which takes care of version specific change	
        check_and_revert_cur_version_specific_changes	
	    cd $DRE_BASE/${S_PRODUCT_NAME}/scripts && if [ -e .rollback.sh ];then ./.rollback.sh; 
        else PLOG_INFO "No rollback support in $ROLLBACK_VERSION, rollback failed!" $LINENO ;
	    exit 1
        fi

        if [ $S_PRODUCT_NAME = "dre" ];then
	        Set_dre_uninstall_info "ver" "$DRE_VER"
        fi

        if [ $S_PRODUCT_NAME = "iwf" ];then
	        Set_dre_uninstall_info "ver" "$IWF_VER"
        fi

	    Set_dre_uninstall_info "rollbk" "yes"
	    Set_dre_uninstall_info "rollbk_ver" "$ROLLBACK_VERSION"
	
        if [ $S_PRODUCT_NAME = "dre" ];then
	        Set_dre_uninstall_info "cur_ver_dbupgrade_flg" `Get_db_upgrade_info "$DRE_VER"`
        fi

        if [ $S_PRODUCT_NAME = "iwf" ];then
	        Set_dre_uninstall_info "cur_ver_dbupgrade_flg" `Get_db_upgrade_info "$IWF_VER"`
        fi


	    Set_dre_uninstall_info "rollbk_ver_dbupgrade_flg" `Get_db_upgrade_info "$ROLLBACK_VERSION"`
   	    check_and_start_3rdparty_proccesses
            if [ "`GetDreInstallMode`" == "2" ] || [ `GetDreInstallMode` == "3" ] || [ `GetDreInstallMode` == "4" ];then
	        LOG_INFO "restarting network service..." $LINENO
	        restart_network	
	    fi

        if [ "$S_PRODUCT_NAME" == "dre" ];then
	        memc_servers_set  
        fi
        #disable unwanted process for iwf
        disable_processes    
        PLOG_INFO "Successfully rolledback to $ROLLBACK_VERSION !" $LINENO
    else
	#this code block is for uninstalling the last PRODUCT in the system
	#check if user wants to delete the db 
        if [ $S_PRODUCT_NAME = "dre" ];then
	        read -p "Do you want to retain the database during the next reinstall($DRE_VER)?:[yes/no]: " ch
        fi

        if [ $S_PRODUCT_NAME = "iwf" ];then
	        read -p "Do you want to retain the database during the next reinstall($IWF_VER)?:[yes/no]: " ch
        fi


        while [ 1 ]
        do
            LOG_DEBUG "Choice = $ch " $LINENO
            if [ $ch == "yes" -o $ch == "no" ];then
                break
            else
                PLOG_INFO echo "Invalid Choice!" $LINENO
                read -p "[yes/no] : " ch

            fi

        done
	    if [ "$ch" == "no" ];then
	        LOG_DEBUG "db_flush=yes" $LINENO
	        Set_dre_uninstall_info "db_flush" "yes"
             #Drop DIAMETRIQ databases
             drop_databases
	    else
	        LOG_DEBUG "db_flush=no" $LINENO
	        Set_dre_uninstall_info "db_flush" "no"
	    fi

        if [ $S_PRODUCT_NAME = "dre" ];then
            Set_dre_uninstall_info "ver" "$DRE_VER"
        fi

        if [ $S_PRODUCT_NAME = "iwf" ];then
            Set_dre_uninstall_info "ver" "$IWF_VER"
        fi

        Set_dre_uninstall_info "rollbk" "no"

        if [ $S_PRODUCT_NAME = "dre" ];then
	        Set_dre_uninstall_info "cur_ver_dbupgrade_flg" `Get_db_upgrade_info "$DRE_VER"`
        fi

        if [ $S_PRODUCT_NAME = "iwf" ];then
	        Set_dre_uninstall_info "cur_ver_dbupgrade_flg" `Get_db_upgrade_info "$IWF_VER"`
        fi



 	    revert_crontab_cfg
        revert_iptable_rules	
	#if PRODUCT mode is active standby revert the heartbeat and mysql replication
	#configurations while uninstalling
        if [ "`GetDreInstallMode`" == "2" ] || [ `GetDreInstallMode` == "3" ] || [ `GetDreInstallMode` == "4" ];then\
	    #if [ "$PRODUCT" == "iwf" ];then
        #        PLOG_INFO "Reverting heartbeat config..." $LINENO
        #        revert_heartbeat_cfg "$DRE_BASE/${S_PRODUCT_NAME}_config_bkp/$CFG_BKP/config/heartbeat"
	    #fi
	    PLOG_INFO "Reverting mysql replication config..." $LINENO
	    revert_mysql_replication_cfg
	fi
        #disable unwanted process for iwf
        disable_processes
        PLOG_INFO "Uninstall Successful" $LINENO
    fi
 
        
fi
