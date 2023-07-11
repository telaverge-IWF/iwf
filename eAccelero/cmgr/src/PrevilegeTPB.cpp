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

void PrevilegeTPBQuery::sql_Previlege_Create_Check_Modifcation_Query(Previlage *previlageConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PRIVILEGE_ID from PRIVILEGE_TB where PRIVILEGE_NAME='%s' ",previlageConfigReq->previlagename().c_str());

}

void PrevilegeTPBQuery::sql_Previlege_Create_Add_Query(Previlage *previlageConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into PRIVILEGE_TB ");
    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),"(PRIVILEGE_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",previlageConfigReq->previlagename().c_str());

    if(previlageConfigReq->has_previlagedesc())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",PRIVILEGE_DISCRIPTION");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",previlageConfigReq->previlagedesc().c_str());
    }


    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void PrevilegeTPBQuery::sql_Previlege_Create_Delete_Query(Previlage *previlageConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from PRIVILEGE_TB where PRIVILEGE_NAME='%s' ",previlageConfigReq->previlagename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void PrevilegeTPBQuery::sql_Previlege_Create_Select_Query(Previlage *previlageConfigReq,char *pStatement)
{

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from PRIVILEGE_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(previlageConfigReq->has_previlageid())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"PRIVILEGE_ID=%d and ",previlageConfigReq->previlageid());
    }

    if(previlageConfigReq->has_previlagename())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"PRIVILEGE_NAME='%s' and ",previlageConfigReq->previlagename().c_str());
    }

    if(previlageConfigReq->has_previlagedesc())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"PRIVILEGE_DISCRIPTION='%s' and ",previlageConfigReq->previlagedesc().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void PrevilegeTPBQuery::sql_Previlege_Create_Mod_Query(Previlage *previlageConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update PRIVILEGE_TB set ");


    if(previlageConfigReq->has_previlagedesc())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"PRIVILEGE_DISCRIPTION='%s',",previlageConfigReq->previlagedesc().c_str());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where PRIVILEGE_NAME='%s' ",previlageConfigReq->previlagename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e PrevilegeTPBQuery::sql_Previlege_Payload_Validation(Previlage *previlageConfigReq)
{
    if(!previlageConfigReq->has_previlagename())
    {
        DLOG_ERROR("Primary Key preivlage is not set in the request");
        return DRE_DB_FAIL;
    }

    return DRE_DB_SUCCESS;
}

DbStatus_e PrevilegeTPBQuery::sql_Previlege_Check_All_Invalid(Previlage *previlageConfigReq)
{

    if(previlageConfigReq->has_previlagedesc())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");

    return DRE_DB_SUCCESS;
}
