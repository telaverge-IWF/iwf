#include <MysqlInterface.h>

using namespace std;

mysql_cli_interface::mysql_cli_interface(string sHostName,string sUserName,string sPassword,string sDataBase)
{
	PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
	try 
	{
		driver = sql::mysql::get_driver_instance();

		connection_properties["hostName"]=sHostName;
        	connection_properties["userName"]=sUserName;
        	connection_properties["password"]=sPassword;
        	connection_properties["OPT_RECONNECT"]=true;
        	connection_properties["schema"]=sDataBase;
	
	        con = driver->connect(connection_properties);

		set_AvaMgrConfig_Set_TableName();
		set_AvaMgrConfig_Set_FieldName();

		set_DefaultRoute_Set_TableName();
		set_DefaultRoute_Set_FieldName();

		set_DynamicDiscovery_Set_TableName();
		set_DynamicDiscovery_Set_FieldName();

		set_LocalHostConfig_Set_TableName();
		set_LocalHostConfig_Set_FieldName();

		set_PeerGlobalConfig_Set_TableName();
		set_PeerGlobalConfig_Set_FieldName();

		set_Peer_Set_TableName();
		set_Peer_Set_FieldName();

		set_PeerTimers_Set_TableName();
		set_PeerTimers_Set_FieldName();

		set_RealmRouting_Set_TableName();
		set_RealmRouting_Set_FieldName();

		set_RepMgrConfig_Set_TableName();
		set_RepMgrConfig_Set_FieldName();

		set_Asf_Set_TableName();
	        set_Asf_Set_FieldName();

		set_AsfConfig_Set_TableName();
        	set_AsfConfig_Set_FieldName();

		set_AsfFeature_Set_TableName();
        	set_AsfFeature_Set_FieldName();

		set_User_Set_TableName();
		set_User_Set_FieldName();

		set_PeerDictionaryMap_Set_TableName();
		set_PeerDictionaryMap_Set_FieldName();


	}	
	catch (sql::SQLException &e) 
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;

		if(e.getErrorCode() == 1049)
		{
			PRINTF("DIAMETRIQ Database is not created. \n exiting!!!!");	
			exit(0);
		}

		if(e.getErrorCode() == 2003)
		{
			PRINTF("Mysql Server is not running. \n exiting!!!!");	
			exit(0);
		}

	}

	PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
}
ConfigReqType_e mysql_cli_interface::mysql_Check_Modifcation(drePayload *payloadConfigReq,dreTableName_e dreTableName)
{
	sql::PreparedStatement 			*pPreStmt = NULL;
	sql::ResultSet 				*pRes = NULL;

	AvaMgrConfigPayload			*avaMgrConfigReq;
	DreDefaultRoutePayload			*dreDefaultRouteConfigReq;
	DreDynamicDiscoveryConfigPayload	*dreDynamicDiscoveryConfigReq;
	DreLocalHostPayload			*dreLocalHostConfigReq;
	DrePeerGlobalConfigPayload		*drePeerGlobalConfigReq;
	DrePeerPayload				*drePeerConfigReq;
	DrePeerTimersConfigPayload		*drePeerTimersConfigReq;
	DreRealmRoutingPayload			*dreRealmRoutingConfigReq;
	RepMgrReplStateConfigPayload		*repMgrReplStateConfigReq;
	DrePeerPayloadAndTimerPayload		*drePeerAndTimerConfigPayload;
	DreUserConfigPayload			*dreUserConfigReq;
	DreASFAppGroupPayload			*dreAsfReq;
    	DreASFConfigPayload	                *dreASFConfigPayload;
	char 					sPreStatement[MAX_STATEMENT_SIZE] = {0};


	PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	

	switch(dreTableName)
	{
		case DRE_AVAILABILITY_MANAGER_CONFIG_T:                                                          

			avaMgrConfigReq 		= (AvaMgrConfigPayload *)payloadConfigReq;
			sql_AvaMgrConfig_Create_Check_Modifcation_Query(avaMgrConfigReq,sPreStatement);

			break;
		case DRE_DEFAULT_ROUTE_T:

			dreDefaultRouteConfigReq 	= (DreDefaultRoutePayload *)payloadConfigReq;
			sql_DefaultRoute_Create_Check_Modifcation_Query(dreDefaultRouteConfigReq,sPreStatement);

			break;                                                  
		case DRE_DYNAMIC_DISCOVERY_T:

			dreDynamicDiscoveryConfigReq 	= (DreDynamicDiscoveryConfigPayload *)payloadConfigReq;
			sql_DynamicDiscovery_Create_Check_Modifcation_Query(dreDynamicDiscoveryConfigReq,sPreStatement);

			break;
		case DRE_LOCAL_HOST_CONFIG_T:

			dreLocalHostConfigReq 		= (DreLocalHostPayload *)payloadConfigReq;
			sql_LocalHostConfig_Create_Check_Modifcation_Query(dreLocalHostConfigReq,sPreStatement);

			break;
		case DRE_PEER_GLOBAL_CONFIG_T: 

			drePeerGlobalConfigReq 		= (DrePeerGlobalConfigPayload *)payloadConfigReq;
			sql_PeerGlobalConfig_Create_Check_Modifcation_Query(drePeerGlobalConfigReq,sPreStatement);

			break;
		case DRE_PEER_T:

			drePeerAndTimerConfigPayload 	= (DrePeerPayloadAndTimerPayload *)payloadConfigReq;
			drePeerConfigReq 		= &drePeerAndTimerConfigPayload->drePeerPayload;
			sql_Peer_Create_Check_Modifcation_Query(drePeerConfigReq,sPreStatement);

			break;
		case DRE_PEER_TIMERS_T:

			drePeerAndTimerConfigPayload 	= (DrePeerPayloadAndTimerPayload *)payloadConfigReq;
			drePeerTimersConfigReq 		= &drePeerAndTimerConfigPayload->drePeerTimersConfigPayload;
			sql_PeerTimers_Create_Check_Modifcation_Query(drePeerTimersConfigReq,sPreStatement);

			break;
		case DRE_REALM_ROUTING_T:

			dreRealmRoutingConfigReq 	= (DreRealmRoutingPayload *)payloadConfigReq;
			sql_RealmRouting_Create_Check_Modifcation_Query(dreRealmRoutingConfigReq,sPreStatement);

			break;
		case DRE_REPLICATION_MANAGER_CONFIG_T:

			repMgrReplStateConfigReq 	= (RepMgrReplStateConfigPayload*)payloadConfigReq;
			sql_RepMgrConfig_Create_Check_Modifcation_Query(repMgrReplStateConfigReq,sPreStatement);

			break;
		case DRE_USER_T:

			dreUserConfigReq 		= (DreUserConfigPayload *)payloadConfigReq;
			sql_User_Create_Check_Modifcation_Query(dreUserConfigReq,sPreStatement);

			break;
		case DRE_ASF_T:

			dreAsfReq                = (DreASFAppGroupPayload *)payloadConfigReq;
                        sql_Asf_Create_Check_Modifcation_Query(dreAsfReq,sPreStatement);
			
			break;
		case DRE_ASFCONFIG_T:

                        dreASFConfigPayload = (DreASFConfigPayload*)payloadConfigReq;
                        sql_AsfConfig_Create_Check_Modifcation_Query(dreASFConfigPayload,sPreStatement);

                        break;
		case DRE_ASFFEATURE_T:
                
                        dreASFConfigPayload = (DreASFConfigPayload*)payloadConfigReq;
                        sql_AsfFeature_Create_Check_Modifcation_Query(dreASFConfigPayload,sPreStatement);
        
                        break;
		case DRE_PEER_DICT_MAP_T:
			drePeerConfigReq = (DrePeerPayload *)payloadConfigReq;
			sql_PeerDictionaryMap_Create_Check_Modifcation_Query(drePeerConfigReq, sPreStatement);
			break;


		default:
	        PRINTF("%s:%d Default\n",__FUNCTION__,__LINE__);	
			break;
	}


	try
	{
		PRINTF("Query Statement: %s\n",sPreStatement);
		pPreStmt 	= con->prepareStatement(sPreStatement);
		pRes 		= pPreStmt->executeQuery();
		if(pRes->rowsCount() == 0)
		{
			PRINTF("%s:%d Count = %lu\n",__FUNCTION__,__LINE__,pRes->rowsCount());	
			delete pRes;
			delete pPreStmt;
			return DRE_DB_ADD;
		}
		
	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		if(pRes != NULL)
			delete pRes;
		if(pPreStmt != NULL)
			delete pPreStmt;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_ERR;
	}
	
	PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
	return DRE_DB_MOD;	
}

DbStatus_e mysql_cli_interface::mysql_Add_Row(drePayload *payloadConfigReq,dreTableName_e dreTableName)
{
	char 					sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::Statement 				*pStmt = NULL;


	AvaMgrConfigPayload			*avaMgrConfigReq;
	DreDefaultRoutePayload			*dreDefaultRouteConfigReq;
	DreDynamicDiscoveryConfigPayload	*dreDynamicDiscoveryConfigReq;
	DreLocalHostPayload			*dreLocalHostConfigReq;
	DrePeerGlobalConfigPayload		*drePeerGlobalConfigReq;
	DrePeerPayload				*drePeerConfigReq;
	DrePeerTimersConfigPayload		*drePeerTimersConfigReq;
	DreRealmRoutingPayload			*dreRealmRoutingConfigReq;
	RepMgrReplStateConfigPayload		*repMgrReplStateConfigReq;
	DrePeerPayloadAndTimerPayload		*drePeerAndTimerConfigPayload;
	DreUserConfigPayload			*dreUserConfigReq;
	DreASFAppGroupPayload			*dreAsfReq;
    	DreASFConfigPayload	                *dreASFConfigPayload;

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	switch(dreTableName)
	{
		case DRE_AVAILABILITY_MANAGER_CONFIG_T:                                                          

			avaMgrConfigReq 		= (AvaMgrConfigPayload *)payloadConfigReq;
			sql_AvaMgrConfig_Create_Add_Query(avaMgrConfigReq,sStatement);

			break;
		case DRE_DEFAULT_ROUTE_T:

			dreDefaultRouteConfigReq 	= (DreDefaultRoutePayload *)payloadConfigReq;
			sql_DefaultRoute_Create_Add_Query(dreDefaultRouteConfigReq,sStatement);

			break;                                                  
		case DRE_DYNAMIC_DISCOVERY_T:

			dreDynamicDiscoveryConfigReq 	= (DreDynamicDiscoveryConfigPayload *)payloadConfigReq;
			sql_DynamicDiscovery_Create_Add_Query(dreDynamicDiscoveryConfigReq,sStatement);

			break;
		case DRE_LOCAL_HOST_CONFIG_T:      

			dreLocalHostConfigReq 		= (DreLocalHostPayload *)payloadConfigReq;
			sql_LocalHostConfig_Create_Add_Query(dreLocalHostConfigReq,sStatement);

			break;
		case DRE_PEER_GLOBAL_CONFIG_T: 

			drePeerGlobalConfigReq 		= (DrePeerGlobalConfigPayload *)payloadConfigReq;
			sql_PeerGlobalConfig_Create_Add_Query(drePeerGlobalConfigReq,sStatement);

			break;
		case DRE_PEER_T:

			drePeerAndTimerConfigPayload 	= (DrePeerPayloadAndTimerPayload *)payloadConfigReq;
			drePeerConfigReq 		= &drePeerAndTimerConfigPayload->drePeerPayload;
			sql_Peer_Create_Add_Query(drePeerConfigReq,sStatement);

			break;
		case DRE_PEER_TIMERS_T:

			drePeerAndTimerConfigPayload 	= (DrePeerPayloadAndTimerPayload *)payloadConfigReq;
			drePeerTimersConfigReq 		= &drePeerAndTimerConfigPayload->drePeerTimersConfigPayload;
			sql_PeerTimers_Create_Add_Query(drePeerTimersConfigReq,sStatement);

			break;
		case DRE_REALM_ROUTING_T:

			dreRealmRoutingConfigReq 	= (DreRealmRoutingPayload *)payloadConfigReq;
			sql_RealmRouting_Create_Add_Query(dreRealmRoutingConfigReq,sStatement);

			break;
		case DRE_REPLICATION_MANAGER_CONFIG_T:

			repMgrReplStateConfigReq 	= (RepMgrReplStateConfigPayload*)payloadConfigReq;
			sql_RepMgrConfig_Create_Add_Query(repMgrReplStateConfigReq,sStatement);

			break;
		case DRE_USER_T:

			dreUserConfigReq 		= (DreUserConfigPayload *)payloadConfigReq;
			sql_User_Create_Add_Query(dreUserConfigReq,sStatement);

			break;
		 case DRE_ASF_T:

                        dreAsfReq                = (DreASFAppGroupPayload *)payloadConfigReq;
                        sql_Asf_Create_Add_Query(dreAsfReq,sStatement);

                        break;
		 case DRE_ASFCONFIG_T:

                        dreASFConfigPayload = (DreASFConfigPayload*)payloadConfigReq;
                        sql_AsfConfig_Create_Add_Query(dreASFConfigPayload,sStatement);

                        break;

 		case DRE_ASFFEATURE_T:

                        dreASFConfigPayload = (DreASFConfigPayload*)payloadConfigReq;
                        sql_AsfFeature_Create_Add_Query(dreASFConfigPayload,sStatement);

                        break;

		case DRE_PEER_DICT_MAP_T:
			drePeerConfigReq = (DrePeerPayload *)payloadConfigReq;
			sql_PeerDictionaryMap_Create_Add_Query(drePeerConfigReq, sStatement);
			break;


		default:
	        PRINTF("%s:%d Default\n",__FUNCTION__,__LINE__);	
			break;
	
	}

	try
	{
		PRINTF("Query Statement: %s\n",sStatement);
		pStmt 	= con->createStatement();
		pStmt->execute(sStatement);
		delete pStmt;
		PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
		
	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		if(pStmt != NULL)
			delete pStmt;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}

	return DRE_DB_SUCCESS;
}

DbStatus_e mysql_cli_interface::mysql_Delete_Row(drePayload *payloadConfigReq,dreTableName_e dreTableName)
{
	char 					sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::Statement 				*pStmt = NULL;


	AvaMgrConfigPayload			*avaMgrConfigReq;
	DreDefaultRoutePayload			*dreDefaultRouteConfigReq;
	DreDynamicDiscoveryConfigPayload	*dreDynamicDiscoveryConfigReq;
	DreLocalHostPayload			*dreLocalHostConfigReq;
	DrePeerGlobalConfigPayload		*drePeerGlobalConfigReq;
	DrePeerPayload				*drePeerConfigReq;
	DrePeerTimersConfigPayload		*drePeerTimersConfigReq;
	DreRealmRoutingPayload			*dreRealmRoutingConfigReq;
	RepMgrReplStateConfigPayload		*repMgrReplStateConfigReq;
	DrePeerPayloadAndTimerPayload		*drePeerAndTimerConfigPayload;
	DreUserConfigPayload			*dreUserConfigReq;
	DreASFAppGroupPayload			*dreAsfReq;
    	DreASFConfigPayload                 	*dreASFConfigPayload;
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	switch(dreTableName)
	{
		case DRE_AVAILABILITY_MANAGER_CONFIG_T:                                                          

			avaMgrConfigReq 		= (AvaMgrConfigPayload *)payloadConfigReq;
			sql_AvaMgrConfig_Create_Delete_Query(avaMgrConfigReq,sStatement);

			break;
		case DRE_DEFAULT_ROUTE_T:

			dreDefaultRouteConfigReq 	= (DreDefaultRoutePayload *)payloadConfigReq;
			sql_DefaultRoute_Create_Delete_Query(dreDefaultRouteConfigReq,sStatement);

			break;                                                  
		case DRE_DYNAMIC_DISCOVERY_T:

			dreDynamicDiscoveryConfigReq 	= (DreDynamicDiscoveryConfigPayload *)payloadConfigReq;
			sql_DynamicDiscovery_Create_Delete_Query(dreDynamicDiscoveryConfigReq,sStatement);

			break;
		case DRE_LOCAL_HOST_CONFIG_T:      

			dreLocalHostConfigReq 		= (DreLocalHostPayload *)payloadConfigReq;
			sql_LocalHostConfig_Create_Delete_Query(dreLocalHostConfigReq,sStatement);

			break;
		case DRE_PEER_GLOBAL_CONFIG_T:

			drePeerGlobalConfigReq 		= (DrePeerGlobalConfigPayload *)payloadConfigReq;
			sql_PeerGlobalConfig_Create_Delete_Query(drePeerGlobalConfigReq,sStatement);

			break;
		case DRE_PEER_T:

			drePeerAndTimerConfigPayload 	= (DrePeerPayloadAndTimerPayload *)payloadConfigReq;
			drePeerConfigReq = &drePeerAndTimerConfigPayload->drePeerPayload;
			sql_Peer_Create_Delete_Query(drePeerConfigReq,sStatement);

			break;
		case DRE_PEER_TIMERS_T:

			drePeerAndTimerConfigPayload 	= (DrePeerPayloadAndTimerPayload *)payloadConfigReq;
			drePeerTimersConfigReq 		= &drePeerAndTimerConfigPayload->drePeerTimersConfigPayload;
			sql_PeerTimers_Create_Delete_Query(drePeerTimersConfigReq,sStatement);

			break;
		case DRE_REALM_ROUTING_T:

			dreRealmRoutingConfigReq 	= (DreRealmRoutingPayload *)payloadConfigReq;
			sql_RealmRouting_Create_Delete_Query(dreRealmRoutingConfigReq,sStatement);

			break;
		case DRE_REPLICATION_MANAGER_CONFIG_T:

			repMgrReplStateConfigReq 	= (RepMgrReplStateConfigPayload*)payloadConfigReq;
			sql_RepMgrConfig_Create_Delete_Query(repMgrReplStateConfigReq,sStatement);

			break;
		case DRE_USER_T:

			dreUserConfigReq 	= (DreUserConfigPayload *)payloadConfigReq;
			sql_User_Create_Delete_Query(dreUserConfigReq,sStatement);

			break;
		 case DRE_ASF_T:

                        dreAsfReq        = (DreASFAppGroupPayload *)payloadConfigReq;
                        sql_Asf_Create_Delete_Query(dreAsfReq,sStatement);

                        break;
		case DRE_ASFCONFIG_T:

                        dreASFConfigPayload = (DreASFConfigPayload*)payloadConfigReq;
                        sql_AsfConfig_Create_Delete_Query(dreASFConfigPayload,sStatement);

                        break;
		case DRE_ASFFEATURE_T:

                        dreASFConfigPayload = (DreASFConfigPayload*)payloadConfigReq;
                        sql_AsfFeature_Create_Delete_Query(dreASFConfigPayload,sStatement);

                        break;

		case DRE_PEER_DICT_MAP_T:
			drePeerConfigReq = (DrePeerPayload *)payloadConfigReq;
			sql_PeerDictionaryMap_Create_Delete_Query(drePeerConfigReq, sStatement);
			break;
		default:
		        PRINTF("%s:%d Default\n",__FUNCTION__,__LINE__);	
			break;
	
	}


	try
	{
		PRINTF("Query Statement: %s\n",sStatement);
		pStmt 	= con->createStatement();
		pStmt->execute(sStatement);
		delete pStmt;

		PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		if (pStmt != NULL)
			delete pStmt;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}

	return DRE_DB_SUCCESS;
}

DbStatus_e mysql_cli_interface::mysql_Get_Record(drePayload *payloadConfig ,GetConfigRsp *resultSet,dreTableName_e dreTableName,int table_number)
{

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	char 			                sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::PreparedStatement 	        	*pPreStmt = NULL;
	sql::ResultSet 		            	*pRes = NULL;

	AvaMgrConfigPayload			*avaMgrConfigReq;
	DreDefaultRoutePayload			*dreDefaultRouteConfigReq;
	DreDynamicDiscoveryConfigPayload	*dreDynamicDiscoveryConfigReq;
	DreLocalHostPayload			*dreLocalHostConfigReq;
	DrePeerGlobalConfigPayload		*drePeerGlobalConfigReq;
	DrePeerPayload				*drePeerConfigReq;
	DrePeerTimersConfigPayload		*drePeerTimersConfigReq;
	DreRealmRoutingPayload			*dreRealmRoutingConfigReq;
	RepMgrReplStateConfigPayload		*repMgrReplStateConfigReq;
	DrePeerPayloadAndTimerPayload		*drePeerAndTimerConfigPayload;
	DreUserConfigPayload			*dreUserConfigReq;
	DreASFAppGroupPayload			*dreAsfReq;
    	DreASFConfigPayload                 	*dreASFConfigPayload;

	DbStatus_e				iReturn;


	PRINTF("%s:%d table_number = %d\n",__FUNCTION__,__LINE__,table_number);

	switch(dreTableName)
	{
		case DRE_AVAILABILITY_MANAGER_CONFIG_T:

			avaMgrConfigReq 			= (AvaMgrConfigPayload *)payloadConfig;
			sql_AvaMgrConfig_Create_Select_Query(avaMgrConfigReq,sStatement);
			resultSet->datatype_names[table_number] = DRE_AVAILABILITY_MANAGER_CONFIG;

			break;
		case DRE_DEFAULT_ROUTE_T:

			dreDefaultRouteConfigReq 		= (DreDefaultRoutePayload *)payloadConfig;
			sql_DefaultRoute_Create_Select_Query(dreDefaultRouteConfigReq,sStatement);
			resultSet->datatype_names[table_number] = DRE_DEFAULT_ROUTE;

			break;                                                  
		case DRE_DYNAMIC_DISCOVERY_T:

			dreDynamicDiscoveryConfigReq 		= (DreDynamicDiscoveryConfigPayload *)payloadConfig;
			sql_DynamicDiscovery_Create_Select_Query(dreDynamicDiscoveryConfigReq,sStatement);
			resultSet->datatype_names[table_number] = DRE_DYNAMIC_DISCOVERY;	

			break;
		case DRE_LOCAL_HOST_CONFIG_T:      

			dreLocalHostConfigReq 			= (DreLocalHostPayload *)payloadConfig;
			sql_LocalHostConfig_Create_Select_Query(dreLocalHostConfigReq,sStatement);
			resultSet->datatype_names[table_number] = DRE_LOCAL_HOST_CONFIG;	

			break;
		case DRE_PEER_GLOBAL_CONFIG_T:

			drePeerGlobalConfigReq 			= (DrePeerGlobalConfigPayload *)payloadConfig;
			sql_PeerGlobalConfig_Create_Select_Query(drePeerGlobalConfigReq,sStatement);
			resultSet->datatype_names[table_number] = DRE_PEER_GLOBAL_CONFIG;	

			break;
		case DRE_PEER_T:

			drePeerAndTimerConfigPayload 		= (DrePeerPayloadAndTimerPayload *)payloadConfig;
			drePeerConfigReq = &drePeerAndTimerConfigPayload->drePeerPayload;
			sql_Peer_Create_Select_Query(drePeerConfigReq,sStatement);
			resultSet->datatype_names[table_number] = DRE_PEER_AND_TIMER;	

			break;
		case DRE_PEER_TIMERS_T:

			drePeerAndTimerConfigPayload 		= (DrePeerPayloadAndTimerPayload *)payloadConfig;
			drePeerTimersConfigReq = &drePeerAndTimerConfigPayload->drePeerTimersConfigPayload;
			sql_PeerTimers_Create_Select_Query(drePeerTimersConfigReq,sStatement);
			resultSet->datatype_names[table_number] = DRE_PEER_AND_TIMER;	

			break;
		case DRE_REALM_ROUTING_T:

			dreRealmRoutingConfigReq 		= (DreRealmRoutingPayload *)payloadConfig;
			sql_RealmRouting_Create_Select_Query(dreRealmRoutingConfigReq,sStatement);
			resultSet->datatype_names[table_number] = DRE_REALM_ROUTING;	

			break;
		case DRE_REPLICATION_MANAGER_CONFIG_T:

			repMgrReplStateConfigReq 		= (RepMgrReplStateConfigPayload*)payloadConfig;
			sql_RepMgrConfig_Create_Select_Query(repMgrReplStateConfigReq,sStatement);
			resultSet->datatype_names[table_number] = DRE_REPLICATION_MANAGER_CONFIG;	

			break;
		case DRE_USER_T:

			dreUserConfigReq 			= (DreUserConfigPayload *)payloadConfig;
			sql_User_Create_Select_Query(dreUserConfigReq,sStatement);
			resultSet->datatype_names[table_number] = DRE_USER;	

			break;
		case DRE_ASF_T:

                        dreAsfReq                        = (DreASFAppGroupPayload *)payloadConfig;
                        sql_Asf_Create_Select_Query(dreAsfReq,sStatement);
                        resultSet->datatype_names[table_number] = DRE_ASF;

                        break;
		case DRE_ASFCONFIG_T:

                        dreASFConfigPayload = (DreASFConfigPayload*)payloadConfig;
                        sql_AsfConfig_Create_Select_Query(dreASFConfigPayload,sStatement);
                        resultSet->datatype_names[table_number] = DRE_ASFCONFIG;

                        break;
		case DRE_ASFFEATURE_T:

                        dreASFConfigPayload = (DreASFConfigPayload*)payloadConfig;
                        sql_AsfFeature_Create_Select_Query(dreASFConfigPayload,sStatement);
                        resultSet->datatype_names[table_number] = DRE_ASFFEATURE;

                        break;

		case DRE_PEER_DICT_MAP_T:
			drePeerConfigReq = (DrePeerPayload *)payloadConfig;
			sql_PeerDictionaryMap_Create_Select_Query(drePeerConfigReq, sStatement);
                        resultSet->datatype_names[table_number] = DRE_PEER_DICT_MAP;
			break;


		default:
	        PRINTF("%s:%d Default\n",__FUNCTION__,__LINE__);	
			break;

	}


	try
	{
		PRINTF("Query Statement: %s\n",sStatement);
		pPreStmt 	= con->prepareStatement(sStatement);
		pRes 		= pPreStmt->executeQuery();
		if(pRes->rowsCount() == 0)
		{
			resultSet->record_count[table_number] 	= 0;
			iReturn = DRE_DB_SUCCESS;
		}
		else
		{
			resultSet->record_count[table_number] 	= pRes->rowsCount();
			iReturn = mysql_Fill_Record(resultSet,dreTableName,pRes,table_number);   
		}
		delete pPreStmt;
		delete pRes;

		PRINTF("%s:%d table_number = %d Record Count = %d \n",__FUNCTION__,__LINE__,table_number,resultSet->record_count[table_number]);
	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		if(pPreStmt != NULL)
			delete pPreStmt;
		if(pRes != NULL)
			delete pRes;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return iReturn;
}

DbStatus_e mysql_cli_interface::mysql_Fill_PeerGlobalConfig_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number)

{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	DrePeerGlobalConfigPayload 	*drePeerGlobalConfigPayload; 
	drePeerGlobalConfigPayload 	= (DrePeerGlobalConfigPayload*)resultSet->payload[table_number];
	int iCount      		= 0;

	try 
	{

		while(pRes->next())
		{
			drePeerGlobalConfigPayload[iCount].PeerGlobalConfigKeyInfo.ComponentID 		= pRes->getInt64("ComponentID");
			drePeerGlobalConfigPayload[iCount].PeerGlobalConfigInfo.DiscoveryInterval 	= pRes->getInt("DiscoveryInterval");
			
			iCount++;
		}

	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return DRE_DB_SUCCESS;
}

DbStatus_e mysql_cli_interface::mysql_Fill_RepMgrConfig_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number)

{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	RepMgrReplStateConfigPayload 		*repMgrReplStateConfigPayload; 
	repMgrReplStateConfigPayload 		= (RepMgrReplStateConfigPayload*)resultSet->payload[table_number];
	int iCount      			= 0;

	try 
	{

		while(pRes->next())
		{
			repMgrReplStateConfigPayload[iCount].ReplStateKeyInfo.ComponentID 		= pRes->getInt("ComponentID");
			repMgrReplStateConfigPayload[iCount].ReplStateConfigInfo.ReplicationState 	= pRes->getInt("ReplicationState");
			
			iCount++;
		}

	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return DRE_DB_SUCCESS;
}

DbStatus_e mysql_cli_interface::mysql_Fill_PeerTimers_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number)

{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	DrePeerPayloadAndTimerPayload 	*drePeerAndTimerConfigPayload; 
	drePeerAndTimerConfigPayload 	= (DrePeerPayloadAndTimerPayload*)resultSet->payload[table_number];
	int iCount      		= 0;

	try 
	{

		while(pRes->next())
		{
			strcpy(drePeerAndTimerConfigPayload[iCount].drePeerTimersConfigPayload.PeerTimersKeyInfo.peerHostNames, (pRes->getString("peerHostIdentity"))->c_str());
			strcpy(drePeerAndTimerConfigPayload[iCount].drePeerTimersConfigPayload.PeerTimersKeyInfo.realmName, (pRes->getString("RealmName"))->c_str());

			drePeerAndTimerConfigPayload[iCount].drePeerTimersConfigPayload. PeerTimersConfigInfo.watchdogValue 	= pRes->getInt("WdVal");
			drePeerAndTimerConfigPayload[iCount].drePeerTimersConfigPayload. PeerTimersConfigInfo.TCValue 		= pRes->getInt("TcVal");
			drePeerAndTimerConfigPayload[iCount].drePeerTimersConfigPayload. PeerTimersConfigInfo.expiryValue 	= pRes->getInt("Eval");

			iCount++;
		}

	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return DRE_DB_SUCCESS;
}

DbStatus_e mysql_cli_interface::mysql_Fill_RealmRouting_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number)
{
	DreRealmRoutingPayload 	*dreRealmPayload;
	dreRealmPayload 	= (DreRealmRoutingPayload*)resultSet->payload[table_number];
	int iCount      	= 0;

	try 
	{

		while(pRes->next())
		{
			strcpy(dreRealmPayload[iCount].realmKeyInfo.RealmName, (pRes->getString("RealmName"))->c_str());
			strcpy(dreRealmPayload[iCount].realmKeyInfo.PeerHostId, (pRes->getString("PeerHostIdentity"))->c_str());
			dreRealmPayload[iCount].realmKeyInfo.AppId    		= pRes->getInt64("ApplicationID");

			dreRealmPayload[iCount].realmInfo.LocalAction 		= pRes->getInt("LocalAction");
			dreRealmPayload[iCount].realmInfo.VendorID 		= pRes->getInt64("VendorID");
			dreRealmPayload[iCount].realmInfo.Priority 		= pRes->getInt("Priority");
			dreRealmPayload[iCount].realmInfo.NodeDiscovery 	= pRes->getInt("NodeDiscovery");
			dreRealmPayload[iCount].realmInfo.RedirectHostUsage 	= pRes->getInt("RedirectHostUsage");
			dreRealmPayload[iCount].realmInfo.RedirectMaxCacheTime 	= pRes->getInt("RedirectMaxCacheTime");

			iCount++;
		}

	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return DRE_DB_SUCCESS;




}

DbStatus_e mysql_cli_interface::mysql_Fill_LocalHostConfig_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number)
{
	DreLocalHostPayload 	*dreLocalHostPayload;

	dreLocalHostPayload 	= (DreLocalHostPayload*)resultSet->payload[table_number];
	int iCount      	= 0;

	try 
	{

		while(pRes->next())
		{
			strcpy(dreLocalHostPayload[iCount].LocalHostKeyInfo.HostName, (pRes->getString("HostName"))->c_str());
			strcpy(dreLocalHostPayload[iCount].LocalHostKeyInfo.RealmName, (pRes->getString("RealmName"))->c_str());


			strcpy(dreLocalHostPayload[iCount].LocalHostTransportInfo.IpAddr, (pRes->getString("IPAddress"))->c_str());
			dreLocalHostPayload[iCount].LocalHostTransportInfo.portno 		= pRes->getInt("Port");	
			dreLocalHostPayload[iCount].LocalHostTransportInfo.transportType 	= pRes->getInt("TransportType");	

			dreLocalHostPayload[iCount].LocalHostAuthInfo.LifeTime 			= pRes->getInt64("AuthLifeTime");	
			dreLocalHostPayload[iCount].LocalHostAuthInfo.GraceTime 		= pRes->getInt64("AuthGraceTime");	
			dreLocalHostPayload[iCount].LocalHostAuthInfo.TimeOut 			= pRes->getInt64("AuthTimeOut");	

			dreLocalHostPayload[iCount].LocalHostAcctInfo.Interim 			= pRes->getInt64("AcctInterim");	
			dreLocalHostPayload[iCount].LocalHostAcctInfo.TimeOut 			= pRes->getInt64("AcctTimeOut");	

			iCount++;
		}

	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return DRE_DB_SUCCESS;



}

DbStatus_e mysql_cli_interface::mysql_Fill_DynamicDiscovery_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number)
{

	DreDynamicDiscoveryConfigPayload 	*dreDynamicDiscoveryPayload;

	dreDynamicDiscoveryPayload		= (DreDynamicDiscoveryConfigPayload*)resultSet->payload[table_number];
	int iCount      			= 0;

	try 
	{

		while(pRes->next())
		{
			strcpy(dreDynamicDiscoveryPayload[iCount].DynamicDiscoveryKeyInfo.RealmName, (pRes->getString("RealmName"))->c_str());

			strcpy(dreDynamicDiscoveryPayload[iCount].DynamicDiscoveryConfigInfo.peerHostNames, (pRes->getString("PeerHostIdentity"))->c_str());
			iCount++;
		}

	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return DRE_DB_SUCCESS;




}

DbStatus_e mysql_cli_interface::mysql_Fill_User_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number)
{

	DreUserConfigPayload 			*dreUserPayload;
    	std::istream                     	*blobstream;

	dreUserPayload				= (DreUserConfigPayload*)resultSet->payload[table_number];
	int iCount      			= 0;

	try 
	{

		while(pRes->next())
		{
			strcpy(dreUserPayload[iCount].UserKeyInfo.UserName, (pRes->getString("UserName"))->c_str());

			if(resultSet->cmd_id != C_cli_showuser_Id)
			{
				blobstream = pRes->getBlob("Password");
				blobstream->read((char *)dreUserPayload[iCount].UserConfigInfo.password,16);
			}
			else
			{
				memset(dreUserPayload[iCount].UserConfigInfo.password,1,sizeof(dreUserPayload[iCount].UserConfigInfo.password));
			}
			//			memcpy(dreUserPayload[iCount].UserConfigInfo.password, (pRes->getBlob("Password"))->c_str(),16);

			dreUserPayload[iCount].UserConfigInfo.privilege 			= pRes->getInt("Previlage");
			iCount++;
		}

	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return DRE_DB_SUCCESS;




}
DbStatus_e mysql_cli_interface::mysql_Fill_Asf_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number)
{
	DreASFAppGroupPayload *dreASFAppGroupPayload;

	dreASFAppGroupPayload = (DreASFAppGroupPayload*)resultSet->payload[table_number];
	int iCount              = 0;
	try
	{
		while(pRes->next())
		{
			 strcpy(dreASFAppGroupPayload[iCount].dreASFKeyInfo.GroupName, (pRes->getString("APP_GRP_NAME"))->c_str());
 			 dreASFAppGroupPayload[iCount].dreASFConfigInfo.priority                        = pRes->getInt("PRIORITY");
		 	 dreASFAppGroupPayload[iCount].dreASFConfigInfo.appType                         = pRes->getInt("IS_HOSTED_APP_GRP");
			 strcpy(dreASFAppGroupPayload[iCount].dreASFConfigInfo.lbAlgorithm, (pRes->getString("LB_METHOD"))->c_str());
			 dreASFAppGroupPayload[iCount].dreASFConfigInfo.maxAppInstances                 = pRes->getInt("MAX_APP_INSTANCES");
		}
	}
	 catch (sql::SQLException &e)
        {
                cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
                cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
                cout << ", SQLState: " << e.getSQLState() << " )" << endl;
                PRINTF("%s:%d\n",__FUNCTION__,__LINE__);
                return DRE_DB_FAIL;
        }

        PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
        return DRE_DB_SUCCESS;


}
DbStatus_e mysql_cli_interface::mysql_Fill_AsfConfig_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number)
{
        DreASFConfigPayload *dreASFConfigPayload;

        dreASFConfigPayload = (DreASFConfigPayload*)resultSet->payload[table_number];
        int iCount              = 0;
        try
        {
                while(pRes->next())
                {
                         dreASFConfigPayload[iCount].dreASFConfigKeyInfo.ComponentID                        = pRes->getInt("COMPONENT_ID");
                         dreASFConfigPayload[iCount].dreASFRespTimeout.responseTimeout                    = pRes->getInt("APP_RESPONSE_TIMEOUT");
                }
        }
         catch (sql::SQLException &e)
        {
                cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
                cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
                cout << ", SQLState: " << e.getSQLState() << " )" << endl;
                PRINTF("%s:%d\n",__FUNCTION__,__LINE__);
                return DRE_DB_FAIL;
        }

        PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
        return DRE_DB_SUCCESS;


}
DbStatus_e mysql_cli_interface::mysql_Fill_AsfFeature_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number)
{
        DreASFConfigPayload *dreASFConfigPayload;

        dreASFConfigPayload = (DreASFConfigPayload*)resultSet->payload[table_number];
        int iCount              = 0;
        try
        {
                while(pRes->next())
                {
                         dreASFConfigPayload[iCount].dreASFConfigKeyInfo.ComponentID                        = pRes->getInt("COMPONENT_ID");
                         dreASFConfigPayload[iCount].dreASFStatus.ASFStatus                    = pRes->getInt("ENABLE_ASF");
  
               		dreASFConfigPayload[iCount].dreASFStatus.ERLBFStatus                    = pRes->getInt("ENABLE_ERLBF");

                }
        }
         catch (sql::SQLException &e)
        {
                cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
                cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
                cout << ", SQLState: " << e.getSQLState() << " )" << endl;
                PRINTF("%s:%d\n",__FUNCTION__,__LINE__);
                return DRE_DB_FAIL;
        }

        PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
        return DRE_DB_SUCCESS;


}


DbStatus_e mysql_cli_interface::mysql_Fill_DefaultRoute_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number)
{
	DreDefaultRoutePayload 	*dreDefaultRoutePayload;

	dreDefaultRoutePayload 	= (DreDefaultRoutePayload*)resultSet->payload[table_number];
	int iCount      	= 0;

	try 
	{

		while(pRes->next())
		{
			strcpy(dreDefaultRoutePayload[iCount].defaultRouteKeyInfo.RealmName, (pRes->getString("RealmName"))->c_str());

			strcpy(dreDefaultRoutePayload[iCount].defaultRouteInfo.PeerHostIds, (pRes->getString("PeerHostIdentity"))->c_str());
			iCount++;
		}

	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return DRE_DB_SUCCESS;


}


DbStatus_e mysql_cli_interface::mysql_Fill_AvaMgrConfig_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number)
{
	AvaMgrConfigPayload 	*avaMgrConfigPayload;	

	avaMgrConfigPayload 	= (AvaMgrConfigPayload*)resultSet->payload[table_number];
	int iCount      	= 0;

	try 
	{

		while(pRes->next())
		{
			avaMgrConfigPayload[iCount].avaMgrConfigKey.ComponentID 			= pRes->getInt("ComponentID");
			avaMgrConfigPayload[iCount].avaMgrConfigInfo.PingPeriodicity               = pRes->getInt64("PingPeriodicity");
			avaMgrConfigPayload[iCount].avaMgrConfigInfo.PingPeriodicityForArbitrator 		= pRes->getInt64("PingPeriodicityForArbitrator");	
			avaMgrConfigPayload[iCount].avaMgrConfigInfo.VirtualInterfaceActivationTime 		= pRes->getInt64("VirtualInterfaceActivationTime");	
			avaMgrConfigPayload[iCount].avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeer 	= pRes->getInt64("NumberOfConsecutivePingAckRcvFailuresFromPeer");	
			avaMgrConfigPayload[iCount].avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitrator 	= pRes->getInt64("NumberOfConsecutivePingAckRcvFailuresFromArbitrator");	
			avaMgrConfigPayload[iCount].avaMgrConfigInfo.ProcessRestartMaximumAllowedInterval	= pRes->getInt64("ProcessRestartMaxAllowedInterval");	
			avaMgrConfigPayload[iCount].avaMgrConfigInfo.ProcessRestartMaximumAllowedCount 	= pRes->getInt64("ProcessRestartMaxAllowedCount");	
			 avaMgrConfigPayload[iCount].avaMgrConfigInfo.UseIpV6                         = pRes->getInt("UseIpV6");
			strcpy(avaMgrConfigPayload[iCount].avaMgrConfigInfo.PrimaryVirtualIpAddress, (pRes->getString("PrimaryVirtualIpAddress"))->c_str());
                        strcpy(avaMgrConfigPayload[iCount].avaMgrConfigInfo.SecondaryVirtualIpAddress, (pRes->getString("SecondaryVirtualIpAddress"))->c_str());
			strcpy(avaMgrConfigPayload[iCount].avaMgrConfigInfo.GatewayIpAddress, (pRes->getString("NearHopGatewayIpAddress"))->c_str());
			iCount++;
		}

	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return DRE_DB_SUCCESS;

}

DbStatus_e mysql_cli_interface::mysql_Fill_Peer_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number)
{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	DrePeerPayloadAndTimerPayload 	*drePeerAndTimerConfigPayload; 
	drePeerAndTimerConfigPayload	= (DrePeerPayloadAndTimerPayload*)resultSet->payload[table_number];
	int iCount      		= 0;

	try 
	{

		while(pRes->next())
		{
			strcpy(drePeerAndTimerConfigPayload[iCount].drePeerPayload.peerKeyInfo.HostName, (pRes->getString("PeerHostIdentity"))->c_str());
			strcpy(drePeerAndTimerConfigPayload[iCount].drePeerPayload.peerKeyInfo.RealmName, (pRes->getString("RealmName"))->c_str());
			strcpy(drePeerAndTimerConfigPayload[iCount].drePeerPayload.peerInfo.IpAddr, (pRes->getString("PeerIP"))->c_str());
			drePeerAndTimerConfigPayload[iCount].drePeerPayload.peerInfo.PortNumber 	= pRes->getInt("PeerPort");
			strcpy(drePeerAndTimerConfigPayload[iCount].drePeerPayload.peerInfo.AltHostName, (pRes->getString("AltPeerID"))->c_str());
			drePeerAndTimerConfigPayload[iCount].drePeerPayload.peerInfo.IsMate 		= pRes->getInt("isMate");
			drePeerAndTimerConfigPayload[iCount].drePeerPayload.peerInfo.TransportType 	= pRes->getInt("TransportType");
			drePeerAndTimerConfigPayload[iCount].drePeerPayload.peerInfo.TLS      = pRes->getInt("TLSEnabled");
			drePeerAndTimerConfigPayload[iCount].drePeerPayload.peerInfo.Enable_Status 	= pRes->getInt("Enable");

			drePeerAndTimerConfigPayload[iCount].drePeerPayload.peerSwitchingInfo.Failover 	= pRes->getInt("FailOverEnable");
			drePeerAndTimerConfigPayload[iCount].drePeerPayload.peerSwitchingInfo.Failback 	= pRes->getInt("FailBackEnable");
			iCount++;
		}

	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return DRE_DB_SUCCESS;
}


DbStatus_e mysql_cli_interface::mysql_Fill_PeerDictionaryMap_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number)
{
	DrePeerPayload *drePeerPayload;

	drePeerPayload = (DrePeerPayload*)resultSet->payload[table_number];
	int iCount      	= 0;
	int iFlag 		= 0;

	try 
	{

		while(pRes->next())
		{
			if(iCount >= MAX_DICTIONARY_NUM)
				break;
			if(iFlag == 0)
			{
				strcpy(drePeerPayload[iCount].peerDictionaryInfo.peerKeyInfo.RealmName, (pRes->getString("RealmName"))->c_str());

				strcpy(drePeerPayload[iCount].peerDictionaryInfo.peerKeyInfo.HostName, (pRes->getString("PeerHostIdentity"))->c_str());
			}	
			strcpy(drePeerPayload[0].peerDictionaryInfo.PeerDictionaryIds[iCount], (pRes->getString("DICTIONARY_ID"))->c_str())
			iCount++;
			iFlag = 1;
		}
		drePeerPayload[0].peerDictionaryInfo.num_dict = iCount;

	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return DRE_DB_SUCCESS;


}


DbStatus_e mysql_cli_interface::mysql_Fill_Record(GetConfigRsp *resultSet,dreTableName_e dreTableName,sql::ResultSet *pRes,int table_number)
{
    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
    DbStatus_e iReturn;

	switch(dreTableName)
	{
		case DRE_AVAILABILITY_MANAGER_CONFIG_T:
			iReturn = mysql_Fill_AvaMgrConfig_Record(resultSet,pRes,table_number);
			break;
		case DRE_DEFAULT_ROUTE_T:
			iReturn = mysql_Fill_DefaultRoute_Record(resultSet,pRes,table_number);
			break;                                                  
		case DRE_DYNAMIC_DISCOVERY_T:
			iReturn = mysql_Fill_DynamicDiscovery_Record(resultSet,pRes,table_number);
			break;
		case DRE_LOCAL_HOST_CONFIG_T:      
			iReturn = mysql_Fill_LocalHostConfig_Record(resultSet,pRes,table_number);
			break;
		case DRE_PEER_GLOBAL_CONFIG_T:
			iReturn = mysql_Fill_PeerGlobalConfig_Record(resultSet,pRes,table_number);
			break;
		case DRE_PEER_T:
			iReturn = mysql_Fill_Peer_Record(resultSet,pRes,table_number);
			break;
		case DRE_PEER_TIMERS_T:
			iReturn = mysql_Fill_PeerTimers_Record(resultSet,pRes,table_number);
			break;
		case DRE_REALM_ROUTING_T:
			iReturn = mysql_Fill_RealmRouting_Record(resultSet,pRes,table_number);
			break;
		case DRE_REPLICATION_MANAGER_CONFIG_T:
			iReturn = mysql_Fill_RepMgrConfig_Record(resultSet,pRes,table_number);
			break;
		case DRE_USER_T:
			iReturn = mysql_Fill_User_Record(resultSet,pRes,table_number);
			break;
		case DRE_ASF_T:
			iReturn = mysql_Fill_Asf_Record(resultSet,pRes,table_number);
                        break;
		case DRE_ASFCONFIG_T:
                        iReturn = mysql_Fill_AsfConfig_Record(resultSet,pRes,table_number);
                        break;
		case DRE_ASFFEATURE_T:
                        iReturn = mysql_Fill_AsfFeature_Record(resultSet,pRes,table_number);
                        break;
		case DRE_PEER_DICT_MAP_T:
                        iReturn = mysql_Fill_PeerDictionaryMap_Record(resultSet,pRes,table_number);
                        break;

		default:
			iReturn = DRE_DB_FAIL;
	        PRINTF("%s:%d Default\n",__FUNCTION__,__LINE__);	
			break;
	
	}
    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
    return iReturn;
}

DbStatus_e mysql_cli_interface::mysql_Modify_Row(drePayload *payloadConfigReq,dreTableName_e dreTableName)
{
	char 						sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::Statement 					*pStmt = NULL;


	AvaMgrConfigPayload				*avaMgrConfigReq;
	DreDefaultRoutePayload				*dreDefaultRouteConfigReq;
	DreDynamicDiscoveryConfigPayload		*dreDynamicDiscoveryConfigReq;
	DreLocalHostPayload				*dreLocalHostConfigReq;
	DrePeerGlobalConfigPayload			*drePeerGlobalConfigReq;
	DrePeerPayload					*drePeerConfigReq;
	DrePeerTimersConfigPayload			*drePeerTimersConfigReq;
	DreRealmRoutingPayload				*dreRealmRoutingConfigReq;
	RepMgrReplStateConfigPayload			*repMgrReplStateConfigReq;
	DrePeerPayloadAndTimerPayload			*drePeerAndTimerConfigPayload;
	DreUserConfigPayload				*dreUserConfigReq;
	DreASFAppGroupPayload				*dreAsfReq;
    	DreASFConfigPayload                     	*dreASFConfigPayload;

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	switch(dreTableName)
	{
		case DRE_AVAILABILITY_MANAGER_CONFIG_T:                                                          
			avaMgrConfigReq 		= (AvaMgrConfigPayload *)payloadConfigReq;
			if(sql_AvaMgrConfig_Check_All_Invalid(avaMgrConfigReq))
			{
				return DRE_DB_SUCCESS;
			}
			sql_AvaMgrConfig_Create_Mod_Query(avaMgrConfigReq,sStatement);
			break;
		case DRE_DEFAULT_ROUTE_T:
			dreDefaultRouteConfigReq 	= (DreDefaultRoutePayload *)payloadConfigReq;
			if(sql_DefaultRoute_Check_All_Invalid(dreDefaultRouteConfigReq))
			{
				return DRE_DB_SUCCESS;
			}
			sql_DefaultRoute_Create_Mod_Query(dreDefaultRouteConfigReq,sStatement);
			break;                                                  
		case DRE_DYNAMIC_DISCOVERY_T:
			dreDynamicDiscoveryConfigReq 	= (DreDynamicDiscoveryConfigPayload *)payloadConfigReq;
			if(sql_DynamicDiscovery_Check_All_Invalid(dreDynamicDiscoveryConfigReq))
			{
				return DRE_DB_SUCCESS;	
			}
			sql_DynamicDiscovery_Create_Mod_Query(dreDynamicDiscoveryConfigReq,sStatement);
			break;
		case DRE_LOCAL_HOST_CONFIG_T:      
			dreLocalHostConfigReq 		= (DreLocalHostPayload *)payloadConfigReq;
			if(sql_LocalHostConfig_Check_All_Invalid(dreLocalHostConfigReq))
			{
				return DRE_DB_SUCCESS;	
			}
			sql_LocalHostConfig_Create_Mod_Query(dreLocalHostConfigReq,sStatement);
			break;
		case DRE_PEER_GLOBAL_CONFIG_T:
			drePeerGlobalConfigReq 		= (DrePeerGlobalConfigPayload *)payloadConfigReq;
			if(sql_PeerGlobalConfig_Check_All_Invalid(drePeerGlobalConfigReq))
			{
				return DRE_DB_SUCCESS;
			}
			sql_PeerGlobalConfig_Create_Mod_Query(drePeerGlobalConfigReq,sStatement);
			break;
		case DRE_PEER_T:
			drePeerAndTimerConfigPayload 	= (DrePeerPayloadAndTimerPayload *)payloadConfigReq;
			drePeerConfigReq 		= &drePeerAndTimerConfigPayload->drePeerPayload;
			if(sql_Peer_Check_All_Invalid(drePeerConfigReq))
			{
				return DRE_DB_SUCCESS;
			}	
			sql_Peer_Create_Mod_Query(drePeerConfigReq,sStatement);
			break;
		case DRE_PEER_TIMERS_T:
			drePeerAndTimerConfigPayload 	= (DrePeerPayloadAndTimerPayload *)payloadConfigReq;
			drePeerTimersConfigReq 		= &drePeerAndTimerConfigPayload->drePeerTimersConfigPayload;
			if(sql_PeerTimers_Check_All_Invalid(drePeerTimersConfigReq))
			{
				return DRE_DB_SUCCESS;	
			}
			sql_PeerTimers_Create_Mod_Query(drePeerTimersConfigReq,sStatement);
			break;
		case DRE_REALM_ROUTING_T:
			dreRealmRoutingConfigReq 	= (DreRealmRoutingPayload *)payloadConfigReq;
			if(sql_RealmRouting_Check_All_Invalid(dreRealmRoutingConfigReq))
			{
				 return DRE_DB_SUCCESS;	
			}
			sql_RealmRouting_Create_Mod_Query(dreRealmRoutingConfigReq,sStatement);
			break;
		case DRE_REPLICATION_MANAGER_CONFIG_T:
			repMgrReplStateConfigReq 	= (RepMgrReplStateConfigPayload*)payloadConfigReq;
			if(sql_RepMgrConfig_Check_All_Invalid(repMgrReplStateConfigReq))
			{
				 return DRE_DB_SUCCESS;	
			}
			sql_RepMgrConfig_Create_Mod_Query(repMgrReplStateConfigReq,sStatement);
			break;
		case DRE_USER_T:
			dreUserConfigReq 		= (DreUserConfigPayload *)payloadConfigReq;
			if(sql_User_Check_All_Invalid(dreUserConfigReq))
			{
				return DRE_DB_SUCCESS;	
			}
			sql_User_Create_Mod_Query(dreUserConfigReq,sStatement);
			break;
		case DRE_ASF_T:
                        dreAsfReq                = (DreASFAppGroupPayload *)payloadConfigReq;
                        if(sql_Asf_Check_All_Invalid(dreAsfReq))
                        {
                                return DRE_DB_SUCCESS;
                        }
                        sql_Asf_Create_Mod_Query(dreAsfReq,sStatement);
                        break;
		case DRE_ASFCONFIG_T:
                        dreASFConfigPayload = (DreASFConfigPayload*)payloadConfigReq;
                        if(sql_AsfConfig_Check_All_Invalid(dreASFConfigPayload))
                        {
                                return DRE_DB_SUCCESS;
                        }
                        sql_AsfConfig_Create_Mod_Query(dreASFConfigPayload,sStatement);
                        break;
		case DRE_ASFFEATURE_T:
                        dreASFConfigPayload = (DreASFConfigPayload*)payloadConfigReq;
                        if(sql_AsfFeature_Check_All_Invalid(dreASFConfigPayload))
                        {
                                return DRE_DB_SUCCESS;
                        }
                        sql_AsfFeature_Create_Mod_Query(dreASFConfigPayload,sStatement);
                        break;
		case DRE_PEER_DICT_MAP_T:
                        drePeerConfigReq = (DrePeerPayload*)payloadConfigReq;
                        if(sql_PeerDictionaryMap_Check_All_Invalid(drePeerConfigReq))
                        {
                                return DRE_DB_SUCCESS;
                        }
                        sql_PeerDictionaryMap_Create_Mod_Query(drePeerConfigReq,sStatement);
                        break;



		default:
	        PRINTF("%s:%d Default\n",__FUNCTION__,__LINE__);	
			break;
	
	}

	try
	{
		PRINTF("Query Statement: %s\n",sStatement);
		pStmt 					= con->createStatement();
		pStmt->execute(sStatement);
		delete pStmt;
		PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
		
	}
	catch (sql::SQLException &e)
	{
		cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
		cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		if(pStmt != NULL)
			delete pStmt;
		PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		return DRE_DB_FAIL;
	}


	return DRE_DB_SUCCESS;
}

DbStatus_e mysql_cli_interface::mysql_Payload_Validation(drePayload *payloadConfigReq,dreTableName_e dreTableName)
{

	AvaMgrConfigPayload				*avaMgrConfigReq;
	DreDefaultRoutePayload				*dreDefaultRouteConfigReq;
	DreDynamicDiscoveryConfigPayload		*dreDynamicDiscoveryConfigReq;
	DreLocalHostPayload				*dreLocalHostConfigReq;
	DrePeerGlobalConfigPayload			*drePeerGlobalConfigReq;
	DrePeerPayload					*drePeerConfigReq;
	DrePeerTimersConfigPayload			*drePeerTimersConfigReq;
	DreRealmRoutingPayload				*dreRealmRoutingConfigReq;
	RepMgrReplStateConfigPayload			*repMgrReplStateConfigReq;
	DrePeerPayloadAndTimerPayload			*drePeerAndTimerConfigPayload;
	DreUserConfigPayload				*dreUserConfigReq;
	DreASFAppGroupPayload				*dreAsfReq;
    	DreASFConfigPayload                     	*dreASFConfigPayload;

	DbStatus_e 					status;

	switch(dreTableName)
	{
		case DRE_AVAILABILITY_MANAGER_CONFIG_T:                                                          
			avaMgrConfigReq 		= (AvaMgrConfigPayload *)payloadConfigReq;
			status = sql_AvaMgrConfig_Payload_Validation(avaMgrConfigReq);
			break;
		case DRE_DEFAULT_ROUTE_T:
			dreDefaultRouteConfigReq 	= (DreDefaultRoutePayload *)payloadConfigReq;
			status = sql_DefaultRoute_Payload_Validation(dreDefaultRouteConfigReq);
			break;                                                  
		case DRE_DYNAMIC_DISCOVERY_T:
			dreDynamicDiscoveryConfigReq 	= (DreDynamicDiscoveryConfigPayload *)payloadConfigReq;
			status = sql_DynamicDiscovery_Payload_Validation(dreDynamicDiscoveryConfigReq);
			break;
		case DRE_LOCAL_HOST_CONFIG_T:      
			dreLocalHostConfigReq 		= (DreLocalHostPayload *)payloadConfigReq;
			status = sql_LocalHostConfig_Payload_Validation(dreLocalHostConfigReq);
			break;
		case DRE_PEER_GLOBAL_CONFIG_T: 
			drePeerGlobalConfigReq 		= (DrePeerGlobalConfigPayload *)payloadConfigReq;
			status = sql_PeerGlobalConfig_Payload_Validation(drePeerGlobalConfigReq);
			break;
		case DRE_PEER_T:
			drePeerAndTimerConfigPayload 	= (DrePeerPayloadAndTimerPayload *)payloadConfigReq;
			drePeerConfigReq 		= &drePeerAndTimerConfigPayload->drePeerPayload;
			status = sql_Peer_Payload_Validation(drePeerConfigReq);
			break;
		case DRE_PEER_TIMERS_T:
			drePeerAndTimerConfigPayload 	= (DrePeerPayloadAndTimerPayload *)payloadConfigReq;
			drePeerTimersConfigReq 		= &drePeerAndTimerConfigPayload->drePeerTimersConfigPayload;
			status = sql_PeerTimers_Payload_Validation(drePeerTimersConfigReq);
			break;
		case DRE_REALM_ROUTING_T:
			dreRealmRoutingConfigReq 	= (DreRealmRoutingPayload *)payloadConfigReq;
			status = sql_RealmRouting_Payload_Validation(dreRealmRoutingConfigReq);
			break;
		case DRE_REPLICATION_MANAGER_CONFIG_T:
			repMgrReplStateConfigReq 	= (RepMgrReplStateConfigPayload*)payloadConfigReq;
			status = sql_RepMgrConfig_Payload_Validation(repMgrReplStateConfigReq);
			break;
		case DRE_USER_T:
			dreUserConfigReq 		= (DreUserConfigPayload *)payloadConfigReq;
			status = sql_User_Payload_Validation(dreUserConfigReq);
			break;
		case DRE_ASF_T:
                        dreAsfReq                = (DreASFAppGroupPayload *)payloadConfigReq;
                        status = sql_Asf_Payload_Validation(dreAsfReq);
                        break;
		case DRE_ASFCONFIG_T:
                        dreASFConfigPayload = (DreASFConfigPayload*)payloadConfigReq;
                        status = sql_AsfConfig_Payload_Validation(dreASFConfigPayload);
                        break;
		case DRE_ASFFEATURE_T:
                        dreASFConfigPayload = (DreASFConfigPayload*)payloadConfigReq;
                        status = sql_AsfFeature_Payload_Validation(dreASFConfigPayload);
                        break;
		case DRE_PEER_DICT_MAP_T:
                        drePeerConfigReq = (DrePeerPayload*)payloadConfigReq;
                        status = sql_PeerDictionaryMap_Payload_Validation(drePeerConfigReq);
                        break;
		default:
	        PRINTF("%s:%d Default\n",__FUNCTION__,__LINE__);	
			break;
	
	}

	return status;

}

DbStatus_e mysql_cli_interface::mysql_exec_oper(drePayload *pPayload,dreTableName_e tableName,OpCode_e oprtype)
{

	DbStatus_e status = DRE_DB_FAIL;
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	switch(oprtype)
	{
        case ADD:
             if(mysql_Payload_Validation(pPayload,tableName) == DRE_DB_FAIL)
               {
                        PRINTF("%s:%d Validation Failed\n",__FUNCTION__,__LINE__);
                        return DRE_DB_FAIL;
               }
            switch(mysql_Check_Modifcation(pPayload,tableName))
                {
                    case DRE_DB_MOD:
                        PRINTF("%s:%d Record Already Exists, Can't add again\n",__FUNCTION__,__LINE__);
                        status = DRE_DB_FAIL;
                        break;
                    case DRE_DB_ADD:
                        status = mysql_Add_Row(pPayload,tableName);
                        break;
                    case DRE_DB_ERR:
                        status = DRE_DB_FAIL;
                        break; 
                    default:
                        PRINTF("%s:%d Default\n",__FUNCTION__,__LINE__);
                        break;
                }
                break;
        case MODIFY:
                if(mysql_Payload_Validation(pPayload,tableName) == DRE_DB_FAIL)
                {
                    PRINTF("%s:%d Validation Failed\n",__FUNCTION__,__LINE__);
                    return DRE_DB_FAIL;
                }
                switch(mysql_Check_Modifcation(pPayload,tableName))
                {
                    case DRE_DB_MOD:
                            status = mysql_Modify_Row(pPayload,tableName); 
                            break;
                    case DRE_DB_ADD: 
                            PRINTF("%s:%d Record Doesn't Exists,Can't modify\n",__FUNCTION__,__LINE__);
                            status = DRE_DB_FAIL;
                            break;
                    case DRE_DB_ERR:
                            status = DRE_DB_FAIL; 
                             break;
                    default:
                            PRINTF("%s:%d Default\n",__FUNCTION__,__LINE__);
                            break;     
                }    
                break;


		case DELETE:
			status = mysql_Delete_Row(pPayload,tableName);
			break;
		default:
	        PRINTF("%s:%d OP_CODE Default\n",__FUNCTION__,__LINE__);
			break;
	}	

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return status;
}

DbStatus_e mysql_cli_interface::mysql_cli_handling_dictionaryid_req(drePayload *pPayload,OpCode_e opCode)
{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	DrePeerPayload					*drePeerConfigReq;
	drePayload					localdrePayload;
	DrePeerPayload					*localdrePeerConfigReq;

	localdrePeerConfigReq = (DrePeerPayload *)&localdrePayload;

    	DbStatus_e          status = DRE_DB_FAIL;

	drePeerConfigReq = (DrePeerPayload *)pPayload;

	int iCount = drePeerConfigReq->peerDictionaryInfo.num_dict;
	
	for(int i=0;i<iCount;i++)
	{
		memset(localdrePeerConfigReq,0,sizeof(localdrePeerConfigReq));

		strcpy(localdrePeerConfigReq->peerDictionaryInfo.peerKeyInfo.HostName,drePeerConfigReq->peerDictionaryInfo.peerKeyInfo.HostName);

		strcpy(localdrePeerConfigReq->peerDictionaryInfo.peerKeyInfo.RealmName,drePeerConfigReq->peerDictionaryInfo.peerKeyInfo.RealmName);
		strcpy(localdrePeerConfigReq->peerDictionaryInfo.PeerDictionaryIds[0], drePeerConfigReq->peerDictionaryInfo.PeerDictionaryIds[i])
		status = mysql_exec_oper(&localdrePayload,DRE_PEER_DICT_MAP_T,opCode);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return status;
}

DbStatus_e mysql_cli_interface::mysql_Payload(SetConfigReq configReq)
{
	drePayload			*pPayload;
    	DbStatus_e          status = DRE_DB_FAIL;

	pPayload			= &configReq.Payload;

	PRINTF("%s:%d cmd_id = %d\n",__FUNCTION__,__LINE__,configReq.cmd_id);	

	switch(configReq.cmd_id)
	{
		case C_cli_peer_Id:
		case C_cli_modifypeer_Id:
		case C_cli_no_peer_Id:
			status = mysql_exec_oper(pPayload,DRE_PEER_T,configReq.OP_CODE);

            if(status == DRE_DB_SUCCESS)
			    status = mysql_exec_oper(pPayload,DRE_PEER_TIMERS_T,configReq.OP_CODE);

			break;
		case C_cli_peer_dictionary_Id:
		case C_cli_deletedictionary_Id:
			
			status = mysql_cli_handling_dictionaryid_req(pPayload,configReq.OP_CODE);
			break;
		case C_cli_defaultRoute_Id:
		case C_cli_modifydefaultRoute_Id:

			status = mysql_exec_oper(pPayload,DRE_DEFAULT_ROUTE_T,configReq.OP_CODE);

			break;
		case C_cli_configRealm_Id:
		case C_cli_no_configRealm_Id:
		case C_cli_modifyrealm_Id:

			status = mysql_exec_oper(pPayload,DRE_REALM_ROUTING_T,configReq.OP_CODE);

			break;
		case C_cli_localhost_Id:
		case C_cli_modifylocalhost_Id:
		case C_cli_no_localhost_Id:
			status = mysql_exec_oper(pPayload,DRE_LOCAL_HOST_CONFIG_T,configReq.OP_CODE);

			break;
		case C_cli_discoveryIntl_Id:

			status = mysql_exec_oper(pPayload,DRE_PEER_GLOBAL_CONFIG_T,configReq.OP_CODE);

			break;
		case C_cli_discoverPeer_Id:

			status = mysql_exec_oper(pPayload,DRE_DYNAMIC_DISCOVERY_T,configReq.OP_CODE);

			break;
        	case C_cli_adduser_Id:
		case C_cli_deleteuser_Id:
			status = mysql_exec_oper(pPayload,DRE_USER_T,configReq.OP_CODE);

            		break;
		case C_cli_add_asgroup_Id:
		case C_cli_modify_asgroup_Id:
        case C_cli_show_asgroup_Id:
        case C_cli_delete_asgroup_Id:
		case C_cli_asf_terminate_Id:

			status = mysql_exec_oper(pPayload,DRE_ASF_T,configReq.OP_CODE);

			break;
		case C_cli_asf_config_Id:

            status = mysql_exec_oper(pPayload,DRE_ASFCONFIG_T,configReq.OP_CODE);

            break;
		case C_cli_asf_responseTimeout_Id:

            status = mysql_exec_oper(pPayload,DRE_ASFFEATURE_T,configReq.OP_CODE);

            break;
             
		default:

	        PRINTF("%s:%d Default\n",__FUNCTION__,__LINE__);	
			break;	
	}
	
	PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
	return status;		
}

void mysql_cli_interface::mysql_Set_Searchkey(GetConfigReq configReq,drePayload *localPayload,int showID)
{
	DreDynamicDiscoveryConfigPayload		*dreDynamicDiscoveryPayload;
	DreRealmRoutingPayload				*dreRealmPayload;
    	DrePeerPayloadAndTimerPayload       		*drePeerAndTimerConfigPayload;
	DreUserConfigPayload				*dreUserConfigPayload;
	DrePeerKeyInfo					*drePeerKeyInfo;
	DreUserKeyInfo					*dreUserKeyInfo;
	DreLocalHostPayload                             *dreLocalHostConfigReq;
	DreASFAppGroupPayload				*dreASFAppGroupPayload;
    	DreASFConfigPayload                     	*dreASFConfigPayload;
	DreRealmRoutingKeyInfo				*realmKey;
	DrePeerPayload					*drePeerPayload;
	PRINTF("%s:%d\n",__FUNCTION__,__LINE__);

	switch(showID)	
	{
		case SH_PEER_CONFIG:	

			drePeerAndTimerConfigPayload = (DrePeerPayloadAndTimerPayload *)localPayload;

			drePeerAndTimerConfigPayload->drePeerPayload.peerKeyInfo.HostName[0] 	= INVALID_STR;
			drePeerAndTimerConfigPayload->drePeerPayload.peerKeyInfo.RealmName[0] 	= INVALID_STR;

			drePeerAndTimerConfigPayload->drePeerPayload.peerInfo.IpAddr[0] 		= INVALID_STR;
			drePeerAndTimerConfigPayload->drePeerPayload.peerInfo.PortNumber 		= INVALID_NUM;
			drePeerAndTimerConfigPayload->drePeerPayload.peerInfo.AltHostName[0] 	= INVALID_STR;
			drePeerAndTimerConfigPayload->drePeerPayload.peerInfo.IsMate 		= INVALID_NUM;
			drePeerAndTimerConfigPayload->drePeerPayload.peerInfo.TransportType 		= INVALID_NUM;
			drePeerAndTimerConfigPayload->drePeerPayload.peerInfo.TLS		= INVALID_NUM;
			drePeerAndTimerConfigPayload->drePeerPayload.peerInfo.Enable_Status 		= INVALID_NUM;

			drePeerAndTimerConfigPayload->drePeerPayload.peerSwitchingInfo.Failover 	= INVALID_NUM;
			drePeerAndTimerConfigPayload->drePeerPayload.peerSwitchingInfo.Failback 	= INVALID_NUM;

			
			drePeerAndTimerConfigPayload->drePeerTimersConfigPayload.PeerTimersKeyInfo.peerHostNames[0] 		= INVALID_STR;
			drePeerAndTimerConfigPayload->drePeerTimersConfigPayload.PeerTimersKeyInfo.realmName[0] 		= INVALID_STR;

			drePeerAndTimerConfigPayload->drePeerTimersConfigPayload.PeerTimersConfigInfo.watchdogValue 		= INVALID_NUM;
			drePeerAndTimerConfigPayload->drePeerTimersConfigPayload.PeerTimersConfigInfo.TCValue 		= INVALID_NUM;
			drePeerAndTimerConfigPayload->drePeerTimersConfigPayload.PeerTimersConfigInfo.expiryValue 		= INVALID_NUM;
			break;
		case SH_PEER_STATUS:
			drePeerAndTimerConfigPayload = (DrePeerPayloadAndTimerPayload *)localPayload;
			drePeerKeyInfo = (DrePeerKeyInfo *)&configReq.shReqPayload.dreKeyInfo;
			
			strcpy(drePeerAndTimerConfigPayload->drePeerPayload.peerKeyInfo.HostName,drePeerKeyInfo->HostName);
			strcpy(drePeerAndTimerConfigPayload->drePeerPayload.peerKeyInfo.RealmName,drePeerKeyInfo->RealmName);

			drePeerAndTimerConfigPayload->drePeerPayload.peerInfo.IpAddr[0] 		= INVALID_STR;
			drePeerAndTimerConfigPayload->drePeerPayload.peerInfo.PortNumber 		= INVALID_NUM;
			drePeerAndTimerConfigPayload->drePeerPayload.peerInfo.AltHostName[0] 	= INVALID_STR;
			drePeerAndTimerConfigPayload->drePeerPayload.peerInfo.IsMate 		= INVALID_NUM;
			drePeerAndTimerConfigPayload->drePeerPayload.peerInfo.TransportType 		= INVALID_NUM;
			drePeerAndTimerConfigPayload->drePeerPayload.peerInfo.TLS               = INVALID_NUM;
			drePeerAndTimerConfigPayload->drePeerPayload.peerInfo.Enable_Status 		= INVALID_NUM;

			drePeerAndTimerConfigPayload->drePeerPayload.peerSwitchingInfo.Failover 	= INVALID_NUM;
			drePeerAndTimerConfigPayload->drePeerPayload.peerSwitchingInfo.Failback 	= INVALID_NUM;

	
			strcpy(drePeerAndTimerConfigPayload->drePeerTimersConfigPayload.PeerTimersKeyInfo.peerHostNames,drePeerKeyInfo->HostName);
			strcpy(drePeerAndTimerConfigPayload->drePeerTimersConfigPayload.PeerTimersKeyInfo.realmName,drePeerKeyInfo->RealmName);

			drePeerAndTimerConfigPayload->drePeerTimersConfigPayload.PeerTimersConfigInfo.watchdogValue 		= INVALID_NUM;
			drePeerAndTimerConfigPayload->drePeerTimersConfigPayload.PeerTimersConfigInfo.TCValue 		= INVALID_NUM;
			drePeerAndTimerConfigPayload->drePeerTimersConfigPayload.PeerTimersConfigInfo.expiryValue 		= INVALID_NUM;
			break;
		case SH_REALM_CONFIG:
			
			dreRealmPayload 		= (DreRealmRoutingPayload *)localPayload;
			realmKey 			= (DreRealmRoutingKeyInfo *)&configReq.shReqPayload.dreKeyInfo;

			strcpy(dreRealmPayload->realmKeyInfo.RealmName,realmKey->RealmName);

			dreRealmPayload->realmKeyInfo.PeerHostId[0] 	= INVALID_STR;	
			dreRealmPayload->realmKeyInfo.AppId             = INVALID_NUM;
			dreRealmPayload->realmInfo.LocalAction 		= INVALID_NUM;	
			dreRealmPayload->realmInfo.VendorID 		= INVALID_NUM;	
			dreRealmPayload->realmInfo.Priority 		= INVALID_NUM;	
			dreRealmPayload->realmInfo.NodeDiscovery 	= INVALID_NUM;	
			dreRealmPayload->realmInfo.RedirectHostUsage 	= INVALID_NUM;	
			dreRealmPayload->realmInfo.RedirectMaxCacheTime = INVALID_NUM;	
			break;

		case SH_CONFIG_REALM:

                        dreRealmPayload                 = (DreRealmRoutingPayload *)localPayload;
                        realmKey                        = (DreRealmRoutingKeyInfo *)&configReq.shReqPayload.dreKeyInfo;

			dreRealmPayload->realmKeyInfo.RealmName[0]      = INVALID_STR;  
                        dreRealmPayload->realmKeyInfo.PeerHostId[0]        = INVALID_STR;
			dreRealmPayload->realmKeyInfo.AppId             = INVALID_NUM;

                        dreRealmPayload->realmInfo.LocalAction          = INVALID_NUM;
                        dreRealmPayload->realmInfo.VendorID             = INVALID_NUM;
                        dreRealmPayload->realmInfo.Priority             = INVALID_NUM;
                        dreRealmPayload->realmInfo.NodeDiscovery        = INVALID_NUM;
                        dreRealmPayload->realmInfo.RedirectHostUsage    = INVALID_NUM;
                        dreRealmPayload->realmInfo.RedirectMaxCacheTime = INVALID_NUM;
                        break;

		case SH_LOCALHOST_CONFIG:
			
			dreLocalHostConfigReq = (DreLocalHostPayload *)localPayload;
			
			dreLocalHostConfigReq->LocalHostKeyInfo.HostName[0]  = INVALID_STR;
			dreLocalHostConfigReq->LocalHostKeyInfo.RealmName[0]  = INVALID_STR;
			dreLocalHostConfigReq->LocalHostTransportInfo.IpAddr[0]  = INVALID_STR;
			dreLocalHostConfigReq->LocalHostTransportInfo.portno = INVALID_NUM;
			dreLocalHostConfigReq->LocalHostTransportInfo.transportType = INVALID_NUM;
			dreLocalHostConfigReq->LocalHostAuthInfo.LifeTime = INVALID_NUM;
			dreLocalHostConfigReq->LocalHostAuthInfo.GraceTime = INVALID_NUM;
			dreLocalHostConfigReq->LocalHostAuthInfo.TimeOut = INVALID_NUM;
			dreLocalHostConfigReq->LocalHostAcctInfo.Interim = INVALID_NUM;
			dreLocalHostConfigReq->LocalHostAcctInfo.TimeOut = INVALID_NUM;
			break;


		case SH_REALM_SUMMARY:
			dreRealmPayload 		= (DreRealmRoutingPayload *)localPayload;

			dreRealmPayload->realmKeyInfo.RealmName[0] 	= INVALID_STR;	
			dreRealmPayload->realmKeyInfo.PeerHostId[0] 	= INVALID_STR;
			dreRealmPayload->realmKeyInfo.AppId             = INVALID_NUM;	
			
			dreRealmPayload->realmInfo.LocalAction 		= INVALID_NUM;	
			dreRealmPayload->realmInfo.VendorID 		= INVALID_NUM;	
			dreRealmPayload->realmInfo.Priority 		= INVALID_NUM;	
			dreRealmPayload->realmInfo.NodeDiscovery 	= INVALID_NUM;	
			dreRealmPayload->realmInfo.RedirectHostUsage 	= INVALID_NUM;	
			dreRealmPayload->realmInfo.RedirectMaxCacheTime = INVALID_NUM;	

			break;
		case SH_DISCOVERED_PEERS:
			dreDynamicDiscoveryPayload 	= (DreDynamicDiscoveryConfigPayload *)localPayload;
		
			dreDynamicDiscoveryPayload->DynamicDiscoveryKeyInfo.RealmName[0] 	= INVALID_STR;		
			dreDynamicDiscoveryPayload->DynamicDiscoveryConfigInfo.peerHostNames[0] = INVALID_STR;		
			break;
		case SH_USERNAME:
			dreUserConfigPayload		= (DreUserConfigPayload *)localPayload;	
			dreUserKeyInfo 			= (DreUserKeyInfo*)&configReq.shReqPayload.dreKeyInfo;

			strcpy(dreUserConfigPayload->UserKeyInfo.UserName,dreUserKeyInfo->UserName);
			dreUserConfigPayload->UserConfigInfo.password[0]			= INVALID_STR;
			dreUserConfigPayload->UserConfigInfo.privilege				= INVALID_NUM;
			break;
		case SH_ASF:
                        dreASFAppGroupPayload            = (DreASFAppGroupPayload *)localPayload;
			
 			dreASFAppGroupPayload->dreASFKeyInfo.GroupName[0]				= INVALID_STR;
			dreASFAppGroupPayload->dreASFConfigInfo.priority				= INVALID_NUM;
			dreASFAppGroupPayload->dreASFConfigInfo.appType                 = INVALID_NUM;
			dreASFAppGroupPayload->dreASFConfigInfo.lbAlgorithm[0]             = INVALID_STR;
			dreASFAppGroupPayload->dreASFConfigInfo.maxAppInstances         = INVALID_NUM;			                     break;
                case SH_ASFCONFIG:
                        dreASFConfigPayload = (DreASFConfigPayload*)localPayload;
                        
			dreASFConfigPayload->dreASFConfigKeyInfo.ComponentID				= INVALID_NUM;
			dreASFConfigPayload->dreASFRespTimeout.responseTimeout                        = INVALID_NUM;
		        break;
                case SH_ASFFEATURE:
                        dreASFConfigPayload = (DreASFConfigPayload*)localPayload;

                        dreASFConfigPayload->dreASFConfigKeyInfo.ComponentID                            	= INVALID_NUM;
                        dreASFConfigPayload->dreASFStatus.ASFStatus                             	= INVALID_NUM;
                        dreASFConfigPayload->dreASFStatus.ERLBFStatus                            	= INVALID_NUM;
                        break;

		case SH_DICTIONARY:
			drePeerKeyInfo	= (DrePeerKeyInfo *)&configReq.shReqPayload.dreKeyInfo.peerKeyInfo;
			drePeerPayload = (DrePeerPayload *)localPayload;
			strcpy(drePeerPayload->peerDictionaryInfo.peerKeyInfo.HostName,drePeerKeyInfo->HostName);
			strcpy(drePeerPayload->peerDictionaryInfo.peerKeyInfo.RealmName,drePeerKeyInfo->RealmName);
			drePeerPayload->peerDictionaryInfo.PeerDictionaryIds[0] 	= NULL;
			break;	

#if 0
		case SH_PEER_TIMER:
			drePeerTimersConfigPayload 	= (DrePeerTimersConfigPayload *)localPayload;
			
			drePeerTimersConfigPayload->PeerTimersKeyInfo.peerHostNames[0] 		= INVALID_STR;
			drePeerTimersConfigPayload->PeerTimersKeyInfo.realmName[0] 		= INVALID_STR;

			drePeerTimersConfigPayload->PeerTimersConfigInfo.watchdogValue 		= INVALID_NUM;
			drePeerTimersConfigPayload->PeerTimersConfigInfo.TCValue 		= INVALID_NUM;
			drePeerTimersConfigPayload->PeerTimersConfigInfo.expiryValue 		= INVALID_NUM;
			break;
#endif
		case SH_INVALID:
			break;
		default:
	        PRINTF("%s:%d Default\n",__FUNCTION__,__LINE__);	
			break;
	}
	PRINTF("%s:%d\n",__FUNCTION__,__LINE__);
}

DbStatus_e mysql_cli_interface::mysql_Payload(GetConfigReq configReq,AllResponses *rsp)
{
	int 		table_count;
	drePayload 	localPayload;
	DbStatus_e 	iReturn = DRE_DB_FAIL;
	GetConfigRsp	resultSet;

	PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	

	memset(&resultSet,0,sizeof(GetConfigRsp));
	memset(&localPayload,0,sizeof(drePayload));
	memset(rsp,0,sizeof(AllResponses));

	PRINTF("%s:%d cmd_id = %d\n",__FUNCTION__,__LINE__,configReq.cmd_id);	

	rsp->cmd_id = configReq.cmd_id;

	switch(configReq.cmd_id)
	{
		case C_cli_showpeer_Id:
			table_count = 0;

			mysql_Set_Searchkey(configReq,&localPayload,configReq.shReqPayload.showID);
			iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_PEER_T,table_count);

			if(iReturn == DRE_DB_SUCCESS)   
			{
				iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_PEER_TIMERS_T,table_count);
			}

			break;

		case C_cli_show_dictionary_Id:
			table_count = 0;
			mysql_Set_Searchkey(configReq,&localPayload,configReq.shReqPayload.showID);
			iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_PEER_DICT_MAP_T,table_count);
			break;
		case C_cli_showrealm_Id:
			table_count = 0;

			mysql_Set_Searchkey(configReq,&localPayload,configReq.shReqPayload.showID);
			iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_REALM_ROUTING_T,table_count);
			break;
		case C_cli_showuser_Id:
			table_count = 0;
			resultSet.cmd_id = C_cli_showuser_Id;
			mysql_Set_Searchkey(configReq,&localPayload,configReq.shReqPayload.showID);
			iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_USER_T,table_count);
			break;
		case C_cli_showDiscoverPeer_Id:
			table_count = 0;

			mysql_Set_Searchkey(configReq,&localPayload,configReq.shReqPayload.showID);
			iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_DYNAMIC_DISCOVERY_T,table_count);
			break;
			
		case C_cli_show_asgroup_Id:
                        table_count = 0;

                        mysql_Set_Searchkey(configReq,&localPayload,configReq.shReqPayload.showID);
                        iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_ASF_T,table_count);
                        break;

		case  C_cli_showconfig_Id:
			table_count = 0;
			if(configReq.shReqPayload.showID==SH_PEER_CONFIG)
			{
	 			mysql_Set_Searchkey(configReq,&localPayload,configReq.shReqPayload.showID);
				iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_PEER_T,table_count);

                        	if(iReturn == DRE_DB_SUCCESS)
                        	{
                               		 iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_PEER_TIMERS_T,table_count);
                        	}

			}
			else if(configReq.shReqPayload.showID==SH_REALM_CONFIG)
			{
				 mysql_Set_Searchkey(configReq,&localPayload,configReq.shReqPayload.showID);
				printf("IFREALMNAME = %s\n",configReq.shReqPayload.dreKeyInfo.realmKeyInfo.RealmName);
				 iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_REALM_ROUTING_T,table_count);
			}
			else if(configReq.shReqPayload.showID==SH_LOCALHOST_CONFIG)
			{
				mysql_Set_Searchkey(configReq,&localPayload,configReq.shReqPayload.showID);
				iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_LOCAL_HOST_CONFIG_T,table_count);
			}
			else if(configReq.shReqPayload.showID==SH_DIAMETERBASE)
			{
                       		 mysql_Set_Searchkey(configReq,&localPayload,SH_PEER_CONFIG);
				 iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_PEER_T,table_count);
				 if(iReturn == DRE_DB_SUCCESS)
				 {
					 iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_PEER_TIMERS_T,table_count);
				 }
				 if(iReturn == DRE_DB_SUCCESS)
				 {
					 table_count++;

					 mysql_Set_Searchkey(configReq,&localPayload,SH_LOCALHOST_CONFIG);
					 iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_LOCAL_HOST_CONFIG_T,table_count);
				 }

				 if(iReturn == DRE_DB_SUCCESS)
				 {
					 table_count++;

					 mysql_Set_Searchkey(configReq,&localPayload,SH_CONFIG_REALM);
					 iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_REALM_ROUTING_T,table_count);
				 }
			}
			break;
			
		case C_cli_showDiameterbase_Id:
			table_count = 0;

			mysql_Set_Searchkey(configReq,&localPayload,SH_PEER_CONFIG);
			iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_PEER_T,table_count);

			if(iReturn == DRE_DB_SUCCESS)
			{
				iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_PEER_TIMERS_T,table_count);
			}
			if(iReturn == DRE_DB_SUCCESS)
			{
				table_count++;

                                mysql_Set_Searchkey(configReq,&localPayload,SH_LOCALHOST_CONFIG);
                                iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_LOCAL_HOST_CONFIG_T,table_count);
                        }

			if(iReturn == DRE_DB_SUCCESS)
			{
				table_count++;

				mysql_Set_Searchkey(configReq,&localPayload,SH_CONFIG_REALM);
				iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_REALM_ROUTING_T,table_count);
			}
			
			break;
        case C_cli_verify_passwd_Id:
			table_count = 0;

			mysql_Set_Searchkey(configReq,&localPayload,configReq.shReqPayload.showID);
			iReturn = mysql_Get_Record(&localPayload,&resultSet,DRE_USER_T,table_count);
			break;
            

		case C_cli_showtask_Id:
			table_count = 0;

			break;
		default:

			PRINTF("%s:%d Default\n",__FUNCTION__,__LINE__);	
			break;
	}

	if(iReturn == DRE_DB_SUCCESS)
	{
		resultSet.table_count = (table_count + 1);
		PRINTF("%s:%d table_count = %d\n",__FUNCTION__,__LINE__,resultSet.table_count);	
		mysql_Rsp_To_Buffer(&resultSet,rsp);
		
	}


	rsp->ResponseCode = iReturn;

	PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	

	return iReturn;		
}


void mysql_cli_interface::mysql_Rsp_To_Buffer(GetConfigRsp *resultSet,AllResponses *rsp)
{
	int i;
	int iTableCount;
	dreDataType_e eDataType;
	int iRecordCount;

	PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	

	iTableCount = resultSet->table_count;

    PRINTF("%s:%d TableCount = %d\n",__FUNCTION__,__LINE__,iTableCount);

	for(i=0;i<iTableCount;i++)
	{
		eDataType = resultSet->datatype_names[i];
		iRecordCount = resultSet->record_count[i];
		mysql_Datatype_To_Buffer(eDataType,iRecordCount,resultSet->payload[i],rsp->payload);
	}

	PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
		
}

void mysql_cli_interface::mysql_Datatype_To_Buffer(dreDataType_e datatype_name,int recordCount,drePayload *payload, char *pPayload)
{

	AvaMgrConfigPayload 			*avaMgrConfigPayload;
	DreDefaultRoutePayload 			*dreDefaultRoutePayload;
	DreDynamicDiscoveryConfigPayload 	*dreDynamicDiscoveryPayload;
	DreLocalHostPayload 			*dreLocalHostPayload;
	DrePeerGlobalConfigPayload 		*dreGlobalConfigPayload;
	DrePeerPayloadAndTimerPayload 		*drePeerAndTimerConfigPayload;
	DrePeerPayload		 		*drePeerConfigPayload;
	DreRealmRoutingPayload 			*dreRealmPayload;
	RepMgrReplStateConfigPayload 		*repMgrReplStateConfigPayload;
	DreUserConfigPayload 			*dreUserPayload;
	DreASFAppGroupPayload 			*dreASFAppGroupPayload;
    	DreASFConfigPayload 			*dreASFConfigPayload;

	PRINTF("%s:%d datatype = %d\n",__FUNCTION__,__LINE__,datatype_name);	

	switch(datatype_name)
	{
		case DRE_AVAILABILITY_MANAGER_CONFIG:
			avaMgrConfigPayload = (AvaMgrConfigPayload *)payload;
			mysql_fill_AvaMgrConfig_Datatype_To_Buffer(recordCount,avaMgrConfigPayload,pPayload);

			break;
		case DRE_DEFAULT_ROUTE:
			dreDefaultRoutePayload = (DreDefaultRoutePayload *)payload;
			mysql_fill_DefaultRoute_Datatype_To_Buffer(recordCount,dreDefaultRoutePayload,pPayload);

			break;
		case DRE_DYNAMIC_DISCOVERY:
			dreDynamicDiscoveryPayload = (DreDynamicDiscoveryConfigPayload *)payload;
			mysql_fill_DynamicDiscovery_Datatype_To_Buffer(recordCount,dreDynamicDiscoveryPayload,pPayload);

			break;
		case DRE_LOCAL_HOST_CONFIG:
			dreLocalHostPayload = (DreLocalHostPayload *)payload;
			mysql_fill_LocalHostConfig_Datatype_To_Buffer(recordCount,dreLocalHostPayload,pPayload);
	
			break;
		case DRE_PEER_GLOBAL_CONFIG:
			dreGlobalConfigPayload = (DrePeerGlobalConfigPayload *)payload;
			mysql_fill_PeerGlobalConfig_Datatype_To_Buffer(recordCount,dreGlobalConfigPayload,pPayload);

			break;
		case DRE_PEER_AND_TIMER:
			drePeerAndTimerConfigPayload = (DrePeerPayloadAndTimerPayload *)payload;
			mysql_fill_PeerAndTimers_Datatype_To_Buffer(recordCount,drePeerAndTimerConfigPayload,pPayload);

			break;
		case DRE_REALM_ROUTING:
			dreRealmPayload = (DreRealmRoutingPayload *)payload;
			mysql_fill_RealmRouting_Datatype_To_Buffer(recordCount,dreRealmPayload,pPayload);

			break;
		case DRE_REPLICATION_MANAGER_CONFIG:
			repMgrReplStateConfigPayload = (RepMgrReplStateConfigPayload *)payload;
			mysql_fill_RepMgrConfig_Datatype_To_Buffer(recordCount,repMgrReplStateConfigPayload,pPayload);

			break;
		case DRE_USER:
			dreUserPayload = (DreUserConfigPayload *)payload;
			mysql_fill_User_Datatype_To_Buffer(recordCount,dreUserPayload,pPayload);

			break;
		case DRE_ASF:
                        dreASFAppGroupPayload = (DreASFAppGroupPayload *)payload;
                        mysql_fill_Asf_Datatype_To_Buffer(recordCount,dreASFAppGroupPayload,pPayload);

                        break;
		case DRE_ASFCONFIG:
                        dreASFConfigPayload = (DreASFConfigPayload*)payload;
                        mysql_fill_AsfConfig_Datatype_To_Buffer(recordCount,dreASFConfigPayload,pPayload);

                        break;
		case DRE_ASFFEATURE:
                        dreASFConfigPayload = (DreASFConfigPayload*)payload;
                        mysql_fill_AsfFeature_Datatype_To_Buffer(recordCount,dreASFConfigPayload,pPayload);

                        break;
		case DRE_PEER_DICT_MAP:
                        drePeerConfigPayload = (DrePeerPayload*)payload;
                        mysql_fill_PeerDictionaryMap_Datatype_To_Buffer(recordCount,drePeerConfigPayload,pPayload);

                        break;



		default:

			PRINTF("%s:%d Default\n",__FUNCTION__,__LINE__);	
			break;
	}	
	
	PRINTF("%s:%d\n",__FUNCTION__,__LINE__);	
}


void mysql_cli_interface::mysql_fill_PeerDictionaryMap_Datatype_To_Buffer(int recordCount,DrePeerPayload *drePeerConfigReq,char *pPayload)
{
	int i;
	sprintf(pPayload + strlen(pPayload),"%s%s",sPeerDictionaryMapTableName,sPeerDictionaryMapFieldNames);

	for(i=0;i<recordCount;i++)
	{
		for(int j=0;j<drePeerConfigReq[i].peerDictionaryInfo.num_dict;j++)
		{
			sprintf(pPayload + strlen(pPayload),"%s%c",drePeerConfigReq[i].peerDictionaryInfo.peerKeyInfo.HostName,FIELD_DELIMITER);
			sprintf(pPayload + strlen(pPayload),"%s%c",drePeerConfigReq[i].peerDictionaryInfo.peerKeyInfo.RealmName,FIELD_DELIMITER);
			sprintf(pPayload + strlen(pPayload),"%d%c",drePeerConfigReq[i].peerDictionaryInfo.PeerDictionaryIds[j],ROW_DELIMITER);
		}

	}
}




void mysql_cli_interface::mysql_fill_AvaMgrConfig_Datatype_To_Buffer(int recordCount,AvaMgrConfigPayload *avaMgrConfigPayload,char *pPayload)
{
	int i;
	sprintf(pPayload + strlen(pPayload),"%s%s",sAvaMgrConfigTableName,sAvaMgrConfigFieldNames);


	for(i=0;i<recordCount;i++)
	{
		sprintf(pPayload + strlen(pPayload),"%ld%c",avaMgrConfigPayload[i].avaMgrConfigInfo.PingPeriodicity,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%ld%c",avaMgrConfigPayload[i].avaMgrConfigInfo.PingPeriodicityForArbitrator,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%ld%c",avaMgrConfigPayload[i].avaMgrConfigInfo.VirtualInterfaceActivationTime,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%ld%c",avaMgrConfigPayload[i].avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeer,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%ld%c",avaMgrConfigPayload[i].avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitrator,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%ld%c",avaMgrConfigPayload[i].avaMgrConfigInfo.ProcessRestartMaximumAllowedInterval,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%ld%c",avaMgrConfigPayload[i].avaMgrConfigInfo.ProcessRestartMaximumAllowedCount,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",avaMgrConfigPayload[i].avaMgrConfigInfo.UseIpV6,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%s%c",avaMgrConfigPayload[i].avaMgrConfigInfo.PrimaryVirtualIpAddress,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%s%c",avaMgrConfigPayload[i].avaMgrConfigInfo.SecondaryVirtualIpAddress,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%s%c",avaMgrConfigPayload[i].avaMgrConfigInfo.GatewayIpAddress,FIELD_DELIMITER);

		sprintf(pPayload + strlen(pPayload),"%d%c",avaMgrConfigPayload[i].avaMgrConfigKey.ComponentID,ROW_DELIMITER);
	}
}


void mysql_cli_interface::mysql_fill_DefaultRoute_Datatype_To_Buffer(int recordCount,DreDefaultRoutePayload *dreDefaultRoutePayload,char *pPayload)
{
	int i;
	sprintf(pPayload + strlen(pPayload),"%s%s",sDefaultRouteTableName,sDefaultRouteFieldNames);

	for(i=0;i<recordCount;i++)
	{
		sprintf(pPayload + strlen(pPayload),"%s%c",dreDefaultRoutePayload[i].defaultRouteKeyInfo.RealmName,FIELD_DELIMITER);

		sprintf(pPayload + strlen(pPayload),"%s%c",dreDefaultRoutePayload[i].defaultRouteInfo.PeerHostIds,ROW_DELIMITER);
	}
}


void mysql_cli_interface::mysql_fill_DynamicDiscovery_Datatype_To_Buffer(int recordCount,DreDynamicDiscoveryConfigPayload *dreDynamicDiscoveryPayload,char *pPayload)
{
	int i;
	sprintf(pPayload + strlen(pPayload),"%s%s",sDynamicDiscoveryTableName,sDynamicDiscoveryFieldNames);

	for(i=0;i<recordCount;i++)
	{
		sprintf(pPayload + strlen(pPayload),"%s%c",dreDynamicDiscoveryPayload[i].DynamicDiscoveryConfigInfo.peerHostNames,FIELD_DELIMITER);

		sprintf(pPayload + strlen(pPayload),"%s%c",dreDynamicDiscoveryPayload[i].DynamicDiscoveryKeyInfo.RealmName,ROW_DELIMITER);
	}

}

void mysql_cli_interface::mysql_fill_User_Datatype_To_Buffer(int recordCount,DreUserConfigPayload *dreUserPayload,char *pPayload)
{
        int i;
        int iLength = 0;
        int iLengthHeader;
        sprintf(pPayload + strlen(pPayload),"%s%s",sUserTableName,sUserFieldNames);
        iLengthHeader = strlen(pPayload);
        printf("pPayload[%d] = %x",iLengthHeader,pPayload[iLengthHeader]);

        for(i=0;i<recordCount;i++)
        {
	 memcpy(pPayload + iLengthHeader + iLength + (16*(i)),dreUserPayload[i].UserConfigInfo.password,16);
	 sprintf(pPayload + iLengthHeader + (16*(i+1)) + iLength,"%c%s%c",FIELD_DELIMITER,dreUserPayload[i].UserKeyInfo.UserName,FIELD_DELIMITER);
	 iLength += (strlen(dreUserPayload[i].UserKeyInfo.UserName)+2);
	 sprintf(pPayload + iLengthHeader + iLength + (16*(i+1)),"%d%c",dreUserPayload[i].UserConfigInfo.privilege,ROW_DELIMITER);
	 iLength = iLength + 1 + 1;
	}
}




/*void mysql_cli_interface::mysql_fill_User_Datatype_To_Buffer(int recordCount,DreUserConfigPayload *dreUserPayload,char *pPayload)
{
	int i;
    int iLength = 0;
	sprintf(pPayload + strlen(pPayload),"%s%s",sUserTableName,sUserFieldNames);

	for(i=0;i<recordCount;i++)
	{
		memcpy(pPayload + strlen(pPayload),dreUserPayload[i].UserConfigInfo.password,16);
		sprintf(pPayload + strlen(pPayload) + 16,"%c%s%c",FIELD_DELIMITER,dreUserPayload[i].UserKeyInfo.UserName,FIELD_DELIMITER);
        iLength = strlen(dreUserPayload[i].UserKeyInfo.UserName);
		sprintf(pPayload + iLength + 16,"%d%c",dreUserPayload[i].UserConfigInfo.privilege,ROW_DELIMITER);
	}

}*/
void mysql_cli_interface::mysql_fill_Asf_Datatype_To_Buffer(int recordCount,DreASFAppGroupPayload *dreASFAppGroupPayload,char *pPayload)
{
        int i;
        sprintf(pPayload + strlen(pPayload),"%s%s",sAsfTableName,sAsfFieldNames);

        for(i=0;i<recordCount;i++)
        {
		sprintf(pPayload + strlen(pPayload),"%s%c",dreASFAppGroupPayload[i].dreASFKeyInfo.GroupName,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",dreASFAppGroupPayload[i].dreASFConfigInfo.priority,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",dreASFAppGroupPayload[i].dreASFConfigInfo.appType,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%s%c",dreASFAppGroupPayload[i].dreASFConfigInfo.lbAlgorithm,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",dreASFAppGroupPayload[i].dreASFConfigInfo.maxAppInstances,FIELD_DELIMITER);


	}
}
void mysql_cli_interface::mysql_fill_AsfConfig_Datatype_To_Buffer(int recordCount,DreASFConfigPayload *dreASFConfigPayload,char *pPayload)
{
        int i;
        sprintf(pPayload + strlen(pPayload),"%s%s",sAsfConfigTableName,sAsfConfigFieldNames);

        for(i=0;i<recordCount;i++)
        {
		sprintf(pPayload + strlen(pPayload),"%d%c",dreASFConfigPayload[i].dreASFConfigKeyInfo.ComponentID,FIELD_DELIMITER);
                sprintf(pPayload + strlen(pPayload),"%d%c",dreASFConfigPayload[i].dreASFRespTimeout.responseTimeout,FIELD_DELIMITER);
	}
}
	
void mysql_cli_interface::mysql_fill_AsfFeature_Datatype_To_Buffer(int recordCount,DreASFConfigPayload *dreASFConfigPayload,char *pPayload)
{
        int i;
        sprintf(pPayload + strlen(pPayload),"%s%s",sAsfFeatureTableName,sAsfFeatureFieldNames);

        for(i=0;i<recordCount;i++)
        {
                sprintf(pPayload + strlen(pPayload),"%d%c",dreASFConfigPayload[i].dreASFConfigKeyInfo.ComponentID,FIELD_DELIMITER);
                sprintf(pPayload + strlen(pPayload),"%d%c",dreASFConfigPayload[i].dreASFStatus.ASFStatus,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",dreASFConfigPayload[i].dreASFStatus.ERLBFStatus,FIELD_DELIMITER);

        }
}



void mysql_cli_interface::mysql_fill_LocalHostConfig_Datatype_To_Buffer(int recordCount,DreLocalHostPayload *dreLocalHostPayload,char *pPayload)
{
	int i;
	sprintf(pPayload + strlen(pPayload),"%s%s",sLocalHostConfigTableName,sLocalHostConfigFieldNames);

	for(i=0;i<recordCount;i++)
	{
		sprintf(pPayload + strlen(pPayload),"%s%c",dreLocalHostPayload[i].LocalHostKeyInfo.HostName,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%s%c",dreLocalHostPayload[i].LocalHostKeyInfo.RealmName,FIELD_DELIMITER);

		sprintf(pPayload + strlen(pPayload),"%s%c",dreLocalHostPayload[i].LocalHostTransportInfo.IpAddr,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",dreLocalHostPayload[i].LocalHostTransportInfo.portno,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",dreLocalHostPayload[i].LocalHostTransportInfo.transportType,FIELD_DELIMITER);

		sprintf(pPayload + strlen(pPayload),"%ld%c",dreLocalHostPayload[i].LocalHostAuthInfo.LifeTime,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%ld%c",dreLocalHostPayload[i].LocalHostAuthInfo.GraceTime,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%ld%c",dreLocalHostPayload[i].LocalHostAuthInfo.TimeOut,FIELD_DELIMITER);

		sprintf(pPayload + strlen(pPayload),"%ld%c",dreLocalHostPayload[i].LocalHostAcctInfo.Interim,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%ld%c",dreLocalHostPayload[i].LocalHostAcctInfo.TimeOut,ROW_DELIMITER);
	}


}

void mysql_cli_interface::mysql_fill_PeerGlobalConfig_Datatype_To_Buffer(int recordCount,DrePeerGlobalConfigPayload *dreGlobalConfigPayload,char *pPayload)
{
	int i;
	sprintf(pPayload + strlen(pPayload),"%s%s",sPeerGlobalConfigTableName,sPeerGlobalConfigFieldNames);

	for(i=0;i<recordCount;i++)
	{
		sprintf(pPayload + strlen(pPayload),"%ld%c",dreGlobalConfigPayload[i].PeerGlobalConfigInfo.DiscoveryInterval,FIELD_DELIMITER);

		sprintf(pPayload + strlen(pPayload),"%d%c",dreGlobalConfigPayload[i].PeerGlobalConfigKeyInfo.ComponentID,ROW_DELIMITER);
	}


}

void mysql_cli_interface::mysql_fill_PeerAndTimers_Datatype_To_Buffer(int recordCount,DrePeerPayloadAndTimerPayload *drePeerAndTimerConfigPayload,char *pPayload)
{
	int i;
	sprintf(pPayload + strlen(pPayload),"%s%s",sPeerTableName,sPeerFieldNames);
	pPayload[strlen(pPayload) - 1] = FIELD_DELIMITER;
	sprintf(pPayload + strlen(pPayload),"%s",sPeerTimersFieldNames);


	for(i=0;i<recordCount;i++)
	{
		sprintf(pPayload + strlen(pPayload),"%s%c",drePeerAndTimerConfigPayload[i].drePeerPayload.peerKeyInfo.HostName,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%s%c",drePeerAndTimerConfigPayload[i].drePeerPayload.peerKeyInfo.RealmName,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%s%c",drePeerAndTimerConfigPayload[i].drePeerPayload.peerInfo.IpAddr,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",drePeerAndTimerConfigPayload[i].drePeerPayload.peerInfo.PortNumber,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",drePeerAndTimerConfigPayload[i].drePeerPayload.peerSwitchingInfo.Failover,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",drePeerAndTimerConfigPayload[i].drePeerPayload.peerSwitchingInfo.Failback,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",drePeerAndTimerConfigPayload[i].drePeerPayload.peerInfo.TransportType,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",drePeerAndTimerConfigPayload[i].drePeerPayload.peerInfo.TLS,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%s%c",drePeerAndTimerConfigPayload[i].drePeerPayload.peerInfo.AltHostName,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",drePeerAndTimerConfigPayload[i].drePeerPayload.peerInfo.IsMate,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",drePeerAndTimerConfigPayload[i].drePeerPayload.peerInfo.Enable_Status,FIELD_DELIMITER);

		/*Removed the HostIdentity and Realm, This values are already shown through PeerT*/
		sprintf(pPayload + strlen(pPayload),"%d%c",drePeerAndTimerConfigPayload[i].drePeerTimersConfigPayload.PeerTimersConfigInfo.watchdogValue,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",drePeerAndTimerConfigPayload[i].drePeerTimersConfigPayload.PeerTimersConfigInfo.TCValue,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",drePeerAndTimerConfigPayload[i].drePeerTimersConfigPayload.PeerTimersConfigInfo.expiryValue,ROW_DELIMITER);
	}


}

void mysql_cli_interface::mysql_fill_RealmRouting_Datatype_To_Buffer(int recordCount,DreRealmRoutingPayload *dreRealmPayload,char *pPayload)
{
	int i;
	sprintf(pPayload + strlen(pPayload),"%s%s",sRealmRoutingTableName,sRealmRoutingFieldNames);



	for(i=0;i<recordCount;i++)
	{
		sprintf(pPayload + strlen(pPayload),"%s%c",dreRealmPayload[i].realmKeyInfo.RealmName,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%s%c",dreRealmPayload[i].realmKeyInfo.PeerHostId,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%ld%c",dreRealmPayload[i].realmKeyInfo.AppId,FIELD_DELIMITER);
		
		sprintf(pPayload + strlen(pPayload),"%d%c",dreRealmPayload[i].realmInfo.LocalAction,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%ld%c",dreRealmPayload[i].realmInfo.VendorID,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",dreRealmPayload[i].realmInfo.Priority,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",dreRealmPayload[i].realmInfo.NodeDiscovery,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",dreRealmPayload[i].realmInfo.RedirectHostUsage,FIELD_DELIMITER);
		sprintf(pPayload + strlen(pPayload),"%d%c",dreRealmPayload[i].realmInfo.RedirectMaxCacheTime,ROW_DELIMITER);
	}

}


void mysql_cli_interface::mysql_fill_RepMgrConfig_Datatype_To_Buffer(int recordCount,RepMgrReplStateConfigPayload *repMgrReplStateConfigPayload,char *pPayload)
{
	int i;
	sprintf(pPayload + strlen(pPayload),"%s%s",sRepMgrConfigTableName,sRepMgrConfigFieldNames);


	for(i=0;i<recordCount;i++)
	{
		sprintf(pPayload + strlen(pPayload),"%d%c",repMgrReplStateConfigPayload[i].ReplStateConfigInfo.ReplicationState,FIELD_DELIMITER);

		sprintf(pPayload + strlen(pPayload),"%d%c",repMgrReplStateConfigPayload[i].ReplStateKeyInfo.ComponentID,ROW_DELIMITER);

	}

}
mysql_cli_interface* mysql_get_handler(void);

