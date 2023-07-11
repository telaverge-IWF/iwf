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

void UserDetailTPBQuery::sql_UserDetails_Create_MaxId_Query(char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select max(UserID) from UserT ");

}


void UserDetailTPBQuery::sql_RoleDetails_Create_Validation_Query_for_Role(UserDetail *dreUserConfigReq,char *pStatement)
{

    ::Role* localRole= dreUserConfigReq->mutable_roledetails();
    if(localRole->has_rolename())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select ROLE_ID from ROLE_TB where ROLE = '%s'",localRole->rolename().c_str());
    }

}


void UserDetailTPBQuery::sql_UserDetails_Create_Check_Modifcation_Query(UserDetail *dreUserConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select UserName from UserT where UserID=%d ",dreUserConfigReq->userid());

}

void UserDetailTPBQuery::sql_UserDetails_Create_Add_Query(UserDetail *dreUserConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into UserT ");
    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),"(UserID");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(%d",dreUserConfigReq->userid());

    if(dreUserConfigReq->has_username())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",UserName");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",dreUserConfigReq->username().c_str());
    }

    if(dreUserConfigReq->has_password())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",Password");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",?");
    }

    if(dreUserConfigReq->has_firstname())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",FirstName");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",dreUserConfigReq->firstname().c_str());
    }

    if(dreUserConfigReq->has_lastname())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",LastName");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",dreUserConfigReq->lastname().c_str());
    }

    if(dreUserConfigReq->has_email())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",Email");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",dreUserConfigReq->email().c_str());
    }

    if(dreUserConfigReq->has_userstatus())
    {
        snprintf(sFieldName+ strlen(sFieldName),MAX_STATEMENT_SIZE,",status");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",dreUserConfigReq->userstatus());
    }

    if(dreUserConfigReq->has_usertype())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",UserType");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",dreUserConfigReq->usertype().c_str());
    }

    if(dreUserConfigReq->has_lastlogin())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",LastLogin");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",dreUserConfigReq->lastlogin().c_str());
    }

    if(dreUserConfigReq->has_createdby())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",CreatedBy");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",dreUserConfigReq->createdbyid());
    }

    if(dreUserConfigReq->has_creationtime())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",CreationTime");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",dreUserConfigReq->creationtime().c_str());
    }

    if(dreUserConfigReq->has_modifiedby())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",ModifiedBy");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue) ,MAX_STATEMENT_SIZE,",%d",dreUserConfigReq->modifiedbyid());
    }

    if(dreUserConfigReq->has_modificationtime())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",ModificationTime");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",dreUserConfigReq->modificationtime().c_str());
    }


    if(dreUserConfigReq->has_roledetails())
    {
        ::Role* localrole = dreUserConfigReq->mutable_roledetails();
        if(localrole->has_rolename())
        {
            if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
                snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",RoleID");
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",(select ROLE_ID from ROLE_TB where ROLE = '%s')",localrole->rolename().c_str());
        }
    }

    if(dreUserConfigReq->has_passwordstatus())
    {
        snprintf(sFieldName+ strlen(sFieldName),MAX_STATEMENT_SIZE,",PasswordStatus");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",dreUserConfigReq->passwordstatus());
    }


    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void UserDetailTPBQuery::sql_UserDetails_Create_Delete_Query(UserDetail *dreUserConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from UserT where UserID=%d ",dreUserConfigReq->userid());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void UserDetailTPBQuery::sql_UserDetails_Create_Select_Query(UserDetail *dreUserConfigReq,char *pStatement)
{

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from UserT ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(dreUserConfigReq->has_username())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"UserName='%s' and ",dreUserConfigReq->username().c_str());
    }


    if(dreUserConfigReq->has_password())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"Password=? and ");
    }

    if(dreUserConfigReq->has_firstname())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"FirstName='%s' and ",dreUserConfigReq->firstname().c_str());
    }

    if(dreUserConfigReq->has_lastname())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"LastName='%s' and ",dreUserConfigReq->lastname().c_str());
    }

    if(dreUserConfigReq->has_email())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"Email='%s' and ",dreUserConfigReq->email().c_str());
    }

    if(dreUserConfigReq->has_userid())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"UserID=%d and ",dreUserConfigReq->userid());
    }

    if(dreUserConfigReq->has_userstatus())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"status=%d and ",dreUserConfigReq->userstatus());
    }

    if(dreUserConfigReq->has_usertype())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"UserType='%s' and ",dreUserConfigReq->usertype().c_str());
    }

    if(dreUserConfigReq->has_lastlogin())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"LastLogin='%s' and ",dreUserConfigReq->lastlogin().c_str());
    }

    if(dreUserConfigReq->has_createdby())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"CreatedBy=%d and ",dreUserConfigReq->createdbyid());
    }

    if(dreUserConfigReq->has_creationtime())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"CreationTime='%s' and ",dreUserConfigReq->creationtime().c_str());
    }

    if(dreUserConfigReq->has_modifiedby())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"ModifiedBy=%d and ",dreUserConfigReq->modifiedbyid());
    }

    if(dreUserConfigReq->has_modificationtime())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"ModificationTime='%s' and ",dreUserConfigReq->modificationtime().c_str());
    }

    if(dreUserConfigReq->has_roledetails())
    {
        ::Role* localrole = dreUserConfigReq->mutable_roledetails();
        if(localrole->has_rolename())
        {
            iFlag = 1;
            if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
                snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"RoleID=(select ROLE_ID from ROLE_TB where ROLE = '%s') and ",localrole->rolename().c_str());
        }
    }

    if(dreUserConfigReq->has_passwordstatus())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"PasswordStatus=%d and ",dreUserConfigReq->passwordstatus());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void UserDetailTPBQuery::sql_UserDetails_Create_Mod_Query(UserDetail *dreUserConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update UserT set ");

    if(dreUserConfigReq->has_password())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"Password=?,");
    }

    if(dreUserConfigReq->has_firstname())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"FirstName='%s',",dreUserConfigReq->firstname().c_str());
    }

    if(dreUserConfigReq->has_lastname())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"LastName='%s',",dreUserConfigReq->lastname().c_str());
    }

    if(dreUserConfigReq->has_email())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"Email='%s',",dreUserConfigReq->email().c_str());
    }

    if(dreUserConfigReq->has_userstatus())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"status=%d,",dreUserConfigReq->userstatus());
    }

    if(dreUserConfigReq->has_username())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"UserName='%s',",dreUserConfigReq->username().c_str());
    }

    if(dreUserConfigReq->has_usertype())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"UserType='%s',",dreUserConfigReq->usertype().c_str());
    }

    if(dreUserConfigReq->has_lastlogin())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"LastLogin='%s',",dreUserConfigReq->lastlogin().c_str());
    }

    if(dreUserConfigReq->has_createdby())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"CreatedBy=%d,",dreUserConfigReq->createdbyid());
    }

    if(dreUserConfigReq->has_creationtime())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"CreationTime='%s',",dreUserConfigReq->creationtime().c_str());
    }

    if(dreUserConfigReq->has_modifiedby())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"ModifiedBy=%d,",dreUserConfigReq->modifiedbyid());
    }

    if(dreUserConfigReq->has_modificationtime())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"ModificationTime='%s',",dreUserConfigReq->modificationtime().c_str());
    }

    if(dreUserConfigReq->has_roledetails())
    {
        ::Role* localrole = dreUserConfigReq->mutable_roledetails();
        if(localrole->has_rolename())
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"RoleID=(select ROLE_ID from ROLE_TB where ROLE = '%s'),",localrole->rolename().c_str());
        }
    }

    if(dreUserConfigReq->has_passwordstatus())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"PasswordStatus=%d,",dreUserConfigReq->passwordstatus());
    }



    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where UserID=%d ",dreUserConfigReq->userid());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e UserDetailTPBQuery::sql_UserDetails_Payload_Validation(UserDetail *dreUserConfigReq)
{
    if(!dreUserConfigReq->has_userid())
    {
        DLOG_ERROR("Primary Key Userid is not set in the request");
        return DRE_DB_FAIL;
    }

    return DRE_DB_SUCCESS;
}

DbStatus_e UserDetailTPBQuery::sql_UserDetails_Check_All_Invalid(UserDetail *dreUserConfigReq)
{

    if(dreUserConfigReq->has_password())
    {
        return DRE_DB_FAIL;
    }

    if(dreUserConfigReq->has_roledetails())
    {
        ::Role* localrole = dreUserConfigReq->mutable_roledetails();
        if(localrole->has_rolename())
        {
            return DRE_DB_FAIL;
        }
    }
    DLOG_INFO("In the Request, No Fields are Set for Operation");

    return DRE_DB_SUCCESS;
}
