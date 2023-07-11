/* *C-*-************************************
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


void CMgrIwfDbInterface::mysql_set_error_for_IWFTranslatorRule_Config_Reqs(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(!(resp->errordetails_size() > 0))
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(iReturn);
        err->set_errormsgkey(iwfErrorMap[iReturn]);
        DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

        if(pIwfTranslatorRuleConfig->has_translatorrulename())
            err->add_variables(pIwfTranslatorRuleConfig->translatorrulename());

        if(iReturn == ADD_TRANSRULES_ERR_DESTINATION_NOT_PRESENT||
                iReturn == MOD_TRANSRULES_ERR_DESTINATION_NOT_PRESENT ||
                iReturn == MOD_TRANSRULES_ERR_DEST_NOT_PART_OF_REMOTE_ROUTE ||
                iReturn == ADD_TRANSRULES_ERR_DEST_NOT_PART_OF_REMOTE_ROUTE)
            err->add_variables(pIwfTranslatorRuleConfig->destinationname());

        if(iReturn == ADD_TRANSRULES_ERR_ALT_DESTINATION_NOT_PRESENT||
                iReturn == MOD_TRANSRULES_ERR_ALT_DESTINATION_NOT_PRESENT ||
                iReturn == MOD_TRANSRULES_ERR_ALT_DEST_NOT_PART_OF_REMOTE_ROUTE ||
                iReturn == ADD_TRANSRULES_ERR_ALT_DEST_NOT_PART_OF_REMOTE_ROUTE)
            err->add_variables(pIwfTranslatorRuleConfig->alternaterealm());

        if(iReturn == ADD_TRANSRULES_ERR_DESTINATION_HOST_NOT_PRESENT ||
                iReturn == MOD_TRANSRULES_ERR_DESTINATION_HOST_NOT_PRESENT)
        {
            err->add_variables(pIwfTranslatorRuleConfig->destinationhost());
            err->add_variables(pIwfTranslatorRuleConfig->destinationname());
        }

        if(iReturn == ADD_TRANSRULES_ERR_ALTERNATE_HOST_NOT_PRESENT ||
                iReturn == MOD_TRANSRULES_ERR_ALTERNATE_HOST_NOT_PRESENT)
        {
            err->add_variables(pIwfTranslatorRuleConfig->alternatehost());
            err->add_variables(pIwfTranslatorRuleConfig->alternaterealm());
        }

        if(iReturn == ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM_MCC_MNC_FOR_SS7 ||
                iReturn == ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM_SERVICE_KEY_FOR_SS7 ||
                iReturn == ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM_PROACTIONRULE_FOR_SS7 ||
                iReturn == ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM_IMSIPREFIX_OR_SERVICEKEY_FOR_SS7)
        {
            IwfLocalHostsConfig plocalIwfLocalHostsConfig;
            IWFCfgResp localresp;
            if(mysql_IWFLocalConfig_Get_Config_Reqs(&plocalIwfLocalHostsConfig,&localresp) == IWF_DB_SUCCESS)
            {
                if(localresp.has_localhostinfo())
                {
                    IwfLocalHostsConfig* plocalhostsconfig = localresp.mutable_localhostinfo();
                    IwfLocalHostConfig* localhostinfo = plocalhostsconfig->mutable_localhostinfo();
                    if(localhostinfo->has_selectcriteria())
                    {
                        int selectcriteria = localhostinfo->selectcriteria();
                        if(selectcriteria == MCC_MNC)
                            err->add_variables("MCC_MNC");
                        else if(selectcriteria == APP_ID)
                            err->add_variables("APP_ID");
                        else if(selectcriteria == MCC_MNC_AND_APP_ID)
                            err->add_variables("MCC_MNC_AND_APP_ID");
                        else if(selectcriteria == GTT)
                            err->add_variables("GTT");
                        else if(selectcriteria == GTT_AND_MCC_MNC)
                            err->add_variables("GTT_AND_MCC_MNC");
                        else if(selectcriteria == SK)
                            err->add_variables("SERVICE_KEY");
                        else if(selectcriteria == SK_AND_MCC_MNC)
                            err->add_variables("SERVICE_KEY_AND_MCC_MNC");
                        else if(selectcriteria == GTT_AND_SK)
                            err->add_variables("GTT_AND_SERVICE_KEY");
                        else if(selectcriteria == IMSI_PREFIX_AND_SK)
                            err->add_variables("IMSIPREFIX_AND_SK");
                    }
                }
            }
        }
        if(iReturn == ADD_TRANSRULES_ERR_MCC_MNC_APPID_COMBINATION_ALREADY_PRESENT||
                iReturn == MOD_TRANSRULES_ERR_MCC_MNC_APPID_COMBINATION_ALREADY_PRESENT)
        {
            IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;
            LocalIwfTranslatorRuleConfigObj.set_mcc(pIwfTranslatorRuleConfig -> mcc());
            LocalIwfTranslatorRuleConfigObj.set_mnc(pIwfTranslatorRuleConfig -> mnc());
            LocalIwfTranslatorRuleConfigObj.set_appid(pIwfTranslatorRuleConfig -> appid());

            sql_IWFTranslatorRule_Create_Select_Query(&LocalIwfTranslatorRuleConfigObj,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = GENERIC_ERR_DB_ERROR;

                DLOG_NONE(" < %s ",__FUNCTION__);
                return;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() > 0)
            {
                if(pRes->next())
                {
                    if(!pRes->isNull("RULE_NAME"))
                        err->add_variables(pRes->getString("RULE_NAME"));
                }
            }
            delete pRes;
        }
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFVplmnId_Config_Reqs(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(pIwfTranslatorRuleConfig->has_translatorrulename())
        err->add_variables(pIwfTranslatorRuleConfig->translatorrulename());

    /*IwfVplmnIdConfig *pIwfVplmnIdConfigReq = NULL;
    pIwfVplmnIdConfigReq = IwfTranslatorRuleConfig -> mutable_vplmninfo();

    if(pIwfVplmnIdConfigReq && pIwfVplmnIdConfigReq -> has_allowedvplmnid())
        err->add_variables(pIwfVplmnIdConfigReq->allowedvplmnid());
*/
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFVplmnId_Config_Reqs(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(pIwfTranslatorRuleConfig->has_translatorrulename())
        err->add_variables(pIwfTranslatorRuleConfig->translatorrulename());

    IwfVplmnIdConfig *pIwfVplmnIdConfigReq = NULL;
    if(pIwfTranslatorRuleConfig -> vplmninfo_size() > iIndex && iIndex > -1)
    {
        pIwfVplmnIdConfigReq = pIwfTranslatorRuleConfig -> mutable_vplmninfo(iIndex);
    }

    if(pIwfVplmnIdConfigReq && pIwfVplmnIdConfigReq -> has_allowedvplmnid())
        err->add_variables(pIwfVplmnIdConfigReq->allowedvplmnid());

    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrIwfDbInterface::mysql_set_error_for_IWFTranslatorRule_Config_Reqs(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp,DbStatus_e iReturn,std::string& RuleName)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error value is %d", iReturn);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(pIwfTranslatorRuleConfig->has_translatorrulename())
        err->add_variables(pIwfTranslatorRuleConfig->translatorrulename());

    err->add_variables(RuleName);

    if(pIwfTranslatorRuleConfig->has_proactionrulename())
        err->add_variables(pIwfTranslatorRuleConfig->proactionrulename());
    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrIwfDbInterface::mysql_set_error_for_IWFTranslatorType_Config_Reqs(IwfTranslatorType *pIwfTranslatorType,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(pIwfTranslatorType->has_translatortypename())
        err->add_variables(pIwfTranslatorType->translatortypename());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFTranslator_Config_Reqs(IwfTranslatorConfig *pIwfTranslatorConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFTranslatorRule_protobuff(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFTranslatorRule_Create_Select_Query(pIwfTranslatorRuleConfig,sStatement);

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
            iReturn = GET_TRANSRULES_ERR_DB_ERROR;

        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("IWF_TRANSLATOR_RULE_ID"))
                    pIwfTranslatorRuleConfig->set_translationruleid(pRes->getInt("IWF_TRANSLATOR_RULE_ID"));
                if(!pRes->isNull("RULE_NAME"))
                    pIwfTranslatorRuleConfig->set_translatorrulename(pRes->getString("RULE_NAME"));
                if(!pRes->isNull("IWF_TRANSLATOR_TYPE_ID"))
                {
                    IwfTranslatorType *pIwfTranslatorType = pIwfTranslatorRuleConfig -> mutable_translatortype();
                    pIwfTranslatorType->set_translatortypeid(pRes->getInt("IWF_TRANSLATOR_TYPE_ID"));
                }
                if(!pRes->isNull("IWF_TRANSLATOR_ID"))
                {
                    IwfTranslatorConfig *pIwfTranslatorConfig = pIwfTranslatorRuleConfig -> mutable_translatorinfo();
                    pIwfTranslatorConfig->set_translatorid(pRes->getInt("IWF_TRANSLATOR_ID"));
                }
                if(!pRes->isNull("DESTINATION_NAME"))
                    pIwfTranslatorRuleConfig->set_destinationname(pRes->getString("DESTINATION_NAME"));
                if(!pRes->isNull("DESTINATION_HOST"))
                    pIwfTranslatorRuleConfig->set_destinationhost(pRes->getString("DESTINATION_HOST"));
                if(!pRes->isNull("ALTERNATE_HOST"))
                    pIwfTranslatorRuleConfig->set_alternatehost(pRes->getString("ALTERNATE_HOST"));
                if(!pRes->isNull("ALTERNATE_REALM"))
                    pIwfTranslatorRuleConfig->set_alternaterealm(pRes->getString("ALTERNATE_REALM"));
                if(!pRes->isNull("MNC"))
                    pIwfTranslatorRuleConfig->set_mnc(pRes->getString("MNC"));
                if(!pRes->isNull("MCC"))
                    pIwfTranslatorRuleConfig->set_mcc(pRes->getString("MCC"));
                if(!pRes->isNull("APPLICATION_ID"))
                    pIwfTranslatorRuleConfig->set_appid(pRes->getString("APPLICATION_ID"));
                if(!pRes->isNull("OSSN"))
                    pIwfTranslatorRuleConfig->set_ossn(pRes->getInt("OSSN"));
                if(!pRes->isNull("DSSN"))
                    pIwfTranslatorRuleConfig->set_dssn(pRes->getInt("DSSN"));
                if(!pRes->isNull("HTTP_URL"))
                    pIwfTranslatorRuleConfig->set_httpurl(pRes->getString("HTTP_URL"));
                if(!pRes->isNull("WEB_SERVICE"))
                    pIwfTranslatorRuleConfig->set_webservice(pRes->getString("WEB_SERVICE"));
                if(!pRes->isNull("IS_RANGE"))
                    pIwfTranslatorRuleConfig->set_isservicekeyinrange(pRes->getInt("IS_RANGE"));
                if(!pRes->isNull("SERVICE_KEY_START_VALUE"))
                    pIwfTranslatorRuleConfig->set_servicekeystartvalue(pRes->getInt("SERVICE_KEY_START_VALUE"));
                if(!pRes->isNull("SERVICE_KEY_END_VALUE"))
                    pIwfTranslatorRuleConfig->set_servicekeyendvalue(pRes->getInt("SERVICE_KEY_END_VALUE"));
                if(!pRes->isNull("CALLING_GT_ADDR_DIGITS"))
                    pIwfTranslatorRuleConfig->set_callinggtaddrdigits(pRes->getString("CALLING_GT_ADDR_DIGITS"));
                if(!pRes->isNull("SERVICE_CONTEXT_ID"))
                    pIwfTranslatorRuleConfig->set_servicecontextid(pRes->getString("SERVICE_CONTEXT_ID"));
                if(!pRes->isNull("SERVICE_KEY"))
                    pIwfTranslatorRuleConfig->set_servicekey(pRes->getString("SERVICE_KEY"));
                if(!pRes->isNull("IMSI_PREFIX"))
                    pIwfTranslatorRuleConfig->set_imsiprefix(pRes->getString("IMSI_PREFIX"));
                if(!pRes->isNull("PRO_ACTION_RULE"))
                    pIwfTranslatorRuleConfig->set_proactionrulename(pRes->getString("PRO_ACTION_RULE"));

            }
        }
        else
        {
            delete pRes;
            return GET_TRANSRULES_ERR_NO_DATA;
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
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFVplmnId_protobuff(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFVplmnId_Create_Select_Query(pIwfTranslatorRuleConfig,sStatement,iIndex);

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
            iReturn = GET_VPLMN_ID_ERR_DB_ERROR;

        mysql_set_error_for_IWFVplmnId_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    IwfVplmnIdConfig *pIwfVplmnIdConfigReq = NULL;
    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            while(pRes->next())
            {
                if(pIwfTranslatorRuleConfig->vplmninfo_size() > iIndex && iIndex > -1)
                {
                    pIwfVplmnIdConfigReq = pIwfTranslatorRuleConfig ->mutable_vplmninfo(iIndex);
                }
                else
                {
                    pIwfVplmnIdConfigReq = pIwfTranslatorRuleConfig ->add_vplmninfo();
                }

                if(!pRes->isNull("VPLMN_ID"))
                    pIwfVplmnIdConfigReq->set_allowedvplmnid(pRes->getString("VPLMN_ID"));
                if(!pRes->isNull("IWF_TRANSLATOR_RULE_ID"))
                   pIwfTranslatorRuleConfig->set_translationruleid(pRes->getInt("IWF_TRANSLATOR_RULE_ID"));
            }
        }
        else
        {
            delete pRes;
            return GET_VPLMN_ID_ERR_NO_DATA;
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
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFTranslatorRules_protobuff(IwfTranslatorRulesConfig *pIwfTranslatorRulesConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    int i=0;
    int ifData = 0;

    IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;
    IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig = NULL;

    int iCount = pIwfTranslatorRulesConfig->ruleinfo_size();
    DLOG_INFO("pIwfTranslatorRulesConfig->ruleinfo_size() = %d",iCount);
    do
    {
        if(iCount != 0)
            pIwfTranslatorRuleConfig = pIwfTranslatorRulesConfig->mutable_ruleinfo(i);
        else
            pIwfTranslatorRuleConfig = &LocalIwfTranslatorRuleConfigObj;

        sql_IWFTranslatorRule_Create_Select_Query(pIwfTranslatorRuleConfig,sStatement);

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
                iReturn = GET_TRANSRULES_ERR_DB_ERROR;

            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
            if(pRes->rowsCount() != 0)
            {
                IwfTranslatorRulesConfig *LocalIwfTranslatorRulesConfig = resp->mutable_translatorrulesinfo();

                while(pRes->next())
                {
                    pIwfTranslatorRuleConfig = LocalIwfTranslatorRulesConfig->add_ruleinfo();

                    ifData = 1;
                    if(!pRes->isNull("IWF_TRANSLATOR_RULE_ID"))
                        pIwfTranslatorRuleConfig->set_translationruleid(pRes->getInt("IWF_TRANSLATOR_RULE_ID"));
                    if(!pRes->isNull("RULE_NAME"))
                        pIwfTranslatorRuleConfig->set_translatorrulename(pRes->getString("RULE_NAME"));
#if 1
                    if(!pRes->isNull("IWF_TRANSLATOR_TYPE_ID"))
                    {
                        IwfTranslatorType *pIwfTranslatorType = pIwfTranslatorRuleConfig -> mutable_translatortype();
                        pIwfTranslatorType->set_translatortypeid(pRes->getInt("IWF_TRANSLATOR_TYPE_ID"));
                        Fill_IWFTranslatorType_protobuff(pIwfTranslatorType,resp);
                    }
                    if(!pRes->isNull("IWF_TRANSLATOR_ID"))
                    {
                        IwfTranslatorConfig *pIwfTranslatorConfig = pIwfTranslatorRuleConfig -> mutable_translatorinfo();
                        pIwfTranslatorConfig->set_translatorid(pRes->getInt("IWF_TRANSLATOR_ID"));
                        Fill_IWFTranslator_protobuff(pIwfTranslatorConfig,resp);
                    }
#endif
                    if(!pRes->isNull("DESTINATION_NAME"))
                        pIwfTranslatorRuleConfig->set_destinationname(pRes->getString("DESTINATION_NAME"));
                    if(!pRes->isNull("DESTINATION_HOST"))
                        pIwfTranslatorRuleConfig->set_destinationhost(pRes->getString("DESTINATION_HOST"));
                    if(!pRes->isNull("ALTERNATE_HOST"))
                        pIwfTranslatorRuleConfig->set_alternatehost(pRes->getString("ALTERNATE_HOST"));
                    if(!pRes->isNull("ALTERNATE_REALM"))
                        pIwfTranslatorRuleConfig->set_alternaterealm(pRes->getString("ALTERNATE_REALM"));
                    if(!pRes->isNull("MNC"))
                        pIwfTranslatorRuleConfig->set_mnc(pRes->getString("MNC"));
                    if(!pRes->isNull("MCC"))
                        pIwfTranslatorRuleConfig->set_mcc(pRes->getString("MCC"));
                    if(!pRes->isNull("APPLICATION_ID"))
                        pIwfTranslatorRuleConfig->set_appid(pRes->getString("APPLICATION_ID"));
                    if(!pRes->isNull("OSSN"))
                        pIwfTranslatorRuleConfig->set_ossn(pRes->getInt("OSSN"));
                    if(!pRes->isNull("DSSN"))
                        pIwfTranslatorRuleConfig->set_dssn(pRes->getInt("DSSN"));
                    if(!pRes->isNull("HTTP_URL"))
                        pIwfTranslatorRuleConfig->set_httpurl(pRes->getString("HTTP_URL"));
                    if(!pRes->isNull("WEB_SERVICE"))
                        pIwfTranslatorRuleConfig->set_webservice(pRes->getString("WEB_SERVICE"));
                    if(!pRes->isNull("IS_RANGE"))
                        pIwfTranslatorRuleConfig->set_isservicekeyinrange(pRes->getInt("IS_RANGE"));
                    if(!pRes->isNull("SERVICE_KEY_START_VALUE"))
                        pIwfTranslatorRuleConfig->set_servicekeystartvalue(pRes->getInt("SERVICE_KEY_START_VALUE"));
                    if(!pRes->isNull("SERVICE_KEY_END_VALUE"))
                        pIwfTranslatorRuleConfig->set_servicekeyendvalue(pRes->getInt("SERVICE_KEY_END_VALUE"));
                    if(!pRes->isNull("CALLING_GT_ADDR_DIGITS"))
                        pIwfTranslatorRuleConfig->set_callinggtaddrdigits(pRes->getString("CALLING_GT_ADDR_DIGITS"));
                    if(!pRes->isNull("SERVICE_CONTEXT_ID"))
                        pIwfTranslatorRuleConfig->set_servicecontextid(pRes->getString("SERVICE_CONTEXT_ID"));
                    if(!pRes->isNull("SERVICE_KEY"))
                        pIwfTranslatorRuleConfig->set_servicekey(pRes->getString("SERVICE_KEY"));
                    if(!pRes->isNull("IMSI_PREFIX"))
                        pIwfTranslatorRuleConfig->set_imsiprefix(pRes->getString("IMSI_PREFIX"));
                    if(!pRes->isNull("PRO_ACTION_RULE"))
                        pIwfTranslatorRuleConfig->set_proactionrulename(pRes->getString("PRO_ACTION_RULE"));

                    Fill_IWFVplmnId_protobuff(pIwfTranslatorRuleConfig,resp,-1);
                }
            }
            else
            {
                delete pRes;
                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,GET_TRANSRULES_ERR_NO_DATA);
                return GET_TRANSRULES_ERR_NO_DATA;
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
        DLOG_DEBUG("There is no data in the table setting GET_TRANSRULES_ERR_NO_DATA");
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(GET_TRANSRULES_ERR_NO_DATA);
        err->set_errormsgkey(iwfErrorMap[GET_TRANSRULES_ERR_NO_DATA]);
        DLOG_DEBUG("Error key is %s", (iwfErrorMap[GET_TRANSRULES_ERR_NO_DATA]).c_str());

        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFTranslatorType_protobuff(IwfTranslatorType *pIwfTranslatorType,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFTranslatorType_Create_Select_Query(pIwfTranslatorType,sStatement);

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
            iReturn = GET_TRANSRULES_ERR_DB_ERROR;

        mysql_set_error_for_IWFTranslatorType_Config_Reqs(pIwfTranslatorType,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("IWF_TRANSLATOR_TYPE_ID"))
                    pIwfTranslatorType->set_translatortypeid(pRes->getInt("IWF_TRANSLATOR_TYPE_ID"));
                if(!pRes->isNull("IWF_TRANSLATOR_TYPE"))
                   pIwfTranslatorType->set_translatortypename(pRes->getString("IWF_TRANSLATOR_TYPE"));
            }
        }
        else
        {
            delete pRes;
            return GET_TRANSLATOR_TYPE_ERR_NO_DATA;
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
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFTranslator_protobuff(IwfTranslatorConfig *pIwfTranslatorConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFTranslator_Create_Select_Query(pIwfTranslatorConfig,sStatement);

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
            iReturn = GET_TRANSRULES_ERR_DB_ERROR;

        mysql_set_error_for_IWFTranslator_Config_Reqs(pIwfTranslatorConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("IWF_TRANSLATOR_ID"))
                    pIwfTranslatorConfig->set_translatorid(pRes->getInt("IWF_TRANSLATOR_ID"));
                if(!pRes->isNull("IWF_TRANSLATOR"))
                    pIwfTranslatorConfig->set_translatorname(pRes->getString("IWF_TRANSLATOR"));
            }
        }
        else
        {
            delete pRes;
            return GET_TRANSLATOR_ERR_NO_DATA;
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
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFVplmnId_Del_Validation(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,int iIndex)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE("iIndex = %d ",iIndex);

    {
        IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;
        LocalIwfTranslatorRuleConfigObj.set_translatorrulename(pIwfTranslatorRuleConfig->translatorrulename());

        sql_IWFTranslatorRule_Create_Check_Modifcation_Query(&LocalIwfTranslatorRuleConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_VPLMN_ID_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Record not Present:DEL_VPLMN_ID_ERR_TRANSRULE_NOT_PRESENT!");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_VPLMN_ID_ERR_TRANSRULE_NOT_PRESENT;
        }
        delete pRes;
    }

    {
        pRes = NULL;
        IwfVplmnIdConfig *pLocalIwfVplmnIdConfig = pIwfTranslatorRuleConfig -> mutable_vplmninfo(iIndex);
        IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;
        IwfVplmnIdConfig *pLocalIwfVplmnIdConfigSecond = LocalIwfTranslatorRuleConfigObj.add_vplmninfo();
        pLocalIwfVplmnIdConfigSecond -> set_allowedvplmnid(pLocalIwfVplmnIdConfig->allowedvplmnid());
        LocalIwfTranslatorRuleConfigObj.set_translatorrulename(pIwfTranslatorRuleConfig->translatorrulename());

        sql_IWFVplmnId_Create_Select_Query(&LocalIwfTranslatorRuleConfigObj,sStatement,0);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_VPLMN_ID_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Record Present:DEL_VPLMN_ID_ERR_NOT_PRESENT!");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_VPLMN_ID_ERR_NOT_PRESENT;
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

#if 1
DbStatus_e CMgrIwfDbInterface::mysql_IWFTranslatorVplmnId_Del_Config_Reqs(IwfTranslatorRulesConfig *pIwfTranslatorRulesConfig,IWFCfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iTranslatorRulesCount = pIwfTranslatorRulesConfig->ruleinfo_size();
    if(iTranslatorRulesCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(DEL_VPLMN_ID_ERR_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_MULTIHOMINGIP_ERR_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iTranslatorRulesCount;i++)
    {
        IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig = pIwfTranslatorRulesConfig->mutable_ruleinfo(i);

        int iCount = pIwfTranslatorRuleConfig->vplmninfo_size();
        DLOG_NONE("iCount =%d ",iCount);
        if(iCount == 0)
        {
            ErrorDetails* err = resp->add_errordetails();
            err->set_errorcode(DEL_MULTIHOMINGIP_ERR_NOT_SET);
            err->set_errormsgkey(iwfErrorMap[DEL_MULTIHOMINGIP_ERR_NOT_SET]);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return IWF_DB_FAIL;
        }

        for(int i=0;i<iCount;i++)
        {
            //IwfVplmnIdConfig *pIwfVplmnIdConfig = pIwfTranslatorRuleConfig->mutable_vplmninfo(i);

            if((iReturn = mysql_IWFVplmnId_Del_Validation(pIwfTranslatorRuleConfig,i)) != IWF_DB_SUCCESS)
            {
                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_VPLMN_ID_ERR_DB_ERROR;

                mysql_set_error_for_IWFVplmnId_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn,i);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if(iReturn == IWF_DB_SUCCESS)
            {
                sql_IWFVplmnId_Create_Delete_Query(pIwfTranslatorRuleConfig,sStatement,i);
            }

            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_VPLMN_ID_ERR_DB_ERROR;

                mysql_set_error_for_IWFVplmnId_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            //Fill all the configurations related to translator rule which is helpful for deletion in IWF
            Fill_IWFTranslatorRule_protobuff(pIwfTranslatorRuleConfig,resp);
        }
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}
#endif

DbStatus_e CMgrIwfDbInterface::mysql_IWFTranslatorRule_Del_Config_Reqs(IwfTranslatorRulesConfig *req,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::IwfTranslatorRulesConfig *pIwfTranslatorRulesConfig = req;
    ::IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pIwfTranslatorRulesConfig->ruleinfo_size() > 0) //if Rule Count is greater than 0
    {
        IwfTranslatorRulesConfig LocalIwfTranslatorRulesConfig;
        LocalIwfTranslatorRulesConfig.set_operreqid(req->operreqid());
        unsigned int trans_rule_size = pIwfTranslatorRulesConfig->ruleinfo_size();
        for (unsigned int iIndex = 0 ; iIndex < trans_rule_size ; iIndex++)
        {
            IwfTranslatorRuleConfig *pLocalIwfTranslatorRuleConfig = LocalIwfTranslatorRulesConfig.add_ruleinfo();
            pIwfTranslatorRuleConfig = pIwfTranslatorRulesConfig->mutable_ruleinfo(iIndex);
            sql_IWFTranslatorRule_Create_Check_Modifcation_Query(pIwfTranslatorRuleConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_TRANSRULES_ERR_DB_ERROR;

                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);
            DLOG_DEBUG("rowsCount()= %d",pRes->rowsCount());

            if(pRes->rowsCount() == 0) // ADD
            {
                delete pRes;
                DLOG_ERROR("Record Not Present");
                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,DEL_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT;

            }
            else // DEL
            {
                delete pRes;
                pLocalIwfTranslatorRuleConfig->set_translatorrulename(pIwfTranslatorRuleConfig->translatorrulename());
                Fill_IWFTranslatorRule_protobuff(pLocalIwfTranslatorRuleConfig,resp);

                sql_IWFTranslatorRule_Create_Delete_Query(pIwfTranslatorRuleConfig,sStatement);
            }

            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                DLOG_NONE(" < %s ",__FUNCTION__);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_TRANSRULES_ERR_DB_ERROR;

                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

        }
        req->CopyFrom(LocalIwfTranslatorRulesConfig);
    }
    else // No rules to Modify
    {
        iReturn = DEL_TRANSRULES_ERR_DATA_NOT_PRESENT;
        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFTranslatorRule_Mod_Validation(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pIwfTranslatorRuleConfig -> has_mcc() && pIwfTranslatorRuleConfig -> has_mnc() && pIwfTranslatorRuleConfig -> has_appid())
    {
        IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;
        LocalIwfTranslatorRuleConfigObj.set_mcc(pIwfTranslatorRuleConfig -> mcc());
        LocalIwfTranslatorRuleConfigObj.set_mnc(pIwfTranslatorRuleConfig -> mnc());
        LocalIwfTranslatorRuleConfigObj.set_appid(pIwfTranslatorRuleConfig -> appid());

        sql_IWFTranslatorRule_Create_Select_Query(&LocalIwfTranslatorRuleConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = GENERIC_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(pRes->getString("RULE_NAME") != pIwfTranslatorRuleConfig -> translatorrulename())
                {
                    delete pRes;
                    DLOG_ERROR("Same Combination for MCC-MNC-APPID is already present!");
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_TRANSRULES_ERR_MCC_MNC_APPID_COMBINATION_ALREADY_PRESENT;
                }
            }
            delete pRes;
        }
        else
            delete pRes;
    }

    if(pIwfTranslatorRuleConfig->has_servicekey() || pIwfTranslatorRuleConfig->has_imsiprefix())
    {
        IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;

        if(pIwfTranslatorRuleConfig->has_servicekey())
        {
            LocalIwfTranslatorRuleConfigObj.set_servicekey(pIwfTranslatorRuleConfig->servicekey());
        }

        if(pIwfTranslatorRuleConfig->has_imsiprefix())
        {
            LocalIwfTranslatorRuleConfigObj.set_imsiprefix(pIwfTranslatorRuleConfig->imsiprefix());
        }
        std::string RuleName="";
        IwfTranslatorConfig *pIwfTranslatorConfig = pIwfTranslatorRuleConfig->mutable_translatorinfo();
        IwfTranslatorConfig *pLocalTranslatorConfig = LocalIwfTranslatorRuleConfigObj.mutable_translatorinfo();
        pLocalTranslatorConfig->set_translatorname(pIwfTranslatorConfig->translatorname().c_str());

        if((iReturn = validate_ImsiPrefix_and_ServiceKey(&LocalIwfTranslatorRuleConfigObj,resp,RuleName)) != IWF_DB_SUCCESS)
        {
            if(iReturn == ADD_TRANSRULES_ERR_IMSI_PREFIX_AND_SERVICE_KEY_ALREADY_PRESENT)
                iReturn = MOD_TRANSRULES_ERR_IMSI_PREFIX_AND_SERVICE_KEY_ALREADY_PRESENT;
            LocalIwfTranslatorRuleConfigObj.set_translatorrulename(pIwfTranslatorRuleConfig->translatorrulename().c_str());

            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(&LocalIwfTranslatorRuleConfigObj,resp,iReturn,RuleName);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    else if(pIwfTranslatorRuleConfig->has_isservicekeyinrange())
    {
        //Validate the serviceKey value
        IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;
        LocalIwfTranslatorRuleConfigObj.set_translatorrulename(pIwfTranslatorRuleConfig->translatorrulename().c_str());
        LocalIwfTranslatorRuleConfigObj.set_isservicekeyinrange(pIwfTranslatorRuleConfig->isservicekeyinrange());

        if(pIwfTranslatorRuleConfig->has_servicekey())
        {
            LocalIwfTranslatorRuleConfigObj.set_servicekey(pIwfTranslatorRuleConfig->servicekey());
        }
        std::string RuleName="";
        if((iReturn = validate_ServiceKey(&LocalIwfTranslatorRuleConfigObj,resp,RuleName)) != IWF_DB_SUCCESS)
        {
            if(iReturn == ADD_TRANSRULES_ERR_SERVICE_KEY_ALREADY_PRESENT)
                iReturn = MOD_TRANSRULES_ERR_SERVICE_KEY_ALREADY_PRESENT;

            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(&LocalIwfTranslatorRuleConfigObj,resp,iReturn,RuleName);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    //Validation for ProActionRuleName
    if(pIwfTranslatorRuleConfig->has_proactionrulename())
    {
        IwfProtocolActionConfig pIwfProtocolActionConfig;
        pIwfProtocolActionConfig.set_actionrulename(pIwfTranslatorRuleConfig->proactionrulename().c_str());
        sql_IWFProtocolAction_Create_Check_Modifcation_Query(&pIwfProtocolActionConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_TRANSRULES_ERR_DB_ERROR;

            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            //NOTE: ProtocolActionRule Not Present in IWF_PROTOCOL_ACTION_TB
            delete pRes;
            DLOG_ERROR("Record Not Present");
            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,MOD_TRANSRULES_ERR_PROTOCOL_ACTION_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_TRANSRULES_ERR_PROTOCOL_ACTION_NOT_PRESENT;
        }
        delete pRes;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFTranslatorRule_Mod_Config_Reqs(IwfTranslatorRulesConfig *req,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    ::IwfTranslatorRulesConfig *pIwfTranslatorRulesConfig = req;
    ::IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pIwfTranslatorRulesConfig->ruleinfo_size() > 0) //if Rule Count is greater than 0
    {
        //NOTE: For Modify Translator Rule , Rule Name and Translator-Type is considered as primary key
        unsigned int trans_rule_size = pIwfTranslatorRulesConfig->ruleinfo_size();
        for (unsigned int iIndex = 0 ; iIndex < trans_rule_size ; iIndex++)
        {
            pIwfTranslatorRuleConfig = pIwfTranslatorRulesConfig->mutable_ruleinfo(iIndex);
            if(pIwfTranslatorRuleConfig->has_translatorrulename() && pIwfTranslatorRuleConfig->has_translatortype() && pIwfTranslatorRuleConfig->has_translatorinfo())
            {
                ::IwfTranslatorRuleConfig pLocalIwfTranslatorRuleConfig;

                pLocalIwfTranslatorRuleConfig.set_translatorrulename(pIwfTranslatorRuleConfig->translatorrulename().c_str());
                ::IwfTranslatorType *pIwfTranslatorType = pIwfTranslatorRuleConfig->mutable_translatortype();
                ::IwfTranslatorConfig *pIwfTranslatorConfig = pIwfTranslatorRuleConfig->mutable_translatorinfo();
                //NOTE: Copying old mcc, mnc, appid, isservicekeyinrange, servicekeystartvalue and servicekeyendvalue to Req Buffer
                IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfig;
                LocalIwfTranslatorRuleConfig.set_translatorrulename(pIwfTranslatorRuleConfig->translatorrulename().c_str());
                Fill_IWFTranslatorRule_protobuff(&LocalIwfTranslatorRuleConfig,resp);
                if(LocalIwfTranslatorRuleConfig.has_mcc())
                    pIwfTranslatorRuleConfig->set_oldmcc(LocalIwfTranslatorRuleConfig.mcc());
                if(LocalIwfTranslatorRuleConfig.has_mnc())
                    pIwfTranslatorRuleConfig->set_oldmnc(LocalIwfTranslatorRuleConfig.mnc());
                if(LocalIwfTranslatorRuleConfig.has_appid())
                    pIwfTranslatorRuleConfig->set_oldappid(LocalIwfTranslatorRuleConfig.appid());
                if(LocalIwfTranslatorRuleConfig.has_isservicekeyinrange())
                    pIwfTranslatorRuleConfig->set_oldisservicekeyinrange(LocalIwfTranslatorRuleConfig.isservicekeyinrange());
                if(LocalIwfTranslatorRuleConfig.has_servicekeystartvalue())
                    pIwfTranslatorRuleConfig->set_oldservicekeystartvalue(LocalIwfTranslatorRuleConfig.servicekeystartvalue());
                if(LocalIwfTranslatorRuleConfig.has_servicekeyendvalue())
                    pIwfTranslatorRuleConfig->set_oldservicekeyendvalue(LocalIwfTranslatorRuleConfig.servicekeyendvalue());

                if(pIwfTranslatorType->has_translatortypename() && pIwfTranslatorConfig->has_translatorname())
                {
                    ::IwfTranslatorType *pLocalIwfTranslatorType = pLocalIwfTranslatorRuleConfig.mutable_translatortype();
                    ::IwfTranslatorConfig *pLocalIwfTranslatorConfig = pLocalIwfTranslatorRuleConfig.mutable_translatorinfo();

                    pLocalIwfTranslatorType->set_translatortypename(pIwfTranslatorType->translatortypename().c_str());
                    pLocalIwfTranslatorConfig->set_translatorname(pIwfTranslatorConfig->translatorname().c_str());
                    sql_IWFTranslatorRule_Create_Select_Query(&pLocalIwfTranslatorRuleConfig, sStatement);

                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                    {
                        if(pRes != NULL)
                        {
                            delete pRes;
                        }

                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == DRE_DB_FAIL)
                            iReturn = MOD_TRANSRULES_ERR_DB_ERROR;

                        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }

                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                    if(pRes->rowsCount() == 0) // ADD
                    {
                        delete pRes;
                        DLOG_ERROR("Record Not Present");
                        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,MOD_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return MOD_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT;

                    }

                    delete pRes;
                    //NOTE: Translator Rule Found, Continue with mod operation
                    //CHECK FOR THE FILEDS TO BE MODIFIED based on translator type
                    //Based on that modify the below code

                    if(pIwfTranslatorRuleConfig->has_translatortype())
                    {
                        ::IwfTranslatorType *pIwfTranslatorType = pIwfTranslatorRuleConfig->mutable_translatortype();
                        if(pIwfTranslatorType->has_translatortypename())
                        {
                            string trans_type = pIwfTranslatorType->translatortypename().c_str();
                            sql_IWFTranslatorType_Create_Check_Modifcation_Query(pIwfTranslatorType,sStatement);

                            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                            {
                                if(pRes != NULL)
                                {
                                    delete pRes;
                                }

                                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                if(iReturn == DRE_DB_FAIL)
                                    iReturn = MOD_TRANSRULES_ERR_DB_ERROR;

                                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                DLOG_DEBUG("iReturn = %d",iReturn);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return iReturn;
                            }

                            memset(sStatement,0,MAX_STATEMENT_SIZE);

                            if(pRes->rowsCount() == 0) // ADD
                            {
                                delete pRes;
                                //NOTE: Translator Rule Not Present
                                DLOG_ERROR("Record Not Present");
                                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,MOD_TRANSRULES_ERR_TRANSLATORTYPE_NOT_PRESENT);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return MOD_TRANSRULES_ERR_TRANSLATORTYPE_NOT_PRESENT;
                            }
                            delete pRes;
                            if((!strcmp(trans_type.c_str(), "SS7") || !strcmp(trans_type.c_str(), "DIAMETER")))
                            {
                                if(!strcmp(trans_type.c_str(), "SS7"))
                                {
                                    if(pIwfTranslatorRuleConfig->has_destinationname())
                                    {
                                        ::RealmConfig pRealmConfig;
                                        pRealmConfig.set_realmname(pIwfTranslatorRuleConfig->destinationname().c_str());

                                        sql_Realm_Create_Check_Modifcation_Query(&pRealmConfig,sStatement);
                                        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                                        {
                                            if(pRes != NULL)
                                            {
                                                delete pRes;
                                            }

                                            DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                            if(iReturn == DRE_DB_FAIL)
                                                iReturn = MOD_TRANSRULES_ERR_DB_ERROR;

                                            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                            DLOG_DEBUG("iReturn = %d",iReturn);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return iReturn;
                                        }

                                        memset(sStatement,0,MAX_STATEMENT_SIZE);

                                        if(pRes->rowsCount() == 0) // ADD
                                        {
                                            //NOTE: Destination(RealmName) Not Present in REALM_TB
                                            delete pRes;
                                            DLOG_ERROR("Record Not Present");
                                            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,MOD_TRANSRULES_ERR_DESTINATION_NOT_PRESENT);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return MOD_TRANSRULES_ERR_DESTINATION_NOT_PRESENT;
                                        }
                                        delete pRes;
                                        pRes = NULL;
                                    }
                                    if(pIwfTranslatorRuleConfig->has_destinationname() && pIwfTranslatorRuleConfig->has_destinationhost())
                                    {
                                        PeerConfig lPeerConfig;
                                        lPeerConfig.set_peerhostname(pIwfTranslatorRuleConfig->destinationhost().c_str());
                                        lPeerConfig.set_realm(pIwfTranslatorRuleConfig->destinationname().c_str());

                                        PeerTPBQuery lPeerTPBQuery;
                                        lPeerTPBQuery.sql_Peer_Create_Check_Modifcation_Query(&lPeerConfig,sStatement);

                                        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                                        {
                                            if(pRes != NULL)
                                            {
                                                delete pRes;
                                            }

                                            DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                            if(iReturn == DRE_DB_FAIL)
                                                iReturn = MOD_TRANSRULES_ERR_DB_ERROR;

                                            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                            DLOG_DEBUG("iReturn = %d",iReturn);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return iReturn;
                                        }

                                        memset(sStatement,0,MAX_STATEMENT_SIZE);

                                        if(pRes->rowsCount() == 0) // ADD
                                        {
                                            //NOTE: Destination Not Present in IWF_SIGTRAN_DESTINATION_TB
                                            delete pRes;
                                            DLOG_ERROR("Record Not Present");
                                            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,MOD_TRANSRULES_ERR_DESTINATION_HOST_NOT_PRESENT);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return MOD_TRANSRULES_ERR_DESTINATION_HOST_NOT_PRESENT;
                                        }
                                        delete pRes;
                                        pRes = NULL;
                                    }
                                    if(pIwfTranslatorRuleConfig->has_alternatehost() && pIwfTranslatorRuleConfig->has_alternaterealm())
                                    {
                                        PeerConfig lPeerConfig;
                                        lPeerConfig.set_peerhostname(pIwfTranslatorRuleConfig->alternatehost().c_str());
                                        lPeerConfig.set_realm(pIwfTranslatorRuleConfig->alternaterealm().c_str());

                                        PeerTPBQuery lPeerTPBQuery;
                                        lPeerTPBQuery.sql_Peer_Create_Check_Modifcation_Query(&lPeerConfig,sStatement);

                                        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                                        {
                                            if(pRes != NULL)
                                            {
                                                delete pRes;
                                            }

                                            DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                            if(iReturn == DRE_DB_FAIL)
                                                iReturn = MOD_TRANSRULES_ERR_DB_ERROR;

                                            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                            DLOG_DEBUG("iReturn = %d",iReturn);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return iReturn;
                                        }

                                        memset(sStatement,0,MAX_STATEMENT_SIZE);

                                        if(pRes->rowsCount() == 0) // ADD
                                        {
                                            //NOTE: Destination Not Present in IWF_SIGTRAN_DESTINATION_TB
                                            delete pRes;
                                            DLOG_ERROR("Record Not Present");
                                            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,MOD_TRANSRULES_ERR_ALTERNATE_HOST_NOT_PRESENT);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return MOD_TRANSRULES_ERR_ALTERNATE_HOST_NOT_PRESENT;
                                        }
                                        delete pRes;
                                        pRes = NULL;
                                    }
                                }
                                else // If Trans-Type is DIAMETER
                                {
                                    if(pIwfTranslatorRuleConfig->has_destinationname())
                                    {
                                        ::IwfSigtranDestinationConfig pIwfSigtranDestinationConfig;
                                        pIwfSigtranDestinationConfig.set_destinationname(pIwfTranslatorRuleConfig->destinationname().c_str());

                                        sql_IWFSigtranDestination_Create_Check_Modifcation_Query(&pIwfSigtranDestinationConfig,sStatement);

                                        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                                        {
                                            if(pRes != NULL)
                                            {
                                                delete pRes;
                                            }

                                            DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                            if(iReturn == DRE_DB_FAIL)
                                                iReturn = MOD_TRANSRULES_ERR_DB_ERROR;

                                            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                            DLOG_DEBUG("iReturn = %d",iReturn);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return iReturn;
                                        }

                                        memset(sStatement,0,MAX_STATEMENT_SIZE);

                                        if(pRes->rowsCount() == 0) // ADD
                                        {
                                            //NOTE: Destination Not Present in IWF_SIGTRAN_DESTINATION_TB
                                            delete pRes;
                                            DLOG_ERROR("Record Not Present");
                                            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,MOD_TRANSRULES_ERR_DESTINATION_NOT_PRESENT);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return MOD_TRANSRULES_ERR_DESTINATION_NOT_PRESENT;
                                        }
                                        delete pRes;
                                        pRes = NULL;

                                        //NOTE: Validate Destination is part of RemoteRoute
                                        IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfig;
                                        IwfSigtranDestinationConfig *pIwfSigtranDestinationConfigReq = LocalIwfSigtranRemoteRouteConfig.mutable_destinationinfo();
                                        pIwfSigtranDestinationConfigReq->set_destinationname(pIwfTranslatorRuleConfig->destinationname().c_str());
                                        sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfig,sStatement);
                                        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                        {    
                                            if(pRes != NULL)    
                                            {    
                                                delete pRes;
                                            }    
                                            DLOG_ERROR("Query Execution Failed %s",sStatement);

                                            if(iReturn == IWF_DB_FAIL)
                                                iReturn = MOD_TRANSRULES_ERR_DB_ERROR;


                                            DLOG_DEBUG("iReturn = %d",iReturn);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return iReturn;
                                        }    


                                        memset(sStatement,0,MAX_STATEMENT_SIZE);

                                        if(pRes->rowsCount() <= 0) // ADD
                                        {
                                            delete pRes;
                                            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,
                                                    MOD_TRANSRULES_ERR_DEST_NOT_PART_OF_REMOTE_ROUTE);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return MOD_TRANSRULES_ERR_DEST_NOT_PART_OF_REMOTE_ROUTE;
                                        }
                                        delete pRes;
                                        pRes = NULL;
                                    }
                                    
                                    if(pIwfTranslatorRuleConfig->has_alternaterealm())
                                    {
                                        ::IwfSigtranDestinationConfig pIwfSigtranDestinationConfig;
                                        pIwfSigtranDestinationConfig.set_destinationname(pIwfTranslatorRuleConfig->alternaterealm().c_str());

                                        sql_IWFSigtranDestination_Create_Check_Modifcation_Query(&pIwfSigtranDestinationConfig,sStatement);

                                        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                                        {
                                            if(pRes != NULL)
                                            {
                                                delete pRes;
                                            }

                                            DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                            if(iReturn == DRE_DB_FAIL)
                                                iReturn = MOD_TRANSRULES_ERR_DB_ERROR;

                                            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                            DLOG_DEBUG("iReturn = %d",iReturn);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return iReturn;
                                        }

                                        memset(sStatement,0,MAX_STATEMENT_SIZE);

                                        if(pRes->rowsCount() == 0) // ADD
                                        {
                                            //NOTE: Destination Not Present in IWF_SIGTRAN_DESTINATION_TB
                                            delete pRes;
                                            DLOG_ERROR("Record Not Present");
                                            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,MOD_TRANSRULES_ERR_ALT_DESTINATION_NOT_PRESENT);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return MOD_TRANSRULES_ERR_ALT_DESTINATION_NOT_PRESENT;
                                        }
                                        delete pRes;
                                        pRes = NULL;

                                        //NOTE: Validate Destination is part of RemoteRoute
                                        IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfig;
                                        IwfSigtranDestinationConfig *pIwfSigtranDestinationConfigReq = LocalIwfSigtranRemoteRouteConfig.mutable_destinationinfo();
                                        pIwfSigtranDestinationConfigReq->set_destinationname(pIwfTranslatorRuleConfig->alternaterealm().c_str());
                                        sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfig,sStatement);
                                        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                        {    
                                            if(pRes != NULL)    
                                            {    
                                                delete pRes;
                                            }    
                                            DLOG_ERROR("Query Execution Failed %s",sStatement);

                                            if(iReturn == IWF_DB_FAIL)
                                                iReturn = MOD_TRANSRULES_ERR_DB_ERROR;


                                            DLOG_DEBUG("iReturn = %d",iReturn);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return iReturn;
                                        }    


                                        memset(sStatement,0,MAX_STATEMENT_SIZE);

                                        if(pRes->rowsCount() <= 0) // ADD
                                        {
                                            delete pRes;
                                            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,
                                                    MOD_TRANSRULES_ERR_ALT_DEST_NOT_PART_OF_REMOTE_ROUTE);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return MOD_TRANSRULES_ERR_ALT_DEST_NOT_PART_OF_REMOTE_ROUTE;
                                        }
                                        delete pRes;
                                        pRes = NULL;
                                    }
                                }
                            }

                            if((iReturn = mysql_IWFTranslatorRule_Mod_Validation(pIwfTranslatorRuleConfig,resp)) != IWF_DB_SUCCESS)
                            {
                                if(iReturn == IWF_DB_FAIL)
                                    iReturn = MOD_TRANSRULES_ERR_DB_ERROR;

                                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                DLOG_DEBUG("iReturn = %d",iReturn);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return iReturn;
                            }

                            if(pIwfTranslatorRuleConfig->has_ossn())
                            {
                                //NOTE: If Ossn present in Modify Req set old OSSN in req
                                //      This old OSSN will be useful to delete the rule and add again
                                IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfig;
                                LocalIwfTranslatorRuleConfig.set_translatorrulename(pIwfTranslatorRuleConfig->translatorrulename());
                                sql_IWFTranslatorRule_Create_Select_Query(&LocalIwfTranslatorRuleConfig,sStatement);

                                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                {
                                    if(pRes != NULL)
                                    {
                                        delete pRes;
                                    }

                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                                    if(iReturn == IWF_DB_FAIL)
                                        iReturn = MOD_TRANSRULES_ERR_DB_ERROR;

                                    mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return iReturn;
                                }

                                DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
                                if(pRes->rowsCount() != 0)
                                {
                                    if(pRes->next())
                                    {
                                        if(!pRes->isNull("OSSN"))
                                            pIwfTranslatorRuleConfig->set_oldossn(pRes->getInt("OSSN"));
                                    }
                                }
                                delete pRes;
                                pRes = NULL;

                            }
                            sql_IWFTranslatorRule_Create_Mod_Query(pIwfTranslatorRuleConfig,sStatement);

                            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                            {
                                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                                DLOG_NONE(" < %s ",__FUNCTION__);

                                if(iReturn == DRE_DB_FAIL)
                                    iReturn = MOD_TRANSRULES_ERR_DB_ERROR;

                                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                DLOG_DEBUG("iReturn = %d",iReturn);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return iReturn;
                            }
                            //Fill all the values after updation in DB
                            Fill_IWFTranslatorRule_protobuff(pIwfTranslatorRuleConfig,resp);
                        }
                        else
                        {
                            iReturn = MOD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
                            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                            DLOG_DEBUG("iReturn = %d",iReturn);
                            DLOG_NONE(" < %s ",__FUNCTION__);
                            return iReturn;
                        }
                    }
                    else
                    {
                        iReturn = MOD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
                        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                }
                else
                {
                    iReturn = MOD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
                    mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    DLOG_DEBUG("iReturn = %d",iReturn);
                    return iReturn;
                }
                int iVplmnIdCount = pIwfTranslatorRuleConfig->vplmninfo_size();
                for(int j=0;j<iVplmnIdCount;j++)
                {
                    if((iReturn = mysql_IWFVplmnId_Validation(pIwfTranslatorRuleConfig,resp,j)) != IWF_DB_SUCCESS)
                    {
                        if(iReturn == IWF_DB_FAIL)
                            iReturn = MOD_TRANSRULES_ERR_DB_ERROR;
                        else if(iReturn == MOD_TRANSRULES_ERR_DB_ERROR)
                            iReturn = MOD_TRANSRULES_ERR_DB_ERROR;
                        else if(iReturn == MOD_TRANSRULES_ERR_VPLMN_ID_ALREADY_PRESENT)
                            iReturn = MOD_TRANSRULES_ERR_VPLMN_ID_ALREADY_PRESENT;

                        mysql_set_error_for_IWFVplmnId_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn,j);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }

                    sql_IWFVplmnId_Create_Check_Modifcation_Query(pIwfTranslatorRuleConfig,sStatement,j);
                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                    {
                        if(pRes != NULL)
                        {
                            delete pRes;
                        }
                        DLOG_ERROR("Query Execution Failed %s",sStatement);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;

                        mysql_set_error_for_IWFVplmnId_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn,j);

                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }

                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                    if(pRes->rowsCount() == 0) // ADD
                    {
                        sql_IWFVplmnId_Create_Add_Query(pIwfTranslatorRuleConfig,sStatement,j);
                    }
                    else // MOD
                    {
                        delete pRes;
                        DLOG_ERROR("Record Already Present");
                        mysql_set_error_for_IWFVplmnId_Config_Reqs(pIwfTranslatorRuleConfig,resp,MOD_SCTPENDPOINT_ERR_MULTIHOMING_IP_ALREADY_PRESENT,j);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return MOD_SCTPENDPOINT_ERR_MULTIHOMING_IP_ALREADY_PRESENT;
                    }

                    delete pRes;
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed %s",sStatement);
                        if(iReturn == IWF_DB_FAIL)
                            iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;

                        mysql_set_error_for_IWFVplmnId_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn,j);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                }
                pIwfTranslatorRuleConfig->clear_vplmninfo();
                Fill_IWFVplmnId_protobuff(pIwfTranslatorRuleConfig, resp, -1);
            }
            else
            {
                iReturn = MOD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
    }
    else // No rules to Modify
    {
        iReturn = MOD_TRANSRULES_ERR_DATA_NOT_PRESENT;
        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFTranslatorRule_Add_Validation(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pIwfTranslatorRuleConfig -> has_mcc() && pIwfTranslatorRuleConfig -> has_mnc() && pIwfTranslatorRuleConfig -> has_appid())
    {
        IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;
        LocalIwfTranslatorRuleConfigObj.set_mcc(pIwfTranslatorRuleConfig -> mcc());
        LocalIwfTranslatorRuleConfigObj.set_mnc(pIwfTranslatorRuleConfig -> mnc());
        LocalIwfTranslatorRuleConfigObj.set_appid(pIwfTranslatorRuleConfig -> appid());

        sql_IWFTranslatorRule_Create_Select_Query(&LocalIwfTranslatorRuleConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = GENERIC_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            DLOG_ERROR("Same Combination for MCC-MNC-APPID is already present!");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_TRANSRULES_ERR_MCC_MNC_APPID_COMBINATION_ALREADY_PRESENT;
        }
        delete pRes;
    }

    if(pIwfTranslatorRuleConfig->has_servicekey() && pIwfTranslatorRuleConfig->has_imsiprefix())
    {
        IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;
        if(pIwfTranslatorRuleConfig->has_servicekey()) 
        {
            LocalIwfTranslatorRuleConfigObj.set_servicekey(pIwfTranslatorRuleConfig->servicekey());
        }

        if(pIwfTranslatorRuleConfig->has_imsiprefix())
        {
            LocalIwfTranslatorRuleConfigObj.set_imsiprefix(pIwfTranslatorRuleConfig->imsiprefix());
        }
        std::string RuleName="";
        IwfTranslatorConfig *pIwfTranslatorConfig = pIwfTranslatorRuleConfig->mutable_translatorinfo();
        IwfTranslatorConfig *pLocalTranslatorConfig = LocalIwfTranslatorRuleConfigObj.mutable_translatorinfo();
        pLocalTranslatorConfig->set_translatorname(pIwfTranslatorConfig->translatorname().c_str());

        if((iReturn = validate_ImsiPrefix_and_ServiceKey(&LocalIwfTranslatorRuleConfigObj,resp,RuleName)) != IWF_DB_SUCCESS)
        {
            LocalIwfTranslatorRuleConfigObj.set_translatorrulename(pIwfTranslatorRuleConfig->translatorrulename().c_str());
            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(&LocalIwfTranslatorRuleConfigObj,resp,iReturn,RuleName);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }
    else if(pIwfTranslatorRuleConfig->has_isservicekeyinrange())
    {
        //Validate the serviceKey value
        IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;
        LocalIwfTranslatorRuleConfigObj.set_translatorrulename(pIwfTranslatorRuleConfig->translatorrulename().c_str());
        LocalIwfTranslatorRuleConfigObj.set_isservicekeyinrange(pIwfTranslatorRuleConfig->isservicekeyinrange());

        if(pIwfTranslatorRuleConfig->has_servicekey())
        {
            LocalIwfTranslatorRuleConfigObj.set_servicekey(pIwfTranslatorRuleConfig->servicekey());
        }
        std::string RuleName="";
        if((iReturn = validate_ServiceKey(&LocalIwfTranslatorRuleConfigObj,resp,RuleName)) != IWF_DB_SUCCESS)
        {
            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(&LocalIwfTranslatorRuleConfigObj,resp,iReturn,RuleName);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    //Validation for ProActionRuleName
    if(pIwfTranslatorRuleConfig->has_proactionrulename())
    {
        IwfProtocolActionConfig pIwfProtocolActionConfig;
        pIwfProtocolActionConfig.set_actionrulename(pIwfTranslatorRuleConfig->proactionrulename().c_str());
        sql_IWFProtocolAction_Create_Check_Modifcation_Query(&pIwfProtocolActionConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_TRANSRULES_ERR_DB_ERROR;

            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            //NOTE: ProtocolActionRule Not Present in IWF_PROTOCOL_ACTION_TB
            delete pRes;
            DLOG_ERROR("Record Not Present");
            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,ADD_TRANSRULES_ERR_PROTOCOL_ACTION_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_TRANSRULES_ERR_PROTOCOL_ACTION_NOT_PRESENT;
        }
        delete pRes;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::validate_ImsiPrefix_and_ServiceKey(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp,std::string& RuleName)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    sql_IWFTranslatorRule_Create_Select_Query(pIwfTranslatorRuleConfig, sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = GENERIC_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() > 0)
    {
        if(pRes->next())
        {
            if(!pRes->isNull("RULE_NAME") &&
                    (pIwfTranslatorRuleConfig->translatorrulename() != pRes->getString("RULE_NAME")))
            {
                if(!pRes->isNull("RULE_NAME"))
                {
                    DLOG_ERROR("ServiceKey/ImsiPrefix collides with Translator Rule %s",pRes->getString("RULE_NAME").c_str());   
                    RuleName = pRes->getString("RULE_NAME").c_str();
                }
                delete pRes;
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_TRANSRULES_ERR_IMSI_PREFIX_AND_SERVICE_KEY_ALREADY_PRESENT;

            }
        }
    }
    delete pRes;
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::validate_ServiceKey(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp,std::string& RuleName)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfig;
    DLOG_NONE(" > %s ",__FUNCTION__);
    if(pIwfTranslatorRuleConfig->has_isservicekeyinrange())
    {
        sql_IWFTranslatorRule_Create_Select_Query(&LocalIwfTranslatorRuleConfig, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = GENERIC_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("RULE_NAME") &&
                        (pIwfTranslatorRuleConfig->translatorrulename() != pRes->getString("RULE_NAME")))
                {
                    if(!pRes->isNull("RULE_NAME"))
                    {
                        DLOG_ERROR("ServiceKey collides with Translator Rule %s",pRes->getString("RULE_NAME").c_str());
                        RuleName = pRes->getString("RULE_NAME").c_str();
                    }
                    delete pRes;
                    mysql_set_error_for_IWFTranslatorRule_Config_Reqs(&LocalIwfTranslatorRuleConfig,resp,
                            ADD_TRANSRULES_ERR_SERVICE_KEY_ALREADY_PRESENT,RuleName);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return ADD_TRANSRULES_ERR_SERVICE_KEY_ALREADY_PRESENT;
                }
            }
        }
        delete pRes;
#if 0
        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                unsigned int isRange = 0;
                unsigned int StartValue = 0;
                unsigned int EndValue = 0;

                if(!pRes->isNull("IS_RANGE"))
                    isRange = pRes->getInt("IS_RANGE");
                if(!pRes->isNull("SERVICE_KEY_START_VALUE"))
                    StartValue = pRes->getInt("SERVICE_KEY_START_VALUE");
                if(!pRes->isNull("SERVICE_KEY_END_VALUE"))
                    EndValue = pRes->getInt("SERVICE_KEY_END_VALUE");

                if(!pIwfTranslatorRuleConfig->isservicekeyinrange()) // If service Key is not Range
                {
                    if(pIwfTranslatorRuleConfig->has_servicekeystartvalue() &&
                            ((isRange &&
                              ((pIwfTranslatorRuleConfig->servicekeystartvalue() >= StartValue) &&
                              (pIwfTranslatorRuleConfig->servicekeystartvalue() <= EndValue))) ||
                            (!isRange && pIwfTranslatorRuleConfig->servicekeystartvalue() == StartValue)) &&
                            !pRes->isNull("RULE_NAME") &&
                            (pIwfTranslatorRuleConfig->translatorrulename() != pRes->getString("RULE_NAME")))
                    {
                        if(!pRes->isNull("RULE_NAME"))
                        {
                            DLOG_ERROR("ServiceKey collides with Translator Rule %s",pRes->getString("RULE_NAME").c_str());
                            RuleName = pRes->getString("RULE_NAME").c_str();
                        }

                        delete pRes;
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return ADD_TRANSRULES_ERR_SERVICE_KEY_ALREADY_PRESENT;
                    }
                }
                else // If service Key is Range
                {
                    //checking with non-range rows
                    if(!isRange)
                    {
                        if(StartValue >= pIwfTranslatorRuleConfig->servicekeystartvalue() &&
                                StartValue <= pIwfTranslatorRuleConfig->servicekeyendvalue() &&
                            !pRes->isNull("RULE_NAME") &&
                            (pIwfTranslatorRuleConfig->translatorrulename() != pRes->getString("RULE_NAME")))
                        {
                            if(!pRes->isNull("RULE_NAME"))
                            {
                                DLOG_ERROR("ServiceKey collides with Translator Rule %s",pRes->getString("RULE_NAME").c_str());
                                RuleName = pRes->getString("RULE_NAME");
                            }
                            delete pRes;
                            DLOG_NONE(" < %s ",__FUNCTION__);
                            return ADD_TRANSRULES_ERR_SERVICE_KEY_ALREADY_PRESENT;
                        }
                    }
                    else //checking with range rows
                    {
                        /*
                         * check for the below mentioned scenario
                         *
                         * 1) if the user input is 210 and 220
                         * and database contains 200 and 300
                         * 2) if the user input is 150 and 210
                         * and databse contains 200 and 300
                         * 3) if the user input is 250 and 350
                         * and database contains 200 and 300
                         *
                         */
                        if(((pIwfTranslatorRuleConfig->servicekeystartvalue() >= StartValue &&
                                pIwfTranslatorRuleConfig->servicekeystartvalue() <= EndValue) ||
                                (pIwfTranslatorRuleConfig->servicekeyendvalue() >= StartValue &&
                                pIwfTranslatorRuleConfig->servicekeyendvalue() <= EndValue)) &&
                                !pRes->isNull("RULE_NAME") &&
                                (pIwfTranslatorRuleConfig->translatorrulename() != pRes->getString("RULE_NAME")))
                        {
                            if(!pRes->isNull("RULE_NAME"))
                            {
                                DLOG_ERROR("ServiceKey collides with Translator Rule %s",pRes->getString("RULE_NAME").c_str());
                                RuleName = pRes->getString("RULE_NAME");
                            }
                            delete pRes;
                            DLOG_NONE(" < %s ",__FUNCTION__);
                            return ADD_TRANSRULES_ERR_SERVICE_KEY_ALREADY_PRESENT;
                        }
                        /**
                         *checking for the below mentioned scenario
                         *
                         * 1) if the user input is 210 and 250
                         * and database contains 200 and 300
                         * 2) if the user input is 210 and 250
                         * and database contains 200 and 230
                         *
                         */
                        else if(((StartValue >= pIwfTranslatorRuleConfig->servicekeystartvalue() &&
                                EndValue <= pIwfTranslatorRuleConfig->servicekeystartvalue()) ||
                                (StartValue >= pIwfTranslatorRuleConfig->servicekeyendvalue() &&
                                EndValue <= pIwfTranslatorRuleConfig->servicekeyendvalue())) &&
                                !pRes->isNull("RULE_NAME") &&
                                (pIwfTranslatorRuleConfig->translatorrulename() != pRes->getString("RULE_NAME")))
                        {
                            if(!pRes->isNull("RULE_NAME"))
                            {
                                DLOG_ERROR("ServiceKey collides with Translator Rule %s",pRes->getString("RULE_NAME").c_str());
                                RuleName = pRes->getString("RULE_NAME");
                            }
                            delete pRes;
                            DLOG_NONE(" < %s ",__FUNCTION__);
                            return ADD_TRANSRULES_ERR_SERVICE_KEY_ALREADY_PRESENT;
                        }
                    }
                }
            }
        }
        delete pRes;
#endif
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFVplmnId_Validation(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig, IWFCfgResp *resp,int iIndex)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

#if 0
    sql_IWFVplmnId_Create_Select_Query(&localIwfTranslatorRuleConfig,sStatement,-1);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = GENERIC_ERR_DB_ERROR;


        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() >= MAX_MULTIHOMING_IP)
    {
        delete pRes;
        DLOG_ERROR("Max Multihoming ip's already present");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return GENERIC_SCTPENDPOINT_ERR_MULTIHOMING_IP_MAXCOUNT;
    }
    delete pRes;

#endif
    IwfVplmnIdConfig *pLocalIwfVplmnIdConfig = pIwfTranslatorRuleConfig -> mutable_vplmninfo(iIndex);
    IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;
    IwfVplmnIdConfig *pLocalIwfVplmnIdConfigSecond = LocalIwfTranslatorRuleConfigObj.add_vplmninfo();
    pLocalIwfVplmnIdConfigSecond -> set_allowedvplmnid(pLocalIwfVplmnIdConfig->allowedvplmnid());
    LocalIwfTranslatorRuleConfigObj.set_translatorrulename(pIwfTranslatorRuleConfig->translatorrulename());

    sql_IWFVplmnId_Create_Select_Query(&LocalIwfTranslatorRuleConfigObj,sStatement,iIndex);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = GENERIC_ERR_DB_ERROR;


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
                IwfVplmnIdConfig *pIwfVplmnIdConfig = pIwfTranslatorRuleConfig->mutable_vplmninfo(iIndex);

                if(!pRes->isNull("VPLMN_ID"))
                {
                    if(pRes->getString("VPLMN_ID") == pIwfVplmnIdConfig->allowedvplmnid().c_str())
                    {
                        delete pRes;
                        DLOG_ERROR("VPLMN-ID already configured for this Trans-Rule");
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return ADD_TRANSRULES_ERR_VPLMN_ID_ALREADY_PRESENT;
                    }
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
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFTranslatorRule_Add_Config_Reqs(IwfTranslatorRulesConfig *req,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::IwfTranslatorRulesConfig *pIwfTranslatorRulesConfig = req;
    ::IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pIwfTranslatorRulesConfig->ruleinfo_size() > 0) //if Rule Count is greater than 0
    {
        unsigned int trans_rule_size = pIwfTranslatorRulesConfig->ruleinfo_size();
        for (unsigned int iIndex = 0 ; iIndex < trans_rule_size ; iIndex++)
        {
            pIwfTranslatorRuleConfig = pIwfTranslatorRulesConfig->mutable_ruleinfo(iIndex);
            sql_IWFTranslatorRule_Create_Check_Modifcation_Query(pIwfTranslatorRuleConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_TRANSRULES_ERR_DB_ERROR;

                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                //NOTE: Translator Rule Not Present, Continue with add operation
            }
            else // MOD
            {
                delete pRes;
                DLOG_ERROR("Record Already Present");
                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,ADD_TRANSRULES_ERR_TRANS_RULE_ALREADY_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_TRANSRULES_ERR_TRANS_RULE_ALREADY_PRESENT;
            }
            delete pRes;

            if(pIwfTranslatorRuleConfig->has_translatortype())
            {
                ::IwfTranslatorType *pIwfTranslatorType = pIwfTranslatorRuleConfig->mutable_translatortype();
                if(pIwfTranslatorType->has_translatortypename())
                {
                    string trans_type = pIwfTranslatorType->translatortypename().c_str();
                    sql_IWFTranslatorType_Create_Check_Modifcation_Query(pIwfTranslatorType,sStatement);

                    pRes = NULL;
                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                    {
                        if(pRes != NULL)
                        {
                            delete pRes;
                        }

                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == DRE_DB_FAIL)
                            iReturn = ADD_TRANSRULES_ERR_DB_ERROR;

                        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }

                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                    if(pRes->rowsCount() == 0) // ADD
                    {
                        //NOTE: Translator Rule Not Present, Continue with add operation
                        delete pRes;
                        DLOG_ERROR("Record Not Present");
                        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,ADD_TRANSRULES_ERR_TRANSLATORTYPE_NOT_PRESENT);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return ADD_TRANSRULES_ERR_TRANSLATORTYPE_NOT_PRESENT;
                    }
                    delete pRes;

                    if((!strcmp(trans_type.c_str(), "SS7") || !strcmp(trans_type.c_str(), "DIAMETER")) &&
                            pIwfTranslatorRuleConfig->has_destinationname())
                    {
                        if(!strcmp(trans_type.c_str(), "SS7"))
                        {
                            IwfLocalHostsConfig plocalIwfLocalHostsConfig;
                            IWFCfgResp localresp;
                            if(mysql_IWFLocalConfig_Get_Config_Reqs(&plocalIwfLocalHostsConfig,&localresp) == IWF_DB_SUCCESS)
                            {
                                if(localresp.has_localhostinfo())
                                {
                                    IwfLocalHostsConfig* plocalhostsconfig = localresp.mutable_localhostinfo();
                                    IwfLocalHostConfig* localhostinfo = plocalhostsconfig->mutable_localhostinfo();
                                    if(localhostinfo->has_selectcriteria())
                                    {
                                        int selectcriteria = localhostinfo->selectcriteria();
                                        DLOG_DEBUG("selectcriteria = %d",selectcriteria);
                                        if((selectcriteria == MCC_MNC ||
                                                    selectcriteria == MCC_MNC_AND_APP_ID ||
                                                    selectcriteria == GTT_AND_MCC_MNC ||
                                                    selectcriteria == SK_AND_MCC_MNC) &&
                                                !pIwfTranslatorRuleConfig->has_mcc() &&
                                                !pIwfTranslatorRuleConfig->has_mnc())
                                        {
                                            //NOTE: check for MCC and MNC as mandatory
                                            iReturn = ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM_MCC_MNC_FOR_SS7;
                                            mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                            DLOG_DEBUG("iReturn = %d",iReturn);
                                            DLOG_NONE(" < %s ",__FUNCTION__);
                                            return iReturn;
                                        }

                                        if(pIwfTranslatorRuleConfig->has_translatorinfo())
                                        {
                                            IwfTranslatorConfig* localTranslatorConfig = pIwfTranslatorRuleConfig->mutable_translatorinfo();
                                            if(localTranslatorConfig->has_translatorname())
                                            {
                                                if(!strcmp(localTranslatorConfig->translatorname().c_str(), "CAP-Ro") ||
                                                        !strcmp(localTranslatorConfig->translatorname().c_str(), "CAP-Ro-TSL"))
                                                {
                                                    if((selectcriteria == SK_AND_MCC_MNC ||
                                                                selectcriteria == SK ||
                                                                selectcriteria == GTT_AND_SK) &&
                                                            !pIwfTranslatorRuleConfig->has_servicekey())
                                                    {
                                                        //NOTE: check for service key
                                                        iReturn = ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM_SERVICE_KEY_FOR_SS7;
                                                        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                                        DLOG_DEBUG("iReturn = %d",iReturn);
                                                        DLOG_NONE(" < %s ",__FUNCTION__);
                                                        return iReturn;
                                                    }

                                                    if((selectcriteria == IMSI_PREFIX_AND_SK) &&
                                                            (!pIwfTranslatorRuleConfig->has_imsiprefix() ||
                                                            !pIwfTranslatorRuleConfig->has_servicekey()))
                                                    {
                                                        //NOTE: check for ImsiPrefix and ServiceKey
                                                        iReturn = ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM_IMSIPREFIX_OR_SERVICEKEY_FOR_SS7;
                                                        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                                        DLOG_DEBUG("iReturn = %d",iReturn);
                                                        DLOG_NONE(" < %s ",__FUNCTION__);
                                                        return iReturn;
                                                    }

                                                    if((selectcriteria == IMSI_PREFIX_AND_SK) &&
                                                            !strcmp(localTranslatorConfig->translatorname().c_str(), "CAP-Ro-TSL") &&
                                                            !pIwfTranslatorRuleConfig->has_proactionrulename())
                                                    {
                                                        //NOTE: check for ProtocolActionRule
                                                        iReturn = ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM_PROACTIONRULE_FOR_SS7;
                                                        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
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

                            ::RealmConfig pRealmConfig;
                            pRealmConfig.set_realmname(pIwfTranslatorRuleConfig->destinationname().c_str());

                            sql_Realm_Create_Check_Modifcation_Query(&pRealmConfig,sStatement);
                            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                            {
                                if(pRes != NULL)
                                {
                                    delete pRes;
                                }

                                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                if(iReturn == DRE_DB_FAIL)
                                    iReturn = ADD_TRANSRULES_ERR_DB_ERROR;

                                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                DLOG_DEBUG("iReturn = %d",iReturn);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return iReturn;
                            }

                            memset(sStatement,0,MAX_STATEMENT_SIZE);

                            if(pRes->rowsCount() == 0) // ADD
                            {
                                //NOTE: Destination(RealmName) Not Present in REALM_TB
                                delete pRes;
                                DLOG_ERROR("Record Not Present");
                                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,ADD_TRANSRULES_ERR_DESTINATION_NOT_PRESENT);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return ADD_TRANSRULES_ERR_DESTINATION_NOT_PRESENT;
                            }
                            delete pRes;
                            pRes = NULL;
                            if(pIwfTranslatorRuleConfig->has_destinationname() && pIwfTranslatorRuleConfig->has_destinationhost())
                            {
                                PeerConfig lPeerConfig;
                                lPeerConfig.set_peerhostname(pIwfTranslatorRuleConfig->destinationhost().c_str());
                                lPeerConfig.set_realm(pIwfTranslatorRuleConfig->destinationname().c_str());

                                PeerTPBQuery lPeerTPBQuery;
                                lPeerTPBQuery.sql_Peer_Create_Check_Modifcation_Query(&lPeerConfig,sStatement);

                                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                                {
                                    if(pRes != NULL)
                                    {
                                        delete pRes;
                                    }

                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = ADD_TRANSRULES_ERR_DB_ERROR;

                                    mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return iReturn;
                                }

                                memset(sStatement,0,MAX_STATEMENT_SIZE);

                                if(pRes->rowsCount() == 0) // ADD
                                {
                                    //NOTE: Destination Not Present in IWF_SIGTRAN_DESTINATION_TB
                                    delete pRes;
                                    DLOG_ERROR("Record Not Present");
                                    mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,ADD_TRANSRULES_ERR_DESTINATION_HOST_NOT_PRESENT);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return ADD_TRANSRULES_ERR_DESTINATION_HOST_NOT_PRESENT;
                                }
                                delete pRes;
                                pRes = NULL;
                            }
                            if(pIwfTranslatorRuleConfig->has_alternatehost() && pIwfTranslatorRuleConfig->has_alternaterealm())
                            {
                                PeerConfig lPeerConfig;
                                lPeerConfig.set_peerhostname(pIwfTranslatorRuleConfig->alternatehost().c_str());
                                lPeerConfig.set_realm(pIwfTranslatorRuleConfig->alternaterealm().c_str());

                                PeerTPBQuery lPeerTPBQuery;
                                lPeerTPBQuery.sql_Peer_Create_Check_Modifcation_Query(&lPeerConfig,sStatement);

                                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                                {
                                    if(pRes != NULL)
                                    {
                                        delete pRes;
                                    }

                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = ADD_TRANSRULES_ERR_DB_ERROR;

                                    mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return iReturn;
                                }

                                memset(sStatement,0,MAX_STATEMENT_SIZE);

                                if(pRes->rowsCount() == 0)
                                {
                                    //NOTE: Alternate Destination Not Present in IWF_SIGTRAN_DESTINATION_TB
                                    delete pRes;
                                    DLOG_ERROR("Record Not Present");
                                    mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,ADD_TRANSRULES_ERR_ALTERNATE_HOST_NOT_PRESENT);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return ADD_TRANSRULES_ERR_ALTERNATE_HOST_NOT_PRESENT;
                                }
                                delete pRes;
                                pRes = NULL;
                            }
                        }
                        else // If Trans-Type is DIAMETER
                        {
                            ::IwfSigtranDestinationConfig pIwfSigtranDestinationConfig;
                            pIwfSigtranDestinationConfig.set_destinationname(pIwfTranslatorRuleConfig->destinationname().c_str());

                            sql_IWFSigtranDestination_Create_Check_Modifcation_Query(&pIwfSigtranDestinationConfig,sStatement);

                            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                            {
                                if(pRes != NULL)
                                {
                                    delete pRes;
                                }

                                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                if(iReturn == DRE_DB_FAIL)
                                    iReturn = ADD_TRANSRULES_ERR_DB_ERROR;

                                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                DLOG_DEBUG("iReturn = %d",iReturn);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return iReturn;
                            }

                            memset(sStatement,0,MAX_STATEMENT_SIZE);

                            if(pRes->rowsCount() == 0) // ADD
                            {
                                //NOTE: Destination Not Present in IWF_SIGTRAN_DESTINATION_TB
                                delete pRes;
                                DLOG_ERROR("Record Not Present");
                                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,ADD_TRANSRULES_ERR_DESTINATION_NOT_PRESENT);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return ADD_TRANSRULES_ERR_DESTINATION_NOT_PRESENT;
                            }
                            delete pRes;
                            pRes = NULL;
                            //NOTE: Validate Destination is part of RemoteRoute
                            IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfig;
                            IwfSigtranDestinationConfig *pIwfSigtranDestinationConfigReq = LocalIwfSigtranRemoteRouteConfig.mutable_destinationinfo();
                            pIwfSigtranDestinationConfigReq->set_destinationname(pIwfTranslatorRuleConfig->destinationname().c_str());
                            sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfig,sStatement);
                            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                            {    
                                if(pRes != NULL)    
                                {    
                                    delete pRes;
                                }    
                                DLOG_ERROR("Query Execution Failed %s",sStatement);

                                if(iReturn == IWF_DB_FAIL)
                                    iReturn = ADD_TRANSRULES_ERR_DB_ERROR;


                                DLOG_DEBUG("iReturn = %d",iReturn);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return iReturn;
                            }    


                            memset(sStatement,0,MAX_STATEMENT_SIZE);

                            if(pRes->rowsCount() <= 0) // ADD
                            {
                                delete pRes;
                                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,
                                        ADD_TRANSRULES_ERR_DEST_NOT_PART_OF_REMOTE_ROUTE);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return ADD_TRANSRULES_ERR_DEST_NOT_PART_OF_REMOTE_ROUTE;
                            }
                            delete pRes;
                            pRes = NULL;

                            if(pIwfTranslatorRuleConfig->has_alternaterealm())
                            {
                                ::IwfSigtranDestinationConfig pIwfSigtranDestinationConfig;
                                pIwfSigtranDestinationConfig.set_destinationname(pIwfTranslatorRuleConfig->alternaterealm().c_str());

                                sql_IWFSigtranDestination_Create_Check_Modifcation_Query(&pIwfSigtranDestinationConfig,sStatement);

                                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                                {
                                    if(pRes != NULL)
                                    {
                                        delete pRes;
                                    }

                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = ADD_TRANSRULES_ERR_DB_ERROR;

                                    mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return iReturn;
                                }

                                memset(sStatement,0,MAX_STATEMENT_SIZE);

                                if(pRes->rowsCount() == 0) // ADD
                                {
                                    //NOTE: Destination Not Present in IWF_SIGTRAN_DESTINATION_TB
                                    delete pRes;
                                    DLOG_ERROR("Record Not Present");
                                    mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,ADD_TRANSRULES_ERR_ALT_DESTINATION_NOT_PRESENT);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return ADD_TRANSRULES_ERR_ALT_DESTINATION_NOT_PRESENT;
                                }
                                delete pRes;
                                pRes = NULL;
                                //NOTE: Validate Destination is part of RemoteRoute
                                IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfig;
                                IwfSigtranDestinationConfig *pIwfSigtranDestinationConfigReq = LocalIwfSigtranRemoteRouteConfig.mutable_destinationinfo();
                                pIwfSigtranDestinationConfigReq->set_destinationname(pIwfTranslatorRuleConfig->alternaterealm().c_str());
                                sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfig,sStatement);
                                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                {    
                                    if(pRes != NULL)    
                                    {    
                                        delete pRes;
                                    }    
                                    DLOG_ERROR("Query Execution Failed %s",sStatement);

                                    if(iReturn == IWF_DB_FAIL)
                                        iReturn = ADD_TRANSRULES_ERR_DB_ERROR;


                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return iReturn;
                                }    


                                memset(sStatement,0,MAX_STATEMENT_SIZE);

                                if(pRes->rowsCount() <= 0) // ADD
                                {
                                    delete pRes;
                                    mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,
                                            ADD_TRANSRULES_ERR_ALT_DEST_NOT_PART_OF_REMOTE_ROUTE);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return ADD_TRANSRULES_ERR_ALT_DEST_NOT_PART_OF_REMOTE_ROUTE;
                                }
                                if(pRes != NULL)
                                {
                                    delete pRes;
                                    pRes = NULL;
                                }
                            }
                        }
                    }
                    else if(!strcmp(trans_type.c_str(), "HTTP"))
                    {
                        //NOTE: Not yet supported
                    }
                    else
                    {
                        iReturn = ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
                        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }

                    if((iReturn = mysql_IWFTranslatorRule_Add_Validation(pIwfTranslatorRuleConfig,resp)) != IWF_DB_SUCCESS)
                    {
                        if(iReturn == IWF_DB_FAIL)
                            iReturn = ADD_TRANSRULES_ERR_DB_ERROR;

                        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }

                    sql_IWFTranslatorRule_Create_Add_Query(pIwfTranslatorRuleConfig,sStatement);

                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);
                        DLOG_NONE(" < %s ",__FUNCTION__);

                        if(iReturn == DRE_DB_FAIL)
                            iReturn = ADD_TRANSRULES_ERR_DB_ERROR;

                        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                    int iVplmnIdCount = pIwfTranslatorRuleConfig->vplmninfo_size();
                    for(int j=0;j<iVplmnIdCount;j++)
                    {
                        pRes = NULL;
                        if((iReturn = mysql_IWFVplmnId_Validation(pIwfTranslatorRuleConfig,resp,j)) != IWF_DB_SUCCESS)
                        {
                            if(iReturn == IWF_DB_FAIL)
                                iReturn = ADD_TRANSRULES_ERR_DB_ERROR;
                            else if(iReturn == ADD_TRANSRULES_ERR_DB_ERROR)
                                iReturn = ADD_TRANSRULES_ERR_DB_ERROR;
                            else if(iReturn == ADD_TRANSRULES_ERR_VPLMN_ID_ALREADY_PRESENT)
                                iReturn = ADD_TRANSRULES_ERR_VPLMN_ID_ALREADY_PRESENT;

                            mysql_set_error_for_IWFVplmnId_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn,j);
                            DLOG_DEBUG("iReturn = %d",iReturn);
                            DLOG_NONE(" < %s ",__FUNCTION__);
                            return iReturn;
                        }

                        sql_IWFVplmnId_Create_Check_Modifcation_Query(pIwfTranslatorRuleConfig,sStatement,j);
                        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                        {
                            if(pRes != NULL)
                            {
                                delete pRes;
                            }
                            DLOG_ERROR("Query Execution Failed %s",sStatement);

                            if(iReturn == IWF_DB_FAIL)
                                iReturn = ADD_TRANSRULES_ERR_DB_ERROR;

                            mysql_set_error_for_IWFVplmnId_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn,j);

                            DLOG_DEBUG("iReturn = %d",iReturn);
                            DLOG_NONE(" < %s ",__FUNCTION__);
                            return iReturn;
                        }

                        memset(sStatement,0,MAX_STATEMENT_SIZE);

                        if(pRes->rowsCount() == 0) // ADD
                        {
                            sql_IWFVplmnId_Create_Add_Query(pIwfTranslatorRuleConfig,sStatement,j);
                        }
                        else // MOD
                        {
                            delete pRes;
                            DLOG_ERROR("Record Already Present:ADD_TRANSRULES_ERR_VPLMN_ID_ALREADY_PRESENT");
                            mysql_set_error_for_IWFVplmnId_Config_Reqs(pIwfTranslatorRuleConfig,resp,ADD_TRANSRULES_ERR_VPLMN_ID_ALREADY_PRESENT,j);
                            DLOG_NONE(" < %s ",__FUNCTION__);
                            return ADD_TRANSRULES_ERR_VPLMN_ID_ALREADY_PRESENT;
                        }

                        delete pRes;
                        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                        {
                            DLOG_ERROR("Query Execution Failed %s",sStatement);
                            if(iReturn == IWF_DB_FAIL)
                                iReturn = ADD_TRANSRULES_ERR_DB_ERROR;

                            mysql_set_error_for_IWFVplmnId_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn,j);
                            DLOG_DEBUG("iReturn = %d",iReturn);
                            DLOG_NONE(" < %s ",__FUNCTION__);
                            return iReturn;
                        }
                    }
                }
                else
                {
                    iReturn = ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
                    mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                    DLOG_DEBUG("iReturn = %d",iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
            }
            else
            {
                iReturn = ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
                mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
    }
    else // No rules to add
    {
        iReturn = ADD_TRANSRULES_ERR_DATA_NOT_PRESENT;
        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(pIwfTranslatorRuleConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFAllTranslatorData_Get_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    DbStatus_e iReturn = IWF_DB_FAIL;

    iReturn = mysql_IWFS6aMAP_Get_Config_Reqs(req,resp);
    iReturn = mysql_IWFMAPS6a_Get_Config_Reqs(req,resp);
    iReturn = mysql_IWFCapRo_Get_Config_Reqs(req,resp);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}


DbStatus_e CMgrIwfDbInterface::mysql_IWFTranslatorRules_Get_Config_Reqs(IwfTranslatorRulesConfig *pIwfTranslatorRulesConfig, IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);

    return Fill_IWFTranslatorRules_protobuff(pIwfTranslatorRulesConfig, resp);
}

#if 0
DbStatus_e CMgrIwfDbInterface::mysql_IWFTranslatorRule_Get_Config_Reqs(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig, IWFCfgResp *resp)
{
    return Fill_IWFTranslatorRule_protobuff(&LocalIwfTranslatorRuleConfigObj, resp);
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFTranslatorRule_Get_Config_Reqs(IwfTranslatorRulesConfig *pIwfTranslatorRulesConfig, IWFCfgResp *resp)
{
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;

    if((iReturn = Fill_IWFTranslatorRule_protobuff(&LocalIwfTranslatorRuleConfigObj, resp)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_TRANSRULES_ERR_DB_ERROR;
        mysql_set_error_for_IWFTranslatorRule_Config_Reqs(&LocalIwfTranslatorRuleConfigObj,resp,iReturn);
    }

    IwfTranslatorRulesConfig *pLocalIwfTranslatorRulesConfig = resp->mutable_translatorrulesinfo();
    IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig = pLocalIwfTranslatorRulesConfig->add_ruleinfo();

    pIwfTranslatorRuleConfig->CopyFrom(LocalIwfTranslatorRuleConfigObj);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}
#endif
#if 0
DbStatus_e CMgrIwfDbInterface::mysql_iwf_IWFTranslatorType_Set_Config_Reqs(IwfTranslatorType *pIwfTranslatorType,IWFCfgResp *resp)
{
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    IwfTranslatorType IwfTranslatorTypeObj;

    if((iReturn = Fill_IWFTranslatorType_protobuff(&IwfTranslatorTypeObj, resp)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_TRANSRULES_ERR_DB_ERROR;
        mysql_set_error_for_IWFTranslatorType_Config_Reqs(&IwfTranslatorTypeObj,resp,iReturn);
    }

    IwfTranslatorRulesConfig *pLocalIwfTranslatorRulesConfig = resp->mutable_translatorrulesinfo();
    IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig = pLocalIwfTranslatorRulesConfig->add_ruleinfo();

    pIwfTranslatorRuleConfig->CopyFrom(LocalIwfTranslatorRuleConfigObj);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_iwf_TranslatorsConfig_Mod_Config_Reqs(TranslatorsConfig *req,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

DbStatus_e CMgrIwfDbInterface::mysql_iwf_TranslatorsConfig_Del_Config_Reqs(TranslatorsConfig *req,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

DbStatus_e CMgrIwfDbInterface::mysql_iwf_TranslatorRules_Get_Config_Reqs(TranslatorRulesConfig *req,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

DbStatus_e CMgrIwfDbInterface::mysql_iwf_TranslatorRules_Set_Config_Reqs(TranslatorRulesConfig *req,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

DbStatus_e CMgrIwfDbInterface::mysql_iwf_TranslatorRules_Mod_Config_Reqs(TranslatorRulesConfig *req,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

DbStatus_e CMgrIwfDbInterface::mysql_iwf_TranslatorRules_Del_Config_Reqs(TranslatorRulesConfig *req,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

DbStatus_e CMgrIwfDbInterface::mysql_iwf_TranslationDataConfig_Get_Config_Reqs(TranslationDataConfig *req,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

DbStatus_e CMgrIwfDbInterface::mysql_iwf_TranslationDataConfig_Set_Config_Reqs(TranslationDataConfig *req,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

DbStatus_e CMgrIwfDbInterface::mysql_iwf_TranslationDataConfig_Mod_Config_Reqs(TranslationDataConfig *req,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}

DbStatus_e CMgrIwfDbInterface::mysql_iwf_TranslationDataConfig_Del_Config_Reqs(TranslationDataConfig *req,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;
}
#endif
