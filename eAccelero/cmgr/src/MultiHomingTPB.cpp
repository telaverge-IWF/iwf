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
void MultiHomingTPBQuery::sql_MultiHoming_Create_Validation_Query_for_TransportType(LHTransport *dreLocalHostReq,char *pStatement)
{
    DLOG_NONE("> %s",__FUNCTION__);
    int iTransportType = 1;
    if(dreLocalHostReq->has_transporttype())
    {
        if(dreLocalHostReq->transporttype() == "SCTP")
        {
            iTransportType = 2;
        }
        else if (dreLocalHostReq->transporttype() == "TLS")
        {
            iTransportType = 3;
        }
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select TRANSPORT_ID from LOCAL_TRANSPORT_TB where IP_ADDRESS='%s' and PORT=%d and TRANSPORT_TYPE=%d",dreLocalHostReq->hostipaddr().c_str(),dreLocalHostReq->port(),iTransportType);
    DLOG_NONE("< %s",__FUNCTION__);

}


void MultiHomingTPBQuery::sql_MultiHoming_Create_Check_Modifcation_Query(LHTransport *dreLocalHostReq,char *pStatement,int iIndex)
{
    string *sSecondaryIp=NULL;
    int transportslot=0;

    DLOG_DEBUG("dreLocalHostReq->secondaryipaddr_size() = %d, iIndex= %d",dreLocalHostReq->secondaryipaddr_size(),iIndex);    

    if(dreLocalHostReq->secondaryipaddr_size() > iIndex && iIndex > -1)
    {
        transportslot = dreLocalHostReq->transportslot(); 
        sSecondaryIp = dreLocalHostReq->mutable_secondaryipaddr(iIndex);
    }
    else
    {
        DLOG_WARNING("secondary Ip is not configured, wrong iIndex = %d , secondaryipaddr_size = %d",iIndex,dreLocalHostReq->secondaryipaddr_size());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }


    snprintf(pStatement,MAX_STATEMENT_SIZE,"select MULTIHOMING_ID from  MULTIHOMING_TB where TRANSPORT_ID=%d and OTHERHOME_IPADDR='%s' ",transportslot,sSecondaryIp->c_str());

}

void MultiHomingTPBQuery::sql_MultiHoming_Create_Add_Query(LHTransport *dreLocalHostReq,char *pStatement,int iIndex)
{
    char sFieldName[MAX_STATEMENT_SIZE]     = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  
    string *sSecondaryIp=NULL;

    DLOG_NONE("> %s",__FUNCTION__);
    DLOG_DEBUG("dreLocalHostReq->secondaryipaddr_size() = %d, iIndex= %d",dreLocalHostReq->secondaryipaddr_size(),iIndex);    

    int iTransportType = 1;
    if(dreLocalHostReq->has_transporttype())
    {
        if(dreLocalHostReq->transporttype() == "SCTP")
        {
            iTransportType = 2;
        }
        else if (dreLocalHostReq->transporttype() == "TLS")
        {
            iTransportType = 3;
        }
    }


    if(dreLocalHostReq->secondaryipaddr_size() > iIndex && iIndex > -1)
    {
        sSecondaryIp = dreLocalHostReq->mutable_secondaryipaddr(iIndex);
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into MULTIHOMING_TB "); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(TRANSPORT_ID");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"((select TRANSPORT_ID from LOCAL_TRANSPORT_TB where IP_ADDRESS='%s' and PORT=%d and TRANSPORT_TYPE=%d)",dreLocalHostReq->hostipaddr().c_str(),dreLocalHostReq->port(),iTransportType);

    if(dreLocalHostReq->secondaryipaddr_size())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",OTHERHOME_IPADDR");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",sSecondaryIp->c_str());
    }

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE("< %s",__FUNCTION__);
}

void MultiHomingTPBQuery::sql_MultiHoming_Create_Mod_Query(LHTransport *dreLocalHostReq,char *pStatement,int iIndex)
{
    DLOG_NONE("> %s",__FUNCTION__);
    string *sSecondaryIp=NULL;

    DLOG_DEBUG("dreLocalHostReq->secondaryipaddr_size() = %d, iIndex= %d",dreLocalHostReq->secondaryipaddr_size(),iIndex);    

    if(dreLocalHostReq->secondaryipaddr_size() > iIndex && iIndex > -1)
    {
        sSecondaryIp = dreLocalHostReq->mutable_secondaryipaddr(iIndex);
    }

    int iTransportType;
    if(dreLocalHostReq->has_transporttype())
    {
        if(dreLocalHostReq->transporttype() == "SCTP")
        {
            iTransportType = 2;
        }
        else if (dreLocalHostReq->transporttype() == "TLS")
        {
            iTransportType = 3;
        }
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update MULTIHOMING_TB set "); 

    if(dreLocalHostReq->secondaryipaddr_size())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"OTHERHOME_IPADDR='%s',",sSecondaryIp->c_str());

    }

    if(dreLocalHostReq->has_hostipaddr() && dreLocalHostReq->has_port(),dreLocalHostReq->has_transporttype())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TRANSPORT_ID=(select TRANSPORT_ID from LOCAL_TRANSPORT_TB where IP_ADDRESS='%s' and PORT=%d and TRANSPORT_TYPE=%d),",dreLocalHostReq->hostipaddr().c_str(),dreLocalHostReq->port(),iTransportType);
    }


    pStatement[strlen(pStatement) -1] = ' ';


    DLOG_NONE("< %s",__FUNCTION__);

}

void MultiHomingTPBQuery::sql_MultiHoming_Create_Check_Delete_Query(LocalHost *dreLocalHostReq,char *pStatement,int iIndex)
{
    DLOG_NONE("> %s",__FUNCTION__);
    ::LHTransport *pLHTransport = NULL;
    int transportslot=0;
    string *sSecondaryIp=NULL;
    if(dreLocalHostReq->transports_size() > iIndex && iIndex > -1)
    {
        pLHTransport = dreLocalHostReq->mutable_transports(iIndex);
        transportslot = pLHTransport->transportslot();
        if(pLHTransport->secondaryipaddr_size() > iIndex && iIndex > -1)
        {
            sSecondaryIp = pLHTransport->mutable_secondaryipaddr(iIndex);
        }
        else
        {
            DLOG_WARNING("secondary Ip is not configured, wrong iIndex = %d , secondaryipaddr_size = %d",iIndex,pLHTransport->secondaryipaddr_size());
            DLOG_NONE(" < %s ",__FUNCTION__);
            return;
        }

    }
    else
    {
        DLOG_WARNING("Transport-Id is not configured, wrong iIndex = %d , transports_size = %d",iIndex,dreLocalHostReq->transports_size());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select MULTIHOMING_ID from  MULTIHOMING_TB where TRANSPORT_ID=%d and OTHERHOME_IPADDR='%s' ",transportslot,sSecondaryIp->c_str());

}
void MultiHomingTPBQuery::sql_MultiHoming_Create_Delete_Query(LocalHost *dreLocalHostReq,char *pStatement,int iIndex)
{
    DLOG_NONE("> %s",__FUNCTION__);
    string *sSecondaryIp=NULL;
    int transportslot=0;
    ::LHTransport *pLHTransport = NULL;

    if(dreLocalHostReq->transports_size() > iIndex && iIndex > -1)
    {
        pLHTransport = dreLocalHostReq->mutable_transports(iIndex);
        transportslot = pLHTransport->transportslot();
        if(pLHTransport->secondaryipaddr_size() > iIndex && iIndex > -1)
        {
            sSecondaryIp = pLHTransport->mutable_secondaryipaddr(iIndex);
        }

        if(pLHTransport->has_transportslot() && pLHTransport->secondaryipaddr_size())
        {
            snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from MULTIHOMING_TB where TRANSPORT_ID=%d and OTHERHOME_IPADDR='%s' ",transportslot,sSecondaryIp->c_str());
        }
    }

    DLOG_NONE("< %s",__FUNCTION__);
}

DbStatus_e MultiHomingTPBQuery::sql_MultiHoming_Payload_Validation(LHTransport *dreLocalHostReq,int iIndex)
{

    if(!dreLocalHostReq->secondaryipaddr_size())
    {
        DLOG_ERROR("Primary Key secondary key is not given");
        return ERR_HOST_MANDATORY_PARAM_TRANSPORT_SLOT_MISSING; 
    }

    if(!dreLocalHostReq->has_hostipaddr())
    {
        DLOG_ERROR("Primary Key ipaddr is not given");
        return ERR_HOST_MANDATORY_PARAM_TRANSPORT_SLOT_MISSING; 
    }

    if(!dreLocalHostReq->has_port())
    {
        DLOG_ERROR("Primary Key port is not given");
        return ERR_HOST_MANDATORY_PARAM_HOSTNAME_MISSING;
    }


    if(!dreLocalHostReq->has_transporttype())
    {
        DLOG_ERROR("Primary Key transport type is not given");
        return ERR_HOST_MANDATORY_PARAM_REALMNAME_MISSING;  
    }


    return DRE_DB_SUCCESS;
}


void MultiHomingTPBQuery::sql_MultiHoming_Create_Select_Query(LHTransport *dreLocalHostReq,char *pStatement,int iIndex)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    string *sSecondaryIp=NULL;
    DLOG_NONE("> %s",__FUNCTION__);

    DLOG_DEBUG("dreLocalHostReq->secondaryipaddr_size() = %d, iIndex= %d",dreLocalHostReq->secondaryipaddr_size(),iIndex);    

    if(dreLocalHostReq->secondaryipaddr_size() > iIndex && iIndex > -1)
    {
        sSecondaryIp = dreLocalHostReq->mutable_secondaryipaddr(iIndex);
    }

    int iTransportType;
    if(dreLocalHostReq->has_transporttype())
    {
        if(dreLocalHostReq->transporttype() == "SCTP")
        {
            iTransportType = 2;
        }
        else if (dreLocalHostReq->transporttype() == "TLS")
        {
            iTransportType = 3;
        }
    }


    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from MULTIHOMING_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(dreLocalHostReq->secondaryipaddr_size())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"OTHERHOME_IPADDR='%s' and ",sSecondaryIp->c_str());

    }


    if(dreLocalHostReq->has_hostipaddr() && dreLocalHostReq->has_port() && dreLocalHostReq->has_transporttype())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TRANSPORT_ID=(select TRANSPORT_ID from LOCAL_TRANSPORT_TB where IP_ADDRESS='%s' and PORT=%d and TRANSPORT_TYPE=%d) and ",dreLocalHostReq->hostipaddr().c_str(),dreLocalHostReq->port(),iTransportType);
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE("< %s",__FUNCTION__);
}

DbStatus_e MultiHomingTPBQuery::sql_MultiHoming_Check_All_Invalid(LHTransport *dreLocalHostReq,int iIndex)
{

    if(dreLocalHostReq->has_hostipaddr())
    {
        return DRE_DB_FAIL;
    }

    if(dreLocalHostReq->has_port())
    {
        return DRE_DB_FAIL;
    }

    if(dreLocalHostReq->has_transporttype())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}

