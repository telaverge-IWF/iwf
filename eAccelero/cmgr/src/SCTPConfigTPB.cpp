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

void SCTPConfigTPBQuery::sql_SCTPConfig_Create_Check_Modifcation_Query(SctpProtocol *SctpProtocolReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);


    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from SCTP_CONFIG ");

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void SCTPConfigTPBQuery::sql_SCTPConfig_Create_Add_Query(SctpProtocol *SctpProtocolReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into SCTP_CONFIG "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"("); 
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");


    if(SctpProtocolReq->has_heartbeatenable())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"HEARTBEAT_ENABLE,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",SctpProtocolReq->heartbeatenable());
    }

    if(SctpProtocolReq->has_hearbeattimeout())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"HEARTBEAT_TIMEOUT,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",SctpProtocolReq->hearbeattimeout());
    }


    if(SctpProtocolReq->has_initialtimeout())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",INIT_TIMEOUT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",SctpProtocolReq->initialtimeout());
    }


    if(SctpProtocolReq->has_maximumattempts())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ASSOC_MAX_ATTEMPTS");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",SctpProtocolReq->maximumattempts());
    }


    if(SctpProtocolReq->has_rtomaximum())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",RTO_MAX");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",SctpProtocolReq->rtomaximum());
    }


    if(SctpProtocolReq->has_rtominimum())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",RTO_MIN");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",SctpProtocolReq->rtominimum());
    }


    if(SctpProtocolReq->has_rtoinitial())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",RTO_INITIAL");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",SctpProtocolReq->rtoinitial());
    }


    if(SctpProtocolReq->has_pathfailretrycount())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PATH_FAILURE_RETRY_COUNT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",SctpProtocolReq->pathfailretrycount());
    }

    sFieldName[strlen(sFieldName) - 1] = ' ';
    sFieldValue[strlen(sFieldValue) - 1] = ' ';

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" < %s ",__FUNCTION__);


}

void SCTPConfigTPBQuery::sql_SCTPConfig_Create_Delete_Query(SctpProtocol *SctpProtocolReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from SCTP_CONFIG "); 

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void SCTPConfigTPBQuery::sql_SCTPConfig_Create_Mod_Query(SctpProtocol *SctpProtocolReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update SCTP_CONFIG set "); 


    if(SctpProtocolReq->has_heartbeatenable())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"HEARTBEAT_ENABLE=%d,",SctpProtocolReq->heartbeatenable());
    }

    if(SctpProtocolReq->has_hearbeattimeout())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"HEARTBEAT_TIMEOUT=%d,",SctpProtocolReq->hearbeattimeout());
    }

    if(SctpProtocolReq->has_initialtimeout())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"INIT_TIMEOUT=%d,",SctpProtocolReq->initialtimeout());
    }

    if(SctpProtocolReq->has_maximumattempts())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ASSOC_MAX_ATTEMPTS=%d,",SctpProtocolReq->maximumattempts());
    }

    if(SctpProtocolReq->has_rtomaximum())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RTO_MAX=%d,",SctpProtocolReq->rtomaximum());
    }

    if(SctpProtocolReq->has_rtominimum())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RTO_MIN=%d,",SctpProtocolReq->rtominimum());
    }

    if(SctpProtocolReq->has_rtoinitial())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RTO_INITIAL=%d,",SctpProtocolReq->rtoinitial());
    }

    if(SctpProtocolReq->has_pathfailretrycount())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PATH_FAILURE_RETRY_COUNT=%d,",SctpProtocolReq->pathfailretrycount());
    }


    pStatement[strlen(pStatement) -1] = ' ';

    //  snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where SCTP_CONFIG_ID=%d",SctpProtocolReq->realmname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e SCTPConfigTPBQuery::sql_SCTPConfig_Payload_Validation(SctpProtocol *SctpProtocolReq)
{
#if 0
    if (!SctpProtocolReq->has_realmname())
    {
        DLOG_ERROR("Primary Key SCTP Config Id is not set in the request");
        return ERR_REALM_MANDATORY_PARAM_SCTP_CONFIG_ID_MISSING;    
    }
#endif
    return DRE_DB_SUCCESS;
}

void SCTPConfigTPBQuery::sql_SCTPConfig_Create_Select_Query(SctpProtocol *SctpProtocolReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from SCTP_CONFIG"); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);
#if 0
    if(SctpProtocolReq->has_enableproxyinfoavp())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SCTP_CONFIG_ID=%d and ",SctpProtocolReq->enableproxyinfoavp());
    }
#endif
    if(SctpProtocolReq->has_heartbeatenable())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"HEARTBEAT_ENABLE=%d and ",SctpProtocolReq->heartbeatenable());
    }

    if(SctpProtocolReq->has_hearbeattimeout())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"HEARTBEAT_TIMEOUT=%d and ",SctpProtocolReq->hearbeattimeout());
    }

    if(SctpProtocolReq->has_initialtimeout())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"INIT_TIMEOUT=%d and ",SctpProtocolReq->initialtimeout());
    }

    if(SctpProtocolReq->has_maximumattempts())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ASSOC_MAX_ATTEMPTS=%d and ",SctpProtocolReq->maximumattempts());
    }

    if(SctpProtocolReq->has_rtomaximum())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RTO_MAX=%d and ",SctpProtocolReq->rtomaximum());
    }

    if(SctpProtocolReq->has_rtominimum())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RTO_MIN=%d and ",SctpProtocolReq->rtominimum());
    }

    if(SctpProtocolReq->has_rtoinitial())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RTO_INITIAL=%d and ",SctpProtocolReq->rtoinitial());
    }

    if(SctpProtocolReq->has_pathfailretrycount())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PATH_FAILURE_RETRY_COUNT=%d and ",SctpProtocolReq->pathfailretrycount());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }


    DLOG_NONE(" < %s ",__FUNCTION__);

}

DbStatus_e SCTPConfigTPBQuery::sql_SCTPConfig_Check_All_Invalid(SctpProtocol *SctpProtocolReq)
{


    if(SctpProtocolReq->has_heartbeatenable())
    {
        return DRE_DB_FAIL;
    }

    if(SctpProtocolReq->has_hearbeattimeout())
    {
        return DRE_DB_FAIL;
    }

    if(SctpProtocolReq->has_initialtimeout())
    {
        return DRE_DB_FAIL;
    }

    if(SctpProtocolReq->has_maximumattempts())
    {
        return DRE_DB_FAIL;
    }

    if(SctpProtocolReq->has_rtomaximum())
    {
        return DRE_DB_FAIL;
    }

    if(SctpProtocolReq->has_rtominimum())
    {
        return DRE_DB_FAIL;
    }

    if(SctpProtocolReq->has_rtoinitial())
    {
        return DRE_DB_FAIL;
    }

    if(SctpProtocolReq->has_pathfailretrycount())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
