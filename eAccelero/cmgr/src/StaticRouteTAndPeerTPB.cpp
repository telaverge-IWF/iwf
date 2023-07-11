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

void StaticRouteTAndPeerTPBQuery::sql_StaticRouteTAndPeer_Create_Select_Query(StaticRoutingTableConfig *staticRoutingTableConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PeerT.PeerHostIdentity,PeerT.RealmName,STATIC_ROUTE_TB.DESTINATION_HOST,STATIC_ROUTE_TB.APPLICATION_ID,STATIC_ROUTE_TB.PRIORITY,STATIC_ROUTE_TB.DESTINATION_REALM from STATIC_ROUTE_TB inner join PeerT on PeerT.PeerID = STATIC_ROUTE_TB.PEER_ID and ");

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    if(staticRoutingTableConfigReq->has_peer())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PeerT.PeerHostIdentity='%s' and ",staticRoutingTableConfigReq->peer().c_str());
    }

    if(staticRoutingTableConfigReq->has_realm())
    {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PeerT.RealmName='%s' and ",staticRoutingTableConfigReq->realm().c_str());
    }

    if(staticRoutingTableConfigReq->has_destionatinhost())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"STATIC_ROUTE_TB.DESTINATION_HOST='%s' and ",staticRoutingTableConfigReq->destionatinhost().c_str());
    }

    if(staticRoutingTableConfigReq->has_applicationid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"STATIC_ROUTE_TB.APPLICATION_ID=%d and ",staticRoutingTableConfigReq->applicationid());
    }

    if(staticRoutingTableConfigReq->has_priority())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"STATIC_ROUTE_TB.PRIORITY=%d and ",staticRoutingTableConfigReq->priority());

    }

    if(staticRoutingTableConfigReq->has_destionatinrealm())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"STATIC_ROUTE_TB.DESTINATION_REALM='%s' and ",staticRoutingTableConfigReq->destionatinrealm().c_str());
    }

    pStatement[strlen(pStatement) - REMOVE_FOUR_CHARATERS] = '\0';

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

}


