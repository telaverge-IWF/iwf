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

void ASFTAndLbAlgoPBQuery::sql_ASFLbAlgo_Create_Select_Query(ASGroupCfg *AsGroupReq,char *pStatement)
{

//    snprintf(pStatement,MAX_STATEMENT_SIZE,"select APPLICATION_GRP_TB.APP_GRP_ID,APPLICATION_GRP_TB.APP_GRP_NAME,APPLICATION_GRP_TB.PRIORITY,APPLICATION_GRP_TB.IS_HOSTED_APP_GRP,APPLICATION_GRP_TB.MAX_APP_INSTANCES,a.UserName as CREATED_BY,APPLICATION_GRP_TB.CREATION_TIME,b.UserName as MODIFIED_BY,APPLICATION_GRP_TB.MODIFICATION_TIME,LB_ALGORITHM_TB.LB_METHOD FROM APPLICATION_GRP_TB inner join LB_ALGORITHM_TB on APPLICATION_GRP_TB.LB_METHOD_ID = LB_ALGORITHM_TB.LB_METHOD_ID join UserT a on APPLICATION_GRP_TB.CREATED_BY = a.UserID join UserT b on APPLICATION_GRP_TB.MODIFIED_BY = b.UserID and ");
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select APPLICATION_GRP_TB.APP_GRP_ID,APPLICATION_GRP_TB.APP_GRP_NAME,APPLICATION_GRP_TB.PRIORITY,APPLICATION_GRP_TB.IS_HOSTED_APP_GRP,APPLICATION_GRP_TB.MAX_APP_INSTANCES,LB_ALGORITHM_TB.LB_METHOD FROM APPLICATION_GRP_TB inner join LB_ALGORITHM_TB on APPLICATION_GRP_TB.LB_METHOD_ID = LB_ALGORITHM_TB.LB_METHOD_ID and ");
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(AsGroupReq->has_appgroupid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"APP_GRP_ID=%d and",AsGroupReq->appgroupid());
    }
    
    if(AsGroupReq->has_appgroup())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"APP_GRP_NAME='%s' and ",AsGroupReq->appgroup().c_str());
    }

    if(AsGroupReq->has_priority())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PRIORITY=%d and ",AsGroupReq->priority());
    }

    if(AsGroupReq->has_ishostedapp())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IS_HOSTED_APP_GRP=%d and ",AsGroupReq->ishostedapp());
    }

    if(AsGroupReq->has_maxappinstances())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MAX_APP_INSTANCES=%d and ",AsGroupReq->maxappinstances());
    }

    if(AsGroupReq->has_createdby())
    {   
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"CREATED_BY = (select UserID from UserT where Username = '%s') and",AsGroupReq->createdby().c_str());
    }   

    if(AsGroupReq->has_creationdate())
    {   
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"CREATION_TIME='%s' and",AsGroupReq->creationdate().c_str());
    }   

    if(AsGroupReq->has_modifiedby())
    {   
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MODIFIED_BY = (select UserID from UserT where Username = '%s') and",AsGroupReq->modifiedby().c_str());
    }   

    if(AsGroupReq->has_modifytime())
    {   
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MODIFICATION_TIME='%s' and",AsGroupReq->modifytime().c_str());
    }   

    if(AsGroupReq->has_lbalgo())
    {
        ::LBAlgorithm* localLBAlogrithm = AsGroupReq->mutable_lbalgo();
        if(localLBAlogrithm->has_lbmethod())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LB_ALGORITHM_TB.LB_METHOD='%s' and ",localLBAlogrithm->lbmethod().c_str());
        }
    }
    pStatement[strlen(pStatement) - REMOVE_FOUR_CHARATERS] = '\0';


    DLOG_NONE(" < %s ",__FUNCTION__);

}


