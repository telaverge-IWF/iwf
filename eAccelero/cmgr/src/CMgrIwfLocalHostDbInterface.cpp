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


void CMgrIwfDbInterface::mysql_set_error_for_LocalHostConfig_Config_Reqs(IwfLocalHostConfig *pIwfLocalHostConfig, IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(pIwfLocalHostConfig->has_protocolfamily())
        err->add_variables(pIwfLocalHostConfig->protocolfamily());

    if(pIwfLocalHostConfig->has_pointcode())
    {
        char sPointCode[10];
        snprintf(sPointCode,10,"%d",pIwfLocalHostConfig->pointcode());
        err->add_variables(sPointCode);
    }

    if(iReturn == SET_LOCALHOST_ERR_SSN_MAX_COUNT_REACHED)
    {
        char sMaxSsnCount[10];
        snprintf(sMaxSsnCount,10,"%d",MAX_SSN_SUPPORTED);
        err->add_variables(sMaxSsnCount);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFLocalConfig_Config_Reqs(IwfLocalHostConfig *pIwfLocalHostConfig, IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(pIwfLocalHostConfig->has_protocolfamily())
        err->add_variables(pIwfLocalHostConfig->protocolfamily());

    if(pIwfLocalHostConfig->has_pointcode())
    {
        char sPointCode[10];
        snprintf(sPointCode,10,"%d",pIwfLocalHostConfig->pointcode());
        err->add_variables(sPointCode);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFLocalSSN_Config_Reqs(IwfLocalSSNConfig *pIwfLocalSSNConfig, IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(pIwfLocalSSNConfig && pIwfLocalSSNConfig->has_ssn())
    {
        char sSsn[10];
        snprintf(sSsn,10,"%d",pIwfLocalSSNConfig->ssn());
        err->add_variables(sSsn);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFLocalSSNMapping_Config_Reqs(IwfLocalHostConfig *pIwfLocalHostConfig, IWFCfgResp *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    IwfLocalSSNConfig* pIwfLocalSSNConfig = NULL;
    if(pIwfLocalHostConfig->ssn_config_size() > iIndex && iIndex > -1)
    {
	    pIwfLocalSSNConfig = pIwfLocalHostConfig->mutable_ssn_config(iIndex);
    }

    if(pIwfLocalSSNConfig && pIwfLocalSSNConfig->has_ssn())
    {
        char sStatement[MAX_STATEMENT_SIZE] = {0};
        sql_IWFLocalSSN_Create_Select_Query(pIwfLocalSSNConfig,sStatement);

        sql::ResultSet *pRes = NULL;
        if(m_dbHandle.mysql_exec_get_query(sStatement,&pRes) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return;
        }

        if(pRes->rowsCount() > 0)
        {
           if(pRes->next()) 
           {
               if(!pRes->isNull("SSN_NAME"))
               {
                   err->add_variables(pRes->getString("SSN_NAME"));
               }
           }
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFProtocolFamily_protobuff(IwfLocalHostConfig *pIwfLocalHostConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_ProtocolFamily_Create_Select_Query(pIwfLocalHostConfig,sStatement);

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
            iReturn = GET_LOCALHOST_ERR_DB_ERROR;

        mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
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
                if(!pRes->isNull("IWF_PROTOCOL_FAMILY_ID"))
                    pIwfLocalHostConfig->set_protocolid(pRes->getInt("IWF_PROTOCOL_FAMILY_ID"));
                if(!pRes->isNull("FAMILY_NAME"))
                   pIwfLocalHostConfig->set_protocolfamily(pRes->getString("FAMILY_NAME"));
            }
        }
        else
        {
            //delete pRes;
            //return GET_PROTOCOL_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::Fill_IWFLocalConfig_protobuff(IwfLocalHostConfig *pIwfLocalHostConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFLocalConfig_Create_Select_Query(pIwfLocalHostConfig,sStatement);

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
            iReturn = GET_LOCALHOST_ERR_DB_ERROR;

        mysql_set_error_for_IWFLocalConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
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
                if(!pRes->isNull("IWF_PROTOCOL_FAMILY_ID"))
                    pIwfLocalHostConfig->set_protocolid(pRes->getInt("IWF_PROTOCOL_FAMILY_ID"));
                if(!pRes->isNull("NI"))
                    pIwfLocalHostConfig->set_networkindicator(pRes->getInt("NI"));
                if(!pRes->isNull("POINTCODE"))
                    pIwfLocalHostConfig->set_pointcode(pRes->getInt("POINTCODE"));
                if(!pRes->isNull("TCAP_INVOKE_TIMER"))
                    pIwfLocalHostConfig->set_tcapinvoketimer(pRes->getInt("TCAP_INVOKE_TIMER"));
                if(!pRes->isNull("ADDRESS_TYPE"))
                    pIwfLocalHostConfig->set_addresstype(pRes->getString("ADDRESS_TYPE"));
                if(!pRes->isNull("GTI"))
                    pIwfLocalHostConfig->set_gti(pRes->getInt("GTI"));
                if(!pRes->isNull("TRANSLATION_TYPE"))
                    pIwfLocalHostConfig->set_translationtype(pRes->getInt("TRANSLATION_TYPE"));
                if(!pRes->isNull("NUMBERING_PLAN"))
                    pIwfLocalHostConfig->set_numberingplan(pRes->getInt("NUMBERING_PLAN"));
                if(!pRes->isNull("ENCODING_SCHEME"))
                    pIwfLocalHostConfig->set_encodingscheme(pRes->getInt("ENCODING_SCHEME"));
                if(!pRes->isNull("NATURE_OF_ADDRESS_INDICATOR"))
                    pIwfLocalHostConfig->set_natureofaddrind(pRes->getInt("NATURE_OF_ADDRESS_INDICATOR"));
                if(!pRes->isNull("SELECTION_CRITERIA"))
                    pIwfLocalHostConfig->set_selectcriteria(pRes->getInt("SELECTION_CRITERIA"));
                if(!pRes->isNull("GT_ADDR_DIGITS"))
                    pIwfLocalHostConfig->set_gtaddrdigits(pRes->getString("GT_ADDR_DIGITS"));
                if(!pRes->isNull("USE_LOCAL_GT_FROM_CONFIG"))
                    pIwfLocalHostConfig->set_localgtusefromconfig(pRes->getInt("USE_LOCAL_GT_FROM_CONFIG"));
                if(!pRes->isNull("USE_SCCP_CDPA_FROM_INCOMMING_MSG"))
                    pIwfLocalHostConfig->set_usesccpcdpafromincommingmsg(pRes->getInt("USE_SCCP_CDPA_FROM_INCOMMING_MSG"));
                if(!pRes->isNull("INCLUDE_SSN"))
                    pIwfLocalHostConfig->set_includessn(pRes->getInt("INCLUDE_SSN"));
                if(!pRes->isNull("INCLUDE_PC"))
                    pIwfLocalHostConfig->set_includepc(pRes->getInt("INCLUDE_PC"));
                if(!pRes->isNull("HOST_NAME_1"))
                    pIwfLocalHostConfig->set_hostname1(pRes->getString("HOST_NAME_1"));
                if(!pRes->isNull("HOST_NAME_2"))
                    pIwfLocalHostConfig->set_hostname2(pRes->getString("HOST_NAME_2"));
                if(!pRes->isNull("ASP_ID_1"))
                    pIwfLocalHostConfig->set_aspid1(pRes->getInt("ASP_ID_1"));
                if(!pRes->isNull("ASP_ID_2"))
                    pIwfLocalHostConfig->set_aspid2(pRes->getInt("ASP_ID_2"));
            }
        }
        else
        {
            delete pRes;
            return GET_LOCALHOST_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::Fill_IWFLocalSSNMapping_protobuff(IwfLocalHostConfig *pIwfLocalHostConfig,IWFCfgResp *resp,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFLocalSSNMapping_Create_Select_Query(pIwfLocalHostConfig,sStatement,iIndex);

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
            iReturn = GET_LOCALHOST_ERR_DB_ERROR;

        mysql_set_error_for_IWFLocalSSNMapping_Config_Reqs(pIwfLocalHostConfig,resp,iReturn,iIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    IwfLocalSSNConfig *pIwfLocalSSNConfig = NULL;

    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            while(pRes->next())
            {
                if(pIwfLocalHostConfig->ssn_config_size() > iIndex && iIndex > -1)
                {
                    pIwfLocalSSNConfig = pIwfLocalHostConfig->mutable_ssn_config(iIndex); 
                }
                else
                {
                    pIwfLocalSSNConfig = pIwfLocalHostConfig->add_ssn_config(); 
                }

                if(!pRes->isNull("IWF_LOCAL_SSN_ID"))
                {
                    pIwfLocalSSNConfig->set_ssnid(pRes->getInt("IWF_LOCAL_SSN_ID"));
                    Fill_IWFLocalSSN_protobuff(pIwfLocalSSNConfig,resp);
                }
            }
        }
        else
        {
            delete pRes;
            return GET_SSN_MAPPING_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::Fill_IWFLocalSSN_protobuff(IwfLocalSSNConfig *pIwfLocalSSNConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFLocalSSN_Create_Select_Query(pIwfLocalSSNConfig,sStatement);

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
            iReturn = GET_LOCALHOST_ERR_DB_ERROR;

        mysql_set_error_for_IWFLocalSSN_Config_Reqs(pIwfLocalSSNConfig,resp,iReturn);
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
                if(!pRes->isNull("IWF_LOCAL_SSN_ID"))
                    pIwfLocalSSNConfig->set_ssnid(pRes->getInt("IWF_LOCAL_SSN_ID"));
                if(!pRes->isNull("SSN"))
                    pIwfLocalSSNConfig->set_ssn(pRes->getInt("SSN"));
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

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

#if 1

DbStatus_e CMgrIwfDbInterface::mysql_IWFLocalHostConfig_Validation(IwfLocalHostConfig *pIwfLocalHostConfig, IWFCfgResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;

    IwfLocalHostConfig lIwfLocalHostConfig;
    lIwfLocalHostConfig.set_pointcode(pIwfLocalHostConfig->pointcode());

    sql_IWFLocalSSNMapping_Create_Select_Query(&lIwfLocalHostConfig,sStatement,-1);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = SET_LOCALSSNMAPPING_ERR_DB_ERROR;

        mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);
    DLOG_ERROR("pRes->rowsCount = %d",pRes->rowsCount());   

    if(pRes->rowsCount() >= MAX_SSN_SUPPORTED)
    {
        delete pRes;
        DLOG_ERROR("Reached Max supported ssn");   
        DLOG_NONE(" < %s ",__FUNCTION__);
        return SET_LOCALHOST_ERR_SSN_MAX_COUNT_REACHED;
    }
    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}

DbStatus_e CMgrIwfDbInterface::mysql_IWFLocalSSNConfig_Add_Validation(IwfLocalSSNConfig *pIwfLocalSSNConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;

    sql_IWFLocalSSN_Create_Select_Query(pIwfLocalSSNConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = SET_LOCALSSN_ERR_DB_ERROR;

        mysql_set_error_for_IWFLocalSSN_Config_Reqs(pIwfLocalSSNConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0)
    {
        delete pRes;
        DLOG_ERROR("Record Not Present");   
        mysql_set_error_for_IWFLocalSSN_Config_Reqs(pIwfLocalSSNConfig,resp,SET_LOCALHOST_ERR_SSN_NOT_PRESENT);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return SET_LOCALHOST_ERR_SSN_NOT_PRESENT;
    }
    delete pRes;

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFLocalConfig_Del_Config_Reqs(IwfLocalHostsConfig *pIwfLocalHostsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(!pIwfLocalHostsConfig->has_localhostinfo())
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(MOD_LOCALHOST_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_LOCALHOST_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    IwfLocalHostConfig *pIwfLocalHostConfig = pIwfLocalHostsConfig->mutable_localhostinfo();

#if 0
    sql_IWFLocalConfig_Create_Check_Modifcation_Query(pIwfLocalHostConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = MOD_LOCALHOST_ERR_DB_ERROR;

        mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        delete pRes;
        DLOG_ERROR("Record Not Present");   
        mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,MOD_LOCALHOST_ERR_LOCALHOST_NOT_PRESENT);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return MOD_LOCALHOST_ERR_LOCALHOST_NOT_PRESENT;
    }

    delete pRes;
#endif

    int iSsnCount = pIwfLocalHostConfig->ssn_config_size(); 
    DLOG_DEBUG("iSsnCount = %d ",iSsnCount);

    for(int i=0;i<iSsnCount;i++)
    {
        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        IwfLocalSSNConfig *pIwfLocalSSNConfig = pIwfLocalHostConfig->mutable_ssn_config(i);
        if((iReturn = mysql_IWFLocalSSNConfig_Add_Validation(pIwfLocalSSNConfig,resp)) != IWF_DB_SUCCESS)
        {
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn; 
        }

        sql_IWFLocalSSNMapping_Create_Check_Modifcation_Query(pIwfLocalHostConfig,sStatement,i);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = SET_LOCALSSNMAPPING_ERR_DB_ERROR;

            mysql_set_error_for_IWFLocalSSNMapping_Config_Reqs(pIwfLocalHostConfig,resp,iReturn,i);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Not Present");   
            mysql_set_error_for_IWFLocalSSNMapping_Config_Reqs(pIwfLocalHostConfig,resp,DEL_LOCALHOST_ERR_SSN_NOT_MAPPED,i);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_LOCALHOST_ERR_SSN_NOT_MAPPED;
        }
        else // MOD
        {
            sql_IWFLocalSSNMapping_CreateCount_Check_Modifcation_Query(sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = SET_LOCALSSNMAPPING_ERR_DB_ERROR;

                mysql_set_error_for_IWFLocalSSNMapping_Config_Reqs(pIwfLocalHostConfig,resp,iReturn,i);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() > 1) 
            {
                sql_IWFLocalSSNMapping_Create_Delete_Query(pIwfLocalHostConfig,sStatement,i);
            }
            else
            {
                delete pRes;
                DLOG_ERROR("Last SSN is not allowed to delete");   
                mysql_set_error_for_IWFLocalSSNMapping_Config_Reqs(pIwfLocalHostConfig,resp,DEL_LOCALHOST_ERR_LAST_SSN_NOT_ALLOWED_TO_DELETE,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_LOCALHOST_ERR_LAST_SSN_NOT_ALLOWED_TO_DELETE;
            }
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_LOCALSSNMAPPING_ERR_DB_ERROR;

            mysql_set_error_for_IWFLocalSSNMapping_Config_Reqs(pIwfLocalHostConfig,resp,iReturn,i);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    if(iReturn == IWF_DB_SUCCESS)
        iReturn = IWF_DB_SUCCESS_SEND;

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFLocalConfig_Mod_Config_Reqs(IwfLocalHostsConfig *pIwfLocalHostsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(!pIwfLocalHostsConfig->has_localhostinfo())
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(MOD_LOCALHOST_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[MOD_LOCALHOST_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }
    IwfLocalHostConfig *pIwfLocalHostConfig = pIwfLocalHostsConfig->mutable_localhostinfo();
#if 1

    sql_IWFLocalConfig_Create_Check_Modifcation_Query(pIwfLocalHostConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = MOD_LOCALHOST_ERR_DB_ERROR;

        mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        delete pRes;
        DLOG_ERROR("Record Not Present");   
        mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,MOD_LOCALHOST_ERR_LOCALHOST_NOT_PRESENT);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return MOD_LOCALHOST_ERR_LOCALHOST_NOT_PRESENT;
    }
    else // MOD
    {
#if 0
        if(pIwfLocalHostConfig->has_aspid1())
        {
            pRes = NULL;
            sql_IWFLocalConfig_Create_Check_AspId_Modifcation_Query(pIwfLocalHostConfig->aspid1(),sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_LOCALHOST_ERR_DB_ERROR;

                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() > 0)
            {
                delete pRes;
                DLOG_ERROR("AspId already configured for LocalHost AspId's");   
                DLOG_NONE(" < %s ",__FUNCTION__);
                return MOD_LOCALHOST_ERR_ASP_ID_ALREADY_PRESENT;
            }
            delete pRes;
            pRes = NULL;
            //NOTE: Update the aspId in Association tabel if user modifies local asp-id
            if((iReturn = CheckAndModifyAssociationAspId(pIwfLocalHostConfig)) != IWF_DB_SUCCESS)
            {
                mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn; 
            }
        }

        if(pIwfLocalHostConfig->has_aspid2())
        {
            pRes = NULL;
            sql_IWFLocalConfig_Create_Check_AspId_Modifcation_Query(pIwfLocalHostConfig->aspid2(),sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_LOCALHOST_ERR_DB_ERROR;

                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() > 0)
            {
                delete pRes;
                DLOG_ERROR("AspId already configured for LocalHost AspId's");   
                DLOG_NONE(" < %s ",__FUNCTION__);
                return MOD_LOCALHOST_ERR_ASP_ID_ALREADY_PRESENT;
            }
            delete pRes;
            pRes = NULL;
            //NOTE: Update the aspId in Association tabel if user modifies local asp-id
            if((iReturn = CheckAndModifyAssociationAspId(pIwfLocalHostConfig)) != IWF_DB_SUCCESS)
            {
                mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn; 
            }
        }
#endif 
        if(pIwfLocalHostConfig->has_selectcriteria())
        {
            DLOG_DEBUG("Selection Criteria is modified under IWF LocalConfig");

            memset(sStatement,0,MAX_STATEMENT_SIZE);
            IwfLocalHostsConfig plocalIwfLocalHostsConfig;
            IWFCfgResp localresp;

            if((iReturn = mysql_IWFLocalConfig_Get_Config_Reqs(&plocalIwfLocalHostsConfig, &localresp)) == IWF_DB_SUCCESS)
            {
                if(localresp.has_localhostinfo())
                {
                    IwfLocalHostsConfig* LocalHostsConfig = localresp.mutable_localhostinfo();
                    if(LocalHostsConfig->has_localhostinfo())
                    {
                        IwfLocalHostConfig* LocalHostInfo = LocalHostsConfig->mutable_localhostinfo();
                        DLOG_DEBUG("LocalHost Config in DB = %s",LocalHostInfo->DebugString().c_str());
                        if(LocalHostInfo->has_selectcriteria() &&
                                (pIwfLocalHostConfig->selectcriteria() != LocalHostInfo->selectcriteria()))
                        {
                            sql_IWFAllTranslatorRule_Create_Delete_Query(sStatement); 

                            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
                            {
                                DLOG_ERROR("Query Execution Failed %s",sStatement);
                                if(iReturn == IWF_DB_FAIL)
                                    iReturn = MOD_LOCALHOST_ERR_DB_ERROR;

                                mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
                                DLOG_DEBUG("iReturn = %d",iReturn);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return iReturn;
                            }
                        }
                    }
                }
            }
        }
        sql_IWFLocalConfig_Create_Mod_Query(pIwfLocalHostConfig,sStatement);
    }

    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);
        if(iReturn == IWF_DB_FAIL)
            iReturn = MOD_LOCALHOST_ERR_DB_ERROR;

        mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
#endif

    int iSsnCount = pIwfLocalHostConfig->ssn_config_size(); 
    DLOG_DEBUG("iSsnCount = %d ",iSsnCount);

    for(int i=0;i<iSsnCount;i++)
    {
        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if((iReturn = mysql_IWFLocalHostConfig_Validation(pIwfLocalHostConfig,resp)) != IWF_DB_SUCCESS)
        {
            mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn; 
        }

        IwfLocalSSNConfig *pIwfLocalSSNConfig = pIwfLocalHostConfig->mutable_ssn_config(i);
        if((iReturn = mysql_IWFLocalSSNConfig_Add_Validation(pIwfLocalSSNConfig,resp)) != IWF_DB_SUCCESS)
        {
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn; 
        }

        sql_IWFLocalSSNMapping_Create_Check_Modifcation_Query(pIwfLocalHostConfig,sStatement,i);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = SET_LOCALSSNMAPPING_ERR_DB_ERROR;

            mysql_set_error_for_IWFLocalSSNMapping_Config_Reqs(pIwfLocalHostConfig,resp,iReturn,i);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_IWFLocalSSNMapping_Create_Add_Query(pIwfLocalHostConfig,sStatement,i);
        }
        else // MOD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present");   
            mysql_set_error_for_IWFLocalSSNMapping_Config_Reqs(pIwfLocalHostConfig,resp,SET_LOCALHOST_ERR_SSN_HOSTID_ALREADY_MAPPED,i);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return SET_LOCALHOST_ERR_SSN_HOSTID_ALREADY_MAPPED;
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
               iReturn = SET_LOCALSSNMAPPING_ERR_DB_ERROR;

            mysql_set_error_for_IWFLocalSSNMapping_Config_Reqs(pIwfLocalHostConfig,resp,iReturn,i);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    if(iReturn == IWF_DB_SUCCESS)
        iReturn = IWF_DB_SUCCESS_SEND;

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::CheckAndModifyAssociationAspId(IwfLocalHostConfig *pIwfLocalHostConfig)
{
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IWFCfgResp resp;
    IwfLocalHostConfig LocalIwfLocalHostConfigObj;
    Fill_IWFLocalConfig_protobuff(&LocalIwfLocalHostConfigObj,&resp);
    if((pIwfLocalHostConfig->has_aspid1() && LocalIwfLocalHostConfigObj.has_aspid1()) || 
            (pIwfLocalHostConfig->has_aspid2() && LocalIwfLocalHostConfigObj.has_aspid2()))
    {
        if(pIwfLocalHostConfig->has_aspid1() && LocalIwfLocalHostConfigObj.has_aspid1())
            sql_IWFSigtranAssociation_Create_Mod_AspId_Query(pIwfLocalHostConfig->aspid1(), LocalIwfLocalHostConfigObj.aspid1(), sStatement);
        else if(pIwfLocalHostConfig->has_aspid2() && LocalIwfLocalHostConfigObj.has_aspid2())
            sql_IWFSigtranAssociation_Create_Mod_AspId_Query(pIwfLocalHostConfig->aspid2(), LocalIwfLocalHostConfigObj.aspid2(), sStatement);
        
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_LOCALHOST_ERR_DB_ERROR;

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFLocalConfig_Get_Config_Reqs(IwfLocalHostsConfig *pIwfLocalHostsConfig,IWFCfgResp *resp)
{
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    IwfLocalHostConfig LocalIwfLocalHostConfigObj;

    if((iReturn = Fill_IWFLocalConfig_protobuff(&LocalIwfLocalHostConfigObj,resp)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_LOCALHOST_ERR_DB_ERROR;

        mysql_set_error_for_IWFLocalConfig_Config_Reqs(&LocalIwfLocalHostConfigObj,resp,iReturn);
        return iReturn;
    }

    Fill_IWFProtocolFamily_protobuff(&LocalIwfLocalHostConfigObj,resp);
    Fill_IWFLocalSSNMapping_protobuff(&LocalIwfLocalHostConfigObj,resp,-1);

    IwfLocalHostsConfig *pLocalIwfLocalHostsConfig = resp->mutable_localhostinfo();
    IwfLocalHostConfig *pIwfLocalHostConfig = pLocalIwfLocalHostsConfig->mutable_localhostinfo();

    pIwfLocalHostConfig->CopyFrom(LocalIwfLocalHostConfigObj);
#if 0
    if((iReturn = Fill_IWFProtocolFamily_protobuff(pIwfLocalHostConfig,resp)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_LOCALHOST_ERR_DB_ERROR;

        mysql_set_error_for_IWFLocalConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
    }

    if((iReturn = Fill_IWFLocalSSNMapping_protobuff(pIwfLocalHostConfig,resp,-1)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_LOCALHOST_ERR_DB_ERROR;

        mysql_set_error_for_IWFLocalConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
    }
#endif

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFLocalConfig_Add_Config_Reqs(IwfLocalHostsConfig *pIwfLocalHostsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(!pIwfLocalHostsConfig->has_localhostinfo())
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(SET_LOCALHOST_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[SET_LOCALHOST_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    IwfLocalHostConfig *pIwfLocalHostConfig = pIwfLocalHostsConfig->mutable_localhostinfo();

    sql_IWFLocalConfig_Create_Check_Modifcation_Query(pIwfLocalHostConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = SET_LOCALHOST_ERR_DB_ERROR;

        mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        DLOG_DEBUG("iReturn = %d",iReturn);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_IWFLocalConfig_Create_Add_Query(pIwfLocalHostConfig,sStatement);
    }
    else // MOD
    {
        delete pRes;
        DLOG_ERROR("Record Already Present");   
        mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,SET_LOCALHOST_ERR_LOCALHOST_ALREADY_EXISTS);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return SET_LOCALHOST_ERR_LOCALHOST_ALREADY_EXISTS;

    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);
        if(iReturn == IWF_DB_FAIL)
            iReturn = SET_LOCALHOST_ERR_DB_ERROR;

        mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }


    int iSsnCount = pIwfLocalHostConfig->ssn_config_size(); 
    DLOG_DEBUG("iSsnCount = %d ",iSsnCount);

    for(int i=0;i<iSsnCount;i++)
    {
        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if((iReturn = mysql_IWFLocalHostConfig_Validation(pIwfLocalHostConfig,resp)) != IWF_DB_SUCCESS)
        {
            mysql_set_error_for_LocalHostConfig_Config_Reqs(pIwfLocalHostConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn; 
        }

        IwfLocalSSNConfig *pIwfLocalSSNConfig = pIwfLocalHostConfig->mutable_ssn_config(i);
        if((iReturn = mysql_IWFLocalSSNConfig_Add_Validation(pIwfLocalSSNConfig,resp)) != IWF_DB_SUCCESS)
        {
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn; 
        }

        sql_IWFLocalSSNMapping_Create_Check_Modifcation_Query(pIwfLocalHostConfig,sStatement,i);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = SET_LOCALSSNMAPPING_ERR_DB_ERROR;

            mysql_set_error_for_IWFLocalSSNMapping_Config_Reqs(pIwfLocalHostConfig,resp,iReturn,i);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_IWFLocalSSNMapping_Create_Add_Query(pIwfLocalHostConfig,sStatement,i);
        }
        else // MOD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present");   
            mysql_set_error_for_IWFLocalSSNMapping_Config_Reqs(pIwfLocalHostConfig,resp,SET_LOCALHOST_ERR_SSN_HOSTID_ALREADY_MAPPED,i);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return SET_LOCALHOST_ERR_SSN_HOSTID_ALREADY_MAPPED;
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
               iReturn = SET_LOCALSSNMAPPING_ERR_DB_ERROR;

            mysql_set_error_for_IWFLocalSSNMapping_Config_Reqs(pIwfLocalHostConfig,resp,iReturn,i);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::check_for_IWF_requestid(IwfLocalHostsConfig *req, IWFCfgResp *resp)
{
    int iOperID = -1;
    DbStatus_e iReturn = DRE_DB_SUCCESS;
    IwfLocalHostsConfig localreq;
    IWFCfgResp localIWFCfgResp;

    DLOG_NONE(" > %s ",__FUNCTION__);


    DLOG_NONE(" req %p %s ",req,__FUNCTION__);    
    if(req->has_operreqid())
    {
        DLOG_NONE("%s Operreq ID is set in LocalHostConfig ",__FUNCTION__);
        iOperID = req->operreqid();
    }

    DLOG_NONE(" OperID = %d %s ",iOperID,__FUNCTION__);

    if (DRE_DB_FAIL == m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");    
        resp->set_respid(CMAPI_ERROR);
        mysql_set_error_for_iwfCfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }  

    switch(iOperID)
    {
        case GET_LOCAL_HOST:
            iReturn = mysql_IWFLocalConfig_Get_Config_Reqs(req,&localIWFCfgResp);
            Copy_IWFCfgResp_localresponse_to_Reponse(&localIWFCfgResp,resp);
            break;
        default:
            DLOG_NONE(" OperID default %s ",__FUNCTION__);
            break;
    }

    if(iReturn == DRE_DB_SUCCESS)
        resp->set_respid(CMAPI_SUCCESS);
    else 
        resp->set_respid(CMAPI_ERROR);

    m_dbHandle.mysql_release_current_connection();

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

void CMgrIwfDbInterface::Copy_IWFCfgResp_localresponse_to_Reponse(IWFCfgResp *localresp, IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    IwfLocalHostsConfig plocalHostsConfig;
    DLOG_DEBUG("Before LocalResp = %s",localresp->DebugString().c_str());
    DLOG_DEBUG("Before IWFResp = %s",resp->DebugString().c_str());


    if(resp->has_localhostinfo())
    {
        IwfLocalHostsConfig *localhost = resp->mutable_localhostinfo();
        IwfLocalHostsConfig *localRespLocalHost = localresp->mutable_localhostinfo();

        if(localhost->has_localhostinfo())
        {
            IwfLocalHostConfig *plocalHostConfig = localhost->mutable_localhostinfo(); 
            if(plocalHostConfig->has_networkindicator())
            {
                IwfLocalHostConfig *pLocalHost = localRespLocalHost->mutable_localhostinfo();
                IwfLocalHostConfig *plocalhostconfig = plocalHostsConfig.mutable_localhostinfo();
                plocalhostconfig->CopyFrom(*pLocalHost);
                plocalhostconfig->MergeFrom(*plocalHostConfig);
            }
        }
        localhost->Clear();
        localhost->CopyFrom(plocalHostsConfig);
    }
    DLOG_DEBUG("After LocalResp = %s",localresp->DebugString().c_str());
    DLOG_DEBUG("After IWFResp = %s",resp->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}
#endif
