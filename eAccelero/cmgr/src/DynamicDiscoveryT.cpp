#include <MysqlInterface.h>

using namespace std;

void DynamicDiscoveryTQuery::sql_DynamicDiscovery_Create_Check_Modifcation_Query(DreDynamicDiscoveryConfigPayload *dreDynamicDiscoveryConfigReq,char *pStatement)
{

	sprintf(pStatement,"select RealmName from DynamicDiscoveryT where RealmName='%s'",dreDynamicDiscoveryConfigReq->DynamicDiscoveryKeyInfo.RealmName);
}


void DynamicDiscoveryTQuery::sql_DynamicDiscovery_Create_Add_Query(DreDynamicDiscoveryConfigPayload *dreDynamicDiscoveryConfigReq,char *pStatement)
{
	char sFieldName[MAX_STATEMENT_SIZE] 	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"insert into DynamicDiscoveryT "); 
	strcpy(sFieldName,"(RealmName");
	sprintf(sFieldValue,"('%s'",dreDynamicDiscoveryConfigReq->DynamicDiscoveryKeyInfo.RealmName);

	if(dreDynamicDiscoveryConfigReq->DynamicDiscoveryConfigInfo.peerHostNames[0] != INVALID_STR)
	{
		strcat(sFieldName,",PeerHostIdentity");
		sprintf(sFieldValue + strlen(sFieldValue),",'%s'",dreDynamicDiscoveryConfigReq->DynamicDiscoveryConfigInfo.peerHostNames);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	strcat(sFieldName,")");
	strcat(sFieldValue,")");

	sprintf(pStatement + strlen(pStatement),"%s value %s",sFieldName,sFieldValue);


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

}


void DynamicDiscoveryTQuery::sql_DynamicDiscovery_Create_Mod_Query(DreDynamicDiscoveryConfigPayload *dreDynamicDiscoveryConfigReq,char *pStatement)
{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"update DynamicDiscoveryT set "); 
	if(dreDynamicDiscoveryConfigReq->DynamicDiscoveryConfigInfo.peerHostNames[0] != INVALID_STR)
	{
		sprintf(pStatement + strlen(pStatement),"PeerHostIdentity='%s',",dreDynamicDiscoveryConfigReq->DynamicDiscoveryConfigInfo.peerHostNames);

	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	pStatement[strlen(pStatement) -1] = ' ';

	sprintf(pStatement + strlen(pStatement),"where RealmName='%s'",dreDynamicDiscoveryConfigReq->DynamicDiscoveryKeyInfo.RealmName);

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}


void DynamicDiscoveryTQuery::sql_DynamicDiscovery_Create_Delete_Query(DreDynamicDiscoveryConfigPayload *dreDynamicDiscoveryConfigReq,char *pStatement)
{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"delete from DynamicDiscoveryT where RealmName='%s'",dreDynamicDiscoveryConfigReq->DynamicDiscoveryKeyInfo.RealmName); 

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}


DbStatus_e DynamicDiscoveryTQuery::sql_DynamicDiscovery_Payload_Validation(DreDynamicDiscoveryConfigPayload *dreDynamicDiscoveryConfigReq)
{
	if(dreDynamicDiscoveryConfigReq->DynamicDiscoveryConfigInfo.peerHostNames[0] == INVALID_STR)
	{
		return DRE_DB_FAIL;	
	}

	return DRE_DB_SUCCESS;
}


void DynamicDiscoveryTQuery::sql_DynamicDiscovery_Create_Select_Query(DreDynamicDiscoveryConfigPayload *dreDynamicDiscoveryConfigReq,char *pStatement)
{


	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	sprintf(pStatement,"select * from DynamicDiscoveryT "); 

	sprintf(sWhereStatement,"where ");

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(dreDynamicDiscoveryConfigReq->DynamicDiscoveryConfigInfo.peerHostNames[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"PeerHostIdentity='%s' and ",dreDynamicDiscoveryConfigReq->DynamicDiscoveryConfigInfo.peerHostNames);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(dreDynamicDiscoveryConfigReq->DynamicDiscoveryKeyInfo.RealmName[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"RealmName='%s' and ",dreDynamicDiscoveryConfigReq->DynamicDiscoveryKeyInfo.RealmName);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
		sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);
	}


}

void DynamicDiscoveryTQuery::set_DynamicDiscovery_Set_TableName()
{
	memset(sDynamicDiscoveryTableName,0,sizeof(sDynamicDiscoveryTableName));
	sprintf(sDynamicDiscoveryTableName + strlen(sDynamicDiscoveryTableName),"%cDynamicDiscoveryT",TABLE_DELIMITER);
}

void DynamicDiscoveryTQuery::set_DynamicDiscovery_Set_FieldName()
{
	memset(sDynamicDiscoveryFieldNames,0,sizeof(sDynamicDiscoveryFieldNames));	
	sprintf(sDynamicDiscoveryFieldNames + strlen(sDynamicDiscoveryFieldNames),"%cPeerHostIdentity%cRealmName%c",FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);
	
}

DbStatus_e DynamicDiscoveryTQuery::sql_DynamicDiscovery_Check_All_Invalid(DreDynamicDiscoveryConfigPayload *dreDynamicDiscoveryPayload)
{

	if(dreDynamicDiscoveryPayload->DynamicDiscoveryConfigInfo.peerHostNames[0] != INVALID_STR)
	{
		return DRE_DB_FAIL;
	}

	return DRE_DB_SUCCESS;
}
