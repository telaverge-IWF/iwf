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

int CMAPIIwfCMgr::HandleGetSigtranMultihomingConfigReqs(IwfSigtransMultihomingConfig *req, IWFCfgResp *resp)
{
     int iOperID;

    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

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
        case GET_SIG_MULTIHOMING:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranMultihoming_Get_Config_Reqs(req,resp);
        break;
    }

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    DLOG_DEBUG("MultiHoming resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("MultiHoming req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);

    return 0;
}

int CMAPIIwfCMgr::HandleGetSctpProfileConfigReqs(IwfSigtranSctpProfilesConfig *req, IWFCfgResp *resp)
{
    int iOperID;

    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

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
        case GET_SCTP_PROFILE:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranSctpProfiles_Get_Config_Reqs(req,resp);
        break;
    }

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    DLOG_DEBUG("SctpProfile resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("SctpProfile req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);

    return 0;
}

int CMAPIIwfCMgr::HandleGetSctpEndPointConfigReqs(IwfSigtranSctpEndPointsConfig *req,IWFCfgResp *resp)
{
    int iOperID;

    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

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
        case GET_SCTP_ENDPOINT:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranSctpEndPoints_Get_Config_Reqs(req,resp);
        break;
    }

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    DLOG_DEBUG("SctpEnd Point resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("SctpEnd Point req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);

    return 0;
}

int CMAPIIwfCMgr::HandleGetAssociationSetConfigReqs(IwfSigtranAssociationSetsConfig *req,IWFCfgResp *resp)
{
    int iOperID;
    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

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
        case GET_ASSOC_SET:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranAssociationSets_Get_Config_Reqs(req,resp);
        break;
    }

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    DLOG_DEBUG("AssociationSets resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("AssociationSets req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);

    return 0;
}

int CMAPIIwfCMgr::HandleSetSigtranMultihomingConfigReqs(IwfSigtransMultihomingConfig *req, IWFCfgResp *resp)
{
    int iOperID;

    DbStatus_e iReturn = IWF_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(req->has_operreqid())
        iOperID =  req->operreqid();
    else
    {
        resp->set_respid(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set");
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
			    m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,GET_IWF_LOCK_ERR_RESOURSE_BUSY);
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
        case SET_SIG_MULTIHOMING:
            break;
        case MOD_SIG_MULTIHOMING:
            break;
        case DEL_SIG_MULTIHOMING:
#if 0
            iReturn = m_IwfdbInterface->mysql_IwfSigtransMultihoming_Del_Config_Reqs(req,resp);
#endif
            break;
        default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_respid(CMAPI_ERROR);
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
        IwfSigtranAssociationsConfig *lReq = new IwfSigtranAssociationsConfig();
        m_IwfdbInterface->IWFSigranAssociationsConfig_Fill_For_MultihomingIP(lReq,req,resp);

        DLOG_INFO("Operation (%d) Sucessfull, Sending to iwf",iOperID);
        DLOG_DEBUG("Data Sending to Iwf = %s",lReq->DebugString().c_str());
        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
                m_IwfdbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
        m_iwfSigtranMethods->HandleAssociationConfigReqs(*lReq, (void*)cookie);
        resp->set_respid(CMAPI_SUCCESS);
    }

    DLOG_DEBUG("MultiHoming resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("MultiHoming req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);

    return 0;
}

int CMAPIIwfCMgr::HandleSetSctpProfileConfigReqs(IwfSigtranSctpProfilesConfig *req, IWFCfgResp *resp)
{
    int iOperID;

	DbStatus_e iReturn = IWF_DB_FAIL;
	DLOG_NONE(" > %s ",__FUNCTION__);

	if(req->has_operreqid())
		iOperID =  req->operreqid();
	else
	{
		resp->set_respid(CMAPI_ERROR);
        	DLOG_ERROR("Operation ID is not Set");
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
			    m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,GET_IWF_LOCK_ERR_RESOURSE_BUSY);
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
        case SET_SCTP_PROFILE:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranSctpProfiles_Add_Config_Reqs(req,resp);
        break;
        case MOD_SCTP_PROFILE:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranSctpProfiles_Mod_Config_Reqs(req,resp);
        break;
        case DEL_SCTP_PROFILE:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranSctpProfiles_Del_Config_Reqs(req,resp);
        break;
		default:
			DLOG_ERROR("Unknown Operation ID");
			resp->set_respid(CMAPI_ERROR);
		break;
	}

	if(iReturn == IWF_DB_SUCCESS)
	{
        m_LockManager->CMgr_ReleaseLock(iOperID);
        DLOG_INFO("Operation (%d) Sucessfull, Not sending to iwf ",iOperID);
		m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
		resp->set_respid(CMAPI_DB_SUCCESS);
	}
	else if(iReturn == IWF_DB_SUCCESS_SEND)
	{
        IwfSigtranAssociationsConfig *lReq = new IwfSigtranAssociationsConfig();
        lReq->set_operreqid(iOperID);
        m_IwfdbInterface->IWFSigranAssociationsConfig_Fill_For_SctpProfile(lReq,req,resp);

        DLOG_INFO("Operation (%d) Sucessfull, Sending to iwf",iOperID);
        DLOG_DEBUG("Data Sending to Iwf = %s",lReq->DebugString().c_str());
		CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
				m_IwfdbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
		m_iwfSigtranMethods->HandleAssociationConfigReqs(*lReq, (void*)cookie);
		resp->set_respid(CMAPI_SUCCESS);
	}
    else
    {
        DLOG_INFO("Operation (%d) Failed",iOperID);
        m_LockManager->CMgr_ReleaseLock(iOperID);
		m_IwfdbInterface->m_dbHandle.mysql_exec_rollback(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
		resp->set_respid(CMAPI_ERROR);

    }

    DLOG_DEBUG("Sctp Profile resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Sctp Profile req = %s",req->DebugString().c_str());

	DLOG_NONE(" < %s ",__FUNCTION__);

    return 0;
}

int CMAPIIwfCMgr::HandleSetSctpEndPointConfigReqs(IwfSigtranSctpEndPointsConfig *req,IWFCfgResp *resp)
{
    int iOperID;
	DbStatus_e iReturn = IWF_DB_FAIL;
	DLOG_NONE(" > %s ",__FUNCTION__);

	if(req->has_operreqid())
		iOperID =  req->operreqid();
	else
	{
		resp->set_respid(CMAPI_ERROR);
        	DLOG_ERROR("Operation ID is not Set");
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
			    m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,GET_IWF_LOCK_ERR_RESOURSE_BUSY);
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
        case SET_SCTP_ENDPOINT:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranSctpEndPoints_Add_Config_Reqs(req,resp);
        break;
        case MOD_SCTP_ENDPOINT:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranSctpEndPoints_Mod_Config_Reqs(req,resp);
        break;
        case DEL_SCTP_ENDPOINT:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranSctpEndPoints_Del_Config_Reqs(req,resp);
        break;
        case DEL_AND_ADD_SIG_MULTIHOMING:
            iReturn = m_IwfdbInterface->mysql_IwfSigtransMultihoming_Del_Config_Reqs(req,resp);
            break;
		default:
			DLOG_ERROR("Unknown Operation ID");
			resp->set_respid(CMAPI_ERROR);
		break;
	}

	if(iReturn == IWF_DB_SUCCESS)
	{
        m_LockManager->CMgr_ReleaseLock(iOperID);
        DLOG_INFO("Operation (%d) Sucessfull, Not sending to iwf ",iOperID);
		m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
		resp->set_respid(CMAPI_DB_SUCCESS);
	}
	else if(iReturn == IWF_DB_SUCCESS_SEND)
	{
        IwfSigtranAssociationsConfig *lReq = new IwfSigtranAssociationsConfig();
        lReq->set_operreqid(iOperID);
        m_IwfdbInterface->IWFSigranAssociationsConfig_Fill_For_SctpEndPoint(lReq,req,resp);

        DLOG_INFO("Operation (%d) Sucessfull, Sending to iwf",iOperID);
        DLOG_DEBUG("Data Sending to Iwf = %s",lReq->DebugString().c_str());
		CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
				m_IwfdbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
		m_iwfSigtranMethods->HandleAssociationConfigReqs(*lReq, (void*)cookie);
		resp->set_respid(CMAPI_SUCCESS);
	}
    else
    {
        DLOG_INFO("Operation (%d) Failed",iOperID);
        m_LockManager->CMgr_ReleaseLock(iOperID);
		m_IwfdbInterface->m_dbHandle.mysql_exec_rollback(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
		resp->set_respid(CMAPI_ERROR);
    }

    DLOG_DEBUG("AssociationSets resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("AssociationSets req = %s",req->DebugString().c_str());

	DLOG_NONE(" < %s ",__FUNCTION__);

    return 0;

}

int CMAPIIwfCMgr::HandleSetAssociationSetConfigReqs(IwfSigtranAssociationSetsConfig *req,IWFCfgResp *resp)
{
    int iOperID;
	DbStatus_e iReturn = IWF_DB_FAIL;
	DLOG_NONE(" > %s ",__FUNCTION__);

	if(req->has_operreqid())
		iOperID =  req->operreqid();
	else
	{
		resp->set_respid(CMAPI_ERROR);
        	DLOG_ERROR("Operation ID is not Set");
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
			    m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,GET_IWF_LOCK_ERR_RESOURSE_BUSY);
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
        case SET_ASSOC_SET:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranAssociationSets_Add_Config_Reqs(req,resp);
        break;
        case MOD_ASSOC_SET:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranAssociationSets_Mod_Config_Reqs(req,resp);
        break;
        case DEL_ASSOC_SET:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranAssociationSets_Del_Config_Reqs(req,resp);
        break;
		default:
			DLOG_ERROR("Unknown Operation ID");
			resp->set_respid(CMAPI_ERROR);
		break;
	}

	if(iReturn != IWF_DB_SUCCESS)
	{
        m_LockManager->CMgr_ReleaseLock(iOperID);
        DLOG_INFO("Operation (%d) Failed, Not sending to iwf ",iOperID);
		m_IwfdbInterface->m_dbHandle.mysql_exec_rollback(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
		resp->set_respid(CMAPI_ERROR);
	}
    else
    {
        IwfSigtranAssociationSetsConfig *lReq = new IwfSigtranAssociationSetsConfig();
        lReq->CopyFrom(*req);
        DLOG_INFO("Operation (%d) Sucessfull, Sending to iwf",iOperID);
        DLOG_DEBUG("Data Sending to Iwf = %s",req->DebugString().c_str());

		CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
				m_IwfdbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
		m_iwfSigtranMethods->HandleAssociationSetConfigReqs(*lReq, (void*)cookie);
		resp->set_respid(CMAPI_SUCCESS);

	}

    DLOG_DEBUG("AssociationSets resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("AssociationSets req = %s",req->DebugString().c_str());

	DLOG_NONE(" < %s ",__FUNCTION__);

    return 0;
}

int CMAPIIwfCMgr::HandleGetAssociationConfigReqs(IwfSigtranAssociationsConfig *req,IWFCfgResp *resp)
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
        case GET_ASSOC:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranAssociations_Get_Config_Reqs(req,resp);
        break;
    }

    m_IwfdbInterface->m_dbHandle.mysql_release_current_connection();
    if(iReturn == IWF_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else
        resp->set_respid(CMAPI_ERROR);

    DLOG_DEBUG("Associations resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Associations req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);

    return 0;
}

int CMAPIIwfCMgr::HandleSetAssociationConfigReqs(IwfSigtranAssociationsConfig *req,IWFCfgResp *resp)
{
    int iOperID;
    DbStatus_e iReturn = IWF_DB_FAIL;
    IwfSigtranAssociationsConfig *lReq = new IwfSigtranAssociationsConfig();

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(req->has_operreqid())
        iOperID =  req->operreqid();
    else
    {
        resp->set_respid(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set");
        DLOG_NONE(" < %s ",__FUNCTION__);
        delete lReq;
        return 0;
    }

    if (IWF_DB_FAIL == m_IwfdbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_respid(CMAPI_ERROR);
        m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        delete lReq;
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
			    m_IwfdbInterface->mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,GET_IWF_LOCK_ERR_RESOURSE_BUSY);
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
        case SET_ASSOC:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranAssociations_Add_Config_Reqs(req,resp);
            break;
        case MOD_ASSOC:
            iReturn = m_IwfdbInterface->mysql_IwfSigtranAssociations_Mod_Config_Reqs(req,resp);
            break;
        case DEL_ASSOC:
            lReq->set_operreqid(iOperID);
            m_IwfdbInterface->IWFSigranAssociationsConfig_Fill_For_Association(lReq,req,resp);

            iReturn = m_IwfdbInterface->mysql_IwfSigtranAssociations_Del_Config_Reqs(req,resp);
            break;
       default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_respid(CMAPI_ERROR);
            break;
    }

    if(iReturn != IWF_DB_SUCCESS)
    {
        m_LockManager->CMgr_ReleaseLock(iOperID);
        DLOG_INFO("Operation (%d) Failed, Not sending to iwf ",iOperID);
        m_IwfdbInterface->m_dbHandle.mysql_exec_rollback(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
        resp->set_respid(CMAPI_ERROR);
        delete lReq;
        lReq = NULL;
    }
    else
    {
        if(iOperID == SET_ASSOC)
        {
            lReq->set_operreqid(iOperID);
            m_IwfdbInterface->IWFSigranAssociationsConfig_Fill_For_Association(lReq,req,resp);

            DLOG_INFO("Operation (%d) Sucessfull, Sending to iwf",iOperID);
            DLOG_DEBUG("Data Sending to Iwf = %s",lReq->DebugString().c_str());

            CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
                    m_IwfdbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
            m_iwfSigtranMethods->HandleAssociationConfigReqs(*lReq, (void*)cookie);
            resp->set_respid(CMAPI_SUCCESS);
        }
        else
        {
            DLOG_INFO("Operation (%d) Sucessfull, Not sending to iwf ",iOperID);
            m_LockManager->CMgr_ReleaseLock(iOperID);
            m_IwfdbInterface->m_dbHandle.mysql_exec_commit(m_IwfdbInterface->m_dbHandle.mysql_get_current_connection());
            resp->set_respid(CMAPI_DB_SUCCESS);
            delete lReq;
            lReq = NULL;
        }
    }
    DLOG_DEBUG("Associations resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Associations req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);

    return 0;
}

int CMAPIIwfCMgr::HandleAssociationConfigReqsRespCbk(IWFCfgResp* resp)
{
    int retVal = 0;
    std::string StrVal;
    IWFCfgResp ErrorResponse;
    DLOG_NONE(">HandleAssociationConfigReqsRespCbk: ");
#if 0
    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_NONE("Response From Instance %d", MeSS::Handle().m_src.instance);
        return 0;
    }
#endif
    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;

    if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY || MeSS::Handle().m_state == MESS_STATUS_BOUNCE)
    {
        if(resp == NULL)
        {
            resp = &ErrorResponse;
        }
        DLOG_WARNING("MESS Responded with state : MESS_STATUS_NOT_READY/MESS_STATUS_BOUNCE ");

        retVal = CMAPI_SRVERROR;
        resp->set_respid(CMAPI_SRVERROR);
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey(iwfErrorMap[CONFIG_COMMON_MESS_NOT_READY]);
        if(cookie == NULL)
        {   
            /*  
             * This will only happen in below scenario
             *
             * In active configuration is sucess, and we commited all data to the database, 
             * after that we send the request to standby,  when response callback come from standby
             * get called, since we commited all the data to the database we can return.
             */
            DLOG_NONE("Cookie is NULL, returning");
            DLOG_NONE("<HandleAssociationConfigReqsRespCbk: ");
            return 0;
        }   
        void* conn = cookie->con;
        int iOperID = cookie->iReqID;

    	m_LockManager->CMgr_ReleaseLock(iOperID,conn);
        m_IwfdbInterface->m_dbHandle.mysql_exec_rollback(conn);
    }
    else
    {
        if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
        {
            if (resp->respid() == CMAPI_SUCCESS)
            {
                if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
                {
                    if((cookie != NULL) && (cookie->activeNodeResponse == CMAPI_ERROR))
                    {
                        void* conn = cookie->con;
                        int iOperID = cookie->iReqID;
                        DLOG_DEBUG(" StandBy IWF operation - Successful. Committing the database ");
                        m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                        m_IwfdbInterface->m_dbHandle.mysql_exec_commit(conn);
                        deleteCookie(cookie,SET_ASSOC);
                    }
                    else
                    {
                        DLOG_DEBUG(" StandBy IWF operation - Successful.");
                    }
                    DLOG_NONE("<HandleAssociationConfigReqsRespCbk: ");
                    return 0;
                }
                else
                {
                    void* conn = cookie->con;
                    int iOperID = cookie->iReqID;
                    IwfSigtranAssociationsConfig *req = (IwfSigtranAssociationsConfig*)cookie->req;
                    DLOG_DEBUG(" Active IWF operation - Successful. Committing the database ");
                    cookie->activeNodeResponse = CMAPI_SUCCESS;
                    //commit database
                    m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(conn);
                    /*
                     * In active configuration is successfull, so we are not storing cookie information
                     * for the response callback called for standby request
                     */
                    m_standbyiwfSigtranMethods->HandleAssociationConfigReqs(*req, (void*)NULL);
                }
            }
            else {
                                
                if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
                {
                    if((cookie != NULL) && (cookie->activeNodeResponse != CMAPI_SUCCESS))
                    {
                        void* conn = cookie->con;
                        int iOperID = cookie->iReqID;
                        //RollBack if standBy also fails
                        DLOG_ERROR("IWF operation - Failure. rollback the database ");
                        m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                        m_IwfdbInterface->m_dbHandle.mysql_exec_rollback(conn);
                        deleteCookie(cookie,SET_ASSOC);
                    }
                    DLOG_NONE("<HandleAssociationConfigReqsRespCbk: ");
                    return 0;
                }
                else
                {
                    IwfSigtranAssociationsConfig *req = (IwfSigtranAssociationsConfig*)cookie->req;
                    cookie->activeNodeResponse = CMAPI_ERROR;
                    DLOG_ERROR("Active IWF operation - Failure. Passing Request to StandByNode");
                    /*
                     * if the configuration in active failes, we are sending the cookie information
                     * to standby This is because, cookie information is required during response
                     * callback
                     */
                    m_standbyiwfSigtranMethods->HandleAssociationConfigReqs(*req, (void*)cookie);
                    m_configResultsHandler[cookie->comp]->SendIWFConfigResult(*resp);
                    DLOG_NONE("<HandleAssociationConfigReqsRespCbk: ");
                    return retVal;
                }
            }

        } else {
            DLOG_DEBUG("Mess Status %d -Failure. rollback the database ",MeSS::Handle().m_state);
            if (resp == NULL || MeSS::Handle().m_state == MESS_STATUS_TIMEOUT)
            {
                if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
                {
                    if(cookie != NULL)
                    {
                        /*
                         * if the cookie is present in the callbacks
                         * it means that in the active it failed, and in the response
                         * callback from standby we need to use cookie and do commit or rollback
                         */
                        void* conn = cookie->con;
                        int iOperID = cookie->iReqID;
                        m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                        m_IwfdbInterface->m_dbHandle.mysql_exec_rollback(conn);
                        deleteCookie(cookie,SET_ASSOC);
                    }
                    DLOG_NONE("<HandleAssociationConfigReqsRespCbk: ");
                    return retVal;
                }

                retVal = CMAPI_SRVERROR;
                ErrorResponse.set_respid(retVal);
                //ErrorResponse.SerializeToString(&StrVal);
                resp = &ErrorResponse;
            } else {
                //resp->SerializeToString(&StrVal);
            }
        }
    }

    m_configResultsHandler[cookie->comp]->SendIWFConfigResult(*resp);

    DLOG_DEBUG("Sending the response to CLI/GUI , resp = %s",resp->DebugString().c_str());
    deleteCookie(cookie,SET_ASSOC);
    DLOG_NONE("<HandleAssociationConfigReqsRespCbk: ");
    return retVal;
}

int CMAPIIwfCMgr::HandleAssociationSetConfigReqsRespCbk(IWFCfgResp* resp)
{
    int retVal = 0;
    std::string StrVal;
    IWFCfgResp ErrorResponse;
    DLOG_NONE(">HandleAssociationSetConfigReqsRespCbk: ");
#if 0
    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_DEBUG("Response From Instance %d", MeSS::Handle().m_src.instance);
        return 0;
    }
#endif
    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY || MeSS::Handle().m_state == MESS_STATUS_BOUNCE)
    {
        if(resp == NULL)
        {
            resp = &ErrorResponse;
        }
        DLOG_WARNING("MESS Responded with state : MESS_STATUS_NOT_READY/MESS_STATUS_BOUNCE ");

        retVal = CMAPI_SRVERROR;
        resp->set_respid(CMAPI_SRVERROR);
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey(iwfErrorMap[CONFIG_COMMON_MESS_NOT_READY]);
        if(cookie == NULL)
        {   
            /*  
             * This will only happen in below scenario
             *
             * In active configuration is sucess, and we commited all data to the database, 
             * after that we send the request to standby,  when response callback come from standby
             * get called, since we commited all the data to the database we can return.
             */
            DLOG_NONE("Cookie is NULL, returning");
            DLOG_DEBUG("<HandleAssociationSetConfigReqsRespCbk: ");
            return 0;
        }   
        void* conn = cookie->con;
        int iOperID = cookie->iReqID;

    	m_LockManager->CMgr_ReleaseLock(iOperID,conn);
        m_IwfdbInterface->m_dbHandle.mysql_exec_rollback(conn);
    }
    else
    {
        if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
        {
            if (resp->respid() == CMAPI_SUCCESS)
            {
                if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
                {
                    if(cookie != NULL && cookie->activeNodeResponse == CMAPI_ERROR)
                    {
                        void* conn = cookie->con;
                        int iOperID = cookie->iReqID;
                        DLOG_DEBUG(" StandBy IWF operation - Successful. Committing the database ");
                        m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                        m_IwfdbInterface->m_dbHandle.mysql_exec_commit(conn);
                        deleteCookie(cookie,DEL_ASSOC_SET);
                    }
                    else
                    {
                        DLOG_DEBUG(" StandBy IWF operation - Successful.");
                    }
                    DLOG_DEBUG("<HandleAssociationSetConfigReqsRespCbk: ");
                    return 0;
                }
                else
                {
                    void* conn = cookie->con;
                    int iOperID = cookie->iReqID;
                    IwfSigtranAssociationSetsConfig *req = (IwfSigtranAssociationSetsConfig*)cookie->req;
                    DLOG_DEBUG(" Active IWF operation - Successful. Committing the database ");
                    cookie->activeNodeResponse = CMAPI_SUCCESS;
                    //commit database
                    m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                    m_IwfdbInterface->m_dbHandle.mysql_exec_commit(conn);
                    /*
                     * In active configuration is successfull, so we are not storing cookie information
                     * for the response callback called for standby request
                     */
                    m_standbyiwfSigtranMethods->HandleAssociationSetConfigReqs(*req, (void*)NULL);
                }
            }
            else {
                                
                if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
                {
                    if(cookie != NULL && cookie->activeNodeResponse != CMAPI_SUCCESS)
                    {
                        void* conn = cookie->con;
                        int iOperID = cookie->iReqID;
                        //RollBack if standBy also fails
                        DLOG_ERROR("IWF operation - Failure. rollback the database ");
                        m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                        m_IwfdbInterface->m_dbHandle.mysql_exec_rollback(conn);
                        deleteCookie(cookie,DEL_ASSOC_SET);
                    }
                    DLOG_DEBUG("<HandleAssociationSetConfigReqsRespCbk: ");
                    return 0;
                }
                else
                {
                    IwfSigtranAssociationSetsConfig *req = (IwfSigtranAssociationSetsConfig*)cookie->req;
                    cookie->activeNodeResponse = CMAPI_ERROR;
                    DLOG_ERROR("Active IWF operation - Failure. Passing Request to StandByNode");
                    /*
                     * if the configuration in active failes, we are sending the cookie information
                     * to standby This is because, cookie information is required during response
                     * callback
                     */
                    m_standbyiwfSigtranMethods->HandleAssociationSetConfigReqs(*req, (void*)cookie);
                    m_configResultsHandler[cookie->comp]->SendIWFConfigResult(*resp);
                    DLOG_DEBUG("<HandleAssociationSetConfigReqsRespCbk: ");
                    return retVal;
                }
            }

        } else {
            DLOG_DEBUG("Mess Status %d -Failure. rollback the database ",MeSS::Handle().m_state);
            if (resp == NULL || MeSS::Handle().m_state == MESS_STATUS_TIMEOUT)
            {
                if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
                {
                    if(cookie != NULL)
                    {
                        /*
                         * if the cookie is present in the callbacks
                         * it means that in the active it failed, and in the response
                         * callback from standby we need to use cookie and do commit or rollback
                         */
                        void* conn = cookie->con;
                        int iOperID = cookie->iReqID;
                        m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                        m_IwfdbInterface->m_dbHandle.mysql_exec_rollback(conn);
                        deleteCookie(cookie,DEL_ASSOC_SET);
                    }
                    DLOG_DEBUG("<HandleAssociationSetConfigReqsRespCbk: ");
                    return retVal;
                }

                retVal = CMAPI_SRVERROR;
                ErrorResponse.set_respid(retVal);
                //ErrorResponse.SerializeToString(&StrVal);
                resp = &ErrorResponse;
            } else {
                //resp->SerializeToString(&StrVal);
            }
        }
    }

    DLOG_DEBUG("Sending the response to CLI/GUI , resp = %s",resp->DebugString().c_str());
    m_configResultsHandler[cookie->comp]->SendIWFConfigResult(*resp);

    deleteCookie(cookie,DEL_ASSOC_SET);
    DLOG_DEBUG("<HandleAssociationSetConfigReqsRespCbk: ");
    return retVal;
}
