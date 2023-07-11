/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/


#include <CMgrDbInterface.h>

using namespace std;

void ASFConfigTPBQuery::sql_ASFConfig_Create_Check_Modifcation_Query(ASFConfiguration *AsfConfigReq,char *pStatement)
{
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from ASF_CONFIGURATION_TB");
}

void ASFConfigTPBQuery::sql_ASFConfig_Create_Add_Query(ASFConfiguration *AsfConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into ASF_CONFIGURATION_TB "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"("); 
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");

    if(AsfConfigReq->has_appresponsetimeout())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"APP_RESPONSE_TIMEOUT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d",AsfConfigReq->appresponsetimeout());
    }   

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

}

void ASFConfigTPBQuery::sql_ASFConfig_Create_Delete_Query(ASFConfiguration *AsfConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from ASF_CONFIGURATION_TB ");

}

void ASFConfigTPBQuery::sql_ASFConfig_Create_Mod_Query(ASFConfiguration *AsfConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update ASF_CONFIGURATION_TB set "); 

    if(AsfConfigReq->has_appresponsetimeout())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"APP_RESPONSE_TIMEOUT=%d,",AsfConfigReq->appresponsetimeout());
    }

}

DbStatus_e ASFConfigTPBQuery::sql_ASFConfig_Payload_Validation(ASFConfiguration *AsfConfigReq)
{
    return DRE_DB_SUCCESS;
}

void ASFConfigTPBQuery::sql_ASFConfig_Create_Select_Query(ASFConfiguration *AsfConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from ASF_CONFIGURATION_TB"); 

}

DbStatus_e ASFConfigTPBQuery::sql_ASFConfig_Check_All_Invalid(ASFConfiguration *AsfConfigReq)
{

    if(AsfConfigReq->has_appresponsetimeout())
    {
        return DRE_DB_FAIL;
    }

    return DRE_DB_SUCCESS;
}
