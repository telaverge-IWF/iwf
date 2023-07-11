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

void IWFSctpEndpointTPBQuery::sql_IWFSctpEndpoint_Create_Check_Modifcation_Query(IwfSigtranSctpEndPointConfig *IwfSigtranSctpEndPointConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_SCTP_ENDPOINT_ID from IWF_SCTP_ENDPOINT_TB where ENDPOINT_NAME='%s'",IwfSigtranSctpEndPointConfigReq->endpointname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSctpEndpointTPBQuery::sql_IWFSctpEndpoint_Create_Add_Query(IwfSigtranSctpEndPointConfig *IwfSigtranSctpEndPointConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_SCTP_ENDPOINT_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(ENDPOINT_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",IwfSigtranSctpEndPointConfigReq->endpointname().c_str());

    if(IwfSigtranSctpEndPointConfigReq->has_endpointtype())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ENDPOINT_TYPE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfSigtranSctpEndPointConfigReq->endpointtype().c_str());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_ipaddress())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IP_ADDRESS");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfSigtranSctpEndPointConfigReq->ipaddress().c_str());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_port())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PORT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpEndPointConfigReq->port());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_transporttype())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",TRANSPORT_TYPE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfSigtranSctpEndPointConfigReq->transporttype().c_str());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_isclient())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IS_CLIENT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranSctpEndPointConfigReq->isclient());
    }

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSctpEndpointTPBQuery::sql_IWFSctpEndpoint_Create_Mod_Query(IwfSigtranSctpEndPointConfig *IwfSigtranSctpEndPointConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_SCTP_ENDPOINT_TB set "); 

    if(IwfSigtranSctpEndPointConfigReq->has_endpointtype())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ENDPOINT_TYPE= '%s',",IwfSigtranSctpEndPointConfigReq->endpointtype().c_str());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_ipaddress())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IP_ADDRESS= '%s',",IwfSigtranSctpEndPointConfigReq->ipaddress().c_str());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_port())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PORT= %d,",IwfSigtranSctpEndPointConfigReq->port());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_transporttype())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TRANSPORT_TYPE='%s',",IwfSigtranSctpEndPointConfigReq->transporttype().c_str());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_isclient())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IS_CLIENT=%d,",IwfSigtranSctpEndPointConfigReq->isclient());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where ENDPOINT_NAME='%s' ",IwfSigtranSctpEndPointConfigReq->endpointname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);

}

void IWFSctpEndpointTPBQuery::sql_IWFSctpEndpoint_Create_Delete_Query(IwfSigtranSctpEndPointConfig *IwfSigtranSctpEndPointConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_SCTP_ENDPOINT_TB where ENDPOINT_NAME='%s'",IwfSigtranSctpEndPointConfigReq->endpointname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSctpEndpointTPBQuery::sql_IWFSctpEndpoint_Payload_Validation(IwfSigtranSctpEndPointConfig *IwfSigtranSctpEndPointConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(!IwfSigtranSctpEndPointConfigReq->has_endpointname())
    {
        DLOG_ERROR("Primary Key ENDPOINT_NAME is not set in the request");
        return IWF_DB_FAIL;
    }
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


void IWFSctpEndpointTPBQuery::sql_IWFSctpEndpoint_Create_Select_Query(IwfSigtranSctpEndPointConfig *IwfSigtranSctpEndPointConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SCTP_ENDPOINT_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfSigtranSctpEndPointConfigReq->has_sctpendpointid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SCTP_ENDPOINT_ID=%d and ",IwfSigtranSctpEndPointConfigReq->sctpendpointid());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_endpointname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ENDPOINT_NAME='%s' and ",IwfSigtranSctpEndPointConfigReq->endpointname().c_str());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_endpointtype())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ENDPOINT_TYPE='%s' and ",IwfSigtranSctpEndPointConfigReq->endpointtype().c_str());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_ipaddress())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IP_ADDRESS='%s' and ",IwfSigtranSctpEndPointConfigReq->ipaddress().c_str());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_port())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PORT=%d and ",IwfSigtranSctpEndPointConfigReq->port());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_transporttype())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TRANSPORT_TYPE='%s' and ",IwfSigtranSctpEndPointConfigReq->transporttype().c_str());
    }

    if(IwfSigtranSctpEndPointConfigReq->has_isclient())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IS_CLIENT=%d and ",IwfSigtranSctpEndPointConfigReq->isclient());  //Boolean ...???
    }

    if(iFlag) 
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSctpEndpointTPBQuery::sql_IWFSctpEndpoint_Check_All_Invalid(IwfSigtranSctpEndPointConfig *IwfSigtranSctpEndPointConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(IwfSigtranSctpEndPointConfigReq->has_endpointname())
    {
        return IWF_DB_FAIL;
    }   
    if(IwfSigtranSctpEndPointConfigReq->has_ipaddress())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpEndPointConfigReq->has_port())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpEndPointConfigReq->has_endpointtype())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpEndPointConfigReq->has_transporttype())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranSctpEndPointConfigReq->has_isclient())
    {
        return IWF_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
