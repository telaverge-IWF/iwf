#ifndef ASF_FEATURET_QUERY_H
#define ASF_FEATURET_QUERY_H


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

#include <CommonStructure.h>
#include <config.h>


class AsfFeatureTQuery
{
	protected:
		char sAsfFeatureTableName[MAX_TABLENAME_LEN];
		char sAsfFeatureFieldNames[MAX_FIELDNAME_LEN];	
		void sql_AsfFeature_Create_Check_Modifcation_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement);
		void sql_AsfFeature_Create_Add_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement);
		void sql_AsfFeature_Create_Mod_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement);
		void sql_AsfFeature_Create_Delete_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement);
		DbStatus_e sql_AsfFeature_Payload_Validation(DreASFConfigPayload *AsfConfigReq);
        	void sql_AsfFeature_Create_Select_Query(DreASFConfigPayload *AsfConfigReq,char *pStatement);
		DbStatus_e sql_AsfFeature_Check_All_Invalid(DreASFConfigPayload *AsfConfigReq);
		void set_AsfFeature_Set_TableName();
		void set_AsfFeature_Set_FieldName();
};
#endif
