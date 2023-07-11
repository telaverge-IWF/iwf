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
void CMgrIwfDbInterface::mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(IwfDccaDestConfig *pIwfDccaDestConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());
    if(pIwfDccaDestConfig->has_destname())
    	err->add_variables(pIwfDccaDestConfig->destname());

    if(pIwfDccaDestConfig->iwfdccaendpoints_size())
    {
        ::IwfDccaEndPointConfig* localEndPointObj=NULL;
        localEndPointObj = pIwfDccaDestConfig->mutable_iwfdccaendpoints(0);
        if(localEndPointObj->has_endpointname())
            err->add_variables(localEndPointObj->endpointname());
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfDccaEndPointConfig_Del_Config_Reqs(IwfDccaDestsConfig *pIwfDccaDestsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfDccaDestsConfig->iwfdccadestinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(DEL_DCCA_DEST_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_DCCA_DEST_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfDccaDestConfig *pIwfDccaDestConfig = pIwfDccaDestsConfig->mutable_iwfdccadestinfo(i);
        if(pIwfDccaDestConfig->has_destname() && pIwfDccaDestConfig->iwfdccaendpoints_size())
        {
            IwfDccaDestConfig LocalIwfDccaDestConfig;
            LocalIwfDccaDestConfig.set_destname(pIwfDccaDestConfig->destname());
            sql_DccaEndPoint_Create_Validation_Query_for_Realm(&LocalIwfDccaDestConfig, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_DCCA_DEST_ERR_DB_ERROR;

                mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(pIwfDccaDestConfig,resp,iReturn);

                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0)
            {
                delete pRes;
                DLOG_ERROR("Record Not present");
                DLOG_NONE(" < %s ",__FUNCTION__);
                iReturn = DEL_DCCA_DEST_ERR_REALM_NOT_PRESENT;
                mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(pIwfDccaDestConfig,resp,iReturn);
                return iReturn;
            }
            delete pRes;

            int endpoint_size = pIwfDccaDestConfig->iwfdccaendpoints_size();
            for (int j = 0; j < endpoint_size; j++)
            {
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                LocalIwfDccaDestConfig.set_destname(pIwfDccaDestConfig->destname().c_str());
                IwfDccaEndPointConfig *LocalIwfDccaEndPointConfig = LocalIwfDccaDestConfig.add_iwfdccaendpoints();
                LocalIwfDccaEndPointConfig->CopyFrom(*pIwfDccaDestConfig->mutable_iwfdccaendpoints(j));
                sql_DccaEndPoint_Create_Select_Query(&LocalIwfDccaDestConfig,sStatement);

                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                {
                    if(pRes != NULL)
                    {
                        delete pRes;
                    }
                    DLOG_ERROR("Query Execution Failed %s",sStatement);

                    if(iReturn == IWF_DB_FAIL)
                        iReturn = DEL_DCCA_DEST_ERR_DB_ERROR;
                    mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(pIwfDccaDestConfig,resp,iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }

                memset(sStatement,0,MAX_STATEMENT_SIZE);

                if(pRes->rowsCount() == 0)
                {
                    delete pRes;
                    DLOG_ERROR("Record Not present");
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    iReturn = DEL_DCCA_DEST_ERR_ENDPOINT_NOT_PRESENT;
                    mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(&LocalIwfDccaDestConfig,resp,DEL_DCCA_DEST_ERR_DESTREALM_NOT_PRESENT);
                    return iReturn;
                }
                
                delete pRes;
                pRes=NULL;

                sql_DccaEndPoint_Create_Delete_Query(&LocalIwfDccaDestConfig,sStatement);

                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                {
                    DLOG_ERROR("Query Execution Failed %s",sStatement);
                    if(iReturn == IWF_DB_FAIL)
                        iReturn = DEL_DCCA_DEST_ERR_DB_ERROR;

                    mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(pIwfDccaDestConfig,resp,iReturn);
                    DLOG_DEBUG("iReturn = %d",iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
            }
        }
        else
        {
            ErrorDetails* err = resp->add_errordetails();
            err->set_errorcode(DEL_DCCA_DEST_ERR_DATA_NOT_SET);
            err->set_errormsgkey(iwfErrorMap[DEL_DCCA_DEST_ERR_DATA_NOT_SET]);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return IWF_DB_FAIL;
        }
    }
    
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfDccaDestConfig_Del_Config_Reqs(IwfDccaDestsConfig *pIwfDccaDestsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfDccaDestsConfig->iwfdccadestinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(DEL_DCCA_DEST_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_DCCA_DEST_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfDccaDestConfig *pIwfDccaDestConfig = pIwfDccaDestsConfig->mutable_iwfdccadestinfo(i);
        if(pIwfDccaDestConfig->has_destname())
        {
            IwfDccaDestConfig LocalIwfDccaDestConfig;
            LocalIwfDccaDestConfig.set_destname(pIwfDccaDestConfig->destname().c_str());
            sql_DccaEndPoint_Create_Validation_Query_for_Realm(&LocalIwfDccaDestConfig, sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_DCCA_DEST_ERR_DB_ERROR;

                mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(pIwfDccaDestConfig,resp,iReturn);

                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0)
            {
                delete pRes;
                DLOG_ERROR("Record Not present");
                DLOG_NONE(" < %s ",__FUNCTION__);
                iReturn = DEL_DCCA_DEST_ERR_REALM_NOT_PRESENT;
                mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(pIwfDccaDestConfig,resp,iReturn);
                return iReturn;
            }
            delete pRes;
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            sql_DccaEndPoint_Create_Select_Query(&LocalIwfDccaDestConfig,sStatement);
            
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_DCCA_DEST_ERR_DB_ERROR;
                mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(pIwfDccaDestConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0)
            {
                delete pRes;
                DLOG_ERROR("Record Not present");
                DLOG_NONE(" < %s ",__FUNCTION__);
                iReturn = DEL_DCCA_DEST_ERR_DESTREALM_NOT_PRESENT;
                mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(&LocalIwfDccaDestConfig,resp,DEL_DCCA_DEST_ERR_DESTREALM_NOT_PRESENT);
                return iReturn;
            }
            delete pRes;
            
            sql_DccaEndPoint_Create_Delete_Query(&LocalIwfDccaDestConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_DCCA_DEST_ERR_DB_ERROR;

                mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(pIwfDccaDestConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
        else
        {
            ErrorDetails* err = resp->add_errordetails();
            err->set_errorcode(DEL_DCCA_DEST_ERR_DATA_NOT_SET);
            err->set_errormsgkey(iwfErrorMap[DEL_DCCA_DEST_ERR_DATA_NOT_SET]);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return IWF_DB_FAIL;
        }
    }
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfDccaDestConfig_Add_Config_Reqs(IwfDccaDestsConfig *pIwfDccaDestsConfig,IWFCfgResp *resp)
{
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfDccaDestsConfig->iwfdccadestinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(ADD_DCCA_DEST_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[ADD_DCCA_DEST_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfDccaDestConfig *pIwfDccaDestConfig = pIwfDccaDestsConfig->mutable_iwfdccadestinfo(i);
        
        if((iReturn = mysql_IwfDccaDestConfig_Add_Validation_and_Process_Reqs(pIwfDccaDestConfig, resp)) != IWF_DB_SUCCESS)
        {
            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_DCCA_DEST_ERR_DB_ERROR;

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        pIwfDccaDestConfig->clear_iwfdccaendpoints();
    }
    //NOTE: Fill endpoinds configuration to pass to IWF.
    Fill_IWFDccaDestsConfig_protobuff(pIwfDccaDestsConfig,resp);
    if(resp->has_iwfdccainfo())
    {
        IwfDccaConfig* LocalIwfDccaConfig = resp->mutable_iwfdccainfo();
        if(LocalIwfDccaConfig->has_iwfdccadestsinfo())
        {
            pIwfDccaDestsConfig->CopyFrom(LocalIwfDccaConfig->iwfdccadestsinfo());
            pIwfDccaDestsConfig->set_operreqid(SET_IWF_DCCA_DEST);
            resp->clear_iwfdccainfo();
        }
    }
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfDccaDestConfig_Add_Validation_and_Process_Reqs(IwfDccaDestConfig *pIwfDccaDestConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0}; 
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    IwfDccaDestConfig LocalIwfDccaDestConfig;
    if(pIwfDccaDestConfig->has_destname())
    {
        LocalIwfDccaDestConfig.set_destname(pIwfDccaDestConfig->destname());
        sql_DccaEndPoint_Create_Validation_Query_for_Realm(&LocalIwfDccaDestConfig, sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_DCCA_DEST_ERR_DB_ERROR;

            mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(pIwfDccaDestConfig,resp,iReturn);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Record Not present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            iReturn = ADD_DCCA_DEST_ERR_REALM_NOT_PRESENT;
            mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(pIwfDccaDestConfig,resp,iReturn);
            return iReturn;
        }
        delete pRes;
        
        
        int endpoint_count = pIwfDccaDestConfig->iwfdccaendpoints_size();
        DLOG_DEBUG("EndPoint Count = %d",endpoint_count);
        if(endpoint_count)
        {
            for(int j = 0; j < endpoint_count; j++)
            {
                memset(sStatement,0,MAX_STATEMENT_SIZE);

                IwfDccaDestConfig lIwfDccaDestConfig;
                lIwfDccaDestConfig.set_destname(pIwfDccaDestConfig->destname());
                if(pIwfDccaDestConfig->has_sendccrtindicator())
                    lIwfDccaDestConfig.set_sendccrtindicator(pIwfDccaDestConfig->sendccrtindicator());
                IwfDccaEndPointConfig *pIwfDccaEndPointConfig = pIwfDccaDestConfig->mutable_iwfdccaendpoints(j);
                IwfDccaEndPointConfig *pLocalIwfDccaEndPointConfig = lIwfDccaDestConfig.add_iwfdccaendpoints();
                pLocalIwfDccaEndPointConfig->CopyFrom(*pIwfDccaEndPointConfig);
                sql_DccaEndPoint_Create_Check_Modifcation_Query(&lIwfDccaDestConfig, sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                {
                    if(pRes != NULL)
                    {
                        delete pRes;
                    }
                    DLOG_ERROR("Query Execution Failed %s",sStatement);

                    if(iReturn == IWF_DB_FAIL)
                        iReturn = ADD_DCCA_DEST_ERR_DB_ERROR;

                    mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(&lIwfDccaDestConfig,resp,iReturn);

                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }

                memset(sStatement,0,MAX_STATEMENT_SIZE);

                if(pRes->rowsCount() > 0)
                {
                    delete pRes;
                    pRes = NULL;
                    DLOG_DEBUG("Record Already present, Delete and add the EndPoint newly");
                    sql_DccaEndPoint_Create_Delete_Query(&lIwfDccaDestConfig,sStatement);

                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed %s",sStatement);
                        if(iReturn == IWF_DB_FAIL)
                            iReturn = ADD_DCCA_DEST_ERR_DB_ERROR;

                        mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(pIwfDccaDestConfig,resp,iReturn);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }
                }
                if(pRes != NULL)
                {
                    delete pRes;
                    pRes = NULL; 
                }
                sql_DccaEndPoint_Create_Select_Query(&LocalIwfDccaDestConfig, sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                {
                    if(pRes != NULL)
                    {
                        delete pRes;
                        pRes = NULL;
                    }
                    DLOG_ERROR("Query Execution Failed %s",sStatement);

                    if(iReturn == IWF_DB_FAIL)
                        iReturn = ADD_DCCA_DEST_ERR_DB_ERROR;

                    mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(&lIwfDccaDestConfig,resp,iReturn);

                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }

                memset(sStatement,0,MAX_STATEMENT_SIZE);
                DLOG_DEBUG("Number of EndPoints in DB with Dest-Realm = %d",pRes->rowsCount());
                if(pRes->rowsCount() >= MAX_DCCA_ENDPOINTS)
                {
                    delete pRes;
                    DLOG_ERROR("Max EndPoint Count %d Reached.",MAX_DCCA_ENDPOINTS);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    iReturn = ADD_DCCA_DEST_ERR_MAX_ENDPOINTS_REACHED;
                    mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(&lIwfDccaDestConfig,resp,iReturn);
                    return iReturn;
                }
                delete pRes;
                pRes = NULL;
                sql_DccaEndPoint_Create_Add_Query(&lIwfDccaDestConfig,sStatement);

                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                {
                    DLOG_ERROR("Query Execution Failed %s",sStatement);
                    if(iReturn == IWF_DB_FAIL)
                        iReturn = ADD_DCCA_DEST_ERR_DB_ERROR;

                    mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(&lIwfDccaDestConfig,resp,iReturn);
                    DLOG_DEBUG("iReturn = %d",iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
            }
        }
#if 0
        else
        {
            ErrorDetails* err = resp->add_errordetails();
            err->set_errorcode(ADD_DCCA_DEST_ERR_DATA_NOT_SET);
            err->set_errormsgkey(iwfErrorMap[ADD_DCCA_DEST_ERR_DATA_NOT_SET]);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return IWF_DB_FAIL;
        }
#endif
        if(pIwfDccaDestConfig->has_sendccrtindicator())
        {
            sql_DccaEndPoint_Create_Modify_Query(pIwfDccaDestConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_DCCA_DEST_ERR_DB_ERROR;

                mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(pIwfDccaDestConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
    }
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFDccaDestConfig_Get_Config_Reqs(IwfDccaDestsConfig *pIwfDccaDestsConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    return Fill_IWFDccaDestsConfig_protobuff(pIwfDccaDestsConfig,resp);

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFDccaDestsConfig_protobuff(IwfDccaDestsConfig *pIwfDccaDestsConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    int i=0;
    int ifData = 0;
    
    IwfDccaDestConfig LocalIwfDccaDestConfig;
    IwfDccaDestConfig *pIwfDccaDestConfig = NULL;
    
    int iCount = pIwfDccaDestsConfig->iwfdccadestinfo_size();
    DLOG_INFO("pIwfDccaDestsConfig->iwfdccadestinfo_size() = %d",iCount);
    do
    {
        if(iCount != 0)
            pIwfDccaDestConfig = pIwfDccaDestsConfig->mutable_iwfdccadestinfo(i);
        else
            pIwfDccaDestConfig = &LocalIwfDccaDestConfig;

        sql_DccaEndPoint_Create_Select_Query(pIwfDccaDestConfig,sStatement);

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
                iReturn = GET_DCCA_DEST_ERR_DB_ERROR;

            mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(pIwfDccaDestConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
            if(pRes->rowsCount() != 0)
            {
                IwfDccaConfig *LocalIwfDccaConfig = resp->mutable_iwfdccainfo();
                IwfDccaDestsConfig *LocalIwfDccaDestsConfig = LocalIwfDccaConfig->mutable_iwfdccadestsinfo();

                while (pRes->next())
                {
                    ifData = 1;
                    int local_size_of_dest = LocalIwfDccaDestsConfig->iwfdccadestinfo_size();
                    if(local_size_of_dest > 0)
                    {
                        bool set_realm = false;
                        for(int i=0; i< local_size_of_dest; i++)
                        {
                            IwfDccaDestConfig *LocalIwfDccaDestConfigObj = LocalIwfDccaDestsConfig->mutable_iwfdccadestinfo(i);
                            if(LocalIwfDccaDestConfigObj->has_destid() &&
                                    !pRes->isNull("DEST_REALM_ID") &&
                                    (LocalIwfDccaDestConfigObj->destid() == (unsigned int)pRes->getInt("DEST_REALM_ID")))
                            {
                                set_realm = true;
                                IwfDccaEndPointConfig *pLocalIwfDccaEndPointConfig = LocalIwfDccaDestConfigObj->add_iwfdccaendpoints();
                                if(!pRes->isNull("ENDPOINT_NAME"))
                                    pLocalIwfDccaEndPointConfig->set_endpointname(pRes->getString("ENDPOINT_NAME"));
                                if(!pRes->isNull("PRIORITY"))
                                    pLocalIwfDccaEndPointConfig->set_priority(pRes->getInt("PRIORITY"));
                                if(!pRes->isNull("SEND_CCRT_INDICATOR") && !LocalIwfDccaDestConfigObj->has_sendccrtindicator())
                                    LocalIwfDccaDestConfigObj->set_sendccrtindicator(pRes->getInt("SEND_CCRT_INDICATOR"));
                                break;
                            }
                        }

                        if(!set_realm)
                        {
                            pIwfDccaDestConfig = LocalIwfDccaDestsConfig->add_iwfdccadestinfo();
                            IwfDccaEndPointConfig *pLocalIwfDccaEndPointConfig = pIwfDccaDestConfig->add_iwfdccaendpoints();
                            if(!pRes->isNull("DEST_REALM_ID"))
                                pIwfDccaDestConfig->set_destid(pRes->getInt("DEST_REALM_ID"));
                            if(!pRes->isNull("ENDPOINT_NAME"))
                                pLocalIwfDccaEndPointConfig->set_endpointname(pRes->getString("ENDPOINT_NAME"));
                            if(!pRes->isNull("PRIORITY"))
                                pLocalIwfDccaEndPointConfig->set_priority(pRes->getInt("PRIORITY"));
                            if(!pRes->isNull("SEND_CCRT_INDICATOR") && !pIwfDccaDestConfig->has_sendccrtindicator())
                                pIwfDccaDestConfig->set_sendccrtindicator(pRes->getInt("SEND_CCRT_INDICATOR"));

                        }
                    }
                    else
                    {
                        pIwfDccaDestConfig = LocalIwfDccaDestsConfig->add_iwfdccadestinfo();
                        IwfDccaEndPointConfig *pLocalIwfDccaEndPointConfig = pIwfDccaDestConfig->add_iwfdccaendpoints();
                        if(!pRes->isNull("DEST_REALM_ID"))
                                pIwfDccaDestConfig->set_destid(pRes->getInt("DEST_REALM_ID"));
                        if(!pRes->isNull("ENDPOINT_NAME"))
                            pLocalIwfDccaEndPointConfig->set_endpointname(pRes->getString("ENDPOINT_NAME"));
                        if(!pRes->isNull("PRIORITY"))
                            pLocalIwfDccaEndPointConfig->set_priority(pRes->getInt("PRIORITY"));
                        if(!pRes->isNull("SEND_CCRT_INDICATOR") && !pIwfDccaDestConfig->has_sendccrtindicator())
                            pIwfDccaDestConfig->set_sendccrtindicator(pRes->getInt("SEND_CCRT_INDICATOR"));

                    }
                }
            }
            delete pRes;
            if(ifData)
            {
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                IwfDccaConfig *LocalIwfDccaConfig = resp->mutable_iwfdccainfo();
                IwfDccaDestsConfig *LocalIwfDccaDestsConfig = LocalIwfDccaConfig->mutable_iwfdccadestsinfo();
                int local_size_of_dest = LocalIwfDccaDestsConfig->iwfdccadestinfo_size();
                for(int i = 0; i < local_size_of_dest; i++)
                {
                    IwfDccaDestConfig *LocalIwfDccaDestConfigObj = LocalIwfDccaDestsConfig->mutable_iwfdccadestinfo(i);
                    if(LocalIwfDccaDestConfigObj->has_destid())
                    {
                        RealmConfig LocalRealmConfig;
                        LocalRealmConfig.set_realmid(LocalIwfDccaDestConfigObj->destid());
                        sql_Realm_Create_Select_Query(&LocalRealmConfig, sStatement);
                        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                        {
                            if(pRes != NULL)        
                            {
                                delete pRes;
                            }

                            DLOG_ERROR("Query Execution Failed: %s",sStatement);
                            if(iReturn == IWF_DB_FAIL)
                                iReturn = GET_DCCA_DEST_ERR_DB_ERROR;

                            mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(pIwfDccaDestConfig,resp,iReturn);
                            DLOG_NONE(" < %s ",__FUNCTION__);
                            return iReturn;
                        }
                        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
                        if(pRes->rowsCount() != 0)
                        {
                            while (pRes->next())
                            {
                                if(!pRes->isNull("REALM_NAME"))
                                    LocalIwfDccaDestConfigObj->set_destname(pRes->getString("REALM_NAME"));
                            }
                        }
                        delete pRes;
                    }
                }
            }
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
        DLOG_DEBUG("There is no data in the table setting GET_DCCA_DEST_ERR_NO_DATA");
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(GET_DCCA_DEST_ERR_NO_DATA);
        err->set_errormsgkey(iwfErrorMap[GET_DCCA_DEST_ERR_NO_DATA]);
        DLOG_DEBUG("Error key is %s", (iwfErrorMap[GET_DCCA_DEST_ERR_NO_DATA]).c_str());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return GET_DCCA_DEST_ERR_NO_DATA;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}


