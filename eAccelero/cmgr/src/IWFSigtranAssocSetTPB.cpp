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

void IWFSigtranAssocSetTPBQuery::sql_IWFSigtranAssocSet_Create_Check_Modifcation_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME = '%s' ",IwfSigtranAssociationSetConfigReq->associationsetname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFSigtranAssocSetTPBQuery::sql_IWFSigtranAssocSet_Create_Add_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_SIGTRAN_ASSOC_SET_TB "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(IWF_SIGTRAN_ASSOC_SET_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",IwfSigtranAssociationSetConfigReq->associationsetname().c_str());

    if(IwfSigtranAssociationSetConfigReq->has_networkindicator())
    { 
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",NI"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranAssociationSetConfigReq->networkindicator());
    }

    if(IwfSigtranAssociationSetConfigReq->has_adjacenpointcode())
    { 
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",APC"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranAssociationSetConfigReq->adjacenpointcode());
    }

    if(IwfSigtranAssociationSetConfigReq->has_routingcontext())
    { 
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ROUTING_CONTEXT"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranAssociationSetConfigReq->routingcontext());
    }
#if 0
    if(IwfSigtranAssociationSetConfigReq->has_acktimer())
    { 
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ACK_TIMER"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranAssociationSetConfigReq->acktimer());
    }

    if(IwfSigtranAssociationSetConfigReq->has_sigtranmode())
    { 
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SIGTRAN_MODE"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfSigtranAssociationSetConfigReq->sigtranmode().c_str());
    }
#endif
    if(IwfSigtranAssociationSetConfigReq->has_trafficmode())
    { 
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",TRAFFIC_MODE"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfSigtranAssociationSetConfigReq->trafficmode().c_str());
    }

    if(IwfSigtranAssociationSetConfigReq->has_aspid())
    { 
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ASP_ID"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranAssociationSetConfigReq->aspid());
    }

    if(IwfSigtranAssociationSetConfigReq->has_status())
    { 
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",STATUS"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranAssociationSetConfigReq->status());
    }

    if(IwfSigtranAssociationSetConfigReq->has_ismember())
    { 
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IS_MEMBER"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranAssociationSetConfigReq->ismember());
    }

    if(IwfSigtranAssociationSetConfigReq->has_homeip())
    { 
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",HOME_IP"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfSigtranAssociationSetConfigReq->homeip().c_str());
    }

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")"); 
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")"); 

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFSigtranAssocSetTPBQuery::sql_IWFSigtranAssocSet_Create_Delete_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME ='%s'",IwfSigtranAssociationSetConfigReq->associationsetname().c_str()); 

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFSigtranAssocSetTPBQuery::sql_IWFSigtranAssocSet_Create_Mod_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_SIGTRAN_ASSOC_SET_TB set "); 

    if(IwfSigtranAssociationSetConfigReq->has_networkindicator())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"NI=%d,",IwfSigtranAssociationSetConfigReq->networkindicator());
    }

    if(IwfSigtranAssociationSetConfigReq->has_adjacenpointcode())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"APC=%d,",IwfSigtranAssociationSetConfigReq->adjacenpointcode());
    }

    if(IwfSigtranAssociationSetConfigReq->has_routingcontext())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ROUTING_CONTEXT=%d,",IwfSigtranAssociationSetConfigReq->routingcontext());
    }
#if 0
    if(IwfSigtranAssociationSetConfigReq->has_acktimer())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ACK_TIMER=%d,",IwfSigtranAssociationSetConfigReq->acktimer());
    }

    if(IwfSigtranAssociationSetConfigReq->has_sigtranmode())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SIGTRAN_MODE='%s',",IwfSigtranAssociationSetConfigReq->sigtranmode().c_str());
    }
#endif
    if(IwfSigtranAssociationSetConfigReq->has_trafficmode())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TRAFFIC_MODE='%s',",IwfSigtranAssociationSetConfigReq->trafficmode().c_str());
    }

    if(IwfSigtranAssociationSetConfigReq->has_aspid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ASP_ID=%d,",IwfSigtranAssociationSetConfigReq->aspid());
    }

    if(IwfSigtranAssociationSetConfigReq->has_status())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"STATUS=%d,",IwfSigtranAssociationSetConfigReq->status());
    }

    if(IwfSigtranAssociationSetConfigReq->has_ismember())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IS_MEMBER=%d,",IwfSigtranAssociationSetConfigReq->ismember());
    }

    if(IwfSigtranAssociationSetConfigReq->has_homeip())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"HOME_IP='%s',",IwfSigtranAssociationSetConfigReq->homeip().c_str());
    }
    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where IWF_SIGTRAN_ASSOC_SET_NAME ='%s'",IwfSigtranAssociationSetConfigReq->associationsetname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e IWFSigtranAssocSetTPBQuery::sql_IWFSigtranAssocSet_Payload_Validation(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (!IwfSigtranAssociationSetConfigReq->has_associationsetname())
    {
        DLOG_ERROR("Primary Key General Config Id is not set in the request");
        return IWF_DB_SUCCESS; 
    }

    return IWF_DB_SUCCESS;
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFSigtranAssocSetTPBQuery::sql_IWFSigtranAssocSet_Create_Select_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SIGTRAN_ASSOC_SET_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfSigtranAssociationSetConfigReq->has_associationsetid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_ID=%d and ",IwfSigtranAssociationSetConfigReq->associationsetid());
    }

    if(IwfSigtranAssociationSetConfigReq->has_associationsetname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_NAME='%s' and ",IwfSigtranAssociationSetConfigReq->associationsetname().c_str());
    }

    if(IwfSigtranAssociationSetConfigReq->has_networkindicator())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NI=%d and ",IwfSigtranAssociationSetConfigReq->networkindicator());
    }
    
    if(IwfSigtranAssociationSetConfigReq->has_adjacenpointcode())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"APC=%d and ",IwfSigtranAssociationSetConfigReq->adjacenpointcode());
    }

    if(IwfSigtranAssociationSetConfigReq->has_routingcontext())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ROUTING_CONTEXT=%d and ",IwfSigtranAssociationSetConfigReq->routingcontext());
    }
#if 0
    if(IwfSigtranAssociationSetConfigReq->has_acktimer())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ACK_TIMER=%d and ",IwfSigtranAssociationSetConfigReq->acktimer());
    }

    if(IwfSigtranAssociationSetConfigReq->has_sigtranmode())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SIGTRAN_MODE='%s' and ",IwfSigtranAssociationSetConfigReq->sigtranmode().c_str());
    }
#endif
    if(IwfSigtranAssociationSetConfigReq->has_trafficmode())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TRAFFIC_MODE='%s' and ",IwfSigtranAssociationSetConfigReq->trafficmode().c_str());
    }

    if(IwfSigtranAssociationSetConfigReq->has_aspid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ASP_ID=%d and ",IwfSigtranAssociationSetConfigReq->aspid());
    }

    if(IwfSigtranAssociationSetConfigReq->has_status())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"STATUS=%d and ",IwfSigtranAssociationSetConfigReq->status());
    }

    if(IwfSigtranAssociationSetConfigReq->has_ismember())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IS_MEMBER=%d and ",IwfSigtranAssociationSetConfigReq->ismember());
    }
    
    if(IwfSigtranAssociationSetConfigReq->has_homeip())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"HOME_IP='%s' and ",IwfSigtranAssociationSetConfigReq->homeip().c_str());
    }
    
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e IWFSigtranAssocSetTPBQuery::sql_IWFSigtranAssocSet_Check_All_Invalid(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (IwfSigtranAssociationSetConfigReq->has_associationsetname())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranAssociationSetConfigReq->has_networkindicator())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranAssociationSetConfigReq->has_adjacenpointcode())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranAssociationSetConfigReq->has_routingcontext())
    {
        return IWF_DB_FAIL;
    }
#if 0
    if(IwfSigtranAssociationSetConfigReq->has_acktimer())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranAssociationSetConfigReq->has_sigtranmode())
    {
        return IWF_DB_FAIL;
    }
#endif
    if(IwfSigtranAssociationSetConfigReq->has_trafficmode())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranAssociationSetConfigReq->has_aspid())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranAssociationSetConfigReq->has_status())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranAssociationSetConfigReq->has_ismember())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranAssociationSetConfigReq->has_homeip())
    {
        return IWF_DB_FAIL;
    }
    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__);
}
