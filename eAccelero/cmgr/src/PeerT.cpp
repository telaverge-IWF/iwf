#include <MysqlInterface.h>

using namespace std;

void PeerTQuery::sql_Peer_Create_Check_Modifcation_Query(DrePeerPayload *drePeerConfigReq,char *pStatement)
{

	sprintf(pStatement,"select RealmName from PeerT where PeerHostIdentity='%s' and RealmName='%s'",drePeerConfigReq->peerKeyInfo.HostName,drePeerConfigReq->peerKeyInfo.RealmName);

}

void PeerTQuery::sql_Peer_Create_Add_Query(DrePeerPayload *drePeerConfigReq,char *pStatement)
{
	char sFieldName[MAX_STATEMENT_SIZE]	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"insert into PeerT "); 
	strcpy(sFieldName,"(PeerHostIdentity,RealmName");	
	sprintf(sFieldValue,"('%s','%s'",drePeerConfigReq->peerKeyInfo.HostName,drePeerConfigReq->peerKeyInfo.RealmName);

	if(drePeerConfigReq->peerInfo.IpAddr[0] != INVALID_STR)
	{
		strcat(sFieldName,",PeerIP");
		sprintf(sFieldValue + strlen(sFieldValue),",'%s'",drePeerConfigReq->peerInfo.IpAddr);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.PortNumber != INVALID_NUM)
	{
		strcat(sFieldName,",PeerPort");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",drePeerConfigReq->peerInfo.PortNumber);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerSwitchingInfo.Failover != INVALID_NUM)
	{
		strcat(sFieldName,",FailOverEnable");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",drePeerConfigReq->peerSwitchingInfo.Failover);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerSwitchingInfo.Failback != INVALID_NUM)
	{
		strcat(sFieldName,",FailBackEnable");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",drePeerConfigReq->peerSwitchingInfo.Failback);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.TransportType != INVALID_NUM)
	{
		strcat(sFieldName,",TransportType");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",drePeerConfigReq->peerInfo.TransportType);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
        if(drePeerConfigReq->peerInfo.TLS != INVALID_NUM)
        {
                strcat(sFieldName,",TLSEnabled");
                sprintf(sFieldValue + strlen(sFieldValue),",%d",drePeerConfigReq->peerInfo.TLS);
        }

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.AltHostName[0] != INVALID_STR)
	{
		strcat(sFieldName,",AltPeerID");
		sprintf(sFieldValue + strlen(sFieldValue),",'%s'",drePeerConfigReq->peerInfo.AltHostName);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.IsMate != INVALID_NUM)
	{
		strcat(sFieldName,",isMate");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",drePeerConfigReq->peerInfo.IsMate);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.Enable_Status != INVALID_NUM)
	{
		strcat(sFieldName,",Enable");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",drePeerConfigReq->peerInfo.Enable_Status);
	}

	strcat(sFieldName,")");
	strcat(sFieldValue,")");

	sprintf(pStatement + strlen(pStatement),"%s value %s",sFieldName,sFieldValue);
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}

void PeerTQuery::sql_Peer_Create_Delete_Query(DrePeerPayload *drePeerConfigReq,char *pStatement)
{

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"delete from PeerT where PeerHostIdentity='%s' and RealmName='%s'",drePeerConfigReq->peerKeyInfo.HostName,drePeerConfigReq->peerKeyInfo.RealmName); 

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}

void PeerTQuery::sql_Peer_Create_Select_Query(DrePeerPayload *drePeerConfigReq,char *pStatement)
{

	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	sprintf(pStatement,"select * from PeerT "); 

	sprintf(sWhereStatement,"where ");

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerKeyInfo.HostName[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"PeerHostIdentity='%s' and ",drePeerConfigReq->peerKeyInfo.HostName);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerKeyInfo.RealmName[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"RealmName='%s' and ",drePeerConfigReq->peerKeyInfo.RealmName);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.IpAddr[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"PeerIP='%s' and ",drePeerConfigReq->peerInfo.IpAddr);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.PortNumber != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"PeerPort=%d and ",drePeerConfigReq->peerInfo.PortNumber);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerSwitchingInfo.Failover != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"FailOverEnable=%d and ",drePeerConfigReq->peerSwitchingInfo.Failover);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerSwitchingInfo.Failback != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"FailBackEnable=%d and ",drePeerConfigReq->peerSwitchingInfo.Failback);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.TransportType != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"TransportType=%d and ",drePeerConfigReq->peerInfo.TransportType);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.TLS != INVALID_NUM)
        {
                iFlag = 1;
                sprintf(sWhereStatement + strlen(sWhereStatement),"TLSEnabled=%d and ",drePeerConfigReq->peerInfo.TLS);
        }

        PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(drePeerConfigReq->peerInfo.AltHostName[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"AltPeerID='%s' and ",drePeerConfigReq->peerInfo.AltHostName);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.IsMate != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"isMate=%d and ",drePeerConfigReq->peerInfo.IsMate);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.Enable_Status != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"Enable=%d and ",drePeerConfigReq->peerInfo.Enable_Status);
	}

	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
		sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);
	}

}

void PeerTQuery::sql_Peer_Create_Mod_Query(DrePeerPayload *drePeerConfigReq,char *pStatement)
{

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"update PeerT set "); 

	if(drePeerConfigReq->peerInfo.IpAddr[0] != INVALID_STR)
	{
		sprintf(pStatement + strlen(pStatement),"PeerIP='%s',",drePeerConfigReq->peerInfo.IpAddr);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.PortNumber != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"PeerPort=%d,",drePeerConfigReq->peerInfo.PortNumber);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerSwitchingInfo.Failover != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"FailOverEnable=%d,",drePeerConfigReq->peerSwitchingInfo.Failover);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerSwitchingInfo.Failback != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"FailBackEnable=%d,",drePeerConfigReq->peerSwitchingInfo.Failback);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.TransportType != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"TransportType=%d,",drePeerConfigReq->peerInfo.TransportType);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
        if(drePeerConfigReq->peerInfo.TLS != INVALID_NUM)
        {
                sprintf(pStatement + strlen(pStatement),"TLSEnabled=%d,",drePeerConfigReq->peerInfo.TLS);
        }

	if(drePeerConfigReq->peerInfo.AltHostName[0] != INVALID_STR)
	{
		sprintf(pStatement + strlen(pStatement),"AltPeerID='%s',",drePeerConfigReq->peerInfo.AltHostName);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.IsMate != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"isMate=%d,",drePeerConfigReq->peerInfo.IsMate);
	}


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(drePeerConfigReq->peerInfo.Enable_Status != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"Enable=%d,",drePeerConfigReq->peerInfo.Enable_Status);
	}


	pStatement[strlen(pStatement) -1] = ' ';


	sprintf(pStatement + strlen(pStatement),"where PeerHostIdentity='%s' and RealmName='%s'",drePeerConfigReq->peerKeyInfo.HostName,drePeerConfigReq->peerKeyInfo.RealmName);

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}

DbStatus_e PeerTQuery::sql_Peer_Payload_Validation(DrePeerPayload *drePeerConfigReq)
{
	if(drePeerConfigReq->peerKeyInfo.HostName[0] == INVALID_STR)
	{
		return DRE_DB_FAIL;	
	}
	else if (drePeerConfigReq->peerKeyInfo.RealmName[0] == INVALID_STR)
	{
		return DRE_DB_FAIL;	
	}
	return DRE_DB_SUCCESS;
}

void PeerTQuery::set_Peer_Set_TableName()
{
	memset(sPeerTableName,0,sizeof(sPeerTableName));
	sprintf(sPeerTableName + strlen(sPeerTableName),"%cPeerT",TABLE_DELIMITER);
}

void PeerTQuery::set_Peer_Set_FieldName()
{
	memset(sPeerFieldNames,0,sizeof(sPeerFieldNames));	
	sprintf(sPeerFieldNames + strlen(sPeerFieldNames),"%cPeerHostIdentity%cRealmName%cPeerIP%cPeerPort%cFailOverEnable%cFailBackEnable%cTransportType%cTLSEnabled%cAltPeerID%cisMate%cEnable%c",FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);
	
}

DbStatus_e PeerTQuery::sql_Peer_Check_All_Invalid(DrePeerPayload *drePeerConfigReq)
{

	if(drePeerConfigReq->peerInfo.IpAddr[0] != INVALID_STR)
	{
		return DRE_DB_FAIL;
	}

	if(drePeerConfigReq->peerInfo.PortNumber != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(drePeerConfigReq->peerSwitchingInfo.Failover != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(drePeerConfigReq->peerSwitchingInfo.Failback != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(drePeerConfigReq->peerInfo.TransportType != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}
	
	if(drePeerConfigReq->peerInfo.TLS != INVALID_NUM)
        {
                return DRE_DB_FAIL;
        }

	if(drePeerConfigReq->peerInfo.AltHostName[0] != INVALID_STR)
	{
		return DRE_DB_FAIL;
	}

	if(drePeerConfigReq->peerInfo.IsMate != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(drePeerConfigReq->peerInfo.Enable_Status != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	return DRE_DB_SUCCESS;
}
