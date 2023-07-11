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

void IWFFeatureTPBQuery::sql_IWFFeature_Create_Check_Modifcation_Query(IwfFeatureConfig *IwfFeatureConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_FEATURE_ID from IWF_FEATURE_TB where IWF_FEATURE_NAME = '%s'",IwfFeatureConfigReq->featurename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFFeatureTPBQuery::sql_IWFFeature_Create_Add_Query(IwfFeatureConfig *IwfFeatureConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_FEATURE_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(IwfFeatureConfigReq->has_featurename())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_FEATURE_NAME,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",IwfFeatureConfigReq->featurename().c_str());
    }

    if(IwfFeatureConfigReq->has_statusvalue())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_FEATURE_STATUS,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%ld,",IwfFeatureConfigReq->statusvalue());
    }

    sFieldName[strlen(sFieldName) -1] = ' ';
    sFieldValue[strlen(sFieldValue) -1] = ' ';
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFFeatureTPBQuery::sql_IWFFeature_Create_Mod_Query(IwfFeatureConfig *IwfFeatureConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_FEATURE_TB set "); 

    if(IwfFeatureConfigReq->has_statusvalue())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_FEATURE_STATUS=%ld,",IwfFeatureConfigReq->statusvalue());
    }

    pStatement[strlen(pStatement) -1] = ' ';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where IWF_FEATURE_NAME = '%s'",IwfFeatureConfigReq->featurename().c_str());

    
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFFeatureTPBQuery::sql_IWFFeature_Create_Delete_Query(IwfFeatureConfig *IwfFeatureConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from  IWF_FEATURE_TB where IWF_FEATURE_NAME = '%s'",IwfFeatureConfigReq->featurename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFFeatureTPBQuery::sql_IWFFeature_Payload_Validation(IwfFeatureConfig *IwfFeatureConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(!IwfFeatureConfigReq->has_featurename())
    {
        DLOG_ERROR("Unique Key IWF_FEATURE_NAME is not set in the request");
        return IWF_DB_FAIL;
    }
    if(!IwfFeatureConfigReq->has_statusvalue())
    {
        DLOG_ERROR("Unique Key IWF_FEATURE_STATUS is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFFeatureTPBQuery::sql_IWFFeature_Create_Select_Query(IwfFeatureConfig *IwfFeatureConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_FEATURE_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfFeatureConfigReq->has_featurename())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_FEATURE_NAME='%s' and ",IwfFeatureConfigReq->featurename().c_str());
    }

    if(IwfFeatureConfigReq->has_statusvalue())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_FEATURE_STATUS=%ld and ",IwfFeatureConfigReq->statusvalue());
    }

    if(iFlag) 
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFFeatureTPBQuery::sql_IWFFeature_Check_All_Invalid(IwfFeatureConfig *IwfFeatureConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(IwfFeatureConfigReq->has_featurename())
    {
        return IWF_DB_FAIL;
    }   
    if(IwfFeatureConfigReq->has_statusvalue())
    {
        return IWF_DB_FAIL;
    }
    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
