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

void ExtTeleserviceToServiceIdMapTPBQuery::sql_ExtTeleserviceToServiceIdMap_Create_Check_Modifcation_Query(CapRoIdpConfig *CapRoIdpConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_DEBUG("CapRoIdpConfigReq->extteleinfo_size() = %d, iIndex= %d",CapRoIdpConfigReq->extteleinfo_size(),iIndex);    

    ExtTeleServiceConfig *pExtTeleServiceConfigReq = NULL;

    if(CapRoIdpConfigReq -> extteleinfo_size() > iIndex && iIndex > -1)
    {
        pExtTeleServiceConfigReq = CapRoIdpConfigReq -> mutable_extteleinfo(iIndex);
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select EXT_TELESERVICE_TO_SERVICE_ID_MAP_ID from EXT_TELESERVICE_TO_SERVICE_ID_MAP_TB where EXT_TELESERVICE = %d ",pExtTeleServiceConfigReq->extteleservicecode());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void ExtTeleserviceToServiceIdMapTPBQuery::sql_ExtTeleserviceToServiceIdMap_Create_Add_Query(CapRoIdpConfig *CapRoIdpConfigReq,char *pStatement,int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("CapRoIdpConfigReq->extteleinfo_size() = %d, iIndex= %d",CapRoIdpConfigReq->extteleinfo_size(),iIndex);    
    ExtTeleServiceConfig *pExtTeleServiceConfigReq = NULL;
    
    if(CapRoIdpConfigReq -> extteleinfo_size() > iIndex && iIndex > -1)
    {
        pExtTeleServiceConfigReq = CapRoIdpConfigReq -> mutable_extteleinfo(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into EXT_TELESERVICE_TO_SERVICE_ID_MAP_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"CAPRO_IDP_CONFIG_ID,");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select CAPRO_IDP_CONFIG_ID from CAPRO_IDP_CONFIG_TB),");

    if(pExtTeleServiceConfigReq && pExtTeleServiceConfigReq->has_extteleservicecode())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"EXT_TELESERVICE,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pExtTeleServiceConfigReq->extteleservicecode());
    }

    if(pExtTeleServiceConfigReq && pExtTeleServiceConfigReq->has_serviceid())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"SERVICE_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pExtTeleServiceConfigReq->serviceid());
    }

    
    sFieldName[strlen(sFieldName) -1] = ' ';
    sFieldValue[strlen(sFieldValue) -1] = ' ';

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void ExtTeleserviceToServiceIdMapTPBQuery::sql_ExtTeleserviceToServiceIdMap_Create_Mod_Query(CapRoIdpConfig *CapRoIdpConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
#if 0
    ExtTeleServiceConfig *pExtTeleServiceConfigReq = NULL;
    
    if(CapRoIdpConfigReq -> extteleinfo_size() > iIndex && iIndex > -1)
    {
        pExtTeleServiceConfigReq = CapRoIdpConfigReq -> mutable_extteleinfo(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update EXT_TELESERVICE_TO_SERVICE_ID_MAP_TB set "); 

    if(pExtTeleServiceConfigReq && pExtTeleServiceConfigReq->has_extteleservicecode())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"EXT_TELESERVICE = %d,",pExtTeleServiceConfigReq->extteleservicecode());
    }

    if(pExtTeleServiceConfigReq && pExtTeleServiceConfigReq->has_serviceid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SERVICE_ID = %d,",pExtTeleServiceConfigReq->serviceid());
    }
    
    pStatement[strlen(pStatement) -1] = ' ';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where",);
#endif
    DLOG_DEBUG("Modify is not there for this table");
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void ExtTeleserviceToServiceIdMapTPBQuery::sql_ExtTeleserviceToServiceIdMap_Create_Delete_Query(CapRoIdpConfig *CapRoIdpConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    ExtTeleServiceConfig *pExtTeleServiceConfigReq = NULL;
    
    if(CapRoIdpConfigReq -> extteleinfo_size() > iIndex && iIndex > -1)
    {
        pExtTeleServiceConfigReq = CapRoIdpConfigReq -> mutable_extteleinfo(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from EXT_TELESERVICE_TO_SERVICE_ID_MAP_TB where EXT_TELESERVICE = %d ",pExtTeleServiceConfigReq->extteleservicecode());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e ExtTeleserviceToServiceIdMapTPBQuery::sql_ExtTeleserviceToServiceIdMap_Payload_Validation(CapRoIdpConfig *CapRoIdpConfigReq,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    ExtTeleServiceConfig *pExtTeleServiceConfigReq = NULL;
    
    if(CapRoIdpConfigReq -> extteleinfo_size() > iIndex && iIndex > -1)
    {
        pExtTeleServiceConfigReq = CapRoIdpConfigReq -> mutable_extteleinfo(iIndex);
    }

    if(!pExtTeleServiceConfigReq && pExtTeleServiceConfigReq->has_extteleservicecode())
    {
        DLOG_ERROR("Primary Key  is not set in the request");
        return IWF_DB_FAIL;
    }
    if(!pExtTeleServiceConfigReq && pExtTeleServiceConfigReq->has_serviceid())
    {
        DLOG_ERROR("Primary Key  is not set in the request");
        return IWF_DB_FAIL;
    }

    return IWF_DB_SUCCESS;
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


void ExtTeleserviceToServiceIdMapTPBQuery::sql_ExtTeleserviceToServiceIdMap_Create_Select_Query(CapRoIdpConfig *CapRoIdpConfigReq,char *pStatement,int iIndex)
{
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    int iFlag = 0;
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    ExtTeleServiceConfig *pExtTeleServiceConfigReq = NULL;
    
    if(CapRoIdpConfigReq -> extteleinfo_size() > iIndex && iIndex > -1)
    {
        pExtTeleServiceConfigReq = CapRoIdpConfigReq -> mutable_extteleinfo(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from EXT_TELESERVICE_TO_SERVICE_ID_MAP_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pExtTeleServiceConfigReq && pExtTeleServiceConfigReq->has_extteleservicecode())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"EXT_TELESERVICE=%d and ",pExtTeleServiceConfigReq->extteleservicecode());
    }

    if(pExtTeleServiceConfigReq && pExtTeleServiceConfigReq->has_serviceid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SERVICE_ID=%d and ",pExtTeleServiceConfigReq->serviceid());
    }
    
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e ExtTeleserviceToServiceIdMapTPBQuery::sql_ExtTeleserviceToServiceIdMap_Check_All_Invalid(CapRoIdpConfig *CapRoIdpConfigReq,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    ExtTeleServiceConfig *pExtTeleServiceConfigReq = NULL;
    
    if(CapRoIdpConfigReq -> extteleinfo_size() > iIndex && iIndex > -1)
    {
        pExtTeleServiceConfigReq = CapRoIdpConfigReq -> mutable_extteleinfo(iIndex);
    }

    if(pExtTeleServiceConfigReq && pExtTeleServiceConfigReq->has_extteleservicecode())
    {
        return IWF_DB_FAIL;
    }
    if(pExtTeleServiceConfigReq && pExtTeleServiceConfigReq->has_serviceid())
    {
        return IWF_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
