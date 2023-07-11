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

void LocalHostConfigTPBQuery::sql_LocalHost_Create_Validation_Query(LocalHost *dreLocalHostReq,char *pStatement)
{
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select LocalHostConfigID from  LocalHostConfigT where RealmName='%s' and HostName='%s'",dreLocalHostReq->realmname().c_str(),dreLocalHostReq->localhostname().c_str());
}

void LocalHostConfigTPBQuery::sql_LocalHost_Create_Check_Modifcation_Query(LocalHost *dreLocalHostReq,char *pStatement)
{
#if 0
    if(dreLocalHostReq->has_realmname() && dreLocalHostReq->has_localhostname())
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select LocalHostConfigID from  LocalHostConfigT where RealmName='%s' and HostName='%s'",dreLocalHostReq->realmname().c_str(),dreLocalHostReq->localhostname().c_str());
    else
#endif
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select LocalHostConfigID from  LocalHostConfigT");
}

void LocalHostConfigTPBQuery::sql_LocalHost_Create_Add_Query(LocalHost *dreLocalHostReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]     = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE("> %s",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into LocalHostConfigT "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(HostName,RealmName");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s','%s'",dreLocalHostReq->localhostname().c_str(),dreLocalHostReq->realmname().c_str());


    if(dreLocalHostReq->has_authsessionlifetime())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",AuthLifeTime");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreLocalHostReq->authsessionlifetime());
    }

    if(dreLocalHostReq->has_authsessiongraceperiod())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",AuthGraceTime");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreLocalHostReq->authsessiongraceperiod());
    }

    if(dreLocalHostReq->has_authsessiontimeout())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",AuthTimeOut");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreLocalHostReq->authsessiontimeout());
    }

    if(dreLocalHostReq->has_acctsessioninteriminterval())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",AcctInterim");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreLocalHostReq->acctsessioninteriminterval());
    }

    if(dreLocalHostReq->has_acctsessiontimeout())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",AcctTimeOut");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",dreLocalHostReq->acctsessiontimeout());
    }


    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE("< %s",__FUNCTION__);
}

void LocalHostConfigTPBQuery::sql_LocalHost_Create_Mod_Query(LocalHost *dreLocalHostReq,char *pStatement)
{
    DLOG_NONE("> %s",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update LocalHostConfigT set "); 

    if(dreLocalHostReq->has_authsessionlifetime())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"AuthLifeTime=%d,",dreLocalHostReq->authsessionlifetime());

    }


    if(dreLocalHostReq->has_authsessiongraceperiod())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"AuthGraceTime=%d,",dreLocalHostReq->authsessiongraceperiod());

    }


    if(dreLocalHostReq->has_authsessiontimeout())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"AuthTimeOut=%d,",dreLocalHostReq->authsessiontimeout());

    }


    if(dreLocalHostReq->has_acctsessioninteriminterval())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"AcctInterim=%d,",dreLocalHostReq->acctsessioninteriminterval());

    }


    if(dreLocalHostReq->has_acctsessiontimeout())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"AcctTimeOut=%d,",dreLocalHostReq->acctsessiontimeout());

    }

    //pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," HostName='%s', RealmName='%s'",dreLocalHostReq->localhostname().c_str(),dreLocalHostReq->realmname().c_str());

    DLOG_NONE("< %s",__FUNCTION__);

}

void LocalHostConfigTPBQuery::sql_LocalHost_Create_Delete_Query(LocalHost *dreLocalHostReq,char *pStatement)
{
    DLOG_NONE("> %s",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from LocalHostConfigT where HostName='%s' and RealmName='%s'",dreLocalHostReq->localhostname().c_str(),dreLocalHostReq->realmname().c_str()); 

    DLOG_NONE("< %s",__FUNCTION__);
}

DbStatus_e LocalHostConfigTPBQuery::sql_LocalHost_Payload_Validation(LocalHost *dreLocalHostReq)
{
    if(!dreLocalHostReq->has_localhostname())
    {
        DLOG_ERROR("Primary Key Localhost Name is not set in the request");
        return ERR_HOST_MANDATORY_PARAM_HOSTNAME_MISSING;   
    }
    else if(!dreLocalHostReq->has_realmname())
    {
        DLOG_ERROR("Primary Key Realm is not set in the request");
        return ERR_HOST_MANDATORY_PARAM_REALMNAME_MISSING;
    }
    return DRE_DB_SUCCESS;
}

////////////////////////////////////////////*****************************************************************

void LocalHostConfigTPBQuery::sql_LocalHost_Create_Select_Query(LocalHost *dreLocalHostReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    DLOG_NONE("> %s",__FUNCTION__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from LocalHostConfigT "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");


    if(dreLocalHostReq->has_localhostname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"HostName='%s' and ",dreLocalHostReq->localhostname().c_str());
    }

    if(dreLocalHostReq->has_realmname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"RealmName='%s' and ",dreLocalHostReq->realmname().c_str());
    }


    if(dreLocalHostReq->has_authsessionlifetime())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"AuthLifeTime=%d and ",dreLocalHostReq->authsessionlifetime());
    }

    if(dreLocalHostReq->has_authsessiongraceperiod())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"AuthGraceTime=%d and ",dreLocalHostReq->authsessiongraceperiod());
    }

    if(dreLocalHostReq->has_authsessiontimeout())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"AuthTimeOut=%d and ",dreLocalHostReq->authsessiontimeout());
    }

    if(dreLocalHostReq->has_acctsessioninteriminterval())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"AcctInterim=%d and ",dreLocalHostReq->acctsessioninteriminterval());
    }

    if(dreLocalHostReq->has_acctsessiontimeout())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"AcctTimeOut=%d and ",dreLocalHostReq->acctsessiontimeout());
    }


    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE("< %s",__FUNCTION__);
}

DbStatus_e LocalHostConfigTPBQuery::sql_LocalHost_Check_All_Invalid(LocalHost *dreLocalHostPayload)
{


    if(dreLocalHostPayload->has_acctsessioninteriminterval())
    {
        return DRE_DB_FAIL;
    }

    if(dreLocalHostPayload->has_acctsessiontimeout())
    {
        return DRE_DB_FAIL;
    }

    if(dreLocalHostPayload->has_authsessionlifetime())
    {
        return DRE_DB_FAIL;
    }

    if(dreLocalHostPayload->has_authsessiongraceperiod())
    {
        return DRE_DB_FAIL;
    }

    if(dreLocalHostPayload->has_authsessiontimeout())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}

