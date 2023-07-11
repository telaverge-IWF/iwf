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
#include "CMAPILib.h"
#include "CMgrMethods_caller.h"
#include "ErrorResp.h"

//Platform (Stack related API)
//Library API
int CMAPIProdConfig::GetLastCallErrorDetails(ErrorDetails& Err)
{

    Err.CopyFrom(m_lastError);
    return 0;
}

int CMAPIProdConfig::SetLocalHostConfig(LocalHost &LHostInfo)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!LHostInfo.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(SET_LHCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::LocalHost* pLocalHost;
        pLocalHost = pStackConfig->mutable_lhost();

        pLocalHost->CopyFrom(LHostInfo);

        CLOG_DEBUG("Sending SET_LHCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            m_lastError.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::SetLocalHostConfig(LocalHost &LHostInfo, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!LHostInfo.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(SET_LHCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::LocalHost* pLocalHost;
        pLocalHost = pStackConfig->mutable_lhost();

        pLocalHost->CopyFrom(LHostInfo);

        CLOG_DEBUG("Sending SET_LHCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::ModifyLocalHostConfig(LocalHost &LHostInfo)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!LHostInfo.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(MOD_LHCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::LocalHost* pLocalHost;
        pLocalHost = pStackConfig->mutable_lhost();

        pLocalHost->CopyFrom(LHostInfo);

        CLOG_DEBUG("Sending MOD_LHCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            m_lastError.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::ModifyLocalHostConfig(LocalHost &LHostInfo, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!LHostInfo.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(MOD_LHCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::LocalHost* pLocalHost;
        pLocalHost = pStackConfig->mutable_lhost();

        pLocalHost->CopyFrom(LHostInfo);

        CLOG_DEBUG("Sending MOD_LHCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::GetLocalTransportTagConfig(LocalTransportTagResponse &LTTResp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIProdConfig: GetLocalTransportTagConfig");

    LocalTransportTagRequest lLocalTransportTagRequest;
    lLocalTransportTagRequest.set_requestid(GET_LTTAG);

    CLOG_DEBUG("Sending Requesting to get the Local Transport Tag Info");
    // Call Caller Method to Call Server Implementation.
    m_CMgrCallerObj->HandleGetLocalTransportTags(lLocalTransportTagRequest);
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);
    LTTResp.ParseFromString(StrVal);
    retVal = LTTResp.responseid();
    if(LTTResp.errordetails_size())
    {
        m_lastError.CopyFrom(LTTResp.errordetails(0));
    }
    // Return appropriate Return value.
    return retVal;
}


int CMAPIProdConfig::GetLocalHostConfig(LocalHost &LHostInfo)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIProdConfig: GetLocalHostConfig ");

    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(GET_LHCFG);

    CLOG_DEBUG("Sending Locahost Host Config Info");
    // Call Caller Method to Call Server Implementation.
    m_CMgrCallerObj->HandleGetStackConfiguration(lStackRequest);
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);
    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();
    if (Response.has_stackconfig())
    {
        ::StackConfiguration* respStackConfig;
        respStackConfig = Response.mutable_stackconfig();

        if(respStackConfig->has_lhost())
        {
            ::LocalHost* respLocalHost;
            respLocalHost = respStackConfig->mutable_lhost();

            LHostInfo.CopyFrom(*respLocalHost);
        }
    }
    if(Response.errordetails_size())
    {
        m_lastError.CopyFrom(Response.errordetails(0));
    }
    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::GetLocalHostConfig(LocalHost &LHostInfo, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIProdConfig: GetLocalHostConfig ");

    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(GET_LHCFG);

    CLOG_DEBUG("Sending Locahost Host Config Info");
    // Call Caller Method to Call Server Implementation.
    m_CMgrCallerObj->HandleGetStackConfiguration(lStackRequest);
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);
    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();
    if (Response.has_stackconfig())
    {
        ::StackConfiguration* respStackConfig;
        respStackConfig = Response.mutable_stackconfig();

        if(respStackConfig->has_lhost())
        {
            ::LocalHost* respLocalHost;
            respLocalHost = respStackConfig->mutable_lhost();

            LHostInfo.CopyFrom(*respLocalHost);
        }
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }
    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}
int CMAPIProdConfig::AddLocalHostTransport(string lHost, string realm, LHTransport &LHTransport)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!LHTransport.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(ADD_LHTCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::LocalHost* pLocalHost;
        pLocalHost = pStackConfig->mutable_lhost();

        pLocalHost->set_localhostname(lHost);
        pLocalHost->set_realmname(realm);
        ::LHTransport* pLHTransport;
        pLHTransport = pLocalHost->add_transports();

        pLHTransport->CopyFrom(LHTransport);

        CLOG_DEBUG("Sending ADD_LHTCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            m_lastError.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::AddLocalHostTransport(string lHost, string realm, LHTransport &LHTransport, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!LHTransport.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(ADD_LHTCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::LocalHost* pLocalHost;
        pLocalHost = pStackConfig->mutable_lhost();

        pLocalHost->set_localhostname(lHost);
        pLocalHost->set_realmname(realm);
        ::LHTransport* pLHTransport;
        pLHTransport = pLocalHost->add_transports();

        pLHTransport->CopyFrom(LHTransport);

        CLOG_DEBUG("Sending ADD_LHTCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::ModifyLocalHostTransport(string lHost, string realm, LHTransport &LHTransport)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!LHTransport.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(MOD_LHTCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::LocalHost* pLocalHost;
        pLocalHost = pStackConfig->mutable_lhost();

        pLocalHost->set_localhostname(lHost);
        pLocalHost->set_realmname(realm);
        ::LHTransport* pLHTransport;
        pLHTransport = pLocalHost->add_transports();

        pLHTransport->CopyFrom(LHTransport);

        CLOG_DEBUG("Sending MOD_LHTCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);

        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            m_lastError.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::ModifyLocalHostTransport(string lHost, string realm, LHTransport &LHTransport, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!LHTransport.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(MOD_LHTCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::LocalHost* pLocalHost;
        pLocalHost = pStackConfig->mutable_lhost();

        pLocalHost->set_localhostname(lHost);
        pLocalHost->set_realmname(realm);
        ::LHTransport* pLHTransport;
        pLHTransport = pLocalHost->add_transports();

        pLHTransport->CopyFrom(LHTransport);

        CLOG_DEBUG("Sending MOD_LHTCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);

        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::DeleteLocalHostTransport(string lHost, string realm, LHTransport &LHTransport)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!LHTransport.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(DEL_LHTCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::LocalHost* pLocalHost;
        pLocalHost = pStackConfig->mutable_lhost();

        pLocalHost->set_localhostname(lHost);
        pLocalHost->set_realmname(realm);
        ::LHTransport* pLHTransport;
        pLHTransport = pLocalHost->add_transports();

        pLHTransport->CopyFrom(LHTransport);

        CLOG_DEBUG("Sending DEL_LHTCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);

        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            m_lastError.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::DeleteLocalHostTransport(string lHost, string realm, LHTransport &LHTransport, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!LHTransport.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(DEL_LHTCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::LocalHost* pLocalHost;
        pLocalHost = pStackConfig->mutable_lhost();

        pLocalHost->set_localhostname(lHost);
        pLocalHost->set_realmname(realm);
        ::LHTransport* pLHTransport;
        pLHTransport = pLocalHost->add_transports();

        pLHTransport->CopyFrom(LHTransport);

        CLOG_DEBUG("Sending DEL_LHTCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);

        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::SetSctpProtocolConfiguration(SctpProtocol& SctpCfg)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!SctpCfg.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(SET_SCTPCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::SctpProtocol* pSctpProtocol;
        pSctpProtocol = pStackConfig->mutable_sctp();

        pSctpProtocol->CopyFrom(SctpCfg);


        CLOG_DEBUG("Sending SET_SCTPCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            m_lastError.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::SetSctpProtocolConfiguration(SctpProtocol& SctpCfg, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!SctpCfg.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(SET_SCTPCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::SctpProtocol* pSctpProtocol;
        pSctpProtocol = pStackConfig->mutable_sctp();

        pSctpProtocol->CopyFrom(SctpCfg);


        CLOG_DEBUG("Sending SET_SCTPCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::GetSctpProtocolConfiguration(SctpProtocol& SctpCfg)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIProdConfig: GetLocalHostConfig ");

    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(GET_SCTPCFG);

    CLOG_DEBUG("Sending Locahost Host Config Info");
    // Call Caller Method to Call Server Implementation.
    m_CMgrCallerObj->HandleGetStackConfiguration(lStackRequest);
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);
    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();
    if (Response.has_stackconfig())
    {
        ::StackConfiguration* respStackConfig;
        respStackConfig = Response.mutable_stackconfig();

        if(respStackConfig->has_sctp())
        {
            ::SctpProtocol* respSctpProtocol;
            respSctpProtocol = respStackConfig->mutable_sctp();

            SctpCfg.CopyFrom(*respSctpProtocol);
        }
    }
    if(Response.errordetails_size())
    {
        m_lastError.CopyFrom(Response.errordetails(0));
    }
    // Return appropriate Return value.
    return retVal;

}

int CMAPIProdConfig::GetSctpProtocolConfiguration(SctpProtocol& SctpCfg, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIProdConfig: GetLocalHostConfig ");

    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(GET_SCTPCFG);

    CLOG_DEBUG("Sending Locahost Host Config Info");
    // Call Caller Method to Call Server Implementation.
    m_CMgrCallerObj->HandleGetStackConfiguration(lStackRequest);
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);
    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();
    if (Response.has_stackconfig())
    {
        ::StackConfiguration* respStackConfig;
        respStackConfig = Response.mutable_stackconfig();

        if(respStackConfig->has_sctp())
        {
            ::SctpProtocol* respSctpProtocol;
            respSctpProtocol = respStackConfig->mutable_sctp();

            SctpCfg.CopyFrom(*respSctpProtocol);
        }
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }
    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::SetGeneralConfiguration(GeneralConfig& gCfg)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!gCfg.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(SET_GENCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::GeneralConfig* pGeneralConfig;
        pGeneralConfig = pStackConfig->mutable_gconfig();

        pGeneralConfig->CopyFrom(gCfg);


        CLOG_DEBUG("Sending SET_GENCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            m_lastError.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::SetGeneralConfiguration(GeneralConfig& gCfg, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!gCfg.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(SET_GENCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::GeneralConfig* pGeneralConfig;
        pGeneralConfig = pStackConfig->mutable_gconfig();

        pGeneralConfig->CopyFrom(gCfg);


        CLOG_DEBUG("Sending SET_GENCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::GetGeneralConfiguration(GeneralConfig& gCfg)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIProdConfig: GetGeneralConfiguration");

    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(GET_GENCFG);

    CLOG_DEBUG("Sending Locahost Host Config Info");
    // Call Caller Method to Call Server Implementation.
    m_CMgrCallerObj->HandleGetStackConfiguration(lStackRequest);
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);
    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();
    if (Response.has_stackconfig())
    {
        ::StackConfiguration* respStackConfig;
        respStackConfig = Response.mutable_stackconfig();

        if(respStackConfig->has_gconfig())
        {
            ::GeneralConfig* respGeneralConfig;
            respGeneralConfig = respStackConfig->mutable_gconfig();

            gCfg.CopyFrom(*respGeneralConfig);
        }
    }
    if(Response.errordetails_size())
    {
        m_lastError.CopyFrom(Response.errordetails(0));
    }
    // Return appropriate Return value.
    return retVal;

}

int CMAPIProdConfig::GetGeneralConfiguration(GeneralConfig& gCfg, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIProdConfig: GetGeneralConfiguration");

    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(GET_GENCFG);

    CLOG_DEBUG("Sending Locahost Host Config Info");
    // Call Caller Method to Call Server Implementation.
    m_CMgrCallerObj->HandleGetStackConfiguration(lStackRequest);
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);
    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();
    if (Response.has_stackconfig())
    {
        ::StackConfiguration* respStackConfig;
        respStackConfig = Response.mutable_stackconfig();

        if(respStackConfig->has_gconfig())
        {
            ::GeneralConfig* respGeneralConfig;
            respGeneralConfig = respStackConfig->mutable_gconfig();

            gCfg.CopyFrom(*respGeneralConfig);
        }
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }
    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;

}

int CMAPIProdConfig::AddCACRLConfiguration(TrustedCAConfiguration& CaCrl)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!CaCrl.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(ADD_CACRLCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::CACRLs* pCACRLs;
        pCACRLs = pStackConfig->mutable_cacrl();

        ::TrustedCAConfiguration* pTrustedCAConfiguration;
        pTrustedCAConfiguration = pCACRLs->add_tcacfg();

        pTrustedCAConfiguration->CopyFrom(CaCrl);


        CLOG_DEBUG("Sending ADD_CACRLCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            m_lastError.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    return retVal;

}

int CMAPIProdConfig::AddCACRLConfiguration(TrustedCAConfiguration& CaCrl, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!CaCrl.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(ADD_CACRLCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::CACRLs* pCACRLs;
        pCACRLs = pStackConfig->mutable_cacrl();

        ::TrustedCAConfiguration* pTrustedCAConfiguration;
        pTrustedCAConfiguration = pCACRLs->add_tcacfg();

        pTrustedCAConfiguration->CopyFrom(CaCrl);


        CLOG_DEBUG("Sending ADD_CACRLCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;

}

int CMAPIProdConfig::RemoveCACRLAssociation(TrustedCAConfiguration& CaCrl)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    if (!CaCrl.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(REM_CACRLASSOC);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::CACRLs* pCACRLs;
        pCACRLs = pStackConfig->mutable_cacrl();

        ::TrustedCAConfiguration* pTrustedCAConfiguration;
        pTrustedCAConfiguration = pCACRLs->add_tcacfg();

        pTrustedCAConfiguration->CopyFrom(CaCrl);


        CLOG_DEBUG("Sending REM_CACRLASSOC for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        StackConfigResponse Response;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            Response.ParseFromString(StrVal);
            retVal = Response.responseid();
            if(Response.errordetails_size())
            {
                m_lastError.CopyFrom(Response.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response.add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::RemoveCACRLAssociation(TrustedCAConfiguration& CaCrl, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    if (!CaCrl.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(REM_CACRLASSOC);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::CACRLs* pCACRLs;
        pCACRLs = pStackConfig->mutable_cacrl();

        ::TrustedCAConfiguration* pTrustedCAConfiguration;
        pTrustedCAConfiguration = pCACRLs->add_tcacfg();

        pTrustedCAConfiguration->CopyFrom(CaCrl);


        CLOG_DEBUG("Sending REM_CACRLASSOC for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        StackConfigResponse Response;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            Response.ParseFromString(StrVal);
            retVal = Response.responseid();
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err.set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err.set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::DeleteCACRLConfiguration(TrustedCAConfiguration& CaCrl)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    if (!CaCrl.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(DEL_CACRLCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::CACRLs* pCACRLs;
        pCACRLs = pStackConfig->mutable_cacrl();

        ::TrustedCAConfiguration* pTrustedCAConfiguration;
        pTrustedCAConfiguration = pCACRLs->add_tcacfg();

        pTrustedCAConfiguration->CopyFrom(CaCrl);


        CLOG_DEBUG("Sending DEL_CACRLCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        StackConfigResponse Response;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            Response.ParseFromString(StrVal);
            retVal = Response.responseid();
            if(Response.errordetails_size())
            {
                m_lastError.CopyFrom(Response.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response.add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }

    }

    // Return appropriate Return value.
    return retVal;

}

int CMAPIProdConfig::DeleteCACRLConfiguration(TrustedCAConfiguration& CaCrl, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    if (!CaCrl.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(DEL_CACRLCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::CACRLs* pCACRLs;
        pCACRLs = pStackConfig->mutable_cacrl();

        ::TrustedCAConfiguration* pTrustedCAConfiguration;
        pTrustedCAConfiguration = pCACRLs->add_tcacfg();

        pTrustedCAConfiguration->CopyFrom(CaCrl);


        CLOG_DEBUG("Sending DEL_CACRLCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        StackConfigResponse Response;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            Response.ParseFromString(StrVal);
            retVal = Response.responseid();
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            //ErrorDetails *err = Response.add_errordetails();
            err.set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err.set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }

    }

    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::ModifyCACRLConfiguration(TrustedCAConfiguration& CaCrl)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!CaCrl.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(MOD_CACRLCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::CACRLs* pCACRLs;
        pCACRLs = pStackConfig->mutable_cacrl();

        ::TrustedCAConfiguration* pTrustedCAConfiguration;
        pTrustedCAConfiguration = pCACRLs->add_tcacfg();

        pTrustedCAConfiguration->CopyFrom(CaCrl);


        CLOG_DEBUG("Sending MOD_CACRLCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            m_lastError.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    return retVal;

}

int CMAPIProdConfig::ModifyCACRLConfiguration(TrustedCAConfiguration& CaCrl, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!CaCrl.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(MOD_CACRLCFG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::CACRLs* pCACRLs;
        pCACRLs = pStackConfig->mutable_cacrl();

        ::TrustedCAConfiguration* pTrustedCAConfiguration;
        pTrustedCAConfiguration = pCACRLs->add_tcacfg();

        pTrustedCAConfiguration->CopyFrom(CaCrl);


        CLOG_DEBUG("Sending MOD_CACRLCFG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::GetCACRLConfiguration(CACRLs& CaCrl)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIProdConfig: GetLocalHostConfig ");

    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(GET_CACRLCFG);

    CLOG_DEBUG("Sending Locahost Host Config Info");
    // Call Caller Method to Call Server Implementation.
    m_CMgrCallerObj->HandleGetStackConfiguration(lStackRequest);
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);
    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();
    if (Response.has_stackconfig())
    {
        ::StackConfiguration* respStackConfig;
        respStackConfig = Response.mutable_stackconfig();

        ::CACRLs* pCACRLs;
        pCACRLs = respStackConfig->mutable_cacrl();

        CaCrl.CopyFrom(*pCACRLs);
    }
    if(Response.errordetails_size())
    {
        m_lastError.CopyFrom(Response.errordetails(0));
    }
    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::GetCACRLConfiguration(CACRLs& CaCrl, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIProdConfig: GetLocalHostConfig ");

    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(GET_CACRLCFG);

    CLOG_DEBUG("Sending Locahost Host Config Info");
    // Call Caller Method to Call Server Implementation.
    m_CMgrCallerObj->HandleGetStackConfiguration(lStackRequest);
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);
    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();
    if (Response.has_stackconfig())
    {
        ::StackConfiguration* respStackConfig;
        respStackConfig = Response.mutable_stackconfig();

        ::CACRLs* pCACRLs;
        pCACRLs = respStackConfig->mutable_cacrl();

        CaCrl.CopyFrom(*pCACRLs);
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }
    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::GetTLSConfiguration(TLSConfig& tls)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIProdConfig: GetLocalHostConfig ");

    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(GET_TLSCONFIG);

    CLOG_DEBUG("Sending Locahost Host Config Info");
    // Call Caller Method to Call Server Implementation.
    m_CMgrCallerObj->HandleGetStackConfiguration(lStackRequest);

    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);

    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();

    if (Response.has_stackconfig())
    {
        ::StackConfiguration* respStackConfig;
        respStackConfig = Response.mutable_stackconfig();

        if(respStackConfig->has_tconfig())
        {
            ::TLSConfig* respTLSConfig;
            respTLSConfig = respStackConfig->mutable_tconfig();

            tls.CopyFrom(*respTLSConfig);
        }
    }
    if(Response.errordetails_size())
    {
        m_lastError.CopyFrom(Response.errordetails(0));
    }
    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::GetTLSConfiguration(TLSConfig& tls, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIProdConfig: GetLocalHostConfig ");

    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(GET_TLSCONFIG);

    CLOG_DEBUG("Sending Locahost Host Config Info");
    // Call Caller Method to Call Server Implementation.
    m_CMgrCallerObj->HandleGetStackConfiguration(lStackRequest);

    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);

    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();

    if (Response.has_stackconfig())
    {
        ::StackConfiguration* respStackConfig;
        respStackConfig = Response.mutable_stackconfig();

        if(respStackConfig->has_tconfig())
        {
            ::TLSConfig* respTLSConfig;
            respTLSConfig = respStackConfig->mutable_tconfig();

            tls.CopyFrom(*respTLSConfig);
        }
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }
    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::SetTLSConfiguration(TLSConfig& tls)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!tls.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(SET_TLSCONFIG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::TLSConfig* pTLSConfig;
        pTLSConfig = pStackConfig->mutable_tconfig();

        pTLSConfig->CopyFrom(tls);


        CLOG_DEBUG("Sending SET_TLSCONFIG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            m_lastError.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::SetTLSConfiguration(TLSConfig& tls, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!tls.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(SET_TLSCONFIG);

        ::StackConfiguration* pStackConfig;
        pStackConfig =  lStackRequest.mutable_stackconfig();

        ::TLSConfig* pTLSConfig;
        pTLSConfig = pStackConfig->mutable_tconfig();

        pTLSConfig->CopyFrom(tls);


        CLOG_DEBUG("Sending SET_TLSCONFIG for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }

    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::GetTlsCipherCfg(TLSCipherConfigs& tlsCipher)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIProdConfig: GetTlsCipherCfg ");

    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(GET_CIPHERSUITE);

    CLOG_DEBUG("Sending Cipher suit Config Info");
    // Call Caller Method to Call Server Implementation.
    m_CMgrCallerObj->HandleGetStackConfiguration(lStackRequest);

    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);

    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();

    if (Response.has_stackconfig())
    {
        ::StackConfiguration* respStackConfig;
        respStackConfig = Response.mutable_stackconfig();

        if(respStackConfig->has_tlsciphers())
        {
            ::TLSCipherConfigs* respTLSCipherConfigs;
            respTLSCipherConfigs = respStackConfig->mutable_tlsciphers();

            tlsCipher.CopyFrom(*respTLSCipherConfigs);
        }
    }
    if(Response.errordetails_size())
    {
        m_lastError.CopyFrom(Response.errordetails(0));
    }
    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::GetTlsCipherCfg(TLSCipherConfigs& tlsCipher, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIProdConfig: GetTlsCipherCfg ");

    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(GET_CIPHERSUITE);

    CLOG_DEBUG("Sending Cipher suit Config Info");
    // Call Caller Method to Call Server Implementation.
    m_CMgrCallerObj->HandleGetStackConfiguration(lStackRequest);

    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);

    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();

    if (Response.has_stackconfig())
    {
        ::StackConfiguration* respStackConfig;
        respStackConfig = Response.mutable_stackconfig();

        if(respStackConfig->has_tlsciphers())
        {
            ::TLSCipherConfigs* respTLSCipherConfigs;
            respTLSCipherConfigs = respStackConfig->mutable_tlsciphers();

            tlsCipher.CopyFrom(*respTLSCipherConfigs);
        }
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }
    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::EnableTlsCipherSuite(string TlsCiphersuiteName)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(MOD_CIPHERSUITE);

    ::StackConfiguration* pStackConfig;
    pStackConfig =  lStackRequest.mutable_stackconfig();

    ::TLSCipherConfigs* pTLSCipherConfigs;
    pTLSCipherConfigs = pStackConfig->mutable_tlsciphers();

    ::TLSCipherConfig* pTLSCipherConfig;
    pTLSCipherConfig = pTLSCipherConfigs->add_tlsciphers();

    pTLSCipherConfig->set_ciphersuitename(TlsCiphersuiteName);
    pTLSCipherConfig->set_enableciphersuite(true);


    CLOG_DEBUG("Sending MOD_CIPHERSUITE for LocalHostConfig");
    // Call DRE Method Implementation.
    m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);
    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();
    if(Response.errordetails_size())
    {
        m_lastError.CopyFrom(Response.errordetails(0));
    }


    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::EnableTlsCipherSuite(string TlsCiphersuiteName, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(MOD_CIPHERSUITE);

    ::StackConfiguration* pStackConfig;
    pStackConfig =  lStackRequest.mutable_stackconfig();

    ::TLSCipherConfigs* pTLSCipherConfigs;
    pTLSCipherConfigs = pStackConfig->mutable_tlsciphers();

    ::TLSCipherConfig* pTLSCipherConfig;
    pTLSCipherConfig = pTLSCipherConfigs->add_tlsciphers();

    pTLSCipherConfig->set_ciphersuitename(TlsCiphersuiteName);
    pTLSCipherConfig->set_enableciphersuite(true);


    CLOG_DEBUG("Sending MOD_CIPHERSUITE for LocalHostConfig");
    // Call DRE Method Implementation.
    m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);
    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }


    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::DisableTlsCipherSuite(string TlsCiphersuiteName)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(MOD_CIPHERSUITE);

    ::StackConfiguration* pStackConfig;
    pStackConfig =  lStackRequest.mutable_stackconfig();

    ::TLSCipherConfigs* pTLSCipherConfigs;
    pTLSCipherConfigs = pStackConfig->mutable_tlsciphers();

    ::TLSCipherConfig* pTLSCipherConfig;
    pTLSCipherConfig = pTLSCipherConfigs->add_tlsciphers();

    pTLSCipherConfig->set_ciphersuitename(TlsCiphersuiteName);
    pTLSCipherConfig->set_enableciphersuite(false);


    CLOG_DEBUG("Sending MOD_CIPHERSUITE for LocalHostConfig");
    // Call DRE Method Implementation.
    m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);
    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();
    if(Response.errordetails_size())
    {
        m_lastError.CopyFrom(Response.errordetails(0));
    }


    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::DisableTlsCipherSuite(string TlsCiphersuiteName, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    StackConfigRequest lStackRequest;
    lStackRequest.set_requestid(MOD_CIPHERSUITE);

    ::StackConfiguration* pStackConfig;
    pStackConfig =  lStackRequest.mutable_stackconfig();

    ::TLSCipherConfigs* pTLSCipherConfigs;
    pTLSCipherConfigs = pStackConfig->mutable_tlsciphers();

    ::TLSCipherConfig* pTLSCipherConfig;
    pTLSCipherConfig = pTLSCipherConfigs->add_tlsciphers();

    pTLSCipherConfig->set_ciphersuitename(TlsCiphersuiteName);
    pTLSCipherConfig->set_enableciphersuite(false);


    CLOG_DEBUG("Sending MOD_CIPHERSUITE for LocalHostConfig");
    // Call DRE Method Implementation.
    m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    m_CMAPIResponse->Get(StrVal);
    StackConfigResponse Response;
    Response.ParseFromString(StrVal);
    retVal = Response.responseid();
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }


    // Return appropriate Return value.
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}


// MeSS Callbacks
int CMAPIProdConfig::HandleGetLocalTransportTagsRespCbk(LocalTransportTagResponse *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">HandleGetLocalTransportTagsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("HandleGetLocalTransportTagsRespCbk message failed. Error: ");
        if (resp == NULL )
        {
            LocalTransportTagResponse ErrorResponse;
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

// MeSS Callbacks
int CMAPIProdConfig::HandleGetStackConfigurationRespCbk(StackConfigResponse *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">HandleGetStackConfigurationRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("HandleGetStackConfigurationRespCbk message failed. Error: ");
        if (resp == NULL )
        {
            StackConfigResponse ErrorResponse;
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

int CMAPIProdConfig::HandleSetStackConfigurationRespCbk(StackConfigResponse *resp)
{

    int retVal = 0;
    CLOG_DEBUG("> HandleSetStackConfigurationRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("HandleSetStackConfigurationRespCbk message failed. Error: ");
        if (resp == NULL )
        {
            StackConfigResponse ErrorResponse;
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

int CMAPIProdConfig::AddSecIPToLocalHost(LocalHost &lHost)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!lHost.has_localhostname() && !lHost.has_realmname() &&
            !(lHost.transports_size() > 4 || lHost.transports_size() <= 0))
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else  {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(ADD_SECIP);

        StackConfiguration* pStackConfig =  lStackRequest.mutable_stackconfig();
        LocalHost* pLocalHost = pStackConfig->mutable_lhost();

        pLocalHost->CopyFrom(lHost);

        CLOG_DEBUG("Sending Add Secondary Ip Address request ");
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            m_lastError.CopyFrom(Response.errordetails(0));
        }
    }
    return retVal;
}

int CMAPIProdConfig::AddSecIPToLocalHost(LocalHost &lHost, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!lHost.has_localhostname() && !lHost.has_realmname() &&
            !(lHost.transports_size() > 4 || lHost.transports_size() <= 0))
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else  {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(ADD_SECIP);

        StackConfiguration* pStackConfig =  lStackRequest.mutable_stackconfig();
        LocalHost* pLocalHost = pStackConfig->mutable_lhost();

        pLocalHost->CopyFrom(lHost);

        CLOG_DEBUG("Sending Add Secondary Ip Address request ");
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::DeleteSecIPFromLocalHost(LocalHost &lHost)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!lHost.has_localhostname() && !lHost.has_realmname() &&
            !(lHost.transports_size() > 4 || lHost.transports_size() <= 0))
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else  {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(DEL_LOCALHOST_SECIP);

        StackConfiguration* pStackConfig =  lStackRequest.mutable_stackconfig();
        LocalHost* pLocalHost = pStackConfig->mutable_lhost();

        pLocalHost->CopyFrom(lHost);

        CLOG_DEBUG("Sending Delete Secondary Ip Address request ");
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            m_lastError.CopyFrom(Response.errordetails(0));
        }
    }
    return retVal;
}

int CMAPIProdConfig::DeleteSecIPFromLocalHost(LocalHost &lHost, ErrorDetails& err)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!lHost.has_localhostname() && !lHost.has_realmname() &&
            !(lHost.transports_size() > 4 || lHost.transports_size() <= 0))
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else  {
        StackConfigRequest lStackRequest;
        lStackRequest.set_requestid(DEL_LOCALHOST_SECIP);

        StackConfiguration* pStackConfig =  lStackRequest.mutable_stackconfig();
        LocalHost* pLocalHost = pStackConfig->mutable_lhost();

        pLocalHost->CopyFrom(lHost);

        CLOG_DEBUG("Sending Delete Secondary Ip Address request ");
        m_CMgrCallerObj->HandleSetStackConfiguration(lStackRequest);
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        StackConfigResponse Response;
        Response.ParseFromString(StrVal);
        retVal = Response.responseid();
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}


