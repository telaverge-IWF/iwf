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
#if 1
void IWFSigtranAssocSetMappingTPBQuery::sql_IWFSigtranAssocSetMapping_Create_Check_Modifcation_Query(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_SIGTRAN_ASSOC_SET_MAPPING_ID from IWF_SIGTRAN_ASSOC_SET_MAPPING_TB where IWF_SIGTRAN_ASSOC_ID=(select IWF_SIGTRAN_ASSOC_ID from IWF_SIGTRAN_ASSOCIATION_TB where IWF_SIGTRAN_ASSOC_NAME='%s')",IwfSigtranAssociationConfigReq->associationname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
#endif

void IWFSigtranAssocSetMappingTPBQuery::sql_IWFSigtranAssocSetMapping_Create_Check_Modifcation_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfSigtranAssociationSetConfigReq->associationinfo_size() = %d, iIndex= %d",IwfSigtranAssociationSetConfigReq->associationinfo_size(),iIndex);   

    IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = NULL;
  
    if(IwfSigtranAssociationSetConfigReq->associationinfo_size() > iIndex && iIndex > -1)
    {
	    pIwfSigtranAssociationConfig = IwfSigtranAssociationSetConfigReq->mutable_associationinfo(iIndex);
    	snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_SIGTRAN_ASSOC_SET_MAPPING_ID from IWF_SIGTRAN_ASSOC_SET_MAPPING_TB where IWF_SIGTRAN_ASSOC_ID=(select IWF_SIGTRAN_ASSOC_ID from IWF_SIGTRAN_ASSOCIATION_TB where IWF_SIGTRAN_ASSOC_NAME='%s') and IWF_SIGTRAN_ASSOC_SET_ID = (select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME='%s'))",pIwfSigtranAssociationConfig->associationname().c_str(),IwfSigtranAssociationSetConfigReq->associationsetname().c_str());
    }
    else
    {
        DLOG_WARNING("SSN is not configured, wrong iIndex = %d , associationinfo_size() = %d",iIndex,IwfSigtranAssociationSetConfigReq->associationinfo_size());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


void IWFSigtranAssocSetMappingTPBQuery::sql_IWFSigtranAssocSetMapping_Create_Add_Query(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  
    int iFlag = 0;

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_SIGTRAN_ASSOC_SET_MAPPING_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(pIwfSigtranAssociationConfig->has_associationname())
    {
        iFlag = 1;
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_SIGTRAN_ASSOC_ID from IWF_SIGTRAN_ASSOCIATION_TB where IWF_SIGTRAN_ASSOC_NAME='%s'),",pIwfSigtranAssociationConfig->associationname().c_str());
    }

    if(pIwfSigtranAssociationConfig->has_associationsetname())
    {
        iFlag = 1;
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME='%s'),",pIwfSigtranAssociationConfig->associationsetname().c_str());
    }

    if(pIwfSigtranAssociationConfig->has_associationmappingid())
    {
        iFlag = 1;
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_MAPPING_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pIwfSigtranAssociationConfig->associationmappingid());
    }

    if(iFlag)
    {
        sFieldName[strlen(sFieldName) - 1]   = ' ';
        sFieldValue[strlen(sFieldValue) - 1] = ' ';
    }

    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


void IWFSigtranAssocSetMappingTPBQuery::sql_IWFSigtranAssocSetMapping_Create_Add_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfSigtranAssociationSetConfigReq->associationinfo_size() = %d, iIndex= %d",IwfSigtranAssociationSetConfigReq->associationinfo_size(),iIndex);   

    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  
    int iFlag = 0;
    IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = NULL;

    if(IwfSigtranAssociationSetConfigReq->associationinfo_size() > iIndex && iIndex > -1)
    {
	    pIwfSigtranAssociationConfig = IwfSigtranAssociationSetConfigReq->mutable_associationinfo(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_SIGTRAN_ASSOC_SET_MAPPING_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(pIwfSigtranAssociationConfig && pIwfSigtranAssociationConfig->has_associationname())
    {
        iFlag = 1;
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_SIGTRAN_ASSOC_ID from IWF_SIGTRAN_ASSOCIATION_TB where IWF_SIGTRAN_ASSOC_NAME='%s'),",pIwfSigtranAssociationConfig->associationname().c_str());
    }

    if(IwfSigtranAssociationSetConfigReq->has_associationsetname())
    {
        iFlag = 1;
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME='%s'),",IwfSigtranAssociationSetConfigReq->associationsetname().c_str());
    }

    if(pIwfSigtranAssociationConfig->has_associationmappingid())
    {
        iFlag = 1;
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_MAPPING_ID,");
        snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(%d,",pIwfSigtranAssociationConfig->associationmappingid());
    }


    if(iFlag)
    {
        sFieldName[strlen(sFieldName) - 1]   = ' ';
        sFieldValue[strlen(sFieldValue) - 1] = ' ';
    }

    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranAssocSetMappingTPBQuery::sql_IWFSigtranAssocSetMapping_Create_Mod_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfSigtranAssociationSetConfigReq->associationinfo_size() = %d, iIndex= %d",IwfSigtranAssociationSetConfigReq->associationinfo_size(),iIndex);    
    //IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = NULL;

    DLOG_DEBUG("All the fields are primary key, so update is not possible");
#if 0    
    if(IwfSigtranAssociationSetConfigReq->associationinfo_size() > iIndex && iIndex > -1)
    {
	    pIwfSigtranAssociationConfig = IwfSigtranAssociationSetConfigReq->mutable_associationinfo(iIndex);
    }


    snprintf(pStatement,MAX_STATEMENT_SIZE,"update LOCAL_SSN_TABLE set "); 

    if(IwfSigtranAssociationSetConfigReq->has_associationsetname())
    {
	    IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = IwfSigtranAssociationSetConfigReq->mutable_associationinfo(iIndex);
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LOCAL_CONFIG_ID=(select LOCAL_CONFIG_ID from LOCAL_CONFIG_TB when associationsetname = %d),",IwfSigtranAssociationSetConfigReq->associationsetname().c_str());

    }

    if(IwfSigtranAssociationSetConfigReq->has_associationname())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SSN = '%d',",IwfSigtranAssociationSetConfigReq->associationname().c_str());

    }

    pStatement[strlen(pStatement) -1] = ' ';
#endif

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranAssocSetMappingTPBQuery::sql_IWFSigtranAssocSetMapping_Create_Delete_Query(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_SIGTRAN_ASSOC_SET_MAPPING_TB where IWF_SIGTRAN_ASSOC_ID=(select IWF_SIGTRAN_ASSOC_ID from IWF_SIGTRAN_ASSOCIATION_TB where IWF_SIGTRAN_ASSOC_NAME='%s')",IwfSigtranAssociationConfigReq->associationname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


void IWFSigtranAssocSetMappingTPBQuery::sql_IWFSigtranAssocSetMapping_Create_Delete_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfSigtranAssociationSetConfigReq->associationinfo_size() = %d, iIndex= %d",IwfSigtranAssociationSetConfigReq->associationinfo_size(),iIndex);   

    IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = NULL;
    if(IwfSigtranAssociationSetConfigReq->associationinfo_size() > iIndex && iIndex > -1)
    {
	    pIwfSigtranAssociationConfig = IwfSigtranAssociationSetConfigReq->mutable_associationinfo(iIndex);
    }

    if(IwfSigtranAssociationSetConfigReq->associationinfo_size() > iIndex && iIndex > -1)
    {
	    IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = IwfSigtranAssociationSetConfigReq->mutable_associationinfo(iIndex);
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_SIGTRAN_ASSOC_SET_MAPPING_TB where IWF_SIGTRAN_ASSOC_ID=(select IWF_SIGTRAN_ASSOC_ID from IWF_SIGTRAN_ASSOCIATION_TB where IWF_SIGTRAN_ASSOC_NAME='%s') and IWF_SIGTRAN_ASSOC_SET_ID=(select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME='%s')",pIwfSigtranAssociationConfig->associationname().c_str(),IwfSigtranAssociationSetConfigReq->associationsetname().c_str());
    }
    else
    {
        DLOG_WARNING("SSN is not configured, wrong iIndex = %d , associationinfo_size() = %d",iIndex,IwfSigtranAssociationSetConfigReq->associationinfo_size());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSigtranAssocSetMappingTPBQuery::sql_IWFSigtranAssocSetMapping_Payload_Validation(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfSigtranAssociationSetConfigReq->associationinfo_size() = %d, iIndex= %d",IwfSigtranAssociationSetConfigReq->associationinfo_size(),iIndex);    

    IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = NULL;

    if(IwfSigtranAssociationSetConfigReq->associationinfo_size() > iIndex && iIndex > -1)
    {
	    pIwfSigtranAssociationConfig = IwfSigtranAssociationSetConfigReq->mutable_associationinfo(iIndex);
    }

    if(!pIwfSigtranAssociationConfig && pIwfSigtranAssociationConfig->has_associationname())
    {
        DLOG_ERROR("Primary Key ssn is not set in the request");
        return IWF_DB_FAIL;
    }
    if(!IwfSigtranAssociationSetConfigReq->has_associationsetname())
    {
        DLOG_ERROR("Primary Key associationsetname is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranAssocSetMappingTPBQuery::sql_IWFSigtranAssocSetMapping_Create_OrderBy_Select_Query(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]  = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SIGTRAN_ASSOC_SET_MAPPING_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfSigtranAssociationConfigReq->has_associationsetname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_ID=(select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME='%s') order by IWF_SIGTRAN_ASSOC_MAPPING_ID and ",IwfSigtranAssociationConfigReq->associationsetname().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
 
}

void IWFSigtranAssocSetMappingTPBQuery::sql_IWFSigtranAssocSetMapping_Create_Select_Query_For_Delete_Association_Validation(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq, char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    char sWhereStatement[MAX_STATEMENT_SIZE]  = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SIGTRAN_ASSOC_SET_MAPPING_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfSigtranAssociationConfigReq->has_associationname())
    {
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_ID=(select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_MAPPING_TB where IWF_SIGTRAN_ASSOC_ID=(select IWF_SIGTRAN_ASSOC_ID from IWF_SIGTRAN_ASSOCIATION_TB where IWF_SIGTRAN_ASSOC_NAME= '%s'))",IwfSigtranAssociationConfigReq->associationname().c_str());
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranAssocSetMappingTPBQuery::sql_IWFSigtranAssocSetMapping_Create_Select_Query(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]  = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SIGTRAN_ASSOC_SET_MAPPING_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfSigtranAssociationConfigReq->has_associationsetname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_ID=(select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME='%s') and ",IwfSigtranAssociationConfigReq->associationsetname().c_str());
    }

    if(IwfSigtranAssociationConfigReq->has_associationname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_ID=(select IWF_SIGTRAN_ASSOC_ID from IWF_SIGTRAN_ASSOCIATION_TB where IWF_SIGTRAN_ASSOC_NAME='%s') and ",IwfSigtranAssociationConfigReq->associationname().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


void IWFSigtranAssocSetMappingTPBQuery::sql_IWFSigtranAssocSetMapping_Create_Select_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    int iFlag = 0;
    DLOG_DEBUG("IwfSigtranAssociationSetConfigReq->associationinfo_size() = %d, iIndex= %d",IwfSigtranAssociationSetConfigReq->associationinfo_size(),iIndex);
    char sWhereStatement[MAX_STATEMENT_SIZE]  = {0};
    IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = NULL;

    if(IwfSigtranAssociationSetConfigReq->associationinfo_size() > iIndex && iIndex > -1)
    {
	    pIwfSigtranAssociationConfig = IwfSigtranAssociationSetConfigReq->mutable_associationinfo(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SIGTRAN_ASSOC_SET_MAPPING_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfSigtranAssociationSetConfigReq->has_associationsetname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_ID=(select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME='%s') and ",IwfSigtranAssociationSetConfigReq->associationsetname().c_str());
    }

    if(pIwfSigtranAssociationConfig && pIwfSigtranAssociationConfig->has_associationname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_ID=(select IWF_SIGTRAN_ASSOC_ID from IWF_SIGTRAN_ASSOCIATION_TB where IWF_SIGTRAN_ASSOC_NAME='%s') and ",pIwfSigtranAssociationConfig->associationname().c_str());
    }
    
    if(pIwfSigtranAssociationConfig && pIwfSigtranAssociationConfig->has_associationid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_ID=%d and ",pIwfSigtranAssociationConfig->associationid());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSigtranAssocSetMappingTPBQuery::sql_IWFSigtranAssocSetMapping_Check_All_Invalid(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfSigtranAssociationSetConfigReq->associationinfo_size() = %d, iIndex= %d",IwfSigtranAssociationSetConfigReq->associationinfo_size(),iIndex);

    IwfSigtranAssociationConfig* pIwfSigtranAssociationConfig = NULL;
    if(IwfSigtranAssociationSetConfigReq->associationinfo_size() > iIndex && iIndex > -1)
    {
	    pIwfSigtranAssociationConfig = IwfSigtranAssociationSetConfigReq->mutable_associationinfo(iIndex);
    }
    if(pIwfSigtranAssociationConfig && pIwfSigtranAssociationConfig->has_associationname())
    {
        return IWF_DB_FAIL;
    }   
    if(IwfSigtranAssociationSetConfigReq->has_associationsetname())
    {
        return IWF_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
