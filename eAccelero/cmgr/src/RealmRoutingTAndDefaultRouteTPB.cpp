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

void RealmRoutingTAndDefaultRouteTPBQuery::sql_RealmRoutingAndDefaultRoute_Create_Select_Query(RealmConfig *realmConfigReq,char *pStatement,int iDestinationIndex)
{
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    ::Destination* localDestinationObj = NULL;

    DLOG_DEBUG("RealmConfigReq->destinfo_size() = %d, iDestinationIndex= %d",realmConfigReq->destinfo_size(),iDestinationIndex);    
    if(realmConfigReq->destinfo_size() > iDestinationIndex && iDestinationIndex > -1)
    {
        localDestinationObj = realmConfigReq->mutable_destinfo(iDestinationIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PeerT.PeerID,"
                                    "RealmRoutingT.RealmName as RealmRoutingTRealmName,"
                                    "RealmRoutingT.PeerHostIdentity as RealmRoutingTPeerHostIdentity,"
                                    "ApplicationID,"
                                    "LocalAction,"
                                    "VendorID,"
                                    "Priority,"
                                    "RedirectHostUsage,"
                                    "RedirectMaxCacheTime,"
                                    "DefaultRouteT.PeerHostIdentity as DefaultRouteTPeerHostIdentity"
                                    " from RealmRoutingT"
                                    " inner join PeerT on RealmRoutingT.RealmName = PeerT.RealmName"
                                    " and RealmRoutingT.PeerHostIdentity = PeerT.PeerHostIdentity and ");


    DLOG_NONE(" > %s ",__FUNCTION__);

    if(realmConfigReq->has_realmname())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RealmRoutingT.RealmName='%s' and ",realmConfigReq->realmname().c_str());
    }

    if(realmConfigReq->destinfo_size() && localDestinationObj->has_applicationid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ApplicationID=%d and ",localDestinationObj->applicationid());
    }

    if(realmConfigReq->destinfo_size() && localDestinationObj->has_peername())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RealmRoutingT.PeerHostIdentity='%s' and ",localDestinationObj->peername().c_str());
    }

#if 0
    if(realmConfigReq->has_localaction())
    {
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LocalAction=%d and ",realmConfigReq->localaction());
    }
#endif

    if(realmConfigReq->destinfo_size() && localDestinationObj->has_vendorid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"VendorID=%d and ",localDestinationObj->vendorid());
    }

    if(realmConfigReq->destinfo_size() && localDestinationObj->has_priority())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"Priority=%d and ",localDestinationObj->priority());
    }

#if 0
    if(realmConfigReq->realmInfo.NodeDiscovery != INVALID_NUM)
    {
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NodeDiscovery=%d and ",realmConfigReq->realmInfo.NodeDiscovery);
    }
#endif

    if(realmConfigReq->has_redirecthostusage())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RedirectHostUsage=%d and ",realmConfigReq->redirecthostusage());
    }

    if(realmConfigReq->has_redirectmaxcachetime())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RedirectMaxCacheTime=%d and ",realmConfigReq->redirectmaxcachetime());
    }


    pStatement[strlen(pStatement) - REMOVE_FOUR_CHARATERS] = '\0';

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"left join DefaultRouteT on RealmRoutingT.RealmName = DefaultRouteT.RealmName ");
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);

    DLOG_NONE(" < %s ",__FUNCTION__);

}


