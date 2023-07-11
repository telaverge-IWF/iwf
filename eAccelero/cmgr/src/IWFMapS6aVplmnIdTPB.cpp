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

void IWFMapS6aVplmnIdTPBQuery::sql_IWFMapS6aVplmnId_Create_Check_Modifcation_Query(IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfig,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_MAPS6A_VPLMN_CONFIG_ID from IWF_MAPS6A_VPLMN_ID_CONFIG_TB where ALLOWED_VPLMN_ID='%s'",pIwfMapToS6aVplmnIdConfig->allowedvplmnid().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFMapS6aVplmnIdTPBQuery::sql_IWFMapS6aVplmnId_Create_Check_Modifcation_Query(IwfMapToS6aConfig *IwfMapToS6aConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
#if 0
    IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfigReq = NULL;

    if(IwfMapToS6aConfigReq -> maptos6avplmnidinfo_size() > iIndex && iIndex > -1)
    {
        pIwfMapToS6aVplmnIdConfigReq = IwfMapToS6aConfigReq -> mutable_maptos6avplmnidinfo(iIndex);
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_MAPS6A_VPLMN_CONFIG_ID from IWF_MAPS6A_VPLMN_ID_CONFIG_TB where IWF_TRANSLATOR_RULE_ID=(select IWF_TRANSLATOR_RULE_ID from IWF_TRANSLATOR_RULE_TB where RULE_NAME ='%s') and VPLMN_ID='%s'",IwfMapToS6aConfigReq->translatorrulename().c_str(),pIwfMapToS6aVplmnIdConfigReq->allowedvplmnid().c_str());
    }
    else
    {
        DLOG_WARNING("Other_Home_IP is not configured, wrong iIndex = %d , sctpendpointinfo_size() = %d",iIndex,IwfMapToS6aConfigReq->maptos6avplmnidinfo_size());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }
#endif
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFMapS6aVplmnIdTPBQuery::sql_IWFMapS6aVplmnId_Create_Add_Query(IwfMapToS6aConfig *IwfMapToS6aConfigReq,char *pStatement,int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  
    IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfigReq = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_MAPS6A_VPLMN_ID_CONFIG_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(IwfMapToS6aConfigReq -> maptos6avplmnidinfo_size() > iIndex && iIndex > -1)
    {
        pIwfMapToS6aVplmnIdConfigReq = IwfMapToS6aConfigReq -> mutable_maptos6avplmnidinfo(iIndex);

        if(pIwfMapToS6aVplmnIdConfigReq->has_allowedvplmnid())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"ALLOWED_VPLMN_ID,");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pIwfMapToS6aVplmnIdConfigReq->allowedvplmnid().c_str());
        }

    }

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_MAPS6A_CONFIG_ID,");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_MAPS6A_CONFIG_ID from IWF_MAPS6A_CONFIG_TB ),");

    sFieldValue[strlen(sFieldValue) - 1] = ' ';
    sFieldName[strlen(sFieldName) - 1]   = ' ';

    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFMapS6aVplmnIdTPBQuery::sql_IWFMapS6aVplmnId_Create_Mod_Query(IwfMapToS6aConfig *IwfMapToS6aConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    DLOG_DEBUG("so update is not possible for vplmnid");

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFMapS6aVplmnIdTPBQuery::sql_IWFMapS6aVplmnId_Create_Delete_Query(IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_MAPS6A_VPLMN_ID_CONFIG_TB where ALLOWED_VPLMN_ID='%s'",pIwfMapToS6aVplmnIdConfigReq->allowedvplmnid().c_str());
    
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFMapS6aVplmnIdTPBQuery::sql_IWFMapS6aVplmnId_Create_Delete_Query(IwfMapToS6aConfig *IwfMapToS6aConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
#if 0
    IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfigReq = NULL;
    if(IwfMapToS6aConfigReq -> maptos6avplmnidinfo_size() > iIndex && iIndex > -1)
    {
        pIwfMapToS6aVplmnIdConfigReq = IwfMapToS6aConfigReq -> mutable_maptos6avplmnidinfo(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_MAPS6A_VPLMN_ID_CONFIG_TB where IWF_TRANSLATOR_RULE_ID=(select IWF_TRANSLATOR_RULE_ID from IWF_TRANSLATOR_RULE_TB where RULE_NAME ='%s') and VPLMN_ID='%s'",IwfMapToS6aConfigReq->translatorrulename().c_str(),pIwfMapToS6aVplmnIdConfigReq->allowedvplmnid().c_str());
#endif
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFMapS6aVplmnIdTPBQuery::sql_IWFMapS6aVplmnId_Payload_Validation(IwfMapToS6aConfig *IwfMapToS6aConfigReq,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfigReq = NULL;
    if(IwfMapToS6aConfigReq -> maptos6avplmnidinfo_size() > iIndex && iIndex > -1)
    {
        pIwfMapToS6aVplmnIdConfigReq = IwfMapToS6aConfigReq -> mutable_maptos6avplmnidinfo(iIndex);

        if(!pIwfMapToS6aVplmnIdConfigReq->has_allowedvplmnid())
        {
            DLOG_ERROR("Primary Key vplmnid is not set in the request");
            return IWF_DB_FAIL;
        }
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFMapS6aVplmnIdTPBQuery::sql_IWFMapS6aVplmnId_Create_Select_Query(IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfig,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_MAPS6A_VPLMN_ID_CONFIG_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pIwfMapToS6aVplmnIdConfig->has_allowedvplmnid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ALLOWED_VPLMN_ID='%s' and ",pIwfMapToS6aVplmnIdConfig->allowedvplmnid().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


void IWFMapS6aVplmnIdTPBQuery::sql_IWFMapS6aVplmnId_Create_Select_Query(IwfMapToS6aConfig *IwfMapToS6aConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfigReq = NULL;

    if(IwfMapToS6aConfigReq -> maptos6avplmnidinfo_size() > iIndex && iIndex > -1)
    {
        pIwfMapToS6aVplmnIdConfigReq = IwfMapToS6aConfigReq -> mutable_maptos6avplmnidinfo(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_MAPS6A_VPLMN_ID_CONFIG_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");


    if(pIwfMapToS6aVplmnIdConfigReq && pIwfMapToS6aVplmnIdConfigReq->has_allowedvplmnid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ALLOWED_VPLMN_ID='%s' and ",pIwfMapToS6aVplmnIdConfigReq->allowedvplmnid().c_str());
    }


    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFMapS6aVplmnIdTPBQuery::sql_IWFMapS6aVplmnId_Check_All_Invalid(IwfMapToS6aConfig *IwfMapToS6aConfigReq,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfigReq = NULL;

    if(IwfMapToS6aConfigReq -> maptos6avplmnidinfo_size() > iIndex && iIndex > -1)
    {
        pIwfMapToS6aVplmnIdConfigReq = IwfMapToS6aConfigReq -> mutable_maptos6avplmnidinfo(iIndex);
    }

    if(pIwfMapToS6aVplmnIdConfigReq && pIwfMapToS6aVplmnIdConfigReq->has_allowedvplmnid())
    {
        return IWF_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
