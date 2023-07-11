#!/bin/bash
#This script installs all the 3rd party dependency rpms requred for DRE
INS_PATH=./DRE_DEP_RPMS
CONFIG_PATH=./CONFIG
ROOT_DIR=`pwd`
RET=0

function package_log()
{
    if [ ! -d "/var/log/dre" ];then
        mkdir -p /var/log/dre > /dev/null
    fi
    PACKAGE_LOG="/var/log/dre/package.log"
    
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

#a common banner heading which scripts can use to print initial infomration/heading
function log_heading()
{
    clear_package_log
    clear_package_log
    if [ ! -d "/var/log/dre" ];then
        mkdir -p /var/log/dre > /dev/null
    fi                
    PACKAGE_LOG="/var/log/dre/package.log"

    echo "-----------------------------------------------------------------------------------------" >> $PACKAGE_LOG
    echo "                                $1  " >> $PACKAGE_LOG
    echo "      Version              :    $CUR_DRE_VER" >> $PACKAGE_LOG
    echo "      Date                 :    `date`" >> $PACKAGE_LOG
    echo "-----------------------------------------------------------------------------------------" >> $PACKAGE_LOG
    echo "--------------------------------" >> $PACKAGE_LOG
    echo "Versions installed in the system" >> $PACKAGE_LOG
    echo "--------------------------------" >> $PACKAGE_LOG
    echo "`rpm -q dre`" >> $PACKAGE_LOG
    echo "" >> $PACKAGE_LOG

    echo "------------------------------" >> $PACKAGE_LOG
    echo "Directories in /opt/diametriq/" >> $PACKAGE_LOG
    echo "------------------------------" >> $PACKAGE_LOG
    if [ -d /opt/diametriq/ ];then
    echo "`ls -lrt /opt/diametriq`" >> $PACKAGE_LOG
    fi
    if [ -d /etc/.dre ];then
    echo "-------------------" >> $PACKAGE_LOG
    echo "PACKAGE FILES STATE" >> $PACKAGE_LOG
    echo "-------------------" >> $PACKAGE_LOG

    if [ -e /etc/.dre/db_upgrade_info ];then
    echo "-------------------------" >> $PACKAGE_LOG
    echo "/etc/.dre/db_upgrade_info" >> $PACKAGE_LOG
    echo "-------------------------" >> $PACKAGE_LOG
    echo "`cat /etc/.dre/db_upgrade_info`" >> $PACKAGE_LOG
    else
    echo "/etc/.dre/db_upgrade_info does not exist!"
    fi

    if [ -e /etc/.dre/dre_install_info ];then
    echo "--------------------------" >> $PACKAGE_LOG
    echo "/etc/.dre/dre_install_info" >> $PACKAGE_LOG
    echo "--------------------------" >> $PACKAGE_LOG
    echo "`cat /etc/.dre/dre_install_info`" >> $PACKAGE_LOG
    else
    echo "/etc/.dre/dre_install_info does not exist!"
    fi

    if [ -e /etc/.dre/dre_uninstall_info ];then
    echo "----------------------------" >> $PACKAGE_LOG
    echo "/etc/.dre/dre_uninstall_info" >> $PACKAGE_LOG
    echo "----------------------------" >> $PACKAGE_LOG
    echo "`cat /etc/.dre/dre_uninstall_info`" >> $PACKAGE_LOG
    else
    echo "/etc/.dre/dre_uninstall_info does not exist!"
    fi

    fi
    echo "-----------------------------------------------------------------------------------------" >> $PACKAGE_LOG
   
}


function null_check()
{
    read -e -p "$1" as
    while [ -z $as ]
    do
        read -p "$2" as
    done
    echo $as
}

function silent_null_check()
{
    read -s -p "$1" as
    while [ -z $as ]
    do
        read -s -p "$2" as
    done
    echo $as
}

#$1=section name $2=name-value string $3=cnf file name
function insert_config_in_section()
{
    #delete the line
    DEL=`echo "$2"|cut -d'=' -f1` 
    sed -i /"^$DEL.*"/d  "$3"
    #insert config
    sed -i '/\["$1"\]/{:a;n;/^$/!ba;i\"$2"' -e '}' "$3"
}

function compare_passwords()
{   n='
'
    first=$1
    second=$2
    while [ "$first" != "$second" ]
    do
        first=`silent_null_check "${n}Passwords do not match!${n}Enter Password     :" "Password (should not be null) :"`
        second=`silent_null_check "${n}Confirm Password     :" "Password (should not be null) :"`
    done
    echo "$first"

}


function configure_mysql_server()
{
n='
'
    #copy my.cnf to /etc/
    service mysql start
    pgrep mysqld >/dev/null
    if [ $? != 0 ]; then
        PLOG_INFO "Mysql is not installed" $LINENO
        exit 1
    else
        PLOG_INFO  "Mysql is up and running" $LINENO

    fi  

    echo "---------------------------------------------------------------------"
    echo "			Configure Mysql Server				   "
    echo "---------------------------------------------------------------------"
#    MysqlUsername="root"
    MysqlUsername=`null_check "MySQL Username     :" "MySQL Username (should not be null):"`
    MysqlPassword=`silent_null_check "MySQL Password     :" "MySQL Password (should not be null) :"`
    ConfirmMysqlPass=`silent_null_check "${n}Confirm Password   :" "Password (should not be null) :"`
    MysqlPassword=`compare_passwords $MysqlPassword $ConfirmMysqlPass`

    mysql -u$MysqlUsername -p$MysqlPassword -se "show databases" > /etc/null 2> /etc/null
    if [ $? -ne 0 ];then
    	mysqladmin -u $MysqlUsername password $MysqlPassword > /etc/null 2> /etc/null
    	if [ $? -ne 0 ];then
        	echo ""
	    	PLOG_INFO "Cannot set the password/Password may already be set!" $LINENO
    	else
        	echo ""
    		PLOG_INFO "Password set successfully" $LINENO
    	fi    
    else
	echo ""
    	PLOG_INFO "Password is already set" $LINENO
    fi
    service mysql stop
}

if [ `id -u` -ne 0 ]; then
    echo "Run as root"
    exit 1
fi
log_heading "DEPENDENCY PACKAGE INSTALLATION" 
cd $INS_PATH
JRE=jre-1.7.0_09-fcs.x86_64.rpm
if [ -n "$JRE" ];then
    mv ./$JRE $ROOT_DIR
fi

rpm -U --test *.rpm 2>../op
cd $ROOT_DIR
if [ -n "`cat op`" ];then
    LOG_INFO "output not empty!" $LINENO
    LIST=`cat op|grep "already installed"|cut -d' ' -f2`
    PLOG_INFO "The following packages are already installed!" $LINENO
    PLOG_INFO "$LIST" $LINENO
    cd $INS_PATH
    # remove already installed rpms
    mkdir -p $ROOT_DIR/tmp
    for RPM in $LIST
    do
	mv -f $RPM.rpm $ROOT_DIR/tmp 2>/dev/null
	if [ $? -ne 0 ];then
	    echo "$RPM.rpm" | grep "0:"
  	    if [ $? -eq 0 ];then
	        mv `echo "$RPM.rpm"|sed -e "s/0://g"` $ROOT_DIR/tmp 2>/dev/null
	        if [ $? -eq 0 ];then
		    LOG_INFO "--"
		fi
            else
		mv `echo "$RPM.rpm"|sed -e "s/1://g"` $ROOT_DIR/tmp 2>/dev/null
		if [ $? -eq 0 ];then
		    LOG_INFO "--"
		fi
	    fi
        else
 	    LOG_INFO "--" 
  	    
	fi
    done
    #special case for java
    rpm -qa|grep "java-1.6.0"
    if [ $? -eq 0 ];then
        mv -f java*.rpm $ROOT_DIR/tmp 2>/dev/null
    fi
    #special case for xinetd
    rpm -qa |grep xinetd-2.3.14-33.el6.x86_64
    if [ $? -eq 0 ];then
	mv -f xinetd*.rpm $ROOT_DIR/tmp 2>/dev/null 
    fi
    is_mysql_configured="no"
    rpm -qa|grep MySQL-Cluster-server-gpl >/dev/null
    if [ $? -eq 0 ];then
        is_mysql_configured="yes"
    else
       cd $ROOT_DIR 
       cp $CONFIG_PATH/my.cnf /etc
       cd $INS_PATH  
    fi

    rpm -Uvh --nosignature  *.rpm 2>warning.txt
    if [ $? -ne 0 ];then
	cat warning.txt|grep "which is newer"
	LOG_DEBUG "`cat warning.txt`" $LINENO
        LIST=`cat warning.txt|grep "which is newer"|cut -d'(' -f2|cut -d' ' -f5|cut -d')' -f1`
	    for RPM in $LIST
            do
	        mv -f $RPM.rpm $ROOT_DIR/tmp 2>/dev/null
	        if [ $? -ne 0 ];then
	            echo "$RPM.rpm" | grep "0:"
  	            if [ $? -eq 0 ];then
	                 mv `echo "$RPM.rpm"|sed -e "s/0://g"` $ROOT_DIR/tmp 2>/dev/null
	                 if [ $? -eq 0 ];then
		                 LOG_INFO "--"
		             fi
                else
		             mv `echo "$RPM.rpm"|sed -e "s/1://g"` $ROOT_DIR/tmp 2>/dev/null
		             if [ $? -eq 0 ];then
		                 LOG_INFO "--" 
		             fi
	                 fi
                   else
 	                echo ""
  	    
	        fi
        done
	ls *.rpm 2> /dev/null
	if [ $? -eq 0 ];then
            rpm -Uvh --nosignature  *.rpm 
            if [ $? -ne 0 ];then
                RET=1
	    fi
        fi
        
    fi

    cd $ROOT_DIR
    if [ -n "$JRE" ];then
        rpm -qa|grep jre >/dev/null
        if [ $? -ne 0 ];then
            rpm -Uvh --nosignature $JRE 2>&1|grep -v "Could not open input file: /usr/java*"
        fi
    fi

    mv ./$JRE $INS_PATH 2>/dev/null
    #move back the rpms
    mv -f ./tmp/* $INS_PATH
    rm -rf ./tmp    
    rm -f ./op
    if [ $RET -eq 0 ];then
        PLOG_INFO "INSTALLATION SUCCESSFUL!" $LINENO
	#now configure mysql server
	if [ "$is_mysql_configured" == "no" ];then	
	    configure_mysql_server
        fi
    else
        PLOG_INFO "INSTALLATION FAILED!" $LINENO
    fi
fi

