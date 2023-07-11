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
void CMgrIwfDbInterface::mysql_set_error_for_IWFFeature_Config_Reqs(IwfFeatureConfig *pIwfFeatureConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());
    if(pIwfFeatureConfig->has_featurename())
    	err->add_variables(pIwfFeatureConfig->featurename());
    DLOG_NONE(" < %s ",__FUNCTION__);
}


DbStatus_e CMgrIwfDbInterface::Fill_IWFFeatures_protobuff(IwfFeaturesConfig *pIwfFeaturesConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    int i=0;
    int ifData = 0;

    IwfFeatureConfig LocalIwfFeatureConfigObj;
    IwfFeatureConfig *pIwfFeatureConfig = NULL;

    int iCount = pIwfFeaturesConfig->iwffeatureinfo_size();
    DLOG_INFO("pIwfFeaturesConfig->iwffeatureinfo_size() = %d",iCount);
    do
    {
        if(iCount != 0)
            pIwfFeatureConfig = pIwfFeaturesConfig->mutable_iwffeatureinfo(i);
        else
            pIwfFeatureConfig = &LocalIwfFeatureConfigObj;

        sql_IWFFeature_Create_Select_Query(pIwfFeatureConfig,sStatement);

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
                iReturn = GET_FEATURE_ERR_DB_ERROR;

            mysql_set_error_for_IWFFeature_Config_Reqs(pIwfFeatureConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
            if(pRes->rowsCount() != 0)
            {
                IwfFeaturesConfig *LocalIwfFeaturesConfig = resp->mutable_featuresinfo();

                while(pRes->next())
                {
                    pIwfFeatureConfig = LocalIwfFeaturesConfig->add_iwffeatureinfo();

                    ifData = 1;
                    if(!pRes->isNull("IWF_FEATURE_NAME"))
                        pIwfFeatureConfig->set_featurename(pRes->getString("IWF_FEATURE_NAME"));
                    if(!pRes->isNull("IWF_FEATURE_STATUS"))
                        pIwfFeatureConfig->set_statusvalue(pRes->getDouble("IWF_FEATURE_STATUS"));


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
        DLOG_DEBUG("There is no data in the table setting GET_FEATURE_ERR_NO_DATA");
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(GET_FEATURE_ERR_NO_DATA);
        err->set_errormsgkey(iwfErrorMap[GET_FEATURE_ERR_NO_DATA]);
        DLOG_DEBUG("Error key is %s", (iwfErrorMap[GET_FEATURE_ERR_NO_DATA]).c_str());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfFeature_Del_Config_Reqs(IwfFeaturesConfig *pIwfFeaturesConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfFeaturesConfig->iwffeatureinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(DEL_FEATURE_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_FEATURE_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfFeatureConfig *pIwfFeatureConfig = pIwfFeaturesConfig->mutable_iwffeatureinfo(i);
        sql_IWFFeature_Create_Check_Modifcation_Query(pIwfFeatureConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_FEATURE_ERR_DB_ERROR;

            mysql_set_error_for_IWFFeature_Config_Reqs(pIwfFeatureConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Not Present");   
            mysql_set_error_for_IWFFeature_Config_Reqs(pIwfFeatureConfig,resp,DEL_FEATURE_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_FEATURE_ERR_NOT_PRESENT;

        }
        else // MOD
        {
            sql_IWFFeature_Create_Delete_Query(pIwfFeatureConfig,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_FEATURE_ERR_DB_ERROR;

            mysql_set_error_for_IWFFeature_Config_Reqs(pIwfFeatureConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}



DbStatus_e CMgrIwfDbInterface::mysql_IwfFeature_Mod_Config_Reqs(IwfFeaturesConfig *pIwfFeaturesConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfFeaturesConfig->iwffeatureinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(MOD_FEATURE_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[MOD_FEATURE_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfFeatureConfig *pIwfFeatureConfig = pIwfFeaturesConfig->mutable_iwffeatureinfo(i);
        sql_IWFFeature_Create_Check_Modifcation_Query(pIwfFeatureConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_FEATURE_ERR_DB_ERROR;

            mysql_set_error_for_IWFFeature_Config_Reqs(pIwfFeatureConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Not Present");   
            mysql_set_error_for_IWFFeature_Config_Reqs(pIwfFeatureConfig,resp,MOD_FEATURE_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_FEATURE_ERR_NOT_PRESENT;

        }
        else // MOD
        {
            sql_IWFFeature_Create_Mod_Query(pIwfFeatureConfig,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_FEATURE_ERR_DB_ERROR;

            mysql_set_error_for_IWFFeature_Config_Reqs(pIwfFeatureConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}



DbStatus_e CMgrIwfDbInterface::mysql_IwfFeature_Add_Config_Reqs(IwfFeaturesConfig *pIwfFeaturesConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfFeaturesConfig->iwffeatureinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(ADD_FEATURE_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[ADD_FEATURE_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfFeatureConfig *pIwfFeatureConfig = pIwfFeaturesConfig->mutable_iwffeatureinfo(i);
        sql_IWFFeature_Create_Check_Modifcation_Query(pIwfFeatureConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_FEATURE_ERR_DB_ERROR;

            mysql_set_error_for_IWFFeature_Config_Reqs(pIwfFeatureConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_IWFFeature_Create_Add_Query(pIwfFeatureConfig,sStatement);
        }
        else // MOD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present");   
            mysql_set_error_for_IWFFeature_Config_Reqs(pIwfFeatureConfig,resp,ADD_FEATURE_ERR_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_FEATURE_ERR_ALREADY_PRESENT;
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_FEATURE_ERR_DB_ERROR;

            mysql_set_error_for_IWFFeature_Config_Reqs(pIwfFeatureConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}



DbStatus_e CMgrIwfDbInterface::Fill_IWFFeature_protobuff(IwfFeatureConfig *pIwfFeatureConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFFeature_Create_Select_Query(pIwfFeatureConfig,sStatement);

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
            iReturn = GET_FEATURE_ERR_DB_ERROR;

        mysql_set_error_for_IWFFeature_Config_Reqs(pIwfFeatureConfig,resp,iReturn);
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
                if(!pRes->isNull("IWF_FEATURE_NAME"))
                    pIwfFeatureConfig->set_featurename(pRes->getString("IWF_FEATURE_NAME"));
                if(!pRes->isNull("IWF_FEATURE_STATUS"))
                   pIwfFeatureConfig->set_statusvalue(pRes->getDouble("IWF_FEATURE_STATUS"));
            }
        }
        else
        {
            delete pRes;
            return GET_FEATURE_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::mysql_IWFFeatures_Get_Config_Reqs(IwfFeaturesConfig *pIwfFeaturesConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    return Fill_IWFFeatures_protobuff(pIwfFeaturesConfig,resp);

    DLOG_NONE(" < %s ",__FUNCTION__);
}
