/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
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

void CmfTriggerTPBQuery::sql_CmfTrigger_Create_Check_Modifcation_Query(CMFTrigger *pCMFTriggerReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pCMFTriggerReq->has_trigger())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select TRIGGER_ID from CMF_TRIGGERS_TB where TRIGGER_NAME='%s'",pCMFTriggerReq->trigger().c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfTriggerTPBQuery::sql_CmfTrigger_Create_Add_Query(CMFTrigger *pCMFTriggerReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into CMF_TRIGGERS_TB ");

    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(TRIGGER_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'", pCMFTriggerReq->trigger().c_str());

    if(pCMFTriggerReq->has_triggervalue())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",TRIGGER_VALUE");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",pCMFTriggerReq->triggervalue());
    }
    if(pCMFTriggerReq->has_description())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",TRIGGER_DESCRIPTION");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",pCMFTriggerReq->description().c_str());
    }

    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfTriggerTPBQuery::sql_CmfTrigger_Create_Mod_Query(CMFTrigger *pCMFTriggerReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update CMF_TRIGGERS_TB set ");

    if(pCMFTriggerReq->has_triggervalue())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"TRIGGER_VALUE=%d,",pCMFTriggerReq->triggervalue());
    }
    if(pCMFTriggerReq->has_description())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"TRIGGER_DESCRIPTION='%s',",pCMFTriggerReq->description().c_str());
    }
    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where TRIGGER_NAME='%s'",pCMFTriggerReq->trigger().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfTriggerTPBQuery::sql_CmfTrigger_Create_Delete_Query(CMFTrigger *pCMFTriggerReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pCMFTriggerReq->has_trigger())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from CMF_TRIGGERS_TB where TRIGGER_NAME='%s'",pCMFTriggerReq->trigger().c_str());
    }
    else if(pCMFTriggerReq->has_triggerid())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from CMF_TRIGGERS_TB where TRIGGER_ID=%d",pCMFTriggerReq->triggerid());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CmfTriggerTPBQuery::sql_CmfTrigger_Payload_Validation(CMFTrigger *pCMFTriggerReq)
{
    if (!pCMFTriggerReq->has_trigger())
    {
        DLOG_ERROR("Primary Key Trigger-name is not set in the request");
        return ERR_MANDATORY_PARAM_REALMNAME_MISSING;
    }
    return DRE_DB_SUCCESS;
}

void CmfTriggerTPBQuery::sql_CmfTrigger_Create_Select_Query(CMFTrigger *pCMFTriggerReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from CMF_TRIGGERS_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pCMFTriggerReq->has_triggerid())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"TRIGGER_ID=%d and ",pCMFTriggerReq->triggerid());
    }
    if(pCMFTriggerReq->has_trigger())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"TRIGGER_NAME='%s' and ",pCMFTriggerReq->trigger().c_str());
    }
    if(pCMFTriggerReq->has_triggervalue())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"TRIGGER_VALUE=%d and ",pCMFTriggerReq->triggervalue());
    }
    if(pCMFTriggerReq->has_description())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"TRIGGER_DESCRIPTION='%s' and ",pCMFTriggerReq->description().c_str());
    }
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CmfTriggerTPBQuery::sql_CmfTrigger_Check_All_Invalid(CMFTrigger *pCMFTriggerReq)
{
    return DRE_DB_SUCCESS;
}
