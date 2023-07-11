#ifndef LOCAL_HOST_CONFIG_T_H
#define LOCAL_HOST_CONFIG_T_H


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


class LocalHostConfigTQuery
{
	protected:
		char sLocalHostConfigTableName[MAX_TABLENAME_LEN];
		char sLocalHostConfigFieldNames[MAX_FIELDNAME_LEN];	
		void sql_LocalHostConfig_Create_Check_Modifcation_Query(DreLocalHostPayload *peerConfigReq,char *pStatement);
		void sql_LocalHostConfig_Create_Add_Query(DreLocalHostPayload *peerConfigReq,char *pStatement);
		void sql_LocalHostConfig_Create_Mod_Query(DreLocalHostPayload *peerConfigReq,char *pStatement);
		void sql_LocalHostConfig_Create_Delete_Query(DreLocalHostPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_LocalHostConfig_Payload_Validation(DreLocalHostPayload *peerConfigReq);
        	void sql_LocalHostConfig_Create_Select_Query(DreLocalHostPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_LocalHostConfig_Check_All_Invalid(DreLocalHostPayload *peerConfigReq);
		void set_LocalHostConfig_Set_TableName();
		void set_LocalHostConfig_Set_FieldName();
};

#endif

