#include <CMgrDbInterface.h>
#include <CMAPICMgr.h>
#include <CMAPICommon.h>

using namespace std;
void LocalHostConfigSingleRowTPBQuery::sql_LocalHostConfig_Create_Check_Modifcation_Query(LocalHostConfig *dreLocalHostConfigReq,char *pStatement)
{
		snprintf(pStatement,MAX_STATEMENT_SIZE,"select IPAddress from  LocalHostConfigT");
}

void LocalHostConfigSingleRowTPBQuery::sql_LocalHostConfig_Create_Add_Query(LocalHostConfig *dreLocalHostConfigReq,char *pStatement)
{
	char sFieldName[MAX_STATEMENT_SIZE] 	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	DLOG_NONE(" > %s ",__FUNCTION__);

	snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into LocalHostConfigT "); 
	snprintf(sFieldName,MAX_STATEMENT_SIZE,"(HostName,RealmName");
	snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s','%s'",dreLocalHostConfigReq->localhostname().c_str(),dreLocalHostConfigReq->realmname().c_str());

	if(dreLocalHostConfigReq->has_hostipaddr())
	{
		snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IPAddress");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",dreLocalHostConfigReq->hostipaddr().c_str());
	}

	if(dreLocalHostConfigReq->has_port())
	{
		snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",Port");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreLocalHostConfigReq->port());
	}


	if(dreLocalHostConfigReq->has_transporttype())
	{
		snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",TransportType");
		if(dreLocalHostConfigReq->transporttype() == "SCTP")
		{
			snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",2");
		}
		else if (dreLocalHostConfigReq->transporttype() == "TLS")
		{
			snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",3");
		}
		else 
		{
			snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",1");
		}
	}

	if(dreLocalHostConfigReq->has_authsessionlifetime())
	{
		snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",AuthLifeTime");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreLocalHostConfigReq->authsessionlifetime());
	}

	if(dreLocalHostConfigReq->has_authsessiongraceperiod())
	{
		snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",AuthGraceTime");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreLocalHostConfigReq->authsessiongraceperiod());
	}

	if(dreLocalHostConfigReq->has_authsessiontimeout())
	{
		snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",AuthTimeOut");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreLocalHostConfigReq->authsessiontimeout());
	}

	if(dreLocalHostConfigReq->has_acctsessioninteriminterval())
	{
		snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",AcctInterim");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreLocalHostConfigReq->acctsessioninteriminterval());
	}

	if(dreLocalHostConfigReq->has_acctsessiontimeout())
	{
		snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",AcctTimeOut");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreLocalHostConfigReq->acctsessiontimeout());
	}


	snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
	snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

	snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


	DLOG_NONE(" < %s ",__FUNCTION__);
}

void LocalHostConfigSingleRowTPBQuery::sql_LocalHostConfig_Create_Mod_Query(LocalHostConfig *dreLocalHostConfigReq,char *pStatement)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	snprintf(pStatement,MAX_STATEMENT_SIZE,"update LocalHostConfigT set "); 
	int iOperReqID;

	if(dreLocalHostConfigReq->has_operreqid())
	{
		iOperReqID = dreLocalHostConfigReq->operreqid();
	}
	else
	{
		iOperReqID = SET_HOST;	
	}
	
	if(iOperReqID == SET_HOST || iOperReqID == SET_HOSTIP)
	{
		if(dreLocalHostConfigReq->has_hostipaddr())
		{
			snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IPAddress='%s',",dreLocalHostConfigReq->hostipaddr().c_str());

		}
		if(dreLocalHostConfigReq->has_port())
		{
			snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"Port=%d,",dreLocalHostConfigReq->port());
		}


	}
	
	if(iOperReqID == SET_HOST)
	{
		if(dreLocalHostConfigReq->has_transporttype())
		{
			if(dreLocalHostConfigReq->transporttype() == "SCTP")
			{
				snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TransportType=2,");
			}
			else if (dreLocalHostConfigReq->transporttype() == "TLS")
			{
				snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TransportType=3,");
			}
			else 
			{
				snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TransportType=1,");
			}
		}
	}

	if(iOperReqID == SET_HOST || iOperReqID == SET_AUTHTIMERS)
	{
		if(dreLocalHostConfigReq->has_authsessionlifetime())
		{
			snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"AuthLifeTime=%d,",dreLocalHostConfigReq->authsessionlifetime());

		}
	}


	if(iOperReqID == SET_HOST || iOperReqID == SET_AUTHTIMERS)
	{
		if(dreLocalHostConfigReq->has_authsessiongraceperiod())
		{
			snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"AuthGraceTime=%d,",dreLocalHostConfigReq->authsessiongraceperiod());

		}
	}
	

	if(iOperReqID == SET_HOST || iOperReqID == SET_AUTHTIMERS)
	{
		if(dreLocalHostConfigReq->has_authsessiontimeout())
		{
			snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"AuthTimeOut=%d,",dreLocalHostConfigReq->authsessiontimeout());

		}
	}


	if(iOperReqID == SET_HOST || iOperReqID == SET_ACCTTIMERS)
	{
		if(dreLocalHostConfigReq->has_acctsessioninteriminterval())
		{
			snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"AcctInterim=%d,",dreLocalHostConfigReq->acctsessioninteriminterval());

		}
	}


	if(iOperReqID == SET_HOST || iOperReqID == SET_ACCTTIMERS)
	{
		if(dreLocalHostConfigReq->has_acctsessiontimeout())
		{
			snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"AcctTimeOut=%d,",dreLocalHostConfigReq->acctsessiontimeout());

		}
	}


	pStatement[strlen(pStatement) -1] = ' ';

	snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where HostName='%s' and RealmName='%s'",dreLocalHostConfigReq->localhostname().c_str(),dreLocalHostConfigReq->realmname().c_str());

	DLOG_NONE(" < %s ",__FUNCTION__);

}

void LocalHostConfigSingleRowTPBQuery::sql_LocalHostConfig_Create_Delete_Query(LocalHostConfig *dreLocalHostConfigReq,char *pStatement)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from LocalHostConfigT"); 

	DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e LocalHostConfigSingleRowTPBQuery::sql_LocalHostConfig_Payload_Validation(LocalHostConfig *dreLocalHostConfigReq)
{
	if(!dreLocalHostConfigReq->has_localhostname())
	{
		DLOG_ERROR("Primary Key LocalHost Name is not set in the request");
		return DRE_DB_FAIL;	
	}
	else if(dreLocalHostConfigReq->has_realmname())
	{
		DLOG_ERROR("Primary Key Realm Name is not set in the request");
		return DRE_DB_FAIL;
	}
	return DRE_DB_SUCCESS;
}

////////////////////////////////////////////*****************************************************************

void LocalHostConfigSingleRowTPBQuery::sql_LocalHostConfig_Create_Select_Query(LocalHostConfig *dreLocalHostConfigReq,char *pStatement)
{
	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE] 	= {0};
	snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from LocalHostConfigT "); 

	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

	DLOG_NONE(" > %s ",__FUNCTION__);

	if(dreLocalHostConfigReq->has_localhostname())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"HostName='%s' and ",dreLocalHostConfigReq->localhostname().c_str());
	}

	if(dreLocalHostConfigReq->has_realmname())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RealmName='%s' and ",dreLocalHostConfigReq->realmname().c_str());
	}

	if(dreLocalHostConfigReq->has_hostipaddr())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IPAddress='%s' and ",dreLocalHostConfigReq->hostipaddr().c_str());
		
	}

	if(dreLocalHostConfigReq->has_port())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"Port=%d and ",dreLocalHostConfigReq->port());
	}

	if(dreLocalHostConfigReq->has_transporttype())
	{
		iFlag = 1;
		if(dreLocalHostConfigReq->transporttype() == "SCTP")
		{
			snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TransportType=2 and ");
		}
		else if (dreLocalHostConfigReq->transporttype() == "TLS")
		{
			snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TransportType=3 and ");
		}
		else 
		{
			snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TransportType=1 and ");
		}
	}

	if(dreLocalHostConfigReq->has_authsessionlifetime())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"AuthLifeTime=%d and ",dreLocalHostConfigReq->authsessionlifetime());
	}

	if(dreLocalHostConfigReq->has_authsessiongraceperiod())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"AuthGraceTime=%d and ",dreLocalHostConfigReq->authsessiongraceperiod());
	}

	if(dreLocalHostConfigReq->has_authsessiontimeout())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"AuthTimeOut=%d and ",dreLocalHostConfigReq->authsessiontimeout());
	}

	if(dreLocalHostConfigReq->has_acctsessioninteriminterval())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"AcctInterim=%d and ",dreLocalHostConfigReq->acctsessioninteriminterval());
	}

	if(dreLocalHostConfigReq->has_acctsessiontimeout())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"AcctTimeOut=%d and ",dreLocalHostConfigReq->acctsessiontimeout());
	}


	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
	}

	DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e LocalHostConfigSingleRowTPBQuery::sql_LocalHostConfig_Check_All_Invalid(LocalHostConfig *dreLocalHostPayload)
{

	if(dreLocalHostPayload->has_hostipaddr())
	{
		return DRE_DB_FAIL;
	}

	if(dreLocalHostPayload->has_port())
	{
		return DRE_DB_FAIL;
	}

	if(dreLocalHostPayload->has_acctsessioninteriminterval())
	{
		return DRE_DB_FAIL;
	}

	if(dreLocalHostPayload->has_acctsessiontimeout())
	{
		return DRE_DB_FAIL;
	}

	if(dreLocalHostPayload->has_transporttype())
	{
		return DRE_DB_FAIL;
	}

	if(dreLocalHostPayload->has_authsessionlifetime())
	{
		return DRE_DB_FAIL;
	}

	if(dreLocalHostPayload->has_authsessiongraceperiod())
	{
		return DRE_DB_FAIL;
	}

	if(dreLocalHostPayload->has_authsessiontimeout())
	{
		return DRE_DB_FAIL;
	}

	DLOG_INFO("In the Request, No Fields are Set for Operation");
	return DRE_DB_SUCCESS;
}

