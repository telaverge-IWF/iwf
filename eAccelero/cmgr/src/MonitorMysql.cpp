/*********************************-*-C++-*-************************************
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

#include "MonitorMysql.h"
#include "ConfigReader.h"
#include "config.h"

using namespace std;


MonitorMysql::MonitorMysql(ConfigManagerAlarms *pConfigManagerAlarms,uint16_t installationMode,std::map<std::string, std::string> &objConfigReaderMap,ConfigManager *pConfigManager)
{
    CLOG_DEBUG("Entered MonitoryMysql::MonitorMysql()");
    updateConnectionFlag=false;
    m_ConfigManagerAlarms = pConfigManagerAlarms;
    string sHostname ="127.0.0.1";
    m_installationMode = installationMode;
    isClosed = false;
    isReplicationFailed = false;
    con_ping = NULL;
    con_replication = NULL;
    pCMgr = pConfigManager;

    map<string, string>::const_iterator map_iterator;

    string dbProtocol;
    string dbHost;
    string dbPort;
    string dbUser;
    string dbPass;
    string WaitTimeToSync;
    string mysqlCfgInfo;
    string sCMgrWaittime="";

    mysqlCfgInfo += "Mysql Server configuration:\n";

    m_objConfigReaderMap = objConfigReaderMap;
    for (map_iterator = m_objConfigReaderMap.begin(); map_iterator != m_objConfigReaderMap.end(); map_iterator++)
    {
        mysqlCfgInfo += map_iterator->first;
        mysqlCfgInfo += " ==>";
        mysqlCfgInfo += map_iterator->second;
        mysqlCfgInfo += "\n";
    }
    CLOG_DEBUG(mysqlCfgInfo.c_str());

    //          map<string, string>::const_iterator map_iterator;

    map_iterator = m_objConfigReaderMap.find("db_protocol");
    if (map_iterator != m_objConfigReaderMap.end()) {
        dbProtocol = map_iterator->second;
    }

    map_iterator = m_objConfigReaderMap.find("db_host");
    if (map_iterator != m_objConfigReaderMap.end()) {
        dbHost = map_iterator->second;
    }

    map_iterator = m_objConfigReaderMap.find("db_port");
    if (map_iterator != m_objConfigReaderMap.end()) {
        dbPort = map_iterator->second;
    }

    map_iterator = m_objConfigReaderMap.find("db_user");
    if (map_iterator != m_objConfigReaderMap.end()) {
        dbUser = map_iterator->second;
    }

    map_iterator = m_objConfigReaderMap.find("db_pass");
    if (map_iterator != m_objConfigReaderMap.end()) {
        dbPass = map_iterator->second;
    }

    map_iterator = m_objConfigReaderMap.find("cmgr_waittime");
    if (map_iterator != m_objConfigReaderMap.end()) {
        sCMgrWaittime = map_iterator->second;
        if(sCMgrWaittime != "")
        {
             cmgr_waittime = atoi(sCMgrWaittime.c_str());
        }
    }
    else
    {
        cmgr_waittime = 5;
    }


    try
    {
        driver = sql::mysql::get_driver_instance();
        virtualIP=dbHost;
        connection_properties["hostName"]=dbHost;
        connection_properties_replicaton["hostName"]=sHostname;
        connection_properties["userName"]=dbUser;
        connection_properties_replicaton["userName"]=dbUser;
        connection_properties["password"]=dbPass;
        connection_properties_replicaton["password"]=dbPass;
        connection_properties["OPT_RECONNECT"]=true;
        connection_properties_replicaton["OPT_RECONNECT"]=true;

    }
    catch (sql::SQLException &e)
    {
        CLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        CLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        exit(0);
    }

}

void MonitorMysql::Run(void* arg)
{
    try
    {

        //Calling for this auto clearance
        m_ConfigManagerAlarms->RaiseMysqlUpAlarm();
        m_ConfigManagerAlarms->RaiseReplicationUpAlarm();
        m_ConfigManagerAlarms->RaiseReplicationNotInSyncAlarm();
        con_ping = driver->connect(connection_properties);
    }
    catch (sql::SQLException &e)
    {
        CLOG_ERROR("Failed to connecto to %s",virtualIP.c_str());
        CLOG_ERROR("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        try

        {
	    //failed to connect to VIP so fall back and connect to localhost
            string localHost=LOCAL_HOST_IP;
            connection_properties["hostName"]=localHost;
            con_ping = driver->connect(connection_properties);
            isClosed = false;
            CLOG_DEBUG("MonitorMysql connected to localhost");

        }
        catch(sql::SQLException &e)
        {
            CLOG_DEBUG("MonitorMysql Could not connect to localhost");
            exit(0);
        }
    }


    MysqlPing();
}

void MonitorMysql::MysqlReconnect()
{

    try
    {
        con_ping = driver->connect(connection_properties);

        isClosed = false;
        m_ConfigManagerAlarms->RaiseMysqlUpAlarm();
    }
    catch (sql::SQLException &e)
    {
        CLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        CLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
    }
}

void MonitorMysql::UpdateConnection()
{
    if(con_ping)
    {
        if(!con_ping->isClosed())
        {
            CLOG_DEBUG("Closing localhost connection");
            con_ping->close();
            delete con_ping;
            con_ping=NULL;
                    }
    }
    connection_properties["hostName"]=virtualIP;
    try
    {
        con_ping=driver->connect(connection_properties);
        isClosed=false;
    }
    catch(sql::SQLException &e)
    {
	CLOG_WARNING("MonitorMysql could not connect to VIP %s",virtualIP.c_str());
	isClosed=true;
    }

}

void MonitorMysql::CheckReplicationStatus()
{
    if(m_installationMode != STANDALONE_MODE)
    {
        try
        {
            if(con_replication == NULL || con_replication->isClosed())
            {
                con_replication = driver->connect(connection_properties_replicaton);
            }
            if(!con_replication->isClosed())
            {
                sql::ResultSet *pRes = NULL;
                char sStatement[MAX_STATEMENT_SIZE] = {"show slave status"};
                sql::PreparedStatement *pPreStmt = NULL;

                pPreStmt = con_replication->prepareStatement(sStatement);

                if(pPreStmt != NULL)
                {
                    pRes = pPreStmt->executeQuery();
                    if(pRes->next())
                    {
                       if(!pRes->isNull("Slave_IO_State")) 
                       {
                           string sStatus;
                           int iError;
                           sStatus = pRes->getString("Slave_IO_State");
                           iError = pRes->getInt("Last_IO_Errno");
                           CLOG_INFO("Slave_IO_State = %s, iError = %d",sStatus.c_str(), iError);
                           if(iError == 0)
                           {
                               if(isReplicationFailed)
                               {
                                    //Raise alarm for Mysql Replication is restored
                                    m_ConfigManagerAlarms->RaiseReplicationUpAlarm();
                                    isReplicationFailed = false;
                               }
                           }
                           else
                           {
                                CLOG_CRITICAL("Slave_IO_State = %s, iError = %d",sStatus.c_str(), iError);
                                if(!isReplicationFailed)
                                {
                                    //Raise alarm for Mysql Replication failed
                                    m_ConfigManagerAlarms->RaiseReplicationDownAlarm();
                                    isReplicationFailed = true;
                                }
                           }
                       }
                    }
                    delete pRes;
                    pPreStmt->close();
                    delete pPreStmt;
                }
            //    con_replication->close();
            }
        }
        catch (sql::SQLException &e)
        {
            CLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
            
        }
    }
}

void MonitorMysql::MysqlPing()
{

    CheckSecondsBehindMaster();

    pCMgr->UpdateSelfStatus();

    while(1)
    {
        try
        {
            if(updateConnectionFlag)
            {
                CLOG_DEBUG("UpdateConnectionFlag is set so destroying connections to localhost and reestablish connections with VIP");
                UpdateConnection();
                updateConnectionFlag=false;
            }
            if(!isClosed)
            {
                if(con_ping->isClosed())
                {
                    isClosed = true;
                    m_ConfigManagerAlarms->RaiseMysqlDownAlarm();

                    con_ping->close();
                }
            }
            else
            {
                MysqlReconnect();
            }
            CheckReplicationStatus();
        }
        catch (sql::SQLException &e)
        {
            CLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
            CLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        }
        sleep(1);
    }

}

void MonitorMysql::CheckSecondsBehindMaster()
{
    CLOG_DEBUG(" > %s",__FUNCTION__);
    if(m_installationMode != STANDALONE_MODE)
    {
        int iSecondsBehind = -1;
        int iCount = cmgr_waittime;
        CLOG_DEBUG(" iCount = %d\n",iCount);

        while(--iCount > 0)
        {
            CLOG_DEBUG(" iCount = %d\n",iCount);
            
            try
            {
                if(con_replication == NULL || con_replication->isClosed())
                {
                    con_replication = driver->connect(connection_properties_replicaton);
                }
                if(!con_replication->isClosed())
                {
                    sql::ResultSet *pRes = NULL;
                    char sStatement[MAX_STATEMENT_SIZE] = {"show slave status"};
                    sql::PreparedStatement *pPreStmt = NULL;

                    pPreStmt = con_replication->prepareStatement(sStatement);

                    if(pPreStmt != NULL)
                    {
                        pRes = pPreStmt->executeQuery();
                        if(pRes->next())
                        {
                          if(!pRes->isNull("Seconds_Behind_Master")) 
                          {
                               string sStatus;
                               int iError;
                               iSecondsBehind = pRes->getInt("Seconds_Behind_Master");
                               sStatus = pRes->getString("Slave_IO_State");
                               iError = pRes->getInt("Last_IO_Errno");
                               CLOG_INFO("Seconds_Behind_Master = %d iError = %d",iSecondsBehind, iError);
			       if(sStatus != "" && iError != 0 && iSecondsBehind == 0)
			       {
				   delete pRes;
				   pPreStmt->close();
				   delete pPreStmt;
				   CLOG_INFO("Mysql Is in Sync");
				   break;
			       }
                               else
                               {
                                   CLOG_CRITICAL("sStatus = %s Seconds_Behind_Master = %d, iError = %d, waiting to sync/Error to resolved",sStatus.c_str(),iSecondsBehind,iError);
                                   sleep(1);
                               }
                           }
                        }
                        delete pRes;
                        pPreStmt->close();
                        delete pPreStmt;
                    }
                //    con_replication->close();
                }
		else
		{
		   CLOG_DEBUG("Connection is in close state");
		}
            }
            catch (sql::SQLException &e)
            {
                 CLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
                 sleep(1);
            
            }
        }

        if(iSecondsBehind > 0)
        {
            m_ConfigManagerAlarms->RaiseReplicationNotInSyncAlarm();
        }
    }
    CLOG_DEBUG(" < %s",__FUNCTION__);
}


void MonitorMysql::SetUpdateConnectionFlag(bool updateConnection)
{
    updateConnectionFlag=updateConnection;
}
