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

#ifndef __CMAPICOMMON_H__
#define __CMAPICOMMON_H__


#include "string.h"
#include "Sync.h"
#include <queue>


#define SUBAGENT_INSTANCE_ID MESS_MIN_ACTIVE_INSTANCE
#define CMGR_INSTANCE_ID  MESS_MIN_ACTIVE_INSTANCE
#define DRE_INSTANCE_ID   MESS_MIN_ACTIVE_INSTANCE
#define IWF_INSTANCE_ID   MESS_MIN_ACTIVE_INSTANCE


enum ComponentReqIDs { GET_PEERGROUP = 0, ADD_PEERGROUP, MOD_PEERGROUP, DEL_PEERGROUP, GET_PEERCONFIG,
    ADD_PEERCONFIG, MOD_PEERCONFIG, DEL_PEERCONFIG, ADD_LBALGO, MOD_LBALGO, GET_LBALGO, DEL_LBALGO, GET_PEERGROUPSTATS, GET_SESSBINDSTATS, RESET_SESSBINDSTATS,
    GET_PEERGENERALSTATS, GET_PEERTRANSPORTSTATS, GET_PEERERRORSTATS, RESET_PEERSTATS, RAISE_ALARM, RESET_PEERGROUPSTATS, INVALID_REQID
};

enum CMAPIRetCodes { CMAPI_SUCCESS = 0, CMAPI_ERROR, CMAPI_INVALIDPARAMS, CMAPI_MESSERROR, CMAPI_SRVERROR, CMAPI_TIMEOUT, CMAPI_DB_SUCCESS };

enum CallerReqIDs {
	GET_HOST      	=1,
	SET_HOST        =2,
	DEL_HOST        =3,
	MOD_HOST        =4,
	SET_AUTHTIMERS  =5,
	SET_ACCTTIMERS  =6,
	SET_HOSTIP      =7,
	GET_PEER        =8,
	SET_PEER        =9,
	DEL_PEER        =10,
	SET_DEFROUTE    =11,
	GET_DEFROUTE    =12,
	DEL_DEFROUTE    =13,
	GET_REALM       =14,
	SET_REALM       =15,
	DEL_REALM       =16,
	SET_DEST        =17,
	GET_DEST        =18,
	MOD_DEST        =19,
	DEL_DEST        =20,
	ENBPXYIAVP      =21,
	DISPXYIAVP      =22,
	MOD_PEER        =23,
	MOD_DEFROUTE    =24,
	MOD_REALM       =25,
	ADD_DICTID      =26,
	DEL_DICTID      =27,
	SET_PEERSTATUS  =28,
	GET_LOGGERCONFIG=29,
	SET_LOGGERCONFIG=30,
	MOD_LOGGERCONFIG=31,
	GET_USER        =32,
	SET_USER        =33,
	MOD_USER        =34,
	DEL_USER        =35,
	GET_GROUP       =36,
	SET_GROUP       =37,
	MOD_GROUP       =38,
	DEL_GROUP       =39,
	GET_PRIVILEGE   =40,
	SET_PRIVILEGE   =41,
	MOD_PRIVILEGE   =42,
	DEL_PRIVILEGE   =43,
	GET_PEEROFREALM =44,
	GET_REALMOFPEER =45,
	DEL_ALTPEER     =46,
	DISASSOCIATE_PEER_TEMPLATE  =47,
	DISSOCIATE_REALM_TEMPLATE   =48,
	SET_ASF         =49,
	GET_ASF         =50,
	ADD_ASGRP       =51,
	MOD_ASGRP		=52,
	DEL_ASGRP		=53,
	GET_ASGRP		=54,
	GET_LHCFG		=55,
	SET_LHCFG		=56,
	MOD_LHCFG		=57,
	GET_LHTCFG		=58,
	ADD_LHTCFG		=59,
	MOD_LHTCFG		=60,
	DEL_LHTCFG		=61,
	GET_SCTPCFG		=62,
	SET_SCTPCFG		=63,
	GET_CACRLCFG	=64,
	ADD_CACRLCFG	=65,
	MOD_CACRLCFG	=66,
	DEL_CACRLCFG	=67,
	REM_CACRLASSOC	=68,
	GET_GENCFG		=69,
	SET_GENCFG		=70,
	GET_PFCFG		=71,
	GET_TLSCONFIG	=72,
	SET_TLSCONFIG	=73,
	GET_CIPHERSUITE	=74,
	MOD_CIPHERSUITE	=75,
	GET_TRACE		=76,
	SET_TRACE		=77,
	MOD_TRACE		=78,
	DEL_TRACE		=79,
	ENABLE_TRACE	=80,
	GET_PEERSTATE	=81,
	ADD_SECIP		=82,
	MOD_SECIP		=83,
	DEL_SECIP		=84,
	GET_SRCONFIG		=85,
	SET_SRCONFIG		=86,
	MOD_SRCONFIG		=87,
	DEL_SRCONFIG		=88,
	SET_THF_ENABLE		=89,
	SET_THF_DEF_BEHAV	=90,
	ADD_THF_REALM		=91,
	ADD_THF_VHOST		=92,
	DEL_THF_REALM		=93,
	DEL_THF_VHOST		=94,
	GET_THF_ENABLE		=95,
	GET_THF_REALM		=96,
	GET_THF_VHOST		=97,
	ADD_PEER_TEMPLATE	=98,
	ADD_REALM_TEMPLATE	=99,
	MOD_PEER_TEMPLATE	=100,
	MOD_REALM_TEMPLATE	=101,
	DEL_REALM_TEMPLATE	=102,
	DEL_PEER_TEMPLATE	=103,
	GET_PEER_TEMPLATE	=104,
	GET_REALM_TEMPLATE	=105,

	DEL_LOCALHOST_SECIP     =128,
    ADD_USER_ROLE           =129,
    DEL_USER_ROLE           =130,
    MOD_USER_ROLE           =131,
    GET_USER_ROLE           =132,
    GET_EMAIL_SERVER        =133,
    SET_EMAIL_SERVER        =134,
    DEL_EMAIL_SERVER        =135,
    GET_EMAIL_CONTENT       =136,
    MOD_EMAIL_CONTENT       =137,
    SET_THF_ENABLE_DEF_BEHAV = 138,
    GET_USER_PRIVILEGE       =139,
    SET_DICT_STATUS              =140,
    SET_TRANSPLUGIN_STATUS       =141,
    RELOAD_TRANSPLUGIN           =142,
    GET_TRANSPLUGIN              =143,
    GET_DICTIONARIES             =144,

    GET_CLUSTER_INFO         =145,
    GET_SYS_RES              =146,
    GET_PROCESS_STATE           =147,
    GET_OVERALL_LATENCY      =148,
    GET_REQ_LATENCY          =149,
    GET_RES_LATENCY          =150,
    GET_OVERALL_TPS          =151,
    GET_CAS                  =152,
    GET_APP_KPI              =153, //should fill all above 5 (GET_OVERALL_LATENCY GET_REQ_LATENCY GET_RES_LATENCY GET_OVERALL_TPS GET_CAS)
    GET_APP_TPS              =154,
    GET_PEER_TPS             =155,
    GET_TPS                  =156, // should fill all above 2 (GET_APP_TPS GET_PEER_TPS)
    GET_APP_CAS              =157,
    GET_PEER_CAS             =158,
    GET_ALLCAS               =159, // should fill all above 2 (GET_APP_CAS GET_PEER_CAS)

    GET_CMF_ACTIONS_AND_TRIGGERS  =160,
    GET_CMF_LEVEL           =161,
    GET_CMF_RULE            =162,
    ADD_CMF_RULE            =163,
    MODIFY_CMF_RULE         =164,
    DELETE_CMF_RULE         =165,
    SET_CMF_RULE_STATUS     =166,
    SET_CMD_CODE_PRIORITY   =167,
    SET_APP_PRIORITY        =168,
    GET_CMF_TRIGGER         =169,
    GET_CMF_ACTION          =170,
    GET_CMF_DIA_PRIORITY    =171,
    ADD_CMF_DIA_PRIORITY    =172,
    DEL_CMF_DIA_PRIORITY    =173,
    MOD_CMF_DIA_PRIORITY    =174,
    GET_CMF_SYSTEM_TRIGGER_STATES  = 175,
    GET_CMF_PEER_TRIGGER_STATES  = 176,
    GET_CMF_REALM_TRIGGER_STATES  = 177,
    GET_CMF_LEVEL_CONFIG = 178,
    RELOAD_SDTF = 179,
    GET_SDTF_CONFIG = 180,
    SET_SDTF_RULE_STATUS = 181,
    ADD_SDTF_CONFIG = 182,
    MOD_SDTF_CONFIG = 183,
    DEL_SDTF_CONFIG = 184,
    GET_SDTF_ENABLE_STATUS = 185,
    SET_SDTF_ENABLE_STATUS = 186,
    GET_LTTAG = 187
};

enum StatsReqIDs {
    GET_APPSPECIFICSTATS = 1, GET_STACKINDICATIONSTATS, GET_GENERICERRORSTATS, GET_GENERICSTATS,
    RESET_APPSPECIFICSTATS, RESET_STACKINDICATIONSTATS, RESET_GENERICERRORSTATS, RESET_GENERICSTATS,
    GET_INTERFACESTATS, RESET_INTERFACESTATS
};

enum DTFReqIDs {
    LOAD_DICTIONARY = 1, UNLOAD_DICTIONARY, GET_DICTIONARY,
    LOAD_PLUGIN, UNLOAD_PLUGIN, GET_PLUGIN, INVALID_DTDREQID
};

enum CompActionIDs {
    GET_NODESTATUS = 1, HA_SWITCHOVER, GET_AMCONFIG
};

enum IWFReqIDs {
    GET_LOCAL_HOST = 1, SET_LOCAL_HOST, MOD_LOCAL_HOST, DEL_LOCAL_HOST_SSN, SET_LOCAL_INVK_TIMER,
    GET_SIGTRAN_DEST, SET_SIGTRAN_DEST, MOD_SIGTRAN_DEST, DEL_SIGTRAN_DEST,
    GET_ASSOC_SET, SET_ASSOC_SET, MOD_ASSOC_SET, DEL_ASSOC_SET, ACTIVATE_ASSOC_SET,
    GET_ASSOC, SET_ASSOC, MOD_ASSOC, DEL_ASSOC, ACTIVATE_ASSOC,
    GET_SCTP_ENDPOINT, SET_SCTP_ENDPOINT, MOD_SCTP_ENDPOINT, DEL_SCTP_ENDPOINT,
    GET_SCTP_PROFILE, SET_SCTP_PROFILE, MOD_SCTP_PROFILE, DEL_SCTP_PROFILE,
    GET_SIG_MULTIHOMING, SET_SIG_MULTIHOMING, MOD_SIG_MULTIHOMING, DEL_SIG_MULTIHOMING,
    DEL_AND_ADD_SIG_MULTIHOMING,//this is used to delete Multihoming IP for an Association
    GET_REMOTE_ROUTE, SET_REMOTE_ROUTE, MOD_REMOTE_ROUTE, DEL_REMOTE_ROUTE,
    GET_TRANSLATOR_RULE, SET_TRANSLATOR_RULE, MOD_TRANSLATOR_RULE, DEL_TRANSLATOR_RULE,
    GET_S6AMAP_DATA, SET_S6AMAP_DATA, MOD_S6AMAP_DATA, DEL_S6AMAP_DATA,
    GET_MAPS6A_DATA, SET_MAPS6A_DATA, MOD_MAPS6A_DATA, DEL_MAPS6A_DATA, GET_ALL_TRANSLATOR_DATA,
    GET_CAPRO_DATA, SET_CAPRO_DATA, MOD_CAPRO_DATA, DEL_CAPRO_DATA,
    GET_CAPRO_IDP_DATA,GET_CAPRO_IDPSMS_DATA,
    GET_IWF_TIMERS, SET_IWF_TIMERS, MOD_IWF_TIMERS, DEL_IWF_TIMERS, GET_ALL_IWF_TIMERS,
    GET_IWF_CAP_TIMERS, SET_IWF_CAP_TIMERS, MOD_IWF_CAP_TIMERS, DEL_IWF_CAP_TIMERS,
    GET_UAL_CONFIG, SET_UAL_CONFIG, MOD_UAL_CONFIG,
    SET_VPLMN_ID, MOD_VPLMN_ID, DEL_VPLMN_ID,
    SET_MAPS6A_VPLMN_ID_DATA, MOD_MAPS6A_VPLMN_ID_DATA, DEL_MAPS6A_VPLMN_ID_DATA,
    SET_VPLMN_ID_SGSN_MAP_DATA, MOD_VPLMN_ID_SGSN_MAP_DATA, DEL_VPLMN_ID_SGSN_MAP_DATA,
    GET_CAP_PROTO_TIMERS, SET_CAP_PROTO_TIMERS, MOD_CAP_PROTO_TIMERS,
    GET_IWF_FEATURES, SET_IWF_FEATURES, MOD_IWF_FEATURES, DEL_IWF_FEATURES, GET_ALL_IWF_FEATURES,
    GET_IWF_DCCA_FEATURES, SET_IWF_DCCA_FEATURES, MOD_IWF_DCCA_FEATURES, DEL_IWF_DCCA_FEATURES, GET_ALL_IWF_DCCA_CONFIG,
    GET_IWF_DCCA_DEST, SET_IWF_DCCA_DEST, MOD_IWF_DCCA_DEST, DEL_IWF_DCCA_DEST, DEL_IWF_DCCA_ENDPOINT, GET_ALL_IWF_DCCA_DEST,
    SET_IWF_PROT_ACTIONS, MOD_IWF_PROT_ACTIONS, GET_IWF_PROT_ACTIONS, DEL_IWF_PROT_ACTIONS, DEL_IWF_CALL_SCENARIO, DEL_IWF_EVENT_TYPE,
    DEL_IWF_EVENT_TYPE_CONFIG,GET_ALL_IWF_PROT_ACTIONS_CONFIG,CLEAR_SESSION, DUMP_SYSTEM_INFO
};

class LibCookie {
    public:
        LibCookie(void *agent, int reqID, void *respStr) :
            m_AgentCookie(agent), m_CReq(reqID) , m_CfgPtr(respStr)
    {};
        ~LibCookie(){};
        void *m_AgentCookie;
        int   m_CReq;
        void *m_CfgPtr;
};

// Cookie used internally by CMAPI
class CMAPICookie {
    public:
        CMAPICookie(unsigned Id, void *pVal):ReqID(Id),pValue(pVal) {}
        ~CMAPICookie() {}
        unsigned ReqID;
        void*    pValue;
};

class CMAPIIntSync
{
    public:
        CMAPIIntSync() : m_isDataSet (false){}
        ~CMAPIIntSync() {}

        void Get(std::string& data)
        {
            eAccelero::ScopedLock<eAccelero::Mutex> guard(m_cond.mutex());
            while(!m_isDataSet)
            {
                m_cond.wait();
            }
            data = m_data;
            m_isDataSet = false;
        }

        bool Get(std::string& data, int uSec)
        {
            eAccelero::ScopedLock<eAccelero::Mutex> guard(m_cond.mutex());
            while (!m_isDataSet)
            {
                if (m_cond.wait(uSec) != 0)
                {
                    return false;
                }
            }
            data = m_data;
            m_isDataSet = false;
            return true;
        }

        void Set(std::string& data)
        {
            eAccelero::ScopedLock<eAccelero::Mutex> guard(m_cond.mutex());
            m_data = data;
            m_isDataSet = true;
            m_cond.signal();
        }

        bool IsDataSet()
        {
            return m_isDataSet;
        }

    protected:
        eAccelero::CondVar m_cond;
        std::string m_data;
        bool    m_isDataSet;
};

#endif // __CMAPICOMMON_H__

