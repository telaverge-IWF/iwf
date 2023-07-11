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
#include <CMgrDbInterface.h>

using namespace std;
extern std::map<int,std::string> errorMap;

void CMgrDbInterface::mysql_set_error_for_Dictionary_Config_Reqs(::Dictionary *pDictionary, DynDictionaryResponse *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    CLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}


DbStatus_e CMgrDbInterface::mysql_DictionaryConfig_Get_Config_Reqs(DynDictionaryRequest *pDynDictionaryConfig,DynDictionaryResponse *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::Dictionary localDictionary;

    DLOG_NONE(" > %s ",__FUNCTION__);

    sql_DictionaryConfig_Create_Select_Query(&localDictionary,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        if(iReturn == DRE_DB_FAIL)
            iReturn = GET_DICTID_ERR_DB_ERROR;

        mysql_set_error_for_Dictionary_Config_Reqs(&localDictionary,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if((iReturn = mysql_DictionaryConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
    {
        delete pRes;
        mysql_set_error_for_Dictionary_Config_Reqs(&localDictionary,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_DictionaryConfig_resultset_to_protoBuff(sql::ResultSet *pRes,DynDictionaryResponse *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG("%s: RowCount = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_DICTID_ERR_NO_DATA_PRESENT;
        }


        while(pRes->next())
        {
            ::Dictionary *pDictionary = resp->add_dictionaries();
            pDictionary->set_dictionaryname(pRes->getString("DICTIONARY_NAME"));
            pDictionary->set_interfacename(pRes->getString("INTERFACE_NAME"));
            pDictionary->set_releasenum(pRes->getString("RELEASE_NUMBER"));
            pDictionary->set_dictionaryid(pRes->getInt("DICTIONARY_ID"));
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






/* Dictionary-provisioning and Transformation-plugin
 */

void CMgrDbInterface::mysql_set_error_for_Dictionary_Config_Reqs(DictionaryConfig *pDictionaryConfig, DRECfgResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pDictionaryConfig->has_dictionaryname())
         err->add_variables(pDictionaryConfig->dictionaryname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_TransPlugin_Config_Reqs(TransformPluginConfig *pTransformPluginConfig, DRECfgResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pTransformPluginConfig->has_pluginname())
        err->add_variables(pTransformPluginConfig->pluginname().c_str());

    if(iReturn == MOD_TRANSFORM_PLUGIN_ERR_CONFIG_FILE_NOT_PRESENT ||
            iReturn == MOD_TRANSFORM_PLUGIN_RELOAD_ERR_PLUGIN_NOT_ENABLED)
    {
        if(pTransformPluginConfig->has_pluginconfigfile())
             err->add_variables(pTransformPluginConfig->pluginconfigfile().c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_TransPlugin_Config_Reqs(TransformPluginConfig *pTransformPluginConfig, DRECfgResp *resp, string dictName, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pTransformPluginConfig->has_pluginname())
        err->add_variables(pTransformPluginConfig->pluginname().c_str());

    if(iReturn == MOD_TRANSFORM_PLUGIN_LOAD_ERR_ASSOCIATED_DICTIONARY_NOT_ENABLED ||
            iReturn == MOD_TRANSFORM_PLUGIN_RELOAD_ERR_ASSOCIATED_DICTIONARY_NOT_ENABLED)
    {
        err->add_variables(dictName);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_Dictionary_Config_Reqs(DRECfgResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_TransPlugin_Config_Reqs(DRECfgResp *resp, DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_TransformPluginConfig_setDictionaryName_resultset_to_protoBuff(TransformPluginConfig *pTransformPluginConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        sql::ResultSet *pRes = NULL;
        DRECfgResp *resp = NULL;
        char sStatement[MAX_STATEMENT_SIZE] = {0};
        DbStatus_e iReturn =  DRE_DB_SUCCESS;


        DictionaryConfig localDictionaryConfig;
        sql_DictionaryConfig_Create_Select_Query(&localDictionaryConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_DICTID_ERR_DB_ERROR;

            mysql_set_error_for_Dictionary_Config_Reqs(&localDictionaryConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        bool statusDictId_1 = false;
        bool statusDictId_2 = false;
        while(pRes->next())
        {
            if(!pRes->isNull("DICTIONARY_ID"))
            {
                if(pRes->getUInt("DICTIONARY_ID") == pTransformPluginConfig->dictionaryid1())
                {
                    statusDictId_1 = true;
                    pTransformPluginConfig->set_dictionaryname1(pRes->getString("DICTIONARY_NAME"));
                }
                else if(pRes->getUInt("DICTIONARY_ID") == pTransformPluginConfig->dictionaryid2())
                {
                    statusDictId_2 = true;
                    pTransformPluginConfig->set_dictionaryname2(pRes->getString("DICTIONARY_NAME"));
                }
            }
            if(statusDictId_1 && statusDictId_2)
            {
                break;
            }
        }
        delete pRes;
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }
    return DRE_DB_SUCCESS;
    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_TransformPluginConfig_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG("%s: RowCount = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_TRANSFORM_PLUGIN_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            TransformPluginConfig *pTransformPluginConfig = resp->add_transformplugininfo();

            pTransformPluginConfig->set_pluginname(pRes->getString("PLUGIN_NAME"));
            pTransformPluginConfig->set_dictionaryid1(pRes->getInt("DICTIONARY_ID1"));
            pTransformPluginConfig->set_dictionaryid2(pRes->getInt("DICTIONARY_ID2"));
            pTransformPluginConfig->set_ispluginenabled(pRes->getInt("IS_ENABLED"));
            pTransformPluginConfig->set_pluginconfigfile(pRes->getString("CONFIG_FILE"));

            mysql_TransformPluginConfig_setDictionaryName_resultset_to_protoBuff(pTransformPluginConfig);
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

DbStatus_e CMgrDbInterface::mysql_DictionaryConfig_resultset_to_protoBuff(sql::ResultSet *pRes, DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG("%s: RowCount = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_DICTID_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            DictionaryConfig *pDictionaryConfig = resp->add_dictionaryinfo();

            pDictionaryConfig->set_dictionaryid(pRes->getInt("DICTIONARY_ID"));
            pDictionaryConfig->set_dictionaryname(pRes->getString("DICTIONARY_NAME"));
            pDictionaryConfig->set_interfacename(pRes->getString("INTERFACE_NAME"));
            pDictionaryConfig->set_releasenumber(pRes->getString("RELEASE_NUMBER"));
            pDictionaryConfig->set_applicationid(pRes->getInt("APP_ID"));
            pDictionaryConfig->set_apptype(pRes->getInt("APP_TYPE"));
            pDictionaryConfig->set_isdictenabled(pRes->getInt("IS_DICTIONARY_ENABLED"));
            pDictionaryConfig->set_isdefaultdict(pRes->getInt("IS_DEFAULT_DICTIONARY"));
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

DbStatus_e CMgrDbInterface::mysql_TransPlugin_Get_Config_Reqs(TransformPluginConfigReq *pTransformPluginConfigReq, DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount = pTransformPluginConfigReq->transformplugininfo_size();

    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG(" %s: DictionaryConfig Req Size = %d ",__FUNCTION__,iCount);

    if(iCount)
    {
        for(int iIndex=0; iIndex<iCount; iIndex++)
        {
            TransformPluginConfig *plocalTransformPluginConfig = pTransformPluginConfigReq->mutable_transformplugininfo(iIndex);

            sql_PluginConfig_Create_Select_Query(plocalTransformPluginConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_DICTID_ERR_DB_ERROR;

                mysql_set_error_for_TransPlugin_Config_Reqs(plocalTransformPluginConfig, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_TransformPluginConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
            {
                delete pRes;
                mysql_set_error_for_TransPlugin_Config_Reqs(plocalTransformPluginConfig, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            delete pRes;
        }
    }
    else
    {
        TransformPluginConfig localTransformPluginConfig;

        sql_PluginConfig_Create_Select_Query(&localTransformPluginConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_DICTID_ERR_DB_ERROR;

            mysql_set_error_for_TransPlugin_Config_Reqs(&localTransformPluginConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_TransformPluginConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;
            mysql_set_error_for_TransPlugin_Config_Reqs(&localTransformPluginConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Dictionary_Get_Config_Reqs(DictionaryConfigReq *pDictionaryConfigReq, DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount = pDictionaryConfigReq->dictionaryinfo_size();

    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG(" %s: DictionaryConfig Req Size = %d ",__FUNCTION__,iCount);

    if(iCount)
    {
        for(int iIndex=0; iIndex<iCount; iIndex++)
        {
            DictionaryConfig *localDictionaryConfig = pDictionaryConfigReq->mutable_dictionaryinfo(iIndex);

            sql_DictionaryConfig_Create_Select_Query(localDictionaryConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_DICTID_ERR_DB_ERROR;

                mysql_set_error_for_Dictionary_Config_Reqs(localDictionaryConfig, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_DictionaryConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
            {
                delete pRes;
                mysql_set_error_for_Dictionary_Config_Reqs(localDictionaryConfig, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            delete pRes;
        }
    }
    else
    {
        DictionaryConfig localDictionaryConfig;

        sql_DictionaryConfig_Create_Select_Query(&localDictionaryConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_DICTID_ERR_DB_ERROR;

            mysql_set_error_for_Dictionary_Config_Reqs(&localDictionaryConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_DictionaryConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;
            mysql_set_error_for_Dictionary_Config_Reqs(&localDictionaryConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_TransPlugin_SetStatus_Validation(TransformPluginConfig *pTransformPluginConfig, DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int dictId1 = 0;
    int dictId2 = 0;

    /* validation: Validate if Plugin name is present in Plugin_table
     * Input to query : Plugin Name
     */
    if(pTransformPluginConfig->has_pluginname())
    {
        TransformPluginConfig localTransformPluginConfig;
        localTransformPluginConfig.set_pluginname(pTransformPluginConfig->pluginname());

        sql_PluginConfig_Create_Check_Modifcation_Query(&localTransformPluginConfig, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_TRANSFORM_PLUGIN_ERR_DB_ERROR;

            mysql_set_error_for_TransPlugin_Config_Reqs(&localTransformPluginConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Record not not present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_TRANSFORM_PLUGIN_ERR_PLUGIN_NOT_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }

    {
        TransformPluginConfig localTransformPluginConfig;
        localTransformPluginConfig.set_pluginname(pTransformPluginConfig->pluginname());

        sql_PluginConfig_Create_Select_Query(&localTransformPluginConfig, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_TRANSFORM_PLUGIN_ERR_DB_ERROR;

            mysql_set_error_for_TransPlugin_Config_Reqs(&localTransformPluginConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("IS_ENABLED"))
                {
                    if(pRes->getInt("IS_ENABLED") == 1 && pTransformPluginConfig->ispluginenabled() == true)
                    {
                        delete pRes;
                        DLOG_ERROR("Transform Plugin is already Enabled");
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return MOD_TRANSFORM_PLUGIN_ERR_PLUGIN_ALREADY_ENABLED;
                    }
                    if(pRes->getInt("IS_ENABLED") == 0 && pTransformPluginConfig->ispluginenabled() == false)
                    {
                        delete pRes;
                        DLOG_ERROR("Transform Plugin is already Disabled");
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return MOD_TRANSFORM_PLUGIN_ERR_PLUGIN_ALREADY_DISABLED;
                    }
                }
                if(!pRes->isNull("DICTIONARY_ID1"))
                {
                    dictId1 = pRes->getInt("DICTIONARY_ID1");
                    DLOG_DEBUG("Fetched DictionaryId-1 : %d",dictId1);
                }
                if(!pRes->isNull("DICTIONARY_ID2"))
                {
                    dictId2 = pRes->getInt("DICTIONARY_ID2");
                    DLOG_DEBUG("Fetched DictionaryId-2 : %d",dictId2);
                }
                if(!pRes->isNull("CONFIG_FILE"))
                {
                    pTransformPluginConfig->set_pluginconfigfile(pRes->getString("CONFIG_FILE"));
                    DLOG_DEBUG("Fetched ConfigFile");
                }
            }
        }
        delete pRes;
        pRes = NULL;
    }

    /* Validation: Dictionary status should be enabled in order to enable
     * transform plugin.
     * If validation is successfull Set Dictionary names
     * (dictionary-1 and dictionary-2) in Request
     */
    if(pTransformPluginConfig->has_ispluginenabled())
    {
        if(dictId1)
        {
            DictionaryConfig localDictionaryConfig;
            localDictionaryConfig.set_dictionaryid(dictId1);

            sql_DictionaryConfig_Create_Select_Query(&localDictionaryConfig, sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_DICTID_ERR_DB_ERROR;

                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() > 0)
            {
                if(pRes->next())
                {
                    if(pTransformPluginConfig->ispluginenabled() == true)
                    {
                        if(!pRes->isNull("IS_DICTIONARY_ENABLED"))
                        {
                            if(pRes->getInt("IS_DICTIONARY_ENABLED") != true)
                            {
                                string dictName;
                                iReturn = MOD_TRANSFORM_PLUGIN_LOAD_ERR_ASSOCIATED_DICTIONARY_NOT_ENABLED;
                                if(!pRes->isNull("DICTIONARY_NAME"))
                                {
                                    dictName = pRes->getString("DICTIONARY_NAME");
                                }
                                delete pRes;
                                DLOG_ERROR("Dictionary-1 is not enabled");
                                mysql_set_error_for_TransPlugin_Config_Reqs(pTransformPluginConfig, resp, dictName, iReturn);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return iReturn;
                            }
                            else
                            {
                                if(!pRes->isNull("DICTIONARY_NAME"))
                                    pTransformPluginConfig->set_dictionaryname1(pRes->getString("DICTIONARY_NAME"));
                            }
                        }
                    }
                    else
                    {
                        if(!pRes->isNull("DICTIONARY_NAME"))
                            pTransformPluginConfig->set_dictionaryname1(pRes->getString("DICTIONARY_NAME"));
                    }
                }
            }
            delete pRes;
            pRes = NULL;
        }

        if(dictId2)
        {
            DictionaryConfig localDictionaryConfig;
            localDictionaryConfig.set_dictionaryid(dictId2);

            sql_DictionaryConfig_Create_Select_Query(&localDictionaryConfig, sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_DICTID_ERR_DB_ERROR;

                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() > 0)
            {
                if(pRes->next())
                {
                    if(pTransformPluginConfig->ispluginenabled() == true)
                    {
                        if(!pRes->isNull("IS_DICTIONARY_ENABLED"))
                        {
                            if(pRes->getInt("IS_DICTIONARY_ENABLED") != true)
                            {
                                string dictName;
                                iReturn = MOD_TRANSFORM_PLUGIN_LOAD_ERR_ASSOCIATED_DICTIONARY_NOT_ENABLED;
                                if(!pRes->isNull("DICTIONARY_NAME"))
                                {
                                    dictName = pRes->getString("DICTIONARY_NAME");
                                }
                                delete pRes;
                                DLOG_ERROR("Dictionary-2 is not enabled");
                                mysql_set_error_for_TransPlugin_Config_Reqs(pTransformPluginConfig, resp, dictName, iReturn);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return iReturn;
                            }
                            else
                            {
                                if(!pRes->isNull("DICTIONARY_NAME"))
                                    pTransformPluginConfig->set_dictionaryname2(pRes->getString("DICTIONARY_NAME"));
                            }
                        }
                    }
                    else
                    {
                        if(!pRes->isNull("DICTIONARY_NAME"))
                            pTransformPluginConfig->set_dictionaryname2(pRes->getString("DICTIONARY_NAME"));
                    }
                }
            }
            delete pRes;
            pRes = NULL;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_TransPlugin_SetStatus_Config_Reqs(TransformPluginConfigReq *pTransformPluginConfigReq, DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount = pTransformPluginConfigReq->transformplugininfo_size();

    DLOG_NONE(" > %s ",__FUNCTION__);

    for(int iIndex=0; iIndex<iCount; iIndex++)
    {
        TransformPluginConfig *pTransformPluginConfig = pTransformPluginConfigReq->mutable_transformplugininfo(iIndex);

        DLOG_DEBUG("Req %s",pTransformPluginConfig->DebugString().c_str());
        if((iReturn = mysql_TransPlugin_SetStatus_Validation(pTransformPluginConfig,resp)) != DRE_DB_SUCCESS)
        {
            if(iReturn == MOD_TRANSFORM_PLUGIN_LOAD_ERR_ASSOCIATED_DICTIONARY_NOT_ENABLED)
            {
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DRE_DB_FAIL;
            }
            else
            {
                DLOG_DEBUG(" %s:%d mysql_TransPlugin_SetStatus_Validation Failed \n",__FUNCTION__,__LINE__);
                mysql_set_error_for_TransPlugin_Config_Reqs(pTransformPluginConfig, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
        if(iReturn == DRE_DB_SUCCESS)
        {
            sql_PluginConfig_Create_Mod_Query(pTransformPluginConfig, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_TRANSFORM_PLUGIN_ERR_DB_ERROR;

                mysql_set_error_for_TransPlugin_Config_Reqs(pTransformPluginConfig, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_TransPlugin_Reload_Validation(TransformPluginConfig *pTransformPluginConfig, DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int dictId1 = 0;
    int dictId2 = 0;
    int pluginStatus;

    /* validation: Validate if Plugin name is present in Plugin_table
     * Input to query : Plugin Name
     */
    if(pTransformPluginConfig->has_pluginname())
    {
        TransformPluginConfig localTransformPluginConfig;
        localTransformPluginConfig.set_pluginname(pTransformPluginConfig->pluginname());

        sql_PluginConfig_Create_Check_Modifcation_Query(&localTransformPluginConfig, sStatement);
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
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Record  not present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_TRANSFORM_PLUGIN_RELOAD_ERR_PLUGIN_NOT_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }

    /* validation: Validate if Plugin File is present in Plugin_table
     * Input to query : Plugin Name, Plugin File
     */
    if(pTransformPluginConfig->has_pluginconfigfile())
    {
        TransformPluginConfig localTransformPluginConfig;
        localTransformPluginConfig.set_pluginconfigfile(pTransformPluginConfig->pluginconfigfile());
        localTransformPluginConfig.set_pluginname(pTransformPluginConfig->pluginname());

        sql_PluginConfig_Create_Select_Query(&localTransformPluginConfig, sStatement);
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
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Plugin file not present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_TRANSFORM_PLUGIN_ERR_CONFIG_FILE_NOT_PRESENT;
        }
        else
        {
            if(pRes->next())
            {
                if(!pRes->isNull("DICTIONARY_ID1"))
                {
                    dictId1 = pRes->getInt("DICTIONARY_ID1");
                    DLOG_DEBUG("Fetched DictionaryId-1 : %d",dictId1);
                }
                if(!pRes->isNull("DICTIONARY_ID2"))
                {
                    dictId2 = pRes->getInt("DICTIONARY_ID2");
                    DLOG_DEBUG("Fetched DictionaryId-1 : %d",dictId2);
                }
                if(!pRes->isNull("IS_ENABLED"))
                {
                    pluginStatus = pRes->getInt("IS_ENABLED");
                    DLOG_DEBUG("Fetched pluginStatus : %d",pluginStatus);
                    if (pluginStatus == 0)
                    {
                        delete pRes;
                        DLOG_ERROR("Plugin file not enabled");
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return MOD_TRANSFORM_PLUGIN_RELOAD_ERR_PLUGIN_NOT_ENABLED;
                    }

                }
            }
        }
        delete pRes;
        pRes = NULL;
    }

    // Set Plugin status in Request
    if(!pTransformPluginConfig->has_ispluginenabled())
        pTransformPluginConfig->set_ispluginenabled(pluginStatus);

    if(dictId1)
    {
        DictionaryConfig localDictionaryConfig;
        localDictionaryConfig.set_dictionaryid(dictId1);

        sql_DictionaryConfig_Create_Select_Query(&localDictionaryConfig, sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_DICTID_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("IS_DICTIONARY_ENABLED"))
                {
                    if(pRes->getInt("IS_DICTIONARY_ENABLED") != true)
                    {
                        string dictName;
                        if(!pRes->isNull("DICTIONARY_NAME"))
                        {
                            dictName = pRes->getString("DICTIONARY_NAME");
                        }
                        delete pRes;
                        DLOG_ERROR("Dictionary-1 %s is not enabled",dictName.c_str());
                        mysql_set_error_for_TransPlugin_Config_Reqs(pTransformPluginConfig, resp, dictName, MOD_TRANSFORM_PLUGIN_RELOAD_ERR_ASSOCIATED_DICTIONARY_NOT_ENABLED);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return MOD_TRANSFORM_PLUGIN_RELOAD_ERR_ASSOCIATED_DICTIONARY_NOT_ENABLED;
                    }
                }
                //Set Dictionary-1 in Request
                if(!pRes->isNull("DICTIONARY_NAME"))
                    pTransformPluginConfig->set_dictionaryname1(pRes->getString("DICTIONARY_NAME"));
            }
        }
        delete pRes;
        pRes = NULL;
    }

    if(dictId2)
    {
        DictionaryConfig localDictionaryConfig;
        localDictionaryConfig.set_dictionaryid(dictId2);

        sql_DictionaryConfig_Create_Select_Query(&localDictionaryConfig, sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_DICTID_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("IS_DICTIONARY_ENABLED"))
                {
                    if(pRes->getInt("IS_DICTIONARY_ENABLED") != true)
                    {
                        string dictName;
                        if(!pRes->isNull("DICTIONARY_NAME"))
                        {
                            dictName = pRes->getString("DICTIONARY_NAME");
                        }
                        delete pRes;
                        DLOG_ERROR("Dictionary-2 %s is not enabled",dictName.c_str());
                        mysql_set_error_for_TransPlugin_Config_Reqs(pTransformPluginConfig, resp, dictName, MOD_TRANSFORM_PLUGIN_RELOAD_ERR_ASSOCIATED_DICTIONARY_NOT_ENABLED);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return MOD_TRANSFORM_PLUGIN_RELOAD_ERR_ASSOCIATED_DICTIONARY_NOT_ENABLED;
                    }
                }
                //Set Dictionary-1 in Request
                if(!pRes->isNull("DICTIONARY_NAME"))
                    pTransformPluginConfig->set_dictionaryname2(pRes->getString("DICTIONARY_NAME"));
            }
        }
        delete pRes;
        pRes = NULL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_TransPlugin_Reload_Config_Reqs(TransformPluginConfigReq *pTransformPluginConfigReq, DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount = pTransformPluginConfigReq->transformplugininfo_size();

    DLOG_NONE(" > %s ",__FUNCTION__);

    for(int iIndex=0; iIndex<iCount; iIndex++)
    {
        TransformPluginConfig *pTransformPluginConfig = pTransformPluginConfigReq->mutable_transformplugininfo(iIndex);

        if((iReturn = mysql_TransPlugin_Reload_Validation(pTransformPluginConfig, resp)) != DRE_DB_SUCCESS)
        {
            DLOG_DEBUG(" %s:%d mysql_TransPlugin_Reload_Validation Failed \n",__FUNCTION__,__LINE__);
            mysql_set_error_for_TransPlugin_Config_Reqs(pTransformPluginConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        if(iReturn == DRE_DB_SUCCESS)
        {
            sql_PluginConfig_Create_Mod_Query(pTransformPluginConfig, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_TRANSFORM_PLUGIN_ERR_DB_ERROR;

                mysql_set_error_for_TransPlugin_Config_Reqs(pTransformPluginConfig, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);

    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Dictionary_SetStatus_Validation(DictionaryConfig *pDictionaryConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int DictId = 0;
    //string interfaceName = "";
    //string releaseNum = "";
    //int appType = 0;
    //int appId = 0;
    //bool isDefaultDict;


    /* validation: Validate if Dictionary name is present in Dict_table
     * Input to query : Dict Name
     */
    DLOG_DEBUG(" %s ",pDictionaryConfig->dictionaryname().c_str());
    if(pDictionaryConfig->has_dictionaryname())
    {
        DictionaryConfig localDictionaryConfig;
        localDictionaryConfig.set_dictionaryname(pDictionaryConfig->dictionaryname());

        sql_DictionaryConfig_Create_Check_Modifcation_Query(&localDictionaryConfig, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_DICTID_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Record not present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_DICTID_ERR_DICTIONARY_NOT_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }

    /* Validation:
     * 1 - validation for default dict, Disabling of default dictionary is not
     * allowed
     * 2 - error if already enabled
     * 3 - error if already disable
     * Input to Query: Dict_Name
     */
    {
        DictionaryConfig localDictionaryConfig;
        localDictionaryConfig.set_dictionaryname(pDictionaryConfig->dictionaryname());

        sql_DictionaryConfig_Create_Select_Query(&localDictionaryConfig, sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_DICTID_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("IS_DEFAULT_DICTIONARY"))
                {
                    // Default dictionary cant be disabled
                    if(pDictionaryConfig->has_isdictenabled() && pDictionaryConfig->isdictenabled() == false)
                    {
                        if((pRes->getInt("IS_DEFAULT_DICTIONARY") == 1))
                        {
                            delete pRes;
                            DLOG_ERROR("Default dictionary: Can't be disabled");
                            DLOG_NONE(" < %s ",__FUNCTION__);
                            return MOD_DICTID_ERR_ITS_DEFAULT_DICTIONARY;
                        }
                    }
                }
                if(!pRes->isNull("IS_DICTIONARY_ENABLED"))
                {
                    if((pRes->getInt("IS_DICTIONARY_ENABLED") == 1) && (pDictionaryConfig->isdictenabled() == true))
                    {
                        delete pRes;
                        DLOG_ERROR("Dictionary is Already Enabled");
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return MOD_DICTID_ERR_DICTIONARY_IS_ALREADY_ENABLED;
                    }
                    if((pRes->getInt("IS_DICTIONARY_ENABLED") == 0) && (pDictionaryConfig->isdictenabled() == false))
                    {
                        delete pRes;
                        DLOG_ERROR("Dictionary is Already Disabled");
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return MOD_DICTID_ERR_DICTIONARY_IS_ALREADY_DISABLED;
                    }
                }
                if(!pRes->isNull("DICTIONARY_ID"))
                {
                    DictId = pRes->getInt("DICTIONARY_ID");
                }
                if(!pRes->isNull("APP_TYPE"))
                {
                    pDictionaryConfig->set_apptype(pRes->getInt("APP_TYPE"));
                }
                if(!pRes->isNull("APP_ID"))
                {
                    pDictionaryConfig->set_applicationid(pRes->getInt("APP_ID"));
                }
            }
        }
        delete pRes;
        pRes = NULL;
    }

    /* Get missing parameters in Request from DB
     */

    /* Scenario: Disable dictionary command by user.
     * Validation: if dictionary is associated with any peer then it cant
     * be disabled.
     */
    if(pDictionaryConfig->has_isdictenabled() && pDictionaryConfig->isdictenabled() == false)
    {
        DictionaryConfig localDictionaryConfig;
        localDictionaryConfig.set_dictionaryid(DictId);

        sql_PeerDictionaryMap_Create_Select_Query(&localDictionaryConfig, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_DICTID_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            DLOG_ERROR("Dictionary Associated with Peer");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_DICTID_ERR_ITS_ASSOCIATED_WITH_ONE_OR_MORE_PEER;
        }
        delete pRes;
        pRes = NULL;
    }

    /* Scenario: Disable dictionary command by User.
     * Validation: Disabling of dictionary should not be allowed if it is
     * associated with any Transform-Plugin and trans-plugin is in
     * enabled state.
     */
    if(pDictionaryConfig->has_isdictenabled() && pDictionaryConfig->isdictenabled() == false)
    {
        TransformPluginConfig localTransformPluginConfig;
        localTransformPluginConfig.set_dictionaryid1(DictId);

        sql_PluginConfig_Create_Select_Query(&localTransformPluginConfig, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_DICTID_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if((!pRes->isNull("IS_ENABLED")) && (pRes->getInt("IS_ENABLED") != false))
                {
                    delete pRes;
                    DLOG_ERROR("Dictionary Associated with Trans-Plugin and plugin is enabled");
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_DICTID_ERR_DICTIONARY_ASSOCIATED_WITH_ENABLED_TRANSFORM_PLUGIN;
                }
            }
        }
        delete pRes;
        pRes = NULL;

        localTransformPluginConfig.clear_dictionaryid1();
        localTransformPluginConfig.set_dictionaryid2(DictId);

        sql_PluginConfig_Create_Select_Query(&localTransformPluginConfig, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_DICTID_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if((!pRes->isNull("IS_ENABLED")) && (pRes->getInt("IS_ENABLED") != false))
                {
                    delete pRes;
                    DLOG_ERROR("Dictionary Associated with Trans-Plugin and plugin is enabled");
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_DICTID_ERR_DICTIONARY_ASSOCIATED_WITH_ENABLED_TRANSFORM_PLUGIN;
                }
            }
        }
        delete pRes;
    }

    //Set remaining parameteres in Request

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Dictionary_SetStatus_Config_Reqs(DictionaryConfigReq *pDictionaryConfigReq, DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount = pDictionaryConfigReq->dictionaryinfo_size();

    DLOG_NONE(" > %s ",__FUNCTION__);

    for(int iIndex=0; iIndex<iCount; iIndex++)
    {
        DictionaryConfig *plocalDictionaryConfig = pDictionaryConfigReq->mutable_dictionaryinfo(iIndex);

        DLOG_DEBUG(" %s ",plocalDictionaryConfig->dictionaryname().c_str());
        if((iReturn = mysql_Dictionary_SetStatus_Validation(plocalDictionaryConfig)) != DRE_DB_SUCCESS)
        {
            DLOG_DEBUG(" %s:%d mysql_Dictionary_SetStatus_Validation Failed \n",__FUNCTION__,__LINE__);
            mysql_set_error_for_Dictionary_Config_Reqs(plocalDictionaryConfig, resp, iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        if(iReturn == DRE_DB_SUCCESS)
        {
            sql_DictionaryConfig_Create_Mod_Query(plocalDictionaryConfig, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_DICTID_ERR_DB_ERROR;

                mysql_set_error_for_Dictionary_Config_Reqs(plocalDictionaryConfig, resp, iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}
