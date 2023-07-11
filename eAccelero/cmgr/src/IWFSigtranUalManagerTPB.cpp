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

void IWFSigtranUalManagerTPBQuery::sql_IWFSigtranUalManager_Create_Check_Modifcation_Query(IwfSigtranUalManagerConfig *IwfSigtranUalManagerConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

//    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_SIGTRAN_UAL_MANAGER_ID from IWF_SIGTRAN_UAL_MANAGER_TB where ACK_TIMER = %d and SIGTRAN_MODE = '%s'",IwfSigtranUalManagerConfigReq->acktimer(),IwfSigtranUalManagerConfigReq->sigtranmode().c_str());
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SIGTRAN_UAL_MANAGER_TB");

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranUalManagerTPBQuery::sql_IWFSigtranUalManager_Create_Add_Query(IwfSigtranUalManagerConfig *IwfSigtranUalManagerConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_SIGTRAN_UAL_MANAGER_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(IwfSigtranUalManagerConfigReq->has_acktimer())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"ACK_TIMER,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",IwfSigtranUalManagerConfigReq->acktimer());
    }

    if(IwfSigtranUalManagerConfigReq->has_sigtranmode())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"SIGTRAN_MODE,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",IwfSigtranUalManagerConfigReq->sigtranmode().c_str());
    }

    sFieldName[strlen(sFieldName) -1] = ' ';
    sFieldValue[strlen(sFieldValue) -1] = ' ';
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranUalManagerTPBQuery::sql_IWFSigtranUalManager_Create_Mod_Query(IwfSigtranUalManagerConfig *IwfSigtranUalManagerConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_SIGTRAN_UAL_MANAGER_TB set "); 

    if(IwfSigtranUalManagerConfigReq->has_acktimer())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ACK_TIMER=%d,",IwfSigtranUalManagerConfigReq->acktimer());
    }

    if(IwfSigtranUalManagerConfigReq->has_sigtranmode())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SIGTRAN_MODE='%s',",IwfSigtranUalManagerConfigReq->sigtranmode().c_str());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranUalManagerTPBQuery::sql_IWFSigtranUalManager_Create_Delete_Query(IwfSigtranUalManagerConfig *IwfSigtranUalManagerConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

//    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from  IWF_SIGTRAN_UAL_MANAGER_TB where ACK_TIMER = %d and SIGTRAN_MODE = '%s'",IwfSigtranUalManagerConfigReq->acktimer(),IwfSigtranUalManagerConfigReq->sigtranmode().c_str());
    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from  IWF_SIGTRAN_UAL_MANAGER_TB");

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSigtranUalManagerTPBQuery::sql_IWFSigtranUalManager_Payload_Validation(IwfSigtranUalManagerConfig *IwfSigtranUalManagerConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(!IwfSigtranUalManagerConfigReq->has_acktimer())
    {
        DLOG_ERROR("Unique Key ACK_TIMER is not set in the request");
        return IWF_DB_FAIL;
    }
    if(!IwfSigtranUalManagerConfigReq->has_sigtranmode())
    {
        DLOG_ERROR("Unique Key SIGTRAN_MODE is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranUalManagerTPBQuery::sql_IWFSigtranUalManager_Create_Select_Query(IwfSigtranUalManagerConfig *IwfSigtranUalManagerConfigReq,char *pStatement)
{
//    int iFlag                   = 0;
//    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SIGTRAN_UAL_MANAGER_TB "); 
#if 0
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfSigtranUalManagerConfigReq->has_acktimer())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ACK_TIMER=%d and ",IwfSigtranUalManagerConfigReq->acktimer());
    }

    if(IwfSigtranUalManagerConfigReq->has_sigtranmode())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SIGTRAN_MODE='%s' and ",IwfSigtranUalManagerConfigReq->sigtranmode().c_str());
    }

    if(iFlag) 
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }
#endif
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSigtranUalManagerTPBQuery::sql_IWFSigtranUalManager_Check_All_Invalid(IwfSigtranUalManagerConfig *IwfSigtranUalManagerConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(IwfSigtranUalManagerConfigReq->has_acktimer())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranUalManagerConfigReq->has_sigtranmode())
    {
        return IWF_DB_FAIL;
    }   
    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
