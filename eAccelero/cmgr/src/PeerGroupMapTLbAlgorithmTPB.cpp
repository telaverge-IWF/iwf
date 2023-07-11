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

void PeerGroupMapAndPeerGrpAndLbAlgorithmTPBQuery::sql_PeerGroupMapAndPeerGrpAndAlgorithm_Create_Select_Query(LBPeerGroup *LbPeerGroupReq,char *pStatement)
{

    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    int iFlag                   = 0;

    DLOG_NONE(" > %s \n",__FUNCTION__); 

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PEER_GRP_TB.PEER_GRP_NAME,"
                                "PEER_GRP_TB.PEER_GRP_ID,"
                                "LB_ALGORITHM_TB.LB_METHOD,"
                                "LB_ALGORITHM_TB.DESCRIPTION,"
                                "PEER_GRP_TB.ENABLE_PCRF_BINDING,"
                                "PEER_GRP_MAP_TB.PEER_WEIGHT,"
                                "PEER_GRP_MAP_TB.PEER_PRIORITY,"
                                "PeerT.PeerHostIdentity,"
                                "PeerT.RealmName,"
                                "PeerT.PeerID"
                                " from PEER_GRP_TB"
                                " left join PEER_GRP_MAP_TB on PEER_GRP_MAP_TB.PEER_GRP_ID = PEER_GRP_TB.PEER_GRP_ID"
                                " left join PeerT on PEER_GRP_MAP_TB.PEER_ID = PeerT.PeerID"
                                " left join LB_ALGORITHM_TB on PEER_GRP_TB.LB_METHOD_ID = LB_ALGORITHM_TB.LB_METHOD_ID "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");



    if(LbPeerGroupReq->has_lbpeergroupname())   
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PEER_GRP_TB.PEER_GRP_NAME='%s' and ",LbPeerGroupReq->lbpeergroupname().c_str());
    }

    if(LbPeerGroupReq->has_enablepcrfbinding()) 
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PEER_GRP_TB.ENABLE_PCRF_BINDING ='%d' and ",LbPeerGroupReq->enablepcrfbinding());
    }

    if(LbPeerGroupReq->has_lbalgo())    
    {

        LBAlgorithm* localLBAlogrithm = LbPeerGroupReq->mutable_lbalgo();

        if(localLBAlogrithm->has_lbmethod())
        {   
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LB_ALGORITHM_TB.LB_METHOD ='%s' and ",localLBAlogrithm->lbmethod().c_str());
        }
    }

    if(iFlag == 1)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s \n",__FUNCTION__); 
}

