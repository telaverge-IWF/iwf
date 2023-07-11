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
void CMgrIwfDbInterface::mysql_set_error_for_IWFUal_Config_Reqs(IwfSigtranUalManagerConfig *pIwfSigtranUalManagerConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

#if 0
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

#endif

DbStatus_e CMgrIwfDbInterface::mysql_IwfUal_Mod_Config_Reqs(IwfSigtranUalManagerConfig *pIwfSigtranUalManagerConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    sql_IWFSigtranUalManager_Create_Check_Modifcation_Query(pIwfSigtranUalManagerConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = MOD_UAL_ERR_DB_ERROR;

        mysql_set_error_for_IWFUal_Config_Reqs(pIwfSigtranUalManagerConfig,resp,iReturn);

        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        delete pRes;
        DLOG_ERROR("Record Not Present");   
        mysql_set_error_for_IWFUal_Config_Reqs(pIwfSigtranUalManagerConfig,resp,MOD_UAL_ERR_NOT_PRESENT);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return MOD_UAL_ERR_NOT_PRESENT;
    }
    else // MOD
    {
        sql_IWFSigtranUalManager_Create_Mod_Query(pIwfSigtranUalManagerConfig,sStatement);
    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);
        if(iReturn == IWF_DB_FAIL)
            iReturn = MOD_UAL_ERR_DB_ERROR;

        mysql_set_error_for_IWFUal_Config_Reqs(pIwfSigtranUalManagerConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}

DbStatus_e CMgrIwfDbInterface::mysql_IwfUal_Add_Config_Reqs(IwfSigtranUalManagerConfig *pIwfSigtranUalManagerConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    
    sql_IWFSigtranUalManager_Create_Check_Modifcation_Query(pIwfSigtranUalManagerConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = ADD_UAL_ERR_DB_ERROR;

        mysql_set_error_for_IWFUal_Config_Reqs(pIwfSigtranUalManagerConfig,resp,iReturn);

        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_IWFSigtranUalManager_Create_Add_Query(pIwfSigtranUalManagerConfig,sStatement);
    }
    else // MOD
    {
        delete pRes;
        DLOG_ERROR("Record Already Present");   
        mysql_set_error_for_IWFUal_Config_Reqs(pIwfSigtranUalManagerConfig,resp,ADD_UAL_ERR_ALREADY_PRESENT);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return ADD_UAL_ERR_ALREADY_PRESENT;
    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);
        if(iReturn == IWF_DB_FAIL)
            iReturn = ADD_UAL_ERR_DB_ERROR;

        mysql_set_error_for_IWFUal_Config_Reqs(pIwfSigtranUalManagerConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrIwfDbInterface::Fill_IWFUal_protobuff(IwfSigtranUalManagerConfig *pIwfSigtranUalManagerConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFSigtranUalManager_Create_Select_Query(pIwfSigtranUalManagerConfig,sStatement);

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
            iReturn = GET_UAL_ERR_DB_ERROR;

        mysql_set_error_for_IWFUal_Config_Reqs(pIwfSigtranUalManagerConfig,resp,iReturn);
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
                IwfSigtranUalManagerConfig *LocalIwfSigtranUalManagerConfig = resp->mutable_ualinfo();
                if(!pRes->isNull("ACK_TIMER"))
                    LocalIwfSigtranUalManagerConfig->set_acktimer(pRes->getInt("ACK_TIMER"));
                if(!pRes->isNull("SIGTRAN_MODE"))
                    LocalIwfSigtranUalManagerConfig->set_sigtranmode(pRes->getString("SIGTRAN_MODE"));
            }
        }
        else
        {
            delete pRes;
            mysql_set_error_for_IWFUal_Config_Reqs(pIwfSigtranUalManagerConfig,resp,GET_UAL_ERR_NO_DATA);
            return GET_UAL_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::mysql_IwfUal_Get_Config_Reqs(IwfSigtranUalManagerConfig *pIwfSigtranUalManagerConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    return Fill_IWFUal_protobuff(pIwfSigtranUalManagerConfig,resp);

    DLOG_NONE(" < %s ",__FUNCTION__);
}
