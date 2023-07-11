
#include "IWFConfigFetch.h"
#include "ComponentDefines.h"
#include "IwfFetch_caller.h"

#define GETIWFCONFIG 200

int IWFConfigFetch::InitializeLibrary()
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">IWFFetch: InitializeLibrary - Initializing Config Manager Interface\n");

    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, CMGR_INSTANCE_ID};
    m_CmgrIwfObj   = new Stub::IwfFetch(dest,0);

    CLOG_DEBUG("Registering Fetch Callbacks");
    RegisterIwfFetchRespHandler();

    m_SyncObj = new CMAPIIntSync();
    m_AsyncCall = false;

    return retVal;
}

void IWFConfigFetch::UpdateCurrentInstanceId(uint16_t newInstanceId)
{
    m_currentInstanceId = newInstanceId;
}

int IWFConfigFetch::GetSigtranLocalHostConfig(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::GetSigtranLocalHostConfig");
    m_SendSuccess = true;
    cout << ">IWFFetch::GetSigtranLocalHostConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfLocalHostsConfig localCfg;
    localCfg.set_operreqid(GET_LOCAL_HOST);
    m_CmgrIwfObj->FetchIwfLocalConfiguration(localCfg);
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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetSigtranLocalHostConfig(bool useCurrentInstanceId,
        IWFCfgResp *Resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">IWFFetch::GetIwfLocalConfig ");
    cout << ">IWFFetch::GetIwfLocalConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfLocalHostsConfig localCfg;
    localCfg.set_operreqid(GET_LOCAL_HOST);
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentInstanceId};
    Stub::IwfFetch cmgrIwfObj(dest,0);
    cmgrIwfObj.FetchIwfLocalConfiguration(localCfg);

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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetSigtranAssociationSetConfig(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::GetSigtranAssociationSetConfig");
    m_SendSuccess = true;
    cout << ">IWFFetch::GetSigtranAssociationSetConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfSigtranAssociationSetsConfig lAssocSet;
    lAssocSet.set_operreqid(GET_ASSOC_SET);
    m_CmgrIwfObj->FetchIwfAssociationSetConfiguration(lAssocSet);
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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetSigtranAssociationSetConfig(bool useCurrentInstanceId,
	IWFCfgResp *Resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">IWFFetch::GetSigtranAssociationSetConfig");
    cout << ">IWFFetch::GetSigtranAssociationSetConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfSigtranAssociationSetsConfig lAssocSet;
    lAssocSet.set_operreqid(GET_ASSOC_SET);
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentInstanceId};
    Stub::IwfFetch cmgrIwfObj(dest,0);
    cmgrIwfObj.FetchIwfAssociationSetConfiguration(lAssocSet);

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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetSigtranAssociationConfig(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::GetSigtranAssociationConfig");
    m_SendSuccess = true;
    cout << ">IWFFetch::GetSigtranAssociationConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfSigtranAssociationsConfig lAssociation;
    lAssociation.set_operreqid(GET_ASSOC);
    m_CmgrIwfObj->FetchIwfAssociationConfiguration(lAssociation);
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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetSigtranAssociationConfig(bool useCurrentInstanceId,
	IWFCfgResp *Resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">IWFFetch::GetSigtranAssociationConfig");
    cout << ">IWFFetch::GetSigtranAssociationConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfSigtranAssociationsConfig lAssociation;
    lAssociation.set_operreqid(GET_ASSOC);
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentInstanceId};
    Stub::IwfFetch cmgrIwfObj(dest,0);
    cmgrIwfObj.FetchIwfAssociationConfiguration(lAssociation);

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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetSigtranRemoteRouteConfig(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::GetSigtranRemoteRouteConfig");
    m_SendSuccess = true;
    cout << ">IWFFetch::GetSigtranRemoteRouteConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfSigtranRemoteRoutesConfig lRemoteRoute;
    lRemoteRoute.set_operreqid(GET_REMOTE_ROUTE);
    m_CmgrIwfObj->FetchIwfRemoteRouteConfiguration(lRemoteRoute);
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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetSigtranRemoteRouteConfig(bool useCurrentInstanceId,
	IWFCfgResp *Resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">IWFFetch::GetSigtranRemoteRouteConfig");
    cout << ">IWFFetch::GetSigtranRemoteRouteConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfSigtranRemoteRoutesConfig lRemoteRoute;
    lRemoteRoute.set_operreqid(GET_REMOTE_ROUTE);
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentInstanceId};
    Stub::IwfFetch cmgrIwfObj(dest,0);
    cmgrIwfObj.FetchIwfRemoteRouteConfiguration(lRemoteRoute);

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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetIwfTranslatorRulesConfig(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::GetIwfTranslatorRulesConfig");
    m_SendSuccess = true;
    cout << ">IWFFetch::GetIwfTranslatorRulesConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfTranslatorRulesConfig lTransRule;
    lTransRule.set_operreqid(GET_TRANSLATOR_RULE);
    m_CmgrIwfObj->FetchIwfTranslatorRuleConfiguration(lTransRule);
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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetIwfTranslatorRulesConfig(bool useCurrentInstanceId,
	IWFCfgResp *Resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">IWFFetch::GetIwfTranslatorRulesConfig");
    cout << ">IWFFetch::GetIwfTranslatorRulesConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfTranslatorRulesConfig lTransRule;
    lTransRule.set_operreqid(GET_TRANSLATOR_RULE);
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentInstanceId};
    Stub::IwfFetch cmgrIwfObj(dest,0);
    cmgrIwfObj.FetchIwfTranslatorRuleConfiguration(lTransRule);

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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetIwfTranslationDataConfig(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::GetIwfTranslationDataConfig");
    m_SendSuccess = true;
    cout << ">IWFFetch::GetIwfTranslationDataConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfTranslationDataConfig lTransData;
    lTransData.set_operreqid(GET_ALL_TRANSLATOR_DATA);
    m_CmgrIwfObj->FetchIwfTranslationDataConfiguration(lTransData);
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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetIwfTranslationDataConfig(bool useCurrentInstanceId,
	IWFCfgResp *Resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">IWFFetch::GetIwfTranslationDataConfig");
    cout << ">IWFFetch::GetIwfTranslationDataConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfTranslationDataConfig lTransData;
    lTransData.set_operreqid(GET_ALL_TRANSLATOR_DATA);
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentInstanceId};
    Stub::IwfFetch cmgrIwfObj(dest,0);
    cmgrIwfObj.FetchIwfTranslationDataConfiguration(lTransData);

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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetIwfTimersConfig(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::GetIwfTimersConfig");
    m_SendSuccess = true;
    cout << ">IWFFetch::GetIwfTimersConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfTimersConfig lTimers;
    lTimers.set_operreqid(GET_ALL_IWF_TIMERS);
    m_CmgrIwfObj->FetchIwfTimersConfiguration(lTimers);
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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetIwfTimersConfig(bool useCurrentInstanceId,
	IWFCfgResp *Resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">IWFFetch::GetIwfTimersConfig");
    cout << ">IWFFetch::GetIwfTimersConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfTimersConfig lTimers;
    lTimers.set_operreqid(GET_ALL_IWF_TIMERS);
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentInstanceId};
    Stub::IwfFetch cmgrIwfObj(dest,0);
    cmgrIwfObj.FetchIwfTimersConfiguration(lTimers);

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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetIwfFeaturesConfig(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::GetIwfFeaturesConfig");
    m_SendSuccess = true;
    cout << ">IWFFetch::GetIwfFeaturesConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfFeaturesConfig lFeatures;
    lFeatures.set_operreqid(GET_ALL_IWF_FEATURES);
    m_CmgrIwfObj->FetchIwfFeaturesConfiguration(lFeatures);
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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetIwfFeaturesConfig(bool useCurrentInstanceId,
	IWFCfgResp *Resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">IWFFetch::GetIwfFeaturesConfig");
    cout << ">IWFFetch::GetIwfFeaturesConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfFeaturesConfig lFeatures;
    lFeatures.set_operreqid(GET_ALL_IWF_FEATURES);
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentInstanceId};
    Stub::IwfFetch cmgrIwfObj(dest,0);
    cmgrIwfObj.FetchIwfFeaturesConfiguration(lFeatures);

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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetIwfProtocolActionsConfig(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::GetIwfProtocolActionConfig");
    m_SendSuccess = true;
    cout << ">IWFFetch::GetIwfProtocolActionConfig" << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfProtocolActionsConfig lProtActionsConfig;
    lProtActionsConfig.set_operreqid(GET_ALL_IWF_PROT_ACTIONS_CONFIG);
    m_CmgrIwfObj->FetchIwfProtocolActionsConfiguration(lProtActionsConfig);
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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetIwfDccaConfig(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::GetIwfDccaConfig");
    m_SendSuccess = true;
    cout << ">IWFFetch::GetIwfDccaConfig" << endl;
    int retVal = CMAPI_SUCCESS;
    std::string ResponseString;
    IwfDccaConfig lDccaConfig;
    lDccaConfig.set_operreqid(GET_ALL_IWF_DCCA_CONFIG);
    m_CmgrIwfObj->FetchIwfDccaConfiguration(lDccaConfig);
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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetIwfDccaConfig(bool useCurrentInstanceId,
	IWFCfgResp *Resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">IWFFetch::GetIwfDccaConfig");
    cout << ">IWFFetch::GetIwfDccaConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    IwfDccaConfig lDccaConfig;
    lDccaConfig.set_operreqid(GET_ALL_IWF_DCCA_CONFIG);
    std::string ResponseString;
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentInstanceId};
    Stub::IwfFetch cmgrIwfObj(dest,0);
    cmgrIwfObj.FetchIwfDccaConfiguration(lDccaConfig);

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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

int IWFConfigFetch::GetIwfProtocolActionsConfig(bool useCurrentInstanceId,
	IWFCfgResp *Resp)
{
    m_SendSuccess = true;
    CLOG_DEBUG(">IWFFetch::GetIwfProtocolActionConfig");
    cout << ">IWFFetch::GetIwfProtocolConfig " << endl;
    int retVal = CMAPI_SUCCESS;
    IwfProtocolActionsConfig lProtActionsConfig;
    lProtActionsConfig.set_operreqid(GET_ALL_IWF_PROT_ACTIONS_CONFIG);
    std::string ResponseString;
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentInstanceId};
    Stub::IwfFetch cmgrIwfObj(dest,0);
    cmgrIwfObj.FetchIwfProtocolActionsConfiguration(lProtActionsConfig);

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
        retVal = Resp->respid();
        cout << " fetch resp received is" << Resp->DebugString() << endl;
    }
    else
    {
        retVal = CMAPI_ERROR;
        cout << " fetch error resp received " << endl;
    }
    return retVal;
}

/* ===========================================
 * CMGR response Callbacks for uration Fetch  
 * =========================================== 
 * */
int IWFConfigFetch::FetchIwfLocalConfigurationRespCbk(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::FetchIwfLocalConfigRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !Resp->IsInitialized() ||
            Resp->respid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchIwfLocal Callback : ERROR ");
        IWFCfgResp Response;
        Response.set_respid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        Resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int IWFConfigFetch::FetchIwfAssociationSetConfigurationRespCbk(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::FetchIwfAssociationSetConfigRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !Resp->IsInitialized() ||
            Resp->respid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchIwfAssociationSet Callback : ERROR ");
        IWFCfgResp Response;
        Response.set_respid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        Resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int IWFConfigFetch::FetchIwfAssociationConfigurationRespCbk(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::FetchIwfAssociationConfigRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !Resp->IsInitialized() ||
            Resp->respid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchIwfAssociation Callback : ERROR ");
        IWFCfgResp Response;
        Response.set_respid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        Resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int IWFConfigFetch::FetchIwfRemoteRouteConfigurationRespCbk(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::FetchIwfRemoteRouteConfigRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !Resp->IsInitialized() ||
            Resp->respid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchIwfRemoteRoute Callback : ERROR ");
        IWFCfgResp Response;
        Response.set_respid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        Resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int IWFConfigFetch::FetchIwfTranslatorRuleConfigurationRespCbk(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::FetchTranslatorRuleConfigurationRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !Resp->IsInitialized() ||
            Resp->respid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchTranslatorRule Callback : ERROR ");
        IWFCfgResp Response;
        Response.set_respid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        Resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int IWFConfigFetch::FetchIwfTranslationDataConfigurationRespCbk(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::FetchIwfTranslationDataConfigurationRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !Resp->IsInitialized() ||
            Resp->respid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchIwfTranslationData Callback : ERROR ");
        IWFCfgResp Response;
        Response.set_respid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        Resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int IWFConfigFetch::FetchIwfTimersConfigurationRespCbk(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::FetchIwfTimersConfigurationRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !Resp->IsInitialized() ||
            Resp->respid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchIwfTimers Callback : ERROR ");
        IWFCfgResp Response;
        Response.set_respid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        Resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int IWFConfigFetch::FetchIwfFeaturesConfigurationRespCbk(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::FetchIwfFeaturesConfigurationRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !Resp->IsInitialized() ||
            Resp->respid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchIwfFeatures Callback : ERROR ");
        IWFCfgResp Response;
        Response.set_respid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        Resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int IWFConfigFetch::FetchIwfDccaConfigurationRespCbk(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::FetchIwfDccaConfigurationRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !Resp->IsInitialized() ||
            Resp->respid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchIwfDccaConfig Callback : ERROR ");
        IWFCfgResp Response;
        Response.set_respid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        Resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}

int IWFConfigFetch::FetchIwfProtocolActionsConfigurationRespCbk(IWFCfgResp *Resp)
{
    CLOG_DEBUG(">IWFFetch::FetchIwfProtocolActionConfigurationRespCbk");
    std::string ResponseString;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !Resp->IsInitialized() ||
            Resp->respid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("FetchIwfProtocolActionConfig Callback : ERROR ");
        IWFCfgResp Response;
        Response.set_respid(CMAPI_MESSERROR);
        Response.SerializeToString(&ResponseString);
    }
    else
    {
        Resp->SerializeToString(&ResponseString);
    }

    m_SyncObj->Set(ResponseString);
    return 0;
}
