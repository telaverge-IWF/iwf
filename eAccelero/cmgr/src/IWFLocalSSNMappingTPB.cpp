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

void IWFLocalSSNMappingTPBQuery::sql_IWFLocalSSNMapping_CreateCount_Check_Modifcation_Query(char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_LOCAL_SSN_MAPPING_TB" ); 

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFLocalSSNMappingTPBQuery::sql_IWFLocalSSNMapping_Create_Check_Modifcation_Query(IwfLocalHostConfig *IwfLocalHostConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    DLOG_DEBUG("IwfLocalHostConfigReq->ssn_config_size() = %d, iIndex= %d",IwfLocalHostConfigReq->ssn_config_size(),iIndex);    
    IwfLocalSSNConfig* pIwfLocalSSNConfig = NULL;
  
    if(IwfLocalHostConfigReq->ssn_config_size() > iIndex && iIndex > -1)
    {
        pIwfLocalSSNConfig = IwfLocalHostConfigReq->mutable_ssn_config(iIndex);
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_LOCAL_SSN_MAPPING_ID from IWF_LOCAL_SSN_MAPPING_TB where IWF_LOCAL_SSN_ID=(select IWF_LOCAL_SSN_ID from IWF_LOCAL_SSN_TABLE where SSN=%d)",pIwfLocalSSNConfig->ssn());
    }
    else
    {
        DLOG_WARNING("SSN is not configured, wrong iIndex = %d , ssn_config_size() = %d",iIndex,IwfLocalHostConfigReq->ssn_config_size());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFLocalSSNMappingTPBQuery::sql_IWFLocalSSNMapping_Create_Add_Query(IwfLocalHostConfig *IwfLocalHostConfigReq,char *pStatement,int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  
    int iFlag = 0;
    DLOG_DEBUG("IwfLocalHostConfigReq->ssn_config_size() = %d, iIndex= %d",IwfLocalHostConfigReq->ssn_config_size(),iIndex);    
    IwfLocalSSNConfig* pIwfLocalSSNConfig = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    if(IwfLocalHostConfigReq->ssn_config_size() > iIndex && iIndex > -1)
    {
	    pIwfLocalSSNConfig = IwfLocalHostConfigReq->mutable_ssn_config(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_LOCAL_SSN_MAPPING_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");
    //snprintf(sFieldName,MAX_STATEMENT_SIZE,"(SSN)");
    //snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(%d)",IwfLocalHostConfigReq->ssn());

    if(pIwfLocalSSNConfig && pIwfLocalSSNConfig->has_ssn())
    {
        iFlag = 1;
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_LOCAL_SSN_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_LOCAL_SSN_ID from IWF_LOCAL_SSN_TABLE where SSN=%d),",pIwfLocalSSNConfig->ssn());
    }
#if 0
    if(IwfLocalHostConfigReq->has_pointcode())
    {
        iFlag = 1;
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_LOCAL_CONFIG_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_LOCAL_CONFIG_ID from IWF_LOCAL_CONFIG_TB where POINTCODE=%d),",IwfLocalHostConfigReq->pointcode());
    }
#endif
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_LOCAL_CONFIG_ID,");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_LOCAL_CONFIG_ID from IWF_LOCAL_CONFIG_TB),");

    if(iFlag)
    {
        sFieldName[strlen(sFieldName) - 1] = ' ';
        sFieldValue[strlen(sFieldValue) - 1] = ' ';
    }

    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFLocalSSNMappingTPBQuery::sql_IWFLocalSSNMapping_Create_Mod_Query(IwfLocalHostConfig *IwfLocalHostConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    //IwfLocalSSNConfig* pIwfLocalSSNConfig = NULL;

    DLOG_DEBUG("IwfLocalHostConfigReq->ssn_config_size() = %d, iIndex= %d",IwfLocalHostConfigReq->ssn_config_size(),iIndex);    
    DLOG_DEBUG("All the fields are primary key, so update is not possible");
#if 0    
    if(IwfLocalHostConfigReq->ssn_config_size() > iIndex && iIndex > -1)
    {
	    pIwfLocalSSNConfig = IwfLocalHostConfigReq->mutable_ssn_config(iIndex);
    }


    snprintf(pStatement,MAX_STATEMENT_SIZE,"update LOCAL_SSN_TABLE set "); 

    if(IwfLocalHostConfigReq->has_pointcode())
    {
	    IwfLocalSSNConfig* pIwfLocalSSNConfig = IwfLocalHostConfigReq->mutable_ssn_config(iIndex);
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LOCAL_CONFIG_ID=(select LOCAL_CONFIG_ID from LOCAL_CONFIG_TB when POINTCODE = %d),",IwfLocalHostConfigReq->pointcode());

    }

    if(IwfLocalHostConfigReq->has_ssn())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SSN = '%d',",IwfLocalHostConfigReq->ssn());

    }

    pStatement[strlen(pStatement) -1] = ' ';
#endif

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFLocalSSNMappingTPBQuery::sql_IWFLocalSSNMapping_Create_Delete_Query(IwfLocalHostConfig *IwfLocalHostConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    DLOG_DEBUG("IwfLocalHostConfigReq->ssn_config_size() = %d, iIndex= %d",IwfLocalHostConfigReq->ssn_config_size(),iIndex);    
    IwfLocalSSNConfig* pIwfLocalSSNConfig = NULL;

    if(IwfLocalHostConfigReq->ssn_config_size() > iIndex && iIndex > -1)
    {
	    pIwfLocalSSNConfig = IwfLocalHostConfigReq->mutable_ssn_config(iIndex);
    }

    if(IwfLocalHostConfigReq->ssn_config_size() > iIndex && iIndex > -1)
    {
	    IwfLocalSSNConfig* pIwfLocalSSNConfig = IwfLocalHostConfigReq->mutable_ssn_config(iIndex);
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_LOCAL_SSN_MAPPING_TB where IWF_LOCAL_SSN_ID=(select IWF_LOCAL_SSN_ID from IWF_LOCAL_SSN_TABLE where SSN=%d)",pIwfLocalSSNConfig->ssn());
    }
    else
    {
        DLOG_WARNING("SSN is not configured, wrong iIndex = %d , ssn_config_size() = %d",iIndex,IwfLocalHostConfigReq->ssn_config_size());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFLocalSSNMappingTPBQuery::sql_IWFLocalSSNMapping_Payload_Validation(IwfLocalHostConfig *IwfLocalHostConfigReq, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    IwfLocalSSNConfig* pIwfLocalSSNConfig = NULL;

    DLOG_DEBUG("IwfLocalHostConfigReq->ssn_config_size() = %d, iIndex= %d",IwfLocalHostConfigReq->ssn_config_size(),iIndex);    

    if(IwfLocalHostConfigReq->ssn_config_size() > iIndex && iIndex > -1)
    {
	    pIwfLocalSSNConfig = IwfLocalHostConfigReq->mutable_ssn_config(iIndex);
    }

    if(!pIwfLocalSSNConfig && pIwfLocalSSNConfig->has_ssn())
    {
        DLOG_ERROR("Primary Key ssn is not set in the request");
        return IWF_DB_FAIL;
    }

    if(!IwfLocalHostConfigReq->has_pointcode())
    {
        DLOG_ERROR("Primary Key pointcode is not set in the request");
        return IWF_DB_FAIL;
    }

    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


void IWFLocalSSNMappingTPBQuery::sql_IWFLocalSSNMapping_Create_Select_Query(IwfLocalHostConfig *IwfLocalHostConfigReq,char *pStatement,int iIndex)
{
    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    IwfLocalSSNConfig* pIwfLocalSSNConfig = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfLocalHostConfigReq->ssn_config_size() = %d, iIndex= %d",IwfLocalHostConfigReq->ssn_config_size(),iIndex);

    if(IwfLocalHostConfigReq->ssn_config_size() > iIndex && iIndex > -1)
    {
	    pIwfLocalSSNConfig = IwfLocalHostConfigReq->mutable_ssn_config(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_LOCAL_SSN_MAPPING_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfLocalHostConfigReq->has_pointcode())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_LOCAL_CONFIG_ID=(select IWF_LOCAL_CONFIG_ID from IWF_LOCAL_CONFIG_TB) and ");
    }

    if(pIwfLocalSSNConfig && pIwfLocalSSNConfig->has_ssn())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_LOCAL_SSN_ID=(select IWF_LOCAL_SSN_ID from IWF_LOCAL_SSN_TABLE where SSN=%d) and ",pIwfLocalSSNConfig->ssn());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFLocalSSNMappingTPBQuery::sql_IWFLocalSSNMapping_Check_All_Invalid(IwfLocalHostConfig *IwfLocalHostConfigReq, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfLocalHostConfigReq->ssn_config_size() = %d, iIndex= %d",IwfLocalHostConfigReq->ssn_config_size(),iIndex);

    IwfLocalSSNConfig* pIwfLocalSSNConfig = NULL;
    if(IwfLocalHostConfigReq->ssn_config_size() > iIndex && iIndex > -1)
    {
	    pIwfLocalSSNConfig = IwfLocalHostConfigReq->mutable_ssn_config(iIndex);
    }
    if(pIwfLocalSSNConfig && pIwfLocalSSNConfig->has_ssn())
    {
        return IWF_DB_FAIL;
    }   
    if(IwfLocalHostConfigReq->has_pointcode())
    {
        return IWF_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
