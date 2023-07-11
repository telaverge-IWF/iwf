#include <CMgrDbInterface.h>

using namespace std;

void TracingFilterTPBQuery::sql_TracingFilter_Create_Check_Modifcation_Query(TraceConfig *dreTraceReq,char *pStatement)
{

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__);

	snprintf(pStatement,MAX_STATEMENT_SIZE,"select FILTER_ID from TRACING_FILTER_TB ");
	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

	if(dreTraceReq->has_filtername())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"FILTER_NAME=\"%s\" and ",dreTraceReq->filtername().c_str());
	}
	
	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
	}

    DLOG_NONE(" < %s ",__FUNCTION__);

}

void TracingFilterTPBQuery::sql_TracingFilter_Create_OrderBy_Select_Query(TraceConfig *dreTraceReq,char *pStatement)
{
    DLOG_NONE(" > %s \n",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select FILTER_ID from TRACING_FILTER_TB where FILTER_ID between 1 and %d order by FILTER_ID",MAX_FILTER_ID);

    DLOG_NONE(" > %s \n",__FUNCTION__);
}

void TracingFilterTPBQuery::sql_TracingFilter_Create_Add_Query(TraceConfig *dreTraceReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  


    DLOG_NONE(" > %s \n",__FUNCTION__);

	snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into TRACING_FILTER_TB "); 
	snprintf(sFieldName,MAX_STATEMENT_SIZE,"(FILTER_NAME");	
	snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(\"%s\"",dreTraceReq->filtername().c_str());

    if(dreTraceReq->has_filterid())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",FILTER_ID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreTraceReq->filterid());
    }

	if(dreTraceReq->has_rule())
	{
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",RULE");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",\"%s\"",dreTraceReq->rule().c_str());
	}
	
	if(dreTraceReq->has_priority())
	{
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PRIORITY");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreTraceReq->priority());
	}
	
	if(dreTraceReq->has_expireduration())
	{
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",EXP_DURATION");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreTraceReq->expireduration());
	}
	
	if(dreTraceReq->has_expiremessages())
	{
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",EXP_MESSAGES");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreTraceReq->expiremessages());
	}
	
	if(dreTraceReq->has_filterstatus())
	{
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",FILTER_STATUS");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreTraceReq->filterstatus());
	}
	
	if(dreTraceReq->has_loglevel())
	{
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",LOG_LEVEL");
		snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreTraceReq->loglevel());
	}

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

	snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);
	DLOG_NONE(" < %s \n",__FUNCTION__);
}

void TracingFilterTPBQuery::sql_TracingFilter_Create_Delete_Query(TraceConfig *dreTraceReq,char *pStatement)
{

	int iFlag 					= 0;
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	DLOG_NONE(" > %s ",__FUNCTION__);


	snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from TRACING_FILTER_TB "); 
	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

	if(dreTraceReq->has_filtername())
	{
		iFlag = 1;
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"FILTER_NAME=\"%s\" and ",dreTraceReq->filtername().c_str());
	}
	
	if(iFlag)
	{
		sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
	}

    DLOG_NONE(" < %s \n",__FUNCTION__);
}

void TracingFilterTPBQuery::sql_TracingFilter_Create_Select_Query(TraceConfig *dreTraceReq,char *pStatement)
{

	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	DLOG_NONE(" > %s \n",__FUNCTION__);


	snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from TRACING_FILTER_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where FILTER_ID between 1 and %d and ",MAX_FILTER_ID);

	if(dreTraceReq->has_filtername())
	{
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"FILTER_NAME=\"%s\" and ",dreTraceReq->filtername().c_str());
	}

	if(dreTraceReq->has_rule())
	{
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RULE=\"%s\" and ",dreTraceReq->rule().c_str());
	}

	if(dreTraceReq->has_priority())
	{
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PRIORITY=%d and ",dreTraceReq->priority());
	}

	if(dreTraceReq->has_expireduration())
	{
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"EXP_DURATION=%d and ",dreTraceReq->expireduration());
	}

	if(dreTraceReq->has_expiremessages())
	{
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"EXP_MESSAGES=%d and ",dreTraceReq->expiremessages());
	}

	if(dreTraceReq->has_filterstatus())
	{
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"FILTER_STATUS=%d and ",dreTraceReq->filterstatus());
	}

	if(dreTraceReq->has_loglevel())
	{
		snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LOG_LEVEL=%d and ",dreTraceReq->loglevel());
	}


    sWhereStatement[strlen(sWhereStatement) - 4] = '\0';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);

    DLOG_NONE(" < %s \n",__FUNCTION__);
}

void TracingFilterTPBQuery::sql_TracingFilter_Create_Mod_Query(TraceConfig *dreTraceReq,char *pStatement)
{

    DLOG_NONE(" > %s \n",__FUNCTION__);


	snprintf(pStatement,MAX_STATEMENT_SIZE,"update TRACING_FILTER_TB set "); 

    if(dreTraceReq->has_filterid())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"FILTER_ID=%d,",dreTraceReq->filterid());
    }

	if(dreTraceReq->has_rule())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"RULE=\"%s\",",dreTraceReq->rule().c_str());
	}

	if(dreTraceReq->has_priority())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PRIORITY=%d,",dreTraceReq->priority());
	}

	if(dreTraceReq->has_expireduration())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"EXP_DURATION=%d,",dreTraceReq->expireduration());
	}


	if(dreTraceReq->has_expiremessages())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"EXP_MESSAGES=%d,",dreTraceReq->expiremessages());
	}

	if(dreTraceReq->has_filterstatus())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"FILTER_STATUS=%d,",dreTraceReq->filterstatus());
	}

	if(dreTraceReq->has_loglevel())
	{
		snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LOG_LEVEL=%d,",dreTraceReq->loglevel());
	}

    pStatement[strlen(pStatement) -1] = ' ';

	snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where FILTER_NAME=\"%s\"",dreTraceReq->filtername().c_str());


    DLOG_NONE(" < %s \n",__FUNCTION__);
}

DbStatus_e TracingFilterTPBQuery::sql_TracingFilter_Payload_Validation(TraceConfig *dreTraceReq)
{
    if(!dreTraceReq->has_filtername())
    {
        DLOG_ERROR("Primary Key filetername Name is not set in the request");
        return ERROR_TRACECONFIG_MANDATORY_PARAM_ENABLE_MISSING;    
    }

    return DRE_DB_SUCCESS;
}

DbStatus_e TracingFilterTPBQuery::sql_TracingFilter_Check_All_Invalid(TraceConfig *dreTraceReq)
{

    if(dreTraceReq->has_rule())
    {
        return DRE_DB_FAIL;
    }

    if(dreTraceReq->has_priority())
    {
        return DRE_DB_FAIL;
    }


    if(dreTraceReq->has_expireduration())
    {
        return DRE_DB_FAIL;
    }


    if(dreTraceReq->has_expiremessages())
    {
        return DRE_DB_FAIL;
    }


    if(dreTraceReq->has_filterstatus())
    {
        return DRE_DB_FAIL;
    }


    if(dreTraceReq->has_loglevel())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
