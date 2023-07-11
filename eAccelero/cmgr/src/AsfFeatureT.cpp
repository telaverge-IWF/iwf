#include <MysqlInterface.h>

using namespace std;

void AsfFeatureTQuery::sql_AsfFeature_Create_Check_Modifcation_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement)
{

	snprintf(pStatement,MAX_STATEMENT_SIZE,"select COMPONENT_ID from FEATURE_TB where COMPONENT_ID=%d",AsfConfigReq->dreASFConfigKeyInfo.ComponentID);

}

void AsfFeatureTQuery::sql_AsfFeature_Create_Add_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement)
{
	char sFieldName[MAX_STATEMENT_SIZE]	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into FEATURE_TB "); 
	strcpy(sFieldName,"(COMPONENT_ID");	
	snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(%d",AsfConfigReq->dreASFConfigKeyInfo.ComponentID);

	if(AsfConfigReq->dreASFStatus.ASFStatus != INVALID_NUM)
	{
		strcat(sFieldName,",ENABLE_ASF");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",AsfConfigReq->dreASFStatus.ASFStatus);
	}	
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	
	 if(AsfConfigReq->dreASFStatus.ERLBFStatus != INVALID_NUM)
        {
                strcat(sFieldName,",ENABLE_ERLBF");
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",AsfConfigReq->dreASFStatus.ERLBFStatus);
        }
        PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	strcat(sFieldName,")");
        strcat(sFieldValue,")");
	snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);


}

void AsfFeatureTQuery::sql_AsfFeature_Create_Delete_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement)
{

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	 int iFlag                   = 0;
	 char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
    	snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from FEATURE_TB ");
	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	 if(AsfConfigReq->dreASFConfigKeyInfo.ComponentID != INVALID_NUM)
        {
                iFlag = 1;
                snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"COMPONENT_ID=%d and ",AsfConfigReq->dreASFConfigKeyInfo.ComponentID);
        }

	 if(iFlag)
        {
                sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
        }


        PRINTF("%s:%d \n",__FUNCTION__,__LINE__);


}

void AsfFeatureTQuery::sql_AsfFeature_Create_Mod_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement)
{

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	snprintf(pStatement,MAX_STATEMENT_SIZE,"update FEATURE_TB set "); 


	if(AsfConfigReq->dreASFStatus.ASFStatus != INVALID_NUM)
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ENABLE_ASF=%d,",AsfConfigReq->dreASFStatus.ASFStatus);
	}
	 PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
        if(AsfConfigReq->dreASFStatus.ERLBFStatus != INVALID_NUM)
        {
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ENABLE_ERLBF=%d,",AsfConfigReq->dreASFStatus.ERLBFStatus);
        }
         PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	pStatement[strlen(pStatement) -1] = ' ';

	snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where COMPONENT_ID=%d ",AsfConfigReq->dreASFConfigKeyInfo.ComponentID);

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}

DbStatus_e AsfFeatureTQuery::sql_AsfFeature_Payload_Validation(DreASFConfigPayload *AsfConfigReq)
{
	if (AsfConfigReq->dreASFConfigKeyInfo.ComponentID == INVALID_NUM)
	{
		return DRE_DB_FAIL;	
	}
	return DRE_DB_SUCCESS;
}


void AsfFeatureTQuery::sql_AsfFeature_Create_Select_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement)
{
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from FEATURE_TB"); 

	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(AsfConfigReq->dreASFConfigKeyInfo.ComponentID != INVALID_NUM)
	{
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"COMPONENT_ID=%d' and ",AsfConfigReq->dreASFConfigKeyInfo.ComponentID);
	}

	sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
	snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

}

void AsfFeatureTQuery::set_AsfFeature_Set_TableName()
{
	memset(sAsfFeatureTableName,0,sizeof(sAsfFeatureTableName));
	snprintf(sAsfFeatureTableName + strlen(sAsfFeatureTableName),MAX_STATEMENT_SIZE,"%cCOMPONENT_ID",TABLE_DELIMITER);
}

void AsfFeatureTQuery::set_AsfFeature_Set_FieldName()
{
	memset(sAsfFeatureFieldNames,0,sizeof(sAsfFeatureFieldNames));	
	snprintf(sAsfFeatureFieldNames + strlen(sAsfFeatureFieldNames),MAX_STATEMENT_SIZE,"%cComponentID%cASFStatus%cERLBFStatus%c",FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);
	
}

DbStatus_e AsfFeatureTQuery::sql_AsfFeature_Check_All_Invalid(DreASFConfigPayload *AsfConfigReq)
{

	if(AsfConfigReq->dreASFStatus.ASFStatus != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}
	if(AsfConfigReq->dreASFStatus.ERLBFStatus != INVALID_NUM)
        {
                return DRE_DB_FAIL;
        }


	return DRE_DB_SUCCESS;
}
