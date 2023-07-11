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

void IWFTranslatorRuleVplmnIdTPBQuery::sql_IWFVplmnId_Create_Check_Modifcation_Query(IwfVplmnIdConfig *pIwfVplmnIdConfig,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_TRANSLATOR_VPLMN_ID from IWF_TRANSLATOR_VPLMN_ID_TB where VPLMN_ID='%s'",pIwfVplmnIdConfig->allowedvplmnid().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFTranslatorRuleVplmnIdTPBQuery::sql_IWFVplmnId_Create_Check_Modifcation_Query(IwfTranslatorRuleConfig *IwfTranslatorRuleConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    IwfVplmnIdConfig *pIwfVplmnIdConfigReq = NULL;

    if(IwfTranslatorRuleConfigReq -> vplmninfo_size() > iIndex && iIndex > -1)
    {
        pIwfVplmnIdConfigReq = IwfTranslatorRuleConfigReq -> mutable_vplmninfo(iIndex);
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_TRANSLATOR_VPLMN_ID from IWF_TRANSLATOR_VPLMN_ID_TB where IWF_TRANSLATOR_RULE_ID=(select IWF_TRANSLATOR_RULE_ID from IWF_TRANSLATOR_RULE_TB where RULE_NAME ='%s') and VPLMN_ID='%s'",IwfTranslatorRuleConfigReq->translatorrulename().c_str(),pIwfVplmnIdConfigReq->allowedvplmnid().c_str());
    }
    else
    {
        DLOG_WARNING("Other_Home_IP is not configured, wrong iIndex = %d , sctpendpointinfo_size() = %d",iIndex,IwfTranslatorRuleConfigReq->vplmninfo_size());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFTranslatorRuleVplmnIdTPBQuery::sql_IWFVplmnId_Create_Add_Query(IwfTranslatorRuleConfig *IwfTranslatorRuleConfigReq,char *pStatement,int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  
    IwfVplmnIdConfig *pIwfVplmnIdConfigReq = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_TRANSLATOR_VPLMN_ID_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(IwfTranslatorRuleConfigReq -> vplmninfo_size() > iIndex && iIndex > -1)
    {
        pIwfVplmnIdConfigReq = IwfTranslatorRuleConfigReq -> mutable_vplmninfo(iIndex);

        if(pIwfVplmnIdConfigReq->has_allowedvplmnid())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"VPLMN_ID,");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pIwfVplmnIdConfigReq->allowedvplmnid().c_str());
        }

    }

    if(IwfTranslatorRuleConfigReq->has_translatorrulename())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_TRANSLATOR_RULE_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_TRANSLATOR_RULE_ID from IWF_TRANSLATOR_RULE_TB where RULE_NAME ='%s'),",IwfTranslatorRuleConfigReq->translatorrulename().c_str());
    }

    sFieldValue[strlen(sFieldValue) - 1] = ' ';
    sFieldName[strlen(sFieldName) - 1]   = ' ';

    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFTranslatorRuleVplmnIdTPBQuery::sql_IWFVplmnId_Create_Mod_Query(IwfTranslatorRuleConfig *IwfTranslatorRuleConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    DLOG_DEBUG("All the fields are primary key, so update is not possible");
#if 0    
    if(AssociationConfigReq->ssn_config_size() > iIndex && iIndex > -1)
    {
	    IwfTranslatorRuleConfigReq = AssociationConfigReq->mutable_ssn_config(iIndex);
    }


    snprintf(pStatement,MAX_STATEMENT_SIZE,"update LOCAL_SSN_TABLE set "); 

    if(AssociationConfigReq->has_pointcode())
    {
	    IwfTranslatorRuleConfig* IwfTranslatorRuleConfigReq = AssociationConfigReq->mutable_ssn_config(iIndex);
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LOCAL_CONFIG_ID=(select LOCAL_CONFIG_ID from LOCAL_CONFIG_TB when POINTCODE = %d),",AssociationConfigReq->pointcode());

    }

    if(AssociationConfigReq->has_ssn())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SSN = '%d',",AssociationConfigReq->ssn());

    }

    pStatement[strlen(pStatement) -1] = ' ';
#endif

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFTranslatorRuleVplmnIdTPBQuery::sql_IWFVplmnId_Create_Delete_Query(IwfVplmnIdConfig *pIwfVplmnIdConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_TRANSLATOR_VPLMN_ID_TB where VPLMN_ID='%s'",pIwfVplmnIdConfigReq->allowedvplmnid().c_str());
    
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFTranslatorRuleVplmnIdTPBQuery::sql_IWFVplmnId_Create_Delete_Query(IwfTranslatorRuleConfig *IwfTranslatorRuleConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    IwfVplmnIdConfig *pIwfVplmnIdConfigReq = NULL;
    if(IwfTranslatorRuleConfigReq -> vplmninfo_size() > iIndex && iIndex > -1)
    {
        pIwfVplmnIdConfigReq = IwfTranslatorRuleConfigReq -> mutable_vplmninfo(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_TRANSLATOR_VPLMN_ID_TB where IWF_TRANSLATOR_RULE_ID=(select IWF_TRANSLATOR_RULE_ID from IWF_TRANSLATOR_RULE_TB where RULE_NAME ='%s') and VPLMN_ID='%s'",IwfTranslatorRuleConfigReq->translatorrulename().c_str(),pIwfVplmnIdConfigReq->allowedvplmnid().c_str());
    
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFTranslatorRuleVplmnIdTPBQuery::sql_IWFVplmnId_Payload_Validation(IwfTranslatorRuleConfig *IwfTranslatorRuleConfigReq,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    IwfVplmnIdConfig *pIwfVplmnIdConfigReq = NULL;
    if(IwfTranslatorRuleConfigReq -> vplmninfo_size() > iIndex && iIndex > -1)
    {
        pIwfVplmnIdConfigReq = IwfTranslatorRuleConfigReq -> mutable_vplmninfo(iIndex);
    }

    if(!IwfTranslatorRuleConfigReq->has_translatorrulename())
    {
        DLOG_ERROR("Primary Key translatorrulename is not set in the request");
        return IWF_DB_FAIL;
    }

    if(!pIwfVplmnIdConfigReq->has_allowedvplmnid())
    {
        DLOG_ERROR("Primary Key vplmnid is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFTranslatorRuleVplmnIdTPBQuery::sql_IWFVplmnId_Create_Select_Query(IwfVplmnIdConfig *pIwfVplmnIdConfig,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_TRANSLATOR_VPLMN_ID_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pIwfVplmnIdConfig->has_allowedvplmnid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"VPLMN_ID='%s' and ",pIwfVplmnIdConfig->allowedvplmnid().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


void IWFTranslatorRuleVplmnIdTPBQuery::sql_IWFVplmnId_Create_Select_Query(IwfTranslatorRuleConfig *IwfTranslatorRuleConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    IwfVplmnIdConfig *pIwfVplmnIdConfigReq = NULL;

    if(IwfTranslatorRuleConfigReq -> vplmninfo_size() > iIndex && iIndex > -1)
    {
        pIwfVplmnIdConfigReq = IwfTranslatorRuleConfigReq -> mutable_vplmninfo(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_TRANSLATOR_VPLMN_ID_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");


    if(pIwfVplmnIdConfigReq && pIwfVplmnIdConfigReq->has_allowedvplmnid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"VPLMN_ID='%s' and ",pIwfVplmnIdConfigReq->allowedvplmnid().c_str());
    }

    if(IwfTranslatorRuleConfigReq->has_translatorrulename())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_TRANSLATOR_RULE_ID=(select IWF_TRANSLATOR_RULE_ID from IWF_TRANSLATOR_RULE_TB where RULE_NAME ='%s') and ",IwfTranslatorRuleConfigReq->translatorrulename().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFTranslatorRuleVplmnIdTPBQuery::sql_IWFVplmnId_Check_All_Invalid(IwfTranslatorRuleConfig *IwfTranslatorRuleConfigReq,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    IwfVplmnIdConfig *pIwfVplmnIdConfigReq = NULL;

    if(IwfTranslatorRuleConfigReq -> vplmninfo_size() > iIndex && iIndex > -1)
    {
        pIwfVplmnIdConfigReq = IwfTranslatorRuleConfigReq -> mutable_vplmninfo(iIndex);
    }

    if(IwfTranslatorRuleConfigReq->has_translatorrulename())
    {
        return IWF_DB_FAIL;
    }   
    if(pIwfVplmnIdConfigReq && pIwfVplmnIdConfigReq->has_allowedvplmnid())
    {
        return IWF_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
