/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
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
 * *
 * *                                                                          *
 * ****************************************************************************/


#include <CMAPICMgr.h>
#include <CMAPICommon.h>
#include <MysqlInterfacePB.h>

extern std::map<int,std::string> errorMap;

int CMAPICMgr::HandleGetPluginConfigReq(TransformPluginConfigReq *Req, DRECfgResp *Resp)
{
    int iOperID;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(Req->has_operreqid())
        iOperID =  Req->operreqid();
    else
    {
        Resp->set_respcode(CMAPI_ERROR);
        DLOG_ERROR("Request id is not set ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to get database connection Object");
        Resp->set_respcode(CMAPI_ERROR);
        return 0;
    }

    switch(iOperID)
    {
        case GET_TRANSPLUGIN:
            iReturn = m_dbInterface->mysql_TransPlugin_Get_Config_Reqs(Req, Resp);
            break;
        default:
            DLOG_ERROR("INVALID_REQID");
            break;
    }

    if(iReturn == DRE_DB_SUCCESS)
        Resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturn == GET_TRANSFORM_PLUGIN_ERR_NO_DATA_PRESENT)
        Resp->set_respcode(CMAPI_SUCCESS);
    else
        Resp->set_respcode(CMAPI_ERROR);

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("TransformPluginResp = %s",Resp->DebugString().c_str());
    DLOG_DEBUG("TransformPluginReq = %s",Req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::HandleGetDictionaryConfigReq(DictionaryConfigReq *Req,DRECfgResp *Resp)
{
    int iOperID;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(Req->has_operreqid())
        iOperID =  Req->operreqid();
    else
    {
        Resp->set_respcode(CMAPI_ERROR);
        DLOG_ERROR("Request id is not set ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to get database connection Object");
        Resp->set_respcode(CMAPI_ERROR);
        return 0;
    }

    switch(iOperID)
    {
        case GET_DICTIONARIES:
            iReturn = m_dbInterface->mysql_Dictionary_Get_Config_Reqs(Req, Resp);
            break;
        default:
            DLOG_ERROR("INVALID_REQID");
            break;
    }

    if(iReturn == DRE_DB_SUCCESS)
        Resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturn == GET_DICTID_ERR_NO_DATA_PRESENT)
        Resp->set_respcode(CMAPI_SUCCESS);
    else
        Resp->set_respcode(CMAPI_ERROR);

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("DictionaryResp = %s",Resp->DebugString().c_str());
    DLOG_DEBUG("DictionaryReq = %s",Req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::HandleSetPluginConfigReq(TransformPluginConfigReq *Req,DRECfgResp *Resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    int iOperID;
    DbStatus_e iReturn = DRE_DB_FAIL;

    if(Req->has_operreqid())
        iOperID =  Req->operreqid();
    else
    {
        Resp->set_respcode(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        Resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_TransPlugin_Config_Reqs(Resp,iReturn);
        return 0;
    }

    //Aquire Table lock before doing any operation in Mysql
    if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
    {
        if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
        {
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
            m_dbInterface->mysql_set_error_for_TransPlugin_Config_Reqs(Resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
        }
        else
        {
            DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
            m_dbInterface->m_dbHandle.mysql_release_current_connection();
            Resp->set_respcode(CMAPI_ERROR);
            DLOG_DEBUG("GET_LOCK_ERR_RESOURSE_BUSY");
            m_dbInterface->mysql_set_error_for_TransPlugin_Config_Reqs(Resp,GET_LOCK_ERR_RESOURSE_BUSY);
            return 0;
        }
    }

    switch(iOperID)
    {
        case SET_TRANSPLUGIN_STATUS:
            iReturn = m_dbInterface->mysql_TransPlugin_SetStatus_Config_Reqs(Req, Resp);
            break;
        case RELOAD_TRANSPLUGIN:
            iReturn = m_dbInterface->mysql_TransPlugin_Reload_Config_Reqs(Req, Resp);
            break;
        case RELOAD_SDTF:
            iReturn = DRE_DB_SUCCESS;
            break;
        default:
            DLOG_ERROR("INVALID_REQID");
            break;
    }

    if(iReturn != DRE_DB_SUCCESS)
    {
        DLOG_ERROR(" :( Database operation failed :(");

        Resp->set_respcode(CMAPI_ERROR);
        m_LockManager->CMgr_ReleaseLock(iOperID);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
    }
    else
    {
        DLOG_DEBUG(" :) Database operation Successfull :)");
        Resp->set_respcode(CMAPI_SUCCESS);
        TransformPluginConfigReq *lReq = new TransformPluginConfigReq();
        lReq->CopyFrom(*Req);

        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId,iOperID, CMAPI_SUCCESS,
                m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
        m_diaMgtCallerObj->HandlePluginConfig(*Req, (void*)cookie);
    }

    DLOG_DEBUG("TransPlugin resp = %s",Resp->DebugString().c_str());
    DLOG_DEBUG("TransPlugin req = %s",Req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::HandleSetDictionaryConfigReq(DictionaryConfigReq *Req, DRECfgResp *Resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    int iOperID;
    DbStatus_e iReturn = DRE_DB_FAIL;

    if(Req->has_operreqid())
        iOperID =  Req->operreqid();
    else
    {
        Resp->set_respcode(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        Resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_Dictionary_Config_Reqs(Resp,iReturn);
        return 0;
    }

    //Aquire Table lock before doing any operation in Mysql
    if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
    {
        if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
        {
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
            m_dbInterface->mysql_set_error_for_Dictionary_Config_Reqs(Resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
        }
        else
        {
            DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
            m_dbInterface->m_dbHandle.mysql_release_current_connection();
            Resp->set_respcode(CMAPI_ERROR);
            DLOG_DEBUG("GET_LOCK_ERR_RESOURSE_BUSY");
            m_dbInterface->mysql_set_error_for_Dictionary_Config_Reqs(Resp,GET_LOCK_ERR_RESOURSE_BUSY);
            return 0;
        }
    }

    switch(iOperID)
    {
        case SET_DICT_STATUS:
            iReturn = m_dbInterface->mysql_Dictionary_SetStatus_Config_Reqs(Req, Resp);
            break;
        default:
            DLOG_ERROR("INVALID_REQID");
            break;
    }

    if(iReturn != DRE_DB_SUCCESS)
    {
        DLOG_ERROR(" :( Database operation failed :(");

        Resp->set_respcode(CMAPI_ERROR);
        m_LockManager->CMgr_ReleaseLock(iOperID);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
    }
    else
    {
        DLOG_DEBUG(" :) Database operation Successfull :)");
        Resp->set_respcode(CMAPI_SUCCESS);
        DictionaryConfigReq *lReq = new DictionaryConfigReq();
        lReq->CopyFrom(*Req);

        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId,iOperID, CMAPI_SUCCESS,
                m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
        m_diaMgtCallerObj->HandleDictionaryConfig(*Req, (void*)cookie);
    }

    DLOG_DEBUG("Dictionary resp = %s",Resp->DebugString().c_str());
    DLOG_DEBUG("Dictionary req = %s",Req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::FetchPluginConfig(TransformPluginConfigReq *Req,DRECfgResp *Resp)
{
    DbStatus_e iTransPlugins = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG("ConfigFetch req = %s",Req->DebugString().c_str());
    if ((iTransPlugins = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        Resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(Resp,iTransPlugins);
        return 0;
    }
    TransformPluginConfigReq TransPluginConfigReq;
    iTransPlugins = m_dbInterface->mysql_TransPlugin_Get_Config_Reqs(&TransPluginConfigReq,Resp);

    if(iTransPlugins == DRE_DB_SUCCESS)
        Resp->set_respcode(CMAPI_SUCCESS);
    else if(iTransPlugins == GET_TRANSFORM_PLUGIN_ERR_NO_DATA_PRESENT)
        Resp->set_respcode(CMAPI_SUCCESS);

    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("TransformResp = %s",Resp->DebugString().c_str());
    DLOG_DEBUG("TransformReq = %s",Req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::FetchDictionaryConfig(DictionaryConfigReq *Req,DRECfgResp *Resp)
{
    DbStatus_e iReturnDictionaries = DRE_DB_FAIL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG("ConfigFetch req = %s",Req->DebugString().c_str());
    if ((iReturnDictionaries = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        Resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_drecfgResp_Config_Reqs(Resp,iReturnDictionaries);
        return 0;
    }
    DictionaryConfigReq DictConfigReq;
    iReturnDictionaries = m_dbInterface->mysql_Dictionary_Get_Config_Reqs(&DictConfigReq,Resp);

    if(iReturnDictionaries == DRE_DB_SUCCESS)
        Resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturnDictionaries == GET_DICTID_ERR_NO_DATA_PRESENT)
        Resp->set_respcode(CMAPI_SUCCESS);

    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("DictionaryResp = %s",Resp->DebugString().c_str());
    DLOG_DEBUG("DictionaryReq = %s",Req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::HandleDictionaryConfigRespCbk(DRECfgResp* resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    int retVal = 0;
    std::string StrVal;
    DRECfgResp ErrorResponse;

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_NONE("Response From Instance %d", MeSS::Handle().m_src.instance);
        return 0;
    }

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    int iOperID = cookie->iReqID;
    void* conn = cookie->con;
    DictionaryConfigReq *req = (DictionaryConfigReq *) cookie->req;

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
                DLOG_NONE(" > %s : DRE operation - Successful. Committing the database ",__FUNCTION__);
                //commit database
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
#if DRE
                m_standbydiaMgtCallerObj->HandleDictionaryConfig(*req, (void*)NULL);
#else
                m_standbyiwfdiaMgtCallerObj->HandleDictionaryConfig(*req, (void*)NULL);
#endif
            }
            else {
                DLOG_DEBUG(" > %s : CMAPI_FAILED",__FUNCTION__);
                DLOG_DEBUG(" > %s : DRE Response - %s",__FUNCTION__,resp->DebugString().c_str());
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

    deleteCookie(cookie,iOperID);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMgr::HandlePluginConfigRespCbk(DRECfgResp* resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    int retVal = 0;
    std::string StrVal;
    DRECfgResp ErrorResponse;

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_NONE("Response From Instance %d", MeSS::Handle().m_src.instance);
        return 0;
    }

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    int iOperID = cookie->iReqID;
    void* conn = cookie->con;
    TransformPluginConfigReq *req = (TransformPluginConfigReq *) cookie->req;

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
                DLOG_NONE(" > %s : DRE operation - Successful. Committing the database ", __FUNCTION__);
                //commit database
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
#if DRE
                m_standbydiaMgtCallerObj->HandlePluginConfig(*req, (void*)NULL);
#else
                m_standbyiwfdiaMgtCallerObj->HandlePluginConfig(*req, (void*)NULL);
#endif
            }
            else {
                DLOG_DEBUG(" > %s : CMAPI_FAILED",__FUNCTION__);
                DLOG_DEBUG(" > %s : DRE Response - %s",__FUNCTION__,resp->DebugString().c_str());
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

    if(iOperID == SET_TRANSPLUGIN_STATUS)
        deleteCookie(cookie,SET_TRANSPLUGIN_STATUS);
    else if(iOperID == RELOAD_TRANSPLUGIN)
        deleteCookie(cookie,RELOAD_TRANSPLUGIN);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return retVal;
}
