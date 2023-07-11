#include <CMgrDbInterface.h>

using namespace std;
extern std::map<int,std::string> errorMap;

void CMgrDbInterface::mysql_set_error_for_Tracing_Config_Reqs(::TraceReq *pTraceReq, TraceResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_TracingFilter_Config_Reqs(::TraceConfig *pTraceConfig, TraceResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());


    if(pTraceConfig->has_filtername())
        err->add_variables(pTraceConfig->filtername().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}




DbStatus_e CMgrDbInterface::mysql_Tracing_Get_Config_Reqs(TraceReq *req, TraceResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    ::TraceConfig *pTracingConfig;
    ::TraceConfig localTracingConfig;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);


    sql_Tracing_Create_Select_Query(req,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = GET_TRACECONFIG_ERR_DB_ERROR;

        mysql_set_error_for_Tracing_Config_Reqs(req,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);   
        return iReturn;
    }

    if((iReturn = mysql_Tracing_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
    {
        delete pRes;
        mysql_set_error_for_Tracing_Config_Reqs(req,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    delete pRes;

    int iCount = req->tracedata_size();

    DLOG_DEBUG(" %s: tracedata_size = %d ",__FUNCTION__,iCount); 

    for(int i=0;i<iCount;i++)
    {

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        pTracingConfig = req->mutable_tracedata(i);

        sql_TracingFilter_Create_Select_Query(pTracingConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_TRACECONFIG_ERR_DB_ERROR;

            mysql_set_error_for_TracingFilter_Config_Reqs(pTracingConfig,resp,iReturn);

            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

        if((iReturn = mysql_TracingFilter_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;
			mysql_set_error_for_TracingFilter_Config_Reqs(pTracingConfig,resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
        }

        delete pRes;
	}

    if(iCount == 0)
    {
        pTracingConfig = &localTracingConfig;

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_TracingFilter_Create_Select_Query(pTracingConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_TRACECONFIG_ERR_DB_ERROR;

            mysql_set_error_for_TracingFilter_Config_Reqs(pTracingConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

        if((iReturn = mysql_TracingFilter_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;
			mysql_set_error_for_TracingFilter_Config_Reqs(pTracingConfig,resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}

        delete pRes;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_Tracing_get_Traceid(TraceConfig *dreTraceReq)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    int iReturn;


    sql_TracingFilter_Create_OrderBy_Select_Query(dreTraceReq,sStatement);
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

    int iLocalFilterID = 1;
    int iFlag = 0;
    try
    {

        while(pRes->next())
        {
            if(!pRes->isNull("FILTER_ID"))
            {
                if(pRes->getInt("FILTER_ID") != iLocalFilterID)
                {
                    iFlag = 1;
                    break;
                }
                iLocalFilterID++;                
            }
        }

        delete pRes;

        if(iFlag != 0 || iLocalFilterID <= MAX_FILTER_ID)
        {
            DLOG_INFO("FilterID Selected = %d",iLocalFilterID);
            dreTraceReq->set_filterid(iLocalFilterID); 
        }
        else
        {
            return SET_TRACECONFIG_ERR_REACHED_MAX_FILTER;
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    return DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_Tracing_resultset_to_protoBuff(sql::ResultSet *pRes,TraceResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: Tracing Config Result Set= %d ",__FUNCTION__,pRes->rowsCount()); 
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_TRACECONFIG_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            if(!pRes->isNull("ENABLE_TRACING"))
                resp->set_enabletrace(pRes->getInt("ENABLE_TRACING"));
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


DbStatus_e CMgrDbInterface::mysql_TracingFilter_resultset_to_protoBuff(sql::ResultSet *pRes,TraceResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: Tracing Config Result Set= %d ",__FUNCTION__,pRes->rowsCount()); 
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_TRACECONFIG_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            ::TraceConfig* pTraceConfig = resp->add_tracedata();

            if(!pRes->isNull("FILTER_ID"))
                pTraceConfig->set_filterid(pRes->getInt("FILTER_ID"));
            if(!pRes->isNull("FILTER_NAME"))
                pTraceConfig->set_filtername(pRes->getString("FILTER_NAME"));
            if(!pRes->isNull("RULE"))
                pTraceConfig->set_rule(pRes->getString("RULE"));
            if(!pRes->isNull("PRIORITY"))
                pTraceConfig->set_priority(pRes->getInt("PRIORITY"));
            if(!pRes->isNull("EXP_DURATION"))
            {
                if(pRes->getInt("EXP_DURATION") != -1)
                    pTraceConfig->set_expireduration(pRes->getInt("EXP_DURATION"));
            }
            if(!pRes->isNull("EXP_MESSAGES"))
            {
                if(pRes->getInt("EXP_MESSAGES") != -1)
                    pTraceConfig->set_expiremessages(pRes->getInt("EXP_MESSAGES"));
            }
            if(!pRes->isNull("FILTER_STATUS"))
                pTraceConfig->set_filterstatus(pRes->getInt("FILTER_STATUS"));
            if(!pRes->isNull("LOG_LEVEL"))
                pTraceConfig->set_loglevel(pRes->getInt("LOG_LEVEL"));

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


DbStatus_e CMgrDbInterface::mysql_Tracing_Set_Config_Reqs(TraceReq *req, TraceResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;


    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if((iReturn = sql_Tracing_Payload_Validation(req)) != DRE_DB_SUCCESS)
    {
        mysql_set_error_for_Tracing_Config_Reqs(req,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    sql_Tracing_Create_Check_Modifcation_Query(req,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ENABLE_TRACECONFIG_ERR_DB_ERROR;

        mysql_set_error_for_Tracing_Config_Reqs(req,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_Tracing_Create_Add_Query(req,sStatement);   
    }
    else // MOD
    {
        sql_Tracing_Create_Mod_Query(req,sStatement);   
    }

    delete pRes;

    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ENABLE_TRACECONFIG_ERR_DB_ERROR;

        mysql_set_error_for_Tracing_Config_Reqs(req,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);   
        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}


DbStatus_e CMgrDbInterface::mysql_TracingFilter_Add_Config_Reqs(TraceReq *req, TraceResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    ::TraceConfig *pTracingData;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int iCount = req->tracedata_size();
    DLOG_DEBUG(" %s: tracedata_size = %d ",__FUNCTION__,iCount); 


    for(int i=0;i<iCount;i++)
    {

        pTracingData = req->mutable_tracedata(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if((iReturn = sql_TracingFilter_Payload_Validation(pTracingData)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_TracingFilter_Config_Reqs(pTracingData,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        if((iReturn = mysql_Tracing_get_Traceid(pTracingData)) != DRE_DB_SUCCESS)
        {

            if(iReturn == DRE_DB_FAIL)
                iReturn = SET_TRACECONFIG_ERR_DB_ERROR;

            mysql_set_error_for_TracingFilter_Config_Reqs(pTracingData,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        sql_TracingFilter_Create_Check_Modifcation_Query(pTracingData,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = SET_TRACECONFIG_ERR_DB_ERROR;

            mysql_set_error_for_TracingFilter_Config_Reqs(pTracingData,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_TracingFilter_Create_Add_Query(pTracingData,sStatement);    
        }
        else // MOD
        {
            delete pRes;
			DLOG_ERROR("Record Already Present"); 	
			mysql_set_error_for_TracingFilter_Config_Reqs(pTracingData,resp,SET_TRACECONFIG_ERR_FILTER_ALREADY_PRESENT);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return SET_TRACECONFIG_ERR_FILTER_ALREADY_PRESENT;
		}

        delete pRes;

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = SET_TRACECONFIG_ERR_DB_ERROR;

            mysql_set_error_for_TracingFilter_Config_Reqs(pTracingData,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

        unset_tracing_variables_before_sending_to_dre(pTracingData);

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::unset_tracing_variables_before_sending_to_dre(TraceConfig *req)
{
    DLOG_NONE(" < %s ",__FUNCTION__);
    if(req->has_expireduration())
    {
        if((int)req->expireduration() == -1)
        {
            req->clear_expireduration();
        }
    }

    if(req->has_expiremessages())
    {
        if((int)req->expiremessages() == -1)
        {
            req->clear_expiremessages();
        }
    }
    DLOG_NONE(" > %s ",__FUNCTION__);

    return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_TracingFilter_Del_Config_Reqs(TraceReq *req, TraceResp *resp)
{

    DLOG_NONE(" < %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    ::TraceConfig *pTracingConfig;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;


    int iCount = req->tracedata_size();
    DLOG_DEBUG(" %s: tracedata_size = %d ",__FUNCTION__,iCount); 

    for(int i=0;i<iCount;i++)
    {
        pTracingConfig = req->mutable_tracedata(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_TracingFilter_Create_Check_Modifcation_Query(pTracingConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_TRACECONFIG_ERR_DB_ERROR;

            mysql_set_error_for_TracingFilter_Config_Reqs(pTracingConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
			DLOG_ERROR("Record not Present"); 	
			mysql_set_error_for_TracingFilter_Config_Reqs(pTracingConfig,resp,DEL_TRACECONFIG_ERR_FILTER_WITH_FILTER_NAME_NOT_PRESENT);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return DEL_TRACECONFIG_ERR_FILTER_WITH_FILTER_NAME_NOT_PRESENT;
		}
		else // MOD
		{
			sql_TracingFilter_Create_Delete_Query(pTracingConfig,sStatement);	
		}

        delete pRes;

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_TRACECONFIG_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);   
            mysql_set_error_for_TracingFilter_Config_Reqs(pTracingConfig,resp,iReturn);
            return iReturn;
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_Tracing_filterid_to_protoBuff(sql::ResultSet *pRes,TraceConfig *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: Tracing Config Result Set= %d ",__FUNCTION__,pRes->rowsCount()); 
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_TRACECONFIG_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            if(!pRes->isNull("FILTER_ID"))
                resp->set_filterid(pRes->getInt("FILTER_ID"));
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



DbStatus_e CMgrDbInterface::mysql_TracingFilter_Mod_Config_Reqs(TraceReq *req, TraceResp *resp)
{

    DLOG_NONE(" < %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    ::TraceConfig *pTracingConfig;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;


    int iCount = req->tracedata_size();
    DLOG_DEBUG(" %s: tracedata_size = %d ",__FUNCTION__,iCount); 

    for(int i=0;i<iCount;i++)
    {
        pTracingConfig = req->mutable_tracedata(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if((iReturn = sql_TracingFilter_Payload_Validation(pTracingConfig)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_TracingFilter_Config_Reqs(pTracingConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        sql_TracingFilter_Create_Check_Modifcation_Query(pTracingConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_TRACECONFIG_ERR_DB_ERROR;

            mysql_set_error_for_TracingFilter_Config_Reqs(pTracingConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
			DLOG_ERROR("Record not Present"); 	
			mysql_set_error_for_TracingFilter_Config_Reqs(pTracingConfig,resp,MOD_TRACECONFIG_ERR_FILTER_WITH_FILTER_NAME_NOT_PRESENT);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return MOD_TRACECONFIG_ERR_FILTER_WITH_FILTER_NAME_NOT_PRESENT;
		}
		else // MOD
		{
			sql_TracingFilter_Create_Mod_Query(pTracingConfig,sStatement);	
		}

        delete pRes;

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_TRACECONFIG_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);   
            mysql_set_error_for_TracingFilter_Config_Reqs(pTracingConfig,resp,iReturn);
            return iReturn;
        }

        unset_tracing_variables_before_sending_to_dre(pTracingConfig);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

