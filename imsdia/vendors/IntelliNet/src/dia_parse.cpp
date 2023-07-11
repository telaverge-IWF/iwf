/*********************************-*-C-*-************************************
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
 * LOG: $Log: dia_parse.cpp,v $
 * LOG: Revision 3.48.4.13.4.5.2.1.2.6.4.3.2.1.4.1  2014/12/04 12:00:26  pramana
 * LOG: Added support for allowing requests for a different hosts
 * LOG:
 * LOG: Revision 3.48.4.13.4.5.2.1.2.6.4.3.2.1  2014/07/10 06:57:04  millayaraja
 * LOG: fix for updating TCP connectonTimeout
 * LOG:
 * LOG: Revision 3.48.4.13.4.5.2.1.2.6.4.3  2014/03/05 11:07:53  jvikram
 * LOG: As TLS was disabled 6733 CEA was being sent out 'coz of which InbandSecurityId was not being included as 6733 CEA was not being set with. Same has been fixed
 * LOG:
 * LOG: Revision 3.48.4.13.4.5.2.1.2.6.4.2  2014/03/05 10:56:24  jvikram
 * LOG: As TLS was disabled 6733 CEA was being sent out 'coz of which OriginStateId was not being included as 6733 CEA was not being set with. Same has been fixed
 * LOG:
 * LOG: Revision 3.48.4.13.4.5.2.1.2.6.4.1  2014/02/12 07:15:00  millayaraja
 * LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
 * LOG:
 * LOG: Revision 3.48.4.13.4.5.2.1.2.6  2013/12/13 09:34:58  vsarath
 * LOG: Merged the session-splict changes
 * LOG:
 * LOG: Revision 3.48.4.13.4.5.2.1.2.5  2013/12/09 04:52:26  ncshivakumar
 * LOG: Fixed bug 2439,2443,2368,1898
 * LOG:
 * LOG: Revision 3.48.4.13.4.5.2.1.2.4  2013/11/27 06:22:37  ncshivakumar
 * LOG: Updated for lincense issues handling
 * LOG:
 * LOG: Revision 3.48.4.13.4.5.2.1.2.3  2013/11/26 14:34:21  ncshivakumar
 * LOG: RFC6733 changes
 * LOG:
 * LOG: Revision 3.48.4.13.4.5.2.1.2.2  2013/10/26 07:42:21  ncshivakumar
 * LOG: RFC 6733 changes
 * LOG:
 * LOG: Revision 3.48.4.13.4.5.2.1.2.1  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 3.48.4.13.4.5.2.1  2013/06/03 11:54:13  millayaraja
 * LOG: modified to disable logs for the test app to run the load with new logging of stack using CLOG which is under the  flag
 * LOG:
 * LOG: Revision 3.48.4.13.4.5  2013/04/12 04:17:48  vsarath
 * LOG: Logs improvement
 * LOG:
 * LOG: Revision 3.48.4.13.4.4  2013/04/01 05:56:45  vsarath
 * LOG: Fix for Coverity warnings
 * LOG:
 * LOG: Revision 3.48.4.13.4.3  2013/03/21 12:54:24  ncshivakumar
 * LOG: Added code to update watch dog timer for peer for test client
 * LOG:
 * LOG: Revision 3.48.4.13.4.2  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.48.4.13.4.1  2013/02/12 05:42:28  vsarath
 * LOG: Changes for TLS enable/disable
 * LOG:
 * LOG: Revision 3.48.4.13  2012/12/28 09:25:17  mallikarjun
 * LOG: Bug 757 chages
 * LOG:
 * LOG: Revision 3.48.4.12  2012/12/15 06:05:20  vsarath
 * LOG: Provided option for own Certificate path
 * LOG:
 * LOG: Revision 3.48.4.11  2012/12/03 08:41:20  ncshivakumar
 * LOG: Changes done for adding static routing table
 * LOG:
 * LOG: Revision 3.48.4.10  2012/11/28 05:47:36  vsarath
 * LOG: Fix for issue 89
 * LOG:
 * LOG: Revision 3.48.4.9  2012/11/20 12:23:23  pramana
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 3.48.4.4.14.2  2012/11/20 04:19:39  pramana
 * LOG: merged from 00 branch
 * LOG:
 * LOG: Revision 3.48.4.7  2012/11/06 16:31:20  pramana
 * LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
 * LOG:
 * LOG: Revision 3.48.4.4.12.3  2012/11/06 10:06:33  cprem
 * LOG: Merged from 00 branch for 0212-06 release
 * LOG:
 * LOG: Revision 3.48.4.4.12.2  2012/11/06 08:57:52  vsarath
 * LOG: Added for TLS enhancements
 * LOG:
 * LOG: Revision 3.48.4.4.12.1  2012/11/05 03:38:10  vsarath
 * LOG: Added for TLS enhancements
 * LOG:
 * LOG: Revision 3.48.4.6  2012/11/05 12:15:47  pramana
 * LOG: Fix for coverity issues
 * LOG:
 * LOG: Revision 3.48.4.5  2012/10/23 08:08:56  cprem
 * LOG: Support for new transformation plugin configuration.
 * LOG:
 * LOG: Revision 3.48.4.4.2.1  2012/11/05 09:49:36  ncshivakumar
 * LOG: Coverit fixes
 * LOG:
 * LOG: Revision 3.48.4.4  2012/10/19 17:54:43  brajappa
 * LOG: BugId 15: IPv6 support enhancements
 * LOG:
 * LOG: Revision 3.48.4.3  2012/10/03 15:08:43  cprem
 * LOG: Merged from ERLBF branch B-DRE-0212-02
 * LOG:
 * LOG: Revision 3.48.4.2.2.1  2012/09/20 07:53:40  cprem
 * LOG: Support for multiple dictionary id configuration per peer.
 * LOG:
 * LOG: Revision 3.48.4.2  2012/09/06 11:30:45  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 * LOG:
 * LOG: Revision 3.48.6.4  2012/08/29 11:47:15  cashok
 * LOG: Added plugin path in configuration
 * LOG:
 * LOG: Revision 3.48.6.3  2012/08/23 11:32:29  jvikas
 * LOG: 1. Reading dictId from Peer Table Configuration
 * LOG: 2. Calling BaseGenericCmd Destructor in DiaMsgFlow Destructor
 * LOG: 3. Changed DictId ITS_UINT
 * LOG: 4. Added HandleTransConfig
 * LOG:
 * LOG: Revision 3.48.6.2  2012/08/22 13:29:08  cashok
 * LOG: Added Dictionary Id to xml configuration
 * LOG:
 * LOG: Revision 3.48.6.1  2012/08/22 12:53:43  jvikas
 * LOG: Fixed Linking Errors and Included XML Config for Transformation.
 * LOG:
 * LOG: Revision 3.48.4.1  2012/08/21 08:55:57  ksalil
 * LOG: Merge from branch B-DRE-IDIA-0100-00
 * LOG:
 * LOG: Revision 3.48.2.2  2012/07/17 09:10:00  pramana
 * LOG: modification for standard port bug 108/109
 * LOG:
 * LOG: Revision 3.48.2.1  2012/07/13 10:56:19  ncshivakumar
 * LOG: Modification for InbandSecurityid
 * LOG:
 * LOG: Revision 3.48  2011/07/22 05:02:12  rajeshak
 * LOG: Parsing Issue in RedirectAgent
 * LOG:
 * LOG: Revision 3.47  2011/07/14 14:04:51  vkumara
 * LOG: ForceDisconnect Requirement - Not to initiate connection.
 * LOG:
 * LOG: Revision 3.46  2011/04/26 06:12:33  nvijikumar
 * LOG: Introduced XML config parameter to disable stack initiated STR while
 * LOG: handling ASA
 * LOG:
 * LOG: Revision 3.45  2010/11/03 12:54:24  vkumara
 * LOG: DSCP support for IPV6
 * LOG:
 * LOG: Revision 3.44  2010/09/20 05:13:32  nvijikumar
 * LOG: 1. trIndx -1 is invalid for unsigned short
 * LOG: 2. Introduced delay in dynamic peer start (dia_mgmt.cpp)
 * LOG:
 * LOG: Revision 3.43  2010/08/31 09:45:35  vkumara
 * LOG: DSCP value range validation added.
 * LOG:
 * LOG: Revision 3.42  2010/08/27 12:28:12  nvijikumar
 * LOG: DSCP value support (IP header) - Vasanth
 * LOG:
 * LOG: Revision 3.41  2010/07/07 08:24:46  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 3.40  2009/08/24 12:12:57  rajeshak
 * LOG: Removed compilation error.
 * LOG:
 * LOG: Revision 3.39  2009/08/24 11:48:12  rajeshak
 * LOG: freeing memory after inserting into destionation list.
 * LOG:
 * LOG: Revision 3.38  2009/08/24 04:46:27  rajeshak
 * LOG: Fix for Issue 2319. (IDS sends messages to first destination entry
 * LOG: in Realm Table even though it has lesser priority than other Peer,
 * LOG: after changing its Priority using "modifyPriority" MML command.)
 * LOG: Reordering Destination entries after ModifyPriority.
 * LOG:
 * LOG: Revision 3.37  2009/08/13 11:43:59  rajeshak
 * LOG: Inserting peers into realmEntry destination list based on priority
 * LOG:
 * LOG: Revision 3.36  2009/07/14 10:05:46  rajeshak
 * LOG: Changes done to include peer realm name  in destination.
 * LOG:
 * LOG: Revision 3.35  2009/07/13 06:46:21  rajeshak
 * LOG: Reverting back session table changes.
 * LOG:
 * LOG: Revision 3.34  2009/06/29 14:54:53  rajeshak
 * LOG: Changes done for performance enhancement (splitting the session table).
 * LOG:
 * LOG: Revision 3.33  2009/04/13 13:36:57  rajeshak
 * LOG: Peer Discovery changes.
 * LOG:
 * LOG: Revision 3.32  2009/04/10 06:33:15  sureshj
 * LOG: Parsing added for enableHMI flag in IDS xml.
 * LOG:
 * LOG: Revision 3.31  2009/04/07 12:39:49  rajeshak
 * LOG: Checking Destination count before inserting into realm destination list.
 * LOG: (fix for motorala core dump issue when no of destination is more than 64)
 * LOG:
 * LOG: Revision 3.30  2009/03/23 10:44:01  ssaxena
 * LOG: Fix for the Issue 1785, IDS is coming up with local host and realm
 * LOG: name given as NULL string. Exit from stack, if mandatory information
 * LOG: of CE found as a NULL string.
 * LOG:
 * LOG: Revision 3.29  2009/03/23 06:12:11  ssaxena
 * LOG: Fix for the Issue 1742, IDS is able to send CER message without
 * LOG: Mandatory AVP. Exit from the stack with proper debug print on
 * LOG: missing mandatory information of CE.
 * LOG:
 * LOG: Revision 3.28  2009/03/19 12:39:28  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.27  2009/03/16 13:21:40  rajeshak
 * LOG: Fix for Issue Id:1739
 * LOG: (ProxyInfoAvp is enabled in spite of giving as "No" in xml)
 * LOG: Fixed the pasring problem.
 * LOG:
 * LOG: Revision 3.26  2009/03/03 11:17:20  rajeshak
 * LOG: Klockwork reported issue fix
 * LOG:
 * LOG: Revision 3.25  2009/03/03 06:52:05  chandrashekharbs
 * LOG: Changes for IPV6 support
 * LOG:
 * LOG: Revision 3.24  2009/02/27 06:15:26  rajeshak
 * LOG: Printing SCTP params configured in XML.
 * LOG:
 * LOG: Revision 3.23  2009/02/19 14:06:50  ssaxena
 * LOG: Partial fix for the whizible issue Id 1493, 1481 and 1482.
 * LOG: Default routing failed and Relay/Proxy failed to forward
 * LOG: ASR/RAR.
 * LOG:
 * LOG: Revision 3.22  2009/02/17 12:52:03  sureshj
 * LOG: Fix for the issue 1485. MML enTrace not showing traces when not configured
 * LOG: in xml. Added missing fix to file (3.14).
 * LOG:
 * LOG: Revision 3.21  2009/02/04 05:48:40  nvijikumar
 * LOG: Changes to make Initiate Peer connections as configurable
 * LOG:
 * LOG: Revision 3.20  2009/02/03 10:21:11  ssaxena
 * LOG: Modifications done for Redirect Agent functionality.
 * LOG:
 * LOG: Revision 3.19  2009/02/02 06:46:28  rajeshak
 * LOG: Parsing sctp socket configuration parameters
 * LOG:
 * LOG: Revision 3.18  2009/01/03 06:56:03  nvijikumar
 * LOG: Setting Peer's trIndex while inserting entry
 * LOG:
 * LOG: Revision 3.17  2009/01/03 05:46:35  rajeshak
 * LOG: Fix for KLOCK Work reported issues
 * LOG:
 * LOG: Revision 3.16  2008/12/12 18:30:47  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.15  2008/12/12 05:55:48  sureshj
 * LOG: Support for Stack statistics
 * LOG:
 * LOG: Revision 3.14  2008/12/10 10:57:57  nvijikumar
 * LOG: Changes to allow enable/disable traces via MML event if value is not
 * LOG: Configured in the XML
 * LOG:
 * LOG: Revision 3.13  2008/11/26 12:03:28  nvijikumar
 * LOG: Local IP binding for Client Sockets
 * LOG:
 * LOG: Revision 3.12  2008/11/19 05:14:15  nvijikumar
 * LOG: IssueID:None
 * LOG: FeatureID:None
 * LOG: Description:Made Peer IP Check as configurable option
 * LOG:
 * LOG: Revision 3.11  2008/11/13 08:51:25  nvijikumar
 * LOG: IssueID:None
 * LOG: FeatureID:None
 * LOG: Description:External IP configuration Support
 * LOG:
 * LOG: Revision 3.10  2008/11/06 07:51:22  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Incorporating Code review Comments renaming StackTunning
 * LOG:              with QueueMgmt
 * LOG:
 * LOG: Revision 3.9  2008/10/31 05:52:23  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID:none
 * LOG: Description:Configuration enhancements for Stack Tunning
 * LOG:
 * LOG: Revision 3.8  2008/08/25 05:43:57  ssaxena
 * LOG: Made Failback as configurable option
 * LOG:
 * LOG: Revision 3.7  2008/07/09 11:03:19  vnarang
 * LOG: Converting #if to #ifdef
 * LOG:
 * LOG: Revision 3.6  2008/07/09 10:55:32  vnarang
 * LOG: Adding a check for TLS_ENABLED flag during compilation & X509 is changed toITS_X509 due to name Conflict
 * LOG:
 * LOG: Revision 3.5  2008/06/13 11:28:29  hbhatnagar
 * LOG: Added functionality to parse newly added Tls-Security Tag in the XML.
 * LOG:
 * LOG: Revision 3.4  2008/04/21 12:11:21  nanaparthi
 * LOG: Fix for Issue #854
 * LOG:
 * LOG: Revision 3.3  2008/04/07 18:46:09  hbhatnagar
 * LOG: Using a macro in place of magic number 0xffffffff.
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:40:05  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.19  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.17.2.1  2007/03/30 12:36:02  nvijikumar
 * LOG: Fix for Addition of same appId multiple times to the CER.
 * LOG: Bridgewater requirement.
 * LOG:
 * LOG: Revision 2.17  2007/02/26 04:45:09  nvijikumar
 * LOG: Enable Hexdump print by default without xml changes.
 * LOG:
 * LOG: Revision 2.16  2007/02/19 15:18:42  nvijikumar
 * LOG: Control Message hex dump from XML configuration.
 * LOG:
 * LOG: Revision 2.15  2007/02/17 06:04:30  nanaparthi
 * LOG: Part of Fix for Internal Cleanup Activity
 * LOG:
 * LOG: Revision 2.14  2006/12/29 06:56:18  nanaparthi
 * LOG: SCTP Multihoming related changes (baseline code base)
 * LOG:
 * LOG: Revision 2.13  2006/12/21 15:34:15  tpanda
 * LOG: Minor fixes to previous commit related to OriginStateId
 * LOG:
 * LOG: Revision 2.12  2006/12/21 15:26:04  tpanda
 * LOG: AddOriginStateId option is added to check if OriginStateId be added to cmd
 * LOG:
 * LOG: Revision 2.11  2006/12/20 14:57:42  tpanda
 * LOG: Other bug fixes related to redundancy(Issue#5075,5073,5069,5057 etc)
 * LOG:
 * LOG: Revision 2.10  2006/12/11 14:27:34  nvijikumar
 * LOG: Send Peer based msgs to application, if peerMsgToApp flag is set in the XML.
 * LOG:
 * LOG: Revision 2.9  2006/12/10 13:42:42  tpanda
 * LOG: Redundancy Bug Fixes and enhancements--Transport Order Fix
 * LOG:
 * LOG: Revision 2.8  2006/11/29 11:52:14  tpanda
 * LOG: Redundancy related enhancements and fixes for few bugs raised for redundancy
 * LOG:
 * LOG: Revision 2.7  2006/11/28 13:59:05  yranade
 * LOG: Updates to set productName from xml configuration.
 * LOG:
 * LOG: Revision 2.6  2006/11/24 03:47:33  nvijikumar
 * LOG: Alternate peer lookup from hostname and realm (Failover).
 * LOG:
 * LOG: Revision 2.5  2006/11/22 10:49:37  nvijikumar
 * LOG: Baseline PendingQ ( Failover ) Changes.
 * LOG:
 * LOG: Revision 2.4  2006/10/30 12:11:23  yranade
 * LOG: Set Origin-State-Id.
 * LOG:
 * LOG: Revision 2.3  2006/10/24 13:59:29  yranade
 * LOG: Use correct destination vendorId string.
 * LOG:
 * LOG: Revision 2.2  2006/10/05 13:21:54  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 ****************************************************************************/
#include <stdio.h>
#include <iostream>
#include <errno.h>
#include <strings.h>
#include <signal.h>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>

#include <its++.h>
#include <its_exception.h>
#include <its_exception_log.h>
#include <its_event_log.h>
#include <its_iniparse.h>

#include <expat.h>

#include <itsdiameter.h>
#include <dia_trace.h>
#include <dia_cmn.h>
#include <dia_err.h>
#include <dia_parse.h>
#include <its_dia_config.h>

#include <dia_peer_table.h>
#include <dia_ip_trans.h>
#include <dia_realm_table.h>
#include <dia_redirect.h>
#include <dia_utils.h>

#ifdef FOR_DRE
#include<Component.h>
#endif

#include <dia_static_routing_table.h>
#include <its_dre_exit_error_codes.h>
#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
#endif

static ITS_BOOLEAN inStaticRoutingConfig = ITS_FALSE;
static ITS_BOOLEAN inLocalConfig = ITS_FALSE;
static ITS_BOOLEAN inVendorSpecific = ITS_FALSE;
static ITS_BOOLEAN inHostInfo = ITS_FALSE;
static ITS_BOOLEAN inSessionConfig = ITS_FALSE;
static ITS_BOOLEAN inTrace = ITS_FALSE;
static ITS_BOOLEAN inPeerConfig = ITS_FALSE;
static ITS_BOOLEAN inPeer = ITS_FALSE;
static ITS_BOOLEAN inRealmConfig = ITS_FALSE;
static ITS_BOOLEAN inDestination = ITS_FALSE;

static ITS_BOOLEAN isInband        = ITS_FALSE;
static ITS_BOOLEAN isVendorId      = ITS_FALSE;
static ITS_BOOLEAN isSupported     = ITS_FALSE;
static ITS_BOOLEAN isAuthId        = ITS_FALSE;
static ITS_BOOLEAN isAccounting    = ITS_FALSE;
static ITS_BOOLEAN isRetransIntv   = ITS_FALSE;
static ITS_BOOLEAN isRetransCnt    = ITS_FALSE;
static ITS_BOOLEAN isFailover      = ITS_FALSE;
static ITS_BOOLEAN isFailback      = ITS_FALSE;
static ITS_BOOLEAN isRedundantMate = ITS_FALSE;

static int critMask;
static int errMask;
static int warnMask;
static int dbgMask;
static int eventMask;

static XML_Parser   parser;
static ITS_BOOLEAN  inParser = ITS_FALSE;
static DIA_HOST_INFO hInfo;
static DIA_TRANS_INFO trans;
const char **peerIPaddrs = NULL;
static int otherPeerIPno = 0;
const char **transIPaddrs = trans.multiHomeipaddrs;
static int otherTranIPno = 0;
static bool vendorIdPresnt = false;
static DIA_TRANFORM_PLUGIN plugin;

static ITS_BOOLEAN inSecurityConfig = ITS_FALSE;
static ITS_BOOLEAN inTrustedCAs = ITS_FALSE;
static ITS_BOOLEAN inTlsCipherSuites = ITS_FALSE;
static ITS_BOOLEAN tlsEnabled = ITS_FALSE;


#define DIA_PARSER_ASSERT(assertion)                                               \
    if (!(assertion))                                                              \
    {                                                                              \
        ITS_ASSERT_PRINT(assertion);                                               \
        if (inParser)                                                              \
        {                                                                          \
            fprintf(stderr, "At around line %d column %d in parsed text.\n",       \
                    XML_GetCurrentLineNumber(parser),                              \
                    XML_GetCurrentColumnNumber(parser));                           \
        }                                                                          \
        exit(ITS_DRE_CONFIG_FILE_ERROR);                                                                   \
    }

static ITSDiaConfig *config = NULL;
static DIA_CER *cer = NULL;
static DIA_CEA *cea = NULL;
static DIA_CER *rfc6733CER = NULL;
static DIA_CEA *rfc6733CEA = NULL;

static void
HandleDiaStack(const char **attr)
{
    ITS_UINT version = 0;

    config = &itsDiaConfig;
    ITSDiaConfig::ProductInfo& info = config->GetProductInfo();
    cer = new CapabilitiesExchangeRequest(false, false);
    cea = new CapabilitiesExchangeAnswer(false, false);
    rfc6733CER = new CapabilitiesExchangeRequest(false, false);
    rfc6733CEA = new CapabilitiesExchangeAnswer(false, false);
    config->SetLocalCER(cer);
    config->SetLocalCEA(cea);
    config->SetRFC6733LocalCER(rfc6733CER);
    config->SetRFC6733LocalCEA(rfc6733CEA);

    info.SetName(ITS_DIA_PRODUCT_NAME);

    /* parse the attributes */
    while (*attr)
    {
        const char *tattr = *attr;
        attr ++;
        if (strcmp(tattr, DIA_VER_STRING) == 0)
        {
            version = RESFILE_ParseNum(*attr);

            info.SetVersionNo(version);
            info.SetFirmwareRev(version);
            cer->setFirmwareRevision(FirmwareRevision(version));
            cea->setFirmwareRevision(FirmwareRevision(version));
            rfc6733CER->setFirmwareRevision(FirmwareRevision(version));
            rfc6733CEA->setFirmwareRevision(FirmwareRevision(version));
        }
        else if (strcmp(tattr, DIA_DICT_FILE_STRING) == 0)
        {
            info.SetDictionary(*attr);
        }
        else if (strcmp(tattr, DIA_PRODUCT_NAME_STRING) == 0)
        {
            info.SetName(*attr);
        }
        else if (strcmp(tattr, DIA_DEFAULT_ROUTING_STRING) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.setDefaultRealmRoutingEnabled();
            }
        }
        else if (strcmp(tattr, DIA_PEER_MSG_TO_APP_STRING) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.setPeerMsgToAppEnabled();
            }
        }
        else if (strcmp(tattr, DIA_ADD_ORIG_STATE_ID_STRING) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.SetOriginStateIdOpt();
            }
        }
        else if (strcmp(tattr, DIA_ENABLE_HEXDUMP_STRING) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.SetHexDumpEnabled();
            }
            else
            {
                itsDiaConfig.SetHexDumpDisabled();
            }
        }
        else if (strcmp(tattr, DIA_ENABLE_HMI_STRING) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.SetHMIEnabled();
            }
            else
            {
                itsDiaConfig.SetHMIDisabled();
            }
        }

        else if (strcmp(tattr, DIA_ENABLE_STACK_STATS_STRING) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.SetStatisticsEnabled();
            }
            else
            {
                itsDiaConfig.SetStatisticsDisabled();
            }
        }
        else if (strcmp(tattr, DIA_ENABLE_PEER_IPCHECK_STRING) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.EnablePeerIpCheck();
            }
        }
        else if (strcmp(tattr, DIA_INITIATE_CONNS_STRING) == 0)
        {
            if (!RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.UnSetInitiateConnsOpt();
            }
        }
        else if (strcmp(tattr, DIA_ENABLE_LOCAL_CACHING_STRING) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.setLocalCachingEnabled();
            }
        }
        else if (strcmp(tattr, DIA_RED_APP_PROCESSING_STRING) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.setRedirectAppProcessing();
            }
        }
        else if (strcmp(tattr, DIA_ENABLE_IPV6) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.setIpv6Enabled();
            }
        }
        else if (strcmp(tattr, DIA_LOCAL_IPV6_DSCP_VAL) == 0)
        {
            if ( (RESFILE_ParseNum(*attr) >= 0) && (RESFILE_ParseNum(*attr) <= 255) )
            {
                int val = RESFILE_ParseNum(*attr);
                itsDiaConfig.setLocalIpv6DscpVal(val);
            }
            else
            {
                printf("localIpv6DscpValue range is from 0 to 255 \n");
            }
        }
        else if (strcmp(tattr, DIA_ENABLE_PEER_DISCOVERY) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.setPeerDiscoveryEnabled();
            }
        }
        else if (strcmp(tattr, DIA_ENABLE_SNAPTR_SUPPORT) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.setIsSnaptrSupportedFlag(true);
            }
        }
        else if (strcmp(tattr, DIA_DISCOVERY_INTERVAL) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                int val = RESFILE_ParseNum(*attr);
                itsDiaConfig.setDiscoveryInterval(val);
            }
        }
        else if (strcmp(tattr, DIA_DIS_STACK_INITIATED_STR) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.SetDisableStackInitiatedSTR();
            }
        }
        else if (strcmp(tattr, DIA_INTER_WORKING_MODE_STRING) == 0)
        {
            if (RESFILE_ParseNum(*attr))
            {
                itsDiaConfig.SetInterWorkingMode(true);
            }
            else
            {
                itsDiaConfig.SetInterWorkingMode(false);
            }
        }
        attr ++;
    }

    cer->setProductName(ProductName(info.GetName()));
    cea->setProductName(ProductName(info.GetName()));
    cea->setResultCode(ResultCode(ITS_DIA_SUCCESS));
    
    rfc6733CER->setProductName(ProductName(info.GetName()));
    rfc6733CEA->setProductName(ProductName(info.GetName()));
    rfc6733CEA->setResultCode(ResultCode(ITS_DIA_SUCCESS));

    DIA_GEN_CMD *gCer = (DIA_GEN_CMD *)cer;
    DIA_GEN_CMD *gCea = (DIA_GEN_CMD *)cea;

    if (gCer->getOriginStateId())
    {
        ITS_UINT &o = (ITS_UINT &)gCer->getOriginStateId()->value();
        o = itsDiaConfig.GetOriginStateId();
    }
    else if(itsDiaConfig.GetOriginStateIdOpt())
    {
        OriginStateId oid(itsDiaConfig.GetOriginStateId());
        AVPContainerDerived &avpCont = (AVPContainerDerived &)
                                       gCer->getContainer();
        avpCont.add(oid.name(), oid, false);
    }

    if(itsDiaConfig.GetOriginStateIdOpt())
    {
        OriginStateId oid(itsDiaConfig.GetOriginStateId());
        AVPContainerDerived &avpCont = (AVPContainerDerived &)
                                       rfc6733CER->getContainer();
        avpCont.add(oid.name(), oid, false);
    }

    if (gCea->getOriginStateId())
    {
        ITS_UINT &o = (ITS_UINT &)gCea->getOriginStateId()->value();
        o = itsDiaConfig.GetOriginStateId();
    }
    else if(itsDiaConfig.GetOriginStateIdOpt())
    {
        OriginStateId oid(itsDiaConfig.GetOriginStateId());
        AVPContainerDerived &avpCont = (AVPContainerDerived &)
                                       gCea->getContainer();
        avpCont.add(oid.name(), oid, false);
    }

    if(itsDiaConfig.GetOriginStateIdOpt())
    {
        OriginStateId oid(itsDiaConfig.GetOriginStateId());
        AVPContainerDerived &avpCont = (AVPContainerDerived &)
                                       rfc6733CEA->getContainer();
        avpCont.add(oid.name(), oid, false);
    }

    printf("ProductInfo: Name = %s, Version No = %d, Firmware Rev = %d\n",
           info.GetName(), info.GetVersionNo(), info.GetFirmwareRev());


}

static VendorSpecificApplicationId *venSpecAppId;

static void
HandleValue(const char *el, const char **attr)
{
    if (inLocalConfig && !inVendorSpecific)
    {
        if (strcmp(el, DIA_INSECURITY_ID_STRING) == 0)
        {
            if (strcmp(*attr, DIA_VALUE_STRING) == 0)
            {
                attr++;
                unsigned secId = RESFILE_ParseNum(*attr);
                if(secId == 0 || secId == 1)
                {
                    InbandSecurityId isId(secId);
                    ((DIA_CER *)cer)->addInbandSecurityId(isId);
                    ((DIA_CEA *)cea)->addInbandSecurityId(isId);
                     rfc6733CER->addInbandSecurityId(isId);
                     rfc6733CEA->addInbandSecurityId(isId);
                }
                else
                {
                    printf("\t--UNKNOWN value passed in InbandSecurityId-- \n");
                     printf("\t--Setting it to DEFAULT(0) value-- \n ");

                    InbandSecurityId isId(0u);
                    ((DIA_CER *)cer)->addInbandSecurityId(isId);
                    ((DIA_CEA *)cea)->addInbandSecurityId(isId);
                     rfc6733CER->addInbandSecurityId(isId);
                     rfc6733CEA->addInbandSecurityId(isId);

                }
                attr++;
            }
        }
        else if (strcmp(el, DIA_VENDOR_ID_STRING) == 0)
        {
            if (strcmp(*attr, DIA_VALUE_STRING) == 0)
            {
                attr++;
                const char *ch = *attr;
                if (strlen(ch) != 0)
                {
                    const char *str = *attr;
                    bool unknownFlag = false;

                    while(*str)
                    {
                        if(isdigit(*str))
                        {
                            str++;
                            continue;
                        }
                        else
                        {
                            unknownFlag = true;
                            printf("-->Unknown value passed in VendorId\n");
                            printf("-->Setting to default value --> 0\n");
                            break;
                        }
                    }
                    
                    if(!unknownFlag)
                    {
                        VendorId id(RESFILE_ParseNum(*attr));
                        ((DIA_CER *)cer)->setVendorId(id);
                        ((DIA_CEA *)cea)->setVendorId(id);
                        ((DIA_CER *)rfc6733CER)->setVendorId(id);
                        ((DIA_CEA *)rfc6733CEA)->setVendorId(id);
                        vendorIdPresnt = true;
                    }
                    else
                    {
                        VendorId id(0u);
                        ((DIA_CER *)cer)->setVendorId(id);
                        ((DIA_CEA *)cea)->setVendorId(id);
                        ((DIA_CER *)rfc6733CER)->setVendorId(id);
                        ((DIA_CEA *)rfc6733CEA)->setVendorId(id);
                        vendorIdPresnt = true;
                    }

                }
                attr++;
            }
        }
        else if (strcmp(el, DIA_SUPP_VENDOR_ID_STRING) == 0)
        {
            if (strcmp(*attr, DIA_VALUE_STRING) == 0)
            {
                attr++;
                SupportedVendorId sId(RESFILE_ParseNum(*attr));
                ((DIA_CER *)cer)->addSupportedVendorId(sId);
                ((DIA_CEA *)cea)->addSupportedVendorId(sId);
                ((DIA_CER *)rfc6733CER)->addSupportedVendorId(sId);
                ((DIA_CEA *)rfc6733CEA)->addSupportedVendorId(sId);

               attr++;
            }
        }
        else if (strcmp(el, DIA_AUTH_APP_ID_STRING) == 0)
        {
            bool found = false;
            if (strcmp(*attr, DIA_VALUE_STRING) == 0)
            {
                attr++;
                for (int i=0; i<((DIA_CER *)cer)->countAuthApplicationId();i++)
                {
                    if (RESFILE_ParseNum(*attr) ==
                        ((DIA_CER *)cer)->getAuthApplicationId(i).value())
                    {
                        found = true;
                        break;
                    }
                }
                if(!found)
                {
                    AuthApplicationId authAppId(RESFILE_ParseNum(*attr));
                    ((DIA_CER *)cer)->addAuthApplicationId(authAppId);
                    ((DIA_CEA *)cea)->addAuthApplicationId(authAppId);
                    ((DIA_CER *)rfc6733CER)->addAuthApplicationId(authAppId);
                    ((DIA_CEA *)rfc6733CEA)->addAuthApplicationId(authAppId);
                    /**
                     * To check for the relay advertisement, verify if the
                     * Auth AppId value is Oxffffffff.
                     */
                     if (RESFILE_ParseNum(*attr) ==
                         RESFILE_ParseNum(DIA_RELAY_APP_ID_STRING))
                     {
                         itsDiaConfig.EnableRelayAdvertisement();
                     }
                }
                attr++;
            }
        }
        else if (strcmp(el, DIA_ACCT_APP_ID_STRING) == 0)
        {
            bool found = false;
            if (strcmp(*attr, DIA_VALUE_STRING) == 0)
            {
                attr++;
                for (int i=0; i<((DIA_CER *)cer)->countAcctApplicationId();i++)
                {
                    if (RESFILE_ParseNum(*attr) ==
                        ((DIA_CER *)cer)->getAcctApplicationId(i).value())
                    {
                        found = true;
                        break;
                    }
                }
                if(!found)
                {
                    AcctApplicationId acctAppId(RESFILE_ParseNum(*attr));
                    ((DIA_CER *)cer)->addAcctApplicationId(acctAppId);
                    ((DIA_CEA *)cea)->addAcctApplicationId(acctAppId);
                    ((DIA_CER *)rfc6733CER)->addAcctApplicationId(acctAppId);
                    ((DIA_CEA *)rfc6733CEA)->addAcctApplicationId(acctAppId);
                }
                attr++;
            }
        }
    }
    else if (inLocalConfig && inVendorSpecific)
    {
        if (strcmp(el, DIA_VENDOR_ID_STRING) == 0)
        {
            if (strcmp(*attr, DIA_VALUE_STRING) == 0)
            {
                attr++;
                VendorId id(RESFILE_ParseNum(*attr));
                venSpecAppId->addVendorId(id);
                attr++;
            }
        }
        else if (strcmp(el, DIA_AUTH_APP_ID_STRING) == 0)
        {
            if (strcmp(*attr, DIA_VALUE_STRING) == 0)
            {
                attr++;
                AuthApplicationId authAppId(RESFILE_ParseNum(*attr));
                venSpecAppId->setAuthApplicationId(authAppId);
                attr++;
            }
        }
        else if (strcmp(el, DIA_ACCT_APP_ID_STRING) == 0)
        {
            if (strcmp(*attr, DIA_VALUE_STRING) == 0)
            {
                attr++;
                AcctApplicationId acctAppId(RESFILE_ParseNum(*attr));
                venSpecAppId->setAcctApplicationId(acctAppId);
                attr++;
            }
        }
    }
    else if (inPeerConfig)
    {
        ITSDiaConfig::PeerTimersConfig& pt = config->GetPeerTimers();
        if (strcmp(el, DIA_RETRANS_INTVL_STRING) == 0)
        {
            if (strcmp(*attr, DIA_VALUE_STRING) == 0)
            {
                attr++;
                pt.SetRetransIntvl(RESFILE_ParseNum(*attr));
                attr++;
            }
        }
        else if (strcmp(el, DIA_RETRANS_COUNT_STRING) == 0)
        {
            if (strcmp(*attr, DIA_VALUE_STRING) == 0)
            {
                attr++;
                pt.SetRetransCount(RESFILE_ParseNum(*attr));
                attr++;
            }
        }

    }
}


static ITS_UINT hInfCnt = 0;
static ITS_UINT trCnt = 0;


static void
StartHostInfo(const char **attr)
{
    if (inLocalConfig)
    {
        while (*attr)
        {
             const char *tattr = *attr;
             attr++;

             if (strcmp(tattr, DIA_SERV_HOST_NAME_STRING) == 0)
             {
                 if(hInfo.servHostName != NULL)
                 {
                     free((char*)hInfo.servHostName);
                     hInfo.servHostName = NULL;
                 }
                 hInfo.servHostName = strdup(*attr);
                 const char* &localHost =
                            itsDiaConfig.getLocalHostName();
                 localHost = strdup(*attr);
             }
             else if (strcmp(tattr, DIA_MATE_HOST_NAME_STRING) == 0)
             {
                const char* &mateHost =
                            itsDiaConfig.getMateHostName();
                mateHost = strdup(*attr);
             }
             else if (strcmp(tattr, DIA_REALM_NAME_STRING) == 0)
             {
                 hInfo.realmName = strdup(*attr);
                 const char* &localRealm =
                           itsDiaConfig.getLocalRealmName();
                 localRealm = strdup(*attr);
             }
             attr++;
        }
    }
}


static void
HandleTrOtherHome(const char *el, const char **attr)     // SCTP MultiHoming
{
    otherTranIPno++;

    while (*attr)
    {
        const char *tattr = *attr;
        attr++;
        if(strcmp(tattr, DIA_SERV_IP_STRING) == 0)
        {
            transIPaddrs[otherTranIPno] = strdup(*attr);
        }
        attr++;
     }
}


static void
HandleTransport(const char *el, const char **attr)
{
    while (*attr)
    {
         const char *tattr = *attr;
         attr++;

         if (strcmp(tattr, DIA_TRANS_TYPE_STRING) == 0)
         {
             if (strcmp(*attr, DIA_PORT_TYPE_TCP_STRING) == 0)
             {
                 trans.type = ITS_DIA_T_TCP;
             }
             else if (strcmp(*attr, DIA_PORT_TYPE_SCTP_STRING) == 0)
             {
                 trans.type = ITS_DIA_T_SCTP;
             }
         }
         else if ((strcmp(tattr, DIA_SERV_IP_STRING) == 0)||
                   (strcmp(tattr, DIA_PRIVATE_SERV_IP_STRING) == 0))
         {
             trans.serverIpAddr = strdup(*attr);
         }
         else if (strcmp(tattr, DIA_PORT_INFO_STRING) == 0)
         {
             trans.portNo = RESFILE_ParseNum(*attr);
         }
         else if (strcmp(tattr, DIA_SECURE_PORT_INFO_STRING) == 0)
         {
             trans.securePort = RESFILE_ParseNum(*attr);
         }
         else if (strcmp(tattr, DIA_PUBLIC_SERV_IP_STRING) == 0)
         {
             trans.publicServerIpAddr = strdup(*attr);
         }

         attr++;
    }

    if(trans.type == ITS_DIA_T_SCTP)           // SCTP MultiHoming
    {
         transIPaddrs[0] = (char *)trans.serverIpAddr;
    }

    trCnt++;
    hInfo.transCnt = trCnt;
}

static void
HandleSocketConfiguration(const char *el, const char **attr)
{
    while (*attr)
    {
        const char *tattr = *attr;
        attr++;

        if (strcmp(tattr, DIA_MAX_CONN_ATTEMPTS_STRING) == 0)
        {
            itsDiaConfig.GetStreamSocketConfig()->maxAttempts = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_MAX_IN_STREAMS_STRING) == 0)
        {
            itsDiaConfig.GetStreamSocketConfig()->maxNoOfInStreams = RESFILE_ParseNum(*attr);
        }
    	else if (strcmp(tattr, DIA_MAX_OUT_STREAMS_STRING) == 0)
    	{
    	    itsDiaConfig.GetStreamSocketConfig()->noOfOutStreams = RESFILE_ParseNum(*attr);
    	}
    	else if (strcmp(tattr, DIA_COOKIE_LIFE_TIME_STRING) == 0)
        {
            itsDiaConfig.GetStreamSocketConfig()->cookieLife = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_HEART_BEAT_ON_STRING) == 0)
        {
            if ((0 == strcmp(*attr, "yes")) || (0 == strcmp(*attr, "YES") ))
            {
                itsDiaConfig.GetStreamSocketConfig()->hbOn = true;
            }
            else
            {
                itsDiaConfig.GetStreamSocketConfig()->hbOn = false;
            }
        }
        else if (strcmp(tattr, DIA_HEART_BEAT_TIMEOUT_STRING) == 0)
        {
            itsDiaConfig.GetStreamSocketConfig()->hbTimeout = RESFILE_ParseNum(*attr);
        }
    	else if (strcmp(tattr, DIA_INIT_TIMEOUT_STRING) == 0)
        {
            itsDiaConfig.GetStreamSocketConfig()->initTimeout = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_PMTU_TIMEOUT_STRING) == 0)
        {
            char temp[20];
            const char* pStr = *attr;

            strncpy(temp, pStr, 20);
            temp[19]='\0';

            itsDiaConfig.GetStreamSocketConfig()->pmtuTimeout.tv_sec = 0;
            itsDiaConfig.GetStreamSocketConfig()->pmtuTimeout.tv_usec = 0;
            char* pSec = strtok(temp, ",");
            if (pSec != NULL)
            {
                itsDiaConfig.GetStreamSocketConfig()->pmtuTimeout.tv_sec = RESFILE_ParseNum(pSec);
            }
            char* pUSec = strtok(NULL, ",");
            if (pUSec != NULL)
            {
                itsDiaConfig.GetStreamSocketConfig()->pmtuTimeout.tv_usec = RESFILE_ParseNum(pUSec);
            }
        }
    	else if (strcmp(tattr, DIA_RECV_TIMEOUT_STRING) == 0)
        {
            char temp[20];
            const char* pStr = *attr;

            strncpy(temp, pStr, 20);
            temp[19]='\0';

            itsDiaConfig.GetStreamSocketConfig()->recvTimeout.tv_sec = 0;
            itsDiaConfig.GetStreamSocketConfig()->recvTimeout.tv_usec = 0;
            char* pSec = strtok(temp, ",");
            if (pSec != NULL)
            {
                itsDiaConfig.GetStreamSocketConfig()->recvTimeout.tv_sec = RESFILE_ParseNum(pSec);
            }
            char* pUSec = strtok(NULL, ",");
            if (pUSec != NULL)
            {
                itsDiaConfig.GetStreamSocketConfig()->recvTimeout.tv_usec = RESFILE_ParseNum(pUSec);
            }
        }
    	else if (strcmp(tattr, DIA_SEND_TIMEOUT_STRING) == 0)
        {
            char temp[20];
            const char* pStr = *attr;

            strncpy(temp, pStr, 20);
            temp[19]='\0';

            itsDiaConfig.GetStreamSocketConfig()->sendTimeout.tv_sec = 0;
            itsDiaConfig.GetStreamSocketConfig()->sendTimeout.tv_usec = 0;
            char* pSec = strtok(temp, ",");
            if (pSec != NULL)
            {
                itsDiaConfig.GetStreamSocketConfig()->sendTimeout.tv_sec = RESFILE_ParseNum(pSec);
            }
            char* pUSec = strtok(NULL, ",");
            if (pUSec != NULL)
            {
                itsDiaConfig.GetStreamSocketConfig()->sendTimeout.tv_usec = RESFILE_ParseNum(pUSec);
            }
        }
    	else if (strcmp(tattr, DIA_SHUTDOWN_TIMEOUT_STRING) == 0)
        {
            itsDiaConfig.GetStreamSocketConfig()->shutdownTimeout = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_ACK_DELAY_STRING) == 0)
        {
            itsDiaConfig.GetStreamSocketConfig()->ackDelay = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_ASOC_FAILURE_RETRY_STRING) == 0)
        {
            itsDiaConfig.GetStreamSocketConfig()->asocmaxrxt = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_RTO_MAX_STRING) == 0)
        {
            itsDiaConfig.GetStreamSocketConfig()->rtoMax = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_RTO_MIN_STRING) == 0)
        {
            itsDiaConfig.GetStreamSocketConfig()->rtoMin = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_RTO_INITIAL_STRING) == 0)
        {
            itsDiaConfig.GetStreamSocketConfig()->rtoInitial = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_SEND_BUFFER_SIZE_STRING) == 0)
        {
            itsDiaConfig.GetStreamSocketConfig()->sndBuffSize = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_RECV_BUFFER_SIZE_STRING) == 0)
        {
            itsDiaConfig.GetStreamSocketConfig()->rcvBuffSize = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_PATH_FAILURE_RETRY_STRING) == 0)
        {
            itsDiaConfig.GetStreamSocketConfig()->pathmaxrxt = RESFILE_ParseNum(*attr);
        }
        attr++;
    }
}
	
static void
HandleTcpSocketConfiguration(const char *el, const char **attr)
{
    while (*attr)
    {
        const char *tattr = *attr;
        attr++;
        if (strcmp(tattr, DIA_TCP_CONNECT_TIMEOUT_STRING) == 0)
        {
            itsDiaConfig.GetTcpSocketConfig()->connectTimeout = RESFILE_ParseNum(*attr);
        }
        attr++;
    }
}

static void
StartAuthSession(const char **attr)
{

    ITSDiaConfig::AuthSessionConfig& authCfg = config->GetAuthSessionConfig();
    if (inLocalConfig && inSessionConfig)
    {
         while (*attr)
        {
             const char *tattr = *attr;
             attr++;

             if (strcmp(tattr, DIA_SESSION_STATE_STRING) == 0)
             {
                  authCfg.SetSubType(RESFILE_ParseNum(*attr));
             }
             else if (strcmp(tattr, DIA_SESSION_TIMEOUT_STRING) == 0)
             {
                  authCfg.SetTimeout(RESFILE_ParseNum(*attr));
             }
             else if (strcmp(tattr, DIA_SESSION_LIFETIME_STRING) == 0)
             {
                  authCfg.SetLifeTime(RESFILE_ParseNum(*attr));
             }
             else if (strcmp(tattr, DIA_SESSION_GRACE_STRING) == 0)
             {
                  authCfg.SetGracePeriod(RESFILE_ParseNum(*attr));
             }
             else if (strcmp(tattr, DIA_SESSION_ABORT_RETRY_STRING) == 0)
             {
                  authCfg.SetRetryAbort(RESFILE_ParseNum(*attr));
             }
             attr++;
        }

    }
}

static void
StartAcctSession(const char **attr)
{
    ITSDiaConfig::AcctSessionConfig& acctCfg = config->GetAcctSessionConfig();
    if (inLocalConfig && inSessionConfig)
    {
         while (*attr)
        {
             const char *tattr = *attr;
             attr++;

             if (strcmp(tattr, DIA_SESSION_STATE_STRING) == 0)
             {
                  acctCfg.SetSubType(RESFILE_ParseNum(*attr));
             }
             else if (strcmp(tattr, DIA_SESSION_TIMEOUT_STRING) == 0)
             {
                  acctCfg.SetTimeout(RESFILE_ParseNum(*attr));
             }
             else if (strcmp(tattr, DIA_SESSION_INTERIM_INTVL_STRING) == 0)
             {
                  acctCfg.SetInterimIntvl(RESFILE_ParseNum(*attr));
             }
             else if (strcmp(tattr, DIA_SESSION_REALTIME_STRING) == 0)
             {
                  acctCfg.SetRealTime(RESFILE_ParseNum(*attr));
             }
             attr++;
        }
    }
}

static void
StartTrace(const char **attr)
{
    critMask = TRACE_TO_NONE;
    errMask  = TRACE_TO_NONE;
    warnMask = TRACE_TO_NONE;
    dbgMask  = TRACE_TO_NONE;
}

static void
HandleTrace(const char *el, const char **attr)
{
    int *mask = NULL;

    if (strcmp(el, DIA_CRITICAL_STRING) == 0)
    {
        mask = &critMask;
#ifdef FOR_DRE
        (eAccelero::ComponentBase::Instance().GetLogger().SetLevel(eAccelero::Logger::EACC_LOG_CRITICAL));
#endif

    }
    else if (strcmp(el, DIA_ERROR_STRING) == 0)
    {
        mask = &errMask;
#ifdef FOR_DRE
        (eAccelero::ComponentBase::Instance().GetLogger().SetLevel(eAccelero::Logger::EACC_LOG_ERROR));
#endif
    }
    else if (strcmp(el, DIA_WARNING_STRING) == 0)
    {
        mask = &warnMask;
#ifdef FOR_DRE
        (eAccelero::ComponentBase::Instance().GetLogger().SetLevel(eAccelero::Logger::EACC_LOG_WARNING));
#endif
    }
    else if (strcmp(el, DIA_DEBUG_STRING) == 0)
    {
        mask = &dbgMask;
#ifdef FOR_DRE
        (eAccelero::ComponentBase::Instance().GetLogger().SetLevel(eAccelero::Logger::EACC_LOG_DEBUG));
#endif
    }
    else
    {
        return;
    }

    while (*attr)
    {
        if (strcmp(*attr, DIA_TRACE_OUTPUT_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, ITS_STDOUT_STRING) == 0)
            {
                *mask &= ~TRACE_TO_NONE;
                *mask |= TRACE_TO_DISPLAY;
            }
            else if (strcmp(*attr, ITS_SYSLOG_STRING) == 0)
            {
                *mask &= ~TRACE_TO_NONE;
                *mask |= TRACE_TO_SYSLOG;
            }
            else if (strcmp(*attr, ITS_FILE_STRING) == 0)
            {
                *mask &= ~TRACE_TO_NONE;
                *mask |= TRACE_TO_FILE;
            }
            else
            {
                *mask = TRACE_TO_NONE;
#ifdef FOR_DRE
                (eAccelero::ComponentBase::Instance().GetLogger().SetLevel(eAccelero::Logger::EACC_LOG_FATAL));
#endif
            }

            attr++;
        }
        else
        {
            attr += 2;
        }
    }
}


static void
HandleTimer(const char **attr)
{
    ITSDiaConfig::PeerTimersConfig& pt = config->GetPeerTimers();
    const char *name = NULL, *value = NULL;
    while (*attr)
    {
        if (strcmp(*attr, DIA_NAME_STRING) == 0)
        {
            attr++;

            name = *attr;

            attr++;
        }
        else if (strcmp(*attr, DIA_VALUE_STRING) == 0)
        {
            attr++;

            value = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    if (name)
    {
        if (strcmp(name, DIA_TIMER_EXPIRY_STRING) == 0)
        {
            pt.SetExpiry(RESFILE_ParseNum(value));
        }
        else if (strcmp(name, DIA_TIMER_RETRY_STRING) == 0)
        {
            pt.SetRetry(RESFILE_ParseNum(value));
        }
        else if (strcmp(name, DIA_TIMER_WATCHDOG_STRING) == 0)
        {
            pt.SetWatchdog(RESFILE_ParseNum(value));
        }
    }
}

PEER_ENTRY *pEntry = NULL;

static void
StartPeer(const char **attr)
{
    if (inPeerConfig)
    {
        pEntry = (PEER_ENTRY *)malloc(sizeof(PEER_ENTRY));
        ITSDiaConfig::PeerTimersConfig& pt = config->GetPeerTimers();
        if (pEntry == NULL)
        {
            //throw Error - malloc failed
            throw "Error: Malloc failed";
        }

        memset(pEntry, 0, sizeof(PEER_ENTRY));
        DIA_PE_DW_TIME_VAL(pEntry)=pt.GetWatchdog();
        DIA_PE_RETRY_TIME_VAL(pEntry) = pt.GetRetry();
        DIA_PE_EXPIRY_TIMER(pEntry) = pt.GetExpiry();

        if (itsDiaConfig.GetInitiateConnsOpt())
        {
            DIA_PE_INIT_CONN(pEntry) = true;
        }

        while (*attr)
        {
             const char *tattr = *attr;
             attr++;

             if (strcmp(tattr, DIA_SERV_HOST_NAME_STRING) == 0)
             {
                 DIA_PE_HOST(pEntry) = strdup(*attr);
             }
             else if (strcmp(tattr, DIA_REALM_NAME_STRING) == 0)
             {
                 DIA_PE_REALM(pEntry) = strdup(*attr);
             }
             else if (strcmp(tattr, DIA_TLS_ENABLED_STRING) == 0)
             {
#ifdef TLS_ENABLED
                 if (strcmp(*attr, "yes") == 0)
                 {
                     DIA_PE_TLS_EN(pEntry) = ITS_TRUE;
                 }
                 else
                 {
                     DIA_PE_TLS_EN(pEntry) = ITS_FALSE;
                 }
#else

                 DIA_PE_TLS_EN(pEntry) = ITS_FALSE;
#endif
             }
             else if (strcmp(tattr, DIA_DSCP_ENABLED_STRING) == 0)
             {
                 if (strcmp(*attr, "yes") == 0)
                 {
                     DIA_PE_DSCP_EN(pEntry) = ITS_TRUE;
                 }
                 else
                 {
                     DIA_PE_DSCP_EN(pEntry) = ITS_FALSE;
                 }
             }

             attr++;
             DIA_PE_STATIC(pEntry) = ITS_TRUE;
        }
        DIA_PE_STATE(pEntry) = PEER_ST_CLOSED;
        DIA_PE_FSM(pEntry) = new PeerFsm();

        if (MUTEX_CreateMutex(&DIA_PE_MUX(pEntry), 0) != ITS_SUCCESS)
        {
            throw its::Error(ITS_EBADMUTEX, __FILE__, __LINE__);
        }

    }
}

static void
HandleDisconnectCauseSupport(const char *el, const char **attr)
{
    while (*attr)
    {
        const char *tattr = *attr;
        attr++;
        if (strcmp(tattr, DIA_TIMER_BUSY_RECONNECT_STRING) == 0)
        {
            DIA_PE_BUSY_RECONNECT_TIMER(pEntry) = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_TIMER_DO_NOT_WANT_TO_TALK_TO_YOU_STRING) == 0)
        {
            DIA_PE_DO_NOT_WANT_TO_TALK_TO_YOU_RECONNECT_TIMER(pEntry) = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_DISCONNECT_CAUSE_SUPPORT_ENABLE) == 0)
        {
            cout<<"Entring"<<endl;
            if (strcmp(*attr, "yes") == 0)
            {
                DIA_PE_DISCONNECT_CAUSE_SUPPORT(pEntry) = true;
            }
            else
            {
                DIA_PE_DISCONNECT_CAUSE_SUPPORT(pEntry) = false;
            }
            cout<<"Leaving"<<endl;

        }
    }
}



static void
HandlePeerTransport(const char *el, const char **attr)
{
    ITS_USHORT port = 0;;
    ITS_USHORT securePort = 0;
    DIA_TRANS_TYPE type = ITS_DIA_T_INAVLID;
    const char * ipAddr = NULL;
    while (*attr)
    {
        const char *tattr = *attr;
        attr++;

        if (strcmp(tattr, DIA_TRANS_TYPE_STRING) == 0)
        {
            if (strcmp(*attr, DIA_PORT_TYPE_TCP_STRING) == 0)
            {
                type = ITS_DIA_T_TCP;
            }
            else if (strcmp(*attr, DIA_PORT_TYPE_SCTP_STRING) == 0)
            {
                type = ITS_DIA_T_SCTP;
            }
        }
        else if (strcmp(tattr, DIA_SERV_IP_STRING) == 0)
        {
            ipAddr = *attr;
        }
        else if (strcmp(tattr, DIA_PORT_INFO_STRING) == 0)
        {
            port = RESFILE_ParseNum(*attr);
        }
        else if(strcmp(tattr, DIA_SECURE_PORT_INFO_STRING) == 0)
        {
            securePort = RESFILE_ParseNum(*attr);
        }
        attr++;
    }
    if(type != ITS_DIA_T_INAVLID &&(port !=0 || securePort !=0))
    {
        DT_DBG(("Add peer %s with transport %d and port %d and tls port %d",
                    DIA_PE_HOST(pEntry),type,port,securePort));
        int index = 0;
        if(type == ITS_DIA_T_TCP)
        {
            if(securePort != 0)
            {
                DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr = strdup(ipAddr);
                DIA_PE_CONN_TINFO_INDEX(pEntry,index).securePort = securePort;
                DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = (DIA_TRANS_TYPE)(type);
                index++;
            }
        }
        if(port !=0)
        {
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr = strdup(ipAddr);
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).portNo = port;
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = (DIA_TRANS_TYPE)(type);
            if (DIA_PE_CONN_TINFO_INDEX(pEntry,index).type == ITS_DIA_T_SCTP)
            {
                DIA_PE_CONN_TINFO_INDEX(pEntry,index).multiHomeipaddrs[0] =
                    DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr;
                DIA_PE_CONN_TINFO_INDEX(pEntry,index).noIPs = 1;
                peerIPaddrs = DIA_PE_CONN_TINFO_INDEX(pEntry,index).multiHomeipaddrs;
            }
            index++;
        }
        DIA_PE_CONN_TRANS_COUNT(pEntry) = index;
    }
    else if(type != ITS_DIA_T_INAVLID &&(port == 0 && securePort ==0))
    {
        int index = 0;
        if(type == ITS_DIA_T_TCP)
        {
            DT_DBG(("Add peer %s with transport %d and default port %d and default tls port %d",
                        DIA_PE_HOST(pEntry),type,DEFAULT_TCP_OR_SCTP_PORT,DEFAULT_TLS_OR_DTLS_PORT));
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr = strdup(ipAddr);
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).securePort = DEFAULT_TLS_OR_DTLS_PORT;
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = (DIA_TRANS_TYPE)(type);
            index++;
        }
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr = strdup(ipAddr);
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).portNo = DEFAULT_TCP_OR_SCTP_PORT;
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = (DIA_TRANS_TYPE)(type);
        if (DIA_PE_CONN_TINFO_INDEX(pEntry,index).type == ITS_DIA_T_SCTP)
        {
            DT_DBG(("Add peer %s with transport %d and default port %d",
                        DIA_PE_HOST(pEntry),type,DEFAULT_TCP_OR_SCTP_PORT));
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).multiHomeipaddrs[0] =
                DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr;
            peerIPaddrs = DIA_PE_CONN_TINFO_INDEX(pEntry,index).multiHomeipaddrs;
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).noIPs = 1;
        }
        index++;
        DIA_PE_CONN_TRANS_COUNT(pEntry) = index;
    }
    else
    {
        DT_DBG(("Add peer %s with default transport info",DIA_PE_HOST(pEntry)));
        int index = 0;
        //minus since DTLS is not supported
        for(int i =0;i<(MAX_TRANS_PER_LIST-1);i++)
        {
            DIA_PE_CONN_TINFO_INDEX(pEntry,i).serverIpAddr = strdup(ipAddr);
        }
        //configure trsnport in the order TLS,DTLS,TCP and SCTP
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).securePort = DEFAULT_TLS_OR_DTLS_PORT;
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = ITS_DIA_T_TCP;
        index++;

        //DIA_PE_CONN_TINFO_INDEX(pEntry,ndex).securePort = DEFAULT_TLS_OR_DTLS_PORT;
        //DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = DIA_TRANS_SCTP;
        //index++
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).portNo = DEFAULT_TCP_OR_SCTP_PORT;
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = ITS_DIA_T_TCP;
        index++;

        DIA_PE_CONN_TINFO_INDEX(pEntry,index).portNo = DEFAULT_TCP_OR_SCTP_PORT;
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = ITS_DIA_T_SCTP;
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).multiHomeipaddrs[0] =
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr;
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).noIPs = 1;
        index++;

        DIA_PE_CONN_TRANS_COUNT(pEntry) = index;
    }

}

static void
HandleDscpValue(const char *el, const char **attr)
{
    while (*attr)
    {
        const char *tattr = *attr;
        attr++;

        if (strcmp(tattr, DIA_VALUE_STRING) == 0)
        {
            if ( (RESFILE_ParseNum(*attr) >= 0) && (RESFILE_ParseNum(*attr) <= 255) )
            {
            	DIA_PE_DSCP_VAL(pEntry) = RESFILE_ParseNum(*attr);
            }
            else
            {
                DT_WRN(("DSCP Value Range is from 0 - 255 "));
            }
        }
        attr++;
    }
}

static void
DTFConfigValue(const char *el, const char **attr)
{
    while (*attr)
    {
        const char *tattr = *attr;
        attr++;

        if (strcmp(*attr, DIA_TRANSFORMATION_VALUE) == 0)
        {
            config->setDTFEnabled(true);
            DT_WRN(("Config for Transformation is %d",config->IsDTFEnabled()));
        }
        else
        {
            config->setDTFEnabled(false);
            DT_WRN(("Config for Transformation is %d",config->IsDTFEnabled()));
        }
        attr++;
    }
}

static void HandlePlugins(const char *el, const char **attr)
{

	while (*attr)
	{
        const char *tattr = *attr;
        attr++;

		if ((strcmp(tattr, DIA_PLUGIN_NAME) == 0))
		{
                        //Fixing Resource leak
			plugin.pluginName.assign(*attr);
		}
		else if((strcmp(tattr, DIA_DICT_1) == 0))
		{
                        //Fixing Resource leak
			plugin.dictId1.assign(*attr);
		}
		else if ((strcmp(tattr, DIA_DICT_2) == 0))
		{
                        //Fixing Resource leak
			plugin.dictId2.assign(*attr);
		}
		else if((strcmp(tattr, DIA_CONFIG) == 0))
		{
                        //Fixing Resource leak
			plugin.config.assign(*attr);
		}

		attr++;
	}

	itsDiaConfig.PopulateTransformPlugin(plugin);

}

static void
HandleDictionaryID(const char *el, const char **attr)
{
    while (*attr)
    {
        const char *tattr = *attr;
        attr++;

        if (strcmp(el, DIA_DICTIONARY_ID_STRING) == 0)
        {
            if(pEntry->dictCount < MAX_DICT_IDS_PER_PEER) {
                DIA_PE_DICTIONARY_ID(pEntry,pEntry->dictCount) = RESFILE_ParseNum(*attr);
                pEntry->dictCount++;
            }
            else {
                DT_WRN(("DICTIONARY Id Reached max size[%d]", pEntry->dictCount));
            }
        }
        attr++;
    }
}

#ifdef TLS_ENABLED
static void HandleCAs(const char **attr)
{
    its::CertificateAuthority *cauObj = new its::CertificateAuthority;
    CRL crl;
    while(*attr && inSecurityConfig && inTrustedCAs)
    {
        const char *tattr = *attr;
        attr++;
        string strObj;

        if (strcmp(tattr, DIA_TRUST_FILE) == 0)
        {
            //Fixing Resource Leak
            //strObj = strdup(*attr);
            strObj.assign(*attr);
            cauObj->SetCertificateFileName(strObj);
        }
        if (strcmp(tattr, DIA_CERT_TYPE) == 0)
        {
            if(strcmp(*attr, DIA_PEM) == 0)
            {
                cauObj->SetCertType(its::CertificateAuthority::CERT_TYPE_PEM);
            }

            else if(strcmp(*attr, DIA_DER) == 0)
            {
                cauObj->SetCertType(its::CertificateAuthority::CERT_TYPE_DER);
            }
        }
        if (strcmp(tattr, DIA_CRL_FILE) == 0)
        {
            //strObj = strdup(*attr);
            strObj.assign(*attr);
            crl.SetCRLFileName(strObj);
            cauObj->SetCRL(crl);
        }

        attr ++;
    }
    
    config = &itsDiaConfig;
    ITSDiaConfig::SecurityConfig& secConf = config->GetSecurityConfig();
    secConf.AddTrustedCA(cauObj);
}
#endif

STATIC_ROUTE_ENTRY *staticRouteEntry = NULL;

static void StartStaticRoute(const char **attr)
{
    if(inStaticRoutingConfig)
    {
       staticRouteEntry = new STATIC_ROUTE_ENTRY;

       while (*attr)
       {
           const char *tattr = *attr;
           attr++;
           if (strcmp(tattr, DIA_DESTINATION_HOST) == 0)
           {
               staticRouteEntry->destinationHostName = (*attr);
           }
           else if (strcmp(tattr, DIA_DESTINATION_REALM) == 0)
           {
               staticRouteEntry->realmName = (*attr);
           }
           else if (strcmp(tattr, DIA_PEER) == 0)
           {
               staticRouteEntry->peerName = (*attr);
           }
           else if (strcmp(tattr, DIA_APPLICATION_ID) == 0)
             {
               staticRouteEntry->appId = RESFILE_ParseNum(*attr);
           }
           else if(strcmp(tattr,DIA_PRIORITY) == 0)
           {
               staticRouteEntry->priority = RESFILE_ParseNum(*attr);
           }
           attr++;
       }
       STATIC_ROUTING_TABLE->InsertEntry(staticRouteEntry);
    }
}

#ifdef TLS_ENABLED
static void HandleCipherSuites(const char **attr)
{
    std::string cipherName;

    while(*attr && inSecurityConfig && inTlsCipherSuites)
    {

        const char *tattr = *attr;
        attr++;

        if (strcmp(tattr, DIA_NAME_STRING) == 0)
        {
            //Fixing Resource leak
            cipherName.assign(*attr);
        }
        attr++;
     }

     config = &itsDiaConfig;
     ITSDiaConfig::SecurityConfig& secConf = config->GetSecurityConfig();
     secConf.PopulateCipherList(cipherName);
}

static void HandleSetCrlPath(const char **attr)
{
    if(inSecurityConfig)
    {
        if(strcmp(*attr, DIA_PATH) == 0)
        {
            config = &itsDiaConfig;
            ITSDiaConfig::SecurityConfig& secConf = config->GetSecurityConfig();
            secConf.SetCrlPath(*(++attr));
        }
        else
        {
            DT_ERR(("Invalid input in XML!"));
        }
    }
}

static void HandleSetCrlVerification(const char **attr)
{
    if(inSecurityConfig)
    {
        config = &itsDiaConfig;
        ITSDiaConfig::SecurityConfig& secConf = config->GetSecurityConfig();

        if(strcmp(*attr, DIA_ENABLE) == 0)
        {
            attr++;

            //Fixing leak
            //if(strcmp(strdup(*attr), "yes") == 0)
            if(strcmp(*attr, "yes") == 0)
            {
                secConf.SetCrlVerify(true);
            }
            else
            {
                secConf.SetCrlVerify(false);
            }
        }
     }
}

static void SetOwnCertPath(const char **attr)
{
    if(inSecurityConfig)
    {
        config = &itsDiaConfig;
        ITSDiaConfig::SecurityConfig& secConf = config->GetSecurityConfig();
        if(strcmp(*attr, DIA_PATH) ==0)
        {
            attr++;
            secConf.SetOwnCertPath(strdup(*attr));
        }
    }
}
#endif
static void TlsEnable(const char **attr)
{
    config = &itsDiaConfig;
    if(strcmp(*attr, DIA_VALUE_STRING) == 0 )
    {
        attr++;
        if(strcmp(*attr,DIA_YES_STRING) == 0 )
        {
            config->setTlsEnable(true);
        }
        else
        {
            config->setTlsEnable(false);
        }
    }
}

static void IsPredectiveLoopEnable(const char **attr)
{
    config = &itsDiaConfig;
    if(strcmp(*attr, DIA_VALUE_STRING) == 0 )
    {
        attr++;
        if(strcmp(*attr,DIA_YES_STRING) == 0 )
        {
            config->setPredectiveLoopAvoidanceEnable(true);
        }
        else
        {
            config->setPredectiveLoopAvoidanceEnable(false);
        }
    }
}

static void
HandlePeerOtherHome(const char *el, const char **attr)         // SCTP MultiHoming
{
    otherPeerIPno++;

     while (*attr)
     {
         const char *tattr = *attr;
         attr++;
         if(strcmp(tattr, DIA_SERV_IP_STRING) == 0)
         {
              peerIPaddrs[otherPeerIPno] = strdup(*attr);
         }
         attr++;
     }
}



REALM_ENTRY *rEntry = NULL;

static void
StartRoute(const char **attr)
{
    if (inRealmConfig)
    {
        rEntry = (REALM_ENTRY *)malloc(sizeof(REALM_ENTRY));
        if (rEntry == NULL)
        {
            //throw Error - malloc failed
            throw "Error: Malloc failed";
        }

        memset(rEntry, 0, sizeof(REALM_ENTRY));
        rEntry->isDefault = ITS_FALSE;

        while (*attr)
        {
             const char *tattr = *attr;
             attr++;

             if (strcmp(tattr, DIA_REALM_NAME_STRING) == 0)
             {
                 rEntry->realmName = strdup(*attr);
             }
             else if (strcmp(tattr, DIA_LOCAL_ACTION_STRING) == 0)
             {
                 if (strcmp(*attr, DIA_LA_LOCAL_STRING) == 0)
                 {
                     rEntry->localAction = ITS_DIA_LOCAL;
                 }
                 else if (strcmp(*attr, DIA_LA_RELAY_STRING) == 0)
                 {
                     rEntry->localAction = ITS_DIA_RELAY;
                 }
                 else if (strcmp(*attr, DIA_LA_PROXY_STRING) == 0)
                 {
                     rEntry->localAction = ITS_DIA_PROXY;
                 }
                 else if (strcmp(*attr, DIA_LA_REDIRECT_STRING) == 0)
                 {
                     rEntry->localAction = ITS_DIA_REDIRECT;
                 }
             }
             else if (strcmp(tattr, DIA_PROXY_INFO_AVP_EN_STRING) == 0)
             {
                 if (strcmp(*attr, "yes") == 0)
                 {
                     rEntry->proxyInfoAvpEnabled = ITS_TRUE;
                 }
                 else
                 {
                     rEntry->proxyInfoAvpEnabled = ITS_FALSE;
                 }
             }
             else if (strcmp(tattr, DIA_DEFAULT_STRING) == 0)
             {
                 if (strcmp(*attr, "yes") == 0)
                 {
                     rEntry->isDefault = ITS_TRUE;
                 }
                 else
                 {
                     rEntry->isDefault = ITS_FALSE;
                 }
             }
             else if (strcmp(tattr, DIA_RED_HOST_USAGE_AVP_STRING) == 0)
             {
                 unsigned int rdUsage = RESFILE_ParseNum(*attr);
                 if (rdUsage <= MAX_USG)
                 {
                     rEntry->redirectUsage = rdUsage;
                 }
                 else
                 {
                     DT_ERR(("Redirect Usage :: Invalid Configuration"));
                 }
             }
             else if (strcmp(tattr, DIA_RED_MAX_CACHE_TIME_AVP_STRING) == 0)
             {
                 rEntry->redMaxCacheTime = RESFILE_ParseNum(*attr);
             }
             attr++;
             rEntry->isStatic = ITS_TRUE;
        }
        if (rEntry->localAction != ITS_DIA_RELAY &&
            rEntry->proxyInfoAvpEnabled == ITS_TRUE)
        {
            rEntry->proxyInfoAvpEnabled = ITS_FALSE;
            DT_ERR(("Invalid Configuration:"));
            DT_ERR(("Cannot add Proxy-Info AVP when localAction is " \
                    "LOCAL or PROXY or REDIRECT\n"));
        }
    }
}

static ITS_UINT rDstCnt = 0;

static void
StartDestination(const char **attr)
{
    /* check destination count before inserting */
    int appId = 0;
    int vendId = 0;
    int priority = 0;
    PEER_ENTRY *pEntry;
    char *peerName = NULL;
    char *realmName = NULL;
    bool isRedirectAgent = false;

    if (rDstCnt >= MAX_LIST_SIZE)
    {
        DT_WRN(("Add Destination Failed. Maximum No of Destination per realm is %d",
                                                                      MAX_LIST_SIZE));
        while (*attr)
        {
            attr++;
        }
        return;
    }

    while (*attr)
    {
         const char *tattr = *attr;
         attr++;

         if (strcmp(tattr, DIA_PEER_NAME_STRING) == 0)
         {
	     //Fixing Resource leak
             if (peerName != NULL)
             {
	        free(peerName);
		peerName = NULL;
	     }//End of if 
             peerName = strdup(*attr);
         }
         else if (strcmp(tattr, DIA_REALM_NAME_STRING) == 0)
         {
	     //Fixing Resource leak
             if (realmName != NULL)
             {
	        free(realmName);
		realmName = NULL;
	     }//End of if 
             realmName = strdup(*attr);
         }
         else if (strcmp(tattr, DIA_APPLICATION_ID_STRING) == 0)
         {
             appId = RESFILE_ParseNum(*attr);
         }
         else if (strcmp(tattr, DIA_DEST_VENDOR_ID_STRING) == 0)
         {
             vendId = RESFILE_ParseNum(*attr);
         }
         else if (strcmp(tattr, DIA_PRIORITY_STRING) == 0)
         {
             priority = RESFILE_ParseNum(*attr);
         }
         else if (strcmp(tattr, DIA_IS_REDIRECT_AGENT) == 0)
         {
             if ( strcmp(*attr, DIA_YES_STRING) == 0 )
             {
                 if ( rDstCnt == 0 )
                 {
                     isRedirectAgent = true;
                 }
                 else
                 {
                     DT_ERR(("Invalid Configuration of Redirect Agent::" \
                             "Only one destination allowed"));
                 }
             }
         }
         attr++;
    }

    bool found = false;
    if (peerName != NULL)
    {
        if (realmName != NULL)
        {
            found = PEER_TABLE->FindEntry(peerName, realmName, pEntry);
        }
        else
        {
            found = PEER_TABLE->FindEntry(peerName,rEntry->realmName, pEntry);
        }

        if (found)
        {
            if (RealmTable::InsertDestination(rEntry, pEntry, appId, vendId, priority) == ITS_SUCCESS)
            {
                if (isRedirectAgent)
                {
                    rEntry->destSpecs[rDstCnt].isRedirectAgent = true;
                    if ( DIA_PE_PENDING_Q(pEntry) == NULL )
                    {
                        DIA_PE_PENDING_Q(pEntry) = new PendingQ();
                    }
                }
                rDstCnt++;
            }
            else
            {
                DT_ERR(("Destination Entry already Exist for this peer"));
                DT_ERR(("for same App Id & Vendor Id in this realm"));
            }
        }
        else
        {
            if (rEntry->localAction == ITS_DIA_REDIRECT )
            {
                rEntry->destSpecs[rDstCnt].redirectHost  = strdup(peerName);
                DT_DBG(("Local Action::Redirect : Destination Added:: %s", peerName));
                rDstCnt++;
            }
            else
            {
                DT_WRN(("Invalid Peer Name %s in Destination: Discarding", peerName));
            }
        }
    }
    else
    {
        DT_ERR(("Invalid Configuration: Discarding"));
    }

    if (peerName)
    {
        free(peerName);
        peerName = NULL;
    }

    if (realmName)
    {
        free(realmName);
        realmName = NULL;
    }
}

static void
StartFailover(const char **attr)
{
  while(*attr)
  {
    const char *tattr = *attr;
    attr++;

    if (strcmp(tattr, DIA_ENABLE_STRING) == 0)
    {
        if (strcmp(*attr, DIA_YES_STRING) == 0)
        {
            isFailover = ITS_TRUE;
            if (pEntry)
            {
                DIA_PE_PENDING_Q(pEntry) = new PendingQ();
            }
        }
        else
        {
            DIA_PE_PENDING_Q(pEntry) = NULL;
        }
    }
    else if(strcmp(tattr, DIA_ENABLE_FAILBACK_STRING) == 0)
    {
        if (strcmp(*attr, DIA_YES_STRING) == 0)
        {
           isFailback = ITS_TRUE;
        }
    }

  }

}

static void
HandleAlternatePeer(const char **attr)
{
    char* hostId    = NULL;
    char* hostRealm = NULL;
    while(*attr)
    {
        const char *tattr = *attr;
        attr++;

        if (strcmp(tattr, DIA_SERV_HOST_NAME_STRING) == 0)
        {
           //Fixing Resource leak
           if (hostId != NULL)
           {
              free(hostId);
              hostId = NULL;
           }//End of if
           hostId   = strdup(*attr);
        }
        else if (strcmp(tattr, DIA_REALM_NAME_STRING) == 0)
        {
           //Fixing Resource leak
           if (hostRealm != NULL)
           {
              free(hostRealm);
              hostRealm = NULL;
           }
           hostRealm = strdup(*attr);
        }
        else if (strcmp(tattr, DIA_ISMATE_STRING) == 0)
        {
           if (strcmp(*attr, DIA_YES_STRING) == 0)
           {
              isRedundantMate = ITS_TRUE;
           }
        }
        attr++;
    }
    if (pEntry && (isFailover || isRedundantMate))
    {
       DIA_PE_ALT_HOST(pEntry)  = hostId;
       DIA_PE_ALT_REALM(pEntry) = hostRealm;
       DIA_PEER_CHK_IS_FAILOVER_ENABLED(pEntry) = isFailover;
       DIA_PEER_CHK_IS_FAILBACK_ENABLED(pEntry) = isFailback;
       DIA_PEER_CHK_IF_REDUNDANT_MATE(pEntry) = isRedundantMate;
    }
    else
    {
       free(hostId);
       free(hostRealm);
    }
}
static void
HandleQueueMgmt(const char **attr)
{
    ITSDiaConfig::QueueMgmt& st = config->GetQueueMgmt();
    char* hostId    = NULL;
    char* hostRealm = NULL;
    while(*attr)
    {
        const char *tattr = *attr;
        attr++;

        if (strcmp(tattr, DIA_ENABLE_STRING) == 0)
        {
           if (strcmp(*attr, DIA_YES_STRING) == 0)
           {
              config->EnableQueueMgmt();
           }

        }
        else if (strcmp(tattr, DIA_NUM_DOWNSTREAM_THREADS) == 0)
        {
           if(config->IsQueueMgmtEnabled())
           {
               if (RESFILE_ParseNum(*attr))
               {
                   st.SetDownStreamThreadCount(RESFILE_ParseNum(*attr));
               }
           }
        }
        else if (strcmp(tattr, DIA_NUM_UPSTREAM_THREADS) == 0)
        {
           if(config->IsQueueMgmtEnabled())
           {
               if (RESFILE_ParseNum(*attr))
               {
                   st.SetUpStreamThreadCount(RESFILE_ParseNum(*attr));
               }
           }
        }
        else if (strcmp(tattr, DIA_NUM_OF_MSG_ROUTER_THREADS) == 0)
        {
            if(config->IsQueueMgmtEnabled())
            {
                if (RESFILE_ParseNum(*attr))
                {
                    int val = RESFILE_ParseNum(*attr);
                    if (val <= MAX_ROUTER_THREADS && val != MIN_ROUTER_THREADS)
                    {
                        st.SetMsgRouterThreadCount(val);
                    }
                    else
                    {
                        DT_WRN(("Single Queue enabled"));
                        config->DisableQueueMgmt();
                    }

                }
            }
        }

        attr++;
    }
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles the TLS Security related configuration.
 *  Input Parameters:
 *      attr:  Address of string
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef TLS_ENABLED
static void
HandleSecurity(const char** attr)
{
    config = &itsDiaConfig;
    ITSDiaConfig::SecurityConfig& secConf = config->GetSecurityConfig();

    /* parse the attributes */
    while (*attr && inSecurityConfig)
    {
        const char *tattr = *attr;
        attr ++;
        if (strcmp(tattr, DIA_TLS_TYPE_STRING) == 0)
        {
            if (strcmp(*attr, DIA_TLS_TYPE_GNU_STRING) ==0)
            {
                secConf.SetTlsType(GNUTLS);
            }
            else if (strcmp(*attr, DIA_TLS_TYPE_OPENSSL_STRING) ==0)
            {
                secConf.SetTlsType(OPENSSL);
            }
            else
            {
                DT_WRN(("Discarding Security Configuration: Invalid" \
                        "TLS Type"));
            }
        }
        else if (strcmp(tattr, DIA_TLS_TRACE_LEVEL_STRING) == 0)
        {
            secConf.SetTLSTraceLevel(RESFILE_ParseNum(*attr));
        }
        else if (strcmp(tattr, DIA_IDENTITY_VERIFICATION_STRING) == 0)
        {
            if (strcmp(*attr,  "yes") == 0)
            {
                secConf.SetIdentityVerifyEnabled();
            }
            else
            {
                secConf.SetIdentityVerifyDisabled();
            }
        }
        else if (strcmp(tattr, DIA_CIPHER_SUITE_STRING) == 0)
        {
            DIA_CIPHER_SUITE ciphSuite = TLS_NO_CIPHER_SUITE;
            if (strcmp(*attr, DIA_CIPHER_RSA_RC4_MD5_STRING) == 0)
            {
                ciphSuite = TLS_RSA_WITH_RC4_128_MD5;
            }
            else if (strcmp(*attr, DIA_CIPHER_RSA_RC4_SHA_STRING) == 0)
            {
                ciphSuite = TLS_RSA_WITH_RC4_128_SHA;
            }
            else if (strcmp(*attr, DIA_CIPHER_RSA_3DESEDECBC_SHA_STRING) == 0)
            {
                ciphSuite = TLS_RSA_WITH_3DES_EDE_CBC_SHA;
            }
            else
            {
               DT_WRN(("Discarding Security configuration: Invalid value for" \
                       "Cipher suite"));
               break;
            }
            secConf.SetCipherSuite(ciphSuite);
        }
        else if (strcmp(tattr, DIA_CERTIFICATE_TYPE_STRING) == 0)
        {
            if (strcmp(*attr, DIA_CERTIFICATE_X_509_STRING) ==0)
            {
                secConf.SetCertificateType(ITS_X509);
            }
            else
            {
                DT_WRN(("Discarding Security Configuration: Invalid value for" \
                        "Certificate Type"));
                break;
            }
        }
        else if (strcmp(tattr, DIA_CL_CERTIFICATE_FILE_STRING) == 0)
        {
            secConf.SetClientCertFile(*attr);
        }
        else if (strcmp(tattr, DIA_CL_KEY_FILE_STRING) == 0)
        {
            secConf.SetClientKeyFile(*attr);
        }
        else if (strcmp(tattr, DIA_SER_CERTIFICATE_FILE_STRING) == 0)
        {
            secConf.SetServCertFile(*attr);
        }
        else if (strcmp(tattr, DIA_SER_KEY_FILE_STRING) == 0)
        {
            secConf.SetServKeyFile(*attr);
        }
        else if (strcmp(tattr, DIA_TLS_CA_PATH) == 0)
        {
            secConf.SetCAPath(*attr);
        }
        else
        {
            DT_ERR(("Invalid Input in the xml"));
        }

        attr ++;
    }
}
#endif
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Xml parser element start function
 *
 *  Input Parameters:
 *      data - dunno
 *      el - the element
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
ElementStart(void *data, const char *el, const char **attr)
{
    if (strcmp(el, DIA_STRING) == 0)
    {
        HandleDiaStack(attr);
    }
    else if (strcmp(el, DIA_LOCAL_STRING) == 0)
    {
        inLocalConfig = ITS_TRUE;
    }
    else if (strcmp(el, DIA_INSECURITY_ID_STRING) == 0)
    {
        isInband = ITS_TRUE;
        HandleValue(el, attr);
    }
    else if (strcmp(el, DIA_VENDOR_ID_STRING) == 0)
    {
        isVendorId = ITS_TRUE;
        HandleValue(el, attr);
    }
    else if (strcmp(el, DIA_SUPP_VENDOR_ID_STRING) == 0)
    {
        isSupported = ITS_TRUE;
        HandleValue(el, attr);
    }
    else if (strcmp(el, DIA_AUTH_APP_ID_STRING) == 0)
    {
        isAuthId = ITS_TRUE;
        HandleValue(el, attr);
    }
    else if (strcmp(el, DIA_ACCT_APP_ID_STRING) == 0)
    {
        isAccounting = ITS_TRUE;
        HandleValue(el, attr);
    }
    else if (strcmp(el, DIA_VENDOR_SPEC_APP_ID_STRING) == 0)
    {
        venSpecAppId = new VendorSpecificApplicationId();
        inVendorSpecific = ITS_TRUE;
    }
    else if (strcmp(el, DIA_HOST_INFO_STRING) == 0)
    {
        inHostInfo = ITS_TRUE;
        trCnt = 0;

        memset(&hInfo, 0, sizeof(DIA_HOST_INFO));
        StartHostInfo(attr);
    }
    else if (strcmp(el, DIA_TRANS_STRING) == 0)
    {
        if (inLocalConfig)
        {
            memset(&trans,0,sizeof(trans));
            HandleTransport(el, attr);
        }
        else if (inPeerConfig)
        {
            HandlePeerTransport(el, attr);
        }
    }
    else if (strcmp(el, DIA_PEER_DISCONNECT_CAUSE_SUPPORT) == 0)
    {
        if (inPeerConfig)
        {
            HandleDisconnectCauseSupport(el, attr);
        }
    }
    else if (strcmp(el, DIA_TCP_SOCK_CONFIG_DATA_STRING) == 0) //TCP configuration
    {
        if (inHostInfo)
        {
            HandleTcpSocketConfiguration(el, attr);
        }
    }
    else if (strcmp(el, DIA_SOCK_CONFIG_DATA_STRING) == 0)
    {
        if (inLocalConfig)
        {
            HandleSocketConfiguration(el, attr);
        }
    }
    else if (strcmp(el, DIA_OTHERHOME_STRING) == 0)           // SCTP MultiHoming
    {
        if (inLocalConfig)
        {
            HandleTrOtherHome(el, attr);
        }
        else if (inPeerConfig)
        {
            HandlePeerOtherHome(el, attr);
        }
    }
    else if (strcmp(el, DIA_SESSION_CFG_STRING) == 0)
    {
        inSessionConfig = ITS_TRUE;
    }
    else if (strcmp(el, DIA_SESSION_AUTH_STRING) == 0)
    {
        StartAuthSession(attr);
    }
    else if (strcmp(el, DIA_SESSION_ACCT_STRING) == 0)
    {
        StartAcctSession(attr);
    }
    else if (strcmp(el, DIA_TRACE_SUBSYSTEM_STRING) == 0)
    {
        inTrace = ITS_TRUE;
        StartTrace(attr);
    }
    else if (strcmp(el, DIA_CRITICAL_STRING) == 0)
    {
        HandleTrace(el, attr);
    }
    else if (strcmp(el, DIA_ERROR_STRING) == 0)
    {
        HandleTrace(el, attr);
    }
    else if (strcmp(el, DIA_WARNING_STRING) == 0)
    {
        HandleTrace(el, attr);
    }
    else if (strcmp(el, DIA_DEBUG_STRING) == 0)
    {
        HandleTrace(el, attr);
    }
    else if (strcmp(el, DIA_PEER_CONFIG_STRING) == 0)
    {
        inPeerConfig = ITS_TRUE;
    }
    else if (strcmp(el, DIA_TIMER_STRING) == 0)
    {
        HandleTimer(attr);
    }
    else if (strcmp(el, DIA_RETRANS_INTVL_STRING) == 0)
    {
        isRetransIntv = ITS_TRUE;
        HandleValue(el, attr);
    }
    else if (strcmp(el, DIA_RETRANS_COUNT_STRING) == 0)
    {
        isRetransCnt = ITS_TRUE;
        HandleValue(el, attr);
    }
    else if (strcmp(el, DIA_PEER_STRING) == 0)
    {
        if (inPeerConfig)
        {
            inPeer = ITS_TRUE;
            StartPeer(attr);
        }
    }
    else if (strcmp(el, DIA_STATIC_ROUTING_TABLE) == 0)
    {
        inStaticRoutingConfig = ITS_TRUE;
    }
    else if (strcmp(el, DIA_STATIC_ROUTE) == 0)
    {
        if (inStaticRoutingConfig)
        {
            StartStaticRoute(attr);
        }
    }
    else if (strcmp(el, DIA_REALM_CONFIG_STRING) == 0)
    {
        inRealmConfig = ITS_TRUE;
    }
    else if (strcmp(el, DIA_ROUTE_STRING) == 0)
    {
        StartRoute(attr);
    }
    else if (strcmp(el, DIA_DESTINATION_STRING) == 0)
    {
        if (inRealmConfig)
        {
            inDestination = ITS_TRUE;
            StartDestination(attr);
        }
    }
    else if (strcmp(el, DIA_FAILOVER_STRING) == 0)
    {
        if (inPeer)
        {
            StartFailover(attr);
        }
    }
    else if (strcmp(el, DIA_ALT_PEER_STRING) == 0)
    {
        if (inPeer)
        {
            HandleAlternatePeer(attr);
        }
    }
    else if (inVendorSpecific)
    {
    }
#ifdef TLS_ENABLED
    else if (strcmp(el, DIA_SECURITY_STRING) == 0)
    {
        inSecurityConfig = ITS_TRUE;
        HandleSecurity(attr);
    }
    else if (strcmp(el, DIA_TRUSTED_CAS) == 0)
    {
        inTrustedCAs = ITS_TRUE;
    }
    else if (strcmp(el, DIA_CA) == 0)
    {
        HandleCAs(attr);
    }
#endif
    else if (strcmp(el, DIA_QUEUE_MGMT_STRING) == 0)
    {
        HandleQueueMgmt(attr);
    }
    else if (strcmp(el, DIA_DSCP_STRING) == 0)
    {
        HandleDscpValue(el, attr);
    }
    else if (strcmp(el, DIA_TRANSFORMATION) == 0)
    {
        DTFConfigValue(el, attr);
    }
    else if (strcmp(el, DIA_DICTIONARY_ID_STRING) == 0)
    {
        HandleDictionaryID(el, attr);
    }
    else if (strcmp(el, DIA_TLS_CIPHER_SUITS) == 0)
    {
        inTlsCipherSuites = ITS_TRUE;
    }
#ifdef TLS_ENABLED
    else if (strcmp(el, DIA_CIPHER_SUIT) == 0)
    {
        HandleCipherSuites(attr);
    }
#endif
    else if (strcmp(el, DIA_TRANS_PLUGIN_PATH_STRING) == 0)
    {
        attr++;
        config->setPluginPathName(*attr);
    }
    else if (strcmp(el, DIA_PLUGIN) == 0)
    {
        HandlePlugins(el, attr);
    }
#ifdef TLS_ENABLED
    else if (strcmp(el, DIA_TLS_CRL_PATH) == 0)
    {
        HandleSetCrlPath(attr);
    }

    else if (strcmp(el, DIA_CRL_VERIFICATION) == 0)
    {
        HandleSetCrlVerification(attr);
    }

    else if (strcmp(el, DIA_TLS_OWN_CA_PATH) == 0)
    {
        SetOwnCertPath(attr);
    }
#endif

    else if (strcmp(el, DIA_ENABLE_TLS_STRING) == 0)
    {
        TlsEnable(attr);
    }
    else if (strcmp(el, DIA_IS_PREDECTIVE_LOOP_AVID_ENABLE) == 0)
    {
        IsPredectiveLoopEnable(attr);
    }

}

static void
EndTrace()
{
    /* Create the Appropriate Traces */
    /* If no fstream (stdout/log/file) value is configured,
       defualt create for stdout and disable. Required  if need to enable
       via MML
    */
    if (dbgMask == TRACE_TO_NONE)
    {
        DiaTrace::GetDiaTrace()->Create(DIA_DEBUG, (dbgMask|TRACE_TO_DISPLAY));
    }
    else
    {
        DiaTrace::GetDiaTrace()->Create(DIA_DEBUG, dbgMask);
    }
    if (warnMask == TRACE_TO_NONE)
    {
       DiaTrace::GetDiaTrace()->Create(DIA_WARNING,(warnMask|TRACE_TO_DISPLAY));
    }
    else
    {
        DiaTrace::GetDiaTrace()->Create(DIA_WARNING, warnMask);
    }
    if (errMask == TRACE_TO_NONE)
    {
        DiaTrace::GetDiaTrace()->Create(DIA_ERROR, (errMask|TRACE_TO_DISPLAY));
    }
    else
    {
        DiaTrace::GetDiaTrace()->Create(DIA_ERROR, errMask);
    }
    if (critMask == TRACE_TO_NONE)
    {
        DiaTrace::GetDiaTrace()->Create(DIA_CRITICAL,
                                        (critMask|TRACE_TO_DISPLAY));
    }
    else
    {
        DiaTrace::GetDiaTrace()->Create(DIA_CRITICAL, critMask);
    }

    DiaTrace::GetDiaTrace()->Disable(DIA_DEBUG);
    DiaTrace::GetDiaTrace()->Disable(DIA_WARNING);
    DiaTrace::GetDiaTrace()->Disable(DIA_ERROR);
    DiaTrace::GetDiaTrace()->Disable(DIA_CRITICAL);

    if (dbgMask != TRACE_TO_NONE)
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_DEBUG);
    }

    if (warnMask != TRACE_TO_NONE)
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_WARNING);
    }

    if (errMask != TRACE_TO_NONE)
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_ERROR);
    }

    if (critMask != TRACE_TO_NONE)
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_CRITICAL);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Xml parser element end function
 *
 *  Input Parameters:
 *      data - dunno
 *      el - the element
 *      attr - the element's attributes
 *
 *  Notes:
 *      If difficulties are encountered either in parsing or setup, an
 *      assertion is raised.
 *
 *  See Also:
 ****************************************************************************/
static void
ElementEnd(void *data, const char *el)
{
    if (strcmp(el, DIA_STRING) == 0)
    {
    }
    else if (strcmp(el, DIA_LOCAL_STRING) == 0)
    {
        inLocalConfig = ITS_FALSE;
    }
    else if (strcmp(el, DIA_INSECURITY_ID_STRING) == 0)
    {
        isInband = ITS_FALSE;
    }
    else if (strcmp(el, DIA_VENDOR_ID_STRING) == 0)
    {
        isVendorId = ITS_FALSE;
    }
    else if (strcmp(el, DIA_SUPP_VENDOR_ID_STRING) == 0)
    {
        isSupported = ITS_FALSE;
    }
    else if (strcmp(el, DIA_AUTH_APP_ID_STRING) == 0)
    {
        isAuthId = ITS_FALSE;
    }
    else if (strcmp(el, DIA_ACCT_APP_ID_STRING) == 0)
    {
        isAccounting = ITS_FALSE;
    }
    else if (strcmp(el, DIA_VENDOR_SPEC_APP_ID_STRING) == 0)
    {
        inVendorSpecific = ITS_FALSE;
        if (inLocalConfig)
        {
            ((DIA_CER *)cer)->addVendorSpecificApplicationId((*venSpecAppId));
            ((DIA_CEA *)cea)->addVendorSpecificApplicationId((*venSpecAppId));
            ((DIA_CER *)rfc6733CER)->addVendorSpecificApplicationId((*venSpecAppId));
            ((DIA_CEA *)rfc6733CEA)->addVendorSpecificApplicationId((*venSpecAppId));
            delete venSpecAppId;
        }
    }
    else if (strcmp(el, DIA_TRANS_STRING) == 0)   // SCTP MultiHoming
    {
        if(inLocalConfig)
        {
            if(trans.type == ITS_DIA_T_SCTP)
            {
                trans.noIPs = otherTranIPno + 1;
                otherTranIPno = 0;
            }
            hInfo.transList[trCnt-1] = trans;
        }
    }

    else if (strcmp(el, DIA_HOST_INFO_STRING) == 0)
    {
        inHostInfo = ITS_FALSE;

        if (inLocalConfig)
        {
            config->GetHostInfoList().arr[hInfCnt] = hInfo;
            hInfCnt++;
            config->GetHostInfoList().count = hInfCnt;

            OriginHost ohost(hInfo.servHostName);
            ((DIA_CER *)cer)->setOriginHost(ohost);
            ((DIA_CEA *)cea)->setOriginHost(ohost);
            ((DIA_CER *)rfc6733CER)->setOriginHost(ohost);
            ((DIA_CEA *)rfc6733CEA)->setOriginHost(ohost);

            OriginRealm orealm(hInfo.realmName);
            ((DIA_CER *)cer)->setOriginRealm(orealm);
            ((DIA_CEA *)cea)->setOriginRealm(orealm);
            ((DIA_CER *)rfc6733CER)->setOriginRealm(orealm);
            ((DIA_CEA *)rfc6733CEA)->setOriginRealm(orealm);
	 try{
            for (int j = 0; j < hInfo.transCnt; j++)
            {
                if (hInfo.transList[j].publicServerIpAddr == NULL)
                {
                    if (DiaUtils::IsIPv6Address(hInfo.transList[j].serverIpAddr))
                    {
                        Address oaddr(Address::IPV6,
                                  hInfo.transList[j].serverIpAddr);

                        HostIPAddress hostIp(oaddr);
                        ((DIA_CER *)cer)->addHostIPAddress(hostIp);
                        ((DIA_CEA *)cea)->addHostIPAddress(hostIp);
                        ((DIA_CER *)rfc6733CER)->addHostIPAddress(hostIp);
                        ((DIA_CEA *)rfc6733CEA)->addHostIPAddress(hostIp);
                    }
                    else
                    {
                        Address oaddr(Address::IPV4,
                                  hInfo.transList[j].serverIpAddr);

                        HostIPAddress hostIp(oaddr);
                        ((DIA_CER *)cer)->addHostIPAddress(hostIp);
                        ((DIA_CEA *)cea)->addHostIPAddress(hostIp);
                        ((DIA_CER *)rfc6733CER)->addHostIPAddress(hostIp);
                        ((DIA_CEA *)rfc6733CEA)->addHostIPAddress(hostIp);
                    }
                }
                else
                {
                   if (DiaUtils::IsIPv6Address(hInfo.transList[j].publicServerIpAddr))
                    {
                        Address oaddr(Address::IPV6,
                                    hInfo.transList[j].publicServerIpAddr);

                        HostIPAddress hostIp(oaddr);
                        ((DIA_CER *)cer)->addHostIPAddress(hostIp);
                        ((DIA_CEA *)cea)->addHostIPAddress(hostIp);
                        ((DIA_CER *)rfc6733CER)->addHostIPAddress(hostIp);
                        ((DIA_CEA *)rfc6733CEA)->addHostIPAddress(hostIp);
                    }
                    else
                    {
                        Address oaddr(Address::IPV4,
                                    hInfo.transList[j].publicServerIpAddr);

                        HostIPAddress hostIp(oaddr);
                        ((DIA_CER *)cer)->addHostIPAddress(hostIp);
                        ((DIA_CEA *)cea)->addHostIPAddress(hostIp);
                        ((DIA_CER *)rfc6733CER)->addHostIPAddress(hostIp);
                        ((DIA_CEA *)rfc6733CEA)->addHostIPAddress(hostIp);
                    }
                }
                /* Store LocalIp to bind Client Sockets */
                if (hInfo.transList[j].serverIpAddr != NULL)
                {
                    config->SetLocalIpAddr(hInfo.transList[j].serverIpAddr);
                }
            }
	   }
	   catch(...)
	   {
		DT_ERR(("Invalid Local Ip Address:: same will not be set in cer/cea also "));
	   }

        }
    }
    else if (strcmp(el, DIA_SESSION_CFG_STRING) == 0)
    {
        inSessionConfig = ITS_FALSE;
        if (inLocalConfig)
        {
        }
    }
    else if (strcmp(el, DIA_TRACE_SUBSYSTEM_STRING) == 0)
    {
        EndTrace();
        inTrace = ITS_FALSE;
    }
    else if (strcmp(el, DIA_PEER_CONFIG_STRING) == 0)
    {
        inPeerConfig = ITS_FALSE;
        PeerTable::GetPeerTable()->UpdateAltPeerInfo();
    }
    else if (strcmp(el, DIA_RETRANS_INTVL_STRING) == 0)
    {
        isRetransIntv = ITS_FALSE;
    }
    else if (strcmp(el, DIA_RETRANS_COUNT_STRING) == 0)
    {
        isRetransCnt = ITS_FALSE;
    }
    else if (strcmp(el, DIA_PEER_STRING) == 0)
    {
        if (inPeerConfig)
        {   /* SCTP MultiHoming */
            for(int i = 0; i < DIA_PE_CONN_TRANS_COUNT(pEntry); i++)
            {
                if(DIA_PE_CONN_TINFO_INDEX(pEntry,i).type == ITS_DIA_T_SCTP)
                {
                    DIA_PE_CONN_TINFO_INDEX(pEntry,i).noIPs = otherPeerIPno + 1;
                }
                if(i == (DIA_PE_CONN_TRANS_COUNT(pEntry) -1))
                {
                    otherPeerIPno = 0;
                }
            }

            inPeer = ITS_FALSE;

            /* get trIndex for Peer */
            int trIndx = trTable.GetNextTrIndex();

            if (trIndx == 0)
            {
                DT_ERR(("Max peer limit reached Peer %s\n",
                        DIA_PE_HOST(pEntry)));

                DIA_Alarm(15250, __FILE__, __LINE__, "Peer=%s:Realm=%s",
                            DIA_PE_HOST(pEntry), DIA_PE_REALM(pEntry));
            }
            else
            {
                DIA_PE_INDEX(pEntry) = trIndx;
                DIA_PE_IS_FORCE_DISCONNECTED(pEntry) = false;

                int ret = PeerTable::GetPeerTable()->InsertEntry(pEntry);

                if (ret == ITS_SUCCESS)
                {
                    DT_DBG(("Succesfully Added Peer Entry For %s\n",pEntry->hostIdentity));

                }
                else if (ret == ITS_EDUPLENTRY)
                {
                    DT_ERR(("Failed to Add Peer Entry: Entry Exists For %s\n",
                                     pEntry->hostIdentity));
                }
            }
        }
    }
    else if (strcmp(el, DIA_REALM_CONFIG_STRING) == 0)
    {
        inRealmConfig = ITS_FALSE;
    }
    else if (strcmp(el, DIA_STATIC_ROUTING_TABLE) == 0)
    {
        inStaticRoutingConfig = ITS_FALSE;
    }
    else if (strcmp(el, DIA_ROUTE_STRING) == 0)
    {
        if (inRealmConfig)
        {
            inDestination = ITS_FALSE;

            if (rDstCnt == 0)
            {
                /* Reached Route End: But No single destination */
                DT_ERR(("Invalid Realm Entry: No Proper Destination Set For %s\n",
                                  rEntry->realmName));
                free ((void *)rEntry->realmName);
                free ((void *)rEntry);
                return;
            }

            int ret = RealmTable::GetRealmTable()->InsertEntry(rEntry);
            if (ret == ITS_SUCCESS)
            {
                DT_DBG(("Succesfully Added Realm Entry For %s\n",
                                 rEntry->realmName));
            }
            else if (ret == ITS_EDUPLENTRY)
            {
                DT_ERR(("Failed to Add Realm Entry: Entry Exists For %s\n",
                                 rEntry->realmName));
            }

        }
        rDstCnt = 0;
    }
    else if (strcmp(el, DIA_FAILOVER_STRING) == 0)
    {
        isFailover      = ITS_FALSE;
        isFailback      = ITS_FALSE;
        isRedundantMate = ITS_FALSE;
    }
    else if (strcmp(el, DIA_SECURITY_STRING) == 0)
    {
        inSecurityConfig = ITS_FALSE;
    }
    else if (strcmp(el, DIA_TRUSTED_CAS) == 0)
    {
        inTrustedCAs = ITS_FALSE;
    }
    else if (strcmp(el, DIA_TLS_CIPHER_SUITS) == 0)
    {
        inTlsCipherSuites = ITS_FALSE;
    }
    else if (strcmp(el, DIA_PEER_DISCONNECT_CAUSE_SUPPORT) == 0)
    {
    }
}

void
ITSDiaConfig::DiaParserInitialize(char *fileName)
{
    FILE *xml;
    long size;
    char *buf;
    size_t count;
    int parseSuccessful, ret;


    buf = NULL;
    size = 0;

    parser = XML_ParserCreate(NULL);
    DIA_PARSER_ASSERT(parser != NULL);

    /* set the token functions */
    XML_SetElementHandler(parser, (XML_StartElementHandler)ElementStart,
                          (XML_EndElementHandler)ElementEnd);

    xml = fopen(fileName, "r");
    DIA_PARSER_ASSERT(xml != NULL);

    /* go to the end */
    ret = fseek(xml, 0, SEEK_END);
    DIA_PARSER_ASSERT(ret == 0);

    /* how big a buffer */
    size = ftell(xml);
    DIA_PARSER_ASSERT(size >= 0);

    /* rewind */
    rewind(xml);

    /* add space for a trailing NUL */
    size++;

    /* get the buffer */
    buf = (char *)malloc(size);
    DIA_PARSER_ASSERT(buf != NULL);

    /* read the file */
    count = fread(buf, sizeof(char), size - 1, xml);

    /* don't need the handle anymore */
    fclose(xml);

#if !defined(WIN32)
    /* this doesn't work due to that stupid everpresent CR/LF issue */
    DIA_PARSER_ASSERT(count == (size_t)(size - 1));
#endif

    /* add NULL */
    buf[size - 1] = 0;

    inParser = ITS_TRUE;
    parseSuccessful = XML_Parse(parser, buf, size, ITS_TRUE);
    DIA_PARSER_ASSERT(parseSuccessful == 0);

    /* clean up */
    if (buf)
    {
        free(buf);
    }

}

void
ITSDiaConfig::Print()
{
    static bool mandInfoMissing = false;

    printf("ProductInfo: Name = %s, Version No = %d, Firmware Rev = %d\n\n",
           prodInfo.GetName(), prodInfo.GetVersionNo(), prodInfo.GetFirmwareRev());

    if(config->getpluginpathname())
    {
        printf("PluginPath::%s\n",config->getpluginpathname());
    }

    for (int i = 0; i < hostInfoList.count; i++)
    {
        printf("HostInfo: HostName = %s\n",
               hostInfoList.arr[i].servHostName);

        if (*(hostInfoList.arr[i].servHostName) == NULL)
        {
            DT_CRT(("Mandatory Configuration : HostName is NULL string\n"));
            mandInfoMissing = true;
        }

        printf("HostInfo: RealmName = %s\n",
               hostInfoList.arr[i].realmName);

        if (*(hostInfoList.arr[i].realmName) == NULL)
        {
            DT_CRT(("Mandatory Configuration : RealmName is NULL string\n"));
            mandInfoMissing = true;
        }

         for (int j = 0;
              j < hostInfoList.arr[i].transCnt;
              j++)
         {
             
             if(hostInfoList.arr[i].transList[j].securePort<=1023)
             {
                 if(hostInfoList.arr[i].transList[j].portNo <= 1023)
                 {
                     DT_CRT(("Mandatory Configuration : Standard Ports Cannot be Configured"));
                     mandInfoMissing = true;
                 }
             }
             printf("HostInfo: Transport: Type = %d, IP Addr = %s, PortNo = %d,SecurePortNo = %d\n",
                     hostInfoList.arr[i].transList[j].type,
                     hostInfoList.arr[i].transList[j].serverIpAddr,
                     hostInfoList.arr[i].transList[j].portNo,
                     hostInfoList.arr[i].transList[j].securePort);


             if (*(hostInfoList.arr[i].transList[j].serverIpAddr) == NULL)
             {
                 DT_CRT(("Mandatory Configuration : IP-Addr is NULL string\n"));
                 mandInfoMissing = true;
             }
         }
    }

    printf("AuthSessionCfg:State:%d,Timeout:%d,LifeTime:%d,GracePeriod:%d, AbortRetry:%d\n",
           authSession.GetSubType(),
           authSession.GetTimeout(),
           authSession.GetLifeTime(),
           authSession.GetGracePeriod(),
           authSession.GetRetryAbort());

    printf("AcctSessionCfg: State:%d,Timeout:%d,InterimIntvl:%d,RealTime:%d\n",
           acctSession.GetSubType(),
           acctSession.GetTimeout(),
           acctSession.GetInterimIntvl(),
           acctSession.GetRealTime());

    printf("PeerTimersCfg: Expiry:%d,Retry:%d,Watchdog:%d\n",
           peerTimers.GetExpiry(),
           peerTimers.GetRetry(),
           peerTimers.GetWatchdog());

    printf("PeerTimersCfg: RetransInterval:%d,RetransCount:%d\n",
           peerTimers.GetRetransIntvl(),
           peerTimers.GetRetransCount());

    std::cout << *(PeerTable::GetPeerTable());
    std::cout << *(RealmTable::GetRealmTable());

    ITSDiaConfig* cfg = &itsDiaConfig;
#ifdef TLS_ENABLED
    if(cfg->isTlsEnable())
    {
        ITSDiaConfig::GetSecurityConfig().PrintSecurityConfig();
    }
#endif
	
	//DTF Plugins
	itsDiaConfig.PrintTransformPlugin();

    try
    {
        cout << "CER Info" << endl << (*localCER) << endl;
        cout << "CEA Info" << endl << (*localCEA) << endl;
        cout << "CER without inband Info" << endl << (*rfc6733LocalCER) << endl;
        cout << "CEA without inband Info" << endl << (*rfc6733LocalCEA) << endl;
    }
    catch (...)
    {
        DT_CRT(("Invalid Configuration::"));

        if (!vendorIdPresnt)
        {
            DT_CRT(("Mandatory Configuration Missing : Vendor-Id"));
            mandInfoMissing = true;
        }
        if (config->GetProductInfo().GetName() == NULL)
        {
            DT_CRT(("Mandatory Configuration Missing : Product Name"));
            mandInfoMissing = true;
        }
        if (config->getLocalHostName() == NULL)
        {
            DT_CRT(("Mandatory Configuration Missing : Local Host"));
            mandInfoMissing = true;
        }
        if (config->getLocalRealmName() == NULL)
        {
            DT_CRT(("Mandatory Configuration Missing : Local Realm"));
            mandInfoMissing = true;
        }
        if (config->GetLocalIpAddr() == NULL)
        {
            DT_CRT(("Mandatory Configuration Missing : Local IP-Addr"));
            mandInfoMissing = true;
        }
    }
    if(mandInfoMissing)
    {
        DT_CRT(("Exiting from Diameter Stack : Mandatory Info Missing or Wrong"));
        exit(0);
    }
}

