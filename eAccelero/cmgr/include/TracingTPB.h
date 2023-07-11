#ifndef TRACING_T_PB_QUERY_H
#define TRACING_T_PB_QUERY_H


#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <driver.h>
#include <string.h>
#include <stdio.h>

#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <CMAPICMgr.h>
#include <CMAPICommon.h>

#include <CommonStructure.h>
#include <config.h>


class TracingTPBQuery
{
	public:
		void sql_Tracing_Create_Check_Modifcation_Query(TraceReq *traceReq,char *pStatement);
		void sql_Tracing_Create_Add_Query(TraceReq *traceReq,char *pStatement);
		void sql_Tracing_Create_Mod_Query(TraceReq *traceReq,char *pStatement);
		void sql_Tracing_Create_Delete_Query(TraceReq *traceReq,char *pStatement);
		DbStatus_e sql_Tracing_Payload_Validation(TraceReq *traceReq);
        	void sql_Tracing_Create_Select_Query(TraceReq *traceReq,char *pStatement);
		DbStatus_e sql_Tracing_Check_All_Invalid(TraceReq *traceReq);
};
#endif
