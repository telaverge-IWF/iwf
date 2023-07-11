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

void RealmTRealmRoutingTAndDefaultRouteTPBQuery::sql_RealmTRealmRoutingAndDefaultRoute_Create_Select_Query(RealmConfig *realmConfigReq,char *pStatement)
{
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	int iFlag = 0;

	snprintf(pStatement,MAX_STATEMENT_SIZE,"select REALM_ROUTING_TB.PEER_ID,"
                            "REALM_TB.REALM_ID,"
                            "REALM_TB.PROXY_INFO_AVP,"
                            "REALM_TB.REALM_NAME as RealmRoutingTRealmName,"
                            "PeerT.PeerHostIdentity as RealmRoutingTPeerHostIdentity,"
                            "PeerT.RealmName as AssociateRealmName,"
                            "APP_ID,"
                            "LOCAL_ACTION,"
                            "VENDOR_ID,"
                            "PRIORITY,"
                            "REDIRECT_HOST_USAGE,"
                            "REDIRECT_MAX_CACHE_TIME,"
                            "DYNAMICALLY_DISCOVERED,"
                            "DYN_DISCOVERY_EXPIRY"
                            " from REALM_TB left join REALM_ROUTING_TB on REALM_ROUTING_TB.REALM_ID = REALM_TB.REALM_ID"
                            " left join PeerT on REALM_ROUTING_TB.PEER_ID = PeerT.PeerID");


	DLOG_NONE(" > %s ",__FUNCTION__);

	snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"where ");

	if(realmConfigReq->has_realmname())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REALM_TB.REALM_NAME='%s' and ",realmConfigReq->realmname().c_str());
	}

	if(realmConfigReq->has_localaction())
	{
		iFlag = 1;
		if(realmConfigReq->localaction() == "Local")
			snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LOCAL_ACTION=1 and ");
		else if(realmConfigReq->localaction() == "Relay")
			snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LOCAL_ACTION=2 and ");
		else if(realmConfigReq->localaction() == "Proxy")
			snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LOCAL_ACTION=3 and ");
		else
			snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LOCAL_ACTION=4 and ");
	}

	if(realmConfigReq->has_enableproxyinfoavp())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REALM_TB.PROXY_INFO_AVP='%d' and ",realmConfigReq->enableproxyinfoavp());
	}

	if(realmConfigReq->has_redirecthostusage())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REDIRECT_HOST_USAGE=%d and ",realmConfigReq->redirecthostusage());
	}

	if(realmConfigReq->has_redirectmaxcachetime())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REDIRECT_MAX_CACHE_TIME=%d and ",realmConfigReq->redirectmaxcachetime());
	}

	
	sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';

	if(iFlag == 1)
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);

	DLOG_NONE(" < %s ",__FUNCTION__);

}


