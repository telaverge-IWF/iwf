/*********************************-*-CPP-*-************************************
 *                                                                          *
 *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 *            Manufactured in the United States of America.                 *
 *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of Diametriq and its licensors, if any.                  *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************/

#include <string>
#include <map>

#include "HAMeSSComponent.h"
#include "ConfigReader.h"
#include "CMAPICMgr.h"
#include "CMAPIIwfCMgr.h"

using namespace std;
using namespace eAccelero;

ConfigManager::ConfigManager(uint16_t instanceId,uint16_t installationMode, std::map<std::string, std::string> &objConfigReaderMap,ConfigManagerAlarms **pconfigManagerAlarms) 
    : HAMeSSComponent("CMGR", COMP_CONFIG_MANAGER),
    m_logger("CMGR"),
    m_syslogChannel("CMGR",(LOG_PID),LOG_LOCAL6)
    /*currently we are using syslog and to avoid
      unneccessary file being generated in the /var/log/dre */
    //m_fileLogChannel("ConfigManager.log", getenv("DRE_LOG_DIR"))
{
    CLOG_NOTICE("CmgrMess Constructor");

    monitorConnection=false;
    Logger::currLogger = &m_logger;
    m_InstallationMode = installationMode;

    this->InitLog();
    ScopedLogger scopedLogger(this->GetLogger());

    m_configManagerAlarms = new ConfigManagerAlarms(instanceId,COMP_CONFIG_MANAGER);
    *pconfigManagerAlarms = m_configManagerAlarms;

    string dbProtocol;
    string dbHost;
    string dbPort;
    string dbUser;
    string dbPass;

    map<string, string>::const_iterator map_iterator;

    string mysqlCfgInfo;
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

    try
    {
        m_cmapiInterface = new CMAPICMgr(dbHost,dbUser,dbPass,DATABASE, instanceId,m_configManagerAlarms,this);
        m_cmapiIwfInterface = new CMAPIIwfCMgr(dbHost,dbUser,dbPass,DATABASE, instanceId,m_configManagerAlarms,this);
        InitializeLogConfig();
    }
    catch(Exception &e)
    {
        CLOG_ERROR(e.what());
    }
    catch(exception &e)
    {
        CLOG_ERROR(e.what());
    }

}



void ConfigManager::InitializeLogConfig()
{

    LoggerConfReq localLoggerConfReq;
    LoggerConfResp localLoggerConfResp;
    LoggerConf *pLoggingConfig;


    pLoggingConfig = localLoggerConfReq.add_loggerconfig();

    pLoggingConfig->set_componentname("CMGR");

    if(DRE_DB_FAIL == m_cmapiInterface->m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");       
        return;
    }
    m_cmapiInterface->m_dbInterface->mysql_Logging_Get_Config_Reqs(&localLoggerConfReq,&localLoggerConfResp);


    if(!localLoggerConfResp.loggerconfig_size())
    {
        DLOG_CRITICAL("CMGR Logger is not Configured");
        return;
    }

    pLoggingConfig = localLoggerConfResp.mutable_loggerconfig(0);

    string componentname = pLoggingConfig->componentname();
    int log_level = pLoggingConfig->level();
    int log_channel = pLoggingConfig->channel();

    SetLogChannel(log_channel);
    SetLogLevel(log_level);
}


void ConfigManager::Initialize()
{
    HAMeSSComponent::Initialize();
}

void ConfigManager::UpdateSelfStatus()
{
    /*Since DB connections are initialized and MeSS is also initialized
     * update the Status as Initialized
     */
    UpdateComponentSelfStatus(COMPONENT_STATUS_INITIALIZED);
}

void ConfigManager::Terminate()
{
    HAMeSSComponent::Terminate();
}

void ConfigManager::RegisterMethods()
{
    CLOG_DEBUG("Registering methods...");
}

int ConfigManager::ProcessAvailabilityStatusResetPreFunc(uint16_t newInstanceId)
{
    m_configManagerAlarms->UpdateDestInstanceId(newInstanceId);
    m_cmapiInterface->UpdateInstanceId(newInstanceId);
    m_cmapiIwfInterface->UpdateInstanceId(newInstanceId);
    
    return 0;
}

int ConfigManager::ProcessAvailabilityStatusResetPostFunc(bool isPlannedSwitchOver)
{
    CLOG_DEBUG("%d >>ProcessAvailabilityStatusResetPostFunc >>",isPlannedSwitchOver);

    if(m_InstallationMode != 1)
    {
        m_cmapiInterface->m_dbInterface->m_dbHandle.mysql_set_connection_hostname("localhost");
        m_cmapiIwfInterface->m_IwfdbInterface->m_dbHandle.mysql_set_connection_hostname("localhost");
        m_cmapiInterface->m_dbInterface->m_dbHandle.mysql_reconnect_connection();
        m_cmapiIwfInterface->m_IwfdbInterface->m_dbHandle.mysql_reconnect_connection();
    }

    CLOG_DEBUG("%d >>ProcessAvailabilityStatusResetPostFunc >>",isPlannedSwitchOver);
    return 0;
}

int ConfigManager::ProcessComponentStatusUpdate(uint16_t componentId,HAComponentStatus newStatus)
{
    return 0;
}


#if 0
int ConfigManager::ShowUser(GetConfigReq *req, AllResponses *rsp)
{
    CLOG_DEBUG("Show user");
    m_dbHandler->mysql_Payload(*req, rsp);
    return 0;
}

int ConfigManager::AddUser(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    CLOG_DEBUG("Add user");
    rsp->ResponseCode = m_dbHandler->mysql_Payload(*req);
    return 0;
}
int ConfigManager::DeleteUser(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    CLOG_DEBUG("Delete user");
    rsp->ResponseCode = m_dbHandler->mysql_Payload(*req);
    return 0;
}
int ConfigManager::VerifyPassword(GetConfigReq *req, AllResponses *rsp)
{
    CLOG_DEBUG("Verify Password ");
    m_dbHandler->mysql_Payload(*req,rsp);
    return 0;
}
#endif


void ConfigManager::InitLog()
{
    unsigned int logChannel = 0;
    unsigned int logLevel   = 7;

    if(logChannel == Logger::EACC_CHANNEL_SYSLOG)
    {
#if 0
        int options = (LOG_PID);
        int facility = LOG_LOCAL7;
#endif
        m_logger.SetLogChannel(&m_syslogChannel);
    }
    m_logger.SetLevel((Logger::Level)(int)logLevel);
}

Logger& ConfigManager::GetLogger()
{
    return m_logger;
}

void ConfigManager::SetLogChannel(const unsigned int channel)
{
    if(channel == Logger::EACC_CHANNEL_SYSLOG)
    {
        this->GetLogger().SetLogChannel(&m_syslogChannel);
    }
    else if (channel == Logger::EACC_CHANNEL_FILE)
    {
        /*This is done because currently we are using syslog and to avoid
        /unneccessary file being generated in the /var/log/dre */

        //this->GetLogger().SetLogChannel(&m_fileLogChannel);
    }
    else 
    {
        this->GetLogger().SetLogChannel(ConsoleLogChannel::Instance());
    }
}

void ConfigManager::SetLogLevel(const unsigned int level)
{
    this->GetLogger().SetLevel((Logger::Level)(int)level);
}

void ConfigManager::SetMysqlMonitorObject(MonitorMysql *pMonitorMysql)    
{    
         m_monitorMysql = pMonitorMysql;                                        
}                                           

int ConfigManager::AvailabilityActiveUpdateBroadcastCbk()
{

    CLOG_DEBUG("Received AvailabilityAcviteUpdateBroadcast");
    m_cmapiInterface->m_dbInterface->m_dbHandle.mysql_set_connection_hostname(m_cmapiInterface->m_dbHostname);
    m_cmapiIwfInterface->m_IwfdbInterface->m_dbHandle.mysql_set_connection_hostname(m_cmapiIwfInterface->m_dbHostname);
    m_cmapiInterface->m_dbInterface->m_dbHandle.mysql_reconnect_connection();
    m_cmapiIwfInterface->m_IwfdbInterface->m_dbHandle.mysql_reconnect_connection();
    if( m_cmapiInterface->m_dbInterface->m_dbHandle.isConnectedToLocalHost())
    {
        m_cmapiInterface->m_dbInterface->m_dbHandle.setLocalHostConnectionFlag(false);

        m_monitorMysql->SetUpdateConnectionFlag(true);
    }
    if( m_cmapiIwfInterface->m_IwfdbInterface->m_dbHandle.isConnectedToLocalHost())
    {
        m_cmapiIwfInterface->m_IwfdbInterface->m_dbHandle.setLocalHostConnectionFlag(false);

    }



    CLOG_DEBUG("AvailabilityActiveUpdateBroadcastCbk <<<");
    return 0;
}
