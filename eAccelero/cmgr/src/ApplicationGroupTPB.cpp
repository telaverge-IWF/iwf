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

void ASFTPBQuery::sql_ASF_Create_Check_Modifcation_Query(ASGroupCfg *AsGroupReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    DLOG_NONE(" > %s ",__FUNCTION__);


    snprintf(pStatement,MAX_STATEMENT_SIZE,"select APP_GRP_ID from APPLICATION_GRP_TB ");
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(AsGroupReq->has_appgroup())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"APP_GRP_NAME='%s' and ",AsGroupReq->appgroup().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }


    DLOG_NONE(" < %s ",__FUNCTION__);
}

void ASFTPBQuery::sql_ASF_Create_Add_Query(ASGroupCfg *AsGroupReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into APPLICATION_GRP_TB "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(APP_GRP_NAME"); 
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",AsGroupReq->appgroup().c_str());


    if(AsGroupReq->has_priority())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PRIORITY");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",AsGroupReq->priority());
    }

    if(AsGroupReq->has_ishostedapp())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IS_HOSTED_APP_GRP");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",AsGroupReq->ishostedapp());
    }


    if(AsGroupReq->has_maxappinstances())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",MAX_APP_INSTANCES");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",AsGroupReq->maxappinstances());
    }

    if(AsGroupReq->has_lbalgo())
    {
        ::LBAlgorithm* localLBAlogrithm = AsGroupReq->mutable_lbalgo();
        if(localLBAlogrithm->has_lbmethod())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",LB_METHOD_ID");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select LB_METHOD_ID from LB_ALGORITHM_TB where LB_METHOD = '%s')",localLBAlogrithm->lbmethod().c_str());
        }
    }


    if(AsGroupReq->has_createdby())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",CREATED_BY");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select UserID from UserT where Username = '%s')",AsGroupReq->createdby().c_str());
    }

    if(AsGroupReq->has_creationdate())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",CREATION_TIME");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",AsGroupReq->creationdate().c_str());
    }

    if(AsGroupReq->has_modifiedby())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",MODIFIED_BY");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select UserID from UserT where Username = '%s')",AsGroupReq->modifiedby().c_str());
    }

    if(AsGroupReq->has_modifytime())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",MODIFICATION_TIME");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",AsGroupReq->modifytime().c_str());
    }

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" < %s ",__FUNCTION__);


}

void ASFTPBQuery::sql_ASF_Create_Delete_Query(ASGroupCfg *AsGroupReq,char *pStatement)
{

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    DLOG_NONE(" > %s ",__FUNCTION__);


    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from APPLICATION_GRP_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(AsGroupReq->has_appgroup())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"APP_GRP_NAME='%s' and ",AsGroupReq->appgroup().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void ASFTPBQuery::sql_ASF_Create_Mod_Query(ASGroupCfg *AsGroupReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update APPLICATION_GRP_TB set "); 

    if(AsGroupReq->has_priority())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PRIORITY=%d,",AsGroupReq->priority());
    }

    if(AsGroupReq->has_ishostedapp())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IS_HOSTED_APP_GRP=%d,",AsGroupReq->ishostedapp());
    }

    if(AsGroupReq->has_maxappinstances())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MAX_APP_INSTANCES=%d,",AsGroupReq->maxappinstances());
    }

    if(AsGroupReq->has_lbalgo())
    {
        ::LBAlgorithm* localLBAlogrithm = AsGroupReq->mutable_lbalgo();
        if(localLBAlogrithm->has_lbmethod())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LB_METHOD_ID = (select LB_METHOD_ID from LB_ALGORITHM_TB where LB_METHOD = '%s'),",localLBAlogrithm->lbmethod().c_str());
        }
    }

    if(AsGroupReq->has_createdby())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"CREATED_BY = (select UserID from UserT where Username = '%s'),",AsGroupReq->createdby().c_str());
    }

    if(AsGroupReq->has_creationdate())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"CREATION_TIME = '%s',",AsGroupReq->creationdate().c_str());
    }

    if(AsGroupReq->has_modifiedby())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MODIFIED_BY = (select UserID from UserT where Username = '%s'),",AsGroupReq->modifiedby().c_str());
    }

    if(AsGroupReq->has_modifytime())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MODIFICATION_TIME = '%s',",AsGroupReq->modifytime().c_str());
    }
    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where APP_GRP_NAME='%s'",AsGroupReq->appgroup().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e ASFTPBQuery::sql_ASF_Payload_Validation(ASGroupCfg *AsGroupReq)
{
    if (!AsGroupReq->has_appgroup())
    {
        DLOG_ERROR("Primary Key GroupName is not set in the request");
        return ERR_ASFGROUP_MANDATORY_PARAM_GROUPNAME_MISSING;  
    }

    return DRE_DB_SUCCESS;
}


void ASFTPBQuery::sql_ASF_Create_Select_Query(ASGroupCfg *AsGroupReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * FROM APPLICATION_GRP_TB"); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(AsGroupReq->has_appgroup())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"APP_GRP_NAME='%s' and ",AsGroupReq->appgroup().c_str());
    }

    if(AsGroupReq->has_priority())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PRIORITY=%d and ",AsGroupReq->priority());
    }

    if(AsGroupReq->has_ishostedapp())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IS_HOSTED_APP_GRP=%d and ",AsGroupReq->ishostedapp());
    }

    if(AsGroupReq->has_maxappinstances())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"MAX_APP_INSTANCES=%d and ",AsGroupReq->maxappinstances());
    }

    if(AsGroupReq->has_createdby())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"CREATED_BY = (select UserID from UserT where Username = '%s') and",AsGroupReq->createdby().c_str());
    }

    if(AsGroupReq->has_creationdate())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"CREATION_TIME='%s' and",AsGroupReq->creationdate().c_str());
    }

    if(AsGroupReq->has_modifiedby())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"MODIFIED_BY = (select UserID from UserT where Username = '%s') and",AsGroupReq->modifiedby().c_str());
    }

    if(AsGroupReq->has_modifytime())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"MODIFICATION_TIME='%s' and",AsGroupReq->modifytime().c_str());
    }


    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }


    DLOG_NONE(" < %s ",__FUNCTION__);

}

DbStatus_e ASFTPBQuery::sql_ASF_Check_All_Invalid(ASGroupCfg *AsGroupReq)
{


    if(AsGroupReq->has_priority())
    {
        return DRE_DB_FAIL;
    }

    if(AsGroupReq->has_ishostedapp())
    {
        return DRE_DB_FAIL;
    }

    if(AsGroupReq->has_maxappinstances())
    {
        return DRE_DB_FAIL;
    }

    if(AsGroupReq->has_lbalgo())
    {
        return DRE_DB_FAIL;
    }

    if(AsGroupReq->has_createdby())
    {
        return DRE_DB_FAIL;
    }

    if(AsGroupReq->has_creationdate())
    {
        return DRE_DB_FAIL;
    }

    if(AsGroupReq->has_modifiedby())
    {
        return DRE_DB_FAIL;
    }

    if(AsGroupReq->has_modifytime())
    {
        return DRE_DB_FAIL;
    }


    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
