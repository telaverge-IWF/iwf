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

void IWFTranslatorRuleTPBQuery::sql_IWFTranslatorRule_Create_Check_Modifcation_Query(IwfTranslatorRuleConfig *IwfTranslatorRuleConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_TRANSLATOR_RULE_ID from IWF_TRANSLATOR_RULE_TB where RULE_NAME = '%s'",IwfTranslatorRuleConfigReq->translatorrulename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFTranslatorRuleTPBQuery::sql_IWFTranslatorRule_Create_Add_Query(IwfTranslatorRuleConfig *IwfTranslatorRuleConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};

    IwfTranslatorType *pIwfTranslatorTypeReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;


    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_TRANSLATOR_RULE_TB");
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(RULE_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",IwfTranslatorRuleConfigReq->translatorrulename().c_str());

    if(IwfTranslatorRuleConfigReq-> has_translatortype())
    {

        pIwfTranslatorTypeReq = IwfTranslatorRuleConfigReq -> mutable_translatortype();
        if(pIwfTranslatorTypeReq->has_translatortypename())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IWF_TRANSLATOR_TYPE_ID");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select IWF_TRANSLATOR_TYPE_ID from IWF_TRANSLATOR_TYPE_TB where IWF_TRANSLATOR_TYPE = '%s')",pIwfTranslatorTypeReq->translatortypename().c_str());
        }
    }

    if(IwfTranslatorRuleConfigReq->has_translatorinfo())
    {

        pIwfTranslatorConfigReq = IwfTranslatorRuleConfigReq -> mutable_translatorinfo();
        if(pIwfTranslatorConfigReq->has_translatorname())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IWF_TRANSLATOR_ID");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR ='%s')",pIwfTranslatorConfigReq->translatorname().c_str());
        }
    }

    if(IwfTranslatorRuleConfigReq->has_destinationname())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",DESTINATION_NAME");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfTranslatorRuleConfigReq->destinationname().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_destinationhost())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",DESTINATION_HOST");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfTranslatorRuleConfigReq->destinationhost().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_alternatehost())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ALTERNATE_HOST");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfTranslatorRuleConfigReq->alternatehost().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_alternaterealm())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ALTERNATE_REALM");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfTranslatorRuleConfigReq->alternaterealm().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_mcc())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",MCC");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfTranslatorRuleConfigReq->mcc().c_str());
    }
    if(IwfTranslatorRuleConfigReq->has_mnc())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",MNC");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfTranslatorRuleConfigReq->mnc().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_appid())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",APPLICATION_ID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfTranslatorRuleConfigReq->appid().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_ossn())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",OSSN");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfTranslatorRuleConfigReq->ossn());
    }

    if(IwfTranslatorRuleConfigReq->has_dssn())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",DSSN");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfTranslatorRuleConfigReq->dssn());
    }

    if(IwfTranslatorRuleConfigReq->has_httpurl())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",HTTP_URL");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfTranslatorRuleConfigReq->httpurl().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_webservice())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",WEB_SERVICE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfTranslatorRuleConfigReq->webservice().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_isservicekeyinrange())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IS_RANGE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfTranslatorRuleConfigReq->isservicekeyinrange());
    }

    if(IwfTranslatorRuleConfigReq->has_servicekeystartvalue())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SERVICE_KEY_START_VALUE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfTranslatorRuleConfigReq->servicekeystartvalue());
    }

    if(IwfTranslatorRuleConfigReq->has_servicekeyendvalue())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SERVICE_KEY_END_VALUE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfTranslatorRuleConfigReq->servicekeyendvalue());
    }

    if(IwfTranslatorRuleConfigReq->has_servicekey())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SERVICE_KEY");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfTranslatorRuleConfigReq->servicekey().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_imsiprefix())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IMSI_PREFIX");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfTranslatorRuleConfigReq->imsiprefix().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_proactionrulename())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PRO_ACTION_RULE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfTranslatorRuleConfigReq->proactionrulename().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_callinggtaddrdigits())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",CALLING_GT_ADDR_DIGITS");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfTranslatorRuleConfigReq->callinggtaddrdigits().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_servicecontextid())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SERVICE_CONTEXT_ID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfTranslatorRuleConfigReq->servicecontextid().c_str());
    }

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFTranslatorRuleTPBQuery::sql_IWFTranslatorRule_Create_Mod_Query(IwfTranslatorRuleConfig *IwfTranslatorRuleConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    IwfTranslatorType *pIwfTranslatorTypeReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;


    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_TRANSLATOR_RULE_TB set ");

    if(IwfTranslatorRuleConfigReq->has_translatortype())
    {
        pIwfTranslatorTypeReq = IwfTranslatorRuleConfigReq -> mutable_translatortype();
        if(pIwfTranslatorTypeReq->has_translatortypename())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_TRANSLATOR_TYPE_ID = (select IWF_TRANSLATOR_TYPE_ID from IWF_TRANSLATOR_TYPE_TB where IWF_TRANSLATOR_TYPE = '%s'),",pIwfTranslatorTypeReq->translatortypename().c_str());
        }
    }

    if(IwfTranslatorRuleConfigReq->has_translatorinfo())
    {
        pIwfTranslatorConfigReq = IwfTranslatorRuleConfigReq -> mutable_translatorinfo();
        if(pIwfTranslatorConfigReq->has_translatorname())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_TRANSLATOR_ID=(select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR='%s'),",pIwfTranslatorConfigReq->translatorname().c_str());
        }
    }

    if(IwfTranslatorRuleConfigReq->has_destinationname())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"DESTINATION_NAME='%s',",IwfTranslatorRuleConfigReq->destinationname().c_str());
        if(IwfTranslatorRuleConfigReq->has_destinationhost())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"DESTINATION_HOST='%s',",IwfTranslatorRuleConfigReq->destinationhost().c_str());
        }
        else
        {
            //Reset to NULL if user not providing primary host for modification
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"DESTINATION_HOST=NULL,");
        }
    }
    
    if(IwfTranslatorRuleConfigReq->has_alternatehost())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ALTERNATE_HOST='%s',",IwfTranslatorRuleConfigReq->alternatehost().c_str());
    }
    if(IwfTranslatorRuleConfigReq->has_alternaterealm())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ALTERNATE_REALM='%s',",IwfTranslatorRuleConfigReq->alternaterealm().c_str());
    }
    if(IwfTranslatorRuleConfigReq->has_mcc())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MCC ='%s',",IwfTranslatorRuleConfigReq->mcc().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_mnc())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MNC ='%s',",IwfTranslatorRuleConfigReq->mnc().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_appid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"APPLICATION_ID ='%s',",IwfTranslatorRuleConfigReq->appid().c_str());
    }
    if(IwfTranslatorRuleConfigReq->has_ossn())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"OSSN = %d,",IwfTranslatorRuleConfigReq->ossn());
    }

    if(IwfTranslatorRuleConfigReq->has_dssn())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"DSSN = %d,",IwfTranslatorRuleConfigReq->dssn());
    }

    if(IwfTranslatorRuleConfigReq->has_httpurl())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"HTTP_URL = '%s',",IwfTranslatorRuleConfigReq->httpurl().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_webservice())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"WEB_SERVICE = '%s',",IwfTranslatorRuleConfigReq->webservice().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_servicekey())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SERVICE_KEY = '%s',",IwfTranslatorRuleConfigReq->servicekey().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_imsiprefix())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IMSI_PREFIX = '%s',",IwfTranslatorRuleConfigReq->imsiprefix().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_proactionrulename())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PRO_ACTION_RULE = '%s',",IwfTranslatorRuleConfigReq->proactionrulename().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_isservicekeyinrange())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IS_RANGE = %d,",IwfTranslatorRuleConfigReq->isservicekeyinrange());
    }

    if(IwfTranslatorRuleConfigReq->has_servicekeystartvalue())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SERVICE_KEY_START_VALUE = %d,",IwfTranslatorRuleConfigReq->servicekeystartvalue());
    }

    if(IwfTranslatorRuleConfigReq->has_servicekeyendvalue())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SERVICE_KEY_END_VALUE = %d,",IwfTranslatorRuleConfigReq->servicekeyendvalue());
    }

    if(IwfTranslatorRuleConfigReq->has_callinggtaddrdigits())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"CALLING_GT_ADDR_DIGITS = '%s',",IwfTranslatorRuleConfigReq->callinggtaddrdigits().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_servicecontextid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SERVICE_CONTEXT_ID = '%s',",IwfTranslatorRuleConfigReq->servicecontextid().c_str());
    }

    pStatement[strlen(pStatement) -1] = ' ';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where RULE_NAME='%s' ",IwfTranslatorRuleConfigReq->translatorrulename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFTranslatorRuleTPBQuery::sql_IWFTranslatorRule_Create_Delete_Query(IwfTranslatorRuleConfig *IwfTranslatorRuleConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_TRANSLATOR_RULE_TB where RULE_NAME='%s'",IwfTranslatorRuleConfigReq->translatorrulename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFTranslatorRuleTPBQuery::sql_IWFAllTranslatorRule_Create_Delete_Query(char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_TRANSLATOR_RULE_TB ");

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFTranslatorRuleTPBQuery::sql_IWFTranslatorRule_Payload_Validation(IwfTranslatorRuleConfig *IwfTranslatorRuleConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(!IwfTranslatorRuleConfigReq->has_translatorrulename())
    {
        DLOG_ERROR("Primary Key RULE_NAME is not set in the request");
        return IWF_DB_FAIL;
    }

    return IWF_DB_SUCCESS;
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


void IWFTranslatorRuleTPBQuery::sql_IWFTranslatorRule_Create_Select_Query(IwfTranslatorRuleConfig *IwfTranslatorRuleConfigReq,char *pStatement)
{
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    int iFlag = 0;
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    IwfTranslatorType *pIwfTranslatorTypeReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;


    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_TRANSLATOR_RULE_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfTranslatorRuleConfigReq->has_translatorrulename())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RULE_NAME='%s' and ",IwfTranslatorRuleConfigReq->translatorrulename().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_destinationname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"DESTINATION_NAME='%s' and ",IwfTranslatorRuleConfigReq->destinationname().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_destinationhost())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"DESTINATION_HOST='%s' and ",IwfTranslatorRuleConfigReq->destinationhost().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_alternatehost())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ALTERNATE_HOST='%s' and ",IwfTranslatorRuleConfigReq->alternatehost().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_alternaterealm())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ALTERNATE_REALM='%s' and ",IwfTranslatorRuleConfigReq->alternaterealm().c_str());
    }
    if(IwfTranslatorRuleConfigReq->has_translatortype())
    {
        pIwfTranslatorTypeReq = IwfTranslatorRuleConfigReq -> mutable_translatortype();
        if(pIwfTranslatorTypeReq->has_translatortypename())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_TRANSLATOR_TYPE_ID=(select IWF_TRANSLATOR_TYPE_ID from IWF_TRANSLATOR_TYPE_TB where IWF_TRANSLATOR_TYPE = '%s') and ",pIwfTranslatorTypeReq->translatortypename().c_str());
        }
    }

    if(IwfTranslatorRuleConfigReq-> has_translatorinfo())
    {
        pIwfTranslatorConfigReq = IwfTranslatorRuleConfigReq -> mutable_translatorinfo();
        if(pIwfTranslatorConfigReq->has_translatorname())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_TRANSLATOR_ID=(select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR='%s') and ",pIwfTranslatorConfigReq->translatorname().c_str());
        }
    }

    if(IwfTranslatorRuleConfigReq->has_mcc())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"MCC= '%s' and ",IwfTranslatorRuleConfigReq->mcc().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_mnc())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"MNC = '%s' and ",IwfTranslatorRuleConfigReq->mnc().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_appid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"APPLICATION_ID = '%s' and ",IwfTranslatorRuleConfigReq->appid().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_ossn())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"OSSN = %d and ",IwfTranslatorRuleConfigReq->ossn());
    }

    if(IwfTranslatorRuleConfigReq->has_dssn())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"DSSN = %d and ",IwfTranslatorRuleConfigReq->dssn());
    }

    if(IwfTranslatorRuleConfigReq->has_httpurl())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"HTTP_URL = '%s' and ",IwfTranslatorRuleConfigReq->httpurl().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_webservice())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"WEB_SERVICE = '%s' and ",IwfTranslatorRuleConfigReq->webservice().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_isservicekeyinrange())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IS_RANGE = %d and ",IwfTranslatorRuleConfigReq->isservicekeyinrange());
    }

    if(IwfTranslatorRuleConfigReq->has_servicekeystartvalue())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SERVICE_KEY_START_VALUE = %d and ",IwfTranslatorRuleConfigReq->servicekeystartvalue());
    }

    if(IwfTranslatorRuleConfigReq->has_servicekeyendvalue())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SERVICE_KEY_END_VALUE = %d and ",IwfTranslatorRuleConfigReq->servicekeyendvalue());
    }

    if(IwfTranslatorRuleConfigReq->has_servicekey())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SERVICE_KEY = '%s' and ",IwfTranslatorRuleConfigReq->servicekey().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_imsiprefix())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IMSI_PREFIX = '%s' and ",IwfTranslatorRuleConfigReq->imsiprefix().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_proactionrulename())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PRO_ACTION_RULE = '%s' and ",IwfTranslatorRuleConfigReq->proactionrulename().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_callinggtaddrdigits())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"CALLING_GT_ADDR_DIGITS = '%s' and ",IwfTranslatorRuleConfigReq->callinggtaddrdigits().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_servicecontextid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SERVICE_CONTEXT_ID = '%s' and ",IwfTranslatorRuleConfigReq->servicecontextid().c_str());
    }
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFTranslatorRuleTPBQuery::sql_IWFTranslatorRule_Check_All_Invalid(IwfTranslatorRuleConfig *IwfTranslatorRuleConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    IwfTranslatorType *pIwfTranslatorTypeReq = NULL;
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;


    if(IwfTranslatorRuleConfigReq->has_translatorrulename())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_destinationname())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq ->has_translatortype())
    {
        pIwfTranslatorTypeReq = IwfTranslatorRuleConfigReq -> mutable_translatortype();
        if(pIwfTranslatorTypeReq->has_translatortypename())
        {
            return IWF_DB_FAIL;
        }
    }
    if(IwfTranslatorRuleConfigReq -> has_translatorinfo())
    {
        pIwfTranslatorConfigReq = IwfTranslatorRuleConfigReq -> mutable_translatorinfo();
        if(pIwfTranslatorConfigReq->has_translatorname())
        {
            return IWF_DB_FAIL;
        }
    }
    if(IwfTranslatorRuleConfigReq->has_mcc())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_mnc())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_appid())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_ossn())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_dssn())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_httpurl())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_webservice())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_isservicekeyinrange())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_servicekeystartvalue())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_servicekeyendvalue())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_callinggtaddrdigits())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_servicecontextid())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_imsiprefix())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_servicekey())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_proactionrulename())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_destinationhost())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_alternatehost())
    {
        return IWF_DB_FAIL;
    }
    if(IwfTranslatorRuleConfigReq->has_alternaterealm())
    {
        return IWF_DB_FAIL;
    }
    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
