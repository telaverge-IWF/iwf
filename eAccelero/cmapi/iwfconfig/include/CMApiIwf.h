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

#ifndef __CMAPIIWF_H_
#define __CMAPIIWF_H_


using namespace std;

#include <string.h>

#include "CMgrIwfMethods_caller.h"
#include "iwfconfig.h"
#include "IwfFetch_caller.h"
#include "IwfSigtranMethods_caller.h"
#include "CMAPICommon.h"
#include "IwfConfigResults_caller.h"

// Common Management Library Class

class CMApiIwfConfig : public Stub::CMgrIwfMethodsRespCbk, public IwfConfigResults
{
public:
 CMApiIwfConfig() {}
 ~CMApiIwfConfig() {}

 int InitializeLibrary();

//CMAPI Library Methods
int GetLastCallErrorDetails(ErrorDetails& Err);
int GetLocalHostConfig(IwfLocalHostConfig& LocalHost, ErrorDetails& err);
int SetLocalHostConfig(IwfLocalHostConfig& LHostInfo, IWFCfgResp* Response);
int ModifyLocalHostConfig(IwfLocalHostConfig& LHostInfo, IWFCfgResp* Response);
int DeleteLocalHostSSN(IwfLocalHostConfig& LHostInfo, IWFCfgResp* Response);
int SetLocalHostInvokeTimer(int Time, IWFCfgResp* Response);
int GetDestination(IwfSigtranDestinationsConfig& DestInfo, ErrorDetails& err); 
int SetDestination(IwfSigtranDestinationsConfig& DestInfo, IWFCfgResp* Response);
int ModifyDestination(IwfSigtranDestinationsConfig& DestInfo, IWFCfgResp* Response);
int DeleteDestination(IwfSigtranDestinationsConfig& DestInfo, IWFCfgResp* Response);
int GetAssociationSet(IwfSigtranAssociationSetsConfig& AssocSet, ErrorDetails& err);
int SetAssociationSet(IwfSigtranAssociationSetsConfig& AssocSet, IWFCfgResp* Response);
int ModifyAssociationSet(IwfSigtranAssociationSetsConfig& AssocSet, IWFCfgResp* Response);
int DeleteAssociationSet(IwfSigtranAssociationSetsConfig& AssocSet, IWFCfgResp* Response);
int ActivateAssociationSet(IwfSigtranAssociationSetsConfig& AssocSet, IWFCfgResp* Response);
int GetAssociation(IwfSigtranAssociationsConfig& AssocInfo, ErrorDetails& err);
int SetAssociation(IwfSigtranAssociationsConfig& AssocInfo, IWFCfgResp* Response);
int ModifyAssociation(IwfSigtranAssociationsConfig& AssocInfo, IWFCfgResp* Response);
int DeleteAssociation(IwfSigtranAssociationsConfig& AssocInfo, IWFCfgResp* Response);
int ActivateAssociation(IwfSigtranAssociationsConfig& AssocInfo, IWFCfgResp* Response);
int GetIwfSctpEndPoint(IwfSigtranSctpEndPointsConfig& SctpEndPoint, ErrorDetails& err);
int SetIwfSctpEndPoint(IwfSigtranSctpEndPointsConfig& SctpEndPoint, IWFCfgResp* Response);
int ModifyIwfSctpEndPoint(IwfSigtranSctpEndPointsConfig& SctpEndPoint, IWFCfgResp* Response);
int DeleteIwfSctpEndPoint(IwfSigtranSctpEndPointsConfig& SctpEndPoint, IWFCfgResp* Response);
int GetSctpProfile(IwfSigtranSctpProfilesConfig& SctpInfo, ErrorDetails& err);
int SetSctpProfile(IwfSigtranSctpProfilesConfig& SctpInfo, IWFCfgResp* Response);
int ModifySctpProfile(IwfSigtranSctpProfilesConfig& SctpInfo, IWFCfgResp* Response);
int DeleteSctpProfile(IwfSigtranSctpProfilesConfig& SctpInfo, IWFCfgResp* Response);
int GetSigtranMultihoming(IwfSigtransMultihomingConfig& IwfMultihoming, ErrorDetails& err);
int SetSigtranMultihoming(IwfSigtransMultihomingConfig& IwfMultihoming, IWFCfgResp* Response);
int ModifySigtranMultihoming(IwfSigtransMultihomingConfig& IwfMultihoming, IWFCfgResp* Response);
int DeleteSigtranMultihoming(IwfSigtranSctpEndPointsConfig& IwfMultihoming, IWFCfgResp* Response);
int GetRemoteRoute(IwfSigtranRemoteRoutesConfig& RemoteRoute, ErrorDetails& err);
int SetRemoteRoute(IwfSigtranRemoteRoutesConfig& RemoteRoute, IWFCfgResp* Response);
int ModifyRemoteRoute(IwfSigtranRemoteRoutesConfig& RemoteRoute, IWFCfgResp* Response);
int DeleteRemoteRoute(IwfSigtranRemoteRoutesConfig& RemoteRoute, IWFCfgResp* Response);
int GetTranslatorRules(IwfTranslatorRulesConfig& Rule, ErrorDetails& err);
int SetTranslatorRules(IwfTranslatorRulesConfig& Rule, IWFCfgResp* Response);
int ModifyTranslatorRules(IwfTranslatorRulesConfig& Rule, IWFCfgResp* Response);
int DeleteTranslatorRules(IwfTranslatorRulesConfig& Rule, IWFCfgResp* Response);
int GetS6aMapTranslationData(IwfS6aToMapConfig& S6aMap, ErrorDetails& err);
int SetS6aMapTranslationData(IwfS6aToMapConfig& S6aMap, IWFCfgResp* Response);
int ModifyS6aMapTranslationData(IwfS6aToMapConfig& S6aMap, IWFCfgResp* Response);
int DeleteS6aMapTranslationData(IwfS6aToMapConfig& S6aMap, IWFCfgResp* Response);
int GetMapS6aTranslationData(IwfMapToS6aConfig& MapS6a, ErrorDetails& err);
int SetMapS6aTranslationData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response);
int ModifyMapS6aTranslationData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response);
int DeleteMaps6aTranslationData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response);
int GetCapRoIDPTranslationData(IwfCapToRoConfig& CapRo, ErrorDetails& err);
int GetCapRoIDPSMSTranslationData(IwfCapToRoConfig& CapRo, ErrorDetails& err);
int SetCapRoTranslationData(IwfCapToRoConfig& CapRo, IWFCfgResp* Response);
int ModifyCapRoTranslationData(IwfCapToRoConfig& CapRo, IWFCfgResp* Response);
int DeleteCapRoTranslationData(IwfCapToRoConfig& CapRo, IWFCfgResp* Response);
int GetAllTranslationData(IwfTranslationDataConfig& TransData, ErrorDetails& err);
int GetIwfTimers(IwfTimersConfig& Timers, ErrorDetails& err);
int SetIwfTimers(IwfTimersConfig& Timers, IWFCfgResp* Response);
int ModifyIwfTimers(IwfTimersConfig& Timers, IWFCfgResp* Response);
int DeleteIwfTimers(IwfTimersConfig& Timers, IWFCfgResp* Response);
int GetUalConfig(IwfSigtranUalManagerConfig& Ual, ErrorDetails& err);
int SetUalConfig(IwfSigtranUalManagerConfig& Ual, IWFCfgResp* Response);
int ModifyUalConfig(IwfSigtranUalManagerConfig& Ual, IWFCfgResp* Response);
int SetTranslatorVplmnIds(IwfTranslatorRulesConfig& Rule, IWFCfgResp* Response);
int ModifyTranslatorVplmnIds(IwfTranslatorRulesConfig& Rule, IWFCfgResp* Response);
int DeleteTranslatorVplmnIds(IwfTranslatorRulesConfig& Rule, IWFCfgResp* Response);
int SetMapS6aVplmnIdData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response);
int ModifyMapS6aVplmnIdData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response);
int DeleteMapS6aVplmnIdData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response);
int SetMapS6aVplmnIdSgsnMapData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response);
int ModifyMapS6aVplmnIdSgsnMapData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response);
int DeleteMapS6aVplmnIdSgsnMapData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response);
int GetIwfCapProtoTimers(IwfTimersConfig& Timers, ErrorDetails& err);
int SetIwfCapProtoTimers(IwfTimersConfig& Timers, IWFCfgResp* Response);
int ModifyIwfCapProtoTimers(IwfTimersConfig& Timers, IWFCfgResp* Response);
int GetIwfFeatures(IwfFeaturesConfig& Features, ErrorDetails& err);
int SetIwfFeatures(IwfFeaturesConfig& Features, IWFCfgResp* Response);
int ModifyIwfFeatures(IwfFeaturesConfig& Features, IWFCfgResp* Response);
int DeleteIwfFeatures(IwfFeaturesConfig& Features, IWFCfgResp* Response);
int GetIwfDccaGenConfig(IwfDccaGenConfig& DccaGenConfig, ErrorDetails& err);
int ModifyIwfDccaGenConfig(IwfDccaGenConfig& DccaGenConfig, IWFCfgResp* Response);
int AddIwfDccaGenConfig(IwfDccaGenConfig& DccaGenConfig, IWFCfgResp* Response);
int DeleteIwfDccaGenConfig(IwfDccaGenConfig& DccaGenConfig, IWFCfgResp* Response);
int GetIwfDccaDestConfig(IwfDccaDestsConfig& DccaDestConfig, ErrorDetails& err);
int ModifyIwfDccaDestConfig(IwfDccaDestsConfig& DccaDestConfig, IWFCfgResp* Response);
int AddIwfDccaDestConfig(IwfDccaDestsConfig& DccaDestConfig, IWFCfgResp* Response);
int DeleteIwfDccaDestConfig(IwfDccaDestsConfig& DccaDestConfig, IWFCfgResp* Response);
int DeleteIwfDccaEndpointConfig(IwfDccaDestsConfig& DccaDestConfig, IWFCfgResp* Response);
int AddIwfProtocolActionsConfig(IwfProtocolActionsConfig &ProtActionssConfig, IWFCfgResp* Response);
int ModifyIwfProtocolActionsConfig(IwfProtocolActionsConfig &ProtActionssConfig, IWFCfgResp* Response);
int GetIwfProtocolActionsConfig(IwfProtocolActionsConfig& ProtActionsConfig, ErrorDetails& err);
int DeleteIwfProtocolActionsConfig(IwfProtocolActionsConfig& ProtActionsConfig, IWFCfgResp* Response);
int DeleteIwfCallScenarioConfig(IwfProtocolActionsConfig& ProtActionsConfig, IWFCfgResp* Response);
int DeleteIwfProtocolEventType(IwfProtocolActionsConfig& ProtActionsConfig, IWFCfgResp* Response);
int DeleteIwfEventTypeConfig(IwfProtocolActionsConfig& ProtActionsConfig, IWFCfgResp* Response);

//Result Interface 
int SendIWFConfigResult(IWFCfgResp *Req, CMAPIRes *Resp);
int ClearSessionContext(string imsi, IWFCfgResp* Response);
int DumpSystemInfo(IWFCfgResp* Response);

//Callbacks for CMGR implementation methods
int HandleGetLocalHostConfigReqsRespCbk(IWFCfgResp *resp);
int HandleSetLocalHostConfigReqsRespCbk(IWFCfgResp *resp);
int HandleGetDestinationConfigReqsRespCbk(IWFCfgResp *resp);
int HandleSetDestinationConfigReqsRespCbk(IWFCfgResp *resp);
int HandleGetAssociationSetConfigReqsRespCbk(IWFCfgResp *resp);
int HandleSetAssociationSetConfigReqsRespCbk(IWFCfgResp *resp);
int HandleGetAssociationConfigReqsRespCbk(IWFCfgResp *resp);
int HandleSetAssociationConfigReqsRespCbk(IWFCfgResp *resp);
int HandleGetSctpEndPointConfigReqsRespCbk(IWFCfgResp *resp);
int HandleSetSctpEndPointConfigReqsRespCbk(IWFCfgResp *resp);
int HandleGetSctpProfileConfigReqsRespCbk(IWFCfgResp *resp);
int HandleSetSctpProfileConfigReqsRespCbk(IWFCfgResp *resp);
int HandleGetSigtranMultihomingConfigReqsRespCbk(IWFCfgResp *resp);
int HandleSetSigtranMultihomingConfigReqsRespCbk(IWFCfgResp *resp);
int HandleGetRemoteRouteConfigReqsRespCbk(IWFCfgResp *resp);
int HandleSetRemoteRouteConfigReqsRespCbk(IWFCfgResp *resp);
int HandleGetTranslatorRuleConfigReqsRespCbk(IWFCfgResp *resp);
int HandleSetTranslatorRuleConfigReqsRespCbk(IWFCfgResp *resp);
int HandleGetTranslationDataConfigReqsRespCbk(IWFCfgResp *resp);
int HandleSetTranslationDataConfigReqsRespCbk(IWFCfgResp *resp);
int HandleSetIwfTimersConfigReqsRespCbk(IWFCfgResp *resp);
int HandleGetIwfTimersConfigReqsRespCbk(IWFCfgResp *resp);
int HandleGetIwfUalManagerConfigReqsRespCbk(IWFCfgResp *resp);
int HandleSetIwfUalManagerConfigReqsRespCbk(IWFCfgResp *resp);
int HandleSetIwfFeaturesConfigReqsRespCbk(IWFCfgResp *resp);
int HandleGetIwfFeaturesConfigReqsRespCbk(IWFCfgResp *resp);
int HandleGetIwfDccaGenConfigReqsRespCbk(IWFCfgResp*);
int HandleSetIwfDccaGenConfigReqsRespCbk(IWFCfgResp*);
int HandleGetIwfDccaDestConfigReqsRespCbk(IWFCfgResp*);
int HandleSetIwfDccaDestConfigReqsRespCbk(IWFCfgResp*);
int HandleSetIwfProtocolActionsConfigReqsRespCbk(IWFCfgResp*);
int HandleGetIwfProtocolActionsConfigReqsRespCbk(IWFCfgResp*);

private:
    int IsResponseOK(IWFCfgResp *Resp);

  Stub::CMgrIwfMethods  *m_CMgrCallerObj;
  CMAPIIntSync          *m_CMAPIResponse;

  static const unsigned int m_waitTime = 32000000;
  ErrorDetails  m_lastError;
  volatile bool m_SendSuccess;
};

#endif  // __CMAPILIB_H_
