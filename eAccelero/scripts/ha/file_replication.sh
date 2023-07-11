#!/bin/bash
PRODUCT=iwf
# file replication

source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh
if test $# -lt 1
then
	echo "Usage, sh file_replication.sh [ install, update ]"
	exit 0
fi

operation=$1
config_file="/opt/diametriq/${PRODUCT}/config/config_dir_file.cfg"
user_account_name=`whoami`
username=`GetRemoteNodeUsername`
ipaddress=`GetRemoteNodeIP`
publickey_path="/root/.ssh/id_rsa.pub"

if [ "$operation" == "install" ] || [ "$operation" == "update" ]
then

    	flag=0
	if [ "$operation" == "install" ]
	then
        expect -f /opt/diametriq/${PRODUCT}/scripts/ssh_Automator.tcl keygen >>/var/log/${PRODUCT}/package.log 2>&1
        #expect -f ssh_Automator.tcl keygen >>/var/log/dre/package.log 2>&1
        ssh-add -D >>/var/log/${PRODUCT}/package.log 2>&1
        ssh-add >>/var/log/${PRODUCT}/package.log 2>&1
        PLOG_INFO "Remote Node ($ipaddress) configuration" $LINENO
        ssh-copy-id -i $publickey_path $username@$ipaddress
	    if [ $? -ne 0 ];then
		PLOG_ERROR "WRONG CREDENTIALS / COULD NOT CONNECT TO $ipaddress..." $LINENO
                flag=1
	    fi
	fi

	incrond_file="/var/spool/incron/$user_account_name"
	> $incrond_file

	for watch_path in `cat $config_file`
	do
		incrond_entry=""

		if [ -e "$watch_path" ]
		then
			if [ -d "$watch_path" ]
			then
				incrond_entry="$watch_path IN_MODIFY,IN_CREATE,IN_DELETE,IN_MOVE,IN_NO_LOOP rsync -rPvaz --exclude=\".*\" --delete $watch_path/ $username@$ipaddress:$watch_path"
			else
				incrond_entry="$watch_path IN_MODIFY,IN_CREATE,IN_DELETE,IN_MOVE,IN_NO_LOOP rsync -rPvaz --exclude=\".*\" --delete $watch_path $username@$ipaddress:$watch_path"
			fi

			echo $incrond_entry >> $incrond_file
		else
			echo "NOTE:- $watch_path doesn't exist, so skipped in incrontab configuration."
		fi
	done

    if [ "$flag" == "1" ];then
        PLOG_ERROR "Rsync Configuration Failed! Enter corrrect credentials / Restore connectivity to $ipaddress and reconfigure filesync using \"reconfigure.sh --filesync \" script" $LINENO
    else
	PLOG_INFO "Sucessfully configured !!!" $LINENO
    fi

else
	echo "Invalid operation, valid operations are [install, update]"
	exit 0
fi
