#include <MysqlInterface.h>

using namespace std;

void AsfTQuery::sql_Asf_Create_Check_Modifcation_Query(DreASFAppGroupPayload *AsfReq,char *pStatement)
{

	sprintf(pStatement,"select APP_GRP_ID from APPLICATION_GRP_TB where APP_GRP_NAME='%s'",AsfReq->dreASFKeyInfo.GroupName);

}

void AsfTQuery::sql_Asf_Create_Add_Query(DreASFAppGroupPayload *AsfReq,char *pStatement)
{
	char sFiedName[MAX_STATEMENT_SIZE]	= {0};
	char sFiedValue[MAX_STATEMENT_SIZE]	= {0};	

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"insert into APPLICATION_GRP_TB "); 
	strcpy(sFiedName,"(APP_GRP_NAME");	
	sprintf(sFiedValue,"('%s'",AsfReq->dreASFKeyInfo.GroupName);

	if(AsfReq->dreASFConfigInfo.priority != INVALID_NUM)
	{
		strcat(sFiedName,",PRIORITY");
		sprintf(sFiedValue + strlen(sFiedValue),",%d",AsfReq->dreASFConfigInfo.priority);
	}	
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(AsfReq->dreASFConfigInfo.appType != INVALID_NUM)
        {
                strcat(sFiedName,",IS_HOSTED_APP_GRP");
                sprintf(sFiedValue + strlen(sFiedValue),",%d",AsfReq->dreASFConfigInfo.appType);
        }
        PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(AsfReq->dreASFConfigInfo.lbAlgorithm[0] != INVALID_STR)
	{
		strcat(sFiedName,",LB_METHOD_ID");
		sprintf(sFiedValue + strlen(sFiedValue),"(select LB_METHOD_ID from LB_ALGORITHM_TB where LB_METHOD = '%s')",AsfReq->dreASFConfigInfo.lbAlgorithm);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(AsfReq->dreASFConfigInfo.maxAppInstances != INVALID_NUM)
        {
                strcat(sFiedName,",MAX_APP_INSTANCES");
                sprintf(sFiedValue + strlen(sFiedValue),",%d",AsfReq->dreASFConfigInfo.maxAppInstances);
        }
        PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	strcat(sFiedName,")");
	strcat(sFiedValue,")");

	sprintf(pStatement + strlen(pStatement),"%s value %s",sFiedName,sFiedValue);


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);


}

void AsfTQuery::sql_Asf_Create_Delete_Query(DreASFAppGroupPayload *AsfReq,char *pStatement)
{

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	 int iFlag                   = 0;
	 char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
    	sprintf(pStatement,"delete from APPLICATION_GRP_TB ");
	sprintf(sWhereStatement,"where ");
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
	 if(AsfReq->dreASFKeyInfo.GroupName[0] != INVALID_STR)
        {
                iFlag = 1;
                sprintf(sWhereStatement + strlen(sWhereStatement),"APP_GRP_NAME='%s' and ",AsfReq->dreASFKeyInfo.GroupName);
        }

	 if(iFlag)
        {
                sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
                sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);
        }


        PRINTF("%s:%d \n",__FUNCTION__,__LINE__);


}

void AsfTQuery::sql_Asf_Create_Mod_Query(DreASFAppGroupPayload *AsfReq,char *pStatement)
{

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"update APPLICATION_GRP_TB set "); 


	if(AsfReq->dreASFConfigInfo.priority != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"PRIORITY=%d,",AsfReq->dreASFConfigInfo.priority);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(AsfReq->dreASFConfigInfo.appType!= INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"IS_HOSTED_APP_GRP=%d,",AsfReq->dreASFConfigInfo.appType);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(AsfReq->dreASFConfigInfo.lbAlgorithm[0] != INVALID_STR)
	{
		sprintf(pStatement + strlen(pStatement),"LB_METHOD_ID= (select LB_METHOD_ID from LB_ALGORITHM_TB where LB_METHOD = '%s'),",AsfReq->dreASFConfigInfo.lbAlgorithm);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(AsfReq->dreASFConfigInfo.maxAppInstances!= INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"MAX_APP_INSTANCES=%d,",AsfReq->dreASFConfigInfo.maxAppInstances);
	}
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);



	pStatement[strlen(pStatement) -1] = ' ';

	sprintf(pStatement + strlen(pStatement),"where APP_GRP_NAME='%s' ",AsfReq->dreASFKeyInfo.GroupName);

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}

DbStatus_e AsfTQuery::sql_Asf_Payload_Validation(DreASFAppGroupPayload *AsfReq)
{
	if (AsfReq->dreASFKeyInfo.GroupName[0] == INVALID_STR)
	{
		return DRE_DB_FAIL;	
	}
	return DRE_DB_SUCCESS;
}


void AsfTQuery::sql_Asf_Create_Select_Query(DreASFAppGroupPayload *AsfReq,char *pStatement)
{
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	sprintf(pStatement,"select APP_GRP_NAME, PRIORITY, IS_HOSTED_APP_GRP, MAX_APP_INSTANCES, LB_METHOD  FROM APPLICATION_GRP_TB, LB_ALGORITHM_TB"); 

	sprintf(sWhereStatement,"where  LB_ALGORITHM_TB.LB_METHOD_ID  =  APPLICATION_GRP_TB. LB_METHOD_ID and ");

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(AsfReq->dreASFKeyInfo.GroupName[0] != INVALID_STR)
	{
		sprintf(sWhereStatement + strlen(sWhereStatement),"APP_GRP_NAME='%s' and ",AsfReq->dreASFKeyInfo.GroupName);
	}

	if(AsfReq->dreASFConfigInfo.priority != INVALID_NUM)
	{
		sprintf(sWhereStatement + strlen(sWhereStatement),"PRIORITY=%d and ",AsfReq->dreASFConfigInfo.priority);
	}
	
	  if(AsfReq->dreASFConfigInfo.appType != INVALID_NUM)
        {
                sprintf(sWhereStatement + strlen(sWhereStatement),"IS_HOSTED_APP_GRP=%d and ",AsfReq->dreASFConfigInfo.appType);
        }
	
	  if(AsfReq->dreASFConfigInfo.maxAppInstances != INVALID_NUM)
        {
                sprintf(sWhereStatement + strlen(sWhereStatement),"MAX_APP_INSTANCES=%d and ",AsfReq->dreASFConfigInfo.maxAppInstances);
        }
	
	if(AsfReq->dreASFConfigInfo.lbAlgorithm[0] != INVALID_STR)
        {
                sprintf(sWhereStatement + strlen(sWhereStatement),"LB_METHOD_ID=(select LB_METHOD_ID from LB_ALGORITHM_TB where LB_METHOD = '%s') and ",AsfReq->dreASFConfigInfo.lbAlgorithm);
        }

	sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
	sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

}

void AsfTQuery::set_Asf_Set_TableName()
{
	memset(sAsfTableName,0,sizeof(sAsfTableName));
	sprintf(sAsfTableName + strlen(sAsfTableName),"%cAPPLICATION_GRP_TB",TABLE_DELIMITER);
}

void AsfTQuery::set_Asf_Set_FieldName()
{
	memset(sAsfFieldNames,0,sizeof(sAsfFieldNames));	
	sprintf(sAsfFieldNames + strlen(sAsfFieldNames),"%cGroupName%cPriority%cAppType%cLbAlgorithm%cMaxAppInstances%c",FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);
	
}

DbStatus_e AsfTQuery::sql_Asf_Check_All_Invalid(DreASFAppGroupPayload *AsfReq)
{

	if(AsfReq->dreASFConfigInfo.priority != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(AsfReq->dreASFConfigInfo.appType != INVALID_NUM)
        {
                return DRE_DB_FAIL;
        }

	if(AsfReq->dreASFConfigInfo.lbAlgorithm[0] != INVALID_STR)
        {
                return DRE_DB_FAIL;
        }

        if(AsfReq->dreASFConfigInfo.maxAppInstances != INVALID_NUM)
        {
                return DRE_DB_FAIL;
        }

	return DRE_DB_SUCCESS;
}
