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

void PeerGroupMapTPBQuery::sql_PeerGroupMap_Create_Validation_Query_for_Peer(LBPeerGroup *lbPeerGroupConfigReq,char *pStatement,int iIndex)
{

    DLOG_NONE(" > %s \n",__FUNCTION__);
    ::LBPeer *pLBPeer =  NULL;

    DLOG_DEBUG("lbPeerGroupConfigReq->lbpeers_size() = %d, iIndex= %d",lbPeerGroupConfigReq->lbpeers_size(),iIndex);    

    if(lbPeerGroupConfigReq->lbpeers_size() > iIndex && iIndex > -1)
    {
        pLBPeer = lbPeerGroupConfigReq->mutable_lbpeers(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s'",pLBPeer->lbpeername().c_str(),pLBPeer->lbpeerrealm().c_str());
    DLOG_NONE(" < %s \n",__FUNCTION__);
}

void PeerGroupMapTPBQuery::sql_PeerGroupMap_Create_Validation_Query_for_PeerGroup(LBPeerGroup *lbPeerGroupConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s \n",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PEER_GRP_ID from PEER_GRP_TB where PEER_GRP_NAME = '%s'",lbPeerGroupConfigReq->lbpeergroupname().c_str());

    DLOG_NONE(" < %s \n",__FUNCTION__);
}

void PeerGroupMapTPBQuery::sql_PeerGroupMap_Create_Check_Modifcation_Query(LBPeerGroup *lbPeerGroupConfigReq,char *pStatement,int iIndex)
{

    ::LBPeer *pLBPeer =  NULL;


    DLOG_DEBUG("lbPeerGroupConfigReq->lbpeers_size() = %d, iIndex= %d",lbPeerGroupConfigReq->lbpeers_size(),iIndex);    

    if(lbPeerGroupConfigReq->lbpeers_size() > iIndex && iIndex > -1)
    {
        pLBPeer = lbPeerGroupConfigReq->mutable_lbpeers(iIndex);
    }
    else
    {
        DLOG_WARNING("LBPeer Object will be NULL, lbPeerGroupConfigReq->lbpeers_size() = %d, iIndex= %d",lbPeerGroupConfigReq->lbpeers_size(),iIndex);    
	    DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PEER_GRP_MAP_ID from PEER_GRP_MAP_TB where PEER_GRP_MAP_TB.PEER_ID=(select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s') and PEER_GRP_MAP_TB.PEER_GRP_ID=(select PEER_GRP_TB.PEER_GRP_ID from PEER_GRP_TB where PEER_GRP_TB.PEER_GRP_NAME= '%s')",pLBPeer->lbpeername().c_str(),pLBPeer->lbpeerrealm().c_str(),lbPeerGroupConfigReq->lbpeergroupname().c_str());
}

void PeerGroupMapTPBQuery::sql_PeerGroupMap_Create_Add_Query(LBPeerGroup *lbPeerGroupConfigReq,char *pStatement,int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    ::LBPeer *pLBPeer =  NULL;

    DLOG_NONE(" > %s \n",__FUNCTION__);
    DLOG_DEBUG("lbPeerGroupConfigReq->lbpeers_size() = %d, iIndex= %d",lbPeerGroupConfigReq->lbpeers_size(),iIndex);    

    if(lbPeerGroupConfigReq->lbpeers_size() > iIndex && iIndex > -1)
    {
        pLBPeer = lbPeerGroupConfigReq->mutable_lbpeers(iIndex);
    }

    else
    {
        DLOG_WARNING("LBPeer Object will be NULL, lbPeerGroupConfigReq->lbpeers_size() = %d, iIndex= %d",lbPeerGroupConfigReq->lbpeers_size(),iIndex);    
	    DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into PEER_GRP_MAP_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(PEER_ID,PEER_GRP_ID");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"((select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s'),(select PEER_GRP_ID from PEER_GRP_TB where PEER_GRP_NAME = '%s')",pLBPeer->lbpeername().c_str(),pLBPeer->lbpeerrealm().c_str(),lbPeerGroupConfigReq->lbpeergroupname().c_str());

    if(lbPeerGroupConfigReq->lbpeers_size() && pLBPeer->has_lbpeerweight())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PEER_WEIGHT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",pLBPeer->lbpeerweight());
    }

    if(lbPeerGroupConfigReq->lbpeers_size() && pLBPeer->has_lbpeerpriority())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PEER_PRIORITY");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",pLBPeer->lbpeerpriority());
    }



    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s \n",__FUNCTION__);
}

void PeerGroupMapTPBQuery::sql_PeerGroupMap_Create_Mod_Query(LBPeerGroup *lbPeerGroupConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s \n",__FUNCTION__);

    ::LBPeer *pLBPeer =  NULL;
    DLOG_DEBUG("lbPeerGroupConfigReq->lbpeers_size() = %d, iIndex= %d",lbPeerGroupConfigReq->lbpeers_size(),iIndex);    

    if(lbPeerGroupConfigReq->lbpeers_size() > iIndex && iIndex > -1)
    {
        pLBPeer = lbPeerGroupConfigReq->mutable_lbpeers(iIndex);
    }
    else
    {
        DLOG_WARNING("LBPeer Object will be NULL, lbPeerGroupConfigReq->lbpeers_size() = %d, iIndex= %d",lbPeerGroupConfigReq->lbpeers_size(),iIndex);    
	    DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update PEER_GRP_MAP_TB set "); 

    if(lbPeerGroupConfigReq->lbpeers_size() && pLBPeer->has_lbpeerweight())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PEER_WEIGHT=%d,",pLBPeer->lbpeerweight());

    }

    if(lbPeerGroupConfigReq->lbpeers_size() && pLBPeer->has_lbpeerpriority())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PEER_PRIORITY=%d,",pLBPeer->lbpeerpriority());
    }


    if(lbPeerGroupConfigReq->has_lbpeergroupname())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PEER_GRP_MAP_TB.PEER_GRP_ID=(select PEER_GRP_TB.PEER_GRP_ID from PEER_GRP_TB where PEER_GRP_NAME = '%s'),",lbPeerGroupConfigReq->lbpeergroupname().c_str());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where PEER_ID=(select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s') and PEER_GRP_MAP_TB.PEER_GRP_ID=(select PEER_GRP_TB.PEER_GRP_ID from PEER_GRP_TB where PEER_GRP_NAME = '%s')",pLBPeer->lbpeername().c_str(),pLBPeer->lbpeerrealm().c_str(),lbPeerGroupConfigReq->lbpeergroupname().c_str());

    DLOG_NONE(" < %s \n",__FUNCTION__);

}

void PeerGroupMapTPBQuery::sql_PeerGroupMap_Create_Delete_Query(LBPeerGroup *lbPeerGroupConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s \n",__FUNCTION__);

    ::LBPeer *pLBPeer =  NULL;
    DLOG_DEBUG("lbPeerGroupConfigReq->lbpeers_size() = %d, iIndex= %d",lbPeerGroupConfigReq->lbpeers_size(),iIndex);    

    if(lbPeerGroupConfigReq->lbpeers_size() > iIndex && iIndex > -1)
    {
        pLBPeer = lbPeerGroupConfigReq->mutable_lbpeers(iIndex);
    }
    else
    {
        DLOG_WARNING("LBPeer Object will be NULL, lbPeerGroupConfigReq->lbpeers_size() = %d, iIndex= %d",lbPeerGroupConfigReq->lbpeers_size(),iIndex);    
	    DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from PEER_GRP_MAP_TB where PEER_ID=(select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s') and PEER_GRP_MAP_TB.PEER_GRP_ID=(select PEER_GRP_TB.PEER_GRP_ID from PEER_GRP_TB where PEER_GRP_NAME = '%s')",pLBPeer->lbpeername().c_str(),pLBPeer->lbpeerrealm().c_str(),lbPeerGroupConfigReq->lbpeergroupname().c_str()); 

    DLOG_NONE(" < %s \n",__FUNCTION__);
}

DbStatus_e PeerGroupMapTPBQuery::sql_PeerGroupMap_Payload_Validation(LBPeerGroup *lbPeerGroupConfigReq,int iIndex)
{

    if(!lbPeerGroupConfigReq->has_lbpeergroupname())
    {
        DLOG_ERROR("Primary Key PeerGroup Name is not set in the request");
        return ERR_PEERCONFIG_MANDATORY_PEERGROUP_MISSING;  
    }

    ::LBPeer *pLBPeer =  NULL;
    DLOG_DEBUG("lbPeerGroupConfigReq->lbpeers_size() = %d, iIndex= %d",lbPeerGroupConfigReq->lbpeers_size(),iIndex);    

    if(lbPeerGroupConfigReq->lbpeers_size() > iIndex && iIndex > -1)
    {
        pLBPeer = lbPeerGroupConfigReq->mutable_lbpeers(iIndex);
    }


    if(lbPeerGroupConfigReq->lbpeers_size() && !pLBPeer->has_lbpeername())
    {
        DLOG_ERROR("Primary Key PeerName is not set in the request");
        return ERR_PEERCONFIG_MANDATORY_PEER_MISSING;   
    }

    if(lbPeerGroupConfigReq->lbpeers_size() && !pLBPeer->has_lbpeerrealm())
    {
        DLOG_ERROR("Primary Key Realm is not set in the request");
        return ERR_PEERCONFIG_MANDATORY_REALM_MISSING;  
    }

    return DRE_DB_SUCCESS;
}


void PeerGroupMapTPBQuery::sql_PeerGroupMap_Create_Select_Query(LBPeerGroup *lbPeerGroupConfigReq,char *pStatement,int iIndex)
{
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    ::LBPeer *pLBPeer =  NULL;

    DLOG_NONE(" > %s \n",__FUNCTION__);

    DLOG_DEBUG("lbPeerGroupConfigReq->lbpeers_size() = %d, iIndex= %d",lbPeerGroupConfigReq->lbpeers_size(),iIndex);    

    if(lbPeerGroupConfigReq->lbpeers_size() > iIndex && iIndex > -1)
    {
        pLBPeer = lbPeerGroupConfigReq->mutable_lbpeers(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PEER_GRP_TB.PEER_GRP_NAME,PeerT.PeerHostIdentity,PeerT.RealmName,PEER_WEIGHT,PEER_PRIORITY from PEER_GRP_MAP_TB,PEER_GRP_TB,PeerT "); 


    if(lbPeerGroupConfigReq->has_lbpeergroupname())
    {
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PEER_GRP_TB.PEER_GRP_NAME='%s' and ",lbPeerGroupConfigReq->lbpeergroupname().c_str());
    }

    if(lbPeerGroupConfigReq->lbpeers_size() && pLBPeer->has_lbpeername())
    {
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PeerT.PeerHostIdentity='%s' and ",pLBPeer->lbpeername().c_str());
    }

    if(lbPeerGroupConfigReq->lbpeers_size() && pLBPeer->has_lbpeerrealm())
    {
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PeerT.RealmName='%s' and ",pLBPeer->lbpeerrealm().c_str());
    }

    if(lbPeerGroupConfigReq->lbpeers_size() && pLBPeer->has_lbpeerweight())
    {
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PEER_GRP_MAP_TB.PEER_WEIGHT='%d' and ",pLBPeer->lbpeerweight());
    }

    if(lbPeerGroupConfigReq->lbpeers_size() && pLBPeer->has_lbpeerpriority())
    {
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PEER_GRP_MAP_TB.PEER_PRIORITY='%d' and ",pLBPeer->lbpeerpriority());
    }



    sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);

    DLOG_NONE(" < %s \n",__FUNCTION__);
}

DbStatus_e PeerGroupMapTPBQuery::sql_PeerGroupMap_Check_All_Invalid(LBPeerGroup *lbPeerGroupConfigReq,int iIndex)
{

    ::LBPeer *pLBPeer =  NULL;

    DLOG_DEBUG("lbPeerGroupConfigReq->lbpeers_size() = %d, iIndex= %d",lbPeerGroupConfigReq->lbpeers_size(),iIndex);    

    if(lbPeerGroupConfigReq->lbpeers_size() > iIndex && iIndex > -1)
    {
        pLBPeer = lbPeerGroupConfigReq->mutable_lbpeers(iIndex);
    }

    if(lbPeerGroupConfigReq->has_lbpeergroupname())
    {
        return DRE_DB_FAIL;
    }   

    if(lbPeerGroupConfigReq->lbpeers_size() && pLBPeer->has_lbpeerweight())
    {
        return DRE_DB_FAIL;
    }

    if(lbPeerGroupConfigReq->lbpeers_size() && pLBPeer->has_lbpeerpriority())
    {
        return DRE_DB_FAIL;
    }


    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}


