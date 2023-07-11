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

void LocalTransportTPBQuery::sql_LocalTransport_Create_Validation_Query_for_LocalHost(LocalHost *dreLocalHostReq,char *pStatement)
{
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select LocalHostConfigID from LocalHostConfigT where HostName='%s' and RealmName='%s'",dreLocalHostReq->localhostname().c_str(),dreLocalHostReq->realmname().c_str());
}


void LocalTransportTPBQuery::sql_LocalTransport_Create_Check_Modifcation_Query(LocalHost *dreLocalHostReq,char *pStatement,int iIndex)
{

    ::LHTransport *pLHTransport = NULL;

    DLOG_DEBUG("dreLocalHostReq->transports_size() = %d, iIndex= %d",dreLocalHostReq->transports_size(),iIndex);    

    if(dreLocalHostReq->transports_size() > iIndex && iIndex > -1)
    {
        pLHTransport = dreLocalHostReq->mutable_transports(iIndex);
    }
    else
    {

        DLOG_WARNING("LHTransport == NULL,iIndex %d greater than transport_size() = %d ",iIndex,dreLocalHostReq->transports_size());
        return;
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select TRANSPORT_ID from  LOCAL_TRANSPORT_TB where TRANSPORT_ID=%d ",pLHTransport->transportslot());
}

void LocalTransportTPBQuery::sql_LocalTransport_Create_Add_Query(LocalHost *dreLocalHostReq,char *pStatement,int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE]     = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE("> %s",__FUNCTION__);

    ::LHTransport *pLHTransport = NULL;

    DLOG_DEBUG("dreLocalHostReq->transports_size() = %d, iIndex= %d",dreLocalHostReq->transports_size(),iIndex);    

    if(dreLocalHostReq->transports_size() > iIndex && iIndex > -1)
    {
        pLHTransport = dreLocalHostReq->mutable_transports(iIndex);
    }
    else
    {
        DLOG_WARNING("LHTransport == NULL,iIndex %d greater than transport_size() = %d ",iIndex,dreLocalHostReq->transports_size());
        return;
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into LOCAL_TRANSPORT_TB "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(TRANSPORT_ID,LocalHostConfigID");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(%d,(select LocalHostConfigID from LocalHostConfigT where HostName='%s' and RealmName='%s')",pLHTransport->transportslot(),dreLocalHostReq->localhostname().c_str(),dreLocalHostReq->realmname().c_str());

    if(pLHTransport->has_hostipaddr())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IP_ADDRESS");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",pLHTransport->hostipaddr().c_str());
    }

    if(pLHTransport->has_port())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PORT");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",pLHTransport->port());
    }

    if(pLHTransport->has_publicserveripaddr())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",PUBLIC_SERVER_IP");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",pLHTransport->publicserveripaddr().c_str());
    }

    if(pLHTransport->has_secureport())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SecurePort");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%d'",pLHTransport->secureport());
    }

    if(pLHTransport->has_transporttype())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",TRANSPORT_TYPE");
        if(pLHTransport->transporttype() == "SCTP")
        {
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",2");
        }
        else if (pLHTransport->transporttype() == "TLS")
        {
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",3");
        }
        else 
        {
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",1");
        }
    }

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE("< %s",__FUNCTION__);
}

void LocalTransportTPBQuery::sql_LocalTransport_Create_Mod_Query(LocalHost *dreLocalHostReq,char *pStatement,int iIndex)
{
    DLOG_NONE("> %s",__FUNCTION__);

    ::LHTransport *pLHTransport = NULL;

    DLOG_DEBUG("dreLocalHostReq->transports_size() = %d, iIndex= %d",dreLocalHostReq->transports_size(),iIndex);    

    if(dreLocalHostReq->transports_size() > iIndex && iIndex > -1)
    {
        pLHTransport = dreLocalHostReq->mutable_transports(iIndex);
    }
    else
    {
        DLOG_WARNING("LHTransport == NULL,iIndex %d greater than transport_size() = %d ",iIndex,dreLocalHostReq->transports_size());
        return;
    }
    snprintf(pStatement,MAX_STATEMENT_SIZE,"update LOCAL_TRANSPORT_TB set "); 

    if(pLHTransport->has_hostipaddr())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IP_ADDRESS='%s',",pLHTransport->hostipaddr().c_str());

    }

    if(pLHTransport->has_port() && pLHTransport->port() > 0)
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PORT=%d,",pLHTransport->port());
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SecurePort=0,");
    }

    if(pLHTransport->has_publicserveripaddr())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PUBLIC_SERVER_IP='%s',",pLHTransport->publicserveripaddr().c_str());
    }

    if(pLHTransport->has_secureport() && pLHTransport->secureport() > 0)
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SecurePort=%d,",pLHTransport->secureport());
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PORT=0,");
    }

    if(pLHTransport->has_transporttype())
    {
        if(pLHTransport->transporttype() == "SCTP")
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TRANSPORT_TYPE=2,");
        }
        else if (pLHTransport->transporttype() == "TLS")
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TRANSPORT_TYPE=3,");
        }
        else 
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TRANSPORT_TYPE=1,");
        }
    }

    pStatement[strlen(pStatement) -1] = ' ';

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where TRANSPORT_ID=%d and LocalHostConfigID=(select LocalHostConfigID from LocalHostConfigT where HostName='%s' and RealmName='%s')",pLHTransport->transportslot(),dreLocalHostReq->localhostname().c_str(),dreLocalHostReq->realmname().c_str());

    DLOG_NONE("< %s",__FUNCTION__);

}

void LocalTransportTPBQuery::sql_LocalTransport_Create_Delete_Query(LocalHost *dreLocalHostReq,char *pStatement,int iIndex)
{
    DLOG_NONE("> %s",__FUNCTION__);

    ::LHTransport *pLHTransport = NULL;

    DLOG_DEBUG("dreLocalHostReq->transports_size() = %d, iIndex= %d",dreLocalHostReq->transports_size(),iIndex);    

    if(dreLocalHostReq->transports_size() > iIndex && iIndex > -1)
    {
        pLHTransport = dreLocalHostReq->mutable_transports(iIndex);
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from LOCAL_TRANSPORT_TB where TRANSPORT_ID=%d ",pLHTransport->transportslot());
    }
    else
    {
        snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from LOCAL_TRANSPORT_TB");
    }

    DLOG_NONE("< %s",__FUNCTION__);
}

DbStatus_e LocalTransportTPBQuery::sql_LocalTransport_Payload_Validation(LocalHost *dreLocalHostReq,int iIndex)
{
    ::LHTransport *pLHTransport = NULL;

    DLOG_DEBUG("dreLocalHostReq->transports_size() = %d, iIndex= %d",dreLocalHostReq->transports_size(),iIndex);    

    if(dreLocalHostReq->transports_size() > iIndex && iIndex > -1)
    {
        pLHTransport = dreLocalHostReq->mutable_transports(iIndex);
    }

    if(pLHTransport == NULL)
    {
        DLOG_WARNING("LHTransport == NULL,iIndex %d greater than transport_size() = %d ",iIndex,dreLocalHostReq->transports_size());
        return ERR_HOST_MANDATORY_PARAM_TRANSPORT_SLOT_MISSING;
    }

    if(!pLHTransport->has_transportslot())
    {
        DLOG_ERROR("Primary Key transport slot is not given");
        return ERR_HOST_MANDATORY_PARAM_TRANSPORT_SLOT_MISSING; 
    }

    if(!dreLocalHostReq->has_localhostname())
    {
        DLOG_ERROR("Primary Key LocalHost Name is not given");
        return ERR_HOST_MANDATORY_PARAM_HOSTNAME_MISSING;
    }


    if(!dreLocalHostReq->has_realmname())
    {
        DLOG_ERROR("Primary Key realm name is not given");
        return ERR_HOST_MANDATORY_PARAM_REALMNAME_MISSING;  
    }


    return DRE_DB_SUCCESS;
}


void LocalTransportTPBQuery::sql_LocalTransport_Create_Select_Query(LocalHost *dreLocalHostReq,char *pStatement,int iIndex)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    DLOG_NONE("> %s",__FUNCTION__);


    ::LHTransport *pLHTransport = NULL;
    DLOG_DEBUG("dreLocalHostReq->transports_size() = %d, iIndex= %d",dreLocalHostReq->transports_size(),iIndex);    

    if(dreLocalHostReq->transports_size() > iIndex && iIndex > -1)
    {
        pLHTransport = dreLocalHostReq->mutable_transports(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from LOCAL_TRANSPORT_TB "); 

    if(pLHTransport == NULL)
    {
        DLOG_WARNING("LHTransport == NULL,iIndex %d greater than transport_size() = %d ",iIndex,dreLocalHostReq->transports_size());
        return;
    }

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(dreLocalHostReq->transports_size() && pLHTransport->has_transportslot())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TRANSPORT_ID=%d and ",pLHTransport->transportslot());
    }


    if(dreLocalHostReq->transports_size() && pLHTransport->has_hostipaddr())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IP_ADDRESS='%s' and ",pLHTransport->hostipaddr().c_str());

    }

    if(dreLocalHostReq->transports_size() && pLHTransport->has_port())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PORT=%d and ",pLHTransport->port());
    }

    if(dreLocalHostReq->transports_size() && pLHTransport->has_secureport())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SecurePort=%d and ",pLHTransport->secureport());
    }
    if(dreLocalHostReq->transports_size() && pLHTransport->has_publicserveripaddr())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PUBLIC_SERVER_IP='%s' and ",pLHTransport->publicserveripaddr().c_str());
    }


    if(dreLocalHostReq->has_realmname() && dreLocalHostReq->has_localhostname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LocalHostConfigID=(select LocalHostConfigID from LocalHostConfigT where HostName='%s' and RealmName='%s') and ",dreLocalHostReq->localhostname().c_str(),dreLocalHostReq->realmname().c_str());
    }


    if(dreLocalHostReq->transports_size() && pLHTransport->has_transporttype())
    {
        iFlag = 1;
        if(pLHTransport->transporttype() == "SCTP")
        {
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TRANSPORT_TYPE=2 and ");
        }
        else if (pLHTransport->transporttype() == "TLS")
        {
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TRANSPORT_TYPE=3 and ");
        }
        else 
        {
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TRANSPORT_TYPE=1 and ");
        }

    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE("< %s",__FUNCTION__);
}

DbStatus_e LocalTransportTPBQuery::sql_LocalTransport_Check_All_Invalid(LocalHost *dreLocalHostPayload,int iIndex)
{
    ::LHTransport *pLHTransport = NULL;

    DLOG_DEBUG("dreLocalHostReq->transports_size() = %d, iIndex= %d",dreLocalHostPayload->transports_size(),iIndex);    

    if(dreLocalHostPayload->transports_size() > iIndex && iIndex > -1)
    {
        pLHTransport = dreLocalHostPayload->mutable_transports(iIndex);
    }

    if(pLHTransport == NULL)
    {
        DLOG_WARNING("LHTransport == NULL,iIndex %d greater than transport_size() = %d ",iIndex,dreLocalHostPayload->transports_size());
        return DRE_DB_SUCCESS;
    }

    if(pLHTransport->has_hostipaddr())
    {
        return DRE_DB_FAIL;
    }

    if(pLHTransport->has_port())
    {
        return DRE_DB_FAIL;
    }

    if(pLHTransport->has_transporttype())
    {
        return DRE_DB_FAIL;
    }

    if(dreLocalHostPayload->has_localhostname() && dreLocalHostPayload->has_realmname())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}

