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

void IWFDccaEndPointsTPBQuery::sql_DccaEndPoint_Create_Validation_Query_for_Realm(IwfDccaDestConfig *pIwfDccaDestConfig,char *pStatement)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	if(pIwfDccaDestConfig->has_destname())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," select REALM_ID from REALM_TB where REALM_NAME='%s'",pIwfDccaDestConfig->destname().c_str());
	}

	DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFDccaEndPointsTPBQuery::sql_DccaEndPoint_Create_Check_Modifcation_Query(IwfDccaDestConfig *pIwfDccaDestConfig,char *pStatement)
{
	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	DLOG_NONE(" > %s ",__FUNCTION__);

	::IwfDccaEndPointConfig* localEndPointObj=NULL;


    DLOG_DEBUG("pIwfDccaDestConfig->iwfdccaendpoints_size() = %d",pIwfDccaDestConfig->iwfdccaendpoints_size());    

	if(pIwfDccaDestConfig->iwfdccaendpoints_size())
    {
		localEndPointObj = pIwfDccaDestConfig->mutable_iwfdccaendpoints(0);
    }

	snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_DCCA_ENDPOINT_ID from IWF_DCCA_ENDPOINTS_TB ");
	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

	if(pIwfDccaDestConfig->iwfdccaendpoints_size() && localEndPointObj->has_endpointname())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ENDPOINT_NAME = '%s' and ",localEndPointObj->endpointname().c_str());
	}

	if(pIwfDccaDestConfig->has_destname())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"DEST_REALM_ID=(select REALM_ID from REALM_TB where REALM_NAME='%s') and ",pIwfDccaDestConfig->destname().c_str());
	}
	
	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
	}


	DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFDccaEndPointsTPBQuery::sql_DccaEndPoint_Create_Add_Query(IwfDccaDestConfig *pIwfDccaDestConfig,char *pStatement)
{
	char sFieldName[MAX_STATEMENT_SIZE]	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	DLOG_NONE(" > %s ",__FUNCTION__);
    ::IwfDccaEndPointConfig* localEndPointObj=NULL;


    DLOG_DEBUG("pIwfDccaDestConfig->iwfdccaendpoints_size() = %d",pIwfDccaDestConfig->iwfdccaendpoints_size());    

	if(pIwfDccaDestConfig->iwfdccaendpoints_size())
    {
		localEndPointObj = pIwfDccaDestConfig->mutable_iwfdccaendpoints(0);
    }
    
	snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_DCCA_ENDPOINTS_TB");
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");


    if(pIwfDccaDestConfig->has_destname())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"DEST_REALM_ID,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"(select REALM_ID from REALM_TB where REALM_NAME='%s'),",pIwfDccaDestConfig->destname().c_str());
    }

    if(pIwfDccaDestConfig->iwfdccaendpoints_size() && localEndPointObj->has_endpointname())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"ENDPOINT_NAME,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",localEndPointObj->endpointname().c_str());
    }

    if(pIwfDccaDestConfig->iwfdccaendpoints_size() && localEndPointObj->has_priority())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"PRIORITY,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",localEndPointObj->priority());
    }
    
    if(pIwfDccaDestConfig->has_sendccrtindicator())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"SEND_CCRT_INDICATOR,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pIwfDccaDestConfig->sendccrtindicator());
    }
    
    sFieldName[strlen(sFieldName) -1] = ' ';
    sFieldValue[strlen(sFieldValue) -1] = ' ';
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");


	snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);
	DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFDccaEndPointsTPBQuery::sql_DccaEndPoint_Create_Modify_Query(IwfDccaDestConfig *pIwfDccaDestConfig,char *pStatement)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_DCCA_ENDPOINTS_TB set ");

    if(pIwfDccaDestConfig->has_sendccrtindicator())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SEND_CCRT_INDICATOR=%d,",pIwfDccaDestConfig->sendccrtindicator());
    }
 
    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," where DEST_REALM_ID=(select REALM_ID from REALM_TB where REALM_NAME='%s') ",pIwfDccaDestConfig->destname().c_str());

	DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFDccaEndPointsTPBQuery::sql_DccaEndPoint_Create_Delete_Query(IwfDccaDestConfig *pIwfDccaDestConfig,char *pStatement)
{
	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	DLOG_NONE(" > %s ",__FUNCTION__);
    ::IwfDccaEndPointConfig* localEndPointObj=NULL;

    DLOG_DEBUG("pIwfDccaDestConfig->iwfdccaendpoints_size() = %d",pIwfDccaDestConfig->iwfdccaendpoints_size());    

	if(pIwfDccaDestConfig->iwfdccaendpoints_size())
    {
		localEndPointObj = pIwfDccaDestConfig->mutable_iwfdccaendpoints(0);
    }

	snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_DCCA_ENDPOINTS_TB"); 
	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pIwfDccaDestConfig->has_destname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"DEST_REALM_ID=(select REALM_ID from REALM_TB where REALM_NAME='%s') and ",pIwfDccaDestConfig->destname().c_str());
    }
	
    if(pIwfDccaDestConfig->iwfdccaendpoints_size() && localEndPointObj->has_endpointname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ENDPOINT_NAME='%s' and ",localEndPointObj->endpointname().c_str());
    }

    if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
	}

	DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFDccaEndPointsTPBQuery::sql_DccaEndPoint_Create_Select_Query(IwfDccaDestConfig *pIwfDccaDestConfig,char *pStatement)
{
	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	DLOG_NONE(" > %s ",__FUNCTION__);
    ::IwfDccaEndPointConfig* localEndPointObj=NULL;

    DLOG_DEBUG("pIwfDccaDestConfig->iwfdccaendpoints_size() = %d",pIwfDccaDestConfig->iwfdccaendpoints_size());    

	if(pIwfDccaDestConfig->iwfdccaendpoints_size())
    {
		localEndPointObj = pIwfDccaDestConfig->mutable_iwfdccaendpoints(0);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_DCCA_ENDPOINTS_TB");
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pIwfDccaDestConfig->has_destname())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"DEST_REALM_ID=(select REALM_TB.REALM_ID from REALM_TB where REALM_NAME='%s') and ",pIwfDccaDestConfig->destname().c_str());
	}

    if(pIwfDccaDestConfig->iwfdccaendpoints_size() && localEndPointObj->has_endpointname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ENDPOINT_NAME='%s' and ",localEndPointObj->endpointname().c_str());
    }

    if(pIwfDccaDestConfig->iwfdccaendpoints_size() && localEndPointObj->has_priority())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PRIORITY=%d and ",localEndPointObj->priority());
    }

	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
	}

	DLOG_NONE(" < %s ",__FUNCTION__);
}
