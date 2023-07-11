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

#ifndef __CMAPILIB_H_
#define __CMAPILIB_H_


using namespace std;

#include <string.h>

#include "CMgrMethods_caller.h"
#include "dreconfig.h"
#include "PeerStats_caller.h"
#include "TraceConfigFetch_caller.h"
#include "CMAPICommon.h"
#include "CMgrStaticRoutingTableMethods_caller.h"
#include "StaticRoutingTable.h"
#include "StaticRoutingTableConfigFetch_caller.h"
#include "OverloadControl.h"
#include "CMgrTemplateMethods_caller.h"

// Common Management Library Class

class CMAPIProdConfig : public Stub::CMgrMethodsRespCbk ,
                        public Stub::PeerStatsRespCbk,
                        public DREConfigResults,
                        public Stub::TraceConfigFetchRespCbk,
                        public DREStaticRoutingConfigResults,
                        public Stub::CMgrStaticRoutingTableMethodsRespCbk,
                        public DREConfigTemplateResults,
                        public Stub::CMgrTemplateMethodsRespCbk
{
public:
 CMAPIProdConfig() {}
 ~CMAPIProdConfig() {}

 int InitializeLibrary();

//CMAPI Library Methods

int GetLocalHostConfig(LocalHostConfig& LocalHost,ErrorDetails& err);
int SetLocalHostConfig(LocalHostConfig& LHostInfo,DRECfgResp* Response);
int ModifyLocalHostConfig(LocalHostConfig& LHostInfo,DRECfgResp* Response);
int DeleteLocalHostConfig(string Hostname, string RealmName,DRECfgResp* Response);
int SetLocalHostAuthTimers(int LifeTime, int GraceTime, int Timeout,DRECfgResp* Response);
int SetLocalHostAcctTimers(int Interim, int RealTime, int Timeout,DRECfgResp* Response);
int SetLocalHostIPAddr(string ipaddr,DRECfgResp* Response);

//Changed cmapi's
int GetLocalHostConfig(LocalHost &LHostInfo, ErrorDetails& err);
int AddLocalHostTransport(string lHost, string realm, LHTransport &LHTransport, ErrorDetails& err);
int ModifyLocalHostTransport(string lHost, string realm, LHTransport &LHTransport, ErrorDetails& err);
int DeleteLocalHostTransport(string lHost, string realm, LHTransport &LHTransport, ErrorDetails& err);
int SetSctpProtocolConfiguration(SctpProtocol& SctpCfg, ErrorDetails& err);
int GetSctpProtocolConfiguration(SctpProtocol& SctpCfg, ErrorDetails& err);
int SetGeneralConfiguration(GeneralConfig& gCfg, ErrorDetails& err);
int GetGeneralConfiguration(GeneralConfig& gCfg, ErrorDetails& err);
int AddCACRLConfiguration(TrustedCAConfiguration& CaCrl, ErrorDetails& err);
int DeleteCACRLConfiguration(TrustedCAConfiguration& CaCrl, ErrorDetails& err);
int RemoveCACRLAssociation(TrustedCAConfiguration& CaCrl, ErrorDetails& err);
int ModifyCACRLConfiguration(TrustedCAConfiguration& CaCrl, ErrorDetails& err);
int GetCACRLConfiguration(CACRLs& CaCrl, ErrorDetails& err);
int GetTLSConfiguration(TLSConfig& tls, ErrorDetails& err);
int SetTLSConfiguration(TLSConfig& tls, ErrorDetails& err);
int GetTlsCipherCfg(TLSCipherConfigs& tlsCipher, ErrorDetails& err);
int EnableTlsCipherSuite(string TlsCiphersuiteName, ErrorDetails& err);
int DisableTlsCipherSuite(string TlsCiphersuiteName, ErrorDetails& err);
int AddSecIPToLocalHost(LocalHost &lHost, ErrorDetails& err);
int DeleteSecIPFromLocalHost(LocalHost &lHost, ErrorDetails& err);
int SetLocalHostConfig(LocalHost &LHostInfo, ErrorDetails& err);
int ModifyLocalHostConfig(LocalHost &LHostInfo, ErrorDetails& err);

int GetRealm(string realmname, RealmConfig& Realm,ErrorDetails& err);
int GetAllRealms(RealmsConfig& Realms,ErrorDetails& err);
int SetRealm(RealmsConfig& RealmInfo,DRECfgResp* Response);
int ModifyRealm(RealmsConfig& RealmInfo,DRECfgResp* Response);
int DeleteRealm(string RealmName,DRECfgResp* Response);
int DissociateRealmTemplate(string RealmName,DRECfgResp* Response);
int SetDefaultRoute(string Hostname, string RealmName,DRECfgResp* Response);
int GetDefaultRoute(RealmConfig& DefRoute,ErrorDetails& err);
int DeleteDefaultRoute(DRECfgResp* Response);
int SetDestination(RealmsConfig& RealmInfo,DRECfgResp* Response);
int ModifyDestination(RealmsConfig& RealmInfo,DRECfgResp* Response);
int GetDestination(string RealmName, RealmsConfig& RealmInfo,ErrorDetails& err);
int GetRealmRouting(string RealmName, RealmConfig& RealmInfo,ErrorDetails& err);
int DeleteDestination(RealmsConfig& RealmInfo,DRECfgResp* Response);
int GetUniqueRealmsOfPeer(RealmsConfig& Realms,ErrorDetails& err);
int EnableProxyInfoAvp(string realmname,DRECfgResp* Response);
int DisableProxyInfoAvp(string realmname,DRECfgResp* Response);
int GetPeerConfig(string peername, string realmname, PeerConfig& Peer,ErrorDetails& err);
int GetAllPeers(PeersConfig& Peers,ErrorDetails& err);
int GetAllPeersofRealm(string realmname, PeersConfig& Peers,ErrorDetails& err);
int SetPeerConfig(PeersConfig& PeerInfo,DRECfgResp* resp);
int ModifyPeerConfig(PeersConfig& PeerInfo,DRECfgResp* Response);
int AddDictionaryID(PeersConfig& PeerInfo,DRECfgResp* Response);
int DeleteDictionaryID(PeersConfig& PeerInfo,DRECfgResp* Response);
int RemovePeerConfig(string peername, string realmname,DRECfgResp* Response);
int RemoveAlternatePeer(string peername, string realmname,DRECfgResp* Response);
int RemovePeerTemplate(string peername, string realmname, DRECfgResp* Response);
int SetPeerStatus(PeersConfig& PeerInfo,DRECfgResp* Response);
int GetPeersState(PeersConfig& PeerInfo);
int AddSecIPToPeer(PeersConfig& PeerInfo, DRECfgResp* Response);
int DeleteSecIPFromPeer(PeersConfig& PeerInfo, DRECfgResp* Response);

//Topology related API's

int SetDefaultBehaviour(bool value,THFResp *Response);
int SetTopologyHiding(bool value,THFResp *Response);
int DelThfRealm(THFReq Request,THFResp *Response);
int DelThfVHost(THFReq Request,THFResp *Response);
int AddThfVHost(THFReq Request,THFResp *Response);
int AddThfRealm(THFReq Request,THFResp *Response);
int GetThfRealm(THFReq& Request,THFResp *Response);
int GetThfvHost(THFReq& Request,THFResp *Response);
int GetTopologyHiding(THFReq& Request,THFResp *Response);
int SetDefaultBehaviourAndTopologyHiding(THFReq Request,THFResp *Response);

// CMAPI Calls from CLI/GUI
int GetSDTFConfig(SDTFReq& Req, SDTFResp& Resp);
int SetSDTFRuleStatus(SDTFReq& Req, SDTFResp& Resp);
int AddSDTFConfig(SDTFReq& Req, SDTFResp& Resp);
int ModifySDTFConfig(SDTFReq& Req, SDTFResp& Resp);
int DeleteSDTFConfig(string& RuleName, SDTFResp& Resp);
int GetSDTFEnableStatus(SDTFResp& Resp);
int SetSDTFEnableStatus(bool enableSDTF, SDTFResp& Resp);

//Tracing related API's
int AddTraceFilter(TraceReq& Request, TraceResp& Response);
int DeleteTraceFilter(TraceReq& Request, TraceResp& Response);
int ModifyTraceFilter(TraceReq& Request, TraceResp& Response);
int GetTraceFilter(TraceReq& Request, TraceResp& Response);
int EnableTracing(TraceReq& Request, TraceResp& Response);
int PollTraceFilter(TraceReq& Request, TraceResp& Response);
int SendTraceRequest(TraceReq& req, TraceResp *resp);

//Congection Control related API's
int ModCMFRealmTemplate(TemplateReq Request,TemplateResp *Response);
int DelCMFRealmTemplate(TemplateReq Request,TemplateResp *Response);
int AddCMFRealmTemplate(TemplateReq Request,TemplateResp *Response);
int ModCMFPeerTemplate(TemplateReq Request,TemplateResp *Response);
int DelCMFPeerTemplate(TemplateReq Request,TemplateResp *Response);
int AddCMFPeerTemplate(TemplateReq Request,TemplateResp *Response);
int GetCMFRealmTemplate(TemplateReq& Request,TemplateResp *Response);
int GetCMFPeerTemplate(TemplateReq& Request,TemplateResp *Response);



//static routing table  related API's
int AddStaticRoutingEntry(StaticRoutingTableConfigReq& Request, StaticRoutingTableConfigResp& Response);
int DeleteStaticRoutingEntry(StaticRoutingTableConfigReq& Request, StaticRoutingTableConfigResp& Response);
int ModifyStaticRoutingEntry(StaticRoutingTableConfigReq& Request, StaticRoutingTableConfigResp& Response);
int GetStaticRoutingEntries(StaticRoutingTableConfigReq& Request, StaticRoutingTableConfigResp& Response);
int SendStaticRoutingRequest(StaticRoutingTableConfigReq& req, StaticRoutingTableConfigResp *resp);

// Results Interface
int SendDREConfigResult(DRECfgResp *Req,CMAPIRes *Resp);
int SendTHFConfigResult(THFResp *Req,CMAPIRes *Resp);
int SendTraceConfigResult(TraceResp *Req,CMAPIRes *Resp);
int SendStaticRoutingTableConfigResult(StaticRoutingTableConfigResp*, CMAPIRes*);
int SendDreTemplateConfigResult(TemplateResp *Req,CMAPIRes *Resp);
int SendSDTFConfigResult(SDTFResp *Req, CMAPIRes *Resp);

//Stacks stack API
int GetPeerGeneralStats(PeerGeneralStatsReq& req, PeerGeneralStatsResp &resp);
int GetPeerTransportStats(PeerTransportStatsReq& req, PeerTransportStatsResp &resp);
int GetPeerDREProtocolErrorStats(PeerDREProtocolErrorStatsReq& req, PeerDREProtocolErrorStatsResp &resp);
int ResetAllPeerStats(ResetPeerStatsReq& req, ResetPeerStatsResp &resp);

int SendPeerStatsRequest(PeerGeneralStatsReq& req, PeerGeneralStatsResp *resp);
int SendPeerStatsRequest(PeerTransportStatsReq& req, PeerTransportStatsResp *resp);
int SendPeerStatsRequest(PeerDREProtocolErrorStatsReq& req, PeerDREProtocolErrorStatsResp *resp);
int SendPeerStatsRequest(ResetPeerStatsReq& req, ResetPeerStatsResp *resp);

// Callbacks for CMGR Implementation Methods
int HandleGetLocalHostConfigReqsRespCbk(DRECfgResp *resp);
int HandleSetLocalHostConfigReqsRespCbk(DRECfgResp *resp);
int HandleGetPeerConfigReqsRespCbk(DRECfgResp *resp);
int HandleGetPeerStatesReqsRespCbk(DRECfgResp *resp);
int HandleSetPeerConfigReqsRespCbk(DRECfgResp *resp);
int HandleDelPeerConfigReqsRespCbk(DRECfgResp *resp);
int HandleGetRealmConfigReqsRespCbk(DRECfgResp *resp);
int HandleSetRealmConfigReqsRespCbk(DRECfgResp *resp);
int HandleDelRealmConfigReqsRespCbk(DRECfgResp *resp);

// Dictionary provisioning and transformation plugins
int HandleSetDictionaryConfigReqRespCbk(DRECfgResp *resp);
int HandleSetPluginConfigReqRespCbk(DRECfgResp *resp);
int GetTransformPlugin(DRECfgResp *Resp);
int GetDictionaryConfiguration(DRECfgResp *Resp);
int HandleGetPluginConfigReqRespCbk(DRECfgResp *resp);
int HandleGetDictionaryConfigReqRespCbk(DRECfgResp *resp);
int HandleGetTraceConfigReqsRespCbk(TraceResp *resp);
int HandleSetTraceConfigReqsRespCbk(TraceResp *resp);
int HandleGetStaticRoutingTableConfigReqsRespCbk(StaticRoutingTableConfigResp *Resp);
int HandleSetStaticRoutingTableConfigReqsRespCbk(StaticRoutingTableConfigResp *Resp);
int SetTHFConfigRespCbk(THFResp *resp);
int GetTHFConfigRespCbk(THFResp *resp);
int HandleSetTemplateConfigReqsRespCbk(TemplateResp *resp);
int HandleGetTemplateConfigReqsRespCbk(TemplateResp *resp);

// Response Callback for SDTF
int GetSDTFConfigRespCbk(SDTFResp *resp);
int SetSDTFConfigRespCbk(SDTFResp *resp);

//Response Callbacks for Stack Stats Implementation Methods
int FetchPeerGeneralStatsRespCbk(PeerGeneralStatsResp *Resp);
int FetchPeerTransportStatsRespCbk(PeerTransportStatsResp *Resp);
int FetchPeerDREProtocolErrorStatsRespCbk(PeerDREProtocolErrorStatsResp *Resp);
int ResetPeerStatsRespCbk(ResetPeerStatsResp *Resp);
int FetchTraceConfigurationRespCbk(TraceResp*);
int GetTraceConfigReqsRespCbk(TraceResp *resp);
int GetStaticRoutingEntriesRespCbk(StaticRoutingTableConfigResp *resp);
int FetchStaticRoutingTableConfigurationRespCbk(StaticRoutingTableConfigResp* resp);
//User Management API
int AddUser(Users& UserList,UserResp* Resp);
int GetUser(string& UserName, Users& UserList,ErrorDetails& err);
int DeleteUser(Users& UserList,UserResp* Resp);
int ChangePassword(string& UserName, char *password, size_t length,UserResp* Resp);

//Response callback for the User Management API
int SetUserConfigRespCbk(UserResp *Resp);
int GetUserConfigRespCbk(UserResp *Resp);


int SetDictionaryStatus(DictionaryConfigReq& dictionaryInfo, ErrorDetails& err);
int SetTransformPluginStatus(TransformPluginConfigReq& transformPluginInfo, ErrorDetails& err);
int ReloadTransformPluginConfig(TransformPluginConfigReq& transformPluginInfo, ErrorDetails& err);
int ReloadSDTFPluginConfig(ErrorDetails& err);

//Platform (Stack related API)
//Library API
int GetLastCallErrorDetails(ErrorDetails& Err);
int SetLocalHostConfig(LocalHost &lHost);
int ModifyLocalHostConfig(LocalHost &lHost);
int GetLocalHostConfig(LocalHost &lHost);
int GetLocalTransportTagConfig(LocalTransportTagResponse &LTTResp);
int AddSecIPToLocalHost(LocalHost &lHost);
int DeleteSecIPFromLocalHost(LocalHost &lHost);

int AddLocalHostTransport(string lHost, string realm, LHTransport& lTransport);
int DeleteLocalHostTransport(string lHost, string realm, LHTransport& lTranport);
int ModifyLocalHostTransport(string lHost, string realm, LHTransport& lTransport);
int SetSctpProtocolConfiguration(SctpProtocol& SctpCfg);
int GetSctpProtocolConfiguration(SctpProtocol& SctpCfg);
int SetGeneralConfiguration(GeneralConfig& gCfg);
int GetGeneralConfiguration(GeneralConfig& gCfg);

int AddCACRLConfiguration(TrustedCAConfiguration& CaCrl);
int DeleteCACRLConfiguration(TrustedCAConfiguration& CaCrl);
int RemoveCACRLAssociation(TrustedCAConfiguration& CaCrl);
int ModifyCACRLConfiguration(TrustedCAConfiguration& CaCrl);
int GetCACRLConfiguration(CACRLs& CaCrl);

int GetTLSConfiguration(TLSConfig& tls);
int SetTLSConfiguration(TLSConfig& tls);

int GetTlsCipherCfg(TLSCipherConfigs& tlsCipher);
int EnableTlsCipherSuite(string TlsCiphersuiteName);
int DisableTlsCipherSuite(string TlsCiphersuiteName);
// MeSS Callbacks
int HandleGetStackConfigurationRespCbk(StackConfigResponse *Resp);
int HandleSetStackConfigurationRespCbk(StackConfigResponse *Resp);
int HandleGetLocalTransportTagsRespCbk(LocalTransportTagResponse *resp);


private:
    int IsResponseOK(UserResp *Resp);
    int IsResponseOK(TraceResp *Resp);
    int IsResponseOK(StaticRoutingTableConfigResp *Resp);

  Stub::CMgrMethods   *m_CMgrCallerObj;
  Stub::CMgrTemplateMethods *m_CMgrTemplateCallerObj;
  Stub::PeerStats     *m_PeerStatsObj;
  Stub::TraceConfigFetch *m_TraceConfigObj;
  CMAPIIntSync        *m_CMAPIResponse;
  Stub::CMgrStaticRoutingTableMethods *m_StaticRoutingConfigObj;

  static const unsigned int m_waitTime = 32000000;
  ErrorDetails m_lastError;
  volatile bool m_SendSuccess;
};

#endif  // __CMAPILIB_H_
