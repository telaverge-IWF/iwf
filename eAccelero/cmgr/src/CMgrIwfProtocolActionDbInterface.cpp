/* *C-*-***********************************
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


#include <CMgrIwfDbInterface.h>

using namespace std;
extern std::map<int,std::string> iwfErrorMap;

void CMgrIwfDbInterface::mysql_set_error_for_IWFProtocolAction_Config_Reqs(IwfProtocolActionConfig *pIwfProtocolActionConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(pIwfProtocolActionConfig->has_actionrulename())
        err->add_variables(pIwfProtocolActionConfig->actionrulename());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFEventType_Config_Reqs(CallScenario *pCallScenario, std::string RuleName, IWFCfgResp *resp,DbStatus_e iReturn, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(RuleName.c_str() != NULL)
        err->add_variables(RuleName.c_str());
    
    if(pCallScenario->has_call_typename())
        err->add_variables(pCallScenario->call_typename().c_str());

    if(pCallScenario->eventtypeval_size() > iIndex && iIndex > -1)
    {
        EventType *pEventType = pCallScenario->mutable_eventtypeval(iIndex);

        if(pEventType->has_eventtypename())
            err->add_variables(pEventType->eventtypename());
    }

}

void CMgrIwfDbInterface::mysql_set_error_for_IWFEventTypeDetails_Config_Reqs(EventType *pEventType, std::string RuleName, std::string callScenario, IWFCfgResp *resp,DbStatus_e iReturn, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(RuleName.c_str() != NULL)
        err->add_variables(RuleName.c_str());
    
    if(callScenario.c_str() != NULL)
        err->add_variables(callScenario.c_str());

    if(pEventType->has_eventtypename())
        err->add_variables(pEventType->eventtypename());

    ArmData* pArmData = NULL;
    if(pEventType->armdatval_size() > iIndex && iIndex > -1)
    {
        pArmData = pEventType->mutable_armdatval(iIndex);

        if(pArmData->has_monitormode())
        {
            err->add_variables(pArmData->monitormode());
        }

        if(pArmData->has_legid())
        {
            err->add_variables(pArmData->legid());
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFCallScenario_Config_Reqs(MsgDet *pMsgDet,std::string RuleName,IWFCfgResp *resp,DbStatus_e iReturn, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(RuleName.c_str() != NULL)
        err->add_variables(RuleName.c_str());

    CallScenario* pCallScenario = NULL;

    if(pMsgDet->callscenarioval_size() > iIndex && iIndex > -1) 
    {   
        pCallScenario = pMsgDet->mutable_callscenarioval(iIndex);
        if(pCallScenario->has_call_typename())
        {   
            err->add_variables(pCallScenario->call_typename().c_str());
        }
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfProtocolAction_Mod_Config_Reqs(IwfProtocolActionsConfig *pIwfProtocolActionsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfProtocolActionsConfig->iwfprotactioncfgval_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(MOD_PROTOCOL_ACTION_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[MOD_PROTOCOL_ACTION_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfProtocolActionConfig *pIwfProtocolActionConfig= pIwfProtocolActionsConfig->mutable_iwfprotactioncfgval(i);
        if(pIwfProtocolActionConfig->has_actionrulename())
        {
            std::string RuleName = pIwfProtocolActionConfig->actionrulename().c_str();

            sql_IWFProtocolAction_Create_Check_Modifcation_Query(pIwfProtocolActionConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_PROTOCOL_ACTION_ERR_DB_ERROR;

                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                delete pRes;
                DLOG_ERROR("Record Not Present");   
                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,MOD_PROTOCOL_ACTION_ERR_RULE_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return MOD_PROTOCOL_ACTION_ERR_RULE_NOT_PRESENT;
            }

            if(pIwfProtocolActionConfig->msgdetval_size())
            {
                int msgdetsize = pIwfProtocolActionConfig->msgdetval_size();

                for (int j = 0; j < msgdetsize; j++)
                {
                    MsgDet *pMsgDet = pIwfProtocolActionConfig->mutable_msgdetval(j);

                    if(pMsgDet->callscenarioval_size())
                    {
                        int callscenarioSize = pMsgDet->callscenarioval_size();
                        for (int k=0 ; k < callscenarioSize; k++)
                        {
                            //Insert of CallScenario
                            CallScenario *pCallScenario = pMsgDet->mutable_callscenarioval(k);
                            string callScenario = pCallScenario->call_typename();
                            memset(sStatement,0,MAX_STATEMENT_SIZE);

                            sql_IWFCallScenarioMapping_Create_Check_Modifcation_Query(pMsgDet, RuleName, sStatement, k);

                            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                            {
                                if(pRes != NULL)    
                                {
                                    delete pRes;
                                }
                                DLOG_ERROR("Query Execution Failed %s",sStatement);

                                if(iReturn == IWF_DB_FAIL)
                                    iReturn = ADD_PROTOCOL_ACTION_ERR_DB_ERROR;

                                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                                DLOG_DEBUG("iReturn = %d",iReturn);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return iReturn;
                            }

                            memset(sStatement,0,MAX_STATEMENT_SIZE);

                            if(pRes->rowsCount() == 0) // ADD
                            {
                                sql_IWFCallScenarioMapping_Create_Add_Query(pMsgDet, RuleName, sStatement, k);

                                delete pRes;
                                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                {
                                    DLOG_ERROR("Query Execution Failed %s",sStatement);
                                    if(iReturn == IWF_DB_FAIL)
                                        iReturn = MOD_PROTOCOL_ACTION_ERR_DB_ERROR;

                                    mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return iReturn;
                                }
                            }
                            
                            if(pCallScenario->eventtypeval_size())
                            {
                                // Insert of EventType for specific call scenario
                                int eventtype_Size = pCallScenario->eventtypeval_size();
                                for (int l = 0; l < eventtype_Size; l++)
                                {
                                    EventType *pEventType = pCallScenario->mutable_eventtypeval(l);
                                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                                    sql_IWFEventTypeMapping_Create_Check_Modifcation_Query(pCallScenario, RuleName, sStatement, l);

                                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                    {
                                        if(pRes != NULL)    
                                        {
                                            delete pRes;
                                        }
                                        DLOG_ERROR("Query Execution Failed %s",sStatement);

                                        if(iReturn == IWF_DB_FAIL)
                                            iReturn = MOD_PROTOCOL_ACTION_ERR_DB_ERROR;

                                        mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                                        DLOG_DEBUG("iReturn = %d",iReturn);
                                        DLOG_NONE(" < %s ",__FUNCTION__);
                                        return iReturn;
                                    }

                                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                                    if(pRes->rowsCount() == 0) // ADD
                                    {
                                        sql_IWFEventTypeMapping_Create_Add_Query(pCallScenario, RuleName, sStatement, l);

                                        delete pRes;
                                        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                        {
                                            DLOG_ERROR("Query Execution Failed %s",sStatement);
                                            if(iReturn == IWF_DB_FAIL)
                                                iReturn = MOD_PROTOCOL_ACTION_ERR_DB_ERROR;

                                            mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);
                                            DLOG_DEBUG("iReturn = %d",iReturn);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return iReturn;
                                        }
                                    }

                                    if(pEventType->armdatval_size())
                                    {
                                        //Insert of EventspecificData
                                        int armDataSize = pEventType->armdatval_size();
                                        for(int m = 0; m < armDataSize; m++)
                                        {
                                            sql_IWFEventTypeDetails_Create_Check_Modifcation_Query(pEventType, RuleName, callScenario, sStatement, m);

                                            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                            {
                                                if(pRes != NULL)    
                                                {
                                                    delete pRes;
                                                }
                                                DLOG_ERROR("Query Execution Failed %s",sStatement);

                                                if(iReturn == IWF_DB_FAIL)
                                                    iReturn = MOD_PROTOCOL_ACTION_ERR_DB_ERROR;

                                                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                                                DLOG_DEBUG("iReturn = %d",iReturn);
                                                DLOG_NONE(" < %s ",__FUNCTION__);
                                                return iReturn;
                                            }

                                            memset(sStatement,0,MAX_STATEMENT_SIZE);

                                            if(pRes->rowsCount() == 0) // ADD
                                            {
                                                sql_IWFEventTypeDetails_Create_Add_Query(pEventType, RuleName, callScenario, sStatement, m);
                                            }
                                            else // MOD
                                            {
                                                delete pRes;
                                                DLOG_ERROR("Record EventType Details Already Present");
                                                mysql_set_error_for_IWFEventTypeDetails_Config_Reqs(pEventType, RuleName, callScenario, resp, MOD_PROTOCOL_ACTION_ERR_CALL_SCENARIO_EVENT_TYPE_DETAILS_ALREADY_PRESENT, m);
                                                    
                                                DLOG_NONE(" < %s ",__FUNCTION__);
                                                return MOD_PROTOCOL_ACTION_ERR_CALL_SCENARIO_EVENT_TYPE_DETAILS_ALREADY_PRESENT;
                                            }

                                            delete pRes;
                                            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                            {
                                                DLOG_ERROR("Query Execution Failed %s",sStatement);
                                                if(iReturn == IWF_DB_FAIL)
                                                    iReturn = MOD_PROTOCOL_ACTION_ERR_DB_ERROR;

                                                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);
                                                DLOG_DEBUG("iReturn = %d",iReturn);
                                                DLOG_NONE(" < %s ",__FUNCTION__);
                                                return iReturn;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                    }
                }
            }
        }
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfProtocolAction_Del_Config_Reqs(IwfProtocolActionsConfig *pIwfProtocolActionsConfig,IWFCfgResp *resp,int OperId)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfProtocolActionsConfig->iwfprotactioncfgval_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(DEL_PROTOCOL_ACTION_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_PROTOCOL_ACTION_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfProtocolActionConfig *pIwfProtocolActionConfig= pIwfProtocolActionsConfig->mutable_iwfprotactioncfgval(i);
        if(pIwfProtocolActionConfig->has_actionrulename())
        {
            std::string RuleName = pIwfProtocolActionConfig->actionrulename().c_str();

            sql_IWFProtocolAction_Create_Check_Modifcation_Query(pIwfProtocolActionConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_PROTOCOL_ACTION_ERR_DB_ERROR;

                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                delete pRes;
                DLOG_ERROR("Record Not Present");   
                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,DEL_PROTOCOL_ACTION_ERR_RULE_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_PROTOCOL_ACTION_ERR_RULE_NOT_PRESENT;
            }
            else if(OperId == DEL_IWF_PROT_ACTIONS)
            {
                //Validate if ProActionRule is default one which is not allowed to delete
                if(!strcmp(pIwfProtocolActionConfig->actionrulename().c_str(),"default-rrb-rule"))
                {
                    DLOG_ERROR("Default ProActionRule Not allowed to delete");   
                    mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,
                            DEL_PROTOCOL_ACTION_ERR_DEFAULT_RRB_RULE_NOT_ALLOWED_TO_DELETE);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return DEL_PROTOCOL_ACTION_ERR_DEFAULT_RRB_RULE_NOT_ALLOWED_TO_DELETE;
                }
                //Validation if ProActionRule is part of TranslatorRule, dont allow to delete
                IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfig;
                LocalIwfTranslatorRuleConfig.set_proactionrulename(pIwfProtocolActionConfig->actionrulename());
                sql_IWFTranslatorRule_Create_Select_Query(&LocalIwfTranslatorRuleConfig, sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                {
                    if(pRes != NULL)    
                    {
                        delete pRes;
                    }
                    DLOG_ERROR("Query Execution Failed %s",sStatement);

                    if(iReturn == IWF_DB_FAIL)
                        iReturn = DEL_PROTOCOL_ACTION_ERR_DB_ERROR;

                    mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                    DLOG_DEBUG("iReturn = %d",iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }

                memset(sStatement,0,MAX_STATEMENT_SIZE);

                if(pRes->rowsCount() > 0) // ADD
                {
                    delete pRes;
                    DLOG_ERROR("ProActionRule part of Translator Rule");   
                    mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,
                            DEL_PROTOCOL_ACTION_ERR_RULE_PART_OF_TRANSLATOR_RULE);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return DEL_PROTOCOL_ACTION_ERR_RULE_PART_OF_TRANSLATOR_RULE;
                }

                sql_IWFProtocolAction_Create_Delete_Query(pIwfProtocolActionConfig, sStatement);
                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                {
                    DLOG_ERROR("Query Execution Failed %s",sStatement);
                    if(iReturn == IWF_DB_FAIL)
                        iReturn = DEL_PROTOCOL_ACTION_ERR_DB_ERROR;

                    mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,DEL_PROTOCOL_ACTION_ERR_DB_ERROR);
                    DLOG_DEBUG("iReturn = %d",iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if(pIwfProtocolActionConfig->msgdetval_size())
            {
                int msgdetsize = pIwfProtocolActionConfig->msgdetval_size();

                for (int j = 0; j < msgdetsize; j++)
                {
                    MsgDet *pMsgDet = pIwfProtocolActionConfig->mutable_msgdetval(j);

                    if(pMsgDet->callscenarioval_size())
                    {
                        int callscenarioSize = pMsgDet->callscenarioval_size();
                        for (int k=0 ; k < callscenarioSize; k++)
                        {
                            CallScenario *pCallScenario = pMsgDet->mutable_callscenarioval(k);
                            string callScenario = pCallScenario->call_typename();
                            memset(sStatement,0,MAX_STATEMENT_SIZE);

                            sql_IWFCallScenarioMapping_Create_Check_Modifcation_Query(pMsgDet, RuleName, sStatement, k);

                            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                            {
                                if(pRes != NULL)    
                                {
                                    delete pRes;
                                }
                                DLOG_ERROR("Query Execution Failed %s",sStatement);

                                if(iReturn == IWF_DB_FAIL)
                                    iReturn = DEL_PROTOCOL_ACTION_ERR_DB_ERROR;

                                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                                DLOG_DEBUG("iReturn = %d",iReturn);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return iReturn;
                            }

                            memset(sStatement,0,MAX_STATEMENT_SIZE);

                            if(pRes->rowsCount() == 0) // ADD
                            {
                                delete pRes;
                                DLOG_ERROR("CallScenario Not Present");   
                                mysql_set_error_for_IWFCallScenario_Config_Reqs(pMsgDet, RuleName, resp,DEL_PROTOCOL_ACTION_ERR_CALL_SCENARIO_NOT_PRESENT, k);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return DEL_PROTOCOL_ACTION_ERR_CALL_SCENARIO_NOT_PRESENT;
                            }
                            else if(OperId == DEL_IWF_CALL_SCENARIO)
                            {
                                if(pRes != NULL)
                                    delete pRes;
                                pRes = NULL;

                                sql_IWFCallScenarioMapping_Create_Delete_Query(pMsgDet, RuleName, sStatement, k);
                                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                {
                                    DLOG_ERROR("Query Execution Failed %s",sStatement);
                                    if(iReturn == IWF_DB_FAIL)
                                        iReturn = DEL_PROTOCOL_ACTION_ERR_DB_ERROR;

                                    mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,DEL_PROTOCOL_ACTION_ERR_DB_ERROR);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return iReturn;
                                }
                                //check if No callscenarios are associated to this rule
                                sql_IWFCallScenarioMapping_Create_Check_Modifcation_Query(pMsgDet, RuleName, sStatement, -1);

                                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                {
                                    if(pRes != NULL)    
                                    {
                                        delete pRes;
                                    }
                                    DLOG_ERROR("Query Execution Failed %s",sStatement);

                                    if(iReturn == IWF_DB_FAIL)
                                        iReturn = DEL_PROTOCOL_ACTION_ERR_DB_ERROR;

                                    mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return iReturn;
                                }

                                memset(sStatement,0,MAX_STATEMENT_SIZE);

                                if(pRes->rowsCount() == 0) // ADD
                                {
                                    delete pRes;
                                    pRes = NULL;
                                    DLOG_DEBUG("No call Scenarios present for rule");
                                    mysql_set_error_for_IWFCallScenario_Config_Reqs(pMsgDet, RuleName, resp,DEL_PROTOCOL_ACTION_ERR_LAST_CALL_SCENARIO_NOT_ALLOWED_TO_DELETE, k);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return DEL_PROTOCOL_ACTION_ERR_LAST_CALL_SCENARIO_NOT_ALLOWED_TO_DELETE;
                                }
                                delete pRes;
                                pRes = NULL;
                                DLOG_DEBUG("iReturn = %d",iReturn);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return iReturn;
                            }
                            if(pRes != NULL)
                                delete pRes;
                            pRes = NULL;
                            if(pCallScenario->eventtypeval_size())
                            {
                                int eventtype_Size = pCallScenario->eventtypeval_size();
                                for (int l = 0; l < eventtype_Size; l++)
                                {
                                    EventType *pEventType = pCallScenario->mutable_eventtypeval(l);
                                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                                    sql_IWFEventTypeMapping_Create_Check_Modifcation_Query(pCallScenario, RuleName, sStatement, l);

                                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                    {
                                        if(pRes != NULL)    
                                        {
                                            delete pRes;
                                        }
                                        DLOG_ERROR("Query Execution Failed %s",sStatement);

                                        if(iReturn == IWF_DB_FAIL)
                                            iReturn = DEL_PROTOCOL_ACTION_ERR_DB_ERROR;

                                        mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                                        DLOG_DEBUG("iReturn = %d",iReturn);
                                        DLOG_NONE(" < %s ",__FUNCTION__);
                                        return iReturn;
                                    }

                                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                                    if(pRes->rowsCount() == 0) // ADD
                                    {
                                        if(pRes != NULL)    
                                            delete pRes;
                                        DLOG_ERROR("EventType Not Present");
                                        mysql_set_error_for_IWFEventType_Config_Reqs(pCallScenario, RuleName, resp, DEL_PROTOCOL_ACTION_ERR_EVENT_TYPE_NOT_PRESENT, l);
                                        DLOG_NONE(" < %s ",__FUNCTION__);
                                        return DEL_PROTOCOL_ACTION_ERR_EVENT_TYPE_NOT_PRESENT;
                                    }
                                    else if(OperId == DEL_IWF_EVENT_TYPE)
                                    {
                                        if(pRes != NULL)
                                            delete pRes;
                                        pRes = NULL;
                                        sql_IWFEventTypeMapping_Create_Delete_Query(pCallScenario, RuleName, sStatement, l);
                                        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                        {
                                            DLOG_ERROR("Query Execution Failed %s",sStatement);
                                            if(iReturn == IWF_DB_FAIL)
                                                iReturn = DEL_PROTOCOL_ACTION_ERR_DB_ERROR;

                                            mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,DEL_PROTOCOL_ACTION_ERR_DB_ERROR);
                                            DLOG_DEBUG("iReturn = %d",iReturn);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return iReturn;
                                        }
                                        //check if No events are associated to this callscenario
                                        sql_IWFEventTypeMapping_Create_Check_Modifcation_Query(pCallScenario, RuleName, sStatement, -1);

                                        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                        {
                                            if(pRes != NULL)    
                                            {
                                                delete pRes;
                                            }
                                            DLOG_ERROR("Query Execution Failed %s",sStatement);

                                            if(iReturn == IWF_DB_FAIL)
                                                iReturn = DEL_PROTOCOL_ACTION_ERR_DB_ERROR;

                                            mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                                            DLOG_DEBUG("iReturn = %d",iReturn);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return iReturn;
                                        }

                                        memset(sStatement,0,MAX_STATEMENT_SIZE);

                                        if(pRes->rowsCount() == 0) // ADD
                                        {
                                            if(pRes != NULL)
                                                delete pRes;
                                            pRes = NULL;
                                            DLOG_DEBUG("CallScenatio not having any EventTypes");
                                            mysql_set_error_for_IWFEventType_Config_Reqs(pCallScenario, RuleName, resp, DEL_PROTOCOL_ACTION_ERR_LAST_EVENT_TYPE_NOT_ALLOWED_TO_DELETE, l);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return DEL_PROTOCOL_ACTION_ERR_LAST_EVENT_TYPE_NOT_ALLOWED_TO_DELETE;
                                        }
                                        if(pRes != NULL)
                                            delete pRes;
                                        pRes = NULL;
                                        DLOG_DEBUG("iReturn = %d",iReturn);
                                        DLOG_NONE(" < %s ",__FUNCTION__);
                                        return iReturn;
                                    }
                                    if(pRes != NULL)
                                        delete pRes;
                                    pRes = NULL;

                                    if(pEventType->armdatval_size())
                                    {
                                        int armDataSize = pEventType->armdatval_size();
                                        for(int m = 0; m < armDataSize; m++)
                                        {
                                            sql_IWFEventTypeDetails_Create_Check_Modifcation_Query(pEventType, RuleName, callScenario, sStatement, m);

                                            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                            {
                                                if(pRes != NULL)    
                                                {
                                                    delete pRes;
                                                }
                                                DLOG_ERROR("Query Execution Failed %s",sStatement);

                                                if(iReturn == IWF_DB_FAIL)
                                                    iReturn = DEL_PROTOCOL_ACTION_ERR_DB_ERROR;

                                                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                                                DLOG_DEBUG("iReturn = %d",iReturn);
                                                DLOG_NONE(" < %s ",__FUNCTION__);
                                                return iReturn;
                                            }

                                            memset(sStatement,0,MAX_STATEMENT_SIZE);
                                            if(pRes->rowsCount() == 0) // ADD
                                            {
                                                delete pRes;
                                                DLOG_ERROR("EventType Details Not Present");   
                                                mysql_set_error_for_IWFEventTypeDetails_Config_Reqs(pEventType, RuleName, callScenario, resp, DEL_PROTOCOL_ACTION_ERR_EVENT_TYPE_DETAILS_NOT_PRESENT, m);
                                                DLOG_NONE(" < %s ",__FUNCTION__);
                                                return DEL_PROTOCOL_ACTION_ERR_EVENT_TYPE_DETAILS_NOT_PRESENT;
                                            }
                                            else if(OperId == DEL_IWF_EVENT_TYPE_CONFIG)
                                            {
                                                if(pRes != NULL)
                                                    delete pRes;
                                                pRes = NULL;
                                                sql_IWFEventTypeDetails_Create_Delete_Query(pEventType, RuleName, callScenario, sStatement, m);
                                                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                                {
                                                    DLOG_ERROR("Query Execution Failed %s",sStatement);
                                                    if(iReturn == IWF_DB_FAIL)
                                                        iReturn = DEL_PROTOCOL_ACTION_ERR_DB_ERROR;

                                                    mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,DEL_PROTOCOL_ACTION_ERR_DB_ERROR);
                                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                                    return iReturn;
                                                }
                                                //delete Event Type if no sub details are present
                                                memset(sStatement,0,MAX_STATEMENT_SIZE);
                                                sql_IWFEventDetails_Create_Select_Query(pEventType, sStatement);
                                                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                                {
                                                    if(pRes != NULL)    
                                                    {
                                                        delete pRes;
                                                        pRes = NULL;
                                                    }
                                                    DLOG_ERROR("Query Execution Failed %s",sStatement);

                                                    if(iReturn == IWF_DB_FAIL)
                                                        iReturn = DEL_PROTOCOL_ACTION_ERR_DB_ERROR;

                                                    mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                                    return iReturn;
                                                }

                                                memset(sStatement,0,MAX_STATEMENT_SIZE);
                                                if(pRes->rowsCount() == 0) // ADD
                                                {
                                                    // Delete Event Type if count is 0
                                                    sql_IWFEventTypeMapping_Create_Delete_Query(pCallScenario, RuleName, sStatement, l);
                                                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                                    {
                                                        delete pRes;
                                                        pRes = NULL;
                                                        DLOG_ERROR("Query Execution Failed %s",sStatement);
                                                        if(iReturn == IWF_DB_FAIL)
                                                            iReturn = DEL_PROTOCOL_ACTION_ERR_DB_ERROR;

                                                        mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,DEL_PROTOCOL_ACTION_ERR_DB_ERROR);
                                                        DLOG_DEBUG("iReturn = %d",iReturn);
                                                        DLOG_NONE(" < %s ",__FUNCTION__);
                                                        return iReturn;
                                                    }
                                                }
                                                if(pRes != NULL)
                                                    delete pRes;
                                                pRes = NULL;
                                                DLOG_DEBUG("iReturn = %d",iReturn);
                                                DLOG_NONE(" < %s ",__FUNCTION__);
                                                return iReturn;
                                            }
                                            if(pRes != NULL)
                                                delete pRes;
                                            pRes = NULL;
                                        }
                                    }
                                }
                            }
                        }

                    }
                }
            }
        }
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfProtocolAction_Add_Config_Reqs(IwfProtocolActionsConfig *pIwfProtocolActionsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfProtocolActionsConfig->iwfprotactioncfgval_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(ADD_PROTOCOL_ACTION_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[ADD_PROTOCOL_ACTION_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfProtocolActionConfig *pIwfProtocolActionConfig= pIwfProtocolActionsConfig->mutable_iwfprotactioncfgval(i);
        if(pIwfProtocolActionConfig->has_actionrulename())
        {
            std::string RuleName = pIwfProtocolActionConfig->actionrulename().c_str();

            sql_IWFProtocolAction_Create_Check_Modifcation_Query(pIwfProtocolActionConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_PROTOCOL_ACTION_ERR_DB_ERROR;

                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                sql_IWFProtocolAction_Create_Add_Query(pIwfProtocolActionConfig,sStatement);
            }
            else // MOD
            {
                delete pRes;
                DLOG_ERROR("Record Already Present");   
                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,ADD_PROTOCOL_ACTION_ERR_ALREADY_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_PROTOCOL_ACTION_ERR_ALREADY_PRESENT;
            }

            delete pRes;
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_PROTOCOL_ACTION_ERR_DB_ERROR;

                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if(pIwfProtocolActionConfig->msgdetval_size())
            {
                int msgdetsize = pIwfProtocolActionConfig->msgdetval_size();

                for (int j = 0; j < msgdetsize; j++)
                {
                    MsgDet *pMsgDet = pIwfProtocolActionConfig->mutable_msgdetval(j);

                    if(pMsgDet->callscenarioval_size())
                    {
                        int callscenarioSize = pMsgDet->callscenarioval_size();
                        for (int k=0 ; k < callscenarioSize; k++)
                        {
                            //Insert of CallScenario
                            CallScenario *pCallScenario = pMsgDet->mutable_callscenarioval(k);
                            string callScenario = pCallScenario->call_typename();
                            memset(sStatement,0,MAX_STATEMENT_SIZE);

                            sql_IWFCallScenarioMapping_Create_Check_Modifcation_Query(pMsgDet, RuleName, sStatement, k);

                            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                            {
                                if(pRes != NULL)    
                                {
                                    delete pRes;
                                }
                                DLOG_ERROR("Query Execution Failed %s",sStatement);

                                if(iReturn == IWF_DB_FAIL)
                                    iReturn = ADD_PROTOCOL_ACTION_ERR_DB_ERROR;

                                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                                DLOG_DEBUG("iReturn = %d",iReturn);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return iReturn;
                            }

                            memset(sStatement,0,MAX_STATEMENT_SIZE);

                            if(pRes->rowsCount() == 0) // ADD
                            {
                                sql_IWFCallScenarioMapping_Create_Add_Query(pMsgDet, RuleName, sStatement, k);
                            }
                            else // MOD
                            {
                                delete pRes;
                                DLOG_ERROR("Record CallScenario Already Present"); 
                                mysql_set_error_for_IWFCallScenario_Config_Reqs(pMsgDet, RuleName, resp, ADD_PROTOCOL_ACTION_ERR_CALL_SCENARIO_ALREADY_PRESENT, k);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return ADD_PROTOCOL_ACTION_ERR_CALL_SCENARIO_ALREADY_PRESENT;
                            }

                            delete pRes;
                            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                            {
                                DLOG_ERROR("Query Execution Failed %s",sStatement);
                                if(iReturn == IWF_DB_FAIL)
                                    iReturn = ADD_PROTOCOL_ACTION_ERR_DB_ERROR;

                                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);
                                DLOG_DEBUG("iReturn = %d",iReturn);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return iReturn;
                            }

                            if(pCallScenario->eventtypeval_size())
                            {
                                // Insert of EventType for specific call scenario
                                int eventtype_Size = pCallScenario->eventtypeval_size();
                                for (int l = 0; l < eventtype_Size; l++)
                                {
                                    EventType *pEventType = pCallScenario->mutable_eventtypeval(l);
                                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                                    sql_IWFEventTypeMapping_Create_Check_Modifcation_Query(pCallScenario, RuleName, sStatement, l);

                                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                    {
                                        if(pRes != NULL)    
                                        {
                                            delete pRes;
                                        }
                                        DLOG_ERROR("Query Execution Failed %s",sStatement);

                                        if(iReturn == IWF_DB_FAIL)
                                            iReturn = ADD_PROTOCOL_ACTION_ERR_DB_ERROR;

                                        mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                                        DLOG_DEBUG("iReturn = %d",iReturn);
                                        DLOG_NONE(" < %s ",__FUNCTION__);
                                        return iReturn;
                                    }

                                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                                    if(pRes->rowsCount() == 0) // ADD
                                    {
                                        sql_IWFEventTypeMapping_Create_Add_Query(pCallScenario, RuleName, sStatement, l);
                                    }
                                    else // MOD
                                    {
                                        delete pRes;
                                        DLOG_ERROR("Record EventType Already Present"); 
                                        mysql_set_error_for_IWFEventType_Config_Reqs(pCallScenario, RuleName, resp, ADD_PROTOCOL_ACTION_ERR_CALL_SCENARIO_EVENT_TYPE_ALREADY_PRESENT, l);
                                        DLOG_NONE(" < %s ",__FUNCTION__);
                                        return ADD_PROTOCOL_ACTION_ERR_CALL_SCENARIO_EVENT_TYPE_ALREADY_PRESENT;
                                    }

                                    delete pRes;
                                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                    {
                                        DLOG_ERROR("Query Execution Failed %s",sStatement);
                                        if(iReturn == IWF_DB_FAIL)
                                            iReturn = ADD_PROTOCOL_ACTION_ERR_DB_ERROR;

                                        mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);
                                        DLOG_DEBUG("iReturn = %d",iReturn);
                                        DLOG_NONE(" < %s ",__FUNCTION__);
                                        return iReturn;
                                    }

                                    if(pEventType->armdatval_size())
                                    {
                                        //Insert of EventspecificData
                                        int armDataSize = pEventType->armdatval_size();
                                        for(int m = 0; m < armDataSize; m++)
                                        {
                                            sql_IWFEventTypeDetails_Create_Check_Modifcation_Query(pEventType, RuleName, callScenario, sStatement, m);

                                            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                            {
                                                if(pRes != NULL)    
                                                {
                                                    delete pRes;
                                                }
                                                DLOG_ERROR("Query Execution Failed %s",sStatement);

                                                if(iReturn == IWF_DB_FAIL)
                                                    iReturn = ADD_PROTOCOL_ACTION_ERR_DB_ERROR;

                                                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);

                                                DLOG_DEBUG("iReturn = %d",iReturn);
                                                DLOG_NONE(" < %s ",__FUNCTION__);
                                                return iReturn;
                                            }

                                            memset(sStatement,0,MAX_STATEMENT_SIZE);

                                            if(pRes->rowsCount() == 0) // ADD
                                            {
                                                sql_IWFEventTypeDetails_Create_Add_Query(pEventType, RuleName, callScenario, sStatement, m);
                                            }
                                            else // MOD
                                            {
                                                delete pRes;
                                                DLOG_ERROR("Record EventType Details Already Present"); 
                                                mysql_set_error_for_IWFEventTypeDetails_Config_Reqs(pEventType, RuleName, callScenario, resp, ADD_PROTOCOL_ACTION_ERR_CALL_SCENARIO_EVENT_TYPE_DETAILS_ALREADY_PRESENT, m);
                                                DLOG_NONE(" < %s ",__FUNCTION__);
                                                return ADD_PROTOCOL_ACTION_ERR_CALL_SCENARIO_EVENT_TYPE_DETAILS_ALREADY_PRESENT;
                                            }

                                            delete pRes;
                                            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                            {
                                                DLOG_ERROR("Query Execution Failed %s",sStatement);
                                                if(iReturn == IWF_DB_FAIL)
                                                    iReturn = ADD_PROTOCOL_ACTION_ERR_DB_ERROR;

                                                mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);
                                                DLOG_DEBUG("iReturn = %d",iReturn);
                                                DLOG_NONE(" < %s ",__FUNCTION__);
                                                return iReturn;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                    }
                }
            }
        }
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFEventTypeDetails_protobuff(EventType *pEventType,IWFCfgResp* resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFEventDetails_Create_Select_Query(pEventType,sStatement); 
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)        
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_PROTOCOL_ACTION_ERR_DB_ERROR;

        //mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    if(pRes->rowsCount() != 0)
    {
        while(pRes->next())
        {
            ArmData* pArmData = pEventType->add_armdatval();
            if(!pRes->isNull("MONITOR_MODE"))
                pArmData->set_monitormode(pRes->getString("MONITOR_MODE"));       
            if(!pRes->isNull("LEG_ID"))
                pArmData->set_legid(pRes->getString("LEG_ID"));
        }
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFEventType_protobuff(CallScenario* callScenario, std::string ActionRuleName,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    
    sql_IWFEventTypeMapping_Create_Select_Query(callScenario, ActionRuleName, sStatement, -1);

    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)        
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_PROTOCOL_ACTION_ERR_DB_ERROR;

        //mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            while(pRes->next())
            {
                EventType *pEventType = callScenario->add_eventtypeval();
                
                if(!pRes->isNull("IWF_EVENT_TYPE_MAPPING_ID"))
                    pEventType->set_eventtypemappingid(pRes->getInt("IWF_EVENT_TYPE_MAPPING_ID"));

                if(!pRes->isNull("IWF_EVENT_TYPE_ID"))
                {
                    memset(sStatement,0,MAX_STATEMENT_SIZE);
                    sql_IWFEventType_Create_Select_Query(pRes->getInt("IWF_EVENT_TYPE_ID"), sStatement);
                    sql::ResultSet *plRes = NULL;
                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&plRes)) != IWF_DB_SUCCESS)
                    {
                        if(plRes != NULL)        
                        {
                            delete plRes;
                        }

                        DLOG_ERROR("Query Execution Failed: %s",sStatement);
                        if(iReturn == IWF_DB_FAIL)
                            iReturn = GET_PROTOCOL_ACTION_ERR_DB_ERROR;

                        //mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                    DLOG_DEBUG("plRes->rowsCount() = %d",plRes->rowsCount());
                    if(plRes->rowsCount() != 0)
                    {
                        while(plRes->next())
                        {
                            if(!plRes->isNull("IWF_EVENT_TYPE_NAME"))
                                pEventType->set_eventtypename(plRes->getString("IWF_EVENT_TYPE_NAME"));       
                        }
                    }
                    delete plRes;
                    Fill_IWFEventTypeDetails_protobuff(pEventType, resp);
                }
            }
        }
        delete pRes;
    }
    catch (sql::SQLException &e)
    {
        delete pRes;
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;

}

DbStatus_e CMgrIwfDbInterface::Fill_IWFCallScenario_protobuff(IwfProtocolActionConfig *pIwfProtocolActionConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    MsgDet LocalMsgDet;
    
    sql_IWFCallScenarioMapping_Create_Select_Query(&LocalMsgDet, pIwfProtocolActionConfig->actionrulename().c_str(), sStatement, -1);

    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)        
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_PROTOCOL_ACTION_ERR_DB_ERROR;

        mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            MsgDet* msgDet = pIwfProtocolActionConfig->add_msgdetval();

            while(pRes->next())
            {
                CallScenario *callScenario = msgDet->add_callscenarioval();
                
                if(!pRes->isNull("IWF_CALL_SCENARIO_ID"))
                {
                    if(pRes->getInt("IWF_CALL_SCENARIO_ID") == 1)
                        callScenario->set_call_typename("MO_CAPV1");
                    else if(pRes->getInt("IWF_CALL_SCENARIO_ID") == 2)
                        callScenario->set_call_typename("MO_CAPV2");
                    else if(pRes->getInt("IWF_CALL_SCENARIO_ID") == 3)
                        callScenario->set_call_typename("MT_CAPV1");
                    else if(pRes->getInt("IWF_CALL_SCENARIO_ID") == 4)
                        callScenario->set_call_typename("MT_CAPV2");
                    else if(pRes->getInt("IWF_CALL_SCENARIO_ID") == 5)
                        callScenario->set_call_typename("SMS_CAPV3");

                    Fill_IWFEventType_protobuff(callScenario, pIwfProtocolActionConfig->actionrulename().c_str(), resp);
                }
            }
        }
        delete pRes;
    }
    catch (sql::SQLException &e)
    {
        delete pRes;
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFProtocolActions_protobuff(IwfProtocolActionsConfig *pIwfProtocolActionsConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    int i=0;
    int ifData = 0;

    IwfProtocolActionConfig LocalIwfProtocolActionConfigObj;
    IwfProtocolActionConfig *pIwfProtocolActionConfig = NULL;

    int iCount = pIwfProtocolActionsConfig->iwfprotactioncfgval_size();
    DLOG_INFO("pIwfProtocolActionsConfig->iwfprotactioncfgval_size() = %d",iCount);
    do
    {
        if(iCount != 0)
            pIwfProtocolActionConfig = pIwfProtocolActionsConfig->mutable_iwfprotactioncfgval(i);
        else
            pIwfProtocolActionConfig = &LocalIwfProtocolActionConfigObj;

        sql_IWFProtocolAction_Create_Select_Query(pIwfProtocolActionConfig,sStatement);

        sql::ResultSet *pRes = NULL;
        DbStatus_e iReturn =  IWF_DB_SUCCESS;
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = GET_PROTOCOL_ACTION_ERR_DB_ERROR;

            mysql_set_error_for_IWFProtocolAction_Config_Reqs(pIwfProtocolActionConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
            if(pRes->rowsCount() != 0)
            {
                IwfProtocolActionsConfig *LocalIwfProtocolActionsConfig = resp->mutable_iwfprotocolactionsinfo();

                while(pRes->next())
                {
                    pIwfProtocolActionConfig = LocalIwfProtocolActionsConfig->add_iwfprotactioncfgval();
                    ifData = 1;
                    if(!pRes->isNull("IWF_PROTOCOL_ACTION_RULE_ID"))
                        pIwfProtocolActionConfig->set_actionruleid(pRes->getInt("IWF_PROTOCOL_ACTION_RULE_ID"));
                    if(!pRes->isNull("ACTION_RULE_NAME"))
                        pIwfProtocolActionConfig->set_actionrulename(pRes->getString("ACTION_RULE_NAME"));
                    if(!pRes->isNull("ACTION_ID"))
                        pIwfProtocolActionConfig->set_actionid(pRes->getInt("ACTION_ID"));
                    if(!pRes->isNull("PROTOCOL_ID"))
                    {
                        if(pRes->getInt("PROTOCOL_ID") == 1)
                            pIwfProtocolActionConfig->set_protocol("CAP");
                    }
                    
                    Fill_IWFCallScenario_protobuff(pIwfProtocolActionConfig,resp);
                }
            }
            delete pRes;
        }
        catch (sql::SQLException &e)
        {
            delete pRes;
            DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
            DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
            DLOG_NONE(" < %s ",__FUNCTION__);
            return IWF_DB_FAIL;
        }

        i++;

    }while(i<iCount);
    
    if(!ifData)
    {
        DLOG_DEBUG("There is no data in the table setting GET_PROTOCOL_ACTION_ERR_NO_DATA");
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(GET_PROTOCOL_ACTION_ERR_NO_DATA);
        err->set_errormsgkey(iwfErrorMap[GET_PROTOCOL_ACTION_ERR_NO_DATA]);
        DLOG_DEBUG("Error key is %s", (iwfErrorMap[GET_PROTOCOL_ACTION_ERR_NO_DATA]).c_str());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfProtocolAction_Get_Config_Reqs(IwfProtocolActionsConfig *pIwfProtocolActionsConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    return Fill_IWFProtocolActions_protobuff(pIwfProtocolActionsConfig,resp);
    DLOG_NONE(" < %s ",__FUNCTION__);
}
