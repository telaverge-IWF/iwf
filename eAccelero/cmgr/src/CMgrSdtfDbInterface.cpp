/*******************************-*-CPP-*-************************************
 *                                                                          *
 *          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
 *            Manufactured in the United States of America.                 *
 *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of Diametriq and its licensors, if any.                  *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************/

/*
 * FILE:   CMgrSdtfDbInterface.cpp
 * Author: Hemanth
 *
 * Created on Nov 25, 2014, 09:32 PM
 */


#include <CMgrDbInterface.h>
#include "ErrorResp.h"

using namespace std;
extern std::map<int,std::string> errorMap;

void CMgrDbInterface::mysql_set_error_for_Sdtf_Config_Reqs(SDTFResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

// Private error functions
void CMgrDbInterface::mysql_set_error_for_SDTF_config_Reqs(SDTFRule *req, SDTFResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(req->has_rulename())
    {
        err->add_variables(req->rulename());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_CongSDTFRule_resultset_to_protoBuff(sql::ResultSet *pRes, SDTFResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG("%s: RowCount = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_SDTF_RULES_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            SDTFRule *pSDTFRule = resp->add_rule();

            if(!pRes->isNull("RULE_ID"))
            {
                pSDTFRule->set_ruleid(pRes->getInt("RULE_ID"));
            }
            if(!pRes->isNull("NAME"))
            {
                pSDTFRule->set_rulename(pRes->getString("NAME"));
            }
            if(!pRes->isNull("PRIORITY"))
            {
                pSDTFRule->set_priority(pRes->getInt("PRIORITY"));
            }
            if(!pRes->isNull("TRIGGER_TYPE"))
            {
                if(pRes->getString("TRIGGER_TYPE") == "Ingress")
                {
                    pSDTFRule->set_type(SDTFRule_TriggerType_Ingress);
                }
                else if(pRes->getString("TRIGGER_TYPE") == "Egress")
                {
                    pSDTFRule->set_type(SDTFRule_TriggerType_Egress);
                }
            }
            if(!pRes->isNull("ENABLED"))
            {
                pSDTFRule->set_enabled(pRes->getInt("ENABLED"));
            }
            if(!pRes->isNull("RULE"))
            {
                pSDTFRule->set_rule(pRes->getString("RULE"));
            }
            if(!pRes->isNull("SCRIPT"))
            {
                pSDTFRule->set_script(pRes->getString("SCRIPT"));
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

DbStatus_e CMgrDbInterface::mysql_Cong_FeatureStatus_resultset_to_protoBuff(sql::ResultSet *pRes, SDTFResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG("%s: RowCount = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_SDTF_FEATURE_STATUS_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            if(!pRes->isNull("IS_ENABLED"))
            {
                resp->set_enablesdtf(pRes->getInt("IS_ENABLED"));
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

DbStatus_e CMgrDbInterface::mysql_fetch_and_fill_SDTF_Rule_Id_And_Status(SDTFRule *pSDTFRule)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn = DRE_DB_SUCCESS;

    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_SDTFRules_Create_Fetch_Query(pSDTFRule, sStatement);

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
    iReturn = DRE_DB_FAIL;

    if(pRes->rowsCount() != 0)
    {
        if(pRes->next())
        {
            iReturn = DRE_DB_SUCCESS;

            do {
                if(!pRes->isNull("RULE_ID"))
                {
                    pSDTFRule->set_ruleid(pRes->getInt("RULE_ID"));
                }
                else
                {
                    iReturn = DRE_DB_FAIL;
                    break;
                }

                if(!pRes->isNull("ENABLED"))
                {
                    pSDTFRule->set_enabled(pRes->getInt("ENABLED"));
                    iReturn = DRE_DB_SUCCESS;
                }
                else
                {
                    iReturn = DRE_DB_FAIL;
                    break;
                }
            } while (false);
        }
    }

    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_fetch_and_fill_SDTF_Rule_Config(SDTFRule *pSDTFRule)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn = DRE_DB_SUCCESS;

    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_SDTFRules_Create_Fetch_Query(pSDTFRule, sStatement);

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
    iReturn = DRE_DB_FAIL;

    if(pRes->rowsCount() != 0)
    {
        if(pRes->next())
        {
            iReturn = DRE_DB_SUCCESS;

            do {
                if(!pRes->isNull("RULE_ID"))
                {
                    pSDTFRule->set_ruleid(pRes->getInt("RULE_ID"));
                }
                else
                {
                    iReturn = DRE_DB_FAIL;
                    break;
                }

                if(!pRes->isNull("PRIORITY"))
                {
                    pSDTFRule->set_priority(pRes->getInt("PRIORITY"));
                }
                else
                {
                    iReturn = DRE_DB_FAIL;
                    break;
                }

                if(!pRes->isNull("RULE"))
                {
                    pSDTFRule->set_rule(pRes->getString("RULE"));
                }
                else
                {
                    iReturn = DRE_DB_FAIL;
                    break;
                }

                if(!pRes->isNull("TRIGGER_TYPE"))
                {
                    if(pRes->getString("TRIGGER_TYPE") == "Ingress")
                    {
                        pSDTFRule->set_type(SDTFRule_TriggerType_Ingress);
                    }
                    else if(pRes->getString("TRIGGER_TYPE") == "Egress")
                    {
                        pSDTFRule->set_type(SDTFRule_TriggerType_Egress);
                    }
                    else
                    {
                        iReturn = DRE_DB_FAIL;
                        break;
                    }
                }
                else
                {
                    iReturn = DRE_DB_FAIL;
                    break;
                }

                if(!pRes->isNull("SCRIPT"))
                {
                    pSDTFRule->set_script(pRes->getString("SCRIPT"));
                }
                else
                {
                    iReturn = DRE_DB_FAIL;
                    break;
                }
            } while (false);
        }
    }

    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Sdtf_Get_SDTFRules_Config_Reqs(SDTFReq *req, SDTFResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_SPECIAL_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    int iCount = req->rule_size();
    DLOG_DEBUG(" %s: SDTFReq Req Size = %d ",__FUNCTION__,iCount);

    if(iCount)
    {
        for(int iIndex=0; iIndex<iCount; iIndex++)
        {
            SDTFRule *plocalSDTFRule = req->mutable_rule(iIndex);

            memset(sStatement,0,MAX_SPECIAL_STATEMENT_SIZE);
            sql_SDTFRules_Create_Select_Query(plocalSDTFRule, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                {
                    iReturn = GET_SDTF_RULES_DB_ERROR;
                }

                mysql_set_error_for_SDTF_config_Reqs(plocalSDTFRule, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_CongSDTFRule_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
            {
                delete pRes;
                mysql_set_error_for_SDTF_config_Reqs(plocalSDTFRule, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            delete pRes;
        }
    }
    else
    {
        SDTFRule localSDTFRule;

        memset(sStatement,0,MAX_SPECIAL_STATEMENT_SIZE);
        sql_SDTFRules_Create_Select_Query(&localSDTFRule, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
            {
                iReturn = GET_SDTF_RULES_DB_ERROR;
            }

            mysql_set_error_for_SDTF_config_Reqs(&localSDTFRule, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_CongSDTFRule_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;
            mysql_set_error_for_SDTF_config_Reqs(&localSDTFRule, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_SDTF_Add_SDTFRule_Validation(SDTFRule *pSDTFRule)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    if((!pSDTFRule->has_rulename()) || (!pSDTFRule->has_priority()) || (!pSDTFRule->has_rule())
            || (!pSDTFRule->has_type()) || (!pSDTFRule->has_script()))
    {
        DLOG_ERROR("mysql_SDTF_Add_SDTFRule_Validation() : Required fields are missing in SDTFRule.");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return CONFIG_COMMON_ERR_NO_INPUT_PARAMS;
    }
    else
    {
        SDTFRule localSDTFRule;
        localSDTFRule.set_rulename(pSDTFRule->rulename());

        sql_SDTFRules_Create_Check_Modifcation_Query(&localSDTFRule, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
            {
                iReturn = ADD_SDTF_RULES_DB_ERROR;
            }

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            DLOG_ERROR("Record already present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_SDTF_RULES_ERR_RULE_ALREADY_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_SDTF_Add_SDTFRule_Config_Req(SDTFReq *req, SDTFResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_SPECIAL_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_SUCCESS;

    int iCount = req->rule_size();

    for(int iIndex=0; iIndex<iCount; iIndex++)
    {
        SDTFRule *plocalSDTFRule = req->mutable_rule(iIndex);

        if((iReturn = mysql_SDTF_Add_SDTFRule_Validation(plocalSDTFRule)) != DRE_DB_SUCCESS)
        {
            DLOG_DEBUG(" %s:%d mysql_SDTF_Add_SDTFRule_Validation Failed \n",__FUNCTION__,__LINE__);
            mysql_set_error_for_SDTF_config_Reqs(plocalSDTFRule, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            memset(sStatement,0,MAX_SPECIAL_STATEMENT_SIZE);
            sql_SDTFRules_Create_Add_Query(plocalSDTFRule, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                {
                    iReturn = ADD_SDTF_RULES_DB_ERROR;
                }

                mysql_set_error_for_SDTF_config_Reqs(plocalSDTFRule, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_fetch_and_fill_SDTF_Rule_Id_And_Status(plocalSDTFRule)) != DRE_DB_SUCCESS)
            {
                iReturn = ADD_SDTF_RULES_DB_ERROR;

                mysql_set_error_for_SDTF_config_Reqs(plocalSDTFRule, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_SDTF_Mod_SDTFRule_Validation(SDTFRule *pSDTFRule)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    if((!pSDTFRule->has_rulename()) || (!pSDTFRule->has_priority()) || (!pSDTFRule->has_rule())
            || (!pSDTFRule->has_type()) || (!pSDTFRule->has_script()))
    {
        DLOG_ERROR("mysql_SDTF_Mod_SDTFRule_Validation() : Required fields are missing in SDTFRule.");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return CONFIG_COMMON_ERR_NO_INPUT_PARAMS;
    }
    else
    {
        SDTFRule localSDTFRule;
        localSDTFRule.set_rulename(pSDTFRule->rulename());

        sql_SDTFRules_Create_Check_Modifcation_Query(&localSDTFRule, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
            {
                iReturn = MOD_SDTF_RULES_DB_ERROR;
            }

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Record mot present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_SDTF_RULES_ERR_RULE_NOT_CONFIGURED;
        }
        delete pRes;
        pRes = NULL;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_SDTF_Mod_SDTFRule_Config_Req(SDTFReq *req, SDTFResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_SPECIAL_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_SUCCESS;

    int iCount = req->rule_size();

    for(int iIndex=0; iIndex<iCount; iIndex++)
    {
        SDTFRule *plocalSDTFRule = req->mutable_rule(iIndex);

        if((iReturn = mysql_SDTF_Mod_SDTFRule_Validation(plocalSDTFRule)) != DRE_DB_SUCCESS)
        {
            DLOG_DEBUG(" %s:%d mysql_SDTF_Mod_SDTFRule_Validation Failed \n",__FUNCTION__,__LINE__);
            mysql_set_error_for_SDTF_config_Reqs(plocalSDTFRule, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            memset(sStatement,0,MAX_SPECIAL_STATEMENT_SIZE);
            sql_SDTFRules_Create_Mod_Query(plocalSDTFRule, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                {
                    iReturn = MOD_SDTF_RULES_DB_ERROR;
                }

                mysql_set_error_for_SDTF_config_Reqs(plocalSDTFRule, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_fetch_and_fill_SDTF_Rule_Id_And_Status(plocalSDTFRule)) != DRE_DB_SUCCESS)
            {
                iReturn = MOD_SDTF_RULES_DB_ERROR;

                mysql_set_error_for_SDTF_config_Reqs(plocalSDTFRule, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_SDTF_Del_SDTFRule_Validation(SDTFRule *pSDTFRule)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    if(!pSDTFRule->has_rulename())
    {
        DLOG_ERROR("mysql_SDTF_Del_SDTFRule_Validation() : Required fields are missing in SDTFRule.");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return CONFIG_COMMON_ERR_NO_INPUT_PARAMS;
    }
    else
    {
        SDTFRule localSDTFRule;
        localSDTFRule.set_rulename(pSDTFRule->rulename());

        sql_SDTFRules_Create_Check_Modifcation_Query(&localSDTFRule, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
            {
                iReturn = DEL_SDTF_RULES_DB_ERROR;
            }

            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_SDTF_RULES_DB_ERROR;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Record not present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_SDTF_RULES_ERR_RULE_NOT_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_SDTF_Del_SDTFRule_Config_Req(SDTFReq *req, SDTFResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_SUCCESS;

    int iCount = req->rule_size();
    DLOG_DEBUG(" %s:%d iCount =%d \n",__FUNCTION__,__LINE__,iCount);

    for(int iIndex=0; iIndex<iCount; iIndex++)
    {
        SDTFRule *plocalSDTFRule = req->mutable_rule(iIndex);

        if((iReturn = mysql_SDTF_Del_SDTFRule_Validation(plocalSDTFRule)) != DRE_DB_SUCCESS)
        {
            DLOG_DEBUG(" %s:%d mysql_SDTF_Del_SDTFRule_Validation Failed \n",__FUNCTION__,__LINE__);
            mysql_set_error_for_SDTF_config_Reqs(plocalSDTFRule, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_SDTFRules_Create_Delete_Query(plocalSDTFRule, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                {
                    iReturn = DEL_SDTF_RULES_DB_ERROR;
                }

                mysql_set_error_for_SDTF_config_Reqs(plocalSDTFRule, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_SDTF_Set_SDTFRule_Status_Validation(SDTFRule *pSDTFRule)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    if((!pSDTFRule->has_rulename()) || (!pSDTFRule->has_enabled()))
    {
        DLOG_ERROR("mysql_SDTF_Set_SDTFRule_Status_Validation() : Required fields are missing in SDTFRule.");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return CONFIG_COMMON_ERR_NO_INPUT_PARAMS;
    }
    else
    {
        SDTFRule localSDTFRule;
        localSDTFRule.set_rulename(pSDTFRule->rulename());

        sql_SDTFRules_Create_Check_Modifcation_Query(&localSDTFRule, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
            {
                iReturn = SET_SDTF_RULE_STATUS_DB_ERROR;
            }

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Record not present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return SET_SDTF_RULE_STATUS_ERR_RULE_NOT_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_SDTF_Set_SDTFRule_Status_Config_Req(SDTFReq *req, SDTFResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_SPECIAL_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_SUCCESS;

    int iCount = req->rule_size();
    DLOG_DEBUG(" %s:%d No of Rules = %d\n",__FUNCTION__,__LINE__,iCount);

    for(int iIndex=0; iIndex<iCount; iIndex++)
    {
        SDTFRule *plocalSDTFRule = req->mutable_rule(iIndex);

        if((iReturn = mysql_SDTF_Set_SDTFRule_Status_Validation(plocalSDTFRule)) != DRE_DB_SUCCESS)
        {
            DLOG_DEBUG(" %s:%d mysql_SDTF_Set_SDTFRule_Status_Validation Failed \n",__FUNCTION__,__LINE__);
            mysql_set_error_for_SDTF_config_Reqs(plocalSDTFRule, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            memset(sStatement,0,MAX_SPECIAL_STATEMENT_SIZE);
            sql_SDTFRules_Create_Mod_Query(plocalSDTFRule, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                {
                    iReturn = SET_SDTF_RULE_STATUS_DB_ERROR;
                }

                mysql_set_error_for_SDTF_config_Reqs(plocalSDTFRule, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_fetch_and_fill_SDTF_Rule_Config(plocalSDTFRule)) != DRE_DB_SUCCESS)
            {
                iReturn = SET_SDTF_RULE_STATUS_DB_ERROR;

                mysql_set_error_for_SDTF_config_Reqs(plocalSDTFRule, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Sdtf_Get_SDTF_EnableStatus_Config_Req(SDTFResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_FeatureStatus_Create_Select_Query("SDTF", sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        if(iReturn == DRE_DB_FAIL)
        {
            iReturn = GET_SDTF_FEATURE_STATUS_DB_ERROR;
        }

        mysql_set_error_for_Sdtf_Config_Reqs(resp, iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if((iReturn = mysql_Cong_FeatureStatus_resultset_to_protoBuff(pRes, resp)) != DRE_DB_SUCCESS)
    {
        delete pRes;
        mysql_set_error_for_Sdtf_Config_Reqs(resp, iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_SDTF_Set_SDTF_EnableStatus_Validation(string featureName)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    sql_FeatureStatus_Create_Check_Modifcation_Query(featureName, sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        if(iReturn == DRE_DB_FAIL)
        {
            iReturn = SET_SDTF_FEATURE_STATUS_DB_ERROR;
        }

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0)
    {
        delete pRes;
        DLOG_ERROR("Record not present");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return SET_SDTF_FEATURE_STATUS_ERR_RULE_NOT_PRESENT;
    }
    delete pRes;
    pRes = NULL;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_SDTF_Set_SDTF_EnableStatus_Config_Req(SDTFReq *req, SDTFResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_SUCCESS;
    string featureName = "SDTF";

    if(!req->has_enablesdtf())
    {
        DLOG_ERROR("mysql_SDTF_Set_SDTF_EnableStatus_Config_Req() : Required fields are missing in SDTFReq.");
        iReturn = CONFIG_COMMON_ERR_NO_INPUT_PARAMS;
        mysql_set_error_for_Sdtf_Config_Reqs(resp, iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    bool enable = req->enablesdtf();

    if((iReturn = mysql_SDTF_Set_SDTF_EnableStatus_Validation(featureName)) != DRE_DB_SUCCESS)
    {
        DLOG_DEBUG(" %s:%d mysql_SDTF_Set_SDTF_EnableStatus_Validation Failed \n",__FUNCTION__,__LINE__);
        mysql_set_error_for_Sdtf_Config_Reqs(resp, iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    else
    {
        sql_FeatureStatus_Create_Mod_Query(featureName, enable, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
            {
                iReturn = SET_SDTF_FEATURE_STATUS_DB_ERROR;
            }

            mysql_set_error_for_Sdtf_Config_Reqs(resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

