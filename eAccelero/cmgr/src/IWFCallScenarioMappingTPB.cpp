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
                                                                           *
 * ****************************************************************************/


#include <CMgrIwfDbInterface.h>

using namespace std;

void IWFCallScenarioMappingTPBQuery::sql_IWFCallScenarioMapping_Create_Check_Modifcation_Query(MsgDet *pMsgDet, std::string RuleName, char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    
    CallScenario* pCallScenario = NULL;
    
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='%s') and ",RuleName.c_str());
    
    if(pMsgDet->callscenarioval_size() > iIndex && iIndex > -1)
    {
        pCallScenario = pMsgDet->mutable_callscenarioval(iIndex);
        if(pCallScenario->has_call_typename())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = '%s') and ",pCallScenario->call_typename().c_str());
        }
    }

    pStatement[strlen(pStatement) - REMOVE_FOUR_CHARATERS] = '\0';

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFCallScenarioMappingTPBQuery::sql_IWFCallScenarioMapping_Create_Add_Query(MsgDet *pMsgDet, std::string RuleName, char *pStatement, int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  
    
    CallScenario* pCallScenario = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_CALL_SCENARIO_MAPPING_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_PROTOCOL_ACTION_RULE_ID,");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME = '%s'),",RuleName.c_str());

    if(pMsgDet->callscenarioval_size() > iIndex && iIndex > -1)
    {
        pCallScenario = pMsgDet->mutable_callscenarioval(iIndex);

        if(pCallScenario->has_call_typename())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_CALL_SCENARIO_ID,");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = '%s'),",pCallScenario->call_typename().c_str());
        }

    }

    sFieldValue[strlen(sFieldValue) - 1] = ' ';
    sFieldName[strlen(sFieldName) - 1]   = ' ';

    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFCallScenarioMappingTPBQuery::sql_IWFCallScenarioMapping_Create_Delete_Query(MsgDet *pMsgDetReq, std::string RuleName, char *pStatement, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    CallScenario* pCallScenario = NULL;
    if(pMsgDetReq->callscenarioval_size() > iIndex && iIndex > -1)
    {
        pCallScenario = pMsgDetReq->mutable_callscenarioval(iIndex);

        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='%s') and IWF_CALL_SCENARIO_ID=(select  IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = '%s')",RuleName.c_str(), pCallScenario->call_typename().c_str());
    }
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFCallScenarioMappingTPBQuery::sql_IWFCallScenarioMapping_Payload_Validation(MsgDet *pMsgDetReq, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    CallScenario* pCallScenario = NULL;
    if(pMsgDetReq->callscenarioval_size() > iIndex && iIndex > -1)
    {
        pCallScenario = pMsgDetReq->mutable_callscenarioval(iIndex);

        if(!pCallScenario->has_call_typename())
        {
            DLOG_ERROR("Primary Key CallType is not set in the request");
            return IWF_DB_FAIL;
        }
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFCallScenarioMappingTPBQuery::sql_IWFCallScenarioMapping_Create_Select_Query(MsgDet *pMsgDet,std::string RuleName, char *pStatement, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_CALL_SCENARIO_MAPPING_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(RuleName.c_str() != NULL)
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID   from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='%s') and ",RuleName.c_str());
    }
    
    CallScenario* pCallScenario = NULL;
    if(pMsgDet->callscenarioval_size() > iIndex && iIndex > -1)
    {
        pCallScenario = pMsgDet->mutable_callscenarioval(iIndex);

        if(pCallScenario->has_call_typename())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_CALL_SCENARIO_ID=(select  IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = '%s') and ", pCallScenario->call_typename().c_str());
        }

    }
    
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


