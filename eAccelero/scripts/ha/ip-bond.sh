#!/bin/bash

#source /opt/diametriq/dre/scripts/package_functions.sh
source /etc/package_functions.sh

PRODUCT=iwf

#array to hold the bond names
declare -a BOND_NAME
#array to hold the bond ips
declare -a BOND_IP
#array to hold the netmasks
declare -a BOND_NETMASK
#array to hold the interfaces(comma seperated)
declare -a BOND_NICS




MODCONF=/etc/modprobe.d/bond.conf

function destroy_bonding_and_backup_cfg()
{
    local NETWORK_SCRIPTS_PATH=/etc/sysconfig/network-scripts
    if [ ! -e /sys/class/net/bonding_masters ];then
        PLOG_INFO "No bonded interfaces found to destroy!" $LINENO
	return 1
    fi

    #create a directory to take backup
    if [ ! -d $NETWORK_SCRIPTS_PATH ];then
        mkdir -p $NETWORK_SCRIPTS_PATH/bkp
    fi
    

    local DATE=`date | tr -s " " | tr " " "_"`   
    BACKUP_PATH=$NETWORK_SCRIPTS_PATH/bkp/bond_$DATE


    #create a directory for primary ethernet interface files 
    mkdir -p $NETWORK_SCRIPTS_PATH/bkp/bond_$DATE/primary_interface
    cp `ls $NETWORK_SCRIPTS_PATH/ifcfg-eth* |sort|head -1` $NETWORK_SCRIPTS_PATH/bkp/bond_$DATE/primary_interface

    BONDS=`cat /sys/class/net/bonding_masters`
    if [ -z "$BONDS" ];then
	PLOG_INFO "No bonds found to destroy!" $LINENO
	return 1
    fi
    PLOG_INFO "BONDS to be destroyed= $BONDS" $LINENO
    mkdir -p $BACKUP_PATH
    echo "$BONDS" > $BACKUP_PATH/bonds.txt
    for bond in $BONDS
    do
        mkdir -p $BACKUP_PATH/$bond
        #remove all the slave interfaces associated with bond
        SLAVES=`cat /sys/class/net/$bond/bonding/slaves`
        PLOG_INFO "Slaves of $bond=$SLAVES" $LINENO
	echo "$SLAVES" > $BACKUP_PATH/$bond/slaves.txt
        for slave in $SLAVES
        do
	    PLOG_INFO "Removing slave $slave from $bond" $LINENO
	    echo "-$slave" > /sys/class/net/$bond/bonding/slaves
	    #remove or backup ifcfg-<slave>
            if [ -e $NETWORK_SCRIPTS_PATH/ifcfg-$slave ];then
	        mv  $NETWORK_SCRIPTS_PATH/ifcfg-$slave $BACKUP_PATH/$bond
  	    fi

        done
        

        ifconfig $bond down
        #remove all the bonding configurations
        PLOG_INFO "Destroying $bond" $LINENO
        echo "-$bond" > /sys/class/net/bonding_masters
        PLOG_INFO "Backup ifcfg-$bond" $LINENO
        #check if ifcfg-<bondname> exist if yes backup or delete
 	if [ -e $NETWORK_SCRIPTS_PATH/ifcfg-$bond ];then
            mv $NETWORK_SCRIPTS_PATH/ifcfg-$bond  $BACKUP_PATH/ 
	fi

    done
    /sbin/rmmod bonding
    if [ -f $MODCONF ];then
        sed -i /bonding/d $MODCONF
    fi
}

function ifdown()
{

    if [ "$1" = "" ];then
	echo "usage: $0 ifdown interface_name"
	return 1
    fi
    eval ifcfg="\$${1}"
    if [ "$ifcfg" = "dhcp" ];then
	if [ -f /var/run/dhcpcd-${1}.pid ];then
	    /bin/kill ${cat /var/run/dhcpd-${1}.pid}
	fi
    fi
    #Bringing the interface itself down
    /sbin/ifconfig ${1} down >/dev/null 2>&1
    return $?



}


#$1=bondname $2=IP Address $3=Netmask $4=InterfaceList $5(optional to configure default gateway) --gateway
function bond()
{
    BOND="/etc/sysconfig/network-scripts/ifcfg-$1"
        echo "Configuring bonding for $1..."
    if [ -e $BOND ];then
	rm -f $BOND
    fi
    echo "DEVICE=$1" > $BOND
    IP="$2"
    NETMASK="$3"
    echo "IPADDR=$IP" >> $BOND
    echo "NETMASK=$NETMASK" >> $BOND
    echo "USERCTL=no" >> $BOND
    echo "BONDING_OPTS=\"miimon=100 mode=1\"" >> $BOND
    echo "BOOTPROTO=none" >> $BOND
    echo "ONBOOT=yes" >> $BOND



    # Modifying the configuration of nics.
    NICS="$4"
    LOG_DEBUG "NICS----=$NICS" $LINENO
    for NIC in $NICS
    do
        
 
        NICPATH=/etc/sysconfig/network-scripts/ifcfg-$NIC
        BKP_NICPATH=/etc/sysconfig/network-scripts/$(date +%Y%m%d-%H%M).ifcfg-$NIC

        ifdown $NIC


        # Backing up existing cfg
	if [ -e $NICPATH ];then
            mv $NICPATH $BKP_NICPATH
	fi

        echo "DEVICE=$NIC" > $NICPATH
        echo "NM_CONTROLLED=no" >> $NICPATH
        echo "USERCTL=no" >> $NICPATH
        echo "ONBOOT=yes" >> $NICPATH
        echo "MASTER=$1" >> $NICPATH
        echo "SLAVE=yes" >> $NICPATH		
        echo "BOOTPROTO=none" >> $NICPATH
    done

}

# Setting up the parameters for bonding module.
function load_bond_module()
{
    

    if [ -f $MODCONF ]; then
        grep "^alias $1 bonding" $MODCONF >>/var/log/${PRODCUT}/package.log
	if [ $? -ne 0 ];then
            echo "alias $1 bonding" >> $MODCONF
	fi
	#/sbin/rmmod bonding
        /sbin/modprobe bonding
    else
        LOG_DEBUG "/etc/modprobe.d/bond.conf is not found" $LINENO
        echo "alias $1 bonding" >> /etc/modprobe.d/bond.conf
	#/sbin/rmmod bonding
	/sbin/modprobe bonding

    fi
    

    restart_network
    if [ -f  /proc/net/bonding/$1 ]; then
        echo "Loading of $1 bonding module successful."
    else
        echo "Issues loading $1 bonding module. Please check or reboot system."
    fi
}

#get_inputs
LOG_DEBUG "Parsing bonding configuration from /etc/${PRODUCT}.cfg" $LINENO

bond_names=`GetBondNames`
i=0
for name in $bond_names
do
    BOND_NAME[$i]=$name
    BOND_IP[$i]=`GetIPOfBond $name`
    BOND_NETMASK[$i]=`GetNetmaskOfBond $name`
    BOND_NICS[$i]=`GetInterfacesForBond $name`
    LOG_DEBUG "BOND_NAME$i=${BOND_NAME[$i]}" $LINENO
    
    LOG_DEBUG "BOND_IP$i=${BOND_IP[$i]}" $LINENO
    
    LOG_DEBUG "BOND_NETMASK$i=${BOND_NETMASK[$i]}" $LINENO

    LOG_DEBUG "BOND_NICS$i=${BOND_NICS[$i]}" $LINENO
    
    
   
    i=$(($i+1))    
done

destroy_bonding_and_backup_cfg

i=0
for name in ${BOND_NAME[@]}
do
    bond $name ${BOND_IP[$i]} ${BOND_NETMASK[$i]} "${BOND_NICS[$i]}" 

    i=$(($i+1))
done

#/sbin/rmmod bonding


for name in ${BOND_NAME[@]}
do
    load_bond_module $name
done
#restart network
#service network restart
