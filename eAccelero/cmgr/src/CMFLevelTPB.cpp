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

void CmfLevelTPBQuery::sql_CmfLevel_Create_Check_Modifcation_Query(CMFLevel *pCMFLevelReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pCMFLevelReq->has_level())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select LEVEL_ID from CMF_LEVEL_TB where LEVEL_NAME='%s'",pCMFLevelReq->level().c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfLevelTPBQuery::sql_CmfLevel_Create_Add_Query(CMFLevel *pCMFLevelReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into CMF_LEVEL_TB ");
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(LEVEL_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'", pCMFLevelReq->level().c_str());

    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfLevelTPBQuery::sql_CmfLevel_Create_Mod_Query(CMFLevel *pCMFLevelReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
#if 0
    snprintf(pStatement,MAX_STATEMENT_SIZE,"update CMF_LEVEL_TB set ");

    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where LEVEL_NAME='%s'",pCMFLevelReq->level().c_str());
#endif
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfLevelTPBQuery::sql_CmfLevel_Create_Delete_Query(CMFLevel *pCMFLevelReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pCMFLevelReq->has_levelid())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from CMF_LEVEL_TB where LEVEL_ID=%d",pCMFLevelReq->levelid());
    }
    else if(pCMFLevelReq->has_level())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from CMF_LEVEL_TB where LEVEL_NAME='%s'",pCMFLevelReq->level().c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CmfLevelTPBQuery::sql_CmfLevel_Payload_Validation(CMFLevel *pCMFLevelReq)
{
    if (!pCMFLevelReq->has_level())
    {
        DLOG_ERROR("Primary Key Realm is not set in the request");
        return ERR_MANDATORY_PARAM_REALMNAME_MISSING;
    }
    return DRE_DB_SUCCESS;
}

void CmfLevelTPBQuery::sql_CmfLevel_Create_Select_Query(CMFLevel *pCMFLevelReq,char *pStatement)
{

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from CMF_LEVEL_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pCMFLevelReq->has_levelid())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"LEVEL_ID=%d and ",pCMFLevelReq->levelid());
    }
    if(pCMFLevelReq->has_level())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"LEVEL_NAME='%s' and ",pCMFLevelReq->level().c_str());
    }
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CmfLevelTPBQuery::sql_CmfLevel_Check_All_Invalid(CMFLevel *pCMFLevelReq)
{
    return DRE_DB_SUCCESS;
}

