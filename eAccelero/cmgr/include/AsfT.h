#ifndef ASFT_QUERY_H
#define ASFT_QUERY_H


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


class AsfTQuery
{
	protected:
		char sAsfTableName[MAX_TABLENAME_LEN];
		char sAsfFieldNames[MAX_FIELDNAME_LEN];	
		void sql_Asf_Create_Check_Modifcation_Query(DreASFAppGroupPayload *AsfReq,char *pStatement);
		void sql_Asf_Create_Add_Query(DreASFAppGroupPayload *AsfReq,char *pStatement);
		void sql_Asf_Create_Mod_Query(DreASFAppGroupPayload *AsfReq,char *pStatement);
		void sql_Asf_Create_Delete_Query(DreASFAppGroupPayload *AsfReq,char *pStatement);
		DbStatus_e sql_Asf_Payload_Validation(DreASFAppGroupPayload *AsfReq);
        	void sql_Asf_Create_Select_Query(DreASFAppGroupPayload *AsfReq,char *pStatement);
		DbStatus_e sql_Asf_Check_All_Invalid(DreASFAppGroupPayload *AsfReq);
		void set_Asf_Set_TableName();
		void set_Asf_Set_FieldName();
};
#endif
