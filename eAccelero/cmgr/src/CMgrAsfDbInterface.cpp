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


#include <CMgrDbInterface.h>

using namespace std;
extern std::map<int,std::string> errorMap;

void CMgrDbInterface::mysql_set_error_for_Asf_Config_Reqs(::ASGroupCfg *pASGroupConf, ASFConfigResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pASGroupConf->has_appgroup())
        err->add_variables(pASGroupConf->appgroup().c_str());

    ::LBAlgorithm* localLBAlogrithm = pASGroupConf->mutable_lbalgo();
    if(localLBAlogrithm->has_lbmethod())
        err->add_variables(localLBAlogrithm->lbmethod().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_AsfRespTime_Config_Reqs(::ASFConfiguration *pASFConf, ASFConfigResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_Asf_Get_Config_Reqs(ASFConfigReq *req, ASFConfigResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ASFConfiguration *pASFConfig;
    pASFConfig = req->mutable_asfinfo();
    sql_ASFConfig_Create_Check_Modifcation_Query(pASFConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {   
        if(pRes != NULL)    
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn =  GET_ASFRESPTIME_ERR_DB_ERROR;

        mysql_set_error_for_AsfRespTime_Config_Reqs(pASFConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);   
        return iReturn;
    }   

    if((iReturn = mysql_Asf_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
    {   
        delete pRes;
        mysql_set_error_for_AsfRespTime_Config_Reqs(pASFConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }   

    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}


DbStatus_e CMgrDbInterface::mysql_AsfGroup_Get_Config_Reqs(ASFConfigReq *req, ASFConfigResp *resp)
{
    ::ASGroupCfg *pASFGroupConfig;
    ::ASGroupCfg localASGroupConfig;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};

    int iCount = req->asgroups_size();

    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG(" %s: loggerconfig_size = %d ",__FUNCTION__,iCount); 
    
    for(int i=0;i<iCount;i++)
    {
        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        pASFGroupConfig = req->mutable_asgroups(i);

        sql_ASFLbAlgo_Create_Select_Query(pASFGroupConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_ASFCONFIG_ERR_DB_ERROR;

            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,iReturn);

            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

        if((iReturn = mysql_AsfGroup_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;

            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        delete pRes;
    }

    if(iCount == 0)
    {
        pASFGroupConfig = &localASGroupConfig;

        sql_ASFLbAlgo_Create_Select_Query(pASFGroupConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_ASFCONFIG_ERR_DB_ERROR;

            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

        if((iReturn = mysql_AsfGroup_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;
            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        delete pRes;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}




DbStatus_e CMgrDbInterface::mysql_AsfGroup_Del_Config_Reqs(ASFConfigReq *req, ASFConfigResp *resp)
{

    DLOG_NONE(" < %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    ::ASGroupCfg *pASFGroupConfig;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;


    int iCount = req->asgroups_size();
    DLOG_DEBUG(" %s: tracedata_size = %d ",__FUNCTION__,iCount); 

    for(int i=0;i<iCount;i++)
    {   
        pASFGroupConfig = req->mutable_asgroups(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_ASF_Create_Check_Modifcation_Query(pASFGroupConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {   

            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_ASFCONFIG_ERR_DB_ERROR;

            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record not Present");
            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,DEL_ASFCONFIG_ERR_FILTER_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_ASFCONFIG_ERR_FILTER_NOT_PRESENT;
        }
        else // MOD
        {
            sql_ASF_Create_Delete_Query(pASFGroupConfig,sStatement);
        }


        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_ASFCONFIG_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,iReturn);
            return iReturn;
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_Asf_resultset_to_protoBuff(sql::ResultSet *pRes,ASFConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());   
        if(pRes->rowsCount() == 0)
        {   
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return GET_ASFRESPTIME_ERR_NO_DATA_PRESENT;
        }   
        while(pRes->next())
        {
            ::ASFConfiguration* AsfConfig = resp->mutable_asfinfo();
            AsfConfig->set_appresponsetimeout(pRes->getInt64("APP_RESPONSE_TIMEOUT"));

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


DbStatus_e CMgrDbInterface::mysql_AsfGroup_resultset_to_protoBuff(sql::ResultSet *pRes,ASFConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: ASFGroup Config Result Set= %d ",__FUNCTION__,pRes->rowsCount()); 
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_ASFCONFIG_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            ::ASGroupCfg* pASFConfig = resp->add_asgroups();
            if(!pRes->isNull("APP_GRP_ID"))
                pASFConfig->set_appgroupid(pRes->getUInt("APP_GRP_ID"));
            if(!pRes->isNull("APP_GRP_NAME"))
                pASFConfig->set_appgroup(pRes->getString("APP_GRP_NAME"));
            if(!pRes->isNull("PRIORITY"))
                pASFConfig->set_priority(pRes->getUInt("PRIORITY"));
            if(!pRes->isNull("IS_HOSTED_APP_GRP"))
                pASFConfig->set_ishostedapp(pRes->getUInt("IS_HOSTED_APP_GRP"));
            if(!pRes->isNull("MAX_APP_INSTANCES"))
                pASFConfig->set_maxappinstances(pRes->getUInt("MAX_APP_INSTANCES"));
            if(!pRes->isNull("LB_METHOD"))
            {
                LBAlgorithm *localLBAlogrithm = pASFConfig->mutable_lbalgo(); 
                localLBAlogrithm->set_lbmethod(pRes->getString("LB_METHOD"));
            }
#if 0
            if(!pRes->isNull("CREATED_BY"))
                pASFConfig->set_createdby(pRes->getString("CREATED_BY"));
            if(!pRes->isNull("CREATION_TIME"))
                pASFConfig->set_creationdate(pRes->getString("CREATION_TIME"));
            if(!pRes->isNull("MODIFIED_BY"))
                pASFConfig->set_modifiedby(pRes->getString("MODIFIED_BY"));
            if(!pRes->isNull("MODIFICATION_TIME"))
                pASFConfig->set_modifytime(pRes->getString("MODIFICATION_TIME"));
#endif

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

DbStatus_e CMgrDbInterface::mysql_Asf_Add_Config_Reqs(ASFConfigReq *req, ASFConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    ::ASFConfiguration *pASFConfig;
    pASFConfig = req->mutable_asfinfo();
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    sql_ASFConfig_Create_Check_Modifcation_Query(pASFConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {   

        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_ASFRESPTIME_ERR_DB_ERROR;

        mysql_set_error_for_AsfRespTime_Config_Reqs(pASFConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);   
        return iReturn;
    }   
    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_ASFConfig_Create_Add_Query(pASFConfig,sStatement);
    }
    else // MOD
    {

        DLOG_ERROR("Record Already Present");
        delete pRes;
        mysql_set_error_for_AsfRespTime_Config_Reqs(pASFConfig,resp,SET_ASF_ERR_RESPTIME_ALREADY_PRESENT);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return SET_ASF_ERR_RESPTIME_ALREADY_PRESENT;
    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_ASFRESPTIME_ERR_DB_ERROR;

        mysql_set_error_for_AsfRespTime_Config_Reqs(pASFConfig,resp,iReturn);
        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}


DbStatus_e CMgrDbInterface::mysql_AsfGroup_Add_validation(::ASGroupCfg *pASFGroupConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;


    ::LBAlgorithm* localLBAlogrithm = pASFGroupConfig->mutable_lbalgo();
    sql_LbAlgorithm_Create_Check_Modifcation_Query(localLBAlogrithm,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
    {
        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_ASFCONFIG_ERR_LBMETHOD_NOT_SUPPORTED;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_AsfGroup_Add_Config_Reqs(ASFConfigReq *req, ASFConfigResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    ::ASGroupCfg *pASFGroupConfig;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int iCount = req->asgroups_size();
    DLOG_DEBUG(" %s: AsfGroupconfig_size = %d ",__FUNCTION__,iCount); 


    for(int i=0;i<iCount;i++)
    {

        pASFGroupConfig = req->mutable_asgroups(i);

        if((iReturn = mysql_AsfGroup_Add_validation(pASFGroupConfig)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_ASF_Create_Check_Modifcation_Query(pASFGroupConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = SET_ASFCONFIG_ERR_DB_ERROR;

            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_ASF_Create_Add_Query(pASFGroupConfig,sStatement);
        }
        else // MOD
        {

            delete pRes;
            DLOG_ERROR("Record Already Present");   
            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,SET_ASFCONFIG_ERR_COMPONENT_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return SET_ASFCONFIG_ERR_COMPONENT_ALREADY_PRESENT;
        }


        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = SET_ASFCONFIG_ERR_DB_ERROR;

            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_ASF_Create_Check_Modifcation_Query(pASFGroupConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = SET_ASFCONFIG_ERR_DB_ERROR;

            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_AsfGroup_AsfGroupid_to_protoBuff(pRes,pASFGroupConfig)) != DRE_DB_SUCCESS)
        {
            delete pRes;
            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        delete pRes;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}


DbStatus_e CMgrDbInterface::mysql_AsfGroup_AsfGroupid_to_protoBuff(sql::ResultSet *pRes,::ASGroupCfg *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: AsfGroup Result Set= %d ",__FUNCTION__,pRes->rowsCount()); 
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_ASFCONFIG_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            if(!pRes->isNull("APP_GRP_ID"))
                resp->set_appgroupid(pRes->getInt("APP_GRP_ID"));
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

DbStatus_e CMgrDbInterface::mysql_AsfGroup_Mod_validation(::ASGroupCfg *pASFGroupConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    ::LBAlgorithm* localLBAlogrithm = pASFGroupConfig->mutable_lbalgo();

    if(localLBAlogrithm->has_lbmethod())
    {
        sql_LbAlgorithm_Create_Check_Modifcation_Query(localLBAlogrithm,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_ASFCONFIG_ERR_LBMETHOD_NOT_SUPPORTED;

        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_AsfGroup_Mod_Config_Reqs(ASFConfigReq *req, ASFConfigResp *resp)
{

    DLOG_NONE(" < %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    ::ASGroupCfg *pASFGroupConfig;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;


    int iCount = req->asgroups_size();
    DLOG_DEBUG(" %s: asgroups_size = %d ",__FUNCTION__,iCount); 

    for(int i=0;i<iCount;i++)
    {
        pASFGroupConfig = req->mutable_asgroups(i);

        if((iReturn = mysql_AsfGroup_Mod_validation(pASFGroupConfig)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_ASF_Create_Check_Modifcation_Query(pASFGroupConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_ASFCONFIG_ERR_DB_ERROR;

            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            DLOG_ERROR("Record Not Present");   
            delete pRes;
            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,MOD_ASFCONFIG_ERR_COMPONENT_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_ASFCONFIG_ERR_COMPONENT_NOT_PRESENT;
        }
        else // MOD
        {
            sql_ASF_Create_Mod_Query(pASFGroupConfig,sStatement);   
        }


        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_ASFCONFIG_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);   
            mysql_set_error_for_Asf_Config_Reqs(pASFGroupConfig,resp,iReturn);
            return iReturn;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

