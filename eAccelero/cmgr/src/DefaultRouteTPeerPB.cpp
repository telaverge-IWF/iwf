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

void DefaultRouteTPeerPBQuery::sql_DefaultRoute_Create_Check_Modifcation_Query(PeerConfig *dreDefaultRouteReq,char *pStatement)
{

    //::Destination* dreDefaultRouteReq = dreDefaultRouteReq->mutable_destinfo(iDestinationIndex);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PeerHostIdentity from  DefaultRouteT where RealmName='%s'",dreDefaultRouteReq->realm().c_str()); 
}

void DefaultRouteTPeerPBQuery::sql_DefaultRoute_Create_Add_Query(PeerConfig *dreDefaultRouteReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into DefaultRouteT "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(RealmName");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",dreDefaultRouteReq->realm().c_str());

    if(dreDefaultRouteReq->has_peerhostname())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PeerHostIdentity");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",dreDefaultRouteReq->peerhostname().c_str());
    }

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}

void DefaultRouteTPeerPBQuery::sql_DefaultRoute_Create_Mod_Query(PeerConfig *dreDefaultRouteReq,char *pStatement)
{
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update DefaultRouteT set "); 

    if(dreDefaultRouteReq->has_peerhostname())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PeerHostIdentity='%s',",dreDefaultRouteReq->peerhostname().c_str());

    }

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where RealmName='%s'",dreDefaultRouteReq->realm().c_str());

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

}

void DefaultRouteTPeerPBQuery::sql_DefaultRoute_Create_Delete_Query(PeerConfig *dreDefaultRouteReq,char *pStatement)
{
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
    //  ::Destination* dreDefaultRouteReq = dreDefaultRouteReq->mutable_destinfo(iDestinationIndex);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from DefaultRouteT where RealmName='%s'",dreDefaultRouteReq->realm().c_str()); 

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}

DbStatus_e DefaultRouteTPeerPBQuery::sql_DefaultRoute_Payload_Validation(PeerConfig *dreDefaultRouteReq)
{
    //::Destination* dreDefaultRouteReq = dreDefaultRouteReq->mutable_destinfo(iDestinationIndex);
    if(!dreDefaultRouteReq->has_realm())
    {
        DLOG_ERROR("Primary Key Realm is not set in the request");
        return ERR_DEFROUTE_MANDATORY_REALMNAME_MISSING;    
    }

    return DRE_DB_SUCCESS;
}


void DefaultRouteTPeerPBQuery::sql_DefaultRoute_Create_Select_Query(PeerConfig *dreDefaultRouteReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from DefaultRouteT "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    if(dreDefaultRouteReq->has_realm())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RealmName='%s' and ",dreDefaultRouteReq->realm().c_str());
    }

    if(dreDefaultRouteReq->has_peerhostname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PeerHostIdentity='%s' and ",dreDefaultRouteReq->peerhostname().c_str());
    }

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

}

DbStatus_e DefaultRouteTPeerPBQuery::sql_DefaultRoute_Check_All_Invalid(PeerConfig *dreDefaultRoutePayload)
{

    if(dreDefaultRoutePayload->has_peerhostname())
    {
        return DRE_DB_FAIL;
    }   

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}

