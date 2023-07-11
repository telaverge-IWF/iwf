/*********************************-*CPP*-************************************
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
 * LOG: $Log: its_dia_config.cpp,v $
 * LOG: Revision 3.21.4.6.4.2.4.3.4.1.8.1  2014/12/04 12:00:26  pramana
 * LOG: Added support for allowing requests for a different hosts
 * LOG:
 * LOG: Revision 3.21.4.6.4.2.4.3.4.1  2014/02/12 07:15:00  millayaraja
 * LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
 * LOG:
 * LOG: Revision 3.21.4.6.4.2.4.3  2013/12/09 04:52:26  ncshivakumar
 * LOG: Fixed bug 2439,2443,2368,1898
 * LOG:
 * LOG: Revision 3.21.4.6.4.2.4.2  2013/10/26 07:42:21  ncshivakumar
 * LOG: RFC 6733 changes
 * LOG:
 * LOG: Revision 3.21.4.6.4.2.4.1  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 3.21.4.6.4.2  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.21.4.6.4.1  2013/02/12 05:45:46  vsarath
 * LOG: Changes for TLS enable/disable
 * LOG:
 * LOG: Revision 3.21.4.6  2012/12/15 06:07:17  vsarath
 * LOG: Provided option for own Certificate path
 * LOG:
 * LOG: Revision 3.21.4.5  2012/11/20 12:23:23  pramana
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 3.21.4.1.22.2  2012/11/20 04:19:40  pramana
 * LOG: merged from 00 branch
 * LOG:
 * LOG: Revision 3.21.4.3  2012/11/06 16:31:21  pramana
 * LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
 * LOG:
 * LOG: Revision 3.21.4.1.20.3  2012/11/06 10:06:40  cprem
 * LOG: Merged from 00 branch for 0212-06 release
 * LOG:
 * LOG: Revision 3.21.4.1.20.2  2012/11/06 08:59:27  vsarath
 * LOG: Added for TLS enhancements
 * LOG:
 * LOG: Revision 3.21.4.1.20.1  2012/11/05 03:37:58  vsarath
 * LOG: Added for TLS enhancements
 * LOG:
 * LOG: Revision 3.21.4.2  2012/10/23 08:10:18  cprem
 * LOG: Support for reading transform plugin configuration.
 * LOG:
 * LOG: Revision 3.21.4.1  2012/09/06 11:30:46  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 * LOG:
 * LOG: Revision 3.21.6.1  2012/08/22 12:53:43  jvikas
 * LOG: Fixed Linking Errors and Included XML Config for Transformation.
 * LOG:
 * LOG: Revision 3.21  2011/04/26 06:12:33  nvijikumar
 * LOG: Introduced XML config parameter to disable stack initiated STR while
 * LOG: handling ASA
 * LOG:
 * LOG: Revision 3.20  2010/11/03 12:59:06  vkumara
 * LOG: DSCP support for IPV6
 * LOG:
 * LOG: Revision 3.19  2009/08/24 11:44:47  rajeshak
 * LOG: Fix for Issue 2317(ACTIVE COLD REDUNDANCY::IDC not able to send
 * LOG: messages to ACTIVE server)
 * LOG:
 * LOG: Revision 3.18  2009/04/13 13:36:57  rajeshak
 * LOG: Peer Discovery changes.
 * LOG:
 * LOG: Revision 3.17  2009/04/10 06:26:28  sureshj
 * LOG: Initial value for enableHMI flag.
 * LOG:
 * LOG: Revision 3.16  2009/03/19 12:03:26  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.15  2009/03/18 12:45:08  rajeshak
 * LOG: Added functions for new MML command and API.
 * LOG:
 * LOG: Revision 3.14  2009/02/27 06:16:15  rajeshak
 * LOG: Printing SCTP params configured in XML.
 * LOG:
 * LOG: Revision 3.13  2009/02/12 04:20:43  nvijikumar
 * LOG: Implementation of Callback for message processing at IDS
 * LOG:
 * LOG: Revision 3.12  2009/02/05 09:50:56  ssaxena
 * LOG: Changes for Redirect Agent code reviews.
 * LOG:
 * LOG: Revision 3.11  2009/02/04 05:48:40  nvijikumar
 * LOG: Changes to make Initiate Peer connections as configurable
 * LOG:
 * LOG: Revision 3.10  2008/12/12 08:01:37  sureshj
 * LOG: Initial draft for Stack Statistics support (Suresh)
 * LOG:
 * LOG: Revision 3.9  2008/12/10 11:29:43  nvijikumar
 * LOG: Having new flag to check Scenario type Distributed / Static
 * LOG:
 * LOG: Revision 3.8  2008/11/26 12:03:28  nvijikumar
 * LOG: Local IP binding for Client Sockets
 * LOG:
 * LOG: Revision 3.7  2008/11/22 10:55:40  ssaxena
 * LOG: Fix for IssueId : 1292
 * LOG: getNodeState and switchOver MML commands are not working for Redundancy
 * LOG:
 * LOG: Revision 3.6  2008/11/19 05:15:26  nvijikumar
 * LOG: IssueID:None
 * LOG: FeatureID:None
 * LOG: Description:Made Peer IP Check as configurable option
 * LOG:
 * LOG: Revision 3.5  2008/11/06 07:51:22  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Incorporating Code review Comments renaming StackTunning
 * LOG:              with QueueMgmt
 * LOG:
 * LOG: Revision 3.4  2008/10/31 05:59:13  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID:none
 * LOG: Description: Configuration changes Stack Tunning
 * LOG:
 * LOG: Revision 3.3  2008/10/28 12:06:28  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.2  2008/06/13 11:48:35  hbhatnagar
 * LOG: Added PrintSecurityInfo() and TLs related functionality
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.10  2007/02/26 04:45:09  nvijikumar
 * LOG: Enable Hexdump print by default without xml changes.
 * LOG:
 * LOG: Revision 2.9  2007/02/19 15:18:42  nvijikumar
 * LOG: Control Message hex dump from XML configuration.
 * LOG:
 * LOG: Revision 2.8  2006/12/21 15:34:15  tpanda
 * LOG: Minor fixes to previous commit related to OriginStateId
 * LOG:
 * LOG: Revision 2.7  2006/12/21 15:26:04  tpanda
 * LOG: AddOriginStateId option is added to check if OriginStateId be added to cmd
 * LOG:
 * LOG: Revision 2.6  2006/12/20 15:54:05  nvijikumar
 * LOG: Elimination of multiple ITS_FindFeature function calls(DCCA & Redundancy).
 * LOG:
 * LOG: Revision 2.5  2006/12/11 14:27:34  nvijikumar
 * LOG: Send Peer based msgs to application, if peerMsgToApp flag is set in the XML.
 * LOG:
 * LOG: Revision 2.4  2006/11/29 11:52:14  tpanda
 * LOG: Redundancy related enhancements and fixes for few bugs raised for redundancy
 * LOG:
 * LOG: Revision 2.3  2006/11/25 03:57:20  tpanda
 * LOG: Changes for Msg based redundancy
 * LOG:
 * LOG: Revision 2.2  2006/10/16 06:18:59  yranade
 * LOG: Generate OriginStateId on Initialization
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 *
 * ID: $Id: its_dia_config.cpp,v 3.21.4.6.4.2.4.3.4.1.8.1 2014/12/04 12:00:26 pramana Exp $
*/
#include <its++.h>
#include <iostream>
#include <engine++.h>
#include <its_timers.h>
#include <its_iniparse.h>

#include <dia_trace.h>
#include <its_dia_config.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

IDSMsgProcessFunc IDSMsgProcessCallBack = NULL;
IDSMsgProcessFunc IDSRedundancyCallBack = NULL;
IDSCmdProcessFunc IDSCmdProcessCallBack = NULL;

ITS_Mutex ITSDiaConfig::guard(0);
ITS_Mutex ITSDiaConfig::lock(0);

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
ITSDiaConfig::ITSDiaConfig()
    :isDebugDump(false),
     originStateId(TIMERS_Time()),
     localCER(NULL),
     localCEA(NULL),
     isMsgRedundancyEnabled(false),
     isRedundancyEnabled(false),
     mateHostName(NULL),
     localHostName(NULL),
     localRealmName(NULL),
     isDefaultRealmRoutingEnabled(false),
     peerMsgToAppEnabled(false),
     redunClass(NULL),
     dccaClass(NULL),
     iforiginStateId(false),
     enableHexDump(true),
     interWorkingMode(false),
     enableHMI(false),
     enableQueueMgmt(false),
     enablePeerIpCheck(false),
     localIpAddr(NULL),
     isDistScenario(false),
     enableStackStats(false),
     initiateConnsOpt(true),
     isLocalCachingEnabled(false),
     isRedirectAppProcessing(false),
     peerDiscoveryEnabled(false),
     peerDiscoveryInterval(PEER_DISCOVERY_INTERVAL),
     ipv6DscpValue(0),
     disStackInitiatedStr(false),
     isDTFEnabled(false),
     ipv6Enabled(false),
     isPredictiveLoopAvdRequired(false),
     isSnaptrSupported(false),
     pluginPathName(NULL)
{
    memset(&hostInfoList,0,sizeof(DIA_HOST_INFO_LIST));
    tcpSockConfig.connectTimeout = 1000;
}

ITSDiaConfig::~ITSDiaConfig()
{
    if (localCER)
    {
        delete localCER;
    }
    if (localCEA)
    {
        delete localCEA;
    }
    if (mateHostName)
    {
       free((char*)mateHostName);
       mateHostName = NULL;
    }
    if (localHostName)
    {
       free((char*)localHostName);
       localHostName = NULL;
    }
    if (localRealmName)
    {
       free((char*)localRealmName);
       localRealmName = NULL;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
void
ITSDiaConfig::Lock() const
{
    int res;
    res = const_cast<ITS_Mutex&>(lock).Acquire();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
void
ITSDiaConfig::Unlock() const
{
    int res;
    res = const_cast<ITS_Mutex&>(lock).Release();    
}

static ITSDiaConfig *config = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  retrieve the current Dia configuration.
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
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************///
#if 0
ITSDiaConfig* ITSDiaConfig::GetITSDiaConfig()
{

    if (config == NULL)
    {
        /* Moved inside if Due to Performance issue */
        ITS_ASSERT(ITSDiaConfig::guard.Acquire() == ITS_SUCCESS);

        config = new ITSDiaConfig;

        ITSDiaConfig::guard.Release();
    }


    return config;
}
#endif
/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
void ITSDiaConfig::ReloadITSDiaConfig()
{
    ITSDiaConfig* tmp = new ITSDiaConfig;
    static ITSDiaConfig* release = NULL;

    if (release)
    {
        TIMERS_Sleep(3);
        delete release;
    }

    ITS_ASSERT(ITSDiaConfig::guard.Acquire() == ITS_SUCCESS);

    release = config;
    config = tmp;

    ITSDiaConfig::guard.Release();
}

void ITSDiaConfig::PrintStreamSocketConfig()
{
    //Warning fix - deprecated convertion from const string to char*
    //char* hbStr = NULL;
    char hbStr[MAX_HB_STR_LENGTH+1];
    memset(hbStr, 0, MAX_HB_STR_LENGTH+1);
    if (sockConfig.hbOn)
    {
        //hbStr = "yes";
        strncpy(hbStr, "yes", MAX_HB_STR_LENGTH-strlen(hbStr));
    }
    else
    {
        //hbStr = "no";
        strncpy(hbStr, "no", MAX_HB_STR_LENGTH-strlen(hbStr));
    }

    DT_DBG(("SCTP Configuration Options: CookieLife =%d, HbOn=%s, HBInterval=%d\n",
                                  sockConfig.cookieLife ,
                                  hbStr,
                                  sockConfig.hbTimeout));
    DT_DBG(("Init Timeout=%d, MaxAttempts=%d, IN Streams=%d, Out Streams=%d\n",
                                  sockConfig.initTimeout,
                                  sockConfig.maxAttempts,
                                  sockConfig.maxNoOfInStreams,
                                  sockConfig.noOfOutStreams));
    DT_DBG(("Recv Timeout sec=%d, USec=%d, Send Timeout sec=%d, USec=%d\n",
                                  sockConfig.recvTimeout.tv_sec,
                                  sockConfig.recvTimeout.tv_usec,
                                  sockConfig.sendTimeout.tv_sec,
                                  sockConfig.sendTimeout.tv_usec));
    DT_DBG(("Shutdown Timeout=%d, SackDelay=%d, Association MaxAttempt=%d\n",
                                  sockConfig.shutdownTimeout,
                                  sockConfig.ackDelay,
                                  sockConfig.asocmaxrxt));
    DT_DBG(("RTO Max=%d, RTO Min=%d, RTO Init=%d\n",
                                  sockConfig.rtoMax,
                                  sockConfig.rtoMin,
                                  sockConfig.rtoInitial));
    DT_DBG(("SendBuf Size=%d, RecvBuf Size=%d, PathMaxRetry=%d\n",
                                  sockConfig.sndBuffSize,
                                  sockConfig.rcvBuffSize,
                                  sockConfig.pathmaxrxt));

}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To Print the Tls security information in tabular form.
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
 *      void  
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef TLS_ENABLED
void
ITSDiaConfig::SecurityConfig::PrintSecurityConfig() const
{
    std::cout << endl;
    std::cout << "--------------------------------------------------------"\
                 "----" << endl;
    std::cout << "-- Security Configuration Begin --" << endl;
    std::cout << "---------------------------------------------------------"\
                 "---" << endl;
    std::cout << endl;


    std::cout << "Tls Type                  = " <<
           DIA_TLS_TYPE_TO_TEXT(GetTlsType()) << endl;

    std::cout << "Identity Verification     = " <<
       ((IsIdentityVerifyEnabled() == true)? "yes" : "no")<< endl;

    std::cout << "Certificate Type          = " <<
          DIA_CERTIFICATE_TYPE_TO_TEXT(GetCertificateType())<< endl;

    std::cout << "ServerCertificateFile     = " <<
          ((GetServCertFile() != NULL)? GetServCertFile(): "INVALID")<< endl;

    std::cout << "ServerKeyFile             = " <<
          ((GetServKeyFile() != NULL)? GetServKeyFile(): "INVALID")<< endl;

    std::cout << "ServerCertificateFile     = " <<
          ((GetServCertFile() != NULL)? GetServCertFile(): "INVALID")<< endl;

    std::cout << "ServerKeyFile             = " <<
          ((GetServKeyFile() != NULL)? GetServKeyFile(): "INVALID")<< endl;

    std::cout << "CAPath                    = " <<
          ((GetCAPath() != NULL)? GetCAPath(): "INVALID")<< endl;

    std::cout << "OwnCertPath               = " <<
          ((GetCAPath() != NULL)? GetOwnCertPath(): "INVALID")<< endl;

    std::cout << "CrlPath                   = " <<
          ((GetCrlPath() != NULL)? GetCrlPath(): "INVALID")<< endl;

    std::cout << "CRL Verification          = " <<
       ((GetCrlVerify() == true)? "yes" : "no")<< endl;

    std::cout << endl<< "-- Trusted Certificate Authorities --" << endl << endl;
    
    config = &itsDiaConfig;
    ITSDiaConfig::SecurityConfig& secConf = config->GetSecurityConfig();

    int count = secConf.GetTrustedCACount();
    for(int i=0; i < count; i++)
    {
        its::CertificateAuthority* CA = secConf.GetTrustedCA(i);
        std::cout << "Certificate FileName      = " <<
            (CA)->GetCertificateFileName()<< endl;

        if ((CA)->GetCertType() == its::CertificateAuthority::CERT_TYPE_PEM)
        {
            std::cout << "Certificate Type          = " <<
            DIA_PEM << endl;
        }
        else if ((CA)->GetCertType() == its::CertificateAuthority::CERT_TYPE_DER)
        {
            std::cout << "Certificate Type          = " <<
            DIA_DER << endl;
        }

        std::cout << "CRL FileName              = " <<
            (CA)->GetCRL().GetCRLFileName()<< endl;

    }

    std::cout << endl<< "-- List of Cipher suits --" << endl << endl;
    int cipherCount = secConf.GetCipherCount();
    for(int i=0; i < cipherCount; i++)
    {
        std::cout << "Cipher:"<<(i+1)<<"                 = " <<
        secConf.GetCipherAt(i)<<endl;
    }

    std::cout  << "-----------------------------------------------------" \
                  "-------" << endl;
    std::cout << "-- Security Configuration End --" << endl;
    std::cout << "-------------------------------------------------------"\
                 "-----" << endl;

}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To set the trace level for the Tls Library 
 *  Input Parameters:
 *     ITS_UINT tracelevel - a value between TLS_LOG_MIN(0) and TLS_LOG_MAX(10)
 *                           Higher number represent more verbosity.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     void 
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef TLS_ENABLED
void
ITSDiaConfig::SecurityConfig::SetTLSTraceLevel(ITS_UINT traceLevel)
{
    if (traceLevel >= DIA_TLS_LOG_MIN && traceLevel <= DIA_TLS_LOG_MAX)
    {
        tlsTraceLevel = traceLevel;
    }
    else
    {
        DT_WRN(("ITSDiaConfig::SecurityConfig::SetTracelevel: Trace level"\
                "not in range. Valid Range is: 0-10."));
        DT_DBG(("ITSDiaConfig::SecurityConfig::SetTracelevel: Overriding"\
                "the Tls Trace Level to 0."));
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To get the trace level for the Tls Library
 *  Input Parameters:
 *      None.
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     ITS_UINT: Value between TLS_LOG_MIN and TLS_LOG_MAX)
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_UINT
ITSDiaConfig::SecurityConfig::GetTLSTraceLevel()
{
    return tlsTraceLevel;
}

void ITSDiaConfig::SecurityConfig::AddTrustedCA(its::CertificateAuthority *cauObj)
{
    TrustedCAs.push_back(cauObj);
}

int ITSDiaConfig::SecurityConfig::GetTrustedCACount()
{
    int count = 0;
    vector<its::CertificateAuthority*>::const_iterator it;
    for(it = TrustedCAs.begin(); it != TrustedCAs.end(); it++)
    {
        count++;
    }
    return count;
}

its::CertificateAuthority* ITSDiaConfig::SecurityConfig::GetTrustedCA(int index)
{
    return TrustedCAs[index];
}

vector<its::CertificateAuthority*> ITSDiaConfig::SecurityConfig::GetCertificateAuthority()
{
    return TrustedCAs;
}

void ITSDiaConfig::SecurityConfig::PopulateCipherList(std::string name)
{
    cipherList.push_back(name);
}

int ITSDiaConfig::SecurityConfig::GetCipherCount()
{
    int count = 0;
    vector<std::string>::const_iterator it;
    for(it = cipherList.begin(); it != cipherList.end(); it++)
    {
        count++;
    }
    return count;
}

std::string ITSDiaConfig::SecurityConfig::GetCipherAt(int index)
{
    return cipherList[index];
}

#endif 

void ITSDiaConfig::PopulateTransformPlugin(DIA_TRANFORM_PLUGIN &plugin)
{
	TransformPlugin.push_back(plugin);
}

void ITSDiaConfig::PrintTransformPlugin(void)
{
	vector<DIA_TRANFORM_PLUGIN>::const_iterator it;

    std::cout << endl;
    std::cout << "--------------------------------------------------------"\
                 "----" << endl;
    std::cout << "-- Diameter Transformation Plugins --" << endl;
    std::cout << "---------------------------------------------------------"\
                 "---" << endl;
    std::cout << endl;

	for(it = TransformPlugin.begin(); it != TransformPlugin.end(); it++)
	{
    	std::cout << "Plugin Name               = " <<
          	 it->pluginName << endl;
    	std::cout << "Dictionary ID:1           = " <<
          	 it->dictId1 << endl;
    	std::cout << "Dictionary ID:2           = " <<
          	 it->dictId2 << endl;
    	std::cout << "Config file               = " <<
          	 it->config << endl<< endl;
    	std::cout << "--------------------------------------------------------"\
        	         "----" << endl;
	}
}

int ITSDiaConfig::GetTransfromPluginCount(void)
{
	int count = 0;
	vector<DIA_TRANFORM_PLUGIN>::const_iterator it;

	for(it = TransformPlugin.begin(); it != TransformPlugin.end(); it++)
	{
		count++;
	}
	return count;
}

DIA_TRANFORM_PLUGIN &ITSDiaConfig::GetTranformPluginAt(int index)
{
	return TransformPlugin[index];
}

void ITSDiaConfig::setTlsEnable(bool status)
{
    isTlsEnabled = status;
}

bool ITSDiaConfig::isTlsEnable()
{
    return isTlsEnabled;
}

bool ITSDiaConfig::isPredictiveLoopAvoidanceEnable()
{
    return isPredictiveLoopAvdRequired;
}

void ITSDiaConfig::setPredectiveLoopAvoidanceEnable(bool status)
{
    isPredictiveLoopAvdRequired = status;
}

bool ITSDiaConfig::isSnaptrSupportEnabled()
{
    return isSnaptrSupported;
}

void ITSDiaConfig::setIsSnaptrSupportedFlag(bool status)
{
    isSnaptrSupported = status;
}
/*.implementation:public
 *  ****************************************************************************
 *  Purpose:
 *      To Print the TCP configuration information .
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
 *      void  
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

void ITSDiaConfig::PrintTcpSocketConfig()
{
    DT_DBG(("Tcp Connect Timeout = %d \n",
                                  tcpSockConfig.connectTimeout));
}
