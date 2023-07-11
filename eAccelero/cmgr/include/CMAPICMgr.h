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

#ifndef __CMAPIMGR_H_
#define __CMAPIMGR_H_

#include <unordered_map>
#include "dreconfig.h"
#include "dreconfig_def.h"
#include "DiaMgtMethods_caller.h"
#include "DreErlbf_caller.h"
#include "DreDTF_caller.h"
#include "DreASF_caller.h"
#include "DREConfigResults_caller.h"
#include "CompConfigResults_caller.h"
#include "LoggingConf_caller.h"
#include <HA.h>
#include <HA_def.h>
#include "Compo.h"
#include "Compo_def.h"
#include "OverloadControl.h"
#include "OverloadControl_def.h"
#include <string.h>
#include "CMgrDbInterface.h"
//#include "CMgrCmfDbInterface.h"
#include "CMgrAlarms.h"
#include "CMgrLock.h"
#include "StaticRoutingTable.h"
#include "DiaMgtForStaticRoutingMethods_caller.h"
#include "DREStaticRoutingConfigResults_caller.h"
#include "DiaMgtTemplateMethods_caller.h"
#include "DiaMgmtCMFConfig_caller.h"
#include "DRECMfConfigResults_caller.h"
#include "DREConfigTemplateResults_caller.h"
#include "UserManagement.h"
#include "UserManagement_def.h"
#include "CMgrUserManagementMethods_caller.h"

class CMgrDbInterface;
//class CMgrCmfDbInterface;
class ConfigManager;
class CnfLockMgr;

struct CMgrCookie
{
    CMgrCookie(uint16_t comp, uint16_t iReqID, uint16_t activeNodeResponse, void* con,void* req=NULL):comp(comp), iReqID(iReqID), activeNodeResponse(activeNodeResponse), con(con), req(req){}
    uint16_t comp;
    uint16_t iReqID;
    uint16_t activeNodeResponse;
    void* con;
    void* req;
};

class CMAPICMgr :
    public CMgrMethods,
    public Stub::DiaMgtMethodsRespCbk,
    public Stub::DreErlbfRespCbk,
    public Stub::DreDTFRespCbk,
    public Stub::DREConfigResultsRespCbk,
    public Stub::CompConfigResultsRespCbk,
    public Stub::DREConfigTemplateResultsRespCbk,
    public Stub::DRECMfConfigResultsRespCbk,
    public Stub::LoggingConfRespCbk,
    public Stub::DreASFRespCbk,
    public DreFetch,
    public CmgrComponents,
    public FetchConfiguration,
    public CMgrHAInterface,
    public Stub::DREStaticRoutingConfigResultsRespCbk,
    public CMgrStaticRoutingTableMethods,
    public Stub::DiaMgtForStaticRoutingMethodsRespCbk,
    public DreStaticRoutingConfigFetch,
    public Stub::DiaMgtTemplateMethodsRespCbk,
    public Stub::DiaMgmtCMFConfigRespCbk,
    public CMgrCMFConfig,
    public CMgrTemplateMethods,
    public DreTemplateFetch,
    public CMgrUserManagementMethods,
    public CMFConfigFetch

{
    public:

        CMgrDbInterface *m_dbInterface;
        //CMgrCmfDbInterface *m_CmfDbInterface;
        ConfigManager *m_ConfigManager;
        CnfLockMgr *m_LockManager;
        Stub::DiaMgtMethods *m_diaMgtCallerObj;
        Stub::DiaMgtMethods *m_standbydiaMgtCallerObj;
        Stub::DiaMgtMethods *m_standbyiwfdiaMgtCallerObj;
        Stub::DiaMgtMethods *m_iwfdiaMgtCallerObj;
        Stub::DiaMgtTemplateMethods *m_diaMgtTemplateCallerObj;
        Stub::DiaMgtTemplateMethods *m_standbydiaMgtTemplateCallerObj;
        Stub::DiaMgmtCMFConfig *m_diaMgmtCmfCallerObj;
        Stub::DiaMgmtCMFConfig *m_standbydiaMgmtCmfCallerObj;
        Stub::DreErlbf      *m_erlbfCallerObj;
        Stub::DreErlbf      *m_standbyerlbfCallerObj;
        Stub::LoggingConf   *m_loggingCallerObj;
        Stub::LoggingConf   *m_iwfloggingCallerObj;
        Stub::LoggingConf   *m_standbyiwfloggingCallerObj;
        Stub::LoggingConf   *m_standbyloggingCallerObj;
        Stub::DreASF        *m_asfCallerObj;
        Stub::DreASF        *m_standbyasfCallerObj;
        Stub::DiaMgtForStaticRoutingMethods *m_staticRoutingCallerObj;
        Stub::DiaMgtForStaticRoutingMethods *m_standbystaticRoutingCallerObj;

        Stub::LoggingConf   *m_loggingAvlCallerObj;
        Stub::LoggingConf   *m_loggingStandbyAvlCallerObj;

        std::unordered_map<uint16_t, Stub::DREConfigResults*>  m_configResultsHandler;
        std::unordered_map<uint16_t, Stub::CompConfigResults*> m_compResultsHandler;
        std::unordered_map<uint16_t, Stub::DREConfigTemplateResults*> m_templateResultsHandler;
        std::unordered_map<uint16_t, Stub::DREStaticRoutingConfigResults*> m_staticConfigResultsHandler;
        std::unordered_map<uint16_t, Stub::DRECMfConfigResults*> m_cmfConfigResultsHandler;
        std::string m_dbHostname;
        CMAPICMgr(std::string sHostName,std::string sUserName,std::string sPassword,std::string sDataBase, uint16_t instanceId,ConfigManagerAlarms *pConfigManagerAlarms,ConfigManager *pConfigManager);
        ~CMAPICMgr();

        DbStatus_e Set_Log_Configuration(LoggerConfReq *req,LoggerConfResp *resp);

        int CMgrGetLBPeerConfigs(LBPeerGroupReq *Req,LBPeerGroupResp *Resp);
        int CMgrSetLBPeerConfigs(LBPeerGroupReq *Req,LBPeerGroupResp *Resp);
        int CMgrDTFConfig(DynDictionaryRequest *Req,DynDictionaryResponse *Resp);
        int CMgrAMSetConfiguration(AvaMgrConfig *Request,AvaMgrConfigResp *Response);
        int CMgrRMSetConfiguration(RepMgrConfig *Request,RepMgrConfigResp *Response);
        int CMgrDreSetConfiguration(DreHAConfig *Request,DreHAConfigResp *Response);
        int FetchAvaMgrConfiguration(AvaMgrConfig *Request,AvaMgrConfigResp *Response);
        int FetchRepMgrConfiguration(RepMgrConfig *Request,RepMgrConfigResp *Response);
        int FetchDreHAConfiguration(DreHAConfig *Request,DreHAConfigResp *Response);
        int FetchDreConfiguration(PeersConfig *req,DRECfgResp *resp);
        int FetchDictionaryConfig(DictionaryConfigReq *Req,DRECfgResp *Resp);
        int FetchPluginConfig(TransformPluginConfigReq *Req,DRECfgResp *Resp);
        int FetchLoggerConfiguration(LoggerConfReq *req, LoggerConfResp *Resp);
        int FetchErlbfConfiguration(LBPeerGroupReq *Req,LBPeerGroupResp *Resp);
        int FetchDTFConfiguration(DynDictionaryRequest *Req,DynDictionaryResponse *Resp);
        int FetchTraceConfiguration(TraceReq *req, TraceResp *resp);
        int FetchStackConfiguration(StackConfigRequest*, StackConfigResponse*);
        int FetchStaticRoutingTableConfiguration(StaticRoutingTableConfigReq *req,StaticRoutingTableConfigResp *Resp);
        int FetchDreTemplateConfiguration(TemplateReq *req, TemplateResp *resp);

        int GetASFConfiguration(ASFConfigReq *Req, ASFConfigResp *Resp);
        int SetASFConfiguration(ASFConfigReq* Req, ASFConfigResp* Resp);
        int FetchASFConfiguration(ASFConfigReq *Req, ASFConfigResp *Resp);
        int GetComponentLoggingConf(LoggerConfReq *req, LoggerConfResp *resp);
        int SetComponentLoggingConf(LoggerConfReq *req, LoggerConfResp *resp);
        int GetUserConfig(UserReq *req, UserResp *resp);
        int SetUserConfig(UserReq *req, UserResp *resp);
        int GetTHFConfig(THFReq *req, THFResp *resp);
        int SetTHFConfig(THFReq *req, THFResp *resp);
        int FetchTHFConfig(THFReq*, THFResp*);

        int GetSDTFConfig(SDTFReq *req, SDTFResp *resp);
        int SetSDTFConfig(SDTFReq *req, SDTFResp *resp);
        int FetchSDTFConfig(SDTFReq *req, SDTFResp *resp);

        // Usermanagement Methods
        int HandleSetUserConfigReqs(UserDetailReq *req, UserDetailResp *resp);
        int HandleGetUserConfigReqs(UserDetailReq *req, UserDetailResp *resp);
        int HandleSetEmailContentReqs(EmailContentReq *req, EmailContentResp *resp);
        int HandleGetEmailContentReqs(EmailContentReq *req, EmailContentResp *resp);
        int HandleSetEmailServerReqs(EmailServerReq *req, EmailServerResp *resp);
        int HandleGetEmailServerReqs(EmailServerReq *req, EmailServerResp *resp);


        int HandleGetLocalHostConfigReqs(LocalHostConfig *req,DRECfgResp *resp);
        int HandleSetLocalHostConfigReqs(LocalHostConfig *req,DRECfgResp *resp);
        int HandleGetLocalTransportTags(LocalTransportTagRequest *, LocalTransportTagResponse*);
        int HandleGetPeerConfigReqs(PeersConfig *req,DRECfgResp *resp);
        int HandleGetPeerStatesReqs(PeersConfig *req,DRECfgResp *resp);
        int HandleSetPeerConfigReqs(PeersConfig *req,DRECfgResp *resp);
        int HandleDelPeerConfigReqs(PeersConfig *req,DRECfgResp *resp);
        int HandleGetRealmConfigReqs(RealmsConfig *req,DRECfgResp *resp);
        int HandleSetRealmConfigReqs(RealmsConfig *req,DRECfgResp *resp);
        int HandleDelRealmConfigReqs(RealmsConfig *req,DRECfgResp *resp);
        int HandleGetTraceConfigReqs(TraceReq *req, TraceResp *resp);
        int HandleSetTraceConfigReqs(TraceReq *req, TraceResp *resp);
        int HandleGetStackConfiguration(StackConfigRequest*, StackConfigResponse*);
        int HandleSetStackConfiguration(StackConfigRequest*, StackConfigResponse*);
        int HandleGetStaticRoutingTableConfigReqs(StaticRoutingTableConfigReq*, StaticRoutingTableConfigResp*);
        int HandleSetStaticRoutingTableConfigReqs(StaticRoutingTableConfigReq*, StaticRoutingTableConfigResp*);

        //DTF: Dict and plugin
        int HandleGetDictionaryConfigReq(DictionaryConfigReq* req, DRECfgResp* resp);
        int HandleGetPluginConfigReq(TransformPluginConfigReq *req, DRECfgResp *resp);
        int HandleSetDictionaryConfigReq(DictionaryConfigReq* req, DRECfgResp* resp);
        int HandleSetPluginConfigReq(TransformPluginConfigReq *req, DRECfgResp *resp);

        //CMF: Congestion management
        int HandleGetTemplateConfigReqs(TemplateReq *req, TemplateResp *resp);
        int HandleSetTemplateConfigReqs(TemplateReq *req, TemplateResp *resp);
        int HandleSetRuleConfig(RuleConfigReq *Req, RuleConfigResp *Resp);
        int HandleDeleteRuleConfig(RuleConfigReq *Req, RuleConfigResp *Resp);
        int HandleSetPriorityConfig(PriorityConfigReq *Req, PriorityConfigResp *Resp);
        int FetchCMFRuleConfiguration(RuleConfigReq *Req, RuleConfigResp *Resp);
        int FetchCMFPriorityConfiguration(PriorityConfigReq *Req, PriorityConfigResp *Resp);
        int FetchAllCMFTriggers(CMFTriggerReq *Req, CMFTriggerResp *Resp);
        int FetchAllCMFActions(CMFActionReq *Req, CMFActionResp *Resp);
        int FetchAllCMFLevels(CMFLevelReq *Req, CMFLevelResp *Resp);
        int FetchCMFActionsForTrigger(CMFActionTriggerReq *Req, CMFActionTriggerResp *Resp);
        int FetchCMFTemlateConfig(TemplateReq *Req, TemplateResp *Resp);
        int FetchCMFConfig(CMFConfigReq *Req, CMFConfigResp *Resp);
        // Callbacks
        int HandleDreSetRuleConfigRespCbk(RuleConfigResp *Resp);
        int HandleDreSetCMFPriorityConfigRespCbk(PriorityConfigResp *Resp);
        int FetchCMFSystemTriggerStatesRespCbk(TriggerStateResponse* resp);
        int FetchCMFDiaPeerTriggerStatesRespCbk(PeerTriggerStateResponse *resp);
        int FetchCMFDiaRealmTriggerStatesRespCbk(RealmTriggerStateResponse* resp);
        int FetchCMFLevelConfigRespCbk(CMFLevelConfigResponse *resp);
        // Callbacks for DRE Implementation Methods
        int HandleLocalHostConfigReqsRespCbk(DRECfgResp *resp);
        int HandleDreSetPeerConfigReqsRespCbk(DRECfgResp *resp);
        int HandleDreDelPeerConfigReqsRespCbk(DRECfgResp *resp);
        int HandleDreSetRealmConfigReqsRespCbk(DRECfgResp *resp);
        int HandleDreDelRealmConfigReqsRespCbk(DRECfgResp *resp);
        int HandleTraceConfigReqsRespCbk(TraceResp *resp);
        int HandleStaticRoutingTableConfigReqsRespCbk(StaticRoutingTableConfigResp *resp);
        int HandleTHFConfigRespCbk(THFResp *resp);
        int HandleDreSetTemplateConfigReqsRespCbk(TemplateResp *resp);
        int HandlePluginConfigRespCbk(DRECfgResp* resp);
        int HandleDictionaryConfigRespCbk(DRECfgResp* resp);
        //int HandleSetDictionaryConfigRespCbk(DRECfgResp *resp);
        //int HandleSetPluginConfigRespCbk(DRECfgResp *resp);
        int HandleSDTFConfigRespCbk(SDTFResp *resp);


        int SendDREConfigResultRespCbk(CMAPIRes *Resp);
        int SendTHFConfigResultRespCbk(CMAPIRes *Resp);
        int SendPeerGrpConfigResultRespCbk(CMAPIRes *Resp);
        int SendDTFConfigResultRespCbk(CMAPIRes *Resp);
        int SendLogConfigResultRespCbk(CMAPIRes *Resp);
        int SetComponentLoggingConfRespCbk(LoggerConfResp *resp);
        int SendTraceConfigResultRespCbk(CMAPIRes *Resp);
        int SendASFConfigResultRespCbk(CMAPIRes *Resp);
        int SetASFConfigurationRespCbk(ASFConfigResp *Resp);
        int SendStaticRoutingTableConfigResultRespCbk(CMAPIRes *Resp);
        int SendDreTemplateConfigResultRespCbk(CMAPIRes *Resp);
        int SendCMFPriorityConfigResultRespCbk(CMAPIRes *Resp);
        int SendCMFRuleConfigResultRespCbk(CMAPIRes *Resp);
        int SendSDTFConfigResultRespCbk(CMAPIRes *Resp);
        // Response call backs for DTF call backs
        int DreDTFConfigRespCbk(DynDictionaryResponse *Resp);

        // Response call backs for ERLBF call backs
        int ErlbfSetLBPeerConfigsRespCbk(LBPeerGroupResp *Resp);


        DbStatus_e CheckforAvaMgr(LoggerConfReq *req,LoggerConfResp *resp);
        DbStatus_e CheckforWebAgentAndCli(LoggerConfReq *req,LoggerConfResp *resp);

        // Method to set new instance ID received from Availability manager
        int UpdateInstanceId(uint16_t instanceId);
        void deleteCookie(CMgrCookie *CookieReq,int iType);

    private:
        uint16_t m_instanceId;

};

#endif // __CMAPIMGR_H_
