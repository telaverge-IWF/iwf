
#ifndef __COMMON_STRUCTURE_H__
#define __COMMON_STRUCTURE_H__
#include <config.h>
#include <stdarg.h>
/********** METHOD IDS ***********/
typedef enum _tmethodId {

    M_GET_PEER_TABLE = 1,
    M_SET_PEER_TABLE,
    M_MULTICAST_REQ,
    M_GET_CONFIG_PEER,
    M_SET_CONFIG_PEER,
    M_SHOW_PEER_STATUS,
    M_SHOW_REALM_CONFIG,
    M_SHOW_REALM_SUMMARY,
    M_SHOW_DISCOVER_PEER,
    M_SET_REALM_TABLE,
    M_SET_DEFAULT_ROUTE,
    M_SHOW_TASK,
    M_SHOW_DEVICE,
    M_SET_PEER_CONTROL,
    M_SHOW_DIAMETERBASE,
    M_SET_LOCALHOST,
    M_SET_DISCOVERY_INTERVAL,
    M_ADD_USER,
    M_DELETE_USER,
    M_SHOW_USER,
    M_VERIFY_PASSWORD,
    M_SHOW_CONFIG,
    M_SHOW_LOCALHOST,
    M_DELETE_PEERTABLE,
    M_DELETE_LOCALHOST,
    M_DELETE_REALMTABLE,
    M_PEER_SET_REQ,
    M_PEER_DELETE_REQ,
    M_GET_NODE_STATE_REQ,
    M_PEER_DISCOVERY_REQ,
    M_PEER_START_REQ,
    M_DEFAULT_ROUTE_REQ,
    M_SET_ASGROUP_REQ,
    M_MODIFY_ASGROUP_REQ,
    M_DELETE_ASGROUP_REQ,
    M_SHOW_ASGROUP_REQ,
    M_PEER_DICT_ID,
    M_PEER_DELETE_DICT_ID,
    M_SHOW_DICTIONARY,
    M_TERMINATE_ASGROUP_REQ,
    M_ASF_RESPONSE_TIMEOUT_REQ,
    M_ASF_CONFIG_REQ
}CliMethodID;

#ifdef FOR_IWF
#define DRE 0
#define IWF 1
#else
#define DRE 1
#define IWF 0
#endif

#define MIN_GT_ADDR_DIGITS 1
#define MAX_GT_ADDR_DIGITS 15

//#define CMGR_COMP_ID      101
//Need to change as per ComponentDefines.h. As of now hard-coding it.
#define CMGR_COMP_ID        1003
#define CLI_COMP_ID         102
#define AVMGR_COMP_ID       103
#define REPMGR_COMP_ID      104

//#define CLI_CMGR_INTERFACE_ID     11
#define CLI_CMGR_INTERFACE_ID   3
#define CLI_AVMGR_INTERFACE_ID  12
#define CLI_REPMGR_INTERFACE_ID 13
#define PASSWORD_LENGTH 16

#define MAX_NAME_LEN            32
#define MAX_IP_LEN              1024
#define MAX_LOG_LEVEL_LEN   10
#define MAX_LOG_CHAN_LEN        24
#define MAX_COMP_NAME_LEN   24
#define MAX_GRP_NAME_LEN        20
#define MAX_FILE_NAME_LEN       32  
#define MAX_LOCALTRANSPORT_ATTRIBUTES    4  
#define MAX_GRP_NAME    50
#define MAX_HEADER_LEN    1024
#define MAX_PAYLOAD_SIZE    8192
#define MAX_RECORD_SIZE     1024
#define MAX_PARAM_SIZE          256
#define MAX_IMSI_LENGTH 16

#define ENABLE          1
#define DISABLE         0
#define PEER_RESTART        3

#define TRANSTYPE_TCP       1
#define TRANSTYPE_SCTP      2
#define TRANSTYPE_TLS       3

#define NODE_DISCOVERY_YES  1
#define NODE_DISCOVERY_NO   0

#define MAX_TABLE_COUNT     9
#define MAX_DICTIONARY_NUM  8
#define MAX_PAYLOAD_LEN     65000
#define MAX_HOST_NAME   1024
#define MAX_SERVICE_KEY_DIGITS 2048
#define MAX_SSN_NUM    3
#define MAX_SSN_LENGTH 32
#define MAX_FAMILY_LENGTH 32
#define MAX_FIELD_NAME 64
#define MAX_SGSN_ADDR_MAP_NUM 10
#define MAX_BEARER_SERVICE_MAP 10
#define MAX_TELE_SERVICE_MAP 10
#define MAX_FEATURE_COUNT 60
#define MAX_DCCA_ENDPOINTS 2

#define MAX_VPLMN_ID_LENGTH 7
#define MAX_VPLMN_ID_COUNT 20
#define MAX_SGSN_NUM_COUNT 20
#define MAX_SGSN_NUM_LENGTH 21

#define MAX_IMSI_DIGITS 16

/* IWF - SSN */
#define HLR	6
#define SGSN 149
#define CAP 146
#define S6A_APPID "16777251"
#define RO_APPID "4"

/* MULTIPLE SERVICE INDICATOR */
enum _msIndicator {
    NOT_SUPPORTED = 0,
    SUPPORTED = 1
};

/* OP CODE */
typedef enum _opCode 
{
    ADD = 1,
    DELETE,
    MODIFY,
    LOAD,
    UNLOAD
}OpCode_e;
/* LOG Level */
typedef enum _loglevel
{
    CLI_FATAL = 0,
    CLI_CRITICAL,
    CLI_ERROR,
    CLI_WARNING,
    CLI_NOTICE,
    CLI_INFO,
    CLI_DEBUG
}log_level;

/* SHOW IDs */
#define SH_PEER_CONFIG      1
#define SH_PEER_STATUS      2
#define SH_REALM_CONFIG     3
#define SH_REALM_SUMMARY    4
#define SH_CONFIG_PEER_TABLE    5
#define SH_CONFIG_REALM     6
#define SH_DISCOVERED_PEERS 7
#define SH_DIAMETERBASE     8
#define SH_PEER_TIMER       9
#define SH_USERNAME     10
#define SH_LOCALHOST_CONFIG 11
#define SH_DRE_CONFIG       12
#define SH_AVLMGR_CONFIG    13
#define SH_REPMGR_CONFIG    14
#define SH_ASF          15
#define SH_ASFCONFIG        16
#define SH_ASFFEATURE       17
#define SH_DICTIONARY       18
#define SH_LOADED_DICTIONARY    19
#define SH_LOADED_TRANSFORM_PLUGIN 20
#define SH_INVALID      21

#define CLI_DEBUG_LOG(...) cli_log(__FUNCTION__,__LINE__,CLI_DEBUG,__VA_ARGS__);
#define CLI_ERROR_LOG(...) cli_log(__FUNCTION__,__LINE__,CLI_ERROR,__VA_ARGS__);
#define CLI_CRITICAL_LOG(...) cli_log(__FUNCTION__,__LINE__,CLI_CRITICAL,__VA_ARGS__);
#define CLI_INFO_LOG(...) cli_log(__FUNCTION__,__LINE__,CLI_INFO,__VA_ARGS__);
#define CLI_FATAL_LOG(...) cli_log(__FUNCTION__,__LINE__,CLI_FATAL,__VA_ARGS__);
#define CLI_NOTICE_LOG(...) cli_log(__FUNCTION__,__LINE__,CLI_NOTICE,__VA_ARGS__);
#define CLI_WARNING_LOG(...) cli_log(__FUNCTION__,__LINE__,CLI_WARNING,__VA_ARGS__);

/*Local action types */
#define LOCAL_ACTION_LOCAL 1
#define LOCAL_ACTION_RELAY 2
#define LOCAL_ACTION_PROXY 3
#define LOCAL_ACTION_REDIRECT 4

#define YES 1
#define NO 0
#define TRUE 1
#define FALSE 0

typedef enum _CMD_LINE_ARG {
    CMD_LINE_ARG_ZERO = 0,
    CMD_LINE_ARG_ONE,
    CMD_LINE_ARG_TWO,
    CMD_LINE_ARG_THREE,
    CMD_LINE_ARG_FOUR,
    CMD_LINE_ARG_FIVE,
    CMD_LINE_ARG_SIX,
    CMD_LINE_ARG_SEVEN,
    CMD_LINE_ARG_EIGHT
}CMD_LINE_ARG;


/*response codes*/
#define NODE_ACTIVE 100
#define NODE_STANDBY 101
#define DRE_CONFIG_ERROR 102
#define CMGR_CONFIG_ERROR 103
#define CMGR_FETCH_SUCCESS 104
#define CMGR_FETCH_ERROR 105
#define DEFAULT_OPTION 106
#define DRE_CONFIG_SUCCESS 107
#define DONT_ALLOW_STANDBY 108
#define IWF_CONFIG_SUCCESS 109
#define IWF_CONFIG_ERROR 110
/* UserConfig levels.Privilege  */

#define  PRIVILEGE_MIN              1
#define  PRIVILEGE_OPERATOR         2
#define  PRIVILEGE_ADMIN            3
#define  PRIVILEGE_TECH_SUPPORT     4
#define  PRIVILEGE_SEC_ADMIN        5
/* */

/*Defaults */
#define DEFAULT_DISCOVER_INTERVAL 120
/*1. PeerTable*/
typedef enum
{
    PEER_CLOSED,
    PEER_WAIT_CONN_ACK,
    PEER_WAIT_I_CEA,
    PEER_WAIT_CONN_ACK_ELECT,
    PEER_WAIT_RETURNS,
    PEER_I_OPEN,
    PEER_R_OPEN,
    PEER_CLOSING,
    PEER_MAX
}PEER_FSM_STATE;

typedef struct _DrePeerKeyInfo {
    char HostName[MAX_HOST_NAME];
    char RealmName[MAX_PARAM_SIZE];
}DrePeerKeyInfo;


typedef struct _DrePeerInfo {
    //int IpAddr;
    char IpAddr[MAX_IP_LEN];
    int PortNumber;
    int SecurePortNumber;
    char AltHostName[MAX_HOST_NAME];
    int IsMate;
    int TransportType;
    int TLS;
    int IsDisconnectCauseSupported;
    int Enable_Status;
    char secondaryIp[MAX_LOCALTRANSPORT_ATTRIBUTES][MAX_IP_LEN];
}DrePeerInfo;

typedef struct _DrePeerDictionaryInfo {
    OpCode_e OP_CODE;
    int num_dict;
    DrePeerKeyInfo peerKeyInfo;
    char PeerDictionaryIds[MAX_DICTIONARY_NUM][MAX_NAME_LEN];
    int dictionaryId[MAX_DICTIONARY_NUM];
}DrePeerDictionaryInfo;

typedef struct _DreDictionaryKeyInfo {
    char DictionaryName[MAX_NAME_LEN];
}DreDictionaryKeyInfo;

typedef struct _DreTransformPluginKeyInfo {
    char PluginName[MAX_NAME_LEN];
}DreTransformPluginKeyInfo;

typedef struct _DreTransformPluginLoadInfo {
    DreTransformPluginKeyInfo dreTransformPluginKeyInfo;
    char Dictionary1[MAX_NAME_LEN];
    char Dictionary2[MAX_NAME_LEN];
    char ConfigFileName[MAX_NAME_LEN];
}DreTransformPluginLoadInfo;

typedef struct _DtfPayload {
    DreDictionaryKeyInfo dreDictionaryKeyInfo;
    DreTransformPluginLoadInfo dreTransformPluginLoadInfo;
}DtfPayload;

typedef struct _DrePeerSwitchingInfo{
    int Failover;
    int Failback;
}DrePeerSwitchingInfo;

typedef struct _DrePeerPayload {
    DrePeerKeyInfo peerKeyInfo;
    DrePeerInfo peerInfo ;
    DrePeerSwitchingInfo peerSwitchingInfo;
    DrePeerDictionaryInfo peerDictionaryInfo;
}DrePeerPayload; 
/*2. Realm Table*/
typedef struct _DreRealmRoutingKeyInfo {
    char RealmName[MAX_PARAM_SIZE];
    char PeerHostId[MAX_HOST_NAME];
    long AppId;
}DreRealmRoutingKeyInfo;

typedef struct _DreRealmRoutingInfo {
    int LocalAction;
    long VendorID;
    int Priority;
    int NodeDiscovery;
    int RedirectHostUsage;
    int RedirectMaxCacheTime;
    char AltRealmName[MAX_PARAM_SIZE]; 
    int EnableProxyInfo;
}DreRealmRoutingInfo;


typedef struct _DreRealmRoutingPayload {
    DreRealmRoutingKeyInfo realmKeyInfo;
    DreRealmRoutingInfo realmInfo;
}DreRealmRoutingPayload;

/*3. Default Route Table*/
typedef struct _DreDefaultRouteKeyInfo {
    char RealmName[MAX_PARAM_SIZE];
}DreDefaultRouteKeyInfo;

typedef struct _DreDefaultRouteConfigInfo {
    /*There can be multiple host-ids here BUT Max 8*/
    char PeerHostIds[MAX_HOST_NAME]; 
}DreDefaultRouteConfigInfo;

typedef struct _DreDefaultRoutePayload {
    DreDefaultRouteKeyInfo defaultRouteKeyInfo;
    DreDefaultRouteConfigInfo defaultRouteInfo;
}DreDefaultRoutePayload;

/*4. LocalHostConfig Table*/
typedef struct _DreLocalHostKeyInfo {
    char HostName[MAX_HOST_NAME];
    char RealmName[MAX_PARAM_SIZE];
}DreLocalHostKeyInfo;

typedef struct _DreLocalHostTransportInfo {
    char IpAddr[MAX_LOCALTRANSPORT_ATTRIBUTES][MAX_IP_LEN];
    char PublicIpAddr[MAX_LOCALTRANSPORT_ATTRIBUTES][MAX_IP_LEN];
    int portno[MAX_LOCALTRANSPORT_ATTRIBUTES];
    int secureportno[MAX_LOCALTRANSPORT_ATTRIBUTES];
    int transportType[MAX_LOCALTRANSPORT_ATTRIBUTES]; /*TCP/SCTP*/
    int transport_count;
    char secondaryIp[MAX_LOCALTRANSPORT_ATTRIBUTES][MAX_LOCALTRANSPORT_ATTRIBUTES][MAX_IP_LEN];
    int transport_id[MAX_LOCALTRANSPORT_ATTRIBUTES];
}DreLocalHostTransportInfo;

typedef struct _DreLocalHostAcctTimersInfo {
    long Interim;
    long TimeOut;
}DreLocalHostAcctTimersInfo;

typedef struct _DreLocalHostAuthTimersInfo {
    long LifeTime;
    long GraceTime;
    long TimeOut;
}DreLocalHostAuthTimersInfo;


typedef struct _DreLocalHostPayloadInfo {
    DreLocalHostKeyInfo LocalHostKeyInfo;
    DreLocalHostTransportInfo LocalHostTransportInfo;
    DreLocalHostAuthTimersInfo LocalHostAuthInfo;
    DreLocalHostAcctTimersInfo LocalHostAcctInfo;
}DreLocalHostPayload;


/* 5. PeerGlobalConfigTable */
typedef struct _DreOverPeerGlobalConfigKeyInfo {
    int ComponentID;
}DrePeerGlobalConfigKeyInfo;

typedef struct _DrePeerGlobalConfigInfo {
    long DiscoveryInterval;
}DrePeerGlobalConfigInfo;

typedef struct _DrePeerGlobalConfigPayload {
    DrePeerGlobalConfigKeyInfo PeerGlobalConfigKeyInfo;
    DrePeerGlobalConfigInfo PeerGlobalConfigInfo;
}DrePeerGlobalConfigPayload;

/* 6. Dynamic Discovery Table */
typedef struct _DreDynamicDiscoveryKeyInfo {
    char RealmName[MAX_PARAM_SIZE];
}DreDynamicDiscoveryKeyInfo;

typedef struct _DreDynamicDiscoveryConfigInfo {
    char peerHostNames[MAX_HOST_NAME];
}DreDynamicDiscoveryConfigInfo;

typedef struct _DreDynamicDiscoveryConfigPayload {
    DreDynamicDiscoveryKeyInfo DynamicDiscoveryKeyInfo;
    DreDynamicDiscoveryConfigInfo DynamicDiscoveryConfigInfo;
}DreDynamicDiscoveryConfigPayload;

/* 7. Peer Timers Table */
typedef struct _DrePeerTimersKeyInfo {
    char peerHostNames[MAX_HOST_NAME];
    char realmName[MAX_PARAM_SIZE];
}DrePeerTimersKeyInfo;

typedef struct _DrePeerTimersConfigInfo {
    int watchdogValue;
    int TCValue;
    int expiryValue;
    int busyReconnectTimerVal;
    int doNotWantToTalkToYouReconnectTimer;
}DrePeerTimersConfigInfo;

typedef struct _DrePeerTimersConfigPayload {
    DrePeerTimersKeyInfo PeerTimersKeyInfo;
    DrePeerTimersConfigInfo PeerTimersConfigInfo;
}DrePeerTimersConfigPayload;

/* 8. User Table */
typedef struct _DreUserKeyInfo {
    char UserName[MAX_NAME_LEN];
}DreUserKeyInfo;

typedef struct _DreUserConfigInfo {
    unsigned char password[MAX_NAME_LEN];
    int privilege;
}DreUserConfigInfo;

typedef struct _DreUserConfigPayload {
    DreUserKeyInfo UserKeyInfo;
    DreUserConfigInfo UserConfigInfo;
}DreUserConfigPayload;

//Static Routing Structures
typedef struct _staticroutingdestination {
    char dest_hostname[MAX_HOST_NAME];
    char dest_realmname[MAX_PARAM_SIZE];
}staticroutingdestination;

typedef struct _staticroutingpeer {
    char peername[MAX_HOST_NAME];
    char realmname[MAX_PARAM_SIZE];
    long appId;
    int priority;
}staticroutingpeer;

typedef struct _StaticRouting {
    staticroutingdestination dest_info;
    staticroutingpeer peer_info;
}StaticRoutingPayload;

/***********************ASF structures **************************/

typedef struct _DreASFKeyInfo {
    char GroupName[MAX_GRP_NAME];
}DreASFKeyInfo;

typedef struct _DreASFConfigInfo {
    int priority;
    int appType;
    char lbAlgorithm[MAX_NAME_LEN];
    int maxAppInstances;    
    int instanceId;
}DreASFConfigInfo;

typedef struct _DreASFPayload {
    DreASFKeyInfo dreASFKeyInfo;
    DreASFConfigInfo dreASFConfigInfo;
}DreASFAppGroupPayload;


typedef struct _DreASFConfigKeyInfo {
    int ComponentID;
}DreASFConfigKeyInfo;

typedef struct _DreASFRespTimeout {
    int responseTimeout;
}DreASFRespTimeout;

typedef struct _DreASFStatus {
    int ASFStatus;
    int ERLBFStatus;
}DreASFStatus;


typedef struct _DreASFConfig{
    DreASFConfigKeyInfo dreASFConfigKeyInfo;
    DreASFRespTimeout dreASFRespTimeout;
    DreASFStatus dreASFStatus;
}DreASFConfigPayload;

//Erlbf structs
typedef struct _peergroup {
    char groupname[MAX_GRP_NAME];
    char lb_algo[MAX_NAME_LEN];
    int pcrf_binding;
}peergroup;

typedef struct _ErlbfPeer {
    char peer_name[MAX_HOST_NAME];
    char realmName[MAX_PARAM_SIZE];
    int  peer_weight;
    int  peer_priority;
}ErlbfPeer;

typedef struct _PeerGroups{
    peergroup peer_group;   
    ErlbfPeer peer_info; 
}PeerGroupsPayload;

/**************************** IWF - SIGTRAN CONFIG Tables ******************************/
// Local Config Structures
typedef enum _NetworkIndicator {
    INTERNATIONAL = 0,
    NATIONAL
}NetworkIndicator;

typedef struct _IWFLocalHostKeyInfo {
    char family[MAX_FAMILY_LENGTH];
    int pointcode;
}IWFLocalHostKeyInfo;

typedef enum _SelectionCriteria {
    MCC_MNC = 1,
    APP_ID = 4,
    MCC_MNC_AND_APP_ID = 5,
    GTT = 8,
    GTT_AND_MCC_MNC = 9,
    SK = 16,
    SK_AND_MCC_MNC = 17,
    GTT_AND_SK = 24,
    IMSI_PREFIX_AND_SK = 25
}SelectionCriteria;


typedef struct _IWFLocalHostConfigInfo {
    int ni;
    char ssn[MAX_SSN_NUM][MAX_SSN_LENGTH];
    int num_ssn_configured;
    long tcap_invoke_timer;
    int gti;
    char routing_indicator[MAX_FIELD_NAME];
    long long translation_type;
    int numbering_plan;
    int encoding_scheme;
    long nature_of_addr_indicator;
    int selection_criteria;
    char global_title_addr_info[MAX_FIELD_NAME];
    int use_local_gt_from_config;
    int use_sccp_cdpa_from_in_msg;
    int include_ssn;
    int include_pc;
    char hostname1[MAX_HOST_NAME];
    char hostname2[MAX_HOST_NAME];
    int aspid1;
    int aspid2;
}IWFLocalHostConfigInfo;

typedef struct _IWFLocalHostConfigPayload {
    IWFLocalHostKeyInfo iwfLocalHostKeyInfo;
    IWFLocalHostConfigInfo iwfLocalHostConfigInfo;
}IWFLocalHostConfigPayload;

//SCTP End Point Config Structures
typedef struct _SCTPEndPointConfigKeyInfo {
    char endpoint[MAX_FIELD_NAME];
}SCTPEndPointConfigKeyInfo;

typedef struct _SCTPEndPointConfigInfo {
    char ipaddr[MAX_IP_LEN];
    int port;
    char type[MAX_FIELD_NAME];
    char secondaryIp[MAX_LOCALTRANSPORT_ATTRIBUTES][MAX_IP_LEN];
}SCTPEndPointConfigInfo;

typedef struct _SCTPEndPointConfigPayload {
    SCTPEndPointConfigKeyInfo sctpEndPointConfigKeyInfo;
    SCTPEndPointConfigInfo sctpEndPointConfigInfo;
}SCTPEndPointConfigPayload;

//SCTP Profile Config Structures
typedef struct _SCTPProfileConfigKeyInfo {
    char profilename[MAX_FIELD_NAME];
}SCTPProfileConfigKeyInfo;

typedef struct _SCTPProfileConfigInfo {
    int heartbeat;
    int heartbeattimeout;
    int rtoinit;
    int rtomin;
    int rtomax;
    int inittimeout;
    int maxattempts;
    int assocmaxattempts;
    int pathfailureretrycount;
    int receivetimeout;
    int shutdowntimeout;
    int pathmaxretransmit;
    int reconnecttimeout;
    int sendbuffsize;
    int receivebuffsize;
    int cookielife;
    int sackdelay;
    int maxinstreams;
    int numofoutstreams;
}SCTPProfileConfigInfo;

typedef struct _SCTPProfileConfigPayload {
    SCTPProfileConfigKeyInfo sctpProfileConfigKeyInfo;
    SCTPProfileConfigInfo sctpProfileConfigInfo;
}SCTPProfileConfigPayload;

//Association Config Structures
typedef struct _AssociationConfigKeyInfo {
    char associationname[MAX_FIELD_NAME];
}AssociationConfigKeyInfo;

typedef struct _AssociationConfigInfo {
    char association_set[MAX_FIELD_NAME];
    char sctp_profile_name[MAX_FIELD_NAME];
    char local_sctp_end_point[MAX_FIELD_NAME];
    char remote_sctp_end_point[MAX_FIELD_NAME];
    int status;
    int aspId;
}AssociationConfigInfo;

typedef struct _AssociationConfigPayload {
    AssociationConfigKeyInfo associationConfigKeyInfo;
    AssociationConfigInfo associationConfigInfo;
}AssociationConfigPayload;

//UAL Config Structures
typedef struct _UALSetConfigInfo {
    int ack_timer;
    char sigtran_mode[MAX_FIELD_NAME];
}UALSetConfigInfo;

typedef struct _UALSetConfigPayload {
    UALSetConfigInfo ualSetConfigInfo;
}UALSetConfigPayload;

//Association-Set Config Structures
typedef struct _AssociationSetConfigKeyInfo {
    char assocsetname[MAX_FIELD_NAME];
}AssociationSetConfigKeyInfo;

typedef struct _AssociationSetConfigInfo {
    char family[MAX_FAMILY_LENGTH];
    int ni;
    int pointcode;
    int routing_key;
    char traffic_mode[MAX_FIELD_NAME];
    int asp_id;
    int status;
    int isMember;
    char homeIp[MAX_FIELD_NAME];
}AssociationSetConfigInfo;

typedef struct _AssociationSetConfigPayload {
    AssociationSetConfigKeyInfo associationSetConfigKeyInfo;
    AssociationSetConfigInfo associationSetConfigInfo;
}AssociationSetConfigPayload;

//Destination Config Structures
typedef struct _DestinationConfigKeyInfo {
    char dest_name[MAX_FIELD_NAME];
}DestinationConfigKeyInfo;

typedef struct _DestinationConfigInfo {
    char family[MAX_FAMILY_LENGTH];
    int ni;
    int pointcode;
    char ssn[MAX_SSN_LENGTH];
    int gti;
    char routing_indicator[MAX_FIELD_NAME];
    long long translation_type;
    int numbering_plan;
    int encoding_scheme;
    long nature_of_addr_indicator;
    char global_title_addr_info[MAX_FIELD_NAME];
}DestinationConfigInfo;

typedef struct _DestinationConfigPayload {
    DestinationConfigKeyInfo destinationConfigKeyInfo;
    DestinationConfigInfo destinationConfigInfo;
}DestinationConfigPayload;

//RemoteRoute Config Structures
typedef struct _RemoteRouteConfigKeyInfo {
    char route_name[MAX_FIELD_NAME];
}RemoteRouteConfigKeyInfo;

typedef struct _RemoteRouteConfigInfo {
    char dest_name[MAX_FIELD_NAME];
    char assocsetname[MAX_FIELD_NAME];
    int priority;
}RemoteRouteConfigInfo;

typedef struct _RemoteRouteConfigPayload {
    RemoteRouteConfigKeyInfo remoteRouteConfigKeyInfo;
    RemoteRouteConfigInfo remoteRouteConfigInfo;
}RemoteRouteConfigPayload;

//ProtocolAction Config Structures
#define MAX_CALL_SCENARIOS 10
#define MAX_EVENT_TYPES 10
#define MAX_EVENT_TYPES_CONFIG 10

typedef enum _ActionIds {
    RRB_ACTION = 1
}ActionIds;

typedef struct _ProtocolActionConfigKeyInfo {
    char protocol[MAX_FIELD_NAME];
    char rule_name[MAX_FIELD_NAME];
    char actionId[MAX_FIELD_NAME];
}ProtocolActionConfigKeyInfo;

typedef struct _ProtocolActionConfigInfo {
    int num_of_callscenarios;
    int current_callscenario;
    int num_of_eventtypes;
    int current_eventType;
    char callscenario[MAX_CALL_SCENARIOS][MAX_FIELD_NAME];
    char eventType[MAX_CALL_SCENARIOS][MAX_EVENT_TYPES][MAX_FIELD_NAME];
    char monitorMode[MAX_CALL_SCENARIOS][MAX_EVENT_TYPES][MAX_EVENT_TYPES_CONFIG][MAX_FIELD_NAME];
    char legId[MAX_CALL_SCENARIOS][MAX_EVENT_TYPES][MAX_EVENT_TYPES_CONFIG][MAX_FIELD_NAME];
}ProtocolActionConfigInfo;

typedef struct _ProtocolActionConfigPayload {
    ProtocolActionConfigKeyInfo protocolActionConfigKeyInfo;
    ProtocolActionConfigInfo protocolActionConfigInfo;
}ProtocolActionConfigPayload;

//Translator Rule Config Structures
typedef struct _TranslatorRuleConfigKeyInfo {
    char rule_name[MAX_FIELD_NAME];
}TranslatorRuleConfigKeyInfo;

typedef struct _TranslatorRuleConfigInfo {
    char translation_type[MAX_FIELD_NAME];
    char translator[MAX_FIELD_NAME];
    char destination[MAX_FIELD_NAME];
    char dest_host[MAX_FIELD_NAME];
    char alt_host[MAX_FIELD_NAME];
    char alt_realm[MAX_FIELD_NAME];
    char mcc[MAX_FIELD_NAME];
    char mnc[MAX_FIELD_NAME];
    char ossn[MAX_FIELD_NAME];
    char dssn[MAX_FIELD_NAME];
    char app_id[MAX_FIELD_NAME];
    char http_url[MAX_FIELD_NAME];
    char web_service[MAX_FIELD_NAME];
    int isRangeDefined;
    int service_key_start_value;
    int service_key_end_value;
    char serviceKey[MAX_SERVICE_KEY_DIGITS];
    char proActionRule[MAX_FIELD_NAME];
    char imsiPrefix[MAX_IMSI_DIGITS];
    char calling_gt_address_digits[MAX_FIELD_NAME];
    char serviceContextId[MAX_FIELD_NAME];
    int vplmn_id_count;
    char vplmn_id[MAX_VPLMN_ID_COUNT][MAX_VPLMN_ID_LENGTH];
}TranslatorRuleConfigInfo;

typedef struct _TranslatorRuleConfigPayload {
    TranslatorRuleConfigKeyInfo translatorRuleConfigKeyInfo;
    TranslatorRuleConfigInfo translatorRuleConfigInfo;
}TranslatorRuleConfigPayload;

//S6a-MAP Config Structures
typedef struct _S6aMAPConfigKeyInfo {
    char translator_name[MAX_FIELD_NAME];
}S6aMAPConfigKeyInfo;

typedef struct _S6aMAPConfigInfo {
    char local_sgsn_num[MAX_SGSN_NUM_LENGTH];
    char routing_prefix[MAX_SGSN_NUM_LENGTH];
    int sgsn_addr_map_count;
    int sgsn_prefix_map_count;
    char org_host[MAX_SGSN_ADDR_MAP_NUM][MAX_HOST_NAME];
    char ip_addr[MAX_SGSN_ADDR_MAP_NUM][MAX_IP_LEN];
    char vplmnId[MAX_SGSN_ADDR_MAP_NUM][MAX_VPLMN_ID_LENGTH];
    char sgsn_prefix[MAX_SGSN_ADDR_MAP_NUM][MAX_SGSN_NUM_LENGTH];
}S6aMAPConfigInfo;

typedef struct _S6aMAPConfigPayload {
    S6aMAPConfigKeyInfo s6aMAPConfigKeyInfo;
    S6aMAPConfigInfo s6aMAPConfigInfo;
}S6aMAPConfigPayload;

//MAP-S6a Config Structures
typedef struct _MAPS6aConfigKeyInfo {
    char translator_name[MAX_FIELD_NAME];
}MAPS6aConfigKeyInfo;

typedef struct _MAPS6aConfigInfo {
    char hlr_number[MAX_FIELD_NAME];
    int vplmn_id_count;
    char vplmn_id[MAX_VPLMN_ID_COUNT][MAX_VPLMN_ID_LENGTH];
    char sgsn_number[MAX_VPLMN_ID_COUNT][MAX_SGSN_NUM_COUNT][MAX_SGSN_NUM_LENGTH];
}MAPS6aConfigInfo;

typedef struct _MAPS6aConfigPayload {
    MAPS6aConfigKeyInfo mapS6aConfigKeyInfo;
    MAPS6aConfigInfo mapS6aConfigInfo;
}MAPS6aConfigPayload;

//CAP-Ro Config Structures
//IDP Config Structures
typedef struct _CAPRoIDPConfigKeyInfo {
    char translator_name[MAX_FIELD_NAME];
}CAPRoIDPConfigKeyInfo;

typedef struct _CAPRoIDPConfigInfo {
    int node_functionality;
    char sip_method[MAX_FIELD_NAME];
    char originating_ioi[MAX_FIELD_NAME];
    char terminating_ioi[MAX_FIELD_NAME];
    char service_context_id[MAX_FIELD_NAME];
    char cause_code[MAX_FIELD_NAME];
    int msc_service_specific_type;
    int gmsc_service_specific_type;
    int cpc_service_specific_type;
    int multi_service_indicator;
    int ext_tele_service_map_count;
    int ext_tele_service[MAX_TELE_SERVICE_MAP];
    int tele_service_id[MAX_TELE_SERVICE_MAP];
    int ext_bearer_service_map_count;
    int ext_bearer_service[MAX_BEARER_SERVICE_MAP];
    int bearer_service_id[MAX_BEARER_SERVICE_MAP];
}CAPRoIDPConfigInfo;

typedef struct _CAPRoIDPConfigPayload {
    CAPRoIDPConfigKeyInfo capRoIDPConfigKeyInfo;
    CAPRoIDPConfigInfo capRoIDPConfigInfo;
}CAPRoIDPConfigPayload;

//IDP-SMS Condig Structures
typedef struct _CAPRoIDPSMSConfigKeyInfo {
    char translator_name[MAX_FIELD_NAME];
}CAPRoIDPSMSConfigKeyInfo;

typedef struct _CAPRoIDPSMSConfigInfo {
    int sms_node;
    char client_addr[MAX_FIELD_NAME];
    char originator_sccp_addr[MAX_FIELD_NAME];
    int reply_path_request;
    int msc_service_specific_type;
    int sgsn_service_specific_type;
    char service_context_id[MAX_FIELD_NAME];
}CAPRoIDPSMSConfigInfo;

typedef struct _CAPRoIDPSMSConfigPayload {
    CAPRoIDPSMSConfigKeyInfo capRoIDPSMSConfigKeyInfo;
    CAPRoIDPSMSConfigInfo capRoIDPSMSConfigInfo;
}CAPRoIDPSMSConfigPayload;

//IWF-Feature Config Structures

typedef enum _LogCDRStatus {
    DISABLE_ALL_CALLS = 0,
    DISABLE_ONLY_SUCCESS_CALLS,
    ENABLE_ONLY_FAILED_CALLS,
    ENABLE_ALL_CALLS
}LogCDRStatus;

typedef struct _IWFFeatureConfigKeyInfo {
    char feature_name[MAX_FIELD_NAME];
}IWFFeatureConfigKeyInfo;

typedef struct _IWFFeatureConfigInfo {
    int status;
    int64_t maxNumberOfCalls;
}IWFFeatureConfigInfo;

typedef struct _IWFFeatureConfigPayload {
    IWFFeatureConfigKeyInfo iwfFeatureConfigKeyInfo;
    IWFFeatureConfigInfo iwfFeatureConfigInfo;
}IWFFeatureConfigPayload;

//CAP-Proto-Timers Structures
#define NO_ACTIVITY_TIMER "NO_ACTIVITY_TIMER"
#define RETRY_COUNT "ACTIVITY_RETRY_COUNT"
#define RESPONSE_TIMEOUT "ACTIVITY_RESPONSE_TIMEOUT"
#define VOICE_NO_ANSWER_TIMER "VOICE_NO_ANSWER_TIMER"
#define NETWORK_DELAY_TIMER "NETWORK_DELAY_TIMER"
#define SMS_NO_EVENT_TIMER "SMS_NO_EVENT_TIMER"

typedef struct _CAPProtoTimersConfigInfo {
    int no_activity_timer;
    int retry_count;
    int response_timeout;
    int voice_no_answer_timer;
    int network_delay_timer;
    int sms_no_event_timer; 
}CAPProtoTimersConfigInfo;

typedef struct _CAPProtoTimersConfigPayload {
    CAPProtoTimersConfigInfo capProtoTimersConfigInfo;
}CAPProtoTimersConfigPayload;

// IWF - DCCA General Configuration
typedef enum _FailureHandlingStatus {
    TERMINATE = 0,
    CONTINUE,
    RETRY_AND_TERMINATE
}FailureHandlingStatus;

typedef struct _IWFDccaGeneralConfigKeyInfo {
    char dcca_feature_name[MAX_FEATURE_COUNT][MAX_FIELD_NAME];
}IWFDccaGeneralConfigKeyInfo;

typedef struct _IWFDccaGeneralConfigInfo {
    int dcca_feature_value[MAX_FEATURE_COUNT];
}IWFDccaGeneralConfigInfo;

typedef struct _IWFDccaGeneralConfigPayload {
    IWFDccaGeneralConfigKeyInfo iwfDccaGeneralConfigKeyInfo;
    IWFDccaGeneralConfigInfo iwfDccaGeneralConfigInfo;
}IWFDccaGeneralConfigPayload;

// IWF - DCCA Destination Configuration
typedef struct _IWFDccaDestinationConfigKeyInfo {
    char dest_realm[MAX_FIELD_NAME];
}IWFDccaDestinationConfigKeyInfo;

typedef struct _IWFDccaDestinationConfigInfo {
    int sendCCRT;
    char endPoint[MAX_DCCA_ENDPOINTS][MAX_FIELD_NAME];
    int priority[MAX_DCCA_ENDPOINTS];
}IWFDccaDestinationConfigInfo;

typedef struct _IWFDccaDestinationConfigPayload {
    IWFDccaDestinationConfigKeyInfo iwfDccaDestinationConfigKeyInfo;
    IWFDccaDestinationConfigInfo iwfDccaDestinationConfigInfo;
}IWFDccaDestinationConfigPayload;


/**************************** Replication Manager Tables *******************************/

/* 1. Replication State Table */
typedef struct _RepMgrReplStateKeyInfo {
    int ComponentID;
}RepMgrReplStateKeyInfo;

typedef struct _RepMgrReplStateConfigInfo {
    int ReplicationState;
}RepMgrReplStateConfigInfo;

typedef struct _RepMgrReplStateConfigPayload {
    RepMgrReplStateKeyInfo ReplStateKeyInfo;
    RepMgrReplStateConfigInfo ReplStateConfigInfo;
}RepMgrReplStateConfigPayload;
/**************************** STACK GENERAL CONFIG TABLES *******************************/
typedef struct _PeerIpCheck {
    int ipcheck;
}PeerIpCheck;

typedef struct _PredictiveLoopdetection {
    int predectiveloopdetection;
}PredictiveLoopdetection;

typedef struct _SNaptrSupport {
    int snaptrsupport;
}SNaptrSupport;

typedef struct _SctpConfig {
    int heartbeat;
    int heartbeattimeout;
    int rtoinit;
    int rtomin;
    int rtomax;
    int inittimeout;
    int maxattempts;
    int pathfailureretrycount;
}SctpConfig;

typedef struct _Tlsconfig {
    int identityverification;
    int crlverification;
}Tlsconfig;

typedef struct _CipherSuite {
    char ciphersuitename[MAX_NAME_LEN];
    int cipherenable;
}CipherSuite;

typedef struct _TrustedCa {
    char cafile[MAX_NAME_LEN];
    char crlfile[MAX_NAME_LEN];
}TrustedCa;

/**************************** Availability Manager Tables *******************************/

/* 1. Availability Manager Config Table */
typedef struct _AvaMgrConfigKeyInfo {
    int ComponentID;
}AvaMgrConfigKeyInfo;

typedef struct _AvaMgrConfigInfo {
    long PingPeriodicity;
    long PingPeriodicityForArbitrator;
    long VirtualInterfaceActivationTime;
    long NumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeer;
    long NumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitrator;
    long ProcessRestartMaximumAllowedInterval;
    long ProcessRestartMaximumAllowedCount;
    int UseIpV6;
    char PrimaryVirtualIpAddress[64];
    char SecondaryVirtualIpAddress[64];
    char GatewayIpAddress[64];
}AvaMgrConfigInfo;

typedef struct _AvaMgrConfigPayload {
    AvaMgrConfigKeyInfo avaMgrConfigKey;
    AvaMgrConfigInfo avaMgrConfigInfo;
}AvaMgrConfigPayload;

typedef struct _DrePeerPayloadAndTimerPayload {
    DrePeerPayload          drePeerPayload;
    DrePeerTimersConfigPayload  drePeerTimersConfigPayload;
}DrePeerPayloadAndTimerPayload;

typedef struct _DreLoggingPayload {
    char compName[MAX_COMP_NAME_LEN];
    char logLevel[MAX_LOG_LEVEL_LEN];
    char logChannel[MAX_FILE_NAME_LEN];
}DreLoggingPayload;


/**************************** ALL PAYLOADS *****************************/
typedef union _drePayload {
    DrePeerPayload drePeerPayload;
    DreRealmRoutingPayload dreRealmPayload;
    DreLocalHostPayload dreLocalHostPayload;
    DrePeerGlobalConfigPayload dreGlobalConfigPayload;
    DreDefaultRoutePayload dreDefaultRoutePayload;
    DreDynamicDiscoveryConfigPayload dreDynamicDiscoveryPayload;
    DrePeerTimersConfigPayload  drePeerTimersConfigPayload;
    RepMgrReplStateConfigPayload repMgrReplStateConfigPayload;
    AvaMgrConfigPayload avaMgrConfigPayload;
    DrePeerPayloadAndTimerPayload drePeerAndTimerConfigPayload;
    DreUserConfigPayload dreUserConfigPayload;
    DreASFAppGroupPayload dreASFAppGroupPayload;
    DreASFConfigPayload dreASFConfigPayload;
    PeerGroupsPayload   peerGroupsPayload;
    DtfPayload dtfPayload;
    DreLoggingPayload loggingPayload;
    PeerIpCheck peeripcheck;
    PredictiveLoopdetection predictiveLoopdetection;
    SNaptrSupport snaptrSupport;
    SctpConfig sctpconfig;
    Tlsconfig tlsconfig;
    CipherSuite ciphersuite;
    TrustedCa trustedca;
    StaticRoutingPayload staticRoutingPayload;
}drePayload;

typedef union _iwfPayload {
    IWFLocalHostConfigPayload iwfLocalHostConfigPayload;
    SCTPEndPointConfigPayload sctpEndPointConfigPayload;
    SCTPProfileConfigPayload sctpProfileConfigPayload;
    AssociationConfigPayload associationConfigPayload;
    AssociationSetConfigPayload associationSetConfigPayload;
    DestinationConfigPayload destinationConfigPayload;
    RemoteRouteConfigPayload remoteRouteConfigPayload;
    TranslatorRuleConfigPayload translatorRuleConfigPayload;
    S6aMAPConfigPayload s6aMAPConfigPayload;
    MAPS6aConfigPayload mapS6aConfigPayload;
    CAPRoIDPConfigPayload capRoIDPConfigPayload;
    CAPRoIDPSMSConfigPayload capRoIDPSMSConfigPayload;
    UALSetConfigPayload ualSetConfigPayload;
    CAPProtoTimersConfigPayload capProtoTimersConfigPayload;
    IWFFeatureConfigPayload iwfFeatureConfigPayload;
    IWFDccaGeneralConfigPayload iwfDccaGeneralConfigPayload;
    IWFDccaDestinationConfigPayload iwfDccaDestinationConfigPayload;
    ProtocolActionConfigPayload protocolActionConfigPayload;
    char ImsiForSessionClearance[MAX_IMSI_LENGTH];
}iwfPayload;

typedef union _dreKeyInfo
{
    DrePeerKeyInfo peerKeyInfo;
    DreUserKeyInfo UserKeyInfo;
    DreRealmRoutingKeyInfo realmKeyInfo;
}DreKeyInfo;

typedef struct _showReqPayload {
    DreKeyInfo dreKeyInfo;     
    int showID;             /* any of above defined Show-IDs */
}showReqPayload;

struct AvaMgrConfigPrimaryVirtualIpAddressReq {
    char cConfigPrimaryVirtualIpAddress[MAX_PARAM_SIZE];
    char cConfigDev[MAX_RECORD_SIZE];
};

#if 0
typedef union _repMgrPayload {
    RepMgrReplStateConfigPayload repMgrReplStateConfigPayload;
}repMgrPayload;

typedef union _avaMgrPayload {
    AvaMgrConfigPayload avaMgrConfigPayload;
}avaMgrPayload;

typedef union _requestPayload {
    drePayload DrePayLoad;
    repMgrPayload RepPayLoad;
    avaMgrPayload AvaPayLoad;
}requestPayload;

#endif

/***************************** SET CONFIG REQUEST ******************************/
typedef struct _SetConfigReq {
    int cmd_id;
    OpCode_e OP_CODE;
    drePayload Payload;
    iwfPayload IWFPayload;
}SetConfigReq;

/***************************** SET CONFIG RESPONSE *****************************/
typedef struct _SetConfigRsp {
    int cmd_id;
    int ResponseCode;
}SetConfigRsp;


/***************************** GET CONFIG REQUEST ******************************/
typedef struct _GetConfigReq {
    int cmd_id;
    showReqPayload shReqPayload;
}GetConfigReq;



/***************************** GET CONFIG RESPONSE *****************************/

typedef struct _GetConfigRsp {
    int cmd_id;
    int ResponseCode;
    int table_count;
    int record_count[DRE_TABLE_COUNT];
    dreDataType_e datatype_names[DRE_DATATYPE_COUNT];
    drePayload payload[DRE_TABLE_COUNT][MAX_RECORD_SIZE];
}GetConfigRsp;

typedef struct _GetConfigPeerResp {
    int cmd_id;
    int record_count;
    char payload[MAX_PAYLOAD_SIZE];
}GetConfigResp;

typedef struct _NoResponse{
    int cmd_id;
    char msg[128];
}NoResponse;

typedef struct _AllResponses {
    int cmd_id;
    int ResponseCode;
    char password[32];
    char payload[MAX_PAYLOAD_LEN];
}AllResponses;

typedef struct ClientInfo{
    int udpPort;
    int clientCookie;
}ClientInfo;

typedef struct _SetReqCookie{
    ClientInfo clientInfo;
    void *req;
}SetReqCookie;

#endif

