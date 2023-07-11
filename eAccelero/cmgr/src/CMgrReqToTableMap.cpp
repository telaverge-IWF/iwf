/* ********************************-*-C-*-************************************
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


#include "CMgrLock.h"
using namespace std;
ReqIdToTableMap m_RTMap;

CnfLockMgr::CnfLockMgr(CMgrIwfDbInterface *pCMgrIwfDbInterface)
{
    DLOG_NONE(" > %s",__FUNCTION__);

    m_dbHandle = &(pCMgrIwfDbInterface->m_dbHandle);

    m_RTMap.insert(ReqIdToTablePair(SET_LOCAL_HOST,"IWF_LOCAL_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_LOCAL_HOST,"IWF_LOCAL_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_LOCAL_HOST_SSN,"IWF_LOCAL_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_LOCAL_INVK_TIMER,"IWF_LOCAL_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_SIGTRAN_DEST,"IWF_SIGTRAN_DESTINATION_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_SIGTRAN_DEST,"IWF_SIGTRAN_DESTINATION_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_SIGTRAN_DEST,"IWF_SIGTRAN_DESTINATION_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_ASSOC_SET,"IWF_SIGTRAN_ASSOC_SET_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_ASSOC_SET,"IWF_SIGTRAN_ASSOC_SET_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_ASSOC_SET,"IWF_SIGTRAN_ASSOC_SET_TB"));
    m_RTMap.insert(ReqIdToTablePair(ACTIVATE_ASSOC_SET,"IWF_SIGTRAN_ASSOC_SET_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_ASSOC,"IWF_SIGTRAN_ASSOCIATION_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_ASSOC,"IWF_SIGTRAN_ASSOCIATION_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_ASSOC,"IWF_SIGTRAN_ASSOCIATION_TB"));
    m_RTMap.insert(ReqIdToTablePair(ACTIVATE_ASSOC,"IWF_SIGTRAN_ASSOCIATION_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_SCTP_ENDPOINT,"IWF_SCTP_ENDPOINT_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_SCTP_ENDPOINT,"IWF_SCTP_ENDPOINT_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_SCTP_ENDPOINT,"IWF_SCTP_ENDPOINT_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_SCTP_PROFILE,"IWF_SIGTRAN_SCTP_PROFILE_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_SCTP_PROFILE,"IWF_SIGTRAN_SCTP_PROFILE_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_SCTP_PROFILE,"IWF_SIGTRAN_SCTP_PROFILE_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_SIG_MULTIHOMING,"IWF_SIGTRAN_ASSOCIATION_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_SIG_MULTIHOMING,"IWF_SIGTRAN_ASSOCIATION_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_SIG_MULTIHOMING,"IWF_SIGTRAN_ASSOCIATION_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_AND_ADD_SIG_MULTIHOMING,"IWF_SIGTRAN_MULTIHOMING_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_REMOTE_ROUTE,"IWF_SIGTRAN_REMOTE_ROUTE_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_REMOTE_ROUTE,"IWF_SIGTRAN_REMOTE_ROUTE_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_REMOTE_ROUTE,"IWF_SIGTRAN_REMOTE_ROUTE_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_TRANSLATOR_RULE,"IWF_TRANSLATOR_RULE_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_TRANSLATOR_RULE,"IWF_TRANSLATOR_RULE_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_TRANSLATOR_RULE,"IWF_TRANSLATOR_RULE_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_S6AMAP_DATA,"IWF_TRANSLATOR_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_S6AMAP_DATA,"IWF_TRANSLATOR_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_S6AMAP_DATA,"IWF_TRANSLATOR_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_MAPS6A_DATA,"IWF_TRANSLATOR_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_MAPS6A_DATA,"IWF_TRANSLATOR_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_MAPS6A_DATA,"IWF_TRANSLATOR_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_CAPRO_DATA,"IWF_TRANSLATOR_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_CAPRO_DATA,"IWF_TRANSLATOR_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_CAPRO_DATA,"IWF_TRANSLATOR_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_IWF_TIMERS,"IWF_TIMER_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_IWF_TIMERS,"IWF_TIMER_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_IWF_TIMERS,"IWF_TIMER_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_IWF_CAP_TIMERS,"IWF_TIMER_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_IWF_CAP_TIMERS,"IWF_TIMER_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_IWF_CAP_TIMERS,"IWF_TIMER_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_UAL_CONFIG,"IWF_SIGTRAN_UAL_MANAGER_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_UAL_CONFIG,"IWF_SIGTRAN_UAL_MANAGER_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_VPLMN_ID,"IWF_TRANSLATOR_RULE_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_VPLMN_ID,"IWF_TRANSLATOR_RULE_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_VPLMN_ID,"IWF_TRANSLATOR_RULE_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_MAPS6A_VPLMN_ID_DATA,"IWF_MAPS6A_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_MAPS6A_VPLMN_ID_DATA,"IWF_MAPS6A_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_MAPS6A_VPLMN_ID_DATA,"IWF_MAPS6A_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_VPLMN_ID_SGSN_MAP_DATA,"IWF_MAPS6A_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_VPLMN_ID_SGSN_MAP_DATA,"IWF_MAPS6A_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_VPLMN_ID_SGSN_MAP_DATA,"IWF_MAPS6A_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_CAP_PROTO_TIMERS,"IWF_TIMER_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_CAP_PROTO_TIMERS,"IWF_TIMER_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_IWF_FEATURES,"IWF_FEATURE_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_IWF_FEATURES,"IWF_FEATURE_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_IWF_FEATURES,"IWF_FEATURE_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_IWF_DCCA_FEATURES,"IWF_DCCA_GENERAL_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_IWF_DCCA_FEATURES,"IWF_DCCA_GENERAL_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_IWF_DCCA_FEATURES,"IWF_DCCA_GENERAL_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_IWF_DCCA_DEST,"IWF_DCCA_ENDPOINTS_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_IWF_DCCA_DEST,"IWF_DCCA_ENDPOINTS_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_IWF_DCCA_DEST,"IWF_DCCA_ENDPOINTS_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_IWF_DCCA_ENDPOINT,"IWF_DCCA_ENDPOINTS_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_IWF_PROT_ACTIONS,"IWF_PROTOCOL_ACTION_RULE_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_IWF_PROT_ACTIONS,"IWF_PROTOCOL_ACTION_RULE_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_IWF_PROT_ACTIONS,"IWF_PROTOCOL_ACTION_RULE_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_IWF_CALL_SCENARIO,"IWF_PROTOCOL_ACTION_RULE_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_IWF_EVENT_TYPE,"IWF_PROTOCOL_ACTION_RULE_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_IWF_EVENT_TYPE_CONFIG,"IWF_PROTOCOL_ACTION_RULE_TB"));
    m_RTMap.insert(ReqIdToTablePair(DUMP_SYSTEM_INFO,"IWF_FEATURE_TB"));

    DLOG_NONE(" < %s",__FUNCTION__);
}

CnfLockMgr::CnfLockMgr(CMgrDbInterface *pCMgrDbInterface)
{
    DLOG_NONE(" > %s",__FUNCTION__);

    m_dbHandle = &(pCMgrDbInterface->m_dbHandle);

    m_RTMap.insert(ReqIdToTablePair(SET_HOST,"LocalHostConfigT"));
    m_RTMap.insert(ReqIdToTablePair(DEL_HOST,"LocalHostConfigT"));
    m_RTMap.insert(ReqIdToTablePair(MOD_HOST,"LocalHostConfigT"));
    m_RTMap.insert(ReqIdToTablePair(SET_AUTHTIMERS,"LocalHostConfigT"));
    m_RTMap.insert(ReqIdToTablePair(SET_ACCTTIMERS,"LocalHostConfigT"));
    m_RTMap.insert(ReqIdToTablePair(SET_HOSTIP,"LocalHostConfigT"));
    m_RTMap.insert(ReqIdToTablePair(SET_PEER,"PeerT"));
    m_RTMap.insert(ReqIdToTablePair(DEL_PEER,"PeerT"));
    m_RTMap.insert(ReqIdToTablePair(SET_DEFROUTE,"REALM_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_DEFROUTE,"REALM_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_REALM,"REALM_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_REALM,"REALM_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_DEST,"REALM_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_DEST,"REALM_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_DEST,"REALM_TB"));
    m_RTMap.insert(ReqIdToTablePair(ENBPXYIAVP,"REALM_TB"));
    m_RTMap.insert(ReqIdToTablePair(DISPXYIAVP,"REALM_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_PEER,"PeerT"));
    m_RTMap.insert(ReqIdToTablePair(MOD_REALM,"REALM_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_DEFROUTE,"REALM_TB"));
    m_RTMap.insert(ReqIdToTablePair(ADD_DICTID,"PeerT"));
    m_RTMap.insert(ReqIdToTablePair(DEL_DICTID,"PeerT"));
    m_RTMap.insert(ReqIdToTablePair(SET_PEERSTATUS,"PeerT"));
    m_RTMap.insert(ReqIdToTablePair(SET_LOGGERCONFIG,"LOGGING_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_LOGGERCONFIG,"LOGGING_CONFIG_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_USER,"UserT"));
    m_RTMap.insert(ReqIdToTablePair(MOD_USER,"UserT"));
    m_RTMap.insert(ReqIdToTablePair(DEL_USER,"UserT"));
    m_RTMap.insert(ReqIdToTablePair(SET_GROUP,""));
    m_RTMap.insert(ReqIdToTablePair(MOD_GROUP,""));
    m_RTMap.insert(ReqIdToTablePair(DEL_GROUP,""));
    m_RTMap.insert(ReqIdToTablePair(SET_PRIVILEGE,"UserT"));
    m_RTMap.insert(ReqIdToTablePair(MOD_PRIVILEGE,"UserT"));
    m_RTMap.insert(ReqIdToTablePair(DEL_PRIVILEGE,"UserT"));
    m_RTMap.insert(ReqIdToTablePair(DEL_ALTPEER,"PeerT"));
    m_RTMap.insert(ReqIdToTablePair(SET_ASF,"ASF_CONFIGURATION_TB"));
    m_RTMap.insert(ReqIdToTablePair(ADD_ASGRP,"ASF_CONFIGURATION_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_ASGRP,"ASF_CONFIGURATION_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_ASGRP,"ASF_CONFIGURATION_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_LHCFG,"LocalHostConfigT"));
    m_RTMap.insert(ReqIdToTablePair(MOD_LHCFG,"LocalHostConfigT"));
    m_RTMap.insert(ReqIdToTablePair(ADD_LHTCFG,"LocalHostConfigT"));
    m_RTMap.insert(ReqIdToTablePair(MOD_LHTCFG,"LocalHostConfigT"));
    m_RTMap.insert(ReqIdToTablePair(DEL_LHTCFG,"LocalHostConfigT"));
    m_RTMap.insert(ReqIdToTablePair(SET_SCTPCFG,"SCTP_CONFIG"));
    m_RTMap.insert(ReqIdToTablePair(ADD_CACRLCFG,"TRUSTED_CA_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_CACRLCFG,"TRUSTED_CA_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_CACRLCFG,"TRUSTED_CA_TB"));
    m_RTMap.insert(ReqIdToTablePair(REM_CACRLASSOC,"TRUSTED_CA_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_GENCFG,"STACK_GEN_CONFIG"));
    m_RTMap.insert(ReqIdToTablePair(SET_TLSCONFIG,"TLS_CONFIG"));
    m_RTMap.insert(ReqIdToTablePair(MOD_CIPHERSUITE,"CIPHER_SUITE_TB"));
    m_RTMap.insert(ReqIdToTablePair(SET_TRACE,"TRACING_FILTER_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_TRACE,"TRACING_FILTER_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_TRACE,"TRACING_FILTER_TB"));
    m_RTMap.insert(ReqIdToTablePair(ENABLE_TRACE,"TRACING_TB"));
    m_RTMap.insert(ReqIdToTablePair(ADD_SECIP,"LocalHostConfigT"));
    m_RTMap.insert(ReqIdToTablePair(MOD_SECIP,"LocalHostConfigT"));
    m_RTMap.insert(ReqIdToTablePair(DEL_SECIP,"PeerT"));
    m_RTMap.insert(ReqIdToTablePair(SET_SRCONFIG,"STATIC_ROUTE_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_SRCONFIG,"STATIC_ROUTE_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_SRCONFIG,"STATIC_ROUTE_TB"));
    m_RTMap.insert(ReqIdToTablePair(ADD_PEERGROUP,"PEER_GRP_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_PEERGROUP,"PEER_GRP_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_PEERGROUP,"PEER_GRP_TB"));
    m_RTMap.insert(ReqIdToTablePair(ADD_PEERCONFIG,"PeerT"));
    m_RTMap.insert(ReqIdToTablePair(MOD_PEERCONFIG,"PeerT"));
    m_RTMap.insert(ReqIdToTablePair(DEL_PEERCONFIG,"PeerT"));
    m_RTMap.insert(ReqIdToTablePair(ADD_LBALGO,"LB_ALGORITHM_TB"));
    m_RTMap.insert(ReqIdToTablePair(MOD_LBALGO,"LB_ALGORITHM_TB"));
    m_RTMap.insert(ReqIdToTablePair(DEL_LBALGO,"LB_ALGORITHM_TB"));

    DLOG_NONE(" < %s",__FUNCTION__);
}
