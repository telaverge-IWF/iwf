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
#include <CMAPICMgr.h>
#include <CMAPICommon.h>


using namespace std;


void LocalTransportTagTPBQuery::sql_LocalTransportTag_Create_Check_Modifcation_Query(LHTransport *pLHTransport,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select LOCAL_TRANSPORT_TAG_ID,TRANSPORT_TAG from LOCAL_TRANSPORT_TAG_TB where TRANSPORT_TAG='%s' ",pLHTransport->transporttag().c_str());
}

void LocalTransportTagTPBQuery::sql_LocalTransportTag_Create_Add_Query(LHTransport *pLHTransport,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]     = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE("> %s",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into LOCAL_TRANSPORT_TAG_TB ");
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(TRANSPORT_TAG");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s' ",pLHTransport->transporttag().c_str());

    if(strlen(sFieldName) < MAX_STATEMENT_SIZE)
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE - strlen(sFieldName),")");
    if(strlen(sFieldValue) < MAX_STATEMENT_SIZE)
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE - strlen(sFieldValue),")");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE("< %s",__FUNCTION__);
}

void LocalTransportTagTPBQuery::sql_LocalTransportTag_Create_Mod_Query(LHTransport *pLHTransport,char *pStatement)
{
    DLOG_NONE("> %s",__FUNCTION__);
    DLOG_NONE("< %s",__FUNCTION__);

}

void LocalTransportTagTPBQuery::sql_LocalTransportTag_Create_Delete_Query(LHTransport *pLHTransport,char *pStatement)
{
    DLOG_NONE("> %s",__FUNCTION__);

    if(pLHTransport->has_transporttag())
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from LOCAL_TRANSPORT_TAG_TB where TRANSPORT_TAG = '%s'",pLHTransport->transporttag().c_str());
    else if(pLHTransport->has_transporttagid())
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from LOCAL_TRANSPORT_TAG_TB where LOCAL_TRANSPORT_TAG_ID = %d",pLHTransport->transporttagid());



    DLOG_NONE("< %s",__FUNCTION__);
}

DbStatus_e LocalTransportTagTPBQuery::sql_LocalTransportTag_Payload_Validation(LHTransport *pLHTransport)
{
    return DRE_DB_SUCCESS;
}

void LocalTransportTagTPBQuery::sql_LocalTransportTag_Create_Select_Query(LHTransport *pLHTransport,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    DLOG_NONE("> %s",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from LOCAL_TRANSPORT_TAG_TB");
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pLHTransport->has_transporttag())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"TRANSPORT_TAG='%s' and ",pLHTransport->transporttag().c_str());
    }

    if(pLHTransport->has_transporttagid())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"LOCAL_TRANSPORT_TAG_ID=%d and ",pLHTransport->transporttagid());
    }


    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE("< %s",__FUNCTION__);
}


DbStatus_e LocalTransportTagTPBQuery::sql_LocalTransportTag_Check_All_Invalid(LHTransport *pLHTransport)
{
    return DRE_DB_SUCCESS;
}

