#!/bin/bash
#This is a script which takes care of database updation.
#This script is specific to a release

#---------------------------------NOTE--------------- -------------------------
#The values ( PREV_1, PREV_2, PREV_3) must be updated for every release.
#PREV_1 is the previous release 
#PREV_2 is the release which is previous to PREV_1
#PREV_3 is the release which is previous to PREV_2
#This script can handle database upgrade of maximum 3 releases.
#The appropriate database upgrade functions must be updated for every release
#Folowing are the functions to be updated
# 1) upgrade_PREV_3_to_PREV_2() :This function must contain the database 
#    transformation script for upgrading database from release $PREV_3 to 
#    release $PREV_2. Must be empty if there is no database change between
#    release $PREV_3 and release $PREV2.
#
# 2) upgrade_PREV_2_to_PREV_1() :This function must contain the database 
#    transformation script for upgrading database from release $PREV_2 to 
#    release  $PREV_1. Must be empty if there is no database change between
#    release $PREV_2 and release $PREV1
#
# 3) upgrade_PREV_1_to_CUR() :This function must contain the database 
#    transformation script for upgrading database from release $PREV_1 to 
#    release  $CUR_VER ( current version being installed).
#    Must be empty if there is no database change between
#    release $PREV_1 and release $CUR_VER



#------------------------------------------------------------------------------

PRODUCT=iwf

PREV_1=iwf-4.1.0-07
PREV_2=iwf-4.1.0-06
PREV_3=iwf-4.1.0-05

#CUR_VER=${CUR_DRE_VER%*_*}
#CUR_DRE_VER is from package_functions.sh script and it will have the value 

function enable_replication()
{
    echo ""
}

function disable_replication()
{
    echo ""
}

function upgrade_PREV_1_to_CUR()
{
###############
    disable_replication ### DONT REMOVE THIS LINE
#############

    LOG_INFO "upgrade_PREV_1_to_CUR" $LINENO
    #ADD THE REQUIRED DATABASE TRANSFORMATION STEPS for $PREV_1 to $CUR_VER
    #THIS FUNCTION IS TO BE LEFT EMPTY IF THERE ARE NO DATABASE CHANGES BETWEEN $PREV_1 AND $CUR_VER



##############
    enable_replication #DONT REMOVE THIS LINE
################
}

function upgrade_PREV_2_to_PREV_1()
{

############
    disable_replication #DONT REMOVE THIS LINE
############

    LOG_INFO "upgrade_PREV_2_to_PREV_1" $LINENO
    #ADD THE REQUIRED DATABASE TRANSFORMATION STEPS for $PREV_2 to $PREV_1
    #THIS FUNCTION IS TO BE LEFT EMPTY IF THERE ARE NO DATABASE CHANGES BETWEEN $PREV_2 AND $PREV_1


############
    enable_replication #DONT REMOVE THIS LINE
############
}

function upgrade_PREV_3_to_PREV_2()
{

############
    disable_replication #DONT REMOVE THIS LINE
###########

    LOG_INFO "upgrade_PREV_3_to_PREV_2" $LINENO
    #ADD THE REQUIRED DATABASE TRANSFORMATION STEPS for $PREV_3 to $PREV_2
    #THIS FUNCTION IS TO BE LEFT EMPTY IF THERE ARE NO DATABASE CHANGES BETWEEN $PREV_3 AND $PREV_2

###########
    enable_replication #DONT REMOVE THIS LINE
###########
}



function upgrade_script()
{
    DB_UPGRADE_VER=$1
    case $DB_UPGRADE_VER in
	$PREV_2*)
	    LOG_INFO "Execute upgrade script for $PREV_2" $LINENO
	    upgrade_PREV_3_to_PREV_2 
	    ;;
	$PREV_1*)
	    LOG_INFO "Execute upgrade script for $PREV_1" $LINENO
	    upgrade_PREV_2_to_PREV_1
	    ;;
	$CUR_DRE_VER*)
	    LOG_INFO "Execute upgrade script for $CUR_DRE_VER" $LINENO
	    upgrade_PREV_1_to_CUR
	    ;;
    esac
}

# $1= Previous version installed in the system
#call upgrade scripts from previous version+1 to current version being installed in sequence
function upgrade_database()
{
    PREV_INSTALLED_VER=$1
    VER=$1
    while [ "$VER" != "$CUR_DRE_VER" ]
    do
	case $VER in
	    $PREV_3*)
		if [ "$VER" == "$PREV_INSTALLED_VER" ];then
		    VER=$PREV_2
           	    continue
        	fi 
		LOG_INFO "Running upgrade script for $PREV_3" $LINENO
		upgrade_script $VER 
	    	VER=$PREV_2
		;;

	    $PREV_2*)
		if [ "$VER" == "$PREV_INSTALLED_VER" ];then
                    VER=$PREV_1
                    continue
                fi
		LOG_INFO "Running upgrade script for $PREV_2" $LINENO
		upgrade_script $VER
		VER=$PREV_1
		;;

	    $PREV_1*)
		if [ "$VER" == "$PREV_INSTALLED_VER" ];then
                    VER=$CUR_DRE_VER    
                    continue
                fi
		LOG_INFO "Running upgrade script for $PREV_1" $LINENO
		upgrade_script $VER
		VER=$CUR_DRE_VER
		
		;;
	    $CUR_DRE_VER*)
		LOG_INFO "Running upgrade script for $CUR_DRE_VER" $LINENO
		upgrade_script $VER
		;;
	    *)
		LOG_INFO "Cannot upgrade, Upgrade script not upto date or $PREV_3 and above versions should be installed to support proper db upgrade" $LINENO
        ############
        enable_replication #DONT REMOVE THIS LINE
        ############
		exit 1
		;;
	esac

    done
    PLOG_INFO "Running db upgrade script for $CUR_DRE_VER" $LINENO
    upgrade_script $CUR_DRE_VER

}

function local_host_db_update()
{
    LOG_DEBUG "function local_host_db_update start" $LINENO
    LOG_DEBUG "Emptying LocalHostConfigT" $LINENO
    ${my2} "${unset_sess_repl} delete from LocalHostConfigT"
    if [ $? != 0 ];then
        LOG_ERROR "delete from LocalHostConfigT failed" $LINENO
        exit 1
    fi
    LOG_DEBUG "Inserting into LocalHostConfigT" $LINENO
   
    ${my} "${unset_sess_repl} INSERT INTO LocalHostConfigT (HostName,RealmName ) VALUES ('$LocalHostName','$LocalRealmName')"
    ${my} "${unset_sess_repl} INSERT INTO LOCAL_TRANSPORT_TB (TRANSPORT_TYPE,IP_ADDRESS,PORT,LocalHostConfigID) VALUES ('$LocalTransportType','$LocalIpAddress','$LocalPort',(select LocalHostConfigID from LocalHostConfigT where HostName = '$LocalHostName' and RealmName = '$LocalRealmName'))"
  
    if [ $? != 0 ];then
        LOG_ERROR "INSERT INTO LocalHostConfigT" $LINENO
        exit 1
    fi

    ${my1} < $DRE_ROOT/scripts/install_functions.sql
    ${my1} < $DRE_ROOT/scripts/trigger_fun.sql
 
    LOG_DEBUG "fucntion local_host_db_update end" $LINENO
}

source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh
if [ "$PRODUCT" == "iwf" ];then
    CUR_DRE_VER=$CUR_IWF_VER
fi
CUR_VER=${CUR_DRE_VER%*_*}
if [ "$PREV_1" == "$CUR_VER" ] || [ "$PREV_2" == "$CUR_VER" ] || [ "$PREV_3" == "$CUR_VER" ];then

    PLOG_ERROR "Wrong Database upgrage script!!" $LINENO
    PLOG_WARNING "Database is not altered!" $LINENO
    exit 0 

fi


USERNAME=`GetMysqlUsername`
LOG_INFO "$USERNAME" $LINENO
PASSWORD=`GetMysqlPassword`
LOG_INFO "$PASSWORD" $LINENO
IP=`GetMysqlIpAddress`
LOG_INFO "$IP" $LINENO
PORT=`GetMysqlPort`
LOG_INFO "$PORT" $LINENO


LocalHostName=$( GetLocalHostName )
LOG_INFO "LocalHostName=$LocalHostName" $LINENO
LocalRealmName=$( GetLocalRealmName )
LOG_INFO "LocalRealmName=$LocalRealmName" $LINENO
LocalIpAddress=$( GetLocalIpAddress )
LOG_INFO "LocalIpAddress=$LocalIpAddress" $LINENO
LocalPort=$( GetLocalPort )
LOG_INFO "LocalPort=$LocalPort" $LINENO
LocalTransportType=$( GetLocalTransportType )
LOG_INFO "LocalTransportType=$LocalTransportType" $LINENO


LOG_INFO "PREV_1 = $PREV_1 | PREV_2 = $PREV_2 | PREV_3 = $PREV_3 | CUR_DRE_VER = $CUR_DRE_VER" $LINENO
my2="mysql  --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT --database=DIAMETRIQ -se"
my1="mysql  --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT "
my="mysql  --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT -se"
unset_sess_repl="set @@session.sql_log_bin=0;"
/opt/diametriq/${PRODUCT}/scripts/configCmgr.sh "TCP" $USERNAME $PASSWORD $IP $PORT
if [ $? != 0 ];then
    LOG_ERROR "$DRE_ROOT/scripts/configCmgr.sh failed!" $LINENO 
    exit 1
fi

#get the previous dre version that is installed 
if [ -n `rpm -q ${PRODUCT}|grep -v "Not installed"|tail -2|head -1` ];then
    PREV_INSTALLED_VER=`rpm -q ${PRODUCT}|tail -2|head -1`
    PREV_INSTALLED_VER=${PREV_INSTALLED_VER%*.*}
    LOG_INFO "PREV_INSTALLED_VER=$PREV_INSTALLED_VER" $LINENO

    ############
    disable_replication  #DONT REMOVE THIS LINE
    ############

    upgrade_database $PREV_INSTALLED_VER

    ############
    enable_replication #DONT REMOVE THIS LINE
    ############

    #local_host_db_update
fi   

exit 0
