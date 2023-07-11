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


#include <CMgrDbInterface.h>

using namespace std;
extern std::map<int,std::string> errorMap;

void CMgrDbInterface::mysql_set_error_for_LocalHost_Config_Reqs(LocalHostConfig *pLocalHostConfig,DRECfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pLocalHostConfig->has_localhostname())
        err->add_variables(pLocalHostConfig->localhostname());

    if(pLocalHostConfig->has_realmname())
        err->add_variables(pLocalHostConfig->realmname());

    DLOG_NONE(" < %s ",__FUNCTION__);
}


DbStatus_e CMgrDbInterface::mysql_LocalHost_Get_Config_Reqs(LocalHostConfig *pLocalHostConfig,DRECfgResp *resp)
{

    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    sql_LocalHostConfig_Create_Select_Query(pLocalHostConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)        
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn =  GET_HOST_ERR_DB_ERROR;

        mysql_set_error_for_LocalHost_Config_Reqs(pLocalHostConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);       
        return iReturn;
    }

    if((iReturn = mysql_LocalHostConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
    {

        delete pRes;
        mysql_set_error_for_LocalHost_Config_Reqs(pLocalHostConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }


    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_LocalHostConfig_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);


    try
    {       
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());   
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);       
            return GET_HOST_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            ::LocalHostConfig* localhostobj = resp->mutable_localhost();
            localhostobj->set_localhostname(pRes->getString("HostName"));
            localhostobj->set_realmname(pRes->getString("RealmName"));


            localhostobj->set_hostipaddr(pRes->getString("IPAddress"));
            localhostobj->set_port(pRes->getInt("Port"));

            if(pRes->getInt("TransportType") == 1)
                localhostobj->set_transporttype("TCP");
            else if(pRes->getInt("TransportType") == 2)
                localhostobj->set_transporttype("SCTP");
            else if(pRes->getInt("TransportType") == 3)
                localhostobj->set_transporttype("TLS");

            localhostobj->set_authsessionlifetime(pRes->getInt64("AuthLifeTime"));  
            localhostobj->set_authsessiongraceperiod(pRes->getInt64("AuthGraceTime"));
            localhostobj->set_authsessiontimeout(pRes->getInt64("AuthTimeOut"));

            localhostobj->set_acctsessioninteriminterval(pRes->getInt64("AcctInterim"));
            localhostobj->set_acctsessiontimeout(pRes->getInt64("AcctTimeOut"));    
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

DbStatus_e CMgrDbInterface::mysql_LocalHost_Add_Config_Reqs(LocalHostConfig *pLocalHostConfig,DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    LocalHostConfig lLocalHostConfig;

    sql_LocalHostConfig_Create_Check_Modifcation_Query(&lLocalHostConfig,sStatement);       

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)        
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_HOST_ERR_DB_ERROR;

        mysql_set_error_for_LocalHost_Config_Reqs(pLocalHostConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);       
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_LocalHostConfig_Create_Add_Query(pLocalHostConfig,sStatement);
    }
    else // MOD
    {

        delete pRes;
        DLOG_ERROR("Record Already Present");   
        mysql_set_error_for_LocalHost_Config_Reqs(pLocalHostConfig,resp,SET_HOST_ERR_HOST_ALREADY_PRESENT);
        DLOG_NONE(" < %s ",__FUNCTION__);       
        return SET_HOST_ERR_HOST_ALREADY_PRESENT;
    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);       

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_HOST_ERR_DB_ERROR;

        mysql_set_error_for_LocalHost_Config_Reqs(pLocalHostConfig,resp,iReturn);
        return iReturn;
    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

void CMgrDbInterface::copy_LocalHostConfig(DRECfgResp *resp,LocalHostConfig *pLocalHostConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(!resp->has_localhost())
    {
        ::LocalHostConfig* plHostConfig = resp->mutable_localhost();
        plHostConfig->CopyFrom(*pLocalHostConfig);
    }
    else
    {
        DLOG_DEBUG("Already localhost value is set in the response structure");
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return;
}

DbStatus_e CMgrDbInterface::mysql_LocalHost_Delete_Config_Reqs(LocalHostConfig *req,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_LocalHostConfig_Create_Delete_Query(req,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = DEL_HOST_ERR_DB_ERROR;

        mysql_set_error_for_LocalHost_Config_Reqs(req,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::copy_LocalHostConfig(LocalHostConfig *req,DRECfgResp  *resp)
{
    DLOG_NONE(" < %s ",__FUNCTION__);

    if(resp->has_localhost())
    {
        ::LocalHostConfig *plHostConfig = resp->mutable_localhost();

        plHostConfig->MergeFrom(*req);
        req->CopyFrom(*plHostConfig);
    }
    else
    {
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

