#include <MysqlInterface.h>

using namespace std;

void UserTQuery::sql_User_Create_Check_Modifcation_Query(DreUserConfigPayload *dreUserConfigReq,char *pStatement)
{

	sprintf(pStatement,"select UserName from UserT where UserName ='%s'",dreUserConfigReq->UserKeyInfo.UserName);
}


void UserTQuery::sql_User_Create_Add_Query(DreUserConfigPayload *dreUserConfigReq,char *pStatement)
{
	char sFieldName[MAX_STATEMENT_SIZE] 	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	
    int iLengthFieldValue = 0;


	sprintf(pStatement,"insert into UserT "); 
	strcpy(sFieldName,"(UserName");
	sprintf(sFieldValue,"('%s'",dreUserConfigReq->UserKeyInfo.UserName);
    iLengthFieldValue = strlen(sFieldValue);

	if(dreUserConfigReq->UserConfigInfo.privilege != INVALID_NUM)
	{
		strcat(sFieldName,",Previlage");
		sprintf(sFieldValue + iLengthFieldValue,",%d",dreUserConfigReq->UserConfigInfo.privilege);
        iLengthFieldValue = strlen(sFieldValue);
	}

	if(dreUserConfigReq->UserConfigInfo.password[0] != INVALID_STR)
	{
		strcat(sFieldName,",Password");
		//snprintf(sFieldValue + iLengthFieldValue,16,",'%s'",dreUserConfigReq->UserConfigInfo.password);
        sprintf(sFieldValue + iLengthFieldValue,",'");
        iLengthFieldValue = iLengthFieldValue + 2;
        memcpy(sFieldValue + iLengthFieldValue,dreUserConfigReq->UserConfigInfo.password,16);
        iLengthFieldValue = iLengthFieldValue + 16;
        sprintf(sFieldValue + iLengthFieldValue,"'");
        iLengthFieldValue = iLengthFieldValue + 1;
	}



	strcat(sFieldName,")");
	sFieldValue[iLengthFieldValue] = ')';

    iLengthFieldValue = iLengthFieldValue + 1;

	sprintf(pStatement + strlen(pStatement),"%s value ",sFieldName);
    memcpy(pStatement + strlen(pStatement),sFieldValue,iLengthFieldValue);

}


void UserTQuery::sql_User_Create_Mod_Query(DreUserConfigPayload *dreUserConfigReq,char *pStatement)
{
    int iLengthStatement = 0;

	sprintf(pStatement,"update UserT set "); 
    iLengthStatement = strlen(pStatement);

	if(dreUserConfigReq->UserConfigInfo.privilege != INVALID_NUM)
	{
		sprintf(pStatement + iLengthStatement,"Previlage=%d,",dreUserConfigReq->UserConfigInfo.privilege);
        iLengthStatement = strlen(pStatement);
	}

	if(dreUserConfigReq->UserConfigInfo.password[0] != INVALID_STR)
	{
		sprintf(pStatement + iLengthStatement,"Password='");
        iLengthStatement = iLengthStatement + 10;
		memcpy(pStatement + iLengthStatement,dreUserConfigReq->UserConfigInfo.password,16);
        iLengthStatement = iLengthStatement + 16;
		sprintf(pStatement + iLengthStatement,"',");
        iLengthStatement = iLengthStatement + 2;

	}


	pStatement[iLengthStatement -1] = ' ';

	sprintf(pStatement + iLengthStatement,"where UserName='%s'",dreUserConfigReq->UserKeyInfo.UserName);

}


void UserTQuery::sql_User_Create_Delete_Query(DreUserConfigPayload *dreUserConfigReq,char *pStatement)
{
	sprintf(pStatement,"delete from UserT where UserName='%s'",dreUserConfigReq->UserKeyInfo.UserName); 

}


DbStatus_e UserTQuery::sql_User_Payload_Validation(DreUserConfigPayload *dreUserConfigReq)
{
	if(dreUserConfigReq->UserKeyInfo.UserName[0] == INVALID_STR)
	{
		return DRE_DB_FAIL;	
	}

	return DRE_DB_SUCCESS;
}


void UserTQuery::sql_User_Create_Select_Query(DreUserConfigPayload *dreUserConfigReq,char *pStatement)
{


	int iFlag 					= 0;
    int iLengthQuery            = 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	sprintf(pStatement,"select * from UserT "); 

	sprintf(sWhereStatement,"where ");
    iLengthQuery = strlen(sWhereStatement);
    
	if(dreUserConfigReq->UserConfigInfo.privilege != INVALID_NUM)
	{
		iFlag = 1;
		sprintf(sWhereStatement + iLengthQuery,"Previlage=%d and ",dreUserConfigReq->UserConfigInfo.privilege);
        iLengthQuery = strlen(sWhereStatement);

	}

	if(dreUserConfigReq->UserKeyInfo.UserName[0] != INVALID_STR)
	{
		iFlag = 1;
		sprintf(sWhereStatement + strlen(sWhereStatement),"UserName='%s' and ",dreUserConfigReq->UserKeyInfo.UserName);
        iLengthQuery = strlen(sWhereStatement);
	}


	if(iFlag)
	{
		sWhereStatement[iLengthQuery - 4] = '\0';
		sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);
	}


}

void UserTQuery::set_User_Set_TableName()
{
	memset(sUserTableName,0,sizeof(sUserTableName));
	sprintf(sUserTableName + strlen(sUserTableName),"%cUserT",TABLE_DELIMITER);
}

void UserTQuery::set_User_Set_FieldName()
{
	memset(sUserFieldNames,0,sizeof(sUserFieldNames));	
	sprintf(sUserFieldNames + strlen(sUserFieldNames),"%cPassword%cUserName%cPrevilage%c",FIELD_DELIMITER,FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);
	
}

DbStatus_e UserTQuery::sql_User_Check_All_Invalid(DreUserConfigPayload *dreUserPayload)
{

	if(dreUserPayload->UserConfigInfo.password[0] != INVALID_STR)
	{
		return DRE_DB_FAIL;
	}

	return DRE_DB_SUCCESS;
}
