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
void CmfDiaRealmTemplateTPBQuery::sql_CmfDiaRealmTemplate_Create_Validation_Query_for_Realm(CMFRealmTemplate *CmfRealmTemplateConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select REALM_ID from REALM_TB where REALM_CMF_CONFIG_ID=(select CMF_REALM_TEMPLATE_ID from CMF_DIA_REALM_TEMPLATE_TB where REALM_TEMPLATE_NAME='%s')",CmfRealmTemplateConfigReq->realmtemplatename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfDiaRealmTemplateTPBQuery::sql_CmfDiaRealmTemplate_Create_Check_Modifcation_Query(CMFRealmTemplate *CmfRealmTemplateConfigReq,char *pStatement)
{
    int iFlag 					= 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
    DLOG_NONE(" > %s ",__FUNCTION__);


    snprintf(pStatement,MAX_STATEMENT_SIZE,"select CMF_REALM_TEMPLATE_ID from CMF_DIA_REALM_TEMPLATE_TB ");
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(CmfRealmTemplateConfigReq->has_realmtemplatename())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"REALM_TEMPLATE_NAME='%s' and ",CmfRealmTemplateConfigReq->realmtemplatename().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfDiaRealmTemplateTPBQuery::sql_CmfDiaRealmTemplate_Create_Add_Query(CMFRealmTemplate *CmfRealmTemplateConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]	= {0};
    char sFieldValue[MAX_STATEMENT_SIZE]	= {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into CMF_DIA_REALM_TEMPLATE_TB ");
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(REALM_TEMPLATE_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",CmfRealmTemplateConfigReq->realmtemplatename().c_str());


    if(CmfRealmTemplateConfigReq->has_priority())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",PRIORITY");
        if(CmfRealmTemplateConfigReq->priority() == 1)
        {
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'normal'");
        }
        if(CmfRealmTemplateConfigReq->priority() == 2)
        {
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'high'");
        }
    }

    if(CmfRealmTemplateConfigReq->has_maxintps())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",MAX_IN_TPS");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",CmfRealmTemplateConfigReq->maxintps());
    }
    if(CmfRealmTemplateConfigReq->has_maxouttps())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",MAX_OUT_TPS");
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",CmfRealmTemplateConfigReq->maxouttps());
    }

    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" < %s ",__FUNCTION__);


}

void CmfDiaRealmTemplateTPBQuery::sql_CmfDiaRealmTemplate_Create_Delete_Query(CMFRealmTemplate *CmfRealmTemplateConfigReq,char *pStatement)
{

    int iFlag 					= 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
    DLOG_NONE(" > %s ",__FUNCTION__);


    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from CMF_DIA_REALM_TEMPLATE_TB ");
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(CmfRealmTemplateConfigReq->has_realmtemplatename())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"REALM_TEMPLATE_NAME='%s' and ",CmfRealmTemplateConfigReq->realmtemplatename().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CmfDiaRealmTemplateTPBQuery::sql_CmfDiaRealmTemplate_Create_Mod_Query(CMFRealmTemplate *CmfRealmTemplateConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update CMF_DIA_REALM_TEMPLATE_TB set ");


    if(CmfRealmTemplateConfigReq->has_priority())
    {
        if(CmfRealmTemplateConfigReq->priority() == 1)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"PRIORITY='normal',");
        }
        else if(CmfRealmTemplateConfigReq->priority() == 2)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"PRIORITY='high',");
        }
    }

    if(CmfRealmTemplateConfigReq->has_maxintps())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"MAX_IN_TPS=%d,",CmfRealmTemplateConfigReq->maxintps());
    }
    if(CmfRealmTemplateConfigReq->has_maxouttps())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"MAX_OUT_TPS=%d,",CmfRealmTemplateConfigReq->maxouttps());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where REALM_TEMPLATE_NAME='%s'",CmfRealmTemplateConfigReq->realmtemplatename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CmfDiaRealmTemplateTPBQuery::sql_CmfDiaRealmTemplate_Payload_Validation(CMFRealmTemplate *CmfRealmTemplateConfigReq)
{

    return DRE_DB_SUCCESS;
}


void CmfDiaRealmTemplateTPBQuery::sql_CmfDiaRealmTemplate_Create_Select_Query(CMFRealmTemplate *CmfRealmTemplateConfigReq,char *pStatement)
{
    int iFlag 					= 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from CMF_DIA_REALM_TEMPLATE_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(CmfRealmTemplateConfigReq->has_realmtemplatename())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"REALM_TEMPLATE_NAME='%s' and ",CmfRealmTemplateConfigReq->realmtemplatename().c_str());
    }

    if(CmfRealmTemplateConfigReq->has_priority())
    {
        iFlag = 1;
        if(CmfRealmTemplateConfigReq->priority() == 1)
        {
            if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
                snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"LOCAL_ACTION='normal' and ");
        }
        else if(CmfRealmTemplateConfigReq->priority() == 2)
        {
            if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
                snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"LOCAL_ACTION='high' and ");
        }
    }

    if(CmfRealmTemplateConfigReq->has_maxintps())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"MAX_IN_TPS=%d and ",CmfRealmTemplateConfigReq->maxintps());
    }
    if(CmfRealmTemplateConfigReq->has_maxouttps())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"MAX_OUT_TPS=%d and ",CmfRealmTemplateConfigReq->maxouttps());
    }


    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }


    DLOG_NONE(" < %s ",__FUNCTION__);

}

DbStatus_e CmfDiaRealmTemplateTPBQuery::sql_CmfDiaRealmTemplate_Check_All_Invalid(CMFRealmTemplate *CmfRealmTemplateConfigReq)
{
    if(CmfRealmTemplateConfigReq->has_priority())
    {
        return DRE_DB_FAIL;
    }

    if(CmfRealmTemplateConfigReq->has_maxintps())
    {
        return DRE_DB_FAIL;
    }
    if(CmfRealmTemplateConfigReq->has_maxouttps())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
