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

void EmailContentTPBQuery::sql_EmailContent_Create_Check_Modifcation_Query(EmailContent *emailConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select EMAIL_CONTENT_FOR from EMAIL_CONTENT_TB where EMAIL_CONTENT_FOR='%s' ",emailConfigReq->emailcontentfor().c_str());

}

void EmailContentTPBQuery::sql_EmailContent_Create_Add_Query(EmailContent *emailConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into EMAIL_CONTENT_TB ");
    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),"(EMAIL_CONTENT_FOR");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",emailConfigReq->emailcontentfor().c_str());

    if(emailConfigReq->has_subject())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",SUBJECT");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",emailConfigReq->subject().c_str());
    }

    if(emailConfigReq->has_emailstatus())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",EMAIL_STATUS");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",emailConfigReq->emailstatus());
    }

    if(emailConfigReq->has_message())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",MESSAGE");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'%s'",emailConfigReq->message().c_str());
    }

    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void EmailContentTPBQuery::sql_EmailContent_Create_Delete_Query(EmailContent *emailConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from EMAIL_CONTENT_TB where EMAIL_CONTENT_FOR='%s' ",emailConfigReq->emailcontentfor().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void EmailContentTPBQuery::sql_EmailContent_Create_Select_Query(EmailContent *emailConfigReq,char *pStatement)
{

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from EMAIL_CONTENT_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(emailConfigReq->has_emailcontentfor())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"EMAIL_CONTENT_FOR='%s' and ",emailConfigReq->emailcontentfor().c_str());
    }


    if(emailConfigReq->has_emailstatus())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"EMAIL_STATUS=%d and ",emailConfigReq->emailstatus());
    }

    if(emailConfigReq->has_message())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"MESSAGE='%s' and ",emailConfigReq->message().c_str());
    }

    if(emailConfigReq->has_subject())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"SUBJECT='%s and ",emailConfigReq->subject().c_str());
    }


    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void EmailContentTPBQuery::sql_EmailContent_Create_Mod_Query(EmailContent *emailConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update EMAIL_CONTENT_TB set ");

    if(emailConfigReq->has_emailstatus())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"EMAIL_STATUS=%d,",emailConfigReq->emailstatus());
    }

    if(emailConfigReq->has_subject())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"SUBJECT='%s',",emailConfigReq->subject().c_str());
    }

    if(emailConfigReq->has_message())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"MESSAGE='%s',",emailConfigReq->message().c_str());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where EMAIL_CONTENT_FOR='%s'",emailConfigReq->emailcontentfor().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e EmailContentTPBQuery::sql_EmailContent_Payload_Validation(EmailContent *emailConfigReq)
{
    if(!emailConfigReq->has_emailcontentfor())
    {
        DLOG_ERROR("Primary Key EMAIL_CONTENT_FOR is not set in the request");
        return DRE_DB_FAIL;
    }

    return DRE_DB_SUCCESS;
}

DbStatus_e EmailContentTPBQuery::sql_EmailContent_Check_All_Invalid(EmailContent *emailConfigReq)
{

    if(emailConfigReq->has_emailstatus())
    {
        return DRE_DB_FAIL;
    }

    if(emailConfigReq->has_message())
    {
        return DRE_DB_FAIL;
    }

    if(emailConfigReq->has_subject())
    {
        return DRE_DB_FAIL;
    }


    DLOG_INFO("In the Request, No Fields are Set for Operation");

    return DRE_DB_SUCCESS;
}
