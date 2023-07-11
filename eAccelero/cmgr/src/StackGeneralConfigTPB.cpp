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

void StackGeneralConfigTPBQuery::sql_StackGeneralConfig_Create_Check_Modifcation_Query(GeneralConfig *generalConfigReq,char *pStatement)
{
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from STACK_GEN_CONFIG ");
}

void StackGeneralConfigTPBQuery::sql_StackGeneralConfig_Create_Add_Query(GeneralConfig *generalConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into STACK_GEN_CONFIG "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(generalConfigReq->has_enablepeeripcheck())
    { 
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"PEER_IP_CHECK_ENABLE"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d",generalConfigReq->enablepeeripcheck());
    }

    if(generalConfigReq->has_ispredictiveloopavdrequired())
    { 
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IS_PREDICTIVE_LOOP_AVD_REQUIRED"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d",generalConfigReq->ispredictiveloopavdrequired());
    }
    
    if(generalConfigReq->has_issnaptrsupported())
    { 
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IS_SNAPTR_SUPPORTED"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d",generalConfigReq->issnaptrsupported());
    }
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")"); 
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")"); 

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" < %s ",__FUNCTION__);


}

void StackGeneralConfigTPBQuery::sql_StackGeneralConfig_Create_Delete_Query(GeneralConfig *generalConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);


    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from STACK_GEN_CONFIG "); 

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void StackGeneralConfigTPBQuery::sql_StackGeneralConfig_Create_Mod_Query(GeneralConfig *generalConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update STACK_GEN_CONFIG set "); 


    if(generalConfigReq->has_enablepeeripcheck())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PEER_IP_CHECK_ENABLE=%d,",generalConfigReq->enablepeeripcheck());
    }

    if(generalConfigReq->has_ispredictiveloopavdrequired())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IS_PREDICTIVE_LOOP_AVD_REQUIRED=%d,",generalConfigReq->ispredictiveloopavdrequired());
    }
    
    if(generalConfigReq->has_issnaptrsupported())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IS_SNAPTR_SUPPORTED=%d,",generalConfigReq->issnaptrsupported());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    //  snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where GEN_CONFIG_ID=%d",generalConfigReq->realmname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e StackGeneralConfigTPBQuery::sql_StackGeneralConfig_Payload_Validation(GeneralConfig *generalConfigReq)
{

#if 0
    if (!generalConfigReq->has_realmname())
    {
        DLOG_ERROR("Primary Key General Config Id is not set in the request");
        return ERR_STACK_MANDATORY_PARAM_GEN_CONFIG_ID_MISSING; 
    }
#endif

    return DRE_DB_SUCCESS;
}

void StackGeneralConfigTPBQuery::sql_StackGeneralConfig_Create_Select_Query(GeneralConfig *generalConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from STACK_GEN_CONFIG"); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);


    if(generalConfigReq->has_enablepeeripcheck())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PEER_IP_CHECK_ENABLE=%d and ",generalConfigReq->enablepeeripcheck());
    }
    if(generalConfigReq->has_ispredictiveloopavdrequired())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IS_PREDICTIVE_LOOP_AVD_REQUIRED=%d and ",generalConfigReq->ispredictiveloopavdrequired());
    }
    if(generalConfigReq->has_issnaptrsupported())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IS_SNAPTR_SUPPORTED=%d and ",generalConfigReq->issnaptrsupported());
    }
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }


    DLOG_NONE(" < %s ",__FUNCTION__);

}

DbStatus_e StackGeneralConfigTPBQuery::sql_StackGeneralConfig_Check_All_Invalid(GeneralConfig *generalConfigReq)
{

    if(generalConfigReq->has_enablepeeripcheck())
    {
        return DRE_DB_FAIL;
    }

    if(generalConfigReq->has_ispredictiveloopavdrequired())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
