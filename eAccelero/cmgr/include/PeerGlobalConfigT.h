#ifndef PEER_GLOBAL_CONFIG_T_QUERY_H
#define PEER_GLOBAL_CONFIG_T_QUERY_H

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

#include <CommonStructure.h>
#include <config.h>


class PeerGlobalConfigTQuery
{
	protected:
		char sPeerGlobalConfigTableName[MAX_TABLENAME_LEN];
		char sPeerGlobalConfigFieldNames[MAX_FIELDNAME_LEN];	
		void sql_PeerGlobalConfig_Create_Check_Modifcation_Query(DrePeerGlobalConfigPayload *peerConfigReq,char *pStatement);
		void sql_PeerGlobalConfig_Create_Add_Query(DrePeerGlobalConfigPayload *peerConfigReq,char *pStatement);
		void sql_PeerGlobalConfig_Create_Mod_Query(DrePeerGlobalConfigPayload *peerConfigReq,char *pStatement);
		void sql_PeerGlobalConfig_Create_Delete_Query(DrePeerGlobalConfigPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_PeerGlobalConfig_Payload_Validation(DrePeerGlobalConfigPayload *peerConfigReq);
        	void sql_PeerGlobalConfig_Create_Select_Query(DrePeerGlobalConfigPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_PeerGlobalConfig_Check_All_Invalid(DrePeerGlobalConfigPayload *peerConfigReq);
		void set_PeerGlobalConfig_Set_TableName();
		void set_PeerGlobalConfig_Set_FieldName();
};

#endif
