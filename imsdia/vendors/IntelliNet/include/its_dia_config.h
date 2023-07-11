/******************************-*-HPP-*-*************************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 *
 *  LOG: $Log: its_dia_config.h,v $
 *  LOG: Revision 3.34.4.10.4.4.2.1.2.4.4.1.2.2.4.5  2020/02/14 11:36:11  jkchaitanya
 *  LOG: TCP Timeout fix ported from DRE
 *  LOG:
 *  LOG: Revision 3.34.4.10.4.4.2.1.2.4.4.1.2.2.4.4  2015/02/17 06:22:44  jkchaitanya
 *  LOG: changes for peer down crash ported from stack branch for bugs 5507, 6067
 *  LOG:
 *  LOG: Revision 3.34.4.10.4.4.2.1.2.4.4.1.2.2.4.3  2014/12/17 05:19:08  jkchaitanya
 *  LOG: changes to revert back the server down crash changes
 *  LOG:
 *  LOG: Revision 3.34.4.10.4.4.2.1.2.4.4.1.2.2.4.1  2014/12/04 12:00:16  pramana
 *  LOG: Added support for allowing requests for a different hosts
 *  LOG:
 *  LOG: Revision 3.34.4.10.4.4.2.1.2.4.4.1.2.2  2014/08/26 10:27:38  pramana
 *  LOG: Compilation warning fixes in imsdia
 *  LOG:
 *  LOG: Revision 3.34.4.10.4.4.2.1.2.4.4.1.2.1  2014/07/02 06:37:11  millayaraja
 *  LOG: updated to handle answer message without mandatory field missing
 *  LOG:
 *  LOG: Revision 3.34.4.10.4.4.2.1.2.4.4.1  2014/02/12 07:13:09  millayaraja
 *  LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
 *  LOG:
 *  LOG: Revision 3.34.4.10.4.4.2.1.2.4  2013/12/13 09:34:58  vsarath
 *  LOG: Merged the session-splict changes
 *  LOG:
 *  LOG: Revision 3.34.4.10.4.4.2.1.2.2  2013/10/26 07:42:21  ncshivakumar
 *  LOG: RFC 6733 changes
 *  LOG:
 *  LOG: Revision 3.34.4.10.4.4.2.1.2.1  2013/09/10 08:36:39  ncshivakumar
 *  LOG: RFC6733 Changes
 *  LOG:
 *  LOG: Revision 3.34.4.10.4.4.2.1  2013/05/24 10:35:56  ncshivakumar
 *  LOG: Fix for bug 1580
 *  LOG:  VS: ----------------------------------------------------------------------
 *  LOG:
 *  LOG: Revision 3.34.4.10.4.4  2013/03/05 06:52:02  ncshivakumar
 *  LOG: Multihome changes
 *  LOG:
 *  LOG: Revision 3.34.4.10.4.3  2013/02/27 08:49:07  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 3.34.4.10.4.2  2013/02/21 11:17:29  ncshivakumar
 *  LOG: modified for multitransport support
 *  LOG:
 *  LOG: Revision 3.34.4.10.4.1  2013/02/12 05:40:32  vsarath
 *  LOG: Changes for TLS enable/disable
 *  LOG:
 *  LOG: Revision 3.34.4.10  2012/12/20 12:12:50  pramana
 *  LOG: Merging changes from CMGR branch
 *  LOG:
 *  LOG: Revision 3.34.4.9  2012/12/15 06:03:59  vsarath
 *  LOG: Provided option for own Certificate path
 *  LOG:
 *  LOG: Revision 3.34.4.8  2012/11/26 05:03:37  jsarvesh
 *  LOG: changes done if sctp is configured from cli and tcp from xml
 *  LOG:
 *  LOG: Revision 3.34.4.7.2.1  2012/12/12 12:12:07  rgovardhan
 *  LOG: DRE Config related and dia_mgmt changes
 *  LOG:
 *  LOG: Revision 3.34.4.7  2012/11/20 12:23:23  pramana
 *  LOG: *** empty log message ***
 *  LOG:
 *  LOG: Revision 3.34.4.1.22.2  2012/11/20 04:19:39  pramana
 *  LOG: merged from 00 branch
 *  LOG:
 *  LOG: Revision 3.34.4.5  2012/11/06 16:31:20  pramana
 *  LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
 *  LOG:
 *  LOG: Revision 3.34.4.1.20.3  2012/11/06 10:06:27  cprem
 *  LOG: Merged from 00 branch for 0212-06 release
 *  LOG:
 *  LOG: Revision 3.34.4.1.20.2  2012/11/06 08:52:38  vsarath
 *  LOG: Added for TLS enhancements
 *  LOG:
 *  LOG: Revision 3.34.4.1.20.1  2012/11/05 03:39:38  vsarath
 *  LOG: Added for TLS enhancements
 *  LOG:
 *  LOG: Revision 3.34.4.4  2012/10/26 15:07:12  cprem
 *  LOG: Support for reading plugin info from Configuration file.
 *  LOG:
 *  LOG: Revision 3.34.4.3  2012/10/26 13:33:38  pramana
 *  LOG: Changes done for config fetch to work
 *  LOG: Revision 3.34.4.2  2012/10/23 08:11:16  cprem
 *  LOG: Support for reading transform plugin configuration.
 *  LOG:
 *  LOG: Revision 3.34.4.1  2012/09/06 11:30:45  jvikas
 *  LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 *  LOG:
 *  LOG: Revision 3.34.6.2  2012/08/29 11:47:15  cashok
 *  LOG: Added plugin path in configuration
 *  LOG:
 *  LOG: Revision 3.34.6.1  2012/08/22 12:53:43  jvikas
 *  LOG: Fixed Linking Errors and Included XML Config for Transformation.
 *  LOG:
 *  LOG: Revision 3.34  2011/04/26 06:11:54  nvijikumar
 *  LOG: Introduced XML config parameter to disable stack initiated STR while
 *  LOG: handling ASA
 *  LOG:
 *  LOG: Revision 3.33  2010/11/03 12:50:40  vkumara
 *  LOG: DSCP Support for IPV6
 *  LOG:
 *  LOG: Revision 3.32  2010/08/25 06:09:45  nvijikumar
 *  LOG: Max number of peers increased (Vasanth)
 *  LOG:
 *  LOG: Revision 3.31  2009/09/30 12:21:16  sureshj
 *  LOG: Help Desk ticket 2224.Issue in responding HSS initiated request's.
 *  LOG:
 *  LOG: Revision 3.30  2009/08/24 11:44:47  rajeshak
 *  LOG: Fix for Issue 2317(ACTIVE COLD REDUNDANCY::IDC not able to send
 *  LOG: messages to ACTIVE server)
 *  LOG:
 *  LOG: Revision 3.29  2009/07/13 06:09:23  rajeshak
 *  LOG: Reverting back session table changes.
 *  LOG:
 *  LOG: Revision 3.28  2009/06/29 14:49:07  rajeshak
 *  LOG: Changes done for performance enhancement (splitting the session table).
 *  LOG:
 *  LOG: Revision 3.27  2009/04/13 13:41:36  rajeshak
 *  LOG: Peer Discovery changes.
 *  LOG:
 *  LOG: Revision 3.26  2009/04/10 06:21:41  sureshj
 *  LOG: setHMIEnabled, setHMIDisabled and IsHMIEnabled APIs added to
 *  LOG: set/check enableHMI flag using MML commands.
 *  LOG:
 *  LOG: Revision 3.25  2009/03/19 11:58:20  nvijikumar
 *  LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 *  LOG: call overhead and ITSDiaConfig::GetITSDiaConfig() func was called max time
 *  LOG:
 *  LOG: Revision 3.24  2009/03/18 12:52:48  rajeshak
 *  LOG: Added functions for new MML command and API.
 *  LOG:
 *  LOG: Revision 3.23  2009/03/11 05:23:46  sureshj
 *  LOG: Issue Id:None
 *  LOG: Feature Id: dynamic configuration
 *  LOG: Description: Dynamic configuration for LocalHost info.New APIs added.
 *  LOG:
 *  LOG: Revision 3.22  2009/03/03 06:51:16  chandrashekharbs
 *  LOG: Changes for IPV6 support
 *  LOG:
 *  LOG: Revision 3.21  2009/02/27 06:13:51  rajeshak
 *  LOG: Printing SCTP params configured in XML.
 *  LOG:
 *  LOG: Revision 3.20  2009/02/12 04:21:48  nvijikumar
 *  LOG: Implementation of Callback for message processing at ID
 *  LOG:
 *  LOG: Revision 3.19  2009/02/06 06:45:07  chandrashekharbs
 *  LOG: GetProdName added in ITSDiaConfig as a part fix to issue 1475
 *  LOG:
 *  LOG: Revision 3.18  2009/02/05 05:44:54  rajeshak
 *  LOG: Returning proper values
 *  LOG:
 *  LOG: Revision 3.17  2009/02/04 05:46:53  nvijikumar
 *  LOG: Changes to make Initiate Peer connections as configurable
 *  LOG:
 *  LOG: Revision 3.16  2009/02/03 10:15:56  ssaxena
 *  LOG: Modifications done for Redirect Agent functionality.
 *  LOG:
 *  LOG: Revision 3.15  2009/02/02 06:53:18  rajeshak
 *  LOG: Storing sctp sockt config struct in ITSDiaConfig
 *  LOG:
 *  LOG: Revision 3.14  2009/01/03 06:44:58  nvijikumar
 *  LOG: Introducing new define MAX_PEER_CONNS
 *  LOG:
 *  LOG: Revision 3.13  2008/12/12 07:54:26  sureshj
 *  LOG: Initial draft for Stack Statistics support (Suresh)
 *  LOG:
 *  LOG: Revision 3.12  2008/12/11 13:46:35  sureshj
 *  LOG: Introduced new flag for statistic support
 *  LOG:
 *  LOG: Revision 3.11  2008/12/10 11:30:37  nvijikumar
 *  LOG: Having new flag to check Scenario type Distributed / Static
 *  LOG:
 *  LOG: Revision 3.10  2008/11/26 12:04:30  nvijikumar
 *  LOG: Local IP binding for Client Sockets
 *  LOG:
 *  LOG: Revision 3.9  2008/11/22 10:57:52  ssaxena
 *  LOG: Fix for IssueId : 1292
 *  LOG: getNodeState and switchOver MML commands are not working for Redundancy
 *  LOG:
 *  LOG: Revision 3.8  2008/11/19 05:22:30  nvijikumar
 *  LOG: IssueID:None
 *  LOG: FeatureID:None
 *  LOG: Description:Made Peer IP Check as configurable option
 *  LOG:
 *  LOG: Revision 3.7  2008/11/13 08:47:41  nvijikumar
 *  LOG: IssueID:None
 *  LOG: FeatureID:None
 *  LOG: Description:External IP configuration Support
 *  LOG:
 *  LOG: Revision 3.6  2008/11/06 07:52:17  nvijikumar
 *  LOG: IssueID: none
 *  LOG: FeatureID: none
 *  LOG: Description: Incorporating Code review Comments renaming StackTunning
 *  LOG:              with QueueMgmt
 *  LOG:
 *  LOG: Revision 3.5  2008/10/31 05:38:31  nvijikumar
 *  LOG: IssueID:1189
 *  LOG: FeatureID: none
 *  LOG: Description: 1. Introducing additional TQs and Threads for better
 *  LOG:                 Performance on PP50 and initial stack tunning
 *  LOG:              2. Unwanted code cleanup
 *  LOG:
 *  LOG: Revision 3.4  2008/07/09 14:05:34  vnarang
 *  LOG: X509 is changed toITS_X509 due to name Conflict with OPEN SSL
 *  LOG:
 *  LOG: Revision 3.3  2008/06/13 11:18:47  hbhatnagar
 *  LOG: Made changes for the TLS implementation and also related xml parsing.
 *  LOG:
 *  LOG: Revision 3.2  2008/04/01 16:03:40  hbhatnagar
 *  LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.20  2007/02/26 04:48:14  nvijikumar
 *  LOG: Provided API to disable the hexdump.
 *  LOG:
 *  LOG: Revision 2.19  2007/02/19 15:26:59  nvijikumar
 *  LOG: Control hex dump print from XML configuration.
 *  LOG:
 *  LOG: Revision 2.18  2007/01/29 14:39:20  nanaparthi
 *  LOG: Change the value of ITS_DIA_LOCAL back to 0
 *  LOG:
 *  LOG: Revision 2.17  2007/01/24 15:10:04  nanaparthi
 *  LOG: Fix for Bug id 5216
 *  LOG:
 *  LOG: Revision 2.16  2006/12/29 06:54:59  nanaparthi
 *  LOG: Added log to these files, forgot it in the previous commit
 *  LOG:
 *  LOG: Revision 2.15  2006/12/29 06:42:27  nanaparthi
 *  LOG: SCTP Multihoming related changes (baseline code base)
 *  LOG:
 *  LOG: Revision 2.14  2006/12/21 15:28:10  tpanda
 *  LOG: AddOriginStateId option is added to check if OriginStateId be added to cmd
 *  LOG:
 *  LOG: Revision 2.13  2006/12/20 15:53:05  nvijikumar
 *  LOG: Elimination of multiple ITS_FindFeature function calls(DCCA & Redundancy).
 *  LOG:
 *  LOG: Revision 2.12  2006/12/11 14:28:43  nvijikumar
 *  LOG: Send Peer based msgs to application, if peerMsgToApp flag is set in the XML.
 *  LOG:
 *  LOG: Revision 2.11  2006/12/10 13:43:48  tpanda
 *  LOG: Redundancy Bug Fixes and enhancements--Transport Order Fix
 *  LOG:
 *  LOG: Revision 2.10  2006/11/29 11:55:31  tpanda
 *  LOG: Redundancy related enhancements and fixes for few bugs raised for redundancy
 *  LOG:
 *  LOG: Revision 2.9  2006/11/25 04:00:12  tpanda
 *  LOG: Changes for Msg based redundancy
 *  LOG:
 *  LOG: Revision 2.8  2006/11/07 11:18:38  kamakshilk
 *  LOG: codec library separated from stack library
 *  LOG:
 *  LOG: Revision 2.7  2006/10/27 09:40:24  yranade
 *  LOG: Update MaxListSize to 64.
 *  LOG:
 *  LOG: Revision 2.6  2006/10/24 08:59:42  tpanda
 *  LOG: Dictionary file related changes
 *  LOG:
 *  LOG: Revision 2.5  2006/10/16 06:18:33  yranade
 *  LOG: Generate OriginStateId on Initialization
 *  LOG:
 *  LOG: Revision 2.4  2006/10/05 14:09:54  tpanda
 *  LOG: Dictionary parsing support for codec
 *  LOG:
 *  LOG: Revision 2.3  2006/10/05 13:00:22  yranade
 *  LOG: Getting there.
 *  LOG:
 *  LOG: Revision 2.2  2006/09/14 09:33:28  nvijikumar
 *  LOG: Added TO_TEXT macros for enums.
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 *  LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: its_dia_config.h,v 3.34.4.10.4.4.2.1.2.4.4.1.2.2.4.5 2020/02/14 11:36:11 jkchaitanya Exp $"

#ifndef _ITS_DIA_CONFIGURATION_H_
#define _ITS_DIA_CONFIGURATION_H_

#include <string>
#include <its++.h>
#include <its_sockets.h>
#include <its_hmi.h>

#include <dia_cmn.h>
#include <dia_parse.h>  
#ifdef TLS_ENABLED
#include "CAu.h"  
#include "CRL.h"  
#endif

/* Callback Func for message processing at IDS */
typedef void (*IDSMsgProcessFunc)(ITS_EVENT *evt);
extern IDSMsgProcessFunc IDSMsgProcessCallBack;
extern IDSMsgProcessFunc IDSRedundancyCallBack;

/* Callback Func for Command processing at IDS */
typedef int (*IDSCmdProcessFunc)(int, void*, void*);
extern IDSCmdProcessFunc IDSCmdProcessCallBack;

extern bool isStackStatsEnabled;

/*max 64 peers can be added, 4 slots for each peer reserved
 *1st slot for connecting connection to peer
 *2nd slot for accepting connection from peer
 *3rd and 4th being reserved, can be used for other transports
 */
#define MAX_PEER_CONNS           400 
#define MAX_LOCAL_TRANSPORTS     (MAX_PEER_CONNS*4)

#define MAX_LIST_SIZE            64 
#define MAX_TRANS_PER_LIST        4
#define MAX_LOCAL_HOSTS           8
#define MAX_MSG_LEN              3048

#define DIA_MSG_CE   257
#define DIA_MSG_RA   258
#define DIA_MSG_AC   271
#define DIA_MSG_AS   274
#define DIA_MSG_ST   275
#define DIA_MSG_DW   280
#define DIA_MSG_DP   282
#define DIA_MSG_CUR  328 

#define DIA_RELAY_APP_ID   (0xffffffff)

#define ITS_DIA_VERSION_NUMBER       1
#define ITS_DIA_PRODUCT_NAME         "ITS-Diameter"
#define PEER_DISCOVERY_INTERVAL      60

//Warning Fix - deprecated conversion from string constant to "char*"
#define MAX_HB_STR_LENGTH    5

/**
 * Defines for setting the tracelevels in the GnuTLs library
 */
#define DIA_TLS_LOG_MIN    0
#define DIA_TLS_LOG_MAX    10

#define DIA_SESSION_TYPE_TO_TEXT(x) \
    ((x==DIA_AUTHORIZATION)           ? "DIA_AUTHORIZATION"               : \
    ((x==DIA_ACCOUNTING)              ? "DIA_ACCOUNTING"                  : \
    "INVALID"))

#define DIA_SESSION_SUB_TYPE_TO_TEXT(x) \
    ((x==DIA_SESSION_STATEFUL)         ? "DIA_SESSION_STATEFUL"           : \
    ((x==DIA_SESSION_STATELESS)        ? "DIA_SESSION_STATELESS"          : \
    "INVALID"))

#define DIA_TRANS_TYPE_TO_TEXT(x) \
    ((x==ITS_DIA_T_TCP)                 ? "ITS_DIA_T_TCP"                 : \
    ((x==ITS_DIA_T_SCTP)                ? "ITS_DIA_T_SCTP"                : \
    ((x==ITS_DIA_T_TLS)                 ? "ITS_DIA_T_TLS"                 : \
    "INVALID")))

#define ITS_DIA_SOCK_TRANS_TYPE_TO_TEXT(x) \
    ((x==ITS_DIA_SERVER_SOCK_TRANS)     ? "ITS_DIA_SERVER_SOCK_TRANS"     : \
    ((x==ITS_DIA_SERVER_DYN_SOCK_TRANS) ? "ITS_DIA_SERVER_DYN_SOCK_TRANS" : \
    ((x==ITS_DIA_CLIENT_SOCK_TRANS)     ? "ITS_DIA_CLIENT_SOCK_TRANS"     : \
    ((x==ITS_DIA_SCTP_SERVER_SOCK_TRANS)? "ITS_DIA_SCTP_SERVER_SOCK_TRANS": \
    ((x==ITS_DIA_SCTP_SERVER_DYN_SOCK_TRANS)? "ITS_DIA_SCTP_SERVER_DYN_SOCK_TRANS" : \
    ((x==ITS_DIA_SCTP_CLIENT_SOCK_TRANS) ? "ITS_DIA_SCTP_CLIENT_SOCK_TRANS": \
    "INVALID"))))))

#define DIA_INBAND_SECURITY_TYPE_TO_TEXT(x) \
    ((x==ITS_DIA_NO_SECURITY)           ? "ITS_DIA_NO_SECURITY"           : \
    ((x==ITS_DIA_TLS)                   ? "ITS_DIA_TLS"                   : \
    "INVALID"))

#define DIA_TRANSFORMATION_TYPE_TO_TEXT(x) \
    ((x==ITS_DIA_NO_TRANSFORMATION)     ? "ITS_DIA_NO_TRANSFORMATION"     : \
    ((x==ITS_DIA_TRANSFORMATION)        ? "ITS_DIA_TRANSFORMATION"        : \
    "INVALID"))

#define DIA_ROUTE_LOCAL_ACTION_TO_TEXT(x) \
    ((x==ITS_DIA_LOCAL)                 ? "ITS_DIA_LOCAL"                 : \
    ((x==ITS_DIA_RELAY)                 ? "ITS_DIA_RELAY"                 : \
    ((x==ITS_DIA_PROXY)                 ? "ITS_DIA_PROXY"                 : \
    ((x==ITS_DIA_REDIRECT)              ? "ITS_DIA_REDIRECT"              : \
    "INVALID"))))

/**
 * prints for TLS related configuration
 */
#define DIA_TLS_TYPE_TO_TEXT(x) \
    ((x==NO_TLS)                        ? "NO-TLS"           : \
    ((x==GNUTLS)                        ? "GNUTLS"           : \
    ((x==OPENSSL)                       ? "OPENSSL"          : \
    "INVALID")))

#define DIA_CIPHER_TYPE_TO_TEXT(x) \
    ((x==TLS_NO_CIPHER_SUITE)                ? "NO-CIPHER-SUITE"          : \
    ((x==TLS_RSA_WITH_RC4_128_MD5)           ? "RSA-RC4128-MD5"           : \
    ((x==TLS_RSA_WITH_RC4_128_SHA)           ? "RSA-RC4128-SHA"           : \
    ((x==TLS_RSA_WITH_3DES_EDE_CBC_SHA)      ? "RSA-TDES_EDE_CBC-SHA"     : \
    ((x==TLS_RSA_WITH_AES_128_CBC_SHA)       ? "RSA-RC4128-SHA"           : \
    ((x==TLS_RFC_3588_ALL)                   ? "RFC_3588_ALL"             : \
    "INVALID"))))))


//Warning Fix - copy past problem resulting in warning of imcompatible type check
#define DIA_CERTIFICATE_TYPE_TO_TEXT(x) \
    ((x==NO_CERT)                        ? "NO-Certificate"           : \
    ((x==ITS_X509)                           ? "X.509"                    : \
    "INVALID"))


#define DEFAULT_TLS_OR_DTLS_PORT 5658
#define DEFAULT_TCP_OR_SCTP_PORT 3868

typedef enum
{
    DIA_AUTHORIZATION = 0,
    DIA_ACCOUNTING
}
DIA_SESSION_TYPE;

typedef DIA_SESSION_TYPE DIA_VS_APP_ID_TYPE;

typedef enum
{
    DIA_SESSION_STATEFUL=0,
    DIA_SESSION_STATELESS
}
DIA_SESSION_SUB_TYPE;

/* Transport Types */
typedef enum _its_dia_trans_type
{
    ITS_DIA_T_TCP = 0,
    ITS_DIA_T_SCTP,
    ITS_DIA_T_TLS,
    ITS_DIA_T_INAVLID
}
DIA_TRANS_TYPE;

typedef enum
{
    ITS_DIA_SERVER_SOCK_TRANS = 0,
    ITS_DIA_SERVER_DYN_SOCK_TRANS,
    ITS_DIA_CLIENT_SOCK_TRANS,
    ITS_DIA_SCTP_SERVER_SOCK_TRANS,
    ITS_DIA_SCTP_SERVER_DYN_SOCK_TRANS,
    ITS_DIA_SCTP_CLIENT_SOCK_TRANS
}
ITS_DIA_SOCK_TRANS_TYPE;

typedef enum _its_dia_inband_security_type
{
    ITS_DIA_NO_SECURITY = 0,
    ITS_DIA_TLS
}
DIA_INBAND_SECURITY_TYPE;

typedef enum _its_dia_transformation
{
    ITS_DIA_NO_TRANSFORMATION = 0,
    ITS_DIA_TRANSFORMATION
}
DIA_DTF;

/* Realm Route Local Action */
typedef enum _its_dia_route_local_action
{
    ITS_DIA_LOCAL = 0,
    ITS_DIA_RELAY,
    ITS_DIA_PROXY,
    ITS_DIA_REDIRECT
}
DIA_ROUTE_LOCAL_ACTION;

typedef struct _its_dia_app_id
{
    ITS_UINT    vendorId;
    ITS_UINT    appId;
}
DIA_APPL_IDENTIFIER;

typedef struct _its_dia_trans_info
{
    DIA_TRANS_TYPE    type;
    const char        *serverIpAddr;
    const char        *publicServerIpAddr;
    ITS_USHORT        portNo;

    const char        *multiHomeipaddrs[MAX_NO_IPS];   // SCTP MultiHoming
    ITS_USHORT        noIPs;
    ITS_USHORT        securePort;//Store the port number for supporting
                                //RFC 6733
}
DIA_TRANS_INFO;

typedef struct _its_dia_host_info
{
    const char*          servHostName;
    const char*          realmName;
    ITS_USHORT           transCnt;
    DIA_TRANS_INFO       transList[MAX_TRANS_PER_LIST];
}
DIA_HOST_INFO;

typedef struct _its_dia_host_list
{
    ITS_OCTET            count;
    DIA_HOST_INFO        arr[MAX_LOCAL_HOSTS];
}
DIA_HOST_INFO_LIST;

#define TIMER_TO_TEXT(x) \
    ((x==RETRY) ? "RETRY TIMER" : \
    ((x==EXPIRY)? "EXPIRY TIMER"  : \
    ((x==DEVICE_WATCHDOG)? "DEVICE WATCHDOG TIMER" : \
    ((x==AUTH_SESSION_TIMER)? "AUTH_SESSION_TIMER" : \
    ((x==AUTH_SESSION_LIFETIME)? "AUTH_SESSION_LIFETIME" : \
    ((x==AUTH_SESSION_GRACE_PERIOD)? "AUTH_SESSION_GRACE_PERIOD" : \
    ((x==AUTH_SESSION_RETRY_ABORT) ? "AUTH_SESSION_RETRY_ABORT" : \
    ((x==ACCT_SESSION_TIMER) ? "ACCT_SESSION_TIMER" : \
    ((x==ACCT_SESSION_INTERIM_INTERVAL) ? "ACCT_SESSION_INTERIM_INTERVAL" : \
    ((x==ACCT_SESSION_REALTIME) ? "ACCT_SESSION_REALTIME" : \
    ((x==CACHE_TIMER) ? "CACHE_TIMER" : \
    ((x==TTL_TIMER) ? "TTL_TIMER" : \
     ((x==TRANSPORT_DEL_DELAY_TIMER) ? "TRANSPORT_DEL_DELAY_TIMER" : \
    ((x==SOCK_FLUSH_TIMER) ? "SOCK_FLUSH_TIMER" : \
    "INVALID"))))))))))))))

typedef enum _its_dia_timer_type
{
    RETRY = 0,
    EXPIRY,
    DEVICE_WATCHDOG,
    AUTH_SESSION_TIMER,
    AUTH_SESSION_LIFETIME,
    AUTH_SESSION_GRACE_PERIOD,
    AUTH_SESSION_RETRY_ABORT,
    ACCT_SESSION_TIMER,
    ACCT_SESSION_INTERIM_INTERVAL,
    ACCT_SESSION_REALTIME,
    CACHE_TIMER,
    TTL_TIMER,
    SOCK_FLUSH_TIMER,
    RETRMISSION_TIMER,
    TRANSPORT_DEL_DELAY_TIMER
}
DIA_TIMER_TYPE;


/**
 * TLS Types
 */
typedef enum _TlsType
{
    NO_TLS = 0, 
    GNUTLS,
    OPENSSL
}
DIA_TLS_TYPE;

/**
 * cipher suite supported by RFC3588 
 */
typedef enum _cipherSuite
{
    TLS_NO_CIPHER_SUITE = 0, 
    TLS_RSA_WITH_RC4_128_MD5,
    TLS_RSA_WITH_RC4_128_SHA,
    TLS_RSA_WITH_3DES_EDE_CBC_SHA,
    TLS_RSA_WITH_AES_128_CBC_SHA,
    TLS_RSA_WITH_NULL_MD5,
    TLS_RSA_WITH_NULL_SHA,
    TLS_RSA_WITH_DES_CBC_SHA,
    TLS_RSA_WITH_AES_256_CBC_SHA,
    TLS_RFC_3588_ALL
}
DIA_CIPHER_SUITE;


/**
 * Certificates types  
 */
typedef enum _certificateType
{
    NO_CERT = 0,
    ITS_X509,
    PGP
}
DIA_CERTIFICATE_TYPE;

//Transform pluggins for DTF
typedef struct  _trasformPlugin
{
	string pluginName;
	string dictId1;
	string dictId2;
	string config;
}
DIA_TRANFORM_PLUGIN;


/** Interface:
 *      ITSDiaConfig
 *      
 *  Purpose:
 *      DiaConfig class is used to encapsulate all Diameter stack 
 *      abstraction related configuration.
 **/
class ITSDiaConfig
{
public:
    class ProductInfo
    {
    public:
        ProductInfo():versionNo(0), firmwareRev(0), prodName(NULL), dictFile(NULL) {}

        ~ProductInfo()
        {
            if (prodName)
            {
                free ((char *)prodName);
            }
            if (dictFile)
            {
                free ((char *)dictFile);
            }
        }
        void SetVersionNo(ITS_UINT ver)
        {
            versionNo = ver;
        }

        ITS_UINT GetVersionNo() const
        {
           return versionNo;
        }

        void SetFirmwareRev(ITS_UINT rev)
        {
            firmwareRev = rev;
        }

        ITS_UINT GetFirmwareRev() const
        {
           return firmwareRev;
        }

        void SetName(const char* name)
        {
            prodName = strdup(name);
        }
 
        const char* GetName() const
        {
            return prodName;
        }

        void SetDictionary(const char* file)
        {
            dictFile = strdup(file);
        }

        const char* GetDictionary() const
        {
            return dictFile;
        }

        const char* GetProdName() const
        {
            return prodName;
        }


    private:
        ITS_UINT     versionNo;
        ITS_UINT     firmwareRev;
        const char*  prodName;
        const char*  dictFile;
    };

    class AuthSessionConfig
    {
    public:
        void SetSubType(ITS_BOOLEAN isStateful)
        {
            subType = isStateful;
        }

        //Fixing Type qualifier on return type is useless
        ITS_BOOLEAN GetSubType() const
        {
            return subType;
        }

        void SetTimeout(ITS_SERIAL val)
        {
            timeout = val;
        }

        //Fixing Type qualifier on return type is useless
        ITS_SERIAL GetTimeout() const
        {
            return timeout;
        }

        void SetLifeTime(ITS_SERIAL val)
        {
            lifetime = val;
        }

        //Fixing Type qualifier on return type is useless
        ITS_SERIAL GetLifeTime() const
        {
            return lifetime;
        }

        void SetGracePeriod(ITS_SERIAL val)
        {
            gracePeriod = val;
        }

        //Fixing Type qualifier on return type is useless
        ITS_SERIAL GetGracePeriod() const
        {
            return gracePeriod;
        }

        void SetRetryAbort(ITS_SERIAL val)
        {
            retryAbort = val;
        }
 
        //Fixing Type qualifier on return type is useless
        ITS_SERIAL GetRetryAbort() const
        {
            return retryAbort;
        }

    private:
        ITS_BOOLEAN subType;  /*Stateful/Stateless */
        ITS_SERIAL  timeout;
        ITS_SERIAL  lifetime;
        ITS_SERIAL  gracePeriod;
        ITS_SERIAL  retryAbort;
    };

    class AcctSessionConfig
    {
    public:

        AcctSessionConfig()
        {
           subType = false;  /*Stateful/Stateless */
           timeout = 0;
           interimIntvl = 0;
           realTime = 0;
        }

        void SetSubType(ITS_BOOLEAN isStateful)
        {
            subType = isStateful;
        }

        //coverity issue fix - 10818 - Parse Warning- return type meaningless
        //const ITS_BOOLEAN GetSubType() const
        ITS_BOOLEAN GetSubType() const
        {
            return subType;
        }

        void SetTimeout(ITS_SERIAL val)
        {
            timeout = val;
        }

        //coverity issue fix - 10818 - Parse Warning- return type meaningless
        //const ITS_SERIAL GetTimeout() const
        ITS_SERIAL GetTimeout() const
        {
            return timeout;
        }

        void SetInterimIntvl(ITS_SERIAL val)
        {
            interimIntvl = val;
        }

        //Fixing Type qualifier on return type is useless
        ITS_SERIAL GetInterimIntvl() const
        {
            return interimIntvl;
        }

        void SetRealTime(ITS_SERIAL val)
        {
            realTime = val;
        }


        //Fixing Type qualifier on return type is useless
        ITS_SERIAL GetRealTime() const
        {
            return realTime;
        }

    private:
        ITS_BOOLEAN subType;  /*Stateful/Stateless */
        ITS_SERIAL  timeout;
        ITS_SERIAL   interimIntvl;
        ITS_SERIAL   realTime;
    };

    class PeerTimersConfig
    {
    public:
        PeerTimersConfig()
        {
            watchdog = 30;
            expiry = 60;
            retry = 30;
            retransIntvl = 0;
            retransCount = 0;
	    sockFlushTimerVal = 2;
            sockFlushRetryCnt = -1;
        }
        void SetExpiry(ITS_SERIAL val)
        {
            expiry = val;
        }

        //Fixing Type qualifier on return type is useless
        ITS_SERIAL GetExpiry() const
        {
            return expiry;
        }
        void SetRetry(ITS_SERIAL val)
        {
            retry = val;
        }
        //Fixing Type qualifier on return type is useless
        ITS_SERIAL GetRetry() const
        {
            return retry;
        }
        void SetWatchdog(ITS_SERIAL val)
        {
            watchdog = val;
        }
        //Fixing Type qualifier on return type is meaningless
        ITS_SERIAL GetWatchdog() const
        {
            return watchdog;
        }
        void SetRetransIntvl(ITS_SERIAL val)
        {
            retransIntvl = val;
        }
        //Fixing Type qualifier on return type is useless
        ITS_SERIAL GetRetransIntvl() const
        {
            return retransIntvl;
        }
        void SetRetransCount(ITS_SERIAL val)
        {
            retransCount = val;
        }

        //Fixing Type qualifier on return type is useless
        ITS_SERIAL GetRetransCount() const
        {
            return retransCount;
        }

	void SetSockFlushTimerVal(ITS_SERIAL val)
	{
	    sockFlushTimerVal = val;	
	}
        
	ITS_SERIAL GetSockFlushTimerVal() const
	{
	    return sockFlushTimerVal;
	}
        
	void SetSockFlushRetryCnt(ITS_SERIAL val)
	{
	    sockFlushRetryCnt = val;
	}
        
	ITS_SERIAL GetSockFlushRetryCnt() const
	{
	    return sockFlushRetryCnt;
	}
    private:
        ITS_SERIAL   expiry;
        ITS_SERIAL   retry;
        ITS_SERIAL   watchdog;
        ITS_SERIAL   retransIntvl;
        ITS_SERIAL   retransCount;
	ITS_SERIAL   sockFlushTimerVal;
	ITS_INT      sockFlushRetryCnt;
    };

    /**
     * New type for the TLS security related configuations
     */
#ifdef TLS_ENABLED
    class SecurityConfig
    {
    public:
       
        SecurityConfig():tlsCrlPath(NULL),caTrustFile(NULL),credentialFile(NULL),clientCertFile(NULL),
                         clientKeyFile(NULL),serverCertFile(NULL),serverKeyFile(NULL),tlsCAPath(NULL),tlsOwnCertPath(NULL) 
        {
           tlsType = NO_TLS;
           tlsTraceLevel = 0;
           IdentVerification = false;
           cipherSuite = TLS_NO_CIPHER_SUITE;
           certType = NO_CERT;
           crlVerification =  false;
        }

        ~SecurityConfig()
        {
            if (caTrustFile)
            {
                free ((char *)caTrustFile);
            }
            if (credentialFile)
            {
                free ((char *)credentialFile);
            }
            if (clientCertFile)
            {
                free ((char *)clientCertFile);
            }
            if (clientKeyFile)
            {
                free ((char *)clientKeyFile);
            }
            if (serverCertFile)
            {
                free ((char *)serverCertFile);
            }
            if (serverKeyFile)
            {
                free ((char *)serverKeyFile);
            }
        }


        //Fixing Type qualifier on return type is useless
        DIA_TLS_TYPE GetTlsType()const
        {
            return tlsType;
        }

        void SetTlsType(DIA_TLS_TYPE tType)
        {
            tlsType = tType;
        }

        //Fixing Type qualifier on return type is meaningless
        bool IsIdentityVerifyEnabled()const
        {
            return IdentVerification;
        }

        void SetIdentityVerifyEnabled()
        {
            IdentVerification  = true;
        }

        void SetIdentityVerifyDisabled()
        {
            IdentVerification  = false;
        }

        //Fixing Type qualifier on return type is useless 
        DIA_CIPHER_SUITE GetCipherSuite()const
        {
            return cipherSuite;
        }

        void SetCipherSuite(DIA_CIPHER_SUITE cSuite)
        {
            cipherSuite = cSuite;
        }
        
        //Fixing Type qualifier on return type is useless
        DIA_CERTIFICATE_TYPE GetCertificateType()const
        {
            return certType;
        }

        void SetCertificateType(DIA_CERTIFICATE_TYPE cType)
        {
            certType = cType;
        }

        void SetCATrustFile(const char* ctf)
        {
            caTrustFile = strdup(ctf);
        }

        const char* GetCATrustFile() const
        {
            return caTrustFile;
        }

        void SetCredentialFile(const char* credFile)
        {
            credentialFile = strdup(credFile);
        }

        const char* GetCredentialFile() const
        {
            return credentialFile;
        }

        void SetClientCertFile(const char* clCertFile)
        {
            clientCertFile = strdup(clCertFile);
        }

        const char* GetClientCertFile() const
        {
            return clientCertFile;
        }

        void SetClientKeyFile(const char* clKeyFile)
        {
            clientKeyFile = strdup(clKeyFile);
        }

        const char* GetClientKeyFile() const
        {
            return clientKeyFile;
        }

        void SetServCertFile(const char* servCertFile)
        {
            serverCertFile = strdup(servCertFile);
        }

        const char* GetServCertFile() const
        {
            return serverCertFile;
        }

        void SetServKeyFile(const char* servKeyFile)
        {
            serverKeyFile = strdup(servKeyFile);
        }

        const char* GetServKeyFile() const
        {
            return serverKeyFile;
        }
       
        void SetCAPath(const char* cAPath)
        {
            tlsCAPath = strdup(cAPath);
        }

        const char* GetCAPath() const
        {
            return tlsCAPath;
        }

        void SetCrlPath(const char* crlPath)
        {
            tlsCrlPath = strdup(crlPath);
        }

        const char* GetCrlPath() const
        {
            return tlsCrlPath;
        }

        void SetCrlVerify(bool value)
        {
            crlVerification = value;
        }

        bool GetCrlVerify() const
        {   
            return crlVerification;
        }

        void SetOwnCertPath(const char* ownPath)
        {
            tlsOwnCertPath = ownPath;
        }

        const char * GetOwnCertPath() const
        {
            return tlsOwnCertPath;
        }

#ifdef TLS_ENABLED
        void SetTLSTraceLevel(ITS_UINT tracelevel);

        ITS_UINT GetTLSTraceLevel();
        void PrintSecurityConfig() const;
        void AddTrustedCA(its::CertificateAuthority *cauObj);
        int GetTrustedCACount(void);
        its::CertificateAuthority* GetTrustedCA(int index);
        vector<its::CertificateAuthority*> GetCertificateAuthority();

        void PopulateCipherList(std::string name);
        int GetCipherCount(void);
        std::string GetCipherAt(int index);
#endif        
    private:
        DIA_TLS_TYPE            tlsType;
        ITS_UINT                tlsTraceLevel;
        bool                    IdentVerification; 
#ifdef TLS_ENABLED
        DIA_CIPHER_SUITE        cipherSuite;
        DIA_CERTIFICATE_TYPE    certType;
        vector<its::CertificateAuthority*> TrustedCAs;
#endif
        vector<std::string>     cipherList;
        bool                    crlVerification;             
        const char*             tlsCrlPath;
        const char*             caTrustFile;
        const char*             credentialFile;
        const char*             clientCertFile;
        const char*             clientKeyFile;
        const char*             serverCertFile;
        const char*             serverKeyFile;
        const char*             tlsCAPath;
        const char*             tlsOwnCertPath;
    };
#endif

    class QueueMgmt
    {
    public:
        QueueMgmt()
        {
            downStreamThreadCount = 1;
            upStreamThreadCount   = 1;
            msgRouterThreadCount  = 1;
        }

        void SetDownStreamThreadCount(ITS_UINT num)
        {
            downStreamThreadCount = num;
        }
        void SetUpStreamThreadCount(ITS_UINT num)
        {
            upStreamThreadCount = num;
        }
        //Fixing Type qualifier on return type is meaningless
        ITS_UINT GetDownStreamThreadCount()
        {
            return downStreamThreadCount;
        }
        //Fixing Type qualifier on return type is meaningless
        ITS_UINT GetUpStreamThreadCount()
        {
            return upStreamThreadCount;
        }
        void SetMsgRouterThreadCount(ITS_UINT num)
        {
            msgRouterThreadCount = num;
        }
        const ITS_UINT GetMsgRouterThreadCount()
        {
            return msgRouterThreadCount;
        }

    private:
        ITS_UINT downStreamThreadCount;
        ITS_UINT upStreamThreadCount;
        ITS_UINT msgRouterThreadCount;
    };

   ~ITSDiaConfig();
    /********************************************************************/
    /** Purpose:
    *      Static Function to get the DiaConfig instance. 
    *
    *  Input Parameters:
    *      None.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Pointer to the singleton DiaConfig object.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    //static ITSDiaConfig* GetITSDiaConfig();

    static void ReloadITSDiaConfig();    
    
    void Lock() const;

    void Unlock() const;

    void DiaParserInitialize(char *fileName);
   
    void Print();

    ITS_TIME GetOriginStateId()
    {
        return originStateId;
    }

    ProductInfo& GetProductInfo()
    {
        return prodInfo;
    }

    DIA_HOST_INFO_LIST& GetHostInfoList()
    {
        return hostInfoList;
    }

    AuthSessionConfig& GetAuthSessionConfig()
    {
        return authSession;
    }

    AcctSessionConfig& GetAcctSessionConfig()
    {
        return acctSession;
    }

    PeerTimersConfig& GetPeerTimers()
    {
        return peerTimers;
    }

    QueueMgmt& GetQueueMgmt()
    {
        return queueMgmt;
    }

    diameter::base::CapabilitiesExchangeRequest * GetLocalCER()
    {
        return localCER;
    }

    void SetLocalCER(diameter::base::CapabilitiesExchangeRequest *cer)
    {
        localCER = cer;
    }

    diameter::base::CapabilitiesExchangeRequest * GetRFC6733LocalCER()
    {
        return rfc6733LocalCER;
    }

    void SetRFC6733LocalCER(diameter::base::CapabilitiesExchangeRequest *cer)
    {
        rfc6733LocalCER = cer;
    }

    diameter::base::CapabilitiesExchangeAnswer * GetLocalCEA()
    {
        return localCEA;
    }

    void SetLocalCEA(diameter::base::CapabilitiesExchangeAnswer *cea)
    {
        localCEA = cea;
    }

    diameter::base::CapabilitiesExchangeAnswer * GetRFC6733LocalCEA()
    {
        return rfc6733LocalCEA;
    }

    void SetRFC6733LocalCEA(diameter::base::CapabilitiesExchangeAnswer *cea)
    {
        rfc6733LocalCEA = cea;
    }
    bool IsMsgRedundancyEnabled()
    {
        return isMsgRedundancyEnabled;
    }

    void setMsgRedundancyEnabled(bool enable=true)
    {
        isMsgRedundancyEnabled = enable;
    }

    const char*& getMateHostName()
    {
        return mateHostName;
    }

    const char*& getLocalHostName()
    {
        return localHostName;
    }
    const char*& getpluginpathname()
    {
        return pluginPathName;
    }
    const char*& getLocalRealmName()
    {
        return localRealmName;
    }

    void setLocalHostInfo(const char *hostname, 
                          const char *realmName, 
                          const char* publicIpAddr)
    {
        if (hostInfoList.arr[0].servHostName)
        {
            free((char*)hostInfoList.arr[0].servHostName);
        }
        if (hostInfoList.arr[0].realmName)
        {
            free((char*)hostInfoList.arr[0].realmName);
        }
        if (hostInfoList.arr[0].transList[0].publicServerIpAddr)
        {
            free((char*)hostInfoList.arr[0].transList[0].publicServerIpAddr);
        }

        hostInfoList.arr[0].servHostName = strdup(hostname);
        hostInfoList.arr[0].realmName = strdup(realmName);
        hostInfoList.arr[0].transList[0].publicServerIpAddr = strdup(publicIpAddr);
        
        setLocalHostName(hostname);
        setLocalRealmName(realmName); 
    }
    
    void setLocalHostInfo(const char *hostname, 
                          const char *realmName)
    {
        if (hostInfoList.arr[0].servHostName)
        {
            free((char*)hostInfoList.arr[0].servHostName);
        }
        if (hostInfoList.arr[0].realmName)
        {
            free((char*)hostInfoList.arr[0].realmName);
        }

        hostInfoList.arr[0].servHostName = strdup(hostname);
        hostInfoList.arr[0].realmName = strdup(realmName);
        
        setLocalHostName(hostname);
        setLocalRealmName(realmName); 
    }

    void setLocalTptInfo(const char *serverIpAddr,DIA_TRANS_TYPE type,
                         ITS_USHORT port,const char **multiHomeIpps,int noIPs,
                         const char* publicIpAddr,ITS_USHORT securePort)
    {
        int index = 0;
        for(int i =0;i < MAX_TRANS_PER_LIST;i++)
        {
           if (hostInfoList.arr[0].transList[i].serverIpAddr == NULL)
           {
              index = i;
              break;
           }
        }
        if(type == ITS_DIA_T_SCTP)
        {
            hostInfoList.arr[0].transList[index].multiHomeipaddrs[0] = strdup(serverIpAddr);
            hostInfoList.arr[0].transList[index].noIPs = (unsigned)1;
        }
        hostInfoList.arr[0].transList[index].serverIpAddr = strdup(serverIpAddr);
        hostInfoList.arr[0].transList[index].type = type;
        if(port != 0)
        {
            hostInfoList.arr[0].transList[index].portNo = port;
        }
        if(securePort != 0)
        {
            hostInfoList.arr[0].transList[index].securePort = securePort;
        }
        if(publicIpAddr != NULL)
        {
            hostInfoList.arr[0].transList[index].publicServerIpAddr = strdup(publicIpAddr);
        }
        else
        {
            hostInfoList.arr[0].transList[index].publicServerIpAddr = strdup(serverIpAddr); 
        }
        for(int i = 1;i <= noIPs;i++)
        {
            hostInfoList.arr[0].transList[index].multiHomeipaddrs[i]=multiHomeIpps[i-1];
        }
        hostInfoList.arr[0].transList[index].noIPs = 1 + noIPs;
        hostInfoList.arr[0].transCnt = index+1;
    }

    void getLocalTptInfo(int* type, ITS_USHORT* port)
    {
        *type = (int) hostInfoList.arr[0].transList[0].type;
        *port = hostInfoList.arr[0].transList[0].portNo;
    }


    void setLocalHostName(const char *hostname)
    {
        if (localHostName)
        {
           free((char*)localHostName);
        }
        localHostName = strdup(hostname);
    } 
    void setPluginPathName(const char *pathname)
    {
        if (pluginPathName)
        {
           free((char*)pluginPathName);
        }
        pluginPathName = strdup(pathname);
    } 

    void setLocalRealmName(const char *realmName)
    {
        if (localRealmName)
        {
           free((char*)localRealmName);
        }
        localRealmName = strdup(realmName);
    }
   
    bool IsDefaultRealmRoutingEnabled()
    {
        return isDefaultRealmRoutingEnabled;
    }

    void setDefaultRealmRoutingEnabled()
    {
        isDefaultRealmRoutingEnabled = true;
    }

    bool IsPeerMsgToAppEnabled()
    {
        return peerMsgToAppEnabled;
    }

    void setPeerMsgToAppEnabled()
    {
        peerMsgToAppEnabled = true;
    }

    bool IsRedundancyEnabled()
    {
        return isRedundancyEnabled;
    }
 
    void setRedundancyEnabled(bool enable=true)
    {
        isRedundancyEnabled = enable;
    }

    void SetRedundancyFeature(ITS_Class redun)
    {
        redunClass = redun;
    }

    void SetDccaFeature(ITS_Class dcca)
    {
        dccaClass = dcca;
    }

    ITS_Class GetRedundancyFeature() 
    { 
        return redunClass;
    }

    ITS_Class GetDccaFeature() 
    { 
        return dccaClass;
    }
  
    void SetOriginStateIdOpt()
    {
       iforiginStateId = true;
    }

    bool GetOriginStateIdOpt()
    {
       return iforiginStateId;
    }   

    void SetHexDumpEnabled()
    {
       enableHexDump = true;
    }

    void SetHexDumpDisabled()
    {
       enableHexDump = false;
    }

    bool IsHexDumpEnabled()
    {
       return enableHexDump;
    }

    void SetInterWorkingMode(bool mode)
    {
       interWorkingMode = mode;
    }

    bool IsInterWorkingMode()
    {
       return interWorkingMode;
    }

    void SetHMIEnabled()
    {  
       HMI_Enable(ITS_TRUE);  
       enableHMI = true;
    }
    void SetHMIDisabled()
    {  
       HMI_Disable(ITS_FALSE);
       enableHMI = false;
    }
    bool IsHMIEnabled()
    {
       return enableHMI;
    }

    void SetStatisticsEnabled()
    {
       enableStackStats = true;
       isStackStatsEnabled = enableStackStats;
    }

    void SetStatisticsDisabled()
    {
       enableStackStats = false;
       isStackStatsEnabled = enableStackStats;
    }

    bool IsStatisticsEnabled()
    {
       return enableStackStats;
    }
 
    void EnableRelayAdvertisement()
    {
        relayAdvertisement = true;
    }
 
    bool IsAdvertisedRelay()
    {
        return relayAdvertisement;
    }
#ifdef TLS_ENABLED
    SecurityConfig& GetSecurityConfig()
    {
        return security;
    }
#endif
    void EnableQueueMgmt()
    {
        enableQueueMgmt = true;
    }

    void DisableQueueMgmt()
    {
        enableQueueMgmt = false;
    }

    bool IsQueueMgmtEnabled()
    {
        return enableQueueMgmt;
    }
    void EnablePeerIpCheck()
    {
       enablePeerIpCheck = true;
    }

    void DisablePeerIpCheck()
    {
       enablePeerIpCheck = false;
    }

    bool IsPeerIpCheckEnabled()
    {
       return enablePeerIpCheck;
    }
    const char*& GetLocalIpAddr()
    {
        return localIpAddr;
    }
    //Fixing Type qualifier on return type is meaningless
    void SetLocalIpAddr(const char* localIp)
    {
        localIpAddr = strdup(localIp);
    }
    bool IsDistScenario()
    {
       return isDistScenario;
    }

    void SetDistScenarioFlag()
    {
       isDistScenario = true;
    }

    bool GetInitiateConnsOpt()
    {
       return initiateConnsOpt;
    }

    void UnSetInitiateConnsOpt()
    {
       initiateConnsOpt = false;
    }

    ITS_SockConfigOpt* GetStreamSocketConfig()
    {
        return &sockConfig;
    }
    void PrintStreamSocketConfig();

    void PrintTcpSocketConfig();

    ITS_TcpSockConfigOpt* GetTcpSocketConfig()
    {
        return &tcpSockConfig;
    }

    bool IsLocalCachingEnabled()
    {
        return isLocalCachingEnabled;
    }
 
    void setLocalCachingEnabled()
    {
        isLocalCachingEnabled = true;
    }
 
    bool IsRedirectAppProcessing()
    {
        return isRedirectAppProcessing;
    }
 
    void setRedirectAppProcessing()
    {
        isRedirectAppProcessing = true;
    }
    void RegisterIDSMsgProcessingCB(void *cbFunc)
    {
        IDSMsgProcessCallBack = (IDSMsgProcessFunc)cbFunc; 
    }
    void RegisterIDSRedundancyCB(void *cbFunc)
    {
        IDSRedundancyCallBack = (IDSMsgProcessFunc)cbFunc;
    }

    void RegisterIDSCmdProcessingCB(void *cbFunc)
    {
       IDSCmdProcessCallBack = (IDSCmdProcessFunc)cbFunc; 
    }
	
    void setIpv6Enabled()
    {
        ipv6Enabled = true;
    }

    bool isIpv6Enabled()
    {
        return ipv6Enabled;
    }

    bool isPeerDiscoveryEnabled()
    {
        return peerDiscoveryEnabled;
    }

    void setPeerDiscoveryEnabled()
    {
        peerDiscoveryEnabled = true;
    }

    void unsetPeerDiscoveryEnabled()
    {
        peerDiscoveryEnabled = false;
    }
   
    void setDiscoveryInterval(int val)
    {
        peerDiscoveryInterval = val;
    }

    int getDiscoveryInterval()
    {
        return peerDiscoveryInterval;
    }

    void setLocalIpv6DscpVal(int val)
    {
        ipv6DscpValue = val;
    }

    int getLocalIpv6DscpVal()
    {
        return ipv6DscpValue;
    }
    bool DisableStackInitiatedSTR()
    {
        return disStackInitiatedStr;
    }

    void SetDisableStackInitiatedSTR()
    {
        disStackInitiatedStr = true;
    }

    bool IsDTFEnabled()
    {
        return isDTFEnabled;
    }
    void setDTFEnabled(bool enable)
    {
        isDTFEnabled = enable;
    }
protected:
    bool                    isDebugDump;
    static its::ITS_Mutex   lock;
    static its::ITS_Mutex   guard;
    ITS_TIME                originStateId;
    ProductInfo             prodInfo;
    DIA_HOST_INFO_LIST      hostInfoList;
    AuthSessionConfig       authSession;
    AcctSessionConfig       acctSession;
    PeerTimersConfig        peerTimers;
    DIA_CER                 *localCER; 
    DIA_CEA                 *localCEA; 
    DIA_CER                 *rfc6733LocalCER; 
    DIA_CEA                 *rfc6733LocalCEA; 
    const char              *mateHostName; /*used for redundancy*/
    const char              *localHostName;
    const char              *localRealmName;
    bool                    isMsgRedundancyEnabled; /*used for redundancy */
    bool                    isRedundancyEnabled; /*used for redundancy */
    bool                    isDefaultRealmRoutingEnabled;/*used for redundancy*/
    bool                    peerMsgToAppEnabled; /*Peer based msgs to App */
    ITS_Class               redunClass;
    ITS_Class               dccaClass;
    bool                    iforiginStateId;
    bool                    enableHexDump;
    bool 		    enableHMI;	
    bool                    relayAdvertisement;
#ifdef TLS_ENABLED
    SecurityConfig          security;
#endif
    QueueMgmt               queueMgmt;
    bool                    enableQueueMgmt;
    bool                    enablePeerIpCheck;
    const char              *localIpAddr;
    bool                    isDistScenario;
    bool                    enableStackStats;
    bool                    initiateConnsOpt;
    ITS_SockConfigOpt       sockConfig;
    ITS_TcpSockConfigOpt    tcpSockConfig;
    bool                    isLocalCachingEnabled;
    bool                    isRedirectAppProcessing;
    bool                    ipv6Enabled;
    bool                    peerDiscoveryEnabled;
    int                     peerDiscoveryInterval;
    int                     ipv6DscpValue;
    bool                    disStackInitiatedStr;
    bool                    isDTFEnabled;
    bool                    isTlsEnabled;
    const char              *pluginPathName;
	vector<DIA_TRANFORM_PLUGIN> TransformPlugin;
    bool                    isPredictiveLoopAvdRequired;
    bool                    isSnaptrSupported;
    bool                    interWorkingMode;
public:
    ITSDiaConfig();                               /* Private Constructor */
	void PopulateTransformPlugin(DIA_TRANFORM_PLUGIN &plugin);
	void PrintTransformPlugin(void);
	int GetTransfromPluginCount(void);
	DIA_TRANFORM_PLUGIN &GetTranformPluginAt(int index);
    void setTlsEnable(bool status);
    bool isTlsEnable();
    void setPredectiveLoopAvoidanceEnable(bool status);
    bool isPredictiveLoopAvoidanceEnable();
    void setIsSnaptrSupportedFlag(bool status);
    bool isSnaptrSupportEnabled();
private:
    ITSDiaConfig(const ITSDiaConfig&);            /* Prevent Copy Constructor */
    ITSDiaConfig& operator=(const ITSDiaConfig&); /* Prevent assignment */
};

//#define DIA_CFG()  ITSDiaConfig::GetITSDiaConfig()
extern ITSDiaConfig itsDiaConfig;


#endif    
