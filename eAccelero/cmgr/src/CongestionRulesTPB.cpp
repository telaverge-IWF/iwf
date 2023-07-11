/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
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
#include "ErrorResp.h"

using namespace std;

void CongestionRulesTPBQuery::sql_CongestionRules_Create_Check_Modifcation_Query(RuleConfig *pRuleConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pRuleConfigReq->has_rulename())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select RULE_ID from CONGESTION_RULES_TB where RULE_NAME='%s'",pRuleConfigReq->rulename().c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CongestionRulesTPBQuery::sql_CongestionRules_Create_Add_Query(RuleConfig *pRuleConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into CONGESTION_RULES_TB ");
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(RULE_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'", pRuleConfigReq->rulename().c_str());

    if(pRuleConfigReq->has_ruledescription())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",RULE_DESCRIPTION");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",\"%s\"",pRuleConfigReq->ruledescription().c_str());
    }
    if(pRuleConfigReq->has_trigger())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",TRIGGER_ID");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",pRuleConfigReq->trigger());
    }
    if(pRuleConfigReq->has_level())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",CONG_LEVEL_ID");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",pRuleConfigReq->level());
    }
    if(pRuleConfigReq->has_rule())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",RULE");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",\"%s\"",pRuleConfigReq->rule().c_str());
    }
    if(pRuleConfigReq->has_action())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",ACTION");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",pRuleConfigReq->action());
    }
    if(pRuleConfigReq->has_priority())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",PRIORITY");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",pRuleConfigReq->priority());
    }
    if(pRuleConfigReq->has_rulestatus())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",FILTER_STATUS");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",pRuleConfigReq->rulestatus());
    }

    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CongestionRulesTPBQuery::sql_CongestionRules_Create_Mod_Query(RuleConfig *pRuleConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update CONGESTION_RULES_TB set ");

    if(pRuleConfigReq->has_ruledescription())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"RULE_DESCRIPTION=\"%s\",",pRuleConfigReq->ruledescription().c_str());
    }
    if(pRuleConfigReq->has_trigger())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"TRIGGER_ID=%d,",pRuleConfigReq->trigger());
    }
    if(pRuleConfigReq->has_level())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"CONG_LEVEL_ID=%d,",pRuleConfigReq->level());
    }
    if(pRuleConfigReq->has_rule())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"RULE=\"%s\",",pRuleConfigReq->rule().c_str());
    }
    if(pRuleConfigReq->has_action())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"ACTION=%d,",pRuleConfigReq->action());
    }
    if(pRuleConfigReq->has_rulestatus())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"FILTER_STATUS=%d,",pRuleConfigReq->rulestatus());
    }
    if(pRuleConfigReq->has_priority())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"PRIORITY=%d,",pRuleConfigReq->priority());
    }
    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where RULE_NAME='%s'",pRuleConfigReq->rulename().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CongestionRulesTPBQuery::sql_CongestionRules_Create_Delete_Query(RuleConfig *pRuleConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pRuleConfigReq->has_rulename())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from CONGESTION_RULES_TB where RULE_NAME='%s'",pRuleConfigReq->rulename().c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CongestionRulesTPBQuery::sql_CongestionRules_Payload_Validation(RuleConfig *pRuleConfigReq)
{
    if (!pRuleConfigReq->has_rulename())
    {
        DLOG_ERROR("Primary Key Rule-name is not set in the request");
        return ERR_MANDATORY_PARAM_REALMNAME_MISSING;
    }
    return DRE_DB_SUCCESS;
}

void CongestionRulesTPBQuery::sql_CongestionRules_Create_Select_Query(RuleConfig *pRuleConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from CONGESTION_RULES_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pRuleConfigReq->has_rulename())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"RULE_NAME='%s' and ",pRuleConfigReq->rulename().c_str());
    }
    if(pRuleConfigReq->has_trigger())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"TRIGGER_ID=%d and ",pRuleConfigReq->trigger());
    }
    if(pRuleConfigReq->has_level())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"CONG_LEVEL_ID=%d and ",pRuleConfigReq->level());
    }
    if(pRuleConfigReq->has_rule())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"RULE=\"%s\" and ",pRuleConfigReq->rule().c_str());
    }
    if(pRuleConfigReq->has_action())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"ACTION=%d and ",pRuleConfigReq->action());
    }
    if(pRuleConfigReq->has_priority())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"PRIORITY=%d and ",pRuleConfigReq->priority());
    }
    if(pRuleConfigReq->has_rulestatus())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"FILTER_STATUS=%d and ",pRuleConfigReq->rulestatus());
    }
    if(pRuleConfigReq->has_ruledescription())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"RULE_DESCRIPTION=\"%s\" and ",pRuleConfigReq->ruledescription().c_str());
    }
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CongestionRulesTPBQuery::sql_CongestionRules_Check_All_Invalid(RuleConfig *pRuleConfigReq)
{
    return DRE_DB_SUCCESS;
}
