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

void IWFS6aMapSgsnPrefixMapTPBQuery::sql_IWFS6aMapSgsnPrefixMap_Create_Check_Modifcation_Query(IwfS6aToMapConfig *IwfS6aToMapConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfS6aToMapConfigReq->sgsnprefixconf_size() = %d, iIndex= %d",IwfS6aToMapConfigReq->sgsnprefixconf_size(),iIndex);    
    
    SgsnPrefixesConfig *pSgsnPrefixesConfigReq = NULL;

    if(IwfS6aToMapConfigReq -> sgsnprefixconf_size() > iIndex && iIndex > -1)
    {
        pSgsnPrefixesConfigReq = IwfS6aToMapConfigReq -> mutable_sgsnprefixconf(iIndex);
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select SGSN_PREFIX_MAP_ID from IWF_S6AMAP_SGSN_PREFIX_MAP where VPLMN_ID = '%s' ",pSgsnPrefixesConfigReq->vplmnid().c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFS6aMapSgsnPrefixMapTPBQuery::sql_IWFS6aMapSgsnPrefixMap_Create_Add_Query(IwfS6aToMapConfig *IwfS6aToMapConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfS6aToMapConfigReq->sgsnprefixconf_size() = %d, iIndex= %d",IwfS6aToMapConfigReq->sgsnprefixconf_size(),iIndex);    
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};
    
    SgsnPrefixesConfig *pSgsnPrefixesConfigReq = NULL;
    if(IwfS6aToMapConfigReq -> sgsnprefixconf_size() > iIndex && iIndex > -1)
    {
        pSgsnPrefixesConfigReq = IwfS6aToMapConfigReq -> mutable_sgsnprefixconf(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_S6AMAP_SGSN_PREFIX_MAP"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");
    
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_S6AMAP_CONFIG_ID,");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_S6AMAP_CONFIG_ID from IWF_S6AMAP_CONFIG_TB),");

    if(pSgsnPrefixesConfigReq && pSgsnPrefixesConfigReq->has_vplmnid())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"VPLMN_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pSgsnPrefixesConfigReq->vplmnid().c_str());
    }

    if(pSgsnPrefixesConfigReq && pSgsnPrefixesConfigReq-> has_sgsnprefix())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"SGSN_PREFIX,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pSgsnPrefixesConfigReq->sgsnprefix().c_str());
    }

    sFieldName[strlen(sFieldName) - 1]   = ' ';
    sFieldValue[strlen(sFieldValue) - 1] = ' ';

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFS6aMapSgsnPrefixMapTPBQuery::sql_IWFS6aMapSgsnPrefixMap_Create_Mod_Query(IwfS6aToMapConfig *IwfS6aToMapConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
#if 0
    DLOG_DEBUG("IwfS6aToMapConfigReq->sgsnprefixconf_size() = %d, iIndex= %d",IwfS6aToMapConfigReq->sgsnprefixconf_size(),iIndex);    
    
    SgsnPrefixesConfig *pSgsnPrefixesConfigReq = NULL;
    if(IwfS6aToMapConfigReq -> sgsnprefixconf_size() > iIndex && iIndex > -1)
    {
        pSgsnPrefixesConfigReq = IwfS6aToMapConfigReq -> mutable_sgsnprefixconf(int index);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_S6AMAP_SGSN_PREFIX_MAP set "); 

    if(pSgsnPrefixesConfigReq && pSgsnPrefixesConfigReq->has_vplmnid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"VPLMN_ID='%s',",IwfS6aToMapConfigReq->vplmnid().c_str());
    }

    if(pSgsnPrefixesConfigReq && pSgsnPrefixesConfigReq->has_sgsnprefix())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SGSN_PREFIX='%s',",pSgsnPrefixesConfigReq->sgsnprefix().c_str());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where IWF_S6AMAP_CONFIG_ID=(select IWF_S6AMAP_CONFIG_ID from IWF_S6AMAP_CONFIG_TB where IWF_TRANSLATOR = '%s') ",pIwfTranslatorConfigReq->translatorname().c_str());
#endif
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);

}

void IWFS6aMapSgsnPrefixMapTPBQuery::sql_IWFS6aMapSgsnPrefixMap_Create_Delete_Query(IwfS6aToMapConfig *IwfS6aToMapConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfS6aToMapConfigReq->sgsnprefixconf_size() = %d, iIndex= %d",IwfS6aToMapConfigReq->sgsnprefixconf_size(),iIndex);    

    SgsnPrefixesConfig *pSgsnPrefixesConfigReq = NULL;
    if(IwfS6aToMapConfigReq -> sgsnprefixconf_size() > iIndex && iIndex > -1)
    {
        pSgsnPrefixesConfigReq = IwfS6aToMapConfigReq -> mutable_sgsnprefixconf(iIndex);
    }
    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_S6AMAP_SGSN_PREFIX_MAP  where VPLMN_ID = '%s' ",pSgsnPrefixesConfigReq->vplmnid().c_str());
 
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFS6aMapSgsnPrefixMapTPBQuery::sql_IWFS6aMapSgsnPrefixMap_Payload_Validation(IwfS6aToMapConfig *IwfS6aToMapConfigReq,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfS6aToMapConfigReq->sgsnprefixconf_size() = %d, iIndex= %d",IwfS6aToMapConfigReq->sgsnprefixconf_size(),iIndex);    

    SgsnPrefixesConfig *pSgsnPrefixesConfigReq = NULL;
    if(IwfS6aToMapConfigReq -> sgsnprefixconf_size() > iIndex && iIndex > -1)
    {
        pSgsnPrefixesConfigReq = IwfS6aToMapConfigReq -> mutable_sgsnprefixconf(iIndex);
    }
    if(!pSgsnPrefixesConfigReq && pSgsnPrefixesConfigReq->has_vplmnid())
    {
        DLOG_ERROR("Unique Key VPLMN_ID is not set in the request");
        return IWF_DB_FAIL;
    }
    if(!pSgsnPrefixesConfigReq && pSgsnPrefixesConfigReq->has_sgsnprefix())
    {
        DLOG_ERROR("Unique Key IP_ADDRESS is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFS6aMapSgsnPrefixMapTPBQuery::sql_IWFS6aMapSgsnPrefixMap_Create_Select_Query(IwfS6aToMapConfig *IwfS6aToMapConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfS6aToMapConfigReq->sgsnprefixconf_size() = %d, iIndex= %d",IwfS6aToMapConfigReq->sgsnprefixconf_size(),iIndex);    
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    SgsnPrefixesConfig *pSgsnPrefixesConfigReq = NULL;
    if(IwfS6aToMapConfigReq -> sgsnprefixconf_size() > iIndex && iIndex > -1)
    {
        pSgsnPrefixesConfigReq = IwfS6aToMapConfigReq -> mutable_sgsnprefixconf(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_S6AMAP_SGSN_PREFIX_MAP "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pSgsnPrefixesConfigReq && pSgsnPrefixesConfigReq->has_vplmnid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"VPLMN_ID = '%s' and ",pSgsnPrefixesConfigReq->vplmnid().c_str());
    }

    if(pSgsnPrefixesConfigReq && pSgsnPrefixesConfigReq->has_sgsnprefix())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SGSN_PREFIX='%s' and ",pSgsnPrefixesConfigReq->sgsnprefix().c_str());
    }

    if(iFlag) 
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFS6aMapSgsnPrefixMapTPBQuery::sql_IWFS6aMapSgsnPrefixMap_Check_All_Invalid(IwfS6aToMapConfig *IwfS6aToMapConfigReq,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfS6aToMapConfigReq->sgsnprefixconf_size() = %d, iIndex= %d",IwfS6aToMapConfigReq->sgsnprefixconf_size(),iIndex);    
    SgsnPrefixesConfig *pSgsnPrefixesConfigReq = NULL;
    if(IwfS6aToMapConfigReq -> sgsnprefixconf_size() > iIndex && iIndex > -1)
    {
        pSgsnPrefixesConfigReq = IwfS6aToMapConfigReq -> mutable_sgsnprefixconf(iIndex);
    }

    if(pSgsnPrefixesConfigReq && pSgsnPrefixesConfigReq->has_vplmnid())
    {
        return IWF_DB_FAIL;
    }   
    if(pSgsnPrefixesConfigReq && pSgsnPrefixesConfigReq->has_sgsnprefix())
    {
        return IWF_DB_FAIL;
    }   

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
