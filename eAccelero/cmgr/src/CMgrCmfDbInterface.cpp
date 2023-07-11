#include <CMgrDbInterface.h>

using namespace std;
extern std::map<int,std::string> errorMap;

/*
 * Error Functions for CMF (Sprint-3)
*/
void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(CMFActionResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(CMFActionTriggerResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(CMFLevelResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(RuleConfigResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(PriorityConfigResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(TemplateResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(CMFConfigResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(CMFTriggerResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}



// Private error functions
void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(CMFTrigger *req, CMFTriggerResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(CMFTrigger *req, CMFActionTriggerResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(CMFLevel *req, CMFLevelResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(RuleConfig *req, RuleConfigResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(req->has_rulename())
        err->add_variables(req->rulename());

    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(PriorityConfig *req, PriorityConfigResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(TemplateReq *req, TemplateResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(CMFConfigReq *req, CMFConfigResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(CMFAction *req, CMFActionResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(AppIdPriority *req, PriorityConfigResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);

}

void CMgrDbInterface::mysql_set_error_for_CMF_config_Reqs(CCPriority *req, PriorityConfigResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);

}
//Errore  - END -


void CMgrDbInterface::mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(::CMFRealmTemplate *req, TemplateResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(req->has_realmtemplatename())
        err->add_variables(req->realmtemplatename());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(::CMFPeerTemplate *req, TemplateResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(req->has_peertemplatename())
        err->add_variables(req->peertemplatename());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_TemplateResp_Config_Reqs(::TemplateReq *req, TemplateResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_Template_config_Reqs(TemplateResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_CmfRealmTemplate_Get_Config_Reqs(TemplateReq *req, TemplateResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int iCount = req->realmtemplates_size();

    for(int i=0; i<iCount; i++)
    {
        ::CMFRealmTemplate *pCMFRealmTemplate = NULL;

        pCMFRealmTemplate = req->mutable_realmtemplates(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_CmfDiaRealmTemplate_Create_Select_Query(pCMFRealmTemplate,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_REALM_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_RealmTemplate_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;

            mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;

    }

    if(iCount == 0)
    {
        ::CMFRealmTemplate localCMFRealmTemplate;
        ::CMFRealmTemplate *pCMFRealmTemplate = &localCMFRealmTemplate;

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_CmfDiaRealmTemplate_Create_Select_Query(pCMFRealmTemplate,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_REALM_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_RealmTemplate_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;

            mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}


DbStatus_e CMgrDbInterface::mysql_RealmTemplate_resultset_to_protoBuff(sql::ResultSet *pRes,TemplateResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: RealmTemplate Config Result Set= %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_REALM_TEMPLATE_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            ::CMFRealmTemplate *pCMFRealmTemplate= resp->add_realmtemplates();
            if(!pRes->isNull("CMF_REALM_TEMPLATE_ID"))
                pCMFRealmTemplate->set_realmtemplateid(pRes->getUInt("CMF_REALM_TEMPLATE_ID"));
            if(!pRes->isNull("REALM_TEMPLATE_NAME"))
                pCMFRealmTemplate->set_realmtemplatename(pRes->getString("REALM_TEMPLATE_NAME"));
            if(!pRes->isNull("MAX_IN_TPS"))
                pCMFRealmTemplate->set_maxintps(pRes->getUInt("MAX_IN_TPS"));
            if(!pRes->isNull("MAX_OUT_TPS"))
                pCMFRealmTemplate->set_maxouttps(pRes->getUInt("MAX_OUT_TPS"));

            if(!pRes->isNull("PRIORITY"))
            {
                if(pRes->getString("PRIORITY") == "normal")
                    pCMFRealmTemplate->set_priority(CMFRealmTemplate_Status_NORMAL);
                if(pRes->getString("PRIORITY") == "high")
                    pCMFRealmTemplate->set_priority(CMFRealmTemplate_Status_HIGH);
            }
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;


}


DbStatus_e CMgrDbInterface::mysql_CmfPeerTemplate_Get_Config_Reqs(TemplateReq *req, TemplateResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int iCount = req->peertemplates_size();

    for(int i=0; i<iCount; i++)
    {
        ::CMFPeerTemplate *pCMFPeerTemplate = NULL;

        pCMFPeerTemplate = req->mutable_peertemplates(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_CmfDiaPeerTemplate_Create_Select_Query(pCMFPeerTemplate,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_PEER_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_PeerTemplate_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;

            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;

    }

    if(iCount == 0)
    {
        ::CMFPeerTemplate localCMFPeerTemplate;
        ::CMFPeerTemplate *pCMFPeerTemplate = &localCMFPeerTemplate;

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_CmfDiaPeerTemplate_Create_Select_Query(pCMFPeerTemplate,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_PEER_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_PeerTemplate_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;

            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;

    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_PeerTemplate_resultset_to_protoBuff(sql::ResultSet *pRes,TemplateResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: PeerTemplate Config Result Set= %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_PEER_TEMPLATE_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            ::CMFPeerTemplate *pCMFPeerTemplate= resp->add_peertemplates();
            if(!pRes->isNull("CMF_PEER_TEMPLATE_ID"))
                pCMFPeerTemplate->set_peertemplateid(pRes->getUInt("CMF_PEER_TEMPLATE_ID"));
            if(!pRes->isNull("PRIORITY"))
            {
                if(pRes->getString("PRIORITY") == "normal")
                    pCMFPeerTemplate->set_priority(CMFPeerTemplate_Status_NORMAL);
                if(pRes->getString("PRIORITY") == "high")
                    pCMFPeerTemplate->set_priority(CMFPeerTemplate_Status_HIGH);
            }
            if(!pRes->isNull("PEER_TEMPLATE_NAME"))
                pCMFPeerTemplate->set_peertemplatename(pRes->getString("PEER_TEMPLATE_NAME"));
            if(!pRes->isNull("MAX_IN_TPS"))
                pCMFPeerTemplate->set_maxintps(pRes->getUInt("MAX_IN_TPS"));
            if(!pRes->isNull("MAX_OUT_TPS"))
                pCMFPeerTemplate->set_maxouttps(pRes->getUInt("MAX_OUT_TPS"));
            if(!pRes->isNull("MAX_AVG_RESP_TIME"))
                pCMFPeerTemplate->set_maxavgresptime(pRes->getUInt("MAX_AVG_RESP_TIME"));
            if(!pRes->isNull("MAX_PENDING_REQS"))
                pCMFPeerTemplate->set_maxpendingreqs(pRes->getUInt("MAX_PENDING_REQS"));
            if(!pRes->isNull("THROTTLE"))
            {
                if(pRes->getString("THROTTLE") == "enable")
                    pCMFPeerTemplate->set_throttle(CMFPeerTemplate_state_THROTTLE_ENABLE);
                else if(pRes->getString("THROTTLE") == "disable")
                    pCMFPeerTemplate->set_throttle(CMFPeerTemplate_state_THROTTLE_DISABLE);
            }
            if(!pRes->isNull("MAX_ERR_RESP"))
                pCMFPeerTemplate->set_maxerrresp(pRes->getUInt("MAX_ERR_RESP"));
            if(!pRes->isNull("TIME_WINDOW"))
                pCMFPeerTemplate->set_timewindow(pRes->getUInt("TIME_WINDOW"));
            if(!pRes->isNull("ERR_RESP_RESULT_CODE"))
                pCMFPeerTemplate->set_errrespresultcode(pRes->getUInt("ERR_RESP_RESULT_CODE"));
            if(!pRes->isNull("OUTGOING_PEER_CONGESTION_CONDITION"))
            {
                if(pRes->getString("OUTGOING_PEER_CONGESTION_CONDITION") == "pending-queue")
                    pCMFPeerTemplate->set_outpeercongcond(CMFPeerTemplate_Condition_PENDING_QUEUE);
                else if(pRes->getString("OUTGOING_PEER_CONGESTION_CONDITION") == "average-response-time")
                    pCMFPeerTemplate->set_outpeercongcond(CMFPeerTemplate_Condition_AVERAGE_RESPONSE_TIME);
                else if(pRes->getString("OUTGOING_PEER_CONGESTION_CONDITION") == "error-response-count")
                    pCMFPeerTemplate->set_outpeercongcond(CMFPeerTemplate_Condition_ERROR_RESPONSE_COUNT);
                else if(pRes->getString("OUTGOING_PEER_CONGESTION_CONDITION") == "tps")
                    pCMFPeerTemplate->set_outpeercongcond(CMFPeerTemplate_Condition_TPS);
                else if(pRes->getString("OUTGOING_PEER_CONGESTION_CONDITION") == "none")
                    pCMFPeerTemplate->set_outpeercongcond(CMFPeerTemplate_Condition_NONE);
            }
            if(!pRes->isNull("DISCONNECT_MISBEHAVING_PEER"))
            {
                if(pRes->getString("DISCONNECT_MISBEHAVING_PEER") == "enable")
                    pCMFPeerTemplate->set_dismisbehavepeer(CMFPeerTemplate_DisconnectMisbehavingPeer_PEER_ENABLE);
                else if(pRes->getString("DISCONNECT_MISBEHAVING_PEER") == "disable")
                    pCMFPeerTemplate->set_dismisbehavepeer(CMFPeerTemplate_DisconnectMisbehavingPeer_PEER_DISABLE);
            }
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;


}

DbStatus_e CMgrDbInterface::mysql_CmfPeerTemplate_Add_Config_Reqs(TemplateReq *req, TemplateResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int iCount = req->peertemplates_size();

    for(int i=0; i<iCount; i++)
    {
        ::CMFPeerTemplate *pCMFPeerTemplate = NULL;

        pCMFPeerTemplate = req->mutable_peertemplates(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_CmfDiaPeerTemplate_Create_Check_Modifcation_Query(pCMFPeerTemplate,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_PEER_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_CmfDiaPeerTemplate_Create_Add_Query(pCMFPeerTemplate,sStatement);
        }
        else // MOD
        {

            delete pRes;
            DLOG_ERROR("Record Already Present");
            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,ADD_PEER_TEMPLATE_ERR_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_PEER_TEMPLATE_ERR_ALREADY_PRESENT;
        }


        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_PEER_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_fetch_and_fill_PeerTemplate_id(pCMFPeerTemplate,resp)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
               iReturn = ADD_PEER_TEMPLATE_ERR_DB_ERROR;
            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_fetch_and_fill_PeerTemplate_id(::CMFPeerTemplate *pCMFPeerTemplate, TemplateResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_CmfDiaPeerTemplate_Create_Check_Modifcation_Query(pCMFPeerTemplate,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {

        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }


    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() != 0) // ADD
    {
        if(pRes->next())
        {
            if(!pRes->isNull("CMF_PEER_TEMPLATE_ID"))
                pCMFPeerTemplate->set_peertemplateid(pRes->getUInt("CMF_PEER_TEMPLATE_ID"));
        }
    }

    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_CmfRealmTemplate_Add_Config_Reqs(TemplateReq *req, TemplateResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int iCount = req->realmtemplates_size();

    for(int i=0; i<iCount; i++)
    {
        ::CMFRealmTemplate *pCMFRealmTemplate = NULL;

        pCMFRealmTemplate = req->mutable_realmtemplates(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_CmfDiaRealmTemplate_Create_Check_Modifcation_Query(pCMFRealmTemplate,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_REALM_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_CmfDiaRealmTemplate_Create_Add_Query(pCMFRealmTemplate,sStatement);
        }
        else // MOD
        {

            delete pRes;
            DLOG_ERROR("Record Already Present");
            mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,ADD_REALM_TEMPLATE_ERR_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_REALM_TEMPLATE_ERR_ALREADY_PRESENT;
        }


        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_REALM_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_fetch_and_fill_RealmTemplate_id(pCMFRealmTemplate,resp)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
               iReturn = ADD_REALM_TEMPLATE_ERR_DB_ERROR;
            mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_fetch_and_fill_RealmTemplate_id(::CMFRealmTemplate *pCMFRealmTemplate, TemplateResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_CmfDiaRealmTemplate_Create_Check_Modifcation_Query(pCMFRealmTemplate,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {

        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }


    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() != 0) // ADD
    {
        if(pRes->next())
        {
            if(!pRes->isNull("CMF_REALM_TEMPLATE_ID"))
                pCMFRealmTemplate->set_realmtemplateid(pRes->getUInt("CMF_REALM_TEMPLATE_ID"));
        }
    }

    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_CmfPeerTemplate_Mod_Validation( ::CMFPeerTemplate *pCMFPeerTemplate)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if(pCMFPeerTemplate->peertemplatename() == "Default")
    {
        DLOG_NONE(" < %s ",__FUNCTION__);
        return MOD_PEER_TEMPLATE_ERR_DEFAULT_ENTRY;
    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_CmfPeerTemplate_Mod_Config_Reqs(TemplateReq *req, TemplateResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int iCount = req->peertemplates_size();

    for(int i=0; i<iCount; i++)
    {
        ::CMFPeerTemplate *pCMFPeerTemplate = NULL;

        pCMFPeerTemplate = req->mutable_peertemplates(i);

        if((iReturn = mysql_CmfPeerTemplate_Mod_Validation(pCMFPeerTemplate)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_CmfDiaPeerTemplate_Create_Check_Modifcation_Query(pCMFPeerTemplate,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_PEER_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {

            delete pRes;
            DLOG_ERROR("Record Already Present");
            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,MOD_PEER_TEMPLATE_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_PEER_TEMPLATE_ERR_NOT_PRESENT;

        }
        else // MOD
        {
            sql_CmfDiaPeerTemplate_Create_Mod_Query(pCMFPeerTemplate,sStatement);
        }


        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_PEER_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_fetch_and_fill_PeerTemplate_id(pCMFPeerTemplate,resp)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
               iReturn = MOD_PEER_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_CmfRealmTemplate_Mod_Config_Reqs(TemplateReq *req, TemplateResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int iCount = req->realmtemplates_size();

    for(int i=0; i<iCount; i++)
    {
        ::CMFRealmTemplate *pCMFRealmTemplate = NULL;

        pCMFRealmTemplate = req->mutable_realmtemplates(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_CmfDiaRealmTemplate_Create_Check_Modifcation_Query(pCMFRealmTemplate,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_REALM_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Not Present");
            mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,MOD_REALM_TEMPLATE_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_REALM_TEMPLATE_ERR_NOT_PRESENT;

        }
        else // MOD
        {
            sql_CmfDiaRealmTemplate_Create_Mod_Query(pCMFRealmTemplate,sStatement);
        }


        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_REALM_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_fetch_and_fill_RealmTemplate_id(pCMFRealmTemplate,resp)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
               iReturn = MOD_REALM_TEMPLATE_ERR_DB_ERROR;
            mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_CmfPeerTemplate_Del_Validation(CMFPeerTemplate *pCMFPeerTemplate, TemplateResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;


    if(pCMFPeerTemplate->peertemplatename() == "Default")
    {
        mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,DEL_PEER_TEMPLATE_ERR_DEFAULT_ENTRY);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DEL_PEER_TEMPLATE_ERR_DEFAULT_ENTRY;
    }


    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_CmfDiaPeerTemplate_Create_Check_Modifcation_Query(pCMFPeerTemplate,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {

        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = DEL_PEER_TEMPLATE_ERR_DB_ERROR;

        mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }


    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        delete pRes;
        DLOG_ERROR("Record Already Present");
        mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,DEL_PEER_TEMPLATE_ERR_NOT_PRESENT);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DEL_PEER_TEMPLATE_ERR_NOT_PRESENT;
    }
    delete pRes;


    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_CmfDiaPeerTemplate_Create_Validation_Query_for_Peer(pCMFPeerTemplate,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {

        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = DEL_PEER_TEMPLATE_ERR_DB_ERROR;

        mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }


    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() > 0) // ADD
    {
        delete pRes;
        DLOG_ERROR("Record Not Present");
        mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,DEL_PEER_TEMPLATE_ERR_USED_IN_PEER);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DEL_PEER_TEMPLATE_ERR_USED_IN_PEER;
    }
    delete pRes;

    return iReturn;

}

DbStatus_e CMgrDbInterface::mysql_CmfRealmTemplate_Del_Validation(CMFRealmTemplate *pCMFRealmTemplate, TemplateResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_CmfDiaRealmTemplate_Create_Check_Modifcation_Query(pCMFRealmTemplate,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {

        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = DEL_REALM_TEMPLATE_ERR_DB_ERROR;

        mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }


    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        delete pRes;
        DLOG_ERROR("Record Already Present");
        mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,DEL_REALM_TEMPLATE_ERR_NOT_PRESENT);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DEL_REALM_TEMPLATE_ERR_NOT_PRESENT;
    }
    delete pRes;


    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_CmfDiaRealmTemplate_Create_Validation_Query_for_Realm(pCMFRealmTemplate,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {

        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = DEL_REALM_TEMPLATE_ERR_DB_ERROR;

        mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }


    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() > 0) // ADD
    {
        delete pRes;
        DLOG_ERROR("Record Not Present");
        mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,DEL_REALM_TEMPLATE_ERR_USED_IN_REALM);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DEL_REALM_TEMPLATE_ERR_USED_IN_REALM;
    }
    delete pRes;
    return iReturn;

}


DbStatus_e CMgrDbInterface::mysql_CmfPeerTemplate_Del_Config_Reqs(TemplateReq *req, TemplateResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int iCount = req->peertemplates_size();

    for(int i=0; i<iCount; i++)
    {
        ::CMFPeerTemplate *pCMFPeerTemplate = NULL;

        pCMFPeerTemplate = req->mutable_peertemplates(i);

        if((iReturn = mysql_CmfPeerTemplate_Del_Validation(pCMFPeerTemplate,resp)) != DRE_DB_SUCCESS)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_fetch_and_fill_PeerTemplate_id(pCMFPeerTemplate,resp)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
               iReturn = DEL_PEER_TEMPLATE_ERR_DB_ERROR;
            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_CmfDiaPeerTemplate_Create_Delete_Query(pCMFPeerTemplate,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_PEER_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(pCMFPeerTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_CmfRealmTemplate_Del_Config_Reqs(TemplateReq *req, TemplateResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int iCount = req->realmtemplates_size();

    for(int i=0; i<iCount; i++)
    {
        ::CMFRealmTemplate *pCMFRealmTemplate = NULL;

        pCMFRealmTemplate = req->mutable_realmtemplates(i);

        if((iReturn = mysql_CmfRealmTemplate_Del_Validation(pCMFRealmTemplate,resp)) != DRE_DB_SUCCESS)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_fetch_and_fill_RealmTemplate_id(pCMFRealmTemplate,resp)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
               iReturn = DEL_REALM_TEMPLATE_ERR_DB_ERROR;
            mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_CmfDiaRealmTemplate_Create_Delete_Query(pCMFRealmTemplate,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_REALM_TEMPLATE_ERR_DB_ERROR;

            mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(pCMFRealmTemplate,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

/*
 * Functions for CMF (Sprint-3)
 */
DbStatus_e CMgrDbInterface::mysql_CMF_CC_Priority_resultset_to_protoBuff(sql::ResultSet *pRes, PriorityConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG("%s: RowCount = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_CMF_DIA_PRIORITY_ERR_NO_DATA_PRESENT;
        }
	PriorityConfig *pPriorityConfig  = NULL;
	int iCount = resp->priorities_size();	
	if(iCount == 0)
	{
	    pPriorityConfig = resp->add_priorities();
	}
	else
	{
	    pPriorityConfig = resp->mutable_priorities(0);
	}
        
	while(pRes->next())
        {
            ::CCPriority *pCCPriority= pPriorityConfig->add_ccpriorities();

            if(!pRes->isNull("CMD_CODE"))
                pCCPriority->set_cmdcode(pRes->getInt("CMD_CODE"));
            if(!pRes->isNull("CMD_NAME"))
                pCCPriority->set_description(pRes->getString("CMD_NAME"));
            if(!pRes->isNull("PRIORITY"))
            {
                if(pRes->getString("PRIORITY") == "normal")
                    pCCPriority->set_priority(CCPriority_PriorityStatus_LOW);
                else if(pRes->getString("PRIORITY") == "high")
                    pCCPriority->set_priority(CCPriority_PriorityStatus_HIGH);
            }
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_CMF_AppId_Priority_resultset_to_protoBuff(sql::ResultSet *pRes, PriorityConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG("%s: RowCount = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_CMF_DIA_PRIORITY_ERR_NO_DATA_PRESENT;
        }

	PriorityConfig *pPriorityConfig = NULL;
        int iCount = resp->priorities_size();
	if(iCount == 0)
	{
	    pPriorityConfig = resp->add_priorities();
	}
	else
	{
	    pPriorityConfig = resp->mutable_priorities(0);
	}
	
        while(pRes->next())
        {
            AppIdPriority *pAppIdPriority = pPriorityConfig->add_apppriorities();

            if(!pRes->isNull("APP_ID"))
                pAppIdPriority->set_appid(pRes->getInt("APP_ID"));
            if(!pRes->isNull("APP_NAME"))
                pAppIdPriority->set_description(pRes->getString("APP_NAME"));
            if(!pRes->isNull("PRIORITY"))
            {
                if(pRes->getString("PRIORITY") == "normal")
                    pAppIdPriority->set_priority(AppIdPriority_PriorityStatus_LOW);
                else if(pRes->getString("PRIORITY") == "high")
                    pAppIdPriority->set_priority(AppIdPriority_PriorityStatus_HIGH);
            }
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Get_DiaPriority_Config_Req(PriorityConfigReq *req, PriorityConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes;

    int iCount = req->priorities_size();
    if(iCount)
    {
        for(int iIndex = 0; iIndex<iCount; iIndex++)
        {
            PriorityConfig *pPriorityConfig;
            pPriorityConfig = req->mutable_priorities(iIndex);
            int iCountCCpri = pPriorityConfig->ccpriorities_size();
            int iCountAppIdpri = pPriorityConfig->apppriorities_size();
            /*********** Fetch CC Priority ******************/
            if(iCountCCpri)
            {
                for(int iIndex = 0; iIndex<iCountCCpri; iIndex++)
                {
                    CCPriority *pCCPriority = pPriorityConfig->mutable_ccpriorities(iIndex);
                    sql_CCPriority_Create_Select_Query(pCCPriority, sStatement);
                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                    {
                        if(pRes != NULL)
                        {
                            delete pRes;
                        }

                        DLOG_ERROR("Query Execution Failed: %s",sStatement);
                        if(iReturn == DRE_DB_FAIL)
                            iReturn = GET_CMF_DIA_PRIORITY_ERR_DB_ERROR;

                        mysql_set_error_for_CMF_config_Reqs(pCCPriority, resp, iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                    if((iReturn = mysql_CMF_CC_Priority_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
                    {
                        delete pRes;
                        mysql_set_error_for_CMF_config_Reqs(pCCPriority, resp, iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                    delete pRes;
                }
            }
            else
            {
                CCPriority cCPriorityObj;
                sql_CCPriority_Create_Select_Query(&cCPriorityObj, sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {
                    if(pRes != NULL)
                    {
                        delete pRes;
                    }

                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                    if(iReturn == DRE_DB_FAIL)
                        iReturn = GET_CMF_DIA_PRIORITY_ERR_DB_ERROR;

                    mysql_set_error_for_CMF_config_Reqs(&cCPriorityObj, resp, iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                if((iReturn = mysql_CMF_CC_Priority_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
                {
                    delete pRes;
                    mysql_set_error_for_CMF_config_Reqs(&cCPriorityObj, resp, iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                delete pRes;
            }

            /*********** Fetch AppID Priority ******************/
            if(iCountAppIdpri)
            {
                for(int iIndex = 0; iIndex<iCountAppIdpri; iIndex++)
                {
                    AppIdPriority *pAppIdPriority = pPriorityConfig->mutable_apppriorities(iIndex);
                    sql_AppIdPriority_Create_Select_Query(pAppIdPriority, sStatement);
                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                    {
                        if(pRes != NULL)
                        {
                            delete pRes;
                        }

                        DLOG_ERROR("Query Execution Failed: %s",sStatement);
                        if(iReturn == DRE_DB_FAIL)
                            iReturn = GET_CMF_DIA_PRIORITY_ERR_DB_ERROR;

                        mysql_set_error_for_CMF_config_Reqs(pAppIdPriority, resp, iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                    if((iReturn = mysql_CMF_AppId_Priority_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
                    {
                        delete pRes;
                        mysql_set_error_for_CMF_config_Reqs(pAppIdPriority, resp, iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                    delete pRes;
                }
            }
            else
            {
                AppIdPriority appIdPriorityObj;
                sql_AppIdPriority_Create_Select_Query(&appIdPriorityObj, sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {
                    if(pRes != NULL)
                    {
                        delete pRes;
                    }

                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                    if(iReturn == DRE_DB_FAIL)
                        iReturn = GET_CMF_DIA_PRIORITY_ERR_DB_ERROR;

                    mysql_set_error_for_CMF_config_Reqs(&appIdPriorityObj, resp, iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                if((iReturn = mysql_CMF_AppId_Priority_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
                {
                    delete pRes;
                    mysql_set_error_for_CMF_config_Reqs(&appIdPriorityObj, resp, iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                delete pRes;
            }
        }
    }
    else
    {
        /*********** Fetch CC Priority ALL ******************/
        CCPriority cCPriorityObj;
        sql_CCPriority_Create_Select_Query(&cCPriorityObj, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_CMF_DIA_PRIORITY_ERR_DB_ERROR;

            mysql_set_error_for_CMF_config_Reqs(&cCPriorityObj, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        if((iReturn = mysql_CMF_CC_Priority_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
        {
            if(iReturn != GET_CMF_DIA_PRIORITY_ERR_NO_DATA_PRESENT)
                mysql_set_error_for_CMF_config_Reqs(&cCPriorityObj, resp, iReturn);
        }
        delete pRes;
        pRes = NULL;

        /*********** Fetch AppId Priority ALL ******************/
        AppIdPriority appIdPriorityObj;
        sql_AppIdPriority_Create_Select_Query(&appIdPriorityObj, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_CMF_DIA_PRIORITY_ERR_DB_ERROR;

            mysql_set_error_for_CMF_config_Reqs(&appIdPriorityObj, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        if((iReturn = mysql_CMF_AppId_Priority_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
        {
            if(iReturn != GET_CMF_DIA_PRIORITY_ERR_NO_DATA_PRESENT)
                mysql_set_error_for_CMF_config_Reqs(&appIdPriorityObj, resp, iReturn);
        }
        delete pRes;

        if(iReturn == GET_CMF_DIA_PRIORITY_ERR_NO_DATA_PRESENT)
        {
            int iCount = resp->priorities_size();
            if(!iCount)
            {
                mysql_set_error_for_CMF_config_Reqs(&appIdPriorityObj, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_CMFTrigger_resultset_to_protoBuff(sql::ResultSet *pRes, CMFTriggerResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG("%s: RowCount = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_CMF_TRIGGER_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            CMFTrigger *pCMFTrigger = resp->add_triggers();

            if(!pRes->isNull("TRIGGER_ID"))
                pCMFTrigger->set_triggerid(pRes->getInt("TRIGGER_ID"));
            if(!pRes->isNull("TRIGGER_NAME"))
                pCMFTrigger->set_trigger(pRes->getString("TRIGGER_NAME"));
            if(!pRes->isNull("TRIGGER_VALUE"))
                pCMFTrigger->set_triggervalue(pRes->getInt("TRIGGER_VALUE"));
            if(!pRes->isNull("TRIGGER_DESCRIPTION"))
                pCMFTrigger->set_description(pRes->getString("TRIGGER_DESCRIPTION"));
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Get_CMFTrigger_Config_Req(CMFTriggerReq *req, CMFTriggerResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes;

    CMFTrigger localCMFTrigger;

    sql_CmfTrigger_Create_Select_Query(&localCMFTrigger, sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        if(iReturn == DRE_DB_FAIL)
            iReturn = GET_CMF_TRIGGER_ERR_DB_ERROR;

        mysql_set_error_for_CMF_config_Reqs(&localCMFTrigger, resp, iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if((iReturn = mysql_CMFTrigger_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
    {
        delete pRes;
        mysql_set_error_for_CMF_config_Reqs(&localCMFTrigger, resp, iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_CMFAction_resultset_to_protoBuff(sql::ResultSet *pRes, CMFActionResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG("%s: RowCount = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_CMF_ACTION_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            CMFAction *pCMFAction = resp->add_actions();

            if(!pRes->isNull("ACTION_ID"))
                pCMFAction->set_actionid(pRes->getInt("ACTION_ID"));
            if(!pRes->isNull("ACTION_NAME"))
                pCMFAction->set_action(pRes->getString("ACTION_NAME"));
            if(!pRes->isNull("ACTION_DESCRIPTION"))
                pCMFAction->set_description(pRes->getString("ACTION_DESCRIPTION"));
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Get_CMFAction_Config_Req(CMFActionReq *req, CMFActionResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes;

    int iCount = req->actionnames_size();
    DLOG_DEBUG(" %s: CMFRule Req Size = %d ",__FUNCTION__,iCount);

    if(iCount)
    {
        for(int iIndex=0; iIndex<iCount; iIndex++)
        {
            string *ActionName = req->mutable_actionnames(iIndex);
            CMFAction localCMFAction;
            localCMFAction.set_action(*ActionName);

            sql_CmfAction_Create_Select_Query(&localCMFAction, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_CMF_ACTION_DB_ERROR;

                mysql_set_error_for_CMF_config_Reqs(&localCMFAction, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_CMFAction_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
            {
                delete pRes;
                mysql_set_error_for_CMF_config_Reqs(&localCMFAction, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            delete pRes;
        }
    }
    else
    {
        CMFAction localCMFAction;;

        sql_CmfAction_Create_Select_Query(&localCMFAction,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_CMF_ACTION_DB_ERROR;

            mysql_set_error_for_CMF_config_Reqs(&localCMFAction, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_CMFAction_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;
            mysql_set_error_for_CMF_config_Reqs(&localCMFAction, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_CMFLevel_resultset_to_protoBuff(sql::ResultSet *pRes, CMFLevelResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG("%s: RowCount = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_CMFLEVEL_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            CMFLevel *pCMFLevel = resp->add_levels();

            if(!pRes->isNull("LEVEL_ID"))
                pCMFLevel->set_levelid(pRes->getInt("LEVEL_ID"));
            if(!pRes->isNull("LEVEL_NAME"))
                pCMFLevel->set_level(pRes->getString("LEVEL_NAME"));
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_CMFTriggerInMapping_resultset_to_protoBuff(CMFTrigger *pCMFTrigger)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    sql::ResultSet *pRes;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};

    sql_CmfTrigger_Create_Select_Query(pCMFTrigger, sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        if(iReturn == DRE_DB_FAIL)
            iReturn = GET_CMF_TRIGGER_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    if(pRes->rowsCount() > 0)
    {
        if(pRes->next())
        {
            if(!pRes->isNull("TRIGGER_NAME"))
               pCMFTrigger->set_trigger(pRes->getString("TRIGGER_NAME"));
            if(!pRes->isNull("TRIGGER_VALUE"))
                pCMFTrigger->set_triggervalue(pRes->getInt("TRIGGER_VALUE"));
            if(!pRes->isNull("TRIGGER_DESCRIPTION"))
                pCMFTrigger->set_description(pRes->getString("TRIGGER_DESCRIPTION"));
        }
    }
    delete pRes;
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_CMFActionsforEachTrigger_resultset_to_protoBuff(CMFAction *pCMFAction)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    sql::ResultSet *pRes;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    char sStatement[MAX_STATEMENT_SIZE] = {0};

    sql_CmfAction_Create_Select_Query(pCMFAction, sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        if(iReturn == DRE_DB_FAIL)
            iReturn = GET_ACTION_FOR_TRIGGER_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    if(pRes->rowsCount() > 0)
    {
        if(pRes->next())
        {
            if(!pRes->isNull("ACTION_NAME"))
                pCMFAction->set_action(pRes->getString("ACTION_NAME"));
            if(!pRes->isNull("ACTION_DESCRIPTION"))
                pCMFAction->set_description(pRes->getString("ACTION_DESCRIPTION"));
        }
    }
    delete pRes;
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_CMFActionForTrigger_resultset_to_protoBuff(sql::ResultSet *pRes, CMFActionTriggerResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    try
    {
        DLOG_DEBUG("%s: RowCount = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_ACTION_FOR_TRIGGER_ERR_NO_MAPPING_PRESENT;
        }

        while(pRes->next())
        {
            int iMapSize=resp->mappings_size();
            DLOG_DEBUG("%s: iMapSize = %d ",__FUNCTION__,iMapSize);
            int iFlag = 0;
            for(int iIndex=0; iIndex<iMapSize; iIndex++)
            {
                CMFTriggerActionMapping *pCMFTriggerActionMapping = resp->mutable_mappings(iIndex);
                CMFTrigger* pCMFTrigger = pCMFTriggerActionMapping->mutable_trigger();

                if(!pRes->isNull("TRIGGER_ID"))
                {
                    // Add actions belongs to same trigger under previous
                    // mapping
                    if(pRes->getUInt("TRIGGER_ID") == pCMFTrigger->triggerid())
                    {
                        iFlag = 1;
                        CMFAction* pCMFAction = pCMFTriggerActionMapping->add_action();
                        if(!pRes->isNull("ACTION_ID"))
                            pCMFAction->set_actionid(pRes->getInt("ACTION_ID"));
                        // Fetch action's other elements based on ACTION_ID
                        if((iReturn = mysql_CMFActionsforEachTrigger_resultset_to_protoBuff(pCMFAction)) != DRE_DB_SUCCESS)
                        {
                            DLOG_NONE(" < %s ",__FUNCTION__);
                            return iReturn;
                        }
                    }
                }
            }

            // First iteration or Trigger id is not matching with last one
            // so add new mapping in "CMFActionTriggerResp"  and add trigger
            // and actions to respective structures.
            if(!iFlag)
            {
                CMFTriggerActionMapping *pCMFTriggerActionMapping  = resp->add_mappings();
                CMFTrigger* pCMFTrigger = pCMFTriggerActionMapping->mutable_trigger();
                if(!pRes->isNull("TRIGGER_ID"))
                    pCMFTrigger->set_triggerid(pRes->getInt("TRIGGER_ID"));
                // Fetch Trigger's other elements based on TRIGGER_ID
                if((iReturn = mysql_CMFTriggerInMapping_resultset_to_protoBuff(pCMFTrigger)) != DRE_DB_SUCCESS)
                {
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                CMFAction* pCMFAction = pCMFTriggerActionMapping->add_action();
                if(!pRes->isNull("ACTION_ID"))
                    pCMFAction->set_actionid(pRes->getInt("ACTION_ID"));
                // Fetch action's other elements based on ACTION_ID
                if((iReturn = mysql_CMFActionsforEachTrigger_resultset_to_protoBuff(pCMFAction)) != DRE_DB_SUCCESS)
                {
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
            }
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Get_Action_For_Trigger_Config_Req(CMFActionTriggerReq *req, CMFActionTriggerResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes;

    int iCount = req->triggers_size();
    DLOG_DEBUG(" %s: CMFRule Req Size = %d ",__FUNCTION__,iCount);

    if(iCount)
    {
        for(int iIndex=0; iIndex<iCount; iIndex++)
        {
            CMFTrigger *plocalCMFTrigger = req->mutable_triggers(iIndex);

            sql_CmfTriggerActionMapping_Create_Select_Query(plocalCMFTrigger, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_ACTION_FOR_TRIGGER_ERR_DB_ERROR;

                mysql_set_error_for_CMF_config_Reqs(plocalCMFTrigger, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_CMFActionForTrigger_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
            {
                delete pRes;
                mysql_set_error_for_CMF_config_Reqs(plocalCMFTrigger, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            delete pRes;
        }
    }
    else
    {
        CMFTrigger localCMFTrigger;

        sql_CmfTriggerActionMapping_Create_Select_Query(&localCMFTrigger,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_ACTION_FOR_TRIGGER_ERR_DB_ERROR;

            mysql_set_error_for_CMF_config_Reqs(&localCMFTrigger, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_CMFActionForTrigger_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;
            mysql_set_error_for_CMF_config_Reqs(&localCMFTrigger, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Get_CMFLevel_Config_Req(CMFLevelReq *req, CMFLevelResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount = req->levels_size();
    DLOG_DEBUG(" %s: CMFRule Req Size = %d ",__FUNCTION__,iCount);
    sql::ResultSet *pRes = NULL;

    if(iCount)
    {
        for(int iIndex=0; iIndex<iCount; iIndex++)
        {
            CMFLevel *plocalCMFLevel = req->mutable_levels(iIndex);

            sql_CmfLevel_Create_Select_Query(plocalCMFLevel, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_CMFLEVEL_ERR_DB_ERROR;

                mysql_set_error_for_CMF_config_Reqs(plocalCMFLevel, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_CMFLevel_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
            {
                delete pRes;
                mysql_set_error_for_CMF_config_Reqs(plocalCMFLevel, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            delete pRes;
        }
    }
    else
    {
        CMFLevel localCMFLevel;

        sql_CmfLevel_Create_Select_Query(&localCMFLevel,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_CMFLEVEL_ERR_DB_ERROR;

            mysql_set_error_for_CMF_config_Reqs(&localCMFLevel, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_CMFLevel_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;
            mysql_set_error_for_CMF_config_Reqs(&localCMFLevel, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_CongRuleConfig_resultset_to_protoBuff(sql::ResultSet *pRes, RuleConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG("%s: RowCount = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_CMFRULE_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            RuleConfig *pRuleConfig = resp->add_rules();

            if(!pRes->isNull("RULE_ID"))
                pRuleConfig->set_ruleid(pRes->getInt("RULE_ID"));
            if(!pRes->isNull("RULE_NAME"))
                pRuleConfig->set_rulename(pRes->getString("RULE_NAME"));
            if(!pRes->isNull("RULE_DESCRIPTION"))
                pRuleConfig->set_ruledescription(pRes->getString("RULE_DESCRIPTION"));
            if(!pRes->isNull("TRIGGER_ID"))
                pRuleConfig->set_trigger(pRes->getInt("TRIGGER_ID"));
            if(!pRes->isNull("CONG_LEVEL_ID"))
                pRuleConfig->set_level(pRes->getInt("CONG_LEVEL_ID"));
            if(!pRes->isNull("RULE"))
                pRuleConfig->set_rule(pRes->getString("RULE"));
            if(!pRes->isNull("ACTION"))
                pRuleConfig->set_action(pRes->getInt("ACTION"));
            if(!pRes->isNull("PRIORITY"))
                pRuleConfig->set_priority(pRes->getInt("PRIORITY"));
            if(!pRes->isNull("FILTER_STATUS"))
                pRuleConfig->set_rulestatus(pRes->getInt("FILTER_STATUS"));
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Get_CMFRules_Config_Req(RuleConfigReq *req, RuleConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    int iCount = req->rules_size();
    DLOG_DEBUG(" %s: CMFRule Req Size = %d ",__FUNCTION__,iCount);

    if(iCount)
    {
        for(int iIndex=0; iIndex<iCount; iIndex++)
        {
            RuleConfig *plocalRuleConfig = req->mutable_rules(iIndex);

            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_CongestionRules_Create_Select_Query(plocalRuleConfig, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_CMFRULE_ERR_DB_ERROR;

                mysql_set_error_for_CMF_config_Reqs(plocalRuleConfig, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_CongRuleConfig_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
            {
                delete pRes;
                mysql_set_error_for_CMF_config_Reqs(plocalRuleConfig, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            delete pRes;
        }
    }
    else
    {
        RuleConfig localRuleConfig;

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_CongestionRules_Create_Select_Query(&localRuleConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_CMFRULE_ERR_DB_ERROR;

            mysql_set_error_for_CMF_config_Reqs(&localRuleConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_CongRuleConfig_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;
            mysql_set_error_for_CMF_config_Reqs(&localRuleConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        delete pRes;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Add_CMFRule_Validation(RuleConfig *pRuleConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    if(pRuleConfig->has_rulename())
    {
        RuleConfig localRuleConfig;
        localRuleConfig.set_rulename(pRuleConfig->rulename());

        sql_CongestionRules_Create_Check_Modifcation_Query(&localRuleConfig, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_CMFRULE_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            DLOG_ERROR("Record already present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_CMFRULE_ERR_RULE_ALREADY_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Add_CMFRule_Config_Req(RuleConfigReq *req, RuleConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    int iCount = req->rules_size();

    for(int iIndex=0; iIndex<iCount; iIndex++)
    {
        RuleConfig *plocalRuleConfig = req->mutable_rules(iIndex);

        if((iReturn = mysql_Cmf_Add_CMFRule_Validation(plocalRuleConfig)) != DRE_DB_SUCCESS)
        {
            DLOG_DEBUG(" %s:%d mysql_Cmf_Add_CMFRule_Validation Failed \n",__FUNCTION__,__LINE__);
            mysql_set_error_for_CMF_config_Reqs(plocalRuleConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_CongestionRules_Create_Add_Query(plocalRuleConfig, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_CMFRULE_ERR_DB_ERROR;

                mysql_set_error_for_CMF_config_Reqs(plocalRuleConfig, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            if(iReturn == DRE_DB_SUCCESS)
            {
                RuleConfig lRuleConfig;
                lRuleConfig.set_rulename(plocalRuleConfig->rulename());
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                sql_CongestionRules_Create_Select_Query(&lRuleConfig,sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {
                    if(pRes != NULL)
                    {
                        delete pRes;
                    }

                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                    if(iReturn == DRE_DB_FAIL)
                        iReturn = ADD_CMFRULE_ERR_DB_ERROR;

                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }

                if(pRes->rowsCount() > 0)
                {
                    if(pRes->next())
                    {
                        if(!pRes->isNull("RULE_ID"))
                        {
                            plocalRuleConfig->set_ruleid(pRes->getInt("RULE_ID"));
                        }
                    }
                }
                delete pRes;
                pRes = NULL;
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Mod_CMFRule_Validation(RuleConfig *pRuleConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    if(pRuleConfig->has_rulename())
    {
        RuleConfig localRuleConfig;
        localRuleConfig.set_rulename(pRuleConfig->rulename());

        sql_CongestionRules_Create_Check_Modifcation_Query(&localRuleConfig, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_CMFRULE_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Record mot present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_CMFRULE_ERR_RULE_NOT_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Mod_CMFRule_Config_Req(RuleConfigReq *req, RuleConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    int iCount = req->rules_size();

    for(int iIndex=0; iIndex<iCount; iIndex++)
    {
        RuleConfig *plocalRuleConfig = req->mutable_rules(iIndex);

        if((iReturn = mysql_Cmf_Mod_CMFRule_Validation(plocalRuleConfig)) != DRE_DB_SUCCESS)
        {
            DLOG_DEBUG(" %s:%d mysql_Cmf_Del_CMFRule_Validation Failed \n",__FUNCTION__,__LINE__);
            mysql_set_error_for_CMF_config_Reqs(plocalRuleConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_CongestionRules_Create_Mod_Query(plocalRuleConfig, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_CMFRULE_ERR_DB_ERROR;

                mysql_set_error_for_CMF_config_Reqs(plocalRuleConfig, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            if(iReturn == DRE_DB_SUCCESS)
            {
                RuleConfig lRuleConfig;
                lRuleConfig.set_rulename(plocalRuleConfig->rulename());
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                sql_CongestionRules_Create_Select_Query(&lRuleConfig,sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {
                    if(pRes != NULL)
                    {
                        delete pRes;
                    }

                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                    if(iReturn == DRE_DB_FAIL)
                        iReturn = MOD_CMFRULE_ERR_DB_ERROR;

                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }

                if(pRes->rowsCount() > 0)
                {
                    if(pRes->next())
                    {
                        if(!pRes->isNull("RULE_ID"))
                        {
                            plocalRuleConfig->set_ruleid(pRes->getInt("RULE_ID"));
                        }
                    }
                }
                delete pRes;
                pRes = NULL;
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Del_CMFRule_Validation(RuleConfig *pRuleConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    if(pRuleConfig->has_rulename())
    {
        RuleConfig localRuleConfig;
        localRuleConfig.set_rulename(pRuleConfig->rulename());

        sql_CongestionRules_Create_Check_Modifcation_Query(&localRuleConfig, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_CMFRULE_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_CMFRULE_ERR_DB_ERROR;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Record not present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_CMFRULE_ERR_RULE_NOT_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Del_CMFRule_Config_Req(RuleConfigReq *req, RuleConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int iCount = req->rules_size();
    DLOG_DEBUG(" %s:%d iCount =%d \n",__FUNCTION__,__LINE__,iCount);

    for(int iIndex=0; iIndex<iCount; iIndex++)
    {
        RuleConfig *plocalRuleConfig = req->mutable_rules(iIndex);

        if((iReturn = mysql_Cmf_Del_CMFRule_Validation(plocalRuleConfig)) != DRE_DB_SUCCESS)
        {
            DLOG_DEBUG(" %s:%d mysql_Cmf_Del_CMFRule_Validation Failed \n",__FUNCTION__,__LINE__);
            mysql_set_error_for_CMF_config_Reqs(plocalRuleConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            /*
             *  Set Trigger-Id in the request.
             */
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_CongestionRules_Create_Select_Query(plocalRuleConfig, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_CMFRULE_ERR_DB_ERROR;

                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if(pRes->rowsCount() > 0)
            {
                if(pRes->next())
                {
                    if(!pRes->isNull("TRIGGER_ID"))
                    {
                        plocalRuleConfig->set_trigger(pRes->getInt("TRIGGER_ID"));
                    }
                }
            }
            delete pRes;
            pRes = NULL;

            /*
             *  Delete the Rule from Database.
             */
            sql_CongestionRules_Create_Delete_Query(plocalRuleConfig, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_CMFRULE_ERR_DB_ERROR;

                mysql_set_error_for_CMF_config_Reqs(plocalRuleConfig, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Set_CMFRuleStatus_Validation(RuleConfig *pRuleConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    if(pRuleConfig->has_rulename())
    {
        RuleConfig localRuleConfig;
        localRuleConfig.set_rulename(pRuleConfig->rulename());

        sql_CongestionRules_Create_Check_Modifcation_Query(&localRuleConfig, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_TRANSFORM_PLUGIN_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_CMFRULE_ERR_DB_ERROR;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Record not present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_CMFRULE_STATUS_ERR_RULE_NOT_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Set_CMFRuleStatus_Config_Req(RuleConfigReq *req, RuleConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int iCount = req->rules_size();
    DLOG_DEBUG(" %s:%d No of Rules = %d\n",__FUNCTION__,__LINE__,iCount);

    for(int iIndex=0; iIndex<iCount; iIndex++)
    {
        RuleConfig *plocalRuleConfig = req->mutable_rules(iIndex);

        if((iReturn = mysql_Cmf_Set_CMFRuleStatus_Validation(plocalRuleConfig)) != DRE_DB_SUCCESS)
        {
            DLOG_DEBUG(" %s:%d mysql_Cmf_Set_CMFRuleStatus_Validation Failed \n",__FUNCTION__,__LINE__);
            mysql_set_error_for_CMF_config_Reqs(plocalRuleConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            /*
             *  Modify the Rule Status in Database.
             */
            sql_CongestionRules_Create_Mod_Query(plocalRuleConfig, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_CMFRULE_ERR_DB_ERROR;

                mysql_set_error_for_CMF_config_Reqs(plocalRuleConfig, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            /*
             *  Set Trigger-Id in the request.
             */
            if(iReturn == DRE_DB_SUCCESS)
            {
                RuleConfig lRuleConfig;
                lRuleConfig.set_rulename(plocalRuleConfig->rulename());
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                sql_CongestionRules_Create_Select_Query(&lRuleConfig, sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {
                    if(pRes != NULL)
                    {
                        delete pRes;
                    }

                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                    if(iReturn == DRE_DB_FAIL)
                        iReturn = MOD_CMFRULE_ERR_DB_ERROR;

                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_CMFRULE_ERR_DB_ERROR;
                }

                if(pRes->rowsCount() > 0)
                {
                    if(pRes->next())
                    {
                        if(!pRes->isNull("TRIGGER_ID"))
                        {
                            plocalRuleConfig->set_trigger(pRes->getInt("TRIGGER_ID"));
                        }
                    }
                }
                delete pRes;
                pRes = NULL;
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Add_Priority_Config_Req(PriorityConfigReq *req, PriorityConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    int iCount = req->priorities_size();

    for(int iIndex=0; iIndex<iCount; iIndex++)
    {
        PriorityConfig *pPriorityConfig = req->mutable_priorities(iIndex);
        int sizeCCPri = pPriorityConfig->ccpriorities_size();
        int sizeAppId = pPriorityConfig->apppriorities_size();

        /******************* Add CC Priority*******************/
        if(sizeCCPri)
        {
            for(int iIndex = 0; iIndex<sizeCCPri; iIndex++)
            {
                CCPriority *pCCPriority = pPriorityConfig->mutable_ccpriorities(iIndex);
                sql_CCPriority_Create_Check_Modifcation_Query(pCCPriority, sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {
                    if(pRes != NULL)
                    {
                        delete pRes;
                    }

                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                    if(iReturn == DRE_DB_FAIL)
                        iReturn = ADD_CMF_DIA_PRIORITY_ERR_DB_ERROR;
                    mysql_set_error_for_CMF_config_Reqs(pCCPriority, resp, iReturn);

                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return DEL_CMFRULE_ERR_DB_ERROR;
                }
                memset(sStatement,0,MAX_STATEMENT_SIZE);

                if(pRes->rowsCount() > 0)
                {
                    delete pRes;
                    DLOG_ERROR("Record already present");
                    iReturn = ADD_CMF_DIA_PRIORITY_ERR_CC_ALREADY_PRESENT;
                    mysql_set_error_for_CMF_config_Reqs(pCCPriority, resp, iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                else // Add
                {
                    delete pRes;
                    sql_CCPriority_Create_Add_Query(pCCPriority, sStatement);
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == DRE_DB_FAIL)
                            iReturn = ADD_CMF_DIA_PRIORITY_ERR_DB_ERROR;

                        mysql_set_error_for_CMF_config_Reqs(pCCPriority, resp, iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                }
            }
        }

        /******************* Add AppId Priority*******************/
        else if(sizeAppId)
        {
            for(int iIndex = 0; iIndex<sizeAppId; iIndex++)
            {
                AppIdPriority *pAppIdPriority = pPriorityConfig->mutable_apppriorities(iIndex);
                sql_AppIdPriority_Create_Check_Modifcation_Query(pAppIdPriority, sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {
                    if(pRes != NULL)
                    {
                        delete pRes;
                    }

                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                    if(iReturn == DRE_DB_FAIL)
                        iReturn = ADD_CMF_DIA_PRIORITY_ERR_DB_ERROR;
                    mysql_set_error_for_CMF_config_Reqs(pAppIdPriority, resp, iReturn);

                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                memset(sStatement,0,MAX_STATEMENT_SIZE);

                if(pRes->rowsCount() > 0)
                {
                    delete pRes;
                    DLOG_ERROR("Record already present");
                    iReturn = ADD_CMF_DIA_PRIORITY_ERR_APPID_ALREADY_PRESENT;
                    mysql_set_error_for_CMF_config_Reqs(pAppIdPriority, resp, iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                else
                {
                    delete pRes;
                    sql_AppIdPriority_Create_Add_Query(pAppIdPriority, sStatement);
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == DRE_DB_FAIL)
                            iReturn = ADD_CMF_DIA_PRIORITY_ERR_DB_ERROR;

                        mysql_set_error_for_CMF_config_Reqs(pAppIdPriority, resp, iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                }
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Mod_Priority_Config_Req(PriorityConfigReq *req, PriorityConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    int iCount = req->priorities_size();

    for(int iIndex=0; iIndex<iCount; iIndex++)
    {
        PriorityConfig *pPriorityConfig = req->mutable_priorities(iIndex);
        int sizeCCPri = pPriorityConfig->ccpriorities_size();
        int sizeAppId = pPriorityConfig->apppriorities_size();

        /******************* Modify CC Priority*******************/
        if(sizeCCPri)
        {
            for(int iIndex = 0; iIndex<sizeCCPri; iIndex++)
            {
                CCPriority *pCCPriority = pPriorityConfig->mutable_ccpriorities(iIndex);
                sql_CCPriority_Create_Check_Modifcation_Query(pCCPriority, sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {
                    if(pRes != NULL)
                    {
                        delete pRes;
                    }

                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                    if(iReturn == DRE_DB_FAIL)
                        iReturn = MOD_CMF_DIA_PRIORITY_ERR_DB_ERROR;
                    mysql_set_error_for_CMF_config_Reqs(pCCPriority, resp, iReturn);

                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                memset(sStatement,0,MAX_STATEMENT_SIZE);

                if(pRes->rowsCount() == 0)
                {
                    delete pRes;
                    DLOG_ERROR("Record not present");
                    iReturn = MOD_CMF_DIA_PRIORITY_ERR_CC_NOT_CONFIGURED;
                    mysql_set_error_for_CMF_config_Reqs(pCCPriority, resp, iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                else // Mod
                {
                    delete pRes;
                    sql_CCPriority_Create_Mod_Query(pCCPriority, sStatement);
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == DRE_DB_FAIL)
                            iReturn = MOD_CMF_DIA_PRIORITY_ERR_DB_ERROR;

                        mysql_set_error_for_CMF_config_Reqs(pCCPriority, resp, iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                }
            }
        }

        /******************* Modify AppId Priority*******************/
        else if(sizeAppId)
        {
            for(int iIndex = 0; iIndex<sizeAppId; iIndex++)
            {
                AppIdPriority *pAppIdPriority = pPriorityConfig->mutable_apppriorities(iIndex);
                sql_AppIdPriority_Create_Check_Modifcation_Query(pAppIdPriority, sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {
                    if(pRes != NULL)
                    {
                        delete pRes;
                    }

                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                    if(iReturn == DRE_DB_FAIL)
                        iReturn = MOD_CMF_DIA_PRIORITY_ERR_DB_ERROR;
                    mysql_set_error_for_CMF_config_Reqs(pAppIdPriority, resp, iReturn);

                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                memset(sStatement,0,MAX_STATEMENT_SIZE);

                if(pRes->rowsCount() == 0)
                {
                    delete pRes;
                    DLOG_ERROR("Record not present");
                    iReturn = MOD_CMF_DIA_PRIORITY_ERR_APPID_NOT_CONFIGURED;
                    mysql_set_error_for_CMF_config_Reqs(pAppIdPriority, resp, iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                else
                {
                    delete pRes;
                    sql_AppIdPriority_Create_Mod_Query(pAppIdPriority, sStatement);
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == DRE_DB_FAIL)
                            iReturn = MOD_CMF_DIA_PRIORITY_ERR_DB_ERROR;

                        mysql_set_error_for_CMF_config_Reqs(pAppIdPriority, resp, iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                }
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Cmf_Del_Priority_Config_Req(PriorityConfigReq *req, PriorityConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;
    int iCount = req->priorities_size();

    for(int iIndex=0; iIndex<iCount; iIndex++)
    {
        PriorityConfig *pPriorityConfig = req->mutable_priorities(iIndex);
        int sizeCCPri = pPriorityConfig->ccpriorities_size();
        int sizeAppId = pPriorityConfig->apppriorities_size();

        /******************* Delete CC Priority*******************/
        if(sizeCCPri)
        {
            for(int iIndex = 0; iIndex<sizeCCPri; iIndex++)
            {
                CCPriority *pCCPriority = pPriorityConfig->mutable_ccpriorities(iIndex);
                sql_CCPriority_Create_Check_Modifcation_Query(pCCPriority, sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {
                    if(pRes != NULL)
                    {
                        delete pRes;
                    }

                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                    if(iReturn == DRE_DB_FAIL)
                        iReturn = DEL_CMF_DIA_PRIORITY_ERR_DB_ERROR;
                    mysql_set_error_for_CMF_config_Reqs(pCCPriority, resp, iReturn);

                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                memset(sStatement,0,MAX_STATEMENT_SIZE);

                if(pRes->rowsCount() == 0)
                {
                    delete pRes;
                    DLOG_ERROR("Record not present");
                    iReturn = DEL_CMF_DIA_PRIORITY_ERR_CC_NOT_CONFIGURED;
                    mysql_set_error_for_CMF_config_Reqs(pCCPriority, resp, iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                else // Delete
                {
                    delete pRes;
                    sql_CCPriority_Create_Delete_Query(pCCPriority, sStatement);
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == DRE_DB_FAIL)
                            iReturn = DEL_CMF_DIA_PRIORITY_ERR_DB_ERROR;

                        mysql_set_error_for_CMF_config_Reqs(pCCPriority, resp, iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                }
            }
        }

        /******************* Delete AppId Priority*******************/
        else if(sizeAppId)
        {
            for(int iIndex = 0; iIndex<sizeAppId; iIndex++)
            {
                AppIdPriority *pAppIdPriority = pPriorityConfig->mutable_apppriorities(iIndex);
                sql_AppIdPriority_Create_Check_Modifcation_Query(pAppIdPriority, sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {
                    if(pRes != NULL)
                    {
                        delete pRes;
                    }

                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                    if(iReturn == DRE_DB_FAIL)
                        iReturn = DEL_CMF_DIA_PRIORITY_ERR_DB_ERROR;
                    mysql_set_error_for_CMF_config_Reqs(pAppIdPriority, resp, iReturn);

                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                memset(sStatement,0,MAX_STATEMENT_SIZE);

                if(pRes->rowsCount() == 0)
                {
                    delete pRes;
                    DLOG_ERROR("Record not present");
                    iReturn = DEL_CMF_DIA_PRIORITY_ERR_APPID_NOT_CONFIGURED;
                    mysql_set_error_for_CMF_config_Reqs(pAppIdPriority, resp, iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                else
                {
                    delete pRes;
                    sql_AppIdPriority_Create_Delete_Query(pAppIdPriority, sStatement);
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == DRE_DB_FAIL)
                            iReturn = DEL_CMF_DIA_PRIORITY_ERR_DB_ERROR;

                        mysql_set_error_for_CMF_config_Reqs(pAppIdPriority, resp, iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                }
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}
