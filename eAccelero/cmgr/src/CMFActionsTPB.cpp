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

void CmfActionTPBQuery::sql_CmfAction_Create_Check_Modifcation_Query(CMFAction *pCMFActionReq,char *pStatement)
{
   DLOG_NONE(" > %s ",__FUNCTION__);

    if(pCMFActionReq->has_action())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select ACTION_ID from CMF_ACTIONS_TB where ACTION_NAME='%s'",pCMFActionReq->action().c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfActionTPBQuery::sql_CmfAction_Create_Add_Query(CMFAction *pCMFActionReq,char *pStatement)
{
   char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into CMF_ACTIONS_TB ");
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(ACTION_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'", pCMFActionReq->action().c_str());

    if(pCMFActionReq->has_description())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",ACTION_DESCRIPTION");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",pCMFActionReq->description().c_str());
    }

    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfActionTPBQuery::sql_CmfAction_Create_Mod_Query(CMFAction *pCMFActionReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update CMF_ACTIONS_TB set ");

    if(pCMFActionReq->has_description())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"ACTION_DESCRIPTION='%s',",pCMFActionReq->description().c_str());
    }
    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where ACTION_NAME='%s'",pCMFActionReq->action().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfActionTPBQuery::sql_CmfAction_Create_Delete_Query(CMFAction *pCMFActionReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pCMFActionReq->has_action())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from CMF_ACTIONS_TB where ACTION_NAME='%s'",pCMFActionReq->action().c_str());
    }
    else if(pCMFActionReq->has_actionid())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from CMF_ACTIONS_TB where ACTION_ID=%d",pCMFActionReq->actionid());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CmfActionTPBQuery::sql_CmfAction_Payload_Validation(CMFAction *pCMFActionReq)
{
    if (!pCMFActionReq->has_action())
    {
        DLOG_ERROR("Primary Key action-name is not set in the request");
        return ERR_MANDATORY_PARAM_REALMNAME_MISSING;
    }
    return DRE_DB_SUCCESS;
}

void CmfActionTPBQuery::sql_CmfAction_Create_Select_Query(CMFAction *pCMFActionReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from CMF_ACTIONS_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pCMFActionReq->has_actionid())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"ACTION_ID=%d and ",pCMFActionReq->actionid());
    }
    if(pCMFActionReq->has_action())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"ACTION_NAME='%s' and ",pCMFActionReq->action().c_str());
    }
    if(pCMFActionReq->has_description())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"ACTION_DESCRIPTION='%s' and ",pCMFActionReq->description().c_str());
    }
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CmfActionTPBQuery::sql_CmfAction_Check_All_Invalid(CMFAction *pCMFActionReq)
{
    return DRE_DB_SUCCESS;
}

