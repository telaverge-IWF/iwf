Name: iwf
Version: 4.2.0
Release: 02
Summary: Diametriq's Interworking Function
Group:   Application
License: Proprietary
URL:     http://www.diametriq.com
Requires: apache-tomcat >= 7.0.20-1,jre >= 1.7, mariadb,lksctp-tools ,memcached, libevent, ncurses,libaio,/usr/bin/pgrep,pcre,net-snmp >= 5.5,ndisc6 >= 1.0.1
AutoReqProv: no

%description
The Diameter Interworking System™ serving as a Interworking Function (IWF) facilitating interworking capability between Legacy Protocols like CAMEL or MAP to Diameter.


%define __os_install_post %{nil}

%build


%install
echo "install"
export DONT_STRIP=1
rm -rf $RPM_BUILD_ROOT
cd $IWF_ROOT/common/src

export IWF_REL=%{name}-%{version}-%{release}
echo $IWF_REL
make SCCP_PROT=CCITT clean all
cd $IWF_ROOT
make SCCP_PROT=CCITT install
UNINST=${RPM_BUILD_ROOT}/opt/diametriq/${IWF_REL}/bin/uninstall_iwf.sh
#update version information in the uninstall_iwf  script
sed -i "s/^IWF_VER=/IWF_VER=${IWF_REL}/" ${UNINST}


%clean
rm -rf $RPM_BUILD_ROOT
%files
%defattr(-,dquser,dquser,-)
/opt/diametriq/%{name}-%{version}-%{release}



%changelog

%pre
source /etc/package_functions.sh
LOG_DEBUG "Begining of pre in iwf.spec" $LINENO
rm -f /tmp/.iwf_install_state
if [ ! -d /etc/.iwf ];then
    LOG_DEBUG "Creating /etc/.iwf ..." $LINENO
    mkdir -p /etc/.iwf
fi

touch /etc/.iwf/iwf_install_info

#this controls whether to start network while starting the IWF service
#if "no" then it wont restart network , if "yes" then it restarts network(will be "no" during boot)
echo "no" >/etc/.iwf/boot

#if this is a fresh install update the /etc/.iwf/iwf_install_info
if [ -z `rpm -q iwf|grep -v "not installed"|tail -1 2>/dev/null` ];then
    if [ -z `grep "fresh_install" /etc/.iwf/iwf_install_info 2>/dev/null` ];then
        echo "fresh_install=yes" >> /etc/.iwf/iwf_install_info  
	LOG_DEBUG "adding fresh_install=yes" $LINENO
    else
	sed -i "s/fresh_install=.*/fresh_install=yes/g" /etc/.iwf/iwf_install_info  
	LOG_DEBUG "replacing fresh_install=yes" $LINENO
    fi
else
    if [ -z `grep "fresh_install" /etc/.iwf/iwf_install_info 2>/dev/null` ];then
        echo "fresh_install=no" >> /etc/.iwf/iwf_install_info
	LOG_DEBUG "adding fresh_install=yes" $LINENO
    else
        sed -i "s/fresh_install=.*/fresh_install=no/g" /etc/.iwf/iwf_install_info  
	LOG_DEBUG "replacing fresh_install=yes" $LINENO 
    fi

fi


if [ $1 -eq 1 ];then
    PLOG_INFO "Preparing for installation..." $LINENO
    pgrep ^avamgr > /dev/null
    if [ $? == 0 ];then
       # pkill -15 ^avamgr
        PLOG_INFO  "Stopping iwf service..." $LINENO
 	PLOG_INFO "Killing IWF service..." $LINENO
      #  while [ $? == 0 ]
      #  do
      #	    pgrep ^avamgr > /dev/null
       # done
       # rm -f /var/lock/subsys/iwf
        service dre stop
    fi
    LOG_DEBUG "pgrep mariadbd = `pgrep mariadbd`" $LINENO
    pgrep mariadbd 1>/dev/null
    if [ $? == 0 ];then
        stop mariadbd
        LOG_DEBUG "pgrep mariadbd = `pgrep mariadbd`" $LINENO
        pgrep mariadbd >/dev/null
	if [ $? == 0 ];then
	    PLOG_WARNING "mariadb still running..." $LINENO
	    pkill -9 mariadbd
	fi
    fi
    pgrep memcached >/dev/null
    if [ $? == 0 ];then
	if [ -e /etc/init/memcached.conf ];then
	    stop memcached    
	fi
    fi
    
    pgrep apache-tomcat >/dev/null
    if [ $? -eq 0 ];then
	if [ -e /etc/init/apache-tomcat.conf ];then
            stop apache-tomcat
  	fi
    fi

elif [ $1 -eq 2 ];then
    pgrep ^avamgr > /dev/null
    if [ $? == 0 ];then
        pkill -15 ^avamgr
	PLOG_INFO "Stopping iwf service..." $LINENO
        while [ $? == 0 ]
	do
	    pgrep ^avamgr > /dev/null

	done
	rm -f /var/lock/subsys/iwf 
    fi
fi

%post
#source the file which contains the logging functions
source /opt/diametriq/%{name}-%{version}-%{release}/scripts/package_functions.sh
LOG_DEBUG "Begining of post install in iwf.spec" $LINENO
IWF_UNINSTALL_INFO=/etc/.iwf/iwf_uninstall_info 
#/etc/.iwf/iwf_uninstall_info is created when iwf is uninstalled using the uninstall_iwf.sh script.
#this file contains the iwf release information of the iwf which is uninstalled, this info is used to indicate if the
# iwf version is reinstalled or if its a fresh install,in case of a reinstall we can avoid creating the database 

IWF_INST_INFO=/etc/.iwf/iwf_install_info
#This file stores the installation infornation , it has the list of installed iwf versions
IWF_PATH=/opt/diametriq
DB_UPGRADE_INFO=/etc/.iwf/db_upgrade_info
UPGRADE=`cat /tmp/.iwf_upgrade 2> /dev/null`
LOG_DEBUG "Upgrade = $UPGRADE" $LINENO
IWF_REL=%{name}-%{version}-%{release}
LOG_DEBUG "IWF_REL=$IWF_REL" $LINENO
#make copy of all the sysconfig 
REL_PATH=$IWF_PATH/%{name}-%{version}-%{release}
LOG_DEBUG "REL_PATH=$REL_PATH" $LINENO


#This function returns the values of any particular field/name passed
#Argument : Field/name 
#returns the value of the field 
function Get_dre_uninstall_info()
{
    if [ -e $DRE_UNINSTALL_INFO ];then  
        RES=`sed -n s/^$1=//p $DRE_UNINSTALL_INFO`
	if [ -z $RES ];then
	    echo "null"
	else
	    echo "$RES"
	fi
    else
        echo "null"
    fi

}


#This function returns the values of any particular field/name passed
#Argument : Field/name 
#returns the value of the field 
function Get_iwf_uninstall_info()
{
    if [ -e $IWF_UNINSTALL_INFO ];then  
        RES=`sed -n s/^$1=//p $IWF_UNINSTALL_INFO`
	if [ -z $RES ];then
	    echo "null"
	else
	    echo "$RES"
	fi
    else
        echo "null"
    fi

}

function Get_dre_install_info()
{
    if [ -e $DRE_INST_INFO ];then
        RES=`sed -n s/^$1=//p $DRE_INST_INFO`
	if [ -z $RES ];then
	    echo "null"
	else
	    echo "$RES"
	fi
    else
        echo "null"
    fi
}

function Get_iwf_install_info()
{
    if [ -e $IWF_INST_INFO ];then
        RES=`sed -n s/^$1=//p $IWF_INST_INFO`
	if [ -z $RES ];then
	    echo "null"
	else
	    echo "$RES"
	fi
    else
        echo "null"
    fi
}

DB_UPGRADE=false
LOG_INFO "DB_UPGRADE=$DB_UPGRADE" $LINENO

#set the database upgrade details in /etc/.iwf/db_upgrade_info
if [ ! -e $DB_UPGRADE_INFO ];then
    touch $DB_UPGRADE_INFO 
fi
if [ -z `grep "$IWF_REL=" $DB_UPGRADE_INFO` ]; then
    echo "$IWF_REL=$DB_UPGRADE" >> $DB_UPGRADE_INFO
else
    sed -i "s/$IWF_REL=.*/$IWF_REL=$DB_UPGRADE/g" $DB_UPGRADE_INFO
fi

PLOG_INFO "copying all iwf sysconfig files..." $LINENO
mkdir -p $REL_PATH/.syscfg
cp $REL_PATH/iwf.sh $REL_PATH/.syscfg
cp $REL_PATH/lib/libmemcached_functions_mysql.so $REL_PATH/.syscfg
cp $REL_PATH/config/my.cnf $REL_PATH/.syscfg
cp $REL_PATH/scripts/iwf.env $REL_PATH/.syscfg
cp $REL_PATH/scripts/dre $REL_PATH/.syscfg
UNINST=`echo "uninstall_%{name}_%{version}_%{release}"`
#rename the uninstall script to reflect its version
#mv $REL_PATH/bin/uninstall_iwf.sh $REL_PATH/bin/$UNINST
mv $REL_PATH/scripts/rollback.sh $REL_PATH/scripts/.rollback.sh

#while upgrading copy all the config files from old release to new release 
if [ "$UPGRADE" == "true" ];then
    PLOG_INFO "Copying config file from prev rel to $IWF_REL" $LINENO
    cd $IWF_PATH/iwf/config/
#    CFG_FILES=`ls`
#    LOG_DEBUG "CFG_FILES = $CFG_FILES" $LINENO
#    for CPY in $CFG_FILES ;
#    do
#        if [ ! -d $CPY ];then
#            cp -f $CPY $REL_PATH/config/
#        fi
#    done
#cp -rf erlbfrls $REL_PATH/config/
#cp -rf asfrls $REL_PATH/config/
    if [ -e its.lic ];then
        cp its.lic $REL_PATH/config/
    fi

    if [ -e couchbase.cfg ];then
        cp couchbase.cfg $REL_PATH/config/
    fi
    cp -f *.cnf $REL_PATH/config/
    cp -f iwf_dia.xml $REL_PATH/config/
    cp -f iwf_itu.xml $REL_PATH/config/
    cp -f ./avamgr/avamgr.json $REL_PATH/config/avamgr/
    cp -f ../bin/iwf.json $REL_PATH/bin/
    LOG_INFO "Upgrade = true" $LINENO
fi
rm -rf $IWF_PATH/iwf
ln -s $IWF_PATH/%{name}-%{version}-%{release} $IWF_PATH/iwf
#check if /etc/ld.so.conf.d/iwf-x86_64.conf is present which has the ld library
#path for the iwf ie /opt/diametriq/iwf/lib
if [ -e /etc/ld.so.conf.d/iwf-x86_64.conf ]; then
    echo ""
else
    PLOG_INFO "Creating /etc/ld.so.conf.d/iwf-x86_64.conf and configuring ld library
    path for iwf..." $LINENO
    echo "/opt/diametriq/iwf/lib" > /etc/ld.so.conf.d/iwf-x86_64.conf
    ldconfig
fi
cp /etc/ld.so.conf.d/iwf-x86_64.conf $IWF_PATH/iwf/.syscfg

#check if incron is installed, if not install incron
if [ ! -e /usr/local/sbin/incrond ];then
    LOG_DEBUG "Installing incron..." $LINENO
    cd $IWF_PATH/iwf/3rdparty/incron && ./install_incron.sh
else
    LOG_DEBUG "Incron already installed!" $LINENO
    #check if incrond is running , if yes stop it
    pgrep ^incrond > /dev/null
    if [ $? -eq 0 ];then
        LOG_DEBUG "Stopping incrond..." $LINENO
	stop incrond
    fi
fi



#copying the iwf script to export env variables to profile.d
PLOG_INFO "Copying iwf.sh to profile.d .." $LINENO
mv -f $IWF_PATH/iwf/iwf.sh /etc/profile.d/
source /etc/profile.d/iwf.sh
if [ $? != 0 ];then
PLOG_ERROR "Error: sourcing failed!" $LINENO
exit 1
fi
PLOG_INFO "Checking for kernel SCTP..." $LINENO
modprobe sctp
if [ $? -eq 0 ]; then
PLOG_INFO "SCTP loaded..." $LINENO
else
PLOG_WARNING "kernel SCTP not found!!!!!" $LINENO
PLOG_WARNING "IWF may not work without kernel SCTP, please install SCTP module" $LINENO
fi

PLOG_INFO "Checking for TIPC..." $LINENO
if [ "$UPGRADE" == "true" ];then
    modprobe tipc 2>/dev/null
    if [ $? -eq 0 ]; then
        PLOG_INFO "TIPC found..." $LINENO
    else
        PLOG_INFO "TIPC not found..." $LINENO
        PLOG_INFO "Installing TIPC..." $LINENO
        cd $DRE_PATH/dre/lib/tipc-1.7.7
        ./install.sh
        if [ $? -eq 0 ];then
            PLOG_INFO "TIPC Configuration success!" $LINENO
        fi  
    fi  

else
    PLOG_INFO "Configuring TIPC..." $LINENO
    cd $IWF_PATH/iwf/lib/tipc-1.7.7
    ./install.sh
    if [ $? -eq 0 ];then
        PLOG_INFO "TIPC configuration success!" $LINENO
    fi  
fi


TIPC_STATE_FILE=/etc/.iwf/tipc_info
if [ -e $TIPC_STATE_FILE ];then
    PLOG_INFO "TIPC Found but config lost" $LINENO
    cd $IWF_PATH/iwf/lib/tipc1*
    ./install.sh
fi


#rm -rf /opt/apache-tomcat/webapps/IWF
#rm -f /opt/apache-tomcat/webapps/IWF.war
#PLOG_INFO "Copying WEB Application to Tomcat folder.." $LINENO
#cp -f $IWF_PATH/iwf/WEB-GUI/IWF.war   /opt/apache-tomcat/webapps/
#PLOG_INFO "Copied WEB Application to Tomcat folder successfully" $LINENO

PLOG_INFO  "Configuring IWF..." $LINENO
if [  -e /usr/local/mysql/lib/plugin/ ]
then
    PLOG_INFO "plugin dir exists" $LINENO
else
    mkdir -p usr/local/mysql/lib/plugin
fi

PLOG_INFO "Checking if mysql is running" $LINENO
LOG_INFO "pgrep mysqld = `pgrep mysqld`" $LINENO
pgrep mysqld >/dev/null
if [ $? -eq 0 ] 
then
    PLOG_INFO "Mysql is runnning... " $LINENO
    PLOG_INFO "Stopping Mysql..." $LINENO
    stop mysqld
    LOG_DEBUG "pgrep mysqld = `pgrep mysqld`" $LINENO
    pgrep mysqld >/dev/null
    if [ $? -eq 0 ];then
        PLOG_WARNING "Could not stop mysql!" $LINENO
	PLOG_INFO "killing..." $LINENO
	LOG_DEBUG "`ps -eaf|grep mysqld`" $LINENO
	pkill -9 mysqld
    fi

fi

#cp /opt/diametriq/iwf/lib/libmemcached_functions_mysql.so /usr/local/mysql/lib/plugin/
cp $IWF_PATH/iwf/lib/libmemcached_functions_mysql.so /usr/lib64/mysql/plugin
if [ "$UPGRADE" != "true" ];then
if [ -e /etc/my.cnf ];then
    PLOG_INFO "backup my.cnf" $LINENO
    LOG_INFO "`cat /etc/my.cnf`" $LINENO
    mv /etc/my.cnf /etc/my.cnfback
fi
mv -f $IWF_PATH/iwf/config/my.cnf /etc/
$IWF_PATH/iwf/scripts/validate_my_cnf_file.sh
LOG_INFO "After replacing my.cnf new my.cnf = `cat /etc/my.cnf`" $LINENO
#fi
else
    rm -f $IWF_PATH/iwf/config/my.cnf
fi
LOG_DEBUG "pgrep mysqld = `pgrep mysqld`" $LINENO
pgrep mysqld >/dev/null
if [ $? -eq 0 ] 
then
    PLOG_INFO "Restarting Mysql..." $LINENO
    stop mysqld
    LOG_DEBUG "pgrep mysqld = `pgrep mysqld`" $LINENO
    pgrep mysqld >/dev/null
    if [ $? -eq 0 ];then
        PLOG_WARNING "Could not stop mysql!" $LINENO
	PLOG_INFO "killing..." $LINENO
	LOG_DEBUG "`ps -eaf|grep mysql`" $LINENO
	pkill -9 mysqld
    fi
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
    LOG_INFO "Starting Mysql..." $LINENO
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
fi
sleep 4

#UNCOMMENT WHEN WE INTRODUCE MEMCACHED
#pgrep memcached 1>/dev/null
#if [ $? == 0 ]
#then
#    PLOG_INFO "Memcached is up and running..." $LINENO
#else
#    PLOG_INFO "Starting Memcached..." $LINENO
#    start memcached
#    if [ $? != 0 ]
#    then
#        PLOG_ERROR "ERROR: Starting memcached failed!" $LINENO
#        exit 1
#    fi

#fi

USER="root"
#configure and start the incrond ..
if [ -e /etc/incron.allow ];then
    #check if root us present in the file
    grep "$USER" /etc/incron.allow >/dev/null
    if [ $? -ne 0 ];then
	#if not present add it
	echo "$USER" >> /etc/incron.allow
    fi
else
    #config file does not exist so create it and add user
    echo "$USER" >> /etc/incron.allow
fi

#restart incrond

pgrep incrond >/dev/null
if [ $? == 0 ];then
    PLOG_INFO "Incrond is up and running..." $LINENO
    stop incrond
    start incrond
else
    PLOG_INFO "Starting Incrond..." $LINENO
    start incrond
    if [ $? -ne 0 ];then
	PLOG_ERROR "Starting Incrond failed!" $LINENO
    fi
fi

############### mysql heart beat scripts########
#Iwf install modes: 1== standalone mode; 2 == active-standby mode; 3 == active-cold-standby mode; 4 == active-hot-standby mode
if ([ "`GetDreInstallMode`" == 2 ] && [ "$UPGRADE" == "false" ]) ||
   ([ "`GetDreInstallMode`" == 3 ] && [ "$UPGRADE" == "false" ]) ||
   ([ "`GetDreInstallMode`" == 4 ] && [ "$UPGRADE" == "false" ]) ;then

    #LOG_DEBUG "Calling heartbeat scripts" $LINENO
    #$IWF_PATH/iwf/scripts/heartbeat_ha.sh  
    #if [ $? != 0 ];then
    #in case of error ,setting state of installation in tmp file since post script always returns 0
    #    LOG_ERROR "Setting \"failure\" in /tmp/.iwf_install_state" $LINENO
	#echo "failure" >/tmp/.iwf_install_state
	#exit 1
    #fi


    $IWF_PATH/iwf/scripts/mysql_ha.sh  
fi
################################################


################ database scripts ###############
#create database,tables and insert default values
#if db upgrade required, call db upgrade script else leave the db as it is
    RES=`Get_iwf_install_info "fresh_install"`
    LOG_DEBUG "Get_iwf_install_info = $RES" $LINENO
    RES=`Get_iwf_uninstall_info "ver"`
    LOG_DEBUG "Get_iwf_uninstall_info = $RES" $LINENO
    #if there is no previous installs of iwf and  this is a reinstall then dont to anything to the db
    if [ `Get_iwf_install_info "fresh_install"` == "yes" ] && [ "$IWF_REL" == `Get_iwf_uninstall_info "ver"` ];then
   	RES=`Get_iwf_uninstall_info "db_flush"`
	LOG_DEBUG "Get_iwf_uninstall_info = $RES" $LINENO
        #if db flush = no then dont create the db
        if [ `Get_iwf_uninstall_info "db_flush"` == "no" ];then	  
            PLOG_INFO "No database change required" $LINENO
            cd $IWF_PATH/iwf/scripts && ./install.sh --reinstall
            if [ $? != 0 ];then
                #setting state of installation in tmp file since post script always returns 0
	        LOG_ERROR "Setting \"failure\" in /tmp/.iwf_install_state" $LINENO
                echo "failure" >/tmp/.iwf_install_state 
                exit 1
            fi
	else
	    PLOG_INFO "Creating database..." $LINENO
            cd $IWF_PATH/iwf/scripts && ./install.sh
            if [ $? != 0 ];then
                #in case of error ,setting state of installation in tmp file since post script always returns 0
	        LOG_ERROR "Setting \"failure\" in /tmp/.iwf_install_state" $LINENO
                echo "failure" >/tmp/.iwf_install_state
                exit 1
            fi
        fi
    #if this is a fresh install then create the database table 
    elif [ `Get_iwf_install_info "fresh_install"` == "yes" ] && [ "$IWF_REL" != `Get_iwf_uninstall_info "ver"` ];then
        PLOG_INFO "Creating database for the first time..." $LINENO
        cd $IWF_PATH/iwf/scripts && ./install.sh
        if [ $? != 0 ];then
            #in case of error ,setting state of installation in tmp file since post script always returns 0
	    LOG_ERROR "Setting \"failure\" in /tmp/.iwf_install_state" $LINENO
            echo "failure" >/tmp/.iwf_install_state
            exit 1
        fi
    else
#	cat $IWF_UNINSTALL_INFO 
	#call the upgrade_database.sh script
	
	PLOG_INFO "Upgrade db..." $LINENO
	LOG_DEBUG "cd $IWF_PATH/iwf/scripts && ./upgrade_database.sh" $LINENO
        cd $IWF_PATH/iwf/scripts && ./upgrade_database.sh 
        if [ $? != 0 ];then
            #in case of error ,setting state of installation in tmp file since post script always returns 0
	    LOG_ERROR "Setting \"failure\" in /tmp/.iwf_install_state" $LINENO
            echo "failure" >/tmp/.iwf_install_state
            exit 1
        fi
    fi
#################################################

#start apache-tomcat
#PLOG_INFO "Starting apache-tomcat ..." $LINENO
#/opt/apache-tomcat/bin/startup.sh
#pgrep apache-tomcat 1>/dev/null
#if [ $? -ne 0 ];then
#    start_apache_tomcat
#fi   

#add start scripts of memcached, apache-tomcat and mysql to rc.local
#check if mysql startup is present in rc.local
RC_LOCAL=/etc/rc.d/rc.local
sed -i /mysql/d $RC_LOCAL
#chkconfig --add mysql
#chkconfig mysql on
#if [ $? != 0 ];then
#    grep "service mysql start" $RC_LOCAL  >/dev/null
#    if [ $? != 0 ]; then
#        PLOG_INFO "Adding mysql startup to $RC_LOCAL " $LINENO
#        echo "service mysql start" >> $RC_LOCAL 
#    fi
#fi
sed -i /memcached/d $RC_LOCAL
sed -i /apache-tomcat/d $RC_LOCAL
#grep "/usr/bin/memcached -p 11211 -m 1024 -u root &" $RC_LOCAL   >/dev/null
#if [ $? != 0 ]; then
#    PLOG_INFO "Adding memcached startup to $RC_LOCAL " $LINENO
#    echo "/usr/bin/memcached -p 11211 -m 1024 -u root &" >> $RC_LOCAL
#fi

#grep "/opt/apache-tomcat/bin/startup.sh" $RC_LOCAL  >/dev/null
#if [ $? != 0 ]; then
#    PLOG_INFO "Adding apache-tomcat startup to $RC_LOCAL " $LINENO
#    echo "/opt/apache-tomcat/bin/startup.sh" >> $RC_LOCAL
#fi    

#copy iwf service related files
mv -f $IWF_PATH/iwf/scripts/iwf.env /etc/sysconfig/iwf
mv -f $IWF_PATH/iwf/scripts/dre /etc/rc.d/init.d/
mv -f $IWF_PATH/iwf/scripts/pre-dre /etc/rc.d/init.d/

chkconfig --add dre
if [ $? == 0 ];then
    PLOG_INFO "iwf init script added to startup" $LINENO
else
    PLOG_ERROR "chkconfig -add failure!" $LINENO
fi
chkconfig --add pre-dre
if [ $? == 0 ];then
    PLOG_INFO "pre-dre script added to startup" $LINENO
else
    PLOG_ERROR "chkconfig -add failure!" $LINENO
fi



#create log dir and stats dir from the env variable
if [ ! -d $SSG_LOG_DIR ];then
    mkdir -p $SSG_LOG_DIR
fi

if [ ! -d $SSG_LOG_DIR/cdr ];then
    mkdir -p $SSG_LOG_DIR/cdr    
fi

if [ ! -d $IWF_STATS_DIR ];then
    mkdir -p $IWF_STATS_DIR
fi

if [ ! -d $IWF_STATS_DIR/archive ];then
    mkdir -p $IWF_STATS_DIR/archive
fi

if [ ! -d $IWF_SESS_TRACE_PATH ];then
    mkdir -p $IWF_SESS_TRACE_PATH
fi

if [ ! -d $IWF_SESS_TRACE_PATH/old ];then
    mkdir -p $IWF_SESS_TRACE_PATH/old    
fi

#deleting the previous crontab configuration
sed -i /iwf_logrotate/d /etc/crontab >/dev/null
sed -i /run_iwf_logrotate.sh/d /etc/crontab >/dev/null
sed -i /run_iwf_console_logrotate.sh/d /etc/crontab >/dev/null
sed -i /database_dump.sh/d /etc/crontab >/dev/null
sed -i /tracer.sh/d /etc/crontab >/dev/null
sed -i /archive_purge.sh/d /etc/crontab >/dev/null

if [ -e /opt/diametriq/iwf/scripts/run_iwf_logrotate.sh ];then
    echo "* * * * * root /opt/diametriq/iwf/scripts/run_iwf_logrotate.sh" >> /etc/crontab
fi

#add tracer.sh to crontab
if [ -e /opt/diametriq/iwf/scripts/tracer.sh ];then
    echo "* * * * * root /opt/diametriq/iwf/scripts/tracer.sh" >> /etc/crontab
fi

#add database_dump.sh to crontab
if [ -e /opt/diametriq/iwf/scripts/database_dump.sh ];then
    echo "30 0 * * * root /opt/diametriq/iwf/scripts/database_dump.sh" >> /etc/crontab
fi

service crond restart

SYSLOG_CONF=/etc/rsyslog.conf
TMP_CONF=/etc/rsyslog_tmp.conf
CAT_CONF=/etc/concat_rsyslog.conf
PLOG_INFO "Configuring syslog..." $LINENO
> $TMP_CONF
#backup original rsyslog conf
mkdir -p /etc/rsyslog_bkp
DATE=`date +%s`
cp -f $SYSLOG_CONF /etc/rsyslog_bkp/rsyslog_$DATE 

#deleting the previous version of syslog config
sed -i /avamgr.log/d $SYSLOG_CONF
sed -i /iwf.log/d $SYSLOG_CONF
sed -i /avamgr_error.log/d $SYSLOG_CONF
sed -i /avamgr_debug.log/d $SYSLOG_CONF
sed -i /Statslogger.log/d $SYSLOG_CONF
sed -i /iwf_debug.log/d $SYSLOG_CONF
sed -i /iwf_error.log/d $SYSLOG_CONF
sed -i /subagent.log/d $SYSLOG_CONF
sed -i /cmgr.log/d $SYSLOG_CONF
sed -i /cli.log/d $SYSLOG_CONF
sed -i /Webagent.log/d $SYSLOG_CONF
sed -i /SUBAGENT/d $SYSLOG_CONF
sed -i /IWF_CONTROLLER/d $SYSLOG_CONF
sed -i /STATSLOGGER/d $SYSLOG_CONF
sed -i /WEBAGENT/d $SYSLOG_CONF
sed -i /CLI/d $SYSLOG_CONF
sed -i /CMGR/d $SYSLOG_CONF
sed -i /IWF/d $SYSLOG_CONF
sed -i /AvailabilityManager/d $SYSLOG_CONF
sed -i /dquser/d $SYSLOG_CONF
sed -i /FileOwner.*root/d $SYSLOG_CONF
sed -i /FileCreateMode/d $SYSLOG_CONF
sed -i /DirCreateMode/d $SYSLOG_CONF
sed -i "s/ActionFileDefaultTemplate.*/ActionFileDefaultTemplate   RSYSLOG_FileFormat/g" $SYSLOG_CONF

#set permissions to dquser for all IWF logs
echo "\$FileOwner dquser" >> $TMP_CONF
echo "\$FileCreateMode 0644" >> $TMP_CONF
echo "\$DirCreateMode 0755" >> $TMP_CONF


    echo "if \$programname == 'IWF'  and (\$syslogseverity <= 3) then /var/log/iwf/iwf_error.log" >> $TMP_CONF
    echo "if \$programname == 'IWF'  and (\$syslogseverity <= 7) then /var/log/iwf/iwf_debug.log" >> $TMP_CONF
    echo "if \$programname == 'IWF' and (\$syslogseverity <= 7) then ~" >> $TMP_CONF

#CMGR logs
echo "if \$programname == 'CMGR'  and (\$syslogseverity <= 7) then /var/log/iwf/cmgr.log" >> $TMP_CONF
    echo "if \$programname == 'CMGR' and (\$syslogseverity <= 7) then ~" >> $TMP_CONF

#CLI logs
echo "if \$programname == 'CLI'  and (\$syslogseverity <= 7) then /var/log/iwf/cli.log" >> $TMP_CONF
echo "if \$programname == 'CLI' and (\$syslogseverity <= 7) then ~" >> $TMP_CONF

#AVMGR logs
echo "if \$programname == 'AvailabilityManager'  and (\$syslogseverity <= 3) then /var/log/iwf/avamgr_error.log" >> $TMP_CONF
echo "if \$programname == 'AvailabilityManager'  and (\$syslogseverity <= 7) then /var/log/iwf/avamgr_debug.log" >> $TMP_CONF
echo "if \$programname == 'AvailabilityManager' and (\$syslogseverity <= 7) then ~" >> $TMP_CONF

#SUBAGENT logs
echo "if \$programname == 'SUBAGENT'  and (\$syslogseverity <= 7) then /var/log/iwf/subagent.log" >> $TMP_CONF
echo "if \$programname == 'SUBAGENT' and (\$syslogseverity <= 7) then ~" >> $TMP_CONF


#reset the permissions to root for other files in rsyslog
echo "\$FileOwner root" >> $TMP_CONF
echo "\$FileCreateMode 0644" >> $TMP_CONF
echo "\$DirCreateMode 0755" >> $TMP_CONF

cat $TMP_CONF $SYSLOG_CONF >$CAT_CONF
LOG_DEBUG "Replacing the original rsyslog conf" $LINENO
mv -f $CAT_CONF $SYSLOG_CONF
rm -f $TMP_CONF
grep "SystemLogRateLimitInterval" $SYSLOG_CONF
if [ $? -eq 0 ];then
    LOG_DEBUG "Replace existing SystemLogRateLimitInterval.." $LINENO
    sed -i 's/$SystemLogRateLimitInterval.*/$SystemLogRateLimitInterval 0/' $SYSLOG_CONF
else
    sed -i '/ModLoad.*imuxsock.*/a $SystemLogRateLimitInterval 0' $SYSLOG_CONF
fi
service rsyslog restart

#enable coredump for iwf daemon
PLOG_INFO "Enabling coredump..." $LINENO
PLOG_INFO "Coredump location = /var/crash/iwf" $LINENO
mkdir -p /var/crash/iwf
grep "ulimit" /etc/profile  >/dev/null
if [ $? == 0 ];then
    sed -i "s/^ulimit.*/ulimit -c unlimited > \/dev\/null 2>\&1/" /etc/profile
else
    echo "" >> /etc/profile
    echo "ulimit -c unlimited > \/dev\/null 2>\&1/" >> /etc/profile
fi
# The suid_dumpable control file is found in different places ...
if [ -e /proc/sys/kernel/suid_dumpable ]; then
  echo 1 > /proc/sys/kernel/suid_dumpable
else
  echo 1 > /proc/sys/fs/suid_dumpable
fi
echo "/var/crash/iwf/core.%e.%p.%t" > /proc/sys/kernel/core_pattern


grep "fs.suid_dumpable" /etc/sysctl.conf    >/dev/null
if [ $? == 0 ];then
    sed -i "s/^fs.suid_dumpable.*/fs.suid_dumpable = 1/" /etc/sysctl.conf
else
    echo "" >> /etc/sysctl.conf
    echo "fs.suid_dumpable = 1" >> /etc/sysctl.conf
fi

grep "kernel.core_pattern" /etc/sysctl.conf   >/dev/null
if [ $? == 0 ];then
    sed -i "s/^kernel.core_pattern.*/kernel.core_pattern = \/var\/crash\/iwf\/core.%e.%p.%t/" /etc/sysctl.conf
else
    echo "" >> /etc/sysctl.conf
    echo "kernel.core_pattern = /var/crash/iwf/core.%e.%p.%t" >> /etc/sysctl.conf

sed -i /soft.*core.*unlimited/d /etc/security/limits.conf
fi

PLOG_INFO "Disabling Selinux..." $LINENO
echo 0 >/selinux/enforce
sed -i "s/SELINUX=enforcing.*/SELINUX=disabled/g" /etc/selinux/config
sed -i "s/SELINUX=permissive.*/SELINUX=disabled/g" /etc/selinux/config

%preun
source  /etc/package_functions.sh
#preuninstall stop all the services related to iwf
#stop iwf service
pgrep ^avamgr > /dev/null
if [ $? == 0 ];then
    PLOG_INFO "Stopping iwf service..." $LINENO
    service dre stop
fi

LOG_DEBUG "pgrep mysqld = `pgrep mysqld`" $LINENO
pgrep mysqld >/dev/null
if [ $? == 0 ];then
    stop mysqld
    LOG_DEBUG "pgrep mysqld = `pgrep mysqld`" $LINENO
    pgrep mysqld >/dev/null 
    if [ $? -eq 0 ];then
	PLOG_WARNING "Mysqld still running!" $LINENO
	PLOG_INFO "Killing mysql..." $LINENO
        pkill -9 mysqld
    fi
fi
ps -eaf|grep apache-tomcat|grep -v "grep"  >/dev/null
if [ $? == 0 ];then
    #/opt/apache-tomcat/bin/shutdown.sh 
    stop apache-tomcat   
fi
pgrep memcached >/dev/null
if [ $? == 0 ];then
    #pkill -9 memcached
    stop memcached
fi    

pgrep incrond >/dev/null
if [ $? -eq 0 ];then
    stop incrond
fi


%postun

rm -f /etc/ld.so.conf.d/iwf-x86_64.conf
rm -f /etc/profile.d/iwf.sh
rm -f /etc/logrotate.d/iwf_logrotate
chkconfig --del dre
chkconfig --del pre-dre
rm -f /etc/sysconfig/iwf
rm -f /etc/rc.d/init.d/dre
rm -f /etc/rc.d/init.d/pre-dre
#revert the changes to the file /etc/rc.d/rc.local
RC_LOCAL=/etc/rc.d/rc.local
sed -i /memcached/d $RC_LOCAL
sed -i /apache-tomcat/d $RC_LOCAL
sed -i /mysql/d $RC_LOCAL

sed -i /iwf_logrotate/d /etc/crontab
sed -i /archive_purge.sh/d /etc/crontab
rm -rf $IWF_PATH/iwf
