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


#include <CMgrDbInterface.h>

using namespace std;

void PeerGroupTPBQuery::sql_PeerGroup_Create_Validation_Query_for_Lbalgo(LBPeerGroup *lbPeerGroupConfigReq,char *pStatement)
{

    ::LBAlgorithm* pLBAlgorithm = lbPeerGroupConfigReq->mutable_lbalgo();
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select LB_ALGORITHM_TB.LB_METHOD_ID from LB_ALGORITHM_TB where LB_METHOD = '%s'",pLBAlgorithm->lbmethod().c_str()); 
}


void PeerGroupTPBQuery::sql_PeerGroup_Create_Check_Modifcation_Query(LBPeerGroup *lbPeerGroupConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PEER_GRP_ID from PEER_GRP_TB where PEER_GRP_NAME='%s'",lbPeerGroupConfigReq->lbpeergroupname().c_str()); 
}

void PeerGroupTPBQuery::sql_PeerGroup_Create_Add_Query(LBPeerGroup *lbPeerGroupConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  


    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into PEER_GRP_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(PEER_GRP_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",lbPeerGroupConfigReq->lbpeergroupname().c_str());

    if(lbPeerGroupConfigReq->has_lbpeergroupid())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PEER_GRP_ID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",lbPeerGroupConfigReq->lbpeergroupid());
    }
    if(lbPeerGroupConfigReq->has_enablepcrfbinding())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ENABLE_PCRF_BINDING");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",lbPeerGroupConfigReq->enablepcrfbinding());
    }

    if(lbPeerGroupConfigReq->has_lbalgo())
    {
        ::LBAlgorithm* pLBAlgorithm = lbPeerGroupConfigReq->mutable_lbalgo();
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",LB_METHOD_ID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select LB_ALGORITHM_TB.LB_METHOD_ID from LB_ALGORITHM_TB where LB_METHOD = '%s')",pLBAlgorithm->lbmethod().c_str());
    }



    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void PeerGroupTPBQuery::sql_PeerGroup_Create_Mod_Query(LBPeerGroup *lbPeerGroupConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);


    snprintf(pStatement,MAX_STATEMENT_SIZE,"update PEER_GRP_TB set "); 

    if(lbPeerGroupConfigReq->has_enablepcrfbinding())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ENABLE_PCRF_BINDING=%d,",lbPeerGroupConfigReq->enablepcrfbinding());

    }

    if(lbPeerGroupConfigReq->has_lbalgo())
    {
        ::LBAlgorithm* pLBAlgorithm = lbPeerGroupConfigReq->mutable_lbalgo();
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PEER_GRP_TB.LB_METHOD_ID=(select LB_ALGORITHM_TB.LB_METHOD_ID from LB_ALGORITHM_TB where LB_METHOD = '%s'),",pLBAlgorithm->lbmethod().c_str());

    }


    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where PEER_GRP_NAME='%s'",lbPeerGroupConfigReq->lbpeergroupname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);

}

void PeerGroupTPBQuery::sql_PeerGroup_Create_Delete_Query(LBPeerGroup *lbPeerGroupConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from PEER_GRP_TB where PEER_GRP_NAME='%s'",lbPeerGroupConfigReq->lbpeergroupname().c_str()); 

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e PeerGroupTPBQuery::sql_PeerGroup_Payload_Validation(LBPeerGroup *lbPeerGroupConfigReq)
{
    if(!lbPeerGroupConfigReq->has_lbpeergroupname())
    {
        DLOG_ERROR("Primary Key PeerGroup is not set in the request");
        return ERR_PEERGROUP_MANDATORY_PEERGROUPNAME_MISSING;   
    }
#if  0
    if(!lbPeerGroupConfigReq->has_lbalgo())
    {
        return DRE_DB_FAIL; 
    }
    else
    {
        ::LBAlgorithm *pLBAlgorithm = lbPeerGroupConfigReq->mutable_lbalgo();
        if(!pLBAlgorithm->has_lbmethod())
        {
            return DRE_DB_FAIL;
        }
    }
#endif

    return DRE_DB_SUCCESS;
}


void PeerGroupTPBQuery::sql_PeerGroup_Create_Select_Query(LBPeerGroup *lbPeerGroupConfigReq,char *pStatement)
{
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PEER_GRP_ID,PEER_GRP_NAME,ENABLE_PCRF_BINDING,LB_ALGORITHM_TB.LB_METHOD from PEER_GRP_TB,LB_ALGORITHM_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where LB_ALGORITHM_TB.LB_METHOD_ID = PEER_GRP_TB.LB_METHOD_ID and ");


    if(lbPeerGroupConfigReq->has_lbpeergroupname())
    {
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PEER_GRP_NAME='%s' and ",lbPeerGroupConfigReq->lbpeergroupname().c_str());
    }

    if(lbPeerGroupConfigReq->has_enablepcrfbinding())
    {
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ENABLE_PCRF_BINDING=%d and ",lbPeerGroupConfigReq->enablepcrfbinding());

    }

    if(lbPeerGroupConfigReq->has_lbalgo())
    {
        ::LBAlgorithm *pLBAlgorithm = lbPeerGroupConfigReq->mutable_lbalgo();
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PEER_GRP_TB.LB_METHOD_ID=(select LB_ALGORITHM_TB.LB_METHOD_ID from LB_ALGORITHM_TB where LB_METHOD = '%s') and ",pLBAlgorithm->lbmethod().c_str());

    }


    sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e PeerGroupTPBQuery::sql_PeerGroup_Check_All_Invalid(LBPeerGroup *lbPeerGroupConfigReq)
{
    ::LBAlgorithm *pLBAlgorithm = lbPeerGroupConfigReq->mutable_lbalgo();

    if(lbPeerGroupConfigReq->has_enablepcrfbinding())
    {
        return DRE_DB_FAIL;
    }   

    if(pLBAlgorithm->has_lbmethod())
    {
        return DRE_DB_FAIL;
    }

    if(pLBAlgorithm->has_lbmethoddesc())
    {
        return DRE_DB_FAIL;
    }


    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
