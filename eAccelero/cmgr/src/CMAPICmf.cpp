#include <CMAPICMgr.h>
#include <CMAPICommon.h>
#include <CMgrDbInterface.h>
//#include <CMgrCmfDbInterface.h>

extern std::map<int,std::string> errorMap;

int CMAPICMgr::HandleGetTemplateConfigReqs(TemplateReq *req, TemplateResp *resp)
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
		m_dbInterface->mysql_set_error_for_Template_config_Reqs(resp,iReturn);
		return 0;
	}

	switch(iOperID)
	{
		case GET_PEER_TEMPLATE:
			iReturn =  m_dbInterface->mysql_CmfPeerTemplate_Get_Config_Reqs(req,resp);
			break;
		case GET_REALM_TEMPLATE:
			iReturn =  m_dbInterface->mysql_CmfRealmTemplate_Get_Config_Reqs(req,resp);
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
    else if(iReturn == GET_PEER_TEMPLATE_ERR_NO_DATA_PRESENT)
		resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_REALM_TEMPLATE_ERR_NO_DATA_PRESENT)
		resp->set_responseid(CMAPI_SUCCESS);
	else
		resp->set_responseid(CMAPI_ERROR);

	DLOG_DEBUG("Template resp = %s",resp->DebugString().c_str());
	DLOG_DEBUG("Template req = %s",req->DebugString().c_str());
	DLOG_NONE(" < %s ",__FUNCTION__);
	return 0;
}

int CMAPICMgr::HandleSetTemplateConfigReqs(TemplateReq *req, TemplateResp *resp)
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
		m_dbInterface->mysql_set_error_for_Template_config_Reqs(resp,iReturn);
		return 0;
	}

	//Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_Template_config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_responseid(CMAPI_ERROR);
			m_dbInterface->mysql_set_error_for_Template_config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
			return 0;
		}
	}

	switch(iOperID)
	{
		case ADD_PEER_TEMPLATE:
			iReturn =  m_dbInterface->mysql_CmfPeerTemplate_Add_Config_Reqs(req,resp);
			break;
		case ADD_REALM_TEMPLATE:
			iReturn =  m_dbInterface->mysql_CmfRealmTemplate_Add_Config_Reqs(req,resp);
			break;
		case MOD_PEER_TEMPLATE:
			iReturn =  m_dbInterface->mysql_CmfPeerTemplate_Mod_Config_Reqs(req,resp);
			break;
		case MOD_REALM_TEMPLATE:
			iReturn =  m_dbInterface->mysql_CmfRealmTemplate_Mod_Config_Reqs(req,resp);
			break;
		case DEL_REALM_TEMPLATE:
			iReturn =  m_dbInterface->mysql_CmfRealmTemplate_Del_Config_Reqs(req,resp);
			break;
		case DEL_PEER_TEMPLATE:
			iReturn =  m_dbInterface->mysql_CmfPeerTemplate_Del_Config_Reqs(req,resp);
			break;
		default:
			DLOG_ERROR("Unknown Operation ID");
			resp->set_responseid(CMAPI_ERROR);
			break;
	}

    if(iReturn != DRE_DB_SUCCESS)
    {

        DLOG_ERROR("iReturn != DRE_DB_SUCCESS");
        m_LockManager->CMgr_ReleaseLock(iOperID);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
        resp->set_responseid(CMAPI_ERROR);
    }
	else
	{
		DLOG_DEBUG("iReturn == DRE_DB_SUCCESS");
		TemplateReq *lReq = new TemplateReq();
		lReq->CopyFrom(*req);

		CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID,
				CMAPI_SUCCESS, m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
		m_diaMgtTemplateCallerObj->HandleDreSetTemplateConfigReqs(*req, (void*)cookie);
		resp->set_responseid(CMAPI_SUCCESS);
	}

	DLOG_DEBUG("Template resp = %s",resp->DebugString().c_str());
	DLOG_DEBUG("Template req = %s",req->DebugString().c_str());

	DLOG_NONE(" < %s ",__FUNCTION__);
	return 0;
}

int CMAPICMgr::FetchDreTemplateConfiguration(TemplateReq *req, TemplateResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DbStatus_e iReturnPeer = DRE_DB_FAIL;
    DbStatus_e iReturnRealm = DRE_DB_FAIL;
    if ((iReturnPeer = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_Template_config_Reqs(resp,iReturnPeer);
        return 0;
    }

    iReturnPeer =  m_dbInterface->mysql_CmfPeerTemplate_Get_Config_Reqs(req,resp);
    iReturnRealm =  m_dbInterface->mysql_CmfRealmTemplate_Get_Config_Reqs(req,resp);

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    if(iReturnPeer == DRE_DB_SUCCESS)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturnPeer == GET_PEER_TEMPLATE_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturnRealm == DRE_DB_SUCCESS)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturnRealm == GET_REALM_TEMPLATE_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("Tracing resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Tracing req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}


//sprint-3 cmapi-calls

int CMAPICMgr::FetchCMFActionsForTrigger(CMFActionTriggerReq *req, CMFActionTriggerResp *resp)
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
		m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,iReturn);
		return 0;
	}

	switch(iOperID)
	{
		case GET_CMF_ACTIONS_AND_TRIGGERS:
			iReturn =  m_dbInterface->mysql_Cmf_Get_Action_For_Trigger_Config_Req(req,resp);
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
	else
		resp->set_responseid(CMAPI_ERROR);

	DLOG_DEBUG("CMF resp = %s",resp->DebugString().c_str());
	DLOG_DEBUG("CMF req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
	return 0;
}

int CMAPICMgr::FetchAllCMFLevels(CMFLevelReq *req, CMFLevelResp *resp)
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
		m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,iReturn);
		return 0;
	}

	switch(iOperID)
	{
		case GET_CMF_LEVEL:
			iReturn =  m_dbInterface->mysql_Cmf_Get_CMFLevel_Config_Req(req, resp);
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
    else if(iReturn == GET_CMFLEVEL_ERR_NO_DATA_PRESENT)
		resp->set_responseid(CMAPI_SUCCESS);
	else
		resp->set_responseid(CMAPI_ERROR);

	DLOG_DEBUG("CMFLevel resp = %s",resp->DebugString().c_str());
	DLOG_DEBUG("CMFLevel req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
	return 0;
}

int CMAPICMgr::FetchCMFPriorityConfiguration(PriorityConfigReq *req, PriorityConfigResp *resp)
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
        m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,iReturn);
        return 0;
    }

    switch(iOperID)
    {
        case GET_CMF_DIA_PRIORITY:
            iReturn = m_dbInterface->mysql_Cmf_Get_DiaPriority_Config_Req(req,resp);
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
    else if(iReturn == GET_CMF_DIA_PRIORITY_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("CMF resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("CMF req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::FetchAllCMFTriggers(CMFTriggerReq *req, CMFTriggerResp *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

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
        m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,iReturn);
        return 0;
    }

    switch(iOperID)
    {
        case GET_CMF_TRIGGER:
            iReturn =  m_dbInterface->mysql_Cmf_Get_CMFTrigger_Config_Req(req, resp);
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
    else if(iReturn == GET_CMF_TRIGGER_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("CMFAction resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("CMFAction req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::FetchAllCMFActions(CMFActionReq *req, CMFActionResp *resp)
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
		m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,iReturn);
		return 0;
	}

	switch(iOperID)
	{
		case GET_CMF_ACTION:
			iReturn =  m_dbInterface->mysql_Cmf_Get_CMFAction_Config_Req(req, resp);
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
    else if(iReturn == GET_CMF_ACTION_ERR_NO_DATA_PRESENT)
		resp->set_responseid(CMAPI_SUCCESS);
	else
		resp->set_responseid(CMAPI_ERROR);

	DLOG_DEBUG("CMFAction resp = %s",resp->DebugString().c_str());
	DLOG_DEBUG("CMFAction req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
	return 0;
}

int CMAPICMgr::HandleDeleteRuleConfig(RuleConfigReq *req, RuleConfigResp *resp)
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
		m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,iReturn);
		return 0;
	}

    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_responseid(CMAPI_ERROR);
			m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
			return 0;
		}
	}

    switch(iOperID)
    {
        case DELETE_CMF_RULE:
            iReturn =  m_dbInterface->mysql_Cmf_Del_CMFRule_Config_Req(req, resp);
            break;
        default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_responseid(CMAPI_ERROR);
            break;
    }

    if(iReturn != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("iReturn != DRE_DB_SUCCESS");
        m_LockManager->CMgr_ReleaseLock(iOperID);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
        resp->set_responseid(CMAPI_ERROR);
    }
    else
    {
        DLOG_ERROR("iReturn == DRE_DB_SUCCESS");
        RuleConfigReq *lReq = new RuleConfigReq();
        lReq->CopyFrom(*req);

        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID,
                CMAPI_SUCCESS, m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
        m_diaMgmtCmfCallerObj->HandleDreSetRuleConfig(*req, (void*)cookie);
        resp->set_responseid(CMAPI_SUCCESS);
    }

    DLOG_DEBUG("CMF Delete Rule resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("CMF Delete Rule req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPICMgr::FetchCMFRuleConfiguration(RuleConfigReq *req, RuleConfigResp *resp)
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
		m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,iReturn);
		return 0;
	}

	switch(iOperID)
	{
		case GET_CMF_RULE:
			iReturn =  m_dbInterface->mysql_Cmf_Get_CMFRules_Config_Req(req, resp);
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
    else if(iReturn == GET_CMFRULE_ERR_NO_DATA_PRESENT)
		resp->set_responseid(CMAPI_SUCCESS);
	else
		resp->set_responseid(CMAPI_ERROR);

	DLOG_DEBUG("CMF resp = %s",resp->DebugString().c_str());
	DLOG_DEBUG("CMF req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
	return 0;
}


int CMAPICMgr::HandleSetRuleConfig(RuleConfigReq *req, RuleConfigResp *resp)
{
	int iOperID;
	DbStatus_e iReturn = DRE_DB_FAIL;
	DLOG_NONE(" > %s ",__FUNCTION__);

	if(req->has_requestid())
		iOperID = req->requestid();
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
		m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,iReturn);
		return 0;
	}

    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_responseid(CMAPI_ERROR);
			m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
			return 0;
		}
	}

    switch(iOperID)
    {
        case ADD_CMF_RULE:
            iReturn =  m_dbInterface->mysql_Cmf_Add_CMFRule_Config_Req(req, resp);
            break;
        case MODIFY_CMF_RULE:
            iReturn =  m_dbInterface->mysql_Cmf_Mod_CMFRule_Config_Req(req, resp);
            break;
        case SET_CMF_RULE_STATUS:
            iReturn =  m_dbInterface->mysql_Cmf_Set_CMFRuleStatus_Config_Req(req, resp);
            break;
        default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_responseid(CMAPI_ERROR);
            break;
    }

    if(iReturn != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("iReturn != DRE_DB_SUCCESS");
        m_LockManager->CMgr_ReleaseLock(iOperID);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
        resp->set_responseid(CMAPI_ERROR);
    }
    else
    {
        DLOG_ERROR("iReturn == DRE_DB_SUCCESS");
        RuleConfigReq *lReq = new RuleConfigReq();
        lReq->CopyFrom(*req);

        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID,
                CMAPI_SUCCESS, m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
        m_diaMgmtCmfCallerObj->HandleDreSetRuleConfig(*req, (void*)cookie);
        resp->set_responseid(CMAPI_SUCCESS);
    }

    DLOG_DEBUG("CMF resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("CMF req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
	return 0;
}

int CMAPICMgr::HandleSetPriorityConfig(PriorityConfigReq *req, PriorityConfigResp *resp)
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
		m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,iReturn);
		return 0;
	}

    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_responseid(CMAPI_ERROR);
			m_dbInterface->mysql_set_error_for_CMF_config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
			return 0;
		}
	}

    switch(iOperID)
    {
        case ADD_CMF_DIA_PRIORITY:
            iReturn =  m_dbInterface->mysql_Cmf_Add_Priority_Config_Req(req, resp);
            break;
        case MOD_CMF_DIA_PRIORITY:
            iReturn =  m_dbInterface->mysql_Cmf_Mod_Priority_Config_Req(req, resp);
            break;
        case DEL_CMF_DIA_PRIORITY:
            iReturn =  m_dbInterface->mysql_Cmf_Del_Priority_Config_Req(req, resp);
            break;
        default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_responseid(CMAPI_ERROR);
            break;
    }

    if(iReturn != DRE_DB_SUCCESS)
    {

        DLOG_ERROR("iReturn != DRE_DB_SUCCESS");
        m_LockManager->CMgr_ReleaseLock(iOperID);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
        resp->set_responseid(CMAPI_ERROR);
    }
    else
    {
        DLOG_ERROR("iReturn == DRE_DB_SUCCESS");
        PriorityConfigReq *lReq = new PriorityConfigReq();
        lReq->CopyFrom(*req);

        CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID,
                CMAPI_SUCCESS, m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);
        m_diaMgmtCmfCallerObj->HandleDreSetCMFPriorityConfig(*req, (void*)cookie);
        resp->set_responseid(CMAPI_SUCCESS);
    }

    DLOG_DEBUG("CMF Priority resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("CMF Priority req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
	return 0;
}

int CMAPICMgr::FetchCMFTemlateConfig(TemplateReq *Req, TemplateResp *Resp)
{
#if 0
	int iOperID;
	DbStatus_e iReturn = DRE_DB_FAIL;
	DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_DEBUG("ConfigFetch req = %s",Req->DebugString().c_str());
    if ((iReturn = m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        Resp->set_respcode(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_CMF_Config_Reqs(Resp,Resp);
        return 0;
    }
    TransformPluginConfigReq TransPluginConfigReq;
    iTransPlugins = m_dbInterface->mysql_TransPlugin_Get_Config_Reqs(&TransPluginConfigReq,Resp);

    if(iTransPlugins == DRE_DB_SUCCESS)
        Resp->set_respcode(CMAPI_SUCCESS);
    else if(iTransPlugins == GET_TRANSFORM_PLUGIN_ERR_NO_DATA_PRESENT)
        Resp->set_respcode(CMAPI_SUCCESS);

    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_NONE(" < %s ",__FUNCTION__);
#endif
	return 0;
}

int CMAPICMgr::FetchCMFConfig(CMFConfigReq *Req, CMFConfigResp *Resp)
{
	DbStatus_e iReturn = DRE_DB_FAIL;
	DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_DEBUG("ConfigFetch req = %s",Req->DebugString().c_str());

    if ((iReturn= m_dbInterface->m_dbHandle.mysql_set_current_connection()) != DRE_DB_SUCCESS)
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        Resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_CMF_config_Reqs(Resp, iReturn);
        return 0;
    }

    // Fetch CMF levels and set in Response
    CMFLevelReq lCMFLevelReq;
    CMFLevelResp lCMFLevelResp;
    iReturn = m_dbInterface->mysql_Cmf_Get_CMFLevel_Config_Req(&lCMFLevelReq, &lCMFLevelResp);
    if(iReturn == DRE_DB_SUCCESS)
    {
        int iCount = lCMFLevelResp.levels_size();
        for(int iIndex=0; iIndex<iCount; iIndex++)
        {
            CMFLevel *pCMFLevel = lCMFLevelResp.mutable_levels(iIndex);
            CMFLevel *pCMFLevelResp = Resp->add_levels();
            pCMFLevelResp->CopyFrom(*pCMFLevel);
        }
    }

    // Fetch CMF Rules and set in Response
    RuleConfigReq lRuleConfigReq;
    RuleConfigResp lRuleConfigResp;
    iReturn = m_dbInterface->mysql_Cmf_Get_CMFRules_Config_Req(&lRuleConfigReq, &lRuleConfigResp);
    if(iReturn == DRE_DB_SUCCESS)
    {
        int iCount = lRuleConfigResp.rules_size();
        for(int iIndex=0; iIndex<iCount; iIndex++)
        {
            RuleConfig *pRuleConfig = lRuleConfigResp.mutable_rules(iIndex);
            RuleConfig *pRuleConfigResp = Resp->add_rules();
            pRuleConfigResp->CopyFrom(*pRuleConfig);
        }
    }

    // Fetch CMF ActionsForTriggers and set in Response
    CMFActionTriggerReq lCMFActionTriggerReq;
    CMFActionTriggerResp lCMFActionTriggerResp;
    iReturn = m_dbInterface->mysql_Cmf_Get_Action_For_Trigger_Config_Req(&lCMFActionTriggerReq, &lCMFActionTriggerResp);
    if(iReturn == DRE_DB_SUCCESS)
    {
        int iCount = lCMFActionTriggerResp.mappings_size();
        for(int iIndex=0; iIndex<iCount; iIndex++)
        {
            CMFTriggerActionMapping *pCMFTriggerActionMapping = lCMFActionTriggerResp.mutable_mappings(iIndex);
            CMFTriggerActionMapping *pCMFTriggerActionMappingResp = Resp->add_mappings();
            pCMFTriggerActionMappingResp->CopyFrom(*pCMFTriggerActionMapping);
        }
    }

    // Fetch CMF Dia Priority and set in Response
    PriorityConfigReq lPriorityConfigReq;
    PriorityConfigResp lPriorityConfigResp;
    iReturn = m_dbInterface->mysql_Cmf_Get_DiaPriority_Config_Req(&lPriorityConfigReq, &lPriorityConfigResp);
    if(iReturn == DRE_DB_SUCCESS)
    {
        int iCount = lPriorityConfigResp.priorities_size();
        for(int iIndex=0; iIndex<iCount; iIndex++)
        {
            PriorityConfig *pPriorityConfig = lPriorityConfigResp.mutable_priorities(iIndex);
            PriorityConfig *pPriorityConfigResp = Resp->add_pconfig();
            pPriorityConfigResp->CopyFrom(*pPriorityConfig);
        }
    }

    if(iReturn == DRE_DB_SUCCESS)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_ACTION_FOR_TRIGGER_ERR_NO_MAPPING_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_CMFRULE_ERR_NO_DATA_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_CMFRULE_ERR_NO_DATA_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_CMF_DIA_PRIORITY_ERR_NO_DATA_PRESENT)
        Resp->set_responseid(CMAPI_SUCCESS);
    else
        Resp->set_responseid(CMAPI_ERROR);

    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("ConfigFetch Resp = %s",Resp->DebugString().c_str());
    DLOG_DEBUG("ConfigFetch Req = %s",Req->DebugString().c_str());
    DLOG_DEBUG("Size of Resp = %dKB",(Resp->ByteSize())/1024);
    DLOG_NONE(" < %s ",__FUNCTION__);

	return 0;
}

// ***********************************************************************
// Congestion Management Function Response Handlers Implementation
// ***********************************************************************

int CMAPICMgr::HandleDreSetTemplateConfigReqsRespCbk(TemplateResp *resp)
{
	int retVal = 0;
	std::string StrVal;
	TemplateResp ErrorResponse;
	DLOG_NONE(">HandleDreSetTemplateConfigReqsRespCbk: ");

	if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
	{
		DLOG_NONE("Response From Instance %d", MeSS::Handle().m_src.instance);
		return 0;
	}
	DLOG_NONE(">HandleDreSetTemplateConfigReqsRespCbk: ");

	CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
	int iOperID = cookie->iReqID;
	void* conn = cookie->con;
	TemplateReq *req = (TemplateReq*)cookie->req;

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

				DLOG_DEBUG(">HandleDreSetTemplateConfigReqsRespCbk: DRE operation - Successful. Committing the database ");
    	    			m_LockManager->CMgr_ReleaseLock(iOperID,conn);
				//commit database
				m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
				m_standbydiaMgtTemplateCallerObj->HandleDreSetTemplateConfigReqs(*req, (void*)NULL);
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
	m_templateResultsHandler[cookie->comp]->SendDreTemplateConfigResult(*resp);
	deleteCookie(cookie,ADD_PEER_TEMPLATE);
	DLOG_NONE("<HandleDreSetTemplateConfigReqsRespCbk: ");
	return retVal;
}

int CMAPICMgr::SendCMFRuleConfigResultRespCbk(CMAPIRes *Resp)
{
	return 0;
}

int CMAPICMgr::SendCMFPriorityConfigResultRespCbk(CMAPIRes *Resp)
{
	return 0;
}

int CMAPICMgr::SendDreTemplateConfigResultRespCbk(CMAPIRes *Resp)
{
	return 0;
}

int CMAPICMgr::HandleDreSetRuleConfigRespCbk(RuleConfigResp *resp)
{
	int retVal = 0;
	std::string StrVal;
	RuleConfigResp ErrorResponse;
	DLOG_NONE(">HandleDreSetRuleConfigRespCbk: ");

	if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
	{
		DLOG_NONE("Response From Instance %d", MeSS::Handle().m_src.instance);
		return 0;
	}

	CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
	int iOperID = cookie->iReqID;
	void* conn = cookie->con;
	RuleConfigReq *req = (RuleConfigReq*)cookie->req;

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

				DLOG_DEBUG(">HandleDreSetRuleConfigRespCbk: DRE operation - Successful. Committing the database ");
    	    	m_LockManager->CMgr_ReleaseLock(iOperID,conn);
				//commit database
				m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
			    m_standbydiaMgmtCmfCallerObj->HandleDreSetRuleConfig(*req, (void*)NULL);
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
	m_cmfConfigResultsHandler[cookie->comp]->SendCMFRuleConfigResult(*resp);
	deleteCookie(cookie,ADD_CMF_RULE);
	DLOG_NONE("<HandleDreSetRuleConfigRespCbk: ");
	return retVal;
}

int CMAPICMgr::HandleDreSetCMFPriorityConfigRespCbk(PriorityConfigResp *resp)
{
	int retVal = 0;
	std::string StrVal;
	PriorityConfigResp ErrorResponse;
	DLOG_NONE(">HandleDreSetCMFPriorityConfigRespCbk: ");

	if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
	{
		DLOG_NONE("Response From Instance %d", MeSS::Handle().m_src.instance);
		return 0;
	}
	DLOG_NONE(">HandleDreSetCMFPriorityConfigRespCbk: ");

	CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
	int iOperID = cookie->iReqID;
	void* conn = cookie->con;
	PriorityConfigReq *req = (PriorityConfigReq*)cookie->req;

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

				DLOG_DEBUG(">HandleDreSetCMFPriorityConfigRespCbk: DRE operation - Successful. Committing the database ");
    	    			m_LockManager->CMgr_ReleaseLock(iOperID,conn);
				//commit database
				m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
				m_standbydiaMgmtCmfCallerObj->HandleDreSetCMFPriorityConfig(*req, (void*)NULL);
			}
			else {
				//resp->SerializeToString(&StrVal);
				//m_CMAPIResponse->Set(StrVal);
				//rollback database, since the DRE configuration failed
                DLOG_DEBUG(">HandleDreSetTemplateConfigReqsRespCbk: DRE operation - Failed ");
                DLOG_DEBUG("> DRE Response : %s", resp->DebugString().c_str());
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
	m_cmfConfigResultsHandler[cookie->comp]->SendCMFPriorityConfigResult(*resp);
	deleteCookie(cookie,ADD_CMF_DIA_PRIORITY);
	DLOG_NONE("<HandleDreSetCMFPriorityConfigRespCbk ");
	return retVal;
}

int CMAPICMgr::FetchCMFSystemTriggerStatesRespCbk(TriggerStateResponse*)
{
	return 0;
}
int CMAPICMgr::FetchCMFDiaPeerTriggerStatesRespCbk(PeerTriggerStateResponse*)
{
	return 0;
}
int CMAPICMgr::FetchCMFDiaRealmTriggerStatesRespCbk(RealmTriggerStateResponse*)
{
	return 0;
}
int CMAPICMgr::FetchCMFLevelConfigRespCbk(CMFLevelConfigResponse*)
{
	return 0;
}
