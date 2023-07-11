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

void EmailServerTPBQuery::sql_EmailServer_Create_Check_Modifcation_Query(EmailServer *emailConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select HOSTNAME from EMAIL_SERVER_TB");

}

void EmailServerTPBQuery::sql_EmailServer_Create_Add_Query(EmailServer *emailConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into EMAIL_SERVER_TB ");
    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),"(HOSTNAME,PORT_NUMBER");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),"('%s',%d",emailConfigReq->hostname().c_str(),emailConfigReq->portnumber());

    if(emailConfigReq->has_password())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",Password");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",?");
    }

    if(emailConfigReq->has_systememail())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",SYSTEM_EMAIL");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",emailConfigReq->systememail().c_str());
    }

    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void EmailServerTPBQuery::sql_EmailServer_Create_Delete_Query(EmailServer *emailConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from EMAIL_SERVER_TB");

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void EmailServerTPBQuery::sql_EmailServer_Create_Select_Query(EmailServer *emailConfigReq,char *pStatement)
{

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from EMAIL_SERVER_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(emailConfigReq->has_hostname())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"HOSTNAME='%s' and ",emailConfigReq->hostname().c_str());
    }


    if(emailConfigReq->has_password())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"Password=? and ");
    }

    if(emailConfigReq->has_systememail())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"SYSTEM_EMAIL='%s' and ",emailConfigReq->systememail().c_str());
    }

    if(emailConfigReq->has_portnumber())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"PORT_NUMBER=%d and ",emailConfigReq->portnumber());
    }


    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void EmailServerTPBQuery::sql_EmailServer_Create_Mod_Query(EmailServer *emailConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update EMAIL_SERVER_TB set ");

    if(emailConfigReq->has_password())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"Password=?,");
    }

    if(emailConfigReq->has_systememail())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"SYSTEM_EMAIL='%s',",emailConfigReq->systememail().c_str());
    }

    if(emailConfigReq->has_hostname())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"HOSTNAME='%s',",emailConfigReq->hostname().c_str());
    }

    if(emailConfigReq->has_portnumber())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"PORT_NUMBER=%d,",emailConfigReq->portnumber());
    }

    pStatement[strlen(pStatement) -1] = ' ';


    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e EmailServerTPBQuery::sql_EmailServer_Payload_Validation(EmailServer *emailConfigReq)
{
    if(!emailConfigReq->has_hostname())
    {
        DLOG_ERROR("Primary Key HOSTNAME is not set in the request");
        return DRE_DB_FAIL;
    }

    return DRE_DB_SUCCESS;
}

DbStatus_e EmailServerTPBQuery::sql_EmailServer_Check_All_Invalid(EmailServer *emailConfigReq)
{

    if(emailConfigReq->has_password())
    {
        return DRE_DB_FAIL;
    }

    if(emailConfigReq->has_systememail())
    {
        return DRE_DB_FAIL;
    }


    DLOG_INFO("In the Request, No Fields are Set for Operation");

    return DRE_DB_SUCCESS;
}
