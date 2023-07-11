#include <CMgrDbInterface.h>

using namespace std;

void TracingTPBQuery::sql_Tracing_Create_Check_Modifcation_Query(TraceReq *dreTraceReq,char *pStatement)
{

	snprintf(pStatement,MAX_STATEMENT_SIZE,"select ENABLE_TRACING from TRACING_TB ");

}

void TracingTPBQuery::sql_Tracing_Create_Add_Query(TraceReq *dreTraceReq,char *pStatement)
{
	char sFieldName[MAX_STATEMENT_SIZE]	= {0};
	char sFieldValue[MAX_STATEMENT_SIZE]	= {0};	

	DLOG_NONE(" > %s \n",__FUNCTION__);

	snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into TRACING_TB "); 
	snprintf(sFieldName,MAX_STATEMENT_SIZE,"(ENABLE_TRACING"); 
	snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(%d",dreTraceReq->enabletrace());

	snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")"); 
	snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")"); 

	snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);
	DLOG_NONE(" < %s \n",__FUNCTION__);
}

void TracingTPBQuery::sql_Tracing_Create_Delete_Query(TraceReq *dreTraceReq,char *pStatement)
{

	DLOG_NONE(" > %s \n",__FUNCTION__);

	snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from TRACING_TB where ENABLE_TRACING=%d ",dreTraceReq->enabletrace()); 

	DLOG_NONE(" < %s \n",__FUNCTION__);
}

void TracingTPBQuery::sql_Tracing_Create_Select_Query(TraceReq *dreTraceReq,char *pStatement)
{

	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from TRACING_TB "); 

	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

	DLOG_NONE(" > %s \n",__FUNCTION__);
	if(dreTraceReq->has_enabletrace())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ENABLE_TRACING=%d and ",dreTraceReq->enabletrace());
	}

	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
	}

	DLOG_NONE(" < %s \n",__FUNCTION__);
}

void TracingTPBQuery::sql_Tracing_Create_Mod_Query(TraceReq *dreTraceReq,char *pStatement)
{

	DLOG_NONE(" > %s \n",__FUNCTION__);

	snprintf(pStatement,MAX_STATEMENT_SIZE,"update TRACING_TB set "); 

	if(dreTraceReq->has_enabletrace())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ENABLE_TRACING=%d,",dreTraceReq->enabletrace());
	}


	pStatement[strlen(pStatement) -1] = ' ';

	DLOG_NONE(" < %s \n",__FUNCTION__);
}

DbStatus_e TracingTPBQuery::sql_Tracing_Payload_Validation(TraceReq *dreTraceReq)
{
	if(!dreTraceReq->has_enabletrace())
	{
		DLOG_ERROR("Primary Key componenet Name is not set in the request");
		return ENABLE_TRACECONFIG_ERR_MANDATORY_PARAM_ENABLE_MISSING;	
	}
	
	return DRE_DB_SUCCESS;
}

DbStatus_e TracingTPBQuery::sql_Tracing_Check_All_Invalid(TraceReq *dreTraceReq)
{

	DLOG_INFO("In the Request, No Fields are Set for Operation");
	return DRE_DB_SUCCESS;
}
