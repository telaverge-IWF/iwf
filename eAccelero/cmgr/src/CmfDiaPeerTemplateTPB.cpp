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

void CmfDiaPeerTemplateTPBQuery::sql_CmfDiaPeerTemplate_Create_Validation_Query_for_Peer(CMFPeerTemplate *CmfPeerTemplateConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select RealmName from PeerT where PeerCMFConfigId=(select CMF_PEER_TEMPLATE_ID from CMF_DIA_PEER_TEMPLATE_TB where PEER_TEMPLATE_NAME='%s')",CmfPeerTemplateConfigReq->peertemplatename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfDiaPeerTemplateTPBQuery::sql_CmfDiaPeerTemplate_Create_Check_Modifcation_Query(CMFPeerTemplate *CmfPeerTemplateConfigReq,char *pStatement)
{
    int iFlag 					= 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
    DLOG_NONE(" > %s ",__FUNCTION__);


    snprintf(pStatement,MAX_STATEMENT_SIZE,"select CMF_PEER_TEMPLATE_ID from CMF_DIA_PEER_TEMPLATE_TB ");
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(CmfPeerTemplateConfigReq->has_peertemplatename())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"PEER_TEMPLATE_NAME='%s' and ",CmfPeerTemplateConfigReq->peertemplatename().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }


    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfDiaPeerTemplateTPBQuery::sql_CmfDiaPeerTemplate_Create_Add_Query(CMFPeerTemplate *CmfPeerTemplateConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]	= {0};
    char sFieldValue[MAX_STATEMENT_SIZE]	= {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into CMF_DIA_PEER_TEMPLATE_TB ");
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(PEER_TEMPLATE_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",CmfPeerTemplateConfigReq->peertemplatename().c_str());


    if(CmfPeerTemplateConfigReq->has_priority())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",PRIORITY");
        if(CmfPeerTemplateConfigReq->priority() == 1)
        {
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'normal'");
        }
        if(CmfPeerTemplateConfigReq->priority() == 2)
        {
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'high'");
        }
    }

    if(CmfPeerTemplateConfigReq->has_maxintps())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",MAX_IN_TPS");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",CmfPeerTemplateConfigReq->maxintps());
    }
    if(CmfPeerTemplateConfigReq->has_maxouttps())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",MAX_OUT_TPS");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",CmfPeerTemplateConfigReq->maxouttps());
    }
    if(CmfPeerTemplateConfigReq->has_maxavgresptime())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",MAX_AVG_RESP_TIME");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",CmfPeerTemplateConfigReq->maxavgresptime());
    }

    if(CmfPeerTemplateConfigReq->has_throttle())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",THROTTLE");
        if(CmfPeerTemplateConfigReq->throttle() == 1)
        {
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'enable'");
        }
        if(CmfPeerTemplateConfigReq->throttle() == 2)
        {
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'disable'");
        }
    }

    if(CmfPeerTemplateConfigReq->has_maxerrresp())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",MAX_ERR_RESP");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",CmfPeerTemplateConfigReq->maxerrresp());
    }

    if(CmfPeerTemplateConfigReq->has_timewindow())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",TIME_WINDOW");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",CmfPeerTemplateConfigReq->timewindow());
    }

    if(CmfPeerTemplateConfigReq->has_maxpendingreqs())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",MAX_PENDING_REQS");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",CmfPeerTemplateConfigReq->maxpendingreqs());
    }

    if(CmfPeerTemplateConfigReq->has_errrespresultcode())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",ERR_RESP_RESULT_CODE");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",CmfPeerTemplateConfigReq->errrespresultcode());
    }

    if(CmfPeerTemplateConfigReq->has_outpeercongcond())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",OUTGOING_PEER_CONGESTION_CONDITION");
        if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_PENDING_QUEUE)
        {
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'pending-queue'");
        }

        else if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_AVERAGE_RESPONSE_TIME)
        {
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'average-response-time'");
        }

        else if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_ERROR_RESPONSE_COUNT)
        {
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'error-response-count'");
        }

        else if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_TPS)
        {
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'tps'");
        }

        else if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_NONE)
        {
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'none'");
        }
    }
    else
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",OUTGOING_PEER_CONGESTION_CONDITION");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'none'");
    }

    if(CmfPeerTemplateConfigReq->has_dismisbehavepeer())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",DISCONNECT_MISBEHAVING_PEER");
        if(CmfPeerTemplateConfigReq->dismisbehavepeer() == CMFPeerTemplate_DisconnectMisbehavingPeer_PEER_ENABLE)
        {
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'enable'");
        }

        else if(CmfPeerTemplateConfigReq->dismisbehavepeer() == CMFPeerTemplate_DisconnectMisbehavingPeer_PEER_DISABLE)
        {
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'disable'");
        }
    }

    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfDiaPeerTemplateTPBQuery::sql_CmfDiaPeerTemplate_Create_Delete_Query(CMFPeerTemplate *CmfPeerTemplateConfigReq,char *pStatement)
{

    int iFlag 					= 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
    DLOG_NONE(" > %s ",__FUNCTION__);


    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from CMF_DIA_PEER_TEMPLATE_TB ");
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(CmfPeerTemplateConfigReq->has_peertemplatename())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"PEER_TEMPLATE_NAME='%s' and ",CmfPeerTemplateConfigReq->peertemplatename().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfDiaPeerTemplateTPBQuery::sql_CmfDiaPeerTemplate_Create_Mod_Query(CMFPeerTemplate *CmfPeerTemplateConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update CMF_DIA_PEER_TEMPLATE_TB set ");


    if(CmfPeerTemplateConfigReq->has_priority())
    {
        if(CmfPeerTemplateConfigReq->priority() == 1)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"PRIORITY='normal',");
        }
        else if(CmfPeerTemplateConfigReq->priority() == 2)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"PRIORITY='high',");
        }
    }

    if(CmfPeerTemplateConfigReq->has_maxintps())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"MAX_IN_TPS=%d,",CmfPeerTemplateConfigReq->maxintps());
    }
    if(CmfPeerTemplateConfigReq->has_maxouttps())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"MAX_OUT_TPS=%d,",CmfPeerTemplateConfigReq->maxouttps());
    }

    if(CmfPeerTemplateConfigReq->has_maxavgresptime())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"MAX_AVG_RESP_TIME=%d,",CmfPeerTemplateConfigReq->maxavgresptime());
    }

    if(CmfPeerTemplateConfigReq->has_throttle())
    {
        if(CmfPeerTemplateConfigReq->throttle() == 1)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"THROTTLE='enable',");
        }
        else if(CmfPeerTemplateConfigReq->throttle() == 2)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"THROTTLE='disable',");
        }
    }

    if(CmfPeerTemplateConfigReq->has_maxerrresp())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"MAX_ERR_RESP=%d,",CmfPeerTemplateConfigReq->maxerrresp());
    }

    if(CmfPeerTemplateConfigReq->has_timewindow())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"TIME_WINDOW=%d,",CmfPeerTemplateConfigReq->timewindow());
    }

    if(CmfPeerTemplateConfigReq->has_maxpendingreqs())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"MAX_PENDING_REQS=%d,",CmfPeerTemplateConfigReq->maxpendingreqs());
    }

    if(CmfPeerTemplateConfigReq->has_errrespresultcode())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"ERR_RESP_RESULT_CODE=%d,",CmfPeerTemplateConfigReq->errrespresultcode());
    }

    if(CmfPeerTemplateConfigReq->has_outpeercongcond())
    {
        if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_PENDING_QUEUE)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"OUTGOING_PEER_CONGESTION_CONDITION='pending-queue',");
        }
        else if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_AVERAGE_RESPONSE_TIME)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"OUTGOING_PEER_CONGESTION_CONDITION='average-response-time',");
        }
        else if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_ERROR_RESPONSE_COUNT)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"OUTGOING_PEER_CONGESTION_CONDITION='error-response-count',");
        }
        else if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_TPS)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"OUTGOING_PEER_CONGESTION_CONDITION='tps',");
        }
        else if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_NONE)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"OUTGOING_PEER_CONGESTION_CONDITION='none',");
        }
    }
    else
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"OUTGOING_PEER_CONGESTION_CONDITION='none',");
    }

    if(CmfPeerTemplateConfigReq->has_dismisbehavepeer())
    {
        if(CmfPeerTemplateConfigReq->dismisbehavepeer() == CMFPeerTemplate_DisconnectMisbehavingPeer_PEER_ENABLE)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"DISCONNECT_MISBEHAVING_PEER='enable',");
        }
        else if(CmfPeerTemplateConfigReq->dismisbehavepeer() == CMFPeerTemplate_DisconnectMisbehavingPeer_PEER_DISABLE)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"DISCONNECT_MISBEHAVING_PEER='disable',");
        }
    }

    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where PEER_TEMPLATE_NAME='%s'",CmfPeerTemplateConfigReq->peertemplatename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CmfDiaPeerTemplateTPBQuery::sql_CmfDiaPeerTemplate_Payload_Validation(CMFPeerTemplate *CmfPeerTemplateConfigReq)
{

    return DRE_DB_SUCCESS;
}

void CmfDiaPeerTemplateTPBQuery::sql_CmfDiaPeerTemplate_Create_Select_Query(CMFPeerTemplate *CmfPeerTemplateConfigReq,char *pStatement)
{
    int iFlag 					= 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from CMF_DIA_PEER_TEMPLATE_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(CmfPeerTemplateConfigReq->has_peertemplatename())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"PEER_TEMPLATE_NAME='%s' and ",CmfPeerTemplateConfigReq->peertemplatename().c_str());
    }

    if(CmfPeerTemplateConfigReq->has_priority())
    {
        iFlag = 1;
        if(CmfPeerTemplateConfigReq->priority() == 1)
        {
            if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
                snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"LOCAL_ACTION='normal' and ");
        }
        else if(CmfPeerTemplateConfigReq->priority() == 2)
        {
            if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
                snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"LOCAL_ACTION='high' and ");
        }
    }

    if(CmfPeerTemplateConfigReq->has_maxavgresptime())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"MAX_AVG_RESP_TIME=%d and ",CmfPeerTemplateConfigReq->maxavgresptime());
    }

    if(CmfPeerTemplateConfigReq->has_maxintps())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"MAX_IN_TPS=%d and ",CmfPeerTemplateConfigReq->maxintps());
    }
    if(CmfPeerTemplateConfigReq->has_maxouttps())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"MAX_OUT_TPS=%d and ",CmfPeerTemplateConfigReq->maxouttps());
    }

    if(CmfPeerTemplateConfigReq->has_throttle())
    {
        iFlag = 1;
        if(CmfPeerTemplateConfigReq->throttle() == 1)
        {
            if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
                snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"THROTTLE='enable' and ");
        }
        else if(CmfPeerTemplateConfigReq->throttle() == 2)
        {
            if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
                snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"THROTTLE='disable' and ");
        }
    }

    if(CmfPeerTemplateConfigReq->has_maxerrresp())
    {
        iFlag = 1;
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"MAX_ERR_RESP=%d and ",CmfPeerTemplateConfigReq->maxerrresp());
    }


    if(CmfPeerTemplateConfigReq->has_timewindow())
    {
        iFlag = 1;
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"TIME_WINDOW=%d and ",CmfPeerTemplateConfigReq->timewindow());
    }

    if(CmfPeerTemplateConfigReq->has_maxpendingreqs())
    {
        iFlag = 1;
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"MAX_PENDING_REQS=%d and ",CmfPeerTemplateConfigReq->maxpendingreqs());
    }


    if(CmfPeerTemplateConfigReq->has_errrespresultcode())
    {
        iFlag = 1;
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"ERR_RESP_RESULT_CODE=%d and ",CmfPeerTemplateConfigReq->errrespresultcode());
    }

    if(CmfPeerTemplateConfigReq->has_outpeercongcond())
    {
        iFlag = 1;
        if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_PENDING_QUEUE)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"OUTGOING_PEER_CONGESTION_CONDITION='pending-queue' and ");
        }
        else if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_AVERAGE_RESPONSE_TIME)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"OUTGOING_PEER_CONGESTION_CONDITION='average-response-time' and ");
        }
        else if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_ERROR_RESPONSE_COUNT)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"OUTGOING_PEER_CONGESTION_CONDITION='error-response-count' and ");
        }
        else if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_TPS)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"OUTGOING_PEER_CONGESTION_CONDITION='tps' and ");
        }
        else if(CmfPeerTemplateConfigReq->outpeercongcond() == CMFPeerTemplate_Condition_NONE)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"OUTGOING_PEER_CONGESTION_CONDITION='none' and ");
        }
    }

    if(CmfPeerTemplateConfigReq->has_dismisbehavepeer())
    {
        iFlag = 1;
        if(CmfPeerTemplateConfigReq->dismisbehavepeer() == CMFPeerTemplate_DisconnectMisbehavingPeer_PEER_ENABLE)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"DISCONNECT_MISBEHAVING_PEER='enable' and ");
        }
        else if(CmfPeerTemplateConfigReq->dismisbehavepeer() == CMFPeerTemplate_DisconnectMisbehavingPeer_PEER_DISABLE)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"DISCONNECT_MISBEHAVING_PEER='disable' and ");
        }
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CmfDiaPeerTemplateTPBQuery::sql_CmfDiaPeerTemplate_Check_All_Invalid(CMFPeerTemplate *CmfPeerTemplateConfigReq)
{
    if(CmfPeerTemplateConfigReq->has_priority())
    {
        return DRE_DB_FAIL;
    }

    if(CmfPeerTemplateConfigReq->has_maxintps())
    {
        return DRE_DB_FAIL;
    }
    if(CmfPeerTemplateConfigReq->has_maxouttps())
    {
        return DRE_DB_FAIL;
    }

    if(CmfPeerTemplateConfigReq->has_throttle())
    {
        return DRE_DB_FAIL;
    }

    if(CmfPeerTemplateConfigReq->has_maxavgresptime())
    {
        return DRE_DB_FAIL;
    }

    if(CmfPeerTemplateConfigReq->has_maxerrresp())
    {
        return DRE_DB_FAIL;
    }

    if(CmfPeerTemplateConfigReq->has_timewindow())
    {
        return DRE_DB_FAIL;
    }

    if(CmfPeerTemplateConfigReq->has_maxpendingreqs())
    {
        return DRE_DB_FAIL;
    }

    if(CmfPeerTemplateConfigReq->has_errrespresultcode())
    {
        return DRE_DB_FAIL;
    }
    if(CmfPeerTemplateConfigReq->has_outpeercongcond())
    {
        return DRE_DB_FAIL;
    }
    if(CmfPeerTemplateConfigReq->has_dismisbehavepeer())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
