#ifndef PEER_TIMERS_T_QUERY_H
#define PEER_TIMERS_T_QUERY_H


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


class PeerTimersTQuery
{
	protected:
		char sPeerTimersTableName[MAX_TABLENAME_LEN];
		char sPeerTimersFieldNames[MAX_FIELDNAME_LEN];	
		void sql_PeerTimers_Create_Check_Modifcation_Query(DrePeerTimersConfigPayload *peerConfigReq,char *pStatement);
		void sql_PeerTimers_Create_Add_Query(DrePeerTimersConfigPayload *peerConfigReq,char *pStatement);
		void sql_PeerTimers_Create_Mod_Query(DrePeerTimersConfigPayload *peerConfigReq,char *pStatement);
		void sql_PeerTimers_Create_Delete_Query(DrePeerTimersConfigPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_PeerTimers_Payload_Validation(DrePeerTimersConfigPayload *peerConfigReq);
        	void sql_PeerTimers_Create_Select_Query(DrePeerTimersConfigPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_PeerTimers_Check_All_Invalid(DrePeerTimersConfigPayload *peerConfigReq);
		void set_PeerTimers_Set_TableName();
		void set_PeerTimers_Set_FieldName();
};
#endif
