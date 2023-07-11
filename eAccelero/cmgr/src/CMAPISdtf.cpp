/*******************************-*-CPP-*-************************************
 *                                                                          *
 *          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
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

/*
 * FILE:   CMAPISdtf.cpp
 * Author: Hemanth
 *
 * Created on Nov 25, 2014, 08:32 PM
 */


#include <CMAPICMgr.h>
#include <CMAPICommon.h>
#include <MysqlInterfacePB.h>

extern std::map<int,std::string> errorMap;

int CMAPICMgr::GetSDTFConfig(SDTFReq *req, SDTFResp *resp)
{
    DbStatus_e iReturn = DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(!req->has_requestid())
    {
        resp->set_responseid(CMAPI_ERROR);
        resp->set_requestid(INVALID_REQID);
        DLOG_ERROR("Request id is not set ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to get database connection Object");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_Sdtf_Config_Reqs(resp, iReturn);
        return 0;
    }

    switch(req->requestid())
    {
        case GET_SDTF_CONFIG:
            iReturn = m_dbInterface->mysql_Sdtf_Get_SDTFRules_Config_Reqs(req, resp);
            break;
        case GET_SDTF_ENABLE_STATUS:
            iReturn = m_dbInterface->mysql_Sdtf_Get_SDTF_EnableStatus_Config_Req(resp);
            break;
        default:
            DLOG_ERROR("INVALID_REQID :<%d>", req->requestid());
            break;
    }

    // Release current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    resp->set_requestid(req->requestid());

    if(iReturn == DRE_DB_SUCCESS)
    {
        resp->set_responseid(CMAPI_SUCCESS);
    }
    else if(iReturn == GET_SDTF_RULES_ERR_NO_DATA_PRESENT)
    {
        resp->set_responseid(CMAPI_SUCCESS);
    }
    else if(iReturn == GET_SDTF_FEATURE_STATUS_ERR_NO_DATA_PRESENT)
    {
        resp->set_responseid(CMAPI_SUCCESS);
    }
    else
    {
        resp->set_responseid(CMAPI_ERROR);
    }

    DLOG_DEBUG("SDTFResp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("SDTFReq = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::SetSDTFConfig(SDTFReq *req, SDTFResp *resp)
{
    DbStatus_e iReturn = DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(!req->has_requestid())
    {
        resp->set_responseid(CMAPI_ERROR);
        resp->set_requestid(INVALID_REQID);
        DLOG_ERROR("Request id is not set.");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to get database connection Object");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_Sdtf_Config_Reqs(resp, iReturn);
        return 0;
    }

    //Aquire Table lock before doing any operation in Mysql
    if ((iReturn = m_LockManager->CMgr_GetLock(req->requestid())) != DRE_DB_SUCCESS)
    {
        if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
        {
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
            m_dbInterface->mysql_set_error_for_Sdtf_Config_Reqs(resp, GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
        }
        else
        {
            DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
            m_dbInterface->m_dbHandle.mysql_release_current_connection();
            resp->set_responseid(CMAPI_ERROR);
            m_dbInterface->mysql_set_error_for_Sdtf_Config_Reqs(resp, GET_LOCK_ERR_RESOURSE_BUSY);
            return 0;
        }
    }

    switch(req->requestid())
    {
        case SET_SDTF_RULE_STATUS:
            iReturn = m_dbInterface->mysql_SDTF_Set_SDTFRule_Status_Config_Req(req, resp);
            break;
        case ADD_SDTF_CONFIG:
            iReturn = m_dbInterface->mysql_SDTF_Add_SDTFRule_Config_Req(req, resp);
            break;
        case MOD_SDTF_CONFIG:
            iReturn = m_dbInterface->mysql_SDTF_Mod_SDTFRule_Config_Req(req, resp);
            break;
        case DEL_SDTF_CONFIG:
            iReturn = m_dbInterface->mysql_SDTF_Del_SDTFRule_Config_Req(req, resp);
            break;
        case SET_SDTF_ENABLE_STATUS:
            iReturn = m_dbInterface->mysql_SDTF_Set_SDTF_EnableStatus_Config_Req(req, resp);
            break;
        default:
            DLOG_ERROR("INVALID_REQID :<%d>", req->requestid());
            break;
    }

    resp->set_requestid(req->requestid());

    if(iReturn != DRE_DB_SUCCESS)
    {
        resp->set_responseid(CMAPI_ERROR);
        m_LockManager->CMgr_ReleaseLock(req->requestid());
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
    }
    else
    {
        SDTFReq *lReq = new SDTFReq();
        lReq->CopyFrom(*req);

        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId,req->requestid(),
                CMAPI_SUCCESS, m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
        DLOG_DEBUG("Calling HandleSDTFConfig() in DRE.");
        m_diaMgtCallerObj->HandleSDTFConfig(*req, (void*)cookie);
        resp->set_responseid(CMAPI_SUCCESS);
    }

    DLOG_DEBUG("SDTFResp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("SDTFReq = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::FetchSDTFConfig(SDTFReq *req, SDTFResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    DbStatus_e iReturn = DRE_DB_SUCCESS;

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to get database connection Object");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_Sdtf_Config_Reqs(resp, iReturn);
        return 0;
    }

    SDTFReq lReq;
    iReturn = m_dbInterface->mysql_Sdtf_Get_SDTFRules_Config_Reqs(&lReq, resp);

    if(iReturn == DRE_DB_SUCCESS)
    {
        resp->set_responseid(CMAPI_SUCCESS);

        iReturn = m_dbInterface->mysql_Sdtf_Get_SDTF_EnableStatus_Config_Req(resp);
        if(iReturn == DRE_DB_SUCCESS)
        {
            resp->set_responseid(CMAPI_SUCCESS);
        }
        else if(iReturn == GET_SDTF_FEATURE_STATUS_ERR_NO_DATA_PRESENT)
        {
            resp->set_responseid(CMAPI_SUCCESS);
        }
        else
        {
            resp->set_responseid(CMAPI_ERROR);
        }
    }
    else if(iReturn == GET_SDTF_RULES_ERR_NO_DATA_PRESENT)
    {
        resp->set_responseid(CMAPI_SUCCESS);
    }
    else
    {
        resp->set_responseid(CMAPI_ERROR);
    }

    // Release current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("SDTFResp = %s", resp->DebugString().c_str());
    DLOG_DEBUG("SDTFReq = %s", req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::HandleSDTFConfigRespCbk(SDTFResp *resp)
{
    int retVal = 0;
    SDTFResp errResp;
    DLOG_NONE(">HandleSDTFConfigRespCbk: ");

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_NONE("Response From Instance :%d", MeSS::Handle().m_src.instance);
		return 0;
	}

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    int iOperID = cookie->iReqID;
    void* conn = cookie->con;
    SDTFReq *req = (SDTFReq*)cookie->req;

    if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
    {
        if(resp == NULL)
        {
            resp = &errResp;
        }
        DLOG_WARNING("MESS Responded with state : MESS_STATUS_NOT_READY ");

        retVal = CMAPI_SRVERROR;
        resp->set_responseid(CMAPI_SRVERROR);
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
            if (resp->responseid() == CMAPI_SUCCESS)
            {
                DLOG_NONE(">HandleSDTFConfigRespCbk: DRE operation - Successful. Committing the database ");
    		    m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                //commit database
                m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
#if DRE
                m_standbydiaMgtCallerObj->HandleSDTFConfig(*req, (void*)NULL);
#else
                m_standbyiwfdiaMgtCallerObj->HandleSDTFConfig(*req, (void*)NULL);
#endif
            }
            else
            {
                //rollback database, since the DRE configuration failed
    		    m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
            }
        }
        else
        {
            if ((resp == NULL) || (MeSS::Handle().m_state == MESS_STATUS_TIMEOUT))
            {
                retVal = CMAPI_SRVERROR;
                errResp.set_responseid(retVal);
                resp = &errResp;
            }

            m_LockManager->CMgr_ReleaseLock(iOperID,conn);
            m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
        }
    }

    m_configResultsHandler[cookie->comp]->SendSDTFConfigResult(*resp);

    deleteCookie(cookie,ADD_SDTF_CONFIG);
    return retVal;
}

int CMAPICMgr::SendSDTFConfigResultRespCbk(CMAPIRes *Resp)
{
    return 0;
}
