/*******************************-*-CPP-*-************************************
 *                                                                          *
 *          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
 *            Manufactured in the United States of America.                 *
 *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of Diametriq and its licensors, if any.                  *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************/

/*
 * FILE:   SDTFRulesTPB.cpp
 * Author: Hemanth
 *
 * Created on Nov 25, 2014, 05:08 PM
 */


#include <CMgrDbInterface.h>
#include "CMgrUtils.h"

using namespace std;

void SDTFRulesTPBQuery::sql_SDTFRules_Create_Check_Modifcation_Query(SDTFRule *pSDTFRuleReq, char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pSDTFRuleReq->has_rulename())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select RULE_ID from SDTF_RULES_TB where NAME='%s'", pSDTFRuleReq->rulename().c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void SDTFRulesTPBQuery::sql_SDTFRules_Create_Fetch_Query(SDTFRule *pSDTFRuleReq, char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pSDTFRuleReq->has_rulename())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from SDTF_RULES_TB where NAME='%s'", pSDTFRuleReq->rulename().c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void SDTFRulesTPBQuery::sql_SDTFRules_Create_Add_Query(SDTFRule *pSDTFRuleReq, char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_SPECIAL_STATEMENT_SIZE] = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_SPECIAL_STATEMENT_SIZE,"insert into SDTF_RULES_TB ");
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(NAME");
    snprintf(sFieldValue,MAX_SPECIAL_STATEMENT_SIZE,"('%s'", pSDTFRuleReq->rulename().c_str());

    if(pSDTFRuleReq->has_priority())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        {
            snprintf(sFieldName + strlen(sFieldName),(MAX_STATEMENT_SIZE - strlen(sFieldName)),",PRIORITY");
        }

        if(strlen(sFieldValue) < MAX_SPECIAL_STATEMENT_SIZE)
        {
            snprintf(sFieldValue + strlen(sFieldValue),(MAX_SPECIAL_STATEMENT_SIZE - strlen(sFieldValue)),",%d",pSDTFRuleReq->priority());
        }
    }

    if(pSDTFRuleReq->has_type())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        {
            snprintf(sFieldName + strlen(sFieldName),(MAX_STATEMENT_SIZE - strlen(sFieldName)),",TRIGGER_TYPE");
        }

        if(pSDTFRuleReq->type() == SDTFRule_TriggerType_Ingress)
        {
            if(strlen(sFieldValue) < MAX_SPECIAL_STATEMENT_SIZE)
            {
                snprintf(sFieldValue + strlen(sFieldValue),(MAX_SPECIAL_STATEMENT_SIZE - strlen(sFieldValue)),",'Ingress'");
            }
        }
        else if(pSDTFRuleReq->type() == SDTFRule_TriggerType_Egress)
        {
            if(strlen(sFieldValue) < MAX_SPECIAL_STATEMENT_SIZE)
            {
                snprintf(sFieldValue + strlen(sFieldValue),(MAX_SPECIAL_STATEMENT_SIZE - strlen(sFieldValue)),",'Egress'");
            }
        }
    }

    if(pSDTFRuleReq->has_enabled())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        {
            snprintf(sFieldName + strlen(sFieldName),(MAX_STATEMENT_SIZE - strlen(sFieldName)),",ENABLED");
        }

        if(strlen(sFieldValue) < MAX_SPECIAL_STATEMENT_SIZE)
        {
            snprintf(sFieldValue + strlen(sFieldValue),(MAX_SPECIAL_STATEMENT_SIZE - strlen(sFieldValue)),",%d",pSDTFRuleReq->enabled());
        }
    }

    if(pSDTFRuleReq->has_rule())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        {
            snprintf(sFieldName + strlen(sFieldName),(MAX_STATEMENT_SIZE - strlen(sFieldName)),",RULE");
        }

        if(strlen(sFieldValue) < MAX_SPECIAL_STATEMENT_SIZE)
        {
            snprintf(sFieldValue + strlen(sFieldValue),(MAX_SPECIAL_STATEMENT_SIZE - strlen(sFieldValue)),",\"%s\"",pSDTFRuleReq->rule().c_str());
        }
    }

    if(pSDTFRuleReq->has_script())
    {
        string scriptStr = pSDTFRuleReq->script();
        int ret = 0;

        // NOTE : updatePattern - STARTS
        // Please do not change this updatePattern order.
        // It will impact the expected string value.
        ret = updatePattern(scriptStr, "\\", "\\\\");
        if (ret != 0)
        {
            // Failed in updating pattern.
            // Retaining to it's orginal value.
            scriptStr = pSDTFRuleReq->script();
        }

        ret = updatePattern(scriptStr, "\"", "\\\"");
        if (ret != 0)
        {
            // Failed in updating pattern.
            // Retaining to it's orginal value.
            scriptStr = pSDTFRuleReq->script();
        }
        // NOTE : updatePattern - ENDS

        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        {
            snprintf(sFieldName + strlen(sFieldName),(MAX_STATEMENT_SIZE - strlen(sFieldName)),",SCRIPT");
        }

        if(strlen(sFieldValue) < MAX_SPECIAL_STATEMENT_SIZE)
        {
            snprintf(sFieldValue + strlen(sFieldValue),(MAX_SPECIAL_STATEMENT_SIZE - strlen(sFieldValue)),",\"%s\"",scriptStr.c_str());
        }
    }

    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
    {
        snprintf(sFieldName + strlen(sFieldName),(MAX_STATEMENT_SIZE - strlen(sFieldName)),")");
    }

    if(strlen(sFieldValue) < MAX_SPECIAL_STATEMENT_SIZE)
    {
        snprintf(sFieldValue + strlen(sFieldValue),(MAX_SPECIAL_STATEMENT_SIZE - strlen(sFieldValue)),")");
    }

    if(strlen(pStatement) < MAX_SPECIAL_STATEMENT_SIZE)
    {
        snprintf(pStatement + strlen(pStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(pStatement)),"%s value %s",sFieldName,sFieldValue);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void SDTFRulesTPBQuery::sql_SDTFRules_Create_Mod_Query(SDTFRule *pSDTFRuleReq, char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_SPECIAL_STATEMENT_SIZE,"update SDTF_RULES_TB set ");

    if(pSDTFRuleReq->has_priority())
    {
        if(strlen(pStatement) < MAX_SPECIAL_STATEMENT_SIZE)
        {
            snprintf(pStatement + strlen(pStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(pStatement)),"PRIORITY=%d,",pSDTFRuleReq->priority());
        }
    }

    if(pSDTFRuleReq->has_type())
    {
        if(pSDTFRuleReq->type() == SDTFRule_TriggerType_Ingress)
        {
            if(strlen(pStatement) < MAX_SPECIAL_STATEMENT_SIZE)
            {
                snprintf(pStatement + strlen(pStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(pStatement)),"TRIGGER_TYPE='Ingress',");
            }
        }
        else if(pSDTFRuleReq->type() == SDTFRule_TriggerType_Egress)
        {
            if(strlen(pStatement) < MAX_SPECIAL_STATEMENT_SIZE)
            {
                snprintf(pStatement + strlen(pStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(pStatement)),"TRIGGER_TYPE='Egress',");
            }
        }
    }

    if(pSDTFRuleReq->has_enabled())
    {
        if(strlen(pStatement) < MAX_SPECIAL_STATEMENT_SIZE)
        {
            snprintf(pStatement + strlen(pStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(pStatement)),"ENABLED=%d,",pSDTFRuleReq->enabled());
        }
    }

    if(pSDTFRuleReq->has_rule())
    {
        if(strlen(pStatement) < MAX_SPECIAL_STATEMENT_SIZE)
        {
            snprintf(pStatement + strlen(pStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(pStatement)),"RULE=\"%s\",",pSDTFRuleReq->rule().c_str());
        }
    }

    if(pSDTFRuleReq->has_script())
    {
        string scriptStr = pSDTFRuleReq->script();
        int ret = 0;

        // NOTE : updatePattern - STARTS
        // Please do not change this updatePattern order.
        // It will impact the expected string value.
        ret = updatePattern(scriptStr, "\\", "\\\\");
        if (ret != 0)
        {
            // Failed in updating pattern.
            // Retaining to it's orginal value.
            scriptStr = pSDTFRuleReq->script();
        }

        ret = updatePattern(scriptStr, "\"", "\\\"");
        if (ret != 0)
        {
            // Failed in updating pattern.
            // Retaining to it's orginal value.
            scriptStr = pSDTFRuleReq->script();
        }
        // NOTE : updatePattern - ENDS

        if(strlen(pStatement) < MAX_SPECIAL_STATEMENT_SIZE)
        {
            snprintf(pStatement + strlen(pStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(pStatement)),"SCRIPT=\"%s\",",scriptStr.c_str());
        }
    }

    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_SPECIAL_STATEMENT_SIZE)
    {
        snprintf(pStatement + strlen(pStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(pStatement)),"where NAME='%s'",pSDTFRuleReq->rulename().c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void SDTFRulesTPBQuery::sql_SDTFRules_Create_Delete_Query(SDTFRule *pSDTFRuleReq, char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pSDTFRuleReq->has_rulename())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from SDTF_RULES_TB where NAME='%s'",pSDTFRuleReq->rulename().c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e SDTFRulesTPBQuery::sql_SDTFRules_Payload_Validation(SDTFRule *pSDTFRuleReq)
{
    if (!pSDTFRuleReq->has_rulename())
    {
        DLOG_ERROR("Primary Key Rule-name is not set in the request");
        return ERR_MANDATORY_PARAM_REALMNAME_MISSING;//TODO:Have seperate error.
    }
    return DRE_DB_SUCCESS;
}

void SDTFRulesTPBQuery::sql_SDTFRules_Create_Select_Query(SDTFRule *pSDTFRuleReq, char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_SPECIAL_STATEMENT_SIZE]    = {0};
    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_SPECIAL_STATEMENT_SIZE,"select * from SDTF_RULES_TB ");

    snprintf(sWhereStatement,MAX_SPECIAL_STATEMENT_SIZE,"where ");

    if(pSDTFRuleReq->has_rulename())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_SPECIAL_STATEMENT_SIZE)
        {
            snprintf(sWhereStatement + strlen(sWhereStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(sWhereStatement)),
                    "NAME='%s' and ",pSDTFRuleReq->rulename().c_str());
        }
    }

    if(pSDTFRuleReq->has_priority())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_SPECIAL_STATEMENT_SIZE)
        {
            snprintf(sWhereStatement + strlen(sWhereStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(sWhereStatement)),"PRIORITY=%d and ",pSDTFRuleReq->priority());
        }
    }

    if(pSDTFRuleReq->has_type())
    {
        iFlag = 1;

        if(pSDTFRuleReq->type() == SDTFRule_TriggerType_Ingress)
        {
            if(strlen(sWhereStatement) < MAX_SPECIAL_STATEMENT_SIZE)
            {
                snprintf(sWhereStatement + strlen(sWhereStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(sWhereStatement)),"TRIGGER_TYPE='Ingress' and ");
            }
        }
        else if(pSDTFRuleReq->type() == SDTFRule_TriggerType_Egress)
        {
            if(strlen(sWhereStatement) < MAX_SPECIAL_STATEMENT_SIZE)
            {
                snprintf(sWhereStatement + strlen(sWhereStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(sWhereStatement)),"TRIGGER_TYPE='Egress' and ");
            }
        }
    }

    if(pSDTFRuleReq->has_enabled())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_SPECIAL_STATEMENT_SIZE)
        {
            snprintf(sWhereStatement + strlen(sWhereStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(sWhereStatement)),"ENABLED=%d and ",pSDTFRuleReq->enabled());
        }
    }

    if(pSDTFRuleReq->has_rule())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_SPECIAL_STATEMENT_SIZE)
        {
            snprintf(sWhereStatement + strlen(sWhereStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(sWhereStatement)),"RULE=\"%s\" and ",pSDTFRuleReq->rule().c_str());
        }
    }

    if(pSDTFRuleReq->has_script())
    {
        string scriptStr = pSDTFRuleReq->script();
        int ret = 0;

        // NOTE : updatePattern - STARTS
        // Please do not change this updatePattern order.
        // It will impact the expected string value.
        ret = updatePattern(scriptStr, "\\", "\\\\");
        if (ret != 0)
        {
            // Failed in updating pattern.
            // Retaining to it's orginal value.
            scriptStr = pSDTFRuleReq->script();
        }

        ret = updatePattern(scriptStr, "\"", "\\\"");
        if (ret != 0)
        {
            // Failed in updating pattern.
            // Retaining to it's orginal value.
            scriptStr = pSDTFRuleReq->script();
        }
        // NOTE : updatePattern - ENDS

        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_SPECIAL_STATEMENT_SIZE)
        {
            snprintf(sWhereStatement + strlen(sWhereStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(sWhereStatement)),"SCRIPT=\"%s\" and ",scriptStr.c_str());
        }
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_SPECIAL_STATEMENT_SIZE)
        {
            snprintf(pStatement + strlen(pStatement),(MAX_SPECIAL_STATEMENT_SIZE - strlen(pStatement))," %s ",sWhereStatement);
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e SDTFRulesTPBQuery::sql_SDTFRules_Check_All_Invalid(SDTFRule *pSDTFRuleReq)
{
    return DRE_DB_SUCCESS;
}

