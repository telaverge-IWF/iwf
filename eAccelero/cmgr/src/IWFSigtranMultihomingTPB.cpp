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
                                                                           *
 * ****************************************************************************/


#include <CMgrIwfDbInterface.h>

using namespace std;

void IWFSigtranMultihomingTPBQuery::sql_IWFSigtranMultihoming_Create_Check_Modifcation_Query(IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);


    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_SIGTRAN_MULTIHOMING_ID from IWF_SIGTRAN_MULTIHOMING_TB where OTHERHOME_IPADDR='%s'",pIwfSigtranMultihomingConfig->otheripaddress().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFSigtranMultihomingTPBQuery::sql_IWFSigtranMultihoming_Create_Check_Modifcation_Query(IwfSigtranSctpEndPointConfig *IwfSigtranSctpEndPointConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfigReq = NULL;

    if(IwfSigtranSctpEndPointConfigReq -> multihominginfo_size() > iIndex && iIndex > -1)
    {
        pIwfSigtranMultihomingConfigReq = IwfSigtranSctpEndPointConfigReq -> mutable_multihominginfo(iIndex);
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_SIGTRAN_MULTIHOMING_ID from IWF_SIGTRAN_MULTIHOMING_TB where IWF_SCTP_ENDPOINT_ID=(select IWF_SCTP_ENDPOINT_ID from IWF_SCTP_ENDPOINT_TB where ENDPOINT_NAME ='%s') and OTHERHOME_IPADDR='%s'",IwfSigtranSctpEndPointConfigReq->endpointname().c_str(),pIwfSigtranMultihomingConfigReq->otheripaddress().c_str());
    }
    else
    {
        DLOG_WARNING("Other_Home_IP is not configured, wrong iIndex = %d , sctpendpointinfo_size() = %d",iIndex,IwfSigtranSctpEndPointConfigReq->multihominginfo_size());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFSigtranMultihomingTPBQuery::sql_IWFSigtranMultihoming_Create_Add_Query(IwfSigtranSctpEndPointConfig *IwfSigtranSctpEndPointConfigReq,char *pStatement,int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  
    IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfigReq = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_SIGTRAN_MULTIHOMING_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(IwfSigtranSctpEndPointConfigReq -> multihominginfo_size() > iIndex && iIndex > -1)
    {
        pIwfSigtranMultihomingConfigReq = IwfSigtranSctpEndPointConfigReq -> mutable_multihominginfo(iIndex);

        if(pIwfSigtranMultihomingConfigReq->has_otheripaddress())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"OTHERHOME_IPADDR,");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pIwfSigtranMultihomingConfigReq->otheripaddress().c_str());
        }

    }

    if(IwfSigtranSctpEndPointConfigReq->has_endpointname())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IWF_SCTP_ENDPOINT_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select IWF_SCTP_ENDPOINT_ID from IWF_SCTP_ENDPOINT_TB where ENDPOINT_NAME ='%s'),",IwfSigtranSctpEndPointConfigReq->endpointname().c_str());
    }

    sFieldValue[strlen(sFieldValue) - 1] = ' ';
    sFieldName[strlen(sFieldName) - 1]   = ' ';

    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranMultihomingTPBQuery::sql_IWFSigtranMultihoming_Create_Mod_Query(IwfSigtranSctpEndPointConfig *IwfSigtranSctpEndPointConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    DLOG_DEBUG("All the fields are primary key, so update is not possible");
#if 0    
    if(AssociationConfigReq->ssn_config_size() > iIndex && iIndex > -1)
    {
	    IwfSigtranSctpEndPointConfigReq = AssociationConfigReq->mutable_ssn_config(iIndex);
    }


    snprintf(pStatement,MAX_STATEMENT_SIZE,"update LOCAL_SSN_TABLE set "); 

    if(AssociationConfigReq->has_pointcode())
    {
	    IwfSigtranSctpEndPointConfig* IwfSigtranSctpEndPointConfigReq = AssociationConfigReq->mutable_ssn_config(iIndex);
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LOCAL_CONFIG_ID=(select LOCAL_CONFIG_ID from LOCAL_CONFIG_TB when POINTCODE = %d),",AssociationConfigReq->pointcode());

    }

    if(AssociationConfigReq->has_ssn())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SSN = '%d',",AssociationConfigReq->ssn());

    }

    pStatement[strlen(pStatement) -1] = ' ';
#endif

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranMultihomingTPBQuery::sql_IWFSigtranMultihoming_Create_Delete_Query(IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_SIGTRAN_MULTIHOMING_TB where OTHERHOME_IPADDR='%s'",pIwfSigtranMultihomingConfigReq->otheripaddress().c_str());
    
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranMultihomingTPBQuery::sql_IWFSigtranMultihoming_Create_Delete_Query(IwfSigtranSctpEndPointConfig *IwfSigtranSctpEndPointConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfigReq = NULL;
    if(IwfSigtranSctpEndPointConfigReq -> multihominginfo_size() > iIndex && iIndex > -1)
    {
        pIwfSigtranMultihomingConfigReq = IwfSigtranSctpEndPointConfigReq -> mutable_multihominginfo(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_SIGTRAN_MULTIHOMING_TB where IWF_SCTP_ENDPOINT_ID=(select IWF_SCTP_ENDPOINT_ID from IWF_SCTP_ENDPOINT_TB where ENDPOINT_NAME ='%s') and OTHERHOME_IPADDR='%s'",IwfSigtranSctpEndPointConfigReq->endpointname().c_str(),pIwfSigtranMultihomingConfigReq->otheripaddress().c_str());
    
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSigtranMultihomingTPBQuery::sql_IWFSigtranMultihoming_Payload_Validation(IwfSigtranSctpEndPointConfig *IwfSigtranSctpEndPointConfigReq,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfigReq = NULL;
    if(IwfSigtranSctpEndPointConfigReq -> multihominginfo_size() > iIndex && iIndex > -1)
    {
        pIwfSigtranMultihomingConfigReq = IwfSigtranSctpEndPointConfigReq -> mutable_multihominginfo(iIndex);
    }

    if(!IwfSigtranSctpEndPointConfigReq->has_endpointname())
    {
        DLOG_ERROR("Primary Key transportname is not set in the request");
        return IWF_DB_FAIL;
    }

    if(!pIwfSigtranMultihomingConfigReq->has_otheripaddress())
    {
        DLOG_ERROR("Primary Key otheripaddress is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranMultihomingTPBQuery::sql_IWFSigtranMultihoming_Create_Select_Query(IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SIGTRAN_MULTIHOMING_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pIwfSigtranMultihomingConfig->has_multihomingid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_MULTIHOMING_ID=%d and ",pIwfSigtranMultihomingConfig->multihomingid());
    }

    if(pIwfSigtranMultihomingConfig->has_otheripaddress())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"OTHERHOME_IPADDR='%s' and ",pIwfSigtranMultihomingConfig->otheripaddress().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


void IWFSigtranMultihomingTPBQuery::sql_IWFSigtranMultihoming_Create_Select_Query(IwfSigtranSctpEndPointConfig *IwfSigtranSctpEndPointConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfigReq = NULL;

    if(IwfSigtranSctpEndPointConfigReq -> multihominginfo_size() > iIndex && iIndex > -1)
    {
        pIwfSigtranMultihomingConfigReq = IwfSigtranSctpEndPointConfigReq -> mutable_multihominginfo(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SIGTRAN_MULTIHOMING_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pIwfSigtranMultihomingConfigReq && pIwfSigtranMultihomingConfigReq->has_multihomingid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_MULTIHOMING_ID=%d and ",pIwfSigtranMultihomingConfigReq->multihomingid());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_endpointname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SCTP_ENDPOINT_ID=(select IWF_SCTP_ENDPOINT_ID from IWF_SCTP_ENDPOINT_TB where ENDPOINT_NAME ='%s') and ",IwfSigtranSctpEndPointConfigReq->endpointname().c_str());
    }

    if(pIwfSigtranMultihomingConfigReq && pIwfSigtranMultihomingConfigReq->has_otheripaddress())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"OTHERHOME_IPADDR='%s' and ",pIwfSigtranMultihomingConfigReq->otheripaddress().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSigtranMultihomingTPBQuery::sql_IWFSigtranMultihoming_Check_All_Invalid(IwfSigtranSctpEndPointConfig *IwfSigtranSctpEndPointConfigReq,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfigReq = NULL;

    if(IwfSigtranSctpEndPointConfigReq -> multihominginfo_size() > iIndex && iIndex > -1)
    {
        pIwfSigtranMultihomingConfigReq = IwfSigtranSctpEndPointConfigReq -> mutable_multihominginfo(iIndex);
    }

    if(IwfSigtranSctpEndPointConfigReq->has_endpointname())
    {
        return IWF_DB_FAIL;
    }   
    if(pIwfSigtranMultihomingConfigReq && pIwfSigtranMultihomingConfigReq->has_otheripaddress())
    {
        return IWF_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
