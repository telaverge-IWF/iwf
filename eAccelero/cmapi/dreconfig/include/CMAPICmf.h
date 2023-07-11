/* ********************************-*-H-*-************************************
 * *                                                                          *
 * *          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
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

#ifndef __CMAPICMF_H_
#define __CMAPICMF_H_


using namespace std;

#include <string.h>

#include "CMAPICommon.h"
#include "OverloadControl.h"

#include "CMgrCMFConfig_caller.h"
#include "CMFStats_caller.h"

class CMAPICMFConfig :  public Stub::CMgrCMFConfigRespCbk,
                        public DRECMfConfigResults,public Stub::CMFStatsRespCbk
{
public:
    CMAPICMFConfig() {}
    ~CMAPICMFConfig() {}

    int InitializeLibrary();

    // CMAPI Calls from CLI/GUI
    int GetCMFActionsAndTriggers(CMFActionTriggerReq& Req, CMFActionTriggerResp& Resp );
    int GetCMFLevels(CMFLevelReq& Req, CMFLevelResp& Resp);
    int GetCMFRules(string& RuleName, RuleConfigResp& Resp);
    int AddCMFRule(RuleConfigReq& Req, RuleConfigResp& Resp);
    int ModifyCMFRule(RuleConfigReq& Req, RuleConfigResp& Resp);
    int DeleteCMFRule(string& RuleName, RuleConfigResp& Resp);
    int SetCMFRuleStatus(RuleConfigReq& Req, RuleConfigResp& Resp);
    int SetCommandCodePriority(CCPriority& Req, PriorityConfigResp& Resp);
    int SetApplicationIdPriority(AppIdPriority& Req, PriorityConfigResp& Resp);
    int GetCMFActions(string& ActionName, RuleConfigResp& Resp);
    int GetCMFTriggers(string& TriggerName, RuleConfigResp& Resp);
    int GetCMFPriorityConfig(PriorityConfigReq& Req, PriorityConfigResp& Resp);
    int SetPriorityConfig(PriorityConfigReq& Req, PriorityConfigResp& Resp);
    int ModifyPriorityConfig(PriorityConfigReq& Req, PriorityConfigResp& Resp);
    int DeletePriorityConfig(PriorityConfigReq& Req, PriorityConfigResp& Resp);
    int AddPriorityConfig(PriorityConfigReq& Req, PriorityConfigResp& Resp);

    int GetSystemTriggerStates (TriggerStateRequest& Req, TriggerStateResponse& Resp);
    int GetDiaPeerTriggerStates(std::string peerName,std::string RealmName, PeerTriggerStateResponse& Resp);
    int GetDiaRealmTriggerStates(std::string realmName, RealmTriggerStateResponse& Resp);
    int GetCMFLevelConfig(uint32_t  triggerID, CMFLevelConfigResponse& Resp);



    //Response Callback
    int HandleSetTemplateConfigReqsRespCbk(TemplateResp *Resp);
    int HandleGetTemplateConfigReqsRespCbk(TemplateResp *Resp);
    int HandleSetRuleConfigRespCbk(RuleConfigResp *Resp);
    int HandleDeleteRuleConfigRespCbk(RuleConfigResp *Resp);
    int HandleSetPriorityConfigRespCbk(PriorityConfigResp *Resp);
    int FetchCMFRuleConfigurationRespCbk(RuleConfigResp *Resp);
    int FetchCMFPriorityConfigurationRespCbk(PriorityConfigResp *Resp);
    int FetchAllCMFTriggersRespCbk(CMFTriggerResp *Resp);
    int FetchAllCMFActionsRespCbk(CMFActionResp *Resp);
    int FetchAllCMFLevelsRespCbk(CMFLevelResp *Resp);
    int FetchCMFActionsForTriggerRespCbk(CMFActionTriggerResp *Resp);
    int SendCMFRuleConfigResult(RuleConfigResp *Req, CMAPIRes *Resp);
    int SendCMFPriorityConfigResult(PriorityConfigResp*, CMAPIRes*);
    int SendDreTemplateConfigResult(TemplateResp*, CMAPIRes*);

    int FetchCMFSystemTriggerStatesRespCbk(TriggerStateResponse *Resp);

    int FetchCMFDiaPeerTriggerStatesRespCbk(PeerTriggerStateResponse *Resp);

    int FetchCMFDiaRealmTriggerStatesRespCbk(RealmTriggerStateResponse *Resp);

    int FetchCMFLevelConfigRespCbk(CMFLevelConfigResponse *Resp);


private:

    Stub::CMgrCMFConfig  *m_CMgrCMFCallerObj;
    Stub::CMFStats  *m_cmfStatsObj;
    CMAPIIntSync         *m_CMAPIResponse;

    static const unsigned int m_waitTime = 32000000;
    ErrorDetails m_lastError;
    volatile bool m_SendSuccess;
};

#endif  //CMAPICMF_H

