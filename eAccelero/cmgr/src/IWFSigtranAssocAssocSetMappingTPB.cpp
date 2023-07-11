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

void IWFSigtranAssocAndAssocSetTPBQuery::sql_IWFSigtranAssocAndAssocSet_Create_Select_Query(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig,char *pStatement)
{

    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    int iFlag                   = 0;

    DLOG_NONE(" > %s \n",__FUNCTION__); 

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_SIGTRAN_ASSOC_SET_TB.IWF_SIGTRAN_ASSOC_SET_ID,"
                                    "IWF_SIGTRAN_ASSOC_SET_TB.IWF_SIGTRAN_ASSOC_SET_NAME,"
                                    "IWF_SIGTRAN_ASSOC_SET_TB.STATUS as ASSOC_SET_STATUS,"
                                    "IWF_SIGTRAN_ASSOCIATION_TB.ASP_ID,"
                                    "IWF_SIGTRAN_ASSOCIATION_TB.IWF_SIGTRAN_ASSOC_ID,"
                                    "IWF_SIGTRAN_ASSOCIATION_TB.IWF_SIGTRAN_ASSOC_NAME,"
                                    "IWF_SIGTRAN_ASSOCIATION_TB.IWF_SIGTRAN_SCTP_PROFILE_ID,"
                                    "IWF_SIGTRAN_ASSOCIATION_TB.IWF_LOCAL_SCTP_ENDPOINT_ID,"
                                    "IWF_SIGTRAN_ASSOCIATION_TB.IWF_REMOTE_SCTP_ENDPOINT_ID,"
                                    "IWF_SIGTRAN_ASSOCIATION_TB.STATUS as ASSOCIATION_STATUS,"
                                    "IWF_SIGTRAN_ASSOC_SET_MAPPING_TB.IWF_SIGTRAN_ASSOC_SET_MAPPING_ID,"
                                    "IWF_SIGTRAN_ASSOC_SET_MAPPING_TB.IWF_SIGTRAN_ASSOC_MAPPING_ID"
                                    " from IWF_SIGTRAN_ASSOC_SET_MAPPING_TB"
                                    " inner join IWF_SIGTRAN_ASSOC_SET_TB on IWF_SIGTRAN_ASSOC_SET_TB.IWF_SIGTRAN_ASSOC_SET_ID = IWF_SIGTRAN_ASSOC_SET_MAPPING_TB.IWF_SIGTRAN_ASSOC_SET_ID"
                                    " inner join IWF_SIGTRAN_ASSOCIATION_TB on IWF_SIGTRAN_ASSOCIATION_TB.IWF_SIGTRAN_ASSOC_ID = IWF_SIGTRAN_ASSOC_SET_MAPPING_TB.IWF_SIGTRAN_ASSOC_ID ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");



    if(pIwfSigtranAssociationConfig->has_associationid())   
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOCIATION_TB.IWF_SIGTRAN_ASSOC_ID=%d and ",pIwfSigtranAssociationConfig->associationid());
    }

    if(pIwfSigtranAssociationConfig->has_associationname())   
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOCIATION_TB.IWF_SIGTRAN_ASSOC_NAME='%s' and ",pIwfSigtranAssociationConfig->associationname().c_str());
    }

    if(pIwfSigtranAssociationConfig->has_associationsetname())   
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_TB.IWF_SIGTRAN_ASSOC_SET_NAME='%s' and ",pIwfSigtranAssociationConfig->associationsetname().c_str());
    }

    if(pIwfSigtranAssociationConfig->has_associationsetid())   
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_TB.IWF_SIGTRAN_ASSOC_SET_ID=%d and ",pIwfSigtranAssociationConfig->associationsetid());
    }

    if(pIwfSigtranAssociationConfig->has_sctpprofile())
    {
        IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig = pIwfSigtranAssociationConfig->mutable_sctpprofile();
        if(pIwfSigtranSctpProfileConfig->has_sctpprofilename())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOCIATION_TB.IWF_SIGTRAN_SCTP_PROFILE_ID=(select IWF_SIGTRAN_SCTP_PROFILE_ID from IWF_SIGTRAN_SCTP_PROFILE_TB where IWF_SIGTRAN_SCTP_PROFILE_NAME='%s') and ",pIwfSigtranSctpProfileConfig->sctpprofilename().c_str());
        }

    }

    if(pIwfSigtranAssociationConfig->has_localendpoint())
    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_localendpoint();
        if(pIwfSigtranSctpEndPointConfig->has_endpointname())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOCIATION_TB.IWF_LOCAL_SCTP_ENDPOINT_ID=(select IWF_SCTP_ENDPOINT_ID from IWF_SCTP_ENDPOINT_TB where ENDPOINT_NAME='%s') and ",pIwfSigtranSctpEndPointConfig->endpointname().c_str());
        }
    }

    if(pIwfSigtranAssociationConfig->has_remoteendpoint())
    {
        IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig = pIwfSigtranAssociationConfig->mutable_remoteendpoint();
        if(pIwfSigtranSctpEndPointConfig->has_endpointname())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOCIATION_TB.IWF_REMOTE_SCTP_ENDPOINT_ID=(select IWF_SCTP_ENDPOINT_ID from IWF_SCTP_ENDPOINT_TB where ENDPOINT_NAME='%s') and ",pIwfSigtranSctpEndPointConfig->endpointname().c_str());
        }
    }

    if(iFlag == 1)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s \n",__FUNCTION__); 
}

void IWFSigtranAssocAndAssocSetTPBQuery::sql_IWFSigtranAssocAndAssocSet_Create_Select_Query(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig,char *pStatement)
{

    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    int iFlag                   = 0;

    DLOG_NONE(" > %s \n",__FUNCTION__); 

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_SIGTRAN_ASSOC_SET_TB.IWF_SIGTRAN_ASSOC_SET_ID,"
                                    "IWF_SIGTRAN_ASSOC_SET_TB.IWF_SIGTRAN_ASSOC_SET_NAME,"
                                    "IWF_SIGTRAN_ASSOCIATION_TB.ASP_ID,"
                                    "IWF_SIGTRAN_ASSOCIATION_TB.IWF_SIGTRAN_ASSOC_ID,"
                                    "IWF_SIGTRAN_ASSOCIATION_TB.IWF_SIGTRAN_ASSOC_NAME,"
                                    "IWF_SIGTRAN_ASSOCIATION_TB.IWF_SIGTRAN_SCTP_PROFILE_ID,"
                                    "IWF_SIGTRAN_ASSOCIATION_TB.IWF_LOCAL_SCTP_ENDPOINT_ID,"
                                    "IWF_SIGTRAN_ASSOCIATION_TB.IWF_REMOTE_SCTP_ENDPOINT_ID,"
                                    "IWF_SIGTRAN_ASSOC_SET_MAPPING_TB.IWF_SIGTRAN_ASSOC_SET_MAPPING_ID"
                                    " from IWF_SIGTRAN_ASSOC_SET_MAPPING_TB"
                                    " inner join IWF_SIGTRAN_ASSOC_SET_TB on IWF_SIGTRAN_ASSOC_SET_TB.IWF_SIGTRAN_ASSOC_SET_ID = IWF_SIGTRAN_ASSOC_SET_MAPPING_TB.IWF_SIGTRAN_ASSOC_SET_ID"
                                    " inner join IWF_SIGTRAN_ASSOCIATION_TB on IWF_SIGTRAN_ASSOCIATION_TB.IWF_SIGTRAN_ASSOC_ID = IWF_SIGTRAN_ASSOC_SET_MAPPING_TB.IWF_SIGTRAN_ASSOC_ID ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");


    if(pIwfSigtranAssociationSetConfig->has_associationsetid())   
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_TB.IWF_SIGTRAN_ASSOC_SET_ID=%d and ",pIwfSigtranAssociationSetConfig->associationsetid());
    }

    if(pIwfSigtranAssociationSetConfig->has_associationsetname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_ASSOC_SET_TB.IWF_SIGTRAN_ASSOC_SET_NAME='%s' and ",pIwfSigtranAssociationSetConfig->associationsetname().c_str());
    }

    if(iFlag == 1)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s \n",__FUNCTION__); 
}

