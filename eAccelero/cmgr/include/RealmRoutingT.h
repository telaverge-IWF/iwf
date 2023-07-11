#ifndef REALM_ROUTING_T_H
#define REALM_ROUTING_T_H


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


class RealmRoutingTQuery
{
	protected:
		char sRealmRoutingTableName[MAX_TABLENAME_LEN];
		char sRealmRoutingFieldNames[MAX_FIELDNAME_LEN];	
		void sql_RealmRouting_Create_Check_Modifcation_Query(DreRealmRoutingPayload *peerConfigReq,char *pStatement);
		void sql_RealmRouting_Create_Add_Query(DreRealmRoutingPayload *peerConfigReq,char *pStatement);
		void sql_RealmRouting_Create_Mod_Query(DreRealmRoutingPayload *peerConfigReq,char *pStatement);
		void sql_RealmRouting_Create_Delete_Query(DreRealmRoutingPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_RealmRouting_Payload_Validation(DreRealmRoutingPayload *peerConfigReq);
        	void sql_RealmRouting_Create_Select_Query(DreRealmRoutingPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_RealmRouting_Check_All_Invalid(DreRealmRoutingPayload *peerConfigReq);
		void set_RealmRouting_Set_TableName();
		void set_RealmRouting_Set_FieldName();
};


#endif

