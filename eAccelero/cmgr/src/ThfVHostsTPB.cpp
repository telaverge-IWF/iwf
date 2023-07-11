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

void THFVHostsTPBQuery::sql_THFHosts_Create_Check_Modifcation_Query(THFVHost *THFVHostReq,char *pStatement)
{
    int iFlag 					= 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
    DLOG_NONE(" > %s ",__FUNCTION__);


    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from THF_VHOST_TB ");
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(THFVHostReq->has_vhost())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"VHOST='%s' and ",THFVHostReq->vhost().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }


    DLOG_NONE(" < %s ",__FUNCTION__);
}

void THFVHostsTPBQuery::sql_THFHosts_Create_Add_Query(THFVHost *THFVHostReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]	= {0};
    char sFieldValue[MAX_STATEMENT_SIZE]	= {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into THF_VHOST_TB ");
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(VHOST");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",THFVHostReq->vhost().c_str());

    if(THFVHostReq->has_vrealm())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",VREALM");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",THFVHostReq->vrealm().c_str());
    }



    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" < %s ",__FUNCTION__);


}

void THFVHostsTPBQuery::sql_THFHosts_Create_Delete_Query(THFVHost *THFVHostReq,char *pStatement)
{

    int iFlag 					= 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
    DLOG_NONE(" > %s ",__FUNCTION__);


    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from THF_VHOST_TB ");
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(THFVHostReq->has_vhost())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"VHOST='%s' and ",THFVHostReq->vhost().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void THFVHostsTPBQuery::sql_THFHosts_Create_Mod_Query(THFVHost *THFVHostReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update THF_VHOST_TB set ");


    if(THFVHostReq->has_vrealm())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"VREALM='%s',",THFVHostReq->vrealm().c_str());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where VHOST='%s'",THFVHostReq->vhost().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e THFVHostsTPBQuery::sql_THFHosts_Payload_Validation(THFVHost *THFVHostReq)
{

    return DRE_DB_SUCCESS;
}


void THFVHostsTPBQuery::sql_THFHosts_Create_Select_Query(THFVHost *THFVHostReq,char *pStatement)
{
    int iFlag 					= 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from THF_VHOST_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(THFVHostReq->has_vhost())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"VHOST='%s' and ",THFVHostReq->vhost().c_str());
    }

    if(THFVHostReq->has_vrealm())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"VREALM='%s' and ",THFVHostReq->vrealm().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }


    DLOG_NONE(" < %s ",__FUNCTION__);

}

DbStatus_e THFVHostsTPBQuery::sql_THFHosts_Check_All_Invalid(THFVHost *THFVHostReq)
{

    if(THFVHostReq->has_vrealm())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}


