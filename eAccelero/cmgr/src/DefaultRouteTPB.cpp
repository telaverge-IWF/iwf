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

void DefaultRouteTPBQuery::sql_DefaultRoute_Create_Check_Modifcation_Query(RealmConfig *dreDefaultRouteReq,char *pStatement,int iDestinationIndex)
{

    //::Destination* localDestinationObj = dreDefaultRouteReq->mutable_destinfo(iDestinationIndex);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PEER_ID from  DEFAULT_ROUTE_TB where REALM_ID=(select REALM_ID from REALM_TB where REALM_NAME ='%s')",dreDefaultRouteReq->realmname().c_str());  
}

void DefaultRouteTPBQuery::sql_DefaultRoute_Create_Add_Query(RealmConfig *dreDefaultRouteReq,char *pStatement,int iDestinationIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE("> %s",__FUNCTION__);
    ::Destination* localDestinationObj = NULL;

    DLOG_DEBUG("dreDefaultRouteReq->destinfo_size() = %d, iDestinationIndex= %d",dreDefaultRouteReq->destinfo_size(),iDestinationIndex);    

    if(dreDefaultRouteReq->destinfo_size() > iDestinationIndex && iDestinationIndex > -1)
    {
        localDestinationObj = dreDefaultRouteReq->mutable_destinfo(iDestinationIndex);
    }
    

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into DEFAULT_ROUTE_TB "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(REALM_ID");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"((select REALM_ID from REALM_TB where REALM_NAME ='%s')",dreDefaultRouteReq->realmname().c_str());

    if(dreDefaultRouteReq->destinfo_size() && localDestinationObj->has_peername())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PEER_ID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s')",localDestinationObj->peername().c_str(),dreDefaultRouteReq->realmname().c_str());
    }


    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE("< %s",__FUNCTION__);
}

void DefaultRouteTPBQuery::sql_DefaultRoute_Create_Mod_Query(RealmConfig *dreDefaultRouteReq,char *pStatement,int iDestinationIndex)
{
    DLOG_NONE("> %s",__FUNCTION__);

    ::Destination* localDestinationObj = NULL;

    DLOG_DEBUG("dreDefaultRouteReq->destinfo_size() = %d, iDestinationIndex= %d",dreDefaultRouteReq->destinfo_size(),iDestinationIndex);    

    if(dreDefaultRouteReq->destinfo_size() > iDestinationIndex && iDestinationIndex > -1)
    {
        localDestinationObj = dreDefaultRouteReq->mutable_destinfo(iDestinationIndex);
    }
    else
    {
        DLOG_WARNING("Destination Object will be NULL, dreDefaultRouteReq->destinfo_size() = %d, iDestinationIndex= %d",dreDefaultRouteReq->destinfo_size(),iDestinationIndex);    
	    DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update DEFAULT_ROUTE_TB set "); 

    if(dreDefaultRouteReq->destinfo_size() && localDestinationObj->has_peername())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PEER_ID=(select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s'),",localDestinationObj->peername().c_str(),dreDefaultRouteReq->realmname().c_str());

    }


    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where REALM_ID=(select REALM_ID from REALM_TB where REALM_NAME ='%s')",dreDefaultRouteReq->realmname().c_str());

    DLOG_NONE("< %s",__FUNCTION__);
}

void DefaultRouteTPBQuery::sql_DefaultRoute_Create_Delete_Query(RealmConfig *dreDefaultRouteReq,char *pStatement,int iDestinationIndex)
{
    DLOG_NONE("> %s",__FUNCTION__);
    //  ::Destination* localDestinationObj = dreDefaultRouteReq->mutable_destinfo(iDestinationIndex);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from DEFAULT_ROUTE_TB where REALM_ID=(select REALM_ID from REALM_TB where REALM_NAME ='%s')",dreDefaultRouteReq->realmname().c_str()); 

    DLOG_NONE("< %s",__FUNCTION__);
}

DbStatus_e DefaultRouteTPBQuery::sql_DefaultRoute_Payload_Validation(RealmConfig *dreDefaultRouteReq,int iDestinationIndex)
{
    //::Destination* localDestinationObj = dreDefaultRouteReq->mutable_destinfo(iDestinationIndex);
    if(!dreDefaultRouteReq->has_realmname())
    {
        DLOG_ERROR("Primary Key Realm is not set in the request");
        return SET_DEFROUTE_MANDATORY_PARAM_REALMNAME_MISSING;  
    }

    return DRE_DB_SUCCESS;
}


void DefaultRouteTPBQuery::sql_DefaultRoute_Create_Select_Query(RealmConfig *dreDefaultRouteReq,char *pStatement,int iDestinationIndex)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    ::Destination* localDestinationObj = NULL;
    DLOG_NONE("> %s",__FUNCTION__);

    DLOG_DEBUG("dreDefaultRouteReq->destinfo_size() = %d, iDestinationIndex= %d",dreDefaultRouteReq->destinfo_size(),iDestinationIndex);    

    if(dreDefaultRouteReq->destinfo_size() > iDestinationIndex && iDestinationIndex > -1)
    {
        localDestinationObj = dreDefaultRouteReq->mutable_destinfo(iDestinationIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from DEFAULT_ROUTE_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");


    if(dreDefaultRouteReq->has_realmname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REALM_ID=(select REALM_ID from REALM_TB where REALM_NAME ='%s') and ",dreDefaultRouteReq->realmname().c_str());
    }

    if(dreDefaultRouteReq->destinfo_size() && localDestinationObj->has_peername())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PEER_ID=(select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s') and ",localDestinationObj->peername().c_str(),dreDefaultRouteReq->realmname().c_str());
    }


    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE("< %s",__FUNCTION__);
}

DbStatus_e DefaultRouteTPBQuery::sql_DefaultRoute_Check_All_Invalid(RealmConfig *dreDefaultRoutePayload,int iDestinationIndex)
{
    ::Destination* localDestinationObj = dreDefaultRoutePayload->mutable_destinfo(iDestinationIndex);

    if(localDestinationObj->has_peername())
    {
        return DRE_DB_FAIL;
    }   


    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}

