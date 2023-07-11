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

void CMgrDbInterface::mysql_set_error_for_LocalTransportTag_Config_Reqs(LocalTransportTagRequest *req,LocalTransportTagResponse *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_StaticRouting_Config_Reqs(StaticRoutingTableConfig *pStaticRoutingTableConfig,StaticRoutingTableConfigResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pStaticRoutingTableConfig->has_destionatinhost())
        err->add_variables(pStaticRoutingTableConfig->destionatinhost());
    if(pStaticRoutingTableConfig->has_destionatinrealm())
        err->add_variables(pStaticRoutingTableConfig->destionatinrealm());
    if(pStaticRoutingTableConfig->has_peer())
        err->add_variables(pStaticRoutingTableConfig->peer());
    if(pStaticRoutingTableConfig->has_realm())
        err->add_variables(pStaticRoutingTableConfig->realm());
    if(pStaticRoutingTableConfig->has_applicationid())
    {
        char sStr[10];
        if(pStaticRoutingTableConfig->applicationid() == 0)
        {
            snprintf(sStr,10,"NULL");
        }
        else
        {
            snprintf(sStr,10,"%d",pStaticRoutingTableConfig->applicationid());
        }
        err->add_variables(sStr);
    }
    else
    {
        char sStr[10];
        snprintf(sStr,10,"NULL");
        err->add_variables(sStr);
    }


    DLOG_NONE(" < %s ",__FUNCTION__);
}


void CMgrDbInterface::mysql_set_error_for_LocalHost_Config_Reqs(::LocalHost *pLocalHost, StackConfigResponse *resp,DbStatus_e iReturn)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pLocalHost->has_localhostname())
	    err->add_variables(pLocalHost->localhostname().c_str());

    if(pLocalHost->has_realmname())
	    err->add_variables(pLocalHost->realmname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

//void CMgrDbInterface::mysql_set_error_for_Common_Config_Reqs(::SctpProtocol *pSctpProtocol, StackConfigResponse *resp,DbStatus_e iReturn)


void CMgrDbInterface::mysql_set_error_for_TrustedCAConfig_Config_Reqs(::TrustedCAConfiguration *pTrustedCAConfiguration, StackConfigResponse *resp,DbStatus_e iReturn)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pTrustedCAConfiguration->has_cafile())
        err->add_variables(pTrustedCAConfiguration->cafile().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}


void CMgrDbInterface::mysql_set_error_for_Common_Config_Reqs(StackConfigResponse *resp,DbStatus_e iReturn)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_CipherSuiteConfig_Config_Reqs(::TLSCipherConfig *pTLSCipherConfig, StackConfigResponse *resp,DbStatus_e iReturn)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pTLSCipherConfig->has_ciphersuitename())
        err->add_variables(pTLSCipherConfig->ciphersuitename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}


void CMgrDbInterface::mysql_set_error_for_MultiHoming_Config_Reqs(::LHTransport *pLHTransport, StackConfigResponse *resp,DbStatus_e iReturn,int iIndex)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    char sPort[10];
    char sSecondaryIP[10];
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
    string *sSecondaryIp;

    if(iIndex != -1)
	    sSecondaryIp = pLHTransport->mutable_secondaryipaddr(iIndex);

    if(pLHTransport->has_hostipaddr())
	    err->add_variables(pLHTransport->hostipaddr().c_str());

    if(pLHTransport->has_port())
    {
        snprintf(sPort,10,"%d",pLHTransport->port());
	    err->add_variables(sPort);
    }

    if(iReturn == ADD_HOST_MULTIHOMING_SECONDARY_IP_REACHED_MAX_LIMIT)
    {
       snprintf(sSecondaryIP,10,"%d",MAX_SECONDARY_IP_SUPPORTED);
       err->add_variables(sSecondaryIP);
    }

    if(iIndex != -1)
    {
        err->add_variables(*sSecondaryIp);
    }

    if(pLHTransport->has_transportslot())
    {
        char sSlot[10];
        snprintf(sSlot,10,"%d",pLHTransport->transportslot());
        err->add_variables(sSlot);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}



void CMgrDbInterface::mysql_set_error_for_LHTransport_Config_Reqs(::LocalHost *pLocalHost, StackConfigResponse *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    char sSlot[10];
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    ::LHTransport *pLHTransport;
    if(iIndex != -1)
	    pLHTransport = pLocalHost->mutable_transports(iIndex);

    if(pLocalHost->has_localhostname())
	    err->add_variables(pLocalHost->localhostname().c_str());

    if(pLocalHost->has_realmname())
	    err->add_variables(pLocalHost->realmname().c_str());

    if(iIndex != -1)
    {
	    if(pLHTransport->has_transportslot())
	    {
		    snprintf(sSlot,10,"%d",pLHTransport->transportslot());
		    err->add_variables(sSlot);
	    }
    }

    {
	    LHTransport* localTransport = pLocalHost->mutable_transports(iIndex);

	    LocalHost LocalLocalHostObj;
	    LHTransport *plocalTransport=LocalLocalHostObj.add_transports();
	    plocalTransport->set_transporttype(localTransport->transporttype());
	    plocalTransport->set_secureport(localTransport->secureport());
	    plocalTransport->set_port(localTransport->port());
	    plocalTransport->set_hostipaddr(localTransport->hostipaddr());

	    sql_LocalTransport_Create_Select_Query(&LocalLocalHostObj,sStatement,iIndex);
	    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
	    {
		    if(pRes != NULL)	
		    {
			    delete pRes;
		    }

		    DLOG_NONE(" < %s ",__FUNCTION__);
		    return;
	    }

	    if(pRes->rowsCount() > 0)
	    {
		if(pRes->next())
		{
			if(!pRes->isNull("TRANSPORT_ID"))
                 	  	err->add_variables(pRes->getString("TRANSPORT_ID"));
		}
	    }
	    delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_LocalHost_Get_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	::LocalHost *pLocalHost;
	::LocalHost localLocalHost;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	DLOG_NONE(" > %s ",__FUNCTION__);

	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_lhost())
	{

		pLocalHost = pStackConfiguration->mutable_lhost();

		sql_LocalHostAndTransport_Create_Select_Query(pLocalHost,sStatement);
		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)	
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = GET_HOST_ERR_DB_ERROR;

			mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,iReturn);

			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}

		if((iReturn = mysql_LocalHost_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
		{
			delete pRes;
			mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}


		delete pRes;
	}
	else
	{
		pLocalHost = &localLocalHost;

		sql_LocalHostAndTransport_Create_Select_Query(pLocalHost,sStatement);
		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)	
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = GET_HOST_ERR_DB_ERROR;

			mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}

		if((iReturn = mysql_LocalHost_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
		{
			delete pRes;
			mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}


		delete pRes;

	}

	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_LocalTransportTagConfig_Get_Config_Reqs(LocalTransportTagRequest *req, LocalTransportTagResponse *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    ::LHTransport *pLHTransport;
    ::LHTransport localLHTransport;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;


    pLHTransport = &localLHTransport;

    sql_LocalTransportTag_Create_Select_Query(pLHTransport,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = GET_SCTPCONFIG_ERR_DB_ERROR;

        mysql_set_error_for_LocalTransportTag_Config_Reqs(req,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if((iReturn = mysql_LocalTransportTag_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
    {
        delete pRes;

        mysql_set_error_for_LocalTransportTag_Config_Reqs(req,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }


    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_StaticRoutingTableConfig_Get_Config_Reqs(StaticRoutingTableConfigReq *req, StaticRoutingTableConfigResp *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	::StaticRoutingTableConfig *pStaticRoutingTableConfig;
	::StaticRoutingTableConfig localStaticRoutingTableConfig;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCountStaticRouting = req->srtconfig_size();
	

	for(int i=0;i<iCountStaticRouting;i++)
	{

		pStaticRoutingTableConfig = req->mutable_srtconfig(i);

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        pRes = NULL;
		sql_StaticRouteTAndPeer_Create_Select_Query(pStaticRoutingTableConfig,sStatement);
		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)	
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = GET_STATIC_ROUTING_CONFIG_ERR_DB_ERROR;

			mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);

			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}

		if((iReturn = mysql_StaticRouteConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
		{
			delete pRes;

            if(iReturn == GET_STATIC_ROUTING_ERR_NO_DATA_PRESENT)
                iReturn = GET_STATIC_ROUTING_ERR_NO_STATIC_ROUTE_PRESENT;

			mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}


		delete pRes;
	}

    if(iCountStaticRouting == 0)
	{
		pStaticRoutingTableConfig = &localStaticRoutingTableConfig;

		sql_StaticRouteTAndPeer_Create_Select_Query(pStaticRoutingTableConfig,sStatement);
		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)	
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = GET_SCTPCONFIG_ERR_DB_ERROR;

			mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}

		if((iReturn = mysql_StaticRouteConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
		{
			delete pRes;

			mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}


		delete pRes;

	}


	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;
}



DbStatus_e CMgrDbInterface::mysql_SCTPConfig_Get_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	::SctpProtocol *pSctpProtocol;
	::SctpProtocol localSctpProtocol;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	DLOG_NONE(" > %s ",__FUNCTION__);

	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_sctp())
	{

		pSctpProtocol = pStackConfiguration->mutable_sctp();

		sql_SCTPConfig_Create_Select_Query(pSctpProtocol,sStatement);
		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)	
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = GET_SCTPCONFIG_ERR_DB_ERROR;

			mysql_set_error_for_Common_Config_Reqs(resp,iReturn);

			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}

		if((iReturn = mysql_SCTPConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
		{
			delete pRes;
			mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}


		delete pRes;
	}
	else
	{
		pSctpProtocol = &localSctpProtocol;

		sql_SCTPConfig_Create_Select_Query(pSctpProtocol,sStatement);
		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)	
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = GET_SCTPCONFIG_ERR_DB_ERROR;

			mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}

		if((iReturn = mysql_SCTPConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
		{
			delete pRes;
			mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}


		delete pRes;

	}


	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_TrustedCAConfig_Get_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
    ::CACRLs* pCACRLs;
    ::TrustedCAConfiguration *pTrustedCAConfiguration;
    ::CACRLs localCACRLs;
    ::TrustedCAConfiguration localTrustedCAConfiguration;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	

	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_cacrl())
	{

        pCACRLs = pStackConfiguration->mutable_cacrl();
        int iCount = pCACRLs->tcacfg_size();

        for(int i=0;i<iCount;i++)
        {
            pRes = NULL;
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            pTrustedCAConfiguration = pCACRLs->mutable_tcacfg(i);

            sql_TrustedCAConfig_Create_Select_Query(pTrustedCAConfiguration,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)	
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_TRUSTEDCA_ERR_DB_ERROR;

                mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);

                DLOG_NONE(" < %s ",__FUNCTION__);	
                return iReturn;
            }

            if((iReturn = mysql_TrustedCAConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
            {
                delete pRes;
                mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }


            delete pRes;
        }
	}
	else
	{
		pTrustedCAConfiguration = &localTrustedCAConfiguration;

		sql_TrustedCAConfig_Create_Select_Query(pTrustedCAConfiguration,sStatement);
		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)	
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = GET_TRUSTEDCA_ERR_DB_ERROR;

			mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}

		if((iReturn = mysql_TrustedCAConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
		{
			delete pRes;
			mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}


		delete pRes;

	}


	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_StackGeneralConfig_Get_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	::GeneralConfig *pGeneralConfig;
	::GeneralConfig localGeneralConfig;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	DLOG_NONE(" > %s ",__FUNCTION__);

	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_gconfig())
	{

		pGeneralConfig = pStackConfiguration->mutable_gconfig();

		sql_StackGeneralConfig_Create_Select_Query(pGeneralConfig,sStatement);
		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)	
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = GET_STACKGENERAL_ERR_DB_ERROR;

			mysql_set_error_for_Common_Config_Reqs(resp,iReturn);

			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}

		if((iReturn = mysql_StackGeneralConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
		{
			delete pRes;
			mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}


		delete pRes;
	}
	else
	{
		pGeneralConfig = &localGeneralConfig;

		sql_StackGeneralConfig_Create_Select_Query(pGeneralConfig,sStatement);
		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)	
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = GET_STACKGENERAL_ERR_DB_ERROR;

			mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}

		if((iReturn = mysql_StackGeneralConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
		{
			delete pRes;
			mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}


		delete pRes;

	}


	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_TLSConfig_Get_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	::TLSConfig *pTLSConfig;
	::TLSConfig localTLSConfig;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	DLOG_NONE(" > %s ",__FUNCTION__);

	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_tconfig())
	{

		pTLSConfig = pStackConfiguration->mutable_tconfig();

		sql_TLSConfig_Create_Select_Query(pTLSConfig,sStatement);
		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)	
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = GET_TLSCONFIG_ERR_DB_ERROR;

			mysql_set_error_for_Common_Config_Reqs(resp,iReturn);

			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}

		if((iReturn = mysql_TLSConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
		{
			delete pRes;
			mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}


		delete pRes;
	}
	else
	{
		pTLSConfig = &localTLSConfig;

		sql_TLSConfig_Create_Select_Query(pTLSConfig,sStatement);
		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)	
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = GET_TLSCONFIG_ERR_DB_ERROR;

			mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}

		if((iReturn = mysql_TLSConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
		{
			delete pRes;
			mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}


		delete pRes;

	}


	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_CipherSuiteConfig_Get_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
    ::TLSCipherConfigs* pTLSCipherConfigs;
    ::TLSCipherConfig *pTLSCipherConfig;
    ::TLSCipherConfigs localTLSCipherConfigs;
    ::TLSCipherConfig localTLSCipherConfig;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	DLOG_NONE(" > %s ",__FUNCTION__);

	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_tlsciphers())
	{

        pTLSCipherConfigs = pStackConfiguration->mutable_tlsciphers();
        int iCount = pTLSCipherConfigs->tlsciphers_size();

        for(int i=0;i<iCount;i++)
        {
            pRes = NULL;
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            pTLSCipherConfig= pTLSCipherConfigs->mutable_tlsciphers(i);

            sql_CipherSuiteConfig_Create_Select_Query(pTLSCipherConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)	
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_CIPHERSUITE_ERR_DB_ERROR;

                mysql_set_error_for_CipherSuiteConfig_Config_Reqs(pTLSCipherConfig,resp,iReturn);

                DLOG_NONE(" < %s ",__FUNCTION__);	
                return iReturn;
            }

            if((iReturn = mysql_CipherSuiteConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
            {
                delete pRes;
                mysql_set_error_for_CipherSuiteConfig_Config_Reqs(pTLSCipherConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }


            delete pRes;
        }
	}
	else
	{
		pTLSCipherConfig = &localTLSCipherConfig;

		sql_CipherSuiteConfig_Create_Select_Query(pTLSCipherConfig,sStatement);
		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)	
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = GET_CIPHERSUITE_ERR_DB_ERROR;

			mysql_set_error_for_CipherSuiteConfig_Config_Reqs(pTLSCipherConfig,resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}

		if((iReturn = mysql_CipherSuiteConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
		{
			delete pRes;
			mysql_set_error_for_CipherSuiteConfig_Config_Reqs(pTLSCipherConfig,resp,iReturn);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}


		delete pRes;

	}


	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_SCTPConfig_Set_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	::SctpProtocol localSctpProtocol;
	::SctpProtocol *pSctpProtocol;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_sctp())
		pSctpProtocol = pStackConfiguration->mutable_sctp();
	else
		pSctpProtocol = &localSctpProtocol;


    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if((iReturn = sql_SCTPConfig_Payload_Validation(pSctpProtocol)) != DRE_DB_SUCCESS)
    {
        mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    sql_SCTPConfig_Create_Check_Modifcation_Query(pSctpProtocol,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)	
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_SCTPCONFIG_ERR_DB_ERROR;

        mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_SCTPConfig_Create_Add_Query(pSctpProtocol,sStatement);	
    }
    else // MOD
    {
        sql_SCTPConfig_Create_Mod_Query(pSctpProtocol,sStatement);	
    }

    delete pRes;

    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_SCTPCONFIG_ERR_DB_ERROR;

        mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);	
        return iReturn;
    }


	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_StackGeneralConfig_Set_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;

	::GeneralConfig localGeneralConfig;
	::GeneralConfig *pGeneralConfig;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_gconfig())
		pGeneralConfig = pStackConfiguration->mutable_gconfig();
	else
		pGeneralConfig = &localGeneralConfig;


    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if((iReturn = sql_StackGeneralConfig_Payload_Validation(pGeneralConfig)) != DRE_DB_SUCCESS)
    {
        mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    sql_StackGeneralConfig_Create_Check_Modifcation_Query(pGeneralConfig,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)	
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_STACKGENERAL_ERR_DB_ERROR;

        mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_StackGeneralConfig_Create_Add_Query(pGeneralConfig,sStatement);	
    }
    else // MOD
    {
        sql_StackGeneralConfig_Create_Mod_Query(pGeneralConfig,sStatement);	
    }

    delete pRes;

    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_STACKGENERAL_ERR_DB_ERROR;

        mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);	
        return iReturn;
    }


	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_TLSConfig_Set_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

    char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;

	::TLSConfig localTLSConfig;
	::TLSConfig *pTLSConfig;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_tconfig())
        pTLSConfig = pStackConfiguration->mutable_tconfig();
	else
		pTLSConfig = &localTLSConfig;


    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if((iReturn = sql_TLSConfig_Payload_Validation(pTLSConfig)) != DRE_DB_SUCCESS)
    {
        mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    sql_TLSConfig_Create_Check_Modifcation_Query(pTLSConfig,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)	
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_TLSCONFIG_ERR_DB_ERROR;

        mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_TLSConfig_Create_Add_Query(pTLSConfig,sStatement);	
    }
    else // MOD
    {
        sql_TLSConfig_Create_Mod_Query(pTLSConfig,sStatement);	
    }

    delete pRes;

    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_TLSCONFIG_ERR_DB_ERROR;

        mysql_set_error_for_Common_Config_Reqs(resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);	
        return iReturn;
    }

	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_StaticRouting_Add_validation(::StaticRoutingTableConfig* pStaticRoutingTableConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    sql_StaticRoute_Create_Validation_Query_for_Peer(pStaticRoutingTableConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
    {
        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_STATIC_ROUTING_ERR_PEER_NOT_CONFIGURED;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}



DbStatus_e CMgrDbInterface::mysql_StaticRouting_Add_Config_Reqs(StaticRoutingTableConfigReq *req,StaticRoutingTableConfigResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::StaticRoutingTableConfig* pStaticRoutingTableConfig;
    ::StaticRoutingTableConfig localStaticRoutingTableConfig;
    DLOG_NONE(" > %s ",__FUNCTION__);


    int iStaticRouteCount = req->srtconfig_size();
    DLOG_DEBUG("iStaticRouteCount = %d ",iStaticRouteCount);

    for(int j=0;j<iStaticRouteCount;j++)
    {

        pRes = NULL;
        pStaticRoutingTableConfig = req->mutable_srtconfig(j);  

        if((iReturn = mysql_StaticRouting_Add_validation(pStaticRoutingTableConfig)) != DRE_DB_SUCCESS)
        {
			mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

        if((iReturn = sql_StaticRoute_Payload_Validation(pStaticRoutingTableConfig)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Static Route Validation Failed");
			mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_StaticRoute_Create_Check_Modifcation_Query(pStaticRoutingTableConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_STATIC_ROUTING_ERR_DB_ERROR;

			mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_StaticRoute_Create_Add_Query(pStaticRoutingTableConfig,sStatement);
        }
        else // MOD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present");
            mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,ADD_STATIC_ROUTING_ERR_ROUTE_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_STATIC_ROUTING_ERR_ROUTE_ALREADY_PRESENT;

        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_STATIC_ROUTING_ERR_DB_ERROR;

            mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;

        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_TrustedCAConfig_Add_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

    char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;

	::CACRLs localCACRLs;
	::CACRLs *pCACRLs;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_cacrl())
        pCACRLs = pStackConfiguration->mutable_cacrl();
	else
		pCACRLs = &localCACRLs;


    int iCount = pCACRLs->tcacfg_size();
    for(int i=0;i<iCount;i++)
    {
        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        ::TrustedCAConfiguration *pTrustedCAConfiguration;

        pTrustedCAConfiguration = pCACRLs->mutable_tcacfg(i);

        if((iReturn = sql_TrustedCAConfig_Payload_Validation(pTrustedCAConfiguration)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

            sql_TrustedCAConfig_Create_Check_Modifcation_Query(pTrustedCAConfiguration,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)	
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_TRUSTEDCA_ERR_DB_ERROR;

            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_TrustedCAConfig_Create_Add_Query(pTrustedCAConfiguration,sStatement);	
        }
        else // MOD
        {
            delete pRes;

            DLOG_ERROR("Record Already Present"); 	
            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,ADD_TRUSTEDCA_ERR_CAFILE_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_TRUSTEDCA_ERR_CAFILE_ALREADY_PRESENT;
        }

        delete pRes;

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_TRUSTEDCA_ERR_DB_ERROR;

            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);	
            return iReturn;
        }
    }

	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_TrustedCAConfig_RemoveAssoc_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

    char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;

	::CACRLs localCACRLs;
	::CACRLs *pCACRLs;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_cacrl())
        pCACRLs = pStackConfiguration->mutable_cacrl();
	else
		pCACRLs = &localCACRLs;


    int iCount = pCACRLs->tcacfg_size();
    for(int i=0;i<iCount;i++)
    {
        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        ::TrustedCAConfiguration *pTrustedCAConfiguration;

        pTrustedCAConfiguration = pCACRLs->mutable_tcacfg(i);

        if((iReturn = sql_TrustedCAConfig_Payload_Validation(pTrustedCAConfiguration)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

            sql_TrustedCAConfig_Create_Check_Modifcation_Query(pTrustedCAConfiguration,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)	
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_ASSOCTRUSTEDCA_ERR_DB_ERROR;

            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;

            DLOG_ERROR("Record not Present"); 	
            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,DEL_ASSOCTRUSTEDCA_ERR_CAFILE_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_ASSOCTRUSTEDCA_ERR_CAFILE_NOT_PRESENT;

        }
        else // MOD
        {
            sql_TrustedCAConfig_Create_DeleteAssoc_Query(pTrustedCAConfiguration,sStatement);	
        }

        delete pRes;

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_ASSOCTRUSTEDCA_ERR_DB_ERROR;

            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);	
            return iReturn;
        }
    }

	DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_StaticRouting_Del_validation(::StaticRoutingTableConfig* pStaticRoutingTableConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    sql_StaticRoute_Create_Validation_Query_for_Peer(pStaticRoutingTableConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
    {
        if(iReturn == DRE_DB_FAIL)
            iReturn = DEL_STATIC_ROUTING_ERR_PEER_NOT_CONFIGURED;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}



DbStatus_e CMgrDbInterface::mysql_StaticRouting_Del_Config_Reqs(StaticRoutingTableConfigReq *req,StaticRoutingTableConfigResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE];
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::StaticRoutingTableConfig* pStaticRoutingTableConfig;
    ::StaticRoutingTableConfig localStaticRoutingTableConfig;

    DLOG_NONE(" > %s ",__FUNCTION__);

    int iStaticRouteCount = req->srtconfig_size();
    DLOG_DEBUG("LBPeerGroupReq Count = %d ",iStaticRouteCount);

    for(int j=0;j<iStaticRouteCount;j++)
    {

        pRes = NULL;
        pStaticRoutingTableConfig = req->mutable_srtconfig(j);  

        if((iReturn = mysql_StaticRouting_Del_validation(pStaticRoutingTableConfig)) != DRE_DB_SUCCESS)
        {
			mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }



        sql_StaticRoute_Create_Check_Modifcation_Query(pStaticRoutingTableConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_STATIC_ROUTING_ERR_DB_ERROR;

			mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            DLOG_ERROR("Record is not present ");
            delete pRes;
			mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,DEL_STATIC_ROUTING_ERR_ROUTE_DOESNT_EXIST);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_STATIC_ROUTING_ERR_ROUTE_DOESNT_EXIST;
        }
        else
        {
            delete pRes;
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_StaticRoute_Create_Delete_Query(pStaticRoutingTableConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_STATIC_ROUTING_ERR_DB_ERROR;

			    mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}



DbStatus_e CMgrDbInterface::mysql_TrustedCAConfig_Del_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

    char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;

	::CACRLs localCACRLs;
	::CACRLs *pCACRLs;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_cacrl())
        pCACRLs = pStackConfiguration->mutable_cacrl();
	else
		pCACRLs = &localCACRLs;


    int iCount = pCACRLs->tcacfg_size();
    for(int i=0;i<iCount;i++)
    {
        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        ::TrustedCAConfiguration *pTrustedCAConfiguration;

        pTrustedCAConfiguration = pCACRLs->mutable_tcacfg(i);

        if((iReturn = sql_TrustedCAConfig_Payload_Validation(pTrustedCAConfiguration)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        sql_TrustedCAConfig_Create_Check_Modifcation_Query(pTrustedCAConfiguration,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)	
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_TRUSTEDCA_ERR_DB_ERROR;

            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;

            DLOG_ERROR("Record not Present"); 	
            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,DEL_TRUSTEDCA_ERR_CAFILE_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_TRUSTEDCA_ERR_CAFILE_NOT_PRESENT;

        }
        else // MOD
        {
            sql_TrustedCAConfig_Create_Delete_Query(pTrustedCAConfiguration,sStatement);	
        }

        delete pRes;

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_TRUSTEDCA_ERR_DB_ERROR;

            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);	
            return iReturn;
        }
    }


	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_StaticRouting_Mod_validation(::StaticRoutingTableConfig* pStaticRoutingTableConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    sql_StaticRoute_Create_Validation_Query_for_Peer(pStaticRoutingTableConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
    {
        if(iReturn == DRE_DB_FAIL)
            iReturn = MOD_STATIC_ROUTING_ERR_PEER_NOT_CONFIGURED;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_StaticRouting_Mod_Config_Reqs(StaticRoutingTableConfigReq *req,StaticRoutingTableConfigResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::StaticRoutingTableConfig* pStaticRoutingTableConfig;
    ::StaticRoutingTableConfig localStaticRoutingTableConfig;

    DLOG_NONE(" > %s ",__FUNCTION__);


    int iStaticRouteCount = req->srtconfig_size();
    DLOG_DEBUG("StaticRouteCount = %d ",iStaticRouteCount);

    for(int j=0;j<iStaticRouteCount;j++)
    {
        pRes = NULL;
        pStaticRoutingTableConfig = req->mutable_srtconfig(j);  

        if((iReturn = mysql_StaticRouting_Mod_validation(pStaticRoutingTableConfig)) != DRE_DB_SUCCESS)
        {
			mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }


        if((iReturn = sql_StaticRoute_Payload_Validation(pStaticRoutingTableConfig)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("StaticRoute Validation Failed");
			mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_StaticRoute_Create_Check_Modifcation_Query(pStaticRoutingTableConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);


            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_STATIC_ROUTING_ERR_DB_ERROR;

			mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;

        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record is not present ");
            mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,MOD_STATIC_ROUTING_ERR_ROUTE_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_STATIC_ROUTING_ERR_ROUTE_NOT_PRESENT;

        }
        else // MOD
        {
            sql_StaticRoute_Create_Mod_Query(pStaticRoutingTableConfig,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_STATIC_ROUTING_ERR_DB_ERROR;

            mysql_set_error_for_StaticRouting_Config_Reqs(pStaticRoutingTableConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);

            return iReturn;
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_TrustedCAConfig_Mod_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

    char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;

	::CACRLs localCACRLs;
	::CACRLs *pCACRLs;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_cacrl())
        pCACRLs = pStackConfiguration->mutable_cacrl();
	else
		pCACRLs = &localCACRLs;


    int iCount = pCACRLs->tcacfg_size();
    for(int i=0;i<iCount;i++)
    {
        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        ::TrustedCAConfiguration *pTrustedCAConfiguration;

        pTrustedCAConfiguration = pCACRLs->mutable_tcacfg(i);

        if((iReturn = sql_TrustedCAConfig_Payload_Validation(pTrustedCAConfiguration)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

            sql_TrustedCAConfig_Create_Check_Modifcation_Query(pTrustedCAConfiguration,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)	
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_TRUSTEDCA_ERR_DB_ERROR;

            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;

            DLOG_ERROR("Record not Present"); 	
            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,MOD_TRUSTEDCA_ERR_CAFILE_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_TRUSTEDCA_ERR_CAFILE_NOT_PRESENT;

        }
        else // MOD
        {
            sql_TrustedCAConfig_Create_Mod_Query(pTrustedCAConfiguration,sStatement);	
        }

        delete pRes;

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_TRUSTEDCA_ERR_DB_ERROR;

            mysql_set_error_for_TrustedCAConfig_Config_Reqs(pTrustedCAConfiguration,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);	
            return iReturn;
        }
    }


	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_CipherSuiteConfig_Mod_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

    char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;

	::TLSCipherConfigs localTLSCipherConfigs;
	::TLSCipherConfigs *pTLSCipherConfigs;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_tlsciphers())
        pTLSCipherConfigs = pStackConfiguration->mutable_tlsciphers();
	else
		pTLSCipherConfigs = &localTLSCipherConfigs;


    int iCount = pTLSCipherConfigs->tlsciphers_size();
    for(int i=0;i<iCount;i++)
    {
        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        ::TLSCipherConfig *pTLSCipherConfig;

        pTLSCipherConfig = pTLSCipherConfigs->mutable_tlsciphers(i);

        if((iReturn = sql_CipherSuiteConfig_Payload_Validation(pTLSCipherConfig)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_CipherSuiteConfig_Config_Reqs(pTLSCipherConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

            sql_CipherSuiteConfig_Create_Check_Modifcation_Query(pTLSCipherConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)	
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_CIPHERSUITE_ERR_DB_ERROR;

            mysql_set_error_for_CipherSuiteConfig_Config_Reqs(pTLSCipherConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;

            DLOG_ERROR("Record not Present"); 	
            mysql_set_error_for_CipherSuiteConfig_Config_Reqs(pTLSCipherConfig,resp,MOD_HOST_ERR_HOST_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_CIPHERSUITE_ERR_CIPHER_NOT_PRESENT;

        }
        else // MOD
        {
            sql_CipherSuiteConfig_Create_Mod_Query(pTLSCipherConfig,sStatement);	
        }

        delete pRes;

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_CIPHERSUITE_ERR_DB_ERROR;

            mysql_set_error_for_CipherSuiteConfig_Config_Reqs(pTLSCipherConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);	
            return iReturn;
        }
    }



	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_StaticRouteConfig_resultset_to_protoBuff(sql::ResultSet *pRes,StaticRoutingTableConfigResp *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	try
	{
		DLOG_DEBUG(" %s: SCTP Config Result Set= %d ",__FUNCTION__,pRes->rowsCount()); 
		if(pRes->rowsCount() == 0)
		{
			DLOG_NONE(" < %s ",__FUNCTION__);
			return GET_STATIC_ROUTING_ERR_NO_DATA_PRESENT;
		}


		while(pRes->next())
		{
        		::StaticRoutingTableConfig *pStaticRoutingTableConfig = resp->add_srtconfig();
				
			if(!pRes->isNull("PeerHostIdentity"))	
				pStaticRoutingTableConfig->set_peer(pRes->getString("PeerHostIdentity"));
			if(!pRes->isNull("RealmName"))	
				pStaticRoutingTableConfig->set_realm(pRes->getString("RealmName"));
			if(!pRes->isNull("DESTINATION_HOST"))	
				pStaticRoutingTableConfig->set_destionatinhost(pRes->getString("DESTINATION_HOST"));
			if(!pRes->isNull("APPLICATION_ID"))	
            {
                if(pRes->getInt("APPLICATION_ID") != 0)
    				pStaticRoutingTableConfig->set_applicationid(pRes->getInt("APPLICATION_ID"));
            }
			if(!pRes->isNull("PRIORITY"))	
				pStaticRoutingTableConfig->set_priority(pRes->getInt("PRIORITY"));
			if(!pRes->isNull("DESTINATION_REALM"))	
				pStaticRoutingTableConfig->set_destionatinrealm(pRes->getString("DESTINATION_REALM"));
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



DbStatus_e CMgrDbInterface::mysql_SCTPConfig_resultset_to_protoBuff(sql::ResultSet *pRes,StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	try
	{
		DLOG_DEBUG(" %s: SCTP Config Result Set= %d ",__FUNCTION__,pRes->rowsCount()); 
		if(pRes->rowsCount() == 0)
		{
			DLOG_NONE(" < %s ",__FUNCTION__);
			return GET_SCTPCONFIG_ERR_NO_DATA_PRESENT;
		}

		StackConfiguration *pStackConfiguration = resp->mutable_stackconfig();
		SctpProtocol *pSctpProtocol = pStackConfiguration->mutable_sctp();

		if(pRes->next())
		{
				
			if(!pRes->isNull("HEARTBEAT_ENABLE"))	
				pSctpProtocol->set_heartbeatenable(pRes->getInt("HEARTBEAT_ENABLE"));
			if(!pRes->isNull("HEARTBEAT_TIMEOUT"))	
				pSctpProtocol->set_hearbeattimeout(pRes->getInt("HEARTBEAT_TIMEOUT"));
			if(!pRes->isNull("INIT_TIMEOUT"))	
				pSctpProtocol->set_initialtimeout(pRes->getInt("INIT_TIMEOUT"));
			if(!pRes->isNull("ASSOC_MAX_ATTEMPTS"))	
				pSctpProtocol->set_maximumattempts(pRes->getInt("ASSOC_MAX_ATTEMPTS"));
			if(!pRes->isNull("RTO_MAX"))	
				pSctpProtocol->set_rtomaximum(pRes->getInt("RTO_MAX"));
			if(!pRes->isNull("RTO_MIN"))	
				pSctpProtocol->set_rtominimum(pRes->getInt("RTO_MIN"));
			if(!pRes->isNull("RTO_INITIAL"))	
				pSctpProtocol->set_rtoinitial(pRes->getInt("RTO_INITIAL"));
			if(!pRes->isNull("PATH_FAILURE_RETRY_COUNT"))	
				pSctpProtocol->set_pathfailretrycount(pRes->getInt("PATH_FAILURE_RETRY_COUNT"));
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

DbStatus_e CMgrDbInterface::mysql_LocalTransportTag_resultset_to_protoBuff(sql::ResultSet *pRes,LocalTransportTagResponse *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: LocalTransport Tag Config Result Set= %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_LOCAL_TRANSPORTTAG_ERR_NO_DATA_PRESENT;
        }


        while(pRes->next())
        {
            ::LocalTransportTag *pLocalTransportTag = resp->add_tags();

            if(!pRes->isNull("LOCAL_TRANSPORT_TAG_ID"))
                pLocalTransportTag->set_tagid(pRes->getInt("LOCAL_TRANSPORT_TAG_ID"));
            if(!pRes->isNull("TRANSPORT_TAG"))
                pLocalTransportTag->set_tagname(pRes->getString("TRANSPORT_TAG"));
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

DbStatus_e CMgrDbInterface::mysql_StackGeneralConfig_resultset_to_protoBuff(sql::ResultSet *pRes,StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	try
	{
		DLOG_DEBUG(" %s: General Config Result Set= %d ",__FUNCTION__,pRes->rowsCount()); 
		if(pRes->rowsCount() == 0)
		{
			DLOG_NONE(" < %s ",__FUNCTION__);
			return GET_STACKGENERAL_ERR_NO_DATA_PRESENT;
		}

		StackConfiguration *pStackConfiguration = resp->mutable_stackconfig();
		GeneralConfig *pGeneralConfig = pStackConfiguration->mutable_gconfig();

		if(pRes->next())
		{
				
			if(!pRes->isNull("PEER_IP_CHECK_ENABLE"))	
				pGeneralConfig->set_enablepeeripcheck(pRes->getInt("PEER_IP_CHECK_ENABLE"));
			if(!pRes->isNull("IS_PREDICTIVE_LOOP_AVD_REQUIRED"))	
				pGeneralConfig->set_ispredictiveloopavdrequired(pRes->getInt("IS_PREDICTIVE_LOOP_AVD_REQUIRED"));
			if(!pRes->isNull("IS_SNAPTR_SUPPORTED"))	
				pGeneralConfig->set_issnaptrsupported(pRes->getInt("IS_SNAPTR_SUPPORTED"));
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


DbStatus_e CMgrDbInterface::mysql_TLSConfig_resultset_to_protoBuff(sql::ResultSet *pRes,StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	try
	{
		DLOG_DEBUG(" %s: General Config Result Set= %d ",__FUNCTION__,pRes->rowsCount()); 
		if(pRes->rowsCount() == 0)
		{
			DLOG_NONE(" < %s ",__FUNCTION__);
			return GET_TLSCONFIG_ERR_NO_DATA_PRESENT;
		}

		StackConfiguration *pStackConfiguration = resp->mutable_stackconfig();
		TLSConfig *pTLSConfig = pStackConfiguration->mutable_tconfig();

		if(pRes->next())
		{
				
			if(!pRes->isNull("IDENTITY_VERIFICATION_ENABLE"))	
				pTLSConfig->set_enableidverification(pRes->getInt("IDENTITY_VERIFICATION_ENABLE"));
			if(!pRes->isNull("CRL_VERIFICATION_ENABLE"))	
				pTLSConfig->set_enablecrlverification(pRes->getInt("CRL_VERIFICATION_ENABLE"));
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



DbStatus_e CMgrDbInterface::mysql_CipherSuiteConfig_resultset_to_protoBuff(sql::ResultSet *pRes,StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	try
	{
		DLOG_DEBUG(" %s: TrustedCAConfig Config Result Set= %d ",__FUNCTION__,pRes->rowsCount()); 
		if(pRes->rowsCount() == 0)
		{
			DLOG_NONE(" < %s ",__FUNCTION__);
			return GET_CIPHERSUITE_ERR_NO_DATA_PRESENT;
		}

		StackConfiguration *pStackConfiguration = resp->mutable_stackconfig();
		::TLSCipherConfigs *pTLSCipherConfigs = pStackConfiguration->mutable_tlsciphers();

		while(pRes->next())
		{
            TLSCipherConfig *pTLSCipherConfig = pTLSCipherConfigs->add_tlsciphers();

			if(!pRes->isNull("Enable"))	
				pTLSCipherConfig->set_enableciphersuite(pRes->getInt("Enable"));
			if(!pRes->isNull("CIPHER_SUITE_NAME"))	
				pTLSCipherConfig->set_ciphersuitename(pRes->getString("CIPHER_SUITE_NAME"));
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



DbStatus_e CMgrDbInterface::mysql_TrustedCAConfig_resultset_to_protoBuff(sql::ResultSet *pRes,StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	try
	{
		DLOG_DEBUG(" %s: TrustedCAConfig Config Result Set= %d ",__FUNCTION__,pRes->rowsCount()); 
		if(pRes->rowsCount() == 0)
		{
			DLOG_NONE(" < %s ",__FUNCTION__);
			return GET_TRUSTEDCA_ERR_NO_DATA_PRESENT;
		}

		StackConfiguration *pStackConfiguration = resp->mutable_stackconfig();
		CACRLs *pCACRLs = pStackConfiguration->mutable_cacrl();

		while(pRes->next())
		{
            TrustedCAConfiguration *pTrustedCAConfiguration = pCACRLs->add_tcacfg();

			if(!pRes->isNull("CA_FILE"))	
				pTrustedCAConfiguration->set_cafile(pRes->getString("CA_FILE"));
			if(!pRes->isNull("CRL_FILE"))	
				pTrustedCAConfiguration->set_crlfile(pRes->getString("CRL_FILE"));
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



DbStatus_e CMgrDbInterface::mysql_LocalHost_resultset_to_protoBuff(sql::ResultSet *pRes,StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	try
	{
		DLOG_DEBUG(" %s: Tracing Config Result Set= %d ",__FUNCTION__,pRes->rowsCount()); 
		if(pRes->rowsCount() == 0)
		{
			DLOG_NONE(" < %s ",__FUNCTION__);
			return GET_HOST_ERR_NO_DATA_PRESENT;
		}

		StackConfiguration *pStackConfiguration = resp->mutable_stackconfig();
		LocalHost *pLocalHost = pStackConfiguration->mutable_lhost();

		if(pRes->next())
		{
				
			if(!pRes->isNull("HostName"))	
				pLocalHost->set_localhostname(pRes->getString("HostName"));
			if(!pRes->isNull("RealmName"))	
				pLocalHost->set_realmname(pRes->getString("RealmName"));
			if(!pRes->isNull("AuthLifeTime"))	
				pLocalHost->set_authsessionlifetime(pRes->getInt("AuthLifeTime"));
			if(!pRes->isNull("AuthGraceTime"))	
				pLocalHost->set_authsessiongraceperiod(pRes->getInt("AuthGraceTime"));
			if(!pRes->isNull("AuthTimeOut"))	
				pLocalHost->set_authsessiontimeout(pRes->getInt("AuthTimeOut"));
			if(!pRes->isNull("AcctInterim"))	
				pLocalHost->set_acctsessioninteriminterval(pRes->getInt("AcctInterim"));
			if(!pRes->isNull("AcctTimeOut"))	
				pLocalHost->set_acctsessiontimeout(pRes->getInt("AcctTimeOut"));

			mysql_LocalHost_resultset_to_LHTransport_protoBuff(pRes,pLocalHost);

		}

		while(pRes->next())
		{
			mysql_LocalHost_resultset_to_LHTransport_protoBuff(pRes,pLocalHost);
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

DbStatus_e CMgrDbInterface::mysql_LocalHost_resultset_to_LHTransport_protoBuff(sql::ResultSet *pRes,LocalHost *pLocalHost)
{
	DLOG_NONE(" > %s ",__FUNCTION__);
    ::LHTransport* pLHTransport;

    int iCount = pLocalHost->transports_size();

    for(int i=0;i<iCount;i++)
    {
       pLHTransport = pLocalHost->mutable_transports(i); 

       if(pLHTransport->transportslot() == (unsigned int)pRes->getInt("TRANSPORT_ID"))
       {
           int jCount = pLHTransport->secondaryipaddr_size();
           for(int j=0;j<jCount;j++)
           {
               if(pLHTransport->secondaryipaddr(j) == pRes->getString("OTHERHOME_IPADDR"))
               {
                   return DRE_DB_SUCCESS; 
               }
           }
           if(!pRes->isNull("OTHERHOME_IPADDR"))
            pLHTransport->add_secondaryipaddr(pRes->getString("OTHERHOME_IPADDR"));
           return DRE_DB_SUCCESS;
       }
        
    }

	pLHTransport = pLocalHost->add_transports();

	pLHTransport->set_transportslot(pRes->getInt("TRANSPORT_ID"));

	if(!pRes->isNull("TRANSPORT_TYPE"))	
	{
		if(pRes->getInt("TRANSPORT_TYPE") == 1)
			pLHTransport->set_transporttype("TCP");
		else if(pRes->getInt("TRANSPORT_TYPE") == 2)
			pLHTransport->set_transporttype("SCTP");
	}

    if(!pRes->isNull("PUBLIC_SERVER_IP"))
        pLHTransport->set_publicserveripaddr(pRes->getString("PUBLIC_SERVER_IP"));
    if(!pRes->isNull("IP_ADDRESS"))
	    pLHTransport->set_hostipaddr(pRes->getString("IP_ADDRESS"));
    if(!pRes->isNull("PORT"))
	    pLHTransport->set_port(pRes->getInt("PORT"));
    if(!pRes->isNull("SecurePort"))
	    pLHTransport->set_secureport(pRes->getInt("SecurePort"));
    if(!pRes->isNull("OTHERHOME_IPADDR"))
        pLHTransport->add_secondaryipaddr(pRes->getString("OTHERHOME_IPADDR"));
	

	DLOG_NONE(" < %s ",__FUNCTION__);

	return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_LocalHost_Mod_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{

	DLOG_NONE(" > %s ",__FUNCTION__);
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	::LocalHost localLocalHost;
	::LocalHost *pLocalHost;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	

	pRes = NULL;
	memset(sStatement,0,MAX_STATEMENT_SIZE);

	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_lhost())
		pLocalHost = pStackConfiguration->mutable_lhost();
	else
		pLocalHost = &localLocalHost;

	if((iReturn = sql_LocalHost_Payload_Validation(pLocalHost)) != DRE_DB_SUCCESS)
	{
		mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,iReturn);
		DLOG_NONE(" < %s ",__FUNCTION__);
		return iReturn;
	}

	sql_LocalHost_Create_Check_Modifcation_Query(pLocalHost,sStatement);

	if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
	{
		if(pRes != NULL)	
		{
			delete pRes;
		}

		DLOG_ERROR("Query Execution Failed: %s",sStatement);

		if(iReturn == DRE_DB_FAIL)
			iReturn = MOD_HOST_ERR_DB_ERROR;

		mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,iReturn);
		DLOG_NONE(" < %s ",__FUNCTION__);
		return iReturn;
	}

	memset(sStatement,0,MAX_STATEMENT_SIZE);

	if(pRes->rowsCount() == 0) // ADD
	{
		delete pRes;
		
		DLOG_ERROR("Record not Present"); 	
		mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,MOD_HOST_ERR_HOST_NOT_PRESENT);
		DLOG_NONE(" < %s ",__FUNCTION__);
		return MOD_HOST_ERR_HOST_NOT_PRESENT;
	}
	else // MOD
	{
		sql_LocalHost_Create_Mod_Query(pLocalHost,sStatement);	
	}

	delete pRes;

	if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
	{
		DLOG_ERROR("Query Execution Failed: %s",sStatement);

		if(iReturn == DRE_DB_FAIL)
			iReturn = MOD_HOST_ERR_DB_ERROR;

		mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,iReturn);
		DLOG_NONE(" < %s ",__FUNCTION__);	
		return iReturn;
	}

	iReturn = mysql_TransportType_Set_Config_Reqs(req,resp);

    if(iReturn == DRE_DB_SUCCESS)
    {
        iReturn = mysql_LocalHostMultihoming_Add_Config_Reqs(req, resp);
    }

	DLOG_NONE(" < %s ",__FUNCTION__);
	return iReturn;

}


DbStatus_e CMgrDbInterface::mysql_LocalHost_Set_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{

	DLOG_NONE(" > %s ",__FUNCTION__);
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	::LocalHost localLocalHost;
	::LocalHost *pLocalHost;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	

	pRes = NULL;
	memset(sStatement,0,MAX_STATEMENT_SIZE);

	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_lhost())
		pLocalHost = pStackConfiguration->mutable_lhost();
	else
		pLocalHost = &localLocalHost;

	if((iReturn = sql_LocalHost_Payload_Validation(pLocalHost)) != DRE_DB_SUCCESS)
	{
		mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,iReturn);
		DLOG_NONE(" < %s ",__FUNCTION__);
		return iReturn;
	}

	sql_LocalHost_Create_Check_Modifcation_Query(pLocalHost,sStatement);

	if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
	{
		if(pRes != NULL)	
		{
			delete pRes;
		}

		DLOG_ERROR("Query Execution Failed: %s",sStatement);

		if(iReturn == DRE_DB_FAIL)
			iReturn = SET_HOST_ERR_DB_ERROR;

		mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,iReturn);
		DLOG_NONE(" < %s ",__FUNCTION__);
		return iReturn;
	}

	memset(sStatement,0,MAX_STATEMENT_SIZE);

	if(pRes->rowsCount() == 0) // ADD
	{
		sql_LocalHost_Create_Add_Query(pLocalHost,sStatement);	
	}
	else // MOD
	{
		delete pRes;
		
		DLOG_ERROR("Record Already Present"); 	
		mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,SET_HOST_ERR_HOST_ALREADY_PRESENT);
		DLOG_NONE(" < %s ",__FUNCTION__);
		return SET_HOST_ERR_HOST_ALREADY_PRESENT;

	}

	delete pRes;

	if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
	{
		DLOG_ERROR("Query Execution Failed: %s",sStatement);

		if(iReturn == DRE_DB_FAIL)
			iReturn = SET_HOST_ERR_DB_ERROR;

		mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,iReturn);
		DLOG_NONE(" < %s ",__FUNCTION__);	
		return iReturn;
	}

	iReturn = mysql_TransportType_Set_Config_Reqs(req,resp);

    if(iReturn == DRE_DB_SUCCESS)
    {
        iReturn = mysql_LocalHostMultihoming_Add_Config_Reqs(req, resp);
    }


	DLOG_NONE(" < %s ",__FUNCTION__);
	return iReturn;

}


DbStatus_e CMgrDbInterface::mysql_LocalHostMultihoming_Del_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{

	DLOG_NONE(" > %s ",__FUNCTION__);
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	::LocalHost localLocalHost;
	::LocalHost *pLocalHost;
	int iCount;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_lhost())
		pLocalHost = pStackConfiguration->mutable_lhost();
	else
		pLocalHost = &localLocalHost;

	iCount = pLocalHost->transports_size();
	DLOG_DEBUG(" %s: transport_size = %d ",__FUNCTION__,iCount); 

	for(int i=0;i<iCount;i++)
    {
         ::LHTransport *pLHTransport = pLocalHost->mutable_transports(i);
         int iMultiHomingCount = pLHTransport->secondaryipaddr_size();
	    DLOG_DEBUG(" %s: secondaryipaddr_size = %d ",__FUNCTION__,iCount); 
        for(int j=0;j<iMultiHomingCount;j++)
        {
            pRes = NULL;
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            sql_MultiHoming_Create_Check_Modifcation_Query(pLHTransport,sStatement,i);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)	
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_HOST_MULTIHOMING_ERR_DB_ERROR;

                mysql_set_error_for_MultiHoming_Config_Reqs(pLHTransport,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                delete pRes;

                DLOG_ERROR("Record Not Present"); 	
                mysql_set_error_for_MultiHoming_Config_Reqs(pLHTransport,resp,DEL_HOST_MULTIHOMING_SECONDARY_IP_NOT_PRESENT,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_HOST_MULTIHOMING_SECONDARY_IP_NOT_PRESENT;

            }
            else // MOD
            {
                sql_MultiHoming_Create_Delete_Query(pLocalHost,sStatement,i);	
            }

            delete pRes;

            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_HOST_MULTIHOMING_ERR_DB_ERROR;

                mysql_set_error_for_MultiHoming_Config_Reqs(pLHTransport,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);	
                return iReturn;
            }       
        } 
    }
	DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_LocalHostMutihoming_Add_validation(::LocalHost *pLocalHost)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    sql_LocalTransport_Create_Validation_Query_for_LocalHost(pLocalHost,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
    {
        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_HOST_MULTIHOMING_INVALID_LOCALHOST;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_LocalHostMultihoming_Add_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{

	DLOG_NONE(" > %s ",__FUNCTION__);
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	::LocalHost localLocalHost;
	::LocalHost *pLocalHost;
	int iCount;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_lhost())
		pLocalHost = pStackConfiguration->mutable_lhost();
	else
		pLocalHost = &localLocalHost;

	iCount = pLocalHost->transports_size();
	DLOG_DEBUG(" %s: transport_size = %d ",__FUNCTION__,iCount); 

	for(int i=0;i<iCount;i++)
    {
         ::LHTransport *pLHTransport = pLocalHost->mutable_transports(i);
         int iMultiHomingCount = pLHTransport->secondaryipaddr_size();
	    DLOG_DEBUG(" %s: secondaryipaddr_size = %d ",__FUNCTION__,iMultiHomingCount); 
        for(int j=0;j<iMultiHomingCount;j++)
        {
            pRes = NULL;
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if((iReturn = mysql_LocalHostMutihoming_Add_validation(pLocalHost)) != DRE_DB_SUCCESS)
            {
                mysql_set_error_for_MultiHoming_Config_Reqs(pLHTransport,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);   
                return iReturn;
            }


            if((iReturn = sql_MultiHoming_Payload_Validation(pLHTransport,j)) != DRE_DB_SUCCESS)
            {
                mysql_set_error_for_MultiHoming_Config_Reqs(pLHTransport,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            sql_MultiHoming_Create_Check_Modifcation_Query(pLHTransport,sStatement,j);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)	
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_HOST_MULTIHOMING_ERR_DB_ERROR;

                mysql_set_error_for_MultiHoming_Config_Reqs(pLHTransport,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                sql_MultiHoming_Create_Add_Query(pLHTransport,sStatement,j);	
            }
            else // MOD
            {
                delete pRes;

                DLOG_ERROR("Record Already Present"); 	
                mysql_set_error_for_MultiHoming_Config_Reqs(pLHTransport,resp,ADD_HOST_MULTIHOMING_SECONDARY_IP_ALREADY_PRESENT,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_HOST_MULTIHOMING_SECONDARY_IP_ALREADY_PRESENT;
            }

            delete pRes;

            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_HOST_MULTIHOMING_ERR_DB_ERROR;

                mysql_set_error_for_MultiHoming_Config_Reqs(pLHTransport,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);	
                return iReturn;
            }       
        } 
        

        LHTransport  lLHTransport;

        lLHTransport.set_transporttype(pLHTransport->transporttype());
        lLHTransport.set_hostipaddr(pLHTransport->hostipaddr());
        lLHTransport.set_port(pLHTransport->port());
 
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        pRes = NULL;
        sql_MultiHoming_Create_Select_Query(&lLHTransport,sStatement,-1);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)	
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_HOST_MULTIHOMING_ERR_DB_ERROR;

            mysql_set_error_for_MultiHoming_Config_Reqs(&lLHTransport,resp,iReturn,-1);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if(pRes->rowsCount() > MAX_SECONDARY_IP_SUPPORTED) // ADD
        {
                delete pRes;
                DLOG_ERROR("Number of Secondary IP is already reached 4"); 	
                mysql_set_error_for_MultiHoming_Config_Reqs(pLHTransport,resp,ADD_HOST_MULTIHOMING_SECONDARY_IP_REACHED_MAX_LIMIT,-1);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_HOST_MULTIHOMING_SECONDARY_IP_REACHED_MAX_LIMIT;
            
        }

        delete pRes;

    }
	DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_TransportType_Set_validation(::LocalHost *pLocalHost)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    sql_LocalTransport_Create_Validation_Query_for_LocalHost(pLocalHost,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
    {
        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_HOST_TRANSPORT_ERR_INVALID_LOCALHOST;

    }

   
    for(int i = 0;i < pLocalHost->transports_size();i++)
    {
    	memset(sStatement,0,MAX_STATEMENT_SIZE);
        LHTransport* localTransport = pLocalHost->mutable_transports(i);

	LocalHost LocalLocalHostObj;
	LHTransport *plocalTransport=LocalLocalHostObj.add_transports();
	plocalTransport->set_transporttype(localTransport->transporttype());
	plocalTransport->set_secureport(localTransport->secureport());
	plocalTransport->set_port(localTransport->port());
	plocalTransport->set_hostipaddr(localTransport->hostipaddr());
	
	sql_LocalTransport_Create_Select_Query(&LocalLocalHostObj,sStatement,i);
	if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
	{
		if(pRes != NULL)	
		{
			delete pRes;
		}

		DLOG_ERROR("Query Execution Failed: %s",sStatement);

		if(iReturn == DRE_DB_FAIL)
			iReturn = SET_HOST_TRANSPORT_ERR_DB_ERROR;

		DLOG_NONE(" < %s ",__FUNCTION__);
		return iReturn;
	}

	if(pRes->rowsCount() > 0)
	{
		if(pRes->next())
		{
			if(!pRes->isNull("TRANSPORT_ID"))
			{
				if(localTransport->transportslot() != pRes->getUInt("TRANSPORT_ID"))
				{
					delete pRes;
					DLOG_ERROR("TransportType+HostIP+Port+SecurePort Combination already present"); 	
					DLOG_NONE(" < %s ",__FUNCTION__);
					return SET_HOST_TRANSPORT_ERR_DUPLICATE_ENTRY_OF_TRANSPORT_CONFIG;
				}
			}
		}
	}

        if (localTransport->has_transporttype())
        {
            if ((strcmp(localTransport->transporttype().c_str(), "SCTP") == 0) &&
                (localTransport->has_secureport() && localTransport->secureport() > 0))
            {
                iReturn = SET_HOST_TRANSPORT_ERR_INVALID_COMBINATION_OF_TYPE_AND_PORT; 
            }
        }
	delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_TransportType_Set_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	::LocalHost localLocalHost;
	::LocalHost *pLocalHost;
	int iCount;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	
	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_lhost())
		pLocalHost = pStackConfiguration->mutable_lhost();
	else
		pLocalHost = &localLocalHost;

	iCount = pLocalHost->transports_size();
	DLOG_DEBUG(" %s: transport_size = %d ",__FUNCTION__,iCount); 

	for(int i=0;i<iCount;i++)
	{
		pRes = NULL;
		memset(sStatement,0,MAX_STATEMENT_SIZE);

        if((iReturn = mysql_TransportType_Set_validation(pLocalHost)) != DRE_DB_SUCCESS)
        {
	    mysql_set_error_for_LHTransport_Config_Reqs(pLocalHost,resp,iReturn,i);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

		if((iReturn = sql_LocalTransport_Payload_Validation(pLocalHost,i)) != DRE_DB_SUCCESS)
		{
			mysql_set_error_for_LHTransport_Config_Reqs(pLocalHost,resp,iReturn,i);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}

		sql_LocalTransport_Create_Check_Modifcation_Query(pLocalHost,sStatement,i);

		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)	
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = SET_HOST_TRANSPORT_ERR_DB_ERROR;

			mysql_set_error_for_LHTransport_Config_Reqs(pLocalHost,resp,iReturn,i);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}

		memset(sStatement,0,MAX_STATEMENT_SIZE);

		if(pRes->rowsCount() == 0) // ADD
		{
			sql_LocalTransport_Create_Add_Query(pLocalHost,sStatement,i);	
		}
		else // MOD
		{
			sql_LocalTransport_Create_Mod_Query(pLocalHost,sStatement,i);	
		}

		delete pRes;

		if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
		{
			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = SET_HOST_TRANSPORT_ERR_DB_ERROR;

			mysql_set_error_for_LHTransport_Config_Reqs(pLocalHost,resp,iReturn,i);
			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}
	}

	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_TransportType_Del_validation(::LocalHost *pLocalHost)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    sql_LocalTransport_Create_Validation_Query_for_LocalHost(pLocalHost,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
    {
        if(iReturn == DRE_DB_FAIL)
            iReturn = DEL_HOST_TRANSPORT_ERR_INVALID_LOCALHOST;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_TransportType_Del_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{

	DLOG_NONE(" > %s ",__FUNCTION__);
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	::LocalHost localLocalHost;
	::LocalHost *pLocalHost;
	int iCount;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;

	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_lhost())
		pLocalHost = pStackConfiguration->mutable_lhost();
	else
		pLocalHost = &localLocalHost;

	iCount = pLocalHost->transports_size();
	DLOG_DEBUG(" %s: transport_size = %d ",__FUNCTION__,iCount); 

	for(int i=0;i<iCount;i++)
	{
		pRes = NULL;

        if((iReturn = mysql_TransportType_Del_validation(pLocalHost)) != DRE_DB_SUCCESS)
        {
			mysql_set_error_for_LHTransport_Config_Reqs(pLocalHost,resp,iReturn,i);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

		memset(sStatement,0,MAX_STATEMENT_SIZE);
		sql_LocalTransport_Create_Check_Modifcation_Query(pLocalHost,sStatement,i);

		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)	
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = DEL_HOST_TRANSPORT_ERR_DB_ERROR;

			mysql_set_error_for_LHTransport_Config_Reqs(pLocalHost,resp,iReturn,i);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}


		memset(sStatement,0,MAX_STATEMENT_SIZE);

		if(pRes->rowsCount() == 0) // ADD
		{
			delete pRes;
			DLOG_ERROR("Record not Present"); 	
			mysql_set_error_for_LHTransport_Config_Reqs(pLocalHost,resp,DEL_HOST_ERR_TRANSPORT_NOT_PRESENT,i);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return DEL_HOST_ERR_TRANSPORT_NOT_PRESENT;
		}
		else // MOD
		{
			if((iReturn = check_last_localTransport_configuration(pLocalHost,i)) != DRE_DB_SUCCESS)
			{
				delete pRes;
				mysql_set_error_for_LHTransport_Config_Reqs(pLocalHost,resp,DEL_HOST_LAST_TRANSPORT_ENTRY,i);
				DLOG_NONE(" < %s ",__FUNCTION__);
				return iReturn;
			}
			else
			{
				sql_LocalTransport_Create_Delete_Query(pLocalHost,sStatement,i);	

			}
		}

		delete pRes;

		if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
		{
			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = DEL_HOST_TRANSPORT_ERR_DB_ERROR;

			mysql_set_error_for_LHTransport_Config_Reqs(pLocalHost,resp,iReturn,i);
			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}

	}

	if(iCount == 0)
	{
		
		memset(sStatement,0,MAX_STATEMENT_SIZE);
		sql_LocalTransport_Create_Delete_Query(pLocalHost,sStatement,0);	

		if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
		{
			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = DEL_HOST_TRANSPORT_ERR_DB_ERROR;

			mysql_set_error_for_LHTransport_Config_Reqs(pLocalHost,resp,iReturn,0);
			DLOG_NONE(" < %s ",__FUNCTION__);	
			return iReturn;
		}
	}

	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::check_last_localTransport_configuration(LocalHost *pLocalHost,int iIndex)
{
	DLOG_NONE(" > %s ",__FUNCTION__);
	::LocalHost localLocalHost;
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	DbStatus_e iReturn = DRE_DB_SUCCESS;

	localLocalHost.CopyFrom(*pLocalHost);
	localLocalHost.clear_transports();

	sql_LocalTransport_Create_Select_Query(&localLocalHost,sStatement,iIndex);

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
	memset(sStatement,0,MAX_STATEMENT_SIZE);
    // check if this is the last localTransport configuration 
    if(pRes->rowsCount() == 1)
	{
		iReturn = DRE_DB_FAIL;
	}
	else
	{
		iReturn = DRE_DB_SUCCESS;
	}

	delete pRes;

	DLOG_NONE(" < %s ",__FUNCTION__);
	return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_LocalHost_Del_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp)
{

	DLOG_NONE(" > %s ",__FUNCTION__);
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	::LocalHost localLocalHost;
	::LocalHost *pLocalHost;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;

	::StackConfiguration *pStackConfiguration = req->mutable_stackconfig();

	if(pStackConfiguration->has_lhost())
		pLocalHost = pStackConfiguration->mutable_lhost();
	else
		pLocalHost = &localLocalHost;



	pRes = NULL;
	memset(sStatement,0,MAX_STATEMENT_SIZE);
	sql_LocalHost_Create_Check_Modifcation_Query(pLocalHost,sStatement);

	if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
	{
		if(pRes != NULL)	
		{
			delete pRes;
		}

		DLOG_ERROR("Query Execution Failed: %s",sStatement);

		if(iReturn == DRE_DB_FAIL)
			iReturn = DEL_HOST_ERR_DB_ERROR;

		mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,iReturn);
		DLOG_NONE(" < %s ",__FUNCTION__);
		return iReturn;
	}


	memset(sStatement,0,MAX_STATEMENT_SIZE);

	if(pRes->rowsCount() == 0) // ADD
	{
		delete pRes;
		DLOG_ERROR("Record not Present"); 	
		mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,DEL_HOST_ERR_NOT_PRESENT);
		DLOG_NONE(" < %s ",__FUNCTION__);
		return DEL_HOST_ERR_NOT_PRESENT;
	}
	else // MOD
	{
		sql_LocalHost_Create_Delete_Query(pLocalHost,sStatement);	
	}

	delete pRes;

	if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
	{
		DLOG_ERROR("Query Execution Failed: %s",sStatement);

		if(iReturn == DRE_DB_FAIL)
			iReturn = DEL_HOST_ERR_DB_ERROR;

		DLOG_NONE(" < %s ",__FUNCTION__);	
		mysql_set_error_for_LocalHost_Config_Reqs(pLocalHost,resp,iReturn);
		return iReturn;
	}

	iReturn = mysql_TransportType_Del_Config_Reqs(req,resp);
	DLOG_NONE(" < %s ",__FUNCTION__);
	return iReturn;

}

