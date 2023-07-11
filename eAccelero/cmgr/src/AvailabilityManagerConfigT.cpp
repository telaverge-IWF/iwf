#include <MysqlInterface.h>

using namespace std;

void AvailabilityManagerConfigTQuery::sql_AvaMgrConfig_Create_Check_Modifcation_Query(AvaMgrConfigPayload *AvaMgrConfigReq,char *pStatement)
{

	sprintf(pStatement,"select ComponentID from AvailabilityManagerConfigT where ComponentID=%d",AvaMgrConfigReq->avaMgrConfigKey.ComponentID);
}

void AvailabilityManagerConfigTQuery::sql_AvaMgrConfig_Create_Add_Query(AvaMgrConfigPayload *AvaMgrConfigReq,char *pStatement)
{


	char sFieldName[MAX_STATEMENT_SIZE] 	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE] 	= {0};	

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"insert into AvailabilityManagerConfigT ");
	strcpy(sFieldName,"(ComponentID");
	sprintf(sFieldValue,"(%d",AvaMgrConfigReq->avaMgrConfigKey.ComponentID);

	if(AvaMgrConfigReq->avaMgrConfigInfo.PingPeriodicity != INVALID_NUM)
        {
                strcat(sFieldName,",PingPeriodicity");
                sprintf(sFieldValue + strlen(sFieldValue),",%ld",AvaMgrConfigReq->avaMgrConfigInfo.PingPeriodicity);
        }
	
	 if(AvaMgrConfigReq->avaMgrConfigInfo.PingPeriodicityForArbitrator != INVALID_NUM)
        {
                strcat(sFieldName,",PingPeriodicityForArbitrator");
                sprintf(sFieldValue + strlen(sFieldValue),",%ld",AvaMgrConfigReq->avaMgrConfigInfo.PingPeriodicityForArbitrator);
        }

	if(AvaMgrConfigReq->avaMgrConfigInfo.VirtualInterfaceActivationTime != INVALID_NUM)
        {
                strcat(sFieldName,",VirtualInterfaceActivationTime");
                sprintf(sFieldValue + strlen(sFieldValue),",%ld",AvaMgrConfigReq->avaMgrConfigInfo.VirtualInterfaceActivationTime);
        }

	if(AvaMgrConfigReq->avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeer != INVALID_NUM)
        {
                strcat(sFieldName,",NumberOfConsecutivePingAckRcvFailuresFromPeer");
                sprintf(sFieldValue + strlen(sFieldValue),",%ld",AvaMgrConfigReq->avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeer);
        }

	 if(AvaMgrConfigReq->avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitrator != INVALID_NUM)
        {
                strcat(sFieldName,",NumberOfConsecutivePingAckRcvFailuresFromArbitrator");
                sprintf(sFieldValue + strlen(sFieldValue),",%ld",AvaMgrConfigReq->avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitrator);
        }

	 if(AvaMgrConfigReq->avaMgrConfigInfo.ProcessRestartMaximumAllowedInterval != INVALID_NUM)
        {
                strcat(sFieldName,",ProcessRestartMaxAllowedInterval");
                sprintf(sFieldValue + strlen(sFieldValue),",%ld",AvaMgrConfigReq->avaMgrConfigInfo.ProcessRestartMaximumAllowedInterval);
        }

	 if(AvaMgrConfigReq->avaMgrConfigInfo.ProcessRestartMaximumAllowedCount != INVALID_NUM)
        {
                strcat(sFieldName,",MaximumAllowedCount");
                sprintf(sFieldValue + strlen(sFieldValue),",%ld",AvaMgrConfigReq->avaMgrConfigInfo.ProcessRestartMaximumAllowedCount);
        }
	
	if(AvaMgrConfigReq->avaMgrConfigInfo.UseIpV6 != INVALID_NUM)
        {
                strcat(sFieldName,",UseIpV6");
                sprintf(sFieldValue + strlen(sFieldValue),",%d",AvaMgrConfigReq->avaMgrConfigInfo.UseIpV6);
        }


	if(AvaMgrConfigReq->avaMgrConfigInfo.PrimaryVirtualIpAddress[0] != INVALID_STR)
	{
		strcat(sFieldName,",PrimaryIpAddress");
		sprintf(sFieldValue + strlen(sFieldValue),",'%s'",AvaMgrConfigReq->avaMgrConfigInfo.PrimaryVirtualIpAddress);
	}

	if(AvaMgrConfigReq->avaMgrConfigInfo.SecondaryVirtualIpAddress[0] != INVALID_STR)
	{
		strcat(sFieldName,",SecondaryVirtualIpAddress");
		sprintf(sFieldValue + strlen(sFieldValue),",'%s'",AvaMgrConfigReq->avaMgrConfigInfo.SecondaryVirtualIpAddress);
	}

	if(AvaMgrConfigReq->avaMgrConfigInfo.GatewayIpAddress[0] != INVALID_STR)
        {
                strcat(sFieldName,",GatewayIpAddress");
                sprintf(sFieldValue + strlen(sFieldValue),",'%s'",AvaMgrConfigReq->avaMgrConfigInfo.GatewayIpAddress);
        }

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	strcat(sFieldName,")");
	strcat(sFieldValue,")");

	sprintf(pStatement + strlen(pStatement),"%s value %s",sFieldName,sFieldValue);


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}


void AvailabilityManagerConfigTQuery::sql_AvaMgrConfig_Create_Mod_Query(AvaMgrConfigPayload *AvaMgrConfigReq,char *pStatement)
{

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"update AvailabilityManagerConfigT set ");

	if(AvaMgrConfigReq->avaMgrConfigInfo.PingPeriodicity != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"PingPeriodicity=%ld,",AvaMgrConfigReq->avaMgrConfigInfo.PingPeriodicity);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(AvaMgrConfigReq->avaMgrConfigInfo.PingPeriodicityForArbitrator != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"PingPeriodicityForArbitrator=%ld,",AvaMgrConfigReq->avaMgrConfigInfo.PingPeriodicityForArbitrator);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	  if(AvaMgrConfigReq->avaMgrConfigInfo.VirtualInterfaceActivationTime != INVALID_NUM)
        {
                sprintf(pStatement + strlen(pStatement),"VirtualInterfaceActivationTime=%ld,",AvaMgrConfigReq->avaMgrConfigInfo.VirtualInterfaceActivationTime);
        }
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	  if(AvaMgrConfigReq->avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeer != INVALID_NUM)
        {
                sprintf(pStatement + strlen(pStatement),"NumberOfConsecutivePingAckRcvFailuresFromPeer=%ld,",AvaMgrConfigReq->avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeer);
        }
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	  if(AvaMgrConfigReq->avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitrator != INVALID_NUM)
        {
                sprintf(pStatement + strlen(pStatement),"NumberOfConsecutivePingAckRcvFailuresFromArbitrator=%ld,",AvaMgrConfigReq->avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitrator);
        }
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	  if(AvaMgrConfigReq->avaMgrConfigInfo.ProcessRestartMaximumAllowedInterval != INVALID_NUM)
        {
                sprintf(pStatement + strlen(pStatement),"ProcessRestartMaxAllowedInterval=%ld,",AvaMgrConfigReq->avaMgrConfigInfo.ProcessRestartMaximumAllowedInterval);
        }
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	  if(AvaMgrConfigReq->avaMgrConfigInfo.ProcessRestartMaximumAllowedCount != INVALID_NUM)
        {
                sprintf(pStatement + strlen(pStatement),"ProcessRestartMaxAllowedCount=%ld,",AvaMgrConfigReq->avaMgrConfigInfo.ProcessRestartMaximumAllowedCount);
        }
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	 if(AvaMgrConfigReq->avaMgrConfigInfo.UseIpV6 != INVALID_NUM)
        {
                sprintf(pStatement + strlen(pStatement),"UseIpV6=%d,",AvaMgrConfigReq->avaMgrConfigInfo.UseIpV6);
        }
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(AvaMgrConfigReq->avaMgrConfigInfo.PrimaryVirtualIpAddress[0] != INVALID_STR)
        {
                sprintf(pStatement + strlen(pStatement),"PrimaryVirtualIpAddress='%s',",AvaMgrConfigReq->avaMgrConfigInfo.PrimaryVirtualIpAddress);
        }
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	 if(AvaMgrConfigReq->avaMgrConfigInfo.SecondaryVirtualIpAddress[0] != INVALID_STR)
        {
                sprintf(pStatement + strlen(pStatement),"SecondaryVirtualIpAddress='%s',",AvaMgrConfigReq->avaMgrConfigInfo.SecondaryVirtualIpAddress);
        }
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	 if(AvaMgrConfigReq->avaMgrConfigInfo.GatewayIpAddress[0] != INVALID_STR)
        {
                sprintf(pStatement + strlen(pStatement),"NearHopGatewayIpAddress='%s',",AvaMgrConfigReq->avaMgrConfigInfo.GatewayIpAddress);
        }
	pStatement[strlen(pStatement) -1] = ' ';

	sprintf(pStatement + strlen(pStatement),"where ComponentID=%d",AvaMgrConfigReq->avaMgrConfigKey.ComponentID);

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}

void AvailabilityManagerConfigTQuery::sql_AvaMgrConfig_Create_Delete_Query(AvaMgrConfigPayload *AvaMgrConfigReq,char *pStatement)
{

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	int iFlag                                       = 0;
        char sWhereStatement[MAX_STATEMENT_SIZE]        = {0};

        sprintf(pStatement,"delete from  AvailabilityManagerConfigT");

        sprintf(sWhereStatement,"where ");

        PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

        if(AvaMgrConfigReq->avaMgrConfigKey.ComponentID != INVALID_NUM)
        {
                iFlag = 1;
                sprintf(sWhereStatement + strlen(sWhereStatement),"ComponentID=%d and ",AvaMgrConfigReq->avaMgrConfigKey.ComponentID);
        }
 	  PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	  if(iFlag)
        {
                sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
                sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);
        }

}

DbStatus_e AvailabilityManagerConfigTQuery::sql_AvaMgrConfig_Payload_Validation(AvaMgrConfigPayload *AvaMgrConfigReq)
{

	if(AvaMgrConfigReq->avaMgrConfigKey.ComponentID != INVALID_NUM)
	 {
                return DRE_DB_FAIL;
        }

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	return DRE_DB_SUCCESS;
}


void AvailabilityManagerConfigTQuery::sql_AvaMgrConfig_Create_Select_Query(AvaMgrConfigPayload *AvaMgrConfigReq,char *pStatement)
{
	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE] 	= {0};

	sprintf(pStatement,"select * from  AvailabilityManagerConfigT"); 

	sprintf(sWhereStatement,"where ");

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	if(AvaMgrConfigReq->avaMgrConfigInfo.PingPeriodicity != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"PingPeriodicity=%ld and ",AvaMgrConfigReq->avaMgrConfigInfo.PingPeriodicity );
	}
	 if(AvaMgrConfigReq->avaMgrConfigInfo.PingPeriodicityForArbitrator != INVALID_NUM)
        {
                iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"PingPeriodicityForArbitrator=%ld and ",AvaMgrConfigReq->avaMgrConfigInfo.PingPeriodicityForArbitrator );

        }
	 if(AvaMgrConfigReq->avaMgrConfigInfo.VirtualInterfaceActivationTime != INVALID_NUM)
        {
                iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"VirtualInterfaceActivationTime=%ld and ",AvaMgrConfigReq->avaMgrConfigInfo.VirtualInterfaceActivationTime );
        }
	 if(AvaMgrConfigReq->avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeer != INVALID_NUM)
        {
                iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"NumberOfConsecutivePingAckRcvFailuresFromPeer=%ld and ",AvaMgrConfigReq->avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeer );
        }
	 if(AvaMgrConfigReq->avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitrator != INVALID_NUM)
        {
                iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"NumberOfConsecutivePingAckRcvFailuresFromArbitrator=%ld and ",AvaMgrConfigReq->avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitrator );
        }
	 if(AvaMgrConfigReq->avaMgrConfigInfo.ProcessRestartMaximumAllowedInterval != INVALID_NUM)
        {
                iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"ProcessRestartMaxAllowedInterval=%ld and ",AvaMgrConfigReq->avaMgrConfigInfo.ProcessRestartMaximumAllowedInterval);
        }
	 if(AvaMgrConfigReq->avaMgrConfigInfo.ProcessRestartMaximumAllowedCount != INVALID_NUM)
        {
                iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"ProcessRestartMaxAllowedCount=%ld and ",AvaMgrConfigReq->avaMgrConfigInfo.ProcessRestartMaximumAllowedCount);
        }
	 if(AvaMgrConfigReq->avaMgrConfigInfo.UseIpV6 != INVALID_NUM)
        {
                iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"UseIpV6=%d and ",AvaMgrConfigReq->avaMgrConfigInfo.UseIpV6);

        }
	 if(AvaMgrConfigReq->avaMgrConfigInfo.PrimaryVirtualIpAddress[0] != INVALID_STR)
        {
                iFlag = 1;
                sprintf(sWhereStatement + strlen(sWhereStatement),"PrimaryVirtualIpAddress='%s' and ",AvaMgrConfigReq->avaMgrConfigInfo.PrimaryVirtualIpAddress);

        }
	if(AvaMgrConfigReq->avaMgrConfigInfo.SecondaryVirtualIpAddress[0] != INVALID_STR)
        {
                iFlag = 1;
                sprintf(sWhereStatement + strlen(sWhereStatement),"SecondaryVirtualIpAddress='%s' and ",AvaMgrConfigReq->avaMgrConfigInfo.SecondaryVirtualIpAddress);

        }
	if(AvaMgrConfigReq->avaMgrConfigInfo.GatewayIpAddress[0] != INVALID_STR)
        {
                iFlag = 1;
                sprintf(sWhereStatement + strlen(sWhereStatement),"NearHopGatewayIpAddress='%s' and ",AvaMgrConfigReq->avaMgrConfigInfo.GatewayIpAddress);

        }
	if(AvaMgrConfigReq->avaMgrConfigKey.ComponentID != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"ComponentID=%d and ",AvaMgrConfigReq->avaMgrConfigKey.ComponentID );
	}


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
		sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);
	}
}

void AvailabilityManagerConfigTQuery::set_AvaMgrConfig_Set_TableName()
{
	memset(sAvaMgrConfigTableName,0,sizeof(sAvaMgrConfigTableName));
	sprintf(sAvaMgrConfigTableName + strlen(sAvaMgrConfigTableName),"%cAvailabilityManagerConfigT",TABLE_DELIMITER);
}

void AvailabilityManagerConfigTQuery::set_AvaMgrConfig_Set_FieldName()
{
	memset(sAvaMgrConfigFieldNames,0,sizeof(sAvaMgrConfigFieldNames));	
	sprintf(sAvaMgrConfigFieldNames + strlen(sAvaMgrConfigFieldNames),"%cPingPeriodicity%cPingPeriodicityForArbitrator%cVirtualInterfaceActivationTime%cNumberOfConsecutivePingAckRcvFailuresFromPeer%cNumberOfConsecutivePingAckRcvFailuresFromArbitrator%cProcessRestartMaxAllowedInterval%cProcessRestartMaxAllowedCount%cUseIpV6%cPrimaryVirtualIpAddress%cSecondaryVirtualIpAddress%cNearHopGatewayIpAddress%cComponentID%c",FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);
	
}


DbStatus_e AvailabilityManagerConfigTQuery::sql_AvaMgrConfig_Check_All_Invalid(AvaMgrConfigPayload *AvaMgrConfigReq)
{

	if(AvaMgrConfigReq->avaMgrConfigInfo.PingPeriodicity != INVALID_NUM)
        {
                return DRE_DB_FAIL;
        }
        if(AvaMgrConfigReq->avaMgrConfigInfo.PingPeriodicityForArbitrator != INVALID_NUM)
        {
                return DRE_DB_FAIL;
        }
        if(AvaMgrConfigReq->avaMgrConfigInfo.VirtualInterfaceActivationTime != INVALID_NUM)
        {
                return DRE_DB_FAIL;
        }
        if(AvaMgrConfigReq->avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeer != INVALID_NUM)
        {
                return DRE_DB_FAIL;
        }
        if(AvaMgrConfigReq->avaMgrConfigInfo.NumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitrator != INVALID_NUM)
        {
                return DRE_DB_FAIL;
        }
        if(AvaMgrConfigReq->avaMgrConfigInfo.ProcessRestartMaximumAllowedInterval != INVALID_NUM)
        {
                return DRE_DB_FAIL;
        }
        if(AvaMgrConfigReq->avaMgrConfigInfo.ProcessRestartMaximumAllowedCount != INVALID_NUM)
        {
                return DRE_DB_FAIL;
        }
        if(AvaMgrConfigReq->avaMgrConfigInfo.UseIpV6 != INVALID_NUM)
        {
                return DRE_DB_FAIL;
        }
        if(AvaMgrConfigReq->avaMgrConfigInfo.PrimaryVirtualIpAddress[0] != INVALID_STR)
         {
                return DRE_DB_FAIL;
        }
        if(AvaMgrConfigReq->avaMgrConfigInfo.SecondaryVirtualIpAddress[0] != INVALID_STR)
         {
                return DRE_DB_FAIL;
        }
        if(AvaMgrConfigReq->avaMgrConfigInfo.GatewayIpAddress[0] != INVALID_STR)
         {
                return DRE_DB_FAIL;
	}
	return DRE_DB_SUCCESS;
}
