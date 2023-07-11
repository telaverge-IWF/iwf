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

void IWFSigtranRemoteRouteTPBQuery::sql_IWFSigtranRemoteRoute_Create_Check_Modifcation_Query(IwfSigtranRemoteRouteConfig *IwfSigtranRemoteRouteConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_SIGTRAN_REMOTE_ROUTE_ID from IWF_SIGTRAN_REMOTE_ROUTE_TB where REMOTE_ROUTE_NAME = '%s'", IwfSigtranRemoteRouteConfigReq -> remoteroutename().c_str());
    //snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_SIGTRAN_REMOTE_ROUTE_ID from IWF_SIGTRAN_REMOTE_ROUTE_TB where DEST_NAME = '%s'", pIwfSigtranDestinationConfigReq -> destinationname().c_str());
    
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFSigtranRemoteRouteTPBQuery::sql_IWFSigtranRemoteRoute_Create_Add_Query(IwfSigtranRemoteRouteConfig *IwfSigtranRemoteRouteConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  

    IwfSigtranDestinationConfig *pIwfSigtranDestinationConfigReq = NULL;
    pIwfSigtranDestinationConfigReq = IwfSigtranRemoteRouteConfigReq -> mutable_destinationinfo();

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_SIGTRAN_REMOTE_ROUTE_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(IWF_SIGTRAN_ASSOC_SET_ID, IWF_SIGTRAN_DESTINATION_ID");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"((select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME ='%s'), (select IWF_SIGTRAN_DESTINATION_ID from IWF_SIGTRAN_DESTINATION_TB where DEST_NAME = '%s')", IwfSigtranRemoteRouteConfigReq -> associationsetname().c_str(), pIwfSigtranDestinationConfigReq -> destinationname().c_str());

    if(IwfSigtranRemoteRouteConfigReq -> has_priority())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PRIORITY");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranRemoteRouteConfigReq -> priority());
    }

    if(IwfSigtranRemoteRouteConfigReq-> has_remoteroutename())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",REMOTE_ROUTE_NAME");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfSigtranRemoteRouteConfigReq -> remoteroutename().c_str());
    }

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

     DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranRemoteRouteTPBQuery::sql_IWFSigtranRemoteRoute_Create_Mod_Query(IwfSigtranRemoteRouteConfig *IwfSigtranRemoteRouteConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    IwfSigtranDestinationConfig *pIwfSigtranDestinationConfigReq = NULL;
    pIwfSigtranDestinationConfigReq = IwfSigtranRemoteRouteConfigReq -> mutable_destinationinfo();
    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_SIGTRAN_REMOTE_ROUTE_TB set "); 

    if(IwfSigtranRemoteRouteConfigReq -> has_priority())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PRIORITY =%d,",IwfSigtranRemoteRouteConfigReq -> priority());
    }

    if(IwfSigtranRemoteRouteConfigReq-> has_associationsetname())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_ID=(select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME ='%s'),",IwfSigtranRemoteRouteConfigReq ->associationsetname().c_str());
    }

    if(pIwfSigtranDestinationConfigReq-> has_destinationname())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_DESTINATION_ID=(select IWF_SIGTRAN_DESTINATION_ID from IWF_SIGTRAN_DESTINATION_TB where DEST_NAME = '%s'),",pIwfSigtranDestinationConfigReq->destinationname().c_str());
    }
#if 0
    if(IwfSigtranRemoteRouteConfigReq-> has_remoteroutename())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"REMOTE_ROUTE_NAME='%s',",IwfSigtranRemoteRouteConfigReq -> remoteroutename().c_str());
    }

#endif
    pStatement[strlen(pStatement) -1] = ' ';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where REMOTE_ROUTE_NAME='%s' ",IwfSigtranRemoteRouteConfigReq->remoteroutename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranRemoteRouteTPBQuery::sql_IWFSigtranRemoteRoute_Create_Delete_Query(IwfSigtranRemoteRouteConfig *IwfSigtranRemoteRouteConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    //IwfSigtranDestinationConfig *pIwfSigtranDestinationConfigReq = NULL;
    //pIwfSigtranDestinationConfigReq = IwfSigtranRemoteRouteConfigReq -> mutable_destinationinfo();

//    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_SIGTRAN_REMOTE_ROUTE_TB where IWF_SIGTRAN_ASSOC_SET_ID = (select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME ='%s') and IWF_SIGTRAN_DESTINATION_ID = (select IWF_SIGTRAN_DESTINATION_ID from IWF_SIGTRAN_DESTINATION_TB where DEST_NAME = '%s')",IwfSigtranRemoteRouteConfigReq -> associationsetname().c_str(), pIwfSigtranDestinationConfigReq -> destinationname().c_str());
    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_SIGTRAN_REMOTE_ROUTE_TB where REMOTE_ROUTE_NAME='%s' ",IwfSigtranRemoteRouteConfigReq->remoteroutename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSigtranRemoteRouteTPBQuery::sql_IWFSigtranRemoteRoute_Payload_Validation(IwfSigtranRemoteRouteConfig *IwfSigtranRemoteRouteConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    IwfSigtranDestinationConfig *pIwfSigtranDestinationConfigReq = NULL;
    pIwfSigtranDestinationConfigReq = IwfSigtranRemoteRouteConfigReq -> mutable_destinationinfo();

    if(!IwfSigtranRemoteRouteConfigReq -> has_associationsetid())
    {
        DLOG_ERROR("Primary Key Association_set_id is not set in the request");
        return IWF_DB_FAIL;
    }

    if(!pIwfSigtranDestinationConfigReq && pIwfSigtranDestinationConfigReq -> has_destinationid())
    {
        DLOG_ERROR("Primary Key Dest_id is not set in the request");
        return IWF_DB_FAIL;
    }

    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranRemoteRouteTPBQuery::sql_IWFSigtranRemoteRoute_Create_Select_Query_For_Delete_Association_Validation(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig, char * pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SIGTRAN_REMOTE_ROUTE_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pIwfSigtranAssociationConfig->has_associationname())
    {
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_ID = (select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_MAPPING_TB where IWF_SIGTRAN_ASSOC_ID = (select IWF_SIGTRAN_ASSOC_ID from IWF_SIGTRAN_ASSOCIATION_TB where IWF_SIGTRAN_ASSOC_NAME = '%s'))",pIwfSigtranAssociationConfig->associationname().c_str());
        
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }
    
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranRemoteRouteTPBQuery::sql_IWFSigtranRemoteRoute_Create_Select_Query(IwfSigtranRemoteRouteConfig *IwfSigtranRemoteRouteConfigReq,char *pStatement)
{
    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    IwfSigtranDestinationConfig *pIwfSigtranDestinationConfigReq = NULL;
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SIGTRAN_REMOTE_ROUTE_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfSigtranRemoteRouteConfigReq -> has_associationsetname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_ID = (select IWF_SIGTRAN_ASSOC_SET_ID from IWF_SIGTRAN_ASSOC_SET_TB where IWF_SIGTRAN_ASSOC_SET_NAME ='%s') and ",IwfSigtranRemoteRouteConfigReq->associationsetname().c_str());
    }

    if(IwfSigtranRemoteRouteConfigReq && IwfSigtranRemoteRouteConfigReq -> has_destinationinfo())
    {
        pIwfSigtranDestinationConfigReq = IwfSigtranRemoteRouteConfigReq -> mutable_destinationinfo();
        if(pIwfSigtranDestinationConfigReq -> has_destinationname())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_DESTINATION_ID = (select IWF_SIGTRAN_DESTINATION_ID from IWF_SIGTRAN_DESTINATION_TB where DEST_NAME = '%s') and ",pIwfSigtranDestinationConfigReq -> destinationname().c_str());
        }
    }

    if(IwfSigtranRemoteRouteConfigReq -> has_priority())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PRIORITY = %d and ",IwfSigtranRemoteRouteConfigReq -> priority());
    }

    if(IwfSigtranRemoteRouteConfigReq -> has_remoteroutename())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REMOTE_ROUTE_NAME = '%s' and ",IwfSigtranRemoteRouteConfigReq -> remoteroutename().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSigtranRemoteRouteTPBQuery::sql_IWFSigtranRemoteRoute_Check_All_Invalid(IwfSigtranRemoteRouteConfig *IwfSigtranRemoteRouteConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    IwfSigtranDestinationConfig *pIwfSigtranDestinationConfigReq = NULL;

    if(IwfSigtranRemoteRouteConfigReq -> has_associationsetid())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranRemoteRouteConfigReq && IwfSigtranRemoteRouteConfigReq -> has_destinationinfo())
    {
        pIwfSigtranDestinationConfigReq = IwfSigtranRemoteRouteConfigReq -> mutable_destinationinfo();
        if(pIwfSigtranDestinationConfigReq -> has_destinationname())
        {
            return IWF_DB_FAIL;
        }
    }
    if(IwfSigtranRemoteRouteConfigReq -> has_priority())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranRemoteRouteConfigReq -> has_remoteroutename())
    {
        return IWF_DB_FAIL;
    }

    
    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
