/* ********************************-*-H-*-************************************
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


#ifndef _CMAPICOMP_H_
#define _CMAPICOMP_H_

#include "CmgrComponents_caller.h"
#include "DreErlbf_caller.h"
#include "ErlbfStats_caller.h"
#include "Compo.h"
#include "LoggingConf_caller.h"
#include "DreASF_caller.h"

// Common Management (CMAPI) Class for Component Configurations.
class CMApiComponents : public Stub::CmgrComponentsRespCbk, public Stub::ErlbfStatsRespCbk,
    public CompConfigResults, public Stub::LoggingConfRespCbk, public Stub::DreASFRespCbk
{
    public:

        CMApiComponents() {}
        ~CMApiComponents() {}

        // Library API for ERLBF Component Configuration
        int CreatePeerGroup(LBPeerGroups& Req,LBPeerGroupResp* Response);
        int ModifyPeerGroup(LBPeerGroups& Req,LBPeerGroupResp* Response);
        int DeletePeerGroup(std::string PeerGroupName,LBPeerGroupResp* Response);
        int GetPeerGroup(LBPeerGroups& Req, LBPeerGroups& Resp,ErrorDetails& err);
        int SetLoadBalancingAlgorithm(std::string PeerGroupName, std::string LBAlgo,LBPeerGroupResp* Response);
        int GetLoadBalancingAlgorithm(std::string PeerGroupName, std::string& AlgoType ,ErrorDetails& err);
        int SetPCRFBinding(std::string PeerGroupName, bool Enable,LBPeerGroupResp* Response);
        bool IsPCRFBindingEnabled(std::string PeerGroupName,ErrorDetails& err);
        int AddPeerToPeerGroup(std::string PeerGroupName, LBPeer& Req,LBPeerGroupResp* Response);
        int RemovePeerFromPeerGroup(std::string PeerGroupName, std::string LBPeerName, std::string RealmName,LBPeerGroupResp* Response);
        int ModifyPeerConfig(std::string PeerGroupName, LBPeer& Req,LBPeerGroupResp* Response);

        // Deffered Implementation - Start.
        int EnableERLFBF(bool Enable);
        bool IsERLBFEnabled();
        int SetPeerWeightage(std::string LBPeerName, int Weight){ return 0;}
        int GetPeerWeightage(std::string LBPeerName, int& Weightage){ return 0;}
        int SetPeerPriority(std::string LBPeerName, int Priority){ return 0;}
        int GetPeerPriority(std::string LBPeerName, int& Priority){ return 0;}
        // Deferred Implementation - End.

        int GetLBAlgorithmSchemes(LBAlgorithm_SuppComponentID CompID, LBAlgorithms& Resp,ErrorDetails& err);
        int AddLBAlgorithmSchemes(LBAlgorithm& Req,LBPeerGroupResp* Response);
        int DeleteLBAlgorithmSchemes(std::string LBAlgo,LBPeerGroupResp* Response);
        int ModifyLBAlgorithmSchemes(LBAlgorithm& Req,LBPeerGroupResp* Response);

        // ERLBF Related Callbacks
        int CMgrSetLBPeerConfigsRespCbk(LBPeerGroupResp *Resp);
        int CMgrGetLBPeerConfigsRespCbk(LBPeerGroupResp *Resp);


        // Library API for ERLBF Component Statistics
        int GetPeerGroupStats(ERLBFPeerGroupStatsReq &Req,ERLBFPeerGroupStatsResp &resp);
        int GetSessionBindingStats(SessionBindingStatsReq &Req,SessionBindingStatsRsp &resp);
        int ResetSessionBindingStats(SessionBindingStatsRsp &resp);
        int ResetPeerGroupStats(ERLBFResetPeerGroupStatsReq &Req,ERLBFResetPeerGroupStatsResp &resp);

        //ERLBF Stats related Callbacks
        int FetchERLBFPeerGroupStatsRespCbk(ERLBFPeerGroupStatsResp *Resp);
        int FetchSessionBindingStatsRespCbk(SessionBindingStatsRsp *Resp);
        int ResetERLBFPeerGroupStatsRespCbk(ERLBFResetPeerGroupStatsResp *Resp);

        int InitializeLibrary();

        // DTF Related API
        int LoadDictionary(std::string DictionaryName);
        int UnLoadDictionary(std::string DictionaryName);
        int ShowDictionary(std::string DictionaryName, Dictionary& dictionary);
        int LoadTransformPlugin(std::string PluginName, std::string FromDictionary,
                std::string ToDictionary, std::string ConfigFileName);
        int UnLoadTransformPlugin(std::string PluginName);
        int ShowTransformPlugin(std::string PluginName, TransformPlugin& plugin);
        int CMgrDTFConfigRespCbk(DynDictionaryResponse *Resp);

        // CMAPI Results Interface Methods
        int SendPeerGrpConfigResult(LBPeerGroupResp *Resp,CMAPIRes *result);
        int SendDTFConfigResult(DynDictionaryResponse *Resp,CMAPIRes *result);
        int SendLogConfigResult(LoggerConfResp *Resp, CMAPIRes *result);
        int SendASFConfigResult(ASFConfigResp *Resp, CMAPIRes *result);

        //Library API for Components Loggging configuration
        int GetLogConfig(std::string& CompName, LoggerInfo& LogInfo,ErrorDetails& err);
        int GetLogConfig(std::string& CompName,bool useCurrentInstanceId, LoggerInfo& LogInfo,ErrorDetails& err);
        int SetLogConfig(LoggerInfo& LogInfo,LoggerConfResp* resp);
        int SetLogChannel(std::string& CompName, LoggerConf_LogChannel Channel,LoggerConfResp* resp);
        int SetLogLevel(std::string& CompName, LoggerConf_LogLevel  Level,LoggerConfResp* resp);

        //Components Logging related Callbacks
        int GetComponentLoggingConfRespCbk(LoggerConfResp *Resp);
        int SetComponentLoggingConfRespCbk(LoggerConfResp *Resp);

        // ASF related Methods
        //
        int GetASFConfigurationRespCbk(ASFConfigResp *Resp);
        int SetASFConfigurationRespCbk(ASFConfigResp *Resp);

        int AddASGroup(ASGroupsCfg& ASGroupInfo);
        int ModifyASGroup(ASGroupsCfg& ASGroupInfo);
        int RemoveASGroup(ASGroupsCfg& ASGroupInfo);
        int GetASGroupConfig(ASGroupsCfg& ASGroupInfo);
        int SetASFAppResponseTimeout(int AppRespTimeout);
        int GetASFAppResponseTimeout(int& AppRespTimeout);
        int SetASGroupPriority(std::string ASGroupName, int Priority);
        int SetASGroupToHostedType(std::string ASGroupName);
        int SetASGroupToExternalType(std::string ASGroupName);
        int SetASGroupMaxInstances(std::string ASGroupName, int MaxInstances);
        int SetASGroupLBAlgorithm(std::string ASGroupName, LBAlgorithm& LBAlgo);
        int GetLastCallErrorDetails(ErrorDetails& Err);


        void UpdateCurrentInstanceId(uint16_t newInstanceId);


        //New Modified

        int ModifyASGroup(ASGroupsCfg& ASGroupCfgInfo, ErrorDetails& err);
        int RemoveASGroup(ASGroupsCfg& ASGroupCfgInfo, ErrorDetails& err);
        int GetASGroupConfig(ASGroupsCfg& ASGroupCfgInfo, ErrorDetails& err);
        int SetASFAppResponseTimeout(int AppRespTimeout, ErrorDetails& err);
        int GetASFAppResponseTimeout(int& AppRespTimeout, ErrorDetails& err);
        int SetASGroupPriority(std::string ASGroupName, int Priority, ErrorDetails& err);
        int SetASGroupToHostedType(std::string ASGroupName, ErrorDetails& err);
        int SetASGroupToExternalType(std::string ASGroupCfgName, ErrorDetails& err);
        int SetASGroupMaxInstances(std::string ASGroupName, int MaxInstances, ErrorDetails& err);
        int SetASGroupLBAlgorithm(std::string ASGroupCfgName, LBAlgorithm& LBAlgo, ErrorDetails& err);
        int AddASGroup(ASGroupsCfg& ASGroupCfgInfo, ErrorDetails& err);

    private:

        static const unsigned int m_waitTime = 32000000;   // Just over MeSS timeout
        std::string m_ErrCondVarTimeoutStr; //

        // Methods
        void CopyPeerGroups(LBPeerGroups *To, LBPeerGroupResp *From);
        void CopyPeerGroups(LBPeerGroupResp *To, LBPeerGroups *From);
        void CopyPeerGroups(LBPeerGroups *To, LBPeerGroupReq *From);
        void CopyPeerGroups(LBPeerGroupReq *To, LBPeerGroups *From);
        int SendCMgrRequest(LBPeerGroupReq& Request, bool GetReq, LBPeerGroupResp *Response = NULL);

        int SendErlbfRequest(ERLBFPeerGroupStatsReq& Request,ERLBFPeerGroupStatsResp *resp);
        int SendErlbfRequest(SessionBindingStatsReq&, SessionBindingStatsRsp *resp);
        int SendErlbfRequest(ERLBFResetPeerGroupStatsReq& Request,ERLBFResetPeerGroupStatsResp *resp);
        int IsResponseOK(LBPeerGroupResp *Resp);
        int IsResponseOK(ERLBFPeerGroupStatsResp *Resp);
        int IsResponseOK(SessionBindingStatsRsp*Resp);
        int IsResponseOK(LoggerConfResp *Resp);
        int IsResponseOK(ERLBFResetPeerGroupStatsResp *Resp);

        // DTF Related API
        int SendCMgrRequest(DynDictionaryRequest& Req, DynDictionaryResponse *Resp = NULL);
        int IsResponseOK(DynDictionaryResponse *Resp);

        // ASF Related Methods
        int SendCMgrRequest(ASFConfigReq& Req, ASFConfigResp *Resp, bool GetReq = false);


        // Caller Handlers.
        Stub::CmgrComponents* m_CmgrObj;
        Stub::ErlbfStats* m_ErlbfStatsObj;

        // DTF Sync Object
        CMAPIIntSync *m_CMgrResponse;

        // ASF related attibutes
        ErrorDetails m_cErr;

        // Send Status
        volatile bool m_SendSuccess;

        //Current Instance Id of dest
        uint16_t m_currentIntanceId;
};


#endif  //_CMAPICOMP_H_
