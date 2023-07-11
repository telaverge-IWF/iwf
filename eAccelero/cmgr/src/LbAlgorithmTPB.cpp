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

void LbAlgorithmTPBQuery::sql_LbAlgorithm_Create_Check_Modifcation_Query(LBAlgorithm *dreLbAlgorithmReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select LB_METHOD_ID from  LB_ALGORITHM_TB where LB_METHOD='%s'",dreLbAlgorithmReq->lbmethod().c_str()); 
}

void LbAlgorithmTPBQuery::sql_LbAlgorithm_Create_Add_Query(LBAlgorithm *dreLbAlgorithmReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE("> %s",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into LB_ALGORITHM_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(LB_METHOD");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",dreLbAlgorithmReq->lbmethod().c_str());

    if(dreLbAlgorithmReq->has_lbmethoddesc())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",DESCRIPTION");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",dreLbAlgorithmReq->lbmethoddesc().c_str());
    }
    if(dreLbAlgorithmReq->has_suppcomponent())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SUPPORTED_MODULES");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreLbAlgorithmReq->suppcomponent());
    }

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE("< %s",__FUNCTION__);

}

void LbAlgorithmTPBQuery::sql_LbAlgorithm_Create_Mod_Query(LBAlgorithm *dreLbAlgorithmReq,char *pStatement)
{
    DLOG_NONE("> %s",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update LB_ALGORITHM_TB set "); 

    if(dreLbAlgorithmReq->has_lbmethoddesc())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"DESCRIPTION='%s',",dreLbAlgorithmReq->lbmethoddesc().c_str());

    }
    if(dreLbAlgorithmReq->has_suppcomponent())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SUPPORTED_MODULES=%d,",dreLbAlgorithmReq->suppcomponent());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where LB_METHOD='%s'",dreLbAlgorithmReq->lbmethod().c_str());

    DLOG_NONE("< %s",__FUNCTION__);

}

void LbAlgorithmTPBQuery::sql_LbAlgorithm_Create_Delete_Query(LBAlgorithm *dreLbAlgorithmReq,char *pStatement)
{
    DLOG_NONE("> %s",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from LB_ALGORITHM_TB where LB_METHOD='%s'",dreLbAlgorithmReq->lbmethod().c_str()); 

    DLOG_NONE("< %s",__FUNCTION__);
}

DbStatus_e LbAlgorithmTPBQuery::sql_LbAlgorithm_Payload_Validation(LBAlgorithm *dreLbAlgorithmReq)
{
    if(!dreLbAlgorithmReq->has_lbmethod())
    {
        DLOG_ERROR("Primary Key LBMethod is not set in the request");
        return ERR_LBALGO_MANDATORY_LBMETHOD_MISSING;   
    }

    return DRE_DB_SUCCESS;
}


void LbAlgorithmTPBQuery::sql_LbAlgorithm_Create_Select_Query(LBAlgorithm *dreLbAlgorithmReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    DLOG_NONE("> %s",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from LB_ALGORITHM_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");


    if(dreLbAlgorithmReq->has_lbmethod())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LB_METHOD='%s' and ",dreLbAlgorithmReq->lbmethod().c_str());
    }

    if(dreLbAlgorithmReq->has_lbmethoddesc())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"DESCRIPTION='%s' and ",dreLbAlgorithmReq->lbmethoddesc().c_str());
    }

    if(dreLbAlgorithmReq->has_suppcomponent())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SUPPORTED_MODULES=%d and ",dreLbAlgorithmReq->suppcomponent());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE("< %s",__FUNCTION__);
}

DbStatus_e LbAlgorithmTPBQuery::sql_LbAlgorithm_Check_All_Invalid(LBAlgorithm *dreLbAlgorithmReq)
{

    if(dreLbAlgorithmReq->has_lbmethoddesc())
    {
        return DRE_DB_FAIL;
    }   
    if(dreLbAlgorithmReq->has_suppcomponent())
    {
        return DRE_DB_FAIL;
    }
    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}

