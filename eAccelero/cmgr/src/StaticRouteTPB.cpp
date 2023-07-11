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
#include "ErrorResp.h"

using namespace std;

void StaticRouteTPBQuery::sql_StaticRoute_Create_Validation_Query_for_Peer(StaticRoutingTableConfig *staticRoutingTableConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s'",staticRoutingTableConfigReq->peer().c_str(),staticRoutingTableConfigReq->realm().c_str());

}


void StaticRouteTPBQuery::sql_StaticRoute_Create_Check_Modifcation_Query(StaticRoutingTableConfig *staticRoutingTableConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select STATIC_ROUTE_ID from STATIC_ROUTE_TB where PEER_ID=(select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s') and DESTINATION_HOST='%s' and DESTINATION_REALM='%s'",staticRoutingTableConfigReq->peer().c_str(),staticRoutingTableConfigReq->realm().c_str(),staticRoutingTableConfigReq->destionatinhost().c_str(),staticRoutingTableConfigReq->destionatinrealm().c_str());

    if(staticRoutingTableConfigReq->has_applicationid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," and APPLICATION_ID=%d",staticRoutingTableConfigReq->applicationid());
    }
    else
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," and APPLICATION_ID=0");
    }

}

void StaticRouteTPBQuery::sql_StaticRoute_Create_Add_Query(StaticRoutingTableConfig *staticRoutingTableConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into STATIC_ROUTE_TB "); 
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"(PEER_ID");   
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"((select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s')",staticRoutingTableConfigReq->peer().c_str(),staticRoutingTableConfigReq->realm().c_str());

    if(staticRoutingTableConfigReq->has_destionatinhost())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",DESTINATION_HOST");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",staticRoutingTableConfigReq->destionatinhost().c_str());
    }

    if(staticRoutingTableConfigReq->has_applicationid())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",APPLICATION_ID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",staticRoutingTableConfigReq->applicationid());
    }

    if(staticRoutingTableConfigReq->has_priority())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PRIORITY");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",staticRoutingTableConfigReq->priority());
    }

    if(staticRoutingTableConfigReq->has_destionatinrealm())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",DESTINATION_REALM");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",staticRoutingTableConfigReq->destionatinrealm().c_str());
    }

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void StaticRouteTPBQuery::sql_StaticRoute_Create_Delete_Query(StaticRoutingTableConfig *staticRoutingTableConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(staticRoutingTableConfigReq->has_applicationid())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from STATIC_ROUTE_TB where PEER_ID=(select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s') and DESTINATION_HOST='%s' and DESTINATION_REALM='%s' and APPLICATION_ID=%d",staticRoutingTableConfigReq->peer().c_str(),staticRoutingTableConfigReq->realm().c_str(),staticRoutingTableConfigReq->destionatinhost().c_str(),staticRoutingTableConfigReq->destionatinrealm().c_str(),staticRoutingTableConfigReq->applicationid()); 
    }
    else
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from STATIC_ROUTE_TB where PEER_ID=(select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s') and DESTINATION_HOST='%s' and DESTINATION_REALM='%s' and APPLICATION_ID=0",staticRoutingTableConfigReq->peer().c_str(),staticRoutingTableConfigReq->realm().c_str(),staticRoutingTableConfigReq->destionatinhost().c_str(),staticRoutingTableConfigReq->destionatinrealm().c_str()); 
    }

    DLOG_NONE(" < %s ",__FUNCTION__);

}

void StaticRouteTPBQuery::sql_StaticRoute_Create_Select_Query(StaticRoutingTableConfig *staticRoutingTableConfigReq,char *pStatement)
{

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from STATIC_ROUTE_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(staticRoutingTableConfigReq->has_peer() && staticRoutingTableConfigReq->has_realm())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PEER_ID=(select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s') ",staticRoutingTableConfigReq->peer().c_str(),staticRoutingTableConfigReq->realm().c_str());
    }

    if(staticRoutingTableConfigReq->has_destionatinhost())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"DESTINATION_HOST='%s' and ",staticRoutingTableConfigReq->destionatinhost().c_str());
    }

    if(staticRoutingTableConfigReq->has_applicationid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"APPLICATION_ID=%d and ",staticRoutingTableConfigReq->applicationid());
    }

    if(staticRoutingTableConfigReq->has_priority())
    {
        iFlag=1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PRIORITY=%d and ",staticRoutingTableConfigReq->priority());

    }

    if(staticRoutingTableConfigReq->has_destionatinrealm())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"DESTINATION_REALM='%s' and ",staticRoutingTableConfigReq->destionatinrealm().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement,MAX_STATEMENT_SIZE + strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void StaticRouteTPBQuery::sql_StaticRoute_Create_Mod_Query(StaticRoutingTableConfig *staticRoutingTableConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update STATIC_ROUTE_TB set "); 

    if(staticRoutingTableConfigReq->has_destionatinhost())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"DESTINATION_HOST='%s',",staticRoutingTableConfigReq->destionatinhost().c_str());
    }

    if(staticRoutingTableConfigReq->has_priority())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PRIORITY=%d,",staticRoutingTableConfigReq->priority());
    }

   if(staticRoutingTableConfigReq->has_destionatinrealm())
    {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"DESTINATION_REALM='%s',",staticRoutingTableConfigReq->destionatinrealm().c_str());
    }

    pStatement[strlen(pStatement) -1] = ' ';


    if(staticRoutingTableConfigReq->has_applicationid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where PEER_ID=(select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s') and DESTINATION_HOST='%s' and DESTINATION_REALM='%s' and APPLICATION_ID=%d",staticRoutingTableConfigReq->peer().c_str(),staticRoutingTableConfigReq->realm().c_str(),staticRoutingTableConfigReq->destionatinhost().c_str(),staticRoutingTableConfigReq->destionatinrealm().c_str(),staticRoutingTableConfigReq->applicationid());
    }
    else
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where PEER_ID=(select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s') and DESTINATION_HOST='%s' and DESTINATION_REALM='%s' and APPLICATION_ID=0",staticRoutingTableConfigReq->peer().c_str(),staticRoutingTableConfigReq->realm().c_str(),staticRoutingTableConfigReq->destionatinhost().c_str(),staticRoutingTableConfigReq->destionatinrealm().c_str());

    }
    DLOG_NONE(" < %s ",__FUNCTION__);

}

DbStatus_e StaticRouteTPBQuery::sql_StaticRoute_Payload_Validation(StaticRoutingTableConfig *staticRoutingTableConfigReq)
{
    if(!staticRoutingTableConfigReq->has_peer())
    {
        DLOG_ERROR("Primary Key HostName is not set in the request");
        return ERR_STATIC_ROUTING_MANDATORY_PARAM_PEERNAME_MISSING;    
    }
    else if (!staticRoutingTableConfigReq->has_realm())
    {
        DLOG_ERROR("Primary Key Realm is not set in the request");
        return ERR_STATIC_ROUTING_MANDATORY_PARAM_REALMNAME_MISSING;   
    }
    else if (!staticRoutingTableConfigReq->has_destionatinhost())
    {
        DLOG_ERROR("Primary Key destionation host is not set in the request");
        return ERR_STATIC_ROUTING_MANDATORY_PARAM_DESTINATION_HOST_MISSING;   
    }
    else if (!staticRoutingTableConfigReq->has_destionatinrealm())
    {
        DLOG_ERROR("Primary Key destionation relm is not set in the request");
        return ERR_STATIC_ROUTING_MANDATORY_PARAM_DESTINATION_REALM_MISSING;   
    }

    return DRE_DB_SUCCESS;
}

DbStatus_e StaticRouteTPBQuery::sql_StaticRoute_Check_All_Invalid(StaticRoutingTableConfig *staticRoutingTableConfigReq)
{

    if(staticRoutingTableConfigReq->has_destionatinhost())
    {
        return DRE_DB_FAIL;
    }

    if(staticRoutingTableConfigReq->has_applicationid())
    {
        return DRE_DB_FAIL;
    }

    if(staticRoutingTableConfigReq->has_priority())
    {
        return DRE_DB_FAIL;
    }

    if(staticRoutingTableConfigReq->has_destionatinrealm())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
