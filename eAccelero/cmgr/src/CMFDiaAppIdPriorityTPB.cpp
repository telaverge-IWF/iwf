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


void CmfDiaAppIdPriorityTPBQuery::sql_AppIdPriority_Create_Check_Modifcation_Query(AppIdPriority *pAppIdPriorityReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pAppIdPriorityReq->has_appid())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select AUTO_APP_ID from CMF_DIA_APP_PRIORITY_TB where APP_ID=%d",pAppIdPriorityReq->appid());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfDiaAppIdPriorityTPBQuery::sql_AppIdPriority_Create_Add_Query(AppIdPriority *pAppIdPriorityReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into CMF_DIA_APP_PRIORITY_TB ");

    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(APP_ID");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(%d", pAppIdPriorityReq->appid());

    if(pAppIdPriorityReq->has_description())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",APP_NAME");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",pAppIdPriorityReq->description().c_str());
    }

    if(pAppIdPriorityReq->has_priority())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",PRIORITY");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",pAppIdPriorityReq->priority());
    }
    else
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",PRIORITY");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",AppIdPriority_PriorityStatus_HIGH);
    }

    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfDiaAppIdPriorityTPBQuery::sql_AppIdPriority_Create_Mod_Query(AppIdPriority *pAppIdPriorityReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update CMF_DIA_APP_PRIORITY_TB set ");

    if(pAppIdPriorityReq->has_description())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"APP_NAME='%s',",pAppIdPriorityReq->description().c_str());
    }
    if(pAppIdPriorityReq->has_priority())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"PRIORITY='%d',",pAppIdPriorityReq->priority());
    }
    else
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"PRIORITY=%d,",AppIdPriority_PriorityStatus_HIGH);
    }
    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where APP_ID=%d",pAppIdPriorityReq->appid());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfDiaAppIdPriorityTPBQuery::sql_AppIdPriority_Create_Delete_Query(AppIdPriority *pAppIdPriorityReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pAppIdPriorityReq->has_appid())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from CMF_DIA_APP_PRIORITY_TB where APP_ID=%d",pAppIdPriorityReq->appid());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CmfDiaAppIdPriorityTPBQuery::sql_AppIdPriority_Payload_Validation(AppIdPriority *pAppIdPriorityReq)
{
    if (!pAppIdPriorityReq->has_appid())
    {
        DLOG_ERROR("Primary Key appid is not set in the request");
        return ERR_MANDATORY_PARAM_REALMNAME_MISSING;
    }
    return DRE_DB_SUCCESS;
}

void CmfDiaAppIdPriorityTPBQuery::sql_AppIdPriority_Create_Select_Query(AppIdPriority *pAppIdPriorityReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from CMF_DIA_APP_PRIORITY_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pAppIdPriorityReq->has_appid())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"APP_ID=%d and ",pAppIdPriorityReq->appid());
    }
    if(pAppIdPriorityReq->has_description())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"APP_NAME='%s' and ",pAppIdPriorityReq->description().c_str());
    }
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CmfDiaAppIdPriorityTPBQuery::sql_AppIdPriority_Check_All_Invalid(AppIdPriority *pAppIdPriorityReq)
{
    return DRE_DB_SUCCESS;
}
