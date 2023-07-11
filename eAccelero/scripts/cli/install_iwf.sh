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
bldwht='\e[1;37m' # White
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

PRODUCT=iwf

source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh                                     



LOG_DEBUG "install.sh script begnining" $LINENO
#MysqlUsername=`null_check "UserName		:" "UserName (should not be null):"`
#MysqlPassword=`silent_null_check "Password		:" "Password (should not be null) :"`
echo ""
#MysqlIpAddress=`null_check "IpAddress		:" "IpAddress (should not be null):"`
#MysqlPort=`num_check "Port			:" "Port (should be integer):"`

LOG_INFO "Mysql Details" $LINENO
MysqlUsername=$( GetMysqlUsername )
LOG_INFO "MysqlUsername=$MysqlUsername"  $LINENO
MysqlPassword=$( GetMysqlPassword )
LOG_INFO "MysqlPassword=$MysqlPassword" $LINENO
MysqlIpAddress=$( GetMysqlIpAddress )
LOG_INFO "MysqlIpAddress=$MysqlIpAddress" $LINENO
MysqlPort=$( GetMysqlPort )
LOG_INFO "MysqlPort=$MysqlPort" $LINENO

#echo -e "${bldblu}****************************************************${txtrst}"
#echo -e "${bldred}               Localhost Details${txtrst}"
#echo -e "${bldblu}****************************************************${txtrst}"

#LocalHostName=`null_check "Server HostName		:" "Server HostName  (should not be null)           :"`
#LocalRealmName=`null_check "RealmName		:" "RealmName (should not be null)            :"`
#LocalIpAddress=`null_check "IpAddress		:" "IpAddress (should not be null)            :"`
#LocalPort=`num_check "Port			:" "Port (should be integer)            :"`

LocalHostName=$( GetLocalHostName )
LOG_INFO "LocalHostName=$LocalHostName" $LINENO
LocalRealmName=$( GetLocalRealmName )
LOG_INFO "LocalRealmName=$LocalRealmName" $LINENO
LocalIpAddress=$( GetLocalIpAddress )
LOG_INFO "LocalIpAddress=$LocalIpAddress" $LINENO
PublicIpAddress=$( GetPublicIpAddress )
LOG_INFO "PublicIpAddress=$PublicIpAddress" $LINENO
LocalPort=$( GetLocalPort )
LOG_INFO "LocalPort=$LocalPort" $LINENO
LocalTransportType=$( GetLocalTransportType )
LOG_INFO "LocalTransportType=$LocalTransportType" $LINENO
LocalPort2="`GetDreConfigValue "LocalPort2"`"
LOG_INFO "LocalPort2=$LocalPort2" $LINENO
LocalTransportType2="`GetDreConfigValue "LocalTransportType2"`"
LOG_INFO "LocalTransportType2=$LocalTransportType2" $LINENO
SecureLocalPort="`GetDreConfigValue "SecureLocalPort"`"
LOG_INFO "SecureLocalPort=$SecureLocalPort" $LINENO
LocalTransportType3="`GetDreConfigValue "LocalTransportType3"`"
LOG_INFO "LocalTransportType3=$LocalTransportType3" $LINENO

if [ -z $PRODUCT ];then
    $DRE_ROOT/scripts/configCmgr.sh "TCP" $MysqlUsername $MysqlPassword $MysqlIpAddress $MysqlPort
    if [ $? != 0 ];then
        LOG_ERROR "$DRE_ROOT/scripts/configCmgr.sh failed!" $LINENO 
        exit 1
    fi
fi

if [ $PRODUCT = "dre" ];then
    $DRE_ROOT/scripts/configCmgr.sh "TCP" $MysqlUsername $MysqlPassword $MysqlIpAddress $MysqlPort
    if [ $? != 0 ];then
        LOG_ERROR "$DRE_ROOT/scripts/configCmgr.sh failed!" $LINENO 
        exit 1
    fi
fi

if [ $PRODUCT = "iwf" ];then
    $IWF_ROOT/scripts/configCmgr.sh "TCP" $MysqlUsername $MysqlPassword $MysqlIpAddress $MysqlPort
    if [ $? != 0 ];then
        LOG_ERROR "$IWF_ROOT/scripts/configCmgr.sh failed!" $LINENO 
        exit 1
    fi
fi

unset_sess_repl="set @@session.sql_log_bin=0;"
my="mysql  --host=$MysqlIpAddress --user=$MysqlUsername --password=$MysqlPassword --port=$MysqlPort --database=DIAMETRIQ -se"
if [ $? != 0 ];then
    PLOG_ERROR "Failed to Login to mysql" $LINENO
    exit 1
fi
my1="mysql  --host=$MysqlIpAddress --user=$MysqlUsername --password=$MysqlPassword --port=$MysqlPort "
if [ $? != 0 ];then
    PLOG_ERROR "Failed to Login to mysql" $LINENO
    exit 1
fi
${my1} -se  "stop slave;"  2> /dev/null

if [ "$1" == "--reinstall" ];then
    LOG_INFO "--reinstall.." $LINENO
    #change only Localhost details 
    ${my} "${unset_sess_repl} delete from LocalHostConfigT"
    ${my} "${unset_sess_repl} delete from LOCAL_TRANSPORT_TB"
    if [ $? != 0 ];then
	LOG_ERROR "delete from LocalHostConfigT failed" $LINENO
    	${my1} -se "start slave;" 2>/dev/null
	if [ $? != 0 ];then
		LOG_WARNING "start slave failed... " $LINENO
	fi
	exit 1
    fi

    if [ $PRODUCT = "iwf" ];then
            pointcode=$( GetPointCode )
#            ni=$( GetNI )
            ssn=$( GetSSN )
            tcapinvoketimer=$( GetTcapInvokeTimer )

           
            format_str=`format_cfg "global_title_indicator"`
            global_title_indicator=`GetDreConfigValue "$format_str"`
           
            format_str=`format_cfg "nature_of_address_indicator"`
            natureofaddrindi=`GetDreConfigValue "$format_str"`
            format_str=`format_cfg "global_title_address_information"`
            globaltitleaddrinfo=`GetDreConfigValue "$format_str"`
            format_str=`format_cfg "translation_type"`
            transtype=`GetDreConfigValue "$format_str"`
            format_str=`format_cfg "numbering_plan"`
            numplan=`GetDreConfigValue "$format_str"`
            format_str=`format_cfg "encoding_scheme"`
            encodescheme=`GetDreConfigValue "$format_str"`
            format_str=`format_cfg "routing_indicator"`
            routingindicator=`GetDreConfigValue "$format_str"`
            format_str=`format_cfg "self_sccp_addr_use_from_config"`
            selfsccpaddrusefromconfig=`GetDreConfigValue "$format_str"`
            format_str=`format_cfg "use_sccp_cdpa_from_incomming_msg"`
            usesccpcdpafromincommingmsg=`GetDreConfigValue "$format_str"`
            format_str=`format_cfg "has_ssn"`
            hasssn=`GetDreConfigValue "$format_str"`
            format_str=`format_cfg "has_pc"`
            haspc=`GetDreConfigValue "$format_str"`
	    format_str=`format_cfg "selection_criteria"`
	    selectioncriteria=`GetDreConfigValue "$format_str"`
	        format_str=`format_cfg "host_name1"`
            host_name1=`GetDreConfigValue "$format_str"`
            format_str=`format_cfg "host_name2"`
            host_name2=`GetDreConfigValue "$format_str"`
            format_str=`format_cfg "asp_id1"`
            asp_id1=`GetDreConfigValue "$format_str"`
            format_str=`format_cfg "asp_id2"`
            asp_id2=`GetDreConfigValue "$format_str"`

            ${my} "${unset_sess_repl} delete from IWF_LOCAL_SSN_MAPPING_TB"
            if [ $? != 0 ];then
	            LOG_ERROR "delete from IWF_LOCAL_SSN_MAPPING_TB failed" $LINENO
            fi
            ${my} "${unset_sess_repl} delete from IWF_LOCAL_CONFIG_TB"
            if [ $? != 0 ];then
	            LOG_ERROR "delete from IWF_LOCAL_CONFIG_TB failed" $LINENO
            fi

            case $global_title_indicator in
                1) 
 
                   # 
                    
                   if [ "`GetDreInstallMode`" == "4" ];then
                       ${my} "${unset_sess_repl}  INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,NATURE_OF_ADDRESS_INDICATOR,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,HOST_NAME_2,ASP_ID_1,ASP_ID_2) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$natureofaddrindi,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1','$host_name2',$asp_id1,$asp_id2) "
                   else
                       ${my} "${unset_sess_repl}  INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,NATURE_OF_ADDRESS_INDICATOR,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,ASP_ID_1) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$natureofaddrindi,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1',$asp_id1) "
                   fi
                       ;;
                2) 

                   # 
                   if [ "`GetDreInstallMode`" == "4" ];then
                       ${my} "${unset_sess_repl} INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,TRANSLATION_TYPE,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,HOST_NAME_2,ASP_ID_1,ASP_ID_2) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$transtype,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1','$host_name2',$asp_id1,$asp_id2) "
                   else
                       ${my} "${unset_sess_repl} INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,TRANSLATION_TYPE,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,ASP_ID_1) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$transtype,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1',$asp_id1) "
                   fi
                       ;;
                3) 

                   # 
                   if [ "`GetDreInstallMode`" == "4" ];then
                       ${my} "${unset_sess_repl} INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,TRANSLATION_TYPE,NUMBERING_PLAN,ENCODING_SCHEME,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,HOST_NAME_2,ASP_ID_1,ASP_ID_2) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$transtype,$numplan,$encodescheme,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1','$host_name2',$asp_id1,$asp_id2) "
                   else
                       ${my} "${unset_sess_repl} INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,TRANSLATION_TYPE,NUMBERING_PLAN,ENCODING_SCHEME,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,ASP_ID_1) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$transtype,$numplan,$encodescheme,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1',$asp_id1) "
                   fi
                       ;;
                   4)

                   #  
                   if [ "`GetDreInstallMode`" == "4" ];then
                       ${my} "${unset_sess_repl} INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,TRANSLATION_TYPE,NUMBERING_PLAN,ENCODING_SCHEME,NATURE_OF_ADDRESS_INDICATOR,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,HOST_NAME_2,ASP_ID_1,ASP_ID_2) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$transtype,$numplan,$encodescheme,$natureofaddrindi,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1','$host_name2',$asp_id1,$asp_id2) "
                   else
                       ${my} "${unset_sess_repl} INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,TRANSLATION_TYPE,NUMBERING_PLAN,ENCODING_SCHEME,NATURE_OF_ADDRESS_INDICATOR,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,ASP_ID_1) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$transtype,$numplan,$encodescheme,$natureofaddrindi,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1',$asp_id1) "
                   fi
                       ;;
            esac

            ${my} "${unset_sess_repl} insert into IWF_LOCAL_SSN_MAPPING_TB(IWF_LOCAL_SSN_ID,IWF_LOCAL_CONFIG_ID ) value ((select IWF_LOCAL_SSN_ID from IWF_LOCAL_SSN_TABLE where SSN_NAME='$ssn'),(select IWF_LOCAL_CONFIG_ID from IWF_LOCAL_CONFIG_TB) )"
    fi

    ${my} "${unset_sess_repl} INSERT INTO LocalHostConfigT (HostName,RealmName ) VALUES ('$LocalHostName','$LocalRealmName')"
    if [ "$PublicIpAddress" == "NULL" ];then

    		if [ "$LocalPort" != "NULL" ] && [ "$LocalTransportType" != "NULL" ];then
    			${my} "${unset_sess_repl} INSERT INTO LOCAL_TRANSPORT_TB
	    		(TRANSPORT_TYPE,IP_ADDRESS,PORT,LocalHostConfigID) VALUES ('$LocalTransportType','$LocalIpAddress','$LocalPort',(select LocalHostConfigID from LocalHostConfigT where HostName = '$LocalHostName' and RealmName = '$LocalRealmName'))"
	        fi
    		if [ "$LocalPort2" != "NULL" ] && [ "$LocalTransportType2" != "NULL" ];then
    			${my} "${unset_sess_repl} INSERT INTO LOCAL_TRANSPORT_TB
    			(TRANSPORT_TYPE,IP_ADDRESS,PORT,LocalHostConfigID) VALUES ('$LocalTransportType2','$LocalIpAddress','$LocalPort2',(select LocalHostConfigID from LocalHostConfigT where HostName = '$LocalHostName' and RealmName = '$LocalRealmName'))"
    		fi
		if [ "$SecureLocalPort" != "NULL" ] && [ "$LocalTransportType3" != "NULL" ];then
			${my} "${unset_sess_repl} INSERT INTO LOCAL_TRANSPORT_TB
    			(TRANSPORT_TYPE,IP_ADDRESS,SecurePort,LocalHostConfigID) VALUES ('$LocalTransportType3','$LocalIpAddress','$SecureLocalPort',(select LocalHostConfigID from LocalHostConfigT where HostName = '$LocalHostName' and RealmName = '$LocalRealmName'))"
    		fi

    else

    		if [ "$LocalPort" != "NULL" ] && [ "$LocalTransportType" != "NULL" ];then
		    	${my} "${unset_sess_repl} INSERT INTO LOCAL_TRANSPORT_TB
		    	(TRANSPORT_TYPE,IP_ADDRESS,PORT,LocalHostConfigID,PUBLIC_SERVER_IP) VALUES ('$LocalTransportType','$LocalIpAddress','$LocalPort',(select LocalHostConfigID from LocalHostConfigT where HostName = '$LocalHostName' and RealmName = '$LocalRealmName'),'$PublicIpAddress')"
		fi

    		if [ "$LocalPort2" != "NULL" ] && [ "$LocalTransportType2" != "NULL" ];then
    	I		${my} "${unset_sess_repl} INSERT INTO LOCAL_TRANSPORT_TB
    			(TRANSPORT_TYPE,IP_ADDRESS,PORT,LocalHostConfigID,PUBLIC_SERVER_IP) VALUES ('$LocalTransportType2','$LocalIpAddress','$LocalPort2',(select LocalHostConfigID from LocalHostConfigT where HostName = '$LocalHostName' and RealmName = '$LocalRealmName'),'$PublicIpAddress')"
    		fi
		
		if [ "$SecureLocalPort" != "NULL" ] && [ "$LocalTransportType3" != "NULL" ];then

			${my} "${unset_sess_repl} INSERT INTO LOCAL_TRANSPORT_TB
    			(TRANSPORT_TYPE,IP_ADDRESS,SecurePort,LocalHostConfigID,PUBLIC_SERVER_IP) VALUES ('$LocalTransportType3','$LocalIpAddress','$SecureLocalPort',(select LocalHostConfigID from LocalHostConfigT where HostName = '$LocalHostName' and RealmName = '$LocalRealmName'),'$PublicIpAddress')"
    		fi
	
    fi
  
    if [ $? != 0 ];then
	LOG_ERROR "INSERT INTO LocalHostConfigT" $LINENO
    	${my1} -se  "start slave;" 2>/dev/null
	if [ $? != 0 ];then
		LOG_WARNING "start slave failed... " $LINENO
	fi
        exit 1
    fi

    if [ $PRODUCT = "dre" ];then
        ${my1} < $DRE_ROOT/scripts/install_functions.sql
        ${my1} < $DRE_ROOT/scripts/trigger_fun.sql
    fi

    ${my1} -se  "start slave;" 2>/dev/null
    if [ $? != 0 ];then
	LOG_WARNING "start slave failed... " $LINENO
    fi
    exit 0
  
fi

${my1} -se  "stop slave;"  2> /dev/null
LOG_DEBUG "Calling createtables.sh" $LINENO
./createtables.sh $MysqlUsername $MysqlPassword $MysqlIpAddress $MysqlPort
if [ $? != 0 ];then 
    LOG_ERROR "createtables.sh failed ! " $LINENO
    	${my1} -se  "start slave;" 2>/dev/null
	if [ $? != 0 ];then
		LOG_WARNING "start slave failed... " $LINENO
	fi
    exit 1
fi

    	${my1} -se "start slave;" 2>/dev/null
	if [ $? != 0 ];then
		LOG_WARNING "start slave failed... " $LINENO
	fi

if [ -z $PRODUCT ];then
    $DRE_ROOT/scripts/configCmgr.sh "TCP" $MysqlUsername $MysqlPassword $MysqlIpAddress $MysqlPort
    if [ $? != 0 ];then
        LOG_ERROR "$DRE_ROOT/scripts/configCmgr.sh failed!" $LINENO 
        exit 1
    fi
fi

if [ $PRODUCT = "dre" ];then
    $DRE_ROOT/scripts/configCmgr.sh "TCP" $MysqlUsername $MysqlPassword $MysqlIpAddress $MysqlPort
    if [ $? != 0 ];then
        LOG_ERROR "$DRE_ROOT/scripts/configCmgr.sh failed!" $LINENO 
        exit 1
    fi
fi

if [ $PRODUCT = "iwf" ];then
    $IWF_ROOT/scripts/configCmgr.sh "TCP" $MysqlUsername $MysqlPassword $MysqlIpAddress $MysqlPort
    if [ $? != 0 ];then
        LOG_ERROR "$IWF_ROOT/scripts/configCmgr.sh failed!" $LINENO 
        exit 1
    fi
fi



LOG_INFO "SUCCESFULLY CREATED TABLES IN DATABASE" $LINENO
echo -e "${bldblu}****************************************************${txtrst}"
echo -e "${bldred}       SUCCESFULLY CREATED TABLES IN DATABASE${txtrst}"
echo -e "${bldblu}****************************************************${txtrst}"
${my} "${unset_sess_repl} show tables"
RES=`${my} "${unset_sess_repl} show tables"`
LOG_INFO "show tables" $LINENO 
LOG_INFO "$RES" $LINENO

LOG_INFO "INSERTING DEFAULT ROWS IN TABLES" $LINENO
echo -e "${bldblu}****************************************************${txtrst}"
echo -e "${bldred}          INSERTING DEFAULT ROWS IN TABLES${txtrst}"
echo -e "${bldblu}****************************************************${txtrst}"

${my1} -se  "stop slave;"  2> /dev/null

if [ $PRODUCT = "iwf" ];then
    pointcode=$( GetPointCode )
#ni=$( GetNI )
    ssn=$( GetSSN )
    tcapinvoketimer=$( GetTcapInvokeTimer )
    format_str=`format_cfg "global_title_indicator"`
    global_title_indicator=`GetDreConfigValue "$format_str"`

    format_str=`format_cfg "nature_of_address_indicator"`
    natureofaddrindi=`GetDreConfigValue "$format_str"`
    format_str=`format_cfg "global_title_address_information"`
    globaltitleaddrinfo=`GetDreConfigValue "$format_str"`
    format_str=`format_cfg "translation_type"`
    transtype=`GetDreConfigValue "$format_str"`
    format_str=`format_cfg "numbering_plan"`
    numplan=`GetDreConfigValue "$format_str"`
    format_str=`format_cfg "encoding_scheme"`
    encodescheme=`GetDreConfigValue "$format_str"`
    format_str=`format_cfg "routing_indicator"`
    routingindicator=`GetDreConfigValue "$format_str"`
    format_str=`format_cfg "self_sccp_addr_use_from_config"`
    selfsccpaddrusefromconfig=`GetDreConfigValue "$format_str"`
    format_str=`format_cfg "use_sccp_cdpa_from_incomming_msg"`
    usesccpcdpafromincommingmsg=`GetDreConfigValue "$format_str"`
    format_str=`format_cfg "has_ssn"`
    hasssn=`GetDreConfigValue "$format_str"`
    format_str=`format_cfg "has_pc"`
    haspc=`GetDreConfigValue "$format_str"`
    format_str=`format_cfg "selection_criteria"`
    selectioncriteria=`GetDreConfigValue "$format_str"`
    format_str=`format_cfg "host_name1"`
    host_name1=`GetDreConfigValue "$format_str"`
    format_str=`format_cfg "host_name2"`
    host_name2=`GetDreConfigValue "$format_str"`
    format_str=`format_cfg "asp_id1"`
    asp_id1=`GetDreConfigValue "$format_str"`
    format_str=`format_cfg "asp_id2"`
    asp_id2=`GetDreConfigValue "$format_str"`

	 case $global_title_indicator in
                1) 
                   # 
                   if [ "`GetDreInstallMode`" == "4" ];then
                       ${my} "${unset_sess_repl} INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,NATURE_OF_ADDRESS_INDICATOR,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,HOST_NAME_2,ASP_ID_1,ASP_ID_2) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$natureofaddrindi,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1','$host_name2',$asp_id1,$asp_id2) "
                   else
                       ${my} "${unset_sess_repl} INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,NATURE_OF_ADDRESS_INDICATOR,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,ASP_ID_1) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$natureofaddrindi,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1',$asp_id1) "
                   fi
                       ;;
                2) 

                   # 
                   if [ "`GetDreInstallMode`" == "4" ];then
                       ${my} "${unset_sess_repl} INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,TRANSLATION_TYPE,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,HOST_NAME_2,ASP_ID_1,ASP_ID_2) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$transtype,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1','$host_name2',$asp_id1,$asp_id2) "
                   else
                       ${my} "${unset_sess_repl} INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,TRANSLATION_TYPE,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,ASP_ID_1) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$transtype,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1',$asp_id1) "
                   fi
                       ;;
                3) 

                   # 
                   if [ "`GetDreInstallMode`" == "4" ];then
                       ${my} "${unset_sess_repl} INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,TRANSLATION_TYPE,NUMBERING_PLAN,ENCODING_SCHEME,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,HOST_NAME_2,ASP_ID_1,ASP_ID_2) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$transtype,$numplan,$encodescheme,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1','$host_name2',$asp_id1,$asp_id2) "
                   else
                       ${my} "${unset_sess_repl} INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,TRANSLATION_TYPE,NUMBERING_PLAN,ENCODING_SCHEME,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,ASP_ID_1) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$transtype,$numplan,$encodescheme,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1',$asp_id1) "
                   fi
                       ;;
                4)

                   # 
                   if [ "`GetDreInstallMode`" == "4" ];then
                       ${my} "${unset_sess_repl} INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,TRANSLATION_TYPE,NUMBERING_PLAN,ENCODING_SCHEME,NATURE_OF_ADDRESS_INDICATOR,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,HOST_NAME_2,ASP_ID_1,ASP_ID_2) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$transtype,$numplan,$encodescheme,$natureofaddrindi,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1','$host_name2',$asp_id1,$asp_id2) "
                   else
                       ${my} "${unset_sess_repl} INSERT INTO IWF_LOCAL_CONFIG_TB 
                       (POINTCODE,ADDRESS_TYPE,TCAP_INVOKE_TIMER,GTI,TRANSLATION_TYPE,NUMBERING_PLAN,ENCODING_SCHEME,NATURE_OF_ADDRESS_INDICATOR,GT_ADDR_DIGITS,SELECTION_CRITERIA,USE_LOCAL_GT_FROM_CONFIG,USE_SCCP_CDPA_FROM_INCOMMING_MSG,INCLUDE_PC,HOST_NAME_1,ASP_ID_1) VALUES 
                       ($pointcode,'$routingindicator',$tcapinvoketimer,$global_title_indicator,$transtype,$numplan,$encodescheme,$natureofaddrindi,'$globaltitleaddrinfo',$selectioncriteria,`convert_yes_no_to_1_0 $selfsccpaddrusefromconfig`,`convert_yes_no_to_1_0 $usesccpcdpafromincommingmsg`,`convert_yes_no_to_1_0 $haspc`,'$host_name1',$asp_id1) "
                   fi
                       ;;
            esac

    ${my} "${unset_sess_repl} insert into IWF_LOCAL_SSN_MAPPING_TB(IWF_LOCAL_SSN_ID,IWF_LOCAL_CONFIG_ID ) value ((select IWF_LOCAL_SSN_ID from IWF_LOCAL_SSN_TABLE where SSN_NAME='$ssn'),(select IWF_LOCAL_CONFIG_ID from IWF_LOCAL_CONFIG_TB) )"
fi


${my} "${unset_sess_repl} INSERT INTO LocalHostConfigT (HostName,RealmName ) VALUES ('$LocalHostName','$LocalRealmName')"

if [ "$PublicIpAddress" == "NULL" ];then
    		if [ "$LocalPort" != "NULL" ] && [ "$LocalTransportType" != "NULL" ];then
    			${my} "${unset_sess_repl} INSERT INTO LOCAL_TRANSPORT_TB
	    		(TRANSPORT_TYPE,IP_ADDRESS,PORT,LocalHostConfigID) VALUES ('$LocalTransportType','$LocalIpAddress','$LocalPort',(select LocalHostConfigID from LocalHostConfigT where HostName = '$LocalHostName' and RealmName = '$LocalRealmName'))"
	        fi
    		if [ "$LocalPort2" != "NULL" ] && [ "$LocalTransportType2" != "NULL" ];then
    			${my} "${unset_sess_repl} INSERT INTO LOCAL_TRANSPORT_TB
    			(TRANSPORT_TYPE,IP_ADDRESS,PORT,LocalHostConfigID) VALUES ('$LocalTransportType2','$LocalIpAddress','$LocalPort2',(select LocalHostConfigID from LocalHostConfigT where HostName = '$LocalHostName' and RealmName = '$LocalRealmName'))"
    		fi
		if [ "$SecureLocalPort" != "NULL" ] && [ "$LocalTransportType3" != "NULL" ];then
			${my} "${unset_sess_repl} INSERT INTO LOCAL_TRANSPORT_TB
    			(TRANSPORT_TYPE,IP_ADDRESS,SecurePort,LocalHostConfigID) VALUES ('$LocalTransportType3','$LocalIpAddress','$SecureLocalPort',(select LocalHostConfigID from LocalHostConfigT where HostName = '$LocalHostName' and RealmName = '$LocalRealmName'))"
    		fi
else
    		if [ "$LocalPort" != "NULL" ] && [ "$LocalTransportType" != "NULL" ];then
		    	${my} "${unset_sess_repl} INSERT INTO LOCAL_TRANSPORT_TB
		    	(TRANSPORT_TYPE,IP_ADDRESS,PORT,LocalHostConfigID,PUBLIC_SERVER_IP) VALUES ('$LocalTransportType','$LocalIpAddress','$LocalPort',(select LocalHostConfigID from LocalHostConfigT where HostName = '$LocalHostName' and RealmName = '$LocalRealmName'),'$PublicIpAddress')"
		fi

    		if [ "$LocalPort2" != "NULL" ] && [ "$LocalTransportType2" != "NULL" ];then
    	I		${my} "${unset_sess_repl} INSERT INTO LOCAL_TRANSPORT_TB
    			(TRANSPORT_TYPE,IP_ADDRESS,PORT,LocalHostConfigID,PUBLIC_SERVER_IP) VALUES ('$LocalTransportType2','$LocalIpAddress','$LocalPort2',(select LocalHostConfigID from LocalHostConfigT where HostName = '$LocalHostName' and RealmName = '$LocalRealmName'),'$PublicIpAddress')"
    		fi
		
		if [ "$SecureLocalPort" != "NULL" ] && [ "$LocalTransportType3" != "NULL" ];then

			${my} "${unset_sess_repl} INSERT INTO LOCAL_TRANSPORT_TB
    			(TRANSPORT_TYPE,IP_ADDRESS,SecurePort,LocalHostConfigID,PUBLIC_SERVER_IP) VALUES ('$LocalTransportType3','$LocalIpAddress','$SecureLocalPort',(select LocalHostConfigID from LocalHostConfigT where HostName = '$LocalHostName' and RealmName = '$LocalRealmName'),'$PublicIpAddress')"
    		fi
fi

if [ $PRODUCT = "dre" ];then
    ${my1} < $DRE_ROOT/scripts/install_functions.sql
    ${my1} < $DRE_ROOT/scripts/trigger_fun.sql
fi
if [ $? != 0 ];then
    exit 1
fi


${my1} -se  "start slave;" 2> /dev/null
if [ $? != 0 ];then
	LOG_WARNING "start slave failed... " $LINENO
fi
