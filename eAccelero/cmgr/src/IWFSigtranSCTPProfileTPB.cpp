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


#include <CMgrIwfDbInterface.h>

using namespace std;

void IWFSigtranSCTPProfileTPBQuery::sql_IWFSigtranSCTPProfile_Create_Check_Modifcation_Query(IwfSigtranSctpProfileConfig *IwfSigtranSctpProfileConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_SIGTRAN_SCTP_PROFILE_ID from IWF_SIGTRAN_SCTP_PROFILE_TB where IWF_SIGTRAN_SCTP_PROFILE_NAME='%s'",IwfSigtranSctpProfileConfigReq->sctpprofilename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranSCTPProfileTPBQuery::sql_IWFSigtranSCTPProfile_Create_Add_Query(IwfSigtranSctpProfileConfig *IwfSigtranSctpProfileConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_SIGTRAN_SCTP_PROFILE_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(IWF_SIGTRAN_SCTP_PROFILE_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",IwfSigtranSctpProfileConfigReq->sctpprofilename().c_str());

    if(IwfSigtranSctpProfileConfigReq->has_heartbeatenable())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",HEARTBEAT_ENABLE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->heartbeatenable());
    }

    if(IwfSigtranSctpProfileConfigReq->has_heartbeattimeout())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",HEARTBEAT_TIMEOUT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->heartbeattimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_inittimeout())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",INIT_TIMEOUT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->inittimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_assocmaxattempt())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ASSOC_MAX_ATTEMPTS");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->assocmaxattempt());
    }

    if(IwfSigtranSctpProfileConfigReq->has_maxattempt())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",MAX_ATTEMPTS");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->maxattempt());
    }

    if(IwfSigtranSctpProfileConfigReq->has_rtomax())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",RTO_MAX");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->rtomax());
    }

    if(IwfSigtranSctpProfileConfigReq->has_rtomin())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",RTO_MIN");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->rtomin());
    }

    if(IwfSigtranSctpProfileConfigReq->has_rtoinitial())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",RTO_INITIAL");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->rtoinitial());
    }

    if(IwfSigtranSctpProfileConfigReq->has_pathfailureretrycount())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PATH_FAILURE_RETRY_COUNT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->pathfailureretrycount());
    }

    if(IwfSigtranSctpProfileConfigReq->has_maxinstreams())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",MAX_IN_STREAMS");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->maxinstreams());
    }

    if(IwfSigtranSctpProfileConfigReq->has_numoutstreams())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",NUM_OUT_STREAMS");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->numoutstreams());
    }

    if(IwfSigtranSctpProfileConfigReq->has_receivetimeout())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",RECEIVE_TIME_OUT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->receivetimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_shutdowntimeout())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SHUTDOWN_TIMEOUT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->shutdowntimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_pmtutimeout())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PMTU_TIMEOUT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->pmtutimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_cookielife())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",COOKIE_LIFE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->cookielife());
    }
    
    if(IwfSigtranSctpProfileConfigReq->has_sendtimeout())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SEND_TIME_OUT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->sendtimeout());
    }
     
    if(IwfSigtranSctpProfileConfigReq->has_sackdelay())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SACK_DELAY");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->sackdelay());
    }
      
    if(IwfSigtranSctpProfileConfigReq->has_sendbufsize())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SEND_BUF_SIZE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->sendbufsize());
    }
       
    if(IwfSigtranSctpProfileConfigReq->has_recvbufsize())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",RECV_BUF_SIZE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->recvbufsize());
    }
        
    if(IwfSigtranSctpProfileConfigReq->has_reconnecttimeout())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",RECONNECT_TIMEOUT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpProfileConfigReq->reconnecttimeout());
    }
  
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranSCTPProfileTPBQuery::sql_IWFSigtranSCTPProfile_Create_Mod_Query(IwfSigtranSctpProfileConfig *IwfSigtranSctpProfileConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_SIGTRAN_SCTP_PROFILE_TB set "); 

    if(IwfSigtranSctpProfileConfigReq->has_heartbeatenable())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"HEARTBEAT_ENABLE=%d,",IwfSigtranSctpProfileConfigReq->heartbeatenable());
    }

    if(IwfSigtranSctpProfileConfigReq->has_heartbeattimeout())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"HEARTBEAT_TIMEOUT=%d,",IwfSigtranSctpProfileConfigReq->heartbeattimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->inittimeout())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"INIT_TIMEOUT=%d,",IwfSigtranSctpProfileConfigReq->inittimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_assocmaxattempt())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ASSOC_MAX_ATTEMPTS=%d,",IwfSigtranSctpProfileConfigReq->assocmaxattempt());
    }

    if(IwfSigtranSctpProfileConfigReq->has_maxattempt())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MAX_ATTEMPTS=%d,",IwfSigtranSctpProfileConfigReq->maxattempt());
    }

    if(IwfSigtranSctpProfileConfigReq->has_rtomax())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RTO_MAX=%d,",IwfSigtranSctpProfileConfigReq->rtomax());
    }

    if(IwfSigtranSctpProfileConfigReq->has_rtomin())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RTO_MIN=%d,",IwfSigtranSctpProfileConfigReq->rtomin());
    }

    if(IwfSigtranSctpProfileConfigReq->has_rtoinitial())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RTO_INITIAL=%d,",IwfSigtranSctpProfileConfigReq->rtoinitial());
    }

    if(IwfSigtranSctpProfileConfigReq->has_pathfailureretrycount())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PATH_FAILURE_RETRY_COUNT=%d,",IwfSigtranSctpProfileConfigReq->pathfailureretrycount());
    }

    if(IwfSigtranSctpProfileConfigReq->has_maxinstreams())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MAX_IN_STREAMS=%d,",IwfSigtranSctpProfileConfigReq->maxinstreams());
    }

    if(IwfSigtranSctpProfileConfigReq->has_numoutstreams())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"NUM_OUT_STREAMS=%d,",IwfSigtranSctpProfileConfigReq->numoutstreams());
    }

    if(IwfSigtranSctpProfileConfigReq->has_sendtimeout())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SEND_TIME_OUT=%d,",IwfSigtranSctpProfileConfigReq->sendtimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_receivetimeout())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RECEIVE_TIME_OUT=%d,",IwfSigtranSctpProfileConfigReq->receivetimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_shutdowntimeout())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SHUTDOWN_TIMEOUT=%d,",IwfSigtranSctpProfileConfigReq->shutdowntimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_pmtutimeout())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PMTU_TIMEOUT=%d,",IwfSigtranSctpProfileConfigReq->pmtutimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_cookielife())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"COOKIE_LIFE=%d,",IwfSigtranSctpProfileConfigReq->cookielife());
    }

    if(IwfSigtranSctpProfileConfigReq->has_sackdelay())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SACK_DELAY=%d,",IwfSigtranSctpProfileConfigReq->sackdelay());
    }

    if(IwfSigtranSctpProfileConfigReq->has_sendbufsize())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SEND_BUF_SIZE=%d,",IwfSigtranSctpProfileConfigReq->sendbufsize());
    }

    if(IwfSigtranSctpProfileConfigReq->has_recvbufsize())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RECV_BUF_SIZE=%d,",IwfSigtranSctpProfileConfigReq->recvbufsize());
    }

    if(IwfSigtranSctpProfileConfigReq->has_reconnecttimeout())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RECONNECT_TIMEOUT=%d,",IwfSigtranSctpProfileConfigReq->reconnecttimeout());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where IWF_SIGTRAN_SCTP_PROFILE_NAME='%s' ",IwfSigtranSctpProfileConfigReq->sctpprofilename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranSCTPProfileTPBQuery::sql_IWFSigtranSCTPProfile_Create_Delete_Query(IwfSigtranSctpProfileConfig *IwfSigtranSctpProfileConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_SIGTRAN_SCTP_PROFILE_TB where IWF_SIGTRAN_SCTP_PROFILE_NAME='%s' ",IwfSigtranSctpProfileConfigReq->sctpprofilename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSigtranSCTPProfileTPBQuery::sql_IWFSigtranSCTPProfile_Payload_Validation(IwfSigtranSctpProfileConfig *IwfSigtranSctpProfileConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(IwfSigtranSctpProfileConfigReq->has_sctpprofilename())
    {
        DLOG_ERROR("Primary Key IWF_SIGTRAN_SCTP_PROFILE_NAME is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranSCTPProfileTPBQuery::sql_IWFSigtranSCTPProfile_Create_Select_Query(IwfSigtranSctpProfileConfig *IwfSigtranSctpProfileConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SIGTRAN_SCTP_PROFILE_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfSigtranSctpProfileConfigReq->has_sctpprofileid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_SCTP_PROFILE_ID=%d and ",IwfSigtranSctpProfileConfigReq->sctpprofileid());
    }

    if(IwfSigtranSctpProfileConfigReq->has_sctpprofilename())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_SCTP_PROFILE_NAME='%s' and ",IwfSigtranSctpProfileConfigReq->sctpprofilename().c_str());
    }

    if(IwfSigtranSctpProfileConfigReq->has_heartbeatenable())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"HEARTBEAT_ENABLE=%d and ",IwfSigtranSctpProfileConfigReq->heartbeatenable());
    }

    if(IwfSigtranSctpProfileConfigReq->has_heartbeattimeout())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"HEARTBEAT_TIMEOUT=%d and ",IwfSigtranSctpProfileConfigReq->heartbeattimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_inittimeout())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"INIT_TIMEOUT=%d and ",IwfSigtranSctpProfileConfigReq->inittimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_assocmaxattempt())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ASSOC_MAX_ATTEMPTS=%d and ",IwfSigtranSctpProfileConfigReq->assocmaxattempt());
    }

    if(IwfSigtranSctpProfileConfigReq->has_maxattempt())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"MAX_ATTEMPTS=%d and ",IwfSigtranSctpProfileConfigReq->maxattempt());
    }

    if(IwfSigtranSctpProfileConfigReq->has_rtomax())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RTO_MAX=%d and ",IwfSigtranSctpProfileConfigReq->rtomax());
    }

    if(IwfSigtranSctpProfileConfigReq->has_rtomin())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RTO_MIN=%d and ",IwfSigtranSctpProfileConfigReq->rtomin());
    }

    if(IwfSigtranSctpProfileConfigReq->has_rtoinitial())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RTO_INITIAL=%d and ",IwfSigtranSctpProfileConfigReq->rtoinitial());
    }

    if(IwfSigtranSctpProfileConfigReq->has_pathfailureretrycount())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PATH_FAILURE_RETRY_COUNT=%d and ",IwfSigtranSctpProfileConfigReq->pathfailureretrycount());
    }

    if(IwfSigtranSctpProfileConfigReq->has_maxinstreams())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"MAX_IN_STREAMS=%d and ",IwfSigtranSctpProfileConfigReq->maxinstreams());
    }

    if(IwfSigtranSctpProfileConfigReq->has_numoutstreams())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NUM_OUT_STREAMS=%d and ",IwfSigtranSctpProfileConfigReq->numoutstreams());
    }

    if(IwfSigtranSctpProfileConfigReq->has_sendtimeout())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SEND_TIME_OUT=%d and ",IwfSigtranSctpProfileConfigReq->sendtimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_receivetimeout())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RECEIVE_TIME_OUT=%d and ",IwfSigtranSctpProfileConfigReq->receivetimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_shutdowntimeout())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SHUTDOWN_TIMEOUT=%d and ",IwfSigtranSctpProfileConfigReq->shutdowntimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_pmtutimeout())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PMTU_TIMEOUT=%d and ",IwfSigtranSctpProfileConfigReq->pmtutimeout());
    }

    if(IwfSigtranSctpProfileConfigReq->has_cookielife())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"COOKIE_LIFE=%d and ",IwfSigtranSctpProfileConfigReq->cookielife());
    }

    if(IwfSigtranSctpProfileConfigReq->has_sackdelay())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SACK_DELAY=%d and ",IwfSigtranSctpProfileConfigReq->sackdelay());
    }

    if(IwfSigtranSctpProfileConfigReq->has_sendbufsize())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SEND_BUF_SIZE=%d and ",IwfSigtranSctpProfileConfigReq->sendbufsize());
    }

    if(IwfSigtranSctpProfileConfigReq->has_recvbufsize())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RECV_BUF_SIZE=%d and ",IwfSigtranSctpProfileConfigReq->recvbufsize());
    }

    if(IwfSigtranSctpProfileConfigReq->has_reconnecttimeout())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RECONNECT_TIMEOUT=%d and ",IwfSigtranSctpProfileConfigReq->reconnecttimeout());
    }


    if(iFlag) 
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSigtranSCTPProfileTPBQuery::sql_IWFSigtranSCTPProfile_Check_All_Invalid(IwfSigtranSctpProfileConfig *IwfSigtranSctpProfileConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(IwfSigtranSctpProfileConfigReq->has_sctpprofilename())
    {
        return IWF_DB_FAIL;
    }   
    if(IwfSigtranSctpProfileConfigReq->has_heartbeatenable())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_heartbeattimeout())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_inittimeout())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_assocmaxattempt())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_maxattempt())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_rtomax())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_rtomin())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_rtoinitial())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_pathfailureretrycount())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_maxinstreams())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_numoutstreams())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_sendtimeout())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_receivetimeout())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_shutdowntimeout())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_pmtutimeout())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_cookielife())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_sackdelay())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_sendbufsize())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_recvbufsize())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpProfileConfigReq->has_reconnecttimeout())
    {
        return IWF_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
