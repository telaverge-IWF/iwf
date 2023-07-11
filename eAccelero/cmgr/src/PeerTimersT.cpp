#include <MysqlInterface.h>

using namespace std;
void PeerTimersTQuery::sql_PeerTimers_Create_Check_Modifcation_Query(DrePeerTimersConfigPayload *drePeerTimersConfigReq,char *pStatement)	
{
	sprintf(pStatement,"select PeerHostIdentity, RealmName from  PeerTimersT where PeerHostIdentity='%s' and RealmName='%s'",drePeerTimersConfigReq->PeerTimersKeyInfo.peerHostNames,drePeerTimersConfigReq->PeerTimersKeyInfo.realmName);	
}

void PeerTimersTQuery::sql_PeerTimers_Create_Add_Query(DrePeerTimersConfigPayload *drePeerTimersConfigReq,char *pStatement)	
{
	char sFieldName[MAX_STATEMENT_SIZE] 	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"insert into PeerTimersT "); 

	strcpy(sFieldName,"(PeerHostIdentity,RealmName");
	sprintf(sFieldValue,"('%s','%s'",drePeerTimersConfigReq->PeerTimersKeyInfo.peerHostNames,drePeerTimersConfigReq->PeerTimersKeyInfo.realmName);

	if(drePeerTimersConfigReq->PeerTimersConfigInfo.watchdogValue != INVALID_NUM)
	{
		strcat(sFieldName,",WdVal");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",drePeerTimersConfigReq->PeerTimersConfigInfo.watchdogValue);
	}

	if(drePeerTimersConfigReq->PeerTimersConfigInfo.TCValue != INVALID_NUM)///////////// Not present in Design Model.
	{
		strcat(sFieldName,",TcVal");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",drePeerTimersConfigReq->PeerTimersConfigInfo.TCValue);
	}

	if(drePeerTimersConfigReq->PeerTimersConfigInfo.expiryValue != INVALID_NUM)/////////////// Not present in Design Model.
	{
		strcat(sFieldName,",Eval");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",drePeerTimersConfigReq->PeerTimersConfigInfo.expiryValue);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	strcat(sFieldName,")");
	strcat(sFieldValue,")");

	sprintf(pStatement + strlen(pStatement),"%s value %s",sFieldName,sFieldValue);


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}	

void PeerTimersTQuery::sql_PeerTimers_Create_Mod_Query(DrePeerTimersConfigPayload *drePeerTimersConfigReq,char *pStatement)
{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"update PeerTimersT set "); 

	if(drePeerTimersConfigReq->PeerTimersConfigInfo.watchdogValue != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"WdVal=%d,",drePeerTimersConfigReq->PeerTimersConfigInfo.watchdogValue);

	}
	if(drePeerTimersConfigReq->PeerTimersConfigInfo.TCValue != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"TcVal=%d,",drePeerTimersConfigReq->PeerTimersConfigInfo.TCValue);
	}

	if(drePeerTimersConfigReq->PeerTimersConfigInfo.expiryValue != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"Eval=%d,",drePeerTimersConfigReq->PeerTimersConfigInfo.expiryValue);

	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	pStatement[strlen(pStatement) -1] = ' ';

	sprintf(pStatement + strlen(pStatement),"where PeerHostIdentity='%s' and RealmName='%s'",drePeerTimersConfigReq->PeerTimersKeyInfo.peerHostNames,drePeerTimersConfigReq->PeerTimersKeyInfo.realmName);

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);


}


void PeerTimersTQuery::sql_PeerTimers_Create_Delete_Query(DrePeerTimersConfigPayload *drePeerTimersConfigReq,char *pStatement)	
{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"delete from PeerTimersT where PeerHostIdentity='%s' and RealmName='%s'",drePeerTimersConfigReq->PeerTimersKeyInfo.peerHostNames,drePeerTimersConfigReq->PeerTimersKeyInfo.realmName); 

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}

DbStatus_e PeerTimersTQuery::sql_PeerTimers_Payload_Validation(DrePeerTimersConfigPayload *drePeerTimersConfigReq)
{
	if(drePeerTimersConfigReq->PeerTimersKeyInfo.peerHostNames[0] == INVALID_STR || drePeerTimersConfigReq->PeerTimersKeyInfo.realmName[0] == INVALID_STR)
	{
		return DRE_DB_FAIL;	
	}

	return DRE_DB_SUCCESS;
}

void PeerTimersTQuery::sql_PeerTimers_Create_Select_Query(DrePeerTimersConfigPayload *drePeerTimersConfigReq,char *pStatement)
{
	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};

	sprintf(pStatement,"select * from PeerTimersT "); 

	sprintf(sWhereStatement,"where ");

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerTimersConfigReq->PeerTimersKeyInfo.peerHostNames[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"PeerHostIdentity='%s' and ",drePeerTimersConfigReq->PeerTimersKeyInfo.peerHostNames);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerTimersConfigReq->PeerTimersKeyInfo.realmName[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"RealmName='%s' and ",drePeerTimersConfigReq->PeerTimersKeyInfo.realmName);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerTimersConfigReq->PeerTimersConfigInfo.watchdogValue != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"WdVal=%d and ",drePeerTimersConfigReq->PeerTimersConfigInfo.watchdogValue);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerTimersConfigReq->PeerTimersConfigInfo.TCValue != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"TcVal=%d and ",drePeerTimersConfigReq->PeerTimersConfigInfo.TCValue);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerTimersConfigReq->PeerTimersConfigInfo.expiryValue != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"Eval=%d and ",drePeerTimersConfigReq->PeerTimersConfigInfo.expiryValue);
	}



	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
		sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);
	}


}

void PeerTimersTQuery::set_PeerTimers_Set_TableName()
{
	memset(sPeerTimersTableName,0,sizeof(sPeerTimersTableName));
	sprintf(sPeerTimersTableName + strlen(sPeerTimersTableName),"%cPeerTimersT",TABLE_DELIMITER);
}

void PeerTimersTQuery::set_PeerTimers_Set_FieldName()
{
	memset(sPeerTimersFieldNames,0,sizeof(sPeerTimersFieldNames));	
	/* Removing PeerHostIdentity and RealmName from the FieldName, 
		Reason:- we are displaying this table along with the PeerT table. 
		which contains the same fields.  */
	sprintf(sPeerTimersFieldNames + strlen(sPeerTimersFieldNames),"%cWatchDogVal%cReTryVal%cExpiryVal%c",FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);
	
}

DbStatus_e PeerTimersTQuery::sql_PeerTimers_Check_All_Invalid(DrePeerTimersConfigPayload *drePeerTimersConfigReq)
{

	if(drePeerTimersConfigReq->PeerTimersConfigInfo.watchdogValue != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(drePeerTimersConfigReq->PeerTimersConfigInfo.TCValue != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(drePeerTimersConfigReq->PeerTimersConfigInfo.expiryValue != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	return DRE_DB_SUCCESS;
}
