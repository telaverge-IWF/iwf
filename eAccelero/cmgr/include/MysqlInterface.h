#ifndef MYSQL_CLI_INTERFACE_H
#define MYSQL_CLI_INTERFACE_H

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <driver.h>
#include <string.h>
#include <stdio.h>

#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


#include <Query.h>
#include <CommonStructure.h>
#include <config.h>


class mysql_cli_interface : private Query
{
	private:
		sql::Driver * driver;
		sql::Connection *con;
		sql::ConnectOptionsMap connection_properties;
		
		DbStatus_e mysql_Add_Row(drePayload *payloadConfigReq,dreTableName_e dreTableName);
		DbStatus_e mysql_Modify_Row(drePayload *payloadConfigReq,dreTableName_e dreTableName);
		DbStatus_e mysql_Delete_Row(drePayload *payloadConfigReq,dreTableName_e dreTableName);
		DbStatus_e mysql_Get_Record(drePayload *payloadConfigReq,GetConfigRsp *resultSet,dreTableName_e dreTableName,int table_number);
        	DbStatus_e mysql_Fill_Record(GetConfigRsp *resultSet,dreTableName_e dreTableName,sql::ResultSet *pRes,int table_number);
		DbStatus_e mysql_Payload_Validation(drePayload *payloadConfigReq,dreTableName_e dreTableName);
		ConfigReqType_e mysql_Check_Modifcation(drePayload *payloadConfigReq,dreTableName_e dreTableName);
		DbStatus_e mysql_exec_oper(drePayload *pPayload,dreTableName_e tableName,OpCode_e oprtype);
		void mysql_Set_Searchkey(GetConfigReq configReq,drePayload *localPayload,int showID);
		void mysql_Rsp_To_Buffer(GetConfigRsp *resultSet,AllResponses *rsp);
		void mysql_Datatype_To_Buffer(dreDataType_e datatype_name,int recordCount,drePayload *payload, char *pPayload);
		

		void mysql_fill_AvaMgrConfig_Datatype_To_Buffer(int recordCount,AvaMgrConfigPayload *avaMgrConfigPayload,char *pPayload);
		void mysql_fill_DefaultRoute_Datatype_To_Buffer(int recordCount,DreDefaultRoutePayload *dreDefaultRoutePayload,char *pPayload);
		void mysql_fill_DynamicDiscovery_Datatype_To_Buffer(int recordCount,DreDynamicDiscoveryConfigPayload *dreDynamicDiscoveryPayload,char *pPayload);
		void mysql_fill_LocalHostConfig_Datatype_To_Buffer(int recordCount,DreLocalHostPayload *dreLocalHostPayload,char *pPayload);
		void mysql_fill_PeerGlobalConfig_Datatype_To_Buffer(int recordCount,DrePeerGlobalConfigPayload *dreGlobalConfigPayload,char *pPayload);
		void mysql_fill_PeerAndTimers_Datatype_To_Buffer(int recordCount,DrePeerPayloadAndTimerPayload *drePeerAndTimerConfigPayload,char *pPayload);
		void mysql_fill_RealmRouting_Datatype_To_Buffer(int recordCount,DreRealmRoutingPayload *dreRealmPayload,char *pPayload);
		void mysql_fill_RepMgrConfig_Datatype_To_Buffer(int recordCount,RepMgrReplStateConfigPayload *repMgrReplStateConfigPayload,char *pPayload);
		void mysql_fill_User_Datatype_To_Buffer(int recordCount,DreUserConfigPayload *dreUserPayload,char *pPayload);
		void mysql_fill_Asf_Datatype_To_Buffer(int recordCount,DreASFAppGroupPayload *dreAsfAppPayload,char *pPayload);
		void mysql_fill_AsfConfig_Datatype_To_Buffer(int recordCount,DreASFConfigPayload *dreASFConfigPayload,char *pPayload);
		void mysql_fill_AsfFeature_Datatype_To_Buffer(int recordCount,DreASFConfigPayload *dreASFConfigPayload,char *pPayload);
		void mysql_fill_PeerDictionaryMap_Datatype_To_Buffer(int recordCount,DrePeerPayload *drePeerConfigReq,char *pPayload);


        	DbStatus_e mysql_Fill_AvaMgrConfig_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number);
        	DbStatus_e mysql_Fill_DefaultRoute_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number);
        	DbStatus_e mysql_Fill_DynamicDiscovery_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number);
        	DbStatus_e mysql_Fill_LocalHostConfig_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number);
        	DbStatus_e mysql_Fill_PeerGlobalConfig_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number);
        	DbStatus_e mysql_Fill_Peer_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number);
        	DbStatus_e mysql_Fill_PeerTimers_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number);
        	DbStatus_e mysql_Fill_RealmRouting_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number);
        	DbStatus_e mysql_Fill_RepMgrConfig_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number);
        	DbStatus_e mysql_Fill_User_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number);
		DbStatus_e mysql_Fill_Asf_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number);
		DbStatus_e mysql_Fill_AsfConfig_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number);
		DbStatus_e mysql_Fill_AsfFeature_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number);
		DbStatus_e mysql_Fill_PeerDictionaryMap_Record(GetConfigRsp *resultSet,sql::ResultSet *pRes,int table_number);



		DbStatus_e mysql_cli_handling_dictionaryid_req(drePayload *pPayload,OpCode_e opCode);
	public:	
		mysql_cli_interface(std::string sHostName,std::string sUserName,std::string sPassword,std::string sDataBase);
		mysql_cli_interface* mysql_get_handler(void);
		DbStatus_e mysql_Payload(SetConfigReq configReq);
		DbStatus_e mysql_Payload(GetConfigReq configReq,AllResponses *rsp);
};

#endif
