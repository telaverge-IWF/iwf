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


#include "MeSSComponent.h"
#include "CMAPICMgr.h"
#include "CMgrMeSS.h"
#include "TopSrv.h"
#include "CommonStructure.h"
#if 0
#include <json.h>
#endif

#define DRE_PEER_CMD_ID 1
#include "config.h"
#include "Common.h"
#include "ConfigReader.h"

#include "ComponentDefines.h"

using namespace eAccelero;

//extern void* cMgrThread(int argc, char *argv[]);
extern void* CMgrMeSSThread(void *args);


CMgrMeSS::CMgrMeSS()
    : MeSSComponent("CMgrMeSS", COMP_CONFIG_MANAGER),
    //: MeSSComponent("CMgrMeSS", CMGR_COMP_ID),
    Interface(CLI_CMGR_INTERFACE_ID),
    m_counter(42)
#if 0
      m_logger("CMGR"),
      m_syslogChannel("CMGR", (LOG_PID)),
      //m_fileLogChannel("CMGR.log", "/opt/diametriq/dre")
#endif

{
    CLOG_NOTICE("CmgrMess Constructor");

#if 0
    /*Initialize Logging*/
    ScopedLogger scopedLogger(this->GetLogger());

    this->InitLog();
#endif


    char *dreMysqlServerConfDir = (char *) ::getenv("DRE_MYSQL_SERVER_CONFDIR");

    string confFile;

    if (dreMysqlServerConfDir != NULL)
    {
        confFile = dreMysqlServerConfDir;
    }
    else
    {
        std::cout << "\nDRE_MYSQL_SERVER_CONFDIR environment variable not defined \n" << std::endl;
        std::cout << "Trying to read configuration file from current directory...\n" << std::endl;
        confFile = ".";
    }

    confFile += "/";
    confFile += "mysql.cfg";

    bool isConfigFileOpenSuccessful = false;
    ConfigReader configReader(confFile.c_str(), isConfigFileOpenSuccessful);
    map<string, string>::const_iterator map_iterator;

    if (isConfigFileOpenSuccessful) 
    {
        m_objConfigReaderMap = configReader.getConfigMap();

        std::cout << "\nMysql Server configuration: \n" << std::endl;

        for (map_iterator = m_objConfigReaderMap.begin(); map_iterator != m_objConfigReaderMap.end(); map_iterator++)
            std::cout << map_iterator->first <<" ==>"<< map_iterator->second << std::endl;
    } 
    else 
    {
        std::cout << "\nmysql.cfg open failed \n" << confFile <<std::endl;
        exit(1);
    }

    //          map<string, string>::const_iterator map_iterator;

    map_iterator = m_objConfigReaderMap.find("db_protocol");
    if (map_iterator != m_objConfigReaderMap.end()) 
    {
        db_protocol = map_iterator->second;
    }

    map_iterator = m_objConfigReaderMap.find("db_host");
    if (map_iterator != m_objConfigReaderMap.end()) 
    {
        db_host = map_iterator->second;
    }

    map_iterator = m_objConfigReaderMap.find("db_port");
    if (map_iterator != m_objConfigReaderMap.end()) 
    {
        db_port = map_iterator->second;
    }

    map_iterator = m_objConfigReaderMap.find("db_user");
    if (map_iterator != m_objConfigReaderMap.end()) 
    {
        db_user = map_iterator->second;
    }

    map_iterator = m_objConfigReaderMap.find("db_pass");
    if (map_iterator != m_objConfigReaderMap.end()) 
    {
        db_pass = map_iterator->second;
    }


    std::cout << "User : " << db_user << std::endl; 
    m_DreConfigObj = new CMAPICMgr(db_host,db_user,db_pass,DATABASE);

    MeSSObj().RegisterInterface(this);

}

void CMgrMeSS::Initialize()
{
    MeSSComponent::Initialize();

}
void CMgrMeSS::Terminate()
{
    MeSSComponent::Terminate();
}

void CMgrMeSS::RegisterMethods()
{
    std::cout << "Registering methods..." << std::endl;
    this->RegisterMethod(M_GET_PEER_TABLE, 
            MethodSlot<CMgrMeSS, GetConfigReq, AllResponses>(this, &CMgrMeSS::ShowConfigPeerTable));
    this->RegisterMethod(M_PEER_SET_REQ, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::SetConfigPeerTable));
    this->RegisterMethod(M_SHOW_PEER_STATUS, 
            MethodSlot<CMgrMeSS, GetConfigReq, AllResponses>(this, &CMgrMeSS::ShowPeerStatus));
    this->RegisterMethod(M_SHOW_REALM_CONFIG, 
            MethodSlot<CMgrMeSS, GetConfigReq, AllResponses>(this, &CMgrMeSS::ShowRealmConfig));
    this->RegisterMethod(M_SHOW_REALM_SUMMARY, 
            MethodSlot<CMgrMeSS, GetConfigReq, AllResponses>(this, &CMgrMeSS::ShowRealmSummary));
    this->RegisterMethod(M_SHOW_DISCOVER_PEER, 
            MethodSlot<CMgrMeSS, GetConfigReq, AllResponses>(this, &CMgrMeSS::ShowDiscoverPeer));
    this->RegisterMethod(M_SHOW_USER, 
            MethodSlot<CMgrMeSS, GetConfigReq, AllResponses>(this, &CMgrMeSS::ShowUser));
    this->RegisterMethod(M_SHOW_DICTIONARY,
            MethodSlot<CMgrMeSS, GetConfigReq, AllResponses>(this, &CMgrMeSS::ShowDictionary));
    this->RegisterMethod(M_SHOW_DIAMETERBASE, 
            MethodSlot<CMgrMeSS, GetConfigReq, AllResponses>(this, &CMgrMeSS::ShowDiameterbase));
    this->RegisterMethod(M_SET_REALM_TABLE, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::SetConfigRealmTable));
    this->RegisterMethod(M_SET_DEFAULT_ROUTE, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::SetDefaultRoute));
    this->RegisterMethod(M_SET_LOCALHOST, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::SetLocalHost));
    this->RegisterMethod(M_PEER_DICT_ID,
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::SetDictionaryMap));
    this->RegisterMethod(M_PEER_DELETE_DICT_ID,
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::DeleteDictionaryMap));
    this->RegisterMethod(M_SET_PEER_CONTROL, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::SetPeerControl));
    this->RegisterMethod(M_SET_DISCOVERY_INTERVAL, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::SetDiscoveryInterval));
    this->RegisterMethod(M_ADD_USER, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::AddUser));
    this->RegisterMethod(M_DELETE_USER, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::DeleteUser));
    this->RegisterMethod(M_VERIFY_PASSWORD, 
            MethodSlot<CMgrMeSS, GetConfigReq, AllResponses>(this, &CMgrMeSS::VerifyPassword));
    this->RegisterMethod(M_SHOW_LOCALHOST, 
            MethodSlot<CMgrMeSS, GetConfigReq, AllResponses>(this, &CMgrMeSS::ShowLocalhost));
    this->RegisterMethod(M_SHOW_CONFIG, 
            MethodSlot<CMgrMeSS, GetConfigReq, AllResponses>(this, &CMgrMeSS::ShowConfig));
    this->RegisterMethod(M_DELETE_PEERTABLE, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::DeletePeerTable));
    this->RegisterMethod(M_DELETE_LOCALHOST, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::DeleteLocalhost));
    this->RegisterMethod(M_DELETE_REALMTABLE, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::DeleteRealmTable));
    /***********************ASF COMMANDS **********************************************/

    this->RegisterMethod(M_SET_ASGROUP_REQ, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::SetASFGroup));
    this->RegisterMethod(M_DELETE_ASGROUP_REQ, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::DeleteASFGroup));
    this->RegisterMethod(M_TERMINATE_ASGROUP_REQ, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::TerminateASFGroup));
    this->RegisterMethod(M_ASF_CONFIG_REQ, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::ConfigASFGroup));
    this->RegisterMethod(M_ASF_RESPONSE_TIMEOUT_REQ, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::ResponseTimeoutASFGroup));
    /***************************** REPLICATION  MANAGER SETTING ******************************/
    this->RegisterMethod(M_REPMGR_REPLFLAG, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::SetReplicationFlag));
    this->RegisterMethod(M_REPMGR_LOGLEVEL, 
            MethodSlot<CMgrMeSS, SetConfigReq, AllResponses>(this, &CMgrMeSS::SetReplLogLevel));
}

int CMgrMeSS::SetASFGroup(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Set ASF Group Req" << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}
int CMgrMeSS::DeleteASFGroup(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Delete ASF Group Req" << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}
int CMgrMeSS::TerminateASFGroup(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Terminate ASF Group Req" << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}
int CMgrMeSS::ConfigASFGroup(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Config ASF group Req" << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}
int CMgrMeSS::ResponseTimeoutASFGroup(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Response Timeout Req" << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}

int CMgrMeSS::AddUser(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Add user" << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}
int CMgrMeSS::DeleteUser(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Delete user" << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}
int CMgrMeSS::SetDiscoveryInterval(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Set Discovery Interval" << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}
int CMgrMeSS::SetPeerControl(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Set Peer control " << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}
int CMgrMeSS::SetLocalHost(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Set Local host" << req->cmd_id << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}
int CMgrMeSS::SetDictionaryMap(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Set PeerDictionaryMap " << req->cmd_id << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}

int CMgrMeSS::SetDefaultRoute(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}

int CMgrMeSS::SetConfigRealmTable(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}
int CMgrMeSS::DeletePeerTable(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Delete Peer Table" << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}
int CMgrMeSS::DeleteLocalhost(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Delete Local Host" << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}
int CMgrMeSS::DeleteDictionaryMap(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Delete PeerDictionaryMap" << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}
int CMgrMeSS::DeleteRealmTable(SetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Delete Realm table" << req->cmd_id << std::endl;
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
}
int CMgrMeSS::VerifyPassword(GetConfigReq *req, AllResponses *rsp)
{
    std::cout << "Verify Password " << std::endl;
    mysqlHandler->mysql_Payload(*req,rsp);
    return 0;
}
int CMgrMeSS::SetReplicationFlag(SetConfigReq *req, AllResponses *rsp)
{
    std::cout << "Setting Replication flag in DB" << std::endl;
    //          mysqlHandler->mysql_Payload(*req,rsp);
    return 0;
}
int CMgrMeSS::SetReplLogLevel(SetConfigReq *req, AllResponses *rsp)
{
    std::cout << "Setting Replication LogLevel in DB" << std::endl;
    //              mysqlHandler->mysql_Payload(*req,rsp);
    return 0;
}
int CMgrMeSS::ShowDiscoverPeer(GetConfigReq *req, AllResponses *rsp)
{
    std::cout << "Show Discover Peer " << std::endl;
    mysqlHandler->mysql_Payload(*req,rsp);
    return 0;
}
int CMgrMeSS::ShowDiameterbase(GetConfigReq *req, AllResponses *rsp)
{
    std::cout << "Show Diameterbase" << std::endl;
    mysqlHandler->mysql_Payload(*req,rsp);
    return 0;
}
int CMgrMeSS::ShowPeerStatus(GetConfigReq *req, AllResponses *rsp)
{
    rsp->cmd_id = req->cmd_id;
    std::cout << "Show peer Satus " << std::endl;
    mysqlHandler->mysql_Payload(*req,rsp);
    return 0;
}
int CMgrMeSS::ShowRealmConfig(GetConfigReq *req, AllResponses *rsp)
{
    std::cout << "Show Realm Config" << std::endl;
    mysqlHandler->mysql_Payload(*req,rsp);
    return 0;
}
int CMgrMeSS::ShowRealmSummary(GetConfigReq *req, AllResponses *rsp)
{
    std::cout << "Show Realm Summary" << std::endl;
    mysqlHandler->mysql_Payload(*req,rsp);
    return 0;
}

int CMgrMeSS::ShowLocalhost(GetConfigReq *req, AllResponses *rsp)
{
    std::cout << "Show Localhost Table" << std::endl;
    mysqlHandler->mysql_Payload(*req,rsp);
    return 0;
}
int CMgrMeSS::ShowConfig(GetConfigReq *req, AllResponses *rsp)
{
    std::cout << "Show Config" << std::endl;
    mysqlHandler->mysql_Payload(*req,rsp);
    return 0;
}
int CMgrMeSS::ShowConfigPeerTable(GetConfigReq *req, AllResponses *rsp)
{
    std::cout << "Show Peer Table" << std::endl;
    mysqlHandler->mysql_Payload(*req,rsp);
    return 0;
}
int CMgrMeSS::ShowUser(GetConfigReq *req, AllResponses *rsp)
{
    std::cout << "Show user" << std::endl;
    mysqlHandler->mysql_Payload(*req, rsp);
    return 0;
}
int CMgrMeSS::ShowDictionary(GetConfigReq *req, AllResponses *rsp)
{
    std::cout << "Show Dictionary" << std::endl;
    mysqlHandler->mysql_Payload(*req, rsp);
    return 0;
}
int CMgrMeSS::SetConfigPeerTable(SetConfigReq *req, AllResponses *rsp)
{
    rsp->ResponseCode = mysqlHandler->mysql_Payload(*req);
    return 0;
} 

void* CMgrMeSSThread(void *args)
{
    char *argv[]={(char*)"dummy",(char*)"-l",(char*)"6",(char*)"-i",(char*)"10"};
    int argc=5;

    CMgrMeSS *app = NULL;
    mysql_cli_interface *conn;
    std::cout << "staring server" << std::endl;
    try
    {
        app = new CMgrMeSS();
        std::cout << "User :" << app->db_user << std::endl; 
        std::cout << "Host :" << app->db_host << std::endl;
        conn = new mysql_cli_interface(app->db_host,app->db_user,app->db_pass,DATABASE);
        app->mysqlHandler = conn;

        app->Init(argc, argv);

        CLOG_NOTICE("Application initialized");

        app->Run();
    }
    catch(CmdParseException &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << CmdParser::Instance().Help() << std::endl;
    }
    catch(Exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    CLOG_NOTICE("Application exiting");

    if (app) delete app;
    //assigning NULL to currLogger object at the thread exit    
    Logger::currLogger = NULL;
    return 0;
}

#if 0

void CMgrMeSS::InitLog()
{
    std::ifstream doc("dre.json");
    if(!(m_jsonConfigFileReader.parse(doc,m_jsonRoot)))
    {
        std::cout  << "Failed to parse dre.json configuration\n"
            << m_jsonConfigFileReader.getFormattedErrorMessages();
    }

    const Json::Value dreLogging = m_jsonRoot["Logging"];
    unsigned int logChannel = dreLogging[0]["CMGR"]["logChannel"].asInt();
    unsigned int logLevel   = dreLogging[0]["CMGR"]["logLevel"].asInt();

    if(logChannel == Logger::EACC_CHANNEL_SYSLOG)
    {
        //int options = DLOG_PID;
        //int facility = DLOG_USER;
        //SyslogChannel *syslogChannel = new SyslogChannel("CMGR",options,facility);
        m_logger.SetLogChannel(&m_syslogChannel);
    }
    m_logger.SetLevel((Logger::Level)(int)logLevel);
}

Logger& CMgrMeSS::GetLogger()
{
    return m_logger;
}

void CMgrMeSS::SetLogChannel(const unsigned int channel)
{
    if(channel == Logger::EACC_CHANNEL_SYSLOG)
    {
        this->GetLogger().SetLogChannel(&m_syslogChannel);
    }
    else if (channel == Logger::EACC_CHANNEL_FILE)
    {
        //this->GetLogger().SetLogChannel(&m_fileLogChannel);
    }
    else
    {
        this->GetLogger().SetLogChannel(ConsoleLogChannel::Instance());
    }
}

void CMgrMeSS::SetLogLevel(const unsigned int level)
{
    this->GetLogger().SetLevel((Logger::Level)(int)level);
}

#endif
