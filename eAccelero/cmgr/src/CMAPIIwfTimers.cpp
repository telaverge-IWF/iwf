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

#include <CMAPIIwfCMgr.h>
#include <CMAPICommon.h>
#include <MysqlInterfacePB.h>

extern std::map<int,std::string> iwfErrorMap;

int CMAPIIwfCMgr::HandleGetIwfTimersConfigReqs(IwfTimersConfig *req,IWFCfgResp *resp)
{
    int iOperID;
    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" req %p %s ",req,__FUNCTION__);

    if(req->has_operreqid())
        iOperID =  req->operreqid();
    else
    {
        resp->set_respid(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set\n");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }

    if (IWF_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respid(CMAPI_ERROR);
        m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }
    switch(iOperID)
    {
        case GET_IWF_TIMERS:
        case GET_CAP_PROTO_TIMERS:
            iReturn = m_IwfdbInterface->mysql_IWFTimers_Get_Config_Reqs(req,resp);
            break;
    }
    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    DLOG_DEBUG("Timers resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Timers req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);

    return 0;
}

int CMAPIIwfCMgr::HandleSetIwfTimersConfigReqs(IwfTimersConfig *req,IWFCfgResp *resp)
{
    int iOperID;
    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" req %p %s ",req,__FUNCTION__);

    if(req->has_operreqid())
        iOperID =  req->operreqid();
    else
    {
        resp->set_respid(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set\n");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }

    if (IWF_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respid(CMAPI_ERROR);
        m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,GET_IWF_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            if(iReturn == GET_LOCK_ERR_DB_ERROR)
            {
			    DLOG_ERROR("Database Error!");
			    m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,GET_IWF_LOCK_ERR_DB_ERROR);
            }
            else if(iReturn == GET_LOCK_ERR_RESOURSE_BUSY)
            {
			    DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
			    m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,GET_IWF_LOCK_ERR_RESOURSE_BUSY);
            }
        	m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_respid(CMAPI_ERROR);
	        DLOG_NONE(" < %s ",__FUNCTION__);
			return 0;
		}
	}

    switch(iOperID)
    {
        case SET_IWF_TIMERS:
        case SET_CAP_PROTO_TIMERS:
		iReturn = m_IwfdbInterface->mysql_IwfTimer_Add_Config_Reqs(req,resp);
            break;
        case MOD_IWF_TIMERS:
        case MOD_CAP_PROTO_TIMERS:
		iReturn = m_IwfdbInterface->mysql_IwfTimer_Mod_Config_Reqs(req,resp);
            break;
        case DEL_IWF_TIMERS:
            break;
    }

    if(iReturn != IWF_DB_SUCCESS)
    {
        m_LockManager->CMgr_ReleaseLock(iOperID);
        DLOG_INFO("Operation (%d) Failed",iOperID);
        m_IwfdbInterface->m_dbHandle.mysql_exec_rollback(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
        resp->set_respid(CMAPI_ERROR);
    }
    else
    {

        IwfTimersConfig *lReq = new IwfTimersConfig();
        lReq->CopyFrom(*req);
        DLOG_INFO("Operation (%d) Sucessfull, Sending to iwf",iOperID);
        DLOG_DEBUG("Data Sending to Iwf = %s",lReq->DebugString().c_str());

        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
                m_IwfdbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
        m_iwfSigtranMethods->HandleTimersConfigReqs(*lReq, (void*)cookie);
        resp->set_respid(CMAPI_SUCCESS);
    }

    DLOG_DEBUG("Timers resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Timers req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);

    return 0;
}

int CMAPIIwfCMgr::HandleTimersConfigReqsRespCbk(IWFCfgResp* resp)
{
    int retVal = 0;
    std::string StrVal;
    IWFCfgResp ErrorResponse;
    DLOG_NONE(">HandleTimersConfigReqsRespCbk: ");

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_NONE("Response From Instance %d", MeSS::Handle().m_src.instance);
        return 0;
    }

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    int iOperID = cookie->iReqID;
    void* conn = cookie->con;
    IwfTimersConfig *req = (IwfTimersConfig*)cookie->req;
    if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
    {
        if(resp == NULL)
        {
            resp = &ErrorResponse;
        }
        DLOG_WARNING("MESS Responded with state : MESS_STATUS_NOT_READY ");

        retVal = CMAPI_SRVERROR;
        resp->set_respid(CMAPI_SRVERROR);
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey(iwfErrorMap[CONFIG_COMMON_MESS_NOT_READY]);
        m_LockManager->CMgr_ReleaseLock(iOperID,conn);
        m_IwfdbInterface->m_dbHandle.mysql_exec_rollback(conn);
    }
    else
    {
        if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
        {
            if (resp->respid() == CMAPI_SUCCESS)
            {
                DLOG_DEBUG(" IWF operation - Successful. Committing the database ");
                //commit database
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                m_IwfdbInterface->m_dbHandle.mysql_exec_commit(conn);
                m_standbyiwfSigtranMethods->HandleTimersConfigReqs(*req, (void*)NULL);
            }
            else {
                //resp->SerializeToString(&StrVal);
                //m_CMAPIResponse->Set(StrVal);
                DLOG_DEBUG("IWF operation -Failure. rollback the database ");
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                m_IwfdbInterface->m_dbHandle.mysql_exec_rollback(conn);
            }

        } else {
            DLOG_DEBUG("Mess Status %d -Failure. rollback the database ",MeSS::Handle().m_state);
            if (resp == NULL || MeSS::Handle().m_state == MESS_STATUS_TIMEOUT)
            {
                retVal = CMAPI_SRVERROR;
                ErrorResponse.set_respid(retVal);
                //ErrorResponse.SerializeToString(&StrVal);
                resp = &ErrorResponse;
            } else {
                //resp->SerializeToString(&StrVal);
            }
            //m_CMAPIResponse->Set(StrVal);
            m_LockManager->CMgr_ReleaseLock(iOperID,conn);
            m_IwfdbInterface->m_dbHandle.mysql_exec_rollback(conn);
        }
    }

    m_configResultsHandler[cookie->comp]->SendIWFConfigResult(*resp);

    DLOG_DEBUG("Sending the response to CLI/GUI , resp = %s",resp->DebugString().c_str());
    deleteCookie(cookie,DEL_IWF_TIMERS);

    DLOG_NONE("<HandleTimersConfigReqsRespCbk: ");
    return retVal;
}

