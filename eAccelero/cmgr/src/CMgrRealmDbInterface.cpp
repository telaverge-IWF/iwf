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

#include "CMgrDbInterface.h"

using namespace std;
extern std::map<int,std::string> errorMap;

void CMgrDbInterface::mysql_set_error_for_Realm_Config_Reqs(RealmConfig *pRealmConfig, DRECfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pRealmConfig->has_realmname())
        err->add_variables(pRealmConfig->realmname());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_RealmRouting_Config_Reqs(RealmConfig *pRealmConfig, DRECfgResp *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ::Destination* localDestinationObj;
    if(iIndex != -1)
        localDestinationObj = pRealmConfig->mutable_destinfo(iIndex);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(iIndex != -1)
    {
        if(localDestinationObj->has_applicationid())
        {
            char sApplicationID[10];
            snprintf(sApplicationID,10,"%d",localDestinationObj->applicationid());
            err->add_variables(sApplicationID);
        }

        if(localDestinationObj->has_peername())
            err->add_variables(localDestinationObj->peername());
    }

    if(pRealmConfig->has_realmname())
        err->add_variables(pRealmConfig->realmname());


    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_Realm_Get_Config_Reqs(RealmsConfig *pRealmsConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);
    int iCount = pRealmsConfig->realms_size();

    DLOG_DEBUG(" %s: realms_size  = %d ",__FUNCTION__,iCount);
    for(int i=0; i<iCount; i++)
    {
        ::RealmConfig* localRealmConfig = pRealmsConfig->mutable_realms(i);

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        pRes = NULL;
        sql_RealmTRealmRoutingAndDefaultRoute_Create_Select_Query(localRealmConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_REALM_ERR_DB_ERROR;

            mysql_set_error_for_Realm_Config_Reqs(localRealmConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_realm_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            if(iReturn == GET_REALM_ERR_NO_DATA_PRESENT)
                iReturn = GET_REALM_ERR_NO_REALM_PRESENT;
            mysql_set_error_for_Realm_Config_Reqs(localRealmConfig,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;
    }

    ::RealmConfig lRealmConfig;
    if(iCount == 0)
    {
        pRes = NULL;
        sql_RealmTRealmRoutingAndDefaultRoute_Create_Select_Query(&lRealmConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_REALM_ERR_DB_ERROR;

            mysql_set_error_for_Realm_Config_Reqs(&lRealmConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            if((iReturn = mysql_realm_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
            {
                mysql_set_error_for_Realm_Config_Reqs(&lRealmConfig,resp,iReturn);
                delete pRes;
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            delete pRes;
        }
    }

    mysql_DefaultRoute_Get_Config_Reqs_Through_Realm(&lRealmConfig,resp);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}


#if 1
DbStatus_e CMgrDbInterface::mysql_RealmRouting_Get_Config_Reqs(RealmsConfig *pRealmsConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);
    int iCount = pRealmsConfig->realms_size();
    DLOG_DEBUG(" %s: realms_size  = %d ",__FUNCTION__,iCount);


    for(int i=0; i<iCount; i++)
    {
        ::RealmConfig* localRealmConfig = pRealmsConfig->mutable_realms(i);

        int iDestinationCount = localRealmConfig->destinfo_size();
        DLOG_DEBUG(" %s: destinfo_size = %d ",__FUNCTION__,iDestinationCount);

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        for(int j=0; j<iDestinationCount; j++)
        {
            pRes = NULL;
            sql_RealmRouting_Create_Select_Query(localRealmConfig,sStatement,j);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_DEST_ERR_DB_ERROR;

                mysql_set_error_for_RealmRouting_Config_Reqs(localRealmConfig,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_realmrouting_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
            {
                delete pRes;
                mysql_set_error_for_RealmRouting_Config_Reqs(localRealmConfig,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            delete pRes;
        }

        if(iDestinationCount == 0)
        {

            pRes = NULL;
            sql_RealmRouting_Create_Select_Query(localRealmConfig,sStatement,0);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_DEST_ERR_DB_ERROR;

                mysql_set_error_for_RealmRouting_Config_Reqs(localRealmConfig,resp,iReturn,-1);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_realmrouting_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
            {
                delete pRes;
                mysql_set_error_for_RealmRouting_Config_Reqs(localRealmConfig,resp,iReturn,-1);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            delete pRes;

        }
    }

    if(iCount == 0)
    {
        pRes = NULL;
        ::RealmConfig lRealmConfig;
        sql_RealmRouting_Create_Select_Query(&lRealmConfig,sStatement,0);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_DEST_ERR_DB_ERROR;

            mysql_set_error_for_RealmRouting_Config_Reqs(&lRealmConfig,resp,iReturn,-1);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        else
        {
            if((iReturn = mysql_realmrouting_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
            {
                mysql_set_error_for_RealmRouting_Config_Reqs(&lRealmConfig,resp,iReturn,-1);
                delete pRes;
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            delete pRes;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}
#endif


DbStatus_e CMgrDbInterface::mysql_realmrouting_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);


    try
    {

        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_DEST_ERR_NO_DATA_PRESENT;
        }


        while(pRes->next())
        {
            mysql_check_and_Add_realmrouting_resultset(pRes,resp);
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



DbStatus_e CMgrDbInterface::mysql_realm_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);


    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_REALM_ERR_NO_DATA_PRESENT;
        }


        while(pRes->next())
        {
            mysql_check_and_Add_realm_resultset(pRes,resp);
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

#if 0

void CMgrDbInterface::mysql_check_and_Add_realm_resultset(sql::ResultSet *pRes,DRECfgResp *resp)
{
    ::RealmsConfig* localRealmsObj;

    DLOG_NONE(" > %s ",__FUNCTION__);

    localRealmsObj = resp->mutable_realms();

    int iRealmCount = localRealmsObj->realms_size();
    for(int j=0; j<iRealmCount; j++)
    {
        ::RealmConfig* localRealmObj = localRealmsObj->mutable_realms(j);

        // Assuming that all this variable will be there

        if(localRealmObj->realmname() == pRes->getString("RealmRoutingTRealmName") &&
                localRealmObj->redirecthostusage() == (unsigned int)pRes->getInt("RedirectHostUsage") &&
                localRealmObj->redirectmaxcachetime() == (unsigned int)(pRes->getInt("RedirectMaxCacheTime")))
        {

            mysql_add_realm_resultset_to_DestinationProtoBuff(pRes,localRealmObj);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return;
        }
    }

    mysql_add_realm_resultset_to_RealmProtoBuff(pRes,localRealmsObj);

    DLOG_NONE(" < %s ",__FUNCTION__);
}

#endif

void CMgrDbInterface::mysql_check_and_Add_realmrouting_resultset(sql::ResultSet *pRes,DRECfgResp *resp)
{
    ::RealmsConfig* localRealmsObj;

    DLOG_NONE(" > %s ",__FUNCTION__);

    localRealmsObj = resp->mutable_realms();

    int iRealmCount = localRealmsObj->realms_size();
    DLOG_DEBUG(" %s: realms_size = %d ",__FUNCTION__,iRealmCount);
    for(int j=0; j<iRealmCount; j++)
    {
        ::RealmConfig* localRealmObj = localRealmsObj->mutable_realms(j);

        // Assuming that all this variable will be there

        if(localRealmObj->realmname() == pRes->getString("REALM_NAME"))
        {

            mysql_add_realmrouting_resultset_to_DestinationProtoBuff(pRes,localRealmObj);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return;
        }
    }

    mysql_add_realmrouting_resultset_to_RealmProtoBuff(pRes,localRealmsObj);

    DLOG_NONE(" < %s ",__FUNCTION__);
}

#if 1

void CMgrDbInterface::mysql_check_and_Add_realm_resultset(sql::ResultSet *pRes,DRECfgResp *resp)
{
    ::RealmsConfig* localRealmsObj;

    DLOG_NONE(" > %s ",__FUNCTION__);

    localRealmsObj = resp->mutable_realms();

    int iRealmCount = localRealmsObj->realms_size();
    DLOG_DEBUG(" %s: realms_size = %d ",__FUNCTION__,iRealmCount);
    for(int j=0; j<iRealmCount; j++)
    {
        ::RealmConfig* localRealmObj = localRealmsObj->mutable_realms(j);

        // Assuming that all this variable will be there

        if(localRealmObj->realmname() == pRes->getString("RealmRoutingTRealmName"))
        {

            mysql_add_realm_resultset_to_DestinationProtoBuff(pRes,localRealmObj);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return;
        }
    }

    mysql_add_realm_resultset_to_RealmProtoBuff(pRes,localRealmsObj);

    DLOG_NONE(" < %s ",__FUNCTION__);
}

#endif

DbStatus_e CMgrDbInterface::mysql_add_realmrouting_resultset_to_DestinationProtoBuff(sql::ResultSet *pRes,RealmConfig* localRealmObj)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pRes->isNull("APP_ID"))
    {
        DLOG_DEBUG("Application ID is Null ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_SUCCESS;
    }

    ::Destination* localDestionationObj = localRealmObj->add_destinfo();

    if(!pRes->isNull("PeerHostIdentity"))
        localDestionationObj->set_peername(pRes->getString("PeerHostIdentity"));
    if(!pRes->isNull("RealmName"))
        localDestionationObj->set_realmname(pRes->getString("RealmName"));
    if(!pRes->isNull("APP_ID"))
        localDestionationObj->set_applicationid(pRes->getInt64("APP_ID"));
    if(!pRes->isNull("VENDOR_ID"))
        localDestionationObj->set_vendorid(pRes->getInt64("VENDOR_ID"));
    if(!pRes->isNull("PRIORITY"))
        localDestionationObj->set_priority(pRes->getInt64("PRIORITY"));
    if(!pRes->isNull("PEER_ID"))
        localDestionationObj->set_peerid(pRes->getInt64("PEER_ID"));
    if(!pRes->isNull("DYNAMICALLY_DISCOVERED"))
        localDestionationObj->set_dynamicallydiscovered(pRes->getInt64("DYNAMICALLY_DISCOVERED"));
    if(!pRes->isNull("DYN_DISCOVERY_EXPIRY"))
        localDestionationObj->set_dyndiscoveryexpiry(pRes->getInt64("DYN_DISCOVERY_EXPIRY"));


    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}



DbStatus_e CMgrDbInterface::mysql_add_realm_resultset_to_DestinationProtoBuff(sql::ResultSet *pRes,RealmConfig* localRealmObj)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pRes->isNull("APP_ID"))
    {
        DLOG_DEBUG("Application ID is Null ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_SUCCESS;
    }

    ::Destination* localDestionationObj = localRealmObj->add_destinfo();

    if(!pRes->isNull("RealmRoutingTPeerHostIdentity"))
        localDestionationObj->set_peername(pRes->getString("RealmRoutingTPeerHostIdentity"));
    if(!pRes->isNull("AssociateRealmName"))
        localDestionationObj->set_realmname(pRes->getString("AssociateRealmName"));
    if(!pRes->isNull("APP_ID"))
        localDestionationObj->set_applicationid(pRes->getInt64("APP_ID"));
    if(!pRes->isNull("VENDOR_ID"))
        localDestionationObj->set_vendorid(pRes->getInt64("VENDOR_ID"));
    if(!pRes->isNull("PRIORITY"))
        localDestionationObj->set_priority(pRes->getInt64("PRIORITY"));
    if(!pRes->isNull("PEER_ID"))
        localDestionationObj->set_peerid(pRes->getInt64("PEER_ID"));
    if(!pRes->isNull("DYNAMICALLY_DISCOVERED"))
        localDestionationObj->set_dynamicallydiscovered(pRes->getInt64("DYNAMICALLY_DISCOVERED"));
    if(!pRes->isNull("DYN_DISCOVERY_EXPIRY"))
        localDestionationObj->set_dyndiscoveryexpiry(pRes->getInt64("DYN_DISCOVERY_EXPIRY"));


    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_add_realmrouting_resultset_to_RealmProtoBuff(sql::ResultSet *pRes,RealmsConfig* localRealmsObj)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ::RealmConfig* localRealmObj = localRealmsObj->add_realms();

    if(!pRes->isNull("REALM_NAME"))
        localRealmObj->set_realmname(pRes->getString("REALM_NAME"));
    if(!pRes->isNull("REDIRECT_HOST_USAGE"))
        localRealmObj->set_redirecthostusage(pRes->getInt("REDIRECT_HOST_USAGE"));
    if(!pRes->isNull("REDIRECT_MAX_CACHE_TIME"))
        localRealmObj->set_redirectmaxcachetime(pRes->getInt("REDIRECT_MAX_CACHE_TIME"));

    if(!pRes->isNull("LOCAL_ACTION"))
    {
        if(pRes->getInt("LOCAL_ACTION") == 1)
            localRealmObj->set_localaction("Local");
        else if(pRes->getInt("LOCAL_ACTION") == 2)
            localRealmObj->set_localaction("Relay");
        else if(pRes->getInt("LOCAL_ACTION") == 3)
            localRealmObj->set_localaction("Proxy");
        else
            localRealmObj->set_localaction("Redirect");
    }


    mysql_add_realmrouting_resultset_to_DestinationProtoBuff(pRes,localRealmObj);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

#if 1
DbStatus_e CMgrDbInterface::mysql_add_realm_resultset_to_RealmProtoBuff(sql::ResultSet *pRes,RealmsConfig* localRealmsObj)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    ::RealmConfig* localRealmObj = localRealmsObj->add_realms();

    if(!pRes->isNull("RealmRoutingTRealmName"))
        localRealmObj->set_realmname(pRes->getString("RealmRoutingTRealmName"));
    if(!pRes->isNull("REDIRECT_HOST_USAGE"))
        localRealmObj->set_redirecthostusage(pRes->getInt("REDIRECT_HOST_USAGE"));
    if(!pRes->isNull("REDIRECT_MAX_CACHE_TIME"))
        localRealmObj->set_redirectmaxcachetime(pRes->getInt("REDIRECT_MAX_CACHE_TIME"));
    if(!pRes->isNull("PROXY_INFO_AVP"))
        localRealmObj->set_enableproxyinfoavp(pRes->getInt("PROXY_INFO_AVP"));

    if(!pRes->isNull("LOCAL_ACTION"))
    {
        if(pRes->getInt("LOCAL_ACTION") == 1)
            localRealmObj->set_localaction("Local");
        else if(pRes->getInt("LOCAL_ACTION") == 2)
            localRealmObj->set_localaction("Relay");
        else if(pRes->getInt("LOCAL_ACTION") == 3)
            localRealmObj->set_localaction("Proxy");
        else
            localRealmObj->set_localaction("Redirect");
    }



    mysql_add_realm_resultset_to_DestinationProtoBuff(pRes,localRealmObj);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}
#endif

#if 0
DbStatus_e CMgrDbInterface::mysql_add_realm_resultset_to_RealmProtoBuff(sql::ResultSet *pRes,RealmsConfig* localRealmsObj)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ::RealmConfig* localRealmObj = localRealmsObj->add_realms();

    localRealmObj->set_realmname(pRes->getString("RealmRoutingTRealmName"));

    mysql_add_realm_resultset_to_DestinationProtoBuff(pRes,localRealmObj);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

#endif

DbStatus_e CMgrDbInterface::mysql_DefaultRoute_Get_Config_Reqs_Through_Realm(RealmsConfig *pRealmsConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    RealmConfig *pRealmConfig;
    RealmConfig lRealmConfig;

    DLOG_DEBUG(" %s: realms_size = %d ",__FUNCTION__,pRealmsConfig->realms_size());
    if(pRealmsConfig->realms_size() < 0)
    {
        pRealmConfig = pRealmsConfig->mutable_realms(0);
    }
    else
    {
        pRealmConfig = &lRealmConfig;
    }

    int iDestinationCount = pRealmConfig->destinfo_size();
    DLOG_DEBUG(" %s: destinfo_size = %d ",__FUNCTION__,iDestinationCount);


    for(int j=0; j<iDestinationCount; j++)
    {

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        sql_DefaultRoute_Create_Select_Query(pRealmConfig,sStatement,j);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_DEFROUTE_ERR_DB_ERROR;

            mysql_set_error_for_Realm_Config_Reqs(pRealmConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        //mysql_defaultRoute_resultset_to_protoBuff(pRes,resp);
        if((iReturn = mysql_DefaultRoute_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Realm_Config_Reqs(pRealmConfig,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;
    }

    if(iDestinationCount == 0)
    {
        sql_DefaultRoute_Create_Select_Query(pRealmConfig,sStatement,0);

        if((iReturn =  m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_DEFROUTE_ERR_DB_ERROR;

            mysql_set_error_for_Realm_Config_Reqs(pRealmConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        //mysql_defaultRoute_resultset_to_protoBuff(pRes,resp);
        if((iReturn = mysql_DefaultRoute_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;
            mysql_set_error_for_Realm_Config_Reqs(pRealmConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_DefaultRoute_resultset_to_protoBuff(sql::ResultSet *pResDefaultR,DRECfgResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pResDefaultR->rowsCount());
        if(pResDefaultR->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_DEFROUTE_ERR_NO_DATA_PRESENT;
        }

        ::RealmsConfig* localRealmsObj = resp->mutable_realms();
        //::RealmConfig* localRealmObj = localRealmsObj->add_realms();
        ::RealmConfig* localRealmObj = NULL;

        while(pResDefaultR->next())
        {
            int iCount = localRealmsObj->realms_size();
            for(int i=0;i<iCount;i++)
            {
                localRealmObj = localRealmsObj->mutable_realms(i);
                if(pResDefaultR->getString("REALM_NAME") == localRealmObj->realmname())
                {
                    break;
                }
                localRealmObj = NULL;
            }

            if(!localRealmObj)
            {
                localRealmObj = localRealmsObj->add_realms();
            }

            localRealmObj->set_realmname(pResDefaultR->getString("REALM_NAME"));
            localRealmObj->set_defaultroute(pResDefaultR->getString("PeerHostIdentity"));
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

DbStatus_e CMgrDbInterface::mysql_Realm_Add_Config_Reqs(RealmConfig *pRealmConfig,DRECfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);


    if((iReturn = sql_Realm_Payload_Validation(pRealmConfig)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Realm Payload validation Failed ",__LINE__);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    sql_Realm_Create_Check_Modifcation_Query(pRealmConfig,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_REALM_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_Realm_Create_Add_Query(pRealmConfig,sStatement);
    }
    else // MOD
    {
        delete pRes;
        DLOG_ERROR("Record Already Present");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return SET_REALM_ERR_REALM_ALREADY_ADDED;
    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_REALM_ERR_DB_ERROR;

        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_RealmRouting_Add_validation(::RealmConfig* pRealmConfig,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::Destination* localDestinationObj = NULL;

    if(pRealmConfig->destinfo_size() > iIndex && iIndex > -1)
    {
        localDestinationObj = pRealmConfig->mutable_destinfo(iIndex);
    }

    if(pRealmConfig->has_realmname())
    {
        sql_RealmRouting_Create_Validation_Query_for_Realm(pRealmConfig,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = SET_DEST_ERR_REALM_NOT_PRESENT;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);
    if(pRealmConfig->destinfo_size() && localDestinationObj->has_peername())
    {
        sql_RealmRouting_Create_Validation_Query_for_Peer(pRealmConfig,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = SET_DEST_ERR_PEER_NOT_PRESENT;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}


#if 1
DbStatus_e CMgrDbInterface::mysql_RealmRouting_Add_Config_Reqs(RealmConfig *pRealmConfig,int iDestinationIndex,DRECfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);


    if((iReturn = mysql_RealmRouting_Add_validation(pRealmConfig,iDestinationIndex)) != DRE_DB_SUCCESS)
    {
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if((iReturn = sql_RealmRouting_Payload_Validation(pRealmConfig,iDestinationIndex)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Realm Payload validation Failed");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    sql_RealmRouting_Create_Check_Modifcation_Query(pRealmConfig,sStatement,iDestinationIndex);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_DEST_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_RealmRouting_Create_Add_Query(pRealmConfig,sStatement,iDestinationIndex);
    }
    else // MOD
    {
        delete pRes;
        DLOG_ERROR("Record Already Present");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return SET_DEST_ERR_DEST_ALREADY_EXISTS;
    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);
        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_DEST_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}
#endif

DbStatus_e CMgrDbInterface::mysql_Realm_Mod_Config_Reqs(RealmConfig *pRealmConfig,DRECfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_FAIL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    if((iReturn = sql_Realm_Payload_Validation(pRealmConfig)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR(" Realm Payload validation Failed ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }


    if(sql_Realm_Check_All_Invalid(pRealmConfig) == DRE_DB_SUCCESS)
    {
        DLOG_NONE("Only Primary Key is set the Request ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return MOD_REALM_ERR_NO_PARAMS_PASSED;
    }



    sql_Realm_Create_Check_Modifcation_Query(pRealmConfig,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = MOD_REALM_ERR_DB_ERROR;

        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        delete pRes;
        DLOG_ERROR("Record is not present ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return MOD_REALM_ERR_REALM_IS_NOT_PRESENT;

    }
    else // MOD
    {
        sql_Realm_Create_Mod_Query(pRealmConfig,sStatement);
    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" <  \n",__FUNCTION__,__LINE__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = MOD_REALM_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_RealmRouting_Mod_validation(::RealmConfig* pRealmConfig,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::Destination* localDestinationObj = NULL;

    if(pRealmConfig->destinfo_size() > iIndex && iIndex > -1)
    {
        localDestinationObj = pRealmConfig->mutable_destinfo(iIndex);
    }

    if(pRealmConfig->has_realmname())
    {
        sql_RealmRouting_Create_Validation_Query_for_Realm(pRealmConfig,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_DEST_ERR_REALM_NOT_PRESENT;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);
    if(pRealmConfig->destinfo_size() && localDestinationObj->has_peername())
    {
        sql_RealmRouting_Create_Validation_Query_for_Peer(pRealmConfig,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_DEST_ERR_PEER_NOT_PRESENT;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}


#if 1
DbStatus_e CMgrDbInterface::mysql_RealmRouting_Mod_Config_Reqs(RealmConfig *pRealmConfig,int iDestinationIndex,DRECfgResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_FAIL;

    DLOG_NONE(" > %s ",__FUNCTION__);


    if((iReturn = mysql_RealmRouting_Mod_validation(pRealmConfig,iDestinationIndex)) != DRE_DB_SUCCESS)
    {
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if((iReturn = sql_RealmRouting_Payload_Validation(pRealmConfig,iDestinationIndex)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Realm Payload validation Failed ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if(sql_RealmRouting_Check_All_Invalid(pRealmConfig,iDestinationIndex) == DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Only Primary Key is set in Request ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return MOD_DEST_ERR_NO_PARAMS_PASSED;
    }



    sql_RealmRouting_Create_Check_Modifcation_Query(pRealmConfig,sStatement,iDestinationIndex);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = MOD_DEST_ERR_DB_ERROR;

        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        delete pRes;
        DLOG_ERROR("Record is not present ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return MOD_DEST_ERR_DEST_TO_MODIFY_NOT_PRESENT;

    }
    else // MOD
    {
        sql_RealmRouting_Create_Mod_Query(pRealmConfig,sStatement,iDestinationIndex);
    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = MOD_DEST_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

#endif

DbStatus_e CMgrDbInterface::mysql_DefaultRoute_Add_validation(RealmConfig *pRealmConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if(pRealmConfig->has_realmname())
    {
        sql_DefaultRoute_Create_Validation_Query_for_Realm(pRealmConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = SET_DEFROUTE_ERR_REALM_NOT_PRESENT;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);
    if(pRealmConfig->has_defaultroute())
    {
        sql_DefaultRoute_Create_Validation_Query_for_Peer(pRealmConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = SET_DEFROUTE_ERR_PEER_NOT_PRESENT;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_DefaultRoute_Add_Config_Reqs_Through_Realm(RealmConfig *pRealmConfig, int iDestinationIndex)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_FAIL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    if((iReturn = mysql_DefaultRoute_Add_validation(pRealmConfig)) != DRE_DB_SUCCESS)
    {
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if((iReturn = sql_DefaultRoute_Payload_Validation(pRealmConfig,iDestinationIndex)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Realm Payload validation Failed");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    sql_DefaultRoute_Create_Check_Modifcation_Query(pRealmConfig,sStatement,iDestinationIndex);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_DEFROUTE_ERR_DB_ERROR;

        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_DefaultRoute_Create_Add_Query(pRealmConfig,sStatement,iDestinationIndex);
    }
    else // MOD
    {
        delete pRes;
        DLOG_ERROR("Record Already Present");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return SET_DEFROUTE_ERR_REALM_DEST_ALREADY_EXISTS;

    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_NONE(" < %s ",__FUNCTION__);
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_DEFROUTE_ERR_DB_ERROR;

        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);

    return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_DefaultRoute_Get_Config_Reqs_Through_Realm(RealmConfig *pRealmConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

#if 0
    RealmConfig *pRealmConfig;
    RealmConfig lRealmConfig;

    if(pRealmsConfig->realms_size() < 0)
    {
        pRealmConfig = pRealmsConfig->mutable_realms(0);
    }
    else
    {
        pRealmConfig = &lRealmConfig;
    }

#endif
    int iDestinationCount = pRealmConfig->destinfo_size();
    DLOG_DEBUG(" %s: destinfo_size = %d ",__FUNCTION__,iDestinationCount);


    for(int j=0; j<iDestinationCount; j++)
    {

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        pRes = NULL;
        sql_DefaultRoute_Create_Select_Query(pRealmConfig,sStatement,j);

        if ((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_DEFROUTE_ERR_DB_ERROR;

            mysql_set_error_for_Realm_Config_Reqs(pRealmConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        //mysql_defaultRoute_resultset_to_protoBuff(pRes,resp);
        if((iReturn = mysql_DefaultRoute_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;
            mysql_set_error_for_Realm_Config_Reqs(pRealmConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;
    }

    if(iDestinationCount == 0)
    {
        sql_DefaultRoute_Create_Select_Query(pRealmConfig,sStatement,0);

        if ((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_DEFROUTE_ERR_DB_ERROR;

            mysql_set_error_for_Realm_Config_Reqs(pRealmConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        //mysql_defaultRoute_resultset_to_protoBuff(pRes,resp);
        if((iReturn = mysql_DefaultRoute_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Realm_Config_Reqs(pRealmConfig,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_DefaultRoute_Delete_Config_Reqs_Through_Realm(RealmConfig *req,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    sql_DefaultRoute_Create_Check_Modifcation_Query(req,sStatement,0);
    pRes=NULL;
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = DEL_DEFROUTE_ERR_DB_ERROR;

        mysql_set_error_for_Realm_Config_Reqs(req,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        delete pRes;
        mysql_set_error_for_Realm_Config_Reqs(req,resp,DEL_DEFROUTE_ERR_DEF_ROUTE_NOT_PRESENT);
        DLOG_NONE(" < %s ",__FUNCTION__);
        DLOG_ERROR("Record is not present ");
        return DEL_DEFROUTE_ERR_DEF_ROUTE_NOT_PRESENT;
    }
    else
    {

        delete pRes;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_DefaultRoute_Create_Delete_Query(req,sStatement,0);
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_DEFROUTE_ERR_DB_ERROR;

            mysql_set_error_for_Realm_Config_Reqs(req,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::copy_DefaultRoute(RealmConfig *req,DRECfgResp  *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);


    ::RealmConfig lRealmConfig;
    lRealmConfig.MergeFrom(*req);
    req->CopyFrom(lRealmConfig);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Realm_Delete_Config_Reqs(RealmsConfig *pRealmsConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE];

    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pRealmsConfig->realms_size();
    DLOG_DEBUG(" %s: realms_size = %d ",__FUNCTION__,iCount);

    for(int i=0; i<iCount; i++)
    {
        ::RealmConfig* localRealmConfig = pRealmsConfig->mutable_realms(i);

        sql_Realm_Create_Check_Modifcation_Query(localRealmConfig,sStatement);
        pRes = NULL;
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_REALM_ERR_DB_ERROR;

            mysql_set_error_for_Realm_Config_Reqs(localRealmConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            mysql_set_error_for_Realm_Config_Reqs(localRealmConfig,resp,DEL_REALM_ERR_REALM_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            DLOG_ERROR("Record is not present ");
            return DEL_REALM_ERR_REALM_NOT_PRESENT;
        }
        else
        {
            delete pRes;
            pRes = NULL;
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            IwfDccaDestConfig pLocalIwfDccaDestConfig;
            pLocalIwfDccaDestConfig.set_destname(localRealmConfig->realmname());
            m_IwfQueryPB->sql_DccaEndPoint_Create_Select_Query(&pLocalIwfDccaDestConfig,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(pRes!=NULL)
                {
                    delete pRes;
                }

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_REALM_ERR_DB_ERROR;

                mysql_set_error_for_Realm_Config_Reqs(localRealmConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;

            }
            else
            {
                if(pRes->rowsCount() > 0)
                {
                    delete pRes;
                    DLOG_ERROR("Realm is present in DCCA table.Hence not allowed to delete");
                    mysql_set_error_for_Realm_Config_Reqs(localRealmConfig,resp,DEL_REALM_ERR_PART_OF_DCCA_CONFIG);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return DEL_REALM_ERR_PART_OF_DCCA_CONFIG;
                }
            }
            delete pRes;
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            // Validate - if this realm is part of translator rule
            {
                IwfTranslatorRuleConfig lIwfTranslatorRuleConfigReq;
                lIwfTranslatorRuleConfigReq.set_destinationname(localRealmConfig->realmname());
                m_IwfQueryPB->sql_IWFTranslatorRule_Create_Select_Query(&lIwfTranslatorRuleConfigReq, sStatement);
                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {
                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                    if(pRes!=NULL)
                    {
                        delete pRes;
                    }

                    if(iReturn == DRE_DB_FAIL)
                        iReturn = DEL_REALM_ERR_DB_ERROR;

                    mysql_set_error_for_Realm_Config_Reqs(localRealmConfig,resp,iReturn);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;

                }
                if(pRes->rowsCount() > 0)
                {
                    delete pRes;
                    DLOG_ERROR("Realm is present in Translator rule table.Hence not allowed to delete");
                    mysql_set_error_for_Realm_Config_Reqs(localRealmConfig,resp,DEL_REALM_ERR_PART_OF_TRANSLATOR_RULE_CONFIG);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return DEL_REALM_ERR_PART_OF_TRANSLATOR_RULE_CONFIG;
                }
                delete pRes;
                pRes = NULL;
                memset(sStatement,0,MAX_STATEMENT_SIZE);
            }

            sql_Realm_Create_Delete_Query(localRealmConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_REALM_ERR_DB_ERROR;

                mysql_set_error_for_Realm_Config_Reqs(localRealmConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_RealmRouting_Delete_validation(::RealmConfig* pRealmConfig,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::Destination* localDestinationObj = NULL;

    if(pRealmConfig->destinfo_size() > iIndex && iIndex > -1)
    {
        localDestinationObj = pRealmConfig->mutable_destinfo(iIndex);
    }

    if(pRealmConfig->has_realmname())
    {
        sql_RealmRouting_Create_Validation_Query_for_Realm(pRealmConfig,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_DEST_ERR_REALM_NOT_PRESENT;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);
    if(pRealmConfig->destinfo_size() && localDestinationObj->has_peername())
    {
        sql_RealmRouting_Create_Validation_Query_for_Peer(pRealmConfig,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_DEST_ERR_PEER_NOT_PRESENT;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}


#if 1
DbStatus_e CMgrDbInterface::mysql_RealmRouting_Delete_Config_Reqs(RealmsConfig *pRealmsConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE];
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pRealmsConfig->realms_size();
    DLOG_DEBUG(" %s: realms_size = %d ",__FUNCTION__,iCount);

    for(int i=0; i<iCount; i++)
    {
        ::RealmConfig* localRealmConfig = pRealmsConfig->mutable_realms(i);

        int iDestinationCount = localRealmConfig->destinfo_size();
        DLOG_DEBUG(" %s: destinfo_size = %d ",__FUNCTION__,iDestinationCount);

        for(int j=0; j<iDestinationCount; j++)
        {

            if((iReturn = mysql_RealmRouting_Delete_validation(localRealmConfig,j)) != DRE_DB_SUCCESS)
            {
                mysql_set_error_for_RealmRouting_Config_Reqs(localRealmConfig,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }


            sql_RealmRouting_Create_Check_Modifcation_Query(localRealmConfig,sStatement,j);
            pRes = NULL;
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                DLOG_NONE(" < %s ",__FUNCTION__);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_DEST_ERR_DB_ERROR;

                mysql_set_error_for_RealmRouting_Config_Reqs(localRealmConfig,resp,iReturn,j);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                delete pRes;
                mysql_set_error_for_RealmRouting_Config_Reqs(localRealmConfig,resp,DEL_DEST_ERR_DEST_IS_NOT_IN_REALM,j);
                DLOG_ERROR("Record is not present ");
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_DEST_ERR_DEST_IS_NOT_IN_REALM;
            }
            else
            {

                delete pRes;
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                sql_RealmRouting_Create_Delete_Query(localRealmConfig,sStatement,j);
                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                {
                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                    if(iReturn == DRE_DB_FAIL)
                        iReturn = DEL_DEST_ERR_DB_ERROR;

                    mysql_set_error_for_RealmRouting_Config_Reqs(localRealmConfig,resp,iReturn,j);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

#endif

DbStatus_e CMgrDbInterface::mysql_DefaultRoute_Delete_Config_Reqs(RealmsConfig *pRealmsConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE];
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    ::RealmConfig localRealmConfig;
#if 1
    sql::ResultSet *pRes = NULL;
    sql_DefaultRoute_Create_Check_Modifcation_Query(&localRealmConfig,sStatement,0);
    pRes = NULL;

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {

        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = DEL_DEFROUTE_ERR_DB_ERROR;

        mysql_set_error_for_Realm_Config_Reqs(&localRealmConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        delete pRes;
        mysql_set_error_for_Realm_Config_Reqs(&localRealmConfig,resp,DEL_DEFROUTE_ERR_DEF_ROUTE_NOT_PRESENT);
        DLOG_ERROR("Record is not present ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return  DEL_DEFROUTE_ERR_DEF_ROUTE_NOT_PRESENT;
    }
    else
    {

        delete pRes;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_DefaultRoute_Create_Delete_Query(&localRealmConfig,sStatement,0);
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_DEFROUTE_ERR_DB_ERROR;

            mysql_set_error_for_Realm_Config_Reqs(&localRealmConfig,resp,DEL_DEFROUTE_ERR_DB_ERROR);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

#else
    sql_DefaultRoute_Create_Delete_Query(&localRealmConfig,sStatement,0);
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = DEL_DEFROUTE_ERR_DB_ERROR;

        mysql_set_error_for_Realm_Config_Reqs(&localRealmConfig,resp,DEL_DEFROUTE_ERR_DB_ERROR);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
#endif

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

