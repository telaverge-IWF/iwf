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

void TrustedCAConfigTPBQuery::sql_TrustedCAConfig_Create_Check_Modifcation_Query(TrustedCAConfiguration *TrustedCAConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select CA_ID from TRUSTED_CA_TB where CA_FILE = '%s'",TrustedCAConfigReq->cafile().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void TrustedCAConfigTPBQuery::sql_TrustedCAConfig_Create_Add_Query(TrustedCAConfiguration *TrustedCAConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into TRUSTED_CA_TB "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"("); 
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");


    if(TrustedCAConfigReq->has_cafile())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"CA_FILE,"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",TrustedCAConfigReq->cafile().c_str());
    }


    if(TrustedCAConfigReq->has_crlfile())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"CRL_FILE,"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",TrustedCAConfigReq->crlfile().c_str());
    }

    sFieldName[strlen(sFieldName) - 1] = ' ';
    sFieldValue[strlen(sFieldValue) - 1] = ' ';

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")"); 
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")"); 

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" < %s ",__FUNCTION__);


}

void TrustedCAConfigTPBQuery::sql_TrustedCAConfig_Create_Delete_Query(TrustedCAConfiguration *TrustedCAConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from TRUSTED_CA_TB where CA_FILE = '%s'",TrustedCAConfigReq->cafile().c_str()); 
    DLOG_NONE(" < %s ",__FUNCTION__);

}
void TrustedCAConfigTPBQuery::sql_TrustedCAConfig_Create_DeleteAssoc_Query(TrustedCAConfiguration *TrustedCAConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"update TRUSTED_CA_TB set CRL_FILE = NULL where CA_FILE = '%s'",TrustedCAConfigReq->cafile().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}
void TrustedCAConfigTPBQuery::sql_TrustedCAConfig_Create_Mod_Query(TrustedCAConfiguration *TrustedCAConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update TRUSTED_CA_TB set "); 

#if 0
    if(TrustedCAConfigReq->has_cafile())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"CA_FILE='%s',",TrustedCAConfigReq->cafile().c_str());
    }
#endif
    if(TrustedCAConfigReq->has_crlfile())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"CRL_FILE='%s',",TrustedCAConfigReq->crlfile().c_str());
    }


    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where CA_FILE='%s'",TrustedCAConfigReq->cafile().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}
DbStatus_e TrustedCAConfigTPBQuery::sql_TrustedCAConfig_Payload_Validation(TrustedCAConfiguration *TrustedCAConfigReq)
{
    if (!TrustedCAConfigReq->has_cafile())
    {
        DLOG_ERROR("Primary Key CA File is not set in the request");
        return ERR_TRUSTEDCA_MANDATORY_PARAM_CAFILE_MISSING;    
    }

    return DRE_DB_SUCCESS;
}

void TrustedCAConfigTPBQuery::sql_TrustedCAConfig_Create_Select_Query(TrustedCAConfiguration *TrustedCAConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from TRUSTED_CA_TB"); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(TrustedCAConfigReq->has_cafile())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"CA_FILE='%s' and ",TrustedCAConfigReq->cafile().c_str());
    }

    if(TrustedCAConfigReq->has_crlfile())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"CRL_FILE='%s' and ",TrustedCAConfigReq->crlfile().c_str());
    }
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }


    DLOG_NONE(" < %s ",__FUNCTION__);

}

DbStatus_e TrustedCAConfigTPBQuery::sql_TrustedCAConfig_Check_All_Invalid(TrustedCAConfiguration *TrustedCAConfigReq)
{

    if(TrustedCAConfigReq->has_cafile())
    {
        return DRE_DB_FAIL;
    }

    if(TrustedCAConfigReq->has_crlfile())
    {
        return DRE_DB_FAIL;
    }


    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
