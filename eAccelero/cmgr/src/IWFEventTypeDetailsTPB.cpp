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

void IWFEventTypeDetailsTPBQuery::sql_IWFEventTypeDetails_Create_Check_Modifcation_Query(EventType *pEventType, std::string RuleName, std::string CallScenario, char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    
    ArmData* pArmData = NULL;

    if(pEventType->armdatval_size() > iIndex && iIndex > -1)
    {
        pArmData = pEventType->mutable_armdatval(iIndex);
        if(pArmData->has_monitormode() && pArmData->has_legid())
        {
            snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_EVENT_TYPE_DETAILS_ID from IWF_EVENT_TYPE_DETAILS_TB where IWF_EVENT_TYPE_MAPPING_ID = (select IWF_EVENT_TYPE_MAPPING_ID from IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='%s') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = '%s')) and IWF_EVENT_TYPE_ID = (select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='%s') and MONITOR_MODE = '%s' and LEG_ID = '%s')",RuleName.c_str(), CallScenario.c_str(), pEventType->eventtypename().c_str(), pArmData->monitormode().c_str(), pArmData->legid().c_str());

        }
        else if(pArmData->has_monitormode())
        {
            snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_EVENT_TYPE_DETAILS_ID from IWF_EVENT_TYPE_DETAILS_TB where IWF_EVENT_TYPE_MAPPING_ID = (select IWF_EVENT_TYPE_MAPPING_ID from IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='%s') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = '%s')) and IWF_EVENT_TYPE_ID = (select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='%s') and MONITOR_MODE = '%s')",RuleName.c_str(), CallScenario.c_str(), pEventType->eventtypename().c_str(), pArmData->monitormode().c_str());

        }
    }
    
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFEventTypeDetailsTPBQuery::sql_IWFEventTypeDetails_Create_Add_Query(EventType *pEventType, std::string RuleName, std::string CallScenario, char *pStatement, int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  
    
    ArmData* pArmData = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_EVENT_TYPE_DETAILS_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(RuleName.c_str() != NULL && CallScenario.c_str() != NULL && pEventType->has_eventtypename())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_EVENT_TYPE_MAPPING_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_EVENT_TYPE_MAPPING_ID from IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='%s') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = '%s')) and IWF_EVENT_TYPE_ID = (select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='%s')),",RuleName.c_str(),CallScenario.c_str(),pEventType->eventtypename().c_str());

    }

    if(pEventType->armdatval_size() > iIndex && iIndex > -1)
    {
        pArmData = pEventType->mutable_armdatval(iIndex);

        if(pArmData->has_monitormode())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"MONITOR_MODE,");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pArmData->monitormode().c_str());
        }

        if(pArmData->has_legid())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"LEG_ID,");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pArmData->legid().c_str());
        }

    }

    sFieldValue[strlen(sFieldValue) - 1] = ' ';
    sFieldName[strlen(sFieldName) - 1]   = ' ';

    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFEventTypeDetailsTPBQuery::sql_IWFEventTypeDetails_Create_Delete_Query(EventType *pEventTypeReq, std::string RuleName, std::string CallScenario, char *pStatement, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    ArmData* pArmData = NULL;
    if(pEventTypeReq->armdatval_size() > iIndex && iIndex > -1)
    {
        pArmData = pEventTypeReq->mutable_armdatval(iIndex);

        if(pArmData->has_monitormode() && pArmData->has_legid())
        {
            snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_EVENT_TYPE_DETAILS_TB where IWF_EVENT_TYPE_MAPPING_ID = (select IWF_EVENT_TYPE_MAPPING_ID from IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='%s') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = '%s')) and IWF_EVENT_TYPE_ID = (select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='%s')) and MONITOR_MODE = '%s' and LEG_ID = '%s'",RuleName.c_str(), CallScenario.c_str(), pEventTypeReq->eventtypename().c_str(), pArmData->monitormode().c_str(), pArmData->legid().c_str());
        }
        else if(pArmData->has_monitormode())
        {
            snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_EVENT_TYPE_DETAILS_TB where IWF_EVENT_TYPE_MAPPING_ID = (select IWF_EVENT_TYPE_MAPPING_ID from IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='%s') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = '%s')) and IWF_EVENT_TYPE_ID = (select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='%s')) and MONITOR_MODE = '%s'",RuleName.c_str(), CallScenario.c_str(), pEventTypeReq->eventtypename().c_str(), pArmData->monitormode().c_str());

        }
    }
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFEventTypeDetailsTPBQuery::sql_IWFEventTypeDetails_Payload_Validation(EventType *pEventTypeReq, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    ArmData* pArmData = NULL;
    if(pEventTypeReq->armdatval_size() > iIndex && iIndex > -1)
    {
        pArmData = pEventTypeReq->mutable_armdatval(iIndex);
    }

    if(!pEventTypeReq->has_eventtypename())
    {
        DLOG_ERROR("Primary Key EventTyepName is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFEventTypeDetailsTPBQuery::sql_IWFEventDetails_Create_Select_Query(EventType *pEventType, char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_EVENT_TYPE_DETAILS_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");
    if(pEventType->has_eventtypemappingid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_EVENT_TYPE_MAPPING_ID = %d and", pEventType->eventtypemappingid());
    }
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);

}

void IWFEventTypeDetailsTPBQuery::sql_IWFEventTypeDetails_Create_Select_Query(EventType *pEventType,std::string RuleName, std::string CallScenario, char *pStatement, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_EVENT_TYPE_DETAILS_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(RuleName.c_str() != NULL && CallScenario.c_str() != NULL)
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_EVENT_TYPE_MAPPING_ID=(select IWF_EVENT_TYPE_MAPPING_ID from IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='%s') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = '%s')) and IWF_EVENT_TYPE_ID = (select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='%s')) and ",RuleName.c_str(),CallScenario.c_str(),pEventType->eventtypename().c_str());
    }
    


    ArmData* pArmData = NULL;
    if(pEventType->armdatval_size() > iIndex && iIndex > -1)
    {
        pArmData = pEventType->mutable_armdatval(iIndex);

        if(pArmData->has_monitormode())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"MONITOR_MODE = '%s' and", pArmData->monitormode().c_str());
        }

        if(pArmData->has_legid())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LEG_ID = '%s' and", pArmData->legid().c_str());
        }
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


