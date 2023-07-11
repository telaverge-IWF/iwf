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
void CMgrIwfDbInterface::mysql_set_error_for_IWFTimer_Config_Reqs(IwfTimerConfig *pIwfTimerConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());
    if(pIwfTimerConfig->has_timername())
    	err->add_variables(pIwfTimerConfig->timername());
    DLOG_NONE(" < %s ",__FUNCTION__);
}


DbStatus_e CMgrIwfDbInterface::Fill_IWFTimers_protobuff(IwfTimersConfig *pIwfTimersConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    int i=0;
    int ifData = 0;

    IwfTimerConfig LocalIwfTimerConfigObj;
    IwfTimerConfig *pIwfTimerConfig = NULL;

    int iCount = pIwfTimersConfig->iwftimersinfo_size();
    DLOG_INFO("pIwfTimersConfig->iwftimersinfo_size() = %d",iCount);
    do
    {
        if(iCount != 0)
            pIwfTimerConfig = pIwfTimersConfig->mutable_iwftimersinfo(i);
        else
            pIwfTimerConfig = &LocalIwfTimerConfigObj;

        sql_IWFTimer_Create_Select_Query(pIwfTimerConfig,sStatement);

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
                iReturn = GET_TIMER_ERR_DB_ERROR;

            mysql_set_error_for_IWFTimer_Config_Reqs(pIwfTimerConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
            if(pRes->rowsCount() != 0)
            {
                IwfTimersConfig *LocalIwfTimersConfig = resp->mutable_timersinfo();

                while(pRes->next())
                {
                    pIwfTimerConfig = LocalIwfTimersConfig->add_iwftimersinfo();

                    ifData = 1;
                    if(!pRes->isNull("IWF_TIMER_NAME"))
                        pIwfTimerConfig->set_timername(pRes->getString("IWF_TIMER_NAME"));
                    if(!pRes->isNull("IWF_TIMER_VALUE"))
                        pIwfTimerConfig->set_timervalue(pRes->getInt("IWF_TIMER_VALUE"));


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
        DLOG_DEBUG("There is no data in the table setting GET_TIMER_ERR_NO_DATA");
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(GET_TIMER_ERR_NO_DATA);
        err->set_errormsgkey(iwfErrorMap[GET_TIMER_ERR_NO_DATA]);
        DLOG_DEBUG("Error key is %s", (iwfErrorMap[GET_TIMER_ERR_NO_DATA]).c_str());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfTimer_Del_Config_Reqs(IwfTimersConfig *pIwfTimersConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfTimersConfig->iwftimersinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(DEL_TIMER_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_TIMER_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfTimerConfig *pIwfTimerConfig = pIwfTimersConfig->mutable_iwftimersinfo(i);
        sql_IWFTimer_Create_Check_Modifcation_Query(pIwfTimerConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_TIMER_ERR_DB_ERROR;

            mysql_set_error_for_IWFTimer_Config_Reqs(pIwfTimerConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Not Present");   
            mysql_set_error_for_IWFTimer_Config_Reqs(pIwfTimerConfig,resp,DEL_TIMER_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_TIMER_ERR_NOT_PRESENT;

        }
        else // MOD
        {
            sql_IWFTimer_Create_Delete_Query(pIwfTimerConfig,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_TIMER_ERR_DB_ERROR;

            mysql_set_error_for_IWFTimer_Config_Reqs(pIwfTimerConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}



DbStatus_e CMgrIwfDbInterface::mysql_IwfTimer_Mod_Config_Reqs(IwfTimersConfig *pIwfTimersConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfTimersConfig->iwftimersinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(MOD_TIMER_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[MOD_TIMER_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfTimerConfig *pIwfTimerConfig = pIwfTimersConfig->mutable_iwftimersinfo(i);
        sql_IWFTimer_Create_Check_Modifcation_Query(pIwfTimerConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_TIMER_ERR_DB_ERROR;

            mysql_set_error_for_IWFTimer_Config_Reqs(pIwfTimerConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Not Present");   
            mysql_set_error_for_IWFTimer_Config_Reqs(pIwfTimerConfig,resp,MOD_TIMER_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_TIMER_ERR_NOT_PRESENT;

        }
        else // MOD
        {
            sql_IWFTimer_Create_Mod_Query(pIwfTimerConfig,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_TIMER_ERR_DB_ERROR;

            mysql_set_error_for_IWFTimer_Config_Reqs(pIwfTimerConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}



DbStatus_e CMgrIwfDbInterface::mysql_IwfTimer_Add_Config_Reqs(IwfTimersConfig *pIwfTimersConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfTimersConfig->iwftimersinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(ADD_TIMER_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[ADD_TIMER_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfTimerConfig *pIwfTimerConfig = pIwfTimersConfig->mutable_iwftimersinfo(i);
        sql_IWFTimer_Create_Check_Modifcation_Query(pIwfTimerConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_TIMER_ERR_DB_ERROR;

            mysql_set_error_for_IWFTimer_Config_Reqs(pIwfTimerConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_IWFTimer_Create_Add_Query(pIwfTimerConfig,sStatement);
        }
        else // MOD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present");   
            mysql_set_error_for_IWFTimer_Config_Reqs(pIwfTimerConfig,resp,ADD_TIMER_ERR_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_TIMER_ERR_ALREADY_PRESENT;
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_TIMER_ERR_DB_ERROR;

            mysql_set_error_for_IWFTimer_Config_Reqs(pIwfTimerConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}



DbStatus_e CMgrIwfDbInterface::Fill_IWFTimer_protobuff(IwfTimerConfig *pIwfTimerConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFTimer_Create_Select_Query(pIwfTimerConfig,sStatement);

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
            iReturn = GET_TIMER_ERR_DB_ERROR;

        mysql_set_error_for_IWFTimer_Config_Reqs(pIwfTimerConfig,resp,iReturn);
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
                if(!pRes->isNull("IWF_TIMER_NAME"))
                    pIwfTimerConfig->set_timername(pRes->getString("IWF_TIMER_NAME"));
                if(!pRes->isNull("IWF_TIMER_VALUE"))
                   pIwfTimerConfig->set_timervalue(pRes->getInt("IWF_TIMER_VALUE"));
            }
        }
        else
        {
            delete pRes;
            return GET_TIMER_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::mysql_IWFTimers_Get_Config_Reqs(IwfTimersConfig *pIwfTimersConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    return Fill_IWFTimers_protobuff(pIwfTimersConfig,resp);

    DLOG_NONE(" < %s ",__FUNCTION__);
}
