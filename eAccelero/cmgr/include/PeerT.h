#ifndef PEERT_QUERY_H
#define PEERT_QUERY_H


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


class PeerTQuery
{
	protected:
		char sPeerTableName[MAX_TABLENAME_LEN];
		char sPeerFieldNames[MAX_FIELDNAME_LEN];	
		void sql_Peer_Create_Check_Modifcation_Query(DrePeerPayload *peerConfigReq,char *pStatement);
		void sql_Peer_Create_Add_Query(DrePeerPayload *peerConfigReq,char *pStatement);
		void sql_Peer_Create_Mod_Query(DrePeerPayload *peerConfigReq,char *pStatement);
		void sql_Peer_Create_Delete_Query(DrePeerPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_Peer_Payload_Validation(DrePeerPayload *peerConfigReq);
        	void sql_Peer_Create_Select_Query(DrePeerPayload *peerConfigReq,char *pStatement);
		DbStatus_e sql_Peer_Check_All_Invalid(DrePeerPayload *peerConfigReq);
		void set_Peer_Set_TableName();
		void set_Peer_Set_FieldName();
};
#endif
