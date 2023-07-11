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

void DictionaryTPBQuery::sql_DictionaryConfig_Create_Validation_Query(Dictionary *DictionaryReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select DICTIONARY_ID,APP_TYPE from DICTIONARY_TB where  DICTIONARY_NAME = '%s'",DictionaryReq->dictionaryname().c_str());
}

void DictionaryTPBQuery::sql_DictionaryConfig_Create_Check_Modifcation_Query(Dictionary *DictionaryReq,char *pStatement)
{

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from DICTIONARY_TB");
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}

void DictionaryTPBQuery::sql_DictionaryConfig_Create_Add_Query(Dictionary *DictionaryReq,char *pStatement)
{
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}


void DictionaryTPBQuery::sql_DictionaryConfig_Create_Mod_Query(Dictionary *DictionaryReq,char *pStatement)
{

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}

void DictionaryTPBQuery::sql_DictionaryConfig_Create_Delete_Query(Dictionary *DictionaryReq,char *pStatement)
{
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}

DbStatus_e DictionaryTPBQuery::sql_DictionaryConfig_Payload_Validation(Dictionary *DictionaryReq)
{

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
    return DRE_DB_SUCCESS;
}


void DictionaryTPBQuery::sql_DictionaryConfig_Create_Select_Query(Dictionary *DictionaryReq,char *pStatement)
{
#if 0
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
#endif

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from  DICTIONARY_TB order by INTERFACE_NAME");
}



DbStatus_e DictionaryTPBQuery::sql_DictionaryConfig_Check_All_Invalid(Dictionary *DictionaryReq)
{
    return DRE_DB_SUCCESS;
}


// New Methods

void DictionaryTPBQuery::sql_DictionaryConfig_Create_Check_Modifcation_Query(DictionaryConfig *pDictionaryConfigReq, char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select DICTIONARY_ID, APP_TYPE from DICTIONARY_TB where DICTIONARY_NAME = '%s'",pDictionaryConfigReq->dictionaryname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}


void DictionaryTPBQuery::sql_DictionaryConfig_Create_Mod_Query(DictionaryConfig *pDictionaryConfigReq, char *pStatement)
{
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update DICTIONARY_TB set ");

    if(pDictionaryConfigReq->has_isdictenabled())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"IS_DICTIONARY_ENABLED=%d,",pDictionaryConfigReq->isdictenabled());
    }

    if(pDictionaryConfigReq->has_isdefaultdict())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"IS_DEFAULT_DICTIONARY=%d,",pDictionaryConfigReq->isdefaultdict());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where DICTIONARY_NAME='%s'",pDictionaryConfigReq->dictionaryname().c_str());

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}

void DictionaryTPBQuery::sql_DictionaryConfig_Create_Select_Query(DictionaryConfig *pDictionaryConfigReq, char *pStatement)
{
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from  DICTIONARY_TB");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pDictionaryConfigReq->has_dictionaryname())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"DICTIONARY_NAME='%s' and ",pDictionaryConfigReq->dictionaryname().c_str());
    }

    if(pDictionaryConfigReq->has_dictionaryid())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"DICTIONARY_ID=%d and ",pDictionaryConfigReq->dictionaryid());
    }

    if(pDictionaryConfigReq->has_applicationid())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"APP_ID=%d and ",pDictionaryConfigReq->applicationid());
    }

    if(pDictionaryConfigReq->has_isdefaultdict())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"IS_DEFAULT_DICTIONARY=%d and ",pDictionaryConfigReq->isdefaultdict());
    }

    if(pDictionaryConfigReq->has_interfacename())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"INTERFACE_NAME='%s' and ",pDictionaryConfigReq->interfacename().c_str());
    }

    if(pDictionaryConfigReq->has_releasenumber())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"RELEASE_NUMBER='%s' and ",pDictionaryConfigReq->releasenumber().c_str());
    }

    if(!iFlag)
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from  DICTIONARY_TB order by INTERFACE_NAME");
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}
#if 0
void DictionaryTPBQuery::sql_DictionaryConfig_Create_Select_Individual_Query(DictionaryConfig *pDictionaryConfigReq, char *pStatement)
{
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    if(pDictionaryConfigReq->has_dictionaryid())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from  DICTIONARY_TB where DICTIONARY_ID = '%d'",pDictionaryConfigReq->dictionaryid());
    }

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}
#endif
