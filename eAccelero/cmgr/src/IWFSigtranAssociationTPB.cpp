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

void IWFSigtranAssociationTPBQuery::sql_IWFSigtranAssociation_Create_Check_Modifcation_Query(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_SIGTRAN_ASSOC_ID from IWF_SIGTRAN_ASSOCIATION_TB where IWF_SIGTRAN_ASSOC_NAME = '%s'",IwfSigtranAssociationConfigReq->associationname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFSigtranAssociationTPBQuery::sql_IWFSigtranAssociation_Create_Add_Query(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  
    IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfigReq = NULL;
    IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfigReq = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_SIGTRAN_ASSOCIATION_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(IWF_SIGTRAN_ASSOC_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",IwfSigtranAssociationConfigReq->associationname().c_str());

    if(IwfSigtranAssociationConfigReq->has_sctpprofile())
    {
        pIwfSigtranSctpProfileConfigReq = IwfSigtranAssociationConfigReq->mutable_sctpprofile();
        if(pIwfSigtranSctpProfileConfigReq -> has_sctpprofilename())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IWF_SIGTRAN_SCTP_PROFILE_ID");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select IWF_SIGTRAN_SCTP_PROFILE_ID from IWF_SIGTRAN_SCTP_PROFILE_TB where IWF_SIGTRAN_SCTP_PROFILE_NAME = '%s')",pIwfSigtranSctpProfileConfigReq->sctpprofilename().c_str());
        }
    }
    else
    {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IWF_SIGTRAN_SCTP_PROFILE_ID");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select IWF_SIGTRAN_SCTP_PROFILE_ID from IWF_SIGTRAN_SCTP_PROFILE_TB where IWF_SIGTRAN_SCTP_PROFILE_NAME = 'default_sctp')");
    }

    if(IwfSigtranAssociationConfigReq->has_associationsetid())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IWF_SIGTRAN_ASSOC_SET_ID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME = '%s')",IwfSigtranAssociationConfigReq->associationsetname().c_str());
    }

    if(IwfSigtranAssociationConfigReq->has_localendpoint())
    {
        pIwfSigtranSctpEndPointConfigReq = IwfSigtranAssociationConfigReq->mutable_localendpoint();
        if(pIwfSigtranSctpEndPointConfigReq -> has_endpointname())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IWF_LOCAL_SCTP_ENDPOINT_ID");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select IWF_SCTP_ENDPOINT_ID from IWF_SCTP_ENDPOINT_TB where ENDPOINT_NAME ='%s')",pIwfSigtranSctpEndPointConfigReq->endpointname().c_str());
        }
    }

    if(IwfSigtranAssociationConfigReq->has_remoteendpoint())
    {
        pIwfSigtranSctpEndPointConfigReq = IwfSigtranAssociationConfigReq->mutable_remoteendpoint();
        if(pIwfSigtranSctpEndPointConfigReq -> has_endpointname())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IWF_REMOTE_SCTP_ENDPOINT_ID");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select IWF_SCTP_ENDPOINT_ID from IWF_SCTP_ENDPOINT_TB where ENDPOINT_NAME ='%s')",pIwfSigtranSctpEndPointConfigReq->endpointname().c_str());
        }
    }

    if(IwfSigtranAssociationConfigReq->has_status())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",STATUS");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranAssociationConfigReq->status());
    }

    if(IwfSigtranAssociationConfigReq->has_aspid())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ASP_ID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranAssociationConfigReq->aspid());
    }
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranAssociationTPBQuery::sql_IWFSigtranAssociation_Create_Mod_AspId_Query(int OldAspId, int ModifiedAspId,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_SIGTRAN_ASSOCIATION_TB set ASP_ID=%d where ASP_ID=%d", ModifiedAspId, OldAspId); 

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranAssociationTPBQuery::sql_IWFSigtranAssociation_Create_Mod_Query(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfigReq = NULL;
    IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfigReq = NULL;

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_SIGTRAN_ASSOCIATION_TB set "); 

    if(IwfSigtranAssociationConfigReq->has_sctpprofile())
    {
        pIwfSigtranSctpProfileConfigReq = IwfSigtranAssociationConfigReq->mutable_sctpprofile();
        if(pIwfSigtranSctpProfileConfigReq -> has_sctpprofilename())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_SCTP_PROFILE_ID = (select IWF_SIGTRAN_SCTP_PROFILE_ID from IWF_SIGTRAN_SCTP_PROFILE_TB where IWF_SIGTRAN_SCTP_PROFILE_NAME = '%s'),",pIwfSigtranSctpProfileConfigReq->sctpprofilename().c_str());
        }
    }

    if(IwfSigtranAssociationConfigReq->has_associationsetid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_ID =(select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME ='%s')",IwfSigtranAssociationConfigReq->associationsetname().c_str());
    }

    if(IwfSigtranAssociationConfigReq->has_localendpoint())
    {
        pIwfSigtranSctpEndPointConfigReq = IwfSigtranAssociationConfigReq->mutable_localendpoint();
        if(pIwfSigtranSctpEndPointConfigReq -> has_endpointname())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_LOCAL_SCTP_ENDPOINT_ID=(select IWF_SCTP_ENDPOINT_ID from IWF_SCTP_ENDPOINT_TB where ENDPOINT_NAME ='%s'),",pIwfSigtranSctpEndPointConfigReq->endpointname().c_str());
        }
    }

    if(IwfSigtranAssociationConfigReq->has_remoteendpoint())
    {
        pIwfSigtranSctpEndPointConfigReq = IwfSigtranAssociationConfigReq->mutable_remoteendpoint();
        if(pIwfSigtranSctpEndPointConfigReq -> has_endpointname())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_REMOTE_SCTP_ENDPOINT_ID=(select IWF_SCTP_ENDPOINT_ID from IWF_SCTP_ENDPOINT_TB where ENDPOINT_NAME ='%s'),",pIwfSigtranSctpEndPointConfigReq->endpointname().c_str());
        }
    }
    
    if(IwfSigtranAssociationConfigReq->has_status())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"STATUS=%d,",IwfSigtranAssociationConfigReq->status());
    }

    if(IwfSigtranAssociationConfigReq->has_aspid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ASP_ID=%d,",IwfSigtranAssociationConfigReq->aspid());
    }
    pStatement[strlen(pStatement) -1] = ' ';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where IWF_SIGTRAN_ASSOC_NAME='%s'",IwfSigtranAssociationConfigReq->associationname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranAssociationTPBQuery::sql_IWFSigtranAssociation_Create_Delete_Query(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_SIGTRAN_ASSOCIATION_TB where IWF_SIGTRAN_ASSOC_NAME='%s'",IwfSigtranAssociationConfigReq->associationname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSigtranAssociationTPBQuery::sql_IWFSigtranAssociation_Payload_Validation(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(!IwfSigtranAssociationConfigReq->has_associationname())
    {
        DLOG_ERROR("Primary Key IWF_SIGTRAN_ASSOC_NAME is not set in the request");
        return IWF_DB_FAIL;
    }

    return IWF_DB_SUCCESS;
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


void IWFSigtranAssociationTPBQuery::sql_IWFSigtranAssociation_Create_Select_Query(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    int iFlag = 0;
    IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfigReq = NULL;
    IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfigReq = NULL;

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SIGTRAN_ASSOCIATION_TB "); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfSigtranAssociationConfigReq->has_associationid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_ID=%d and ",IwfSigtranAssociationConfigReq->associationid());
    }

    if(IwfSigtranAssociationConfigReq->has_associationname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_NAME='%s' and ",IwfSigtranAssociationConfigReq->associationname().c_str());
    }

    if(IwfSigtranAssociationConfigReq->has_sctpprofile())
    {
        pIwfSigtranSctpProfileConfigReq = IwfSigtranAssociationConfigReq->mutable_sctpprofile();
        if(pIwfSigtranSctpProfileConfigReq -> has_sctpprofilename())
        {
        iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_SCTP_PROFILE_ID=(select IWF_SIGTRAN_SCTP_PROFILE_ID from IWF_SIGTRAN_SCTP_PROFILE_TB where IWF_SIGTRAN_SCTP_PROFILE_NAME = '%s') and ",pIwfSigtranSctpProfileConfigReq->sctpprofilename().c_str());
        }
    }
        
    if(IwfSigtranAssociationConfigReq->has_localendpoint())
    {
        pIwfSigtranSctpEndPointConfigReq = IwfSigtranAssociationConfigReq->mutable_localendpoint();
        if(pIwfSigtranSctpEndPointConfigReq -> has_endpointname())
        {
        iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_LOCAL_SCTP_ENDPOINT_ID=(select IWF_SCTP_ENDPOINT_ID from IWF_SCTP_ENDPOINT_TB where ENDPOINT_NAME ='%s') and ",pIwfSigtranSctpEndPointConfigReq->endpointname().c_str());
        }
    }
                             
    if(IwfSigtranAssociationConfigReq->has_remoteendpoint())
    {
        pIwfSigtranSctpEndPointConfigReq = IwfSigtranAssociationConfigReq->mutable_remoteendpoint();
        if(pIwfSigtranSctpEndPointConfigReq -> has_endpointname())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_REMOTE_SCTP_ENDPOINT_ID=(select IWF_SCTP_ENDPOINT_ID from IWF_SCTP_ENDPOINT_TB where ENDPOINT_NAME ='%s') and ",pIwfSigtranSctpEndPointConfigReq->endpointname().c_str());
        }
    }
    
    if(IwfSigtranAssociationConfigReq->has_status())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"STATUS=%d and ",IwfSigtranAssociationConfigReq->status());
    }

    if(IwfSigtranAssociationConfigReq->has_aspid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ASP_ID=%d and ",IwfSigtranAssociationConfigReq->aspid());
    }
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSigtranAssociationTPBQuery::sql_IWFSigtranAssociation_Check_All_Invalid(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfigReq = NULL;
    IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfigReq = NULL;

    if(IwfSigtranAssociationConfigReq->has_associationname())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranAssociationConfigReq->has_sctpprofile())
    {
        pIwfSigtranSctpProfileConfigReq = IwfSigtranAssociationConfigReq->mutable_sctpprofile();    
        if(pIwfSigtranSctpProfileConfigReq -> has_sctpprofilename())
        {
            return IWF_DB_FAIL;
        }
    }
    if(IwfSigtranAssociationConfigReq->has_associationsetid())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranAssociationConfigReq->has_localendpoint())
    {
        pIwfSigtranSctpEndPointConfigReq = IwfSigtranAssociationConfigReq->mutable_localendpoint();
        if(pIwfSigtranSctpEndPointConfigReq -> has_endpointname())
        {
            return IWF_DB_FAIL;
        }
    }
    if(IwfSigtranAssociationConfigReq->has_remoteendpoint())
    {
        pIwfSigtranSctpEndPointConfigReq = IwfSigtranAssociationConfigReq->mutable_remoteendpoint();
        if(pIwfSigtranSctpEndPointConfigReq -> has_endpointname())
        {
            return IWF_DB_FAIL;
        }
    }
    if(IwfSigtranAssociationConfigReq->has_status())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranAssociationConfigReq->has_aspid())
    {
        return IWF_DB_FAIL;
    }
    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
