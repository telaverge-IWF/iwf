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

void LocalHostTAndTransportTPBQuery::sql_LocalHostAndTransport_Create_Select_Query(LocalHost *dreLocalHostReq,char *pStatement)
{

    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    int iFlag                   = 0;
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select LocalHostConfigT.LocalHostConfigID,HostName,AuthLifeTime,RealmName,AuthGraceTime,AuthTimeOut,AcctInterim,AcctTimeOut,LOCAL_TRANSPORT_TB.TRANSPORT_ID,TRANSPORT_TYPE,PUBLIC_SERVER_IP,IP_ADDRESS,PORT,SecurePort,MULTIHOMING_TB.OTHERHOME_IPADDR from LocalHostConfigT left join LOCAL_TRANSPORT_TB on LocalHostConfigT.LocalHostConfigID = LOCAL_TRANSPORT_TB.LocalHostConfigID left join MULTIHOMING_TB on LOCAL_TRANSPORT_TB.TRANSPORT_ID = MULTIHOMING_TB.TRANSPORT_ID "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(dreLocalHostReq->has_localhostname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LocalHostConfigT.HostName='%s' and ",dreLocalHostReq->localhostname().c_str());
    }

    if(dreLocalHostReq->has_realmname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LocalHostConfigT.RealmName='%s' and ",dreLocalHostReq->realmname().c_str());
    }

    if(iFlag == 1)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
}

