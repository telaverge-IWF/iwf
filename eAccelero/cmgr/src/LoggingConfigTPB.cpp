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

void LoggingConfigTPBQuery::sql_LoggingConfig_Create_Check_Modifcation_Query(LoggerConf *dreLoggerConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select LOG_ID from LOGGING_CONFIG_TB where COMPONENT_NAME='%s' ",dreLoggerConfigReq->componentname().c_str());

}

void LoggingConfigTPBQuery::sql_LoggingConfig_Create_Add_Query(LoggerConf *dreLoggerConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE(" > %s \n",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into LOGGING_CONFIG_TB "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(COMPONENT_NAME");   
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",dreLoggerConfigReq->componentname().c_str());

    if(dreLoggerConfigReq->has_channel())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",LOG_CHANNEL");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreLoggerConfigReq->channel());
    }

    if(dreLoggerConfigReq->has_level())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",LOG_LEVEL");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreLoggerConfigReq->level());
    }


    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);
    DLOG_NONE(" < %s \n",__FUNCTION__);
}

void LoggingConfigTPBQuery::sql_LoggingConfig_Create_Delete_Query(LoggerConf *dreLoggerConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s \n",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from LOGGING_CONFIG_TB where COMPONENT_NAME='%s' ",dreLoggerConfigReq->componentname().c_str()); 

    DLOG_NONE(" < %s \n",__FUNCTION__);
}

void LoggingConfigTPBQuery::sql_LoggingConfig_Create_Select_Query(LoggerConf *dreLoggerConfigReq,char *pStatement)
{

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from LOGGING_CONFIG_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s \n",__FUNCTION__);
    if(dreLoggerConfigReq->has_componentname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"COMPONENT_NAME='%s' and ",dreLoggerConfigReq->componentname().c_str());
    }


    if(dreLoggerConfigReq->has_channel())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LOG_CHANNEL=%d and ",dreLoggerConfigReq->channel());
    }

    if(dreLoggerConfigReq->has_level())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LOG_LEVEL=%d and ",dreLoggerConfigReq->level());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s \n",__FUNCTION__);
}

void LoggingConfigTPBQuery::sql_LoggingConfig_Create_Mod_Query(LoggerConf *dreLoggerConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s \n",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update LOGGING_CONFIG_TB set "); 

    if(dreLoggerConfigReq->has_channel())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LOG_CHANNEL=%d,",dreLoggerConfigReq->channel());
    }

    if(dreLoggerConfigReq->has_level())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LOG_LEVEL=%d,",dreLoggerConfigReq->level());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where COMPONENT_NAME='%s' ",dreLoggerConfigReq->componentname().c_str());

    DLOG_NONE(" < %s \n",__FUNCTION__);
}

DbStatus_e LoggingConfigTPBQuery::sql_LoggingConfig_Payload_Validation(LoggerConf *dreLoggerConfigReq)
{
    if(!dreLoggerConfigReq->has_componentname())
    {
        DLOG_ERROR("Primary Key componenet Name is not set in the request");
        return SET_LOGCONFIG_ERR_MANDATORY_PARAM_COMPONENT_MISSING; 
    }

    return DRE_DB_SUCCESS;
}

DbStatus_e LoggingConfigTPBQuery::sql_LoggingConfig_Check_All_Invalid(LoggerConf *dreLoggerConfigReq)
{

    if(dreLoggerConfigReq->has_channel())
    {
        return DRE_DB_FAIL;
    }

    if(dreLoggerConfigReq->has_level())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
