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

void IWFLocalConfigTPBQuery::sql_IWFLocalConfig_Create_Check_Modifcation_Query(IwfLocalHostConfig *IwfLocalHostConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_LOCAL_CONFIG_ID from IWF_LOCAL_CONFIG_TB ");
    
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFLocalConfigTPBQuery::sql_IWFLocalConfig_Create_Check_AspId_Modifcation_Query(int aspid,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_LOCAL_CONFIG_ID from IWF_LOCAL_CONFIG_TB where ASP_ID_1=%d or ASP_ID_2=%d",aspid,aspid);
    
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFLocalConfigTPBQuery::sql_IWFLocalConfig_Create_Add_Query(IwfLocalHostConfig *IwfLocalHostConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_LOCAL_CONFIG_TB"); 

    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(POINTCODE");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(%d",IwfLocalHostConfigReq->pointcode());

    if(IwfLocalHostConfigReq->has_protocolfamily())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IWF_PROTOCOL_FAMILY_ID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select IWF_PROTOCOL_FAMILY_ID from IWF_PROTOCOL_FAMILY_TB where FAMILY_NAME = '%s')",IwfLocalHostConfigReq->protocolfamily().c_str());
    }

    if(IwfLocalHostConfigReq->has_networkindicator())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",NI");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfLocalHostConfigReq->networkindicator());
    }

    if(IwfLocalHostConfigReq->has_gti())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",GTI");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfLocalHostConfigReq->gti());
    }

    if(IwfLocalHostConfigReq->has_tcapinvoketimer())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",TCAP_INVOKE_TIMER");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfLocalHostConfigReq->tcapinvoketimer());
    }

    if(IwfLocalHostConfigReq->has_addresstype())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ADDRESS_TYPE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfLocalHostConfigReq->addresstype().c_str());
    }

    if(IwfLocalHostConfigReq-> has_translationtype())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",TRANSLATION_TYPE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfLocalHostConfigReq->translationtype());
    }

    if(IwfLocalHostConfigReq-> has_numberingplan())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",NUMBERING_PLAN");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfLocalHostConfigReq->numberingplan());
    }

    if(IwfLocalHostConfigReq-> has_encodingscheme())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ENCODING_SCHEME");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfLocalHostConfigReq->encodingscheme());
    }

    if(IwfLocalHostConfigReq -> has_natureofaddrind())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",NATURE_OF_ADDRESS_INDICATOR");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfLocalHostConfigReq->natureofaddrind());
    }

    if(IwfLocalHostConfigReq -> has_selectcriteria())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SELECTION_CRITERIA");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfLocalHostConfigReq->selectcriteria());
    }

    if(IwfLocalHostConfigReq -> has_gtaddrdigits())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",GT_ADDR_DIGITS");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfLocalHostConfigReq->gtaddrdigits().c_str());
    }

    if(IwfLocalHostConfigReq -> has_localgtusefromconfig())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",USE_LOCAL_GT_FROM_CONFIG");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfLocalHostConfigReq->localgtusefromconfig());
    }

    if(IwfLocalHostConfigReq -> has_usesccpcdpafromincommingmsg())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",USE_SCCP_CDPA_FROM_INCOMMING_MSG");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfLocalHostConfigReq->usesccpcdpafromincommingmsg());
    }

    if(IwfLocalHostConfigReq -> has_includessn())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",INCLUDE_SSN");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfLocalHostConfigReq->includessn());
    }

    if(IwfLocalHostConfigReq -> has_includepc())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",INCLUDE_PC");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfLocalHostConfigReq->includepc());
    }

    if(IwfLocalHostConfigReq -> has_aspid1())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ASP_ID_1");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfLocalHostConfigReq->aspid1());
    }
    
    if(IwfLocalHostConfigReq -> has_aspid2())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ASP_ID_2");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfLocalHostConfigReq->aspid2());
    }
    
    if(IwfLocalHostConfigReq -> has_hostname1())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",HOST_NAME_1");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfLocalHostConfigReq->hostname1().c_str());
    }
    
    if(IwfLocalHostConfigReq -> has_hostname2())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",HOST_NAME_2");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfLocalHostConfigReq->hostname2().c_str());
    }
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFLocalConfigTPBQuery::sql_IWFLocalConfig_Create_Mod_Query(IwfLocalHostConfig *IwfLocalHostConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_LOCAL_CONFIG_TB set "); 

    if(IwfLocalHostConfigReq->has_protocolfamily())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_PROTOCOL_FAMILY_ID=(select IWF_PROTOCOL_FAMILY_ID from IWF_PROTOCOL_FAMILY_TB when FAMILY_NAME = '%s'),",IwfLocalHostConfigReq->protocolfamily().c_str());
    }

    if(IwfLocalHostConfigReq->has_networkindicator())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"NI = %d,",IwfLocalHostConfigReq->networkindicator());
    }

    if(IwfLocalHostConfigReq->has_gti())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"GTI= %d,",IwfLocalHostConfigReq->gti());
    }

    if(IwfLocalHostConfigReq->has_tcapinvoketimer())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TCAP_INVOKE_TIMER= %d,",IwfLocalHostConfigReq->tcapinvoketimer());
    }

    if(IwfLocalHostConfigReq->has_addresstype())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ADDRESS_TYPE= '%s',",IwfLocalHostConfigReq->addresstype().c_str());
    }

    if(IwfLocalHostConfigReq-> has_translationtype())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TRANSLATION_TYPE= %d,",IwfLocalHostConfigReq->translationtype());
    }

    if(IwfLocalHostConfigReq-> has_numberingplan())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"NUMBERING_PLAN= %d,",IwfLocalHostConfigReq->numberingplan());
    }

    if(IwfLocalHostConfigReq-> has_encodingscheme())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ENCODING_SCHEME= %d,",IwfLocalHostConfigReq->encodingscheme());
    }

    if(IwfLocalHostConfigReq-> has_natureofaddrind())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"NATURE_OF_ADDRESS_INDICATOR= %d,",IwfLocalHostConfigReq->natureofaddrind());
    }

    if(IwfLocalHostConfigReq -> has_selectcriteria())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SELECTION_CRITERIA= %d,",IwfLocalHostConfigReq->selectcriteria());
    }

    if(IwfLocalHostConfigReq-> has_gtaddrdigits())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"GT_ADDR_DIGITS= '%s',",IwfLocalHostConfigReq->gtaddrdigits().c_str());
    }

    if(IwfLocalHostConfigReq -> has_pointcode())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"POINTCODE= %d,",IwfLocalHostConfigReq->pointcode());
    }

    if(IwfLocalHostConfigReq -> has_localgtusefromconfig())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"USE_LOCAL_GT_FROM_CONFIG= %d,",IwfLocalHostConfigReq->localgtusefromconfig());
    }

    if(IwfLocalHostConfigReq -> has_usesccpcdpafromincommingmsg())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"USE_SCCP_CDPA_FROM_INCOMMING_MSG= %d,",IwfLocalHostConfigReq->usesccpcdpafromincommingmsg());
    }

    if(IwfLocalHostConfigReq -> has_includessn())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"INCLUDE_SSN= %d,",IwfLocalHostConfigReq->includessn());
    }

    if(IwfLocalHostConfigReq -> has_includepc())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"INCLUDE_PC= %d,",IwfLocalHostConfigReq->includepc());
    }

    if(IwfLocalHostConfigReq -> has_aspid1())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ASP_ID_1= %d,",IwfLocalHostConfigReq->aspid1());
    }
    
    if(IwfLocalHostConfigReq -> has_aspid2())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ASP_ID_2= %d,",IwfLocalHostConfigReq->aspid2());
    }
    
    if(IwfLocalHostConfigReq -> has_hostname1())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"HOST_NAME_1= '%s',",IwfLocalHostConfigReq->hostname1().c_str());
    }
    
    if(IwfLocalHostConfigReq -> has_hostname2())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"HOST_NAME_2= '%s',",IwfLocalHostConfigReq->hostname2().c_str());
    }
    pStatement[strlen(pStatement) -1] = ' ';

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFLocalConfigTPBQuery::sql_IWFLocalConfig_Create_Delete_Query(IwfLocalHostConfig *IwfLocalHostConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_LOCAL_CONFIG_TB where POINTCODE=%d ",IwfLocalHostConfigReq->pointcode());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFLocalConfigTPBQuery::sql_IWFLocalConfig_Payload_Validation(IwfLocalHostConfig *IwfLocalHostConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(IwfLocalHostConfigReq->has_pointcode())
    {
        DLOG_ERROR("Primary Key pointcode is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFLocalConfigTPBQuery::sql_IWFLocalConfig_Create_Select_Query(IwfLocalHostConfig *IwfLocalHostConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_LOCAL_CONFIG_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

#if 0
    if(IwfLocalHostConfigReq->has_localhostid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_LOCAL_CONFIG_ID=%d and ",IwfLocalHostConfigReq->localhostid());
    }
#endif

    if(IwfLocalHostConfigReq->has_protocolfamily())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_PROTOCOL_FAMILY_ID=(select IWF_PROTOCOL_FAMILY_ID from IWF_PROTOCOL_FAMILY_TB where FAMILY_NAME='%s') and ",IwfLocalHostConfigReq->protocolfamily().c_str());
    }

    if(IwfLocalHostConfigReq->has_networkindicator())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NI=%d and ",IwfLocalHostConfigReq->networkindicator());
    }

    if(IwfLocalHostConfigReq->has_pointcode())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"POINTCODE=%d and ",IwfLocalHostConfigReq->pointcode());
    }

    if(IwfLocalHostConfigReq->has_gti())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"GTI=%d and ",IwfLocalHostConfigReq->gti());
    }

    if(IwfLocalHostConfigReq->has_tcapinvoketimer())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TCAP_INVOKE_TIMER=%d and ",IwfLocalHostConfigReq->tcapinvoketimer());
    }

    if(IwfLocalHostConfigReq->has_addresstype())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ADDRESS_TYPE='%s' and ",IwfLocalHostConfigReq->addresstype().c_str());
    }

    if(IwfLocalHostConfigReq->has_translationtype())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TRANSLATION_TYPE=%d and ",IwfLocalHostConfigReq->translationtype());
    }

    if(IwfLocalHostConfigReq->has_numberingplan())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NUMBERING_PLAN=%d and ",IwfLocalHostConfigReq->numberingplan());
    }

    if(IwfLocalHostConfigReq->has_encodingscheme())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ENCODING_SCHEME=%d and ",IwfLocalHostConfigReq->encodingscheme());
    }
    
    if(IwfLocalHostConfigReq->has_natureofaddrind())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NATURE_OF_ADDRESS_INDICATOR=%d and ",IwfLocalHostConfigReq->natureofaddrind());
    }

    if(IwfLocalHostConfigReq->has_selectcriteria())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SELECTION_CRITERIA=%d and ",IwfLocalHostConfigReq->selectcriteria());
    }

    if(IwfLocalHostConfigReq->has_gtaddrdigits())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"GT_ADDR_DIGITS='%s' and ",IwfLocalHostConfigReq->gtaddrdigits().c_str());
    }

    if(IwfLocalHostConfigReq -> has_localgtusefromconfig())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"USE_LOCAL_GT_FROM_CONFIG= %d and ",IwfLocalHostConfigReq->localgtusefromconfig());
    }

    if(IwfLocalHostConfigReq -> has_usesccpcdpafromincommingmsg())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"USE_SCCP_CDPA_FROM_INCOMMING_MSG= %d and ",IwfLocalHostConfigReq->usesccpcdpafromincommingmsg());
    }

    if(IwfLocalHostConfigReq -> has_includessn())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"INCLUDE_SSN= %d and ",IwfLocalHostConfigReq->includessn());
    }

    if(IwfLocalHostConfigReq -> has_includepc())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"INCLUDE_PC= %d and ",IwfLocalHostConfigReq->includepc());
    }
    
    if(IwfLocalHostConfigReq -> has_aspid1())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ASP_ID_1= %d and ",IwfLocalHostConfigReq->aspid1());
    }
    
    if(IwfLocalHostConfigReq -> has_aspid2())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ASP_ID_2= %d and ",IwfLocalHostConfigReq->aspid2());
    }
    
    if(IwfLocalHostConfigReq -> has_hostname1())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"HOST_NAME_1= '%s' and ",IwfLocalHostConfigReq->hostname1().c_str());
    }
    
    if(IwfLocalHostConfigReq -> has_hostname2())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"HOST_NAME_2= '%s' and ",IwfLocalHostConfigReq->hostname2().c_str());
    }
    if(iFlag) 
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFLocalConfigTPBQuery::sql_IWFLocalConfig_Check_All_Invalid(IwfLocalHostConfig *IwfLocalHostConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(IwfLocalHostConfigReq->has_protocolfamily())
    {
        return IWF_DB_FAIL;
    }   
    if(IwfLocalHostConfigReq->has_networkindicator())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_pointcode())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_gti())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_tcapinvoketimer())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_addresstype())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_translationtype())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_numberingplan())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_encodingscheme())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_natureofaddrind())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_selectcriteria())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_gtaddrdigits())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_localgtusefromconfig())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_usesccpcdpafromincommingmsg())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_includessn())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_includepc())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_aspid1())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_aspid2())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_hostname1())
    {
        return IWF_DB_FAIL;
    }
    if(IwfLocalHostConfigReq->has_hostname2())
    {
        return IWF_DB_FAIL;
    }
    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
