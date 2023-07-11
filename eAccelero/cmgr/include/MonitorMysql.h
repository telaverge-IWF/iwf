/*********************************-*-H-*-**************************************
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
#ifndef _MONITOR_MYSQL_H_
#define _MONITOR_MYSQL_H_


#include "mysql_connection.h"
#include "mysql_driver.h"
#include <driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "config.h"
#include "ThreadQueue.h"
#include "CMgrAlarms.h"
#include "MysqlInterfacePB.h"
#include "HAMeSSComponent.h"
#include "ConfigManager.h"

using namespace std;

class ConfigManager;

class MonitorMysql: public eAccelero::Runnable {

    public:
        MonitorMysql(){};
        MonitorMysql(ConfigManagerAlarms *pConfigManagerAlarms,uint16_t installationMode,std::map<std::string, std::string> &objConfigReaderMap,ConfigManager *pConfigManager);
        void MysqlPing();
        void MysqlReconnect();
        void Run(void *arg);
        void SetUpdateConnectionFlag(bool updateConnection);
        void UpdateConnection();
        void CheckReplicationStatus();
        void CheckSecondsBehindMaster();
    private:
        std::map<std::string, std::string> m_objConfigReaderMap;
        bool isClosed;
        bool isReplicationFailed;
        uint16_t m_installationMode;
        ConfigManagerAlarms *m_ConfigManagerAlarms;
		sql::Driver *driver;
        sql::Connection *con_ping;
        sql::Connection *con_replication;
        sql::ConnectOptionsMap connection_properties;
        sql::ConnectOptionsMap connection_properties_replicaton;
        string virtualIP;
        ConfigManager *pCMgr;
        bool updateConnectionFlag;
        int cmgr_waittime;

}; //class MonitorMysql


#endif
