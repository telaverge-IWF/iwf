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

void IWFTranslatorTPBQuery::sql_IWFTranslator_Create_Check_Modifcation_Query(IwfTranslatorConfig *IwfTranslatorConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_TRANSLATOR_ID from IWF_TRANSLATOR_TB where IWF_TRANSLATOR='%s'",IwfTranslatorConfigReq->translatorname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFTranslatorTPBQuery::sql_IWFTranslator_Create_Add_Query(IwfTranslatorConfig *IwfTranslatorConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_TRANSLATOR_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(IWF_TRANSLATOR");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",IwfTranslatorConfigReq->translatorname().c_str());

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFTranslatorTPBQuery::sql_IWFTranslator_Create_Mod_Query(IwfTranslatorConfig *IwfTranslatorConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("Modify is not there for this table");
#if 0
    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_TRANSLATOR_TB set "); 


    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where IWF_TRANSLATOR='%s' ",IwfTranslatorConfigReq->endpointname().c_str());
#endif 
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);

}

void IWFTranslatorTPBQuery::sql_IWFTranslator_Create_Delete_Query(IwfTranslatorConfig *IwfTranslatorConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_TRANSLATOR_TB where IWF_TRANSLATOR='%s'",IwfTranslatorConfigReq->translatorname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFTranslatorTPBQuery::sql_IWFTranslator_Payload_Validation(IwfTranslatorConfig *IwfTranslatorConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(!IwfTranslatorConfigReq->has_translatorname())
    {
        DLOG_ERROR("Primary Key IWF_TRANSLATOR_NAME is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFTranslatorTPBQuery::sql_IWFTranslator_Create_Select_Query(IwfTranslatorConfig *IwfTranslatorConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_TRANSLATOR_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfTranslatorConfigReq->has_translatorid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_TRANSLATOR_ID=%d and ",IwfTranslatorConfigReq->translatorid());
    }

    if(IwfTranslatorConfigReq->has_translatorname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_TRANSLATOR='%s' and ",IwfTranslatorConfigReq->translatorname().c_str());
    }

    if(iFlag) 
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFTranslatorTPBQuery::sql_IWFTranslator_Check_All_Invalid(IwfTranslatorConfig *IwfTranslatorConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(IwfTranslatorConfigReq->has_translatorname())
    {
        return IWF_DB_FAIL;
    }   

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
