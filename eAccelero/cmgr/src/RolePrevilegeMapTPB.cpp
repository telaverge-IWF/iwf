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

void RolePrevilegeMapTPBQuery::sql_RolePrevilegeMap_Create_Check_Modifcation_Query(Role *roleConfigReq,char *pStatement,int iIndex)
{
    Previlage *pPrevilage = NULL;
    Previlages *localPrevilages = roleConfigReq->mutable_previlagesdetails();
    DLOG_DEBUG("Previlages->previlageinfo_size() = %d, iIndex = %d",localPrevilages->previlageinfo_size(),iIndex);

    if(localPrevilages->previlageinfo_size() > iIndex && iIndex > -1)
    {
        pPrevilage = localPrevilages->mutable_previlageinfo(iIndex);
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select ROLE_ID from MAP_ROLE_PRIVELEGE_TB where ROLE_ID=(select ROLE_ID from ROLE_TB where ROLE='%s') and PRIVILEGE_ID=(select PRIVILEGE_ID from PRIVILEGE_TB where PRIVILEGE_NAME='%s')",roleConfigReq->rolename().c_str(),pPrevilage->previlagename().c_str());
    }
    else
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select ROLE_ID from MAP_ROLE_PRIVELEGE_TB where ROLE_ID=(select ROLE_ID from ROLE_TB where ROLE ='%s') ",roleConfigReq->rolename().c_str());
    }

}

void RolePrevilegeMapTPBQuery::sql_RolePrevilegeMap_Create_Add_Query(Role *roleConfigReq,char *pStatement,int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    Previlage *pPrevilage = NULL;
    Previlages *localPrevilages = roleConfigReq->mutable_previlagesdetails();
    DLOG_DEBUG("Previlages->previlageinfo_size() = %d, iIndex = %d",localPrevilages->previlageinfo_size(),iIndex);

    if(localPrevilages->previlageinfo_size() > iIndex && iIndex > -1)
    {
        pPrevilage = localPrevilages->mutable_previlageinfo(iIndex);
    }
    else
    {
        DLOG_WARNING("pPrevilage Object  will be NULL, localPrevilages->previlageinfo_size() = %d,iIndex = %d",localPrevilages->previlageinfo_size(),iIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }
    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into MAP_ROLE_PRIVELEGE_TB ");
    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),"(ROLE_ID");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"((select ROLE_ID from ROLE_TB where ROLE ='%s')",roleConfigReq->rolename().c_str());

    if(localPrevilages->previlageinfo_size() && pPrevilage->has_previlagename())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",PRIVILEGE_ID");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",(select PRIVILEGE_ID from PRIVILEGE_TB where PRIVILEGE_NAME='%s')",pPrevilage->previlagename().c_str());
    }


    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void RolePrevilegeMapTPBQuery::sql_RolePrevilegeMap_Create_Delete_Query(Role *roleConfigReq,char *pStatement,int iIndex)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    Previlage *pPrevilage = NULL;
    Previlages *localPrevilages = roleConfigReq->mutable_previlagesdetails();
    DLOG_DEBUG("Previlages->previlageinfo_size() = %d, iIndex = %d",localPrevilages->previlageinfo_size(),iIndex);

    if(localPrevilages->previlageinfo_size() > iIndex && iIndex > -1)
    {
        pPrevilage = localPrevilages->mutable_previlageinfo(iIndex);
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from MAP_ROLE_PRIVELEGE_TB where ROLE_ID=(select ROLE_ID from ROLE_TB where ROLE='%s') and PRIVILEGE_ID=(select PRIVILEGE_ID from PRIVILEGE_TB where PRIVILEGE_NAME='%s')",roleConfigReq->rolename().c_str(),pPrevilage->previlagename().c_str());
    }
    else
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from MAP_ROLE_PRIVELEGE_TB where ROLE_ID=(select ROLE_ID from ROLE_TB where ROLE='%s')",roleConfigReq->rolename().c_str());

    }


    DLOG_NONE(" < %s ",__FUNCTION__);
}

void RolePrevilegeMapTPBQuery::sql_RolePrevilegeMap_Create_Select_Query(Role *roleConfigReq,char *pStatement,int iIndex)
{

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from MAP_ROLE_PRIVELEGE_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG("Role = %s",roleConfigReq->DebugString().c_str());
    Previlage *pPrevilage = NULL;
    Previlages *localPrevilages = roleConfigReq->mutable_previlagesdetails();
    DLOG_DEBUG("Previlages->previlageinfo_size() = %d, iIndex = %d",localPrevilages->previlageinfo_size(),iIndex);

    if(localPrevilages->previlageinfo_size() > iIndex && iIndex > -1)
    {
        pPrevilage = localPrevilages->mutable_previlageinfo(iIndex);
    }
    else
    {
        DLOG_WARNING("pPrevilage Object  will be NULL, localPrevilages->previlageinfo_size() = %d,iIndex = %d",localPrevilages->previlageinfo_size(),iIndex);
    }

    if(roleConfigReq->has_rolename())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"ROLE_ID=(select ROLE_ID from ROLE_TB where ROLE='%s') and ",roleConfigReq->rolename().c_str());
    }

    if(localPrevilages->previlageinfo_size() && pPrevilage->has_previlagename())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"PRIVILEGE_ID=(select PRIVILEGE_ID from PRIVILEGE_TB where PRIVILEGE_NAME='%s') and ",pPrevilage->previlagename().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void RolePrevilegeMapTPBQuery::sql_RolePrevilegeMap_Create_Mod_Query(Role *roleConfigReq,char *pStatement,int iIndex)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG("Modify is not supported for this table");

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e RolePrevilegeMapTPBQuery::sql_RolePrevilegeMap_Payload_Validation(Role *roleConfigReq)
{
    if(!roleConfigReq->has_rolename())
    {
        DLOG_ERROR("Primary Key ROLE is not set in the request");
        return DRE_DB_FAIL;
    }

    return DRE_DB_SUCCESS;
}

DbStatus_e RolePrevilegeMapTPBQuery::sql_RolePrevilegeMap_Check_All_Invalid(Role *roleConfigReq,int iIndex)
{

    Previlage *pPrevilage = NULL;
    Previlages *localPrevilages = roleConfigReq->mutable_previlagesdetails();

    if(localPrevilages->previlageinfo_size() > iIndex && iIndex > -1)
    {
        pPrevilage = localPrevilages->mutable_previlageinfo(iIndex);
        if(pPrevilage->has_previlagename())
        {
            return DRE_DB_FAIL;
        }
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");

    return DRE_DB_SUCCESS;
}
