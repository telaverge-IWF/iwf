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

void RoleTPBQuery::sql_Role_Create_MaxId_Query(char *pStatement)
{
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select max(ROLE_ID) from ROLE_TB");
}


void RoleTPBQuery::sql_Role_Create_Validation_Query_for_User(Role *roleConfigReq,char *pStatement)
{
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select UserName from UserT where RoleID=(select ROLE_ID from ROLE_TB where ROLE='%s') ",roleConfigReq->rolename().c_str());
}

void RoleTPBQuery::sql_Role_Create_Check_Modifcation_Query(Role *roleConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select ROLE_ID from ROLE_TB where ROLE_ID=%d ",roleConfigReq->roleid());

}

void RoleTPBQuery::sql_Role_Create_Add_Query(Role *roleConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into ROLE_TB ");
    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),"(ROLE_ID");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),"(%d",roleConfigReq->roleid());

    if(roleConfigReq->has_rolename())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",ROLE");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",roleConfigReq->rolename().c_str());
    }

    if(roleConfigReq->has_rolestatus())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",ROLE_STATUS");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",roleConfigReq->rolestatus());
    }


    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void RoleTPBQuery::sql_Role_Create_Delete_Query(Role *roleConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from ROLE_TB where ROLE_ID=%d ",roleConfigReq->roleid());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void RoleTPBQuery::sql_Role_Create_Select_Query(Role *roleConfigReq,char *pStatement)
{

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from ROLE_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(roleConfigReq->has_roleid())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"ROLE_ID=%d and ",roleConfigReq->roleid());
    }

    if(roleConfigReq->has_rolename())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"ROLE='%s' and ",roleConfigReq->rolename().c_str());
    }

    if(roleConfigReq->has_rolestatus())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"ROLE_STATUS=%d and ",roleConfigReq->rolestatus());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void RoleTPBQuery::sql_Role_Create_Mod_Query(Role *roleConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update ROLE_TB set ");


    if(roleConfigReq->has_rolename())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"ROLE='%s',",roleConfigReq->rolename().c_str());
    }


    if(roleConfigReq->has_rolestatus())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"ROLE_STATUS=%d,",roleConfigReq->rolestatus());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where ROLE_ID=%d ",roleConfigReq->roleid());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e RoleTPBQuery::sql_Role_Payload_Validation(Role *roleConfigReq)
{
    if(!roleConfigReq->has_rolename())
    {
        DLOG_ERROR("Primary Key ROLE is not set in the request");
        return DRE_DB_FAIL;
    }

    return DRE_DB_SUCCESS;
}

DbStatus_e RoleTPBQuery::sql_Role_Check_All_Invalid(Role *roleConfigReq)
{

    if(roleConfigReq->has_rolestatus())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");

    return DRE_DB_SUCCESS;
}
