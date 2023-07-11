/**
 *
 *   @file  CMApiHA.cpp
 *
 *  @brief  CMAPI Library Implementation for HA.
 *
 **/

#include "CMAPICommon.h"
#include "ComponentDefines.h"
#include "CMApiHA.h"
#include "ErrorResp.h"

using namespace std;
using namespace eAccelero;

int CMApiHA::InitializeLibrary() 
{
    int retVal = CMAPI_SUCCESS;
    MeSSEndpoint AMdest    = {COMP_AVAILABILITY_MANAGER, MESS_MULTICAST_ACTIVE};
    MeSSEndpoint RMdest    = {COMP_REPLICATION_MANAGER,  MESS_MULTICAST_ACTIVE};
    MeSSEndpoint DREdest   = {COMP_DRE_APP,              MESS_MULTICAST_ACTIVE};
    MeSSEndpoint CMgrdest  = {COMP_CONFIG_MANAGER,       MESS_MULTICAST_ACTIVE};

    m_AMObj    = new Stub::AvaMgrHAInterface(AMdest, 0);
    RegisterAvaMgrHAInterfaceRespHandler();
    m_CMgrObj  = new Stub::CMgrHAInterface(CMgrdest, 0);
    RegisterCMgrHAInterfaceRespHandler();
    m_DREObj   = new Stub::DreHAInterface(DREdest, 0);
    RegisterDreHAInterfaceRespHandler();
    m_RMObj    = new Stub::RepMgrHAInterface(RMdest, 0);
    RegisterRepMgrHAInterfaceRespHandler();

    m_HAResponse = new CMAPIIntSync();

    return retVal;

}

int CMApiHA::SetAMPeerPingPeriodicity(int PingPeriodicity)
{
    int retVal = CMAPI_SUCCESS;
    if (PingPeriodicity < 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        AvaMgrConfig AMConfigReq;
        AMConfigReq.set_peerpingperiodicity(PingPeriodicity);
        retVal = SendAMRequest(AMConfigReq);
    }

    return retVal;
}

int CMApiHA::SetAMArbitratorPingPeriodicity(int ArbPingPeriodicity)
{
    int retVal = CMAPI_SUCCESS;
    if (ArbPingPeriodicity < 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        AvaMgrConfig AMConfigReq;
        AMConfigReq.set_arbitratorpingperiodicity(ArbPingPeriodicity);
        retVal = SendAMRequest(AMConfigReq);
    }

    return retVal;

}

int CMApiHA::SetAMMaximumPingACKReceiveFailures(int MaxValue)
{
    int retVal = CMAPI_SUCCESS;
    if (MaxValue < 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        AvaMgrConfig AMConfigReq;
        AMConfigReq.set_peernumconsecpingackrcvfailures(MaxValue);
        retVal = SendAMRequest(AMConfigReq);
    }

    return retVal;

}

int CMApiHA::SetAMMaximumArbPingACKReceiveFailures(int MaxValue)
{
    int retVal = CMAPI_SUCCESS;
    if (MaxValue < 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        AvaMgrConfig AMConfigReq;
        AMConfigReq.set_arbitratornumconsecpingackrcvfailures(MaxValue);
        retVal = SendAMRequest(AMConfigReq);
    }

    return retVal;

}

int CMApiHA::SetAMProcessRestartMAXAllowedInterval(int MaxValue)
{
    int retVal = CMAPI_SUCCESS;
    if (MaxValue < 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        AvaMgrConfig AMConfigReq;
        AMConfigReq.set_processrestartmaxallowedinterval(MaxValue);
        retVal = SendAMRequest(AMConfigReq);
    }

    return retVal;

}

int CMApiHA::SetAMProcessRestartMaxAllowedCount(int MaxValue)
{
    int retVal = CMAPI_SUCCESS;
    if (MaxValue < 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        AvaMgrConfig AMConfigReq;
        AMConfigReq.set_processrestartmaxallowedcount(MaxValue);
        retVal = SendAMRequest(AMConfigReq);
    }

    return retVal;

}

int CMApiHA::SetAMArbitratorIpAddress(string IPAddress)
{
    int retVal = CMAPI_SUCCESS;
    if (IPAddress.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        AvaMgrConfig AMConfigReq;
        AMConfigReq.set_arbitratoripaddress(IPAddress);
        retVal = SendAMRequest(AMConfigReq);
    }

    return retVal;
}

int CMApiHA::SetAMVirtualAddressInfo(string VirtualIpAddresses, string EthernetInterfaces)
{
    int retVal = CMAPI_SUCCESS;
    if (VirtualIpAddresses.empty() || EthernetInterfaces.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        AvaMgrConfig AMConfigReq;
        AMConfigReq.set_virtualipaddressescidrformat(VirtualIpAddresses);
        AMConfigReq.set_ethernetinterfaces(EthernetInterfaces);
        retVal = SendAMRequest(AMConfigReq);
    }

    return retVal;
}

int CMApiHA::GetNodeStatus(string& nodeStatus,AvaMgrConfigResp* Response)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    ComponentActionReq Request;
    Request.set_requestid(GET_NODESTATUS);
    retVal = SendAMRequest(Request, Response);
    if (retVal == CMAPI_SUCCESS)  // && Response.has_nodestatus())
    {
        nodeStatus = Response->nodestatus();
    }
    return retVal;
}

int CMApiHA::SwitchOver(AvaMgrConfigResp* Response)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    ComponentActionReq Request;
    Request.set_requestid(HA_SWITCHOVER);
    m_AMObj->AvaMgrSwitchOverRequest(Request);
    if(m_HAResponse->Get(StrVal,m_waitTime))
    {
        Response->ParseFromString(StrVal);
        if (Response->has_responseid())
        {
            retVal = Response->responseid();
        }
        CLOG_DEBUG("Received Response %s",Response->DebugString().c_str());
    }
    else
    {
        retVal = CMAPI_TIMEOUT;
        Response->set_responseid(retVal);
        // Fill in errordetails in Response
        ErrorDetails *Err = Response->add_errordetails();
        Err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        Err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }
    return retVal;
}


int CMApiHA::GetAMConfiguration(AvaMgrConfig *AvaMgrData,AvaMgrConfigResp* Response)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    // Request for AM configurations
    if (AvaMgrData == NULL)
    {
        return CMAPI_INVALIDPARAMS;
    }

    ComponentActionReq Request;
    Request.set_requestid(GET_AMCONFIG);
    retVal = SendAMRequest(Request, Response);
    if (retVal == CMAPI_SUCCESS)
    {
        AvaMgrData->CopyFrom(Response->avamgrdata());
    }
    return retVal;
}


int CMApiHA::GetRMConfiguration(RepMgrConfig *RepMgrData)
{
    int retVal = CMAPI_SUCCESS;
    if (RepMgrData == NULL)
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        // Request for RM configurations
        RepMgrConfigResp RepMgrResponse;
        retVal = SendCMgrRequest(*RepMgrData, &RepMgrResponse);
        if (retVal == CMAPI_SUCCESS)
        {
            if (RepMgrResponse.has_repmgrdata())
            {
                RepMgrData->CopyFrom(RepMgrResponse.repmgrdata());
            }
        }
    }
    return retVal;
}


int CMApiHA::SetDREReplicationFlag(bool ReplicateData)
{
    DreHAConfig Request;
    Request.set_replicatedata(ReplicateData);
    int retVal = SendDRERequest(Request);

    return retVal;
}

int CMApiHA::GetDREHAConfiguration(DreHAConfig *DreHAData)
{
    int retVal = CMAPI_SUCCESS;
    if (DreHAData == NULL)
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        // Request for DRE HA configurations
        DreHAConfigResp DreResponse;
        retVal = SendCMgrRequest(*DreHAData, &DreResponse);
        if (retVal == CMAPI_SUCCESS)
        {
            if (DreResponse.has_drehadata())
            {
                DreHAData->CopyFrom(DreResponse.drehadata());
            }
        }
    }
    return retVal;
}


int CMApiHA::AvaMgrSetConfigurationRespCbk(AvaMgrConfigResp *Response)
{
    int retVal = 0;
    std::string StrVal;

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        CLOG_DEBUG("CMAPI: Ignoring response from STANDBY AVAMGR instance : %d", MeSS::Handle().m_src.instance);
        return 0;
    }

    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }

    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            (Response == NULL) )
    {
        AvaMgrConfigResp ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_MESSERROR);
        ErrorResponse.SerializeToString(&StrVal);
        m_HAResponse->Set(StrVal);
    } else if ( Response != NULL && Response->has_responseid() &&
            Response->responseid() != CMAPI_SUCCESS) {
        Response->SerializeToString(&StrVal);
        m_HAResponse->Set(StrVal);
    } else {
        AvaMgrConfig *Request = reinterpret_cast <AvaMgrConfig *> (lCookie->pValue);
        SendCMgrRequest(*Request);
    }
    delete lCookie;
    return retVal;
}

int CMApiHA::AvaMgrGetConfigurationRespCbk(AvaMgrConfigResp *Response)
{
    int retVal = 0;
    std::string StrVal;

    if(!(MESS_ISActiveInst(MeSS::Handle().m_src.instance)))
    {
        CLOG_DEBUG("CMAPI: Ignoring response from STANDBY AVAMGR instance : %d", MeSS::Handle().m_src.instance);
        return 0;
    }
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }


    if ( (Response == NULL) || (MeSS::Handle().m_state != MESS_STATUS_SUCCESS))
    {
        AvaMgrConfigResp ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_MESSERROR);
        ErrorResponse.SerializeToString(&StrVal);
    }  else {
        Response->SerializeToString(&StrVal);
    } 
    m_HAResponse->Set(StrVal);
    return retVal;
}

int CMApiHA::AvaMgrSwitchOverRequestRespCbk(AvaMgrConfigResp *Response)
{
    int retVal = 0;
    if(Response &&  Response->errordetails_size() && Response->errordetails(0).errorcode() != CMAPI_SUCCESS)
    {
        CLOG_DEBUG("Received Response with error code %d, error key %s",Response->errordetails(0).errorcode(),Response->errordetails(0).errormsgkey().c_str());
        std::string StrVal;
        Response->set_responseid(CMAPI_ERROR);
        Response->SerializeToString(&StrVal);
        m_HAResponse->Set(StrVal); 
        retVal = CMAPI_ERROR;
        return retVal;
    }
    if(MESS_ISActiveInst(MeSS::Handle().m_src.instance))
    {
        CLOG_DEBUG("CMAPI: received response from active AVAMGR instance : %d", MeSS::Handle().m_src.instance);
    }
    else
    {
        CLOG_DEBUG("CMAPI: Ignoring response from STANDBY AVAMGR instance : %d", MeSS::Handle().m_src.instance);
    }
    return retVal;
}

int CMApiHA::SetData(int requestId, int retCode)
{
    std::string StrVal;

    if (m_HAResponse->IsDataSet())
    {
        return retCode;
    }

    switch(requestId)
    {
        case HA_SWITCHOVER:
            {
                AvaMgrConfigResp Response;
                Response.set_responseid(CMAPI_SUCCESS);
                Response.SerializeToString(&StrVal);
                break;
            }
        default: 
            return retCode;
    }
    m_HAResponse->Set(StrVal);
    return retCode;
}

int CMApiHA::DreSetConfigurationRespCbk(DreHAConfigResp *Response)
{
    int retVal = 0;
    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }

    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            (Response == NULL) )
    {
        DreHAConfigResp ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_MESSERROR);
        ErrorResponse.SerializeToString(&StrVal);
        m_HAResponse->Set(StrVal);
    } else if ( Response != NULL && Response->has_responseid() &&
            Response->responseid() != CMAPI_SUCCESS) {
        Response->SerializeToString(&StrVal);
        m_HAResponse->Set(StrVal);
    } else {
        DreHAConfig *Request = reinterpret_cast <DreHAConfig *> (lCookie->pValue);
        SendCMgrRequest(*Request);
    }
    delete lCookie;
    return retVal;

}

int CMApiHA::RepMgrSetConfigurationRespCbk(RepMgrConfigResp *Response)
{
    int retVal = 0;
    std::string StrVal;
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            (Response == NULL) )
    {
        RepMgrConfigResp ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_MESSERROR);
        ErrorResponse.SerializeToString(&StrVal);
        m_HAResponse->Set(StrVal);
    } else if ( Response != NULL && Response->has_responseid() &&
            Response->responseid() != CMAPI_SUCCESS) {
        Response->SerializeToString(&StrVal);
        m_HAResponse->Set(StrVal);
    } else {
        RepMgrConfig *Request = reinterpret_cast <RepMgrConfig *> (lCookie->pValue);
        SendCMgrRequest(*Request);
    }
    delete lCookie;
    return retVal;

}


int CMApiHA::CMgrAMSetConfigurationRespCbk(AvaMgrConfigResp *Response)
{
    int retVal = 0;
    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }

    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            (Response == NULL) )
    {
        AvaMgrConfigResp ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_MESSERROR);
        ErrorResponse.SerializeToString(&StrVal);
    } else if ( Response != NULL && Response->has_responseid()) {
        Response->SerializeToString(&StrVal);
    }
    delete lCookie;
    m_HAResponse->Set(StrVal);
    return retVal;
}

int CMApiHA::CMgrRMSetConfigurationRespCbk(RepMgrConfigResp *Response)
{
    int retVal = 0;
    std::string StrVal;
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            (Response == NULL) )
    {
        RepMgrConfigResp ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_MESSERROR);
        ErrorResponse.SerializeToString(&StrVal);
    } else if ( Response != NULL && Response->has_responseid()) {
        Response->SerializeToString(&StrVal);
    }
    delete lCookie;
    m_HAResponse->Set(StrVal);
    return retVal;
}

int CMApiHA::CMgrDreSetConfigurationRespCbk(DreHAConfigResp *Response)
{
    int retVal = 0;
    std::string StrVal;
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            (Response == NULL) )
    {
        DreHAConfigResp ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_MESSERROR);
        ErrorResponse.SerializeToString(&StrVal);
    } else if ( Response != NULL && Response->has_responseid()) {
        Response->SerializeToString(&StrVal);
    }
    delete lCookie;
    m_HAResponse->Set(StrVal);
    return retVal;

}

int CMApiHA::FetchAvaMgrConfigurationRespCbk(AvaMgrConfigResp *Response)
{
    int retVal = 0;
    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }

    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    delete lCookie;
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            (Response == NULL) )
    {
        AvaMgrConfigResp ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_MESSERROR);
        ErrorResponse.SerializeToString(&StrVal);
    } else if ( Response != NULL && Response->has_responseid()) {
        Response->SerializeToString(&StrVal);
    }
    m_HAResponse->Set(StrVal);
    return retVal;
}

int CMApiHA::FetchRepMgrConfigurationRespCbk(RepMgrConfigResp *Response)
{
    int retVal = 0;
    std::string StrVal;
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    delete lCookie;
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            (Response == NULL) )
    {
        RepMgrConfigResp ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_MESSERROR);
        ErrorResponse.SerializeToString(&StrVal);
    } else if ( Response != NULL && Response->has_responseid()) {
        Response->SerializeToString(&StrVal);
    }
    m_HAResponse->Set(StrVal);
    return retVal;
}

int CMApiHA::FetchDreHAConfigurationRespCbk(DreHAConfigResp *Response)
{
    int retVal = 0;
    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }

    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    delete lCookie;
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            (Response == NULL) )
    {
        DreHAConfigResp ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_MESSERROR);
        ErrorResponse.SerializeToString(&StrVal);
    } else if ( Response != NULL && Response->has_responseid()) {
        Response->SerializeToString(&StrVal);
    }
    m_HAResponse->Set(StrVal);
    return retVal;
}

int CMApiHA::SendCMgrRequest(AvaMgrConfig& Request, AvaMgrConfigResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    m_CMgrObj->CMgrAMSetConfiguration(Request, 
            new CMAPICookie(0, (void *) &Request));
    if (m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        Response->set_responseid(retVal);
        m_SendSuccess = true;
        return retVal;
    }

    if (Response != NULL)
    {
        std::string StrVal;
        m_HAResponse->Get(StrVal);
        if (!StrVal.empty())
        {
            Response->ParseFromString(StrVal);
            if (Response->has_responseid())
            {
                retVal = Response->responseid();
            }
        }
    }
    return retVal;
}

int CMApiHA::SendCMgrRequest(RepMgrConfig& Request, RepMgrConfigResp *Response)
{
    int retVal = 0;
    m_SendSuccess = true;
    m_CMgrObj->CMgrRMSetConfiguration(Request, 
            new CMAPICookie(0, (void *) &Request));
    if (m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        Response->set_responseid(retVal);
        m_SendSuccess = true;
        return retVal;
    }

    if (Response != NULL)
    {
        std::string StrVal;
        m_HAResponse->Get(StrVal);
        if (!StrVal.empty())
        {
            Response->ParseFromString(StrVal);
            if (Response->has_responseid())
            {
                retVal = Response->responseid();
            }
        }
    }
    return retVal;

}
int CMApiHA::SendCMgrRequest(DreHAConfig&  Request, DreHAConfigResp  *Response)
{
    int retVal = 0;
    m_SendSuccess = true;
    m_CMgrObj->CMgrDreSetConfiguration(Request, 
            new CMAPICookie(0, (void *) &Request));
    if (m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        Response->set_responseid(retVal);
        m_SendSuccess = true;
        return retVal;
    }

    if (Response != NULL)
    {
        std::string StrVal;
        m_HAResponse->Get(StrVal);
        if (!StrVal.empty())
        {
            Response->ParseFromString(StrVal);
            if (Response->has_responseid())
            {
                retVal = Response->responseid();
            }
        }
    }
    return retVal;
}

int CMApiHA::SendAMRequest(AvaMgrConfig& Request)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    AvaMgrConfigResp Response;
    std::string StrVal;
    m_AMObj->AvaMgrSetConfiguration(Request, 
            new CMAPICookie(0, (void *) &Request));
    if (m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }

    if(m_HAResponse->Get(StrVal,m_waitTime))
    {
        Response.ParseFromString(StrVal);
        if (Response.has_responseid())
        {
            retVal = Response.responseid();
        }
    }
    else
    {
        /*Response.set_respcode(CMAPI_TIMEOUT);
        // Fill in errordetails in Response
        ErrorDetails *err = Response.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");*/
    }
    return retVal;
}

int CMApiHA::SendAMRequest(ComponentActionReq& Request, AvaMgrConfigResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    std::string StrVal;
    m_AMObj->AvaMgrGetConfiguration(Request);
    if (m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        Response->set_responseid(retVal);
        ErrorDetails* Err = Response->add_errordetails();
        Err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        Err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_HAResponse->Get(StrVal,m_waitTime))
    {
        Response->ParseFromString(StrVal);
        if (Response->has_responseid())
        {
            retVal = Response->responseid();
        }
    }
    else
    {
        retVal = CMAPI_TIMEOUT;
        Response->set_responseid(retVal);
        // Fill in errordetails in Response
        ErrorDetails *Err = Response->add_errordetails();
        Err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        Err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }
    return retVal;
}

int CMApiHA::SendRMRequest(RepMgrConfig& Request)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    RepMgrConfigResp Response;
    std::string StrVal;
    m_SendSuccess = true;
    m_RMObj->RepMgrSetConfiguration(Request, 
            new CMAPICookie(0, (void *) &Request));
    if (m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }

    m_HAResponse->Get(StrVal);
    Response.ParseFromString(StrVal);
    if (Response.has_responseid())
    {
        retVal = Response.responseid();
    }
    return retVal;

}

int CMApiHA::SendDRERequest(DreHAConfig& Request)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    DreHAConfigResp Response;
    std::string StrVal;
    m_SendSuccess = true;
    m_DREObj->DreSetConfiguration(Request, 
            new CMAPICookie(0, (void *) &Request));
    if (m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }

    m_HAResponse->Get(StrVal);
    Response.ParseFromString(StrVal);
    if (Response.has_responseid())
    {
        retVal = Response.responseid();
    }
    return retVal;

}



