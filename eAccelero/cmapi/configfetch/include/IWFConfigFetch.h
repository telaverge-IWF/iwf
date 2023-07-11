
#ifndef _IWFCONFIGFETCH_H_
#define _IWFCONFIGFETCH_H_

#include "IwfFetch_caller.h"
#include "IwfConfigResults_caller.h"
#include "iwfconfig.h"
#include "CMAPICommon.h"

using namespace std;


// Common Management (CMAPI) Class to Fetch IWF specific Configurations.
// Will be updated as and when new configurations are added.
class IWFConfigFetch : public Stub::IwfFetchRespCbk
{
    public:

        IWFConfigFetch() {}
        ~IWFConfigFetch() {}

        int InitializeLibrary();
        int GetSigtranLocalHostConfig(IWFCfgResp *Resp);
        int GetSigtranAssociationSetConfig(IWFCfgResp *Resp);
        int GetSigtranAssociationConfig(IWFCfgResp *Resp);
        int GetSigtranRemoteRouteConfig(IWFCfgResp *Resp);
        int GetIwfTranslatorRulesConfig(IWFCfgResp *Resp);
        int GetIwfTranslationDataConfig(IWFCfgResp *Resp);
        int GetIwfTimersConfig(IWFCfgResp *Resp);
        int GetIwfFeaturesConfig(IWFCfgResp *Resp);
        int GetIwfDccaConfig(IWFCfgResp *Resp);
        int GetIwfProtocolActionsConfig(IWFCfgResp *Resp);

        //Overloaded Methods to use current Instance Id instead of 0.
        int GetSigtranLocalHostConfig(bool useCurrentInstanceId, IWFCfgResp *resp);
        int GetSigtranAssociationSetConfig(bool useCurrentInstanceId, IWFCfgResp *Resp);
        int GetSigtranAssociationConfig(bool useCurrentInstanceId, IWFCfgResp *Resp);
        int GetSigtranRemoteRouteConfig(bool useCurrentInstanceId, IWFCfgResp *Resp);
        int GetIwfTranslatorRulesConfig(bool useCurrentInstanceId, IWFCfgResp *Resp);
        int GetIwfTranslationDataConfig(bool useCurrentInstanceId, IWFCfgResp *Resp);
        int GetIwfTimersConfig(bool useCurrentInstanceId, IWFCfgResp *Resp);
        int GetIwfFeaturesConfig(bool useCurrentInstanceId, IWFCfgResp *Resp);
        int GetIwfDccaConfig(bool useCurrentInstanceId, IWFCfgResp *Resp);
        int GetIwfProtocolActionsConfig(bool useCurrentInstanceId, IWFCfgResp *Resp);


        int FetchIwfLocalConfigurationRespCbk(IWFCfgResp *Resp);
        int FetchIwfAssociationSetConfigurationRespCbk(IWFCfgResp *Resp);
        int FetchIwfAssociationConfigurationRespCbk(IWFCfgResp *Resp);
        int FetchIwfRemoteRouteConfigurationRespCbk(IWFCfgResp *Resp);
        int FetchIwfTranslatorRuleConfigurationRespCbk(IWFCfgResp *Resp);
        int FetchIwfTranslationDataConfigurationRespCbk(IWFCfgResp *Resp);
        int FetchIwfTimersConfigurationRespCbk(IWFCfgResp* Resp);
        int FetchIwfFeaturesConfigurationRespCbk(IWFCfgResp* Resp);
        int FetchIwfDccaConfigurationRespCbk(IWFCfgResp* Resp);
        int FetchIwfProtocolActionsConfigurationRespCbk(IWFCfgResp* Resp);
        void UpdateCurrentInstanceId(uint16_t newInstanceId);
    private:

        // Caller Handlers.
        Stub::IwfFetch*   m_CmgrIwfObj;
        CMAPIIntSync*     m_SyncObj;
        bool m_AsyncCall;
        uint16_t m_currentInstanceId;
        static const int m_waitCMAPI = 32000000;
        volatile bool m_SendSuccess;
};


#endif  //_IWFCONFIGFETCH_H_
