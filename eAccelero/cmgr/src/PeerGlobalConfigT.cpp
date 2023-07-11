#include <MysqlInterface.h>

using namespace std;

void PeerGlobalConfigTQuery::sql_PeerGlobalConfig_Create_Check_Modifcation_Query(DrePeerGlobalConfigPayload *DrePeerGlobalConfigReq,char *pStatement)
{

	sprintf(pStatement,"select ComponentID from PeerGlobalConfigT where ComponentID=%d",DrePeerGlobalConfigReq->PeerGlobalConfigKeyInfo.ComponentID);
}

void PeerGlobalConfigTQuery::sql_PeerGlobalConfig_Create_Add_Query(DrePeerGlobalConfigPayload *DrePeerGlobalConfigReq,char *pStatement)
{

	char sFieldName[MAX_STATEMENT_SIZE]	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"insert into PeerGlobalConfigT");
	strcpy(sFieldName,"(ComponentID");
	sprintf(sFieldValue,"(%d",DrePeerGlobalConfigReq->PeerGlobalConfigKeyInfo.ComponentID);

	if(DrePeerGlobalConfigReq->PeerGlobalConfigInfo.DiscoveryInterval != INVALID_NUM)
	{
		strcat(sFieldName,",DiscoveryInterval");
		sprintf(sFieldValue + strlen(sFieldValue),",%ld",DrePeerGlobalConfigReq->PeerGlobalConfigInfo.DiscoveryInterval);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	strcat(sFieldName,")");
	strcat(sFieldValue,")");

	sprintf(pStatement + strlen(pStatement),"%s value %s",sFieldName,sFieldValue);


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}


void PeerGlobalConfigTQuery::sql_PeerGlobalConfig_Create_Mod_Query(DrePeerGlobalConfigPayload *DrePeerGlobalConfigReq,char *pStatement)
{

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"update PeerGlobalConfigT set ");
	if(DrePeerGlobalConfigReq->PeerGlobalConfigInfo.DiscoveryInterval != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"DiscoveryInterval=%ld,",DrePeerGlobalConfigReq->PeerGlobalConfigInfo.DiscoveryInterval);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	pStatement[strlen(pStatement) -1] = ' ';

	sprintf(pStatement + strlen(pStatement),"where ComponentID=%d",DrePeerGlobalConfigReq->PeerGlobalConfigKeyInfo.ComponentID);

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}



void PeerGlobalConfigTQuery::sql_PeerGlobalConfig_Create_Delete_Query(DrePeerGlobalConfigPayload *DrePeerGlobalConfigReq,char *pStatement)
{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"delete from PeerGlobalConfigT where ComponentID=%d",DrePeerGlobalConfigReq->PeerGlobalConfigKeyInfo.ComponentID); 

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}


DbStatus_e PeerGlobalConfigTQuery::sql_PeerGlobalConfig_Payload_Validation(DrePeerGlobalConfigPayload *DrePeerGlobalConfigReq)
{

	if(DrePeerGlobalConfigReq->PeerGlobalConfigInfo.DiscoveryInterval == INVALID_NUM)
	{
		return DRE_DB_FAIL;	
	}

	return DRE_DB_SUCCESS;
}

void PeerGlobalConfigTQuery::sql_PeerGlobalConfig_Create_Select_Query(DrePeerGlobalConfigPayload *DrePeerGlobalConfigReq,char *pStatement)
{


	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	sprintf(pStatement,"select * from  PeerGlobalConfigT"); 

	sprintf(sWhereStatement,"where ");

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(DrePeerGlobalConfigReq->PeerGlobalConfigInfo.DiscoveryInterval != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"DiscoveryInterval=%ld and ",DrePeerGlobalConfigReq->PeerGlobalConfigInfo.DiscoveryInterval );
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(DrePeerGlobalConfigReq->PeerGlobalConfigKeyInfo.ComponentID != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"ComponentID=%d and ",DrePeerGlobalConfigReq->PeerGlobalConfigKeyInfo.ComponentID);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
		sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);
	}
}

void PeerGlobalConfigTQuery::set_PeerGlobalConfig_Set_TableName()
{
	memset(sPeerGlobalConfigTableName,0,sizeof(sPeerGlobalConfigTableName));
	sprintf(sPeerGlobalConfigTableName + strlen(sPeerGlobalConfigTableName),"%cPeerGlobalConfigT",TABLE_DELIMITER);
}

void PeerGlobalConfigTQuery::set_PeerGlobalConfig_Set_FieldName()
{
	memset(sPeerGlobalConfigFieldNames,0,sizeof(sPeerGlobalConfigFieldNames));	
	sprintf(sPeerGlobalConfigFieldNames + strlen(sPeerGlobalConfigFieldNames),"%cDiscoveryInterval%cComponentID%c",FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);
	
}

DbStatus_e PeerGlobalConfigTQuery::sql_PeerGlobalConfig_Check_All_Invalid(DrePeerGlobalConfigPayload *DrePeerGlobalConfigReq)
{

	if(DrePeerGlobalConfigReq->PeerGlobalConfigInfo.DiscoveryInterval != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	return DRE_DB_SUCCESS;
}
