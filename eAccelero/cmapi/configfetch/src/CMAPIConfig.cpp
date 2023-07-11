
#include "CMAPIConfig.h"
#include "ComponentDefines.h"

#define GETCONFIG 100

int CMAPIConfig::InitializeLibrary(FetchDataAsync *m_AsyncObj)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMAPIConfig: InitializeLibrary - Initializing Config Manager Interface\n");

    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, CMGR_INSTANCE_ID};
    m_CmgrCompoObj = new Stub::FetchConfiguration(dest,0);
    m_CmgrDreObj   = new Stub::DreFetch(dest,0);
    m_CmgrCMFObj   = new Stub::DreTemplateFetch(dest,0);
    m_CMgrCMFFetchObj = new Stub::CMFConfigFetch(dest,0);
    m_CmgrStaticRoutingObj   = new Stub::DreStaticRoutingConfigFetch(dest,0);

    CLOG_DEBUG("Registering Fetch Callbacks");
    RegisterDreFetchRespHandler();
    RegisterFetchConfigurationRespHandler();
    RegisterDreStaticRoutingConfigFetchRespHandler();
    RegisterDreTemplateFetchRespHandler();
    RegisterCMFConfigFetchRespHandler();

    m_SyncObj = new CMAPIIntSync();
    m_AsyncObjPtr = NULL;
    m_AsyncCall = false;

    if (m_AsyncObj != NULL)
    {
        m_AsyncObjPtr = m_AsyncObj;
    }

    return retVal;
}


int CMAPIConfig::GetSDTFConfiguration(SDTFResp *resp)
{
    CLOG_DEBUG(">CMAPIConfig::GetSDTFConfiguration ");
    m_SendSuccess = true;
    cout << ">CMAPIConfig::GetSDTFConfiguration " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    SDTFReq req;
    m_CmgrDreObj->FetchSDTFConfig(req);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        resp->ParseFromString(ResponseString);
        retVal = resp->responseid();
        cout << "Config fetch resp received is" << resp->DebugString() << endl;
    } else {
        retVal = CMAPI_ERROR;
        cout << "Config fetch error resp received " << endl;
    }
    return retVal;
}

int CMAPIConfig::GetCMFConfiguration(TemplateResp *resp)
{
    CLOG_DEBUG(">CMAPIConfig::GetCMFConfiguration ");
    m_SendSuccess = true;
    cout << ">CMAPIConfig::GetCMFConfiguration " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    TemplateReq req;
    m_CmgrCMFObj->FetchDreTemplateConfiguration(req);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        resp->ParseFromString(ResponseString);
        retVal = resp->responseid();
        cout << "Config fetch resp received is" << resp->DebugString() << endl;
    } else {
        retVal = CMAPI_ERROR;
        cout << "Config fetch error resp received " << endl;
    }
    return retVal;
}

int CMAPIConfig::GetSDTFConfiguration(bool useCurrentInstanceId,
        SDTFResp *resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">CMAPIConfig::GetSDTFConfiguration ");
    cout << ">CMAPIConfig::GetSDTFConfiguration " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    SDTFReq req;
    req.set_requestid(GET_SDTF_CONFIG);
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::DreFetch cmgrSDTFObj(dest,0);
    cmgrSDTFObj.FetchSDTFConfig(req);

    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        resp->ParseFromString(ResponseString);
        retVal = resp->responseid();
        cout << "Config fetch resp received is" << resp->DebugString() << endl;
    } else {
        retVal = CMAPI_ERROR;
        cout << "Config fetch error resp received " << endl;
    }
    return retVal;
}

int CMAPIConfig::GetCMFConfiguration(bool useCurrentInstanceId,
        TemplateResp *resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">CMAPIConfig::GetCMFConfiguration ");
    cout << ">CMAPIConfig::GetCMFConfiguration " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    TemplateReq req;
    req.set_requestid(GET_REALM_TEMPLATE);
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::DreTemplateFetch cmgrDreObj(dest,0);
    cmgrDreObj.FetchDreTemplateConfiguration(req);

    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        resp->ParseFromString(ResponseString);
        retVal = resp->responseid();
        cout << "Config fetch resp received is" << resp->DebugString() << endl;
    } else {
        retVal = CMAPI_ERROR;
        cout << "Config fetch error resp received " << endl;
    }
    return retVal;
}


int CMAPIConfig::GetDreConfiguration(DRECfgResp *resp)
{
    CLOG_DEBUG(">CMAPIConfig::GetDreConfiguration ");
    m_SendSuccess = true;
    cout << ">CMAPIConfig::GetDreConfiguration " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    PeersConfig pCfg;
    m_CmgrDreObj->FetchDreConfiguration(pCfg);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        resp->ParseFromString(ResponseString);
        retVal = resp->respcode();
        cout << "Config fetch resp received is" << resp->DebugString() << endl;
    } else {
        retVal = CMAPI_ERROR;
        cout << "Config fetch error resp received " << endl;
    }
    return retVal;
}

int CMAPIConfig::GetDreConfiguration(bool useCurrentInstanceId,
        DRECfgResp *resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">CMAPIConfig::GetDreConfiguration ");
    cout << ">CMAPIConfig::GetDreConfiguration " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    PeersConfig pCfg;
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::DreFetch cmgrDreObj(dest,0);
    cmgrDreObj.FetchDreConfiguration(pCfg);

    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        resp->ParseFromString(ResponseString);
        retVal = resp->respcode();
        cout << "Config fetch resp received is" << resp->DebugString() << endl;
    } else {
        retVal = CMAPI_ERROR;
        cout << "Config fetch error resp received " << endl;
    }
    return retVal;
}

int CMAPIConfig::GetErlbfConfiguration(LBPeerGroups *Resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">CMAPIConfig::GetErlbfConfiguration ");
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    LBPeerGroupReq Req;
    Req.set_requestid(GETCONFIG);
    m_AsyncCall = false;
    m_CmgrCompoObj->FetchErlbfConfiguration(Req);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        LBPeerGroupResp Response;
        Response.ParseFromString(ResponseString);
        int NumPGrps = Response.peergroups_size();
        if (NumPGrps > 0)
        {
            for (int i=0; i < NumPGrps; i++)
            {
                LBPeerGroup* pGrp = Resp->add_peergroups();
                pGrp->CopyFrom(Response.peergroups(i));
            }
        } else {
            retVal = CMAPI_ERROR;
        }
    }
    else
    {
        retVal = CMAPI_SRVERROR;
    }
    return retVal;
}

int CMAPIConfig::GetErlbfConfiguration(bool useCurrentInstanceId, LBPeerGroups *Resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">CMAPIConfig::GetErlbfConfiguration ");
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    LBPeerGroupReq Req;
    Req.set_requestid(GETCONFIG);
    m_AsyncCall = false;
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::FetchConfiguration cmgrErlbfObj(dest,0);
    cmgrErlbfObj.FetchErlbfConfiguration(Req);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }

    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        LBPeerGroupResp Response;
        Response.ParseFromString(ResponseString);
        int NumPGrps = Response.peergroups_size();
        if (NumPGrps > 0)
        {
            for (int i=0; i < NumPGrps; i++)
            {
                LBPeerGroup* pGrp = Resp->add_peergroups();
                pGrp->CopyFrom(Response.peergroups(i));
            }
        } else {
            retVal = CMAPI_ERROR;
        }
    }
    else
    {
        retVal = CMAPI_SRVERROR;
    }
    return retVal;
}
int CMAPIConfig::GetErlbfConfigurationAsync()
{
    CLOG_DEBUG(">CMAPIConfig::GetErlbfConfiguration ");
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;

    if (m_AsyncObjPtr != NULL)
    {
        LBPeerGroupReq Req;
        Req.set_requestid(GETCONFIG);
        m_AsyncCall = true;
        m_CmgrCompoObj->FetchErlbfConfiguration(Req);
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_SendSuccess = true;
            return retVal;
        }
    } else {
        retVal = CMAPI_ERROR; // Error Code TDB: Callback not registered
    }

    return retVal;
}

int CMAPIConfig::GetErlbfConfigurationAsync(bool useCurrentInstanceId)
{
    CLOG_DEBUG(">CMAPIConfig::GetErlbfConfiguration ");
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;

    if (m_AsyncObjPtr != NULL)
    {
        LBPeerGroupReq Req;
        Req.set_requestid(GETCONFIG);
        m_AsyncCall = true;
        MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
        Stub::FetchConfiguration cmgrErlbfObj(dest,0);
        cmgrErlbfObj.FetchErlbfConfiguration(Req);
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_SendSuccess = true;
            return retVal;
        }
    } else {
        retVal = CMAPI_ERROR; // Error Code TDB: Callback not registered
    }

    return retVal;
}

int CMAPIConfig::GetDTFConfiguration(DynDictionaryResponse *Resp)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    DynDictionaryRequest Request;
    Request.set_requestid(GETCONFIG);
    m_CmgrCompoObj->FetchDTFConfiguration(Request);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        Resp->ParseFromString(ResponseString);
        retVal = Resp->responseid();
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIConfig::GetDTFConfiguration(bool useCurrentInstanceId,
        DynDictionaryResponse *Resp)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    DynDictionaryRequest Request;
    Request.set_requestid(GETCONFIG);

    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::FetchConfiguration cmgrErlbfObj(dest,0);
    cmgrErlbfObj.FetchDTFConfiguration(Request);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        Resp->ParseFromString(ResponseString);
        retVal = Resp->responseid();
    }
    return retVal;
}

int CMAPIConfig::GetASFConfiguration(ASFConfigResp *Resp)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    ASFConfigReq Request;
    Request.set_requestid(GETCONFIG);
    m_CmgrCompoObj->FetchASFConfiguration(Request);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }
    if (m_SyncObj->Get(ResponseString, m_waitCMAPI))
    {
        Resp->ParseFromString(ResponseString);
        retVal = Resp->responseid();
    } else {
        retVal = CMAPI_TIMEOUT;
    }
    return retVal;
}

int CMAPIConfig::GetASFConfiguration(bool useCurrentInstanceId, ASFConfigResp *Resp)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    ASFConfigReq Request;
    Request.set_requestid(GETCONFIG);

    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::FetchConfiguration cmgrErlbfObj(dest,0);
    cmgrErlbfObj.FetchASFConfiguration(Request);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }

    if (m_SyncObj->Get(ResponseString, m_waitCMAPI))
    {
        if (!ResponseString.empty())
        {
            Resp->ParseFromString(ResponseString);
            retVal = Resp->responseid();
        }
    } else {
        retVal = CMAPI_TIMEOUT;
    }
    return retVal;
}

//DTF
int CMAPIConfig::GetDictionaryConfiguration(DRECfgResp *resp)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    CLOG_DEBUG(">CMAPIConfig:: %s",__FUNCTION__);
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    DictionaryConfigReq DictCfg;
    m_CmgrDreObj->FetchDictionaryConfig(DictCfg);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        CLOG_DEBUG(" < %s ",__FUNCTION__);
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        resp->ParseFromString(ResponseString);
        retVal = resp->respcode();
        CLOG_DEBUG("Config fetch resp received is %s",resp->DebugString().c_str());
    } else {
        retVal = CMAPI_ERROR;
        CLOG_DEBUG("Config fetch error resp received");
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}
int CMAPIConfig::GetDictionaryConfiguration(bool useCurrentInstanceId,DRECfgResp *resp)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    CLOG_DEBUG(">CMAPIConfig::GetDictionaryConfiguration");
    m_SendSuccess = true;
    cout << ">CMAPIConfig::GetDictionaryConfiguration " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    //PeersConfig pCfg;
    DictionaryConfigReq DictCfg;
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::DreFetch cmgrDreObj(dest,0);
    cmgrDreObj.FetchDictionaryConfig(DictCfg);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        CLOG_DEBUG(" < %s ",__FUNCTION__);
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        resp->ParseFromString(ResponseString);
        retVal = resp->respcode();
        cout << "Config fetch resp received is" << resp->DebugString() << endl;
    } else {
        retVal = CMAPI_ERROR;
        cout << "Config fetch error resp received " << endl;
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIConfig::GetTransformPluginConfiguration(DRECfgResp *resp)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    CLOG_DEBUG(">CMAPIConfig:: %s",__FUNCTION__);
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    TransformPluginConfigReq TransPluginCfg;
    m_CmgrDreObj->FetchPluginConfig(TransPluginCfg);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        CLOG_DEBUG(" < %s ",__FUNCTION__);
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        resp->ParseFromString(ResponseString);
        retVal = resp->respcode();
        CLOG_DEBUG("Config fetch resp received is %s",resp->DebugString().c_str());
    } else {
        retVal = CMAPI_ERROR;
        CLOG_DEBUG("Config fetch error resp received");
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIConfig::GetTransformPluginConfiguration(bool useCurrentInstanceId,DRECfgResp *resp)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    CLOG_DEBUG(">CMAPIConfig::GetTransformPluginConfiguration ");
    m_SendSuccess = true;
    cout << ">CMAPIConfig::GetTransformPluginConfiguration " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    //PeersConfig pCfg;
    TransformPluginConfigReq TransPluginCfg;
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::DreFetch cmgrDreObj(dest,0);
    cmgrDreObj.FetchPluginConfig(TransPluginCfg);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        CLOG_DEBUG(" < %s ",__FUNCTION__);
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        resp->ParseFromString(ResponseString);
        retVal = resp->respcode();
        cout << "Config fetch resp received is" << resp->DebugString() << endl;
    } else {
        retVal = CMAPI_ERROR;
        cout << "Config fetch error resp received " << endl;
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

// Congestion management config-fetch
int CMAPIConfig::GetCMFTemlateConfig(TemplateResp *Resp)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    CLOG_DEBUG(">CMAPIConfig:: %s",__FUNCTION__);
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    TemplateReq Req;
    m_CMgrCMFFetchObj->FetchCMFTemlateConfig(Req);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        CLOG_DEBUG(" < %s ",__FUNCTION__);
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        Resp->ParseFromString(ResponseString);
        retVal = Resp->responseid();
        CLOG_DEBUG("Config fetch resp received is %s",Resp->DebugString().c_str());
    } else {
        retVal = CMAPI_ERROR;
        CLOG_DEBUG("Config fetch error resp received");
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIConfig::GetCMFConfig(bool useCurrentInstanceId, CMFConfigResp *Resp)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    CLOG_DEBUG(">CMAPIConfig:: %s",__FUNCTION__);
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    CMFConfigReq Req;
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::CMFConfigFetch cmgrDreObj(dest,0);
    cmgrDreObj.FetchCMFConfig(Req);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        CLOG_DEBUG(" < %s ",__FUNCTION__);
        return retVal;
    }
    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        Resp->ParseFromString(ResponseString);
        retVal = Resp->responseid();
        CLOG_DEBUG("Config fetch resp received is %s",Resp->DebugString().c_str());
    } else {
        retVal = CMAPI_ERROR;
        CLOG_DEBUG("Config fetch error resp received");
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPIConfig::FetchASFConfigurationRespCbk(ASFConfigResp *Resp)
{
    string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL)
    {
        ASFConfigResp ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_SRVERROR);
        //Fill ErrorDetails here
        ErrorResponse.SerializeToString(&ResponseString);
    } else  {
        Resp->SerializeToString(&ResponseString);
    }
    m_SyncObj->Set(ResponseString);
    return 0;
}

int CMAPIConfig::GetLoggerConfiguration(LoggerConfResp *Resp)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    LoggerConfReq Req;
    Req.set_requestid(GET_LOGGERCONFIG);

    CLOG_DEBUG("CMAPIConfig::GetLoggerConfigurations");

    m_CmgrCompoObj->FetchLoggerConfiguration(Req);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }

    m_SyncObj->Get(ResponseString);
    if(!ResponseString.empty())
    {
        LoggerConfResp Response;
        Response.ParseFromString(ResponseString);
        int numComp = Response.loggerconfig_size();
        if(numComp > 0)
        {
            for(int curComp = 0 ; curComp < numComp ; curComp++)
            {
                LoggerConf *logConf = Resp->add_loggerconfig();
                logConf->CopyFrom(Response.loggerconfig(curComp));
            }
            Resp->set_responseid(CMAPI_SUCCESS);
        }
        else
        {
            retVal = CMAPI_ERROR;
        }
    }
    else
    {
        retVal = CMAPI_SRVERROR;
    }
    return retVal;

}

int CMAPIConfig::GetLoggerConfiguration(bool useCurrentInstanceId,
        LoggerConfResp *Resp)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    LoggerConfReq Req;
    Req.set_requestid(GET_LOGGERCONFIG);

    CLOG_DEBUG("CMAPIConfig::GetLoggerConfigurations");

    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::FetchConfiguration cmgrErlbfObj(dest,0);
    cmgrErlbfObj.FetchLoggerConfiguration(Req);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }

    m_SyncObj->Get(ResponseString);
    if(!ResponseString.empty())
    {
        LoggerConfResp Response;
        Response.ParseFromString(ResponseString);
        int numComp = Response.loggerconfig_size();
        if(numComp > 0)
        {
            for(int curComp = 0 ; curComp < numComp ; curComp++)
            {
                LoggerConf *logConf = Resp->add_loggerconfig();
                logConf->CopyFrom(Response.loggerconfig(curComp));
            }
            Resp->set_responseid(CMAPI_SUCCESS);
        }
        else
        {
            retVal = CMAPI_ERROR;
        }
    }
    else
    {
        retVal = CMAPI_SRVERROR;
    }
    return retVal;

}
int CMAPIConfig::FetchDTFConfigurationRespCbk(DynDictionaryResponse *Resp)
{
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !Resp->IsInitialized() ||
            Resp->responseid() != CMAPI_SUCCESS )
    {
        DynDictionaryResponse Response;
        Response.set_responseid((int)CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        Resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}


int CMAPIConfig::FetchErlbfConfigurationRespCbk(LBPeerGroupResp *Resp)
{
    CLOG_DEBUG(">CMAPIConfig::FetchErlbfConfigurationRespCbk");
    std::string ResponseString;
    LBPeerGroupResp Response;
    LBPeerGroupResp *RespPtr;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL ||
            !Resp->IsInitialized() || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchErlbfConfiguration CallBack :  ERROR ");
        Response.set_responseid((int)CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
        RespPtr = &Response;
    }
    else
    {
        Resp->SerializeToString(&ResponseString);
        RespPtr = Resp;
    }

    if (m_AsyncCall == true)
    {
        m_AsyncCall = false;
        LBPeerGroups PGrps;
        int NumPGrps = RespPtr->peergroups_size();
        if (NumPGrps > 0)
        {
            for (int i=0; i < NumPGrps; i++)
            {
                LBPeerGroup* pGrp = PGrps.add_peergroups();
                pGrp->CopyFrom(RespPtr->peergroups(i));
            }
        }
        m_AsyncObjPtr->ErlbfConfiguration(&PGrps);
    } else {
        m_SyncObj->Set(ResponseString);
    }
    return 0;
}

int CMAPIConfig::FetchDreConfigurationRespCbk(DRECfgResp *resp)
{
    CLOG_DEBUG(">CMAPIConfig::FetchErlbfConfigurationRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !resp->IsInitialized() ||
            resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchDreConfiguration Callback : ERROR ");
        DRECfgResp Response;
        Response.set_respcode(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int CMAPIConfig::FetchLoggerConfigurationRespCbk(LoggerConfResp *resp)
{
    CLOG_DEBUG("CMAPIConfig::FetchLoggerConfigurationRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !resp->IsInitialized() ||
            resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchLoggerConfiguration Callback : ERROR ");
        LoggerConfResp Response;
        Response.set_responseid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int CMAPIConfig::GetStackConfiguration(StackConfigResponse *Resp)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    StackConfigRequest Request;
    Request.set_requestid(GETCONFIG);
    m_CmgrDreObj->FetchStackConfiguration(Request);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }
    m_SyncObj->Get(ResponseString);

    Resp->ParseFromString(ResponseString);
    retVal = Resp->responseid();
    return retVal;
}

int CMAPIConfig::GetStackConfiguration(bool useCurrentInstanceId, StackConfigResponse *Resp)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    StackConfigRequest Request;
    Request.set_requestid(GETCONFIG);

    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::DreFetch cmgrDreObj(dest,0);
    cmgrDreObj.FetchStackConfiguration(Request);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }

    m_SyncObj->Get(ResponseString);
    Resp->ParseFromString(ResponseString);
    retVal = Resp->responseid();
    return retVal;
}

int CMAPIConfig::FetchStackConfigurationRespCbk(StackConfigResponse *Resp)
{
    string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL)
    {
        StackConfigResponse ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_SRVERROR);
        //Fill ErrorDetails here
        ErrorResponse.SerializeToString(&ResponseString);
    } else  {
        Resp->SerializeToString(&ResponseString);
    }
    m_SyncObj->Set(ResponseString);
    return 0;
}

int CMAPIConfig::GetTraceConfiguration(TraceResp *Resp)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    TraceReq Req;

    CLOG_DEBUG("CMAPIConfig::GetTraceConfiguration ");
    Req.set_requestid(GET_TRACE);
    m_CmgrDreObj->FetchTraceConfiguration(Req);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }

    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        Resp->ParseFromString(ResponseString);
        Resp->set_responseid(CMAPI_SUCCESS);
        retVal = Resp->responseid();
    }
    else
    {
        retVal = CMAPI_ERROR;
    }
    return retVal;
}

int CMAPIConfig::GetTopologyHidingFetureConfiguration(THFResp *Resp)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    THFReq Req;

    CLOG_DEBUG("CMAPIConfig::GetTopologyHidingFetureConfiguration");
    Req.set_requestid(GET_THF_ENABLE);
    m_CmgrDreObj->FetchTHFConfig(Req);

    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }

    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        Resp->ParseFromString(ResponseString);
        Resp->set_responseid(CMAPI_SUCCESS);
        retVal = Resp->responseid();
    }
    else
    {
        retVal = CMAPI_ERROR;
    }
    return retVal;
}

int CMAPIConfig::GetTopologyHidingFeatureConfiguration(bool useCurrentInstanceId,
                                               THFResp *Resp)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    THFReq Req;

    CLOG_DEBUG("CMAPIConfig::GetTopologyHidingFeatureConfiguration");
    Req.set_requestid(GET_THF_ENABLE);
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::DreFetch cmgrTopologyReqObj(dest,0);
    cmgrTopologyReqObj.FetchTHFConfig(Req);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }

    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        Resp->ParseFromString(ResponseString);
        Resp->set_responseid(CMAPI_SUCCESS);
        retVal = Resp->responseid();
    }
    else
    {
        retVal = CMAPI_ERROR;
    }
    return retVal;
}

int CMAPIConfig::GetTraceConfiguration(bool useCurrentInstanceId, TraceResp *Resp)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    TraceReq Req;

    CLOG_DEBUG("CMAPIConfig::GetTraceConfiguration ");
    Req.set_requestid(GET_TRACE);
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::DreFetch cmgrDreObj(dest,0);
    cmgrDreObj.FetchTraceConfiguration(Req);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }

    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        Resp->ParseFromString(ResponseString);
        Resp->set_responseid(CMAPI_SUCCESS);
        retVal = Resp->responseid();
    }
    else
    {
        retVal = CMAPI_ERROR;
    }
    return retVal;
}

int CMAPIConfig::GetStaticRoutingConfiguration(StaticRoutingTableConfigResp *Resp)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    StaticRoutingTableConfigReq Req;

    CLOG_DEBUG("CMAPIConfig::GetStaticRoutingConfiguration ");
    Req.set_requestid(GET_SRCONFIG);
    m_CmgrStaticRoutingObj->FetchStaticRoutingTableConfiguration(Req);

    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }

    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        Resp->ParseFromString(ResponseString);
        Resp->set_responseid(CMAPI_SUCCESS);
        retVal = Resp->responseid();
    }
    else
    {
        retVal = CMAPI_ERROR;
    }
    return retVal;
}

int CMAPIConfig::GetStaticRoutingConfiguration(bool useCurrentInstanceId,
                                               StaticRoutingTableConfigResp *Resp)
{
    m_SendSuccess = true;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    StaticRoutingTableConfigReq Req;

    CLOG_DEBUG("CMAPIConfig::GetStaticRoutingConfiguration");
    Req.set_requestid(GET_SRCONFIG);
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::DreStaticRoutingConfigFetch cmgrStaticRoutingObj(dest,0);
    cmgrStaticRoutingObj.FetchStaticRoutingTableConfiguration(Req);
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_SendSuccess = true;
        return retVal;
    }

    m_SyncObj->Get(ResponseString);
    if (!ResponseString.empty())
    {
        Resp->ParseFromString(ResponseString);
        Resp->set_responseid(CMAPI_SUCCESS);
        retVal = Resp->responseid();
    }
    else
    {
        retVal = CMAPI_ERROR;
    }
    return retVal;
}

int CMAPIConfig::FetchDreTemplateConfigurationRespCbk(TemplateResp *resp)
{
    CLOG_DEBUG("CMAPIConfig::FetchDreTemplateConfigurationRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !resp->IsInitialized() ||
            resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchDreTemplateConfiguration Callback : ERROR ");
        TraceResp Response;
        Response.set_responseid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int CMAPIConfig::FetchTHFConfigRespCbk(THFResp *resp)
{
    CLOG_DEBUG("CMAPIConfig::FetchTHFConfigRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !resp->IsInitialized() ||
            resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchTHFConfig Callback : ERROR MeSS state %d",
            MeSS::Handle().m_state);
        THFResp Response;
        Response.set_responseid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int CMAPIConfig::FetchSDTFConfigRespCbk(SDTFResp *resp)
{
    CLOG_DEBUG("CMAPIConfig::FetchSDTFConfigRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !resp->IsInitialized() ||
            resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchSDTFConfig Callback : ERROR MeSS state %d",
            MeSS::Handle().m_state);
        SDTFResp Response;
        Response.set_responseid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int CMAPIConfig::FetchTraceConfigurationRespCbk(TraceResp *resp)
{
    CLOG_DEBUG("CMAPIConfig::FetchTraceConfigurationRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !resp->IsInitialized() ||
            resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchTraceConfiguration Callback : ERROR ");
        TraceResp Response;
        Response.set_responseid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

void CMAPIConfig::UpdateCurrentInstanceId(uint16_t newInstanceId)
{
    m_currentIntanceId = newInstanceId;
}

int CMAPIConfig::FetchStaticRoutingTableConfigurationRespCbk(StaticRoutingTableConfigResp* resp)
{
    CLOG_DEBUG("CMAPIConfig::FetchStaticRoutingTableConfigurationRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !resp->IsInitialized() ||
            resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchStaticRoutingTableConfigurationRespCbk : ERROR ");
        TraceResp Response;
        Response.set_responseid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int CMAPIConfig::FetchDictionaryConfigRespCbk(DRECfgResp *resp)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        CLOG_DEBUG(" < %s ",__FUNCTION__);
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !resp->IsInitialized() ||
            resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG(" %s MeSS ERROR ",__FUNCTION__);
        DRECfgResp Response;
        Response.set_respcode(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPIConfig::FetchPluginConfigRespCbk(DRECfgResp *resp)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        CLOG_DEBUG(" < %s ",__FUNCTION__);
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !resp->IsInitialized() ||
            resp->respcode() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG(" %s MeSS ERROR ",__FUNCTION__);
        DRECfgResp Response;
        Response.set_respcode(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return 0;
}

// Congestion management response-callback
int CMAPIConfig::FetchCMFTemlateConfigRespCbk(TemplateResp *resp)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        CLOG_DEBUG(" < %s ",__FUNCTION__);
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !resp->IsInitialized() ||
            resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG(" %s MeSS ERROR ",__FUNCTION__);
        TemplateResp Response;
        Response.set_responseid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return 0;
}

int CMAPIConfig::FetchCMFConfigRespCbk(CMFConfigResp *resp)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        CLOG_DEBUG(" < %s ",__FUNCTION__);
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !resp->IsInitialized() ||
            resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG(" %s MeSS ERROR ",__FUNCTION__);
        CMFConfigResp Response;
        Response.set_responseid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return 0;
}
