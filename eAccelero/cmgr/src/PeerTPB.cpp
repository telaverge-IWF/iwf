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

void PeerTPBQuery::sql_Peer_Create_Check_Unique_Constrain(PeerConfig *drePeerConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    if(drePeerConfigReq->has_port() && (drePeerConfigReq->port() > 0))
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select RealmName from PeerT where PeerIP='%s' and PeerPort=%d",drePeerConfigReq->serveripaddr().c_str(),drePeerConfigReq->port());
    }
    else
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select RealmName from PeerT where PeerIP='%s',PeerPort=0 and SecurePort=0",drePeerConfigReq->serveripaddr().c_str());
    }
    DLOG_NONE(" < %s ",__FUNCTION__);

}

void PeerTPBQuery::sql_Peer_Create_Check_Unique_Constrain_For_SecurePort(PeerConfig *drePeerConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    if(drePeerConfigReq->has_secureport() && (drePeerConfigReq->secureport() > 0))
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select RealmName from PeerT where PeerIP='%s' and SecurePort=%d",drePeerConfigReq->serveripaddr().c_str(),drePeerConfigReq->secureport());
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
}


void PeerTPBQuery::sql_Peer_Create_Validation_Query_for_alternate_peer(PeerConfig *drePeerConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select RealmName from PeerT where PeerHostIdentity='%s' and RealmName='%s' and AltPeerID is NULL",drePeerConfigReq->peerhostname().c_str(),drePeerConfigReq->realm().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}


void PeerTPBQuery::sql_Peer_Create_Check_Modifcation_Query(PeerConfig *drePeerConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select RealmName from PeerT where PeerHostIdentity='%s' and RealmName='%s'",drePeerConfigReq->peerhostname().c_str(),drePeerConfigReq->realm().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void PeerTPBQuery::sql_Peer_Create_Add_Query(PeerConfig *drePeerConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into PeerT ");
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(PeerHostIdentity,RealmName");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s','%s'",drePeerConfigReq->peerhostname().c_str(),drePeerConfigReq->realm().c_str());

    if(drePeerConfigReq->has_serveripaddr())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PeerIP");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",drePeerConfigReq->serveripaddr().c_str());
    }

    if(drePeerConfigReq->has_port())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PeerPort");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",drePeerConfigReq->port());
    }

    if(drePeerConfigReq->has_failoverenable())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",FailOverEnable");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",drePeerConfigReq->failoverenable());
    }

    if(drePeerConfigReq->has_failebackenable())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",FailBackEnable");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",drePeerConfigReq->failebackenable());
    }

    if(drePeerConfigReq->has_transporttype())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",TransportType");

        if(drePeerConfigReq->transporttype() == "SCTP")
        {
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",2);
        }
        else if(drePeerConfigReq->transporttype() == "TLS")
        {
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",3);
        }
        else if(drePeerConfigReq->transporttype() == "TCP")
        {
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",1);
        }
        else
        {
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",0);
        }
    }

    if(drePeerConfigReq->has_tlsenabled())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",TLSEnabled");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",drePeerConfigReq->tlsenabled());
    }

    if(drePeerConfigReq->has_altpeername())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",AltPeerID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",drePeerConfigReq->altpeername().c_str());
    }

    if(drePeerConfigReq->has_ismate())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",isMate");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",drePeerConfigReq->ismate());
    }

    if(drePeerConfigReq->has_peerstatus())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",Enable");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",drePeerConfigReq->peerstatus());
    }

    if(drePeerConfigReq->has_issupportdisconnectcause())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IsSupportDisconnectCause");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",drePeerConfigReq->issupportdisconnectcause());
    }
    if(drePeerConfigReq->has_secureport())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SecurePort");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",drePeerConfigReq->secureport());
    }
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void PeerTPBQuery::sql_Peer_Create_Delete_Query(PeerConfig *drePeerConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from PeerT where PeerHostIdentity='%s' and RealmName='%s'",drePeerConfigReq->peerhostname().c_str(),drePeerConfigReq->realm().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);

}

void PeerTPBQuery::sql_Peer_Create_Select_Query(PeerConfig *drePeerConfigReq,char *pStatement)
{

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from PeerT ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(drePeerConfigReq->has_peerhostname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PeerHostIdentity='%s' and ",drePeerConfigReq->peerhostname().c_str());
    }

    if(drePeerConfigReq->has_realm())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RealmName='%s' and ",drePeerConfigReq->realm().c_str());
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

    if(drePeerConfigReq->has_transporttype())
    {
        iFlag = 1;
        if(drePeerConfigReq->transporttype() == "SCTP")
        {
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TransportType=2 and ");
        }
        else if(drePeerConfigReq->transporttype() == "TLS")
        {
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TransportType=3 and ");
        }
        else
        {
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TransportType=1 and ");
        }

    }

    if(drePeerConfigReq->has_tlsenabled())
    {
        iFlag=1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TLSEnabled=%d and ",drePeerConfigReq->tlsenabled());

    }

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

    if(drePeerConfigReq->has_peerstatus())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"Enable=%d and ",drePeerConfigReq->peerstatus());
    }

    if(drePeerConfigReq->has_issupportdisconnectcause())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IsSupportDisconnectCause=%d and ",drePeerConfigReq->issupportdisconnectcause());
    }

    if(drePeerConfigReq->has_secureport())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SecurePort=%d and ",drePeerConfigReq->secureport());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void PeerTPBQuery::sql_Peer_Create_Mod_Query(PeerConfig *drePeerConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update PeerT set ");

    if(drePeerConfigReq->has_serveripaddr())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PeerIP='%s',",drePeerConfigReq->serveripaddr().c_str());
    }

    if(drePeerConfigReq->has_port())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PeerPort=%d,",drePeerConfigReq->port());
    }

    if(drePeerConfigReq->has_secureport())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SecurePort=%d,",drePeerConfigReq->secureport());
    }
    if(drePeerConfigReq->has_failoverenable())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"FailOverEnable=%d,",drePeerConfigReq->failoverenable());
    }

    if(drePeerConfigReq->has_failebackenable())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"FailBackEnable=%d,",drePeerConfigReq->failebackenable());
    }

    if(drePeerConfigReq->has_transporttype())
    {
        if(drePeerConfigReq->transporttype() == "SCTP")
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TransportType=2,");
        }
        else if(drePeerConfigReq->transporttype() == "TLS")
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TransportType=3,");
        }
        else if(drePeerConfigReq->transporttype() == "TCP")
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TransportType=1,");
        }
        else
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TransportType=0,");
        }

    }

    if(drePeerConfigReq->has_tlsenabled())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TLSEnabled=%d,",drePeerConfigReq->tlsenabled());
    }

    if(drePeerConfigReq->has_issupportdisconnectcause())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IsSupportDisconnectCause=%d,",drePeerConfigReq->issupportdisconnectcause());
    }
    if(drePeerConfigReq->has_altpeername())
    {
        if(drePeerConfigReq->altpeername() == "")
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"AltPeerID=NULL,");
        }
        else
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"AltPeerID='%s',",drePeerConfigReq->altpeername().c_str());
        }
    }

    if(drePeerConfigReq->has_ismate())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"isMate=%d,",drePeerConfigReq->ismate());
    }

    if(drePeerConfigReq->has_peerstatus())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"Enable=%d,",drePeerConfigReq->peerstatus());
    }

    pStatement[strlen(pStatement) -1] = ' ';


    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where PeerHostIdentity='%s' and RealmName='%s'",drePeerConfigReq->peerhostname().c_str(),drePeerConfigReq->realm().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);

}

DbStatus_e PeerTPBQuery::sql_Peer_Payload_Validation(PeerConfig *drePeerConfigReq)
{
    if(!drePeerConfigReq->has_peerhostname())
    {
        DLOG_ERROR("Primary Key HostName is not set in the request");
        return ERR_MANDATORY_PARAM_PEERNAME_MISSING;
    }
    else if (!drePeerConfigReq->has_realm())
    {
        DLOG_ERROR("Primary Key Realm is not set in the request");
        return ERR_MANDATORY_PARAM_REALMNAME_MISSING;
    }
    return DRE_DB_SUCCESS;
}

DbStatus_e PeerTPBQuery::sql_Peer_Check_All_Invalid(PeerConfig *drePeerConfigReq)
{

    if(drePeerConfigReq->has_serveripaddr())
    {
        return DRE_DB_FAIL;
    }

    if(drePeerConfigReq->has_port())
    {
        return DRE_DB_FAIL;
    }

    if(drePeerConfigReq->has_secureport())
    {
        return DRE_DB_FAIL;
    }

    if(drePeerConfigReq->has_failoverenable())
    {
        return DRE_DB_FAIL;
    }

    if(drePeerConfigReq->has_failebackenable())
    {
        return DRE_DB_FAIL;
    }

    if(drePeerConfigReq->has_transporttype())
    {
        return DRE_DB_FAIL;
    }

    if(drePeerConfigReq->has_tlsenabled())
    {
        return DRE_DB_FAIL;
    }


    if(drePeerConfigReq->has_altpeername())
    {
        return DRE_DB_FAIL;
    }

    if(drePeerConfigReq->has_ismate())
    {
        return DRE_DB_FAIL;
    }

    if(drePeerConfigReq->has_peerstatus())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
