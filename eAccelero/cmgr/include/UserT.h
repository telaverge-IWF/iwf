#ifndef USER_T_H
#define USER_T_H


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


class UserTQuery
{
	protected:
		char sUserTableName[MAX_TABLENAME_LEN];
		char sUserFieldNames[MAX_FIELDNAME_LEN];	
		void sql_User_Create_Check_Modifcation_Query(DreUserConfigPayload *peerConfigReq,char *pStatement);
		void sql_User_Create_Add_Query(DreUserConfigPayload *peerConfigReq,char *pStatement);
		void sql_User_Create_Mod_Query(DreUserConfigPayload *peerConfigReq,char *pStatement);
		void sql_User_Create_Delete_Query(DreUserConfigPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_User_Payload_Validation(DreUserConfigPayload *peerConfigReq);
        	void sql_User_Create_Select_Query(DreUserConfigPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_User_Check_All_Invalid(DreUserConfigPayload *peerConfigReq);
		void set_User_Set_TableName();
		void set_User_Set_FieldName();
};

#endif

