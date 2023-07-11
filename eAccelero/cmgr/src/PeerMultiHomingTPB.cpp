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
#include <CMAPICMgr.h>
#include <CMAPICommon.h>


using namespace std;

void PeerMultiHomingTPBQuery::sql_PeerMutiHoming_Create_Validation_Query_for_Peer(PeerConfig *drePeerConfigReq,char *pStatement,int iIndex)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement ,MAX_STATEMENT_SIZE,"select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s'",drePeerConfigReq->peerhostname().c_str(),drePeerConfigReq->realm().c_str());

	DLOG_NONE(" < %s ",__FUNCTION__);
}

void PeerMultiHomingTPBQuery::sql_PeerMultiHoming_Create_Check_Modifcation_Query(PeerConfig *drePeerConfigReq,char *pStatement,int iIndex)
{
    string *sSecondaryIp = NULL;

    DLOG_DEBUG("drePeerConfigReq->secondaryipaddr_size() = %d, iIndex= %d",drePeerConfigReq->secondaryipaddr_size(),iIndex);    

    if(drePeerConfigReq->secondaryipaddr_size() > iIndex && iIndex > -1)
    {
        sSecondaryIp = drePeerConfigReq->mutable_secondaryipaddr(iIndex);
    }
    else
    {
        DLOG_WARNING("secondary ip address will be NULL, drePeerConfigReq->secondaryipaddr_size() = %d, iIndex= %d",drePeerConfigReq->secondaryipaddr_size(),iIndex);    
        return; 
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PEER_MULTIHOMING_ID from  PEER_MULTIHOMING_TB "
                        "where "
                        "PEER_ID=(select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s') "
                        "and OTHERHOME_IPADDR='%s' ",
                        drePeerConfigReq->peerhostname().c_str(),
                        drePeerConfigReq->realm().c_str(),
                        sSecondaryIp->c_str());

}

void PeerMultiHomingTPBQuery::sql_PeerMultiHoming_Create_Add_Query(PeerConfig *drePeerConfigReq,char *pStatement,int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE]     = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  
    string *sSecondaryIp = NULL;

    DLOG_NONE("> %s",__FUNCTION__);
    DLOG_DEBUG("drePeerConfigReq->secondaryipaddr_size() = %d, iIndex= %d",drePeerConfigReq->secondaryipaddr_size(),iIndex);    

    if(drePeerConfigReq->secondaryipaddr_size() > iIndex && iIndex > -1)
    {
        sSecondaryIp = drePeerConfigReq->mutable_secondaryipaddr(iIndex);
    }
    else
    {
        DLOG_WARNING("secondary ip address will be NULL, drePeerConfigReq->secondaryipaddr_size() = %d, iIndex= %d",drePeerConfigReq->secondaryipaddr_size(),iIndex);    
        return; 
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into PEER_MULTIHOMING_TB "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(PEER_ID");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"((select PeerID from PeerT "
                        "where "
                        "PeerHostIdentity='%s' and RealmName = '%s')",
                        drePeerConfigReq->peerhostname().c_str(),
                        drePeerConfigReq->realm().c_str());

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",OTHERHOME_IPADDR");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",sSecondaryIp->c_str());

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE("< %s",__FUNCTION__);
}

void PeerMultiHomingTPBQuery::sql_PeerMultiHoming_Create_Mod_Query(PeerConfig *drePeerConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE("> %s",__FUNCTION__);
#if 0
    string *sSecondaryIp;


    if(drePeerConfigReq->secondaryipaddr_size())
        sSecondaryIp = drePeerConfigReq->mutable_secondaryipaddr(iIndex);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update PEER_MULTIHOMING_TB set "); 

    if(drePeerConfigReq->secondaryipaddr_size())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"OTHERHOME_IPADDR='%s',",sSecondaryIp->c_str());

    }

    pStatement[strlen(pStatement) -1] = ' ';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where PEER_ID=((select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s')",drePeerConfigReq->peerhostname().c_str(),drePeerConfigReq->realm().c_str());
#endif

    DLOG_NONE("< %s",__FUNCTION__);

}

void PeerMultiHomingTPBQuery::sql_PeerMultiHoming_Create_Delete_Query(PeerConfig *drePeerConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE("> %s",__FUNCTION__);
    string *sSecondaryIp = NULL;

    DLOG_DEBUG("drePeerConfigReq->secondaryipaddr_size() = %d, iIndex= %d",drePeerConfigReq->secondaryipaddr_size(),iIndex);    

    if(drePeerConfigReq->secondaryipaddr_size() > iIndex && iIndex > -1)
    {
        sSecondaryIp = drePeerConfigReq->mutable_secondaryipaddr(iIndex);
    }
    else
    {
        DLOG_WARNING("secondary ip address will be NULL, drePeerConfigReq->secondaryipaddr_size() = %d, iIndex= %d",drePeerConfigReq->secondaryipaddr_size(),iIndex);    
        return; 
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from PEER_MULTIHOMING_TB "
                        "where "
                        "PEER_ID=(select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s') "
                        "and OTHERHOME_IPADDR = '%s'",
                        drePeerConfigReq->peerhostname().c_str(),
                        drePeerConfigReq->realm().c_str(),
                        sSecondaryIp->c_str());

    DLOG_NONE("< %s",__FUNCTION__);
}

DbStatus_e PeerMultiHomingTPBQuery::sql_PeerMultiHoming_Payload_Validation(PeerConfig *drePeerConfigReq,int iIndex)
{

    if(!drePeerConfigReq->has_peerhostname())
    {   
        DLOG_ERROR("Primary Key Peer is not set in the request");
        return DRE_DB_FAIL; 
    }   

    if(!drePeerConfigReq->has_realm())
    {   
        DLOG_ERROR("Primary Key Realm is not set in the request");
        return DRE_DB_FAIL; 
    }   

    if(!drePeerConfigReq->secondaryipaddr_size())
    {
        DLOG_ERROR("Primary Key secondary key is not given");
        return DRE_DB_FAIL; 
    }

    return DRE_DB_SUCCESS;
}


void PeerMultiHomingTPBQuery::sql_PeerMultiHoming_Create_Select_Query(PeerConfig *drePeerConfigReq,char *pStatement,int iIndex)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PeerT.PeerHostIdentity,"
                        "PeerT.RealmName,"
                        "PEER_MULTIHOMING_TB.PEER_MULTIHOMING_ID,"
                        "OTHERHOME_IPADDR "
                        "from PEER_MULTIHOMING_TB,PeerT");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where PeerT.PeerID = PEER_MULTIHOMING_TB.PEER_ID and ");

    DLOG_NONE(" < %s ",__FUNCTION__);
    if(drePeerConfigReq->has_peerhostname() && drePeerConfigReq->has_realm())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PEER_ID=(select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s') and ",drePeerConfigReq->peerhostname().c_str(),drePeerConfigReq->realm().c_str());

    }

    sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    DLOG_NONE(" > %s ",__FUNCTION__);
}

DbStatus_e PeerMultiHomingTPBQuery::sql_PeerMultiHoming_Check_All_Invalid(PeerConfig *drePeerConfigReq,int iIndex)
{
    int iSecondaryIpCount = drePeerConfigReq->secondaryipaddr_size();

    if(iSecondaryIpCount > 0) 

        DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}

