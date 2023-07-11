#!/bin/bash
HOST_NAME=`hostname`
PRODUCT=iwf
DRE_CFG_FILE=/etc/${PRODUCT}.cfg
USER_CFG_FILE=/opt/diametriq/${PRODUCT}/config/${HOST_NAME}_${PRODUCT}.cnf
ORIG_CFG_FILE=/opt/diametriq/${PRODUCT}/config/user_${PRODUCT}.cnf

source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh

#$1=name $2=Value $3=cnf file
function replace_configuration()
{
    sed -i "s/^$1=.*/$1=$2/g" $3
}

#$1=section name $2=name-value string $3=cnf file name
function insert_config_in_section()
{
    #delete the line
    DEL=`echo "$2"|cut -d'=' -f1`
    local session=$1
    local namevalue=$2
    sed -i /"^$DEL.*"/d  "$3"
    #insert config
    sed -e '/\['$session'\]/{:a;n;/^$/!ba;i'$namevalue'' -e '}' "$3" >/tmp/tmp.cfg
    mv /tmp/tmp.cfg $3



}

#$1=name 
function check_string_is_trapsinkip()
{
	local config_string=$1	

	local ret=`echo $config_string | grep -ic "trapsink"` 

	if [ $ret -ne 0 ];then
		
		ret=`echo $config_string | grep -ic "ip"`
		if [ $ret -ne 0 ];then
			echo "0"
			return 
		fi	
	fi

	echo "1"
	return
}


#$1=name 
function check_string_is_interfacebond()
{
	local config_string=$1	

	local ret=`echo $config_string | grep -ic "^interface"` 

	if [ $ret -ne 0 ];then
		
			echo "0"
			return
	fi

	echo "1"
	return
}

#$1=name
function check_string_is_cidrip()
{
   local config_string=$1

   local ret=`echo $config_string | grep -ic "^cidr"` 

   if [ $ret -ne 0 ];then
        echo "0"
        return
   fi

   echo "1"
   return
}


#$1=name 
function check_string_is_ipbond()
{
	local config_string=$1	

	local ret=`echo $config_string | grep -ic "^ip"` 

	if [ $ret -ne 0 ];then
		echo "0"
		return
	fi

	echo "1"
	return
}

#$1=name 
function get_common_name_for_dynamic_variables()
{
	local config_string=$1

	ret=`check_string_is_interfacebond $config_string`
	if [ $ret -eq 0 ];then
		echo "InterfaceBond"
	fi

	ret=`check_string_is_trapsinkip $config_string`
	if [ $ret -eq 0 ];then
		echo "TrapSinkIP"
	fi

	ret=`check_string_is_cidrip $config_string`
	if [ $ret -eq 0 ];then
		echo "CIDR_IP"
	fi

}

#$1=section-name $2=name $3=value pair $4=filename
function insert_or_replace_name_value_string()
{
	local section_name=$1
	local config_string=$2
	local config_value=$3
	local file_name=$4

	grep "^$config_string" $file_name 

	if [ $? -eq 0 ];then
		replace_configuration $config_string $config_value $file_name
	else
		name_value_pair=$config_string"="$config_value
		insert_config_in_section $section_name $name_value_pair $file_name
	fi

}

#$1=name $2=value
function create_name_value_string()
{
	local config_string=$1
	local config_value=$2

	common_name=`get_common_name_for_dynamic_variables $config_string`
	case $common_name in
		"InterfaceBond")
			#echo "It is InterfaceBond "$config_string
			#interfaceno=${config_string:9:1}
			#bond=${config_string:14:1}
			#str="interface"$interfaceno"_bond"$bond
            str=`echo $config_string | tr 'A-Z' 'a-z'`
			insert_or_replace_name_value_string "bonding" "$str" "$config_value" "$USER_CFG_FILE"
			;;
		"TrapSinkIP")
			#echo "It is TrapSinkIP "$config_string
			trapip=${config_string:10:1}
			str="trap_sink_ip"$trapip
			insert_or_replace_name_value_string "alarm" "$str" "$config_value" "$USER_CFG_FILE"
			;;
        "CIDR_IP")
			#echo "It is CIDR Bond "$config_string
			str=${config_string:5:${#config_string}}
			insert_or_replace_name_value_string "bonding" "$str" "$config_value" "$USER_CFG_FILE"
            ;;
		*)
			;;
	esac	
}

function delete_dynamically_created_namevalue_pair()
{
    sed -i /"^ip_"/d  "$1"
    sed -i /"^interface[1-9]_"/d  "$1"
    sed -i /"^trap_sink_ip"/d  "$1"
}

cp $ORIG_CFG_FILE $USER_CFG_FILE
delete_dynamically_created_namevalue_pair $USER_CFG_FILE

for i in `cat $DRE_CFG_FILE`
do
	CONFIG_STRING_VALUE=$i
	CONFIG_STRING=`echo $i | tr -s "=" | cut -d "=" -f 1`
	CONFIG_VALUE=`echo $i | tr -s "=" | cut -d "=" -f 2`

	case $CONFIG_STRING in
		"DreInstallMode")	
			replace_configuration "dre_install_mode" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"MysqlUsername")	
			replace_configuration "mysql_username" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"MysqlPassword")	
			replace_configuration "mysql_password" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"MysqlIpAddress")	
				;;
		"MysqlPort")	
				;;
		"LocalHostName")	
			replace_configuration "host_name" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"LocalRealmName")	
			replace_configuration "realm_name" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"LocalIpAddress")	
			replace_configuration "ip_address" $CONFIG_VALUE $USER_CFG_FILE
				;;
	 	"PublicIpAddress")
			replace_configuration "public_ip_address" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"LocalPort")	
			replace_configuration "port" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"LocalTransportType")	
			replace_configuration "transport_type" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"NetID")	
			replace_configuration "net_id" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"TipcNodeAddress")	
			replace_configuration "tipc_node_address" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"BearerName")	
			replace_configuration "bearer_name" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"HAMode")	
			replace_configuration "ha_mode" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"VirtualIP")	
			replace_configuration "mysql_virtual_ip" `convert_cidrip_to_sed_cirdrip "$CONFIG_VALUE"` $USER_CFG_FILE
				;;
		"Ethernet")	
			replace_configuration "mysql_interface_name" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"BroadcastAddress")	
				;;
		"SubNetMaskPrefixLen")	
				;;
		"NoOfBonds")	
				;;
        "BondName.")
                ;;
		"MysqlLocalIP")	
			replace_configuration "mysql_local_ip" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"MysqlMateIP")	
			replace_configuration "mysql_mate_ip" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"MysqlLocalHostname")	
				;;
		"MysqlMateHostname")	
			replace_configuration "mysql_mate_hostname" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"NtpServerIP")	
			replace_configuration "ntp_server_ip" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"RemoteNodeUsername")	
			replace_configuration "mysql_password" $CONFIG_VALUE $USER_CFG_FILE
				;;
		"RemoteNodeIP")	
				;;
		"Bonding")
			replace_configuration "bonding" $CONFIG_VALUE $USER_CFG_FILE
				;;
			
		*)
			#printf "ACTUAL_STR %s  \n\tSTRING %s \n\tVALUE %s\n" $CONFIG_STRING_VALUE $CONFIG_STRING $CONFIG_VALUE
			create_name_value_string $CONFIG_STRING $CONFIG_VALUE
				;;
	esac
	
done

