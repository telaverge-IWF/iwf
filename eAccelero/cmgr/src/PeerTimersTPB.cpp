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
void PeerTimersTPBQuery::sql_PeerTimers_Create_Check_Modifcation_Query(PeerConfig *drePeerTimersConfigReq,char *pStatement) 
{
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PeerHostIdentity, RealmName from  PeerTimersT where PeerHostIdentity='%s' and RealmName='%s'",drePeerTimersConfigReq->peerhostname().c_str(),drePeerTimersConfigReq->realm().c_str());   
}

void PeerTimersTPBQuery::sql_PeerTimers_Create_Add_Query(PeerConfig *drePeerTimersConfigReq,char *pStatement)   
{
    char sFieldName[MAX_STATEMENT_SIZE]     = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into PeerTimersT "); 

    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(PeerHostIdentity,RealmName");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s','%s'",drePeerTimersConfigReq->peerhostname().c_str(),drePeerTimersConfigReq->realm().c_str());

    if(drePeerTimersConfigReq->has_watchdogtimer())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",WdVal");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",drePeerTimersConfigReq->watchdogtimer());
    }

    if(drePeerTimersConfigReq->has_tctimerval())///////////// Not present in Design Model.
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",TcVal");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",drePeerTimersConfigReq->tctimerval());
    }

    if(drePeerTimersConfigReq->has_expirytimer())/////////////// Not present in Design Model.
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",Eval");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",drePeerTimersConfigReq->expirytimer());
    }

    if(drePeerTimersConfigReq->has_busyreconnecttimerval())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",BusyReconnectTimer");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",drePeerTimersConfigReq->busyreconnecttimerval());
    }

    if(drePeerTimersConfigReq->has_donotwanttotalktoyoutimerval())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",DoNotwantToTalkToYouTimer");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",drePeerTimersConfigReq->donotwanttotalktoyoutimerval());
    }
    /*
    if(drePeerTimersConfigReq->has_issupportdisconnectcause())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IsSupportDisconnectCause");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",drePeerTimersConfigReq->issupportdisconnectcause());
    }
    */
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" < %s ",__FUNCTION__);
}   

void PeerTimersTPBQuery::sql_PeerTimers_Create_Mod_Query(PeerConfig *drePeerTimersConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update PeerTimersT set "); 

    if(drePeerTimersConfigReq->has_watchdogtimer())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"WdVal=%d,",drePeerTimersConfigReq->watchdogtimer());

    }
    if(drePeerTimersConfigReq->has_tctimerval())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TcVal=%d,",drePeerTimersConfigReq->tctimerval());
    }

    if(drePeerTimersConfigReq->has_expirytimer())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"Eval=%d,",drePeerTimersConfigReq->expirytimer());
    }

    if(drePeerTimersConfigReq->has_busyreconnecttimerval())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"BusyReconnectTimer=%d,",drePeerTimersConfigReq->busyreconnecttimerval());
    }
    if(drePeerTimersConfigReq->has_donotwanttotalktoyoutimerval())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"DoNotwantToTalkToYouTimer=%d,",drePeerTimersConfigReq->donotwanttotalktoyoutimerval());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where PeerHostIdentity='%s' and RealmName='%s'",drePeerTimersConfigReq->peerhostname().c_str(),drePeerTimersConfigReq->realm().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);


}


void PeerTimersTPBQuery::sql_PeerTimers_Create_Delete_Query(PeerConfig *drePeerTimersConfigReq,char *pStatement)    
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from PeerTimersT where PeerHostIdentity='%s' and RealmName='%s'",drePeerTimersConfigReq->peerhostname().c_str(),drePeerTimersConfigReq->realm().c_str()); 

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e PeerTimersTPBQuery::sql_PeerTimers_Payload_Validation(PeerConfig *drePeerTimersConfigReq)
{
    if(!drePeerTimersConfigReq->has_peerhostname())
    {
        DLOG_ERROR("Primary Key Hostname is not set in the request");
        return ERR_MANDATORY_PARAM_PEERNAME_MISSING;    
    }

    if(!drePeerTimersConfigReq->has_realm())
    {
        DLOG_ERROR("Primary Key Realm is not set in the request");
        return ERR_MANDATORY_PARAM_REALMNAME_MISSING;   
    }


    return DRE_DB_SUCCESS;
}

void PeerTimersTPBQuery::sql_PeerTimers_Create_Select_Query(PeerConfig *drePeerTimersConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from PeerTimersT "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(drePeerTimersConfigReq->has_peerhostname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PeerHostIdentity='%s' and ",drePeerTimersConfigReq->peerhostname().c_str());
    }

    if(drePeerTimersConfigReq->has_realm())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RealmName='%s' and ",drePeerTimersConfigReq->realm().c_str());
    }

    if(drePeerTimersConfigReq->has_watchdogtimer())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"WdVal=%d and ",drePeerTimersConfigReq->watchdogtimer());
    }

    if(drePeerTimersConfigReq->has_tctimerval())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TcVal=%d and ",drePeerTimersConfigReq->tctimerval());
    }

    if(drePeerTimersConfigReq->has_expirytimer())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"Eval=%d and ",drePeerTimersConfigReq->expirytimer());
    }

    if(drePeerTimersConfigReq->has_busyreconnecttimerval())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"BusyReconnectTimer=%d and ",drePeerTimersConfigReq->busyreconnecttimerval());
    }

    if(drePeerTimersConfigReq->has_donotwanttotalktoyoutimerval())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"DoNotwantToTalkToYouTimer=%d and ",drePeerTimersConfigReq->donotwanttotalktoyoutimerval());
    }
    /*
    if(drePeerTimersConfigReq->has_issupportdisconnectcause())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IsSupportDisconnectCause=%d and ",drePeerTimersConfigReq->issupportdisconnectcause());
    }
    */
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }


    DLOG_NONE(" > %s ",__FUNCTION__);
}

DbStatus_e PeerTimersTPBQuery::sql_PeerTimers_Check_All_Invalid(PeerConfig *drePeerTimersConfigReq)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(drePeerTimersConfigReq->has_watchdogtimer())
    {
        return DRE_DB_FAIL;
    }

    if(drePeerTimersConfigReq->has_tctimerval())
    {
        return DRE_DB_FAIL;
    }

    if(drePeerTimersConfigReq->has_expirytimer())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    DLOG_NONE(" > %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}
