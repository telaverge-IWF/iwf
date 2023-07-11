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

void CipherSuiteConfigTPBQuery::sql_CipherSuiteConfig_Create_Check_Modifcation_Query(TLSCipherConfig *CipherConfigReq,char *pStatement)
{
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select CIPHER_SUITE_ID from CIPHER_SUITE_TB where CIPHER_SUITE_NAME ='%s'",CipherConfigReq->ciphersuitename().c_str());
}

void CipherSuiteConfigTPBQuery::sql_CipherSuiteConfig_Create_Add_Query(TLSCipherConfig *CipherConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into CIPHER_SUITE_TB "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"("); 
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");


    if(CipherConfigReq->has_ciphersuitename())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",CIPHER_SUITE_NAME");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",CipherConfigReq->ciphersuitename().c_str());
    }

    if(CipherConfigReq->has_enableciphersuite())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",Enable");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",CipherConfigReq->enableciphersuite());
    }



    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" < %s ",__FUNCTION__);


}

void CipherSuiteConfigTPBQuery::sql_CipherSuiteConfig_Create_Delete_Query(TLSCipherConfig *CipherConfigReq,char *pStatement)
{
    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from CIPHER_SUITE_TB where CIPHER_SUITE_NAME ='%s'",CipherConfigReq->ciphersuitename().c_str()); 
}

void CipherSuiteConfigTPBQuery::sql_CipherSuiteConfig_Create_Mod_Query(TLSCipherConfig *CipherConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update CIPHER_SUITE_TB set "); 


    if(CipherConfigReq->has_enableciphersuite())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"Enable=%d,",CipherConfigReq->enableciphersuite());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where CIPHER_SUITE_NAME='%s'",CipherConfigReq->ciphersuitename().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CipherSuiteConfigTPBQuery::sql_CipherSuiteConfig_Payload_Validation(TLSCipherConfig *CipherConfigReq)
{
#if 0
    if (!CipherConfigReq->has_realmname())
    {
        DLOG_ERROR("Primary Key Realm is not set in the request");
        return ERR_REALM_MANDATORY_PARAM_REALMNAME_MISSING; 
    }

#endif
    return DRE_DB_SUCCESS;
}

void CipherSuiteConfigTPBQuery::sql_CipherSuiteConfig_Create_Select_Query(TLSCipherConfig *CipherConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from CIPHER_SUITE_TB"); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(CipherConfigReq->has_ciphersuitename())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"CIPHER_SUITE_NAME='%s' and ",CipherConfigReq->ciphersuitename().c_str());
    }

    if(CipherConfigReq->has_enableciphersuite())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"Enable=%d and ",CipherConfigReq->enableciphersuite());
    }
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }


    DLOG_NONE(" < %s ",__FUNCTION__);

}

DbStatus_e CipherSuiteConfigTPBQuery::sql_CipherSuiteConfig_Check_All_Invalid(TLSCipherConfig *CipherConfigReq)
{


    if(CipherConfigReq->has_ciphersuitename())
    {
        return DRE_DB_FAIL;
    }

    if(CipherConfigReq->has_enableciphersuite())
    {
        return DRE_DB_FAIL;
    }


    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
