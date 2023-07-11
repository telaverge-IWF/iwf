
#ifndef _CMAPICFG_H_
#define _CMAPICFG_H_

#include "DreFetch_caller.h"
#include "FetchConfiguration_caller.h"
#include "CMAPICommon.h"
#include "StaticRoutingTableConfigFetch_caller.h"
#include "DreStaticRoutingConfigFetch_caller.h"
#include "DreTemplateFetch_caller.h"
#include "CMFConfigFetch_caller.h"

using namespace std;

// Class interface for Async Operations

class FetchDataAsync {
    public:
        virtual int ErlbfConfiguration(LBPeerGroups *ConfigData) = 0;
};

// Common Management (CMAPI) Class  to Fetch Component Configurations.
// Will be updated as and when new component configurations are added.
//
class CMAPIConfig : public Stub::DreFetchRespCbk,
                    public Stub::DreTemplateFetchRespCbk,
                    public Stub::FetchConfigurationRespCbk,
                    public Stub::DreStaticRoutingConfigFetchRespCbk,
                    public Stub::CMFConfigFetchRespCbk

{
    public:

        CMAPIConfig() {}
        ~CMAPIConfig() {}

        int InitializeLibrary(FetchDataAsync *AsyncObj = NULL);
        int GetDreConfiguration(DRECfgResp *resp);
        int GetErlbfConfiguration(LBPeerGroups *Resp);
        int GetErlbfConfigurationAsync();
        int GetLoggerConfiguration(LoggerConfResp *Resp);
        int GetASFConfiguration(ASFConfigResp *Resp);
        int GetASFConfiguration(bool useCurrentInstanceId, ASFConfigResp *Resp);
        int GetStackConfiguration(StackConfigResponse *Resp);
        int GetTraceConfiguration(TraceResp *Resp);
        int GetStaticRoutingConfiguration(StaticRoutingTableConfigResp *Resp);
        int GetCMFConfiguration(TemplateResp *resp);
        int GetSDTFConfiguration(SDTFResp *resp);

        //Overloaded Methods to use current Instance Id instead of 0.
        int GetDreConfiguration(bool useCurrentInstanceId,
                DRECfgResp *resp);
        int GetLoggerConfiguration(bool useCurrentInstanceId,
                LoggerConfResp *Resp);
        int GetErlbfConfiguration(bool useCurrentInstanceId,
                LBPeerGroups *Resp);
        int GetTraceConfiguration(bool useCurrentInstanceId,
                TraceResp *Resp);
        int GetStaticRoutingConfiguration(bool useCurrentInstanceId,
                StaticRoutingTableConfigResp *Resp);
        int GetErlbfConfigurationAsync(bool useCurrentInstanceId);
        int GetStackConfiguration(bool useCurrentInstanceId,
                StackConfigResponse *Resp);
        int GetCMFConfiguration(bool useCurrentInstanceId,
                TemplateResp *resp);
        int GetDictionaryConfiguration(bool useCurrentInstanceId,
                DRECfgResp *Resp);
        int GetTransformPluginConfiguration(bool useCurrentInstanceId,
                DRECfgResp *resp);
        int GetSDTFConfiguration(bool useCurrentInstanceId,
                SDTFResp *resp);

        int FetchErlbfConfigurationRespCbk(LBPeerGroupResp *Resp);
        int FetchDreConfigurationRespCbk(DRECfgResp *resp);
        int FetchLoggerConfigurationRespCbk(LoggerConfResp *Resp);
        int FetchASFConfigurationRespCbk(ASFConfigResp *Resp);
        int FetchStackConfigurationRespCbk(StackConfigResponse *Resp);
        int FetchTraceConfigurationRespCbk(TraceResp *Resp);
        int FetchStaticRoutingTableConfigurationRespCbk(StaticRoutingTableConfigResp* resp);
        int FetchTHFConfigRespCbk(THFResp *resp);
        int FetchSDTFConfigRespCbk(SDTFResp *resp);

        //For Topology Hiding Feature
        int GetTopologyHidingFetureConfiguration(THFResp *Resp);
        int GetTopologyHidingFeatureConfiguration(bool useCurrentInstanceId,
                THFResp *Resp);

        // For DTF configurations
        int GetDTFConfiguration(DynDictionaryResponse *Resp);
        int GetDTFConfiguration(bool useCurrentInstanceId,
                DynDictionaryResponse *Resp);
        int FetchDTFConfigurationRespCbk(DynDictionaryResponse *Resp);
        int FetchDreTemplateConfigurationRespCbk(TemplateResp *resp);

        void UpdateCurrentInstanceId(uint16_t newInstanceId);
        //DTF : dict and trans plugin
        int GetDictionaryConfiguration(DRECfgResp *resp);
        int GetTransformPluginConfiguration(DRECfgResp *resp);
        int FetchDictionaryConfigRespCbk(DRECfgResp *resp);
        int FetchPluginConfigRespCbk(DRECfgResp *resp);

        //Congetion Management Config-fetch
        int GetCMFTemlateConfig(TemplateResp *Resp);
        int GetCMFConfig(bool useCurrentInstanceId,CMFConfigResp *Resp);
        int FetchCMFTemlateConfigRespCbk(TemplateResp *Resp);
        int FetchCMFConfigRespCbk(CMFConfigResp *Resp);
    private:

        // Caller Handlers.
        Stub::FetchConfiguration* m_CmgrCompoObj;
        Stub::DreFetch*   m_CmgrDreObj;
        Stub::DreTemplateFetch*   m_CmgrCMFObj;
        CMAPIIntSync*     m_SyncObj;
        Stub::DreStaticRoutingConfigFetch*   m_CmgrStaticRoutingObj;
        Stub::CMFConfigFetch*  m_CMgrCMFFetchObj;
        bool m_AsyncCall;
        FetchDataAsync *m_AsyncObjPtr;
        uint16_t m_currentIntanceId;
        static const int m_waitCMAPI = 32000000;
        volatile bool m_SendSuccess;
};


#endif  //_CMAPICFG_H_
