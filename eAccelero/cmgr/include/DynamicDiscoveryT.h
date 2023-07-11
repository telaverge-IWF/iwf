#ifndef DYNAMIC_DISCOVERY_T_H
#define DYNAMIC_DISCOVERY_T_H


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


class DynamicDiscoveryTQuery
{
	protected:
		char sDynamicDiscoveryTableName[MAX_TABLENAME_LEN];
		char sDynamicDiscoveryFieldNames[MAX_FIELDNAME_LEN];	
		void sql_DynamicDiscovery_Create_Check_Modifcation_Query(DreDynamicDiscoveryConfigPayload *peerConfigReq,char *pStatement);
		void sql_DynamicDiscovery_Create_Add_Query(DreDynamicDiscoveryConfigPayload *peerConfigReq,char *pStatement);
		void sql_DynamicDiscovery_Create_Mod_Query(DreDynamicDiscoveryConfigPayload *peerConfigReq,char *pStatement);
		void sql_DynamicDiscovery_Create_Delete_Query(DreDynamicDiscoveryConfigPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_DynamicDiscovery_Payload_Validation(DreDynamicDiscoveryConfigPayload *peerConfigReq);
        	void sql_DynamicDiscovery_Create_Select_Query(DreDynamicDiscoveryConfigPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_DynamicDiscovery_Check_All_Invalid(DreDynamicDiscoveryConfigPayload *peerConfigReq);
		void set_DynamicDiscovery_Set_TableName();
		void set_DynamicDiscovery_Set_FieldName();
};

#endif

