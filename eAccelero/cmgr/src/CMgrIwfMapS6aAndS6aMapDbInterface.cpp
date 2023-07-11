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


void CMgrIwfDbInterface::mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(IwfMapToS6aConfig *pIwfMapToS6aConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    IwfTranslatorConfig *pLocalIwfTranslatorConfig = NULL;

    if(pIwfMapToS6aConfig -> has_translatorinfo())
    {
        pLocalIwfTranslatorConfig = pIwfMapToS6aConfig -> mutable_translatorinfo();
        if(pLocalIwfTranslatorConfig -> has_translatorname())
            err->add_variables(pLocalIwfTranslatorConfig -> translatorname());
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFMapS6aVplmnId_Config_Reqs(IwfMapToS6aConfig *pIwfMapToS6aConfig,IWFCfgResp *resp,DbStatus_e iReturn, int index)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    IwfTranslatorConfig *pLocalIwfTranslatorConfig = NULL;

    if(pIwfMapToS6aConfig -> has_translatorinfo())
    {
        pLocalIwfTranslatorConfig = pIwfMapToS6aConfig -> mutable_translatorinfo();
        if(pLocalIwfTranslatorConfig -> has_translatorname())
            err->add_variables(pLocalIwfTranslatorConfig -> translatorname());
    }

    if(pIwfMapToS6aConfig->maptos6avplmnidinfo_size())
    {
	IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfig = pIwfMapToS6aConfig->mutable_maptos6avplmnidinfo(index);
	if(pIwfMapToS6aVplmnIdConfig->has_allowedvplmnid())
		err->add_variables(pIwfMapToS6aVplmnIdConfig->allowedvplmnid());
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFMapS6aVplmnIdSgsnMap_Config_Reqs(IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfig,IWFCfgResp *resp,DbStatus_e iReturn, int index)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());
    if(pIwfMapToS6aVplmnIdConfig->has_allowedvplmnid())
	err->add_variables(pIwfMapToS6aVplmnIdConfig->allowedvplmnid());
    
    if((index != -1) && (pIwfMapToS6aVplmnIdConfig->sgsnnumberinfo_size()))
    {
	SgsnNumbers *pSgsnNumbers = pIwfMapToS6aVplmnIdConfig->mutable_sgsnnumberinfo(index);
	if(pSgsnNumbers->has_sgsnnumber())
		err->add_variables(pSgsnNumbers->sgsnnumber());
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(IwfS6aToMapConfig *pIwfS6aToMapConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    IwfTranslatorConfig *pLocalIwfTranslatorConfig = NULL;

    if(pIwfS6aToMapConfig -> has_translatorinfo())
    {
        pLocalIwfTranslatorConfig = pIwfS6aToMapConfig -> mutable_translatorinfo();
        if(pLocalIwfTranslatorConfig -> has_translatorname())
            err->add_variables(pLocalIwfTranslatorConfig -> translatorname());
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFS6aMapSgsnAddrMap_Config_Reqs(IwfS6aToMapConfig *pIwfS6aToMapConfig,IWFCfgResp *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    SgsnAddresses *pSgsnAddressesReq = NULL;
    if(pIwfS6aToMapConfig -> sgsnaddress_size() > iIndex && iIndex > -1)
    {
        pSgsnAddressesReq = pIwfS6aToMapConfig -> mutable_sgsnaddress(iIndex);
    }

    if(pSgsnAddressesReq && pSgsnAddressesReq->has_orginhost())
    {
        err->add_variables(pSgsnAddressesReq -> orginhost());
    }

    if(pSgsnAddressesReq && pSgsnAddressesReq-> has_ipaddress())
    {
        err->add_variables(pSgsnAddressesReq -> ipaddress());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFS6aMapSgsnPrefixMap_Config_Reqs(IwfS6aToMapConfig *pIwfS6aToMapConfig,IWFCfgResp *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    SgsnPrefixesConfig *pSgsnPrefixesConfigReq = NULL;
    if(pIwfS6aToMapConfig -> sgsnprefixconf_size() > iIndex && iIndex > -1)
    {
        pSgsnPrefixesConfigReq = pIwfS6aToMapConfig -> mutable_sgsnprefixconf(iIndex);
    }

    if(pSgsnPrefixesConfigReq && pSgsnPrefixesConfigReq->has_vplmnid())
    {
        err->add_variables(pSgsnPrefixesConfigReq -> vplmnid());
    }

    if(pSgsnPrefixesConfigReq && pSgsnPrefixesConfigReq-> has_sgsnprefix())
    {
        err->add_variables(pSgsnPrefixesConfigReq -> sgsnprefix());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFMapS6aVplmnIdSgsnMapConfig_protobuff(IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFMapS6aVplmnIdSgsnMap_Create_Select_Query(pIwfMapToS6aVplmnIdConfig,sStatement,-1);
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
            iReturn = GET_MAPS6ACONFIG_ERR_DB_ERROR;
        mysql_set_error_for_IWFMapS6aVplmnIdSgsnMap_Config_Reqs(pIwfMapToS6aVplmnIdConfig,resp,iReturn,-1);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            while(pRes->next())
            {
                if(!pRes->isNull("SGSN_NUMBER"))
                {
                    SgsnNumbers *pSgsnNumbersConfig = pIwfMapToS6aVplmnIdConfig -> add_sgsnnumberinfo();
                    pSgsnNumbersConfig->set_sgsnnumber(pRes->getString("SGSN_NUMBER"));
                }
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

DbStatus_e CMgrIwfDbInterface::Fill_IWFMapS6aVplmnIdConfig_protobuff(IwfMapToS6aConfig *pIwfMapToS6aConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFMapS6aVplmnId_Create_Select_Query(pIwfMapToS6aConfig,sStatement,-1);
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
            iReturn = GET_MAPS6ACONFIG_ERR_DB_ERROR;

        mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            while(pRes->next())
            {
                if(!pRes->isNull("ALLOWED_VPLMN_ID"))
                {
                    IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfig = pIwfMapToS6aConfig -> add_maptos6avplmnidinfo();
                    pIwfMapToS6aVplmnIdConfig->set_allowedvplmnid(pRes->getString("ALLOWED_VPLMN_ID"));
                    Fill_IWFMapS6aVplmnIdSgsnMapConfig_protobuff(pIwfMapToS6aVplmnIdConfig,resp);
                }
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

DbStatus_e CMgrIwfDbInterface::Fill_IWFMapS6aConfig_protobuff(IwfMapToS6aConfig *pIwfMapToS6aConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFMapS6aConfig_Create_Select_Query(pIwfMapToS6aConfig,sStatement);

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
            iReturn = GET_MAPS6ACONFIG_ERR_DB_ERROR;

        mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            while(pRes->next())
            {
                if(!pRes->isNull("IWF_TRANSLATOR_ID"))
                {
                    IwfTranslatorConfig *pIwfTranslatorConfig = pIwfMapToS6aConfig -> mutable_translatorinfo();
                    pIwfTranslatorConfig->set_translatorid(pRes->getInt("IWF_TRANSLATOR_ID"));
                }
                if(!pRes->isNull("HLR_NUMBER"))
                    pIwfMapToS6aConfig->set_hlrnumber(pRes->getString("HLR_NUMBER"));
                Fill_IWFMapS6aVplmnIdConfig_protobuff(pIwfMapToS6aConfig,resp);
            }
        }
        else
        {
            delete pRes;
            return GET_MAPS6ACONFIG_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::mysql_IWFMAPS6a_Get_Config_Reqs(IwfTranslationDataConfig *pIwfTranslationDataConfig, IWFCfgResp *resp)
{
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    IwfMapToS6aConfig LocalIwfMapToS6aConfigObj;

    if((iReturn = Fill_IWFMapS6aConfig_protobuff(&LocalIwfMapToS6aConfigObj, resp)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_MAPS6ACONFIG_ERR_DB_ERROR;
        mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(&LocalIwfMapToS6aConfigObj,resp,iReturn);
    }

    IwfTranslationDataConfig *pLocalIwfTranslationDataConfig = resp->mutable_translationdatainfo();
    IwfMapToS6aConfig *pIwfMapToS6aConfig = pLocalIwfTranslationDataConfig->mutable_maptos6ainfo();

    pIwfMapToS6aConfig->CopyFrom(LocalIwfMapToS6aConfigObj);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}

DbStatus_e CMgrIwfDbInterface::mysql_IWFS6aMAP_Get_Config_Reqs(IwfTranslationDataConfig *pIwfTranslationDataConfig, IWFCfgResp *resp)
{
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    IwfS6aToMapConfig LocalIwfS6aToMapConfigObj;

    if((iReturn = Fill_IWFS6aMapConfig_protobuff(&LocalIwfS6aToMapConfigObj, resp)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = GET_S6AMAPCONFIG_ERR_DB_ERROR;
        mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(&LocalIwfS6aToMapConfigObj,resp,iReturn);
    }

    Fill_IWFS6aMapSgsnAddrMap_protobuff(&LocalIwfS6aToMapConfigObj,resp,-1);
    Fill_IWFS6aMapSgsnPrefixMap_protobuff(&LocalIwfS6aToMapConfigObj,resp,-1);

    IwfTranslationDataConfig *pLocalIwfTranslationDataConfig = resp->mutable_translationdatainfo();
    IwfS6aToMapConfig *pIwfS6aToMapConfig = pLocalIwfTranslationDataConfig->mutable_s6atomapinfo();

    pIwfS6aToMapConfig->CopyFrom(LocalIwfS6aToMapConfigObj);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFS6aMapConfig_protobuff(IwfS6aToMapConfig *pIwfS6aToMapConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFS6aMapConfig_Create_Select_Query(pIwfS6aToMapConfig,sStatement);

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
            iReturn = GET_S6AMAPCONFIG_ERR_DB_ERROR;

        mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
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
                    IwfTranslatorConfig *pIwfTranslatorConfig = pIwfS6aToMapConfig -> mutable_translatorinfo();
                    pIwfTranslatorConfig->set_translatorid(pRes->getInt("IWF_TRANSLATOR_ID"));
                }
                if(!pRes->isNull("SGSN_NUMBER"))
                    pIwfS6aToMapConfig->set_sgsnnumber(pRes->getString("SGSN_NUMBER"));
                if(!pRes->isNull("ROUTING_PREFIX"))
                    pIwfS6aToMapConfig->set_routingprefix(pRes->getString("ROUTING_PREFIX"));
            }
        }
        else
        {
            delete pRes;
            return GET_S6AMAPCONFIG_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::mysql_IWFMAPS6a_Mod_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0}; 
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::IwfMapToS6aConfig *pIwfMapToS6aConfig = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(req->has_maptos6ainfo())
    {
        pIwfMapToS6aConfig = req->mutable_maptos6ainfo();
        if(pIwfMapToS6aConfig->has_translatorinfo())
        {
            ::IwfTranslatorConfig *pIwfTranslatorConfig = pIwfMapToS6aConfig->mutable_translatorinfo();

            sql_IWFTranslator_Create_Check_Modifcation_Query(pIwfTranslatorConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_MAPS6ACONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0)
            {
                delete pRes;
                DLOG_ERROR("Record Not Present");
                mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,MOD_MAPS6ACONFIG_ERR_TRANSLATOR_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return MOD_MAPS6ACONFIG_ERR_TRANSLATOR_NOT_PRESENT;
            }
            delete pRes;
            if(sql_IWFMapS6aConfig_Check_All_Invalid(pIwfMapToS6aConfig) == IWF_DB_FAIL)
            {
                sql_IWFMapS6aConfig_Create_Check_Modifcation_Query(pIwfMapToS6aConfig,sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {   
                    if(pRes != NULL)            
                    {   
                        delete pRes;
                    }   

                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                    if(iReturn == IWF_DB_FAIL)
                        iReturn = MOD_MAPS6ACONFIG_ERR_DB_ERROR;

                    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
                    DLOG_DEBUG("iReturn = %d",iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);           
                    return iReturn;
                }
                memset(sStatement,0,MAX_STATEMENT_SIZE);

                if(pRes->rowsCount() == 0) // ADD
                {   
                    delete pRes;
                    DLOG_ERROR("Record is not present ");
                    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,MOD_MAPS6ACONFIG_ERR_TRANSLATOR_MAPPING_NOT_PRESENT);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_MAPS6ACONFIG_ERR_TRANSLATOR_MAPPING_NOT_PRESENT;
                }
                else // MOD
                {
                    sql_IWFMapS6aConfig_Create_Mod_Query(pIwfMapToS6aConfig,sStatement);
                }

                delete pRes;

                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                {
                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                    DLOG_NONE(" < %s ",__FUNCTION__);

                    if(iReturn == IWF_DB_FAIL)
                        iReturn = MOD_MAPS6ACONFIG_ERR_DB_ERROR;

                    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
                    DLOG_DEBUG("iReturn = %d",iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
		if(pIwfMapToS6aConfig->maptos6avplmnidinfo_size() > 0)
		{
			int l_vplmn_info_size = pIwfMapToS6aConfig->maptos6avplmnidinfo_size();
			for(int index = 0; index < l_vplmn_info_size; index++)
			{
				IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfig = pIwfMapToS6aConfig->mutable_maptos6avplmnidinfo(index);
				if(pIwfMapToS6aVplmnIdConfig->has_allowedvplmnid())
				{
					memset(sStatement,0,MAX_STATEMENT_SIZE);
					sql_IWFMapS6aVplmnId_Create_Check_Modifcation_Query(pIwfMapToS6aVplmnIdConfig,sStatement);
					if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
					{   
						if(pRes != NULL)            
						{   
							delete pRes;
						}   

						DLOG_ERROR("Query Execution Failed: %s",sStatement);

						if(iReturn == IWF_DB_FAIL)
							iReturn = MOD_MAPS6ACONFIG_ERR_DB_ERROR;

						mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
						DLOG_DEBUG("iReturn = %d",iReturn);
						DLOG_NONE(" < %s ",__FUNCTION__);           
						return iReturn;
					}
					memset(sStatement,0,MAX_STATEMENT_SIZE);

					if(pRes->rowsCount() == 0)
					{
						delete pRes;
						sql_IWFMapS6aVplmnId_Create_Add_Query(pIwfMapToS6aConfig,sStatement,index);
						if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
						{
							DLOG_ERROR("Query Execution Failed: %s",sStatement);
							DLOG_NONE(" < %s ",__FUNCTION__);

							if(iReturn == IWF_DB_FAIL)
								iReturn = MOD_MAPS6ACONFIG_ERR_DB_ERROR;

							mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
							DLOG_DEBUG("iReturn = %d",iReturn);
							return iReturn;
						}

					}	
					else	
					{
						delete pRes;
						DLOG_DEBUG("VplmnId Already Present Proceeding with adding sgsn map entries");	
					}

					if(pIwfMapToS6aVplmnIdConfig->sgsnnumberinfo_size() > 0)
					{
						int sgsn_size = pIwfMapToS6aVplmnIdConfig->sgsnnumberinfo_size();
						for(int s_index = 0; s_index < sgsn_size; s_index++)
						{
							memset(sStatement,0,MAX_STATEMENT_SIZE);
							SgsnNumbers *pSgsnNumbers = pIwfMapToS6aVplmnIdConfig->mutable_sgsnnumberinfo(s_index);
							if(pSgsnNumbers->has_sgsnnumber())
							{
								sql_IWFMapS6aVplmnIdSgsnMap_Create_Check_Modifcation_Query(pIwfMapToS6aVplmnIdConfig,sStatement,s_index);
								if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
								{   
									if(pRes != NULL)            
									{   
										delete pRes;
									}   

									DLOG_ERROR("Query Execution Failed: %s",sStatement);

									if(iReturn == IWF_DB_FAIL)
										iReturn = MOD_MAPS6ACONFIG_ERR_DB_ERROR;

									mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
									DLOG_DEBUG("iReturn = %d",iReturn);
									DLOG_NONE(" < %s ",__FUNCTION__);           
									return iReturn;
								}
								memset(sStatement,0,MAX_STATEMENT_SIZE);

								if(pRes->rowsCount() == 0)
								{
								    delete pRes;
                                    sql_IWFMapS6aVplmnIdSgsnMap_Create_Check_Modifcation_Query(pSgsnNumbers,sStatement);
                                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                                    {   
                                        if(pRes != NULL)            
                                        {   
                                            delete pRes;
                                        }   

                                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                        if(iReturn == IWF_DB_FAIL)
                                            iReturn = MOD_MAPS6ACONFIG_ERR_DB_ERROR;

                                        mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
                                        DLOG_DEBUG("iReturn = %d",iReturn);
                                        DLOG_NONE(" < %s ",__FUNCTION__);           
                                        return iReturn;
                                    }
                                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                                    if(pRes->rowsCount() > 0)
                                    {
                                        delete pRes;
                                        DLOG_ERROR("Record Already Present");
                                        mysql_set_error_for_IWFMapS6aVplmnIdSgsnMap_Config_Reqs(pIwfMapToS6aVplmnIdConfig,resp,MOD_MAPS6ACONFIG_ERR_SGSN_CONFIG_ALREADY_PRESENT,s_index);
                                        DLOG_NONE(" < %s ",__FUNCTION__);
                                        return MOD_MAPS6ACONFIG_ERR_SGSN_CONFIG_ALREADY_PRESENT;
                                    }
                                    delete pRes;
									sql_IWFMapS6aVplmnIdSgsnMap_Create_Add_Query(pIwfMapToS6aVplmnIdConfig,sStatement,s_index);
								}	
								else
								{
									delete pRes;
									DLOG_ERROR("Record Already Present");
									mysql_set_error_for_IWFMapS6aVplmnIdSgsnMap_Config_Reqs(pIwfMapToS6aVplmnIdConfig,resp,ADD_MAPS6ACONFIG_ERR_ALLOWED_VPLMN_ID_SGSN_MAP_ALREADY_PRESENT,s_index);
									DLOG_NONE(" < %s ",__FUNCTION__);
									return MOD_MAPS6ACONFIG_ERR_ALLOWED_VPLMN_ID_SGSN_MAP_ALREADY_PRESENT;
								}

								if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
								{
									DLOG_ERROR("Query Execution Failed: %s",sStatement);
									DLOG_NONE(" < %s ",__FUNCTION__);

									if(iReturn == IWF_DB_FAIL)
										iReturn = MOD_MAPS6ACONFIG_ERR_DB_ERROR;

									mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
									DLOG_DEBUG("iReturn = %d",iReturn);
									return iReturn;
								}
							}
							else
							{
								iReturn = MOD_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
								mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
								DLOG_DEBUG("iReturn = %d",iReturn);
								DLOG_NONE(" < %s ",__FUNCTION__);
								return iReturn;	
							}	
						}
					}
				}	
				else
				{
					iReturn = MOD_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
					mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
					DLOG_DEBUG("iReturn = %d",iReturn);
					DLOG_NONE(" < %s ",__FUNCTION__);
					return iReturn;
				}
			}
		}
	    }
	}
        else
        {
            iReturn = MOD_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
            mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }
    else
    {
        iReturn = MOD_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
        mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFS6aMAP_Add_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0}; 
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::IwfS6aToMapConfig *pIwfS6aToMapConfig = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(req->has_s6atomapinfo())
    {
        pIwfS6aToMapConfig = req->mutable_s6atomapinfo();
        if(pIwfS6aToMapConfig->has_translatorinfo())
        {
            ::IwfTranslatorConfig *pIwfTranslatorConfig = pIwfS6aToMapConfig->mutable_translatorinfo();

            sql_IWFTranslator_Create_Check_Modifcation_Query(pIwfTranslatorConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_S6AMAPCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0)
            {
                delete pRes;
                DLOG_ERROR("Record Not Present");
                mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,ADD_S6AMAPCONFIG_ERR_TRANSLATOR_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_S6AMAPCONFIG_ERR_TRANSLATOR_NOT_PRESENT;
            }
            delete pRes;
            sql_IWFS6aMapConfig_Create_Check_Modifcation_Query(pIwfS6aToMapConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_S6AMAPCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {   
                sql_IWFS6aMapConfig_Create_Add_Query(pIwfS6aToMapConfig,sStatement);
            }
            else // MOD
            {
                delete pRes;
                DLOG_ERROR("Record Already Present");
                mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,ADD_S6AMAPCONFIG_ERR_TRANSLATOR_MAPPING_ALREADY_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_S6AMAPCONFIG_ERR_TRANSLATOR_MAPPING_ALREADY_PRESENT;
            }
            delete pRes;
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                DLOG_NONE(" < %s ",__FUNCTION__);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_S6AMAPCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            if(pIwfS6aToMapConfig->sgsnaddress_size() > 0)
            {
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                unsigned int sgsn_addr_size = pIwfS6aToMapConfig->sgsnaddress_size();
                for(unsigned int iIndex = 0; iIndex < sgsn_addr_size; iIndex++)
                {
                    memset(sStatement,0,MAX_STATEMENT_SIZE);
                    sql_IWFS6aMapSgsnAddrMap_Create_Check_Modifcation_Query(pIwfS6aToMapConfig,sStatement,iIndex);

                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                    {   
                        if(pRes != NULL)            
                        {   
                            delete pRes;
                        }   

                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = ADD_S6AMAPCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_IWFS6aMapSgsnAddrMap_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn,iIndex);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);           
                        return iReturn;
                    }
                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                    if(pRes->rowsCount() == 0) // ADD
                    {   
                        sql_IWFS6aMapSgsnAddrMap_Create_Add_Query(pIwfS6aToMapConfig,sStatement,iIndex);
                    }
                    else // MOD
                    {
                        delete pRes;
                        DLOG_ERROR("Record Already Present");
                        mysql_set_error_for_IWFS6aMapSgsnAddrMap_Config_Reqs(pIwfS6aToMapConfig,resp,ADD_S6AMAPCONFIG_ERR_S6AMAP_SGSN_ALREADY_PRESENT,iIndex);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return ADD_S6AMAPCONFIG_ERR_S6AMAP_SGSN_ALREADY_PRESENT;
                    }
                    delete pRes;
                    pRes = NULL;
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);
                        DLOG_NONE(" < %s ",__FUNCTION__);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = ADD_S6AMAPCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_IWFS6aMapSgsnAddrMap_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn,iIndex);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);           
                        return iReturn;
                    }

                }
            }
            if(pIwfS6aToMapConfig->sgsnprefixconf_size() > 0)
            {
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                unsigned int sgsn_prefix_size = pIwfS6aToMapConfig->sgsnprefixconf_size();
                for(unsigned int iIndex = 0; iIndex < sgsn_prefix_size; iIndex++)
                {
                    memset(sStatement,0,MAX_STATEMENT_SIZE);
                    sql_IWFS6aMapSgsnPrefixMap_Create_Check_Modifcation_Query(pIwfS6aToMapConfig,sStatement,iIndex);

                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                    {   
                        if(pRes != NULL)            
                        {   
                            delete pRes;
                        }   

                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = ADD_S6AMAPCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_IWFS6aMapSgsnPrefixMap_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn,iIndex);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);           
                        return iReturn;
                    }
                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                    if(pRes->rowsCount() == 0) // ADD
                    {   
                        sql_IWFS6aMapSgsnPrefixMap_Create_Add_Query(pIwfS6aToMapConfig,sStatement,iIndex);
                    }
                    else // MOD
                    {
                        delete pRes;
                        DLOG_ERROR("Record Already Present");
                        mysql_set_error_for_IWFS6aMapSgsnPrefixMap_Config_Reqs(pIwfS6aToMapConfig,resp,ADD_S6AMAPCONFIG_ERR_S6AMAP_SGSN_PREFIX_ALREADY_PRESENT,iIndex);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return ADD_S6AMAPCONFIG_ERR_S6AMAP_SGSN_PREFIX_ALREADY_PRESENT;
                    }
                    delete pRes;
                    pRes = NULL;
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);
                        DLOG_NONE(" < %s ",__FUNCTION__);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = ADD_S6AMAPCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_IWFS6aMapSgsnPrefixMap_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn,iIndex);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);           
                        return iReturn;
                    }
                }
            }
        }
        else
        {
            iReturn = ADD_S6AMAPCONFIG_ERR_DATA_NOT_PRESENT;
            mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }
    else
    {
        iReturn = ADD_S6AMAPCONFIG_ERR_DATA_NOT_PRESENT;
        mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFS6aMAP_Del_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0}; 
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::IwfS6aToMapConfig *pIwfS6aToMapConfig = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(req->has_s6atomapinfo())
    {
        pIwfS6aToMapConfig = req->mutable_s6atomapinfo();
        if(pIwfS6aToMapConfig->has_translatorinfo())
        {
            ::IwfTranslatorConfig *pIwfTranslatorConfig = pIwfS6aToMapConfig->mutable_translatorinfo();

            sql_IWFTranslator_Create_Check_Modifcation_Query(pIwfTranslatorConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_S6AMAPCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0)
            {
                delete pRes;
                DLOG_ERROR("Record Not Present");
                mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,ADD_S6AMAPCONFIG_ERR_TRANSLATOR_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_S6AMAPCONFIG_ERR_TRANSLATOR_NOT_PRESENT;
            }
            delete pRes;
            sql_IWFS6aMapConfig_Create_Check_Modifcation_Query(pIwfS6aToMapConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_S6AMAPCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {   
                delete pRes;
                DLOG_ERROR("Record Not Present");
                mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,DEL_S6AMAPCONFIG_ERR_TRANSLATOR_MAPPING_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_S6AMAPCONFIG_ERR_TRANSLATOR_MAPPING_NOT_PRESENT;
            }
            delete pRes;
            pRes = NULL;
            if(pIwfS6aToMapConfig->sgsnaddress_size() > 0)
            {
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                unsigned int sgsn_addr_size = pIwfS6aToMapConfig->sgsnaddress_size();
                for(unsigned int iIndex = 0; iIndex < sgsn_addr_size; iIndex++)
                {
                    sql_IWFS6aMapSgsnAddrMap_Create_Check_Modifcation_Query(pIwfS6aToMapConfig,sStatement,iIndex);

                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                    {   
                        if(pRes != NULL)            
                        {   
                            delete pRes;
                        }   

                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = DEL_S6AMAPCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_IWFS6aMapSgsnAddrMap_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn,iIndex);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);           
                        return iReturn;
                    }
                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                    if(pRes->rowsCount() == 0) // ADD
                    {
                        delete pRes;
                        DLOG_ERROR("Record Not Present");
                        mysql_set_error_for_IWFS6aMapSgsnAddrMap_Config_Reqs(pIwfS6aToMapConfig,resp,DEL_S6AMAPCONFIG_ERR_S6AMAP_SGSN_NOT_PRESENT,iIndex);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return DEL_S6AMAPCONFIG_ERR_S6AMAP_SGSN_NOT_PRESENT;

                    }
                    else // DEL
                    {
                        sql_IWFS6aMapSgsnAddrMap_Create_Delete_Query(pIwfS6aToMapConfig,sStatement,iIndex);
                    }
                    delete pRes;
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);
                        DLOG_NONE(" < %s ",__FUNCTION__);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = DEL_S6AMAPCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_IWFS6aMapSgsnAddrMap_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn,iIndex);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        return iReturn;
                    }

                }
            }
            if(pIwfS6aToMapConfig->sgsnprefixconf_size() > 0)
            {
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                unsigned int sgsn_prefix_size = pIwfS6aToMapConfig->sgsnprefixconf_size();
                for(unsigned int iIndex = 0; iIndex < sgsn_prefix_size; iIndex++)
                {
                    sql_IWFS6aMapSgsnPrefixMap_Create_Check_Modifcation_Query(pIwfS6aToMapConfig,sStatement,iIndex);

                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                    {   
                        if(pRes != NULL)            
                        {   
                            delete pRes;
                        }   

                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = DEL_S6AMAPCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_IWFS6aMapSgsnPrefixMap_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn,iIndex);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);           
                        return iReturn;
                    }
                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                    if(pRes->rowsCount() == 0) // ADD
                    {
                        delete pRes;
                        DLOG_ERROR("Record Not Present");
                        mysql_set_error_for_IWFS6aMapSgsnPrefixMap_Config_Reqs(pIwfS6aToMapConfig,resp,DEL_S6AMAPCONFIG_ERR_S6AMAP_SGSN_PREFIX_NOT_PRESENT,iIndex);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return DEL_S6AMAPCONFIG_ERR_S6AMAP_SGSN_PREFIX_NOT_PRESENT;

                    }
                    else // DEL
                    {
                        sql_IWFS6aMapSgsnPrefixMap_Create_Delete_Query(pIwfS6aToMapConfig,sStatement,iIndex);
                    }
                    delete pRes;
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);
                        DLOG_NONE(" < %s ",__FUNCTION__);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = DEL_S6AMAPCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_IWFS6aMapSgsnPrefixMap_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn,iIndex);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        return iReturn;
                    }
                }
            }
        }
        else
        {
            iReturn = DEL_S6AMAPCONFIG_ERR_DATA_NOT_PRESENT;
            mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }
    else
    {
        iReturn = DEL_S6AMAPCONFIG_ERR_DATA_NOT_PRESENT;
        mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFS6aMAP_Mod_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0}; 
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::IwfS6aToMapConfig *pIwfS6aToMapConfig = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(req->has_s6atomapinfo())
    {
        pIwfS6aToMapConfig = req->mutable_s6atomapinfo();
        if(pIwfS6aToMapConfig->has_translatorinfo())
        {
            ::IwfTranslatorConfig *pIwfTranslatorConfig = pIwfS6aToMapConfig->mutable_translatorinfo();

            sql_IWFTranslator_Create_Check_Modifcation_Query(pIwfTranslatorConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_S6AMAPCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0)
            {
                delete pRes;
                DLOG_ERROR("Record Not Present");
                mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,MOD_S6AMAPCONFIG_ERR_TRANSLATOR_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return MOD_S6AMAPCONFIG_ERR_TRANSLATOR_NOT_PRESENT;
            }
            delete pRes; 
            if((sql_IWFS6aMapConfig_Check_All_Invalid(pIwfS6aToMapConfig)) == IWF_DB_FAIL)
            {
                sql_IWFS6aMapConfig_Create_Check_Modifcation_Query(pIwfS6aToMapConfig,sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {   
                    if(pRes != NULL)            
                    {   
                        delete pRes;
                    }   

                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                    if(iReturn == IWF_DB_FAIL)
                        iReturn = MOD_S6AMAPCONFIG_ERR_DB_ERROR;

                    mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
                    DLOG_DEBUG("iReturn = %d",iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);           
                    return iReturn;
                }
                memset(sStatement,0,MAX_STATEMENT_SIZE);

                if(pRes->rowsCount() == 0) // ADD
                {   
                    delete pRes;
                    DLOG_ERROR("Record Not Present");
                    mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,MOD_S6AMAPCONFIG_ERR_TRANSLATOR_MAPPING_NOT_PRESENT);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_S6AMAPCONFIG_ERR_TRANSLATOR_MAPPING_NOT_PRESENT;
                }
                else // MOD
                {
                    sql_IWFS6aMapConfig_Create_Mod_Query(pIwfS6aToMapConfig,sStatement);
                }
                delete pRes;
                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                {
                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                    DLOG_NONE(" < %s ",__FUNCTION__);

                    if(iReturn == IWF_DB_FAIL)
                        iReturn = MOD_S6AMAPCONFIG_ERR_DB_ERROR;

                    mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
                    DLOG_DEBUG("iReturn = %d",iReturn);
                    return iReturn;
                }
            }

            if(pIwfS6aToMapConfig->sgsnaddress_size() > 0)
            {
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                unsigned int sgsn_addr_size = pIwfS6aToMapConfig->sgsnaddress_size();
                for(unsigned int iIndex = 0; iIndex < sgsn_addr_size; iIndex++)
                {
                    sql_IWFS6aMapSgsnAddrMap_Create_Check_Modifcation_Query(pIwfS6aToMapConfig,sStatement,iIndex);

                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                    {   
                        if(pRes != NULL)            
                        {   
                            delete pRes;
                        }   

                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = MOD_S6AMAPCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_IWFS6aMapSgsnAddrMap_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn,iIndex);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);           
                        return iReturn;
                    }
                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                    if(pRes->rowsCount() == 0) // ADD
                    {   
                        sql_IWFS6aMapSgsnAddrMap_Create_Add_Query(pIwfS6aToMapConfig,sStatement,iIndex);
                    }
                    else // MOD
                    {
                        delete pRes;
                        DLOG_ERROR("Record Already Present");
                        mysql_set_error_for_IWFS6aMapSgsnAddrMap_Config_Reqs(pIwfS6aToMapConfig,resp,MOD_S6AMAPCONFIG_ERR_S6AMAP_SGSN_ALREADY_PRESENT,iIndex);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return MOD_S6AMAPCONFIG_ERR_S6AMAP_SGSN_ALREADY_PRESENT;
                    }
                    delete pRes;
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);
                        DLOG_NONE(" < %s ",__FUNCTION__);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = MOD_S6AMAPCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_IWFS6aMapSgsnAddrMap_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn,iIndex);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        return iReturn;
                    }

                }
            }
            if(pIwfS6aToMapConfig->sgsnprefixconf_size() > 0)
            {
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                unsigned int sgsn_prefix_size = pIwfS6aToMapConfig->sgsnprefixconf_size();
                for(unsigned int iIndex = 0; iIndex < sgsn_prefix_size; iIndex++)
                {
                    sql_IWFS6aMapSgsnPrefixMap_Create_Check_Modifcation_Query(pIwfS6aToMapConfig,sStatement,iIndex);

                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                    {   
                        if(pRes != NULL)            
                        {   
                            delete pRes;
                        }   

                        DLOG_ERROR("Query Execution Failed: %s",sStatement);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = MOD_S6AMAPCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_IWFS6aMapSgsnPrefixMap_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn,iIndex);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);           
                        return iReturn;
                    }
                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                    if(pRes->rowsCount() == 0) // ADD
                    {   
                        sql_IWFS6aMapSgsnPrefixMap_Create_Add_Query(pIwfS6aToMapConfig,sStatement,iIndex);
                    }
                    else // MOD
                    {
                        delete pRes;
                        DLOG_ERROR("Record Already Present");
                        mysql_set_error_for_IWFS6aMapSgsnPrefixMap_Config_Reqs(pIwfS6aToMapConfig,resp,MOD_S6AMAPCONFIG_ERR_S6AMAP_SGSN_PREFIX_ALREADY_PRESENT,iIndex);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return MOD_S6AMAPCONFIG_ERR_S6AMAP_SGSN_PREFIX_ALREADY_PRESENT;
                    }
                    delete pRes;
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                    {
                        DLOG_ERROR("Query Execution Failed: %s",sStatement);
                        DLOG_NONE(" < %s ",__FUNCTION__);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = MOD_S6AMAPCONFIG_ERR_DB_ERROR;

                        mysql_set_error_for_IWFS6aMapSgsnPrefixMap_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn,iIndex);
                        DLOG_DEBUG("iReturn = %d",iReturn);
                        return iReturn;
                    }
                }
            }
        }
        else
        {
            iReturn = MOD_S6AMAPCONFIG_ERR_DATA_NOT_PRESENT;
            mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }
    else
    {
        iReturn = MOD_S6AMAPCONFIG_ERR_DATA_NOT_PRESENT;
        mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFMAPS6aVplmnId_Del_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0}; 
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::IwfMapToS6aConfig *pIwfMapToS6aConfig = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    if(req->has_maptos6ainfo())
    {
        pIwfMapToS6aConfig = req->mutable_maptos6ainfo();
        if(pIwfMapToS6aConfig->has_translatorinfo())
        {
            ::IwfTranslatorConfig *pIwfTranslatorConfig = pIwfMapToS6aConfig->mutable_translatorinfo();

            sql_IWFTranslator_Create_Check_Modifcation_Query(pIwfTranslatorConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_MAPS6ACONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);
	    if(pRes->rowsCount() == 0)
            {
                delete pRes;
                DLOG_ERROR("Record Not Present");
                mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,DEL_MAPS6ACONFIG_ERR_TRANSLATOR_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_MAPS6ACONFIG_ERR_TRANSLATOR_NOT_PRESENT;
            }
            delete pRes;
            sql_IWFMapS6aConfig_Create_Check_Modifcation_Query(pIwfMapToS6aConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_MAPS6ACONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {   
                delete pRes;
                DLOG_ERROR("Record Not Present");
                mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,DEL_MAPS6ACONFIG_ERR_TRANSLATOR_MAPPING_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_MAPS6ACONFIG_ERR_TRANSLATOR_MAPPING_NOT_PRESENT;
            }
		delete pRes;
		if(pIwfMapToS6aConfig->maptos6avplmnidinfo_size() > 0)
		{
			//Need to be Implemented for vplmn-id configuration addition
			int l_vplmn_info_size = pIwfMapToS6aConfig->maptos6avplmnidinfo_size();
			for(int index = 0; index < l_vplmn_info_size; index++)
			{
				IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfig = pIwfMapToS6aConfig->mutable_maptos6avplmnidinfo(index);
				if(pIwfMapToS6aVplmnIdConfig->has_allowedvplmnid())
				{
					memset(sStatement,0,MAX_STATEMENT_SIZE);
					sql_IWFMapS6aVplmnId_Create_Check_Modifcation_Query(pIwfMapToS6aVplmnIdConfig,sStatement);
					if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
					{   
						if(pRes != NULL)            
						{   
							delete pRes;
						}   

						DLOG_ERROR("Query Execution Failed: %s",sStatement);

						if(iReturn == IWF_DB_FAIL)
							iReturn = DEL_MAPS6ACONFIG_ERR_DB_ERROR;

						mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
						DLOG_DEBUG("iReturn = %d",iReturn);
						DLOG_NONE(" < %s ",__FUNCTION__);           
						return iReturn;
					}
					memset(sStatement,0,MAX_STATEMENT_SIZE);

					if(pRes->rowsCount() == 0)
					{
						delete pRes;
						DLOG_ERROR("Record Not Present");
						mysql_set_error_for_IWFMapS6aVplmnId_Config_Reqs(pIwfMapToS6aConfig,resp,DEL_MAPS6ACONFIG_ERR_ALLOWED_VPLMN_ID_NOT_PRESENT,index);
						DLOG_NONE(" < %s ",__FUNCTION__);
						return DEL_MAPS6ACONFIG_ERR_ALLOWED_VPLMN_ID_NOT_PRESENT;
					}
					delete pRes;
					sql_IWFMapS6aVplmnId_Create_Delete_Query(pIwfMapToS6aVplmnIdConfig,sStatement);
					if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
					{
						DLOG_ERROR("Query Execution Failed: %s",sStatement);
						DLOG_NONE(" < %s ",__FUNCTION__);

						if(iReturn == IWF_DB_FAIL)
							iReturn = DEL_MAPS6ACONFIG_ERR_DB_ERROR;

						mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
						DLOG_DEBUG("iReturn = %d",iReturn);
						return iReturn;
					}

				}
				else
				{
					iReturn = DEL_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
					mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
					DLOG_DEBUG("iReturn = %d",iReturn);
					DLOG_NONE(" < %s ",__FUNCTION__);
					return iReturn;
				}
			}
		}
	}
	else
	{
		iReturn = DEL_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
		mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
		DLOG_DEBUG("iReturn = %d",iReturn);
		DLOG_NONE(" < %s ",__FUNCTION__);
		return iReturn;
	}
    }
    else
    {
	    iReturn = DEL_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
	    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
	    DLOG_NONE(" < %s ",__FUNCTION__);
	    return iReturn;
    }
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFMAPS6aVplmnIdSgsnMap_Del_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0}; 
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::IwfMapToS6aConfig *pIwfMapToS6aConfig = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);
    if(req->has_maptos6ainfo())
    {
	    pIwfMapToS6aConfig = req->mutable_maptos6ainfo();
	    if(pIwfMapToS6aConfig->has_translatorinfo())
	    {
		    ::IwfTranslatorConfig *pIwfTranslatorConfig = pIwfMapToS6aConfig->mutable_translatorinfo();

		    sql_IWFTranslator_Create_Check_Modifcation_Query(pIwfTranslatorConfig,sStatement);

		    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		    {   
			    if(pRes != NULL)            
			    {   
				    delete pRes;
			    }   

			    DLOG_ERROR("Query Execution Failed: %s",sStatement);

			    if(iReturn == IWF_DB_FAIL)
				    iReturn = DEL_MAPS6ACONFIG_ERR_DB_ERROR;

			    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
			    DLOG_DEBUG("iReturn = %d",iReturn);
			    DLOG_NONE(" < %s ",__FUNCTION__);           
			    return iReturn;
		    }
		    memset(sStatement,0,MAX_STATEMENT_SIZE);
		    if(pRes->rowsCount() == 0)
		    {
			    delete pRes;
			    DLOG_ERROR("Record Not Present");
			    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,DEL_MAPS6ACONFIG_ERR_TRANSLATOR_NOT_PRESENT);
			    DLOG_NONE(" < %s ",__FUNCTION__);
			    return DEL_MAPS6ACONFIG_ERR_TRANSLATOR_NOT_PRESENT;
		    }
		    delete pRes;
		    sql_IWFMapS6aConfig_Create_Check_Modifcation_Query(pIwfMapToS6aConfig,sStatement);
		    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		    {   
			    if(pRes != NULL)            
			    {   
				    delete pRes;
			    }   

			    DLOG_ERROR("Query Execution Failed: %s",sStatement);

			    if(iReturn == IWF_DB_FAIL)
				    iReturn = DEL_MAPS6ACONFIG_ERR_DB_ERROR;

			    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
			    DLOG_DEBUG("iReturn = %d",iReturn);
			    DLOG_NONE(" < %s ",__FUNCTION__);           
			    return iReturn;
		    }
		    memset(sStatement,0,MAX_STATEMENT_SIZE);

		    if(pRes->rowsCount() == 0) // ADD
		    {   
			    delete pRes;
			    DLOG_ERROR("Record Not Present");
			    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,DEL_MAPS6ACONFIG_ERR_TRANSLATOR_MAPPING_NOT_PRESENT);
			    DLOG_NONE(" < %s ",__FUNCTION__);
			    return DEL_MAPS6ACONFIG_ERR_TRANSLATOR_MAPPING_NOT_PRESENT;
		    }
		    delete pRes;
		    if(pIwfMapToS6aConfig->maptos6avplmnidinfo_size() > 0)
		    {
			    //Need to be Implemented for vplmn-id configuration addition
			    int l_vplmn_info_size = pIwfMapToS6aConfig->maptos6avplmnidinfo_size();
			    for(int index = 0; index < l_vplmn_info_size; index++)
			    {
				    IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfig = pIwfMapToS6aConfig->mutable_maptos6avplmnidinfo(index);
				    if(pIwfMapToS6aVplmnIdConfig->has_allowedvplmnid())
				    {
					    memset(sStatement,0,MAX_STATEMENT_SIZE);
					    sql_IWFMapS6aVplmnId_Create_Check_Modifcation_Query(pIwfMapToS6aVplmnIdConfig,sStatement);
					    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
					    {   
						    if(pRes != NULL)            
						    {   
							    delete pRes;
						    }   

						    DLOG_ERROR("Query Execution Failed: %s",sStatement);

						    if(iReturn == IWF_DB_FAIL)
							    iReturn = DEL_MAPS6ACONFIG_ERR_DB_ERROR;

						    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
						    DLOG_DEBUG("iReturn = %d",iReturn);
						    DLOG_NONE(" < %s ",__FUNCTION__);           
						    return iReturn;
					    }
					    memset(sStatement,0,MAX_STATEMENT_SIZE);

					    if(pRes->rowsCount() == 0)
					    {
						    delete pRes;
						    DLOG_ERROR("Record Not Present");
						    mysql_set_error_for_IWFMapS6aVplmnId_Config_Reqs(pIwfMapToS6aConfig,resp,DEL_MAPS6ACONFIG_ERR_ALLOWED_VPLMN_ID_NOT_PRESENT,index);
						    DLOG_NONE(" < %s ",__FUNCTION__);
						    return DEL_MAPS6ACONFIG_ERR_ALLOWED_VPLMN_ID_NOT_PRESENT;
					    }
					    delete pRes;
					    if(pIwfMapToS6aVplmnIdConfig->sgsnnumberinfo_size() > 0)
					    {
						    int sgsn_size = pIwfMapToS6aVplmnIdConfig->sgsnnumberinfo_size();
						    for(int s_index = 0; s_index < sgsn_size; s_index++)
						    {
							    memset(sStatement,0,MAX_STATEMENT_SIZE);
							    SgsnNumbers *pSgsnNumbers = pIwfMapToS6aVplmnIdConfig->mutable_sgsnnumberinfo(s_index);
							    if(pSgsnNumbers->has_sgsnnumber())
							    {
								    sql_IWFMapS6aVplmnIdSgsnMap_Create_Check_Modifcation_Query(pIwfMapToS6aVplmnIdConfig,sStatement,s_index);
								    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
								    {   
									    if(pRes != NULL)            
									    {   
										    delete pRes;
									    }   

									    DLOG_ERROR("Query Execution Failed: %s",sStatement);

									    if(iReturn == IWF_DB_FAIL)
										    iReturn = DEL_MAPS6ACONFIG_ERR_DB_ERROR;

									    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
									    DLOG_DEBUG("iReturn = %d",iReturn);
									    DLOG_NONE(" < %s ",__FUNCTION__);           
									    return iReturn;
								    }
								    memset(sStatement,0,MAX_STATEMENT_SIZE);

								    if(pRes->rowsCount() == 0)
								    {
									    delete pRes;
									    DLOG_ERROR("Record Not Present");
									    mysql_set_error_for_IWFMapS6aVplmnIdSgsnMap_Config_Reqs(pIwfMapToS6aVplmnIdConfig,resp,DEL_MAPS6ACONFIG_ERR_ALLOWED_VPLMN_ID_SGSN_MAP_NOT_PRESENT,s_index);
									    DLOG_NONE(" < %s ",__FUNCTION__);
									    return DEL_MAPS6ACONFIG_ERR_ALLOWED_VPLMN_ID_SGSN_MAP_NOT_PRESENT;
								    }
								    delete pRes;

								    sql_IWFMapS6aVplmnIdSgsnMap_Create_Delete_Query(pIwfMapToS6aVplmnIdConfig,sStatement,s_index);
								    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
								    {
									    DLOG_ERROR("Query Execution Failed: %s",sStatement);
									    DLOG_NONE(" < %s ",__FUNCTION__);

									    if(iReturn == IWF_DB_FAIL)
										    iReturn = DEL_MAPS6ACONFIG_ERR_DB_ERROR;

									    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
									    DLOG_DEBUG("iReturn = %d",iReturn);
									    return iReturn;
								    }
							    }
							    else
							    {
								    iReturn = DEL_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
								    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
								    DLOG_DEBUG("iReturn = %d",iReturn);
								    DLOG_NONE(" < %s ",__FUNCTION__);
								    return iReturn;	
							    }	
						    }
					    }
					    else
					    {
						    iReturn = DEL_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
						    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
						    DLOG_DEBUG("iReturn = %d",iReturn);
						    DLOG_NONE(" < %s ",__FUNCTION__);
						    return iReturn;
					    }
				    }
			    }
		    }
	}
	else
	{
		iReturn = DEL_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
		mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
		DLOG_DEBUG("iReturn = %d",iReturn);
		DLOG_NONE(" < %s ",__FUNCTION__);
		return iReturn;
	}
    }
    else
    {
	    iReturn = DEL_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
	    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
	    DLOG_NONE(" < %s ",__FUNCTION__);
	    return iReturn;
    }
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFMAPS6a_Add_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0}; 
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::IwfMapToS6aConfig *pIwfMapToS6aConfig = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(req->has_maptos6ainfo())
    {
        pIwfMapToS6aConfig = req->mutable_maptos6ainfo();
        if(pIwfMapToS6aConfig->has_translatorinfo())
        {
            ::IwfTranslatorConfig *pIwfTranslatorConfig = pIwfMapToS6aConfig->mutable_translatorinfo();

            sql_IWFTranslator_Create_Check_Modifcation_Query(pIwfTranslatorConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_MAPS6ACONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0)
            {
                delete pRes;
                DLOG_ERROR("Record Not Present");
                mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,ADD_MAPS6ACONFIG_ERR_TRANSLATOR_NOT_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_MAPS6ACONFIG_ERR_TRANSLATOR_NOT_PRESENT;
            }
            delete pRes;
            sql_IWFMapS6aConfig_Create_Check_Modifcation_Query(pIwfMapToS6aConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {   
                if(pRes != NULL)            
                {   
                    delete pRes;
                }   

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_MAPS6ACONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);           
                return iReturn;
            }
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {   
                sql_IWFMapS6aConfig_Create_Add_Query(pIwfMapToS6aConfig,sStatement);
            }
            else // MOD
            {

                delete pRes;
                DLOG_ERROR("Record Already Present");
                mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,ADD_MAPS6ACONFIG_ERR_TRANSLATOR_MAPPING_ALREADY_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_MAPS6ACONFIG_ERR_TRANSLATOR_MAPPING_ALREADY_PRESENT;
            }

            delete pRes;

            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                DLOG_NONE(" < %s ",__FUNCTION__);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_MAPS6ACONFIG_ERR_DB_ERROR;

                mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                return iReturn;
            }

	    if(pIwfMapToS6aConfig->maptos6avplmnidinfo_size() > 0)
	    {
		//Need to be Implemented for vplmn-id configuration addition
		int l_vplmn_info_size = pIwfMapToS6aConfig->maptos6avplmnidinfo_size();
		for(int index = 0; index < l_vplmn_info_size; index++)
		{
			IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfig = pIwfMapToS6aConfig->mutable_maptos6avplmnidinfo(index);
			if(pIwfMapToS6aVplmnIdConfig->has_allowedvplmnid())
			{
				memset(sStatement,0,MAX_STATEMENT_SIZE);
				sql_IWFMapS6aVplmnId_Create_Check_Modifcation_Query(pIwfMapToS6aVplmnIdConfig,sStatement);
				if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
				{   
					if(pRes != NULL)            
					{   
						delete pRes;
					}   

					DLOG_ERROR("Query Execution Failed: %s",sStatement);

					if(iReturn == IWF_DB_FAIL)
						iReturn = ADD_MAPS6ACONFIG_ERR_DB_ERROR;

					mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
					DLOG_DEBUG("iReturn = %d",iReturn);
					DLOG_NONE(" < %s ",__FUNCTION__);           
					return iReturn;
				}
				memset(sStatement,0,MAX_STATEMENT_SIZE);

				if(pRes->rowsCount() == 0)
				{
					sql_IWFMapS6aVplmnId_Create_Add_Query(pIwfMapToS6aConfig,sStatement,index);
				}	
				else
				{
					delete pRes;
					DLOG_ERROR("Record Already Present");
					mysql_set_error_for_IWFMapS6aVplmnId_Config_Reqs(pIwfMapToS6aConfig,resp,ADD_MAPS6ACONFIG_ERR_ALLOWED_VPLMN_ID_ALREADY_PRESENT,index);
					DLOG_NONE(" < %s ",__FUNCTION__);
					return ADD_MAPS6ACONFIG_ERR_ALLOWED_VPLMN_ID_ALREADY_PRESENT;
				}
				delete pRes;

				if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
				{
					DLOG_ERROR("Query Execution Failed: %s",sStatement);
					DLOG_NONE(" < %s ",__FUNCTION__);

					if(iReturn == IWF_DB_FAIL)
						iReturn = ADD_MAPS6ACONFIG_ERR_DB_ERROR;

					mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
					DLOG_DEBUG("iReturn = %d",iReturn);
					return iReturn;
				}
				
				if(pIwfMapToS6aVplmnIdConfig->sgsnnumberinfo_size() > 0)
				{
					int sgsn_size = pIwfMapToS6aVplmnIdConfig->sgsnnumberinfo_size();
					for(int s_index = 0; s_index < sgsn_size; s_index++)
					{
						memset(sStatement,0,MAX_STATEMENT_SIZE);
						SgsnNumbers *pSgsnNumbers = pIwfMapToS6aVplmnIdConfig->mutable_sgsnnumberinfo(s_index);
						if(pSgsnNumbers->has_sgsnnumber())
						{
							sql_IWFMapS6aVplmnIdSgsnMap_Create_Check_Modifcation_Query(pIwfMapToS6aVplmnIdConfig,sStatement,s_index);
							if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
							{   
								if(pRes != NULL)            
								{   
									delete pRes;
								}   

								DLOG_ERROR("Query Execution Failed: %s",sStatement);

								if(iReturn == IWF_DB_FAIL)
									iReturn = ADD_MAPS6ACONFIG_ERR_DB_ERROR;

								mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
								DLOG_DEBUG("iReturn = %d",iReturn);
								DLOG_NONE(" < %s ",__FUNCTION__);           
								return iReturn;
							}
							memset(sStatement,0,MAX_STATEMENT_SIZE);

                            if(pRes->rowsCount() == 0)
                            {
                                delete pRes;
                                sql_IWFMapS6aVplmnIdSgsnMap_Create_Check_Modifcation_Query(pSgsnNumbers,sStatement);
                                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                                {   
                                    if(pRes != NULL)            
                                    {   
                                        delete pRes;
                                    }   

                                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                                    if(iReturn == IWF_DB_FAIL)
                                        iReturn = MOD_MAPS6ACONFIG_ERR_DB_ERROR;

                                    mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
                                    DLOG_DEBUG("iReturn = %d",iReturn);
                                    DLOG_NONE(" < %s ",__FUNCTION__);           
                                    return iReturn;
                                }
                                memset(sStatement,0,MAX_STATEMENT_SIZE);

                                if(pRes->rowsCount() > 0)
                                {
                                    delete pRes;
                                    DLOG_ERROR("Record Already Present");
                                    mysql_set_error_for_IWFMapS6aVplmnIdSgsnMap_Config_Reqs(pIwfMapToS6aVplmnIdConfig,resp,ADD_MAPS6ACONFIG_ERR_SGSN_CONFIG_ALREADY_PRESENT,s_index);
                                    DLOG_NONE(" < %s ",__FUNCTION__);
                                    return ADD_MAPS6ACONFIG_ERR_SGSN_CONFIG_ALREADY_PRESENT;
                                }
                                delete pRes;

                                sql_IWFMapS6aVplmnIdSgsnMap_Create_Add_Query(pIwfMapToS6aVplmnIdConfig,sStatement,s_index);
                            }	
                            else
                            {
                                delete pRes;
                                DLOG_ERROR("Record Already Present");
                                mysql_set_error_for_IWFMapS6aVplmnIdSgsnMap_Config_Reqs(pIwfMapToS6aVplmnIdConfig,resp,ADD_MAPS6ACONFIG_ERR_ALLOWED_VPLMN_ID_SGSN_MAP_ALREADY_PRESENT,s_index);
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return ADD_MAPS6ACONFIG_ERR_ALLOWED_VPLMN_ID_SGSN_MAP_ALREADY_PRESENT;
                            }

							if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
							{
								DLOG_ERROR("Query Execution Failed: %s",sStatement);
								DLOG_NONE(" < %s ",__FUNCTION__);

								if(iReturn == IWF_DB_FAIL)
									iReturn = ADD_MAPS6ACONFIG_ERR_DB_ERROR;

								mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
								DLOG_DEBUG("iReturn = %d",iReturn);
								return iReturn;
							}
						}
						else
						{
							iReturn = ADD_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
							mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
							DLOG_DEBUG("iReturn = %d",iReturn);
							DLOG_NONE(" < %s ",__FUNCTION__);
							return iReturn;	
						}	
					}
				}
			}	
			else
			{
				iReturn = ADD_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
				mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
				DLOG_DEBUG("iReturn = %d",iReturn);
				DLOG_NONE(" < %s ",__FUNCTION__);
				return iReturn;
			}
		}
	    }
        }
        else
        {
            iReturn = ADD_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
            mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }
    else
    {
        iReturn = ADD_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT;
        mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(pIwfMapToS6aConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFS6aMapSgsnAddrMap_protobuff(IwfS6aToMapConfig *pIwfS6aToMapConfig,IWFCfgResp *resp,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFS6aMapSgsnAddrMap_Create_Select_Query(pIwfS6aToMapConfig,sStatement,iIndex);

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
            iReturn = GET_S6AMAPCONFIG_ERR_DB_ERROR;

        mysql_set_error_for_IWFS6aMapSgsnAddrMap_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn,iIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    SgsnAddresses *pSgsnAddresses = NULL;

    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            while(pRes->next())
            {
                if(pIwfS6aToMapConfig->sgsnaddress_size() > iIndex && iIndex > -1)
                {
                    pSgsnAddresses = pIwfS6aToMapConfig -> mutable_sgsnaddress(iIndex);
                }
                else
                {
                    pSgsnAddresses = pIwfS6aToMapConfig -> add_sgsnaddress();
                }
                if(!pRes->isNull("IWF_S6AMAP_CONFIG_ID"))
                {
                    pIwfS6aToMapConfig->set_s6atomapid(pRes->getInt("IWF_S6AMAP_CONFIG_ID"));
                }
                if(!pRes->isNull("ORIGIN_HOST"))
                {
                    pSgsnAddresses->set_orginhost(pRes->getString("ORIGIN_HOST"));
                }
                if(!pRes->isNull("IPADDRESS"))
                {
                    pSgsnAddresses->set_ipaddress(pRes->getString("IPADDRESS"));
                }
            }
        }
        else
        {
            delete pRes;
            return GET_S6AMAP_SGSNADDR_CONFIG_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::Fill_IWFS6aMapSgsnPrefixMap_protobuff(IwfS6aToMapConfig *pIwfS6aToMapConfig,IWFCfgResp *resp,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFS6aMapSgsnPrefixMap_Create_Select_Query(pIwfS6aToMapConfig,sStatement,iIndex);

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
            iReturn = GET_S6AMAPCONFIG_ERR_DB_ERROR;

        mysql_set_error_for_IWFS6aMapSgsnPrefixMap_Config_Reqs(pIwfS6aToMapConfig,resp,iReturn,iIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    SgsnPrefixesConfig *pSgsnPrefix = NULL;

    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            while(pRes->next())
            {
                if(pIwfS6aToMapConfig->sgsnprefixconf_size() > iIndex && iIndex > -1)
                {
                    pSgsnPrefix = pIwfS6aToMapConfig -> mutable_sgsnprefixconf(iIndex);
                }
                else
                {
                    pSgsnPrefix = pIwfS6aToMapConfig -> add_sgsnprefixconf();
                }
                if(!pRes->isNull("IWF_S6AMAP_CONFIG_ID"))
                {
                    pIwfS6aToMapConfig->set_s6atomapid(pRes->getInt("IWF_S6AMAP_CONFIG_ID"));
                }
                if(!pRes->isNull("VPLMN_ID"))
                {
                    pSgsnPrefix->set_vplmnid(pRes->getString("VPLMN_ID"));
                }
                if(!pRes->isNull("SGSN_PREFIX"))
                {
                    pSgsnPrefix->set_sgsnprefix(pRes->getString("SGSN_PREFIX"));
                }
            }
        }
        else
        {
            delete pRes;
            return GET_S6AMAP_SGSNADDR_CONFIG_ERR_NO_DATA;
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
