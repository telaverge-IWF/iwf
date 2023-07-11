#ifndef PEER_TIMERS_T_PB_QUERY_H
#define PEER_TIMERS_T_PB_QUERY_H


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

#include <CMAPICMgr.h>
#include <CMAPICommon.h>

#include <CommonStructure.h>
#include <config.h>


class PeerTimersTPBQuery
{
	public:
		void sql_PeerTimers_Create_Check_Modifcation_Query(PeerConfig *peerConfigReq,char *pStatement);
		void sql_PeerTimers_Create_Add_Query(PeerConfig *peerConfigReq,char *pStatement);
		void sql_PeerTimers_Create_Mod_Query(PeerConfig *peerConfigReq,char *pStatement);
		void sql_PeerTimers_Create_Delete_Query(PeerConfig *peerConfigReq,char *pStatement);
		DbStatus_e sql_PeerTimers_Payload_Validation(PeerConfig *peerConfigReq);
        	void sql_PeerTimers_Create_Select_Query(PeerConfig *peerConfigReq,char *pStatement);
		DbStatus_e sql_PeerTimers_Check_All_Invalid(PeerConfig *peerConfigReq);
};
#endif
