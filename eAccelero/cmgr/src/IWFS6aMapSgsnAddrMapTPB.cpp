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

void IWFS6aMapSgsnAddrMapTPBQuery::sql_IWFS6aMapSgsnAddrMap_Create_Check_Modifcation_Query(IwfS6aToMapConfig *IwfS6aToMapConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfS6aToMapConfigReq->sgsnaddress_size() = %d, iIndex= %d",IwfS6aToMapConfigReq->sgsnaddress_size(),iIndex);    
    
    SgsnAddresses *pSgsnAddressesReq = NULL;

    if(IwfS6aToMapConfigReq -> sgsnaddress_size() > iIndex && iIndex > -1)
    {
        pSgsnAddressesReq = IwfS6aToMapConfigReq -> mutable_sgsnaddress(iIndex);
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select SGSN_ADDR_MAP_ID from IWF_S6AMAP_SGSN_ADDR_MAP where ORIGIN_HOST = '%s' ",pSgsnAddressesReq->orginhost().c_str());
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFS6aMapSgsnAddrMapTPBQuery::sql_IWFS6aMapSgsnAddrMap_Create_Add_Query(IwfS6aToMapConfig *IwfS6aToMapConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfS6aToMapConfigReq->sgsnaddress_size() = %d, iIndex= %d",IwfS6aToMapConfigReq->sgsnaddress_size(),iIndex);    
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};
    
    SgsnAddresses *pSgsnAddressesReq = NULL;
    if(IwfS6aToMapConfigReq -> sgsnaddress_size() > iIndex && iIndex > -1)
    {
        pSgsnAddressesReq = IwfS6aToMapConfigReq -> mutable_sgsnaddress(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_S6AMAP_SGSN_ADDR_MAP"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");
    
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_S6AMAP_CONFIG_ID,");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_S6AMAP_CONFIG_ID from IWF_S6AMAP_CONFIG_TB),");

    if(pSgsnAddressesReq && pSgsnAddressesReq->has_orginhost())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"ORIGIN_HOST,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pSgsnAddressesReq->orginhost().c_str());
    }

    if(pSgsnAddressesReq && pSgsnAddressesReq-> has_ipaddress())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IPADDRESS,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pSgsnAddressesReq->ipaddress().c_str());
    }

    sFieldName[strlen(sFieldName) - 1]   = ' ';
    sFieldValue[strlen(sFieldValue) - 1] = ' ';

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFS6aMapSgsnAddrMapTPBQuery::sql_IWFS6aMapSgsnAddrMap_Create_Mod_Query(IwfS6aToMapConfig *IwfS6aToMapConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
#if 0
    DLOG_DEBUG("IwfS6aToMapConfigReq->sgsnaddress_size() = %d, iIndex= %d",IwfS6aToMapConfigReq->sgsnaddress_size(),iIndex);    
    
    SgsnAddresses *pSgsnAddressesReq = NULL;
    if(IwfS6aToMapConfigReq -> sgsnaddress_size() > iIndex && iIndex > -1)
    {
        pSgsnAddressesReq = IwfS6aToMapConfigReq -> mutable_sgsnaddress(int index);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_S6AMAP_SGSN_ADDR_MAP set "); 

    if(pSgsnAddressesReq && pSgsnAddressesReq->has_orginhost())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ORIGIN_HOST='%s',",IwfS6aToMapConfigReq->orginhost().c_str());
    }

    if(pSgsnAddressesReq && pSgsnAddressesReq->has_ipaddress())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IPADDRESS='%s',",pSgsnAddressesReq->ipaddress().c_str());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where IWF_S6AMAP_CONFIG_ID=(select IWF_S6AMAP_CONFIG_ID from IWF_S6AMAP_CONFIG_TB where IWF_TRANSLATOR = '%s') ",pIwfTranslatorConfigReq->translatorname().c_str());
#endif
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);

}

void IWFS6aMapSgsnAddrMapTPBQuery::sql_IWFS6aMapSgsnAddrMap_Create_Delete_Query(IwfS6aToMapConfig *IwfS6aToMapConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfS6aToMapConfigReq->sgsnaddress_size() = %d, iIndex= %d",IwfS6aToMapConfigReq->sgsnaddress_size(),iIndex);    

    SgsnAddresses *pSgsnAddressesReq = NULL;
    if(IwfS6aToMapConfigReq -> sgsnaddress_size() > iIndex && iIndex > -1)
    {
        pSgsnAddressesReq = IwfS6aToMapConfigReq -> mutable_sgsnaddress(iIndex);
    }
    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_S6AMAP_SGSN_ADDR_MAP  where ORIGIN_HOST = '%s' ",pSgsnAddressesReq->orginhost().c_str());
 
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFS6aMapSgsnAddrMapTPBQuery::sql_IWFS6aMapSgsnAddrMap_Payload_Validation(IwfS6aToMapConfig *IwfS6aToMapConfigReq,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfS6aToMapConfigReq->sgsnaddress_size() = %d, iIndex= %d",IwfS6aToMapConfigReq->sgsnaddress_size(),iIndex);    

    SgsnAddresses *pSgsnAddressesReq = NULL;
    if(IwfS6aToMapConfigReq -> sgsnaddress_size() > iIndex && iIndex > -1)
    {
        pSgsnAddressesReq = IwfS6aToMapConfigReq -> mutable_sgsnaddress(iIndex);
    }
    if(!pSgsnAddressesReq && pSgsnAddressesReq->has_orginhost())
    {
        DLOG_ERROR("Unique Key ORIGIN_HOST is not set in the request");
        return IWF_DB_FAIL;
    }
    if(!pSgsnAddressesReq && pSgsnAddressesReq->has_ipaddress())
    {
        DLOG_ERROR("Unique Key IP_ADDRESS is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFS6aMapSgsnAddrMapTPBQuery::sql_IWFS6aMapSgsnAddrMap_Create_Select_Query(IwfS6aToMapConfig *IwfS6aToMapConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfS6aToMapConfigReq->sgsnaddress_size() = %d, iIndex= %d",IwfS6aToMapConfigReq->sgsnaddress_size(),iIndex);    
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    SgsnAddresses *pSgsnAddressesReq = NULL;
    if(IwfS6aToMapConfigReq -> sgsnaddress_size() > iIndex && iIndex > -1)
    {
        pSgsnAddressesReq = IwfS6aToMapConfigReq -> mutable_sgsnaddress(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_S6AMAP_SGSN_ADDR_MAP "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pSgsnAddressesReq && pSgsnAddressesReq->has_orginhost())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ORIGIN_HOST = '%s' and ",pSgsnAddressesReq->orginhost().c_str());
    }

    if(pSgsnAddressesReq && pSgsnAddressesReq->has_ipaddress())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IPADDRESS='%s' and ",pSgsnAddressesReq->ipaddress().c_str());
    }

    if(iFlag) 
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFS6aMapSgsnAddrMapTPBQuery::sql_IWFS6aMapSgsnAddrMap_Check_All_Invalid(IwfS6aToMapConfig *IwfS6aToMapConfigReq,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    DLOG_DEBUG("IwfS6aToMapConfigReq->sgsnaddress_size() = %d, iIndex= %d",IwfS6aToMapConfigReq->sgsnaddress_size(),iIndex);    
    SgsnAddresses *pSgsnAddressesReq = NULL;
    if(IwfS6aToMapConfigReq -> sgsnaddress_size() > iIndex && iIndex > -1)
    {
        pSgsnAddressesReq = IwfS6aToMapConfigReq -> mutable_sgsnaddress(iIndex);
    }

    if(pSgsnAddressesReq && pSgsnAddressesReq->has_orginhost())
    {
        return IWF_DB_FAIL;
    }   
    if(pSgsnAddressesReq && pSgsnAddressesReq->has_ipaddress())
    {
        return IWF_DB_FAIL;
    }   

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
