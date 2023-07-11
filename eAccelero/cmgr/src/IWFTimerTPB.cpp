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

void IWFTimerTPBQuery::sql_IWFTimer_Create_Check_Modifcation_Query(IwfTimerConfig *IwfTimerConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_TIMER_ID from IWF_TIMER_TB where IWF_TIMER_NAME = '%s'",IwfTimerConfigReq->timername().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFTimerTPBQuery::sql_IWFTimer_Create_Add_Query(IwfTimerConfig *IwfTimerConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_TIMER_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(IwfTimerConfigReq->has_timername())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_TIMER_NAME,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",IwfTimerConfigReq->timername().c_str());
    }

    if(IwfTimerConfigReq->has_timervalue())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_TIMER_VALUE,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",IwfTimerConfigReq->timervalue());
    }

    sFieldName[strlen(sFieldName) -1] = ' ';
    sFieldValue[strlen(sFieldValue) -1] = ' ';
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFTimerTPBQuery::sql_IWFTimer_Create_Mod_Query(IwfTimerConfig *IwfTimerConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_TIMER_TB set "); 

    if(IwfTimerConfigReq->has_timervalue())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_TIMER_VALUE=%d,",IwfTimerConfigReq->timervalue());
    }

    pStatement[strlen(pStatement) -1] = ' ';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where IWF_TIMER_NAME = '%s'",IwfTimerConfigReq->timername().c_str());

    
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFTimerTPBQuery::sql_IWFTimer_Create_Delete_Query(IwfTimerConfig *IwfTimerConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from  IWF_TIMER_TB where IWF_TIMER_NAME = '%s'",IwfTimerConfigReq->timername().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFTimerTPBQuery::sql_IWFTimer_Payload_Validation(IwfTimerConfig *IwfTimerConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(!IwfTimerConfigReq->has_timername())
    {
        DLOG_ERROR("Unique Key IWF_TIMER_NAME is not set in the request");
        return IWF_DB_FAIL;
    }
    if(!IwfTimerConfigReq->has_timervalue())
    {
        DLOG_ERROR("Unique Key IWF_TIMER_VALUE_ is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFTimerTPBQuery::sql_IWFTimer_Create_Select_Query(IwfTimerConfig *IwfTimerConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_TIMER_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfTimerConfigReq->has_timername())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_TIMER_NAME='%s' and ",IwfTimerConfigReq->timername().c_str());
    }

    if(IwfTimerConfigReq->has_timervalue())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_TIMER_VALUE=%d and ",IwfTimerConfigReq->timervalue());
    }

    if(iFlag) 
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFTimerTPBQuery::sql_IWFTimer_Check_All_Invalid(IwfTimerConfig *IwfTimerConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(IwfTimerConfigReq->has_timername())
    {
        return IWF_DB_FAIL;
    }   
    if(IwfTimerConfigReq->has_timervalue())
    {
        return IWF_DB_FAIL;
    }
    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
