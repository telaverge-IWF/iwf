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

int CMAPICMgr::CMgrGetLBPeerConfigs(LBPeerGroupReq *Req,LBPeerGroupResp *Resp)
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

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to get database connection Object");
        Resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_LBPeerGroupResp_Config_Reqs(Resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }
    switch(Req->requestid())
    {
        case GET_PEERGROUP:
            DLOG_NONE("%s:%d GET_PEERGROUP\n",__FUNCTION__,__LINE__);
            iReturn = m_dbInterface->mysql_PeerGroup_Get_Config_Reqs(Req,Resp);
            break;
        case GET_PEERCONFIG:
            DLOG_NONE("%s:%d GET_PEERCONFIG\n",__FUNCTION__,__LINE__);
            iReturn = m_dbInterface->mysql_PeerConfig_Get_Config_Reqs(Req,Resp);
            break;
#if 0
        case ADD_LBALGO:
            DLOG_NONE("%s:%d ADD_LBALGO\n",__FUNCTION__,__LINE__);
            iReturn = m_dbInterface->mysql_Lbalgo_Add_Config_Reqs(Req,Resp);
            break;
        case MOD_LBALGO:
            DLOG_NONE("%s:%d MOD_LBALGO\n",__FUNCTION__,__LINE__);
            iReturn = m_dbInterface->mysql_Lbalgo_Mod_Config_Reqs(Req,Resp);
            break;
        case DEL_LBALGO:
            DLOG_NONE("%s:%d DELETE_LBALGO\n",__FUNCTION__,__LINE__);
            iReturn = m_dbInterface->mysql_Lbalgo_Delete_Config_Reqs(Req,Resp);
            break;
#endif
        case GET_LBALGO:
            DLOG_NONE("%s:%d GET_LBALGO\n",__FUNCTION__,__LINE__);
            iReturn = m_dbInterface->mysql_Lbalgo_Get_Config_Reqs(Req,Resp);
            break;
        case INVALID_REQID:
            DLOG_NONE("%s:%d INVALID_REQID\n",__FUNCTION__,__LINE__);
            break;
        default:
            DLOG_ERROR("INVALID_REQID");
            break;
    }
    if((Req->requestid() == ADD_LBALGO) ||
            (Req->requestid() == MOD_LBALGO) ||
            (Req->requestid() == DEL_LBALGO))

    {
        m_dbInterface->m_dbHandle.mysql_exec_commit(m_dbInterface->m_dbHandle.mysql_get_current_connection());
    }

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    Resp->set_requestid(Req->requestid());

    if(iReturn == DRE_DB_SUCCESS)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_PEERGROUP_ERR_NO_DATA_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_PEERCONFIG_ERR_NO_DATA_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_LBALGO_ERR_NO_DATA_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_PEERGROUP_ERR_NO_PEERGROUP_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else
        Resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("LBPeerGroupResp resp = %s",Resp->DebugString().c_str());
    DLOG_DEBUG("LBPeerGroupReq req = %s",Req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::CMgrSetLBPeerConfigs(LBPeerGroupReq *Req,LBPeerGroupResp *Resp)
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

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to get database connection Object");
        Resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_LBPeerGroupResp_Config_Reqs(Resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(Req->requestid())) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_LBPeerGroupResp_Config_Reqs(Resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            if(iReturn == GET_LOCK_ERR_DB_ERROR)
            {
			    DLOG_ERROR("Database Error!");
			    m_dbInterface->mysql_set_error_for_LBPeerGroupResp_Config_Reqs(Resp,GET_LOCK_ERR_DB_ERROR);
            }
            else if(iReturn == GET_LOCK_ERR_RESOURSE_BUSY)
            {
			    DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
			    m_dbInterface->mysql_set_error_for_LBPeerGroupResp_Config_Reqs(Resp,GET_LOCK_ERR_RESOURSE_BUSY);
            }
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			Resp->set_responseid(CMAPI_ERROR);
	        DLOG_NONE(" < %s ",__FUNCTION__);
			return 0;
		}
	}

    switch(Req->requestid())
    {
        case ADD_PEERGROUP:
            DLOG_NONE("%s:%d ADD_PEERGROUP\n",__FUNCTION__,__LINE__);
            iReturn = m_dbInterface->mysql_PeerGroup_Add_Config_Reqs(Req,Resp);
            break;
        case MOD_PEERGROUP:
            DLOG_NONE("%s:%d MOD_PEERGROUP\n",__FUNCTION__,__LINE__);
            iReturn = m_dbInterface->mysql_PeerGroup_Mod_Config_Reqs(Req,Resp);
            break;
        case DEL_PEERGROUP:
            DLOG_NONE("%s:%d DEL_PEERGROUP\n",__FUNCTION__,__LINE__);
            iReturn = m_dbInterface->mysql_PeerGroup_Delete_Config_Reqs(Req,Resp);
            break;
        case ADD_PEERCONFIG:
            DLOG_NONE("%s:%d ADD_PEERCONFIG\n",__FUNCTION__,__LINE__);
            iReturn = m_dbInterface->mysql_PeerConfig_Add_Config_Reqs(Req,Resp);
            break;
        case MOD_PEERCONFIG:
            DLOG_NONE("%s:%d MOD_PEERCONFIG\n",__FUNCTION__,__LINE__);
            iReturn = m_dbInterface->mysql_PeerConfig_Mod_Config_Reqs(Req,Resp);
            break;
        case DEL_PEERCONFIG:
            DLOG_NONE("%s:%d DEL_PEERCONFIG\n",__FUNCTION__,__LINE__);
            iReturn = m_dbInterface->mysql_PeerConfig_Delete_Config_Reqs(Req,Resp);
            break;
        case INVALID_REQID:
            DLOG_NONE("%s:%d INVALID_REQID\n",__FUNCTION__,__LINE__);
            break;
        default:
            DLOG_ERROR("INVALID_REQID");
            break;
    }

    Resp->set_requestid(Req->requestid());

    if(iReturn != DRE_DB_SUCCESS)
    {
        m_LockManager->CMgr_ReleaseLock(Req->requestid());
        Resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
    }
    else
    {
        LBPeerGroupReq *lReq = new LBPeerGroupReq();
        lReq->CopyFrom(*Req);

        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, Req->requestid(), CMAPI_SUCCESS,
                m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
        m_erlbfCallerObj->ErlbfSetLBPeerConfigs(*Req, (void*)cookie);
        Resp->set_responseid(CMAPI_SUCCESS);
    }

    DLOG_DEBUG("LBPeerGroupResp resp = %s",Resp->DebugString().c_str());
    DLOG_DEBUG("LBPeerGroupReq req = %s",Req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::FetchErlbfConfiguration(LBPeerGroupReq *Req,LBPeerGroupResp *Resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to get database connection Object");
        Resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_LBPeerGroupResp_Config_Reqs(Resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }
    iReturn = m_dbInterface->mysql_PeerGroup_Get_Config_Reqs(Req,Resp);

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    if(iReturn == DRE_DB_SUCCESS)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_PEERGROUP_ERR_NO_DATA_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_PEERGROUP_ERR_NO_PEERGROUP_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else
        Resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("LBPeerGroupResp resp = %s",Resp->DebugString().c_str());
    DLOG_DEBUG("LBPeerGroupReq req = %s",Req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::FetchDTFConfiguration(DynDictionaryRequest *Req,DynDictionaryResponse *Resp)
{
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to get database connection Object");
        Resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_DynDictionaryResponse_Config_Reqs(Resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }
    iReturn = m_dbInterface->mysql_DictionaryConfig_Get_Config_Reqs(Req,Resp);

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    if(iReturn == DRE_DB_SUCCESS)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn ==  GET_DICTID_ERR_NO_DATA_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else
        Resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("DynDictionaryResponse resp = %s",Resp->DebugString().c_str());
    DLOG_DEBUG("DynDictionaryRequest req = %s",Req->DebugString().c_str());
    return 0;


}

int CMAPICMgr::CMgrDTFConfig(DynDictionaryRequest *Req,DynDictionaryResponse *Resp)
{
    return 0;
}

// Response call back from DRE

int CMAPICMgr::ErlbfSetLBPeerConfigsRespCbk(LBPeerGroupResp *resp)
{
    int retVal = 0;
    std::string StrVal;
    LBPeerGroupResp ErrorResponse;
    DLOG_NONE(">ErlbfSetLBPeerConfigsRespCbk : ");

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_NONE("Response From Instance %d", MeSS::Handle().m_src.instance);
        return 0;
    }

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    int iOperID = cookie->iReqID;
    void* conn = cookie->con;
    LBPeerGroupReq *req = (LBPeerGroupReq*)cookie->req;

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

                DLOG_NONE(">ErlbfSetLBPeerConfigsRespCbk : DRE operation - Successful. Committing the database ");
    		m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                //commit database
                m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
                m_standbyerlbfCallerObj->ErlbfSetLBPeerConfigs(*req, (void*)NULL);
            }
            else {
                //resp->SerializeToString(&StrVal);
                //m_CMAPIResponse->Set(StrVal);
                //rollback database, since the DRE configuration failed
                m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
            }
        } else {
            if ((resp == NULL) || (MeSS::Handle().m_state == MESS_STATUS_TIMEOUT))
            {
                retVal = CMAPI_SRVERROR;
                ErrorResponse.set_responseid(retVal);
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
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
    m_compResultsHandler[cookie->comp]->SendPeerGrpConfigResult(*resp);

    deleteCookie(cookie,ADD_PEERGROUP);
    return retVal;
}

int CMAPICMgr::DreDTFConfigRespCbk(DynDictionaryResponse *resp)
{
    int retVal = 0;
    std::string StrVal;
    DynDictionaryResponse ErrorResponse;
    DLOG_NONE(">DreDTFConfigRespCbk : ");

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    void* conn = cookie->con;
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
    }
    else
    {

        if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
        {
            if (resp->responseid() == CMAPI_SUCCESS)
            {

                DLOG_NONE(">DreDTFConfigRespCbk : DRE operation - Successful. Committing the database ");
                //commit database
                m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
            }
            else {
                //resp->SerializeToString(&StrVal);
                //m_CMAPIResponse->Set(StrVal);
                //rollback database, since the DRE configuration failed
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
            m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
            //m_CMAPIResponse->Set(StrVal);
        }
    }
    m_compResultsHandler[cookie->comp]->SendDTFConfigResult(*resp);

    return retVal;
}

int CMAPICMgr::SendPeerGrpConfigResultRespCbk(CMAPIRes* resp)
{
    return 0;
}

int CMAPICMgr::SendDTFConfigResultRespCbk(CMAPIRes* resp)
{
    return 0;
}

int CMAPICMgr::SendLogConfigResultRespCbk(CMAPIRes* resp)
{
    return 0;
}
