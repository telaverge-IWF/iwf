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

#ifndef __CMAPI_IWF_MGR_H_
#define __CMAPI_IWF_MGR_H_

#include <unordered_map>
#include <string.h>
#include "CMgrIwfDbInterface.h"
#include "CMgrAlarms.h"

#include "IwfConfigResults_caller.h"
#include "IwfSigtranMethods_caller.h"
#include "iwfconfig_def.h"
#include "iwfconfig.h"
#include "CMgrLock.h"

struct CMgrCookie;
class CMgrIwfDbInterface;
class ConfigManager;
class CnfLockMgr;

class CMAPIIwfCMgr :
            public IwfFetch,
            public CMgrIwfMethods,
            public Stub::IwfConfigResultsRespCbk,
            public Stub::IwfSigtranMethodsRespCbk
{
    public:

        CMgrIwfDbInterface *m_IwfdbInterface;
        ConfigManager *m_ConfigManager;
        CnfLockMgr *m_LockManager;
        Stub::IwfSigtranMethods *m_iwfSigtranMethods;
        Stub::IwfSigtranMethods *m_standbyiwfSigtranMethods;

        std::unordered_map<uint16_t, Stub::IwfConfigResults*>  m_configResultsHandler;
        std::string m_dbHostname;
        CMAPIIwfCMgr(std::string sHostName,std::string sUserName,std::string sPassword,std::string sDataBase, uint16_t instanceId,ConfigManagerAlarms *pConfigManagerAlarms,ConfigManager *pConfigManager);
        ~CMAPIIwfCMgr();

        int SendIWFConfigResultRespCbk(CMAPIRes*);
        int HandleLocalHostConfigReqsRespCbk(IWFCfgResp*);
        int HandleDestinationConfigReqsRespCbk(IWFCfgResp*);
        int HandleAssociationSetConfigReqsRespCbk(IWFCfgResp*);
        int HandleAssociationConfigReqsRespCbk(IWFCfgResp*);
        int HandleRemoteRouteConfigReqsRespCbk(IWFCfgResp*);
        int HandleTranslatorRuleConfigReqsRespCbk(IWFCfgResp*);
        int HandleTranslationDataConfigReqsRespCbk(IWFCfgResp*);
        int HandleTimersConfigReqsRespCbk(IWFCfgResp*);
        int HandleFeaturesConfigReqsRespCbk(IWFCfgResp*);
        int HandleIwfDccaGenConfigReqsRespCbk(IWFCfgResp*);
        int HandleIwfDccaDestConfigReqsRespCbk(IWFCfgResp*);
        int HandleUalManagerConfigReqsRespCbk(IWFCfgResp*);
        int HandleIwfProtocolActionsConfigReqsRespCbk(IWFCfgResp*);
        int HandleGetLocalHostConfigReqs(IwfLocalHostsConfig*, IWFCfgResp*);
        int HandleSetLocalHostConfigReqs(IwfLocalHostsConfig*, IWFCfgResp*);
        int HandleGetDestinationConfigReqs(IwfSigtranDestinationsConfig*, IWFCfgResp*);
        int HandleSetDestinationConfigReqs(IwfSigtranDestinationsConfig*, IWFCfgResp*);
        int HandleGetAssociationSetConfigReqs(IwfSigtranAssociationSetsConfig*, IWFCfgResp*);
        int HandleSetAssociationSetConfigReqs(IwfSigtranAssociationSetsConfig*, IWFCfgResp*);
        int HandleGetAssociationConfigReqs(IwfSigtranAssociationsConfig*, IWFCfgResp*);
        int HandleSetAssociationConfigReqs(IwfSigtranAssociationsConfig*, IWFCfgResp*);
        int HandleGetSctpEndPointConfigReqs(IwfSigtranSctpEndPointsConfig*, IWFCfgResp*);
        int HandleSetSctpEndPointConfigReqs(IwfSigtranSctpEndPointsConfig*, IWFCfgResp*);
        int HandleGetSctpProfileConfigReqs(IwfSigtranSctpProfilesConfig*, IWFCfgResp*);
        int HandleSetSctpProfileConfigReqs(IwfSigtranSctpProfilesConfig*, IWFCfgResp*);
        int HandleGetSigtranMultihomingConfigReqs(IwfSigtransMultihomingConfig*, IWFCfgResp*);
        int HandleSetSigtranMultihomingConfigReqs(IwfSigtransMultihomingConfig*, IWFCfgResp*);
        int HandleGetRemoteRouteConfigReqs(IwfSigtranRemoteRoutesConfig*, IWFCfgResp*);
        int HandleSetRemoteRouteConfigReqs(IwfSigtranRemoteRoutesConfig*, IWFCfgResp*);
        int HandleGetTranslatorRuleConfigReqs(IwfTranslatorRulesConfig*, IWFCfgResp*);
        int HandleSetTranslatorRuleConfigReqs(IwfTranslatorRulesConfig*, IWFCfgResp*);
        int HandleGetTranslationDataConfigReqs(IwfTranslationDataConfig*, IWFCfgResp*);
        int HandleSetTranslationDataConfigReqs(IwfTranslationDataConfig*, IWFCfgResp*);
        int HandleSetIwfTimersConfigReqs(IwfTimersConfig*, IWFCfgResp*);
        int HandleGetIwfTimersConfigReqs(IwfTimersConfig*, IWFCfgResp*);
        int HandleSetIwfFeaturesConfigReqs(IwfFeaturesConfig*, IWFCfgResp*);
        int HandleGetIwfFeaturesConfigReqs(IwfFeaturesConfig*, IWFCfgResp*);
        int HandleSetIwfDccaGenConfigReqs(IwfDccaGenConfig*, IWFCfgResp*);
        int HandleGetIwfDccaGenConfigReqs(IwfDccaGenConfig*, IWFCfgResp*);
        int HandleGetIwfDccaDestConfigReqs(IwfDccaDestsConfig*, IWFCfgResp*);
        int HandleSetIwfDccaDestConfigReqs(IwfDccaDestsConfig*, IWFCfgResp*);
        int HandleGetIwfUalManagerConfigReqs(IwfSigtranUalManagerConfig*, IWFCfgResp*);
        int HandleSetIwfUalManagerConfigReqs(IwfSigtranUalManagerConfig*, IWFCfgResp*);
        int HandleGetIwfProtocolActionsConfigReqs(IwfProtocolActionsConfig*, IWFCfgResp*);
        int HandleSetIwfProtocolActionsConfigReqs(IwfProtocolActionsConfig*, IWFCfgResp*);

        //Config Fetch
        int FetchIwfLocalConfiguration(IwfLocalHostsConfig*, IWFCfgResp*);
        int FetchIwfAssociationSetConfiguration(IwfSigtranAssociationSetsConfig*, IWFCfgResp*);
        int FetchIwfAssociationConfiguration(IwfSigtranAssociationsConfig*, IWFCfgResp*);
        int FetchIwfRemoteRouteConfiguration(IwfSigtranRemoteRoutesConfig*, IWFCfgResp*);
        int FetchIwfTranslatorRuleConfiguration(IwfTranslatorRulesConfig*, IWFCfgResp*);
        int FetchIwfTranslationDataConfiguration(IwfTranslationDataConfig*, IWFCfgResp*);
        int FetchIwfTimersConfiguration(IwfTimersConfig*, IWFCfgResp*);
        int FetchIwfFeaturesConfiguration(IwfFeaturesConfig*, IWFCfgResp*);
        int FetchIwfDccaConfiguration(IwfDccaConfig*, IWFCfgResp*);
        int FetchIwfProtocolActionsConfiguration(IwfProtocolActionsConfig*, IWFCfgResp*);

        // Method to set new instance ID received from Availability manager
        int UpdateInstanceId(uint16_t instanceId);
        void deleteCookie(CMgrCookie *CookieReq,int iType);

        //TestFunctions
        int TestIwfCMgr();
        DbStatus_e TestIwfSctpEndPointAdd();
        DbStatus_e TestIwfSctpEndPointMod();
        DbStatus_e TestIwfSctpEndPointDel();
        DbStatus_e TestIwfSctpEndPointSelect();

        DbStatus_e TestSctpProfileAdd();
        DbStatus_e TestSctpProfileMod();
        DbStatus_e TestSctpProfileDel();
        DbStatus_e TestSctpProfileSelect();

        DbStatus_e TestAssociationAdd();
        DbStatus_e TestAssociationMod();
        DbStatus_e TestAssociationDel();
        DbStatus_e TestAssociationSelect();

        DbStatus_e TestMultihomingAdd();
        DbStatus_e TestMultihomingMod();
        DbStatus_e TestMultihomingDel();
        DbStatus_e TestMultihomingSelect();
        DbStatus_e TestMultihomingSelectAll();

        DbStatus_e TestAssocSetAdd();
        DbStatus_e TestAssocSetMod();
        DbStatus_e TestAssocSetDel();
        DbStatus_e TestAssocSetSelect();

        DbStatus_e TestAssocSetMappingAdd();
        DbStatus_e TestAssocSetMappingMod();
        DbStatus_e TestAssocSetMappingDel();
        DbStatus_e TestAssocSetMappingSelect();
        DbStatus_e TestAssocSetMappingSelectall();

        DbStatus_e TestIwfLocalConfigAdd();
        DbStatus_e TestIwfLocalConfigMod();
        DbStatus_e TestIwfLocalConfigDel();
        DbStatus_e TestIwfLocalConfigSelect();

        DbStatus_e TestIwfLocalSSNMappingAdd();
        DbStatus_e TestIwfLocalSSNMappingMod();
        DbStatus_e TestIwfLocalSSNMappingDel();
        DbStatus_e TestIwfLocalSSNMappingSelect();
        DbStatus_e TestIwfLocalSSNMappingSelectAll();

        DbStatus_e TestIwfTranslatorRuleAdd();
        DbStatus_e TestIwfTranslatorRuleMod();
        DbStatus_e TestIwfTranslatorRuleDel();
        DbStatus_e TestIwfTranslatorRuleSelectAll();
        DbStatus_e TestIwfTranslatorRuleSelect();

        DbStatus_e TestIwfDestinationAdd();
        DbStatus_e TestIwfDestinationMod();
        DbStatus_e TestIwfDestinationDel();
        DbStatus_e TestIwfDestinationSelect();

        DbStatus_e TestIwfMapS6aConfigAdd();
        DbStatus_e TestIwfMapS6aConfigMod();
        DbStatus_e TestIwfMapS6aConfigDel();
        DbStatus_e TestIwfMapS6aConfigSelect();

        DbStatus_e TestIwfS6aMapConfigAdd();
        DbStatus_e TestIwfS6aMapConfigMod();
        DbStatus_e TestIwfS6aMapConfigDel();
        DbStatus_e TestIwfS6aMapConfigSelect();

        DbStatus_e TestIwfCapRoConfigAdd();
        DbStatus_e TestIwfCapRoConfigMod();
        DbStatus_e TestIwfCapRoConfigDel();
        DbStatus_e TestIwfCapRoConfigSelect();

        DbStatus_e TestCapRoIdpConfigAdd();
        DbStatus_e TestCapRoIdpConfigMod();
        DbStatus_e TestCapRoIdpConfigDel();
        DbStatus_e TestCapRoIdpConfigSelect();

        DbStatus_e TestCapRoIdpSmsConfigAdd();
        DbStatus_e TestCapRoIdpSmsConfigMod();
        DbStatus_e TestCapRoIdpSmsConfigDel();
        DbStatus_e TestCapRoIdpSmsConfigSelect();

        DbStatus_e TestRemoteRouteAdd();
        DbStatus_e TestRemoteRouteMod();
        DbStatus_e TestRemoteRouteDel();
        DbStatus_e TestRemoteRouteSelect();

        DbStatus_e TestIwfS6aMapAddrAdd();
        DbStatus_e TestIwfS6aMapAddrSelect();
        DbStatus_e TestIwfS6aMapAddrSelectAll();

        DbStatus_e TestExtServiceSelectAll();
        DbStatus_e TestExtServiceSelect();
        DbStatus_e TestExtBearerServiceSelectAll();
        DbStatus_e TestExtBearerServiceSelect();

        DbStatus_e TestIwfTimerAdd();
        DbStatus_e TestIwfTimerSelect();
    private:
        uint16_t m_instanceId;

};

#endif // __CMAPIMGR_H_
