#ifndef TRACING_FILTER_T_PB_QUERY_H
#define TRACING_FILTER_T_PB_QUERY_H


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


class TracingFilterTPBQuery
{
    public:
        void sql_TracingFilter_Create_Check_Modifcation_Query(TraceConfig *traceReq,char *pStatement);
        void sql_TracingFilter_Create_OrderBy_Select_Query(TraceConfig *dreTraceReq,char *pStatement);
        void sql_TracingFilter_Create_Add_Query(TraceConfig *traceReq,char *pStatement);
        void sql_TracingFilter_Create_Mod_Query(TraceConfig *traceReq,char *pStatement);
        void sql_TracingFilter_Create_Delete_Query(TraceConfig *traceReq,char *pStatement);
        DbStatus_e sql_TracingFilter_Payload_Validation(TraceConfig *traceReq8);
        void sql_TracingFilter_Create_Select_Query(TraceConfig *traceReq,char *pStatement);
        DbStatus_e sql_TracingFilter_Check_All_Invalid(TraceConfig *traceReq);
};
#endif
