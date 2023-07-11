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

void CapRoIdpConfigTPBQuery::sql_CapRoIdpConfig_Create_Check_Modifcation_Query(IwfCapToRoConfig *IwfCapToRoConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    CapRoIdpConfig *pCapRoIdpConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pCapRoIdpConfigReq = IwfCapToRoConfigReq -> mutable_caproidpinfo();
    pIwfTranslatorConfigReq = IwfCapToRoConfigReq -> mutable_translatorinfo();

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select CAPRO_IDP_CONFIG_ID from CAPRO_IDP_CONFIG_TB where CAPRO_CONFIG_ID=(select IWF_CAPRO_CONFIG_ID from IWF_CAPRO_CONFIG_TB where IWF_TRANSLATOR_ID = (select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR = '%s'))",pIwfTranslatorConfigReq->translatorname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void CapRoIdpConfigTPBQuery::sql_CapRoIdpConfig_Create_Add_Query(IwfCapToRoConfig *IwfCapToRoConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    CapRoIdpConfig *pCapRoIdpConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;

    if(IwfCapToRoConfigReq->has_caproidpinfo())
    {
        pCapRoIdpConfigReq = IwfCapToRoConfigReq -> mutable_caproidpinfo();
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into CAPRO_IDP_CONFIG_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(IwfCapToRoConfigReq->has_translatorinfo())
    {
        pIwfTranslatorConfigReq = IwfCapToRoConfigReq -> mutable_translatorinfo();
        if(pIwfTranslatorConfigReq -> has_translatorname())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"CAPRO_CONFIG_ID,");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_CAPRO_CONFIG_ID from IWF_CAPRO_CONFIG_TB),");
//            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_TRANSLATOR_ID from IWF_CAPRO_CONFIG_TB where IWF_CAPRO_CONFIG_ID = (select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR ='%s')),",pIwfTranslatorConfigReq->translatorname().c_str());
        }
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq ->has_nodefunctionality())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"NODE_FUNCTIONALITY,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pCapRoIdpConfigReq->nodefunctionality());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_sipmethod())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"SIP_METHOD,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pCapRoIdpConfigReq->sipmethod().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_orignatingtoi())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"ORIGINATING_TOI,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pCapRoIdpConfigReq->orignatingtoi().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_terminatingtoi())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"TERMINATING_TOI,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pCapRoIdpConfigReq->terminatingtoi().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_servicecontextid())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"SERVICE_CONTEXT_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pCapRoIdpConfigReq->servicecontextid().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_causecode())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"CAUSE_CODE,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pCapRoIdpConfigReq->causecode().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_mscservicespecfictype())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"MSC_SERVICE_SPECIFIC_TYPE,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pCapRoIdpConfigReq->mscservicespecfictype());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_gmscservicespecifictype())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"GMSC_SERVICE_SPECIFIC_TYPE,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pCapRoIdpConfigReq->gmscservicespecifictype());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_cpcservicespecifictype())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"CPC_SERVICE_SPECIFIC_TYPE,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pCapRoIdpConfigReq->cpcservicespecifictype());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_multipleserviceindicator())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"MULTIPLE_SERVICES_INDICATOR,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pCapRoIdpConfigReq->multipleserviceindicator());
    }

    sFieldName[strlen(sFieldName) -1] = ' ';
    sFieldValue[strlen(sFieldValue) -1] = ' ';
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void CapRoIdpConfigTPBQuery::sql_CapRoIdpConfig_Create_Mod_Query(IwfCapToRoConfig *IwfCapToRoConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    CapRoIdpConfig *pCapRoIdpConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;

    pIwfTranslatorConfigReq = IwfCapToRoConfigReq -> mutable_translatorinfo();
    if(IwfCapToRoConfigReq->has_caproidpinfo())
    {
        pCapRoIdpConfigReq = IwfCapToRoConfigReq -> mutable_caproidpinfo();
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update CAPRO_IDP_CONFIG_TB set "); 

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_nodefunctionality())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"NODE_FUNCTIONALITY=%d,",pCapRoIdpConfigReq->nodefunctionality());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_sipmethod())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SIP_METHOD='%s',",pCapRoIdpConfigReq->sipmethod().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_orignatingtoi())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ORIGINATING_TOI='%s',",pCapRoIdpConfigReq->orignatingtoi().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_terminatingtoi())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TERMINATING_TOI='%s',",pCapRoIdpConfigReq->terminatingtoi().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_servicecontextid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SERVICE_CONTEXT_ID='%s',",pCapRoIdpConfigReq->servicecontextid().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_causecode())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"CAUSE_CODE='%s',",pCapRoIdpConfigReq->causecode().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_mscservicespecfictype())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MSC_SERVICE_SPECIFIC_TYPE=%d,",pCapRoIdpConfigReq->mscservicespecfictype());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_gmscservicespecifictype())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"GMSC_SERVICE_SPECIFIC_TYPE=%d,",pCapRoIdpConfigReq->gmscservicespecifictype());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_cpcservicespecifictype())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"CPC_SERVICE_SPECIFIC_TYPE=%d,",pCapRoIdpConfigReq->cpcservicespecifictype());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_multipleserviceindicator())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MULTIPLE_SERVICES_INDICATOR=%d,",pCapRoIdpConfigReq->multipleserviceindicator());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where CAPRO_CONFIG_ID=(select IWF_CAPRO_CONFIG_ID from IWF_CAPRO_CONFIG_TB where IWF_TRANSLATOR_ID = (select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR = '%s'))",pIwfTranslatorConfigReq->translatorname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void CapRoIdpConfigTPBQuery::sql_CapRoIdpConfig_Create_Delete_Query(IwfCapToRoConfig *IwfCapToRoConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    CapRoIdpConfig *pCapRoIdpConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pCapRoIdpConfigReq = IwfCapToRoConfigReq -> mutable_caproidpinfo();
    pIwfTranslatorConfigReq = IwfCapToRoConfigReq -> mutable_translatorinfo();

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete  from CAPRO_IDP_CONFIG_TB where CAPRO_CONFIG_ID=(select IWF_CAPRO_CONFIG_ID from IWF_CAPRO_CONFIG_TB where IWF_TRANSLATOR_ID = (select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR = '%s'))",pIwfTranslatorConfigReq->translatorname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e CapRoIdpConfigTPBQuery::sql_CapRoIdpConfig_Payload_Validation(IwfCapToRoConfig *IwfCapToRoConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    CapRoIdpConfig *pCapRoIdpConfigReq = NULL;
    //IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pCapRoIdpConfigReq = IwfCapToRoConfigReq -> mutable_caproidpinfo();


    if(pCapRoIdpConfigReq && IwfCapToRoConfigReq -> has_translatorinfo())
    {
        DLOG_ERROR("Primary Key translatorinfo() is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void CapRoIdpConfigTPBQuery::sql_CapRoIdpConfig_Create_Select_Query(IwfCapToRoConfig *IwfCapToRoConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    CapRoIdpConfig *pCapRoIdpConfigReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pCapRoIdpConfigReq = IwfCapToRoConfigReq -> mutable_caproidpinfo();
    if(IwfCapToRoConfigReq->has_caproidpinfo())
    {
        pCapRoIdpConfigReq = IwfCapToRoConfigReq -> mutable_caproidpinfo();
    }

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from CAPRO_IDP_CONFIG_TB "); 

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

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_nodefunctionality())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NODE_FUNCTIONALITY=%d and ",pCapRoIdpConfigReq->nodefunctionality());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_sipmethod())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SIP_METHOD='%s' and ",pCapRoIdpConfigReq->sipmethod().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_orignatingtoi())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ORIGINATING_TOI='%s' and ",pCapRoIdpConfigReq->orignatingtoi().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_terminatingtoi())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TERMINATING_TOI='%s' and ",pCapRoIdpConfigReq->terminatingtoi().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_servicecontextid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SERVICE_CONTEXT_ID='%s' and ",pCapRoIdpConfigReq->servicecontextid().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_causecode())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"CAUSE_CODE='%s' and ",pCapRoIdpConfigReq->causecode().c_str());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_mscservicespecfictype())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"MSC_SERVICE_SPECIFIC_TYPE=%d and ",pCapRoIdpConfigReq->mscservicespecfictype());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_gmscservicespecifictype())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"GMSC_SERVICE_SPECIFIC_TYPE=%d and ",pCapRoIdpConfigReq->gmscservicespecifictype());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_cpcservicespecifictype())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"CPC_SERVICE_SPECIFIC_TYPE=%d and ",pCapRoIdpConfigReq->cpcservicespecifictype());
    }

    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_multipleserviceindicator())
    {
        iFlag = 1;
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MULTIPLE_SERVICES_INDICATOR=%d and ",pCapRoIdpConfigReq->multipleserviceindicator());
    }

    if(iFlag) 
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e CapRoIdpConfigTPBQuery::sql_CapRoIdpConfig_Check_All_Invalid(IwfCapToRoConfig *IwfCapToRoConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    CapRoIdpConfig *pCapRoIdpConfigReq = NULL;
    pCapRoIdpConfigReq = IwfCapToRoConfigReq -> mutable_caproidpinfo();
#if 0
    if(IwfCapToRoConfigReq->has_caproidpinfo())
    {
        pCapRoIdpConfigReq = IwfCapToRoConfigReq -> mutable_caproidpinfo();
    }

    if(IwfCapToRoConfigReq->has_translatorinfo())
    {
        pIwfTranslatorConfigReq = IwfCapToRoConfigReq -> mutable_translatorinfo();
        if(pIwfTranslatorConfigReq -> has_translatorname())
        {
            return IWF_DB_FAIL;
        }
    }
#endif
    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_nodefunctionality())
    {
        return IWF_DB_FAIL;
    }   
    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_sipmethod())
    {
        return IWF_DB_FAIL;
    }
    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_orignatingtoi())
    {
        return IWF_DB_FAIL;
    }
    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_terminatingtoi())
    {
        return IWF_DB_FAIL;
    }
    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_servicecontextid())
    {
        return IWF_DB_FAIL;
    }
    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_causecode())
    {
        return IWF_DB_FAIL;
    }
    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_mscservicespecfictype())
    {
        return IWF_DB_FAIL;
    }
    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_gmscservicespecifictype())
    {
        return IWF_DB_FAIL;
    }
    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_cpcservicespecifictype())
    {
        return IWF_DB_FAIL;
    }
    if(pCapRoIdpConfigReq && pCapRoIdpConfigReq->has_multipleserviceindicator())
    {
        return IWF_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
