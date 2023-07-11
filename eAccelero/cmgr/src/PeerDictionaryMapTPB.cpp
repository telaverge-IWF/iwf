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

void PeerDictionaryMapTPBQuery::sql_PeerDictionaryMap_Create_Validation_Query_for_Dictionary(PeerConfig *drePeerConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" < %s ",__FUNCTION__);
    string sDictionaryName = "";

    DLOG_DEBUG("drePeerConfigReq->dictionaryname_size() = %d, iIndex= %d",drePeerConfigReq->dictionaryname_size(),iIndex);

    if(drePeerConfigReq->dictionaryname_size() > iIndex && iIndex > -1)
    {
        sDictionaryName = drePeerConfigReq->dictionaryname(iIndex);
    }
    else
    {
        DLOG_WARNING("dictionaryname Object will be NULL, drePeerConfigReq->dictionaryname_size() = %d, iIndex= %d",drePeerConfigReq->dictionaryname_size(),iIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    snprintf(pStatement ,MAX_STATEMENT_SIZE,"select DICTIONARY_ID,APP_TYPE from DICTIONARY_TB where DICTIONARY_NAME = '%s'",sDictionaryName.c_str());

    DLOG_NONE(" > %s ",__FUNCTION__);
}

void PeerDictionaryMapTPBQuery::sql_PeerDictionaryMap_Create_Validation_Query_for_Peer(PeerConfig *drePeerConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement ,MAX_STATEMENT_SIZE,"select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s'",drePeerConfigReq->peerhostname().c_str(),drePeerConfigReq->realm().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void PeerDictionaryMapTPBQuery::sql_PeerDictionaryMap_Create_Check_Modifcation_Query(PeerConfig *drePeerConfigReq,char *pStatement,int iIndex)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    string sDictionaryName = "";

    DLOG_DEBUG("drePeerConfigReq->dictionaryname_size() = %d, iIndex= %d",drePeerConfigReq->dictionaryname_size(),iIndex);

    if(drePeerConfigReq->dictionaryname_size() > iIndex && iIndex > -1)
    {
        sDictionaryName = drePeerConfigReq->dictionaryname(iIndex);
    }
    else
    {
        DLOG_WARNING("dictionaryname Object will be NULL, drePeerConfigReq->dictionaryname_size() = %d, iIndex= %d",drePeerConfigReq->dictionaryname_size(),iIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }



    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PEER_DICTIONARY_ASSN_ID from PEER_DICTIONARY_MAP_TB where PEER_ID=(select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s') and DICTIONARY_ID = (select DICTIONARY_ID from DICTIONARY_TB where DICTIONARY_NAME = '%s')",drePeerConfigReq->peerhostname().c_str(),drePeerConfigReq->realm().c_str(),sDictionaryName.c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}


void PeerDictionaryMapTPBQuery::sql_PeerDictionaryMap_Create_Add_Query(PeerConfig *drePeerConfigReq,char *pStatement,int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE]     = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" < %s ",__FUNCTION__);
    string sDictionaryName = "";

    DLOG_DEBUG("drePeerConfigReq->dictionaryname_size() = %d, iIndex= %d",drePeerConfigReq->dictionaryname_size(),iIndex);

    if(drePeerConfigReq->dictionaryname_size() > iIndex && iIndex > -1)
    {
        sDictionaryName = drePeerConfigReq->dictionaryname(iIndex);
    }
    else
    {
        DLOG_WARNING("dictionaryname Object will be NULL, drePeerConfigReq->dictionaryname_size() = %d, iIndex= %d",drePeerConfigReq->dictionaryname_size(),iIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into PEER_DICTIONARY_MAP_TB ");
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(PEER_ID");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"((select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s')",drePeerConfigReq->peerhostname().c_str(),drePeerConfigReq->realm().c_str());

    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",DICTIONARY_ID");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",(select DICTIONARY_ID from DICTIONARY_TB where DICTIONARY_NAME = '%s')",sDictionaryName.c_str());

    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" > %s ",__FUNCTION__);

}


void PeerDictionaryMapTPBQuery::sql_PeerDictionaryMap_Create_Mod_Query(PeerConfig *drePeerConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" < %s ",__FUNCTION__);

#if 0
    string sDictionaryName = drePeerConfigReq->dictionaryname(iIndex);
    snprintf(pStatement,MAX_STATEMENT_SIZE,"update PEER_DICTIONARY_MAP_TB set ");
    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"DICTIONARY_ID=%d,",sDictionaryName);


    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where PEER_ID=((select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s')",drePeerConfigReq->peerhostname().c_str(),drePeerConfigReq->realm().c_str());

#endif

    DLOG_NONE("%s:%d Modification is not possible\n",__FUNCTION__,__LINE__);
    DLOG_NONE(" > %s ",__FUNCTION__);
}


void PeerDictionaryMapTPBQuery::sql_PeerDictionaryMap_Create_Delete_Query(PeerConfig *drePeerConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE(" < %s ",__FUNCTION__);

    string sDictionaryName = "";

    DLOG_DEBUG("drePeerConfigReq->dictionaryname_size() = %d, iIndex= %d",drePeerConfigReq->dictionaryname_size(),iIndex);

    if(drePeerConfigReq->dictionaryname_size() > iIndex && iIndex > -1)
    {
        sDictionaryName = drePeerConfigReq->dictionaryname(iIndex);
    }
    else
    {
        DLOG_WARNING("dictionaryname Object will be NULL, drePeerConfigReq->dictionaryname_size() = %d, iIndex= %d",drePeerConfigReq->dictionaryname_size(),iIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from PEER_DICTIONARY_MAP_TB where PEER_ID=(select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s') and DICTIONARY_ID = (select DICTIONARY_ID from DICTIONARY_TB where DICTIONARY_NAME = '%s')",drePeerConfigReq->peerhostname().c_str(),drePeerConfigReq->realm().c_str(),sDictionaryName.c_str());


    DLOG_NONE(" > %s ",__FUNCTION__);
}


DbStatus_e PeerDictionaryMapTPBQuery::sql_PeerDictionaryMap_Payload_Validation(PeerConfig *drePeerConfigReq,int iIndex)
{

    if(!drePeerConfigReq->has_peerhostname())
    {
        DLOG_ERROR("Primary Key Peer is not set in the request");
        return DRE_DB_FAIL;
    }

    if(!drePeerConfigReq->has_realm())
    {
        DLOG_ERROR("Primary Key Realm is not set in the request");
        return DRE_DB_FAIL;
    }

    if(drePeerConfigReq->dictionaryname_size() == 0)
    {
        DLOG_ERROR("dictionaryname is not present in the request");
        return DRE_DB_FAIL;
    }



    return DRE_DB_SUCCESS;
}


void PeerDictionaryMapTPBQuery::sql_PeerDictionaryMap_Create_Select_Query(DictionaryConfig *pDictionaryConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pDictionaryConfigReq->has_dictionaryid())
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"select PEER_DICTIONARY_ASSN_ID from PEER_DICTIONARY_MAP_TB where DICTIONARY_ID = %d",pDictionaryConfigReq->dictionaryid());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void PeerDictionaryMapTPBQuery::sql_PeerDictionaryMap_Create_Select_Query(PeerConfig *drePeerConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from PEER_DICTIONARY_MAP_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(drePeerConfigReq->has_peerid())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"PEER_ID=%d and ",drePeerConfigReq->peerid());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void PeerDictionaryMapTPBQuery::sql_PeerDictionaryMap_Create_Select_Query(PeerConfig *drePeerConfigReq,char *pStatement,int iIndex)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PeerT.PeerHostIdentity,PeerT.RealmName,DICTIONARY_TB.DICTIONARY_ID,DICTIONARY_TB.DICTIONARY_NAME,DICTIONARY_TB.APP_TYPE  from PEER_DICTIONARY_MAP_TB,PeerT,DICTIONARY_TB ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where PeerT.PeerID = PEER_DICTIONARY_MAP_TB.PEER_ID and PEER_DICTIONARY_MAP_TB.DICTIONARY_ID = DICTIONARY_TB.DICTIONARY_ID and ");

    DLOG_NONE(" < %s ",__FUNCTION__);
#if 0
    string sDictionaryName = drePeerConfigReq->dictionaryname(iIndex);
    if()
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"DICTIONARY_ID=%d and ",drePeerConfigReq->peerDictionaryInfo.PeerDictionaryIds[0]);
    }

#endif
    if(drePeerConfigReq->has_peerhostname() && drePeerConfigReq->has_realm())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"PEER_ID=(select PeerID from PeerT where PeerHostIdentity = '%s' and RealmName = '%s') and ",drePeerConfigReq->peerhostname().c_str(),drePeerConfigReq->realm().c_str());

    }


    sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    DLOG_NONE(" > %s ",__FUNCTION__);
}

DbStatus_e PeerDictionaryMapTPBQuery::sql_PeerDictionaryMap_Check_All_Invalid(PeerConfig *drePeerConfigReq,int iIndex)
{
    int iDictionarySize = drePeerConfigReq->dictionaryname_size();

    if(iDictionarySize > 0)
        return DRE_DB_FAIL;


    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
