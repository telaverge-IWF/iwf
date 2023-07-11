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


void CMgrIwfDbInterface::mysql_set_error_for_IWFSigtranSetMapping_Config_Reqs(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig,IWFCfgResp *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(pIwfSigtranAssociationSetConfig->has_associationsetname())
        err->add_variables(pIwfSigtranAssociationSetConfig->associationsetname());

    if(iReturn == DEL_ASSOCIATIONSET_ERR_IS_ASSOCIATED)
    {
        char sStatement[MAX_STATEMENT_SIZE] = {0};

        IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;
        LocalIwfSigtranAssociationSetConfigObj.set_associationsetname(pIwfSigtranAssociationSetConfig->associationsetname()); 

        sql_IWFSigtranAssocAndAssocSet_Create_Select_Query(&LocalIwfSigtranAssociationSetConfigObj,sStatement);

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
        DLOG_NONE("%d",pRes->rowsCount());

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("IWF_SIGTRAN_ASSOC_NAME"))
                    err->add_variables(pRes->getString("IWF_SIGTRAN_ASSOC_NAME"));
            }
        }
        delete pRes;
    }

    if(iReturn == DEL_ASSOCIATIONSET_ERR_USED_IN_ROUTE)
    {
        char sStatement[MAX_STATEMENT_SIZE] = {0};

        IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfigObj;
        LocalIwfSigtranRemoteRouteConfigObj.set_associationsetname(pIwfSigtranAssociationSetConfig->associationsetname());

        sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfigObj,sStatement);

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
        DLOG_NONE("%d",pRes->rowsCount());

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("REMOTE_ROUTE_NAME"))
                    err->add_variables(pRes->getString("REMOTE_ROUTE_NAME"));
            }
        }
        delete pRes;
    }

    if(iReturn == ADD_ASSOCIATIONSET_ERR_ADJPOINTCODE_ALREADY_PRESENT
            || iReturn == MOD_ASSOCIATIONSET_ERR_ADJPOINTCODE_ALREADY_PRESENT)
    {
        char sStatement[MAX_STATEMENT_SIZE] = {0};
        sql::ResultSet *pRes = NULL;

        if(pIwfSigtranAssociationSetConfig->has_adjacenpointcode())
        {
            char adjPointCode[10];
            snprintf(adjPointCode,10,"%d",pIwfSigtranAssociationSetConfig->adjacenpointcode());
            err->add_variables(adjPointCode);
        }

        IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;
        LocalIwfSigtranAssociationSetConfigObj.set_adjacenpointcode(pIwfSigtranAssociationSetConfig->adjacenpointcode());

        sql_IWFSigtranAssocSet_Create_Select_Query(&LocalIwfSigtranAssociationSetConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        DLOG_NONE("%d",pRes->rowsCount());

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("IWF_SIGTRAN_ASSOC_SET_NAME"))
                    err->add_variables(pRes->getString("IWF_SIGTRAN_ASSOC_SET_NAME"));
            }
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(pIwfSigtranAssociationConfig->has_associationname())
        err->add_variables(pIwfSigtranAssociationConfig->associationname());

    if(iReturn == ADD_ASSOCIATION_ERR_LOCALENDPOINT_ALREADY_USED_IN_ASSOCIATION
            || iReturn == MOD_ASSOCIATION_ERR_LOCALENDPOINT_ALREADY_USED_IN_ASSOCIATION)
    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = NULL;
            pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();

        if(pIwfSigtranSctpEndPointConfig->has_endpointname())
            err->add_variables(pIwfSigtranSctpEndPointConfig->endpointname());
    

        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig = NULL;
        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
        pLocalIwfSigtranSctpEndPointConfig = LocalIwfSigtranAssociationConfigObj.mutable_localendpoint();
        pLocalIwfSigtranSctpEndPointConfig->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());
        Fill_IWFSigtranAssociation_protobuff(&LocalIwfSigtranAssociationConfigObj,resp);

        if(LocalIwfSigtranAssociationConfigObj.has_associationname())
            err->add_variables(LocalIwfSigtranAssociationConfigObj.associationname());
        else
        {
            pIwfSigtranSctpEndPointConfig = NULL;
            pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();
            IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj2;
            pLocalIwfSigtranSctpEndPointConfig = LocalIwfSigtranAssociationConfigObj2.mutable_localendpoint();
            pLocalIwfSigtranSctpEndPointConfig->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());
            Fill_IWFSigtranAssociation_protobuff(&LocalIwfSigtranAssociationConfigObj2,resp);

            if(LocalIwfSigtranAssociationConfigObj2.has_associationname())
                err->add_variables(LocalIwfSigtranAssociationConfigObj2.associationname());
            else
            {
                pIwfSigtranSctpEndPointConfig = NULL;
                pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();
                IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
                pLocalIwfSigtranSctpEndPointConfig = LocalIwfSigtranAssociationConfigObj.mutable_remoteendpoint();
                pLocalIwfSigtranSctpEndPointConfig->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

                Fill_IWFSigtranAssociation_protobuff(&LocalIwfSigtranAssociationConfigObj,resp);
                if(LocalIwfSigtranAssociationConfigObj.has_associationname())
                    err->add_variables(LocalIwfSigtranAssociationConfigObj.associationname());
            }
        }
    }
    else if(iReturn == ADD_ASSOCIATION_ERR_REMOTEENDPOINT_ALREADY_USED_IN_ASSOCIATION
            || iReturn == MOD_ASSOCIATION_ERR_REMOTEENDPOINT_ALREADY_USED_IN_ASSOCIATION)
    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = NULL;
        pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();

        if(pIwfSigtranSctpEndPointConfig->has_endpointname())
            err->add_variables(pIwfSigtranSctpEndPointConfig->endpointname());

        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig = NULL;
        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
        pLocalIwfSigtranSctpEndPointConfig = LocalIwfSigtranAssociationConfigObj.mutable_remoteendpoint();
        pLocalIwfSigtranSctpEndPointConfig->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());
        Fill_IWFSigtranAssociation_protobuff(&LocalIwfSigtranAssociationConfigObj,resp);

        if(LocalIwfSigtranAssociationConfigObj.has_associationname())
            err->add_variables(LocalIwfSigtranAssociationConfigObj.associationname());
        else
        {
            pIwfSigtranSctpEndPointConfig = NULL;
            pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();
            IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj2;
            pLocalIwfSigtranSctpEndPointConfig = LocalIwfSigtranAssociationConfigObj2.mutable_remoteendpoint();
            pLocalIwfSigtranSctpEndPointConfig->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());
            Fill_IWFSigtranAssociation_protobuff(&LocalIwfSigtranAssociationConfigObj2,resp);

            if(LocalIwfSigtranAssociationConfigObj2.has_associationname())
                err->add_variables(LocalIwfSigtranAssociationConfigObj2.associationname());
            else
            {
                pIwfSigtranSctpEndPointConfig = NULL;
                pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();
                IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
                pLocalIwfSigtranSctpEndPointConfig = LocalIwfSigtranAssociationConfigObj.mutable_localendpoint();
                pLocalIwfSigtranSctpEndPointConfig->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

                Fill_IWFSigtranAssociation_protobuff(&LocalIwfSigtranAssociationConfigObj,resp);
                if(LocalIwfSigtranAssociationConfigObj.has_associationname())
                    err->add_variables(LocalIwfSigtranAssociationConfigObj.associationname());
            }
        }
    }
    else if(iReturn == ADD_ASSOCIATION_ERR_SCTP_END_POINT_NOT_PRESENT 
            || iReturn == MOD_ASSOCIATION_ERR_SCTP_END_POINT_NOT_PRESENT)
    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = NULL;
        char sStatement[MAX_STATEMENT_SIZE] = {0};

        if(pIwfSigtranAssociationConfig->has_localendpoint())
        {
            pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();

            sql_IWFSctpEndpoint_Create_Check_Modifcation_Query(pIwfSigtranSctpEndPointConfig,sStatement);

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

            if(pRes->rowsCount() == 0)
            {
                err->add_variables(pIwfSigtranSctpEndPointConfig->endpointname());
                delete pRes;
                pRes = NULL;
            }
            else
            {
                memset(sStatement,0,sizeof(sStatement)); 
                delete pRes;
                pRes = NULL;
                pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();

                sql_IWFSctpEndpoint_Create_Check_Modifcation_Query(pIwfSigtranSctpEndPointConfig,sStatement);

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

                if(pRes->rowsCount() == 0)
                {
                    err->add_variables(pIwfSigtranSctpEndPointConfig->endpointname());
                }
                delete pRes;
                pRes = NULL;

            }
        }
        else if(pIwfSigtranAssociationConfig->has_remoteendpoint())
        {
            memset(sStatement,0,sizeof(sStatement)); 

            pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();

            sql_IWFSctpEndpoint_Create_Check_Modifcation_Query(pIwfSigtranSctpEndPointConfig,sStatement);

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

            if(pRes->rowsCount() == 0)
            {
                err->add_variables(pIwfSigtranSctpEndPointConfig->endpointname());
            }
            delete pRes;
            pRes = NULL;


        }

    }
    else if(iReturn == ADD_ASSOCIATION_ERR_ASSOCIATION_SET_NOT_PRESENT || 
            iReturn == MOD_ASSOCIATION_ERR_ASSOCIATION_SET_NOT_PRESENT ||
            iReturn == ADD_ASSOCIATION_MAPPING_ERR_REACHED_MAX_LIMIT)
    {
         err->add_variables(pIwfSigtranAssociationConfig->associationsetname());
    }
    else if(iReturn == ADD_ASSOCIATION_ERR_SCTP_PROFILE_NOT_PRESENT || iReturn == MOD_ASSOCIATION_ERR_SCTP_PROFILE_NOT_PRESENT)
    {
        if(pIwfSigtranAssociationConfig->has_sctpprofile())
        {
            IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = pIwfSigtranAssociationConfig->mutable_sctpprofile();
            err->add_variables(pIwfSigtranSctpProfileConfig->sctpprofilename());
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(pIwfSigtranMultihomingConfig-> has_otheripaddress())
        err->add_variables(pIwfSigtranMultihomingConfig->otheripaddress());


    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = NULL;
    if(pIwfSigtranSctpEndPointConfig->multihominginfo_size() > iIndex && iIndex > -1)
    {
	    pIwfSigtranMultihomingConfig = pIwfSigtranSctpEndPointConfig->mutable_multihominginfo(iIndex);
        if(pIwfSigtranMultihomingConfig-> has_otheripaddress())
        {
            err->add_variables(pIwfSigtranMultihomingConfig->otheripaddress());
        }
    }

    if(iReturn == MOD_SCTPENDPOINT_ERR_MAX_MULTIHOMING_IP)
    {
        char sMaxMultihomingIp[10];
        snprintf(sMaxMultihomingIp,10,"%d",MAX_MULTIHOMING_IP);
        err->add_variables(sMaxMultihomingIp);
    }
    if(pIwfSigtranSctpEndPointConfig ->has_endpointname())
        err->add_variables(pIwfSigtranSctpEndPointConfig->endpointname());


    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    sql::ResultSet *pRes = NULL;
    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(pIwfSigtranSctpEndPointConfig->has_endpointname())
        err->add_variables(pIwfSigtranSctpEndPointConfig->endpointname());

    if(iReturn == ADD_SCTPENDPOINT_ERR_IP_PORT_ALREADY_PRESENT || 
            iReturn == MOD_SCTPENDPOINT_ERR_IP_PORT_ALREADY_PRESENT)
    {
        if(pIwfSigtranSctpEndPointConfig->has_port())
        {
            char sPort[10];
            snprintf(sPort,10,"%d",pIwfSigtranSctpEndPointConfig->port());
            err->add_variables(sPort);
        }

        if(pIwfSigtranSctpEndPointConfig->has_ipaddress())
            err->add_variables(pIwfSigtranSctpEndPointConfig->ipaddress());

        IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
        LocalIwfSigtranSctpEndPointConfigObj.set_ipaddress(pIwfSigtranSctpEndPointConfig->ipaddress());
        LocalIwfSigtranSctpEndPointConfigObj.set_port(pIwfSigtranSctpEndPointConfig->port());
        Fill_IWFSctpEndpoint_protobuff(&LocalIwfSigtranSctpEndPointConfigObj,resp);

        err->add_variables(LocalIwfSigtranSctpEndPointConfigObj.endpointname());
    }
    else if(iReturn == DEL_SCTPENDPOINT_ERR_USED_IN_ASSOCIATION||
            iReturn == MOD_SCTPENDPOINT_ERR_USED_IN_ASSOCIATION||
            iReturn == DEL_SCTPENDPOINT_ERR_USED_IN_ASSOCIATION_AND_ASSOCIATION_IN_MULTIHOMING_IP)
    {
        char sStatement[MAX_STATEMENT_SIZE] = {0};

        IwfSigtranAssociationConfig lIwfSigtranAssociationConfigObj;
        IwfSigtranSctpEndPointConfig *pLocalpIwfSigtranSctpEndPointConfigReq = lIwfSigtranAssociationConfigObj.mutable_localendpoint();
        pLocalpIwfSigtranSctpEndPointConfigReq->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());  

        sql_IWFSigtranAssociation_Create_Select_Query(&lIwfSigtranAssociationConfigObj,sStatement);

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
        DLOG_NONE("%d",pRes->rowsCount());

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("IWF_SIGTRAN_ASSOC_NAME"))
                    err->add_variables(pRes->getString("IWF_SIGTRAN_ASSOC_NAME"));
            }
            delete pRes;
            pRes = NULL;
        }
        else
        {
            delete pRes;
            pRes = NULL;
            IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
            pLocalpIwfSigtranSctpEndPointConfigReq = LocalIwfSigtranAssociationConfigObj.mutable_remoteendpoint();
            pLocalpIwfSigtranSctpEndPointConfigReq->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname()); 

            sql_IWFSigtranAssociation_Create_Select_Query(&LocalIwfSigtranAssociationConfigObj,sStatement);

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
            DLOG_NONE("%d",pRes->rowsCount());

            if(pRes->rowsCount() > 0)
            {
                if(pRes->next())
                {
                    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_NAME"))
                        err->add_variables(pRes->getString("IWF_SIGTRAN_ASSOC_NAME"));
                }
            }
            delete pRes;
            pRes = NULL;
        }

        if(iReturn == DEL_SCTPENDPOINT_ERR_USED_IN_ASSOCIATION_AND_ASSOCIATION_IN_MULTIHOMING_IP)
        {
#if 0
            IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
            if(!pRes->isNull("IWF_SIGTRAN_ASSOC_NAME"))
                LocalIwfSigtranAssociationConfigObj.set_associationname(pRes->getString("IWF_SIGTRAN_ASSOC_NAME"));
            else
                LocalIwfSigtranAssociationConfigObj.set_associationname("");


            Fill_IWFSigtranMultihoming_protobuff(&LocalIwfSigtranAssociationConfigObj,resp,-1);
            int iCount = LocalIwfSigtranAssociationConfigObj.multihominginfo_size();
            char sIpAddress[MAX_STATEMENT_SIZE]={0};
            for(int i=0;i<iCount;i++)
            {
                IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = LocalIwfSigtranAssociationConfigObj.mutable_multihominginfo(i);
                snprintf(sIpAddress + strlen(sIpAddress),MAX_STATEMENT_SIZE,"%s,",pIwfSigtranMultihomingConfig->otheripaddress().c_str()); 
            }
            sIpAddress[strlen(sIpAddress)-1] = ' ';
            err->add_variables(sIpAddress);
#endif
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    sql::ResultSet *pRes = NULL;
    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(pIwfSigtranSctpProfileConfig->has_sctpprofilename())
        err->add_variables(pIwfSigtranSctpProfileConfig->sctpprofilename());

    if(iReturn == DEL_SCTPPROFILE_ERR_USED_IN_ASSOCIATION || 
                iReturn == MOD_SCTPPROFILE_ERR_ASSOCIATION_IN_ACTIVE_STATE || 
                iReturn == DEL_SCTPPROFILE_ERR_USED_IN_ASSOCIATION_AND_ASSOCIATION_IN_MUTIHOMING_IP)
    {
        char sStatement[MAX_STATEMENT_SIZE] = {0};

        IwfSigtranAssociationConfig lIwfSigtranAssociationConfigObj;
        IwfSigtranSctpProfileConfig *pLocalpIwfSigtranSctpProfileConfigReq = lIwfSigtranAssociationConfigObj.mutable_sctpprofile();
        pLocalpIwfSigtranSctpProfileConfigReq->set_sctpprofilename(pIwfSigtranSctpProfileConfig->sctpprofilename());  
        
        sql_IWFSigtranAssocAndAssocSet_Create_Select_Query(&lIwfSigtranAssociationConfigObj,sStatement);

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
        DLOG_NONE("pRes->rowsCount() = %d",pRes->rowsCount());

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("IWF_SIGTRAN_ASSOC_NAME"))
                    err->add_variables(pRes->getString("IWF_SIGTRAN_ASSOC_NAME"));
            }
        }

        if(iReturn == DEL_SCTPPROFILE_ERR_USED_IN_ASSOCIATION_AND_ASSOCIATION_IN_MUTIHOMING_IP)
        {
#if 0
            IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
            if(!pRes->isNull("IWF_SIGTRAN_ASSOC_NAME"))
                LocalIwfSigtranAssociationConfigObj.set_associationname(pRes->getString("IWF_SIGTRAN_ASSOC_NAME"));
            else
                LocalIwfSigtranAssociationConfigObj.set_associationname("");


            Fill_IWFSigtranMultihoming_protobuff(&LocalIwfSigtranAssociationConfigObj,resp,-1);
            int iCount = LocalIwfSigtranAssociationConfigObj.multihominginfo_size();
            char sIpAddress[MAX_STATEMENT_SIZE]={0};
            for(int i=0;i<iCount;i++)
            {
                IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = LocalIwfSigtranAssociationConfigObj.mutable_multihominginfo(i);
                snprintf(sIpAddress + strlen(sIpAddress),MAX_STATEMENT_SIZE,"%s,",pIwfSigtranMultihomingConfig->otheripaddress().c_str()); 
            }
            sIpAddress[strlen(sIpAddress)-1] = ' ';
            err->add_variables(sIpAddress);
#endif
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}


DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranAssocSet_protobuff(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFSigtranAssocSet_Create_Select_Query(pIwfSigtranAssociationSetConfig,sStatement);

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
            iReturn = GET_ASSOCIATIONSET_ERR_DB_ERROR;

        mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,iReturn);
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
                if(!pRes->isNull("IWF_SIGTRAN_ASSOC_SET_ID"))
                    pIwfSigtranAssociationSetConfig->set_associationsetid(pRes->getInt("IWF_SIGTRAN_ASSOC_SET_ID"));
                if(!pRes->isNull("IWF_SIGTRAN_ASSOC_SET_NAME"))
                    pIwfSigtranAssociationSetConfig->set_associationsetname(pRes->getString("IWF_SIGTRAN_ASSOC_SET_NAME"));
                if(!pRes->isNull("NI"))
                    pIwfSigtranAssociationSetConfig->set_networkindicator(pRes->getInt("NI"));
                if(!pRes->isNull("APC"))
                    pIwfSigtranAssociationSetConfig->set_adjacenpointcode(pRes->getInt("APC"));
                if(!pRes->isNull("ROUTING_CONTEXT"))
                    pIwfSigtranAssociationSetConfig->set_routingcontext(pRes->getInt("ROUTING_CONTEXT"));
#if 0
                if(!pRes->isNull("ACK_TIMER"))
                    pIwfSigtranAssociationSetConfig->set_acktimer(pRes->getInt("ACK_TIMER"));
                if(!pRes->isNull("SIGTRAN_MODE"))
                    pIwfSigtranAssociationSetConfig->set_sigtranmode(pRes->getString("SIGTRAN_MODE"));
#endif
                if(!pRes->isNull("TRAFFIC_MODE"))
                    pIwfSigtranAssociationSetConfig->set_trafficmode(pRes->getString("TRAFFIC_MODE"));
                if(!pRes->isNull("ASP_ID"))
                    pIwfSigtranAssociationSetConfig->set_aspid(pRes->getInt("ASP_ID"));
                if(!pRes->isNull("STATUS"))
                    pIwfSigtranAssociationSetConfig->set_status(pRes->getInt("STATUS"));
                if(!pRes->isNull("HOME_IP"))
                    pIwfSigtranAssociationSetConfig->set_homeip(pRes->getString("HOME_IP"));
                if(!pRes->isNull("IS_MEMBER"))
                    pIwfSigtranAssociationSetConfig->set_ismember(pRes->getInt("IS_MEMBER"));

            }
        }
        else
        {
            DLOG_DEBUG("pRes->rowsCount() = %d, returning GET_ASSOCIATIONSET_ERR_NO_DATA",pRes->rowsCount());
            delete pRes;
            return GET_ASSOCIATIONSET_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranAssocSetMapping_protobuff(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig,IWFCfgResp *resp,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFSigtranAssocSetMapping_Create_Select_Query(pIwfSigtranAssociationSetConfig,sStatement,iIndex);

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
            iReturn = GET_ASSOCIATIONSET_ERR_DB_ERROR;

        mysql_set_error_for_IWFSigtranSetMapping_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,iReturn,iIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = NULL;

    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            while(pRes->next())
            {
                if(pIwfSigtranAssociationSetConfig->associationinfo_size() > iIndex && iIndex > -1)
                {
                    pIwfSigtranAssociationConfig = pIwfSigtranAssociationSetConfig->mutable_associationinfo(iIndex);
                }
                else
                {
                    pIwfSigtranAssociationConfig = pIwfSigtranAssociationSetConfig->add_associationinfo();
                }

                if(!pRes->isNull("IWF_SIGTRAN_ASSOC_ID"))
                {
                    pIwfSigtranAssociationConfig->set_associationid(pRes->getInt("IWF_SIGTRAN_ASSOC_ID"));

                    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_SET_ID"))
                        pIwfSigtranAssociationConfig->set_associationsetid(pRes->getInt("IWF_SIGTRAN_ASSOC_SET_ID"));

                    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_MAPPING_ID"))
                        pIwfSigtranAssociationConfig->set_associationmappingid(pRes->getInt("IWF_SIGTRAN_ASSOC_MAPPING_ID"));

                    Fill_IWFSigtranAssociationSetConfigForAssociation(pIwfSigtranAssociationConfig);
                }

                if(!pRes->isNull("IWF_SIGTRAN_ASSOC_SET_ID"))
                    pIwfSigtranAssociationSetConfig->set_associationsetid(pRes->getInt("IWF_SIGTRAN_ASSOC_SET_ID"));
            }
        }
        else
        {
            delete pRes;
            return GET_ASSOCIATIONSET_MAPPING_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranAssociation_protobuff(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFSigtranAssociation_Create_Select_Query(pIwfSigtranAssociationConfig,sStatement);

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
            iReturn = GET_ASSOCIATION_ERR_DB_ERROR;

        mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);
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
                if(!pRes->isNull("IWF_SIGTRAN_ASSOC_ID"))
                    pIwfSigtranAssociationConfig->set_associationid(pRes->getInt("IWF_SIGTRAN_ASSOC_ID"));
                if(!pRes->isNull("IWF_SIGTRAN_ASSOC_NAME"))
                   pIwfSigtranAssociationConfig->set_associationname(pRes->getString("IWF_SIGTRAN_ASSOC_NAME"));
                if(!pRes->isNull("STATUS"))
                    pIwfSigtranAssociationConfig->set_status(pRes->getInt("STATUS"));
                if(!pRes->isNull("IWF_SIGTRAN_SCTP_PROFILE_ID"))
                {
                    IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = pIwfSigtranAssociationConfig->mutable_sctpprofile();
                    pIwfSigtranSctpProfileConfig->set_sctpprofileid(pRes->getInt("IWF_SIGTRAN_SCTP_PROFILE_ID"));
                }
                if(!pRes->isNull("IWF_LOCAL_SCTP_ENDPOINT_ID"))
                {
                    IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();
                    pIwfSigtranSctpEndPointConfig->set_sctpendpointid(pRes->getInt("IWF_LOCAL_SCTP_ENDPOINT_ID"));
                }
                if(!pRes->isNull("IWF_REMOTE_SCTP_ENDPOINT_ID"))
                {
                    IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();
                    pIwfSigtranSctpEndPointConfig->set_sctpendpointid(pRes->getInt("IWF_REMOTE_SCTP_ENDPOINT_ID"));
                }
                if(!pRes->isNull("ASP_ID"))
                    pIwfSigtranAssociationConfig->set_aspid(pRes->getInt("ASP_ID"));
            }
        }
        else
        {
            delete pRes;
            return GET_ASSOCIATION_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranMultihoming_protobuff(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFSigtranMultihoming_Create_Select_Query(pIwfSigtranSctpEndPointConfig,sStatement,iIndex);

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
            iReturn = GET_REALMOFPEER_ERR_DB_ERROR;

        mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn,iIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = NULL;
    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            while(pRes->next())
            {
                if(pIwfSigtranSctpEndPointConfig->multihominginfo_size() > iIndex && iIndex > -1)
                {
                    pIwfSigtranMultihomingConfig = pIwfSigtranSctpEndPointConfig ->mutable_multihominginfo(iIndex);
                }
                else
                {
                    pIwfSigtranMultihomingConfig = pIwfSigtranSctpEndPointConfig ->add_multihominginfo();
                }

                if(!pRes->isNull("IWF_SIGTRAN_MULTIHOMING_ID"))
                    pIwfSigtranMultihomingConfig->set_multihomingid(pRes->getInt("IWF_SIGTRAN_MULTIHOMING_ID"));
                if(!pRes->isNull("IWF_SCTP_ENDPOINT_ID"))
                   pIwfSigtranSctpEndPointConfig->set_sctpendpointid(pRes->getInt("IWF_SCTP_ENDPOINT_ID"));
                if(!pRes->isNull("OTHERHOME_IPADDR"))
                   pIwfSigtranMultihomingConfig->set_otheripaddress(pRes->getString("OTHERHOME_IPADDR"));

            }
        }
        else
        {
            delete pRes;
            return GET_ASSOCIATION_MULTIHOMING_ERR_NO_DATA;
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


DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranMultihoming_Get_Config_Reqs(IwfSigtransMultihomingConfig *pIwfSigtransMultihomingConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);

    return Fill_IWFSigtranMultihomings_protobuff(pIwfSigtransMultihomingConfig,resp);
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranMultihomings_protobuff(IwfSigtransMultihomingConfig *pIwfSigtransMultihomingConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    int i=0;
    int ifData = 0;

    IwfSigtranMultihomingConfig LocalIwfSigtranMultihomingObj;
    IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = NULL;

    int iCount = pIwfSigtransMultihomingConfig->multihominginfo_size();
    DLOG_INFO("pIwfSigtransMultihomingConfig->multihominginfo_size() = %d",iCount);
    do
    {
        if(iCount != 0)
            pIwfSigtranMultihomingConfig = pIwfSigtransMultihomingConfig->mutable_multihominginfo(i);
        else
            pIwfSigtranMultihomingConfig = &LocalIwfSigtranMultihomingObj;

        sql_IWFSigtranMultihoming_Create_Select_Query(pIwfSigtranMultihomingConfig,sStatement);

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
                iReturn = GET_SCTPENDPOINT_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranMultihomingConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
            if(pRes->rowsCount() != 0)
            {
                IwfSigtransMultihomingConfig *LocalIwfSigtransMultihomingConfig = resp->mutable_multihominginfo();

                while(pRes->next())
                {
                    pIwfSigtranMultihomingConfig = LocalIwfSigtransMultihomingConfig->add_multihominginfo();

                    ifData = 1;

                    if(!pRes->isNull("IWF_SIGTRAN_MULTIHOMING_ID"))
                        pIwfSigtranMultihomingConfig->set_multihomingid(pRes->getInt("IWF_SIGTRAN_MULTIHOMING_ID"));
                    if(!pRes->isNull("IWF_SCTP_ENDPOINT_ID"))
                        pIwfSigtranMultihomingConfig->set_sctpendpointid(pRes->getInt("IWF_SCTP_ENDPOINT_ID"));
                    if(!pRes->isNull("OTHERHOME_IPADDR"))
                        pIwfSigtranMultihomingConfig->set_otheripaddress(pRes->getString("OTHERHOME_IPADDR"));

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
        DLOG_DEBUG("There is no data in the table setting GET_MULTIHOMINGIP_ERR_NO_DATA");
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(GET_MULTIHOMINGIP_ERR_NO_DATA);
        err->set_errormsgkey(iwfErrorMap[GET_MULTIHOMINGIP_ERR_NO_DATA]);
        DLOG_DEBUG("Error key is %s", (iwfErrorMap[GET_MULTIHOMINGIP_ERR_NO_DATA]).c_str());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}



DbStatus_e CMgrIwfDbInterface::Fill_IWFSctpEndpoints_protobuff(IwfSigtranSctpEndPointsConfig *pIwfSigtranSctpEndPointsConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    int i=0;
    int ifData = 0;

    IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
    IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = NULL;

    int iCount = pIwfSigtranSctpEndPointsConfig->sctpendpointinfo_size();
    DLOG_INFO("pIwfSigtranSctpEndPointsConfig->sctpendpointinfo_size() = %d",iCount);
    do
    {
        if(iCount != 0)
            pIwfSigtranSctpEndPointConfig = pIwfSigtranSctpEndPointsConfig->mutable_sctpendpointinfo(i);
        else
            pIwfSigtranSctpEndPointConfig = &LocalIwfSigtranSctpEndPointConfigObj;

        sql_IWFSctpEndpoint_Create_Select_Query(pIwfSigtranSctpEndPointConfig,sStatement);

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
                iReturn = GET_SCTPENDPOINT_ERR_DB_ERROR;

            mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
            if(pRes->rowsCount() != 0)
            {
                IwfSigtranSctpEndPointsConfig *LocalIwfSigtranSctpEndPointsConfig = resp->mutable_sctpendpointinfo();

                while(pRes->next())
                {
                    pIwfSigtranSctpEndPointConfig = LocalIwfSigtranSctpEndPointsConfig->add_sctpendpointinfo();

                    ifData = 1;
                    if(!pRes->isNull("IWF_SCTP_ENDPOINT_ID"))
                        pIwfSigtranSctpEndPointConfig->set_sctpendpointid(pRes->getInt("IWF_SCTP_ENDPOINT_ID"));

                    if(!pRes->isNull("ENDPOINT_NAME"))
                        pIwfSigtranSctpEndPointConfig->set_endpointname(pRes->getString("ENDPOINT_NAME"));

                    if(!pRes->isNull("ENDPOINT_TYPE"))
                        pIwfSigtranSctpEndPointConfig->set_endpointtype(pRes->getString("ENDPOINT_TYPE"));

                    if(!pRes->isNull("IP_ADDRESS"))
                        pIwfSigtranSctpEndPointConfig->set_ipaddress(pRes->getString("IP_ADDRESS"));

                    if(!pRes->isNull("PORT"))
                        pIwfSigtranSctpEndPointConfig->set_port(pRes->getInt("PORT"));

                    if(!pRes->isNull("TRANSPORT_TYPE"))
                        pIwfSigtranSctpEndPointConfig->set_transporttype(pRes->getString("TRANSPORT_TYPE"));

                    if(!pRes->isNull("IS_CLIENT"))
                        pIwfSigtranSctpEndPointConfig->set_isclient(pRes->getInt("IS_CLIENT"));
                    
                    Fill_IWFSigtranMultihoming_protobuff(pIwfSigtranSctpEndPointConfig,resp,-1);

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
        DLOG_DEBUG("There is no data in the table setting GET_SCTPENDPOINT_ERR_NO_DATA");
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(GET_SCTPENDPOINT_ERR_NO_DATA);
        err->set_errormsgkey(iwfErrorMap[GET_SCTPENDPOINT_ERR_NO_DATA]);
        DLOG_DEBUG("Error key is %s", (iwfErrorMap[GET_SCTPENDPOINT_ERR_NO_DATA]).c_str());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}


DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociations_Get_Config_Reqs(IwfSigtranAssociationsConfig *req,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);

    return Fill_IWFSigtranAssociations_protobuff(req,resp);
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociationSets_Get_Config_Reqs(IwfSigtranAssociationSetsConfig *req,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);

    return Fill_IWFSigtranAssocSets_protobuff(req,resp);
}


DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranAssocSets_protobuff(IwfSigtranAssociationSetsConfig *pIwfSigtranAssociationSetsConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    int i=0;
    int ifData = 0;

    IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;
    IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig = NULL;

    int iCount = pIwfSigtranAssociationSetsConfig->associationsetinfo_size();
    DLOG_INFO("pIwfSigtranAssociationSetsConfig->associationsetinfo_size() = %d",iCount);
    do
    {
        if(iCount != 0)
            pIwfSigtranAssociationSetConfig = pIwfSigtranAssociationSetsConfig->mutable_associationsetinfo(i);
        else
            pIwfSigtranAssociationSetConfig = &LocalIwfSigtranAssociationSetConfigObj;

        sql_IWFSigtranAssocSet_Create_Select_Query(pIwfSigtranAssociationSetConfig,sStatement);

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
                iReturn = GET_ASSOCIATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
            if(pRes->rowsCount() != 0)
            {
                IwfSigtranAssociationSetsConfig *LocalIwfSigtranAssociationSetsConfig = resp->mutable_associationsetinfo();

                while(pRes->next())
                {
                    pIwfSigtranAssociationSetConfig = LocalIwfSigtranAssociationSetsConfig->add_associationsetinfo();

                    ifData = 1;
                    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_SET_ID"))
                        pIwfSigtranAssociationSetConfig->set_associationsetid(pRes->getInt("IWF_SIGTRAN_ASSOC_SET_ID"));
                    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_SET_NAME"))
                        pIwfSigtranAssociationSetConfig->set_associationsetname(pRes->getString("IWF_SIGTRAN_ASSOC_SET_NAME"));
                    if(!pRes->isNull("NI"))
                        pIwfSigtranAssociationSetConfig->set_networkindicator(pRes->getInt("NI"));
                    if(!pRes->isNull("APC"))
                        pIwfSigtranAssociationSetConfig->set_adjacenpointcode(pRes->getInt("APC"));
                    if(!pRes->isNull("ROUTING_CONTEXT"))
                        pIwfSigtranAssociationSetConfig->set_routingcontext(pRes->getInt("ROUTING_CONTEXT"));
#if 0
                    if(!pRes->isNull("ACK_TIMER"))
                        pIwfSigtranAssociationSetConfig->set_acktimer(pRes->getInt("ACK_TIMER"));
                    if(!pRes->isNull("SIGTRAN_MODE"))
                        pIwfSigtranAssociationSetConfig->set_sigtranmode(pRes->getString("SIGTRAN_MODE"));
#endif
                    if(!pRes->isNull("TRAFFIC_MODE"))
                        pIwfSigtranAssociationSetConfig->set_trafficmode(pRes->getString("TRAFFIC_MODE"));
                    if(!pRes->isNull("ASP_ID"))
                        pIwfSigtranAssociationSetConfig->set_aspid(pRes->getInt("ASP_ID"));
                    if(!pRes->isNull("STATUS"))
                        pIwfSigtranAssociationSetConfig->set_status(pRes->getInt("STATUS"));
                    if(!pRes->isNull("HOME_IP"))
                        pIwfSigtranAssociationSetConfig->set_homeip(pRes->getString("HOME_IP"));
                    if(!pRes->isNull("IS_MEMBER"))
                        pIwfSigtranAssociationSetConfig->set_ismember(pRes->getInt("IS_MEMBER"));

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
        DLOG_DEBUG("There is no data in the table setting GET_ASSOCIATION_ERR_NO_DATA");
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(GET_ASSOCIATIONSET_ERR_NO_DATA);
        err->set_errormsgkey(iwfErrorMap[GET_ASSOCIATIONSET_ERR_NO_DATA]);
        DLOG_DEBUG("Error key is %s", (iwfErrorMap[GET_ASSOCIATIONSET_ERR_NO_DATA]).c_str());

        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranAssociations_protobuff(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    int i=0;
    int ifData = 0;

    IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
    IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = NULL;

    int iCount = pIwfSigtranAssociationsConfig->associationinfo_size();
    DLOG_INFO("pIwfSigtranAssociationsConfig->associationinfo_size() = %d",iCount);
    do
    {
        if(iCount != 0)
            pIwfSigtranAssociationConfig = pIwfSigtranAssociationsConfig->mutable_associationinfo(i);
        else
            pIwfSigtranAssociationConfig = &LocalIwfSigtranAssociationConfigObj;

        sql_IWFSigtranAssociation_Create_Select_Query(pIwfSigtranAssociationConfig,sStatement);

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
                iReturn = GET_ASSOCIATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
            if(pRes->rowsCount() != 0)
            {
                IwfSigtranAssociationsConfig *LocalIwfSigtranAssociationsConfig = resp->mutable_associationinfo();

                while(pRes->next())
                {
                    pIwfSigtranAssociationConfig = LocalIwfSigtranAssociationsConfig->add_associationinfo();

                    ifData = 1;
                    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_ID"))
                    {
                        pIwfSigtranAssociationConfig->set_associationid(pRes->getInt("IWF_SIGTRAN_ASSOC_ID"));
                        IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;
                        IwfSigtranAssociationConfig *pLocalIwfSigtranAssociationConfig = LocalIwfSigtranAssociationSetConfigObj.add_associationinfo();
                        pLocalIwfSigtranAssociationConfig->CopyFrom(*pIwfSigtranAssociationConfig);
                        Fill_IWFSigtranAssocSetMapping_protobuff(&LocalIwfSigtranAssociationSetConfigObj,resp,0);
                        pIwfSigtranAssociationConfig->set_associationmappingid(pLocalIwfSigtranAssociationConfig->associationmappingid());
                        if(pLocalIwfSigtranAssociationConfig->has_homeip())
                           pIwfSigtranAssociationConfig->set_homeip(pLocalIwfSigtranAssociationConfig->homeip());
                        pIwfSigtranAssociationConfig->set_routingkey(pLocalIwfSigtranAssociationConfig->routingkey());
                        Fill_IWFSigtranAssocSet_protobuff(&LocalIwfSigtranAssociationSetConfigObj,resp);
                        pIwfSigtranAssociationConfig->set_associationsetname(LocalIwfSigtranAssociationSetConfigObj.associationsetname());
                        pIwfSigtranAssociationConfig->set_associationsetid(LocalIwfSigtranAssociationSetConfigObj.associationsetid());
                    }
                    
                    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_NAME"))
                        pIwfSigtranAssociationConfig->set_associationname(pRes->getString("IWF_SIGTRAN_ASSOC_NAME"));
                        
                    if(!pRes->isNull("STATUS"))
                        pIwfSigtranAssociationConfig->set_status(pRes->getInt("STATUS"));
                    if(!pRes->isNull("IWF_SIGTRAN_SCTP_PROFILE_ID"))
                    {
                        IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = pIwfSigtranAssociationConfig->mutable_sctpprofile();
                        pIwfSigtranSctpProfileConfig->set_sctpprofileid(pRes->getInt("IWF_SIGTRAN_SCTP_PROFILE_ID"));

                        IwfSigtranSctpProfileConfig LocalIwfSigtranSctpProfileConfigObj;
                        LocalIwfSigtranSctpProfileConfigObj.CopyFrom(*pIwfSigtranSctpProfileConfig);

                        Fill_IWFSigtranSCTPProfile_protobuff(&LocalIwfSigtranSctpProfileConfigObj,resp);
                        pIwfSigtranSctpProfileConfig->CopyFrom(LocalIwfSigtranSctpProfileConfigObj);

                    }
                    if(!pRes->isNull("IWF_LOCAL_SCTP_ENDPOINT_ID"))
                    {
                        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();
                        pIwfSigtranSctpEndPointConfig->set_sctpendpointid(pRes->getInt("IWF_LOCAL_SCTP_ENDPOINT_ID"));

                        IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
                        LocalIwfSigtranSctpEndPointConfigObj.CopyFrom(*pIwfSigtranSctpEndPointConfig);

                        Fill_IWFSctpEndpoint_protobuff(&LocalIwfSigtranSctpEndPointConfigObj,resp);
                        pIwfSigtranSctpEndPointConfig->CopyFrom(LocalIwfSigtranSctpEndPointConfigObj);
                    }
                    if(!pRes->isNull("IWF_REMOTE_SCTP_ENDPOINT_ID"))
                    {
                        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();
                        pIwfSigtranSctpEndPointConfig->set_sctpendpointid(pRes->getInt("IWF_REMOTE_SCTP_ENDPOINT_ID"));

                        IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
                        LocalIwfSigtranSctpEndPointConfigObj.CopyFrom(*pIwfSigtranSctpEndPointConfig);

                        Fill_IWFSctpEndpoint_protobuff(&LocalIwfSigtranSctpEndPointConfigObj,resp);
                        pIwfSigtranSctpEndPointConfig->CopyFrom(LocalIwfSigtranSctpEndPointConfigObj);
                    }
                    if(!pRes->isNull("ASP_ID"))
                        pIwfSigtranAssociationConfig->set_aspid(pRes->getInt("ASP_ID"));

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
        DLOG_DEBUG("There is no data in the table setting GET_ASSOCIATION_ERR_NO_DATA");
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(GET_ASSOCIATION_ERR_NO_DATA);
        err->set_errormsgkey(iwfErrorMap[GET_ASSOCIATION_ERR_NO_DATA]);
        DLOG_DEBUG("Error key is %s", (iwfErrorMap[GET_ASSOCIATION_ERR_NO_DATA]).c_str());

        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}


DbStatus_e CMgrIwfDbInterface::Fill_IWFSctpProfiles_protobuff(IwfSigtranSctpProfilesConfig *pIwfSigtranSctpProfilesConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    int i=0;
    int ifData = 0;

    IwfSigtranSctpProfileConfig LocalIwfSigtranSctpProfileConfigObj;
    IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = NULL;

    int iCount = pIwfSigtranSctpProfilesConfig->sctpprofileinfo_size();
    DLOG_INFO("pIwfSigtranSctpProfilesConfig->sctpprofileinfo_size() = %d",iCount);
    do
    {
        if(iCount != 0)
            pIwfSigtranSctpProfileConfig = pIwfSigtranSctpProfilesConfig->mutable_sctpprofileinfo(i);
        else
            pIwfSigtranSctpProfileConfig = &LocalIwfSigtranSctpProfileConfigObj;

        sql_IWFSigtranSCTPProfile_Create_Select_Query(pIwfSigtranSctpProfileConfig,sStatement);

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
                iReturn = GET_SCTPPROFILE_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(pIwfSigtranSctpProfileConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
            if(pRes->rowsCount() != 0)
            {
                IwfSigtranSctpProfilesConfig *LocalIwfSigtranSctpProfilesConfig = resp->mutable_sctpprofileinfo();

                while(pRes->next())
                {
                    pIwfSigtranSctpProfileConfig = LocalIwfSigtranSctpProfilesConfig->add_sctpprofileinfo();

                    ifData = 1;
                    if(!pRes->isNull("IWF_SIGTRAN_SCTP_PROFILE_ID"))
                        pIwfSigtranSctpProfileConfig->set_sctpprofileid(pRes->getInt("IWF_SIGTRAN_SCTP_PROFILE_ID"));
                    if(!pRes->isNull("IWF_SIGTRAN_SCTP_PROFILE_NAME"))
                        pIwfSigtranSctpProfileConfig->set_sctpprofilename(pRes->getString("IWF_SIGTRAN_SCTP_PROFILE_NAME"));
                    if(!pRes->isNull("HEARTBEAT_ENABLE"))
                        pIwfSigtranSctpProfileConfig->set_heartbeatenable(pRes->getInt("HEARTBEAT_ENABLE"));
                    if(!pRes->isNull("HEARTBEAT_TIMEOUT"))
                        pIwfSigtranSctpProfileConfig->set_heartbeattimeout(pRes->getInt("HEARTBEAT_TIMEOUT"));
                    if(!pRes->isNull("INIT_TIMEOUT"))
                        pIwfSigtranSctpProfileConfig->set_inittimeout(pRes->getInt("INIT_TIMEOUT"));
                    if(!pRes->isNull("ASSOC_MAX_ATTEMPTS"))
                        pIwfSigtranSctpProfileConfig->set_assocmaxattempt(pRes->getInt("ASSOC_MAX_ATTEMPTS"));
                    if(!pRes->isNull("MAX_ATTEMPTS"))
                        pIwfSigtranSctpProfileConfig->set_maxattempt(pRes->getInt("MAX_ATTEMPTS"));
                    if(!pRes->isNull("RTO_MAX"))
                        pIwfSigtranSctpProfileConfig->set_rtomax(pRes->getInt("RTO_MAX"));
                    if(!pRes->isNull("RTO_MIN"))
                        pIwfSigtranSctpProfileConfig->set_rtomin(pRes->getInt("RTO_MIN"));
                    if(!pRes->isNull("RTO_INITIAL"))
                        pIwfSigtranSctpProfileConfig->set_rtoinitial(pRes->getInt("RTO_INITIAL"));
                    if(!pRes->isNull("PATH_FAILURE_RETRY_COUNT"))
                        pIwfSigtranSctpProfileConfig->set_pathfailureretrycount(pRes->getInt("PATH_FAILURE_RETRY_COUNT"));
                    if(!pRes->isNull("MAX_IN_STREAMS"))
                        pIwfSigtranSctpProfileConfig->set_maxinstreams(pRes->getInt("MAX_IN_STREAMS"));
                    if(!pRes->isNull("NUM_OUT_STREAMS"))
                        pIwfSigtranSctpProfileConfig->set_numoutstreams(pRes->getInt("NUM_OUT_STREAMS"));
                    if(!pRes->isNull("COOKIE_LIFE"))
                        pIwfSigtranSctpProfileConfig->set_cookielife(pRes->getInt("COOKIE_LIFE"));
                    if(!pRes->isNull("SEND_TIME_OUT"))
                        pIwfSigtranSctpProfileConfig->set_sendtimeout(pRes->getInt("SEND_TIME_OUT"));
                    if(!pRes->isNull("RECEIVE_TIME_OUT"))
                        pIwfSigtranSctpProfileConfig->set_receivetimeout(pRes->getInt("RECEIVE_TIME_OUT"));
                    if(!pRes->isNull("SHUTDOWN_TIMEOUT"))
                        pIwfSigtranSctpProfileConfig->set_shutdowntimeout(pRes->getInt("SHUTDOWN_TIMEOUT"));
                    if(!pRes->isNull("PMTU_TIMEOUT"))
                        pIwfSigtranSctpProfileConfig->set_pmtutimeout(pRes->getInt("PMTU_TIMEOUT"));
                    if(!pRes->isNull("SACK_DELAY"))
                        pIwfSigtranSctpProfileConfig->set_sackdelay(pRes->getInt("SACK_DELAY"));
                    if(!pRes->isNull("SEND_BUF_SIZE"))
                        pIwfSigtranSctpProfileConfig->set_sendbufsize(pRes->getInt("SEND_BUF_SIZE"));
                    if(!pRes->isNull("RECV_BUF_SIZE"))
                        pIwfSigtranSctpProfileConfig->set_recvbufsize(pRes->getInt("RECV_BUF_SIZE"));
                    if(!pRes->isNull("RECONNECT_TIMEOUT"))
                        pIwfSigtranSctpProfileConfig->set_reconnecttimeout(pRes->getInt("RECONNECT_TIMEOUT"));

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
        DLOG_DEBUG("There is no data in the table setting GET_SCTPPROFILE_ERR_NO_DATA");
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(GET_SCTPPROFILE_ERR_NO_DATA);
        err->set_errormsgkey(iwfErrorMap[GET_SCTPPROFILE_ERR_NO_DATA]);
        DLOG_DEBUG("Error key is %s", (iwfErrorMap[GET_SCTPPROFILE_ERR_NO_DATA]).c_str());

        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}


DbStatus_e CMgrIwfDbInterface::mysql_IWFSctpProfile_Check_Association_isEnabled(IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    IwfSigtranAssociationConfig lIwfSigtranAssociationConfigObj;
    IwfSigtranSctpProfileConfig *plocalIwfSigtranSctpProfileConfig = NULL;
    plocalIwfSigtranSctpProfileConfig = lIwfSigtranAssociationConfigObj.mutable_sctpprofile();

    plocalIwfSigtranSctpProfileConfig->set_sctpprofilename(pIwfSigtranSctpProfileConfig->sctpprofilename());

    sql_IWFSigtranAssocAndAssocSet_Create_Select_Query(&lIwfSigtranAssociationConfigObj,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = MOD_SCTPPROFILE_ERR_DB_ERROR;

        mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(pIwfSigtranSctpProfileConfig,resp,iReturn);

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() > 0)
    {
        while(pRes->next())
        {
            if(pRes->getInt("ASSOCIATION_STATUS") == 0)
            {
                iReturn = IWF_DB_SUCCESS_SEND;
            }
            else
            {
                delete pRes;
                DLOG_ERROR("Association is in Active state");   
                mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(pIwfSigtranSctpProfileConfig,resp,MOD_SCTPPROFILE_ERR_ASSOCIATION_IN_ACTIVE_STATE);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return MOD_SCTPPROFILE_ERR_ASSOCIATION_IN_ACTIVE_STATE;
            }
        }
    }
    else
    {
        delete pRes;
        return IWF_DB_SUCCESS;
    }
    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrIwfDbInterface::IWFSigranAssociationSetsConfig_Fill_For_SctpProfiles(IwfSigtranAssociationSetsConfig *pIwfSigtranAssociationSetsConfig,IwfSigtranSctpProfilesConfig *pIwfSigtranSctpProfilesConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    int iReturn = IWF_DB_SUCCESS;
    int iCount = pIwfSigtranSctpProfilesConfig->sctpprofileinfo_size();

    IwfSigtranAssociationsConfig LocalIwfSigtranAssociationsConfig;
    IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig = &LocalIwfSigtranAssociationsConfig;

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = pIwfSigtranSctpProfilesConfig->mutable_sctpprofileinfo(i);

        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
        IwfSigtranSctpProfileConfig *pLocalIwfSigtranSctpProfileConfig = LocalIwfSigtranAssociationConfigObj.mutable_sctpprofile();

        pLocalIwfSigtranSctpProfileConfig->set_sctpprofilename(pIwfSigtranSctpProfileConfig->sctpprofilename());

        if((iReturn = Fill_IWFSigtranAssocAndAssocSet_protobuff(&LocalIwfSigtranAssociationConfigObj,resp,pIwfSigtranAssociationsConfig)) == GET_ASSOCIATIONSET_MAPPING_ERR_NO_DATA)
        {
            DLOG_ERROR("SctpProfile is not associated with any Association");
            return IWF_DB_SUCCESS;
        }
    }

    iCount = pIwfSigtranAssociationsConfig->associationinfo_size();

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = pIwfSigtranAssociationsConfig->mutable_associationinfo(i);
        
        int iCountSets = pIwfSigtranAssociationSetsConfig->associationsetinfo_size();
        int iFlag = 0;
        for(int j=0; j<iCountSets; j++)
        {
            IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig = pIwfSigtranAssociationSetsConfig->mutable_associationsetinfo(j);
            if(pIwfSigtranAssociationSetConfig->associationsetname() == pIwfSigtranAssociationConfig->associationsetname())
            {
                iFlag = 1;
                IwfSigtranAssociationConfig *pLocalIwfSigtranAssociationConfig = pIwfSigtranAssociationSetConfig->add_associationinfo();                
                pLocalIwfSigtranAssociationConfig->CopyFrom(*pIwfSigtranAssociationConfig);
                break;
            }

        }
        if(!iFlag)
        {
            IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig = pIwfSigtranAssociationSetsConfig->add_associationsetinfo();
            pIwfSigtranAssociationSetConfig->set_associationsetname(pIwfSigtranAssociationConfig->associationsetname());
            pIwfSigtranAssociationSetConfig->set_associationsetid(pIwfSigtranAssociationConfig->associationsetid());

        }

    }

    int iCountSets = pIwfSigtranAssociationSetsConfig->associationsetinfo_size();


    for(int j=0;j<iCountSets;j++)
    {
        IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig = pIwfSigtranAssociationSetsConfig->mutable_associationsetinfo(j);
       
        iReturn = Fill_IWFSigtranAssocSet_protobuff(pIwfSigtranAssociationSetConfig,resp);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());

        iCount = pIwfSigtranAssociationSetConfig->associationinfo_size();
        for(int i=0;i<iCount;i++)
        {
            IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = pIwfSigtranAssociationSetConfig->mutable_associationinfo(i);
            iReturn = Fill_IWFSigtranAssociation_protobuff(pIwfSigtranAssociationConfig,resp);
            if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
                DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());

            IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();
            iReturn = Fill_IWFSctpEndpoint_protobuff(pLocalIwfSigtranSctpEndPointConfig,resp);
            if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
                DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());

            pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();
            iReturn = Fill_IWFSctpEndpoint_protobuff(pLocalIwfSigtranSctpEndPointConfig,resp);
            if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
                DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());

            IwfSigtranSctpProfileConfig *pLocalIwfSigtranSctpProfileConfig = pIwfSigtranAssociationConfig->mutable_sctpprofile();
            iReturn = Fill_IWFSigtranSCTPProfile_protobuff(pLocalIwfSigtranSctpProfileConfig,resp);
            if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
                DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranSctpProfiles_Mod_Config_Reqs(IwfSigtranSctpProfilesConfig *pIwfSigtranSctpProfilesConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
//    int iSendFlag = -1;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranSctpProfilesConfig->sctpprofileinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(MOD_SCTPPROFILE_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[MOD_SCTPPROFILE_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = pIwfSigtranSctpProfilesConfig->mutable_sctpprofileinfo(i);
#if 0
        iReturn = mysql_IWFSctpProfile_Check_Association_isEnabled(pIwfSigtranSctpProfileConfig,resp);
        if(iReturn == IWF_DB_SUCCESS)
            iSendFlag = 0;
        else if(iReturn == IWF_DB_SUCCESS_SEND)
        {
            if(iSendFlag == -1)
                iSendFlag = 1;
        }
        else
        {
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
#endif
        sql_IWFSigtranSCTPProfile_Create_Check_Modifcation_Query(pIwfSigtranSctpProfileConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_SCTPPROFILE_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(pIwfSigtranSctpProfileConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Not Present");   
            mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(pIwfSigtranSctpProfileConfig,resp,MOD_SCTPPROFILE_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_SCTPPROFILE_ERR_NOT_PRESENT;
        }
        else // MOD
        {
            sql_IWFSigtranSCTPProfile_Create_Mod_Query(pIwfSigtranSctpProfileConfig,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_SCTPPROFILE_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(pIwfSigtranSctpProfileConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }
#if 0
    if(iSendFlag == 1)
        iReturn = IWF_DB_SUCCESS_SEND;
#endif
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranSctpProfiles_Add_Config_Reqs(IwfSigtranSctpProfilesConfig *pIwfSigtranSctpProfilesConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranSctpProfilesConfig->sctpprofileinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(ADD_SCTPPROFILE_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[ADD_SCTPPROFILE_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = pIwfSigtranSctpProfilesConfig->mutable_sctpprofileinfo(i);
        sql_IWFSigtranSCTPProfile_Create_Check_Modifcation_Query(pIwfSigtranSctpProfileConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_SCTPENDPOINT_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(pIwfSigtranSctpProfileConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_IWFSigtranSCTPProfile_Create_Add_Query(pIwfSigtranSctpProfileConfig,sStatement);
        }
        else // MOD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present:ADD_SCTPPROFILE_ERR_ALREADY_PRESENT!!");   
            mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(pIwfSigtranSctpProfileConfig,resp,ADD_SCTPPROFILE_ERR_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_SCTPPROFILE_ERR_ALREADY_PRESENT;
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_SCTPPROFILE_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(pIwfSigtranSctpProfileConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranSctpProfiles_Get_Config_Reqs(IwfSigtranSctpProfilesConfig *pIwfSigtranSctpProfilesConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);

    return Fill_IWFSctpProfiles_protobuff(pIwfSigtranSctpProfilesConfig,resp);
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranSctpEndPoints_Get_Config_Reqs(IwfSigtranSctpEndPointsConfig *pIwfSigtranSctpEndPointsConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);

    return Fill_IWFSctpEndpoints_protobuff(pIwfSigtranSctpEndPointsConfig,resp);
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFSctpEndpoint_protobuff(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFSctpEndpoint_Create_Select_Query(pIwfSigtranSctpEndPointConfig,sStatement);

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
            iReturn = GET_SCTPENDPOINT_ERR_DB_ERROR;

        mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
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
                if(!pRes->isNull("IWF_SCTP_ENDPOINT_ID"))
                    pIwfSigtranSctpEndPointConfig->set_sctpendpointid(pRes->getInt("IWF_SCTP_ENDPOINT_ID"));
                if(!pRes->isNull("ENDPOINT_NAME"))
                   pIwfSigtranSctpEndPointConfig->set_endpointname(pRes->getString("ENDPOINT_NAME"));
                if(!pRes->isNull("ENDPOINT_TYPE"))
                   pIwfSigtranSctpEndPointConfig->set_endpointtype(pRes->getString("ENDPOINT_TYPE"));
                if(!pRes->isNull("IP_ADDRESS"))
                   pIwfSigtranSctpEndPointConfig->set_ipaddress(pRes->getString("IP_ADDRESS"));
                if(!pRes->isNull("PORT"))
                   pIwfSigtranSctpEndPointConfig->set_port(pRes->getInt("PORT"));

                Fill_IWFSigtranMultihoming_protobuff(pIwfSigtranSctpEndPointConfig,resp,0); 
#if 0
                if(!pRes->isNull("TRANSPORT_TYPE"))
                   pIwfSigtranSctpEndPointConfig->set_transporttype(pRes->getString("TRANSPORT_TYPE"));
                if(!pRes->isNull("IS_CLIENT"))
                   pIwfSigtranSctpEndPointConfig->set_isclient(pRes->getInt("IS_CLIENT"));
#endif
            }
        }
        else
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_SCTPENDPOINT_ERR_NO_DATA;
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

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranAssocAndAssocSet_protobuff(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig,IWFCfgResp *resp,IwfSigtranAssociationSetsConfig *pIwfSigtranAssociationSetsConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFSigtranAssocAndAssocSet_Create_Select_Query(pIwfSigtranAssociationSetConfig,sStatement);

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
            iReturn = GET_ASSOCIATIONSET_ERR_DB_ERROR;

        mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,iReturn);
        DLOG_DEBUG("iReturn = %d",iReturn);
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
                if(IWFSigtranAssociationSetsConfig_check_already_entered(pIwfSigtranAssociationSetsConfig,pRes) == IWF_DB_FAIL) 
                {
                    IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig = pIwfSigtranAssociationSetsConfig->add_associationsetinfo(); 
                    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_SET_ID"))
                        pIwfSigtranAssociationSetConfig->set_associationsetid(pRes->getInt("IWF_SIGTRAN_ASSOC_SET_ID"));
                    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_SET_NAME"))
                        pIwfSigtranAssociationSetConfig->set_associationsetname(pRes->getString("IWF_SIGTRAN_ASSOC_SET_NAME"));

                    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_ID"))
                    {
                        IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = pIwfSigtranAssociationSetConfig->add_associationinfo();
                        if(!pRes->isNull("IWF_SIGTRAN_ASSOC_MAPPING_ID"))
                            pIwfSigtranAssociationConfig->set_associationmappingid(pRes->getInt("IWF_SIGTRAN_ASSOC_MAPPING_ID"));
                        Fill_only_IWFSigtranAssociation(pIwfSigtranAssociationConfig,pRes); 
                    }
                }
            }
        }
        else
        {
            delete pRes;
            return GET_ASSOCIATIONSET_MAPPING_ERR_NO_DATA;
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
    return IWF_DB_SUCCESS;
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranAssocAndAssocSet_protobuff(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig,IWFCfgResp *resp,IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFSigtranAssocAndAssocSet_Create_Select_Query(pIwfSigtranAssociationConfig,sStatement);

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
            iReturn = GET_ASSOCIATIONSET_ERR_DB_ERROR;

        mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);
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
                if(IWFSigtranAssociationsConfig_check_already_entered(pIwfSigtranAssociationsConfig,pRes) == IWF_DB_FAIL) 
                {
                    IwfSigtranAssociationConfig *pIwfSigtranAssociationConfigLocal = pIwfSigtranAssociationsConfig->add_associationinfo(); 
                    Fill_only_IWFSigtranAssociation(pIwfSigtranAssociationConfigLocal,pRes); 
                }
            }
        }
        else
        {
            delete pRes;
            return GET_ASSOCIATIONSET_MAPPING_ERR_NO_DATA;
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
    return IWF_DB_SUCCESS;
}

void CMgrIwfDbInterface::Fill_only_IWFSigtranAssociation(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig,sql::ResultSet *pRes)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_SET_ID"))
        pIwfSigtranAssociationConfig->set_associationsetid(pRes->getInt("IWF_SIGTRAN_ASSOC_SET_ID"));
    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_SET_NAME"))
        pIwfSigtranAssociationConfig->set_associationsetname(pRes->getString("IWF_SIGTRAN_ASSOC_SET_NAME"));
    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_ID"))
        pIwfSigtranAssociationConfig->set_associationid(pRes->getInt("IWF_SIGTRAN_ASSOC_ID"));
    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_MAPPING_ID"))
        pIwfSigtranAssociationConfig->set_associationmappingid(pRes->getInt("IWF_SIGTRAN_ASSOC_MAPPING_ID"));
    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_NAME"))
        pIwfSigtranAssociationConfig->set_associationname(pRes->getString("IWF_SIGTRAN_ASSOC_NAME"));
    if(!pRes->isNull("IWF_SIGTRAN_SCTP_PROFILE_ID"))
    {
        IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = pIwfSigtranAssociationConfig->mutable_sctpprofile();
        pIwfSigtranSctpProfileConfig->set_sctpprofileid(pRes->getInt("IWF_SIGTRAN_SCTP_PROFILE_ID"));
    }

    if(!pRes->isNull("IWF_LOCAL_SCTP_ENDPOINT_ID"))
    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranLocalSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();
        pIwfSigtranLocalSctpEndPointConfig->set_sctpendpointid(pRes->getInt("IWF_LOCAL_SCTP_ENDPOINT_ID"));
    }

    if(!pRes->isNull("IWF_REMOTE_SCTP_ENDPOINT_ID"))
    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranRemoteSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();
        pIwfSigtranRemoteSctpEndPointConfig->set_sctpendpointid(pRes->getInt("IWF_REMOTE_SCTP_ENDPOINT_ID"));
    }
    if(!pRes->isNull("ASP_ID"))
        pIwfSigtranAssociationConfig->set_aspid(pRes->getInt("ASP_ID"));

#if 0
    if(!pRes->isNull("OTHERHOME_IPADDR"))
    {
        IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = pIwfSigtranAssociationConfig->add_multihominginfo(); 
        pIwfSigtranMultihomingConfig->set_associationid(pRes->getInt("IWF_SIGTRAN_ASSOC_ID"));
        pIwfSigtranMultihomingConfig->set_otheripaddress(pRes->getString("OTHERHOME_IPADDR"));
    }
#endif

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranAssociationSetConfigForAssociation(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfig;
    LocalIwfSigtranAssociationSetConfig.set_associationsetid(pIwfSigtranAssociationConfig->associationsetid());
    sql_IWFSigtranAssocSet_Create_Select_Query(&LocalIwfSigtranAssociationSetConfig, sStatement);
     
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
            iReturn = GET_ASSOCIATIONSET_ERR_DB_ERROR;

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
                if(!pRes->isNull("ROUTING_CONTEXT"))
                    pIwfSigtranAssociationConfig->set_routingkey(pRes->getInt("ROUTING_CONTEXT"));
                if(!pRes->isNull("HOME_IP"))
                    pIwfSigtranAssociationConfig->set_homeip(pRes->getString("HOME_IP"));
            }
        }
        else
        {
            delete pRes;
            return GET_ASSOCIATIONSET_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranSCTPProfile_protobuff(IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFSigtranSCTPProfile_Create_Select_Query(pIwfSigtranSctpProfileConfig,sStatement);

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
            iReturn = GET_SCTPPROFILE_ERR_DB_ERROR;

        mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(pIwfSigtranSctpProfileConfig,resp,iReturn);
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
                if(!pRes->isNull("IWF_SIGTRAN_SCTP_PROFILE_ID"))
                    pIwfSigtranSctpProfileConfig->set_sctpprofileid(pRes->getInt("IWF_SIGTRAN_SCTP_PROFILE_ID"));
                if(!pRes->isNull("IWF_SIGTRAN_SCTP_PROFILE_NAME"))
                    pIwfSigtranSctpProfileConfig->set_sctpprofilename(pRes->getString("IWF_SIGTRAN_SCTP_PROFILE_NAME"));
                if(!pRes->isNull("HEARTBEAT_ENABLE"))
                    pIwfSigtranSctpProfileConfig->set_heartbeatenable(pRes->getInt("HEARTBEAT_ENABLE"));
                if(!pRes->isNull("HEARTBEAT_TIMEOUT"))
                    pIwfSigtranSctpProfileConfig->set_heartbeattimeout(pRes->getInt("HEARTBEAT_TIMEOUT"));
                if(!pRes->isNull("INIT_TIMEOUT"))
                    pIwfSigtranSctpProfileConfig->set_inittimeout(pRes->getInt("INIT_TIMEOUT"));
                if(!pRes->isNull("ASSOC_MAX_ATTEMPTS"))
                    pIwfSigtranSctpProfileConfig->set_assocmaxattempt(pRes->getInt("ASSOC_MAX_ATTEMPTS"));
                if(!pRes->isNull("MAX_ATTEMPTS"))
                    pIwfSigtranSctpProfileConfig->set_maxattempt(pRes->getInt("MAX_ATTEMPTS"));
                if(!pRes->isNull("RTO_MAX"))
                    pIwfSigtranSctpProfileConfig->set_rtomax(pRes->getInt("RTO_MAX"));
                if(!pRes->isNull("RTO_MIN"))
                    pIwfSigtranSctpProfileConfig->set_rtomin(pRes->getInt("RTO_MIN"));
                if(!pRes->isNull("RTO_INITIAL"))
                    pIwfSigtranSctpProfileConfig->set_rtoinitial(pRes->getInt("RTO_INITIAL"));
                if(!pRes->isNull("PATH_FAILURE_RETRY_COUNT"))
                    pIwfSigtranSctpProfileConfig->set_pathfailureretrycount(pRes->getInt("PATH_FAILURE_RETRY_COUNT"));
                if(!pRes->isNull("MAX_IN_STREAMS"))
                    pIwfSigtranSctpProfileConfig->set_maxinstreams(pRes->getInt("MAX_IN_STREAMS"));
                if(!pRes->isNull("NUM_OUT_STREAMS"))
                    pIwfSigtranSctpProfileConfig->set_numoutstreams(pRes->getInt("NUM_OUT_STREAMS"));
                if(!pRes->isNull("COOKIE_LIFE"))
                    pIwfSigtranSctpProfileConfig->set_cookielife(pRes->getInt("COOKIE_LIFE"));
                if(!pRes->isNull("SEND_TIME_OUT"))
                    pIwfSigtranSctpProfileConfig->set_sendtimeout(pRes->getInt("SEND_TIME_OUT"));
                if(!pRes->isNull("RECEIVE_TIME_OUT"))
                    pIwfSigtranSctpProfileConfig->set_receivetimeout(pRes->getInt("RECEIVE_TIME_OUT"));
                if(!pRes->isNull("SHUTDOWN_TIMEOUT"))
                    pIwfSigtranSctpProfileConfig->set_shutdowntimeout(pRes->getInt("SHUTDOWN_TIMEOUT"));
                if(!pRes->isNull("PMTU_TIMEOUT"))
                    pIwfSigtranSctpProfileConfig->set_pmtutimeout(pRes->getInt("PMTU_TIMEOUT"));
                if(!pRes->isNull("SACK_DELAY"))
                    pIwfSigtranSctpProfileConfig->set_sackdelay(pRes->getInt("SACK_DELAY"));
                if(!pRes->isNull("SEND_BUF_SIZE"))
                    pIwfSigtranSctpProfileConfig->set_sendbufsize(pRes->getInt("SEND_BUF_SIZE"));
                if(!pRes->isNull("RECV_BUF_SIZE"))
                    pIwfSigtranSctpProfileConfig->set_recvbufsize(pRes->getInt("RECV_BUF_SIZE"));
                if(!pRes->isNull("RECONNECT_TIMEOUT"))
                    pIwfSigtranSctpProfileConfig->set_reconnecttimeout(pRes->getInt("RECONNECT_TIMEOUT"));


            }
        }
        else
        {
            delete pRes;
            return GET_SCTPPROFILE_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::IWFSigranAssociationsConfig_Fill_For_MultihomingIP(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IwfSigtransMultihomingConfig *pIwfSigtransMultihomingConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    int iReturn = IWF_DB_SUCCESS;
#if 0
    int iCount = pIwfSigtransMultihomingConfig->multihominginfo_size();

    IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = NULL;
    if(iCount>0)
    {

        IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = pIwfSigtransMultihomingConfig->mutable_multihominginfo(0);
        IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;
        pIwfSigtranAssociationConfig = pIwfSigtranAssociationsConfig->add_associationinfo();
        IwfSigtranMultihomingConfig *pLocalIwfSigtranMultihomingConfig = pIwfSigtranAssociationConfig->add_multihominginfo();
        pLocalIwfSigtranMultihomingConfig->set_otheripaddress(pIwfSigtranMultihomingConfig->otheripaddress());

        //Fill_IWFSigtranMultihoming_protobuff(pIwfSigtranAssociationConfig,resp,0);
        Fill_IWFSigtranAssociation_protobuff(pIwfSigtranAssociationConfig,resp);
        Fill_IWFSigtranAssocSetMapping_protobuff(&LocalIwfSigtranAssociationSetConfigObj,resp,0);

        pIwfSigtranAssociationConfig->set_associationsetid(LocalIwfSigtranAssociationSetConfigObj.associationsetid());
    }

    for(int i=1;i<iCount;i++)
    {
        IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = pIwfSigtransMultihomingConfig->mutable_multihominginfo(i);

        IwfSigtranMultihomingConfig *pLocalIwfSigtranMultihomingConfig = pIwfSigtranAssociationConfig->add_multihominginfo();
        pLocalIwfSigtranMultihomingConfig->set_otheripaddress(pIwfSigtranMultihomingConfig->otheripaddress());
    }
#endif
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

#if 1

DbStatus_e CMgrIwfDbInterface::IWFSigranAssociationsConfig_Fill_For_Association(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IwfSigtranAssociationsConfig *pOrginalIwfSigtranAssociationsConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    int iReturn = IWF_DB_SUCCESS;
    int iCount = pOrginalIwfSigtranAssociationsConfig->associationinfo_size();

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = pOrginalIwfSigtranAssociationsConfig->mutable_associationinfo(i);

        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
        LocalIwfSigtranAssociationConfigObj.set_associationname(pIwfSigtranAssociationConfig->associationname());

        if((iReturn = Fill_IWFSigtranAssocAndAssocSet_protobuff(&LocalIwfSigtranAssociationConfigObj,resp,pIwfSigtranAssociationsConfig)) == GET_ASSOCIATIONSET_MAPPING_ERR_NO_DATA)
        {
            DLOG_ERROR("SctpProfile is not associated with any Association");
            return IWF_DB_SUCCESS;
        }
    }

    iCount = pIwfSigtranAssociationsConfig->associationinfo_size();

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = pIwfSigtranAssociationsConfig->mutable_associationinfo(i);
        iReturn = Fill_IWFSigtranAssociation_protobuff(pIwfSigtranAssociationConfig,resp);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());
#if 0
        iReturn = Fill_IWFSigtranMultihoming_protobuff(pIwfSigtranAssociationConfig,resp,-1);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());
#endif
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranLocalSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();
        iReturn = Fill_IWFSctpEndpoint_protobuff(pLocalIwfSigtranLocalSctpEndPointConfig,resp);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());

        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranRemoteSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();
        iReturn = Fill_IWFSctpEndpoint_protobuff(pLocalIwfSigtranRemoteSctpEndPointConfig,resp);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());

        IwfSigtranSctpProfileConfig *pLocalIwfSigtranSctpProfileConfig = pIwfSigtranAssociationConfig->mutable_sctpprofile();
        iReturn = Fill_IWFSigtranSCTPProfile_protobuff(pLocalIwfSigtranSctpProfileConfig,resp);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());

        // To fill RoutingKey and HomeIp
        Fill_IWFSigtranAssociationSetConfigForAssociation(pIwfSigtranAssociationConfig);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


#endif

DbStatus_e CMgrIwfDbInterface::IWFSigranAssociationsConfig_Fill_For_SctpProfile(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IwfSigtranSctpProfilesConfig *pIwfSigtranSctpProfilesConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    int iReturn = IWF_DB_SUCCESS;
    int iCount = pIwfSigtranSctpProfilesConfig->sctpprofileinfo_size();

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = pIwfSigtranSctpProfilesConfig->mutable_sctpprofileinfo(i);

        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
        IwfSigtranSctpProfileConfig *pLocalIwfSigtranSctpProfileConfig = LocalIwfSigtranAssociationConfigObj.mutable_sctpprofile();

        pLocalIwfSigtranSctpProfileConfig->set_sctpprofilename(pIwfSigtranSctpProfileConfig->sctpprofilename());

        if((iReturn = Fill_IWFSigtranAssocAndAssocSet_protobuff(&LocalIwfSigtranAssociationConfigObj,resp,pIwfSigtranAssociationsConfig)) == GET_ASSOCIATIONSET_MAPPING_ERR_NO_DATA)
        {
            DLOG_ERROR("SctpProfile is not associated with any Association");
            return IWF_DB_SUCCESS;
        }
    }

    iCount = pIwfSigtranAssociationsConfig->associationinfo_size();

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = pIwfSigtranAssociationsConfig->mutable_associationinfo(i);
        iReturn = Fill_IWFSigtranAssociation_protobuff(pIwfSigtranAssociationConfig,resp);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());
#if 0
        iReturn = Fill_IWFSigtranMultihoming_protobuff(pIwfSigtranAssociationConfig,resp,-1);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());
#endif
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();
        iReturn = Fill_IWFSctpEndpoint_protobuff(pLocalIwfSigtranSctpEndPointConfig,resp);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());

        pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();
        iReturn = Fill_IWFSctpEndpoint_protobuff(pLocalIwfSigtranSctpEndPointConfig,resp);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());

        IwfSigtranSctpProfileConfig *pLocalIwfSigtranSctpProfileConfig = pIwfSigtranAssociationConfig->mutable_sctpprofile();
        iReturn = Fill_IWFSigtranSCTPProfile_protobuff(pLocalIwfSigtranSctpProfileConfig,resp);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrIwfDbInterface::IWFSigranAssociationsConfig_Fill_For_SctpEndPoint(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IwfSigtranSctpEndPointsConfig *pIwfSigtranSctpEndPointsConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    int iReturn = IWF_DB_SUCCESS;
    int iCount = pIwfSigtranSctpEndPointsConfig->sctpendpointinfo_size();

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranSctpEndPointsConfig->mutable_sctpendpointinfo(i);

        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig = LocalIwfSigtranAssociationConfigObj.mutable_localendpoint();

        pLocalIwfSigtranSctpEndPointConfig->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

        if((iReturn = Fill_IWFSigtranAssocAndAssocSet_protobuff(&LocalIwfSigtranAssociationConfigObj,resp,pIwfSigtranAssociationsConfig)) == GET_ASSOCIATIONSET_MAPPING_ERR_NO_DATA)
        {
            pLocalIwfSigtranSctpEndPointConfig = LocalIwfSigtranAssociationConfigObj.mutable_remoteendpoint();
            pLocalIwfSigtranSctpEndPointConfig->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());
            
            if((iReturn = Fill_IWFSigtranAssocAndAssocSet_protobuff(&LocalIwfSigtranAssociationConfigObj,resp,pIwfSigtranAssociationsConfig)) == GET_ASSOCIATIONSET_MAPPING_ERR_NO_DATA)
            {
                DLOG_ERROR("SctpEndPoint is not associated with any Association");
                return IWF_DB_SUCCESS;
            }
        }
    }

    iCount = pIwfSigtranAssociationsConfig->associationinfo_size();

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = pIwfSigtranAssociationsConfig->mutable_associationinfo(i);
        iReturn = Fill_IWFSigtranAssociation_protobuff(pIwfSigtranAssociationConfig,resp);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());
#if 0
        iReturn = Fill_IWFSigtranMultihoming_protobuff(pIwfSigtranAssociationConfig,resp,-1);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());
#endif
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();
        iReturn = Fill_IWFSctpEndpoint_protobuff(pLocalIwfSigtranSctpEndPointConfig,resp);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());

        pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();
        iReturn = Fill_IWFSctpEndpoint_protobuff(pLocalIwfSigtranSctpEndPointConfig,resp);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());

        IwfSigtranSctpProfileConfig *pLocalIwfSigtranSctpProfileConfig = pIwfSigtranAssociationConfig->mutable_sctpprofile();
        iReturn = Fill_IWFSigtranSCTPProfile_protobuff(pLocalIwfSigtranSctpProfileConfig,resp);
        if(iReturn != IWF_DB_SUCCESS || iReturn != IWF_DB_FAIL)
            DLOG_WARNING("Return = %d - %s",iReturn,iwfErrorMap[iReturn].c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::IWFSigtranAssociationSetsConfig_check_already_entered(IwfSigtranAssociationSetsConfig *pIwfSigtranAssociationSetsConfig,sql::ResultSet *pRes)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount;
    iCount = pIwfSigtranAssociationSetsConfig->associationsetinfo_size();

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig = pIwfSigtranAssociationSetsConfig->mutable_associationsetinfo(i);

        if(pIwfSigtranAssociationSetConfig->associationsetname() == pRes->getString("IWF_SIGTRAN_ASSOC_SET_NAME"))
        {
#if 0
            int iCount = pIwfSigtranAssociationSetConfig->associationinfo_size();
            for(int j=0;j<iCount;j++)
            {
                IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = pIwfSigtranAssociationSetConfig->mutable_associationinfo(j);
                if(pIwfSigtranAssociationConfig->associationname() == pRes->getString("IWF_SIGTRAN_ASSOC_NAME"))
                {
                    IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = pIwfSigtranAssociationConfig->add_multihominginfo(); 

                    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_ID"))
                        pIwfSigtranMultihomingConfig->set_associationid(pRes->getInt("IWF_SIGTRAN_ASSOC_ID"));
                    if(!pRes->isNull("OTHERHOME_IPADDR"))
                        pIwfSigtranMultihomingConfig->set_otheripaddress(pRes->getString("OTHERHOME_IPADDR"));
                    return IWF_DB_SUCCESS;
                }
            }

#endif
            IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = pIwfSigtranAssociationSetConfig->add_associationinfo(); 
            
            Fill_only_IWFSigtranAssociation(pIwfSigtranAssociationConfig,pRes);
            return IWF_DB_SUCCESS;
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_FAIL;
}

DbStatus_e CMgrIwfDbInterface::IWFSigtranAssociationsConfig_check_already_entered(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,sql::ResultSet *pRes)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

#if 0
    int iCount;
    iCount = pIwfSigtranAssociationsConfig->associationinfo_size();

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = pIwfSigtranAssociationsConfig->mutable_associationinfo(i);
        if(pIwfSigtranAssociationConfig->associationname() == pRes->getString("IWF_SIGTRAN_ASSOC_NAME"))
        {
           IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = pIwfSigtranAssociationConfig->add_multihominginfo(); 

           if(!pRes->isNull("IWF_SIGTRAN_ASSOC_ID"))
                pIwfSigtranMultihomingConfig->set_associationid(pRes->getInt("IWF_SIGTRAN_ASSOC_ID"));
           if(!pRes->isNull("OTHERHOME_IPADDR"))
                pIwfSigtranMultihomingConfig->set_otheripaddress(pRes->getString("OTHERHOME_IPADDR"));

           DLOG_NONE(" < %s ",__FUNCTION__);
           return IWF_DB_SUCCESS;
        }

    }
#endif

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_FAIL;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFSctpEndPoint_Validation(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    {
        IwfSigtranSctpEndPointConfig lIwfSigtranSctpEndPointConfig;
        lIwfSigtranSctpEndPointConfig.set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());    

        sql_IWFSctpEndpoint_Create_Select_Query(&lIwfSigtranSctpEndPointConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_SCTPENDPOINT_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            DLOG_ERROR("Record alrady present");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_SCTPENDPOINT_ERR_ALREADY_PRESENT;
        }
        delete pRes;
    }
    {
        IwfSigtranSctpEndPointConfig lIwfSigtranSctpEndPointConfig;
        lIwfSigtranSctpEndPointConfig.set_ipaddress(pIwfSigtranSctpEndPointConfig->ipaddress());
        lIwfSigtranSctpEndPointConfig.set_port(pIwfSigtranSctpEndPointConfig->port());    

        sql_IWFSctpEndpoint_Create_Select_Query(&lIwfSigtranSctpEndPointConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_SCTPENDPOINT_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            DLOG_ERROR("Record Present with same ip and port");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_SCTPENDPOINT_ERR_IP_PORT_ALREADY_PRESENT;
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFSctpEndPoint_Check_Association_isEnabled(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
{
        IwfSigtranAssociationConfig lIwfSigtranAssociationConfigObj;
        IwfSigtranSctpEndPointConfig *plocalIwfSigtranSctpEndPointConfig = NULL;
        plocalIwfSigtranSctpEndPointConfig = lIwfSigtranAssociationConfigObj.mutable_remoteendpoint();

        plocalIwfSigtranSctpEndPointConfig->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSigtranAssocAndAssocSet_Create_Select_Query(&lIwfSigtranAssociationConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;

            mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        DLOG_NONE("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() > 0)
        {
            while(pRes->next())
            {
                if(pRes->getInt("ASSOCIATION_STATUS") == 0)
                {
                    iReturn = IWF_DB_SUCCESS_SEND;
                }
                else
                {
                    delete pRes;
                    DLOG_ERROR("Association is in Active state");   
                    mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,MOD_SCTPENDPOINT_ERR_ASSOCIATION_IN_ACTIVE_STATE);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_SCTPENDPOINT_ERR_ASSOCIATION_IN_ACTIVE_STATE;
                }
            }
        }
        else
        {
            iReturn = IWF_DB_SUCCESS;
        }
        delete pRes;
    }
    {
        IwfSigtranAssociationConfig lIwfSigtranAssociationConfigObj;
        IwfSigtranSctpEndPointConfig *plocalIwfSigtranSctpEndPointConfig = NULL;
        plocalIwfSigtranSctpEndPointConfig = lIwfSigtranAssociationConfigObj.mutable_localendpoint();

        plocalIwfSigtranSctpEndPointConfig->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSigtranAssocAndAssocSet_Create_Select_Query(&lIwfSigtranAssociationConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;

            mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        DLOG_NONE("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() > 0)
        {
            while(pRes->next())
            {
                if(pRes->getInt("ASSOCIATION_STATUS") == 0)
                {
                    iReturn = IWF_DB_SUCCESS_SEND;
                }
                else
                {
                    delete pRes;
                    DLOG_ERROR("Association is in Active state");   
                    mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,MOD_SCTPENDPOINT_ERR_ASSOCIATION_IN_ACTIVE_STATE);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_SCTPENDPOINT_ERR_ASSOCIATION_IN_ACTIVE_STATE;
                }
            }
        }
        else
        {
            iReturn = IWF_DB_SUCCESS;
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFSctpEndPoint_Mod_Validation(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    {
        sql_IWFSctpEndpoint_Create_Check_Modifcation_Query(pIwfSigtranSctpEndPointConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Not Present");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_SCTPENDPOINT_ERR_NOT_PRESENT;
        }
        delete pRes;
    }
#if 0
    {
        pRes = NULL; 
        IwfSigtranAssociationConfig lIwfSigtranAssociationConfigObj;
        IwfSigtranSctpEndPointConfig *plocalIwfSigtranSctpEndPointConfig = NULL;
        plocalIwfSigtranSctpEndPointConfig = lIwfSigtranAssociationConfigObj.mutable_remoteendpoint();

        plocalIwfSigtranSctpEndPointConfig->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSigtranAssocAndAssocSet_Create_Select_Query(&lIwfSigtranAssociationConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        DLOG_NONE("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            DLOG_ERROR("Association is in Active state");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_SCTPENDPOINT_ERR_USED_IN_ASSOCIATION;
        }
        delete pRes;
    }

    {
        pRes = NULL;
        IwfSigtranAssociationConfig lIwfSigtranAssociationConfigObj;
        IwfSigtranSctpEndPointConfig *plocalIwfSigtranSctpEndPointConfig = NULL;
        plocalIwfSigtranSctpEndPointConfig = lIwfSigtranAssociationConfigObj.mutable_localendpoint();

        plocalIwfSigtranSctpEndPointConfig->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSigtranAssocAndAssocSet_Create_Select_Query(&lIwfSigtranAssociationConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        DLOG_NONE("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            DLOG_ERROR("Association is in Active state");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_SCTPENDPOINT_ERR_USED_IN_ASSOCIATION;
        }
        delete pRes;
    }
#endif
    IwfSigtranSctpEndPointConfig lIwfSigtranSctpEndPointConfig;


    if(!pIwfSigtranSctpEndPointConfig->has_ipaddress() && pIwfSigtranSctpEndPointConfig->has_port())
    {
        IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
        LocalIwfSigtranSctpEndPointConfigObj.set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

        Fill_IWFSctpEndpoint_protobuff(&LocalIwfSigtranSctpEndPointConfigObj,resp);
        lIwfSigtranSctpEndPointConfig.set_ipaddress(LocalIwfSigtranSctpEndPointConfigObj.ipaddress());
        pIwfSigtranSctpEndPointConfig->set_ipaddress(LocalIwfSigtranSctpEndPointConfigObj.ipaddress());
    }

    if(pIwfSigtranSctpEndPointConfig->has_ipaddress() && !pIwfSigtranSctpEndPointConfig->has_port())
    {
        IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
        LocalIwfSigtranSctpEndPointConfigObj.set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

        Fill_IWFSctpEndpoint_protobuff(&LocalIwfSigtranSctpEndPointConfigObj,resp);
        lIwfSigtranSctpEndPointConfig.set_port(LocalIwfSigtranSctpEndPointConfigObj.port());
        pIwfSigtranSctpEndPointConfig->set_port(LocalIwfSigtranSctpEndPointConfigObj.port());
    }

    if(pIwfSigtranSctpEndPointConfig->has_ipaddress() && pIwfSigtranSctpEndPointConfig->has_port())
    {
        lIwfSigtranSctpEndPointConfig.set_ipaddress(pIwfSigtranSctpEndPointConfig->ipaddress());
        lIwfSigtranSctpEndPointConfig.set_port(pIwfSigtranSctpEndPointConfig->port());
    }
    
    DLOG_DEBUG("pIwfSigtranSctpEndPointConfig = %s",pIwfSigtranSctpEndPointConfig->DebugString().c_str());

#if 0
    if(pIwfSigtranSctpEndPointConfig->has_ipaddress())
        lIwfSigtranSctpEndPointConfig.set_ipaddress(pIwfSigtranSctpEndPointConfig->ipaddress());
    if(pIwfSigtranSctpEndPointConfig->has_port())
        lIwfSigtranSctpEndPointConfig.set_port(pIwfSigtranSctpEndPointConfig->port());
#endif
    pRes = NULL;
    if(pIwfSigtranSctpEndPointConfig->has_port() || pIwfSigtranSctpEndPointConfig->has_ipaddress())
    {
        sql_IWFSctpEndpoint_Create_Select_Query(&lIwfSigtranSctpEndPointConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        DLOG_NONE("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(pIwfSigtranSctpEndPointConfig->endpointname() == pRes->getString("ENDPOINT_NAME"))
                {
                    iReturn = IWF_DB_SUCCESS;
                }
                else
                {
                    delete pRes;
                    DLOG_ERROR("Record Present with same ip and port");   
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_SCTPENDPOINT_ERR_IP_PORT_ALREADY_PRESENT;
                }
            }
        }
        delete pRes;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranSctpEndPoints_Mod_Config_Reqs(IwfSigtranSctpEndPointsConfig *pIwfSigtranSctpEndPointsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    int iSendFlag = -1;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranSctpEndPointsConfig->sctpendpointinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(MOD_SCTPENDPOINT_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[MOD_SCTPENDPOINT_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranSctpEndPointsConfig->mutable_sctpendpointinfo(i);
        
        if((iReturn = mysql_IWFSctpEndPoint_Mod_Validation(pIwfSigtranSctpEndPointConfig,resp)) != IWF_DB_SUCCESS)
        {
            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;

            mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
#if 0
        iReturn = mysql_IWFSctpEndPoint_Check_Association_isEnabled(pIwfSigtranSctpEndPointConfig,resp);
        if(iReturn == IWF_DB_SUCCESS)
            iSendFlag = 0;
        else if(iReturn == IWF_DB_SUCCESS_SEND)
        {
            if(iSendFlag == -1)
                iSendFlag = 1;
        }
        else
        {
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
#endif
        if(pIwfSigtranSctpEndPointConfig->has_ipaddress() || pIwfSigtranSctpEndPointConfig->has_port())
        {
            if(iReturn == IWF_DB_SUCCESS)
            {
                sql_IWFSctpEndpoint_Create_Mod_Query(pIwfSigtranSctpEndPointConfig,sStatement);
            }

            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;

                mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
        
        int iMutihomingCount = pIwfSigtranSctpEndPointConfig->multihominginfo_size();
        for(int j=0;j<iMutihomingCount;j++)
        {
            if((iReturn = mysql_IwfSigtranMultihoming_Validation(pIwfSigtranSctpEndPointConfig,resp,j)) != IWF_DB_SUCCESS)
            {
                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;
                else if(iReturn == GENERIC_ERR_DB_ERROR)
                    iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;
                else if(iReturn == GENERIC_SCTPENDPOINT_ERR_MULTIHOMING_IP_MAXCOUNT)
                    iReturn = MOD_SCTPENDPOINT_ERR_MAX_MULTIHOMING_IP;
                else if(iReturn == GENERIC_SCTPENDPOINT_ERR_MULTIHOMING_IP_SAMEAS_PRIMARY_IP)
                    iReturn = MOD_SCTPENDPOINT_ERR_MULTIHOMING_IP_SAMEAS_PRIMARY_IP;

                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn,j);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            sql_IWFSigtranMultihoming_Create_Check_Modifcation_Query(pIwfSigtranSctpEndPointConfig,sStatement,j);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;

                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn,j);

                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                sql_IWFSigtranMultihoming_Create_Add_Query(pIwfSigtranSctpEndPointConfig,sStatement,j);
            }
            else // MOD
            {
                delete pRes;
                DLOG_ERROR("Record Already Present");   
                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,MOD_SCTPENDPOINT_ERR_MULTIHOMING_IP_ALREADY_PRESENT,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return MOD_SCTPENDPOINT_ERR_MULTIHOMING_IP_ALREADY_PRESENT;
            }

            delete pRes;
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;

                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn,j);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

        }
#if 0
        IwfSigtranAssociationConfig lIwfSigtranAssociationConfigObj;
        IwfSigtranSctpEndPointConfig *plocalIwfSigtranSctpEndPointConfig = lIwfSigtranAssociationConfigObj.mutable_localendpoint();

        plocalIwfSigtranSctpEndPointConfig->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSigtranAssocAndAssocSet_Create_Select_Query(&lIwfSigtranAssociationConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_SCTPENDPOINT_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        DLOG_NONE("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            pRes = NULL;
            IwfSigtranSctpEndPointConfig pLocalIwfSigtranSctpEndPointConfig;
            if(pIwfSigtranSctpEndPointConfig->has_endpointname())
            {
                pLocalIwfSigtranSctpEndPointConfig.set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());
                if((iReturn = Validate_IWFLocalSctpEndpoint(&pLocalIwfSigtranSctpEndPointConfig,resp)) != IWF_DB_SUCCESS)
                {
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    if(iReturn == ADD_ASSOCIATION_ERR_FAILED_INVALID_LOCAL_ENDPOINT_IP)
                        iReturn = MOD_SCTPENDPOINT_ERR_FAILED_INVALID_LOCAL_ENDPOINT_IP;
                    mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);
                    return iReturn;
                }
            }
        }
        else
        {
            delete pRes;
            pRes = NULL;
        }
#endif
    }

    if(iSendFlag == 1)
        iReturn = IWF_DB_SUCCESS_SEND;

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFCheck_InMultiHoming(string sEndPointName)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    IwfSigtranSctpEndPointConfig lIwfSigtranSctpEndPointConfigObj;
    lIwfSigtranSctpEndPointConfigObj.set_endpointname(sEndPointName);

    sql_IWFSigtranMultihoming_Create_Select_Query(&lIwfSigtranSctpEndPointConfigObj,sStatement,-1);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = GENERIC_ERR_DB_ERROR;


        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GENERIC_ERR_USED_IN_SCTPENDPOINT_IN_MULTIHOMING_IP;
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

DbStatus_e CMgrIwfDbInterface::mysql_IWFCheck_InAssociation(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);


    sql_IWFSigtranAssociation_Create_Select_Query(pIwfSigtranAssociationConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = GENERIC_ERR_DB_ERROR;


        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    try
    {
        DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GENERIC_ERR_USED_IN_ASSOCIATION;
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

DbStatus_e CMgrIwfDbInterface::mysql_IWFSctpEndPoint_Del_Validation(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp)
{
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    {
        IwfSigtranAssociationConfig lIwfSigtranAssociationConfigObj;
        IwfSigtranSctpEndPointConfig *pLocalpIwfSigtranSctpEndPointConfigReq = lIwfSigtranAssociationConfigObj.mutable_localendpoint();
        pLocalpIwfSigtranSctpEndPointConfigReq->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());
        if((iReturn = mysql_IWFCheck_InAssociation(&lIwfSigtranAssociationConfigObj)) != IWF_DB_SUCCESS)
        {
            if(iReturn == GENERIC_ERR_DB_ERROR)
                iReturn = DEL_SCTPENDPOINT_ERR_DB_ERROR;
            else if (iReturn == GENERIC_ERR_USED_IN_ASSOCIATION)
            {
                DLOG_ERROR("EndPoint is used in a Association");   
                iReturn = DEL_SCTPENDPOINT_ERR_USED_IN_ASSOCIATION;
            }
            else if (iReturn == GENERIC_ERR_USED_IN_ASSOCIATION_IN_MULTIHOMING_IP)
            {
                DLOG_ERROR("EndPoint is used in a Association and Association Used in Mutihoming ip");   
                iReturn = DEL_SCTPENDPOINT_ERR_USED_IN_ASSOCIATION_AND_ASSOCIATION_IN_MULTIHOMING_IP;
            }

            mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        
    }

    {
        IwfSigtranAssociationConfig lIwfSigtranAssociationConfigObj;
        IwfSigtranSctpEndPointConfig *pLocalpIwfSigtranSctpEndPointConfigReq = lIwfSigtranAssociationConfigObj.mutable_remoteendpoint();
        pLocalpIwfSigtranSctpEndPointConfigReq->set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());
        if((iReturn = mysql_IWFCheck_InAssociation(&lIwfSigtranAssociationConfigObj)) != IWF_DB_SUCCESS)
        {
            if(iReturn == GENERIC_ERR_DB_ERROR)
                iReturn = DEL_SCTPENDPOINT_ERR_DB_ERROR;
            else if (iReturn == GENERIC_ERR_USED_IN_ASSOCIATION)
            {
                DLOG_ERROR("EndPoint is used in a Association");   
                iReturn = DEL_SCTPENDPOINT_ERR_USED_IN_ASSOCIATION;
            }

            mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        
    }

    if((iReturn = mysql_IWFCheck_InMultiHoming(pIwfSigtranSctpEndPointConfig->endpointname())) != IWF_DB_SUCCESS)
    {
        if(iReturn == GENERIC_ERR_DB_ERROR)
            iReturn = DEL_SCTPENDPOINT_ERR_DB_ERROR;
        else if (iReturn == GENERIC_ERR_USED_IN_SCTPENDPOINT_IN_MULTIHOMING_IP)
        {
            DLOG_ERROR("EndPoint is used in a MultiHoming");
            iReturn = DEL_SCTPENDPOINT_ERR_USED_IN_MULTIHOMING_IP;
        }
        mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;

    }
        

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranSctpEndPoints_Del_Config_Reqs(IwfSigtranSctpEndPointsConfig *pIwfSigtranSctpEndPointsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranSctpEndPointsConfig->sctpendpointinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(DEL_SCTPENDPOINT_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_SCTPENDPOINT_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranSctpEndPointsConfig->mutable_sctpendpointinfo(i);

        if((iReturn = mysql_IWFSctpEndPoint_Del_Validation(pIwfSigtranSctpEndPointConfig,resp)) != IWF_DB_SUCCESS)
        {
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        sql_IWFSctpEndpoint_Create_Check_Modifcation_Query(pIwfSigtranSctpEndPointConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_SCTPENDPOINT_ERR_DB_ERROR;

            mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record NOT Present:DEL_SCTPENDPOINT_ERR_NOT_PRESENT!!");   
            mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,DEL_SCTPENDPOINT_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_SCTPENDPOINT_ERR_NOT_PRESENT;
        }
        else // MOD
        {
            sql_IWFSctpEndpoint_Create_Delete_Query(pIwfSigtranSctpEndPointConfig,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_SCTPENDPOINT_ERR_DB_ERROR;

            mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IWFSctpProfile_Del_Validation(IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig,IWFCfgResp *resp)
{
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    {
        if(!strcmp(pIwfSigtranSctpProfileConfig->sctpprofilename().c_str(), "default_sctp"))
        {
            DLOG_ERROR("Default SCTP Profile is not allowed to delete");
            return DEL_SCTPPROFILE_ERR_DEFAULT_PROFILE_NOT_ALLOWED;
        }
        IwfSigtranAssociationConfig lIwfSigtranAssociationConfigObj;
        IwfSigtranSctpProfileConfig *pLocalpIwfSigtranSctpProfileConfigReq = lIwfSigtranAssociationConfigObj.mutable_sctpprofile();
        pLocalpIwfSigtranSctpProfileConfigReq->set_sctpprofilename(pIwfSigtranSctpProfileConfig->sctpprofilename());
        if((iReturn = mysql_IWFCheck_InAssociation(&lIwfSigtranAssociationConfigObj)) != IWF_DB_SUCCESS)
        {
            if(iReturn == GENERIC_ERR_DB_ERROR)
                iReturn = DEL_SCTPENDPOINT_ERR_DB_ERROR;
            else if (iReturn == GENERIC_ERR_USED_IN_ASSOCIATION)
            {
                DLOG_ERROR("EndPoint is used in a Association");   
                iReturn = DEL_SCTPPROFILE_ERR_USED_IN_ASSOCIATION;
            }
            else if (iReturn == GENERIC_ERR_USED_IN_ASSOCIATION_IN_MULTIHOMING_IP)
            {
                DLOG_ERROR("EndPoint is used in a Association and Association Used in Mutihoming ip");   
                iReturn = DEL_SCTPPROFILE_ERR_USED_IN_ASSOCIATION_AND_ASSOCIATION_IN_MUTIHOMING_IP;
            }

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranSctpProfiles_Del_Config_Reqs(IwfSigtranSctpProfilesConfig *pIwfSigtranSctpProfilesConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranSctpProfilesConfig->sctpprofileinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(DEL_SCTPPROFILE_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_SCTPPROFILE_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = pIwfSigtranSctpProfilesConfig->mutable_sctpprofileinfo(i);

        if((iReturn = mysql_IWFSctpProfile_Del_Validation(pIwfSigtranSctpProfileConfig,resp)) != IWF_DB_SUCCESS)
        {
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(pIwfSigtranSctpProfileConfig,resp,iReturn);
            return iReturn;
        }

        sql_IWFSigtranSCTPProfile_Create_Check_Modifcation_Query(pIwfSigtranSctpProfileConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_SCTPPROFILE_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(pIwfSigtranSctpProfileConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record NOT Present:DEL_SCTPPROFILE_ERR_NOT_PRESENT!");   
            mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(pIwfSigtranSctpProfileConfig,resp,DEL_SCTPPROFILE_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_SCTPPROFILE_ERR_NOT_PRESENT;
        }
        else // MOD
        {
            sql_IWFSigtranSCTPProfile_Create_Delete_Query(pIwfSigtranSctpProfileConfig,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_SCTPPROFILE_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(pIwfSigtranSctpProfileConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociationSet_Del_Validation(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig, IWFCfgResp *resp)
{

    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

#if 0
    if((iReturn = mysql_IwfSigtranAssociationSet_Validation(pIwfSigtranAssociationSetConfig,resp)) != IWF_DB_SUCCESS)
    {
        if(iReturn == IWF_DB_FAIL)
            iReturn = DEL_ASSOCIATIONSET_ERR_DB_ERROR;
        else if(iReturn == GENERIC_ERR_DB_ERROR)
            iReturn = DEL_ASSOCIATIONSET_ERR_DB_ERROR;
        else if(iReturn == GENERIC_ERR_ASSOCIATIONSET_IN_ACTIVE_STATE)
            iReturn = DEL_ASSOCIATIONSET_ERR_ASSOCIATIONSET_IN_ACTIVE_STATE;
        
        return iReturn;
    }
#endif
    sql_IWFSigtranAssocSetMapping_Create_Select_Query(pIwfSigtranAssociationSetConfig,sStatement,-1);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = DEL_ASSOCIATIONSET_ERR_DB_ERROR;


        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() > 0)
    {
        delete pRes;
        DLOG_ERROR("Association is in Enabled state");   
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DEL_ASSOCIATIONSET_ERR_IS_ASSOCIATED;
    }
    delete pRes;

    IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfigObj;
    LocalIwfSigtranRemoteRouteConfigObj.set_associationsetname(pIwfSigtranAssociationSetConfig->associationsetname());

    sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfigObj,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = DEL_ASSOCIATIONSET_ERR_DB_ERROR;


        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() > 0)
    {
        delete pRes;
        DLOG_ERROR("Association is in Enabled state");   
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DEL_ASSOCIATIONSET_ERR_USED_IN_ROUTE;
    }
    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociationSets_Del_Config_Reqs(IwfSigtranAssociationSetsConfig *pIwfSigtranAssociationSetsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranAssociationSetsConfig->associationsetinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(DEL_ASSOCIATIONSET_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_ASSOCIATIONSET_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig = pIwfSigtranAssociationSetsConfig->mutable_associationsetinfo(i);

        if((iReturn = mysql_IwfSigtranAssociationSet_Del_Validation(pIwfSigtranAssociationSetConfig,resp)) != IWF_DB_SUCCESS)
        {
            mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        sql_IWFSigtranAssocSet_Create_Check_Modifcation_Query(pIwfSigtranAssociationSetConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_ASSOCIATIONSET_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Not Present:DEL_ASSOCIATIONSET_ERR_NO_PRESENT!");   
            mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,DEL_ASSOCIATIONSET_ERR_NO_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_ASSOCIATIONSET_ERR_NO_PRESENT;

        }
        else // MOD
        {
            IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;
            LocalIwfSigtranAssociationSetConfigObj.set_associationsetname(pIwfSigtranAssociationSetConfig->associationsetname());
            Fill_IWFSigtranAssocSet_protobuff(&LocalIwfSigtranAssociationSetConfigObj,resp);
            pIwfSigtranAssociationSetConfig->CopyFrom(LocalIwfSigtranAssociationSetConfigObj);

            sql_IWFSigtranAssocSet_Create_Delete_Query(pIwfSigtranAssociationSetConfig,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_ASSOCIATIONSET_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranMultihoming_Validation(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig, IWFCfgResp *resp,int iIndex)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    IwfSigtranSctpEndPointConfig localIwfSigtranSctpEndPointConfig;
    localIwfSigtranSctpEndPointConfig.set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());
    sql_IWFSigtranMultihoming_Create_Select_Query(&localIwfSigtranSctpEndPointConfig,sStatement,-1);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = GENERIC_ERR_DB_ERROR;


        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() >= MAX_MULTIHOMING_IP)
    {
        delete pRes;
        DLOG_ERROR("Max Multihoming ip's already present");   
        DLOG_NONE(" < %s ",__FUNCTION__);
        return GENERIC_SCTPENDPOINT_ERR_MULTIHOMING_IP_MAXCOUNT;
    }
    delete pRes;
   
    sql_IWFSctpEndpoint_Create_Select_Query(&localIwfSigtranSctpEndPointConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = GENERIC_ERR_DB_ERROR;


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
                IwfSigtranMultihomingConfig *pLocalIwfSigtranMultihomingConfig = pIwfSigtranSctpEndPointConfig->mutable_multihominginfo(iIndex);

                if(!pRes->isNull("IP_ADDRESS"))
                {
                    if(pRes->getString("IP_ADDRESS") == pLocalIwfSigtranMultihomingConfig->otheripaddress().c_str())
                    {
                        delete pRes;
                        DLOG_ERROR("Multihoming ip is same as PrimaryIp");   
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return GENERIC_SCTPENDPOINT_ERR_MULTIHOMING_IP_SAMEAS_PRIMARY_IP;
                    }
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

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociation_Add_Validation(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig, IWFCfgResp *resp)
{

    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    {
        sql_IWFSigtranAssociation_Create_Check_Modifcation_Query(pIwfSigtranAssociationConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present:ADD_ASSOCIATION_ERR_ALREADY_PRESENT!!");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ASSOCIATION_ERR_ALREADY_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }

    if(pIwfSigtranAssociationConfig -> has_localendpoint() && pIwfSigtranAssociationConfig -> has_remoteendpoint())
    {
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig =  NULL;
        pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig -> mutable_localendpoint();

        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig2 =  NULL;
        pLocalIwfSigtranSctpEndPointConfig2 = pIwfSigtranAssociationConfig -> mutable_remoteendpoint();
        if(pLocalIwfSigtranSctpEndPointConfig -> endpointname() == pLocalIwfSigtranSctpEndPointConfig2 -> endpointname())
            return ADD_ASSOCIATION_ERR_SCTP_END_POINTS_ARE_SAME_IN_ASSOCIATION;
    }

    if(pIwfSigtranAssociationConfig->has_sctpprofile())
    {
        IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = pIwfSigtranAssociationConfig->mutable_sctpprofile();

        IwfSigtranSctpProfileConfig LocalIwfSigtranSctpProfileConfigObj;
        LocalIwfSigtranSctpProfileConfigObj.set_sctpprofilename(pIwfSigtranSctpProfileConfig->sctpprofilename());

        sql_IWFSigtranSCTPProfile_Create_Select_Query(&LocalIwfSigtranSctpProfileConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Sctp Profile is not Present");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ASSOCIATION_ERR_SCTP_PROFILE_NOT_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }

    {
        IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;
        LocalIwfSigtranAssociationSetConfigObj.set_associationsetname(pIwfSigtranAssociationConfig->associationsetname());

        sql_IWFSigtranAssocSet_Create_Select_Query(&LocalIwfSigtranAssociationSetConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Association Set is not presert");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ASSOCIATION_ERR_ASSOCIATION_SET_NOT_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }

    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();
        IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
        LocalIwfSigtranSctpEndPointConfigObj.set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSctpEndpoint_Create_Select_Query(&LocalIwfSigtranSctpEndPointConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Remote end point is not presert");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ASSOCIATION_ERR_SCTP_END_POINT_NOT_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }

    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();
        IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
        LocalIwfSigtranSctpEndPointConfigObj.set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSctpEndpoint_Create_Select_Query(&LocalIwfSigtranSctpEndPointConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Local end point is not present");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ASSOCIATION_ERR_SCTP_END_POINT_NOT_PRESENT;
        }
        delete pRes;
        pRes = NULL;
    }
#if 0 
    {
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig -> mutable_localendpoint();
        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig2 = LocalIwfSigtranAssociationConfigObj.mutable_localendpoint();
        pLocalIwfSigtranSctpEndPointConfig2->set_endpointname(pLocalIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSigtranAssociation_Create_Select_Query(&LocalIwfSigtranAssociationConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
            
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            DLOG_ERROR("LocalEndPoint is already part of some other Association");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ASSOCIATION_ERR_LOCALENDPOINT_ALREADY_USED_IN_ASSOCIATION;
        }
        delete pRes;
        pRes = NULL;
    }
#endif 
    {
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig3 = pIwfSigtranAssociationConfig -> mutable_localendpoint();
        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj2;
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig4 = LocalIwfSigtranAssociationConfigObj2.mutable_remoteendpoint();
        pLocalIwfSigtranSctpEndPointConfig4->set_endpointname(pLocalIwfSigtranSctpEndPointConfig3->endpointname());

        sql_IWFSigtranAssociation_Create_Select_Query(&LocalIwfSigtranAssociationConfigObj2,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {

                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            DLOG_ERROR("LocalEndPoint is already part of some other Association");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ASSOCIATION_ERR_LOCALENDPOINT_ALREADY_USED_IN_ASSOCIATION;
        }
        delete pRes;
        pRes = NULL;
#if 0
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig -> mutable_localendpoint();
        IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
        if(pLocalIwfSigtranSctpEndPointConfig->has_endpointname())
        {
            LocalIwfSigtranSctpEndPointConfigObj.set_endpointname(pLocalIwfSigtranSctpEndPointConfig->endpointname());
            if((iReturn = Validate_IWFLocalSctpEndpoint(&LocalIwfSigtranSctpEndPointConfigObj,resp)) != IWF_DB_SUCCESS)
            {
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
#endif
    }   

    {
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig3 = pIwfSigtranAssociationConfig -> mutable_remoteendpoint();
        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj2;
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig4 = LocalIwfSigtranAssociationConfigObj2.mutable_localendpoint();
        pLocalIwfSigtranSctpEndPointConfig4->set_endpointname(pLocalIwfSigtranSctpEndPointConfig3->endpointname());

        sql_IWFSigtranAssociation_Create_Select_Query(&LocalIwfSigtranAssociationConfigObj2,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {

                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            DLOG_ERROR("RemoteEndPoint is already part of some other Association");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ASSOCIATION_ERR_REMOTEENDPOINT_ALREADY_USED_IN_ASSOCIATION;
        }
        delete pRes;
        pRes = NULL;
    }   
    {
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig -> mutable_remoteendpoint();
        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig2 = LocalIwfSigtranAssociationConfigObj.mutable_remoteendpoint();
        pLocalIwfSigtranSctpEndPointConfig2->set_endpointname(pLocalIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSigtranAssociation_Create_Select_Query(&LocalIwfSigtranAssociationConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {

                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        DLOG_NONE("pRes->rowsCount() = %d",pRes->rowsCount());
        if(pRes->rowsCount() > 0)
        {
            while(pRes->next())
            {
                if(pIwfSigtranAssociationConfig->has_aspid() && (pRes->getInt("ASP_ID") == (int)pIwfSigtranAssociationConfig->aspid()))
                {
                    delete pRes;
                    DLOG_ERROR("RemoteEndPoint is already part of some other Association for same node with same AspId");
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return ADD_ASSOCIATION_ERR_REMOTEENDPOINT_ALREADY_USED_IN_ASSOCIATION;
                }
            }

        }
        delete pRes;
        pRes = NULL;
    }
    if(pIwfSigtranAssociationConfig->has_aspid())
    {
        pRes = NULL;
        sql_IWFLocalConfig_Create_Check_AspId_Modifcation_Query(pIwfSigtranAssociationConfig->aspid(),sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() <= 0)
        {
            delete pRes;
            DLOG_ERROR("AspId is not same as configured for LocalHost AspId's");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ASSOCIATION_ERR_ASP_ID_NOT_PRESENT;
        }
        delete pRes;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::Validate_IWFLocalSctpEndpoint(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp)
{
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
    LocalIwfSigtranSctpEndPointConfigObj.CopyFrom(*pIwfSigtranSctpEndPointConfig);
    Fill_IWFSctpEndpoint_protobuff(&LocalIwfSigtranSctpEndPointConfigObj,resp);
    std::vector<std::string> localIp;

    if(LocalIwfSigtranSctpEndPointConfigObj.has_ipaddress() && LocalIwfSigtranSctpEndPointConfigObj.has_port())
    {
        int port = LocalIwfSigtranSctpEndPointConfigObj.port();
        localIp.push_back(LocalIwfSigtranSctpEndPointConfigObj.ipaddress());
        if(LocalIwfSigtranSctpEndPointConfigObj.multihominginfo_size() > 0)
        {
            for(int numExtrahomes = 0; numExtrahomes < LocalIwfSigtranSctpEndPointConfigObj.multihominginfo_size() ; numExtrahomes++)
            {
                IwfSigtranMultihomingConfig multiHomingInfo = LocalIwfSigtranSctpEndPointConfigObj.multihominginfo(numExtrahomes);
                if(multiHomingInfo.has_otheripaddress())
                {    
                    localIp.push_back(multiHomingInfo.otheripaddress());
                }
            }
        }
        if ((iReturn = ValidateLocalHostIP(localIp,port)) != IWF_DB_SUCCESS)
        {    
            DLOG_ERROR("Validation of LocalHost IP(s) configured failed, unable to add Asscociation");
            iReturn = ADD_ASSOCIATION_ERR_FAILED_INVALID_LOCAL_ENDPOINT_IP;
            return iReturn;
        }
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::ValidateLocalHostIP(std::vector<string>& ipAddress, int port, bool isIPv6)
{
    int sockFd;
    DbStatus_e retVal = IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if((sockFd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP)) < 0)
    {
        DLOG_ERROR("Unable to create Socket");
        retVal = !IWF_DB_SUCCESS;
    }
    else
    {
        if( isIPv6 )
        {
            struct sockaddr_in6 lSocket[MAX_IP_ADDRS];
            memset(lSocket, 0, sizeof(sockaddr_in)*MAX_IP_ADDRS);
            for( unsigned int currIp = 0 ; currIp < ipAddress.size(); currIp++ )
            {
                lSocket[currIp].sin6_family = AF_INET;
                lSocket[currIp].sin6_port = htonl(port);
                DLOG_DEBUG("IPv6 ip %s ",ipAddress[currIp].c_str());
                DLOG_DEBUG("Port %d ",port);
                if ( inet_pton(AF_INET6, ipAddress[currIp].c_str(),
                            &(lSocket[currIp].sin6_addr)) == 0 )
                {
                    DLOG_ERROR("Convertion to IPv6 address failed ");
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return !IWF_DB_SUCCESS;
                }
            }
            if (sctp_bindx(sockFd, (sockaddr *)lSocket,
                        ipAddress.size(), SCTP_BINDX_ADD_ADDR) < 0)
            {
                DLOG_ERROR("local host Ip bind failed .errno = %d.",errno);
                retVal = !IWF_DB_SUCCESS;
            }
            else
            {
                DLOG_DEBUG("Validation of local host ip successful");
                close(sockFd);
            }
        }
        else
        {
            struct sockaddr_in lSocket[MAX_IP_ADDRS];
            memset(lSocket, 0, sizeof(sockaddr_in)*MAX_IP_ADDRS);
            for( unsigned int currIp = 0 ; currIp < ipAddress.size(); currIp++ )
            {
                lSocket[currIp].sin_family = AF_INET;
                lSocket[currIp].sin_port = htonl(port);
                DLOG_DEBUG("IPv4 ip %s ",ipAddress[currIp].c_str());
                DLOG_DEBUG("Port %d ",port);
                lSocket[currIp].sin_addr.s_addr = inet_addr(ipAddress[currIp].c_str());
            }
            if (sctp_bindx(sockFd, (sockaddr *)lSocket,
                        ipAddress.size(), SCTP_BINDX_ADD_ADDR) < 0)
            {
                DLOG_ERROR("local host Ip bind failed.errno = %d.",errno);
                retVal = !IWF_DB_SUCCESS;
            }
            else
            {
                DLOG_DEBUG("Validation of local host ip successful");
                close(sockFd);
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return retVal;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociation_Del_Validation(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    //NOTE: To validate AssociationSet part of RemoteRout and having more than 1 Associations
        //1) Get the associationSet linked to association
        //2) Find whether it is part of Route
        //3) If linked to Route find number of associations linked to associationset, if morethan 1 then allow to delete

    IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;

    LocalIwfSigtranAssociationConfigObj.set_associationname(pIwfSigtranAssociationConfig->associationname());
    
    sql_IWFSigtranRemoteRoute_Create_Select_Query_For_Delete_Association_Validation(&LocalIwfSigtranAssociationConfigObj, sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = DEL_ASSOCIATION_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() > 0) // AssociationSet part of RemoteRoute
    {
        delete pRes;
        sql_IWFSigtranAssocSetMapping_Create_Select_Query_For_Delete_Association_Validation(&LocalIwfSigtranAssociationConfigObj, sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_ASSOCIATION_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() <= 1) // AssociationSet is associated to lessthan or equal to one association
        {
            delete pRes;
            DLOG_ERROR("AssociationSet is linked to only one Association");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_ASSOCIATION_ERR_ASSOCIATED_TO_ASSOCIATION_SET_PART_OF_ROUTE;
        }
    }
    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtransMultihoming_Del_Validation(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,int iIndex)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE("iIndex = %d ",iIndex);

    {
        IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
        LocalIwfSigtranSctpEndPointConfigObj.set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSctpEndpoint_Create_Check_Modifcation_Query(&LocalIwfSigtranSctpEndPointConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_MULTIHOMINGIP_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Record not Present:DEL_MULTIHOMINGIP_ERR_ENDPOINT_NOT_PRESENT!");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_MULTIHOMINGIP_ERR_ENDPOINT_NOT_PRESENT;
        }
        delete pRes;
    }

    {
        pRes = NULL;
        IwfSigtranMultihomingConfig *pLocalIwfSigtranMultihomingConfig = pIwfSigtranSctpEndPointConfig -> mutable_multihominginfo(iIndex);
        IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
        IwfSigtranMultihomingConfig *pLocalIwfSigtranMultihomingConfigSecond = LocalIwfSigtranSctpEndPointConfigObj.add_multihominginfo();
        pLocalIwfSigtranMultihomingConfigSecond -> set_otheripaddress(pLocalIwfSigtranMultihomingConfig->otheripaddress());
        LocalIwfSigtranSctpEndPointConfigObj.set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSigtranMultihoming_Create_Select_Query(&LocalIwfSigtranSctpEndPointConfigObj,sStatement,0);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_MULTIHOMINGIP_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) 
        {
            delete pRes;
            DLOG_ERROR("Record Present:DEL_MULTIHOMINGIP_ERR_NOT_PRESENT!");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_MULTIHOMINGIP_ERR_NOT_PRESENT;
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtransMultihoming_Del_Config_Reqs(IwfSigtranSctpEndPointsConfig *pIwfSigtranSctpEndPointsConfig,IWFCfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iendpointCount = pIwfSigtranSctpEndPointsConfig->sctpendpointinfo_size();
    if(iendpointCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(DEL_MULTIHOMINGIP_ERR_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_MULTIHOMINGIP_ERR_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iendpointCount;i++)
    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranSctpEndPointsConfig->mutable_sctpendpointinfo(i);

        int iCount = pIwfSigtranSctpEndPointConfig->multihominginfo_size();
        DLOG_NONE("iCount =%d ",iCount);
        if(iCount == 0)
        {
            ErrorDetails* err = resp->add_errordetails();
            err->set_errorcode(DEL_MULTIHOMINGIP_ERR_NOT_SET);
            err->set_errormsgkey(iwfErrorMap[DEL_MULTIHOMINGIP_ERR_NOT_SET]);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return IWF_DB_FAIL;
        }

        for(int i=0;i<iCount;i++)
        {
            IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = pIwfSigtranSctpEndPointConfig->mutable_multihominginfo(i);

            if((iReturn = mysql_IwfSigtransMultihoming_Del_Validation(pIwfSigtranSctpEndPointConfig,i)) != IWF_DB_SUCCESS)
            {
                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_MULTIHOMINGIP_ERR_DB_ERROR;

                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranMultihomingConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if(iReturn == IWF_DB_SUCCESS)
            {
                sql_IWFSigtranMultihoming_Create_Delete_Query(pIwfSigtranSctpEndPointConfig,sStatement,i);
            }

            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_MULTIHOMINGIP_ERR_DB_ERROR;

                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranMultihomingConfig,resp,iReturn);
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
#if 0
DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtransMultihoming_Del_Config_Reqs(IwfSigtransMultihomingConfig *pIwfSigtransMultihomingConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtransMultihomingConfig->multihominginfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(DEL_MULTIHOMINGIP_ERR_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_MULTIHOMINGIP_ERR_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig = pIwfSigtransMultihomingConfig->mutable_multihominginfo(i);

        if((iReturn = mysql_IwfSigtransMultihoming_Del_Validation(pIwfSigtranMultihomingConfig)) != IWF_DB_SUCCESS)
        {
            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_ASSOCIATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranMultihomingConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        sql_IWFSigtranMultihoming_Create_Select_Query(pIwfSigtranMultihomingConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_ASSOCIATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranMultihomingConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Not Present:DEL_ASSOCIATION_ERR_NOT_PRESENT!");   
            mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranMultihomingConfig,resp,DEL_ASSOCIATION_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_ASSOCIATION_ERR_NOT_PRESENT;
        }
        else // MOD
        {
            sql_IWFSigtranMultihoming_Create_Delete_Query(pIwfSigtranMultihomingConfig,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_ASSOCIATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranMultihomingConfig,resp,iReturn);
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

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociations_Del_Config_Reqs(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    int iSendFlag = -1;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranAssociationsConfig->associationinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(DEL_ASSOCIATION_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_ASSOCIATION_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = pIwfSigtranAssociationsConfig->mutable_associationinfo(i);

        iReturn = mysql_IWFSigtranAssociation_Check_Association_isEnabled(pIwfSigtranAssociationConfig,resp);
        if(iReturn == IWF_DB_SUCCESS)
        {
            iSendFlag = 0;
            DLOG_DEBUG("iReturn from mysql_IWFSigtranAssociation_Check_Association_isEnabled = %d",iReturn);
        }
        else if(iReturn == IWF_DB_SUCCESS_SEND)
        {
            iReturn = IWF_DB_SUCCESS;
            if(iSendFlag == -1)
                iSendFlag = 1;
            DLOG_DEBUG("iReturn from mysql_IWFSigtranAssociation_Check_Association_isEnabled = %d",iReturn);
        }
        else
        {
            DLOG_DEBUG("iReturn from mysql_IWFSigtranAssociation_Check_Association_isEnabled = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_IwfSigtranSetMapping_Del_Config(pIwfSigtranAssociationConfig, true)) != IWF_DB_SUCCESS)
        {
                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_ASSOCIATION_ERR_DB_ERROR;
                DLOG_DEBUG("iReturn = %d",iReturn);
                mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
        }

        sql_IWFSigtranAssociation_Create_Check_Modifcation_Query(pIwfSigtranAssociationConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_ASSOCIATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Not Present:DEL_ASSOCIATION_ERR_NOT_PRESENT!!");   
            mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,DEL_ASSOCIATION_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_ASSOCIATION_ERR_NOT_PRESENT;
        }
        else // MOD
        {
            sql_IWFSigtranAssociation_Create_Delete_Query(pIwfSigtranAssociationConfig,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_ASSOCIATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociations_Mod_Config_Reqs(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IWFCfgResp *resp)
{
    //sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    int iSendFlag = -1;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranAssociationsConfig->associationinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(MOD_ASSOCIATION_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[MOD_ASSOCIATION_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = pIwfSigtranAssociationsConfig->mutable_associationinfo(i);

        if((iReturn = mysql_IwfSigtranAssociation_Mod_Validation(pIwfSigtranAssociationConfig)) != IWF_DB_SUCCESS)
        {

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        iReturn = mysql_IWFSigtranAssociation_Check_Association_isEnabled(pIwfSigtranAssociationConfig,resp);
        if(iReturn == IWF_DB_SUCCESS)
        {
            DLOG_DEBUG("iReturn from mysql_IWFSigtranAssociation_Check_Association_isEnabled = %d",iReturn);
            iSendFlag = 0;
        }
        else if(iReturn == IWF_DB_SUCCESS_SEND)
        {
            iReturn = IWF_DB_SUCCESS;
            DLOG_DEBUG("iReturn from mysql_IWFSigtranAssociation_Check_Association_isEnabled = %d",iReturn);
        }
        else
        {
            DLOG_DEBUG("iReturn from mysql_IWFSigtranAssociation_Check_Association_isEnabled = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if(pIwfSigtranAssociationConfig->has_sctpprofile() ||
                pIwfSigtranAssociationConfig->has_localendpoint() ||
                pIwfSigtranAssociationConfig->has_aspid() ||
                pIwfSigtranAssociationConfig->has_remoteendpoint())
        {
            sql_IWFSigtranAssociation_Create_Mod_Query(pIwfSigtranAssociationConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;

                mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

        /*******************************************************************************/
        if(pIwfSigtranAssociationConfig->has_associationsetname())
        {
            if((iReturn = mysql_IwfSigtranSetMapping_Del_Config(pIwfSigtranAssociationConfig)) != IWF_DB_SUCCESS)
            {
                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            
            if((iReturn = mysql_IwfSigtranAssociations_get_Associationid(pIwfSigtranAssociationConfig)) != DRE_DB_SUCCESS)
            {   

                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;

                mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }   

            sql_IWFSigtranAssocSetMapping_Create_Add_Query(pIwfSigtranAssociationConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;

                mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

        /************************************************************************************************/

#if 0
        int iMutihomingCount = pIwfSigtranAssociationConfig->multihominginfo_size();
        for(int j=0;j<iMutihomingCount;j++)
        {
            if((iReturn = mysql_IwfSigtranMultihoming_Validation(pIwfSigtranAssociationConfig,resp,j)) != IWF_DB_SUCCESS)
            {
                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;
                else if(iReturn == GENERIC_ERR_DB_ERROR)
                    iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;
                else if(iReturn == GENERIC_ASSOCIATION_ERR_MULTIHOMING_IP_MAXCOUNT)
                    iReturn = MOD_ASSOCIATION_ERR_MAX_MULTIHOMING_IP;

                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn,j);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            sql_IWFSigtranMultihoming_Create_Check_Modifcation_Query(pIwfSigtranAssociationConfig,sStatement,j);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;

                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn,j);

                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                sql_IWFSigtranMultihoming_Create_Add_Query(pIwfSigtranAssociationConfig,sStatement,j);
            }
            else // MOD
            {
                delete pRes;
                DLOG_ERROR("Record Already Present");   
                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranAssociationConfig,resp,MOD_ASSOCIATION_ERR_MULTIHOMING_IP_ALREADY_PRESENT,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return MOD_ASSOCIATION_ERR_MULTIHOMING_IP_ALREADY_PRESENT;
            }

            delete pRes;
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;

                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn,j);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
#endif
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrIwfDbInterface::mysql_IWFSigtranAssociation_Check_Association_isEnabled(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    IwfSigtranAssociationConfig lIwfSigtranAssociationConfigObj;

    lIwfSigtranAssociationConfigObj.set_associationname(pIwfSigtranAssociationConfig->associationname());

    sql_IWFSigtranAssocAndAssocSet_Create_Select_Query(&lIwfSigtranAssociationConfigObj,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = MOD_SCTPPROFILE_ERR_DB_ERROR;

        mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    DLOG_NONE("pRes->rowsCount() = %d",pRes->rowsCount());
    if(pRes->rowsCount() > 0)
    {
        while(pRes->next())
        {
            if(pRes->getInt("ASSOCIATION_STATUS") == 0)
            {
                iReturn = IWF_DB_SUCCESS_SEND;
            }
            else
            {
                delete pRes;
                DLOG_ERROR("Association is in Active state");   
                mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,MOD_ASSOCIATION_ERR_ASSOCIATION_IN_ACTIVE_STATE);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return MOD_ASSOCIATION_ERR_ASSOCIATION_IN_ACTIVE_STATE;
            }
        }
    }
    else
    {
        delete pRes;
        return IWF_DB_SUCCESS;
    }
    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociation_set_Assoctionid(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
    LocalIwfSigtranAssociationConfigObj.set_associationname(pIwfSigtranAssociationConfig->associationname());

    sql_IWFSigtranAssocSetMapping_Create_Select_Query(&LocalIwfSigtranAssociationConfigObj,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() > 0) // ADD
    {
        if(pRes->next())
        {
            if(pRes->isNull("IWF_SIGTRAN_ASSOC_SET_ID"))
            {
                pIwfSigtranAssociationConfig->set_oldassociationsetid(pRes->getInt("IWF_SIGTRAN_ASSOC_SET_ID"));
            }
        }
    }
    delete pRes;


    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranSetMapping_Del_Config(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig, bool isDeleteAssociation)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    sql_IWFSigtranAssocSetMapping_Create_Check_Modifcation_Query(pIwfSigtranAssociationConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;


        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() > 0) // ADD
    {
        if(isDeleteAssociation)
        {
            //NOTE: Validation only if operation is delete Association
            if((iReturn = mysql_IwfSigtranAssociation_Del_Validation(pIwfSigtranAssociationConfig)) != IWF_DB_SUCCESS)
            {
                if(iReturn == IWF_DB_FAIL)
                    iReturn = DEL_ASSOCIATION_ERR_DB_ERROR;
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
        sql_IWFSigtranAssocSetMapping_Create_Delete_Query(pIwfSigtranAssociationConfig,sStatement); 
    }
    else
    {
        DLOG_WARNING("Its look like Association is not mapped in Association set");
        delete pRes;
        return IWF_DB_SUCCESS;
    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);
        if(iReturn == IWF_DB_FAIL)
            iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;

        DLOG_DEBUG("iReturn = %d",iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociation_Mod_Validation(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pIwfSigtranAssociationConfig -> has_localendpoint() && pIwfSigtranAssociationConfig -> has_remoteendpoint())
    {
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig =  NULL;
        pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig -> mutable_localendpoint();

        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig2 =  NULL;
        pLocalIwfSigtranSctpEndPointConfig2 = pIwfSigtranAssociationConfig -> mutable_remoteendpoint();
        if(pLocalIwfSigtranSctpEndPointConfig -> endpointname() == pLocalIwfSigtranSctpEndPointConfig2 -> endpointname())
            return MOD_ASSOCIATION_ERR_SCTP_END_POINTS_ARE_SAME_IN_ASSOCIATION;

    }
    else if(pIwfSigtranAssociationConfig -> has_localendpoint())
    {
        DLOG_DEBUG("Inside for checking");
        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
        LocalIwfSigtranAssociationConfigObj.set_associationname(pIwfSigtranAssociationConfig->associationname());

        sql_IWFSigtranAssociation_Create_Select_Query(&LocalIwfSigtranAssociationConfigObj,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        DLOG_DEBUG("pRes->rowsCount=%d",pRes->rowsCount());
        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("IWF_REMOTE_SCTP_ENDPOINT_ID"))
                {
                    sql::ResultSet *pLocalRes = NULL;
                    IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
                    LocalIwfSigtranSctpEndPointConfigObj.set_sctpendpointid(pRes->getInt("IWF_REMOTE_SCTP_ENDPOINT_ID"));

                    sql_IWFSctpEndpoint_Create_Select_Query(&LocalIwfSigtranSctpEndPointConfigObj,sStatement);

                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pLocalRes)) != IWF_DB_SUCCESS)
                    {
                        if(pLocalRes != NULL)    
                        {
                            delete pLocalRes;
                        }
                        DLOG_ERROR("Query Execution Failed %s",sStatement);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;


                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }

                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                    DLOG_DEBUG("pLocalRes->rowsCount=%d",pLocalRes->rowsCount());
                    if(pLocalRes->rowsCount() > 0)
                    {
                        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();
                        if(pLocalRes->next())
                        {
                            DLOG_DEBUG("comparison %s == %s",pLocalRes->getString("ENDPOINT_NAME").c_str(),pLocalIwfSigtranSctpEndPointConfig->endpointname().c_str());
                            if(pLocalRes->getString("ENDPOINT_NAME") == pLocalIwfSigtranSctpEndPointConfig->endpointname())
                            {
                                delete pLocalRes;
                                DLOG_ERROR("Both sctpEndPoints are same!!!");   
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return MOD_ASSOCIATION_ERR_SCTP_END_POINTS_ARE_SAME_IN_ASSOCIATION;
                            }
                        }
                    }
                    delete pLocalRes;
                }
            }
        }
        delete pRes;
    }
    else if(pIwfSigtranAssociationConfig -> has_remoteendpoint())
    {
        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
        LocalIwfSigtranAssociationConfigObj.set_associationname(pIwfSigtranAssociationConfig->associationname());

        sql_IWFSigtranAssociation_Create_Select_Query(&LocalIwfSigtranAssociationConfigObj,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        DLOG_DEBUG("pRes->rowsCount=%d",pRes->rowsCount());
        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("IWF_LOCAL_SCTP_ENDPOINT_ID"))
                {
                    sql::ResultSet *pLocalRes = NULL;
                    IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
                    LocalIwfSigtranSctpEndPointConfigObj.set_sctpendpointid(pRes->getInt("IWF_LOCAL_SCTP_ENDPOINT_ID"));

                    sql_IWFSctpEndpoint_Create_Select_Query(&LocalIwfSigtranSctpEndPointConfigObj,sStatement);

                    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pLocalRes)) != IWF_DB_SUCCESS)
                    {
                        if(pLocalRes != NULL)    
                        {
                            delete pLocalRes;
                        }
                        DLOG_ERROR("Query Execution Failed %s",sStatement);

                        if(iReturn == IWF_DB_FAIL)
                            iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;


                        DLOG_DEBUG("iReturn = %d",iReturn);
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return iReturn;
                    }

                    memset(sStatement,0,MAX_STATEMENT_SIZE);

                    DLOG_DEBUG("pLocalRes->rowsCount=%d",pLocalRes->rowsCount());
                    if(pLocalRes->rowsCount() > 0)
                    {
                        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();
                        if(pLocalRes->next())
                        {
                            DLOG_DEBUG("comparison %s == %s",pLocalRes->getString("ENDPOINT_NAME").c_str(),pLocalIwfSigtranSctpEndPointConfig->endpointname().c_str());
                            if(pLocalRes->getString("ENDPOINT_NAME") == pLocalIwfSigtranSctpEndPointConfig->endpointname())
                            {
                                delete pLocalRes;
                                DLOG_ERROR("Both sctpEndPoints are same!!!");   
                                DLOG_NONE(" < %s ",__FUNCTION__);
                                return MOD_ASSOCIATION_ERR_SCTP_END_POINTS_ARE_SAME_IN_ASSOCIATION;;
                            }
                        }
                    }
                    delete pLocalRes;
                }
            }
        }
        delete pRes;
    }

    if(pIwfSigtranAssociationConfig->has_associationname())
    {
        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
        LocalIwfSigtranAssociationConfigObj.set_associationname(pIwfSigtranAssociationConfig->associationname());

        sql_IWFSigtranAssociation_Create_Select_Query(&LocalIwfSigtranAssociationConfigObj,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Association is not Present");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_ASSOCIATION_ERR_NOT_PRESENT;
        }
        else if(!pIwfSigtranAssociationConfig->has_aspid() && pRes->rowsCount() > 0)
        {
            //Fill AspId in Request Buffer for validation of RemoteEndPoint
            while(pRes->next())
            {
                pIwfSigtranAssociationConfig->set_aspid(pRes->getInt("ASP_ID"));
            }
        }
        delete pRes;
    }

    if(pIwfSigtranAssociationConfig->has_sctpprofile())
    {
        IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = pIwfSigtranAssociationConfig->mutable_sctpprofile();

        IwfSigtranSctpProfileConfig LocalIwfSigtranSctpProfileConfigObj;
        LocalIwfSigtranSctpProfileConfigObj.set_sctpprofilename(pIwfSigtranSctpProfileConfig->sctpprofilename());

        sql_IWFSigtranSCTPProfile_Create_Select_Query(&LocalIwfSigtranSctpProfileConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Sctp Profile is not Present");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_ASSOCIATION_ERR_SCTP_PROFILE_NOT_PRESENT;
        }
        
        delete pRes;
    }

    if(pIwfSigtranAssociationConfig->has_associationsetname())
    {
        IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;
        LocalIwfSigtranAssociationSetConfigObj.set_associationsetname(pIwfSigtranAssociationConfig->associationsetname());

        sql_IWFSigtranAssocSet_Create_Select_Query(&LocalIwfSigtranAssociationSetConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Association Set is not presert");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_ASSOCIATION_ERR_ASSOCIATION_SET_NOT_PRESENT;
        }
        else
        {
            if((iReturn = mysql_IwfSigtranAssociation_set_Assoctionid(pIwfSigtranAssociationConfig)) != IWF_DB_SUCCESS)
            {
                delete pRes;
                if(iReturn == IWF_DB_FAIL)
                    iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;

                DLOG_DEBUG("iReturn = %d",iReturn);
                return iReturn;
            }
        }
    }

    if(pIwfSigtranAssociationConfig->has_remoteendpoint())
    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();
        IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
        LocalIwfSigtranSctpEndPointConfigObj.set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSctpEndpoint_Create_Select_Query(&LocalIwfSigtranSctpEndPointConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Remote end point is not presert");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_ASSOCIATION_ERR_SCTP_END_POINT_NOT_PRESENT;
        }
        delete pRes;
    }

    if(pIwfSigtranAssociationConfig->has_localendpoint())
    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();
        IwfSigtranSctpEndPointConfig LocalIwfSigtranSctpEndPointConfigObj;
        LocalIwfSigtranSctpEndPointConfigObj.set_endpointname(pIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSctpEndpoint_Create_Select_Query(&LocalIwfSigtranSctpEndPointConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("Local end point is not presert");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_ASSOCIATION_ERR_SCTP_END_POINT_NOT_PRESENT;
        }
        delete pRes;
    }

#if 0
    if(pIwfSigtranAssociationConfig->has_localendpoint())
    {
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig -> mutable_localendpoint();
        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig2 = LocalIwfSigtranAssociationConfigObj.mutable_localendpoint();
        pLocalIwfSigtranSctpEndPointConfig2->set_endpointname(pLocalIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSigtranAssociation_Create_Select_Query(&LocalIwfSigtranAssociationConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(pRes->getString("IWF_SIGTRAN_ASSOC_NAME") != pIwfSigtranAssociationConfig->associationname())
                {
                    delete pRes;
                    DLOG_ERROR("LocalEndPoint is already part of some other Association");   
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_ASSOCIATION_ERR_LOCALENDPOINT_ALREADY_USED_IN_ASSOCIATION;
                }
            }
        }
        delete pRes;
    }
#endif
    if(pIwfSigtranAssociationConfig->has_remoteendpoint())
    {
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig3 = pIwfSigtranAssociationConfig -> mutable_remoteendpoint();
        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj2;
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig4 = LocalIwfSigtranAssociationConfigObj2.mutable_localendpoint();
        pLocalIwfSigtranSctpEndPointConfig4->set_endpointname(pLocalIwfSigtranSctpEndPointConfig3->endpointname());

        sql_IWFSigtranAssociation_Create_Select_Query(&LocalIwfSigtranAssociationConfigObj2,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(pRes->getString("IWF_SIGTRAN_ASSOC_NAME") != pIwfSigtranAssociationConfig->associationname())
                {
                    delete pRes;
                    DLOG_ERROR("RemoteEndPoint is already part of some other Association");   
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_ASSOCIATION_ERR_REMOTEENDPOINT_ALREADY_USED_IN_ASSOCIATION;
                }
            }
        }
        delete pRes;
    }
    if(pIwfSigtranAssociationConfig->has_remoteendpoint())
    {
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig -> mutable_remoteendpoint();
        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj;
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig2 = LocalIwfSigtranAssociationConfigObj.mutable_remoteendpoint();
        pLocalIwfSigtranSctpEndPointConfig2->set_endpointname(pLocalIwfSigtranSctpEndPointConfig->endpointname());

        sql_IWFSigtranAssociation_Create_Select_Query(&LocalIwfSigtranAssociationConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            while(pRes->next())
            {
                if(pIwfSigtranAssociationConfig->has_aspid() && (pRes->getInt("ASP_ID") == (int)pIwfSigtranAssociationConfig->aspid()))
                {
                    if(pRes->getString("IWF_SIGTRAN_ASSOC_NAME") != pIwfSigtranAssociationConfig->associationname())
                    {
                        delete pRes;
                        DLOG_ERROR("RemoteEndPoint is already part of some other Association for same node with same AspId");
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return MOD_ASSOCIATION_ERR_REMOTEENDPOINT_ALREADY_USED_IN_ASSOCIATION;
                    }
                }
            }
        }
        delete pRes;
        pRes = NULL;
    }

    if(pIwfSigtranAssociationConfig->has_localendpoint())
    {
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig3 = pIwfSigtranAssociationConfig -> mutable_localendpoint();
        IwfSigtranAssociationConfig LocalIwfSigtranAssociationConfigObj2;
        IwfSigtranSctpEndPointConfig *pLocalIwfSigtranSctpEndPointConfig4 = LocalIwfSigtranAssociationConfigObj2.mutable_remoteendpoint();
        pLocalIwfSigtranSctpEndPointConfig4->set_endpointname(pLocalIwfSigtranSctpEndPointConfig3->endpointname());

        sql_IWFSigtranAssociation_Create_Select_Query(&LocalIwfSigtranAssociationConfigObj2,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(pRes->getString("IWF_SIGTRAN_ASSOC_NAME") != pIwfSigtranAssociationConfig->associationname())
                {
                    delete pRes;
                    DLOG_ERROR("LocalEndPoint is already part of some other Association");   
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_ASSOCIATION_ERR_LOCALENDPOINT_ALREADY_USED_IN_ASSOCIATION;
                }
            }
        }
        delete pRes;
    }

    if(pIwfSigtranAssociationConfig->has_aspid())
    {
        pRes = NULL;
        sql_IWFLocalConfig_Create_Check_AspId_Modifcation_Query(pIwfSigtranAssociationConfig->aspid(),sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() <= 0)
        {
            delete pRes;
            DLOG_ERROR("AspId is not same as configured for LocalHost AspId's");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_ASSOCIATION_ERR_ASP_ID_NOT_PRESENT;
        }
        delete pRes;
    }
    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociations_get_Associationid(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    int iReturn;


    sql_IWFSigtranAssocSetMapping_Create_OrderBy_Select_Query(pIwfSigtranAssociationConfig,sStatement);
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

    int iLocalAssociationID = 0;
    int iFlag = 0;
    try
    {

        while(pRes->next())
        {
            if(!pRes->isNull("IWF_SIGTRAN_ASSOC_MAPPING_ID"))
            {
                if(pRes->getInt("IWF_SIGTRAN_ASSOC_MAPPING_ID") != iLocalAssociationID)
                {
                    iFlag = 1;
                    break;
                }
                iLocalAssociationID++;                
            }
        }

        delete pRes;

        if(iFlag != 0 || iLocalAssociationID <= MAX_ASSOCIATION_MAPPING_ID)
        {
            DLOG_INFO("AssociationMappingID Selected = %d",iLocalAssociationID);
            pIwfSigtranAssociationConfig->set_associationmappingid(iLocalAssociationID);
        }
        else
        {
            DLOG_INFO("AssociationMappingID not Selected since max limit %d reached for mapping.",iLocalAssociationID);
            return ADD_ASSOCIATION_MAPPING_ERR_REACHED_MAX_LIMIT;
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

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociations_Add_Config_Reqs(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = IWF_DB_SUCCESS_SEND;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranAssociationsConfig->associationinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(ADD_ASSOCIATION_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[ADD_ASSOCIATION_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig = pIwfSigtranAssociationsConfig->mutable_associationinfo(i);

        if((iReturn = mysql_IwfSigtranAssociation_Add_Validation(pIwfSigtranAssociationConfig,resp)) != IWF_DB_SUCCESS)
        {

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if(iReturn == IWF_DB_SUCCESS)
        {
            sql_IWFSigtranAssociation_Create_Add_Query(pIwfSigtranAssociationConfig,sStatement);
        }

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        /*******************************************************************************/
        if((iReturn = mysql_IwfSigtranAssociations_get_Associationid(pIwfSigtranAssociationConfig)) != DRE_DB_SUCCESS)
        {   

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }   


        sql_IWFSigtranAssocSetMapping_Create_Check_Modifcation_Query(pIwfSigtranAssociationConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_IWFSigtranAssocSetMapping_Create_Add_Query(pIwfSigtranAssociationConfig,sStatement);
        }
        else // MOD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present:ADD_ASSOCIATION_ERR_ALREADY_ASSOCIATED_TO_ASSOCIATIONSET!!");   
            mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,ADD_ASSOCIATION_ERR_ALREADY_ASSOCIATED_TO_ASSOCIATIONSET);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ASSOCIATION_ERR_ALREADY_ASSOCIATED_TO_ASSOCIATIONSET;
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        /************************************************************************************************/

#if 0
        int iMutihomingCount = pIwfSigtranAssociationConfig->multihominginfo_size();
        for(int j=0;j<iMutihomingCount;j++)
        {

            if((iReturn = mysql_IwfSigtranMultihoming_Validation(pIwfSigtranAssociationConfig,resp,j)) != IWF_DB_SUCCESS)
            {
                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;
                else if(iReturn == GENERIC_ERR_DB_ERROR)
                    iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;
                else if(iReturn == GENERIC_ASSOCIATION_ERR_MULTIHOMING_IP_MAXCOUNT)
                    iReturn = ADD_ASSOCIATION_ERR_MAX_MULTIHOMING_IP;

                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn,j);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            sql_IWFSigtranMultihoming_Create_Check_Modifcation_Query(pIwfSigtranAssociationConfig,sStatement,j);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;

                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn,j);

                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                sql_IWFSigtranMultihoming_Create_Add_Query(pIwfSigtranAssociationConfig,sStatement,j);
            }
            else // MOD
            {
                delete pRes;
                DLOG_ERROR("Record Already Present:ADD_ASSOCIATION_ERR_MULTIHOMING_IP_ALREADY_PRESENT");   
                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranAssociationConfig,resp,ADD_ASSOCIATION_ERR_MULTIHOMING_IP_ALREADY_PRESENT,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_ASSOCIATION_ERR_MULTIHOMING_IP_ALREADY_PRESENT;
            }

            delete pRes;
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_ASSOCIATION_ERR_DB_ERROR;

                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranAssociationConfig,resp,iReturn,j);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
#endif
        {
            IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;
            IwfSigtranAssociationConfig *pLocalIwfSigtranAssociationConfig = LocalIwfSigtranAssociationSetConfigObj.add_associationinfo();

            pLocalIwfSigtranAssociationConfig->set_associationname(pIwfSigtranAssociationConfig->associationname());

            Fill_IWFSigtranAssocSetMapping_protobuff(&LocalIwfSigtranAssociationSetConfigObj,resp,0);

            pIwfSigtranAssociationConfig->set_associationid(pLocalIwfSigtranAssociationConfig->associationid());
            pIwfSigtranAssociationConfig->set_associationmappingid(pLocalIwfSigtranAssociationConfig->associationmappingid());
            pIwfSigtranAssociationConfig->set_associationsetid(LocalIwfSigtranAssociationSetConfigObj.associationsetid());
        }
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociationSet_Validation(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig, IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;

    LocalIwfSigtranAssociationSetConfigObj.set_associationsetname(pIwfSigtranAssociationSetConfig->associationsetname());
    LocalIwfSigtranAssociationSetConfigObj.set_status(1);

    sql_IWFSigtranAssocSet_Create_Select_Query(&LocalIwfSigtranAssociationSetConfigObj,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = GENERIC_ERR_DB_ERROR;


        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() > 0)
    {
        delete pRes;
        DLOG_ERROR("Association is in Enabled state");   
        DLOG_NONE(" < %s ",__FUNCTION__);
        return GENERIC_ERR_ASSOCIATIONSET_IN_ACTIVE_STATE;
    }
    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociationSet_Mod_Validation(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig, IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    {
        sql_IWFSigtranAssocSet_Create_Check_Modifcation_Query(pIwfSigtranAssociationSetConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ASSOCIATIONSET_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_ERROR("AssociationSet Not present");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_ASSOCIATIONSET_ERR_NO_PRESENT;
        }
        delete pRes;
    }
    pRes = NULL;
#if 0
    {
        IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;
        LocalIwfSigtranAssociationSetConfigObj.set_adjacenpointcode(pIwfSigtranAssociationSetConfig->adjacenpointcode());

        sql_IWFSigtranAssocSet_Create_Select_Query(&LocalIwfSigtranAssociationSetConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ASSOCIATIONSET_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(pRes->getString("IWF_SIGTRAN_ASSOC_SET_NAME") != pIwfSigtranAssociationSetConfig->associationsetname())
                {
                    delete pRes;
                    DLOG_ERROR("Adj-PointCode is already configured for some other AssociationSet");   
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_ASSOCIATIONSET_ERR_ADJPOINTCODE_ALREADY_PRESENT;
                }
            }
        }
        delete pRes;
    }
#endif
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociationSets_Mod_Config_Reqs(IwfSigtranAssociationSetsConfig *pIwfSigtranAssociationSetsConfig,IWFCfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranAssociationSetsConfig->associationsetinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(MOD_ASSOCIATIONSET_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[MOD_ASSOCIATIONSET_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig = pIwfSigtranAssociationSetsConfig->mutable_associationsetinfo(i);

        if((iReturn = mysql_IwfSigtranAssociationSet_Mod_Validation(pIwfSigtranAssociationSetConfig,resp)) != IWF_DB_SUCCESS)
        {
            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ASSOCIATIONSET_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
#if 0
        if((iReturn = mysql_IwfSigtranAssociationSet_Validation(pIwfSigtranAssociationSetConfig,resp)) != IWF_DB_SUCCESS)
        {
            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ASSOCIATIONSET_ERR_DB_ERROR;
            else if(iReturn == GENERIC_ERR_DB_ERROR)
                iReturn = MOD_ASSOCIATIONSET_ERR_DB_ERROR;
            else if(iReturn == GENERIC_ERR_ASSOCIATIONSET_IN_ACTIVE_STATE)
                iReturn = MOD_ASSOCIATIONSET_ERR_ASSOCIATIONSET_IN_ACTIVE_STATE;

            mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,iReturn);
            
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
#endif
        if(iReturn == IWF_DB_SUCCESS)
        {
            sql_IWFSigtranAssocSet_Create_Mod_Query(pIwfSigtranAssociationSetConfig,sStatement);
        }

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ASSOCIATIONSET_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;
        LocalIwfSigtranAssociationSetConfigObj.set_associationsetname(pIwfSigtranAssociationSetConfig->associationsetname());
        Fill_IWFSigtranAssocSet_protobuff(&LocalIwfSigtranAssociationSetConfigObj,resp);
        pIwfSigtranAssociationSetConfig->CopyFrom(LocalIwfSigtranAssociationSetConfigObj);
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociationSet_Add_Validation(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig, IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    {
        sql_IWFSigtranAssocSet_Create_Check_Modifcation_Query(pIwfSigtranAssociationSetConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATIONSET_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0) 
        {
            delete pRes;
            DLOG_ERROR("Record Already Present:ADD_ASSOCIATIONSET_ERR_ALREADY_PRESENT!!");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ASSOCIATIONSET_ERR_ALREADY_PRESENT;
        }
        delete pRes;
    }
#if 0
    if(pIwfSigtranAssociationSetConfig->has_aspid())
    {
        pRes = NULL;
        sql_IWFLocalConfig_Create_Check_AspId_Modifcation_Query(pIwfSigtranAssociationSetConfig->aspid(),sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATIONSET_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() <= 0)
        {
            delete pRes;
            DLOG_ERROR("AspId is not same as configured for LocalHost AspId's");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ASSOCIATIONSET_ERR_ASP_ID_NOT_PRESENT;
        }
        delete pRes;
    }
    {
        pRes = NULL;
        IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;
        LocalIwfSigtranAssociationSetConfigObj.set_adjacenpointcode(pIwfSigtranAssociationSetConfig->adjacenpointcode());

        sql_IWFSigtranAssocSet_Create_Select_Query(&LocalIwfSigtranAssociationSetConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATIONSET_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0)
        {
            delete pRes;
            DLOG_ERROR("Adj-Pointcode is already configured for some Assos-Set");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ASSOCIATIONSET_ERR_ADJPOINTCODE_ALREADY_PRESENT;
        }
        delete pRes;
    }
#endif
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranAssociationSets_Add_Config_Reqs(IwfSigtranAssociationSetsConfig *pIwfSigtranAssociationSetsConfig,IWFCfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranAssociationSetsConfig->associationsetinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(ADD_ASSOCIATIONSET_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[ADD_ASSOCIATIONSET_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig = pIwfSigtranAssociationSetsConfig->mutable_associationsetinfo(i);

        if((iReturn = mysql_IwfSigtranAssociationSet_Add_Validation(pIwfSigtranAssociationSetConfig,resp)) != IWF_DB_SUCCESS)
        {
            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATIONSET_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if(iReturn == IWF_DB_SUCCESS)
        {
            sql_IWFSigtranAssocSet_Create_Add_Query(pIwfSigtranAssociationSetConfig,sStatement);
        }

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ASSOCIATIONSET_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(pIwfSigtranAssociationSetConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;
        LocalIwfSigtranAssociationSetConfigObj.set_associationsetname(pIwfSigtranAssociationSetConfig->associationsetname());
        Fill_IWFSigtranAssocSet_protobuff(&LocalIwfSigtranAssociationSetConfigObj,resp);
        pIwfSigtranAssociationSetConfig->CopyFrom(LocalIwfSigtranAssociationSetConfigObj);
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranSctpEndPoints_Add_Config_Reqs(IwfSigtranSctpEndPointsConfig *pIwfSigtranSctpEndPointsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranSctpEndPointsConfig->sctpendpointinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(ADD_SCTPENDPOINT_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[ADD_SCTPENDPOINT_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranSctpEndPointsConfig->mutable_sctpendpointinfo(i);

        if((iReturn = mysql_IWFSctpEndPoint_Validation(pIwfSigtranSctpEndPointConfig,resp)) != IWF_DB_SUCCESS)
        {
            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_SCTPENDPOINT_ERR_DB_ERROR;
            mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        sql_IWFSctpEndpoint_Create_Check_Modifcation_Query(pIwfSigtranSctpEndPointConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_SCTPENDPOINT_ERR_DB_ERROR;

            mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_IWFSctpEndpoint_Create_Add_Query(pIwfSigtranSctpEndPointConfig,sStatement);
        }
        else // MOD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present:ADD_SCTPENDPOINT_ERR_ALREADY_PRESENT!!");   
            mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,ADD_SCTPENDPOINT_ERR_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_SCTPENDPOINT_ERR_ALREADY_PRESENT;
        }
        delete pRes;
        
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_SCTPENDPOINT_ERR_DB_ERROR;

            mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        
        int iMutihomingCount = pIwfSigtranSctpEndPointConfig->multihominginfo_size();
        for(int j=0;j<iMutihomingCount;j++)
        {
            pRes = NULL;
            if((iReturn = mysql_IwfSigtranMultihoming_Validation(pIwfSigtranSctpEndPointConfig,resp,j)) != IWF_DB_SUCCESS)
            {
                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_SCTPENDPOINT_ERR_DB_ERROR;
                else if(iReturn == GENERIC_ERR_DB_ERROR)
                    iReturn = ADD_SCTPENDPOINT_ERR_DB_ERROR;
                else if(iReturn == GENERIC_SCTPENDPOINT_ERR_MULTIHOMING_IP_MAXCOUNT)
                    iReturn = ADD_SCTPENDPOINT_ERR_MAX_MULTIHOMING_IP;
                else if(iReturn == GENERIC_SCTPENDPOINT_ERR_MULTIHOMING_IP_SAMEAS_PRIMARY_IP)
                    iReturn = ADD_SCTPENDPOINT_ERR_MULTIHOMING_IP_SAMEAS_PRIMARY_IP;

                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn,j);
                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            sql_IWFSigtranMultihoming_Create_Check_Modifcation_Query(pIwfSigtranSctpEndPointConfig,sStatement,j);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_SCTPENDPOINT_ERR_DB_ERROR;

                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn,j);

                DLOG_DEBUG("iReturn = %d",iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                sql_IWFSigtranMultihoming_Create_Add_Query(pIwfSigtranSctpEndPointConfig,sStatement,j);
            }
            else // MOD
            {
                delete pRes;
                DLOG_ERROR("Record Already Present:ADD_SCTPENDPOINT_ERR_MULTIHOMING_IP_ALREADY_PRESENT");   
                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,ADD_SCTPENDPOINT_ERR_MULTIHOMING_IP_ALREADY_PRESENT,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_SCTPENDPOINT_ERR_MULTIHOMING_IP_ALREADY_PRESENT;
            }

            delete pRes;
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == IWF_DB_FAIL)
                    iReturn = ADD_SCTPENDPOINT_ERR_DB_ERROR;

                mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(pIwfSigtranSctpEndPointConfig,resp,iReturn,j);
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


