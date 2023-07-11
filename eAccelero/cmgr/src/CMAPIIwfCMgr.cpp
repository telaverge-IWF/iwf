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
#include <CMAPIIwfCMgr.h>
#include <CMAPICommon.h>
#include <CMgrIwfDbInterface.h>

#include "IwfErrorResp.h"
#include <CMgrLock.h>
using namespace std;
using namespace eAccelero;

extern std::map<int,std::string> errorMap;
CMAPIIwfCMgr::~CMAPIIwfCMgr()
{
    if(m_IwfdbInterface)
    {
        delete m_IwfdbInterface;
    }

    if(m_configResultsHandler[COMP_CLI_PROC])
    {
        delete m_configResultsHandler[COMP_CLI_PROC];
    }

    if(m_configResultsHandler[COMP_WEBAGENT_PROC])
    {
        delete m_configResultsHandler[COMP_WEBAGENT_PROC];
    }

    if(m_iwfSigtranMethods)
    {
        delete m_iwfSigtranMethods;
    }

    if(m_standbyiwfSigtranMethods)
    {
        delete m_standbyiwfSigtranMethods;
    }
}

CMAPIIwfCMgr::CMAPIIwfCMgr(string sHostName,string sUserName,string sPassword,string sDataBase, uint16_t instanceId,ConfigManagerAlarms *pConfigManagerAlarms,ConfigManager *pConfigManager):
    m_instanceId(instanceId)
{

    m_ConfigManager = pConfigManager;
    m_dbHostname = sHostName;
    CMgrIwfDbInterface *CMgrIwfDbObj = new CMgrIwfDbInterface(sHostName, sUserName, sPassword, sDataBase, pConfigManager,pConfigManagerAlarms);
    m_IwfdbInterface = CMgrIwfDbObj;
    m_LockManager = new CnfLockMgr(CMgrIwfDbObj);

    /* for n active, n standby scenario this will not work */

    MeSSEndpoint iwfDest = { COMP_IWF_APP, MESS_MIN_ACTIVE_INSTANCE};
    MeSSEndpoint standbyiwfDest = { COMP_IWF_APP, MESS_MIN_STANDBY_INSTANCE};

    m_iwfSigtranMethods = new Stub::IwfSigtranMethods(iwfDest, 0);
    m_standbyiwfSigtranMethods = new Stub::IwfSigtranMethods(standbyiwfDest, 0);

    Stub::IwfSigtranMethodsRespCbk::RegisterIwfSigtranMethodsRespHandler();

    MeSSEndpoint cliDest = { COMP_CLI_PROC, m_instanceId };
    m_configResultsHandler[COMP_CLI_PROC] = new Stub::IwfConfigResults(cliDest, 0);
    Stub::IwfConfigResultsRespCbk::RegisterIwfConfigResultsRespHandler();


    MeSSEndpoint agentDest = { COMP_WEBAGENT_PROC, m_instanceId };
    m_configResultsHandler[COMP_WEBAGENT_PROC] = new Stub::IwfConfigResults(agentDest, 0);

    /* for n active, n standby scenario this will not work */

}


int CMAPIIwfCMgr::UpdateInstanceId(uint16_t instanceId)
{

    DLOG_DEBUG("Update Instance Id");

    m_instanceId = instanceId;
    MeSSEndpoint cliDest = { COMP_CLI_PROC, m_instanceId };

    delete m_configResultsHandler[COMP_CLI_PROC];
    m_configResultsHandler[COMP_CLI_PROC] = new Stub::IwfConfigResults(cliDest, 0);

    MeSSEndpoint agentDest = { COMP_WEBAGENT_PROC, m_instanceId };
    delete m_configResultsHandler[COMP_WEBAGENT_PROC];
    m_configResultsHandler[COMP_WEBAGENT_PROC] = new Stub::IwfConfigResults(agentDest, 0);

    return 0;
}

void CMAPIIwfCMgr::deleteCookie(CMgrCookie *CookieObj,int iType)
{
    if(!CookieObj)
        return;

    if(CookieObj->req)
    {
        if(iType == SET_SIGTRAN_DEST)
            delete (IwfSigtranDestinationsConfig*)CookieObj->req;
        if(iType == SET_REMOTE_ROUTE)
            delete (IwfSigtranRemoteRoutesConfig*) CookieObj->req;
        if(iType == SET_ASSOC)
            delete (IwfSigtranAssociationsConfig*) CookieObj->req;
        if(iType == DEL_ASSOC_SET)
            delete (IwfSigtranAssociationSetsConfig*) CookieObj->req;
        if(iType == SET_S6AMAP_DATA)
            delete (IwfTranslationDataConfig*) CookieObj->req;
        if(iType == MOD_LOCAL_HOST)
            delete (IwfLocalHostsConfig*) CookieObj->req;
        if(iType == SET_TRANSLATOR_RULE)
            delete (IwfTranslatorRulesConfig*) CookieObj->req;
        if(iType == DEL_IWF_TIMERS)
            delete (IwfTimersConfig*) CookieObj->req;
        if(iType == DEL_IWF_FEATURES)
            delete (IwfFeaturesConfig*) CookieObj->req;
        if(iType == DEL_IWF_DCCA_FEATURES)
            delete (IwfDccaGenConfig*) CookieObj->req;
        if(iType == DEL_IWF_DCCA_DEST)
            delete (IwfDccaDestsConfig*) CookieObj->req;
        if(iType == SET_UAL_CONFIG)
            delete (IwfSigtranUalManagerConfig*) CookieObj->req;
        if(iType == SET_IWF_PROT_ACTIONS)
            delete (IwfProtocolActionsConfig*) CookieObj->req;
    }

    delete CookieObj;
}

int CMAPIIwfCMgr::FetchIwfProtocolActionsConfiguration(IwfProtocolActionsConfig *req, IWFCfgResp *resp)
{
    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" req %p %s ",req,__FUNCTION__);

    if (IWF_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respid(CMAPI_ERROR);
        m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    iReturn = m_IwfdbInterface->mysql_IwfProtocolAction_Get_Config_Reqs(req,resp);

    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("ConfigFetch resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("ConfigFetch req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPIIwfCMgr::FetchIwfLocalConfiguration(IwfLocalHostsConfig *req, IWFCfgResp *resp)
{
    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" req %p %s ",req,__FUNCTION__);

    if (IWF_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respid(CMAPI_ERROR);
        m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    iReturn = m_IwfdbInterface->mysql_IWFLocalConfig_Get_Config_Reqs(req,resp);

    if(iReturn == IWF_DB_SUCCESS)
    {
        IwfSigtranUalManagerConfig *LocalIwfSigtranUalManagerConfig = NULL;
        iReturn = m_IwfdbInterface->mysql_IwfUal_Get_Config_Reqs(LocalIwfSigtranUalManagerConfig,resp);
        resp->set_respid(CMAPI_SUCCESS);
    }
    else
        resp->set_respid(CMAPI_ERROR);


    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("ConfigFetch resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("ConfigFetch req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

int CMAPIIwfCMgr::FetchIwfAssociationSetConfiguration(IwfSigtranAssociationSetsConfig *req, IWFCfgResp *resp)
{
    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" req %p %s ",req,__FUNCTION__);

    if (IWF_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respid(CMAPI_ERROR);
        m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    iReturn = m_IwfdbInterface->mysql_IwfSigtranAssociationSets_Get_Config_Reqs(req,resp);

    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("ConfigFetch resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("ConfigFetch req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;


}

int CMAPIIwfCMgr::FetchIwfAssociationConfiguration(IwfSigtranAssociationsConfig *req, IWFCfgResp *resp)
{
    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" req %p %s ",req,__FUNCTION__);

    if (IWF_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respid(CMAPI_ERROR);
        m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    iReturn = m_IwfdbInterface->mysql_IwfSigtranAssociations_Get_Config_Reqs(req,resp);

    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("ConfigFetch resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("ConfigFetch req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;


}

int CMAPIIwfCMgr::FetchIwfRemoteRouteConfiguration(IwfSigtranRemoteRoutesConfig *req, IWFCfgResp *resp)
{
    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" req %p %s ",req,__FUNCTION__);

    if (IWF_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respid(CMAPI_ERROR);
        m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    iReturn = m_IwfdbInterface->mysql_IwfSigtranRemoteRoute_Get_Config_Reqs(req,resp);

    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("ConfigFetch resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("ConfigFetch req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;


}

int CMAPIIwfCMgr::FetchIwfTranslatorRuleConfiguration(IwfTranslatorRulesConfig *req, IWFCfgResp *resp)
{
    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" req %p %s ",req,__FUNCTION__);

    if (IWF_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respid(CMAPI_ERROR);
        m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    iReturn = m_IwfdbInterface->mysql_IWFTranslatorRules_Get_Config_Reqs(req,resp);

    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("ConfigFetch resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("ConfigFetch req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;


}

int CMAPIIwfCMgr::FetchIwfTranslationDataConfiguration(IwfTranslationDataConfig *req, IWFCfgResp *resp)
{
    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" req %p %s ",req,__FUNCTION__);

    if (IWF_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respid(CMAPI_ERROR);
        m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    iReturn = m_IwfdbInterface->mysql_IWFAllTranslatorData_Get_Config_Reqs(req,resp);

    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("ConfigFetch resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("ConfigFetch req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;


}

int CMAPIIwfCMgr::FetchIwfTimersConfiguration(IwfTimersConfig *req, IWFCfgResp *resp)
{
    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" req %p %s ",req,__FUNCTION__);

    if (IWF_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respid(CMAPI_ERROR);
        m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    iReturn = m_IwfdbInterface->mysql_IWFTimers_Get_Config_Reqs(req,resp);

    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("ConfigFetch resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("ConfigFetch req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;


}

int CMAPIIwfCMgr::FetchIwfFeaturesConfiguration(IwfFeaturesConfig *req, IWFCfgResp *resp)
{
    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" req %p %s ",req,__FUNCTION__);

    if (IWF_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respid(CMAPI_ERROR);
        m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    iReturn = m_IwfdbInterface->mysql_IWFFeatures_Get_Config_Reqs(req,resp);

    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("ConfigFetch resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("ConfigFetch req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPIIwfCMgr::FetchIwfDccaConfiguration(IwfDccaConfig* req, IWFCfgResp* resp)
{
    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" req %p %s ",req,__FUNCTION__);

    if (IWF_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respid(CMAPI_ERROR);
        m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }
    IwfDccaGenConfig LocalIwfDccaGenConfig;
    IwfDccaDestsConfig LocalIwfDccaDestsConfig;
    iReturn = m_IwfdbInterface->mysql_IWFDccaDestConfig_Get_Config_Reqs(&LocalIwfDccaDestsConfig,resp);
    iReturn = m_IwfdbInterface->mysql_IWFDccaFeatures_Get_Config_Reqs(&LocalIwfDccaGenConfig,resp);

    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("ConfigFetch resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("ConfigFetch req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPIIwfCMgr::SendIWFConfigResultRespCbk(CMAPIRes* resp)
{

    return 0;
}

int CMAPIIwfCMgr::TestIwfCMgr()
{
    //********** SctpEndPoint Table ****************
    //TestIwfSctpEndPointAdd();
    //TestIwfSctpEndPointDel();
    //TestIwfSctpEndPointMod();
    //TestIwfSctpEndPointSelect();

    //********** SctpProfile Table ****************
    // TestSctpProfileAdd();
    //TestSctpProfileMod();
    //TestSctpProfileDel();
    //TestSctpProfileSelect();

    //********** Association Table ****************
    //TestAssociationAdd();
    //TestAssociationMod();
    //TestAssociationDel();
    //TestAssociationSelect();

    //********** Multihoming Table ****************
    //TestMultihomingAdd();
    //TestMultihomingMod();
    //    TestMultihomingDel();
    //TestMultihomingSelect();
    // TestMultihomingSelectAll();

    //********** AssociationSet Table ****************
    //TestAssocSetAdd();
    //TestAssocSetMod();
    //TestAssocSetDel();
    //TestAssocSetSelect();

    //********** AssociationSetMapping Table ****************
    //TestAssocSetMappingAdd();
    //TestAssocSetMappingMod();
    //TestAssocSetMappingDel();
    //TestAssocSetMappingSelect();
    //TestAssocSetMappingSelectall();

    //********** AssociationSetMapping Table ****************
    //TestIwfLocalConfigAdd();
    //TestIwfLocalConfigMod();
    //    TestIwfLocalConfigDel();
    //   TestIwfLocalConfigSelect();

    //********** AssociationSetMapping Table ****************
    //TestIwfLocalSSNMappingAdd();
    //TestIwfLocalSSNMappingMod();
    //TestIwfLocalSSNMappingDel();
    //TestIwfLocalSSNMappingSelect();

    //********** TranslatorRule Table ****************
    //TestIwfTranslatorRuleAdd();
    //TestIwfTranslatorRuleMod();
    //TestIwfTranslatorRuleDel();
    //TestIwfTranslatorRuleSelect();
    //TestIwfTranslatorRuleSelectAll();

    //********** Destination Table ****************
    //TestIwfDestinationAdd();
    //TestIwfDestinationMod();
    //TestIwfDestinationDel();
    //TestIwfDestinationSelect();

    //********** MapS6aConfig Table ****************
    //TestIwfMapS6aConfigAdd();
    //TestIwfMapS6aConfigMod();
    //TestIwfMapS6aConfigDel();//Not allowed
    //TestIwfMapS6aConfigSelect();

    //********** S6aMapConfig Table ****************
    //TestIwfS6aMapConfigAdd();
    //TestIwfS6aMapConfigMod();
    //TestIwfS6aMapConfigSelect();
    //TestIwfS6aMapConfigDel();//Not Allowed

    //********** S6aMapConfig Table ****************
    //TestIwfCapRoConfigAdd();
    //TestIwfCapRoConfigMod();//Not Allowed
    //TestIwfCapRoConfigDel();//Not Allowed
    //TestIwfCapRoConfigSelect();

    //********** CapRoIdpConfig Table ****************
   // TestCapRoIdpConfigAdd();
    //TestCapRoIdpConfigMod();
    //TestCapRoIdpConfigDel();
    //TestCapRoIdpConfigSelect();

    //********** CapRoIdpConfig Table ****************
    //TestCapRoIdpSmsConfigAdd();
    //TestCapRoIdpSmsConfigMod();
    //TestCapRoIdpSmsConfigDel();
    //TestCapRoIdpSmsConfigSelect();

    //********** CapRoIdpConfig Table ****************
    //TestRemoteRouteAdd();
    //TestRemoteRouteMod();
    //TestRemoteRouteDel();
    //TestRemoteRouteSelect();

    //********** S6aMapSgsnAddr Table ****************
    //TestIwfS6aMapAddrAdd();
    //TestIwfS6aMapAddrSelect();
    //TestIwfS6aMapAddrSelectAll();


    //**********  Table ****************
    //TestExtServiceSelectAll();
    //TestExtServiceSelect();

    //TestExtBearerServiceSelectAll();
    //TestExtBearerServiceSelect();

    //**********  Timer ****************
    //TestIwfTimerAdd();
    //TestIwfTimerSelect();
    return 0;
}

DbStatus_e CMAPIIwfCMgr::TestIwfSctpEndPointAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranSctpEndPointConfig SctpEndPointObj;

    string TestVariable="EndPoint1";
    SctpEndPointObj.set_endpointname(TestVariable);
    TestVariable="Local";
    SctpEndPointObj.set_endpointtype(TestVariable);
    TestVariable="172.16.12.14";
    SctpEndPointObj.set_ipaddress(TestVariable);
    SctpEndPointObj.set_port(3333);
    TestVariable="SCTP";
    SctpEndPointObj.set_transporttype(TestVariable);
    SctpEndPointObj.set_isclient(1);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSctpEndpoint_Create_Add_Query(&SctpEndPointObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfSctpEndPointDel()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranSctpEndPointConfig SctpEndPointObj;

    string TestVariable="EndPointName3";
    SctpEndPointObj.set_endpointname(TestVariable);
    TestVariable="Local";
    SctpEndPointObj.set_endpointtype(TestVariable);
    TestVariable="172.16.12.14";
    SctpEndPointObj.set_ipaddress(TestVariable);
    SctpEndPointObj.set_port(3333);
    TestVariable="SCTP";
    SctpEndPointObj.set_transporttype(TestVariable);
    SctpEndPointObj.set_isclient(0);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSctpEndpoint_Create_Delete_Query(&SctpEndPointObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;

}

DbStatus_e CMAPIIwfCMgr::TestIwfSctpEndPointMod()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranSctpEndPointConfig SctpEndPointObj;

    string TestVariable="EndPointName4";

    SctpEndPointObj.set_endpointname(TestVariable);
    TestVariable="Proxy";
    SctpEndPointObj.set_endpointtype(TestVariable);
    TestVariable="172.16.12.111";
    SctpEndPointObj.set_ipaddress(TestVariable);
    SctpEndPointObj.set_port(3000);
    TestVariable="TCP";
    SctpEndPointObj.set_transporttype(TestVariable);
    SctpEndPointObj.set_isclient(0);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSctpEndpoint_Create_Mod_Query(&SctpEndPointObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;

}

DbStatus_e CMAPIIwfCMgr::TestSctpProfileAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranSctpProfileConfig  SctpProfileObj;

    string TestVariable="Profile2";
    SctpProfileObj.set_sctpprofilename(TestVariable);
    SctpProfileObj.set_heartbeatenable(1);
    SctpProfileObj.set_heartbeattimeout(30);
    SctpProfileObj.set_inittimeout(60);
    SctpProfileObj.set_assocmaxattempt(16);
    SctpProfileObj.set_rtomax(20);
    SctpProfileObj.set_rtomin(2);
    SctpProfileObj.set_rtoinitial(12);
    SctpProfileObj.set_pathfailureretrycount(11);
    SctpProfileObj.set_maxinstreams(4);
    SctpProfileObj.set_numoutstreams(3);
    SctpProfileObj.set_sendtimeout(600);
    SctpProfileObj.set_receivetimeout(500);
    SctpProfileObj.set_shutdowntimeout(400);
    SctpProfileObj.set_pmtutimeout(111);
    SctpProfileObj.set_cookielife(112);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranSCTPProfile_Create_Add_Query(&SctpProfileObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestSctpProfileMod()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranSctpProfileConfig  SctpProfileObj;

    string TestVariable="Profile1";
    SctpProfileObj.set_sctpprofilename(TestVariable);
    SctpProfileObj.set_heartbeatenable(0);
    SctpProfileObj.set_heartbeattimeout(31);
    SctpProfileObj.set_inittimeout(61);
    SctpProfileObj.set_assocmaxattempt(17);
    SctpProfileObj.set_rtomax(21);
    SctpProfileObj.set_rtomin(3);
    SctpProfileObj.set_rtoinitial(13);
    SctpProfileObj.set_pathfailureretrycount(12);
    SctpProfileObj.set_maxinstreams(5);
    SctpProfileObj.set_numoutstreams(4);
    SctpProfileObj.set_sendtimeout(601);
    SctpProfileObj.set_receivetimeout(501);
    SctpProfileObj.set_shutdowntimeout(401);
    SctpProfileObj.set_pmtutimeout(112);
    SctpProfileObj.set_cookielife(113);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranSCTPProfile_Create_Mod_Query(&SctpProfileObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestSctpProfileDel()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranSctpProfileConfig  SctpProfileObj;

    string TestVariable="Profile1";
    SctpProfileObj.set_sctpprofilename(TestVariable);
    SctpProfileObj.set_heartbeatenable(0);
    SctpProfileObj.set_heartbeattimeout(31);
    SctpProfileObj.set_inittimeout(61);
    SctpProfileObj.set_assocmaxattempt(17);
    SctpProfileObj.set_rtomax(21);
    SctpProfileObj.set_rtomin(3);
    SctpProfileObj.set_rtoinitial(13);
    SctpProfileObj.set_pathfailureretrycount(12);
    SctpProfileObj.set_maxinstreams(5);
    SctpProfileObj.set_numoutstreams(4);
    SctpProfileObj.set_sendtimeout(601);
    SctpProfileObj.set_receivetimeout(501);
    SctpProfileObj.set_shutdowntimeout(401);
    SctpProfileObj.set_pmtutimeout(112);
    SctpProfileObj.set_cookielife(113);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranSCTPProfile_Create_Delete_Query(&SctpProfileObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestAssociationAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranAssociationConfig AssociationObj;
    IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = NULL;
    pIwfSigtranSctpProfileConfig = AssociationObj.mutable_sctpprofile();
    IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = NULL;
    pIwfSigtranSctpEndPointConfig = AssociationObj.mutable_localendpoint();

    string TestVariable="Association4";
    AssociationObj.set_associationname(TestVariable);
    TestVariable="Profile2";
    pIwfSigtranSctpProfileConfig->set_sctpprofilename(TestVariable);
    TestVariable="EndPoint1";
    pIwfSigtranSctpEndPointConfig->set_endpointname(TestVariable);
    pIwfSigtranSctpEndPointConfig = AssociationObj.mutable_remoteendpoint();
    TestVariable="EndPoint1";
    pIwfSigtranSctpEndPointConfig->set_endpointname(TestVariable);
    AssociationObj.set_status(1);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranAssociation_Create_Add_Query(&AssociationObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestAssociationDel()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranAssociationConfig AssociationObj;
    IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = NULL;
    pIwfSigtranSctpProfileConfig = AssociationObj.mutable_sctpprofile();
    IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = NULL;
    pIwfSigtranSctpEndPointConfig = AssociationObj.mutable_localendpoint();

    string TestVariable="Association1";
    AssociationObj.set_associationname(TestVariable);
    TestVariable="Profile1";
    pIwfSigtranSctpProfileConfig->set_sctpprofilename(TestVariable);
    TestVariable="EndPointName3";
    pIwfSigtranSctpEndPointConfig->set_endpointname(TestVariable);
    pIwfSigtranSctpEndPointConfig = AssociationObj.mutable_remoteendpoint();
    TestVariable="EndPointName3";
    pIwfSigtranSctpEndPointConfig->set_endpointname(TestVariable);
    AssociationObj.set_status(1);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranAssociation_Create_Delete_Query(&AssociationObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestAssociationMod()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranAssociationConfig AssociationObj;
    IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = NULL;
    pIwfSigtranSctpProfileConfig = AssociationObj.mutable_sctpprofile();
    IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = NULL;
    pIwfSigtranSctpEndPointConfig = AssociationObj.mutable_localendpoint();

    string TestVariable="Association1";
    AssociationObj.set_associationname(TestVariable);
    TestVariable="Profile2";
    pIwfSigtranSctpProfileConfig->set_sctpprofilename(TestVariable);
    TestVariable="EndPointName4";
    pIwfSigtranSctpEndPointConfig->set_endpointname(TestVariable);
    pIwfSigtranSctpEndPointConfig = AssociationObj.mutable_remoteendpoint();
    TestVariable="EndPointName4";
    pIwfSigtranSctpEndPointConfig->set_endpointname(TestVariable);
    AssociationObj.set_status(1);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranAssociation_Create_Mod_Query(&AssociationObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestMultihomingAdd()
{
#if 0
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranAssociationConfig pIwfSigtranAssociationConfig;
    IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = NULL;
    pIwfSigtranMultihomingConfig = pIwfSigtranAssociationConfig.add_multihominginfo();

    string TestVariable;
    TestVariable = "Association3";
    pIwfSigtranAssociationConfig.set_associationname(TestVariable);
    TestVariable = "172.16.12.14";
    pIwfSigtranMultihomingConfig->set_otheripaddress(TestVariable);

    pIwfSigtranMultihomingConfig = pIwfSigtranAssociationConfig.add_multihominginfo();
    TestVariable = "172.16.12.15";
    pIwfSigtranMultihomingConfig->set_otheripaddress(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    for(int i=0;i<pIwfSigtranAssociationConfig.multihominginfo_size();i++)
    {
        m_IwfdbInterface->sql_IWFSigtranMultihoming_Create_Add_Query(&pIwfSigtranAssociationConfig,sStatement,i);
        if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_LBALGO_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            DLOG_ERROR("Query Execution Successfull %s",sStatement);
        }
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
#endif
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestMultihomingDel()
{
#if 0
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranAssociationConfig pIwfSigtranAssociationConfig;
    IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = NULL;
    pIwfSigtranMultihomingConfig = pIwfSigtranAssociationConfig.add_multihominginfo();

    string TestVariable;
    TestVariable = "Association1";
    pIwfSigtranAssociationConfig.set_associationname(TestVariable);
    TestVariable = "172.16.12.14";
    pIwfSigtranMultihomingConfig->set_otheripaddress(TestVariable);

    pIwfSigtranMultihomingConfig = pIwfSigtranAssociationConfig.add_multihominginfo();
    TestVariable = "172.16.12.15";
    pIwfSigtranMultihomingConfig->set_otheripaddress(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    for(int i=0;i<pIwfSigtranAssociationConfig.multihominginfo_size();i++)
    {
        m_IwfdbInterface->sql_IWFSigtranMultihoming_Create_Delete_Query(&pIwfSigtranAssociationConfig,sStatement,i);
        if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_LBALGO_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            DLOG_ERROR("Query Execution Successfull %s",sStatement);
        }
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
#endif
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestMultihomingMod()
{
#if 0
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranAssociationConfig pIwfSigtranAssociationConfig;
    IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = NULL;
    pIwfSigtranMultihomingConfig = pIwfSigtranAssociationConfig.add_multihominginfo();

    string TestVariable;
    TestVariable = "Association2";
    pIwfSigtranAssociationConfig.set_associationname(TestVariable);
    TestVariable = "172.16.12.16";
    pIwfSigtranMultihomingConfig->set_otheripaddress(TestVariable);

    pIwfSigtranMultihomingConfig = pIwfSigtranAssociationConfig.add_multihominginfo();
    TestVariable = "172.16.12.17";
    pIwfSigtranMultihomingConfig->set_otheripaddress(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    for(int i=0;i<pIwfSigtranAssociationConfig.multihominginfo_size();i++)
    {
        m_IwfdbInterface->sql_IWFSigtranMultihoming_Create_Mod_Query(&pIwfSigtranAssociationConfig,sStatement,i);
        if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_LBALGO_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            DLOG_ERROR("Query Execution Successfull %s",sStatement);
        }
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
#endif
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestAssocSetAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranAssociationSetConfig AssociationSetObj;

    string TestVariable="AssocSet2";
    AssociationSetObj.set_associationsetname(TestVariable);
    AssociationSetObj.set_networkindicator(1);
    AssociationSetObj.set_adjacenpointcode(123);
    AssociationSetObj.set_routingcontext(321);

    //AssociationSetObj.set_acktimer(111);
    //TestVariable="SigtranMode";
    //AssociationSetObj.set_sigtranmode(TestVariable);
    TestVariable="TrafficMode";
    AssociationSetObj.set_trafficmode(TestVariable);
    AssociationSetObj.set_aspid(121);
    AssociationSetObj.set_status(0);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranAssocSet_Create_Add_Query(&AssociationSetObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestAssocSetDel()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranAssociationSetConfig AssociationSetObj;

    string TestVariable="AssocSet2";
    AssociationSetObj.set_associationsetname(TestVariable);
    AssociationSetObj.set_networkindicator(1);
    AssociationSetObj.set_adjacenpointcode(123);
    AssociationSetObj.set_routingcontext(321);
    //AssociationSetObj.set_acktimer(111);
    //TestVariable="SigtranMode";
    //AssociationSetObj.set_sigtranmode(TestVariable);
    TestVariable="TrafficMode";
    AssociationSetObj.set_trafficmode(TestVariable);
    AssociationSetObj.set_aspid(121);
    AssociationSetObj.set_status(0);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranAssocSet_Create_Delete_Query(&AssociationSetObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestAssocSetMod()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranAssociationSetConfig AssociationSetObj;

    string TestVariable="AssocSet1";
    AssociationSetObj.set_associationsetname(TestVariable);
    AssociationSetObj.set_networkindicator(2);
    AssociationSetObj.set_adjacenpointcode(124);
    AssociationSetObj.set_routingcontext(322);
    //AssociationSetObj.set_acktimer(112);
    //TestVariable="SigtranMode2";
    //AssociationSetObj.set_sigtranmode(TestVariable);
    TestVariable="TrafficMode2";
    AssociationSetObj.set_trafficmode(TestVariable);
    AssociationSetObj.set_aspid(122);
    AssociationSetObj.set_status(1);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranAssocSet_Create_Mod_Query(&AssociationSetObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestAssocSetMappingAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranAssociationSetConfig IwfSigtranAssociationSetConfigObj;
    IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = NULL;
    pIwfSigtranAssociationConfig = IwfSigtranAssociationSetConfigObj.add_associationinfo();

    string TestVariable;
    TestVariable = "AssocSet2";
    IwfSigtranAssociationSetConfigObj.set_associationsetname(TestVariable);
    TestVariable = "Association4";
    pIwfSigtranAssociationConfig->set_associationname(TestVariable);

    //pIwfSigtranMultihomingConfig = pIwfSigtranAssociationConfig.add_multihominginfo();
    //TestVariable = "172.16.12.15";
    //pIwfSigtranMultihomingConfig->set_otheripaddress(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    for(int i=0;i<IwfSigtranAssociationSetConfigObj.associationinfo_size();i++)
    {
        m_IwfdbInterface->sql_IWFSigtranAssocSetMapping_Create_Add_Query(&IwfSigtranAssociationSetConfigObj,sStatement,i);
        if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_LBALGO_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            DLOG_ERROR("Query Execution Successfull %s",sStatement);
        }
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestAssocSetMappingDel()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranAssociationSetConfig IwfSigtranAssociationSetConfigObj;
    IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = NULL;
    pIwfSigtranAssociationConfig = IwfSigtranAssociationSetConfigObj.add_associationinfo();

    string TestVariable;
    TestVariable = "AssocSet1";
    IwfSigtranAssociationSetConfigObj.set_associationsetname(TestVariable);
    TestVariable = "Association1";
    pIwfSigtranAssociationConfig->set_associationname(TestVariable);

    //pIwfSigtranMultihomingConfig = pIwfSigtranAssociationConfig.add_multihominginfo();
    //TestVariable = "172.16.12.15";
    //pIwfSigtranMultihomingConfig->set_otheripaddress(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    for(int i=0;i<IwfSigtranAssociationSetConfigObj.associationinfo_size();i++)
    {
        m_IwfdbInterface->sql_IWFSigtranAssocSetMapping_Create_Delete_Query(&IwfSigtranAssociationSetConfigObj,sStatement,i);
        if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_LBALGO_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            DLOG_ERROR("Query Execution Successfull %s",sStatement);
        }
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestAssocSetMappingMod()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranAssociationSetConfig IwfSigtranAssociationSetConfigObj;
    IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = NULL;
    pIwfSigtranAssociationConfig = IwfSigtranAssociationSetConfigObj.add_associationinfo();

    string TestVariable;
    TestVariable = "AssocSet1";
    IwfSigtranAssociationSetConfigObj.set_associationsetname(TestVariable);
    TestVariable = "Association2";
    pIwfSigtranAssociationConfig->set_associationname(TestVariable);

    //pIwfSigtranMultihomingConfig = pIwfSigtranAssociationConfig.add_multihominginfo();
    //TestVariable = "172.16.12.15";
    //pIwfSigtranMultihomingConfig->set_otheripaddress(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    for(int i=0;i<IwfSigtranAssociationSetConfigObj.associationinfo_size();i++)
    {
        m_IwfdbInterface->sql_IWFSigtranAssocSetMapping_Create_Mod_Query(&IwfSigtranAssociationSetConfigObj,sStatement,i);
        if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_LBALGO_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            DLOG_ERROR("Query Execution Successfull %s",sStatement);
        }
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfLocalConfigAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfLocalHostConfig IwfLocalHostConfigObj;
    string TestVariable;

    IwfLocalHostConfigObj.set_networkindicator(100);
    IwfLocalHostConfigObj.set_pointcode(200);
    IwfLocalHostConfigObj.set_tcapinvoketimer(300);
    TestVariable="AddressType";
    IwfLocalHostConfigObj.set_addresstype(TestVariable);
    IwfLocalHostConfigObj.set_gti(400);
    //TestVariable="TranslationType";
    IwfLocalHostConfigObj.set_translationtype(1);
    IwfLocalHostConfigObj.set_numberingplan(2);
    IwfLocalHostConfigObj.set_encodingscheme(3);
    IwfLocalHostConfigObj.set_natureofaddrind(4);
    TestVariable="GT_ADDR_DIGITS";
    IwfLocalHostConfigObj.set_gtaddrdigits(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFLocalConfig_Create_Add_Query(&IwfLocalHostConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfLocalConfigDel()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfLocalHostConfig IwfLocalHostConfigObj;
    string TestVariable;

    IwfLocalHostConfigObj.set_networkindicator(100);
    IwfLocalHostConfigObj.set_pointcode(200);
    IwfLocalHostConfigObj.set_tcapinvoketimer(300);
    TestVariable="AddressType";
    IwfLocalHostConfigObj.set_addresstype(TestVariable);
    IwfLocalHostConfigObj.set_gti(400);
    IwfLocalHostConfigObj.set_translationtype(1);
    IwfLocalHostConfigObj.set_numberingplan(2);
    IwfLocalHostConfigObj.set_encodingscheme(3);
    IwfLocalHostConfigObj.set_natureofaddrind(4);
    TestVariable="GT_ADDR_DIGITS";
    IwfLocalHostConfigObj.set_gtaddrdigits(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFLocalConfig_Create_Delete_Query(&IwfLocalHostConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfLocalConfigMod()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfLocalHostConfig IwfLocalHostConfigObj;
    string TestVariable;

    IwfLocalHostConfigObj.set_networkindicator(101);
    IwfLocalHostConfigObj.set_pointcode(200);
    IwfLocalHostConfigObj.set_tcapinvoketimer(301);
    TestVariable="AddressType2";
    IwfLocalHostConfigObj.set_addresstype(TestVariable);
    IwfLocalHostConfigObj.set_gti(401);
    IwfLocalHostConfigObj.set_translationtype(10);
    IwfLocalHostConfigObj.set_numberingplan(20);
    IwfLocalHostConfigObj.set_encodingscheme(30);
    IwfLocalHostConfigObj.set_natureofaddrind(40);
    TestVariable="GT_ADDR_DIGITS2";
    IwfLocalHostConfigObj.set_gtaddrdigits(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFLocalConfig_Create_Mod_Query(&IwfLocalHostConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfLocalConfigSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

   IwfLocalHostConfig IwfLocalHostConfigObj;
   IwfLocalHostConfigObj.set_pointcode(200);
   IWFCfgResp IWFCfgRespObj;

   printf("LocalConfig :\n %s",IwfLocalHostConfigObj.DebugString().c_str());
   m_IwfdbInterface->Fill_IWFLocalConfig_protobuff(&IwfLocalHostConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
   printf("LocalConfig :\n %s",IwfLocalHostConfigObj.DebugString().c_str());
   return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfLocalSSNMappingAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfLocalHostConfig IwfLocalHostConfigObj;
    IwfLocalSSNConfig *pIwfLocalSSNConfig = NULL;
    pIwfLocalSSNConfig = IwfLocalHostConfigObj.add_ssn_config();

    IwfLocalHostConfigObj.set_pointcode(200);
    pIwfLocalSSNConfig->set_ssn(6);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    for(int i=0;i<IwfLocalHostConfigObj.ssn_config_size();i++)
    {
        m_IwfdbInterface->sql_IWFLocalSSNMapping_Create_Add_Query(&IwfLocalHostConfigObj,sStatement,i);
        if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_LBALGO_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            DLOG_ERROR("Query Execution Successfull %s",sStatement);
        }
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfLocalSSNMappingDel()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfLocalHostConfig IwfLocalHostConfigObj;
    IwfLocalSSNConfig *pIwfLocalSSNConfig = NULL;
    pIwfLocalSSNConfig = IwfLocalHostConfigObj.add_ssn_config();

    IwfLocalHostConfigObj.set_pointcode(200);
    pIwfLocalSSNConfig->set_ssn(6);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    for(int i=0;i<IwfLocalHostConfigObj.ssn_config_size();i++)
    {
        m_IwfdbInterface->sql_IWFLocalSSNMapping_Create_Delete_Query(&IwfLocalHostConfigObj,sStatement,i);
        if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_LBALGO_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            DLOG_ERROR("Query Execution Successfull %s",sStatement);
        }
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfDestinationAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranDestinationConfig IwfSigtranDestinationConfigObj;

    string TestVariable="Dest1";
    IwfSigtranDestinationConfigObj.set_destinationname(TestVariable);
    TestVariable="AddressType";
    IwfSigtranDestinationConfigObj.set_addresstype(TestVariable);
    TestVariable="AddressStyle";
    IwfSigtranDestinationConfigObj.set_addressstyle(TestVariable);
    IwfSigtranDestinationConfigObj.set_pointcode(200);
    TestVariable="GT_ADDR_DIGITS";
    IwfSigtranDestinationConfigObj.set_gtaddrdigits(TestVariable);
    IwfSigtranDestinationConfigObj.set_translationtype(2);
    TestVariable="ITU";
    IwfSigtranDestinationConfigObj.set_protocolfamily(TestVariable);
    IwfSigtranDestinationConfigObj.set_networkindicator(300);
    IwfSigtranDestinationConfigObj.set_ssn(400);
    IwfSigtranDestinationConfigObj.set_gti(500);
    IwfSigtranDestinationConfigObj.set_numberingplan(600);
    IwfSigtranDestinationConfigObj.set_encodingscheme(700);
    IwfSigtranDestinationConfigObj.set_natureofaddrind(800);
    IwfSigtranDestinationConfigObj.set_sio(900);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranDestination_Create_Add_Query(&IwfSigtranDestinationConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfDestinationMod()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranDestinationConfig IwfSigtranDestinationConfigObj;

    string TestVariable="Dest1";
    IwfSigtranDestinationConfigObj.set_destinationname(TestVariable);
    TestVariable="AddressType2";
    IwfSigtranDestinationConfigObj.set_addresstype(TestVariable);
    TestVariable="AddressStyle2";
    IwfSigtranDestinationConfigObj.set_addressstyle(TestVariable);
    IwfSigtranDestinationConfigObj.set_pointcode(201);
    TestVariable="GT_ADDR_DIGITS2";
    IwfSigtranDestinationConfigObj.set_gtaddrdigits(TestVariable);
    IwfSigtranDestinationConfigObj.set_translationtype(3);
    TestVariable="ANSI";
    IwfSigtranDestinationConfigObj.set_protocolfamily(TestVariable);
    IwfSigtranDestinationConfigObj.set_networkindicator(301);
    IwfSigtranDestinationConfigObj.set_ssn(401);
    IwfSigtranDestinationConfigObj.set_gti(501);
    IwfSigtranDestinationConfigObj.set_numberingplan(601);
    IwfSigtranDestinationConfigObj.set_encodingscheme(701);
    IwfSigtranDestinationConfigObj.set_natureofaddrind(801);
    IwfSigtranDestinationConfigObj.set_sio(901);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranDestination_Create_Mod_Query(&IwfSigtranDestinationConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfDestinationDel()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranDestinationConfig IwfSigtranDestinationConfigObj;

    string TestVariable="Dest1";
    IwfSigtranDestinationConfigObj.set_destinationname(TestVariable);
    TestVariable="AddressType2";
    IwfSigtranDestinationConfigObj.set_addresstype(TestVariable);
    TestVariable="AddressStyle2";
    IwfSigtranDestinationConfigObj.set_addressstyle(TestVariable);
    IwfSigtranDestinationConfigObj.set_pointcode(201);
    TestVariable="GT_ADDR_DIGITS2";
    IwfSigtranDestinationConfigObj.set_gtaddrdigits(TestVariable);
    IwfSigtranDestinationConfigObj.set_translationtype(3);
    TestVariable="ANSI";
    IwfSigtranDestinationConfigObj.set_protocolfamily(TestVariable);
    IwfSigtranDestinationConfigObj.set_networkindicator(301);
    IwfSigtranDestinationConfigObj.set_ssn(401);
    IwfSigtranDestinationConfigObj.set_gti(501);
    IwfSigtranDestinationConfigObj.set_numberingplan(601);
    IwfSigtranDestinationConfigObj.set_encodingscheme(701);
    IwfSigtranDestinationConfigObj.set_natureofaddrind(801);
    IwfSigtranDestinationConfigObj.set_sio(901);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranDestination_Create_Delete_Query(&IwfSigtranDestinationConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

#if 1
DbStatus_e CMAPIIwfCMgr::TestIwfTranslatorRuleSelect()
{

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

   IwfTranslatorRuleConfig IwfTranslatorRuleConfigObj;
   IwfTranslatorRuleConfigObj.set_translatorrulename("TranslatorRuleName");
   IWFCfgResp IWFCfgRespObj;

   printf("TranslatorRule = %s",IwfTranslatorRuleConfigObj.DebugString().c_str());
   m_IwfdbInterface->Fill_IWFTranslatorRule_protobuff(&IwfTranslatorRuleConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
   printf("TranslatorRule = %s",IwfTranslatorRuleConfigObj.DebugString().c_str());
   return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfTranslatorRuleSelectAll()
{

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

   IwfTranslatorRuleConfig IwfTranslatorRuleConfigObj;
   IWFCfgResp IWFCfgRespObj;

   printf("TranslatorRule = %s",IwfTranslatorRuleConfigObj.DebugString().c_str());
   m_IwfdbInterface->Fill_IWFTranslatorRule_protobuff(&IwfTranslatorRuleConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
   printf("TranslatorRule = %s",IwfTranslatorRuleConfigObj.DebugString().c_str());
   return IWF_DB_SUCCESS;
}
#endif

DbStatus_e CMAPIIwfCMgr::TestIwfTranslatorRuleAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfTranslatorRuleConfig IwfTranslatorRuleConfigObj;
    IwfTranslatorType *pIwfTranslatorTypeReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pIwfTranslatorTypeReq = IwfTranslatorRuleConfigObj.mutable_translatortype();
    pIwfTranslatorConfigReq = IwfTranslatorRuleConfigObj.mutable_translatorinfo();

    string TestVariable="TranslatorRuleName";
    IwfTranslatorRuleConfigObj.set_translatorrulename(TestVariable);
    TestVariable="Dest1";
    IwfTranslatorRuleConfigObj.set_destinationname(TestVariable);
    TestVariable="MCC1";
    IwfTranslatorRuleConfigObj.set_mcc(TestVariable);
    TestVariable="MNC1";
    IwfTranslatorRuleConfigObj.set_mnc(TestVariable);
    TestVariable="APP_ID";
    IwfTranslatorRuleConfigObj.set_appid(TestVariable);
    IwfTranslatorRuleConfigObj.set_ossn(100);
    IwfTranslatorRuleConfigObj.set_dssn(200);
    TestVariable="google.com";
    IwfTranslatorRuleConfigObj.set_httpurl(TestVariable);
    TestVariable="WebService";
    IwfTranslatorRuleConfigObj.set_webservice(TestVariable);
    TestVariable="Diameter";
    pIwfTranslatorTypeReq->set_translatortypename(TestVariable);
    TestVariable="CAP-Ro";
    pIwfTranslatorConfigReq->set_translatorname(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFTranslatorRule_Create_Add_Query(&IwfTranslatorRuleConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();

    return IWF_DB_SUCCESS;
}


DbStatus_e CMAPIIwfCMgr::TestIwfMapS6aConfigAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfMapToS6aConfig IwfMapToS6aConfigObj;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pIwfTranslatorConfigReq = IwfMapToS6aConfigObj.mutable_translatorinfo();

    string TestVariable="Map-s6a";
    pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    TestVariable="HLR_Number123";
    IwfMapToS6aConfigObj.set_hlrnumber(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFMapS6aConfig_Create_Add_Query(&IwfMapToS6aConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfMapS6aConfigMod()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfMapToS6aConfig IwfMapToS6aConfigObj;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pIwfTranslatorConfigReq = IwfMapToS6aConfigObj.mutable_translatorinfo();

    string TestVariable="CAP-Ro";
    pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    TestVariable="HLR_Number321";
    IwfMapToS6aConfigObj.set_hlrnumber(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFMapS6aConfig_Create_Mod_Query(&IwfMapToS6aConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfS6aMapConfigAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfS6aToMapConfig IwfS6aToMapConfigObj;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pIwfTranslatorConfigReq = IwfS6aToMapConfigObj.mutable_translatorinfo();

    string TestVariable="CAP-Ro";
    pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    TestVariable="SGSN_Number123";
    IwfS6aToMapConfigObj.set_sgsnnumber(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFS6aMapConfig_Create_Add_Query(&IwfS6aToMapConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfS6aMapConfigMod()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfS6aToMapConfig IwfS6aToMapConfigObj;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pIwfTranslatorConfigReq = IwfS6aToMapConfigObj.mutable_translatorinfo();

    string TestVariable="CAP-Ro";
    pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    TestVariable="SGSN_Number321";
    IwfS6aToMapConfigObj.set_sgsnnumber(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFS6aMapConfig_Create_Mod_Query(&IwfS6aToMapConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfCapRoConfigAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfCapToRoConfig IwfCapToRoConfigObj;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pIwfTranslatorConfigReq = IwfCapToRoConfigObj.mutable_translatorinfo();

    string TestVariable="CAP-Ro";
    pIwfTranslatorConfigReq->set_translatorname(TestVariable);
   // TestVariable="SGSN_Number321";
    //IwfCapToRoConfigObj.set_sgsnnumber(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFCapRoConfig_Create_Add_Query(&IwfCapToRoConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestCapRoIdpConfigAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfCapToRoConfig IwfCapToRoConfigObj;
    string TestVariable;
    CapRoIdpConfig *pCapRoIdpConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pCapRoIdpConfigReq = IwfCapToRoConfigObj.mutable_caproidpinfo();
    pIwfTranslatorConfigReq = IwfCapToRoConfigObj.mutable_translatorinfo();

    TestVariable = "CAP-Ro";
    pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    pCapRoIdpConfigReq->set_nodefunctionality(100);
    TestVariable = "sipmethod";
    pCapRoIdpConfigReq->set_sipmethod(TestVariable);
    TestVariable = "orignatingtoi";
    pCapRoIdpConfigReq->set_orignatingtoi(TestVariable);
    TestVariable = "terminatingtoi";
    pCapRoIdpConfigReq->set_terminatingtoi(TestVariable);
    TestVariable = "servicecontextid";
    pCapRoIdpConfigReq->set_servicecontextid(TestVariable);
    TestVariable = "causecode";
    pCapRoIdpConfigReq->set_causecode(TestVariable);
    pCapRoIdpConfigReq->set_mscservicespecfictype(200);
    pCapRoIdpConfigReq->set_gmscservicespecifictype(300);
    pCapRoIdpConfigReq->set_multipleserviceindicator(400);
    pCapRoIdpConfigReq->set_cpcservicespecifictype(500);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_CapRoIdpConfig_Create_Add_Query(&IwfCapToRoConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestCapRoIdpConfigMod()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfCapToRoConfig IwfCapToRoConfigObj;
    string TestVariable;
    CapRoIdpConfig *pCapRoIdpConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pCapRoIdpConfigReq = IwfCapToRoConfigObj.mutable_caproidpinfo();
    pIwfTranslatorConfigReq = IwfCapToRoConfigObj.mutable_translatorinfo();

    TestVariable = "CAP-Ro";
    pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    pCapRoIdpConfigReq->set_nodefunctionality(101);
    TestVariable = "sipmethod3";
    pCapRoIdpConfigReq->set_sipmethod(TestVariable);
    TestVariable = "orignatingtoi3";
    pCapRoIdpConfigReq->set_orignatingtoi(TestVariable);
    TestVariable = "terminatingtoi3";
    pCapRoIdpConfigReq->set_terminatingtoi(TestVariable);
    TestVariable = "servicecontextid3";
    pCapRoIdpConfigReq->set_servicecontextid(TestVariable);
    TestVariable = "causecode3";
    pCapRoIdpConfigReq->set_causecode(TestVariable);
    pCapRoIdpConfigReq->set_mscservicespecfictype(201);
    pCapRoIdpConfigReq->set_gmscservicespecifictype(301);
    pCapRoIdpConfigReq->set_multipleserviceindicator(401);
    pCapRoIdpConfigReq->set_cpcservicespecifictype(501);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_CapRoIdpConfig_Create_Mod_Query(&IwfCapToRoConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestCapRoIdpConfigDel()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfCapToRoConfig IwfCapToRoConfigObj;
    string TestVariable;
    CapRoIdpConfig *pCapRoIdpConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pCapRoIdpConfigReq = IwfCapToRoConfigObj.mutable_caproidpinfo();
    pIwfTranslatorConfigReq = IwfCapToRoConfigObj.mutable_translatorinfo();

    TestVariable = "CAP-Ro";
    pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    pCapRoIdpConfigReq->set_nodefunctionality(101);
    TestVariable = "sipmethod2";
    pCapRoIdpConfigReq->set_sipmethod(TestVariable);
    TestVariable = "orignatingtoi2";
    pCapRoIdpConfigReq->set_orignatingtoi(TestVariable);
    TestVariable = "terminatingtoi2";
    pCapRoIdpConfigReq->set_terminatingtoi(TestVariable);
    TestVariable = "servicecontextid2";
    pCapRoIdpConfigReq->set_servicecontextid(TestVariable);
    TestVariable = "causecode2";
    pCapRoIdpConfigReq->set_causecode(TestVariable);
    pCapRoIdpConfigReq->set_mscservicespecfictype(201);
    pCapRoIdpConfigReq->set_gmscservicespecifictype(301);
    pCapRoIdpConfigReq->set_multipleserviceindicator(401);
    pCapRoIdpConfigReq->set_cpcservicespecifictype(501);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_CapRoIdpConfig_Create_Delete_Query(&IwfCapToRoConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestCapRoIdpSmsConfigAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfCapToRoConfig IwfCapToRoConfigObj;
    string TestVariable;
    CapRoIdpSmsConfig *pCapRoIdpSmsConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pCapRoIdpSmsConfigReq = IwfCapToRoConfigObj.mutable_caproidpsmsinfo();
    pIwfTranslatorConfigReq = IwfCapToRoConfigObj.mutable_translatorinfo();

    TestVariable = "CAP-Ro";
    pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    pCapRoIdpSmsConfigReq->set_smsnode(100);
    TestVariable = "172.16.12.14";
    pCapRoIdpSmsConfigReq->set_clientaddress(TestVariable);
    TestVariable = "172.16.12.15";
    pCapRoIdpSmsConfigReq->set_originatorsccpaddress(TestVariable);
    pCapRoIdpSmsConfigReq->set_mscservicespecifictype(200);
    pCapRoIdpSmsConfigReq->set_sgsnservicespecifictype(300);
    pCapRoIdpSmsConfigReq->set_replypathrequested(400);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_CapRoIdpSmsConfig_Create_Add_Query(&IwfCapToRoConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestCapRoIdpSmsConfigMod()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfCapToRoConfig IwfCapToRoConfigObj;
    string TestVariable;
    CapRoIdpSmsConfig *pCapRoIdpSmsConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pCapRoIdpSmsConfigReq = IwfCapToRoConfigObj.mutable_caproidpsmsinfo();
    pIwfTranslatorConfigReq = IwfCapToRoConfigObj.mutable_translatorinfo();

    TestVariable = "CAP-Ro";
    pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    pCapRoIdpSmsConfigReq->set_smsnode(101);
    TestVariable = "172.16.12.10";
    pCapRoIdpSmsConfigReq->set_clientaddress(TestVariable);
    TestVariable = "172.16.12.11";
    pCapRoIdpSmsConfigReq->set_originatorsccpaddress(TestVariable);
    pCapRoIdpSmsConfigReq->set_mscservicespecifictype(201);
    pCapRoIdpSmsConfigReq->set_sgsnservicespecifictype(301);
    pCapRoIdpSmsConfigReq->set_replypathrequested(401);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_CapRoIdpSmsConfig_Create_Mod_Query(&IwfCapToRoConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestCapRoIdpSmsConfigDel()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfCapToRoConfig IwfCapToRoConfigObj;
    string TestVariable;
    CapRoIdpSmsConfig *pCapRoIdpSmsConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pCapRoIdpSmsConfigReq = IwfCapToRoConfigObj.mutable_caproidpsmsinfo();
    pIwfTranslatorConfigReq = IwfCapToRoConfigObj.mutable_translatorinfo();

    TestVariable = "CAP-Ro";
    pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    pCapRoIdpSmsConfigReq->set_smsnode(101);
    TestVariable = "172.16.12.10";
    pCapRoIdpSmsConfigReq->set_clientaddress(TestVariable);
    TestVariable = "172.16.12.11";
    pCapRoIdpSmsConfigReq->set_originatorsccpaddress(TestVariable);
    pCapRoIdpSmsConfigReq->set_mscservicespecifictype(201);
    pCapRoIdpSmsConfigReq->set_sgsnservicespecifictype(301);
    pCapRoIdpSmsConfigReq->set_replypathrequested(401);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_CapRoIdpSmsConfig_Create_Delete_Query(&IwfCapToRoConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfSctpEndPointSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

   IwfSigtranSctpEndPointConfig IwfSigtranSctpEndPointConfigObj;
    string TestVar;
    TestVar = "EndPoint1";
   IwfSigtranSctpEndPointConfigObj.set_endpointname(TestVar);
   IWFCfgResp IWFCfgRespObj;

   printf("SCTP End Point :\n %s",IwfSigtranSctpEndPointConfigObj.DebugString().c_str());
   m_IwfdbInterface->Fill_IWFSctpEndpoint_protobuff(&IwfSigtranSctpEndPointConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
   printf("SCTP End Point :\n %s",IwfSigtranSctpEndPointConfigObj.DebugString().c_str());
   return IWF_DB_SUCCESS;
}


DbStatus_e CMAPIIwfCMgr::TestSctpProfileSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

   IwfSigtranSctpProfileConfig IwfSigtranSctpProfileConfigObj;
   string Test = "Profile2";
   IwfSigtranSctpProfileConfigObj.set_sctpprofilename(Test);
   IWFCfgResp IWFCfgRespObj;

   printf("LocalConfig :\n %s",IwfSigtranSctpProfileConfigObj.DebugString().c_str());
   m_IwfdbInterface->Fill_IWFSigtranSCTPProfile_protobuff(&IwfSigtranSctpProfileConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
   printf("LocalConfig :\n %s",IwfSigtranSctpProfileConfigObj.DebugString().c_str());
   return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestAssociationSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }
   string TestVariable="Association3";
   IwfSigtranAssociationConfig IwfSigtranAssociationConfigObj;
   IwfSigtranAssociationConfigObj.set_associationname(TestVariable);
   IWFCfgResp IWFCfgRespObj;

   printf("LocalConfig :\n %s",IwfSigtranAssociationConfigObj.DebugString().c_str());
   m_IwfdbInterface->Fill_IWFSigtranAssociation_protobuff(&IwfSigtranAssociationConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
   printf("LocalConfig :\n %s",IwfSigtranAssociationConfigObj.DebugString().c_str());
   return IWF_DB_SUCCESS;
}


DbStatus_e CMAPIIwfCMgr::TestAssocSetSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }
    string Test="AssocSet2";
    IwfSigtranAssociationSetConfig IwfSigtranAssociationSetConfigObj;
    IwfSigtranAssociationSetConfigObj.set_associationsetname(Test);
    IWFCfgResp IWFCfgRespObj;

    printf("AssocSet :\n %s",IwfSigtranAssociationSetConfigObj.DebugString().c_str());
    m_IwfdbInterface->Fill_IWFSigtranAssocSet_protobuff(&IwfSigtranAssociationSetConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("AssocSet :\n %s",IwfSigtranAssociationSetConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestAssocSetMappingSelectall()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }
    //int iIndex;
    IwfSigtranAssociationSetConfig IwfSigtranAssociationSetConfigObj;
    //IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = NULL;

    IWFCfgResp IWFCfgRespObj;

    printf("AssocSetMapping :\n %s",IwfSigtranAssociationSetConfigObj.DebugString().c_str());
    m_IwfdbInterface->Fill_IWFSigtranAssocSetMapping_protobuff(&IwfSigtranAssociationSetConfigObj,&IWFCfgRespObj,-1);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("AssocSetMapping :\n %s",IwfSigtranAssociationSetConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestAssocSetMappingSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }
    //int iIndex;
    IwfSigtranAssociationSetConfig IwfSigtranAssociationSetConfigObj;
    IwfSigtranAssociationSetConfigObj.set_associationsetname("AssocSet2");
    IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = NULL;
    pIwfSigtranAssociationConfig = IwfSigtranAssociationSetConfigObj.add_associationinfo();
    //pIwfSigtranAssociationConfig->set_associationsetname("Association3");
    //pIwfSigtranAssociationConfig = IwfSigtranAssociationSetConfigObj.add_associationinfo();
    //pIwfSigtranAssociationConfig->set_associationname("Association4");

    IWFCfgResp IWFCfgRespObj;

    printf("AssocSetMapping :\n %s",IwfSigtranAssociationSetConfigObj.DebugString().c_str());
    for(int i=0;i<IwfSigtranAssociationSetConfigObj.associationinfo_size();i++)
    {
        m_IwfdbInterface->Fill_IWFSigtranAssocSetMapping_protobuff(&IwfSigtranAssociationSetConfigObj,&IWFCfgRespObj,i);
    }

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("AssocSetMapping :\n %s",IwfSigtranAssociationSetConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;
}


DbStatus_e CMAPIIwfCMgr::TestMultihomingSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    string Test = "Association3";
    IwfSigtranAssociationConfig IwfSigtranAssociationConfigObj;
    IwfSigtranAssociationConfigObj.set_associationname(Test);
#if 0
    IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfigReq = NULL;
    pIwfSigtranMultihomingConfigReq = IwfSigtranAssociationConfigObj.add_multihominginfo();

    IWFCfgResp IWFCfgRespObj;
    printf("before MH :\n %s",IwfSigtranAssociationConfigObj.DebugString().c_str());
    for(int i=0;i<IwfSigtranAssociationConfigObj.multihominginfo_size();i++)
    {
        m_IwfdbInterface->Fill_IWFSigtranMultihoming_protobuff(&IwfSigtranAssociationConfigObj,&IWFCfgRespObj,i);
    }
#endif
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("After MH :\n %s",IwfSigtranAssociationConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestMultihomingSelectAll()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    IwfSigtranAssociationConfig IwfSigtranAssociationConfigObj;

    IWFCfgResp IWFCfgRespObj;

    printf("before MH :\n %s",IwfSigtranAssociationConfigObj.DebugString().c_str());
//    m_IwfdbInterface->Fill_IWFSigtranMultihoming_protobuff(&IwfSigtranAssociationConfigObj,&IWFCfgRespObj,-1);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("After MH :\n %s",IwfSigtranAssociationConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfDestinationSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    string Test="Dest1";
    IwfSigtranDestinationConfig IwfSigtranDestinationConfigObj;
    IwfSigtranDestinationConfigObj.set_destinationname(Test);
    IWFCfgResp IWFCfgRespObj;

    printf("before Destination :\n %s",IwfSigtranDestinationConfigObj.DebugString().c_str());
    m_IwfdbInterface->Fill_IWFSigtranDestination_protobuff(&IwfSigtranDestinationConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("after Destination :\n %s",IwfSigtranDestinationConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestRemoteRouteAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranRemoteRouteConfig IwfSigtranRemoteRouteConfigObj;

    IwfSigtranDestinationConfig *pIwfSigtranDestinationConfigReq = NULL;
    pIwfSigtranDestinationConfigReq = IwfSigtranRemoteRouteConfigObj.mutable_destinationinfo();

    string TestVariable="RemoteRoute1";
    IwfSigtranRemoteRouteConfigObj.set_remoteroutename(TestVariable);
    TestVariable="AssocSet2";
    IwfSigtranRemoteRouteConfigObj.set_associationsetname(TestVariable);
    TestVariable="Dest1";
    pIwfSigtranDestinationConfigReq -> set_destinationname(TestVariable);
    IwfSigtranRemoteRouteConfigObj.set_priority(2);


    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranRemoteRoute_Create_Add_Query(&IwfSigtranRemoteRouteConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestRemoteRouteMod()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranRemoteRouteConfig IwfSigtranRemoteRouteConfigObj;

    IwfSigtranDestinationConfig *pIwfSigtranDestinationConfigReq = NULL;
    pIwfSigtranDestinationConfigReq = IwfSigtranRemoteRouteConfigObj.mutable_destinationinfo();

    string TestVariable="RemoteRoute1";
    IwfSigtranRemoteRouteConfigObj.set_remoteroutename(TestVariable);
    TestVariable="AssocSet2";
    IwfSigtranRemoteRouteConfigObj.set_associationsetname(TestVariable);
    TestVariable="Dest1";
    pIwfSigtranDestinationConfigReq -> set_destinationname(TestVariable);
    IwfSigtranRemoteRouteConfigObj.set_priority(10);


    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranRemoteRoute_Create_Mod_Query(&IwfSigtranRemoteRouteConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestRemoteRouteDel()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranRemoteRouteConfig IwfSigtranRemoteRouteConfigObj;

    IwfSigtranDestinationConfig *pIwfSigtranDestinationConfigReq = NULL;
    pIwfSigtranDestinationConfigReq = IwfSigtranRemoteRouteConfigObj.mutable_destinationinfo();

    string TestVariable="RemoteRoute1";
    IwfSigtranRemoteRouteConfigObj.set_remoteroutename(TestVariable);
    TestVariable="AssocSet2";
    IwfSigtranRemoteRouteConfigObj.set_associationsetname(TestVariable);
    TestVariable="Dest1";
    pIwfSigtranDestinationConfigReq -> set_destinationname(TestVariable);
    IwfSigtranRemoteRouteConfigObj.set_priority(10);


    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFSigtranRemoteRoute_Create_Delete_Query(&IwfSigtranRemoteRouteConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestRemoteRouteSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    string Test = "RemoteRoute1";
    IwfSigtranRemoteRouteConfig IwfSigtranRemoteRouteConfigObj;
    IwfSigtranRemoteRouteConfigObj.set_remoteroutename(Test);
    IwfSigtranDestinationConfig *pIwfSigtranDestinationConfigReq = NULL;
    pIwfSigtranDestinationConfigReq = IwfSigtranRemoteRouteConfigObj.mutable_destinationinfo();
    Test="AssocSet2";
    IwfSigtranRemoteRouteConfigObj.set_associationsetname(Test);
    Test="Dest1";
    pIwfSigtranDestinationConfigReq -> set_destinationname(Test);
    IWFCfgResp IWFCfgRespObj;

    printf("LocalConfig :\n %s",IwfSigtranRemoteRouteConfigObj.DebugString().c_str());
    m_IwfdbInterface->Fill_IWFSigtranRemoteRoute_protobuff(&IwfSigtranRemoteRouteConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("LocalConfig :\n %s",IwfSigtranRemoteRouteConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfMapS6aConfigSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    string Test = "MAP-s6a";
    IwfMapToS6aConfig IwfMapToS6aConfigObj;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pIwfTranslatorConfigReq = IwfMapToS6aConfigObj.mutable_translatorinfo();
    pIwfTranslatorConfigReq -> set_translatorname(Test);
    Test = "HLR_Number123";
    IwfMapToS6aConfigObj.set_hlrnumber(Test);
    IWFCfgResp IWFCfgRespObj;

    printf("MapS6aConfig :\n %s",IwfMapToS6aConfigObj.DebugString().c_str());
    m_IwfdbInterface->Fill_IWFMapS6aConfig_protobuff(&IwfMapToS6aConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("MapS6aConfig :\n %s",IwfMapToS6aConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestIwfS6aMapConfigSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    string Test = "s6a-MAP";
    IwfS6aToMapConfig IwfS6aToMapConfigObj;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pIwfTranslatorConfigReq = IwfS6aToMapConfigObj.mutable_translatorinfo();
    pIwfTranslatorConfigReq -> set_translatorname(Test);
    //Test = "15243152";
    //IwfS6aToMapConfigObj.set_sgsnnumber(Test);
    IWFCfgResp IWFCfgRespObj;

    printf("S6aMapConfig :\n %s",IwfS6aToMapConfigObj.DebugString().c_str());
    m_IwfdbInterface->Fill_IWFS6aMapConfig_protobuff(&IwfS6aToMapConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("S6aMapConfig :\n %s",IwfS6aToMapConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;
}
#if 0
DbStatus_e CMAPIIwfCMgr::TestCapRoIdpConfigSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    string Test = "CAP-Ro";
    IwfCapToRoConfig IwfCapToRoConfigObj;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pIwfTranslatorConfigReq = IwfCapToRoConfigObj.mutable_translatorinfo();
    pIwfTranslatorConfigReq -> set_translatorname(Test);
    IWFCfgResp IWFCfgRespObj;

    printf("S6aMapConfig :\n %s",IwfCapToRoConfigObj.DebugString().c_str());
    m_IwfdbInterface->Fill_IWFCapRoConfig_protobuff(&IwfCapToRoConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("S6aMapConfig :\n %s",IwfCapToRoConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;
}
#endif
DbStatus_e CMAPIIwfCMgr::TestCapRoIdpConfigSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    string Test = "CAP-Ro";
    IwfCapToRoConfig IwfCapToRoConfigObj;
    CapRoIdpConfig *pCapRoIdpConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pCapRoIdpConfigReq = IwfCapToRoConfigObj.mutable_caproidpinfo();
    pIwfTranslatorConfigReq = IwfCapToRoConfigObj.mutable_translatorinfo();
    pIwfTranslatorConfigReq -> set_translatorname(Test);
    IWFCfgResp IWFCfgRespObj;

    printf("S6aMapConfig :\n %s",IwfCapToRoConfigObj.DebugString().c_str());
    m_IwfdbInterface->Fill_CapRoIdpConfig_protobuff(&IwfCapToRoConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("S6aMapConfig :\n %s",IwfCapToRoConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;
}

DbStatus_e CMAPIIwfCMgr::TestCapRoIdpSmsConfigSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    string Test = "CAP-Ro";
    IwfCapToRoConfig IwfCapToRoConfigObj;
    CapRoIdpSmsConfig *pCapRoIdpSmsConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pCapRoIdpSmsConfigReq = IwfCapToRoConfigObj.mutable_caproidpsmsinfo();
    pIwfTranslatorConfigReq = IwfCapToRoConfigObj.mutable_translatorinfo();
    pIwfTranslatorConfigReq -> set_translatorname(Test);


    IWFCfgResp IWFCfgRespObj;

    printf("S6aMapConfig :\n %s",IwfCapToRoConfigObj.DebugString().c_str());
    m_IwfdbInterface->Fill_CapRoIdpSmsConfig_protobuff(&IwfCapToRoConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("S6aMapConfig :\n %s",IwfCapToRoConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;

}


DbStatus_e CMAPIIwfCMgr::TestIwfS6aMapAddrAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfS6aToMapConfig IwfS6aToMapConfigObj;
    SgsnAddresses *pSgsnAddressesReq = NULL;
    pSgsnAddressesReq = IwfS6aToMapConfigObj.add_sgsnaddress();

    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pIwfTranslatorConfigReq = IwfS6aToMapConfigObj.mutable_translatorinfo();

    string TestVariable="s6a-MAP";
    pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    TestVariable="OriginHost";
    pSgsnAddressesReq->set_orginhost(TestVariable);
    TestVariable="172.16.12.14";
    pSgsnAddressesReq->set_ipaddress(TestVariable);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    for(int i=0;i<IwfS6aToMapConfigObj.sgsnaddress_size();i++)
    {
        m_IwfdbInterface->sql_IWFS6aMapSgsnAddrMap_Create_Add_Query(&IwfS6aToMapConfigObj,sStatement,i);
    }
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}


DbStatus_e CMAPIIwfCMgr::TestIwfS6aMapAddrSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    IwfS6aToMapConfig IwfS6aToMapConfigObj;
    SgsnAddresses *pSgsnAddressesReq = NULL;
    pSgsnAddressesReq = IwfS6aToMapConfigObj.add_sgsnaddress();

   // IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
   // pIwfTranslatorConfigReq = IwfS6aToMapConfigObj.mutable_translatorinfo();

    string TestVariable="s6a-MAP";
    //pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    TestVariable="OriginHost";
    pSgsnAddressesReq->set_orginhost(TestVariable);
    TestVariable="172.16.12.14";
    pSgsnAddressesReq->set_ipaddress(TestVariable);
    IWFCfgResp IWFCfgRespObj;

    printf("S6aMapAddr :\n %s",IwfS6aToMapConfigObj.DebugString().c_str());
    for(int i=0;i < IwfS6aToMapConfigObj.sgsnaddress_size();i++)
    {
        m_IwfdbInterface->Fill_IWFS6aMapSgsnAddrMap_protobuff(&IwfS6aToMapConfigObj,&IWFCfgRespObj,i);
    }

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("S6aMapAddr :\n %s",IwfS6aToMapConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;

}

DbStatus_e CMAPIIwfCMgr::TestIwfS6aMapAddrSelectAll()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    IwfS6aToMapConfig IwfS6aToMapConfigObj;
    SgsnAddresses *pSgsnAddressesReq = NULL;
    pSgsnAddressesReq = IwfS6aToMapConfigObj.add_sgsnaddress();

   // IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
   // pIwfTranslatorConfigReq = IwfS6aToMapConfigObj.mutable_translatorinfo();

    string TestVariable="s6a-MAP";
    //pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    TestVariable="OriginHost";
    pSgsnAddressesReq->set_orginhost(TestVariable);
    TestVariable="172.16.12.14";
    pSgsnAddressesReq->set_ipaddress(TestVariable);
    IWFCfgResp IWFCfgRespObj;

    printf("S6aMapAddr :\n %s",IwfS6aToMapConfigObj.DebugString().c_str());
    m_IwfdbInterface->Fill_IWFS6aMapSgsnAddrMap_protobuff(&IwfS6aToMapConfigObj,&IWFCfgRespObj,-1);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("S6aMapAddr :\n %s",IwfS6aToMapConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;

}


DbStatus_e CMAPIIwfCMgr::TestExtServiceSelectAll()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    CapRoIdpConfig CapRoIdpConfigObj;
    //ExtTeleServiceConfig *pExtTeleServiceConfigReq = NULL;
    //pExtTeleServiceConfigReq = CapRoIdpConfigObj.add_extteleinfo();

   // IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
   // pIwfTranslatorConfigReq = IwfS6aToMapConfigObj.mutable_translatorinfo();

    //string TestVariable="s6a-MAP";
    //pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    IWFCfgResp IWFCfgRespObj;

    printf("ExtService :\n %s",CapRoIdpConfigObj.DebugString().c_str());
    //for(int i=0;i < CapRoIdpConfigObj.extteleinfo_size();i++)
   // {
        m_IwfdbInterface->Fill_ExtTeleserviceToServiceIdMap_Config_protobuff(&CapRoIdpConfigObj,&IWFCfgRespObj,-1);
   // }

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("ExtService :\n %s",CapRoIdpConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;

}

DbStatus_e CMAPIIwfCMgr::TestExtBearerServiceSelectAll()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    CapRoIdpConfig CapRoIdpConfigObj;
    //ExtBearerServiceConfig *pExtBearerServiceConfigReq = NULL;
    //pExtBearerServiceConfigReq = CapRoIdpConfigObj.add_extbearerinfo();

   // IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
   // pIwfTranslatorConfigReq = IwfS6aToMapConfigObj.mutable_translatorinfo();

    //string TestVariable="s6a-MAP";
    //pIwfTranslatorConfigReq->set_translatorname(TestVariable);
    IWFCfgResp IWFCfgRespObj;

    printf("ExtService :\n %s",CapRoIdpConfigObj.DebugString().c_str());
    //for(int i=0;i < CapRoIdpConfigObj.extteleinfo_size();i++)
   // {
        m_IwfdbInterface->Fill_ExtBearerserviceToServiceIdMap_Config_protobuff(&CapRoIdpConfigObj,&IWFCfgRespObj,-1);
   // }

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("ExtService :\n %s",CapRoIdpConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;

}
DbStatus_e CMAPIIwfCMgr::TestExtServiceSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    CapRoIdpConfig CapRoIdpConfigObj;
    ExtTeleServiceConfig *pExtTeleServiceConfigReq = NULL;
    pExtTeleServiceConfigReq = CapRoIdpConfigObj.add_extteleinfo();

    pExtTeleServiceConfigReq->set_extteleservicecode(10);
    IWFCfgResp IWFCfgRespObj;

    printf("ExtService :\n %s",CapRoIdpConfigObj.DebugString().c_str());
    for(int i=0;i < CapRoIdpConfigObj.extteleinfo_size();i++)
    {
        m_IwfdbInterface->Fill_ExtTeleserviceToServiceIdMap_Config_protobuff(&CapRoIdpConfigObj,&IWFCfgRespObj,i);
    }

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("ExtService :\n %s",CapRoIdpConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;

}

DbStatus_e CMAPIIwfCMgr::TestExtBearerServiceSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    CapRoIdpConfig CapRoIdpConfigObj;
    ExtBearerServiceConfig *pExtBearerServiceConfigReq = NULL;
    pExtBearerServiceConfigReq = CapRoIdpConfigObj.add_extbearerinfo();

    pExtBearerServiceConfigReq->set_extbearerservicecode(1);
    IWFCfgResp IWFCfgRespObj;

    printf("ExtService :\n %s",CapRoIdpConfigObj.DebugString().c_str());
    for(int i=0;i < CapRoIdpConfigObj.extbearerinfo_size();i++)
    {
        m_IwfdbInterface->Fill_ExtBearerserviceToServiceIdMap_Config_protobuff(&CapRoIdpConfigObj,&IWFCfgRespObj,i);
    }

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("ExtService :\n %s",CapRoIdpConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;

}

DbStatus_e CMAPIIwfCMgr::TestIwfTimerAdd()
{
    DbStatus_e iReturn = IWF_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfTimerConfig IwfTimerConfigObj;

    string TestVariable="Timer1";
    IwfTimerConfigObj.set_timername(TestVariable);
    TestVariable="10";
    IwfTimerConfigObj.set_timervalue(10);

    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }

    m_IwfdbInterface->sql_IWFTimer_Create_Add_Query(&IwfTimerConfigObj,sStatement);
    if((iReturn = m_IwfdbInterface->m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_LBALGO_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        DLOG_ERROR("Query Execution Successfull %s",sStatement);
    }
    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    return IWF_DB_SUCCESS;
}
#if 1
DbStatus_e CMAPIIwfCMgr::TestIwfTimerSelect()
{
    if (DRE_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        return 0;
    }
    IwfTimerConfig IwfTimerConfigObj;
    string TestVariable="Timer1";
    IwfTimerConfigObj.set_timername(TestVariable);
    TestVariable="10";
    IwfTimerConfigObj.set_timervalue(10);
    IWFCfgResp IWFCfgRespObj;

    printf("S6aMapConfig :\n %s",IwfTimerConfigObj.DebugString().c_str());
    m_IwfdbInterface->Fill_IWFTimer_protobuff(&IwfTimerConfigObj,&IWFCfgRespObj);

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    printf("S6aMapConfig :\n %s",IwfTimerConfigObj.DebugString().c_str());
    return IWF_DB_SUCCESS;
}
#endif
