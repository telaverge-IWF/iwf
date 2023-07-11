#ifndef LOCAL_HOST_CONFIG_SINGLE_ROW_T_PB_H
#define LOCAL_HOST_CONFIG_SINGLE_ROW_T_PB_H


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


class LocalHostConfigSingleRowTPBQuery
{
	public:
		void sql_LocalHostConfig_Create_Check_Modifcation_Query(LocalHostConfig *peerConfigReq,char *pStatement);
		void sql_LocalHostConfig_Create_Add_Query(LocalHostConfig *peerConfigReq,char *pStatement);
		void sql_LocalHostConfig_Create_Mod_Query(LocalHostConfig *peerConfigReq,char *pStatement);
		void sql_LocalHostConfig_Create_Delete_Query(LocalHostConfig *peerConfigReq,char *pStatement);
		DbStatus_e sql_LocalHostConfig_Payload_Validation(LocalHostConfig *peerConfigReq);
        	void sql_LocalHostConfig_Create_Select_Query(LocalHostConfig *peerConfigReq,char *pStatement);
		DbStatus_e sql_LocalHostConfig_Check_All_Invalid(LocalHostConfig *peerConfigReq);
};

#endif

