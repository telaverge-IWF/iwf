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

void IWFEventTypeMappingTPBQuery::sql_IWFEventTypeMapping_Create_Check_Modifcation_Query(CallScenario *pCallScenario, std::string RuleName, char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    bool iFlag = false; 
    EventType* pEventType = NULL;

    if(pCallScenario->has_call_typename())
    {
        iFlag = true;
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_EVENT_TYPE_MAPPING_ID from IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID =( select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='%s') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = '%s')) and ",RuleName.c_str(),pCallScenario->call_typename().c_str());
    }

    if(pCallScenario->eventtypeval_size() > iIndex && iIndex > -1)
    {
        pEventType = pCallScenario->mutable_eventtypeval(iIndex);
#if 0
        if(pEventType->has_eventtypename() && pCallScenario->has_call_typename())
        {
            snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_EVENT_TYPE_MAPPING_ID from IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID =( select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='%s') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = '%s')) and IWF_EVENT_TYPE_ID = (select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='%s')",RuleName.c_str(),pCallScenario->call_typename().c_str(), pEventType->eventtypename().c_str());
        }
#endif
        if(pEventType->has_eventtypename())
        {
            iFlag = true;
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_EVENT_TYPE_ID = (select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='%s') and ",pEventType->eventtypename().c_str());
        }
    }
    
    if(iFlag)
    {
        pStatement[strlen(pStatement) - REMOVE_FOUR_CHARATERS] = '\0';
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFEventTypeMappingTPBQuery::sql_IWFEventTypeMapping_Create_Add_Query(CallScenario *pCallScenario, std::string RuleName, char *pStatement, int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  
    
    EventType* pEventType = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_EVENT_TYPE_MAPPING_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(pCallScenario->has_call_typename())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_CALL_SCENARIO_MAPPING_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='%s') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = '%s')),",RuleName.c_str(), pCallScenario->call_typename().c_str());
    }

    if(pCallScenario->eventtypeval_size() > iIndex && iIndex > -1)
    {
        pEventType = pCallScenario->mutable_eventtypeval(iIndex);

        if(pEventType->has_eventtypename())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_EVENT_TYPE_ID,");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = '%s'),",pEventType->eventtypename().c_str());
        }

    }

    sFieldValue[strlen(sFieldValue) - 1] = ' ';
    sFieldName[strlen(sFieldName) - 1]   = ' ';

    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFEventTypeMappingTPBQuery::sql_IWFEventTypeMapping_Create_Delete_Query(CallScenario *pCallScenarioReq, std::string RuleName, char *pStatement, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    EventType* pEventType = NULL;
    if(pCallScenarioReq->eventtypeval_size() > iIndex && iIndex > -1)
    {
        pEventType = pCallScenarioReq->mutable_eventtypeval(iIndex);

        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID =( select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='%s') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO =  '%s')) and IWF_EVENT_TYPE_ID = (select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='%s')",RuleName.c_str(),pCallScenarioReq->call_typename().c_str(), pEventType->eventtypename().c_str());
        
    }
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFEventTypeMappingTPBQuery::sql_IWFEventTypeMapping_Payload_Validation(CallScenario *pCallScenarioReq, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    EventType* pEventType = NULL;
    if(pCallScenarioReq->eventtypeval_size() > iIndex && iIndex > -1)
    {
        pEventType = pCallScenarioReq->mutable_eventtypeval(iIndex);

        if(!pEventType->has_eventtypename())
        {
            DLOG_ERROR("Primary Key EventType is not set in the request");
            return IWF_DB_FAIL;
        }
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFEventTypeMappingTPBQuery::sql_IWFEventType_Create_Select_Query(int EventType, char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_EVENT_TYPE_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(EventType)
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_EVENT_TYPE_ID=%d and ", EventType); 
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);

}

void IWFEventTypeMappingTPBQuery::sql_IWFEventTypeMapping_Create_Select_Query(CallScenario *pCallScenario,std::string RuleName, char *pStatement, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_EVENT_TYPE_MAPPING_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(RuleName.c_str() != NULL && pCallScenario->has_call_typename())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_CALL_SCENARIO_MAPPING_ID =( select IWF_CALL_SCENARIO_MAPPING_ID  from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME  ='%s') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO =  '%s')) and ",RuleName.c_str(), pCallScenario->call_typename().c_str());
    }

    EventType* pEventType = NULL;
    if(pCallScenario->eventtypeval_size() > iIndex && iIndex > -1)
    {
        pEventType = pCallScenario->mutable_eventtypeval(iIndex);

        if(pEventType->has_eventtypename())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_EVENT_TYPE_ID=(select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = '%s') and ", pEventType->eventtypename().c_str());
        }
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


