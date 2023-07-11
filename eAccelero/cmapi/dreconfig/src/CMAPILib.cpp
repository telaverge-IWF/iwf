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
#include "ErrorResp.h"
#include "CMAPILib.h"
#include "ComponentDefines.h"
#include "CMgrMethods_caller.h"
#include "PeerStats_caller.h"
#include "PeerStats_def.h"
#include "TraceConfigFetch_caller.h"
//#include "StaticRoutingTableConfigFetch_caller.h"
//#define CMGR_INSTANCE_ID  MESS_MIN_ACTIVE_INSTANCE
//#define DRE_INSTANCE_ID   MESS_MIN_ACTIVE_INSTANCE

int CMAPIProdConfig::InitializeLibrary()
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG(">CMAPIProdConfig: InitializeLibrary\n");
    CLOG_DEBUG("InitializeLibrary: Initializing Config Manager Interface");
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, CMGR_INSTANCE_ID};
    m_CMgrCallerObj = new Stub::CMgrMethods(dest, 0);
    Stub::CMgrMethodsRespCbk::RegisterCMgrMethodsRespHandler();

    m_CMgrTemplateCallerObj = new Stub::CMgrTemplateMethods(dest, 0);
    Stub::CMgrTemplateMethodsRespCbk::RegisterCMgrTemplateMethodsRespHandler();

    m_StaticRoutingConfigObj = new Stub::CMgrStaticRoutingTableMethods(dest, 0);
    Stub::CMgrStaticRoutingTableMethodsRespCbk::RegisterCMgrStaticRoutingTableMethodsRespHandler();

    CLOG_DEBUG("InitializeLibrary: Initializing DRE Application Interface");
    MeSSEndpoint Dredest = {COMP_DRE_APP, DRE_INSTANCE_ID};
    m_PeerStatsObj = new Stub::PeerStats(Dredest,0);
    Stub::PeerStatsRespCbk::RegisterPeerStatsRespHandler();

    m_TraceConfigObj = new Stub::TraceConfigFetch(Dredest,0);
    Stub::TraceConfigFetchRespCbk::RegisterTraceConfigFetchRespHandler();

    m_CMAPIResponse = new CMAPIIntSync();

    return retVal;
}

int CMAPIProdConfig::GetLocalHostConfig(LocalHostConfig& LocalHost,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    // Build a LocalHostConfig Request
    // Set Local Host Name to be fetched
    CLOG_DEBUG(">CMAPIProdConfig: GetLocalHostConfig ");
    LocalHostConfig lHost;
    lHost.set_operreqid(GET_HOST);

    CLOG_DEBUG("Sending Locahost Host Config Info");
    // Call Caller Method to Call Server Implementation.
    m_CMgrCallerObj->HandleGetLocalHostConfigReqs(lHost,
            new CMAPICookie(GET_HOST, (void *) &lHost));
    std::string StrVal;
    m_CMAPIResponse->Get(StrVal);
    DRECfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respcode();
    if (Response.has_localhost())
    {
        LocalHost.CopyFrom(Response.localhost());
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }
    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::SetLocalHostConfig(LocalHostConfig& LHostInfo,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    if (!LHostInfo.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        LHostInfo.set_operreqid(SET_HOST);
        CLOG_DEBUG("Sending SET_HOST for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetLocalHostConfigReqs(LHostInfo,
                new CMAPICookie(SET_HOST, (void *) &LHostInfo ));
        std::string StrVal;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMAPIProdConfig::ModifyLocalHostConfig(LocalHostConfig& LHostInfo,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    if (!LHostInfo.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        LHostInfo.set_operreqid(MOD_HOST);
        CLOG_DEBUG("Sending MOD_HOST for LocalHostConfig");
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetLocalHostConfigReqs(LHostInfo,
                new CMAPICookie(MOD_HOST, (void *) &LHostInfo ));
        std::string StrVal;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}
int CMAPIProdConfig::DeleteLocalHostConfig(string Hostname, string RealmName,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG(">DeleteLocalHostConfig ");
    if ( Hostname.empty() || RealmName.empty() )
    {
        CLOG_DEBUG(">DeleteLocalHostConfig : ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        // Build Request Information
        LocalHostConfig lHost;
        lHost.set_localhostname(Hostname);
        lHost.set_realmname(RealmName);
        lHost.set_operreqid(DEL_HOST);

        CLOG_DEBUG("Sending DEL_HOST request for Local Host: %s - %s", Hostname.c_str(), RealmName.c_str());

        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetLocalHostConfigReqs(lHost,
                new CMAPICookie(DEL_HOST, (void *) &lHost));
        std::string StrVal;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // return
    return retVal;
}

int CMAPIProdConfig::SetLocalHostAuthTimers(int LifeTime, int GraceTime, int Timeout,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG(">SetLocalHostAuthTimers ");
    if (LifeTime < 0 || GraceTime < 0 || Timeout < 0)
    {
        CLOG_DEBUG(">SetLocalHostAuthTimers : ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        LocalHostConfig lHost;
        lHost.set_authsessionlifetime(LifeTime);
        lHost.set_authsessiongraceperiod(GraceTime);
        lHost.set_authsessiontimeout(Timeout);
        lHost.set_operreqid(SET_AUTHTIMERS);

        CLOG_DEBUG(">SetLocalHostAuthTimers : AUTH Timers %d %d %d", LifeTime, GraceTime, Timeout);
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetLocalHostConfigReqs(lHost,
                new CMAPICookie(SET_AUTHTIMERS, (void *) &lHost));
        std::string StrVal;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return
    return retVal;
}

int CMAPIProdConfig::SetLocalHostAcctTimers(int Interim, int RealTime, int Timeout,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG(">SetLocalHostAcctTimers ");
    if (Interim < 0 || RealTime < 0 || Timeout < 0)
    {
        CLOG_DEBUG(">SetLocalHostAcctTimers : ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        LocalHostConfig lHost;
        lHost.set_acctsessioninteriminterval(Interim);
        lHost.set_acctsessionrealtime(RealTime);
        lHost.set_acctsessiontimeout(Timeout);
        lHost.set_operreqid(SET_ACCTTIMERS);

        CLOG_DEBUG(">SetLocalHostAcctTimers : ACCT Timers %d %d %d", Interim, RealTime, Timeout);
        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetLocalHostConfigReqs(lHost,
                new CMAPICookie(SET_ACCTTIMERS, (void *) &lHost));
        std::string StrVal;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return
    return retVal;
}

int CMAPIProdConfig::SetLocalHostIPAddr(string ipaddr,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG(">SetLocalHostIPAddr ");

    if ( ipaddr.empty() )
    {
        CLOG_DEBUG(">SetLocalHostIPAddr : ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        LocalHostConfig lHost;
        lHost.set_hostipaddr(ipaddr);
        lHost.set_operreqid(SET_HOSTIP);

        CLOG_DEBUG(">SetLocalHostIPAddr SET_HOSTIP %s", ipaddr.c_str());

        // Call DRE Method Implementation.
        m_CMgrCallerObj->HandleSetLocalHostConfigReqs(lHost,
                new CMAPICookie(SET_HOSTIP, (void *) &lHost));
        std::string StrVal;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return
    return retVal;

}

// ***********************************************************************

int CMAPIProdConfig::GetRealm(string realmname, RealmConfig& Realm,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    CLOG_DEBUG(">GetRealm ");

    if (realmname.empty())
    {
        CLOG_DEBUG("GetRealm : ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        RealmsConfig Realms;
        RealmConfig *realm = Realms.add_realms();
        realm->set_realmname(realmname);
        Realms.set_operreqid(GET_REALM);

        CLOG_DEBUG("GetRealm : GET_REALM Request : %s", realmname.c_str());
        m_CMgrCallerObj->HandleGetRealmConfigReqs(Realms,
                new CMAPICookie(GET_REALM, (void *) &Realms));
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
        DRECfgResp Response;
        Response.ParseFromString(StrVal);
        retVal = Response.respcode();
        if (Response.has_realms())
        {
            RealmsConfig realms = Response.realms();
            Realm.CopyFrom(realms.realms(0));
        }
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }
    //return
    return retVal;
}

int CMAPIProdConfig::GetUniqueRealmsOfPeer(RealmsConfig& Realms,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    PeersConfig Peers;
    Peers.set_operreqid(GET_REALMOFPEER);
    m_CMgrCallerObj->HandleGetPeerConfigReqs(Peers,
            new CMAPICookie(GET_REALMOFPEER, (void *) &Peers));
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
    DRECfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respcode();
    if (Response.has_realms())
    {
        Realms.CopyFrom(Response.realms());
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }
    return retVal;
}

int CMAPIProdConfig::GetRealmRouting(string RealmName, RealmConfig& Realm,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    //RealmsConfig Realms;
    RealmsConfig Realms;
    Realms.set_operreqid(GET_DEST);
    if (!RealmName.empty())
    {
        RealmConfig *realm = Realms.add_realms();
        realm->set_realmname(RealmName);
    }

    m_CMgrCallerObj->HandleGetRealmConfigReqs(Realms,
            new CMAPICookie(GET_DEST, (void *) &Realms));
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
    DRECfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respcode();
    if (Response.has_realms())
    {
        RealmsConfig *realms = Response.mutable_realms();
        RealmConfig realm;
        int iCount = realms->realms_size();

        if(iCount >= 0)
        {
            realm = realms->realms(0);
            Realm.CopyFrom(realm);
        }
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }
    return retVal;
}

int CMAPIProdConfig::GetDestination(string RealmName, RealmsConfig& Realm,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    //RealmsConfig Realms;
    //Realms.set_operreqid(GET_REALM);
    Realm.set_operreqid(GET_REALM);
    if (!RealmName.empty())
    {
        RealmConfig *realm = Realm.add_realms();
        realm->set_realmname(RealmName);
    }

    m_CMgrCallerObj->HandleGetRealmConfigReqs(Realm,
            new CMAPICookie(GET_DEST, (void *) &Realm));
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
    DRECfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respcode();
    if (Response.has_realms())
    {
        Realm.CopyFrom(Response.realms());
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }
    return retVal;
}

int CMAPIProdConfig::GetAllRealms(RealmsConfig& Realms,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    CLOG_DEBUG(">GetAllRealms ");
    RealmsConfig realms;
    realms.set_operreqid(GET_REALM);

    CLOG_DEBUG("GetRealm : GET_REALM ALL Request ");
    m_CMgrCallerObj->HandleGetRealmConfigReqs(realms,
            new CMAPICookie(GET_REALM, (void *) &realms));
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
    DRECfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respcode();
    if (Response.has_realms())
    {
        Realms.CopyFrom(Response.realms());
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }
    //return
    return retVal;

}

int CMAPIProdConfig::SetRealm(RealmsConfig& RealmInfo,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!RealmInfo.IsInitialized())
    {
        retVal = CMAPI_INVALIDPARAMS;
    }
    else
    {
        RealmInfo.set_operreqid(SET_REALM);
        CLOG_DEBUG("SetRealm SET_REALM Request : ");
        m_CMgrCallerObj->HandleSetRealmConfigReqs(RealmInfo,
                new CMAPICookie(SET_REALM, (void *) &RealmInfo));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // return
    return retVal;
}

int CMAPIProdConfig::ModifyRealm(RealmsConfig& RealmInfo,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!RealmInfo.IsInitialized())
    {
        retVal = CMAPI_INVALIDPARAMS;
    }
    else
    {
        RealmInfo.set_operreqid(MOD_REALM);
        CLOG_DEBUG("SetRealm SET_REALM Request : ");
        m_CMgrCallerObj->HandleSetRealmConfigReqs(RealmInfo,
                new CMAPICookie(MOD_REALM, (void *) &RealmInfo));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // return
    return retVal;
}

int CMAPIProdConfig::DissociateRealmTemplate(string RealmName,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    CLOG_DEBUG(">DissociateRealmTemplate");
    CLOG_DEBUG("Realm Name = %s",RealmName.c_str());
    if (RealmName.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG("DissociateRealmTemplate Invalid Params ");
    }
    else
    {
        RealmsConfig Realms;
        RealmConfig *Realm = Realms.add_realms();
        Realm->set_realmname(RealmName);
        Realms.set_operreqid(DISSOCIATE_REALM_TEMPLATE);
        CLOG_DEBUG("Realms.operreqid():%d",Realms.operreqid());

        CLOG_DEBUG("Realm: DISSOCIATE_REALM_TEMPLATE Request : %s", RealmName.c_str());
        m_CMgrCallerObj->HandleSetRealmConfigReqs(Realms,
                new CMAPICookie(DISSOCIATE_REALM_TEMPLATE, (void *) &Realms));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // return
    return retVal;
}

int CMAPIProdConfig::DeleteRealm(string RealmName,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    CLOG_DEBUG(">DeleteRealm");
    if (RealmName.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG("DeleteRealm Invalid Params ");
    }
    else
    {
        RealmsConfig Realms;
        RealmConfig *Realm = Realms.add_realms();
        Realm->set_realmname(RealmName);
        Realms.set_operreqid(DEL_REALM);

        CLOG_DEBUG("DeleteRealm: DEL_REALM Request : %s", RealmName.c_str());
        m_CMgrCallerObj->HandleDelRealmConfigReqs(Realms,
                new CMAPICookie(DEL_REALM, (void *) &Realms));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // return
    return retVal;
}

int CMAPIProdConfig::DeleteDestination(RealmsConfig& RealmInfo,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">DeletePeerFromRealm ");
    if (RealmInfo.realms_size() <= 0 )
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">DeletePeerFromRealm : Invalid Parameters");
    } else {
        RealmInfo.set_operreqid(DEL_DEST);

        m_CMgrCallerObj->HandleDelRealmConfigReqs(RealmInfo,
                new CMAPICookie(DEL_DEST, (void *) &RealmInfo));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    return retVal;
}

int CMAPIProdConfig::SetDestination(RealmsConfig& RealmInfo,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;

    m_SendSuccess = true;
    CLOG_DEBUG(">SetDestination ");
    if (!RealmInfo.IsInitialized())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG("SetDestination: Invalid Params ");
    }
    else
    {
        RealmInfo.set_operreqid(SET_DEST);

        m_CMgrCallerObj->HandleSetRealmConfigReqs(RealmInfo,
                new CMAPICookie(SET_DEST, (void *) &RealmInfo));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // return
    return retVal;
}

int CMAPIProdConfig::ModifyDestination(RealmsConfig& RealmInfo,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    CLOG_DEBUG(">ModifyDestination ");
    if (!RealmInfo.IsInitialized())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG("ModifyDestination: Invalid Params ");
    }
    else
    {
        RealmsConfig Realms;
        Realms.CopyFrom(RealmInfo);
        Realms.set_operreqid(MOD_DEST);

        m_CMgrCallerObj->HandleSetRealmConfigReqs(Realms,
                new CMAPICookie(MOD_DEST, (void *) &Realms));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    return retVal;
}

int CMAPIProdConfig::EnableProxyInfoAvp(string realmname,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    CLOG_DEBUG(">EnableProxyInfoAvp ");

    if (realmname.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG("EnableProxyInfoAvp: Invalid Params ");
    }
    else
    {
        RealmsConfig Realms;
        RealmConfig *Realm = Realms.add_realms();
        Realm->set_realmname(realmname);
        Realms.set_operreqid(ENBPXYIAVP);

        CLOG_DEBUG("EnableProxyInfoAvp: Enable Proxy Request");
        m_CMgrCallerObj->HandleSetRealmConfigReqs(Realms,
                new CMAPICookie(ENBPXYIAVP, (void *) &Realms));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // return
    return retVal;
}

int CMAPIProdConfig::DisableProxyInfoAvp(string realmname,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    CLOG_DEBUG(">DisableProxyInfoAvp ");

    if (realmname.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG("DisableProxyInfoAvp: Invalid Params ");
    }
    else
    {
        RealmsConfig Realms;
        RealmConfig *Realm = Realms.add_realms();
        Realm->set_realmname(realmname);
        Realms.set_operreqid(DISPXYIAVP);

        CLOG_DEBUG("DisableProxyInfoAvp: Disable Proxy Request");
        m_CMgrCallerObj->HandleSetRealmConfigReqs(Realms,
                new CMAPICookie(DISPXYIAVP, (void *) &Realms));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // return
    return retVal;
}

// ************************************************************************
// Peer Operations

int CMAPIProdConfig::GetAllPeersofRealm(string realmname, PeersConfig& Peers,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    CLOG_DEBUG(">GetAllPeersOfRealm ");

    if (realmname.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG("GetAllPeersofRealm: Invalid Params ");
    }
    else
    {
        PeersConfig lPeers;
        PeerConfig  *peer = lPeers.add_peers();
        peer->set_realm(realmname);
        lPeers.set_operreqid(GET_PEER);

        CLOG_DEBUG("GetAllPeersofRealm: GET PEER Request for : %s ", realmname.c_str());
        // Call CMGR Method Implementation
        // m_CMgrCallerObj->HandleGetPeerConfigReqs(lPeers,
        m_CMgrCallerObj->HandleGetPeerStatesReqs(lPeers,
                new CMAPICookie(GET_PEER, (void *) &lPeers));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        DRECfgResp Response;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            Response.ParseFromString(StrVal);
            retVal = Response.respcode();
            if (Response.has_peers())
            {
                /*
                   PeersConfig PCfg = Response.peers();
                   Peer.CopyFrom(PCfg.peers(0));
                   */
                Peers.CopyFrom(Response.peers());
            }
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
        else
        {
            Response.set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response.add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return
    return retVal;
}

int CMAPIProdConfig::GetPeerConfig(string peername, string realmname, PeerConfig& Peer,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    CLOG_DEBUG(">GetPeerConfig ");

    if (peername.empty() || realmname.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG("GetPeerConfig: Invalid Params ");
    }
    else
    {
        PeersConfig Peers;
        PeerConfig  *peer = Peers.add_peers();
        peer->set_peerhostname(peername);
        peer->set_realm(realmname);
        Peers.set_operreqid(GET_PEER);

        CLOG_DEBUG("GetPeerConfig: GET PEER Request for : %s - %s ", peername.c_str(), realmname.c_str());
        // Call CMGR Method Implementation
        // m_CMgrCallerObj->HandleGetPeerConfigReqs(Peers,
        m_CMgrCallerObj->HandleGetPeerStatesReqs(Peers,
                new CMAPICookie(GET_PEER, (void *) &Peers));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        DRECfgResp Response;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            DRECfgResp Response;
            Response.ParseFromString(StrVal);
            retVal = Response.respcode();
            if (Response.has_peers())
            {
                PeersConfig PCfg = Response.peers();
                if(PCfg.peers_size() > 0)
                    Peer.CopyFrom(PCfg.peers(0));
            }
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
        else
        {
            Response.set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response.add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
            retVal = CMAPI_TIMEOUT;
        }
    }
    // Return
    return retVal;
}

int CMAPIProdConfig::GetAllPeers(PeersConfig& peers,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    CLOG_DEBUG(">GetAllPeers : ");
    PeersConfig Peers;
    Peers.set_operreqid(GET_PEER);

    // Call CMGR Method Implementation
    // m_CMgrCallerObj->HandleGetPeerConfigReqs(Peers,
    m_CMgrCallerObj->HandleGetPeerStatesReqs(Peers,
            new CMAPICookie(GET_PEER, (void *) &Peers));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    DRECfgResp Response;
    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        Response.ParseFromString(StrVal);
        retVal = Response.respcode();
        if (Response.has_peers())
        {
            peers.CopyFrom(Response.peers());
        }
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }
    else
    {
        Response.set_respcode(CMAPI_TIMEOUT);
        // Fill in errordetails in Response
        ErrorDetails *err = Response.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }
    // Return
    return retVal;
}

int CMAPIProdConfig::SetPeerConfig(PeersConfig& PeerInfo,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    CLOG_DEBUG(">SetPeerConfig ");

    if (!PeerInfo.IsInitialized())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">SetPeerConfig Invalid Params");
    }
    else
    {

        PeerInfo.set_operreqid(SET_PEER);
        CLOG_DEBUG(">SetPeerConfig SET PEER Request");
        // Call CMGR Method Implementation
        CMAPICookie *lCookie = new CMAPICookie(SET_PEER, (void *) &PeerInfo);
        if (lCookie != NULL)
        {
            m_CMgrCallerObj->HandleSetPeerConfigReqs(PeerInfo, lCookie);
            std::string StrVal;
            if(m_SendSuccess == false)
            {
                retVal = CMAPI_MESSERROR;
                ErrorDetails* err = Response->add_errordetails();
                err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
                err->set_errormsgkey("config.common.mess.not.ready");
                m_SendSuccess = true;
                return retVal;
            }
            if(m_CMAPIResponse->Get(StrVal,m_waitTime))
            {
                //DRECfgResp Response;
                Response->ParseFromString(StrVal);
                retVal = Response->respcode();
            }
            else
            {
                Response->set_respcode(CMAPI_TIMEOUT);
                // Fill in errordetails in Response
                ErrorDetails *err = Response->add_errordetails();
                err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
                err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
            }
        } else {
            CLOG_DEBUG(">SetPeerConfig SET PEER Request: Error");
            retVal = CMAPI_ERROR;
        }
    }

    // return
    return retVal;
}

int CMAPIProdConfig::ModifyPeerConfig(PeersConfig& PeerInfo,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">ModifyPeerConfig ");

    if (!PeerInfo.IsInitialized())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">ModifyPeerConfig Invalid Params");
    }
    else
    {
        PeerInfo.set_operreqid(MOD_PEER);
        CLOG_DEBUG(">ModifyPeerConfig SET PEER Request");
        // Call CMGR Method Implementation
        m_CMgrCallerObj->HandleSetPeerConfigReqs(PeerInfo,
                new CMAPICookie(MOD_PEER, (void *) &PeerInfo));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // return
    return retVal;
}

int CMAPIProdConfig::AddDictionaryID(PeersConfig& PeerInfo,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">AddDictionaryID");

    if (!PeerInfo.IsInitialized() ||
            PeerInfo.peers_size() <= 0 )
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::AddDictionaryID Invalid Params");
    }
    else
    {
        PeerInfo.set_operreqid(ADD_DICTID);
        CLOG_DEBUG(">AddDictionaryID:  SET PEER Request");
        // Call CMGR Method Implementation
        m_CMgrCallerObj->HandleSetPeerConfigReqs(PeerInfo,
                new CMAPICookie(ADD_DICTID, (void *) &PeerInfo));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    return retVal;
}

int CMAPIProdConfig::DeleteDictionaryID(PeersConfig& PeerInfo,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">DeleteDictionaryID ");

    if (!PeerInfo.IsInitialized() ||
            PeerInfo.peers_size() <= 0 )
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">DeleteDictionaryID Invalid Params");
    }
    else
    {
        PeerInfo.set_operreqid(DEL_DICTID);
        CLOG_DEBUG(">AddDictionaryID:  SET PEER Request");
        // Call CMGR Method Implementation
        m_CMgrCallerObj->HandleDelPeerConfigReqs(PeerInfo,
                new CMAPICookie(DEL_DICTID, (void *) &PeerInfo));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    return retVal;
}

int CMAPIProdConfig::SetPeerStatus(PeersConfig& PeerInfo,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">SetPeerStatus ");

    if (!PeerInfo.IsInitialized() ||
            PeerInfo.peers_size() <= 0 )
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">SetPeerStatus: Invalid Params");
    }
    else
    {
        PeerInfo.set_operreqid(SET_PEERSTATUS);
        CLOG_DEBUG(">SetPeerStatus:  SET PEER Request");
        // Call CMGR Method Implementation
        m_CMgrCallerObj->HandleSetPeerConfigReqs(PeerInfo,
                new CMAPICookie(SET_PEERSTATUS, (void *) &PeerInfo));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    return retVal;
}

int CMAPIProdConfig::RemovePeerConfig(string peername, string realmname,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">RemovePeerConfig ");

    if (peername.empty() || realmname.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">RemovePeerConfig Invalid Params ");
    }
    else
    {
        PeersConfig Peers;
        PeerConfig  *Peer = Peers.add_peers();
        Peer->set_peerhostname(peername);
        Peer->set_realm(realmname);
        Peers.set_operreqid(DEL_PEER);

        // Call CMGR Method Implementation
        m_CMgrCallerObj->HandleDelPeerConfigReqs(Peers,
                new CMAPICookie(DEL_PEER, (void *) &Peers));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // return
    return retVal;
}

int CMAPIProdConfig::RemoveAlternatePeer(string peername, string realmname,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">Delete Alternate Peer ");

    if (peername.empty() || realmname.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">Delete Alternate Peer Invalid Params ");
    }
    else
    {
        PeersConfig Peers;
        PeerConfig  *Peer = Peers.add_peers();
        Peer->set_peerhostname(peername);
        Peer->set_realm(realmname);
        Peers.set_operreqid(DEL_ALTPEER);

        // Call CMGR Method Implementation
        m_CMgrCallerObj->HandleDelPeerConfigReqs(Peers,
                new CMAPICookie(DEL_ALTPEER, (void *) &Peers));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    return retVal;
}


int CMAPIProdConfig::RemovePeerTemplate(string peername, string realmname, DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">Delete Peer Template");

    if (peername.empty() || realmname.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">Delete Peer Template Invalid Params ");
    }
    else
    {
        PeersConfig Peers;
        PeerConfig  *Peer = Peers.add_peers();
        Peer->set_peerhostname(peername);
        Peer->set_realm(realmname);
        Peers.set_operreqid(DISASSOCIATE_PEER_TEMPLATE);

        // Call CMGR Method Implementation

        CLOG_DEBUG(">Call to: HandleSetPeerConfigReqs");
        m_CMgrCallerObj->HandleSetPeerConfigReqs(Peers,
                new CMAPICookie(DISASSOCIATE_PEER_TEMPLATE, (void *) &Peers));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    return retVal;
}

int CMAPIProdConfig::DeleteDefaultRoute(DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    RealmsConfig Realms;
    Realms.set_operreqid(DEL_DEFROUTE);
    CLOG_DEBUG(">DeleteDefaultRoute ");
    m_CMgrCallerObj->HandleDelRealmConfigReqs(Realms,
            new CMAPICookie(DEL_DEFROUTE, (void *) &Realms));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //DRECfgResp Response;
        Response->ParseFromString(StrVal);
        retVal = Response->respcode();
    }
    else
    {
        Response->set_respcode(CMAPI_TIMEOUT);
        // Fill in errordetails in Response
        ErrorDetails *err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }
    return retVal;
}

int CMAPIProdConfig::SetDefaultRoute(string peername, string RealmName,DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    CLOG_DEBUG(">SetDefaultRoute ");

    if (RealmName.empty() || peername.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG("SetDefaultRoute: Invalid Params ");
    }
    else
    {
        RealmsConfig Realms;
        RealmConfig *Realm = Realms.add_realms();
        Realm->set_realmname(RealmName);
        Realm->set_defaultroute(peername);
        Realms.set_operreqid(SET_DEFROUTE);

        CLOG_DEBUG("SetDefaultRoute: Request");
        m_CMgrCallerObj->HandleSetRealmConfigReqs(*&Realms,
                new CMAPICookie(SET_DEFROUTE, (void *) &Realms));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respcode();
        }
        else
        {
            Response->set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // return
    return retVal;
}

int CMAPIProdConfig::GetDefaultRoute(RealmConfig& DefRoute,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">GetDefaultRoute ");

    RealmsConfig Realms;
    Realms.set_operreqid(GET_DEFROUTE);

    CLOG_DEBUG(">GetDefaultRoute GET DEFROUTE Requesst ");
    // Call Dre Method Implementation
    m_CMgrCallerObj->HandleGetRealmConfigReqs(Realms,
            new CMAPICookie(GET_DEFROUTE, (void *) &Realms));
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
    DRECfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respcode();

    if (Response.has_realms())
    {
        RealmsConfig RealmsR = Response.realms();
        DefRoute.CopyFrom(RealmsR.realms(0));
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }
    // return
    return  retVal;
}

// DTF : dictionary provisioning and Transformation-plugin
int CMAPIProdConfig::SetDictionaryStatus(DictionaryConfigReq& dictionaryInfo, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    if (!dictionaryInfo.IsInitialized() ||
            dictionaryInfo.dictionaryinfo_size() <= 0 )
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::SetDictionaryStatus Invalid Params");
    }
    else
    {
        dictionaryInfo.set_operreqid(SET_DICT_STATUS);
        CLOG_DEBUG(">SetDictionaryStatus:  SET_DICT_STATUS Request");
        // Call CMGR Method Implementation
        m_CMgrCallerObj->HandleSetDictionaryConfigReq(dictionaryInfo,
                new CMAPICookie(SET_DICT_STATUS, (void *) &dictionaryInfo));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        DRECfgResp Response;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response.ParseFromString(StrVal);
            retVal = Response.respcode();
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Response.set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err.set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err.set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::SetTransformPluginStatus(TransformPluginConfigReq& transformPluginInfo, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    if (!transformPluginInfo.IsInitialized() ||
            transformPluginInfo.transformplugininfo_size() <= 0 )
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::SetTransformPluginStatus Invalid Params");
    }
    else
    {
        transformPluginInfo.set_operreqid(SET_TRANSPLUGIN_STATUS);
        CLOG_DEBUG(">SetTransformPluginStatus:  SET_TRANSPLUGIN_STATUS Request");
        // Call CMGR Method Implementation
        m_CMgrCallerObj->HandleSetPluginConfigReq(transformPluginInfo,
                new CMAPICookie(SET_TRANSPLUGIN_STATUS, (void *) &transformPluginInfo));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        DRECfgResp Response;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response.ParseFromString(StrVal);
            retVal = Response.respcode();
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Response.set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err.set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err.set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::ReloadSDTFPluginConfig(ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    TransformPluginConfigReq transformPluginInfo;

    transformPluginInfo.set_operreqid(RELOAD_SDTF);
    CLOG_DEBUG(">ReloadTransformPluginConfig:  RELOAD_SDTF Request");
    // Call CMGR Method Implementation
    m_CMgrCallerObj->HandleSetPluginConfigReq(transformPluginInfo,
            new CMAPICookie(RELOAD_SDTF, (void *) &transformPluginInfo));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    DRECfgResp Response;
    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //DRECfgResp Response;
        Response.ParseFromString(StrVal);
        retVal = Response.respcode();
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }
    else
    {
        retVal = CMAPI_TIMEOUT;
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        Response.set_respcode(CMAPI_TIMEOUT);
        // Fill in errordetails in Response
        err.set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err.set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::ReloadTransformPluginConfig(TransformPluginConfigReq& transformPluginInfo, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    if (!transformPluginInfo.IsInitialized() ||
            transformPluginInfo.transformplugininfo_size() <= 0 )
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::ReloadTransformPluginConfig Invalid Params");
    }
    else
    {
        transformPluginInfo.set_operreqid(RELOAD_TRANSPLUGIN);
        CLOG_DEBUG(">ReloadTransformPluginConfig:  RELOAD_TRANSPLUGIN Request");
        // Call CMGR Method Implementation
        m_CMgrCallerObj->HandleSetPluginConfigReq(transformPluginInfo,
                new CMAPICookie(RELOAD_TRANSPLUGIN, (void *) &transformPluginInfo));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        DRECfgResp Response;
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //DRECfgResp Response;
            Response.ParseFromString(StrVal);
            retVal = Response.respcode();
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Response.set_respcode(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err.set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err.set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::GetTransformPlugin(DRECfgResp *Resp)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG(" > %s ",__FUNCTION__);
    TransformPluginConfigReq TransformPluginConfig;
    TransformPluginConfig.set_operreqid(GET_TRANSPLUGIN);
    m_SendSuccess = true;

    // Call CMGR Method Implementation
    // m_CMgrCallerObj->HandleGetPeerConfigReqs(PeerInfo,
    m_CMgrCallerObj->HandleGetPluginConfigReq(TransformPluginConfig,
            new CMAPICookie(GET_TRANSPLUGIN, (void *) &TransformPluginConfig));
    std::string StrVal;
    //DRECfgResp Response;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        Resp->set_respcode(retVal);
        ErrorDetails* err = Resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //DRECfgResp Response;
        Resp->Clear();
        Resp->ParseFromString(StrVal);
        CLOG_DEBUG(" Resp: %s ",StrVal.c_str());
        CLOG_DEBUG(" Resp: %s ",Resp->DebugString().c_str());
        retVal = Resp->respcode();
    }
    else
    {
        Resp->set_respcode(CMAPI_TIMEOUT);
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        // Fill in errordetails in Response
        ErrorDetails *err = Resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::GetDictionaryConfiguration(DRECfgResp *Resp)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG(" > %s ",__FUNCTION__);
    DictionaryConfigReq DictionaryConfig;
    DictionaryConfig.set_operreqid(GET_DICTIONARIES);
    m_SendSuccess = true;

    // Call CMGR Method Implementation
    // m_CMgrCallerObj->HandleGetPeerConfigReqs(PeerInfo,
    m_CMgrCallerObj->HandleGetDictionaryConfigReq(DictionaryConfig,
            new CMAPICookie(GET_DICTIONARIES, (void *) &DictionaryConfig));
    std::string StrVal;
    //DRECfgResp Response;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        Resp->set_respcode(retVal);
        ErrorDetails* err = Resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //DRECfgResp Response;
        Resp->Clear();
        Resp->ParseFromString(StrVal);
        retVal = Resp->respcode();
    }
    else
    {
        Resp->set_respcode(CMAPI_TIMEOUT);
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        // Fill in errordetails in Response
        ErrorDetails *err = Resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}
// ***********************************************************************
// Config Manager Methods Response Handlers Implementation
// ***********************************************************************

int CMAPIProdConfig::HandleGetLocalHostConfigReqsRespCbk(DRECfgResp *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">HandleGetLocalHostConfigReqsRespCbk ");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("HandleGetLocalHostConfigReqs message failed. Error: ");
        if (resp == NULL )
        {
            DRECfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respcode(retVal);
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
    delete lCookie;
    return retVal;
}


int CMAPIProdConfig::HandleSetLocalHostConfigReqsRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetLocalHostConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("HandleSetLocalHostConfigReqs message failed. Error: ");
        if (resp == NULL )
        {
            DRECfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respcode(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

int CMAPIProdConfig::HandleGetPeerConfigReqsRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleGetPeerConfigReqsRespCbk ");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("HandleGetPeerConfigReqs message failed. Error: ");
        if (resp == NULL )
        {
            DRECfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respcode(retVal);
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
    delete lCookie;
    return retVal;
}

int CMAPIProdConfig::HandleSetPeerConfigReqsRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetPeerConfigReqsRespCbk ");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("HandleSetPeerConfigReqs message failed. Error: ");
        if (resp == NULL )
        {
            DRECfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respcode(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

int CMAPIProdConfig::HandleDelPeerConfigReqsRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleDelPeerConfigReqsRespCbk : ");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( lCookie != NULL)
        CLOG_DEBUG(">HandleDelPeerConfigReqsRespCbk : %u", lCookie);

    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("HandleGetLocalHostConfigReqs message failed. Error: ");
        if (resp == NULL )
        {
            DRECfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respcode(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    CLOG_DEBUG(">HandleDelPeerConfigReqsRespCbk : %u", lCookie);
    delete lCookie;
    return retVal;
}

int CMAPIProdConfig::HandleGetRealmConfigReqsRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleGetRealmConfigReqsRespCbk : ");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("HandleGetRealmConfigReqs message failed. Error: ");
        if (resp == NULL )
        {
            DRECfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respcode(retVal);
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
    delete lCookie;
    return retVal;
}

int CMAPIProdConfig::HandleSetRealmConfigReqsRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetRealmConfigReqsRespCbk : ");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("HandleSetRealmConfigReqs message failed. Error: ");
        if (resp == NULL )
        {
            DRECfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respcode(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

int CMAPIProdConfig::HandleDelRealmConfigReqsRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleDelRealmConfigReqsRespCbk : ");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("HandleDelRealmConfigReqs message failed. Error: ");
        if (resp == NULL )
        {
            DRECfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respcode(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

// ***********************************************************************
// DRE Product Statistics Response Handlers Implementation
// ***********************************************************************


int CMAPIProdConfig::GetPeerGeneralStats(PeerGeneralStatsReq& req, PeerGeneralStatsResp& resp)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG("CMAPIProdConfig::GetPeerGeneralStats");
    req.set_requestid(GET_PEERGENERALSTATS);

    retVal = SendPeerStatsRequest(req,&resp);
    return retVal;
}

int CMAPIProdConfig::SendPeerStatsRequest(PeerGeneralStatsReq& req, PeerGeneralStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;

    CLOG_DEBUG("Sending GetPeerGeneralStats Request ");

    m_PeerStatsObj->FetchPeerGeneralStats(req,
            new CMAPICookie(req.requestid(), (void *) &req));
    CLOG_DEBUG("SendPeerStatsRequest:GetPeerGeneralStats: Waiting for Response");
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails *err = resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("SendPeerStatsRequest:GetPeerGeneralStats: Response Received");
    if(strVal.empty())
    {
        return CMAPI_SRVERROR;
    }

    resp->ParseFromString(strVal);
    if (resp->has_responseid())
    {
        retVal = resp->responseid();
    }
    return retVal;
}

int CMAPIProdConfig::GetPeerTransportStats(PeerTransportStatsReq& req, PeerTransportStatsResp &resp)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG("CMAPIProdConfig::GetPeerTransportStats");
    req.set_requestid(GET_PEERTRANSPORTSTATS);

    retVal = SendPeerStatsRequest(req,&resp);
    return retVal;
}

int CMAPIProdConfig::SendPeerStatsRequest(PeerTransportStatsReq& req, PeerTransportStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;

    CLOG_DEBUG("Sending GetPeerTransportStats Request");

    m_PeerStatsObj->FetchPeerTransportStats(req,
            new CMAPICookie(req.requestid(), (void *) &req));
    CLOG_DEBUG("SendPeerStatsRequest:GetPeerTransportStats: Waiting for Response");
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails *err = resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("SendPeerStatsRequest:GetPeerTranspoertStats: Response Received");
    if(strVal.empty())
    {
        return CMAPI_SRVERROR;
    }

    resp->ParseFromString(strVal);
    if (resp->has_responseid())
    {
        retVal = resp->responseid();
    }
    return retVal;
}

int CMAPIProdConfig::GetPeerDREProtocolErrorStats(PeerDREProtocolErrorStatsReq& req, PeerDREProtocolErrorStatsResp &resp)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG("CMAPIProdConfig::GetPeerDREProtocolErrorStats");

    req.set_requestid(GET_PEERERRORSTATS);

    retVal = SendPeerStatsRequest(req,&resp);
    return retVal;
}


int CMAPIProdConfig::SendPeerStatsRequest(PeerDREProtocolErrorStatsReq& req, PeerDREProtocolErrorStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;

    CLOG_DEBUG("Sending GetPeerDREProcotolStats Request");

    m_PeerStatsObj->FetchPeerDREProtocolErrorStats(req,
            new CMAPICookie(req.requestid(), (void *) &req));
    CLOG_DEBUG("SendPeerStatsRequest:GetPeerDREProtocolErrorStats: Waiting for Response");
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails *err = resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("SendPeerStatsRequest:GetPeerDREProtocolErrorStats: Response Received");
    if(strVal.empty())
    {
        return CMAPI_SRVERROR;
    }

    resp->ParseFromString(strVal);
    if (resp->has_responseid())
    {
        retVal = resp->responseid();
    }
    return retVal;
}

int CMAPIProdConfig::ResetAllPeerStats(ResetPeerStatsReq& req, ResetPeerStatsResp& resp)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG("CMAPIProdConfig::ResetAllPeerStats");

    req.set_requestid(RESET_PEERSTATS);

    retVal = SendPeerStatsRequest(req,&resp);
    return retVal;
}

int CMAPIProdConfig::SendPeerStatsRequest(ResetPeerStatsReq& req, ResetPeerStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;

    CLOG_DEBUG("Sending ResetPeerStats Request ");

    m_PeerStatsObj->ResetPeerStats(req,
            new CMAPICookie(req.requestid(), (void *) &req));
    CLOG_DEBUG("SendPeerStatsRequest:ResetAllPeerStats: Waiting for Response");
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails *err = resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("SendPeerStatsRequest:ResetAllPeerStats: Response Received");
    if(strVal.empty())
    {
        return CMAPI_SRVERROR;
    }

    resp->ParseFromString(strVal);
    if (resp->has_responseid())
    {
        retVal = resp->responseid();
    }
    return retVal;
}


int CMAPIProdConfig::FetchPeerGeneralStatsRespCbk(PeerGeneralStatsResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("FetchPeerGeneralStatsRespCbk");
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }

    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
    {
        if (Resp->responseid() == CMAPI_SUCCESS)
        {
            CLOG_DEBUG("FetchPeerGeneralStats: DRE operation - Successful");
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            CLOG_ERROR("FetchPeerGeneralStats : DRE operation - Failed");
            Resp->SerializeToString(&StrVal);
            retVal = CMAPI_SRVERROR;
        }
    }
    else
    {
        if( Resp == NULL )
        {
            CLOG_DEBUG("FetchPeerGeneralStats : MeSS - Failed");
            PeerGeneralStatsResp errorResponse;
            retVal = CMAPI_SRVERROR;
            errorResponse.set_responseid(retVal);
            errorResponse.SerializeToString(&StrVal);
        }
        else
        {
            Resp->SerializeToString(&StrVal);
        }
    }

    m_CMAPIResponse->Set(StrVal);

    CLOG_DEBUG("FetchPeerGeneralStats: Deleting Local Cookie");
    delete lCookie;

    return retVal;
}

int CMAPIProdConfig::FetchPeerTransportStatsRespCbk(PeerTransportStatsResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("FetchPeerTranportStatsRespCbk");
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }

    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
    {
        if (Resp->responseid() == CMAPI_SUCCESS)
        {
            CLOG_DEBUG("FetchPeerTransportStats: DRE operation - Successful");
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            CLOG_ERROR("FetchPeerTransportStats : DRE operation - Failed");
            Resp->SerializeToString(&StrVal);
            retVal = CMAPI_SRVERROR;
        }
    }
    else
    {
        if( Resp == NULL )
        {
            CLOG_DEBUG("FetchPeerTransportStats : MeSS - Failed");
            PeerTransportStatsResp errorResponse;
            retVal = CMAPI_SRVERROR;
            errorResponse.set_responseid(retVal);
            errorResponse.SerializeToString(&StrVal);
        }
        else
        {
            Resp->SerializeToString(&StrVal);
        }
    }

    m_CMAPIResponse->Set(StrVal);

    CLOG_DEBUG("FetchPeerTransportStats: Deleting Local Cookie");
    delete lCookie;

    return retVal;
}

int CMAPIProdConfig::FetchPeerDREProtocolErrorStatsRespCbk(PeerDREProtocolErrorStatsResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("FetchPeerDREProtocolErrorStatsRespCbk");
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }

    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
    {
        if (Resp->responseid() == CMAPI_SUCCESS)
        {
            CLOG_DEBUG("FetchPeerTransportStats: DRE operation - Successful");
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            CLOG_ERROR("FetchPeerDREProtocolErrorStats : DRE operation - Failed");
            Resp->SerializeToString(&StrVal);
            retVal = CMAPI_SRVERROR;
        }
    }
    else
    {
        if( Resp == NULL )
        {
            CLOG_DEBUG("FetchPeerDREProcotolErrorStats : MeSS - Failed");
            PeerDREProtocolErrorStatsResp errorResponse;
            retVal = CMAPI_SRVERROR;
            errorResponse.set_responseid(retVal);
            errorResponse.SerializeToString(&StrVal);
        }
        else
        {
            Resp->SerializeToString(&StrVal);
        }
    }

    m_CMAPIResponse->Set(StrVal);

    CLOG_DEBUG("FetchPeerDREProtocolErrorStats: Deleting Local Cookie");
    delete lCookie;
    return retVal;
}

int CMAPIProdConfig::ResetPeerStatsRespCbk(ResetPeerStatsResp *Resp)
{

    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("ResetPeerStatsRespCbk");
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }

    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
    {
        if (Resp->responseid() == CMAPI_SUCCESS)
        {
            CLOG_DEBUG("ResetPeerStatsRespCbk: DRE operation - Successful");
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            CLOG_ERROR("ResetPeerStatsRespCbk : DRE operation - Failed");
            Resp->SerializeToString(&StrVal);
            retVal = CMAPI_SRVERROR;
        }
    }
    else
    {
        if( Resp == NULL )
        {
            CLOG_DEBUG("ResetPeerStatsRespCbk : MeSS - Failed");
            ResetPeerStatsResp errorResponse;
            retVal = CMAPI_SRVERROR;
            errorResponse.set_responseid(retVal);
            errorResponse.SerializeToString(&StrVal);
        }
        else
        {
            Resp->SerializeToString(&StrVal);
        }
    }

    m_CMAPIResponse->Set(StrVal);

    CLOG_DEBUG("ResetPeerStatsRespCbk: Deleting Local Cookie");
    delete lCookie;

    return retVal;
}

// Results Implementation
int CMAPIProdConfig::SendDreTemplateConfigResult(TemplateResp *Req,CMAPIRes *Resp)
{
    CLOG_DEBUG("DREConfig ReportResult");
    string StrVal;
    if (Req != NULL)
    {
        Req->SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);
    Resp->set_responsecode(CMAPI_SUCCESS);
    return 0;
}

// Results Implementation
int CMAPIProdConfig::SendTHFConfigResult(THFResp *Req,CMAPIRes *Resp)
{
    CLOG_DEBUG("DREConfig ReportResult");
    string StrVal;
    if (Req != NULL)
    {
        Req->SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);
    Resp->set_responsecode(CMAPI_SUCCESS);
    return 0;
}

// Results Implementation
int CMAPIProdConfig::SendDREConfigResult(DRECfgResp *Req,CMAPIRes *Resp)
{
    CLOG_DEBUG("DREConfig ReportResult");
    string StrVal;
    if (Req != NULL)
    {
        Req->SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);
    Resp->set_responsecode(CMAPI_SUCCESS);
    return 0;
}

int CMAPIProdConfig::AddUser(Users& UserList,UserResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    UserReq Req;
    m_SendSuccess = true;
    //UserResp Resp;
    string StrVal;
    int numOfUser;

    CLOG_DEBUG("CMAPIProdConfig::AddUser");

    Req.set_requestid(SET_USER);
    numOfUser = UserList.userdata_size();
    if(numOfUser > 0 )
    {
        Users *usersInfo = Req.mutable_user();
        usersInfo->CopyFrom(UserList);

        m_CMgrCallerObj->SetUserConfig(Req,
                new CMAPICookie(Req.requestid(), (void *) &Req));
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails *err = Resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        CLOG_DEBUG("AddUser::Waiting for Response");

        m_CMAPIResponse->Get(StrVal);
        CLOG_DEBUG("AddUser::Response received");
        if(StrVal.empty())
        {
            retVal = CMAPI_ERROR;
        }
        else
        {
            Resp->ParseFromString(StrVal);
            if(Resp->responseid() == CMAPI_SUCCESS)
            {
                retVal = Resp->responseid();
                CLOG_DEBUG("AddUser::Successfully added user");
            }
            else
            {
                retVal = CMAPI_SRVERROR;
                CLOG_DEBUG("AddUser::Failed to add user");
            }
        }
    }
    else
    {
        DLOG_ERROR("AddUser::No UserName or Password");
        retVal = CMAPI_INVALIDPARAMS;
    }
    return retVal;
}

int CMAPIProdConfig::SetUserConfigRespCbk(UserResp *Resp)
{
    CLOG_DEBUG("SetUserRespCbk");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        std::string StrVal;
        Resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}

int CMAPIProdConfig::IsResponseOK(UserResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("CMAPIProdConfig: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL
            || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        UserResp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);

        if ( Resp!=NULL && Resp->has_responseid() )
        {
            retVal = Resp->responseid();
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            retVal = CMAPI_MESSERROR;
            ErrResp.SerializeToString(&StrVal);
        }

        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}

int CMAPIProdConfig::GetUser(string& UserName, Users& UserList,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    UserReq Req;
    UserResp Resp;
    string StrVal;

    CLOG_DEBUG("CMAPIProdConfig::GetUSer");

    Req.set_requestid(GET_USER);
    if(!(UserName.empty()))
    {
        Users *user;
        UserInfo *userInfo;
        user = Req.mutable_user();
        userInfo = user->add_userdata();
        userInfo->set_username(UserName);
    }

    m_CMgrCallerObj->GetUserConfig(Req,
            new CMAPICookie(Req.requestid(), (void *) &Req));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    CLOG_DEBUG("GetUser::Waiting for Response");

    m_CMAPIResponse->Get(StrVal);
    CLOG_DEBUG("GetUser::Response received");
    if(StrVal.empty())
    {
        retVal = CMAPI_ERROR;
    }
    else
    {
        Resp.ParseFromString(StrVal);

        if(Resp.responseid() == CMAPI_SUCCESS)
        {
            retVal = Resp.responseid();
            CLOG_DEBUG("GetUser:Successfully reterived Userdata");
            if(Resp.has_user())
            {
                UserList.CopyFrom(Resp.user());
            }
            else
            {
                CLOG_ERROR("GetUser:Failed to get Userdata");
                if(Resp.errordetails_size())
                {
                    err.CopyFrom(Resp.errordetails(0));
                }
            }

        }
        else
        {
            retVal = CMAPI_SRVERROR;
            if(Resp.errordetails_size())
            {
                err.CopyFrom(Resp.errordetails(0));
            }
            CLOG_ERROR("GetUser: Server Error");
        }
    }
    return retVal;

}

int CMAPIProdConfig::GetUserConfigRespCbk(UserResp *Resp)
{
    CLOG_DEBUG("GetUserRespCbk");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        std::string StrVal;
        Resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}

int CMAPIProdConfig::DeleteUser(Users& UserList,UserResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    UserReq Req;
    //UserResp Resp;
    string StrVal;
    Users *user = NULL;
    m_SendSuccess = true;

    CLOG_DEBUG("CMAPIProdConfig::DeleteUser");
    Req.set_requestid(DEL_USER);
    if((UserList.userdata_size()) > 0)
    {
        user = Req.mutable_user();
        user->CopyFrom(UserList);

        m_CMgrCallerObj->SetUserConfig(Req,
                new CMAPICookie(Req.requestid(), (void *) &Req));
        CLOG_DEBUG("DeleteUser::Waiting for Response");

        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        m_CMAPIResponse->Get(StrVal);
        CLOG_DEBUG("DeleteUser::Response received");
        if(StrVal.empty())
        {
            retVal = CMAPI_ERROR;
        }
        else
        {
            Resp->ParseFromString(StrVal);

            if(Resp->responseid() == CMAPI_SUCCESS)
            {
                retVal = Resp->responseid();
                CLOG_DEBUG("DeleteUser:Successfully reset password");
            }
            else
            {
                retVal = CMAPI_SRVERROR;
                CLOG_ERROR("DeleteUser: Server Error");
            }
        }
    }
    else
    {
        CLOG_ERROR("DeleteUser: Invalid parameters");
        retVal = CMAPI_INVALIDPARAMS;
    }
    return retVal;
}

int CMAPIProdConfig::ChangePassword(string& UserName, char *password, size_t length,UserResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    UserReq Req;
    //UserResp Resp;
    string StrVal;
    m_SendSuccess = true;

    CLOG_DEBUG("CMAPIProdConfig::ChangePassword");

    Req.set_requestid(MOD_USER);
    if(!(UserName.empty()))
    {
        Users *user;
        UserInfo *userInfo;
        user = Req.mutable_user();
        userInfo = user->add_userdata();
        userInfo->set_username(UserName);
        userInfo->set_password((void*)password,length);

        m_CMgrCallerObj->SetUserConfig(Req,
                new CMAPICookie(Req.requestid(), (void *) &Req));
        CLOG_DEBUG("ChangePassword::Waiting for Response");
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails* err = Resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        m_CMAPIResponse->Get(StrVal);
        CLOG_DEBUG("ChangePassword::Response received");
        if(StrVal.empty())
        {
            retVal = CMAPI_ERROR;
        }
        else
        {
            Resp->ParseFromString(StrVal);

            if(Resp->responseid() == CMAPI_SUCCESS)
            {
                retVal = Resp->responseid();
                CLOG_DEBUG("ChangePassword:Successfully reset password");
            }
            else
            {
                retVal = CMAPI_SRVERROR;
                CLOG_ERROR("ChangePassword: Server Error");
            }
        }
    }
    else
    {
        CLOG_ERROR("ChangePassword:No User or Password");
        retVal = CMAPI_INVALIDPARAMS;
    }
    return retVal;
}

int CMAPIProdConfig::GetPeersState(PeersConfig& PeerInfo)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG(">GetPeersState : ");
    PeerInfo.set_operreqid(GET_PEERSTATE);
    m_SendSuccess = true;

    // Call CMGR Method Implementation
    // m_CMgrCallerObj->HandleGetPeerConfigReqs(PeerInfo,
    m_CMgrCallerObj->HandleGetPeerStatesReqs(PeerInfo,
            new CMAPICookie(GET_PEERSTATE, (void *) &PeerInfo));
    std::string StrVal;
    DRECfgResp Response;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        Response.set_respcode(retVal);
        ErrorDetails* err = Response.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //DRECfgResp Response;
        Response.ParseFromString(StrVal);
        retVal = Response.respcode();
        if (Response.has_peers())
        {
            PeerInfo.CopyFrom(Response.peers());
        }
    }
    else
    {
        Response.set_respcode(CMAPI_TIMEOUT);
        // Fill in errordetails in Response
        ErrorDetails *err = Response.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    return retVal;
}


int CMAPIProdConfig::AddTraceFilter(TraceReq& Request, TraceResp& Response)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG("CMAPIProdConfig: AddTraceFilter");

    Request.set_requestid(SET_TRACE);

    retVal = SendTraceRequest(Request, &Response);

    return retVal;
}

int CMAPIProdConfig::DeleteTraceFilter(TraceReq& Request, TraceResp& Response)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG("CMAPIProdConfig: DeleteTraceFilter");

    Request.set_requestid(DEL_TRACE);

    retVal = SendTraceRequest(Request, &Response);

    return retVal;
}

int CMAPIProdConfig::ModifyTraceFilter(TraceReq& Request, TraceResp& Response)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG("CMAPIProdConfig: ModifyTraceFilter");

    Request.set_requestid(MOD_TRACE);

    retVal = SendTraceRequest(Request, &Response);

    return retVal;
}

int CMAPIProdConfig::GetTraceFilter(TraceReq& Request, TraceResp& Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;

    CLOG_DEBUG("CMAPIProdConfig: GetTraceFilter");

    Request.set_requestid(GET_TRACE);

    CLOG_DEBUG("Sending tracing request ");

    m_CMgrCallerObj->HandleGetTraceConfigReqs(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("SendTraceRequest: Waiting for Response");

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("SendTraceRequest: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response.ParseFromString(strVal);
    if (Response.responseid() == CMAPI_SUCCESS)
    {
        retVal = Response.responseid();
        CLOG_DEBUG("GetTraceFilter: Successfully returned TraceFilters");
    }
    else
    {
        retVal = CMAPI_SRVERROR;
        CLOG_ERROR("GetTraceFilter: Failed to fetch TraceFilters");
    }

    return retVal;
}

int CMAPIProdConfig::EnableTracing(TraceReq& Request, TraceResp& Response)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG("CMAPIProdConfig: EnableTracing");

    Request.set_requestid(ENABLE_TRACE);

    retVal = SendTraceRequest(Request, &Response);

    return retVal;
}

int CMAPIProdConfig::SendTraceRequest(TraceReq& Request, TraceResp *Response)
{

    int retVal = CMAPI_SUCCESS;
    std::string strVal;

    CLOG_DEBUG("Sending tracing request ");

    m_CMgrCallerObj->HandleSetTraceConfigReqs(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("SendTraceRequest: Waiting for Response");

    if((m_CMAPIResponse->Get(strVal,m_waitTime)))
    {
        CLOG_DEBUG("SendTraceRequest: Response Received");
        if(strVal.empty())
        {
            return CMAPI_ERROR;
        }

        Response->ParseFromString(strVal);
        if (Response->has_responseid())
        {
            retVal = Response->responseid();
            CLOG_DEBUG("retVal : %d",Response->responseid());
        }
        else
        {
            retVal = CMAPI_SRVERROR;

        }
    }
    else
    {
        retVal = CMAPI_TIMEOUT;
        Response->set_responseid(retVal);
        ErrorDetails *err=Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    return retVal;
}

int CMAPIProdConfig::PollTraceFilter(TraceReq& Request, TraceResp& Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: PollTraceFilter");

    Request.set_requestid(GET_TRACE);

    m_TraceConfigObj->GetTraceConfigReqs(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("SendTraceRequest: Waiting for Response");

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("SendTraceRequest: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response.ParseFromString(strVal);
    if (Response.has_responseid())
    {
        retVal = Response.responseid();
        CLOG_DEBUG("retVal : %d",Response.responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::SetDefaultBehaviourAndTopologyHiding(THFReq Request,THFResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: SetDefaultBehaviourAndTopologyHiding");

    Request.set_requestid(SET_THF_ENABLE_DEF_BEHAV);

    m_CMgrCallerObj->SetTHFConfig(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("SendTHFConfig: Waiting for Response");

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("SendTHFConfig: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;
    }

    return retVal;
}

int CMAPIProdConfig::SetDefaultBehaviour(bool value,THFResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: SetDefaultBehaviour");
    THFReq Request;

    Request.set_requestid(SET_THF_DEF_BEHAV);
    Request.set_defaultexpose(value);

    m_CMgrCallerObj->SetTHFConfig(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("SendTHFConfig: Waiting for Response");

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("SendTHFConfig: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::GetThfvHost(THFReq& Request,THFResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: GetThfRealm");

    Request.set_requestid(GET_THF_VHOST);

    m_CMgrCallerObj->GetTHFConfig(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("GetThfvHost: Waiting for Response");

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("GetThfvHost: Response Received");

    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }


    Request.Clear();
    CLOG_DEBUG("GetThfvHost: %s",Request.DebugString().c_str());

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        for(int i=0;i<Response->vhosts_size();i++)
        {
            ::THFVHost *src_Vhost =  Response->mutable_vhosts(i);
            ::THFVHost *dest_Vhost =  Request.add_vhosts();
            dest_Vhost->CopyFrom(*src_Vhost);
        }


        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::GetThfRealm(THFReq& Request,THFResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: GetThfRealm");

    Request.set_requestid(GET_THF_REALM);

    m_CMgrCallerObj->GetTHFConfig(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("GetTHFConfig: Waiting for Response");

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("GetTHFConfig: Response Received");

    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Request.Clear();
    CLOG_DEBUG("GetThfRealm: %s",Request.DebugString().c_str());
    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        Request.set_defaultexpose(Response->defaultexpose());
        for(int i=0;i<Response->vhosts_size();i++)
        {
            ::THFVHost *src_Vhost =  Response->mutable_vhosts(i);
            ::THFVHost *dest_Vhost =  Request.add_vhosts();
            dest_Vhost->CopyFrom(*src_Vhost);
        }
        for(int i=0;i<Response->realms_size();i++)
        {
            ::THFRealm *src_Vhost =  Response->mutable_realms(i);
            ::THFRealm *dest_Vhost =  Request.add_realms();
            dest_Vhost->CopyFrom(*src_Vhost);
        }

        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::GetTopologyHiding(THFReq& Request,THFResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: GetTopologyHiding");

    Request.set_requestid(GET_THF_ENABLE);

    m_CMgrCallerObj->GetTHFConfig(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("GetTHFConfig: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("GetTHFConfig: Response Received");

    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        Request.set_enablethf(Response->enablethf());
        Request.set_defaultexpose(Response->defaultexpose());
        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d Request = %s",Response->responseid(),Request.DebugString().c_str());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::DelThfRealm(THFReq Request,THFResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: DelThfRealm");

    Request.set_requestid(DEL_THF_REALM);

    m_CMgrCallerObj->SetTHFConfig(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("SetTHFConfig: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("SetTHFConfig: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::DelThfVHost(THFReq Request,THFResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: DelThfVHost");

    Request.set_requestid(DEL_THF_VHOST);

    m_CMgrCallerObj->SetTHFConfig(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("DelThfVHost: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("DelThfVHost: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::AddThfVHost(THFReq Request,THFResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: AddThfVHost");

    Request.set_requestid(ADD_THF_VHOST);

    m_CMgrCallerObj->SetTHFConfig(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("AddThfVHost: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("AddThfVHost: Response Received");

    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::AddThfRealm(THFReq Request,THFResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: AddThfRealm");

    Request.set_requestid(ADD_THF_REALM);

    m_CMgrCallerObj->SetTHFConfig(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("SetTHFConfig: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("SetTHFConfig: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::SetTopologyHiding(bool value,THFResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: SetTopologyHiding");
    THFReq Request;

    Request.set_requestid(SET_THF_ENABLE);
    Request.set_enablethf(value);

    m_CMgrCallerObj->SetTHFConfig(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("SetTHFConfig: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("SetTHFConfig: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::SetTHFConfigRespCbk(THFResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">CMAPIProdConfig: SetTHFConfigRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("SetTHFConfigRespCbk message failed. Error: ");
        if (resp == NULL )
        {
            THFResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }


    delete lCookie;
    CLOG_DEBUG("<CMAPIProdConfig: SetTHFConfigRespCbk");
    return retVal;
}


int CMAPIProdConfig::GetTHFConfigRespCbk(THFResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">CMAPIProdConfig: GetTHFConfigRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        CLOG_DEBUG("CMAPIProdConfig: GetTHFConfigRespCbk");
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("GetTHFConfigRespCbk message failed. Error: ");
        if (resp == NULL )
        {
            THFResp ErrorResponse;
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
    delete lCookie;
    return 0;
}


int CMAPIProdConfig::IsResponseOK(TraceResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("CMAPIProdConfig: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL
            || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        TraceResp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);

        if ( Resp!=NULL && Resp->has_responseid() )
        {
            retVal = Resp->responseid();
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails *err = ErrResp.add_errordetails();
            err->set_errorcode(ERROR_TRACECONFIG_MAX_ERROR);
            ErrResp.SerializeToString(&StrVal);
        }

        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}

int CMAPIProdConfig::HandleGetTraceConfigReqsRespCbk(TraceResp *resp)
{
    CLOG_DEBUG("HandleGetTraceConfigRespCbk");
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    int retVal = IsResponseOK(resp);
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        std::string StrVal;
        resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}

int CMAPIProdConfig::HandleSetTraceConfigReqsRespCbk(TraceResp *resp)
{
    CLOG_DEBUG("HandleSetTraceConfigRespCbk");
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if(resp != NULL)
    {
        CLOG_DEBUG("HandleSetTraceConfigRespCbk:TraceResp->responseid : %d",resp->responseid());
    }
    int retVal = IsResponseOK(resp);

    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        delete lCookie;
    }
    return 0;
}

int CMAPIProdConfig::GetTraceConfigReqsRespCbk(TraceResp *resp)
{
    CLOG_DEBUG("GetTraceConfigRespCbk");
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if(resp != NULL)
    {
        CLOG_DEBUG("GetTraceConfigRespCbk:TraceResp->responseid : %d",resp->responseid());
    }
    int retVal = IsResponseOK(resp);

    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        std::string StrVal;
        resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return 0;
}

// Results Implementation
int CMAPIProdConfig::SendTraceConfigResult(TraceResp *Req,CMAPIRes *Resp)
{
    CLOG_DEBUG("Trace ReportResult");
    string StrVal;
    if (Req != NULL)
    {
        Req->SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);
    return 0;
}

int CMAPIProdConfig::SendStaticRoutingTableConfigResult(StaticRoutingTableConfigResp* Req, CMAPIRes* Resp)
{
    CLOG_DEBUG("Static routing ReportResult");
    string StrVal;
    if (Req != NULL)
    {
        Req->SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);
    return 0;
}


int CMAPIProdConfig::HandleGetPeerStatesReqsRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleGetPeerStatesReqsRespCbk ");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("HandleGetPeerConfigReqs message failed. Error: ");
        if (resp == NULL )
        {
            DRECfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respcode(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    /*else
      {
      resp->SerializeToString(&StrVal);
      }*/

    delete lCookie;
    return 0;
}

int CMAPIProdConfig::AddSecIPToPeer(PeersConfig& PeerInfo, DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;

    m_SendSuccess = true;
    CLOG_DEBUG(">AddSecPToPeer ");

    if (!PeerInfo.IsInitialized())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">AddSecPToPeer Invalid Params");
    }
    else
    {
        PeerInfo.set_operreqid(ADD_SECIP);
        CLOG_DEBUG(">AddSecPToPeer Add Secondary IP Request");
        // Call CMGR Method Implementation
        m_CMgrCallerObj->HandleSetPeerConfigReqs(PeerInfo);
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            Response->set_respcode(retVal);
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        std::string StrVal;
        m_CMAPIResponse->Get(StrVal);
        Response->ParseFromString(StrVal);
        retVal = Response->respcode();
    }
    return retVal;
}

int CMAPIProdConfig::DeleteSecIPFromPeer(PeersConfig& PeerInfo, DRECfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">DeleteSecIPFromPeer ");

    m_SendSuccess = true;
    if (!PeerInfo.IsInitialized())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">DeleteSecIPFromPeer Invalid Params ");
    }
    else
    {
        PeerInfo.set_operreqid(DEL_SECIP);
        // Call CMGR Method Implementation
        m_CMgrCallerObj->HandleDelPeerConfigReqs(PeerInfo);
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            Response->set_respcode(retVal);
            ErrorDetails* err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        std::string StrVal;
        m_CMAPIResponse->Get(StrVal);
        //DRECfgResp Response;
        Response->ParseFromString(StrVal);
        retVal = Response->respcode();
    }
    // return
    return retVal;
}



int CMAPIProdConfig::AddStaticRoutingEntry(StaticRoutingTableConfigReq& Request,
                                           StaticRoutingTableConfigResp& Response)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG("CMAPIProdConfig: AddStaticRoutingEntry");

    Request.set_requestid(SET_SRCONFIG);

    retVal = SendStaticRoutingRequest(Request, &Response);

    return retVal;
}



int CMAPIProdConfig::DeleteStaticRoutingEntry(StaticRoutingTableConfigReq& Request,
                                           StaticRoutingTableConfigResp& Response)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG("CMAPIProdConfig: DeleteStaticRoutingEntry");

    Request.set_requestid(DEL_SRCONFIG);

    retVal = SendStaticRoutingRequest(Request, &Response);

    return retVal;
}



int CMAPIProdConfig::ModifyStaticRoutingEntry(StaticRoutingTableConfigReq& Request,
                                           StaticRoutingTableConfigResp& Response)
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG("CMAPIProdConfig: ModifyStaticRoutingEntry");

    Request.set_requestid(MOD_SRCONFIG);

    retVal = SendStaticRoutingRequest(Request, &Response);

    return retVal;
}


int CMAPIProdConfig::SendStaticRoutingRequest(StaticRoutingTableConfigReq& req,
                                              StaticRoutingTableConfigResp *resp)
{

    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    std::string strVal;

    CLOG_DEBUG("Sending static routing config request ");

    m_StaticRoutingConfigObj->HandleSetStaticRoutingTableConfigReqs(req,
            new CMAPICookie(req.requestid(), (void *) &req));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("SendStaticRoutingRequest: Waiting for Response");

    if((m_CMAPIResponse->Get(strVal,m_waitTime)))
    {
        CLOG_DEBUG("SendStaticRoutingRequest: Response Received");
        if(strVal.empty())
        {
            return CMAPI_ERROR;
        }

        resp->ParseFromString(strVal);
        if (resp->has_responseid())
        {
            retVal = resp->responseid();
            CLOG_DEBUG("retVal : %d",resp->responseid());
        }
        else
        {
            retVal = CMAPI_SRVERROR;

        }
    }
    else
    {
        retVal = CMAPI_TIMEOUT;
        resp->set_responseid(retVal);
        ErrorDetails *err=resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    return retVal;
}

int CMAPIProdConfig::GetStaticRoutingEntries(StaticRoutingTableConfigReq& Request,
                                             StaticRoutingTableConfigResp& Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;

    CLOG_DEBUG("CMAPIProdConfig: GetStaticRoutingEntries");

    Request.set_requestid(GET_SRCONFIG);

    CLOG_DEBUG("Sending static routing table config ");

    m_StaticRoutingConfigObj->HandleGetStaticRoutingTableConfigReqs(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("GetStaticRoutingEntries: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("GetStaticRoutingEntries: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response.ParseFromString(strVal);
    if (Response.responseid() == CMAPI_SUCCESS)
    {
        retVal = Response.responseid();
        CLOG_DEBUG("GetStaticRoutingEntries: Successfully returned staticRouting");
    }
    else
    {
        retVal = CMAPI_SRVERROR;
        CLOG_ERROR("GetStaticRoutingEntries: Failed to fetch staticRouting");
    }

    return retVal;
}

int CMAPIProdConfig::HandleGetStaticRoutingTableConfigReqsRespCbk(StaticRoutingTableConfigResp *resp)
{
    CLOG_DEBUG("HandleGetStaticRoutingTableConfigReqsRespCbk");
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    int retVal = IsResponseOK(resp);
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        std::string StrVal;
        resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}

int CMAPIProdConfig::HandleSetStaticRoutingTableConfigReqsRespCbk(StaticRoutingTableConfigResp *resp)
{
    CLOG_DEBUG("HandleSetStaticRoutingTableConfigReqsRespCbk");
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if(resp != NULL)
    {
        CLOG_DEBUG("HandleSetStaticRoutingTableConfigReqsRespCbk:responseid : %d",resp->responseid());
    }
    int retVal = IsResponseOK(resp);

    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        delete lCookie;
    }
    return 0;
}

int CMAPIProdConfig::GetStaticRoutingEntriesRespCbk(StaticRoutingTableConfigResp *resp)
{
    CLOG_DEBUG(">GetStaticRoutingEntriesRespCbk");
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if(resp != NULL)
    {
        CLOG_DEBUG("GetStaticRoutingEntriesRespCbk:responseid : %d",resp->responseid());
    }
    int retVal = IsResponseOK(resp);

    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        std::string StrVal;
        resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return 0;
}

int CMAPIProdConfig::ModCMFRealmTemplate(TemplateReq Request,TemplateResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: ModCMFRealmTemplate");

    Request.set_requestid(MOD_REALM_TEMPLATE);

    m_CMgrTemplateCallerObj->HandleSetTemplateConfigReqs(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("HandleSetTemplateConfigReqs: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("HandleSetTemplateConfigReqs: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::DelCMFRealmTemplate(TemplateReq Request,TemplateResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: DelCMFRealmTemplate");

    Request.set_requestid(DEL_REALM_TEMPLATE);

    m_CMgrTemplateCallerObj->HandleSetTemplateConfigReqs(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("HandleSetTemplateConfigReqs: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("HandleSetTemplateConfigReqs: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}


int CMAPIProdConfig::AddCMFRealmTemplate(TemplateReq Request,TemplateResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: AddCMFRealmTemplate");

    Request.set_requestid(ADD_REALM_TEMPLATE);

    m_CMgrTemplateCallerObj->HandleSetTemplateConfigReqs(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("HandleSetTemplateConfigReqs: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("HandleSetTemplateConfigReqs: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::ModCMFPeerTemplate(TemplateReq Request,TemplateResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: ModCMFPeerTemplate");

    Request.set_requestid(MOD_PEER_TEMPLATE);

    m_CMgrTemplateCallerObj->HandleSetTemplateConfigReqs(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("HandleSetTemplateConfigReqs: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("HandleSetTemplateConfigReqs: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::DelCMFPeerTemplate(TemplateReq Request,TemplateResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: DelCMFPeerTemplate");

    Request.set_requestid(DEL_PEER_TEMPLATE);

    m_CMgrTemplateCallerObj->HandleSetTemplateConfigReqs(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("HandleSetTemplateConfigReqs: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("HandleSetTemplateConfigReqs: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::AddCMFPeerTemplate(TemplateReq Request,TemplateResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: AddCMFPeerTemplate");

    Request.set_requestid(ADD_PEER_TEMPLATE);

    m_CMgrTemplateCallerObj->HandleSetTemplateConfigReqs(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("HandleSetTemplateConfigReqs: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("HandleSetTemplateConfigReqs: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d",Response->responseid());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::GetCMFRealmTemplate(TemplateReq& Request,TemplateResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: GetCMFRealmTemplate");

    Request.set_requestid(GET_REALM_TEMPLATE);

    m_CMgrTemplateCallerObj->HandleGetTemplateConfigReqs(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("GetCMFRealmTemplate: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("GetCMFRealmTemplate: Response Received");

    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Request.Clear();
    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        for(int i=0;i<Response->realmtemplates_size();i++)
        {
            ::CMFRealmTemplate *src_RealmTemplate =  Response->mutable_realmtemplates(i);
            ::CMFRealmTemplate *dest_RealmTemplate =  Request.add_realmtemplates();
            dest_RealmTemplate->CopyFrom(*src_RealmTemplate);
        }

        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d Request = %s",Response->responseid(),Request.DebugString().c_str());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}


int CMAPIProdConfig::GetCMFPeerTemplate(TemplateReq& Request,TemplateResp *Response)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;
    CLOG_DEBUG("CMAPIProdConfig: GetCMFPeerTemplate");

    Request.set_requestid(GET_PEER_TEMPLATE);

    m_CMgrTemplateCallerObj->HandleGetTemplateConfigReqs(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("GetCMFPeerTemplate: Waiting for Response");

    m_CMAPIResponse->Get(strVal);
    CLOG_DEBUG("GetCMFPeerTemplate: Response Received");

    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Request.Clear();
    Response->ParseFromString(strVal);
    if (Response->has_responseid())
    {
        for(int i=0;i<Response->peertemplates_size();i++)
        {
            ::CMFPeerTemplate *src_PeerTemplate =  Response->mutable_peertemplates(i);
            ::CMFPeerTemplate *dest_PeerTemplate =  Request.add_peertemplates();
            dest_PeerTemplate->CopyFrom(*src_PeerTemplate);
        }

        retVal = Response->responseid();
        CLOG_DEBUG("retVal : %d Request = %s",Response->responseid(),Request.DebugString().c_str());
    }
    else
    {
        retVal = CMAPI_SRVERROR;

    }

    return retVal;
}

int CMAPIProdConfig::HandleGetTemplateConfigReqsRespCbk(TemplateResp *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">HandleGetTemplateConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("HandleGetLocalHostConfigReqs message failed. Error: ");
        if (resp == NULL )
        {
            TemplateResp ErrorResponse;
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
    delete lCookie;
    return retVal;
}


int CMAPIProdConfig::HandleSetTemplateConfigReqsRespCbk(TemplateResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">CMAPIProdConfig: HandleSetTemplateConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("HandleSetTemplateConfigReqsRespCbk message failed. Error: ");
        if (resp == NULL )
        {
            TemplateResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }


    delete lCookie;
    CLOG_DEBUG("<CMAPIProdConfig: HandleSetTemplateConfigReqsRespCbk");
    return retVal;
}

int CMAPIProdConfig::IsResponseOK(StaticRoutingTableConfigResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG(" >CMAPIProdConfig: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL
            || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        StaticRoutingTableConfigResp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);

        if ( Resp!=NULL && Resp->has_responseid() )
        {
            retVal = Resp->responseid();
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails *err = ErrResp.add_errordetails();
            err->set_errorcode(ERROR_TRACECONFIG_MAX_ERROR);
            ErrResp.SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
        if(lCookie != NULL)
            delete lCookie;
    }
    CLOG_DEBUG(" <CMAPIProdConfig: IsResponseOK");
    return retVal;
}

int CMAPIProdConfig::HandleSetDictionaryConfigReqRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (resp == NULL )
        {
            DRECfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respcode(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }

    delete lCookie;
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::HandleSetPluginConfigReqRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (resp == NULL )
        {
            DRECfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respcode(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }

    delete lCookie;
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::HandleGetPluginConfigReqRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (resp == NULL )
        {
            DRECfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respcode(retVal);
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
    delete lCookie;
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::HandleGetDictionaryConfigReqRespCbk(DRECfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (resp == NULL )
        {
            DRECfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respcode(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
            CLOG_DEBUG(" Resp: %s ",resp->DebugString().c_str());
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie;
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

// CMAPI Calls from CLI/GUI
int CMAPIProdConfig::GetSDTFConfig(SDTFReq& Req, SDTFResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    Req.set_requestid(GET_SDTF_CONFIG);
    m_SendSuccess = true;

    // Call CMGR Method Implementation
    m_CMgrCallerObj->GetSDTFConfig(Req,
            new CMAPICookie(GET_SDTF_CONFIG, (void *) &Req));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        Resp.set_responseid(retVal);
        ErrorDetails* err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal, m_waitTime))
    {
        Resp.Clear();
        Resp.ParseFromString(StrVal);
        CLOG_DEBUG(" Resp: %s ", StrVal.c_str());
        CLOG_DEBUG(" Resp: %s ", Resp.DebugString().c_str());
        retVal = Resp.responseid();
    }
    else
    {
        Resp.set_responseid(CMAPI_TIMEOUT);
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        // Fill in errordetails in Response
        ErrorDetails *err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::SetSDTFRuleStatus(SDTFReq& Req, SDTFResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;

    if ((!Req.IsInitialized()) || (Req.rule_size() <= 0))
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::SetSDTFRuleStatus Invalid Params");
    }
    else
    {
        Req.set_requestid(SET_SDTF_RULE_STATUS);
        CLOG_DEBUG(">CMAPIProdConfig: SET_SDTF_RULE_STATUS Request");
        // Call CMGR Method Implementation
        m_CMgrCallerObj->SetSDTFConfig(Req,
                new CMAPICookie(SET_SDTF_RULE_STATUS, (void *) &Req));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            ErrorDetails *err =Resp.add_errordetails();
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal, m_waitTime))
        {
            ErrorDetails *err =Resp.add_errordetails();
            Resp.ParseFromString(StrVal);
            retVal = Resp.responseid();
            if(Resp.errordetails_size())
            {
                err->CopyFrom(Resp.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            ErrorDetails *err =Resp.add_errordetails();
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Resp.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::AddSDTFConfig(SDTFReq& Req, SDTFResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;

    if ((!Req.IsInitialized()) || (Req.rule_size() <= 0))
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::AddSDTFConfig Invalid Params");
    }
    else
    {
        Req.set_requestid(ADD_SDTF_CONFIG);
        CLOG_DEBUG(">CMAPIProdConfig: ADD_SDTF_CONFIG Request");
        // Call CMGR Method Implementation
        m_CMgrCallerObj->SetSDTFConfig(Req,
                new CMAPICookie(ADD_SDTF_CONFIG, (void *) &Req));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            ErrorDetails *err =Resp.add_errordetails();
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal, m_waitTime))
        {
            ErrorDetails *err =Resp.add_errordetails();
            Resp.ParseFromString(StrVal);
            retVal = Resp.responseid();
            if(Resp.errordetails_size())
            {
                err->CopyFrom(Resp.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            ErrorDetails *err =Resp.add_errordetails();
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Resp.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::ModifySDTFConfig(SDTFReq& Req, SDTFResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;

    if ((!Req.IsInitialized()) || (Req.rule_size() <= 0))
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::ModifySDTFConfig Invalid Params");
    }
    else
    {
        Req.set_requestid(MOD_SDTF_CONFIG);
        CLOG_DEBUG(">CMAPIProdConfig: MOD_SDTF_CONFIG Request");
        // Call CMGR Method Implementation
        m_CMgrCallerObj->SetSDTFConfig(Req,
                new CMAPICookie(MOD_SDTF_CONFIG, (void *) &Req));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            ErrorDetails *err =Resp.add_errordetails();
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal, m_waitTime))
        {
            ErrorDetails *err =Resp.add_errordetails();
            Resp.ParseFromString(StrVal);
            retVal = Resp.responseid();
            if(Resp.errordetails_size())
            {
                err->CopyFrom(Resp.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            ErrorDetails *err =Resp.add_errordetails();
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Resp.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::DeleteSDTFConfig(string& RuleName, SDTFResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;

    if (RuleName.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::DeleteSDTFConfig Invalid Params");
    }
    else
    {
        SDTFReq Req;
        SDTFRule *pRuleConfig = Req.add_rule();
        pRuleConfig->set_rulename(RuleName);
        Req.set_requestid(DEL_SDTF_CONFIG);
        CLOG_DEBUG(">CMAPIProdConfig: DEL_SDTF_CONFIG Request");
        // Call CMGR Method Implementation
        m_CMgrCallerObj->SetSDTFConfig(Req,
                new CMAPICookie(DEL_SDTF_CONFIG, (void *) &Req));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            ErrorDetails *err =Resp.add_errordetails();
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal, m_waitTime))
        {
            ErrorDetails *err =Resp.add_errordetails();
            Resp.ParseFromString(StrVal);
            retVal = Resp.responseid();
            if(Resp.errordetails_size())
            {
                err->CopyFrom(Resp.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            ErrorDetails *err =Resp.add_errordetails();
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Resp.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::GetSDTFEnableStatus(SDTFResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    SDTFReq Req;
    Req.set_requestid(GET_SDTF_ENABLE_STATUS);
    m_SendSuccess = true;

    // Call CMGR Method Implementation
    m_CMgrCallerObj->GetSDTFConfig(Req,
            new CMAPICookie(GET_SDTF_ENABLE_STATUS, (void *) &Req));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        Resp.set_responseid(retVal);
        ErrorDetails* err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal, m_waitTime))
    {
        Resp.Clear();
        Resp.ParseFromString(StrVal);
        CLOG_DEBUG(" Resp: %s ", StrVal.c_str());
        CLOG_DEBUG(" Resp: %s ", Resp.DebugString().c_str());
        retVal = Resp.responseid();
    }
    else
    {
        Resp.set_responseid(CMAPI_TIMEOUT);
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        // Fill in errordetails in Response
        ErrorDetails *err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::SetSDTFEnableStatus(bool enableSDTF, SDTFResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;

    SDTFReq Req;
    Req.set_requestid(SET_SDTF_ENABLE_STATUS);
    Req.set_enablesdtf(enableSDTF);
    CLOG_DEBUG(">CMAPIProdConfig: SET_SDTF_ENABLE_STATUS Request");
    // Call CMGR Method Implementation
    m_CMgrCallerObj->SetSDTFConfig(Req,
            new CMAPICookie(SET_SDTF_ENABLE_STATUS, (void *) &Req));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        ErrorDetails *err =Resp.add_errordetails();
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    if(m_CMAPIResponse->Get(StrVal, m_waitTime))
    {
        ErrorDetails *err =Resp.add_errordetails();
        Resp.ParseFromString(StrVal);
        retVal = Resp.responseid();
        if(Resp.errordetails_size())
        {
            err->CopyFrom(Resp.errordetails(0));
        }
    }
    else
    {
        retVal = CMAPI_TIMEOUT;
        ErrorDetails *err =Resp.add_errordetails();
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        Resp.set_responseid(CMAPI_TIMEOUT);
        // Fill in errordetails in Response
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

// Response Callbacks
int CMAPIProdConfig::GetSDTFConfigRespCbk(SDTFResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }

    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (resp == NULL)
        {
            SDTFResp errorResp;
            retVal = CMAPI_SRVERROR;
            errorResp.set_responseid(retVal);
            errorResp.SerializeToString(&StrVal);
        }
        else
        {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie;

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIProdConfig::SetSDTFConfigRespCbk(SDTFResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }

    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            resp == NULL || resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (resp == NULL)
        {
            SDTFResp errorResp;
            retVal = CMAPI_SRVERROR;
            errorResp.set_responseid(retVal);
            errorResp.SerializeToString(&StrVal);
        }
        else
        {
            resp->SerializeToString(&StrVal);
            CLOG_DEBUG(" resp: %s ", resp->DebugString().c_str());
        }
        m_CMAPIResponse->Set(StrVal);
    }

    delete lCookie;
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

// Results Implementation
int CMAPIProdConfig::SendSDTFConfigResult(SDTFResp *Req, CMAPIRes *Resp)
{
    CLOG_DEBUG(" >>>>>>>>>> Entered CMAPIProdConfig::SendSDTFConfigResult() >>>>>>>>>>\n");

    string StrVal;
    if (Req != NULL)
    {
        Req->SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);
    Resp->set_responsecode(CMAPI_SUCCESS);

    CLOG_DEBUG(" <<<<<<<<<< Exiting CMAPIProdConfig::SendSDTFConfigResult() <<<<<<<<<<\n");
    return 0;
}

