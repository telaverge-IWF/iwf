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

int CMAPICMgr::HandleGetStackConfiguration(StackConfigRequest *req, StackConfigResponse *resp)
{
    int iOperID;
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG("Stack req = %s",req->DebugString().c_str());

    if(req->has_requestid())
        iOperID =  req->requestid();
    else
    {
        resp->set_responseid(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }



    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_StackConfigResponse_Config_Reqs(resp,iReturn);
        return 0;
    }

    switch(iOperID)
    {
        case GET_LHCFG:
            iReturn = m_dbInterface->mysql_LocalHost_Get_Config_Reqs(req, resp);
            break;
        case GET_LHTCFG:
            iReturn = m_dbInterface->mysql_LocalHost_Get_Config_Reqs(req, resp);
            break;
        case GET_SCTPCFG:
            iReturn = m_dbInterface->mysql_SCTPConfig_Get_Config_Reqs(req, resp);
            break;
        case GET_CACRLCFG:
            iReturn = m_dbInterface->mysql_TrustedCAConfig_Get_Config_Reqs(req, resp);
            break;
        case GET_GENCFG:
            iReturn = m_dbInterface->mysql_StackGeneralConfig_Get_Config_Reqs(req, resp);
            break;
        case GET_TLSCONFIG:
            iReturn = m_dbInterface->mysql_TLSConfig_Get_Config_Reqs(req, resp);
            break;
        case GET_CIPHERSUITE:
            iReturn = m_dbInterface->mysql_CipherSuiteConfig_Get_Config_Reqs(req, resp);
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
    else if(iReturn == GET_HOST_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_SCTPCONFIG_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_TRUSTEDCA_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_STACKGENERAL_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_TLSCONFIG_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_CIPHERSUITE_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("Stack resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Stack req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;


}


int CMAPICMgr::HandleGetStaticRoutingTableConfigReqs(StaticRoutingTableConfigReq *req,StaticRoutingTableConfigResp *resp)
{
    int iOperID;
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG("StaticRouting req = %s",req->DebugString().c_str());

    if(req->has_requestid())
        iOperID =  req->requestid();
    else
    {
        resp->set_responseid(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }



    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_StaticRoutingTableConfigResp_Config_Reqs(resp,iReturn);
        return 0;
    }

    switch(iOperID)
    {
        case GET_SRCONFIG:
            iReturn = m_dbInterface->mysql_StaticRoutingTableConfig_Get_Config_Reqs(req, resp);
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
    else if(iReturn == GET_HOST_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("StaticRouting resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("StaticRouting req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

int CMAPICMgr::HandleSetStaticRoutingTableConfigReqs(StaticRoutingTableConfigReq *req, StaticRoutingTableConfigResp *resp)
{
	int iOperID;
	DbStatus_e iReturn = DRE_DB_FAIL;
	DLOG_NONE(" > %s ",__FUNCTION__);

	DLOG_DEBUG("StaticRouting req = %s",req->DebugString().c_str());
	if(req->has_requestid())
		iOperID =  req->requestid();
	else
	{
		resp->set_responseid(CMAPI_ERROR);
		DLOG_ERROR("Operation ID is not Set");
		DLOG_NONE(" < %s ",__FUNCTION__);
		return 0;
	}

	if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
	{
		DLOG_CRITICAL("Failed to Get the Database Connection");
		resp->set_responseid(CMAPI_ERROR);
		m_dbInterface->mysql_set_error_for_StaticRoutingTableConfigResp_Config_Reqs(resp,iReturn);
		return 0;
	}

	//Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_StaticRoutingTableConfigResp_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
			DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_responseid(CMAPI_ERROR);
			DLOG_DEBUG("GET_LOCK_ERR_RESOURSE_BUSY");
			m_dbInterface->mysql_set_error_for_StaticRoutingTableConfigResp_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
			return 0;
		}
	}

    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_StaticRoutingTableConfigResp_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            if(iReturn == GET_LOCK_ERR_DB_ERROR)
            {
			    DLOG_ERROR("Database Error!");
			    m_dbInterface->mysql_set_error_for_StaticRoutingTableConfigResp_Config_Reqs(resp,GET_LOCK_ERR_DB_ERROR);
            }
            else if(iReturn == GET_LOCK_ERR_RESOURSE_BUSY)
            {
			    DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
			    m_dbInterface->mysql_set_error_for_StaticRoutingTableConfigResp_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
            }
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_responseid(CMAPI_ERROR);
	        DLOG_NONE(" < %s ",__FUNCTION__);
			return 0;
		}
	}

    switch(iOperID)
	{
		case SET_SRCONFIG:
			iReturn = m_dbInterface->mysql_StaticRouting_Add_Config_Reqs(req,resp);
			break;
		case MOD_SRCONFIG:
			iReturn = m_dbInterface->mysql_StaticRouting_Mod_Config_Reqs(req,resp);
			break;
		case DEL_SRCONFIG:
			iReturn = m_dbInterface->mysql_StaticRouting_Del_Config_Reqs(req,resp);
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
		StaticRoutingTableConfigReq *lReq = new StaticRoutingTableConfigReq();
		lReq->CopyFrom(*req);

		CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
				m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
		m_staticRoutingCallerObj->HandleStaticRoutingTableConfigReqs(*req, (void*)cookie);
		resp->set_responseid(CMAPI_SUCCESS);

	}


	DLOG_DEBUG("StaticRouting resp = %s",resp->DebugString().c_str());
	DLOG_DEBUG("StaticRouting req = %s",req->DebugString().c_str());

	DLOG_NONE(" < %s ",__FUNCTION__);
	return 0;
}
int CMAPICMgr::HandleSetStackConfiguration(StackConfigRequest *req, StackConfigResponse *resp)
{
    int iOperID;
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG("Stack req = %s",req->DebugString().c_str());


    if(req->has_requestid())
        iOperID =  req->requestid();
    else
    {
        resp->set_responseid(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_StackConfigResponse_Config_Reqs(resp,iReturn);
        return 0;
    }
    //Aquire Table lock before doing any operation in Mysql
    if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
    {
	    if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
	    {
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
		    m_dbInterface->mysql_set_error_for_StackConfigResponse_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
	    }
	    else
	    {
			DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
		    resp->set_responseid(CMAPI_ERROR);
		    m_dbInterface->mysql_set_error_for_StackConfigResponse_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
		    return 0;
	    }
    }

    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_StackConfigResponse_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            if(iReturn == GET_LOCK_ERR_DB_ERROR)
            {
			    DLOG_ERROR("Database Error");
			    m_dbInterface->mysql_set_error_for_StackConfigResponse_Config_Reqs(resp,GET_LOCK_ERR_DB_ERROR);
            }
            else if(iReturn == GET_LOCK_ERR_RESOURSE_BUSY)
            {
			    DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
			    m_dbInterface->mysql_set_error_for_StackConfigResponse_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
            }
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_responseid(CMAPI_ERROR);
	        DLOG_NONE(" < %s ",__FUNCTION__);
			return 0;
		}
	}
    switch(iOperID)
    {
	    case SET_LHCFG:
		    iReturn = m_dbInterface->mysql_LocalHost_Set_Config_Reqs(req, resp);
            break;
        case ADD_LHTCFG:
            iReturn = m_dbInterface->mysql_TransportType_Set_Config_Reqs(req, resp);
            break;
        case MOD_LHCFG:
            iReturn = m_dbInterface->mysql_LocalHost_Mod_Config_Reqs(req, resp);
            break;
        case MOD_LHTCFG:
            iReturn = m_dbInterface->mysql_TransportType_Set_Config_Reqs(req, resp);
            break;
        case DEL_LHTCFG:
            iReturn = m_dbInterface->mysql_TransportType_Del_Config_Reqs(req, resp);
            break;
        case SET_SCTPCFG:
            iReturn = m_dbInterface->mysql_SCTPConfig_Set_Config_Reqs(req, resp);
            break;
        case SET_GENCFG:
            iReturn = m_dbInterface->mysql_StackGeneralConfig_Set_Config_Reqs(req, resp);
            break;
        case SET_TLSCONFIG:
            iReturn = m_dbInterface->mysql_TLSConfig_Set_Config_Reqs(req, resp);
            break;
        case ADD_CACRLCFG:
            iReturn = m_dbInterface->mysql_TrustedCAConfig_Add_Config_Reqs(req, resp);
            break;
        case REM_CACRLASSOC:
            iReturn = m_dbInterface->mysql_TrustedCAConfig_RemoveAssoc_Config_Reqs(req, resp);
            break;
        case DEL_CACRLCFG:
            iReturn = m_dbInterface->mysql_TrustedCAConfig_Del_Config_Reqs(req, resp);
            break;
        case MOD_CACRLCFG:
            iReturn = m_dbInterface->mysql_TrustedCAConfig_Mod_Config_Reqs(req, resp);
            break;
        case MOD_CIPHERSUITE:
            iReturn = m_dbInterface->mysql_CipherSuiteConfig_Mod_Config_Reqs(req, resp);
            break;
        case ADD_SECIP:
            iReturn = m_dbInterface->mysql_LocalHostMultihoming_Add_Config_Reqs(req, resp);
            break;
        case MOD_SECIP:
    //        iReturn = m_dbInterface->mysql_LocalHostMultihoming_Mod_Config_Reqs(req, resp);
            break;
        case DEL_LOCALHOST_SECIP:
            iReturn = m_dbInterface->mysql_LocalHostMultihoming_Del_Config_Reqs(req, resp);
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
    	m_LockManager->CMgr_ReleaseLock(iOperID);
        m_dbInterface->m_dbHandle.mysql_exec_commit(m_dbInterface->m_dbHandle.mysql_get_current_connection());
        resp->set_responseid(CMAPI_SUCCESS);

    }

    DLOG_DEBUG("Stack resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Stack req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::HandleGetLocalTransportTags(LocalTransportTagRequest* req, LocalTransportTagResponse* resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    int iOperID;
    DbStatus_e iReturn = DRE_DB_FAIL;

    DLOG_DEBUG("LocalTranportTag req = %s",req->DebugString().c_str());

    if(req->has_requestid())
        iOperID =  req->requestid();
    else
    {
        resp->set_responseid(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }


    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_LocalTransportTagResponse_Config_Reqs(resp,iReturn);
        return 0;
    }

    if(iOperID == GET_LTTAG)
    {
        iReturn = m_dbInterface->mysql_LocalTransportTagConfig_Get_Config_Reqs(req, resp);
    }
    else
    {
        resp->set_responseid(CMAPI_ERROR);
        DLOG_ERROR("Unknown Operation ID");
    }

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    if(iReturn == DRE_DB_SUCCESS ||
            iReturn == GET_LOCAL_TRANSPORTTAG_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("LocalTranportTag req = %s",req->DebugString().c_str());
    DLOG_DEBUG("LocalTransport resp = %s",resp->DebugString().c_str());


    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}


int CMAPICMgr::FetchStaticRoutingTableConfiguration(StaticRoutingTableConfigReq *req, StaticRoutingTableConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    DbStatus_e iReturnLocal = DRE_DB_FAIL;

    DLOG_DEBUG("staticRouting req = %s",req->DebugString().c_str());

    if ((iReturnLocal = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_StaticRoutingTableConfigResp_Config_Reqs(resp,iReturnLocal);
        return 0;
    }

    iReturnLocal = m_dbInterface->mysql_StaticRoutingTableConfig_Get_Config_Reqs(req, resp);
    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();
    if(iReturnLocal == DRE_DB_SUCCESS)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturnLocal == GET_STATIC_ROUTING_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("staticRouting resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("staticRouting req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}


int CMAPICMgr::FetchStackConfiguration(StackConfigRequest *req, StackConfigResponse *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    DbStatus_e iReturnLocal = DRE_DB_FAIL;
    DbStatus_e iReturnSctp = DRE_DB_FAIL;
    DbStatus_e iReturnTCa = DRE_DB_FAIL;
    DbStatus_e iReturnStack = DRE_DB_FAIL;
    DbStatus_e iReturnTls = DRE_DB_FAIL;
    DbStatus_e iReturnCipher = DRE_DB_FAIL;

    DLOG_DEBUG("Stack req = %s",req->DebugString().c_str());

    if ((iReturnLocal = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_StackConfigResponse_Config_Reqs(resp,iReturnLocal);
        return 0;
    }



    iReturnLocal = m_dbInterface->mysql_LocalHost_Get_Config_Reqs(req, resp);
    iReturnSctp = m_dbInterface->mysql_SCTPConfig_Get_Config_Reqs(req, resp);
    iReturnTCa = m_dbInterface->mysql_TrustedCAConfig_Get_Config_Reqs(req, resp);
    iReturnStack = m_dbInterface->mysql_StackGeneralConfig_Get_Config_Reqs(req, resp);
    iReturnTls = m_dbInterface->mysql_TLSConfig_Get_Config_Reqs(req, resp);
    iReturnCipher = m_dbInterface->mysql_CipherSuiteConfig_Get_Config_Reqs(req, resp);
    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();
    if(iReturnLocal == DRE_DB_SUCCESS &&
       iReturnSctp == DRE_DB_SUCCESS &&
       iReturnTCa == DRE_DB_SUCCESS &&
       iReturnStack == DRE_DB_SUCCESS &&
       iReturnTls == DRE_DB_SUCCESS &&
       iReturnCipher == DRE_DB_SUCCESS)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturnLocal == GET_HOST_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturnSctp == GET_SCTPCONFIG_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturnTCa == GET_TRUSTEDCA_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturnStack == GET_STACKGENERAL_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturnTls == GET_TLSCONFIG_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturnCipher == GET_CIPHERSUITE_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("Stack resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Stack req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

// ***********************************************************************
// Component Static Routing Configuration Response Handlers Implementation
// ***********************************************************************
int CMAPICMgr::HandleStaticRoutingTableConfigReqsRespCbk(StaticRoutingTableConfigResp *resp)
{
    int retVal = 0;
    std::string StrVal;
    StaticRoutingTableConfigResp ErrorResponse;
    DLOG_NONE(">HandleSetStaticRoutingTableConfigReqsCbk : ");

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_DEBUG("Response from Instance : %d", MeSS::Handle().m_src.instance);
        return 0;
    }

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
	int iOperID = cookie->iReqID;
    void* conn = cookie->con;
    StaticRoutingTableConfigReq *req = (StaticRoutingTableConfigReq*)cookie->req;

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

                DLOG_DEBUG(">HandleSetStaticRoutingTableConfigReqsCbk: DRE operation - Successful. Committing the database ");
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                //commit database
                m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
                m_standbystaticRoutingCallerObj->HandleStaticRoutingTableConfigReqs(*req, (void*)NULL);
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
    m_staticConfigResultsHandler[cookie->comp]->SendStaticRoutingTableConfigResult(*resp);

    deleteCookie(cookie,SET_SRCONFIG);
    return retVal;
}

int CMAPICMgr::SendStaticRoutingTableConfigResultRespCbk(CMAPIRes *Resp)
{
    return 0;
}

// ***********************************************************************
// Component Tracing Configuration Response Handlers Implementation
// ***********************************************************************
#if 0
int CMAPICMgr::HandleTraceConfigReqsRespCbk(StackConfigResponse *resp)
{
    int retVal = 0;
    std::string StrVal;
    StackConfigResponse ErrorResponse;
    DLOG_NONE(">HandleSetTraceConfigReqsRespCbk : ");

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    void* conn = cookie->con;

    if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
    {
        if (resp->responseid() == CMAPI_SUCCESS)
        {

            DLOG_DEBUG(">HandleSetTraceConfigReqsRespCbk: DRE operation - Successful. Committing the database ");
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
        if (resp == NULL || MeSS::Handle().m_state == MESS_STATUS_TIMEOUT)
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
    //   m_configResultsHandler[cookie->comp]->SendTraceConfigResult(*resp);

    return retVal;
}

int CMAPICMgr::SendTraceConfigResultRespCbk(CMAPIRes *Resp)
{
    return 0;
}
#endif
