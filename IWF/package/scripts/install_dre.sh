PRODUCT=iwf
DRE_CONFIG=/etc/${PRODUCT}.cfg


function clean_up()
{
    #TODO All the cleanup activities of this script
    LOG_ERROR "Installation termintated in between!" $LINENO
    exit 
}

trap clean_up SIGHUP SIGINT SIGTERM



MYSQL_SERVER=MySQL-Cluster-server-gpl-7.2.8-1.el6.x86_64
MYSQL_CLIENT=MySQL-Cluster-client-gpl-7.2.8-1.el6.x86_64
MYSQL_SHARED=MySQL-Cluster-shared-gpl-7.2.8-1.el6.x86_64
APACHE_TOMCAT=apache-tomcat-7.0*
JRE=jre-1.7*
MEMCACHED=memcached-1.4.4-3
LKSCTP_TOOLS=lksctp-tools-1.0*
NET_SNMP=net-snmp
PCRE=pcre
function setMysqlPassword()
{
    service mysql start
    if [ $? != 0 ]; then
        pkill -9 mysqld
        mysql_install_db
        /etc/init.d/mysql restart
    fi
    echo -e "${bldblu}Set Mysql Password${txtrst}"
    NewMysqlPass=`silent_null_check "Password      :" "Password(should not be null) :"`
    mysqladmin -u root password $NewMysqlPass
    if [ $? != 0 ];then
        echo "Password already set!"        
    fi    

}


function CheckDependencies()
{
    LOG_DEBUG "function CheckDependencies starting" $LINENO
    LOG_INFO  "Checking Dependencies..." $LINENO
    cd ./System    
    FILES=`ls`
    for FILE in $FILES
    do
        STRIP=${FILE%*.*}
        rpm -qa | grep $STRIP
        if [ $? != 0 ]; then
            rpm -ivh $FILE
            if [ $? != 0 ]; then
                PLOG_ERROR "$FILE could not be installed!" $LINENO
                exit 1
            else
                #check if mysql-cluster-server is installed  
                #if yes , configure its password
                PLOG_INFO "$FILE installed successfully!" $LINENO
                if [ $FILE == $MYSQL_SERVER ];then
                    setMysqlPassword
                fi
            fi
        fi
    done

}

function CheckPrerequisites
{
    echo "Checking dependencies..."
    FLAG=0
    rpm -qa|grep $MYSQL_SERVER
    if [ $? != 0 ];then
        echo -e "${bldred}$MYSQL_SERVER not installed!${txtrst}"
        FLAG=1
    fi
    rpm -qa|grep $MYSQL_CLIENT
    if [ $? != 0 ]; then
        echo -e "${bldred}$MYSQL_CLIENT not installed!${txtrst}"
        FLAG=1
    fi
    rpm -qa|grep $MYSQL_SHARED
    if [ $? != 0 ];then
        echo -e "${bldred}$MYSQL_SHARED not installed!${txtrst}"
        FLAG=1
    fi
    rpm -qa|grep $APACHE_TOMCAT
    if [ $? != 0 ];then
        echo -e "${bldred}$APACHE_TOMCAT not installed!${txtrst}"
        FLAG=1
    fi
    rpm -qa|grep $JRE
    if [ $? != 0 ];then 
        echo -e "${bldred}$JRE not installed!${txtrst}"
        FLAG=1
    fi

    rpm -qa|grep $NET_SNMP
    if [ $? != 0 ];then
        echo -e "${bldred}$NET_SNMP not installed!${txtrst}"
        FLAG=1
    fi

    rpm -qa|grep $PCRE
    if [ $? != 0 ];then
        echo -e "${bldred}$PCRE not installed!${txtrst}"
        FLAG=1
    fi
    if [ $FLAG == 1 ];then
        echo "Install the above dependencies and try again"
        exit 1
    fi

    if [ ! -d /etc/.${PRODUCT} ];then
	mkdir  /etc/${PRODUCT}.
    fi
}






function GetMysqlUsername()
{
    sed -n s/MysqlUsername=//p $DRE_CONFIG
}

function GetMysqlPassword()
{
    sed -n s/MysqlPassword=//p $DRE_CONFIG
}

function GetMysqlIpAddress()
{
    sed -n s/MysqlIpAddress=//p $DRE_CONFIG
}

function GetMysqlPort()
{
    sed -n s/MysqlPort=//p $DRE_CONFIG
}

function CreateMysqlDump()
{
    LOG_DEBUG "function CreateMysqlDump starting" $LINENO
    if [ ! -d /opt/diametriq/${PRODUCT} ] || [ -z `rpm -q ${PRODUCT}|grep -v "not installed"|tail -1 2>/dev/null` ] ;then
	PLOG_INFO "Mysql dump not required.." $LINENO
        return 0
    fi
    PLOG_INFO "Checking if mysql is running" $LINENO
    LOG_DEBUG "pgrep mysqld = `pgrep mysqld`" $LINENO
    pgrep mysqld >/dev/null
    if [ $? -eq 0 ];then
	LOG_INFO "Stopping mysql..." $LINENO
	stop mysqld
        LOG_DEBUG "pgrep mysqld = `pgrep mysqld`" $LINENO
	pgrep mysqld >/dev/null
        if [ $? -eq 0 ];then
	    PLOG_WARNING "Mysql still running.." $LINENO
	    PLOG_INFO "So killing..." $LINENO
	    pkill -9 mysqld
  	   
	fi
    fi
    LOG_DEBUG "pgrep mysqld = `pgrep mysqld`" $LINENO
    pgrep mysqld >/dev/null
    if [ $? -ne 0 ];then
        PLOG_INFO "Starting Mysql..." $LINENO
	    start mysqld
        check_mysql
        LOG_DEBUG "pgrep mysqld = `pgrep mysqld`" $LINENO
	pgrep mysqld >/dev/null
        if [ $? != 0 ]; then
            PLOG_ERROR "Mysql is not installed" $LINENO
            exit 1
        else
           PLOG_INFO "Mysql is up and running" $LINENO

        fi
    else
	PLOG_INFO "Mysql already running..." $LINENO
    fi 
    MysqlUsername=$( GetMysqlUsername )
    LOG_INFO "MysqlUsername=$MysqlUsername" $LINENO
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
    PLOG_INFO "Saving mysql dump..." $LINENO
    mv $MYSQL_DUMP_FILE /opt/diametriq/${PRODUCT}/.syscfg/ >/dev/null
    LOG_DEBUG "function CreateMysqlDump end" $LINENO
}



function temp_function()
{
#code to handle upstart migration of 3rd party processes
#can be removed in future releases
    pgrep memcached 1>/dev/null
    if [ $? -eq 0 ];then
        pkill -9 memcached
    fi
    pgrep apache-tomcat 1>/dev/null
    if [ $? -eq 0 ];then
        pkill -9 apache-tomcat
    fi
     
    pgrep mysqld 1>/dev/null
    if [ $? -eq 0 ];then
	pkill -9 mysqld
    fi

}

if [ `id -u` -ne 0 ]; then
    echo "Run as root"
    exit 1
fi
source ./package_functions.sh
cp ./package_functions.sh /etc/
CONFIG_FILE=""
UPGRADE_FLG="no"
begin_install
VALID_ARGS="--configFile --upgrade"
SKIP_ARG=0
#check if there are is a PRODUCT already installed
#if yes then set the UPGRADE_FLG to yes
i=0
DRE_BIN_PATH="$0"
args="$*"
for arg in $args
do
    LOG_INFO "--- $arg---" $LINENO
    VALID_ARG_FLG=0
    if [ $SKIP_ARG -eq 1 ];then
	SKIP_ARG=0
	continue
    fi
    for check in $VALID_ARGS
    do
	LOG_INFO "check $arg in $VALID_ARGS" $LINENO
        if [ "$check" == "$arg" ];then
	    VALID_ARG_FLG=1
	    LOG_INFO "FOUND $arg breaking" $LINENO
	    break;
	fi	
    done
    if [ $VALID_ARG_FLG -eq 0 ];then
	PLOG_INFO "Invalid argument \"$arg\"!" $LINENO
	rpm -qa|grep "^${PRODUCT}-[0-9].*" >/dev/null
        if [ $? -eq 0 ];then
	    LOG_INFO "Usage: $DRE_BIN_PATH --upgrade" $LINENO
	else
	    LOG_INFO "Usage: $DRE_BIN_PATH --configFile install_${PRODUCT}.cnf" $LINENO
	fi

	exit
    fi

    if [ "$arg" == "--configFile" ];then
	rpm -qa|grep "^${PRODUCT}-[0-9].*" >/dev/null
        if [ $? -eq 0 ];then
	    PLOG_INFO "config file input not supported while upgrade!" $LINENO
	    exit 1
	fi
	SKIP_ARG=1
        continue
    fi
    if [ "$arg" == "--upgrade" ];then
	#ignore the --upgrade flag if its the first PRODUCT being installed
	rpm -qa|grep "^${PRODUCT}-[0-9].*" >/dev/null
 	if [ $? -ne 0 ];then
	    LOG_DEBUG "No previous ${PRODUCT} found , ignoring the upgrade flag passed" $LINENO
	    UPGRADE_FLG="no"    
	else
            UPGRADE_FLG="yes"
	    LOG_DEBUG "Upgrade flag is passed as an argument" $LINENO
	    LOG_DEBUG "Setting UPGRADE_FLG=yes" $LINENO
	fi
    fi
done


rpm -qa|grep "^${PRODUCT}-[0-9].*" >/dev/null
if [ $? -eq 0 ];then 

    if [ $PRODUCT = "dre" ];then
        if [ "`get_cur_dre_version`" == "`echo $CUR_DRE_VER |cut -d'_' -f1`" ];then
	        PLOG_INFO "$CUR_DRE_VER is already installed!" $LINENO
	        exit 
        fi
    fi

    if [ $PRODUCT = "iwf" ];then
        if [ "`get_cur_dre_version`" == "`echo $CUR_IWF_VER |cut -d'_' -f1`" ];then
	        PLOG_INFO "$CUR_IWF_VER is already installed!" $LINENO
	        exit 
        fi
    fi


    if [ "$UPGRADE_FLG" == "no" ];then
        if [ $PRODUCT = "dre" ];then
            ch=`yes_no_check "Upgrading ${PRODUCT} to $CUR_DRE_VER..Do You Want to continue?:[yes/no] :"`
        fi

        if [ $PRODUCT = "iwf" ];then
            ch=`yes_no_check "Upgrading ${PRODUCT} to $CUR_IWF_VER..Do You Want to continue?:[yes/no] :"`
        fi
       
        if [ "$ch" == "no" ];then
            if [ $PRODUCT = "dre" ];then
	            LOG_DEBUG "User does not want to upgrade to $CUR_DRE_VER" $LINENO
            fi

            if [ $PRODUCT = "iwf" ];then
	            LOG_DEBUG "User does not want to upgrade to $CUR_IWF_VER" $LINENO
            fi

	        exit
        fi
        UPGRADE_FLG="yes"
        LOG_DEBUG "Upgrade flag is not passed but there is a ${PRODUCT} already in the system" $LINENO
        LOG_DEBUG "Setting UPGRADE_FLG=yes" $LINENO
    fi
elif [ $# -ne 2 ];then
    #if configuration file is not passed for installation exit
    PLOG_INFO "Installation configuration file should be passed!" $LINENO
    PLOG_INFO "Usage: <${PRODUCT}_binary> --configFile install_iwf.cnf" $LINENO
    exit
fi


#check if the upgrade_database.sh script is uptodate
if [ "$UPGRADE_FLG" == "yes" ];then
    LOG_DEBUG "Checking if db upgrade is possible..." $LINENO
    cat ./upgrade_database.sh|grep "^PREV_"|grep  "`get_cur_dre_version`" >>/var/log/${PRODUCT}/package.log
    if [ $? -ne 0 ];then
        if [ $PRODUCT = "dre" ];then
            PLOG_ERROR "Upgrade not supported from `get_cur_dre_version` to $CUR_DRE_VER / Database upgrade script not upto date!" $LINENO
        fi  

        if [ $PRODUCT = "iwf" ];then
            PLOG_ERROR "Upgrade not supported from `get_cur_dre_version` to $CUR_IWF_VER / Database upgrade script not upto date!" $LINENO
        fi  

        exit 1
    else
        LOG_DEBUG "Upgrade is possible" $LINENO
    fi

else
    if [ -e /etc/${PRODUCT}.cfg ];then
        LOG_DEBUG "Truncating /etc/${PRODUCT}.cfg file" $LINENO >  /etc/${PRODUCT}.cfg
    fi
fi
mv -f ./memcached.conf /etc/init
mv -f ./snmpd.conf /etc/init
mv -f ./apache-tomcat.conf /etc/init
mv -f ./incrond.conf /etc/init
mv -f ./mysqld.conf /etc/init
mv -f ./pre-${PRODUCT}.conf /etc/init
chkconfig mysql off

while [ $# -gt 0 ]
do
    case "$1" in
        "--configFile")
                        shift
                        CONFIG_FILE="$1"
                        echo "$1"|grep "^/"
			if [ $? -ne 0 ];then
			    CONFIG_FILE="../$CONFIG_FILE"
			    if [ "$UPGRADE_FLG" == "yes" ];then
			        parse_user_dre_cnf_file "$CONFIG_FILE" "--upgrade"
				LOG_DEBUG "Upgrade flag is set, passing --upgrade to parse_user_dre_cnf_file" $LINENO
			    else
				parse_user_dre_cnf_file "$CONFIG_FILE"
			    fi
                            LOG_INFO "ConfigFile passed=$CONFIG_FILE" $LINENO
			else
			    if [ "$UPGRADE_FLG" == "yes" ];then
				#check if its a standalone to active standby upgrade
			        parse_user_dre_cnf_file "$CONFIG_FILE" "--upgrade"
				LOG_DEBUG "Upgrade flag is set, passing --upgrade to parse_user_dre_cnf_file" $LINENO
			    else
				parse_user_dre_cnf_file "$CONFIG_FILE"
			    fi
                            LOG_INFO "ConfigFile passed=$CONFIG_FILE" $LINENO
			fi  
                    ;;
		    
	       
    esac
    shift
done


#cp -f ./ip-bond0.sh /tmp
#cp -f ./ip-bond1.sh /tmp
#if [ -e /etc/init/mysqld.conf ];then
#    rm -f /etc/init/mysqld.conf
#fi
cp -d ./ip-bond.sh /tmp
temp_function
PACKAGING_ROOT=`pwd`
LOG_DEBUG "Packaging root= $PACKAGING_ROOT" $LINENO
#check and install the dependencies
LOG_DEBUG "Checking Prerequisites" $LINENO
populate_ht

if [ "$UPGRADE_FLG" == "yes" ];then
    backup_bonding_cfg
    #backup_heartbeat_cfg
    backup_dre_sys_cfg
    enter_installation_mode "--upgrade"
else
    enter_installation_mode
fi


#check and stop heartbeat if its running stop it
#this step is because ,in standby machine if active mysql is running we have to switch 
#active mysql to active machine 
pgrep heartbeat >/dev/null
if [ $? -eq 0 ];then
    kill_heartbeat &
    service heartbeat stop
fi
if [ $PRODUCT = "dre" ];then
    PLOG_INFO "Checking dependencies for $CUR_DRE_VER..." $LINENO
    check_dependencies ./$CUR_DRE_VER"_dep.txt" 
fi

if [ $PRODUCT = "iwf" ];then
    PLOG_INFO "Checking dependencies for $CUR_IWF_VER..." $LINENO
    check_dependencies ./$CUR_IWF_VER"_dep.txt" 
fi

if [ "$UPGRADE_FLG" == "no" ];then
    #validate mysql authentication and privilages
    check_mysql_configuration --configFile
    if [ $? -ne 0 ];then
        LOG_ERROR "Wrong MySQL configuration" $LINENO
        exit
    fi
fi

LOG_DEBUG "Checking Dependencies" $LINENO
CheckDependencies
LOG_DEBUG "Creating Mysql dump" $LINENO
CreateMysqlDump
if [ $? != 0 ];then
    PLOG_ERROR "Mysql dump failed!" $LINENO
fi

if [ "$UPGRADE_FLG" == "yes" ];then
    echo "true" > /tmp/.${S_PRODUCT_NAME}_upgrade
    if [ ! -e /etc/${PRODUCT}.cfg ];then
        PLOG_WARNING "${S_PRODUCT_NAME} config file lost!" $LINENO
	configure_dre
        check_config_while_upgrade
    fi
else
    PLOG_INFO "No previous releases of ${PRODUCT} found, hence installing!" $LINENO
    echo "false" > /tmp/.${S_PRODUCT_NAME}_upgrade
    configure_dre
    check_config_while_upgrade

fi
#create a Non-Root user "dquser" for DRE service 
create_dre_dquser
#create the Non-Root MySQL user "dquser"
create_mysql_dquser
   
cd $PACKAGING_ROOT
pgrep ^avamgr > /dev/null
if [ $? == 0 ];then
    #pkill -15 ^avamgr
    PLOG_INFO  "Stopping ${PRODUCT} service..." $LINENO
    LOG_INFO "STOP ${S_PRODUCT_NAME}..." $LINENO
    #while [ $? == 0 ]
    #do
    #        pgrep ^avamgr > /dev/null
    #done
    #rm -f /var/lock/subsys/dre
    service ${PRODUCT} stop
fi
 #####
#remove the dre_install_state file before installing
rm -f /tmp/.${S_PRODUCT_NAME}_install_state
rpm -ivh ${S_PRODUCT_NAME}*.rpm
if [ $? == 0 -a ! -e /tmp/.${S_PRODUCT_NAME}_install_state ];then
    cp $DRE_CONFIG  /opt/diametriq/${PRODUCT}/.syscfg/
    if [ $PRODUCT = "dre" ];then
        cp $CUR_DRE_VER"_dep.txt" /opt/diametriq/${PRODUCT}/.syscfg/
    fi

    if [ $PRODUCT = "iwf" ];then
        cp $CUR_IWF_VER"_dep.txt" /opt/diametriq/${PRODUCT}/.syscfg/
    fi

    if [ "$UPGRADE_FLG" == "yes" ];then
        post_rpm_install "--upgrade"
    else
	post_rpm_install 
    fi
    #clear
    echo -e "${bldblu}****************************************************${txtrst}"
    if [ "$UPGRADE_FLG" == "yes" ];then
    echo -e "${bldred}            ${S_PRODUCT_NAME} Upgrade Successful!${txtrst}"
    else
    echo -e "${bldred}            ${PRODUCT_NAME} Installation Successful!${txtrst}"
    fi
    echo -e "${bldblu}****************************************************
    ${txtrst}"
    if [ "$UPGRADE_FLG" == "yes" ];then
    LOG_INFO "${S_PRODUCT_NAME} Upgrade Successful!" $LINENO
    else
    LOG_INFO "${PRODUCT_NAME} Installation Successful!" $LINENO
    fi

    echo ""
    echo -e "${bldgrn}NOTE: Use \"service dre start\" to start the ${PRODUCT} ${txtrst}"
    echo ""
    echo ""

else
    #rollback the installation only incase the rmp related scripts fail
    #.dre_install_State file is created only when the rpm related scripts fail
    #No need to roll back if rpm installation itself failed
    if [ -e /tmp/.${S_PRODUCT_NAME}_install_state ];then 
        UNINSTALL=/opt/diametriq/${PRODUCT}/bin/uninstall_${PRODUCT}.sh
        $UNINSTALL "rollback"
    fi
    #clear
    echo -e "${bldblu}****************************************************${txtrst}"
    if [ "$UPGRADE_FLG" == "yes" ];then
    echo -e "${bldred}    ERROR:Dre Upgrade failed!${txtrst}"
    else
    echo -e "${bldred} ERROR:Dre installation failed!${txtrst}"
    fi
    echo -e "${bldblu}****************************************************${txtrst}"
    
    if [ "$UPGRADE_FLG" == "yes" ];then
    LOG_INFO "ERROR:Dre Upgrade failed!" $LINENO
    else
    LOG_INFO "ERROR:Dre Installation failed!" $LINENO
    fi
fi







