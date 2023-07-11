#ifndef DEFAULT_ROUTE_T_H
#define DEFAULT_ROUTE_T_H


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


class DefaultRouteTQuery
{
	protected:
		char sDefaultRouteTableName[MAX_TABLENAME_LEN];
		char sDefaultRouteFieldNames[MAX_FIELDNAME_LEN];	
		void sql_DefaultRoute_Create_Check_Modifcation_Query(DreDefaultRoutePayload *peerConfigReq,char *pStatement);
		void sql_DefaultRoute_Create_Add_Query(DreDefaultRoutePayload *peerConfigReq,char *pStatement);
		void sql_DefaultRoute_Create_Mod_Query(DreDefaultRoutePayload *peerConfigReq,char *pStatement);
		void sql_DefaultRoute_Create_Delete_Query(DreDefaultRoutePayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_DefaultRoute_Payload_Validation(DreDefaultRoutePayload *peerConfigReq);
        	void sql_DefaultRoute_Create_Select_Query(DreDefaultRoutePayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_DefaultRoute_Check_All_Invalid(DreDefaultRoutePayload *peerConfigReq);
		void set_DefaultRoute_Set_TableName();
		void set_DefaultRoute_Set_FieldName();
};

#endif

