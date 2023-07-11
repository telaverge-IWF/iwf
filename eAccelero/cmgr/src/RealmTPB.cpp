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

void RealmTPBQuery::sql_Realm_Create_Check_Modifcation_Query(RealmConfig *RealmConfigReq,char *pStatement)
{
	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	DLOG_NONE(" > %s ",__FUNCTION__);


	snprintf(pStatement,MAX_STATEMENT_SIZE,"select REALM_ID from REALM_TB ");
	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

	if(RealmConfigReq->has_realmname())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REALM_NAME='%s' and ",RealmConfigReq->realmname().c_str());
	}
	
	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
	}


	DLOG_NONE(" < %s ",__FUNCTION__);
}

void RealmTPBQuery::sql_Realm_Create_Add_Query(RealmConfig *realmConfigReq,char *pStatement)
{
	char sFieldName[MAX_STATEMENT_SIZE]	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	DLOG_NONE(" > %s ",__FUNCTION__);

	snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into REALM_TB "); 
	snprintf(sFieldName,MAX_STATEMENT_SIZE,"(REALM_NAME");	
	snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",realmConfigReq->realmname().c_str());


	if(realmConfigReq->has_localaction())
	{
		snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",LOCAL_ACTION");
		if(realmConfigReq->localaction() == "Local")
			snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",1");
		else if(realmConfigReq->localaction() == "Relay")
			snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",2");
		else if(realmConfigReq->localaction() == "Proxy")
			snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",3");
		else 
			snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",4");
	}


	if(realmConfigReq->has_redirecthostusage())
	{
		snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",REDIRECT_HOST_USAGE");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",realmConfigReq->redirecthostusage());
	}

	if(realmConfigReq->has_enableproxyinfoavp())
	{
		snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PROXY_INFO_AVP");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",realmConfigReq->enableproxyinfoavp());
	}


	if(realmConfigReq->has_redirectmaxcachetime())
	{
		snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",REDIRECT_MAX_CACHE_TIME");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",realmConfigReq->redirectmaxcachetime());
	}



	snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
	snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

	snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


	DLOG_NONE(" < %s ",__FUNCTION__);


}

void RealmTPBQuery::sql_Realm_Create_Delete_Query(RealmConfig *realmRoutingConfigReq,char *pStatement)
{

	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	DLOG_NONE(" > %s ",__FUNCTION__);


	snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from REALM_TB "); 
	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");
	
	if(realmRoutingConfigReq->has_realmname())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REALM_NAME='%s' and ",realmRoutingConfigReq->realmname().c_str());
	}
	
	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
	}

	DLOG_NONE(" < %s ",__FUNCTION__);
}

void RealmTPBQuery::sql_Realm_Create_Mod_Query(RealmConfig *realmRoutingConfigReq,char *pStatement)
{

	DLOG_NONE(" > %s ",__FUNCTION__);

	snprintf(pStatement,MAX_STATEMENT_SIZE,"update REALM_TB set "); 


	if(realmRoutingConfigReq->has_localaction())
	{
		if(realmRoutingConfigReq->localaction() == "Local")
			snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LOCAL_ACTION=1,");
		else if(realmRoutingConfigReq->localaction() == "Relay")
			snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LOCAL_ACTION=2,");
		else if(realmRoutingConfigReq->localaction() == "Proxy")
			snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LOCAL_ACTION=3,");
		else
			snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LOCAL_ACTION=4,");
	}

	if(realmRoutingConfigReq->has_redirecthostusage())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"REDIRECT_HOST_USAGE=%d,",realmRoutingConfigReq->redirecthostusage());
	}

	if(realmRoutingConfigReq->has_enableproxyinfoavp())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PROXY_INFO_AVP=%d,",realmRoutingConfigReq->enableproxyinfoavp());
	}

	if(realmRoutingConfigReq->has_redirectmaxcachetime())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"REDIRECT_MAX_CACHE_TIME=%d,",realmRoutingConfigReq->redirectmaxcachetime());
	}


	pStatement[strlen(pStatement) -1] = ' ';

	snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where REALM_NAME='%s'",realmRoutingConfigReq->realmname().c_str());

	DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e RealmTPBQuery::sql_Realm_Payload_Validation(RealmConfig *realmConfigReq)
{
	if (!realmConfigReq->has_realmname())
	{
		DLOG_ERROR("Primary Key Realm is not set in the request");
		return ERR_REALM_MANDATORY_PARAM_REALMNAME_MISSING;	
	}

	return DRE_DB_SUCCESS;
}


void RealmTPBQuery::sql_Realm_Create_Select_Query(RealmConfig *realmConfigReq,char *pStatement)
{
	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};

	snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from REALM_TB"); 

	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

	DLOG_NONE(" > %s ",__FUNCTION__);

    if(realmConfigReq->has_realmid())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REALM_ID=%d and ",realmConfigReq->realmid());
	}

	if(realmConfigReq->has_realmname())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REALM_NAME='%s' and ",realmConfigReq->realmname().c_str());
	}

	if(realmConfigReq->has_localaction())
	{
		iFlag = 1;
		if(realmConfigReq->localaction() == "Local")
			snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LOCAL_ACTION=1 and ");
		else if(realmConfigReq->localaction() == "Relay")
			snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LOCAL_ACTION=2 and ");
		else if(realmConfigReq->localaction() == "Proxy")
			snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LOCAL_ACTION=3 and ");
		else
			snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LOCAL_ACTION=4 and ");
	}

	if(realmConfigReq->has_enableproxyinfoavp())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PROXY_INFO_AVP=%d and ",realmConfigReq->enableproxyinfoavp());
	}

	if(realmConfigReq->has_redirecthostusage())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REDIRECT_HOST_USAGE=%d and ",realmConfigReq->redirecthostusage());
	}

	if(realmConfigReq->has_redirectmaxcachetime())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"REDIRECT_MAX_CACHE_TIME=%d and ",realmConfigReq->redirectmaxcachetime());
	}

	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
	}


	DLOG_NONE(" < %s ",__FUNCTION__);

}

DbStatus_e RealmTPBQuery::sql_Realm_Check_All_Invalid(RealmConfig *realmRoutingConfigReq)
{


	if(realmRoutingConfigReq->has_localaction())
	{
		return DRE_DB_FAIL;
	}

	if(realmRoutingConfigReq->has_redirecthostusage())
	{
		return DRE_DB_FAIL;
	}

	if(realmRoutingConfigReq->has_redirectmaxcachetime())
	{
		return DRE_DB_FAIL;
	}

	if(realmRoutingConfigReq->has_enableproxyinfoavp())
	{
		return DRE_DB_FAIL;
	}


	DLOG_INFO("In the Request, No Fields are Set for Operation");
	return DRE_DB_SUCCESS;
}
