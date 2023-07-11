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

void ThfTPBQuery::sql_Thf_Create_Check_Modifcation_Query(THFReq *ThfConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(ThfConfigReq->has_enablethf())
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from THF_TB where CONFIG_NAME='enable'");
    else if(ThfConfigReq->has_defaultexpose())
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from THF_TB where CONFIG_NAME='default-behaviour'");
    else
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from THF_TB ");

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void ThfTPBQuery::sql_Thf_Create_Add_Query(THFReq *ThfConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]	= {0};
    char sFieldValue[MAX_STATEMENT_SIZE]	= {0};

    DLOG_NONE(" > %s ",__FUNCTION__);


    if(ThfConfigReq->has_enablethf())
    {

        snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into THF_TB ");
        snprintf(sFieldName,MAX_STATEMENT_SIZE,"(CONFIG_NAME,VALUE");
        if(ThfConfigReq->enablethf() == true)
            snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('enable','true'");
        else if(ThfConfigReq->enablethf() == false)
            snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('enable','false'");

        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s;",sFieldName,sFieldValue);
    }

    if(ThfConfigReq->has_defaultexpose())
    {

        snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into THF_TB ");
        snprintf(sFieldName,MAX_STATEMENT_SIZE,"(CONFIG_NAME,VALUE");
        if(ThfConfigReq->defaultexpose() == false)
            snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('default-behaviour','hide'");
        else if(ThfConfigReq->defaultexpose() == true)
            snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('default-behaviour','expose'");

        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s;",sFieldName,sFieldValue);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void ThfTPBQuery::sql_Thf_Create_Delete_Query(THFReq *ThfConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void ThfTPBQuery::sql_Thf_Create_Mod_Query(THFReq *ThfConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(ThfConfigReq->has_enablethf())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"update THF_TB set ");

        if(ThfConfigReq->enablethf() == true)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"VALUE='true',");
        }
        else if(ThfConfigReq->enablethf() == false)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"VALUE='false',");
        }

        pStatement[strlen(pStatement) -1] = ' ';

        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where CONFIG_NAME='enable';");
    }

    if(ThfConfigReq->has_defaultexpose())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"update THF_TB set ");
        if(ThfConfigReq->defaultexpose() == false)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"VALUE='hide',");
        }
        else if(ThfConfigReq->defaultexpose() == true)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"VALUE='expose',");
        }

        pStatement[strlen(pStatement) -1] = ' ';

        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where CONFIG_NAME='default-behaviour';");
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e ThfTPBQuery::sql_Thf_Payload_Validation(THFReq *ThfConfigReq)
{
    return DRE_DB_SUCCESS;
}


void ThfTPBQuery::sql_Thf_Create_Select_Query(THFReq *ThfConfigReq,char *pStatement)
{
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from THF_TB");


    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e ThfTPBQuery::sql_Thf_Check_All_Invalid(THFReq *ThfConfigReq)
{
    if(ThfConfigReq->has_enablethf())
    {
        return DRE_DB_FAIL;
    }

    if(ThfConfigReq->has_defaultexpose())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
