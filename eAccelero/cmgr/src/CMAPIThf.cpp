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


#include <CMAPICMgr.h>
#include <CMAPICommon.h>
#include <MysqlInterfacePB.h>

extern std::map<int,std::string> errorMap;

int CMAPICMgr::GetTHFConfig(THFReq *Req, THFResp *Resp)
{
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(!Req->has_requestid())
    {
        Resp->set_responseid(CMAPI_ERROR);  
        Resp->set_requestid(INVALID_REQID);
        DLOG_ERROR("Request id is not set ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;       
    }

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to get database connection Object");
        Resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_Thf_Config_Reqs(Resp,iReturn);
        return 0;
    }
    switch(Req->requestid())
    {
        case GET_THF_ENABLE:
            iReturn = m_dbInterface->mysql_Thf_Enable_Get_Config_Reqs(Req,Resp);
            break;
        case GET_THF_REALM:
            iReturn = m_dbInterface->mysql_Thf_Realm_Get_Config_Reqs(Req,Resp);
            break;
        case GET_THF_VHOST:
            iReturn = m_dbInterface->mysql_Thf_VHost_Get_Config_Reqs(Req,Resp);
            break;
        default:
            DLOG_ERROR("INVALID_REQID");
            break;
    }

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    Resp->set_requestid(Req->requestid());

    if(iReturn == DRE_DB_SUCCESS)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_THF_ERR_NO_DATA_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_THF_VHOST_ERR_NO_DATA_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_THF_REALM_ERR_NO_DATA_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else
        Resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("THFResp = %s",Resp->DebugString().c_str());
    DLOG_DEBUG("THFReq = %s",Req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::SetTHFConfig(THFReq *Req, THFResp *Resp)
{
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(!Req->has_requestid())
    {
        Resp->set_responseid(CMAPI_ERROR);  
        Resp->set_requestid(INVALID_REQID);
        DLOG_ERROR("Request id is not set ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;       
    }

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to get database connection Object");
        Resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_Thf_Config_Reqs(Resp,iReturn);
        return 0;
    }

    //Aquire Table lock before doing any operation in Mysql
    if ((iReturn = m_LockManager->CMgr_GetLock(Req->requestid())) != DRE_DB_SUCCESS)
    {
	    if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
	    {
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
		    m_dbInterface->mysql_set_error_for_Thf_Config_Reqs(Resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
	    }
	    else
	    {
		    DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
		    Resp->set_responseid(CMAPI_ERROR);
		    m_dbInterface->mysql_set_error_for_Thf_Config_Reqs(Resp,GET_LOCK_ERR_RESOURSE_BUSY);
		    return 0;
	    }
    }

    switch(Req->requestid())
    {
	    case SET_THF_ENABLE:
		    iReturn = m_dbInterface->mysql_Thf_Enable_Set_Config_Reqs(Req,Resp);
		    break;
	    case SET_THF_DEF_BEHAV:
		    iReturn = m_dbInterface->mysql_Thf_defaultBehaviour_Set_Config_Reqs(Req,Resp);
		    break;
	    case ADD_THF_REALM:
		    iReturn = m_dbInterface->mysql_Thf_Realm_Add_Config_Reqs(Req,Resp);
		    break;
	    case ADD_THF_VHOST:
		    iReturn = m_dbInterface->mysql_Thf_vhost_Add_Config_Reqs(Req,Resp);
		    break;
	    case DEL_THF_REALM:
		    iReturn = m_dbInterface->mysql_Thf_Realm_Del_Config_Reqs(Req,Resp);
		    break;
	    case DEL_THF_VHOST:
		    iReturn = m_dbInterface->mysql_Thf_Vhost_Del_Config_Reqs(Req,Resp);
		    break;
	    case SET_THF_ENABLE_DEF_BEHAV:
		    {
			    THFReq localTHFReq;
			    localTHFReq.set_enablethf(Req->enablethf());
			    iReturn = m_dbInterface->mysql_Thf_Enable_Set_Config_Reqs(&localTHFReq,Resp);
		    }
		    if (iReturn == DRE_DB_SUCCESS)
		    {
			    THFReq localTHFReq;
			    localTHFReq.set_defaultexpose(Req->defaultexpose());
			    iReturn = m_dbInterface->mysql_Thf_defaultBehaviour_Set_Config_Reqs(&localTHFReq,Resp);
		    }
		    break; 
	    default:
		    DLOG_ERROR("INVALID_REQID");
		    break;
    }

    Resp->set_requestid(Req->requestid());

    if(iReturn != DRE_DB_SUCCESS)
    {

        Resp->set_responseid(CMAPI_ERROR);
    	m_LockManager->CMgr_ReleaseLock(Req->requestid());
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());

    }
    else        
    {
        THFReq *lReq = new THFReq();
        lReq->CopyFrom(*Req);
        
        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId,Req->requestid(),
                CMAPI_SUCCESS, m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
        m_diaMgtCallerObj->HandleTHFConfig(*Req, (void*)cookie);
        Resp->set_responseid(CMAPI_SUCCESS);
    }

    DLOG_DEBUG("THFResp = %s",Resp->DebugString().c_str());
    DLOG_DEBUG("THFReq = %s",Req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::FetchTHFConfig(THFReq *Req,THFResp *Resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to get database connection Object");
        Resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_Thf_Config_Reqs(Resp,iReturn);
        return 0;
    }

    THFReq lReq;

    iReturn = m_dbInterface->mysql_Thf_Realm_Get_Config_Reqs(&lReq,Resp);


    if(iReturn == DRE_DB_SUCCESS)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_THF_ERR_NO_DATA_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_THF_REALM_ERR_NO_DATA_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_THF_VHOST_ERR_NO_DATA_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else
        Resp->set_responseid(CMAPI_ERROR);

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("THFResp = %s",Resp->DebugString().c_str());
    DLOG_DEBUG("THFReq = %s",Req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::HandleTHFConfigRespCbk(THFResp *resp)
{
    int retVal = 0;
    std::string StrVal;
    THFResp ErrorResponse;
    DLOG_NONE(">HandleTHFConfigRespCbk: ");

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_NONE("Response From Instance :%d", MeSS::Handle().m_src.instance);
		return 0;
	}

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    int iOperID = cookie->iReqID;
    void* conn = cookie->con;
    THFReq *req = (THFReq*)cookie->req;

    if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
    {
        if(resp == NULL)
        {
            resp = &ErrorResponse;
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

                DLOG_NONE(">HandleTHFConfigRespCbk: DRE operation - Successful. Committing the database ");
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                //commit database
                m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
#if DRE
                m_standbydiaMgtCallerObj->HandleTHFConfig(*req, (void*)NULL);
#else
                m_standbyiwfdiaMgtCallerObj->HandleTHFConfig(*req, (void*)NULL);
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
            if ((resp == NULL) || (MeSS::Handle().m_state == MESS_STATUS_TIMEOUT))
            {
                retVal = CMAPI_SRVERROR;
                ErrorResponse.set_responseid(retVal);
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
    m_configResultsHandler[cookie->comp]->SendTHFConfigResult(*resp);

    deleteCookie(cookie,ADD_THF_REALM);	
    return retVal;
}

int CMAPICMgr::SendTHFConfigResultRespCbk(CMAPIRes *Resp)
{
    return 0;
}
