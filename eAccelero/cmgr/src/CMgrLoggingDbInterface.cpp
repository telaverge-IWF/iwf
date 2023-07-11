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

void CMgrDbInterface::mysql_set_error_for_Logging_Config_Reqs(::LoggerConf *pLoggerConf, LoggerConfResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pLoggerConf->has_componentname())
        err->add_variables(pLoggerConf->componentname());

    DLOG_NONE(" < %s ",__FUNCTION__);
}


DbStatus_e CMgrDbInterface::mysql_Logging_Get_Config_Reqs(LoggerConfReq *req, LoggerConfResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    ::LoggerConf *pLoggingConfig;
    ::LoggerConf localLoggingConfig;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int iCount = req->loggerconfig_size();

    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG(" %s: loggerconfig_size = %d ",__FUNCTION__,iCount); 

    for(int i=0;i<iCount;i++)
    {

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        pLoggingConfig = req->mutable_loggerconfig(i);

        sql_LoggingConfig_Create_Select_Query(pLoggingConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_LOGCONFIG_ERR_DB_ERROR;

            mysql_set_error_for_Logging_Config_Reqs(pLoggingConfig,resp,iReturn);

            DLOG_NONE(" < %s ",__FUNCTION__);       
            return iReturn;
        }

        if((iReturn = mysql_LoggingConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {

            delete pRes;
            mysql_set_error_for_Logging_Config_Reqs(pLoggingConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        delete pRes;
    }

    if(iCount == 0)
    {
        pLoggingConfig = &localLoggingConfig;

        sql_LoggingConfig_Create_Select_Query(pLoggingConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_LOGCONFIG_ERR_DB_ERROR;

            mysql_set_error_for_Logging_Config_Reqs(pLoggingConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);       
            return iReturn;
        }

        if((iReturn = mysql_LoggingConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {

            delete pRes;
            mysql_set_error_for_Logging_Config_Reqs(pLoggingConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        delete pRes;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}


DbStatus_e CMgrDbInterface::mysql_LoggingConfig_resultset_to_protoBuff(sql::ResultSet *pRes,LoggerConfResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: Logging Config Result Set= %d ",__FUNCTION__,pRes->rowsCount()); 
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_LOGCONFIG_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            ::LoggerConf* pLoggerConfig = resp->add_loggerconfig();

            if(!pRes->isNull("COMPONENT_NAME"))
                pLoggerConfig->set_componentname(pRes->getString("COMPONENT_NAME"));
            if(!pRes->isNull("LOG_LEVEL"))
                pLoggerConfig->set_level((LoggerConf_LogLevel)pRes->getUInt("LOG_LEVEL"));
            if(!pRes->isNull("LOG_CHANNEL"))
                pLoggerConfig->set_channel((LoggerConf_LogChannel)pRes->getUInt("LOG_CHANNEL"));

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


DbStatus_e CMgrDbInterface::mysql_Logging_Add_Config_Reqs(LoggerConfReq *req, LoggerConfResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    ::LoggerConf *pLoggingConfig;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    int iCount = req->loggerconfig_size();
    DLOG_DEBUG(" %s: loggerconfig_size = %d ",__FUNCTION__,iCount); 


    for(int i=0;i<iCount;i++)
    {

        pLoggingConfig = req->mutable_loggerconfig(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_LoggingConfig_Create_Check_Modifcation_Query(pLoggingConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = SET_LOGCONFIG_ERR_DB_ERROR;

            mysql_set_error_for_Logging_Config_Reqs(pLoggingConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_LoggingConfig_Create_Add_Query(pLoggingConfig,sStatement);  
        }
        else // MOD
        {

            delete pRes;
            DLOG_ERROR("Record Already Present");   
            mysql_set_error_for_Logging_Config_Reqs(pLoggingConfig,resp,SET_LOGCONFIG_ERR_COMPONENT_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return SET_LOGCONFIG_ERR_COMPONENT_ALREADY_PRESENT;
        }

        delete pRes;

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = SET_LOGCONFIG_ERR_DB_ERROR;

            mysql_set_error_for_Logging_Config_Reqs(pLoggingConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);       
            return iReturn;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_Logging_Mod_Config_Reqs(LoggerConfReq *req, LoggerConfResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    ::LoggerConf *pLoggingConfig;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;


    int iCount = req->loggerconfig_size();
    DLOG_DEBUG(" %s: loggerconfig_size = %d ",__FUNCTION__,iCount); 

    for(int i=0;i<iCount;i++)
    {
        pLoggingConfig = req->mutable_loggerconfig(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_LoggingConfig_Create_Check_Modifcation_Query(pLoggingConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_LOGCONFIG_ERR_DB_ERROR;

            mysql_set_error_for_Logging_Config_Reqs(pLoggingConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present");   
            mysql_set_error_for_Logging_Config_Reqs(pLoggingConfig,resp,MOD_LOGCONFIG_ERR_COMPONENT_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_LOGCONFIG_ERR_COMPONENT_NOT_PRESENT;
        }
        else // MOD
        {
            sql_LoggingConfig_Create_Mod_Query(pLoggingConfig,sStatement);  
        }

        delete pRes;

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_LOGCONFIG_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);       
            mysql_set_error_for_Logging_Config_Reqs(pLoggingConfig,resp,iReturn);
            return iReturn;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

