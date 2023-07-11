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


#ifndef CMGR_DB_INTERFACE_H
#define CMGR_DB_INTERFACE_H

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <driver.h>
#include <string.h>
#include <stdio.h>


#include "QueryPB.h"
#include "QueryIwfPB.h"
#include "MysqlInterfacePB.h"
#include "CommonStructure.h"
#include "config.h"
#include "ConfigManager.h"

#include "dreconfig_def.h"
#include "Compo_def.h"
#include "HA_def.h"
#include "StaticRoutingTable_def.h"
#include "UserManagement_def.h"
class ConfigManager;
class QueryIwf_PB;
class CMgrDbInterface : public Query_PB
{

    public:
        MysqlInterfacePB m_dbHandle;
        ConfigManager *m_ConfigManager;
        QueryIwf_PB *m_IwfQueryPB;
        ConfigManagerAlarms *m_ConfigManagerAlarms;
        CMgrDbInterface(std::string sHostName,std::string sUserName,std::string sPassword,std::string sDataBase,ConfigManager *pConfigManager, ConfigManagerAlarms* alarms);
        DbStatus_e mysql_Peer_Delete_peerGrpAssoc_validation(PeerConfig *pPeerConfig);
        DbStatus_e mysql_AltPeer_Delete_Config_Reqs(PeersConfig *pPeersConfig,DRECfgResp *resp);
        DbStatus_e mysql_PeerOverloadTemplate_DisAssociate_Config_Reqs(PeersConfig *pPeersConfig,DRECfgResp *resp);
        DbStatus_e mysql_PeerTemplate_DisAssociate_validation(PeerConfig *pPeerConfig);
        DbStatus_e mysql_LocalHost_Get_Config_Reqs(LocalHostConfig *pLocalHostConfig,DRECfgResp *resp);
        DbStatus_e mysql_StaticRoutingTableConfig_Get_Config_Reqs(StaticRoutingTableConfigReq *req, StaticRoutingTableConfigResp *resp);
        DbStatus_e mysql_Peer_Get_Config_Reqs(PeersConfig *pPeersConfig,DRECfgResp *resp);
        DbStatus_e mysql_Peer_Get_Config_Reqs_for_peerstat(PeersConfig *pPeersConfig,DRECfgResp *resp);
        DbStatus_e mysql_PeerOfRealm_Get_Config_Reqs(PeersConfig *pPeersConfig,DRECfgResp *resp);
        DbStatus_e mysql_DefaultRoute_Get_Config_Reqs_Through_Peer(PeersConfig *pPeersConfig,DRECfgResp *resp);
        DbStatus_e mysql_Realm_Get_Config_Reqs(RealmsConfig *pRealmsConfig,DRECfgResp *resp);
        DbStatus_e mysql_RealmRouting_Get_Config_Reqs(RealmsConfig *pRealmsConfig,DRECfgResp *resp);
        DbStatus_e mysql_PeerOfRealm_Get_Config_Reqs(RealmsConfig *pRealmsConfig,DRECfgResp *resp);
        DbStatus_e mysql_DefaultRoute_Get_Config_Reqs_Through_Realm(RealmConfig *pRealmsConfig,DRECfgResp *resp);
        DbStatus_e mysql_DefaultRoute_Get_Config_Reqs_Through_Realm(RealmsConfig *pRealmsConfig,DRECfgResp *resp);
        DbStatus_e mysql_PeerGroup_Get_Config_Reqs(LBPeerGroupReq *req,LBPeerGroupResp *Resp);
        DbStatus_e mysql_PeerConfig_Get_Config_Reqs(LBPeerGroupReq *req,LBPeerGroupResp *Resp);
        DbStatus_e mysql_Lbalgo_Get_Config_Reqs(LBPeerGroupReq *req,LBPeerGroupResp *Resp);
        DbStatus_e mysql_DictionaryConfig_Get_Config_Reqs(DynDictionaryRequest *pDynDictionaryConfig,DynDictionaryResponse *resp);
        DbStatus_e mysql_AvaMgr_Get_Config_Reqs(AvaMgrConfig *req,AvaMgrConfigResp *Resp);
        DbStatus_e mysql_RepMgr_Get_Config_Reqs(RepMgrConfig *req,RepMgrConfigResp *Resp);
        DbStatus_e mysql_Dre_Get_Config_Reqs(DreHAConfig *req,DreHAConfigResp *Resp);
        DbStatus_e mysql_TracingFilter_Get_Config_Reqs(TraceReq *req, TraceResp *resp);
        DbStatus_e mysql_Tracing_Get_Config_Reqs(TraceReq *req, TraceResp *resp);
        DbStatus_e mysql_LocalHost_Get_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_SCTPConfig_Get_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_TrustedCAConfig_Get_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_StackGeneralConfig_Get_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_TLSConfig_Get_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_CipherSuiteConfig_Get_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);

        DbStatus_e mysql_LocalHost_Add_Config_Reqs(LocalHostConfig *pLocalHostConfig,DRECfgResp *resp);
        DbStatus_e mysql_PeerAndTimer_Add_Config_Reqs(PeerConfig *pPeerConfig,DRECfgResp *resp);
        DbStatus_e mysql_PeerDictionaryMap_Add_Config_Reqs_Through_Peer(PeerConfig *pPeerConfig,DRECfgResp *resp);
        DbStatus_e mysql_PeerSecondaryIp_Add_Config_Reqs_Through_Peer(PeerConfig *pPeerConfig,DRECfgResp *resp);
        DbStatus_e mysql_DefaultRoute_Add_Config_Reqs_Through_Peer(PeerConfig *pPeerConfig,DRECfgResp *resp);
        DbStatus_e mysql_RealmRouting_Add_Config_Reqs(RealmConfig *pRealmConfig, int iDestinationIndex,DRECfgResp *resp);
        DbStatus_e mysql_Realm_Add_Config_Reqs(RealmConfig *pRealmConfig,DRECfgResp *resp);
        DbStatus_e mysql_Realm_Validation(RealmConfig *pRealmConfig);
        DbStatus_e mysql_Realm_Delete_validation(::RealmConfig* pRealmConfig);
        DbStatus_e mysql_DefaultRoute_Add_Config_Reqs_Through_Realm(RealmConfig *pRealmConfig, int iDestinationIndex);
        DbStatus_e mysql_PeerGroup_Add_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp);
        DbStatus_e mysql_PeerConfig_Add_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp);
        DbStatus_e mysql_Lbalgo_Add_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp);
        DbStatus_e mysql_Tracing_Set_Config_Reqs(TraceReq *req, TraceResp *resp);
        DbStatus_e mysql_SCTPConfig_Set_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_StackGeneralConfig_Set_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_TLSConfig_Set_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_TrustedCAConfig_Add_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_TrustedCAConfig_Add_Validation(TrustedCAConfiguration *pTrustedCAConfiguration);
        DbStatus_e mysql_TrustedCAConfig_Mod_Validation(TrustedCAConfiguration *pTrustedCAConfiguration);

        DbStatus_e mysql_TracingFilter_Add_Config_Reqs(TraceReq *req, TraceResp *resp);
        DbStatus_e sql_TracingFilter_Rule_Validation(TraceConfig *pTracingData,int opType,string& filterName);
        DbStatus_e mysql_StaticRouting_Add_Config_Reqs(StaticRoutingTableConfigReq *req,StaticRoutingTableConfigResp *resp);

        DbStatus_e mysql_LocalHost_Delete_Config_Reqs(LocalHostConfig *req,DRECfgResp *resp);
        DbStatus_e mysql_DefaultRoute_Delete_Config_Reqs_Through_Realm(RealmConfig *req,DRECfgResp *resp);
        DbStatus_e mysql_Peer_Delete_Config_Reqs(PeersConfig *pPeersConfig,DRECfgResp *resp);
        DbStatus_e mysql_PeerDictionaryMap_Delete_Config_Reqs_Through_Peer(PeersConfig *pPeersConfig,DRECfgResp *resp);
        DbStatus_e mysql_PeerSecondaryIp_Delete_Config_Reqs_Through_Peer(PeersConfig *pPeersConfig,DRECfgResp *resp);
        DbStatus_e mysql_DefaultRoute_Delete_Config_Reqs(RealmsConfig *pRealmsConfig,DRECfgResp *resp);
        DbStatus_e mysql_PeerGroup_Delete_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp);
        DbStatus_e mysql_PeerConfig_Delete_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp);
        DbStatus_e mysql_Lbalgo_Delete_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp);
        DbStatus_e mysql_RealmRouting_Delete_Config_Reqs(RealmsConfig *pRealmsConfig,DRECfgResp *resp);
        DbStatus_e mysql_Realm_Delete_Config_Reqs(RealmsConfig *pRealmsConfig,DRECfgResp *resp);
        DbStatus_e mysql_TransportType_Del_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_LocalHost_Del_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_TrustedCAConfig_Del_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_StaticRouting_Del_Config_Reqs(StaticRoutingTableConfigReq *req,StaticRoutingTableConfigResp *resp);
        DbStatus_e mysql_TrustedCAConfig_RemoveAssoc_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);

        DbStatus_e copy_LocalHostConfig(LocalHostConfig *req,DRECfgResp  *resp);
        DbStatus_e copy_DefaultRoute(RealmConfig *req,DRECfgResp  *resp);

        DbStatus_e mysql_PeerAndTimer_Mod_Config_Reqs(PeerConfig *pPeerConfig,DRECfgResp *resp);
        DbStatus_e mysql_Peer_PeerSourcePort_And_LocalTransportPortOrSecurePort_Conflict_validation(PeerConfig *pPeerConfig);
        DbStatus_e mysql_LocalTransportTagConfig_Get_Config_Reqs(LocalTransportTagRequest *req, LocalTransportTagResponse *resp);
        DbStatus_e mysql_Peer_Mod_Unique_IpAndPortOrSecurePort_validation(PeerConfig *pPeerConfig,DRECfgResp *resp);
        DbStatus_e mysql_PeerAndTimer_Mod_validation(PeerConfig *pPeerConfig,DRECfgResp *resp);
        DbStatus_e mysql_DefaultRoute_Mod_Config_Reqs_Through_Peer(PeerConfig *pPeerConfig,DRECfgResp *resp);
        DbStatus_e mysql_RealmRouting_Mod_Config_Reqs(RealmConfig *pRealmConfig, int iDestinationIndex,DRECfgResp *resp);
        DbStatus_e mysql_Realm_Mod_Config_Reqs(RealmConfig *pRealmConfig,DRECfgResp *resp);
        DbStatus_e mysql_Realm_Dissociate_Template_Config_Reqs(RealmsConfig *pRealmsConfig,DRECfgResp *resp);
        DbStatus_e mysql_RealmTemplate_Disssociate_validation(RealmConfig *pRealmConfig);
        DbStatus_e mysql_PeerGroup_Mod_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp);
        DbStatus_e mysql_PeerConfig_Mod_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp);
        DbStatus_e mysql_Lbalgo_Mod_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp);
        DbStatus_e mysql_TracingFilter_Mod_Config_Reqs(TraceReq *req, TraceResp *resp);
        DbStatus_e mysql_LocalHost_Mod_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_TrustedCAConfig_Mod_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_CipherSuiteConfig_Mod_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_StaticRouting_Mod_Config_Reqs(StaticRoutingTableConfigReq *req,StaticRoutingTableConfigResp *resp);

        DbStatus_e mysql_AvaMgr_Set_Config_Reqs(AvaMgrConfig *req,AvaMgrConfigResp *Resp);
        DbStatus_e mysql_RepMgr_Set_Config_Reqs(RepMgrConfig *req,RepMgrConfigResp *Resp);
        DbStatus_e mysql_Dre_Set_Config_Reqs(DreHAConfig *req,DreHAConfigResp *Resp);
        DbStatus_e mysql_LocalHost_Set_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_LocalHostMultihoming_Add_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_TransportType_Set_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_LocalHostMultihoming_Mod_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);
        DbStatus_e mysql_LocalHostMultihoming_Del_Config_Reqs(StackConfigRequest *req, StackConfigResponse *resp);

        DbStatus_e mysql_Logging_Add_Config_Reqs(LoggerConfReq *req, LoggerConfResp *resp);
        DbStatus_e mysql_Logging_Mod_Config_Reqs(LoggerConfReq *req, LoggerConfResp *resp);
        DbStatus_e mysql_Logging_Get_Config_Reqs(LoggerConfReq *req, LoggerConfResp *resp);

        DbStatus_e mysql_Asf_Get_Config_Reqs(ASFConfigReq *req, ASFConfigResp *resp);
        DbStatus_e mysql_AsfGroup_Get_Config_Reqs(ASFConfigReq *req, ASFConfigResp *resp);
        DbStatus_e mysql_AsfGroup_Add_Config_Reqs(ASFConfigReq *req, ASFConfigResp *resp);
        DbStatus_e mysql_Asf_Add_Config_Reqs(ASFConfigReq *req, ASFConfigResp *resp);
        DbStatus_e mysql_AsfGroup_Mod_Config_Reqs(ASFConfigReq *req, ASFConfigResp *resp);
        DbStatus_e mysql_AsfGroup_Del_Config_Reqs(ASFConfigReq *req, ASFConfigResp *resp);
        DbStatus_e mysql_User_Get_Config_Reqs(UserReq* req,UserResp* resp);
        DbStatus_e mysql_User_set_UserID(::UserDetail *pUserInfo);
        DbStatus_e mysql_Role_set_RoleID(::Role *pRole);
        DbStatus_e mysql_RoleName_Modification(::Role *pRole,UserDetailResp *resp);
        DbStatus_e mysql_User_Add_Config_Reqs(UserReq* req,UserResp* resp);
        DbStatus_e mysql_User_Mod_Config_Reqs(UserReq* req,UserResp* resp);
        DbStatus_e mysql_User_Del_Config_Reqs(UserReq* req,UserResp* resp);
        DbStatus_e mysql_Role_Get_Config_Reqs(UserReq* req,UserResp* resp);
        DbStatus_e mysql_FetchAndFill_UserRole(::Role *pRole, UserDetailResp *resp);
        DbStatus_e mysql_User_set_ModifiedBy_And_CreatedBy(::UserDetail *pUserInfo);
        DbStatus_e mysql_FetchAndFill_UserDetail(UserDetail *pUserDetail);
        DbStatus_e mysql_Role_Del_Validation(Role *pRole,UserDetailResp *resp);
        DbStatus_e mysql_TracingFilter_Del_Config_Reqs(TraceReq *req, TraceResp *resp);
        DbStatus_e mysql_Tracing_get_Traceid(TraceConfig *dreTraceReq);


        DbStatus_e mysql_Thf_Enable_Get_Config_Reqs(THFReq *req,THFResp *resp);
        DbStatus_e mysql_Thf_Realm_Get_Config_Reqs(THFReq *req,THFResp *resp);
        DbStatus_e mysql_Thf_Realm_Get_Config_Reqs_when_OtherRealm_size_is_zero(THFReq *req,THFResp *resp);
        DbStatus_e mysql_Thf_Realm_Add_Validation(::THFRealm *pTHFRealm,THFResp *resp,int iIndex);
        DbStatus_e mysql_Thf_Realmaction_Add_Validation(::THFRealm *pTHFRealm,THFResp *resp);
        DbStatus_e mysql_Thf_VHost_Get_Config_Reqs(THFReq *req,THFResp *resp);
        DbStatus_e mysql_Thf_Enable_Set_Config_Reqs(THFReq *req,THFResp *resp);
        DbStatus_e mysql_Thf_defaultBehaviour_Set_Config_Reqs(THFReq *req,THFResp *resp);
        DbStatus_e mysql_Thf_Realm_Add_Config_Reqs(THFReq *req,THFResp *resp);
        DbStatus_e mysql_Thf_vhost_Add_Config_Reqs(THFReq *req,THFResp *resp);
        DbStatus_e mysql_Thf_vhost_Add_Validation(THFVHost *pTHFVHost);
        DbStatus_e mysql_Thf_Realm_Del_Config_Reqs(THFReq *req,THFResp *resp);
        DbStatus_e mysql_Thf_Vhost_Del_Config_Reqs(THFReq *req,THFResp *resp);


        DbStatus_e mysql_AsfGroup_Add_validation(::ASGroupCfg *pASFGroupConfig);
        DbStatus_e mysql_AsfGroup_Mod_validation(::ASGroupCfg *pASFGroupConfig);
        DbStatus_e mysql_PeerDictionaryMap_Add_validation(PeerConfig *pPeerConfig,int iIndex);
        DbStatus_e mysql_PeerSecondaryIp_Add_validation(PeerConfig *pPeerConfig,int iIndex);
        DbStatus_e mysql_RealmRouting_Add_validation(::RealmConfig* pRealmConfig,int iIndex);
        DbStatus_e mysql_RealmRouting_Mod_validation(::RealmConfig* pRealmConfig,int iIndex);
        DbStatus_e mysql_DefaultRoute_Add_validation(RealmConfig *pRealmConfig);
        DbStatus_e mysql_PeerDictionaryMap_Delete_validation(PeerConfig *pPeerConfig,int iIndex);
        DbStatus_e mysql_PeerSecondaryIp_Delete_validation(PeerConfig *pPeerConfig,int iIndex);
        DbStatus_e mysql_AltPeer_Delete_validation(PeerConfig *pPeerConfig);
        DbStatus_e mysql_RealmRouting_Delete_validation(::RealmConfig* pRealmConfig,int iIndex);
        DbStatus_e mysql_PeerGroup_Add_validation(LBPeerGroupReq *pPeerGroupReq);
        DbStatus_e mysql_PeerGroup_Add_validation(LBPeerGroup *pPeerGroup);
        DbStatus_e mysql_PeerGroup_Mod_validation(LBPeerGroup *pPeerGroup);
        DbStatus_e mysql_PeerConfig_Add_validation(::LBPeerGroup* pLBPeerGroup,int iIndex);
        DbStatus_e mysql_PeerConfig_Mod_validation(::LBPeerGroup* pLBPeerGroup,int iIndex);
        DbStatus_e mysql_PeerConfig_Delete_validation(::LBPeerGroup* pLBPeerGroup,int iIndex);
        DbStatus_e mysql_StaticRouting_Add_validation(::StaticRoutingTableConfig* pStaticRoutingTableConfig);
        DbStatus_e mysql_StaticRouting_Mod_validation(::StaticRoutingTableConfig* pStaticRoutingTableConfig);
        DbStatus_e mysql_StaticRouting_Del_validation(::StaticRoutingTableConfig* pStaticRoutingTableConfig);
        DbStatus_e mysql_TransportType_Set_validation(::LocalHost *pLocalHost);
        DbStatus_e mysql_TransportType_Del_validation(::LocalHost *pLocalHost);
        DbStatus_e mysql_LocalHostMutihoming_Add_validation(::LocalHost *pLocalHost);
        DbStatus_e mysql_LocalHostTransport_PrimaryToMultihomingIp_Conflict_Validation(LHTransport *pLHTransport);
        DbStatus_e mysql_User_Add_validation(::UserInfo *pUserInfo);
        DbStatus_e mysql_User_Mod_validation(::UserInfo *pUserInfo);
        DbStatus_e mysql_PeerAndTimerVhost_Add_validation(PeerConfig *pPeerConfig);


        void mysql_set_error_for_LocalTransportTagResponse_Config_Reqs(LocalTransportTagResponse *resp,DbStatus_e iReturn);
        void mysql_set_error_for_LocalTransportTag_Config_Reqs(LocalTransportTagRequest *req,LocalTransportTagResponse *resp,DbStatus_e iReturn);
        void mysql_set_error_for_UserDetailResp_Config_Reqs(UserDetailResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_EmailContentResp_Config_Reqs(EmailContentResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_EmailServerResp_Config_Reqs(EmailServerResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_RolePrevilegeMap_Config_Reqs(Role *pRole,UserDetailResp *resp,DbStatus_e iReturn,int iIndex);
        void mysql_set_error_for_Role_Config_Reqs(Role *pRole,UserDetailResp *resp,DbStatus_e iReturn,string sVariable="");
        DbStatus_e mysql_UserRolePrivilegeMapping_Add_Config_Reqs(Role *req, UserDetailResp *resp);
        DbStatus_e mysql_UserRolePrivilegeMapping_Del_Config_Reqs(Role *req, UserDetailResp *resp);
        void mysql_set_error_for_UserDetail_Config_Reqs(UserDetail *req,UserDetailResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_EmailContent_Config_Reqs(::EmailContent *req,EmailContentResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_EmailServer_Config_Reqs(EmailServer *req,EmailServerResp *resp,DbStatus_e iReturn);
        DbStatus_e mysql_User_Add_validation(::UserDetail *pUserInfo);
        DbStatus_e mysql_RolePrevilageMapping_Add_validation(::Role *pRole,UserDetailResp *resp);

        DbStatus_e mysql_EmailContent_Get_Config_Reqs(EmailContentReq *req, EmailContentResp *resp);
        DbStatus_e mysql_EmailContent_Mod_Config_Reqs(EmailContentReq *req, EmailContentResp *resp);
        DbStatus_e mysql_EmailServer_Get_Config_Reqs(EmailServerReq *req, EmailServerResp *resp);
        DbStatus_e mysql_UserRole_Get_Config_Reqs(UserDetailReq *req, UserDetailResp *resp);
        DbStatus_e mysql_RolePrevilageMapping_NoPrevilage_validation(::Role *pRole,UserDetailResp *resp);
        DbStatus_e mysql_UserDetail_Get_Config_Reqs(UserDetailReq *req, UserDetailResp *resp);
        DbStatus_e mysql_UserDetail_Add_Config_Reqs(UserDetailReq *req, UserDetailResp *resp);
        DbStatus_e mysql_UserDetail_Mod_Config_Reqs(UserDetailReq *req, UserDetailResp *resp);
        DbStatus_e mysql_UserDetail_Del_Config_Reqs(UserDetailReq *req, UserDetailResp *resp);
        DbStatus_e mysql_UserRole_Add_Config_Reqs(UserDetailReq *req, UserDetailResp *resp);
        DbStatus_e mysql_UserRole_Del_Config_Reqs(UserDetailReq *req, UserDetailResp *resp);
        DbStatus_e mysql_UserRole_Mod_Config_Reqs(UserDetailReq *req, UserDetailResp *resp);
        DbStatus_e mysql_EmailServer_Set_Config_Reqs(EmailServerReq *req, EmailServerResp *resp);
        DbStatus_e mysql_EmailServer_Del_Config_Reqs(EmailServerReq *req, EmailServerResp *resp);
        DbStatus_e mysql_EmailServer_resultset_to_protoBuff(sql::ResultSet *pRes,EmailServerResp *resp);
        DbStatus_e mysql_LocalTransportTag_resultset_to_protoBuff(sql::ResultSet *pRes,LocalTransportTagResponse *resp);
        DbStatus_e mysql_EmailContent_resultset_to_protoBuff(sql::ResultSet *pRes,EmailContentResp *resp);
        DbStatus_e mysql_Role_resultset_to_protoBuff(sql::ResultSet *pRes,UserDetailResp *resp);
        DbStatus_e mysql_User_Mod_validation(::UserDetail *pUserInfo);
        DbStatus_e mysql_RolePrevilageMapping_Mod_validation(::Role *pRole,UserDetailResp *resp);
        DbStatus_e mysql_UserDetail_resultset_to_protoBuff(sql::ResultSet *pRes,UserDetailResp *resp);
        DbStatus_e mysql_PrevilegeMapping_resultset_to_protoBuff(Role *pRole);
        DbStatus_e mysql_Previlege_resultset_to_protoBuff(Previlage *pPrevilage);
        DbStatus_e mysql_UserRole_Get_Config_Reqs(::Roles *pRoles, UserDetailResp *resp);
        DbStatus_e mysql_UserRole_Get_Config_Reqs(::Role *pRole, UserDetailResp *resp);

        void mysql_set_error_for_Previlages_Config_Reqs(Previlages *req,UserDetailResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_Previlage_Config_Reqs(Previlage *req,UserDetailResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_Thf_Config_Reqs(::THFVHost *req, THFResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_Thf_Config_Reqs(::THFRealm *req, THFResp *resp,DbStatus_e iReturn, int iIndex=-1);
        void mysql_set_error_for_Thf_Config_Reqs(THFReq *req, THFResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_Thf_Config_Reqs(THFResp *resp,DbStatus_e iReturn);
        DbStatus_e mysql_Thf_resultset_to_protoBuff(sql::ResultSet *pRes,THFResp *resp);
        DbStatus_e mysql_Previleges_resultset_to_protoBuff(Previlages *pPrevilages);
        DbStatus_e mysql_THFRealm_resultset_to_protoBuff(sql::ResultSet *pRes,THFResp *resp);
        void mysql_check_and_add_THFRealm_resultset(sql::ResultSet *pRes,THFResp *resp);
        DbStatus_e mysql_add_THFRealm_resultset_with_otherrealm(sql::ResultSet *pRes,::THFRealm *localRealmObj);
        void mysql_add_THFRealm_resultset(sql::ResultSet *pRes,THFResp *resp);
        DbStatus_e mysql_TransportTag_Add_Config_Reqs(::LocalHost *pLocalHost, StackConfigResponse *resp,int iIndex);
        DbStatus_e mysql_THFVHost_resultset_to_protoBuff(sql::ResultSet *pRes,THFResp *resp);
        DbStatus_e mysql_Previlage_GetConfig_Reqs(UserDetailReq *req,UserDetailResp *resp);

        DbStatus_e mysql_CmfRealmTemplate_Del_Config_Reqs(TemplateReq *req, TemplateResp *resp);
        DbStatus_e mysql_CmfPeerTemplate_Del_Config_Reqs(TemplateReq *req, TemplateResp *resp);
        DbStatus_e mysql_CmfPeerTemplate_Mod_Validation( ::CMFPeerTemplate *pCMFPeerTemplate);
        DbStatus_e mysql_CmfPeerTemplate_Add_Config_Reqs(TemplateReq *req, TemplateResp *resp);
        DbStatus_e mysql_CmfRealmTemplate_Add_Config_Reqs(TemplateReq *req, TemplateResp *resp);
        DbStatus_e mysql_CmfRealmTemplate_Mod_Config_Reqs(TemplateReq *req, TemplateResp *resp);
        DbStatus_e mysql_CmfPeerTemplate_Mod_Config_Reqs(TemplateReq *req, TemplateResp *resp);
        DbStatus_e mysql_CmfPeerTemplate_Get_Config_Reqs(TemplateReq *req, TemplateResp *resp);
        DbStatus_e mysql_CmfRealmTemplate_Get_Config_Reqs(TemplateReq *req, TemplateResp *resp);
        DbStatus_e mysql_PeerTemplate_resultset_to_protoBuff(sql::ResultSet *pRes,TemplateResp *resp);
        DbStatus_e mysql_RealmTemplate_resultset_to_protoBuff(sql::ResultSet *pRes,TemplateResp *resp);
        DbStatus_e mysql_CmfPeerTemplate_Del_Validation(CMFPeerTemplate *pCMFPeerTemplate, TemplateResp *resp);
        DbStatus_e mysql_CmfRealmTemplate_Del_Validation(CMFRealmTemplate *pCMFRealmTemplate, TemplateResp *resp);
        DbStatus_e mysql_fetch_and_fill_RealmTemplate_id(::CMFRealmTemplate *req, TemplateResp *resp);
        DbStatus_e mysql_fetch_and_fill_PeerTemplate_id(::CMFPeerTemplate *req, TemplateResp *resp);
        void mysql_set_error_for_TemplateResp_Config_Reqs(::TemplateReq *req, TemplateResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_CmfDiaRealmTemplate_Config_Reqs(::CMFRealmTemplate *req, TemplateResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_CmfDiaPeerTemplate_Config_Reqs(::CMFPeerTemplate *req, TemplateResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_Template_config_Reqs(TemplateResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_StackConfigResponse_Config_Reqs(StackConfigResponse *resp,DbStatus_e iReturn);
        void mysql_set_error_for_StaticRoutingTableConfigResp_Config_Reqs(StaticRoutingTableConfigResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_StaticRouting_Config_Reqs(StaticRoutingTableConfig *pStaticRoutingTableConfig,StaticRoutingTableConfigResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_drecfgResp_Config_Reqs(DRECfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_LBPeerGroupResp_Config_Reqs(LBPeerGroupResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_DynDictionaryResponse_Config_Reqs(DynDictionaryResponse *resp,DbStatus_e iReturn);
        void mysql_set_error_for_AvaMgrConfigResp_Config_Reqs(AvaMgrConfigResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_RepMgrConfigResp_Config_Reqs(RepMgrConfigResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_DreHAConfigResp_Config_Reqs(DreHAConfigResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_LoggerConfResp_Config_Reqs(LoggerConfResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_UserResp_Config_Reqs(UserResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_TraceResp_Config_Reqs(TraceResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_AsfConfResp_Config_Reqs(ASFConfigResp *resp,DbStatus_e iReturn);
        DbStatus_e check_for_requestid(PeersConfig *req,DRECfgResp *resp);
        void Copy_PeersConfig_request_to_Response(PeersConfig *req,DRECfgResp *resp);
        void Copy_DRECfgResp_localresponse_to_Reponse(DRECfgResp *localresp,DRECfgResp *resp);

        // DTF : Transformation-plugin and dictionary-provisioning
        DbStatus_e mysql_Dictionary_Get_Config_Reqs(DictionaryConfigReq *Req,DRECfgResp *Resp);
        DbStatus_e mysql_Dictionary_SetStatus_Config_Reqs(DictionaryConfigReq *Req,DRECfgResp *Resp);
        DbStatus_e mysql_TransPlugin_Get_Config_Reqs(TransformPluginConfigReq *Req,DRECfgResp *Resp);
        DbStatus_e mysql_TransPlugin_SetStatus_Config_Reqs(TransformPluginConfigReq *Req,DRECfgResp *Resp);
        DbStatus_e mysql_TransPlugin_Reload_Config_Reqs(TransformPluginConfigReq *Req,DRECfgResp *Resp);
        DbStatus_e mysql_DictionaryConfig_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp);
        DbStatus_e mysql_TransformPluginConfig_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp);
        DbStatus_e mysql_TransformPluginConfig_setDictionaryName_resultset_to_protoBuff(TransformPluginConfig *pTransformPluginConfig);
        DbStatus_e mysql_Dictionary_SetStatus_Validation(DictionaryConfig *pDictionaryConfig);
        DbStatus_e mysql_TransPlugin_SetStatus_Validation(TransformPluginConfig *pTransformPluginConfig, DRECfgResp *resp);
        DbStatus_e mysql_TransPlugin_Reload_Validation(TransformPluginConfig *pTransformPluginConfig, DRECfgResp *resp);

        // DTF : Transformation-plugin and dictionary-provisioning
        void mysql_set_error_for_Dictionary_Config_Reqs(DRECfgResp *resp, DbStatus_e iReturn);
        void mysql_set_error_for_TransPlugin_Config_Reqs(DRECfgResp *resp, DbStatus_e iReturn);

        //CMF: Congestion management function
        void mysql_set_error_for_CMF_config_Reqs(CMFTriggerResp *Resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(CMFActionResp *resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(CMFActionTriggerResp *Resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(CMFLevelResp *Resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(RuleConfigResp *Resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(PriorityConfigResp *Resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(TemplateResp *Resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(CMFConfigResp *Resp, DbStatus_e iReturn);
        DbStatus_e mysql_CongRuleConfig_resultset_to_protoBuff(sql::ResultSet *pRes, RuleConfigResp *resp);
        DbStatus_e mysql_CMFActionForTrigger_resultset_to_protoBuff(sql::ResultSet *pRes, CMFActionTriggerResp *resp);
        DbStatus_e mysql_CMFLevel_resultset_to_protoBuff(sql::ResultSet *pRes, CMFLevelResp *resp);
        DbStatus_e mysql_Cmf_Get_Action_For_Trigger_Config_Req(CMFActionTriggerReq *req, CMFActionTriggerResp *resp);
        DbStatus_e mysql_Cmf_Get_CMFLevel_Config_Req(CMFLevelReq *req, CMFLevelResp *resp);
        DbStatus_e mysql_Cmf_Get_CMFRules_Config_Req(RuleConfigReq *req, RuleConfigResp *resp);
        DbStatus_e mysql_Cmf_Add_CMFRule_Validation(RuleConfig *req);
        DbStatus_e mysql_Cmf_Add_CMFRule_Config_Req(RuleConfigReq *req, RuleConfigResp *resp);
        DbStatus_e mysql_Cmf_Mod_CMFRule_Validation(RuleConfig *req);
        DbStatus_e mysql_Cmf_Mod_CMFRule_Config_Req(RuleConfigReq *req, RuleConfigResp *resp);
        DbStatus_e mysql_Cmf_Del_CMFRule_Validation(RuleConfig *req);
        DbStatus_e mysql_Cmf_Del_CMFRule_Config_Req(RuleConfigReq *req, RuleConfigResp *resp);
        DbStatus_e mysql_Cmf_Set_CMFRuleStatus_Validation(RuleConfig *req);
        DbStatus_e mysql_Cmf_Set_CMFRuleStatus_Config_Req(RuleConfigReq *req, RuleConfigResp *resp);
        DbStatus_e mysql_Cmf_Set_CommandCodePriority_Validation(PriorityConfig *req);
        DbStatus_e mysql_Cmf_Set_CommandCodePriority_Config_Req(PriorityConfigReq *req, PriorityConfigResp *resp);
        DbStatus_e mysql_Cmf_Set_CMFRuleStatus_Validation(PriorityConfig *req);
        DbStatus_e mysql_Cmf_Set_ApplicationIdPriority_Config_Req(PriorityConfigReq *req, PriorityConfigResp *resp);
        DbStatus_e mysql_Cmf_Get_CMFAction_Config_Req(CMFActionReq *Req, CMFActionResp *Resp);
        DbStatus_e mysql_CMFAction_resultset_to_protoBuff(sql::ResultSet *pRes, CMFActionResp *resp);
        DbStatus_e mysql_CMFTrigger_resultset_to_protoBuff(sql::ResultSet *pRes, CMFTriggerResp *Resp);
        DbStatus_e mysql_Cmf_Get_CMFTrigger_Config_Req(CMFTriggerReq *Req, CMFTriggerResp *Resp);
        DbStatus_e mysql_CMFActionsforEachTrigger_resultset_to_protoBuff(CMFAction *pCMFAction);
        DbStatus_e mysql_CMFTriggerInMapping_resultset_to_protoBuff(CMFTrigger *pCMFTrigger);
        DbStatus_e mysql_Cmf_Get_DiaPriority_Config_Req(PriorityConfigReq *req, PriorityConfigResp *resp);
        DbStatus_e mysql_CMF_CC_Priority_resultset_to_protoBuff(sql::ResultSet *pRes, PriorityConfigResp *resp);
        DbStatus_e mysql_CMF_AppId_Priority_resultset_to_protoBuff(sql::ResultSet *pRes, PriorityConfigResp *resp);
        DbStatus_e mysql_Cmf_Add_Priority_Config_Req(PriorityConfigReq *req, PriorityConfigResp *resp);
        DbStatus_e mysql_Cmf_Mod_Priority_Config_Req(PriorityConfigReq *req, PriorityConfigResp *resp);
        DbStatus_e mysql_Cmf_Del_Priority_Config_Req(PriorityConfigReq *req, PriorityConfigResp *resp);

        // SDTF
        void mysql_set_error_for_Sdtf_Config_Reqs(SDTFResp *resp, DbStatus_e iReturn);
        DbStatus_e mysql_Sdtf_Get_SDTFRules_Config_Reqs(SDTFReq *req, SDTFResp *resp);
        DbStatus_e mysql_SDTF_Add_SDTFRule_Validation(SDTFRule *pSDTFRule);
        DbStatus_e mysql_SDTF_Add_SDTFRule_Config_Req(SDTFReq *req, SDTFResp *resp);
        DbStatus_e mysql_SDTF_Mod_SDTFRule_Validation(SDTFRule *pSDTFRule);
        DbStatus_e mysql_SDTF_Mod_SDTFRule_Config_Req(SDTFReq *req, SDTFResp *resp);
        DbStatus_e mysql_SDTF_Del_SDTFRule_Validation(SDTFRule *pSDTFRule);
        DbStatus_e mysql_SDTF_Del_SDTFRule_Config_Req(SDTFReq *req, SDTFResp *resp);
        DbStatus_e mysql_SDTF_Set_SDTFRule_Status_Validation(SDTFRule *pSDTFRule);
        DbStatus_e mysql_SDTF_Set_SDTFRule_Status_Config_Req(SDTFReq *req, SDTFResp *resp);
        DbStatus_e mysql_Sdtf_Get_SDTF_EnableStatus_Config_Req(SDTFResp *resp);
        DbStatus_e mysql_SDTF_Set_SDTF_EnableStatus_Validation(string featureName);
        DbStatus_e mysql_SDTF_Set_SDTF_EnableStatus_Config_Req(SDTFReq *req, SDTFResp *resp);
        DbStatus_e mysql_fetch_and_fill_SDTF_Rule_Id_And_Status(SDTFRule *pSDTFRule);
        DbStatus_e mysql_fetch_and_fill_SDTF_Rule_Config(SDTFRule *pSDTFRule);

    private:
        void mysql_set_error_for_CMF_config_Reqs(CMFTrigger *req, CMFTriggerResp *resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(CMFTrigger *Req, CMFActionTriggerResp *Resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(CMFLevel *Req, CMFLevelResp *Resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(RuleConfig *Req, RuleConfigResp *Resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(PriorityConfig *Req, PriorityConfigResp *Resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(TemplateReq *Req, TemplateResp *Resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(CMFConfigReq *Req, CMFConfigResp *Resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(CMFAction *req, CMFActionResp *resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(AppIdPriority *req, PriorityConfigResp *resp, DbStatus_e iReturn);
        void mysql_set_error_for_CMF_config_Reqs(CCPriority *req, PriorityConfigResp *resp, DbStatus_e iReturn);

        void mysql_set_error_for_LocalHost_Config_Reqs(::LocalHost *pLocalHost, StackConfigResponse *resp,DbStatus_e iReturn);
        void mysql_set_error_for_LHTransport_Config_Reqs(::LocalHost *pLocalHost, StackConfigResponse *resp,DbStatus_e iReturn,int iIndex);
        void mysql_set_error_for_Lbalgo_Config_Reqs(::LBAlgorithm *pLBAlgorithm, LBPeerGroupResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_PeerGroup_Config_Reqs(::LBPeerGroup *pLBPeerGroup, LBPeerGroupResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_PeerGroupMap_Config_Reqs(::LBPeerGroup *pLBPeerGroup, LBPeerGroupResp *resp,DbStatus_e iReturn,int iIndex);
        void mysql_set_error_for_DefaultRoute_Config_Reqs(RealmConfig *pRealmConfig, DRECfgResp *resp,DbStatus_e iReturn,int iIndex);
        void mysql_set_error_for_LocalHost_Config_Reqs(LocalHostConfig *pLocalHostConfig, DRECfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_Dictionary_Config_Reqs(::Dictionary *pDictionary, DynDictionaryResponse *resp,DbStatus_e iReturn);
        void mysql_set_error_for_AvaMgr_Config_Reqs(AvaMgrConfig *pAvaMgrConfig, AvaMgrConfigResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_Logging_Config_Reqs(LoggerConf *pLoggerConf, LoggerConfResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_Peer_Config_Reqs(PeerConfig *pPeerConfig, DRECfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_Peer_Config_Reqs(PeerConfig *pPeerConfig, DRECfgResp *resp, std::string **dictName, DbStatus_e iReturn);
        void mysql_set_error_for_PrimaryIP_with_SecondaryIP(PeerConfig *pPeerConfig, DRECfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_Peer_Config_Reqs(PeerConfig *pPeerConfig, DRECfgResp *resp, int appId, DbStatus_e iReturn);
        void mysql_set_error_for_sourcePort(PeerConfig *pPeerConfig,DRECfgResp *resp,DbStatus_e iReturn,int sourcePort, int transportType);
        void mysql_set_error_for_PeerDictionaryMap_Config_Reqs(PeerConfig *pPeerConfig, DRECfgResp *resp,DbStatus_e iReturn,int iIndex);
        void mysql_set_error_for_PeerSecondaryIp_Config_Reqs(PeerConfig *pPeerConfig, DRECfgResp *resp,DbStatus_e iReturn,int iIndex);
        void mysql_set_error_for_SecondaryIP_with_PrimaryIP(PeerConfig *pPeerConfig, DRECfgResp *resp,DbStatus_e iReturn,int iIndex, string peerIP);
        void mysql_set_error_for_Realm_Config_Reqs(RealmConfig *pRealmConfig, DRECfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_RealmRouting_Config_Reqs(RealmConfig *pRealmConfig, DRECfgResp *resp,DbStatus_e iReturn,int iIndex);
        void mysql_set_error_for_User_Config_Reqs(UserInfo *pUserConfig,UserResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_Tracing_Config_Reqs(::TraceReq *pTraceReq, TraceResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_TracingFilter_Config_Reqs(::TraceConfig *pTraceConfig, TraceResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_TracingFilter_Config_Reqs(::TraceConfig *pTraceConfig, TraceResp *resp,DbStatus_e iReturn, string& filterName);
        void mysql_set_error_for_Asf_Config_Reqs(::ASGroupCfg *pASGroupConf, ASFConfigResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_Common_Config_Reqs(StackConfigResponse *resp,DbStatus_e iReturn);
        void mysql_set_error_for_AsfRespTime_Config_Reqs(::ASFConfiguration *pASFConf, ASFConfigResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_TrustedCAConfig_Config_Reqs(::TrustedCAConfiguration *pTrustedCAConfiguration, StackConfigResponse *resp,DbStatus_e iReturn);
        void mysql_set_error_for_CipherSuiteConfig_Config_Reqs(::TLSCipherConfig *pTLSCipherConfig, StackConfigResponse *resp,DbStatus_e iReturn);
        void mysql_set_error_for_MultiHoming_Config_Reqs(::LHTransport *pLHTransport, StackConfigResponse *resp,DbStatus_e iReturn,int iIndex);

        // SDTF
        void mysql_set_error_for_SDTF_config_Reqs(SDTFRule *req, SDTFResp *resp, DbStatus_e iReturn);
        DbStatus_e mysql_CongSDTFRule_resultset_to_protoBuff(sql::ResultSet *pRes, SDTFResp *resp);
        DbStatus_e mysql_Cong_FeatureStatus_resultset_to_protoBuff(sql::ResultSet *pRes, SDTFResp *resp);

        //DTF
        void mysql_set_error_for_Dictionary_Config_Reqs(DictionaryConfig *pDictionaryConfig, DRECfgResp *resp, DbStatus_e iReturn);
        void mysql_set_error_for_TransPlugin_Config_Reqs(TransformPluginConfig *pTransformPluginConfig, DRECfgResp *resp, DbStatus_e iReturn);
        void mysql_set_error_for_TransPlugin_Config_Reqs(TransformPluginConfig *pTransformPluginConfig, DRECfgResp *resp, string dictName, DbStatus_e iReturn);

        DbStatus_e Set_Log_Configuration(LoggerConf *pLoggingConfig);

        DbStatus_e mysql_PeerAndTimer_Add_validation(PeerConfig *pPeerConfig);
        DbStatus_e mysql_PeerAndTimer_Dictionary_Add_validation(PeerConfig *pPeerConfig, DRECfgResp *resp);
        DbStatus_e mysql_PeerAndTimer_Dictionary_Mod_validation(PeerConfig *pPeerConfig, DRECfgResp *resp);
        DbStatus_e mysql_AlternatePeer_Validation(PeerConfig *pPeersConfig);
        DbStatus_e mysql_Peer_State_Validation(PeerConfig *pPeerConfig,PeersConfig *req);
        DbStatus_e mysql_Peer_State_for_Dictionary_Validation(PeerConfig *pPeerConfig);
        DbStatus_e mysql_Get_RealmName_From_RealmRouting(PeerConfig *localPeerConfig,char *pRealmName);
        DbStatus_e mysql_DictionaryName_resultset_to_peer_protoBuff(sql::ResultSet *pRes,PeerConfig *pPeerConfig,int iIndex);
        DbStatus_e mysql_SecondaryIp_resultset_to_peer_protoBuff(sql::ResultSet *pRes,PeerConfig *pPeerConfig,int iIndex);
        DbStatus_e mysql_PeerGroupid_to_protobuf(sql::ResultSet *pRes,::LBPeerGroup *resp);
        DbStatus_e mysql_PeerGroupMap_RejectRequest_Validation(LBPeerGroup *pLBPeerGroup);
        DbStatus_e mysql_Peerid_to_protobuf(sql::ResultSet *pRes,::LBPeerGroup *resp,int iIndex);

        DbStatus_e mysql_peer_resultset_to_realm_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp);
        DbStatus_e mysql_add_peer_resultset_to_DestinationProtoBuff(sql::ResultSet *pRes,RealmConfig* localRealmObj);
        DbStatus_e mysql_add_peer_resultset_to_RealmProtoBuff(sql::ResultSet *pRes,RealmsConfig* localRealmsObj);
        DbStatus_e mysql_User_resultset_to_protoBuff(sql::ResultSet *pRes,UserResp *resp);
        DbStatus_e mysql_StaticRouteConfig_resultset_to_protoBuff(sql::ResultSet *pRes,StaticRoutingTableConfigResp *resp);
        DbStatus_e mysql_SCTPConfig_resultset_to_protoBuff(sql::ResultSet *pRes,StackConfigResponse *resp);
        DbStatus_e mysql_StackGeneralConfig_resultset_to_protoBuff(sql::ResultSet *pRes,StackConfigResponse *resp);
        DbStatus_e mysql_TrustedCAConfig_resultset_to_protoBuff(sql::ResultSet *pRes,StackConfigResponse *resp);
        DbStatus_e mysql_TLSConfig_resultset_to_protoBuff(sql::ResultSet *pRes,StackConfigResponse *resp);
        DbStatus_e mysql_CipherSuiteConfig_resultset_to_protoBuff(sql::ResultSet *pRes,StackConfigResponse *resp);
        DbStatus_e mysql_AsfGroup_resultset_to_protoBuff(sql::ResultSet *pRes,ASFConfigResp *resp);
        DbStatus_e mysql_Asf_resultset_to_protoBuff(sql::ResultSet *pRes,ASFConfigResp *resp);

        void mysql_check_and_Add_Peer_resultset(sql::ResultSet *pRes,DRECfgResp *resp);
        DbStatus_e mysql_LocalHostConfig_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp);
        DbStatus_e mysql_peer_and_peerTimer_resultset_to_protoBuff(sql::ResultSet *pResPeerAndTimerT, DRECfgResp *resp);
        DbStatus_e mysql_peer_and_peerTimer_withstat_resultset_to_protoBuff(sql::ResultSet *pResPeerAndTimerT,
                DRECfgResp *resp);
        DbStatus_e mysql_realm_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp);
        DbStatus_e mysql_realmrouting_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp);
        DbStatus_e mysql_add_realm_resultset_to_RealmProtoBuff(sql::ResultSet *pRes,RealmsConfig* localRealmsObj);
        DbStatus_e mysql_add_realmrouting_resultset_to_RealmProtoBuff(sql::ResultSet *pRes,RealmsConfig* localRealmsObj);
        DbStatus_e mysql_add_realm_resultset_to_DestinationProtoBuff(sql::ResultSet *pRes,RealmConfig* localRealmObj);
        DbStatus_e mysql_add_realmrouting_resultset_to_DestinationProtoBuff(sql::ResultSet *pRes,RealmConfig* localRealmObj);
        DbStatus_e mysql_defaultRoute_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp);
        DbStatus_e mysql_TracingFilter_resultset_to_protoBuff(sql::ResultSet *pRes,TraceResp *resp);
        DbStatus_e unset_tracing_variables_before_sending_to_dre(TraceConfig *req);
        DbStatus_e mysql_Tracing_filterid_to_protoBuff(sql::ResultSet *pRes,TraceConfig *resp);
        DbStatus_e mysql_AsfGroup_AsfGroupid_to_protoBuff(sql::ResultSet *pRes,::ASGroupCfg *resp);
        DbStatus_e mysql_Tracing_resultset_to_protoBuff(sql::ResultSet *pRes,TraceResp *resp);

        void mysql_check_and_Add_realm_resultset(sql::ResultSet *pRes,DRECfgResp *resp);
        void mysql_check_and_Add_realmrouting_resultset(sql::ResultSet *pRes,DRECfgResp *resp);
        void mysql_check_and_add_peer_peerTimer_dictionary_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp);
        //void mysql_check_and_add_peer_peerTimer_SecondaryIp_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp);
        void mysql_check_and_add_peer_peerTimer_stat_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp);
        void mysql_add_peer_peerTimer_resultset_to_protoBuff(sql::ResultSet *pRes,PeersConfig  *pPeersConfig);
        void mysql_add_dictionary_resultset_to_protoBuff(sql::ResultSet *pRes,::PeerConfig* pPeerConfig);
        void mysql_add_SecondaryIp_resultset_to_protoBuff(sql::ResultSet *pRes,::PeerConfig* pPeerConfig);
        void mysql_add_stat_resultset_to_protoBuff(sql::ResultSet *pRes,::PeerConfig* pPeerConfig);
        void mysql_check_and_Add_defaultRoute_resultset(sql::ResultSet *pRes,DRECfgResp *resp);
        DbStatus_e mysql_add_defaultRoute_resultset_to_RealmProtoBuff(sql::ResultSet *pRes,RealmsConfig* localRealmsObj);
        DbStatus_e mysql_add_defaultRoute_resultset_to_DestinationProtoBuff(sql::ResultSet *pRes,RealmConfig* localRealmObj);
        DbStatus_e mysql_DefaultRoute_resultset_to_protoBuff(sql::ResultSet *pResDefaultR,DRECfgResp *resp);
        DbStatus_e mysql_PeerGroup_resultset_to_protoBuff(sql::ResultSet *pRes,LBPeerGroupResp *resp);
        void mysql_check_and_Add_PeerGroup_resultset(sql::ResultSet *pRes,LBPeerGroupResp *resp);
        void mysql_add_PeerGroup_resultset_to_PeerGroupProtoBuff(sql::ResultSet *pRes,LBPeerGroupResp *resp);
        void mysql_add_PeerGroup_resultset_to_PeerProtoBuff(sql::ResultSet *pRes,::LBPeerGroup *localPeerGroup);
        DbStatus_e mysql_Lbalgo_resultset_to_protoBuff(sql::ResultSet *pRes,LBPeerGroupResp *resp,int component);
        DbStatus_e mysql_PeerConfig_resultset_to_protoBuff(sql::ResultSet *pRes,LBPeerGroupResp *resp);
        DbStatus_e mysql_AvaMgrConfig_resultset_to_protoBuff(sql::ResultSet *pRes,AvaMgrConfigResp *resp);
        DbStatus_e mysql_DictionaryConfig_resultset_to_protoBuff(sql::ResultSet *pRes,DynDictionaryResponse *resp);
        DbStatus_e mysql_LocalHost_resultset_to_protoBuff(sql::ResultSet *pRes,StackConfigResponse *resp);
        DbStatus_e mysql_LocalHost_resultset_to_LHTransport_protoBuff(sql::ResultSet *pRes,LocalHost *pLocalHost);


        DbStatus_e mysql_LocalHost_Mod_Config_Reqs(LocalHostConfig *pLocalHostConfig,DRECfgResp *resp);
        DbStatus_e mysql_DefaultRoute_Mod_Config_Reqs_Through_Realm(RealmConfig *pRealmConfig,DRECfgResp *resp, int iDestinationIndex);
        DbStatus_e check_last_localTransport_configuration(LocalHost *pLocalHost,int iIndex);
        DbStatus_e check_last_PeerDicationary_configuration(::PeerConfig *pPeerConfig,int iIndex);

        void copy_DestinationConfig(RealmConfig *pToRealmConfig,int iDestinationIndex,RealmConfig *pFromRealmConfig);
        void copy_RealmOnlyConfig(RealmsConfig *pRealmsConfig,int iDestinationIndex,RealmConfig *pFromRealmConfig);
        void copy_RealmConfig(DRECfgResp *resp,RealmConfig *pRealmConfig,int iDestinationIndex);
        void copy_RealmConfig(DRECfgResp *resp,RealmConfig *pRealmConfig);
        void copy_PeerConfig(DRECfgResp *resp,PeerConfig *pPeerConfig);
        void copy_LocalHostConfig(DRECfgResp *resp,LocalHostConfig *pLocalHostConfig);
        void copy_PeerGroupConfig(LBPeerGroupResp *resp,::LBPeerGroup *pLBPeerGroup);
        void copy_PeerConfig(LBPeerGroupResp *resp,LBPeerGroup *pLBPeerGroup,int Index);
        LBPeerGroup* copy_checkPeerGroupAlreadyPresent(LBPeerGroupResp *resp,LBPeerGroup *pLBPeerGroup);
        void copy_LBAlgorithmConfig(LBPeerGroupResp *resp,::LBAlgorithm *pLBAlgorithm);
        void copy_AvaMgrConfig(AvaMgrConfigResp *resp,AvaMgrConfig *pAvaMgrConfig);
        void Copy_ResultSet_To_AvaMgrConfig(sql::ResultSet *pRes,AvaMgrConfig *pFromAvaMgrConfig,AvaMgrConfig *pToAvaMgrConfig);


        DbStatus_e mysql_LoggingConfig_resultset_to_protoBuff(sql::ResultSet *pRes,LoggerConfResp *resp);
};


#endif
