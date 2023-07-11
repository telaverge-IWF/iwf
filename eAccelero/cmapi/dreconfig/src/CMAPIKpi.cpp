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

#include "CMAPICommon.h"
#include "CMAPIKpi.h"
#include "ResourceUsageStat_caller.h"
#include "ErrorResp.h"


int CMAPIKPIConfig::InitializeLibrary()
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG(">CMAPIKPIConfig: InitializeLibrary\n");

    MeSSEndpoint ActiveResourceMgr = {COMP_RESOURCE_MANAGER, MESS_MIN_ACTIVE_INSTANCE};
    MeSSEndpoint StandByResourceMgr = {COMP_RESOURCE_MANAGER, MESS_MIN_STANDBY_INSTANCE};
    m_ActiveRsrcMgrCallerObj = new Stub::ResourceUsageStat(ActiveResourceMgr,0);
    m_StandByRsrcMgrCallerObj = new Stub::ResourceUsageStat(StandByResourceMgr,0);

    MeSSEndpoint AMdest    = {COMP_AVAILABILITY_MANAGER, MESS_MULTICAST_ACTIVE};
    m_MutiActiveAvaMgrCallerObj = new Stub::AvaMgrKPIInterface(AMdest,0);

    MeSSEndpoint ActiveAvaMgr = {COMP_AVAILABILITY_MANAGER, MESS_MIN_ACTIVE_INSTANCE};
    MeSSEndpoint StandByAvaMgr = {COMP_AVAILABILITY_MANAGER, MESS_MIN_STANDBY_INSTANCE};
    m_StandByAvaMgrCallerObj = new Stub::AvaMgrKPIInterface(StandByAvaMgr,0);
    m_ActiveAvaMgrCallerObj = new Stub::AvaMgrKPIInterface(ActiveAvaMgr,0);


    MeSSEndpoint DREdest   = {COMP_DRE_APP,MESS_MIN_ACTIVE_INSTANCE};
    m_ActiveDRECallerObj = new Stub::DreKPIInterface(DREdest,0);

    Stub::ResourceUsageStatRespCbk::RegisterResourceUsageStatRespHandler();
    Stub::AvaMgrKPIInterfaceRespCbk::RegisterAvaMgrKPIInterfaceRespHandler();
    Stub::DreKPIInterfaceRespCbk::RegisterDreKPIInterfaceRespHandler();

    m_CMAPIResponse = new CMAPIIntSync();

    return retVal;
}


//Need to fill the hostname in the Req
int CMAPIKPIConfig::GetActiveProcessStateRequest(ProcessStateReq& Req,ProcessStateResp& resp)
{
     int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIKPIConfig: GetProcessStateRequest"); 

    if(!Req.has_hostname())
    {
        CLOG_ERROR("Hostname is not set.");
        retVal = CMAPI_MESSERROR;
        ::ErrorDetails *pErrorDetails;
        pErrorDetails = resp.add_errordetails();
        pErrorDetails->set_errorcode(CONFIG_COMMON_ERR_HOSTNAME_NOT_SET);
        pErrorDetails->set_errormsgkey("config.common.err.hostname.not.set");
        return retVal;
    }

    Req.set_requestid(GET_PROCESS_STATE);

    CLOG_DEBUG("Sending Requst to get SystemResource Info");
    // Call Caller Method to Call Server Implementation. 

    m_ActiveAvaMgrCallerObj->FetchProcessState(Req);

    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ::ErrorDetails *pErrorDetails;
        pErrorDetails = resp.add_errordetails();
        pErrorDetails->set_errorcode(CONFIG_COMMON_ERR_GENERIC_ERROR);
        pErrorDetails->set_errormsgkey("config.common.err.generic.error");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);

    resp.ParseFromString(StrVal);
    retVal = resp.responseid();

    // Return appropriate Return value.
    return retVal;
                                             
}

//Need to fill the hostname in the Req
int CMAPIKPIConfig::GetStandByProcessStateRequest(ProcessStateReq& Req,ProcessStateResp& resp)
{
     int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">CMAPIKPIConfig: GetProcessStateRequest"); 

    if(!Req.has_hostname())
    {
        CLOG_ERROR("Hostname is not set.");
        retVal = CMAPI_MESSERROR;
        ::ErrorDetails *pErrorDetails;
        pErrorDetails = resp.add_errordetails();
        pErrorDetails->set_errorcode(CONFIG_COMMON_ERR_HOSTNAME_NOT_SET);
        pErrorDetails->set_errormsgkey("config.common.err.hostname.not.set");
        return retVal;
    }

    Req.set_requestid(GET_PROCESS_STATE);

    CLOG_DEBUG("Sending Requst to get SystemResource Info");

    m_StandByAvaMgrCallerObj->FetchProcessState(Req);

    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ::ErrorDetails *pErrorDetails;
        pErrorDetails = resp.add_errordetails();
        pErrorDetails->set_errorcode(CONFIG_COMMON_ERR_GENERIC_ERROR);
        pErrorDetails->set_errormsgkey("config.common.err.generic.error");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);

    resp.ParseFromString(StrVal);
    retVal = resp.responseid();

    // Return appropriate Return value.
    return retVal;
                                             
}


// MeSS Callbacks
int CMAPIKPIConfig::FetchProcessStateRespCbk(ProcessStateResp *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">CMAPIKPIConfig::FetchProcessStateRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->responseid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("FetchProcessStateRespCbk message failed. Error: ");
        if (resp == NULL ) 
        {
            ProcessStateResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {

        if(!resp->has_hostname())
        {
            CLOG_DEBUG("%s Hostname is not set in the response, it is not a valid response Resp  %s",__FUNCTION__,resp->DebugString().c_str());
            return retVal;
        }
        resp->SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);
    return retVal;

}


//Need to fill the hostname and Request id in the Req
int CMAPIKPIConfig::GetCasReq(DiaCASReq& Req,DiaCASResp& resp)
{
     int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">CMAPIKPIConfig::GetCasReq"); 

    if(!Req.has_requestid())
    {
        CLOG_DEBUG("Requestid is not set, from the user, so setting the default value GET_ALLCAS ");
        Req.set_requestid(GET_ALLCAS);
    }

    CLOG_DEBUG("Sending Requst to get GetCasReq Info");
    // Call Caller Method to Call Server Implementation. 
    m_ActiveDRECallerObj->FetchCAS(Req);

    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ::ErrorDetails *pErrorDetails;
        pErrorDetails = resp.add_errordetails();
        pErrorDetails->set_errorcode(CONFIG_COMMON_ERR_GENERIC_ERROR);
        pErrorDetails->set_errormsgkey("config.common.err.generic.error");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);

    resp.ParseFromString(StrVal);
    retVal = resp.responseid();

    // Return appropriate Return value.
    return retVal;
                                             
}


// MeSS Callbacks
int CMAPIKPIConfig::FetchCASRespCbk(DiaCASResp *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">CMAPIKPIConfig::FetchCASRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->responseid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("FetchClusterInfoRespCbk message failed. Error: ");
        if (resp == NULL ) 
        {
            DiaCASResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    return retVal;

}

//Need to fill the hostname and Request id in the Req
int CMAPIKPIConfig::GetTpsReq(TPSReq& Req,TPSResp& resp)
{
     int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">CMAPIKPIConfig::GetTpsReq"); 

    if(!Req.has_requestid())
    {
        CLOG_DEBUG("Requestid is not set, from the user, so setting the default value GET_TPS");
        Req.set_requestid(GET_TPS);
    }

    CLOG_DEBUG("Sending Requst to get GetTpsReq Info");
    // Call Caller Method to Call Server Implementation. 
    m_ActiveDRECallerObj->FetchTPS(Req);

    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ::ErrorDetails *pErrorDetails;
        pErrorDetails = resp.add_errordetails();
        pErrorDetails->set_errorcode(CONFIG_COMMON_ERR_GENERIC_ERROR);
        pErrorDetails->set_errormsgkey("config.common.err.generic.error");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);

    resp.ParseFromString(StrVal);
    retVal = resp.responseid();

    // Return appropriate Return value.
    return retVal;
                                            
}


// MeSS Callbacks
int CMAPIKPIConfig::FetchTPSRespCbk(TPSResp *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">CMAPIKPIConfig::FetchTPSRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->responseid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("FetchClusterInfoRespCbk message failed. Error: ");
        if (resp == NULL ) 
        {
            TPSResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    return retVal;

}

//Need to fill the hostname and Request id in the Req
int CMAPIKPIConfig::GetApplicationKPIReq(DiaGeneralKPIReq& Req,DiaGeneralKPIResp& resp)
{
     int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIKPIConfig: GetApplicationKPIReq"); 

    if(!Req.has_requestid())
    {
        CLOG_DEBUG("Requestid is not set, from the user, so setting the default value GET_APP_KPI ");
        Req.set_requestid(GET_APP_KPI);
    }

    CLOG_DEBUG("Sending Requst to get ApplicationKPI Info");
    // Call Caller Method to Call Server Implementation. 
    m_ActiveDRECallerObj->FetchApplicationKPI(Req);

    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ::ErrorDetails *pErrorDetails;
        pErrorDetails = resp.add_errordetails();
        pErrorDetails->set_errorcode(CONFIG_COMMON_ERR_GENERIC_ERROR);
        pErrorDetails->set_errormsgkey("config.common.err.generic.error");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);

    resp.ParseFromString(StrVal);
    retVal = resp.responseid();

    // Return appropriate Return value.
    return retVal;
                                             
}


// MeSS Callbacks
int CMAPIKPIConfig::FetchApplicationKPIRespCbk(DiaGeneralKPIResp *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">CMAPIKPIConfig::FetchApplicationKPIRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->responseid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("FetchClusterInfoRespCbk message failed. Error: ");
        if (resp == NULL ) 
        {
            DiaGeneralKPIResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    return retVal;

}

//Need to fill the hostname in the Req
int CMAPIKPIConfig::GetActiveSystemResource(SystemResourceReq& Req,SystemResourceResp& resp)
{
     int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIKPIConfig: GetSystemResource"); 

    if(!Req.has_hostname())
    {
        CLOG_ERROR("Hostname is not set.");
        retVal = CMAPI_MESSERROR;
        ::ErrorDetails *pErrorDetails;
        pErrorDetails = resp.add_errordetails();
        pErrorDetails->set_errorcode(CONFIG_COMMON_ERR_HOSTNAME_NOT_SET);
        pErrorDetails->set_errormsgkey("config.common.err.hostname.not.set");
        return retVal;
    }

    Req.set_requestid(GET_SYS_RES);

    CLOG_DEBUG("Sending Requst to get SystemResource Info");
    // Call Caller Method to Call Server Implementation. 
    m_ActiveRsrcMgrCallerObj->FetchSystemResourceUsage(Req);

    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ::ErrorDetails *pErrorDetails;
        pErrorDetails = resp.add_errordetails();
        pErrorDetails->set_errorcode(CONFIG_COMMON_ERR_GENERIC_ERROR);
        pErrorDetails->set_errormsgkey("config.common.err.generic.error");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);

    resp.ParseFromString(StrVal);
    retVal = resp.responseid();

    // Return appropriate Return value.
    return retVal;
                                             
}


//Need to fill the hostname in the Req
int CMAPIKPIConfig::GetStandBySystemResource(SystemResourceReq& Req,SystemResourceResp& resp)
{
     int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIKPIConfig: GetSystemResource"); 

    if(!Req.has_hostname())
    {
        CLOG_ERROR("Hostname is not set.");
        retVal = CMAPI_MESSERROR;
        ::ErrorDetails *pErrorDetails;
        pErrorDetails = resp.add_errordetails();
        pErrorDetails->set_errorcode(CONFIG_COMMON_ERR_HOSTNAME_NOT_SET);
        pErrorDetails->set_errormsgkey("config.common.err.hostname.not.set");
        return retVal;
    }

    Req.set_requestid(GET_SYS_RES);

    CLOG_DEBUG("Sending Requst to get SystemResource Info");
    // Call Caller Method to Call Server Implementation. 
    m_StandByRsrcMgrCallerObj->FetchSystemResourceUsage(Req);

    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ::ErrorDetails *pErrorDetails;
        pErrorDetails = resp.add_errordetails();
        pErrorDetails->set_errorcode(CONFIG_COMMON_ERR_GENERIC_ERROR);
        pErrorDetails->set_errormsgkey("config.common.err.generic.error");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);

    resp.ParseFromString(StrVal);
    retVal = resp.responseid();

    // Return appropriate Return value.
    return retVal;
                                             
}


// MeSS Callbacks
int CMAPIKPIConfig::FetchSystemResourceUsageRespCbk(SystemResourceResp *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">FetchSystemResourceUsageRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->responseid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("FetchClusterInfoRespCbk message failed. Error: ");
        if (resp == NULL ) 
        {
            SystemResourceResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        if(!resp->has_hostname())
        {
            CLOG_DEBUG("%s Hostname is not set in the response, it is not a valid response Resp  %s",__FUNCTION__,resp->DebugString().c_str());
            return retVal;
        }

        resp->SerializeToString(&StrVal);
    }


    m_CMAPIResponse->Set(StrVal);
    return retVal;

}


int CMAPIKPIConfig::GetClusterInfoReq(ClusterInfoResp& resp)
{
     int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIKPIConfig: GetClusterInfoReq"); 

    ClusterInfoReq lClusterInfoRequest;
    lClusterInfoRequest.set_requestid(GET_CLUSTER_INFO);

    CLOG_DEBUG("Sending Requst to get ClusterInfo Info");
    // Call Caller Method to Call Server Implementation. 
    m_ActiveAvaMgrCallerObj->FetchClusterInfo(lClusterInfoRequest);

    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ::ErrorDetails *pErrorDetails;
        pErrorDetails = resp.add_errordetails();
        pErrorDetails->set_errorcode(CONFIG_COMMON_ERR_GENERIC_ERROR);
        pErrorDetails->set_errormsgkey("config.common.err.generic.error");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);

    resp.ParseFromString(StrVal);
    retVal = resp.responseid();

    // Return appropriate Return value.
    return retVal;
                                             
}


// MeSS Callbacks
int CMAPIKPIConfig::FetchClusterInfoRespCbk(ClusterInfoResp *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">FetchClusterInfoRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->responseid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("FetchClusterInfoRespCbk message failed. Error: ");
        if (resp == NULL ) 
        {
            ClusterInfoResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    return retVal;

}
