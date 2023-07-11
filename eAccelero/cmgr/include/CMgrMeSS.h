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



#ifndef __MeSSTest_h__
#define __MeSSTest_h__
#include "TopSrv.h"
#include "CommonStructure.h"
#if 0
#include <json.h>
#endif

#define DRE_PEER_CMD_ID 1
#include "MysqlInterface.h"
#include "CMgrDbInterface.h"
#include "config.h"
#include "Common.h"
#include "ConfigReader.h"

#include "MeSSComponent.h"
#include "CMAPICMgr.h"
#include "ComponentDefines.h"


#if 0

#define SERVER_COMP_ID  100
#define CLIENT_COMP_ID  200

#define I_TEST_ID       10
#define M_GET_CONFIG    1
#define M_SET_CONFIG    2
#define M_MULTICAST_REQ 3
#define M_GET_CONFIG_PEER    4	j
#define M_SET_CONFIG_PEER    5

#define CONFIG_MNGR_COMP_ID 101
#define CLI_CONFIG_INTERFACE_ID 11
#define TEST_CONFIG 8
#define CLI_COMP_ID 102
#endif


#if 0
struct GetConfigReq
{
    int id;
    char str[100];
};
#endif

struct testConfigReq
{
    int id;
    char str[100];
};

#if 0
struct GetConfigResp
{
    int id;
    int val;
    char result[100];
};
#endif
struct testConfigResp
{
    int id;
    int val;
    char result[100];
};



struct SetConfigResp
{
    int id;
    char result[100];
};
#if 0
typedef struct _GetConfigRsp {
	int cmd_id;
	int num_rec;
	char result[4096];
	//DrePeerPayload RspPayload;
	//DrePeerPayload RspPayload[10];
}GetConfigRsp;

struct SetConfigReq
{
    int id;
    int val;
    char descr[100];
};
#endif

//extern void* cMgrThread(int argc, char *argv[]);
extern void* CMgrMeSSThread(void *args);

class CMgrMeSS: public MeSSComponent, public Interface
{
	public:
		mysql_cli_interface *mysqlHandler;
		string db_protocol;
		string db_host;
		string db_port;
		string db_user;
		string db_pass;
		std::map<std::string, std::string> m_objConfigReaderMap;

#if 0
		/*LOGGING*/
		void InitLog();
		Logger& GetLogger();
		Logger m_logger;
		SyslogChannel m_syslogChannel;
		FileLogChannel m_fileLogChannel; /*TBD::Use This for File Logging*/
#endif

		CMgrMeSS();
		void Initialize();
		void Terminate();
		void RegisterMethods();
		int SetASFGroup(SetConfigReq *req, AllResponses *rsp);
		int DeleteASFGroup(SetConfigReq *req, AllResponses *rsp);
		int TerminateASFGroup(SetConfigReq *req, AllResponses *rsp);
		int ConfigASFGroup(SetConfigReq *req, AllResponses *rsp);
		int ResponseTimeoutASFGroup(SetConfigReq *req, AllResponses *rsp);
		int AddUser(SetConfigReq *req, AllResponses *rsp);
		int DeleteUser(SetConfigReq *req, AllResponses *rsp);
		int SetDiscoveryInterval(SetConfigReq *req, AllResponses *rsp);
		int SetPeerControl(SetConfigReq *req, AllResponses *rsp);
		int SetLocalHost(SetConfigReq *req, AllResponses *rsp);
		int SetDictionaryMap(SetConfigReq *req, AllResponses *rsp);
		int SetDefaultRoute(SetConfigReq *req, AllResponses *rsp);
		int SetConfigRealmTable(SetConfigReq *req, AllResponses *rsp);
		int DeletePeerTable(SetConfigReq *req, AllResponses *rsp);
		int DeleteLocalhost(SetConfigReq *req, AllResponses *rsp);
		int DeleteDictionaryMap(SetConfigReq *req, AllResponses *rsp);
		int DeleteRealmTable(SetConfigReq *req, AllResponses *rsp);
		int VerifyPassword(GetConfigReq *req, AllResponses *rsp);
		int SetReplicationFlag(SetConfigReq *req, AllResponses *rsp);
		int SetReplLogLevel(SetConfigReq *req, AllResponses *rsp);
		int ShowDiscoverPeer(GetConfigReq *req, AllResponses *rsp);
		int ShowDiameterbase(GetConfigReq *req, AllResponses *rsp);
		int ShowPeerStatus(GetConfigReq *req, AllResponses *rsp);
		int ShowRealmConfig(GetConfigReq *req, AllResponses *rsp);
		int ShowRealmSummary(GetConfigReq *req, AllResponses *rsp);
		int ShowLocalhost(GetConfigReq *req, AllResponses *rsp);
		int ShowConfig(GetConfigReq *req, AllResponses *rsp);
		int ShowConfigPeerTable(GetConfigReq *req, AllResponses *rsp);
		int ShowUser(GetConfigReq *req, AllResponses *rsp);
		int ShowDictionary(GetConfigReq *req, AllResponses *rsp);
		int SetConfigPeerTable(SetConfigReq *req, AllResponses *rsp);
		
	protected:
		unsigned m_counter;
		// Erlbf Component Configurations
		CMAPICMgr  *m_DreConfigObj;
};
#endif // __MeSSTest_h__
