#include <MysqlInterface.h>

using namespace std;

void RealmRoutingTQuery::sql_RealmRouting_Create_Check_Modifcation_Query(DreRealmRoutingPayload *RealmRoutingConfigReq,char *pStatement)
{

	sprintf(pStatement,"select ApplicationID from RealmRoutingT where RealmName='%s' and PeerHostIdentity='%s' and ApplicationID=%ld",RealmRoutingConfigReq->realmKeyInfo.RealmName,RealmRoutingConfigReq->realmKeyInfo.PeerHostId,RealmRoutingConfigReq->realmKeyInfo.AppId);

}

void RealmRoutingTQuery::sql_RealmRouting_Create_Add_Query(DreRealmRoutingPayload *realmConfigReq,char *pStatement)
{
	char sFieldName[MAX_STATEMENT_SIZE]	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"insert into RealmRoutingT "); 
	strcpy(sFieldName,"(RealmName,PeerHostIdentity,ApplicationID");	
	sprintf(sFieldValue,"('%s','%s',%ld",realmConfigReq->realmKeyInfo.RealmName,realmConfigReq->realmKeyInfo.PeerHostId,realmConfigReq->realmKeyInfo.AppId);

	if(realmConfigReq->realmInfo.LocalAction != INVALID_NUM)
	{
		strcat(sFieldName,",LocalAction");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",realmConfigReq->realmInfo.LocalAction);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(realmConfigReq->realmInfo.VendorID != INVALID_NUM)
        {
                strcat(sFieldName,",VendorID");
                sprintf(sFieldValue + strlen(sFieldValue),",%ld",realmConfigReq->realmInfo.VendorID);
        }
        PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	
	if(realmConfigReq->realmInfo.Priority != INVALID_NUM)
	{
		strcat(sFieldName,",Priority");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",realmConfigReq->realmInfo.Priority);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(realmConfigReq->realmInfo.NodeDiscovery != INVALID_NUM)
	{
		strcat(sFieldName,",NodeDiscovery");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",realmConfigReq->realmInfo.NodeDiscovery);
	}

	if(realmConfigReq->realmInfo.RedirectHostUsage != INVALID_NUM)
	{
		strcat(sFieldName,",RedirectHostUsage");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",realmConfigReq->realmInfo.RedirectHostUsage);
	}

	if(realmConfigReq->realmInfo.RedirectMaxCacheTime != INVALID_NUM)
	{
		strcat(sFieldName,",RedirectMaxCacheTime");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",realmConfigReq->realmInfo.RedirectMaxCacheTime);
	}



	strcat(sFieldName,")");
	strcat(sFieldValue,")");

	sprintf(pStatement + strlen(pStatement),"%s value %s",sFieldName,sFieldValue);


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);


}

void RealmRoutingTQuery::sql_RealmRouting_Create_Delete_Query(DreRealmRoutingPayload *realmConfigReq,char *pStatement)
{

	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"delete from RealmRoutingT ");

	sprintf(sWhereStatement,"where ");


	if(realmConfigReq->realmKeyInfo.RealmName[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"RealmName='%s' and ",realmConfigReq->realmKeyInfo.RealmName);
	}

	if(realmConfigReq->realmKeyInfo.PeerHostId[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"PeerHostIdentity='%s' and ",realmConfigReq->realmKeyInfo.PeerHostId);
	}

	if(realmConfigReq->realmKeyInfo.AppId != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"ApplicationID=%ld and ",realmConfigReq->realmKeyInfo.AppId);
	}



	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
		sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}

void RealmRoutingTQuery::sql_RealmRouting_Create_Mod_Query(DreRealmRoutingPayload *realmRoutingConfigReq,char *pStatement)
{

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"update RealmRoutingT set "); 

	if(realmRoutingConfigReq->realmInfo.LocalAction != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"LocalAction=%d,",realmRoutingConfigReq->realmInfo.LocalAction);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(realmRoutingConfigReq->realmInfo.VendorID != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"VendorID=%ld,",realmRoutingConfigReq->realmInfo.VendorID);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(realmRoutingConfigReq->realmInfo.Priority != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"Priority=%d,",realmRoutingConfigReq->realmInfo.Priority);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(realmRoutingConfigReq->realmInfo.NodeDiscovery != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"NodeDiscovery=%d,",realmRoutingConfigReq->realmInfo.NodeDiscovery);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(realmRoutingConfigReq->realmInfo.RedirectHostUsage != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"RedirectHostUsage=%d,",realmRoutingConfigReq->realmInfo.RedirectHostUsage);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(realmRoutingConfigReq->realmInfo.RedirectMaxCacheTime != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"RedirectMaxCacheTime=%d,",realmRoutingConfigReq->realmInfo.RedirectMaxCacheTime);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);


	pStatement[strlen(pStatement) -1] = ' ';

	sprintf(pStatement + strlen(pStatement),"where RealmName='%s' and PeerHostIdentity='%s' and ApplicationID=%ld",realmRoutingConfigReq->realmKeyInfo.RealmName,realmRoutingConfigReq->realmKeyInfo.PeerHostId,realmRoutingConfigReq->realmKeyInfo.AppId);

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}

DbStatus_e RealmRoutingTQuery::sql_RealmRouting_Payload_Validation(DreRealmRoutingPayload *realmConfigReq)
{
	if (realmConfigReq->realmKeyInfo.RealmName[0] == INVALID_STR)
	{
		return DRE_DB_FAIL;	
	}
	else if(realmConfigReq->realmKeyInfo.PeerHostId[0] == INVALID_STR)
	{
		return DRE_DB_FAIL;
	}
	else if(realmConfigReq->realmKeyInfo.AppId == INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}
	return DRE_DB_SUCCESS;
}


void RealmRoutingTQuery::sql_RealmRouting_Create_Select_Query(DreRealmRoutingPayload *realmConfigReq,char *pStatement)
{
	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	sprintf(pStatement,"select * from RealmRoutingT"); 

	sprintf(sWhereStatement,"where ");

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(realmConfigReq->realmKeyInfo.RealmName[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"RealmName='%s' and ",realmConfigReq->realmKeyInfo.RealmName);
	}

	if(realmConfigReq->realmKeyInfo.PeerHostId[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"PeerHostIdentity='%s' and ",realmConfigReq->realmKeyInfo.PeerHostId);
	}

	if(realmConfigReq->realmKeyInfo.AppId != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"ApplicationID=%ld and ",realmConfigReq->realmKeyInfo.AppId);
	}

	if(realmConfigReq->realmInfo.LocalAction != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"LocalAction=%d and ",realmConfigReq->realmInfo.LocalAction);
	}

	if(realmConfigReq->realmInfo.VendorID != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"VendorID=%ld and ",realmConfigReq->realmInfo.VendorID);
	}

	if(realmConfigReq->realmInfo.Priority != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"Priority=%d and ",realmConfigReq->realmInfo.Priority);
	}

	if(realmConfigReq->realmInfo.NodeDiscovery != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"NodeDiscovery=%d and ",realmConfigReq->realmInfo.NodeDiscovery);
	}

	if(realmConfigReq->realmInfo.RedirectHostUsage != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"RedirectHostUsage=%d and ",realmConfigReq->realmInfo.RedirectHostUsage);
	}

	if(realmConfigReq->realmInfo.RedirectMaxCacheTime != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"RedirectMaxCacheTime=%d and ",realmConfigReq->realmInfo.RedirectMaxCacheTime);
	}

	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
		sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);
	}


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

}

void RealmRoutingTQuery::set_RealmRouting_Set_TableName()
{
	memset(sRealmRoutingTableName,0,sizeof(sRealmRoutingTableName));
	sprintf(sRealmRoutingTableName + strlen(sRealmRoutingTableName),"%cRealmRoutingT",TABLE_DELIMITER);
}

void RealmRoutingTQuery::set_RealmRouting_Set_FieldName()
{
	memset(sRealmRoutingFieldNames,0,sizeof(sRealmRoutingFieldNames));	
	sprintf(sRealmRoutingFieldNames + strlen(sRealmRoutingFieldNames),"%cRealmName%cPeerHostIdentity%cApplicationID%cLocalAction%cVendorID%cPriority%cNodeDiscovery%cRedirectHostUsage%cRedirectMaxCacheTime%c",FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);
	
}

DbStatus_e RealmRoutingTQuery::sql_RealmRouting_Check_All_Invalid(DreRealmRoutingPayload *realmRoutingConfigReq)
{
	
	if(realmRoutingConfigReq->realmInfo.LocalAction != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(realmRoutingConfigReq->realmInfo.VendorID != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(realmRoutingConfigReq->realmInfo.Priority != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(realmRoutingConfigReq->realmInfo.NodeDiscovery != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(realmRoutingConfigReq->realmInfo.RedirectHostUsage != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(realmRoutingConfigReq->realmInfo.RedirectMaxCacheTime != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}


	return DRE_DB_SUCCESS;
}
