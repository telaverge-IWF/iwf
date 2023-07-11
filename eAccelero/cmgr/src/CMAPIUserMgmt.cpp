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


int CMAPICMgr::HandleGetEmailServerReqs(EmailServerReq* req,EmailServerResp* resp)
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

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_EmailServerResp_Config_Reqs(resp,iReturn);
        return 0;
    }

    switch(iOperID)
    {
        case GET_EMAIL_SERVER:
            iReturn =  m_dbInterface->mysql_EmailServer_Get_Config_Reqs(req,resp);
            break;
        default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_responseid(CMAPI_ERROR);
            break;
    }

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    if(iReturn == DRE_DB_SUCCESS)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_USER_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("UserDetailResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("UserDetailReq req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}


int CMAPICMgr::HandleGetEmailContentReqs(EmailContentReq* req,EmailContentResp* resp)
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

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_EmailContentResp_Config_Reqs(resp,iReturn);
        return 0;
    }

    switch(iOperID)
    {
        case GET_EMAIL_CONTENT:
            iReturn =  m_dbInterface->mysql_EmailContent_Get_Config_Reqs(req,resp);
            break;
        default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_responseid(CMAPI_ERROR);
            break;
    }

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    if(iReturn == DRE_DB_SUCCESS)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_USER_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("UserDetailResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("UserDetailReq req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}


int CMAPICMgr::HandleGetUserConfigReqs(UserDetailReq* req,UserDetailResp* resp)
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

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_UserDetailResp_Config_Reqs(resp,iReturn);

        return 0;
    }
#if NOT_USED_IN_IWF
    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_UserResp_Config_Reqs(resp, iReturn);
		}
		else
		{
            if(iReturn == GET_LOCK_ERR_DB_ERROR)
            {
			    DLOG_ERROR("Database Error!");
			    m_dbInterface->mysql_set_error_for_UserResp_Config_Reqs(resp, iReturn);
            }
            else if(iReturn == GET_LOCK_ERR_RESOURSE_BUSY)
            {
			    DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
			    m_dbInterface->mysql_set_error_for_UserResp_Config_Reqs(resp, iReturn);
            }
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_responseid(CMAPI_ERROR);
	        DLOG_NONE(" < %s ",__FUNCTION__);
			return 0;
		}
	}

    switch(iOperID)
    {
        case GET_USER:
            iReturn =  m_dbInterface->mysql_UserDetail_Get_Config_Reqs(req,resp);
            break;
        case GET_USER_ROLE:
            iReturn =  m_dbInterface->mysql_UserRole_Get_Config_Reqs(req,resp);
            break;
        case GET_USER_PRIVILEGE:
            iReturn =  m_dbInterface->mysql_Previlage_GetConfig_Reqs(req,resp);
            break;
        default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_responseid(CMAPI_ERROR);
            break;
    }

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    if(iReturn == DRE_DB_SUCCESS)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_USER_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("UserDetailResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("UserDetailReq req = %s",req->DebugString().c_str());
#endif
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}


int CMAPICMgr::GetUserConfig(UserReq* req,UserResp* resp)
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

    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_UserResp_Config_Reqs(resp,iReturn);
        return 0;
    }

    switch(iOperID)
    {
        case GET_USER:
            iReturn =  m_dbInterface->mysql_User_Get_Config_Reqs(req,resp);
            break;
#if 0
        case GET_GROUP:
            iReturn =  m_dbInterface->mysql_Role_Get_Config_Reqs(req,resp);
            break;
#endif
        default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_responseid(CMAPI_ERROR);
            break;
    }

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    if(iReturn == DRE_DB_SUCCESS)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_USER_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("UserResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("UserReq req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::HandleSetEmailContentReqs(EmailContentReq* req,EmailContentResp* resp)
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

	if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
	{
		DLOG_CRITICAL("Failed to Get the Database Connection");
		resp->set_responseid(CMAPI_ERROR);
		m_dbInterface->mysql_set_error_for_EmailContentResp_Config_Reqs(resp,iReturn);
		return 0;
	}

	//Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_EmailContentResp_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
			DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_responseid(CMAPI_ERROR);
			m_dbInterface->mysql_set_error_for_EmailContentResp_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
			return 0;
		}
	}

	switch(iOperID)
	{
        case MOD_EMAIL_CONTENT:
			iReturn =  m_dbInterface->mysql_EmailContent_Mod_Config_Reqs(req,resp);
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

	DLOG_DEBUG("UserResp resp = %s",resp->DebugString().c_str());
	DLOG_DEBUG("UserReq req = %s",req->DebugString().c_str());
	DLOG_NONE(" < %s ",__FUNCTION__);
	return 0;
}

int CMAPICMgr::HandleSetEmailServerReqs(EmailServerReq* req,EmailServerResp* resp)
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

	if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
	{
		DLOG_CRITICAL("Failed to Get the Database Connection");
		resp->set_responseid(CMAPI_ERROR);
		m_dbInterface->mysql_set_error_for_EmailServerResp_Config_Reqs(resp,iReturn);
		return 0;
	}

	//Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_EmailServerResp_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
			DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_responseid(CMAPI_ERROR);
			m_dbInterface->mysql_set_error_for_EmailServerResp_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
			return 0;
		}
	}

	switch(iOperID)
	{
        case SET_EMAIL_SERVER:
			iReturn =  m_dbInterface->mysql_EmailServer_Set_Config_Reqs(req,resp);
            break;
        case DEL_EMAIL_SERVER:
			iReturn =  m_dbInterface->mysql_EmailServer_Del_Config_Reqs(req,resp);
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

	DLOG_DEBUG("UserResp resp = %s",resp->DebugString().c_str());
	DLOG_DEBUG("UserReq req = %s",req->DebugString().c_str());
	DLOG_NONE(" < %s ",__FUNCTION__);
	return 0;
}

int CMAPICMgr::HandleSetUserConfigReqs(UserDetailReq* req,UserDetailResp* resp)
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

	if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
	{
		DLOG_CRITICAL("Failed to Get the Database Connection");
		resp->set_responseid(CMAPI_ERROR);
		m_dbInterface->mysql_set_error_for_UserDetailResp_Config_Reqs(resp,iReturn);
		return 0;
	}

	//Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_UserDetailResp_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
			DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_responseid(CMAPI_ERROR);
			m_dbInterface->mysql_set_error_for_UserDetailResp_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
			return 0;
		}
	}

	switch(iOperID)
	{
		case SET_USER:
			iReturn =  m_dbInterface->mysql_UserDetail_Add_Config_Reqs(req,resp);
			break;
		case MOD_USER:
			iReturn =  m_dbInterface->mysql_UserDetail_Mod_Config_Reqs(req,resp);
			break;
		case DEL_USER:
			iReturn =  m_dbInterface->mysql_UserDetail_Del_Config_Reqs(req,resp);
			break;
        case MOD_USER_ROLE:
			iReturn =  m_dbInterface->mysql_UserRole_Mod_Config_Reqs(req,resp);
            break;
        case DEL_USER_ROLE:
			iReturn =  m_dbInterface->mysql_UserRole_Del_Config_Reqs(req,resp);
            break;
        case ADD_USER_ROLE:
			iReturn =  m_dbInterface->mysql_UserRole_Add_Config_Reqs(req,resp);
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

	DLOG_DEBUG("UserResp resp = %s",resp->DebugString().c_str());
	DLOG_DEBUG("UserReq req = %s",req->DebugString().c_str());
	DLOG_NONE(" < %s ",__FUNCTION__);
	return 0;
}

int CMAPICMgr::SetUserConfig(UserReq* req,UserResp* resp)
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

	if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
	{
		DLOG_CRITICAL("Failed to Get the Database Connection");
		resp->set_responseid(CMAPI_ERROR);
		m_dbInterface->mysql_set_error_for_UserResp_Config_Reqs(resp,iReturn);
		return 0;
	}

	//Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_UserResp_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
			DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_responseid(CMAPI_ERROR);
			m_dbInterface->mysql_set_error_for_UserResp_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
			return 0;
		}
	}

	switch(iOperID)
	{
		case SET_USER:
			iReturn =  m_dbInterface->mysql_User_Add_Config_Reqs(req,resp);
			break;
		case MOD_USER:
			iReturn =  m_dbInterface->mysql_User_Mod_Config_Reqs(req,resp);
			break;
		case DEL_USER:
			iReturn =  m_dbInterface->mysql_User_Del_Config_Reqs(req,resp);
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

	DLOG_DEBUG("UserResp resp = %s",resp->DebugString().c_str());
	DLOG_DEBUG("UserReq req = %s",req->DebugString().c_str());
	DLOG_NONE(" < %s ",__FUNCTION__);
	return 0;
}
