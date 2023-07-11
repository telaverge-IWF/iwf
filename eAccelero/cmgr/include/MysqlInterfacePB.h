/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/


#ifndef MYSQL_INTERFACE_PB_H
#define MYSQL_INTERFACE_PB_H

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
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

#include "HAMeSSComponent.h"
#include <CommonStructure.h>
#include <config.h>

#include <dreconfig_def.h>
#include <Compo_def.h>
#include <Compo_def.h>
#include <ErrorResp.h>
#include <IwfErrorResp.h>
#include "CMgrAlarms.h"

#define MAX_MYSQL_CONNECTION 5
#define MAX_RETRY_CONNECTION 3


typedef struct ConnectionPool
{
	sql::Connection *con;
	bool status;
} ConnectionPool_t;

class MysqlInterfacePB
{
	private:
		sql::Driver * driver;
		ConnectionPool_t connectionlist[MAX_MYSQL_CONNECTION];
		sql::Connection *cur_con;
		sql::ConnectOptionsMap connection_properties;
		bool mysql_conn_pool_status;
        ConfigManagerAlarms *m_ConfigManagerAlarms;
        bool connectedToLocalHost;


	public:
		~MysqlInterfacePB();
		MysqlInterfacePB(std::string sHostName,std::string sUserName,std::string sPassword,std::string sDataBase,ConfigManagerAlarms *pConfigManagerAlarms);
		DbStatus_e mysql_exec_set_query(char *pStatement);
        DbStatus_e mysql_exec_and_check_get_query(char *pStatement);
		DbStatus_e mysql_exec_get_query(char *pStatement,sql::ResultSet **pRes, void *connFromCookie=NULL);
        DbStatus_e mysql_exec_get_resultset_count(char *pStatement,sql::ResultSet **pRes,int *iCount);


		DbStatus_e mysql_exec_set_query_for_user_table(char *pStatement,std::istringstream *encryptPassword,bool PasswordIsSet);
		DbStatus_e mysql_exec_get_query_for_user_table(char *pStatement,sql::ResultSet **pRes,std::istringstream *encryptPassword,bool PasswordIsSet);

		DbStatus_e mysql_set_current_connection();
		DbStatus_e mysql_unset_connection(sql::Connection *con);
		void mysql_release_current_connection();
		void* mysql_get_current_connection();
		DbStatus_e mysql_exec_commit(void *con);
		DbStatus_e mysql_exec_rollback(void *con);
		DbStatus_e mysql_close_all_connection();
        DbStatus_e mysql_check_error_code(int iMysqlErrorCode);
		int mysql_reconnect_connection();
        void mysql_set_connection_hostname(std::string hostname);
        bool isConnectedToLocalHost();
        void setLocalHostConnectionFlag(bool isLocal);
};


#endif
