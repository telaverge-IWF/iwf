#!/bin/bash
DIR=DRE_State_Info
DUMP_DIR=/tmp/$DIR
THIRD_PARTY=$DUMP_DIR/3rdParty
DRE=$DUMP_DIR/DRE
OS=$DUMP_DIR/OS

APACHE=$THIRD_PARTY/apache-tomcat
CROND=$THIRD_PARTY/crond
LOGROT=$THIRD_PARTY/logrotate
MEMCACHED=$THIRD_PARTY/memcached
MYSQL=$THIRD_PARTY/mysql
NTP=$THIRD_PARTY/NTP
SNMPD=$THIRD_PARTY/snmpd
SYSLOG=$THIRD_PARTY/syslog

CUR_DRE_DIRS=$DRE/current_dre_dirs
DRE_LOGS=$DRE/logs
PACKAGE=$DRE/package
NETWORK=$OS/network
DRE_CONFIG=/etc/dre.cfg

DRE_BASE=/opt/diametriq/dre

function correct_folder_structure
{
   rm -rf $THIRD_PARTY
   rm -rf $DRE
}

function init()
{
    if [ `id -u` -ne 0 ];then
	echo "Run as root"
        exit
    fi

    rm -rf $DUMP_DIR
    mkdir -p $DUMP_DIR
    mkdir -p $THIRD_PARTY
    mkdir -p $DRE
    mkdir -p $OS

    mkdir -p $APACHE
    mkdir -p $CROND
    mkdir -p $LOGROT
    mkdir -p $MEMCACHED
    mkdir -p $MYSQL
    mkdir -p $NTP
    mkdir -p $SNMPD
    mkdir -p $SYSLOG

    mkdir -p $CUR_DRE_DIRS
    mkdir -p $DRE_LOGS
    mkdir -p $PACKAGE
    mkdir -p $NETWORK

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

function GetLocalHostName()
{
    sed -n s/LocalHostName=//p $DRE_CONFIG
}



function package_log()
{
    PACKAGE_LOG="$DUMP_DIR/dre_sys_dump.log"
    
    if [ $# -eq 0 ];then
        echo "" >> $PACKAGE_LOG
    elif [ $# -eq 4  ];then
        # $1 = LogLevel $2 = Message to be printed 
        # $3 = 1 for file only , 2 for console only , 3 for both file and console.
        # $4 : Is the line number passed
        case $1 in
             1) case $3 in
                   1) echo "[`date`] Alert | $0:$4 | $2" >> $PACKAGE_LOG
                      ;;
                   2) echo "ALERT | $2"
                      ;;
                   3) echo "[`date`] Alert | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "ALERT | $2"
                      ;;
                   *) echo "[`date`] Alert | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "ALERT | $2"
                      ;;   
                esac   
               ;;
            2) case $3 in
                   1) echo "[`date`] Critical | $0:$4 | $2" >> $PACKAGE_LOG
                      ;;
                   2) echo "CRITICAL | $2"
                      ;;
                   3) echo "[`date`] Critical | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "CRITICAL | $2"
                      ;;
                   *) echo "[`date`] Critical | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "CRITICAL | $2"
                      ;; 
                esac 
               ;;
            3) case $3 in
                   1) echo "[`date`] Error | $0:$4 | $2" >> $PACKAGE_LOG
                      ;;
                   2) echo "ERROR | $2"
                      ;;
                   3) echo "[`date`] Error | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "ERROR | $2"
                      ;;
                   *) echo "[`date`] Error | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "ERROR | $2"
                      ;; 

                esac 
               ;;
            4) case $3 in
                  1) echo "[`date`] Warning | $0:$4 | $2" >> $PACKAGE_LOG
                      ;;
                   2) echo "WARNING | $2"
                      ;;
                   3) echo "[`date`] Warning | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "WARNING | $2"
                      ;;
                   *) echo "[`date`] Warning | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "WARNING | $2"
                      ;; 
                esac 
               ;;
            5) case $3 in
                   1) echo "[`date`] Notice | $0:$4 | $2" >> $PACKAGE_LOG
                      ;;
                   2) echo "$2"
                      ;;
                   3) echo "[`date`] Notice | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "$2"
                      ;;
                   *) echo "[`date`] Notice | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "$2"
                      ;; 

                esac 
               ;;
            6) case $3 in
                   1) echo "[`date`] Info | $0:$4 | $2" >> $PACKAGE_LOG
                      ;;
                   2) echo "$2"
                      ;;
                   3) echo "[`date`] Info | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "$2"
                      ;;
                   *) echo "[`date`] Info | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "$2"
                      ;; 

                esac 
               ;;
            7) case $3 in
                   1) echo "[`date`] Debug | $0:$4 | $2" >> $PACKAGE_LOG
                      ;;
                   2) echo "$2"
                      ;;
                   3) echo "[`date`] Debug | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "$2"
                      ;;
                   *) echo "[`date`] Debug | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "$2"
                      ;; 

                esac 
               ;;
            *) case $3 in
                   1) echo "[`date`] Info | $0:$4 | $2" >> $PACKAGE_LOG
                      ;;
                   2) echo "$2"
                      ;;
                   3) echo "[`date`] Info | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "$2"
                      ;;
                   *) echo "[`date`] Info | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "$2"
                      ;; 


              esac  
               ;;
           esac 
           
    fi
}

function PLOG_ALERT
{
    package_log 1 "$1" 3 $2
}

function PLOG_CRITICAL
{
    package_log 2 "$1" 3 $2
}

function PLOG_ERROR
{
    package_log 3 "$1" 3 $2
}

function PLOG_WARNING
{
    package_log 4 "$1" 3 $2
}

function PLOG_NOTICE
{
    package_log 5 "$1" 3 $2
}
function PLOG_INFO
{
    package_log 6 "$1" 3 $2
}

function PLOG_DEBUG
{
    package_log 7 "$1" 3 $2
}

function LOG_ALERT
{
    package_log 1 "$1" 1 $2
}

function LOG_CRITICAL
{
    package_log 2 "$1" 1 $2
}

function LOG_ERROR
{
    package_log 3 "$1" 1 $2
}

function LOG_WARNING
{
    package_log 4 "$1" 1 $2
}

function LOG_NOTICE
{
    package_log 5 "$1" 1 $2
}
function LOG_INFO
{
    package_log 6 "$1" 1 $2
}

function LOG_DEBUG
{
    package_log 7 "$1" 1 $2
}


function clear_package_log
{
    package_log 
    package_log 
    package_log 
    package_log 
    package_log
    package_log
    package_log
}


#$1=filepath $2=heading
function heading()
{
 echo "" >>$1
 echo "" >>$1
 echo "----------------------------------------------------------------------------------" >> $1
 echo "                                  $2                                              " >> $1
 echo "----------------------------------------------------------------------------------" >> $1
 echo "DATE=`date`" >>$1
 echo "" >>$1


}

#saves all the info under DRE
function save_dre_info()
{
    #save dre logs
    if [ -e /var/log/dre ];then
        PLOG_INFO "saving dre logs..." $LINENO
	cp -r /var/log/dre $DRE_LOGS
        # -mtime n, means 24*n
        # for 1 hour, 24*(1/24)
        # 1/24 = 0.041666666666666664
        #
        #local mtime_equalent_of_hour=0.0416
        #find /var/log/dre -type f -mtime -$mtime_equalent_of_hour -exec cp {} $DRE_LOGS \;
    fi
    #save dre directories
    if [ -e $DRE_BASE ];then
        PLOG_INFO "saving dre directories..." $LINENO
        cp -r $DRE_BASE/* $CUR_DRE_DIRS/
        rm -rf $CUR_DRE_DIRS/lib
        rm -rf $CUR_DRE_DIRS/bin
	rm -rf $CUR_DRE_DIRS/WEB-GUI
        heading "$CUR_DRE_DIRS/dre_dir_list.txt" "DRE Directory structure"
        echo "`ls -lR $DRE_BASE/`" >> $CUR_DRE_DIRS/dre_dir_list.txt

      #  heading "$CUR_DRE_DIRS/Soft_link_state" "Softlink state"
      #  echo "`cd /opt/diametriq && ll`" >>$CUR_DRE_DIRS/Soft_link_state
    else
        PLOG_ERROR "dre may not be installed" $LINENO
    fi
     
    #save package related info/state
    if [ -e /etc/.dre ];then
        cp -r /etc/.dre $PACKAGE
        
    fi
    if [ -e /etc/dre.cfg ];then
        cp /etc/dre.cfg $PACKAGE
    fi

    save_cmd "dre_appD --version" "$DRE/dre_version"
}


function save_network_info()
{

    PLOG_INFO "saving network cfg and scripts..." $LINENO

    save_cmd "uname -irm" "$NETWORK/network_info"
    save_cmd "rpm -qa \*-release\*" "$NETWORK/network_info"
    save_cmd "cat /etc/redhat-release" "$NETWORK/network_info"
    save_cmd "getenforce" "$NETWORK/network_info"
    save_cmd "free -m" "$NETWORK/network_info"
    save_cmd "lspci" "$NETWORK/network_info"
    save_cmd "lsusb" "$NETWORK/network_info"
    save_cmd "rpm -qa kmod\* kmdl\*" "$NETWORK/network_info"
    save_cmd "ifconfig -a" "$NETWORK/network_info"
    save_cmd "brctl show" "$NETWORK/network_info"
    save_cmd "route -n" "$NETWORK/network_info"
    save_cmd "ip rule show" "$NETWORK/network_info"
    save_cmd "ip route show" "$NETWORK/network_info"
    save_cmd "cat /etc/resolv.conf" "$NETWORK/resolv.conf"
    save_cmd "cat /etc/nsswitch.conf" "$NETWORK/nsswitch.conf"
    save_cmd "chkconfig --list " "$NETWORK/chkconfig_list"

    if [ -d /etc/sysconfig/network-scripts ];then
        cp /etc/sysconfig/network-scripts/ifcfg* $NETWORK
        if [ -d /etc/sysconfig/network-scripts/bkp ];then
	    cp -r /etc/sysconfig/network-scripts/bkp $NETWORK
        fi
      
        cp -r /etc/sysconfig/network-scripts/route* $NETWORK 2>/dev/null
    fi

    if [ -e /etc/hosts ];then
	    cp /etc/hosts $NETWORK
    fi
    if [ -e /etc/resolv.conf ];then
	    cp /etc/resolv.conf $NETWORK
    fi

    heading "$NETWORK/ifconfig_output.txt" "ifconfig"
    echo "`ifconfig`" >> $NETWORK/ifconfig_output.txt

    heading "$NETWORK/ipaddr_show_output.txt" "ip addr show"
    echo "`ip addr show`" >> $NETWORK/ipaddr_show_output.txt   


    #check if bonding exists, if yes save them as well
   
    if [ -e /sys/class/net/bonding_masters ];then
	PLOG_INFO "saving bonding info" $LINENO
        mkdir -p $NETWORK/bonding
 	if [ -e /etc/modprobe.d/bond.conf ];then
	    cp /etc/modprobe.d/bond.conf $NETWORK/bonding
	fi
        heading "$NETWORK/bonding/bonds.txt" "Bonded Interfaces"
	cat /sys/class/net/bonding_masters >>$NETWORK/bonding/bonds.txt
        for bonds in `cat /sys/class/net/bonding_masters`
	do
	    heading "$NETWORK/bonding/$bonds" "Interfaces of $bonds"
	    cat /sys/class/net/$bonds/bonding/slaves >> $NETWORK/bonding/$bonds
	done
    fi 
    
}

function save_thirdparty_info()
{
    #apache-tomcat related
    LOG1=`ls -lrt /opt/apache-tomcat/logs/|grep "localhost_access"|tail -1|cut -d':' -f2|cut -d' ' -f2`
    LOG2=`ls -lrt /opt/apache-tomcat/logs/|grep "catalina\."|tail -1|cut -d':' -f2|cut -d' ' -f2`    
    LOG3=`ls -lrt /opt/apache-tomcat/logs/|grep "localhost\."|tail -1|cut -d':' -f2|cut -d' ' -f2`
    LOG_INFO "log1=$LOG1" $LINENO
    LOG_INFO "log2=$LOG2" $LINENO
    LOG_INFO "log3=$LOG3" $LINENO
    #cp -r /opt/apache-tomcat/logs/$LOG1 $APACHE
    #cp -f /opt/apache-tomcat/logs/$LOG2 $APACHE
    #cp -f /opt/apache-tomcat/logs/$LOG3 $APACHE
    mkdir -p $APACHE/logs
    cp -rf /opt/apache-tomcat/logs/ $APACHE/logs
    heading "$APACHE/process_info.txt" "Apache Process Information"
    echo "`ps -eaf|grep apache-tomcat`" >>$APACHE/process_info.txt 

    heading "$APACHE/logs_disk_space.txt" "Logs folder space"
    echo "`du -h /opt/apache-tomcat/logs`" >>$APACHE/logs_disk_space.txt

    #snmpd related
    if [ -d /etc/snmp ];then
	PLOG_INFO "saving snmp cfg..." $LINENO
        cp -r /etc/snmp $SNMPD
    fi
 
    #logrotate
    if [ -e /etc/logrotate.d/dre_logrotate ];then
	PLOG_INFO "saving logrotate cfg..." $LINENO
	cp /etc/logrotate.d/dre_logrotate $LOGROT
    fi
    #myql related
    if [ -e /var/log/mysqld.log ];then
	PLOG_INFO "saving mysql log..." $LINENO
	cp /var/log/mysqld.log $MYSQL
    fi
    if [ -e /etc/my.cnf ];then
	cp /etc/my.cnf $MYSQL
    fi
    if [ -e ~/.mysql_history ];then
	cp ~/.mysql_history $MYSQL/mysql_history
    fi


 

    #crond related
    PLOG_INFO "saving crontab..." $LINENO
    cp /etc/crontab $CROND

    #syslogd related
    if [ -e /etc/rsyslog.conf ];then
	PLOG_INFO "saving rsyslog conf..." $LINENO
	cp /etc/rsyslog.conf $SYSLOG
    fi

    #NTP related
    if [ -e /etc/ntp.conf ];then
	PLOG_INFO "saving NTP conf..." $LINENO
        cp /etc/ntp.conf $NTP
    fi

    #save bash history
    if [ -e ~/.bash_history ];then
	PLOG_INFO "saving history..." $LINENO
	cp ~/.bash_history $OS/bash_history
    fi

    #save /var/log/messages
    tail -n 1000 /var/log/messages > $OS/messages_last_1000

    #find /var/log/ -size -10M |grep messages >/dev/null
    #if [ $? -eq 0 ];then
    #    if [ -e /var/log/messages ];then
    #    cp /var/log/messages $OS/
    #    fi
    #fi

}

function save_pmap_pstack_info()
{

    PLOG_INFO "saving pmap info..." $LINENO
    local AVAMGR_PID=`get_pid "avamgr"`
    local DRE_PID=`get_pid "dre_app"`
    local CLI_PID=`get_pid "cli"`
    local CMGR_PID=`get_pid "cmgr"`
    local WEBAGENT_PID=`get_pid "CPPWebAgent"`
    local STATSLOGGER_PID=`get_pid "statsLogger"`
    local SUBAGENT_PID=`get_pid "subagent"`

    pgrep "^avamgr" >/dev/null
    if [ $? -ne 0 ];then
        PLOG_INFO "Dre procceses not running!" $LINENO
	return
    fi

    heading "$DRE/pmap_info.txt" "pmap information of dre processes"
    local value=`pmap $AVAMGR_PID 2>>$DRE/pmap_info.txt`
    echo "$value" >> $DRE/pmap_info.txt
    echo "" >> $DRE/pmap_info.txt
    local value=`pmap $DRE_PID 2>>$DRE/pmap_info.txt`
    echo "$value" >> $DRE/pmap_info.txt
    echo "" >> $DRE/pmap_info.txt
    local value=`pmap $CLI_PID 2>>$DRE/pmap_info.txt`
    echo "$value" >> $DRE/pmap_info.txt
    echo "" >> $DRE/pmap_info.txt
    local value=`pmap $CMGR_PID 2>>$DRE/pmap_info.txt`
    echo "$value" >> $DRE/pmap_info.txt
    echo "" >> $DRE/pmap_info.txt
    local value=`pmap $WEBAGENT_PID 2>>$DRE/pmap_info.txt`
    echo "$value" >> $DRE/pmap_info.txt
    echo "" >> $DRE/pmap_info.txt
    local value=`pmap $STATSLOGGER_PID 2>>$DRE/pmap_info.txt`
    echo "$value" >> $DRE/pmap_info.txt
    echo "" >> $DRE/pmap_info.txt
    local value=`pmap $SUBAGENT_PID 2>>$DRE/pmap_info.txt`
    echo "$value" >> $DRE/pmap_info.txt
 
    heading "$DRE/pstack_info.txt" "pstack information of dre processes"
    local value=`pstack $AVAMGR_PID 2>>$DRE/pstack_info.txt`
    echo "$value" >> $DRE/pstack_info.txt
    echo "" >> $DRE/pstack_info.txt
    local value=`pstack $DRE_PID 2>>$DRE/pstack_info.txt`
    echo "$value" >> $DRE/pstack_info.txt
    echo "" >> $DRE/pstack_info.txt
    local value=`pstack $CLI_PID 2>>$DRE/pstack_info.txt`
    echo "$value" >> $DRE/pstack_info.txt
    echo "" >> $DRE/pstack_info.txt
    local value=`pstack $CMGR_PID 2>>$DRE/pstack_info.txt`
    echo "$value" >> $DRE/pstack_info.txt
    echo "" >> $DRE/pstack_info.txt
    local value=`pstack $WEBAGENT_PID 2>>$DRE/pstack_info.txt`
    echo "$value" >> $DRE/pstack_info.txt
    echo "" >> $DRE/pstack_info.txt
    local value=`pstack $STATSLOGGER_PID 2>>$DRE/pstack_info.txt`
    echo "$value" >> $DRE/pstack_info.txt
    echo "" >> $DRE/pstack_info.txt
    local value=`pstack $SUBAGENT_PID 2>>$DRE/pstack_info.txt`
    echo "$value" >> $DRE/pstack_info.txt
     
  
}


#$1=process name
function get_pid()
{
    local PID=`ps -eaf|grep "$1"|grep -v grep|tr -s " "|cut -d' ' -f2`
    if [ -n "$PID" ];then
	echo "$PID"
    fi

}

function save_set()
{
    PLOG_INFO "executing set...." $LINENO
    local value="set"
    heading "$DUMP_DIR/OS/set" "$value"
    local value=`set 2>>$DUMP_DIR/OS/set`
    echo "$value"  >>$DUMP_DIR/OS/set 
}

#$1 command
#$2 filename
function save_cmd()
{
    local value="$1"
    PLOG_INFO "executing $value...." $LINENO
    heading "$2" "$value"
    local value=`$1 2>>$2`
    echo "$value" >>$2 
}

function save_os_info()
{
   save_set 
   save_cmd "uname -a" "$OS/os_info"
   save_cmd "lsb_release -a" "$OS/os_info"
   save_cmd "cat /etc/redhat-release" "$OS/os_info"
   save_cmd "lsblk -a" "$OS/os_info"
   save_cmd "lscgroup" "$OS/os_info"
   save_cmd "lscpu" "$OS/os_info"
   save_cmd "lshal" "$OS/lshal"
   save_cmd "lsmod" "$OS/os_info"
   save_cmd "lspci" "$OS/os_info"
   save_cmd "lspci -n" "$OS/os_info"
   save_cmd "lssubsys -a" "$OS/os_info"
   save_cmd "lsof" "$OS/lsof"
   save_cmd "w" "$OS/os_info"
   save_cmd "cat /proc/version" "$OS/os_info"
   save_cmd "cat /proc/cpuinfo" "$OS/os_info"
   save_cmd "cat /proc/meminfo" "$OS/os_info"
   save_cmd "vmstat 1 5" "$OS/os_info"
   save_cmd "top -b -n 3 -H" "$OS/top"
   save_cmd "ps -elf" "$OS/ps"
   save_cmd "netstat -nap" "$OS/netstat"
   save_cmd "df -h" "$OS/os_info"
   save_cmd "uptime" "$OS/os_info"
   save_cmd "ulimit -a" "$OS/os_info"
   save_cmd "hostname" "$OS/os_info"
   save_cmd "last -aF" "$OS/login_info"
   save_cmd "service dre status" "$OS/os_info"
   save_cmd "sysctl -a" "$OS/kernal_parameters"
   save_cmd "rpm -qa" "$OS/rpms_installed"
}

function save_mysqldump()
{
    USERNAME=`GetMysqlUsername`
    PASSWORD=`GetMysqlPassword`
    IP=`GetMysqlIpAddress`
    PORT=`GetMysqlPort`

    MYSQL_DUMP_FILE="mysql_dump_"
    local DATE=`date | tr -s " " | tr " " "_"`
    MYSQL_DUMP_FILE=$MYSQL_DUMP_FILE$DATE".sql"
    PLOG_INFO "Taking Mysql dump.... File $MYSQL_DUMP_FILE" $LINENO
    mysqldump --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT --databases DIAMETRIQ >> $MYSQL/$MYSQL_DUMP_FILE


}

function save_diametriq_mysql()
{
    local USERNAME=`GetMysqlUsername`
    local PASSWORD=`GetMysqlPassword`
    local IP=`GetMysqlIpAddress`
    local PORT=`GetMysqlPort`

    local CMD=$1

    PLOG_INFO "executing $CMD...." $LINENO
    heading "$2" "$CMD"

    my="mysql  --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT --database=DIAMETRIQ -se"

    ${my} "$CMD" >>$2 2>>$2
}

function save_cmd_mysql()
{
    local USERNAME=`GetMysqlUsername`
    local PASSWORD=`GetMysqlPassword`
    local IP=`GetMysqlIpAddress`
    local PORT=`GetMysqlPort`

    local CMD=$1
    PLOG_INFO "executing $CMD...." $LINENO
    heading "$2" "$CMD"

    my="mysql  --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT -se " 
    ${my} "$CMD" >>$2 2>>$2

}

function save_mysql_info()
{
    save_mysqldump
    save_cmd_mysql "SHOW VARIABLES\G" $MYSQL/mysql_variables
    save_cmd_mysql "SHOW PROCESSLIST\G" $MYSQL/processlist
    save_cmd_mysql "SHOW ENGINE INNODB STATUS\G" $MYSQL/innodb_status
    save_cmd_mysql "SHOW SLAVE STATUS\G" $MYSQL/mysql_ha_info
    save_cmd_mysql "SHOW MASTER STATUS\G" $MYSQL/mysql_ha_info
    save_cmd_mysql "SHOW MASTER LOGS\G" $MYSQL/mysql_ha_info
}

function tar_and_zip()
{
    local DATE=`date | tr -s " " | tr " " "_"|tr ":" "_"`
    cd /tmp
    if [ $# == 1 ];then
	if [ "$1" == "--network" ];then
		mv $DIR dre_sys_network_info
		tar cvzf dre_sys_network_info"_"$DATE.tar.gz dre_sys_network_info	
		rm -rf dre_sys_network_info
		cd -
    		echo "DRE NETWORK SYS DUMP Created /tmp/dre_sys_network_info""_"$DATE".tar.gz" 
		return
	fi	
    fi
    tar cvzf $DIR"_"$DATE.tar.gz $DIR
    rm -rf $DUMP_DIR
    cd -
    echo "DRE SYS DUMP Created $DUMP_DIR""_"$DATE".tar.gz" 
}

if [ $# == 1 ];then

    if [ "$1" == "--network" ];then
        init
        save_network_info
        save_os_info
        correct_folder_structure
        tar_and_zip $1
        exit 0
    fi
    
fi

init
save_os_info
save_mysql_info
save_dre_info
save_network_info
save_thirdparty_info
save_pmap_pstack_info
tar_and_zip
