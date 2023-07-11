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

#ifndef __CMAPIIWFCONFIG_H_
#define __CMAPIIWFCONFIG_H_

#include "CMAPICommon.h"
#include "IwfErrorResp.h"
#include "Compo.h"
#include "dia_mgmt.h"
#include "iwfconfig.h"
#include "iwf_fsm.h"
#include "iwf_config.h"
#include "iwf_prot_translator.h"
#include "iwf_transaction_manager.h"
#include "iwf_prot_defines.h"

#define VOICE_NO_EVNT     "VOICE_NO_ANSWER_TIMER"
#define SMS_NO_EVNT       "SMS_NO_EVENT_TIMER"
#define NO_ACR            "NETWORK_DELAY_TIMER"
#define NO_ACTIVITY       "NO_ACTIVITY_TIMER"
#define AT_RETRY_COUNT    "ACTIVITY_RETRY_COUNT"
#define AT_RESPONSE_TIMEOUT "ACTIVITY_RESPONSE_TIMEOUT"

#define TX_TIMEOUT_STR     "TX_TIMEOUT"
#define INITIAL_ACTION_STR "INITIAL_ACTION"
#define UPDATE_ACTION_STR  "UPDATE_ACTION"

#define MAX_IP_ADDRS 5 /* maximum ip allowed include 4 secondary ip's*/

class CMAPIIwfConfig : public IwfSigtranMethods, public LoggingConf
{
    public:
        CMAPIIwfConfig();
        ~CMAPIIwfConfig();

        int HandleLocalHostConfigReqs(IwfLocalHostsConfig *req,IWFCfgResp *resp);
        int HandleDestinationConfigReqs(IwfSigtranDestinationsConfig *req,IWFCfgResp *resp);
        int HandleAssociationSetConfigReqs(IwfSigtranAssociationSetsConfig *req,IWFCfgResp *resp);
        int HandleAssociationConfigReqs(IwfSigtranAssociationsConfig *req,IWFCfgResp *resp);
        int HandleRemoteRouteConfigReqs(IwfSigtranRemoteRoutesConfig *req,IWFCfgResp *resp);
        int HandleTranslatorRuleConfigReqs(IwfTranslatorRulesConfig *req,IWFCfgResp *resp);
        int HandleTranslationDataConfigReqs(IwfTranslationDataConfig *req,IWFCfgResp *resp);
        int HandleTimersConfigReqs(IwfTimersConfig *req,IWFCfgResp *resp);
        int HandleFeaturesConfigReqs(IwfFeaturesConfig *req,IWFCfgResp *resp);
        int HandleUalManagerConfigReqs(IwfSigtranUalManagerConfig* req, IWFCfgResp* resp);
        int HandleIwfDccaGenConfigReqs(IwfDccaGenConfig* req, IWFCfgResp* resp);
        int HandleIwfDccaDestConfigReqs(IwfDccaDestsConfig* req, IWFCfgResp* resp);
        int HandleIwfProtocolActionsConfigReqs(IwfProtocolActionsConfig*, IWFCfgResp*);
        // Logging Configuration Server Method
        int SetComponentLoggingConf(LoggerConfReq *Req, LoggerConfResp *Resp);

    private: // Methods
        // LocalHostRelated Methods
        int ModifyLocalHost(IwfLocalHostConfig localhost);
        int SetLocalHost(IwfLocalHostConfig localhost);
        //bool IsSameLocalHost(std::string lhost);

        // associationSet related methods
        int SetAssociationSet(IwfSigtranAssociationSetConfig associationSet);
        int ModifyAssociationSet(IwfSigtranAssociationSetConfig associationSet);
        int DeleteAssociationSet(IwfSigtranAssociationSetConfig associationSet);

        // Association related methods
        int SetAssociationConfig(IwfSigtranAssociationConfig association);
        int ModifyAssociationConfig(IwfSigtranAssociationConfig association);
        int DeleteAssociationConfig(IwfSigtranAssociationConfig association);

        // RemoteRoute related methods
        int ModifyRemoteRoute(IwfSigtranRemoteRouteConfig remoteRouteConfig);
        int DeleteRemoteRoute(IwfSigtranRemoteRouteConfig remoteRouteConfig);

        //private:
        //  DiaMgmt *m_diaMgtObj;
};

#endif   //  __CMAPIIWFCONFIG_H_
