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


#include <CMgrIwfDbInterface.h>

using namespace std;

void IWFProtocolActionTPBQuery::sql_IWFProtocolAction_Create_Check_Modifcation_Query(IwfProtocolActionConfig *IwfProtocolActionConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME = '%s'",IwfProtocolActionConfigReq->actionrulename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFProtocolActionTPBQuery::sql_IWFProtocolAction_Create_Add_Query(IwfProtocolActionConfig *IwfProtocolActionConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_PROTOCOL_ACTION_RULE_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(ACTION_RULE_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",IwfProtocolActionConfigReq->actionrulename().c_str());

    if(IwfProtocolActionConfigReq-> has_protocol())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PROTOCOL_ID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select IWF_PROTOCOL_ID from IWF_PROTOCOL_TB where IWF_PROTOCOL_NAME = '%s')",IwfProtocolActionConfigReq->protocol().c_str());
    }

    if(IwfProtocolActionConfigReq->has_actionid())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ACTION_ID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfProtocolActionConfigReq->actionid());
    }

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFProtocolActionTPBQuery::sql_IWFProtocolAction_Create_Mod_Query(IwfProtocolActionConfig *IwfProtocolActionConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);


    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_PROTOCOL_ACTION_RULE_TB set "); 

    if(IwfProtocolActionConfigReq->has_protocol())
    {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PROTOCOL_ID=(select IWF_PROTOCOL_ID from IWF_PROTOCOL_TB where IWF_PROTOCOL_NAME='%s'),",IwfProtocolActionConfigReq->protocol().c_str());
    }

    if(IwfProtocolActionConfigReq->has_actionid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ACTION_ID = %d,",IwfProtocolActionConfigReq->actionid());
    }

    pStatement[strlen(pStatement) -1] = ' ';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where ACTION_RULE_NAME='%s' ",IwfProtocolActionConfigReq->actionrulename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFProtocolActionTPBQuery::sql_IWFProtocolAction_Create_Delete_Query(IwfProtocolActionConfig *IwfProtocolActionConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME='%s'",IwfProtocolActionConfigReq->actionrulename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
#if 0
void IWFProtocolActionTPBQuery::sql_IWFAllTranslatorRule_Create_Delete_Query(char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_PROTOCOL_ACTION_RULE_TB ");

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
#endif
DbStatus_e IWFProtocolActionTPBQuery::sql_IWFProtocolAction_Payload_Validation(IwfProtocolActionConfig *IwfProtocolActionConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(!IwfProtocolActionConfigReq->has_actionrulename())
    {
        DLOG_ERROR("Primary Key ACTION_RULE_NAME is not set in the request");
        return IWF_DB_FAIL;
    }

    return IWF_DB_SUCCESS;
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


void IWFProtocolActionTPBQuery::sql_IWFProtocolAction_Create_Select_Query(IwfProtocolActionConfig *IwfProtocolActionConfigReq,char *pStatement)
{
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    int iFlag = 0;
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_PROTOCOL_ACTION_RULE_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfProtocolActionConfigReq->has_actionrulename())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ACTION_RULE_NAME='%s' and ",IwfProtocolActionConfigReq->actionrulename().c_str());
    }

    if(IwfProtocolActionConfigReq->has_protocol())
    {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PROTOCOL_ID=(select IWF_PROTOCOL_ID from IWF_PROTOCOL_TB where IWF_PROTOCOL_NAME = '%s') and ",IwfProtocolActionConfigReq->protocol().c_str());
    }

    if(IwfProtocolActionConfigReq->has_actionid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ACTION_ID = %d and ",IwfProtocolActionConfigReq->actionid());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFProtocolActionTPBQuery::sql_IWFProtocolAction_Check_All_Invalid(IwfProtocolActionConfig *IwfProtocolActionConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(IwfProtocolActionConfigReq->has_actionrulename())
    {
        return IWF_DB_FAIL;
    }
    if(IwfProtocolActionConfigReq->has_protocol())
    {
        return IWF_DB_FAIL;
    }
    if(IwfProtocolActionConfigReq->has_actionid())
    {
        return IWF_DB_FAIL;
    }
    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
