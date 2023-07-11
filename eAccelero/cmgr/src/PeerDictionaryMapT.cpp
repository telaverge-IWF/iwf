#include <MysqlInterface.h>

using namespace std;

void PeerDictionaryMapTQuery::sql_PeerDictionaryMap_Create_Check_Modifcation_Query(DrePeerPayload *peerConfigReq,char *pStatement)
{

	sprintf(pStatement,"select PEER_DICTIONARY_ASSN_ID from PEER_DICTIONARY_MAP_TB where PEER_ID=(select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s') and DICTIONARY_ID = %s",peerConfigReq->peerDictionaryInfo.peerKeyInfo.HostName,peerConfigReq->peerDictionaryInfo.peerKeyInfo.RealmName,peerConfigReq->peerDictionaryInfo.PeerDictionaryIds[0]);
}


void PeerDictionaryMapTQuery::sql_PeerDictionaryMap_Create_Add_Query(DrePeerPayload *peerConfigReq,char *pStatement)
{
	char sFieldName[MAX_STATEMENT_SIZE] 	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"insert into PEER_DICTIONARY_MAP_TB "); 
	strcpy(sFieldName,"(PEER_ID");
	sprintf(sFieldValue,"((select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s')",peerConfigReq->peerDictionaryInfo.peerKeyInfo.HostName,peerConfigReq->peerDictionaryInfo.peerKeyInfo.RealmName);

	if(peerConfigReq->peerDictionaryInfo.PeerDictionaryIds[0] != NULL)
	{
		strcat(sFieldName,",DICTIONARY_ID");
		sprintf(sFieldValue + strlen(sFieldValue),",%s",peerConfigReq->peerDictionaryInfo.PeerDictionaryIds[0]);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	strcat(sFieldName,")");
	strcat(sFieldValue,")");

	sprintf(pStatement + strlen(pStatement),"%s value %s",sFieldName,sFieldValue);


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

}


void PeerDictionaryMapTQuery::sql_PeerDictionaryMap_Create_Mod_Query(DrePeerPayload *peerConfigReq,char *pStatement)
{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"update PEER_DICTIONARY_MAP_TB set "); 
	if(peerConfigReq->peerDictionaryInfo.PeerDictionaryIds[0] != NULL)
	{
		sprintf(pStatement + strlen(pStatement),"DICTIONARY_ID=%s,",peerConfigReq->peerDictionaryInfo.PeerDictionaryIds[0]);

	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	pStatement[strlen(pStatement) -1] = ' ';

	sprintf(pStatement + strlen(pStatement),"where PEER_DICTIONARY_ASSN_ID=%s",peerConfigReq->peerDictionaryInfo.PeerDictionaryIds[0]);

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}


void PeerDictionaryMapTQuery::sql_PeerDictionaryMap_Create_Delete_Query(DrePeerPayload *peerConfigReq,char *pStatement)
{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"delete from PEER_DICTIONARY_MAP_TB where PEER_ID=(select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s')",peerConfigReq->peerDictionaryInfo.peerKeyInfo.HostName,peerConfigReq->peerDictionaryInfo.peerKeyInfo.RealmName);

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}


DbStatus_e PeerDictionaryMapTQuery::sql_PeerDictionaryMap_Payload_Validation(DrePeerPayload *peerConfigReq)
{
	PRINTF("%s:%d  realm name %s\n",__FUNCTION__,__LINE__,peerConfigReq->peerDictionaryInfo.peerKeyInfo.RealmName);
	PRINTF("%s:%d  host name %s\n",__FUNCTION__,__LINE__,peerConfigReq->peerDictionaryInfo.peerKeyInfo.HostName);
	PRINTF("%s:%d  dictionary %dsn",__FUNCTION__,__LINE__,peerConfigReq->peerDictionaryInfo.PeerDictionaryIds[0]);
	if(peerConfigReq->peerDictionaryInfo.peerKeyInfo.RealmName[0] == INVALID_STR)
	{
		return DRE_DB_FAIL;	
	}

	if(peerConfigReq->peerDictionaryInfo.peerKeyInfo.HostName[0] == INVALID_STR)
	{
		return DRE_DB_FAIL;	
	}

	if(peerConfigReq->peerDictionaryInfo.PeerDictionaryIds[0] == NULL)
	{
		return DRE_DB_FAIL;	
	}



	return DRE_DB_SUCCESS;
}


void PeerDictionaryMapTQuery::sql_PeerDictionaryMap_Create_Select_Query(DrePeerPayload *peerConfigReq,char *pStatement)
{
	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	sprintf(pStatement,"select PeerT.PeerHostIdentity,PeerT.RealmName,DICTIONARY_ID from PEER_DICTIONARY_MAP_TB,PeerT ");

	sprintf(sWhereStatement,"where PeerT.PeerID = PEER_DICTIONARY_MAP_TB.PEER_ID and ");

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(peerConfigReq->peerDictionaryInfo.PeerDictionaryIds[0] != NULL)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"DICTIONARY_ID=%s and ",peerConfigReq->peerDictionaryInfo.PeerDictionaryIds[0]);
	}

	if(peerConfigReq->peerDictionaryInfo.peerKeyInfo.HostName[0] != INVALID_STR && peerConfigReq->peerDictionaryInfo.peerKeyInfo.RealmName[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"PEER_ID=(select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s') and ",peerConfigReq->peerDictionaryInfo.peerKeyInfo.HostName,peerConfigReq->peerDictionaryInfo.peerKeyInfo.RealmName);

	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	
	sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
	sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);

}

void PeerDictionaryMapTQuery::set_PeerDictionaryMap_Set_TableName()
{
	memset(sPeerDictionaryMapTableName,0,sizeof(sPeerDictionaryMapTableName));
	sprintf(sPeerDictionaryMapTableName + strlen(sPeerDictionaryMapTableName),"%cPEER_DICTIONARY_MAP_TB",TABLE_DELIMITER);
}

void PeerDictionaryMapTQuery::set_PeerDictionaryMap_Set_FieldName()
{
	memset(sPeerDictionaryMapFieldNames,0,sizeof(sPeerDictionaryMapFieldNames));	
	sprintf(sPeerDictionaryMapFieldNames + strlen(sPeerDictionaryMapFieldNames),"%cPeerHostIdentity%cRealmName%cDictionary ID%c",FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);
	
}

DbStatus_e PeerDictionaryMapTQuery::sql_PeerDictionaryMap_Check_All_Invalid(DrePeerPayload *peerConfigReq)
{

	if(peerConfigReq->peerDictionaryInfo.PeerDictionaryIds[0] != INVALID_STR)
	{
		return DRE_DB_FAIL;
	}

	return DRE_DB_SUCCESS;
}
