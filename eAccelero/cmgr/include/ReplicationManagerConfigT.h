#ifndef REPLICATION_MANAGER_CONFIG_T_H
#define REPLICATION_MANAGER_CONFIG_T_H


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


class ReplicationManagerConfigTQuery
{
	protected:
		char sRepMgrConfigTableName[MAX_TABLENAME_LEN];
		char sRepMgrConfigFieldNames[MAX_FIELDNAME_LEN];	
		void sql_RepMgrConfig_Create_Check_Modifcation_Query(RepMgrReplStateConfigPayload *peerConfigReq,char *pStatement);
		void sql_RepMgrConfig_Create_Add_Query(RepMgrReplStateConfigPayload *peerConfigReq,char *pStatement);
		void sql_RepMgrConfig_Create_Mod_Query(RepMgrReplStateConfigPayload *peerConfigReq,char *pStatement);
		void sql_RepMgrConfig_Create_Delete_Query(RepMgrReplStateConfigPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_RepMgrConfig_Payload_Validation(RepMgrReplStateConfigPayload *peerConfigReq);
        	void sql_RepMgrConfig_Create_Select_Query(RepMgrReplStateConfigPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_RepMgrConfig_Check_All_Invalid(RepMgrReplStateConfigPayload *peerConfigReq);
		void set_RepMgrConfig_Set_TableName();
		void set_RepMgrConfig_Set_FieldName();
};


#endif

