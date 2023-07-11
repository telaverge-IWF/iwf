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


void CMgrIwfDbInterface::mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(IwfCapToRoConfig *pIwfCapToRoConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_CapRoIdpConfig_Config_Reqs(CapRoIdpConfig *pCapRoIdpConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_CapRoIdpSmsConfig_Config_Reqs(CapRoIdpSmsConfig *pCapRoIdpSmsConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_ExtBearerservice_Config_Reqs(CapRoIdpConfig *pCapRoIdpConfig,IWFCfgResp *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_ExtTeleservice_Config_Reqs(CapRoIdpConfig *pCapRoIdpConfig,IWFCfgResp *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}



DbStatus_e CMgrIwfDbInterface::Fill_IWFCapRoConfig_protobuff(IwfCapToRoConfig *pIwfCapToRoConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFCapRoConfig_Create_Select_Query(pIwfCapToRoConfig,sStatement);

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
            iReturn = GET_CAPROCONFIG_ERR_DB_ERROR;

        mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
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
                {
                    IwfTranslatorConfig *pIwfTranslatorConfig = pIwfCapToRoConfig -> mutable_translatorinfo();
                    pIwfTranslatorConfig->set_translatorid(pRes->getInt("IWF_TRANSLATOR_ID"));
                }
                if(!pRes->isNull("IWF_CAPRO_CONFIG_ID"))
                    pIwfCapToRoConfig->set_captoroconfigid(pRes->getInt("IWF_CAPRO_CONFIG_ID"));
            }
        }
        else
        {
            delete pRes;
            return GET_CAPROCONFIG_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::Fill_CapRoIdpConfig_protobuff(IwfCapToRoConfig *pIwfCapToRoConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_CapRoIdpConfig_Create_Select_Query(pIwfCapToRoConfig,sStatement);

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
            iReturn = GET_CAPROIDPCONFIG_ERR_DB_ERROR;

        mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
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
                CapRoIdpConfig *pCapRoIdpConfig = NULL;
                pCapRoIdpConfig = pIwfCapToRoConfig-> mutable_caproidpinfo();
                if(!pRes->isNull("CAPRO_CONFIG_ID"))
                    pIwfCapToRoConfig->set_captoroconfigid(pRes->getInt("CAPRO_CONFIG_ID"));
                if(!pRes->isNull("CAPRO_IDP_CONFIG_ID"))
                    pCapRoIdpConfig->set_caproidpconfigid(pRes->getInt("CAPRO_IDP_CONFIG_ID"));
                if(!pRes->isNull("NODE_FUNCTIONALITY"))
                    pCapRoIdpConfig->set_nodefunctionality(pRes->getInt("NODE_FUNCTIONALITY"));
                if(!pRes->isNull("SIP_METHOD"))
                    pCapRoIdpConfig->set_sipmethod(pRes->getString("SIP_METHOD"));
                if(!pRes->isNull("ORIGINATING_TOI"))
                    pCapRoIdpConfig->set_orignatingtoi(pRes->getString("ORIGINATING_TOI"));
                if(!pRes->isNull("TERMINATING_TOI"))
                    pCapRoIdpConfig->set_terminatingtoi(pRes->getString("TERMINATING_TOI"));
                if(!pRes->isNull("SERVICE_CONTEXT_ID"))
                    pCapRoIdpConfig->set_servicecontextid(pRes->getString("SERVICE_CONTEXT_ID"));
                if(!pRes->isNull("CAUSE_CODE"))
                    pCapRoIdpConfig->set_causecode(pRes->getString("CAUSE_CODE"));
                if(!pRes->isNull("MSC_SERVICE_SPECIFIC_TYPE"))
                    pCapRoIdpConfig->set_mscservicespecfictype(pRes->getInt("MSC_SERVICE_SPECIFIC_TYPE"));
                if(!pRes->isNull("GMSC_SERVICE_SPECIFIC_TYPE"))
                    pCapRoIdpConfig->set_gmscservicespecifictype(pRes->getInt("GMSC_SERVICE_SPECIFIC_TYPE"));
                if(!pRes->isNull("CPC_SERVICE_SPECIFIC_TYPE"))
                    pCapRoIdpConfig->set_cpcservicespecifictype(pRes->getInt("CPC_SERVICE_SPECIFIC_TYPE"));
                if(!pRes->isNull("MULTIPLE_SERVICES_INDICATOR"))
                    pCapRoIdpConfig->set_multipleserviceindicator(pRes->getInt("MULTIPLE_SERVICES_INDICATOR"));

            }
        }
        else
        {
            delete pRes;
            return GET_CAPROIDPCONFIG_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::Fill_CapRoIdpSmsConfig_protobuff(IwfCapToRoConfig *pIwfCapToRoConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_CapRoIdpSmsConfig_Create_Select_Query(pIwfCapToRoConfig,sStatement);

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
            iReturn = GET_CAPROIDPSMSCONFIG_ERR_DB_ERROR;

        mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
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
                CapRoIdpSmsConfig *pCapRoIdpSmsConfig = NULL;
                pCapRoIdpSmsConfig = pIwfCapToRoConfig->mutable_caproidpsmsinfo();
                if(!pRes->isNull("CAPRO_IDPSMS_CONFIG_ID"))
                    pCapRoIdpSmsConfig->set_caproidpsmsconfigid(pRes->getInt("CAPRO_IDPSMS_CONFIG_ID"));
                if(!pRes->isNull("SMS_NODE"))
                    pCapRoIdpSmsConfig->set_smsnode(pRes->getInt("SMS_NODE"));
                if(!pRes->isNull("CLIENT_ADDRESS"))
                    pCapRoIdpSmsConfig->set_clientaddress(pRes->getString("CLIENT_ADDRESS"));
                if(!pRes->isNull("ORIGINATOR_SCCP_ADDRESS"))
                    pCapRoIdpSmsConfig->set_originatorsccpaddress(pRes->getString("ORIGINATOR_SCCP_ADDRESS"));
                if(!pRes->isNull("REPLY_PATH_REQUESTED"))
                    pCapRoIdpSmsConfig->set_replypathrequested(pRes->getInt("REPLY_PATH_REQUESTED"));
                if(!pRes->isNull("MSC_SERVICE_SPECIFIC_TYPE"))
                    pCapRoIdpSmsConfig->set_mscservicespecifictype(pRes->getInt("MSC_SERVICE_SPECIFIC_TYPE"));
                if(!pRes->isNull("SGSN_SERVICE_SPECIFIC_TYPE"))
                    pCapRoIdpSmsConfig->set_sgsnservicespecifictype(pRes->getInt("SGSN_SERVICE_SPECIFIC_TYPE"));
                if(!pRes->isNull("SERVICE_CONTEXT_ID"))
                    pCapRoIdpSmsConfig->set_servicecontextid(pRes->getString("SERVICE_CONTEXT_ID"));
            }
        }
        else
        {
            delete pRes;
            return GET_CAPROIDPSMSCONFIG_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::Fill_ExtBearerserviceToServiceIdMap_Config_protobuff(CapRoIdpConfig *pCapRoIdpConfig,IWFCfgResp *resp,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_ExtBearerserviceToServiceIdMap_Create_Select_Query(pCapRoIdpConfig,sStatement,iIndex);

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
            iReturn = GET_CAPROIDPCONFIG_ERR_DB_ERROR;

        mysql_set_error_for_ExtBearerservice_Config_Reqs(pCapRoIdpConfig,resp,iReturn,iIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    ExtBearerServiceConfig *pExtBearerServiceConfig = NULL;

    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            while(pRes->next())
            {
                if(pCapRoIdpConfig->extbearerinfo_size() > iIndex && iIndex > -1)
                {
                    pExtBearerServiceConfig = pCapRoIdpConfig-> mutable_extbearerinfo(iIndex);
                }
                else
                {
                    pExtBearerServiceConfig = pCapRoIdpConfig-> add_extbearerinfo();

                }
                if(!pRes->isNull("CAPRO_IDP_CONFIG_ID"))
                    pCapRoIdpConfig->set_caproidpconfigid(pRes->getInt("CAPRO_IDP_CONFIG_ID"));
                if(!pRes->isNull("EXT_BEARERSERVICE"))
                    pExtBearerServiceConfig->set_extbearerservicecode(pRes->getInt("EXT_BEARERSERVICE"));
                if(!pRes->isNull("SERVICE_ID"))
                    pExtBearerServiceConfig->set_serviceid(pRes->getInt("SERVICE_ID"));
            }
        }
        else
        {
            delete pRes;
            return GET_BEARERSERVICE_TO_SERVICE_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::Fill_ExtTeleserviceToServiceIdMap_Config_protobuff(CapRoIdpConfig *pCapRoIdpConfig,IWFCfgResp *resp,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_ExtTeleserviceToServiceIdMap_Create_Select_Query(pCapRoIdpConfig,sStatement,iIndex);

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
            iReturn = GET_CAPROIDPCONFIG_ERR_DB_ERROR;

        mysql_set_error_for_ExtTeleservice_Config_Reqs(pCapRoIdpConfig,resp,iReturn,iIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    ExtTeleServiceConfig *pExtTeleServiceConfigReq = NULL;
    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            while(pRes->next())
            {
                if(pCapRoIdpConfig->extteleinfo_size() > iIndex && iIndex > -1)
                {
                    pExtTeleServiceConfigReq = pCapRoIdpConfig-> mutable_extteleinfo(iIndex);
                }
                else
                {
                    pExtTeleServiceConfigReq = pCapRoIdpConfig-> add_extteleinfo();
                }
                if(!pRes->isNull("CAPRO_IDP_CONFIG_ID"))
                    pCapRoIdpConfig->set_caproidpconfigid(pRes->getInt("CAPRO_IDP_CONFIG_ID"));
                if(!pRes->isNull("EXT_TELESERVICE"))
                    pExtTeleServiceConfigReq->set_extteleservicecode(pRes->getInt("EXT_TELESERVICE"));
                if(!pRes->isNull("SERVICE_ID"))
                    pExtTeleServiceConfigReq->set_serviceid(pRes->getInt("SERVICE_ID"));
            }
        }
        else
        {
            delete pRes;
            return GET_TELESERVICE_TO_SERVICE_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::mysql_IWFCapRo_Add_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0}; 
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    ::IwfCapToRoConfig *pIwfCapToRoConfig = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    
    if(req->has_captoroinfo())
    {
        pIwfCapToRoConfig = req->mutable_captoroinfo();
        if(pIwfCapToRoConfig->has_translatorinfo())
        {
            ::IwfTranslatorConfig *pIwfTranslatorConfig = pIwfCapToRoConfig->mutable_translatorinfo();

            sql_IWFTranslator_Create_Check_Modifcation_Query(pIwfTranslatorConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_CAPROCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) 
            {
                delete pRes;
                DLOG_ERROR("Record Not Present");
                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,ADD_CAPROCONFIG_ERR_TRANSLATOR_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_CAPROCONFIG_ERR_TRANSLATOR_NOT_PRESENT;
            }
            delete pRes; 
            sql_IWFCapRoConfig_Create_Check_Modifcation_Query(pIwfCapToRoConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_CAPROCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            
            DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
            if(pRes->rowsCount() == 0) 
            {
                sql_IWFCapRoConfig_Create_Add_Query(pIwfCapToRoConfig,sStatement);
            }

            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_CAPROCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            delete pRes;
            if(pIwfCapToRoConfig->has_caproidpinfo() || pIwfCapToRoConfig->has_caproidpsmsinfo())
            {
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                if(pIwfCapToRoConfig->has_caproidpsmsinfo()) //If CAPRo-IDPSMS info is present
                {
                    ::CapRoIdpSmsConfig *pCapRoIdpSmsConfig = pIwfCapToRoConfig->mutable_caproidpsmsinfo();
                    
                    sql_CapRoIdpSmsConfig_Create_Check_Modifcation_Query(pIwfCapToRoConfig,sStatement);

                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                    {   
                        if(pRes != NULL)            
                        {   
                            delete pRes;
                        }   

                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == DRE_DB_FAIL)
                            iReturn = ADD_CAPROIDPSMSCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_CapRoIdpSmsConfig_Config_Reqs(pCapRoIdpSmsConfig,resp,iReturn);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);           
                        return iReturn;
                    }

                    if(pRes->rowsCount() == 0) // ADD
                    {   
                        sql_CapRoIdpSmsConfig_Create_Add_Query(pIwfCapToRoConfig,sStatement);
                    }
                    else // MOD
                    {
                        delete pRes;
                        DLOG_ERROR("Record Already Present");
                        mysql_set_error_for_CapRoIdpSmsConfig_Config_Reqs(pCapRoIdpSmsConfig,resp,ADD_CAPROIDPSMSCONFIG_ERR_CONFIG_ALREADY_PRESENT);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return ADD_CAPROIDPSMSCONFIG_ERR_CONFIG_ALREADY_PRESENT;
                    }
                    delete pRes; 
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);
                        DLOG_NONE(" < %s ",__FUNCTION__);

                        if(iReturn == DRE_DB_FAIL)
                            iReturn = ADD_CAPROIDPSMSCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_CapRoIdpSmsConfig_Config_Reqs(pCapRoIdpSmsConfig,resp,iReturn);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);           
                        return iReturn;
                    }

                }
                if(pIwfCapToRoConfig->has_caproidpinfo()) //If CAPRo-IDP info is present
                {
                    ::CapRoIdpConfig *pCapRoIdpConfig = pIwfCapToRoConfig->mutable_caproidpinfo();
                    sql_CapRoIdpConfig_Create_Check_Modifcation_Query(pIwfCapToRoConfig,sStatement);

                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                    {   
                        if(pRes != NULL)            
                        {   
                            delete pRes;
                        }   

                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == DRE_DB_FAIL)
                            iReturn = ADD_CAPROIDPCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_CapRoIdpConfig_Config_Reqs(pCapRoIdpConfig,resp,iReturn);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);           
                        return iReturn;
                    }
                    memset(sStatement,0,MAX_STATEMENT_SIZE);
                    if(pRes->rowsCount() == 0) // ADD
                    {   
                        sql_CapRoIdpConfig_Create_Add_Query(pIwfCapToRoConfig,sStatement);
                    }
                    else // MOD
                    {
                        delete pRes;
                        DLOG_ERROR("Record Already Present");
                        mysql_set_error_for_CapRoIdpConfig_Config_Reqs(pCapRoIdpConfig,resp,ADD_CAPROIDPCONFIG_ERR_CONFIG_ALREADY_PRESENT);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return ADD_CAPROIDPCONFIG_ERR_CONFIG_ALREADY_PRESENT;
                    }
                    delete pRes;
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);
                        DLOG_NONE(" < %s ",__FUNCTION__);

                        if(iReturn == DRE_DB_FAIL)
                            iReturn = ADD_CAPROIDPCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_CapRoIdpConfig_Config_Reqs(pCapRoIdpConfig,resp,iReturn);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);           
                        return iReturn;
                    }
                    
                    if(pCapRoIdpConfig->extteleinfo_size() > 0 || pCapRoIdpConfig->extbearerinfo_size() > 0)
                    {
                        memset(sStatement,0,MAX_STATEMENT_SIZE);
                        if(pCapRoIdpConfig->extteleinfo_size()) // If EXT_TELE_INFO is present
                        {
                            unsigned int ext_tele_size = pCapRoIdpConfig->extteleinfo_size();
                            for(unsigned int iIndex = 0; iIndex < ext_tele_size ; iIndex++)
                            {
                                memset(sStatement,0,MAX_STATEMENT_SIZE);
                                sql_ExtTeleserviceToServiceIdMap_Create_Check_Modifcation_Query(pCapRoIdpConfig,sStatement,iIndex);

                                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                {   
                                    if(pRes != NULL)            
                                    {   
                                        delete pRes;
                                    }   

                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = ADD_CAPROIDPEXTTELESERVICECONFIG_ERR_DB_ERROR;

                                    mysql_set_error_for_ExtTeleservice_Config_Reqs(pCapRoIdpConfig,resp,iReturn,iIndex);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);           
                                    return iReturn;
                                }
                                memset(sStatement,0,MAX_STATEMENT_SIZE);

                                if(pRes->rowsCount() == 0) // ADD
                                {   
                                    sql_ExtTeleserviceToServiceIdMap_Create_Add_Query(pCapRoIdpConfig,sStatement,iIndex);
                                }
                                else // MOD
                                {
                                    delete pRes;
                                    DLOG_ERROR("Record Already Present");
                                    mysql_set_error_for_ExtTeleservice_Config_Reqs(pCapRoIdpConfig,resp,ADD_CAPROIDPEXTTELESERVICECONFIG_ERR_CONFIG_ALREADY_PRESENT,iIndex);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return ADD_CAPROIDPEXTTELESERVICECONFIG_ERR_CONFIG_ALREADY_PRESENT;
                                }
                                delete pRes;
                                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                {
                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                                    DLOG_NONE(" < %s ",__FUNCTION__);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = ADD_CAPROIDPEXTTELESERVICECONFIG_ERR_DB_ERROR;

                                    mysql_set_error_for_ExtTeleservice_Config_Reqs(pCapRoIdpConfig,resp,iReturn,iIndex);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);           
                                    return iReturn;
                                }

                            }
                        }

                        if(pCapRoIdpConfig->extbearerinfo_size()) // If EXT_BEARER_INFO is present
                        {
                            unsigned int ext_bearer_size = pCapRoIdpConfig->extbearerinfo_size();
                            for(unsigned int iIndex = 0; iIndex < ext_bearer_size ; iIndex++)
                            {
                                memset(sStatement,0,MAX_STATEMENT_SIZE);
                                sql_ExtBearerserviceToServiceIdMap_Create_Check_Modifcation_Query(pCapRoIdpConfig,sStatement,iIndex);

                                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                {   
                                    if(pRes != NULL)            
                                    {   
                                        delete pRes;
                                    }   

                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = ADD_CAPROIDPEXTBEARERSERVICECONFIG_ERR_DB_ERROR;

                                    mysql_set_error_for_ExtBearerservice_Config_Reqs(pCapRoIdpConfig,resp,iReturn,iIndex);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);           
                                    return iReturn;
                                }
                                memset(sStatement,0,MAX_STATEMENT_SIZE);

                                if(pRes->rowsCount() == 0) // ADD
                                {   
                                    sql_ExtBearerserviceToServiceIdMap_Create_Add_Query(pCapRoIdpConfig,sStatement,iIndex);
                                }
                                else // MOD
                                {
                                    delete pRes;
                                    DLOG_ERROR("Record Already Present");
                                    mysql_set_error_for_ExtBearerservice_Config_Reqs(pCapRoIdpConfig,resp,ADD_CAPROIDPEXTBEARERSERVICECONFIG_ERR_CONFIG_ALREADY_PRESENT,iIndex);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return ADD_CAPROIDPEXTBEARERSERVICECONFIG_ERR_CONFIG_ALREADY_PRESENT;
                                }
                                delete pRes;
                                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                {
                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                                    DLOG_NONE(" < %s ",__FUNCTION__);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = ADD_CAPROIDPEXTBEARERSERVICECONFIG_ERR_DB_ERROR;

                                    mysql_set_error_for_ExtBearerservice_Config_Reqs(pCapRoIdpConfig,resp,iReturn,iIndex);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return iReturn;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                iReturn = ADD_CAPROCONFIG_ERR_DATA_NOT_PRESENT;
                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
        else
        {
            iReturn = ADD_CAPROCONFIG_ERR_DATA_NOT_PRESENT;
            mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }
    else
    {
        iReturn = ADD_CAPROCONFIG_ERR_DATA_NOT_PRESENT;
        mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFCapRo_Get_Config_Reqs(IwfTranslationDataConfig *pIwfTranslationDataConfig, IWFCfgResp *resp)
{
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    IwfCapToRoConfig LocalIwfCapToRoConfig;

    if((iReturn = Fill_IWFCapRoConfig_protobuff(&LocalIwfCapToRoConfig, resp)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_CAPROCONFIG_ERR_DB_ERROR;
        mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(&LocalIwfCapToRoConfig,resp,iReturn);
    }
    
    if((iReturn = Fill_CapRoIdpConfig_protobuff(&LocalIwfCapToRoConfig, resp)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_CAPROIDPCONFIG_ERR_DB_ERROR;
        mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(&LocalIwfCapToRoConfig,resp,iReturn);
    }
    
    CapRoIdpConfig *LocalCapRoIdpConfig = LocalIwfCapToRoConfig.mutable_caproidpinfo();
    Fill_ExtBearerserviceToServiceIdMap_Config_protobuff(LocalCapRoIdpConfig,resp,-1);
    Fill_ExtTeleserviceToServiceIdMap_Config_protobuff(LocalCapRoIdpConfig,resp,-1);
    
    if((iReturn = Fill_CapRoIdpSmsConfig_protobuff(&LocalIwfCapToRoConfig, resp)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_CAPROIDPSMSCONFIG_ERR_DB_ERROR;
        mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(&LocalIwfCapToRoConfig,resp,iReturn);
    }

    IwfTranslationDataConfig *pLocalIwfTranslationDataConfig = resp->mutable_translationdatainfo();
    IwfCapToRoConfig *pIwfCapToRoConfig = pLocalIwfTranslationDataConfig->mutable_captoroinfo();

    pIwfCapToRoConfig->CopyFrom(LocalIwfCapToRoConfig);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFCapRoIdp_Get_Config_Reqs(IwfTranslationDataConfig *pIwfTranslationDataConfig, IWFCfgResp *resp)
{
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    IwfCapToRoConfig LocalIwfCapToRoConfig;

    if((iReturn = Fill_IWFCapRoConfig_protobuff(&LocalIwfCapToRoConfig, resp)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_CAPROCONFIG_ERR_DB_ERROR;
        mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(&LocalIwfCapToRoConfig,resp,iReturn);
    }
    
    if((iReturn = Fill_CapRoIdpConfig_protobuff(&LocalIwfCapToRoConfig, resp)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_CAPROIDPCONFIG_ERR_DB_ERROR;
        mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(&LocalIwfCapToRoConfig,resp,iReturn);
    }
    
    CapRoIdpConfig *LocalCapRoIdpConfig = LocalIwfCapToRoConfig.mutable_caproidpinfo();
    Fill_ExtBearerserviceToServiceIdMap_Config_protobuff(LocalCapRoIdpConfig,resp,-1);
    Fill_ExtTeleserviceToServiceIdMap_Config_protobuff(LocalCapRoIdpConfig,resp,-1);
    
    IwfTranslationDataConfig *pLocalIwfTranslationDataConfig = resp->mutable_translationdatainfo();
    IwfCapToRoConfig *pIwfCapToRoConfig = pLocalIwfTranslationDataConfig->mutable_captoroinfo();

    pIwfCapToRoConfig->CopyFrom(LocalIwfCapToRoConfig);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFCapRoIdpSms_Get_Config_Reqs(IwfTranslationDataConfig *pIwfTranslationDataConfig, IWFCfgResp *resp)
{
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    IwfCapToRoConfig LocalIwfCapToRoConfig;

    if((iReturn = Fill_IWFCapRoConfig_protobuff(&LocalIwfCapToRoConfig, resp)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_CAPROCONFIG_ERR_DB_ERROR;
        mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(&LocalIwfCapToRoConfig,resp,iReturn);
    }
    
    if((iReturn = Fill_CapRoIdpSmsConfig_protobuff(&LocalIwfCapToRoConfig, resp)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_CAPROIDPSMSCONFIG_ERR_DB_ERROR;
        mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(&LocalIwfCapToRoConfig,resp,iReturn);
    }

    IwfTranslationDataConfig *pLocalIwfTranslationDataConfig = resp->mutable_translationdatainfo();
    IwfCapToRoConfig *pIwfCapToRoConfig = pLocalIwfTranslationDataConfig->mutable_captoroinfo();

    pIwfCapToRoConfig->CopyFrom(LocalIwfCapToRoConfig);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFCapRo_Mod_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0}; 
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    ::IwfCapToRoConfig *pIwfCapToRoConfig = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    
    if(req->has_captoroinfo())
    {
        pIwfCapToRoConfig = req->mutable_captoroinfo();
        if(pIwfCapToRoConfig->has_translatorinfo())
        {
            ::IwfTranslatorConfig *pIwfTranslatorConfig = pIwfCapToRoConfig->mutable_translatorinfo();

            sql_IWFTranslator_Create_Check_Modifcation_Query(pIwfTranslatorConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_CAPROCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) 
            {
                delete pRes;
                DLOG_ERROR("Record Not Present");
                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,MOD_CAPROCONFIG_ERR_TRANSLATOR_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return MOD_CAPROCONFIG_ERR_TRANSLATOR_NOT_PRESENT;
            }
            delete pRes; 
            sql_IWFCapRoConfig_Create_Check_Modifcation_Query(pIwfCapToRoConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_CAPROCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) 
            {
				delete pRes;
                DLOG_ERROR("Record Not Present");
                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,MOD_CAPROCONFIG_ERR_CONFIG_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return MOD_CAPROCONFIG_ERR_CONFIG_NOT_PRESENT;
            }
            delete pRes;
            if(pIwfCapToRoConfig->has_caproidpinfo() || pIwfCapToRoConfig->has_caproidpsmsinfo())
            {
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                if(pIwfCapToRoConfig->has_caproidpsmsinfo()) //If CAPRo-IDPSMS info is present
                {
                    ::CapRoIdpSmsConfig *pCapRoIdpSmsConfig = pIwfCapToRoConfig->mutable_caproidpsmsinfo();
                    if((sql_CapRoIdpSmsConfig_Check_All_Invalid(pIwfCapToRoConfig)) == IWF_DB_FAIL)
					{
						sql_CapRoIdpSmsConfig_Create_Check_Modifcation_Query(pIwfCapToRoConfig,sStatement);

						if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
						{   
							if(pRes != NULL)            
							{   
								delete pRes;
							}   

							DLOG_ERROR("Query Execution Failed: %s",sStatement);

							if(iReturn == DRE_DB_FAIL)
								iReturn = MOD_CAPROIDPSMSCONFIG_ERR_DB_ERROR;

							mysql_set_error_for_CapRoIdpSmsConfig_Config_Reqs(pCapRoIdpSmsConfig,resp,iReturn);
                            DLOG_DEBUG("iReturn = %d",iReturn);
							DLOG_NONE(" < %s ",__FUNCTION__);           
							return iReturn;
						}
						memset(sStatement,0,MAX_STATEMENT_SIZE);

						if(pRes->rowsCount() != 0) // MODIFY
						{   
							sql_CapRoIdpSmsConfig_Create_Mod_Query(pIwfCapToRoConfig,sStatement);
						}
						else // ADD
						{
							delete pRes;
							DLOG_ERROR("Record Not Present");
							mysql_set_error_for_CapRoIdpSmsConfig_Config_Reqs(pCapRoIdpSmsConfig,resp,MOD_CAPROIDPSMSCONFIG_ERR_CONFIG_NOT_PRESENT);
							DLOG_NONE(" < %s ",__FUNCTION__);
							return MOD_CAPROIDPSMSCONFIG_ERR_CONFIG_NOT_PRESENT;
						}
                        delete pRes;        
						if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
						{
							DLOG_ERROR("Query Execution Failed: %s",sStatement);
							DLOG_NONE(" < %s ",__FUNCTION__);

							if(iReturn == DRE_DB_FAIL)
								iReturn = MOD_CAPROIDPSMSCONFIG_ERR_DB_ERROR;

							mysql_set_error_for_CapRoIdpSmsConfig_Config_Reqs(pCapRoIdpSmsConfig,resp,iReturn);
                            DLOG_DEBUG("iReturn = %d",iReturn);
							DLOG_NONE(" < %s ",__FUNCTION__);
							return iReturn;
						}
					}
                }
                if(pIwfCapToRoConfig->has_caproidpinfo()) //If CAPRo-IDP info is present
                {
                    ::CapRoIdpConfig *pCapRoIdpConfig = pIwfCapToRoConfig->mutable_caproidpinfo();
					if((sql_CapRoIdpConfig_Check_All_Invalid(pIwfCapToRoConfig)) == IWF_DB_FAIL)
					{
						sql_CapRoIdpConfig_Create_Check_Modifcation_Query(pIwfCapToRoConfig,sStatement);

						if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
						{   
							if(pRes != NULL)            
							{   
								delete pRes;
							}   

							DLOG_ERROR("Query Execution Failed: %s",sStatement);

							if(iReturn == DRE_DB_FAIL)
								iReturn = MOD_CAPROIDPCONFIG_ERR_DB_ERROR;

							mysql_set_error_for_CapRoIdpConfig_Config_Reqs(pCapRoIdpConfig,resp,iReturn);
                            DLOG_DEBUG("iReturn = %d",iReturn);
							DLOG_NONE(" < %s ",__FUNCTION__);           
							return iReturn;
						}
						memset(sStatement,0,MAX_STATEMENT_SIZE);

						if(pRes->rowsCount() != 0) // MODIFY
						{   
							sql_CapRoIdpConfig_Create_Mod_Query(pIwfCapToRoConfig,sStatement);
						}
						else // ADD
						{
							delete pRes;
							DLOG_ERROR("Record Not Present");
							mysql_set_error_for_CapRoIdpConfig_Config_Reqs(pCapRoIdpConfig,resp,ADD_CAPROIDPCONFIG_ERR_CONFIG_NOT_PRESENT);
							DLOG_NONE(" < %s ",__FUNCTION__);
							return MOD_CAPROIDPCONFIG_ERR_CONFIG_NOT_PRESENT;
						}
                        delete pRes; 
						if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
						{
							DLOG_ERROR("Query Execution Failed: %s",sStatement);
							DLOG_NONE(" < %s ",__FUNCTION__);

							if(iReturn == DRE_DB_FAIL)
								iReturn = MOD_CAPROIDPCONFIG_ERR_DB_ERROR;

							mysql_set_error_for_CapRoIdpConfig_Config_Reqs(pCapRoIdpConfig,resp,iReturn);
                            DLOG_DEBUG("iReturn = %d",iReturn);
							DLOG_NONE(" < %s ",__FUNCTION__);           
							return iReturn;
						}
					}
					
                    if(pCapRoIdpConfig->extteleinfo_size() > 0 || pCapRoIdpConfig->extbearerinfo_size() > 0)
                    {
                        memset(sStatement,0,MAX_STATEMENT_SIZE);
                        if(pCapRoIdpConfig->extteleinfo_size()) // If EXT_TELE_INFO is present
                        {
                            unsigned int ext_tele_size = pCapRoIdpConfig->extteleinfo_size();
                            for(unsigned int iIndex = 0; iIndex < ext_tele_size ; iIndex++)
                            {
                                memset(sStatement,0,MAX_STATEMENT_SIZE);
                                sql_ExtTeleserviceToServiceIdMap_Create_Check_Modifcation_Query(pCapRoIdpConfig,sStatement,iIndex);

                                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                {   
                                    if(pRes != NULL)            
                                    {   
                                        delete pRes;
                                    }   

                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = MOD_CAPROIDPEXTTELESERVICECONFIG_ERR_DB_ERROR;

                                    mysql_set_error_for_ExtTeleservice_Config_Reqs(pCapRoIdpConfig,resp,iReturn,iIndex);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);           
                                    return iReturn;
                                }
                                memset(sStatement,0,MAX_STATEMENT_SIZE);

                                if(pRes->rowsCount() == 0) // ADD
                                {   
                                    sql_ExtTeleserviceToServiceIdMap_Create_Add_Query(pCapRoIdpConfig,sStatement,iIndex);
                                }
                                else // MOD
                                {
                                    delete pRes;
                                    DLOG_ERROR("Record Already Present");
                                    mysql_set_error_for_ExtTeleservice_Config_Reqs(pCapRoIdpConfig,resp,MOD_CAPROIDPEXTTELESERVICECONFIG_ERR_CONFIG_ALREADY_PRESENT,iIndex);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return MOD_CAPROIDPEXTTELESERVICECONFIG_ERR_CONFIG_ALREADY_PRESENT;
                                }
                                delete pRes;
                                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                {
                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                                    DLOG_NONE(" < %s ",__FUNCTION__);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = MOD_CAPROIDPEXTTELESERVICECONFIG_ERR_DB_ERROR;

                                    mysql_set_error_for_ExtTeleservice_Config_Reqs(pCapRoIdpConfig,resp,iReturn,iIndex);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);           
                                    return iReturn;
                                }

                            }
                        }

                        if(pCapRoIdpConfig->extbearerinfo_size()) // If EXT_BEARER_INFO is present
                        {
                            unsigned int ext_bearer_size = pCapRoIdpConfig->extbearerinfo_size();
                            for(unsigned int iIndex = 0; iIndex < ext_bearer_size ; iIndex++)
                            {
                                memset(sStatement,0,MAX_STATEMENT_SIZE);
                                sql_ExtBearerserviceToServiceIdMap_Create_Check_Modifcation_Query(pCapRoIdpConfig,sStatement,iIndex);

                                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                {   
                                    if(pRes != NULL)            
                                    {   
                                        delete pRes;
                                    }   

                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = MOD_CAPROIDPEXTBEARERSERVICECONFIG_ERR_DB_ERROR;

                                    mysql_set_error_for_ExtBearerservice_Config_Reqs(pCapRoIdpConfig,resp,iReturn,iIndex);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);           
                                    return iReturn;
                                }
                                memset(sStatement,0,MAX_STATEMENT_SIZE);

                                if(pRes->rowsCount() == 0) // ADD
                                {   
                                    sql_ExtBearerserviceToServiceIdMap_Create_Add_Query(pCapRoIdpConfig,sStatement,iIndex);
                                }
                                else // MOD
                                {
                                    delete pRes;
                                    DLOG_ERROR("Record Already Present");
                                    mysql_set_error_for_ExtBearerservice_Config_Reqs(pCapRoIdpConfig,resp,MOD_CAPROIDPEXTBEARERSERVICECONFIG_ERR_CONFIG_ALREADY_PRESENT,iIndex);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return MOD_CAPROIDPEXTBEARERSERVICECONFIG_ERR_CONFIG_ALREADY_PRESENT;
                                }
                                delete pRes;
                                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                {
                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                                    DLOG_NONE(" < %s ",__FUNCTION__);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = MOD_CAPROIDPEXTBEARERSERVICECONFIG_ERR_DB_ERROR;

                                    mysql_set_error_for_ExtBearerservice_Config_Reqs(pCapRoIdpConfig,resp,iReturn,iIndex);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);           
                                    return iReturn;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                iReturn = MOD_CAPROCONFIG_ERR_DATA_NOT_PRESENT;
                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
        else
        {
            iReturn = MOD_CAPROCONFIG_ERR_DATA_NOT_PRESENT;
            mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }
    else
    {
        iReturn = MOD_CAPROCONFIG_ERR_DATA_NOT_PRESENT;
        mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFCapRo_Del_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0}; 
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    ::IwfCapToRoConfig *pIwfCapToRoConfig = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    
    if(req->has_captoroinfo())
    {
        pIwfCapToRoConfig = req->mutable_captoroinfo();
        if(pIwfCapToRoConfig->has_translatorinfo())
        {
            ::IwfTranslatorConfig *pIwfTranslatorConfig = pIwfCapToRoConfig->mutable_translatorinfo();

            sql_IWFTranslator_Create_Check_Modifcation_Query(pIwfTranslatorConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_CAPROCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) 
            {
                delete pRes;
                DLOG_ERROR("Record Not Present");
                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,DEL_CAPROCONFIG_ERR_TRANSLATOR_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_CAPROCONFIG_ERR_TRANSLATOR_NOT_PRESENT;
            }
            delete pRes;            
            sql_IWFCapRoConfig_Create_Check_Modifcation_Query(pIwfCapToRoConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_CAPROCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) 
            {
				delete pRes;
                DLOG_ERROR("Record Not Present");
                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,DEL_CAPROCONFIG_ERR_CONFIG_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_CAPROCONFIG_ERR_CONFIG_NOT_PRESENT;
            }
            delete pRes;
            if(pIwfCapToRoConfig->has_caproidpinfo())
            {
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                
                if(pIwfCapToRoConfig->has_caproidpinfo()) //If CAPRo-IDP info is present
                {
                    ::CapRoIdpConfig *pCapRoIdpConfig = pIwfCapToRoConfig->mutable_caproidpinfo();
					if((sql_CapRoIdpConfig_Check_All_Invalid(pIwfCapToRoConfig)) == IWF_DB_FAIL)
					{
						sql_CapRoIdpConfig_Create_Check_Modifcation_Query(pIwfCapToRoConfig,sStatement);

						if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
						{   
							if(pRes != NULL)            
							{   
								delete pRes;
							}   

							DLOG_ERROR("Query Execution Failed: %s",sStatement);

							if(iReturn == DRE_DB_FAIL)
								iReturn = DEL_CAPROIDPCONFIG_ERR_DB_ERROR;

							mysql_set_error_for_CapRoIdpConfig_Config_Reqs(pCapRoIdpConfig,resp,iReturn);
                            DLOG_DEBUG("iReturn = %d",iReturn);
							DLOG_NONE(" < %s ",__FUNCTION__);           
							return iReturn;
						}
						memset(sStatement,0,MAX_STATEMENT_SIZE);

						if(pRes->rowsCount() == 0) // NO DATA
						{   
							delete pRes;
							DLOG_ERROR("Record Not Present");
							mysql_set_error_for_CapRoIdpConfig_Config_Reqs(pCapRoIdpConfig,resp,DEL_CAPROIDPCONFIG_ERR_CONFIG_NOT_PRESENT);
							DLOG_NONE(" < %s ",__FUNCTION__);
							return DEL_CAPROIDPCONFIG_ERR_CONFIG_NOT_PRESENT;
						}
                        delete pRes; 
					}
					
                    if(pCapRoIdpConfig->extteleinfo_size() > 0 || pCapRoIdpConfig->extbearerinfo_size() > 0)
                    {
                        memset(sStatement,0,MAX_STATEMENT_SIZE);
                        if(pCapRoIdpConfig->extteleinfo_size()) // If EXT_TELE_INFO is present
                        {
                            unsigned int ext_tele_size = pCapRoIdpConfig->extteleinfo_size();
                            for(unsigned int iIndex = 0; iIndex < ext_tele_size ; iIndex++)
                            {
                                memset(sStatement,0,MAX_STATEMENT_SIZE);
                                sql_ExtTeleserviceToServiceIdMap_Create_Check_Modifcation_Query(pCapRoIdpConfig,sStatement,iIndex);

                                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                {   
                                    if(pRes != NULL)            
                                    {   
                                        delete pRes;
                                    }   

                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = DEL_CAPROIDPEXTTELESERVICECONFIG_ERR_DB_ERROR;

                                    mysql_set_error_for_ExtTeleservice_Config_Reqs(pCapRoIdpConfig,resp,iReturn,iIndex);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);           
                                    return iReturn;
                                }
                                memset(sStatement,0,MAX_STATEMENT_SIZE);

                                if(pRes->rowsCount() != 0) // DELETE
                                {   
                                    sql_ExtTeleserviceToServiceIdMap_Create_Delete_Query(pCapRoIdpConfig,sStatement,iIndex);
                                }
                                else // ADD
                                {
                                    delete pRes;
                                    DLOG_ERROR("Record Not Present");
                                    mysql_set_error_for_ExtTeleservice_Config_Reqs(pCapRoIdpConfig,resp,DEL_CAPROIDPEXTTELESERVICECONFIG_ERR_CONFIG_NOT_PRESENT,iIndex);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return DEL_CAPROIDPEXTTELESERVICECONFIG_ERR_CONFIG_NOT_PRESENT;
                                }
                                delete pRes;
                                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                {
                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                                    DLOG_NONE(" < %s ",__FUNCTION__);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = DEL_CAPROIDPEXTTELESERVICECONFIG_ERR_DB_ERROR;

                                    mysql_set_error_for_ExtTeleservice_Config_Reqs(pCapRoIdpConfig,resp,iReturn,iIndex);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);           
                                    return iReturn;
                                }

                            }
                        }

                        if(pCapRoIdpConfig->extbearerinfo_size()) // If EXT_BEARER_INFO is present
                        {
                            unsigned int ext_bearer_size = pCapRoIdpConfig->extbearerinfo_size();
                            for(unsigned int iIndex = 0; iIndex < ext_bearer_size ; iIndex++)
                            {
                                memset(sStatement,0,MAX_STATEMENT_SIZE);
                                sql_ExtBearerserviceToServiceIdMap_Create_Check_Modifcation_Query(pCapRoIdpConfig,sStatement,iIndex);

                                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
                                {   
                                    if(pRes != NULL)            
                                    {   
                                        delete pRes;
                                    }   

                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = DEL_CAPROIDPEXTBEARERSERVICECONFIG_ERR_DB_ERROR;

                                    mysql_set_error_for_ExtBearerservice_Config_Reqs(pCapRoIdpConfig,resp,iReturn,iIndex);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);           
                                    return iReturn;
                                }
                                memset(sStatement,0,MAX_STATEMENT_SIZE);

                                if(pRes->rowsCount() != 0) // DELETE
                                {   
                                    sql_ExtBearerserviceToServiceIdMap_Create_Delete_Query(pCapRoIdpConfig,sStatement,iIndex);
                                }
                                else // ADD
                                {
                                    delete pRes;
                                    DLOG_ERROR("Record Not Present");
                                    mysql_set_error_for_ExtBearerservice_Config_Reqs(pCapRoIdpConfig,resp,DEL_CAPROIDPEXTBEARERSERVICECONFIG_ERR_CONFIG_NOT_PRESENT,iIndex);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return DEL_CAPROIDPEXTBEARERSERVICECONFIG_ERR_CONFIG_NOT_PRESENT;
                                }
                                delete pRes;
                                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                                {
                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                                    DLOG_NONE(" < %s ",__FUNCTION__);

                                    if(iReturn == DRE_DB_FAIL)
                                        iReturn = DEL_CAPROIDPEXTBEARERSERVICECONFIG_ERR_DB_ERROR;

                                    mysql_set_error_for_ExtBearerservice_Config_Reqs(pCapRoIdpConfig,resp,iReturn,iIndex);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);           
                                    return iReturn;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                iReturn = DEL_CAPROCONFIG_ERR_DATA_NOT_PRESENT;
                mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
        else
        {
            iReturn = DEL_CAPROCONFIG_ERR_DATA_NOT_PRESENT;
            mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }
    else
    {
        iReturn = DEL_CAPROCONFIG_ERR_DATA_NOT_PRESENT;
        mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(pIwfCapToRoConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}
