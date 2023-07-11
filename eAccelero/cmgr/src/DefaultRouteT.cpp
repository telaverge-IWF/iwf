#include <MysqlInterface.h>

using namespace std;

void DefaultRouteTQuery::sql_DefaultRoute_Create_Check_Modifcation_Query(DreDefaultRoutePayload *dreDefaultRouteReq,char *pStatement)
{
	sprintf(pStatement,"select PeerHostIdentity from  DefaultRouteT where RealmName='%s'",dreDefaultRouteReq->defaultRouteKeyInfo.RealmName);	
}

void DefaultRouteTQuery::sql_DefaultRoute_Create_Add_Query(DreDefaultRoutePayload *dreDefaultRouteReq,char *pStatement)
{
	char sFieldName[MAX_STATEMENT_SIZE]	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"insert into DefaultRouteT "); 
	strcpy(sFieldName,"(RealmName");
	sprintf(sFieldValue,"('%s'",dreDefaultRouteReq->defaultRouteKeyInfo.RealmName);

	if(dreDefaultRouteReq->defaultRouteInfo.PeerHostIds != INVALID_STR)
	{
		strcat(sFieldName,",PeerHostIdentity");
		sprintf(sFieldValue + strlen(sFieldValue),",'%s'",dreDefaultRouteReq->defaultRouteInfo.PeerHostIds);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	strcat(sFieldName,")");
	strcat(sFieldValue,")");

	sprintf(pStatement + strlen(pStatement),"%s value %s",sFieldName,sFieldValue);


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}

void DefaultRouteTQuery::sql_DefaultRoute_Create_Mod_Query(DreDefaultRoutePayload *dreDefaultRouteReq,char *pStatement)
{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"update DefaultRouteT set "); 

	if(dreDefaultRouteReq->defaultRouteInfo.PeerHostIds[0] != INVALID_STR)
	{
		sprintf(pStatement + strlen(pStatement),"PeerHostIdentity='%s',",dreDefaultRouteReq->defaultRouteInfo.PeerHostIds);

	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	pStatement[strlen(pStatement) -1] = ' ';

	sprintf(pStatement + strlen(pStatement),"where RealmName='%s'",dreDefaultRouteReq->defaultRouteKeyInfo.RealmName);

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

}

void DefaultRouteTQuery::sql_DefaultRoute_Create_Delete_Query(DreDefaultRoutePayload *dreDefaultRouteReq,char *pStatement)
{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"delete from DefaultRouteT where RealmName='%s'",dreDefaultRouteReq->defaultRouteKeyInfo.RealmName); 

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}

DbStatus_e DefaultRouteTQuery::sql_DefaultRoute_Payload_Validation(DreDefaultRoutePayload *dreDefaultRouteReq)
{
	if(dreDefaultRouteReq->defaultRouteKeyInfo.RealmName[0] == INVALID_STR)
	{
		return DRE_DB_FAIL;	
	}

	return DRE_DB_SUCCESS;
}


void DefaultRouteTQuery::sql_DefaultRoute_Create_Select_Query(DreDefaultRoutePayload *dreDefaultRouteReq,char *pStatement)
{
	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE] 	= {0};
	sprintf(pStatement,"select * from DefaultRouteT "); 

	sprintf(sWhereStatement,"where ");

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(dreDefaultRouteReq->defaultRouteKeyInfo.RealmName[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"RealmName='%s' and ",dreDefaultRouteReq->defaultRouteKeyInfo.RealmName);
	}

	if(dreDefaultRouteReq->defaultRouteInfo.PeerHostIds[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"PeerHostIdentity='%s' and ",dreDefaultRouteReq->defaultRouteInfo.PeerHostIds);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
		sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);
	}

}

void DefaultRouteTQuery::set_DefaultRoute_Set_TableName()
{
	memset(sDefaultRouteTableName,0,sizeof(sDefaultRouteTableName));
	sprintf(sDefaultRouteTableName + strlen(sDefaultRouteTableName),"%cDefaultRouteT",TABLE_DELIMITER);
}

void DefaultRouteTQuery::set_DefaultRoute_Set_FieldName()
{
	memset(sDefaultRouteFieldNames,0,sizeof(sDefaultRouteFieldNames));	
	sprintf(sDefaultRouteFieldNames + strlen(sDefaultRouteFieldNames),"%cRealmName%cPeerHostIdentity%c",FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);
	
}


DbStatus_e DefaultRouteTQuery::sql_DefaultRoute_Check_All_Invalid(DreDefaultRoutePayload *dreDefaultRoutePayload)
{
	if(dreDefaultRoutePayload->defaultRouteInfo.PeerHostIds[0] != INVALID_STR)
	{
		return DRE_DB_FAIL;
	}	

	return DRE_DB_SUCCESS;
}

