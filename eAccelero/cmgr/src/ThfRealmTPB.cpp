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

void THFRealmTPBQuery::sql_THFRealm_Create_Validation_Query_for_Realm(string sRealmName,char *pStatement)
{

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"select REALM_ID from REALM_TB where REALM_NAME='%s'",sRealmName.c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);

}

void THFRealmTPBQuery::sql_THFRealm_Create_Check_Modifcation_Query(THFRealm *THFRealmReq,char *pStatement,int iIndex)
{
    THFAction *localTHFAction = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG("THFRealmReq->otherrealm_size() = %d, iIndex= %d",THFRealmReq->otherrealm_size(),iIndex);

    if(THFRealmReq->otherrealm_size() > iIndex && iIndex > -1)
    {
        localTHFAction = THFRealmReq->mutable_otherrealm(iIndex);
    }

    if(THFRealmReq->otherrealm_size() && localTHFAction->has_realmname())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," select * from THF_REALM_TB where TARGET_REALM=(select REALM_ID from REALM_TB where REALM_NAME='%s') and OTHER_REALM=(select REALM_ID from REALM_TB where REALM_NAME='%s')",THFRealmReq->realmname().c_str(),localTHFAction->realmname().c_str());
    }
    else if(THFRealmReq->has_realmname())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," select * from THF_REALM_TB where TARGET_REALM=(select REALM_ID from REALM_TB where REALM_NAME='%s')",THFRealmReq->realmname().c_str());
    }


    DLOG_NONE(" < %s ",__FUNCTION__);
}

void THFRealmTPBQuery::sql_THFRealm_Create_Add_Query(THFRealm *THFRealmReq,char *pStatement,int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE]	= {0};
    char sFieldValue[MAX_STATEMENT_SIZE]	= {0};
    THFAction *localTHFAction = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG("THFRealmReq->otherrealm_size() = %d, iIndex= %d",THFRealmReq->otherrealm_size(),iIndex);

    if(THFRealmReq->otherrealm_size() > iIndex && iIndex > -1)
    {
        localTHFAction = THFRealmReq->mutable_otherrealm(iIndex);
    }
    else
    {
        DLOG_WARNING("Action Object will be NULL, THFRealmReq->otherrealm_size() = %d, iIndex= %d",THFRealmReq->otherrealm_size(),iIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into THF_REALM_TB ");
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(TARGET_REALM,OTHER_REALM");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"((select REALM_ID from REALM_TB where REALM_NAME='%s'),(select REALM_ID from REALM_TB where REALM_NAME='%s')",THFRealmReq->realmname().c_str(),localTHFAction->realmname().c_str());

    if(THFRealmReq->otherrealm_size() && localTHFAction->has_action())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",ACTION");
        if(localTHFAction->action() == THFAction_Action_ExposeTo)
        {
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'expose-to'");
        }
        if(localTHFAction->action() == THFAction_Action_HideFrom)
        {
            if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
                snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",'hide-from'");
        }
    }

    if(THFRealmReq->otherrealm_size() && localTHFAction->has_exposedavps())
    {
        if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),",EXPOSED_AVP");
#if 0
        int avp_size = localTHFAction->exposedavps_size();

        int value=0;
        for(int i=0;i<avp_size;i++)
        {

            if(localTHFAction->exposedavps(i) == ORIGIN_HOST)
                value =| EXPOSE_ORIGIN_HOST;
            else if(localTHFAction->exposedavps(i) == ORIGIN_REALM)
                value =| EXPOSE_ORIGIN_REALM;
            else if(localTHFAction->exposedavps(i) == DESTINATION_HOST)
                value =| EXPOSE_DESTINATION_HOST;
            else if(localTHFAction->exposedavps(i) == DESTINATION_REALM)
                value =| EXPOSE_DESTINATION_REALM;
        }
#endif
        if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),",%d",localTHFAction->exposedavps());
    }

    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__);


}

void THFRealmTPBQuery::sql_THFRealm_Create_Delete_Query(THFRealm *THFRealmReq,char *pStatement,int iIndex)
{

    int iFlag 					= 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
    THFAction *localTHFAction = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG("THFRealmReq->otherrealm_size() = %d, iIndex= %d",THFRealmReq->otherrealm_size(),iIndex);

    if(THFRealmReq->otherrealm_size() > iIndex && iIndex > -1)
    {
        localTHFAction = THFRealmReq->mutable_otherrealm(iIndex);
    }


    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from THF_REALM_TB ");
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(THFRealmReq->has_realmname())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"TARGET_REALM=(select REALM_ID from REALM_TB where REALM_NAME='%s') and ",THFRealmReq->realmname().c_str());
    }

    if(THFRealmReq->otherrealm_size() && localTHFAction->has_realmname())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"OTHER_REALM=(select REALM_ID from REALM_TB where REALM_NAME='%s') and ",localTHFAction->realmname().c_str());
    }

    if(THFRealmReq->otherrealm_size() && localTHFAction->has_action())
    {
        if(localTHFAction->action() == THFAction_Action_ExposeTo)
        {
            if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
                snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),",ACTION='expose-to' and ");
        }
        if(localTHFAction->action() == THFAction_Action_HideFrom)
        {
            if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
                snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),",ACTION='hide-from' and ");
        }

    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void THFRealmTPBQuery::sql_THFRealm_Create_Mod_Query(THFRealm *THFRealmReq,char *pStatement,int iIndex)
{

    THFAction *localTHFAction = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG("THFRealmReq->otherrealm_size() = %d, iIndex= %d",THFRealmReq->otherrealm_size(),iIndex);

    if(THFRealmReq->otherrealm_size() > iIndex && iIndex > -1)
    {
        localTHFAction = THFRealmReq->mutable_otherrealm(iIndex);
    }


    snprintf(pStatement,MAX_STATEMENT_SIZE,"update THF_REALM_TB set ");

#if 0
    if(THFRealmReq->has_realmname())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"TARGET_REALM=(select REALM_ID from REALM_TB where REALM_NAME='%s'),",THFRealmReq->realmname().c_str());
    }

    if(THFRealmReq->otherrealm_size() && localTHFAction->has_realmname())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"OTHER_REALM=(select REALM_ID from REALM_TB where REALM_NAME='%s'),",localTHFAction->realmname().c_str());
    }
#endif

    if(THFRealmReq->otherrealm_size() && localTHFAction->has_action())
    {
        if(localTHFAction->action() == THFAction_Action_ExposeTo)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),",ACTION='expose-to',");
        }
        if(localTHFAction->action() == THFAction_Action_HideFrom)
        {
            if(strlen(pStatement) < MAX_STATEMENT_SIZE)
                snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),",ACTION='hide-from',");
        }

    }

    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where TARGET_REALM=(select REALM_ID from REALM_TB where REALM_NAME='%s') and OTHER_REALM=(select REALM_ID from REALM_TB where REALM_NAME='%s')",THFRealmReq->realmname().c_str(),localTHFAction->realmname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e THFRealmTPBQuery::sql_THFRealm_Payload_Validation(THFRealm *THFRealmReq,int iIndex)
{
    return DRE_DB_SUCCESS;
}


void THFRealmTPBQuery::sql_THFRealm_Create_Select_Query(THFRealm *THFRealmReq,char *pStatement,int iIndex)
{
    int iFlag 					= 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
    THFAction *localTHFAction = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG("THFRealmReq->otherrealm_size() = %d, iIndex= %d",THFRealmReq->otherrealm_size(),iIndex);

    if(THFRealmReq->otherrealm_size() > iIndex && iIndex > -1)
    {
        localTHFAction = THFRealmReq->mutable_otherrealm(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select "
            "TARGET.REALM_NAME as TARGET_REALM,"
            "OTHER.REALM_NAME as OTHER_REALM,"
            "THF_REALM_TB.ACTION,"
            "THF_REALM_TB.EXPOSED_AVP"
            " from THF_REALM_TB"
            " inner join REALM_TB TARGET on THF_REALM_TB.TARGET_REALM = TARGET.REALM_ID"
            " inner join REALM_TB OTHER on THF_REALM_TB.OTHER_REALM = OTHER.REALM_ID ");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");


    if(THFRealmReq->has_realmname())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"THF_REALM_TB.TARGET_REALM=(select REALM_ID from REALM_TB where REALM_NAME='%s') and ",THFRealmReq->realmname().c_str());
    }

    if(THFRealmReq->otherrealm_size() && localTHFAction->has_realmname())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"THF_REALM_TB.OTHER_REALM=(select REALM_ID from REALM_TB where REALM_NAME='%s') and ",localTHFAction->realmname().c_str());
    }

    if(THFRealmReq->otherrealm_size() && localTHFAction->has_action())
    {
        if(localTHFAction->action() == THFAction_Action_ExposeTo)
        {
            if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
                snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),",ACTION='expose-to' and ");
        }
        if(localTHFAction->action() == THFAction_Action_HideFrom)
        {
            if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
                snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),",ACTION='hide-from' and ");
        }

    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e THFRealmTPBQuery::sql_THFRealm_Check_All_Invalid(THFRealm *THFRealmReq,int iIndex)
{
    return DRE_DB_SUCCESS;
}
