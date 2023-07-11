/*********************************-*HPP*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: dia_parse.h,v $
 * LOG: Revision 3.22.4.8.4.1.4.4.8.1.4.1  2014/12/04 12:00:16  pramana
 * LOG: Added support for allowing requests for a different hosts
 * LOG:
 * LOG: Revision 3.22.4.8.4.1.4.4.8.1  2014/07/10 06:57:04  millayaraja
 * LOG: fix for updating TCP connectonTimeout
 * LOG:
 * LOG: Revision 3.22.4.8.4.1.4.4  2013/12/13 09:34:58  vsarath
 * LOG: Merged the session-splict changes
 * LOG:
 * LOG: Revision 3.22.4.8.4.1.4.3  2013/12/09 04:52:43  ncshivakumar
 * LOG: Fixed bug 2439,2443,2368,1898
 * LOG:
 * LOG: Revision 3.22.4.8.4.1.4.2  2013/10/26 07:42:21  ncshivakumar
 * LOG: RFC 6733 changes
 * LOG:
 * LOG: Revision 3.22.4.8.4.1.4.1  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 3.22.4.8.4.1  2013/02/12 05:40:19  vsarath
 * LOG: Changes for TLS enable/disable
 * LOG:
 * LOG: Revision 3.22.4.8  2012/12/15 06:01:39  vsarath
 * LOG: Provided option for own Certificate path
 * LOG:
 * LOG: Revision 3.22.4.7  2012/12/03 08:40:52  ncshivakumar
 * LOG: Changes done for adding static routing table
 * LOG:
 * LOG: Revision 3.22.4.6  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.22.4.1.16.2  2012/11/20 10:28:35  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.22.4.1  2012/09/06 11:30:45  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 * LOG:
 * LOG: Revision 3.22.6.4  2012/08/29 11:47:15  cashok
 * LOG: Added plugin path in configuration
 * LOG:
 * LOG: Revision 3.22.6.3  2012/08/23 11:32:29  jvikas
 * LOG: 1. Reading dictId from Peer Table Configuration
 * LOG: 2. Calling BaseGenericCmd Destructor in DiaMsgFlow Destructor
 * LOG: 3. Changed DictId ITS_UINT
 * LOG: 4. Added HandleTransConfig
 * LOG:
 * LOG: Revision 3.22.6.2  2012/08/22 13:29:08  cashok
 * LOG: Added Dictionary Id to xml configuration
 * LOG:
 * LOG: Revision 3.22.6.1  2012/08/22 12:53:43  jvikas
 * LOG: Fixed Linking Errors and Included XML Config for Transformation.
 * LOG:
 * LOG: Revision 3.22  2011/04/26 06:11:54  nvijikumar
 * LOG: Introduced XML config parameter to disable stack initiated STR while
 * LOG: handling ASA
 * LOG:
 * LOG: Revision 3.21  2010/11/03 12:50:40  vkumara
 * LOG: DSCP Support for IPV6
 * LOG:
 * LOG: Revision 3.20  2010/08/27 12:29:23  nvijikumar
 * LOG: DSCP value support IP Header (Vasanth)
 * LOG:
 * LOG: Revision 3.19  2010/07/07 08:25:29  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 3.18  2009/07/13 06:09:23  rajeshak
 * LOG: Reverting back session table changes.
 * LOG:
 * LOG: Revision 3.17  2009/06/29 14:49:07  rajeshak
 * LOG: Changes done for performance enhancement (splitting the session table).
 * LOG:
 * LOG: Revision 3.16  2009/04/13 13:41:36  rajeshak
 * LOG: Peer Discovery changes.
 * LOG:
 * LOG: Revision 3.15  2009/04/10 06:23:07  sureshj
 * LOG: enableHMI defined for xml configuration of HMI option.
 * LOG:
 * LOG: Revision 3.14  2009/03/03 06:50:33  chandrashekharbs
 * LOG: Changes for IPV6 support
 * LOG:
 * LOG: Revision 3.13  2009/02/04 05:46:53  nvijikumar
 * LOG: Changes to make Initiate Peer connections as configurable
 * LOG:
 * LOG: Revision 3.12  2009/02/03 10:15:56  ssaxena
 * LOG: Modifications done for Redirect Agent functionality.
 * LOG:
 * LOG: Revision 3.11  2009/02/02 06:49:23  rajeshak
 * LOG: Parsing sctp socket configuration parameters
 * LOG:
 * LOG: Revision 3.10  2008/12/12 05:38:20  sureshj
 * LOG: Support for Stack statistics
 * LOG:
 * LOG: Revision 3.9  2008/11/19 05:24:44  nvijikumar
 * LOG: IssueID:None
 * LOG: FeatureID:None
 * LOG: Description:Made Peer IP Check as configurable option
 * LOG:
 * LOG: Revision 3.8  2008/11/13 08:49:11  nvijikumar
 * LOG: IssueID:None
 * LOG: FeatureID:None
 * LOG: Description:External IP configuration Support
 * LOG:
 * LOG: Revision 3.7  2008/11/06 07:52:17  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Incorporating Code review Comments renaming StackTunning
 * LOG:              with QueueMgmt
 * LOG:
 * LOG: Revision 3.6  2008/10/31 05:38:31  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID: none
 * LOG: Description: 1. Introducing additional TQs and Threads for better
 * LOG:                 Performance on PP50 and initial stack tunning
 * LOG:              2. Unwanted code cleanup
 * LOG:
 * LOG: Revision 3.5  2008/08/25 05:52:12  ssaxena
 * LOG: 1. Failover / Failback indications to application
 * LOG: 2. Failback is XML configurable option
 * LOG:
 * LOG: Revision 3.4  2008/06/13 11:18:47  hbhatnagar
 * LOG: Made changes for the TLS implementation and also related xml parsing.
 * LOG:
 * LOG: Revision 3.3  2008/04/07 18:44:35  hbhatnagar
 * LOG: Added new define for relay AppId to remove the magic number.
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:16:17  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.11  2007/02/19 15:26:59  nvijikumar
 * LOG: Control hex dump print from XML configuration.
 * LOG:
 * LOG: Revision 2.10  2006/12/29 06:54:59  nanaparthi
 * LOG: Added log to these files, forgot it in the previous commit
 * LOG:
 * LOG: Revision 2.9  2006/12/29 06:42:27  nanaparthi
 * LOG: SCTP Multihoming related changes (baseline code base)
 * LOG:
 * LOG: Revision 2.8  2006/12/21 15:28:10  tpanda
 * LOG: AddOriginStateId option is added to check if OriginStateId be added to cmd
 * LOG:
 * LOG: Revision 2.7  2006/12/12 15:04:51  nvijikumar
 * LOG: Rename XML variable name to peerNotificationsToApp from peerMsgToApp.
 * LOG:
 * LOG: Revision 2.6  2006/12/11 14:28:43  nvijikumar
 * LOG: Send Peer based msgs to application, if peerMsgToApp flag is set in the XML.
 * LOG:
 * LOG: Revision 2.5  2006/12/10 13:43:48  tpanda
 * LOG: Redundancy Bug Fixes and enhancements--Transport Order Fix
 * LOG:
 * LOG: Revision 2.4  2006/11/29 11:55:31  tpanda
 * LOG: Redundancy related enhancements and fixes for few bugs raised for redundancy
 * LOG:
 * LOG: Revision 2.3  2006/11/28 13:59:05  yranade
 * LOG: Updates to set productName from xml configuration.
 * LOG:
 * LOG: Revision 2.2  2006/11/22 10:51:46  nvijikumar
 * LOG: Baseline PendingQ (Failover) changes.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 ****************************************************************************/

#ifndef DIA_PARSER_H_
#define DIA_PARSER_H_

#include <expat.h>

#define DIA_STRING                       "ITS-Diameter"
#define DIA_VER_STRING                   "version"
#define DIA_DICT_FILE_STRING             "dictionaryFile"
#define DIA_PRODUCT_NAME_STRING          "productName" 
#define DIA_DEFAULT_ROUTING_STRING       "enableDefaultRouting" 
#define DIA_PEER_MSG_TO_APP_STRING       "peerNotificationsToApp" 
#define DIA_ADD_ORIG_STATE_ID_STRING     "addOriginStateIdOpt" 
#define DIA_ENABLE_HEXDUMP_STRING        "enableHexDump"
#define DIA_ENABLE_HMI_STRING            "enableHMI"
#define DIA_ENABLE_PEER_IPCHECK_STRING   "enablePeerIpCheck"
#define DIA_ENABLE_STACK_STATS_STRING    "enableStatistics"
#define DIA_INITIATE_CONNS_STRING        "initiateConnsOpt"
#define DIA_RED_APP_PROCESSING_STRING    "redirectAppProcessing"
#define DIA_ENABLE_LOCAL_CACHING_STRING  "enableLocalCaching"
#define DIA_ENABLE_IPV6                  "enableipv6"
#define DIA_LOCAL_IPV6_DSCP_VAL          "localIpv6DscpValue"
#define DIA_ENABLE_PEER_DISCOVERY        "enablePeerDiscovery"
#define DIA_DISCOVERY_INTERVAL           "peerDiscoveryInterval"
#define DIA_DIS_STACK_INITIATED_STR      "disableStackInitiatedSTR"
#define DIA_ENABLE_SNAPTR_SUPPORT        "enableSnaptrSupport"
#define DIA_INTER_WORKING_MODE_STRING    "interWorkingMode"

#define DIA_NAME_STRING                  "name"
#define DIA_VALUE_STRING                 "value"

#define DIA_LOCAL_STRING                 "LocalConfig"
#define DIA_INSECURITY_ID_STRING         "InbandSecurityId"
#define DIA_VENDOR_ID_STRING             "VendorId"
#define DIA_SUPP_VENDOR_ID_STRING        "SupportedVendorId"
#define DIA_AUTH_APP_ID_STRING           "AuthAppId"
#define DIA_ACCT_APP_ID_STRING           "AccountingAppId"

#define DIA_VENDOR_SPEC_APP_ID_STRING    "VendorSpecificAppId"

#define DIA_HOST_INFO_STRING             "LocalHost"
#define DIA_SERV_HOST_NAME_STRING        "serverHostName"
#define DIA_MATE_HOST_NAME_STRING        "mateHostName"
#define DIA_REALM_NAME_STRING            "realmName"
#define DIA_TRANS_STRING                 "Transport"
#define DIA_TRANS_TYPE_STRING            "type"
#define DIA_SERV_IP_STRING               "serverIpAddr"
#define DIA_PRIVATE_SERV_IP_STRING       "privateServerIpAddr"
#define DIA_PUBLIC_SERV_IP_STRING        "publicServerIpAddr"
#define DIA_PORT_INFO_STRING             "port"
#define DIA_SECURE_PORT_INFO_STRING      "securePort"
#define DIA_DICTIONARY_ID_STRING         "DictionaryId"
#define DIA_TRANS_PLUGIN_PATH_STRING     "PluginPath"

#define DIA_TRANSFORM_PLUGINS            "TransformPlugins"
#define DIA_PLUGIN                       "Plugin"
#define DIA_PLUGIN_NAME                  "name"
#define DIA_DICT_1                       "dict1"
#define DIA_DICT_2                       "dict2"
#define DIA_CONFIG						 "config"

/**
 * Added defines for the security
 */
#define DIA_TLS_ENABLED_STRING           "tlsEnabled"
#define DIA_DSCP_ENABLED_STRING          "dscpEnabled"

#define DIA_OTHERHOME_STRING             "OtherHome"        // SCTP MultiHoming
#define MAX_NO_IPS                        8


#define DIA_PORT_TYPE_TCP_STRING         "TCP"
#define DIA_PORT_TYPE_SCTP_STRING        "SCTP"

/**
 * For socket config
 */
#define DIA_SOCK_CONFIG_DATA_STRING      "ConfigData"
#define DIA_MAX_CONN_ATTEMPTS_STRING     "maxAttempts"
#define DIA_MAX_IN_STREAMS_STRING        "maxInStreams"
#define DIA_MAX_OUT_STREAMS_STRING       "numOutStreams"
#define DIA_COOKIE_LIFE_TIME_STRING      "cookieLife"
#define DIA_HEART_BEAT_ON_STRING         "hbOn"
#define DIA_HEART_BEAT_TIMEOUT_STRING    "hbTimeout"
#define DIA_INIT_TIMEOUT_STRING          "initTimeout"
#define DIA_PMTU_TIMEOUT_STRING          "pmtuTimeout"
#define DIA_RECV_TIMEOUT_STRING          "recvTimeout"
#define DIA_SEND_TIMEOUT_STRING          "sendTimeout"
#define DIA_SHUTDOWN_TIMEOUT_STRING      "shutdownTimeout"
#define DIA_ACK_DELAY_STRING             "sackDelay"
#define DIA_ASOC_FAILURE_RETRY_STRING    "asocMaxAttempt"
#define DIA_RTO_MAX_STRING               "rtoMax"
#define DIA_RTO_MIN_STRING               "rtoMin"
#define DIA_RTO_INITIAL_STRING           "rtoInitial"
#define DIA_SEND_BUFFER_SIZE_STRING      "sendBufSize"
#define DIA_RECV_BUFFER_SIZE_STRING      "recvBufSize"
#define DIA_PATH_FAILURE_RETRY_STRING    "pathmaxrxt"


#define DIA_SESSION_CFG_STRING           "SessionConfig"
#define DIA_SESSION_AUTH_STRING          "AuthSession"
#define DIA_SESSION_ACCT_STRING          "AcctSession"
#define DIA_SESSION_STATE_STRING         "state"
#define DIA_SESSION_TIMEOUT_STRING       "timeout"
#define DIA_SESSION_LIFETIME_STRING      "lifetime"
#define DIA_SESSION_GRACE_STRING         "gracePeriod"
#define DIA_SESSION_ABORT_RETRY_STRING   "retryAbort" 
#define DIA_SESSION_INTERIM_INTVL_STRING "interimInterval"
#define DIA_SESSION_REALTIME_STRING      "realTime"

#define DIA_TRACE_SUBSYSTEM_STRING        "TraceSubsystem"
#define DIA_CRITICAL_STRING               "Critical"
#define DIA_ERROR_STRING                  "Error"
#define DIA_WARNING_STRING                "Warning"
#define DIA_DEBUG_STRING                  "Debug"

#define DIA_TRACE_OUTPUT_STRING           "output"

#define DIA_QUEUE_MGMT_STRING              "QueueMgmt"
#define DIA_NUM_DOWNSTREAM_THREADS        "downStreamThreadCount"
#define DIA_NUM_UPSTREAM_THREADS          "upStreamThreadCount"
#define DIA_NUM_OF_MSG_ROUTER_THREADS     "msgRouterThreadCount"

#define DIA_TIMER_STRING                  "Timer"
#define DIA_TIMER_EXPIRY_STRING           "Expiry"
#define DIA_TIMER_RETRY_STRING            "Tc"
#define DIA_TIMER_WATCHDOG_STRING         "Watchdog"
#define DIA_TIMER_BUSY_RECONNECT_STRING   "BusyReconnectTimer"
#define DIA_TIMER_DO_NOT_WANT_TO_TALK_TO_YOU_STRING         "DoNotwantToTalkToYouTimer"
#define DIA_DISCONNECT_CAUSE_SUPPORT_ENABLE "DisconnectCauseSupportEnable"
#define DIA_RETRANS_INTVL_STRING          "RetransmitInterval"
#define DIA_RETRANS_COUNT_STRING          "RetransmitCount"

#define DIA_PEER_CONFIG_STRING            "PeerConfig"
#define DIA_REALM_CONFIG_STRING           "RealmConfig"

#define DIA_PEER_STRING                   "Peer"

#define DIA_ROUTE_STRING                  "Route"
#define DIA_DEFAULT_STRING                "default"
#define DIA_REALM_NAME_STRING             "realmName"
#define DIA_LOCAL_ACTION_STRING           "localAction"
#define DIA_PROXY_INFO_AVP_EN_STRING      "proxyInfoAvpEnabled"
#define DIA_RED_HOST_USAGE_AVP_STRING     "redirectHostUsage"
#define DIA_RED_MAX_CACHE_TIME_AVP_STRING "redirectMaxCacheTime"

#define DIA_LA_LOCAL_STRING               "local"
#define DIA_LA_RELAY_STRING               "relay"
#define DIA_LA_PROXY_STRING               "proxy"
#define DIA_LA_REDIRECT_STRING            "redirect"

#define DIA_DESTINATION_STRING            "Destination"
#define DIA_PEER_NAME_STRING              "peerName"
#define DIA_APPLICATION_ID_STRING         "applicationId"
#define DIA_DEST_VENDOR_ID_STRING         "vendorId"
#define DIA_PRIORITY_STRING               "priority"

#define DIA_FAILOVER_STRING               "Failover"
#define DIA_ALT_PEER_STRING               "AlternatePeer"
#define DIA_ENABLE_STRING                 "enable"
#define DIA_ENABLE_FAILBACK_STRING        "enableFailback"
#define DIA_YES_STRING                    "yes"
#define DIA_ISMATE_STRING                 "isMate"
#define DIA_IS_REDIRECT_AGENT             "isRedirectAgent"
#define DIA_DSCP_STRING                   "Dscp"

/**
 * Adding a define for relay AppId
 */
#define DIA_RELAY_APP_ID_STRING           "0xffffffff"


/**
 * Adding defines for TLS security
 */
#define DIA_ENABLE_TLS_STRING                    "TlsEnable"
#define DIA_SECURITY_STRING                      "Tls-Security"

#define DIA_TLS_TYPE_STRING                      "TlsType"
#define DIA_TLS_TRACE_LEVEL_STRING               "TlsTraceLevel"
#define DIA_TLS_TYPE_GNU_STRING                  "GNUTLS"
#define DIA_TLS_TYPE_OPENSSL_STRING              "OPENSSL"

#define DIA_IDENTITY_VERIFICATION_STRING         "TlsIdentityVerification"

#define DIA_CIPHER_SUITE_STRING                  "TlsCipherSuite"
#define DIA_CIPHER_RSA_RC4_MD5_STRING            "RSA-RC4128-MD5"
#define DIA_CIPHER_RSA_RC4_SHA_STRING            "RSA-RC4128-SHA"
#define DIA_CIPHER_RSA_3DESEDECBC_SHA_STRING     "RSA-TDES_EDE_CBC-SHA"
#define DIA_CIPHER_RSA_RC4_SHA_STRING            "RSA-RC4128-SHA"
#define DIA_CIPHER_NULL_MD5_STRING               "NULL-MD5"
#define DIA_CIPHER_NULL_SHA_STRING               "NULL-SHA"
#define DIA_CIPHER_RC4_MD5_STRING                "RC4-MD5"
#define DIA_CIPHER_RC4_SHA_STRING                "RC4-SHA"
#define DIA_CIPHER_DES_CBC_SHA_STRING            "DES-CBC-SHA"
#define DIA_CIPHER_DES_CBC3_SHA_STRING           "DES-CBC3-SHA"
#define DIA_CIPHER_AES_128_SHA_STRING            "AES128-SHA"
#define DIA_CIPHER_AES_256_SHA_STRING            "AES256-SHA"

#define DIA_CIPHER_RFC_3588_ALL_STRING           "DIAMETER-ALL"

#define DIA_CERTIFICATE_TYPE_STRING              "TlsCertificateType"
#define DIA_CERTIFICATE_X_509_STRING             "X.509"

#define DIA_CL_CERTIFICATE_FILE_STRING           "TlsClientCertificateFile"
#define DIA_CL_KEY_FILE_STRING                   "TlsClientKeyFile"
#define DIA_SER_CERTIFICATE_FILE_STRING          "TlsServerCertificateFile"
#define DIA_SER_KEY_FILE_STRING                  "TlsServerKeyFile"
#define DIA_TLS_CA_PATH                          "TlsCAPath"
#define DIA_TLS_OWN_CA_PATH                      "TlsOwnCertPath"

#define DIA_TRUSTED_CAS                          "TrustedCAs"
#define DIA_CA                                   "CA"
#define DIA_TRUST_FILE                           "TrustFile"
#define DIA_CERT_TYPE                            "CertType"
#define DIA_CRL_FILE                             "CRLFile"
#define DIA_PEM                                  "PEM"
#define DIA_DER                                  "DER"

#define DIA_TLS_CRL_PATH                         "TlsCRLPath"
#define DIA_PATH                                 "path"
#define DIA_CRL_VERIFICATION                     "CrlVerification"
#define DIA_ENABLE                               "enable"

#define DIA_TLS_CIPHER_SUITS                     "TlsCipherSuites"
#define DIA_CIPHER_SUIT                          "CipherSuite"

#define DIA_TRANSFORMATION                       "Transformation"
#define DIA_TRANSFORMATION_VALUE                 "ITS_DIA_TRANSFORMATION"

#define DIA_STATIC_ROUTING_TABLE                 "StaticRoutingTable"
#define DIA_STATIC_ROUTE                         "StaticRoute"
#define DIA_DESTINATION_HOST                     "destionatinHost"
#define DIA_DESTINATION_REALM                    "destinationRealm"
#define DIA_PEER                                 "peer"
#define DIA_APPLICATION_ID                       "ApplicationId"
#define DIA_PRIORITY                             "Priority"
#define DIA_IS_PREDECTIVE_LOOP_AVID_ENABLE       "IsPredictiveLoopAvoidanceEnable"
#define DIA_PEER_DISCONNECT_CAUSE_SUPPORT        "PeerDisconnectCauseSupport"
#define DIA_TCP_SOCK_CONFIG_DATA_STRING		     "TcpConfigData"
#define DIA_TCP_CONNECT_TIMEOUT_STRING		     "connectTimeout"
#endif

