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

void CapRoIdpSmsConfigTPBQuery::sql_CapRoIdpSmsConfig_Create_Check_Modifcation_Query(IwfCapToRoConfig *IwfCapToRoConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    CapRoIdpSmsConfig *pCapRoIdpSmsConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pCapRoIdpSmsConfigReq = IwfCapToRoConfigReq -> mutable_caproidpsmsinfo();
    pIwfTranslatorConfigReq = IwfCapToRoConfigReq -> mutable_translatorinfo();

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select CAPRO_IDPSMS_CONFIG_ID from CAPRO_IDPSMS_CONFIG_TB where CAPRO_CONFIG_ID=(select IWF_CAPRO_CONFIG_ID from IWF_CAPRO_CONFIG_TB where IWF_TRANSLATOR_ID = (select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR = '%s'))",pIwfTranslatorConfigReq->translatorname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void CapRoIdpSmsConfigTPBQuery::sql_CapRoIdpSmsConfig_Create_Add_Query(IwfCapToRoConfig *IwfCapToRoConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    CapRoIdpSmsConfig *pCapRoIdpSmsConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    
    if(IwfCapToRoConfigReq->has_caproidpsmsinfo())
    {
        pCapRoIdpSmsConfigReq = IwfCapToRoConfigReq -> mutable_caproidpsmsinfo();
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into CAPRO_IDPSMS_CONFIG_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(IwfCapToRoConfigReq->has_translatorinfo())
    {
        pIwfTranslatorConfigReq = IwfCapToRoConfigReq -> mutable_translatorinfo();
        if(pIwfTranslatorConfigReq -> has_translatorname())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"CAPRO_CONFIG_ID,");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_CAPRO_CONFIG_ID from IWF_CAPRO_CONFIG_TB where IWF_TRANSLATOR_ID = (select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR ='%s')),",pIwfTranslatorConfigReq->translatorname().c_str());
        }
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_smsnode())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"SMS_NODE,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pCapRoIdpSmsConfigReq->smsnode());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_clientaddress())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"CLIENT_ADDRESS,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pCapRoIdpSmsConfigReq->clientaddress().c_str());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_originatorsccpaddress())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"ORIGINATOR_SCCP_ADDRESS,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pCapRoIdpSmsConfigReq->originatorsccpaddress().c_str());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_replypathrequested())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"REPLY_PATH_REQUESTED,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pCapRoIdpSmsConfigReq->replypathrequested());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_mscservicespecifictype())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"MSC_SERVICE_SPECIFIC_TYPE,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pCapRoIdpSmsConfigReq->mscservicespecifictype());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_sgsnservicespecifictype())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"SGSN_SERVICE_SPECIFIC_TYPE,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pCapRoIdpSmsConfigReq->sgsnservicespecifictype());
    }
    
    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_servicecontextid())
    {   
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"SERVICE_CONTEXT_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pCapRoIdpSmsConfigReq->servicecontextid().c_str());
    }   

    sFieldName[strlen(sFieldName) -1] = ' ';
    sFieldValue[strlen(sFieldValue) -1] = ' ';
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void CapRoIdpSmsConfigTPBQuery::sql_CapRoIdpSmsConfig_Create_Mod_Query(IwfCapToRoConfig *IwfCapToRoConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    CapRoIdpSmsConfig *pCapRoIdpSmsConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pIwfTranslatorConfigReq = IwfCapToRoConfigReq -> mutable_translatorinfo();


    if(IwfCapToRoConfigReq->has_caproidpsmsinfo())
    {
        pCapRoIdpSmsConfigReq = IwfCapToRoConfigReq -> mutable_caproidpsmsinfo();
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update CAPRO_IDPSMS_CONFIG_TB set "); 
#if 0
    if(IwfCapToRoConfigReq->has_translatorinfo())
    {
        pIwfTranslatorConfigReq = IwfCapToRoConfigReq -> mutable_translatorinfo();
        if(pIwfTranslatorConfigReq -> has_translatorname())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"(select IWF_TRANSLATOR_ID from IWF_CAPRO_CONFIG_TB where IWF_CAPRO_CONFIG_ID = (select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR ='%s')),",pIwfTranslatorConfigReq->translatorname().c_str());
        }
    }
#endif
    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_smsnode())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SMS_NODE=%d,",pCapRoIdpSmsConfigReq->smsnode());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_clientaddress())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"CLIENT_ADDRESS='%s',",pCapRoIdpSmsConfigReq->clientaddress().c_str());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_originatorsccpaddress())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ORIGINATOR_SCCP_ADDRESS='%s',",pCapRoIdpSmsConfigReq->originatorsccpaddress().c_str());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_replypathrequested())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"REPLY_PATH_REQUESTED=%d,",pCapRoIdpSmsConfigReq->replypathrequested());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_mscservicespecifictype())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MSC_SERVICE_SPECIFIC_TYPE=%d,",pCapRoIdpSmsConfigReq->mscservicespecifictype());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_sgsnservicespecifictype())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SGSN_SERVICE_SPECIFIC_TYPE=%d,",pCapRoIdpSmsConfigReq->sgsnservicespecifictype());
    }
    
    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_servicecontextid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SERVICE_CONTEXT_ID='%s',",pCapRoIdpSmsConfigReq->servicecontextid().c_str());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where CAPRO_CONFIG_ID=(select IWF_CAPRO_CONFIG_ID from IWF_CAPRO_CONFIG_TB where IWF_TRANSLATOR_ID = (select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR ='%s'))",pIwfTranslatorConfigReq->translatorname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void CapRoIdpSmsConfigTPBQuery::sql_CapRoIdpSmsConfig_Create_Delete_Query(IwfCapToRoConfig *IwfCapToRoConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    CapRoIdpSmsConfig *pCapRoIdpSmsConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pCapRoIdpSmsConfigReq = IwfCapToRoConfigReq -> mutable_caproidpsmsinfo();
    pIwfTranslatorConfigReq = IwfCapToRoConfigReq -> mutable_translatorinfo();

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from CAPRO_IDPSMS_CONFIG_TB where CAPRO_CONFIG_ID=(select IWF_CAPRO_CONFIG_ID from IWF_CAPRO_CONFIG_TB where IWF_TRANSLATOR_ID = (select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR = '%s'))",pIwfTranslatorConfigReq->translatorname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e CapRoIdpSmsConfigTPBQuery::sql_CapRoIdpSmsConfig_Payload_Validation(IwfCapToRoConfig *IwfCapToRoConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    CapRoIdpSmsConfig *pCapRoIdpSmsConfigReq = NULL;
    pCapRoIdpSmsConfigReq = IwfCapToRoConfigReq -> mutable_caproidpsmsinfo();


    if(pCapRoIdpSmsConfigReq && IwfCapToRoConfigReq -> has_translatorinfo())
    {
        DLOG_ERROR("Primary Key IWF_SIGTRAN_SCTP_PROFILE_NAME is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void CapRoIdpSmsConfigTPBQuery::sql_CapRoIdpSmsConfig_Create_Select_Query(IwfCapToRoConfig *IwfCapToRoConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    CapRoIdpSmsConfig *pCapRoIdpSmsConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;

    if(IwfCapToRoConfigReq->has_caproidpsmsinfo())
    {
        pCapRoIdpSmsConfigReq = IwfCapToRoConfigReq -> mutable_caproidpsmsinfo();
    }

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from CAPRO_IDPSMS_CONFIG_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfCapToRoConfigReq->has_translatorinfo())
    {
        pIwfTranslatorConfigReq = IwfCapToRoConfigReq -> mutable_translatorinfo();
        if(pIwfTranslatorConfigReq -> has_translatorname())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"CAPRO_CONFIG_ID=(select IWF_CAPRO_CONFIG_ID from IWF_CAPRO_CONFIG_TB where IWF_TRANSLATOR_ID = (select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR = '%s')) and ",pIwfTranslatorConfigReq->translatorname().c_str());
        }
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_smsnode())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SMS_NODE=%d and ",pCapRoIdpSmsConfigReq->smsnode());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_clientaddress())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"CLIENT_ADDRESS='%s' and ",pCapRoIdpSmsConfigReq->clientaddress().c_str());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_originatorsccpaddress())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ORIGINATOR_SCCP_ADDRESS='%s' and ",pCapRoIdpSmsConfigReq->originatorsccpaddress().c_str());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_replypathrequested())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REPLY_PATH_REQUESTED=%d and ",pCapRoIdpSmsConfigReq->replypathrequested());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_mscservicespecifictype())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"MSC_SERVICE_SPECIFIC_TYPE=%d and ",pCapRoIdpSmsConfigReq->mscservicespecifictype());
    }

    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_sgsnservicespecifictype())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SGSN_SERVICE_SPECIFIC_TYPE=%d and ",pCapRoIdpSmsConfigReq->sgsnservicespecifictype());
    }
    
    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_servicecontextid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SERVICE_CONTEXT_ID='%s' and ",pCapRoIdpSmsConfigReq->servicecontextid().c_str());
    }

    if(iFlag) 
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e CapRoIdpSmsConfigTPBQuery::sql_CapRoIdpSmsConfig_Check_All_Invalid(IwfCapToRoConfig *IwfCapToRoConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    CapRoIdpSmsConfig *pCapRoIdpSmsConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;

    if(IwfCapToRoConfigReq->has_caproidpsmsinfo())
    {
        pCapRoIdpSmsConfigReq = IwfCapToRoConfigReq -> mutable_caproidpsmsinfo();
    }

    if(IwfCapToRoConfigReq->has_translatorinfo())
    {
        pIwfTranslatorConfigReq = IwfCapToRoConfigReq -> mutable_translatorinfo();
        if(pIwfTranslatorConfigReq -> has_translatorname())
        {
            return IWF_DB_FAIL;
        }
    }
    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_smsnode())
    {
        return IWF_DB_FAIL;
    }   
    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_clientaddress())
    {
        return IWF_DB_FAIL;
    }
    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_originatorsccpaddress())
    {
        return IWF_DB_FAIL;
    }
    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_replypathrequested())
    {
        return IWF_DB_FAIL;
    }
    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_mscservicespecifictype())
    {
        return IWF_DB_FAIL;
    }
    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_sgsnservicespecifictype())
    {
        return IWF_DB_FAIL;
    }
    if(pCapRoIdpSmsConfigReq && pCapRoIdpSmsConfigReq->has_servicecontextid())
    {
        return IWF_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
