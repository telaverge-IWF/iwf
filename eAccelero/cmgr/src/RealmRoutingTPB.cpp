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

void RealmRoutingTPBQuery::sql_RealmRouting_Create_Validation_Query_for_Realm(RealmConfig *RealmRoutingConfigReq,char *pStatement,int iDestinationIndex)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	::Destination* localDestinationObj=NULL;

    DLOG_DEBUG("RealmRoutingConfigReq->destinfo_size() = %d, iDestinationIndex= %d",RealmRoutingConfigReq->destinfo_size(),iDestinationIndex);    
	if(RealmRoutingConfigReq->destinfo_size() > iDestinationIndex && iDestinationIndex > -1)
    {
		localDestinationObj = RealmRoutingConfigReq->mutable_destinfo(iDestinationIndex);
    }

	if(RealmRoutingConfigReq->destinfo_size() && localDestinationObj->has_realmname())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," select REALM_ID from REALM_TB where REALM_NAME='%s'",RealmRoutingConfigReq->realmname().c_str());
	}

	DLOG_NONE(" < %s ",__FUNCTION__);
}
void RealmRoutingTPBQuery::sql_RealmRouting_Create_Validation_Query_for_Peer(RealmConfig *RealmRoutingConfigReq,char *pStatement,int iDestinationIndex)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	::Destination* localDestinationObj=NULL;

    DLOG_DEBUG("RealmRoutingConfigReq->destinfo_size() = %d, iDestinationIndex= %d",RealmRoutingConfigReq->destinfo_size(),iDestinationIndex);    
	if(RealmRoutingConfigReq->destinfo_size() > iDestinationIndex && iDestinationIndex > -1)
    {
		localDestinationObj = RealmRoutingConfigReq->mutable_destinfo(iDestinationIndex);
    }

	if(RealmRoutingConfigReq->destinfo_size() && localDestinationObj->has_peername())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s'",localDestinationObj->peername().c_str(),localDestinationObj->realmname().c_str());
	}

	DLOG_NONE(" < %s ",__FUNCTION__);
}

void RealmRoutingTPBQuery::sql_RealmRouting_Create_Check_Modifcation_Query(RealmConfig *RealmRoutingConfigReq,char *pStatement,int iDestinationIndex)
{
	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	DLOG_NONE(" > %s ",__FUNCTION__);

	::Destination* localDestinationObj=NULL;


    DLOG_DEBUG("RealmRoutingConfigReq->destinfo_size() = %d, iDestinationIndex= %d",RealmRoutingConfigReq->destinfo_size(),iDestinationIndex);    

	if(RealmRoutingConfigReq->destinfo_size() > iDestinationIndex && iDestinationIndex > -1)
    {
		localDestinationObj = RealmRoutingConfigReq->mutable_destinfo(iDestinationIndex);
    }

	snprintf(pStatement,MAX_STATEMENT_SIZE,"select APP_ID from REALM_ROUTING_TB ");
	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

	if(RealmRoutingConfigReq->destinfo_size() && localDestinationObj->has_applicationid())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"APP_ID=%d and ",localDestinationObj->applicationid());
	}

	if(RealmRoutingConfigReq->destinfo_size() && localDestinationObj->has_peername())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PEER_ID=(select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s') and ",localDestinationObj->peername().c_str(),localDestinationObj->realmname().c_str());
	}

	if(RealmRoutingConfigReq->has_realmname())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REALM_ID=(select REALM_ID from REALM_TB where REALM_NAME='%s') and ",RealmRoutingConfigReq->realmname().c_str());
	}
	
	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
	}


	DLOG_NONE(" < %s ",__FUNCTION__);
}

void RealmRoutingTPBQuery::sql_RealmRouting_Create_Add_Query(RealmConfig *realmConfigReq,char *pStatement,int iDestinationIndex)
{
	char sFieldName[MAX_STATEMENT_SIZE]	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	DLOG_NONE(" > %s ",__FUNCTION__);
	::Destination* localDestinationObj=NULL;

    DLOG_DEBUG("RealmRoutingConfigReq->destinfo_size() = %d, iDestinationIndex= %d",realmConfigReq->destinfo_size(),iDestinationIndex);    
    
	if(realmConfigReq->destinfo_size() > iDestinationIndex && iDestinationIndex > -1)
	    localDestinationObj = realmConfigReq->mutable_destinfo(iDestinationIndex);
    else
    {
        DLOG_WARNING("Destination Object will be NULL, RealmRoutingConfigReq->destinfo_size() = %d, iDestinationIndex= %d",realmConfigReq->destinfo_size(),iDestinationIndex);    
	    DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

	snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into REALM_ROUTING_TB "); 
	snprintf(sFieldName,MAX_STATEMENT_SIZE,"(REALM_ID,APP_ID,PEER_ID");	
	snprintf(sFieldValue,MAX_STATEMENT_SIZE,"((select REALM_ID from REALM_TB where REALM_NAME='%s'),%d,(select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s')",realmConfigReq->realmname().c_str(),localDestinationObj->applicationid(),localDestinationObj->peername().c_str(),localDestinationObj->realmname().c_str());



	if(realmConfigReq->destinfo_size() && localDestinationObj->has_vendorid())
	{
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",VENDOR_ID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",localDestinationObj->vendorid());
	}

	if(realmConfigReq->destinfo_size() && localDestinationObj->has_priority())
	{
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PRIORITY");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",localDestinationObj->priority());
	}

	if(realmConfigReq->destinfo_size() && localDestinationObj->has_dynamicallydiscovered())
	{
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",DYNAMICALLY_DISCOVERED");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",localDestinationObj->dynamicallydiscovered());
	}

	if(realmConfigReq->destinfo_size() && localDestinationObj->has_dyndiscoveryexpiry())
	{
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",DYN_DISCOVERY_EXPIRY");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",localDestinationObj->dyndiscoveryexpiry());
	}



    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

	snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


	DLOG_NONE(" < %s ",__FUNCTION__);


}

void RealmRoutingTPBQuery::sql_RealmRouting_Create_Delete_Query(RealmConfig *realmRoutingConfigReq,char *pStatement,int iDestinationIndex)
{

	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	DLOG_NONE(" > %s ",__FUNCTION__);
	::Destination* localDestinationObj;

    DLOG_DEBUG("RealmRoutingConfigReq->destinfo_size() = %d, iDestinationIndex= %d",realmRoutingConfigReq->destinfo_size(),iDestinationIndex);    

	if(realmRoutingConfigReq->destinfo_size() > iDestinationIndex && iDestinationIndex > -1)
    {
		localDestinationObj = realmRoutingConfigReq->mutable_destinfo(iDestinationIndex);
    }

	snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from REALM_ROUTING_TB "); 
	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");
	

	if(realmRoutingConfigReq->destinfo_size() && localDestinationObj->has_applicationid())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"APP_ID=%d and ",localDestinationObj->applicationid());
	}

	if(realmRoutingConfigReq->destinfo_size() && localDestinationObj->has_peername())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PEER_ID=(select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s') and ",localDestinationObj->peername().c_str(),localDestinationObj->realmname().c_str());
	}

	if(realmRoutingConfigReq->has_realmname())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REALM_ID=(select REALM_ID from REALM_TB where REALM_NAME='%s') and ",realmRoutingConfigReq->realmname().c_str());
	}
	
	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
	}

	DLOG_NONE(" < %s ",__FUNCTION__);
}

void RealmRoutingTPBQuery::sql_RealmRouting_Create_Mod_Query(RealmConfig *realmRoutingConfigReq,char *pStatement,int iDestinationIndex)
{

	DLOG_NONE(" > %s ",__FUNCTION__);
	::Destination* localDestinationObj=NULL;

    DLOG_DEBUG("RealmRoutingConfigReq->destinfo_size() = %d, iDestinationIndex= %d",realmRoutingConfigReq->destinfo_size(),iDestinationIndex);    

	if(realmRoutingConfigReq->destinfo_size() > iDestinationIndex && iDestinationIndex > -1)
    {
        localDestinationObj = realmRoutingConfigReq->mutable_destinfo(iDestinationIndex);
    }
    else
    {
        DLOG_WARNING("Destination Object will be NULL, RealmRoutingConfigReq->destinfo_size() = %d, iDestinationIndex= %d",realmRoutingConfigReq->destinfo_size(),iDestinationIndex);    
	    DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

	snprintf(pStatement,MAX_STATEMENT_SIZE,"update REALM_ROUTING_TB set "); 

	if(realmRoutingConfigReq->destinfo_size() && localDestinationObj->has_vendorid())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"VENDOR_ID=%d,",localDestinationObj->vendorid());
	}


	if(realmRoutingConfigReq->destinfo_size() && localDestinationObj->has_priority())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PRIORITY=%d,",localDestinationObj->priority());
	}

	if(realmRoutingConfigReq->destinfo_size() && localDestinationObj->has_dynamicallydiscovered())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"DYNAMICALLY_DISCOVERED=%d,",localDestinationObj->dynamicallydiscovered());
	}

	if(realmRoutingConfigReq->destinfo_size() && localDestinationObj->has_dyndiscoveryexpiry())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"DYN_DISCOVERY_EXPIRY=%d,",localDestinationObj->dyndiscoveryexpiry());
	}


	pStatement[strlen(pStatement) -1] = ' ';

	snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where APP_ID=%d and REALM_ID=(select REALM_ID from REALM_TB where REALM_NAME='%s') and PEER_ID=(select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s')",localDestinationObj->applicationid(),realmRoutingConfigReq->realmname().c_str(),localDestinationObj->peername().c_str(),localDestinationObj->realmname().c_str());

	DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e RealmRoutingTPBQuery::sql_RealmRouting_Payload_Validation(RealmConfig *realmConfigReq,int iDestinationIndex)
{

	::Destination* localDestinationObj = NULL;

    DLOG_DEBUG("RealmRoutingConfigReq->destinfo_size() = %d, iDestinationIndex= %d",realmConfigReq->destinfo_size(),iDestinationIndex);    

    if(realmConfigReq->destinfo_size() > iDestinationIndex && iDestinationIndex > -1)
    {
	    localDestinationObj = realmConfigReq->mutable_destinfo(iDestinationIndex);
    }
    else
    {
	    DLOG_ERROR("Destionation object is NULL ");
        return ERR_DEST_MANDATORY_PARAM_APPID_MISSING; 
    }

	if(!localDestinationObj->has_applicationid())
	{
		DLOG_ERROR("Primary Key ApplicationID is not set in the request");
		return ERR_DEST_MANDATORY_PARAM_APPID_MISSING;	
	}
	else if (!realmConfigReq->has_realmname())
	{
		DLOG_ERROR("Primary Key Realm is not set in the request");
		return ERR_DEST_MANDATORY_PARAM_REALMNAME_MISSING;	
	}
	else if(!localDestinationObj->has_peername())
	{
		DLOG_ERROR("Primary Key PeerName is not set in the request");
		return ERR_DEST_MANDATORY_PARAM_PEERNAME_MISSING;	
	}

	return DRE_DB_SUCCESS;
}


void RealmRoutingTPBQuery::sql_RealmRouting_Create_Select_Query(RealmConfig *realmConfigReq,char *pStatement,int iDestinationIndex)
{
	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	::Destination* localDestinationObj = NULL;

    DLOG_DEBUG("RealmRoutingConfigReq->destinfo_size() = %d, iDestinationIndex= %d",realmConfigReq->destinfo_size(),iDestinationIndex);    

	if(realmConfigReq->destinfo_size() > iDestinationIndex && iDestinationIndex > -1)
    {
		localDestinationObj = realmConfigReq->mutable_destinfo(iDestinationIndex);
    }

	snprintf(pStatement,MAX_STATEMENT_SIZE,"select REALM_TB.REALM_NAME,"
                        "REALM_TB.REALM_ID,"
                        "REALM_TB.REDIRECT_HOST_USAGE,"
                        "REALM_TB.REDIRECT_MAX_CACHE_TIME,"
                        "REALM_TB.LOCAL_ACTION,"
                        "PEER_ID,"
                        "APP_ID,"
                        "VENDOR_ID,"
                        "PRIORITY,"
                        "DYNAMICALLY_DISCOVERED,"
                        "DYN_DISCOVERY_EXPIRY,"
                        "PeerT.PeerHostIdentity,"
                        "PeerT.RealmName"
                        " from REALM_ROUTING_TB"
                        " inner join REALM_TB on REALM_ROUTING_TB.REALM_ID = REALM_TB.REALM_ID"
                        " left join PeerT on REALM_ROUTING_TB.PEER_ID = PeerT.PeerID "); 

	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

	DLOG_NONE(" > %s ",__FUNCTION__);

	if(realmConfigReq->has_realmname())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REALM_TB.REALM_ID=(select REALM_TB.REALM_ID from REALM_TB where REALM_NAME='%s') and ",realmConfigReq->realmname().c_str());
	}

	if(realmConfigReq->destinfo_size() && localDestinationObj->has_applicationid())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"APP_ID=%d and ",localDestinationObj->applicationid());
	}

	if(realmConfigReq->destinfo_size() && localDestinationObj->has_peername())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PEER_ID=(select PeerID from PeerT where PeerHostIdentity='%s' and RealmName='%s') and ",localDestinationObj->peername().c_str(),localDestinationObj->realmname().c_str());
	}

	if(realmConfigReq->destinfo_size() && localDestinationObj->has_vendorid())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"VENDOR_ID=%d and ",localDestinationObj->vendorid());
	}

	if(realmConfigReq->destinfo_size() && localDestinationObj->has_priority())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PRIORITY=%d and ",localDestinationObj->priority());
	}

#if 0
	if(realmConfigReq->realmInfo.NodeDiscovery != INVALID_NUM)
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NodeDiscovery=%d and ",realmConfigReq->realmInfo.NodeDiscovery);
	}
#endif

	if(realmConfigReq->destinfo_size() && localDestinationObj->has_dynamicallydiscovered())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"DYNAMICALLY_DISCOVERED=%d and ",localDestinationObj->dynamicallydiscovered());
	}

	if(realmConfigReq->destinfo_size() && localDestinationObj->has_dyndiscoveryexpiry())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"DYN_DISCOVERY_EXPIRY=%d and ",localDestinationObj->dyndiscoveryexpiry());
	}

	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
	}


	DLOG_NONE(" < %s ",__FUNCTION__);

}

DbStatus_e RealmRoutingTPBQuery::sql_RealmRouting_Check_All_Invalid(RealmConfig *realmRoutingConfigReq,int iDestinationIndex)
{

    DLOG_DEBUG("RealmRoutingConfigReq->destinfo_size() = %d, iDestinationIndex= %d",realmRoutingConfigReq->destinfo_size(),iDestinationIndex);    

	::Destination* localDestinationObj = NULL;

    
	if(realmRoutingConfigReq->destinfo_size() > iDestinationIndex && iDestinationIndex > -1)
    {
	    localDestinationObj = realmRoutingConfigReq->mutable_destinfo(iDestinationIndex);
    }
    else
    {
        DLOG_WARNING("RealmRoutingConfigReq->destinfo_size() = %d, iDestinationIndex= %d",realmRoutingConfigReq->destinfo_size(),iDestinationIndex);    
        return DRE_DB_SUCCESS;
    }

   

	if(localDestinationObj->has_vendorid())
	{
		return DRE_DB_FAIL;
	}

	if(localDestinationObj->has_priority())
	{
		return DRE_DB_FAIL;
	}

#if 0
	if(realmRoutingConfigReq->realmInfo.NodeDiscovery != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

#endif

	if(localDestinationObj->has_dynamicallydiscovered())
	{
		return DRE_DB_FAIL;
	}

	if(localDestinationObj->has_dyndiscoveryexpiry())
	{
		return DRE_DB_FAIL;
	}


	DLOG_INFO("In the Request, No Fields are Set for Operation");
	return DRE_DB_SUCCESS;
}
