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

void IWFMapS6aConfigTPBQuery::sql_IWFMapS6aConfig_Create_Check_Modifcation_Query(IwfMapToS6aConfig *IwfMapToS6aConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pIwfTranslatorConfigReq = IwfMapToS6aConfigReq -> mutable_translatorinfo();

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_MAPS6A_CONFIG_ID from IWF_MAPS6A_CONFIG_TB where IWF_TRANSLATOR_ID = (select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR='%s')",pIwfTranslatorConfigReq->translatorname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFMapS6aConfigTPBQuery::sql_IWFMapS6aConfig_Create_Add_Query(IwfMapToS6aConfig *IwfMapToS6aConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};

    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_MAPS6A_CONFIG_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(IwfMapToS6aConfigReq -> has_translatorinfo())
    {
        pIwfTranslatorConfigReq = IwfMapToS6aConfigReq -> mutable_translatorinfo();
        if(pIwfTranslatorConfigReq -> has_translatorname())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_TRANSLATOR_ID,");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR = '%s'),",pIwfTranslatorConfigReq->translatorname().c_str());
        }
    }

    if(IwfMapToS6aConfigReq -> has_hlrnumber())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"HLR_NUMBER,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",IwfMapToS6aConfigReq->hlrnumber().c_str());
    }

    sFieldName[strlen(sFieldName) - 1]   = ' ';
    sFieldValue[strlen(sFieldValue) - 1] = ' ';

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFMapS6aConfigTPBQuery::sql_IWFMapS6aConfig_Create_Mod_Query(IwfMapToS6aConfig *IwfMapToS6aConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pIwfTranslatorConfigReq = IwfMapToS6aConfigReq -> mutable_translatorinfo();

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_MAPS6A_CONFIG_TB set "); 

    if(IwfMapToS6aConfigReq->has_hlrnumber())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"HLR_NUMBER='%s',",IwfMapToS6aConfigReq->hlrnumber().c_str());
    }
    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where IWF_TRANSLATOR_ID=(select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR = '%s') ",pIwfTranslatorConfigReq->translatorname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);

}

void IWFMapS6aConfigTPBQuery::sql_IWFMapS6aConfig_Create_Delete_Query(IwfMapToS6aConfig *IwfMapToS6aConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    pIwfTranslatorConfigReq = IwfMapToS6aConfigReq -> mutable_translatorinfo();

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete * from IWF_MAPS6A_CONFIG_TB where IWF_TRANSLATOR_ID = (select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR = '%s')",pIwfTranslatorConfigReq->translatorname().c_str());
 
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFMapS6aConfigTPBQuery::sql_IWFMapS6aConfig_Payload_Validation(IwfMapToS6aConfig *IwfMapToS6aConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;

    if(!IwfMapToS6aConfigReq->has_translatorinfo())
    {
        pIwfTranslatorConfigReq = IwfMapToS6aConfigReq -> mutable_translatorinfo();
        if(pIwfTranslatorConfigReq -> has_translatorname())
        {
            DLOG_ERROR("Primary Key IWF_TRANSLATOR_NAME is not set in the request");
            return IWF_DB_FAIL;
        }
    }
    if(!IwfMapToS6aConfigReq->has_hlrnumber())
    {
        DLOG_ERROR("Primary Key HLR_NUMBER is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFMapS6aConfigTPBQuery::sql_IWFMapS6aConfig_Create_Select_Query(IwfMapToS6aConfig *IwfMapToS6aConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_MAPS6A_CONFIG_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfMapToS6aConfigReq -> has_translatorinfo())
    {
        pIwfTranslatorConfigReq = IwfMapToS6aConfigReq -> mutable_translatorinfo();
        if(pIwfTranslatorConfigReq -> has_translatorname())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_TRANSLATOR_ID=(select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR = '%s') and ",pIwfTranslatorConfigReq->translatorname().c_str());
        }
    }

    if(IwfMapToS6aConfigReq->has_hlrnumber())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"HLR_NUMBER='%s' and ",IwfMapToS6aConfigReq->hlrnumber().c_str());
    }

    if(iFlag) 
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFMapS6aConfigTPBQuery::sql_IWFMapS6aConfig_Check_All_Invalid(IwfMapToS6aConfig *IwfMapToS6aConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    IwfTranslatorConfig *pIwfTranslatorConfigReq = NULL;

    if(IwfMapToS6aConfigReq -> has_translatorinfo())
    {
        pIwfTranslatorConfigReq = IwfMapToS6aConfigReq -> mutable_translatorinfo();
        if(pIwfTranslatorConfigReq -> has_translatorname())
        {
            return IWF_DB_FAIL;
        }
    }   
    if(IwfMapToS6aConfigReq -> has_hlrnumber())
    {
        return IWF_DB_FAIL;
    }   

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
