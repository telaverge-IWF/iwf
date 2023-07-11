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


#ifndef CMGR_IWF_DB_INTERFACE_H
#define CMGR_IWF_DB_INTERFACE_H

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <driver.h>
#include <string.h>
#include <stdio.h>


#include "QueryIwfPB.h"
#include "MysqlInterfacePB.h"
#include "CommonStructure.h"
#include "config.h"
#include "ConfigManager.h"

#include "iwfconfig_def.h"
class ConfigManager;

class CMgrIwfDbInterface : public QueryIwf_PB
{
    public:
        MysqlInterfacePB m_dbHandle;
        ConfigManager *m_ConfigManager;
        ConfigManagerAlarms *m_ConfigManagerAlarms;
        CMgrIwfDbInterface(std::string sHostName,std::string sUserName,std::string sPassword,std::string sDataBase,ConfigManager *pConfigManager,ConfigManagerAlarms *pConfigManagerAlarms);

        void mysql_set_error_for_LocalHostConfig_Config_Reqs(IwfLocalHostConfig *pIwfLocalHostConfig, IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFLocalSSN_Config_Reqs(IwfLocalSSNConfig *pIwfLocalSSNConfig,IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFLocalConfig_Config_Reqs(IwfLocalHostConfig *pIwfLocalHostConfig, IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFLocalSSNMapping_Config_Reqs(IwfLocalHostConfig *pIwfLocalHostConfig, IWFCfgResp *resp,DbStatus_e iReturn,int iIndex);
        DbStatus_e Fill_IWFProtocolFamily_protobuff(IwfLocalHostConfig *pIwfLocalHostConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFLocalConfig_protobuff(IwfLocalHostConfig *pIwfLocalHostConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFLocalSSNMapping_protobuff(IwfLocalHostConfig *pIwfLocalHostConfig,IWFCfgResp *resp,int iIndex);
        DbStatus_e Fill_IWFLocalSSN_protobuff(IwfLocalSSNConfig *pIwfLocalSSNConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFLocalHostConfig_Validation(IwfLocalHostConfig *pIwfLocalHostConfig, IWFCfgResp *resp);
        DbStatus_e mysql_IWFLocalSSNConfig_Add_Validation(IwfLocalSSNConfig *pIwfLocalSSNConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFLocalConfig_Add_Config_Reqs(IwfLocalHostsConfig *pIwfLocalHostsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFLocalConfig_Mod_Config_Reqs(IwfLocalHostsConfig *pIwfLocalHostsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFLocalConfig_Del_Config_Reqs(IwfLocalHostsConfig *pIwfLocalHostsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFLocalConfig_Get_Config_Reqs(IwfLocalHostsConfig *pIwfLocalHostsConfig,IWFCfgResp *resp);
        DbStatus_e CheckAndModifyAssociationAspId(IwfLocalHostConfig *pIwfLocalHostConfig);

        void mysql_set_error_for_iwfCfgResp_Config_Reqs(IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFSigtranAssocSet_Config_Reqs(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig,IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFSigtranAssociation_Config_Reqs(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig,IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp,DbStatus_e iReturn,int iIndex);
        void mysql_set_error_for_IWFSigtranMultihoming_Config_Reqs(IwfSigtranMultihomingConfig *pIwfSigtranMultihomingConfig,IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFSctpEndpoint_Config_Reqs(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFSigtranSCTPProfile_Config_Reqs(IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig,IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFSigtranSetMapping_Config_Reqs(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig,IWFCfgResp *resp,DbStatus_e iReturn,int iIndex);
        DbStatus_e Fill_IWFSigtranAssocSet_protobuff(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFSigtranAssociation_protobuff(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFSigtranAssociations_protobuff(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFSigtranMultihoming_protobuff(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp,int iIndex);
        DbStatus_e Fill_IWFSigtranAssocSetMapping_protobuff(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig,IWFCfgResp *resp,int iIndex);
        DbStatus_e Fill_IWFSctpEndpoint_protobuff(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp);
        DbStatus_e Validate_IWFLocalSctpEndpoint(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp);
        DbStatus_e ValidateLocalHostIP(std::vector<string>& ipAddress, int port=0, bool isIPv6=false);
        DbStatus_e Fill_IWFSigtranSCTPProfile_protobuff(IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFSigtranAssociationSetConfigForAssociation(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig);
        DbStatus_e Fill_IWFSigtranAssocAndAssocSet_protobuff(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig,IWFCfgResp *resp,IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig);
        DbStatus_e IWFSigtranAssociationsConfig_check_already_entered(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,sql::ResultSet *pRes);
        DbStatus_e Fill_IWFSigtranAssocAndAssocSet_protobuff(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig,IWFCfgResp *resp,IwfSigtranAssociationSetsConfig *pIwfSigtranAssociationSetsConfig);
        DbStatus_e IWFSigtranAssociationSetsConfig_check_already_entered(IwfSigtranAssociationSetsConfig *pIwfSigtranAssociationSetsConfig,sql::ResultSet *pRes);
        void Fill_only_IWFSigtranAssociation(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig,sql::ResultSet *pRes);
        DbStatus_e mysql_IwfSigtranSctpEndPoints_Add_Config_Reqs(IwfSigtranSctpEndPointsConfig *pIwfSigtranSctpEndPointsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFSctpEndPoint_Validation(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFSctpEndPoint_Check_Association_isEnabled(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFSctpEndPoint_Mod_Validation(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranSctpEndPoints_Mod_Config_Reqs(IwfSigtranSctpEndPointsConfig *pIwfSigtranSctpEndPointsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFCheck_InMultiHoming(string sEndPointName);
        DbStatus_e mysql_IWFCheck_InAssociation(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig);
        DbStatus_e mysql_IWFSctpEndPoint_Del_Validation(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranSctpEndPoints_Del_Config_Reqs(IwfSigtranSctpEndPointsConfig *pIwfSigtranSctpEndPointsConfig,IWFCfgResp *resp);
        DbStatus_e IWFSigranAssociationsConfig_Fill_For_SctpEndPoint(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IwfSigtranSctpEndPointsConfig *pIwfSigtranSctpEndPointsConfig,IWFCfgResp *resp);
        DbStatus_e IWFSigranAssociationsConfig_Fill_For_Association(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IwfSigtranAssociationsConfig *pOrginalIwfSigtranAssociationsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranSctpEndPoints_Get_Config_Reqs(IwfSigtranSctpEndPointsConfig *pIwfSigtranSctpEndPointsConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFSctpEndpoints_protobuff(IwfSigtranSctpEndPointsConfig *pIwfSigtranSctpEndPointsConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFSctpProfiles_protobuff(IwfSigtranSctpProfilesConfig *pIwfSigtranSctpProfilesConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranSctpProfiles_Get_Config_Reqs(IwfSigtranSctpProfilesConfig *pIwfSigtranSctpProfilesConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranSctpProfiles_Add_Config_Reqs(IwfSigtranSctpProfilesConfig *pIwfSigtranSctpProfilesConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranSctpProfiles_Mod_Config_Reqs(IwfSigtranSctpProfilesConfig *pIwfSigtranSctpProfilesConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFSctpProfile_Check_Association_isEnabled(IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranAssociationSets_Add_Config_Reqs(IwfSigtranAssociationSetsConfig *pIwfSigtranAssociationSetsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranMultihoming_Validation(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig, IWFCfgResp *resp,int iIndex);
        DbStatus_e mysql_IwfSigtranAssociation_Add_Validation(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig, IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranAssociations_Add_Config_Reqs(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranAssociations_Mod_Config_Reqs(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFSigtranAssociation_Check_Association_isEnabled(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranAssociation_set_Assoctionid(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig);
        DbStatus_e mysql_IwfSigtranSetMapping_Del_Config(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig, bool isDeleteAssociation = false);
        DbStatus_e mysql_IwfSigtranAssociation_Mod_Validation(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig);
        DbStatus_e IWFSigranAssociationsConfig_Fill_For_SctpProfile(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IwfSigtranSctpProfilesConfig *pIwfSigtranSctpProfilesConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranAssociation_Del_Validation(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig);
        DbStatus_e mysql_IwfSigtranAssociations_Del_Config_Reqs(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFSigtranAssociation_protobuff(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranAssociations_Get_Config_Reqs(IwfSigtranAssociationsConfig *req,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtransMultihoming_Del_Validation(IwfSigtranSctpEndPointConfig *pIwfSigtranSctpEndPointConfig,int);
        DbStatus_e mysql_IwfSigtransMultihoming_Del_Config_Reqs(IwfSigtranSctpEndPointsConfig *pIwfSigtranSctpEndPointsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranAssociationSets_Get_Config_Reqs(IwfSigtranAssociationSetsConfig *req,IWFCfgResp *resp);
        DbStatus_e Fill_IWFSigtranAssocSets_protobuff(IwfSigtranAssociationSetsConfig *pIwfSigtranAssociationSetsConfig,IWFCfgResp *resp);
        DbStatus_e IWFSigranAssociationsConfig_Fill_For_MultihomingIP(IwfSigtranAssociationsConfig *pIwfSigtranAssociationsConfig,IwfSigtransMultihomingConfig *pIwfSigtransMultihomingConfig,IWFCfgResp *resp);
        DbStatus_e IWFSigranAssociationSetsConfig_Fill_For_SctpProfiles(IwfSigtranAssociationSetsConfig *pIwfSigtranAssociationSetsConfig,IwfSigtranSctpProfilesConfig *pIwfSigtranSctpProfilesConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFSctpProfile_Del_Validation(IwfSigtranSctpProfileConfig *pIwfSigtranSctpProfileConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranSctpProfiles_Del_Config_Reqs(IwfSigtranSctpProfilesConfig *pIwfSigtranSctpProfilesConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranAssociationSets_Mod_Config_Reqs(IwfSigtranAssociationSetsConfig *pIwfSigtranAssociationSetsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranAssociationSet_Validation(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig, IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranAssociationSet_Del_Validation(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig, IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranAssociationSets_Del_Config_Reqs(IwfSigtranAssociationSetsConfig *pIwfSigtranAssociationSetsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranAssociationSet_Add_Validation(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig, IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranAssociationSet_Mod_Validation(IwfSigtranAssociationSetConfig *pIwfSigtranAssociationSetConfig, IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranAssociations_get_Associationid(IwfSigtranAssociationConfig *pIwfSigtranAssociationConfig);
        DbStatus_e Fill_IWFSigtranMultihomings_protobuff(IwfSigtransMultihomingConfig *pIwfSigtransMultihomingConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranMultihoming_Get_Config_Reqs(IwfSigtransMultihomingConfig *pIwfSigtransMultihomingConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFSigtranDestinations_protobuff(IwfSigtranDestinationsConfig *pIwfSigtranDestinationsConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFSigtranRemoteRoutes_protobuff(IwfSigtranRemoteRoutesConfig *pIwfSigtranRemoteRoutesConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranRemoteRoute_Get_Config_Reqs(IwfSigtranRemoteRoutesConfig *pIwfSigtranRemoteRoutesConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranDestination_Get_Config_Reqs(IwfSigtranDestinationsConfig *pIwfSigtranDestinationsConfig,IWFCfgResp *resp);


        void mysql_set_error_for_IWFTranslatorRule_Config_Reqs(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFTranslatorRule_Config_Reqs(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp,DbStatus_e iReturn,std::string& RuleName);
        void mysql_set_error_for_IWFTranslatorType_Config_Reqs(IwfTranslatorType *pIwfTranslatorType,IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFTranslator_Config_Reqs(IwfTranslatorConfig *pIwfTranslatorConfig,IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFVplmnId_Config_Reqs(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFVplmnId_Config_Reqs(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp,DbStatus_e iReturn,int iIndex);
        DbStatus_e Fill_IWFTranslatorRule_protobuff(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFTranslatorRules_protobuff(IwfTranslatorRulesConfig *pIwfTranslatorRulesConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFTranslatorType_protobuff(IwfTranslatorType *pIwfTranslatorType,IWFCfgResp *resp);
        DbStatus_e Fill_IWFTranslator_protobuff(IwfTranslatorConfig *pIwfTranslatorConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFVplmnId_protobuff(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp,int iIndex);
        DbStatus_e mysql_IWFTranslatorVplmnId_Del_Config_Reqs(IwfTranslatorRulesConfig *pIwfTranslatorRulesConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFVplmnId_Del_Validation(IwfTranslatorRuleConfig *pIwfTranslatorRulesConfig,int iIndex);
        DbStatus_e mysql_IWFVplmnId_Validation(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig, IWFCfgResp *resp,int iIndex);
        DbStatus_e validate_ServiceKey(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp,std::string& RuleName);
        DbStatus_e validate_ImsiPrefix_and_ServiceKey(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp,std::string& RuleName);
        DbStatus_e mysql_IWFTranslatorRule_Add_Config_Reqs(IwfTranslatorRulesConfig *req,IWFCfgResp *resp);
        DbStatus_e mysql_IWFTranslatorRule_Add_Validation(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFTranslatorRule_Mod_Config_Reqs(IwfTranslatorRulesConfig *req,IWFCfgResp *resp);
        DbStatus_e mysql_IWFTranslatorRule_Mod_Validation(IwfTranslatorRuleConfig *pIwfTranslatorRuleConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IWFTranslatorRule_Del_Config_Reqs(IwfTranslatorRulesConfig *req,IWFCfgResp *resp);
        DbStatus_e mysql_IWFTranslatorRules_Get_Config_Reqs(IwfTranslatorRulesConfig *req,IWFCfgResp *resp);
        DbStatus_e mysql_IWFAllTranslatorData_Get_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranDestination_Add_Config_Reqs(IwfSigtranDestinationsConfig *pIwfSigtranDestinationsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranDestination_Mod_Validation(IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig);
        DbStatus_e mysql_IwfSigtranDestination_Mod_Config_Reqs(IwfSigtranDestinationsConfig *pIwfSigtranDestinationsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranDestination_Del_Config_Reqs(IwfSigtranDestinationsConfig *pIwfSigtranDestinationsConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranDestination_Del_Validation(IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig);
        DbStatus_e mysql_IwfSigtranRemoteRoute_Fill_For_Destination(IwfSigtranRemoteRoutesConfig *pIwfSigtranRemoteRoutesConfig,IwfSigtranDestinationsConfig *pIwfSigtranDestination,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranRemoteRoute_Validation(IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig);
        DbStatus_e mysql_IwfSigtranRemoteRoute_Add_Config_Reqs(IwfSigtranRemoteRoutesConfig *pIwfSigtranRemoteRoutesConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranRemoteRoute_Mod_Config_Reqs(IwfSigtranRemoteRoutesConfig *pIwfSigtranRemoteRoutesConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranRemoteRoute_Mod_Validation(IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig);
        void mysql_set_error_for_IWFSigtranRemoteRoute_Config_Reqs(IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig,IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFSigtranDestination_Config_Reqs(IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig,IWFCfgResp *resp,DbStatus_e iReturn);
        DbStatus_e Fill_IWFSigtranRemoteRoute_protobuff(IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFSigtranDestination_protobuff(IwfSigtranDestinationConfig *pIwfSigtranDestinationConfig,IWFCfgResp *resp);
        DbStatus_e mysql_IwfSigtranRemoteRoute_Del_Validation(IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig);
        DbStatus_e mysql_IwfSigtranRemoteRoute_Del_Config_Reqs(IwfSigtranRemoteRoutesConfig *pIwfSigtranRemoteRoutesConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFSigtranRemoteRoute_protobuff(IwfSigtranRemoteRouteConfig *pIwfSigtranRemoteRouteConfig,IWFCfgResp *resp,int AssociationSetID);
        DbStatus_e mysql_IwfSigtranRemoteRoute_Fill_For_RemoteRoute(IwfSigtranRemoteRoutesConfig *pIwfSigtranRemoteRoutesConfig,IwfSigtranRemoteRoutesConfig *pOrignalIwfSigtranRemoteRoutesConfig,IWFCfgResp *resp);


        void mysql_set_error_for_IWFMapS6aConfig_Config_Reqs(IwfMapToS6aConfig *pIwfMapToS6aConfig,IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFMapS6aVplmnId_Config_Reqs(IwfMapToS6aConfig *pIwfMapToS6aConfig,IWFCfgResp *resp,DbStatus_e iReturn, int index);
        void mysql_set_error_for_IWFMapS6aVplmnIdSgsnMap_Config_Reqs(IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfig,IWFCfgResp *resp,DbStatus_e iReturn, int index);
        void mysql_set_error_for_IWFS6aMapConfig_Config_Reqs(IwfS6aToMapConfig *pIwfS6aToMapConfig,IWFCfgResp *resp,DbStatus_e iReturn);
        void mysql_set_error_for_IWFS6aMapSgsnAddrMap_Config_Reqs(IwfS6aToMapConfig *pIwfS6aToMapConfig,IWFCfgResp *resp,DbStatus_e iReturn,int iIndex);
        void mysql_set_error_for_IWFS6aMapSgsnPrefixMap_Config_Reqs(IwfS6aToMapConfig *pIwfS6aToMapConfig,IWFCfgResp *resp,DbStatus_e iReturn,int iIndex);
        DbStatus_e Fill_IWFMapS6aConfig_protobuff(IwfMapToS6aConfig *pIwfMapToS6aConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFMapS6aVplmnIdConfig_protobuff(IwfMapToS6aConfig *pIwfMapToS6aConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFMapS6aVplmnIdSgsnMapConfig_protobuff(IwfMapToS6aVplmnIdConfig *pIwfMapToS6aVplmnIdConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFS6aMapConfig_protobuff(IwfS6aToMapConfig *pIwfS6aToMapConfig,IWFCfgResp *resp);
        DbStatus_e Fill_IWFS6aMapSgsnAddrMap_protobuff(IwfS6aToMapConfig *pIwfS6aToMapConfig,IWFCfgResp *resp,int iIndex);
        DbStatus_e Fill_IWFS6aMapSgsnPrefixMap_protobuff(IwfS6aToMapConfig *pIwfS6aToMapConfig,IWFCfgResp *resp,int iIndex);
        DbStatus_e mysql_IWFMAPS6a_Add_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp);
        DbStatus_e mysql_IWFMAPS6a_Mod_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp);
        DbStatus_e mysql_IWFMAPS6a_Get_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp);
        DbStatus_e mysql_IWFS6aMAP_Add_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp);
        DbStatus_e mysql_IWFS6aMAP_Mod_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp);
        DbStatus_e mysql_IWFS6aMAP_Del_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp);
        DbStatus_e mysql_IWFS6aMAP_Get_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp);
        DbStatus_e mysql_IWFMAPS6aVplmnId_Del_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp);
        DbStatus_e mysql_IWFMAPS6aVplmnIdSgsnMap_Del_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp);

    void mysql_set_error_for_IWFCapToRoConfig_Config_Reqs(IwfCapToRoConfig *pIwfCapToRoConfig,IWFCfgResp *resp,DbStatus_e iReturn);
    void mysql_set_error_for_CapRoIdpConfig_Config_Reqs(CapRoIdpConfig *pCapRoIdpConfig,IWFCfgResp *resp,DbStatus_e iReturn);
    void mysql_set_error_for_CapRoIdpSmsConfig_Config_Reqs(CapRoIdpSmsConfig *pCapRoIdpSmsConfig,IWFCfgResp *resp,DbStatus_e iReturn);
    void mysql_set_error_for_ExtBearerservice_Config_Reqs(CapRoIdpConfig *pCapRoIdpConfig,IWFCfgResp *resp,DbStatus_e iReturn,int iIndex);
    void mysql_set_error_for_ExtTeleservice_Config_Reqs(CapRoIdpConfig *pCapRoIdpConfig,IWFCfgResp *resp,DbStatus_e iReturn,int iIndex);
    DbStatus_e Fill_IWFCapRoConfig_protobuff(IwfCapToRoConfig *pIwfCapToRoConfig,IWFCfgResp *resp);
    DbStatus_e Fill_CapRoIdpConfig_protobuff(IwfCapToRoConfig *pIwfCapToRoConfig,IWFCfgResp *resp);
    DbStatus_e Fill_CapRoIdpSmsConfig_protobuff(IwfCapToRoConfig *pIwfCapToRoConfig,IWFCfgResp *resp);
    DbStatus_e Fill_ExtTeleserviceToServiceIdMap_Config_protobuff(CapRoIdpConfig *pCapRoIdpConfig,IWFCfgResp *resp,int iIndex);
    DbStatus_e Fill_ExtBearerserviceToServiceIdMap_Config_protobuff(CapRoIdpConfig *pCapRoIdpConfig,IWFCfgResp *resp,int iIndex);

    DbStatus_e mysql_IWFCapRo_Add_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp);
    DbStatus_e mysql_IWFCapRo_Mod_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp);
    DbStatus_e mysql_IWFCapRo_Del_Config_Reqs(IwfTranslationDataConfig *req, IWFCfgResp *resp);
    DbStatus_e mysql_IWFCapRo_Get_Config_Reqs(IwfTranslationDataConfig *pIwfTranslationDataConfig, IWFCfgResp *resp);
    DbStatus_e mysql_IWFCapRoIdpSms_Get_Config_Reqs(IwfTranslationDataConfig *pIwfTranslationDataConfig, IWFCfgResp *resp);
    DbStatus_e mysql_IWFCapRoIdp_Get_Config_Reqs(IwfTranslationDataConfig *pIwfTranslationDataConfig, IWFCfgResp *resp);

    void mysql_set_error_for_IWFTimer_Config_Reqs(IwfTimerConfig *pIwfTimerConfig,IWFCfgResp *resp,DbStatus_e iReturn);
    DbStatus_e Fill_IWFTimers_protobuff(IwfTimersConfig *pIwfTimersConfig,IWFCfgResp *resp);
    DbStatus_e Fill_IWFTimer_protobuff(IwfTimerConfig *pIWFTimer,IWFCfgResp *resp);
    DbStatus_e mysql_IWFTimers_Get_Config_Reqs(IwfTimersConfig *pIwfTimersConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfTimer_Add_Config_Reqs(IwfTimersConfig *pIwfTimersConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfTimer_Mod_Config_Reqs(IwfTimersConfig *pIwfTimersConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfTimer_Del_Config_Reqs(IwfTimersConfig *pIwfTimersConfig,IWFCfgResp *resp);

    void mysql_set_error_for_IWFUal_Config_Reqs(IwfSigtranUalManagerConfig *pIwfSigtranUalManagerConfig,IWFCfgResp *resp,DbStatus_e iReturn);
    DbStatus_e Fill_IWFUal_protobuff(IwfSigtranUalManagerConfig *pIwfSigtranUalManagerConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfUal_Get_Config_Reqs(IwfSigtranUalManagerConfig *pIwfSigtranUalManagerConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfUal_Add_Config_Reqs(IwfSigtranUalManagerConfig *pIwfSigtranUalManagerConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfUal_Mod_Config_Reqs(IwfSigtranUalManagerConfig *pIwfSigtranUalManagerConfig,IWFCfgResp *resp);
    DbStatus_e check_for_IWF_requestid(IwfLocalHostsConfig *req,IWFCfgResp *resp);
    void Copy_IWFCfgResp_localresponse_to_Reponse(IWFCfgResp *localresp, IWFCfgResp *resp);

    void mysql_set_error_for_IWFFeature_Config_Reqs(IwfFeatureConfig *pIwfFeatureConfig,IWFCfgResp *resp,DbStatus_e iReturn);
    DbStatus_e Fill_IWFFeatures_protobuff(IwfFeaturesConfig *pIwfFeaturesConfig,IWFCfgResp *resp);
    DbStatus_e Fill_IWFFeature_protobuff(IwfFeatureConfig *pIWFFeature,IWFCfgResp *resp);
    DbStatus_e mysql_IWFFeatures_Get_Config_Reqs(IwfFeaturesConfig *pIwfFeaturesConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfFeature_Add_Config_Reqs(IwfFeaturesConfig *pIwfFeaturesConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfFeature_Mod_Config_Reqs(IwfFeaturesConfig *pIwfFeaturesConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfFeature_Del_Config_Reqs(IwfFeaturesConfig *pIwfFeaturesConfig,IWFCfgResp *resp);

    void mysql_set_error_for_IWFDccaFeature_Config_Reqs(IwfDccaFeatureConfig *pIwfDccaFeatureConfig,IWFCfgResp *resp,DbStatus_e iReturn);
    DbStatus_e Fill_IWFDccaFeatures_protobuff(IwfDccaGenConfig *pIwfDccaGenConfig,IWFCfgResp *resp);
    DbStatus_e Fill_IWFDccaFeature_protobuff(IwfDccaFeatureConfig *pIwfDccaFeatureConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IWFDccaFeatures_Get_Config_Reqs(IwfDccaGenConfig *pIwfDccaGenConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfDccaGeneralConfig_Add_Config_Reqs(IwfDccaGenConfig *pIwfDccaGenConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfDccaGeneralConfig_Mod_Config_Reqs(IwfDccaGenConfig *pIwfDccaGenConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfDccaGeneralConfig_Del_Config_Reqs(IwfDccaGenConfig *pIwfDccaGenConfig,IWFCfgResp *resp);
    
    void mysql_set_error_for_IWFDccaDestConfig_Config_Reqs(IwfDccaDestConfig *pIwfDccaDestConfig,IWFCfgResp *resp,DbStatus_e iReturn);
    DbStatus_e Fill_IWFDccaDestsConfig_protobuff(IwfDccaDestsConfig *pIwfDccaDestsConfig,IWFCfgResp *resp);
    //DbStatus_e Fill_IWFDccaFeature_protobuff(IwfDccaFeatureConfig *pIwfDccaFeatureConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IWFDccaDestConfig_Get_Config_Reqs(IwfDccaDestsConfig *pIwfDccaDestsConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfDccaDestConfig_Add_Config_Reqs(IwfDccaDestsConfig *pIwfDccaDestsConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfDccaDestConfig_Add_Validation_and_Process_Reqs(IwfDccaDestConfig *pIwfDccaDestConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfDccaDestConfig_Del_Config_Reqs(IwfDccaDestsConfig *pIwfDccaDestsConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfDccaEndPointConfig_Del_Config_Reqs(IwfDccaDestsConfig *pIwfDccaDestsConfig,IWFCfgResp *resp);

    void mysql_set_error_for_IWFProtocolAction_Config_Reqs(IwfProtocolActionConfig *pIwfProtocolActionConfig,IWFCfgResp *resp,DbStatus_e iReturn);
    DbStatus_e mysql_IwfProtocolAction_Add_Config_Reqs(IwfProtocolActionsConfig *pIwfProtocolActionsConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfProtocolAction_Mod_Config_Reqs(IwfProtocolActionsConfig *pIwfProtocolActionsConfig,IWFCfgResp *resp);
    DbStatus_e mysql_IwfProtocolAction_Del_Config_Reqs(IwfProtocolActionsConfig *pIwfProtocolActionsConfig,IWFCfgResp *resp, int OperId);
    DbStatus_e mysql_IwfProtocolAction_Get_Config_Reqs(IwfProtocolActionsConfig *pIwfProtocolActionsConfig,IWFCfgResp *resp);
    DbStatus_e Fill_IWFProtocolActions_protobuff(IwfProtocolActionsConfig *pIwfProtocolActionsConfig,IWFCfgResp *resp);
    DbStatus_e Fill_IWFCallScenario_protobuff(IwfProtocolActionConfig *pIwfProtocolActionConfig,IWFCfgResp *resp);
    DbStatus_e Fill_IWFEventType_protobuff(CallScenario* callScenario, std::string ActionRuleName,IWFCfgResp *resp);
    DbStatus_e Fill_IWFEventTypeDetails_protobuff(EventType *pEventType,IWFCfgResp* resp);
    void mysql_set_error_for_IWFEventTypeDetails_Config_Reqs(EventType *pEventType, std::string RuleName, std::string callScenario, IWFCfgResp *resp,DbStatus_e iReturn, int iIndex);
    void mysql_set_error_for_IWFEventType_Config_Reqs(CallScenario *pCallScenario, std::string RuleName, IWFCfgResp *resp,DbStatus_e iReturn, int iIndex);
    void mysql_set_error_for_IWFCallScenario_Config_Reqs(MsgDet *pMsgDet,std::string RuleName,IWFCfgResp *resp,DbStatus_e iReturn, int iIndex);
};
#endif

