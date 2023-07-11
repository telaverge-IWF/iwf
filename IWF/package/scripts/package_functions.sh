CUR_DRE_VER=dre-3.2.0-06_split_brain
CUR_IWF_VER=iwf-3.3.4.4-Release
PRODUCT=iwf

if [ -z $PRODUCT ];then
    S_PRODUCT_NAME=dre
    PRODUCT_NAME=DRE
elif [ $PRODUCT = "dre" ];then
    S_PRODUCT_NAME=dre
    PRODUCT_NAME=DRE
elif [ $PRODUCT = "iwf" ];then
    S_PRODUCT_NAME=iwf
    PRODUCT_NAME=IWF
fi

#Do not change the above value, value is set automatically by the package.sh script
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red
txtgrn='\e[0;32m' # Green
txtylw='\e[0;33m' # Yellow
txtblu='\e[0;34m' # Blue
txtpur='\e[0;35m' # Purple
txtcyn='\e[0;36m' # Cyan
txtwht='\e[0;37m' # White
bldblk='\e[1;30m' # Black - Bold
bldred='\e[1;31m' # Red
bldgrn='\e[1;32m' # Green
bldylw='\e[1;33m' # Yellow
bldblu='\e[1;34m' # Blue
bldpur='\e[1;35m' # Purple
bldcyn='\e[1;36m' # Cyan
bldwht='\e[1;30;37m' # White
unkblk='\e[4;30m' # Black - Underline
undred='\e[4;31m' # Red
undgrn='\e[4;32m' # Green
undylw='\e[4;33m' # Yellow
undblu='\e[4;34m' # Blue
undpur='\e[4;35m' # Purple
undcyn='\e[4;36m' # Cyan
undwht='\e[4;37m' # White
bakblk='\e[40m'   # Black - Background
bakred='\e[41m'   # Red
bakgrn='\e[42m'   # Green
bakylw='\e[43m'   # Yellow
bakblu='\e[44m'   # Blue
bakpur='\e[45m'   # Purple
bakcyn='\e[46m'   # Cyan
bakwht='\e[47m'   # White
txtrst='\e[0m'    # Text Reset
#internal config file produced while installing, the same will be used while upgrade,rollback 

DRE_CONFIG=/etc/${S_PRODUCT_NAME}.cfg
MYSQL_CNFPATH=/etc/my.cnf

DB_UPGRADE_FAILURE=65

#config variables
BONDING_CFG=1
LOCALHOST_CFG=2
MYSQL_CFG=3
TIPC_CFG=4
HEARTBEAT_CFG=5
ALARM_CFG=6
NTP_CFG=7
SIGTRAN_CFG=8


DRE_CNF_FILE=""

STANDALONE_TO_ACTIVESTANDBY="no"
#this function returns the value of the field name passed 
#$1 = field name passed
function get_dre_cnf_val()
{
    sed -n s/^$1=//p $DRE_CNF_FILE
}

#mysql global variables
MySQL_Local_IP="127.0.0.1"
MySQL_Port="3306"

#variables to hold config parameters that are parsed, which will be used during the installation
dre_install_mode=""
bonding=""
number_of_bonds=""


#bond0
ip_bond0=""
interface1_bond0=""
interface2_bond0=""

#bond1
bond1_ip=""
interface1_bond1=""
interface2_bond1=""

#Mysql Heartbeat configurations
mysql_local_ip=""
mysql_mate_ip=""
mysql_mate_hostname=""
ha_mode=""
#virtual ip in cidr notation
mysql_virtual_ip=""
mysql_interface_name=""

#Mysql configuration
mysql_username="root"
mysql_root_password=""

#Local Host Configuration
host_name=""
realm_name=""
ip_address=""
public_ip_address=""
port=""
transport_type=""
port2=""
transport_type2=""
secure_port=""
tranport_type3=""


#sigtran configuration
#specific to IWF
point_code=""
ssn=""
tcap_invoke_timer=""
global_title_indicator=""
nature_of_address_indicator=""
global_title_address_information=""
translation_type=""
numbering_plan=""
encoding_scheme=""
routing_indicator=""
self_sccp_addr_use_from_config=""
use_sccp_cdpa_from_incomming_msg=""
has_ssn=""
has_pc=""
selection_criteria=""
###############



#TIPC Configuration
net_id=""
tipc_node_address=
bearer_name=""

#Alarms configuration
declare -a trap_sink_ip


#NTP server Configuration
ntp_server_ip=""


#couchbase configurations
ram_size=""


#$1=list , $2=-i(optional) if passed dont print errors
function validate_filled()
{ 
    local list="$1"
    RET=0
    for item in $list
    do
        if [ -z `get_dre_cnf_val "$item"` ];then
            PLOG_ERROR "\"$item\" not configured" $LINENO
            RET=1
        else
            LOG_DEBUG "$item is present" $LINENO
        fi
    done
    return $RET
}

function validate_ip_list()
{
    local list="$1"
    RET=0
    for item in $list
    do
        LOG_DEBUG "item=$item" $LINENO
        ipcalc -cs `get_dre_cnf_val "$item"`
        if [ $? -ne 0 ];then
            PLOG_ERROR "$item = `get_dre_cnf_val "$item"` not a valid IP Address!" $LINENO
            RET=1
        else
            LOG_DEBUG "$item is valid" $LINENO
        fi
    done
    return $RET

}
#gets the interface list associated with all bonded interfaces 
function GetInterfaceList()
{
    cat $DRE_CNF_FILE |grep "^interface._"|cut -d'=' -f2  
}

function validate_interfaces()
{
    local list="$1"
    RET=0
    for item in $list
    do
	LOG_DEBUG "item=$item" $LINENO
        ifconfig $item up 2>>/var/log/${S_PRODUCT_NAME}/package.log
	if [ $? -ne 0 ];then
	    PLOG_ERROR "Interface $item does not exist in this system!" $LINENO
	    RET=1
	else
	    LOG_DEBUG "Interface $item is valid" $LINENO
	fi 
    done
    return $RET

}


#validate duplicate interface names for bonding
function validate_duplicate_interfaces()
{
    RET=0
    local LIST=`GetInterfaceList`
    if [ -n "`echo "$LIST"|sort|uniq -d`" ];then
	PLOG_ERROR "2 or more interfaces for bonding cannot be same! (`echo "$LIST"|sort|uniq -d`)" $LINENO
	RET=1
    fi
    return $RET

}

#compares 2 ips, if both are in the same subnet it returns 0 , else 1
#1 and #2 are ips
function subnet_cmp()
{
    LOG_DEBUG "IP1= $1 IP2= $2" $LINENO
    local BCAST_IP1=`ipcalc -b "$1"|cut -d'=' -f2` 
    local BCAST_IP2=`ipcalc -b "$2"|cut -d'=' -f2`
    local RET=0
    LOG_DEBUG "bcast_ip1=$BCAST_IP1  bcast_ip2=$BCAST_IP2" $LINENO

    if [ "$BCAST_IP1" == "$BCAST_IP2" ];then
        RET=0
    else
        RET=1
    fi

    return $RET

}

#validate mysql vip
function validate_mysql_vip()
{
    local len=${#bond_name[@]}
    local ip=""
    local RET=0
    local i=0
    if [ "$bonding" == "yes" ];then
        for (( i=0; i<${len}; i++ ));
        do
            if [ "$mysql_interface_name" == "${bond_name[$i]}" ];then
	        break
            fi
        done
	   
        if [ $i -lt $len ];then
            ip=${bond_cidr_ip[$i]}
	    subnet_cmp "$ip" "$mysql_virtual_ip"
	    if [ $? -ne 0 ];then
	        PLOG_ERROR "MySQL Virtual IP and the $mysql_interface_name IP should be in same subnet!" $LINENO
		RET=1
	    fi  	    
	else
	    PLOG_ERROR "Invalid \"mysql_interface_name\" OR \"$mysql_interface_name\" is not a bonded interface!" $LINENO
            RET=1
        fi
        
    else
	LOG_INFO "bonding = no" $LINENO
	ip=`ifconfig "$mysql_interface_name" | grep Bcast | tr -s " " | cut -d " " -f4 | cut -d ":" -f2`
	if [ -n "$ip" ];then
	    LOG_DEBUG "$mysql_interface_name bcast IP=$ip" $LINENO
	    if [ "`ipcalc -b "$mysql_virtual_ip"|cut -d'=' -f2`" == "$ip" ];then
	        RET=0
	    else
		RET=1
		PLOG_ERROR "MySQL Virtual IP and the $mysql_interface_name IP should be in same subnet!" $LINENO
	    fi
	else
	    PLOG_ERROR "Invalid interface:$mysql_interface_name / No IP Assigned to $mysql_interface_name" $LINENO	    
	    RET=1
	fi
    fi

    return $RET
}

function validate_mate_hostname()
{
    local RET=0
    if [ "$mysql_mate_hostname" == "`uname -n`" ];then
  	RET=1
	PLOG_ERROR "Local hostname and Mate Hostname are same!" $LINENO
    fi

    return $RET
}

function validate_transport_type()
{
    local RET=0
    local transport="`echo $1|tr [:lower:] [:upper:]`"
    if [ "$transport" == "TCP" ] || [ "$transport" == "SCTP" ];then
	RET=0
    else
	PLOG_ERROR "Invalid transport_type :$1 \n Should be TCP/SCTP" $LINENO
	RET=1
    fi
   
    return $RET

}


function validate_mysql_cnf()
{

    mysql_cfg_list="mysql_root_password"
    validate_filled "$mysql_cfg_list"
    if [ $? -ne 0 ];then
       PLOG_ERROR "Configure proper values for Mysql section!" $LINENO
       exit 1
    fi

}

function validate_install_mode_cnf()
{
   #validate if everything is not null
   if [ "$PRODUCT" == "dre" ];then
       validate_filled "dre_install_mode"
       if [ $? -ne 0 ];then
           exit 1
       fi
       elif [ "$PRODUCT" == "iwf" ];then
       validate_filled "install_mode"
       if [ $? -ne 0 ];then
           exit 1
       else
	   validate_possible_values "install_mode" "1 3"
	   if [ $? -ne 0 ];then
		exit 1
	   fi
       fi

   fi

}


function validate_localhost_cnf()
{

   localhost_cfg__list="host_name realm_name ip_address"
    validate_filled "$localhost_cfg__list"
    if [ $? -ne 0 ];then
       PLOG_ERROR "Configure proper values for Local_host section!" $LINENO
       exit 1
    fi
      
    validate_ip_list "ip_address"
    if [ $? -ne 0 ];then
        exit 1
    fi 

    if [ -n "$public_ip_address" ];then
        validate_ip_list "public_ip_address"
    fi

    local transport1_filled=0
    local transport2_filled=0
    local transport3_filled=0
    local port1_filled=0
    local port2_filled=0
    local port3_filled=0

    if [ -n "$port" ];then
 	 port1_filled=1
    fi
    if [ -n "$port2" ];then 
	 port2_filled=1
    fi
    if [ -n "$secure_port" ];then
	 port3_filled=1
    fi


    if [ -n "$transport_type" ];then
        validate_transport_type "$transport_type"
        if [ $? -ne 0 ];then
            exit 1
        else
	   if [ "$port1_filled" == "1" ];then
	       transport1_filled="1"
	   fi
       fi
       
   fi



   #if transport type2 is present
   if [ -n "$transport_type2" ];then
       validate_transport_type "$transport_type2"
       if [ $? -ne 0 ];then
           exit 1
       else
	   if [ "$port2_filled" == "1" ];then
	       transport2_filled="1"
	   fi
       fi
        
   fi

   #if transport type2 is present
   if [ -n "$transport_type3" ];then
       validate_transport_type "$transport_type3"
   if [ $? -ne 0 ];then
      exit 1
       else
	   if [ "$port3_filled" == "1" ];then
	       transport3_filled="1"
	   fi
       fi

   fi
 
 
   if [ "$transport1_filled" == "1" ] || [ "$transport2_filled" == "1" ] || [ "$transport3_filled" == "1" ];then
	LOG_DEBUG "Atlest one transport configured" $LINENO
   else
	PLOG_ERROR "Atleast 1 transport should be configured!" $LINENO
	exit 1
   fi

}

function validate_tipc_cnf()
{

    tipc_cfg_list="net_id tipc_node_address bearer_name"
    validate_filled "$tipc_cfg_list"
    if [ $? -ne 0 ];then
        PLOG_ERROR "Configure proper values for Tipc section!" $LINENO
        exit 1
    fi
   
    validate_range  "net_id" 1000 9999
    if [ $? -ne 0 ];then
	exit 1
    fi

    
    echo "$tipc_node_address" |grep "^.\..\..$" >/dev/null
    if [ $? -ne 0 ];then
	PLOG_ERROR "Invalid format: tipc_node_address" $LINENO
	exit 1
    else
	local nodeAddr=`echo "$tipc_node_address" |grep "^.\..\..$"`	
	local first_digit=`echo "$nodeAddr" | cut -d'.' -f1`
	local second_digit=`echo "$nodeAddr" | cut -d'.' -f2`
 	local third_digit=`echo "$nodeAddr" | cut -d'.' -f3`
	local flag=0
	if [ $first_digit -lt 1 ] || [ $first_digit -gt 255 ];then
	    flag=1
	fi

	if [ $second_digit -lt 1 ] || [ $second_digit -gt 255 ];then
	    flag=1
	fi

	if [ $third_digit -lt 1 ] || [ $third_digit -gt 255 ];then
	    flag=1
	fi

	if [ "$flag" == "1" ];then
	    PLOG_ERROR "Invalid tipc_node_address" $LINENO
	    exit 1	
	fi	

    fi

    echo "$bearer_name" | grep "^eth:" >/dev/null
    if [ $? -ne 0 ];then
	PLOG_ERROR "Invalid bearer_name format!" $LINENO
	PLOG_ERROR "syntax : eth:<interface_name>" $LINENO
	exit 1
    else
	ip addr show |grep `echo "$bearer_name"|cut -d':' -f2` >/dev/null
	if [ $? -ne 0 ];then
	   PLOG_ERROR "Invalid interface : `echo "$bearer_name"|cut -d':' -f2`" $LINENO
	   PLOG_ERROR "Interface `echo "$bearer_name"|cut -d':' -f2` is not present in the system" $LINENO
	   exit 1 
	fi	
    fi 


    #check if tipc module is in use
    tipc_mod_state=`lsmod|grep tipc|tr -s " " " "|cut -d' ' -f3`
    if [ ! -z "$tipc_mod_state" ];then
        if [ "$tipc_mod_state" != "0" ];then
	        PLOG_ERROR "TIPC Module is in use by some other Process/Module" $LINENO
	        PLOG_ERROR "Stop the process/module and retry" $LINENO
	        exit 1
        fi
    fi

}

function validate_bonding()
{
    if [ "$bonding" == "yes" ];then
       #validate the bonding interfaces selected
       LOG_DEBUG "bonding=yes" $LINENO
       validate_interfaces "`GetInterfaceList`"
       if [ $? -ne 0 ];then
          exit 1
       fi
       validate_duplicate_interfaces
       if [ $? -ne 0 ];then
          exit 1
       fi
       
    fi
    
}

function validate_ntp_cnf()
{
       validate_filled "ntp_server_ip"
       if [ $? -ne 0 ];then
	       PLOG_ERROR "Configure proper NTP server IP in the NTP section" $LINENO
           exit 1
       fi
	
      validate_ip_list "ntp_server_ip"
       if [ $? -ne 0 ];then
           exit 1
       fi

}

function validate_mysql_heartbeat_cnf()
{

   mysql_heartbeat_cfg__list="mysql_local_ip mysql_mate_ip mysql_mate_hostname ha_mode \

   mysql_virtual_ip mysql_interface_name"
    validate_filled "$mysql_heartbeat_cfg__list"
    if [ $? -ne 0 ];then
       PLOG_ERROR "Configure proper values for Mysql_heartbeat section!" $LINENO
       exit 1
    fi
       #check if localhost name and mate hostname are  unique and different
    #if [ "$mysql_mate_hostname" == "`uname -n`" ];then
    #       PLOG_ERROR "mysql_mate_hostname and localhostname should not be same!" $LINENO
    #    exit 1
    #fi

    ip_address_list="mysql_local_ip  mysql_mate_ip  mysql_virtual_ip "
       validate_ip_list "$ip_address_list"
       if [ $? -ne 0 ];then
           exit 1
       fi
    validate_mysql_vip   
    if [ $? -ne 0 ];then
        exit 1
    fi
    #validate_mate_hostname
    #if [ $? -ne 0 ];then
	#exit 1
    #fi

}

#if $1= --upgrade then validate only acrive-standby related parameters
function validate_dre_cnf_inputs()
{
    #basic validation include checking if they are not null
   local RET=0
   validate_install_mode_cnf


       validate_mysql_cnf

       validate_localhost_cnf
       
       if [ "$PRODUCT" == "iwf" ];then
           	   #validate point_code
	   #validate ssn
	   #validate tcap_invoke_timer   
	   validate_sigtran_config
	   if [ $? -ne 0 ];then
		exit 1
	   fi
       fi

       validate_tipc_cnf

   #if [ "$dre_install_mode" == "2" ];then
    validate_ntp_cnf
      
   #fi
   
    
    
    validate_bonding
    if [ "$dre_install_mode" == "2" ] || [ "$dre_install_mode" == "3" ] || [ "$dre_install_mode" == "4" ];then
        validate_mysql_heartbeat_cnf


    fi
      
    #validate the couchbase configurations
    check_and_validate_couchbase_cfg
    if [ $? -ne 0 ];then
	exit
    fi
      
}

#$1=name $2=value
function set_dre_cfg()
{
    LOG_DEBUG "set_dre_cfg $1=$2" $LINENO
    grep "$1" $DRE_CONFIG  >/dev/null 2>&1
    if [ $? -eq 0 ];then
        #replace the value
	#check if its Cidr_IP to handle the sed error case
	echo "$1"|grep "Cidr_IP" >>/var/log/${S_PRODUCT_NAME}/package.log
	if [ $? -eq 0 ];then
	    CIDR_BOND_IP="`echo "$1"|cut -d'_' -f1`"
	else
	    CIDR_BOND_IP="null"
	fi
        if [ "$1" == "VirtualIP" ] || [ "$1" == "IPBond0" ] || [ "$1" == "IPBond1" ] || [ "$CIDR_BOND_IP" == "Cidr" ];then
            sed -i "s/^$1=.*/$1=`convert_cidrip_to_sed_cirdrip "$2"`/g" $DRE_CONFIG
        else
            sed -i "s/^$1=.*/$1=$2/g" $DRE_CONFIG
       
        fi
    else
        echo "$1=$2" >> $DRE_CONFIG
        #append the value
    fi
}


function upgade_install_mode_in_dre_cfg()
{

    set_dre_cfg "DreInstallMode" "$dre_install_mode"
}

function update_mysql_in_dre_cfg()
{
    set_dre_cfg "MysqlUsername" "$mysql_username"
    set_dre_cfg "MysqlPassword" "$mysql_root_password"
    set_dre_cfg "MysqlIpAddress" "$MySQL_Local_IP"
    set_dre_cfg "MysqlPort" "$MySQL_Port"

}

function update_localhost_in_dre_cfg()
{
    set_dre_cfg "LocalHostName" "$host_name"
    set_dre_cfg "LocalRealmName" "$realm_name"
    set_dre_cfg "LocalIpAddress" "$ip_address"
    if [ -z "$public_ip_address" ];then
	#store NULL if public_ip_address is not passed in dre_cnf file
	set_dre_cfg "PublicIpAddress" "NULL"
    else
	set_dre_cfg "PublicIpAddress" "$public_ip_address"
    fi
    if [ -z "$port" ];then
	set_dre_cfg "LocalPort" "NULL"
    else
	set_dre_cfg "LocalPort" "$port"

    fi

    if [ -z "$transport_type" ];then
	set_dre_cfg "LocalTransportType" "NULL"
    else
        set_dre_cfg "LocalTransportType" "`if [ "$transport_type" == "SCTP" ];then echo "2"; else echo "1";fi` "
    fi


        #set_dre_cfg "LocalPort" "$port"
        #set_dre_cfg "LocalTransportType" "`if [ "$transport_type" == "SCTP" ];then echo "2"; else echo "1";fi` "
        	
    if [ -z "$port2" ];then
	set_dre_cfg "LocalPort2" "NULL"
    else
	set_dre_cfg "LocalPort2" "$port2"
    fi

        
    if [ -z "$transport_type2" ];then
	set_dre_cfg "LocalTransportType2" "NULL"
    else
	set_dre_cfg "LocalTransportType2" "`if [ "$transport_type2" == "SCTP" ];then echo "2"; else echo "1";fi` "
    fi
     
    if [ -z "$secure_port" ];then
	set_dre_cfg "SecureLocalPort" "NULL"
    else
	set_dre_cfg "SecureLocalPort" "$secure_port"
    fi

    if [ -z "$transport_type3" ];then
	set_dre_cfg "LocalTransportType3" "NULL"
    else
	set_dre_cfg "LocalTransportType3" "`if [ "$transport_type3" == "SCTP" ];then echo "2"; else echo "1";fi` "
    fi

}

function update_tipc_in_dre_cfg()
{
    set_dre_cfg "NetID" "$net_id"
    set_dre_cfg "TipcNodeAddress" "$tipc_node_address"
    set_dre_cfg "BearerName" "$bearer_name"

}


function update_alarm_in_dre_cfg()
{
  #TrapSinkIP
   #set the trapsinki ips from the array
   i=0
   #delete the trap sink IPs 
   sed -i /"^TrapSinkIP"/d  $DRE_CONFIG
   for ip in "${trap_sink_ip[@]}"
   do
       i=$((i + 1))
       LOG_DEBUG "$ip " $LINENO
       set_dre_cfg "TrapSinkIP$i" "$ip"
   done

}

function update_ntp_in_dre_cfg()
{

    set_dre_cfg "NtpServerIP" "$ntp_server_ip"
}


function update_mysql_heartbeat_in_dre_cfg()
{
        #set_dre_cfg "HAMode" "`echo "$ha_mode"| tr '[:lower:]' '[:upper:]'`"
        set_dre_cfg "VirtualIP" "$mysql_virtual_ip"
        set_dre_cfg "Ethernet" "$mysql_interface_name"
        set_dre_cfg "BroadcastAddress" "`/bin/ipcalc $mysql_virtual_ip -b|cut -d"=" -f2`"
        set_dre_cfg "SubNetMaskPrefixLen" "`/bin/ipcalc $mysql_virtual_ip -p|cut -d"=" -f2`"
        set_dre_cfg "MysqlLocalIP" "$mysql_local_ip"
        set_dre_cfg "MysqlMateIP" "$mysql_mate_ip"
        set_dre_cfg "MysqlLocalHostname" "`uname -n`"
        #set_dre_cfg "MysqlMateHostname" "$mysql_mate_hostname"

}

function update_couchbase_in_dre_cfg()
{

    set_dre_cfg "ClusterRAM" $ram_size
}

function update_install_mode_in_dre_cfg()
{
    set_dre_cfg "DreInstallMode" "$dre_install_mode"
}

#after parsing and validating config file,  add the config values to the existing $PRODUCT.cfg file
#if $1 = --upgrade then update only active-standby related parameters in ${S_PRODUCT_NAME}.cfg file
function update_dre_cfg()
{
    LOG_DEBUG "update_dre_cfg" $LINENO
    if [ $# -eq 0 ];then
	update_install_mode_in_dre_cfg
        update_mysql_in_dre_cfg
           
        update_localhost_in_dre_cfg
	update_tipc_in_dre_cfg
	if [ "$PRODUCT" == "iwf" ];then
	    update_sigtrancfg_in_iwfcfg
	fi

 
	update_ntp_in_dre_cfg
      	update_alarm_in_dre_cfg
    fi
    #set the bonding config
    update_bonding_in_dre_cfg

    if [ "$dre_install_mode" == "2" ] || [ "$dre_install_mode" == "3" ] || [ "$dre_install_mode" == "4" ];then
 	update_mysql_heartbeat_in_dre_cfg
    fi

    #update the couchbase configurations in /etc/dre.cfg only 
    if [ "$dre_install_mode" == "4" ];then
	update_couchbase_in_dre_cfg
    fi

}

function is_standalone_to_activestandby_upgrade()
{
    local RET
    if [ "$STANDALONE_TO_ACTIVESTANDBY" == "yes" ];then
        RET=0
	LOG_DEBUG "STANDALONE_TO_ACTIVESTANDBY=yes" $LINENO
	echo "yes"
    else
	RET=1
	LOG_DEBUG "STANDALONE_TO_ACTIVESTANDBY=no" $LINENO
	echo "no"
    fi

    return $RET
}

function parse_couchbase_cfg_from_usr_cnf()
{
   
    #parse the couchbase configuration only if dre_install_mode == 4
    if [ "$dre_install_mode" == "4" ];then
	LOG_DEBUG "Parsing couchbase config form user_dre.cnf" $LINENO
        ram_size=`get_dre_cnf_val "ram_size"` 
        calculate_ram_for_couchbase
	
    fi 

}

#done as part of parsing user dre cnf
function check_and_validate_couchbase_cfg()
{
    local ret=0
    #check if dre_install_mode == 4
    if [ "$dre_install_mode" == "4" ];then
	#check ram_size configured is available in the system
	if [ $ram_available -lt $ram_size ];then
	    PLOG_ERROR "Not enough RAM available for couchbase" $LINENO
	    PLOG_INFO "Available RAM=$ram_available MB" $LINENO
	    PLOG_INFO "RAM configured=$ram_size MB" $LINENO
	    ret=1
	fi
    fi

    return $ret

}

#function to parse all the sigtran related config
function parse_sigtran_config()
{
    #sigtran configuration
    point_code=`get_dre_cnf_val "point_code"`
    ssn=`get_dre_cnf_val "ssn"`
    tcap_invoke_timer=`get_dre_cnf_val "tcap_invoke_timer"`
    global_title_indicator=`get_dre_cnf_val "global_title_indicator"`
    nature_of_address_indicator=`get_dre_cnf_val "nature_of_address_indicator"`
    global_title_address_information=`get_dre_cnf_val "global_title_address_information"`
    translation_type=`get_dre_cnf_val "translation_type"`
    numbering_plan=`get_dre_cnf_val "numbering_plan"`
    encoding_scheme=`get_dre_cnf_val "encoding_scheme"`
    
    routing_indicator=`get_dre_cnf_val "routing_indicator"`
    self_sccp_addr_use_from_config=`get_dre_cnf_val "self_sccp_addr_use_from_config"`
    use_sccp_cdpa_from_incomming_msg=`get_dre_cnf_val "use_sccp_cdpa_from_incomming_msg"`
    has_ssn=`get_dre_cnf_val "has_ssn"`
    has_pc=`get_dre_cnf_val "has_pc"`

    selection_criteria=`get_dre_cnf_val "selection_criteria"`
    


	
}

#converts fields from format "test_one_two" to "TestOneTwo"
#$1=field
function format_cfg()
{
    local word=""
    for i in `echo "$1" |tr "_" " "`; do word="${word}${i^}" ; done
    
    echo "$word"

}

#function to update parsed sigtran values in /etc/iwf.cfg
function update_sigtrancfg_in_iwfcfg()
{
    set_dre_cfg "`format_cfg "point_code"`" "$point_code"
    set_dre_cfg "`format_cfg "ssn"`" "$ssn"
    set_dre_cfg "`format_cfg "tcap_invoke_timer"`"  "$tcap_invoke_timer"
    set_dre_cfg "`format_cfg "routing_indicator"`"  "$routing_indicator"
    set_dre_cfg "`format_cfg "self_sccp_addr_use_from_config"`"  "$self_sccp_addr_use_from_config"
    set_dre_cfg "`format_cfg "use_sccp_cdpa_from_incomming_msg"`"  "$use_sccp_cdpa_from_incomming_msg"
    set_dre_cfg "`format_cfg "has_ssn"`"  "$has_ssn"
    set_dre_cfg "`format_cfg "has_pc"`"  "$has_pc"
    set_dre_cfg "`format_cfg "selectionCriteria"`" "$selection_criteria"
    set_dre_cfg "`format_cfg "global_title_indicator"`" "$global_title_indicator"
    case $global_title_indicator in
        1) 
	   set_dre_cfg "`format_cfg "nature_of_address_indicator"`" "$nature_of_address_indicator"
	   set_dre_cfg "`format_cfg "global_title_address_information"`" "$global_title_address_information"
	   ;;
	2) validate_filled "$gti_combi2"

	   set_dre_cfg "`format_cfg "translation_type"`" "$translation_type"
	   set_dre_cfg "`format_cfg "global_title_address_information"`" "$global_title_address_information"
		;;
	3) validate_filled "$gti_combi3"

	   set_dre_cfg "`format_cfg "translation_type"`" "$translation_type"
	   set_dre_cfg "`format_cfg "numbering_plan"`" "$numbering_plan"
	   set_dre_cfg "`format_cfg "encoding_scheme"`" "$encoding_scheme"
	   set_dre_cfg "`format_cfg "global_title_address_information"`" "$global_title_address_information"
		;;
	4)validate_filled "$gti_combi4"

	   set_dre_cfg "`format_cfg "translation_type"`" "$translation_type"
	   set_dre_cfg "`format_cfg "numbering_plan"`" "$numbering_plan"
	   set_dre_cfg "`format_cfg "encoding_scheme"`" "$encoding_scheme"
	   set_dre_cfg "`format_cfg "global_title_address_information"`" "$global_title_address_information"
	   set_dre_cfg "`format_cfg "nature_of_address_indicator"`" "$nature_of_address_indicator"
		;;
    esac


}

function validate_ssn()
{
    local RET=0
    local ssn=`echo "$1" |tr '[:upper:]' '[:lower:]'`
    if [ "$ssn" == "hlr" ] || [ "$ssn" == "sgsn" ] || [ "$ssn" == "cap" ];then
	RET=0
    else
	RET=1
	PLOG_ERROR "Invalid ssn value $ssn in config file!" $LINENO
	PLOG_INFO "Possible Values HLR, SGSN, CAP" $LINENO
    fi


    return $RET 
}

#function to validate if possible values are present
#1= field name, $2 arguments are the possible values
#always pass upper case arguments in the possible values list
function validate_possible_values()
{
    local RET=1
    local passed_val=`get_dre_cnf_val "$1"`
    local possible_vals=`echo $2|tr '[:lower:]' '[:upper:]'`
    local val=`echo "$passed_val" |tr '[:lower:]' '[:upper:]'`
    #check 
    for i in $possible_vals
    do
	if [ "$i" == "$val" ];then
	    RET=0
	    break
	fi
    done

    if [ $RET -eq 1 ];then
	local possible_value_list=`echo "$possible_vals"| tr ' ' '/'`
	PLOG_ERROR "Invalid Value \"$passed_val\" for \"$1\" field" $LINENO
	PLOG_ERROR "Possible values are \"$possible_value_list\"" $LINENO
    fi
    return $RET

}

function validate_gti()
{
    local RET=0 
    local gti_combi1="nature_of_address_indicator global_title_address_information"
    local gti_combi2="translation_type global_title_address_information"
    local gti_combi3="translation_type numbering_plan encoding_scheme global_title_address_information"
    local gti_combi4="translation_type numbering_plan encoding_scheme nature_of_address_indicator global_title_address_information"

    




    validate_filled "global_title_indicator"
    if [ $? -ne 0 ];then
	PLOG_ERROR "Configure proper values for Sigtran section!" $LINENO
	return 1
    fi   

    validate_range "global_title_indicator" 1 4
    if [ $? -ne 0 ];then
	return 1
    fi

    case $global_title_indicator in
        1) validate_filled "$gti_combi1"
	   if [ $? -ne 0 ];then
		PLOG_ERROR "Configure proper values for Sigtran section" $LINENO
		RET=1
	   else
		validate_range "nature_of_address_indicator" 0 4
		if [ $? -ne 0 ];then
		    RET=1
		fi

		validate_range "global_title_address_information" 0 99999999999
		if [ $? -ne 0 ];then
		    RET=1
		fi
		

	    fi
		;;
	2) validate_filled "$gti_combi2"
	   if [ $? -ne 0 ];then
		PLOG_ERROR "Configure proper values for Sigtran section" $LINENO
		RET=1
	   else
		validate_range "translation_type" 0 255
		if [ $? -ne 0 ];then
		    RET=1
		fi

	   fi

		;;
	3) validate_filled "$gti_combi3"
	   if [ $? -ne 0 ];then
		PLOG_ERROR "Configure proper values for Sigtran section" $LINENO
		RET=1
	   else
		validate_range "translation_type" 0 255
		if [ $? -ne 0 ];then
		    RET=1
		fi
		validate_range "numbering_plan" 0 15
		if [ $? -ne 0 ];then
		    RET=1
		fi
		validate_range "encoding_scheme" 0 15
		if [ $? -ne 0 ];then
		    RET=1
		fi
		

	   fi


		;;
	4)validate_filled "$gti_combi4"
	    if [ $? -ne 0 ];then
		PLOG_ERROR "Configure proper values for Sigtran section" $LINENO
		RET=1
	    else
		validate_range "translation_type" 0 255
		if [ $? -ne 0 ];then
		    RET=1
		fi
		validate_range "numbering_plan" 0 15
		if [ $? -ne 0 ];then
		    RET=1
		fi
		validate_range "encoding_scheme" 0 15
		if [ $? -ne 0 ];then
		    RET=1
		fi
		validate_range "nature_of_address_indicator" 0 127
		if [ $? -ne 0 ];then
		    RET=1
		fi


	    fi


		;;
    esac
	


    return $RET
}

#$1=configFieldName $2=start $3=end
function validate_range()
{
    local RET=0
    local val=`get_dre_cnf_val "$1"`
    LOG_DEBUG "Validating Range for $1: < $2 - $3 >" $LINENO

    if [[ $val = *[[:digit:]]* ]];then
	LOG_DEBUG "$val is Number" $LINENO
	if [ $val -lt $2 ] || [ $val -gt $3 ];then
	    RET=1
	    PLOG_ERROR "Invalid Value \"$val\" for field \"$1\" : valid Range: < $2 - $3 >" $LINENO
        fi
    else
	RET=1
	PLOG_ERROR "Invalid Value \"$val\" for field \"$1\": valid Range: < $2 - $3 >" $LINENO
    fi

   
    return $RET

}

function validate_sigtran_config()
{
    local RET=0
    
    #list of sigtran config except gti related/dependent , gti related will be
    #validated in validate_gti function 
    sigtran_cfg_list="point_code ssn tcap_invoke_timer global_title_indicator routing_indicator selection_criteria"

    #validate point code
    validate_filled "$sigtran_cfg_list"
    if [ $? -ne 0 ];then
	PLOG_ERROR "Configure proper values for Sigtran section!" $LINENO
	#return 1
    fi


    #validate gti and related configurations
    validate_gti
    if [ $? -ne 0 ];then
	return 1
    fi

    

   
    validate_possible_values "ssn" "HLR SGSN CAP"
    if [ $? -ne 0 ];then
	return 1
    fi


    #validate tcap_invoke_timer
    validate_range "tcap_invoke_timer" 1 65535
    if [ $? -ne 0 ];then
	return 1
    fi

    validate_possible_values "routing_indicator" "SSN GT"
    if [ $? -ne 0 ];then
	return 1
    fi
    
    validate_possible_values "selection_criteria" "1 4 5 8 9 16 17 24"
    if [ $? -ne 0 ];then
        return 1
    fi
    
    #validate_possible_values "self_sccp_addr_use_from_config" "yes no"
    #if [ $? -ne 0 ];then
#	return 1
#    fi

#    validate_possible_values "use_sccp_cdpa_from_incomming_msg" "yes no"
#    if [ $? -ne 0 ];then
#	return 1
#    fi

#    validate_possible_values "has_ssn" "yes no"
#    if [ $? -ne 0 ];then
#	return 1
#    fi

#    validate_possible_values "has_pc" "yes no"
#    if [ $? -ne 0 ];then
#	return 1
#    fi

    return $RET
}


function parse_install_mode()
{
    #get all the config values from the ${S_PRODUCT_NAME}.cnf 
    dre_install_mode=`get_dre_cnf_val "install_mode"`

}

function parse_mysql_cnf()
{
    #Mysql configuration
    mysql_username="root"
    mysql_root_password=`get_dre_cnf_val "mysql_root_password"`

}

function parse_tipc_cnf()
{
    net_id=`get_dre_cnf_val "net_id"`
    tipc_node_address=`get_dre_cnf_val "tipc_node_address"`
    bearer_name=`get_dre_cnf_val "bearer_name"`

}

function parse_alarm_cnf()
{
    trap_sink_ip=( `grep "^trap_sink_ip" "$1" |cut -d"=" -f2 |tr "\n" " "` )
    
    for ip in "${trap_sink_ip[@]}"
    do
        LOG_DEBUG "$ip " $LINENO
    done

}


function parse_ntp_cnf()
{
    ntp_server_ip=`get_dre_cnf_val "ntp_server_ip"`
}

function parse_mysql_heartbeat_cnf()
{
    #mysql heartbeat related
    mysql_local_ip=`get_dre_cnf_val "mysql_local_ip"`
    mysql_mate_ip=`get_dre_cnf_val "mysql_mate_ip"`
    #mysql_mate_hostname=`get_dre_cnf_val "mysql_mate_hostname"`
    #ha_mode=`get_dre_cnf_val "ha_mode"`
    mysql_virtual_ip=`get_dre_cnf_val "mysql_virtual_ip"`
    mysql_interface_name=`get_dre_cnf_val "mysql_interface_name"`

}

function parse_localhost_cnf()
{
    #Localhost configurations
    host_name=`get_dre_cnf_val "host_name"`
    realm_name=`get_dre_cnf_val "realm_name"`
    ip_address=`get_dre_cnf_val "ip_address"`
    public_ip_address=`get_dre_cnf_val "public_ip_address"`
    port=`get_dre_cnf_val "port"`
    transport_type=`get_dre_cnf_val "transport_type"`
    port2=`get_dre_cnf_val "port2"`
    transport_type2=`get_dre_cnf_val "transport_type2"`
    secure_port=`get_dre_cnf_val "secure_port"`
    transport_type3=`get_dre_cnf_val "transport_type3"`

}

#this function is used to parse all the config parameters from the dre_config 
#file which is passed as an argument to the PRODUCT installer
#$1 will be the file path passed $2 indicates whether it is an upgrade(to parse only while upgrade from standalone to active-standby)
#if $2 value passed is --upgrade then check if its active-standby install mode, if yes parse only what is required for active standby mode
function parse_user_dre_cnf_file()
{

    if [ $# -lt 1 ] || [ $# -gt 2 ];then
        LOG_ERROR "file shoud be passed as argument/Invalid Arguments" $LINENO
        exit 1
    else
        if [ ! -e "$1" ];then
            PLOG_ERROR "Invalid file: $1" $LINENO
            exit 1
        fi
            
    fi

    LOG_DEBUG "CNF File passed: `cat $1`" $LINENO 
    
    DRE_CNF_FILE="$1"
    parse_install_mode 
  
    #if $2 == --upgrade ,only allow standalone DRE(version X) --> active standby DRE(version X+1) upgradation
    if [ $# -gt 1 ] && [ "$2" == "--upgrade" ];then
	if [  "`GetDreInstallMode`" == "1" ] && [ "$dre_install_mode" == "2" ];then
	    LOG_DEBUG "User trying to upgrade from standalone ${PRODUCT_NAME} to Active-standby ${PRODUCT_NAME} by passing configFile" $LINENO
	    STANDALONE_TO_ACTIVESTANDBY="yes"
	    PLOG_ERROR "Version Upgrade from standalone to active-standby not supported" $LINENO
	    PLOG_INFO "Convert current standalone ${PRODUCT_NAME} to active-standby ${PRODUCT_NAME} by executing /opt/diametriq/${S_PRODUCT_NAME}/scripts/standalone_to_ha.sh" $LINENO
	    exit 1
	else
	    LOG_DEBUG "Unsupported scenario" $LINENO
	    LOG_DEBUG "Current Mode=`GetDreInstallMode`, Mode in conf file passed = $dre_install_mode" $LINENO
	    PLOG_ERROR "Upgrade using conf file supported only for Standalone to Active-standby ${PRODUCT_NAME} upgrade"
	    exit 1
	fi
    fi

    #parse all the bonding configuration from the user input file
    parse_bonding_from_user_cnf

    #parse the common parameters for standalone and active standby only incase of a fresh install scenario   
    if [ $# -eq 1 ];then
	parse_mysql_cnf

        parse_localhost_cnf
	if [ "$PRODUCT" == "iwf" ] ; then
	    LOG_DEBUG "Parsing sigtran" $LINENO
	    parse_sigtran_config $1
	fi


        #TIPC Configuration
	parse_tipc_cnf   

       	parse_alarm_cnf $1
    fi

    parse_ntp_cnf
    if [ "$dre_install_mode" == "2" ] || [ "$dre_install_mode" == "3" ] || [ "$dre_install_mode" == "4" ];then
        #parse only if dre_install_mode is 2
   
         parse_mysql_heartbeat_cnf	
    fi    

    #parse the couchbase configuration only if dre_install_mode == 4
    if [ "$dre_install_mode" == "4" ];then
        parse_couchbase_cfg_from_usr_cnf
    fi     
    
    #validate the values
    if [ "$2" == "--upgrade" ];then
        #validate only active standby related parameters
        validate_dre_cnf_inputs --upgrade 
	echo ""
    else
	validate_dre_cnf_inputs 
	echo ""
    fi

    #if all values are valid, store them in /etc/${S_PRODUCT_NAME}.cfg which will be used by the script
    #to read the inputs
    if [ "$2" == "--upgrade" ];then
	#update only active standby related parameters
        update_dre_cfg --upgrade
    else
        update_dre_cfg
    fi

}


function GetPointCode()
{
    sed -n s/^PointCode=//p $DRE_CONFIG
}

function GetNI()
{
    sed -n s/^NI=//p $DRE_CONFIG
}

function GetSSN()
{
    sed -n s/^Ssn=//p $DRE_CONFIG
}

function GetTcapInvokeTimer()
{
    sed -n s/^TcapInvokeTimer=//p $DRE_CONFIG
}


function GetMysqlUsername()
{
    sed -n s/^MysqlUsername=//p $DRE_CONFIG
}

function GetMysqlPassword()
{
    sed -n s/^MysqlPassword=//p $DRE_CONFIG
}

function GetMysqlIpAddress()
{
    sed -n s/^MysqlIpAddress=//p $DRE_CONFIG
}

function GetMysqlPort()
{
    sed -n s/^MysqlPort=//p $DRE_CONFIG
}

function GetLocalHostName()
{
    sed -n s/^LocalHostName=//p $DRE_CONFIG
}

function GetLocalRealmName()
{
    sed -n s/^LocalRealmName=//p $DRE_CONFIG
}

function GetLocalIpAddress()
{
    sed -n s/^LocalIpAddress=//p $DRE_CONFIG
}

function GetPublicIpAddress()
{
    sed -n s/^PublicIpAddress=//p $DRE_CONFIG
}

function GetLocalPort()
{
    sed -n s/^LocalPort=//p $DRE_CONFIG
}

function GetLocalTransportType()
{
    sed -n s/^LocalTransportType=//p $DRE_CONFIG
}
function GetDreInstallMode()
{
    sed -n s/^DreInstallMode=//p $DRE_CONFIG
}


function GetMysqlLocalIP()
{
    sed -n s/^MysqlLocalIP=//p $DRE_CONFIG
}

function GetMysqlMateIP()
{
    sed -n s/^MysqlMateIP=//p $DRE_CONFIG
}

function GetMysqlLocalHostname()
{
    sed -n s/^MysqlLocalHostname=//p $DRE_CONFIG
}

function GetMysqlMateHostname()
{
    sed -n s/^MysqlMateHostname=//p $DRE_CONFIG
}

function GetHAMode()
{
    sed -n s/^HAMode=//p $DRE_CONFIG
}

function GetVirtualIP()
{
    sed -n s/^VirtualIP=//p $DRE_CONFIG
}

function GetEthernet()
{
    sed -n s/^Ethernet=//p $DRE_CONFIG
}


function GetBroadcastAddress()
{
    sed -n s/^BroadcastAddress=//p $DRE_CONFIG
}

function GetSubNetMaskPrefixLen()
{
    sed -n s/^SubNetMaskPrefixLen=//p $DRE_CONFIG
}

function GetAutoFailback()
{
    sed -n s/^AutoFailback=//p $DRE_CONFIG
}

function GetDreInstallMode()
{
    sed -n s/^DreInstallMode=//p $DRE_CONFIG
}

#$1=field name
function GetDreConfigValue()
{
    sed -n s/^$1=//p $DRE_CONFIG
}

#get the tipc config parameters from the PRODUCT config file
function GetNetID()
{
    sed -n s/^NetID=//p $DRE_CONFIG
}

function GetTipcNodeAddress()
{
    sed -n s/^TipcNodeAddress=//p $DRE_CONFIG
}

function GetTrapSinkIP()
{
    sed -n s/^TrapSinkIP=//p $DRE_CONFIG
}


function GetBearerName()
{
    sed -n s/^BearerName=//p $DRE_CONFIG
}

function GetNtpServerIP()
{
    sed -n s/^NtpServerIP=//p $DRE_CONFIG
}

function GetRemoteNodeUsername()
{
    sed -n s/^RemoteNodeUsername=//p $DRE_CONFIG
}

function GetRemoteNodeIP()
{
    sed -n s/^RemoteNodeIP=//p $DRE_CONFIG
}

function GetRemoteNodePassword()
{
    sed -n s/^RemoteNodePassword=//p $DRE_CONFIG
}


function check_apache_tomcat()
{
    echo -n "checking for apache-tomcat "
    local count=0
    local flag=0
    while [ 1 ];do
	    sleep 1
        if [ $count -eq 15 ];then
            flag=1
            break;
        fi
        netstat -nap | grep "8080" | grep "LISTEN" > /dev/null
	    if [ $? -eq 0 ]; then
	        echo "."
	        PLOG_INFO "Apache-tomcat started Listening" $LINENO
	        return 0
	    fi
	    echo -n "."
        ((count++))
    done

    if [ $flag -eq 1 ];then
        return 1
    fi
}

function check_mysql()
{
    echo -n "checking for mysql "
    while [ 1 ];do
	sleep 1
        netstat -nap | grep mysql | grep "LISTEN" > /dev/null
	if [ $? -eq 0 ]; then
	    echo "."
	    echo "Mysql started Listening"
	    return 0
	fi
	echo -n "."
    done
}

function check_and_start_3rdparty_proccesses()
{
    #snmpd
    pgrep snmpd >/dev/null
    if [ $? -ne 0 ];then
	LOG_DEBUG "snmpd not running.starting it..." $LINENO
	start snmpd
    fi
    #memcached
    ps -eaf|grep "memcached -p 50000" |grep -v "grep"  >/dev/null
    if [ $? -ne 0 ];then
	LOG_DEBUG "memcached not running.starting it..." $LINENO
	start memcached
    fi
    #apache-tomcat
    ps -eaf|grep apache-tomcat|grep -v "grep" >/dev/null
    if [ $? -ne 0 ];then
	LOG_DEBUG "apache-tomcat not running.starting it..." $LINENO
        start_apache_tomcat
    fi 
    #mysql
    check_and_start_mysql
    #crontab
    pgrep crond >/dev/null
    if [ $? -ne 0 ];then
	LOG_DEBUG "crond not running.starting it..." $LINENO
	service crond start
    fi 
    #ntp
    pgrep ntpd > /dev/null
    if [ $? -ne 0 ];then
	LOG_DEBUG "ntpd not running.starting it..." $LINENO
	service ntpd start
    fi 
    #heartbeat
    if [ "`GetDreInstallMode`" == "2" ] || [ "`GetDreInstallMode`" == "3" ] || [ "`GetDreInstallMode`" == "4" ];then
	#ps -elf | grep heartbeat | grep -v grep | grep master  >/dev/null
	#if [ $? -ne 0 ];then
	#LOG_DEBUG "heartbeat not running.starting it..." $LINENO
	#   service heartbeat start
	#fi
	check_and_start_heartbeat
    fi

    pgrep incrond >/dev/null
    if [ $? -ne 0 ];then
	start incrond
    fi 

}

function check_and_start_mysql()
{
    LOG_DEBUG "pgrep mysqld = `pgrep mysqld`" $LINENO
    pgrep mysqld >/dev/null 
    if [ $? -ne 0 ];then
        PLOG_INFO "starting mysql..." $LINENO
        if [ -e /etc/init/mysqld.conf ];then
            start mysqld
        else
            service mysql start
        fi
        check_mysql
        LOG_DEBUG "pgrep mysqld = `pgrep mysqld`" $LINENO
        pgrep mysqld >/dev/null
        if [ $? -eq 0 ];then
            PLOG_INFO "Myql up and running..." $LINENO
	    check_mysql
        else
            PLOG_ERROR " Could not start mysql" $LINENO
            exit 1
        fi
    fi
}

function check_and_restart_heartbeat()
{
	check_and_stop_heartbeat
	check_and_start_heartbeat	
}

function check_and_stop_heartbeat()
{
    local process_pid=`ps -elf | grep heartbeat | grep -v grep | grep master | awk '{print $4}'`
    LOG_DEBUG "Heartbeat pid :- $process_pid " $LINENO
    if [ -n "$process_pid" ];then
	LOG_DEBUG "Stopping heartbeat in check_and_stop_heartbeat function" $LINENO
	kill_heartbeat &
        service heartbeat stop
    fi

}

function check_and_start_heartbeat()
{
    local process_pid=`ps -elf | grep heartbeat | grep -v grep | grep master | awk '{print $4}'`
    LOG_DEBUG "Heartbeat pid :- $process_pid " $LINENO
    if [ -z "$process_pid" ];then
    	if [ "`GetDreInstallMode`" == "2" ] || [ "`GetDreInstallMode`" == "3" ] || [ "`GetDreInstallMode`" == "4" ];then
	   LOG_DEBUG "Starting heartbeat in check_and_start_heartbeat function" $LINENO
           service heartbeat start
        fi
    fi

}

function check_and_stop_mysql()
{
    pgrep mysqld >/dev/null 
    if [ $? -eq 0 ];then
    
        PLOG_INFO "Stopping mysql..." $LINENO
        stop mysqld
        LOG_DEBUG "pgrep mysqld = `pgrep mysqld`" $LINENO
        pgrep mysqld >/dev/null
        if [ $? -eq 0 ];then
	        PLOG_WARNING "Mysql not stopped !" $LINENO
	        pkill -9 mysqld
	        PLOG_INFO  "killing mysql..." $LINENO
        fi
    fi

}


function num_check()
{
	default=$3
	read -e -i "$default" -p "$1" as
	actualvalue=${as:-$default}

	until expr $as - 1 >>/dev/null 2>/dev/null 
	do
		read -e -i "$default" -p "$2" as
		actualvalue=${as:-$default}
		
	done
	echo $actualvalue
}
#$1=Message $2=error message $3=start number $4 end number
function spl_num_check()
{
    local i=0
    local default=$5
    local flag=0
    while [ 1 ]
    do
        if [ $i -eq 0 ];then
            read -e -i "$default" -p "$1" ch
        else
            read -e -i "$default" -p "$2" ch
        fi
       
	actualvalue=${ch:-$default}
         
        #until expr $actualvalue - 1 >>/dev/null 2>/dev/null
        #do
        #    LOG_WARNING "wrong choice $actualvalue" $LINENO
        #    flag=1
        #    break
        #done
        #if [ $flag -eq 1 ];then
        #    flag=0
        #    continue
        #fi
        if [[ $actualvalue -ge $3 && $actualvalue -le $4 ]] ; then
            echo "$actualvalue"
            return
        else
            LOG_WARNING "wrong choice $actualvalue" $LINENO
        fi
        i=$(($i+1))
    done

}

function tcp_sctp_check()
{
	default=$3
	read -e -i "$default" -p "$1" as
	actualvalue=${as:-$default}

	if [ "$as" = "TCP" ]
	then
        	as=1	
	else
        	if [ "$as" = "SCTP" ]
        	then
			as=2	
        	else
			as=""	
		fi
	fi

	while [ -z $as ]
	do
		read -e -i "$default" -p "$2" as
		actualvalue=${as:-$default}

		if [ "$as" = "TCP" ]
		then
			as=1	
		else
     		 	if [ "$as" = "SCTP" ]
       		 	then
				as=2	
        		else
				as=""	
			fi
		fi

	done
	echo $as
}

function install_mode_check()
{
	default=$3
	read -e -i "$default" -p "$1" ch
	actualvalue=${ch:-$default}

	while [ "$ch" != "1" ] &&  [ "$ch" != "2" ] || [ -z "$ch" ]
	do
		read -e -i "$default" -p "$2" ch
		actualvalue=${ch:-$default}
	done    

	echo $actualvalue  
}

function char_check()
{
	default=$3	
	read -e -i "$default" -p "$1" as
	actualvalue=${as:-$default}
	
	while expr $as - 1 >>/dev/null 2>/dev/null 
	do
		read -e -i $default -p "$2" as
		actualvalue=${as:-$default}
	done
	echo $actualvalue
}


function null_check()
{
	default=$3
	read -e -i "$default" -p "$1" as
	actualvalue=${as:-$default}

	while [ -z $as ]
	do
		read -e -i "$default" -p "$2" as
		actualvalue=${as:-$default}

	done
	echo $actualvalue
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


function alphacheck()
{
	default=$3	
	read -e -i "$default" -p "$1" as
	actualvalue=${as:-$default}

	while echo $as | grep [0-9\!\@\#$\%\^\&\*\(\)\-\_\|] 2>>/dev/null >>/dev/null
	do
		read -e -i "$default" -p "$2" as
		actualvalue=${as:-$default}
	done
	echo $actualvalue
}

function package_log()
{
    if [ ! -d "/var/log/${S_PRODUCT_NAME}" ];then
        mkdir -p /var/log/${S_PRODUCT_NAME} > /dev/null
    fi
    PACKAGE_LOG="/var/log/${S_PRODUCT_NAME}/package.log"
    CRITICAL_PACKAGE_LOG="/var/log/${S_PRODUCT_NAME}/package_critical.log"
    
    if [ $# -eq 0 ];then
        echo "" >> $PACKAGE_LOG
	echo "" >> $CRITICAL_PACKAGE_LOG
    elif [ $# -eq 4  ];then
        # $1 = LogLevel $2 = Message to be printed 
        # $3 = 1 for file only , 2 for console only , 3 for both file and console.
        # $4 : Is the line number passed
        case $1 in
             1) case $3 in
                   1) echo "[`date`] Alert | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "[`date`] Alert | $0:$4 | $2" >> $CRITICAL_PACKAGE_LOG
		      ;;
                   2) echo -e "${bldred}ALERT | $2${txtrst}"
                      ;;
                   3) echo "[`date`] Alert | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "[`date`] Alert | $0:$4 | $2" >> $CRITICAL_PACKAGE_LOG
		      echo -e "${bldred}ALERT | $2${txtrst}"
                      ;;
                   *) echo "[`date`] Alert | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "[`date`] Alert | $0:$4 | $2" >> $CRITICAL_PACKAGE_LOG
	 	      echo -e "${bldred}ALERT | $2${txtrst}"
                      ;;   
                esac   
               ;;
            2) case $3 in
                   1) echo "[`date`] Critical | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "[`date`] Critical | $0:$4 | $2" >> $CRITICAL_PACKAGE_LOG

		      ;;
                   2) echo -e "${bldred}CRITICAL | $2 ${txtrst}"
                      ;;
                   3) echo "[`date`] Critical | $0:$4 | $2" >> $PACKAGE_LOG
                      echo -e "${bldred}CRITICAL | $2 ${txtrst}"
		      echo "[`date`] Critical | $0:$4 | $2" >> $CRITICAL_PACKAGE_LOG

                      ;;
                   *) echo "[`date`] Critical | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "[`date`] Critical | $0:$4 | $2" >> $CRITICAL_PACKAGE_LOG
		      echo -e "${bldred}CRITICAL | $2 ${txtrst}"
                      ;; 
                esac 
               ;;
            3) case $3 in
                   1) echo "[`date`] Error | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "[`date`] Error | $0:$4 | $2" >> $CRITICAL_PACKAGE_LOG
	               ;;
                   2) echo -e "${bldred}ERROR | $2 ${txtrst}"
                      ;;
                   3) echo "[`date`] Error | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "[`date`] Error | $0:$4 | $2" >> $CRITICAL_PACKAGE_LOG
		      echo -e "${bldred}ERROR | $2 ${txtrst}"
                      ;;
                   *) echo "[`date`] Error | $0:$4 | $2" >> $PACKAGE_LOG
                      echo "[`date`] Error | $0:$4 | $2" >> $CRITICAL_PACKAGE_LOG
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



function begin_install
{
    clear_package_log
    if [ ! -d "/var/log/${S_PRODUCT_NAME}" ];then
        mkdir -p /var/log/${S_PRODUCT_NAME} > /dev/null
    fi  
    PACKAGE_LOG="/var/log/${S_PRODUCT_NAME}/package.log"
    package_critical_heading "INSTALLATION" 
    echo "-----------------------------------------------------------------------------------------" >> $PACKAGE_LOG
    echo "                                INSTALL INFO" >> $PACKAGE_LOG
    if [ $PRODUCT = "dre" ];then
        echo "      Version            :    $CUR_DRE_VER" >> $PACKAGE_LOG
    fi

    if [ $PRODUCT = "iwf" ];then
        echo "      Version            :    $CUR_IWF_VER" >> $PACKAGE_LOG
    fi
    echo "      Date of Install    :    `date`" >> $PACKAGE_LOG
    echo "-----------------------------------------------------------------------------------------" >> $PACKAGE_LOG
    echo "--------------------------------" >> $PACKAGE_LOG
    echo "Versions installed in the system" >> $PACKAGE_LOG
    echo "--------------------------------" >> $PACKAGE_LOG
    echo "`rpm -q ${S_PRODUCT_NAME}`" >> $PACKAGE_LOG
    echo "" >> $PACKAGE_LOG

    echo "------------------------------" >> $PACKAGE_LOG
    echo "Directories in /opt/diametriq/" >> $PACKAGE_LOG
    echo "------------------------------" >> $PACKAGE_LOG
    if [ -d /opt/diametriq/ ];then
    echo "`ls -lrt /opt/diametriq`" >> $PACKAGE_LOG
    fi
    if [ -d /etc/.${S_PRODUCT_NAME} ];then
    echo "-------------------" >> $PACKAGE_LOG
    echo "PACKAGE FILES STATE" >> $PACKAGE_LOG
    echo "-------------------" >> $PACKAGE_LOG

    if [ -e /etc/.${S_PRODUCT_NAME}/db_upgrade_info ];then
    echo "-------------------------" >> $PACKAGE_LOG
    echo "/etc/.${S_PRODUCT_NAME}/db_upgrade_info" >> $PACKAGE_LOG
    echo "-------------------------" >> $PACKAGE_LOG
    echo "`cat /etc/.${S_PRODUCT_NAME}/db_upgrade_info`" >> $PACKAGE_LOG
    else
    echo "/etc/.${S_PRODUCT_NAME}/db_upgrade_info does not exist!"
    fi

    if [ -e /etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_install_info ];then
    echo "--------------------------" >> $PACKAGE_LOG
    echo "/etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_install_info" >> $PACKAGE_LOG
    echo "--------------------------" >> $PACKAGE_LOG
    echo "`cat /etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_install_info`" >> $PACKAGE_LOG
    else
    echo "/etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_install_info does not exist!"
    fi

    if [ -e /etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_uninstall_info ];then
    echo "----------------------------" >> $PACKAGE_LOG
    echo "/etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_uninstall_info" >> $PACKAGE_LOG
    echo "----------------------------" >> $PACKAGE_LOG
    echo "`cat /etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_uninstall_info`" >> $PACKAGE_LOG
    else
    echo "/etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_uninstall_info does not exist!"
    fi

    fi
    echo "-----------------------------------------------------------------------------------------" >> $PACKAGE_LOG

    

}

function begin_uninstall
{
    clear_package_log
    clear_package_log
    if [ ! -d "/var/log/${S_PRODUCT_NAME}" ];then
        mkdir -p /var/log/${S_PRODUCT_NAME} > /dev/null
    fi                
    PACKAGE_LOG="/var/log/${S_PRODUCT_NAME}/package.log"
    package_critical_heading "UNINSTALL" $LINENO
    echo "-----------------------------------------------------------------------------------------" >> $PACKAGE_LOG
    echo "                                UNINSTALL INFO" >> $PACKAGE_LOG
    if [ $PRODUCT = "dre" ];then
        echo "      Version            :    $CUR_DRE_VER" >> $PACKAGE_LOG
    fi

    if [ $PRODUCT = "iwf" ];then
        echo "      Version            :    $CUR_IWF_VER" >> $PACKAGE_LOG
    fi

    echo "      Date of uninstall    :    `date`" >> $PACKAGE_LOG
    echo "-----------------------------------------------------------------------------------------" >> $PACKAGE_LOG
    echo "--------------------------------" >> $PACKAGE_LOG
    echo "Versions installed in the system" >> $PACKAGE_LOG
    echo "--------------------------------" >> $PACKAGE_LOG
    echo "`rpm -q ${S_PRODUCT_NAME}`" >> $PACKAGE_LOG
    echo "" >> $PACKAGE_LOG

    echo "------------------------------" >> $PACKAGE_LOG
    echo "Directories in /opt/diametriq/" >> $PACKAGE_LOG
    echo "------------------------------" >> $PACKAGE_LOG
    if [ -d /opt/diametriq/ ];then
    echo "`ls -lrt /opt/diametriq`" >> $PACKAGE_LOG
    fi
    if [ -d /etc/.${S_PRODUCT_NAME} ];then
    echo "-------------------" >> $PACKAGE_LOG
    echo "PACKAGE FILES STATE" >> $PACKAGE_LOG
    echo "-------------------" >> $PACKAGE_LOG

    if [ -e /etc/.${S_PRODUCT_NAME}/db_upgrade_info ];then
    echo "-------------------------" >> $PACKAGE_LOG
    echo "/etc/.${S_PRODUCT_NAME}/db_upgrade_info" >> $PACKAGE_LOG
    echo "-------------------------" >> $PACKAGE_LOG
    echo "`cat /etc/.${S_PRODUCT_NAME}/db_upgrade_info`" >> $PACKAGE_LOG
    else
    echo "/etc/.${S_PRODUCT_NAME}/db_upgrade_info does not exist!"
    fi

    if [ -e /etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_install_info ];then
    echo "--------------------------" >> $PACKAGE_LOG
    echo "/etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_install_info" >> $PACKAGE_LOG
    echo "--------------------------" >> $PACKAGE_LOG
    echo "`cat /etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_install_info`" >> $PACKAGE_LOG
    else
    echo "/etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_install_info does not exist!"
    fi

    if [ -e /etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_uninstall_info ];then
    echo "----------------------------" >> $PACKAGE_LOG
    echo "/etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_uninstall_info" >> $PACKAGE_LOG
    echo "----------------------------" >> $PACKAGE_LOG
    echo "`cat /etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_uninstall_info`" >> $PACKAGE_LOG
    else
    echo "/etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_uninstall_info does not exist!"
    fi

    fi
    echo "-----------------------------------------------------------------------------------------" >> $PACKAGE_LOG


}

function is_dep_installed()
{
    rpm -qa|grep "^$1" >/dev/null
    if [ $? == 0 ];then
        echo "true"
    else
        echo "false"
    fi
}
function compare_passwords
{   n='
'
    first=$1
    second=$2
    while [ "$first" != "$second" ]
    do
        first=`silent_null_check $'\nPasswords do not match!\nEnter Password\t\t\t\t:' $'\nPassword (should not be null)\t\t:'`
        second=`silent_null_check $'\nConfirm Password\t\t\t:' $'\nConfirm Password (should not be null)\t:'`
    done
    echo "$first"

}

function enter_installation_mode
{
   n='
'
    
    if [ ! -z $DRE_CNF_FILE ];then
    #block handles the inputs passed using config file
        if [ ! -e $DRE_CONFIG ];then
            echo "DreInstallMode=$dre_install_mode" >> $DRE_CONFIG
        else
            if [ "`check_if_config_exist "DreInstallMode"`" == 1 ];then
                sed -i "s/DreInstallMode.*/DreInstallMode=$dre_install_mode/g" $DRE_CONFIG
            else
                echo "DreInstallMode=$dre_install_mode" >> $DRE_CONFIG
            fi
        fi
   
        return 0
    fi

    #if its previous version is standalone or cold-standby mode  then carry out the upgrade
    if [ "$1" == "--upgrade" ] && [ "`GetDreInstallMode`" == "3" ];then
	LOG_INFO "Upgrade from Cold-standby to Cold-standby" $LINENO
	PLOG_INFO "Upgrade from Cold-Standby to Cold-Standby" $LINENO
	return 0
    elif [ "$1" == "--upgrade" ] && [ "`GetDreInstallMode`" == "1" ];then
        LOG_INFO "Upgrade mode: standalone " $LINENO
        PLOG_INFO "Upgrade from Standalone to Standalone" $LINENO
	#PLOG_INFO "NOTE: To upgrade to Active-Standby ${PRODUCT_NAME} Version $CUR_DRE_VER follow below steps" $LINENO 
	#PLOG_INFO "1) Upgrade to Active-Standby ${PRODUCT_NAME} of current version using the standalone_to_ha.sh script(Abort current upgradation by entering \"no\"!" $LINENO
	#PLOG_INFO "2) Perform a standard upgrade procedure which will upgrade to Active-Standby ${PRODUCT_NAME} Version: $CUR_DRE_VER" $LINENO
        if [ $PRODUCT = "dre" ];then
	        PLOG_INFO "Upgrading to Standalone ${PRODUCT_NAME} Version $CUR_DRE_VER..." $LINENO
        fi

        if [ $PRODUCT = "iwf" ];then
	    PLOG_INFO "Upgrading to Standalone ${PRODUCT_NAME} Version $CUR_IWF_VER..." $LINENO
        fi

	#choice=`yes_no_check "Do you want to continue?[yes/no]:"`
	#if [ "$choice" == "no" ];then
	#    exit 0
	#else
	    return 0
        #fi

    fi

    LOG_DEBUG "Enter ${S_PRODUCT_NAME} installation mode" $LINENO
    echo -e "${bldblu}****************************************************${txtrst}"
    if [ "$1" == "--upgrade" ];then
    echo -e "${bldred}               ${PRODUCT_NAME} Upgrade Mode${txtrst}"
    else
    echo -e "${bldred}               ${PRODUCT_NAME} Installation Mode${txtrst}"
    fi
    echo -e "${bldblu}****************************************************${txtrst}"
    if [ "$1" == "--upgrade" ];then
    Dre_install_mode=`install_mode_check "${PRODUCT_NAME} Upgrade Modes:${n}1. Standalone mode${n}2. Active-Standby mode${n}Choose ${PRODUCT_NAME} Upgrade mode(enter number): " "Invalid Mode Chosen!${n}1 Standalone mode${n}2 Active-Standby mode${n}Choose a valid mode(enter number): "`
    else
    Dre_install_mode=`install_mode_check "${PRODUCT_NAME} Installation Modes:${n}1. Standalone mode${n}2. Active-Standby mode${n}Choose ${PRODUCT_NAME} installation mode(enter number): " "Invalid Mode Chosen!${n}1 Standalone mode${n}2 Active-Standby mode${n}Choose a valid mode(enter number): "`
    fi
    LOG_DEBUG "${PRODUCT_NAME} install mode selected = $Dre_install_mode" $LINENO

    if [ "$1" == "--upgrade" ];then
	LOG_DEBUG "upgrade flag passed enter ${S_PRODUCT_NAME} installmode" $LINENO
        LOG_DEBUG "Dre_install_mode in ${S_PRODUCT_NAME}.cfg = `GetDreInstallMode`, Dre_install_mode entered = $Dre_install_mode" $LINENO
	if [ "$Dre_install_mode" == "2" ];then
	    if [ "`GetDreInstallMode`" == "1" ];then
		LOG_INFO "User wants to upgrade from Standalone to Active-standby ${PRODUCT_NAME}" $LINENO
		STANDALONE_TO_ACTIVESTANDBY="yes"
		PLOG_ERROR "Version Upgrade from standalone to active-standby not supported" $LINENO
                PLOG_INFO "Convert current standalone ${PRODUCT_NAME} to active-standby ${PRODUCT_NAME} by executing /opt/diametriq/${S_PRODUCT_NAME}/scripts/standalone_to_ha.sh" $LINENO
	        exit 1	
	    fi
	fi
    fi
    
    if [ ! -e $DRE_CONFIG ];then
        echo "DreInstallMode=$Dre_install_mode" >> $DRE_CONFIG
    else
        if [ "`check_if_config_exist "DreInstallMode"`" == 1 ];then
            sed -i "s/DreInstallMode.*/DreInstallMode=$Dre_install_mode/g" $DRE_CONFIG
        else
            echo "DreInstallMode=$Dre_install_mode" >> $DRE_CONFIG
        fi
    fi

    

}

function configure_dre()
{
    
    LOG_INFO "configuring ethernet bonding" $LINENO
    configure_ethernet_bonding 
    enter_ha_configuration
    configure_mysql
    configure_localhost
    configure_tipc
    if [ $PRODUCT = "iwf" ];then
        configure_sigtran
    fi
    #configure_alarms
    #enter_configuration

    LOG_DEBUG "${S_PRODUCT_NAME}.cfg = `cat /etc/${S_PRODUCT_NAME}.cfg`" $LINENO
}

function enter_ha_configuration()
{   n='
'
    
    if [ "`GetDreInstallMode`" == "2" ] || [ "`GetDreInstallMode`" == "3" ] || [ "`GetDreInstallMode`" == "4" ];then
        LOG_DEBUG "enter_ha_configuration" $LINENO
        #if install mode is Active-standby
 	    #configure Mysql heartbeat
	    LOG_INFO "configuring mysql heartbeat" $LINENO
	    configure_heartbeat 
        #LOG_INFO "configuring NTP" $LINENO
        #configure_NTP
    fi
    LOG_INFO "configuring NTP" $LINENO
#configure_NTP
}

function configuration_heading()
{
    echo -e "${bldblu}****************************************************************${txtrst}"
    echo -e "${bldred}            $1 Configuration ${txtrst}"
    echo -e "${bldblu}****************************************************************${txtrst}"
}

function heading()
{
    echo -e "${bldblu}****************************************************************${txtrst}"
    echo -e "${bldred}                      $1  ${txtrst}"
    echo -e "${bldblu}****************************************************************${txtrst}"
}

function package_critical_heading()
{
    if [ ! -d "/var/log/${S_PRODUCT_NAME}" ];then
        mkdir -p /var/log/${S_PRODUCT_NAME} > /dev/null
    fi                
    CRITICAL_PACKAGE_LOG="/var/log/${S_PRODUCT_NAME}/package_critical.log"

    echo "-----------------------------------------------------------------------------------------" >> $CRITICAL_PACKAGE_LOG
    echo "                                $1  " >> $CRITICAL_PACKAGE_LOG
    if [ $PRODUCT = "dre" ];then
        echo "      Version              :    $CUR_DRE_VER" >> $CRITICAL_PACKAGE_LOG
    fi

    if [ $PRODUCT = "iwf" ];then
        echo "      Version              :    $CUR_IWF_VER" >> $CRITICAL_PACKAGE_LOG
    fi


    echo "      Date                 :    `date`" >> $CRITICAL_PACKAGE_LOG
    echo "-----------------------------------------------------------------------------------------" >> $CRITICAL_PACKAGE_LOG


}

#a common banner heading which scripts can use to print initial infomration/heading
function log_heading()
{
   
    clear_package_log
    clear_package_log
    if [ ! -d "/var/log/${S_PRODUCT_NAME}" ];then
        mkdir -p /var/log/${S_PRODUCT_NAME} > /dev/null
    fi                
    PACKAGE_LOG="/var/log/${S_PRODUCT_NAME}/package.log"
    package_critical_heading "$1"
    echo "-----------------------------------------------------------------------------------------" >> $PACKAGE_LOG
    echo "                                $1  " >> $PACKAGE_LOG
    if [ $PRODUCT = "dre" ];then
        echo "      Version              :    $CUR_DRE_VER" >> $PACKAGE_LOG
    fi

    if [ $PRODUCT = "iwf" ];then
        echo "      Version              :    $CUR_IWF_VER" >> $PACKAGE_LOG
    fi


    echo "      Date                 :    `date`" >> $PACKAGE_LOG
    echo "-----------------------------------------------------------------------------------------" >> $PACKAGE_LOG
    echo "--------------------------------" >> $PACKAGE_LOG
    echo "Versions installed in the system" >> $PACKAGE_LOG
    echo "--------------------------------" >> $PACKAGE_LOG
    echo "`rpm -q ${S_PRODUCT_NAME}`" >> $PACKAGE_LOG
    echo "" >> $PACKAGE_LOG

    echo "------------------------------" >> $PACKAGE_LOG
    echo "Directories in /opt/diametriq/" >> $PACKAGE_LOG
    echo "------------------------------" >> $PACKAGE_LOG
    if [ -d /opt/diametriq/ ];then
    echo "`ls -lrt /opt/diametriq`" >> $PACKAGE_LOG
    fi
    if [ -d /etc/.${S_PRODUCT_NAME} ];then
    echo "-------------------" >> $PACKAGE_LOG
    echo "PACKAGE FILES STATE" >> $PACKAGE_LOG
    echo "-------------------" >> $PACKAGE_LOG

    if [ -e /etc/.${S_PRODUCT_NAME}/db_upgrade_info ];then
    echo "-------------------------" >> $PACKAGE_LOG
    echo "/etc/.${S_PRODUCT_NAME}/db_upgrade_info" >> $PACKAGE_LOG
    echo "-------------------------" >> $PACKAGE_LOG
    echo "`cat /etc/.${S_PRODUCT_NAME}/db_upgrade_info`" >> $PACKAGE_LOG
    else
    echo "/etc/.${S_PRODUCT_NAME}/db_upgrade_info does not exist!"
    fi

    if [ -e /etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_install_info ];then
    echo "--------------------------" >> $PACKAGE_LOG
    echo "/etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_install_info" >> $PACKAGE_LOG
    echo "--------------------------" >> $PACKAGE_LOG
    echo "`cat /etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_install_info`" >> $PACKAGE_LOG
    else
    echo "/etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_install_info does not exist!"
    fi

    if [ -e /etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_uninstall_info ];then
    echo "----------------------------" >> $PACKAGE_LOG
    echo "/etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_uninstall_info" >> $PACKAGE_LOG
    echo "----------------------------" >> $PACKAGE_LOG
    echo "`cat /etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_uninstall_info`" >> $PACKAGE_LOG
    else
    echo "/etc/.${S_PRODUCT_NAME}/${S_PRODUCT_NAME}_uninstall_info does not exist!"
    fi

    fi
    echo "-----------------------------------------------------------------------------------------" >> $PACKAGE_LOG
   
}

function configure_mysql()
{
  n='
'
    choice="no" #default value
    if [ ! -z $DRE_CNF_FILE ];then
        choice="yes"
    fi
    while [ "$choice" == "no" ]
    do    
    configuration_heading "Mysql"
    MysqlUsername="root"
    MysqlPassword=`silent_null_check $'MySQL Root Password\t\t\t:' $'\nMySQL Root Password (should not be null):'`
    ConfirmMysqlPass=`silent_null_check $'\nConfirm MySQL Root Password\t\t:' $'\nConfirm MySQL root Password\n(should not be null)\t\t\t:'`
    MysqlPassword=`compare_passwords $MysqlPassword $ConfirmMysqlPass`
     echo ""
    MysqlIpAddress="$MySQL_Local_IP"
    MysqlPort=$MySQL_Port
    if [ ! -e $DRE_CONFIG ];then
        echo "MysqlUsername=$MysqlUsername" >> $DRE_CONFIG
    else
        if [ "`check_if_config_exist "MysqlUsername"`" == 1 ];then
            #if field exist just change the value
            LOG_DEBUG "add mysqlusername" $LINENO
            sed -i "s/MysqlUsername.*/MysqlUsername=$MysqlUsername/g" $DRE_CONFIG
        else
            #else append the fieldname and value
            LOG_DEBUG "append mysqlusername" $LINENO
            echo "MysqlUsername=$MysqlUsername" >> $DRE_CONFIG
        fi
    fi

    if [ "`check_if_config_exist "MysqlPassword"`" == 1 ];then
        sed -i "s/MysqlPassword.*/MysqlPassword=$MysqlPassword/g" $DRE_CONFIG
    else
        echo "MysqlPassword=$MysqlPassword" >> $DRE_CONFIG
    fi

    if [ "`check_if_config_exist "MysqlIpAddress"`" == 1 ];then
        sed -i "s/MysqlIpAddress.*/MysqlIpAddress=$MysqlIpAddress/g" $DRE_CONFIG
    else
        echo "MysqlIpAddress=$MysqlIpAddress" >> $DRE_CONFIG
    fi
    
    if [ "`check_if_config_exist "MysqlPort"`" == 1 ];then
        sed -i "s/MysqlPort.*/MysqlPort=$MysqlPort/g" $DRE_CONFIG
    else
        echo "MysqlPort=$MysqlPort" >> $DRE_CONFIG
    fi
    #confirm_inputs $MYSQL_CFG 
    #if [ $? -eq 0 ];then
    #    choice="yes"
    #fi
    check_mysql_configuration
    if [ $? -eq 1 ];then
	choice="no"
    else
	choice="yes"
    fi
    done
   
}

function configure_newuser_for_cli()
{
    local username="diametriq"
    local password="diametriq@123"
    local RET=0

    grep $username /etc/passwd > /dev/null 
    if [ $? -ne 0 ];then
    	useradd $username
    	if [ $? != 0 ];then
        	PLOG_ERROR "Failed to create user" $LINENO
        	RET=1
		return $RET
    	fi
    else
	LOG_DEBUG "$username User already exist" $LINENO
    fi

    echo $password | passwd $username --stdin 1> /dev/null 2> /dev/null
    if [ $? != 0 ];then
        PLOG_ERROR "Failed to create user" $LINENO
        RET=1
	return $RET
    fi
    
    if [ ! -d /home/$username ];then
	mkdir -p /home/$username 
    fi    

    cp /opt/diametriq/${S_PRODUCT_NAME}/config/telnet.expect /home/$username/.
    if [ $? != 0 ];then
        PLOG_ERROR "Failed to copy expect script" $LINENO
        RET=1
	return $RET
    fi

    return $RET
}
#####################################################################
# MySQL related validation functions
#####################################################################

#if arg is passed validate password from passed user config file
function check_mysql_configuration()
{
    if [ $# -eq 1 ];then
        local ip="$MySQL_Local_IP"
        local port="$MySQL_Port"
        local username="$mysql_username"
	local password="$mysql_root_password"
    else
        local ip=`GetMysqlIpAddress`
        local username=`GetMysqlUsername`
        local password=`GetMysqlPassword`
        local port=`GetMysqlPort`
    fi
    check_and_start_mysql
    PLOG_INFO "Checking Mysql configuration...." $LINENO
    my="mysql  --host=$ip --user=$username --password=$password --port=$port -se"

    local RET=0
    ${my} "show databases" 1> /dev/null 2> /dev/null
    if [ $? != 0 ];then
        PLOG_ERROR "Wrong Mysql configuration" $LINENO
        RET=1
    else
 	
	mysql_user_permission_validation "$username" "$password" 
	if [ $? -ne 0 ];then
	    PLOG_ERROR "No sufficient permissions for $username!" $LINENO
	    RET=1
	else
	    RET=0
	fi
    fi

    return $RET
}

function mysql_user_permission_validation()
{

	local IP="$MySQL_Local_IP"
	local USERNAME=$1
	local PASSWORD=$2
	local PORT="$MySQL_Port"
	my="mysql  --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT -se"


	local OUTPUT=`${my} "show grants\G"| tr " " "_"  2>/dev/null` 

	check_for_All_privilege "$OUTPUT"
	if [ $? -eq 0 ];then
		return 0
	fi

	check_for_privilege "$OUTPUT"
	if [ $? -ne 0 ];then
		return 1
	fi

	return 0
}

function check_for_All_privilege()
{
	local OUTPUT="$1"
	echo "$OUTPUT" | grep "GRANT_ALL_PRIVILEGES" 1>/dev/null 2>/dev/null

	if [ $? -ne 0 ];then
		return 1
	fi
}

function check_for_privilege()
{
	local OUTPUT="$1"
	echo "$OUTPUT" | grep "_SELECT," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "SELECT Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_INSERT," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "INSERT Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_UPDATE," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "UPDATE Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_DELETE," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "DELETE Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_CREATE," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "CREATE Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_DROP," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "DROP Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_REFERENCES," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "REFERENCES Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_INDEX," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "INDEX Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_ALTER," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "ALTER Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_SUPER," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "SUPER Privilege is not there for the user " $LINENO
		return 1
	fi


	echo "$OUTPUT" | grep "_LOCK_TABLES," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "LOCK TABLES Privilege is not there for the user " $LINENO
		return 1
	fi


	echo "$OUTPUT" | grep "_EXECUTE," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "EXECUTE Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_REPLICATION_SLAVE," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "REPLICATION SLAVE Privilege is not there for the user " $LINENO
		return 1
	fi


	echo "$OUTPUT" | grep "_REPLICATION_CLIENT," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "REPLICATION CLIENT Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_CREATE_ROUTINE," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "CREATE ROUTINE Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_ALTER_ROUTINE," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "ALTER ROUTINE Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_CREATE_USER," 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "CREATE USER Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_TRIGGER" 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "TRIGGER Privilege is not there for the user " $LINENO
		return 1
	fi

	echo "$OUTPUT" | grep "_WITH_GRANT_OPTION" 1>/dev/null 2>/dev/null
	if [ $? -ne 0 ];then
		PLOG_ERROR "GRANT Privilege is not there for the user " $LINENO
		return 1
	fi
}

############################################################################

function configure_sigtran()
{
   n='
'
    local choice="no"
    if [ ! -z $DRE_CNF_FILE ];then
        choice="yes"
    fi
    while [ "$choice" == "no" ]
    do
    configuration_heading "IWF Sigtran"
    PointCode=`null_check $'Point Code \t\t\t:' $'Point Code(should not be null)\t :'`
#    NI=`spl_num_check $'NI:\n 1) NATIONAL\n 2) INTERNATIONAL\n Enter valid Option\t\t:' $'NI(Enter valid Option)\t\t :' "1" "2" "1"`
    SSN=`spl_num_check  $'SSN:\n 1) HLR\n 2) SGSN\n 3) CAP\n Enter valid Option\t\t:' $'SSN (Enter valid Option)\t\t :' "1" "3" "3"`
    TcapInvokeTimer=`spl_num_check $'TCap Invoke Timer\t\t:' $'TCap Invoke Timer (Invalid range)\t :' "1" "65535" "30"`
   
#    if [ "$NI" == "1" ];then
#        NI_NUM="1"
#    fi
# 
#    if [ "$NI" == "2" ];then
#        NI_NUM="0"
#    fi

    if [ "$SSN" == "1" ];then
        SSN_STRING="HLR"
    fi
     
    if [ "$SSN" == "2" ];then
        SSN_STRING="SGSN"
    fi
      
    if [ "$SSN" == "3" ];then
        SSN_STRING="CAP"
    fi
        
    if [ "`check_if_config_exist "PointCode"`" == 1 ];then
        sed -i "s/PointCode.*/PointCode=$PointCode/g" $DRE_CONFIG
    else
        echo "PointCode=$PointCode" >> $DRE_CONFIG
    fi

#    if [ "`check_if_config_exist "NI"`" == 1 ];then
#        sed -i "s/NI.*/NI=$NI_NUM/g" $DRE_CONFIG
#    else
#        echo "NI=$NI_NUM" >> $DRE_CONFIG
#    fi

    if [ "`check_if_config_exist "SSN"`" == 1 ];then
        sed -i "s/SSN.*/SSN=$SSN_STRING/g" $DRE_CONFIG
    else
        echo "SSN=$SSN_STRING" >> $DRE_CONFIG
    fi

    if [ "`check_if_config_exist "TcapInvokeTimer"`" == 1 ];then
        sed -i "s/TcapInvokeTimer.*/TcapInvokeTimer=$TcapInvokeTimer/g" $DRE_CONFIG
    else
        echo "TcapInvokeTimer=$TcapInvokeTimer" >> $DRE_CONFIG
    fi

    confirm_inputs $SIGTRAN_CFG
    if [ $? -eq 0 ];then
            choice="yes"
        fi
    done


}

function configure_localhost()
{
   n='
'
    local choice="no"
    if [ ! -z $DRE_CNF_FILE ];then
        choice="yes"
    fi
    while [ "$choice" == "no" ]
    do
    configuration_heading "${PRODUCT_NAME} Local Host"
    LocalHostName=`null_check $'Host Name\t\t\t:' $'Host Name(should not be null)\t:'`
    LocalRealmName=`null_check $'Realm\t\t\t\t:' $'Realm(should not be null)\t:'`
    LocalIpAddress=`validate_ip $'IP Address\t\t\t:' $'IP Address (Enter valid IP)\t:'`
    PublicIpAddress=`spl_validate_ip $'Public IP Address\t\t:' $'Public IP Address\n(Enter valid IP)\t\t:'`

    confirm_transport_defaults
    if [ $? -ne 0 ];then
        PLOG_INFO "1. Enter Port" $LINENO
        PLOG_INFO "2. Enter Secure Port" $LINENO
        local ch_port_type=`spl_num_check $'Enter choice(1 or 2)\t\t:' $'Enter choice(1 or 2)\t\t:' "1" "2"`
        if [ "$ch_port_type" == "1" ];then
	    LocalPort=`spl_num_check $'Port\t\t\t\t:' $'Port (Invalid port range)\t:' "1" "65535" `
            LocalTransportType=`tcp_sctp_check $'Transport Type(TCP/SCTP)\t:' $'Transport Type(should be TCP/SCTP):' `
	    LocalPort2="NULL"
	    LocalTransportType2="NULL"
	    SecureLocalPort="NULL"
	    LocalTransportType3="NULL"
        else
	    SecureLocalPort=`spl_num_check $'Secure Port\t\t\t:' $'Secure Port (Invalid port range):' "1" "65535" `
            LocalTransportType3="1"
	    LocalPort="NULL"
	    LocalTransportType="NULL"
	    LocalPort2="NULL"
	    LocalTransportType2="NULL"
        fi

    else
        #user confirmed the defaults so assigning defaults
        LocalPort="3868"
        LocalTransportType="1"
	LocalPort2="3868"
        LocalTransportType2="2"
	SecureLocalPort="5658"
	LocalTransportType3="1"
	

    fi

    #LocalPort=`spl_num_check $'Port\t\t\t\t:' $'Port (Invalid port range)\t:' "1" "65535" "3868"`
    #LocalTransportType=`tcp_sctp_check $'Transport Type(TCP/SCTP)\t:' $'Transport Type(should be TCP/SCTP):' "SCTP"`
    
    
        
    if [ "`check_if_config_exist "LocalHostName"`" == 1 ];then
        sed -i "s/LocalHostName.*/LocalHostName=$LocalHostName/g" $DRE_CONFIG
    else
        echo "LocalHostName=$LocalHostName" >> $DRE_CONFIG
    fi

    if [ "`check_if_config_exist "LocalRealmName"`" == 1 ];then
        sed -i "s/LocalRealmName.*/LocalRealmName=$LocalRealmName/g" $DRE_CONFIG
    else
        echo "LocalRealmName=$LocalRealmName" >> $DRE_CONFIG
    fi

    if [ "`check_if_config_exist "LocalIpAddress"`" == 1 ];then
        sed -i "s/LocalIpAddress.*/LocalIpAddress=$LocalIpAddress/g" $DRE_CONFIG
    else
        echo "LocalIpAddress=$LocalIpAddress" >> $DRE_CONFIG
    fi
    if [ "`check_if_config_exist "PublicIpAddress"`" == 1 ];then
        sed -i "s/PublicIpAddress.*/PublicIpAddress=$PublicIpAddress/g" $DRE_CONFIG
    else
        echo "PublicIpAddress=$PublicIpAddress" >> $DRE_CONFIG
    fi


    if [ "`check_if_config_exist "LocalPort"`" == 1 ];then
        sed -i "s/LocalPort=.*/LocalPort=$LocalPort/g" $DRE_CONFIG
    else
        echo "LocalPort=$LocalPort" >> $DRE_CONFIG
    fi

    if [ "`check_if_config_exist "LocalTransportType"`" == 1 ];then
        sed -i "s/LocalTransportType=.*/LocalTransportType=$LocalTransportType/g" $DRE_CONFIG
    else
        echo "LocalTransportType=$LocalTransportType" >> $DRE_CONFIG
    fi

    if [ "`check_if_config_exist "LocalPort2"`" == 1 ];then
        sed -i "s/LocalPort2.*/LocalPort2=$LocalPort2/g" $DRE_CONFIG
    else
        echo "LocalPort2=$LocalPort2" >> $DRE_CONFIG
    fi

    if [ "`check_if_config_exist "LocalTransportType2"`" == 1 ];then
        sed -i "s/LocalTransportType2.*/LocalTransportType2=$LocalTransportType2/g" $DRE_CONFIG
    else
        echo "LocalTransportType2=$LocalTransportType2" >> $DRE_CONFIG
    fi

    if [ "`check_if_config_exist "SecureLocalPort"`" == 1 ];then
        sed -i "s/SecureLocalPort.*/SecureLocalPort=$SecureLocalPort/g" $DRE_CONFIG
    else
        echo "SecureLocalPort=$SecureLocalPort" >> $DRE_CONFIG
    fi

    if [ "`check_if_config_exist "LocalTransportType3"`" == 1 ];then
        sed -i "s/LocalTransportType3.*/LocalTransportType3=$LocalTransportType3/g" $DRE_CONFIG
    else
        echo "LocalTransportType3=$LocalTransportType3" >> $DRE_CONFIG
    fi


    if [ "`check_if_config_exist "LocalHostName"`" == 1 ];then
        sed -i "s/LocalHostName.*/LocalHostName=$LocalHostName/g" $DRE_CONFIG
    else
        echo "LocalHostName=$LocalHostName" >> $DRE_CONFIG
    fi
    confirm_inputs $LOCALHOST_CFG
    if [ $? -eq 0 ];then
            choice="yes"
        fi
    done

}

#this function while rollback checks if there is any difference 
#in the tipc configuration of previous PRODUCT version, if yes it will
#restore it else it will do nothing
function check_and_reconfig_tipc()
{

    lsmod|grep tipc >/dev/null
    if [ $? -eq 0 ];then
        NODE_ID=`tipc-config -a|cut -d'<' -f2|cut -d'>' -f1`
	LOG_DEBUG "Node Address configured=$NODE_ID" $LINENO
	NET_ID=`tipc-config -netid|cut -d':' -f2|cut -d' ' -f2`
	LOG_DEBUG "Net id configured=$NET_ID" $LINENO	
	tipc-config -b|grep "No active bearers"
	if [ $? -ne 0 ];then
	    BEARERS=`tipc-config -b|grep -v "Bearers:"|sort`
	    LOG_DEBUG "Bearers configured=$BEARERS" $LINENO
	else
	    LOG_WARNING "No active bearers found" $LINENO
	fi
	BRRS=`GetBearerName`
        CFG_BEARERS=`echo $BRRS|tr "," "\n"|sort`
	LOG_DEBUG "Bearers from ${S_PRODUCT_NAME}.cfg=$CFG_BEARERS" $LINENO
	if [ "$NODE_ID" == "`GetTipcNodeAddress`" ] && [ "$NET_ID" == "`GetNetID`" ] && [ "$BEARERS" == "$CFG_BEARERS" ];then
	    PLOG_INFO "No change in tipc configurations!" $LINENO
	else
 	    PLOG_INFO "Change in Tipc found!" $LINENO
	    cd /opt/diametriq/${S_PRODUCT_NAME}/lib/tipc1* && ./install.sh
	    
	fi
    else
	PLOG_ERROR "TIPC not found!" $LINENO
    fi
}
#function to configure tipc bearer only
#mainly used when we configure/reconfigure bonding
function configure_tipc_bearer()
{
    if [ -z $DRE_CNF_FILE ];then
        configuration_heading "TIPC Bearer"
        BearerName=`null_check $'Bearer Name [ex.eth:eth3,eth:eth4 or eth:bond1]\t  :' $'Bearer Name[ex. eth:eth3,eth:eth4 or eth:bond1]\n(should not be null)\t\t\t\t  :'`
        if [ "`check_if_config_exist "BearerName"`" == 1 ];then
            sed -i "s/BearerName.*/BearerName=$BearerName/g" $DRE_CONFIG
        else
            echo "BearerName=$BearerName" >> $DRE_CONFIG
        fi
    fi
    check_and_reconfig_tipc
}

function configure_tipc()
{
  n='
'
    local CONFIGURE=""
    modprobe tipc 2>/dev/null
    if [ $? -eq 0 ];then
	CONFIGURE="false"
    else
	CONFIGURE="true"
    fi
    
    if [ "$CONFIGURE" == "true" ] || [ "$1" == "--reconfigure" ] ; then
        LOG_INFO "Tipc is not configured..." $LINENO
        local choice="no"
        if [ ! -z $DRE_CNF_FILE ];then
            choice="yes"
        fi
   	    while [ "$choice" == "no" ]
   	    do
            configuration_heading "TIPC Configuration"
            NetID=`num_check $'TIPC Net ID [ex. 2112, less than 9999]\t\t  :' $'TIPC Net ID [ex. 2112, less than 9999]\n(should be integer)\t\t\t\t  :'`
            TipcNodeAddress=`null_check $'TIPC Node Address [ex. 2.2.4, <zone.cluster.node>]:' $'TIPC Node Address [ex. 2.2.4, <zone.cluster.node>]\n(should not be null)\t\t\t\t  :'`
            BearerName=`null_check $'Bearer Name [ex.eth:eth3,eth:eth4 or eth:bond1]\t  :' $'Bearer Name[ex. eth:eth3,eth:eth4 or eth:bond1]\n(should not be null)\t\t\t\t  :'`
    
            if [ "`check_if_config_exist "NetID"`" == 1 ];then
                sed -i "s/NetID.*/NetID=$NetID/g" $DRE_CONFIG
            else
                echo "NetID=$NetID" >> $DRE_CONFIG
            fi
        
            if [ "`check_if_config_exist "TipcNodeAddress"`" == 1 ];then
                sed -i "s/TipcNodeAddress.*/TipcNodeAddress=$TipcNodeAddress/g" $DRE_CONFIG
            else
                echo "TipcNodeAddress=$TipcNodeAddress" >> $DRE_CONFIG
            fi
  
            if [ "`check_if_config_exist "BearerName"`" == 1 ];then
                sed -i "s/BearerName.*/BearerName=$BearerName/g" $DRE_CONFIG
            else
                echo "BearerName=$BearerName" >> $DRE_CONFIG
            fi
            confirm_inputs $TIPC_CFG
	        if [ $? -eq 0 ];then
		        choice="yes"
	        fi
	    done

    fi 
   
}


function check_if_config_exist()
{
    grep "$1" $DRE_CONFIG 1>/dev/null
    if [ $? -eq 0 ];then
        echo "1"  
    else
        echo "0"
    fi
}

#checks if all the fields of general config are present in /etc/PRODUCT.cfg
function check_config()
{
    if [ "`check_if_config_exist "MysqlUsername"`" == "1" ] && \
       [ "`check_if_config_exist "MysqlPassword"`" == "1" ] && \
       [ "`check_if_config_exist "MysqlIpAddress"`" == "1" ] && \
       [ "`check_if_config_exist "MysqlPort"`" == "1" ] && \
       [ "`check_if_config_exist "LocalHostName"`" == "1" ] && \
       [ "`check_if_config_exist "LocalRealmName"`" == "1" ] && \
       [ "`check_if_config_exist "LocalIpAddress"`" == "1" ] && \
       [ "`check_if_config_exist "LocalPort"`" == "1" ] && \
       [ "`check_if_config_exist "LocalTransportType"`" == "1" ] && \
       [ "`check_if_config_exist "NetID"`" == "1" ] && \
       [ "`check_if_config_exist "TipcNodeAddress"`" == "1" ] && \
       [ "`check_if_config_exist "BearerName"`" == "1" ];then

        echo "1"
    else
        echo "0"      
    fi   
}

function check_ha_config()
{
    if [ "`check_if_config_exist "DreInstallMode"`" == "1" ];then
        echo "1"
    else
        echo "0"
    fi
}


function check_dependencies()
{
    if [ $# -ne 1 ];then
        echo "Usage: check_dependencies <dependency list file path>"
	return 1
    fi 
    LOG_DEBUG "file = $1" $LINENO
    if [ ! -e $1 ];then
	echo "$1 does not exist"
	return 1
    fi
    LIST=`cat $1`
    RET=0
    for RPM in $LIST
    do
        if [ "`GetDreInstallMode`" == "1" ];then    
	        if [ "$RPM" == "heartbeat-3.0.4-1.el6.x86_64" ];then
	            LOG_DEBUG "checking for heartbeat" $LINENO
 	        fi
		if [ "$RPM" == "expect-devel" ];then
		    LOG_DEBUG "expect devel not required for standalone" $LINENO
		    continue
		fi
        fi
        if [ `is_dep_installed $RPM` == "true" ];then
            PLOG_INFO "$RPM is installed.." $LINENO
        else
            PLOG_ERROR "$RPM is not installed!" $LINENO
  	        RET=1
        fi
    done
    if [ $RET -eq 1 ];then
	   PLOG_ERROR "Install the above dependencies and try again!" $LINENO
       if [ -e /etc/init/mysqld.conf ];then
          rm -f /etc/init/mysqld.conf
       fi

	   exit 1
    fi
}


function set_dre_mode()
{
    if [ ! -e /etc/sysconfig/${S_PRODUCT_NAME} ];then
        PLOG_ERROR "/etc/sysconfig/${S_PRODUCT_NAME} does not exist" $LINENO
        return 1
    fi
    LOG_DEBUG "GetDreInstallMode `GetDreInstallMode`" 
    case `GetDreInstallMode` in
    "1") sed -i "s/^export BASICOPTS=.*/export BASICOPTS=\"-i 13 -l 3 -m 1\"/g" /etc/sysconfig/${S_PRODUCT_NAME}  
	 LOG_INFO "-m 1" $LINENO 
	 ;;
    "2") sed -i "s/^export BASICOPTS=.*/export BASICOPTS=\"-i 13 -l 3 -m 0\"/g" /etc/sysconfig/${S_PRODUCT_NAME} 
	 LOG_INFO "-m 0" $LINENO
	 ;;
    "3") sed -i "s/^export BASICOPTS=.*/export BASICOPTS=\"-i 13 -l 3 -m 3\"/g" /etc/sysconfig/${S_PRODUCT_NAME} 
	 LOG_INFO "-m 3" $LINENO
	 ;;
    "4") sed -i "s/^export BASICOPTS=.*/export BASICOPTS=\"-i 13 -l 3 -m 4\"/g" /etc/sysconfig/${S_PRODUCT_NAME} 
	 LOG_INFO "-m 4" $LINENO
	 ;;

     *)  LOG_WARNING "GetDreInstallMode failure" $LINENO
	 ;;
    esac

}

function get_previous_dre_version()
{
    if [ `rpm -q ${S_PRODUCT_NAME}|wc -l` -gt 1 ];then
        if [ $PRODUCT = "dre" ];then
	        PREV_DRE_VER=`rpm -q ${S_PRODUCT_NAME}|tail -2|head -1`
            PREV_DRE_VER=${PRE_DRE_VER%*.*}
	        echo "$PREV_DRE_VER"
        fi

        if [ $PRODUCT = "iwf" ];then
	        PREV_IWF_VER=`rpm -q ${S_PRODUCT_NAME}|tail -2|head -1`
            PREV_IWF_VER=${PRE_IWF_VER%*.*}
	        echo "$PREV_IWF_VER"
        fi


    else
        echo "null"
    fi


}
function get_cur_dre_version()
{
    if [ `rpm -q ${S_PRODUCT_NAME}|grep -v "is not installed"|wc -l` -gt 0 ];then
        if [ $PRODUCT = "dre" ];then
            CUR_DRE_VER=`rpm -q ${S_PRODUCT_NAME}|tail -1`
            CUR_DRE_VER=${CUR_DRE_VER%*.*}
            CUR=`echo $CUR_DRE_VER|cut -d'_' -f1`
            echo "$CUR"
        fi

        if [ $PRODUCT = "iwf" ];then
            CUR_IWF_VER=`rpm -q ${S_PRODUCT_NAME}|tail -1`
            CUR_IWF_VER=${CUR_IWF_VER%*.*}
            CUR=`echo $CUR_IWF_VER|cut -d'_' -f1`
            echo "$CUR"
        fi


    else
        echo "null"
    fi

}

function get_rsync_inputs()
{  
    choice="no"
    while [ "$choice" == "no" ]
    do

        USERNAME=`null_check $'Enter the Remote-node Username\t\t\t  :' $'Enter the Remote-node Username(should not be null):' "root"`
        IP=`validate_ip $'Enter the Remote-node IP Address\t\t  :' $'Enter the Remote-node IP Address(Enter valid IP!) :'`
        #PASSWORD=`silent_null_check $'Enter the Remote-node Password\t\t\t  :' $'\nEnter the Remote-node Password(should not be null):'`
        #CONFIRM=`silent_null_check $'\nConfirm Remote-node Password\t\t\t  :' $'\nConfirm Remote-node Password(should not be null)  :'`
        #REMOTE_NODE_PASS=`compare_passwords $PASSWORD $CONFIRM`
        set_dre_cfg "RemoteNodeUsername" "$USERNAME"
        set_dre_cfg "RemoteNodeIP" "$IP"
        #set_dre_cfg "RemoteNodePassword" "$REMOTE_NODE_PASS"
        confirm_inputs $RSYNC_CFG
        if [ $? -eq 0 ];then
            choice="yes"
        fi
    done

}
function configure_rsync()
{
    configuration_heading "File Sync"
    #call the file replication script, ensure incrond is running
    #this script is an interactive script which takes few inputs from the user
    get_rsync_inputs
    LOG_INFO "Configuring file_replication..." $LINENO
    PREV=`get_previous_dre_version`
    if [ "$PREV" == "null" ];then
	LOG_DEBUG "$PREV : no previous ${S_PRODUCT_NAME} found" $LINENO
        /opt/diametriq/${S_PRODUCT_NAME}/scripts/file_replication.sh install
    else
	if [ -e "/opt/diametriq/$PREV/config/config_dir_file.cfg" ];then
	    LOG_DEBUG "$PREV has config_dir_file.cfg" $LINENO
	    CUR="/opt/diametriq/${S_PRODUCT_NAME}/config/config_dir_file.cfg"
	    PREV="/opt/diametriq/$PREV/config/config_dir_file.cfg"
 	    #check if any new files are added to be synced in the config_dir_file.cfg
	    #if yes update the file sync
	    diff $CUR $PREV >/dev/null
 	    if [ $? -ne 0 ];then
		LOG_INFO "There are new files added to be synced : `diff $CUR $PREV`" $LINENO
		/opt/diametriq/${S_PRODUCT_NAME}/scripts/file_replication.sh update
	    else
	  	LOG_INFO "No new files are added for sync" $LINENO		
	    fi
	 
 	else
	    LOG_DEBUG "No config_dir_file.cfg present in $PREV" $LINENO
	    /opt/diametriq/${S_PRODUCT_NAME}/scripts/file_replication.sh install    
	fi	
    fi  
}

function remove_tipc_from_rc_local()
{
    sed -i /tipc-config/d /etc/rc.d/rc.local
}

function copy_dre_cnf()
{
    local HOST_NAME=`hostname`
    if [ -n "$DRE_CNF_FILE" ];then
	LOG_INFO "Copying the passed ${S_PRODUCT_NAME} cnf file" $LINENO
	cp $DRE_CNF_FILE /opt/diametriq/${S_PRODUCT_NAME}/config/${HOST_NAME}_${S_PRODUCT_NAME}.cnf
    else
	LOG_INFO "Calling create_user_config.sh" $LINENO
	/opt/diametriq/${S_PRODUCT_NAME}/scripts/create_user_config.sh
    fi

}

function backup_cnf_file()
{
    cp -f /opt/diametriq/${PRODUCT}/.syscfg/install_${PRODUCT}.cnf /opt/diametriq/${PRODUCT}/.syscfg/install_${PRODUCT}.cnf_`date +%s`
    cp -f $DRE_CNF_FILE /opt/diametriq/${PRODUCT}/.syscfg
}


function update_cnf_timestamp()
{
    stat --format=%z /opt/diametriq/${PRODUCT}/config/install_${PRODUCT}.cnf > /etc/.${PRODUCT}/cnf_update_time
}

function check_if_cnf_modified()
{
    file_time="`stat --format=%z /opt/diametriq/${PRODUCT}/config/install_${PRODUCT}.cnf`"
    cnf_update_time="`cat /etc/.${PRODUCT}/cnf_update_time`"
    if [ "$file_time" == "$cnf_update_time" ];then
	echo "no"
    else
	echo "yes"
    fi
}

function post_rpm_install()
{
    LOG_DEBUG "in post_rpm_install" $LINENO
    
    #if its an upgrade dont call the configure functions
    if [ "$1" == "--upgrade" ];then
        LOG_DEBUG "post_rpm_install upgrade" $LINENO
        #if its an upgrade from standalone to active standby execute standalone_to_ha script
        if [ "$STANDALONE_TO_ACTIVESTANDBY" == "yes" ];then
	    if [ ! -z "$DRE_CNF_FILE" ];then
		cp $DRE_CNF_FILE /opt/diametriq/${S_PRODUCT_NAME}/config/user_${S_PRODUCT_NAME}.cnf
	        /opt/diametriq/${S_PRODUCT_NAME}/scripts/standalone_to_ha.sh "--upgrade" 
	    else
		/opt/diametriq/${S_PRODUCT_NAME}/scripts/standalone_to_ha.sh
	    fi   

        fi
    else
	LOG_DEBUG "Post_rpm_install" $LINENO
    if [ $S_PRODUCT_NAME = "dre" ];then
	    configure_alarms
    fi
        #if dre installation mode is active-stand by configure rsync for file replication
        if [ "`GetDreInstallMode`" == "2" ] || [ "`GetDreInstallMode`" == "3" ] || [ "`GetDreInstallMode`" == "4" ] ;then
    	    configure_rsync
        fi

    fi
    #set the installation mode in /etc/sysconfig/dre
    set_dre_mode 
    if [ "$PRODUCT" == "dre" ];then
        configure_webgui_https
    fi
    check_and_start_3rdparty_proccesses
    configure_newuser_for_cli
    config_ip_tables
    #if dre installation mode is active host standby
    if [ "`GetDreInstallMode`" == "4" ];then
        #have to handle couchbase configuration during upgrade differentl
        if [ "$1" == "--upgrade" ];then
            configure_couchbase "--upgrade"
        else
            configure_couchbase
        fi
	    chkconfig couchbase-server on
    else
	#in other modes stop couchbase
        if [ -e /etc/init.d/couchbase-server ];then
	        LOG_DEBUG "Couchbase is installed!" $LINENO
	        LOG_DEBUG "Stop/disable couchbase service" $LINENO
	        check_and_stop_couchbase
	        chkconfig couchbase-server off	
	    else
	        LOG_DEBUG "Couchbase is not installed!" $LINENO
	    fi
    fi

    #copy the actuall file passed by the user
    cp $DRE_CNF_FILE /opt/diametriq/${PRODUCT}/config/install_${PRODUCT}.cnf
    copy_dre_cnf
    remove_tipc_from_rc_local
    update_cnf_timestamp
    memc_servers_set
      
      
  
}

function hostname_check()
{
        default=""
        error_bk=$2
        read -e -i "$default" -p "$1" as

        if [ "$as" = `uname -n` ]; then
                error="$1 (Error:- Local hostname and Mate Hostname are same) :"
                as=""
        else
                error=$error_bk
        fi
        while [ -z $as ]
        do
                read -e -i "$default" -p "$error" as

                if [ "$as" = `uname -n` ]; then
                        error="$1 (Error:- Local hostname and Mate Hostname are same) :"
                        as=""
                else
                        error=$error_bk
                fi
        done
        echo $as
}


function on_off_check()
{
    default=$3	
    read -e -i "$default" -p "$1" as
    actualvalue=${as:-$default}

    if [ "$as" = "on" ]
    then
            as="on"       
    else
            if [ "$as" = "off" ]
            then
            as="off"
            else
            as=""   
        fi  
    fi  

    while [ -z $as ]
    do  
	read -e -i "$default" -p "$2" as
	actualvalue=${as:-$default}

        if [ "$as" = "on" ]
        then
            as="on"
        else
                if [ "$as" = "off" ]
                then
                as="off"
                else
                as=""   
            fi  
        fi  

    done
    echo $actualvalue
}

function master_slave_check()
{
    default=$3	
    read -e -i "$default" -p "$1" as
    actualvalue=${as:-$default}

    if [ "$as" = "master" ]
    then
            as="MASTER"       
    else
            if [ "$as" = "slave" ]
            then
            as="SLAVE"
            else
            as=""   
        fi  
    fi  

    while [ -z $as ]
    do  
	read -e -i "$default" -p "$2" as
	actualvalue=${as:-$default}

        if [ "$as" = "master" ]
        then
            as="MASTER"
        else
                if [ "$as" = "slave" ]
                then
                as="SLAVE"
                else
                as=""   
            fi  
        fi  

    done
    echo $as
}


function configure_NTP()
{
    local choice="no"
    if [ ! -z $DRE_CNF_FILE ];then
        choice="yes"
        NtpServerIP=`GetNtpServerIP`
    fi
    NTP_CONF=/etc/ntp.conf
    #backup NTP conf file
    if [ ! -e /etc/ntp.confbackup ];then
        cp $NTP_CONF /etc/ntp.confbackup
    fi
    #delete all entries of Public NTP servers
    sed -i /"^server.*"/d  $NTP_CONF

    while [ "$choice" == "no" ]
    do
        configuration_heading "NTP"
                NtpServerIP=`validate_ip $'NTP Server IP Address\t\t\t:' $'NTP Server IP Address (Enter Valid IP)  :'`
        grep "NtpServerIP" $DRE_CONFIG >/dev/null
        if [ $? -ne 0 ];then
            echo "NtpServerIP=$NtpServerIP" >> $DRE_CONFIG
        else
            sed -i "s/^NtpServerIP.*/NtpServerIP=$NtpServerIP/g" $DRE_CONFIG
        fi
        confirm_inputs $NTP_CFG
        if [ $? -eq 0 ];then
            choice="yes"
        fi
    done

    echo "server $NtpServerIP" >> $NTP_CONF
    chkconfig ntpd on
    pgrep ntpd >/dev/null
    if [ $? -eq 0 ];then
        service ntpd restart 2>/dev/null
    else
	service ntpd start 2>/dev/null
    fi
    LOG_INFO "NTP Server IP entered = $NtpServerIP" $LINENO
}

function configure_alarms()
{
    local choice="no"
    mv /etc/snmp/snmpd.conf /etc/snmp/snmpd.confbkp 2>/dev/null
    cp /opt/diametriq/${S_PRODUCT_NAME}/config/snmpd.conf /etc/snmp/

    #delete the trap2sink entries from /etc/snmp/snmpd.conf
    sed -i /^trap2sink/d /etc/snmp/snmpd.conf
    if [ ! -z $DRE_CNF_FILE ];then
        
        #add the trap2sink entries one by one from the stored array
        i=0
        for ip in "${trap_sink_ip[@]}"
        do
            i=$((i + 1))
            LOG_DEBUG "$ip " $LINENO
            echo "trap2sink $ip" >> /etc/snmp/snmpd.conf
        done

        choice="yes"
    fi
    local i=1
    while [ "$choice" == "no" ]
    do

        sed -i /^TrapSinkIP/d $DRE_CONFIG
        configuration_heading "Alarms"
        # backup snmpd.conf
        while [ 1 ]
        do
            TrapSinkIP[$i]=`validate_ip $'Trap Sink IP\t\t\t:' $'Trap Sink IP (Enter valid IP!)  :'`
            echo "trap2sink ${TrapSinkIP[$i]}" >>/etc/snmp/snmpd.conf
            echo "TrapSinkIP$i=${TrapSinkIP[$i]}" >> $DRE_CONFIG
            ch=`yes_no_check "Do you want to configure another Trap Sink IP?[yes/no] :"`
            if [ "$ch" == "no" ];then
                break;
            fi
            i=$(($i+1))
        done
	    confirm_inputs $ALARM_CFG
        if [ $? -eq 0 ];then
             choice="yes"
        else
            #unset the array
            unset TrapSinkIP
        fi
    done
    pgrep snmpd >/dev/null
    if [ $? -eq 0 ];then
        stop snmpd 
	PLOG_INFO "Restarting snmpd..."   
    else
	PLOG_INFO "Starting snmpd..."
    fi
    start snmpd
}

#function configure_ethernet_bonding()
#{
#    BOND_PATH=/tmp
    #configuration_heading "Ethernet bonding"
    #configure bonding only for active-standby mode
#    LOG_DEBUG "Configuring ethernet bonding..." $LINENO
#stop the NetworkManager
#    pgrep NetworkManager >/dev/null
#    if [ $? -eq 0 ];then
#	   service NetworkManager stop >/dev/null
#    fi
#    chkconfig NetworkManager off
#
#    LOG_DEBUG "Calling bond script" $LINENO
#    if [ ! -z $DRE_CNF_FILE ];then
#        $BOND_PATH/ip-bond.sh --config
#    else
#        $BOND_PATH/ip-bond.sh 
#    fi
	

#}

#hash table function 
function ht() 
{ 
    local ht=`echo "$*" |cksum`; echo "${ht//[!0-9]}"; 
}

#$1= key for map which is config field name, $2= value which is a display string
function insert_into_ht()
{
    configMap[`ht $1`]="$2"
}

function populate_ht()
{
    insert_into_ht "MysqlUsername" "Username	:"
    insert_into_ht "MysqlPassword" "Password	:"
    insert_into_ht "LocalHostName" "Hostname	:"
    insert_into_ht "LocalRealmName" "Realm	:"
    insert_into_ht "LocalIpAddress" "IP Address	:"
    insert_into_ht "LocalPort" "Port"
    insert_into_ht "LocalTransportType" "Transport Type(TCP/SCTP)	:"
    insert_into_ht "NetID" "Net ID [ex. 2112, less than 9999]	:"
    insert_into_ht "TipcNodeAddress" "TIPC Node Address [ex. 2.2.4, <zone.cluster.node>]	:"
    insert_into_ht "BearerName" "Bearer Name [ex. eth:eth3,eth:eth4,eth:bond0]	:"
    insert_into_ht "MysqlLocalIP" "(MySQL) Local IP Address	:"
    insert_into_ht "MysqlMateIP" "(MySQL) Mate IP Address	:"
    insert_into_ht "MysqlLocalHostname" "(MySQL) Local Hostname	:"
    insert_into_ht "MysqlMateHostname" "(MySQL) Mate HostName	:"
    insert_into_ht "HAMode" "HA Mode(master/slave)	:"
    insert_into_ht "VirtualIP" "(MySQL) VirtualIP in CIDR notation (a.b.c.d/x)	:"
    insert_into_ht "Ethernet" "(MySQL) Interface Name for Virtual IP      :"
    insert_into_ht "BroadcastAddress" "(MySQL) Network broadcast Address (w.x.y.z)       :"
    insert_into_ht "SubNetMaskPrefixLen" "MySQL) Subnet Mask Prefix length(in bits)       :"
    insert_into_ht "NtpServerIP" "NTP Server IP Address :"
    insert_into_ht "TrapSinkIP" "Trap Sink IP Address   :"
    insert_into_ht "" ""
    
}

function get_value_from_map()
{
    echo ${configMap[`ht $1`]}
}

#while upgrade check if all the config parameters are present and 
#take input for those which are not present
function check_and_update_config()
{
    RET=0;
    CONFIG_LIST="$1"
    LOG_INFO "Config :$CONFIG_LIST" $LINENO
    for CONFIG in $CONFIG_LIST
    do
	    #if config field exist in ${S_PRODUCT_NAME}.cfg
        LOG_INFO "Checking for $CONFIG..." $LINENO
	    if [ "`check_if_config_exist "$CONFIG"`" == 1 ];then
	        #if its empty
	        if [ -z `GetDreConfigValue "$CONFIG"` ];then
                PLOG_INFO "$CONFIG is not present in ${S_PRODUCT_NAME} configuration file! Please Enter" $LINENO
                    MAP_VAL=`get_value_from_map $CONFIG`
                    VAR=`null_check "$MAP_VAL"  "$MAP_VAL"`
                    sed -i "s/^$CONFIG=.*/$CONFIG=$VAR/g" $DRE_CONFIG
		    RET=1
	        fi
	    else
                PLOG_INFO "$CONFIG is not present in ${S_PRODUCT_NAME} configuration file! Please Enter" $LINENO
                MAP_VAL=`get_value_from_map $CONFIG`
                VAR=`null_check "$MAP_VAL"  "$MAP_VAL"`
                echo "$CONFIG=$VAR" >> $DRE_CONFIG
		RET=1

	    fi
    done  

    return $RET
}

function check_config_while_upgrade()
{
    TIPC_STATE_FILE=/etc/.${S_PRODUCT_NAME}/tipc_info
    MYSQL_CFG="MysqlUsername MysqlPassword"
    LOCAL_HOST_CFG="LocalHostName LocalRealmName LocalIpAddress LocalPort LocalTransportType"
    TIPC_CFG="NetID TipcNodeAddress BearerName"
    ALARM_CFG="TrapSinkIP"
    #check Mysql and Localhost config
    PLOG_INFO "Checking for Mysql and LocalHost config..." $LINENO
    check_and_update_config "$MYSQL_CFG"
    check_and_update_config "$LOCAL_HOST_CFG"
    if [ -e $TIPC_STATE_FILE ];then
        rm -f $TIPC_STATE_FILE
    fi
    #check TIPC config
    PLOG_INFO "Checking for TIPC config..." $LINENO
    check_and_update_config "$TIPC_CFG"
    if [ $? -ne 0 ];then
        echo "tipc_config_required" > $TIPC_STATE_FILE
    fi
    #check Alarm config
    #PLOG_INFO "Checking for Alarm config..." $LINENO
    #check_and_update_config "$ALARM_CFG"
    #
    if [ "`GetDreInstallMode`" == "2" ];then
	HEART_BEAT_STATE_FILE=/etc/.${S_PRODUCT_NAME}/heartbeat_info
	if [ -e $HEART_BEAT_STATE_FILE ];then
	    rm -f $HEART_BEAT_STATE_FILE
	fi
        HEARTBEAT_CFG="MysqlLocalIP MysqlMateIP MysqlLocalHostname MysqlMateHostname HAMode VirtualIP Ethernet BroadcastAddress SubNetMaskPrefixLen"
        NTP_CFG="NtpServerIP"
	#TODO upgrade considerations 
        #check Heartbeat config
       # PLOG_INFO "Checking for Heartbeat config..." $LINENO
       # check_and_update_config "$HEARTBEAT_CFG"
	#if [ $? -ne 0 ];then
	#    LOG_INFO "Heartbeat config not present"
	#    echo "heartbeat_config_required" > $HEART_BEAT_STATE_FILE
	#fi
        #check NTP config
        #PLOG_INFO "Checking for NTP config..." $LINENO
        #check_and_update_config "$NTP_CFG"
    fi
}

function configure_heartbeat()
{
    local choice="no"
    if [ ! -z $DRE_CNF_FILE ];then
        return
    fi
    while [ "$choice" == "no" ]
    do
    configuration_heading "Mysql Heartbeat"
    MysqlLocalIP=`validate_ip $'(MySQL) Local IP Address\t\t\t:' $'(MySQL) Local IP Address(Enter Valid IP)\t:'`
    if [ "`check_if_config_exist "MysqlLocalIP"`" == 1 ];then
        sed -i "s/MysqlLocalIP.*/MysqlLocalIP=$MysqlLocalIP/g" $DRE_CONFIG
    else
        echo "MysqlLocalIP=$MysqlLocalIP" >> $DRE_CONFIG
    fi

    MysqlMateIP=`validate_ip $'(MySQL) Mate IP Address\t\t\t\t:' $'(MySQL) Mate IP Address(Enter Valid IP)\t\t:'`
    if [ "`check_if_config_exist "MysqlMateIP"`" == 1 ];then
        sed -i "s/MysqlMateIP.*/MysqlMateIP=$MysqlMateIP/g" $DRE_CONFIG
    else
        echo "MysqlMateIP=$MysqlMateIP" >> $DRE_CONFIG
    fi
    MysqlLocalHostname=`uname -n`
#`null_check "(MySQL) Local Hostname       :" "(MySQL) Local Hostname (should not be null)            :"`
    if [ "`check_if_config_exist "MysqlLocalHostname"`" == 1 ];then
        sed -i "s/MysqlLocalHostname.*/MysqlLocalHostname=$MysqlLocalHostname/g" $DRE_CONFIG
    else
        echo "MysqlLocalHostname=$MysqlLocalHostname" >> $DRE_CONFIG
    fi
    MysqlMateHostname=`hostname_check $'(MySQL) Mate Host Name\t\t\t\t:' $'(MySQL) Mate Host Name(should not be null)\t:'`
    if [ "`check_if_config_exist "MysqlMateHostname"`" == 1 ];then
        sed -i "s/MysqlMateHostname.*/MysqlMateHostname=$MysqlMateHostname/g" $DRE_CONFIG
    else
        echo "MysqlMateHostname=$MysqlMateHostname" >> $DRE_CONFIG
    fi
    HAMode=`master_slave_check $'(MySQL) HA Mode(master/slave)\t\t\t:' $'(MySQL) HA Mode(should be master/slave)\t\t:' `
    if [ "`check_if_config_exist "HAMode"`" == 1 ];then
        sed -i "s/HAMode.*/HAMode=$HAMode/g" $DRE_CONFIG
    else
        echo "HAMode=$HAMode" >> $DRE_CONFIG
    fi
    VirtualIP=`ipv4_check $'(MySQL) Virtual IP in CIDR notation (a.b.c.d/x)\t:' $'(MySQL) Virtual IP in CIDR notation(a.b.c.d/x)\n(Enter Valid IP)\t\t\t\t:'`
    if [ "`check_if_config_exist "VirtualIP"`" == 1 ];then
        sed -i "s/VirtualIP.*/VirtualIP=`convert_cidrip_to_sed_cirdrip "$VirtualIP"`/g" $DRE_CONFIG
    else
        echo "VirtualIP=$VirtualIP" >> $DRE_CONFIG
    fi
    Ethernet=`null_check $'(MySQL) Interface Name for Virtual IP\t\t:' $'(MySQL) Interface Name for Virtual IP\n(should not be null)\t\t\t\t:'`
    if [ "`check_if_config_exist "Ethernet"`" == 1 ];then
        sed -i "s/Ethernet.*/Ethernet=$Ethernet/g" $DRE_CONFIG
    else
        echo "Ethernet=$Ethernet" >> $DRE_CONFIG
    fi
    BroadcastAddress=`/bin/ipcalc $VirtualIP -b|cut -d"=" -f2`
#`null_check "(MySQL) Network broadcast Address (w.x.y.z)       :" "(MySQL) Network broadcast addresss (w.x.y.z) (should not be null)            :"`
    if [ "`check_if_config_exist "BroadcastAddress"`" == 1 ];then
        sed -i "s/BroadcastAddress.*/BroadcastAddress=$BroadcastAddress/g" $DRE_CONFIG
    else
        echo "BroadcastAddress=$BroadcastAddress" >> $DRE_CONFIG
    fi
    SubNetMaskPrefixLen=`/bin/ipcalc $VirtualIP -p|cut -d"=" -f2`
#`num_check "(MySQL) Subnet Mask Prefix length(in bits)       :" "(MySQL) Subnet Mask Prefix length(in bits) (should be interger)            :"`
    if [ "`check_if_config_exist "SubNetMaskPrefixLen"`" == 1 ];then
        sed -i "s/SubNetMaskPrefixLen.*/SubNetMaskPrefixLen=$SubNetMaskPrefixLen/g" $DRE_CONFIG
    else
        echo "SubNetMaskPrefixLen=$SubNetMaskPrefixLen" >> $DRE_CONFIG
    fi
#
#    AutoFailback=`on_off_check "(MySQL) AutoFailback(on/off)       :" "(MySQL) AutoFailback (should be on/off)            :"`
#    if [ "`check_if_config_exist "AutoFailback"`" == 1 ];then
#        sed -i "s/AutoFailback.*/AutoFailback=$AutoFailback/g" $DRE_CONFIG
#    else
#        echo "AutoFailback=$AutoFailback" >> $DRE_CONFIG
#    fi
    confirm_inputs $HEARTBEAT_CFG
    if [ $? -eq 0 ];then
        choice="yes"
    fi
    done
}


#this function displays the user inputs for various configurations which is used for user confirmation
function display_inputs()
{
    echo ""
    case $1 in
        $BONDING_CFG)  #get hold of the arrays which have bonding info and display in loop	
		       local i=0
		       configuration_heading "Confirm Ethernet Bonding"	
		       for bondName in ${bond_name[@]}
		       do
			   PLOG_INFO "----------------------------------------------------------------" $LINENO
		           PLOG_INFO "Bond Name		   		= $bondName" $LINENO
			   PLOG_INFO "IP of $bondName	   			= ${bond_ip[$i]}" $LINENO
			   PLOG_INFO "Netmask of $bondName 			= ${bond_netmask[$i]}" $LINENO
			   PLOG_INFO "Interfaces/NICs associated with $bondName   = ${bond_nics[$i]}" $LINENO
			   PLOG_INFO "----------------------------------------------------------------" $LINENO
			   PLOG_INFO "" $LINENO
			   i=$(($i+1))
		       done
			 ;;

        $SIGTRAN_CFG) configuration_heading "Confirm IWF Sigtran"

			 PLOG_INFO "PointCode           = `GetPointCode`" $LINENO
#             if [ "`GetNI`" == "0" ];then
#                PLOG_INFO "NI                  = INTERNATIONAL" $LINENO
#             fi
#             if [ "`GetNI`" == "1" ];then
#                PLOG_INFO "NI                  = NATIONAL" $LINENO
#             fi
			 PLOG_INFO "SSN                 = `GetSSN`" $LINENO
			 PLOG_INFO "TcapInvokeTimer     = `GetTcapInvokeTimer`" $LINENO
				;;

        $LOCALHOST_CFG) configuration_heading "Confirm ${PRODUCT_NAME} Local Host"
			 PLOG_INFO "Hostname          = `GetLocalHostName`" $LINENO
			 PLOG_INFO "Realm             = `GetLocalRealmName`" $LINENO
			 PLOG_INFO "IP Address        = `GetLocalIpAddress`" $LINENO
			 if [  "`GetPublicIpAddress`" != "NULL" ];then
			     PLOG_INFO "Public IP Address = `GetPublicIpAddress`" $LINENO
			 else
			     PLOG_INFO "Public IP Address = Nil" $LINENO
			 
			 fi
                         PLOG_INFO "Port              = `GetLocalPort`" $LINENO
                     if [ "`GetLocalTransportType`" == "1" ];then
                         PLOG_INFO "Transport Type    = TCP" $LINENO
             else
                 PLOG_INFO "Transport Type    = SCTP" $LINENO
             fi

				;;
        $MYSQL_CFG)	configuration_heading "Confirm Mysql"
			PLOG_INFO "Username	   = `GetMysqlUsername`" $LINENO
			LOG_INFO "Password	   = `GetMysqlPassword`" $LINENO
				;;
        $TIPC_CFG)	configuration_heading "Confirm TIPC"
			PLOG_INFO "TIPC Net ID             = `GetNetID`" $LINENO
			PLOG_INFO "TIPC Node ID	        = `GetTipcNodeAddress`" $LINENO
			PLOG_INFO "Bearer Name	        = `GetBearerName`" $LINENO
				;;
        $HEARTBEAT_CFG)	configuration_heading "Confirm MySQL Heartbeat"
            PLOG_INFO "(MySQL) Local IP Address             = `GetMysqlLocalIP`" $LINENO
			PLOG_INFO "(MySQL) Mate IP Address              = `GetMysqlMateIP`" $LINENO
			PLOG_INFO "(MySQL) Local Hostname               = `GetMysqlLocalHostname`" $LINENO
 			PLOG_INFO "(MySQL) Mate Hostname                = `GetMysqlMateHostname`" $LINENO
			PLOG_INFO "(MySQL) HA Mode 	             = `GetHAMode`" $LINENO
			PLOG_INFO "(MySQL) Virtual IP	             = `GetVirtualIP`" $LINENO
			PLOG_INFO "(MySQL) Interface Name for virtual IP= `GetEthernet`" $LINENO
			PLOG_INFO "(MySQL) Broadcast Address            = `GetBroadcastAddress`" $LINENO
			PLOG_INFO "(MySQL) Subnet Mask Prefix length    = `GetSubNetMaskPrefixLen`" $LINENO

				;;
        $ALARM_CFG)	configuration_heading "Confirm Alarm"
            i=1
            for ip in "${TrapSinkIP[@]}"
            do
                PLOG_DEBUG "Trap Sink IP$i = $ip " $LINENO
                i=$((i + 1))
            done
   
				;;
        $NTP_CFG)	configuration_heading "Confirm NTP"
			PLOG_INFO "NTP Server IP Address = `GetNtpServerIP`" $LINENO
				;;
 	$RSYNC_CFG) 	configuration_heading "Confirm File Sync"
			PLOG_INFO "Remote Node Username = `GetRemoteNodeUsername`" $LINENO
			PLOG_INFO "Remote Node IP	     = `GetRemoteNodeIP`" $LINENO
			;;
    	*)			;; 
    esac

    echo ""

}

function yes_no_check()
{
    default=$2	
    read -e -i "$default" -p "$1" ch
    actualvalue=${ch:-$default}
    while [ "`echo "$ch"|tr '[:upper:]' '[:lower:]'`" != "yes" ] &&  [ "`echo "$ch"|tr '[:upper:]' '[:lower:]'`" != "no" ] || [ -z "$ch" ]
    do
	read -e -i "$default" -p "$1" ch
	actualvalue=${ch:-$default}
    done    
    
    echo "$actualvalue"|tr '[:upper:]' '[:lower:]'

}



#confirm set of inputs by a user
function confirm_inputs()
{
    local RET=0
    case $1 in
        $BONDING_CFG) display_inputs $1
                    choice=`yes_no_check "Enter \"yes\" to confirm, \"no\" to re-configure : "`
				;;
        $LOCALHOST_CFG)display_inputs $1
                    choice=`yes_no_check "Enter \"yes\" to confirm, \"no\" to re-configure : "`
				          ;;
        $MYSQL_CFG)	display_inputs $1
                    choice=`yes_no_check "Enter \"yes\" to confirm, \"no\" to re-configure : "`
		                ;;
        $SIGTRAN_CFG)	display_inputs $1
                    choice=`yes_no_check "Enter \"yes\" to confirm, \"no\" to re-configure : "`
		                ;;
        $TIPC_CFG)	display_inputs $1
                    choice=`yes_no_check "Enter \"yes\" to confirm, \"no\" to re-configure : "`
        			;;
        $HEARTBEAT_CFG)	display_inputs $1
                    choice=`yes_no_check "Enter \"yes\" to confirm, \"no\" to re-configure : "`
       
		    		;;
        $ALARM_CFG)	display_inputs $1
                    choice=`yes_no_check "Enter \"yes\" to confirm, \"no\" to re-configure : "`
			    	;;
        $NTP_CFG)	display_inputs $1
                    choice=`yes_no_check "Enter \"yes\" to confirm, \"no\" to re-configure : "`
		    		;;
        $RSYNC_CFG) 	display_inputs $1
                    choice=`yes_no_check "Enter \"yes\" to confirm, \"no\" to re-configure : "`
			
				;;
    	*)			;; 
    esac
    
    if [ "$choice" == "yes" ];then
        RET=0
    elif [ "$choice" == "no" ];then
        RET=1
    fi


    return $RET
}

#IP Address Validation functions
function ipv6_cidr_validation()
{
	CIDR=$1

	IP_ADD=`echo $CIDR | cut -d "/" -f 1`
	BIT_MASK=`echo $CIDR | cut -d "/" -f 2`

	/bin/ipcalc -cs $CIDR -6

	if [ $? -ne 0 ]
	then
		echo "false"
		return
	fi

	if [ "$BIT_MASK" -lt 0 ]
	then
		echo "false"
		return 
	fi

	if [ "$BIT_MASK" -gt 128 ]
	then
		echo "false"
		return
	fi

	echo "true"
	return 
}

function ipv4_check()
{
	tmp=""

	read -p "$1" as
	tmp=`ipv4_cidr_validation $as`

	if [ "$tmp" = "false" ]
	then
			tmp=""
	fi
    
    while [ -z $tmp ]
	do
		read -p "$2" as

		tmp=`ipv4_cidr_validation $as`

		if [ "$tmp" = "false" ]
		then
			tmp=""
		fi
	done
	echo $as
}

function ipv4_validation()
{
    /bin/ipcalc -cs "$1"
    if [ $? -eq 0 ];then
        echo "true"
    else
	echo "false"
    fi

}

function validate_ip()
{
    
    read -p "$1" as

    /bin/ipcalc -cs "$as"
    
    while [ $? -ne 0 ]
    do
        read -p "$2" as
        ipcalc -cs "$as"
    done
    
    echo "$as"


}

function spl_validate_ip()
{
     
    read -p "$1" as
    if [ -z "$as" ];then
	echo "NULL"
	return
    fi

    /bin/ipcalc -cs "$as"
    
    while [ $? -ne 0 ]
    do
        read -p "$2" as
        if [ -z "$as" ];then
	    echo "NULL"
	    return
        fi

        ipcalc -cs "$as"
    done
    
    echo "$as"


}


function ipv4_cidr_validation()
{
	CIDR=$1

    echo "$1"|grep "/" >/dev/null
    if [ "$?" -ne 0 ];then
        echo "false"
        return
    fi
	IP_ADD=`echo $CIDR | cut -d "/" -f 1`
	BIT_MASK=`echo $CIDR | cut -d "/" -f 2`

	/bin/ipcalc -cs $CIDR -4

	if [ $? -ne 0 ]
	then
		echo "false"
		return
	fi
    
    if [ -z "$BIT_MASK" ];then
        echo "false"
        return
    fi

	if [ "$BIT_MASK" -lt 0 ]
	then
		echo "false"
		return 
	fi

	if [ "$BIT_MASK" -gt 32 ]
	then
		echo "false"
		return
	fi

	echo "true"
	return 
}



function convert_cidrip_to_sed_cirdrip()
{
     virtualip=$1
     IP=`echo $virtualip | cut -d "/" -f 1`
     SUBNET=`echo $virtualip | cut -d "/" -f 2`
     echo $IP"\\/"$SUBNET
     return
}

function check_env()
{
    if [ -z "$ISS7_CONFIG_DIR" ];then
	PLOG_INFO "Could not load environment variables" $LINENO
	PLOG_INFO "Open a new terminal or bash and try again" $LINENO
	exit
    fi   

}

function revert_crontab_cfg()
{
     sed -i /dre_logrotate/d /etc/crontab >/dev/null
     sed -i /run_dre_logrotate.sh/d /etc/crontab >/dev/null
     sed -i /run_dre_console_logrotate.sh/d /etc/crontab >/dev/null
     sed -i /database_dump.sh/d /etc/crontab >/dev/null
     sed -i /tracer.sh/d /etc/crontab >/dev/null
     sed -i /archive_purge.sh/d /etc/crontab >/dev/null
     service crond restart
}

#$1= directory name where heartbeat config are stored
function revert_heartbeat_cfg()
{
	pgrep "heartbeat" >/dev/null
	if [ $? -eq 0 ];then
	    PLOG_DEBUG "Stopping heartbeat" $LINENO
	    kill_heartbeat &
	    service heartbeat stop
	fi
	LOG_DEBUG "Path of heartbeat config pasded=$1" $LINENO
	/bin/cp -f "$1/ha.cf" /etc/ha.d/.	
	/bin/cp -f "$1/authkeys" /etc/ha.d/.	
	/bin/cp -f "$1/haresources" /etc/ha.d/.	
}

function revert_mysql_replication_cfg()
{

	local ip=`GetMysqlIpAddress`
	local username=`GetMysqlUsername`
	local password=`GetMysqlPassword`
	local port=`GetMysqlPort`
	local flag=0
	pgrep "mysqld" >/dev/null
	if [ $? -ne 0 ];then
            start mysqld
	    check_mysql
	    flag=1
	fi

	my="mysql  --host=$ip --user=$username --password=$password --port=$port -se"

	${my} "STOP SLAVE;" >/dev/null 2>&1
	${my} "CHANGE MASTER TO MASTER_HOST=' ', MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';" >/dev/null 2>&1
	${my} "RESET MASTER;" >/dev/null 2>&1
	if [ "$flag" == "1" ];then
        stop mysqld
	fi
	local value=`grep "^server-id" $MYSQL_CNFPATH`
    	/bin/sed -i "s/^server-id.*/#$value/g"  $MYSQL_CNFPATH
	local value=`grep "^log-bin" $MYSQL_CNFPATH`
    	/bin/sed -i "s/^log-bin.*/#$value/g"  $MYSQL_CNFPATH
	local value=`grep "^slave-skip-error" $MYSQL_CNFPATH`
    	/bin/sed -i "s/^slave-skip-error.*/#$value/g"  $MYSQL_CNFPATH
	local value=`grep "^relay-log" $MYSQL_CNFPATH`
    	/bin/sed -i "s/^relay-log.*/#$value/g"  $MYSQL_CNFPATH

}

# Checks and starts mysql, set the triggers and install functions for the triggers
#and call memc_servers_set , Should be called only once after restarting mysql
function memc_servers_set()
{
    local ip=`GetMysqlIpAddress`
    local username=`GetMysqlUsername`
    local password=`GetMysqlPassword`
    local port=`GetMysqlPort`
    local flag=0
    my="mysql  --host=$ip --user=$username --password=$password --port=$port -se"
    my1="mysql  --host=$ip --user=$username --password=$password --port=$port "

    netstat -anp|grep "50000"|grep "mysqld"|grep "ESTABLISHED"  >/dev/null
    if [ $? -ne 0 ];then
	LOG_DEBUG "connecting mysql to memcached..." $LINENO
        check_and_start_mysql
        if [ $S_PRODUCT_NAME = "dre" ];then
            ${my1} < /opt/diametriq/${S_PRODUCT_NAME}/scripts/install_functions.sql
            ${my1} < /opt/diametriq/${S_PRODUCT_NAME}/scripts/trigger_fun.sql
        fi
    fi


}


#configures https for webgui this is called by post_rpm function
function configure_webgui_https()
{
    local APACHE_CONF_PATH=/opt/apache-tomcat/conf
    #if drekey already is copied return without doing anything
    if [ -e $APACHE_CONF_PATH/drekey ];then
        LOG_INFO "Https is already configured for WebGui" $LINENO
        return
    fi

    PLOG_INFO "Configuring HTTPS for Web-GUI..." $LINENO
    LOG_DEBUG "Copying ${S_PRODUCT_NAME} key..." $LINENO
    #copy drekey to /opt/apache-tomcat/conf
    cp /opt/diametriq/${S_PRODUCT_NAME}/WEB-GUI/drekey $APACHE_CONF_PATH

    LOG_DEBUG "backup /opt/apache-tomcat/conf/server.xml" $LINENO
    #take backup of /opt/apache-tomcat/conf/server.xml
    cp $APACHE_CONF_PATH/server.xml $APACHE_CONF_PATH/server.xmlbk

    LOG_DEBUG "commenting lines..." $LINENO
    #commenting  lines
    sed -i "s/<Listener className=\"org.apache.catalina.core.AprLifecycleListener\" SSLEngine=\"on\" *\/>/<\!--Listener className=\"org.apache.catalina.core.AprLifecycleListener\" SSLEngine=\"on\"-->/g" $APACHE_CONF_PATH/server.xml


    sed -i "s/<Connector port=\"8009\" protocol=\"AJP\/1.3\" redirectPort=\"8443\" *\/>/<\!--Connector port=\"8009\" protocol=\"AJP\/1.3\"redirectPort=\"8443\"-->/g" $APACHE_CONF_PATH/server.xml

    #add the following line
    sed -i "s/<\/Service>/<Connector port=\"8443\" protocol=\"org.apache.coyote.http11.Http11Protocol\" SSLEnabled=\"true\" maxThreads=\"150\" scheme=\"https\" secure=\"true\" keystoreFile=\"\/opt\/apache-tomcat\/conf\/drekey\" keystorePass=\"diametriq@123\" clientAuth=\"false\" sslProtocol=\"TLS\" \/>\n <\/Service>/g" $APACHE_CONF_PATH/server.xml
    
    #restart apache-tomcat
    ps -eaf|grep apache-tomcat|grep -v "grep" >/dev/null
    if [ $? -ne 0 ];then
	LOG_DEBUG "apache-tomcat not running.starting it..." $LINENO
        start_apache_tomcat
    else
	LOG_DEBUG "Restarting apache-tomcat" $LINENO
	stop apache-tomcat
    start_apache_tomcat
    fi 

}


##########################################################################
####     BONDING RELATED FUNCTIONS                      #############
########################################################################
#array to hold the bond names
declare -a bond_name
#array to hold the bond ips
declare -a bond_ip
#array to hold the netmasks
declare -a bond_netmask
#array to hold the interfaces(comma seperated)
declare -a bond_nics
#array to hold bond ips in cidr format
declare -a bond_cidr_ip

#deletes the old bonding  configuration from /etc/${S_PRODUCT_NAME}.cfg
function delete_bonding_in_dre_cfg()
{
    sed -i /BondName/d $DRE_CONFIG
    sed -i /IP_/d $DRE_CONFIG
    sed -i /Netmask_/d $DRE_CONFIG
    sed -i /NoOfInterfaces/d $DRE_CONFIG
    sed -i /Interface[1-9]_/d $DRE_CONFIG
    sed -i /DefaultGatewayIP/d $DRE_CONFIG

}


#updates the ${S_PRODUCT_NAME}.cfg with the input from user either parsed from user.cnf or console input 
function update_bonding_in_dre_cfg()
{
    declare -a INTERFACE_LIST
    len=${#bond_name[@]}
    LOG_DEBUG "NoOfBonds=$len" $LINENO
    if [ "$len" == "0" ];then
	set_dre_cfg "Bonding" "no"
        set_dre_cfg "NoOfBonds" "$len"
	return 1
    else
	set_dre_cfg "Bonding" "yes"
        set_dre_cfg "NoOfBonds" "$len"
    fi


    for (( i=0; i<${len}; i++ ));
    do
	BOND_NAME=${bond_name[$i]}
        BOND_IP=${bond_ip[$i]}
	BOND_NETMASK=${bond_netmask[$i]}
	BOND_NICS=${bond_nics[$i]}
	BOND_CIDR_IP=${bond_cidr_ip[$i]}
	LOG_DEBUG "`echo $BOND_NICS|tr "," " "`" $LINENO
	set_dre_cfg "BondName$(($i+1))" "$BOND_NAME"
        set_dre_cfg "IP_$BOND_NAME" "$BOND_IP"
	set_dre_cfg "Netmask_$BOND_NAME" "$BOND_NETMASK"
	set_dre_cfg "Cidr_IP_$BOND_NAME" "$BOND_CIDR_IP" 	
        j=1
	LOG_DEBUG "Len=__ $k" $LINENO
        INTERFACE_LIST=(`echo $BOND_NICS|tr "," " "`)
	k=1
	for name in "${INTERFACE_LIST[@]}"
	do
	    #INTERFACE_LIST[$k]=$name
	    LOG_DEBUG "--$name" $LINENO
	    tmp="Interface$k"
	    LOG_DEBUG "tmp =$tmp" $LINENO
	    tmp+="_$BOND_NAME"
	    LOG_DEBUG "tmp =$tmp" $LINENO
	    set_dre_cfg "$tmp" "$name"
            LOG_DEBUG "--k=$k" $LINENO
	    k=$(($k+1))
	done

	set_dre_cfg "NoOfInterfaces_$BOND_NAME" "$(($k-1))"
	unset k
	LOG_INFO "BondName=${bond_name[$i]}" $LINENO
	LOG_INFO "BondIp=${bond_ip[$i]}" $LINENO
	LOG_INFO "BondMask=${bond_netmask[$i]}" $LINENO
	LOG_INFO "BondNics=${bond_nics[$i]}" $LINENO
	
	unset INTERFACE_LIST
    done


}

#gets the inputs related to bonding configuration
function configure_ethernet_bonding()
{
    n='
'
    pgrep NetworkManager >/dev/null
    if [ $? -eq 0 ];then
	service NetworkManager stop >/dev/null
    fi
    chkconfig --list|grep "NetworkManager" >>/var/log/${S_PRODUCT_NAME}/package.log
    if [ $? -eq 0 ];then 
        chkconfig NetworkManager off
    fi

    #variable to keep track of number of bonding interfaces
    choice="no" #default value
    if [ ! -z $DRE_CNF_FILE ];then
	#check if bonding is set to "no", if so return
	if [ "$bonding" != "yes" ]; then
	    LOG_DEBUG "Bonding is set to no , so returning" $LINENO
	    return
	fi
        choice="yes"
    fi
    while [ "$choice" == "no" ]
    do    
    configuration_heading "Ethernet bonding"
    local i=0;
    while [ 1 ]
    do
        if [ "$i" == 0 ];then
            ch1=`yes_no_check            "Do you want to configure ethernet bonding?:[yes/no]              :" "no"`
        else
            ch1=`yes_no_check            "Do you want to configure another bonded interface?:[yes/no]      :" "no"`
        fi
        if [ "$ch1" == "yes" ];then
            if [ "$i" == "0" ];then
                BOND_NAME=`null_check   $'Enter the bond name                                              :' $'Enter the bond name(Should not be null)        :' "bond0"`
	    elif [ "$i" == "1" ];then
                BOND_NAME=`null_check   $'Enter the bond name                                              :' $'Enter the bond name(Should not be null):' "bond1"`
	    else
                BOND_NAME=`null_check   $'Enter the bond name                                              :' $'Enter the bond name(Should not be null):'`
            fi
            BOND_IP_CIDR=`ipv4_check    $'Enter the Default IP for "'$BOND_NAME'" in CIDR notation(a.b.c.d/x)     :' $'Enter the Default IP for '$BOND_NAME' in CIDR notation(a.b.c.d/x)(Enter valid IP) :'`
            #calculate Netmask from the entered bond ip that is in cidr notation
            BOND_NETMASK=`ipcalc -m $BOND_IP_CIDR|cut -d'=' -f2`   
            #extract only IP from CIDR notation
            BOND_IP=`echo $BOND_IP_CIDR|cut -d'/' -f1`
    
            NUM_INT=`num_check          $'How many ethernet interfaces do you want to associate for "'$BOND_NAME'":' \
            $'Invalid entry!\nHow many ethernet interfaces do you want to associate for "'$BOND_NAME'":' "2"` 

            #variable to keep track of number of interfaces per bond
            local j=0
            INTERFACES_PER_BOND=""
            #based on the number of interfaces get the interfaces  
       
            while [ $j -lt $NUM_INT ]
            do
                case "$j" in
                *) INT_NAME=`null_check $'Enter Ethernet device name of  NIC-'$(($j+1))' for '$BOND_NAME':' \
		        $'Invalid entry!\nEnter Ethernet device name of NIC-'$(($j+1))' for '$BOND_NAME':'` 
		    ;;
                esac
                if [ "$j" == "0" ];then
                    INTERFACES_PER_BOND="$INT_NAME"
                else
                    INTERFACES_PER_BOND="$INTERFACES_PER_BOND,$INT_NAME" 
                fi
                j=$(($j+1))
            done

            bond_name[$i]=$BOND_NAME
            bond_ip[$i]=$BOND_IP
            bond_netmask[$i]=$BOND_NETMASK
            bond_nics[$i]=$INTERFACES_PER_BOND
	    bond_cidr_ip[$i]=$BOND_IP_CIDR
        else
            
            LOG_DEBUG "return if 0 else configure" $LINENO
            if [ "$i" == "0" ];then
	        return
	    else
	        break
	    fi
    
        fi
        i=$(($i+1))
    done
    if [ $i -ne 0 ];then
        confirm_inputs $BONDING_CFG
        if [ $? -eq 0 ];then
            choice="yes"
        else
	        unset bond_name
	        unset bond_ip
	        unset bond_netmask
	        unset bond_nics
	        unset bond_cidr_ip
            
        fi
    else
	LOG_DEBUG "return if 0 else configure" $LINENO
	return
    fi
    done #main confirmation loop
    #populate the /etc/${S_PRODUCT_NAME}.cfg configuration file based on the inputs from the parsed user input file
    delete_bonding_in_dre_cfg
    update_bonding_in_dre_cfg

    #call the ip bonding script which will configure ethernet bonding
    BOND_PATH=/tmp
    $BOND_PATH/ip-bond.sh
    lsmod|grep tipc >/dev/null
    if [ $? -eq 0 ];then
	LOG_INFO "TIPC Module found so enabling bearer after bonding configuration" $LINENO
        if [ -n "`GetBearerName`" ];then
            tipc-config -be `GetBearerName`
        fi
    fi
}

#function to parse,validate the configurations required to convert standalone
#to HA mode
function parse_validate_cnf_for_HA()
{
    if [ $# -lt 1 ] || [ $# -gt 2 ];then
        LOG_ERROR "file shoud be passed as argument/Invalid Arguments" $LINENO
        exit 1
    else
        if [ ! -e "$1" ];then
            PLOG_ERROR "Invalid file: $1" $LINENO
            exit 1
        fi
            
    fi
    LOG_DEBUG "CNF File passed: `cat $1`" $LINENO 
    
    DRE_CNF_FILE="$1"

    parse_install_mode
    parse_bonding_from_user_cnf
    parse_tipc_cnf 
    parse_localhost_cnf 
    parse_mysql_heartbeat_cnf

    validate_install_mode_cnf
    validate_bonding
    validate_tipc_cnf
    validate_localhost_cnf
    validate_mysql_heartbeat_cnf
 

    update_install_mode_in_dre_cfg
    update_bonding_in_dre_cfg
    update_tipc_in_dre_cfg
    update_localhost_in_dre_cfg
    update_mysql_heartbeat_in_dre_cfg
     
}


#this function parses all the bonding related configuration from the 
#user_dre_cnf ie the configuration file or the input file passed by the user
#for installation

function parse_bonding_from_user_cnf()
{
    #parse all the configurations and store into the arrays defined for bonding


    #check if bonding configuration is enabled
    if [ "`get_dre_cnf_val "bonding"`" == "yes" ];then
	    LOG_DEBUG "bonding=yes" $LINENO
	    bonding="yes"
    else
	    LOG_DEBUG "bonding=no" $LINENO
	    return
    fi
    #if yes get the number of bonds
    local no_of_bonds=` cat $DRE_CNF_FILE |grep "^ip_"|grep -v "ip_address"|wc -l`
    #get the bondnames and store it in the bond_name array
    local bonds=`cat $DRE_CNF_FILE |grep "^ip_"|grep -v "ip_address"|cut -d'_' -f2|cut -d'=' -f1|tr "\n" " "`
    #get the bond ip addresses and store it in the bond_ip array
    local i=0
    for bondName in $bonds
    do
	    bond_name[$i]="$bondName"
	    local no_of_interfaces=`cat  $DRE_CNF_FILE|grep "^interface.*$bondName"|wc -l`
	    local interfaces=`cat  $DRE_CNF_FILE|grep "^interface.*$bondName"|cut -d'=' -f2`
	    bond_nics[$i]="$interfaces"
	    bond_ip[$i]=`cat $DRE_CNF_FILE |grep "^ip_$bondName"|cut -d'/' -f1|cut -d'=' -f2`
	    local ip=`cat $DRE_CNF_FILE |grep "^ip_$bondName"|cut -d'=' -f2`
	    bond_netmask[$i]=`ipcalc -m $ip|cut -d'=' -f2`
	    bond_cidr_ip[$i]=$ip
	    i=$(($i+1))
	   
    done
    #get the bond netmasks and store it in the bond_netmask array

    #get the interface names that is associated for each bond and store it in bond_nics array


    #validate the stored configurations

    #populate the /etc/${S_PRODUCT_NAME}.cfg configuration file based on the inputs from the parsed user input file
    delete_bonding_in_dre_cfg
    update_bonding_in_dre_cfg
}

#gets the number of bonds that are configured from /etc/${S_PRODUCT_NAME}.cfg
function GetNoOfBonds()
{
    sed -n s/NoOfBonds=//p $DRE_CONFIG
}

#Gets the value of the field Bonding,which denotes whether bonding is configured from /etc/${S_PRODUCT_NAME}.cfg
function isBondingConfigured()
{
    sed -n s/Bonding=//p $DRE_CONFIG
}

NO_OF_BONDS=`GetNoOfBonds`


#Gets all the bondnames configured from /etc/${S_PRODUCT_NAME}.cfg
function GetBondNames()
{
    cat $DRE_CONFIG |grep "^BondName"|cut -d'=' -f2

}


#gets the IP from /etc/${S_PRODUCT_NAME}.cfg of the bondname passed
#$1=bondname
function GetIPOfBond()
{
    cat $DRE_CONFIG | grep "^IP_$1"|cut -d'=' -f2
}

#gets the interfaces associated with a bond that is passed
#$1 = bondname
function GetInterfacesForBond()
{

    cat $DRE_CONFIG |grep "^Interface[0-9].*$1"|cut -d'=' -f2

}


#gets the netmask from /etc/${S_PRODUCT_NAME}.cfg of the bondname passed
#$1 = bondname
function GetNetmaskOfBond()
{
    cat $DRE_CONFIG |grep "^Netmask_$1"|cut -d'=' -f2

}


#function which is called before upgrading to take backup of bonding conf
function backup_bonding_cfg()
{
    LOG_DEBUG "function backup_bonding starting" $LINENO
    if [ ! -d /opt/diametriq/${S_PRODUCT_NAME} ] || [ -z `rpm -q ${S_PRODUCT_NAME}|grep -v "not installed"|tail -1 2>/dev/null` ] ;then
	LOG_INFO "bonding scripts backup not required.." $LINENO
        return 0
    fi

    local NETWORK_SCRIPTS_PATH=/etc/sysconfig/network-scripts
    local BACKUP_PATH=/opt/diametriq/${S_PRODUCT_NAME}/.syscfg/bonding
    mkdir -p $BACKUP_PATH
    #backup  bonding  cfg only if it exists
    if [ ! -e /sys/class/net/bonding_masters ];then
        LOG_INFO "No bonded interfaces found to backup!" $LINENO
	return 1
    fi
    PLOG_INFO "Backing up bonding cfg..." $LINENO

    local DATE=`date | tr -s " " | tr " " "_"`
    

    BONDS=`cat /sys/class/net/bonding_masters`
    LOG_INFO "Bonds=$BONDS" $LINENO
    mkdir -p $BACKUP_PATH/bond_$DATE
    LOG_DEBUG "Creating $BACKUP_PATH/bond_$DATE" $LINENO
    echo "$BONDS" > $BACKUP_PATH/bond_$DATE/bonds.txt
    for bond in $BONDS
    do

        
        mkdir -p $BACKUP_PATH/bond_$DATE/$bond
        #remove all the slave interfaces associated with bond
        LOG_INFO "Slaves for $bond" $LINENO
        LOG_INFO "`cat /sys/class/net/$bond/bonding/slaves`" $LINENO
        SLAVES=`cat /sys/class/net/$bond/bonding/slaves`
        echo "$SLAVES" > $BACKUP_PATH/bond_$DATE/$bond/slaves.txt
        for slave in $SLAVES
        do
	    #remove or backup ifcfg-<slave>
 	    if [ -e $NETWORK_SCRIPTS_PATH/ifcfg-$slave ];then
                cp $NETWORK_SCRIPTS_PATH/ifcfg-$slave $BACKUP_PATH/bond_$DATE/$bond/
            fi

        done
        

        PLOG_INFO "Backup ifcfg-$bond" $LINENO
        #check if ifcfg-<bondname> exist if yes backup or delete
        if [ -e $NETWORK_SCRIPTS_PATH/ifcfg-$bond ];then
            cp  $NETWORK_SCRIPTS_PATH/ifcfg-$bond  $BACKUP_PATH/bond_$DATE   
        fi
    done
    if [ -e /etc/modprobe.d/bond.conf ];then
	cp /etc/modprobe.d/bond.conf $BACKUP_PATH/bond_$DATE
    fi

}
#function to destroy the bonding configuration
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
	PLOG_INFO "No bonds to found to destroy!" $LINENO
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

#function to restore bonding configurations duriing a rollback
#$1 will be the directory containing configurations which has to be restored
function restore_bonding_cfg()
{
    local NETWORK_SCRIPTS_PATH=/etc/sysconfig/network-scripts
    if [ ! -d $1 ];then
	PLOG_ERROR "$1 does not exist" $LINENO
	return 1
    fi
    BOND_BKP_ROOT=$1 
    cd $BOND_BKP_ROOT 
    local BOND_PATH=`ls -lrt |tail -1|tr -s " "|cut -d' ' -f9`
    LOG_DEBUG "bond path = $BOND_PATH" $LINENO
    if [ ! -d $BOND_PATH ];then
	PLOG_ERROR "$BOND_PATH does not exist" $LINENO
	return 1
    fi
    destroy_bonding_and_backup_cfg
    cd $BOND_PATH

    PLOG_DEBUG "PWD=`pwd`" $LINENO
    if [ ! -e bonds.txt ];then
	PLOG_INFO "No bonds to be restored" $LINENO
	return 0
    else
	if [ -z "`cat bonds.txt`" ];then
	    LOG_INFO "bonds.txt is empty..." $LINENO
	    return 0
	fi
    fi
    cp -f bond.conf /etc/modprobe.d/
    modprobe bonding
    #iterate over all the bonds that need to be restored
    for bond in `cat bonds.txt`
    do
	PLOG_INFO "Restoring $bond..." $LINENO
	cp -f ./ifcfg-$bond $NETWORK_SCRIPTS_PATH 2>/dev/null
	cat /sys/class/net/bonding_masters |grep $bond >/dev/null
	if [ $? -ne 0 ];then
	    echo +$bond > /sys/class/net/bonding_masters
	fi
	for slave in `cat ./$bond/slaves.txt`
	do
	    PLOG_INFO "Restoring $bond:$slave..." $LINENO
	    cp -f ./$bond/ifcfg-$slave $NETWORK_SCRIPTS_PATH 2>/dev/null
	    cat /sys/class/net/$bond/bonding/slaves |grep $slave > /dev/null
	    if [ $? -ne 0 ];then
	        echo +$slave > /sys/class/net/$bond/bonding/slaves
	    fi
	done 
    

    done    
    if [ -n "`GetBearerName`" ];then
        tipc-config -be `GetBearerName`
    fi
    restart_network 
}

#this function will backup of ${S_PRODUCT_NAME} service script and other related cfgs
function backup_dre_sys_cfg()
{
    LOG_DEBUG "Backing up ${S_PRODUCT_NAME} sys cfg files..." $LINENO
    cp -f /etc/profile.d/${S_PRODUCT_NAME}.sh /opt/diametriq/${S_PRODUCT_NAME}/.syscfg
    cp -f /etc/my.cnf /opt/diametriq/${S_PRODUCT_NAME}/.syscfg
    cp -f /etc/sysconfig/${S_PRODUCT_NAME} /opt/diametriq/${S_PRODUCT_NAME}/.syscfg/${S_PRODUCT_NAME}.env
    cp -f /etc/init.d/dre /opt/diametriq/${S_PRODUCT_NAME}/.syscfg
    cp -f /etc/${S_PRODUCT_NAME}.cfg /opt/diametriq/${S_PRODUCT_NAME}/.syscfg

}
#function which is called before upgrade to take backup of heartbeat conf files
function backup_heartbeat_cfg()
{
    LOG_DEBUG "function backup_heartbeat starting" $LINENO
    if [ ! -d /opt/diametriq/${S_PRODUCT_NAME} ] || [ -z `rpm -q ${S_PRODUCT_NAME}|grep -v "not installed"|tail -1 2>/dev/null` ] ;then
	LOG_INFO "Heartbeat scripts backup not required.." $LINENO
        return 0
    fi

    local HEARTBEAT_PATH=/etc/ha.d
    local BACKUP_PATH=/opt/diametriq/${S_PRODUCT_NAME}/.syscfg/heartbeat
    mkdir -p $BACKUP_PATH

    if [ -d $HEARTBEAT_PATH ];then
        PLOG_INFO "Backing up heartbeat cfg..." $LINENO
        cp -rf $HEARTBEAT_PATH/* $BACKUP_PATH  	
    else
	LOG_INFO "No ha.d directory found to backup!" $LINENO
    fi

}

#function to restore heartbeat configurations while rollback
#$1=path where the heartbeat configurations reside which are to be restored
function restore_heartbeat_cfg()
{
    local HEARTBEAT_PATH=/etc/ha.d
    
    if [ ! -d "$1" ];then
	PLOG_ERROR "$1 does not exist" $LINE
	exit 1
    fi
    
    rm -rf $HEARTBEAT_PATH/*
    PLOG_INFO "Restoring heartbeat cfg..." $LINENO
    if [ -d $HEARTBEAT_PATH ];then
	cp -rf $1/* $HEARTBEAT_PATH/
    else
	mkdir -p $HEARTBEAT_PATH
	cp -rf $1/* $HEARTBEAT_PATH/
    fi    

    pgrep "heartbeat" >/dev/null
    if [ $? -eq 0 ];then
	 PLOG_DEBUG "Stopping heartbeat..." $LINENO
	 kill_heartbeat &
	 service heartbeat stop
    fi
    PLOG_DEBUG "Starting heartbeat..." $LINENO

    if [ "`GetDreInstallMode`" == "2" ] || [ "`GetDreInstallMode`" == "3" ] || [ "`GetDreInstallMode`" == "4" ];then
        service heartbeat start
    fi

}

#This function will restore the mysql replication configuration
function restore_mysqlreplication_cfg
{

if [ "`GetDreInstallMode`" == "2" ] || [ "`GetDreInstallMode`" == "3" ] || [ "`GetDreInstallMode`" == "4" ];then
    LOG_DEBUG "Executing mysql_ha.sh as ${S_PRODUCT_NAME} mode =2" $LINENO
    if [ -e /opt/diametriq/${S_PRODUCT_NAME}/scripts/mysql_ha.sh ];then
        check_and_start_mysql
        /opt/diametriq/${S_PRODUCT_NAME}/scripts/mysql_ha.sh --rollback
    fi
else
    LOG_DEBUG "DreMode=1" $LINENO 
    if [ -e /opt/diametriq/${S_PRODUCT_NAME}/bin/querydiametriq ];then
	    LOG_DEBUG "executing stop slave" $LINENO
	    check_and_start_mysql
        /opt/diametriq/${S_PRODUCT_NAME}/bin/querydiametriq "stop slave"
    fi
fi


}

# This function will command the name value pair, which is not required in standalone mode
function command_my_cnf_for_standalone()
{

    if [ "`GetDreInstallMode`" == "1" ];then
        local value=`grep "^server-id" $MYSQL_CNFPATH`
	    /bin/sed -i "s/^server-id.*/#$value/g"  $MYSQL_CNFPATH
        local value=`grep "^log-bin" $MYSQL_CNFPATH`
	    /bin/sed -i "s/^log-bin.*/#$value/g"  $MYSQL_CNFPATH
        local value=`grep "^slave-skip-error" $MYSQL_CNFPATH`
	    /bin/sed -i "s/^slave-skip-error.*/#$value/g"  $MYSQL_CNFPATH
        local value=`grep "^relay-log" $MYSQL_CNFPATH`
	    /bin/sed -i "s/^relay-log.*/#$value/g"  $MYSQL_CNFPATH
    fi


}

# This function will uncommand the name value pair, which is required in active-standby mode
function uncommand_my_cnf_for_activestandby()
{

    if [ "`GetDreInstallMode`" == "2" ] || [ "`GetDreInstallMode`" == "3" ] || [ "`GetDreInstallMode`" == "4" ];then
        local value=`grep "^#server-id" $MYSQL_CNFPATH | tr -d "#"`
	    /bin/sed -i "s/^#server-id.*/$value/g"  $MYSQL_CNFPATH
        local value=`grep "^#log-bin" $MYSQL_CNFPATH | tr -d "#"`
	    /bin/sed -i "s/^#log-bin.*/$value/g"  $MYSQL_CNFPATH
        local value=`grep "^#slave-skip-error" $MYSQL_CNFPATH | tr -d "#"`
	    /bin/sed -i "s/^#slave-skip-error.*/$value/g"  $MYSQL_CNFPATH
        local value=`grep "^#relay-log" $MYSQL_CNFPATH | tr -d "#"`
	    /bin/sed -i "s/^#relay-log.*/$value/g"  $MYSQL_CNFPATH
    fi


}


function config_ip_tables()
{
    LOG_DEBUG "Calling iptables_rules script" $LINENO
    /opt/diametriq/${S_PRODUCT_NAME}/bin/iptables_rules --insert

    #save a copy of the rule for rollback
    cp -f /etc/sysconfig/iptables /opt/diametriq/${S_PRODUCT_NAME}/.syscfg
    cp -f /etc/sysconfig/ip6tables /opt/diametriq/${S_PRODUCT_NAME}/.syscfg


}

#called during uninstall
function revert_iptable_rules()
{
    LOG_DEBUG "Reverting iptable rules" $LINENO
    cp -f /etc/sysconfig/ipv4_default_rules_bkp/iptables /etc/sysconfig
    service iptables restart   
 
    LOG_DEBUG "Reverting ip6table rules" $LINENO
    cp -f /etc/sysconfig/ipv6_default_rules_bkp/ip6tables /etc/sysconfig
    service ip6tables restart

}

#called during rollback to restore the prev ip table rules
#$1 = path from where iprules have to be restored
function restore_iptable_rules()
{
    LOG_DEBUG "Restoring iptable rules" $LINENO
    local process_pid=`ps -elf | grep heartbeat | grep -v grep | grep master | awk '{print $4}'`
    LOG_DEBUG "Heartbeat pid :- $process_pid " $LINENO
    if [ -n "$process_pid" ];then
	LOG_DEBUG "Stopping heartbeat in restore_iptable_rules function" $LINENO
	kill_heartbeat &
        service heartbeat stop
    fi

    if [ -e "$1/iptables" ];then
        cp -f $1/iptables /etc/sysconfig
	service iptables restart
    fi

    LOG_DEBUG "Restoring ip6table rules" $LINENO
    if [ -e "$1/ipt6tables" ];then
	cp -f $1/ip6tables /etc/sysconfig
	service ip6tables restart
    fi
    check_and_stop_mysql
    check_and_start_mysql
    if [ -n "$process_pid" ];then
	LOG_DEBUG "Starting heartbeat in restore_iptable_rules function" $LINENO
	service heartbeat start
    fi 

}

#to avoid heartbeat going into deadlock while stopping(rarely happens) we call kill_heartbeat
#which will wait for 15 seconds and kill
function kill_heartbeat()
{
    local process_pid=`ps -elf | grep heartbeat | grep -v grep | grep master | awk '{print $4}'`
    if [ -z $process_pid ];then
       LOG_DEBUG "heartbeat is not running exiting...." $LINENO
       exit  
    fi

    local count=1;
    while [ 1 ]
    do
        local process_pid1=`ps -elf | grep heartbeat | grep -v grep | grep master | awk '{print $4}'`
        LOG_DEBUG "heartbeat is pid $process_pid1 $process_pid" $LINENO
        if [ -z $process_pid1 ];then
       	    LOG_DEBUG "heartbeat is stopped so exiting...." $LINENO
            exit
        fi
        
        if [ $process_pid1 != $process_pid ];then
       	    LOG_DEBUG "heartbeat pid changed so exiting, assuming that heartbeat restarted...." $LINENO
            exit
        fi
        ((count++))
        sleep 1
        if [ $count == 15 ];then
       	    LOG_DEBUG "Killing heartbeat... count 15 reached" $LINENO
            kill -9 $process_pid
       	    LOG_DEBUG "kill_heartbeat exiting...." $LINENO
            exit
        fi
    done
}



#function to take care of stopping heartbeat before restarting network service
function restart_network()
{
    local process_pid=`ps -elf | grep heartbeat | grep -v grep | grep master | awk '{print $4}'`
    LOG_DEBUG "Heartbeat pid :- $process_pid " $LINENO
    if [ -z $process_pid ];then
        LOG_DEBUG "heartbeat is not running so can safely restart network...." $LINENO
	LOG_DEBUG "Restarting network..." $LINENO
        service network restart
    else
        LOG_DEBUG "heartbeat is running, stopping heartbeat!" $LINENO
        #to avoid heartbeat going into deadlock while stopping(rarely happens) we call kill_heartbeat
	kill_heartbeat &
        service heartbeat stop
	LOG_DEBUG "Restarting network..." $LINENO
        service network restart
	LOG_DEBUG "Starting Heartbeat..." $LINENO
	service heartbeat start
    fi


}

#creates dquser and adds to sudoers for running ${PRODUCT_NAME} service
function create_dre_dquser()
{
    local USER="dquser"
    local PASS="diametriq@123"
    #check if $USER is present
    cat /etc/passwd|grep "$USER" >/dev/null
    if [ $? -ne 0 ];then
        LOG_INFO "Creating $USER..." $LINENO
        #create $USER
        useradd $USER
        #set the password
        echo "$PASS"|passwd $USER --stdin
        LOG_INFO "Adding $USER to sudoers for running ${PRODUCT_NAME} service" $LINENO
        #now add the $USER to the sudoers and give permissions to run ${PRODUCT_NAME} services
        sed -i /$USER/d /etc/sudoers
        echo "$USER  ALL=/sbin/service ${S_PRODUCT_NAME} start,/sbin/service ${S_PRODUCT_NAME} stop,/sbin/service ${S_PRODUCT_NAME} restart,/sbin/service ${S_PRODUCT_NAME} status" >>/etc/sudoers

    else
        LOG_INFO  "\"dquser\"  already exists for ${PRODUCT_NAME} service" $LINENO
    fi


}

#create Nonroot user "dquser" for MySQL
function create_mysql_dquser()
{
    local USER="dquser"
    local PASS="diametriq@123"
    local ROOT_P="`GetMysqlPassword`"
    LOG_DEBUG "Create MySQL Non-Root User \"dquser\"" $LINENO
    LOG_DEBUG "----Begin create_mysql_dquser----: `cat /etc/${S_PRODUCT_NAME}.cfg`" $LINENO 
    #if mysql non-root user is not created, create non-root user called "dquser" and give appropriate permissions
    if [ "`GetMysqlUsername`" == "root" ];then
        PLOG_INFO "Creating Non-root MySQL user \"dquser\"..." $LINENO
	#disable the replication
	mysql -uroot -p$ROOT_P -se "set @@global.sql_log_bin=0"
	mysql -uroot -p$ROOT_P -se "set @@session.sql_log_bin=0"
        #mysql -uroot -p$ROOT_P -se "DROP USER '$USER'@'localhost'" 2>/dev/null
	mysql -uroot -p$ROOT_P -se "SELECT 1 FROM mysql.user WHERE user = '$USER';"| grep 1
	if [ $? -ne 0 ];then
        	mysql -uroot -p$ROOT_P -se "CREATE USER '$USER'@'localhost' IDENTIFIED BY '$PASS';"
        	mysql -uroot -p$ROOT_P -se "GRANT CREATE,RELOAD,EXECUTE,GRANT OPTION,LOCK TABLES,DROP,REFERENCES,ALTER,DELETE,INDEX,INSERT,SELECT,UPDATE,TRIGGER,ALTER ROUTINE,CREATE ROUTINE,CREATE USER,REPLICATION CLIENT,REPLICATION SLAVE,REFERENCES,SUPER ON *.* TO \"$USER\"@\"%\" IDENTIFIED BY '$PASS';"
        	mysql -uroot -p$ROOT_P -se "GRANT CREATE,RELOAD,EXECUTE,GRANT OPTION,LOCK TABLES,DROP,REFERENCES,ALTER,DELETE,INDEX,INSERT,SELECT,UPDATE,TRIGGER,ALTER ROUTINE,CREATE ROUTINE,CREATE USER,REPLICATION CLIENT,REPLICATION SLAVE,REFERENCES,SUPER ON *.* TO \"$USER\"@'localhost' IDENTIFIED BY '$PASS';"
	fi
        #####################
        #This block of code is executed when upgrading in HA machine,This is used to add Non-Root MySQL "dquser" in the peer node
        if [ "`GetDreInstallMode`" == "2" ] || [ "`GetDreInstallMode`" == "3" ] || [ "`GetDreInstallMode`" == "4" ];then
	    local mate_mysql_ip="`GetMysqlMateIP`"
            if [ "`get_cur_dre_version`" != "null" ]; then
		#disable replication in the mate mysql
    		mysql -uroot -p$ROOT_P -h $mate_mysql_ip -se "set @@global.sql_log_bin=0"
    		mysql -uroot -p$ROOT_P -h $mate_mysql_ip -se "set @@session.sql_log_bin=0"
       	        #mysql -uroot -p$ROOT_P -h $mate_mysql_ip -se "DROP USER '$USER'@'localhost'" 2>/dev/null
		mysql -uroot -p$ROOT_P -h $mate_mysql_ip -se "SELECT 1 FROM mysql.user WHERE user = '$USER';"| grep 1
		if [ $? -ne 0 ];then
    	        	mysql -uroot -p$ROOT_P -h $mate_mysql_ip -se "CREATE USER '$USER'@'localhost' IDENTIFIED BY '$PASS';" 2>/dev/null
    	        	mysql -uroot -p$ROOT_P -h $mate_mysql_ip -se "GRANT CREATE,RELOAD,EXECUTE,GRANT OPTION,LOCK TABLES,DROP,REFERENCES,ALTER,DELETE,INDEX,INSERT,SELECT,UPDATE,TRIGGER,ALTER ROUTINE,CREATE ROUTINE,CREATE USER,REPLICATION CLIENT,REPLICATION SLAVE,REFERENCES,SUPER ON *.* TO \"$USER\"@\"%\" IDENTIFIED BY '$PASS';"  2>/dev/null
    	        	mysql -uroot -p$ROOT_P -h $mate_mysql_ip -se "GRANT CREATE,RELOAD,EXECUTE,GRANT OPTION,LOCK TABLES,DROP,REFERENCES,ALTER,DELETE,INDEX,INSERT,SELECT,UPDATE,TRIGGER,ALTER ROUTINE,CREATE ROUTINE,CREATE USER,REPLICATION CLIENT,REPLICATION SLAVE,REFERENCES,SUPER ON *.* TO \"$USER\"@'localhost' IDENTIFIED BY '$PASS';"  2>/dev/null
    			mysql -uroot -p$ROOT_P -h $mate_mysql_ip mysql -se "update user set Select_priv='Y', Insert_priv='Y', Update_priv='Y', Delete_priv='Y', Create_priv='Y', Drop_priv='Y', Reload_priv='Y',Grant_priv='Y', References_priv='Y', Index_priv='Y', Alter_priv='Y', Super_priv='Y', Lock_tables_priv='Y', Execute_priv='Y', Repl_slave_priv='Y', Repl_client_priv='Y', Create_routine_priv='Y', Alter_routine_priv='Y', Create_user_priv='Y', Trigger_priv='Y' where Host='localhost' and User='dquser' "
		fi
		#enable replication in the mate mysql
    		mysql -uroot -p$ROOT_P -h $mate_mysql_ip -se "flush privileges"
    		mysql -uroot -p$ROOT_P -h $mate_mysql_ip -se "set @@global.sql_log_bin=1"
    		mysql -uroot -p$ROOT_P -h $mate_mysql_ip -se "set @@session.sql_log_bin=1"
            fi
        fi
    #####################
        #enable replication
    	mysql -uroot -p$ROOT_P -se "flush privileges"
    	mysql -uroot -p$ROOT_P -se "set @@global.sql_log_bin=1"
    	mysql -uroot -p$ROOT_P -se "set @@session.sql_log_bin=1"
    #update the /etc/${S_PRODUCT_NAME}.cfg with the new mysql nonroot user "dquser" and its password
        if [ "`check_if_config_exist "MysqlUsername"`" == 1 ];then
            sed -i "s/MysqlUsername.*/MysqlUsername=$USER/g" $DRE_CONFIG
        else
            echo "MysqlUsername=$USER" >> $DRE_CONFIG
        fi

        if [ "`check_if_config_exist "MysqlPassword"`" == 1 ];then
            sed -i "s/MysqlPassword.*/MysqlPassword=$PASS/g" $DRE_CONFIG
        else
            echo "MysqlPassword=$PASS" >> $DRE_CONFIG
        fi
        LOG_DEBUG "----After updating ----: `cat /etc/${S_PRODUCT_NAME}.cfg`" $LINENO
    fi

    
}


function start_apache_tomcat()
{
    if [ "$PRODUCT" == "iwf" ];then
        return 0
    fi
    RETRIES=0
    #apache-tomcat
    ps -eaf|grep apache-tomcat|grep -v "grep" >/dev/null
    if [ $? -ne 0 ];then
	LOG_DEBUG "apache-tomcat not running.starting it..." $LINENO
	start apache-tomcat
    fi

    for (( RETRIES=0; RETRIES<3; RETRIES++ ));
    do
        check_apache_tomcat
        if [ $? -ne 0 ];then
            stop apache-tomcat
            start apache-tomcat
            continue
        else
            local OUTPUT=`curl -Is http://127.0.0.1:8080/DRE/|head -n 1`
            echo $OUTPUT | grep "200.*OK"
            if [ $? -ne 0 ];then
                PLOG_WARNING "Failed to deploy ${PRODUCT_NAME} web-application, retrying..." $LINENO
                stop apache-tomcat
                start apache-tomcat
                continue
            else
                break
            fi
        fi
    done
   
    if [ $RETRIES -eq 3 ];then
        PLOG_CRITICAL "Failed to deploy ${PRODUCT_NAME} web-application" $LINENO
    fi
}

########################################
#### couchbase related functions  ######
########################################

buckets="DiameterSession SessionBindingMap IPV4CalledStationIdMap IPV6CalledStationIdMap"
CB_LOGS=/etc/.${PRODUCT}/cb_logs
#function to decide the ram allocation for couchbase
function calculate_ram_for_couchbase()
{
    ram_available=`cat /proc/meminfo |grep MemTotal|tr -s " "|cut -d' ' -f2`
    ram_available=$(($ram_available/1024))
    #if ram size for couchbase passed in user dre cnf 
    if [ -z "$ram_size" ];then
        ram_size=$(expr $ram_available / 3|bc)
    fi
    diameter_session_bucket_ram=$(expr $ram_size / 2|bc)
    other_bucket_ram=$(expr $diameter_session_bucket_ram / 3|bc)
}

function create_buckets()
{
    local IP=`GetMysqlLocalIP`
    local PORT=8091
    local ADMIN_NAME="dquser"
    local ADMIN_PASS="diametriq@123"
    local BUCKET_PASS="diametriq@123"
    #delete buckets before creating them
    delete_buckets

    for i in $buckets
    do 
	#for DiameterSession bucket allocate 50% and for other buckets allocate the other 50%
	if [ "$i" == "DiameterSession" ];then
	    op=`curl -v -u $ADMIN_NAME:$ADMIN_PASS -d name=$i -d ramQuotaMB=$diameter_session_bucket_ram -d authType=sasl -d replicaNumber=1 -d saslPassword=$BUCKET_PASS -d threadsNumber=8 $IP:$PORT/pools/default/buckets 2>&1`
	else
	    op=`curl -v -u $ADMIN_NAME:$ADMIN_PASS -d name=$i -d ramQuotaMB=$other_bucket_ram -d authType=sasl -d replicaNumber=1 -d saslPassword=$BUCKET_PASS -d threadsNumber=8 $IP:$PORT/pools/default/buckets 2>&1`
	fi
	handle_curl_error "$op"
	if [ $? -ne 0 ];then
	    PLOG_ERROR "Creation of bucket $i failed" $LINENO
	else
	    PLOG_DEBUG "Successfully created bucket $i" $LINENO
	fi

    done


}

#return 0 in case of success else return 1
#$1 is the status returned by curl
function handle_curl_error()
{
    
    
    echo $1  |tr "\r" " "|grep "200.*OK" >/dev/null 
    if [ $? -eq 0 ];then
	return 0
    else
	echo $1|tr "\r" " "|grep "202" >/dev/null
	if [ $? -eq 0 ];then
	    return 0
	else
	    #if bucket deletion is still on going return success
	    echo $1|tr "\r" " "|grep "Bucket deletion not yet complete, but will continue" >/dev/null
	    if [ $? -eq 0 ];then
		LOG_INFO "Bucket deletetion in progress..." $LINENO
		return 0
	    else
	        return 1
	    fi
	fi
    fi 

}


function delete_buckets()
{
    local IP=`GetMysqlLocalIP`
    local PORT=8091
    local ADMIN_NAME="dquser"
    local ADMIN_PASS="diametriq@123"
    #get the bucket list from the server and delete those
    local bucket_list=`/opt/couchbase/bin/couchbase-cli  bucket-list -c $IP:$PORT -u $ADMIN_NAME -p $ADMIN_PASS|grep -v " "`
    LOG_DEBUG "DELETE $bucket_list" $LINENO
    for i in $bucket_list
    do
        op=`curl -v -X DELETE -u $ADMIN_NAME:$ADMIN_PASS $IP:$PORT/pools/default/buckets/$i 2>&1`
	handle_curl_error "$op"
	if [ $? -ne 0 ];then
	    PLOG_ERROR "Deletion of $i failed!" $LINENO
	    LOG_ERROR "$op" $LINENO
	else
	    PLOG_DEBUG "Successfully deleted bucket $i" $LINENO
	fi

    done
}

#this will update the /opt/diametriq/dre/config/couchbase.cfg file with the details
# $1= name $2 = value
function update_couchbase_cfg()
{
    COUCHBASE_CFG=/opt/diametriq/${PRODUCT}/config/couchbase.cfg
    if [ ! -e $COUCHBASE_CFG ];then
	touch $COUCHBASE_CFG
    fi
    LOG_DEBUG "update_couchbase_cfg $1=$2" $LINENO
    grep "$1" $COUCHBASE_CFG  >/dev/null 2>&1
    if [ $? -eq 0 ];then
        sed -i "s/^$1=.*/$1=$2/g" $COUCHBASE_CFG
    else
        echo "$1=$2" >> $COUCHBASE_CFG 
        #append the value
    fi
}



function configure_couchbase() 
{
    local IP=`GetMysqlLocalIP`
    local PORT=8091
    local ADMIN_NAME="dquser"
    local ADMIN_PASS="diametriq@123"
    local RAM_SIZE=$ram_size
    local MATE_HOSTNAME=`GetMysqlMateHostname`
    local MATE_IP=`GetMysqlMateIP`
    local CLI=/opt/couchbase/couchbase/bin/couchbase-cli
    local DATA_PATH=/opt/couchbase/var/lib/couchbase/data
    #initialize the cluster node
    PLOG_DEBUG "Configuring couchbase..." $LINENO
    check_and_start_couchbase 
    
    op=`$CLI cluster-init -c "$IP" --cluster-init-port="$PORT" --cluster-init-username="$ADMIN_NAME" --cluster-init-password="$ADMIN_PASS" --cluster-init-ramsize="$RAM_SIZE"`
    if [ $? -ne 0 ];then
        #if username/pass is already set
        echo $op|grep "check your username" >/dev/null
        if [ $? -eq 0 ];then
            PLOG_DEBUG "User/Pass already set! Reinitializing..." $LINENO
            op=`$CLI cluster-init -u $ADMIN_NAME -p $ADMIN_PASS -c "$IP" --cluster-init-port="$PORT" --cluster-init-username="$ADMIN_NAME" --cluster-init-password="$ADMIN_PASS" --cluster-init-ramsize="$RAM_SIZE"`
        else
            PLOG_ERROR "Couchbase initialization failed!" $LINENO
        fi
    fi


    #node init
    $CLI node-init -c $IP:$PORT --node-init-data-path=$DATA_PATH -u $ADMIN_NAME -p $ADMIN_PASS


    #create the couchbase buckets
    create_buckets 

    #update the /opt/diametriq/dre/config/couchbase.cfg
    update_couchbase_cfg "cb_hostname" "$IP"
    update_couchbase_cfg "cb_port" "$PORT"
    update_couchbase_cfg "cb_userName" $ADMIN_NAME
    update_couchbase_cfg "cb_pass" $ADMIN_PASS
    update_couchbase_cfg "cb_matehostname" $MATE_HOSTNAME 
    update_couchbase_cfg "cb_mateip" $MATE_IP
}


function check_and_stop_couchbase()
{
    ps -eaf|grep -v "grep"|grep `cat /opt/couchbase/var/lib/couchbase/couchbase-server.pid`  >/dev/null
    if [ $? -eq 0 ];then

        #update the couchbase-state file
        echo "0" > /etc/.${PRODUCT}/couchbase_state
        LOG_INFO "Stopping couchbase-server node..." $LINENO    
        service couchbase-server stop
        LOG_INFO "Couchbase state=`cat /etc/.${PRODUCT}/couchbase_state`" $LINENO

    else
	PLOG_WARNING "Couchbase-server is not running!" $LINENO
	echo "0" >/etc/.${PRODUCT}/couchbase_state 
    fi


}

function wait_for_couchbase_to_comeup()
{
    #make sure all the processes have come up
    #wait until then
    echo "2" > /etc/.${PRODUCT}/couchbase_state
    local flag=1    
    local list="epmd beam.smp memsup cpu_sup ssl_esock i386-linux-godu moxi /opt/couchbase/bin/memcached  inet_gethost portsigar"

    while [ $flag -eq 1 ]
    do

	sleep 1
	flag=0
	for i in $list
	do 
	    ps -eaf|grep $i|grep -v grep > /dev/null
            if [ $? -ne 0 ];then
                echo "Waiting for $i to come up ." >>$CB_LOGS
	    	flag=1
            fi

	done
  	    
    done
    

}

function check_and_start_couchbase()
{
    ps -eaf|grep -v "grep"|grep `cat /opt/couchbase/var/lib/couchbase/couchbase-server.pid` >/dev/null
    if [ $? -ne 0 ];then

        echo "1" > /etc/.${PRODUCT}/couchbase_state
        LOG_INFO "Starting couchbase-server node..." $LINENO    
        service couchbase-server start
        #update the couchbase-state file
	wait_for_couchbase_to_comeup
        echo "1" > /etc/.${PRODUCT}/couchbase_state
        LOG_INFO "Couchbase state=`cat /etc/.${PRODUCT}/couchbase_state`" $LINENO
    else
	PLOG_WARNING "Couchbase-server is already running!" $LINENO
	echo "1" > /etc/.${PRODUCT}/couchbase_state
    fi

}

#clean couchbase function required during uninstall
function clean_couchbase()
{
    local IP=`GetMysqlLocalIP`
    local PORT=8091
    local ADMIN_NAME="dquser"
    local ADMIN_PASS="diametriq@123"
    local RAM_SIZE=$ram_size
    local MATE_HOSTNAME=`GetMysqlMateHostname`
    local MATE_IP=`GetMysqlMateIP`
    local CLI=/opt/couchbase/couchbase/bin/couchbase-cli
    local DATA_PATH=/opt/couchbase/var/lib/couchbase/data

#if the other node is already in the cluster remove
    op=`$CLI rebalance-stop -c $IP:$PORT -u $ADMIN_NAME -p $ADMIN_PASS`
    op=`$CLI failover --cluster=$IP:$PORT    -u $ADMIN_NAME -p $ADMIN_PASS    --server-failover=$MATE_IP:$PORT`
    if [ $? -eq 0 ];then
        PLOG_DEBUG "Removed $MATE_IP from the cluster" $LINENO
        op=`$CLI rebalance -c $IP:$PORT     -u $ADMIN_NAME -p $ADMIN_PASS  --server-remove=$MATE_IP:$PORT`
    fi

    delete_buckets
    /opt/diametriq/${PRODUCT}/bin/couchbase stop
}




