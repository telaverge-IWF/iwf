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


#include "ComponentDefines.h"
#include <CMAPICMgr.h>
#include <CMAPICommon.h>
#include <CMgrDbInterface.h>
#include <CMgrLock.h>

#include "ErrorResp.h"
using namespace std;
using namespace eAccelero;

extern std::map<int,std::string> errorMap;
CMAPICMgr::~CMAPICMgr()
{
    if(m_dbInterface)
    {
        delete m_dbInterface;
    }

    if(m_diaMgtCallerObj)
    {
        delete m_diaMgtCallerObj;
    }

    if(m_standbydiaMgtCallerObj)
    {
        delete m_standbydiaMgtCallerObj;
    }

    if(m_erlbfCallerObj)
    {
        delete m_erlbfCallerObj;
    }

    if(m_standbyerlbfCallerObj)
    {
        delete m_standbyerlbfCallerObj;
    }

    if(m_loggingCallerObj)
    {
        delete m_loggingCallerObj;
    }

    if(m_standbyloggingCallerObj)
    {
        delete m_standbyloggingCallerObj;
    }

    if(m_configResultsHandler[COMP_CLI_PROC])
    {
        delete m_configResultsHandler[COMP_CLI_PROC];
    }

    if(m_compResultsHandler[COMP_CLI_PROC])
    {
        delete m_compResultsHandler[COMP_CLI_PROC];
    }

    if(m_configResultsHandler[COMP_WEBAGENT_PROC])
    {
        delete m_configResultsHandler[COMP_WEBAGENT_PROC];
    }

    if(m_compResultsHandler[COMP_WEBAGENT_PROC])
    {
        delete m_compResultsHandler[COMP_WEBAGENT_PROC];
    }

    if(m_loggingAvlCallerObj)
    {
        delete m_loggingAvlCallerObj;
    }

    if(m_loggingStandbyAvlCallerObj)
    {
        delete m_loggingStandbyAvlCallerObj;
    }

    if(m_staticConfigResultsHandler[COMP_CLI_PROC])
    {
        delete m_staticConfigResultsHandler[COMP_CLI_PROC];
    }

    if(m_iwfdiaMgtCallerObj)
    {
        delete m_iwfdiaMgtCallerObj;
    }

    if(m_iwfloggingCallerObj)
    {
        delete m_iwfloggingCallerObj;
    }

    if(m_standbyiwfloggingCallerObj)
    {
        delete m_standbyiwfloggingCallerObj;
    }

    if(m_standbyiwfdiaMgtCallerObj)
    {
        delete m_standbyiwfdiaMgtCallerObj;
    }
}

CMAPICMgr::CMAPICMgr(string sHostName,string sUserName,string sPassword,string sDataBase, uint16_t instanceId,ConfigManagerAlarms *pConfigManagerAlarms,ConfigManager *pConfigManager):
    m_instanceId(instanceId)
{

    m_ConfigManager = pConfigManager;
    m_dbHostname = sHostName;

    CMgrDbInterface *CMgrDbObj = new CMgrDbInterface(sHostName, sUserName, sPassword, sDataBase, pConfigManager,pConfigManagerAlarms);
    m_dbInterface = CMgrDbObj;
    m_LockManager = new CnfLockMgr(m_dbInterface);

    /* for n active, n standby scenario this will not work */

    MeSSEndpoint iwfDest = { COMP_IWF_APP, MESS_MIN_ACTIVE_INSTANCE};
    m_iwfdiaMgtCallerObj = new Stub::DiaMgtMethods(iwfDest, 0);
    m_iwfloggingCallerObj = new Stub::LoggingConf(iwfDest, 0);
    
    MeSSEndpoint standbyiwfDest = { COMP_IWF_APP, MESS_MIN_STANDBY_INSTANCE};
    m_standbyiwfloggingCallerObj = new Stub::LoggingConf(standbyiwfDest, 0);
    Stub::DiaMgtMethodsRespCbk::RegisterDiaMgtMethodsRespHandler();

    MeSSEndpoint standbydreDest = { COMP_DRE_APP, MESS_MIN_STANDBY_INSTANCE};
    MeSSEndpoint dreDest = { COMP_DRE_APP, MESS_MIN_ACTIVE_INSTANCE};

    m_diaMgtCallerObj = new Stub::DiaMgtMethods(dreDest, 0);
    m_standbydiaMgtCallerObj = new Stub::DiaMgtMethods(standbydreDest, 0);
    m_standbyiwfdiaMgtCallerObj = new Stub::DiaMgtMethods(standbyiwfDest, 0);

    m_erlbfCallerObj = new Stub::DreErlbf(dreDest, 0);
    m_standbyerlbfCallerObj = new Stub::DreErlbf(standbydreDest, 0);
    Stub::DreErlbfRespCbk::RegisterDreErlbfRespHandler();

    m_loggingCallerObj = new Stub::LoggingConf(dreDest, 0);
    m_standbyloggingCallerObj = new Stub::LoggingConf(standbydreDest, 0);
    Stub::LoggingConfRespCbk::RegisterLoggingConfRespHandler();

    m_asfCallerObj = new Stub::DreASF(dreDest, 0);
    m_standbyasfCallerObj = new Stub::DreASF(standbydreDest, 0);
    Stub::DreASFRespCbk::RegisterDreASFRespHandler();
    MeSSEndpoint cliDest = { COMP_CLI_PROC, m_instanceId };
    m_configResultsHandler[COMP_CLI_PROC] = new Stub::DREConfigResults(cliDest, 0);
    Stub::DREConfigResultsRespCbk::RegisterDREConfigResultsRespHandler();

    m_staticRoutingCallerObj = new Stub::DiaMgtForStaticRoutingMethods(iwfDest, 0);
    m_standbystaticRoutingCallerObj = new Stub::DiaMgtForStaticRoutingMethods(standbydreDest, 0);
    Stub::DiaMgtForStaticRoutingMethodsRespCbk::RegisterDiaMgtForStaticRoutingMethodsRespHandler();
    m_staticConfigResultsHandler[COMP_CLI_PROC] = new Stub::DREStaticRoutingConfigResults(cliDest, 0);
    Stub::DREStaticRoutingConfigResultsRespCbk::RegisterDREStaticRoutingConfigResultsRespHandler();

    m_compResultsHandler[COMP_CLI_PROC] = new Stub::CompConfigResults(cliDest, 0);
    Stub::CompConfigResultsRespCbk::RegisterCompConfigResultsRespHandler();

    MeSSEndpoint agentDest = { COMP_WEBAGENT_PROC, m_instanceId };
    m_configResultsHandler[COMP_WEBAGENT_PROC] = new Stub::DREConfigResults(agentDest, 0);
    m_compResultsHandler[COMP_WEBAGENT_PROC] = new Stub::CompConfigResults(agentDest, 0);

    /* for n active, n standby scenario this will not work */
    MeSSEndpoint standbyavlDest = { COMP_AVAILABILITY_MANAGER, MESS_MIN_STANDBY_INSTANCE};
    MeSSEndpoint avlDest = { COMP_AVAILABILITY_MANAGER, MESS_MIN_ACTIVE_INSTANCE};
    m_loggingAvlCallerObj = new Stub::LoggingConf(avlDest, 0);
    m_loggingStandbyAvlCallerObj = new Stub::LoggingConf(standbyavlDest, 0);


}


int CMAPICMgr::UpdateInstanceId(uint16_t instanceId)
{

    DLOG_DEBUG("Update Instance Id");

    m_instanceId = instanceId;
    MeSSEndpoint cliDest = { COMP_CLI_PROC, m_instanceId };

    delete m_configResultsHandler[COMP_CLI_PROC];
    m_configResultsHandler[COMP_CLI_PROC] = new Stub::DREConfigResults(cliDest, 0);

    delete m_compResultsHandler[COMP_CLI_PROC];
    m_compResultsHandler[COMP_CLI_PROC] = new Stub::CompConfigResults(cliDest, 0);

    MeSSEndpoint agentDest = { COMP_WEBAGENT_PROC, m_instanceId };
    delete m_configResultsHandler[COMP_WEBAGENT_PROC];
    m_configResultsHandler[COMP_WEBAGENT_PROC] = new Stub::DREConfigResults(agentDest, 0);

    delete m_compResultsHandler[COMP_WEBAGENT_PROC];
    m_compResultsHandler[COMP_WEBAGENT_PROC] = new Stub::CompConfigResults(agentDest, 0);

    delete m_staticConfigResultsHandler[COMP_CLI_PROC];
    m_staticConfigResultsHandler[COMP_CLI_PROC] = new Stub::DREStaticRoutingConfigResults(cliDest, 0);

    return 0;
}

int CMAPICMgr::HandleGetLocalHostConfigReqs(LocalHostConfig *req,DRECfgResp *resp)
{
    int iOperID;
    DbStatus_e iReturn = DRE_DB_FAIL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(req->has_operreqid())
        iOperID =  req->operreqid();
    else
    {
        resp->set_respcode(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {

        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    switch(iOperID)
    {
        case GET_HOST:
            iReturn = m_dbInterface->mysql_LocalHost_Get_Config_Reqs(req,resp);
            break;
        default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_respcode(CMAPI_ERROR);
            break;
    }
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    if(iReturn == DRE_DB_SUCCESS)
        resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturn == GET_HOST_ERR_NO_DATA_PRESENT)
        resp->set_respcode(CMAPI_SUCCESS);
    else
        resp->set_respcode(CMAPI_ERROR);

    DLOG_DEBUG("Localhost resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Localhost req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

int CMAPICMgr::HandleGetPeerStatesReqs(PeersConfig *req,DRECfgResp *resp)
{
    int iOperID;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" req %p %s ",req,__FUNCTION__);


    if(req->has_operreqid())
        iOperID =  req->operreqid();
    else
    {
        resp->set_respcode(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set\n");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    switch(iOperID)
    {
        case GET_PEER:
        case GET_PEERSTATE:
            PeersConfig *lreq = new PeersConfig();
            lreq->CopyFrom(*req);

            CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
                    m_dbInterface->m_dbHandle.mysql_get_current_connection(),lreq);
#if DRE
            m_diaMgtCallerObj->HandleDreSetPeerConfigReqs(*req, (void*)cookie);
#else
            m_iwfdiaMgtCallerObj->HandleDreSetPeerConfigReqs(*req, (void*)cookie);
#endif
            break;
    }

    resp->set_respcode(CMAPI_SUCCESS);
    return 0;
}

int CMAPICMgr::HandleGetPeerConfigReqs(PeersConfig *req,DRECfgResp *resp)
{
    int iOperID;
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);


    if(req->has_operreqid())
        iOperID =  req->operreqid();
    else
    {
        resp->set_respcode(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set\n");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }
    switch(iOperID)
    {
        case GET_PEER:
            iReturn =   m_dbInterface->mysql_Peer_Get_Config_Reqs(req,resp);
            break;

        case GET_REALMOFPEER:
            iReturn = m_dbInterface->mysql_PeerOfRealm_Get_Config_Reqs(req,resp);
            break;
#if 0
        case GET_DEFROUTE:
            iReturn =   m_dbInterface->mysql_DefaultRoute_Get_Config_Reqs_Through_Peer(req,resp);
            break;
#endif
        default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_respcode(CMAPI_ERROR);
            break;
    }
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    if(iReturn == DRE_DB_SUCCESS)
        resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturn == GET_PEER_ERR_NO_DATA_PRESENT)
        resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturn == GET_REALMOFPEER_ERR_NO_DATA_PRESENT)
        resp->set_respcode(CMAPI_SUCCESS);
    else
        resp->set_respcode(CMAPI_ERROR);

    DLOG_DEBUG("DRECfgResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("PeersConfig req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

int CMAPICMgr::HandleGetRealmConfigReqs(RealmsConfig *req,DRECfgResp *resp)
{
    DbStatus_e iReturn = DRE_DB_FAIL;
    int iOperID;
    DLOG_NONE(" > %s ",__FUNCTION__);


    if(req->has_operreqid())
        iOperID =  req->operreqid();
    else
    {
        resp->set_respcode(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set\n");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }
    switch(iOperID)
    {
        case GET_REALM:
            iReturn = m_dbInterface->mysql_Realm_Get_Config_Reqs(req,resp);
            break;

        case GET_DEST:
            iReturn = m_dbInterface->mysql_RealmRouting_Get_Config_Reqs(req,resp);
            break;
        case GET_DEFROUTE:
            iReturn = m_dbInterface->mysql_DefaultRoute_Get_Config_Reqs_Through_Realm(req,resp);
            break;

        default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_respcode(CMAPI_ERROR);
            break;

    }
    m_dbInterface->m_dbHandle.mysql_release_current_connection();


    if(iReturn == DRE_DB_SUCCESS)
        resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturn == GET_REALM_ERR_NO_DATA_PRESENT)
        resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturn == GET_DEST_ERR_NO_DATA_PRESENT)
        resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturn == GET_DEFROUTE_ERR_NO_DATA_PRESENT)
        resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturn == GET_REALM_ERR_NO_REALM_PRESENT)
        resp->set_respcode(CMAPI_SUCCESS);
    else
        resp->set_respcode(CMAPI_ERROR);

    DLOG_DEBUG("DRECfgResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("RealmsConfig req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

int CMAPICMgr::HandleSetLocalHostConfigReqs(LocalHostConfig *req,DRECfgResp *resp)
{

    DbStatus_e iReturn = DRE_DB_FAIL;
    DRECfgResp localResp;
    LocalHostConfig lHostConfig;
    int iOperID;

    DLOG_NONE(" > %s",__FUNCTION__);

    if(req->has_operreqid())
        iOperID =  req->operreqid();
    else
    {
        resp->set_respcode(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set\n");
        DLOG_NONE(" < %s",__FUNCTION__);
        return 0;
    }

    // Need More Clarity Regarding LocalHost Table

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            if(iReturn == GET_LOCK_ERR_DB_ERROR)
            {
			    DLOG_ERROR("Database Error!");
			    m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_DB_ERROR);
            }
            else if(iReturn == GET_LOCK_ERR_RESOURSE_BUSY)
            {
			    DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
			    m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
            }
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_respcode(CMAPI_ERROR);
	        DLOG_NONE(" < %s ",__FUNCTION__);
			return 0;
		}
	}

    switch(iOperID)
    {
        case SET_HOST:
            iReturn = m_dbInterface->mysql_LocalHost_Add_Config_Reqs(req,resp);
            break;

        case SET_AUTHTIMERS:
        case SET_HOSTIP:
        case SET_ACCTTIMERS:
        case MOD_HOST:
            m_dbInterface->mysql_LocalHost_Get_Config_Reqs(&lHostConfig,&localResp);
            m_dbInterface->mysql_LocalHost_Delete_Config_Reqs(&lHostConfig,resp);
            iReturn = m_dbInterface->copy_LocalHostConfig(req,&localResp);
            if(iReturn == DRE_DB_SUCCESS)
                iReturn = m_dbInterface->mysql_LocalHost_Add_Config_Reqs(req,resp);
            break;

        default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_respcode(CMAPI_ERROR);
            break;
    }

    if(iReturn != DRE_DB_SUCCESS)
    {
        m_LockManager->CMgr_ReleaseLock(iOperID);
        resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
    }
    else
    {
        LocalHostConfig *lReq = new LocalHostConfig();
        lReq->CopyFrom(*req);
        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
                m_dbInterface->m_dbHandle.mysql_get_current_connection(),lReq);
#if DRE
        m_diaMgtCallerObj->HandleLocalHostConfigReqs(*req, (void*)cookie);
#else
        m_iwfdiaMgtCallerObj->HandleLocalHostConfigReqs(*req, (void*)cookie);
#endif

        resp->set_respcode(CMAPI_SUCCESS);
    }

    DLOG_DEBUG("DRECfgResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("LocalHostConfig req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

int CMAPICMgr::HandleSetPeerConfigReqs(PeersConfig *req,DRECfgResp *resp)
{
    int iCount = req->peers_size();
    int iOperID;
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_DEBUG("PeersConfig req = %s",req->DebugString().c_str());

    DLOG_NONE(" > %s",__FUNCTION__);
    if(req->has_operreqid())
        iOperID =  req->operreqid();
    else
    {
        resp->set_respcode(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set\n");
        DLOG_NONE(" < %s",__FUNCTION__);
        return 0;
    }


    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            if(iReturn == GET_LOCK_ERR_DB_ERROR)
            {
			    DLOG_ERROR("Database Error!");
			    m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_DB_ERROR);
            }
            else if(iReturn == GET_LOCK_ERR_RESOURSE_BUSY)
            {
			    DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
			    m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
            }
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_respcode(CMAPI_ERROR);
	        DLOG_NONE(" < %s ",__FUNCTION__);
			return 0;
		}
	}

    for(int i=0; i<iCount; i++)
    {

        ::PeerConfig* localPeerConfig = req->mutable_peers(i);
        switch(iOperID)
        {
            case SET_PEER:
                iReturn = m_dbInterface->mysql_PeerAndTimer_Add_Config_Reqs(localPeerConfig,resp);
                break;
            case SET_PEERSTATUS:
            case MOD_PEER:
                iReturn = m_dbInterface->mysql_PeerAndTimer_Mod_Config_Reqs(localPeerConfig,resp);
                break;
            case ADD_DICTID:
                iReturn = m_dbInterface->mysql_PeerDictionaryMap_Add_Config_Reqs_Through_Peer(localPeerConfig,resp);
                break;
            case ADD_SECIP:
                iReturn = m_dbInterface->mysql_PeerSecondaryIp_Add_Config_Reqs_Through_Peer(localPeerConfig,resp);
                break;
#if 0
            case SET_DEFROUTE:
                iReturn = m_dbInterface->mysql_DefaultRoute_Add_Config_Reqs_Through_Peer(localPeerConfig,resp);
                break;
            case MOD_DEFROUTE:
                iReturn = m_dbInterface->mysql_DefaultRoute_Mod_Config_Reqs_Through_Peer(localPeerConfig,resp);
                break;
#endif
            default:
                DLOG_ERROR("Unknown Operation ID");
                break;

        }

        if(iReturn != DRE_DB_SUCCESS)
        {
#if 0
            ErrorDetails* err = resp->add_errordetails();
            err->set_errorcode(iReturn);
            err->set_errormsgkey(errorMap[iReturn]);
            CLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
            if(localPeerConfig->has_peerhostname())
                err->add_variables(localPeerConfig->peerhostname());
            if(localPeerConfig->has_realm())
                err->add_variables(localPeerConfig->realm());
#endif

            break;
        }
    }

    if(iReturn != DRE_DB_SUCCESS)
    {
        m_LockManager->CMgr_ReleaseLock(iOperID);
        resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
    }
    else
    {
        PeersConfig *lReq = new PeersConfig();
        lReq->CopyFrom(*req);
        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
                m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
#if DRE
        m_diaMgtCallerObj->HandleDreSetPeerConfigReqs(*req, (void*)cookie);
#else
        m_iwfdiaMgtCallerObj->HandleDreSetPeerConfigReqs(*req, (void*)cookie);
#endif

        resp->set_respcode(CMAPI_SUCCESS);
    }

    DLOG_DEBUG("DRECfgResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("PeersConfig req = %s",req->DebugString().c_str());
    DLOG_NONE(" > %s ",__FUNCTION__);
    return 0;

}

int CMAPICMgr::HandleSetRealmConfigReqs(RealmsConfig *req,DRECfgResp *resp)
{

    DbStatus_e iReturn = DRE_DB_SUCCESS;
    int iOperID;
    DRECfgResp localResp;
    RealmConfig lRealmConfig;
    DLOG_NONE(" > %s ",__FUNCTION__);
    int iCount = req->realms_size();


    if(req->has_operreqid())
        iOperID =  req->operreqid();
    else
    {
        resp->set_respcode(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set\n");
        DLOG_NONE(" < %s",__FUNCTION__);
        return 0;
    }

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            if(iReturn == GET_LOCK_ERR_DB_ERROR)
            {
			    DLOG_ERROR("Database Error!");
			    m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_DB_ERROR);
            }
            else if(iReturn == GET_LOCK_ERR_RESOURSE_BUSY)
            {
			    DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
			    m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
            }
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_respcode(CMAPI_ERROR);
	        DLOG_NONE(" < %s ",__FUNCTION__);
			return 0;
		}
	}

    for(int i=0; i<iCount; i++)
    {
        ::RealmConfig* localRealmConfig = req->mutable_realms(i);

        int iDestinationCount = localRealmConfig->destinfo_size();

        for(int j=0; j<iDestinationCount; j++)
        {
            ::Destination* localDestinationObj = localRealmConfig->mutable_destinfo(j);

            switch(iOperID)
            {
#if 1

                case SET_DEST:
                    {
                        iReturn = m_dbInterface->mysql_RealmRouting_Add_Config_Reqs(localRealmConfig,j,resp);
                        break;
                    }

                case MOD_DEST:
                    {
                        iReturn = m_dbInterface->mysql_RealmRouting_Mod_Config_Reqs(localRealmConfig,j,resp);
                        break;
                    }
#endif

                case SET_DEFROUTE:
                    {
                        iReturn = m_dbInterface->mysql_DefaultRoute_Add_Config_Reqs_Through_Realm(localRealmConfig,j);
                        break;

                    }

                case MOD_DEFROUTE:
                    {
                        m_dbInterface->mysql_DefaultRoute_Get_Config_Reqs_Through_Realm(&lRealmConfig,&localResp);
                        m_dbInterface->mysql_DefaultRoute_Delete_Config_Reqs_Through_Realm(&lRealmConfig,resp);
                        iReturn = m_dbInterface->copy_DefaultRoute(localRealmConfig,&localResp);
                        if(iReturn == DRE_DB_SUCCESS)
                            iReturn = m_dbInterface->mysql_DefaultRoute_Add_Config_Reqs_Through_Realm(localRealmConfig,j);
                        break;

                    }

                default:
                    {
                        resp->set_respcode(CMAPI_ERROR);
                        DLOG_ERROR("Unknown Operation ID");
                        DLOG_NONE(" < %s Default",__FUNCTION__);
                        iReturn = DRE_DB_FAIL;
                    }

            }

            if(iReturn != DRE_DB_SUCCESS)
            {
                ErrorDetails* err = resp->add_errordetails();
                err->set_errorcode(iReturn);
                err->set_errormsgkey(errorMap[iReturn]);
                DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

                if(localDestinationObj->has_applicationid())
                {
                    char sApplicationID[10];
                    snprintf(sApplicationID,10,"%d",localDestinationObj->applicationid());
                    err->add_variables(sApplicationID);
                }

                if(localDestinationObj->has_peername())
                {
                    DLOG_DEBUG("setting peer %s",localDestinationObj->peername().c_str());
                    err->add_variables(localDestinationObj->peername());
                }

                if(localRealmConfig->has_realmname())
                    err->add_variables(localRealmConfig->realmname());
                break;
            }

        }

        if(iDestinationCount == 0)
        {
            switch(iOperID)
            {
                case SET_REALM:
                    {
                        iReturn = m_dbInterface->mysql_Realm_Add_Config_Reqs(localRealmConfig,resp);
                        break;
                    }
                case MOD_REALM:
                    {
                        iReturn = m_dbInterface->mysql_Realm_Mod_Config_Reqs(localRealmConfig,resp);
                        break;
                    }

                case SET_DEFROUTE:
                    {
                        iReturn = m_dbInterface->mysql_DefaultRoute_Add_Config_Reqs_Through_Realm(localRealmConfig,0);
                        break;

                    }

                case MOD_DEFROUTE:
                    {
                        m_dbInterface->mysql_DefaultRoute_Get_Config_Reqs_Through_Realm(&lRealmConfig,&localResp);
                        m_dbInterface->mysql_DefaultRoute_Delete_Config_Reqs_Through_Realm(&lRealmConfig,resp);
                        iReturn = m_dbInterface->copy_DefaultRoute(localRealmConfig,&localResp);
                        if(iReturn == DRE_DB_SUCCESS)
                            iReturn = m_dbInterface->mysql_DefaultRoute_Add_Config_Reqs_Through_Realm(localRealmConfig,0);
                        break;

                    }

                default:
                    {
                        resp->set_respcode(CMAPI_ERROR);
                        DLOG_ERROR("Unknown Operation ID");
                        DLOG_NONE(" < %s Default",__FUNCTION__);
                        return 0;
                    }
            }

            if(iReturn != DRE_DB_SUCCESS)
            {
                ErrorDetails* err = resp->add_errordetails();
                err->set_errorcode(iReturn);
                err->set_errormsgkey(errorMap[iReturn]);
                DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
#if 0
                if(localDestinationObj->has_applicationid())
                    err->add_variables(localDestinationObj->applicationid());
#endif
                if(localRealmConfig->has_realmname())
                    err->add_variables(localRealmConfig->realmname());

                if(localRealmConfig->has_defaultroute())
                    err->add_variables(localRealmConfig->defaultroute());

                break;
            }
        }




    }


    if(iReturn != DRE_DB_SUCCESS)
    {
        m_LockManager->CMgr_ReleaseLock(iOperID);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
        resp->set_respcode(CMAPI_ERROR);
    }
    else
    {
        RealmsConfig *lReq = new RealmsConfig();
        lReq->CopyFrom(*req);
        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
                m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
#if DRE
        m_diaMgtCallerObj->HandleDreSetRealmConfigReqs(*req, (void*)cookie);
#else
        m_iwfdiaMgtCallerObj->HandleDreSetRealmConfigReqs(*req, (void*)cookie);
#endif

        resp->set_respcode(CMAPI_SUCCESS);
    }


    DLOG_DEBUG("DRECfgResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("RealmsConfig req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

#if 0
int CMAPICMgr::HandleSetRealmConfigReqs(RealmsConfig *req,DRECfgResp *resp)
{

    DbStatus_e iReturn = DRE_DB_SUCCESS;
    int iOperID;
    DRECfgResp localResp;
    RealmConfig lRealmConfig;
    DLOG_NONE(" > %s ",__FUNCTION__);
    int iCount = req->realms_size();


    if(req->has_operreqid())
        iOperID =  req->operreqid();
    else
    {
        resp->set_respcode(CMAPI_ERROR);
        DLOG_ERROR("%s:%d Operation ID is not Set\n",__FUNCTION__,__LINE__);
        return 0;
    }

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return DRE_DB_FAIL;
    }
    for(int i=0; i<iCount; i++)
    {
        ::RealmConfig* localRealmConfig = req->mutable_realms(i);

        int iDestinationCount = localRealmConfig->destinfo_size();

        for(int j=0; j<iDestinationCount; j++)
        {

            switch(iOperID)
            {
                case SET_REALM:
                    {
                        iReturn = m_dbInterface->mysql_Realm_Add_Config_Reqs(localRealmConfig,j,resp);
                        break;
                    }
                case MOD_REALM:
                    {
                        iReturn = m_dbInterface->mysql_Realm_Mod_Config_Reqs(localRealmConfig,j,resp);
                        break;
                    }

                case SET_DEFROUTE:
                    {
                        iReturn = m_dbInterface->mysql_DefaultRoute_Add_Config_Reqs_Through_Realm(localRealmConfig,j);
                        break;

                    }

                case MOD_DEFROUTE:
                    {
                        m_dbInterface->mysql_DefaultRoute_Get_Config_Reqs_Through_Realm(&lRealmConfig,&localResp);
                        m_dbInterface->mysql_DefaultRoute_Delete_Config_Reqs_Through_Realm(&lRealmConfig,resp);
                        iReturn = m_dbInterface->copy_DefaultRoute(localRealmConfig,&localResp);
                        if(iReturn == DRE_DB_SUCCESS)
                            iReturn = m_dbInterface->mysql_DefaultRoute_Add_Config_Reqs_Through_Realm(localRealmConfig,j);
                        break;

                    }

                default:
                    {
                        resp->set_respcode(CMAPI_ERROR);
                        DLOG_ERROR("Unknown Operation ID");
                        DLOG_NONE(" > %s ",__FUNCTION__);
                        return 0;
                    }
            }

        }

        if(iDestinationCount == 0)
        {
            switch(iOperID)
            {
                case SET_REALM:
                    {
                        break;
                    }
                case MOD_REALM:
                    {
                        iReturn = m_dbInterface->mysql_Realm_Mod_Config_Reqs(localRealmConfig,0,resp);
                        break;
                    }

                case SET_DEFROUTE:
                    {
                        iReturn = m_dbInterface->mysql_DefaultRoute_Add_Config_Reqs_Through_Realm(localRealmConfig,0);
                        break;

                    }

                case MOD_DEFROUTE:
                    {
                        m_dbInterface->mysql_DefaultRoute_Get_Config_Reqs_Through_Realm(&lRealmConfig,&localResp);
                        m_dbInterface->mysql_DefaultRoute_Delete_Config_Reqs_Through_Realm(&lRealmConfig,resp);
                        iReturn = m_dbInterface->copy_DefaultRoute(localRealmConfig,&localResp);
                        if(iReturn == DRE_DB_SUCCESS)
                            iReturn = m_dbInterface->mysql_DefaultRoute_Add_Config_Reqs_Through_Realm(localRealmConfig,0);
                        break;

                    }

                default:
                    {
                        resp->set_respcode(CMAPI_ERROR);
                        DLOG_ERROR("Unknown Operation ID");
                        DLOG_NONE(" > %s ",__FUNCTION__);
                        return 0;
                    }
            }
        }
    }


    if(iReturn == DRE_DB_FAIL)
        resp->set_respcode(CMAPI_ERROR);
    else
    {
        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, CMAPI_SUCCESS,
                m_dbInterface->m_dbHandle.mysql_get_current_connection());
        m_diaMgtCallerObj->HandleDreSetRealmConfigReqs(*req, (void*)cookie);

#if DRE
        m_standbydiaMgtCallerObj->HandleDreSetRealmConfigReqs(*req, (void*)cookie);
#else
        m_standbyiwfdiaMgtCallerObj->HandleDreSetRealmConfigReqs(*req, (void*)cookie);
#endif
        resp->set_respcode(CMAPI_SUCCESS);
    }

    DLOG_NONE(" > %s ",__FUNCTION__);
    return 0;

}
#endif

int CMAPICMgr::HandleDelPeerConfigReqs(PeersConfig *req,DRECfgResp *resp)
{
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iOperID;
    DLOG_NONE(" > %s ",__FUNCTION__);


    if(req->has_operreqid())
        iOperID =  req->operreqid();
    else
    {
        resp->set_respcode(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set\n");
        DLOG_NONE(" < %s",__FUNCTION__);
        return 0;
    }

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            if(iReturn == GET_LOCK_ERR_DB_ERROR)
            {
			    DLOG_ERROR("Database Error!");
			    m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_DB_ERROR);
            }
            else if(iReturn == GET_LOCK_ERR_RESOURSE_BUSY)
            {
			    DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
			    m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
            }
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_respcode(CMAPI_ERROR);
	        DLOG_NONE(" < %s ",__FUNCTION__);
			return 0;
		}
	}

    switch(iOperID)
    {
        case DEL_PEER:
            iReturn = m_dbInterface->mysql_Peer_Delete_Config_Reqs(req,resp);
            break;
        case DEL_DICTID:
            iReturn = m_dbInterface->mysql_PeerDictionaryMap_Delete_Config_Reqs_Through_Peer(req,resp);
            break;
        case DEL_SECIP:
            iReturn = m_dbInterface->mysql_PeerSecondaryIp_Delete_Config_Reqs_Through_Peer(req,resp);
            break;
        case DEL_ALTPEER:
            iReturn = m_dbInterface->mysql_AltPeer_Delete_Config_Reqs(req,resp);
            break;
        default:
            DLOG_ERROR("Unknown Operation ID");
            DLOG_NONE(" Default %s",__FUNCTION__);
            break;
    }


    if(iReturn != DRE_DB_SUCCESS)
    {
        m_LockManager->CMgr_ReleaseLock(iOperID);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
        resp->set_respcode(CMAPI_ERROR);
    }
    else
    {
        PeersConfig *lReq = new PeersConfig();
        lReq->CopyFrom(*req);

        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
                m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
#if DRE
        m_diaMgtCallerObj->HandleDreDelPeerConfigReqs(*req, (void*)cookie);
#else
        m_iwfdiaMgtCallerObj->HandleDreDelPeerConfigReqs(*req, (void*)cookie);
#endif

        resp->set_respcode(CMAPI_SUCCESS);
    }

    DLOG_DEBUG("DRECfgResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("PeersConfig req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

int CMAPICMgr::HandleDelRealmConfigReqs(RealmsConfig *req,DRECfgResp *resp)
{
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iOperID;

    DLOG_NONE(" > %s ",__FUNCTION__);


    if(req->has_operreqid())
        iOperID =  req->operreqid();
    else
    {
        resp->set_respcode(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set\n");
        DLOG_NONE(" < %s",__FUNCTION__);
        return 0;
    }


    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            if(iReturn == GET_LOCK_ERR_DB_ERROR)
            {
			    DLOG_ERROR("Database Error!");
			    m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_DB_ERROR);
            }
            else if(iReturn == GET_LOCK_ERR_RESOURSE_BUSY)
            {
			    DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
			    m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
            }
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_respcode(CMAPI_ERROR);
	        DLOG_NONE(" < %s ",__FUNCTION__);
			return 0;
		}
	}

    switch(iOperID)
    {
        case DEL_REALM:
            iReturn = m_dbInterface->mysql_Realm_Delete_Config_Reqs(req,resp);
            break;
        case DEL_DEST:
            iReturn = m_dbInterface->mysql_RealmRouting_Delete_Config_Reqs(req,resp);
            break;
        case DEL_DEFROUTE:
            iReturn = m_dbInterface->mysql_DefaultRoute_Delete_Config_Reqs(req,resp);
            break;
        default:
            DLOG_ERROR("Unknown Operation ID");
            DLOG_NONE("%s:%d Default\n",__FUNCTION__,__LINE__);
            break;
    }


    if(iReturn != DRE_DB_SUCCESS)
    {
        m_LockManager->CMgr_ReleaseLock(iOperID);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
        resp->set_respcode(CMAPI_ERROR);
    }
    else
    {
        RealmsConfig *lReq = new RealmsConfig();
        lReq->CopyFrom(*req);
        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
                m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
#if DRE
        m_diaMgtCallerObj->HandleDreDelRealmConfigReqs(*req, (void*)cookie);
#else
        m_iwfdiaMgtCallerObj->HandleDreDelRealmConfigReqs(*req, (void*)cookie);
#endif

        resp->set_respcode(CMAPI_SUCCESS);
    }

    DLOG_DEBUG("DRECfgResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("RealmsConfig req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

// ***********************************************************************
// DRE Product Configuration Response Handlers Implementation
// ***********************************************************************

int CMAPICMgr::HandleLocalHostConfigReqsRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    std::string StrVal;
    DRECfgResp ErrorResponse;
    DLOG_NONE(">HandleLocalHostConfigReqsRespCbk : ");

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_NONE("Response from Instance : %d", MeSS::Handle().m_src.instance);
        return 0;
    }

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    int iOperID = cookie->iReqID;
    void* conn = cookie->con;
    LocalHostConfig *req = (LocalHostConfig*)cookie->req;


    if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
    {
        if(resp == NULL)
        {
            resp = &ErrorResponse;
        }

        DLOG_WARNING("MESS Responded with state : MESS_STATUS_NOT_READY ");
        retVal = CMAPI_SRVERROR;
        resp->set_respcode(CMAPI_SRVERROR);
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey(errorMap[CONFIG_COMMON_MESS_NOT_READY]);
        m_LockManager->CMgr_ReleaseLock(iOperID,conn);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
    }
    else
    {

        if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
        {
            if (resp->respcode() == CMAPI_SUCCESS)
            {

                DLOG_NONE(">HandleLocalHostConfigReqsRespCbk : DRE operation - Successful. Committing the database ");
                //commit database
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
#if DRE
                m_standbydiaMgtCallerObj->HandleLocalHostConfigReqs(*req, (void*)NULL);
#else
                m_standbyiwfdiaMgtCallerObj->HandleLocalHostConfigReqs(*req, (void*)NULL);
#endif
            }
            else {
                //resp->SerializeToString(&StrVal);
                //m_CMAPIResponse->Set(StrVal);
                //rollback database, since the DRE configuration failed
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
            }
        } else {
            if (resp == NULL || MeSS::Handle().m_state == MESS_STATUS_TIMEOUT)
            {
                retVal = CMAPI_SRVERROR;
                ErrorResponse.set_respcode(retVal);
                //ErrorResponse.SerializeToString(&StrVal);
                resp = &ErrorResponse;
            } else {
                //resp->SerializeToString(&StrVal);
            }
            m_LockManager->CMgr_ReleaseLock(iOperID,conn);
            m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
            //m_CMAPIResponse->Set(StrVal);
        }
    }
    m_configResultsHandler[cookie->comp]->SendDREConfigResult(*resp);

    deleteCookie(cookie,SET_HOST);
    return retVal;
}


int CMAPICMgr::HandleDreSetPeerConfigReqsRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    std::string StrVal;
    DRECfgResp ErrorResponse;
    DLOG_NONE(">HandleDreSetPeerConfigReqsRespCbk : ");

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_NONE("Response from Instance : %d", MeSS::Handle().m_src.instance);
        return 0;
    }

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    void* conn = cookie->con;
    int iOperID = cookie->iReqID;
    PeersConfig *req = (PeersConfig*) cookie->req;

    if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
    {
        if(resp == NULL)
        {
            resp = &ErrorResponse;
        }
        DLOG_WARNING("MESS Responded with state : MESS_STATUS_NOT_READY ");

        retVal = CMAPI_SRVERROR;
        resp->set_respcode(CMAPI_SRVERROR);
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey(errorMap[CONFIG_COMMON_MESS_NOT_READY]);

        /* In case GET_PEER
         * We are sending request to dre. to get the PeerConnection
         * Status, So everytime Get Peer is called this Callback
         * be executed. Since in all Get Function (Even in GET_PEER)
         * we are not taking MySql NameLock so Release is not
         * Requiered */

        if(iOperID != GET_PEER)
        {
            m_LockManager->CMgr_ReleaseLock(iOperID,conn);
        }
        m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
    }
    else
    {

        if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
        {
            if (resp->respcode() == CMAPI_SUCCESS)
            {

                m_dbInterface->check_for_requestid(req,resp);

                DLOG_NONE(">HandleDreSetPeerConfigReqsRespCbk: DRE operation - Successful. Committing the database ");
                //TODO: commit database

                /* In case GET_PEER
                 * We are sending request to dre. to get the PeerConnection
                 * Status, So everytime Get Peer is called this Callback
                 * be executed. Since in all Get Function (Even in GET_PEER)
                 * we are not taking MySql NameLock so Release is not
                 * Requiered */

                if(iOperID != GET_PEER)
                {
                    if(iOperID != GET_PEERSTATE)
                    {
                        m_LockManager->CMgr_ReleaseLock(iOperID,conn);
#if DRE
                        m_standbydiaMgtCallerObj->HandleDreSetPeerConfigReqs(*req, (void*)NULL);
#else
                        m_standbyiwfdiaMgtCallerObj->HandleDreSetPeerConfigReqs(*req, (void*)NULL);
#endif
                    }
                }
                m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
            }
            else {

                /* In case GET_PEER
                 * We are sending request to dre. to get the PeerConnection
                 * Status, So everytime Get Peer is called this Callback
                 * be executed. Since in all Get Function (Even in GET_PEER)
                 * we are not taking MySql NameLock so Release is not
                 * Requiered */
                DLOG_DEBUG(" > %s : CMAPI_FAILED",__FUNCTION__);
                DLOG_DEBUG(" > %s : DRE Response - %s",__FUNCTION__,resp->DebugString().c_str());

                if(iOperID != GET_PEER)
                {
                    if(iOperID != GET_PEERSTATE)
                    {
                        m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                    }
                }
                m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
                //resp->SerializeToString(&StrVal);
                //m_CMAPIResponse->Set(StrVal);
            }
        } else {
            if (resp == NULL || MeSS::Handle().m_state == MESS_STATUS_TIMEOUT)
            {
                retVal = CMAPI_SRVERROR;
                ErrorResponse.set_respcode(retVal);
                //ErrorResponse.SerializeToString(&StrVal);
                resp = &ErrorResponse;
            } else {
                //resp->SerializeToString(&StrVal);
            }

            /* In case GET_PEER
             * We are sending request to dre. to get the PeerConnection
             * Status, So everytime Get Peer is called this Callback
             * be executed. Since in all Get Function (Even in GET_PEER)
             * we are not taking MySql NameLock so Release is not
             * Requiered */

            if(iOperID != GET_PEER)
            {
                if(iOperID != GET_PEERSTATE)
                {
                    m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                    m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
                }
            }

            //m_CMAPIResponse->Set(StrVal);
        }
    }

    m_configResultsHandler[cookie->comp]->SendDREConfigResult(*resp);

    deleteCookie(cookie,SET_PEER);
    return 0;
}

int CMAPICMgr::HandleDreDelPeerConfigReqsRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    std::string StrVal;
    DRECfgResp ErrorResponse;
    DLOG_NONE(">HandleDreDelPeerConfigReqsRespCbk : ");

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_NONE("Response From Instance %d", MeSS::Handle().m_src.instance);
        return 0;
    }

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    int iOperID = cookie->iReqID;
    void* conn = cookie->con;
    PeersConfig *req = (PeersConfig *)cookie->req;

    if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
    {
        if(resp == NULL)
        {
            resp = &ErrorResponse;
        }
        DLOG_WARNING("MESS Responded with state : MESS_STATUS_NOT_READY ");

        retVal = CMAPI_SRVERROR;
        resp->set_respcode(CMAPI_SRVERROR);
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey(errorMap[CONFIG_COMMON_MESS_NOT_READY]);
        m_LockManager->CMgr_ReleaseLock(iOperID,conn);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
    }
    else
    {
        if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
        {
            if (resp->respcode() == CMAPI_SUCCESS)
            {

                DLOG_NONE(">HandleDreDelPeerConfigReqsRespCbk: DRE operation - Successful. Committing the database ");
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                //commit database
                m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
#if DRE
                m_standbydiaMgtCallerObj->HandleDreDelPeerConfigReqs(*req, (void*)NULL);
#else
                m_standbyiwfdiaMgtCallerObj->HandleDreDelPeerConfigReqs(*req, (void*)NULL);
#endif
            }
            else {
                //resp->SerializeToString(&StrVal);
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
            }
        } else {
            if (resp == NULL || MeSS::Handle().m_state == MESS_STATUS_TIMEOUT)
            {
                retVal = CMAPI_SRVERROR;
                ErrorResponse.set_respcode(retVal);
                //ErrorResponse.SerializeToString(&StrVal);
                resp = &ErrorResponse;
            } else {
                //resp->SerializeToString(&StrVal);
            }
            //m_CMAPIResponse->Set(StrVal);
            m_LockManager->CMgr_ReleaseLock(iOperID,conn);
            m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
        }
    }
    m_configResultsHandler[cookie->comp]->SendDREConfigResult(*resp);

    deleteCookie(cookie,DEL_PEER);
    return retVal ;
}

int CMAPICMgr::HandleDreSetRealmConfigReqsRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    std::string StrVal;
    DRECfgResp ErrorResponse;
    DLOG_NONE(">HandleDreSetRealmConfigReqsRespCbk : ");

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_NONE("Response From Instance %d", MeSS::Handle().m_src.instance);
        return 0;
    }

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    int iOperID = cookie->iReqID;
    void* conn = cookie->con;
    RealmsConfig *req = (RealmsConfig *) cookie->req;

    if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
    {
        if(resp == NULL)
        {
            resp = &ErrorResponse;
        }
        DLOG_WARNING("MESS Responded with state : MESS_STATUS_NOT_READY ");

        retVal = CMAPI_SRVERROR;
        resp->set_respcode(CMAPI_SRVERROR);
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey(errorMap[CONFIG_COMMON_MESS_NOT_READY]);
        m_LockManager->CMgr_ReleaseLock(iOperID,conn);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
    }
    else
    {
        if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
        {
            if (resp->respcode() == CMAPI_SUCCESS)
            {
                DLOG_NONE(">HandleDreSetRealmConfigReqsRespCbk : DRE operation - Successful. Committing the database ");
                //commit database
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
#if DRE
                m_standbydiaMgtCallerObj->HandleDreSetRealmConfigReqs(*req, (void*)NULL);
#else
                m_standbyiwfdiaMgtCallerObj->HandleDreSetRealmConfigReqs(*req, (void*)NULL);
#endif
            }
            else {
                //resp->SerializeToString(&StrVal);
                //m_CMAPIResponse->Set(StrVal);
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
            }
        } else {
            if (resp == NULL || MeSS::Handle().m_state == MESS_STATUS_TIMEOUT)
            {
                retVal = CMAPI_SRVERROR;
                ErrorResponse.set_respcode(retVal);
                //ErrorResponse.SerializeToString(&StrVal);
                resp = &ErrorResponse;
            } else {
                //resp->SerializeToString(&StrVal);
            }
            //m_CMAPIResponse->Set(StrVal);
            m_LockManager->CMgr_ReleaseLock(iOperID,conn);
            m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
        }
    }

    m_configResultsHandler[cookie->comp]->SendDREConfigResult(*resp);

    deleteCookie(cookie,SET_REALM);
    return retVal;
}

int CMAPICMgr::HandleDreDelRealmConfigReqsRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    std::string StrVal;
    DRECfgResp ErrorResponse;
    DLOG_NONE(">HandleDreDelRealmConfigReqsRespCbk : ");

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_NONE("Response From Instance %d", MeSS::Handle().m_src.instance);
        return 0;
    }

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    int iOperID = cookie->iReqID;
    void* conn = cookie->con;
    RealmsConfig *req = (RealmsConfig *)cookie->req;

    if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
    {
        if(resp == NULL)
        {
            resp = &ErrorResponse;
        }
        DLOG_WARNING("MESS Responded with state : MESS_STATUS_NOT_READY ");

        retVal = CMAPI_SRVERROR;
        resp->set_respcode(CMAPI_SRVERROR);
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey(errorMap[CONFIG_COMMON_MESS_NOT_READY]);
        m_LockManager->CMgr_ReleaseLock(iOperID,conn);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
    }
    else
    {

        if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
        {
            if (resp->respcode() == CMAPI_SUCCESS)
            {

                DLOG_NONE(">HandleDreDelRealmConfigReqsRespCbk : DRE operation - Successful. Committing the database ");
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                //commit database
                m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
#if DRE
                m_standbydiaMgtCallerObj->HandleDreDelRealmConfigReqs(*req, (void*)NULL);
#else
                m_standbyiwfdiaMgtCallerObj->HandleDreDelRealmConfigReqs(*req, (void*)NULL);
#endif
            }
            else {
                //resp->SerializeToString(&StrVal);
                //m_CMAPIResponse->Set(StrVal);
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
            }

        } else {
            if (resp == NULL || MeSS::Handle().m_state == MESS_STATUS_TIMEOUT)
            {
                retVal = CMAPI_SRVERROR;
                ErrorResponse.set_respcode(retVal);
                //ErrorResponse.SerializeToString(&StrVal);
                resp = &ErrorResponse;
            } else {
                //resp->SerializeToString(&StrVal);
            }
            //m_CMAPIResponse->Set(StrVal);
            m_LockManager->CMgr_ReleaseLock(iOperID,conn);
            m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
        }
    }

    m_configResultsHandler[cookie->comp]->SendDREConfigResult(*resp);

    deleteCookie(cookie,DEL_REALM);
    return retVal;
}


int CMAPICMgr::FetchDreConfiguration(PeersConfig *req,DRECfgResp *resp)
{

    DbStatus_e iReturnPeer = DRE_DB_FAIL;
    DbStatus_e iReturnRealm = DRE_DB_FAIL;

    DLOG_NONE(">FetchDreConfiguration : Entering\n");

    DLOG_DEBUG("ConfigFetch req = %s",req->DebugString().c_str());
    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }
#if 0
    LocalHostConfig LocalHostConfigReq;
    iReturnLocalHost = m_dbInterface->mysql_LocalHost_Get_Config_Reqs(&LocalHostConfigReq,resp);
#endif

    PeersConfig PeersConfigReq;
    iReturnPeer = m_dbInterface->mysql_Peer_Get_Config_Reqs(&PeersConfigReq,resp);

    RealmsConfig RealmsConfigReq;
    iReturnRealm = m_dbInterface->mysql_Realm_Get_Config_Reqs(&RealmsConfigReq,resp);


    if(iReturnPeer == DRE_DB_SUCCESS && iReturnRealm == DRE_DB_SUCCESS)
        resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturnPeer == GET_PEER_ERR_NO_DATA_PRESENT)
        resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturnRealm == GET_REALM_ERR_NO_DATA_PRESENT)
        resp->set_respcode(CMAPI_SUCCESS);
    else
        resp->set_respcode(CMAPI_ERROR);

    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("ConfigFetch resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("ConfigFetch req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

int CMAPICMgr::SendDREConfigResultRespCbk(CMAPIRes *Resp)
{
    return 0;
}

void CMAPICMgr::deleteCookie(CMgrCookie *CookieObj,int iType)
{
    if(!CookieObj)
        return;

    if(CookieObj->req)
    {
        if(iType == DEL_REALM)
            delete (RealmsConfig*)CookieObj->req;
        else if(iType == SET_REALM)
            delete (RealmsConfig*)CookieObj->req;
        else if(iType == DEL_PEER)
            delete (PeersConfig*)CookieObj->req;
        else if(iType == SET_PEER)
            delete (PeersConfig*)CookieObj->req;
        else if(iType == SET_HOST)
            delete (LocalHostConfig*)CookieObj->req;
        else if(iType == SET_ASF)
            delete (ASFConfigReq*)CookieObj->req;
        else if(iType == ADD_PEERGROUP)
            delete (LBPeerGroupReq*)CookieObj->req;
        else if(iType == SET_LOGGERCONFIG)
            delete (LoggerConfReq*)CookieObj->req;
        else if(iType == SET_TRACE)
            delete (TraceReq*)CookieObj->req;
        else if(iType == SET_SRCONFIG)
            delete (StaticRoutingTableConfigReq*)CookieObj->req;
        else if(iType == SET_REMOTE_ROUTE)
            delete (IwfSigtranRemoteRoutesConfig*)CookieObj->req;
    }

    delete CookieObj;
}
