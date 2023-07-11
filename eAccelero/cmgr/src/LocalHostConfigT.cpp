#include <MysqlInterface.h>

using namespace std;

void LocalHostConfigTQuery::sql_LocalHostConfig_Create_Check_Modifcation_Query(DreLocalHostPayload *dreLocalHostConfigReq,char *pStatement)
{
	sprintf(pStatement,"select IPAddress from  LocalHostConfigT where RealmName='%s' and HostName='%s'",dreLocalHostConfigReq->LocalHostKeyInfo.RealmName,dreLocalHostConfigReq->LocalHostKeyInfo.HostName);
}

void LocalHostConfigTQuery::sql_LocalHostConfig_Create_Add_Query(DreLocalHostPayload *dreLocalHostConfigReq,char *pStatement)
{
	char sFieldName[MAX_STATEMENT_SIZE] 	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"insert into LocalHostConfigT "); 
	strcpy(sFieldName,"(HostName,RealmName");
	sprintf(sFieldValue,"('%s','%s'",dreLocalHostConfigReq->LocalHostKeyInfo.HostName,dreLocalHostConfigReq->LocalHostKeyInfo.RealmName);

	if(dreLocalHostConfigReq->LocalHostTransportInfo.IpAddr[0] != INVALID_STR)
	{
		strcat(sFieldName,",IPAddress");
		sprintf(sFieldValue + strlen(sFieldValue),",'%s'",dreLocalHostConfigReq->LocalHostTransportInfo.IpAddr);
	}

	if(dreLocalHostConfigReq->LocalHostTransportInfo.portno != INVALID_NUM)
	{
		strcat(sFieldName,",Port");
		sprintf(sFieldValue + strlen(sFieldValue),",%d",dreLocalHostConfigReq->LocalHostTransportInfo.portno);
	}
	
	if(dreLocalHostConfigReq->LocalHostTransportInfo.transportType != INVALID_NUM)
        {
                strcat(sFieldName,",TransportType");
                sprintf(sFieldValue + strlen(sFieldValue),",%d",dreLocalHostConfigReq->LocalHostTransportInfo.transportType);
        }

	if(dreLocalHostConfigReq->LocalHostAuthInfo.LifeTime != INVALID_NUM)
	{
		strcat(sFieldName,",AuthLifeTime");
		sprintf(sFieldValue + strlen(sFieldValue),",%ld",dreLocalHostConfigReq->LocalHostAuthInfo.LifeTime);
	}

	if(dreLocalHostConfigReq->LocalHostAuthInfo.GraceTime != INVALID_NUM)
	{
		strcat(sFieldName,",AuthGraceTime");
		sprintf(sFieldValue + strlen(sFieldValue),",%ld",dreLocalHostConfigReq->LocalHostAuthInfo.GraceTime);
	}

	if(dreLocalHostConfigReq->LocalHostAuthInfo.TimeOut != INVALID_NUM)
	{
		strcat(sFieldName,",AuthTimeOut");
		sprintf(sFieldValue + strlen(sFieldValue),",%ld",dreLocalHostConfigReq->LocalHostAuthInfo.TimeOut);
	}

	if(dreLocalHostConfigReq->LocalHostAcctInfo.Interim != INVALID_NUM)
	{
		strcat(sFieldName,",AcctInterim");
		sprintf(sFieldValue + strlen(sFieldValue),",%ld",dreLocalHostConfigReq->LocalHostAcctInfo.Interim);
	}

	if(dreLocalHostConfigReq->LocalHostAcctInfo.TimeOut != INVALID_NUM)
	{
		strcat(sFieldName,",AcctTimeOut");
		sprintf(sFieldValue + strlen(sFieldValue),",%ld",dreLocalHostConfigReq->LocalHostAcctInfo.TimeOut);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	strcat(sFieldName,")");
	strcat(sFieldValue,")");

	sprintf(pStatement + strlen(pStatement),"%s value %s",sFieldName,sFieldValue);


	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}

void LocalHostConfigTQuery::sql_LocalHostConfig_Create_Mod_Query(DreLocalHostPayload *dreLocalHostConfigReq,char *pStatement)
{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"update LocalHostConfigT set "); 

	if(dreLocalHostConfigReq->LocalHostTransportInfo.IpAddr[0] != INVALID_STR)
	{
		sprintf(pStatement + strlen(pStatement),"IPAddress='%s',",dreLocalHostConfigReq->LocalHostTransportInfo.IpAddr);

	}
	if(dreLocalHostConfigReq->LocalHostTransportInfo.portno != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"Port=%d,",dreLocalHostConfigReq->LocalHostTransportInfo.portno);
	}

	if(dreLocalHostConfigReq->LocalHostTransportInfo.transportType != INVALID_NUM)
        {
                sprintf(pStatement + strlen(pStatement),"TransportType=%d,",dreLocalHostConfigReq->LocalHostTransportInfo.transportType);
        }

	if(dreLocalHostConfigReq->LocalHostAuthInfo.LifeTime != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"AuthLifeTime=%ld,",dreLocalHostConfigReq->LocalHostAuthInfo.LifeTime);

	}
	if(dreLocalHostConfigReq->LocalHostAuthInfo.GraceTime != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"AuthGraceTime=%ld,",dreLocalHostConfigReq->LocalHostAuthInfo.GraceTime);

	}
	if(dreLocalHostConfigReq->LocalHostAuthInfo.TimeOut != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"AuthTimeOut=%ld,",dreLocalHostConfigReq->LocalHostAuthInfo.TimeOut);

	}

	if(dreLocalHostConfigReq->LocalHostAcctInfo.Interim != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"AcctInterim=%ld,",dreLocalHostConfigReq->LocalHostAcctInfo.Interim);

	}
	if(dreLocalHostConfigReq->LocalHostAcctInfo.TimeOut != INVALID_NUM)
	{
		sprintf(pStatement + strlen(pStatement),"AcctTimeOut=%ld,",dreLocalHostConfigReq->LocalHostAcctInfo.TimeOut);

	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	pStatement[strlen(pStatement) -1] = ' ';

	sprintf(pStatement + strlen(pStatement),"where HostName='%s' and RealmName='%s'",dreLocalHostConfigReq->LocalHostKeyInfo.HostName,dreLocalHostConfigReq->LocalHostKeyInfo.RealmName);

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

}

void LocalHostConfigTQuery::sql_LocalHostConfig_Create_Delete_Query(DreLocalHostPayload *dreLocalHostConfigReq,char *pStatement)
{
	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	sprintf(pStatement,"delete from LocalHostConfigT where HostName='%s' and RealmName='%s'",dreLocalHostConfigReq->LocalHostKeyInfo.HostName,dreLocalHostConfigReq->LocalHostKeyInfo.RealmName); 

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}

DbStatus_e LocalHostConfigTQuery::sql_LocalHostConfig_Payload_Validation(DreLocalHostPayload *dreLocalHostConfigReq)
{
	if(dreLocalHostConfigReq->LocalHostKeyInfo.HostName[0] == INVALID_STR)
	{
		return DRE_DB_FAIL;	
	}
	else if(dreLocalHostConfigReq->LocalHostKeyInfo.RealmName[0] == INVALID_STR)
	{
		return DRE_DB_FAIL;
	}
	return DRE_DB_SUCCESS;
}

////////////////////////////////////////////*****************************************************************

void LocalHostConfigTQuery::sql_LocalHostConfig_Create_Select_Query(DreLocalHostPayload *dreLocalHostConfigReq,char *pStatement)
{
	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE] 	= {0};
	sprintf(pStatement,"select * from LocalHostConfigT "); 

	sprintf(sWhereStatement,"where ");

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(dreLocalHostConfigReq->LocalHostKeyInfo.HostName[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"HostName='%s' and ",dreLocalHostConfigReq->LocalHostKeyInfo.HostName);
	}

	if(dreLocalHostConfigReq->LocalHostKeyInfo.RealmName[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"RealmName='%s' and ",dreLocalHostConfigReq->LocalHostKeyInfo.RealmName);
	}

	if(dreLocalHostConfigReq->LocalHostTransportInfo.IpAddr[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"IPAddress='%s' and ",dreLocalHostConfigReq->LocalHostTransportInfo.IpAddr);
		
	}

	if(dreLocalHostConfigReq->LocalHostTransportInfo.portno != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"Port=%d and ",dreLocalHostConfigReq->LocalHostTransportInfo.portno);
	}

	if(dreLocalHostConfigReq->LocalHostTransportInfo.transportType != INVALID_NUM)
        {
                iFlag = 1;
                sprintf(sWhereStatement + strlen(sWhereStatement),"TransportType=%d and ",dreLocalHostConfigReq->LocalHostTransportInfo.transportType);
        }

	if(dreLocalHostConfigReq->LocalHostAuthInfo.LifeTime != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"AuthLifeTime=%ld and ",dreLocalHostConfigReq->LocalHostAuthInfo.LifeTime);
	}

	if(dreLocalHostConfigReq->LocalHostAuthInfo.GraceTime != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"AuthGraceTime=%ld and ",dreLocalHostConfigReq->LocalHostAuthInfo.GraceTime);
	}

	if(dreLocalHostConfigReq->LocalHostAuthInfo.TimeOut != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"AuthTimeOut=%ld and ",dreLocalHostConfigReq->LocalHostAuthInfo.TimeOut);
	}

	if(dreLocalHostConfigReq->LocalHostAcctInfo.Interim != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"AcctInterim=%ld and ",dreLocalHostConfigReq->LocalHostAcctInfo.Interim);
	}

	if(dreLocalHostConfigReq->LocalHostAcctInfo.TimeOut != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"AcctTimeOut=%ld and ",dreLocalHostConfigReq->LocalHostAcctInfo.TimeOut);
	}

	PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
		sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);
	}

}

void LocalHostConfigTQuery::set_LocalHostConfig_Set_TableName()
{
	memset(sLocalHostConfigTableName,0,sizeof(sLocalHostConfigTableName));
	sprintf(sLocalHostConfigTableName + strlen(sLocalHostConfigTableName),"%cLocalHostConfigT",TABLE_DELIMITER);
}

void LocalHostConfigTQuery::set_LocalHostConfig_Set_FieldName()
{
	memset(sLocalHostConfigFieldNames,0,sizeof(sLocalHostConfigFieldNames));	
	sprintf(sLocalHostConfigFieldNames + strlen(sLocalHostConfigFieldNames),"%cHostName%cRealmName%cIPAddress%cPort%cTransportType%cAuthLifeTime%cAuthGraceTime%cAuthTimeOut%cAcctInterim%cAcctTimeOut%c",FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);
	
}

DbStatus_e LocalHostConfigTQuery::sql_LocalHostConfig_Check_All_Invalid(DreLocalHostPayload *dreLocalHostPayload)
{

	if(dreLocalHostPayload->LocalHostTransportInfo.IpAddr[0] != INVALID_STR)
	{
		return DRE_DB_FAIL;
	}

	if(dreLocalHostPayload->LocalHostTransportInfo.portno != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(dreLocalHostPayload->LocalHostTransportInfo.transportType != INVALID_NUM)
        {
                return DRE_DB_FAIL;
        }

	if(dreLocalHostPayload->LocalHostAcctInfo.Interim != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(dreLocalHostPayload->LocalHostAcctInfo.TimeOut != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(dreLocalHostPayload->LocalHostAuthInfo.LifeTime != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(dreLocalHostPayload->LocalHostAuthInfo.GraceTime != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	if(dreLocalHostPayload->LocalHostAuthInfo.TimeOut != INVALID_NUM)
	{
		return DRE_DB_FAIL;
	}

	return DRE_DB_SUCCESS;
}
