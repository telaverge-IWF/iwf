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


void UserTPBQuery::sql_Role_Create_Validation_Query_for_Role(UserInfo *dreUserConfigReq,char *pStatement)
{

    ::Group* localGroup = dreUserConfigReq->mutable_usergroup();
    if(localGroup->has_groupname())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select ROLE_ID from ROLE_TB where ROLE = '%s'",localGroup->groupname().c_str());
    }

}


void UserTPBQuery::sql_User_Create_Check_Modifcation_Query(UserInfo *dreUserConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select Username from UserT where Username='%s' ",dreUserConfigReq->username().c_str());

}

void UserTPBQuery::sql_User_Create_Add_Query(UserInfo *dreUserConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into UserT "); 
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"(Username"); 
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",dreUserConfigReq->username().c_str());

    if(dreUserConfigReq->has_password())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",Password"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",?");
    }

    if(dreUserConfigReq->has_usergroup())
    {
        ::Group* localGroup = dreUserConfigReq->mutable_usergroup();
        if(localGroup->has_groupname())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",RoleID"); 
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select ROLE_ID from ROLE_TB where ROLE = '%s')",localGroup->groupname().c_str());
        }
    }


    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")"); 
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")"); 

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void UserTPBQuery::sql_User_Create_Delete_Query(UserInfo *dreUserConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from UserT where Username='%s' ",dreUserConfigReq->username().c_str()); 

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void UserTPBQuery::sql_User_Create_Select_Query(UserInfo *dreUserConfigReq,char *pStatement)
{

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from UserT inner join ROLE_TB on UserT.RoleID = ROLE_TB.ROLE_ID "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(dreUserConfigReq->has_username())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"Username='%s' and ",dreUserConfigReq->username().c_str());
    }


    if(dreUserConfigReq->has_password())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"Password=? and ");
    }

    if(dreUserConfigReq->has_usergroup())
    {
        ::Group* localGroup = dreUserConfigReq->mutable_usergroup();
        if(localGroup->has_groupname())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RoleID=(select ROLE_ID from ROLE_TB where ROLE = '%s') and ",localGroup->groupname().c_str());
        }
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void UserTPBQuery::sql_User_Create_Mod_Query(UserInfo *dreUserConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update UserT set "); 

    if(dreUserConfigReq->has_password())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"Password=?,");
    }

    if(dreUserConfigReq->has_usergroup())
    {
        ::Group* localGroup = dreUserConfigReq->mutable_usergroup();
        if(localGroup->has_groupname())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RoleID=(select ROLE_ID from ROLE_TB where ROLE = '%s'),",localGroup->groupname().c_str());
        }
    }


    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where Username='%s' ",dreUserConfigReq->username().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e UserTPBQuery::sql_User_Payload_Validation(UserInfo *dreUserConfigReq)
{
    if(!dreUserConfigReq->has_username())
    {
        DLOG_ERROR("Primary Key Username is not set in the request");
        return DRE_DB_FAIL; 
    }

    return DRE_DB_SUCCESS;
}

DbStatus_e UserTPBQuery::sql_User_Check_All_Invalid(UserInfo *dreUserConfigReq)
{

    if(dreUserConfigReq->has_password())
    {
        return DRE_DB_FAIL;
    }

    if(dreUserConfigReq->has_usergroup())
    {
        ::Group* localGroup = dreUserConfigReq->mutable_usergroup();
        if(localGroup->has_groupname())
        {
            return DRE_DB_FAIL;
        }
    }
    DLOG_INFO("In the Request, No Fields are Set for Operation");

    return DRE_DB_SUCCESS;
}
