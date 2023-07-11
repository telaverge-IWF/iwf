#include <MysqlInterface.h>

using namespace std;

void AsfConfigTQuery::sql_AsfConfig_Create_Check_Modifcation_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement)
{

	sprintf(pStatement,"select COMPONENT_ID from ASF_CONFIGURATION_TB where COMPONENT_ID=%d",AsfConfigReq->dreASFConfigKeyInfo.ComponentID);

}

void AsfConfigTQuery::sql_AsfConfig_Create_Add_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement)
{
	char sFieldName[MAX_STATEMENT_SIZE]	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"insert into ASF_CONFIGURATION_TB "); 
	strcpy(sFieldName,"(COMPONENT_ID");	
	sprintf(sFieldValue,"(%d",AsfConfigReq->dreASFConfigKeyInfo.ComponentID);

	if(AsfConfigReq->dreASFRespTimeout.responseTimeout != INVALID_NUM)
	{
		strcat(sFieldName,",APP_RESPONSE_TIMEOUT");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",AsfConfigReq->dreASFRespTimeout.responseTimeout);
	}	
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	strcat(sFieldName,")");
        strcat(sFieldValue,")");
	sprintf(pStatement + strlen(pStatement),"%s value %s",sFieldName,sFieldValue);


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);


}

void AsfConfigTQuery::sql_AsfConfig_Create_Delete_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement)
{

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	 int iFlag                   = 0;
	 char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
    	sprintf(pStatement,"delete from ASF_CONFIGURATION_TB ");
	sprintf(sWhereStatement,"where ");
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	 if(AsfConfigReq->dreASFConfigKeyInfo.ComponentID != INVALID_NUM)
        {
                iFlag = 1;
                sprintf(sWhereStatement + strlen(sWhereStatement),"COMPONENT_ID=%d and ",AsfConfigReq->dreASFConfigKeyInfo.ComponentID);
        }

	 if(iFlag)
        {
                sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
                sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);
        }


        PRINTF("%s:%d \n",__FUNCTION__,__LINE__);


}

void AsfConfigTQuery::sql_AsfConfig_Create_Mod_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement)
{

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"update ASF_CONFIGURATION_TB set "); 


	if(AsfConfigReq->dreASFRespTimeout.responseTimeout != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"APP_RESPONSE_TIMEOUT=%d,",AsfConfigReq->dreASFRespTimeout.responseTimeout);
	}
	pStatement[strlen(pStatement) -1] = ' ';

	sprintf(pStatement + strlen(pStatement),"where COMPONENT_ID=%d ",AsfConfigReq->dreASFConfigKeyInfo.ComponentID);

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}

DbStatus_e AsfConfigTQuery::sql_AsfConfig_Payload_Validation(DreASFConfigPayload *AsfConfigReq)
{
	if (AsfConfigReq->dreASFConfigKeyInfo.ComponentID == INVALID_NUM)
	{
		return DRE_DB_FAIL;	
	}
	return DRE_DB_SUCCESS;
}


void AsfConfigTQuery::sql_AsfConfig_Create_Select_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement)
{
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	sprintf(pStatement,"select * from ASF_CONFIGURATION_TB"); 

	sprintf(sWhereStatement,"where ");

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(AsfConfigReq->dreASFConfigKeyInfo.ComponentID != INVALID_NUM)
	{
		sprintf(sWhereStatement + strlen(sWhereStatement),"COMPONENT_ID=%d' and ",AsfConfigReq->dreASFConfigKeyInfo.ComponentID);
	}

	sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
	sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

}

void AsfConfigTQuery::set_AsfConfig_Set_TableName()
{
	memset(sAsfConfigTableName,0,sizeof(sAsfConfigTableName));
	sprintf(sAsfConfigTableName + strlen(sAsfConfigTableName),"%cCOMPONENT_ID",TABLE_DELIMITER);
}

void AsfConfigTQuery::set_AsfConfig_Set_FieldName()
{
	memset(sAsfConfigFieldNames,0,sizeof(sAsfConfigFieldNames));	
	sprintf(sAsfConfigFieldNames + strlen(sAsfConfigFieldNames),"%cComponentID%cResponseTimeout%c",FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);
	
}

DbStatus_e AsfConfigTQuery::sql_AsfConfig_Check_All_Invalid(DreASFConfigPayload *AsfConfigReq)
{

	if(AsfConfigReq->dreASFRespTimeout.responseTimeout != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	return DRE_DB_SUCCESS;
}
