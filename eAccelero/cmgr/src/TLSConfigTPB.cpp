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

void TLSConfigTPBQuery::sql_TLSConfig_Create_Check_Modifcation_Query(TLSConfig *TLSConfigReq,char *pStatement)
{
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from TLS_CONFIG ");
}

void TLSConfigTPBQuery::sql_TLSConfig_Create_Add_Query(TLSConfig *TLSConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE] = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into TLS_CONFIG "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"("); 
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");


    if(TLSConfigReq->has_enableidverification())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"IDENTITY_VERIFICATION_ENABLE,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",TLSConfigReq->enableidverification());
    }

    if(TLSConfigReq->has_enablecrlverification())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"CRL_VERIFICATION_ENABLE,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",TLSConfigReq->enablecrlverification());
    }

    sFieldName[strlen(sFieldName) - 1] = ' ';
    sFieldValue[strlen(sFieldValue) - 1] = ' ';

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" < %s ",__FUNCTION__);

}

void TLSConfigTPBQuery::sql_TLSConfig_Create_Delete_Query(TLSConfig *TLSConfigReq,char *pStatement)
{
    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from TLS_CONFIG "); 
}

void TLSConfigTPBQuery::sql_TLSConfig_Create_Mod_Query(TLSConfig *TLSConfigReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update TLS_CONFIG set "); 

    if(TLSConfigReq->has_enableidverification())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IDENTITY_VERIFICATION_ENABLE=%d,",TLSConfigReq->enableidverification());
    }

    if(TLSConfigReq->has_enablecrlverification())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"CRL_VERIFICATION_ENABLE=%d,",TLSConfigReq->enablecrlverification());
    }
    pStatement[strlen(pStatement) -1] = ' ';

    //  snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where REALM_NAME='%s'",TLSConfigReq->realmname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e TLSConfigTPBQuery::sql_TLSConfig_Payload_Validation(TLSConfig *TLSConfigReq)
{

#if 0
    if (!TLSConfigReq->has_realmname())
    {
        DLOG_ERROR("Primary Key Realm is not set in the request");
        return ERR_REALM_MANDATORY_PARAM_REALMNAME_MISSING; 
    }
#endif
    return DRE_DB_SUCCESS;
}

void TLSConfigTPBQuery::sql_TLSConfig_Create_Select_Query(TLSConfig *TLSConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from TLS_CONFIG"); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(TLSConfigReq->has_enableidverification())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IDENTITY_VERIFICATION_ENABLE=%d and ",TLSConfigReq->enableidverification());
    }
    if(TLSConfigReq->has_enablecrlverification())
    {   
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"CRL_VERIFICATION_ENABLE=%d and ",TLSConfigReq->enablecrlverification());
    }
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }


    DLOG_NONE(" < %s ",__FUNCTION__);

}

DbStatus_e TLSConfigTPBQuery::sql_TLSConfig_Check_All_Invalid(TLSConfig *TLSConfigReq)
{


    if(TLSConfigReq->has_enableidverification())
    {
        return DRE_DB_FAIL;
    }
    if(TLSConfigReq->has_enablecrlverification())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
