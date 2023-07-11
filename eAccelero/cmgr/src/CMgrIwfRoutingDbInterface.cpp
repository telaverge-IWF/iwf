/* *C-*-***********************************
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

void CMgrIwfDbInterface::mysql_set_error_for_IWFSigtranDestination_Config_Reqs(IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    if(pIwfSigtranDestinationConfig->has_destinationname())
        err->add_variables(pIwfSigtranDestinationConfig->destinationname());

    if(iReturn == DEL_DESTINATION_ERR_USED_IN_ROUTE
            || iReturn == MOD_DESTINATION_ERR_USED_IN_ROUTE)
    {
        char sStatement[MAX_STATEMENT_SIZE] = {0};

        IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfigObj;
        IwfSigtranDestinationConfig *pLocalIwfSigtranDestinationConfig = NULL;
        pLocalIwfSigtranDestinationConfig = LocalIwfSigtranRemoteRouteConfigObj.mutable_destinationinfo();
        pLocalIwfSigtranDestinationConfig->set_destinationname(pIwfSigtranDestinationConfig->destinationname());

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
    }

    if(iReturn == DEL_DESTINATION_ERR_USED_IN_TRANSLATOR_RULE
            ||iReturn == MOD_DESTINATION_ERR_USED_IN_TRANSLATOR_RULE)
    {
        char sStatement[MAX_STATEMENT_SIZE] = {0};
        sql::ResultSet *pRes = NULL;

        IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;
        LocalIwfTranslatorRuleConfigObj.set_destinationname(pIwfSigtranDestinationConfig->destinationname());
        IwfTranslatorType *pIwfTranslatorType = LocalIwfTranslatorRuleConfigObj.mutable_translatortype();
        pIwfTranslatorType->set_translatortypename("DIAMETER");

        sql_IWFTranslatorRule_Create_Select_Query(&LocalIwfTranslatorRuleConfigObj,sStatement);

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

        if(pRes->rowsCount() > 0) 
        {
            if(pRes->next())
            {
                if(!pRes->isNull("RULE_NAME"))
                    err->add_variables(pRes->getString("RULE_NAME"));
            }
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrIwfDbInterface::mysql_set_error_for_IWFSigtranRemoteRoute_Config_Reqs(IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig,IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(iReturn);
        err->set_errormsgkey(iwfErrorMap[iReturn]);
        DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

        if(pIwfSigtranRemoteRouteConfig->has_remoteroutename())
        err->add_variables(pIwfSigtranRemoteRouteConfig->remoteroutename());

    if(iReturn == ADD_ROUTE_ERR_DESTINATION_ALREADY_USED_IN_ROUTE
            ||iReturn == MOD_ROUTE_ERR_DESTINATION_NOT_PRESENT
            ||iReturn == ADD_ROUTE_ERR_DESTINATION_NOT_PRESENT
            ||iReturn == MOD_ROUTE_ERR_DESTINATION_ALREADY_USED_IN_ROUTE)
    {
        char sStatement[MAX_STATEMENT_SIZE] = {0};
        sql::ResultSet *pRes = NULL;

        IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig = NULL;
        pIwfSigtranDestinationConfig = pIwfSigtranRemoteRouteConfig -> mutable_destinationinfo();
        if(pIwfSigtranDestinationConfig -> has_destinationname())
            err->add_variables(pIwfSigtranDestinationConfig -> destinationname());

        IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfigObj;
        IwfSigtranDestinationConfig *pLocalIwfSigtranDestinationConfig = LocalIwfSigtranRemoteRouteConfigObj.mutable_destinationinfo();
        pLocalIwfSigtranDestinationConfig->set_destinationname(pIwfSigtranDestinationConfig->destinationname());

        sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfigObj,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

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

    if(iReturn == ADD_ROUTE_ERR_ASSOCIATION_SET_ALREADY_HAVE_ROUTE
            || iReturn == MOD_ROUTE_ERR_ASSOCIATION_SET_NOT_PRESENT
            || iReturn == ADD_ROUTE_ERR_ASSOCIATION_SET_NOT_PRESENT
            || iReturn == MOD_ROUTE_ERR_ASSOCIATION_SET_ALREADY_HAVE_ROUTE
            || iReturn == MOD_ROUTE_ERR_ASSOCIATION_SET_IN_ACTIVE_STATE
            || iReturn == DEL_ROUTE_ERR_ASSOCIATION_SET_IN_ACTIVE_STATE)
    {
        char sStatement[MAX_STATEMENT_SIZE] = {0};
        sql::ResultSet *pRes = NULL;

        if(pIwfSigtranRemoteRouteConfig-> has_associationsetname())
            err->add_variables(pIwfSigtranRemoteRouteConfig->associationsetname());

        IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfigObj;
        LocalIwfSigtranRemoteRouteConfigObj.set_associationsetname(pIwfSigtranRemoteRouteConfig->associationsetname());

        sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfigObj,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

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

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranRemoteRoute_protobuff(IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig,IWFCfgResp *resp,int AssociationSetID)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};

    IwfSigtranAssociationSetConfig IwfSigtranAssociationSetConfigReq;
    IwfSigtranAssociationSetConfigReq.set_associationsetid(AssociationSetID);
    sql_IWFSigtranAssocSet_Create_Select_Query(&IwfSigtranAssociationSetConfigReq,sStatement);

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
            iReturn = GET_ROUTE_ERR_DB_ERROR;

        mysql_set_error_for_IWFSigtranRemoteRoute_Config_Reqs(pIwfSigtranRemoteRouteConfig,resp,iReturn);
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
                if(!pRes->isNull("IWF_SIGTRAN_ASSOC_SET_NAME"))
                    pIwfSigtranRemoteRouteConfig->set_associationsetname(pRes->getString("IWF_SIGTRAN_ASSOC_SET_NAME"));
                if(!pRes->isNull("ASP_ID"))
                    pIwfSigtranRemoteRouteConfig->set_associationsetaspid(pRes->getInt("ASP_ID"));
            }
        }
        else
        {

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

DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranRemoteRoute_protobuff(IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFSigtranRemoteRoute_Create_Select_Query(pIwfSigtranRemoteRouteConfig,sStatement);

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
            iReturn = GET_ROUTE_ERR_DB_ERROR;

        mysql_set_error_for_IWFSigtranRemoteRoute_Config_Reqs(pIwfSigtranRemoteRouteConfig,resp,iReturn);
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
                if(!pRes->isNull("REMOTE_ROUTE_NAME"))
                    pIwfSigtranRemoteRouteConfig->set_remoteroutename(pRes->getString("REMOTE_ROUTE_NAME"));
                if(!pRes->isNull("IWF_SIGTRAN_ASSOC_SET_ID"))
                    pIwfSigtranRemoteRouteConfig->set_associationsetid(pRes->getInt("IWF_SIGTRAN_ASSOC_SET_ID"));

                if(!pRes->isNull("IWF_SIGTRAN_DESTINATION_ID"))
                {
                    IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig = pIwfSigtranRemoteRouteConfig->mutable_destinationinfo();
                    pIwfSigtranDestinationConfig->set_destinationid(pRes->getInt("IWF_SIGTRAN_DESTINATION_ID"));
                }
                if(!pRes->isNull("PRIORITY"))
                    pIwfSigtranRemoteRouteConfig->set_priority(pRes->getInt("PRIORITY"));

                Fill_IWFSigtranRemoteRoute_protobuff(pIwfSigtranRemoteRouteConfig,resp,pIwfSigtranRemoteRouteConfig->associationsetid());
                DLOG_DEBUG("pIwfSigtranRemoteRouteConfig = %s",pIwfSigtranRemoteRouteConfig->DebugString().c_str()); 

            }
        }
        else
        {
            delete pRes;
            return GET_ROUTE_ERR_NO_DATA;
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

DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranDestination_protobuff(IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql_IWFSigtranDestination_Create_Select_Query(pIwfSigtranDestinationConfig,sStatement);

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
            iReturn = GET_DESTINATION_ERR_DB_ERROR;

        mysql_set_error_for_IWFSigtranDestination_Config_Reqs(pIwfSigtranDestinationConfig,resp,iReturn);
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
                if(!pRes->isNull("IWF_SIGTRAN_DESTINATION_ID"))
                    pIwfSigtranDestinationConfig->set_destinationid(pRes->getInt("IWF_SIGTRAN_DESTINATION_ID"));
                if(!pRes->isNull("DEST_NAME"))
                    pIwfSigtranDestinationConfig->set_destinationname(pRes->getString("DEST_NAME"));
                if(!pRes->isNull("IWF_PROTOCOL_FAMILY_ID"))
                    pIwfSigtranDestinationConfig->set_protocolid(pRes->getInt("IWF_PROTOCOL_FAMILY_ID"));
                if(!pRes->isNull("ADDRESS_STYLE"))
                    pIwfSigtranDestinationConfig->set_addressstyle(pRes->getString("ADDRESS_STYLE"));
                if(!pRes->isNull("ADDRESS_TYPE"))
                    pIwfSigtranDestinationConfig->set_addresstype(pRes->getString("ADDRESS_TYPE"));
                if(!pRes->isNull("POINTCODE"))
                    pIwfSigtranDestinationConfig->set_pointcode(pRes->getInt("POINTCODE"));
                if(!pRes->isNull("NI"))
                    pIwfSigtranDestinationConfig->set_networkindicator(pRes->getInt("NI"));
                if(!pRes->isNull("SSN"))
                    pIwfSigtranDestinationConfig->set_ssn(pRes->getInt("SSN"));
                if(!pRes->isNull("GTI"))
                    pIwfSigtranDestinationConfig->set_gti(pRes->getInt("GTI"));
                if(!pRes->isNull("TRANSLATION_TYPE"))
                    pIwfSigtranDestinationConfig->set_translationtype(pRes->getInt("TRANSLATION_TYPE"));
                if(!pRes->isNull("NUMBERING_PLAN"))
                    pIwfSigtranDestinationConfig->set_numberingplan(pRes->getInt("NUMBERING_PLAN"));
                if(!pRes->isNull("ENCODING_SCHEME"))
                    pIwfSigtranDestinationConfig->set_encodingscheme(pRes->getInt("ENCODING_SCHEME"));
                if(!pRes->isNull("NATURE_OF_ADDRESS_INDICATOR"))
                    pIwfSigtranDestinationConfig->set_natureofaddrind(pRes->getInt("NATURE_OF_ADDRESS_INDICATOR"));
                if(!pRes->isNull("SIO"))
                    pIwfSigtranDestinationConfig->set_sio(pRes->getInt("SIO"));
                if(!pRes->isNull("GT_ADDR_DIGITS"))
                    pIwfSigtranDestinationConfig->set_gtaddrdigits(pRes->getString("GT_ADDR_DIGITS"));
            }
        }
        else
        {
            delete pRes;
            return GET_DESTINATION_ERR_NO_DATA;
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


DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranRemoteRoute_Get_Config_Reqs(IwfSigtranRemoteRoutesConfig *pIwfSigtranRemoteRoutesConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);

    return Fill_IWFSigtranRemoteRoutes_protobuff(pIwfSigtranRemoteRoutesConfig,resp);
}

DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranRemoteRoutes_protobuff(IwfSigtranRemoteRoutesConfig *pIwfSigtranRemoteRoutesConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    int i=0;
    int ifData = 0;

    IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfigObj;
    IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig = NULL;

    int iCount = pIwfSigtranRemoteRoutesConfig->remoterouteinfo_size();
    DLOG_INFO("pIwfSigtranRemoteRoutesConfig->remoterouteinfo_size() = %d",iCount);
    do
    {
        if(iCount != 0)
            pIwfSigtranRemoteRouteConfig = pIwfSigtranRemoteRoutesConfig->mutable_remoterouteinfo(i);
        else
            pIwfSigtranRemoteRouteConfig = &LocalIwfSigtranRemoteRouteConfigObj;

        sql_IWFSigtranRemoteRoute_Create_Select_Query(pIwfSigtranRemoteRouteConfig,sStatement);

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
                iReturn = GET_ROUTE_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranRemoteRoute_Config_Reqs(pIwfSigtranRemoteRouteConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
            if(pRes->rowsCount() != 0)
            {
                IwfSigtranRemoteRoutesConfig *LocalIwfSigtranRemoteRoutesConfig = resp->mutable_remoterouteinfo();

                while(pRes->next())
                {
                    pIwfSigtranRemoteRouteConfig = LocalIwfSigtranRemoteRoutesConfig->add_remoterouteinfo();

                    ifData = 1;

                    if(!pRes->isNull("REMOTE_ROUTE_NAME"))
                        pIwfSigtranRemoteRouteConfig->set_remoteroutename(pRes->getString("REMOTE_ROUTE_NAME"));
                    if(!pRes->isNull("IWF_SIGTRAN_ASSOC_SET_ID"))
                        pIwfSigtranRemoteRouteConfig->set_associationsetid(pRes->getInt("IWF_SIGTRAN_ASSOC_SET_ID"));

                    if(!pRes->isNull("IWF_SIGTRAN_DESTINATION_ID"))
                    {
                        IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig = pIwfSigtranRemoteRouteConfig->mutable_destinationinfo();
                        pIwfSigtranDestinationConfig->set_destinationid(pRes->getInt("IWF_SIGTRAN_DESTINATION_ID"));
                        Fill_IWFSigtranDestination_protobuff(pIwfSigtranDestinationConfig,resp);
                    }
                    if(!pRes->isNull("PRIORITY"))
                        pIwfSigtranRemoteRouteConfig->set_priority(pRes->getInt("PRIORITY"));

                    Fill_IWFSigtranRemoteRoute_protobuff(pIwfSigtranRemoteRouteConfig,resp,pIwfSigtranRemoteRouteConfig->associationsetid());


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
        DLOG_DEBUG("There is no data in the table setting GET_ROUTE_ERR_NO_DATA");
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(GET_ROUTE_ERR_NO_DATA);
        err->set_errormsgkey(iwfErrorMap[GET_ROUTE_ERR_NO_DATA]);
        DLOG_DEBUG("Error key is %s", (iwfErrorMap[GET_ROUTE_ERR_NO_DATA]).c_str());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}

#endif

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranDestination_Get_Config_Reqs(IwfSigtranDestinationsConfig *pIwfSigtranDestinationsConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_NONE(" < %s ",__FUNCTION__);

    return Fill_IWFSigtranDestinations_protobuff(pIwfSigtranDestinationsConfig,resp);
}


DbStatus_e CMgrIwfDbInterface::Fill_IWFSigtranDestinations_protobuff(IwfSigtranDestinationsConfig *pIwfSigtranDestinationsConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    int i=0;
    int ifData = 0;

    IwfSigtranDestinationConfig LocalIwfSigtranDestinationConfigObj;
    IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig = NULL;

    int iCount = pIwfSigtranDestinationsConfig->destioninfo_size();
    DLOG_INFO("pIwfSigtranDestinationsConfig->destioninfo_size() = %d",iCount);
    do
    {
        if(iCount != 0)
            pIwfSigtranDestinationConfig = pIwfSigtranDestinationsConfig->mutable_destioninfo(i);
        else
            pIwfSigtranDestinationConfig = &LocalIwfSigtranDestinationConfigObj;

        sql_IWFSigtranDestination_Create_Select_Query(pIwfSigtranDestinationConfig,sStatement);

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
                iReturn = GET_DESTINATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranDestination_Config_Reqs(pIwfSigtranDestinationConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG("pRes->rowsCount() = %d",pRes->rowsCount());
            if(pRes->rowsCount() != 0)
            {
                IwfSigtranDestinationsConfig *LocalIwfSigtranDestinationsConfig = resp->mutable_destionationinfo();

                while(pRes->next())
                {
                    pIwfSigtranDestinationConfig = LocalIwfSigtranDestinationsConfig->add_destioninfo();

                    ifData = 1;
                    if(!pRes->isNull("IWF_SIGTRAN_DESTINATION_ID"))
                        pIwfSigtranDestinationConfig->set_destinationid(pRes->getInt("IWF_SIGTRAN_DESTINATION_ID"));
                    if(!pRes->isNull("DEST_NAME"))
                        pIwfSigtranDestinationConfig->set_destinationname(pRes->getString("DEST_NAME"));
                    if(!pRes->isNull("IWF_PROTOCOL_FAMILY_ID"))
                        pIwfSigtranDestinationConfig->set_protocolid(pRes->getInt("IWF_PROTOCOL_FAMILY_ID"));
                    if(!pRes->isNull("ADDRESS_STYLE"))
                        pIwfSigtranDestinationConfig->set_addressstyle(pRes->getString("ADDRESS_STYLE"));
                    if(!pRes->isNull("ADDRESS_TYPE"))
                        pIwfSigtranDestinationConfig->set_addresstype(pRes->getString("ADDRESS_TYPE"));
                    if(!pRes->isNull("POINTCODE"))
                        pIwfSigtranDestinationConfig->set_pointcode(pRes->getInt("POINTCODE"));
                    if(!pRes->isNull("NI"))
                        pIwfSigtranDestinationConfig->set_networkindicator(pRes->getInt("NI"));
                    if(!pRes->isNull("SSN"))
                        pIwfSigtranDestinationConfig->set_ssn(pRes->getInt("SSN"));
                    if(!pRes->isNull("GTI"))
                        pIwfSigtranDestinationConfig->set_gti(pRes->getInt("GTI"));
                    if(!pRes->isNull("TRANSLATION_TYPE"))
                        pIwfSigtranDestinationConfig->set_translationtype(pRes->getInt("TRANSLATION_TYPE"));
                    if(!pRes->isNull("NUMBERING_PLAN"))
                        pIwfSigtranDestinationConfig->set_numberingplan(pRes->getInt("NUMBERING_PLAN"));
                    if(!pRes->isNull("ENCODING_SCHEME"))
                        pIwfSigtranDestinationConfig->set_encodingscheme(pRes->getInt("ENCODING_SCHEME"));
                    if(!pRes->isNull("NATURE_OF_ADDRESS_INDICATOR"))
                        pIwfSigtranDestinationConfig->set_natureofaddrind(pRes->getInt("NATURE_OF_ADDRESS_INDICATOR"));
                    if(!pRes->isNull("SIO"))
                        pIwfSigtranDestinationConfig->set_sio(pRes->getInt("SIO"));
                    if(!pRes->isNull("GT_ADDR_DIGITS"))
                        pIwfSigtranDestinationConfig->set_gtaddrdigits(pRes->getString("GT_ADDR_DIGITS"));

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
        DLOG_DEBUG("There is no data in the table setting GET_DESTINATION_ERR_NO_DATA");
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(GET_DESTINATION_ERR_NO_DATA);
        err->set_errormsgkey(iwfErrorMap[GET_DESTINATION_ERR_NO_DATA]);
        DLOG_DEBUG("Error key is %s", (iwfErrorMap[GET_DESTINATION_ERR_NO_DATA]).c_str());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return IWF_DB_SUCCESS;
}


DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranDestination_Mod_Validation(IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
#if 0
    {
        IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfigObj;

        IwfSigtranDestinationConfig *pLocalIwfSigtranDestinationConfig = LocalIwfSigtranRemoteRouteConfigObj.mutable_destinationinfo();

        pLocalIwfSigtranDestinationConfig->set_destinationname(pIwfSigtranDestinationConfig->destinationname());

        sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Desination is used in Remote");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_DESTINATION_ERR_USED_IN_ROUTE;

        }
        delete pRes;
    }
    pRes = NULL;
#endif
    {
        IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;
        LocalIwfTranslatorRuleConfigObj.set_destinationname(pIwfSigtranDestinationConfig->destinationname());
        IwfTranslatorType *pIwfTranslatorType = LocalIwfTranslatorRuleConfigObj.mutable_translatortype();
        pIwfTranslatorType->set_translatortypename("DIAMETER");

        sql_IWFTranslatorRule_Create_Select_Query(&LocalIwfTranslatorRuleConfigObj,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Desination is used in Translator Rule");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_DESTINATION_ERR_USED_IN_TRANSLATOR_RULE;
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranDestination_Del_Validation(IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    {
        IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfigObj;
        IwfSigtranDestinationConfig *pLocalIwfSigtranDestinationConfig = NULL;
        pLocalIwfSigtranDestinationConfig = LocalIwfSigtranRemoteRouteConfigObj.mutable_destinationinfo();
        pLocalIwfSigtranDestinationConfig->set_destinationname(pIwfSigtranDestinationConfig->destinationname());

        sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfigObj,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Desination is used in Route");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_DESTINATION_ERR_USED_IN_ROUTE;
        }
        delete pRes;
    }
    pRes = NULL;

    {
        IwfTranslatorRuleConfig LocalIwfTranslatorRuleConfigObj;
        LocalIwfTranslatorRuleConfigObj.set_destinationname(pIwfSigtranDestinationConfig->destinationname());
        IwfTranslatorType *pIwfTranslatorType = LocalIwfTranslatorRuleConfigObj.mutable_translatortype();
        pIwfTranslatorType->set_translatortypename("DIAMETER");

        sql_IWFTranslatorRule_Create_Select_Query(&LocalIwfTranslatorRuleConfigObj,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Desination is used in Translator Rule");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_DESTINATION_ERR_USED_IN_TRANSLATOR_RULE;
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

#if 1

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranRemoteRoute_Fill_For_RemoteRoute(IwfSigtranRemoteRoutesConfig *pIwfSigtranRemoteRoutesConfig,IwfSigtranRemoteRoutesConfig *pOrignalIwfSigtranRemoteRoutesConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    int iReturn = IWF_DB_SUCCESS;
    int iCount = pOrignalIwfSigtranRemoteRoutesConfig->remoterouteinfo_size();

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig = pIwfSigtranRemoteRoutesConfig->add_remoterouteinfo();
        IwfSigtranRemoteRouteConfig *pOrginalIwfSigtranRemoteRouteConfig = pOrignalIwfSigtranRemoteRoutesConfig->mutable_remoterouteinfo(i);


        pIwfSigtranRemoteRouteConfig->set_remoteroutename(pOrginalIwfSigtranRemoteRouteConfig->remoteroutename());
        Fill_IWFSigtranRemoteRoute_protobuff(pIwfSigtranRemoteRouteConfig,resp);
        DLOG_DEBUG("pIwfSigtranRemoteRouteConfig = %s",pIwfSigtranRemoteRouteConfig->DebugString().c_str());
        IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig = pIwfSigtranRemoteRouteConfig->mutable_destinationinfo();
        Fill_IWFSigtranDestination_protobuff(pIwfSigtranDestinationConfig,resp);

        pIwfSigtranRemoteRouteConfig->set_oldpointcode(pOrginalIwfSigtranRemoteRouteConfig->oldpointcode());
        pIwfSigtranRemoteRouteConfig->set_oldnetworkindicator(pOrginalIwfSigtranRemoteRouteConfig->oldnetworkindicator());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

#endif

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranRemoteRoute_Fill_For_Destination(IwfSigtranRemoteRoutesConfig *pIwfSigtranRemoteRoutesConfig,IwfSigtranDestinationsConfig *pIwfSigtranDestinationsConfig,IWFCfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    int iReturn = IWF_DB_SUCCESS;
    int iCount = pIwfSigtranDestinationsConfig->destioninfo_size();

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig = pIwfSigtranDestinationsConfig->mutable_destioninfo(i);
        IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfig;
        IwfSigtranDestinationConfig *pLocalIwfSigtranDestinationConfig = LocalIwfSigtranRemoteRouteConfig.mutable_destinationinfo();

        pLocalIwfSigtranDestinationConfig->set_destinationname(pIwfSigtranDestinationConfig->destinationname());

        Fill_IWFSigtranDestination_protobuff(pLocalIwfSigtranDestinationConfig,resp);
        Fill_IWFSigtranRemoteRoute_protobuff(&LocalIwfSigtranRemoteRouteConfig,resp);

        IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig = pIwfSigtranRemoteRoutesConfig->add_remoterouteinfo();
        pIwfSigtranRemoteRouteConfig->CopyFrom(LocalIwfSigtranRemoteRouteConfig);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranDestination_Del_Config_Reqs(IwfSigtranDestinationsConfig *pIwfSigtranDestinationsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranDestinationsConfig->destioninfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(DEL_DESTINATION_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_DESTINATION_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig= pIwfSigtranDestinationsConfig->mutable_destioninfo(i);

        if((iReturn = mysql_IwfSigtranDestination_Del_Validation(pIwfSigtranDestinationConfig)) != IWF_DB_SUCCESS)
        {
            mysql_set_error_for_IWFSigtranDestination_Config_Reqs(pIwfSigtranDestinationConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        sql_IWFSigtranDestination_Create_Check_Modifcation_Query(pIwfSigtranDestinationConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_DESTINATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranDestination_Config_Reqs(pIwfSigtranDestinationConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Not Present");   
            mysql_set_error_for_IWFSigtranDestination_Config_Reqs(pIwfSigtranDestinationConfig,resp,DEL_DESTINATION_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_DESTINATION_ERR_NOT_PRESENT;
        }
        else // MOD
        {
            sql_IWFSigtranDestination_Create_Delete_Query(pIwfSigtranDestinationConfig,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_DESTINATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranDestination_Config_Reqs(pIwfSigtranDestinationConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranDestination_Mod_Config_Reqs(IwfSigtranDestinationsConfig *pIwfSigtranDestinationsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    int iSend = 0;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranDestinationsConfig->destioninfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(MOD_DESTINATION_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[MOD_DESTINATION_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig= pIwfSigtranDestinationsConfig->mutable_destioninfo(i);

        iReturn = mysql_IwfSigtranDestination_Mod_Validation(pIwfSigtranDestinationConfig);
        if(iReturn == IWF_DB_SUCCESS_SEND)
        {
            iSend = 1;
        }
        else if(iReturn == IWF_DB_SUCCESS)
        {
        }
        else
        {
            mysql_set_error_for_IWFSigtranDestination_Config_Reqs(pIwfSigtranDestinationConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        sql_IWFSigtranDestination_Create_Check_Modifcation_Query(pIwfSigtranDestinationConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_DESTINATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranDestination_Config_Reqs(pIwfSigtranDestinationConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Not Present");   
            mysql_set_error_for_IWFSigtranDestination_Config_Reqs(pIwfSigtranDestinationConfig,resp,MOD_DESTINATION_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_DESTINATION_ERR_NOT_PRESENT;

        }
        else // MOD
        {
            sql_IWFSigtranDestination_Create_Mod_Query(pIwfSigtranDestinationConfig,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_DESTINATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranDestination_Config_Reqs(pIwfSigtranDestinationConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }


    if(iSend)
        iReturn = IWF_DB_SUCCESS_SEND;

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranRemoteRoute_Validation(IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    {
        sql_IWFSigtranRemoteRoute_Create_Check_Modifcation_Query(pIwfSigtranRemoteRouteConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ROUTE_ERR_DB_ERROR;


            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0) // ADD
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ROUTE_ERR_ROUTE_ALREADY_PRESENT;
        }
        delete pRes;
    }

    {
        IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig = pIwfSigtranRemoteRouteConfig->mutable_destinationinfo();

        sql_IWFSigtranDestination_Create_Check_Modifcation_Query(pIwfSigtranDestinationConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ROUTE_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return  ADD_ROUTE_ERR_DESTINATION_NOT_PRESENT;
        }
        delete pRes;
    }

    {
        IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;

        LocalIwfSigtranAssociationSetConfigObj.set_associationsetname(pIwfSigtranRemoteRouteConfig->associationsetname());

        sql_IWFSigtranAssocSet_Create_Check_Modifcation_Query(&LocalIwfSigtranAssociationSetConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ROUTE_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return  ADD_ROUTE_ERR_ASSOCIATION_SET_NOT_PRESENT;
        }
        delete pRes;
    }
#if 0
    {
        IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig = pIwfSigtranRemoteRouteConfig->mutable_destinationinfo();
        IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfigObj;
        IwfSigtranDestinationConfig *pLocalIwfSigtranDestinationConfig = LocalIwfSigtranRemoteRouteConfigObj.mutable_destinationinfo();
        pLocalIwfSigtranDestinationConfig->set_destinationname(pIwfSigtranDestinationConfig->destinationname());

        sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ROUTE_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0) // ADD
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ROUTE_ERR_DESTINATION_ALREADY_USED_IN_ROUTE;
        }
        delete pRes;
    }
    {
        IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfigObj;
        LocalIwfSigtranRemoteRouteConfigObj.set_associationsetname(pIwfSigtranRemoteRouteConfig->associationsetname());

        sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ROUTE_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0) // ADD
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return  ADD_ROUTE_ERR_ASSOCIATION_SET_ALREADY_HAVE_ROUTE;
        }
        delete pRes;
    }
#endif
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranRemoteRoute_Add_Config_Reqs(IwfSigtranRemoteRoutesConfig *pIwfSigtranRemoteRoutesConfig,IWFCfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranRemoteRoutesConfig->remoterouteinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(ADD_ROUTE_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[ADD_ROUTE_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig= pIwfSigtranRemoteRoutesConfig->mutable_remoterouteinfo(i);

        if((iReturn = mysql_IwfSigtranRemoteRoute_Validation(pIwfSigtranRemoteRouteConfig)) != IWF_DB_SUCCESS)
        {
            mysql_set_error_for_IWFSigtranRemoteRoute_Config_Reqs(pIwfSigtranRemoteRouteConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

#if 0
        sql_IWFSigtranRemoteRoute_Create_Check_Modifcation_Query(pIwfSigtranRemoteRouteConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ROUTE_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranRemoteRoute_Config_Reqs(pIwfSigtranRemoteRouteConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
#endif    

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        sql_IWFSigtranRemoteRoute_Create_Add_Query(pIwfSigtranRemoteRouteConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_ROUTE_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranRemoteRoute_Config_Reqs(pIwfSigtranRemoteRouteConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        //This below method is call to fill AspId to pass to IWF
        Fill_IWFSigtranRemoteRoute_protobuff(pIwfSigtranRemoteRouteConfig,resp);

    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

#if 1

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranRemoteRoute_Del_Validation(IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);


    IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfigObj;
    //IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;
    LocalIwfSigtranRemoteRouteConfigObj.set_remoteroutename(pIwfSigtranRemoteRouteConfig->remoteroutename());

    sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfigObj,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = MOD_ROUTE_ERR_DB_ERROR;


        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);
    if(pRes->rowsCount() > 0) // ADD
    {
#if 0
        if(pRes->next())
        {
            if(pRes->isNull("IWF_SIGTRAN_ASSOC_SET_ID"))
            {
                LocalIwfSigtranAssociationSetConfigObj.set_associationsetid(pRes->getInt("IWF_SIGTRAN_ASSOC_SET_ID"));
            }
        }
#endif
    }
    else
    {
        delete pRes;
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DEL_ROUTE_ERR_ROUTE_NOT_PRESENT;
    }

    delete pRes;

    memset(sStatement,0,MAX_STATEMENT_SIZE);
#if 0
    LocalIwfSigtranAssociationSetConfigObj.set_status(true);

    sql_IWFSigtranAssocSet_Create_Select_Query(&LocalIwfSigtranAssociationSetConfigObj,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == IWF_DB_FAIL)
            iReturn = MOD_ROUTE_ERR_DB_ERROR;


        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() > 0) // ADD
    {
        delete pRes;
        DLOG_NONE(" < %s ",__FUNCTION__);
        return  DEL_ROUTE_ERR_ASSOCIATION_SET_IN_ACTIVE_STATE;
    }
    delete pRes;
#endif
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranRemoteRoute_Del_Config_Reqs(IwfSigtranRemoteRoutesConfig *pIwfSigtranRemoteRoutesConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranRemoteRoutesConfig->remoterouteinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(DEL_ROUTE_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[DEL_ROUTE_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig= pIwfSigtranRemoteRoutesConfig->mutable_remoterouteinfo(i);

        if((iReturn = mysql_IwfSigtranRemoteRoute_Del_Validation(pIwfSigtranRemoteRouteConfig)) != IWF_DB_SUCCESS)
        {
            mysql_set_error_for_IWFSigtranRemoteRoute_Config_Reqs(pIwfSigtranRemoteRouteConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        sql_IWFSigtranRemoteRoute_Create_Check_Modifcation_Query(pIwfSigtranRemoteRouteConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_ROUTE_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranRemoteRoute_Config_Reqs(pIwfSigtranRemoteRouteConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Not Present");   
            mysql_set_error_for_IWFSigtranRemoteRoute_Config_Reqs(pIwfSigtranRemoteRouteConfig,resp,DEL_ROUTE_ERR_ROUTE_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_ROUTE_ERR_ROUTE_NOT_PRESENT;
        }
        else // MOD
        {
            sql_IWFSigtranRemoteRoute_Create_Delete_Query(pIwfSigtranRemoteRouteConfig,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = DEL_ROUTE_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranRemoteRoute_Config_Reqs(pIwfSigtranRemoteRouteConfig,resp,iReturn);
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

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranRemoteRoute_Mod_Validation(IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG("pIwfSigtranRemoteRouteConfig = %s",pIwfSigtranRemoteRouteConfig->DebugString().c_str());

    {
        sql_IWFSigtranRemoteRoute_Create_Check_Modifcation_Query(pIwfSigtranRemoteRouteConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ROUTE_ERR_DB_ERROR;

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
            return MOD_ROUTE_ERR_ROUTE_NOT_PRESENT;
        }
        delete pRes;
    }
#if 0
    if(pIwfSigtranRemoteRouteConfig->has_associationsetname())
    {
        pRes = NULL;
        IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;

        LocalIwfSigtranAssociationSetConfigObj.set_associationsetname(pIwfSigtranRemoteRouteConfig->associationsetname());
        LocalIwfSigtranAssociationSetConfigObj.set_status(true);

        sql_IWFSigtranAssocSet_Create_Select_Query(&LocalIwfSigtranAssociationSetConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ROUTE_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0) // ADD
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return  MOD_ROUTE_ERR_ASSOCIATION_SET_IN_ACTIVE_STATE;
        }
        delete pRes;
    }

    if(pIwfSigtranRemoteRouteConfig->has_destinationinfo())
    {
        pRes = NULL;
        IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig = pIwfSigtranRemoteRouteConfig->mutable_destinationinfo();
        IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfigObj;
        IwfSigtranDestinationConfig *pLocalIwfSigtranDestinationConfig = LocalIwfSigtranRemoteRouteConfigObj.mutable_destinationinfo();
        pLocalIwfSigtranDestinationConfig->set_destinationname(pIwfSigtranDestinationConfig->destinationname());

        sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ROUTE_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0) // ADD
        {
            if(pRes->next())
            {
                if(pRes->getString("REMOTE_ROUTE_NAME") != pIwfSigtranRemoteRouteConfig->remoteroutename())
                {
                    delete pRes;
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_ROUTE_ERR_DESTINATION_ALREADY_USED_IN_ROUTE;
                }
            }
        }
        delete pRes;
    }
#endif

    if(pIwfSigtranRemoteRouteConfig->has_associationsetname())
    {
        pRes = NULL;
        IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfig;
        IWFCfgResp LocalResp;

        LocalIwfSigtranAssociationSetConfig.set_associationsetname(pIwfSigtranRemoteRouteConfig->associationsetname());
        Fill_IWFSigtranAssocSet_protobuff(&LocalIwfSigtranAssociationSetConfig,&LocalResp);

        IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfigObj;
        LocalIwfSigtranRemoteRouteConfigObj.set_associationsetname(LocalIwfSigtranAssociationSetConfig.associationsetname());

        sql_IWFSigtranRemoteRoute_Create_Select_Query(&LocalIwfSigtranRemoteRouteConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ROUTE_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() > 0) // ADD
        {
            if(pRes->next())
            {
                if(pRes->getString("REMOTE_ROUTE_NAME") != pIwfSigtranRemoteRouteConfig->remoteroutename())
                {
                    delete pRes;
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return  MOD_ROUTE_ERR_ASSOCIATION_SET_ALREADY_HAVE_ROUTE;
                }
            }
        }
        delete pRes;
    }


    if(pIwfSigtranRemoteRouteConfig->has_associationsetname())
    {
        pRes = NULL;
        IwfSigtranAssociationSetConfig LocalIwfSigtranAssociationSetConfigObj;

        LocalIwfSigtranAssociationSetConfigObj.set_associationsetname(pIwfSigtranRemoteRouteConfig->associationsetname());

        sql_IWFSigtranAssocSet_Create_Check_Modifcation_Query(&LocalIwfSigtranAssociationSetConfigObj,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ROUTE_ERR_DB_ERROR;


            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return  MOD_ROUTE_ERR_ASSOCIATION_SET_NOT_PRESENT;
        }
        delete pRes;
    }

    if(pIwfSigtranRemoteRouteConfig->has_destinationinfo())
    {
        pRes = NULL;
        IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig = pIwfSigtranRemoteRouteConfig->mutable_destinationinfo();

        sql_IWFSigtranDestination_Create_Check_Modifcation_Query(pIwfSigtranDestinationConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ROUTE_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return  MOD_ROUTE_ERR_DESTINATION_NOT_PRESENT;
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranRemoteRoute_Mod_Config_Reqs(IwfSigtranRemoteRoutesConfig *pIwfSigtranRemoteRoutesConfig,IWFCfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranRemoteRoutesConfig->remoterouteinfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(MOD_ROUTE_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[MOD_ROUTE_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig= pIwfSigtranRemoteRoutesConfig->mutable_remoterouteinfo(i);

        if((iReturn = mysql_IwfSigtranRemoteRoute_Mod_Validation(pIwfSigtranRemoteRouteConfig)) != IWF_DB_SUCCESS)
        {
            mysql_set_error_for_IWFSigtranRemoteRoute_Config_Reqs(pIwfSigtranRemoteRouteConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        IwfSigtranRemoteRouteConfig LocalIwfSigtranRemoteRouteConfigObj;
        LocalIwfSigtranRemoteRouteConfigObj.set_remoteroutename(pIwfSigtranRemoteRouteConfig->remoteroutename());
        Fill_IWFSigtranRemoteRoute_protobuff(&LocalIwfSigtranRemoteRouteConfigObj,resp);

        IwfSigtranDestinationConfig *pLocalIwfSigtranDestinationConfig = LocalIwfSigtranRemoteRouteConfigObj.mutable_destinationinfo();
        Fill_IWFSigtranDestination_protobuff(pLocalIwfSigtranDestinationConfig,resp);

        sql_IWFSigtranRemoteRoute_Create_Mod_Query(pIwfSigtranRemoteRouteConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = MOD_ROUTE_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranRemoteRoute_Config_Reqs(pIwfSigtranRemoteRouteConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        pIwfSigtranRemoteRouteConfig->set_oldpointcode(pLocalIwfSigtranDestinationConfig->pointcode());
        pIwfSigtranRemoteRouteConfig->set_oldnetworkindicator(pLocalIwfSigtranDestinationConfig->networkindicator());
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrIwfDbInterface::mysql_IwfSigtranDestination_Add_Config_Reqs(IwfSigtranDestinationsConfig *pIwfSigtranDestinationsConfig,IWFCfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  IWF_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pIwfSigtranDestinationsConfig->destioninfo_size();
    if(iCount == 0)
    {
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(ADD_DESTINATION_ERR_DATA_NOT_SET);
        err->set_errormsgkey(iwfErrorMap[ADD_DESTINATION_ERR_DATA_NOT_SET]);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return IWF_DB_FAIL;
    }

    for(int i=0;i<iCount;i++)
    {
        IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig= pIwfSigtranDestinationsConfig->mutable_destioninfo(i);
        sql_IWFSigtranDestination_Create_Check_Modifcation_Query(pIwfSigtranDestinationConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != IWF_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_DESTINATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranDestination_Config_Reqs(pIwfSigtranDestinationConfig,resp,iReturn);

            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_IWFSigtranDestination_Create_Add_Query(pIwfSigtranDestinationConfig,sStatement);
        }
        else // MOD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present");   
            mysql_set_error_for_IWFSigtranDestination_Config_Reqs(pIwfSigtranDestinationConfig,resp,ADD_DESTINATION_ERR_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_DESTINATION_ERR_ALREADY_PRESENT;
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != IWF_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == IWF_DB_FAIL)
                iReturn = ADD_DESTINATION_ERR_DB_ERROR;

            mysql_set_error_for_IWFSigtranDestination_Config_Reqs(pIwfSigtranDestinationConfig,resp,iReturn);
            DLOG_DEBUG("iReturn = %d",iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    DLOG_DEBUG("iReturn = %d",iReturn);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

