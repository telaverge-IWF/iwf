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

void PeerTAndTimerTPBQuery::sql_PeerAndTimer_Create_Select_Query(PeerConfig *drePeerConfigReq,char *pStatement)
{

    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    int iFlag                   = 0;
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PeerT.PeerID,"
                        "PeerT.PeerHostIdentity,"
                        "PeerT.Enable,"
                        "PeerT.RealmName,"
                        "TLSEnabled,"
                        "isMate,"
                        "PeerIP,"
                        "PeerPort,"
                        "FailOverEnable,"
                        "FailBackEnable,"
                        "TransportType,"
                        "AltPeerID,"
                        "WdVal,"
                        "TcVal,"
                        "Eval,"
                        "BusyReconnectTimer,"
                        "DoNotwantToTalkToYouTimer,"
                        "IsSupportDisconnectCause,"
                        "SecurePort,"
                        "PEER_DICTIONARY_MAP_TB.DICTIONARY_ID,"
                        "DICTIONARY_TB.DICTIONARY_NAME,"
                        "DICTIONARY_TB.APP_TYPE,"
                        "PEER_MULTIHOMING_TB.OTHERHOME_IPADDR"
                        " from PeerT"
                        " left join PeerTimersT on PeerT.PeerHostIdentity = PeerTimersT.PeerHostIdentity and PeerT.RealmName = PeerTimersT.RealmName"
                        " left join PEER_DICTIONARY_MAP_TB on PeerT.PeerID = PEER_DICTIONARY_MAP_TB.PEER_ID"
                        " left join DICTIONARY_TB on DICTIONARY_TB.DICTIONARY_ID = PEER_DICTIONARY_MAP_TB.DICTIONARY_ID"
                        " left join PEER_MULTIHOMING_TB on PeerT.PeerID = PEER_MULTIHOMING_TB.PEER_ID "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(drePeerConfigReq->has_peerhostname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PeerT.PeerHostIdentity='%s' and ",drePeerConfigReq->peerhostname().c_str());
    }

    if(drePeerConfigReq->has_realm())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PeerT.RealmName='%s' and ",drePeerConfigReq->realm().c_str());
    }

    if(drePeerConfigReq->has_serveripaddr())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PeerIP='%s' and ",drePeerConfigReq->serveripaddr().c_str());
    }

    if(drePeerConfigReq->has_port())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PeerPort=%d and ",drePeerConfigReq->port());
    }

    if(drePeerConfigReq->has_secureport())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SecurePort=%d and ",drePeerConfigReq->secureport());
    }
    if(drePeerConfigReq->has_failoverenable())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"FailOverEnable=%d and ",drePeerConfigReq->failoverenable());
    }

    if(drePeerConfigReq->has_failebackenable())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"FailBackEnable=%d and ",drePeerConfigReq->failebackenable());
    }

#if 0
    if(drePeerConfigReq->has_transporttype())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TransportType=%d and ",drePeerConfigReq->transporttype());
    }

#endif
    if(drePeerConfigReq->has_altpeername())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"AltPeerID='%s' and ",drePeerConfigReq->altpeername().c_str());
    }

    if(drePeerConfigReq->has_ismate())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"isMate=%d and ",drePeerConfigReq->ismate());
    }

    if(drePeerConfigReq->has_watchdogtimer())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"WdVal=%d and ",drePeerConfigReq->watchdogtimer());
    }

    if(drePeerConfigReq->has_tctimerval())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TcVal=%d and ",drePeerConfigReq->tctimerval());
    }

    if(drePeerConfigReq->has_expirytimer())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"Eval=%d and ",drePeerConfigReq->expirytimer());
    }

    if(drePeerConfigReq->has_busyreconnecttimerval())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"BusyReconnectTimer=%d and ",drePeerConfigReq->busyreconnecttimerval());
    }

    if(drePeerConfigReq->has_donotwanttotalktoyoutimerval())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"DoNotwantToTalkToYouTimer=%d and ",drePeerConfigReq->donotwanttotalktoyoutimerval());
    }

    if(drePeerConfigReq->has_issupportdisconnectcause())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IsSupportDisconnectCause=%d and ",drePeerConfigReq->issupportdisconnectcause());
    }
    if(drePeerConfigReq->has_secureport())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SecurePort=%d and ",drePeerConfigReq->issupportdisconnectcause());
    }


#if 0
    if(drePeerConfigReq->peerInfo.Enable_Status != INVALID_NUM)
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"Enable=%d and ",drePeerConfigReq->peerInfo.Enable_Status);
    }

#endif

    if(iFlag == 1)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
}

