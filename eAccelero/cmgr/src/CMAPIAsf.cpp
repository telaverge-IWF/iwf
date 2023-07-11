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
#include <CMgrDbInterface.h>

extern std::map<int,std::string> errorMap;

int CMAPICMgr::GetASFConfiguration(ASFConfigReq *req, ASFConfigResp *resp)
{
    int iOperID;
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(req->has_requestid())
        iOperID =  req->requestid();
    else
    {
        resp->set_responseid(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }



    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_AsfConfResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    switch(iOperID)
    {
        case GET_ASGRP:
            iReturn =  m_dbInterface->mysql_AsfGroup_Get_Config_Reqs(req,resp);
            break;
        case GET_ASF:
            iReturn = m_dbInterface->mysql_Asf_Get_Config_Reqs(req,resp);
            break;
        default:
            resp->set_responseid(CMAPI_ERROR);
            DLOG_ERROR("Unknown Operation ID");
            break;

    }

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    if(iReturn == DRE_DB_SUCCESS)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_ASFCONFIG_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("Asf resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Asf req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;


}

int CMAPICMgr::SetASFConfiguration(ASFConfigReq* req, ASFConfigResp* resp)
{
    int iOperID;
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(req->has_requestid())
        iOperID =  req->requestid();
    else
    {
        resp->set_responseid(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }


    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_AsfConfResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_AsfConfResp_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            if(iReturn == GET_LOCK_ERR_DB_ERROR)
            {
			    DLOG_ERROR("Database Error!");
			    m_dbInterface->mysql_set_error_for_AsfConfResp_Config_Reqs(resp,GET_LOCK_ERR_DB_ERROR);
            }
            else if(iReturn == GET_LOCK_ERR_RESOURSE_BUSY)
            {
			    DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
			    m_dbInterface->mysql_set_error_for_AsfConfResp_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
            }
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_responseid(CMAPI_ERROR);
	        DLOG_NONE(" < %s ",__FUNCTION__);
			return 0;
		}
	}

    switch(iOperID)
    {
        case SET_ASF:
            iReturn =  m_dbInterface->mysql_Asf_Add_Config_Reqs(req,resp);
            break;
        case ADD_ASGRP:
            iReturn =  m_dbInterface->mysql_AsfGroup_Add_Config_Reqs(req,resp);
            break;
        case MOD_ASGRP:
            iReturn = m_dbInterface->mysql_AsfGroup_Mod_Config_Reqs(req,resp);
            break;
        case DEL_ASGRP:
            iReturn = m_dbInterface->mysql_AsfGroup_Del_Config_Reqs(req,resp);
            break;
        default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_responseid(CMAPI_ERROR);
            break;

    }


    if(iReturn != DRE_DB_SUCCESS)
    {
        m_LockManager->CMgr_ReleaseLock(iOperID);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
        resp->set_responseid(CMAPI_ERROR);
    }
    else
    {
        ASFConfigReq *lReq = new ASFConfigReq();
        lReq->CopyFrom(*req);

        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
                m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
        m_asfCallerObj->SetASFConfiguration(*req, (void*)cookie);

        resp->set_responseid(CMAPI_SUCCESS);
    }

    DLOG_DEBUG("ASF resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("ASF req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;


}

int CMAPICMgr::FetchASFConfiguration(ASFConfigReq *req, ASFConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    DbStatus_e iReturn = DRE_DB_FAIL;


    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        //m_dbInterface->mysql_set_error_for_AsfConfResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }


    iReturn =  m_dbInterface->mysql_AsfGroup_Get_Config_Reqs(req,resp);

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();
    if(iReturn == DRE_DB_SUCCESS)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_ASFCONFIG_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("Asf resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Asf req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

// ***********************************************************************
// Component Logging Configuration Response Handlers Implementation
// ***********************************************************************

int CMAPICMgr::SetASFConfigurationRespCbk(ASFConfigResp *resp)
{
    int retVal = 0;
    std::string StrVal;
    ASFConfigResp ErrorResponse;

    DLOG_NONE(">SetASFConfigurationRespCbk( : ");

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_DEBUG("Response from Instance : %d", MeSS::Handle().m_src.instance);
        return 0;
    }

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    int iOperID = cookie->iReqID;
    void* conn = cookie->con;
    ASFConfigReq *req = (ASFConfigReq*)cookie->req;


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

                DLOG_DEBUG(">SetASFConfigurationRespCbk( : DRE operation - Successful. Committing the database ");
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                //commit database
                m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
                m_standbyasfCallerObj->SetASFConfiguration(*req,(void *) NULL);
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

    m_compResultsHandler[cookie->comp]->SendASFConfigResult(*resp);

    deleteCookie(cookie,SET_ASF);
    return retVal;
}
int CMAPICMgr::SendASFConfigResultRespCbk(CMAPIRes *Resp)
{
    return 0;
}
