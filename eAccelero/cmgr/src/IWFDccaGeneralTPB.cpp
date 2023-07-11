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

void IWFDccaGeneralTPBQuery::sql_IWFDccaGeneral_Create_Check_Modifcation_Query(IwfDccaFeatureConfig *IwfDccaFeatureConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_DCCA_FEATURE_ID from IWF_DCCA_GENERAL_CONFIG_TB where IWF_DCCA_FEATURE_NAME = '%s'",IwfDccaFeatureConfigReq->dccafeaturename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFDccaGeneralTPBQuery::sql_IWFDccaGeneral_Create_Add_Query(IwfDccaFeatureConfig *IwfDccaFeatureConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_DCCA_GENERAL_CONFIG_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(IwfDccaFeatureConfigReq->has_dccafeaturename())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_DCCA_FEATURE_NAME,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",IwfDccaFeatureConfigReq->dccafeaturename().c_str());
    }

    if(IwfDccaFeatureConfigReq->has_dccavalue())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_DCCA_FEATURE_VALUE,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",IwfDccaFeatureConfigReq->dccavalue());
    }

    sFieldName[strlen(sFieldName) -1] = ' ';
    sFieldValue[strlen(sFieldValue) -1] = ' ';
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFDccaGeneralTPBQuery::sql_IWFDccaGeneral_Create_Mod_Query(IwfDccaFeatureConfig *IwfDccaFeatureConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_DCCA_GENERAL_CONFIG_TB set "); 

    if(IwfDccaFeatureConfigReq->has_dccavalue())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_DCCA_FEATURE_VALUE=%d,",IwfDccaFeatureConfigReq->dccavalue());
    }

    pStatement[strlen(pStatement) -1] = ' ';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where IWF_DCCA_FEATURE_NAME = '%s'",IwfDccaFeatureConfigReq->dccafeaturename().c_str());

    
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFDccaGeneralTPBQuery::sql_IWFDccaGeneral_Create_Delete_Query(IwfDccaFeatureConfig *IwfDccaFeatureConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from  IWF_DCCA_GENERAL_CONFIG_TB where IWF_DCCA_FEATURE_NAME = '%s'",IwfDccaFeatureConfigReq->dccafeaturename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFDccaGeneralTPBQuery::sql_IWFDccaGeneral_Payload_Validation(IwfDccaFeatureConfig *IwfDccaFeatureConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(!IwfDccaFeatureConfigReq->has_dccafeaturename())
    {
        DLOG_ERROR("Unique Key IWF_DCCA_FEATURE_NAME is not set in the request");
        return IWF_DB_FAIL;
    }
    if(!IwfDccaFeatureConfigReq->has_dccavalue())
    {
        DLOG_ERROR("Unique Key IWF_DCCA_FEATURE_VALUE is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFDccaGeneralTPBQuery::sql_IWFDccaGeneral_Create_Select_Query(IwfDccaFeatureConfig *IwfDccaFeatureConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_DCCA_GENERAL_CONFIG_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfDccaFeatureConfigReq->has_dccafeaturename())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_DCCA_FEATURE_NAME='%s' and ",IwfDccaFeatureConfigReq->dccafeaturename().c_str());
    }

    if(IwfDccaFeatureConfigReq->has_dccavalue())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_DCCA_FEATURE_VALUE=%d and ",IwfDccaFeatureConfigReq->dccavalue());
    }

    if(iFlag) 
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFDccaGeneralTPBQuery::sql_IWFDccaGeneral_Check_All_Invalid(IwfDccaFeatureConfig *IwfDccaFeatureConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(IwfDccaFeatureConfigReq->has_dccafeaturename())
    {
        return IWF_DB_FAIL;
    }   
    if(IwfDccaFeatureConfigReq->has_dccavalue())
    {
        return IWF_DB_FAIL;
    }
    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
