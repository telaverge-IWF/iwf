#ifndef AVAILABILITY_MANAGER_CONFIG_T_H
#define AVAILABILITY_MANAGER_CONFIG_T_H

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


class AvailabilityManagerConfigTQuery
{
	protected:
		char sAvaMgrConfigTableName[MAX_TABLENAME_LEN];
		char sAvaMgrConfigFieldNames[MAX_FIELDNAME_LEN];	
		void sql_AvaMgrConfig_Create_Check_Modifcation_Query(AvaMgrConfigPayload *peerConfigReq,char *pStatement);
		void sql_AvaMgrConfig_Create_Add_Query(AvaMgrConfigPayload *peerConfigReq,char *pStatement);
		void sql_AvaMgrConfig_Create_Mod_Query(AvaMgrConfigPayload *peerConfigReq,char *pStatement);
		void sql_AvaMgrConfig_Create_Delete_Query(AvaMgrConfigPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_AvaMgrConfig_Payload_Validation(AvaMgrConfigPayload *peerConfigReq);
        	void sql_AvaMgrConfig_Create_Select_Query(AvaMgrConfigPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_AvaMgrConfig_Check_All_Invalid(AvaMgrConfigPayload *peerConfigReq);
		void set_AvaMgrConfig_Set_TableName();
		void set_AvaMgrConfig_Set_FieldName();
};

#endif

